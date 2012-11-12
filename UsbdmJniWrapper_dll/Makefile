include ../Common.mk

target = UsbdmJniWrapper

$(target):
	$(MAKE) dll -f Target.mk BUILDDIR=$@ CDEFS=""

$(target)-debug:
	$(MAKE) dll -f Target.mk BUILDDIR=$@ CDEFS="" DEBUG="Y"

all: $(target) $(target)-debug

clean:
	${RMDIR} $(target)
	${RMDIR} $(target)-debug

.PHONY: all clean test $(target) $(target)-debug 