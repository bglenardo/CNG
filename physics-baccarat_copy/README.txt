################################################################################
# README file for the BACCARAT package                                         #
#                                                                              #
# Change log:                                                                  #
# 2009-03-18 - Initial submission, Kareem Kazkaz                               #
# 2014-05-01 - Rewritten for BACCARAT instead of LUXSim                        #
################################################################################
README for BACCARAT

The BACCARAT detector simulation essetially grew out of the simulation for the 
LUX experiment, LUXSim.  The documentation for LUXSim is on the LUX TWiki, 
available at:
http://teacher.pas.rochester.edu:8080/wiki/bin/view/Lux/LUXSim_SimulationDocumentation

Right now the documentation for BACCARAT is rather spare, but we hope to make a 
simlar wiki page for BACCARAT.  We may also decide to just distribute a pdf with
the GIT repo.  When it is done, the documentation will be a comprehensive list 
of the macro commands available in BACCARAT.

The current version of GEANT4 used for the simulation is GEANT4.9.4. It may work
with other versions, but this is the supported version. If you want to use other
versions, support will be given as time and energy allows.

To compile LUXSim, type "make" from within the top-level LUXSim directory. It
should all work, either on Linux or MacOSX machines. If you have a Windows box,
support will be given as time and energy allows.

The are two readers available for the output data of LUXSim, and these are 
being ported over to BACCARAT.  The ROOT reader has been sucessfully ported over
and tested.  There is also a MATLAB reader coming soon.  For these readers to 
work, you should of course have either ROOT or MATLAB installed on your 
computer.

There are several example geometries included with BACCARAT to help the user get
started.  The process of adding your own geometry is quite simple:
 * New geometry code is defined in the "geometry" subdirectory, the actual
   geometry definition code should be in "NewDetectorClass::BuildDetector()"
 * When defining your geometry code, make sure that the outermost volume in your
   code is defined only as a G4LogicalVolume, named "logicalVolume."  This 
   object is initialized outside of your geometry code.
 * Your new geometry class must be registered in 
   "BaccDetectorConstruction::BacDetectorConstruction()" in the section of this 
   file with the list of detectors in a series of "push_back()" statements.  Do
   not forget to add the "#include" statement for your code to 
   BaccDetectorConstruction.cc so that the rest of BACCARAT can find it.

Victor M. Gehman
vmgehman@lbl.gov
