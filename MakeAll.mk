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
  RS08_Interface       \
  Unlocker             \
  FirmwareChanger      \
  JS16_Bootloader      \
  MergeXML             \
  UsbdmJniWrapper_DLL  \
  CopyFlash            \
  CreateFlashTestImage \
  CreateCTestImage     \
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

ifeq ($(UNAME_S),Windows)
DIRS = $(COMMON_DIRS) $(WIN_DIRS)
else
DIRS = $(COMMON_DIRS)
endif

BUILD_DIRS = $(DIRS:%=build-%)
CLEAN_DIRS = $(DIRS:%=clean-%)

.PHONY: $(CLEAN_DIRS)
.PHONY: $(BUILD_DIRS)
.PHONY: clean all 

all: $(BUILD_DIRS)

clean: $(CLEAN_DIRS)

$(BUILD_DIRS):
	$(MAKE) -C $(@:build-%=%) all

$(CLEAN_DIRS):
	$(MAKE) -C $(@:clean-%=%) clean
