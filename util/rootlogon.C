{
   gSystem->Load("$ROOTSYS/lib/libPhysics.so");   // need to make tvector3 play nice.

   TString path = gSystem->Getenv("GRSISYS");
   if (path.Length() == 0) {
      path = gEnv->GetValue("GRSI.Path", "/opt/GRSISpoon");
   }
   FileStat_t buf;
   gSystem->GetPathInfo(path, buf);

   if ( !R_ISDIR(buf.fMode) ) {
      std::cout << "GRSISpoon path " << path << " does not exist." << std::endl;
      gROOT->ProcessLine(".q");
   }
   gROOT->ProcessLine(TString(".include " + path + "/include"));

   path += "/libraries";

   gSystem->Load("libNet.so"); // necessary for libMidasInterface

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

   gStyle->SetOptStat(111111);
   gROOT->LoadMacro("Setup.C");  
}
