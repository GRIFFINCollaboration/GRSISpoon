#ifndef TTIGRESS_H
#define TTIGRESS_H


#include <vector>
#include <iostream>
#include <set>
#include <stdio.h>

#include "TCrystalData.h"
#include "TBGOData.h"
#include "TTigressHit.h"


#include <TMath.h>
#include <TVector3.h> 
#include <TNamed.h>

using namespace std;

class TTigress : public TCrystalData, public TBGOData, public TNamed {

	public:
		TTigress();
		~TTigress();

	public: 
		void BuildHits();	//!
		void BuildAddBack();	//!

		TTigressHit *GetTigressHit(int i)	{	return &tigress_hits[i];	}	
		Short_t GetMultiplicity()		{	return tigress_hits.size();	}	

		TTigressHit *GetAddBackHit(int i)	{	return &addback_hits[i];	}	
		Short_t GetAddBackMultiplicity()	{	return addback_hits.size();	}	


		TVector3 GetPosition(TTigressHit *);
		void   SetBeta(double &b) 		{	TTigress::beta = b;	} 
		double GetDopplerEnergy(TTigressHit *);

		static TVector3 GetPosition(int DetNbr ,int CryNbr, int SegNbr);


	private: 
		std::vector <TTigressHit> tigress_hits;
		std::vector <TTigressHit> addback_hits;

		static double beta;

		static bool fSetSegmentHits;
		static bool fSetBGOHits;

		static bool fSetCoreWave;
		static bool fSetSegmentWave;
		static bool fSetBGOWave;

		static double GeBlue_Position[17][9][3];	//!	detector segment XYZ
		static double GeGreen_Position[17][9][3];	//!
		static double GeRed_Position[17][9][3];		//!
		static double GeWhite_Position[17][9][3];	//!

	public:         
		virtual void Clear(Option_t *opt = "");		//!
		virtual void Print(Option_t *opt = "");		//!

   ClassDef(TTigress,1)  // SharcPhysics structure


};








#endif


