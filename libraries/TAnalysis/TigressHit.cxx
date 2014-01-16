
#include "TigressHit.h"

ClassImp(TigressHit)

TigressHit::TigressHit()	{	
	Clear();
}

TigressHit::~TigressHit()	{	}


void TigressHit::Clear()	{
	position.SetXYZ(0,0,1);
	energy = 0.0;
	time	 = 0.0;
}


void TigressHit::Print()	{
	printf("Tigress hit energy: %f\n",energy);
	printf("Tigress hit time:   %f\n",time);
	printf("Tigress hit TV3 theta: %f\tphi%f\n",position.Theta() *180/(3.141597),position.Phi() *180/(3.141597));
}
