#include <wx/wx.h>
#include <wx/window.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/filefn.h>
#include <wx/app.h>
#include <wx/evtloop.h>
#include <wx/msgdlg.h>
#include <wxPlugin.h>
#include <MyException.h>

#ifdef __unix__
#include <dlfcn.h>
#endif

#ifdef _WIN32
#include <wx/msw/private.h>
#include <wx/msw/registry.h>
#endif

//===================================================================
//
class MinimalApp : public  wxApp {
   DECLARE_CLASS( MinimalApp )

public:
   MinimalApp() :
      wxApp() {
   }
   virtual ~MinimalApp(){
   }
   bool OnInit() {
      return true;
   }
   int OnExit() {
      return 0;
   }
};

#pragma GCC visibility push(default)
MinimalApp *dummyApp;
IMPLEMENT_APP_NO_MAIN(MinimalApp)
IMPLEMENT_CLASS(MinimalApp, wxApp)
#pragma GCC visibility pop

static bool wxInitializationSuccess = false;
//static FILE* logFile = NULL;

static bool createWxAppInstance(void) {
   static int   argc   = 1;
   static char  arg0[] = "usbdm";
   static char *argv[] = {arg0, NULL};

   dummyApp = new MinimalApp();

   wxApp::SetInstance(dummyApp);

   wxInitializationSuccess = wxEntryStart(argc, argv);
   wxInitializationSuccess = wxInitializationSuccess && (wxTheApp != NULL) && wxTheApp->CallOnInit();
//   fprintf(logFile, "createWxAppInstance() - wxInitializationSuccess = %s\n", wxInitializationSuccess?"TRUE":"FALSE");
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
static bool destroyWxAppInstance(void) {
//   fprintf(logFile, "destroyWxAppInstance()\n");
   wxApp* wxApplication = static_cast<wxApp*>(wxApp::GetInstance());
   if (!wxInitializationSuccess) {
//      fprintf(logFile, "destroyWxAppInstance() - wxInitializationSuccess = false, No action)\n");
   }
   else {
      if (wxApplication != dummyApp) {
//         fprintf(logFile, "destroyWxAppInstance() - wxApplication != dummyApp, No action)\n");
      }
      else {
//         fprintf(logFile, "destroyWxAppInstance() - Doing wxEntryCleanup()\n");
         wxEntryCleanup();
//         fprintf(logFile, "destroyWxAppInstance() - Done wxEntryCleanup()\n");
      }
   }
//   fflush(logFile);
   return true;
}
#endif

//! Access to wxApp instance
//! If it doesn't exist then it is created
//!
//! @return reference to the single wxApp instance
//!
DLL_LOCAL
wxApp& getUsbdmWxApp() {
//   static bool reported = false;
//   if (logFile == NULL) {
//      logFile = fopen("c:\\delme.log", "wt");
//   }
   wxApp* wxApplication = static_cast<wxApp*>(wxApp::GetInstance());
//   if ((wxApplication != NULL) && !reported) {
//      fprintf(logFile, "getUsbdmWxApp() - wxApp already exists\n");
//      fflush(logFile);
//   }
   if (wxApplication == NULL) {
      if (!createWxAppInstance()) {
         throw MyException("getUsbdmWxApp() - Creation of wxApp failed");
      }
      wxApplication = static_cast<wxApp*>(wxApp::GetInstance());
      if (wxApplication == NULL) {
         throw MyException("getUsbdmWxApp() - Creation of wxApp failed");
      }
   }
//   reported = true;
   return *wxApplication;
}

#ifdef __unix__

#define DLL_NAME "libusbdm-wx.so"

static void *libHandle = NULL;

extern "C"
void __attribute__ ((constructor))
dll_initialize(void) {
//   fprintf(stderr, "dll_initialize()...\n");
   // Lock Library in memory!
   if (libHandle == NULL) {
      libHandle = dlopen(DLL_NAME, RTLD_NOW|RTLD_NODELETE);
      if (libHandle == NULL) {
         fprintf(stderr, "wxWindowsStub::dll_initialize() - Library \'%s\' failed to lock %s\n", DLL_NAME, dlerror());
         return;
      }
//      else {
//         fprintf(stderr, "wxWindowsStub::dll_initialize() - Library \'%s\' locked OK (a=%p)\n", DLL_NAME, libHandle);
//      }
   }
   else {
      fprintf(stderr, "wxWindowsStub::dll_initialize() - Library \%s\' already locked (a=%p)\n", DLL_NAME, libHandle);
   }
}

extern "C"
void __attribute__ ((destructor))
dll_uninitialize(void) {
//   destroyWxAppInstance();
//   if (libHandle != NULL)
//      dlclose(libHandle);
//   fprintf(stderr, "wxWindowsStub::dll_uninitialize()...\n");
//   dll_close();
   //fprintf(logFile, "wxWindowsStub::dll_uninitialize() - done\n");
}

#else

extern "C" WINAPI __declspec(dllexport)
BOOL DllMain(HINSTANCE  hDLLInst,
             DWORD      fdwReason,
             LPVOID     lpvReserved) {

   switch (fdwReason) {
      case DLL_PROCESS_ATTACH:
//         logFile = fopen("c:\\delme.log", "wt");
//         fprintf(logFile, "=================================\n"
//                          "wxWindowsStub::DLL_PROCESS_ATTACH\n");
//         fflush(logFile);
         break;
      case DLL_PROCESS_DETACH:
         destroyWxAppInstance();
//         fprintf(logFile, "wxWindowsStub::DLL_PROCESS_DETACH\n"
//                          "=================================\n");
//         fflush(logFile);
//         fclose(logFile);
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
