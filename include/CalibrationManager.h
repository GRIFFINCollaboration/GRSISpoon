
#ifndef CALIBRATIONMANAGER_H
#define CALIBRATIONMANAGER_H

#include <cstdio>
#include <map>
#include <string>
#include <utility>

#include "TChannel.h"
#include "VirtualOdb.h"

class	CalibrationManager	{

	public:
		static CalibrationManager *instance();
		~CalibrationManager();

		bool UseODBFromFile()					{ return fuseodbfile;};
		bool UseCALFromFile()					{ return fusecalfile;};

		const char *GetODBFileName()			{	return fodbfilename.c_str();};
		const char *GetCALFileName()			{	return fcalfilename.c_str();};

		void SetODBFileName(const char *oname)	{fodbfilename = oname; 
																						 printf("odb file set to: %s\n",oname);		
																						 fuseodbfile=true;};
		void SetCalFileName(const char *cname)	{fcalfilename = cname; 
																						 printf("cal file set to: %s\n",cname);
																						 fusecalfile=true;};

			


	private:
		static CalibrationManager *fCalibrationManager;
		CalibrationManager();

		std::map<int,TChannel*> AddressChannelMap;
		std::map<std::string,TChannel*> NameChannelMap;

		void MergeChannels(TChannel*,TChannel*);

		enum InfileOptions {JUNK, NAME, DETECTOR, COEFFICIENTS, PIXEL, NUMBER, ENG_COEFF, CFD_COEFF, LED_COEFF, TIME_COEFF, STREAM, ADDRESS};
		void set_enum_map();
		std::map<std::string,int> enum_map;
		int StringToEnum(std::string);

		static std::string WhiteSpaces;//( " \f\n\r\t\v" ); 
		void trim(std::string*,const std::string& trimChars = WhiteSpaces);

	public:
		void ReadXMLOdb(VirtualOdb*);
		void ReadCalibrationFile();

		TChannel *GetChannel(int fspc) {return AddressChannelMap[fspc];	};
		TChannel *GetChannel(const char *name) { std::string sname = name;
												 return NameChannelMap[sname];	};

		void AddChannel(TChannel*);
		void AddVirtualChannel(TChannel*);
	
		void CalibrateFragment(TTigFragment *frag);

		//SetChannel(
	private:
		bool fuseodbfile;
		bool fusecalfile;

		std::string fodbfilename;
		std::string fcalfilename;
		
		ClassDef(CalibrationManager,0);
};



#endif
