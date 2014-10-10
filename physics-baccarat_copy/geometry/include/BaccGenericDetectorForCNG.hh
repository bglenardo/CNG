////////////////////////////////////////////////////////////////////////////////
/* BaccGenericDetectorForCNG.hh

This header file is copied from the BaccExampleNobleTPC header file, and then
is customized to serve as the generic detector for studies of a compact neutron
generator.  
Within this default is the option to set the material to either argon or xenon,
with xenon being the default. The material can be changed via a messenger
command.
********************************************************************************
Change log
  2014/10/06 - Created as a copy of BaccExampleNobleTPC, names changed
               appropriately. (Brian)
  2014/10/09 - Added water tank variables. (Brian)

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef BaccGenericDetectorForCNG_HH
#define BaccGenericDetectorForCNG_HH 1

//
//	GEANT4 includes
//
#include "globals.hh"

//
//	Bacc includes
//
#include "BaccDetector.hh"

//
//	Class forwarding
//
class G4LogicalVolume;
class BaccDetectorComponent;

//------++++++------++++++------++++++------++++++------++++++------++++++------
class BaccGenericDetectorForCNG : public BaccDetector
{
	public:
		BaccGenericDetectorForCNG( G4String, G4String );
		~BaccGenericDetectorForCNG();
        void BuildDetector();
        
	private:
        //  These variables have to be defined at the class level rather than
        //  the method or function level because they may be needed by multiple
        //  methods or functions.
        G4double pmtHeight;
        G4double pmtRadius;
    
        G4double spaceBelowBottomPMTs;
        G4double reverseFieldHeight;
        G4double activeTargetHeight;
        G4double gainVolumeHeight;
        G4double spaceAboveTopPMTs;
        G4double totalCentralVolumeHalfHeight;
        G4double totalCentralVolumeRadius;
    
        G4double reflectorThickness;
        G4double reflectorHalfHeight;
        G4double reflectorOuterRadius;
    
        G4double cryostatWallThickness;
        G4double cryostatHalfHeight;
        G4double cryostatOuterRadius;
    
        G4double vacuumSpaceThickness;
        G4double vacuumHalfHeight;
        G4double vacuumOuterRadius;
    
        G4double vacuumVesselThickness;
        G4double vacuumVesselOuterRadius;
        G4double vacuumVesselHalfHeight;
        
        G4double waterVolumeHalfHeight;
        G4double waterVolumeRadius;
        G4double waterTankThickness;
        G4double waterTankHalfHeight;
        G4double waterTankRadius;

};

#endif
