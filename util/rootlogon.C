{
   // Grab an environment variable either from the system: GRSISYS
   //   or from the ROOT rc file: GRSI.Path
   //   This is where we look for relevant libraries and header files
   TString path = gSystem->Getenv("GRSISYS");
   if (path.Length() == 0) {
      path = gEnv->GetValue("GRSI.Path", "/opt/GRSISpoon");
   }
   // Double check that this path actually exists and is a directory
   FileStat_t buf;
   gSystem->GetPathInfo(path, buf);

   if ( !R_ISDIR(buf.fMode) ) {
      std::cout << "GRSISpoon path " << path << " does not exist." << std::endl;
      gROOT->ProcessLine(".q");
   }

   // add proper include path
   gROOT->ProcessLine(TString(".include " + path + "/include"));

   // start linking libraries
   path += "/libraries";

   // root libraries first
   gSystem->Load("libNet.so"); // necessary for libMidasInterface
   gSystem->Load("libPhysics.so"); // needed to make TVector3 play nice for analysis

   // now give a list of GRSISpoon libraries we want
   std::vector<TString> liblist;   
   liblist.push_back("libMidasInterface.so");
   liblist.push_back("libFormat.so");

   for (size_t i=0; i < liblist.size(); i++) {
      TString file = liblist.at(i);

      if ( gSystem->FindFile(path, file) == NULL) {
	 std::cout << "Library " << liblist.at(i) << " not found." << std::endl;
	 gROOT->ProcessLine(".q");
      } else {
	 gSystem->Load(file);
      }
   }

   // and finally a few stylistic preferences
   gStyle->SetOptStat(111111);
   gROOT->LoadMacro("Setup.C");  
}
