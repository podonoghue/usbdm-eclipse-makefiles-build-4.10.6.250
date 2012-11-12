# List source file to include from current directory
SRC += DSC_API.cpp
SRC += JTAGSequence.cpp
SRC += JTAGUtilities.cpp
SRC += Version.rc

# Shared files $(SHARED_SRC)
VPATH := $(SHARED_SRC) $(VPATH)
SRC += Log.cpp
SRC += Names.cpp
SRC += Utils.cpp
