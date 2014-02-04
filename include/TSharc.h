#ifndef TSHARC_H
#define TSHARC_H


#include <vector>
#include <stdio.h>
#include <iostream>

#include "TSharcData.h"
#include "SharcHit.h"

#include "TVector3.h" 
#include "TNamed.h"
#include "TMath.h"

#include "Globals.h"


class TSharc : public TSharcData, public TNamed 	{
	public:
		TSharc();
		~TSharc();

	public: 
		void Clear();   
		void BuildHits();

		SharcHit *GetSharcHit(int i) {return &sharc_hits[i];};
		Short_t GetMultiplicity() { return sharc_hits.size();};

		//private:
		//double GetEnergy()	{	;};
		TVector3 GetPosition(int FrontDet, int FrontStr, int BackDet, int BackStr);

	private: 
		std::vector <SharcHit> sharc_hits;

		static int totalhits;
        
   ClassDef(TSharc,1)  // SharcPhysics structure
};







#endif
