# Build list for Codewarrior GDI interface

# List source file to include from current directory
SRC += DSC_Utilities.cpp
SRC += FlashProgramming.cpp
SRC += USBDM_GDI.cpp
SRC += GDI_Common.cpp
SRC += Version.rc

# Shared files $(SHARED_SRC)
VPATH := $(VPATH) $(SHARED_SRC)
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

# Shared files $(SHARED_SRC)/gdi
VPATH := $(SHARED_SRC)/gdi $(VPATH)
INCS  += -I$(SHARED_SRC)/gdi
SRC += GDI_Aux.cpp
SRC += MetrowerksInterface.cpp
