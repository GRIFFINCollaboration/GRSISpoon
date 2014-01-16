#ifndef TFRAGMENT_H
#define TFRAGMENT_H

#include<vector>
#include<queue>
#include<string>
#include<time.h>

//#include"TH1F.h"
#include<TRefArray.h>
#include<TNamed.h>
#include<TRandom.h>

#ifndef __CINT__
#include "Globals.h"
#endif

//using namespace std;

class TFragment : public TNamed	{

  public:
    TFragment();
    // Create the class and reserve the vector size for MaxChannel
    // Limit the number of dynamic allocation, so better perf but more memory used
    ~TFragment(); 

    time_t MidasTimeStamp;	//->
    unsigned int MidasId;	//->
    int TriggerId;	//->
    int FragmentId;	//->
    int TriggerBitPattern;		//->
    std::string DigitizerType; 	//->      // currently tig10 or tig64
    int ODBType;	//->
    
    std::string ChannelName;	//->
    int ChannelNumber;	//->
    int ChannelRaw;	//->
    int Cfd;	//->
    int Led;	//->
    int TimeToTrig; //->
    int Charge;	//->
    float ChargeCal;	//->
    
    int TimeStampLow;	//->
    int TimeStampHigh;	//->
    int TimeStampLive;	//->
    int TimeStampTR;  	//->       // triggers requested
    int TimeStampTA;	//->         // triggers accepted
    
    int SamplesFound;	//->
    //TH1F waveform;
    
    bool SlowRiseTime;	//->
    bool PileUp;	//->

    std::vector<int>  wavebuffer;	//->	
      
    void	Clear(); //!
    void 	Print(); //!
    
    bool	HasWave() { //!     
      return !wavebuffer.empty(); 
    };
    //in order to use root sort function when the fragments are in arrays 
    //puts newset id at the beginning of the array, older ids at the end.
    bool IsSortable() const {return kTRUE;}; //!
    int	 Compare(const TObject *obj) const; //! compare by trigger and fragment id 
        
    ClassDef(TFragment,1);  // TFragment structure
};
#endif // TFRAGMENT_H
