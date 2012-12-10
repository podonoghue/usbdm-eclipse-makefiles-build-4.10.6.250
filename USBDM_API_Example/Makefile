# BUILDDIR - Where to build target files
# TARGET   - Root name of final target (default to BUILDDIR)
# MODULE   - Name of make file in source directory listing files included in build
# CDEFS    - C defines to add to CFLAGS
# target   - either 'dll' or 'exe'

include Common.mk

TARGET = USBDM_API_Example

$(TARGET):
	$(MAKE) exe -f Target.mk BUILDDIR=$@ CDEFS="-DUSE_ICON"

$(TARGET)-debug:
	$(MAKE) exe -f Target.mk BUILDDIR=$@ CDEFS="-DUSE_ICON" DEBUG="Y"

all: $(TARGET) $(TARGET)-debug

clean:
	$(MAKE) clean -f Target.mk BUILDDIR=$(TARGET)
	$(MAKE) clean -f Target.mk BUILDDIR=$(TARGET)-debug
	
.PHONY: $(TARGET) $(TARGET)-debug all clean