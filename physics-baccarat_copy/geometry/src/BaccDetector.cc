////////////////////////////////////////////////////////////////////////////////
/*	BaccDetector.cc

This is the code file to define the Bacc detector. This "detector" is just the 
detector part, it does not include the water shield or the rock.
********************************************************************************
Change log
  2013/09/18 - Initial submission (Vic)
*/
////////////////////////////////////////////////////////////////////////////////

//
//	GEANT4 includes
//
#include "G4LogicalVolume.hh"

//
//	Bacc includes
//
#include "BaccDetector.hh"
#include "BaccDetectorConstruction.hh"

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					BaccDetector()
//------++++++------++++++------++++++------++++++------++++++------++++++------
BaccDetector::BaccDetector()
{
	baccManager = BaccManager::GetManager();
	baccMaterials = BaccMaterials::GetMaterials();
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					~BaccDetector()
//------++++++------++++++------++++++------++++++------++++++------++++++------
BaccDetector::~BaccDetector() {}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					BuildDetector()
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccDetector::BuildDetector()
{
    G4cout << G4endl << G4endl;
    G4cout << "Something's dreadfully wrong here. It appears the programmer "
           << "hasn't created a" << G4endl;
    G4cout << "BuildDetector method within the " << detectorName
           << "class." << G4endl;
    G4cout << G4endl << G4endl;
    
    exit(0);
}
