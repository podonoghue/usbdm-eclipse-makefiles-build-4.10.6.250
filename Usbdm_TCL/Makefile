include ../Common.mk

EXE_DEFS ='-DUSE_ICON -DINTERACTIVE'
DLL_DEFS ='-DUSBDM_TCL_DLL_EXPORTS'

ifeq ($(UNAME_S),Windows)
   USBDM_TCL = UsbdmTCL
   VER_SUFFIX = .4
else
   USBDM_TCL = usbdm-tcl
   VER_SUFFIX = 
endif

UsbdmScript:
	$(MAKE) exe -f Target.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) CDEFS=$(EXE_DEFS)

UsbdmScript-debug:
	$(MAKE) exe -f Target.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) CDEFS=$(EXE_DEFS) DEBUG='Y'

$(USBDM_TCL):
	$(MAKE) dll -f Target.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) TARGET=$@$(VER_SUFFIX) CDEFS=$(DLL_DEFS) 

$(USBDM_TCL)-debug:
	$(MAKE) dll -f Target.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) TARGET=$@$(VER_SUFFIX) CDEFS=$(DLL_DEFS) DEBUG='Y'

all: UsbdmScript UsbdmScript-debug $(USBDM_TCL) $(USBDM_TCL)-debug

test: $(USBDM_TCL) $(USBDM_TCL)-debug

clean:
	${RMDIR} UsbdmScript$(BUILDDIR_SUFFIX)
	${RMDIR} UsbdmScript-debug$(BUILDDIR_SUFFIX)
	${RMDIR} $(USBDM_TCL)$(BUILDDIR_SUFFIX)
	${RMDIR} $(USBDM_TCL)-debug$(BUILDDIR_SUFFIX)

.PHONY: all clean
.PHONY: UsbdmScript UsbdmScript-debug $(USBDM_TCL) $(USBDM_TCL)-debug
