
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>


#include "RootIOManager.h"
#include "TigScope.h"

//class TigScope;

RootIOManager *RootIOManager::fRootIOManager = 0;

RootIOManager *RootIOManager::instance()	{
	if(!fRootIOManager)
		fRootIOManager = new RootIOManager();
	return fRootIOManager;
}

RootIOManager::RootIOManager()	{
	//printf("RootIOManager created.\n");
	fouttree	= 0;
	frootfile = 0;	
	fonlinetree	= 0;
	fbufferfrag = 0;
	fRunningProcessor = false;
	foutlist = 0;
	fcounter = 0;
}

RootIOManager::~RootIOManager()	{	}



void RootIOManager::OpenOutFile(int runnumber,int subrunnumber,char *filename)	{
	printf("open outfile called.\n");
	printf("frootfile = 0x%08x\n",frootfile); fflush(stdout);
	if(frootfile)	{
		//return;  // i shouldn't have to do this.
		printf("Warning: last root output file(%s) left opened, attempting to close it.\n",frootfile->GetName());
		frootfile->Close();
		frootfile->Delete();
	}
	if(runnumber==0)	{
		frootfile = new TFile(filename,"RECREATE");
	}
	else	{
		std::ostringstream tmpname;
		tmpname << "fragment" << std::setfill('0') << std::setw(5) << runnumber;
		printf("... subrunnumber is equal to %i\n",subrunnumber);
		if(subrunnumber >= 0) 
			tmpname << std::setfill('0') << "_" << std::setw(3) << subrunnumber;
		tmpname << ".root";
		//tmpname += std::to_string((long long int)runnumber);
		//tmpname += "_";
		//tmpname += std::to_string((long long int)subrunnumber);
		//tmpname += ".root";
		frootfile = new TFile(tmpname.str().c_str(),"RECREATE");
	}
	printf("Opened output file: %s\n",frootfile->GetName());
	
	frootfile->SetCompressionSettings(1);

	SetUpOutTree();
	StartFragmentProcessor();
	return;

}

void RootIOManager::SetUpOutTree()	{
	printf("Initiallizing tree... ");
	if(fouttree)	{

		delete frootfile;
	}
	if(!frootfile)	{
		printf("\n\tno root file open!! tree not opened!\n");
		return;
	}
	frootfile->cd();
	fouttree = new TTree("FragmentTree","FragmentTree");
	fouttree->SetDirectory(frootfile);
	fbufferfrag = 0;
	fouttree->Branch("TTigFragment","TTigFragment",&fbufferfrag,1000,99);
	//fouttree->SetAutoFlush(30000000);
	//fouttree->SetAutoSave(300000000);
	fouttree->SetMaxVirtualSize(2 * 1000 * 1000 * 1000);
	fouttree->AutoSave();
	
	printf("done!\n");
	return;

};

void RootIOManager::SetUpOnlineTree()	{
	return;
};


void RootIOManager::StartFragmentProcessor()	{
	std::thread FragmentProcessor(&RootIOManager::HandleFragments,this);
	fRunningProcessor = true;	
	//printf("\nthis->FragProcessorIsOn() = %i\n",this->FragProcessorIsOn()); 
	
	FragmentProcessor.detach();
	return;
}


void RootIOManager::HandleFragments()	{
	//RootIOManager *myroot = (RootIOManager*)ptr;
	while(fRunningProcessor)	{
		if(TFragmentQueue::instance()->Size()==0)	{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			continue;
		}
		TTigFragment *fragment = TFragmentQueue::instance()->PopFragment();
		FragmentSwitchBoard(fragment);
	}
	return;
}

void RootIOManager::FragmentSwitchBoard(TTigFragment *fragment)	{
	if(!fragment)
		return;
	// if(TigScope::instance()->IsOffline())
		FillTree(fragment);
	delete fragment;
	//fragment->Delete();
	return;
}

void RootIOManager::FillTree(TTigFragment *frag)	{
	if(!fouttree)
		return;
	fbufferfrag = frag;
	if((fcounter++) == 10)	{
		//fouttree->OptimizeBaskets(10000000,1.1,"d");	
		fouttree->OptimizeBaskets(10000000,1.1,"");
	}
	if(fcounter%500000==0)	{
		fouttree->DropBuffers(1);
	}

	//if(fcounter%1000==0) {
	//	fouttree->AutoSave("SaveSelf"); //allows me to read the tree while writing, but reallllly slow.
	//}
	
	fouttree->Fill();
	return;
}


void RootIOManager::Stop()	{
	fRunningProcessor = false;
	CloseRootFile();
	return;
}

bool RootIOManager::CloseRootFile()	{
	if(!frootfile)
		return false;
	frootfile->cd();
	
	if(fouttree)	{
		//fouttree->Write();
		//fouttree = (TTree*)frootfile->Get("FragmentTree");
		printf("\nBuilding index...	");
		fflush(stdout);
		fouttree->BuildIndex("TriggerId","FragmentId");     
		printf("  Done\n");
		fflush(stdout);

		if((fouttree->GetTreeIndex()->GetN() *64) > 0x70000000)     {
			printf("Index to large to write to file.\n");
			printf("If built events are needed, remember to BuildIndex(\"TriggerId\",\"FragmentId\") before sorting the tree!\n");
			fouttree->GetTreeIndex()->Delete();
			fouttree->SetTreeIndex(0);
		}
		fouttree->FlushBaskets();
		fouttree->Write();
	}
	
	if(foutlist)	{
		//foutlist->Write();
	}
	
	frootfile->Close();
	frootfile->Delete();

	frootfile	= 0;
	fouttree	= 0;

	return true;
}

TH1 *RootIOManager::MakeHitPattern()	{
	if(!fouttree)
		return 0;
	fouttree->AutoSave();
	fouttree->Project("h(3000,0,3000)","ChannelNumber");
	return (TH1*)gDirectory->Get("h");
};



TH1 *RootIOManager::Make1DProjection(std::string command,std::string gate)	{
	if(!fouttree)
		return 0;
	fouttree->AutoSave();
	fouttree->Project("hist(16000,0,64000)",command.c_str(),gate.c_str());
	TH1 *junk = (TH1*)gDirectory->Get("hist");
	return junk;
}


TH1 *RootIOManager::Make2DProjection(std::string command,std::string gate)	{
	if(!fouttree)
		return 0;
	fouttree->AutoSave();
	fouttree->Project("hist(4000,0,16000,4000,0,16000)",command.c_str(),gate.c_str());
	TH1 *junk = (TH1*)gDirectory->Get("hist");
	return junk;
}










