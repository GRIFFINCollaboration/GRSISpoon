//
//    Short and sweet program. Finds all the 1d histograms in a tfile by
//    itterating over the keys, than turn each of them into a fortran formatted 
//    .spe file used by radware.  Histograms are truncated at 16384 bins
//    as that is the radware limit, no rebinning is done here.               pcb.
//
//
//to compile:
//   g++ RootToSpe.cxx -oRootToSpe `root-config --cflags --libs`
//
//ro run:
//   ./RootTospe rootfile.root
//



#include<stdint.h>
#include<fstream>
#include<iostream>

#include<string.h>

#include<TFile.h>
#include<TH1.h>
#include<TSystem.h>
#include<TList.h>
#include<TClass.h>
#include<TKey.h>
#include<TTimeStamp.h>


struct SpeHeader {
  int32_t buffsize;          /*fortran file, each record starts with record size */            // 14
  char label[8]; 
  int32_t size;
  int32_t junk1;
  int32_t junk2;
  int32_t junk3;
  int32_t buffcheck;         /*fortran file, record ends with record size :) */                // 14
} __attribute__((packed));


//the above would be followed by an integer of bin size * 4
//the value of all bins in int sizes
//an integer os bin size * 4           ------- number of char in the histogram.

void WriteHist(TH1*,fstream*);

int main(int argc, char** argv)	{	

	TFile *infile = new TFile();	
	if(argc < 2  || !(infile = TFile::Open(argv[1],"read")) )	{
		printf ( "problem opening file.\nUsage: RootToNsm file.root\n");
		return 1;
	}

	//std::string outfilename = infile->GetName();
	//outfilename.erase(outfilename.find_last_of('.'));
	//outfilename.append(".spe");
	//fstream outfile;
	//outfile.open(outfilename.c_str(), std::ios::out | std::ios::binary);
	
	TList *keys = infile->GetListOfKeys();
	keys->Sort();
	TIter next(keys);
	TList *histstowrite = new TList();
	//int counter = 1;
	while( TKey *currentkey = (TKey*)next() ) {
		std::string keytype = currentkey->ReadObj()->IsA()->GetName();
		if(keytype.compare(0,3,"TH1")==0)	{
			//printf("%i currentkey->GetName() = %s\n",counter++, currentkey->GetName());
			//if((counter-1)%4==0)
			//	printf("*****************************\n");
			histstowrite->Add(currentkey->ReadObj());
		}
	}

	//printf("histstowrite->GetSize() = %i\n", histstowrite->GetSize());
	
	TIter nexthist(histstowrite);

	while( TH1 *currenthist = (TH1*)nexthist() ) {
		std::string outfilename = currenthist->GetName();
		outfilename.append(".spe");
		fstream outfile;
		outfile.open(outfilename.c_str(), std::ios::out | std::ios::binary);
		WriteHist(currenthist, &outfile);
		printf("\t%s written to file %s.\n",currenthist->GetName(),outfilename.c_str());
		outfile.close();
	}

	//printf("closing file %s.\n",outfilename.c_str());
	//outfile.close();

	return 0;
}


void WriteHist(TH1 *hist,fstream *outfile)	{
	SpeHeader spehead;
	spehead.buffsize = 24;
  	strncpy(spe.label,hit->GetName(),8); 
	if(hist->GetNbinsX() >4095)	{
	  	spehead.size = hist->GetNbinsX();
	}
	else 	{
		spehead.size = 4096;
	}
	spehead.junk1 = 1;
	spehead.junk2 = 1;
	spehead.junk3 = 1;
	spehead.buffcheck = 24;         /*fortran file, record ends with record size :) */                // 14


	outfile->write((char*)(&spehead),sizeof(SpeHeader));	

	int32_t histsizeinbytes = spehead.size *4;

	outfile->write((char*)&histsizeinbytes,sizeof(int32_t));	
	float bin = 0.0;
	for(int x=1;x<=spehead.size;x++)	{
		if(x<=hist->GetNbinsX())	{
			bin = (float)hist->GetBinContent(x);
			outfile->write((char*)&bin,sizeof(int32_t));	
		}
		else {
			bin = 0.0;
			outfile->write((char*)&bin,sizeof(int32_t));	
		}
	}

	outfile->write((char*)&histsizeinbytes,sizeof(int32_t));	

	return;	
}


