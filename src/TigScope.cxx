
#include "TigScope.h"
#include "TServer.h"

#include "TigInput.h"
#include "TParser.h"

#include "TFragmentQueue.h"

ClassImp(TigScope)

TigScope *TigScope::fTigScope = NULL;


TigScope *TigScope::instance(int argc, char** argv)	{
	if(!fTigScope)
		fTigScope = new TigScope(argc,argv);
//		fTigScope->SetMidasFile();
//	HandleOptions(argc<argv);
	
	return fTigScope;
}

TigScope::TigScope(int argc,char** argv)	{	
	TFragmentQueue::instance();
	fInteractiveMode	=	false;;
	fScopeMode			=	false;
	fIsOnline			=	false;
	fIsOffline			=	false;
	fTestMode			=	false;


	fmidasfile		=	0;
	fmidasevent		=	0;
	ftigfragment	= 0;

	wavehist = new TList();
	
	HandleOptions(argc,argv);
	
	fTigScope = this;		

	fTotalFragments = 0;

	SetOptions();
}

TigScope::~TigScope()	{	}


bool TigScope::ProcessMidasEvent(TMidasEvent *mevent)	{	
	if(!mevent)
		return false;
	//fMidasEventsProcessed++;
    //int NumFragsFound = 0;
	void *ptr;
	int banksize = 0;
	int testnumber = 0;
	switch(mevent->GetEventId())	{
		case 1:
			banksize = mevent->LocateBank(NULL, "WFDN", &ptr);
			if(banksize)    {
				fTotalFragments += TParser::instance()->TigressDATAToFragment((int*)ptr,banksize,mevent->GetSerialNumber(),mevent->GetTimeStamp());
			}
			break;
		default:
			break;
	};
	return true;
};

void TigScope::Initialize(void) {	}

void TigScope::BeginRun(int transition,int run,int time)	{
	printf("Begin run called.\n");
	fTotalFragments = 0;
//	fflush(stdout);
	CalibrationManager::instance()->ReadXMLOdb(GetODB());
	if(CalibrationManager::instance()->UseCALFromFile())
		CalibrationManager::instance()->ReadCalibrationFile();
	RootIOManager::instance()->OpenOutFile(run,GetSubRunNumber());  //GetRunNumber(),GetSubRunNumber());
	if(fTestMode)
		TFragmentQueue::instance()->StartStatusUpdate();
//	if(IsOnline())
//		TFragmentQueue::instance()->StartStatusUpdate();

//	printf( " done.\n");			
}

void TigScope::EndRun(int transition,int run,int time)		{
	printf("\nend run called.\t%i\t%i\n",TFragmentQueue::instance()->Size(),RootIOManager::instance()->FragProcessorIsOn());
	printf("\tTotal Fragments Extracted from midas file: " CYAN "%i" RESET_COLOR "\n",fTotalFragments); 
	//while(RootIOManager::instance()->FragProcessorIsOn())	{
	if(IsOnline())	{
		StopSignal();
		return;
	}
		while(TFragmentQueue::instance()->Size()!=0) {               
			printf("     %i fragments left to processes.      \r",TFragmentQueue::instance()->Size());
    		fflush(stdout);
			gSystem->Sleep(100);
			continue;
  		}
		printf("     %i fragments left to processes.      \n",TFragmentQueue::instance()->Size());
		StopSignal();
	//}
	return;
}




void TigScope::Finalize(void)	{	return;	}


void TigScope::StopSignal()	{
	printf(DRED "STOP SIGNAL!!\n" RESET_COLOR); fflush(stdout);
	RootIOManager::instance()->Stop();
	return;
}


bool TigScope::SetMidasFile(const char* filename)	{
	printf("trying to open %s \n",filename);

	if(!fmidasfile)
		fmidasfile = new TMidasFile();
	else	{
		fmidasfile->Close();		
	}
	
	
	return fmidasfile->Open(filename);
}


TMidasEvent *TigScope::ReadMidasFile()	{
	if(!fmidasfile)
		return 0;
	if(!fmidasevent)
		fmidasevent = new TMidasEvent();
	if(fmidasfile->Read(fmidasevent))	{
		if(!(fmidasevent->GetEventId()&0x8000))
			fmidasevent->SetBankList();
		return fmidasevent;
	}
	else
		return 0;
}


TTigFragment *TigScope::ExtractFragment(TMidasEvent *mevent)	{
	if(!mevent)
		return 0;
	if(mevent->GetEventId()==1)	{
		void *ptr;
		int banksize = mevent->LocateBank(NULL, "WFDN", &ptr);
		if(banksize)	
			fTotalFragments += TParser::instance()->TigressDATAToFragment((int*)ptr,banksize,mevent->GetSerialNumber(),mevent->GetTimeStamp());

		banksize = mevent->LocateBank(NULL, "GRF0", &ptr);
		if(banksize)	
			int NumberOfFrags = TParser::instance()->GriffinDATAToFragment((int*)ptr,banksize,mevent->GetSerialNumber(),mevent->GetTimeStamp());
	}
	return TFragmentQueue::instance()->Get();
};





bool TigScope::HandleOptions(int argc,char **argv)	{
   if(argc==0) {return true;}
	if(argc==1)	{
		PrintHelp();
		return false;
	}
		
   std::vector<std::string> args;
   for (int i=0; i<argc; i++)	{
	   if (strcmp(argv[i],"--help")==0 || strcmp(argv[i],"-help")==0)	{
	      PrintHelp();
	      //refresh();
	      break;
	   }
      args.push_back(argv[i]);
   }
   for(unsigned int i=1; i<args.size(); i++)	{	// loop over the commandline options
      std::string arg = args[i];
      if(arg[0] == '-')	{
         char val = arg[1];
         if(islower(val)) val = val + 'A' -'a';
			switch(val)	{
			case 'E':  // Set experiment name
			   if(arg[2] == '\0') {
				   if(i<argc-1 && (args[i+1])[0] != '-' ) { 
					   arg = args[++i];
					}   
					else {
					   arg.erase(0,2);
					}   		
					exptname = arg;//.c_str();
				}	
			   break;
			case 'H':  // Set hostname
			   if(arg[2] == '\0') {
			      if(i<argc-1 && (args[i+1])[0] != '-' ) {
					   arg = args[++i];
					}   
					else {
                  arg.erase(0,2);	
               }			
            }
            hostname = arg;//.c_str();
            break;
         case 'P':  // Set port number for server
            if(arg[2] == '\0') {
               if(i<argc-1 && (args[i+1])[0] != '-' ) {
                  arg = args[++i];
               }
               else {
                  arg.erase(0,2);
               }
            }
				TServer::instance(atoi(arg.c_str()));
            break;
			case 'F':  // Set filename
			   NumMFiles = 0;
		      if(arg[2] == '\0') {	      
		         while(i<argc-1 && (args[i+1])[0] != '-' ) {
		            arg = args[++i];
		            NumMFiles++;
		            mfileinname.push_back(arg);
				   }
				}   
		      else {
				   arg.erase(0,2);
				   NumMFiles++;
				   mfileinname.push_back(arg);//.c_str();
				}						
				fIsOffline = true;
				break;
			case 'O': // Set alternate ODB file
            if(arg[2] == '\0') {
				   if(i<argc-1 && (args[i+1])[0] != '-' ) {
					   arg = args[++i];
					}
					else {
					   arg.erase(0,2);
					}
            }   
				odbfname = arg;//.c_str();
				CalibrationManager::instance()->SetODBFileName(odbfname.c_str());
				break;
			case 'C':  // Set calibration file
			   if(arg[2] == '\0') {
				   if(i<argc-1 && (args[i+1])[0] != '-' ) {
					   arg = args[++i];
					}
					else {
					   arg.erase(0,2);
					}
            }
            calfname = arg;//.c_str();
            CalibrationManager::instance()->SetCalFileName(calfname.c_str());
				break;
			case 'I':  
            fInteractiveMode = true;
            break;
			case 'R':
            if(arg[2] == '\0') {
				   if(i<argc-1 && (args[i+1])[0] != '-' ) {
                  arg = args[++i];
               }
					else {
                  arg.erase(0,2);
               }
				}
				rfileinname = arg;//.c_str();
				break;
			case 'S':
					fScopeMode = true;
					break;
			case 'T':
					fTestMode	= true;
					break;
//				case 'H':
//					PrintHelp();
//					return false;
			default:
					printf("commmand %s not understood. ignoring %s, try --help.\n",arg.c_str(),arg.c_str());			
					break;
			};
		}
		else
			printf("commmand %s not understood. ignoring %s, try --help.\n",arg.c_str(),arg.c_str());
	}
	
	if(odbfname.length()>0)
		CalibrationManager::instance()->SetODBFileName(odbfname.c_str());
	
	if(mfileinname[NumMFiles-1].length()>0)	{
		SetMidasFile(mfileinname[NumMFiles-1].c_str());
		fIsOffline = true;
	}

	if(fTestMode)
		printf(DRED "  **** STARTED IN TEST MODE ****  " RESET_COLOR "\n");

	
	return true;
}


void TigScope::PrintHelp()	{
	printf( "Current Options Incudle:\n" );
	printf( DBLUE "\t--help              \t" DRED "print this menu." RESET_COLOR "\n");
	printf( DBLUE "\t-e <experiment name>\t" DRED "midas online experiment name." RESET_COLOR "\n");
	printf( DBLUE "\t-h <host name>      \t" DRED "midas online host name." RESET_COLOR "\n");
	printf( DBLUE "\t-f <midas file>     \t" DRED "midas data file, and sort the file." RESET_COLOR "\n");
	printf( DBLUE "\t-o <odb.xml>        \t" DRED "use odb saved to file, currently only xml format works." RESET_COLOR "\n");
	printf( DBLUE "\t-c <file.cal>       \t" DRED "read custom calibration file." RESET_COLOR "\n");
	printf( DBLUE "\t-p <port num>       \t" DRED "start server on port <port num>." RESET_COLOR "\n");
	//printf( DBLUE "\t-r <root file>      \t" DRED "root input file containing FragmentTree." RESET_COLOR "\n");

	printf( DBLUE "\t-i	\t" DGREEN "start program in interactive mode." RESET_COLOR "\n");
	//printf( DBLUE "\t-t	\t" DGREEN "start program in test mode." RESET_COLOR "\n");
	printf( DBLUE "\t-s	\t" DGREEN "start program in scope mode." RESET_COLOR "\n");
}


void TigScope::PrintState()	{
printf("TigScope's current state:\n");
if(exptname.length()>0)
	printf("\texperiment name is set to: " DBLUE "%s" RESET_COLOR "\n",exptname.c_str());
else
	printf("\texperiment name is set to: " DRED "null" RESET_COLOR "\n",exptname.c_str());

if(hostname.length()>0)
	printf("\thost name is set to:       " DBLUE "%s" RESET_COLOR "\n",hostname.c_str());
else
	printf("\thost name is set to:       " DRED "null" RESET_COLOR "\n",hostname.c_str());

if(mfileinname[NumMFiles].length()>0)
	printf("\tinput midas file name:     " DBLUE "%s" RESET_COLOR "\n",mfileinname[NumMFiles].c_str());
else
	printf("\tinput midas file name:     " DRED "null" RESET_COLOR "\n",mfileinname[NumMFiles].c_str());

if(odbfname.length()>0)
	printf("\todb file name is set to:   " DBLUE "%s" RESET_COLOR "\n",odbfname.c_str());
else
	printf("\todb file name is set to:   " DRED "null" RESET_COLOR "\n",odbfname.c_str());

if(calfname.length()>0)
	printf("\tcal file name is set to:   " DBLUE "%s" RESET_COLOR "\n",calfname.c_str());
else
	printf("\tcal file name is set to:   " DRED "null" RESET_COLOR "\n",calfname.c_str());

if(rfileinname.length()>0)
	printf("\tinput FragmentTree file:   " DBLUE "%s" RESET_COLOR "\n",rfileinname.c_str());
else
	printf("\tinput FragmentTree file:   " DRED "null" RESET_COLOR "\n",rfileinname.c_str());


if(fIsOnline)
printf("\tIs Online:                 " DBLUE "true" RESET_COLOR "\n");
else
printf("\tIs Online:                 " DRED  "false" RESET_COLOR "\n");

if(fIsOffline)
printf("\tIs Offline:                " DBLUE "true" RESET_COLOR "\n");
else
printf("\tIs Offline:                " DRED  "false" RESET_COLOR "\n");



if(fInteractiveMode)
printf("\tInteractive mode:          " DBLUE "true" RESET_COLOR "\n");
else
printf("\tInteractive mode:          " DRED  "false" RESET_COLOR "\n");

if(fScopeMode)
printf("\tScope mode:                " DBLUE "true" RESET_COLOR "\n");
else
printf("\tScope mode:                " DRED  "false" RESET_COLOR "\n");

}


void TigScope::Draw(TTigFragment *frag)	{
	if(!frag)		
		return;
	std::vector<int> *v = &(frag->wavebuffer);
	if(!v->size())
		return;
	const char *hisName = frag->ChannelName.c_str();;
	 	//TObject *obj = gROOT->FindObjectAny(hisName);
	TH1I *h;
	if(!(h = (TH1I*)wavehist->FindObject(hisName)))	{
		h = new TH1I(hisName, hisName, v->size(), 0, v->size());
		wavehist->Add(h);
	}
  for (Int_t i=0; i < v->size(); i++) {
    h->SetBinContent(i, v->at(i));
  }
	h->GetXaxis()->SetRangeUser(0,v->size()-2);
	h->Draw();
	return;
}




void TigScope::SetOptions()	{
	printf("Setting options.\n");
	//TigInput::instance()->PrintLogo(false);
	if(fmidasfile)	{
		fIsOffline = true;
		ExecuteLoop(fmidasfile);
	}
	else if(hostname.length()>0 && exptname.length()>0)	{
		fIsOnline = true;
		ExecuteLoop(0,0,(char*) hostname.c_str(),(char*) exptname.c_str());
	}
	else
		fInteractiveMode = true;

}



