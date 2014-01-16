/*****************************************************************************
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *
 * Modified by    : Mhd Moukaddam  contact address: moukaddam@triumf.ca      *
 *---------------------------------------------------------------------------*
 * Decription: This class stores the results of the G4 simulation for the    *
 *             SiLi detector. And was adapted from S1 detector Class.         *
 *             The format is the same as the one which is used for the GANIL *
 *             experiments after conversion of the raw data with GRU. Ask    *
 *             N. de Sereville and J. Burgunder (burgunder@ganil.fr) for     *
 *             informations.                                                 *
 *             This class derives from TObject (ROOT) and its aim is to be   *
 *             stored in the output TTree of the G4 simulation               *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *                                                                           *
 *****************************************************************************/

#include <iostream>
using namespace std;

#include "TSiLiData.h"


ClassImp(TSiLiData)

TSiLiData::TSiLiData()
{
   // Default constructor
   Clear();
}

TSiLiData::~TSiLiData() {}


void TSiLiData::Clear()
{

	fSiLiSegment.clear();
	fSiLiCharge.clear();
	fSiLiEnergy.clear();
	fSiLiCFD.clear(); 
	fSiLiLED.clear();
	fSiLiTIME.clear();
}



void TSiLiData::Print()
{
	printf("=======================\n");
	printf("not yet written\n");
	printf("=======================\n");
   
}
