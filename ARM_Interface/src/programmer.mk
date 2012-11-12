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
SRC += USBDM_AUX.cpp
SRC += Utils.cpp
#SRC += tclInterface.cpp

# Shared files $(SHARED_SRC)/Programmer
VPATH := $(SHARED_SRC)/Programmer $(VPATH)
SRC += AdvancedPanel.cpp
SRC += FlashPanel.cpp
SRC += FlashProgrammerApp.cpp
SRC += USBDMDialogue.cpp
SRC += USBDMPanel.cpp
