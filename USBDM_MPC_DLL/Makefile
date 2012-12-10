include ../Common.mk

target   = mpc
DLL_DEFS = -DTARGET=MPC56xx -DUSBDMMPC_DLL_EXPORTS

usbdm-$(target):
	$(MAKE) dll -f Target.mk BUILDDIR=$@ TARGET=$@.4 CDEFS="$(DLL_DEFS)"

usbdm-$(target)-debug:
	$(MAKE) dll -f Target.mk BUILDDIR=$@ TARGET=$@.4 CDEFS="$(DLL_DEFS)" DEBUG="Y"

test:
	$(MAKE) exe -f Target.mk BUILDDIR=$@ TARGET=$@ MODULE=$@ CDEFS="$(DLL_DEFS)"  DEBUG="Y"

all: usbdm-$(target) usbdm-$(target)-debug test

clean:
	${RMDIR} test
	${RMDIR} usbdm-$(target)
	${RMDIR} usbdm-$(target)-debug

.PHONY: all clean test usbdm-$(target) usbdm-$(target)-debug
