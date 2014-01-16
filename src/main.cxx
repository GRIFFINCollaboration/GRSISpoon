
#include<cstdio>

#include "TigScope.h"
#include "TigInput.h"
#include "TTigOcilloscope.h"

TigScope *gSCOPE = NULL;

int main(int argc,char **argv)	{
	
	printf("main started.\n");
	
	gSCOPE = TigScope::instance(argc,argv);	
	TigInput *input = 0;

	if(gSCOPE->IsScopeOnly())	{
		TApplication *app = new TApplication("app",&argc,argv);
		TTigOcilloscope *oscope = new TTigOcilloscope();//(gClient->GetRoot());
		app->Run(true);
		printf("goodbye.\n");
	}

	else if(gSCOPE->IsInteractive())	{
		input = TigInput::instance();			
		input->Run(true);
	}
	
	

	return 0;
}
