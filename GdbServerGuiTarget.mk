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

# Use C++ Compiler
CC = $(GPP)

# Extra Compiler flags
CFLAGS +=

# Extra C Definitions
DEFS += $(CDEFS)  # From command line
DEFS += $(WXWIDGETS_DEFS)
DEFS += $(XERCES_DEFS)

# Look for include files in each of the modules
INCS := $(patsubst %,-I%,$(SOURCEDIRS))
INCS += $(WXWIDGETS_INC)
INCS += $(XERCES_INC)

# Extra Library dirs
LIBDIRS += $(WXWIDGETS_LIBDIRS)
LIBDIRS += $(XERCES_LIBDIRS)

# Extra libraries
LIBS += -l$(LIB_USBDM) 
LIBS += -l$(LIB_USBDM_TCL)
ifneq ($(UNAME_S),Windows)
LIBS += -l$(LIB_USBDM_DSC)
endif
LIBS += $(WXWIDGETS_LIBS)
LIBS += $(XERCES_LIBS)
#LIBS += -l$(LIB_WX_PLUGIN)
LIBS += $(LIB_SOCKETS)
LIBS += -lwxbase294u_net_gcc_custom

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
#$(BUILDDIR)/%.d : %.c $(BUILDDIR)/timestamp
#	@echo -- Building $@ from $<
#	$(CC) -MM -MQ $(patsubst %.d,%.o, $@) $(CFLAGS) $(DEFS) $(INCS) $< >$@ 
#
#$(BUILDDIR)/%.d : %.cpp $(BUILDDIR)/timestamp
#	@echo -- Building $@ from $<
#	$(CC) -MM -MQ $(patsubst %.d,%.o, $@) $(CFLAGS) $(DEFS) $(INCS) $< >$@ 

# Rules to build object (.o) files
#==============================================
ifeq ($(UNAME_S),Windows)
$(BUILDDIR)/%.o : %.rc $(BUILDDIR)/timestamp
	@echo -- Building $@ from $<
	$(WINDRES) $< $(DEFS) $(INCS) -o $@
endif

$(BUILDDIR)/%.o : %.c $(BUILDDIR)/timestamp
	@echo -- Building $@ from $<
	$(CC) $(CFLAGS) $(DEFS) $(INCS) -MD -c $< -o $@
	
$(BUILDDIR)/%.o : %.cpp $(BUILDDIR)/timestamp
	@echo -- Building $@ from $<
	$(CC) $(CFLAGS) $(DEFS) $(INCS) -MD -c $< -o $@
	
# How to link an EXE
#==============================================
$(BUILDDIR)/$(TARGET)$(EXE_SUFFIX): $(OBJ) $(RESOURCE_OBJ)
	@echo --
	@echo -- Linking Target $@
	$(CC) -o $@ $(WIN32_GUI_OPTS) $(LDFLAGS) $(OBJ) $(RESOURCE_OBJ) $(LIBDIRS) $(LIBS) 

# How to link a DLL
#==============================================
$(BUILDDIR)/$(LIB_PREFIX)$(TARGET)$(LIB_SUFFIX): $(OBJ) $(RESOURCE_OBJ)
	@echo --
	@echo -- Linking Target $@
	$(CC) -shared -o $@ $(LDFLAGS) $(OBJ) $(RESOURCE_OBJ) $(LIBDIRS) $(LIBS) 

$(BUILDDIR) : $(BUILDDIR)/timestamp
	
$(BUILDDIR)/timestamp :
	-$(MKDIR) $(BUILDDIR)
	-$(TOUCH) $(BUILDDIR)/timestamp
    
clean:
	-$(RM) $(BUILDDIR)/*.*
	-$(RMDIR) $(BUILDDIR)

dll: $(BUILDDIR) $(BUILDDIR)/$(LIB_PREFIX)$(TARGET)$(LIB_SUFFIX)
#	@echo SRC          = $(SRC)
#	@echo OBJ          = $(OBJ)
#	@echo RESOURCE_OBJ = $(RESOURCE_OBJ)

exe: $(BUILDDIR) $(BUILDDIR)/$(TARGET)$(EXE_SUFFIX)
#	@echo SRC          = $(SRC)
#	@echo OBJ          = $(OBJ)
#	@echo RESOURCE_OBJ = $(RESOURCE_OBJ)
   
.PHONY: clean dll exe $(BUILDDIR)

