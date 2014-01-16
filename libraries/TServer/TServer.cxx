
#include "TServer.h"

#include "RootIOManager.h"

#include "TRandom.h"

ClassImp(TServer)


TServer *TServer::fTServer = 0;

TServer *TServer::instance(int port)	{
	if(fTServer == 0)
		fTServer = new TServer(port);
	return fTServer;
}

TServer::TServer(int port)	{
	printf("TServer created, listening on port: %i\n",port);

	fserversocket = new TServerSocket(port,true);
	fmonitor = new TMonitor;

	std::thread listenthread(&TServer::Listen,this);
	std::thread monitorthread(&TServer::Monitor,this);

	fserving = true;

	listenthread.detach();
	monitorthread.detach();

	return;
};

TServer::~TServer()	{

}

void TServer::Listen()	{
	while(fserving)	{
		TSocket *socket = fserversocket->Accept();
		fmonitor->Add(socket);
		socket->Send("go");
	}
	return;
};


void TServer::Monitor()	{

	char buffer[512];
	while(fserving)	{
		if(fmonitor->GetActive() == 0)	{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			continue;
		}
		TSocket *socket;
		socket = fmonitor->Select();//1000);
		if(socket == 0) {
			continue;
		}
		socket->Recv(buffer,511);
		std::string tmp = buffer;
		DoStuff(tmp,socket);
	}
	printf("hello end\n");
	return;

};

void TServer::DoStuff(std::string message, TSocket *socket)	{
	if(!message.length())	
		printf("empty message recv!\n");
	else if(message == "STOP") {
		// Stop();
		fmonitor->Remove(socket);
		socket->Close();
	} else if(message == "SEND JUNK")	{
		printf("\tsending junk!!\n");
		TH1F *junk = makejunk();
		socket->SendObject((TObject*)junk);
		junk->Delete();
	}
	else if(message == "SEND HIT")	{
		printf("sending hit pattern!\n");
		TH1 *hitpattern = RootIOManager::instance()->MakeHitPattern();
		socket->SendObject((TObject*)hitpattern);
		hitpattern->Delete();
	}
	else if(message== "SEND PROJ")	{
		char buffer[512];
		std::string command;
		std::string gate;			
		printf("send projection recv\n");
		socket->Send("type,command,gate");
		socket->Recv(buffer,511);
		message = buffer;
		socket->Recv(buffer,511);
		command = buffer;
		socket->Recv(buffer,511);
		gate = buffer;
		TH1* hist;
		if(message == "1D") {
			hist = RootIOManager::instance()->Make1DProjection(command,gate);
		}
		else if(message == "2D")	{
			hist = RootIOManager::instance()->Make2DProjection(command,gate);
		}
		else	{
			hist = (TH1*)(new TH1I("junk","unknown type",10,0,10));
		}
		socket->SendObject((TObject*)hist);
		hist->Delete();
	}
	else
		printf("recv: %s\n",message.c_str());
	return;
};




void TServer::Stop()	{
	printf("ok, stopping now. adios.");
	fserving = false;
}


TH1F *TServer::makejunk()	{
	
	TH1F *junk = new TH1F("junk","JUNK!!",100,0,100);

	float one       = gRandom->Uniform(10,90);
    float two       = gRandom->Uniform(10,90);
    float three     = gRandom->Uniform(10,90);
    for(int x=0;x<10000;x++)        {
	    junk->Fill(gRandom->Gaus(one,5));
        junk->Fill(gRandom->Gaus(two,5));
        junk->Fill(gRandom->Gaus(three,5));
    }
	return junk;
}







