include ../Common.mk

TARGET = CreateFlashTestImage

$(TARGET):
	$(MAKE) exe -f Target.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) CDEFS='-DUSE_ICON'

all: $(TARGET)

clean:
	${RMDIR} $(TARGET)$(BUILDDIR_SUFFIX)
	
.PHONY: $(TARGET) all clean