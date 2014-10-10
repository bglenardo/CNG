////////////////////////////////////////////////////////////////////////////////
/*	BaccDetector.hh

This is the header file to define the Baccarat detector. This "detector" is just 
the detector part, it does not include the water shield or the rock.
********************************************************************************
Change log
  2013/09/18 - Initial submission (Vic)
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef BaccDetector_HH
#define BaccDetector_HH 1

//
//  Geant4 includes
//
#include "G4LogicalVolume.hh"

//
//	Bacc includes
//
#include "BaccManager.hh"
#include "BaccMaterials.hh"

//
//	Class forwarding
//
class BaccDetectorConstruction;

//------++++++------++++++------++++++------++++++------++++++------++++++------
class BaccDetector
{
	public:
        BaccDetector();
		~BaccDetector();
		
		inline G4LogicalVolume *GetLogicalVolume() { return logicalVolume; };
    
        virtual void BuildDetector();
    
        inline G4String GetName() { return detectorName; };
        inline G4String GetVolumeName() { return outermostVolumeName; };
		
	protected:
		G4LogicalVolume *logicalVolume;
		
		BaccManager *baccManager;
        BaccMaterials *baccMaterials;
		
        G4String detectorName;
        G4String outermostVolumeName;
    
    //  Below here is where all the public methods and private variables are
    //  set that are specific to an individual geometry
    public:
        void SetTPCMaterial( G4String mat ) { tpcMaterial = mat; };
    
    protected:
         G4String tpcMaterial;
    

};

#endif
