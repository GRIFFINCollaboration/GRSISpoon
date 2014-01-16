#ifndef SILIHIT_H
#define SILIHIT_H

#include <cstdio>
#include <utility>

#include "TVector3.h" 
#include "TObject.h" 

class SiLiHit : public TObject         {
	public:
			SiLiHit();
			~SiLiHit();

			TVector3 position;

			double energy;
			unsigned int charge;
			double time;
			double cfd;

			int segment;

			void Clear();
			void Print();

			int GetSegment()		{	return segment;	}
			double GetEnergy()	{	return energy;	}
			double GetCharge()	{	return charge;	}
			double GetTime()		{	return time;		}

	
	ClassDef(SiLiHit,1);

};



#endif
