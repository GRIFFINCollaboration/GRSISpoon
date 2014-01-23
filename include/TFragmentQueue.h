#ifndef TTIGFRAGMENTQUEUE_H
#define TTIGFRAGMENTQUEUE_H

#include <stdio.h>
#include <queue>


#ifndef __CINT__
#define _GLIBCXX_USE_NANOSLEEP 1
#include <thread>
#include <mutex>
#endif

#include<TObjArray.h>
#include<TStopwatch.h>

#include "TTigFragment.h"


class TFragmentQueue : public TObject {
	
	public:
		static TFragmentQueue *instance();
		virtual ~TFragmentQueue();

	private:
		static TFragmentQueue *fFragmentQueueClassPointer;
		TFragmentQueue();
	

		std::queue<TTigFragment*> fFragmentQueue;
		int fFragsInQueue;

		TObjArray *fFragmentStorage;

		void StatusUpdate();
		bool fStatusUpdateOn;

		bool fStop;
		
		int fragments_in;		
		int fragments_out;

		TStopwatch *sw;
		void ResetRateCounter();

		unsigned int fTotalFragsIn;
		unsigned int fTotalFragsOut;	

#ifndef __CINT__
#ifndef NO_MUTEX
	public:
		static std::mutex All;
		static std::mutex Sorted;
#endif
#endif

	public:
		void Add(TTigFragment*);

		TTigFragment *Get();	
	
		void Pop();
		TTigFragment *PopFragment();

		int Size();

		void StartStatusUpdate();
		void StopStatusUpdate();
		void CheckStatus();

		unsigned int GetTotalFragsIn() { return fTotalFragsIn;}
		unsigned int GetTotalFragsOut()	{	return fTotalFragsOut;}

		bool Running() { return !fStop;}
		void Stop() { fStop = true;}
		
		ClassDef(TFragmentQueue,0);
};






#endif
