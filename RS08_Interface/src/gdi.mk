# List source file to include from current directory
SRC += FlashProgramming.cpp
SRC += USBDM_GDI.cpp
SRC += Version.rc

# Shared files $(SHARED_SRC)
VPATH := $(SHARED_SRC) $(VPATH)
SRC += ApplicationFiles.cpp
SRC += AppSettings.cpp
SRC += ClockTrimming.cpp
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
SRC += FindWindow.c
SRC += GDI_Common.c

# Shared files $(SHARED_SRC)/Programmer
VPATH := $(SHARED_SRC)/gdi $(VPATH)
SRC += GDI_Aux.cpp
SRC += MetrowerksInterface.cpp
