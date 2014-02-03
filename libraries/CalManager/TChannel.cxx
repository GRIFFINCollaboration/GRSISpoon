#include"TChannel.h"

ClassImp(TChannel)

TChannel::TChannel()	{
  Clear();
}

TChannel::~TChannel()	{	}

void TChannel::Clear(){  
	fspc				=	0xffffffff;
	type				=	0;
	integration			=	0;
	number				=	0;
	nbins				=	0;
	nsamp				=	0;
	maxchg				=	0;
	maxeng				=	0;
	detector		=	0;
	pixel				=	std::make_pair(0,0);


	name.clear();

	type_title.clear();
	type_name.clear();
	type_units.clear();

	ENGCoefficients.clear();
	CFDCoefficients.clear();
	LEDCoefficients.clear();
	TIMECoefficients.clear();
}

void TChannel::SetChannel(int tfspc, 
	int tnumber, 
	std::string tname)	{
	fspc		=	tfspc; 
	number		=	tnumber; 
	name		=	tname;								
}

void TChannel::SetTypeInfo(char ttype,
								 std::string	ttype_name,
								 std::string	ttype_title,
								 std::string	ttype_units,
								 int tnbins, 
								 int tnsamp, 
								 int tmaxchg, 
								 float tmaxeng)	{
								 
	type_name 	= ttype_name;
	type_title	=	ttype_title;
	type_units	=	ttype_units;
	nbins				=	tnbins;
	nsamp				=	tnsamp;
	maxchg			= tmaxchg;
	maxeng			=	tmaxeng;
	type_title	=	ttype_title;
	type_units	=	ttype_units;
	nbins				=	tnbins;
	nsamp				=	tnsamp;
	maxchg			=	tmaxchg; 
	maxeng			=	tmaxeng;
}




void TChannel::DestroyENGCal()	{
	ENGCoefficients.clear();
}

void TChannel::DestroyCFDCal()	{
	CFDCoefficients.clear();
}

void TChannel::DestroyLEDCal()	{
	LEDCoefficients.clear();
}

void TChannel::DestroyTIMECal()	{
	LEDCoefficients.clear();
}


void TChannel::DestroyCalibrations()	{
	DestroyENGCal();
	DestroyCFDCal();
	DestroyLEDCal();
	DestroyTIMECal();	
};







double TChannel::CalibrateENG(int charge)	{
	return CalibrateENG((double)charge + gRandom->Uniform());
};

double TChannel::CalibrateENG(double charge)	{
	if(ENGCoefficients.size()==0)
		return charge;
	
	double temp_int = 125.0;
	if(integration != 0)
		temp_int = integration/4;  //the 4 is the dis. 
	
	double cal_chg = 0.0;
	for(int i=0;i<ENGCoefficients.size();i++){
		cal_chg += ENGCoefficients[i] * pow((charge/temp_int),i);
	}
	return cal_chg;
};


double TChannel::CalibrateCFD(int cfd)	{
	return CalibrateCFD((double)cfd + gRandom->Uniform());
};

double TChannel::CalibrateCFD(double cfd)	{
	if(CFDCoefficients.size()==0)
		return cfd;
	
	double cal_cfd = 0.0;
	for(int i=0;i<CFDCoefficients.size();i++){
		cal_cfd += CFDCoefficients[i] * pow(cfd,i);
	}
	return cal_cfd;
};


double TChannel::CalibrateLED(int led)	{
	return CalibrateLED((double)led + gRandom->Uniform());
};

double TChannel::CalibrateLED(double led)	{
	if(LEDCoefficients.size()==0)
		return led;
	
	double cal_led = 0.0;
	for(int i=0;i<LEDCoefficients.size();i++){
		cal_led += LEDCoefficients[i] * pow(led,i);
	}
	return cal_led;
}


double TChannel::CalibrateTIME(int time)	{
	return CalibrateTIME((double)time + gRandom->Uniform());
};

double TChannel::CalibrateTIME(double time)	{
	if(TIMECoefficients.size()==0)
		return time;
	
	double cal_time = 0.0;
	for(int i=0;i<TIMECoefficients.size();i++){
		cal_time += TIMECoefficients[i] * pow(time,i);
	}
	return cal_time;
}




void TChannel::CalibrateFragment(TTigFragment *frag)	{
	
	frag->ChannelNumber = number;
	frag->ChannelName	=	name;
	
	frag->ChargeCal = (float) CalibrateENG(frag->Charge);
	
}


void TChannel::Print()	{
	printf( "Channel: %i\t\t" DBLUE "%s" RESET_COLOR "\n",number, name.c_str());
	printf( "Address: " DMAGENTA "0x%08x" RESET_COLOR "\n", fspc);
	printf( "Energy Coefficients{%i}:\n", ENGCoefficients.size() );
	printf( "\t");
	for(int x=0;x<ENGCoefficients.size();x++)
		printf( DRED "E[%i]: %f  " RESET_COLOR, x, ENGCoefficients[x] );
	printf( "\n====================================\n");
};


void TChannel::PrintFormatted()	{
	//This function is designed to output the 
	//info stored in the Channel to std out such
	//that it matches the format of a .cal file.
	printf("%s\t{\n",name.c_str());
	printf("\tADDRESS:     \t0x%08x\n",fspc);
	printf("\tNAME:        \t%s\n",name.c_str());	
	printf("\tNUMBER:      \t%i\n",number);
	printf("\tCOEFFICIENTS:\t"); for(int x=0;x<ENGCoefficients.size();x++) {ENGCoefficients.at(x);} printf("\n");
    printf("\tENG_COEFF:   \t"); for(int x=0;x<ENGCoefficients.size();x++) {ENGCoefficients.at(x);} printf("\n");
    printf("\tCFD_COEFF:   \t"); for(int x=0;x<CFDCoefficients.size();x++) {CFDCoefficients.at(x);} printf("\n");
    printf("\tLED_COEFF:   \t"); for(int x=0;x<LEDCoefficients.size();x++) {LEDCoefficients.at(x);} printf("\n");
    printf("\tTIME_COEFF:  \t"); for(int x=0;x<TIMECoefficients.size();x++){TIMECoefficients.at(x);} printf("\n");
	//printf("\tSTREAM:      \t\n");
	printf("\tDETECTOR:    \t%i\n",detector);
	printf("\tPIXEL:       \t%i %i\n",pixel.first,pixel.second);
	printf("}\n\n");
}
