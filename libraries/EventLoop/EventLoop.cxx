#include "EventLoop.h"


#include "CalibrationManager.h"
//#include "RootManager.h"
#include <TTreeIndex.h>

EventLoop *EventLoop::fEventLoop = NULL;

EventLoop	&EventLoop::Get(void)	{
	if(!fEventLoop)	{
		printf("somethings wrong...\n");
	}
	return *fEventLoop;
}

EventLoop::EventLoop()	{
	//fOutputFile 				=	0;
	//fOutputDir					=	new TDirectory("Home","Home");
	fODB						=	0;
	fCurrentRunNumber 			=	0;
	fCurrentEventNumber 		=	0;
	fIsOffline 					= 	false;
	fPause 						=	false;  
	fStop						=	false;
	fMidasEvent					=	new TMidasEvent();
	fMidasFile					=	NULL;	
	fMidasOnline				=	NULL;
	fEventLoop 					=	this;
	fTestMode					=	false;
	
}

EventLoop::~EventLoop (){
	Finalize();
  if(fODB) delete fODB;
  //CloseOutputFile();
}

void EventLoop::Initialize(void)	{	}
void EventLoop::BeginRun(int transition,int run,int time)	{	}
void EventLoop::EndRun(int transition,int run,int time)	{	}
void EventLoop::Finalize()	{	}

//void EventLoop::HandleCommand(char val,std::string arg)	{
//	printf("commmand %s not understood. ignoring %s.\n",arg.c_str(),arg.c_str());					
//	return;
//}


int EventLoop::ExecuteLoop(TMidasFile *mfile,char *odbfname,char *hostname,char *exptname){  //int argc, char **args){

	//char *filename = args[0];
	//char *odbfname;
	//char *hostname;
	//char *exptname;


//	if(mfile || (hostname && exptname))	{
		//if(tcpPort == 0)
		//	tcpPort = 9099;

//		if(fIsOffline) {
	
		if(mfile)	{
			printf("filename = %s\n",mfile->GetFilename());
			std::thread MidasThread(&EventLoop::ProcessMidasFile, this, mfile);	
			MidasThread.join();      //creatres a thread and holds open till the thread terminates.   pcb.
			//MidasThread.detach();
		}
		else if(hostname && exptname)	{
			std::thread MidasThread{&EventLoop::ProcessMidasOnline, this, hostname, exptname, odbfname};
			MidasThread.join();
			//MidasThread.join();
			//in
		}
		else	{
			return 1;
		}
	//}
	return 0;
}


/*
int EventLoop::ExecuteLoop(char *filenaname){
	if(!this->Getfmidasfile)


		fmidasfile = new TMidasFile();
	else
		fmidasfile->Close();
	fmidasfile->Open(filename);
  if(fmidasfile)  {
    printf("filename = %s\n",filename);
     std::thread MidasThread(&EventLoop::ProcessMidasFile, this, fmidasfile);
     //MidasThread.detach();
		 MidasThread.join();
	}
	return 0;
}
*/










//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
void EventLoop::ProcessMidasFile(TMidasFile *midasfile)	{
	//fMidasFileName = fname;
	//printf("fname = %s\n",fMidasFileName.c_str());
	//if(fMidasFile)	{
	//	fMidasFile->Close();	
	//	delete fMidasFile;
	//}
	//fMidasFile = new TMidasFile();
	if(!midasfile)
		return;
	//if(!fMidasFile->Open(fMidasFileName.c_str()))	{
	//	printf("problem opening midas file: %s\n",fname);
		//printf("file returned false?\n");
		//refresh();
	//	return;
	//}
	//and lets try to get the file size...
	std::ifstream in(midasfile->GetFilename(), std::ifstream::in | std::ifstream::binary);
	in.seekg(0, std::ifstream::end);
	long long filesize = in.tellg(); 
	in.close();

	Initialize();

	//read one event and try to get the odb....
	fMidasEvent->Clear(); 
	if(!midasfile->Read(fMidasEvent))	{
		printf(DMAGENTA "\tFound no events in %s!!!!\n" RESET_COLOR, midasfile->GetFilename());
		return;
	}
	if((fMidasEvent->GetEventId()&0xffff)!=0x8000)	{
		printf(DMAGENTA "WARNING: Begining of run not found: not setting odb!\n" RESET_COLOR);
	}
	else	{

		if(fODB)
			delete fODB;
		if(CalibrationManager::instance()->UseODBFromFile())	{
			fODB = new XmlOdb(CalibrationManager::instance()->GetODBFileName());
			printf("ODB set from %s.\n",CalibrationManager::instance()->GetODBFileName());
		}
		else	{	
			fODB = new XmlOdb(fMidasEvent->GetData(),fMidasEvent->GetDataSize());
			printf("Read ODB from midas file.\n");
		}
	}
			

		
	fFirstTime = fMidasEvent->GetTimeStamp();
	fCurrentRunNumber = fMidasEvent->GetSerialNumber();
	//CreateOutputFile(fCurrentRunNumber);
	fCurrentEventNumber	= 0;
	long long bytesread	= 0;
	int bytes			= 0;

	BeginRun(0,fCurrentRunNumber,0); // <-- set the calibration info in here!!

	while(true)	{
		int eventId = fMidasEvent->GetEventId();
		eventId = eventId & 0xffff;
		switch(eventId)	{
			case 0x8000:	//start of run
				printf( DGREEN );
				fMidasEvent->Print();  
				printf( RESET_COLOR );
				break;
			case 0x8001:	//end of run
			printf("Processing event %i have processed %.2fMB/%.2fMB\n",fCurrentEventNumber,(bytesread/1000000.0),(filesize/1000000.0));    ////Event Count Printing.
				printf( DRED);
				fMidasEvent->Print();
				printf(RESET_COLOR);
				break;
			default:			
				fMidasEvent->SetBankList();
				ProcessMidasEvent(fMidasEvent);
				break;		
		};    
		if(((++fCurrentEventNumber)%1250)==0)	{
			printf("Processing event %i have processed %.2fMB/%.2fMB                \r",fCurrentEventNumber,(bytesread/1000000.0),(filesize/1000000.0));    ////Event Count Printing.
			//gSystem->Sleep(100);  ///handicapped!!
		}
		fMidasEvent->Clear();
		bytes = midasfile->Read(fMidasEvent);
		if(bytes == 0){
			printf(DMAGENTA "\tfile: %s ended on %s" RESET_COLOR "\n",midasfile->GetFilename(),midasfile->GetLastError());
			break;
		}
		bytesread += bytes;
	}
	printf("Read %i MIDAS events from file %s.\n",fCurrentEventNumber,midasfile->GetFilename());

	EndRun(0,fCurrentRunNumber,0);
	SendStop();
	//fmidiasfile.Close();
}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//

void onlineBeginRunHandler(int transition,int run, int time)	{
 // EventLoop::Get().CreateOutputFile(run);
  EventLoop::Get().SetCurrentRunNumber(run);
  EventLoop::Get().BeginRun(transition,run,time);
}


void onlineEndRunHandler(int transition,int run,int time)
{
	EventLoop::Get().SetCurrentRunNumber(run);
 	EventLoop::Get().EndRun(transition,run,time);
  //TRootanaEventLoop::Get().CloseRootFile();
}

static bool onlineEventLock = false;

void onlineEventHandler(const void *pheader, const void *pdata, int size)	{
	//printf("here.\n");
  if(onlineEventLock) {
		printf("still processing last event, discarding event...\n");
		return;
	}
  onlineEventLock = true;

  TMidasEvent event;
  memcpy(event.GetEventHeader(), pheader, sizeof(TMidas_EVENT_HEADER));
  event.SetData(size, (char*)pdata);
  event.SetBankList();
  
  /// Set the midas event pointer in the physics event.
  //EventLoop::Get().GetDataContainer()->SetMidasEventPointer(event);

  // Now pass this to the user event function.
  // EventLoop::Get().ProcessMidasEvent(*EventLoop::Get().GetDataContainer());
  EventLoop::Get().ProcessMidasEvent(&event);

  // Cleanup the information for this event.
  //EventLoop::Get().GetDataContainer()->CleanupEvent();

  //TRootanaEventLoop::Get().ProcessEvent(event);
  onlineEventLock = false;
}


void MidasPollHandlerLocal()
{
  if (!(TMidasOnline::instance()->poll(0)))
    gSystem->ExitLoop();
}

void EventLoop::ProcessMidasOnline(const char *hostname, const char *exptname, const char *oname)	{
	fMidasOnline = TMidasOnline::instance();

	int err = fMidasOnline->connect(hostname,exptname,"ts");//"peter's toolkit");
	if(err)	{
		printf("Cannont connect to MIDAS sever at host, expt: %s %s\n",hostname, exptname);
		return;
	}


	fODB = fMidasOnline;
	fCurrentRunNumber = fODB->odbReadInt("/runinfo/Run number");
	bool startnow = false;
	if (fODB->odbReadInt("/Runinfo/State") == STATE_RUNNING) {
		startnow = true;
	}

	if(oname)	{
		fODB = new XmlOdb(oname);
		printf("ODB set from %s.\n",oname);
	}
	else	{
			printf("ODB set from online source.\n");
	}

	//fCurrentRunNumber = fODB->odbReadInt("/runinfo/Run number");
	//CreateOutputFile(fCurrentRunNumber);

	if (startnow) {
		BeginRun(0,fCurrentRunNumber,0);
	}

	fMidasOnline->setTransitionHandlers(onlineBeginRunHandler,onlineEndRunHandler,NULL,NULL);
	fMidasOnline->registerTransitions();
	fMidasOnline->setEventHandler(onlineEventHandler);
	fMidasOnline->eventRequest("SYSTEM",1,TRIGGER_ALL,GET_NONBLOCKING);  

	TPeriodicClass tm(10,MidasPollHandlerLocal);

	while(!fStop)	{
		gSystem->ProcessEvents();
		gSystem->Sleep(1);
	}
	//TApplication *app = new TApplication("app",0,0);
	//app->Run(true);

   fMidasOnline->disconnect();
   return ;

}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//



//void EventLoop::movedir( TDirectory* olddir, TDirectory* newdir ) {
//  TList* list1= olddir->GetList();
//  TIter iter( list1 );
//  TObject* obj= 0;
//  while( obj= iter.Next() ) {
//    if( obj->InheritsFrom( "TH1" ) ) {
      // TH1::SetDirectory does all the work for us:
//      ((TH1*)obj)->SetDirectory( newdir );
//    }
//    else if( strcmp( obj->ClassName(), "TDirectory" ) == 0 ) {
      // Have to do it by hand recursively for TDirectory:
//      list1->Remove( obj );
//      TDirectory* dir= newdir->mkdir( obj->GetName() );
//      movedir( (TDirectory*)obj, dir );
//    }
//  }    
//	return;
//}

//bool EventLoop::CloseOutputFile(){
/*
  if(fOutputFile) {
  	fOutputFile->cd();
  	
  	TTree *tree = RootManager::instance()->GetTree();

    RootManager::instance()->GetTree()->Write();

		tree = (TTree*)fOutputFile->Get("FragmentTree");

		//printf("tree file =\t%s\n",	RootManager::instance()->GetTree()->GetCurrentFile()->GetName());

*/

//***********************************************************************//
//***********************************************************************//
//***********************************************************************//
    //so, if the index is large than a gb it crashes the sort and the tree doesn't save.
    //the simpliest (i.e. what I am doing right now fix) is to take this out and run the line:
    //tree->BuildIndex("TriggerId","FragmentId");	before the i want to make hist/mat/or physics trees sort,
    //currently done in another file.  This adds < 1 min to the next stage sorting and stops me have to wait 10-15 min to resort the tree.
    // stupid root.   
 /* 
		printf("\nBuilding index...");
		fflush(stdout);
		tree->BuildIndex("TriggerId","FragmentId");	
		printf("  Done\n");
		fflush(stdout);

		if((tree->GetTreeIndex()->GetN() *64) > 0x70000000)	{
			printf("Index to large to write to file.\n");
			printf("If built events are needed, remember to BuildIndex(\"TriggerId\",\"FragmentId\") before sorting the tree!\n");
			tree->GetTreeIndex()->Delete();
			tree->SetTreeIndex(0);
		}
*/
//***********************************************************************//  
//***********************************************************************//
//***********************************************************************//
//***********************************************************************//

/*

//    RootManager::instance()->GetTree()->Write();
//		RootManager::instance()->GetTree()->GetCurrentFile()->cd();

    //fOutputFile->Write();
//		if(fOnlineHistDir)	{
//			printf("writing online hist dir to file....");
//			movedir(fOnlineHistDir,fOutputFile);
//		}
	
    RootManager::instance()->GetTree()->FlushBaskets();	
    RootManager::instance()->GetTree()->Write();

		// fOutputFile = RootManager::instance()->GetTree()->GetCurrentFile();
//	  fOutputFile->Write();
		fOutputFile->Close();
		fOutputFile->Delete();	
		//  delete fOutputFile;
		fOutputFile = 0;

		printf("\tdone.\n");
		//return true;
  } 
	if(fmidasfile)	{
		fmidasfile->Close();
		delete fmidasfile;
		fmidasfile = NULL;
	}
	if(fmidasonline)	{
		fmidasonline->disconnect();
		fmidasonline = NULL;
	}

*/
//	return true;
	//return false;
//}

/*
bool EventLoop::CreateOutputFile(int run, std::string options)	{

	if(fOutputFile)	{
		CloseOutputFile();
	}

  char filename[32];
  sprintf(filename, "fragment%05d.root", run);
	fOutputFile = new TFile(filename,options.c_str());

	printf("Opened output file with name:\t%s\n",filename);

	//RootManager::instance()->SetUpTree(fOutputFile);

	if(fOutputFile)	
		return true;
	return false;
}
*/
