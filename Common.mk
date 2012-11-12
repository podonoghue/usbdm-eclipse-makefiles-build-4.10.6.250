# Shared make definitions
#

#.SILENT :

ifeq ($(OS),Windows_NT)
    UNAME_S := Windows
else
    UNAME_S := $(shell uname -s)
endif

ifeq ($(UNAME_S),Windows)
   .SUFFIXES : .d .rc
   LIB_PREFIX = 
   LIB_SUFFIX = .dll
   EXE_SUFFIX = .exe
   MINGWBIN := c:/Apps/MinGW/bin
   MSYSBIN  := c:/Apps/MinGW/msys/1.0/bin
   RM       := $(MSYSBIN)/rm
   RMDIR    := $(MSYSBIN)/rm -R -f
   TOUCH    := $(MSYSBIN)/touch
   MKDIR    := $(MSYSBIN)/mkdir
   MAKE     := $(MINGWBIN)/mingw32-make
   GCC      := $(MINGWBIN)/gcc
   GPP      := $(MINGWBIN)/g++
   WINDRES  := $(MINGWBIN)/windres
   PROGRAM_DIR = C:/"Program Files"
   #PROGRAM_DIR = C:/"Program Files (x86)"
else
   .SUFFIXES : .d
   LIB_PREFIX = lib
   LIB_SUFFIX = .so.4.10
   EXE_SUFFIX = 

   MINGWBIN := 
   MSYSBIN  := 
   RM       := rm
   RMDIR    := rm -R -f
   TOUCH    := touch
   MKDIR    := mkdir
   MAKE     := make
   GCC      := gcc
   GPP      := g++
   WINDRES  := 
endif

SHARED_WXWIDGETS := "Y"
SHARED_XERCES    := "Y"

#===========================================================
# Options to build standalone DLL (windows)
ifeq ($(UNAME_S),Windows)
   STATIC_GCC_OPTION := -static-libstdc++ -static-libgcc
endif

#===========================================================
# WIN32
ifeq ($(UNAME_S),Windows)
   WIN32_GUI_OPTS     := -Wl,--subsystem,windows -mwindows
else
   WIN32_GUI_OPTS     := 
endif

#===========================================================
# WDI
# Header files in local dir
WDI_INC        := 
# Pick up shared DLLs from Shared_V4/lib
WDI_LIBDIRS    := 
WDI_LIBS       := -lwdi-static -lsetupapi -lole32  -lcomctl32

#===========================================================
# TCL
# Pick up shared DLLs from Shared_V4/lib
TCL_LIBDIRS    := 
ifeq ($(UNAME_S),Windows)
   TCL_INC        := -IC:/Apps/Tcl/include
   TCL_LIBS       := -ltcl85
else
   TCL_INC        :=
   TCL_LIBS       := -ltcl8.5
endif

#===========================================================
# WXWIDGETS
ifeq ($(UNAME_S),Windows)
   WXWIDGETS_INC     := -IC:/Apps/wxWidgets-2.9.4/lib/gcc_lib/mswu -IC:/Apps/wxWidgets-2.9.4/include
   WXWIDGETS_DEFS    := -DuseWxWidgets -D__WXMSW__ -D__GNUWIN32__ -DUNICODE

   # Pick up shared DLLs from Shared_V4/lib
   WXWIDGETS_SHARED_LIBDIRS :=
   WXWIDGETS_SHARED_LIBS    := \
   -lwxmsw294u_core_gcc_custom       -lwxbase294u_gcc_custom \
   -lwxmsw294u_adv_gcc_custom
   #-lwxbase294u_net_gcc_custom       -lwxbase294u_xml_gcc_custom     \
   #-lwxmsw294u_aui_gcc_custom      \
   #-lwxmsw294u_gl_gcc_custom         -lwxmsw294u_html_gcc_custom     \
   #-lwxmsw294u_media_gcc_custom      -lwxmsw294u_propgrid_gcc_custom \
   #-lwxmsw294u_ribbon_gcc_custom     -lwxmsw294u_richtext_gcc_custom \
   #-lwxmsw294u_stc_gcc_custom        -lwxmsw294u_webview_gcc_custom  \
   #-lwxmsw294u_xrc_gcc_custom   

   WXWIDGETS_STATIC_LIBDIRS := -LC:/Apps/wxWidgets-2.9.4/lib/gcc_lib
   WXWIDGETS_STATIC_LIBS    := \
   -lwxmsw29u_richtext -lwxmsw29u_aui -lwxmsw29u_html -lwxmsw29u_xrc -lwxmsw29u_adv \
   -lwxmsw29u_core -lwxbase29u -lwxbase29u_net -lwxbase29u_xml -lwxtiff -lwxjpeg \
   -lwxpng -lwxzlib -lwxregexu -lwxexpat \
   -lkernel32 -luser32 -lgdi32 -lcomdlg32 -lwinspool -lwinmm -lshell32 -lcomctl32 -lole32 \
   -loleaut32 -luuid -lrpcrt4 -ladvapi32 -lwsock32

   #-lwxmsw29u_gl -lwxmsw29u_media -lwxmsw29u_propgrid -lwxmsw29u_ribbon \
   #-lwxmsw29u_stc -lwxmsw29u_webview \
   #-lwxscintilla           

else
   WXWIDGETS_INC     := `wx-config --cppflags`
   WXWIDGETS_DEFS    := -DuseWxWidgets

   WXWIDGETS_SHARED_LIBDIRS :=
   WXWIDGETS_SHARED_LIBS    := `wx-config --libs`

   WXWIDGETS_STATIC_LIBDIRS := 
   WXWIDGETS_STATIC_LIBS    := 
endif

ifdef SHARED_WXWIDGETS
   WXWIDGETS_LIBDIRS := $(WXWIDGETS_SHARED_LIBDIRS)
   WXWIDGETS_LIBS    := $(WXWIDGETS_SHARED_LIBS)
else
   WXWIDGETS_LIBDIRS := $(WXWIDGETS_STATIC_LIBDIRS)
   WXWIDGETS_LIBS    := $(WXWIDGETS_STATIC_LIBS)       
endif

#===========================================================
# XERCES
ifeq ($(UNAME_S),Windows)
   XERCES_INC     := -IC:/Apps/xerces-c-3.1.1/src/

   # Pick up shared DLLs from Shared_V4/lib
   XERCES_SHARED_LIBDIRS := 
   XERCES_STATIC_LIBDIRS := -LC:/Apps/xerces-c-3.1.1/src/.libs
   XERCES_SHARED_LIBS    := -lxerces-c-3-1
   XERCES_STATIC_LIBS    := -lxerces-c
   else
   XERCES_INC     :=

   # Pick up shared DLLs from Shared_V4/lib
   XERCES_SHARED_LIBDIRS := 
   XERCES_STATIC_LIBDIRS := 
   XERCES_SHARED_LIBS    := -lxerces-c
   XERCES_STATIC_LIBS    := 
endif

ifdef SHARED_XERCES
   XERCES_LIBS    := $(XERCES_SHARED_LIBS)
   XERCES_LIBDIRS := $(XERCES_SHARED_LIBDIRS)
else
   XERCES_LIBS    := $(XERCES_STATIC_LIBS)
   XERCES_LIBDIRS := $(XERCES_STATIC_LIBDIRS)
endif

#===========================================================
# Windows Installer XML v3.5 & Windows Installer v4.5 SDK

WIN_XML_INSTALLER_INC     := -I$(PROGRAM_DIR)/"Windows Installer 4.5 SDK"/INCLUDE
WIN_XML_INSTALLER_LIBDIRS := -L$(PROGRAM_DIR)/"Windows Installer 4.5 SDK"/LIB/x86
WIN_XML_INSTALLER_LIBS    := -lMsi

#===========================================================
# Java for JNI
ifeq ($(UNAME_S),Windows)
   JAVA_INC := -I$(PROGRAM_DIR)/Java/jdk1.7.0_07/include
   JAVA_INC += -I$(PROGRAM_DIR)/Java/jdk1.7.0_07/include/win32
else
   JAVA_INC := -I/usr/lib/jvm/default-java/include
endif

#===========================================================
# Shared directory - Relative to child directory
SHARED_SRC     := ../Shared_V4/src
SHARED_LIBDIRS := ../Shared_V4/lib

#=============================================================
# Common USBDM DLLs in debug and non-debug versions as needed
ifeq ($(UNAME_S),Windows)
   LIB_WX_PLUGIN = wxPlugin
else
   LIB_WX_PLUGIN = usbdm-wx
endif

LIB_USB_SHARED  = usb-1.0
LIB_USB_STATIC  = usb-static-1.0

ifeq ($(UNAME_S),Windows)
   LIB_USB = $(LIB_USB_STATIC)
   ifdef DEBUG
      LIB_USBDM     = usbdm-debug.4 
      LIB_USBDM_TCL = usbdmTCL-debug.4 
      LIB_USBDM_DSC = usbdm-dsc-debug.4 
   else
      LIB_USBDM     = usbdm.4 
      LIB_USBDM_TCL = usbdmTCL.4 
      LIB_USBDM_DSC = usbdm-dsc.4 
   endif
else
   LIB_USB = $(LIB_USB_SHARED)
   ifdef DEBUG
      LIB_USBDM     = usbdm-debug
      LIB_USBDM_TCL = usbdm-tcl-debug 
      LIB_USBDM_DSC = usbdm-dsc-debug 
   else
      LIB_USBDM     = usbdm
      LIB_USBDM_TCL = usbdm-tcl 
      LIB_USBDM_DSC = usbdm-dsc 
   endif
endif

#===========================================================
# Debug flags
ifeq ($(UNAME_S),Windows)
GCC_VISIBILITY_DEFS=
else
GCC_VISIBILITY_DEFS=-fvisibility=hidden -fvisibility-inlines-hidden
endif
ifdef DEBUG
   # Compiler flags
   CFLAGS := -O0 -g3 ${GCC_VISIBILITY_DEFS}
   # Compiler flags (Linking)
   LDFLAGS = 
   # C Definitions
   DEFS   := -DLOG
else
   # Compiler flags
   CFLAGS := -O3 -g0 ${GCC_VISIBILITY_DEFS}
   # Compiler flags (Linking)
   LDFLAGS = -s
endif
#CFLAGS += -Wshadow -DWINVER=0x500 -D_WIN32_IE=0x500 -std=gnu99 -Wall -Wundef -Wunused -Wstrict-prototypes -Werror-implicit-function-declaration -Wno-pointer-sign

#===========================================================
# Look in shared Library dir first
LIBDIRS := -L$(SHARED_LIBDIRS)

#===========================================================
# Common Definitions for building Programmer, GDI & GDB
PROGRAMMER_DEFS = -DTARGET=$(TARGET) -DFLASH_PROGRAMMER -DUSE_ICON
GDI_DEFS        = -DTARGET=$(TARGET) -DGDI
GDI_LEGACY_DEFS = -DTARGET=$(TARGET) -DGDI -DLEGACY
GDB_DEFS        = -DTARGET=$(TARGET) -DGDB

ifeq ($(UNAME_S),Windows)
# Windows version of Codewarrior packs structs
GDI_DEFS        = -DPACK_STRUCTS=1 -DTARGET=$(TARGET) -DGDI
endif

