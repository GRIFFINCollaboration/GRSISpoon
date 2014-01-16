

TMidasFile *mfile = 0;
TMidasEvent *mevent = new TMidasEvent();


void Setup(string name = "")	{

	if(name.length()==0)	{
		printf("try Setup(filename)\n");
		return; 
	}
	mfile = new TMidasFile();	
	mfile->Open(name.c_str());
	return;
}

void Read()	{
	if(mfile ==0)	{
		printf("do Setup(filename) first\n");
		return;
	}
	mfile->Read(mevent);
	if(mevent->GetEventId() == 0x8000 || mevent->GetEventId() == 0x8001)	{
		mevent->Print();
		return;
	}
	mevent->SetBankList();
	mevent->Print("a");
	return;

}






