
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
		//socket->Send("go");
		char buffer[8192];
	    int junk = socket->RecvRaw(buffer,8192,kPeek);
        std::string tmp = buffer;
        DoStuff(tmp,socket);
		socket->Close();
//		fmonitor->Add(socket);
	}
	return;
};


void TServer::Monitor()	{

	char buffer[8192];
	while(fserving)	{
		if(fmonitor->GetActive() == 0)	{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			continue;
		}
		TSocket *socket;// = new TSocket;
		socket = fmonitor->Select();//1000);
		if(socket == 0) {
			continue;
		}
		socket->RecvRaw(buffer,8191);
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
	else if (strncmp(message.c_str(),"GET",3)==0)	{
		printf("found GET request.\n");
		int	 begque = message.find_first_of('?');
		int  endque = message.find_first_of('\n');
		std::string command;
		if(endque != std::string::npos)	{
			command = message.substr(begque+1,message.length());
			command = command.substr(0,command.find_first_of(' '));
 		}
		//printf("command: %s\n",command.c_str());
		DoQuery(command,socket);
	} 
	else
		printf("I am unique, recv: %s\n end of message\n\n",message.c_str());
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


void TServer::DoQuery(std::string query, TSocket *socket)	{

	printf("do query called with\n\t%s\n",query.c_str());

	std::string tosend = "I got this: "; tosend += query.c_str();

	SendHttpReply(socket,"application/json",tosend);

}



void TServer::SendString(TSocket* sock, const char* str)
{
   sock->SendRaw(str, strlen(str));
}


void TServer::SendHttpReply(TSocket* sock, const char* mimetype, const char* message)
{
   char buf[256];
   int len = strlen(message);

	std::string tosend = "HTTP/1.1 200 OK\n";
	sprintf(buf, "Content-Length: %d\n", len);
	tosend += buf;
	sprintf(buf, "Content-Type: %s\n", mimetype);
	tosend += buf;
	tosend += '\n';
	tosend += message;

	SendString(sock,tosend.c_str());

/*
	printf("here 1\n");
   SendString(sock, "HTTP/1.1 200 OK\n");
   //SendString(sock, "Date: Tue, 15 May 2012 16:50:31 GMT\n");
//   SendString(sock, "Server: ROOTANA xmlServer\n");
	printf("here 2\n");
   sprintf(buf, "Content-Length: %d\n", len);
   SendString(sock, buf);
   //Connection: close\n
	printf("here 3\n");
   sprintf(buf, "Content-Type: %s\n", mimetype);
   SendString(sock, buf);
   //charset=iso-8859-1\n
	printf("here 4\n");
   SendString(sock, "\n");
   SendString(sock, message);
   // printf("SendHttpReply: content-length %d, content-type %s\n", len, mimetype);
*/

//	SendString(sock, "HTTP/1.1 101 \n");







}
   
void TServer::SendHttpReply(TSocket* sock, const char* mimetype, const std::string& str)
{
  SendHttpReply(sock, mimetype, str.c_str());
}
                                 
