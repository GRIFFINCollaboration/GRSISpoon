

#include "TTigOcilloscope.h"
#include "TTigOFrame.h"
	
//#include "TigScope.h"	
//#include "TigInput.h"


ClassImp(TTigOcilloscope)

TTigOcilloscope::TTigOcilloscope()	{	

	oframe = new TTigOFrame(gClient->GetRoot());

}

TTigOcilloscope::~TTigOcilloscope()	{	
//cleanup


}


