include ../Common.mk

VSUFFIX=
ifeq ($(UNAME_S),Windows)
   TARGET=usbdm-wxPlugin
   VSUFFIX=.4
   NAME=usbdm
else
   TARGET=usbdm-wx
endif

export TARGET

$(TARGET):
	$(MAKE) dll -f Target.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) CDEFS="-DWXPLUGIN_DLL_EXPORTS"

all: $(TARGET)

clean:
	${RMDIR} $(TARGET)$(BUILDDIR_SUFFIX)

.PHONY: all clean $(TARGET)

	
