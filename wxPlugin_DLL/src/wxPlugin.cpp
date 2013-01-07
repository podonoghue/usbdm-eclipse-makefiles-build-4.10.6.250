#include <wx/wx.h>
#include <wx/window.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/filefn.h>
#include <wx/app.h>
#include <wx/evtloop.h>
#ifdef __unix__
#include <dlfcn.h>
#endif

#ifdef _WIN32
#include <wx/msw/private.h>
#include <wx/msw/registry.h>
#endif

#include <stdio.h>
#include <string.h>

#include "wxPlugin.h"
#include "myDialog.h"

static wxWindow *topLevelWindow = NULL;

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

#if !defined(_WIN32)
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
#endif

//FILE *logFile = NULL;

//===================================================================
//
WXPLUGIN_API
int displayDialogue(const char *message, const char *caption, long style) {
//   fprintf(logFile, "displayDialogue() before\n");
//   fflush(logFile);
//   MyDialog dialog(topLevelWindow, wxID_ANY, caption, wxDefaultPosition, wxDefaultSize, style);
//   dialog.ShowModal();
//   if (topLevelWindow != NULL) {
//      topLevelWindow->Enable(false);
//   }
   int rc =  wxMessageBox(
               wxString(message, wxConvUTF8), // message
               wxString(caption, wxConvUTF8), // caption
               style|wxCENTRE,                // style
               topLevelWindow                 // parent
               );
//   fprintf(logFile, "displayDialogue() after\n");
//   fflush(logFile);
//   if (topLevelWindow != NULL) {
//      topLevelWindow->Enable(true);
//      topLevelWindow->SetFocus();
//      topLevelWindow->Raise();
//   }
#if !defined(_WIN32)
   runGuiEventLoop();
#endif
   return rc;
}

#ifdef _WIN32
//===================================================================
//
WXPLUGIN_API
int getInstallationDir(char *buff, int size) {
//   fprintf(logFile, "getInstallationDir()\n");
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
   memset(buff, '\0', size);
   wxString s = wxStandardPaths::Get().GetDataDir();
   if (!s.empty()) {
      strncpy(buff, (const char*)s.mb_str(wxConvUTF8), size);
      return 0;
   }
   return -1;
}
//===================================================================
//
WXPLUGIN_API
int getUserDataDir(char *buff, int size) {
   //printf("getUserDataDir()\n");
   memset(buff, '\0', size);
   wxString s = wxStandardPaths::Get().GetUserDataDir();
   if (!s.empty()) {
      strncpy(buff, (const char*)s.mb_str(wxConvUTF8), size);
      return 0;
   }
   return -1;
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
//      fprintf(logFile, "MinimalApp::MinimalApp()\n");
   }
   ~MinimalApp(){
//      fprintf(logFile, "MinimalApp::~MinimalApp()\n");
   }
   bool OnInit() {
//      fprintf(logFile, "MinimalApp::OnInit()\n");
      return true;
   }
   int OnExit() {
//      fprintf(logFile, "MinimalApp::OnExit()\n");
      return 0;
   }
};

static MinimalApp *dummyApp;

//===================================================================
//
WXPLUGIN_API
int setDefaultWindowParent(WindowHandle *windowHandle) {
//   fprintf(logFile, "setDefaultWindowParent() windowHandle = %p\n", windowHandle);
//   fflush(logFile);
   topLevelWindow = new wxWindow();
   topLevelWindow->SetHWND((WXHWND)windowHandle);
   topLevelWindow->AdoptAttributesFromHWND();
   dummyApp->SetTopWindow(topLevelWindow);
   return 0;
}

IMPLEMENT_APP_NO_MAIN(MinimalApp)
IMPLEMENT_CLASS(MinimalApp, wxApp)

static bool wxInitializationSuccess = false;

static bool dll_open(void) {
   static int   argc   = 1;
   static char  arg0[] = "usbdm";
   static char *argv[] = {arg0, NULL};

//   logFile = fopen("c:\\delme.log", "wt");

   dummyApp = new MinimalApp();

   wxApp::SetInstance(dummyApp);

   wxInitializationSuccess = wxEntryStart(argc, argv);
   wxInitializationSuccess = wxInitializationSuccess && (wxTheApp != NULL) && wxTheApp->CallOnInit();
//   fprintf(logFile, "dll_open() - wxInitializationSuccess = %s\n", wxInitializationSuccess?"TRUE":"FALSE");
//   fflush(logFile);
   if (!wxInitializationSuccess) {
      return false;
   }
#ifndef _WIN32
   ((wxStandardPaths&)wxStandardPaths::Get()).SetInstallPrefix(_("/usr/local"));
#endif
   return true;
}

#ifdef _WIN32
static bool dll_close(void) {
//   fprintf(logFile, "dll_close()\n");
   if (wxInitializationSuccess) {
//      fprintf(logFile, "dll_close() - Doing wxEntryCleanup()\n");
      wxEntryCleanup();
//      fprintf(logFile, "dll_close() - Done wxEntryCleanup()\n");
   }
//   fflush(logFile); fclose(logFile);
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

   fprintf(logFile, "dll_initialize()...\n");
   dll_open();
   // Lock Library in memory!
   if (libHandle == NULL) {
      libHandle = dlopen(DLL_NAME, RTLD_NOW|RTLD_NODELETE);
      if (libHandle == NULL) {
         fprintf(logFile, "dll_initialize() - Library failed to lock %s\n", dlerror());
         return;
      }
      else {
         fprintf(logFile, "dll_initialize() - Library locked OK (a=%p)\n", libHandle);
      }
   }
   else {
      fprintf(logFile, "dll_initialize() - Library already locked (a=%p)\n", libHandle);
   }
}

extern "C"
void __attribute__ ((destructor))
dll_uninitialize(void) {
//   if (libHandle != NULL)
//      dlclose(libHandle);
   fprintf(logFile, "dll_uninitialize()...\n");
//   dll_close();
   //fprintf(logFile, "dll_uninitialize() - done\n");
}

#else

extern "C"
void
dll_initialize(void) {
   dll_open();
}

extern "C"
void
dll_uninitialize(void) {
   dll_close();
}

extern "C" WINAPI __declspec(dllexport)
bool DllMain(HINSTANCE  hDLLInst,
             DWORD      fdwReason,
             LPVOID     lpvReserved) {

   switch (fdwReason) {
      case DLL_PROCESS_ATTACH:
//         fprintf(logFile, "=================================\n"
//                         "DLL_PROCESS_ATTACH\n");
         dll_open();
         break;
      case DLL_PROCESS_DETACH:
//         fprintf(logFile, "DLL_PROCESS_DETACH\n"
//                         "=================================\n");
         dll_close();
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
