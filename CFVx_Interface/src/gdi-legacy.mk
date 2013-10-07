# Build list for Codewarrior Legacy GDI interface

# List source file to include from current directory

SRC += USBDM_GDI.cpp
SRC += Version.rc

# Shared files $(SHARED_SRC)
VPATH := $(SHARED_SRC) $(VPATH)
INCS  += -I$(SHARED_SRC)
SRC += ApplicationFiles.cpp
SRC += AppSettings.cpp
SRC += Log.cpp
SRC += Names.cpp
SRC += USBDM_AUX.cpp
SRC += Utils.cpp
SRC += GDI_Common.cpp

# Shared files $(SHARED_SRC)/gdi
VPATH := $(SHARED_SRC)/gdi $(VPATH)
INCS  += -I$(SHARED_SRC)/gdi
SRC += GDI_Aux.cpp
SRC += MetrowerksInterface.cpp

# Shared files $(SHARED_SRC)/Programmer
VPATH := $(SHARED_SRC)/Programmer $(VPATH)
INCS  += -I$(SHARED_SRC)/Programmer
SRC += AdvancedPanel.cpp
SRC += InterfacePanel.cpp
SRC += Shared.cpp
SRC += USBDMDialogue.cpp
