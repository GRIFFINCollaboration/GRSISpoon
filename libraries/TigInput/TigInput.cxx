#include <string>
#include <vector>
#include <cstdlib>

#include <TRandom.h>
#include <TSystem.h>
#include <TUnixSystem.h>
#include <TSysEvtHandler.h>
#include <TSocket.h>
#include <TPython.h>

#include <signal.h>

#include "Globals.h"

#include "TigInput.h"
#include "TigUtilities.h"


ClassImp(TigInput)

TigInput *TigInput::fTigInput = NULL;


TigInput *TigInput::instance(int *argc, char **argv, const char *appClassName,
			      void *options,int numOptions, bool noLogo,bool py_flag)	{
	if(!fTigInput)
		fTigInput = new TigInput(appClassName,argc,argv,options,numOptions,true,py_flag);
	return fTigInput;
}


TigInput::TigInput(const char *appClassName, int *argc, char **argv,
                   void *options, Int_t numOptions, Bool_t noLogo,bool py_flag)
					:TRint(appClassName, argc, argv, options, numOptions,noLogo)
					,fRunning(kFALSE)
					,fUseRintInterruptHandler(kFALSE)
					,fRintInterruptHandler(0)
					,fTIGInterruptHandler(0)
					,fFPEMask(0)
					,fRemoteProcess(kFALSE)
//					,fSocketClientNetFolder(0)
					,fSocketClientHost("localhost")
					,fSocketClientPort(9099)
{
		fRintInterruptHandler = gSystem->RemoveSignalHandler(GetSignalHandler());
		fUseRintInterruptHandler = kFALSE;

		//--- install default handlers
		//UnixSignal(kSigChild,                 SigHandler);
		UnixSignal(kSigBus,                   SigHandler);
		UnixSignal(kSigSegmentationViolation, SigHandler);
		UnixSignal(kSigIllegalInstruction,    SigHandler);
		UnixSignal(kSigSystem,                SigHandler);
		UnixSignal(kSigPipe,                  SigHandler);
		UnixSignal(kSigAlarm,                 SigHandler);
		//UnixSignal(kSigUrgent,                SigHandler);
		UnixSignal(kSigFloatingException,     SigHandler);
		//UnixSignal(kSigWindowChanged,         SigHandler);
		
		//printf( DGREEN "getenv = %s" RESET_COLOR "\n", getenv("GRSISYS"));
		//std::string grsi_path = getenv("GRSISYS");
		//if(grsi_path.length()>0)	{
		//	grsi_path += "/.grsirc";
		//	fGrsiEnv = new TEnv(grsi_path.c_str());	
		//}
		
		PrintLogo(false);
		//SetPrompt( DYELLOW "TIGRESS [%d]" RESET_COLOR);
		SetPrompt( DYELLOW "GRSI [%d]" RESET_COLOR);
		//printf("fpython = %i\n",TigInput::fpython);
		if(py_flag) {
			printf("in start python....\n");
			//gSystem->Load("libPyROOT");
			TPython *pyp = new TPython();

			//TPython::ExecScript("/home/bender/Programs/GRSISpoon/test.py",0,0);
			//pyp->ExecScript("/home/bender/Programs/GRSISpoon/test.py",0,0);
			
			pyp->Prompt();
			//TPython::Prompt();
		}
		//Run();
}


TigInput::~TigInput()
{
   SafeDelete(fTIGInterruptHandler);
//   SafeDelete(fSocketClientNetFolder);
}


bool TigInput::HandleTermInput()
{
	return TRint::HandleTermInput();
//   return true;
}

int TigInput::TabCompletionHook(char* buf,int* pLoc,ostream& out)	{
	return TRint::TabCompletionHook(buf,pLoc,out);
}

void TigInput::PrintLogo(bool lite)	{
	
	//const char *root_version = gROOT->GetVersion();
	if(!lite)	{
	#if PLATFORM == Linux
		const std::string &ref = ProgramName();	
	#else 
		const std::strinf &ref = "Nuclear Data";
	#endif


  	const unsigned int reflength = ref.length() - 78;
		const unsigned int width = reflength + (reflength % 2);
				
		//printf(DBLACK);
		printf("\t*%s*\n", std::string(width,'*').c_str());	
		printf("\t*%*s%*s*\n",width/2+5,"GRSI SPOON", width/2-5, "");
	
		printf("\t*%*s%*s*\n",width/2+reflength/2, ref.c_str(), width/2-reflength/2, "");
		printf("\t*%*s%*s*\n",width/2+5, "version 1.0", width/2-5, "");
		printf("\t*%s*\n", std::string(width,'*').c_str());	
		//printf(RESET_COLOR "\n");
	}

}







































