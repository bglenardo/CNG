////////////////////////////////////////////////////////////////////////////////
/*	BaccSteppingAction.cc

This is the code file to control the simulation step-by-step.
********************************************************************************
Change log
  2013/11/20 - Initial submission (Vic)
  2014/01/03 - Code cleanup (Vic)
  2014/09/08 - Fixed bug in the timing of decay particles from 
               radioisotopes (Brian)
  2014/09/09 - Added include fo G4SystemOfUnits.hh for geant4.10 compatibility
               (Brian)
*/
////////////////////////////////////////////////////////////////////////////////

//
//	GEANT4 includes
//
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "G4SystemOfUnits.hh"

//
//	Bacc includes
//
#include "BaccSteppingAction.hh"
#include "BaccManager.hh"
#include "BaccDetectorComponent.hh"
#include "BaccMaterials.hh"
#include "BaccEventAction.hh"

//
//	Definitions
//
#define DEBUGGING 0

//------++++++------++++++------++++++------++++++------++++++------++++++------
//				BaccSteppingAction()
//------++++++------++++++------++++++------++++++------++++++------++++++------
BaccSteppingAction::BaccSteppingAction()
{
	baccManager = BaccManager::GetManager();
	baccManager->Register( this );
	
	BaccMaterials *baccMaterials = BaccMaterials::GetMaterials();
	blackiumMat = baccMaterials->Blackium();

	optPhotRecordLevel = 0;
	thermElecRecordLevel = 0;
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//				~BaccSteppingAction()
//------++++++------++++++------++++++------++++++------++++++------++++++------
BaccSteppingAction::~BaccSteppingAction() {}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//				UserSteppingAction()
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccSteppingAction::UserSteppingAction( const G4Step* theStep )
{
	//	Initialize step specifics
	theTrack = theStep->GetTrack();
	trackPosition = theStep->GetPostStepPoint()->GetPosition();
	particleDirection = theStep->GetPreStepPoint()->GetMomentumDirection();
	recordLevel = baccManager->GetComponentRecordLevel(
			(BaccDetectorComponent*)theTrack->GetVolume() );
	optPhotRecordLevel = baccManager->GetComponentRecordLevelOptPhot(
			(BaccDetectorComponent*)theTrack->GetVolume() );
	thermElecRecordLevel = baccManager->GetComponentRecordLevelThermElec(
                        (BaccDetectorComponent*)theTrack->GetVolume() );
	
	//	Record relevant parameters in the step record
	aStepRecord.stepNumber = theTrack->GetCurrentStepNumber();
	aStepRecord.particleID = theTrack->GetDefinition()->GetPDGEncoding();
	aStepRecord.particleName = theTrack->GetDefinition()->GetParticleName();
	if( theTrack->GetCreatorProcess() )
		aStepRecord.creatorProcess =
				theTrack->GetCreatorProcess()->GetProcessName();
	else 
		aStepRecord.creatorProcess = "primary";
	aStepRecord.trackID = theTrack->GetTrackID();
	aStepRecord.parentID = theTrack->GetParentID();
	aStepRecord.particleEnergy =
			theStep->GetPreStepPoint()->GetKineticEnergy()/keV;
	aStepRecord.particleDirection[0] = particleDirection.x();
	aStepRecord.particleDirection[1] = particleDirection.y();
	aStepRecord.particleDirection[2] = particleDirection.z();
	aStepRecord.energyDeposition = theStep->GetTotalEnergyDeposit()/keV;
	aStepRecord.position[0] = trackPosition.x()/cm;
	aStepRecord.position[1] = trackPosition.y()/cm;
	aStepRecord.position[2] = trackPosition.z()/cm;
	
	//	Record whether or not the primary particle is a radioactive ion
	if( (aStepRecord.parentID==0) && (aStepRecord.stepNumber==1) &&
			!theTrack->GetDefinition()->GetPDGStable() &&
			(aStepRecord.particleName.find("[") < G4String::npos) )
		baccManager->GetEvent()->SetRadioactivePrimaryTime(
				baccManager->GetPrimaryParticles()[0].time );
	
	//	Check to see if the particle is an immediate daughter of a primary
	//	radioactive nucleus, and if so, wipe out the global time. This has the
	//	effect of having the primary particle decaying at global time = 0.
	if( (aStepRecord.parentID==1) && (aStepRecord.stepNumber==1) &&
			baccManager->GetEvent()->GetRadioactivePrimaryTime() )
		theTrack->SetGlobalTime(
				baccManager->GetEvent()->GetRadioactivePrimaryTime() );
	
	aStepRecord.stepTime = theTrack->GetGlobalTime()/ns;
	
	//	Handle the case of optical photon record keeping
	if( aStepRecord.particleName == "opticalphoton" ) {
	
		aStepRecord.energyDeposition = 0;
	
		if( optPhotRecordLevel )
			baccManager->AddDeposition(
					(BaccDetectorComponent*)theTrack->GetVolume(),
					aStepRecord );
		
		if( optPhotRecordLevel == 1 || optPhotRecordLevel == 3 )
			theTrack->SetTrackStatus( fStopAndKill );

	} else if ( aStepRecord.particleName == "thermalelectron" ){

                aStepRecord.energyDeposition = 0;

                if( thermElecRecordLevel )
                        baccManager->AddDeposition(
                                        (BaccDetectorComponent*)theTrack->GetVolume(),
                                        aStepRecord );

                if( thermElecRecordLevel == 1 || thermElecRecordLevel == 3 )
                        theTrack->SetTrackStatus( fStopAndKill );

	} else
		baccManager->AddDeposition(
				(BaccDetectorComponent*)theTrack->GetVolume(),
				aStepRecord );
	
	//	Kill the particle if the current volume is made of blackium, or if the
	//	record level is set to 4. The blackium support is kept for historical
	//	reasons. Note that the particle is killed only after the first step is
	//	recorded, so that we at least know what went into the volume and where.
	if( (theTrack->GetMaterial() == blackiumMat) || (recordLevel == 4) )
		theTrack->SetTrackStatus( fStopAndKill );
	
	//	Put debugging code here
	if( DEBUGGING ) {
		G4cout << "\tTracking a " << aStepRecord.particleEnergy << "-keV "
			   << aStepRecord.particleName << " in "
			   << theTrack->GetVolume()->GetName() << " at ( "
			   << aStepRecord.position[0] << ", " << aStepRecord.position[1]
			   << ", " << aStepRecord.position[2] << " )" << G4endl;
		if( aStepRecord.particleName == "gamma" ||
				aStepRecord.particleName == "alpha" ||
				aStepRecord.particleName == "e-" ||
				aStepRecord.particleName == "anti_nu_e" ||
				aStepRecord.particleName == "neutron"
				)
			theTrack->SetTrackStatus( fStopAndKill );
	}
}
