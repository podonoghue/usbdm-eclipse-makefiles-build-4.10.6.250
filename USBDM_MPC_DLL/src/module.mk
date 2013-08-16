# List source file to include from current directory
SRC += MPC_API.cpp
SRC += JTAGSequence.cpp
SRC += JTAGUtilities.cpp
SRC += Version.rc

# Shared files $(SHARED_SRC)
VPATH := $(SHARED_SRC) $(VPATH)
INCS += -I$(SHARED_SRC)
SRC += Log.cpp
SRC += Names.cpp
SRC += Utils.cpp
