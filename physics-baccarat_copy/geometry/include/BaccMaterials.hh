////////////////////////////////////////////////////////////////////////////////
/*	BaccMaterials.hh

This is the header file to contain all the material definitions in Baccarat.  
These definitions include optical properties.
********************************************************************************
Change log
  2013/09/26 - Initial submission (Vic)
  2014/04/09 - Added silicon to the list of materials
  2014/09/08 - Added some variables related to liquid argon, commented them out.
               (Brian)
*/
////////////////////////////////////////////////////////////////////////////////

#ifndef BaccMaterials_HH
#define BaccMaterials_HH 1

//
//	Class forwarding
//
class G4Material;
class G4VisAttributes;
class G4MaterialPropertiesTable;
class G4OpticalSurface;

class BaccManager;

//------++++++------++++++------++++++------++++++------++++++------++++++------
class BaccMaterials
{
	public:
		BaccMaterials();
		~BaccMaterials();
	
		static BaccMaterials *GetMaterials();
		
		inline G4Material *Acrylic() { return acrylic; };
		inline G4Material *Air() { return air; };
		inline G4Material *Aluminum() { return aluminum; };
		inline G4Material *Beryllium() { return beryllium; };
		inline G4Material *BeCu() { return berylliumCopper; };
		inline G4Material *Blackium() { return blackium; };
		inline G4Material *Copper() { return copper; };
		inline G4Material *Gadolinium() { return gadolinium; };
		inline G4Material *GasAr() { return gasAr; };
		inline G4Material *GasArN2() { return gasArN2; };
		inline G4Material *GasN2() { return gasN2; };
		inline G4Material *GasXe() { return gasXe; };
		inline G4Material *Gold() { return gold; };
		inline G4Material *GS20Glass() { return gs20Glass; };
		inline G4Material *Halon() {return halon; };
		inline G4Material *Iron() { return iron; };
		inline G4Material *Isohexane() { return isohexane; };
		inline G4Material *DopedIsohexaneTMB5() { return dopedIsohexaneTMB5; };
		inline G4Material *DopedIsohexaneTMB50() { return dopedIsohexaneTMB50;};
		inline G4Material *DopedIsohexaneGd3() { return dopedIsohexaneGd3; };
		inline G4Material *DopedIsohexaneGd7() { return dopedIsohexaneGd7; };
		inline G4Material *Kapton() { return kapton; };
		inline G4Material *KG2Glass() { return kg2Glass; };
		inline G4Material *Lead() { return lead; };
		inline G4Material *LeadGlass() { return leadGlass; };
		inline G4Material *LiquidAr() { return liquidAr; };
		inline G4Material *LiquidN2() { return liquidN2; };
		inline G4Material *LiquidXe() { return liquidXe; };
		inline G4Material *MineralOil() { return mineralOil; };
		inline G4Material *Peek() { return peek; };
		inline G4Material *Polyethylene() { return polyethylene; };
		inline G4Material *PVC() { return pvc; };
		inline G4Material *PolyethyleneBorated() { return polyethyleneBorated;};
		inline G4Material *Quartz() { return quartz; };
		inline G4Material *Rock() { return rock; };
		inline G4Material *Sapphire() { return sapphire; };
        inline G4Material *Silicon() { return silicon; };
		inline G4Material *SS316() { return ss316; };
		inline G4Material *Steel() { return steel; };
		inline G4Material *Teflon() { return teflon; };
		inline G4Material *Titanium() { return titanium; };
		inline G4Material *TMB() { return tmb; };
		inline G4Material *TPB() { return tpb; };
		inline G4Material *Tungsten() { return tungsten; };
		inline G4Material *Vacuum() { return vacuum; };
		inline G4Material *Water() { return water; };
		inline G4Material *DopedWater3() {return dopedWater3; };
		inline G4Material *DopedWater7() {return dopedWater7; };

		inline G4VisAttributes *AcrylicVis() { return acrylicVis; };
		inline G4VisAttributes *AirVis() { return airVis; };
		inline G4VisAttributes *AluminumVis() { return aluminumVis; };
		inline G4VisAttributes *BerylliumVis() { return berylliumVis; };
		inline G4VisAttributes *BeCuVis() { return berylliumCopperVis; };
		inline G4VisAttributes *BlackiumVis() { return blackiumVis; };
		inline G4VisAttributes *CopperVis() { return copperVis; };
		inline G4VisAttributes *GasArVis() { return gasArVis; };
		inline G4VisAttributes *GasArN2Vis() { return gasArN2Vis; };
		inline G4VisAttributes *GasN2Vis() { return gasN2Vis; };
		inline G4VisAttributes *GasXeVis() { return gasXeVis; };
		inline G4VisAttributes *GoldVis() { return goldVis; };
		inline G4VisAttributes *IronVis() { return ironVis; };
		inline G4VisAttributes *IsohexaneVis() { return isohexaneVis; };
		inline G4VisAttributes *KaptonVis() { return kaptonVis; };
		inline G4VisAttributes *LeadVis() { return leadVis; };
		inline G4VisAttributes *LeadGlassVis() { return leadGlassVis; };
		inline G4VisAttributes *LiquidArVis() { return liquidArVis; };
		inline G4VisAttributes *LiquidN2Vis() { return liquidN2Vis; };
		inline G4VisAttributes *LiquidXeVis() { return liquidXeVis; };
		inline G4VisAttributes *MineralOilVis() { return mineralOilVis; };
		inline G4VisAttributes *PeekVis() { return peekVis; };
		inline G4VisAttributes *PolyethyleneVis() { return polyethyleneVis; };
		inline G4VisAttributes *PolyethyleneBoratedVis()
				{ return polyethyleneBoratedVis; };
		inline G4VisAttributes *PVCVis() { return pvcVis; };
		inline G4VisAttributes *QuartzVis() { return quartzVis; };
		inline G4VisAttributes *RockVis() { return rockVis; };
		inline G4VisAttributes *SapphireVis() { return sapphireVis; };
		inline G4VisAttributes *SteelVis() { return steelVis; };
		inline G4VisAttributes *TeflonVis() { return teflonVis; };
		inline G4VisAttributes *TitaniumVis() { return titaniumVis; };
		inline G4VisAttributes *TPBVis() { return tpbVis; };
		inline G4VisAttributes *TungstenVis() { return tungstenVis; };
		inline G4VisAttributes *VacuumVis() { return vacuumVis; };
		inline G4VisAttributes *WaterVis() { return waterVis; };
		
		inline G4MaterialPropertiesTable *AcrylicTable() { return acrylicMat; };
		inline G4MaterialPropertiesTable *AirTable() { return airMat; };
		inline G4MaterialPropertiesTable *AluminumTable() {return aluminumMat;};
		inline G4MaterialPropertiesTable *BerylliumTable()
				{ return berylliumMat; };
		inline G4MaterialPropertiesTable *BeCuTable()
				{ return berylliumCopperMat; };
		inline G4MaterialPropertiesTable *BlackiumTable() {return blackiumMat;};
		inline G4MaterialPropertiesTable *CopperTable() { return copperMat; };
		inline G4MaterialPropertiesTable *GasArTable() { return gasArMat; };
		inline G4MaterialPropertiesTable *GasArN2Table() { return gasArN2Mat; };
		inline G4MaterialPropertiesTable *GasN2Table() { return gasN2Mat; };
		inline G4MaterialPropertiesTable *GasXeTable() { return gasXeMat; };
		inline G4MaterialPropertiesTable *GoldTable() {return goldMat; };
		inline G4MaterialPropertiesTable *HalonTable() {return halonMat; };
		inline G4MaterialPropertiesTable *IronTable() { return ironMat; };
		inline G4MaterialPropertiesTable *IsohexaneTable()
				{ return isohexaneMat; };
		inline G4MaterialPropertiesTable *KaptonTable() { return kaptonMat; };
		inline G4MaterialPropertiesTable *LeadTable() { return leadMat; };
		inline G4MaterialPropertiesTable *LeadGlassTable()
				{ return leadGlassMat; };
		inline G4MaterialPropertiesTable *LArTable() { return liquidArMat; };
		inline G4MaterialPropertiesTable *LN2Table() { return liquidN2Mat; };
		inline G4MaterialPropertiesTable *LXeTable() { return liquidXeMat; };
		inline G4MaterialPropertiesTable *MineralOilTable()
				{ return mineralOilMat; };
		inline G4MaterialPropertiesTable *PeekTable() { return peekMat; };
		inline G4MaterialPropertiesTable *PolyTable() {return polyethyleneMat;};
		inline G4MaterialPropertiesTable *PVCTable() {return pvcMat;};
		inline G4MaterialPropertiesTable *QuartzTable() { return quartzMat; };
		inline G4MaterialPropertiesTable *RockTable() { return rockMat; };
		inline G4MaterialPropertiesTable *SapphireTable() {return sapphireMat;};
		inline G4MaterialPropertiesTable *SS316Table() { return ss316Mat; };
		inline G4MaterialPropertiesTable *SteelTable() { return steelMat; };
		inline G4MaterialPropertiesTable *TeflonTable() { return teflonMat; };
		inline G4MaterialPropertiesTable *TitaniumTable() {return titaniumMat;};
		inline G4MaterialPropertiesTable *TPBTable() { return tpbMat; };
		inline G4MaterialPropertiesTable *TungstenTable() {return tungstenMat;};
		inline G4MaterialPropertiesTable *VacuumTable() { return vacuumMat; };
		inline G4MaterialPropertiesTable *WaterTable() { return waterMat; };
		
		inline G4OpticalSurface *AlQuartzSurface()
				{ return aluminumQuartzSurface; };
		inline G4OpticalSurface *GXeCopperSurface()
				{ return gasXeCopperSurface; };
		inline G4OpticalSurface *LXeCopperSurface()
				{ return liquidXeCopperSurface; };
		inline G4OpticalSurface *GXeHDPESurface()
				{ return gasXeHDPESurface; };
		inline G4OpticalSurface *LXeHDPESurface()
				{ return liquidXeHDPESurface; };
		inline G4OpticalSurface *GXeTeflonSurface()
				{ return gasXeTeflonSurface; };
		inline G4OpticalSurface *LXeTeflonSurface()
				{ return liquidXeTeflonSurface; };
		inline G4OpticalSurface *GXeSteelSurface()
				{ return gasXeSteelSurface; };
		inline G4OpticalSurface *LXeSteelSurface()
				{ return liquidXeSteelSurface; };
                inline G4OpticalSurface *GArTeflonSurface()
                                { return gasArTeflonSurface; };
                inline G4OpticalSurface *LArTeflonSurface()
                                { return liquidArTeflonSurface; };
                inline G4OpticalSurface *GArSteelSurface()
                                { return gasArSteelSurface; };
                inline G4OpticalSurface *LArSteelSurface()
                                { return liquidArSteelSurface; };
		inline G4OpticalSurface *GXeTiSurface()
				{ return gasXeTitaniumSurface; };
		inline G4OpticalSurface *LXeTiSurface()
				{ return liquidXeTitaniumSurface; };
		inline G4OpticalSurface *GArGoldSurface()
				{ return gasArN2GoldSurface; };
		inline G4OpticalSurface *GArAluminumSurface()
				{ return gasArN2AluminumSurface; };
		inline G4OpticalSurface *GArN2GoldSurface()
				{ return gasArN2GoldSurface; };
		inline G4OpticalSurface *GArN2AluminumSurface()
				{ return gasArN2AluminumSurface; };
		inline G4OpticalSurface *QuartzTeflonSurface()
				{ return quartzTeflonSurface; };
		
        void UpdateElectricField();
		void SetOpticalDebugging( G4bool );
		G4bool GetOpticalDebugging() { return opticalDebugging; };
		
		//	Materials methods
		void SetLXeTeflonRefl( G4double );
		void SetLXeSteelRefl( G4double );
		void SetLXeAbs( G4double );
		void SetLXeRayleigh( G4double );
		void SetGXeTeflonRefl( G4double );
		void SetGXeSteelRefl( G4double );
		void SetGXeAbs( G4double );
		void SetGXeRayleigh( G4double );
		void SetAlUnoxQuartzRefl( G4double );


	private:
		void DefineArrays();
		void CreateMaterials();
		void SetOpticalProperties();
		void CreateOpticalSurfaces();
		void CreateVisualAttributes();
		void InitializeMatrix( G4int, G4int* );
		void InitializeMatrix( G4int, G4double* );

	private:
		static BaccMaterials *baccMaterials;

		G4Material *acrylic;
		G4Material *air;		
		G4Material *aluminum;
		G4Material *beryllium;
		G4Material *berylliumCopper;
		G4Material *blackium;
		G4Material *copper;
		G4Material *gadolinium;
		G4Material *gasAr;
		G4Material *gasArN2;
		G4Material *gasN2;
		G4Material *gasXe;
		G4Material *gold;
		G4Material *gs20Glass;
		G4Material *halon;
		G4Material *iron;
		G4Material *isohexane;
		G4Material *dopedIsohexaneTMB5;
		G4Material *dopedIsohexaneTMB50;
		G4Material *dopedIsohexaneGd3;
		G4Material *dopedIsohexaneGd7;
		G4Material *kapton;
		G4Material *kg2Glass;
		G4Material *lead;
		G4Material *leadGlass;
		G4Material *liquidAr;
		G4Material *liquidN2;
		G4Material *liquidXe;
		G4Material *mineralOil;
		G4Material *peek;
		G4Material *polyethylene;
		G4Material *polyethyleneBorated;
		G4Material *pvc;
		G4Material *quartz;
		G4Material *rock;
		G4Material *sapphire;
		G4Material *silicon;
		G4Material *ss316;
		G4Material *steel;
		G4Material *teflon;
		G4Material *titanium;
		G4Material *tmb;
		G4Material *tpb;
		G4Material *tungsten;
		G4Material *vacuum;
		G4Material *water;
		G4Material *dopedWater3;
		G4Material *dopedWater7;		

		G4VisAttributes *acrylicVis;
		G4VisAttributes *airVis;
		G4VisAttributes *aluminumVis;
		G4VisAttributes *berylliumVis;
		G4VisAttributes *berylliumCopperVis;
		G4VisAttributes *blackiumVis;
		G4VisAttributes *copperVis;
		G4VisAttributes *gasArVis;
		G4VisAttributes *gasArN2Vis;
		G4VisAttributes *gasN2Vis;
		G4VisAttributes *gasXeVis;
		G4VisAttributes *goldVis;
		G4VisAttributes *gs20GlassVis;
		G4VisAttributes *ironVis;
		G4VisAttributes *isohexaneVis;
		G4VisAttributes *kaptonVis;
		G4VisAttributes *kg2GlassVis;
		G4VisAttributes *leadVis;
		G4VisAttributes *leadGlassVis;
		G4VisAttributes *liquidArVis;
		G4VisAttributes *liquidN2Vis;
		G4VisAttributes *liquidXeVis;
		G4VisAttributes *mineralOilVis;
		G4VisAttributes *peekVis;
		G4VisAttributes *polyethyleneVis;
		G4VisAttributes *polyethyleneBoratedVis;
		G4VisAttributes *pvcVis;
		G4VisAttributes *quartzVis;
		G4VisAttributes *rockVis;
		G4VisAttributes *sapphireVis;
		G4VisAttributes *steelVis;
		G4VisAttributes *teflonVis;
		G4VisAttributes *titaniumVis;
		G4VisAttributes *tpbVis;
		G4VisAttributes *tungstenVis;
		G4VisAttributes *vacuumVis;
		G4VisAttributes *waterVis;
		
		G4MaterialPropertiesTable *acrylicMat;
		G4MaterialPropertiesTable *airMat;
		G4MaterialPropertiesTable *aluminumMat;
		G4MaterialPropertiesTable *berylliumMat;
		G4MaterialPropertiesTable *berylliumCopperMat;
		G4MaterialPropertiesTable *blackiumMat;
		G4MaterialPropertiesTable *copperMat;
		G4MaterialPropertiesTable *gasArMat;
		G4MaterialPropertiesTable *gasArN2Mat;
		G4MaterialPropertiesTable *gasN2Mat;
		G4MaterialPropertiesTable *gasXeMat;
		G4MaterialPropertiesTable *goldMat;
		G4MaterialPropertiesTable *gs20GlassMat;
		G4MaterialPropertiesTable *halonMat;
		G4MaterialPropertiesTable *ironMat;
		G4MaterialPropertiesTable *isohexaneMat;
		G4MaterialPropertiesTable *kaptonMat;
		G4MaterialPropertiesTable *kg2GlassMat;
		G4MaterialPropertiesTable *leadMat;
		G4MaterialPropertiesTable *leadGlassMat;
		G4MaterialPropertiesTable *liquidArMat;
		G4MaterialPropertiesTable *liquidN2Mat;
		G4MaterialPropertiesTable *liquidXeMat;
		G4MaterialPropertiesTable *mineralOilMat;
		G4MaterialPropertiesTable *peekMat;
		G4MaterialPropertiesTable *polyethyleneMat;
		G4MaterialPropertiesTable *pvcMat;
		G4MaterialPropertiesTable *quartzMat;
		G4MaterialPropertiesTable *rockMat;
		G4MaterialPropertiesTable *sapphireMat;
		G4MaterialPropertiesTable *ss316Mat;
		G4MaterialPropertiesTable *steelMat;
		G4MaterialPropertiesTable *teflonMat;
		G4MaterialPropertiesTable *titaniumMat;
		G4MaterialPropertiesTable *tpbMat;
		G4MaterialPropertiesTable *tungstenMat;
		G4MaterialPropertiesTable *vacuumMat;
		G4MaterialPropertiesTable *waterMat;
		
		G4OpticalSurface *aluminumQuartzSurface;
		G4OpticalSurface *gasXeCopperSurface;
		G4OpticalSurface *liquidXeCopperSurface;
		G4OpticalSurface *gasXeHDPESurface;
		G4OpticalSurface *liquidXeHDPESurface;
		G4OpticalSurface *gasXeTeflonSurface;
		G4OpticalSurface *liquidXeTeflonSurface;
		G4OpticalSurface *gasXeSteelSurface;
		G4OpticalSurface *liquidXeSteelSurface;
                G4OpticalSurface *gasArTeflonSurface;
                G4OpticalSurface *liquidArTeflonSurface;
                G4OpticalSurface *gasArSteelSurface;
                G4OpticalSurface *liquidArSteelSurface;
		G4OpticalSurface *gasXeTitaniumSurface;
		G4OpticalSurface *liquidXeTitaniumSurface;
		G4OpticalSurface *gasArGoldSurface;
		G4OpticalSurface *gasArAluminumSurface;
		G4OpticalSurface *gasArN2GoldSurface;
		G4OpticalSurface *gasArN2AluminumSurface;
		G4OpticalSurface *quartzTeflonSurface;
		
		//	These arrays are used to hold the optical parameters of the various
		//	materials.
		G4bool opticalDebugging;
		
		G4double *photonWavelengths;
		G4double *photonEnergies;
		G4double *photonEnergies_ConstProp;
		
		G4double *optDebugRefIndex;
		G4double *optDebugReflection;
		G4double *optDebugAbsLength;
		G4double *optDebugRayleighLength;
		
		G4int num_pp;
		G4int num_pp_constProp;
		G4int num_water;
		G4int num_tpbAbs;
		G4int num_tpbEmi;
		
		G4double *acrylicRefractiveIndex;
		G4double *airRefractiveIndex;
		G4double *aluminumRefl;
		G4double *aluminumUnoxidizedRefl;
		G4double *berylliumRefl;
		G4double *berylliumCopperRefl;
		G4double *copperRefl;
		G4double *gasArRindex;
		G4double *gasArAbslength;
		G4double *gasArN2Rindex;
		G4double *gasArN2Abslength;
		G4double *gasN2Rindex;
		G4double *gasN2Abslength;
  //G4double *gasXeScint;
		G4double *gasXeRindex;
		G4double *gasXeAbslength;
		G4double *goldRefl;
		G4double *ironRefl;
		G4double *isohexaneRindex;
		G4double *leadRefl;
		G4double *leadGlassRefractiveIndex;
		G4double *leadGlassAbsorption;
  //G4double *liquidArScint;
  //G4double *liquidArRindex;
  //G4double *liquidArAbslength;
  //G4double *liquidArRayleigh;
  //G4double *liquidN2Scint;
  //G4double *liquidN2Rindex;
  //G4double *liquidN2Abslength;
  //G4double *liquidN2Rayleigh;
  //G4double *liquidXeScint;
  //G4double *liquidArRindix;
  //G4double *liquidArAbslength;
  //G4double *liquidArRayleigh;
		G4double *liquidXeRindex;
		G4double *liquidXeAbslength;
		G4double *liquidXeRayleigh;
		G4double *mineralOilRIndex;
		G4double *peekRefl;
		G4double *polyethyleneRefl;
		G4double *polyethyleneBoratedRefl;
		G4double *pvcRefl;
		G4double *quartzRefractiveIndex;
		G4double *quartzAbsorption;
  //G4double *teflonAbsorption;
		G4double *rockRefl;
		G4double *sapphireRefractiveIndex;
                G4double *teflonRefractiveIndex;
		G4double *sapphireAbsorption;
		G4double *ss316Refl;
		G4double *steelRefl;
		G4double *teflonRefl;
		G4double *titaniumRefl;
		G4double *tpbAbsorptionEnergies;
		G4double *tpbAbsorption;
		G4double *tpbEmissionEnergies;
		G4double *tpbEmission;
		G4double *tungstenRefl;
		G4double *waterPhotonEnergies;	//	Note that water gets its own
		G4double *waterRefractiveIndex;	//	energies matrix.
		G4double *waterAbsorption;
		G4double *halonRefl;
		
		//	Support for internal workings
		BaccManager *baccManager;
};

#endif
