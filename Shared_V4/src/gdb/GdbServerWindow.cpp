/*!
 * GdbServerWindow.cpp
 *
 *  Created on: 30/06/2013
 *      Author: Peter
 *
 \verbatim
Change History
-==================================================================================
| 30 Jun 2013 | Created                                                       - pgo
+==================================================================================
\endverbatim

 */

// for all others, include the necessary headers
#ifndef WX_PRECOMP
#  include "wx/wx.h"
#endif

#include "wx/busyinfo.h"
#include "GdbServerWindow.h"
#include "GdbMiscellaneous.h"
#include "USBDMDialogue.h"
#include "GdbHandler.h"

#include "Log.h"

// --------------------------------------------------------------------------
// constants
// --------------------------------------------------------------------------

// IDs for the controls and the menu commands
enum
{
   // menu items
   SERVER_QUIT = wxID_EXIT,
   SERVER_ABOUT = wxID_ABOUT,
   SERVER_CLEARLOG,
   SERVER_RESTART,
   SERVER_DROPCONNECTION,
   SERVER_SHOWLOGWINDOW,
   SERVER_DISABLEOFF,
   SERVER_MODERATELOG,
   SERVER_VERBOSELOG,
   SERVER_STATUSTIMER,
   SERVER_RESETTARGET,
   SERVER_SETSPEED,
   SERVER_TOGGLEMASKISR,
   SERVER_HALTTARGET,
   // id for sockets
   SERVER_ID = 100,
   SOCKET_ID,
};

// --------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// --------------------------------------------------------------------------

BEGIN_EVENT_TABLE(GdbServerWindow, wxFrame)
   EVT_MENU(SERVER_RESTART,            GdbServerWindow::OnChangeSettings)
   EVT_MENU(SERVER_DROPCONNECTION,     GdbServerWindow::OnDropConnection)
   EVT_MENU(SERVER_QUIT,               GdbServerWindow::OnQuit)

   EVT_MENU(SERVER_CLEARLOG,           GdbServerWindow::OnClearLog)
   EVT_MENU(SERVER_SHOWLOGWINDOW,      GdbServerWindow::OnShowLogWindow)
   EVT_MENU(SERVER_DISABLEOFF,         GdbServerWindow::OnDisableLog)
   EVT_MENU(SERVER_MODERATELOG,        GdbServerWindow::OnModerateLog)
   EVT_MENU(SERVER_VERBOSELOG,         GdbServerWindow::OnVerboseLog)

   EVT_MENU(SERVER_HALTTARGET,         GdbServerWindow::OnHaltTarget)
   EVT_MENU(SERVER_RESETTARGET,        GdbServerWindow::OnResetTarget)
   EVT_MENU(SERVER_SETSPEED,           GdbServerWindow::OnSetSpeed)

   EVT_MENU(SERVER_TOGGLEMASKISR,      GdbServerWindow::OnToggleMaskISR)
   EVT_MENU(SERVER_RESETTARGET,        GdbServerWindow::OnResetTarget)

   EVT_SOCKET(SERVER_ID,               GdbServerWindow::OnServerEvent)
   EVT_SOCKET(SOCKET_ID,               GdbServerWindow::OnSocketEvent)
   EVT_TIMER(SERVER_STATUSTIMER,       GdbServerWindow::OnTimer)

   EVT_CLOSE(GdbServerWindow::OnCloseWindow)
END_EVENT_TABLE()

// --------------------------------------------------------------------------
// main frame
// --------------------------------------------------------------------------

/*  Constructor
 */
GdbServerWindow::GdbServerWindow(SharedPtr shared, AppSettings &appSettings) :
   wxFrame((wxFrame *)NULL, wxID_ANY, _("USBDM GDB Server"), wxDefaultPosition, wxDefaultSize),
   shared(shared),
   appSettings(appSettings),
   loggingLevel(M_ERROR),
   targetStatus(T_UNKNOWN),
   serverState(idle),
   gdbInOut(NULL),
   statusTimer(NULL),
   deferredFail(false),
   deferredOpen(false) {
   LOGGING;

   serverSocket = NULL;
   clientSocket = NULL;

   // Make menus
   menuBar = new wxMenuBar();

   wxMenu *menuServer = new wxMenu();
   menuServer->Append(SERVER_RESTART,        _("&Change Server Settings"),  _("Restarts server with new settings"));
   menuServer->AppendSeparator();
   menuServer->Append(SERVER_DROPCONNECTION, _("&Drop Connection"),  _("Forcibly drop connection"));
   menuServer->Append(SERVER_QUIT,           _("E&xit\tAlt-X"),      _("Quit server"));
   menuBar->Append(menuServer,               _("&Server"));

   wxMenu *menuLog = new wxMenu();
   menuLog->Append(SERVER_CLEARLOG,          _("&Clear"),            _("Clear log window"));
   menuLog->Append(SERVER_DISABLEOFF,        _("&Off"),              _("Turn off logging"),         wxITEM_RADIO);
   menuLog->Append(SERVER_MODERATELOG,       _("&Moderate"),         _("Turn on moderate logging"), wxITEM_RADIO);
   menuLog->Append(SERVER_VERBOSELOG,        _("&Verbose"),          _("Turn on verbose logging"),  wxITEM_RADIO);
   menuBar->Append(menuLog, _("&Log"));

   wxMenu *menuTarget = new wxMenu();
   menuTarget->Append(SERVER_RESETTARGET,     _("&Reset"),                 _("Reset target"));
   menuTarget->Append(SERVER_TOGGLEMASKISR,   _("&Disable Interrrupts"),   _("Disable interrupts when stepping"), wxITEM_CHECK);
   menuTarget->Check(SERVER_TOGGLEMASKISR, getMaskISR());

//   menuTarget->Append(SERVER_SETSPEED,        _("&Interface Speed"), _("Set communication speed"));
   menuBar->Append(menuTarget, _("&Target"));

   SetMenuBar(menuBar);

#if wxUSE_STATUSBAR
   // Status bar
   CreateStatusBar(3);
#endif // wxUSE_STATUSBAR

   const int borderWidth = 3;

   wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
   mainPanel = new wxPanel(this, wxID_ANY,
                           wxDefaultPosition, wxDefaultSize,
                           wxTAB_TRAVERSAL, _("mypanel"));
   mainPanel->SetSizer(panelSizer);

   // Make a textctrl for logging
   statusTextControl  = new wxTextCtrl(mainPanel, wxID_ANY,
                                       _("Welcome to USBDM GDB server\n"),
                                       wxDefaultPosition, wxSize(400,100),
                                       wxTE_MULTILINE | wxTE_READONLY);

   panelSizer->Add(statusTextControl, 1, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, borderWidth);
}

USBDM_ErrorCode GdbServerWindow::execute(bool skipOpeningDialogue) {
   if (!skipOpeningDialogue) {
      doSettingsDialogue();
   }
   Show();

   createServer();

   return BDM_RC_OK;
}

USBDM_ErrorCode GdbServerWindow::doSettingsDialogue() {
   LOGGING;

   // Create the setting dialogue
   UsbdmDialogue usbdmDialogue(shared, appSettings, _("GDB Settings"));
   usbdmDialogue.enableSettingsAreNotPersistent(true);
   return usbdmDialogue.execute();
}

/* Destructor
 */
GdbServerWindow::~GdbServerWindow() {
   // No delayed deletion here, as the frame is dying anyway
   delete serverSocket;
   serverSocket = NULL;
   delete clientSocket;
   clientSocket = NULL;
   delete statusTimer;
   statusTimer = NULL;
}

/*!
 *  Translate a IPaddress into a meaningful string
 *
 *  @param addr The address to translate
 *
 *  @return A string representing the addr e.g. localhost:1099
 */
wxString GdbServerWindow::getAddr(IPaddress addr) {
   wxString *serverAddr = new wxString();

   if (addr.IPAddress().compare(_("127.0.0.1")) == 0) {
      serverAddr->Printf(_("localhost:%u"), addr.Service());
   }
   else {
      serverAddr->Printf(_("%s:%u"), (const char *)addr.IPAddress().c_str(), addr.Service());
   }
   return *serverAddr;
}

/*!
 *  Create server listening on socket
 *  Subscribes to connection events with ID SERVER_ID
 */
void GdbServerWindow::createServer() {

   // Create the address
   IPaddress listenAddr;
   listenAddr.Service(shared->getGdbServerPort());
   listenAddr.Hostname(_("localhost"));
   serverAddr = getAddr(listenAddr);

   closeServer();

   // Create the socket
   serverSocket = new wxSocketServer(listenAddr, wxSOCKET_NOWAIT);

   // We use IsOk() here to see if the server is really listening
   if (!serverSocket->IsOk()) {
      statusTextControl->AppendText(_("ERROR: Could not create server at the specified port !\n"));
      return;
   }

   string bdmSerialNumber = shared->getBdmSerialNumber();
   if (bdmSerialNumber.length() > 0) {
      if (shared->getBdmMatchRequired()) {
         statusTextControl->AppendText(_("Using required USBDM interface S/N = \'")+wxString(bdmSerialNumber.c_str(), wxConvUTF8)+_("\'\n"));
      }
      else {
         statusTextControl->AppendText(_("Using preferred USBDM interface S/N = \'")+wxString(bdmSerialNumber.c_str(), wxConvUTF8)+_("\'\n"));
      }
   }
   else {
      statusTextControl->AppendText(_("Using any suitable USBDM interface\n"));
   }
   IPaddress addrReal;
   if (!serverSocket->GetLocal(addrReal) ) {
      statusTextControl->AppendText(_("ERROR: couldn't get the address we bound to\n"));
   }
   else {
      serverAddr = getAddr(addrReal);
      wxString s;
      s.Printf(_("Server created @%s\n"), (const char *)serverAddr.c_str());
      statusTextControl->AppendText(s);
   }

   // Setup the event handler and subscribe to connection events
   serverSocket->SetEventHandler(*this, SERVER_ID);
   serverSocket->SetNotify(wxSOCKET_CONNECTION_FLAG);
   serverSocket->Notify(true);

   serverState = listening;

   UpdateStatusBar();
}

void GdbServerWindow::closeServer() {

   dropConnection();

   if (serverSocket != NULL) {
      statusTextControl->AppendText(_("Stopping Server\n"));
      serverSocket->Destroy();
      serverSocket = NULL;
   }
   serverState = idle;
   UpdateStatusBar();
}

bool GdbServerWindow::confirmDropConnection() {
   if (serverState != connected) {
      return true;
   }
   int getYesNo = wxMessageBox(
                _("There is a current GDB connection.\n\nDrop this connection?"),
                _("Active Connection Warning"),
                wxOK|wxCANCEL,
                this
                );
   return (getYesNo == wxOK);
}

//===========================================================================
// event handlers
//===========================================================================

/*!  Handler for Drop connection menu item
 *
 */
void GdbServerWindow::OnDropConnection(wxCommandEvent& WXUNUSED(event)) {
   if ((clientSocket != NULL) && confirmDropConnection()) {
      dropConnection();
   }
}

/*!   Handler for Quit button
 *
 */
void GdbServerWindow::OnChangeSettings(wxCommandEvent& WXUNUSED(event)) {
   if (confirmDropConnection()) {
      closeServer();
      serverState = abort;
      doSettingsDialogue();
      createServer();
   }
}

/*!   Handler for Quit button
 *
 */
void GdbServerWindow::OnQuit(wxCommandEvent& WXUNUSED(event)) {
   Close(false);
}

void GdbServerWindow::OnCloseWindow(wxCloseEvent& event) {
   if (!event.CanVeto() || confirmDropConnection())  {
      dropConnection();
      this->Destroy();
   }
   else {
      event.Veto();
   }
}

/*!  Handler for Clear Log Button
 *
 */
void GdbServerWindow::OnClearLog(wxCommandEvent& WXUNUSED(event)) {
   statusTextControl->Clear();
}

/*!   Verbose log checkbox menu item
 *
 */
void GdbServerWindow::OnDisableLog(wxCommandEvent& event) {
   setLoggingLevel(M_ERROR);
}

/*!   Verbose log checkbox menu item
 *
 */
void GdbServerWindow::OnModerateLog(wxCommandEvent& event) {
   setLoggingLevel(M_INFO);
}

/*!   Verbose log checkbox menu item
 *
 */
void GdbServerWindow::OnVerboseLog(wxCommandEvent& event) {
   setLoggingLevel(M_BORINGINFO);
}

/*!  Handler for Show/Hide Log checkbox menu item
 *
 */
void GdbServerWindow::OnShowLogWindow(wxCommandEvent& event) {
   static bool visible = event.IsChecked();

   mainPanel->Show(visible);
//   if (!mainPanel->GetSizer()->Show(mainPanel, visible, true)) {
//      statusTextControl->AppendText("Didn't find mainPanel\n");
//   }
   statusTextControl->Show(visible);
   mainPanel->GetSizer()->Layout();
   mainPanel->GetSizer()->Fit(this);
//   this->Fit();
}

/*!  Handler for Reset Target menu item
 *
 */
void GdbServerWindow::OnResetTarget(wxCommandEvent& event) {
   usbdmResetTarget();
   statusTextControl->AppendText(_("User reset of target - step GDB to synchronise\n"));
}

/*!  Handler for Reset Target menu item
 *
 */
void GdbServerWindow::OnHaltTarget(wxCommandEvent& event) {
   USBDM_TargetHalt();
   statusTextControl->AppendText(_("User halt of target - step GDB to synchronise\n"));
}

/*!  Handler for Reset Target menu item
 *
 */
void GdbServerWindow::OnToggleMaskISR(wxCommandEvent& event) {
   bool disableInterrupts = event.IsChecked();
   setMaskISR(disableInterrupts);
}

/*!  Handler for Set Speed menu item
 *
 */
void GdbServerWindow::OnSetSpeed(wxCommandEvent& event) {
}

/*!
 *  Handler for Server events (before connection)
 *
 *  - Only expects connection events wxSOCKET_CONNECTION
 *  - Creates new socket and adds handler for socket events
 *
 *  @param event Event to handle
 */
void GdbServerWindow::OnServerEvent(wxSocketEvent& event) {
   if (event.GetSocketEvent() != wxSOCKET_CONNECTION) {
      statusTextControl->AppendText(_("Unexpected event on Server\n"));
      // Ignore
      return;
   }

   if (clientSocket != NULL) {
      statusTextControl->AppendText(_("Client connection while busy - rejected\n"));
      wxSocketBase *clientSocket = serverSocket->Accept(false);
      clientSocket->Destroy();
      return;
   }

   // Accept new connection if there is one in the pending
   // connections queue, else exit. We use Accept(false) for
   // non-blocking accept (although if we got here, there
   // should ALWAYS be a pending connection).

   clientSocket = serverSocket->Accept(false);
   if (clientSocket == NULL) {
      statusTextControl->AppendText(_("Error: couldn't accept a new connection\n"));
      return;
   }

   IPaddress peerAddr;
   if ( !clientSocket->GetPeer(peerAddr) ) {
      statusTextControl->AppendText(_("New connection from unknown client accepted.\n"));
   }
   else {
      clientAddr = getAddr(peerAddr);
      statusTextControl->AppendText(_(
            "\n=====================================\n"
            "New client connection from ")+ clientAddr + _(" accepted\n"));
   }

   // Subscribe to socket events
   //  wxSOCKET_INPUT_FLAG - received data
   //  wxSOCKET_LOST_FLAG  - lost connection
   clientSocket->SetEventHandler(*this, SOCKET_ID);
   clientSocket->SetNotify(wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
   clientSocket->Notify(true);

   setDeferredFail(false);
   deferredOpen = true;

   statusTimer = new wxTimer(this, SERVER_STATUSTIMER);
   statusTimer->Start(pollIntervalSlow, wxTIMER_ONE_SHOT);

   serverState = connected;
   UpdateStatusBar();
}

/*! Handler for Timer events
 *
 *   - Handles polling target when running
 */
void GdbServerWindow::OnTimer(wxTimerEvent& event) {
   pollTarget();
}

/*! Drop client connection and clean up
 *
 */
void GdbServerWindow::dropConnection() {
   if (gdbInOut != NULL) {
      gdbInOut->finish();
      delete gdbInOut;
      gdbInOut = NULL;
   }
   if (statusTimer != NULL) {
      statusTimer->Stop();
      delete statusTimer;
      statusTimer = NULL;
   }
   shared->closeBdm();
   if (clientSocket != NULL) {
      clientSocket->Destroy();
      clientSocket = NULL;
      statusTextControl->AppendText(_(
            "\n=====================\n"
            "Dropped connection\n"));
      if (!deferredOpen && shared->isExitOnClose()) {
         statusTextControl->AppendText(_("Closing\n\n"));
         Close(true);
      }
   }
   serverState  = listening;
   clientAddr = _("None");
   targetStatus = T_UNKNOWN;
   UpdateStatusBar();
}

/*!  Report error message
 *
 *   @param msg   Message to display
 *   @param rc    Error code
 */
USBDM_ErrorCode GdbServerWindow::reportError(const char *msg, GdbMessageLevel level, USBDM_ErrorCode rc) {

   if ((rc != BDM_RC_OK) || (level >= getLoggingLevel())) {
      statusTextControl->AppendText(wxString(msg, wxConvUTF8));
      if (level == M_FATAL) {
         setDeferredFail();
      }
   }
   if (rc != BDM_RC_OK) {
      statusTextControl->AppendText(wxString(USBDM_GetErrorString(rc), wxConvUTF8));
      statusTextControl->AppendText(_("\n"));

      Iconize(false); // restore the window if minimized
      SetFocus();     // focus on my window
      Raise();        // bring window to front
      Show(true);     // show the window
      wxMessageBox(
         wxString(USBDM_GetErrorString(rc), wxConvUTF8), /* message */
         wxString(msg, wxConvUTF8),                      /* caption */
         wxOK|wxICON_ERROR,                              /* style   */
         this                                            /* parent  */
         );
   }
   return rc;
}

GdbServerWindow *GdbServerWindow::GdbMessageWrapper::me = NULL; //!< handle on GdbServerWindow

/*! Call back to display messages from GDB handler
 *
 *   @param msg   Message to display
 *   @param level Level
 *   @param rc    Error code
 *
 *   @return      Modified error code
 */
USBDM_ErrorCode GdbServerWindow::GdbMessageWrapper::callback(const char *msg, GdbMessageLevel level, USBDM_ErrorCode rc) {
   return me->reportError(msg, level, rc);
}

/*!
 *  Handler for Socket events (after connection)
 *
 *  - Only expects:
 *    - wxSOCKET_INPUT - New data
 *    - wxSOCKET_LOST  - Connection dropped
 *
 *  @param event Event to handle
 */
void GdbServerWindow::OnSocketEvent(wxSocketEvent& event) {

   if (event.GetSocket() != clientSocket) {
      statusTextControl->AppendText(_("Event from unknown socket\n"));
      return;
   }
   // Now we process the event
   switch(event.GetSocketEvent()) {
      case wxSOCKET_INPUT: {
         if (clientSocket != NULL) {
            clientSocket->SetNotify(wxSOCKET_LOST_FLAG);
         }
         if (deferredOpen) {
            // Open on first access after socket creation
            deferredOpen = false;

            USBDM_ErrorCode rc = shared->initBdm();
            if (rc != BDM_RC_OK) {
               reportError("BDM Open failed, reason: ", M_FATAL, rc);
               statusTextControl->AppendText(_("BDM Open failed\n"));
               dropConnection();
               return;
            }

            gdbInOut = new GdbInOutWx(clientSocket, statusTextControl);
            GdbCallback cb = GdbMessageWrapper::getCallBack(this);

            rc = gdbHandlerInit(gdbInOut, *shared->getCurrentDevice(), cb);
            if (rc != BDM_RC_OK) {
               reportError("GDB Handler initialisation failed, reason: ", M_FATAL, rc);
               dropConnection();
               return;
            }
            statusTextControl->AppendText(_("BDM Open OK\n"));
         }
         // Triggers read of socket
         const GdbPacket *packet;
         USBDM_ErrorCode rc = BDM_RC_OK;
         do {
            // Process packets from GDB until idle
            packet = gdbInOut->getGdbPacket();
            if (packet != NULL) {
               rc = doGdbCommand(packet);
               if (rc != BDM_RC_OK) {
                  statusTextControl->AppendText(wxString(USBDM_GetErrorString(rc),wxConvUTF8));
               }
            }
         } while ((packet != NULL) && (rc == BDM_RC_OK) && !deferredFail);

         if (deferredFail) {
            // A fatal error was reported - drop connection
            dropConnection();
         }
         else {
            // Poll target immediately (also adjusts polling rate)
            pollTarget();
         }
         if (clientSocket != NULL) {
            clientSocket->SetNotify(wxSOCKET_LOST_FLAG | wxSOCKET_INPUT_FLAG);
         }
         break;
      }
      case wxSOCKET_LOST: {
         serverState = listening;
         dropConnection();
         break;
      }
      default:
         statusTextControl->AppendText(_("Unexpected event on socket!\n"));
         break;
   }
   UpdateStatusBar();
}

/*!  Poll target to check run status
 *
 */
void GdbServerWindow::pollTarget() {
   static GdbTargetStatus lastTargetStatus = T_UNKNOWN;

   // Get status without polling target
   targetStatus = getGdbTargetStatus();
   switch (targetStatus) {
      case T_RUNNING:
      case T_SLEEPING:
         // Actually poll the target
         targetStatus = gdbPollTarget();
         // Set up next polling time
         statusTimer->Start(pollIntervalFast, wxTIMER_ONE_SHOT);
         break;
      case T_NOCONNECTION:
         dropConnection();
         break;
      case T_UNKNOWN:
      case T_HALT:
         // Don't poll while not running
         break;
   }
   if (targetStatus != lastTargetStatus) {
      UpdateStatusBar();
   }
   lastTargetStatus = targetStatus;
}

/*!  Update status bar
 *
 */
void GdbServerWindow::UpdateStatusBar() {
#if wxUSE_STATUSBAR
   wxString serverStatusString = wxEmptyString;
   switch(serverState) {
      case idle :
         serverStatusString = _("Server not running");
         break;
      case connected :
         serverStatusString = _("Client @") + clientAddr;
         break;
      case listening :
         serverStatusString = _("Listening @") + serverAddr;
         break;
      case abort :
         serverStatusString = _("Server Abort");
         break;
   }
   SetStatusText(serverStatusString, 1);
//   dropConnectionButton->Enable(serverState == connected);

   wxString targetStatusString = wxEmptyString;
   switch (targetStatus) {
      case T_RUNNING:
         targetStatusString = _("Running");
         break;
      case T_SLEEPING:
         targetStatusString = _("Sleeping");
         break;
      case T_HALT:
         targetStatusString = _("Stopped");
         break;
      default:
         targetStatusString = _("");
         break;
   }
   SetStatusText(targetStatusString, 2);
#endif // wxUSE_STATUSBAR
}
