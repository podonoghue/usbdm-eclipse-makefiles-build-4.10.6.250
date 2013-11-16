/*
 *

\verbatim
Change History
-==============================================================================================
|  7 Nov 2013 | Changed displayDialogue() back to previous method for WIN32   - pgo V4.10.6.60
|  7 Nov 2013 | Corrected return values in displayDialogue()                  - pgo V4.10.6.60
| 12 Oct 2013 | Improved hiding of dummy parent window in linux               - pgo
| 16 Jul 2013 | Added creation of a parent window                             - pgo
|        ???? | Created                                                       - pgo
+==============================================================================================
\endverbatim

*/
#include <wx/wx.h>
#include <wx/window.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/filefn.h>
#include <wx/app.h>
#include <wx/evtloop.h>
#include <wx/msgdlg.h>

#include <MyException.h>

#ifdef __unix__
#include <dlfcn.h>
#endif

#ifdef _WIN32
#include <wx/msw/private.h>
#include <wx/msw/registry.h>
#endif

#include <stdio.h>
#include <string.h>

#include "Utils.h"

#include "wxPlugin.h"
#include "myDialog.h"

static wxTopLevelWindow *topLevelWindow = NULL;

DLL_LOCAL wxApp& getUsbdmWxApp();

//===================================================================
//
WXPLUGIN_API
WindowHandle *getWindowHandle(const char *windowName) {
#if defined(WIN32) && 0
   return FindWindowA(NULL, "Debug - CodeWarrior Development Studio");
#else
   getUsbdmWxApp();
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
//      fprintf(stderr, "eLoop->Pending == TRUE #1\n");
      eLoop->Dispatch();
   }
//   fprintf(stderr, "eLoop->Pending == FALSE #1\n");
   wxEventLoopBase::SetActive(originalEventLoop);
}
#endif

//FILE *logFile = NULL;

//===================================================================
//
WXPLUGIN_API
int displayDialogue(const char *message, const char *caption, long style) {
   getUsbdmWxApp();

//   fprintf(logFile, "displayDialogue() before\n");
//   fflush(logFile);
//   MyDialog dialog(topLevelWindow, wxID_ANY, caption, wxDefaultPosition, wxDefaultSize, style);
//   dialog.ShowModal();
//   if (topLevelWindow != NULL) {
//      topLevelWindow->Enable(false);
//   }
#if defined(_WIN32)
   int rc =  wxMessageBox(
               wxString(message, wxConvUTF8), // message
               wxString(caption, wxConvUTF8), // caption
               style|wxCENTRE,                // style
               topLevelWindow                 // parent
               );
#else
   wxTopLevelWindow *tlw;
   tlw = topLevelWindow;
   if (tlw == NULL) {
      // Make a minimal window to use
      tlw = new wxFrame(NULL, wxID_ANY, _("Dummy window"), wxDefaultPosition, wxSize(10,10));
   }
   getUsbdmWxApp().SetTopWindow(tlw);
   tlw->Centre(wxBOTH);
   tlw->Show(true);                  // show the window
   ((wxFrame*)tlw)->Iconize(false);  // restore the window if minimized
   tlw->SetFocus();                  // focus on my window
   tlw->Raise();                     // bring window to front
   milliSleep(100);
   wxMessageDialog dialogue(tlw,
                     wxString(message, wxConvUTF8), // message
                     wxString(caption, wxConvUTF8), // caption
                     style|wxCENTRE                 // style
                     );
   int rc = dialogue.ShowModal();         // show the window
   switch (rc) {
      case wxID_OK:     rc = wxOK;     break;
      case wxID_CANCEL: rc = wxCANCEL; break;
      case wxID_YES:    rc = wxYES;    break;
      case wxID_NO:     rc = wxNO;     break;
      default:;
   }
//   fprintf(stderr, "Hiding Window\n");
   tlw->Show(false);
//   fprintf(stderr, "Closing Window\n");
   tlw->Close(true);
   if (tlw != topLevelWindow) {
      // If we made the window, destroy it
//      fprintf(stderr, "Deleting Window\n");
      tlw->Destroy();
   }
   tlw = NULL;
#endif
#if !defined(_WIN32)
//   fprintf(stderr, "calling runGuiEventLoop()\n");
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
   getUsbdmWxApp();
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
   getUsbdmWxApp();
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
   getUsbdmWxApp();
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
   getUsbdmWxApp();
   return (char)wxFileName::GetPathSeparator();
}

//===================================================================
//
WXPLUGIN_API
int setDefaultWindowParent(WindowHandle *windowHandle) {
//   fprintf(logFile, "setDefaultWindowParent() windowHandle = %p\n", windowHandle);
//   fflush(logFile);
#ifdef WIN32
   wxApp& wxApplication = getUsbdmWxApp();
   topLevelWindow = new wxTopLevelWindow();
   topLevelWindow->SetHWND((WXHWND)windowHandle);
   topLevelWindow->AdoptAttributesFromHWND();
   wxApplication.SetTopWindow(topLevelWindow);
#endif
   return 0;
}
