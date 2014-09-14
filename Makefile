include Common.mk

# Built on both Windows and Linux
# Note - order is important
COMMON_DIRS = \
  wxPlugin_DLL         \
  USBDM_DLL            \
  USBDM_DSC_DLL        \
  Usbdm_TCL            \
  ARM_Interface        \
  CFV1_Interface       \
  CFVx_Interface       \
  DSC_Interface        \
  HCS08_Interface      \
  HCS12_Interface      \
  S12Z_Interface       \
  RS08_Interface       \
  Unlocker             \
  FirmwareChanger      \
  JS16_Bootloader      \
  MergeXML             \
  UsbdmJniWrapper_DLL  \
  CreateFlashTestImage \
  CreateCTestImage     \
  USBDM_Kinetis_Unlock \
  USBDM_API_Example

# Built only on Windows
WIN_DIRS = \
  Legacy_DLLs          \
  SetBoot              \
  USBDM_ARM_DLL        \
  USBDM_MPC_DLL        \
  MyCustomAction

#  Min test set
#	USBDM_DLL            \
#	USBDM_DSC_DLL        \
#	Usbdm_TCL    

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

export BITNESS TARGET_BINDIR TARGET_LIBDIR BUILDDIR_SUFFIX

BUILD_DIRS = $(DIRS:%=build-%)
CLEAN_DIRS = $(DIRS:%=clean-%)

.PHONY: $(CLEAN_DIRS)
.PHONY: $(BUILD_DIRS)
.PHONY: clean all cleanTargetFiles

all: cleanTargetFiles $(BUILD_DIRS)

clean: $(CLEAN_DIRS)

cleanTargetFiles:
	$(RMDIR) $(DUMMY_CHILD)/$(TARGET_LIBDIR)
	$(MKDIR) $(DUMMY_CHILD)/$(TARGET_LIBDIR)
	$(RMDIR) $(DUMMY_CHILD)/$(TARGET_BINDIR)
	$(MKDIR) $(DUMMY_CHILD)/$(TARGET_BINDIR)
ifeq ($(UNAME_S),Windows)
	$(CP) $(DUMMY_CHILD)/$(SHARED_LIBDIRS)/* $(DUMMY_CHILD)/$(TARGET_LIBDIR)
endif

$(BUILD_DIRS):
	$(MAKE) -C $(@:build-%=%) all

$(CLEAN_DIRS):
	$(MAKE) -C $(@:clean-%=%) clean
