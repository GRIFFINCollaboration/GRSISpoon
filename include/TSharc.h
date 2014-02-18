#ifndef TSHARC_H
#define TSHARC_H


#include <vector>
#include <cstdio>

#include "TSharcData.h"
#include "TSharcHit.h"

#include <TVector3.h>
#include <TObject.h>
#include <TNamed.h>

#include "Globals.h"


class TSharc : public TSharcData, public TNamed 	{
	public:
		TSharc();
		~TSharc();

	public: 
		virtual void Clear(Option_t * = "");		//!
		virtual void Print(Option_t * = "");		//!
		void BuildHits();			//!

		TSharcHit *GetHit(int i)		{return &sharc_hits.at(i);}	//->
		Short_t GetMultiplicity()	{return sharc_hits.size();}	//->

		TVector3 GetPosition(TSharcHit*);
		double GetDeadLayer(TSharcHit*);

		static TVector3 GetPosition(int detector, int frontstrip, int backstrip);	//!
		static double   GetDeadLayer(int detector, int frontstrip, int backstrip);	//!

//	public:

//		virtual inline void SetFront(const UShort_t &DetNbr,const UShort_t &StripNbr,const Double_t &Energy ,const Double_t &TimeCFD,const Double_t &TimeLED,const Double_t &Time = 0, const UInt_t &Charge = 0)
//		virtual inline void SetBack( const UShort_t &DetNbr,const UShort_t &StripNbr,const Double_t &Energy, const Double_t &TimeCFD,const Double_t &TimeLED,const Double_t &Time = 0, const UInt_t &Charge = 0)
//		virtual inline void SetPAD(  const UShort_t &DetNbr,const Double_t &Energy,  const Double_t &TimeCFD,const Double_t &TimeLED,const Double_t &Time = 0, const Int_t &Charge = 0)


		


	private: 
		std::vector <TSharcHit> sharc_hits;

        
   ClassDef(TSharc,2)  // Sharc Analysis structure
};







#endif
