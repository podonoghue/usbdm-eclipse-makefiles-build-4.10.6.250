include ../Common.mk

CFVx_DEFS = -DTARGET=CFVx -DUSE_ICON -DUNLOCKER
DSC_DEFS  = -DTARGET=MC56F80xx -DUSE_ICON -DUNLOCKER

CFVx_Unlocker:
	$(MAKE) exe -f Target.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) CDEFS="$(CFVx_DEFS)"

CFVx_Unlocker-debug:
	$(MAKE) exe -f Target.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) CDEFS="$(CFVx_DEFS)" DEBUG="Y"

DSC_Unlocker:
	$(MAKE) exe -f Target.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) CDEFS="$(DSC_DEFS)"

DSC_Unlocker-debug:
	$(MAKE) exe -f Target.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) CDEFS="$(DSC_DEFS)" DEBUG="Y"

all: CFVx_Unlocker CFVx_Unlocker-debug DSC_Unlocker DSC_Unlocker-debug

test: CFVx_Unlocker-debug

clean:
	${RMDIR} CFVx_Unlocker$(BUILDDIR_SUFFIX)
	${RMDIR} CFVx_Unlocker-debug$(BUILDDIR_SUFFIX)
	${RMDIR} DSC_Unlocker$(BUILDDIR_SUFFIX)
	${RMDIR} DSC_Unlocker-debug$(BUILDDIR_SUFFIX)
	
.PHONY: all clean CFVx_Unlocker CFVx_Unlocker-debug DSC_Unlocker DSC_Unlocker-debug
