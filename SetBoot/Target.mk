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

VPATH      := src;$(BUILDDIR);
SOURCEDIRS := src $(SHARED_SRC)

# Use C Compiler
CC = $(GCC)

# Extra Compiler flags
CFLAGS +=

# Extra C Definitions
DEFS += $(CDEFS)  # From command line
DEFS +=

# Look for include files in each of the modules
INCS := $(patsubst %,-I%,$(SOURCEDIRS))

# Extra Library dirs
LIBDIRS += 

# Extra libraries
LIBS += -l$(LIB_USBDM)

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

# Determine the resource object files 
RESOURCE_OBJ := \
$(patsubst %.rc,$(BUILDDIR)/%.o, \
$(filter %.rc,$(SRC))) 

# Include the C dependency files (if they exist)
-include $(OBJ:.o=.d)

# Rules to build dependency (.d) files
$(BUILDDIR)/%.d : %.c $(BUILDDIR)/timestamp
	@echo ** Building $@ from $<
	$(CC) -MM -MG -MQ $(patsubst %.d,%.o, $@) $(CFLAGS) $(DEFS) $(INCS) $< >$@ 

$(BUILDDIR)/%.d : %.cpp $(BUILDDIR)/timestamp
	@echo ** Building $@ from $<
	$(CC) -MM -MG -MQ $(patsubst %.d,%.o, $@) $(CFLAGS) $(DEFS) $(INCS) $< >$@ 

# Rules to buld object (.o) files
$(BUILDDIR)/%.o : %.rc $(BUILDDIR)/timestamp
	@echo ** Building $@ from $<
	$(WINDRES) $< $(DEFS) $(INCS) -o $@

$(BUILDDIR)/%.o : %.c $(BUILDDIR)/timestamp
	@echo ** Building $@ from $<
	$(CC) $(CFLAGS) $(DEFS) $(INCS) -c $< -o $@
	
$(BUILDDIR)/%.o : %.cpp $(BUILDDIR)/timestamp
	@echo ** Building $@ from $<
	$(CC) $(CFLAGS) $(DEFS) $(INCS) -c $< -o $@
	
# How to link an EXE
$(TARGET).exe: $(OBJ) $(RESOURCE_OBJ)
	@echo ** Linking Target $@
	$(CC) -o $(BUILDDIR)/$@  $(LDFLAGS) $(OBJ) $(RESOURCE_OBJ) $(LIBDIRS) $(LIBS) 

# How to link a DLL
$(TARGET).dll: $(OBJ) $(RESOURCE_OBJ)
	@echo ** Linking Target $@
	$(CC) -shared -o $(BUILDDIR)/$@  $(LDFLAGS) $(OBJ) $(RESOURCE_OBJ) $(LIBDIRS) $(LIBS) 

$(BUILDDIR) : $(BUILDDIR)/timestamp
	
$(BUILDDIR)/timestamp :
	-$(MKDIR) $(BUILDDIR)
	-$(TOUCH) $(BUILDDIR)/timestamp
    
clean:
	-$(RM) $(BUILDDIR)/*.*
	-$(RMDIR) $(BUILDDIR)

dll: $(BUILDDIR) $(TARGET).dll
#	@echo SRC          = $(SRC)
#	@echo OBJ          = $(OBJ)
#	@echo RESOURCE_OBJ = $(RESOURCE_OBJ)

exe: $(BUILDDIR) $(TARGET).exe
#	@echo SRC          = $(SRC)
#	@echo OBJ          = $(OBJ)
#	@echo RESOURCE_OBJ = $(RESOURCE_OBJ)
   
.PHONY: clean dll exe $(BUILDDIR)

