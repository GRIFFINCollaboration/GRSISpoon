#ifndef TS3DATA_H
#define TS3DAtA_H

#include <cstdlib>
#include <vector>
#include <map>

#include "Rtypes.h"

class TS3Data	{

	private:
		std::vector<UShort_t> fS3_RingDetectorNumber;
		std::vector<UShort_t>	fS3_RingNumber;
		std::vector<UInt_t>		fS3_RingCharge;
		std::vector<Double_t>	fS3_RingEnergy;
		std::vector<Double_t> fS3_RingCFD; 
		std::vector<Double_t> fS3_RingLED;
		std::vector<Double_t> fS3_RingTIME;

		std::vector<UShort_t> fS3_SectorDetectorNumber;
		std::vector<UShort_t>	fS3_SectorNumber;
		std::vector<UInt_t>		fS3_SectorCharge;
		std::vector<Double_t>	fS3_SectorEnergy;
		std::vector<Double_t> fS3_SectorCFD; 
		std::vector<Double_t> fS3_SectorLED;
		std::vector<Double_t> fS3_SectorTIME;

	public:
		TS3Data();
		~TS3Data();

		void ClearData();
		void Print();


		inline void SetRing_DetectorNumber(const UShort_t &DetNbr){fS3_RingDetectorNumber.push_back(DetNbr);}//!
		inline void SetRing_Number(const UShort_t &RingNbr){fS3_RingNumber.push_back(RingNbr);}//!
		inline void SetRing_Energy(const Double_t &Energy){fS3_RingEnergy.push_back(Energy);}//!
		inline void SetRing_Charge(const UInt_t &Charge){fS3_RingCharge.push_back(Charge);}//!
		inline void SetRing_CFD(const Double_t &TimeCFD){fS3_RingCFD.push_back(TimeCFD);}//!
		inline void SetRing_LED(const Double_t &TimeLED){fS3_RingLED.push_back(TimeLED);}//!
		inline void SetRing_Time(const Double_t &Time){fS3_RingTIME.push_back(Time);}//!


		inline void SetSector_DetectorNumber(const UShort_t &DetNbr){fS3_SectorDetectorNumber.push_back(DetNbr);}//!
		inline void SetSector_Number(const UShort_t &SectorNbr){fS3_SectorNumber.push_back(SectorNbr);}//!
		inline void SetSector_Energy(const Double_t &Energy){fS3_SectorEnergy.push_back(Energy);}//!
		inline void SetSector_Charge(const UInt_t &Charge){fS3_SectorCharge.push_back(Charge);}//!
		inline void SetSector_CFD(const Double_t &TimeCFD){fS3_SectorCFD.push_back(TimeCFD);}//!
		inline void SetSector_LED(const Double_t &TimeLED){fS3_SectorLED.push_back(TimeLED);}//!
		inline void SetSector_Time(const Double_t &Time){fS3_SectorTIME.push_back(Time);}//!


		inline void SetRing(const UShort_t &DetNbr,const UShort_t &RingNbr,const Double_t &Energy ,const Double_t &CFD,const Double_t &LED,const Double_t &Time = 0, const UInt_t &Charge = 0)	{
			SetRing_DetectorNumber(DetNbr);
			SetRing_Number(RingNbr);
			SetRing_Energy(Energy);
			SetRing_Charge(Charge);
			SetRing_CFD(CFD);
			SetRing_LED(LED);
			SetRing_Time(Time);
		} //!

		inline void SetSector(const UShort_t &DetNbr,const UShort_t &SectorNbr,const Double_t &Energy ,const Double_t &CFD,const Double_t &LED,const Double_t &Time = 0, const UInt_t &Charge = 0)	{
			SetSector_DetectorNumber(DetNbr);
			SetSector_Number(SectorNbr);
			SetSector_Energy(Energy);
			SetSector_Charge(Charge);
			SetSector_CFD(CFD);
			SetSector_LED(LED);
			SetSector_Time(Time);
		} //!


		inline Int_t GetRingMultiplicity()	{return fS3_RingNumber.size();}

		inline UShort_t GetRing_DetectorNumber(const unsigned int &i)	{return fS3_RingDetectorNumber.at(i);}//!
		inline UShort_t GetRing_Number(const unsigned int &i)					{return fS3_RingNumber.at(i);}//!
		inline Double_t GetRing_Energy(const unsigned int &i)					{return fS3_RingEnergy.at(i);}//!
		inline UInt_t		GetRing_Charge(const unsigned int &i)					{return fS3_RingCharge.at(i);}//!
		inline Double_t GetRing_CFD(const unsigned int &i)				{return fS3_RingCFD.at(i);}//!
		inline Double_t GetRing_LED(const unsigned int &i)				{return fS3_RingLED.at(i);}//!
		inline Double_t GetRing_Time(const unsigned int &i)						{return fS3_RingTIME.at(i);}//!

		inline Int_t GetSectorMultiplicity()	{return fS3_SectorNumber.size();}

		inline UShort_t GetSector_DetectorNumber(const unsigned int &i)	{return fS3_SectorDetectorNumber.at(i);}//!
		inline UShort_t GetSector_Number(const unsigned int &i)					{return fS3_SectorNumber.at(i);}//!
		inline Double_t GetSector_Energy(const unsigned int &i)					{return fS3_SectorEnergy.at(i);}//!
		inline UInt_t		GetSector_Charge(const unsigned int &i)					{return fS3_SectorCharge.at(i);}//!
		inline Double_t GetSector_CFD(const unsigned int &i)				{return fS3_SectorCFD.at(i);}//!
		inline Double_t GetSector_LED(const unsigned int &i)				{return fS3_SectorLED.at(i);}//!
		inline Double_t GetSector_Time(const unsigned int &i)						{return fS3_SectorTIME.at(i);}//!





	ClassDef(TS3Data,1)


};


#endif
