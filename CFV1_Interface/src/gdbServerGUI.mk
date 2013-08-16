# Build list for Socket-based GUI GDB server

# List source file to include from current directory
SRC += FlashProgramming.cpp
SRC += Version.rc

# Shared files $(SHARED_SRC)
VPATH := $(SHARED_SRC) $(VPATH)
INCS  += -I$(SHARED_SRC)
SRC += ApplicationFiles.cpp
SRC += AppSettings.cpp
SRC += ClockTrimming.cpp
SRC += DeviceData.cpp
SRC += DeviceXmlParser.cpp
SRC += DualString.cpp
SRC += Log.cpp
SRC += ProgressTimer.cpp
SRC += SimpleSRecords.cpp
SRC += Names.cpp
SRC += USBDM_AUX.cpp
SRC += Utils.cpp

# Shared files $(SHARED_SRC)/Programmer
VPATH := $(SHARED_SRC)/Programmer $(VPATH)
INCS  += -I$(SHARED_SRC)/Programmer
SRC += AdvancedPanel.cpp
SRC += InterfacePanel.cpp
SRC += Shared.cpp
SRC += TargetPanel.cpp
SRC += USBDMDialogue.cpp

# Shared files $(SHARED_SRC)/gdb
VPATH := $(SHARED_SRC)/gdb $(VPATH)
INCS  += -I$(SHARED_SRC)/gdb
SRC += GdbBreakpoints.cpp
SRC += GdbHandler.cpp
SRC += GdbInOut.cpp
SRC += GdbInOutWx.cpp
SRC += GdbMiscellaneous.cpp
SRC += GdbServerApp.cpp
SRC += GdbServerWindow.cpp
