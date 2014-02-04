
#include "SharcHit.h"

ClassImp(SharcHit)

SharcHit::SharcHit()	{	
	Clear();
}

SharcHit::~SharcHit()	{	}


void SharcHit::Clear()	{
	position.SetXYZ(0,0,1);
	pixel = std::make_pair(0,0);
	delta_e		= 0.0;
	front_charge	=	0;	
	back_charge		=	0;
	delta_t		= 0.0;
	delta_cfd	= 0.0;
	energy		= 0.0;  //only the pad!!
	charge 		=	0;
	time	 		= 0.0;  //only the pad!!
	pad_cfd		= 0.0;  //only the pad!!
}

void SharcHit::Print()	{
			printf("Sharc hit energy: %f\n",energy);
			printf("Sharc hit time:   %f\n",time);
			printf("Sharc hit TV3 theta: %f\tphi%f\n",position.Theta() *180/(3.141597),position.Phi() *180/(3.141597));
}
