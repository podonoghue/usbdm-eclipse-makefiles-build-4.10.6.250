include ../Common.mk

TARGET = MergeXML

Version.o : src/Version.rc src/uacManifest.xml
	@echo -- Building $@ from $<
	$(WINDRES) $< $(DEFS) $(INCS) -o $@

$(TARGET): Version.o
	$(MAKE) exe -f Target.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) CDEFS='-DUSE_ICON'

$(TARGET)-debug: Version.o
	$(MAKE) exe -f Target.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX)  DEBUG='Y' CDEFS='-DUSE_ICON -DDEBUG'

all: $(TARGET) $(TARGET)-debug

clean:
	${RMDIR} $(TARGET)$(BUILDDIR_SUFFIX)
	${RMDIR} $(TARGET)-debug$(BUILDDIR_SUFFIX)
	
.PHONY: $(TARGET) $(TARGET)-debug all clean