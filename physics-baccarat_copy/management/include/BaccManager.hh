////////////////////////////////////////////////////////////////////////////////
/*	BaccManager.hh
This is the header file to manage all the workings of Baccarat. This class is a 
clearing house for all internal controls, from geometry to output to event 
generation. All classes can and should  have access to this manager class, and 
there should only be one instance of this class in the entire simulation.
********************************************************************************
Change log
  2013/09/26 - Initial submission (Vic)
  2014/01/22 - Removed a few vestigial variables (Vic)
  2014/09/08 - Added two boolean variables and associated functions to test
               whether the code is stored using svn or git.
  2014/09/08 - Spun off the SetUseOpticalProcesses method to the code file
               (Brian)
  2014/10/05 - Added flag for checking overlaps for all volumes (automatic
               checking off by default) (Brian)
  2014/10/09 - Added methods GetDetectorSelection and SetDetectorSelection as
               geometry methods. (Brian)

*/
////////////////////////////////////////////////////////////////////////////////

#ifndef BaccManager_HH
#define BaccManager_HH 1

//
//	C/C++ includes
//
#include <vector>
#include <queue>

//
//	GEANT4 includes
//
#include "G4ThreeVector.hh"
#include "globals.hh"

//
//	CLHEP includes
//
#include "CLHEP/Random/MTwistEngine.h"

//
//	Bacc includes
//
#include "BaccMaterials.hh"
#include "BaccBST.hh"
//#include "BaccIsotope.hh"

//
//	Class forwarding
//
class G4UImanager;
class G4GeneralParticleSource;
class G4Event;

class BaccPhysicsList;
class BaccPhysicsOpticalPhysics;
class BaccDetectorConstruction;
class BaccDetectorComponent;
class BaccGeometryCatalog;
class BaccPrimaryGeneratorAction;
class BaccRunAction;
class BaccEventAction;
class BaccSteppingAction;
class BaccOutput;
class BaccMessenger;
class BaccSourceCatalog;

//------++++++------++++++------++++++------++++++------++++++------++++++------
class BaccManager
{
	public:
		BaccManager();
		~BaccManager();

		//	General methods
		static BaccManager *GetManager();
		
		//	Overloaded registration methods
		void Register( BaccPhysicsList* phys ) { BaccPhysics = phys; };
		void Register( BaccPhysicsOpticalPhysics *optPhys )
				{ BaccPhysicsOptical = optPhys; }
		void Register( BaccDetectorConstruction *con )
				{ BaccDetector = con; };
		void Register( BaccMaterials *mat ) { BaccMat = mat; };
		void Register( BaccPrimaryGeneratorAction *gen )
				{ BaccGenerator = gen; };
		void Register( BaccRunAction *run ) { BaccRun = run; };
		void Register( BaccEventAction *evt ) { BaccEvent = evt; };
		void Register( BaccSteppingAction *step ) { BaccStep = step; };
		void Register( BaccOutput *out ) { BaccOut = out; };
		void Register( BaccSourceCatalog *cat ) { BaccSourceCat = cat; };
		void Register( BaccGeometryCatalog *geom ) { BaccGeometryCat = geom; };
		
		BaccPhysicsList *GetPhysicsList() { return BaccPhysics; };
		BaccDetectorConstruction *GetDetectorConstruction() {
				return BaccDetector; };
		BaccPrimaryGeneratorAction *GetGenerator() {
				return BaccGenerator; };
		BaccRunAction *GetRun() { return BaccRun; };
		BaccEventAction *GetEvent() { return BaccEvent; };
		BaccSteppingAction *GetStep() { return BaccStep; };
		BaccOutput *GetOutput() { return BaccOut; };
		BaccSourceCatalog *GetSourceCatalog() { return BaccSourceCat; };
		BaccGeometryCatalog *GetGeometryCatalog() { return BaccGeometryCat; };
		
		//	General-purpose methods
		void BeamOn( G4int );
		inline G4int GetRandomSeed() { return randomSeed; };
		void SetRandomSeed( G4int );
		
		//	Input/output methods
                void SetIsSVNRepo( G4bool isSVN ) { IsSVNRepo = isSVN; }
                G4bool GetIsSVNRepo() { return IsSVNRepo; }
                void SetIsGitRepo( G4bool isGit ) { IsGitRepo = isGit; }
		G4bool GetIsGitRepo () { return IsGitRepo; }
		void SetCompilationDirectory( G4String dir ) { compilationDir = dir; };
		G4String GetCompilationDirectory() { return compilationDir; };
		void SetOutputDir( G4String );
		G4String GetOutputDir() { return outputDir; };
		void SetOutputName( G4String name ) { outputName = name; };
		G4String GetOutputName() { return outputName; };
		G4String GetHistoryFile() { return historyFile; };
		G4String GetInputCommands() { return listOfCommands; };
		G4String GetDiffs() { return listOfDiffs; };
		
		void SetRunEndedCleanly( G4bool val ) { runEndedCleanly = val; };
		G4bool GetRunEndedCleanly() { return runEndedCleanly; };
		G4int GetNumEvents() { return numEvents; };
		
		void SetAlwaysRecordPrimary( G4bool val ) { alwaysRecordPrimary = val;};
		G4bool GetAlwaysRecordPrimary() { return alwaysRecordPrimary; };

        void SetEventProgressFrequency( G4int val ) { eventProgressFrequency = val;};
        G4int GetEventProgressFreqnecy() { return eventProgressFrequency; };

        // User defined variables methods
        void SetUserVar1( G4double var ) { userVar1 = var;};
        void SetUserVar2( G4double var ) { userVar2 = var;};
        void SetUserVar3( G4double var ) { userVar3 = var;};
        void SetUserVar4( G4double var ) { userVar4 = var;};
        void SetUserVar5( G4double var ) { userVar5 = var;};
        G4double GetUserVar1() { return userVar1;};
        G4double GetUserVar2() { return userVar2;};
        G4double GetUserVar3() { return userVar3;};
        G4double GetUserVar4() { return userVar4;};
        G4double GetUserVar5() { return userVar5;};

		//	Geometry methods
		void UpdateGeometry();
		
		void Register( BaccDetectorComponent *com )
				{ BaccComponents.push_back( com ); };
		void Deregister( BaccDetectorComponent* );
		
		G4String GetDetectorComponentLookupTable();

		G4bool CapturePhotons( BaccDetectorComponent* );

		void SetRecordLevel( G4String );
		std::vector<G4int> GetRecordLevels( G4String );
		G4int GetComponentRecordLevel( BaccDetectorComponent* );
		
		void SetRecordLevelOptPhot( G4String );
		std::vector<G4int> GetRecordLevelsOptPhot( G4String );
		G4int GetComponentRecordLevelOptPhot( BaccDetectorComponent* );
		
		void SetRecordLevelThermElec( G4String );
		std::vector<G4int> GetRecordLevelsThermElec( G4String );
		G4int GetComponentRecordLevelThermElec( BaccDetectorComponent* );
	
                void SetCheckVolumeOverlaps( G4bool val ) {
                       checkVolumeOverlaps = val; }
                G4bool GetCheckVolumeOverlaps() { return checkVolumeOverlaps; };

	
		BaccDetectorComponent *GetComponentByName( G4String );
                void     SetDetectorSelection( G4String sel ) { detectorSelection = sel; }
                G4String GetDetectorSelection() { return detectorSelection; };

			
         //	Source methods
        void SetSource( G4String );
        void SetPrintEventList( G4bool sel ) { printEventList = sel; };
        void ResetSources();
        void BuildEventList();
        void TrimEventList();
        void PrintEventList() { recordTree->PrintNodes(); };
        void GenerateEvent( G4GeneralParticleSource*, G4Event* );
        void GenerateEventList();
      	G4double GetTotalSimulationActivity() { return totalSimulationActivity;};
        G4bool GetBaccSources() { return hasBaccSources;};
        void RecordTreeInsert(Isotope*, G4double, G4ThreeVector, G4int, G4int);
        G4double GetWindowEndTime() {return windowEnd;};

        G4double GetGammaXFiducialR() {return gammaXFiducialR;}
        G4double GetGammaXFiducialLoZ() {return gammaXFiducialLoZ;}
        G4double GetGammaXFiducialHiZ() {return gammaXFiducialHiZ;}
        G4double GetGammaXReverseFieldR() {return gammaXReverseFieldR;}
        G4double GetGammaXReverseFieldLoZ() {return gammaXReverseFieldLoZ;}
        G4double GetGammaXReverseFieldHiZ() {return gammaXReverseFieldHiZ;}
        G4double GetGammaXMaxEnergy() {return gammaXMaxEnergy;}
        void LoadEventsFile(G4String);
        G4int NextEventToGenerate();
        G4int NextParticleIDToGenerate();
        G4double NextEnergyDepToGenerate();
        G4ThreeVector NextPositionToGenerate();




		//	Data methods

		//	Simulation data methods and variables
		struct stepRecord {
			G4int stepNumber;
			G4int particleID;
			G4String particleName;
			G4String creatorProcess;
			G4int trackID;
			G4int parentID;
			G4double particleEnergy;
			G4double particleDirection[3];
			G4double energyDeposition;
			G4double position[3];
			G4double stepTime;
		};
		void AddDeposition( BaccDetectorComponent*, stepRecord );
		G4bool KillPhoton( BaccDetectorComponent* );
		void RecordValues( G4int );
		void RecordValuesOptPhot( G4int );
		void RecordValuesThermElec( G4int );
		void ClearRecords();
		
		//	Primary particle information
		struct primaryParticleInfo {
			G4String id;
			G4double energy;
			G4double time;
			G4ThreeVector position;
			G4ThreeVector direction;
		};
		void AddPrimaryParticle( primaryParticleInfo particle )
				{ primaryParticles.push_back( particle );}; 
		std::vector<primaryParticleInfo> GetPrimaryParticles()
				{ return primaryParticles; };

		//	Physics list methods
		inline G4bool GetUseOpticalProcesses() { return useOpticalProcesses; };
        void SetUseOpticalProcesses( G4bool ); 
        inline void SetS1Gain( G4double val ) { s1gain = val; };
        inline G4double GetS1Gain() { return s1gain; };
        inline void SetS2Gain( G4double val ) { s2gain = val; };
        inline G4double GetS2Gain() { return s2gain; };
		
		inline void SetDriftElecAttenuation( G4double val )
				{ driftElecAttenuation = val; };
		inline G4double GetDriftElecAttenuation()
				{ return driftElecAttenuation; };
		
		inline G4bool GetOpticalDebugging()
				{ return BaccMat->GetOpticalDebugging(); };
		void SetOpticalDebugging( G4bool debug )
				{ BaccMat->SetOpticalDebugging(debug); };
		

	private:
		static BaccManager *baccManager;
		BaccMessenger *baccMessenger;
		
		BaccPhysicsList *BaccPhysics;
		BaccPhysicsOpticalPhysics *BaccPhysicsOptical;
		BaccDetectorConstruction *BaccDetector;
		BaccMaterials *BaccMat;
		BaccPrimaryGeneratorAction *BaccGenerator;
		BaccRunAction *BaccRun;
		BaccEventAction *BaccEvent;
		BaccSteppingAction *BaccStep;
		BaccOutput *BaccOut;
		BaccSourceCatalog *BaccSourceCat;
		BaccGeometryCatalog *BaccGeometryCat;
	
		G4UImanager *UI;
		
		CLHEP::MTwistEngine randomizationEngine;
		G4int randomSeed;
		
		//	Input/output variables
		G4bool   IsSVNRepo;
		G4bool   IsGitRepo;
		G4String compilationDir;
		G4String outputDir;
		G4String outputName;
		G4String historyFile;
		G4String listOfCommands;
		G4String listOfDiffs;
		G4bool runEndedCleanly;
		G4int numEvents;
		G4bool alwaysRecordPrimary;
		G4int eventProgressFrequency;

        // User defined variables
        G4double userVar1;
        G4double userVar2;
        G4double userVar3;
        G4double userVar4;
        G4double userVar5;
		
		//	Geometry variables
		std::vector<BaccDetectorComponent*> BaccComponents;
                G4bool checkVolumeOverlaps;       
                G4String detectorSelection;
 
		//	Source variables
        struct volumeSource {
          BaccDetectorComponent *component;
          G4double totalVolumeActivity;
          G4double totalVolumeActivityRatio;
        };
        std::vector<volumeSource> sourceByVolume;
        G4double totalSimulationActivity;
        G4double windowStart, windowEnd;
        G4bool hasBaccSources, isEventListBuilt;
        G4bool hasDecayChainSources, printEventList;
        BaccBST* recordTree;
	
        G4double gammaXFiducialR;
        G4double gammaXFiducialLoZ;
        G4double gammaXFiducialHiZ;
        G4double gammaXReverseFieldR;
        G4double gammaXReverseFieldLoZ;
        G4double gammaXReverseFieldHiZ;
        G4double gammaXMaxEnergy;
	        
		std::vector<primaryParticleInfo> primaryParticles;
		
		//	Physics list variables
		G4bool useOpticalProcesses;
		G4bool opticalDebugging;
        G4double s1gain;
        G4double s2gain;
		G4double driftElecAttenuation;

        // for evnets file generator
        std::queue<G4int> qEvtN;
        std::queue<G4int> qParticleID;
        std::queue<G4double> qEnergyDep_keV;
        std::queue<G4double> qPositionX_cm;
        std::queue<G4double> qPositionY_cm;
        std::queue<G4double> qPositionZ_cm;
        G4int currentEvtN;
        std::queue<G4int> currentParticleID;
        std::queue<G4double> currentEnergyDep_keV;
        std::queue<G4double> currentX_cm;
        std::queue<G4double> currentY_cm;
        std::queue<G4double> currentZ_cm;




};

#endif
