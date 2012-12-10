# Shared make definitions
#

#.SILENT :

.SUFFIXES : .d .rc

MINGWBIN := f:/Apps/MinGW64/bin
MSYSBIN  := f:/Apps/MinGW64/msys/1.0/bin
RM       := $(MSYSBIN)/rm
RMDIR    := $(MSYSBIN)/rm -R
TOUCH    := $(MSYSBIN)/touch
MKDIR    := $(MSYSBIN)/mkdir
MAKE     := $(MINGWBIN)/mingw32-make
GCC      := $(MINGWBIN)/gcc
GPP      := $(MINGWBIN)/g++
WINDRES  := $(MINGWBIN)/windres
 
PROGRAM_DIR = C:/"Program Files"
#PROGRAM_DIR = C:/"Program Files (x86)"

SHARED_WXWIDGETS := "Y"
SHARED_XERCES    := "Y"

#===========================================================
# Options to build standalone DLL
STATIC_GCC_OPTION := -static-libstdc++ -static-libgcc

#===========================================================
# WIN32
WIN32_GUI_OPTS     := -Wl,--subsystem,windows -mwindows

#===========================================================
# WDI
# Header files in local dir
WDI_INC        := 
# Pick up shared DLLs from Shared_V4/lib
WDI_LIBDIRS    := 
WDI_LIBS       := -lwdi -lsetupapi -lole32  -lcomctl32 -luser32 -lgdi32

#===========================================================
# TCL
TCL_INC        := -IC:/Apps/Tcl/include
# Pick up shared DLLs from Shared_V4/lib
TCL_LIBDIRS    := 
TCL_LIBS       := -ltcl85

#===========================================================
# WXWIDGETS
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

WXWIDGETS_STATIC_LIBDIRS := -LF:/Apps/wxWidgets-2.9.4/lib/gcc_lib
WXWIDGETS_STATIC_LIBS    := \
-lwxmsw29u_richtext -lwxmsw29u_aui -lwxmsw29u_html -lwxmsw29u_xrc -lwxmsw29u_adv \
-lwxmsw29u_core -lwxbase29u -lwxbase29u_net -lwxbase29u_xml -lwxtiff -lwxjpeg \
-lwxpng -lwxzlib -lwxregexu -lwxexpat \
-lkernel32 -luser32 -lgdi32 -lcomdlg32 -lwinspool -lwinmm -lshell32 -lcomctl32 -lole32 \
-loleaut32 -luuid -lrpcrt4 -ladvapi32 -lwsock32
#-lwxmsw29u_gl -lwxmsw29u_media -lwxmsw29u_propgrid -lwxmsw29u_ribbon \
#-lwxmsw29u_stc -lwxmsw29u_webview \
#-lwxscintilla           

ifdef SHARED_WXWIDGETS
WXWIDGETS_LIBDIRS := $(WXWIDGETS_SHARED_LIBDIRS)
WXWIDGETS_LIBS    := $(WXWIDGETS_SHARED_LIBS)
else
WXWIDGETS_LIBDIRS := $(WXWIDGETS_STATIC_LIBDIRS)
WXWIDGETS_LIBS    := $(WXWIDGETS_STATIC_LIBS)       
endif

#===========================================================
# XERCES
XERCES_INC     := -IF:/Apps/xerces-c-3.1.1/src/

# Pick up shared DLLs from Shared_V4/lib
XERCES_SHARED_LIBDIRS := 
XERCES_STATIC_LIBDIRS := -LF:/Apps/xerces-c-3.1.1/src/.libs
XERCES_SHARED_LIBS    := -lxerces-c-3-1
XERCES_STATIC_LIBS    := -lxerces-c

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
JAVA_INC := -I$(PROGRAM_DIR)/Java/jdk1.7.0_07/include
JAVA_INC += -I$(PROGRAM_DIR)/Java/jdk1.7.0_07/include/win32

#===========================================================
# Shared directory - Relative to child directory
SHARED_SRC     := ../Shared_V4/src
SHARED_LIBDIRS := ../Shared_V4/lib

#=============================================================
# Common USBDM DLLs in debug and non-debug versions as needed
LIB_WX_PLUGIN = wxPlugin
LIB_USB_SHARED  = usb-1.0
LIB_USB_STATIC  = usb-static-1.0
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

#===========================================================
# Debug flags
ifdef DEBUG
# Compiler flags
CFLAGS := -O0
# Compiler flags (Linking)
LDFLAGS = 
# C Definitions
DEFS   := -DLOG
else
# Compiler flags
CFLAGS := -O3
# Compiler flags (Linking)
LDFLAGS = -s
endif
CFLAGS += -Wshadow -DWINVER=0x500 -D_WIN32_IE=0x500 -std=gnu99 -Wall -Wundef -Wunused -Wstrict-prototypes -Werror-implicit-function-declaration -Wno-pointer-sign

#===========================================================
# Library dir
LIBDIRS := -L$(SHARED_LIBDIRS)
