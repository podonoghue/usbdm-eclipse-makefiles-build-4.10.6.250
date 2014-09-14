include ../Common.mk

ifeq ($(UNAME_S),Windows)
VSUFFIX=.4
else
VSUFFIX=
endif

target   = arm
DLL_DEFS = -DTARGET=MC56F80xx -DDLL

usbdm-$(target):
	$(MAKE) dll -f Target.mk BUILDDIR=$@$(BUILDDIR_SUFFIX) TARGET=$@${VSUFFIX} CDEFS='$(DLL_DEFS)'

usbdm-$(target)-debug:
	$(MAKE) dll -f Target.mk BUILDDIR=$@$(BUILDDIR_SUFFIX) TARGET=$@${VSUFFIX} CDEFS='$(DLL_DEFS)' DEBUG='Y'

all: usbdm-$(target) usbdm-$(target)-debug #test

clean:
	${RMDIR} usbdm-$(target)$(BUILDDIR_SUFFIX)
	${RMDIR} usbdm-$(target)-debug$(BUILDDIR_SUFFIX)

.PHONY: all clean test usbdm-$(target) usbdm-$(target)-debug 