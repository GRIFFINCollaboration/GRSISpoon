#ifndef TTIGOFRAME_H
#define TTIGOFRAME_H

#define INITIAL_HEIGHT 500
#define INITIAL_WIDTH 700
#define MCA_SIZE 32768



#include <TGFrame.h>
#include <TGMenu.h>
#include <TGApplication.h>
#include <TApplication.h>
#include <TGClient.h>
#include <TGTab.h>
#include <TGButton.h>
#include <TGNumberEntry.h>
#include <TGLabel.h>
#include <TGTextEntry.h>
#include <TGFileDialog.h>
#include <TGStatusBar.h>

#include <TRootEmbeddedCanvas.h>

#include <TH1.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TF1.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <cstdio>





enum Commands	{//commands for the menu bar popups

        FILE_EXIT,
        FILE_OPEN,
        BOOT_BUTTON,
        ABOUT,
        DISPLAY,	
        READ_WF,
        ANLY_WF,
        SAVE_SEC,
				FRONTEND_NUMBER,
				SLAVE_NUMBER,
				PORT_NUMBER,
				CHANNEL_NUMBER,
        MODULE_NUMBER,
        MODULE_NUMBER_MCA,
        CHANNEL_NUMBER_MCA,
        ASG,
        BASELINE,
        EFILTER,
        TFILTER,
        EXTTRIG,
        TFILTEROR,
        CFDS,
        CSRA,
        PULSE,
        DECAY,
        MAXEVENT,
        FILE_SAVE,
        MODVAR,
        CHANVAR,
        CLEARMCA,
        SAVEMCA,
        REFRESHMCA,
        STOPMCA,
        STARTMCA,
        CONTINUEMCA,
        MCACHECKBUTTON,
        HISTOGRAM,
        MAXMIN,
        FIND_WF,
        SCOPEDT,
        MODCSRB,
        FINDTAU,
        SAVEHISTO,
        STARTRUN,
        STOPRUN,
        BASELINERUN,
        ENDRUN,
        TEST,
        BUTTON1,
        BUTTON2,
        BUTTON3
				
};


class TTigOFrame : public TGMainFrame	{
	public:
		TTigOFrame();
		TTigOFrame(const TGWindow *p);
		~TTigOFrame();

	private:
		TGFileInfo fEventFileOpenInfo;
		TGTextEntry *StateMsgFold1;
		TGTextButton *button1,*button2,*button3;
		TGStatusBar *fStatusBar;

		//TMidasFile *midasfile;
		//TFile *fragmentfile;


		TGNumberEntry *numericFrontend;           
		TGNumberEntry *numericSlave;            
		TGNumberEntry *numericPort;           
		TGNumberEntry *numericChannel;            

		TH1I *fCurrentTrace;
		TH1I *fCurrentHisto;
		TCanvas *dCanvasF1;
		TObject *selected;

	  Pixel_t color;
	
		int xmin, xmax, ymin, ymax;
		int frontend,slave,port,channel;
	  int parts[4];

		bool ProcessMessage(Long_t msg, Long_t parm1, Long_t);
		void HandleCommand(int,long,long);
		void HandleMenu(long,long);
		void HandleButton(long,long);

		void CloseWindow();
		void CreateMenuBar(void);
		void MakePanel(TGCompositeFrame *TabPanel);
		//void GetNewTrace()

	

};




































#endif
