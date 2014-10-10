////////////////////////////////////////////////////////////////////////////////
/*	BaccGeneratorSingleParticle.cc

This is the code file for the SingleParticle generator.
********************************************************************************
Change log
  2013/11/20 - Initial submission (Vic)
*/
////////////////////////////////////////////////////////////////////////////////

//
//  C/C++ includes
//
#include <sstream>

//
//	GEANT4 includes
//
#include "globals.hh"
#include "G4ParticleTable.hh"
#include "G4Geantino.hh"

//
//	Bacc includes
//
#include "BaccGeneratorSingleParticle.hh"

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					BaccGeneratorSingleParticle()
//------++++++------++++++------++++++------++++++------++++++------++++++------
BaccGeneratorSingleParticle::BaccGeneratorSingleParticle()
{
	name = "SingleParticle";
	activityMultiplier = 1;
    energy = 0*keV;
    particlename = G4Geantino::Definition();
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					~BaccGeneratorSingleParticle()
//------++++++------++++++------++++++------++++++------++++++------++++++------
BaccGeneratorSingleParticle::~BaccGeneratorSingleParticle() {;}


//------++++++------++++++------++++++------++++++------++++++------++++++------
//					GenerateEventList()
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccGeneratorSingleParticle::GenerateEventList( G4ThreeVector position,
                G4int sourceByVolumeID, G4int sourcesID, G4String pname, 
                G4double energy, G4double time)
{

    G4int z=-1; G4int a=-1;
  	Isotope *currentIso = new Isotope(name, z, a, pname, energy);
  	baccManager->RecordTreeInsert( currentIso, time, position, 
                  sourceByVolumeID, sourcesID );	
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					GenerateFromEventList()
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccGeneratorSingleParticle::GenerateFromEventList( 
    G4GeneralParticleSource *particleGun, G4Event *event, decayNode *firstNode )
{

    G4String particlestring = firstNode->particleName; //name=SingleParticle
    G4ParticleTable *pTable = G4ParticleTable::GetParticleTable();
    particlename = pTable->FindParticle( particlestring ) ;
    if(particlename){
        particleGun->GetCurrentSource()->SetParticleDefinition( particlename );
    }

    G4double time = (firstNode->timeOfEvent)/ns;//time in ns
    particleGun->GetCurrentSource()->SetParticleTime( time*ns );

    G4ThreeVector pos = G4ThreeVector(firstNode->pos );
    particleGun->GetCurrentSource()->GetPosDist()->SetCentreCoords(pos);

  	particleGun->GetCurrentSource()->GetAngDist()->SetParticleMomentumDirection(
			GetRandomDirection() );

    G4double energy = firstNode->energy;
	particleGun->GetCurrentSource()->GetEneDist()->SetMonoEnergy( energy );

   	particleGun->GeneratePrimaryVertex( event );
    baccManager->AddPrimaryParticle( GetParticleInfo(particleGun) ) ;

}

