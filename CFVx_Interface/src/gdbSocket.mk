# Build list for Socket-based command-line GDB server (obsolete)

# List source file to include from current directory
SRC += FlashProgramming.cpp
SRC += Version.rc

# Shared files $(SHARED_SRC)
VPATH := $(SHARED_SRC) $(VPATH)
INCS  += -I$(SHARED_SRC)
SRC += ApplicationFiles.cpp
SRC += AppSettings.cpp
SRC += DeviceData.cpp
SRC += DeviceXmlParser.cpp
SRC += DualString.cpp
SRC += Log.cpp
SRC += ProgressTimer.cpp
SRC += SimpleSRecords.cpp
SRC += Names.cpp
SRC += tclInterface.cpp
SRC += USBDM_AUX.cpp
SRC += Utils.cpp
ifeq ($(UNAME_S),Windows)
SRC += FindWindow.c
endif

# Shared files $(SHARED_SRC)/gdb
VPATH := $(SHARED_SRC)/gdb $(VPATH)
INCS  += -I$(SHARED_SRC)/gdb
SRC += GdbBreakpoints.cpp
SRC += GdbHandler.cpp
SRC += GdbInOut.cpp
SRC += GdbInOutSocket.cpp
SRC += GdbSocketServer.cpp
SRC += GdbMiscellaneous.cpp
