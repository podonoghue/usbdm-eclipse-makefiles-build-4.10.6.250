include ../Common.mk

TARGET = JS16_Bootloader

$(TARGET):
	$(MAKE) exe -f Target.mk BUILDDIR=$@ CDEFS="-DUSE_ICON"

$(TARGET)-debug:
	$(MAKE) exe -f Target.mk BUILDDIR=$@ CDEFS="-DUSE_ICON" DEBUG="Y"

all: $(TARGET) $(TARGET)-debug

clean:
	${RMDIR} $(TARGET)
	${RMDIR} $(TARGET)-debug
	
.PHONY: $(TARGET) $(TARGET)-debug all clean