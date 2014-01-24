
#include "TFragmentQueue.h"

#include "CalibrationManager.h"
#include "RootIOManager.h"


std::mutex TFragmentQueue::All;
std::mutex TFragmentQueue::Sorted;

ClassImp(TFragmentQueue);

TFragmentQueue *TFragmentQueue::fFragmentQueueClassPointer = NULL;

TFragmentQueue *TFragmentQueue::instance()	{
	while(TFragmentQueue::All.try_lock())	{
		//do nothing
	}
	if(fFragmentQueueClassPointer==NULL)	{
	//printf(BLUE "\nfrag que ptr = 0x%08x" RESET_COLOR "\n",fFragmentQueueClassPointer);
		fFragmentQueueClassPointer = new TFragmentQueue();
	//printf(RED "\nfrag que ptr = 0x%08x" RESET_COLOR "\n",fFragmentQueueClassPointer);
	}
	TFragmentQueue::All.unlock();
	return fFragmentQueueClassPointer;
	
}

TFragmentQueue::TFragmentQueue()	{	
	//printf(DRED "\n\tFragment Queue Created." RESET_COLOR "\n");
	fFragsInQueue = 0;

	fragments_in  = 0;		
	fragments_out = 0;

	sw = new TStopwatch();
	sw->Start();

	fStop = false;

	//StartStatusUpdate();

	fTotalFragsIn = 0;
	fTotalFragsOut = 0;
}

TFragmentQueue::~TFragmentQueue()	{	}



void TFragmentQueue::StartStatusUpdate()	{
	fStatusUpdateOn = true;

	std::thread statusUpdate(&TFragmentQueue::StatusUpdate, this);
	statusUpdate.detach();

}

void TFragmentQueue::StopStatusUpdate()	{
	fStatusUpdateOn = false;
}



void TFragmentQueue::Add(TTigFragment *frag)	{
	CalibrationManager::instance()->CalibrateFragment(frag);

	unsigned int added_test = fTotalFragsIn;

	//if(fTotalFragsIn == 0){
	//	printf("\nIn fragment queue %i\n", frag->MidasId);
	//}

	
		//std::unique_lock<std::mutex> sorted(Sorted,std::defer_lock);


		//sorted.lock();
		
		while(!TFragmentQueue::Sorted.try_lock())	{
			//do nothing	
		}
		fTotalFragsIn++;

		fFragmentQueue.push(frag);
		fFragsInQueue++;
		fragments_in++;
		//sorted.unlock();
	
		TFragmentQueue::Sorted.unlock();


	return;
	//printf("Adding frag:\t%i\tNumber in Q = %i\n",frag->MidasId,fFragsInQueue);
}

TTigFragment *TFragmentQueue::Get()	{	

    //std::unique_lock<std::mutex> sorted(Sorted,std::defer_lock);
    //sorted.lock();
	while(TFragmentQueue::Sorted.try_lock())	{
		//do nothing
	}


	TTigFragment *frag = (fFragmentQueue.back());	

    	TFragmentQueue::Sorted.unlock();
	//printf("\tGetting frag:\t%i\tNumber in Q = %i\n",frag->MidasId,fFragsInQueue);
	return frag;
}

void TFragmentQueue::Pop()	{	
    //std::unique_lock<std::mutex> sorted(Sorted,std::defer_lock);
    //sorted.lock();
	while(!TFragmentQueue::Sorted.try_lock())	{ 
		//do nothing
	}	

	TTigFragment *frag = (fFragmentQueue.front());	
	fFragmentQueue.pop();
	fFragsInQueue--;
	fragments_out++;
	//fTotalFragsOut++;
	TFragmentQueue::Sorted.unlock();
	delete frag;
}

TTigFragment *TFragmentQueue::PopFragment()
{
	//std::unique_lock<std::mutex> sorted(Sorted,std::defer_lock);
	//sorted.lock();
	while(!TFragmentQueue::Sorted.try_lock())	{
		//do nothing
	}
	
	TTigFragment *frag = fFragmentQueue.front();
	if(frag)	{
		fFragmentQueue.pop();
		fFragsInQueue--;
		fragments_out++;
		fTotalFragsOut++;
	}
    TFragmentQueue::Sorted.unlock();
	return frag;
}

int TFragmentQueue::Size()	{
	return fFragsInQueue;
}

void TFragmentQueue::CheckStatus()	{
	//std::unique_lock<std::mutex> all(All,std::defer_lock);
	//all.lock();
	while(!TFragmentQueue::All.try_lock())	{
		//do nothing
	}
	

	printf( BLUE   "# Fragments currently in Q = %d" RESET_COLOR "\n",Size());
	printf( DGREEN "# Fragments currently in T = %d" RESET_COLOR "\n",RootIOManager::instance()->TreeSize());

	printf( BLUE   "# Total Fragments put in Q     = %d" RESET_COLOR "\n",fTotalFragsIn);
	printf( DGREEN "# Total Fragments taken from Q = %d" RESET_COLOR "\n",fTotalFragsOut);

	TFragmentQueue::All.unlock();
	return;
};

void TFragmentQueue::StatusUpdate()	{

	float time = 0;
	float frag_rate_in = 0;
	float frag_rate_out = 0;

	 //std::unique_lock<std::mutex> all(All,std::defer_lock);


	while(fStatusUpdateOn)	{
		//printf("Fragments in que: %i\n",frag_q_ptr->Size());
		time = sw->RealTime();
		frag_rate_in = fragments_in/time; 
		frag_rate_out = fragments_out/time;
		while(!TFragmentQueue::All.try_lock()){
			//do nothing
		}



		printf(BLUE "\n\tfrags rate in  = %.2f/sec, nqueue = %d\n" RESET_COLOR,frag_rate_in, Size());
		printf(DGREEN "\tfrags rate out = %.2f/sec, ntree  = %d\n" RESET_COLOR,frag_rate_out, RootIOManager::instance()->TreeSize());
		TFragmentQueue::All.unlock();
//		TThread::ps();
		ResetRateCounter();
		sw->Start();
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	}
	//TThread::CleanUp();
}

void TFragmentQueue::ResetRateCounter()	{
	//std::unique_lock<std::mutex> all(All,std::defer_lock);
	//all.lock();
	while(!TFragmentQueue::All.try_lock())	{
		//do nothing
	}

	fragments_in	=	0;		
	fragments_out	= 0;
	TFragmentQueue::All.unlock();
}



