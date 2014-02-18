#ifndef TBGODATA_H
#define TBGODATA_H


#include <cstdlib>
#include <cstdio>
#include <vector>

#include "Globals.h"
#include "TTigFragment.h"

//#include <TObject.h>


class TBGOData {

	private:

		std::vector<UShort_t> fBGO_CloverNbr;		//!
		std::vector<UShort_t> fBGO_CrystalNbr;		//!
		std::vector<UShort_t> fBGO_PmNbr;		//!
		std::vector<Int_t>    fBGO_Charge;		//!
		std::vector<Double_t> fBGO_Energy;		//!
		std::vector<Double_t> fBGO_TimeCFD;		//!
		std::vector<Double_t> fBGO_TimeLED;		//!
		std::vector<Double_t> fBGO_Time;		//!

		std::vector<std::vector<int> > fBGO_Wave;	//!

	public:
		TBGOData();					//!
		virtual ~TBGOData();				//!

 		virtual void Clear(Option_t *opt = "");		//!
		virtual void Print(Option_t *opt = "");		//!
  
		/////////////////////           SETTERS           ////////////////////////
		inline void SetBGOCloverNbr(const UShort_t &BGOClvNbr)		{fBGO_CloverNbr.push_back(BGOClvNbr);}  //!
		inline void SetBGOCrystalNbr(const UShort_t &BGOCryNbr)		{fBGO_CrystalNbr.push_back(BGOCryNbr);}	//!
		inline void SetBGOPmNbr(const UShort_t &BGOPmNbr)		{fBGO_PmNbr.push_back(BGOPmNbr);}	//!
		inline void SetBGOCharge(const Int_t &BGOCharge)		{fBGO_Charge.push_back(BGOCharge);}	//!	
		inline void SetBGOEnergy(const Double_t &BGOEnergy)		{fBGO_Energy.push_back(BGOEnergy);}	//!
		inline void SetBGOCFD(const Double_t &BGOTimeCFD)		{fBGO_TimeCFD.push_back(BGOTimeCFD);}	//!
		inline void SetBGOLED(const Double_t &BGOTimeLED)		{fBGO_TimeLED.push_back(BGOTimeLED);}	//!
		inline void SetBGOTime(const Double_t &BGOTime)			{fBGO_Time.push_back(BGOTime);}		//!

		inline void SetBGOWave(const std::vector<int> &BGOWave)		{fBGO_Wave.push_back(BGOWave);}		//!

		inline void SetBGO(const UShort_t &BGOCloverNbr, const UShort_t &BGOCrystalNbr, const UShort_t &BGOPmNbr, const Int_t &BGOCharge, const Double_t &BGOEnergy, const Double_t &BGOTimeCFD, const Double_t &BGOTimeLED, const Double_t &BGOTime = 0)	{
			SetBGOCloverNbr(BGOCloverNbr);
			SetBGOCrystalNbr(BGOCrystalNbr);
			SetBGOPmNbr(BGOPmNbr);
			SetBGOCharge(BGOCharge);
			SetBGOEnergy(BGOEnergy);
			SetBGOCFD(BGOTimeCFD);
			SetBGOLED(BGOTimeLED);
			SetBGOTime(BGOTime);
		};	//!
		inline void SetBGO(TTigFragment *frag,const UShort_t &BGOCloverNbr ,const UShort_t &BGOCrystalNbr, const UShort_t &BGOPmNbr )	{
			SetBGOCloverNbr(BGOCloverNbr);
			SetBGOCrystalNbr(BGOCrystalNbr);
			SetBGOPmNbr(BGOPmNbr);
			SetBGOCharge(frag->Charge);
			SetBGOEnergy(frag->ChargeCal);
			SetBGOCFD(frag->Cfd);
			SetBGOLED(frag->Led);
			SetBGOTime(frag->TimeToTrig);
		};	//! overload function added by sjc
		
		/////////////////////           GETTERS           ////////////////////////
        inline UShort_t GetBGOCloverNumber(const unsigned &i)       {return fBGO_CloverNbr.at(i);} //!
		inline UShort_t GetBGOCoreNumber(const unsigned &i)      {return fBGO_CrystalNbr.at(i);}//!
		inline UShort_t GetBGOPmNbr(const unsigned int &i)       {return fBGO_PmNbr.at(i); }	//!
		inline Int_t    GetBGOCharge(const unsigned int &i)      {return fBGO_Charge.at(i);}	//!		
		inline Double_t GetBGOEnergy(const unsigned int &i)      {return fBGO_Energy.at(i);}	//!
		inline Double_t GetBGOCFD(const unsigned int &i)     {return fBGO_TimeCFD.at(i);}	//!
		inline Double_t GetBGOLED(const unsigned int &i)     {return fBGO_TimeLED.at(i);}	//!
		inline Double_t GetBGOTime(const unsigned int &i)    	 {return fBGO_Time.at(i);}	//!

		inline std::vector<int> GetBGOWave(const unsigned int &i) {return fBGO_Wave.at(i);}	//!

		inline unsigned int GetBGOMultiplicity()  {return fBGO_PmNbr.size();}			//!

  ClassDef(TBGOData,0)  // TBgoData structure
};









#endif








