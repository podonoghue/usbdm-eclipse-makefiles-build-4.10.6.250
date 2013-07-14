# List source file to include from current directory
SRC += armInterface.cpp
SRC += ICP.cpp
SRC += JTAGSequence.cpp
SRC += low_level_usb.cpp
SRC += Log.cpp
SRC += USBDM_API.cpp
SRC += USBDM_ErrorMessages.cpp
SRC += Version.rc

# Shared files $(SHARED_SRC)/Programmer
VPATH := $(VPATH) $(SHARED_SRC)
INCS += -I$(SHARED_SRC)
SRC += Names.cpp
