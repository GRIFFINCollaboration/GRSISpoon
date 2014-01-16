#ifndef TCLOVERDATA_H
#define TCLOVERDATA_H


#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "Globals.h"

#include "TNamed.h"

#include "TCrystalData.h"

class TCloverData 	{

	private:
	  std::vector<UShort_t> 		fTIG_Ge_CloverNbr;
		std::vector<TCrystalData>	fTIG_Crystal;

	  std::vector<UShort_t> fTIG_BGO_CloverNbr;
	  std::vector<UShort_t> fTIG_BGO_CrystalNbr;
	  std::vector<UShort_t> fTIG_BGO_PmNbr;
	  std::vector<Double_t> fTIG_BGO_Energy;
	  std::vector<Double_t> fTIG_BGO_TimeCFD;
	  std::vector<Double_t> fTIG_BGO_TimeLED;
	  std::vector<Double_t> fTIG_BGO_Time;

	public:
  	TCloverData();
  	virtual ~TCloverData();

  void ClearData();
  void Print();
  
  /////////////////////           SETTERS           ////////////////////////
  inline void SetGeCloverNbr(const UShort_t &GeCloverNbr)			{fTIG_Ge_CloverNbr.push_back(GeCloverNbr); }

  //inline void SetGeCrystalNbr(const UShort_t &GeCrystalNbr);		
  //inline void SetGeSegmentNbr(const UShort_t &GeSegmentNbr)		{fTIG_Ge_SegmentNbr.push_back(GeSegmentNbr);}
  //inline void SetGeMidasId(const UInt_t &GeMidasId)						{fTIG_Ge_MidasId.push_back(GeMidasId);}
  //inline void SetGeEnergy(const Double_t &GeEnergy)						{fTIG_Ge_Energy.push_back(GeEnergy);}
  //inline void SetGeTimeCFD(const Double_t &GeTimeCFD)					{fTIG_Ge_TimeCFD.push_back(GeTimeCFD);}
  //inline void SetGeTimeLED(const Double_t &GeTimeLED)					{fTIG_Ge_TimeLED.push_back(GeTimeLED);}
	//inline void SetGeTime(const Double_t &GeTime)								{fTIG_Ge_Time.push_back(GeTime);}

	void SetGe(const UShort_t &GeCloverNbr,const UShort_t &GeCrystalNbr, const UShort_t &GeSegmentNbr, const Double_t &GeEnergy, const Double_t &GeTimeCFD, const Double_t &GeTimeLED, const Double_t &GeTime = 0);




  inline void SetBGOCloverNbr(const UShort_t &BGOCloverNbr)		{fTIG_BGO_CloverNbr.push_back(BGOCloverNbr); }
  inline void SetBGOCrystalNbr(const UShort_t &BGOCrystalNbr)	{fTIG_BGO_CrystalNbr.push_back(BGOCrystalNbr);}
  inline void SetBGOPmNbr(const UShort_t &BGOPmNbr)						{fTIG_BGO_PmNbr.push_back(BGOPmNbr);}
  inline void SetBGOEnergy(const Double_t &BGOEnergy)					{fTIG_BGO_Energy.push_back(BGOEnergy);}
  inline void SetBGOTimeCFD(const Double_t &BGOTimeCFD)				{fTIG_BGO_TimeCFD.push_back(BGOTimeCFD);}
  inline void SetBGOTimeLED(const Double_t &BGOTimeLED)				{fTIG_BGO_TimeLED.push_back(BGOTimeLED);}
	inline void SetBGOTime(const Double_t &BGOTime)							{fTIG_BGO_Time.push_back(BGOTime);}

	inline void SetBGO(const UShort_t &BGOCloverNbr,const UShort_t &BGOCrystalNbr, const UShort_t &BGOPmNbr, const Double_t &BGOEnergy, const Double_t &BGOTimeCFD, const Double_t &BGOTimeLED, const Double_t &BGOTime = 0)	{
		SetBGOCloverNbr(BGOCloverNbr);
		SetBGOCrystalNbr(BGOCrystalNbr);
		SetBGOPmNbr(BGOPmNbr);
		SetBGOEnergy(BGOEnergy);
		SetBGOTimeCFD(BGOTimeCFD);
		SetBGOTimeLED(BGOTimeLED);
		SetBGOTime(BGOTime);
	};

  /////////////////////           GETTERS           ////////////////////////
  inline UShort_t GetGeCloverNbr(const unsigned int &i)   {return fTIG_Ge_CloverNbr[i]; }
  inline TCrystalData GetGeCrystal(const unsigned int &i)  {return fTIG_Crystal[i]; }
  inline UShort_t GetBGOCloverNbr(const unsigned int &i)   {return fTIG_BGO_CloverNbr[i]; }
  inline UShort_t GetBGOCrystalNbr(const unsigned int &i)  {return fTIG_BGO_CrystalNbr[i]; }
  inline UShort_t GetBGOPmNbr(const unsigned int &i)       {return fTIG_BGO_PmNbr[i]; }
  inline Double_t GetBGOEnergy(const unsigned int &i)      {return fTIG_BGO_Energy[i];}
  inline Double_t GetBGOTimeCFD(const unsigned int &i)     {return fTIG_BGO_TimeCFD[i];}
  inline Double_t GetBGOTimeLED(const unsigned int &i)     {return fTIG_BGO_TimeLED[i];}
  inline Double_t GetBGOTime(const unsigned int &i)     {return fTIG_BGO_Time[i];}

  inline unsigned int GetMultiplicityGe()  {return fTIG_Ge_CloverNbr.size();}
  inline unsigned int GetMultiplicityBGO()  {return fTIG_BGO_CloverNbr.size();}
  
  ClassDef(TCloverData,1)  // TCloverData structure
};









#endif








