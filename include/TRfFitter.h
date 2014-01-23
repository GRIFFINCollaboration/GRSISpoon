#ifndef __TRF_FITTER_H
#define __TRF_FITTER_H

#include <vector>

#include <TNamed.h>

class TRfFitter : public TNamed {
 public:
   typedef int vector_element_t;
 private:
   void CalculateDerivative(const std::vector<TRfFitter::vector_element_t> &waveform);
   void CalculateDoubleDerivative(const std::vector<TRfFitter::vector_element_t> &waveform);
 public:
   TRfFitter();
   ~TRfFitter();

   double GetPhase() { return phase;	};
   double GetTime()	{	return rftime;	};
   const std::vector<double> &GetDerivative() {return derivative;};
   const std::vector<double> &GetDoubleDerivative() { return doubleDerivative; };
   const std::vector<double> &GetResiduals() {return residuals;};
   const std::vector<double> &GetScaledResiduals() {return scaledResiduals;};
   void Clear();
   void FindPhase(const std::vector<TRfFitter::vector_element_t> &waveform, Bool_t calcErrors);

   //private:   
   double rf_omega; 
   double phase;
   double rftime;
   double amplitude;
   double offset;
   
   double chisquare;
   double error_phase;
   double error_amplitude;
   double error_offset;
   double correlation;
   
   double scale_factor;
   double signal_noise;

   void Print(void) const;

   std::vector<double> derivative;  
   std::vector<double> doubleDerivative;
   std::vector<double> residuals;
   std::vector<double> scaledResiduals;
   
   ClassDef(TRfFitter, 1);
};

#endif // __TRF_FITTER_H
