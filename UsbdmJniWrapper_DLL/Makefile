include ../Common.mk

TARGET = UsbdmJniWrapper

BUILDDIR_SUFFIX=

ifeq ($(UNAME_S),Windows)
   VSUFFIX=.4
   NAME=usbdm
else
   ifeq ($(BITNESS),32)
      BUILDDIR_SUFFIX=.i386
   endif
   ifeq ($(BITNESS),64)
      BUILDDIR_SUFFIX=.x86_64
   endif
endif

$(TARGET):
	$(MAKE) dll -f Target.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) CDEFS=

$(TARGET)-debug:
	$(MAKE) dll -f Target.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) CDEFS= DEBUG="Y"

all: $(TARGET) $(TARGET)-debug

clean:
	${RMDIR} $(TARGET)$(BUILDDIR_SUFFIX)
	${RMDIR} $(TARGET)-debug$(BUILDDIR_SUFFIX)

.PHONY: all clean test $(TARGET) $(TARGET)-debug 