#ifndef TS3_H
#define TS3_H

#include <TNamed.h>

#include "TS3Data.h"
#include "S3Hit.h"


class TS3 : public TS3Data, public TNamed {

	public:
		TS3();
		~TS3();

	public: 
		void Clear();   
		void BuildHits();

		S3Hit *GetS3Hit(int i)		{	return &s3_hits[i];};	
		Short_t GetMultiplicity()	{	return s3_hits.size();};


		TVector3 GetPosition(int front, int back);


	//private: 

		std::vector<S3Hit> s3_hits;
		
		static int ring_number;
		static int sector_number;

		static double offset_phi;
		static double outer_diameter;
		static double inner_diameter;
		static double target_distance;

		

	ClassDef(TS3,1)

};

#endif
