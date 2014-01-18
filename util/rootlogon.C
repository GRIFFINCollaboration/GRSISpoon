{
	gSystem->Load("$ROOTSYS/lib/libPhysics.so");   // need to make tvector3 play nice.
	gSystem->Load("/home/tigress/new_packages/GRSISpoon/libraries/libMidasInterface.so");
	gSystem->Load("/home/tigress/new_packages/GRSISpoon/libraries/libTigress.so");
	gStyle->SetOptStat(111111);
	gROOT->LoadMacro("Setup.C");
}
