



#include <cstdio>
#include <fstream>
#include <string>


#include <TS3Data.h>



ClassImp(TS3Data)

TS3Data::TS3Data()	{	}

TS3Data::~TS3Data()	{	}
		 
void TS3Data::ClearData()	{

	fS3_RingDetectorNumber.clear();
	fS3_RingNumber.clear();
	fS3_RingCharge.clear();
	fS3_RingEnergy.clear();
	fS3_RingCFD.clear(); 
	fS3_RingLED.clear();
	fS3_RingTIME.clear();

	fS3_SectorDetectorNumber.clear();
	fS3_SectorNumber.clear();
	fS3_SectorCharge.clear();
	fS3_SectorEnergy.clear();
	fS3_SectorCFD.clear(); 
	fS3_SectorLED.clear();

}


void TS3Data::Print()	{
	printf("==============================\n");
	printf("this has not yet been written.\n");
	printf("==============================\n");
}
