

#include "TCrystalData.h"


ClassImp(TCrystalData)

TCrystalData::TCrystalData()	{	}

TCrystalData::~TCrystalData()	{	}


void TCrystalData::ClearData()	{
	fCrystal_Nbr			=	0;
	fCrystal_Eng			=	0;
	fCrystal_TimeCFD	=	0;
	fCrystal_TimeLED	=	0;
	fCrystal_Time			=	0;

	fSegment_Nbr.clear();	
	fSegment_Eng.clear();
	fSegment_TimeCFD.clear();
	fSegment_TimeLED.clear();
	fSegment_Time.clear();
}

void TCrystalData::Print()	{	}
