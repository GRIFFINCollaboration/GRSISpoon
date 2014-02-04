//define DEBUG 1
#ifdef DEBUG
#include <iostream>
#endif
#include "TSharc.h"

ClassImp(TSharc)

int TSharc::totalhits = 0;

TSharc::TSharc()	{	}

TSharc::~TSharc()	{	}

void	TSharc::BuildHits()	{
  //Clear();
  SharcHit sharchit;
  sharchit.Clear();
  //sharc_hits.clear();


  for(int i=0;i<GetMultiplicityFront();i++)	{	
  	
    #ifdef DEBUG
    		std::cout << "F " << GetFront_DetectorNbr(i) << std::endl;
    #endif
    for(int j=0;j<GetMultiplicityBack();j++)	{	
      #ifdef DEBUG
      			std::cout << "\tB " << GetBack_DetectorNbr(j) << std::endl;
      #endif
      if(GetFront_DetectorNbr(i) == GetBack_DetectorNbr(j))	{ //check if same detector
				sharchit.detectornumber = GetFront_DetectorNbr(i);

				sharchit.delta_e = (GetFront_Energy(i) + GetBack_Energy(j))/2.0;

				sharchit.front_charge = GetFront_Charge(i);
				sharchit.back_charge = GetBack_Charge(i);
				sharchit.delta_t			= GetFront_Time(i) ;  //cheak time allignment;
				sharchit.delta_cfd			= GetFront_TimeCFD(i) ;  //cheak time allignment;
				sharchit.position = GetPosition(GetFront_DetectorNbr(i), GetFront_StripNbr(i),							
				GetBack_DetectorNbr(j), GetBack_StripNbr(j));
				sharchit.pixel = std::make_pair(GetFront_StripNbr(i),GetBack_StripNbr(j));
																				
					//#ifdef DEBUG
					//				cout << "inside setting energy" << (GetFront_Energy(i) + GetBack_Energy(j))/2.0 << endl;
					//				cout << "and position: frontDet	"<< GetFront_DetectorNbr(i)<<" Strip	"<< GetFront_StripNbr(i)<<" backDet	"<<	GetBack_DetectorNbr(j)<<" Strip	"<< GetBack_StripNbr(j) <<endl;
					//				#endif	
					sharc_hits.push_back(sharchit);																				
					
      }
    }
  }
  //std::cout << "===============================================================" << std::endl;
  //cout << "GetMultiplicityFront(): " << GetMultiplicityFront();
  //cout <<	"\tGetMultiplicityBack():  " << GetMultiplicityBack();
  //cout << "\tn sharc hits " << sharc_hits.size() << endl;
	//cout << "\there 1" << endl;
  for(int k=0;k<GetMultiplicityPAD();k++)	{	
	//cout << "\t\there 1" << endl;
    //if(GetPAD_Energy(k)<1)
    //  continue; // stops pads getting set to zero energy with EVERY sharc hit
      
//    cout << "P " << GetPAD_DetectorNbr(k) << endl;
		int oldtotalhits = TSharc::totalhits;
    for(int l=0;l<sharc_hits.size();l++){
// cout << "sharc" << sharc_hits.at(l).detectornumber << endl;
      if(GetPAD_DetectorNbr(k) == sharc_hits.at(l).detectornumber)	{ //check if same detector
/*
				cout << "==============================================" << endl;				
				cout << "totalhits so far = " << ++TSharc::totalhits << endl;
				cout << "GetPAD_DetectorNbr(k): " << GetPAD_DetectorNbr(k) << endl; 
				cout << "GetPAD_Energy(k):      " << GetPAD_Energy(k) << endl; 
				cout << "GetPAD_Charge(k):      " << GetPAD_Charge(k) << endl; 
				cout << "GetPAD_Time(k):        " << GetPAD_Time(k) << endl; 
				cout << "GetPAD_TimeCFD(k):     " << GetPAD_TimeCFD(k) << endl; 
	*/			
				sharc_hits.at(l).energy = GetPAD_Energy(k);
				sharc_hits.at(l).charge = GetPAD_Charge(k);
				sharc_hits.at(l).time = GetPAD_Time(k);
				sharc_hits.at(l).pad_cfd = GetPAD_TimeCFD(k);
/*
				cout << "sharc_hits.at(l).detectornumber: " << sharc_hits.at(l).detectornumber << endl;
				cout << "sharc_hits.at(l).energy:         " << sharc_hits.at(l).energy << endl;
				cout << "sharc_hits.at(l).charge:         " << sharc_hits.at(l).charge << endl;
				cout << "sharc_hits.at(l).time:           " << sharc_hits.at(l).time << endl;
				cout << "sharc_hits.at(l).pad_cfd:        " << sharc_hits.at(l).pad_cfd << endl;
				//	cout << "GetPAD_DetectorNbr(k): " << GetPAD_DetectorNbr(k) << "\tenergy " << GetPAD_Energy(k) << endl;
				cout << "==============================================" << endl;
*/
      }
    }
/*
		if(oldtotalhits == TSharc::totalhits)	{
				cout << DRED << "\t==============================================" << RESET_COLOR << endl;
				cout << DRED << "\tPAD?DETECTOR MATCH NOT FOUND!!" << RESET_COLOR << endl;
				cout << DRED << "\tGetPAD_DetectorNbr(k): " << RESET_COLOR << GetPAD_DetectorNbr(k) << endl; 
				cout << DRED << "\tGetPAD_Energy(k):      " << RESET_COLOR << GetPAD_Energy(k) << endl; 
				cout << DRED << "\tGetPAD_Charge(k):      " << RESET_COLOR << GetPAD_Charge(k) << endl; 
				cout << DRED << "\tGetPAD_Time(k):        " << RESET_COLOR << GetPAD_Time(k) << endl; 
				cout << DRED << "\tGetPAD_TimeCFD(k):     " << RESET_COLOR << GetPAD_TimeCFD(k) << endl; 
				cout << DRED << "\t==============================================" << RESET_COLOR << endl;
		}
*/
  }
}


TVector3 TSharc::GetPosition(int FrontDet, int FrontStr, int BackDet, int BackStr)	{
  TVector3 position;
  double stripBpitch = 48.0/48;
  double stripFpitch = 72.0/24;
  double Zoffset = 7.;
  double Yoffset = 72.0/2;
  double x = 0;
  double y = 0;
  double z = 1;
  if(FrontDet>4 && FrontDet<9){ //forward box
    z = stripBpitch*(BackStr+0.5)+Zoffset;
    y = Yoffset;
    x = stripFpitch*(FrontStr-12+0.5);
    position.SetXYZ(x,y,z);
  }
  else if(FrontDet>8 && FrontDet<13){ //backward box
    z = stripBpitch*(BackStr+0.5)+Zoffset;
    z= -z;
    y = Yoffset;
    x = stripFpitch*(FrontStr-12+0.5);
    position.SetXYZ(x,y,z);
  }
  else{
    double outerradius =41;
    double ringpitch = (41.-9.)/16;
    double segmentpitch = 81.6/24;
    double z = 66.0;
    double rho = outerradius - (FrontStr+0.5)*ringpitch;
    double phi = (BackStr+0.5)*segmentpitch*TMath::Pi()/180.;
    phi+=(4-FrontDet)*TMath::Pi()/2.;
    position.SetXYZ(1.,1.,1.);
    position.SetPerp(rho);
    position.SetPhi(phi);
    if(FrontDet<5)
      position.SetZ(z);
    else
      position.SetZ(-z);
  }
  
  
  
  
  return position;
}




void TSharc::Clear()	{
  //cout << "clearing " << endl;
  ClearData();
  sharc_hits.clear();
  //cout <<" size: " << sharc_hits.size() << endl;
}


