

#include <TMath.h>

#include "TSharc.h"


ClassImp(TSharc)


TSharc::TSharc()	{	}

TSharc::~TSharc()	{	}





void	TSharc::BuildHits()	{

  //  after the data has been taken from the fragement tree, the data
  //  is stored/correlated breifly in by the tsharcdata class - these 
  //  function takes the data out of tsharcdata, and puts it into the 
  //  the tsharchits class.  These tsharchit objects are how we access
  //  the data stored in the tsharc branch in the analysis tree. 
  //
  //  pcb.
  //

  TSharcHit sharchit;

  for(int i=0;i<GetMultiplicityFront();i++)	{	
  	
    for(int j=0;j<GetMultiplicityBack();j++)	{	

      if(GetFront_DetectorNbr(i) == GetBack_DetectorNbr(j))	{ //check if same detector
				sharchit.SetDetector(GetFront_DetectorNbr(i));
			
				sharchit.SetDeltaE(GetFront_Energy(i)); 
				sharchit.SetFrontCharge(GetFront_Charge(i));
				sharchit.SetBackCharge(GetBack_Charge(i));
				sharchit.SetDeltaT(GetFront_Time(i)) ;  		//cheak time allignment;
				//sharchit.SetDeltaCfd(GetFront_TimeCFD(i));		//cheak time allignment;
																				
				sharc_hits.push_back(sharchit);																				
      }
    }
  }

  for(int k=0;k<GetMultiplicityPAD();k++)	{	
	//int oldtotalhits = TSharc::totalhits;
    for(int l=0;l<sharc_hits.size();l++)	{
      if(GetPAD_DetectorNbr(k) == sharc_hits.at(l).GetDetectorNumber())	{ //check if same detector
				
				sharc_hits.at(l).SetPadE(GetPAD_Energy(k));
				sharc_hits.at(l).SetPadCharge(GetPAD_Charge(k));
				sharc_hits.at(l).SetPadT(GetPAD_Time(k));
				//sharc_hits.at(l).SetPadCFD(GetPAD_TimeCFD(k));
      }
    }
  }
}


TVector3 TSharc::GetPosition(TSharcHit *hit)	{
  // given a tsharchit, this function gets
  // it's pixel and detector number and returns
  // a TVector3 pointing to the hits position from 
  // the `center` of teh area.	
  //
  // pcb.
  //



  int FrontDet = hit->GetDetectorNumber();
  int FrontStr = hit->GetPixel().first;
  int BackDet  = hit->GetDetectorNumber();
  int BackStr  = hit->GetPixel().second;


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




void TSharc::Clear(Option_t *option)	{
  //cout << "clearing " << endl;
  ClearData();
  sharc_hits.clear();
  //cout <<" size: " << sharc_hits.size() << endl;
  return;
}

void TSharc::Print(Option_t *option)	{
  printf("not yet written...\n");
  return;
}



double TSharc::GetDeadLayer(TSharcHit *hit)	{
	
		
   //TVector3 position = sharc->GetPosition(detector,frontstrip,detector,backstrip);
	TVector3 position = GetPosition(hit);

	double deadlayerthicknessinput[16] = {0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};  // note: make a .sharc_rc to put stuff like this.

	if(hit->GetDetectorNumber()>4 && hit->GetDetectorNumber()<13 ){ // BOX
		//double sintheta = TMath::Sin(position.Theta());
		//double phi = position.Phi() - (TMath::Pi()/2);
		//double cosphi = TMath::Cos(phi);
		//return deadlayerthicknesslayer[hit->GetDetectorNumber()]/(sintheta*cosphi);
		return deadlayerthicknessinput[hit->GetDetectorNumber()]/(  TMath::Sin(position.Theta())*TMath::Cos(position.Phi() - (TMath::Pi()/2)) );   
	}
	else if( hit->GetDetectorNumber() <= 4 || hit->GetDetectorNumber() >= 13 ){ // QQQ
		//double costheta = TMath::Cos(position.Theta());
		//return deadlayerthicknesslayer[hit->GetDetectorNumber()]/(costheta);
		return deadlayerthicknessinput[hit->GetDetectorNumber()]/(TMath::Cos(position.Theta()));
	}	

}




TVector3 TSharc::GetPosition(int detector, int frontstrip, int backstrip)	{
  int FrontDet = detector;
  int FrontStr = frontstrip;
  int BackDet  = detector;
  int BackStr  = backstrip;


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

double TSharc::GetDeadLayer(int detector, int frontstrip, int backstrip)		{
    TVector3 position = TSharc::GetPosition(detector,frontstrip,backstrip);

    double deadlayerthicknessinput[16] = {0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1};  // note: make a .sharc_rc to put stuff like this.

    if(detector>4 && detector<13 ){ // BOX
        return deadlayerthicknessinput[detector]/(  TMath::Sin(position.Theta())*TMath::Cos(position.Phi() - (TMath::Pi()/2)) );
	}
    else if( detector <= 4 || detector >= 13 ){ // QQQ
        return deadlayerthicknessinput[detector]/(TMath::Cos(position.Theta()));
    }

}










