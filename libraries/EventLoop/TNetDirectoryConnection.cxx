

#incldue "TNetDirectoryConnection.h"


class TNetDirectoryConnection	{
  TSocket* fSocket;

public:

TNetDirectoryConnection::TNetDirectoryConnection(const char* host, int port)	{
	fSocket = new TSocket(host, port);
	printf("Connected to %s:%d\n", host, port);
}

int TNetDirectoryConnection::Reconnect()  {
	std::string host = fSocket->GetName();
	int         port = fSocket->GetPort();
	fSocket->Close();
	delete fSocket;
	fSocket = new TSocket(host.c_str(), port);
	printf("Connected to %s:%d\n", host.c_str(), port);
	return 0;
}

void TNetDirectoryConnection::Request(const char* req)  {
	if (gVerbose)
	  printf("Request [%s]\n", req);
	int s = fSocket->Send(req);
	//printf("Request sent %d\n", s);
}

TObject* TNetDirectoryConnection::ReadObject(TClass* type)	{
	TMessage *mr = 0;
	int r = fSocket->Recv(mr);
	//printf("ReadObject recv %d\n", r);
	if (r <= 0) {
		printf("Error reading from socket!\n");
  return NULL;
	}

	TObject *obj = NULL;

	if (mr) {
		//mr->Print();
		obj = (TObject*)mr->ReadObjectAny(mr->GetClass());
	}

	//printf("mr %p, obj %p, class %p, %s\n", mr, obj, mr->GetClass(), mr->GetClass()->GetName());

	if (obj) {
		//obj->Print();
		if (!obj->InheritsFrom(type)) {
			if (obj->IsA() == TObjString::Class()) {
				TObjString *ostr = (TObjString*)obj;
					printf("Instead of a %s, received a %s reading \'%s\'\n", type->GetName(), obj->IsA()->GetName(), ostr->GetName());
					return NULL;
			}		
			printf("Object type mismatch, received %s, expected %s\n", obj->IsA()->GetName(), type->GetName());
			return NULL;
		}
	}

	if (mr)
		delete mr;
	return obj;
  }
}

