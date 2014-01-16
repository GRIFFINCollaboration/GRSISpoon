

static void SigHandler(ESignals sig)
{
   // Unix signal handler.
   Long64_t event;
   if (gROME) {
      event = gROME->GetCurrentEventNumber();
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
}
