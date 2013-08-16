/*! \file
    \brief Implements USBDM Flash Programmer dialogue

    InterfacePanel.cpp

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
   -==================================================================================
   | 30 Mar 2012 | Updated to using USBDM_ExtendedOptions                  - pgo V4.9
   | 30 Jan 2012 | Added firmware version compatibility checks             - pgo V4.9
   | 26 Oct 2010 | Added PST capability checks on dialogue                 - pgo
   |  1 Jul 2010 | wxWidgets version created                               - pgo
   +==================================================================================
   \endverbatim
*/

// For compilers that support pre-compilation, includes <wx/wx.h>.
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/imaglist.h>
#include <wx/gbsizer.h>

#include "Common.h"
#include "USBDMDialogue.h"
#include "InterfacePanel.h"
#include "USBDM_API.h"
#include "USBDM_AUX.h"
#include "ApplicationFiles.h"
#include "Log.h"

//===================================================================
//! Obtains the version of the BDM library as a string
//!
//! @return Version string (reference to static buffer)
//!
static const wxString &bdmGetDllVersion(void) {
   static wxString versionString;

   versionString = wxString(USBDM_DLLVersionString(), wxConvUTF8);

   versionString.Prepend(_("DLL Ver "));

   return versionString; // Software version of USBDM DLL
}

//! Structure to describe a configuration setting
//!
typedef struct {
   const wxString name;   //!< Name of setting
   int * const value;     //!< Location to modify
} ConfigLine;

//! Maps between a drop-down box 'name' and its value
typedef struct {
   int   value;           //!< Value to use
   const wxString name;   //!< Name to display in DD box
} DropDownType;

//! Mappings for Frequency drop-down box
static const DropDownType CFVx_Speeds[] = {
   {  250, _("250kHz") },
   {  500, _("500kHz") },
   {  750, _("750kHz") },
   { 1000, _("1MHz")   },
   { 1500, _("1.5MHz") },
   { 2000, _("2MHz")   },
   { 3000, _("3MHz")   },
   { 4000, _("4MHz")   },
   { 6000, _("6MHz")   },
   {12000, _("12MHz")  }, // Not supported on JTAG etc
   {  0,   wxEmptyString },
};

//===================================================================
//! Maps a value to a drop-down box index
//!
//! @param information  Array of data describing the DD box
//! @param value        Value to locate
//!
//! @return Dropdown box index, -1 if value not present
//!
static int searchDropDown(const DropDownType information[], int value) {
int sub;

   // Populate the list
   for (sub = 0; information[sub].value != 0; sub++)
      if (information[sub].value == value)
         return sub;
   return -1;
}

#define settingsKey "InterfacePanel"

//! Load settings
//!
//! @param settings      - Object to load settings from
//!
//! @note - Settings may be filtered by by target type or BDM capabilities.
//!
void InterfacePanel::loadSettings(const AppSettings &settings) {
   Logging log("InterfacePanel::loadSettings");

//   bdmIdentification             =            wxString(settings.getValue(settingsKey+".bdmSelection",             "").c_str(), wxConvUTF8);
}

//! Save settings
//!
//! @param settings      - Object to save settings to
//!
//! @note - Settings may be filtered by by target type or BDM capabilities.
//!
void InterfacePanel::saveSettings(AppSettings &settings) {
   Logging::print("InterfacePanel::saveSettings()\n");

//   settings.addValue(settingsKey+".bdmSelection",             bdmIdentification.ToAscii());
}

InterfacePanel::InterfacePanel( wxWindow* parent, SharedPtr shared) :
#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
            currentDevice(shared->getCurrentDevice()),
#endif
            bdmOptions(shared->getBdmOptions()),
            shared(shared) {
   Logging Log("InterfacePanel::InterfacePanel");
   Init();
   Create(parent);
}

InterfacePanel::InterfacePanel(Shared *shared) :
#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
            currentDevice(shared->getCurrentDevice()),
#endif
            bdmOptions(shared->getBdmOptions()),
            shared(shared) {
   Logging Log("InterfacePanel::InterfacePanel");
   Init();
}

//===================================================================
//! Set the panel internal state to the default
//!
void InterfacePanel::Init() {
   Logging Log("InterfacePanel::Init");

   bdmDeviceNum          = -1;
   bdmIdentification     = wxEmptyString;
   
   // Set options to default
   // TransferDataToWindow() will validate these for the particular dialog/BDM being used.
   USBDM_ExtendedOptions_t tempOptions;
   tempOptions.size       = sizeof(USBDM_ExtendedOptions_t);
   tempOptions.targetType = bdmOptions.targetType;
   USBDM_GetDefaultExtendedOptions(&tempOptions);

   bdmOptions.size               = sizeof(USBDM_ExtendedOptions_t);
   bdmOptions.targetVdd          = tempOptions.targetVdd;
   bdmOptions.cycleVddOnReset    = tempOptions.cycleVddOnReset;
   bdmOptions.cycleVddOnConnect  = tempOptions.cycleVddOnConnect;
   bdmOptions.leaveTargetPowered = tempOptions.leaveTargetPowered;
   bdmOptions.autoReconnect      = tempOptions.autoReconnect;
   bdmOptions.useResetSignal     = tempOptions.useResetSignal;
   bdmOptions.usePSTSignals      = tempOptions.usePSTSignals;
   bdmOptions.guessSpeed         = tempOptions.guessSpeed;
   bdmOptions.interfaceFrequency = tempOptions.interfaceFrequency;

}

//! InterfacePanel creator
//!
//! @param parent     : Parent window
//!
//! @return error code
//! - BDM_RC_OK => success
//! - else => failed
USBDM_ErrorCode InterfacePanel::Create(wxWindow* parent) {
   Logging Log("InterfacePanel::Create");

   if (!wxPanel::Create(parent, ID_COMMUNICATION, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL)) {
      return BDM_RC_FAIL;
   }
   CreateControls();
   if (GetSizer()) {
       GetSizer()->SetSizeHints(this);
   }
   return BDM_RC_OK;
}

//! Control creation for USBDM Communication settings
//!
//! @return error code
//! - BDM_RC_OK => success
//! - else => failed
USBDM_ErrorCode InterfacePanel::CreateControls(void) {
   Logging Log("InterfacePanel::CreateControls");

   // Determine dialogue features
   targetProperties = HAS_NONE;
   switch(bdmOptions.targetType) {
      case T_ARM :
      case T_ARM_JTAG :
      case T_ARM_SWD :
         targetProperties = HAS_SELECT_SPEED;
         break;
      case T_HC12 :
         targetProperties = (TargetOptions)(HAS_CLK_SW|HAS_GUESS_SPEED);
         break;
      case T_HCS08 :
         targetProperties = (TargetOptions)(HAS_CLK_SW|HAS_USE_RESET|HAS_MASK_INTERRUPTS);
         break;
      case T_RS08 :
         targetProperties = (TargetOptions)(HAS_CLK_SW|HAS_USE_RESET);
         break;
      case T_CFV1 :
         targetProperties = (TargetOptions)(HAS_CLK_SW|HAS_USE_RESET);
         break;
      case T_CFVx :
         targetProperties = HAS_SELECT_SPEED;
         break;
      case T_JTAG :
         targetProperties = HAS_SELECT_SPEED;
         break;
      case T_MC56F80xx :
         targetProperties = HAS_SELECT_SPEED;
         break;
      default :
         targetProperties = HAS_NONE;
         break;
   }
#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
   targetProperties = (TargetOptions)(targetProperties&~HAS_CLK_SW); // Not allowed on Programmer
#endif
   wxPanel* panel = this;
   wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
   panel->SetSizer(panelSizer);

   const int borderWidth = 3;

   wxStaticBox      *staticTextBox;
   wxStaticBoxSizer *staticBoxSizer;
   wxBoxSizer       *itemBoxSizer;

   //-----------------------------------------------
   staticTextBox = new wxStaticBox(panel, wxID_ANY, _("Select BDM"));
   staticBoxSizer = new wxStaticBoxSizer(staticTextBox, wxVERTICAL);
   panelSizer->Add(staticBoxSizer, 0, wxGROW|wxALL, borderWidth);

   itemBoxSizer = new wxBoxSizer(wxHORIZONTAL);
   staticBoxSizer->Add(itemBoxSizer, 0, wxGROW|wxALL, borderWidth);

   bdmSelectChoiceControl = new wxChoice( panel, ID_BDM_SELECT_CHOICE, wxDefaultPosition, wxDefaultSize);
   itemBoxSizer->Add(bdmSelectChoiceControl, 1, wxALIGN_CENTER_HORIZONTAL|wxALL, borderWidth);
   populateBDMChoices();

   bdmRefreshButtonControl = new wxButton( panel, ID_REFRESH_BDM_BUTTON, _("&Detect"), wxDefaultPosition, wxDefaultSize, 0 );
   bdmRefreshButtonControl->SetToolTip(_("Refresh list of connected BDMs"));
   itemBoxSizer->Add(bdmRefreshButtonControl, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, borderWidth);

   bdmDescriptionStaticControl = new wxStaticText( panel, ID_BDM_DESCRIPTION_STRING, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
   staticBoxSizer->Add(bdmDescriptionStaticControl, 0, wxGROW|wxALL, borderWidth);

   //-----------------------------------------------
   staticTextBox = new wxStaticBox(panel, wxID_ANY, _("Target Vdd Control"));
   staticBoxSizer = new wxStaticBoxSizer(staticTextBox, wxVERTICAL);
   panelSizer->Add(staticBoxSizer, 0, wxGROW|wxALL, borderWidth);

   itemBoxSizer = new wxBoxSizer(wxVERTICAL);
   staticBoxSizer->Add(itemBoxSizer, 0, wxGROW|wxALL, borderWidth);

   wxArrayString targetVddControlStrings;
   targetVddControlStrings.Add(_("&Off"));
   targetVddControlStrings.Add(_("&3.3V"));
   targetVddControlStrings.Add(_("&5V"));
   targetVddControl = new wxRadioBox( panel, ID_VDD_SELECT_BOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, targetVddControlStrings, 1, wxRA_SPECIFY_ROWS );
   targetVddControl->SetSelection(0);
   itemBoxSizer->Add(targetVddControl, 0, wxGROW|wxALL, borderWidth);

   cycleVddOnResetControl = new wxCheckBox( panel, ID_CYCLE_VDD_ON_RESET_CHECKBOX, _("&Cycle target Vdd on reset"), wxDefaultPosition, wxDefaultSize, 0 );
   cycleVddOnResetControl->SetValue(false);
   itemBoxSizer->Add(cycleVddOnResetControl, 0, wxLEFT|wxRIGHT|wxTOP, 10);

   cycleVddOnConnectionControl = new wxCheckBox( panel, ID_CYCLE_TARGET_VDD_ON_CONNECTION_CHECKBOX, _("Cycle &target Vdd on connection problems"), wxDefaultPosition, wxDefaultSize, 0 );
   cycleVddOnConnectionControl->SetValue(false);
   itemBoxSizer->Add(cycleVddOnConnectionControl, 0, wxLEFT|wxRIGHT|wxTOP, 10);

   leaveTargetPoweredControl = new wxCheckBox( panel, ID_LEAVE_TARGET_ON_CHECKBOX, _("&Leave target powered on exit"), wxDefaultPosition, wxDefaultSize, 0 );
   leaveTargetPoweredControl->SetValue(false);
   itemBoxSizer->Add(leaveTargetPoweredControl, 0, wxALL, 10);

//   promptToManualCycleVddControl = new wxCheckBox( panel, ID_MANUALLY_CYCLE_VDD_CHECKBOX, _("&Prompt to manually cycle target Vdd"), wxDefaultPosition, wxDefaultSize, 0 );
//   promptToManualCycleVddControl->SetValue(false);
//   itemBoxSizer->Add(promptToManualCycleVddControl, 0, wxALL, borderWidth);

   //-----------------------------------------------
   staticTextBox = new wxStaticBox(panel, wxID_ANY, _("Connection control"));
   staticBoxSizer = new wxStaticBoxSizer(staticTextBox, wxVERTICAL);
   panelSizer->Add(staticBoxSizer, 0, wxGROW|wxALL, borderWidth);
   automaticallyReconnectControl = new wxCheckBox( panel, ID_RECONNECT_CHECKBOX, _("&Automatically re-connect"), wxDefaultPosition, wxDefaultSize, 0 );
   automaticallyReconnectControl->SetToolTip(_("Re-synchronise with target before each operation."));
   automaticallyReconnectControl->SetValue(false);
   staticBoxSizer->Add(automaticallyReconnectControl, 0, wxALL, borderWidth);

   if (targetProperties & HAS_CLK_SW) {
      wxArrayString bdmClockSelectControlStrings;
      bdmClockSelectControlStrings.Add(_("&Default"));
      bdmClockSelectControlStrings.Add(_("&Bus Clock/2"));
      bdmClockSelectControlStrings.Add(_("&Alt"));
      bdmClockSelectControl = new wxRadioBox( panel, ID_BDM_CLOCK_SELECT_RADIOBOX, _("BDM Clock Select"), wxDefaultPosition, wxDefaultSize, bdmClockSelectControlStrings, 1, wxRA_SPECIFY_ROWS );
      bdmClockSelectControl->SetToolTip(_("Drive RESET signal when resetting the target."));
      bdmClockSelectControl->SetSelection(0);
      staticBoxSizer->Add(bdmClockSelectControl, 0, wxGROW|wxALL, borderWidth);
   }
   if (targetProperties & HAS_GUESS_SPEED) {
      guessTargetSpeedControl = new wxCheckBox( panel, ID_GUESS_SPEED_CHECKBOX, _("&Guess speed if no sync"), wxDefaultPosition, wxDefaultSize, 0 );
      guessTargetSpeedControl->SetValue(false);
      staticBoxSizer->Add(guessTargetSpeedControl, 0, wxGROW|wxALL, borderWidth);
   }
   if (targetProperties & HAS_USE_RESET) {
      useResetSignalControl = new wxCheckBox( panel, ID_USE_RESET_CHECKBOX, _("Use &RESET signal"), wxDefaultPosition, wxDefaultSize, 0 );
      useResetSignalControl->SetValue(false);
      staticBoxSizer->Add(useResetSignalControl, 0, wxLEFT|wxALL, borderWidth);
   }
   if (bdmOptions.targetType == T_CFVx) {
      usePstSignalControl = new wxCheckBox( panel, ID_USE_PST_SIGNAL_CHECKBOX, _("Monitor &PST signals"), wxDefaultPosition, wxDefaultSize, 0 );
      usePstSignalControl->SetValue(false);
      staticBoxSizer->Add(usePstSignalControl, 0, wxLEFT|wxALL, borderWidth);
   }
   if (targetProperties & HAS_SELECT_SPEED) {
      wxBoxSizer* itemBoxSizer = new wxBoxSizer(wxHORIZONTAL);
      staticBoxSizer->Add(itemBoxSizer, 0, wxGROW|wxRIGHT|wxTOP|wxBOTTOM, borderWidth);
      itemBoxSizer->Add(5, 5, 0, wxALIGN_CENTER_VERTICAL|wxALL, borderWidth);

      wxStaticText* itemStaticText22 = new wxStaticText( panel, wxID_STATIC, _("Connection &Speed"), wxDefaultPosition, wxDefaultSize, 0 );
      itemBoxSizer->Add(itemStaticText22, 0, wxALIGN_CENTER_VERTICAL|wxALL, borderWidth);

      int maxSpeed;
      switch(bdmOptions.targetType) {
      case T_ARM_JTAG : maxSpeed =  6000; break;
      case T_ARM_SWD  : maxSpeed = 12000; break;
      case T_CFVx     : maxSpeed = 12000; break;
      default         : maxSpeed = 12000; break;
      }
      wxArrayString connectionSpeedControlStrings;
      for (int sub=0; CFVx_Speeds[sub].value != 0; sub++) {
         if (CFVx_Speeds[sub].value > maxSpeed) {
            continue;
         }
         connectionSpeedControlStrings.Add(CFVx_Speeds[sub].name);
      }
      connectionSpeedControl = new wxChoice( panel, ID_SPEED_SELECT_CHOICE, wxDefaultPosition, wxSize(100, -1), connectionSpeedControlStrings, 0 );
      itemBoxSizer->Add(connectionSpeedControl, 0, wxALIGN_CENTER_VERTICAL|wxALL, borderWidth);

      if (bdmOptions.targetType == T_CFVx) {
         wxStaticText* staticText = new wxStaticText( panel, ID_SPEED_REMINDER_STATIC, _("Speed < Target Clock Frequency/5"), wxDefaultPosition, wxDefaultSize, 0 );
         staticBoxSizer->Add(staticText, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, borderWidth);
      }
   }
#ifdef GDI
   if (targetProperties & HAS_MASK_INTERRUPTS) {
      maskInterruptWhenSteppingControl = new wxCheckBox( panel, ID_MASK_INTERRUPTS_WHEN_STEPPING, _("Mask interrupts when stepping"), wxDefaultPosition, wxDefaultSize, 0 );
      maskInterruptWhenSteppingControl->SetValue(false);
      staticBoxSizer->Add(maskInterruptWhenSteppingControl, 0, wxLEFT|wxALL, borderWidth);
   }
#endif
   //------------------------------------------------
   wxBoxSizer* versionBoxSizerH = new wxBoxSizer(wxHORIZONTAL);
   panelSizer->Add(versionBoxSizerH, 0, wxGROW|wxALL, 0);

   firmwareStaticControl = new wxStaticText( panel, ID_BDM_VERSION_STRING, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
   versionBoxSizerH->Add(firmwareStaticControl, 0, wxGROW|wxALL, borderWidth);

   versionBoxSizerH->Add(5, 5, 1, wxALIGN_CENTER_VERTICAL|wxALL, borderWidth);

   wxStaticText *dllVersionstaticControl = new wxStaticText( panel, ID_DLL_VERSION_STRING, bdmGetDllVersion(), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT );
   versionBoxSizerH->Add(dllVersionstaticControl, 0, wxGROW|wxALL, borderWidth);

   return BDM_RC_OK;
}

//===================================================================
//! Set the internal dialogue values.
//!
//!
bool InterfacePanel::setDialogueValuesToDefault() {
   Logging Log("InterfacePanel::setDialogueValuesToDefault");

   Init();
   TransferDataToWindow();
   return true;
}

//===================================================================
//! Update the dialogue from internal state
//!
bool InterfacePanel::TransferDataToWindow() {
   Logging Log("InterfacePanel::TransferDataToWindow");

   bdmIdentification = wxString(shared->getBdmSerialNumber().c_str(), wxConvUTF8);

   Logging::print("BDM = \'%s\'\n", (const char *)bdmIdentification.ToAscii());
   HardwareCapabilities_t  bdmCapabilities;

   // Try to set choice to match BDM identification string
   if (!bdmSelectChoiceControl->SetStringSelection(bdmIdentification)) {
      // Failed - select first BDM
      bdmSelectChoiceControl->Select(0);
   }
   // Make BDM serial number string consistent with display
   int choice = bdmSelectChoiceControl->GetSelection();
   bdmDeviceNum = (int)bdmSelectChoiceControl->GetClientData(choice);
   bdmIdentification = bdmSelectChoiceControl->GetStringSelection();

   Logging::print("Device# = %d, BDM = \'%s\'\n", bdmDeviceNum, (const char *)bdmIdentification.ToAscii());

   if (bdmDeviceNum >= 0) {
      bdmCapabilities = connectedBDMs[bdmDeviceNum].getInfo().capabilities;
      wxString versionString;
      versionString.Printf(_("BDM Firmware Ver %d.%d.%d"),
                           (connectedBDMs[bdmDeviceNum].getInfo().BDMsoftwareVersion>>16)&0xFF,
                           (connectedBDMs[bdmDeviceNum].getInfo().BDMsoftwareVersion>>8)&0xFF,
                           connectedBDMs[bdmDeviceNum].getInfo().BDMsoftwareVersion&0xFF
                           );
      firmwareStaticControl->SetLabel(versionString);
      bdmDescriptionStaticControl->SetLabel(wxString::FromUTF8(connectedBDMs[bdmDeviceNum].getDescription().c_str()));
   }
   else {
      bdmCapabilities   = BDM_CAP_NONE;
      bdmIdentification = wxEmptyString;
      firmwareStaticControl->SetLabel(wxEmptyString);
      bdmDescriptionStaticControl->SetLabel(wxEmptyString);
   }
   if (!(bdmCapabilities & BDM_CAP_VDDCONTROL)) {
      // BDM doesn't have Vdd control - Vdd control options disabled
      targetVddControl->Enable(false);
      bdmOptions.targetVdd          = BDM_TARGET_VDD_OFF;
      bdmOptions.cycleVddOnReset    = false;
      bdmOptions.leaveTargetPowered = false;
      bdmOptions.cycleVddOnConnect  = false;
   }
   else {
      targetVddControl->Enable(true);
   }
   targetVddControl->Select(bdmOptions.targetVdd);

   bool checkBoxEnable = (bdmOptions.targetVdd != BDM_TARGET_VDD_OFF);
   cycleVddOnResetControl->Enable(checkBoxEnable);
   cycleVddOnConnectionControl->Enable(checkBoxEnable);
   leaveTargetPoweredControl->Enable(checkBoxEnable);
   cycleVddOnConnectionControl->Set3StateValue(bdmOptions.cycleVddOnConnect?wxCHK_CHECKED:wxCHK_UNCHECKED);
   cycleVddOnResetControl->Set3StateValue(bdmOptions.cycleVddOnReset?wxCHK_CHECKED:wxCHK_UNCHECKED);
   leaveTargetPoweredControl->Set3StateValue(bdmOptions.leaveTargetPowered?wxCHK_CHECKED:wxCHK_UNCHECKED);

   if (!(bdmCapabilities & (BDM_CAP_RST|BDM_CAP_HCS12))) {
      // BDM doesn't support reset control - Reset must be false
      // (Control not present in dialogue)
      bdmOptions.useResetSignal  = false;
   }
   else if (targetProperties & HAS_USE_RESET) {
      // Reset control present
      useResetSignalControl->Enable(true);
      useResetSignalControl->Set3StateValue(bdmOptions.useResetSignal?wxCHK_CHECKED:wxCHK_UNCHECKED);
   }
   else {// Reset control not present in dialogue as reset MUST be used
      bdmOptions.useResetSignal = true;
   }
   if (bdmOptions.targetType == T_CFVx) {
      if (bdmCapabilities & BDM_CAP_PST) {
         // BDM supports PST monitoring
         usePstSignalControl->Set3StateValue(bdmOptions.usePSTSignals?wxCHK_CHECKED:wxCHK_UNCHECKED);
         usePstSignalControl->Enable(true);
      }
      else {
         usePstSignalControl->Set3StateValue(wxCHK_UNCHECKED);
         usePstSignalControl->Enable(false);
         bdmOptions.usePSTSignals = false;
      }
   }
   if (targetProperties & HAS_GUESS_SPEED) {
      // Guess speed control is present
      guessTargetSpeedControl->Set3StateValue(bdmOptions.guessSpeed?wxCHK_CHECKED:wxCHK_UNCHECKED);
   }
   else {
      // Control not present and option unused
      bdmOptions.guessSpeed = false;
   }
   if (targetProperties & HAS_CLK_SW) {
      // Alternative clock available on this target & present in dialogue
      int index;
      switch (bdmOptions.bdmClockSource) {
		 default:
         case CS_DEFAULT :      index = 0; break;
         case CS_NORMAL_CLK :   index = 1; break;
         case CS_ALT_CLK :      index = 2; break;
      }
      bdmClockSelectControl->Select(index);
   }
   else {
      // No BDM clock options
      bdmOptions.bdmClockSource = CS_DEFAULT;
   }

   automaticallyReconnectControl->Set3StateValue(bdmOptions.autoReconnect?wxCHK_CHECKED:wxCHK_UNCHECKED);

   if (targetProperties & HAS_SELECT_SPEED) {
      int index = searchDropDown(CFVx_Speeds, bdmOptions.interfaceFrequency);
      if (index < 0)
         index = 0;
      connectionSpeedControl->SetSelection(index);
   }
#ifdef GDI
   if (targetProperties & HAS_MASK_INTERRUPTS) {
      maskInterruptWhenSteppingControl->Set3StateValue(bdmOptions.maskInterrupts?wxCHK_CHECKED:wxCHK_UNCHECKED);
   }
#endif
   return true;
}

bool InterfacePanel::TransferDataFromWindow() {
   Logging Log("InterfacePanel::TransferDataFromWindow");

   shared->setBdmSerialNumber((const char *)bdmIdentification.ToAscii(), true);
   return true;
}

bool InterfacePanel::updateState() {
   Logging Log("InterfacePanel::updateState");

   bool ok = true;
   ok = ok && TransferDataToWindow();
   ok = ok && TransferDataFromWindow();
   return ok;
}

/*
 * USBDMParametersDialogue type definition
 */
IMPLEMENT_CLASS( InterfacePanel, wxPanel )

/*
 * InterfacePanel event table definition
 */
BEGIN_EVENT_TABLE( InterfacePanel, wxPanel )
   EVT_CHOICE(   ID_BDM_SELECT_CHOICE,                         InterfacePanel::OnBDMSelectComboSelected )
   EVT_BUTTON(   ID_REFRESH_BDM_BUTTON,                        InterfacePanel::OnRefreshBDMClick )
   EVT_RADIOBOX( ID_VDD_SELECT_BOX,                            InterfacePanel::OnVddSelectBoxSelected )
   EVT_CHECKBOX( ID_CYCLE_VDD_ON_RESET_CHECKBOX,               InterfacePanel::OnCycleVddOnResetCheckboxClick )
   EVT_CHECKBOX( ID_CYCLE_TARGET_VDD_ON_CONNECTION_CHECKBOX,   InterfacePanel::OnCycleTargetVddOnConnectionCheckboxClick )
   EVT_CHECKBOX( ID_LEAVE_TARGET_ON_CHECKBOX,                  InterfacePanel::OnLeaveTargetOnCheckboxClick )
   EVT_CHECKBOX( ID_RECONNECT_CHECKBOX,                        InterfacePanel::OnReconnectCheckboxClick )
   EVT_CHECKBOX( ID_GUESS_SPEED_CHECKBOX,                      InterfacePanel::OnGuessSpeedCheckboxClick )
   EVT_CHECKBOX( ID_USE_RESET_CHECKBOX,                        InterfacePanel::OnUseResetCheckboxClick )
   EVT_CHECKBOX( ID_USE_PST_SIGNAL_CHECKBOX,                   InterfacePanel::OnUseUsePstSignalCheckboxClick )
   EVT_RADIOBOX( ID_BDM_CLOCK_SELECT_RADIOBOX,                 InterfacePanel::OnBdmClockSelectRadioboxSelected )
   EVT_CHOICE(   ID_SPEED_SELECT_CHOICE,                       InterfacePanel::OnSpeedSelectComboSelected )
   EVT_CHECKBOX( ID_MASK_INTERRUPTS_WHEN_STEPPING,             InterfacePanel::OnMaskInterruptsWhenSteppingCheckboxClick )
END_EVENT_TABLE()

//! wxEVT_COMMAND_RADIOBOX_SELECTED event handler for ID_VDD_SELECT_BOX
//!
//! @param event The event to handle
//!
void InterfacePanel::OnVddSelectBoxSelected( wxCommandEvent& event ) {

   switch(event.GetSelection()) {
      case 1  :    bdmOptions.targetVdd = BDM_TARGET_VDD_3V3; break;
      case 2  :    bdmOptions.targetVdd = BDM_TARGET_VDD_5V;  break;
      case 0  :
      default :    bdmOptions.targetVdd = BDM_TARGET_VDD_OFF; break;
   }
   bool checkBoxEnable = (bdmOptions.targetVdd != BDM_TARGET_VDD_OFF);
   cycleVddOnResetControl->Enable(checkBoxEnable);
   cycleVddOnConnectionControl->Enable(checkBoxEnable);
   leaveTargetPoweredControl->Enable(checkBoxEnable);
}

//! wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_CYCLE_VDD_ON_RESET_CHECKBOX
//!
//! @param event The event to handle
//!
void InterfacePanel::OnCycleVddOnResetCheckboxClick( wxCommandEvent& event ) {
   bdmOptions.cycleVddOnReset = event.IsChecked();
}

//! wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_CYCLE_TARGET_VDD_ON_CONNECTION_CHECKBOX
//!
//! @param event The event to handle
//!
void InterfacePanel::OnCycleTargetVddOnConnectionCheckboxClick( wxCommandEvent& event ) {
   bdmOptions.cycleVddOnConnect = event.IsChecked();
}

//! wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_LEAVE TARGET_ON_CHECKBOX
//!
void InterfacePanel::OnLeaveTargetOnCheckboxClick( wxCommandEvent& event ) {
   bdmOptions.leaveTargetPowered = event.IsChecked();
}

//! wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_RECONNECT_CHECKBOX
//!
//! @param event The event to handle
//!
void InterfacePanel::OnReconnectCheckboxClick( wxCommandEvent& event ) {
   bdmOptions.autoReconnect = event.IsChecked()?AUTOCONNECT_STATUS:AUTOCONNECT_NEVER;
}

//! wxEVT_COMMAND_RADIOBOX_SELECTED event handler for ID_BDM_CLOCK_SELECT_RADIOBOX
//!
//! @param event The event to handle
//!
void InterfacePanel::OnBdmClockSelectRadioboxSelected( wxCommandEvent& event ) {

   switch(event.GetSelection()) {
      case 1  :    bdmOptions.bdmClockSource = CS_NORMAL_CLK; break;
      case 2  :    bdmOptions.bdmClockSource = CS_ALT_CLK;  break;
      case 0  :
      default :    bdmOptions.bdmClockSource = CS_DEFAULT; break;
   }
}

//! wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_USE_RESET_CHECKBOX
//!
//! @param event The event to handle
//!
void InterfacePanel::OnUseResetCheckboxClick( wxCommandEvent& event ) {
   bdmOptions.useResetSignal = event.IsChecked();
}

//! wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_USE_PST_SIGNAL_CHECKBOX
//!
//! @param event The event to handle
//!
void InterfacePanel::OnUseUsePstSignalCheckboxClick( wxCommandEvent& event ) {
   bdmOptions.usePSTSignals = event.IsChecked();
}

//! wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_GUESS_SPEED_CHECKBOX
//!
//! @param event The event to handle
//!
void InterfacePanel::OnGuessSpeedCheckboxClick( wxCommandEvent& event ) {
   bdmOptions.guessSpeed = event.IsChecked();
}

//! wxEVT_COMMAND_COMBOBOX_SELECTED event handler for ID_SPEED_SELECT_COMBO
//!
//! @param event The event to handle
//!
void InterfacePanel::OnSpeedSelectComboSelected( wxCommandEvent& event ) {
   bdmOptions.interfaceFrequency = CFVx_Speeds[event.GetSelection()].value;
//   Logging::print("InterfacePanel::OnSpeedSelectComboSelected() sel = %d, f = %d\n", event.GetSelection(), bdmOptions.interfaceSpeed);
}

//! Update the list of connected BDMs
//!
void InterfacePanel::findBDMs(void) {
//   Logging::print("InterfacePanel::findBDMs()\n");

   bdmDeviceNum = 0;

   // Enumerate all attached BDMs
   USBDM_FindBDMs(bdmOptions.targetType, connectedBDMs);
   if (connectedBDMs.empty()) {
      bdmDeviceNum = -1;
      bdmIdentification = wxEmptyString;
      Logging::print("InterfacePanel::findBDMs() - no BDMs found\n");
   }
}

//! Populate the BDM Choice box
//!
void InterfacePanel::populateBDMChoices(void) {
//   Logging::print("InterfacePanel::populateBDMChoices()\n");

   findBDMs();
   unsigned deviceCount = connectedBDMs.size();
   bdmSelectChoiceControl->Clear();

//   Logging::print("InterfacePanel::populateBDMChoices(), bdmIdentification = \'%s\'\n", (const char *)bdmIdentification.ToAscii());
   if (deviceCount==0) {
      // No devices found
      bdmSelectChoiceControl->Append(_("[No devices Found]"));
      bdmSelectChoiceControl->Select(0);
      bdmSelectChoiceControl->SetClientData(0, (void*)-2);
      bdmSelectChoiceControl->Enable(false);
      bdmDeviceNum = -1;
      bdmIdentification = wxEmptyString;
      Logging::print("InterfacePanel::populateBDMChoices() - no devices\n");
      return;
   }
   // Add device names to choice box, client data is device number from usb scan
   vector<BdmInformation>::iterator it;
   for ( it=connectedBDMs.begin(); it < connectedBDMs.end(); it++ ) {
      int index = bdmSelectChoiceControl->Append(wxString::FromUTF8(it->getSerialNumber().c_str()));
      bdmSelectChoiceControl->SetClientData(index, (void*)it->getDeviceNumber());
   }
   // Try to select previous device
   if (bdmIdentification.empty() || !bdmSelectChoiceControl->SetStringSelection(bdmIdentification)) {
      // Select 1st device by default
      bdmSelectChoiceControl->Select(0);
   }
   bdmDeviceNum      = (int)bdmSelectChoiceControl->GetClientData();
   bdmIdentification = bdmSelectChoiceControl->GetStringSelection();

   bdmSelectChoiceControl->Enable(deviceCount>1);
   Logging::print("InterfacePanel::populateBDMChoices() - %d BDMs added.\n", deviceCount);
}

//! wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_DEFAULT
//!
//! @param event The event to handle
//!
void InterfacePanel::OnRefreshBDMClick( wxCommandEvent& event ) {
//   Logging::print("InterfacePanel::OnRefreshBDMClick()\n");
   populateBDMChoices();
   TransferDataToWindow();
}

//! wxEVT_COMMAND_COMBOBOX_SELECTED event handler for ID_SPEED_SELECT_COMBO
//!
//! @param event The event to handle
//!
void InterfacePanel::OnBDMSelectComboSelected( wxCommandEvent& event ) {
   Logging log("InterfacePanel::OnBDMSelectComboSelected");

   Logging::print("event.GetSelection() = %d\n", event.GetSelection());
   bdmDeviceNum = (int)bdmSelectChoiceControl->GetClientData(event.GetSelection());
   Logging::print("bdmDeviceNum = %d\n", bdmDeviceNum);

   shared->setBdmSerialNumber(connectedBDMs[bdmDeviceNum].getSerialNumber(), true);
   Logging::print("event.getBdmSerialNumber() = \'%s\'\n", shared->getBdmSerialNumber().c_str());
   TransferDataToWindow();
}

//! wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_GUESS_SPEED_CHECKBOX
//!
//! @param event The event to handle
//!
void InterfacePanel::OnMaskInterruptsWhenSteppingCheckboxClick( wxCommandEvent& event ) {
   bdmOptions.maskInterrupts = event.IsChecked();
}

