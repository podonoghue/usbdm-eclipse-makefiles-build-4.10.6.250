#include <wx/wx.h>
#include <wx/window.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/app.h>
#include <wx/evtloop.h>
#ifdef __unix__
#include <dlfcn.h>
#endif

#ifdef _WIN32
#include <wx/msw/registry.h>
#endif

#include <stdio.h>
#include <string.h>

#include "wxPlugin.h"

static bool dll_open(void);
static bool dll_close(void);

static WindowHandle *defaultWindowParent = NULL;

//===================================================================
//
WXPLUGIN_API
int setDefaultWindowParent(WindowHandle *windowHandle) {
   defaultWindowParent = windowHandle;
   return 0;
}
//===================================================================
//
WXPLUGIN_API
WindowHandle *getWindowHandle(const char *windowName) {
#if defined(WIN32) && 0
   return FindWindowA(NULL, "Debug - CodeWarrior Development Studio");
#else
   return wxWindow::FindWindowByLabel(_("CodeWarrior Development Studio"), NULL);
#endif
}

//! Used to make sure that any pending events are handled
//!
static void runGuiEventLoop(void) {
#if wxCHECK_VERSION(2, 9, 0)
   wxEventLoopBase  *originalEventLoop = wxEventLoop::GetActive();
   wxEventLoopBase  *eLoop = originalEventLoop;
#else
   wxEventLoop  *originalEventLoop = wxEventLoop::GetActive();
   wxEventLoop  *eLoop = originalEventLoop;
#endif
   if (eLoop == NULL) {
      eLoop = new wxEventLoop;
   }
   wxEventLoopBase::SetActive(eLoop);
   while (eLoop->Pending()) {
//      print("eLoop->Pending == TRUE #1\n");
      eLoop->Dispatch();
   }
   wxEventLoopBase::SetActive(originalEventLoop);
}


//===================================================================
//
WXPLUGIN_API
int displayDialogue(const char *message, const char *caption, long style) {
   //printf("displayDialogue()\n");
   int rc =  wxMessageBox(
               wxString(message, wxConvUTF8), // message
               wxString(caption, wxConvUTF8), // caption
               style,                         // style
               NULL
               );
   runGuiEventLoop();
   return rc;
}

#ifdef _WIN32
//===================================================================
//
int getInstallationDir(char *buff, int size) {
   //printf("getInstallationDir()\n");
   memset(buff, '\0', size);
   wxString path;
   wxRegKey key(wxRegKey::HKLM, "Software\\pgo\\usbdm");
   if (key.Exists() && key.QueryValue("InstallationDirectory", path)) {
      strncpy(buff, (const char*)path.mb_str(wxConvUTF8), size);
      return 0;
   }
   return -1;
}
#endif

//===================================================================
//
WXPLUGIN_API
int getDataDir(char *buff, int size) {
   //printf("getDataDir()\n");
   wxString s = wxStandardPaths::Get().GetDataDir();
   memset(buff, '\0', size);
   strncpy(buff, (const char*)s.mb_str(wxConvUTF8), size);
   return 0;
}
//===================================================================
//
WXPLUGIN_API
int getUserDataDir(char *buff, int size) {
   //printf("getUserDataDir()\n");
   wxString s = wxStandardPaths::Get().GetUserDataDir();
   memset(buff, '\0', size);
   strncpy(buff, (const char*)s.mb_str(wxConvUTF8), size);
   return 0;
}
//===================================================================
//
WXPLUGIN_API
char getPathSeparator(void) {
   //printf("getPathSeparator()\n");
   return (char)wxFileName::GetPathSeparator();
}
//===================================================================
//
class MinimalApp : public  wxApp {
   DECLARE_CLASS( MinimalApp )

public:
   MinimalApp() :
      wxApp() {
//      fprintf(stderr, "MinimalApp::MinimalApp()\n");
   }
   ~MinimalApp(){
//      fprintf(stderr, "MinimalApp::~MinimalApp()\n");
   }
   bool OnInit() {
//      fprintf(stderr, "MinimalApp::OnInit()\n");
      return true;
   }
   int OnExit() {
//      fprintf(stderr, "MinimalApp::OnExit()\n");
      return 0;
   }
};

IMPLEMENT_APP_NO_MAIN( MinimalApp )
IMPLEMENT_CLASS( MinimalApp, wxApp )

static bool wxInitializationDone = false;

static bool dll_open(void) {
   static wxApp* pApp = NULL;
   static int argc = 1;
   static char  arg0[] = "usbdm";
   static char *argv[] = {arg0, NULL};

//   fprintf(stderr, "   dll_open() - pApp = %p\n", pApp);
   if (pApp == NULL) {
//      fprintf(stderr, "   dll_open() - creating MinimalApp\n");
      pApp = new MinimalApp();
      wxApp::SetInstance(pApp);

      wxInitializationDone = wxEntryStart(argc, argv);
//      fprintf(stderr, "   dll_open() - wxTheApp = %p\n", wxTheApp);
//      fprintf(stderr, "   dll_open() - AppName = %s\n", (const char *)wxTheApp->GetAppName().ToAscii());
   }
   if (wxInitializationDone) {
//      fprintf(stderr, "   dll_open() - wxEntryStart() successful\n");
   }
   else {
//      fprintf(stderr, "   dll_open() - wxEntryStart() failed\n");
      return false;
   }
#ifndef _WIN32
   ((wxStandardPaths&)wxStandardPaths::Get()).SetInstallPrefix(_("/usr/local"));
#endif
   return true;
}

#ifdef _WIN32
static bool dll_close(void) {
//   fprintf(stderr, "   dll_close()\n");

   if (wxInitializationDone) {
//      fprintf(stderr, "dll_close() - Doing wxEntryCleanup()\n");
      wxEntryCleanup();
//      fprintf(stderr, "dll_close() - Done wxEntryCleanup()\n");
   }
   return true;
}
#endif

#ifdef __unix__

#ifdef __WXDEBUG__
   #define WXWIDGET_DLL_NAME "libwx_baseud-2.8.so"
   #define DLL_NAME "libusbdm-wx-debug.so.4.8"
#else
   #define WXWIDGET_DLL_NAME "libwx_baseud-2.8.so"
   #define DLL_NAME "libusbdm-wx.so"
#endif

static void *libHandle = NULL;

extern "C"
void __attribute__ ((constructor))
dll_initialize(void) {

   fprintf(stderr, "dll_initialize()...\n");
   dll_open();
   // Lock Library in memory!
   if (libHandle == NULL) {
      libHandle = dlopen(DLL_NAME, RTLD_NOW|RTLD_NODELETE);
      if (libHandle == NULL) {
         fprintf(stderr, "dll_initialize() - Library failed to lock %s\n", dlerror());
         return;
      }
      else {
         fprintf(stderr, "dll_initialize() - Library locked OK (a=%p)\n", libHandle);
      }
   }
   else {
      fprintf(stderr, "dll_initialize() - Library already locked (a=%p)\n", libHandle);
   }
}

extern "C"
void __attribute__ ((destructor))
dll_uninitialize(void) {
//   if (libHandle != NULL)
//      dlclose(libHandle);
   fprintf(stderr, "dll_uninitialize()...\n");
//   dll_close();
   //fprintf(stderr, "dll_uninitialize() - done\n");
}

#else

extern "C"
void
//__attribute__ ((constructor))
dll_initialize(void) {
   //fprintf(stderr, "dll_initialize()\n");
   dll_open();
}

extern "C"
void
//__attribute__ ((destructor))
dll_uninitialize(void) {
   //fprintf(stderr, "dll_uninitialize()\n");
   dll_close();
}

extern "C" WINAPI __declspec(dllexport)
bool DllMain(HINSTANCE  hDLLInst,
             DWORD      fdwReason,
             LPVOID     lpvReserved) {

   switch (fdwReason) {
      case DLL_PROCESS_ATTACH:
//         fprintf(stderr, "=================================\n"
//                         "DLL_PROCESS_ATTACH\n");
         dll_initialize();
         break;
      case DLL_PROCESS_DETACH:
//         fprintf(stderr, "DLL_PROCESS_DETACH\n"
//                         "=================================\n");
         dll_uninitialize();
         break;
      case DLL_THREAD_ATTACH:
         //dll_initialize(_hDLLInst);
         break;
      case DLL_THREAD_DETACH:
         //dll_uninitialize();
         break;
   }
   return TRUE;
}
#endif
