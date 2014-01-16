#ifndef TTIGRESS_H
#define TTIGRESS_H


#include <vector>
#include <iostream>
#include <set>
#include <stdio.h>

#include "TCloverData.h"
#include "TigressHit.h"

#include "TMath.h"
#include "TRotation.h"
#include "TVector3.h" 
#include "TNamed.h"

using namespace std;

class TTigress : public TCloverData, public TNamed {

	public:
		TTigress();
		~TTigress();

	public: 
		void Clear();   
		void BuildHits();
		void DoAddBack();


		TigressHit *GetTigressHit(int i)	{	return &tigress_hits[i];};	
		Short_t GetMultiplicity()	{	return tigress_hits.size();};

		TigressHit *GetAddBackHit(int i)	{	return &addback_hits[i];};	
		Short_t GetAddBackMultiplicity()	{	return addback_hits.size();};


		TVector3 GetPosition(int DetNbr,int CryNbr=0,int SegNbr=0);



	private: 

		std::vector <TigressHit> tigress_hits;
		std::vector <TigressHit> addback_hits;

		static double GeBlue_Position[17][9][3];	//detector segment XYZ
		static double GeGreen_Position[17][9][3];
		static double GeRed_Position[17][9][3];
		static double GeWhite_Position[17][9][3];

         
   ClassDef(TTigress,1)  // SharcPhysics structure


};








#endif


