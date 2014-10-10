////////////////////////////////////////////////////////////////////////////////
/* BaccGeometryCatalog.hh

This is the code file to handle the various detector geometries. This catalog 
object is essentially a sub-manager for the detector geometries.
********************************************************************************
Change log
  2013/09/11 - Initial submission (Vic)
*/
////////////////////////////////////////////////////////////////////////////////

//
//	GEANT4 includes
//
#include "globals.hh"

//
//	Bacc includes
//
#include "BaccGeometryCatalog.hh"
#include "BaccManager.hh"

#include "Bacc7081PMT.hh"
#include "BaccDetectorConstruction.hh"
#include "BaccExampleComplexDetector.hh"
#include "BaccDetector.hh"
#include "BaccExamplePMTBank.hh"
#include "BaccGeometryCatalog.hh"
#include "BaccMaterials.hh"
#include "BaccDetectorComponent.hh"
#include "BaccExample8778PMT.hh"
#include "BaccExampleSimpleDetector.hh"

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					BaccGeometryCatalog()
//------++++++------++++++------++++++------++++++------++++++------++++++------
BaccGeometryCatalog *BaccGeometryCatalog::baccGeometryCatalog = 0;
BaccGeometryCatalog::BaccGeometryCatalog(){
	baccGeometryCatalog = this;
	
	baccManager = BaccManager::GetManager();
	baccManager->Register( baccGeometryCatalog );
	
	geometry.clear();
	
//	geometry.push_back( new BaccExampleSimpleDetector );
//	geometry.push_back( new BaccExampleComplexDetector );
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					GetCatalog()
//------++++++------++++++------++++++------++++++------++++++------++++++------
BaccGeometryCatalog *BaccGeometryCatalog::GetCatalog()
{
	return baccGeometryCatalog;
}


//------++++++------++++++------++++++------++++++------++++++------++++++------
//					~BaccGeometryCatalog()
//------++++++------++++++------++++++------++++++------++++++------++++++------
BaccGeometryCatalog::~BaccGeometryCatalog()
{
	geometry.clear();
}
