# List source file to include from current directory
SRC += ApplicationFiles.cpp
SRC += Log.cpp
SRC += Names.cpp
SRC += Version.rc

SRC += OpenSourceBDM_dll.cpp

SRC += AppSettings.cpp
SRC += hcs12UnsecureDialogue.cpp
SRC += USBDM_AUX.cpp
SRC += USBDMDialogue.cpp
SRC += USBDMPanel.cpp

VPATH := src/LegacyDLLs;$(VPATH)
VPATH := src/gui;$(VPATH)
