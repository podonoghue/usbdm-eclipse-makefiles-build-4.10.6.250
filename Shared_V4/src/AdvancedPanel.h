/*
 * FlashProgrammerDialogue.h
 *
 *  Created on: 07/07/2010
 *      Author: pgo
 */

#ifndef ADVANCEDPANEL_H
#define ADVANCEDPANEL_H

#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/string.h>
#include <wx/validate.h>
#include <wx/textctrl.h>
//#include <wx/richtext/richtextctrl.h>

#include "Log.h"
#include "AppSettings.h"
#if defined(FLASH_PROGRAMMER)
#include "FlashProgramming.h"
#include "SecurityValidator.h"
#endif
#include "AppSettings.h"
#include "NumberTextEditCtrl.h"

#include "TimeIntervalValidator.h"

class Shared;

/*!
 * FlashPanel class declaration
 */
class AdvancedPanel: public wxPanel {

    DECLARE_CLASS( AdvancedPanel )
    DECLARE_EVENT_TABLE()

private:
    static const string           settingsKey;
    int                           eeepromSizeChoice;      // Choice for eeepromSizeChoice control & index for eeepromSizeValues[]
    int                           flexNvmPartitionIndex;  // Index for flexNvmPartitionValues[]

    // Provided by USBDMDialogue
    USBDM_ExtendedOptions_t&      bdmOptions;
    TargetType_t                  targetType;

 #if defined(FLASH_PROGRAMMER)
    DeviceDataPtr&                currentDevice;
 #endif

   // Creates the controls and sizers
   bool      CreateControls();
   void      populateEeepromControl();
   void      populatePartitionControl();
   int       findEeepromSizeIndex(unsigned eepromSize);
   int       findPartitionControlIndex(unsigned backingStoreSize);
   void      updateFlashNVM();
   void      populateSecurityControl();
   wxString  parseSecurityValue();
   void      updateSecurity();
   void      updateSecurityDescription();

   void      OnEeepromSizeChoiceSelected( wxCommandEvent& event );
   void      OnFlexNvmPartionChoiceSelected( wxCommandEvent& event );
   void      OnSecurityMemoryRegionChoiceSelected( wxCommandEvent& event );
   void      OnResetCustomValueClick( wxCommandEvent& event );
   void      OnSecurityEditUpdate(wxCommandEvent& event);
   void      OnSecurityCheckboxClick( wxCommandEvent& event );

   char tohex(uint8_t value) {
      const char table[] = "0123456789ABCDEF";
      return table[value&0x0F];
   }

   // Controls
   NumberTextEditCtrl*           powerOffDurationTextControl;
   NumberTextEditCtrl*           powerOnRecoveryIntervalTextControl;
   NumberTextEditCtrl*           resetDurationTextControl;
   NumberTextEditCtrl*           resetReleaseIntervalTextControl;
   NumberTextEditCtrl*           resetRecoveryIntervalTextControl;

#if (TARGET==CFV1) || (TARGET==ARM)
   wxStaticText*                 eeepromSizeStaticText;
   wxChoice*                     eeepromSizeChoiceControl;
   wxStaticText*                 flexNvmPartitionStaticText;
   wxChoice*                     flexNvmPartitionChoiceControl;
   wxStaticText*                 flexNvmDescriptionStaticControl;
#endif
   wxCheckBox*                   customSecurityCheckbox;
   wxChoice*                     securityMemoryRegionChoice;
   wxButton*                     resetCustomButtonControl;
   wxStaticText*                 securityDescriptionStaticText;
   wxStaticText*                 securityMemoryRegionSecurityAddress;
   wxTextCtrl*                   securityValuesTextControl;

   int                           securityMemoryRegionIndex;
   static const int              maxSecurityNum = 4;

#if defined(FLASH_PROGRAMMER)
   SecurityInfoPtr               customSecurityInfoPtr[maxSecurityNum];
   SecurityInfoPtr               securedInfoPtr;
   SecurityInfoPtr               unsecuredInfoPtr;
   SecurityInfoPtr               securityInfoPtr;
   SecurityDescriptionConstPtr   securityDescriptionPtr;
   SecurityOptions_t             lastSecurityOption;
#endif

public:
   // Constructors
   AdvancedPanel(wxWindow* parent, Shared *shared, TargetType_t targetType=T_HCS08, HardwareCapabilities_t bdmCapabilities=BDM_CAP_ALL);

   // Destructor
   ~AdvancedPanel() {
//      print("~AdvancedPanel()\n");
   };

   // Create the window
   bool Create( wxWindow* parent);

   // Set internal state to default
   void Init();

   void loadSettings(const AppSettings &settings);
   void saveSettings(AppSettings &settings);

   bool TransferDataToWindow();
   bool TransferDataFromWindow();

   bool updateState();
};

#endif /* ADVANCEDPANEL_H */
