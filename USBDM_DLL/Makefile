include ../Common.mk

VSUFFIX=
ifeq ($(UNAME_S),Windows)
   VSUFFIX=.4
   NAME=usbdm
endif

usbdm:
	$(MAKE) dll -f Target.mk BUILDDIR=$@$(BUILDDIR_SUFFIX) TARGET=$@${VSUFFIX}     MODULE=usbdm      CDEFS='-DUSBDM_DLL_EXPORTS'

usbdm-debug:
	$(MAKE) dll -f Target.mk BUILDDIR=$@$(BUILDDIR_SUFFIX) TARGET=$@${VSUFFIX}     MODULE=usbdm      CDEFS='-DUSBDM_DLL_EXPORTS'  DEBUG='Y'

osbdm:
	$(MAKE) dll -f Target.mk BUILDDIR=$@$(BUILDDIR_SUFFIX) TARGET=osbdm-jm60       MODULE=osbdm      CDEFS='-DUSBDM_DLL_EXPORTS'

osbdm-debug:
	$(MAKE) dll -f Target.mk BUILDDIR=$@$(BUILDDIR_SUFFIX) TARGET=osbdm-jm60-debug MODULE=osbdm      CDEFS='-DUSBDM_DLL_EXPORTS'  DEBUG='Y'

usbdm-cff:
	$(MAKE) dll -f Target.mk BUILDDIR=$@$(BUILDDIR_SUFFIX) TARGET=$@               MODULE=cfflasher  CDEFS='-DUSBDM_DLL_EXPORTS'  EXTRA_LINK_OPTS='-Wl,--kill-at' 

usbdm-cff-debug:
	$(MAKE) dll -f Target.mk BUILDDIR=$@$(BUILDDIR_SUFFIX) TARGET=$@               MODULE=cfflasher  CDEFS='-DUSBDM_DLL_EXPORTS'  EXTRA_LINK_OPTS='-Wl,--kill-at'  DEBUG='Y'

allCommon: usbdm usbdm-debug usbdm

cleanCommon:
	${RMDIR} usbdm$(BUILDDIR_SUFFIX)
	${RMDIR} usbdm-debug$(BUILDDIR_SUFFIX)

ifeq ($(UNAME_S),Windows)
allWindows:osbdm osbdm-debug usbdm-cff usbdm-cff-debug

cleanWindows:
	${RMDIR} osbdm$(BUILDDIR_SUFFIX)
	${RMDIR} osbdm-debug$(BUILDDIR_SUFFIX)
	${RMDIR} usbdm-cff$(BUILDDIR_SUFFIX)
	${RMDIR} usbdm-cff-debug$(BUILDDIR_SUFFIX)
else
allWindows:
cleanWindows:
endif

all: allCommon allWindows

clean: cleanCommon cleanWindows

test: usbdm-debug

.PHONY: all clean 
.PHONY: allCommon allWindows cleanCommon cleanWindows
.PHONY: usbdm usbdm-debug 
.PHONY: osbdm osbdm-debug usbdm-cff usbdm-cff-debug
.PHONY: test
