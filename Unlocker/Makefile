include ../Common.mk

CFVx_DEFS = -DTARGET=CFVx -DUSE_ICON
DSC_DEFS  = -DTARGET=MC56F80xx -DUSE_ICON

CFVx_Unlocker:
	$(MAKE) exe -f Target.mk BUILDDIR=$@ CDEFS="$(CFVx_DEFS)"

CFVx_Unlocker-debug:
	$(MAKE) exe -f Target.mk BUILDDIR=$@ CDEFS="$(CFVx_DEFS)" DEBUG="Y"

DSC_Unlocker:
	$(MAKE) exe -f Target.mk BUILDDIR=$@ CDEFS="$(DSC_DEFS)"

DSC_Unlocker-debug:
	$(MAKE) exe -f Target.mk BUILDDIR=$@ CDEFS="$(DSC_DEFS)" DEBUG="Y"

all: CFVx_Unlocker CFVx_Unlocker-debug DSC_Unlocker DSC_Unlocker-debug

clean:
	${RMDIR} CFVx_Unlocker
	${RMDIR} CFVx_Unlocker-debug
	${RMDIR} DSC_Unlocker
	${RMDIR} DSC_Unlocker-debug
	
.PHONY: all clean CFVx_Unlocker CFVx_Unlocker-debug DSC_Unlocker DSC_Unlocker-debug
