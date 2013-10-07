include ../Common.mk

TARGET = MergeXML

$(TARGET):
	$(MAKE) exe -f Target.mk BUILDDIR=$@ CDEFS='-DUSE_ICON'

$(TARGET)-debug:
	$(MAKE) exe -f Target.mk BUILDDIR=$@  DEBUG='Y' CDEFS='-DUSE_ICON -DDEBUG'

all: $(TARGET) $(TARGET)-debug

clean:
	${RMDIR} $(TARGET)
	${RMDIR} $(TARGET)-debug
	
.PHONY: $(TARGET) $(TARGET)-debug all clean