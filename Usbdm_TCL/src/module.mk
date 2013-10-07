# List source file to include from current directory
SRC += DSC_Utilities.c
SRC += Names.c
SRC += usbdmTcl.c
SRC += Version.rc

# Shared files $(SHARED_SRC)
ifeq ($(UNAME_S),Windows)
VPATH := $(VPATH) $(SHARED_SRC)
SRC += FindWindow.c
endif
INCS += -I$(SHARED_SRC)
