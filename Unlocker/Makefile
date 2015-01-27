include ../Common.mk

CFVx_DEFS = -DTARGET=CFVx -DUSE_ICON -DUNLOCKER

CFVx_Unlocker:
	$(MAKE) exe -f Target.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) CDEFS="$(CFVx_DEFS)"

CFVx_Unlocker-debug:
	$(MAKE) exe -f Target.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) CDEFS="$(CFVx_DEFS)" DEBUG="Y"

all: CFVx_Unlocker CFVx_Unlocker-debug

test: CFVx_Unlocker-debug

clean:
	${RMDIR} CFVx_Unlocker$(BUILDDIR_SUFFIX)
	${RMDIR} CFVx_Unlocker-debug$(BUILDDIR_SUFFIX)
	
.PHONY: all clean CFVx_Unlocker CFVx_Unlocker-debug
