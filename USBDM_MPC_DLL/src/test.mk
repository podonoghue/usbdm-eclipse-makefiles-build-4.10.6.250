# List source file to include from current directory
SRC += MPC_API.cpp
SRC += JTAGSequence.cpp
SRC += JTAGUtilities.cpp
SRC += Version.rc
SRC += Test.rc

# Shared files $(SHARED_SRC)
VPATH := $(SHARED_SRC);$(VPATH)
SRC += Log.cpp
SRC += Names.cpp
SRC += Utils.cpp
