/*! \file
    \brief Implements Dummy Panel displaying a message

   AdvancedPanel.cpp

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
   -============================================================================
   |  5 Jul 2013 | Corrected printing of %b format in security             - pgo v4.10.6
   | 16 Dec 2012 | Security description added                              - pgo v4.10.4
   | ?? ??? 2012 | FlexNVM description added                               - pgo v4.10.?
   |  1 Jul 2010 | wxWidgets version created                               - pgo
   +============================================================================
   \endverbatim
 */

// For compilers that support precompilation, includes <wx/wx.h".
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include <ctype.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/imaglist.h>
#include <wx/gbsizer.h>
#include <wx/stattext.h>

#include "Common.h"
#include "USBDMDialogue.h"
#include "AdvancedPanel.h"
#include "Log.h"

const string settingsKey("AdvancedPanel");

enum {
   ID_POWER_OFF_DURATION_TEXT,
   ID_POWER_RECOVERY_INTERVAL_TEXT,
   ID_RESET_DURATION_TEXT,
   ID_RESET_RELEASE_INTERVAL_TEXT,
   ID_RESET_RECOVERY_INTERVAL_TEXT,
   ID_EEPROM_SIZE_CHOICE,
   ID_FLEXNVM_PARTITION_CHOICE,
   ID_SECURITY_REGION_CHOICE,
   ID_SECURITY_TEXT_ENTRY,
   ID_RESET_CUSTOM_VALUES_BUTTON,
   ID_ENABLE_CUSTOM_SECURITY_CHECKBOX,
};

/*
 * AdvancedPanel type definition
 */
IMPLEMENT_CLASS( AdvancedPanel, wxPanel )

/*
 * AdvancedPanel event table definition
 */
BEGIN_EVENT_TABLE( AdvancedPanel, wxPanel )
#if ((TARGET==CFV1) || (TARGET==ARM)) && !defined(GDB_SERVER)
EVT_CHOICE( ID_EEPROM_SIZE_CHOICE,                   AdvancedPanel::OnEeepromSizeChoiceSelected )
EVT_CHOICE( ID_FLEXNVM_PARTITION_CHOICE,             AdvancedPanel::OnFlexNvmPartionChoiceSelected )
#endif
#if !defined(LEGACY)
EVT_CHECKBOX( ID_ENABLE_CUSTOM_SECURITY_CHECKBOX,    AdvancedPanel::OnSecurityCheckboxClick )
EVT_CHOICE(   ID_SECURITY_REGION_CHOICE,             AdvancedPanel::OnSecurityMemoryRegionChoiceSelected )
EVT_BUTTON(   ID_RESET_CUSTOM_VALUES_BUTTON,         AdvancedPanel::OnResetCustomValueClick )
EVT_TEXT(     ID_SECURITY_TEXT_ENTRY,                AdvancedPanel::OnSecurityEditUpdate)
#endif
END_EVENT_TABLE()

#define settingsKey "AdvancedPanel"
const string eeepromSizeKey(             settingsKey ".eeepromSize");
const string flexNvmPartitionSizeKey(    settingsKey ".flexNvmPartitionSize");
const string customSecurityValueKey(     settingsKey ".customSecurityValue");

//========================================================================================================================
// AdvancedPanel

AdvancedPanel::AdvancedPanel( wxWindow* parent, SharedPtr shared, HardwareCapabilities_t bdmCapabilities) :
#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
      currentDevice(shared->getCurrentDevice()),
#endif
      bdmOptions(shared->getBdmOptions()) {
   Logging log("AdvancedPanel::AdvancedPanel");
   Init();
   Create(parent);
}

bool AdvancedPanel::Create(wxWindow* parent) {
   Logging::print("AdvancedPanel::Create()\n");
   if (!wxPanel::Create(parent) || !CreateControls()) {
      return false;
   }
   return true;
}

//===================================================================
//! Set the panel internal state to the default
//!
void AdvancedPanel::Init() {
   Logging log("AdvancedPanel::Init");

   // Set options to default
   // TransferDataToWindow() will validate these for the particular dialog/BDM being used.

   securityMemoryRegionIndex      = 0;

#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
   lastSecurityOption             = SEC_UNSECURED;
#endif
}

//! Control creation for USBDM Flash programming settings
//!
bool AdvancedPanel::CreateControls() {
   Logging log("AdvancedPanel::CreateControls");

   wxPanel* panel = this;
   wxBoxSizer* panelBoxSizerV = new wxBoxSizer(wxVERTICAL);
   panel->SetSizer(panelBoxSizerV);

   wxStaticBox* itemStaticBox = new wxStaticBox(panel, wxID_ANY, _("BDM Parameters"));
   wxStaticBoxSizer* itemStaticBoxSizer = new wxStaticBoxSizer(itemStaticBox, wxHORIZONTAL);
   panelBoxSizerV->Add(itemStaticBoxSizer, 0, wxGROW|wxLEFT|wxRIGHT|wxTOP, 5);

   wxGridBagSizer* gridBagSizer = new wxGridBagSizer(0,0);
   itemStaticBoxSizer->Add(gridBagSizer, 0, wxGROW|wxALL, 5);

   const int borderWidth = 3;

   wxStaticText* itemStaticText;
   int row = 0;

   // Note: copies are used so original is shared!
   TimeIntervalValidator timeIntervalValidator(NULL, NULL, 10, 10000);

   //===
   itemStaticText = new wxStaticText( panel, wxID_STATIC, _("Power Off duration"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(itemStaticText, wxGBPosition(row,0), wxGBSpan(1,2), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, borderWidth);

   timeIntervalValidator.setMin(100);
   timeIntervalValidator.setMax(10000);
   timeIntervalValidator.setObject("Power Off Duration", &bdmOptions.powerOffDuration);
   powerOffDurationTextControl = new NumberTextEditCtrl( panel, ID_POWER_OFF_DURATION_TEXT, wxEmptyString, wxDefaultPosition, wxSize(80, -1), 0, timeIntervalValidator );
   gridBagSizer->Add(powerOffDurationTextControl, wxGBPosition(row,2), wxGBSpan(1,1), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, borderWidth);
   powerOffDurationTextControl->SetToolTip(_("Duration to power off when cycling target power"));

   itemStaticText = new wxStaticText( panel, wxID_STATIC, _("ms"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(itemStaticText, wxGBPosition(row,3), wxGBSpan(1,1), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, borderWidth);

   row++;

   //===
   itemStaticText = new wxStaticText( panel, wxID_STATIC, _("Power On Recovery interval"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(itemStaticText, wxGBPosition(row,0), wxGBSpan(1,2), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, borderWidth);

   timeIntervalValidator.setMin(100);
   timeIntervalValidator.setMax(10000);
   timeIntervalValidator.setObject("Power On Recovery interval", &bdmOptions.powerOnRecoveryInterval);
   powerOnRecoveryIntervalTextControl = new NumberTextEditCtrl( panel, ID_POWER_RECOVERY_INTERVAL_TEXT, wxEmptyString, wxDefaultPosition, wxSize(80, -1), 0, timeIntervalValidator );
   gridBagSizer->Add(powerOnRecoveryIntervalTextControl, wxGBPosition(row,2), wxGBSpan(1,1), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, borderWidth);
   powerOnRecoveryIntervalTextControl->SetToolTip(_("Interval to wait after power on of target"));

   itemStaticText = new wxStaticText( panel, wxID_STATIC, _("ms"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(itemStaticText, wxGBPosition(row,3), wxGBSpan(1,1), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, borderWidth);

   row++;

   //===
   itemStaticText = new wxStaticText( panel, wxID_STATIC, _("Reset duration"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(itemStaticText, wxGBPosition(row,0), wxGBSpan(1,2), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, borderWidth);

   timeIntervalValidator.setMin(100);
   timeIntervalValidator.setMax(10000);
   timeIntervalValidator.setObject("Reset duration", &bdmOptions.resetDuration);
   resetDurationTextControl = new NumberTextEditCtrl( panel, ID_RESET_DURATION_TEXT, wxEmptyString, wxDefaultPosition, wxSize(80, -1), 0, timeIntervalValidator );
   gridBagSizer->Add(resetDurationTextControl, wxGBPosition(row,2), wxGBSpan(1,1), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, borderWidth);
   resetDurationTextControl->SetToolTip(_("Duration to apply reset to target"));

   itemStaticText = new wxStaticText( panel, wxID_STATIC, _("ms"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(itemStaticText, wxGBPosition(row,3), wxGBSpan(1,1), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, borderWidth);

   row++;

   //===
   itemStaticText = new wxStaticText( panel, wxID_STATIC, _("Reset Release interval"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(itemStaticText, wxGBPosition(row,0), wxGBSpan(1,2), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, borderWidth);

   timeIntervalValidator.setMin(10);
   timeIntervalValidator.setMax(10000);
   timeIntervalValidator.setObject("Reset Release interval", &bdmOptions.resetReleaseInterval);
   resetReleaseIntervalTextControl = new NumberTextEditCtrl( panel, ID_RESET_RELEASE_INTERVAL_TEXT, wxEmptyString, wxDefaultPosition, wxSize(80, -1), 0, timeIntervalValidator );
   gridBagSizer->Add(resetReleaseIntervalTextControl, wxGBPosition(row,2), wxGBSpan(1,1), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, borderWidth);
   resetReleaseIntervalTextControl->SetToolTip(_("Interval to hold other target signals after reset release"));

   itemStaticText = new wxStaticText( panel, wxID_STATIC, _("ms"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(itemStaticText, wxGBPosition(row,3), wxGBSpan(1,1), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, borderWidth);

   row++;

   //===
   itemStaticText = new wxStaticText( panel, wxID_STATIC, _("Reset Recovery interval"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(itemStaticText, wxGBPosition(row,0), wxGBSpan(1,2), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, borderWidth);

   timeIntervalValidator.setMin(10);
   timeIntervalValidator.setMax(10000);
   timeIntervalValidator.setObject("Reset Recovery interval", &bdmOptions.resetRecoveryInterval);
   resetRecoveryIntervalTextControl = new NumberTextEditCtrl( panel, ID_RESET_RECOVERY_INTERVAL_TEXT, wxEmptyString, wxDefaultPosition, wxSize(80, -1), 0, timeIntervalValidator );
   gridBagSizer->Add(resetRecoveryIntervalTextControl, wxGBPosition(row,2), wxGBSpan(1,1), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, borderWidth);
   resetRecoveryIntervalTextControl->SetToolTip(_("Interval to wait after target reset"));

   itemStaticText = new wxStaticText( panel, wxID_STATIC, _("ms"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(itemStaticText, wxGBPosition(row,3), wxGBSpan(1,1), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, borderWidth);

   row++;

#if ((TARGET==CFV1) || (TARGET==ARM)) && defined(FLASH_PROGRAMMER)
   //================================================================================
   itemStaticBox = new wxStaticBox(panel, wxID_ANY, _("FlexNVM Parameters"));
   itemStaticBoxSizer = new wxStaticBoxSizer(itemStaticBox, wxHORIZONTAL);
   panelBoxSizerV->Add(itemStaticBoxSizer, 0, wxGROW|wxLEFT|wxRIGHT|wxTOP, borderWidth);

   gridBagSizer = new wxGridBagSizer(0,0);
   itemStaticBoxSizer->Add(gridBagSizer, 0, wxGROW|wxALL, borderWidth);
   row = 0;

   //===
   eeepromSizeStaticText = new wxStaticText( panel, wxID_STATIC, _("EEEPROM Size (FF)"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(eeepromSizeStaticText, wxGBPosition(row,0), wxGBSpan(1,1), wxALIGN_CENTER_VERTICAL|wxLEFT, borderWidth);
   eeepromSizeChoiceControl = new wxChoice( panel, ID_EEPROM_SIZE_CHOICE, wxDefaultPosition , wxSize(150, -1));
   gridBagSizer->Add(eeepromSizeChoiceControl, wxGBPosition(row,1), wxGBSpan(1,1), wxALIGN_CENTER_VERTICAL|wxLEFT|wxEXPAND, borderWidth);
   eeepromSizeChoiceControl->SetToolTip(_("Controls size of emulated EEPROM region(s) in FlexRAM"));

   itemStaticText = new wxStaticText( panel, wxID_STATIC, _("bytes"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(itemStaticText, wxGBPosition(row,2), wxGBSpan(1,1), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, borderWidth);
   row++;

   //===
   flexNvmPartitionStaticText = new wxStaticText( panel, wxID_STATIC, _("FlexNVM Partition (FF)"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(flexNvmPartitionStaticText, wxGBPosition(row,0), wxGBSpan(1,1), wxALIGN_CENTER_VERTICAL|wxLEFT, borderWidth);
   flexNvmPartitionChoiceControl = new wxChoice( panel, ID_FLEXNVM_PARTITION_CHOICE, wxDefaultPosition , wxSize(150, -1));
   gridBagSizer->Add(flexNvmPartitionChoiceControl, wxGBPosition(row,1), wxGBSpan(1,1), wxALIGN_CENTER_VERTICAL|wxLEFT|wxTOP, borderWidth);
   flexNvmPartitionChoiceControl->SetToolTip(_("Controls how FlexNVM is divided between Data Flash and EEPROM backing store\n"
                                               "EEPROM backing store size >= 16 x EEEPROM size - affects flash lifetime"));
//   flexNvmPartitionChoiceControl->SetMinSize(wxSize(100,0));
   itemStaticText = new wxStaticText( panel, wxID_STATIC, _("Kbytes"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(itemStaticText, wxGBPosition(row,2), wxGBSpan(1,1), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, borderWidth);

   wxSize sz(flexNvmPartitionChoiceControl->GetMinSize());
   sz.x += 10;
   flexNvmPartitionChoiceControl->SetMinSize(sz);
   row++;
   //===
   flexNvmDescriptionStaticControl = new wxStaticText( panel, wxID_STATIC, _("Estimated 16-bit write cycles (based on JU128 specs) = ----------"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(flexNvmDescriptionStaticControl, wxGBPosition(row,0), wxGBSpan(1,3), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, borderWidth);
   row++;

   populateEeepromControl();
   populatePartitionControl();
#endif

#if !defined(LEGACY) && defined(FLASH_PROGRAMMER)
   //================================================================================
   itemStaticBox = new wxStaticBox(panel, wxID_ANY, _("Custom Security Parameters"));
   itemStaticBoxSizer = new wxStaticBoxSizer(itemStaticBox, wxHORIZONTAL);
   panelBoxSizerV->Add(itemStaticBoxSizer, 0, wxGROW|wxLEFT|wxRIGHT|wxTOP, borderWidth);

   gridBagSizer = new wxGridBagSizer(0,0);
   itemStaticBoxSizer->Add(gridBagSizer, 0, wxGROW|wxALL, borderWidth);
   row = 0;

   //===
   customSecurityCheckbox = new wxCheckBox( panel, ID_ENABLE_CUSTOM_SECURITY_CHECKBOX, _("Enable"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(customSecurityCheckbox, wxGBPosition(row,0), wxGBSpan(1,1), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, borderWidth);

//   itemStaticText = new wxStaticText( panel, wxID_STATIC, _("Region"), wxDefaultPosition, wxDefaultSize, 0 );
//   gridBagSizer->Add(itemStaticText, wxGBPosition(row,0), wxGBSpan(1,1), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, borderWidth);
   securityMemoryRegionChoice = new wxChoice( panel, ID_SECURITY_REGION_CHOICE, wxDefaultPosition , wxSize(130, -1));
   gridBagSizer->Add(securityMemoryRegionChoice, wxGBPosition(row,1), wxGBSpan(1,1), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, borderWidth);
   securityMemoryRegionChoice->SetToolTip(_("Security information is programmed to this memory region"));
   resetCustomButtonControl = new wxButton( panel, ID_RESET_CUSTOM_VALUES_BUTTON, _("&Reset Values"), wxDefaultPosition, wxDefaultSize, 0 );
   resetCustomButtonControl->SetToolTip(_("Reset custom values to unsecured default"));
   gridBagSizer->Add(resetCustomButtonControl, wxGBPosition(row,2), wxGBSpan(1,2), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, borderWidth);
   row++;

   //===

   securityValuesTextControl = new wxTextCtrl( panel, ID_SECURITY_TEXT_ENTRY, _(""), wxDefaultPosition , wxSize(300, 20), 0);
   gridBagSizer->Add(securityValuesTextControl, wxGBPosition(row,0), wxGBSpan(1,3), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, borderWidth);
   securityValuesTextControl->SetToolTip(_("Security value used for device"));
   securityValuesTextControl->SetValidator(SecurityValidator("Security value", SecurityInfoPtr()));
   row++;

   //===
   securityMemoryRegionSecurityAddress = new wxStaticText( panel, wxID_STATIC, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(securityMemoryRegionSecurityAddress, wxGBPosition(row,0), wxGBSpan(1,2), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT|wxTOP, borderWidth);
   row++;

   //===
#ifdef _WIN32
#define CONTROL_WIDTH (320)
#else
#define CONTROL_WIDTH (380)
#endif
   securityDescriptionStaticText = new wxStaticText( panel, wxID_STATIC, _("...Status..."), wxDefaultPosition, wxSize(CONTROL_WIDTH, 75), wxALIGN_LEFT|wxST_NO_AUTORESIZE );
   gridBagSizer->Add(securityDescriptionStaticText, wxGBPosition(row,0), wxGBSpan(1,3), wxALIGN_CENTER_VERTICAL|wxLEFT|wxRIGHT, borderWidth);
   securityDescriptionStaticText->SetToolTip(_("See Target tab to change how these value are used"));
   row++;
   #endif

   return true;
}

#if ((TARGET==CFV1) || (TARGET==ARM)) && defined(FLASH_PROGRAMMER)
//! Populates eeepromSizeChoiceControl with EEEPROM sizes
//! Selects 1st entry if reload is necessary (device changed)
//!
void AdvancedPanel::populateEeepromControl() {

   static FlexNVMInfoConstPtr lastFlexNVMInfo;
   if (currentDevice == NULL) {
      Logging::print("AdvancedPanel::populateEeepromControl() - currentDevice not set\n");
      lastFlexNVMInfo.reset();
      eeepromSizeChoiceControl->Clear();
      eeepromSizeChoiceControl->Append(_("[No device selected]"));
      eeepromSizeChoiceControl->Select(0);
      eeepromSizeChoiceControl->Enable(false);
      eeepromSizeChoice = 0;
      return;
   }
   FlexNVMInfoConstPtr flexNVMInfo = currentDevice->getflexNVMInfo();
   if (flexNVMInfo == NULL) {
      Logging::print("AdvancedPanel::populatePartitionControl() - device has no flexNVMInfo\n");
      lastFlexNVMInfo.reset();
      eeepromSizeChoiceControl->Clear();
      eeepromSizeChoiceControl->Append(_("[EEEPROM not supported]"));
      eeepromSizeChoiceControl->Select(0);
      eeepromSizeChoiceControl->Enable(false);
      eeepromSizeChoice = 0;
      return;
   }
   if (flexNVMInfo.get() == lastFlexNVMInfo.get()) {
      // No device change - no change in list
      Logging::print("AdvancedPanel::populateEeepromControl() - no update as flexNVMInfo unchanged\n");
      return;
   }
   Logging::print("AdvancedPanel::populateEeepromControl()\n");
   lastFlexNVMInfo = flexNVMInfo;
   const vector<FlexNVMInfo::EeepromSizeValue> &list(flexNVMInfo->getEeepromSizeValues());
   vector<FlexNVMInfo::EeepromSizeValue>::const_iterator it;

   eeepromSizeChoiceControl->Clear();
   for ( it=list.begin(); it < list.end(); it++) {
      eeepromSizeChoiceControl->Append(wxString(it->description.c_str(), wxConvUTF8));
   }
   eeepromSizeChoiceControl->Select(0);
   eeepromSizeChoiceControl->Enable(true);
   eeepromSizeChoice = 0;
   flexNvmPartitionIndex = 0; // Previous value is now invalid as partition table may have changed
}

//! Finds table index for given eeeprom size (FlexRAM used as Emulated eeprom)
//!
//! @param eepromSize size to look for
//!
//! @return index into eeepromSizeValues (and eeepromSizeChoiceControl control)
//!
int AdvancedPanel::findEeepromSizeIndex(unsigned eepromSize) {
   if (currentDevice == NULL) {
      Logging::print("AdvancedPanel::findEeepromSizeIndex() - currentDevice not set\n");
      return 0;
   }
   FlexNVMInfoConstPtr flexNVMInfo = currentDevice->getflexNVMInfo();
   if (flexNVMInfo == NULL) {
      Logging::print("AdvancedPanel::findEeepromSizeIndex() - flexNVMInfo not set\n");
      return 0;
   }
   const vector<FlexNVMInfo::EeepromSizeValue> &list(flexNVMInfo->getEeepromSizeValues());
   vector<FlexNVMInfo::EeepromSizeValue>::const_iterator it;

   int index;
   for ( it=list.begin(), index=0;
         it < list.end();
         it++, index++) {
      if (it->size == eepromSize) {
         return index;
      }
   }
   return 0; // default to 1st entry (zero size)
}

/*
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_DEVICE_TYPE_CHOICE
 */
void AdvancedPanel::OnEeepromSizeChoiceSelected( wxCommandEvent& event ) {
   // Get currently selected eeeprom choice
   eeepromSizeChoice = event.GetSelection();
   Logging::print("AdvancedPanel::OnEeepromSizeChoiceSelected(): EEPROM size choice = %d\n", eeepromSizeChoice);
   TransferDataToWindow();
}

//! Populates flexNvmPartitionChoiceControl with Partition values
//!
//! @note Entries are filtered by minimum size required to satisfy eeepromSizeChoice
//! @note flexNvmPartitionIndex is used to select entry if valid or 1st entry is used
//!
void AdvancedPanel::populatePartitionControl() {
   assert(sizeof(int) <= sizeof(intptr_t));

   int flexNvmPartitionChoice = 0;      // Default to select 1st entry in populated control

   Logging::print("AdvancedPanel::populatePartitionControl()\n");
   flexNvmPartitionChoiceControl->Clear();
   if (currentDevice == NULL) {
      Logging::print("AdvancedPanel::populatePartitionControl() - currentDevice not set\n");
      flexNvmPartitionChoiceControl->Append(_("[No device selected]"));
      flexNvmPartitionChoiceControl->Select(0);
      flexNvmPartitionChoiceControl->Enable(false);
      flexNvmPartitionIndex = 0;
      return;
   }
   FlexNVMInfoConstPtr flexNVMInfo = currentDevice->getflexNVMInfo();
   if (flexNVMInfo == NULL) {
      Logging::print("AdvancedPanel::populatePartitionControl() - device has no flexNVMInfo\n");
      flexNvmPartitionChoiceControl->Append(_("[EEEPROM not supported]"));
      flexNvmPartitionChoiceControl->Select(0);
      flexNvmPartitionChoiceControl->Enable(false);
      flexNvmPartitionIndex = 0;
      return;
   }
   const vector<FlexNVMInfo::EeepromSizeValue> &eeepromSizeValues(flexNVMInfo->getEeepromSizeValues());
   const vector<FlexNVMInfo::FlexNvmPartitionValue> &flexNvmPartitionValues(flexNVMInfo->getFlexNvmPartitionValues());
   if (eeepromSizeChoice<=0) {
      flexNvmPartitionChoiceControl->Append(_("[All DFlash]"));
      flexNvmPartitionChoiceControl->Enable(false);
      flexNvmPartitionIndex = 0;
   }
   else {
      vector<FlexNVMInfo::FlexNvmPartitionValue>::const_iterator it;

      // Minimum required backing store for currently selected EEEPROM size
      unsigned minimumBackingStore = flexNVMInfo->getBackingRatio()*eeepromSizeValues[eeepromSizeChoice].size;
      int newIndex            = 0;                                            // Default No EEPROM
      int index;
      for ( it=flexNvmPartitionValues.begin(), index = 0; it < flexNvmPartitionValues.end(); it++, index++) {
         if (it->backingStore >= minimumBackingStore) {
            int controlIndex = flexNvmPartitionChoiceControl->Append(wxString(it->description.c_str(), wxConvUTF8));
            // Save index as client data as not all entries may be present in control
            flexNvmPartitionChoiceControl->SetClientData(controlIndex, (void*)(intptr_t)index);
            if (newIndex==0) {
               // Use 1st added choice entry as default
               newIndex = index;
            }
            if (index == flexNvmPartitionIndex) {
               // Previously selected value still available - use it selected entry
               flexNvmPartitionChoice = controlIndex; // record control entry to select
               newIndex               = index;        // record corresponding table entry
            }
         }
      }
      flexNvmPartitionChoiceControl->Enable(true);
      flexNvmPartitionIndex = newIndex;
   }
   flexNvmPartitionChoiceControl->Select(flexNvmPartitionChoice);
   Logging::print("AdvancedPanel::populatePartitionControl(), choice=%d, index=%d => size=%d\n",
          flexNvmPartitionChoice, flexNvmPartitionIndex, flexNvmPartitionValues[flexNvmPartitionIndex].backingStore);
}

//! Finds table index for given backingStoreSize size
//!
//! @param backingStoreSize size to look for
//!
//! @return index into flexNvmPartitionValues
//!
int AdvancedPanel::findPartitionControlIndex(unsigned backingStoreSize) {
   if (currentDevice == NULL) {
      Logging::print("AdvancedPanel::findPartitionControlIndex() - currentDevice not set\n");
      return 0;
   }
   FlexNVMInfoConstPtr flexNVMInfo = currentDevice->getflexNVMInfo();
   if (flexNVMInfo == NULL) {
      Logging::print("AdvancedPanel::findPartitionControlIndex() - flexNVMInfo not set\n");
      return 0;
   }
   const vector<FlexNVMInfo::FlexNvmPartitionValue> &flexNvmPartitionValues(flexNVMInfo->getFlexNvmPartitionValues());
   vector<FlexNVMInfo::FlexNvmPartitionValue>::const_iterator it;
   int index;
   for ( it=flexNvmPartitionValues.begin(), index = 0; it < flexNvmPartitionValues.end(); it++, index++) {
      if (it->backingStore == backingStoreSize) {
         return index;
         }
      }
   return 0; // default to 1st entry (zero size)
}

/*
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_DEVICE_TYPE_CHOICE
 */
void AdvancedPanel::OnFlexNvmPartionChoiceSelected( wxCommandEvent& event ) {
   // Get currently selected FlexNVM partition choice
   flexNvmPartitionIndex = (int)(intptr_t) event.GetClientData();
   Logging::print("AdvancedPanel::OnFlexNvmPartionChoiceSelected(): Partition value =0x%02X\n", flexNvmPartitionIndex);
   TransferDataToWindow();
}
#endif

//! Updates GUI from internal FlashNVM  state
//!
//! @note values are validated
//!
void AdvancedPanel::updateFlashNVM() {
#if ((TARGET==CFV1) || (TARGET==ARM)) && defined(FLASH_PROGRAMMER)
   static const double writeEfficiency = 0.5;     // Assume 16/32-bit writes
   static const double endurance       = 10000.0; // From JU128 specification sheet
   Logging log("AdvancedPanel::updateFlashNVM");

   populateEeepromControl();
   eeepromSizeChoiceControl->SetSelection(eeepromSizeChoice);
   populatePartitionControl();

   FlexNVMInfoConstPtr flexNVMInfo;
   if (currentDevice == NULL) {
      Logging::print("CurrentDevice not set\n");
   }
   else {
      flexNVMInfo = currentDevice->getflexNVMInfo();
   }
   if (flexNVMInfo == NULL) {
      flexNvmDescriptionStaticControl->SetLabel(_("EEPROM emulation not available"));
      eeepromSizeChoice     = 0;
      flexNvmPartitionIndex = 0;
      eeepromSizeStaticText->SetLabel(_("EEEPROM Size (--)"));
      flexNvmPartitionStaticText->SetLabel(_("FlexNVM Partition (--)"));
      return;
   }
   if (eeepromSizeChoice == 0) {
      flexNvmDescriptionStaticControl->SetLabel(_("EEPROM emulation will be disabled if device is mass-erased"));
      eeepromSizeStaticText->SetLabel(_("EEEPROM Size (FF)"));
      flexNvmPartitionStaticText->SetLabel(_("FlexNVM Partition (FF)"));
      return;
   }
   const vector<FlexNVMInfo::EeepromSizeValue>      &eeepromSizeValues(flexNVMInfo->getEeepromSizeValues());
   const vector<FlexNVMInfo::FlexNvmPartitionValue> &flexNvmPartitionValues(flexNVMInfo->getFlexNvmPartitionValues());
   unsigned eeepromSize = eeepromSizeValues[eeepromSizeChoice].size;
   unsigned eepromSize  = flexNvmPartitionValues[flexNvmPartitionIndex].backingStore;
   double estimatedFlexRamWrites = (writeEfficiency*endurance*(eepromSize-2*eeepromSize))/eeepromSize;
   char buff[100];
   Logging::print("    eeepromSize=%d, eepromSize=%d, ratio=%.2g, estimatedFlexRamWrites=%.2g\n",
              eeepromSize, eepromSize, (double)eepromSize/eeepromSize, estimatedFlexRamWrites);

   snprintf(buff, sizeof(buff),"EEEPROM Size (%02X)", eeepromSizeValues[eeepromSizeChoice].value);
   eeepromSizeStaticText->SetLabel(wxString(buff, wxConvUTF8));
   snprintf(buff, sizeof(buff),"FlexNVM Partition (%02X)", flexNvmPartitionValues[flexNvmPartitionIndex].value);
   flexNvmPartitionStaticText->SetLabel(wxString(buff, wxConvUTF8));

   snprintf(buff, sizeof(buff),"Estimated 16-bit write cycles (based on JU128 specs) = %.2g", estimatedFlexRamWrites);
   flexNvmDescriptionStaticControl->SetLabel(wxString(buff, wxConvUTF8));
#endif
}

#if !defined(LEGACY)
//! Populates customSecurityInfoPtr[] with suitable starting values if not already present
//! Populates securityMemoryRegionChoice with memory regions
//! The above are based on the current device
void AdvancedPanel::populateSecurityControl() {
#if defined(FLASH_PROGRAMMER)
   Logging log("AdvancedPanel::populateSecurityControl");
   securityMemoryRegionChoice->Clear();
   if (currentDevice == NULL) {
      Logging::print("CurrentDevice not set\n");
      securityMemoryRegionChoice->Append(_("[No device selected]"));
      securityMemoryRegionChoice->Select(0);
      securityMemoryRegionChoice->SetClientData(0, 0);
      securityMemoryRegionChoice->Enable(false);
      securityMemoryRegionIndex = 0;

      resetCustomButtonControl->Enable(false);
      customSecurityCheckbox->Enable(false);
      return;
   }
   int index = 0;
   MemoryRegionConstPtr memoryRegionPtr = currentDevice->getMemoryRegion(index);
   int  securityRegionFounds = 0;
   while (memoryRegionPtr != NULL) {
      const MemoryRegion::MemoryRange *memoryRange = memoryRegionPtr->getMemoryRange(0);
      if (memoryRange == NULL) {
         throw(MyException("AdvancedPanel::populateSecurityControl() - empty memory range!"));
      }
      SecurityEntryConstPtr securityEntry = memoryRegionPtr->getSecurityEntry();
      if (securityEntry != NULL) {
//         Logging::print("securityEntry => %s\n", (const char *)securityEntry->toString().c_str());
         // Add memory to list as has security area
         securityRegionFounds++;
         wxString memName(memoryRegionPtr->getMemoryTypeName(), wxConvUTF8);
         wxString descr;
         descr.Printf(_("%s @ %X"), (const char *)memName.c_str(), memoryRange->start);
//         descr.Printf(_("%s @ %X"), memoryRange->start);
         int itemIndex = securityMemoryRegionChoice->Append(descr);
         securityMemoryRegionChoice->SetClientData(itemIndex, (void*)(intptr_t)index);
         if (customSecurityInfoPtr[itemIndex] == NULL) {
            // Add default setting memory security area
            customSecurityInfoPtr[itemIndex] = SecurityInfoPtr(new SecurityInfo(*securityEntry->getUnsecureInformation()));
            customSecurityInfoPtr[itemIndex]->setMode(SecurityInfo::custom);
            Logging::print("Created customSecurityInfo[%d] = %s\n",
                           itemIndex, (const char *)customSecurityInfoPtr[itemIndex]->toString().c_str());
         }
      }
      memoryRegionPtr = currentDevice->getMemoryRegion(++index);
   }
   if (securityRegionFounds >= 1) {
      if (securityRegionFounds >= 2) {
         securityMemoryRegionChoice->Enable(true);
      }
      else {
         securityMemoryRegionChoice->Enable(false);
      }
      customSecurityCheckbox->Enable(true);
      resetCustomButtonControl->Enable(currentDevice->getSecurity() == SEC_CUSTOM);
      if (securityMemoryRegionIndex > securityMemoryRegionChoice->GetCount()) {
         securityMemoryRegionIndex = 0;
      }
      securityMemoryRegionChoice->Select(securityMemoryRegionIndex);
   }
   else {
      Logging::print("No Memory Regions\n");
      securityMemoryRegionChoice->Append(_("[No memory regions]"));
      securityMemoryRegionChoice->Select(0);
      securityMemoryRegionChoice->SetClientData(0, 0);
      securityMemoryRegionChoice->Enable(false);
      securityMemoryRegionIndex = 0;

      customSecurityCheckbox->Enable(false);
      resetCustomButtonControl->Enable(false);
   }
#endif
}

//! Parse current value
//!
//! @return parsed value as a string
//!
wxString AdvancedPanel::parseSecurityValue() {
   Logging log("AdvancedPanel::parseSecurityValue");

   enum {s_text, s_width, s_escape, s_bits} state = s_text;

   if (securityInfoPtr == NULL) {
      Logging::print("securityInfoPtr == NULL\n");
      return _("[not applicable]");
   }
   else if (securityDescriptionPtr == NULL) {
      Logging::print("securityDescriptionPtr == NULL\n");
      return _("[no description available]");
   }
   else {
      Logging::print("parsing...\n");

      // Update securityInfoPtr
      SecurityValidator *validator = dynamic_cast<SecurityValidator*>(securityValuesTextControl->GetValidator());
      securityInfoPtr->setSecurityInfo(validator->getHexValues());

//      unsigned       size          = securityInfoPtr->getSize();
      const uint8_t *securityValue = securityInfoPtr->getData();

      char buffer[500], *b=buffer;
      int securityIndex = 0; // index into security value array
      string s = securityDescriptionPtr->getSecurityDescription();
      unsigned width    = 0;
      unsigned value    = 0;
      unsigned bitMask  = 0;
      unsigned bitCount = 0;
      char bitName[20], *pBitName=bitName;
      for (unsigned index=0; index<s.length(); index++) {
         if (b+2*width+4 >= buffer+sizeof(buffer)) {
            Logging::print("result too large\n");
            break;
         }
         switch(state) {
            case s_text:
               if (s[index] == '%') {
                  state    = s_width;
                  width    = 0;
               }
               else if (s[index] == '\\') {
                  state = s_escape;
               }
               else {
                  *b++ = s[index];
               }
               break;
            case s_escape:
               state = s_text;
               switch(s[index]) {
                  case 'n':
                     *b++ = '\n';
                     break;
                  case 'r':
                     *b++ = '\r';
                     break;
                  case 't':
                     *b++ = '\t';
                     break;
                  default:
                     *b++ = s[index];
                     break;
               }
               break;
            case s_width:
               if (isdigit(s[index])) {
                  width *= 10;
                  width += s[index]-'0';
               }
               else {
                  if (width == 0) {
                     width = 1;
                  }
                  state = s_text;
                  switch(s[index]) {
                     case 'x':
                     case 'X':
                        bitCount = 0;
                        for(unsigned sub=0; sub < width; sub++) {
                           *b++ = tohex(securityValue[securityIndex]>>4);
                           *b++ = tohex(securityValue[securityIndex++]);
                        }
                        break;
                     case 'b':
                     case 'B':
                        if (bitCount == 0) {
                           value = securityValue[securityIndex++];
                           bitCount = 8;
                        }
                        if (width > bitCount) {
                           throw MyException("AdvancedPanel::parseSecurityValue() - Binary field width crosses byte boundary");
                        }
                        bitCount -= width;
                        bitMask = ((1<<width)-1);
                        sprintf(b,"%X",(value>>bitCount)&bitMask);
                        b += strlen(b);
                        break;
                     case '[':
                        bitCount = 0;
                        value = 0;
                        for(unsigned sub=0; sub < width; sub++) {
                           value *= 8;
                           value += securityValue[securityIndex++];
                        }
                        bitMask  = 1<<((width*8)-1);
                        pBitName = bitName;
                        state = s_bits;
                        break;
                     case 'd':
                        bitCount = 0;
                        break;
                     default:
                        bitCount = 0;
                        *b++ = '*';
                        break;
                  }
               }
               break;
            case s_bits:
               if (isalnum(s[index])) {
                  *pBitName++ = s[index];
               }
               else if ((s[index] == ',')||(s[index] == '|')||(s[index] == ']')) {
                  *pBitName++ = '\0';
                  if ((value & bitMask) != 0) {
                     strcpy(b, pBitName);
                     b += strlen(pBitName);
                  }
                  else {
                     *b++ = '0';
                  }
                  pBitName = bitName;
                  bitMask >>= 1;
                  if (s[index] == ']') {
                     state = s_text;
                  }
                  else {
                     *b++ = s[index];
                  }
               }
               else {
                  // ignore
               }
               break;
            default:
               break;
         }
          s[index];
      }
      *b = '\0';
      return wxString(buffer, wxConvUTF8);
   }
}

void AdvancedPanel::updateSecurityDescription() {
   Logging log("AdvancedPanel::updateSecurityDescription");
   securityDescriptionStaticText->SetLabel(parseSecurityValue());
}

//! Updates the security information display
//!
void AdvancedPanel::updateSecurity() {
#if defined(FLASH_PROGRAMMER)
   Logging log("AdvancedPanel::updateSecurity");
   Logging::print("securityMemoryRegionIndex = %d\n", securityMemoryRegionIndex);
   int memoryIndex = (int)(intptr_t)securityMemoryRegionChoice->GetClientData(securityMemoryRegionIndex);
   Logging::print("memoryIndex = %d\n", memoryIndex);
   MemoryRegionConstPtr   memoryRegionPtr = currentDevice->getMemoryRegion(memoryIndex);
   SecurityEntryConstPtr  securityEntry;

   securityInfoPtr        = SecurityInfoPtr((SecurityInfo *)0);
   securityDescriptionPtr = SecurityDescriptionPtr((SecurityDescription *)0);

   wxString sDescription(_(""));

   SecurityValidator *validator = dynamic_cast<SecurityValidator*>(securityValuesTextControl->GetValidator());
   if (memoryRegionPtr == NULL) {
      Logging::print("No memory Region information\n");
      securityValuesTextControl->SetValue(_("[Illegal memory region]"));
   }
   else {
      securityEntry = memoryRegionPtr->getSecurityEntry();
      if (securityEntry == NULL) {
         Logging::print("No security information for memory region\n");
         securityValuesTextControl->SetValue(_("[No security region]"));
      }
      else {
         securityDescriptionPtr = securityEntry->getSecurityDescription();
         switch (currentDevice->getSecurity()) {
            case SEC_DEFAULT:
               Logging::print("SEC_DEFAULT\n");
               securityValuesTextControl->SetValue(_("[Using values from flash image]"));
               securityInfoPtr = SecurityInfoPtr();
               sDescription = _(", determined by Flash image");
               break;
            case SEC_SECURED:
               Logging::print("SEC_SECURED\n");
               if (securedInfoPtr == NULL) {
                  securedInfoPtr = SecurityInfoPtr(new SecurityInfo());
               }
               *securedInfoPtr  = *securityEntry->getSecureInformation();
               securityInfoPtr  = securedInfoPtr;
               sDescription = _(", using default secured value");
               break;
            case SEC_UNSECURED:
            case SEC_SMART:
               Logging::print("SEC_UNSECURED/SEC_SMART\n");
               if (unsecuredInfoPtr == NULL) {
                  unsecuredInfoPtr = SecurityInfoPtr(new SecurityInfo());
               }
               *unsecuredInfoPtr = *securityEntry->getUnsecureInformation();
               securityInfoPtr   = unsecuredInfoPtr;
               sDescription = _(", using default unsecured value");
               break;
            case SEC_CUSTOM:
               Logging::print("SEC_CUSTOM\n");
               if (customSecurityInfoPtr[securityMemoryRegionIndex] == NULL) {
                  // Entries should already be populated
                  throw MyException("AdvancedPanel::updateSecurity()- Unexpected NULL security entry");
//                  Logging::print("Creating customSecurityInfo\n");
//                  customSecurityInfoPtr[securityMemoryRegionIndex] = SecurityInfoPtr(new SecurityInfo(*securityEntry->getUnsecureInformation()));
//                  customSecurityInfoPtr[securityMemoryRegionIndex]->setMode(SecurityInfo::custom);
//                  securityEntry->setCustomSecureInformation(customSecurityInfoPtr[securityMemoryRegionIndex]);
               }
               securityInfoPtr = customSecurityInfoPtr[securityMemoryRegionIndex];
               Logging::print("Setting to Custom %s\n", (const char *)customSecurityInfoPtr[securityMemoryRegionIndex]->toString().c_str());
               sDescription = _(", using custom security value");
               break;
         }
      }
   }
   validator->setObject("Security Value", securityInfoPtr);
   if (securityInfoPtr == NULL) {
      Logging::print("No security information\n");
      securityMemoryRegionSecurityAddress->SetLabel(wxEmptyString);
      validator->enable(false);
      securityValuesTextControl->Enable(false);
   }
   else {
      wxString sAddress;
      sAddress.Printf(_("security @ %08X"), memoryRegionPtr->getSecurityAddress());
      sAddress += sDescription;
      securityMemoryRegionSecurityAddress->SetLabel(sAddress);
      validator->enable(true);
      securityValuesTextControl->Enable(currentDevice->getSecurity() == SEC_CUSTOM);
   }
   customSecurityCheckbox->SetValue(currentDevice->getSecurity() == SEC_CUSTOM);
#endif
}

void AdvancedPanel::OnSecurityMemoryRegionChoiceSelected( wxCommandEvent& event ) {
   LOGGING_Q;
   int index = event.GetSelection();
   // Save date for currently selected security memory region choice
   Logging::print("From = %d\n", securityMemoryRegionIndex);
   TransferDataFromWindow();
   // Change memory region
   securityMemoryRegionIndex = index;
   TransferDataToWindow();
   Logging::print("To   = %d\n", securityMemoryRegionIndex);
}

//! wxEVT_COMMAND_BUTTON_CLICKED event handler
//!
//! @param event The event to handle
//!
void AdvancedPanel::OnResetCustomValueClick( wxCommandEvent& event ) {
   Logging::print("AdvancedPanel::OnResetCustomValueClick()\n");
   for(int index=0; index<maxSecurityNum; index++) {
      customSecurityInfoPtr[index] = SecurityInfoPtr();
   }
   TransferDataToWindow();
}

//! wxEVT_COMMAND_BUTTON_CLICKED event handler
//!
//! @param event The event to handle
//!
void AdvancedPanel::OnSecurityCheckboxClick( wxCommandEvent& event ) {
   Logging::print("AdvancedPanel::OnSecurityCheckboxClick()\n");
   if (event.IsChecked()) {
      // Enabling custom values

      // Save current value to return to if disabled
      lastSecurityOption = currentDevice->getSecurity();
      if (lastSecurityOption == SEC_CUSTOM) {
         lastSecurityOption = SEC_UNSECURED;
      }
      // Set custom values
      currentDevice->setSecurity(SEC_CUSTOM);
   }
   else {
      // Restore last non-custom value
      currentDevice->setSecurity(lastSecurityOption);
   }
   TransferDataToWindow();
}

void AdvancedPanel::OnSecurityEditUpdate(wxCommandEvent& event) {
   Logging::print("OnSecurityEditUpdate()\n");
   updateSecurityDescription();
}

#endif

//!
//! @param settings - Object to load settings from
//!
void AdvancedPanel::loadSettings(const AppSettings &settings) {
   Logging log("AdvancedPanel::loadSettings");

#if defined(PROGRAMMER) && ((TARGET==CFV1) || (TARGET==ARM))
   int eepromSize = settings.getValue(eeepromSizeKey,             0);
   eeepromSizeChoice = findEeepromSizeIndex(eepromSize);
   if (eeepromSizeChoice == 0) {
      flexNvmPartitionIndex = 0;
   }
   else {
      int partitionSize = settings.getValue(flexNvmPartitionSizeKey,        0);
      flexNvmPartitionIndex = findPartitionControlIndex(partitionSize);
   }
#endif
#if !defined(LEGACY)
   for(int index=0; index<maxSecurityNum; index++) {
      string value = settings.getValue(customSecurityValueKey+'.'+(char)('0'+index), string(""));
      if (!value.empty()) {
         customSecurityInfoPtr[index] = SecurityInfoPtr(new SecurityInfo(value.length()/2, SecurityInfo::custom, value));
      }
   }
#endif
//   TransferDataToWindow();
}

//! Save setting file
//!
//! @param settings      - Object to save settings to
//!
void AdvancedPanel::saveSettings(AppSettings &settings) {
   Logging log("AdvancedPanel::saveSettings");

#if defined(PROGRAMMER) && ((TARGET==CFV1) || (TARGET==ARM))
   FlexNVMInfoConstPtr flexNVMInfo = currentDevice->getflexNVMInfo();
   if (flexNVMInfo != NULL) {
      const vector<FlexNVMInfo::EeepromSizeValue>        &eeepromSizeValues(flexNVMInfo->getEeepromSizeValues());
      const vector<FlexNVMInfo::FlexNvmPartitionValue>   &flexNvmPartitionValues(flexNVMInfo->getFlexNvmPartitionValues());
      settings.addValue(eeepromSizeKey,               eeepromSizeValues[eeepromSizeChoice].size);
      if (eeepromSizeChoice>0) {
         settings.addValue(flexNvmPartitionSizeKey,   flexNvmPartitionValues[flexNvmPartitionIndex].backingStore);
      }
   }
#endif
#if !defined(LEGACY)
   for(int index=0; index<maxSecurityNum; index++) {
      if (customSecurityInfoPtr[index] != NULL) {
         Logging::print("customSecurityInfoPtr[%d] => %s\n", index, (const char *)customSecurityInfoPtr[index]->toString().c_str());
         settings.addValue(customSecurityValueKey+'.'+(char)('0'+index),     customSecurityInfoPtr[index]->getSecurityInfo());
      }
   }
#endif
}

//
//! Make device consistent with internal state
//!
bool AdvancedPanel::updateState() {
   Logging log("AdvancedPanel::updateState");

   bool ok = true;
   ok = ok && TransferDataToWindow();
   ok = ok && TransferDataFromWindow();
   if (!ok) {
      return false;
   }
   return true;
}

bool AdvancedPanel::TransferDataToWindow() {
   LOGGING;
   updateFlashNVM();
#if !defined(LEGACY)
   populateSecurityControl();
   updateSecurity();
#endif
   return wxPanel::TransferDataToWindow();
}

bool AdvancedPanel::TransferDataFromWindow() {
   LOGGING;
   bool ok = wxPanel::TransferDataFromWindow();

#if defined(FLASH_PROGRAMMER)
   DeviceData::FlexNVMParameters flexParameters; // Default value for no parameters
   FlexNVMInfoConstPtr flexNVMInfo = currentDevice->getflexNVMInfo();
   if (flexNVMInfo != NULL) {
      const vector<FlexNVMInfo::EeepromSizeValue>      &eeepromSizeValues(flexNVMInfo->getEeepromSizeValues());
      const vector<FlexNVMInfo::FlexNvmPartitionValue> &flexNvmPartitionValues(flexNVMInfo->getFlexNvmPartitionValues());
      flexParameters.eeepromSize  = eeepromSizeValues[eeepromSizeChoice].value;
      flexParameters.partionValue = flexNvmPartitionValues[flexNvmPartitionIndex].value;
   }
   currentDevice->setFlexNVMParameters(flexParameters);
#endif

#if !defined(LEGACY)
   if (currentDevice->getSecurity() == SEC_CUSTOM) {
      Logging::print("SEC_CUSTOM\n");
      // Transfer custom security setting to device
      for(unsigned index=0; index<securityMemoryRegionChoice->GetCount(); index++) {
         int memoryIndex = (int)(intptr_t)securityMemoryRegionChoice->GetClientData(index);
         Logging::print("memoryIndex = %d\n", memoryIndex);
         MemoryRegionPtr memoryRegionPtr = currentDevice->getMemoryRegion(memoryIndex);
         if (memoryRegionPtr == NULL) {
            // No matching memory region!
            throw MyException("AdvancedPanel::getDeviceOptions()- No matching memory region");
         }
         SecurityEntryPtr securityEntry = memoryRegionPtr->getSecurityEntry();
         if (securityEntry == NULL) {
            // Memory region has no security region - skip
            continue;
         }
         if (customSecurityInfoPtr[index] == NULL) {
            // No Custom data for memory region!
            // Need to update this page
            wxMessageBox(
                        _("Inconsistent settings on  Advanced page\n"
                          "Please check before proceeding."),
                        _("Parameter Error"),
                        wxOK,
                        this);
            return false;
         }
         Logging::print("Copying Custom[%d] to Device memoryIndex[%d], %s\n", index, memoryIndex, (const char *)customSecurityInfoPtr[index]->toString().c_str());
         securityEntry->setCustomSecureInformation(customSecurityInfoPtr[index]);
      }
   }
#endif

   // Other internal state is maintained by validators

   return ok;
}

//void AdvancedPanel::setCurrentDevice(DeviceData *currentDevice) {
//   Logging log("AdvancedPanel::setCurrentDevice");
////   this->currentDevice = currentDevice;
//   updateFlashNVM();
//   updateSecurity();
//}
