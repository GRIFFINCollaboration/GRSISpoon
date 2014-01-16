


#include "TRf.h"

#include "math.h"
#include <gsl/gsl_linalg.h>


ClassImp(TRf)

TRf::TRf() 	{
	Clear();
}

TRf::~TRf() 	{	}

void TRf::SetRf(TTigFragment *frag)	{

	if(frag->HasWave())	{
		FindPhase(frag->wavebuffer);
		rftime = frag->TimeToTrig - phase;
	}
	else	{
		phase = NAN;
		rftime = NAN;
	}
}

void TRf::Clear()	{
	rf_omega = 2 * M_PI / (84e-9 / 10e-9);
	phase = NAN;
	rftime = NAN;
}


void TRf::FindPhase(vector<int> waveform)	{
   // Solve the chi-square equation for f(t) = a sin(wt) + b sin(wt) + c
   //   This is related to g(t) = A sin (wt + phi) + c
   //   via the transform: A = sqrt(a^2+b^2), phi = atan2(a,b)
   
   double omega = rf_omega;
   
   double matrix_data[9]; // 3x3
   double vector_data[3];

   // clear the matrix and vectors
   for (int i=0; i <3; i++) {
      vector_data[i] = 0;
      for (int j=0; j < 3; j++) {
	 matrix_data[3*i + j] = 0;
      }
   }
   // populate the matrix and vector from the waveform data
   for (size_t i=0; i < waveform.size(); i++) {
      double s = sin(omega * i);
      double c = cos(omega * i);

      // row for del(chi^2)/del a
      matrix_data[0] += s * s;
      matrix_data[1] += s * c;
      matrix_data[2] += s;
      // row for del(chi^2)/del b
      matrix_data[3] += s * c;
      matrix_data[4] += c * c;
      matrix_data[5] += c;
      // row for del(chi^2)/del c
      matrix_data[6] += s;
      matrix_data[7] += c;
      matrix_data[8] += 1;
      // column data
      vector_data[0] += waveform[i] * s;
      vector_data[1] += waveform[i] * c;
      vector_data[2] += waveform[i];
   }

   gsl_matrix_view m = gsl_matrix_view_array(matrix_data, 3, 3);
   gsl_vector_view v = gsl_vector_view_array(vector_data, 3);
   
   gsl_vector *x = gsl_vector_alloc(3); // the solution
   int s;
   
   gsl_permutation *p = gsl_permutation_alloc(3); // for the LU decomposition
   gsl_linalg_LU_decomp(&m.matrix, p, &s);
   gsl_linalg_LU_solve(&m.matrix, p, &v.vector, x);

   double x0 = gsl_vector_get(x,0); // the value of A
   double x1 = gsl_vector_get(x,1); // the value of B
   phase = atan2(x0,x1);		
   /* not currently used */
   /*
   double amplitude = sqrt(x0*x0 + x1*x1);
   double offset = gsl_vector_get(x,2);
   */
   gsl_permutation_free(p);
   gsl_vector_free(x);
   
   //return phase;
}




