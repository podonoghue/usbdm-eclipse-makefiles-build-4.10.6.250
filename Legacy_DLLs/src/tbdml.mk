# List source file to include from current directory
SRC += ApplicationFiles.cpp
SRC += Log.cpp
SRC += Names.cpp
SRC += Version.rc

VPATH := src/LegacyDLLs;$(VPATH)
SRC += TBDML_dll.cpp

VPATH := src/gui;$(VPATH)
SRC += AppSettings.cpp
SRC += hcs12UnsecureDialogue.cpp
SRC += USBDM_AUX.cpp
SRC += USBDMDialogue.cpp
SRC += USBDMPanel.cpp
