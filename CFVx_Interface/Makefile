include ../Common.mk

TARGET = CFVx
target = cfvx

$(TARGET)_FlashProgrammer:
	$(MAKE) exe -f ../ProgrammerTarget.mk BUILDDIR=$@ MODULE=programmer CDEFS="$(PROGRAMMER_DEFS)"

$(TARGET)_FlashProgrammer-debug:
	$(MAKE) exe -f ../ProgrammerTarget.mk BUILDDIR=$@ MODULE=programmer CDEFS="$(PROGRAMMER_DEFS)" DEBUG='Y'

usbdm-$(target)-gdi:
	$(MAKE) dll -f ../GdiTarget.mk        BUILDDIR=$@ MODULE=gdi        CDEFS="$(GDI_DEFS)"

usbdm-$(target)-gdi-debug:
	$(MAKE) dll -f ../GdiTarget.mk        BUILDDIR=$@ MODULE=gdi        CDEFS="$(GDI_DEFS)" DEBUG='Y'

usbdm-$(target)-gdi-legacy:
	$(MAKE) dll -f ../GdiLegacyTarget.mk BUILDDIR=$@  MODULE=gdi-legacy CDEFS="$(GDI_LEGACY_DEFS)"

usbdm-$(target)-gdi-legacy-debug:
	$(MAKE) dll -f ../GdiLegacyTarget.mk BUILDDIR=$@  MODULE=gdi-legacy CDEFS="$(GDI_LEGACY_DEFS)" DEBUG='Y'

usbdm-$(target)-gdbServer:
	$(MAKE) exe -f ../GdbTarget.mk        BUILDDIR=$@ MODULE=gdb        CDEFS="$(GDB_DEFS)" 

usbdm-$(target)-gdbServer-debug:
	$(MAKE) exe -f ../GdbTarget.mk        BUILDDIR=$@ MODULE=gdb        CDEFS="$(GDB_DEFS)" DEBUG='Y'

allCommon: $(TARGET)_FlashProgrammer $(TARGET)_FlashProgrammer-debug 
allCommon: usbdm-$(target)-gdi usbdm-$(target)-gdi-debug
allCommon: usbdm-$(target)-gdbServer usbdm-$(target)-gdbServer-debug
ifeq ($(UNAME_S),Windows)
allCommon: usbdm-$(target)-gdi-legacy usbdm-$(target)-gdi-legacy-debug
endif

cleanCommon:
	${RMDIR} $(TARGET)_FlashProgrammer
	${RMDIR} $(TARGET)_FlashProgrammer-debug
	${RMDIR} usbdm-$(target)-gdi
	${RMDIR} usbdm-$(target)-gdi-debug
	${RMDIR} usbdm-$(target)-gdbServer
	${RMDIR} usbdm-$(target)-gdbServer-debug
ifeq ($(UNAME_S),Windows)
	${RMDIR} usbdm-$(target)-gdi-legacy
	${RMDIR} usbdm-$(target)-gdi-legacy-debug
endif

all: allCommon

# used for quick test builds
#Test: $(TARGET)_FlashProgrammer-debug
Test: usbdm-$(target)-gdi-debug
#Test: usbdm-$(target)-gdbServer-debug

clean: cleanCommon

.PHONY: all clean test
.PHONY: allCommon allWindows cleanCommon cleanWIndows
.PHONY: $(TARGET)_FlashProgrammer $(TARGET)_FlashProgrammer-debug 
.PHONY: usbdm-$(target)-gdi       usbdm-$(target)-gdi-debug 
.PHONY: usbdm-$(target)-gdbServer usbdm-$(target)-gdbServer-debug
.PHONY: usbdm-$(target)-gdi-legacy usbdm-$(target)-gdi-legacy-debug

