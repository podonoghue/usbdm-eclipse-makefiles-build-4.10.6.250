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
	$(MAKE) exe -f ProgrammerTarget.mk BUILDDIR=$@ MODULE=programmer CDEFS=$(PROGRAMMER_DEFS)

$(TARGET)_FlashProgrammer-debug:
	$(MAKE) exe -f ProgrammerTarget.mk BUILDDIR=$@ MODULE=programmer CDEFS=$(PROGRAMMER_DEFS) DEBUG='Y'

usbdm-$(target)-gdi:
	$(MAKE) dll -f GdiTarget.mk        BUILDDIR=$@ MODULE=gdi        CDEFS=$(GDI_DEFS)

usbdm-$(target)-gdi-debug:
	$(MAKE) dll -f GdiTarget.mk        BUILDDIR=$@ MODULE=gdi        CDEFS=$(GDI_DEFS) DEBUG='Y'

usbdm-$(target)-gdi-legacy:
	$(MAKE) dll -f ../GdiLegacyTarget.mk BUILDDIR=$@  MODULE=gdi-legacy CDEFS=$(GDI_LEGACY_DEFS)

usbdm-$(target)-gdi-legacy-debug:
	$(MAKE) dll -f ../GdiLegacyTarget.mk BUILDDIR=$@  MODULE=gdi-legacy CDEFS=$(GDI_LEGACY_DEFS) DEBUG='Y'

allCommon: $(TARGET)_FlashProgrammer        $(TARGET)_FlashProgrammer-debug 
allCommon: usbdm-$(target)-gdi              usbdm-$(target)-gdi-debug

cleanCommon:
	${RMDIR} $(TARGET)_FlashProgrammer
	${RMDIR} $(TARGET)_FlashProgrammer-debug
	${RMDIR} usbdm-$(target)-gdi
	${RMDIR} usbdm-$(target)-gdi-debug

ifeq ($(UNAME_S),Windows)
allWindows: usbdm-$(target)-gdi-legacy usbdm-$(target)-gdi-legacy-debug

cleanWindows:
	${RMDIR} usbdm-$(target)-gdi-legacy
	${RMDIR} usbdm-$(target)-gdi-legacy-debug
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

