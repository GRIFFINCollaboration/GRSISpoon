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
		double 			front_cfd;		//	

		int				back_strip;		//
		unsigned int	back_charge;	//
		double			back_cfd;		// 		

		unsigned int	pad_charge;		//

	  	double d_energy;				//		
  		double d_time;					//		
	  	double d_cfd;					//		

  		double p_energy;	//			pad only;
 		double p_time;		//			pad only;
 		double p_cfd;		//

		int detectornumber;	//

		TVector3 position;  //

	public:

		virtual void Clear(Option_t* = "");	//!
		virtual void Print(Option_t* = "");	//!

		static bool Compare(TSharcHit *lhs,TSharcHit *rhs);

		Double_t GetDeltaE()	{	return d_energy;	};	//!
		Double_t GetDeltaT()	{	return d_time;		};	//!
		
		Double_t GetPadE()		{	return p_energy;	};	//!
		Double_t GetPadT()		{	return p_time;		};	//!

		int GetDetectorNumber()			{ return detectornumber;	} //!
		std::pair<int,int>	GetPixel()	{ return std::make_pair(front_strip,back_strip);	}	//!

		unsigned int GetFrontCharge() 	{	return	front_charge;	}	//!
		unsigned int GetBackCharge()	{	return	back_charge;	}	//!
		unsigned int GetPadCharge()		{	return	pad_charge;		}	//!
		
		unsigned int GetFrontStrip()	{	return	front_strip;	}	//!
		unsigned int GetBackStrip()		{	return	back_strip;		}	//!
			
		double GetFrontCFD()	{	return front_cfd;	}	//!
		double GetBackCFD()		{	return back_cfd;	}	//!

		TVector3 GetPosition()	{	return position;	}	//!

		void SetDeltaE(const double &energy)	{	d_energy = energy;	}	//!
		void SetDeltaT(const double &time)		{	d_time = time;	}		//!
		void SetPadE(const double &energy)		{	p_energy = energy;	}	//!
		void SetPadT(const double &time)		{	p_time = time;	}		//!

		void SetFrontCFD(const double &cfd)		{	front_cfd = cfd;	} //!
		void SetBackCFD(const double &cfd)		{	back_cfd = cfd;		} //!

		void SetPosition(const TVector3 &pos)	{	position = pos;		} //!

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
