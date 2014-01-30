

#include "TCloverData.h"

ClassImp(TCloverData)

TCloverData::TCloverData()	{	}

TCloverData::~TCloverData()	{	}


void TCloverData::ClearData()	{
  fTIG_Ge_CloverNbr.clear();
  fTIG_Crystal.clear();

  fTIG_BGO_CloverNbr.clear();
  fTIG_BGO_CrystalNbr.clear();
  fTIG_BGO_PmNbr.clear();
  fTIG_BGO_Energy.clear();
  fTIG_BGO_TimeCFD.clear();
  fTIG_BGO_TimeLED.clear();
  fTIG_BGO_Time.clear();
}


void TCloverData::Print()	{	}


void TCloverData::SetGe(const UShort_t &GeCloverNbr,const UShort_t &GeCrystalNbr, const UShort_t &GeSegmentNbr, const Double_t &GeEnergy, const Double_t &GeTimeCFD, const Double_t &GeTimeLED, const Double_t &GeTime )	{
	if(GeEnergy < 10)
		return;
	//printf("GeCloverNbr: %i\tGeCrystalNbr: %i\tGeSegmentNbr: %i\tGeEnergy: %f\tGeTimeCFD: %f\tGeTimeLED: %f\tGeTime: %f\n",GeCloverNbr,GeCrystalNbr, GeSegmentNbr, GeEnergy, GeTimeCFD, GeTimeLED, GeTime);
	bool found = false;
	for(int i=0;i<fTIG_Ge_CloverNbr.size();i++)	{
		if(GeCloverNbr == fTIG_Ge_CloverNbr[i])	{
			if(GeCrystalNbr == fTIG_Crystal[i].GetCrystalNumber())	{
				if(GeSegmentNbr	==	0)	{
					fTIG_Crystal[i].SetCore(GeEnergy,GeTimeCFD,GeTimeLED,GeTime);
				}	
				else{
					fTIG_Crystal[i].SetSegment(GeSegmentNbr,GeEnergy,GeTimeCFD,GeTimeLED,GeTime);
				}
				found = true;
			 //printf("added to %i GeCloverNbr: %i\n",i,fTIG_Crystal[i].GetCrystalNumber());
				break;
			}
		}
	}
	if(found)
		return;
	SetGeCloverNbr(GeCloverNbr);
	TCrystalData cry_data;	
	cry_data.SetCrystalNumber(GeCrystalNbr);
	if(GeSegmentNbr	==	0)	{
		cry_data.SetCore(GeEnergy,GeTimeCFD,GeTimeLED,GeTime);
	}	
	else{
		cry_data.SetSegment(GeSegmentNbr,GeEnergy,GeTimeCFD,GeTimeLED,GeTime);
	}
	fTIG_Crystal.push_back(cry_data);
	//printf("new one GeCloverNbr: %i\n",fTIG_Crystal.back().GetCrystalNumber());
};

