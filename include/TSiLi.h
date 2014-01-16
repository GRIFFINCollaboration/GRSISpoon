
#ifndef TSILI_H
#define TSILI_H

#include <cstdio>
#include <vector>


#include <TNamed.h>
#include <TVector3.h>

#include "TSiLiData.h"
#include "SiLiHit.h"

class TSiLi: public TSiLiData, public TNamed	{

	public:
		TSiLi();
		~TSiLi();

		void BuildHits();		
		void Print();
		void Clear();
		
		
		int GetMultiplicity()	{	return	sili_hits.size();	}
		SiLiHit GetHit(int i) 	{	return	sili_hits.at(i);	}

		TVector3 GetPosition(int segment);

//	private:
	
		std::vector<SiLiHit> sili_hits;


	ClassDef(TSiLi,1);
	
};


#endif
