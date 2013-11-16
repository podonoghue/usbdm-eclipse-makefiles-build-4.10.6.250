# List source file to include from current directory
SRC += wxPlugin.cpp
SRC += wxWindowsStub.cpp
SRC += Version.rc
#SRC += MyDialog.rc

# Shared files $(SHARED_SRC)
VPATH := $(SHARED_SRC) $(VPATH)
INCS  += -I$(SHARED_SRC)
SRC += Utils.cpp
