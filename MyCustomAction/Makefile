include ../Common.mk

TARGET = MyCustomAction

$(TARGET):
	$(MAKE) dll -f Target.mk TARGET=$@ BUILDDIR=$@ CDEFS=

$(TARGET)-debug:
	$(MAKE) dll -f Target.mk TARGET=$@ BUILDDIR=$@ CDEFS= DEBUG="Y"

all: $(TARGET) $(TARGET)-debug

clean:
	${RMDIR} $(TARGET)
	${RMDIR} $(TARGET)-debug
	
.PHONY: $(TARGET) $(TARGET)-debug all clean