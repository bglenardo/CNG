################################################################################
# GNUmakefile for the overall Bacc package
#
# Change log:
# 18 March 2009 - Initial submission (Kareem)
# 17 March 2010 - Added make commands for the tools directory (Kareem)
#
################################################################################

SUBDIRS = generator geometry io management physicslist processing
G4LIB_BUILD_SHARED =

.PHONY: makeall clean

makeall:
	@echo "********************************************************************************"
	@echo " Building BACCARAT"
	@echo "********************************************************************************"
	@for dir in $(SUBDIRS); do (echo; echo; echo Building $$dir...; cd $$dir; $(MAKE) "SUBDIRS=$(SUBDIRS)"); done
	@echo; echo; echo Building tools...; cd tools; $(MAKE); cd ..
	@echo
	@echo
	@echo Building BACCARAT...
	@echo
	@echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	@echo
	@echo Do not be worried about errors from ls not finding lib*.a or lib*.so files.
	@echo These warnings are known. If the simulation compiles and you see \"... Done!\"
	@echo as the last line, you\'re golden.
	@echo
	@cd BACCARAT; $(MAKE) "SUBDIRS=$(SUBDIRS)"
	@cd ..
	@rm -f BACCARATExecutable
	@ln -s BACCARAT/bin/$(G4SYSTEM)/BACCARAT ./BACCARATExecutable

clean:
	@for dir in $(SUBDIRS); do (echo; echo; echo Cleaning $$dir...; cd $$dir; $(MAKE) cleanup); done
	@echo; echo; echo Cleaning tools...; cd tools; $(MAKE) cleanup; cd ..
	@echo
	@echo
	@echo Cleaning Bacc...
	rm -rf Bacc/bin Bacc/tmp
	@echo Cleaning libraries and executable...
	rm -rf BaccLibraries
	rm -f BACCARATExecutable
	@echo Removing extraneous, system-dependent files
	@rm -rf $(shell find . -name .DS_Store)
	@rm -rf $(shell find . -name ._\*)	
	@rm -rf $(shell find . -name g4_\*.wrl)

archive: clean
	@cd ..; tar zcvf Bacc.tgz Bacc
