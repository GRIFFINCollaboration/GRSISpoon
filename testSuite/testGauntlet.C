void testGauntlet(){
  //open our files
  TFile *standard  = new TFile("fragment27422_000_benchmark.root");
  TFile *contender = new TFile("fragment27422_000.root");

  //open our trees
  TTree *benchmarkTree = (TTree*)standard->Get("FragmentTree");
  TTree *contenderTree = (TTree*)contender->Get("FragmentTree");

  //magic
  benchmarkTree->SetMakeClass(1);
  contenderTree->SetMakeClass(1);

  //variables: _st for standard, _ct for contender
  UInt_t  fUniqueID_st;
  UInt_t  fUniqueID_ct;
  UInt_t  fBits_st;
  UInt_t  fBits_ct;
  TString fName_st;
  TString fName_ct;
  TString fTitle_st;
  TString fTitle_ct;
  Long_t  MidasTimeStamp_st;
  Long_t  MidasTimeStamp_ct;
  UInt_t  MidasId_st;
  UInt_t  MidasId_ct;
  Int_t   TriggerId_st;
  Int_t   TriggerId_ct;
  Int_t FragmentId_st;
  Int_t FragmentId_ct;
  Int_t TriggerBitPattern_st;
  Int_t TriggerBitPattern_ct;
  string DigitizerType_st;
  string DigitizerType_ct;
  Int_t ODBType_st;
  Int_t ODBType_ct;
  string ChannelName_st;
  string ChannelName_ct;
  Int_t ChannelNumber_st;
  Int_t ChannelNumber_ct;
  Int_t ChannelRaw_st;
  Int_t ChannelRaw_ct;
  Int_t Cfd_st;
  Int_t Cfd_ct;
  Int_t Led_st; 
  Int_t Led_ct;
  Int_t TimeToTrig_st;
  Int_t TimeToTrig_ct;
  Int_t Charge_st;
  Int_t Charge_ct;
  Float_t ChargeCal_st;
  Float_t ChargeCal_ct;
  Int_t TimeStampLow_st;
  Int_t TimeStampLow_ct;
  Int_t TimeStampHigh_st;
  Int_t TimeStampHigh_ct;
  Int_t TimeStampLive_st;
  Int_t TimeStampLive_ct;
  Int_t TimeStampTR_st;
  Int_t TimeStampTR_ct;
  Int_t TimeStampTA_st;
  Int_t TimeStampTA_ct;
  Int_t SamplesFound_st;
  Int_t SamplesFound_ct;
  Bool_t SlowRiseTime_st;
  Bool_t SlowRiseTime_ct;
  Bool_t PileUp_st;
  Bool_t PileUp_ct;
  vector<int> wavebuffer_st;
  vector<int> wavebuffer_ct;


  //branches
  TBranch *fUniqueID_st_b = benchmarkTree->GetBranch("fUniqueID");
  TBranch *fUniqueID_ct_b = contenderTree->GetBranch("fUniqueID");
  TBranch *fBits_st_b = benchmarkTree->GetBranch("fBits");
  TBranch *fBits_ct_b = contenderTree->GetBranch("fBits");
  TBranch *fName_st_b = benchmarkTree->GetBranch("fName");
  TBranch *fName_ct_b = contenderTree->GetBranch("fName");
  TBranch *fTitle_st_b = benchmarkTree->GetBranch("fTitle");
  TBranch *fTitle_ct_b = contenderTree->GetBranch("fTitle");
  TBranch *MidasTimeStamp_st_b = benchmarkTree->GetBranch("MidasTimeStamp");
  TBranch *MidasTimeStamp_ct_b = contenderTree->GetBranch("MidasTimeStamp");
  TBranch *MidasId_st_b = benchmarkTree->GetBranch("MidasId");
  TBranch *MidasId_ct_b = contenderTree->GetBranch("MidasId");
  TBranch *TriggerId_st_b = benchmarkTree->GetBranch("TriggerId");
  TBranch *TriggerId_ct_b = contenderTree->GetBranch("TriggerId");
  TBranch *FragmentId_st_b = benchmarkTree->GetBranch("FragmentId");
  TBranch *FragmentId_ct_b = contenderTree->GetBranch("FragmentId");
  TBranch *TriggerBitPattern_st_b = benchmarkTree->GetBranch("TriggerBitPattern");
  TBranch *TriggerBitPattern_ct_b = contenderTree->GetBranch("TriggerBitPattern");
  TBranch *DigitizerType_st_b = benchmarkTree->GetBranch("DigitizerType");
  TBranch *DigitizerType_ct_b = contenderTree->GetBranch("DigitizerType");
  TBranch *ODBType_st_b = benchmarkTree->GetBranch("ODBType");
  TBranch *ODBType_ct_b = contenderTree->GetBranch("ODBType");
  TBranch *ChannelName_st_b = benchmarkTree->GetBranch("ChannelName");
  TBranch *ChannelName_ct_b = contenderTree->GetBranch("ChannelName");
  TBranch *ChannelNumber_st_b = benchmarkTree->GetBranch("ChannelNumber");
  TBranch *ChannelNumber_ct_b = contenderTree->GetBranch("ChannelNumber");
  TBranch *ChannelRaw_st_b = benchmarkTree->GetBranch("ChannelRaw");
  TBranch *ChannelRaw_ct_b = contenderTree->GetBranch("ChannelRaw");
  TBranch *Cfd_st_b = benchmarkTree->GetBranch("Cfd");
  TBranch *Cfd_ct_b = contenderTree->GetBranch("Cfd");
  TBranch *Led_st_b = benchmarkTree->GetBranch("Led");
  TBranch *Led_ct_b = contenderTree->GetBranch("Led");
  TBranch *TimeToTrig_st_b = benchmarkTree->GetBranch("TimeToTrig");
  TBranch *TimeToTrig_ct_b = contenderTree->GetBranch("TimeToTrig");
  TBranch *Charge_st_b = benchmarkTree->GetBranch("Charge");
  TBranch *Charge_ct_b = contenderTree->GetBranch("Charge");
  TBranch *ChargeCal_st_b = benchmarkTree->GetBranch("ChargeCal");
  TBranch *ChargeCal_ct_b = contenderTree->GetBranch("ChargeCal");
  TBranch *TimeStampLow_st_b = benchmarkTree->GetBranch("TimeStampLow");
  TBranch *TimeStampLow_ct_b = contenderTree->GetBranch("TimeStampLow");
  TBranch *TimeStampHigh_st_b = benchmarkTree->GetBranch("TimeStampHigh");
  TBranch *TimeStampHigh_ct_b = contenderTree->GetBranch("TimeStampHigh");
  TBranch *TimeStampLive_st_b = benchmarkTree->GetBranch("TimeStampLive");
  TBranch *TimeStampLive_ct_b = contenderTree->GetBranch("TimeStampLive");
  TBranch *TimeStampTR_st_b = benchmarkTree->GetBranch("TimeStampTR");
  TBranch *TimeStampTR_ct_b = contenderTree->GetBranch("TimeStampTR");
  TBranch *TimeStampTA_st_b = benchmarkTree->GetBranch("TimeStampTA");
  TBranch *TimeStampTA_ct_b = contenderTree->GetBranch("TimeStampTA");
  TBranch *SamplesFound_st_b = benchmarkTree->GetBranch("SamplesFound");
  TBranch *SamplesFound_ct_b = contenderTree->GetBranch("SamplesFound");
  TBranch *SlowRiseTime_st_b = benchmarkTree->GetBranch("SlowRiseTime");
  TBranch *SlowRiseTime_ct_b = contenderTree->GetBranch("SlowRiseTime");
  TBranch *PileUp_st_b = benchmarkTree->GetBranch("PileUp");
  TBranch *PileUp_ct_b = contenderTree->GetBranch("PileUp");
  TBranch *wavebuffer_st_b = benchmarkTree->GetBranch("wavebuffer");
  TBranch *wavebuffer_ct_b = contenderTree->GetBranch("wavebuffer");

  //point the branches
  fUniqueID_st_b->SetAddress(&fUniqueID_st);
  fUniqueID_ct_b->SetAddress(&fUniqueID_ct);
  fBits_st_b->SetAddress(&fBits_st);
  fBits_ct_b->SetAddress(&fBits_ct);
  fName_st_b->SetAddress(&fName_st);
  fName_ct_b->SetAddress(&fName_ct);
  fTitle_st_b->SetAddress(&fTitle_st);
  fTitle_ct_b->SetAddress(&fTitle_ct);
  MidasTimeStamp_st_b->SetAddress(&MidasTimeStamp_st);
  MidasTimeStamp_ct_b->SetAddress(&MidasTimeStamp_ct);
  MidasId_st_b->SetAddress(&MidasId_st);
  MidasId_ct_b->SetAddress(&MidasId_ct);
  TriggerId_st_b->SetAddress(&TriggerId_st);
  TriggerId_ct_b->SetAddress(&TriggerId_ct);
  FragmentId_st_b->SetAddress(&FragmentId_st);
  FragmentId_ct_b->SetAddress(&FragmentId_ct);
  TriggerBitPattern_st_b->SetAddress(&TriggerBitPattern_st);
  TriggerBitPattern_ct_b->SetAddress(&TriggerBitPattern_ct);
  DigitizerType_st_b->SetAddress(&DigitizerType_st);
  DigitizerType_ct_b->SetAddress(&DigitizerType_ct);
  ODBType_st_b->SetAddress(&ODBType_st);
  ODBType_ct_b->SetAddress(&ODBType_ct);
  ChannelName_st_b->SetAddress(&ChannelName_st);
  ChannelName_ct_b->SetAddress(&ChannelName_ct);
  ChannelNumber_st_b->SetAddress(&ChannelNumber_st);
  ChannelNumber_ct_b->SetAddress(&ChannelNumber_ct);
  ChannelRaw_st_b->SetAddress(&ChannelRaw_st);
  ChannelRaw_ct_b->SetAddress(&ChannelRaw_ct);
  Cfd_st_b->SetAddress(&Cfd_st);
  Cfd_ct_b->SetAddress(&Cfd_ct);
  Led_st_b->SetAddress(&Led_st);
  Led_ct_b->SetAddress(&Led_ct);
  TimeToTrig_st_b->SetAddress(&TimeToTrig_st);
  TimeToTrig_ct_b->SetAddress(&TimeToTrig_ct);
  Charge_st_b->SetAddress(&Charge_st);
  Charge_ct_b->SetAddress(&Charge_ct);
  ChargeCal_st_b->SetAddress(&ChargeCal_st);
  ChargeCal_ct_b->SetAddress(&ChargeCal_ct);
  TimeStampLow_st_b->SetAddress(&TimeStampLow_st);
  TimeStampLow_ct_b->SetAddress(&TimeStampLow_ct);
  TimeStampHigh_st_b->SetAddress(&TimeStampHigh_st);
  TimeStampHigh_ct_b->SetAddress(&TimeStampHigh_ct);
  TimeStampLive_st_b->SetAddress(&TimeStampLive_st);
  TimeStampLive_ct_b->SetAddress(&TimeStampLive_ct);
  TimeStampTR_st_b->SetAddress(&TimeStampTR_st);
  TimeStampTR_ct_b->SetAddress(&TimeStampTR_ct);
  TimeStampTA_st_b->SetAddress(&TimeStampTA_st);
  TimeStampTA_ct_b->SetAddress(&TimeStampTA_ct);
  SamplesFound_st_b->SetAddress(&SamplesFound_st);
  SamplesFound_ct_b->SetAddress(&SamplesFound_ct);
  SlowRiseTime_st_b->SetAddress(&SlowRiseTime_st);
  SlowRiseTime_ct_b->SetAddress(&SlowRiseTime_ct);
  PileUp_st_b->SetAddress(&PileUp_st);
  PileUp_ct_b->SetAddress(&PileUp_ct);
  wavebuffer_st_b->SetAddress(&wavebuffer_st);
  wavebuffer_ct_b->SetAddress(&wavebuffer_ct);


  Int_t nentries_st = (Int_t)benchmarkTree->GetEntries();
  Int_t nentries_ct = (Int_t)contenderTree->GetEntries();

  if(nentries_ct != nentries_st){
    cout << "Standard and contender trees don't have the same number of entries, test failed." << endl;
    return;
  }

  for (Int_t i=0; i<nentries_st; i++) {
    //populate the variables
    fUniqueID_st_b->GetEntry(i);
    fUniqueID_ct_b->GetEntry(i);
    fBits_st_b->GetEntry(i);
    fBits_ct_b->GetEntry(i);
    fName_st_b->GetEntry(i);
    fName_ct_b->GetEntry(i);
    fTitle_st_b->GetEntry(i);
    fTitle_ct_b->GetEntry(i);
    MidasTimeStamp_st_b->GetEntry(i);
    MidasTimeStamp_ct_b->GetEntry(i);
    MidasId_st_b->GetEntry(i);
    MidasId_ct_b->GetEntry(i);
    TriggerId_st_b->GetEntry(i);
    TriggerId_ct_b->GetEntry(i);
    FragmentId_st_b->GetEntry(i);
    FragmentId_ct_b->GetEntry(i);
    TriggerBitPattern_st_b->GetEntry(i);
    TriggerBitPattern_ct_b->GetEntry(i);
    DigitizerType_st_b->GetEntry(i);
    DigitizerType_ct_b->GetEntry(i);
    ODBType_st_b->GetEntry(i);
    ODBType_ct_b->GetEntry(i);
    ChannelName_st_b->GetEntry(i);
    ChannelName_ct_b->GetEntry(i);
    ChannelNumber_st_b->GetEntry(i);
    ChannelNumber_ct_b->GetEntry(i);
    ChannelRaw_st_b->GetEntry(i);
    ChannelRaw_ct_b->GetEntry(i);
    Cfd_st_b->GetEntry(i);
    Cfd_ct_b->GetEntry(i);
    Led_st_b->GetEntry(i);
    Led_ct_b->GetEntry(i);
    TimeToTrig_st_b->GetEntry(i);
    TimeToTrig_ct_b->GetEntry(i);
    Charge_st_b->GetEntry(i);
    Charge_ct_b->GetEntry(i);
    ChargeCal_st_b->GetEntry(i);
    ChargeCal_ct_b->GetEntry(i);
    TimeStampLow_st_b->GetEntry(i);
    TimeStampLow_ct_b->GetEntry(i);
    TimeStampHigh_st_b->GetEntry(i);
    TimeStampHigh_ct_b->GetEntry(i);
    TimeStampLive_st_b->GetEntry(i);
    TimeStampLive_ct_b->GetEntry(i);
    TimeStampTR_st_b->GetEntry(i);
    TimeStampTR_ct_b->GetEntry(i);
    TimeStampTA_st_b->GetEntry(i);
    TimeStampTA_ct_b->GetEntry(i);
    SamplesFound_st_b->GetEntry(i);
    SamplesFound_ct_b->GetEntry(i);
    SlowRiseTime_st_b->GetEntry(i);
    SlowRiseTime_ct_b->GetEntry(i);
    PileUp_st_b->GetEntry(i);
    PileUp_ct_b->GetEntry(i);
    wavebuffer_st_b->GetEntry(i);
    wavebuffer_ct_b->GetEntry(i);

     
    //demand exact matches everywhere, bail out and report on first problem encountered:
    if(fUniqueID_st != fUniqueID_ct){
      cout << "fUniqueID mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(fBits_st != fBits_ct){
      cout << "fBits mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(fName_st != fName_ct){
      cout << "fName mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(fTitle_st != fTitle_ct){
      cout << "fTitle mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }
    //this might be an actual timestamp, don't check
    /*
    if(MidasTimeStamp_st != MidasTimeStamp_ct){
      cout << "MidasTimeStamp mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }
    */
    if(MidasId_st != MidasId_ct){
      cout << "MidasId mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(TriggerId_st != TriggerId_ct){
      cout << "TriggerId mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(FragmentId_st != FragmentId_ct){
      cout << "FragmentId mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(TriggerBitPattern_st != TriggerBitPattern_ct){
      cout << "TriggerBitPattern mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(DigitizerType_st != DigitizerType_ct){
      cout << "DigitizerType mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(ODBType_st != ODBType_ct){
      cout << "ODBType mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(ChannelName_st != ChannelName_ct){
      cout << "ChannelName mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(ChannelNumber_st != ChannelNumber_ct){
      cout << "ChannelNumber mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(ChannelRaw_st != ChannelRaw_ct){
      cout << "ChannelRaw mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(Cfd_st != Cfd_ct){
      cout << "Cfd mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(Led_st != Led_ct){
      cout << "Led mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(TimeToTrig_st != TimeToTrig_ct){
      cout << "TimeToTrig mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(Charge_st != Charge_ct){
      cout << "Charge mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(ChargeCal_st != ChargeCal_ct){
      cout << "ChargeCal mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(TimeStampLow_st != TimeStampLow_ct){
      cout << "TimeStampLow mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(TimeStampHigh_st != TimeStampHigh_ct){
      cout << "TimeStampHigh mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(TimeStampLive_st != TimeStampLive_ct){
      cout << "TimeStampLive mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(TimeStampTR_st != TimeStampTR_ct){
      cout << "TimeStampTR mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(TimeStampTA_st != TimeStampTA_ct){
      cout << "TimeStampTA mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(SamplesFound_st != SamplesFound_ct){
      cout << "SamplesFound mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(SlowRiseTime_st != SlowRiseTime_ct){
      cout << "SlowRiseTime mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(PileUp_st != PileUp_ct){
      cout << "PileUp mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }

    if(wavebuffer_st != wavebuffer_ct){
      cout << "wavebuffer mismatch at entry " << i << "; do not attempt pull request!" << endl;
      return;
    }


  }

  cout << "Congratulations, test gauntlet cleared!" << endl;

}