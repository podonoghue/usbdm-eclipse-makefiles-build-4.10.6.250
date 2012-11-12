include ../Common.mk

EXE_DEFS = "-DUSE_ICON -DINTERACTIVE"

UsbdmScript:
	$(MAKE) exe -f Target.mk BUILDDIR=$@ CDEFS=$(EXE_DEFS)

UsbdmScript-debug:
	$(MAKE) exe -f Target.mk BUILDDIR=$@ CDEFS=$(EXE_DEFS) DEBUG="Y"

UsbdmTCL:
	$(MAKE) dll -f Target.mk BUILDDIR=$@ TARGET=$@.4 CDEFS="-DUSBDM_TCL_DLL_EXPORTS"

UsbdmTCL-debug:
	$(MAKE) dll -f Target.mk BUILDDIR=$@ TARGET=$@.4 CDEFS="-DUSBDM_TCL_DLL_EXPORTS" DEBUG="Y"

all: UsbdmScript UsbdmScript-debug UsbdmTCL UsbdmTCL-debug

clean:
	${RMDIR} UsbdmScript
	${RMDIR} UsbdmScript-debug
	${RMDIR} UsbdmTCL
	${RMDIR} UsbdmTCL-debug

.PHONY: all clean
.PHONY: UsbdmScript UsbdmScript-debug UsbdmTCL UsbdmTCL-debug