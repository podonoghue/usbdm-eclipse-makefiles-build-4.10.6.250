include ../Common.mk

PROGRAMMER_DEFS = -DTARGET='MC56F80xx -DFLASH_PROGRAMMER -DUSE_ICON'
GDI_DEFS        = -DTARGET='MC56F80xx -DGDI'
GDI_LEGACY_DEFS = -DTARGET='MC56F80xx -DGDI -DLEGACY'
GDB_DEFS        = -DTARGET='MC56F80xx -DGDB'

ifeq ($(UNAME_S),Windows)
# Windows version of Codewarrior packs structs
GDI_DEFS        = '-DPACK_STRUCTS=1 -DTARGET=MC56F80xx -DGDI'
endif

TARGET = DSC
target = dsc

$(TARGET)_FlashProgrammer:
	$(MAKE) exe -f ProgrammerTarget.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) MODULE=programmer CDEFS=$(PROGRAMMER_DEFS)

$(TARGET)_FlashProgrammer-debug:
	$(MAKE) exe -f ProgrammerTarget.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) MODULE=programmer CDEFS=$(PROGRAMMER_DEFS) DEBUG='Y'

usbdm-$(target)-gdi:
	$(MAKE) dll -f GdiTarget.mk        TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) MODULE=gdi        CDEFS=$(GDI_DEFS)

usbdm-$(target)-gdi-debug:
	$(MAKE) dll -f GdiTarget.mk        TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) MODULE=gdi        CDEFS=$(GDI_DEFS) DEBUG='Y'

usbdm-$(target)-gdi-legacy:
	$(MAKE) dll -f ../GdiLegacyTarget.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX)  MODULE=gdi-legacy CDEFS=$(GDI_LEGACY_DEFS)

usbdm-$(target)-gdi-legacy-debug:
	$(MAKE) dll -f ../GdiLegacyTarget.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX)  MODULE=gdi-legacy CDEFS=$(GDI_LEGACY_DEFS) DEBUG='Y'

allCommon: $(TARGET)_FlashProgrammer        $(TARGET)_FlashProgrammer-debug 
allCommon: usbdm-$(target)-gdi              usbdm-$(target)-gdi-debug

cleanCommon:
	${RMDIR} $(TARGET)_FlashProgrammer$(BUILDDIR_SUFFIX)
	${RMDIR} $(TARGET)_FlashProgrammer-debug$(BUILDDIR_SUFFIX)
	${RMDIR} usbdm-$(target)-gdi$(BUILDDIR_SUFFIX)
	${RMDIR} usbdm-$(target)-gdi-debug$(BUILDDIR_SUFFIX)
ifeq ($(UNAME_S),Windows)
allWindows: usbdm-$(target)-gdi-legacy usbdm-$(target)-gdi-legacy-debug$(BUILDDIR_SUFFIX)

cleanWindows:
	${RMDIR} usbdm-$(target)-gdi-legacy$(BUILDDIR_SUFFIX)
	${RMDIR} usbdm-$(target)-gdi-legacy-debug$(BUILDDIR_SUFFIX)
else
allWindows:
cleanWindows:
endif

all: allCommon allWindows

clean: cleanCommon cleanWindows

.PHONY: all clean test
.PHONY: allCommon allWindows cleanCommon cleanWIndows
.PHONY: $(TARGET)_FlashProgrammer $(TARGET)_FlashProgrammer-debug 
.PHONY: usbdm-$(target)-gdi       usbdm-$(target)-gdi-debug 
.PHONY: usbdm-$(target)-gdi-legacy usbdm-$(target)-gdi-legacy-debug

