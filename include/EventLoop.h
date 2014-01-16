#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <cstdio>
//#include <vector>
#include <fstream>
#include <iostream>

#include "TMidasFile.h"
#include "TMidasOnline.h"
#include "VirtualOdb.h"
#include "TMidasEvent.h"
#include "TPeriodicClass.hxx"
#include "XmlOdb.h"
#include "HttpOdb.h"

#ifndef __CINT__
#include <thread>
#include "midas.h"
#endif

#include <TSystem.h>

#include "Globals.h"

class EventLoop	{

	public:
		virtual ~EventLoop ();
		static EventLoop &Get(void);
  
		/// The main method, called for each event.  Users must implement this function!
		virtual bool ProcessMidasEvent(TMidasEvent *event) = 0;
	
		/// Called after the arguments are processes but before reading the first event is read
		virtual void Initialize(void);
  
		/// Called before the first event of a file is read, but you should prefer
		/// Initialize() for general initialization.  This method will be called
		/// once for each input file.  
		virtual void BeginRun(int transition,int run,int time);
  
		/// Called after the last event of a file is read, but you should prefer
		/// Finalize() for general finalization.  This method will be called once
		/// for each input file.	
		virtual void EndRun(int transition,int run,int time);
  
		/// Called after the last event has been processed, but before any open
	  	/// output files are closed.
  		virtual void Finalize(void);

		//virtual void HandleCommand(char val,std::string arg);

    	/// Are we processing online data?
		bool IsOnline() const {return !fIsOffline;};
  
		/// Are we processing offline data?
		bool IsOffline() const {return fIsOffline;};
  
		//bool Status() {	return !fStop;};
		int  Status() {	return fCurrentEventNumber;};

		bool SendStop() {fStop = true; };

		//void SetOutputDir(std::string name,std::string title) { 
		//	if(!fOutputDir) 
		//		fOutputDir = new TDirectory(name.c_str(),title.c_str());
		//};

		//TDirectory *GetOutputtDir() {return fOutputDir;};

		/// Method to start the corrct Midas thread baised on the information read in, either as file or online.
//		int ExecuteLoop(TMidasFile *midasfile,char *odbname = 0,char *hostname = 0, char *exptname = 0); //int argc, char *argv[]);
		int ExecuteLoop(TMidasFile *midasfile,char *odbname = 0,char *hostname = 0, char *exptname =0 ); //int argc, char *argv[]);
//		int	ExecuteLoop(char*);

		//std::thread *MidasThread;
		//Midas threads..
		void ProcessMidasFile(TMidasFile *midasfile);
		void ProcessMidasOnline(const char* hostname, const char* exptname, const char *oname);

		  /// This static templated function will make it a little easier
		  /// for users to create the singleton instance.
//		  template<typename T>
//		  static void CreateSingleton()
//	 	 {	
//	    	if(fEventLoop)
//		      std::cout << "Singleton has already been created" << std::endl;
//		    else
//	    	  fEventLoop = new T();
//		  } 
 
		/// Get pointer to ODB variables
		VirtualOdb* GetODB(){return fODB;}

		void SetCurrentRunNumber(int run)	{ fCurrentRunNumber = run;		};
		
		int  GetCurrentRunNumber()			{ return	fCurrentRunNumber;	};

		int GetCurrentEventNumber() const 	{ return fCurrentEventNumber;	};

		time_t GetRunStartTime() 			{ return fFirstTime;			};

		//TFile *GetRootFileOut()	{	return fOutputFile;};

		//int GetPort()	{return tcpPort;};

		//bool InCommandMode()	{return fCommandMode;};

		bool InTestMode()	{	return fTestMode;};


		//std::string GetFileName() {if(!fmidasfile) return ""; return fmidasfile->GetFilename();

		//bool CreateOutputFile(int run, std::string options = "RECREATE");
	   	//bool CloseOutputFile();

	protected:

		EventLoop();
		/// The static pointer to the singleton instance.
		static EventLoop* fEventLoop;

		/// TDirectory for online histograms.
		//TDirectory* fOutputDir;

		//void movedir(TDirectory*,TDirectory*);
	
	private:
  
		/// Output ROOT file
		//TFile *fOutputFile;

		/// Pointer to the ODB access instance
		VirtualOdb* fODB;
 
		//time the run started, (time of first event in the file/got when connected onine)		
		time_t fFirstTime;

		/// Are we processing offline or online data?
		bool fIsOffline;

		bool fStop;

		/// Current run number
	 	int fCurrentRunNumber;

		// tcp port
		//int  tcpPort;

		int fCurrentEventNumber;

		bool fPause;
	
		std::string fMidasFileName;

		TMidasFile	 *fMidasFile;
		TMidasEvent	 *fMidasEvent;
		TMidasOnline *fMidasOnline;

		bool fTestMode;

	ClassDef(EventLoop,0);
		
};



#endif 


