include ../Common.mk

TARGET = ARM
target = arm

$(TARGET)_FlashProgrammer:
	$(MAKE) exe -f ../ProgrammerTarget.mk BUILDDIR=$@ MODULE=programmer CDEFS="$(PROGRAMMER_DEFS)"

$(TARGET)_FlashProgrammer-debug:
	$(MAKE) exe -f ../ProgrammerTarget.mk BUILDDIR=$@ MODULE=programmer CDEFS="$(PROGRAMMER_DEFS)" DEBUG='Y'

usbdm-$(target)-gdi:
	$(MAKE) dll -f ../GdiTarget.mk        BUILDDIR=$@ MODULE=gdi        CDEFS="$(GDI_DEFS)"

usbdm-$(target)-gdi-debug:
	$(MAKE) dll -f ../GdiTarget.mk        BUILDDIR=$@ MODULE=gdi        CDEFS="$(GDI_DEFS)" DEBUG='Y'

usbdm-$(target)-gdbServer:
	$(MAKE) exe -f ../GdbTarget.mk        BUILDDIR=$@ MODULE=gdb        CDEFS="$(GDB_DEFS)" 

usbdm-$(target)-gdbServer-debug:
	$(MAKE) exe -f ../GdbTarget.mk        BUILDDIR=$@ MODULE=gdb        CDEFS="$(GDB_DEFS)" DEBUG='Y'

allCommon: $(TARGET)_FlashProgrammer $(TARGET)_FlashProgrammer-debug usbdm-$(target)-gdi usbdm-$(target)-gdi-debug

cleanCommon:
	${RMDIR} $(TARGET)_FlashProgrammer
	${RMDIR} $(TARGET)_FlashProgrammer-debug
	${RMDIR} usbdm-$(target)-gdi
	${RMDIR} usbdm-$(target)-gdi-debug

ifeq ($(UNAME_S),Windows)
allWindows: usbdm-$(target)-gdbServer usbdm-$(target)-gdbServer-debug

cleanWindows:
	${RMDIR} usbdm-$(target)-gdbServer
	${RMDIR} usbdm-$(target)-gdbServer-debug
else
allWindows:
cleanWindows:
endif

all: allCommon allWindows

clean: cleanCommon cleanWindows

.PHONY: all clean 
.PHONY: allCommon allWindows cleanCommon cleanWIndows
.PHONY: $(TARGET)_FlashProgrammer $(TARGET)_FlashProgrammer-debug 
.PHONY: usbdm-$(target)-gdi       usbdm-$(target)-gdi-debug 
.PHONY: usbdm-$(target)-gdbServer usbdm-$(target)-gdbServer-debug
