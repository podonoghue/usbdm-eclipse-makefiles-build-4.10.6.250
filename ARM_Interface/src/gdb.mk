# List source file to include from current directory
SRC += FlashProgramming.cpp
SRC += Version.rc

# Shared files $(SHARED_SRC)
VPATH := $(SHARED_SRC) $(VPATH)
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

# Shared files $(SHARED_SRC)/gdb
VPATH := $(SHARED_SRC)/gdb $(VPATH)
SRC += GdbBreakpoints.cpp
SRC += GdbHandler.cpp
SRC += GdbInput.cpp
SRC += GdbOutput.cpp
SRC += GdbServer.cpp
