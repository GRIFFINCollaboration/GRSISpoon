
#include "SiLiHit.h"

ClassImp(SiLiHit)

SiLiHit::SiLiHit()	{	}

SiLiHit::~SiLiHit()	{	}


void SiLiHit::Clear()	{

	energy	= -1.0;
	charge	=	0;
	time		=	-1.0;
	cfd			=	-1.0;

	segment	=	-1.0;
}

void SiLiHit::Print()	{
	printf("===============\n");
	printf("not yet written\n");
	printf("===============\n");
}

