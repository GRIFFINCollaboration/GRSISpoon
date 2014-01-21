
#include "CalibrationManager.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cctype>

#include <string>

ClassImp(CalibrationManager)

CalibrationManager *CalibrationManager::fCalibrationManager = 0;
std::string CalibrationManager::WhiteSpaces = ( " \n\f\r\t\v" );


CalibrationManager *CalibrationManager::instance()	{
  if(!fCalibrationManager)	
    fCalibrationManager = new CalibrationManager();
  return fCalibrationManager;
}

CalibrationManager::CalibrationManager()	{	
  fuseodbfile	= false;
  fusecalfile	= false;
  set_enum_map();

  fCalibrationManager = this;
}

CalibrationManager::~CalibrationManager()	{	}


void CalibrationManager::ReadXMLOdb(VirtualOdb *vodb)	{

  printf("now mapping odb info.\n");
  int NumberOfChannels = vodb->odbReadUint32("/Analyzer/Parameters/Cathode/Config/N");

  for(int x=0;x<NumberOfChannels;x++)        {
    TChannel *channel;
    int fspc_value	=	vodb->odbReadUint32("/Analyzer/Parameters/Cathode/Config/FSCP",x);
    //printf("fspc = 0x%08x\n",fspc_value);
    if(!AddressChannelMap[fspc_value])	
      channel = new TChannel();
    else
      channel = AddressChannelMap[fspc_value]; 
    channel->SetChannel(fspc_value,
			x,
			vodb->odbReadString("/Analyzer/Parameters/Cathode/Config/Name",x));

    char type = vodb->odbReadByte("/Analyzer/Parameters/Cathode/Config/Type",x);
    channel->SetTypeInfo(type,
			 vodb->odbReadString("/Analyzer/Parameters/Cathode/type/name",type),
			 vodb->odbReadString("/Analyzer/Parameters/Cathode/type/title",type),
			 vodb->odbReadString("/Analyzer/Parameters/Cathode/type/units",type),
			 vodb->odbReadInt("/Analyzer/Parameters/Cathode/type/nbins",type),
			 vodb->odbReadInt("/Analyzer/Parameters/Cathode/type/nsamp",type),
			 vodb->odbReadUint32("/Analyzer/Parameters/Cathode/type/MaxCharge",type),										 			
			 vodb->odbReadFloat("/Analyzer/Parameters/Cathode/type/maxE",channel->type));
			
    //fspc->integration     = GetODB()->odbReadInt("/Analyzer/Parameters/Cathode/type/integration",fspc->type);
               
    channel->AddENGCoefficient(vodb->odbReadFloat("/Analyzer/Parameters/Cathode/Config/o",x));
    channel->AddENGCoefficient(vodb->odbReadFloat("/Analyzer/Parameters/Cathode/Config/g",x));

    //AddressChannelMap[fspc_value] = channel;//->insert(std::make_pair(fspc_value,fspc));
    AddChannel(channel);
  }
  printf("%i FSPCs now mapped.\n",NumberOfChannels);
                
  //	for(int x=0;x<NumberOfChannels;x++)        {
  //		unsigned int fspc_value = vodb->odbReadUint32("/Analyzer/Parameters/Cathode/config/FSCP",x);
  //		TChannel *channel = AddressChannelMap[fspc_value];
  //		printf("FSPC: 0x%08x\n",fspc_value);
  //		channel->Print();
  //		printf("0x%08x\t%i\t%s\t"BLUE"%f\t%f"RESET_COLOR"\n",fspc_value,AddressCh[fspc_value]->number,FSPC_Map[fspc_value]->name.c_str(),FSPC_Map[fspc_value]->gain,FSPC_Map[fspc_value]->offset  );
  //	}
        

}



void CalibrationManager::CalibrateFragment(TTigFragment *frag)	{
  if(!frag)
    return;

  TChannel *temp;
  if(NameChannelMap.count(frag->ChannelName.substr(0,10)) == 1)	{
	temp = NameChannelMap[frag->ChannelName.substr(0,10)];
  } 
  else if(AddressChannelMap.count(frag->ChannelAddress & 0x00ffffff) == 1)	{
	temp = AddressChannelMap[frag->ChannelAddress & 0x00ffffff];
  }
  else	{
    return;
  }
  //printf("	frag->ChannelAddress & 0x00ffffff  =  0x%08x\t0x%08x\n",frag->ChannelRaw & 0x00ffffff,temp);
  temp->CalibrateFragment(frag);

	
  return;
}


void CalibrationManager::AddChannel(TChannel *channel)	{
  //	channel->Print();
  AddressChannelMap[channel->fspc] = channel;//->insert(std::make_pair(fspc_value,fspc));
  std::string temp = channel->name.substr(0,10);
  NameChannelMap[temp] = channel;//->insert(std::make_pair(fspc_value,fspc));
}

void CalibrationManager::AddVirtualChannel(TChannel *channel)	{
  //channel->Print();
	if(channel->name != "")	{
		if(NameChannelMap.count(channel->name)==1)	{
			MergeChannels(NameChannelMap[channel->name],channel);
		}
	}
	else	{
		NameChannelMap[channel->name] = channel;
	}
	if(channel->fspc != 0xffffffff)	{
		if(AddressChannelMap.count(channel->fspc) ==1)	{
			MergeChannels(AddressChannelMap[channel->fspc],channel);
		}
	}
	else	{
		AddressChannelMap[channel->fspc] = channel;
	}
}

void CalibrationManager::MergeChannels(TChannel *chan1, TChannel *chan2)	{
	//printf("============================\n");
	//printf("Merge called.\n");
	//chan1->Print();
	//chan2->Print();
	//printf("============================\n");

	if(!chan1 || !chan2)
		return;

	if(chan2->fspc !=  0xffffffff)
		chan1->fspc = chan2->fspc;
	if(chan2->type !=	0)
		chan1->type = chan2->type;
	if(chan2->integration != 0)
		chan1->integration = chan2->integration;
	if(chan2->number != 0)
		chan1->number = chan2->number;
	if(chan2->nbins != 0)
		chan1->nbins = chan2->nbins;
	if(chan2->nsamp != chan1->nsamp)
		chan1->nsamp = chan2->nsamp;
	if(chan2->maxchg != 0)
		chan1->maxchg = chan2->maxchg;
	if(chan2->maxeng != 0)
		chan1->maxeng = chan2->maxeng;
	if(chan2->detector != 0)
		chan1->detector = chan2->detector;
	if(chan2->pixel != std::make_pair(0,0))
		chan1->pixel = chan2->pixel;

	if(chan2->name.length() != 0)
		chan1->name = chan2->name;
	if(chan2->type_title.length() != 0)   
		chan1->type_title = chan2->type_title;
	if(chan2->type_name.length() != 0)   
        chan1->type_name = chan2->type_name;
	if(chan2->type_units.length() != 0)   
        chan1->type_units = chan2->type_units;

	if(chan2->ENGCoefficients.size() != 0)
		chan1->ENGCoefficients = chan2->ENGCoefficients; 

	if(chan2->CFDCoefficients.size() != 0)
		chan1->CFDCoefficients = chan2->CFDCoefficients; 

	if(chan2->LEDCoefficients.size() != 0)
		chan1->LEDCoefficients = chan2->LEDCoefficients; 
	if(chan2->TIMECoefficients.size() != 0)
		chan1->TIMECoefficients = chan2->TIMECoefficients; 
		
	delete chan2;


}


//===========================================================================//
//===========================================================================//
void CalibrationManager::ReadCalibrationFile()	{
  printf("attempting to read in file %s...\t",fcalfilename.c_str()); fflush(stdout);

  //do magic, fill cal_ino


    
  ifstream infile;
  infile.open(fcalfilename);
  if(!infile)	{
    printf("could not open file.\n");
    return;
  }

  fflush(stdout);

  TChannel *channel = 0;

  std::string line;
  int linenumber = 0;
  int newchannels = 0;
	
  bool creatednewchannel = false;
  bool brace_open = false;
  int detector = 0;
  std::string name;

  std::pair<int,int> pixel = std::make_pair(0,0);

  while(std::getline(infile,line))        {
    linenumber++;
    //printf("%s \n",line.c_str());
    trim(&line);
    //
    int comment = line.find("//");
    if(comment != std::string::npos)        {
      line =  line.substr(0,comment);
    }
    if(!line.length())
      continue;
    //
    int openbrace = line.find("{");
    int closebrace  = line.find("}");

    if(closebrace != std::string::npos)	{
      brace_open = false;
      if(channel && (name.length()>0)) {//&& pixel.first && pixel.second )
	AddVirtualChannel(channel);
	newchannels++;
      }
      else if(creatednewchannel)
	delete channel;
      channel = 0;
      name.clear();
      detector = 0;
    }

    if(brace_open) {
      int ntype = line.find(":");
      if(ntype != std::string::npos)	{
	std::string type = line.substr(0,ntype);
	trim(&type);
	line = line.substr(ntype+1,line.length());
	trim(&line);
	std::istringstream ss( line );
	switch(StringToEnum(type))      {
	case NAME:  // this is to rename a detector channel (by creating a new TChannel) normally the name should be taken from the is statement below.
	  channel->SetName(line);
	  break;
	case DETECTOR:
	  {	
	    int tmpdet;
	    ss >> tmpdet;							
	    channel->SetDetector(tmpdet); 
	  }
	  break;
	case ADDRESS:
		{
			int tmpadd;
			ss >> tmpadd;
			if(tmpadd>0x1000000)
				tmpadd = tmpadd & 0x00ffffff;
			channel->SetAddress(tmpadd);
		}
		break;
	case PIXEL:
	  {
	    int first, second;
	    ss >> first; ss >> second;
	    channel->SetPixel(first,second);
	  }			
	  break;
	case COEFFICIENTS:  //careful here, this is doing the same thing as ENG_COEFF....
	  {
	    channel->DestroyENGCal();
	    while (!ss.eof())  {
	      double value;
	      ss >> value; 
	      channel->AddENGCoefficient(value);
	    }
	  }
	  break;
	case NUMBER:		//this is the number in the fspc list from the odb, probable shouldn't use this either...
	  {
	    int tmpnum;
	    ss >> tmpnum;
	    channel->SetNumber(tmpnum);
	  }
	  break;
	case ENG_COEFF:
	  //printf("here?\n");
	  {
	    channel->DestroyENGCal();
	    double value;
	    while(ss>>value)	{
	      //printf("value: %i\n",value);
	      channel->AddENGCoefficient(value);
	    }
	  }
	  break;
	case CFD_COEFF:
	  {
	    channel->DestroyCFDCal();
	    while (!ss.eof())  {
	      double value;
	      ss >> value; 
	      channel->AddCFDCoefficient(value);
	    }
	  }
	  break;
	case LED_COEFF:
	  {
	    channel->DestroyLEDCal();
	    while (!ss.eof())  {
	      double value;
	      ss >> value; 
	      channel->AddLEDCoefficient(value);
	    }
	  }
	  break;
	case TIME_COEFF:
	  {
	    channel->DestroyTIMECal();
	    while (!ss.eof())  {
	      double value;
	      ss >> value; 
	      channel->AddTIMECoefficient(value);
	    }
	  }
	  break;
	case STREAM:
	  {
	    int tmpstream;
	    ss >> tmpstream;				 
	    channel->SetStream(tmpstream);	
	  }
	default:
	  break;				
	};
      }
    }

    if(openbrace != std::string::npos)	{
      brace_open = true;
      name = line.substr(0,openbrace).c_str();
      if(GetChannel(name.c_str()))
	channel = GetChannel(name.c_str());
      else	{
	channel = new TChannel();
	channel->name = name;
	creatednewchannel = true;
      }


    }
  }
  printf("%i lines from %s parsed and turned into %i TChannels.\n",linenumber,fcalfilename.c_str(),newchannels);


}

void CalibrationManager::trim(std::string* line, const std::string &trimChars)	{
  if(line->length() == 0)
    return;
  std::size_t found = line->find_first_not_of(trimChars);
  if(found != std::string::npos)
    *line = line->substr(found,line->length());
  found = line->find_last_not_of(trimChars);
  if(found != std::string::npos)
    *line = line->substr(0,found+1);
  return;
}




void CalibrationManager::set_enum_map() {
  std::string key = "DETECTOR";
  enum_map[key] = DETECTOR;
  key = "PIXEL";
  enum_map[key] = PIXEL;
  key = "COEFFICIENTS";
  enum_map[key] = COEFFICIENTS;
  key = "PIXEL";
  enum_map[key] = PIXEL;        
  key = "NUMBER";
  enum_map[key] = NUMBER;        
  key	=	"ENG_COEFF";
  enum_map[key] = ENG_COEFF;        
  key = "CFD_COEFF";
  enum_map[key] = CFD_COEFF;        
  key = "LED_COEFF";
  enum_map[key] = LED_COEFF;        
  key = "TIME_COEFF";
  enum_map[key] = TIME_COEFF;
  key = "NAME";
  enum_map[key] = NAME;
  key = "STREAM";
  enum_map[key] = STREAM;
  key = "ADDRESS";
  enum_map[key] = ADDRESS;
}


int CalibrationManager::StringToEnum(std::string input) {
  int j=0;
  while(input[j]) {

    char c = *(input.c_str() + j );
    c = toupper(c);
    input[j++] = c;
  }
  return enum_map[input];
}

