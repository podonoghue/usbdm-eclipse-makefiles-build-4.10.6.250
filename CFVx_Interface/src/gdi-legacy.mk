# List source file to include from current directory

SRC += USBDM_GDI.cpp
SRC += Version.rc

# Shared files $(SHARED_SRC)
VPATH := $(SHARED_SRC);$(VPATH)
SRC += ApplicationFiles.cpp
SRC += AppSettings.cpp
SRC += Log.cpp
SRC += Names.cpp
SRC += USBDM_AUX.cpp
SRC += Utils.cpp
SRC += GDI_Common.cpp

# Shared files $(SHARED_SRC)/gdi
VPATH := $(SHARED_SRC)/gdi $(VPATH)
SRC += GDI_Aux.cpp
SRC += MetrowerksInterface.cpp

# Shared files $(SHARED_SRC)/Programmer
VPATH := $(SHARED_SRC)/Programmer $(VPATH)
SRC += AdvancedPanel.cpp
SRC += USBDMDialogue.cpp
SRC += USBDMPanel.cpp
