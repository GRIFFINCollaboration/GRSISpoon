
#ifndef TPARSER_H
#define TPARSER_H

#include <ctime>
#include <map>

#include <TObject.h>

class TParser : public TObject	{

	private:
		static TParser *fParser;
		TParser();
	
	public:
		~TParser();
		static TParser *instance();

	private:
		static const unsigned int fgMaxTriggerId;
		unsigned int fLastMidasId;
		unsigned int fLastTriggerId;
		std::map<int,int> fragment_id_map;


	public:
		int TigressDATAToFragment(int *data, int size,unsigned int midasserialnumber = 0, time_t midastime = 0);

		int GriffinDATAToFragment(int *data, int size,unsigned int midasserialnumber = 0, time_t midastime = 0);




	ClassDef(TParser,0);

};

#endif
