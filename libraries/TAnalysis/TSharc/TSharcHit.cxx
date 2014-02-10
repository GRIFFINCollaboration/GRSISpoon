
#include "TSharcHit.h"

ClassImp(TSharcHit)

TSharcHit::TSharcHit()	{	
	Clear();
}

TSharcHit::~TSharcHit()	{	}


void TSharcHit::Clear(Option_t *options)	{

	front_strip		=	0;	//
	front_charge	=	0;	//  
	back_strip		=	0;	//
	back_charge		=	0;	//

	pad_charge		=	0;	//

	d_energy		=	0;	//      
	d_time			=	0;	//      
	d_cfd			=	0;	//      

	p_energy		=	0;	//          pad only;
	p_time			=	0;	//          pad only;
	p_cfd			=	0;	//

	detectornumber	=	0;	//

}

void TSharcHit::Print(Option_t *options)	{
			//printf("Sharc hit energy: %f\n",d_energy);
			//printf("Sharc hit time:   %f\n",d_time);
}
