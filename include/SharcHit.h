#ifndef SHARCHIT_H
#define SHARCHIT_H

#include <stdio.h>
#include <utility>

#include "TVector3.h" 
#include "TObject.h" 

class SharcHit : public TObject 	{
	public:
		SharcHit();
		~SharcHit();

		TVector3 position;
		std::pair <int,int> pixel;
  	double delta_e;		
		unsigned int front_charge;	
		unsigned int back_charge;
  	double delta_t;		
  	double delta_cfd;		
  	double energy;   //pad only;
  	int		 charge;
 		double time;     //pad only;
 		double pad_cfd;
		int detectornumber; //
		void Clear();
		void Print();

//Double_t GetTime()		{	};

		Double_t GetDeltaE()	{	return delta_e;	};
		Double_t GetDeltaT()	{	return delta_t;	};
		Double_t GetPadE()		{	return energy;	};
		Double_t GetPadT()		{	return time;	};
		//Double_t GetDetectorNumber()		{	return  detectornumber;	};


		
	ClassDef(SharcHit,2)
};




#endif
