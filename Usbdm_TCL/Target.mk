# Defined on command line
#BUILDDIR  = UsbdmScript-debug
#CDEFS     = -DLOG
#MODULE    = module
#TARGET    = BUILDDIR

# default to 'module'
MODULE ?= module

# default to same as build directory
TARGET ?= $(BUILDDIR)

include ../Common.mk

VPATH      := src $(BUILDDIR) 
SOURCEDIRS := src

# Use C Compiler
CC = $(GCC)

# Extra Compiler flags
CFLAGS +=

# Extra C Definitions
DEFS += $(CDEFS)  # From command line
DEFS += $(TCL_DEFS)

# Look for include files in each of the modules
INCS := $(patsubst %,-I%,$(SOURCEDIRS))
INCS += $(TCL_INC)

# Extra Library dirs
LIBDIRS += $(TCL_LIBDIRS)

# Extra libraries
LIBS += -l$(LIB_USBDM) 
LIBS += -l$(LIB_USBDM_DSC)
LIBS += $(TCL_LIBS)
ifneq ($(UNAME_S),Windows)
LIBS += -ldl
LIBS += -lm
endif

# Extra libraries for EXE only
EXELIBS += $(WXWIDGETS_SHARED_LIBS) -l$(LIB_WX_PLUGIN)

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
	$(CC) -o $@  $(LDFLAGS) $(OBJ) $(RESOURCE_OBJ) $(LIBDIRS) $(LIBS) ${EXELIBS}

# How to link a LIBRARY
#==============================================
$(BUILDDIR)/$(LIB_PREFIX)$(TARGET)$(LIB_SUFFIX): $(OBJ) $(RESOURCE_OBJ)
	@echo --
	@echo -- Linking Target $@
	$(CC) -shared -o $@ -Wl,-soname,$(basename $(notdir $@)) $(LDFLAGS) $(OBJ) $(RESOURCE_OBJ) $(LIBDIRS) $(LIBS) ${EXELIBS}

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

