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

# Rules to build dependency (.d) files
#==============================================
$(BUILDDIR)/%.d : %.c $(BUILDDIR)/timestamp
	@echo -- Building $@ from $<
	$(CC) -MM -MG -MQ $(patsubst %.d,%.o, $@) $(CFLAGS) $(DEFS) $(INCS) $< >$@ 

$(BUILDDIR)/%.d : %.cpp $(BUILDDIR)/timestamp
	@echo -- Building $@ from $<
	$(CC) -MM -MG -MQ $(patsubst %.d,%.o, $@) $(CFLAGS) $(DEFS) $(INCS) $< >$@ 

# Rules to build object (.o) files
#==============================================
ifeq ($(UNAME_S),Windows)
$(BUILDDIR)/%.o : %.rc $(BUILDDIR)/timestamp
	@echo -- Building $@ from $<
	$(WINDRES) $< $(DEFS) $(INCS) -o $@
endif

$(BUILDDIR)/%.o : %.c $(BUILDDIR)/timestamp
	@echo -- Building $@ from $<
	$(CC) $(CFLAGS) $(DEFS) $(INCS) -c $< -o $@
	
$(BUILDDIR)/%.o : %.cpp $(BUILDDIR)/timestamp
	@echo -- Building $@ from $<
	$(CC) $(CFLAGS) $(DEFS) $(INCS) -c $< -o $@
	
# How to link an EXE
#==============================================
$(BUILDDIR)/$(TARGET)$(EXE_SUFFIX): $(OBJ) $(RESOURCE_OBJ)
	@echo --
	@echo -- Linking Target $@
	$(CC) -o $@  $(WIN32_GUI_OPTS) $(LDFLAGS) $(OBJ) $(RESOURCE_OBJ) $(LIBDIRS) $(LIBS) 

# How to link a LIBRARY
#==============================================
$(BUILDDIR)/$(LIB_PREFIX)$(TARGET)$(LIB_SUFFIX): $(OBJ) $(RESOURCE_OBJ)
	@echo --
	@echo -- Linking Target $@
	$(CC) -shared -o $@ $(LDFLAGS) $(OBJ) $(RESOURCE_OBJ) $(LIBDIRS) $(LIBS) 

# How to copy a LIBRARY to the shared directory
#==============================================
$(SHARED_LIBDIRS)/$(LIB_PREFIX)$(TARGET)$(LIB_SUFFIX): $(BUILDDIR)/$(LIB_PREFIX)$(TARGET)$(LIB_SUFFIX)
	@echo --
	@echo -- Copying $? to $(SHARED_LIBDIRS)
	$(CP) $? $@
ifneq ($(UNAME_S),Windows)
	$(LN) -f ./$(LIB_PREFIX)$(TARGET)$(LIB_SUFFIX) $(SHARED_LIBDIRS)/$(LIB_PREFIX)$(TARGET)$(LIB_MAJOR_SUFFIX)
	$(LN) -f ./$(LIB_PREFIX)$(TARGET)$(LIB_SUFFIX) $(SHARED_LIBDIRS)/$(LIB_PREFIX)$(TARGET)$(LIB_NO_SUFFIX)
endif

$(BUILDDIR) : $(BUILDDIR)/timestamp
	
$(BUILDDIR)/timestamp :
	-$(MKDIR) $(BUILDDIR)
	-$(TOUCH) $(BUILDDIR)/timestamp
    
clean:
	-$(RM) $(BUILDDIR)/*.*
	-$(RMDIR) $(BUILDDIR)

dll: $(BUILDDIR) $(SHARED_LIBDIRS)/$(LIB_PREFIX)$(TARGET)$(LIB_SUFFIX)
#	@echo SRC          = $(SRC)
#	@echo OBJ          = $(OBJ)
#	@echo RESOURCE_OBJ = $(RESOURCE_OBJ)

exe: $(BUILDDIR) $(BUILDDIR)/$(TARGET)$(EXE_SUFFIX)
#	@echo SRC          = $(SRC)
#	@echo OBJ          = $(OBJ)
#	@echo RESOURCE_OBJ = $(RESOURCE_OBJ)
   
.PHONY: clean dll exe $(BUILDDIR)

