#ifndef TTIGOCILLOSCOPE_H
#define TTIGOCILLOSCOPE_H

#include <map>

#include "TTigOFrame.h"
#include "TTigFragment.h"

class TTigOcilloscope : public TObject	{

	public:
		TTigOcilloscope();
		~TTigOcilloscope();

		


	private:
		TTigOFrame *oframe;

		std::map<int,TTigFragment> fragbuffer;



	ClassDef(TTigOcilloscope,0)

};

#endif
