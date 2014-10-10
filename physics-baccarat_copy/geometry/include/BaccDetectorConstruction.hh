////////////////////////////////////////////////////////////////////////////////
/*	BaccDetectorConstruction.hh

This is the header file to build the detector geometry within Bacc.
********************************************************************************
Change log
  2013/09/26 - Initial submission (Vic)
*/
////////////////////////////////////////////////////////////////////////////////


#ifndef BaccDetectorConstruction_HH
#define BaccDetectorConstruction_HH 1

//
//	GEANT4 includes
//
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "BaccGeometryMessenger.hh"

//
// C/C++ includes
//
#include <vector>

//
//	Class forwarding
//

class BaccManager;
class BaccDetectorComponent;
class BaccMaterials;

class BaccDetector;
class BaccExampleSimpleCryostat;
class BaccExampleComplexCryostat;
//class BaccGeometryMessenger;

//------++++++------++++++------++++++------++++++------++++++------++++++------
class BaccDetectorConstruction : public G4VUserDetectorConstruction
{
	public:

		BaccDetectorConstruction();
		~BaccDetectorConstruction();

        static BaccDetectorConstruction *GetDetectorConstruction();

		G4VPhysicalVolume *Construct();
		void UpdateGeometry();
		
		BaccDetectorComponent	*GetWorldVolume()	{ return experimentalHall;};
		BaccDetector 			*GetDetectorType()	{ return detectorType; };
		BaccDetectorComponent	*GetDetector()		{ return detector; };
		
		//	Materials methods
		void SetLXeTeflonRefl( G4double r );
		void SetLXeSteelRefl( G4double r );
		void SetLXeAbs( G4double l );
		void SetLXeRayleigh( G4double l );
		void SetGXeTeflonRefl( G4double r );
		void SetGXeSteelRefl( G4double r );
		void SetGXeAbs( G4double l );
		void SetGXeRayleigh( G4double l );
		void SetAlUnoxQuartzRefl( G4double r );
		
		//	Geometry methods
        void SetDetectorSelection( G4String det ) { detectorSelection = det; };
		void SetDetectorZ( G4double z );
		bool DetectorSpecified() { return detectorSpecified; };

	private:
        static BaccDetectorConstruction *baccDetectorConstruction;
        BaccGeometryMessenger *baccGeometryMessenger;
    
		//	Detector components
		//	Just the experimentalHall should be a G4VPhysicalVolume. The rest
		//	should be BaccDetectorComponents.
		BaccDetectorComponent *experimentalHall;
        BaccDetectorComponent *subVol;
		BaccDetector *detectorType;
		BaccDetectorComponent *detector;
        G4String detectorSelection;

		//	Support for internal workings
		BaccManager *baccManager;
		BaccMaterials *materials;
		G4VPhysicalVolume *ConstructDetector();
		std::vector<BaccDetector*> detectorList;
		
		//	Detector position (default: 0 cm)
		G4double detX, detY, detZ;

		bool detectorSpecified;		
};

#endif

