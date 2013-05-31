include ../Common.mk

ifeq ($(UNAME_S),Windows)
TARGET=usbdm-wxPlugin
else
TARGET=usbdm-wxPlugin
endif

$(TARGET):
	$(MAKE) dll -f Target.mk BUILDDIR=$@ CDEFS="-DWXPLUGIN_DLL_EXPORTS"

all: $(TARGET)

clean:
	${RMDIR} $(TARGET)

.PHONY: all clean $(TARGET)

	