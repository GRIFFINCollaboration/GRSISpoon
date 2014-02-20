/*
 * Loop over all indexed events in a list of trees and call processEvent() and processFragment() declared
 *   elsewhere to construct relevant histograms. Works both in interactive ROOT session as well as in a
 *   compiled program.
 * Trees are determined by looking into all loaded files and looking for ones with a corresponding
 *   FragmentTree. Compiled program can pass list of files via command line arguments.
 ** /

#include <iomanip>
#include <iostream>
#include <set>
#include <vector>

#include <TChain.h>
#include <TFile.h>
#include <TIterator.h>
#include <TROOT.h>
#include <TStopwatch.h>

#include "TTigFragment.h"

void processFragment(TTigFragment *frag);
void processEvent(const std::vector<TTigFragment> &ev);

const long int MEM_SIZE = 3LL * 1000 * 1000 * 1000;
  /** The bigger the better - related to the amount of ram the program is ALLOWED to use
   *  will not necessarily use all this number.  For best performance, this number should be 
   *  at least as large as the largest file that will be sorted.  Large (2*filesize) is even 
   *  better.  Smaller than the file will result in a longer sort.
   *  Please make sure the RAM >> this number.
   *  This number is in bytes!
   *  with a 1.9 GB file:
   *  MEM_SIZE =   30000000  =                     (this is the default root size.)
   *  MEM_SIZE =  500000000  = 64.916842 seconds
   *  MEM_SIZE = 1000000000  = 61.716737 seconds
   *  MEM_SIZE = 2000000000  = 53.647293 seconds
   *  MEM_SIZE = 4000000000  = 46.794047 seconds
   *  MEM_SIZE = 6000000000  = 43.901112 seconds
   *  results will very depending on how 'out of order' the fragments are. */
 
TFile *outFile = NULL;

int process(void)
{
  static TChain *chain = new TChain("FragmentTree");

  chain->Reset();

  // find all the relevant files by looking in the big ROOT object
  TSeqCollection *files = gROOT->GetListOfFiles();
  TIterator *it = files->MakeIterator();
  TFile *f;
  TObject *obj;

  int numTrees = 0;

  while ( (obj = it->Next()) != NULL) {
    // find any files with FragmentTree in them
    f = (TFile *)obj;    
    obj = f->FindObjectAny("FragmentTree");
    if (obj) {
      chain->Add(f->GetName());
      numTrees++;
    }
  }
  TTigFragment *pFrag = 0;

  TStopwatch w;
  w.Start();
  int numChainEntries = chain->GetEntries();
  int treeNumber, lastTreeNumber = -1;
  
  // make an output file
  if (outFile == NULL) {
    outFile = new TFile("output.root", "recreate");
  }

  for (int i=0; i < numChainEntries; i++) {
    chain->LoadTree(i);
    treeNumber = chain->GetTreeNumber();

    if (treeNumber != lastTreeNumber) {
      std::cout << "Changing to tree number " << treeNumber
		<< " from " << lastTreeNumber 
		<< " at chain entry number " << i << std::endl;
      lastTreeNumber = treeNumber;
    } else {
      continue;
    }

    TTree *tree = chain->GetTree();
    TBranch *branch = tree->GetBranch("TTigFragment");
    
    branch->SetAddress(&pFrag);
    branch->LoadBaskets();
    // tree->SetCacheSize(MEM_SIZE);
    // tree->AddBranchToCache(branch, true);
    // tree->StopCacheLearningPhase();
    tree->SetMaxVirtualSize(MEM_SIZE);

    int numTreeEntries = tree->GetEntries();
    int numTreeEvents = (Int_t)tree->GetMaximum("TriggerId");
    std::vector<TTigFragment> ev;

    for (int j=0; j < numTreeEvents; j++) {
      ev.clear();
      Int_t fragno = 1;

      while (tree->GetEntryWithIndex(j, fragno++) != -1) {
	ev.push_back(*pFrag);
	outFile->cd();
	processFragment(pFrag);
	gROOT->cd();
      }
      if (!ev.empty()) {
	outFile->cd();
	processEvent(ev);
	gROOT->cd();
      }
      if ( (j % 1000) == 0 || j == numTreeEvents - 1) {
	std::cout << "Processing event " << j + 1 << " / " << numTreeEvents
		  << " from tree " << treeNumber + 1 << " / " << numTrees
		  << " time: " << std::setw(10) << w.RealTime()
		  << " sys time: " << std::setw(10) << w.CpuTime() << "   \r";
	w.Continue();
      }
    } // loop over the tree entries
    branch->DropBaskets("all");
    std::cout << std::endl;

    i += numTreeEntries - 10;
  } // loop over the entries in the chain (effectively looping over trees)

  return numChainEntries;
}

#ifndef __CINT__
int main(int argc, char **argv)
{
  // treat all command line arguments as files we want to chain
  for (int i=1; i < argc; i++) {
    new TFile(argv[i]);
  }
  process();
  outFile->Write();
}
#endif
