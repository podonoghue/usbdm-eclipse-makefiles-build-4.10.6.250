/*! \file
    \brief Implements USBDM dialogue

   UsbdmDialogue.cpp

    \verbatim
    USBDM
    Copyright (C) 2009  Peter O'Donoghue

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
    \endverbatim

    \verbatim
   Change History
   -=============================================================================================
   | 16 Jan 2013 | Corrected exit of UsbdmDialogue::Init() on exception             - pgo 4.10.4a
   |  1 Jul 2010 | wxWidgets version created                                        - pgo
   +=============================================================================================
   \endverbatim
 */

// For compilers that support precompilation, includes <wx/wx.h>.
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/imaglist.h>
#include <wx/gbsizer.h>
#include <wx/msgdlg.h>

#include "Common.h"
#include "Version.h"
#include "USBDM_API.h"
#include "ApplicationFiles.h"
#include "Log.h"
#include "AppSettings.h"
#include "UsbdmDialogue.h"
#include "InterfacePanel.h"
#include "TargetPanel.h"
#include "AdvancedPanel.h"
#if TARGET == MC56F80xx
#include "USBDM_DSC_API.h"
#endif
#include "Shared.h"

const string UsbdmDialogue::settingsKey("UsbdmDialogue");

/*
 * UsbdmDialogue type definition
 */
IMPLEMENT_CLASS( UsbdmDialogue, wxDialog )

//
//  UsbdmDialogue event table definition
//
BEGIN_EVENT_TABLE( UsbdmDialogue, wxDialog )
   EVT_CHECKBOX( ID_DONT_SHOW_AGAIN_CHECKBOX, UsbdmDialogue::OnDontShowAgainControlClick )
   EVT_BUTTON( wxID_DEFAULT, UsbdmDialogue::OnDefaultClick )
//#ifdef GDI
   EVT_BUTTON( wxID_OK, UsbdmDialogue::OnOkClick )
//#endif
   EVT_BUTTON( wxID_CANCEL, UsbdmDialogue::OnCancelClick )
   EVT_NOTEBOOK_PAGE_CHANGING( ID_NOTEBOOK, UsbdmDialogue::OnSelChanging )
   EVT_NOTEBOOK_PAGE_CHANGED( ID_NOTEBOOK, UsbdmDialogue::OnSelChanged )
END_EVENT_TABLE()

//========================================================================================================================
// UsbdmDialogue methods

typedef USBDM_ErrorCode (*openTarget)(void);

#if defined(GDI) && defined(LEGACY)
//! Display the USBDM dialogue etc. Intended for use with Legacy GDI
//! The BDM is ready for use upon exit.
//!
//! @param deviceName      Name of device
//! @param projectName     Name of project
//! @param forceDisplay    Force display of dialogue
//! @param openTarget      Function to open target
//!
//! @return error code \n
//!   - BDM_RC_OK => ok
//!   - else => various USBDM error codes. An error pop-up has already been displayed.
//!
USBDM_ErrorCode UsbdmDialogue::execute(string const     &deviceName,
                                       string const     &projectName,
                                       bool              forceDisplay,
                                       USBDM_ErrorCode (*openTarget)(void)) {
   USBDM_ErrorCode rc = BDM_RC_OK;
   int getYesNo = wxNO;

   if (errorSet != BDM_RC_OK) {
      return errorSet;
   }
   loadSettings(appSettings);

   forceDisplay =  forceDisplay || !disableDialogueDisplay;
   do {
      if (forceDisplay) {
         ShowModal();
         if (!saveSettings(appSettings)) {
            wxMessageBox(_("Unable to save USBDM settings. \n"
                           "Please set \'eclipseHome\' attribute\n"
                           "in Debug Configurations"),
                         _("USBDM Failure"),
                         wxOK|wxICON_WARNING,
                         this
                         );
         }
      }
      rc = shared->initBdm();
      if (openTarget != NULL) {
         rc = openTarget();
      }
      else {
#if TARGET == MC56F80xx
         if (rc == BDM_RC_OK) {
            rc = DSC_Connect();
         }
         if (rc != BDM_RC_OK) {
            DSC_TargetReset((TargetMode_t)(RESET_DEFAULT|RESET_SPECIAL));
            rc = DSC_Connect();
         }
#else
         if (rc == BDM_RC_OK) {
            rc = USBDM_Connect();
         }
#endif
      }
      if (rc != BDM_RC_OK) {
         USBDM_Close();
         Logging::print("UsbdmDialogue::execute() - failed\n");
#if wxVERSION_NUMBER < 2900
         wxString prompt;
         if (forceDisplay)
            prompt = _("\n\n Return to connection dialogue?");
         else
            prompt = _("\n\n Open connection dialogue?");
         wxMessageDialog msgBox(this,
                                _("Failed to connect to target.\n\n"
                                  "Reason: ") +
                                wxString(USBDM_GetErrorString(rc), wxConvUTF8) +
                                prompt,
                                _("USBDM Connection Error"),
                                wxYES_NO|wxICON_ERROR|wxSTAY_ON_TOP
                                );
         getYesNo = msgBox.ShowModal();
         if (getYesNo == wxID_NO) {
            getYesNo = wxID_CANCEL;
         }
         forceDisplay = true;
#else
         wxString prompt;
         wxMessageDialog msgBox(this,
                                _("Failed to connect to target.\n\n"
                                  "Reason: ") +
                                wxString(USBDM_GetErrorString(rc), wxConvUTF8),
                                _("USBDM Connection Error"),
                                wxYES_NO|wxCANCEL|wxICON_ERROR|wxSTAY_ON_TOP
                                );
                                    // ID_YES         ID_NO             ID_CANCEL
         msgBox.SetYesNoCancelLabels(_("Retry"), _("Change Settings"), _("Cancel"));
         getYesNo = msgBox.ShowModal();
         forceDisplay = (getYesNo == wxID_NO); // Retry with changed settings
#endif
      }
   } while ((rc != BDM_RC_OK) && (getYesNo != wxID_CANCEL));
   return rc;
}

#elif defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
//! This displays the Dialogue which represents the entire application
//! for the stand-alone flash programmers.  Accepts starting parameters.
//!
//! @param settingsFilename Base name of settings file to use
//! @param hexFilename      Hex file to load
//!
//! @return BDM_RC_OK - no useful return vale
//!
USBDM_ErrorCode UsbdmDialogue::execute(wxString const &hexFilename) {
   Logging log("UsbdmDialogue::execute");

   loadSettings(appSettings);

#if defined (FLASH_PROGRAMMER)
   if (!hexFilename.IsEmpty() && (flashParametersPanel->loadHexFile(hexFilename, true) != PROGRAMMING_RC_OK)) {
      Logging::print("UsbdmDialogue::execute() - Failed to load Hex file\n");
   }
#endif
   USBDM_ErrorCode rc = (USBDM_ErrorCode)ShowModal();
   if (rc == BDM_RC_OK) {
      log.print("Saving settings\n");
      // Save settings
      if (!saveSettings(appSettings)) {
         wxMessageBox(_("Unable to save USBDM settings."),
                      _("USBDM Failure"),
                      wxOK|wxICON_WARNING,
                      this
         );
      }
   }
   else {
      // Restore setting to original values
      log.print("Restoring settings\n");
      loadSettings(appSettings);
   }
   return rc;
}
#endif

//! Load settings from a settings object
//!
//! @param appSettings - Object containing settings
//!
bool UsbdmDialogue::loadSettings(const AppSettings &appSettings) {
   Logging log("UsbdmDialogue::loadSettings");

   shared->loadSettings(appSettings);

#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
   flashParametersPanel->loadSettings(appSettings);
#endif

   interfacePanel->loadSettings(appSettings);
   advancedPanel->loadSettings(appSettings);

#ifdef GDI
   disableDialogueDisplay = appSettings.getValue(settingsKey+".dontDisplayDialogue", false);
#endif
   return true;
}

#if 0
//! Load setting file
//!
//! @param fileName - Name of file to use (without path)
//!
bool UsbdmDialogue::loadSettingsFile(const string &fileName) {

   Logging::print("UsbdmDialogue::loadSettingsFile(%s)\n", (const char *)fileName.c_str());

   AppSettings appSettings;
   string settingsFilename(AppSettings::getSettingsFilename(fileName, shared->bdmOptions.targetType));

   if (!appSettings.loadFromFile(settingsFilename)) {
      Logging::print("UsbdmDialogue::loadSettingsFile() - no settings file found\n");
      return false;
   }
   appSettings.printToLog();

   // Load the saved settings
   return loadSettings(appSettings);
}

//! Load setting file from %APPDATA%
//!
//! @param fileName      - Name of file to use (without path)
//!
bool UsbdmDialogue::loadSettingsFileFromAppDir(string const &fileName) {
   Logging log("UsbdmDialogue::loadSettingsFileFromAppDir");

   AppSettings appSettings;
   string settingsFilename(AppSettings::getSettingsFilename(fileName, shared->bdmOptions.targetType));

   Logging::print("filename = \'%s\'\n", settingsFilename.c_str());

   if (!appSettings.loadFromAppDirFile(settingsFilename)) {
      Logging::print("No settings file found\n");
//      return false;
   }
   appSettings.printToLog();

   // Load the saved settings
   return loadSettings(appSettings);
}
#endif

//! Save setting file
//!
//! @param appSettings
//!
bool UsbdmDialogue::saveSettings(AppSettings &appSettings) {
   Logging log("UsbdmDialogue::saveSettings");

   TransferDataFromWindow();
#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
   flashParametersPanel->saveSettings(appSettings);
#endif
   interfacePanel->saveSettings(appSettings);
   advancedPanel->saveSettings(appSettings);
#ifdef GDI
   appSettings.addValue(settingsKey+".dontDisplayDialogue", disableDialogueDisplay);
#endif

   shared->saveSettings(appSettings);

   appSettings.printToLog();
   return true;
}

#if 0
//! Save setting file
//!
//! @param fileName      - Name of file to use (without path)
//!
bool UsbdmDialogue::saveSettingsFile(string const &fileName) {
   Logging log("UsbdmDialogue::saveSettingsFile");

   AppSettings appSettings;
   string settingsFilename(AppSettings::getSettingsFilename(fileName, shared->bdmOptions.targetType));

   Logging::print("filename = \'%s\'\n", settingsFilename.c_str());

   saveSettings(appSettings);

   if (!appSettings.writeToFile(settingsFilename, USBDM_VERSION_STRING)) {
      return false;
   }
   return true;
}

//! Save setting file
//!
//! @param fileName      - Name of file to use (without path)
//!
bool UsbdmDialogue::saveSettingsFileToAppDir(string const &fileName) {
   Logging log("UsbdmDialogue::saveSettingsFileToAppDir");

   Logging::print("filename = \'%s\'\n", fileName.c_str());

   AppSettings appSettings;
   string settingsFilename(AppSettings::getSettingsFilename(fileName, shared->bdmOptions.targetType));

   saveSettings(appSettings);

   if (!appSettings.writeToAppDirFile(settingsFilename, USBDM_VERSION_STRING)) {
      return false;
   }
   return true;
}
#endif

//===================================================================
//===================================================================
//===================================================================

//! UsbdmDialogue constructor
//!
//! @param targetType       : Target type - controls which dialogue & options are displayed
//! @param caption          : Base caption to display on dialogue
//! @param settingsFilename : filename of file to load/save dialogue settings
//!
//! @note: It is necessary to call Create()
//!
UsbdmDialogue::UsbdmDialogue(SharedPtr shared, AppSettings &appSettings, const wxString &caption):
                             shared(shared),
                             appSettings(appSettings),
                             caption(caption),
                             bdmCapabilities(BDM_CAP_NONE),
                             errorSet(BDM_RC_OK) {
   Logging::setLoggingLevel(100);
   Logging log("AdvancedPanel::AdvancedPanel");
   Init();
   Create(NULL);
}

//! Set the dialogue internal state to the default (not including pages)
//!
bool UsbdmDialogue::Init() {
   Logging log("UsbdmDialogue::Init");

   disableDialogueDisplay = false;
   return (shared->loadDeviceDatabase() == BDM_RC_OK);
}

//! UsbdmDialogue creator
//!
//! @param parent     : Parent window
//! @param style      : Window style
//!
bool UsbdmDialogue::Create( wxWindow* parent, long style) {
   Logging log("UsbdmDialogue::Create");

   if (errorSet) {
      return false;
   }
   wxString completeCaption(caption);

   switch(shared->bdmOptions.targetType) {
      case T_HC12 :
         completeCaption  += _(" - HCS12");
         break;
      case T_HCS08 :
         completeCaption  += _(" - HCS08");
         break;
      case T_RS08 :
         completeCaption  += _(" - RS08");
         break;
      case T_CFV1 :
         completeCaption  += _(" - Coldfire V1 ");
         break;
      case T_CFVx :
         completeCaption  += _(" - Coldfire V2, 3 & 4 ");
         break;
      case T_JTAG :
         completeCaption  += _(" - JTAG");
         break;
      case T_MC56F80xx :
         completeCaption  += _(" - MC56F80xx ");
         break;
      case T_ARM :
         completeCaption  += _(" - ARM ");
         break;
      default :
         completeCaption += _(" - OPPS");
         errorSet = BDM_RC_ILLEGAL_PARAMS;
         return false;
         break;
   }

   wxDialog::Create( parent, ID_FLASH_PROGRAMMER_DIALOGUE, completeCaption, wxDefaultPosition, wxSize(-1,-1), style);

   CreateControls();

   if (GetSizer()) {
      GetSizer()->SetSizeHints(this);
   }
   Centre();

   return true;
}

//! UsbdmDialogue destructor
//!
UsbdmDialogue::~UsbdmDialogue() {
}

//! Control creation
//!
void UsbdmDialogue::CreateControls() {
   Logging log("UsbdmDialogue::CreateControls");

   UsbdmDialogue* frame = this;

   wxBoxSizer* frameBoxSizerV = new wxBoxSizer(wxVERTICAL);
   frame->SetSizer(frameBoxSizerV);

   noteBook = new wxNotebook( frame, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );
   frameBoxSizerV->Add(noteBook, 1, wxGROW, 5);

   interfacePanel = new InterfacePanel(noteBook, shared);
   noteBook->AddPage(interfacePanel, _("Interface"));

#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
   flashParametersPanel = new TargetPanel(noteBook, shared, bdmCapabilities);
   noteBook->AddPage(flashParametersPanel, _("Target"));
#endif

   advancedPanel = new AdvancedPanel(noteBook, shared, bdmCapabilities);
   noteBook->AddPage(advancedPanel, _("Advanced"));

//------------------------------------------------
   wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
   frameBoxSizerV->Add(buttonSizer, 0, wxGROW|wxALL, 5);

#if !(defined(FLASH_PROGRAMMER) || defined(GDB_SERVER))
   wxButton* defaultButton = new wxButton( frame, wxID_DEFAULT, _("&Default"), wxDefaultPosition, wxDefaultSize, 0 );
   buttonSizer->Add(defaultButton, 0, wxGROW|wxALL, 5);
#endif

   buttonSizer->Add(5, 5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

#if defined(FLASH_PROGRAMMER)
   wxButton* okButton = new wxButton( frame, wxID_OK, _("C&lose"), wxDefaultPosition, wxDefaultSize, 0 );
#elif defined(GDB_SERVER)
   wxButton* okButton = new wxButton( frame, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
#else
   wxButton* okButton = new wxButton( frame, wxID_OK, _("&OK"), wxDefaultPosition, wxDefaultSize, 0 );
#endif
   buttonSizer->Add(okButton, 0, wxGROW|wxALL, 5);

#if defined(GDB_SERVER)
   wxButton* cancelButton = new wxButton( frame, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
   buttonSizer->Add(cancelButton, 0, wxGROW|wxALL, 5);
#endif

   okButton->SetDefault();

#if !(defined(FLASH_PROGRAMMER) || defined(GDB_SERVER))
   dontShowAgainControl = new wxCheckBox( frame, ID_DONT_SHOW_AGAIN_CHECKBOX, _("Don't show this dialogue in future"), wxDefaultPosition, wxDefaultSize, 0 );
   dontShowAgainControl->SetValue(false);
   frameBoxSizerV->Add(dontShowAgainControl, 0, wxALIGN_LEFT|wxALL, 5);
#endif
}

//===================================================================
//! Copy internal state to Dialogue controls
//!
bool UsbdmDialogue::TransferDataToWindow() {
   Logging log("UsbdmDialogue::TransferDataToWindow");

#if !(defined(FLASH_PROGRAMMER) || defined(GDB_SERVER))
   dontShowAgainControl->Set3StateValue(disableDialogueDisplay?wxCHK_CHECKED:wxCHK_UNCHECKED);
#endif

   bool ok = wxDialog::TransferDataToWindow();
#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
   ok = flashParametersPanel->TransferDataToWindow();
#endif
   ok = ok && interfacePanel->TransferDataToWindow();
   ok = ok && advancedPanel->TransferDataToWindow();
   return ok;
}

//===================================================================
//! Update internal state on all pages
//!
//! @return true  => success
//!         false => dialogue page has inconsistent data
//!
bool UsbdmDialogue::updateState() {
   bool ok = true;
#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
   ok = ok && flashParametersPanel->updateState();
#endif
   ok = ok && interfacePanel->updateState();
   ok = ok && advancedPanel->updateState();
   return ok;
}

//===================================================================
//! Set dialogue state to default values
//!
bool UsbdmDialogue::setDialogueValuesToDefault() {
   Logging log("UsbdmDialogue::setDialogueValuesToDefault");

   Init();
   TransferDataToWindow();

   return true;
}

//===================================================================
//! Copy internal state from Dialogue controls
//!
bool UsbdmDialogue::TransferDataFromWindow() {
   Logging log("UsbdmDialogue::TransferDataFromWindow");

   bool ok = wxDialog::TransferDataFromWindow();

#if !(defined(FLASH_PROGRAMMER) || defined(GDB_SERVER))
   disableDialogueDisplay = dontShowAgainControl->IsChecked();
#endif

#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
   ok = ok && flashParametersPanel->TransferDataFromWindow();
#endif
   ok = ok && interfacePanel->TransferDataFromWindow();
   ok = ok && advancedPanel->TransferDataFromWindow();
   return ok;
}

//! Should we show tooltips?
//!
bool UsbdmDialogue::ShowToolTips() {
    return true;
}

//! Get bitmap resources
//!
//! @param name
//!
wxBitmap UsbdmDialogue::GetBitmapResource( const wxString& name ) {
    // Bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
}

//! Get icon resources
//!
//! @param name
//!
wxIcon UsbdmDialogue::GetIconResource( const wxString& name ) {
    // Icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
}

//! wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_RECONNECT_CHECKBOX
//!
//! @param event The event to handle
//!
void UsbdmDialogue::OnDontShowAgainControlClick( wxCommandEvent& event ) {
   disableDialogueDisplay = event.IsChecked();
}

//! wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_DEFAULT
//!
//! @param event The event to handle
//!
void UsbdmDialogue::OnDefaultClick( wxCommandEvent& event ) {
   Logging::print("UsbdmDialogue::OnDefaultClick()\n");
   setDialogueValuesToDefault();
}

//! wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
//!
//! @param event The event to handle
//!
void UsbdmDialogue::OnOkClick( wxCommandEvent& event ) {
   if (TransferDataFromWindow()) {
      EndModal(BDM_RC_OK);
   }
}

//! wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_OK
//!
//! @param event The event to handle
//!
void UsbdmDialogue::OnCancelClick( wxCommandEvent& event ) {
   if (TransferDataFromWindow()) {
      EndModal(BDM_RC_FAIL);
   }
}

#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
//! Returns the Device options from the internal state
//!
//! @param deviceData - where to return options
//!
void UsbdmDialogue::getDeviceData( DeviceData &deviceData ) {
   // Make sure each panel has updated internal state
   advancedPanel->TransferDataFromWindow();
   flashParametersPanel->TransferDataFromWindow();

   deviceData.shallowCopy(*this->shared->currentDevice);
};
#endif

//! Returns the BDM options from the internal state
//!
//! @param bdmOptions - where to return options
//!
void UsbdmDialogue::getBdmOptions( USBDM_ExtendedOptions_t &bdmOptions ) {
   // Make sure each panel has updated internal state
   advancedPanel->TransferDataFromWindow();

#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
   flashParametersPanel->TransferDataFromWindow();
#endif

   bdmOptions = this->shared->bdmOptions;
};

//! wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING event handler for ID_NOTEBOOK
//!
//! @param event The event to handle.
//!
void UsbdmDialogue::OnSelChanging( wxNotebookEvent& event ) {
   LOGGING;
   Logging::print("(%d => %d)\n", event.GetOldSelection(), event.GetSelection());

   int leavingPage = event.GetOldSelection();
   if (leavingPage < 0) {
      return;
   }
   // Validate page before leaving (& update shared state)
   wxPanel *panel = static_cast<wxPanel *>(noteBook->GetPage(leavingPage));
   if (!panel->TransferDataFromWindow()) {
      Logging::print("Vetoing page change\n");
      event.Veto();
      return;
   }
}

//! wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED event handler for ID_NOTEBOOK
//!
//! @param event The event to handle.
//!
void UsbdmDialogue::OnSelChanged( wxNotebookEvent& event ) {
   LOGGING;
   Logging::print("(%d => %d)\n", event.GetOldSelection(), event.GetSelection());
#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
   int enteringPage = event.GetSelection();
   if (enteringPage < 0) {
      return;
   }
   // Make sure page is updated with shared state
   wxPanel *panel = static_cast<wxPanel *>(noteBook->GetPage(enteringPage));
   panel->TransferDataToWindow();
#endif
}

