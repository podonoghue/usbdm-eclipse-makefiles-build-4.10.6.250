# List source file to include from current directory
SRC += FirmwareChanger.cpp
SRC += Version.rc

# Shared files $(SHARED_SRC)
VPATH := $(SHARED_SRC) $(VPATH)
SRC += Names.cpp
SRC += ApplicationFiles.cpp
SRC += AppSettings.cpp
SRC += Utils.cpp
SRC += Log.cpp