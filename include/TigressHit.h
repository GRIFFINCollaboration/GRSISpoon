#ifndef TIGRESSHIT_H
#define TIGRESSHIT_H

#include <stdio.h>

#include "TVector3.h" 
#include "TObject.h" 


class TigressHit : public TObject	{
	public:
		TigressHit();
		~TigressHit();

		TVector3 position;
		TVector3 position_smeared;
		//double charge;
  	double energy;
 		double time;

		int detectornumber; 
		void Clear();
		void Print();	

	ClassDef(TigressHit,1)
};




#endif
