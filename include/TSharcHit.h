#ifndef TSHARCHIT_H
#define TSHARCHIT_H

#include <stdio.h>
#include <utility>

#include "TVector3.h" 
#include "TObject.h" 

class TSharcHit : public TObject 	{
	public:
		TSharcHit();
		~TSharcHit();

	private:

		int				front_strip;	//
		unsigned int	front_charge;	//	
		int				back_strip;		//
		unsigned int	back_charge;	//

		unsigned int	pad_charge;		//

	  	double d_energy;				//		
  		double d_time;					//		
	  	double d_cfd;					//		

  		double p_energy;	//			pad only;
 		double p_time;		//			pad only;
 		double p_cfd;		//

		int detectornumber;	//

	public:

		void Clear(Option_t* = "");	//!
		void Print(Option_t* = "");	//!

		Double_t GetDeltaE()	{	return d_energy;	};	//!
		Double_t GetDeltaT()	{	return d_time;		};	//!
		
		Double_t GetPadE()		{	return p_energy;	};	//!
		Double_t GetPadT()		{	return p_time;		};	//!

		int GetDetectorNumber()			{ return detectornumber;	} //!
		std::pair<int,int>	GetPixel()	{ return std::make_pair(front_strip,back_strip);	}	//!

		unsigned int GetFrontCharge() 	{	return	front_charge;	}	//!
		unsigned int GetBackCharge()	{	return	back_charge;	}	//!
		unsigned int GetPadCharge()		{	return	pad_charge;		}	//!
					

		void SetDeltaE(const double &energy)	{	d_energy = energy;	}	//!
		void SetDeltaT(const double &time)		{	d_time = time;	}		//!
		void SetPadE(const double &energy)		{	p_energy = energy;	}	//!
		void SetPadT(const double &time)		{	p_time = time;	}		//!

		void SetPixel(const int &front, const  int &back)	{front_strip = front; back_strip = back;}	//!
		void SetDetector(const int &detector)	{	detectornumber = detector;	}						//!
	
		void SetFrontCharge(const unsigned int &charge)	{ front_charge = charge;}	//!
		void SetBackCharge(const unsigned int &charge)	{ back_charge = charge;}	//!
		void SetPadCharge(const unsigned int &charge)	{ pad_charge = charge;}		//!

		//void SetFrontWave(std::vector<int> &wave)	{ front_strip_wave = wave;	} 
		//void SetBackWave(std::vector<int> &wave)	{ back_strip_wave = wave;	} 
		//void SetPadWave(std::vector<int> &wave)	{ pad_wave = wave;	} 


		
	ClassDef(TSharcHit,1)
};




#endif
