include ../Common.mk

VSUFFIX=
ifeq ($(UNAME_S),Windows)
   VSUFFIX=.4
   NAME=usbdm
endif

target   = dsc
DLL_DEFS = -DTARGET=MC56F80xx -DUSBDMDSC_DLL_EXPORTS

usbdm-$(target):
	$(MAKE) dll -f Target.mk BUILDDIR=$@$(BUILDDIR_SUFFIX) TARGET=$@${VSUFFIX} CDEFS='$(DLL_DEFS)'

usbdm-$(target)-debug:
	$(MAKE) dll -f Target.mk BUILDDIR=$@$(BUILDDIR_SUFFIX) TARGET=$@${VSUFFIX} CDEFS='$(DLL_DEFS)' DEBUG='Y'

test:
	$(MAKE) exe -f Target.mk BUILDDIR=$@$(BUILDDIR_SUFFIX) TARGET=$@ MODULE=$@ CDEFS='$(DLL_DEFS)'  DEBUG='Y'

all: usbdm-$(target) usbdm-$(target)-debug #test

clean:
	${RMDIR} test$(BUILDDIR_SUFFIX)
	${RMDIR} usbdm-$(target)$(BUILDDIR_SUFFIX)
	${RMDIR} usbdm-$(target)-debug$(BUILDDIR_SUFFIX)

.PHONY: all clean test usbdm-$(target) usbdm-$(target)-debug
