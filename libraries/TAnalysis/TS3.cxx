

#include "TS3.h"

#include <TMath.h>
#include <cmath>

ClassImp(TS3)


TS3::TS3()	{

	ring_number=24;
	sector_number=32;

	offset_phi=15*TMath::Pi()/180.; // according to dave.
	outer_diameter=70.;
	inner_diameter=22.;
	target_distance=21.;
}

TS3::~TS3()	{	}


void TS3::BuildHits()	{

	S3Hit s3hit;

	for(int i=0;i<GetRingMultiplicity();i++)     { 
		for(int j=0;j<GetSectorMultiplicity();j++)    { 
			if(GetRing_DetectorNumber(i) == GetSector_DetectorNumber(j))     {

				s3hit.pixel		= std::make_pair(i,j);
				s3hit.energy	=	GetRing_Energy(i);
				s3hit.charge	=	GetRing_Charge(i);
				s3hit.time		=	GetRing_Time(i);
				s3hit.cfd			=	GetRing_CFD(i);
				s3hit.detectornumber	=	GetRing_DetectorNumber(i);

				s3_hits.push_back(s3hit);

			}
		}
	}

}

TVector3 TS3::GetPosition(int ring, int sector)	{

	TVector3 position;

	double ring_width=(outer_diameter-inner_diameter)*0.5/ring_number; // 24 rings   radial width!
	double inner_radius=inner_diameter/2.0;

	
	double correctedsector = 6+sector; //moe is currently checking.

	double phi 		=	2.*TMath::Pi()/sector_number * (correctedsector + 0.5);   //the phi angle....
	double radius =	inner_radius + ring_width * (ring + 0.5) ;
	
	position.SetMagThetaPhi(sqrt(radius*radius + target_distance*target_distance),atan((radius/target_distance)),phi+offset_phi);


	return position;


}




void TS3::Clear()    {

  ClearData();
  s3_hits.clear();

}


