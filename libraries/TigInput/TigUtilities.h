

void UnixSignal(ESignals sig, SigHandler_t handler)
{
   // Set a signal handler for a signal.
/*
   if (gSignalMap[sig].fHandler != handler) {
      struct sigaction sigact;

      gSignalMap[sig].fHandler    = handler;
      gSignalMap[sig].fOldHandler = new struct sigaction();

#if defined(R__SUN)
      sigact.sa_handler = (void (*)())sighandler;
#elif defined(R__SOLARIS)
      sigact.sa_handler = sighandler;
#elif defined(R__KCC)
      sigact.sa_handler = (sighandlerFunc_t)sighandler;
#elif (defined(R__SGI) && !defined(R__KCC)) || defined(R__LYNXOS)
#  if defined(R__SGI64) || (__GNUG__>=3)
      sigact.sa_handler = sighandler;
#  else
      sigact.sa_handler = (void (*)(...))sighandler;
#  endif
#else
      sigact.sa_handler = sighandler;
#endif
      sigemptyset(&sigact.sa_mask);
      sigact.sa_flags = 0;
#if defined(SA_RESTART)
      sigact.sa_flags |= SA_RESTART;
#endif
      if (sigaction(gSignalMap[sig].fCode, &sigact,
                    gSignalMap[sig].fOldHandler) < 0)
         gSystem->SysError("ROMERint::UnixSignal", "sigaction");
   }
*/
}



static void SigHandler(ESignals sig)
{
   // Unix signal handler.
/*
   Long64_t event;
   if (gSCOPE) {
      event = gSCOPE->GetCurrentEventNumber();
      cerr<<"Signal";
      if (static_cast<Int_t>(sig) >= 0 &&
          static_cast<Int_t>(sig) < static_cast<Int_t>(kMAXSIGNALS)) {
         cerr<<"("<<gSignalMap[static_cast<Int_t>(sig)].fSigName<<")";
      }
      cerr<<" caught at run="<<gROME->GetCurrentRunNumber();
      switch (event) {
      case kEventNumberInit :
         cerr<<", Init"<<endl;
         break;
      case kEventNumberBeginOfRun:
         cerr<<", BeginOfRun"<<endl;
         break;
      case kEventNumberEndOfRun:
         cerr<<", EndOfRun"<<endl;
         break;
      case kEventNumberTerminate:
         cerr<<", Terminate"<<endl;
         break;
      default:
         cerr<<", event="<<event<<endl;
         break;
      }
   }
   cleaning();
   if (gSystem)
      ((TUnixSystem*)gSystem)->DispatchSignals(sig);
*/
}


