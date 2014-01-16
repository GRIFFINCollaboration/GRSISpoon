#ifndef TRF_PHASE_H
#define TRF_PHASE_H


#include <vector>
#include <iostream>
#include <stdio.h>



#include "TNamed.h"

#include "TTigFragment.h"

using namespace std;

class TRf :  public TNamed {
	
	public:
		TRf();
		~TRf();

		void 	 SetRf(TTigFragment*);
		double GetPhase() { return phase;	};
		double GetTime()	{	return rftime;	};
	
		void Clear();
	
	//private:
	
		double rf_omega; 
		double phase;
		double rftime;
		void FindPhase(vector <int> waveform);
		
	ClassDef(TRf,1)  // RF Physics structure

};



#endif
