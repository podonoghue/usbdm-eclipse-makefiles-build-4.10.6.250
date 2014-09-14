include ../Common.mk

TARGET = ARM
target = arm

$(TARGET)_FlashProgrammer:
	$(MAKE) exe -f ../ProgrammerTarget.mk   TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) MODULE=programmer        CDEFS='$(PROGRAMMER_DEFS)'

$(TARGET)_FlashProgrammer-debug:
	$(MAKE) exe -f ../ProgrammerTarget.mk   TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) MODULE=programmer        CDEFS='$(PROGRAMMER_DEFS)' DEBUG='Y'

$(TARGET)_GDBServer:
	$(MAKE) exe -f ../GdbServerGuiTarget.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) MODULE=gdbServerGUI      CDEFS='$(GDB_SERVER_DEFS)'

$(TARGET)_GDBServer-debug:
	$(MAKE) exe -f ../GdbServerGuiTarget.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) MODULE=gdbServerGUI      CDEFS='$(GDB_SERVER_DEFS)' DEBUG='Y'

usbdm-$(target)-gdi:
	$(MAKE) dll -f ../GdiTarget.mk          TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) MODULE=gdi               CDEFS='$(GDI_DEFS)'

usbdm-$(target)-gdi-debug:
	$(MAKE) dll -f ../GdiTarget.mk          TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) MODULE=gdi               CDEFS='$(GDI_DEFS)' DEBUG='Y'

usbdm-$(target)-gdbPipeServer:
	$(MAKE) exe -f ../GdbTarget.mk          TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) MODULE=gdbPipe        	CDEFS='$(GDB_DEFS)' 

usbdm-$(target)-gdbPipeServer-debug:
	$(MAKE) exe -f ../GdbTarget.mk          TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) MODULE=gdbPipe        	CDEFS='$(GDB_DEFS)' DEBUG='Y'

usbdm-$(target)-gdbSocketServer:
	$(MAKE) exe -f ../GdbTarget.mk          TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) MODULE=gdbSocket  		CDEFS='$(GDB_DEFS)' 

usbdm-$(target)-gdbSocketServer-debug:
	$(MAKE) exe -f ../GdbTarget.mk          TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) MODULE=gdbSocket  		CDEFS='$(GDB_DEFS)' DEBUG='Y'

allCommon: $(TARGET)_FlashProgrammer        $(TARGET)_FlashProgrammer-debug 
allCommon: $(TARGET)_GDBServer              $(TARGET)_GDBServer-debug
allCommon: usbdm-$(target)-gdi              usbdm-$(target)-gdi-debug
allCommon: usbdm-$(target)-gdbPipeServer    usbdm-$(target)-gdbPipeServer-debug
allCommon: usbdm-$(target)-gdbSocketServer  usbdm-$(target)-gdbSocketServer-debug

cleanCommon:
	${RMDIR} $(TARGET)_FlashProgrammer$(BUILDDIR_SUFFIX)
	${RMDIR} $(TARGET)_FlashProgrammer-debug$(BUILDDIR_SUFFIX)
	${RMDIR} $(TARGET)_GDBServer$(BUILDDIR_SUFFIX)
	${RMDIR} $(TARGET)_GDBServer-debug$(BUILDDIR_SUFFIX)
	${RMDIR} usbdm-$(target)-gdi$(BUILDDIR_SUFFIX)
	${RMDIR} usbdm-$(target)-gdi-debug$(BUILDDIR_SUFFIX)
	${RMDIR} usbdm-$(target)-gdbPipeServer$(BUILDDIR_SUFFIX)
	${RMDIR} usbdm-$(target)-gdbPipeServer-debug$(BUILDDIR_SUFFIX)
	${RMDIR} usbdm-$(target)-gdbSocketServer$(BUILDDIR_SUFFIX)
	${RMDIR} usbdm-$(target)-gdbSocketServer-debug$(BUILDDIR_SUFFIX)

all: allCommon allWindows

# used for quick test builds
#Test: $(TARGET)_FlashProgrammer-debug
#Test: usbdm-$(target)-gdi-debug
#Test: usbdm-$(target)-gdbPipeServer-debug usbdm-$(target)-gdbPipeServer
#Test: usbdm-$(target)-gdbPipeServer-debug usbdm-$(target)-gdbSocketServer
#Test: usbdm-$(target)-gdbPipeServer-debug
#Test: $(TARGET)_GDBServer-debug usbdm-$(target)-gdbSocketServer-debug usbdm-$(target)-gdbPipeServer-debug 
#Test: usbdm-$(target)-gdbPipeServer-debug
#Test: usbdm-$(target)-gdbSocketServer-debug
#Test: usbdm-$(target)-gdbPipeServer-debug usbdm-$(target)-gdbSocketServer
#Test: $(TARGET)_FlashProgrammer-debug
Test: $(TARGET)_GDBServer-debug 
#Test: $(TARGET)_GDBServer-debug $(TARGET)_FlashProgrammer-debug

clean: cleanCommon

.PHONY: all clean test
.PHONY: allCommon allWindows cleanCommon cleanWIndows
.PHONY: $(TARGET)_FlashProgrammer $(TARGET)_FlashProgrammer-debug 
.PHONY: $(TARGET)_GDBServer $(TARGET)_GDBServer-debug 
.PHONY: usbdm-$(target)-gdi       usbdm-$(target)-gdi-debug 
.PHONY: usbdm-$(target)-gdbPipeServer usbdm-$(target)-gdbPipeServer-debug
.PHONY: usbdm-$(target)-gdbSocketServer usbdm-$(target)-gdbSocketServer-debug
.PHONY: usbdm-$(target)-gdbSocketServer usbdm-$(target)-gdbSocketServer-debug
