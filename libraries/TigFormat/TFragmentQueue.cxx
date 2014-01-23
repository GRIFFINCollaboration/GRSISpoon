
#include "TFragmentQueue.h"

#include "CalibrationManager.h"
#include "RootIOManager.h"


#include <TThread.h>

ClassImp(TFragmentQueue);

TFragmentQueue *TFragmentQueue::fFragmentQueueClassPointer = 0;

TFragmentQueue *TFragmentQueue::instance()	{
	if(!fFragmentQueueClassPointer)
		fFragmentQueueClassPointer = new TFragmentQueue();
	return fFragmentQueueClassPointer;
}

TFragmentQueue::TFragmentQueue()	{	
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

//	while (fFragsInQueue > 5000000) {
//		TThread::UnLock();
		//RootManager::instance()->GetTree()->FlushBaskets();
//		gSystem->Sleep(1000);
//		TThread::Lock();
// }
	std::unique_lock<std::mutex> sorted(Sorted,std::defer_lock);
	sorted.lock();

	fTotalFragsIn++;

	fFragmentQueue.push(frag);
	fFragsInQueue++;
	fragments_in++;
	sorted.unlock();
	//printf("Adding frag:\t%i\tNumber in Q = %i\n",frag->MidasId,fFragsInQueue);
}

TTigFragment *TFragmentQueue::Get()	{	

    std::unique_lock<std::mutex> sorted(Sorted,std::defer_lock);
    sorted.lock();

	TTigFragment *frag = (fFragmentQueue.back());	

    sorted.unlock();
	//printf("\tGetting frag:\t%i\tNumber in Q = %i\n",frag->MidasId,fFragsInQueue);
	return frag;
}

void TFragmentQueue::Pop()	{	
    std::unique_lock<std::mutex> sorted(Sorted,std::defer_lock);
    sorted.lock();
	TTigFragment *frag = (fFragmentQueue.front());	
	fFragmentQueue.pop();
	fFragsInQueue--;
	fragments_out++;
	fTotalFragsOut++;
	sorted.unlock();
	delete frag;
}

TTigFragment *TFragmentQueue::PopFragment()
{
	std::unique_lock<std::mutex> sorted(Sorted,std::defer_lock);
	sorted.lock();
	TTigFragment *frag = fFragmentQueue.front();
	if(frag)	{
		fFragmentQueue.pop();
		fFragsInQueue--;
		fragments_out++;
	}
    sorted.unlock();
	return frag;
}

int TFragmentQueue::Size()	{
	return fFragsInQueue;
}

void TFragmentQueue::CheckStatus()	{
	std::unique_lock<std::mutex> all(All,std::defer_lock);
	all.lock();
	printf( BLUE   "# Fragments currently in Q = %d" RESET_COLOR "\n",Size());
	printf( DGREEN "# Fragments currently in T = %d" RESET_COLOR "\n",RootIOManager::instance()->TreeSize());

	printf( BLUE   "# Total Fragments put in Q     = %d" RESET_COLOR "\n",fTotalFragsIn);
	printf( DGREEN "# Total Fragments taken from Q = %d" RESET_COLOR "\n",fTotalFragsOut);

	all.unlock();
	return;
};

void TFragmentQueue::StatusUpdate()	{

	float time = 0;
	float frag_rate_in = 0;
	float frag_rate_out = 0;

	 std::unique_lock<std::mutex> all(All,std::defer_lock);
	while(fStatusUpdateOn)	{
		//printf("Fragments in que: %i\n",frag_q_ptr->Size());
		time = sw->RealTime();
		frag_rate_in = fragments_in/time; 
		frag_rate_out = fragments_out/time;
		all.lock();
		printf(BLUE "\n\tfrags rate in  = %.2f/sec, nqueue = %d\n" RESET_COLOR,frag_rate_in, Size());
		printf(DGREEN "\tfrags rate out = %.2f/sec, ntree  = %d\n" RESET_COLOR,frag_rate_out, RootIOManager::instance()->TreeSize());
		all.unlock();
//		TThread::ps();
		ResetRateCounter();
		sw->Start();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	}
	//TThread::CleanUp();
}

void TFragmentQueue::ResetRateCounter()	{
	std::unique_lock<std::mutex> all(All,std::defer_lock);
	all.lock();
	fragments_in	=	0;		
	fragments_out	= 0;
	all.unlock();
}



