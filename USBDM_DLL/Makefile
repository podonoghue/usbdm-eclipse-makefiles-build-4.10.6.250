include ../Common.mk

ifeq ($(UNAME_S),Windows)
VSUFFIX=.4
else
VSUFFIX=
endif

usbdm:
	$(MAKE) dll -f Target.mk BUILDDIR=$@ TARGET=$@${VSUFFIX}     MODULE=usbdm      CDEFS="-DUSBDM_DLL_EXPORTS"

usbdm-debug:
	$(MAKE) dll -f Target.mk BUILDDIR=$@ TARGET=$@${VSUFFIX}     MODULE=usbdm      CDEFS="-DUSBDM_DLL_EXPORTS"  DEBUG='Y'

osbdm:
	$(MAKE) dll -f Target.mk BUILDDIR=$@ TARGET=osbdm-jm60       MODULE=osbdm      CDEFS="-DUSBDM_DLL_EXPORTS"

osbdm-debug:
	$(MAKE) dll -f Target.mk BUILDDIR=$@ TARGET=osbdm-jm60-debug MODULE=osbdm      CDEFS="-DUSBDM_DLL_EXPORTS"  DEBUG='Y'

usbdm-cff:
	$(MAKE) dll -f Target.mk BUILDDIR=$@ TARGET=$@               MODULE=cfflasher  CDEFS="-DUSBDM_DLL_EXPORTS"  LINK_OPTS="-Wl,--kill-at" 

usbdm-cff-debug:
	$(MAKE) dll -f Target.mk BUILDDIR=$@ TARGET=$@               MODULE=cfflasher  CDEFS="-DUSBDM_DLL_EXPORTS"  LINK_OPTS="-Wl,--kill-at"  DEBUG='Y'

allCommon: usbdm usbdm-debug

cleanCommon:
	${RMDIR} usbdm
	${RMDIR} usbdm-debug

ifeq ($(UNAME_S),Windows)
allWindows:osbdm osbdm-debug usbdm-cff usbdm-cff-debug

cleanWindows:
	${RMDIR} osbdm
	${RMDIR} osbdm-debug
	${RMDIR} usbdm-cff
	${RMDIR} usbdm-cff-debug
else
allWindows:
cleanWindows:
endif

all: allCommon allWindows

clean: cleanCommon cleanWindows

.PHONY: all clean 
.PHONY: allCommon allWindows cleanCommon cleanWindows
.PHONY: usbdm usbdm-debug 
.PHONY: osbdm osbdm-debug usbdm-cff usbdm-cff-debug
