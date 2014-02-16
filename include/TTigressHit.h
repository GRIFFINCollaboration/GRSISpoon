#ifndef TIGRESSHIT_H
#define TIGRESSHIT_H

#include <stdio.h>

#include <TObject.h>

#include "TCrystalHit.h"

class TTigressHit : public TObject	{
	public:
		TTigressHit();
		~TTigressHit();

	private:
		int detector;
		int crystal;
		int first_segment;
		double first_segment_charge;

		TCrystalHit core;
		std::vector<TCrystalHit> segment;
		std::vector<TCrystalHit> bgo;

	public:

		/////////////////////////		/////////////////////////////////////
		void SetCore(TCrystalHit &temp)		{ core = temp;	} 
		void SetSegment(TCrystalHit &temp)	{ segment.push_back(temp);	}
		void SetBGO(TCrystalHit &temp)		{ bgo.push_back(temp);	}

		void SetDetectorNumber(const int &i)	{ detector = i;	} 
		void SetCrystalNumber(const int &i)	{ crystal = i; }
		void SetInitalHit(const int &i)		{ first_segment = i; }
		
		/////////////////////////		/////////////////////////////////////
		inline int GetDetectorNumber()	{	return detector;	}
		inline int GetCrystalNumber()	{	return crystal;		}
		inline int GetInitialHit()		{	return first_segment;	}

		inline int GetCharge()			{	return core.GetCharge();	}
		inline double GetEnergy()		{	return core.GetEnergy();	}
		inline double GetTime()			{	return core.GetTime();		}

		inline int GetSegmentMultiplicity()		{	return segment.size();	}
		inline TCrystalHit *GetSegment(const int &i)	{	return &segment.at(i);	}

		inline int GetBGOMultiplicity()			{	return bgo.size();	}
		inline TCrystalHit *GetBGO(const int &i)	{	return &bgo.at(i);	}

		inline TCrystalHit *GetCore()			{	return &core;	}

		void CheckFirstHit(int charge,int segment);

		static bool Compare(TTigressHit lhs, TTigressHit rhs);	//{ return (lhs.GetDetectorNumber() < rhs.GetDetectorNumber()); }

	public:
		virtual void Clear(Option_t *opt = "");
		virtual void Print(Option_t *opt = "");	

	ClassDef(TTigressHit,1)
};




#endif
