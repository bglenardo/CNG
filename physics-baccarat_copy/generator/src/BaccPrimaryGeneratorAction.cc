////////////////////////////////////////////////////////////////////////////////
/*	BaccPrimaryGeneratorAction.cc

This is the code file to control the GEANT4 side of event generation.
********************************************************************************
Change log
  2013/11/20 - Initial submission (Vic)
*/
////////////////////////////////////////////////////////////////////////////////

//
//	GEANT4 includes
//
#include "globals.hh"
#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"

//
//	Bacc includes
//
#include "BaccPrimaryGeneratorAction.hh"
#include "BaccManager.hh"

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					BaccPrimaryGeneratorAction()
//------++++++------++++++------++++++------++++++------++++++------++++++------
BaccPrimaryGeneratorAction::BaccPrimaryGeneratorAction()
{
	baccManager = BaccManager::GetManager();
	baccManager->Register( this );
	particleGun = new G4GeneralParticleSource();
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					~BaccPrimaryGeneratorAction()
//------++++++------++++++------++++++------++++++------++++++------++++++------
BaccPrimaryGeneratorAction::~BaccPrimaryGeneratorAction()
{
	delete particleGun;
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					GeneratePrimaries()
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccPrimaryGeneratorAction::GeneratePrimaries( G4Event *event )
{
	//	Have the management class determine which event is next and generate
	//	that event
	if( baccManager->GetTotalSimulationActivity() )
		baccManager->GenerateEvent( particleGun, event );
	else {
	    //BaccManager::primaryParticleInfo particle = GetParticleInfo(particleGun);
        particleGun->GeneratePrimaryVertex( event );
        baccManager->AddPrimaryParticle( GetParticleInfo(particleGun) );
    }
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//                  GetParticleInfo()
//------++++++------++++++------++++++------++++++------++++++------++++++------
BaccManager::primaryParticleInfo BaccPrimaryGeneratorAction::GetParticleInfo(
        G4GeneralParticleSource *particleGun )
{
    BaccManager::primaryParticleInfo particle;
    particle.id = particleGun->GetParticleDefinition()->GetParticleName();
    particle.energy = particleGun->GetCurrentSource()->GetParticleEnergy();
    particle.time = particleGun->GetCurrentSource()->GetParticleTime();
    particle.position = particleGun->GetCurrentSource()->GetParticlePosition();
    particle.direction = particleGun->GetCurrentSource()->
                            GetParticleMomentumDirection();
    return particle;
}
