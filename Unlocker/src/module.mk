# List source file to include from current directory
SRC += BitVector.cpp
SRC += CFUnlockerApp.cpp
SRC += CFUnlockerDialogue.cpp
SRC += CFUnlockerPanel.cpp
SRC += FlashEraseMethods.cpp
SRC += JTAG.cpp
SRC += KnownDevices.cpp
SRC += Version.rc

# Shared files $(SHARED_SRC)
VPATH := $(SHARED_SRC) $(VPATH)
SRC += ApplicationFiles.cpp
SRC += Log.cpp
SRC += Names.cpp
SRC += USBDM_AUX.cpp
SRC += Utils.cpp

# Shared files $(SHARED_SRC)/Programmer
VPATH := $(SHARED_SRC)/Programmer $(VPATH)
SRC += USBDMPanel.cpp