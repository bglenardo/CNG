################################################################################
# GNUmakefile for the BaccSim tools
#
# Change log:
# 17 March 2010 - Initial submission (Melinda)
# 20 April 2010 - Added BaccExampleAnalysis (Melinda)
# 22 April 2010 - Added BaccRoot2Dat and a -gstabs for macosx to
#                 get rid of .dSYM bundles created on OS X (Michael Woods)
# 27 Sep 2010 - Added BaccExampleAnalysis and NMDAnalysis to the cleanup section
#		(Kareem)
# 14 Feb 2012 - Removed funny ^M newline characters, and added BaccAsciiReader
#		(Matthew)
# 15 Aug 2012 - Changed order of arguments and corrected LIBDIRS to match
#               needs of latest g++ (Rich)
################################################################################

CC			 = g++
CCFLAGS		 = -O2
INCLUDE		 = -I$(ROOTSYS)/include

ifeq ($(OSTYPE),darwin)
OSFLAGS	= -bind_at_load
endif

ifdef ROOTSYS
COMPILEJOBS	= BaccAsciiReader BaccRootReader BaccExampleAnalysis NMDAnalysis Bacc2evt
ROOTLIBS	= $(shell $(ROOTSYS)/bin/root-config --libs)
LIBDIRS		= -L$(shell $(ROOTSYS)/bin/root-config --libdir)
INCLUDE		= -I$(shell $(ROOTSYS)/bin/root-config --incdir)
LDFLAGS		= $(shell $(ROOTSYS)/bin/root-config --ldflags)
PLATFORM	= $(shell $(ROOTSYS)/bin/root-config --platform)
OBJLIST		= BaccAsciiReader.o BaccRootReader.o BaccExampleAnalysis.o NMDAnalysis.o
endif

ALLFLAGS	= $(CCFLAGS) $(LDFLAGS) $(OSFLAGS) $(INCLUDE)
ALLLIBS		= $(LIBDIRS) $(ROOTLIBS)

All:		$(COMPILEJOBS)

BaccAsciiReader:		BaccAsciiReader.cc
			$(CC) BaccAsciiReader.cc $(ALLFLAGS) $(ALLLIBS) -o BaccAsciiReader

BaccRootReader:          BaccRootReader.cc
			$(CC) BaccRootReader.cc $(ALLFLAGS) $(ALLLIBS) -o BaccRootReader

BaccExampleAnalysis:	BaccExampleAnalysis.cc
			$(CC)  BaccExampleAnalysis.cc $(ALLFLAGS) $(ALLLIBS) -o BaccExampleAnalysis

NMDAnalysis:		NMDAnalysis.cc
			$(CC) NMDAnalysis.cc $(ALLFLAGS) $(ALLLIBS) -o NMDAnalysis

.PHONY: BaccSim2evt
BaccSim2evt:		
			@cd BaccSim2evt && make #-C BaccSim2evt
			@#cd BaccSim2evt && make -B

neat:
		rm -rf *.o

cleanup:
		rm -rf *.o BaccAsciiReader BaccRootReader BaccExampleAnalysis NMDAnalysis BaccSim2evt/BaccSim2evt


