#ifndef S3HIT_H
#define S3HIT_H

#include <cstdio>
#include <utility>

#include "TVector3.h" 
#include "TObject.h" 

class S3Hit : public TObject         {
	public:
			S3Hit();
			~S3Hit();

			TVector3 position;
			std::pair<int,int> pixel;
			double energy;
			unsigned int charge;
			double time;
			double cfd;
			int detectornumber;
			void Clear();
			void Print();

			Double_t GetEnergy()	{	return energy;	}
			Double_t GetCharge()	{	return charge;	}
			Double_t GetTime()		{	return time;		}

	
	ClassDef(S3Hit,1);

};

#endif
