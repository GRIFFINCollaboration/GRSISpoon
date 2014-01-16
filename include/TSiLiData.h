#ifndef __SiLiDATA__
#define __SiLiDATA__



#include <vector>


#include "TObject.h"


class TSiLiData : public TObject {

	private:
		std::vector<UShort_t> fSiLiSegment;
		std::vector<UInt_t>		fSiLiCharge;
		std::vector<Double_t>	fSiLiEnergy;
		std::vector<Double_t> fSiLiCFD; 
		std::vector<Double_t> fSiLiLED;
		std::vector<Double_t> fSiLiTIME;
   
   
 public:
		TSiLiData();
		~TSiLiData();

   void   Clear(); //!
   void		Print(); //!

		inline void SetSegment(UShort_t &fSeg)		{	fSiLiSegment.push_back(fSeg);	} //!
		inline void SetCharge(UInt_t &fCharge)		{	fSiLiCharge.push_back(fCharge);	} 	//!
		inline void SetEnergy(Double_t &fEnergy)	{	fSiLiEnergy.push_back(fEnergy);	}		//!
		inline void SetCFD(Double_t &fCFD)				{	fSiLiCFD.push_back(fCFD);	}	//!
		inline void SetLED(Double_t &fLED)				{	fSiLiLED.push_back(fLED);	}	//!
		inline void SetTime(Double_t &fTime)			{	fSiLiTIME.push_back(fTime);	}	//!
				

		inline void SetSiLi(UShort_t fSeg,Double_t fEnergy,Double_t fCFD,Double_t fLED,Double_t fTime=0.0,UInt_t fCharge=0.0)	{
			SetSegment(fSeg);	
			SetCharge(fCharge);	
			SetEnergy(fEnergy);	
			SetCFD(fCFD);		
			SetLED(fLED);		
			SetTime(fTime);		
		}

		inline UInt_t	GetMultiplicity()	{return	fSiLiSegment.size();	}

		inline UShort_t GetSegment(UInt_t &i)	{	return fSiLiSegment.at(i);	}	//!
		inline UInt_t 	GetCharge(UInt_t &i)				{	return fSiLiCharge.at(i);	}		//!
		inline Double_t GetEnergy(UInt_t &i)				{	return fSiLiEnergy.at(i);	}		//!
		inline Double_t GetCFD(UInt_t &i)						{	return fSiLiCFD.at(i);	}	//!
		inline Double_t GetLED(UInt_t &i)						{	return fSiLiLED.at(i);	}	//!
		inline Double_t GetTime(UInt_t &i)					{	return fSiLiTIME.at(i);	}	//!




    
   ClassDef(TSiLiData,1)  // SiLiData structure
};

#endif
