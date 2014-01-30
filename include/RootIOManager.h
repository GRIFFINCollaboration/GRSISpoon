
#ifndef ROOTIOMANAGER_H
#define ROOTIOMANAGER_H

#include <cstdio>
#ifndef __CINT__
#define _GLIBCXX_USE_NANOSLEEP 1
#include <thread>
#endif

#include <string>

#include <TObject.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TTreeIndex.h>


#include "TTigFragment.h"
#include "TFragmentQueue.h"
#include "CalibrationManager.h"

class RootIOManager : public TObject{

	public:
		static RootIOManager *instance();
		~RootIOManager();

		void OpenOutFile(int runnumber = 0, int subrunnumber = 0, char * filename = "output.root");

	private: 
		static RootIOManager *fRootIOManager;
		RootIOManager();

		TFile *frootfile;

		TTree *fouttree;
		TTree *fonlinetree;
		TTigFragment *fbufferfrag;

		TChain *finputchain;	
		TList *finputfilelist;
		
		TList *foutlist;
		std::map<std::string,TList*> outlistmap;

		bool fRunningProcessor;

		int fcounter;

	public:
		bool FragProcessorIsOn()	{	return fRunningProcessor;	};
		void Stop(); //	{	fRunningProcessor = false; return;	};

		void SetFragmentTreeAnalysisMode();

		void SetRootFileInName(const char*);
		bool CloseRootFile();

		int TreeSize()	{	return fcounter;	};

		TH1 *MakeHitPattern();
		TH1 *Make1DProjection(std::string,std::string);
		TH1 *Make2DProjection(std::string,std::string);

	private:

		void StartFragmentProcessor();
		void HandleFragments(); 
		void FragmentSwitchBoard(TTigFragment*);
		void FillTree(TTigFragment*);

		void SetUpOutTree();
		void SetUpOnlineTree();

		
	ClassDef(RootIOManager,0)
};




#endif
