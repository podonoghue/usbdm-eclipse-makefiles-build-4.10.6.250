/*! \file
    \brief Implements USBDM Flash Panel

    FlashPanel.cpp

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
-==============================================================================
| 26 Dec 2012 | 4.10.4  Fixed file change check if file has been deleted  - pgo
|  4 Nov 2012 | 4.10.4  Fixed filer for file extensions to load           - pgo
|  4 May 2012 | 4.7.5   More robust error checking                        - pgo
|    Apr 2012 | 4.7.4   Added Load if changed option                      - pgo
|  4 Oct 2011 | 4.7.4   Added Extended options                            - pgo
|  4 Apr 2012 | 4.7.4   Added Load & Go                                   - pgo
|  6 Feb 2011 | Added sound effects + options                             - pgo
|  1 Feb 2011 | Modified confirmation prompt to allow chain programming   - pgo
|  1 Jul 2010 | wxWidgets version created                                 - pgo
+==============================================================================
\endverbatim
 */

// For compilers that support precompilation, includes <wx/wx.h".
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <string>

#include <wx/imaglist.h>
#include <wx/gbsizer.h>
#include <wx/stattext.h>

#include "Common.h"
#include "Version.h"
#include "USBDMDialogue.h"
#include "FlashPanel.h"
#include "USBDM_API.h"
#include "USBDM_AUX.h"
#include "Names.h"
#include "ApplicationFiles.h"
#include "Log.h"
#include "FlashImage.h"
#include "FlashImage.h"
#if TARGET == MC56F80xx
#include "USBDM_DSC_API.h"
#endif

#define MASS_ERASE_NEVER     0
#define MASS_ERASE_OPTIONAL  1
#define MASS_ERASE_ALWAYS    2

#if (TARGET == CFVx) || (TARGET == MC56F80xx)
#define MASS_ERASE (MASS_ERASE_NEVER)
#elif (TARGET==ARM) || (TARGET == CFV1) || (TARGET == HC12) || (TARGET == HCS08)
#define MASS_ERASE (MASS_ERASE_OPTIONAL)
#else
#define MASS_ERASE (MASS_ERASE_ALWAYS)
#endif

const string FlashPanel::settingsKey("FlashPanel");

static struct {
   const wxString name;
   int            length;
} rootNames[] = {{_("MC9S08"),   sizeof("MC9S08")-1},
                 {_("MC9S12"),   sizeof("MC9S12")-1 },
                 {_("S9S08"),    sizeof("S9S08")-1 },
                 {wxEmptyString, 0},
                };

//! Converts a device name to the form used in the device list combobox
//!
//! @param targetName - name of device e.g. "MC9S08AW16"
//!
//! @return ptr to static buffer containing the converted name e.g. "AW-MC9S08AW16"
//!
static const wxString makeDeviceName(const wxString& targetName) {
int nameIndex;
static wxString buffer;

   for (nameIndex = 0; rootNames[nameIndex].length != 0; nameIndex++) {
      if (targetName.compare(0,rootNames[nameIndex].length,rootNames[nameIndex].name) == 0) {
         buffer = targetName[rootNames[nameIndex].length];
         if (isalpha((int)targetName[rootNames[nameIndex].length+1]))
            buffer += targetName[rootNames[nameIndex].length+1];
         if (isalpha((int)targetName[rootNames[nameIndex].length+2]))
            buffer += targetName[rootNames[nameIndex].length+2];
         buffer += '-';
         buffer += targetName;
//         Logging::print("makeDeviceName(%s), root = %s => %s\n", (const char *)targetName.ToAscii(),
//                (const char *)rootNames[nameIndex].name.ToAscii(), (const char *)buffer.ToAscii());
         return buffer;
      }
   }
//   Logging::print("makeDeviceName(%s) => %s\n", targetName - unchanged);
   return targetName; // Return unchanged
}

//! Populates the clock drop-down box with known clock types
//!
void FlashPanel::populateClockDropDown(void) {

   int sub;
   int index;

   // Logging::print("FlashPanel::populateClockDropDown()\n");

   // Populate the list
   for (sub=0; ClockTypes::getClockName((ClockTypes_t)sub) != ""; sub++) {
      index = clockModuleTypeChoiceControl->Append(wxString(ClockTypes::getClockName((ClockTypes_t)sub).c_str(), wxConvUTF8));
      if (index>=0) {
         clockModuleTypeChoiceControl->SetClientData(index, (void *)sub);
      }
   }
   // Select 1st item
   clockModuleTypeChoiceControl->SetSelection(0);
}

//! Populates the device drop-down box with known devices
//!
//! @note: the list may be filtered by filterChipIds
//!
void FlashPanel::populateDeviceDropDown() {
   Logging log("FlashPanel()::populateDeviceDropDown");

   // Clear device list
   deviceTypeChoiceControl->Clear();

   // Populate the list with filtered items
   int firstAddedDeviceIndex       = -1;
   int previousDeviceControlIndex  = -1;
   vector<DeviceDataPtr>::const_iterator it;
   int deviceIndex;
   for ( it=deviceDatabase->begin(), deviceIndex=0;
         it < deviceDatabase->end(); it++, deviceIndex++ ) {
      if (((*it)->getTargetName().length() != 0) &&
          !((*it)->isHidden()) &&
          (!doFilterByChipId || (*it)->isThisDevice(filterChipIds, false))) {
//         Logging::print("Adding device %s\n", (*it)->getTargetName().c_str());
         int controlIndex = deviceTypeChoiceControl->Append(makeDeviceName(wxString((*it)->getTargetName().c_str(), wxConvUTF8)));
         if (controlIndex>=0) {
            // Associate index value with item
            deviceTypeChoiceControl->SetClientData(controlIndex, (void *) deviceIndex);
//            Logging::print("FlashPanel::populateDeviceDropDown() - Add device %s @%d, devIndex=%d\n", (*it)->getTargetName().c_str(), controlIndex, deviceIndex);
            if (firstAddedDeviceIndex == -1) {
               firstAddedDeviceIndex = deviceIndex;
            }
            if (deviceIndex == currentDeviceIndex) {
               previousDeviceControlIndex = controlIndex;
            }
         }
         else {
            Logging::print("Add device failed, rc = %d\n", controlIndex);
         }
      }
   }
   if (firstAddedDeviceIndex<0) {
      // No devices added
      Logging::print("No devices\n");
      setDeviceindex(-1);
      deviceTypeChoiceControl->Append(_("[No matching device]"));
      deviceTypeChoiceControl->SetClientData(0, (void *) -22);
      deviceTypeChoiceControl->SetSelection(0);
      deviceTypeChoiceControl->Enable(false);
   }
   else if (previousDeviceControlIndex>=0) {
      // Select originally selected device in list control
      Logging::print("Selecting previous device #%d\n", previousDeviceControlIndex);
      setDeviceindex(currentDeviceIndex);
      deviceTypeChoiceControl->Enable(true);
   }
   else {
      // Select 1st added device in list control
      Logging::print("Selecting 1st added device\n");
      setDeviceindex(firstAddedDeviceIndex);
      deviceTypeChoiceControl->Enable(true);
   }
}

//! Updates internal state to selected device
//!
//! @param newDeviceIndex - index of device in deviceDatabase to select (or -1 for default)
//!
void FlashPanel::setDeviceindex(int newDeviceIndex) {
   Logging log("FlashPanel::setDeviceindex()");

   Logging::print("newDeviceIndex = %d\n", newDeviceIndex);
   Logging::print("Trim Freq (before change)= %f kHz\n", currentDevice->getClockTrimFreq()/1000.0);

   // Save non-device-specific settings.
   DeviceData savedDevice = *currentDevice;
   if (newDeviceIndex<0) {
      currentDevice->shallowCopy(*deviceDatabase->getDefaultDevice());
   }
   else if (newDeviceIndex != currentDeviceIndex) {
      currentDevice->shallowCopy((*deviceDatabase)[newDeviceIndex]);
      if (currentDevice->isAlias()) {
         // Keep device name & SDIDs but update device details from real device
         string aliasedName = currentDevice->getTargetName();
         const std::vector<uint32_t> targetSDIDs = currentDevice->getTargetSDIDs();
         currentDevice->shallowCopy(*deviceDatabase->findDeviceFromName(aliasedName));
         Logging::print("devIndex=%d, aliased(%s) => %s\n",
               newDeviceIndex, (const char *)aliasedName.c_str(), (const char *)currentDevice->getTargetName().c_str());
         currentDevice->setTargetName(aliasedName);
         currentDevice->setTargetSDIDs(targetSDIDs);
      }
   }
   Logging::print("Trim Freq (after change)= %f kHz\n", currentDevice->getClockTrimFreq()/1000.0);
   currentDeviceIndex = newDeviceIndex;

   // Restore non-device-specific settings.
   currentDevice->setSecurity(savedDevice.getSecurity());
   currentDevice->setEraseOption(savedDevice.getEraseOption());
   currentDevice->setConnectionFreq(savedDevice.getConnectionFreq());
   if (!doTrim) {
      currentDevice->setClockTrimFreq(0);
   }
}

#if TARGET == HCS12
//! Special handling for HCS12
//!
USBDM_ErrorCode FlashPanel::hcs12Check(void) {
   USBDM_ErrorCode rc;
   USBDM_ErrorCode rc_flash;
   unsigned long connectionFrequency;
   USBDMStatus_t usbdmStatus;

   // Assume we can auto-detect connection speed
   needManualFrequencySet = false;
   currentDevice->setConnectionFreq(0);
   busFrequencyTextControl->Enable(false);

   flashprogrammer->setDeviceData(*currentDevice);
   rc_flash = flashprogrammer->resetAndConnectTarget();
   if ((rc_flash != PROGRAMMING_RC_OK) && (rc_flash != PROGRAMMING_RC_ERROR_SECURED)) {
      return BDM_RC_FAIL;
   }
   // Get connection speed
   rc = USBDM_GetSpeedHz(&connectionFrequency);
   if (rc != BDM_RC_OK) {
      return rc;
   }
   rc = USBDM_GetBDMStatus(&usbdmStatus);
   if (rc != BDM_RC_OK) {
      return rc;
   }
   // Round to 10's kHz
   connectionFrequency = 10000*round(connectionFrequency/10000.0);
   currentDevice->setConnectionFreq(connectionFrequency);

   if (flashprogrammer->checkTargetUnSecured() == PROGRAMMING_RC_ERROR_SECURED) {
      if (usbdmStatus.connection_state == SPEED_SYNC) {
         // Assume device secure but connection speed has been determined correctly
         rc = BDM_RC_OK;
      }
      else if (usbdmStatus.connection_state == SPEED_GUESSED) {
         // Target speed has been guessed and may be inaccurate.
         // Device is secured so target timing code cannot be used (later).
         // Warn the user to manually set the speed to allow unsecure
         Logging::print("FlashPanel::autoDetectTargetDevice() - Guessed connection speed (Hz) = %d\n", connectionFrequency);
         needManualFrequencySet = true;
         TransferDataToWindow();
         wxMessageBox(
               _("The device appears to be secured and does not support SYNC.\n"
                 "The currently set bus frequency is an approximation and\n"
                 "may not be sufficiently accurate for unsecuring the target.\n\n"
                 "Please manually set the bus frequency before programming."),
               _("Programming Error"),
               wxOK|wxICON_INFORMATION|wxSTAY_ON_TOP|wxCENTER,
               this);
      rc = BDM_RC_OK;
      }
   }
   return rc;
}
#endif

wxProgressDialog *FlashPanel::progressDialogue = NULL;

extern "C"
USBDM_ErrorCode FlashPanel::progressCallBack(USBDM_ErrorCode status, int percent, const char *message) {
   if (progressDialogue == NULL)
      return status;
   if (percent >= 100)
      percent = 99;
   if (message != NULL) {
      wxString msg(message, wxConvUTF8);
      if (percent < 0) {
         progressDialogue->Pulse(msg);
      }
      else {
         progressDialogue->Update(percent, msg);
      }
   }
   else {
      if (percent < 0) {
         progressDialogue->Pulse();
      }
      else {
         progressDialogue->Update(percent);
      }
   }
   return status;
}

//! Auto detect connected device and connection speed
//!
//! @return various error codes
//!
//! @note Any errors are flagged to the user
//!
USBDM_ErrorCode FlashPanel::autoDetectTargetDevice(void) {
uint32_t targetChipId;
USBDM_ErrorCode flashRc;
USBDM_ErrorCode lastRc = PROGRAMMING_RC_OK;

   Logging::print("FlashPanel::autoDetectTargetDevice()\n");

   if (flashprogrammer == NULL) {
      flashprogrammer = new FlashProgrammer;
   }
   filterChipIds.clear();
//   Logging::print("FlashPanel::autoDetectTargetDevice()#A\n");
   Logging::print("FlashPanel::autoDetectTargetDevice() =>\n");
   printBdmOptions(&bdmOptions);

   if (USBDM_SetOptionsWithRetry(&bdmOptions) != BDM_RC_OK) {
      return PROGRAMMING_RC_ERROR_BDM_TARGET;
   }
   if (USBDM_SetTargetTypeWithRetry(targetType) != BDM_RC_OK) {
      return PROGRAMMING_RC_ERROR_BDM_OPEN;
   }
//   Logging::print("FlashPanel::autoDetectTargetDevice()\n");
#if TARGET == HCS12
   // HCS12 has problems if the target is secured and doesn't support SYNC
   USBDM_ErrorCode rc = hcs12Check();
//   Logging::print("FlashPanel::autoDetectTargetDevice()#D\n");
   if (rc != BDM_RC_OK) {
      wxMessageBox(
            _("Failed to connect to target\n\n"
              "Reason: ") +
              wxString(USBDM_GetErrorString(rc), wxConvUTF8),
            _("Programming Error"),
            wxOK|wxICON_ERROR|wxSTAY_ON_TOP|wxCENTER,
            this);
      USBDM_SetTargetType(T_OFF);
      Logging::print("FlashPanel::autoDetectTargetDevice() - Failed to connect to target\n");
      return PROGRAMMING_RC_ERROR_BDM_CONNECT;
   }
#elif TARGET == MC56F80xx
   if (DSC_Initialise() != BDM_RC_OK) {
      USBDM_SetTargetType(T_OFF);
      return PROGRAMMING_RC_ERROR_BDM_CONNECT;
   }
//   Logging::print("FlashPanel::autoDetectTargetDevice()\n");
#elif TARGET == ARM
   USBDM_ErrorCode rc = USBDM_TargetConnectWithRetry((RetryMode)(retryByReset|retryNotPartial));
   if ((rc != BDM_RC_OK) && (rc != BDM_RC_SECURED)) {
      USBDM_SetTargetType(T_OFF);
      return rc;
   }
#else
   if (USBDM_TargetConnectWithRetry((RetryMode)(retryAlways|retryByReset)) != BDM_RC_OK) {
      USBDM_SetTargetType(T_OFF);
      return PROGRAMMING_RC_ERROR_BDM_CONNECT;
   }
#endif
//   USBDM_TargetHalt();

#if (TARGET == CFV1) || (TARGET == ARM)
   flashRc = flashprogrammer->setDeviceData(*deviceDatabase->getDefaultDevice());
   if (flashRc != PROGRAMMING_RC_OK) {
      USBDM_SetTargetType(T_OFF);
      Logging::print("FlashPanel::autoDetectTargetDevice() - setDeviceData() failed\n");
      return flashRc;
   }
   // CFV1 is a bit unusual in that you can't determine the device type of a secured device.
   flashRc = flashprogrammer->checkTargetUnSecured();
   if (flashRc == PROGRAMMING_RC_ERROR_SECURED) {
      int getYesNo = wxMessageBox(_("It is not possible to determine the device type \n"
                                    "as it appears to be secured.\n\n"
                                    "It is necessary to unsecure the device to allow the Chip ID\n"
                                    "to be read and the device re-programmed.\n"
                                    "Unsecuring the device will entirely erase its contents.\n\n"
                                    "Unsecure & entirely erase the device ?"),
                                  _("Device is Secured"),
                                  wxYES_NO|wxNO_DEFAULT|wxSTAY_ON_TOP|wxCENTER,
                                  this);
      if (getYesNo != wxYES) {
         USBDM_SetTargetType(T_OFF);
         return flashRc;
      }
      flashRc = flashprogrammer->massEraseTarget();
      if (flashRc != PROGRAMMING_RC_OK) {
         wxMessageBox(_("Unsecuring the device failed.\n"
                        "Reason: ") +
                        wxString(USBDM_GetErrorString(flashRc), wxConvUTF8),
                      _("Erasing Failed"),
                      wxOK|wxICON_ERROR|wxSTAY_ON_TOP|wxCENTER,
                      this);
         USBDM_SetTargetType(T_OFF);
         return flashRc;
      }
   }
   else if (flashRc != PROGRAMMING_RC_OK) {
      USBDM_SetTargetType(T_OFF);
      return flashRc;
   }
#endif
//   Logging::print("FlashPanel::autoDetectTargetDevice(): Here #1\n");
   // To reduce time keep a history of probed locations for re-use
   vector<DeviceDataPtr>::const_iterator deviceIterator;
   for ( deviceIterator = deviceDatabase->begin();
         deviceIterator < deviceDatabase->end();
         deviceIterator++ ) {
//      Logging::print("FlashPanel::autoDetectTargetDevice(): Considering %s\n", (*deviceIterator)->getTargetName().c_str());
//      Logging::print("FlashPanel::autoDetectTargetDevice() Checking device %s\n", (*deviceIterator)->getTargetName().c_str());
//      Logging::print("FlashPanel::autoDetectTargetDevice() Checking device Chip ID=0x%X, IDAddress=0x%X\n",
//           (*deviceIterator)->getSDID(0),(*deviceIterator)->getSDIDAddress());
      if ((*deviceIterator)->getSDIDAddress() == 0x0000) {
         continue; // Skip 'match any device'
      }
//      Logging::print("FlashPanel::autoDetectTargetDevice(): Checking %s\n", (*deviceIterator)->getTargetName().c_str());
      map<uint32_t,uint32_t>::iterator chipIdEntry;
      // Check if already probed location
      chipIdEntry = filterChipIds.find((*deviceIterator)->getSDIDAddress());
      if (chipIdEntry == filterChipIds.end()) {
         // Add new entry - if successfully probed
         flashRc = flashprogrammer->setDeviceData(**deviceIterator);
         if (flashRc == PROGRAMMING_RC_OK) {
#if (TARGET == ARM)
            flashRc = flashprogrammer->readTargetChipId(&targetChipId, true);
#else
            flashRc = flashprogrammer->readTargetChipId(&targetChipId, false);
#endif
         }
         if (flashRc != PROGRAMMING_RC_OK) {
            // Ignore errors as may be accessing illegal memory
            lastRc = flashRc;
            Logging::print("FlashPanel::autoDetectTargetDevice() - Failed to read chip ID from target, Reason: %s\n",
                   USBDM_GetErrorString(flashRc));
            continue;
         }
         filterChipIds.insert ( pair<uint32_t,uint32_t>((*deviceIterator)->getSDIDAddress(), targetChipId) );
//         Logging::print("FlashPanel::autoDetectTargetDevice() - Added chip ID entry (A=0x%6.6X, V=0x%8.8X)\n",
//               (*deviceIterator)->getSDIDAddress(),
//               targetChipId);
      }
   }
//   Logging::print("FlashPanel::autoDetectTargetDevice(): Here #2\n");
   USBDM_SetTargetType(T_OFF);

   if (filterChipIds.empty()) {
      Logging::print("FlashPanel::autoDetectTargetDevice() - Failed to read any chip IDs from target\n");
      if (lastRc != PROGRAMMING_RC_OK) {
       wxMessageBox(
             _("Failed to read any ChipIds from target\n"
               "Reason: ") +
               wxString(USBDM_GetErrorString(lastRc), wxConvUTF8),
                 _("Error"),
                 wxOK|wxSTAY_ON_TOP|wxCENTER,
                 this);
      }
      else {
       wxMessageBox(
             _("Failed to read any Chip IDs from target"),
                  _("Error"),
                  wxOK|wxSTAY_ON_TOP|wxCENTER,
                  this);
      }
   }
   else {
      Logging::print("FlashPanel::autoDetectTargetDevice() - Found %d chips\n", filterChipIds.size());
   }
   return PROGRAMMING_RC_OK;
}

//========================================================================================================================
// FlashPanel

FlashPanel::FlashPanel( wxWindow* parent, Shared *shared, TargetType_t targetType, HardwareCapabilities_t bdmCapabilities) :
      shared(shared),
      bdmOptions(shared->getBdmOptions()),
      currentDevice(shared->getCurrentDevice()),
      currentDeviceIndex(-1),
      deviceDatabase(shared->getDeviceDataBase()),
      targetType(targetType),
      bdmCapabilities(bdmCapabilities),
      flashprogrammer(NULL),
      beep(0)   {
   Logging log("FlashPanel::FlashPanel");
   Init();
   Create(parent);
}

//FlashPanel::FlashPanel(TargetType_t targetType, HardwareCapabilities_t bdmCapabilities) :
//      deviceDatabase(NULL),
//      targetType(targetType),
//      bdmCapabilities(bdmCapabilities),
//      flashprogrammer(NULL),
//      beep(0)
//   {
//   Init();
//}

bool FlashPanel::Create(wxWindow* parent) {
   Logging log("FlashPanel::Create");

   if (!wxPanel::Create(parent) || !CreateControls()) {
      return false;
   }
   wxString okSoundPath = wxString(getApplicationFilePath("error.wav", "r").c_str(), wxConvUTF7);
   if (okSoundPath != wxEmptyString) {
      beep = new wxSound(okSoundPath);
   }
#ifdef FLASH_PROGRAMMER
   securityRadioBoxControl->SetSelection(0);
   incrementalFileLoadCheckBoxControl->Set3StateValue(wxCHK_UNCHECKED);
#endif
#if TARGET != HCS12
   populateClockDropDown();
#endif
   populateDeviceDropDown();
   return true;
}

//===================================================================
//! Set the panel internal state to the default
//!
void FlashPanel::Init() {
   Logging log("FlashPanel::Init");

   currentDevice->setSecurity(SEC_DEFAULT);
   filterChipIds.clear();
   doFilterByChipId       = false;
   needManualFrequencySet = false;
   incrementalLoad        = false;
   fileLoaded             = false;
   doTrim                 = false;
   sound                  = false;
}

//! Control creation for USBDM Flash programming settings
//!
bool FlashPanel::CreateControls() {
   Logging log("FlashPanel::CreateControls");

   wxStaticText*     itemStaticText;
   wxStaticBox*      itemStaticBox;
   wxStaticBoxSizer* itemStaticBoxSizer;
   wxBoxSizer*       itemBoxSizer;
   wxGridBagSizer*   gridBagSizer;

   wxPanel*    panel = this;
   wxBoxSizer* panelBoxSizerV = new wxBoxSizer(wxVERTICAL);
   panel->SetSizer(panelBoxSizerV);

   const int borderWidth = 3;

   //======================================================================
#ifdef FLASH_PROGRAMMER
   itemStaticBox = new wxStaticBox(panel, wxID_ANY, _("Flash Image Buffer"));
   itemStaticBoxSizer = new wxStaticBoxSizer(itemStaticBox, wxVERTICAL);
   panelBoxSizerV->Add(itemStaticBoxSizer, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, borderWidth);

   //------------------------------------------------------------------------
   itemBoxSizer = new wxBoxSizer(wxHORIZONTAL);
   itemStaticBoxSizer->Add(itemBoxSizer, 0, wxALIGN_CENTER_VERTICAL|wxALL, 0);

   loadFileButtonControl = new wxButton( panel, ID_LOAD_FILE_BUTTON, _("&Load Hex Files"), wxDefaultPosition, wxDefaultSize, 0 );
   itemBoxSizer->Add(loadFileButtonControl, 0, wxALIGN_CENTER_VERTICAL|wxALL, borderWidth);

   incrementalFileLoadCheckBoxControl = new wxCheckBox( panel, ID_INCREMENTAL_FILE_LOAD_CHECKBOX, _("Incremental Load"), wxDefaultPosition, wxDefaultSize, 0 );
   incrementalFileLoadCheckBoxControl->SetValue(false);
   incrementalFileLoadCheckBoxControl->SetToolTip(_("Load new file without clearing buffer"));
   itemBoxSizer->Add(incrementalFileLoadCheckBoxControl, 0, wxALIGN_LEFT|wxALIGN_CENTRE_VERTICAL|wxLEFT|wxRIGHT|wxTOP, borderWidth);


   autoFileReloadCheckBoxControl = new wxCheckBox( panel, ID_AUTO_FILE_RELOAD_CHECKBOX, _("Auto Reload"), wxDefaultPosition, wxDefaultSize, 0 );
   autoFileReloadCheckBoxControl->SetToolTip(_("Reload changed file quietly."));
   autoFileReloadCheckBoxControl->SetValue(false);
   autoFileReloadCheckBoxControl->SetToolTip(_("Reload file before programming if it has changed."));
   itemBoxSizer->Add(autoFileReloadCheckBoxControl, 0, wxALIGN_LEFT|wxALIGN_CENTRE_VERTICAL|wxLEFT|wxRIGHT|wxTOP, borderWidth);

   loadedFilenameStaticControl = new wxStaticText( panel, wxID_STATIC, _("No File Loaded"), wxDefaultPosition, wxDefaultSize, 0 );
   itemStaticBoxSizer->Add(loadedFilenameStaticControl, 0, wxALIGN_LEFT|wxLEFT|wxRIGHT, 10);
#endif

   //======================================================================

   itemStaticBox = new wxStaticBox(panel, wxID_ANY, _("Device Selection"));
   itemStaticBoxSizer = new wxStaticBoxSizer(itemStaticBox, wxHORIZONTAL);
   panelBoxSizerV->Add(itemStaticBoxSizer, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, borderWidth);

   //------------------------------------------------------------------------
   wxFlexGridSizer *flexGridSizer = new wxFlexGridSizer(0,2,0,0);
//   flexGridSizer->SetFlexibleDirection(wxHORIZONTAL);
//   flexGridSizer->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_NONE);
   itemStaticBoxSizer->Add(flexGridSizer, 1, wxALIGN_CENTER_VERTICAL|wxALL, 0);

   deviceTypeChoiceControl = new wxChoice(panel, ID_DEVICE_TYPE_CHOICE, wxDefaultPosition, wxSize(220,-1), 0, NULL, 0); //wxDefaultSize);
//   deviceTypeChoiceControl = new wxComboBox(panel, ID_DEVICE_TYPE_CHOICE, _("Select Device"), wxDefaultPosition, wxSize(180,-1), 0, NULL, wxCB_READONLY); //wxDefaultSize);
   flexGridSizer->Add(deviceTypeChoiceControl, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND|wxALL, borderWidth);

#ifdef FLASH_PROGRAMMER
   detectChipButtonControl = new wxButton( panel, ID_DETECT_CHIP_ID_BUTTON, _("&Detect Chip"), wxDefaultPosition, wxDefaultSize, 0 );
   detectChipButtonControl->SetToolTip(_("Query target chip ID."));
   flexGridSizer->Add(detectChipButtonControl, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND|wxALL, borderWidth);

   filterByChipIdCheckBoxControl = new wxCheckBox( panel, ID_FILTER_BY_CHIP_ID_CHECKBOX, _("Filter by chip ID"), wxDefaultPosition, wxDefaultSize, 0 );
   filterByChipIdCheckBoxControl->SetToolTip(_("Restrict displayed chips to those matching chip ID."));
   filterByChipIdCheckBoxControl->SetValue(false);
   filterByChipIdCheckBoxControl->Enable(false);
   flexGridSizer->Add(filterByChipIdCheckBoxControl, 0, wxALIGN_CENTER_VERTICAL|wxEXPAND|wxLEFT|wxRIGHT|wxTOP, borderWidth);
#endif

#if TARGET == HCS12
   //======================================================================

   itemStaticBox = new wxStaticBox(panel, wxID_ANY, _("Options for secured devices without SYNC"));
   itemStaticBoxSizer = new wxStaticBoxSizer(itemStaticBox, wxHORIZONTAL);
   panelBoxSizerV->Add(itemStaticBoxSizer, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, borderWidth);

   //------------------------------------------------------------------------
   itemStaticText = new wxStaticText( panel, wxID_STATIC, _("Bus Frequency (Crystal/2)"), wxDefaultPosition, wxDefaultSize, 0 );
   itemStaticBoxSizer->Add(itemStaticText, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, borderWidth);

   busFrequencyTextControl = new NumberTextEditCtrl( panel, ID_BUS_FREQ_TEXT, wxEmptyString, wxDefaultPosition, wxSize(80, -1), 0 );
   itemStaticBoxSizer->Add(busFrequencyTextControl, 0, wxALIGN_CENTER_VERTICAL|wxALL, borderWidth);
   busFrequencyTextControl->Enable(false);

   itemStaticText = new wxStaticText( panel, wxID_STATIC, _("kHz"), wxDefaultPosition, wxDefaultSize, 0 );
   itemStaticBoxSizer->Add(itemStaticText, 0, wxALIGN_CENTER_VERTICAL|wxALL, borderWidth);
#endif

#if TARGET != HCS12
   //====================================================================

   itemStaticBox = new wxStaticBox(panel, wxID_ANY, _("Clock type and parameters"));
   itemStaticBoxSizer = new wxStaticBoxSizer(itemStaticBox, wxHORIZONTAL);
   panelBoxSizerV->Add(itemStaticBoxSizer, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, borderWidth);

   //------------------------------------------------------------------------
   gridBagSizer = new wxGridBagSizer(0,0);
   itemStaticBoxSizer->Add(gridBagSizer, 0, wxEXPAND|wxALL, 0);

   //------------------------------------------------------------------------
   itemStaticText = new wxStaticText( panel, wxID_STATIC, _("Clock Module"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(itemStaticText, wxGBPosition(0,0), wxGBSpan(1,2), wxLEFT|wxRIGHT|wxTOP, borderWidth);

   clockModuleTypeChoiceControl = new wxChoice( panel, ID_CLOCK_MODULE_TYPE_CHOICE, wxDefaultPosition, wxSize(150, -1));
   gridBagSizer->Add(clockModuleTypeChoiceControl, wxGBPosition(1,0), wxGBSpan(1,2), wxLEFT|wxTOP, borderWidth);
   clockModuleTypeChoiceControl->Enable(false);

   clockModuleAddressStaticControl = new wxStaticText( panel, wxID_STATIC, _("&Clock Module Address"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(clockModuleAddressStaticControl, wxGBPosition(2,0), wxGBSpan(1,3),  wxLEFT|wxRIGHT|wxTOP, borderWidth);

   clockModuleAddressTextControl = new NumberTextEditCtrl( panel, ID_CLOCK_MODULE_ADDRESS_TEXT, wxEmptyString, wxDefaultPosition, wxSize(80, -1), 0 );
   gridBagSizer->Add(clockModuleAddressTextControl, wxGBPosition(3,0), wxGBSpan(1,1), wxLEFT|wxTOP, borderWidth);
   clockModuleAddressTextControl->Enable(false);

   itemStaticText = new wxStaticText( panel, wxID_STATIC, _("(hex)"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(itemStaticText, wxGBPosition(3,1), wxGBSpan(1,1), wxLEFT|wxTOP|wxALIGN_LEFT|wxALIGN_CENTRE_VERTICAL, borderWidth);

   //------------------------------------------------------------------------
   trimFrequencyStaticControl = new wxStaticText( panel, wxID_STATIC, _("&Trim Frequency"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(trimFrequencyStaticControl, wxGBPosition(0,4), wxGBSpan(1,2), wxALIGN_LEFT|wxRIGHT|wxTOP, borderWidth);

   trimFrequencyCheckBoxControl = new wxCheckBox( panel, ID_TRIM_FREQUENCY_CHECKBOX, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT|wxCHK_2STATE );
   trimFrequencyCheckBoxControl->SetValue(false);
   gridBagSizer->Add(trimFrequencyCheckBoxControl, wxGBPosition(1,2), wxGBSpan(1,2), wxALL|wxALIGN_RIGHT|wxALIGN_CENTRE_VERTICAL, borderWidth);

   trimFrequencyTextControl = new NumberTextEditCtrl( panel, ID_TRIM_FREQUENCY_TEXT, wxEmptyString, wxDefaultPosition, wxSize(80, -1), 0 );
   trimFrequencyTextControl->SetToolTip(_("Frequency to trim the internal clock to\nNot the bus frequency"));
   gridBagSizer->Add(trimFrequencyTextControl, wxGBPosition(1,4), wxGBSpan(1,1), wxRIGHT|wxTOP|wxBOTTOM|wxALIGN_LEFT, borderWidth);

   itemStaticText = new wxStaticText( panel, wxID_STATIC, _("kHz"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(itemStaticText, wxGBPosition(1,5), wxGBSpan(1,1), wxALIGN_LEFT|wxALIGN_CENTRE_VERTICAL, borderWidth);

   trimAddressStaticControl = new wxStaticText( panel, wxID_STATIC, _("&NVTRIM Address"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(trimAddressStaticControl, wxGBPosition(2,4), wxGBSpan(1,2), wxRIGHT|wxTOP|wxALIGN_LEFT, borderWidth);

   trimAddressTextControl = new NumberTextEditCtrl( panel, ID_NONVOLATILE_ADDRESS_TEXT, wxEmptyString, wxDefaultPosition, wxSize(80, -1), 0 );
   trimAddressTextControl->SetToolTip(_("Flash address to program trim values to."));
   gridBagSizer->Add(trimAddressTextControl, wxGBPosition(3,4), wxGBSpan(1,1), wxRIGHT|wxTOP|wxALIGN_LEFT, borderWidth);

   itemStaticText = new wxStaticText( panel, wxID_STATIC, _("(hex)"), wxDefaultPosition, wxDefaultSize, 0 );
   gridBagSizer->Add(itemStaticText, wxGBPosition(3,5), wxGBSpan(1,1), wxTOP|wxALIGN_LEFT|wxALIGN_CENTRE_VERTICAL, borderWidth);
#endif

#ifdef FLASH_PROGRAMMER
   //====================================================================
   wxArrayString securityRadioBoxControlStrings;
   securityRadioBoxControlStrings.Add(_("&Image"));
   securityRadioBoxControlStrings.Add(_("&Secure"));
   securityRadioBoxControlStrings.Add(_("&Unsecure"));
   securityRadioBoxControlStrings.Add(_("S&mart"));
   securityRadioBoxControl = new wxRadioBox( panel, ID_SECURITY_RADIOBOX, _("Security"), wxDefaultPosition, wxDefaultSize, securityRadioBoxControlStrings, 1, wxRA_SPECIFY_ROWS );
   securityRadioBoxControl->SetSelection(0);
   securityRadioBoxControl->SetToolTip(_("Security state after programming:\n"
                                         "Image   \t\t- whatever the flash image contains\n"
                                         "Secure  \t\t- the device will be secured\n"
                                         "Unsecure\t- the device will be unsecured\n"
                                         "Smart   \t\t- set unsecured if security area in image is unprogrammed\n"
                                         "Disabled\t-value is set on Advanced tab"));
   panelBoxSizerV->Add(securityRadioBoxControl, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, borderWidth);

   //====================================================================
   itemStaticBox = new wxStaticBox(panel, wxID_ANY, _("Device Operations"));
   itemStaticBoxSizer = new wxStaticBoxSizer(itemStaticBox, wxHORIZONTAL);
   panelBoxSizerV->Add(itemStaticBoxSizer, 0, wxEXPAND|wxLEFT|wxRIGHT|wxTOP, borderWidth);

   //------------------------------------------------------------------------
   gridBagSizer = new wxGridBagSizer(borderWidth,0);
   itemStaticBoxSizer->Add(gridBagSizer, wxEXPAND|wxALL);

   itemStaticText = new wxStaticText( panel, wxID_STATIC, _("Erase Options"));
   gridBagSizer->Add(itemStaticText, wxGBPosition(0,0), wxGBSpan(1,1), wxALIGN_LEFT|wxALIGN_BOTTOM|wxLEFT, 10);

   eraseChoiceControl = new wxChoice( panel, ID_ERASE_CHOICE);
   eraseChoiceControl->SetToolTip(_("None      - Don't erase before programming\n"
                                    "Selective - Erase only sectors being programmed\n"
                                    "All       - Erase entire chip\n"
                                    "Mass      - Use device specific mass erase method"));

#if MASS_ERASE == MASS_ERASE_NEVER
   eraseChoiceControl->Append(wxString(DeviceData::getEraseOptionName(DeviceData::eraseNone),wxConvUTF7),      (void*)DeviceData::eraseNone);
   eraseChoiceControl->Append(wxString(DeviceData::getEraseOptionName(DeviceData::eraseSelective),wxConvUTF7), (void*)DeviceData::eraseSelective);
   eraseChoiceControl->Append(wxString(DeviceData::getEraseOptionName(DeviceData::eraseAll),wxConvUTF7),       (void*)DeviceData::eraseAll);
#elif MASS_ERASE == MASS_ERASE_OPTIONAL
   eraseChoiceControl->Append(wxString(DeviceData::getEraseOptionName(DeviceData::eraseNone),wxConvUTF7),      (void*)DeviceData::eraseNone);
   eraseChoiceControl->Append(wxString(DeviceData::getEraseOptionName(DeviceData::eraseSelective),wxConvUTF7), (void*)DeviceData::eraseSelective);
   eraseChoiceControl->Append(wxString(DeviceData::getEraseOptionName(DeviceData::eraseAll),wxConvUTF7),       (void*)DeviceData::eraseAll);
   eraseChoiceControl->Append(wxString(DeviceData::getEraseOptionName(DeviceData::eraseMass),wxConvUTF7),      (void*)DeviceData::eraseMass);
#elif MASS_ERASE == MASS_ERASE_ALWAYS
   eraseChoiceControl->Append(wxString(DeviceData::getEraseOptionName(DeviceData::eraseNone),wxConvUTF7),      (void*)DeviceData::eraseNone);
   eraseChoiceControl->Append(wxString(DeviceData::getEraseOptionName(DeviceData::eraseMass),wxConvUTF7),      (void*)DeviceData::eraseMass);
#endif
   gridBagSizer->Add(eraseChoiceControl, wxGBPosition(1,0), wxGBSpan(1,1), wxALIGN_CENTRE|wxLEFT|wxRIGHT, borderWidth);

   enableSoundsCheckBoxControl = new wxCheckBox( panel, ID_SOUND, _("Enable Sounds"));
   enableSoundsCheckBoxControl->SetValue(false);
   gridBagSizer->Add(enableSoundsCheckBoxControl, wxGBPosition(1,1), wxGBSpan(1,1), wxALIGN_CENTER|wxLEFT|wxRIGHT, borderWidth);

   trimValueStaticControl = new wxStaticText( panel, wxID_STATIC, _("Trim Value: - 0x??.?"));
   trimValueStaticControl->SetToolTip(_("Calculated Trim value (8/9 bit)"));
   gridBagSizer->Add(trimValueStaticControl, wxGBPosition(1,2), wxGBSpan(1,1), wxALIGN_CENTER|wxLEFT|wxRIGHT, borderWidth);

#if (TARGET == HCS12) || (TARGET == CFVx) || (TARGET == ARM) || (TARGET == MC56F80xx)
   trimValueStaticControl->Enable(false);
#endif

   //--------
   programFlashButtonControl = new wxButton( panel, ID_PROGRAM_FLASH_BUTTON, _("&Program Flash") );
   programFlashButtonControl->Enable(false);
   gridBagSizer->Add(programFlashButtonControl, wxGBPosition(2,0), wxGBSpan(1,1), wxEXPAND|wxALL, borderWidth);

   verifyFlashButtonControl = new wxButton( panel, ID_VERIFY_FLASH_BUTTON, _("&Verify Flash") );
   verifyFlashButtonControl->Enable(false);
   gridBagSizer->Add(verifyFlashButtonControl, wxGBPosition(2,1), wxGBSpan(1,1), wxEXPAND|wxALL, borderWidth);

   loadAndGoButtonControl = new wxButton( panel, ID_LOAD_AND_GO_BUTTON, _("Load and &Go") );
   loadAndGoButtonControl->SetToolTip(_("Program Target, Reset and start execution."));
   loadAndGoButtonControl->Enable(false);
   gridBagSizer->Add(loadAndGoButtonControl, wxGBPosition(2,2), wxGBSpan(1,1), wxEXPAND|wxALL, borderWidth);
#endif //FLASH_PROGRAMMER

   return true;
}

//===================================================================
//! Update the dialogue from internal state
//!
bool FlashPanel::TransferDataToWindow() {
   Logging log("FlashPanel::TransferDataToWindow");

//   Logging::print("FlashPanel::TransferDataToWindow() - target = %s, currentDeviceIndex = %d\n",
//         (const char *)makeDeviceName(currentDeviceName).ToAscii(),
//         currentDeviceIndex);
   Logging::print("CurrentDeviceIndex = %d\n", currentDeviceIndex);

   if (currentDeviceIndex < 0) {
      // No valid device selected (control is empty?)
      deviceTypeChoiceControl->SetSelection(0);
   }
   else {
      // Set currently selected device
      wxString deviceName = makeDeviceName(wxString((*deviceDatabase)[currentDeviceIndex].getTargetName().c_str(), wxConvUTF8));
      Logging::print("Setting device \'%s\'\n", (const char *)deviceName.c_str());
      int deviceIndex = currentDeviceIndex;
      if (!deviceTypeChoiceControl->SetStringSelection(deviceName)) {
         // Device not found - change to 1st device
         Logging::print("Device not found (%s), changing to dev #0\n", (const char *)deviceName.c_str());
         deviceIndex = 0;
      }
      setDeviceindex(deviceIndex);
   }
#if TARGET != HCS12
   bool usingClock = (currentDevice->getClockType() != CLKEXT) &&
                     (currentDevice->getClockType() != CLKINVALID);
//   Logging::print("FlashPanel::TransferDataToWindow() - usingClock=%s, getClockType()=%d\n",
//            usingClock?"true":"false",
//                  currentDevice->getClockType()
//            );
   clockModuleAddressStaticControl->Enable(usingClock);
   trimFrequencyCheckBoxControl->Enable(usingClock);

   bool trimEnabled = usingClock && doTrim;

   trimFrequencyStaticControl->Enable(trimEnabled);
   trimFrequencyTextControl->Enable(trimEnabled);
   trimAddressStaticControl->Enable(trimEnabled);
   trimAddressTextControl->Enable(trimEnabled);

   clockModuleTypeChoiceControl->SetStringSelection(wxString(ClockTypes::getClockName(currentDevice->getClockType()).c_str(), wxConvUTF8));

   clockModuleAddressTextControl->SetHexValue(currentDevice->getClockAddress());

   trimFrequencyCheckBoxControl->Set3StateValue(doTrim?wxCHK_CHECKED:wxCHK_UNCHECKED);

   trimFrequencyTextControl->SetDoubleValue(currentDevice->getClockTrimFreq()/1000.0);
   trimAddressTextControl->SetHexValue(currentDevice->getClockTrimNVAddress());
#endif

#ifdef FLASH_PROGRAMMER
   if (filterChipIds.empty()) {
      filterByChipIdCheckBoxControl->SetLabel(_("Filter by chip ID (none)"));
   }
   else {
      // Update displayed Chip IDs
      wxString buff = _("Filter by chip ID (");
      for (map<uint32_t,uint32_t>::const_iterator it = filterChipIds.begin();
            it != filterChipIds.end();
            ++it
            ) {
         char sdidBuffer[20];
         sprintf(sdidBuffer, "%4.4X ", it->second);
         buff.append(wxString(sdidBuffer,wxConvUTF7));
      }
      buff.append(_(")"));
      filterByChipIdCheckBoxControl->SetLabel(buff);
   }
   bool customSelected = currentDevice->getSecurity() == SEC_CUSTOM;
   Logging::print("Setting device security = %s\n", getSecurityName(currentDevice->getSecurity()));
   if (customSelected) {
      securityRadioBoxControl->SetLabel(_("Security - see Advanced tab"));
   }
   else {
      securityRadioBoxControl->SetLabel(_("Security"));
   }
   securityRadioBoxControl->Enable(0, !customSelected);
   securityRadioBoxControl->Enable(1, !customSelected);
   securityRadioBoxControl->Enable(2, !customSelected);
   securityRadioBoxControl->Enable(3, !customSelected);
   switch(currentDevice->getSecurity()) {
      case SEC_DEFAULT:   securityRadioBoxControl->SetSelection(0);  break;
      case SEC_SECURED:   securityRadioBoxControl->SetSelection(1);  break;
      case SEC_UNSECURED: securityRadioBoxControl->SetSelection(2);  break;
      case SEC_SMART:     securityRadioBoxControl->SetSelection(3);  break;
      case SEC_CUSTOM:    break;
   }
   enableSoundsCheckBoxControl->SetValue(sound);
   if (!eraseChoiceControl->SetStringSelection(wxString(DeviceData::getEraseOptionName(currentDevice->getEraseOption()),wxConvUTF7))) {
      // Current erase option not supported - default to 1st item
      eraseChoiceControl->SetSelection(0);
      DeviceData::EraseOptions eraseOption = (DeviceData::EraseOptions)(int)eraseChoiceControl->GetClientData(0);
      currentDevice->setEraseOption(eraseOption);
   }
   autoFileReloadCheckBoxControl->Set3StateValue(autoFileLoad?wxCHK_CHECKED:wxCHK_UNCHECKED);
#endif

#if TARGET == HCS12
   busFrequencyTextControl->SetDecimalValue(round(currentDevice->getConnectionFreq()/1000));
   busFrequencyTextControl->Enable(needManualFrequencySet);
#endif
   updateProgrammingState();
   return true;
}

bool FlashPanel::TransferDataFromWindow() {
//   Logging::print("FlashPanel::TransferDataFromWindow()\n");

#ifdef FLASH_PROGRAMMER
   sound        = enableSoundsCheckBoxControl->IsChecked();
   autoFileLoad = autoFileReloadCheckBoxControl->IsChecked();
#endif
   return true;
}

bool FlashPanel::updateState() {
   Logging log("FlashPanel::updateState");

   bool ok = true;
   ok = ok && TransferDataToWindow();
   ok = ok && TransferDataFromWindow();
   if (!ok) {
      return false;
   }
   if (currentDevice->getClockType() == CLKEXT) {
      currentDevice->setClockTrimNVAddress(0);
      currentDevice->setClockTrimFreq(0);
      currentDevice->setClockAddress(0);
   }
   if (!doTrim) {
      currentDevice->setClockTrimNVAddress(0);
      currentDevice->setClockTrimFreq(0);
   }
#ifdef GDI
   currentDevice->setSecurity(SEC_UNSECURED);
   currentDevice->setConnectionFreq(0);
#endif
   return true;
}

/*
 * FlashPanel type definition
 */
IMPLEMENT_CLASS( FlashPanel, wxPanel )

/*
 * FlashPanel event table definition
 */
BEGIN_EVENT_TABLE( FlashPanel, wxPanel )
   EVT_CHOICE( ID_DEVICE_TYPE_CHOICE,               FlashPanel::OnDeviceTypeChoiceSelected )
   EVT_CHECKBOX( ID_TRIM_FREQUENCY_CHECKBOX,        FlashPanel::OnTrimFrequencyCheckboxClick )
   EVT_TEXT( ID_TRIM_FREQUENCY_TEXT,                FlashPanel::OnTrimFrequencyTextTextUpdated )
   EVT_TEXT( ID_NONVOLATILE_ADDRESS_TEXT,           FlashPanel::OnNonvolatileAddressTextTextUpdated )

#ifdef FLASH_PROGRAMMER
   EVT_BUTTON( ID_LOAD_FILE_BUTTON,                 FlashPanel::OnLoadFileButtonClick )
   EVT_CHECKBOX( ID_INCREMENTAL_FILE_LOAD_CHECKBOX, FlashPanel::OnIncrementalFileLoadCheckboxClick )
   EVT_CHECKBOX( ID_AUTO_FILE_RELOAD_CHECKBOX,      FlashPanel::OnAutoFileReloadCheckboxClick )

   EVT_CHECKBOX( ID_FILTER_BY_CHIP_ID_CHECKBOX,     FlashPanel::OnFilterByChipIdCheckboxClick )
   EVT_BUTTON( ID_DETECT_CHIP_ID_BUTTON,            FlashPanel::OnDetectChipButtonClick )

   EVT_RADIOBOX( ID_SECURITY_RADIOBOX,              FlashPanel::OnSecurityRadioboxSelected )
   EVT_BUTTON( ID_PROGRAM_FLASH_BUTTON,             FlashPanel::OnProgramFlashButtonClick )
   EVT_BUTTON( ID_VERIFY_FLASH_BUTTON,              FlashPanel::OnVerifyFlashButtonClick )
   EVT_BUTTON( ID_LOAD_AND_GO_BUTTON,               FlashPanel::OnLoadAndGoButtonClick )
   EVT_CHOICE( ID_ERASE_CHOICE,                     FlashPanel::OnEraseChoiceSelect )
   EVT_CHECKBOX( ID_SOUND,                          FlashPanel::OnSoundCheckboxClick )
#endif

END_EVENT_TABLE()

#if defined(FLASH_PROGRAMMER)

USBDM_ErrorCode FlashPanel::loadHexFile( wxString hexFilename, bool clearBuffer ) {
   Logging log("FlashPanel::loadHexFile");
   USBDM_ErrorCode rc;

   Logging::print("(%s)\n", (const char *)hexFilename.ToAscii());
   loadedFilenameStaticControl->SetLabel(_("Loading File"));
   rc = flashImageData.loadFile((const char*)hexFilename.mb_str(wxConvUTF8), clearBuffer);
   if (rc != BDM_RC_OK) {
      wxMessageBox(_("Failed to read S-File.\n") +
                     hexFilename +
                   _("\nReason: ") +
                     wxString(USBDM_GetErrorString(rc), wxConvUTF8),
                   _("S-File load error - buffer cleared!"),
                   wxOK|wxSTAY_ON_TOP|wxCENTER,
                   this);
      // Buffer image may be corrupted
      fileLoaded = FALSE;
      flashImageData.initData();
      loadedFilenameStaticControl->SetLabel(_("No file loaded"));
      updateProgrammingState();
      return PROGRAMMING_RC_ERROR_FILE_OPEN_FAIL;
   }
   else {
      fileLoaded = TRUE;
      lastFileLoaded = hexFilename;
      fileLoadTime = wxFileModificationTime(hexFilename);
      loadedFilenameStaticControl->SetLabel(wxFileNameFromPath(hexFilename));
      updateProgrammingState();
   }
   flashImageData.printMemoryMap();
   return PROGRAMMING_RC_OK;
}

//! Check if last loaded file has changed on disk.\n
//! If so then prompt to reload.
//!
USBDM_ErrorCode FlashPanel::checkFileChange(void) {
   LOGGING;
   if (!fileLoaded) {
      Logging::print("No file loaded\n");
      return PROGRAMMING_RC_OK;
   }
   time_t currentFileTime;
   if (!wxFileExists(lastFileLoaded)) {
      Logging::print("File no longer exists\n");
      currentFileTime = -1;
   }
   else {
      currentFileTime = wxFileModificationTime(lastFileLoaded);
   }
   if ((currentFileTime != -1) && (currentFileTime == fileLoadTime)) {
      // Up-to-date - Continue operation without re-load
      Logging::print("Loaded file is up-to-date\n");
      return PROGRAMMING_RC_OK;
   }
   if (autoFileLoad) {
      if (currentFileTime == -1) {
         // Original file no longer exists - alert user
         int getYesNo = wxMessageBox(_("Unable to auto-reload file as it is no longer accessible.\n\n"
                                       "Continue operation?"),
                                     _("Cannot Load File"),
                                     wxYES_NO|wxICON_QUESTION|wxYES_DEFAULT,
                                     this
                                    );
         if (getYesNo == wxYES) {
            Logging::print("Continuing without re-load\n");
            // Continue without re-load
            return PROGRAMMING_RC_OK;
         }
         else {
            // Abort programming/verifying
            Logging::print("Aborting operation\n");
            return PROGRAMMING_RC_ERROR_FILE_OPEN_FAIL;
         }
      }
      // Auto-reload changed file
      Logging::print("Auto-reloading file\n");
      return loadHexFile(lastFileLoaded, !incrementalLoad);
   }
   else { // !autoFileLoad
      if (currentFileTime == -1) {
         // Original file no longer exists - Ignore & continue without re-load
         return PROGRAMMING_RC_OK;
      }
      // File changed - alert user
      int getYesNo = wxMessageBox(_("Last loaded file has changed on disk.\n\n"
                                    "Reload file?"),
                                  _("File Changed"),
                                    wxYES_NO|wxICON_QUESTION,
                                    this
                                    );
       if (getYesNo != wxYES) {
          // Continue operation without re-load
          Logging::print("Continuing without re-load\n");
          return PROGRAMMING_RC_OK;
       }
       // Reload file non user OK
       Logging::print("Reloading file after user confirmation\n");
       return loadHexFile(lastFileLoaded, !incrementalLoad);
   }
}

//! wxEVT_COMMAND_BUTTON_CLICKED event handler for wxID_DEFAULT
//!
//! @param event The event to handle
//!
void FlashPanel::OnLoadFileButtonClick( wxCommandEvent& event ) {
//   Logging::print("FlashPanel::OnLoadFileButtonClick()\n");

   wxString caption  = _("Select Binary File to Load");
   wxString wildcard = _("Binary Files(*.s19,*.sx,*.afx,*.elf)|*.s19;*.sx;*.afx;*.elf|"
                         "SREC Hex files (*.s19,*.sx)|*.s19;*.sx|"
                         "Elf files (*.afx)|*.afx;*.elf|"
                         "All Files|*");
   wxString defaultDir = wxEmptyString;
   wxString defaultFilename = wxEmptyString;
   wxFileDialog dialog(this, caption, defaultDir, defaultFilename, wildcard, wxFD_OPEN);
   int getCancelOK = dialog.ShowModal();
   if (getCancelOK != wxID_OK) {
      return;
   }
   loadHexFile(dialog.GetPath(), !incrementalLoad || !fileLoaded);
}

//! wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_INCREMENTAL_FILE_LOAD_CHECKBOX
//!
//! @param event The event to handle
//!
void FlashPanel::OnIncrementalFileLoadCheckboxClick( wxCommandEvent& event ) {
   incrementalLoad = event.IsChecked();
}

//! wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_AUTO_FILE_RELOAD_CHECKBOX
//!
//! @param event The event to handle
//!
void FlashPanel::OnAutoFileReloadCheckboxClick( wxCommandEvent& event ) {
   autoFileLoad = event.IsChecked();
}
#endif

/*
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_DEVICE_TYPE_CHOICE
 */
void FlashPanel::OnDeviceTypeChoiceSelected( wxCommandEvent& event ) {
   // Get currently selected device type
   int deviceIndex = (int) event.GetClientData();
   Logging::print("FlashPanel::OnDeviceTypeChoiceSelected(): devIndex=%d\n", deviceIndex);
   setDeviceindex(deviceIndex);
   TransferDataToWindow();
}

#ifdef FLASH_PROGRAMMER
static int displayDialogue(const char *message, const char *caption, int style, USBDM_ErrorCode rc) {
   return wxMessageBox(
         wxString(message, wxConvUTF8), /* message */
         wxString(caption, wxConvUTF8), /* caption */
         style,                         /* style   */
         NULL                           /* parent  */
         );
}

/*
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_FILTER_BY_CHIP_ID_CHECKBOX
 */
void FlashPanel::OnFilterByChipIdCheckboxClick( wxCommandEvent& event ) {
   doFilterByChipId = event.IsChecked() &&
                    !filterChipIds.empty();

   Logging::print("FlashPanel::OnFilterByChipIdCheckboxClick(), currentDeviceIndex=%d\n", currentDeviceIndex);

   // Re-load the device list
   populateDeviceDropDown();
   TransferDataToWindow();
}

/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_DETECT_CHIP_ID_BUTTON
 */
void FlashPanel::OnDetectChipButtonClick( wxCommandEvent& event ) {

   USBDM_ErrorCode rc = autoDetectTargetDevice();
   if (rc != PROGRAMMING_RC_OK) {
      displayDialogue("Failed to detect devices", "Detection failure", wxOK|wxICON_INFORMATION, rc);
   }
   // Default to filtered display if valid CHIP_ID
   doFilterByChipId = !filterChipIds.empty();

   // Enable filter control checkbox if valid CHIP_ID
   filterByChipIdCheckBoxControl->Set3StateValue(doFilterByChipId?wxCHK_CHECKED:wxCHK_UNCHECKED);
   filterByChipIdCheckBoxControl->Enable(doFilterByChipId);

   // Re-load the device list
   populateDeviceDropDown();
   TransferDataToWindow();
}
#endif

/*
 * wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_TRIM_FREQUENCY_CHECKBOX
 */
void FlashPanel::OnTrimFrequencyCheckboxClick( wxCommandEvent& event ) {
   doTrim = event.IsChecked() &&
            (currentDevice->getClockType() != CLKEXT) &&
            (currentDevice->getClockType() != CLKINVALID);
//   Logging::print("FlashPanel::OnTrimFrequencyCheckboxClick(), doTrim= %s\n", doTrim?"True":"False");
   if (doTrim) {
      // Enabling trim - restore to default value
      currentDevice->setClockTrimFreq(currentDevice->getDefaultClockTrimFreq());
      currentDevice->setClockTrimNVAddress(currentDevice->getDefaultClockTrimNVAddress());
   }
   else {
      // Disabling trim
      currentDevice->setClockTrimFreq(0);
      currentDevice->setClockTrimNVAddress(currentDevice->getDefaultClockTrimNVAddress());
   }
   TransferDataToWindow();
}

/*
 * wxEVT_COMMAND_TEXT_UPDATED event handler for ID_TRIM_FREQUENCY_TEXT
 */
void FlashPanel::OnTrimFrequencyTextTextUpdated( wxCommandEvent& event ) {
   double value;
   event.GetString().ToDouble(&value);
   currentDevice->setClockTrimFreq((unsigned long int)trunc(value*1000));
   Logging::print("FlashPanel::OnTrimFrequencyTextTextUpdated(), Trim Freq = %f kHz\n", currentDevice->getClockTrimFreq()/1000.0);
}

/*
 * wxEVT_COMMAND_TEXT_UPDATED event handler for ID_NONVOLATILE_ADDRESS_TEXT
 */
void FlashPanel::OnNonvolatileAddressTextTextUpdated( wxCommandEvent& event ) {
   long int value;
   event.GetString().ToLong(&value, 16);
   currentDevice->setClockTrimNVAddress(value);
}

void FlashPanel::getDialogueValues(DeviceData &state) {

//   Logging::print("FlashPanel::getDialogueValues(), device = %s\n", (const char *)currentDevice->getTargetName().c_str());
   state.shallowCopy(*currentDevice);
   if (state.getClockType() == CLKEXT) {
      state.setClockTrimNVAddress(0);
      state.setClockTrimFreq(0);
      state.setClockAddress(0);
   }
   if (!doTrim) {
      state.setClockTrimNVAddress(0);
      state.setClockTrimFreq(0);
   }
#ifdef GDI   
   state.setSecurity(SEC_UNSECURED);
   state.setConnectionFreq(0);
#endif   
}

//! Set current device by name
//!
//! @param deviceName name of device e.g. 51AC128A
//!
bool FlashPanel::chooseDevice(const string &deviceName) {

//   Logging::print("FlashPanel::chooseDevice(%s)\n", (const char *)deviceName.ToAscii());

   // Make sure all devices are available
//   filterChipIds.clear();
//   populateDeviceDropDown();

   int deviceIndex = deviceDatabase->findDeviceIndexFromName(deviceName);
   if (deviceIndex < 0) {
      Logging::print("FlashPanel::chooseDevice(): no suitable device in comboBox\n");
      setDeviceindex(0);
      return false;
   }
   setDeviceindex(deviceIndex);

//   Logging::print("FlashPanel::chooseDevice() - device Name = \'%s\'\n", currentDevice->getTargetName().c_str());
//   Logging::print("FlashPanel::chooseDevice() - currentDeviceIndex = %d\n", currentDeviceIndex);
   return true;
}

//!
//! @param settings      - Object to load settings from
//!
void FlashPanel::loadSettings(const AppSettings &settings) {
   Logging log("FlashPanel::loadSettings");

//   Init();

   // Check for saved device name setting
   string deviceName  = settings.getValue(settingsKey+".deviceName", "");
   Logging::print("FlashPanel::loadSettings() - deviceName = \"%s\"\n", (const char *)deviceName.c_str());
   chooseDevice(deviceName);

   // Load the trim information
   unsigned long clockTrimFrequency = settings.getValue(settingsKey+".clockTrimFrequency", 0);
   currentDevice->setClockTrimFreq(clockTrimFrequency);
   doTrim = (clockTrimFrequency != 0);
   currentDevice->setClockTrimNVAddress(settings.getValue(settingsKey+".clockTrimNVAddress", currentDevice->getClockTrimNVAddress()));

   unsigned long targetBusFrequency = settings.getValue(settingsKey+".targetBusFrequency", 0);
   currentDevice->setConnectionFreq(targetBusFrequency);

#ifdef FLASH_PROGRAMMER
   autoFileLoad = settings.getValue(settingsKey+".autoFileLoad", 0) != 0;
   currentDevice->setSecurity((SecurityOptions_t)settings.getValue(settingsKey+".security", currentDevice->getSecurity()));
   currentDevice->setEraseOption((DeviceData::EraseOptions)settings.getValue(settingsKey+".eraseOption", (int)currentDevice->getEraseOption()));
   sound = settings.getValue(settingsKey+".playSounds", 0);
#endif

//   TransferDataToWindow();
}

//! Save setting file
//!
//! @param settings      - Object to save settings to
//!
void FlashPanel::saveSettings(AppSettings &settings) {
   Logging log("FlashPanel::saveSettings");

//   DeviceData deviceData;
//   getDialogueValues(deviceData);

   // Save device name
   settings.addValue(settingsKey+".deviceName",   currentDevice->getTargetName().c_str());

   // Save non-device fixed settings
   if (currentDevice->getClockTrimFreq() != 0) {
      settings.addValue(settingsKey+".clockTrimFrequency", currentDevice->getClockTrimFreq());
      settings.addValue(settingsKey+".clockTrimNVAddress", currentDevice->getClockTrimNVAddress());
   }
#ifdef FLASH_PROGRAMMER
   settings.addValue(settingsKey+".security", currentDevice->getSecurity());
   settings.addValue(settingsKey+".playSounds", (int)sound);
   settings.addValue(settingsKey+".eraseOption", (int)currentDevice->getEraseOption());
   settings.addValue(settingsKey+".autoFileLoad",  autoFileLoad?1:0);
#endif
}

#ifdef FLASH_PROGRAMMER
/*
 * Program device with error check and user notification of errors
 */
USBDM_ErrorCode FlashPanel::programFlash(bool loadAndGo) {
   Logging log("FlashPanel::programFlash");
   USBDM_ErrorCode rc = PROGRAMMING_RC_OK;

   if (!shared->updateState()) {
      return BDM_RC_ILLEGAL_PARAMS;
   }
   wxProgressDialog pd(_("Accessing Target"),
                       _("Initialising..."),
                       100,
                       this,
                       wxPD_APP_MODAL|wxPD_ELAPSED_TIME
                       );
   progressDialogue = &pd;

   if (flashprogrammer == NULL) {
      flashprogrammer = new FlashProgrammer;
   }
   do {
      // Temporarily change power options for "load & Go"
      bool leaveTargetPowered = bdmOptions.leaveTargetPowered;
      bdmOptions.leaveTargetPowered = loadAndGo;
      rc = USBDM_SetExtendedOptions(&bdmOptions);
      bdmOptions.leaveTargetPowered = leaveTargetPowered;
      if (rc != BDM_RC_OK) {
         continue;
      }
      rc = USBDM_SetTargetTypeWithRetry(targetType);
      if (rc != BDM_RC_OK) {
         continue;
      }
#if TARGET == MC56F80xx
      rc = DSC_Initialise();
      if (rc != BDM_RC_OK) {
         continue;
      }
#elif TARGET != HCS12
      rc = USBDM_TargetConnectWithRetry(retryNotPartial);
      if ((rc != BDM_RC_OK) && (rc != BDM_RC_BDM_EN_FAILED) && (rc != BDM_RC_SECURED)) {
         USBDM_SetTargetType(T_OFF);
         continue;
      }
#endif
      rc = flashprogrammer->setDeviceData(*currentDevice);
      if (rc != BDM_RC_OK) {
         continue;
      }
      rc = flashprogrammer->programFlash(&flashImageData, progressCallBack);
      if (rc != BDM_RC_OK) {
         continue;
      }
      if (loadAndGo) {
#if (TARGET == MC56F80xx)
         DSC_TargetReset((TargetMode_t)(RESET_DEFAULT|RESET_NORMAL));
#else
         USBDM_TargetReset((TargetMode_t)(RESET_DEFAULT|RESET_NORMAL));
#endif
      }
      else {
#if (TARGET == MC56F80xx)
         DSC_TargetReset((TargetMode_t)(RESET_DEFAULT|RESET_SPECIAL));
#else
         USBDM_TargetReset((TargetMode_t)(RESET_DEFAULT|RESET_SPECIAL));
#endif
      }
      uint16_t trimValue;
      rc = flashprogrammer->getCalculatedTrimValue(trimValue);
      if (trimValue != 0) {
         wxString tmp;
         tmp.Printf(_("Trim Value: 0x%2.2X.%1X"), trimValue>>1, trimValue&0x01);
         trimValueStaticControl->SetLabel(tmp);
      }
      else {
         trimValueStaticControl->SetLabel(_("Trim Value: -"));
      }
   } while (false);

   progressDialogue = NULL;
   USBDM_SetTargetType(T_OFF);

   // Flag error to user
   failBeep();
   switch(rc) {
      case PROGRAMMING_RC_OK:
         break;
      case PROGRAMMING_RC_ERROR_WRONG_SDID:
         wxMessageBox(
               _("Selected target device does not agree with detected device.   \n"
                 "(Unable to read/confirm CHIP_ID)"),
               _("Programming Failed!"),
               wxOK|wxICON_ERROR|wxSTAY_ON_TOP|wxCENTER,
               this);
         break;
      case PROGRAMMING_RC_ERROR_SPEED_APPROX:
         wxMessageBox(
               _("Unable to accurately determine target bus frequency.\n\n"
                 "Please use Detect Chip to calculate an approximate value.  "),
               _("Programming not possible!"),
               wxOK|wxICON_ERROR|wxSTAY_ON_TOP|wxCENTER,
               this);
         break;
      case PROGRAMMING_RC_ERROR_TRIM:
         wxMessageBox(
               _("Trimming of target clock before programming failed!\n\n"
                 "Frequency may be out of range or clock choice incorrect.  "),
               _("Clock Trim Failed!"),
               wxOK|wxICON_ERROR|wxSTAY_ON_TOP|wxCENTER,
               this);
         break;
      case PROGRAMMING_RC_ERROR_SECURED:
         wxMessageBox(
               _("Target is secured.\n\n"
                 "The Mass Erase option must be selected to program the device.  "),
               _("Programming Failed!"),
               wxOK|wxICON_ERROR|wxSTAY_ON_TOP|wxCENTER,
               this);
         break;
      case PROGRAMMING_RC_ERROR_FAILED_VERIFY:
         wxMessageBox(
               _("Readback of the flash contents does not agree with buffer.  "),
               _("Verify after programming failed!"),
               wxOK|wxICON_ERROR|wxSTAY_ON_TOP|wxCENTER,
               this);
         break;
      default:
         wxMessageBox(
               _("Programming of the target flash failed!\n\n"
                 "Reason: ") +
                 wxString(USBDM_GetErrorString(rc), wxConvUTF8),
               _("Programming Error"),
               wxOK|wxICON_ERROR|wxSTAY_ON_TOP|wxCENTER,
               this);
         break;
   }
   return rc;
}
/*
 * Verify target flash with user confirmation
 */
USBDM_ErrorCode FlashPanel::verifyFlash(void) {
   USBDM_ErrorCode rc = BDM_RC_OK;

   if (!shared->updateState()) {
      return BDM_RC_ILLEGAL_PARAMS;
   }
   wxProgressDialog pd(_("Accessing Target"),
                       _("Initialising..."),
                       100,
                       this,
                       wxPD_APP_MODAL|wxPD_ELAPSED_TIME
                       );
   progressDialogue = &pd;

   if (flashprogrammer == NULL) {
      flashprogrammer = new FlashProgrammer;
   }
//   Logging::print("FlashPanel::verifyFlash()\n");
   do {
      rc = USBDM_SetExtendedOptions(&bdmOptions);
      if (rc != BDM_RC_OK) {
         continue;
      }
      rc = USBDM_SetTargetTypeWithRetry(targetType);
      if (rc != BDM_RC_OK) {
         continue;
      }
#if (TARGET == MC56F80xx)
      rc = DSC_Initialise();
      if (rc != BDM_RC_OK) {
         continue;
      }
#elif (TARGET != HCS12)
      rc = USBDM_TargetConnectWithRetry(retryNotPartial);
      if ((rc != BDM_RC_OK) && (rc != BDM_RC_BDM_EN_FAILED) && (rc != BDM_RC_SECURED)) {
         continue;
      }
#endif
      rc = flashprogrammer->setDeviceData(*currentDevice);
      if (rc != BDM_RC_OK) {
         continue;
      }
      rc = flashprogrammer->verifyFlash(&flashImageData, progressCallBack);
   } while(false);

   USBDM_SetTargetType(T_OFF);
   progressDialogue = NULL;

   // Flag error to user
   failBeep();
   switch (rc) {
      case PROGRAMMING_RC_OK:
         break;
      case PROGRAMMING_RC_ERROR_SECURED:
         wxMessageBox(
                   _("Target is secured.\n\n"
                     "Reading target memory is not possible.  \n"
                     "(Programming flash is still available.)"),
                   _("Verify Failed!"),
                   wxOK|wxICON_ERROR|wxSTAY_ON_TOP|wxCENTER,
                   this
                   );
         break;
      case PROGRAMMING_RC_ERROR_FAILED_VERIFY:
         wxMessageBox(
               _("Readback of the flash contents does not agree with buffer.  "),
               _("Verify failed!"),
               wxOK|wxICON_ERROR|wxSTAY_ON_TOP|wxCENTER,
               this
               );
         break;
      default:
         wxMessageBox(
               _("Verification of the target flash failed!\n\n"
                 "Reason: ")+
                 wxString(USBDM_GetErrorString(rc), wxConvUTF8),
               _("Verify failed!"),
               wxOK|wxICON_ERROR|wxSTAY_ON_TOP|wxCENTER,
               this
               );
         break;
   }
   return rc;
}

/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_PROGRAM_FLASH_BUTTON
 */
void FlashPanel::OnProgramFlashButtonClick( wxCommandEvent& event ) {
   Logging log("FlashPanel::OnProgramFlashButtonClick");

   int getYesNo;
   long style = wxYES_NO|wxNO_DEFAULT |wxICON_QUESTION|wxSTAY_ON_TOP|wxCENTER;

   do {
      if (checkFileChange() != PROGRAMMING_RC_OK) {
         return;
      }
      if (programFlash() != PROGRAMMING_RC_OK) {
         return;
      }
      getYesNo = wxMessageBox(
                        _("Programming and verification of the    \n"
                          "flash has completed successfully.\n\n"
                          "Program another device?"),
                        _("Programming Completed"),
                        style,
                        this);
      // Change default to yes on subsequent dialogues
      style = wxYES_NO|wxYES_DEFAULT|wxICON_QUESTION|wxSTAY_ON_TOP|wxCENTER;
   } while (getYesNo == wxYES);
}

/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_VERIFY_FLASH_BUTTON
 */
void FlashPanel::OnVerifyFlashButtonClick( wxCommandEvent& event ) {

   int getYesNo;
   long style = wxYES_NO|wxNO_DEFAULT|wxICON_QUESTION|wxSTAY_ON_TOP|wxCENTER;

   do {
      if (checkFileChange() != PROGRAMMING_RC_OK) {
         return;
      }
      if (verifyFlash() != PROGRAMMING_RC_OK) {
         return;
      }
      getYesNo = wxMessageBox(
                        _("Verification of the flash contents      \n"
                          "has completed successfully.\n\n"
                          "Verify another device?"),
                        _("Verify Completed"),
                        style,
                        this);
      // Change default to yes on subsequent dialogues
      style = wxYES_NO|wxYES_DEFAULT|wxICON_QUESTION|wxSTAY_ON_TOP|wxCENTER;
   } while (getYesNo == wxYES);
}

/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_VERIFY_FLASH_BUTTON
 */
void FlashPanel::OnLoadAndGoButtonClick( wxCommandEvent& event ) {

   int getYesNo;
   long style = wxYES_NO|wxNO_DEFAULT|wxICON_QUESTION|wxSTAY_ON_TOP|wxCENTER;
   do {
      if (checkFileChange() != PROGRAMMING_RC_OK) {
         return;
      }
      if (programFlash(true) != PROGRAMMING_RC_OK) {
         return;
      }
      getYesNo = wxMessageBox(
                        _("Programming is complete.             \n"
                          "Target has been reset and is running.\n\n"
                          "Program another device?"),
                        _("Load and Go Completed"),
                        style,
                        this);
      // Change default to yes on subsequent dialogues
      style = wxYES_NO|wxYES_DEFAULT|wxICON_QUESTION|wxSTAY_ON_TOP|wxCENTER;
   } while (getYesNo == wxYES);
}

void FlashPanel::OnSecurityRadioboxSelected( wxCommandEvent& event ) {
   switch (event.GetSelection()) {
      default:
      case 0:
         currentDevice->setSecurity(SEC_DEFAULT);
//         Logging::print("Security = default\n");
         break;
      case 1:
         currentDevice->setSecurity(SEC_SECURED);
//         Logging::print("Security = secured\n");
         break;
      case 2:
         currentDevice->setSecurity(SEC_UNSECURED);
//         Logging::print("Security = unsecured\n");
         break;
      case 3:
         currentDevice->setSecurity(SEC_SMART);
//         Logging::print("Security = intelligent\n");
         break;
//      case 3:
//         currentDevice->setSecurity(SEC_CUSTOM);
////         Logging::print("Security = custom\n");
//         break;
   }
}

void FlashPanel::updateProgrammingState(void) {
   bool enableProgramming = ((currentDeviceIndex>=0)&&
                             (fileLoaded ||
                             (doTrim && (currentDevice->getEraseOption() != DeviceData::eraseMass))));
   programFlashButtonControl->Enable(enableProgramming);
   verifyFlashButtonControl->Enable(enableProgramming);
   loadAndGoButtonControl->Enable(enableProgramming);
}

//! wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_ERASE_CHOICE
//!
//! @param event The event to handle
//!
void FlashPanel::OnEraseChoiceSelect( wxCommandEvent& event ) {
   int selIndex = event.GetSelection();
   DeviceData::EraseOptions eraseOption = (DeviceData::EraseOptions)(int)eraseChoiceControl->GetClientData(selIndex);
   currentDevice->setEraseOption(eraseOption);
   updateProgrammingState();
//   Logging::print("FlashPanel::OnEraseChoiceSelect(%s)\n", DeviceData::getEraseOptionName(eraseOption));
}

void FlashPanel::OnSoundCheckboxClick( wxCommandEvent& event ) {
   sound = event.IsChecked();
}
#endif
