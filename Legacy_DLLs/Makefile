include ../Common.mk

tbdml:
	$(MAKE) dll -f Target.mk BUILDDIR=$@ TARGET=$@ MODULE=tbdml CDEFS="-DLEGACY_DLL_EXPORTS -DTBDML -DGDI"

tbdml-debug:
	$(MAKE) dll -f Target.mk BUILDDIR=$@ TARGET=$@ MODULE=tbdml CDEFS="-DLEGACY_DLL_EXPORTS -DTBDML -DGDI" DEBUG='Y'

opensourcebdm:
	$(MAKE) dll -f Target.mk BUILDDIR=$@ TARGET=opensourcebdm MODULE=osbdm CDEFS="-DLEGACY_DLL_EXPORTS -DOSBDM -DGDI"

opensourcebdm-debug:
	$(MAKE) dll -f Target.mk BUILDDIR=$@ TARGET=$@ MODULE=osbdm CDEFS="-DLEGACY_DLL_EXPORTS -DOSBDM -DGDI" DEBUG='Y'

all: tbdml tbdml-debug opensourcebdm opensourcebdm-debug

clean:
	${RMDIR} tbdml
	${RMDIR} tbdml-debug
	${RMDIR} opensourcebdm
	${RMDIR} opensourcebdm-debug

.PHONY: all clean 
.PHONY: tbdml tbdml-debug
.PHONY: opensourcebdm opensourcebdm-debug
