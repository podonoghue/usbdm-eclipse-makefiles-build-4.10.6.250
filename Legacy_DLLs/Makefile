include ../Common.mk

tbdml:
	$(MAKE) dll -f Target.mk BUILDDIR=$@$(BUILDDIR_SUFFIX) TARGET=$@ MODULE=tbdml CDEFS='-DLEGACY_DLL_EXPORTS -DTBDML -DGDI'

tbdml-debug:
	$(MAKE) dll -f Target.mk BUILDDIR=$@$(BUILDDIR_SUFFIX) TARGET=$@ MODULE=tbdml CDEFS='-DLEGACY_DLL_EXPORTS -DTBDML -DGDI' DEBUG='Y'

opensourcebdm:
	$(MAKE) dll -f Target.mk BUILDDIR=$@ $(BUILDDIR_SUFFIX)TARGET=opensourcebdm MODULE=osbdm CDEFS='-DLEGACY_DLL_EXPORTS -DOSBDM -DGDI'

opensourcebdm-debug:
	$(MAKE) dll -f Target.mk BUILDDIR=$@$(BUILDDIR_SUFFIX) TARGET=$@ MODULE=osbdm CDEFS='-DLEGACY_DLL_EXPORTS -DOSBDM -DGDI' DEBUG='Y'

all: tbdml tbdml-debug opensourcebdm opensourcebdm-debug

clean:
	${RMDIR} tbdml$(BUILDDIR_SUFFIX)
	${RMDIR} tbdml-debug$(BUILDDIR_SUFFIX)
	${RMDIR} opensourcebdm$(BUILDDIR_SUFFIX)
	${RMDIR} opensourcebdm-debug$(BUILDDIR_SUFFIX)

.PHONY: all clean 
.PHONY: tbdml tbdml-debug
.PHONY: opensourcebdm opensourcebdm-debug
