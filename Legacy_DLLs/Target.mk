# Defined on command line
#BUILDDIR  = UsbdmScript-debug
#CDEFS     = -DLOG
#MODULE    = module
#TARGET    = BUILDDIR

ifeq ($(OS),Windows_NT)
    UNAME_S := Windows
else
    UNAME_S := $(shell uname -s)
endif

ifeq ($(UNAME_S),Windows)
   DIRS = $(COMMON_DIRS) $(WIN_DIRS)
   TARGET_BINDIR   := ../PackageFiles/bin/win32
   TARGET_LIBDIR   := ../PackageFiles/bin/win32
   BITNESS         := 32
   BUILDDIR_SUFFIX :=
else
   DIRS = $(COMMON_DIRS)
   # BITNESS can be forced on the command line
   BITNESS ?= $(shell getconf LONG_BIT)
   ifeq ($(BITNESS),32)
      TARGET_BINDIR   := ../PackageFiles/bin/i386-linux-gnu
      TARGET_LIBDIR   := ../PackageFiles/lib/i386-linux-gnu
      BUILDDIR_SUFFIX := .i386
   endif
   ifeq ($(BITNESS),64)
      TARGET_BINDIR   := ../PackageFiles/bin/x86_64-linux-gnu
      TARGET_LIBDIR   := ../PackageFiles/lib/x86_64-linux-gnu
      BUILDDIR_SUFFIX := .x86_64
   endif
endif

# default to 'module'
MODULE ?= module

# default to same as build directory
TARGET ?= $(BUILDDIR)

include ../Common.mk

VPATH      := src $(BUILDDIR) 
SOURCEDIRS := src $(SHARED_SRC)

# Use C++ Compiler
CC = $(GPP)

# Extra Compiler flags
CFLAGS +=

# Extra C Definitions
DEFS += $(CDEFS)  # From command line
DEFS += $(WXWIDGETS_DEFS)

# Look for include files in each of the modules
INCS := $(patsubst %,-I%,$(SOURCEDIRS))
INCS += $(WXWIDGETS_INC)

# Extra Library dirs
LIBDIRS += $(WXWIDGETS_LIBDIRS)

# Extra libraries
LIBS += -l$(LIB_USBDM) 
LIBS += $(WXWIDGETS_LIBS)

# Each module will add to this
SRC :=

# Include the source list from each module
-include $(patsubst %,%/$(MODULE).mk,$(SOURCEDIRS))

# Determine the C/CPP object files from source file list
OBJ := \
$(patsubst %.cpp,$(BUILDDIR)/%.o, \
$(filter %.cpp,$(SRC))) \
$(patsubst %.c,$(BUILDDIR)/%.o, \
$(filter %.c,$(SRC)))

ifeq ($(UNAME_S),Windows)
# Determine the resource object files 
RESOURCE_OBJ := \
$(patsubst %.rc,$(BUILDDIR)/%.o, \
$(filter %.rc,$(SRC))) 
else
RESOURCE_OBJ := 
endif

# Include the C dependency files (if they exist)
-include $(OBJ:.o=.d)

# Rules to build object (.o) files
#==============================================
ifeq ($(UNAME_S),Windows)
$(BUILDDIR)/%.o : %.rc
	@echo -- Building $@ from $<
	$(WINDRES) $< $(DEFS) $(INCS) -o $@
endif

$(BUILDDIR)/%.o : %.c
	@echo -- Building $@ from $<
	$(CC) $(CFLAGS) $(DEFS) $(INCS) -MD -c $< -o $@
	
$(BUILDDIR)/%.o : %.cpp
	@echo -- Building $@ from $<
	$(CC) $(CFLAGS) $(DEFS) $(INCS) -MD -c $< -o $@
	
# How to link an EXE
#==============================================
$(BUILDDIR)/$(TARGET)$(EXE_SUFFIX): $(OBJ) $(RESOURCE_OBJ)
	@echo --
	@echo -- Linking Target $@
	$(CC) -o $@ $(LDFLAGS) $(OBJ) $(RESOURCE_OBJ) $(LIBDIRS) $(LIBS) 

# How to link a LIBRARY
#==============================================
$(BUILDDIR)/$(LIB_PREFIX)$(TARGET)$(LIB_SUFFIX): $(OBJ) $(RESOURCE_OBJ)
	@echo --
	@echo -- Linking Target $@
	$(CC) -shared -o $@ -Wl,-soname,$(basename $(notdir $@)) $(LDFLAGS) $(OBJ) $(RESOURCE_OBJ) $(LIBDIRS) $(LIBS) 

DLL_TARGET=$(LIB_PREFIX)$(TARGET)$(LIB_SUFFIX)
EXE_TARGET=$(TARGET)$(EXE_SUFFIX)

# How to copy LIBRARY to target directory
#==============================================
$(TARGET_LIBDIR)/$(DLL_TARGET): $(BUILDDIR)/$(DLL_TARGET)
	@echo --
	@echo -- Copying $? to $(TARGET_LIBDIR)
	$(CP) $? $@
ifneq ($(UNAME_S),Windows)
	$(LN) $(DLL_TARGET) $(TARGET_LIBDIR)/$(LIB_PREFIX)$(TARGET)$(LIB_MAJOR_SUFFIX)
	$(LN) $(DLL_TARGET) $(TARGET_LIBDIR)/$(LIB_PREFIX)$(TARGET)$(LIB_NO_SUFFIX)
endif

# How to copy EXE to target directory
#==============================================
$(TARGET_BINDIR)/$(EXE_TARGET): $(BUILDDIR)/$(EXE_TARGET)
	@echo --
	@echo -- Copying $? to $(TARGET_BINDIR)
	$(CP) $? $@

# Create required directories
#==============================================
directories : 
	-$(MKDIR) $(BUILDDIR) $(TARGET_LIBDIR)
	-$(MKDIR) $(BUILDDIR) $(TARGET_BINDIR)
    
clean:
	-$(RMDIR) $(BUILDDIR)

dll: directories $(TARGET_LIBDIR)/$(DLL_TARGET)
exe: directories $(TARGET_BINDIR)/$(EXE_TARGET)
   
.PHONY: directories clean dll exe 

