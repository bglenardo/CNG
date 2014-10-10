////////////////////////////////////////////////////////////////////////////////
/*	BaccSourceCatalog.hh

This is the code file to handle the various event generators. This catalog 
object is essentially a sub-manager for the source generators.
********************************************************************************
Change log
  2013/11/20 - Initial submission (Vic)
  2014/09/09 - YBe generator added, from LUXSim (Brian)

*/
////////////////////////////////////////////////////////////////////////////////

//
//	GEANT4 includes
//
#include "globals.hh"

//
//	Bacc includes
//
#include "BaccSourceCatalog.hh"
#include "BaccManager.hh"

#include "BaccSource.hh"
#include "BaccGeneratorAmBe.hh"
#include "BaccGeneratorCfFission.hh"
#include "BaccGeneratorMASN.hh"
#include "BaccGeneratorTh232.hh"
#include "BaccGeneratorDecayChain.hh" 
#include "BaccGeneratorU238.hh"
#include "BaccGeneratorRa226.hh"
#include "BaccGeneratorRn222.hh"
#include "BaccGeneratorPb210.hh"
#include "BaccGeneratorSingleDecay.hh"
#include "BaccGeneratorSingleParticle.hh"
#include "BaccGeneratorScintPhotons.hh"
#include "BaccGeneratorNeutronGenerator-p-Li.hh"
#include "BaccGeneratorKr83m.hh"
#include "BaccGeneratorXe129m.hh"
#include "BaccGeneratorXe131m.hh"
#include "BaccGeneratorWimp.hh"
#include "BaccGeneratorTritium.hh"
#include "BaccGeneratorGammaX.hh"
#include "BaccGeneratorYBe.hh"
#include "BaccGeneratorEventsFile.hh"

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					BaccSourceCatalog()
//------++++++------++++++------++++++------++++++------++++++------++++++------
BaccSourceCatalog::BaccSourceCatalog()
{
	baccManager = BaccManager::GetManager();
	baccManager->Register( this );
	
	sources.clear();
	
	sources.push_back( new BaccGeneratorAmBe );
	sources.push_back( new BaccGeneratorCfFission );
	sources.push_back( new BaccGeneratorRa226 );
	sources.push_back( new BaccGeneratorRn222 );
	sources.push_back( new BaccGeneratorPb210 );
	sources.push_back( new BaccGeneratorTh232 );
	sources.push_back( new BaccGeneratorDecayChain );
	sources.push_back( new BaccGeneratorU238 );
    sources.push_back( new BaccGeneratorSingleDecay ); 
    sources.push_back( new BaccGeneratorSingleParticle ); 
    sources.push_back( new BaccGeneratorScintPhotons ); 
	sources.push_back( new BaccGeneratorMASN );
	sources.push_back( new BaccGeneratorpLithium );
	sources.push_back( new BaccGeneratorKr83m );
	sources.push_back( new BaccGeneratorXe129m );
	sources.push_back( new BaccGeneratorXe131m );
    sources.push_back( new BaccGeneratorWimp );
	sources.push_back( new BaccGeneratorTritium );
	sources.push_back( new BaccGeneratorGammaX );
        sources.push_back( new BaccGeneratorYBe );
	sources.push_back( new BaccGeneratorEventsFile );
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					~BaccSourceCatalog()
//------++++++------++++++------++++++------++++++------++++++------++++++------
BaccSourceCatalog::~BaccSourceCatalog()
{
	sources.clear();
}
