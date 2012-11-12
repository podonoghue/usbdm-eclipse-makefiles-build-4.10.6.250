include ../Common.mk

TARGET = CreateCTestImage

$(TARGET):
	$(MAKE) exe -f Target.mk BUILDDIR=$@ CDEFS="-DUSE_ICON"

all: $(TARGET)

clean:
	${RMDIR} $(TARGET)
	
.PHONY: $(TARGET) all clean