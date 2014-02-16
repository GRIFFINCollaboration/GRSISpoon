

#include "TParser.h"

#include "TTigFragment.h"
#include "TFragmentQueue.h"



TParser *TParser::fParser = 0;
const unsigned int TParser::fgMaxTriggerId = 1024 * 1024 * 16; // 24 bits internally

ClassImp(TParser)

TParser *TParser::instance()	{
	if(!fParser)
		fParser = new TParser();
	return fParser;
}

TParser::TParser()	{
	ResetCounters();
}


void TParser::ResetCounters()	{
	fLastMidasId   = 0;
	fLastTriggerId = 0;
	
	//fragment_id_map->clear();

}



TParser::~TParser()	{	}


int TParser::TigressDATAToFragment(int *data, int size,unsigned int midasserialnumber, time_t midastime) {

	//if(fTestMode)
	//	gSystem->Sleep(10);

	int FragmentsFound = 1;

	TTigFragment *eventfragment = new TTigFragment();//currentfragment;
	//eventfragment->Clear();	

	bool badtimestamp = false;
	bool needtodeletelast = false;
	eventfragment->MidasTimeStamp = midastime;
	eventfragment->MidasId = midasserialnumber;	 

	//if(fLastMidasId == 0x0)
		fLastMidasId = midasserialnumber;
	//else if((fLastMidasId+1) == midasserialnumber)
	//	fLastMidasId = midasserialnumber;
	//else	{
		//printf(RED"\tmissing midas ids!\t LastMidasID = %i\t CurrentMidasId = %i\n"RESET_COLOR,fLastMidasId,midasserialnumber);
		fLastMidasId = midasserialnumber;
	//}
	
	for(int x=0;x<size;x++)	{
		int dword =	*(data+x);
		unsigned int type	=	(dword & 0xf0000000); //>> 28;
		int slave =	(dword & 0x0ff00000) >> 20;
		int value =	(dword & 0x0fffffff);
		switch(type)	{
			case 0x00000000: // waveform data 
				if(eventfragment->wavebuffer.size() > (100000) ) {
					printf("number of wave samples found is to great\n"); 
					break;
				}       
				if (value & 0x00002000) {
					int temp =  value & 0x00003fff;
					temp = ~temp;
					temp = (temp & 0x00001fff) + 1;
					eventfragment->wavebuffer.push_back(-temp);	//eventfragment->SamplesFound++;
				} else {
					eventfragment->wavebuffer.push_back((value & 0x00001fff)); //eventfragment->SamplesFound++;
				}
				if ((value >> 14) & 0x00002000) {
					int temp =  (value >> 14) & 0x00003fff;
					temp = ~temp;
					temp = (temp & 0x00001fff) + 1;
					eventfragment->wavebuffer.push_back(-temp);	//eventfragment->SamplesFound++;
				} else {
					eventfragment->wavebuffer.push_back( ((value >> 14) & 0x00001fff) );	//eventfragment->SamplesFound++;
				}
				break; 
			case 0x10000000: // trapeze data 
				//currently not used.
				break;          
			case 0x40000000: // CFD Time 
				eventfragment->SlowRiseTime = value & 0x08000000;
				eventfragment->Cfd = value & 0x07ffffff;
				{
		 			// remove vernier for now and calculate the time to the trigger
					int tsBits;
					int cfdBits;
					if ( eventfragment->DigitizerType == "tig10" ) {
						cfdBits = (eventfragment->Cfd >> 4);
						tsBits  = eventfragment->TimeStampLow & 0x007fffff;

						// probably should check that there hasn't been any wrap around here
						eventfragment->TimeToTrig = tsBits - cfdBits;
					} else if ( eventfragment->DigitizerType == "tig64" ) {
						eventfragment->TimeToTrig = (eventfragment->Cfd >> 5);
						// cfdBits	= (eventfragment->Cfd >> 5);
						// tsBits  = eventfragment->TimeStampLow & 0x003fffff;
					} else {
						printf("CFD obtained without knowing digitizer type with midas Id = %d!\n",eventfragment->MidasId);
	  				}
				}		
				break;
				case 0x50000000: // Charge 
					if( strncmp(eventfragment->DigitizerType.c_str(),"tig10",5) == 0)	{
						eventfragment->PileUp = (value &  0x04000000);
						eventfragment->Charge	= (value &	0x03ffffff);
						if(value & 0x02000000)	{
							eventfragment->Charge = -( (~(value & 0x01ffffff)) & 0x01ffffff)+1;
						}
					}	
					else if( strncmp(eventfragment->DigitizerType.c_str(),"tig64",5) == 0) {
						eventfragment->Charge	= (value &	0x003fffff);
						if(value & 0x00200000)	{
							eventfragment->Charge = -( (~(value & 0x001fffff)) & 0x001fffff)+1;
						}
					}
					else{	//printf("%i  problem extracting charge, digitizer not set(?)\n", error++); IsBad = true;}
							//printf("%i  problem extracting charge, digitizer not set(?)\n", error++);  // IsBad = true;
						eventfragment->DigitizerType = "unknown";
						eventfragment->Charge	= (value &	0x03ffffff);
						if(value & 0x02000000)	{
							eventfragment->Charge = -( (~(value & 0x01ffffff)) & 0x01ffffff)+1;
						}
					}
        			break;
				case 0x60000000: // led ?? leading edge!
					eventfragment->Led = (value & 0x07ffffff);
        			break;
      			case 0x80000000: // Event header 		
					{
		  				unsigned int LastTriggerIdHiBits = fLastTriggerId & 0xFF000000; // highest 8 bits, remainder will be determined by the reported value
	  					unsigned int LastTriggerIdLoBits = fLastTriggerId & 0x00FFFFFF;
						if ( value < fgMaxTriggerId / 10 ) {
							// the trigger id has wrapped around	
							if ( LastTriggerIdLoBits > fgMaxTriggerId * 9 / 10 ) {
								eventfragment->TriggerId = LastTriggerIdHiBits + value + fgMaxTriggerId;
								printf(DBLUE "We are looping new trigger id = %d, last trigger hi bits = %d, last trigger lo bits = %d, value = %d, 				midas = %d" RESET_COLOR "\n", eventfragment->TriggerId, LastTriggerIdHiBits, LastTriggerIdLoBits, value, 	midasserialnumber);				
							} else {
								eventfragment->TriggerId = LastTriggerIdHiBits + value;
							}
						} else if ( value < fgMaxTriggerId * 9 / 10 ) {
							eventfragment->TriggerId = LastTriggerIdHiBits + value;
						} else {
							if ( LastTriggerIdLoBits < fgMaxTriggerId / 10 ) {
								eventfragment->TriggerId = LastTriggerIdHiBits + value - fgMaxTriggerId;
								printf(DRED "We are backwards looping new trigger id = %d, last trigger hi bits = %d, last trigger lo bits = %d, value = %d, midas = %d" RESET_COLOR "\n", eventfragment->TriggerId, LastTriggerIdHiBits, LastTriggerIdLoBits, value, midasserialnumber);
							} else {
								eventfragment->TriggerId = LastTriggerIdHiBits + value;			
							}
						}	
					}
					//fragment_id_map[value]++;
					//eventfragment->FragmentId = fragment_id_map[value];
					fLastTriggerId = eventfragment->TriggerId;
					break; 
				case 0xa0000000:  // timestamp
				{
					int time[5];
					time[0] = *(data + x);
					x += 1;
					time[1] =	*(data + x);	//& 0x0fffffff;
					if( (time[1] & 0xf0000000) != 0xa0000000) {
						if( ( (time[1] & 0xf0000000) == 0xc0000000) &&  ( ((time[1] & 0x000000ff) == 0x0000003f) || ((time[1] & 0x000000ff) == 0x0000001f) ) ) { x-=1; break;}
						//IsBad = true;
						badtimestamp = true;
//						printf("timestamp probelm 1.\t%08x\t%08x\t%08x\t%i\n",time[0],time[1], 0xa0000000,x ); //PrintBank(data,size); 
						break;
					} 
					if( ((time[0] & 0x0f000000)==0) && ((time[1] & 0x0f000000)==0) ) { //tig64
						eventfragment->DigitizerType = "tig64";
						eventfragment->TimeStampLow = time[0] & 0x00ffffff;
						eventfragment->TimeStampHigh = time[1] & 0x00ffffff;
					}
					else { //tig10 
						eventfragment->DigitizerType = "tig10";
						eventfragment->TimeStampLow = time[0] & 0x00ffffff;
						eventfragment->TimeStampHigh = time[1] & 0x00ffffff;
						x += 1;
						time[2] =	*(data+x);//	& 0x0fffffff;
						if( (time[2] & 0xf0000000) != 0xa0000000) {
							x = x-1;  /// If a tig10 is missing some timestamp words.
							break;
							//printf("timestamp probelm 2.\t%08x\t%08x\t%08x\t%i\n",time[0],time[2], 0xa0000000,x ); 
							//PrintBank(data,size); break;
						} 
						x += 1;
						time[3] =	*(data+x);//	& 0x0fffffff;
						if( (time[3] & 0xf0000000) != 0xa0000000) {
							//printf("timestamp probelm 3.\t%08x\t%08x\t%08x\t%i\n",time[0],time[3], 0xa0000000,x ); 
							badtimestamp = true; 
							break;
						} 
						x += 1;
						time[4] =	*(data+x);//	& 0x0fffffff;
						if( (time[4] & 0xf0000000) != 0xa0000000) {
							//printf("timestamp probelm 4.\t%08x\t%08x\t%08x\t%i\n",time[0],time[4], 0xa0000000,x ); 
							badtimestamp = true; 
							break;
						}
						for(int nstamp =0; nstamp<5; nstamp++)	{
							int subtype = (time[nstamp] & 0x0f000000);
							switch(subtype)	{
								case 0x00000000:
									eventfragment->TimeStampLow = (time[nstamp] & 0x00ffffff);
									break;
								case 0x01000000:
									eventfragment->TimeStampHigh = (time[nstamp] & 0x00ffffff);
									break;
								case 0x02000000:
									eventfragment->TimeStampLive = (time[nstamp] & 0x00ffffff);
									break;
								case 0x04000000:
									eventfragment->TimeStampTR	 = (time[nstamp] & 0x00ffffff);
									break;
								case 0x08000000:
									eventfragment->TimeStampTA	 = (time[nstamp] & 0x00ffffff);
								 break;
								default:
									badtimestamp = true;
//									printf("timestamp probelm default.\t%08x\t%08x\t%i\n",time[1], 0xa0000000,x );  
									break;
							};
							eventfragment->SetTimeStamp();
						}
					}
				}
				//has_timestamp = true;
        break;
      case 0xb0000000: // Trigger Pattern
				eventfragment->TriggerBitPattern = value;
				break;
      case 0xc0000000: // port info,  New Channel 
				//eventfragment->channel =  FSPC_to_channel( value ) ;
        eventfragment->ChannelAddress =  value;
				//if(slave<3) {eventfragment->DigitizerType = "tig64";}
				//else{eventfragment->DigitizerType = "tig10";}
        break;
      case 0xe0000000: // Event Trailer
				if(needtodeletelast)	{
					delete eventfragment;
					FragmentsFound--;
					//printf("deleting fragment.\n");
				}
				else	{	
					//eventfragment->Print();
					//CalibrationManager::instance()->CalibrateFragment(eventfragment);
					TFragmentQueue::instance()->Add(eventfragment);
				}
				return FragmentsFound;
				break;                                    
      case 0xf0000000: // EventBuilder Timeout
        printf("Event builder error, builder timed out ,found type: %08x\n", type); 
				//IsBad = true;
				break;
      default:  
				printf("Unpacking error: found data word.\t%08x\t%i\n",dword,x);
				//IsBad = true;
				break;
		};	

		if(badtimestamp)	{
			//PrintBank(data,size);	
			//PrintBank(data,size);	
//			printf("Removing Fragment.\n");
			delete eventfragment;
//			printf("\tFragment Removed.\n");
			return 0;
		}

		//printf("eventfragment-> = 0x%08x\n",dword);
		if(eventfragment->Cfd >=0 && ( ((*(data+x+1))&0xf0000000) != 0xe0000000) ) { //.....tig64
			//CalibrationManager::instance()->CalibrateFragment(eventfragment);
			TFragmentQueue::instance()->Add(eventfragment);
			//eventfragment->Print();
			TTigFragment *temp = eventfragment;
			//eventfragment = (TTigFragment*)fragmentptrs->At(FragmentsFound++);
			//eventfragment->Print();
			eventfragment = new TTigFragment();
			eventfragment->Clear();
			//TFragmentQueue::instance()->Add(eventfragment);


			eventfragment->MidasTimeStamp			=	temp->MidasTimeStamp;
			eventfragment->MidasId						=	temp->MidasId;
			eventfragment->TriggerId					=	temp->TriggerId;
			//fragment_id_map[value]++;
		  	//eventfragment->FragmentId = fragment_id_map[value];
			eventfragment->TriggerBitPattern	=	temp->TriggerBitPattern;	
			eventfragment->DigitizerType			=	temp->DigitizerType; 

			eventfragment->TimeStampLow				=	temp->TimeStampLow;
			eventfragment->TimeStampHigh			=	temp->TimeStampHigh;
			needtodeletelast = true;
		}
	}
	if(needtodeletelast)	{
		delete eventfragment;
		FragmentsFound--;
		//if(strncmp(eventfragment->DigitizerType.c_str(),"tig10",5) == 0)
		//	printf("delete framgent.\n");
	}
	else{
		//CalibrationManager::instance()->CalibrateFragment(eventfragment);
		TFragmentQueue::instance()->Add(eventfragment);
		//eventfragment->Print();
	}
	return FragmentsFound;
}	


int TParser::GriffinDATAToFragment(int *data, int size,unsigned int midasserialnumber, time_t midastime)	{

	return 0;
}
