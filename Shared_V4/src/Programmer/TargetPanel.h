/*
 * FlashProgrammerDialogue.h
 *
 *  Created on: 07/07/2010
 *      Author: pgo
 */

#ifndef SERVERPANEL_H_
#define SERVERPANEL_H_

#if defined(FLASH_PROGRAMMER) || defined(LEGACY) || defined (GDB_SERVER)

#include <wx/frame.h>
#include <wx/notebook.h>
#include <wx/combo.h>
#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/sound.h>
#include <wx/progdlg.h>
#include <wx/log.h>
#include "USBDM_API.h"
#include "Log.h"
#include "DeviceData.h"
#include "FlashProgramming.h"
#include "AppSettings.h"
#include "NumberTextEditCtrl.h"
#include "ProgressTimer.h"
#include "Names.h"

class Shared;

/*!
 * USBDMConfigDialogue class declaration
 */
class TargetPanel: public wxPanel {

    DECLARE_CLASS( TargetPanel )
    DECLARE_EVENT_TABLE()

private:
   static wxProgressDialog* progressDialogue;
   SharedPtr                shared;

   // The following are shared between dialogue pages
   USBDM_ExtendedOptions_t& bdmOptions;             //!< Current BDM options
   DeviceDataPtr&           currentDevice;          //!< Description of current device

   const static string      settingsKey;            //!< Key to use for saving settings
   bool                     doFilterByChipId;       //!< For dialogue handling - Filter by SDID
   map<uint32_t,uint32_t>   filterChipIds;          //!< The SDIDs being filtered by
   bool                     incrementalLoad;        //!< Don't clear buffer when loading a file
   bool                     autoFileLoad;           //!< Auto load changed files before programing
   bool                     fileLoaded;             //!< Flag indicating Hex file loaded
   bool                     doTrim;                 //!< Trim target clock (if possible)
   bool                     needManualFrequencySet; //!< Connection speed has been manually set
   bool                     sound;                  //!< Sound on/off
   time_t                   fileLoadTime;           //!< Time last file was loaded
   wxString                 lastFileLoaded;         //!< Path to last file loaded
   FlashImage               flashImageData;         //!< Memory Image loaded from S1S9 files.
   DeviceDataBase*          deviceDatabase;         //!< Database of available devices
   HardwareCapabilities_t   bdmCapabilities;        //!< Capabilities of the connected BDM
   FlashProgrammer*         flashprogrammer;        //!< Flash programmer
   wxSound*                 beep;
   wxLogWindow*             logWindow;              //!< Log for server

   // Control Identifiers
   enum {
      ID_FLASH_PROGRAMMING = 12000,
      ID_USBDMCONFIG,
      ID_PANEL,
      ID_LOAD_FILE_BUTTON,
      ID_INCREMENTAL_FILE_LOAD_CHECKBOX,
      ID_AUTO_FILE_RELOAD_CHECKBOX,
      ID_DEVICE_TYPE_CHOICE,
      ID_FILTER_BY_CHIP_ID_CHECKBOX,
      ID_DETECT_CHIP_ID_BUTTON,
      ID_CLOCK_MODULE_TYPE_CHOICE,
      ID_CLOCK_MODULE_ADDRESS_TEXT,
      ID_TRIM_FREQUENCY_CHECKBOX,
      ID_TRIM_FREQUENCY_TEXT,
      ID_NONVOLATILE_ADDRESS_TEXT,
      ID_SECURITY_RADIOBOX,
      ID_PROGRAM_FLASH_BUTTON,
      ID_GDB_SERVER_PORT_NUMBER_TEXT,
      ID_GDB_SERVER_TEXT,
      ID_VERIFY_FLASH_BUTTON,
      ID_LOAD_AND_GO_BUTTON,
      ID_ERASE_CHOICE,
      ID_BUS_FREQ_TEXT,
      ID_SOUND  };

#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
   wxButton*               loadFileButtonControl;
   wxStaticText*           loadedFilenameStaticControl;
   wxCheckBox*             incrementalFileLoadCheckBoxControl;
   wxCheckBox*             autoFileReloadCheckBoxControl;
   wxCheckBox*             filterByChipIdCheckBoxControl;
   wxButton*               detectChipButtonControl;
   wxRadioBox*             securityRadioBoxControl;
   wxButton*               programFlashButtonControl;
   wxButton*               verifyFlashButtonControl;
   wxButton*               loadAndGoButtonControl;
   wxStaticText*           trimValueStaticControl;
   wxCheckBox*             enableSoundsCheckBoxControl;
   wxChoice*               eraseChoiceControl;

   NumberTextEditCtrl*     gdbServerPortNumberTextControl;
#endif

   NumberTextEditCtrl*     busFrequencyTextControl;
   wxChoice*               deviceTypeChoiceControl;
   wxChoice*               clockModuleTypeChoiceControl;
   wxStaticText*           clockModuleAddressStaticControl;
   NumberTextEditCtrl*     clockModuleAddressTextControl;
   wxStaticText*           trimFrequencyStaticControl;
   wxCheckBox*             trimFrequencyCheckBoxControl;
   NumberTextEditCtrl*     trimFrequencyTextControl;
   wxStaticText*           trimAddressStaticControl;
   NumberTextEditCtrl*     trimAddressTextControl;

   void setDeviceIndex(int deviceIndex);
   USBDM_ErrorCode autoDetectTargetDevice();
   USBDM_ErrorCode hcs12Check(void);

   void populateClockDropDown();
   void populateDeviceDropDown();

   // Creates the controls and sizers
   bool CreateControls();

   // Event Handlers
   void OnLoadFileButtonClick( wxCommandEvent& event );
   void OnIncrementalFileLoadCheckboxClick( wxCommandEvent& event );
   void OnAutoFileReloadCheckboxClick( wxCommandEvent& event );
   void OnDeviceTypeChoiceSelected( wxCommandEvent& event );
   void OnFilterByChipIdCheckboxClick( wxCommandEvent& event );
   void OnDetectChipButtonClick( wxCommandEvent& event );
   void OnRamBeginAddressTextTextUpdated( wxCommandEvent& event );
   void OnRamEndAddressTextTextUpdated( wxCommandEvent& event );
   void OnClockModuleTypeChoiceSelected( wxCommandEvent& event );
   void OnClockModuleAddressTextTextUpdated( wxCommandEvent& event );
   void OnTrimFrequencyCheckboxClick( wxCommandEvent& event );
   void OnTrimFrequencyTextTextUpdated( wxCommandEvent& event );
   void OnNonvolatileAddressTextTextUpdated( wxCommandEvent& event );
   void OnSecurityRadioboxSelected( wxCommandEvent& event );
   void OnRefreshBDMClick( wxCommandEvent& event );
   void OnProgramFlashButtonClick( wxCommandEvent& event );
   void OnVerifyFlashButtonClick( wxCommandEvent& event );
   void OnLoadAndGoButtonClick( wxCommandEvent& event );
   void OnSoundCheckboxClick( wxCommandEvent& event );
   void OnEraseChoiceSelect( wxCommandEvent& event );

   void updateProgrammingState(void);
   USBDM_ErrorCode programFlash(bool loadAndGo = false);
   USBDM_ErrorCode verifyFlash(void);
   USBDM_ErrorCode checkFileChange(void);

public:
   // Constructors
   TargetPanel(wxWindow* parent, SharedPtr shared, HardwareCapabilities_t bdmCapabilities=BDM_CAP_NONE);

   // Destructor
   ~TargetPanel() {
      if (flashprogrammer != NULL)
         delete flashprogrammer;
      if (beep != NULL)
         delete beep;
   };

   // Create the window
   bool Create( wxWindow* parent);

   // Update window from internal state
   bool TransferDataToWindow();

   // Update internal state from window
   bool TransferDataFromWindow();

   bool updateState();

   // Set internal state to default
   void Init();

   void loadSettings(const AppSettings &settings);
   void saveSettings(AppSettings &settings);

   bool chooseDevice(const string &deviceName);
   void getDialogueValues(DeviceData &state);

   void failBeep() {
      if (sound && (beep != NULL))
         beep->Play(wxSOUND_ASYNC);
   }
   static USBDM_ErrorCode progressCallBack(USBDM_ErrorCode rc, int percent, const char *message);

   USBDM_ErrorCode loadHexFile( wxString hexFilename, bool clearBuffer );

#ifdef GDI
   bool setDevice(const wxString &deviceName);
#endif   
};

#endif /* defined(PROGRAMMER) || defined(LEGACY) */

#endif /* SERVERPANEL_H_ */
