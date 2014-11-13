# Build list for Flash Programmer

# List source file to include from current directory
SRC += FlashProgramming.cpp
SRC += Version.rc
SRC += ClockTrimmingKinetis.cpp

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
SRC += USBDM_AUX.cpp
SRC += Utils.cpp

# Shared files $(SHARED_SRC)/Programmer
VPATH := $(SHARED_SRC)/Programmer $(VPATH)
INCS  += -I$(SHARED_SRC)/Programmer
SRC += AdvancedPanel.cpp
SRC += FlashProgrammerApp.cpp
SRC += InterfacePanel.cpp
SRC += Shared.cpp
SRC += TargetPanel.cpp
SRC += USBDMDialogue.cpp
