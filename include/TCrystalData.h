#ifndef TCRYSTALDATA_H
#define TCRYSTALDATA_H

#include <stdlib.h>
#include <stdio.h>
#include <vector>

#include "Globals.h"

#include "TNamed.h"

class TCrystalData		{

	private:
		UShort_t fCrystal_Nbr;
		Double_t fCrystal_Eng;
		Double_t fCrystal_TimeCFD;
		Double_t fCrystal_TimeLED;
		Double_t fCrystal_Time;
		std::vector<UShort_t> fSegment_Nbr;	
		std::vector<Double_t> fSegment_Eng;
		std::vector<Double_t> fSegment_TimeCFD;
		std::vector<Double_t> fSegment_TimeLED;
		std::vector<Double_t> fSegment_Time;

	public:
		TCrystalData();
		~TCrystalData();
		
		void ClearData();
		void Print();

		inline void SetCrystalNumber(const UShort_t &CrystalNumber)		{fCrystal_Nbr = CrystalNumber;};
		inline void SetCrystalEnergy(const Double_t &CrystalEnergy)		{fCrystal_Eng = CrystalEnergy;};		
		inline void SetCrystalTimeCFD(const Double_t &CrystalTimeCFD)	{fCrystal_TimeCFD = CrystalTimeCFD;};		
		inline void SetCrystalTimeLED(const Double_t &CrystalTimeLED)	{fCrystal_TimeLED = CrystalTimeLED;};		
		inline void SetCrystalTime(const Double_t &CrystalTime)				{fCrystal_Time = CrystalTime;};		
	
		inline void SetCore(const Double_t &CrystalEnergy,const Double_t &CrystalTimeCFD,const Double_t &CrystalTimeLED,const Double_t &CrystalTime)	{
			SetCrystalEnergy(CrystalEnergy);		
			SetCrystalTimeCFD(CrystalTimeCFD);		
			SetCrystalTimeLED(CrystalTimeLED);		
			SetCrystalTime(CrystalTime);		
		}
		
		inline void SetSegmentNumber(const UShort_t &SegmentNumber)		{fSegment_Nbr.push_back(SegmentNumber);};
		inline void SetSegmentEnergy(const Double_t &SegmentEnergy)		{fSegment_Eng.push_back(SegmentEnergy);};
		inline void SetSegmentTimeCFD(const Double_t &SegmentTimeCFD)	{fSegment_TimeCFD.push_back(SegmentTimeCFD);};
		inline void SetSegmentTimeLED(const Double_t &SegmentTimeLED)	{fSegment_TimeLED.push_back(SegmentTimeLED);};
		inline void SetSegmentTime(const Double_t &SegmentTime)				{fSegment_Time.push_back(SegmentTime);};

		inline void SetSegment(const UShort_t &SegmentNumber,const Double_t &SegmentEnergy,const Double_t &SegmentTimeCFD,const Double_t &SegmentTimeLED,const Double_t &SegmentTime)	{
			SetSegmentNumber(SegmentNumber);
			SetSegmentEnergy(SegmentEnergy);
			SetSegmentTimeCFD(SegmentTimeCFD);
			SetSegmentTimeLED(SegmentTimeLED);
			SetSegmentTime(SegmentTime);
		}

		inline UShort_t GetCrystalNumber()	{return fCrystal_Nbr;};
		inline Double_t GetCoreEnergy()	{return fCrystal_Eng;};
		inline Double_t GetCoreTimeCFD()	{return fCrystal_TimeCFD;};
		inline Double_t GetCoreTimeLED()	{return fCrystal_TimeLED;};		
		inline Double_t GetCoreTime()	{return fCrystal_Time;};		
		
		inline UShort_t GetSegmentNumber(const unsigned int &i)	{return fSegment_Nbr[i];};
		inline Double_t GetSegmentEnergy(const unsigned int &i)	{return fSegment_Eng[i];};
		inline Double_t GetSegmentTimeCFD(const unsigned int &i)	{return fSegment_TimeCFD[i];};
		inline Double_t GetSegmentTimeLED(const unsigned int &i)	{return fSegment_TimeLED[i];};
		inline Double_t GetSegmentTime(const unsigned int &i)	{return fSegment_Time[i];};
	
		inline unsigned int GetSegmentMultiplicity()	{	return fSegment_Nbr.size();	};
		
		ClassDef(TCrystalData,1)  // TCloverData structure
};


#endif





