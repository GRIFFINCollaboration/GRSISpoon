

#include "TCrystalData.h"


ClassImp(TCrystalData)

TCrystalData::TCrystalData()	{	
	Clear();
}

TCrystalData::~TCrystalData()	{	}


void TCrystalData::Clear(Option_t *opt)	{

	fClover_Nbr.clear();
	fCore_Nbr.clear();
	fCore_Eng.clear();
	fCore_Chg.clear();
	fCore_TimeCFD.clear();
	fCore_TimeLED.clear();
	fCore_Time.clear();

	for(int x=0;x<fCore_Wave.size();x++)	{
		fCore_Wave[x].clear();
	}
	fCore_Wave.clear();

	fSeg_Clover_Nbr.clear();
	fSeg_Core_Nbr.clear();
	fSegment_Nbr.clear();	
	fSegment_Eng.clear();
	fSegment_TimeCFD.clear();
	fSegment_TimeLED.clear();
	fSegment_Time.clear();

	for(int x=0;x<fSegment_Wave.size();x++)	{
		fSegment_Wave[x].clear();	
	}
	fSegment_Wave.clear();
}

void TCrystalData::Print(Option_t *opt)	{
	// not yet written.
	printf("not yet written.\n");
}


