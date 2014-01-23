

#include "TTigOFrame.h"

TTigOFrame::TTigOFrame(const TGWindow *p)	{
	

	CreateMenuBar();
  SetWindowName("TIGRESS Oscilloscope");
  MapSubwindows();
  MapWindow();
  Resize(INITIAL_WIDTH, INITIAL_HEIGHT);
  SetCleanup(kDeepCleanup);

	fCurrentTrace	=	0;
	fCurrentHisto	=	0;
	selected			=	0;
	
	xmin = 0;
  xmax = 8192;
  ymin = 0;
  ymax = 4096;

	
	
}

TTigOFrame::~TTigOFrame()	{  
	CloseWindow();
}

void TTigOFrame::CloseWindow()
{
  // this->Delete();
  // gApplication->Terminate(0);
  TGMainFrame::CloseWindow();
}



void TTigOFrame::CreateMenuBar()	{
	TGMenuBar *MenuBar = new TGMenuBar(this,1,1,kHorizontalFrame);

	TGPopupMenu *MenuFile = new TGPopupMenu(fClient->GetRoot());
	MenuFile->AddEntry("&Open",FILE_OPEN);
	MenuFile->AddEntry("E&xit",FILE_EXIT);
	MenuFile->AddSeparator();
	MenuFile->AddEntry("&About",ABOUT);
	MenuFile->Associate(this);
	MenuBar->AddPopup("&File",MenuFile,new TGLayoutHints(kLHintsTop|kLHintsLeft,0,0,0,0));

	
	TGPopupMenu *MenuSetup = new TGPopupMenu(fClient->GetRoot());
	MenuSetup->AddEntry("&Display",DISPLAY);
	MenuSetup->AddEntry("&Histogramming", HISTOGRAM);
	MenuSetup->Associate(this);
	MenuBar->AddPopup("&Channel Setup", MenuSetup, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	
	TGPopupMenu *MenuRun = new TGPopupMenu (fClient->GetRoot ());
	MenuRun->AddEntry("&Start Run", STARTRUN);
	MenuRun->AddEntry("Sto&p Run", STOPRUN);  
	MenuRun->Associate(this);
	MenuBar->AddPopup("&Run Control", MenuRun, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));

	TGPopupMenu *MenuScope = new TGPopupMenu (fClient->GetRoot ());
	
	MenuScope->Associate(this);
	MenuScope->AddEntry("Test", TEST);
  MenuBar->AddPopup("&Scope", MenuScope, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));

	this->AddFrame(MenuBar,new TGLayoutHints(kLHintsTop|kLHintsLeft|kLHintsExpandX,0,0,0,0));
	
	TGTab *TabPanel = new TGTab (this);
  this->AddFrame(TabPanel, new TGLayoutHints(kLHintsBottom|kLHintsExpandX|kLHintsExpandY, 0, 0, 0, 0));
  TGCompositeFrame *Tab1 = TabPanel->AddTab("");

  MakePanel(Tab1);
}


void TTigOFrame::MakePanel(TGCompositeFrame * TabPanel)	{
  TGCompositeFrame *ButtonFrame = new TGCompositeFrame (TabPanel,0,0,kHorizontalFrame);
	
	//********************************************************************************//
  TGTextButton *bootB = new TGTextButton (ButtonFrame, "Boot", BOOT_BUTTON);
  bootB->SetFont("-adobe-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1", true);
  fClient->GetColorByName("blue", color);
  bootB->SetTextColor(color, true);
  bootB->Associate(this);
  ButtonFrame->AddFrame(bootB, new TGLayoutHints(kLHintsTop|kLHintsLeft,5,10,10,0));
  TabPanel->AddFrame(ButtonFrame, new TGLayoutHints(kLHintsTop|kLHintsLeft,0,0,0,0));
	//********************************************************************************//
	TGGroupFrame *StateMsgFrame = new TGGroupFrame (ButtonFrame,"Status",kVerticalFrame);
	StateMsgFold1 = new TGTextEntry (StateMsgFrame,
																	 new TGTextBuffer (30), 10000,
                                   StateMsgFold1->GetDefaultGC ()(),
                                   StateMsgFold1->GetDefaultFontStruct (),
                                   kRaisedFrame | kDoubleBorder,
                                   GetWhitePixel ());
  StateMsgFold1->SetFont("-adobe-helvetica-bold-r-*-*-10-*-*-*-*-*-iso8859-1", false);
  fClient->GetColorByName("red", color);
  StateMsgFold1->SetTextColor(color, true);
  StateMsgFold1->SetText("no input loaded");
  StateMsgFold1->Resize(100, 12);
  StateMsgFold1->SetEnabled(kFALSE);
  StateMsgFold1->SetFrameDrawn(kFALSE);
  StateMsgFrame->AddFrame(StateMsgFold1, new TGLayoutHints(kLHintsTop|kLHintsLeft,0,0,0,0));
  ButtonFrame->AddFrame(StateMsgFrame, new TGLayoutHints(kLHintsTop|kLHintsLeft,2,5,1,5));



  /********** button 1 **********/
  button1 = new TGTextButton(ButtonFrame, "  Run   ", BUTTON1);
  fClient->GetColorByName("blue", color);
  button1->SetTextColor(color, true);
  button1->Associate(this);
  ButtonFrame->AddFrame(button1,new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandY,3,10,10,0));

  /********** button 2 **********/
  button2 = new TGTextButton(ButtonFrame, "  Stop  ", BUTTON2);
  fClient->GetColorByName("blue", color);
  button2->SetTextColor(color, true);
  button2->Associate(this);
  ButtonFrame->AddFrame(button2,new TGLayoutHints(kLHintsLeft|kLHintsTop|kLHintsExpandY,3,10,10,0));

  /********** button 3 **********/
  button3 = new TGTextButton (ButtonFrame,"  Draw New  ", BUTTON3);
  fClient->GetColorByName("blue", color);
  button3->SetTextColor(color, true);
  button3->SetToolTipText("This is a tool tip", 0);
  button3->Associate(this);
  ButtonFrame->AddFrame(button3,new TGLayoutHints(kLHintsTop|kLHintsLeft|kLHintsExpandY, 0, 10, 10, 0));

	/**********  labels  **********/
	TGVerticalFrame *fFeSlLabels = new TGVerticalFrame (ButtonFrame);
  TGLabel *fe = new TGLabel (fFeSlLabels, "Frtend #:");
  fe->SetTextColor(color, true);
  fFeSlLabels->AddFrame(fe, new TGLayoutHints(kLHintsLeft|kLHintsTop,10,3,4,0));
  TGLabel *sl = new TGLabel(fFeSlLabels, "Slave #:");
  fFeSlLabels->AddFrame(sl,new TGLayoutHints(kLHintsLeft,10,3,4,0));
  ButtonFrame->AddFrame(fFeSlLabels, new TGLayoutHints(kLHintsTop|kLHintsLeft,0,0,0,0));

	/**********  number entries  **********/
  TGVerticalFrame *fFrontendSlave = new TGVerticalFrame(ButtonFrame);

  numericFrontend = new TGNumberEntry(fFrontendSlave,0,4,FRONTEND_NUMBER, // Module # entry
		                                 (TGNumberFormat::EStyle) 12,
     			                           (TGNumberFormat::EAttribute) 1,
     			                           (TGNumberFormat::ELimit) 3,1, 2);
  numericFrontend->SetButtonToNum(0);
  fFrontendSlave->AddFrame(numericFrontend,new TGLayoutHints(kLHintsTop|kLHintsLeft,2,3,0,0));
  numericFrontend->Associate(this);

  numericSlave = new TGNumberEntry(fFrontendSlave,0,4,SLAVE_NUMBER, // Channel # entry
                           		    (TGNumberFormat::EStyle) 12,
                           		    (TGNumberFormat::EAttribute) 1,
                           		    (TGNumberFormat::ELimit) 3, 0, 16);
  numericSlave->SetButtonToNum(0);
  fFrontendSlave->AddFrame(numericSlave,new TGLayoutHints(kLHintsTop|kLHintsLeft,2,3,0,0));
  numericSlave->Associate(this);


  ButtonFrame->AddFrame(fFrontendSlave,new TGLayoutHints(kLHintsTop|kLHintsLeft,0,0,0,0));
  
	/**********  labels  **********/
	TGVerticalFrame *fPtChLabels = new TGVerticalFrame (ButtonFrame);
  TGLabel *pt = new TGLabel (fPtChLabels, "Port #:");
  pt->SetTextColor(color, true);
  fPtChLabels->AddFrame(pt, new TGLayoutHints(kLHintsLeft|kLHintsTop,10,3,4,0));
  TGLabel *ch = new TGLabel(fPtChLabels, "Chan #:");
  fPtChLabels->AddFrame(ch,new TGLayoutHints(kLHintsLeft,10,3,4,0));
  ButtonFrame->AddFrame(fPtChLabels, new TGLayoutHints(kLHintsTop|kLHintsLeft,0,0,0,0));
  
  /********** mor number entries *********/
  
  TGVerticalFrame *fPortChannel = new TGVerticalFrame(ButtonFrame);

  numericPort = new TGNumberEntry(fPortChannel,0,4,PORT_NUMBER, // Module # entry
                                 (TGNumberFormat::EStyle) 12,
 			                           (TGNumberFormat::EAttribute) 1,
 			                           (TGNumberFormat::ELimit) 3,0,16);
  numericPort->SetButtonToNum(0);
  fPortChannel->AddFrame(numericPort,new TGLayoutHints(kLHintsTop|kLHintsLeft,2,3,0,0));
  numericPort->Associate(this);

  numericChannel = new TGNumberEntry(fPortChannel,0,4,CHANNEL_NUMBER, // Channel # entry
                     	      		    (TGNumberFormat::EStyle) 12,
                     	      		    (TGNumberFormat::EAttribute) 1,
                     	      		    (TGNumberFormat::ELimit) 3, 0, 256);
  numericChannel->SetButtonToNum(0);
  fPortChannel->AddFrame(numericChannel,new TGLayoutHints(kLHintsTop|kLHintsLeft,2,3,0,0));
  numericChannel->Associate(this);


  ButtonFrame->AddFrame(fPortChannel,new TGLayoutHints(kLHintsTop|kLHintsLeft,0,0,0,0));
  
  
  /********** Canvas **********/
  TGCompositeFrame *CanvasFrame = new TGCompositeFrame(TabPanel,60,60,kHorizontalFrame);
  TGLayoutHints *Hint = new TGLayoutHints(kLHintsExpandX|kLHintsExpandY,1, 1, 1, 1);
  TRootEmbeddedCanvas *eCanvasF1 = new TRootEmbeddedCanvas ("ec1",CanvasFrame,100, 100);
  dCanvasF1 = eCanvasF1->GetCanvas();
  dCanvasF1->SetBorderMode(0); // No red frame
  CanvasFrame->AddFrame(eCanvasF1, Hint);
  TabPanel->AddFrame(CanvasFrame, Hint);

  parts[0] = 33;
  parts[1] = 10;
  parts[2] = 10;
  parts[3] = 47;

  fStatusBar = new TGStatusBar (TabPanel, 10, 10);
  fStatusBar->SetParts(parts, 4);
  TabPanel->AddFrame(fStatusBar, new TGLayoutHints(kLHintsBottom|kLHintsLeft|kLHintsExpandX,2,2,1,1));

}


bool TTigOFrame::ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2)	{
	printf("ProcessMessage:  msg = %d\tparm1 = %d\tparm2 = %d\t\n",msg,parm1,parm2);
	int message = GET_MSG(msg);
	int submessage = GET_SUBMSG(msg);
	switch (message)	{
		case kC_COMMAND:
			printf("msg = kC_COMMAND\n");
			HandleCommand(submessage,parm1,parm2);
			break;
		case kC_TEXTENTRY:
			printf("msg = kCM_TEXTENTRY\n");		
			break;
		default:
			printf("msg not found?\n");		
			break;
	};


	return true;


}

void TTigOFrame::HandleCommand(int submessage,long parm1, long parm2)	{

	switch (submessage)	{
		case kCM_MENU:
			printf("submsg = kCM_MENU\n");
			HandleMenu(parm1,parm2);
			break;
		case kCM_BUTTON:
			printf("submsg = kCM_BUTTON\n");
			HandleButton(parm1,parm2);
			break;
		default:
			printf("submsg not found?\n");		
			break;
	};


}


void TTigOFrame::HandleMenu(long parm1,long parm2)	{
	switch(parm1)	{
		case FILE_EXIT:
			//check if connected online....
			CloseWindow();
			break;
		case FILE_OPEN:
			{
				new TGFileDialog(fClient->GetRoot(),this, kFDOpen, &fEventFileOpenInfo);
        if(fEventFileOpenInfo.fFilename != 0)
					printf("\t file = %s\n",fEventFileOpenInfo.fFilename);
			}
			break;
		case ABOUT:
			printf("this doesn't exist, move along.\n");
			break;
		};
}


void TTigOFrame::HandleButton(long parm1, long parm2)	{
	switch(parm1)	{
		case BUTTON1:
			printf("\tbutton one pressed.\n");
			break;
		case BUTTON2:
			printf("\tbutton two pressed.\n");
			break;
		case BUTTON3:
			printf("\tbutton three pressed.\n");
			{
				int l_fe =	numericFrontend->GetNumber();           
				int l_sl =	numericSlave->GetNumber();            
				int l_pt =	numericPort->GetNumber();           
				int l_ch =	numericChannel->GetNumber();     
				int fspc = (l_fe<<24 ) + (l_sl<<20) + (l_pt<<8) + l_ch;
				printf("\tfscp = 0x%08x\n",fspc);
			}
			break;
		default:
			printf("\tunknown button pressed.\n");
			break;
	};

}















































