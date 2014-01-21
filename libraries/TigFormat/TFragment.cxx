#include"TFragment.h"

ClassImp(TFragment)

TFragment::TFragment(){
  Clear();
}

TFragment::~TFragment(){
	//Clear();
}

void TFragment::Clear(){  

	MidasTimeStamp = 0;
	MidasId = 0;

  TriggerId		= 0;
  FragmentId		= 0;
  TriggerBitPattern	= 0;

  ChannelAddress	=	-1;
  Cfd	=	-1;

  Charge	=	-1;
  
  TimeStamp	=	-1;
  
	if(!wavebuffer.empty())
		wavebuffer.clear();
}

void TFragment::Print()	{
	printf("not written yet.\n");
}











