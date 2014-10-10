////////////////////////////////////////////////////////////////////////////////
/*	BACCARAT.cc

This is the main code file for Baccarat.
********************************************************************************
* Change log
  2013/09/26 - Initial submission (Vic)
  2014/01/04 - Code cleanup (Vic)
  2014/01/22 - Cosmetic shenannigans (Vic)
  2014/09/08 - Added code to check whether this checkout uses git or svn (Brian)
*/
////////////////////////////////////////////////////////////////////////////////

//
//	GEANT4 includes
//
#include "globals.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4Version.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE_XM
#include "G4UIXm.hh"
#endif

//
//	Bacc includes
//
#include "BaccMaterials.hh"
#include "BaccPhysicsList.hh"
#include "BaccDetectorConstruction.hh"
#include "BaccPrimaryGeneratorAction.hh"
#include "BaccRunAction.hh"
#include "BaccEventAction.hh"
#include "BaccSteppingAction.hh"
#include "BaccOutput.hh"
#include "BaccSourceCatalog.hh"
#include "BaccGeometryCatalog.hh"
#include "BaccManager.hh"

//
//	C++ includes
//
#include <cstdlib>
#include <cstdio>

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					main()
//------++++++------++++++------++++++------++++++------++++++------++++++------
int main( int argc, char **argv )
{
	
	if( argc > 3 ) {
		G4cout << G4endl << G4endl << G4endl;
		G4cout << "You have supplied " << argc-1 << " arguments, but Bacc "
			   << "can only handle two." << G4endl;
		G4cout << G4endl << G4endl << G4endl;
		
		exit(0);
	}

	if( G4VERSION_NUMBER < 940 ) {
		stringstream version;
		version << G4VERSION_NUMBER;
		G4String majorVersion = version.str().substr(0,1);
		G4String minorVersion = version.str().substr(1,1);
		G4String patchLevel = version.str().substr(2,1);

		G4cout << G4endl << G4endl << G4endl;
		G4cout << "You are running Geant4." << majorVersion << "."
			   << minorVersion << ".p0" << patchLevel << G4endl;
		G4cout << "Bacc no longer operates with versions of Geant4 prior to "
			   << "4.9.4.p00" << G4endl;
		G4cout << G4endl << G4endl << G4endl;
		
		exit(0);
	}
	
	if( argc == 3 && !strcmp(argv[2],"-f") ) {
		strcpy( argv[2], argv[1] );
		strcpy( argv[1], "-f" );
	}
	
	if( G4VERSION_NUMBER != 944 && G4VERSION_NUMBER != 951 &&
			G4VERSION_NUMBER != 952 ) {
		//	The logic in this next line is aesthetically displeasing, but it's
		//	actually the most concise way to perform the required check.
		if( argc>1 && !strcmp(argv[1], "-f") )
			;
		else {
			
			G4cout << G4endl << G4endl << G4endl;
			G4cout << "You should run Bacc with one of the following "
				   << "versions of Geant4:" << G4endl;
			G4cout << "\t4.9.4.p04" << G4endl;
			G4cout << "\t4.9.5.p01" << G4endl;
			G4cout << "\t4.9.5.p02" << G4endl;
			G4cout << G4endl;
			
			stringstream version;
			version << G4VERSION_NUMBER;
			G4String majorVersion = version.str().substr(0,1);
			G4String minorVersion = version.str().substr(1,1);
			G4String patchLevel = version.str().substr(2,1);
			G4cout << "If you insist on running with Geant4." << majorVersion
				   << "." << minorVersion << ".p0" << patchLevel
				   << ", you can force execution with the" << G4endl;
			G4cout << "'-f' flag." << G4endl;
			G4cout << G4endl << G4endl << G4endl;
			
			exit(0);
		}
	}

	//	Construct the default run manager
	G4RunManager* runManager = new G4RunManager;

	//	Instantiate and create all the required classes
	BaccManager *baccManager;
    baccManager = new BaccManager();
	
	//	For this next bit of code, COMPDIR is set at compilation time using the
	//	compilation switch -DCOMPDIR=\"`pwd`\". It is therefore a hard-coded
	//	string of where the executable was compiled. This is relevant for
	//	generating the SVN diffs if you're running the executable anywhere other
	//	than the top-level Bacc directory.
	G4String compDir = COMPDIR;
	if( compDir.substr(compDir.length()-1,1) == "/" )
		compDir = compDir.substr( 0, compDir.length()-1 );
	compDir = compDir.substr( 0, compDir.find_last_of( "/" ) );
	baccManager->SetCompilationDirectory( compDir );

        char repoTestCommand[100];
        sprintf(repoTestCommand, "ls -a %s/../ | grep svn", COMPDIR);
        baccManager->SetIsSVNRepo( (bool) !bool( system( repoTestCommand ) ) );
        sprintf(repoTestCommand, "ls -a %s/../ | grep git", COMPDIR);
        baccManager->SetIsGitRepo( (bool) !bool( system( repoTestCommand ) ) );

	BaccMaterials *baccMaterials;
    baccMaterials = new BaccMaterials();
	
	BaccPhysicsList *BaccPhysics = new BaccPhysicsList();
	runManager->SetUserInitialization( BaccPhysics );

	BaccDetectorConstruction *BaccDetector =
			new BaccDetectorConstruction();
	runManager->SetUserInitialization( BaccDetector );

	BaccPrimaryGeneratorAction *BaccGenerator =
			new BaccPrimaryGeneratorAction();
	runManager->SetUserAction( BaccGenerator );

	BaccRunAction *BaccRun = new BaccRunAction();
	runManager->SetUserAction( BaccRun );

	BaccEventAction *BaccEvent = new BaccEventAction();
	runManager->SetUserAction( BaccEvent );

	BaccSteppingAction *BaccStep = new BaccSteppingAction();
	runManager->SetUserAction( BaccStep );
	
	BaccSourceCatalog *BaccSourceCat;
    BaccSourceCat = new BaccSourceCatalog();

	BaccGeometryCatalog *BaccGeometryCat;
    BaccGeometryCat = new BaccGeometryCatalog();
	
	//	Set up the visualization
#ifdef G4VIS_USE
	G4VisManager *visManager = new G4VisExecutive;
	visManager->Initialize();
#endif

	// Initialize G4 kernel
	runManager->Initialize();
	
	//	Get the user interface manager
	G4UImanager *UI = G4UImanager::GetUIpointer();

	// Define (G)UI terminal for interactive mode
	G4UIsession *session = 0;
#ifdef G4UI_USE_TCSH
	session = new G4UIterminal(new G4UItcsh);      
#else
	session = new G4UIterminal();
#endif
	
	// Execute input macro, if specified
	if( argc == 1 || (argc == 2 && !strcmp(argv[1],"-f")) ) {
		session->SessionStart();
		delete session;	
	} else {
		G4String commandFile = argv[1];
		if( argc > 2 )
			commandFile = argv[2];
		G4String command = "/control/execute " + commandFile;
		UI->ApplyCommand(command);
	
		//	Read in the commands file, and if the last command is "exit", don't
		//	start the command session.
		ifstream commands( commandFile.c_str() );
		commands.seekg( 0, ios::end );
		int length = commands.tellg();
		commands.seekg( 0, ios::beg );
		char *inputBuffer;
		inputBuffer = new char[length+1];
		commands.read( inputBuffer, length );
		inputBuffer[length] = '\0';
		commands.close();
		G4String commandList = inputBuffer;
		delete [] inputBuffer;
		while( commandList.substr( commandList.length()-1 ) == "\n" ||
			   commandList.substr( commandList.length()-1 ) == "\t" ||
			   commandList.substr( commandList.length()-1 ) == " " )
			commandList = commandList.substr( 0, commandList.length()-1 );
		if( commandList.find_last_of("\n") < G4String::npos )
			commandList = commandList.substr( commandList.find_last_of("\n") );
		while( commandList.substr( 0,1 ) == "\n" ||
			   commandList.substr( 0,1 ) == "\t" ||
			   commandList.substr( 0,1 ) == " " )
			commandList = commandList.substr( 1 );
		if( commandList != "exit" ) {
			session->SessionStart();
			delete session;
		}
	}

	//	Clean up
#ifdef G4VIS_USE
	delete visManager;
#endif
	
	delete runManager;
	delete baccManager;

	return 0;
}


