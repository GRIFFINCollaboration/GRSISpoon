#include <vector>

#ifdef __CINT__
#include "process.cxx"
#else
void process(void);
#endif

#include "TTigFragment.h"

void processFragment(TTigFragment *frag) 
{
   // put things that are to be done on a per-fragment basis here
}

void processEvent(const std::vector<TTigFragment> &ev)
{
   // put things that are to be done on a per-event basis here
}

void empty_process()
{
   // just in case one wants to execute this with ".x" in an interactive ROOT session
   process();
}



