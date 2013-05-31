include ../Common.mk

EXE_DEFS = "-DUSE_ICON -DINTERACTIVE"

ifeq ($(UNAME_S),Windows)
USBDM_TCL = UsbdmTCL
VER_SUFFIX = .4
else
USBDM_TCL = usbdm-tcl
VER_SUFFIX = 
endif
UsbdmScript:
	$(MAKE) exe -f Target.mk BUILDDIR=$@ CDEFS=$(EXE_DEFS)

UsbdmScript-debug:
	$(MAKE) exe -f Target.mk BUILDDIR=$@ CDEFS=$(EXE_DEFS) DEBUG="Y"

$(USBDM_TCL):
	$(MAKE) dll -f Target.mk BUILDDIR=$@ TARGET=$@$(VER_SUFFIX) CDEFS="-DUSBDM_TCL_DLL_EXPORTS"

$(USBDM_TCL)-debug:
	$(MAKE) dll -f Target.mk BUILDDIR=$@ TARGET=$@$(VER_SUFFIX) CDEFS="-DUSBDM_TCL_DLL_EXPORTS" DEBUG="Y"

all: UsbdmScript UsbdmScript-debug $(USBDM_TCL) $(USBDM_TCL)-debug

clean:
	${RMDIR} UsbdmScript
	${RMDIR} UsbdmScript-debug
	${RMDIR} $(USBDM_TCL)
	${RMDIR} $(USBDM_TCL)-debug

.PHONY: all clean
.PHONY: UsbdmScript UsbdmScript-debug $(USBDM_TCL) $(USBDM_TCL)-debug