

#include <TMath.h>

#include "TSharc.h"


ClassImp(TSharc)


TSharc::TSharc()	{	}

TSharc::~TSharc()	{	}





void	TSharc::BuildHits(Option_t *opt)	{

  //  after the data has been taken from the fragement tree, the data
  //  is stored/correlated breifly in by the tsharcdata class - these 
  //  function takes the data out of tsharcdata, and puts it into the 
  //  the tsharchits class.  These tsharchit objects are how we access
  //  the data stored in the tsharc branch in the analysis tree. 
  //
  //  pcb.
  //

  TSharcHit sharchit;
	int fCfdBuildDiff = 5; // largest acceptable time difference between events (clock ticks)  (50 ns)

	std::map<std::tuple<int,int,int>,int> hitmap;

  for(int i=0;i<GetMultiplicityFront();i++)	{	
  	
    for(int j=0;j<GetMultiplicityBack();j++)	{	

      if(GetFront_DetectorNbr(i) == GetBack_DetectorNbr(j))	{ //check if same detector
		
				if(abs(GetFront_TimeCFD(i)-GetFront_TimeCFD(j)) > fCfdBuildDiff)
					continue; // ensure there s front-back time correlation to protect against noise
		
				sharchit.SetDetector(GetFront_DetectorNbr(i));
	
				sharchit.SetDeltaE(GetFront_Energy(i)); 
				sharchit.SetFrontCharge(GetFront_Charge(i));
				sharchit.SetBackCharge(GetBack_Charge(j));
				sharchit.SetDeltaT(GetFront_Time(i)) ;  		//cheak time allignment;

				sharchit.SetFrontCFD(GetFront_TimeCFD(i));
				sharchit.SetBackCFD(GetBack_TimeCFD(j));			

				sharchit.SetPixel(GetFront_StripNbr(i),GetBack_StripNbr(j));
				//sharchit.SetDeltaCfd(GetFront_TimeCFD(i));		//cheak time allignment;

				sharchit.SetPosition(TSharc::GetPosition(GetFront_DetectorNbr(i),GetFront_StripNbr(i),GetBack_StripNbr(j)));
																				
				sharc_hits.push_back(sharchit);																				

				hitmap.insert({std::make_tuple((int)GetFront_DetectorNbr(i),(int)GetFront_StripNbr(i),(int)GetBack_StripNbr(j)),sharc_hits.size()-1});


      }
    }
  }

	if(opt == "CLEAN")	{

		// std::sort(sharc_hits.begin(),sharc_hits.end(),TSharcHits::Compare);


  	//
  	///  Do we have good hits??
  	//
/*
		double sumfront, sumback;
		double cdiff_frac = 0.05;


  	for(int x=0;x<sharc_hits.size()-1;x++)  {
  	  for(int y=x+1;y<sharc_hits.size();y++)  {
  				// are hits on same detector   ? 
				if(sharc_hits.GetDetectorNumber(y) != sharc_hits.GetDetectorNUmber(x) )	//{   //===> IS GOOD.	
					break;
				
					// are hits on adjacent front strips	?
				if( abs(sharc_hits.GetFrontStrip(y) - sharc_hits.GetFrontStrip(x) ) > 1 ) 
					break;            // >1 ) ===> IS GOOD.
	
					// are hits on adjacent back strips	?
				if( abs(sharc_hits.GetiBackStrip(y) - sharc_hits.GetBackStrip(x) ) >1 )  {//===> IS GOOD.
					
					if
					{
					}
				}





				// is the front and back of each hit time correlated		?
				if( abs(sharc_hits.GetFrontCFD(x) - sharc_hits.GetBackCFD(x)) > 5 )
			 		if( abs(sharc_hits.GetFrontCFD(y) - sharc_hits.GetBackCFD(y)) > 5 )
						if( abs (((sharc_hits.GetFrontCFD(x)+sharc_hits.GetBackCFD(x))/2) -  ((sharc_hits.GetFrontCFD(y)+sharc_hits.GetBackCFD(y))/2)) > 5)     ===> IS GOOD.
						// are the two hits time correlated		?
	
						// get combined front charge and back charge of both hits
						sumfront = sharc_hits.GetFrontCharge(x)+sharc_hits.GetFrontCharge(y);
						sumback = sharc_hits.GetBackCharge(x)+sharc_hits.GetBackCharge(y);
				
									
					// is the deviation in combined charge between the fronts and backs large	?
						if(2*abs(sumfront-sumback)/(sumfront+sumback)>cdiff_frac)) =====> THROW ONE OUT??
	
  	  }
	  }
*/
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


//TVector3 TSharc::GetPosition(TSharcHit *hit)	{
//
//   The vector3 must be stored in the TSharcHit class to 
//   allow for weighted avgs of differenet pixel to be calculated
//   and stored.
//
//}




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



//double TSharc::GetDeadLayer(TSharcHit *hit)	{
//	
//
//}




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
        return deadlayerthicknessinput[detector-1]/(  TMath::Sin(position.Theta())*TMath::Cos(position.Phi() - (TMath::Pi()/2)) );
	}
    else if( detector <= 4 || detector >= 13 ){ // QQQ
        return deadlayerthicknessinput[detector-1]/(TMath::Cos(position.Theta()));
    }

}










