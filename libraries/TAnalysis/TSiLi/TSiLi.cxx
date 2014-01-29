

#include "TSiLi.h"

ClassImp(TSiLi)

TSiLi::TSiLi()	{	}

TSiLi::~TSiLi()	{	}

void TSiLi::Clear()	{
	sili_hits.clear();
}

void TSiLi::Print()	{	
	printf("===============\n");
	printf("not yet written\n");
	printf("===============\n");
}

void TSiLi::BuildHits()	{

	SiLiHit silihit;

	for(UInt_t i=0;i<this->GetMultiplicity();i++)     { 
//		for(int j=0;j<GetSectorMultiplicity();j++)    { 
//			if(GetRing_DetectorNumber(i) == GetSector_DetectorNumber(j))     {


	
			silihit.energy	=	this->GetEnergy(i);
			silihit.charge	=	this->GetCharge(i);
			silihit.time		=	this->GetTime(i);	
			silihit.cfd			=	this->GetCFD(i);
			silihit.segment	=	this->GetSegment(i);

				sili_hits.push_back(silihit);


//			}
//		}
	}



}

TVector3 TSiLi::GetPosition(int seg)	{
	TVector3 position;
	position.SetXYZ(0,0,-1);
	return position;
}
