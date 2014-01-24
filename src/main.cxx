
#include<cstdio>

#include "TigScope.h"
#include "TigInput.h"
#include "TTigOscilloscope.h"

TigScope *gSCOPE = NULL;

int main(int argc,char **argv)	{
	
	printf("main started.\n");
	
	gSCOPE = TigScope::instance(argc,argv);	
	TigInput *input = 0;

	if(gSCOPE->IsScopeOnly())	{
		TApplication *app = new TApplication("app",&argc,argv);
		TTigOscilloscope *oscope = new TTigOscilloscope();//(gClient->GetRoot());
		app->Run(true);
		printf("goodbye.\n");
	}

	else if(gSCOPE->IsInteractive()>0)	{
		input = TigInput::instance();			
		input->Run(true);
	}
	
	

	return 0;
}
