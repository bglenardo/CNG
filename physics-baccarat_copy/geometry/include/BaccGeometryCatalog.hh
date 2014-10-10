////////////////////////////////////////////////////////////////////////////////
/*	BaccGeometryCatalog.hh

This is the header file to handle the various event generators. This catalog 
object is essentially a sub-manager for the geometry.
********************************************************************************
Change log
  2013/11/20 - Initial submission (Vic)
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef BaccGeometryCatalog_HH
#define BaccGeometryCatalog_HH 1

//
//	C/C++ includes
//
#include <vector>

//
//	GEANT4 includes
//
#include "globals.hh"

//
//	Class forwarding
//
class BaccManager;
class BaccDetector;

//------++++++------++++++------++++++------++++++------++++++------++++++------
class BaccGeometryCatalog
{
	public:
		BaccGeometryCatalog();
		~BaccGeometryCatalog();

		static BaccGeometryCatalog *GetCatalog();

	public:
		G4int GetNumGeometryTypes() { return geometry.size(); };
		BaccDetector *GetGeometryType( G4int i ) { return geometry[i]; };

	private:
		BaccManager *baccManager;

		static BaccGeometryCatalog *baccGeometryCatalog;
		
		std::vector<BaccDetector*> geometry;
};

#endif
