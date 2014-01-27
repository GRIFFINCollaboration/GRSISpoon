#ifndef TIGSCOPE_H
#define TIGSCOPE_H


#include <cstdio>
#include <cstdlib>
#include <map>
#include <vector>
#include <cctype>

//#include <TTask.h>
//#include <TFolder.h>
//#include <TFile.h>
//#include <TSystem.h>
//#include <TDirectoryFile.h>

#include <TObject.h>
#include <TStopwatch.h>
#include <TList.h>
#include <TH1.h>

#include "TMidasFile.h"
#include "TMidasEvent.h"


#include "EventLoop.h"

#include "TTigFragment.h"
#include "TFragmentQueue.h"

#include "RootIOManager.h"
#include "CalibrationManager.h"

#include "Globals.h"

class EventLoop;

class TigScope : public EventLoop, public TObject	{
	public:
		static TigScope *instance(int argc=0,char** argv=0);

		~TigScope();

		bool SetMidasFile(const char*);
		TMidasFile *GetMidasFile()	{ return fmidasfile; }; //TMP

		TMidasEvent *ReadMidasFile();
		TTigFragment *ExtractFragment(TMidasEvent*);

		void PrintState();
		void PrintHelp();
		void Draw(TTigFragment*);
		
		int  IsInteractive()	{ 	return fInteractiveMode;}
		bool IsScopeOnly()	{	return fScopeMode;	}
		bool IsOnline()		{	return fIsOnline;	}
		bool IsOffline()	{	return fIsOffline;	}
		bool IsPyMode()		{	return fpythonMode;	}	
	
		//int GetRunNumber()	{	if(!fmidasfile) return 0; return fmidasfile->GetRunNumber();}; doesn't really work.
		int GetSubRunNumber()	{	if(!fmidasfile) return 0; return fmidasfile->GetSubRunNumber();};
		
		void StopSignal();	
	
	private:
		static TigScope *fTigScope;
		TigScope(int,char**);

		TMidasFile *fmidasfile;
		TMidasEvent *fmidasevent;
		TTigFragment *ftigfragment;

		TList *wavehist;

	private:
		TStopwatch *fScopeWatch;		
		//VirtualOdb* fODB;
		unsigned int fTotalFragments;

	private:

		bool HandleOptions(int,char**);
		void SetOptions();
		std::string hostname;
		std::string exptname;
		
		std::vector<std::string> mfileinname; 
		//int fNumMFiles;
		 
		std::string rfileinname;  
		std::string odbfname;
		std::string calfname;

		bool fInteractiveMode;
		bool fpythonMode;
		bool fScopeMode;
		bool fTestMode;
		bool fIsOnline;
		bool fIsOffline;

	private: 
		//inheritied from eventloop...
		bool ProcessMidasEvent(TMidasEvent *event);
		void Initialize(void);
		void BeginRun(int transition,int run,int time);
		void EndRun(int transition,int run,int time);
		void Finalize(void);

	ClassDef(TigScope,0)
};



#endif
