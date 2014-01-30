

#include "S3Hit.h"

ClassImp(S3Hit)

S3Hit::S3Hit()	{
	Clear();
}

S3Hit::~S3Hit()	{	}

void S3Hit::Clear()	{

	position.SetXYZ(0,0,1);
	pixel		= std::make_pair(0,0);
	energy	=	0.0;
	charge	=	0;
	time		=	0.0;
	cfd			=	0.0;
	detectornumber	=	-1;

}


void S3Hit::Print()	{
	printf("================\n");
	printf("not yet written.\n");
	printf("================\n");
}
