////////////////////////////////////////////////////////////////////////////////
/*	BaccMaterials.cc

This is the code file to contain all the material definitions in Baccarat.  
These definitions include optical properties.
********************************************************************************
Change log
  2013/09/26 - Initial submission (Vic)
  2014/01/03 - Code cleanup (Vic)
  2014/04/09 - Added silicon to the list of materials
*/
////////////////////////////////////////////////////////////////////////////////

#define LXETEMPERATURE 173*kelvin //Sets the T of the LXe,GXe,quartz,blackium,vacuum
#define LXEPRESSURE 1.57*bar //~2 bar in Run02, 2.854 g/cm^3, 18.7E-3 g/cm^3

#define LXEDENS 2.888*g/cm3	// NIST LXe density (used 2 places because needed to set refr. index and Rayl.)
#define GXEDENS 15e-3*g/cm3	// NIST GXe density for 1.57 bar and 173.1 K

//
//	GEANT4 includes
//
#include "G4Isotope.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4OpticalSurface.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4SystemOfUnits.hh"

//
//	Bacc includes
//
#include "BaccMaterials.hh"
#include "BaccManager.hh"

G4double constC = 299792458;

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					BaccMaterials()
//------++++++------++++++------++++++------++++++------++++++------++++++------
BaccMaterials *BaccMaterials::baccMaterials = 0;
BaccMaterials::BaccMaterials()
{
	baccManager = BaccManager::GetManager();
	baccManager->Register( this );

	DefineArrays();
	CreateMaterials();
	SetOpticalProperties();
	CreateOpticalSurfaces();
	SetOpticalDebugging( false );
	CreateVisualAttributes();
	
	baccMaterials = this;
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					~BaccMaterials()
//------++++++------++++++------++++++------++++++------++++++------++++++------
BaccMaterials::~BaccMaterials()
{
	delete acrylic;
	delete air;
	delete aluminum;
	delete beryllium;
	delete berylliumCopper;
	delete blackium;
	delete copper;
	delete silicon;
	delete gasAr;
	delete gasArN2;
	delete gasN2;
	delete gasXe;
	delete gold;
	delete gs20Glass;
	delete halon;
	delete iron;
	delete isohexane;
	delete dopedIsohexaneTMB5;
	delete dopedIsohexaneTMB50;
	delete dopedIsohexaneGd3;
	delete dopedIsohexaneGd7;
	delete kapton;
	delete kg2Glass;
	delete lead;
	delete leadGlass;
	delete liquidAr;
	delete liquidN2;
	delete liquidXe;
	delete mineralOil;
	delete peek;
	delete polyethylene;
	delete polyethyleneBorated;
        delete pvc;
	delete quartz;
	delete rock;
	delete sapphire;
	delete ss316;
	delete steel;
	delete teflon;
	delete titanium;
	delete tmb;
	delete tpb;
	delete tungsten;
	delete vacuum;
	delete water;
	delete dopedWater3;
	delete dopedWater7;

	delete acrylicVis;
	delete airVis;
	delete aluminumVis;
	delete berylliumVis;
	delete berylliumCopperVis;
	delete blackiumVis;
	delete copperVis;
	delete gasArVis;
	delete gasArN2Vis;
	delete gasN2Vis;
	delete gasXeVis;
	delete goldVis;
	delete gs20GlassVis;
	delete ironVis;
	delete isohexaneVis;
	delete kaptonVis;
	delete kg2GlassVis;
	delete leadVis;
	delete leadGlassVis;
	delete liquidArVis;
	delete liquidN2Vis;
	delete liquidXeVis;
	delete mineralOilVis;
	delete peekVis;
	delete polyethyleneVis;
	delete polyethyleneBoratedVis;
        delete pvcVis;
	delete quartzVis;
	delete rockVis;
	delete sapphireVis;
	delete steelVis;
	delete teflonVis;
	delete titaniumVis;
	delete tpbVis;
	delete tungstenVis;
	delete vacuumVis;
	delete waterVis;
	
	delete acrylicMat;
	delete airMat;
	delete aluminumMat;
	delete berylliumMat;
	delete berylliumCopperMat;
	delete copperMat;
	delete gasArMat;
	delete gasArN2Mat;
	delete gasN2Mat;
	delete gasXeMat;
	delete goldMat;
	delete gs20GlassMat;
	delete halonMat;
	delete ironMat;
	delete isohexaneMat;
	delete kaptonMat;
	delete kg2GlassMat;
	delete leadMat;
	delete leadGlassMat;
	delete liquidArMat;
	delete liquidN2Mat;
	delete liquidXeMat;
	delete mineralOilMat;
	delete peekMat;
	delete polyethyleneMat;
        delete pvcMat;
	delete quartzMat;
	delete rockMat;
	delete sapphireMat;
	delete ss316Mat;
	delete steelMat;
	delete teflonMat;
	delete titaniumMat;
	delete tpbMat;
	delete tungstenMat;
	delete vacuumMat;
	delete waterMat;
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					GetMaterials()
//------++++++------++++++------++++++------++++++------++++++------++++++------
BaccMaterials *BaccMaterials::GetMaterials()
{
	return baccMaterials;
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					DefineArrays()
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccMaterials::DefineArrays()
{
	//	This is a method for defining the arrays that are used in setting the
	//	optical parameters in SetOpticalProperties.
	
	//	Note: While xenon only scintillates in the ~170-180 nm range, optical
	//	properties are defined for the entire range of wavelengths so as to
	//	avoid the dreaded "G4Excpetion: OutOfRange" error that otherwise
	//	plagues the output.
	
	//	Note: 175.8641 nm = 7.05 eV
	//		  177.6278 nm = 6.98 eV
	//		  179.4272 nm = 6.91 eV
	
	
	num_pp = 23;
	num_pp_constProp = 2;
	
	const G4int NUM_PP = num_pp;
	const G4int NUM_PP_ConstProp = num_pp_constProp;
	
	photonWavelengths = new G4double[NUM_PP];
	photonWavelengths[0] = 110.0;
	photonWavelengths[1] = 144.5;
	photonWavelengths[2] = 175.8641;
	photonWavelengths[3] = 177.6278;
	photonWavelengths[4] = 179.4272;
	photonWavelengths[5] = 193.6;
	photonWavelengths[6] = 250.3;
	photonWavelengths[7] = 303.4;
	photonWavelengths[8] = 340.4;
	photonWavelengths[9] = 410.2;
	photonWavelengths[10] = 467.8;
	photonWavelengths[11] = 508.6;
	photonWavelengths[12] = 546.1;
	photonWavelengths[13] = 627.8;
	photonWavelengths[14] = 706.5;
	photonWavelengths[15] = 766.5;
	photonWavelengths[16] = 844.7;
	photonWavelengths[17] = 1000.0;
	photonWavelengths[18] = 1300.0;
	photonWavelengths[19] = 1529.6;
	photonWavelengths[20] = 1600.0;
	photonWavelengths[21] = 1800.0;
	photonWavelengths[22] = 2058.2;
	photonEnergies = new G4double[NUM_PP];
	for( G4int i=0; i<NUM_PP; i++ )
		photonEnergies[i] =
				(4.13566743E-15*constC/(photonWavelengths[i]*1.E-9))*eV;

	optDebugRefIndex = new G4double[NUM_PP_ConstProp];
	optDebugRefIndex[0] = optDebugRefIndex[1] = 1.;
	optDebugReflection = new G4double[NUM_PP_ConstProp];
	optDebugReflection[0] = optDebugReflection[1] = 0;
	optDebugAbsLength = new G4double[NUM_PP_ConstProp];
	optDebugAbsLength[0] = optDebugAbsLength[1] = 1000.*km;
	optDebugRayleighLength = new G4double[NUM_PP_ConstProp];
	optDebugRayleighLength[0] = optDebugRayleighLength[1] = 1000.*km;
	
	// Taking average refractive index from
	//	http://en.wikipedia.org/wiki/Poly(methyl_methacrylate)
	acrylicRefractiveIndex = new G4double[NUM_PP_ConstProp];
	acrylicRefractiveIndex[0] = acrylicRefractiveIndex[1] = 1.4896;

	//	Air is set to have a constant index of refraction that spans from the
	//	highest-energy scintillation photons to 2 microns to allow for
	//	refraction and reflection of Cerenkov photons.
	airRefractiveIndex = new G4double[NUM_PP_ConstProp];
	airRefractiveIndex[0] = airRefractiveIndex[1] = 1.000293;
	
	aluminumRefl = new G4double[NUM_PP];
	for( G4int i=0; i<NUM_PP; i++ )
		aluminumRefl[i] = 0.1;
	aluminumRefl[1] = aluminumRefl[2] = aluminumRefl[3] = aluminumRefl[4] = 0.7;
	
	aluminumUnoxidizedRefl = new G4double[NUM_PP_ConstProp];
	aluminumUnoxidizedRefl[0] = aluminumUnoxidizedRefl[1] = 1.0;
	
	berylliumRefl = new G4double[NUM_PP_ConstProp];
	berylliumRefl[0] = berylliumRefl[1] = 0.1;

	berylliumCopperRefl = new G4double[NUM_PP];
	for( G4int i=0; i<NUM_PP; i++ )
		berylliumCopperRefl[i] = 0.1;

	copperRefl = new G4double[NUM_PP];
	for( G4int i=0; i<NUM_PP; i++ )
		copperRefl[i] = 0.1;
	
	gasArRindex = new G4double[NUM_PP_ConstProp];
	gasArRindex[0] = gasArRindex[1] = 1.000293;
	gasArAbslength = new G4double[NUM_PP_ConstProp];
	gasArAbslength[0] = gasArAbslength[1] = 100.*km;
	
	gasArN2Rindex = new G4double[NUM_PP_ConstProp];
	gasArN2Rindex[0] = gasArN2Rindex[1] = 1.000293;
	gasArN2Abslength = new G4double[NUM_PP_ConstProp];
	gasArN2Abslength[0] = gasArN2Abslength[1] = 100.*km;
	
	gasN2Rindex = new G4double[NUM_PP_ConstProp];
	gasN2Rindex[0] = gasN2Rindex[1] = 1.000293;
	gasN2Abslength = new G4double[NUM_PP_ConstProp];
	gasN2Abslength[0] = gasN2Abslength[1] = 100.*km;
	
	gasXeRindex = new G4double[NUM_PP_ConstProp];
	gasXeRindex[0] = gasXeRindex[1] = 1.000702;
	gasXeAbslength = new G4double[NUM_PP_ConstProp];
	gasXeAbslength[0] = gasXeAbslength[1] = 5.0*m;
	
	goldRefl = new G4double[NUM_PP_ConstProp];
	goldRefl[0] = goldRefl[1] = 0.1;
	
	ironRefl = new G4double[NUM_PP_ConstProp];
	ironRefl[0] = ironRefl[1] = 0.001;
	
	isohexaneRindex = new G4double[NUM_PP_ConstProp];
	isohexaneRindex[0] = isohexaneRindex[1] = 1.379;
	
	leadRefl = new G4double[NUM_PP_ConstProp];
	leadRefl[0] = leadRefl[1] = 0.001;	//	Same as for Cu
	
	//	These definitions are, for now, blatantly ripped off from the quartz
	//	definitions, with the exception that the index of refraction has had
	//	0.15 added to every wavelength. I have no rational basis for believing
	//	this is the case other than the fact that Wikipedia says the index of
	//	refaction for quartz is "1.55" and "1.7" for lead glass.
	leadGlassRefractiveIndex = new G4double[NUM_PP];
	leadGlassRefractiveIndex[0] = 1.5317+4102.2/pow(photonWavelengths[0],2.)+1.8831e7/pow(photonWavelengths[0],4.);
	leadGlassRefractiveIndex[1] = 1.8; //guessed: makes the curve look smooth
	leadGlassRefractiveIndex[2] = 1.68175;
	leadGlassRefractiveIndex[3] = 1.67959;
	leadGlassRefractiveIndex[4] = 1.67738;
	leadGlassRefractiveIndex[5] = 1.65999;
	leadGlassRefractiveIndex[6] = 1.60032;
	leadGlassRefractiveIndex[7] = 1.576955;
	leadGlassRefractiveIndex[8] = 1.56747;
	leadGlassRefractiveIndex[9] = 1.556502;
	leadGlassRefractiveIndex[10] = 1.551027;
	leadGlassRefractiveIndex[11] = 1.548229;
	leadGlassRefractiveIndex[12] = 1.546174;
	leadGlassRefractiveIndex[13] = 1.542819;
	leadGlassRefractiveIndex[14] = 1.540488;
	leadGlassRefractiveIndex[15] = 1.539071;
	leadGlassRefractiveIndex[16] = 1.537525;
	leadGlassRefractiveIndex[17] = 1.53503;
	leadGlassRefractiveIndex[18] = 1.53102;
	leadGlassRefractiveIndex[19] = 1.52800;
	leadGlassRefractiveIndex[20] = 1.52703;
	leadGlassRefractiveIndex[21] = 1.52413;
	leadGlassRefractiveIndex[22] = 1.51998;
	for( G4int i=0; i<NUM_PP; i++ )
		leadGlassRefractiveIndex[i] += 0.15;
	leadGlassAbsorption = new G4double[NUM_PP_ConstProp];
        leadGlassAbsorption[0] = 1.*m; leadGlassAbsorption[1] = 1./3*m; //taken from quartz
        //see http://www.mt-berlin.com/frames_cryst/descriptions/quartz%20.htm for abs.
	
	//	These LXe properties are set by Matthew Szydagis, based on the
	//	most recent papers.
	//	The equation for the index of refraction for liquid xenon comes from
	//	the Journal of Chemical Physics 123, 234508 (2005), and is a
	//	generalization for any density (hence any T and P) and any
	//	wavelength, but it has only been vetted at 161 to 170 K and at
	//      140 nm to 700 nm in wavelength range.
	liquidXeRindex = new G4double[NUM_PP];
	liquidXeRayleigh = new G4double[NUM_PP];
	for( G4int i=0; i<NUM_PP; i++ ) {
	  G4double term = 1.2055e-2*(2./3.)*(LXEDENS/(5.8984e-3*g/cm3))*
	                 (0.26783/(43.741-pow(photonWavelengths[i]*1e-3,-2.))+
	                  0.29481/(57.480-pow(photonWavelengths[i]*1e-3,-2.))+
	                  5.03330/(112.74-pow(photonWavelengths[i]*1e-3,-2.)));
	  liquidXeRindex[i] = sqrt(2*term+1)*sqrt(1/(1-term)); 
	  if(i==1) liquidXeRindex[i]=1.8*(LXETEMPERATURE/(161.35*kelvin));
	  if(i==0) liquidXeRindex[i]=1.000;
	  //from L.M. Barkov et al., NIM A379 (1996), p.482 and ref. there-in
	  
	  G4double lightSpeed = constC*m/s; G4double mathPi = 3.141592653589793;
	  G4double omega = (2*mathPi*lightSpeed)/(photonWavelengths[i]*nm);
	  G4double kBoltz = 1.38e-23*joule/kelvin; G4double kappaT = 1.68e-5*cm2/newton;
	  G4double epsilon = pow(liquidXeRindex[i],2.); //G4double constA = 0.0801*cm3/g;
	  G4double dedpT = (epsilon-1)*(epsilon+2)/(3*LXEDENS);
	  G4double inverse = pow(omega,4.)/(6*mathPi*pow(lightSpeed,4.))*kBoltz*LXETEMPERATURE*pow(LXEDENS,2.)*kappaT*pow(dedpT,2.);
	  liquidXeRayleigh[i] = 1./(inverse); //based on NIM A 489 (2002) p.189
	  
	}
	
	liquidXeAbslength = new G4double[NUM_PP_ConstProp];
	liquidXeAbslength[0] = liquidXeAbslength[1] = 8.6*m;
	
	//	Note that the refractive index is dirt simple and only roughly correct.
	//	This is just to make sure optical photons propagate at all.
	mineralOilRIndex = new G4double[NUM_PP_ConstProp];
	mineralOilRIndex[0] = mineralOilRIndex[1] = 1.53;

	// Zero for no reason other than it is grey 
	peekRefl = new G4double[NUM_PP_ConstProp];
	peekRefl[0] = peekRefl[1] = 0.0;
	
	polyethyleneRefl = new G4double[NUM_PP_ConstProp];
	polyethyleneRefl[0] = polyethyleneRefl[1] = 0.10;	//	~10% acc. to
														//	Dr. White @175nm
	// Not accurate because dyes are put in borated poly.
	polyethyleneBoratedRefl = new G4double[NUM_PP_ConstProp];
	polyethyleneBoratedRefl[0] = polyethyleneBoratedRefl[1] = 0.10;

        // Zero for no other reason than it's black... yeah, I went there
        pvcRefl = new G4double[NUM_PP_ConstProp];
        pvcRefl[0] = pvcRefl[1] = 0.0;
	
	// The index of refraction of quartz agrees with Claudio Silva's (LIP-Coimbra)
	// report "Optical constants of some materials used in the LUX detector" @178nm
	quartzRefractiveIndex = new G4double[NUM_PP];
	for( G4int i=0; i<NUM_PP; i++ ) //room temperature, but dn/dT is very small
	  quartzRefractiveIndex[i] = leadGlassRefractiveIndex[i] - 0.15;
	quartzAbsorption = new G4double[NUM_PP];
	quartzAbsorption[0] =     1*m;
        quartzAbsorption[1] = 0.08*cm;
	quartzAbsorption[2] = 1.21*cm;
	quartzAbsorption[3] = 1.35*cm;
	quartzAbsorption[4] = 1.51*cm;
	quartzAbsorption[5] = 3.35*cm;
	quartzAbsorption[6] = 7.98*cm;
	quartzAbsorption[7] = 11.3*cm;
	quartzAbsorption[8] = 13.2*cm;
	quartzAbsorption[9] = 15.8*cm;
       quartzAbsorption[10] = 17.7*cm;
       quartzAbsorption[11] = 18.6*cm;
       quartzAbsorption[12] = 19.3*cm;
       quartzAbsorption[13] = 20.5*cm;
       quartzAbsorption[14] = 21.5*cm;
       quartzAbsorption[15] = 22.1*cm;
       quartzAbsorption[16] = 22.8*cm;
       quartzAbsorption[17] = 23.8*cm;
       quartzAbsorption[18] = 25.1*cm;
       quartzAbsorption[19] = 25.8*cm;
       quartzAbsorption[20] = 25.9*cm;
       quartzAbsorption[21] = 26.3*cm;
       quartzAbsorption[22] = 26.7*cm;
	
	rockRefl = new G4double[NUM_PP_ConstProp];
	rockRefl[0] = rockRefl[1] = 0;
	
	//	Optical parameters for sapphire are (for now at least) taken to be the
	//	same as quartz
	sapphireRefractiveIndex = new G4double[NUM_PP];
	for( G4int i=0; i<NUM_PP; i++ )
		sapphireRefractiveIndex[i] = quartzRefractiveIndex[i];
	sapphireAbsorption = new G4double[NUM_PP_ConstProp];
	sapphireAbsorption[0] = 1.*m; sapphireAbsorption[1] = 1./3*m;
	
	teflonRefractiveIndex = new G4double[NUM_PP];
	for( G4int i=0; i<NUM_PP; i++ )
          teflonRefractiveIndex[i] = 1.4536+1.3744/photonWavelengths[i]+5926.5/pow(photonWavelengths[i],2.)-2.1066e6/pow(photonWavelengths[i],3.)+2.5863e8/pow(photonWavelengths[i],4.);
        //http://teacher.pas.rochester.edu:8080/wiki/pub/Lux/LuxMaterial46/LUX_PTFE_Reflectance_InternalNote.pdf says n=1.53 on average for PTFE @177nm
	//Used http://www.lrsm.upenn.edu/~frenchrh/download/0807JM3OptPropTeflonAF.pdf to estimate the wavelength dependence. Fit data to Cauchy's formula
	
	// Taken from the steelRefl
	ss316Refl = new G4double[NUM_PP_ConstProp];
	ss316Refl[0] = ss316Refl[1] = 0.1;
	
	steelRefl = new G4double[NUM_PP_ConstProp];
	steelRefl[0] = steelRefl[1] = 0.1; //ansatz. Maybe much higher.
	
	teflonRefl = new G4double[NUM_PP_ConstProp];
	teflonRefl[0] = teflonRefl[1] = 0.98; //this is the reflectivity for 
	//surfaces other than LXe or GXe, which are set separately below
	
	titaniumRefl = new G4double[NUM_PP_ConstProp];
	titaniumRefl[0] = titaniumRefl[1] = 0.1;
	
	//	TPB spectra come from a file I got from Kostas Mavrokoridis at
	//	Liverpool. I had to force them to span the full range of wavelengths
	//	defined in this file.
	G4double tmpTPBAbsEn[] = { 0.602391363477914, 3.06133803533393, 
			3.07319513634028, 3.08941499610084, 3.10563473187722,
			3.12185459163779, 3.13807420342997, 3.15429418717473,
			3.1705140469353, 3.18673365872749, 3.20295327051967,
			3.21917325426443, 3.235393114025, 3.25161272581718,
			3.26783270956194, 3.28405256932251, 3.3002721811147,
			3.31649179290688, 3.33206495113016, 3.34821922325399,
			3.36920639912082, 3.3854261348972, 3.40164574668939,
			3.41786535848157, 3.43408534222633, 3.4503052019869,
			3.46652481377908, 3.48274467353965, 3.49896465728441,
			3.5151842690766, 3.53140388086878, 3.54762386461354,
			3.56384372437411, 3.5800633361663, 3.59628319592686,
			3.61250317967162, 3.62872279146381, 3.64494240325599,
			3.66116238700075, 3.67738224676132, 3.69360185855351,
			3.70982147034569, 3.72604145409045, 3.74226131385102,
			3.7584809256432, 3.77470090938796, 3.79092076914853,
			3.80714038094072, 3.8233599927329, 3.83957972850928,
			3.85579958826985, 3.87201944803041, 3.88823918380679,
			3.90445904356736, 3.92067890332793, 3.93689851512011,
			3.95311849886487, 3.96933835862544, 3.98555797041763,
			3.99772280324596, 4.01394266300652, 4.03016227479871,
			4.04638213455928, 4.06260187033565, 4.07882173009622,
			4.09504183782517, 4.11126144961736, 4.12748118539373,
			4.14370079718592, 4.15992040897811, 4.17614014475448,
			4.19235975654667, 4.20857986427562, 4.22479997200457,
			4.24101970778094, 4.25723931957313, 4.27345893136532,
			4.28967866714169, 4.30589877487064, 4.32211838666283,
			4.33833849439178, 4.35455823016815, 4.37077784196034,
			4.38699745375253, 4.40321718952891, 4.41943680132109,
			9.68626487742377 };
	G4double tpbMolarExtinction[] = { 0, 0, 3.051, 158.318, 251.477, 344.637,
			593.063,
			996.755, 1524.659, 2176.777, 3015.214, 3946.811, 5157.886, 6803.707,
			8480.581, 10405.880, 12548.553, 14598.066, 16577.320, 18556.701,
			21119.242, 22827.170, 24224.564, 25621.959, 27205.674, 28478.855,
			29689.932, 31180.486, 32484.721, 33633.688, 34441.070, 35217.402,
			35683.199, 36024.789, 36055.836, 35931.629, 35652.148, 35248.457,
			34720.551, 34161.598, 33602.637, 32950.520, 32236.295, 31273.645,
			30217.836, 29006.758, 27857.789, 26677.766, 25559.852, 24441.936,
			23448.232, 22392.424, 21336.615, 20280.805, 19162.889, 18076.027,
			17113.375, 16181.778, 15188.077, 14411.746, 13573.308, 12703.817,
			11927.488, 11120.104, 10561.146, 9877.976, 9381.124, 8884.272,
			8294.262, 7828.463, 7393.718, 6927.919, 6555.281, 6244.749,
			5965.270, 5623.684, 5406.312, 5126.833, 4940.514, 4754.194,
			4629.981, 4443.662, 4319.449, 4226.290, 4195.236, 4133.129,
			4100.0 };
	
	num_tpbAbs = sizeof( tmpTPBAbsEn ) / sizeof( G4double );
	tpbAbsorptionEnergies = new G4double[num_tpbAbs];
	tpbAbsorption = new G4double[num_tpbAbs];
	G4double concentration = 1.079e6;		//	mg/L
	G4double molecularWeight = 358.475e3;	//	mg/mol
	concentration /= molecularWeight; 
	for( G4int i=0; i<num_tpbAbs; i++ ) {
		tpbAbsorptionEnergies[i] = tmpTPBAbsEn[i]*eV;
		tpbAbsorption[i] = ( 1. /
				( log(10)*tpbMolarExtinction[i]*concentration ) )*cm;
	}
	
	G4double tmpTPBEmiEn[] = { 0.602391363477914, 2.08376790640377,
			2.08378852632909,
			2.10000838608965, 2.11622799788184, 2.1324479816266,
			2.14866759341879, 2.16488745317935, 2.18110706497154,
			2.1973270487163, 2.21354666050848, 2.22976652026905,
			2.24598625604543, 2.262206115806, 2.27842597556656,
			2.29464558735875, 2.31086557110351, 2.32708518289569,
			2.34330504265626, 2.35952477843264, 2.37574463819321,
			2.39196424998539, 2.40818410974596, 2.42440384552234,
			2.4406237052829, 2.45684356504347, 2.47306330081985,
			2.48928316058042, 2.5055027723726, 2.52172263213317,
			2.53794236790955, 2.55416222767012, 2.57038208743068,
			2.58660182320706, 2.60282143499925, 2.61904129475981,
			2.63526115452038, 2.65148089029676, 2.66770075005733,
			2.68392036184951, 2.70014034559427, 2.71635995738646,
			2.73257981714703, 2.74879967690759, 2.76501941268397,
			2.78123902447616, 2.79745888423672, 2.81367886798148,
			2.82989847977367, 2.84611833953424, 2.86233795132642,
			2.87855793507118, 2.89477754686337, 2.91099740662393,
			2.92721714240031, 2.94343700216088, 2.95965661395307,
			2.97587647371363, 2.99209645745839, 3.00831606925058,
			3.02453568104276, 3.04075566478752, 3.05697552454809,
			3.07319513634028, 3.08941499610084, 3.10563473187722,
			3.12185459163779, 3.13807420342997, 3.15429418717473,
			3.1705140469353, 3.18673365872749, 3.20295327051967,
			3.21917325426443, 3.22036858262401, 9.68626487742377 };
	G4double tmpTPBEmi[] = { 0, 0, 0.085, 0.102, 0.120, 0.138, 0.155, 0.173,
			0.188,
			0.205, 0.225, 0.245, 0.262, 0.280, 0.301, 0.329, 0.364, 0.395,
			0.431, 0.482, 0.517, 0.556, 0.593, 0.629, 0.662, 0.692, 0.715,
			0.744, 0.783, 0.817, 0.852, 0.883, 0.899, 0.923, 0.942, 0.961,
			0.984, 0.990, 0.996, 0.996, 0.994, 0.990, 0.984, 0.969, 0.950,
			0.928, 0.902, 0.869, 0.840, 0.801, 0.764, 0.719, 0.676, 0.633,
			0.587, 0.548, 0.507, 0.453, 0.412, 0.368, 0.321, 0.284, 0.249,
			0.210, 0.179, 0.151, 0.122, 0.091, 0.071, 0.053, 0.039, 0.027,
			0.017, 0, 0 };

	num_tpbEmi = sizeof( tmpTPBEmiEn ) / sizeof( G4double );
	tpbEmissionEnergies = new G4double[num_tpbAbs];
	tpbEmission = new G4double[num_tpbEmi];
	for( G4int i=0; i<num_tpbEmi; i++ ) {
		tpbEmissionEnergies[i] = tmpTPBEmiEn[i]*eV;
		tpbEmission[i] = tmpTPBEmi[i];
	}

	tungstenRefl = new G4double[NUM_PP_ConstProp];
	tungstenRefl[0] = tungstenRefl[1] = 0.1;
	
	//	Water code taken from Kareem's NeutronDetector simulation code
	//	53 entries creates wavelengths from 200 to 720 nm in 10 nm steps, and
	//	the first is set to the first and last elements of the photonEnergies
	//	array.
	num_water = 55;
	const G4int nWaterEntries = num_water;
	G4double wavelength;
	waterPhotonEnergies = new G4double[nWaterEntries];
	waterRefractiveIndex = new G4double[nWaterEntries];
	for( G4int i=0; i<nWaterEntries; i++ ) {
		wavelength = 190. + 10.*(G4double)i;	//	This is the wavelength in nm
		waterPhotonEnergies[i] =
				(4.13566743E-15 * constC / (wavelength*1.E-9))*eV;
		if( i==0 ) waterPhotonEnergies[i] = photonEnergies[0];
		if( i==(nWaterEntries-1) ) waterPhotonEnergies[i] =
				photonEnergies[NUM_PP-1];

		//	The equation for the refractive index is evaluated by D. T. Huibers,
		//	"Models for the wavelength dependence of the index of refraction
		//	of water", Applied Optics 36 (1997) p.3785. The original equation
		//	comes from X. Qua and E. S. Fry, "Empirical equation for the index
		//	of refraction of seawater", Applied Optics 34 (1995) p.3477.
		waterRefractiveIndex[i] = 1.31279 + 15.762/wavelength
				- 4382./(pow(wavelength,2)) + 1.1455E6/(pow(wavelength,3));
	}
	//	The absorption distances from from several references -- 
	//	200 - 320 nm:	T. I. Quickenden & J. A. Irvin, "The ultraviolet
	//					absorption spectrum of liquid water", J. Chem. Phys.
	//					72(8) (1980) p4416.
	//	330 nm:			A rough average between 320 and 340 nm. Very subjective.
	//	340 - 370 nm:	F. M. Sogandares and E. S. Fry,  "Absorption
	//					spectrum (340 - 640 nm) of pure water. I. Photothermal
	//					measurements", Applied Optics 36 (1997) p.8699.
	//	380 - 720 nm:	R. M. Pope and E. S. Fry, "Absorption spectrum (380 - 
	//					700 nm) of pure water. II. Integrating cavity
	//					measurements", Applied Optics 36 (1997) p.8710.
	//	The first and last points are wild guesses based on a by-eye
	//	extrapolationof the curve from 200-320 nm.
	waterAbsorption = new G4double[nWaterEntries];
	waterAbsorption[0] = 0*m;
	waterAbsorption[1] = 3.086419753*m;
	waterAbsorption[2] = 7.936507937*m;
	waterAbsorption[3] = 12.42236025*m;
	waterAbsorption[4] = 16.80672269*m;
	waterAbsorption[5] = 20.70393375*m;
	waterAbsorption[6] = 26.59574468*m;
	waterAbsorption[7] = 32.46753247*m;
	waterAbsorption[8] = 42.37288136*m;
	waterAbsorption[9] = 45.04504505*m;
	waterAbsorption[10] = 61.34969325*m;
	waterAbsorption[11] = 80.64516129*m;
	waterAbsorption[12] = 89.28571429*m;
	waterAbsorption[13] = 100.*m;
	waterAbsorption[14] = 50.*m;
	waterAbsorption[15] = 30.76923077*m;
	waterAbsorption[16] = 49.01960784*m;
	waterAbsorption[17] = 64.1025641*m;
	waterAbsorption[18] = 87.71929825*m;
	waterAbsorption[19] = 87.95074758*m;
	waterAbsorption[20] = 117.5088132*m;
	waterAbsorption[21] = 150.8295626*m;
	waterAbsorption[22] = 211.4164905*m;
	waterAbsorption[23] = 220.2643172*m;
	waterAbsorption[24] = 202.020202*m;
	waterAbsorption[25] = 157.480315*m;
	waterAbsorption[26] = 108.4598698*m;
	waterAbsorption[27] = 102.145046*m;
	waterAbsorption[28] = 94.33962264*m;
	waterAbsorption[29] = 78.74015748*m; 
	waterAbsorption[30] = 66.66666667*m;
	waterAbsorption[31] = 49.01960784*m;
	waterAbsorption[32] = 30.76923077*m;
	waterAbsorption[33] = 24.44987775*m;
	waterAbsorption[34] = 23.04147465*m;
	waterAbsorption[35] = 21.09704641*m;
	waterAbsorption[36] = 17.69911504*m;
	waterAbsorption[37] = 16.15508885*m;
	waterAbsorption[38] = 14.38848921*m;
	waterAbsorption[39] = 11.16071429*m;
	waterAbsorption[40] = 7.4019245*m;
	waterAbsorption[41] = 4.496402878*m;
	waterAbsorption[42] = 3.78214826*m;
	waterAbsorption[43] = 3.629764065*m;
	waterAbsorption[44] = 3.429355281*m;
	waterAbsorption[45] = 3.217503218*m;
	waterAbsorption[46] = 2.941176471*m;
	waterAbsorption[47] = 2.43902439*m;
	waterAbsorption[48] = 2.277904328*m;
	waterAbsorption[49] = 2.150537634*m;
	waterAbsorption[50] = 1.937984496*m;
	waterAbsorption[51] = 1.602564103*m;
	waterAbsorption[52] = 1.209189843*m;
	waterAbsorption[53] = 0.812347685*m;
	waterAbsorption[54] = 0*m;
	
	halonRefl = new G4double[nWaterEntries];
	for( G4int i=0; i<nWaterEntries; i++ )
		halonRefl[i] = 0.94;

}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					CreateMaterials()
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccMaterials::CreateMaterials()
{
	//
	//	Isotopes
	//	Atomic weights come from webelements.com
	//
	G4Isotope *H1 = new G4Isotope( "H1", 1, 1, 1.007825035*g/mole );
	G4Isotope *H2 = new G4Isotope( "H2", 1, 2, 2.014101779*g/mole );
	
	G4Isotope *Li6 = new G4Isotope( "Li6", 3, 6, 6.0151223*g/mole );
	G4Isotope *Li7 = new G4Isotope( "Li7", 3, 7, 7.0160040*g/mole );
	
	G4Isotope *Be9 = new G4Isotope( "Be9", 4, 9, 9.012182*g/mole );

	G4Isotope *B10 = new G4Isotope( "B10", 5, 10, 10.012936992*g/mole );
	G4Isotope *B11 = new G4Isotope( "B11", 5, 11, 11.009305406*g/mole );
	
	G4Isotope *C12 = new G4Isotope( "C12", 6, 12, 12.*g/mole );
	G4Isotope *C13 = new G4Isotope( "C13", 6, 13, 13.003354826*g/mole );
	
	G4Isotope *N14 = new G4Isotope( "N14", 7, 14, 14.00307400478*g/mole );
	G4Isotope *N15 = new G4Isotope( "N15", 7, 15, 15.00010889823*g/mole );
	
	G4Isotope *O16 = new G4Isotope( "O16", 8, 16, 15.99491463*g/mole );
	G4Isotope *O17 = new G4Isotope( "O17", 8, 17, 16.9991312*g/mole );
	G4Isotope *O18 = new G4Isotope( "O18", 8, 18, 17.9991603*g/mole );
	
	G4Isotope *F19 = new G4Isotope( "F19", 9, 19, 18.99840322*g/mole );
	
	G4Isotope *Na23 = new G4Isotope( "Na23", 11, 23, 22.9897677*g/mole );

	G4Isotope *Mg24 = new G4Isotope( "Mg24", 12, 24, 23.9850417*g/mole );
	G4Isotope *Mg25 = new G4Isotope( "Mg25", 12, 25, 24.9858369*g/mole );
	G4Isotope *Mg26 = new G4Isotope( "Mg26", 12, 26, 25.9825929*g/mole );	
	
	G4Isotope *Al27 = new G4Isotope( "Al27", 13, 27, 26.9815386*g/mole );
	
	G4Isotope *S32 = new G4Isotope( "S32", 16, 32, 31.97207070*g/mole );
	G4Isotope *S33 = new G4Isotope( "S33", 16, 33, 32.97145843*g/mole );
	G4Isotope *S34 = new G4Isotope( "S34", 16, 34, 33.96786665*g/mole );
	G4Isotope *S36 = new G4Isotope( "S36", 16, 36, 35.96708062*g/mole );
	
	G4Isotope *Cl35 = new G4Isotope( "Cl35", 17, 35, 34.968852721*g/mole );
	G4Isotope *Cl37 = new G4Isotope( "Cl37", 17, 37, 36.96590262*g/mole );

	G4Isotope *Ar36 = new G4Isotope( "Ar36", 18, 36, 35.96754552*g/mole );
	G4Isotope *Ar38 = new G4Isotope( "Ar38", 18, 38, 37.9627325 *g/mole );
	G4Isotope *Ar40 = new G4Isotope( "Ar40", 18, 40, 39.9623837 *g/mole );
	
	G4Isotope *Ti46 = new G4Isotope( "Ti46", 22, 46, 45.9526294*g/mole );
	G4Isotope *Ti47 = new G4Isotope( "Ti47", 22, 47, 46.9517640*g/mole );
	G4Isotope *Ti48 = new G4Isotope( "Ti48", 22, 48, 47.9479473*g/mole );
	G4Isotope *Ti49 = new G4Isotope( "Ti49", 22, 49, 48.9478711*g/mole );
	G4Isotope *Ti50 = new G4Isotope( "Ti50", 22, 50, 49.9447921*g/mole );
	
	G4Isotope *Cr50 = new G4Isotope( "Cr50", 24, 50, 49.9460464*g/mole );
	G4Isotope *Cr52 = new G4Isotope( "Cr52", 24, 52, 51.9405098*g/mole );
	G4Isotope *Cr53 = new G4Isotope( "Cr53", 24, 53, 52.9406513*g/mole );
	G4Isotope *Cr54 = new G4Isotope( "Cr54", 24, 54, 53.9388825*g/mole );
	
	G4Isotope *Fe54 = new G4Isotope( "Fe54", 26, 54, 53.9396127*g/mole );
	G4Isotope *Fe56 = new G4Isotope( "Fe56", 26, 56, 55.9349393*g/mole );
	G4Isotope *Fe57 = new G4Isotope( "Fe57", 26, 57, 56.9353958*g/mole );
	G4Isotope *Fe58 = new G4Isotope( "Fe58", 26, 58, 57.9332773*g/mole );
	
	G4Isotope *Ni58 = new G4Isotope ("Ni58", 28, 58, 57.9353429*g/mole );
	G4Isotope *Ni60 = new G4Isotope ("Ni60", 28, 60, 59.9307863*g/mole );
	G4Isotope *Ni61 = new G4Isotope ("Ni61", 28, 61, 60.9310560*g/mole );
	G4Isotope *Ni62 = new G4Isotope ("Ni62", 28, 62, 61.9283451*g/mole );
	G4Isotope *Ni64 = new G4Isotope ("Ni64", 28, 64, 63.9279659*g/mole );
	
	G4Isotope *Cu63 = new G4Isotope( "Cu63", 29, 63, 62.92959898*g/mole );
	G4Isotope *Cu65 = new G4Isotope( "Cu65", 29, 65, 64.9277929*g/mole );

	G4Isotope *Si28 = new G4Isotope( "Si28", 14, 28, 28.0 * g/mole );
	G4Isotope *Si29 = new G4Isotope( "Si29", 14, 29, 29.0 * g/mole );
	G4Isotope *Si30 = new G4Isotope( "Si30", 14, 30, 30.0 * g/mole );
	
	G4Isotope *Zn64 = new G4Isotope( "Zn64", 30, 64, 63.9291448*g/mole );
	G4Isotope *Zn66 = new G4Isotope( "Zn66", 30, 66, 65.9260347*g/mole );
	G4Isotope *Zn67 = new G4Isotope( "Zn67", 30, 67, 66.9271291*g/mole );
	G4Isotope *Zn68 = new G4Isotope( "Zn68", 30, 68, 67.9248459*g/mole );
	G4Isotope *Zn70 = new G4Isotope( "Zn70", 30, 70, 69.925325*g/mole );

	G4Isotope *Mo92 = new G4Isotope( "Mo92", 42, 92, 91.906809*g/mole );
	G4Isotope *Mo94 = new G4Isotope( "Mo94", 42, 94, 93.9050853*g/mole );
	G4Isotope *Mo95 = new G4Isotope( "Mo95", 42, 95, 94.9058411*g/mole );
	G4Isotope *Mo96 = new G4Isotope( "Mo96", 42, 96, 95.9046785*g/mole );
	G4Isotope *Mo97 = new G4Isotope( "Mo97", 42, 97, 96.9060205*g/mole );
	G4Isotope *Mo98 = new G4Isotope( "Mo98", 42, 98, 97.9054073*g/mole );
	G4Isotope *Mo100 = new G4Isotope( "Mo100", 42, 100, 99.907477*g/mole );
	
	G4Isotope *Xe124 = new G4Isotope( "Xe124", 54, 124, 123.9058942 *g/mole );
	G4Isotope *Xe126 = new G4Isotope( "Xe126", 54, 126, 125.904281 *g/mole );
	G4Isotope *Xe128 = new G4Isotope( "Xe128", 54, 128, 127.9035312 *g/mole );
	G4Isotope *Xe129 = new G4Isotope( "Xe129", 54, 129, 128.9047801 *g/mole );
	G4Isotope *Xe130 = new G4Isotope( "Xe130", 54, 130, 129.9035094 *g/mole );
	G4Isotope *Xe131 = new G4Isotope( "Xe131", 54, 131, 130.905072 *g/mole );
	G4Isotope *Xe132 = new G4Isotope( "Xe132", 54, 132, 131.904144 *g/mole );
	G4Isotope *Xe134 = new G4Isotope( "Xe134", 54, 134, 133.905395 *g/mole );
	G4Isotope *Xe136 = new G4Isotope( "Xe136", 54, 136, 135.907214 *g/mole );

	G4Isotope *Ce136 = new G4Isotope( "Ce136", 58, 136, 135.907172*g/mole );
	G4Isotope *Ce138 = new G4Isotope( "Ce138", 58, 138, 137.905991*g/mole );
	G4Isotope *Ce140 = new G4Isotope( "Ce140", 58, 140, 139.905438*g/mole );
	G4Isotope *Ce142 = new G4Isotope( "Ce142", 58, 142, 141.909244*g/mole );
	
	G4Isotope *W180 = new G4Isotope( "W180", 74, 180, 179.946701*g/mole );
	G4Isotope *W182 = new G4Isotope( "W182", 74, 182, 181.948202*g/mole );
	G4Isotope *W183 = new G4Isotope( "W183", 74, 183, 182.950220*g/mole );
	G4Isotope *W184 = new G4Isotope( "W184", 74, 184, 183.950928*g/mole );
	G4Isotope *W186 = new G4Isotope( "W186", 74, 186, 185.954357*g/mole );
	
	G4Isotope *Au197 = new G4Isotope( "Au197", 79, 197, 196.966543*g/mole );
	
	G4Isotope *Pb204 = new G4Isotope( "Pb204", 82, 204, 203.973020*g/mole );
	G4Isotope *Pb206 = new G4Isotope( "Pb206", 82, 206, 205.974440*g/mole );
	G4Isotope *Pb207 = new G4Isotope( "Pb207", 82, 207, 206.975872*g/mole );
	G4Isotope *Pb208 = new G4Isotope( "Pb208", 82, 208, 207.976627*g/mole );
	
	G4Isotope *Gd152 = new G4Isotope( "Gd152", 64, 152, 151.919786*g/mole );
	G4Isotope *Gd154 = new G4Isotope( "Gd154", 64, 154, 153.920861*g/mole );
	G4Isotope *Gd155 = new G4Isotope( "Gd155", 64, 155, 154.922618*g/mole );
	G4Isotope *Gd156 = new G4Isotope( "Gd156", 64, 156, 155.922118*g/mole );
	G4Isotope *Gd157 = new G4Isotope( "Gd157", 64, 157, 156.923956*g/mole );
	G4Isotope *Gd158 = new G4Isotope( "Gd158", 64, 158, 157.924019*g/mole );
	G4Isotope *Gd160 = new G4Isotope( "Gd160", 64, 160, 159.927049*g/mole );
	
	//
	//	Elements
	//
	G4Element *natH = new G4Element( "Natural H", "natH", 2 );
	natH->AddIsotope( H1, 99.9885*perCent );
	natH->AddIsotope( H2, 0.0115*perCent );
	
	G4Element *natLi = new G4Element( "Natural Li", "natLi", 2 );
	natLi->AddIsotope( Li6, 7.59*perCent );
	natLi->AddIsotope( Li7, 92.41*perCent );

	G4Element *enrLi = new G4Element( "Enriched Li", "enrLi", 2 );
	enrLi->AddIsotope( Li6, 95.00*perCent );
	enrLi->AddIsotope( Li7, 5.00*perCent );
	
	G4Element *natB = new G4Element( "Natural B", "natB", 2 );
	natB->AddIsotope( B10, 19.8*perCent );
	natB->AddIsotope( B11, 80.2*perCent );
	
	G4Element *natBe = new G4Element( "Natural Be", "natBe", 1 );
	natBe->AddIsotope( Be9, 100*perCent );
	
	G4Element *natC = new G4Element( "Natural C", "natC", 2 );
	natC->AddIsotope( C12, 98.93*perCent );
	natC->AddIsotope( C13, 1.07*perCent );
	
	G4Element *natN = new G4Element( "Natural N", "natN", 2 );
	natN->AddIsotope( N14, 99.632*perCent );
	natN->AddIsotope( N15, 0.368*perCent );
	
	G4Element *natO = new G4Element( "Natural O", "natO", 3 );
	natO->AddIsotope( O16, 99.757*perCent );
	natO->AddIsotope( O17, 0.038*perCent );
	natO->AddIsotope( O18, 0.205*perCent );
	
	G4Element *natF = new G4Element( "Natural F", "natF", 1 );
	natF->AddIsotope( F19, 100.*perCent );
	
	G4Element *natNa = new G4Element( "Natural Na", "natNa", 1 );
	natNa->AddIsotope( Na23, 100.*perCent );

	G4Element *natMg = new G4Element( "Natural Mg", "natMg", 3 );
	natMg->AddIsotope( Mg24, 78.99*perCent );
	natMg->AddIsotope( Mg25, 10.00*perCent );
	natMg->AddIsotope( Mg26, 11.01*perCent );
	
	G4Element *natAl = new G4Element( "Natural Al", "natAl", 1 );
	natAl->AddIsotope( Al27, 100.*perCent );
	
	G4Element *natSi = new G4Element( "Natural Si", "natSi", 3 );
	natSi->AddIsotope( Si28, 92.2297*perCent );
	natSi->AddIsotope( Si29, 4.6832*perCent );
	natSi->AddIsotope( Si30, 3.0872*perCent );
	
	G4Element *natS = new G4Element( "Natural S", "natS", 4 );
	natS->AddIsotope( S32, 94.93*perCent );
	natS->AddIsotope( S33, 0.76*perCent );
	natS->AddIsotope( S34, 4.29*perCent );
	natS->AddIsotope( S36, 0.02*perCent );
	
	G4Element *natCl = new G4Element( "Natural Cl", "natCl", 2 );
	natCl->AddIsotope( Cl35, 75.78*perCent );
	natCl->AddIsotope( Cl37, 24.22*perCent );

	G4Element *natAr = new G4Element( "Natural Ar", "natAr", 3 );
	natAr->AddIsotope( Ar36, 0.3365*perCent );
	natAr->AddIsotope( Ar38, 0.0632*perCent );
	natAr->AddIsotope( Ar40, 99.6003*perCent );
	
	G4Element *natTi = new G4Element( "Natural Ti", "natTi", 5 );
	natTi->AddIsotope( Ti46, 8.25*perCent );
	natTi->AddIsotope( Ti47, 7.44*perCent );
	natTi->AddIsotope( Ti48, 73.72*perCent );
	natTi->AddIsotope( Ti49, 5.41*perCent );
	natTi->AddIsotope( Ti50, 5.18*perCent );
	
	G4Element *natCr = new G4Element( "Natural Cr", "natCr", 4 );
	natCr->AddIsotope( Cr50, 4.345*perCent );
	natCr->AddIsotope( Cr52, 83.789*perCent );
	natCr->AddIsotope( Cr53, 9.501*perCent );
	natCr->AddIsotope( Cr54, 2.365*perCent );
	
	G4Element *natFe = new G4Element( "Natural Fe", "natFe", 4 );
	natFe->AddIsotope( Fe54, 5.845*perCent );
	natFe->AddIsotope( Fe56, 91.754*perCent );
	natFe->AddIsotope( Fe57, 2.119*perCent );
	natFe->AddIsotope( Fe58, 0.282*perCent );
	
	G4Element *natNi = new G4Element( "Natural Ni", "natNi", 5 );
	natNi->AddIsotope( Ni58, 68.077*perCent );
	natNi->AddIsotope( Ni60, 26.223*perCent );
	natNi->AddIsotope( Ni61, 1.14*perCent );
	natNi->AddIsotope( Ni62, 3.634*perCent );
	natNi->AddIsotope( Ni64, 0.926*perCent );
	
	G4Element *natCu = new G4Element( "Natural Cu", "natCu", 2 );
	natCu->AddIsotope( Cu63, 69.17*perCent );
	natCu->AddIsotope( Cu65, 30.83*perCent );

	G4Element *natZn = new G4Element( "Natural Zn", "natZn", 5 );
	natZn->AddIsotope( Zn64, 48.63*perCent );
	natZn->AddIsotope( Zn66, 27.90*perCent );
	natZn->AddIsotope( Zn67, 4.10*perCent );
	natZn->AddIsotope( Zn68, 18.75*perCent );
	natZn->AddIsotope( Zn70, 0.62*perCent );
	
	G4Element *natMo = new G4Element( "Natural Mo", "natMo", 7 );
	natMo->AddIsotope( Mo92, 14.84*perCent );
	natMo->AddIsotope( Mo94, 9.25*perCent );
	natMo->AddIsotope( Mo95, 15.92*perCent );
	natMo->AddIsotope( Mo96, 16.68*perCent );
	natMo->AddIsotope( Mo97, 9.55*perCent );
	natMo->AddIsotope( Mo98, 24.13*perCent );
	natMo->AddIsotope( Mo100, 9.63*perCent );
	
	G4Element *natXe = new G4Element( "Natural Xe", "natXe", 9 );
	natXe->AddIsotope( Xe124, 0.09*perCent );
	natXe->AddIsotope( Xe126, 0.09*perCent );
	natXe->AddIsotope( Xe128, 1.92*perCent );
	natXe->AddIsotope( Xe129, 26.44*perCent );
	natXe->AddIsotope( Xe130, 4.08*perCent );
	natXe->AddIsotope( Xe131, 21.18*perCent );
	natXe->AddIsotope( Xe132, 26.89*perCent );
	natXe->AddIsotope( Xe134, 10.44*perCent );
	natXe->AddIsotope( Xe136, 8.87*perCent );
	
	G4Element *natCe = new G4Element( "Natural Ce", "natCe", 4 );
	natCe->AddIsotope( Ce136, 0.185*perCent );
	natCe->AddIsotope( Ce138, 0.251*perCent );
	natCe->AddIsotope( Ce140, 88.45*perCent );
	natCe->AddIsotope( Ce142, 11.114*perCent );
	
	G4Element *natW = new G4Element( "Natural W", "natW", 5 );
	natW->AddIsotope( W180, 0.12*perCent );
	natW->AddIsotope( W182, 26.50*perCent );
	natW->AddIsotope( W183, 14.31*perCent );
	natW->AddIsotope( W184, 30.64*perCent );
	natW->AddIsotope( W186, 28.43*perCent );
	
	G4Element *natAu = new G4Element( "Natural Au", "natAu", 1 );
	natAu->AddIsotope( Au197, 100.*perCent );
	
	G4Element *natPb = new G4Element( "Natural lead", "natPb", 4 );
	natPb->AddIsotope( Pb204, 1.4*perCent );
	natPb->AddIsotope( Pb206, 24.1*perCent );
	natPb->AddIsotope( Pb207, 22.1*perCent );
	natPb->AddIsotope( Pb208, 52.4*perCent );
	
	G4Element *natGd = new G4Element( "Natural Gd", "natGd", 7 );
	natGd->AddIsotope( Gd152, 0.20*perCent );
	natGd->AddIsotope( Gd154, 2.18*perCent );
	natGd->AddIsotope( Gd155, 14.80*perCent );
	natGd->AddIsotope( Gd156, 20.47*perCent );
	natGd->AddIsotope( Gd157, 15.65*perCent );
	natGd->AddIsotope( Gd158, 24.84*perCent );
	natGd->AddIsotope( Gd160, 21.86*perCent );	

	//
	//	Materials
	//
	
	// Assuming PMMA -- see
	//	http://en.wikipedia.org/wiki/Poly(methyl_methacrylate)
	acrylic = new G4Material( "acrylic", 1.17*g/cm3, 3 );
	acrylic->AddElement( natC, 5 );
	acrylic->AddElement( natO, 2 );
	acrylic->AddElement( natH, 8 );
	
	//	This composition for air comes from Wikipedia. Note that this assumes
	//	no water content.
	air = new G4Material( "air", 0.0012*g/cm3, 3 );
	air->AddElement( natO, 20.946*perCent );
	air->AddElement( natN, 78.12*perCent );
	air->AddElement( natAr, 0.9340*perCent );
	
	aluminum = new G4Material( "aluminum", 2.7*g/cm3, 1 );
	aluminum->AddElement( natAl, 1 );
	
	beryllium = new G4Material( "beryllium", 1.85*g/cm3, 1 );
	beryllium->AddElement( natBe, 1 );

	// using Cu density
	berylliumCopper = new G4Material( "berylliumCopper", 8.920*g/cm3, 2 );
	berylliumCopper->AddElement( natBe, 1 );
	berylliumCopper->AddElement( natCu, 1 );
	
	//	Blackium is defined as a vacuum, so that even on a particle's first step
	//	inside a part made of blackium, it's unlikely to interact.
	blackium = new G4Material( "blackium", 1., 1.008*g/mole, 1.e-25*g/cm3,
			kStateGas, LXETEMPERATURE, 3.8e-18*pascal );
	
	copper = new G4Material( "copper", 8.920*g/cm3, 1 );
	copper->AddElement( natCu, 1 );

	silicon = new G4Material( "silicon", 2.33 * g/cm3, 1 );
	silicon->AddElement( natSi, 1 );
	
	gadolinium = new G4Material( "gadolinium", 157.25*g/mole, 1 );
	gadolinium->AddElement( natGd, 1 );
	
	//	For this density of the argon gas, the STP density is 1.784 g/L, but
	//	the pressure was 750 Torr and the temperature was 21.4 C.
	//	1.784 g/L * (750/760) * (273 / (273+21.4)) = 1.632 g/L
	gasAr = new G4Material( "gasAr", 0.00163255*g/cm3, 1 );
	gasAr->AddElement( natAr, 1 );
	
	gasN2 = new G4Material( "gasN2", 0.001251*g/cm3, 1 );
	gasN2->AddElement( natN, 1 );

	gasArN2 = new G4Material( "gasArN2", 9.3895e-04*g/cm3, 2 );
	gasArN2->AddMaterial( gasAr, 0.985 );
	gasArN2->AddMaterial( gasN2, 0.015 );

	gasXe = new G4Material( "gasXe", GXEDENS, 1, kStateGas, LXETEMPERATURE,
			LXEPRESSURE );
	gasXe->AddElement( natXe, 1 );
	
	gold = new G4Material( "gold", 19.3*g/cm3, 1 );
	gold->AddElement( natAu, 1 );
	
	halon = new G4Material( "halon", 2.16*g/cm3, 2 );
	halon->AddElement( natC, 1 );
	halon->AddElement( natF, 2 );

	iron = new G4Material( "iron", 7.874*g/cm3, 1 );
	iron->AddElement( natFe, 1 );
	
	isohexane = new G4Material( "isohexane", 0.653*g/cm3, 2 );
	isohexane->AddElement( natC, 6 );
	isohexane->AddElement( natH, 14 );
	
	tmb = new G4Material( "TMB", 0.932*g/cm3, 4 );
	tmb->AddElement( natC, 3 );
	tmb->AddElement( natH, 9 );
	tmb->AddElement( natB, 1 );
	tmb->AddElement( natO, 3 );
	
	//	Taking a random stab at what the density would be...
	dopedIsohexaneTMB5 = new G4Material( "dopedIsohexaneTMB5", 0.653*g/cm3, 2 );
	dopedIsohexaneTMB5->AddMaterial( isohexane, 95*perCent );
	dopedIsohexaneTMB5->AddMaterial( tmb, 5*perCent );
	
	//	Taking a random stab at what the density would be...
	dopedIsohexaneTMB50 = new G4Material( "dopedIsohexaneTMB50", 0.8*g/cm3, 2 );
	dopedIsohexaneTMB50->AddMaterial( isohexane, 50*perCent );
	dopedIsohexaneTMB50->AddMaterial( tmb, 50*perCent );
	
	dopedIsohexaneGd3 = new G4Material( "dopedIsohexaneGd3", 0.653*g/cm3, 2 );
	dopedIsohexaneGd3->AddMaterial( isohexane, 99.7*perCent );
	dopedIsohexaneGd3->AddMaterial( gadolinium, 0.3*perCent );
	
	dopedIsohexaneGd7 = new G4Material( "dopedIsohexaneGd7", 0.653*g/cm3, 2 );
	dopedIsohexaneGd7->AddMaterial( isohexane, 99.3*perCent );
	dopedIsohexaneGd7->AddMaterial( gadolinium, 0.7*perCent );
	
	kapton = new G4Material( "kapton", 1.43*g/cm3, 4);
	kapton->AddElement( natC, 22);
	kapton->AddElement( natH, 10);
	kapton->AddElement( natN, 2);
	kapton->AddElement( natO, 5);
	
	lead = new G4Material( "lead", 11.340*g/cm3, 1 );
	lead->AddElement( natPb, 1 );

	//	This definition of lead glass specifically comes from Ray-Bar
	//	Engineering Corporation.
	leadGlass = new G4Material( "leadGlass", 5.2*g/cm3, 3 );
	leadGlass->AddElement( natSi, 1 );
	leadGlass->AddElement( natO, 3 );
	leadGlass->AddElement( natPb, 1 );

	liquidAr = new G4Material( "liquidAr", 1.40*g/cm3, 1 );
	liquidAr->AddElement( natAr, 1 );

	liquidN2 = new G4Material( "liquidN2", 0.808*g/cm3, 1 );
	liquidN2->AddElement( natN, 1 );

	liquidXe = new G4Material( "liquidXe", LXEDENS, 1, kStateLiquid,
			LXETEMPERATURE, LXEPRESSURE );
	liquidXe->AddElement( natXe, 1 );
	
	mineralOil = new G4Material( "mineralOil", 0.8*g/cm3, 2 );
	mineralOil->AddElement( natC, 1 );
	mineralOil->AddElement( natH, 2 );
	
	//  PEEK polyether ether ketone
	//  http://en.wikipedia.org/wiki/PEEK
	peek = new G4Material( "peek", 1.32*g/cm3, 3);
	peek->AddElement( natC, 19);
	peek->AddElement( natO, 3);
	peek->AddElement( natH, 12);
	
	polyethylene = new G4Material( "polyethylene", 0.94*g/cm3, 2 );
	polyethylene->AddElement( natC, 1 );
	polyethylene->AddElement( natH, 2 );

	polyethyleneBorated = new G4Material( "polyethyleneBorated", 1.19*g/cm3, 3);
	polyethyleneBorated->AddElement( natB, 5.*perCent );
	polyethyleneBorated->AddElement( natC, 81.4*0.95*perCent );
	polyethyleneBorated->AddElement( natH, 18.6*0.95*perCent );

        pvc = new G4Material( "pcv", 1.375*g/cm3, 3); // ranged of desnity for rigid PVC is 1.3 to 1.45 g/cm^3, I pick the middle value
        pvc->AddElement( natC, 2);
        pvc->AddElement( natH, 3);
        pvc->AddElement( natCl, 1);
	
	quartz = new G4Material( "quartz", 2.65*g/cm3, 2, kStateSolid, LXETEMPERATURE,
			LXEPRESSURE );
	quartz->AddElement( natSi, 1 );
	quartz->AddElement( natO, 2 );
	
	rock = new G4Material( "rock", 2.4*g/cm3, 2 );
	rock->AddElement( natSi, 1 );
	rock->AddElement( natO, 2 );
	
	sapphire = new G4Material( "sapphire", 3.98*g/cm3, 2 );
	sapphire->AddElement( natAl, 2 );
	sapphire->AddElement( natO, 3 );
	
	steel = new G4Material( "steel", 8.03*g/cm3, 7 ); //AK Steel Corporation
	steel->AddElement( natC, 0.04*perCent );
	steel->AddElement( natS,0.015*perCent );
	steel->AddElement( natSi,0.37*perCent );
	steel->AddElement( natCr, 19.*perCent );
        steel->AddElement( natNi, 10.*perCent );
	steel->AddElement( natN, 0.05*perCent );
	steel->AddElement( natFe, 70.525*perCent );
	
	ss316 = new G4Material( "ss316", 7.99*g/cm3, 4 ); // From answers.com (not exactly the best source)
	ss316->AddElement( natFe, 68.5*perCent );
	ss316->AddElement( natCr, 17.*perCent );
	ss316->AddElement( natNi, 12.*perCent );
	ss316->AddElement( natMo, 2.5*perCent );
	
	teflon = new G4Material( "teflon", 2.16*g/cm3, 2 );
	teflon->AddElement( natC, 1 );
	teflon->AddElement( natF, 2 );

	titanium = new G4Material( "titanium", 4.507*g/cm3, 1 );	
	titanium->AddElement( natTi, 1 );
	
	tpb = new G4Material( "tpb", 1.079*g/cm3, 2 );
	tpb->AddElement( natH, 22 );
	tpb->AddElement( natC, 28 );
	
	tungsten = new G4Material( "tungsten", 19.250*g/cm3, 1 );
	tungsten->AddElement( natW, 1 );
	
	vacuum = new G4Material( "vacuum", 1., 1.008*g/mole, 1.e-25*g/cm3,
							kStateGas, LXETEMPERATURE, 3.8e-18*pascal );
	
	water = new G4Material( "water", 1*g/cm3, 2 );
	water->AddElement( natH, 2 );
	water->AddElement( natO, 1 );

	dopedWater3 = new G4Material( "dopedWater3", 1*g/cm3, 2);
	dopedWater3->AddMaterial( water, 99.7*perCent );
	dopedWater3->AddMaterial( gadolinium, 0.3*perCent );

	dopedWater7 = new G4Material( "dopedWater7", 1*g/cm3, 2);
	dopedWater7->AddMaterial( water, 99.3*perCent );
	dopedWater7->AddMaterial( gadolinium, 0.7*perCent );
	
	// Defining materials to be combined for enriched 6Li-doped glass
	G4Material *siO2 = new G4Material( "siO2", 2.65*g/cm3, 2);
	siO2->AddElement( natSi, 1 );
	siO2->AddElement( natO, 2 );
	
	G4Material *mgO = new G4Material( "mgO", 3.58*g/cm3, 2);
	mgO->AddElement( natMg, 1 );
	mgO->AddElement( natO, 1 );
	
	G4Material *al2O3 = new G4Material( "al2O3", 3.98*g/cm3, 2);
	al2O3->AddElement( natAl, 2 );
	al2O3->AddElement( natO, 3 );
	
	G4Material *ce2O3 = new G4Material( "ce2O3", 6.2*g/cm3, 2);
	ce2O3->AddElement( natCe, 2 );
	ce2O3->AddElement( natO, 3 );	

	// density of this may be off, but it shouldn't matter since it is
	// combined into the GS-20 and KG-2 glass
	G4Material *li2OEnriched = new G4Material( "li2OEnriched", 2.0*g/cm3, 2);
	li2OEnriched->AddElement( enrLi, 2 );
	li2OEnriched->AddElement( natO, 1 );
	
	// The accuracy of these compositions is in doubt for the time being
	gs20Glass = new G4Material( "GS20Glass", 2.5*g/cm3, 5);
	gs20Glass->AddMaterial( siO2, 56.0*perCent );
	gs20Glass->AddMaterial( mgO, 4.0*perCent );
	gs20Glass->AddMaterial( al2O3, 18.0*perCent );
	gs20Glass->AddMaterial( ce2O3, 4.0*perCent );
	gs20Glass->AddMaterial( li2OEnriched, 18.0*perCent );

	// The accuracy of these compositions is in doubt for the time being
	kg2Glass = new G4Material( "KG2Glass", 2.42*g/cm3, 3);
	kg2Glass->AddMaterial( siO2, 75.0*perCent );
	kg2Glass->AddMaterial( ce2O3, 4.6*perCent );
	kg2Glass->AddMaterial( li2OEnriched, 20.4*perCent );
	
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					SetOpticalProperties()
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccMaterials::SetOpticalProperties()
{
	//	Create material properties tables and assign values 
	//	for optical properties
	
	//	For those properties that are constant, we simply define an energy
	//	array with the largest and smallest values.
	const G4int NUM_PP = num_pp;
	const G4int NUM_PP_ConstProp = num_pp_constProp;
	const G4int nWaterEntries = num_water;
	photonEnergies_ConstProp = new G4double[NUM_PP_ConstProp];
	photonEnergies_ConstProp[0] = photonEnergies[0];
	photonEnergies_ConstProp[1] = photonEnergies[NUM_PP-1];
	
	acrylicMat = new G4MaterialPropertiesTable();
	acrylic->SetMaterialPropertiesTable( acrylicMat );
	
	airMat = new G4MaterialPropertiesTable();
	air->SetMaterialPropertiesTable( airMat );

	aluminumMat = new G4MaterialPropertiesTable();
	aluminum->SetMaterialPropertiesTable( aluminumMat );
	
	berylliumMat = new G4MaterialPropertiesTable();
	beryllium->SetMaterialPropertiesTable( berylliumMat );

	berylliumCopperMat = new G4MaterialPropertiesTable();
	berylliumCopper->SetMaterialPropertiesTable( berylliumCopperMat );

	copperMat = new G4MaterialPropertiesTable();
	copper->SetMaterialPropertiesTable( copperMat );
	
	//	The gas argon properties are set to those of air. This is a terrible
	//	approximation, but that's what we have for now.
	gasArMat = new G4MaterialPropertiesTable();
	gasAr->SetMaterialPropertiesTable( gasArMat );
	
	//	The gas argon/N2 properties are also set to those of air. This is still
	//	a terrible approximation, but that's what we have for now.
	gasArN2Mat = new G4MaterialPropertiesTable();
	gasArN2->SetMaterialPropertiesTable( gasArN2Mat );

	//	The gas nitrogen properties are set to those of air. This is a terrible
	//	approximation, but that's what we have for now.
	gasN2Mat = new G4MaterialPropertiesTable();
	gasN2->SetMaterialPropertiesTable( gasN2Mat );
	
	//	Gas Xe scintillation (S2 + small S1)
	gasXeMat = new G4MaterialPropertiesTable();
	
	//	Gas Electric Fields (all Gas is same field OR 3 different regions: pmt
	//	window to top to anode to surface)
	G4double setField = 0.; // Dummy value.  This should be set by a messenger or some other method
	gasXeMat->AddConstProperty( "ELECTRICFIELD", setField  );
	gasXeMat->AddConstProperty( "TOTALNUM_INT_SITES", -1 );
	//save all properties
	gasXe->SetMaterialPropertiesTable( gasXeMat );
	
	goldMat = new G4MaterialPropertiesTable();
	gold->SetMaterialPropertiesTable( goldMat );
	
	gs20GlassMat = new G4MaterialPropertiesTable();
	gs20Glass->SetMaterialPropertiesTable( gs20GlassMat );
	
	//*** Halon material definitions ***//
	halonMat = new G4MaterialPropertiesTable();
	G4double *halonSpeclobe;
	halonSpeclobe = new G4double[nWaterEntries];
	G4double *halonSpecspike;
	halonSpecspike = new G4double[nWaterEntries];
	G4double *halonBackscat;
	halonBackscat = new G4double[nWaterEntries];
	G4double *halonEff;
	halonEff = new G4double[nWaterEntries];
	
	for(G4int i=0; i<nWaterEntries; i++){
		halonSpeclobe[i] = 0.;
		halonSpecspike[i] = 0.;
		halonBackscat[i] = 0.;
		halonEff[i] = 1.;
	}
	
	halonMat->AddProperty( "SPECULARLOBECONSTANT", waterPhotonEnergies,
			halonSpeclobe, nWaterEntries );
	halonMat->AddProperty( "SPECULARSPIKECONSTANT", waterPhotonEnergies,
			halonSpecspike, nWaterEntries );
	halonMat->AddProperty( "BACKSCATTERCONSTANT", waterPhotonEnergies,
			halonBackscat, nWaterEntries );
	halonMat->AddProperty( "EFFICIENCY", waterPhotonEnergies, halonEff,
			nWaterEntries );
	
	halon->SetMaterialPropertiesTable( halonMat );

	ironMat = new G4MaterialPropertiesTable();
	iron->SetMaterialPropertiesTable( ironMat );
	
	isohexaneMat = new G4MaterialPropertiesTable();
	isohexaneMat->AddProperty( "RINDEX", photonEnergies_ConstProp,
			isohexaneRindex, NUM_PP_ConstProp );
	isohexane->SetMaterialPropertiesTable( isohexaneMat );
	
	kaptonMat = new G4MaterialPropertiesTable();
	kapton->SetMaterialPropertiesTable( kaptonMat );
	
	kg2GlassMat = new G4MaterialPropertiesTable();
	kg2Glass->SetMaterialPropertiesTable( kg2GlassMat );
	
	leadMat = new G4MaterialPropertiesTable();
	lead->SetMaterialPropertiesTable( leadMat );
	
	leadGlassMat = new G4MaterialPropertiesTable();
	leadGlass->SetMaterialPropertiesTable( leadGlassMat );
	
	liquidArMat = new G4MaterialPropertiesTable();
	liquidAr->SetMaterialPropertiesTable( liquidArMat );

	liquidN2Mat = new G4MaterialPropertiesTable();
	liquidN2->SetMaterialPropertiesTable( liquidN2Mat );
	
	//*** Liquid Xe material definitions ***//
	liquidXeMat = new G4MaterialPropertiesTable();
	
	// Electric field used to determine the scintillation quenching as the
	// recombination probability decreases with increasing field.
	//  Either set all Liq. Fields same OR use 4 regions (From surf to bot pmts)
	setField = 0.; // Dummy value.  This should be set by a messenger or some other method
	liquidXeMat->AddConstProperty( "ELECTRICFIELD", setField  );
	
	liquidXeMat->AddConstProperty( "TOTALNUM_INT_SITES", -1 );
	liquidXe->SetMaterialPropertiesTable( liquidXeMat );
	
	mineralOilMat = new G4MaterialPropertiesTable();
	mineralOilMat->AddProperty( "RINDEX", photonEnergies_ConstProp,
			mineralOilRIndex, NUM_PP_ConstProp );
	mineralOil->SetMaterialPropertiesTable( mineralOilMat );
	
	peekMat = new G4MaterialPropertiesTable();
	peek->SetMaterialPropertiesTable( peekMat );	
	
	//	These values were stolen wholesale from the Teflon properties //
	polyethyleneMat = new G4MaterialPropertiesTable();
	G4double *polyethyleneSpeclobe;
	polyethyleneSpeclobe = new G4double[NUM_PP_ConstProp];
	polyethyleneSpeclobe[0] = polyethyleneSpeclobe[1] = 0;
	G4double *polyethyleneSpecspike;
	polyethyleneSpecspike = new G4double[NUM_PP_ConstProp];
	polyethyleneSpecspike[0] = polyethyleneSpecspike[1] = 0;
	G4double *polyethyleneBackscat;
	polyethyleneBackscat = new G4double[NUM_PP_ConstProp];
	polyethyleneBackscat[0] = polyethyleneBackscat[1] = 0;
	G4double *polyethyleneEff;
	polyethyleneEff = new G4double[NUM_PP_ConstProp];
	polyethyleneEff[0] = polyethyleneEff[1] = 1;
	
	polyethyleneMat->AddProperty( "SPECULARLOBECONSTANT",
			photonEnergies_ConstProp, polyethyleneSpeclobe, NUM_PP_ConstProp );
	polyethyleneMat->AddProperty( "SPECULARSPIKECONSTANT",
			photonEnergies_ConstProp, polyethyleneSpecspike, NUM_PP_ConstProp );
	polyethyleneMat->AddProperty( "BACKSCATTERCONSTANT",
			photonEnergies_ConstProp, polyethyleneBackscat, NUM_PP_ConstProp );
	polyethyleneMat->AddProperty( "EFFICIENCY", photonEnergies_ConstProp,
			polyethyleneEff, NUM_PP_ConstProp );

        pvcMat = new G4MaterialPropertiesTable();
        pvc->SetMaterialPropertiesTable( pvcMat );
	
	quartzMat = new G4MaterialPropertiesTable();
	quartz->SetMaterialPropertiesTable( quartzMat );
	
	rockMat = new G4MaterialPropertiesTable();
	rockMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp, rockRefl,
			NUM_PP_ConstProp );
	rock->SetMaterialPropertiesTable( rockMat );
	
	sapphireMat = new G4MaterialPropertiesTable();
	sapphire->SetMaterialPropertiesTable( sapphireMat );
	
	ss316Mat = new G4MaterialPropertiesTable();
	ss316->SetMaterialPropertiesTable( ss316Mat );
	
	steelMat = new G4MaterialPropertiesTable();
	steel->SetMaterialPropertiesTable( steelMat );
	
	//*** Teflon material definitions ***//
	teflonMat = new G4MaterialPropertiesTable();
	G4double *teflonSpeclobe;
	teflonSpeclobe = new G4double[NUM_PP_ConstProp];
	teflonSpeclobe[0] = teflonSpeclobe[1] = 0;
	G4double *teflonSpecspike;
	teflonSpecspike = new G4double[NUM_PP_ConstProp];
	teflonSpecspike[0] = teflonSpecspike[1] = 0;
	G4double *teflonBackscat;
	teflonBackscat = new G4double[NUM_PP_ConstProp];
	teflonBackscat[0] = teflonBackscat[1] = 0;
	G4double *teflonEff;
	teflonEff = new G4double[NUM_PP_ConstProp];
	teflonEff[0] = teflonEff[1] = 1;
	
	teflonMat->AddProperty( "SPECULARLOBECONSTANT", photonEnergies_ConstProp,
			teflonSpeclobe, NUM_PP_ConstProp);
	teflonMat->AddProperty( "SPECULARSPIKECONSTANT", photonEnergies_ConstProp,
			teflonSpecspike, NUM_PP_ConstProp );
	teflonMat->AddProperty( "BACKSCATTERCONSTANT", photonEnergies_ConstProp,
			teflonBackscat, NUM_PP_ConstProp );
	teflonMat->AddProperty( "EFFICIENCY", photonEnergies_ConstProp, teflonEff,
			NUM_PP_ConstProp );
	
	teflon->SetMaterialPropertiesTable( teflonMat );
	
	titaniumMat = new G4MaterialPropertiesTable();
	titanium->SetMaterialPropertiesTable( titaniumMat );

	//*** TPB material definitions ***//
	//	I can only imagine that the scattering and absorption length are going
	//	to be highly dependent on the method used to deposit the TPB (vacuum
	//	deposition vs. dipping vs. spray-on vs. whatever). So even though these
	//	values are SWAGs, they're actually double-suspect.
	tpbMat = new G4MaterialPropertiesTable();
	G4double tpbScattering[] = { 5.e-6*m, 5.e-6*mm };	//	This is a SWAG
	G4double tpbAbsorptionKill[] = { 1.*cm, 1.*cm };	//	Also a SWAG
	tpbMat->AddProperty( "RAYLEIGH", photonEnergies_ConstProp, tpbScattering,
			NUM_PP_ConstProp );
	tpbMat->AddProperty( "RINDEX", photonEnergies_ConstProp,
			quartzRefractiveIndex, NUM_PP_ConstProp );
	tpbMat->AddProperty( "ABSLENGTH", photonEnergies_ConstProp,
			tpbAbsorptionKill, NUM_PP_ConstProp );
	tpbMat->AddProperty( "WLSABSLENGTH", tpbAbsorptionEnergies, tpbAbsorption,
			num_tpbAbs );
	tpbMat->AddProperty( "WLSCOMPONENT", tpbEmissionEnergies, tpbEmission,
			num_tpbEmi );
	tpbMat->AddConstProperty( "WLSTIMECONSTANT", 2.*ns );
	tpb->SetMaterialPropertiesTable( tpbMat );
	
	//*** W material definitions ***//
	tungstenMat = new G4MaterialPropertiesTable();
	tungsten->SetMaterialPropertiesTable( tungstenMat );

	//*** Vacuum material definitions ***//
	vacuumMat = new G4MaterialPropertiesTable();
	G4double *vacuumRindex;
	vacuumRindex = new G4double[NUM_PP_ConstProp];
	vacuumRindex[0] = vacuumRindex[1] = 1;
	G4double *vacuumAbsLength;
	vacuumAbsLength = new G4double[NUM_PP_ConstProp];
	vacuumAbsLength[0] = vacuumAbsLength[1] = 1e20;
	vacuumMat->AddProperty( "RINDEX", photonEnergies_ConstProp, vacuumRindex,
			NUM_PP_ConstProp );
	vacuumMat->AddProperty( "ABSLENGTH", photonEnergies_ConstProp,
			vacuumAbsLength, NUM_PP_ConstProp );
	vacuum->SetMaterialPropertiesTable( vacuumMat );
	
	blackiumMat = vacuumMat;
	blackium->SetMaterialPropertiesTable( blackiumMat );
	
	//*** Water material definitions ***//
	waterMat = new G4MaterialPropertiesTable();	
	water->SetMaterialPropertiesTable( waterMat );
	// overwrite computed meanExcitationEnergy with ICRU recommended value 
	water->GetIonisation()->SetMeanExcitationEnergy(75.0*eV);

	dopedWater3->SetMaterialPropertiesTable( waterMat );
	dopedWater7->SetMaterialPropertiesTable( waterMat );
	dopedWater3->GetIonisation()->SetMeanExcitationEnergy(75.0*eV);
	dopedWater7->GetIonisation()->SetMeanExcitationEnergy(75.0*eV);	

}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					CreateOpticalSurfaces()
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccMaterials::CreateOpticalSurfaces()
{
	/* ********* Create Al - quartz boundary ********** */
	aluminumQuartzSurface = new G4OpticalSurface("aluminumQuartzSurface",
			unified, polished, dielectric_metal);
	// Create new materials table
	G4MaterialPropertiesTable * aluminumQuartzSurfaceMat =
			new G4MaterialPropertiesTable();
	aluminumQuartzSurfaceMat->AddProperty( "REFLECTIVITY", 
		photonEnergies_ConstProp, aluminumUnoxidizedRefl, 2 );
	// Set surface material table
	aluminumQuartzSurface->SetMaterialPropertiesTable(aluminumQuartzSurfaceMat);
	/* ************************************************ */
	
	/* ********* Create gas Xe - copper boundary ********* */
	gasXeCopperSurface = new G4OpticalSurface("gasXeCopperSurface", unified, 
		polished, dielectric_metal);
	// Create new materials table
	G4MaterialPropertiesTable * gasXeCopperSurfaceMat = 
		new G4MaterialPropertiesTable();
	gasXeCopperSurfaceMat->AddProperty( "REFLECTIVITY", 
		photonEnergies_ConstProp, copperRefl, 2 );
	// Set surface material table
	gasXeCopperSurface->SetMaterialPropertiesTable(gasXeCopperSurfaceMat);
	/* *************************************************** */
	
	/* ********* Create liquid Xe - copper boundary ********* */
	liquidXeCopperSurface = new G4OpticalSurface("liquidXeCopperSurface",
			unified, polished, dielectric_metal);
	// Create new materials table
	G4MaterialPropertiesTable * liquidXeCopperSurfaceMat = 
		new G4MaterialPropertiesTable();
	liquidXeCopperSurfaceMat->AddProperty( "REFLECTIVITY", 
		photonEnergies_ConstProp, copperRefl, 2 );
	// Set surface material table
	liquidXeCopperSurface->SetMaterialPropertiesTable(liquidXeCopperSurfaceMat);
	/* *************************************************** */
	
	/* ********* Create gas Xe - HDPE boundary ********* */
	gasXeHDPESurface = new G4OpticalSurface("gasXeHDPESurface", unified, 
		polished, dielectric_metal);
	// Create new materials table
	G4MaterialPropertiesTable * gasXeHDPESurfaceMat = 
		new G4MaterialPropertiesTable();
	gasXeHDPESurfaceMat->AddProperty( "SPECULARLOBECONSTANT", 
		polyethyleneMat->GetProperty("SPECULARLOBECONSTANT") );
	gasXeHDPESurfaceMat->AddProperty( "SPECULARSPIKECONSTANT", 
		polyethyleneMat->GetProperty("SPECULARSPIKECONSTANT") );
	gasXeHDPESurfaceMat->AddProperty( "BACKSCATTERCONSTANT", 
		polyethyleneMat->GetProperty("BACKSCATTERCONSTANT") );
	gasXeHDPESurfaceMat->AddProperty( "EFFICIENCY", 
		polyethyleneMat->GetProperty("EFFICIENCY") );
	gasXeHDPESurfaceMat->AddProperty( "REFLECTIVITY", 
		photonEnergies_ConstProp, polyethyleneRefl, 2 );
	// Set surface material table
	gasXeHDPESurface->SetMaterialPropertiesTable(gasXeHDPESurfaceMat);
	/* *************************************************** */
	
	/* ********* Create liquid Xe - HDPE boundary ********* */
	liquidXeHDPESurface = new G4OpticalSurface("liquidXeHDPESurface", unified, 
		polished, dielectric_metal);
	// Create new materials table
	G4MaterialPropertiesTable * liquidXeHDPESurfaceMat = 
		new G4MaterialPropertiesTable();
	liquidXeHDPESurfaceMat->AddProperty( "SPECULARLOBECONSTANT", 
		polyethyleneMat->GetProperty("SPECULARLOBECONSTANT") );
	liquidXeHDPESurfaceMat->AddProperty( "SPECULARSPIKECONSTANT", 
		polyethyleneMat->GetProperty("SPECULARSPIKECONSTANT") );
	liquidXeHDPESurfaceMat->AddProperty( "BACKSCATTERCONSTANT", 
		polyethyleneMat->GetProperty("BACKSCATTERCONSTANT") );
	liquidXeHDPESurfaceMat->AddProperty( "EFFICIENCY", 
		polyethyleneMat->GetProperty("EFFICIENCY") );
	liquidXeHDPESurfaceMat->AddProperty( "REFLECTIVITY", 
		photonEnergies_ConstProp, polyethyleneRefl, 2 );
	// Set surface material table
	liquidXeHDPESurface->SetMaterialPropertiesTable(liquidXeHDPESurfaceMat);
	/* *************************************************** */
	
	/* ********* Create gas Xe - Teflon boundary ********* */
	gasXeTeflonSurface = new G4OpticalSurface("gasXeTeflonSurface", unified, 
		groundfrontpainted, dielectric_dielectric);
	// Create new materials table
	G4MaterialPropertiesTable * gasXeTeflonSurfaceMat = 
		new G4MaterialPropertiesTable();
	gasXeTeflonSurfaceMat->AddProperty( "SPECULARLOBECONSTANT", 
		teflonMat->GetProperty("SPECULARLOBECONSTANT"));
	gasXeTeflonSurfaceMat->AddProperty( "SPECULARSPIKECONSTANT", 
		teflonMat->GetProperty("SPECULARSPIKECONSTANT"));
	gasXeTeflonSurfaceMat->AddProperty( "BACKSCATTERCONSTANT", 
		teflonMat->GetProperty("BACKSCATTERCONSTANT"));
	gasXeTeflonSurfaceMat->AddProperty( "EFFICIENCY", 
		teflonMat->GetProperty("EFFICIENCY"));
	G4double gasXeTeflonRefl[23] = { 0.00, 0.03, 0.65, 0.65, 0.65,
					 0.67, 0.71, 0.73, 0.74, 0.99,
					 0.99, 0.99, 0.99, 0.99, 0.99,
					 0.99, 0.99, 0.99, 0.99, 0.99,
					 0.99, 0.99, 1.00 };
	//Puja Kadkhoda, Detlev Ristau, Ferdinand von Alvensleben.
	//Total scatter measurements in the DUV/VUV. volume 3578,
	//pages 544–554. SPIE, 1999. Figure 7 was rule of thumb, but
	//Figures 1.12 and 1.13 of Silva's Ph.D. Thesis also (2009)
	if ( LXETEMPERATURE < 200*kelvin ) {
	  for ( G4int i=0; i < 23; i++ )
	    gasXeTeflonRefl[i] = 0.75;
	}
	gasXeTeflonSurfaceMat->AddProperty( "REFLECTIVITY", 
		photonEnergies, gasXeTeflonRefl, 23 );
	// Set surface material table
	gasXeTeflonSurface->SetMaterialPropertiesTable(gasXeTeflonSurfaceMat);
	/* *************************************************** */
	
	/* ********* Create liquid Xe - Teflon boundary ********* */
	liquidXeTeflonSurface = new G4OpticalSurface("liquidXeTeflonSurface", 
		unified, groundfrontpainted, dielectric_dielectric);
	// Create new materials table
	G4MaterialPropertiesTable * liquidXeTeflonSurfaceMat = 
		new G4MaterialPropertiesTable();
	liquidXeTeflonSurfaceMat->AddProperty( "SPECULARLOBECONSTANT", 
		teflonMat->GetProperty("SPECULARLOBECONSTANT"));
	liquidXeTeflonSurfaceMat->AddProperty( "SPECULARSPIKECONSTANT", 
		teflonMat->GetProperty("SPECULARSPIKECONSTANT"));
	liquidXeTeflonSurfaceMat->AddProperty( "BACKSCATTERCONSTANT", 
		teflonMat->GetProperty("BACKSCATTERCONSTANT"));
	liquidXeTeflonSurfaceMat->AddProperty( "EFFICIENCY", 
		teflonMat->GetProperty("EFFICIENCY"));
	G4double liquidXeTeflonRefl[2] = { 1.00, 1.00 }; //true value may lie 
	//between >~0.95 and 1.15 (EXO). Look at Vladimir's Sept. LZ meeting talk.
	liquidXeTeflonSurfaceMat->AddProperty( "REFLECTIVITY", 
		photonEnergies_ConstProp, liquidXeTeflonRefl, 2 );
	// Set surface material table
	liquidXeTeflonSurface->SetMaterialPropertiesTable(liquidXeTeflonSurfaceMat);

	/* *************************************************** */
	
	/* ********* Create gas Xe - Steel boundary ********* */
	gasXeSteelSurface = new G4OpticalSurface("gasXeSteelSurface", unified, 
		polished, dielectric_metal);
	// Create new materials table
	G4MaterialPropertiesTable * gasXeSteelSurfaceMat = 
		new G4MaterialPropertiesTable();
	G4double gasXeSteelRefl[2] = { 0.15, 0.15 };
	gasXeSteelSurfaceMat->AddProperty( "REFLECTIVITY", 
		photonEnergies_ConstProp, gasXeSteelRefl, 2);
	// Set surface material table
	gasXeSteelSurface->SetMaterialPropertiesTable(gasXeSteelSurfaceMat);
	/* *************************************************** */
	
	/* ********* Create liquid Xe - Steel boundary ********* */
	liquidXeSteelSurface = new G4OpticalSurface("liquidXeSteelSurface", 
		unified, polished, dielectric_metal);
	// Create new materials table
	G4MaterialPropertiesTable * liquidXeSteelSurfaceMat = 
		new G4MaterialPropertiesTable();
	G4double liquidXeSteelRefl[2] = { 0.00, 0.00 };
	liquidXeSteelSurfaceMat->AddProperty( "REFLECTIVITY", 
		photonEnergies_ConstProp, liquidXeSteelRefl, 2);
	// Set surface material table
	liquidXeSteelSurface->SetMaterialPropertiesTable(
			liquidXeSteelSurfaceMat );

	/* *************************************************** */
	
	/* ********* Create gas Ar - Teflon boundary ********* */
        gasArTeflonSurface = new G4OpticalSurface("gasArTeflonSurface", 
	unified, groundfrontpainted, dielectric_dielectric);
        // Create new materials table
        G4MaterialPropertiesTable * gasArTeflonSurfaceMat = 
	  new G4MaterialPropertiesTable();
        gasArTeflonSurfaceMat->AddProperty( "SPECULARLOBECONSTANT", 
        teflonMat->GetProperty("SPECULARLOBECONSTANT"));
        gasArTeflonSurfaceMat->AddProperty( "SPECULARSPIKECONSTANT", 
	teflonMat->GetProperty("SPECULARSPIKECONSTANT"));
        gasArTeflonSurfaceMat->AddProperty( "BACKSCATTERCONSTANT", 
	teflonMat->GetProperty("BACKSCATTERCONSTANT"));
        gasArTeflonSurfaceMat->AddProperty( "EFFICIENCY", 
	teflonMat->GetProperty("EFFICIENCY"));
        G4double gasArTeflonRefl[23] = { 0.00, 0.03, 0.65, 0.65, 0.65,
                                         0.67, 0.71, 0.73, 0.74, 0.99,
                                         0.99, 0.99, 0.99, 0.99, 0.99,
                                         0.99, 0.99, 0.99, 0.99, 0.99,
                                         0.99, 0.99, 1.00 };
        gasArTeflonSurfaceMat->AddProperty( "REFLECTIVITY", 
	photonEnergies, gasArTeflonRefl, 23 );
        // Set surface material table
        gasArTeflonSurface->SetMaterialPropertiesTable(gasArTeflonSurfaceMat);
        /* *************************************************** */
        
        /* ********* Create liquid Ar - Teflon boundary ********* */
        liquidArTeflonSurface = new G4OpticalSurface("liquidArTeflonSurface", 
	unified, groundfrontpainted, dielectric_dielectric);
        // Create new materials table
        G4MaterialPropertiesTable * liquidArTeflonSurfaceMat = 
	  new G4MaterialPropertiesTable();
        liquidArTeflonSurfaceMat->AddProperty( "SPECULARLOBECONSTANT", 
	teflonMat->GetProperty("SPECULARLOBECONSTANT"));
        liquidArTeflonSurfaceMat->AddProperty( "SPECULARSPIKECONSTANT", 
	teflonMat->GetProperty("SPECULARSPIKECONSTANT"));
        liquidArTeflonSurfaceMat->AddProperty( "BACKSCATTERCONSTANT", 
	teflonMat->GetProperty("BACKSCATTERCONSTANT"));
        liquidArTeflonSurfaceMat->AddProperty( "EFFICIENCY", 
	teflonMat->GetProperty("EFFICIENCY"));
        G4double liquidArTeflonRefl[2] = { 1.00, 1.00 };
        liquidArTeflonSurfaceMat->AddProperty( "REFLECTIVITY", 
	photonEnergies_ConstProp, liquidArTeflonRefl, 2 );
        // Set surface material table
        liquidArTeflonSurface->SetMaterialPropertiesTable(
				 liquidArTeflonSurfaceMat);
	
        /* *************************************************** */
        
        /* ********* Create gas Ar - Steel boundary ********* */
        gasArSteelSurface = new G4OpticalSurface("gasArSteelSurface",
	unified, polished, dielectric_metal);
        // Create new materials table
        G4MaterialPropertiesTable * gasArSteelSurfaceMat = 
	  new G4MaterialPropertiesTable();
        G4double gasArSteelRefl[2] = { 0.15, 0.15 };
        gasArSteelSurfaceMat->AddProperty( "REFLECTIVITY", 
	photonEnergies_ConstProp, gasArSteelRefl, 2);
        // Set surface material table
        gasArSteelSurface->SetMaterialPropertiesTable(gasArSteelSurfaceMat);
        /* *************************************************** */
        
        /* ********* Create liquid Ar - Steel boundary ********* */
        liquidArSteelSurface = new G4OpticalSurface("liquidArSteelSurface", 
	unified, polished, dielectric_metal);
        // Create new materials table
        G4MaterialPropertiesTable * liquidArSteelSurfaceMat = 
	  new G4MaterialPropertiesTable();
        G4double liquidArSteelRefl[2] = { 0.00, 0.00 };
        liquidArSteelSurfaceMat->AddProperty( "REFLECTIVITY", 
	photonEnergies_ConstProp, liquidArSteelRefl, 2);
        // Set surface material table
        liquidArSteelSurface->SetMaterialPropertiesTable(
				liquidArSteelSurfaceMat );
	
        /* *************************************************** */
	
	/* ********* Create gas Xe - Titanium boundary ********* */
	gasXeTitaniumSurface = new G4OpticalSurface("gasXeTitaniumSurface", unified, 
		polished, dielectric_metal);
	// Create new materials table
	G4MaterialPropertiesTable * gasXeTitaniumSurfaceMat = 
		new G4MaterialPropertiesTable();
	gasXeTitaniumSurfaceMat->AddProperty( "REFLECTIVITY", 
		photonEnergies_ConstProp, titaniumRefl, 2);
	// Set surface material table
	gasXeTitaniumSurface->SetMaterialPropertiesTable(gasXeTitaniumSurfaceMat);
	/* *************************************************** */
	
	/* ********* Create liquid Xe - Titanium boundary ********* */
	liquidXeTitaniumSurface = new G4OpticalSurface("liquidXeTitaniumSurface", 
		unified, polished, dielectric_metal);
	// Create new materials table
	G4MaterialPropertiesTable * liquidXeTitaniumSurfaceMat = 
		new G4MaterialPropertiesTable();
	liquidXeTitaniumSurfaceMat->AddProperty( "REFLECTIVITY", 
		photonEnergies_ConstProp, titaniumRefl, 2);
	// Set surface material table
	liquidXeTitaniumSurface->SetMaterialPropertiesTable(
			liquidXeTitaniumSurfaceMat );
	/* *************************************************** */

	/* ********* Create gas Ar - Gold boundary ********* */
	gasArGoldSurface = new G4OpticalSurface("gasArGoldSurface", unified, 
		polished, dielectric_metal);
	// Create new materials table
	G4MaterialPropertiesTable *gasArGoldSurfaceMat = 
		new G4MaterialPropertiesTable();
	gasArGoldSurfaceMat->AddProperty( "REFLECTIVITY", 
		photonEnergies_ConstProp, goldRefl, 2);
	// Set surface material table
	gasArGoldSurface->SetMaterialPropertiesTable(gasArGoldSurfaceMat);
	/* *************************************************** */
	
	/* ********* Create gas Ar - Aluminum boundary ********* */
	gasArAluminumSurface = new G4OpticalSurface("gasArAluminumSurface",
		unified, polished, dielectric_metal);
	// Create new materials table
	G4MaterialPropertiesTable *gasArAluminumSurfaceMat = 
		new G4MaterialPropertiesTable();
	gasArAluminumSurfaceMat->AddProperty( "REFLECTIVITY", 
		photonEnergies_ConstProp, aluminumRefl, 2);
	// Set surface material table
	gasArAluminumSurface->SetMaterialPropertiesTable(
			gasArAluminumSurfaceMat );
	/* *************************************************** */

	/* ********* Create gas ArN2 - Gold boundary ********* */
	gasArN2GoldSurface = new G4OpticalSurface("gasArN2GoldSurface", unified, 
		polished, dielectric_metal);
	// Create new materials table
	G4MaterialPropertiesTable *gasArN2GoldSurfaceMat = 
		new G4MaterialPropertiesTable();
	gasArN2GoldSurfaceMat->AddProperty( "REFLECTIVITY", 
		photonEnergies_ConstProp, goldRefl, 2);
	// Set surface material table
	gasArN2GoldSurface->SetMaterialPropertiesTable(gasArN2GoldSurfaceMat);
	/* *************************************************** */
	
	/* ********* Create gas ArN2 - Aluminum boundary ********* */
	gasArN2AluminumSurface = new G4OpticalSurface("gasArN2AluminumSurface",
		unified, polished, dielectric_metal);
	// Create new materials table
	G4MaterialPropertiesTable *gasArN2AluminumSurfaceMat = 
		new G4MaterialPropertiesTable();
	gasArN2AluminumSurfaceMat->AddProperty( "REFLECTIVITY", 
		photonEnergies_ConstProp, aluminumRefl, 2);
	// Set surface material table
	gasArN2AluminumSurface->SetMaterialPropertiesTable(
			gasArN2AluminumSurfaceMat );
	/* *************************************************** */
	
	/* ********* Create quartz - PTFE boundary ********* */
	quartzTeflonSurface = new G4OpticalSurface("quartzTeflonSurface",
		unified, groundfrontpainted, dielectric_dielectric);
	// Create new materials table
	G4MaterialPropertiesTable * quartzTeflonSurfaceMat = 
		new G4MaterialPropertiesTable();
	G4double quartzTeflonRefl[2] = { 1.0, 1.0 };
	quartzTeflonSurfaceMat->AddProperty( "REFLECTIVITY", 
		photonEnergies_ConstProp, quartzTeflonRefl, 2 );
	// Set surface material table
	quartzTeflonSurface->SetMaterialPropertiesTable(quartzTeflonSurfaceMat);
	/* *************************************************** */
	
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					CreateVisualAttributes()
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccMaterials::CreateVisualAttributes()
{
	//	For SetColor, the order is Red, Green, Blue, Alpha
	//	Colors included in the G4Color class are:
	//	White(), Gray(), Black()
	//	Red(), Green(), Blue()
	//	Cyan(), Magenta(), Yellow()
	
	acrylicVis = new G4VisAttributes();
	acrylicVis->SetColor( 0.5, 0.5, 0.5, 0.1 );
	acrylicVis->SetVisibility( true );
	
	airVis = new G4VisAttributes();
	airVis->SetColor( 0.5, 0.5, 0.5, 0.1 );
	airVis->SetVisibility( false );
	
	aluminumVis = new G4VisAttributes();
	aluminumVis->SetColor( 0.5, 0.5, 0.5, 0.1 );
	aluminumVis->SetVisibility( true );
	
	berylliumVis = new G4VisAttributes();
	berylliumVis->SetColor( 0.9, 0.9, 0.9, 0.1 );
	berylliumVis->SetVisibility( true );
	
	berylliumCopperVis = new G4VisAttributes();
	berylliumCopperVis->SetColor( 1.0, 0.7, 0.3, 0.1 );
	berylliumCopperVis->SetVisibility( true );
	
	blackiumVis = new G4VisAttributes();
	blackiumVis->SetVisibility( false );
	
	copperVis = new G4VisAttributes();
	copperVis->SetColor( 1.0, 0.5, 0, 0.1 );
	copperVis->SetVisibility( true );
	
	gasArVis = new G4VisAttributes();
	gasArVis->SetColor( 0.9, 0.5, 0.3, 0.1 );
	gasArVis->SetVisibility( false );
	
	gasArN2Vis = new G4VisAttributes();
	gasArN2Vis->SetColor( 0.5, 0.5, 0.5, 0.1 );
	gasArN2Vis->SetVisibility( false );
	
	gasN2Vis = new G4VisAttributes();
	gasN2Vis->SetColor( 0.5, 0.5, 0.5, 0.1 );
	gasN2Vis->SetVisibility( false );
	
	gasXeVis = new G4VisAttributes();
	gasXeVis->SetColor( 0.0, 1.0, 1.0, 0.4 );
	gasXeVis->SetVisibility( true );
	
	goldVis = new G4VisAttributes();
	goldVis->SetColor( 1.0, 0.5, 0, 0.1 );
	goldVis->SetVisibility( true );

	gs20GlassVis = new G4VisAttributes();
	gs20GlassVis->SetColor( 0.6, 0.6, 0.9, 0.1 );
	gs20GlassVis->SetVisibility( true );
	
	ironVis = new G4VisAttributes();
	ironVis->SetColor( 1.0, 0.7, 0.0, 0.1 );
	ironVis->SetVisibility( true );
	
	isohexaneVis = new G4VisAttributes();
	isohexaneVis->SetColor( G4Color::Yellow() );
	isohexaneVis->SetVisibility( true );
	
	kaptonVis = new G4VisAttributes();
	kaptonVis->SetColor( 0.1, 0.1, 0.1, 0.1 );
	kaptonVis->SetVisibility( true );
	
	kg2GlassVis = new G4VisAttributes();
	kg2GlassVis->SetColor( 0.6, 0.6, 0.9, 0.1 );
	kg2GlassVis->SetVisibility( true );
	
	leadVis = new G4VisAttributes();
	leadVis->SetColor( 0.2, 0.2, 0.2 );
	leadVis->SetForceWireframe( true );
	leadVis->SetVisibility( true );
	
	leadGlassVis = new G4VisAttributes();
	leadGlassVis->SetColor( 0.9, 0.9, 0.9 );
	leadGlassVis->SetForceSolid( true );
	leadGlassVis->SetVisibility( true );
	
	liquidArVis = new G4VisAttributes();
	liquidArVis->SetColor( 0.5, 0.5, 1, 0.4 );
	liquidArVis->SetVisibility( true );
	
	liquidN2Vis = new G4VisAttributes();
	liquidN2Vis->SetColor( 0.5, 0.5, 0.5, 0.4 );
	liquidN2Vis->SetVisibility( true );
	
	liquidXeVis = new G4VisAttributes();
	liquidXeVis->SetColor( 0.0, 0.0, 1.0, 0.4 );
	liquidXeVis->SetVisibility( true );
	
	mineralOilVis = new G4VisAttributes();
	mineralOilVis->SetColor( G4Color::Yellow() );
	mineralOilVis->SetVisibility( true );
	
	peekVis = new G4VisAttributes();
	peekVis->SetColor( 1.0, 0.3, 0.0 );
	peekVis->SetVisibility( true );
	
	polyethyleneVis = new G4VisAttributes();
	polyethyleneVis->SetColor( G4Color::White() );
	polyethyleneVis->SetForceWireframe( true );
	polyethyleneVis->SetVisibility( true );

	polyethyleneBoratedVis = new G4VisAttributes();
	polyethyleneBoratedVis->SetColor( G4Color::Magenta() );
	polyethyleneBoratedVis->SetForceWireframe( true );
	polyethyleneBoratedVis->SetVisibility( true );

        pvcVis = new G4VisAttributes();
        pvcVis->SetColor( G4Color::Magenta() );
        pvcVis->SetVisibility( true );
	
	quartzVis = new G4VisAttributes();
	quartzVis->SetColor( G4Color::Magenta() );
	quartzVis->SetForceSolid( true );
	quartzVis->SetVisibility( true );
	
	rockVis = new G4VisAttributes();
	rockVis->SetColor( 1.0, 0.3, 0.0 );
	rockVis->SetForceWireframe( true );
	rockVis->SetVisibility( true );
	
	sapphireVis = new G4VisAttributes();
	sapphireVis->SetColor( 0.5, 0.5, 1.0, 0.1 );
	sapphireVis->SetForceSolid( true );
	sapphireVis->SetVisibility( true );
	
	steelVis = new G4VisAttributes();
	steelVis->SetColor( 0.4, 0.4, 0.4, 0.1 );
	steelVis->SetVisibility( true );
	
	teflonVis = new G4VisAttributes();
	teflonVis->SetColor( 1.0, 1.0, 1.0, 0.5 );
	teflonVis->SetVisibility( true );
	
	titaniumVis = new G4VisAttributes();
	titaniumVis->SetColor( 0.6, 0.6, 0.6, 0.1 );
	titaniumVis->SetVisibility( true );
	
	tpbVis = new G4VisAttributes();
	tpbVis->SetColor( 0.1, 0.1, 1.0, 0.1 );
	tpbVis->SetVisibility( true );
	tpbVis->SetForceSolid( true );
	
	tungstenVis = new G4VisAttributes();
	tungstenVis->SetColor( G4Color::Gray() );
	tungstenVis->SetForceWireframe( true );
	tungstenVis->SetVisibility( true );
	
	vacuumVis = new G4VisAttributes();
	vacuumVis->SetVisibility( false );
	
	waterVis = new G4VisAttributes();
	waterVis->SetColor( 0.0, 0.0, 1.0, 0.1 );
	waterVis->SetVisibility( true );
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					InitializeMatrix()
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccMaterials::InitializeMatrix( G4int numEntries, G4int* theMatrix)
{
	for( G4int i=0; i<numEntries; i++ )
		theMatrix[i] = 0;
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					InitializeMatrix()
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccMaterials::InitializeMatrix( G4int numEntries, G4double* theMatrix)
{
	for( G4int i=0; i<numEntries; i++ )
		theMatrix[i] = 0;
}

//------++++++------++++++------++++++------++++++------++++++------++++++------ 
//                                      UpdateElectricField() 
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccMaterials::UpdateElectricField()
{ 
  //---------- Gas ---------------------- 
  gasXe->GetMaterialPropertiesTable(); 
  if( gasXeMat->ConstPropertyExists( "ELECTRICFIELD" ))
    gasXeMat->RemoveConstProperty( "ELECTRICFIELD" ); 
  if( gasXeMat->ConstPropertyExists( "ELECTRICFIELDWINDOW" ))
    gasXeMat->RemoveConstProperty( "ELECTRICFIELDWINDOW") ;
  if( gasXeMat->ConstPropertyExists( "ELECTRICFIELDTOP" ))
    gasXeMat->RemoveConstProperty( "ELECTRICFIELDTOP" ); 
  if( gasXeMat->ConstPropertyExists( "ELECTRICFIELDANODE" )) 
    gasXeMat->RemoveConstProperty( "ELECTRICFIELDANODE" );
  G4double setField = 0.; // Dummy value.  This should be set by a messenger or some other method
  gasXeMat->AddConstProperty("ELECTRICFIELD", setField ); 
  //G4cout << "Setting gaseous xenon electric field to: "<< setField << G4endl; 
  //Update gasXe Properties
  gasXe->SetMaterialPropertiesTable( gasXeMat );
  
  //---------- Liquid ------------------- 
  liquidXe->GetMaterialPropertiesTable();
  if( liquidXeMat->ConstPropertyExists( "ELECTRICFIELD" ))
    liquidXeMat->RemoveConstProperty( "ELECTRICFIELD" ); 
  if( liquidXeMat->ConstPropertyExists( "ELECTRICFIELDSURFACE" )) 
    liquidXeMat->RemoveConstProperty( "ELECTRICFIELDSURFACE" ); 
  if( liquidXeMat->ConstPropertyExists( "ELECTRICFIELDGATE" )) 
    liquidXeMat->RemoveConstProperty( "ELECTRICFIELDGATE" ); 
  if( liquidXeMat->ConstPropertyExists( "ELECTRICFIELDCATHODE" )) 
    liquidXeMat->RemoveConstProperty( "ELECTRICFIELDCATHODE" ); 
  if( liquidXeMat->ConstPropertyExists( "ELECTRICFIELDBOTTOM" )) 
    liquidXeMat->RemoveConstProperty( "ELECTRICFIELDBOTTOM" ); 
  setField = 0.; // Dummy value.  This should be set by a messenger or some other method.
  liquidXeMat->AddConstProperty("ELECTRICFIELD", setField ); 
  //G4cout << "Setting liquid xenon electric field to: "<< setField << G4endl; 
  //Update liquid xenon properties
  liquidXe->SetMaterialPropertiesTable( liquidXeMat ); 
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					SetLXeTeflonRefl()
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccMaterials::SetLXeTeflonRefl( G4double r )
{
    G4MaterialPropertiesTable *tmp = 
    	liquidXeTeflonSurface->GetMaterialPropertiesTable();
    G4double liquidXeTeflonRefl[2];
    liquidXeTeflonRefl[0] = liquidXeTeflonRefl[1] = r;
	tmp->AddProperty( "REFLECTIVITY", 
		photonEnergies_ConstProp, liquidXeTeflonRefl, 2 );
	// Set surface material table
	liquidXeTeflonSurface->SetMaterialPropertiesTable(tmp);
	G4cout << "LXe/PTFE reflectivity set to " << 100.*r << "%" << G4endl;
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					SetLXeSteelRefl()
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccMaterials::SetLXeSteelRefl( G4double r )
{
    G4MaterialPropertiesTable *tmp = 
    	liquidXeSteelSurface->GetMaterialPropertiesTable();
    G4double liquidXeSteelRefl[2];
    liquidXeSteelRefl[0] = liquidXeSteelRefl[1] = r;
    tmp->RemoveConstProperty( "REFLECTIVITY" );
	tmp->AddProperty( "REFLECTIVITY", 
		photonEnergies_ConstProp, liquidXeSteelRefl, 2 );
	// Set surface material table
	liquidXeSteelSurface->SetMaterialPropertiesTable(tmp);
	G4cout << "LXe/steel reflectivity set to " << 100.*r << "%" << G4endl;
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					SetLXeAbs()
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccMaterials::SetLXeAbs( G4double l )
{
	G4double liquidXeAbslength[2];
	liquidXeAbslength[0] = liquidXeAbslength[1] = l;
	liquidXeMat->RemoveConstProperty( "ABSLENGTH" );
    liquidXeMat->AddProperty( "ABSLENGTH", photonEnergies_ConstProp,
				liquidXeAbslength, 2 );
	/*liquidXeAbslength = l;
	SetOpticalDebugging( opticalDebugging );*/
	G4cout << "LXe absorption length set to " << 0.1*l << " cm" << G4endl;
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					SetLXeRayleigh()
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccMaterials::SetLXeRayleigh( G4double l )
{
	G4double liquidXeRayleighlength[2];
	liquidXeRayleighlength[0] = liquidXeRayleighlength[1] = l;
	liquidXeMat->RemoveConstProperty( "RAYLEIGH" );
    liquidXeMat->AddProperty( "RAYLEIGH", photonEnergies_ConstProp,
				liquidXeRayleighlength, 2 );
	G4cout << "LXe Rayleigh length set to " << 0.1*l << " cm" << G4endl;
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					SetGXeTeflonRefl()
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccMaterials::SetGXeTeflonRefl( G4double r )
{
    G4MaterialPropertiesTable *tmp = 
    	gasXeTeflonSurface->GetMaterialPropertiesTable();
    G4double gasXeTeflonRefl[2];
    gasXeTeflonRefl[0] = gasXeTeflonRefl[1] = r;
	tmp->AddProperty( "REFLECTIVITY", 
		photonEnergies_ConstProp, gasXeTeflonRefl, 2 );
	// Set surface material table
	gasXeTeflonSurface->SetMaterialPropertiesTable(tmp);
	G4cout << "GXe/PTFE reflectivity set to " << 100.*r << "%" << G4endl;
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					SetGXeSteelRefl()
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccMaterials::SetGXeSteelRefl( G4double r )
{
    G4MaterialPropertiesTable *tmp = 
    	gasXeSteelSurface->GetMaterialPropertiesTable();
    G4double gasXeSteelRefl[2];
    gasXeSteelRefl[0] = gasXeSteelRefl[1] = r;
	tmp->AddProperty( "REFLECTIVITY", 
		photonEnergies_ConstProp, gasXeSteelRefl, 2 );
	// Set surface material table
	gasXeSteelSurface->SetMaterialPropertiesTable(tmp);
	G4cout << "GXe/steel reflectivity set to " << 100.*r << "%" << G4endl;
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					SetGXeAbs()
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccMaterials::SetGXeAbs( G4double l )
{
	G4double gasXeAbslength[2];
	gasXeAbslength[0] = gasXeAbslength[1] = l;
	gasXeMat->RemoveConstProperty( "ABSLENGTH" );
    gasXeMat->AddProperty( "ABSLENGTH", photonEnergies_ConstProp,
				gasXeAbslength, 2 );
	G4cout << "GXe absorption length set to " << 0.1*l << " cm" << G4endl;
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					SetGXeRayleigh()
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccMaterials::SetGXeRayleigh( G4double l )
{
	G4double gasXeRayleighlength[2];
	gasXeRayleighlength[0] = gasXeRayleighlength[1] = l;
	gasXeMat->RemoveConstProperty( "RAYLEIGH" );
    gasXeMat->AddProperty( "RAYLEIGH", photonEnergies_ConstProp,
				gasXeRayleighlength, 2 );
	G4cout << "GXe Rayleigh length set to " << 0.1*l << " cm" << G4endl;
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					SetAlUnoxQuartzRefl()
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccMaterials::SetAlUnoxQuartzRefl( G4double r )
{
	G4MaterialPropertiesTable *tmp = 
		aluminumQuartzSurface->GetMaterialPropertiesTable();
	G4double alUnoxQuartzRefl[2];
	alUnoxQuartzRefl[0] = alUnoxQuartzRefl[1] = r;
	tmp->AddProperty( "REFLECTIVITY", 
		photonEnergies_ConstProp, alUnoxQuartzRefl, 2 );
	// Set surface material table
	aluminumQuartzSurface->SetMaterialPropertiesTable(tmp);
	G4cout << "Unoxidized Al reflectivity set to " << 100.*r << "%" << G4endl;
}

//------++++++------++++++------++++++------++++++------++++++------++++++------
//					SetOpticalDebugging()
//------++++++------++++++------++++++------++++++------++++++------++++++------
void BaccMaterials::SetOpticalDebugging( G4bool debug )
{
	//	Set the flag that says whether we are using simplified optical
	//	properties for debugging purposes. These simplifications are:
	//		1. Set all indices of refraction to 1.
	//		2. Set the absorption and Rayleigh scattering lengths for water,
	//		   liquid xenon, gaseous xenon, and quartz (basically, all
	//		   transparent materials) to 1000 km.
	//		3. Set quartz transmission to 100%.
	//		4. Set the reflectivity of all opaque materials (including diffuse
	//		   reflectors such as PFTE and HDPE) to 0%.
	opticalDebugging = debug;
	
	const G4int NUM_PP_ConstProp = num_pp_constProp;
	const G4int NUM_PP = num_pp;
	const G4int nWaterEntries = num_water;
	
	std::vector<std::string> properties;
	properties.push_back( "RINDEX" );
	properties.push_back( "REFLECTIVITY" );
	properties.push_back( "ABSLENGTH" );
	properties.push_back( "RALEIGH" );
	
	for( G4int i=0; i<(G4int)properties.size(); i++ ) {
		if( acrylicMat->ConstPropertyExists( properties[i].c_str() ) )
			acrylicMat->RemoveProperty( properties[i].c_str() );
		if( airMat->ConstPropertyExists( properties[i].c_str() ) )
			airMat->RemoveProperty( properties[i].c_str() );
		if( aluminumMat->ConstPropertyExists( properties[i].c_str() ) )
			aluminumMat->RemoveProperty( properties[i].c_str() );
		if( berylliumMat->ConstPropertyExists( properties[i].c_str() ) )
			berylliumMat->RemoveProperty( properties[i].c_str() );
		if( berylliumCopperMat->ConstPropertyExists( properties[i].c_str() ) )
			berylliumCopperMat->RemoveProperty( properties[i].c_str() );
		if( copperMat->ConstPropertyExists( properties[i].c_str() ) )
			copperMat->RemoveProperty( properties[i].c_str() );
		if( gasArMat->ConstPropertyExists( properties[i].c_str() ) )
			gasArMat->RemoveProperty( properties[i].c_str() );
		if( gasArN2Mat->ConstPropertyExists( properties[i].c_str() ) )
			gasArN2Mat->RemoveProperty( properties[i].c_str() );
		if( gasN2Mat->ConstPropertyExists( properties[i].c_str() ) )
			gasN2Mat->RemoveProperty( properties[i].c_str() );
		if( gasXeMat->ConstPropertyExists( properties[i].c_str() ) )
			gasXeMat->RemoveProperty( properties[i].c_str() );
		if( goldMat->ConstPropertyExists( properties[i].c_str() ) )
			goldMat->RemoveProperty( properties[i].c_str() );
		if( halonMat->ConstPropertyExists( properties[i].c_str() ) )
			halonMat->RemoveProperty( properties[i].c_str() );
		if( ironMat->ConstPropertyExists( properties[i].c_str() ) )
			ironMat->RemoveProperty( properties[i].c_str() );
		if( isohexaneMat->ConstPropertyExists( properties[i].c_str() ) )
			isohexaneMat->RemoveProperty( properties[i].c_str() );
		if( leadMat->ConstPropertyExists( properties[i].c_str() ) )
			leadMat->RemoveProperty( properties[i].c_str() );
		if( leadGlassMat->ConstPropertyExists( properties[i].c_str() ) )
			leadGlassMat->RemoveProperty( properties[i].c_str() );
		if( liquidArMat->ConstPropertyExists( properties[i].c_str() ) )
			liquidArMat->RemoveProperty( properties[i].c_str() );
			liquidArMat->RemoveProperty( properties[i].c_str() );
		if( liquidN2Mat->ConstPropertyExists( properties[i].c_str() ) )
			liquidN2Mat->RemoveProperty( properties[i].c_str() );
		if( liquidXeMat->ConstPropertyExists( properties[i].c_str() ) )
			liquidXeMat->RemoveProperty( properties[i].c_str() );
		if( mineralOilMat->ConstPropertyExists( properties[i].c_str() ) )
			mineralOilMat->RemoveProperty( properties[i].c_str() );
		if( peekMat->ConstPropertyExists( properties[i].c_str() ) )
			peekMat->RemoveProperty( properties[i].c_str() );
		if( polyethyleneMat->ConstPropertyExists( properties[i].c_str() ) )
			polyethyleneMat->RemoveProperty( properties[i].c_str() );
		if( pvcMat->ConstPropertyExists( properties[i].c_str() ) )
			pvcMat->RemoveProperty( properties[i].c_str() );
		if( quartzMat->ConstPropertyExists( properties[i].c_str() ) )
			quartzMat->RemoveProperty( properties[i].c_str() );
		if( ss316Mat->ConstPropertyExists( properties[i].c_str() ) )
			ss316Mat->RemoveProperty( properties[i].c_str() );
		if( steelMat->ConstPropertyExists( properties[i].c_str() ) )
			steelMat->RemoveProperty( properties[i].c_str() );
		if( teflonMat->ConstPropertyExists( properties[i].c_str() ) )
			teflonMat->RemoveProperty( properties[i].c_str() );
		if( titaniumMat->ConstPropertyExists( properties[i].c_str() ) )
			titaniumMat->RemoveProperty( properties[i].c_str() );
		if( tungstenMat->ConstPropertyExists( properties[i].c_str() ) )
			tungstenMat->RemoveProperty( properties[i].c_str() );
		if( waterMat->ConstPropertyExists( properties[i].c_str() ) )
			waterMat->RemoveProperty( properties[i].c_str() );
	}
	
	if( debug ) {
		acrylicMat->AddProperty( "RINDEX", photonEnergies_ConstProp,
				optDebugRefIndex, NUM_PP_ConstProp);
		airMat->AddProperty( "RINDEX", photonEnergies_ConstProp,
				optDebugRefIndex, NUM_PP_ConstProp );
		aluminumMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				optDebugReflection, NUM_PP_ConstProp );
		berylliumMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				optDebugReflection, NUM_PP_ConstProp );
		berylliumCopperMat->AddProperty( "REFLECTIVITY",
				photonEnergies_ConstProp, optDebugReflection,
				NUM_PP_ConstProp );
		copperMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				optDebugReflection, NUM_PP_ConstProp );
		gasArMat->AddProperty( "RINDEX", photonEnergies_ConstProp,
				optDebugRefIndex, NUM_PP_ConstProp );
		gasArMat->AddProperty( "ABSLENGTH", photonEnergies_ConstProp,
				optDebugAbsLength, NUM_PP_ConstProp );
		gasArN2Mat->AddProperty( "RINDEX", photonEnergies_ConstProp,
				optDebugRefIndex, NUM_PP_ConstProp );
		gasArN2Mat->AddProperty( "ABSLENGTH", photonEnergies_ConstProp,
				optDebugAbsLength, NUM_PP_ConstProp );
		gasN2Mat->AddProperty( "RINDEX", photonEnergies_ConstProp,
				optDebugRefIndex, NUM_PP_ConstProp );
		gasN2Mat->AddProperty( "ABSLENGTH", photonEnergies_ConstProp,
				optDebugAbsLength, NUM_PP_ConstProp );
		gasXeMat->AddProperty( "RINDEX", photonEnergies_ConstProp,
				optDebugRefIndex, NUM_PP_ConstProp );
		gasXeMat->AddProperty( "ABSLENGTH", photonEnergies_ConstProp,
				optDebugAbsLength, NUM_PP_ConstProp );
		goldMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				optDebugReflection, NUM_PP_ConstProp );
		halonMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				optDebugReflection, NUM_PP_ConstProp );
		ironMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				optDebugReflection, NUM_PP_ConstProp );
		isohexaneMat->AddProperty( "RINDEX", photonEnergies_ConstProp,
				optDebugRefIndex, NUM_PP_ConstProp );
		leadMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				optDebugReflection, NUM_PP_ConstProp );
		leadGlassMat->AddProperty( "RINDEX", photonEnergies_ConstProp,
				optDebugRefIndex, NUM_PP_ConstProp );
		leadGlassMat->AddProperty( "ABSLENGTH", photonEnergies_ConstProp,
				optDebugAbsLength, NUM_PP_ConstProp );
		liquidXeMat->AddProperty( "RINDEX", photonEnergies_ConstProp,
				optDebugRefIndex, NUM_PP_ConstProp );
		liquidXeMat->AddProperty( "ABSLENGTH", photonEnergies_ConstProp,
				optDebugAbsLength, NUM_PP_ConstProp );
		liquidXeMat->AddProperty( "RAYLEIGH", photonEnergies_ConstProp,
				optDebugRayleighLength, NUM_PP_ConstProp );
		mineralOilMat->AddProperty( "RINDEX", photonEnergies_ConstProp,
				optDebugRefIndex, NUM_PP_ConstProp );
		peekMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				optDebugReflection, NUM_PP_ConstProp);
		polyethyleneMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				optDebugReflection, NUM_PP_ConstProp);
		pvcMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				optDebugReflection, NUM_PP_ConstProp);
		quartzMat->AddProperty( "RINDEX", photonEnergies_ConstProp,
				optDebugRefIndex, NUM_PP_ConstProp );
		quartzMat->AddProperty( "ABSLENGTH", photonEnergies_ConstProp,
				optDebugAbsLength, NUM_PP_ConstProp );	
		sapphireMat->AddProperty( "RINDEX", photonEnergies_ConstProp,
				optDebugRefIndex, NUM_PP_ConstProp );
		sapphireMat->AddProperty( "ABSLENGTH", photonEnergies_ConstProp,
				optDebugAbsLength, NUM_PP_ConstProp );	
		ss316Mat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				optDebugReflection, NUM_PP_ConstProp );
		steelMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				optDebugReflection, NUM_PP_ConstProp );
		teflonMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				optDebugReflection, NUM_PP_ConstProp );
		titaniumMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				optDebugReflection, NUM_PP_ConstProp );
		tungstenMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				optDebugReflection, NUM_PP_ConstProp );
		waterMat->AddProperty( "RINDEX", photonEnergies_ConstProp,
				optDebugRefIndex, NUM_PP_ConstProp);
		waterMat->AddProperty( "ABSLENGTH", photonEnergies_ConstProp,
				optDebugAbsLength, NUM_PP_ConstProp);
	} else {
		acrylicMat->AddProperty( "RINDEX", photonEnergies_ConstProp,
				acrylicRefractiveIndex, NUM_PP_ConstProp);
		airMat->AddProperty( "RINDEX", photonEnergies_ConstProp,
				airRefractiveIndex, NUM_PP_ConstProp );
		aluminumMat->AddProperty( "REFLECTIVITY", photonEnergies, aluminumRefl,
				NUM_PP );
		berylliumMat->AddProperty( "REFLECTIVITY", photonEnergies,
				berylliumRefl, NUM_PP );
		berylliumCopperMat->AddProperty( "REFLECTIVITY", photonEnergies,
				berylliumCopperRefl, NUM_PP );
		copperMat->AddProperty( "REFLECTIVITY", photonEnergies, copperRefl,
				NUM_PP );
		gasArMat->AddProperty( "RINDEX", photonEnergies_ConstProp, gasArRindex,
				NUM_PP_ConstProp );
		gasArMat->AddProperty( "ABSLENGTH", photonEnergies_ConstProp,
				gasArAbslength, NUM_PP_ConstProp );
		gasArN2Mat->AddProperty( "RINDEX", photonEnergies_ConstProp,
				gasArN2Rindex, NUM_PP_ConstProp );
		gasArN2Mat->AddProperty( "ABSLENGTH", photonEnergies_ConstProp,
				gasArN2Abslength, NUM_PP_ConstProp );
		gasN2Mat->AddProperty( "RINDEX", photonEnergies_ConstProp, gasN2Rindex,
				NUM_PP_ConstProp );
		gasN2Mat->AddProperty( "ABSLENGTH", photonEnergies_ConstProp,
				gasN2Abslength, NUM_PP_ConstProp );
		gasXeMat->AddProperty( "RINDEX", photonEnergies_ConstProp, gasXeRindex,
				NUM_PP_ConstProp );
		gasXeMat->AddProperty( "ABSLENGTH", photonEnergies_ConstProp,
				gasXeAbslength, NUM_PP_ConstProp );
		goldMat->AddProperty( "REFLECTIVITY", photonEnergies, goldRefl,
				NUM_PP );
		halonMat->AddProperty( "REFLECTIVITY", waterPhotonEnergies,
				halonRefl, nWaterEntries );
		ironMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				ironRefl, NUM_PP_ConstProp );
		isohexaneMat->AddProperty( "RINDEX", photonEnergies, isohexaneRindex,
				NUM_PP );
		leadMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				leadRefl, NUM_PP_ConstProp );
		leadGlassMat->AddProperty( "RINDEX", photonEnergies,
				leadGlassRefractiveIndex, NUM_PP );
		leadGlassMat->AddProperty( "ABSLENGTH", photonEnergies_ConstProp,
				leadGlassAbsorption, NUM_PP_ConstProp );
		liquidXeMat->AddProperty( "RINDEX", photonEnergies, liquidXeRindex,
				NUM_PP );
		liquidXeMat->AddProperty( "ABSLENGTH", photonEnergies_ConstProp,
				liquidXeAbslength, NUM_PP_ConstProp );
		liquidXeMat->AddProperty( "RAYLEIGH", photonEnergies,
				liquidXeRayleigh, NUM_PP );
		mineralOilMat->AddProperty( "RINDEX", photonEnergies, mineralOilRIndex,
				NUM_PP );
		peekMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
                peekRefl, NUM_PP_ConstProp );
		polyethyleneMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				polyethyleneRefl, NUM_PP_ConstProp);
		pvcMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				pvcRefl, NUM_PP_ConstProp);
		quartzMat->AddProperty( "RINDEX", photonEnergies, quartzRefractiveIndex,
				NUM_PP );
		quartzMat->AddProperty( "ABSLENGTH", photonEnergies,
				quartzAbsorption, NUM_PP );
		sapphireMat->AddProperty( "RINDEX", photonEnergies,
				sapphireRefractiveIndex, NUM_PP );
		sapphireMat->AddProperty( "ABSLENGTH", photonEnergies_ConstProp,
				sapphireAbsorption, NUM_PP_ConstProp );
		ss316Mat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				ss316Refl, NUM_PP_ConstProp );
		steelMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				steelRefl, NUM_PP_ConstProp );
		teflonMat->AddProperty( "RINDEX", photonEnergies, teflonRefractiveIndex, NUM_PP );
		teflonMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				teflonRefl, NUM_PP_ConstProp );
		titaniumMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				titaniumRefl, NUM_PP_ConstProp );
		tungstenMat->AddProperty( "REFLECTIVITY", photonEnergies_ConstProp,
				tungstenRefl, NUM_PP_ConstProp );
		waterMat->AddProperty( "RINDEX", waterPhotonEnergies,
				waterRefractiveIndex, nWaterEntries);
		waterMat->AddProperty( "ABSLENGTH", waterPhotonEnergies,
				waterAbsorption, nWaterEntries);
	}
	
}
