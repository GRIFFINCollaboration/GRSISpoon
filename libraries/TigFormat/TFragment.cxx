#include"TFragment.h"

ClassImp(TFragment)

TFragment::TFragment(){
  Clear();
}

TFragment::~TFragment(){
	//Clear();
}

void TFragment::Clear(){  
  TriggerId		= 0;
  FragmentId		= 0;
  TriggerBitPattern	= 0;
  ODBType		= 0;
  
  ChannelName		= "XXXXXXXXXX";
  ChannelNumber	=	0;
  ChannelRaw	=	-1;
  Cfd	=	-1;
  Led	=	-1;
  TimeToTrig    = -9999;
  Charge	=	-1;
  ChargeCal	=	0;
  
  TimeStampLow	=	-1;
  TimeStampHigh	=	-1;
  TimeStampLive	=	0;
  TimeStampTR	=	0;  // triggers requested
  TimeStampTA	=	0;  // triggers accepted
  
  if(SamplesFound)
    wavebuffer.clear();
  SamplesFound	=	0;
  //waveform.SetBit(TH1::kCanRebin);
  
  SlowRiseTime = false;
  PileUp       = false;
}


int TFragment::Compare(const TObject *obj) const
{
  TFragment *other = (TFragment *)obj;
  if(TriggerId > other->TriggerId) {
    return -1;
  } else if (TriggerId == other->TriggerId) {
    if (FragmentId > other->FragmentId) {
      return -1;
    } else if (FragmentId == other->FragmentId) {
      return 0; // this shouldn't happen
    } else {
      return 1;
    }
  } else {
    return  1;  
  }
}

void TFragment::Print()	{
  printf("%s Event at	%i:\n",DigitizerType.c_str(),MidasId);
  printf("MidasId    	%i\n",MidasId);
  printf("TriggerId: 	%i\n",TriggerId);
  printf("FragmentId:   %i\n",FragmentId);
  printf("TriggerBit:	0x%08x\n",TriggerBitPattern);
  printf("Channel: %i\tName: %s\n",ChannelNumber,ChannelName.c_str());
  printf("\tChannel Raw: 0x%08x",ChannelRaw); printf("\t\tChannel Num:      %i\n",ChannelNumber);  
  printf("\tCharge Raw   0x%08x",Charge);			printf("\t\tCharge Cal:       %f\n",ChargeCal);  
  printf("\tLED:         0x%08x",Led);	  		printf("\t\tTimeStamp High: 0x%08x\n",TimeStampHigh); 
  printf("\tCFD:         0x%08x",Cfd);  		printf("\t\tTimeStamp Low:    0x%08x\n",TimeStampLow); 
  printf("\tTimeToTrig:  %i\n", TimeToTrig);
  unsigned short temptime = (TimeStampLow&0x0000ffff) - ((Cfd>>4)&0x0000ffff);//TimeStampLow&0x0000ffff; 
  printf("\ttime from timestamp(to the nearest 10ns):    0x%04x\t%ins\n",temptime,temptime*10);
  if(SamplesFound>0) printf("Has a wave form stored.\n");
  else printf("Does Not have a wave form stored.\n");
}











