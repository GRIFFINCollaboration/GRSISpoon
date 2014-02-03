#ifndef TCHANNEL_H
#define TCHANNEL_H

#include<string>
#include<cmath>
#include<utility>

#include<TNamed.h>
#include<TRandom.h>

#include<TTigFragment.h>
#include<Globals.h>

class TChannel : public TNamed	{

  public:
    TChannel();
    ~TChannel(); 
	
	private:
	public:
		unsigned int	fspc;
		unsigned char	type;
		int				integration;
		int 			number;
		int 			nbins;
		int 			nsamp;
		int 			maxchg;
		float 			maxeng;

		int				stream;

		int detector;
		std::pair<int,int> pixel;

		std::vector<double> ENGCoefficients;
		std::vector<double> CFDCoefficients;
		std::vector<double> LEDCoefficients;
		std::vector<double> TIMECoefficients;

		std::string	name;
		std::string	type_title;
		std::string	type_name;
		std::string	type_units;
	  
	public:

		void SetChannel(int tfspc, 
		int tnumber = 0, 
		std::string tname = "");

		void SetTypeInfo(char ttype, 
						 std::string type_name   = "",
						 std::string ttype_title = "",
						 std::string ttype_units = "",
						 int tnbins    = 0, 
						 int tnsamp    = 0, 
						 int tmaxchg   = 0, 
						 float tmaxeng = 0);

		void SetAddress(int &tmpadd) 			{fspc = tmpadd;};
		void SetName(std::string &tmpname)		{name = tmpname;}; 
		void SetDetector(int &tmpdet)			{detector = tmpdet;}; 
		void SetPixel(int &tmp1, int &tmp2)		{pixel = std::make_pair(tmp1,tmp2);};
		void SetNumber(int &tmpnum)				{number = tmpnum;};
		void SetStream(int &tmpstream)			{type = tmpstream;};


		int	GetNumber()		 	{ return number; };
		int	GetFSCP() 			{ return fspc; };
		std::string GetName()	{ return name;	 };
		//write the rest of the gettters/setters...

		void AddENGCoefficient(double temp)  { ENGCoefficients.push_back(temp); };
		void AddCFDCoefficient(double temp)  { CFDCoefficients.push_back(temp); };
		void AddLEDCoefficient(double temp)  { LEDCoefficients.push_back(temp); };
 		void AddTIMECoefficient(double temp) { TIMECoefficients.push_back(temp); };
	  
		void CalibrateFragment(TTigFragment*);

		double CalibrateENG(double);
		double CalibrateENG(int);
		double CalibrateCFD(double);
		double CalibrateCFD(int);
		double CalibrateLED(double);
		double CalibrateLED(int);
		double CalibrateTIME(double);
		double CalibrateTIME(int);


		void DestroyCalibrations();

		void DestroyENGCal();
		void DestroyCFDCal();
		void DestroyLEDCal();
		void DestroyTIMECal();

		void Print();
		void PrintFormatted();
		void Clear();
      
	  ClassDef(TChannel,1)
};
#endif






