/*!
 * GdbServerWindow.h
 *
 *  Created on: 30/06/2013
 *      Author: Peter
 \verbatim
Change History
-==================================================================================
| 30 Jun 2013 | Created                                                       - pgo
+==================================================================================
\endverbatim

 */

#ifndef GDBSERVERWINDOW_H_
#define GDBSERVERWINDOW_H_

#include <wx/socket.h>
#include <wx/timer.h>
typedef wxIPV4address IPaddress;

#include "Shared.h"
#include "DeviceData.h"
#include "USBDM_API.h"
#include "GdbInOutWx.h"
#include "GdbHandler.h"

class GdbServerWindow : public wxFrame {
private:
   class GdbMessageWrapper {
   private:
      static GdbServerWindow *me;
      static USBDM_ErrorCode callback(const char *msg, GdbMessageLevel level, USBDM_ErrorCode rc);

   public:
      static GdbCallback getCallBack(GdbServerWindow *me) {
         GdbMessageWrapper::me = me;
         return callback;
      }
   };

public:
   GdbServerWindow(SharedPtr shared, AppSettings &appSettings);
   ~GdbServerWindow();

   USBDM_ErrorCode execute(bool skipOpeningDialogue);
   USBDM_ErrorCode doSettingsDialogue();
   bool confirmDropConnection();

   // Menu handlers
   void OnChangeSettings(wxCommandEvent& event);
   void OnDropConnection(wxCommandEvent& event);
   void OnAbout(wxCommandEvent& event);
   void OnQuit(wxCommandEvent& event);
   void OnCloseWindow(wxCloseEvent& event);

   void OnClearLog(wxCommandEvent& event);
   void OnDisableLog(wxCommandEvent& event);
   void OnModerateLog(wxCommandEvent& event);
   void OnVerboseLog(wxCommandEvent& event);
   void OnShowLogWindow(wxCommandEvent& event);

   void OnResetTarget(wxCommandEvent& event);
   void OnSetSpeed(wxCommandEvent& event);

   // Timer Event handler
   void OnTimer(wxTimerEvent& event);

   // Socket events
   void OnServerEvent(wxSocketEvent& event);
   void OnSocketEvent(wxSocketEvent& event);

   void createServer();
   void closeServer();
   void dropConnection();

//   USBDM_ErrorCode openBDM();
//   USBDM_ErrorCode closeBDM();

   // Convenience functions
   void UpdateStatusBar();
   void pollTarget();

   GdbMessageLevel getLoggingLevel() {
      return loggingLevel;
   }

    void setLoggingLevel(GdbMessageLevel level) {
      loggingLevel = level;
   }

   USBDM_ErrorCode reportError(const char *msg, GdbMessageLevel level, USBDM_ErrorCode rc);

private:
   static wxString getAddr(IPaddress addr);
   void setDeferredFail(bool value = true) {
      deferredFail = value;
   }

private:
   wxPanel                 *mainPanel;
   wxTextCtrl              *statusTextControl;
   wxMenuBar               *menuBar;

   wxString                 serverAddr;         // Current server address as string
   wxString                 clientAddr;         // Current client address as string
   wxSocketServer          *serverSocket;       // Server socket
   wxSocketBase            *clientSocket;       // Client socket

   SharedPtr                shared;
   AppSettings             &appSettings;

   GdbMessageLevel          loggingLevel;
   GdbTargetStatus          targetStatus;

   typedef enum {idle, listening, connected, abort} ServerState;
   ServerState              serverState;

   GdbInOutWx              *gdbInOut;

   wxTimer                 *statusTimer;

   bool                     deferredFail;
   bool                     deferredOpen;

   static const int pollIntervalFast = 100;      // ms
   static const int pollIntervalSlow = 1000;     // ms

   // any class wishing to process wxWidgets events must use this macro
   DECLARE_EVENT_TABLE()
};
#endif /* GDBSERVERWINDOW_H_ */
