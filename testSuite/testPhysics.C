//To compile:
// g++ testPhysics.C -I/home/cu/Code/TIGRESS/GRSISpoon/include --std=c++0x -o testPhysics /home/cu/Code/TIGRESS/GRSISpoon/libraries/TigFormat/libFormat.so /home/cu/Code/TIGRESS/GRSISpoon/libraries/libCalManager.so /home/cu/Code/TIGRESS/GRSISpoon/libraries/libRootIOManager.so -O2 `root-config --cflags --libs` -lTreePlayer -lSpectrum -lgsl -lgslcblas -g
// C/C++ libraries:
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <fstream>

// ROOT libraries:
#include <TFile.h>
#include <TStopwatch.h>
#include <TTree.h>
#include <TCutG.h>
#include <TTreeIndex.h>
#include <TTreePlayer.h>
#include <TChain.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TApplication.h>
#include <TStyle.h>
#include <TRandom3.h>  // TRandom3 is less correlated than TRandom and almost as fast.  ls 
#include <TCanvas.h>

// GRSIspoon libraries
#include "TTigFragment.h"

#define CLOVERS 16
#define CRYSTALS 4
#define EN_SPECTRA_CHANS 8192
#define EN_SPECTRA_MAX 2048

// Global/static Variables
TApplication* App;  // Pointer to root environment for plotting etc

static TH1F *hTestSpectrum = 0;
static TH1F *hCoreEn[CLOVERS][CRYSTALS] = {0};
static TH1F *hCoreEnGated[CLOVERS][CRYSTALS] = {0};
static TH1F *hCloverABEn[CLOVERS] = {0};
static TH1F *hCloverABEnGated[CLOVERS] = {0};

static TFile *outfile = 0;

// Functions
int InitCoincEff();    // initialise spectra, etc
int FinalCoincEff();   // perform fits/integration, save spectra, etc
int CoincEff(std::vector<TTigFragment> &ev);        // event by event analysis


int main(int argc, char **argv) {

   // Set options for histo stats
	gStyle->SetOptStat("iouRMen");
	
   // create root environment for interacting with plots etc
   App= new TApplication("Output", 0, NULL);  
 
   // Variables, Constants, etc
   int i,j;     
   int NumTreeEntries = -1;
	int NumTreeEvents = -1;
	int FragCount = -1;
   
   // Timing
   TStopwatch StopWatch;
	StopWatch.Start();

   // Fragments
   TTigFragment *Frag = 0;
	std::vector<TTigFragment> evFrags;

   // Initialise spectra
   if(InitCoincEff() > 0) {
      cout << "Spectra initialised." << endl;
   }
   else {
      cout << "Error initialisingn spectra!";
      return -1;
   }

   //open input file
	TFile *FileIn = new TFile("/media/data1/Experiments/tigress/TigTest/fragment27401_000.root");
	if(!FileIn) {
	   printf("Error opening file!\n");
	   return -1;
	}
	else {
	   printf("\t"  "file opened: %s" "\n", FileIn->GetName());
	}
	
	//open our trees
	TTree *Tree = (TTree*)FileIn->Get("FragmentTree");
	
	// Get/Build Index
	if(!Tree->GetTreeIndex())	{
      printf("\nTree Index not found, Building index...");
      fflush(stdout);
      Tree->BuildIndex("TriggerId","FragmentId");
      printf("  Done\n");
      fflush(stdout);
   }
	
   TBranch *Branch = Tree->GetBranch("TTigFragment");
	
	Branch->SetAddress(&Frag);
	//   Tree->SetMaxVirtualSize(ROOT_VIRT_SIZE);
	Branch->LoadBaskets();
	   
	NumTreeEntries = Tree->GetEntries();  
	NumTreeEvents  = (int)Tree->GetMaximum("TriggerId");

   for(int j=0;j<NumTreeEvents;j++)	{  
      evFrags.clear();		   
      int FragNum = 1;
   
      FragCount = 0;
   
      while(Tree->GetEntryWithIndex(j,FragNum++) != -1 ) {
		   evFrags.push_back(*Frag);
		   FragCount++;
		}
		
      
      CoincEff(evFrags);
      
   
   
   }
   
   return 0;

}



int CoincEff(std::vector<TTigFragment> &ev)	{

   cout << "Processing frags..." << endl;
   for(int i=0;i<ev.size();i++) {
      cout << ev[i].ChannelName << endl;
   }
   int a = 1;
	return a;
}

int InitCoincEff()	{
   // Initialise output file                                       
   outfile = new TFile("CoincEffOut.root","RECREATE");
   
   char Colours[] = "BGRW";
   char name[512], title[512];
   int Clover, Crystal;  
   
   hTestSpectrum = new TH1F("TS","Test Spectrum",4096,0,4095);
   for(Clover=0;Clover<CLOVERS;Clover++) {
      sprintf(name,"TIG%02d AB",Clover+1); 
      sprintf(title,"TIG%02d Clover Add-Back Energy (keV)",Clover+1);     
      hCloverABEn[Clover] = new TH1F(name,title,EN_SPECTRA_CHANS,0,EN_SPECTRA_MAX);
      sprintf(name,"TIG%02d Gated AB",Clover+1); 
      sprintf(title,"TIG%02d Gated Clover Add-Back Energy (keV)",Clover+1);     
      hCloverABEnGated[Clover] = new TH1F(name,title,EN_SPECTRA_CHANS,0,EN_SPECTRA_MAX);    
      for(Crystal=0;Crystal<CRYSTALS;Crystal++) {
         sprintf(name,"TIG%02d%c En",Clover+1,Colours[Crystal]);
         sprintf(title,"TIG%02d%c Core Energy (keV)",Clover+1,Colours[Crystal]);
         hCoreEn[Clover][Crystal] = new TH1F(name,title,EN_SPECTRA_CHANS,0,EN_SPECTRA_MAX);
         sprintf(name,"TIG%02d%c Gated",Clover+1,Colours[Crystal]);
         sprintf(title,"TIG%02d%c Gated Core Energy (keV)",Clover+1,Colours[Crystal]);
         hCoreEnGated[Clover][Crystal] = new TH1F(name,title,EN_SPECTRA_CHANS,0,EN_SPECTRA_MAX);
      }
   }   
   
	return 1;
}

int FinalCoincEff()	{

   int Clover, Crystal;  
   outfile->cd();
   
   for(Clover=0;Clover<CLOVERS;Clover++) {
      hCloverABEn[Clover]->Write();
   }
   for(Clover=0;Clover<CLOVERS;Clover++) {
      hCloverABEnGated[Clover]->Write();
   }
   for(Clover=0;Clover<CLOVERS;Clover++) {
      for(Crystal=0;Crystal<CRYSTALS;Crystal++) {
         hCoreEn[Clover][Crystal]->Write();
      }
   }
   for(Clover=0;Clover<CLOVERS;Clover++) {
      for(Crystal=0;Crystal<CRYSTALS;Crystal++) {
         hCoreEnGated[Clover][Crystal]->Write();
      }
   }
	return 1;
}
          
