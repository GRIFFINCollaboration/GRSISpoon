#ifndef TSERVER_H
#define TSERVER_H

#include <cstdio>
#include <string>

#ifndef __CINT__
#define _GLIBCXX_USE_NANOSLEEP 1
#include <thread>
#endif

#include <TSocket.h>
#include <TServerSocket.h>
#include <TMonitor.h>

#include <TH1.h>

class TServer : public TObject	{

	public:
		static TServer *instance(int port = 9099);
		virtual ~TServer();

	private:
		static TServer *fTServer;
		TServer(int);

		TServerSocket *fserversocket;
		TMonitor      *fmonitor;

		bool fserving;

		void Listen();
		void Monitor();

		void DoStuff(std::string,TSocket*);
		void DoQuery(std::string,TSocket*);

		void SendString(TSocket* sock, const char* str);
		void SendHttpReply(TSocket* sock, const char* mimetype, const char* message);
		void SendHttpReply(TSocket* sock, const char* mimetype, const std::string& str);


	public:
		void Stop();

		TH1F *makejunk();

	ClassDef(TServer,0)

};

#endif
