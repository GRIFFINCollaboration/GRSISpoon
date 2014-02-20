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
#define THRESH 5 
#define GATE_LOW 1170
#define GATE_HIGH 1176
#define ROOT_VIRT_SIZE    500000000  //  500MB 

// Global/static Variables
TApplication* App;  // Pointer to root environment for plotting etc

static TH1F *hStatHist = 0;
static TH1F *hCoreEn[CLOVERS][CRYSTALS] = {0};
static TH1F *hCoreEnGated[CLOVERS][CRYSTALS] = {0};
static TH1F *hCloverABEn[CLOVERS] = {0};
static TH1F *hCloverABEnGated[CLOVERS] = {0};

static TFile *outfile = 0;

// Structure to hold Mnemonic
struct Mnemonic	{
   int arrayposition;
   int	segment;
   std::string system;
   std::string subsystem;
   std::string arraysubposition;
   std::string collectedcharge;
   std::string outputsensor;
};

// Functions
int InitCoincEff();    // initialise spectra, etc
int FinalCoincEff();   // perform fits/integration, save spectra, etc
int CoincEff(std::vector<TTigFragment> &ev);        // event by event analysis
void ParseMnemonic(std::string *name,Mnemonic *mnemonic);  // Function to parse Mnemonic name:
int Col2Num(char Colour);  // Convert crystal Name/number
char Num2Col(int Crystal);

int main(int argc, char **argv) {

   // Set options for histogram stats
	gStyle->SetOptStat("iouRMen");
	
   // create root environment for interacting with plots etc
   App= new TApplication("Output", 0, NULL);  
 
   // Variables, Constants, etc
   int i,j;     
   int NumTreeEntries = -1;
	int NumTreeEvents = -1;
	int FirstTreeEvent = -1;
	int FragCount = 0;
   
   // Timing
   TStopwatch StopWatch;
	StopWatch.Start();

   // Fragments
   TTigFragment *Frag = 0;
	std::vector<TTigFragment> evFrags;

   // Initialise spectra and output file
   if(InitCoincEff() > 0) {cout << "Spectra initialised." << endl;}
   else {
      cout << "Error initialisingn spectra!";
      return -1;
   }

   //open input file
	TFile *FileIn = new TFile("/media/data1/Experiments/tigress/TigTest/fragment27401_000.root");
	//TFile *FileIn = new TFile("/media/data1/Experiments/tigress/TigTest/fragment26831_001.root");
	if(!FileIn) {
	   printf("Error opening file!\n");
	   return -1;
	}
	else {printf("\t"  "file opened: %s" "\n", FileIn->GetName());}
	
	// load tree
	TTree *Tree = (TTree*)FileIn->Get("FragmentTree");
	
	// Get/Build Index
	if(!Tree->GetTreeIndex())	{
      printf("\nTree Index not found, Building index...");
      fflush(stdout);
      Tree->BuildIndex("TriggerId","FragmentId");
      printf("  Done\n");
      fflush(stdout);
   }
	
	// Set up branch
   TBranch *Branch = Tree->GetBranch("TTigFragment");	
	Branch->SetAddress(&Frag);
	Tree->SetMaxVirtualSize(ROOT_VIRT_SIZE);  // not sure if this is still needed or if default is now 
	Branch->LoadBaskets();
	
	// Get some numbers from tree
	NumTreeEntries = Tree->GetEntries();  
	FirstTreeEvent = (int)Tree->GetMinimum("TriggerId");
	NumTreeEvents  = (int)Tree->GetMaximum("TriggerId");
   
   cout << NumTreeEntries << " fragments in " << NumTreeEvents << " events." << endl;
   
   for(int j=FirstTreeEvent;j<NumTreeEvents;j++)	{  // loop events
   
      evFrags.clear(); // clear frag list
      int FragNum = 1; // fragment number in this event
   
      while(Tree->GetEntryWithIndex(j,FragNum++) != -1 ) {
		   evFrags.push_back(*Frag);  
		   FragCount++;  // total frags seen in all events so far
		}
	 
      CoincEff(evFrags);  // Function to process each event
      
      if(j%500 ==0) {
         cout << "Processed " << j << " / " << NumTreeEvents << " events" << endl;
      }
     
   }
   
   FinalCoincEff();
   
   return 0;

}



int CoincEff(std::vector<TTigFragment> &ev)	{
   
   Double_t val = 0;
   Int_t Crystal;
   Int_t Clover;
   Int_t GatePassed = 0;
   Int_t GateCrystal = 0;
   Int_t GateClover = 0;
   Int_t i;
   float Energy;
   float CoreEnergies[CRYSTALS][CLOVERS];
   float CloverAddBack[CLOVERS];
   
   memset(CoreEnergies, 0.0, (CLOVERS*CRYSTALS*sizeof(float)));
   memset(CloverAddBack  , 0.0,  CLOVERS*sizeof(float));
   
   
   // First loop fragments and extract info we need
   for (i=0; i < ev.size(); i++) {
      std::string name	=	ev[i].ChannelName;
      
      Mnemonic mnemonic;
      if(name.size() >= 10) {ParseMnemonic(&name,&mnemonic);}
      else {
         cout << "This shouldn't happen if the odb is correctly configured!" << endl;
         continue;   
      }
   
      if(mnemonic.system == "TI") {  // If this is TIGRESS
         // Determine Crystal
         char Colour = mnemonic.arraysubposition.c_str()[0];  
         Crystal = Col2Num(Colour);
         if(Crystal == -1) {
            cout << "Bad Colour: " << Colour << endl;
            continue;
         }
         
         // Determine Clover position
         Clover = mnemonic.arrayposition;
         
         // If this is a core
         if(mnemonic.segment == 0) {
            Energy = ev[i].ChargeCal;
            if(Energy>THRESH) {
            
               // Add energy to cloverAB
               CloverAddBack[Clover-1] += Energy;
               
               // Add to crystal energy array
               CoreEnergies[Clover-1][Crystal] = Energy;
               
               // Fill raw core spectra
               hCoreEn[Clover-1][Crystal]->Fill(Energy);
               
            }        
         } 
      }
   }
   // Loop clovers and fill add-back spectra
   for(Clover=0;Clover<CLOVERS;Clover++) {
      if(CloverAddBack[Clover] > THRESH) {
         hCloverABEn[Clover]->Fill(CloverAddBack[Clover]);
      }
   }
   
   // Now loop energy arrays, see if 1173 gate is passed, and if so fill gated spectra
   GatePassed = 0;
   GateClover = 0;
   GateCrystal = 0;
   // First check core energies
   for(Clover=0;Clover<CLOVERS;Clover++) {
      for(Crystal=0;Crystal<CRYSTALS;Crystal++) {
         if((CoreEnergies[Clover][Crystal] > GATE_LOW) && (CoreEnergies[Clover][Crystal] < GATE_HIGH) ) {
            GatePassed = 1;
            GateClover = Clover;
            GateCrystal = Crystal; 
            break;
         }
      }
      if(GatePassed==1) {
         break;
      }
   }
   // If gate not passed by core, check add-back
   for(Clover=0;Clover<CLOVERS;Clover++) {
      if((CloverAddBack[Clover] > GATE_LOW) && (CloverAddBack[Clover] < GATE_HIGH) ) {
         GatePassed = 1;
         GateClover = Clover;
         GateCrystal = 0;
         break;
      }
   }
   // If gate was passed, fill gated spectra
   if(GatePassed) {
      // Record count of events passing gate
      hStatHist->Fill(1.0);
      // Add-back first
      for(Clover=0;Clover<CLOVERS;Clover++) {
         if((Clover!=GateClover) && (CloverAddBack[Clover]>THRESH)) {
            hCloverABEnGated[Clover]->Fill(CloverAddBack[Clover]);        
         }
      }
      // Now cores
      for(Clover=0;Clover<CLOVERS;Clover++) { 
         for(Crystal=0;Crystal<CRYSTALS;Crystal++) {
            if((Clover!=GateClover) || (Crystal != GateCrystal)) {
               if(CoreEnergies[Clover][Crystal]>THRESH) {
                  hCoreEnGated[Clover][Crystal]->Fill(CoreEnergies[Clover][Crystal]);
               }
            }
         }
      }
     
   }
   
	return 1;
}

int InitCoincEff() {
   // Initialise output file                                       
   outfile = new TFile("testPhysicsOut.root","RECREATE");
   
   char name[512], title[512];
   int Clover, Crystal;  
   
   hStatHist = new TH1F("Stats","Stats Spectrum",4096,0,4095);
   for(Clover=0;Clover<CLOVERS;Clover++) {
      sprintf(name,"TIG%02d AB",Clover+1); 
      sprintf(title,"TIG%02d Clover Add-Back Energy (keV)",Clover+1);     
      hCloverABEn[Clover] = new TH1F(name,title,EN_SPECTRA_CHANS,0,EN_SPECTRA_MAX);
      sprintf(name,"TIG%02d Gated AB",Clover+1); 
      sprintf(title,"TIG%02d Gated Clover Add-Back Energy (keV)",Clover+1);     
      hCloverABEnGated[Clover] = new TH1F(name,title,EN_SPECTRA_CHANS,0,EN_SPECTRA_MAX);    
      for(Crystal=0;Crystal<CRYSTALS;Crystal++) {
         sprintf(name,"TIG%02d%c En",Clover+1,Num2Col(Crystal));
         sprintf(title,"TIG%02d%c Core Energy (keV)",Clover+1,Num2Col(Crystal));
         hCoreEn[Clover][Crystal] = new TH1F(name,title,EN_SPECTRA_CHANS,0,EN_SPECTRA_MAX);
         sprintf(name,"TIG%02d%c Gated",Clover+1,Num2Col(Crystal));
         sprintf(title,"TIG%02d%c Gated Core Energy (keV)",Clover+1,Num2Col(Crystal));
         hCoreEnGated[Clover][Crystal] = new TH1F(name,title,EN_SPECTRA_CHANS,0,EN_SPECTRA_MAX);
      }
   }   
   
	return 1;
}

int FinalCoincEff()	{

   cout << "Finalising...." << endl;

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
   
   outfile->Close();
   
	return 1;
}

// Function to parse Mnemonic name:
void ParseMnemonic(std::string *name,Mnemonic *mnemonic)	{
  std::string buf;
  mnemonic->system.assign(*name,0,2);
  mnemonic->subsystem.assign(*name,2,1);
  buf.clear();	
  buf.assign(*name,3,2);
  mnemonic->arrayposition = atoi(buf.c_str());
  mnemonic->arraysubposition.assign(*name,5,1);
  mnemonic->collectedcharge.assign(*name,6,1);
  buf.clear(); 
  buf.assign(*name,7,2);
  mnemonic->segment = atoi(buf.c_str());
  mnemonic->outputsensor.assign(*name,9,1);
}

int Col2Num(char Colour) {
   switch(Colour) {
      case 'B':
         return 0;
      case 'G':
         return 1;
      case 'R':
          return 2;
      case 'W':
         return 3;
      default:
         return -1; 
    }
}

char Num2Col(int Crystal) {
   switch(Crystal) {
      case 0:
         return 'B';
      case 1:
         return 'G';
      case 2:
         return 'R';
      case 3:
         return 'W';
      default:
         return 'X';
   }
}
          
