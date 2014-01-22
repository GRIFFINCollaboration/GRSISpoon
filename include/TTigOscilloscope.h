#ifndef TTIGOSCILLOSCOPE_H
#define TTIGOSCILLOSCOPE_H

#include <map>

#include "TTigOFrame.h"
#include "TTigFragment.h"

class TTigOscilloscope : public TObject	{

	public:
		TTigOscilloscope();
		~TTigOscilloscope();

		


	private:
		TTigOFrame *oframe;

		std::map<int,TTigFragment> fragbuffer;



	ClassDef(TTigOscilloscope,0)

};

#endif
