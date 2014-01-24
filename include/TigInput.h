#ifndef TIGINPUT_H
#define TIGINPUT_H

#include <cstdio>
#include <iostream>

#include <RConfig.h>
#include <TRint.h>
#include <TSysEvtHandler.h>

#include "Globals.h"

class TigInput : public TRint	{

	private:
	  	bool						fRunning;
		bool						fUseRintInterruptHandler; // flag if TRint signal handler is used
		TSignalHandler *fRintInterruptHandler;    // original signal handler of TRint
		TSignalHandler *fTIGInterruptHandler;    // special handler of ROMERint
		int							fFPEMask;                 // Customized FPE mode
		static bool	fpython;
		bool          	fRemoteProcess;           // Flag if lines are processed remotely
//		TNetFolder     *fSocketClientNetFolder;   // Socket client for remote execution
		TString         fSocketClientHost;        // Hostname for remote execution
		int           	fSocketClientPort;        // Port number for remote execution

	private:
		TigInput(const char *appClassName, int *argc, char **argv,
						 void *options = 0, Int_t numOptions = 0, Bool_t noLogo = kFALSE);
	public:
		static TigInput *fTigInput;
		static TigInput	*instance(int *argc = 0, char **argv = 0, const char *appClassName = "tigscope",
						 void *options = 0, Int_t numOptions = 0, Bool_t noLogo = kFALSE);
		virtual ~TigInput();

		void SetPython(bool pyflag) { fpython = pyflag;}


		void PrintLogo(bool);

		bool	HandleTermInput();
		int		TabCompletionHook(char*,int*,ostream&);
//		long	ProcessLine(const char *line, Bool_t sync = kFALSE, Int_t *error = 0);
//		long	ProcessFile(const char *file, Int_t *error = 0);




	ClassDef(TigInput,1)
};

#endif

