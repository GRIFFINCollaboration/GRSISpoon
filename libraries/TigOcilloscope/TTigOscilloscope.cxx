

#include "TTigOscilloscope.h"
#include "TTigOFrame.h"
	
//#include "TigScope.h"	
//#include "TigInput.h"


ClassImp(TTigOscilloscope)

TTigOscilloscope::TTigOscilloscope()	{	

	oframe = new TTigOFrame(gClient->GetRoot());

}

TTigOscilloscope::~TTigOscilloscope()	{	
//cleanup


}


