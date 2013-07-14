/*
 * CFUnlockerPanel.h
 *
 *  Created on: 23/10/2010
 *      Author: podonoghue
 */

#ifndef CFUNLOCKERPANEL_H_
#define CFUNLOCKERPANEL_H_

/*!
 * Includes
 */

#include <wx/spinctrl.h>

#include "KnownDevices.h"
#include "FlashEraseMethods.h"
#include "NumberTextEditCtrl.h"
#include "BitVector.h"
#include "JTAG.h"
#include "Shared.h"

class wxSpinCtrl;

/*!
 * Control identifiers
 */

#define SYMBOL_COLDFIREUNLOCKERPANEL_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_COLDFIREUNLOCKERPANEL_IDNAME ID_COLDFIREUNLOCKERPANEL

/*!
 * ColdfireUnlockerDialogue class declaration
 */
class ColdfireUnlockerPanel: public wxPanel
{
    DECLARE_DYNAMIC_CLASS( ColdfireUnlockerPanel )
    DECLARE_EVENT_TABLE()

private:
   KnownDevices      knownDevices;
   FlashEraseMethods flashEraseMethods;
   JTAG_Chain        jtagChain;

   void loadDeviceList();
   void loadEraseMethodsList();
   void updateClockDividerValue();
   void updateEraseParameters();
   void updateDeviceDetails();
   void loadJTAGDeviceList();
   void findDeviceInJTAGChain(unsigned int deviceNum);
   USBDM_ErrorCode eraseDscDevice();
   USBDM_ErrorCode eraseCFVxDevice();
   USBDM_ExtendedOptions_t &bdmOptions;

public:
    /// Constructors
    ColdfireUnlockerPanel( wxWindow* parent, SharedPtr shared);

    /// Creation
    bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style);

    // Destructor
    ~ColdfireUnlockerPanel();

    // Initializes member variables
    void Init();

    bool TransferDataToWindow();
    bool TransferDataFromWindow();

    bool updateState();

    // Creates the controls and sizers
    void CreateControls();

    void OnInitChainButtonClick( wxCommandEvent& event );
    void OnJtagDeviceChoiceSelected( wxCommandEvent& event );
    void OnIrLengthSpinctrlUpdated( wxSpinEvent& event );
    void OnPinStaticUpdate( wxUpdateUIEvent& event );
    void OnTargetDeviceChoiceSelected( wxCommandEvent& event );
    void OnSpeedTextctrlTextUpdated( wxCommandEvent& event );
    void OnMinFreqTextctrlTextUpdated( wxCommandEvent& event );
    void OnMaxFreqTextctrlTextUpdated( wxCommandEvent& event );
    void OnEquationChoiceSelected( wxCommandEvent& event );
    void OnUnlockValueTextctrlTextUpdated( wxCommandEvent& event );
    void OnClockDividerValueTextctrlTextUpdated( wxCommandEvent& event );
    void OnUnlockButtonClick( wxCommandEvent& event );

    // Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    // Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );

    // Should we show tooltips?
    static bool ShowToolTips();

    // Controls
    wxButton*              initChainButtonControl;
    wxStaticText*          numberOfDeviceStaticControl;
    wxStaticText*          jtagIdcodeStaticText;
    wxChoice*              jtagDeviceChoiceControl;
    wxSpinCtrl*            irLengthSpinControl;
    wxStaticText*          freescalePINStaticControl;
    wxStaticText*          totalIrLengthStaticControl;
    wxStaticText*          descriptionStaticControl;
    wxChoice*              targetDeviceChoiceControl;
    NumberTextEditCtrl*    targetSpeedTextControl;
    NumberTextEditCtrl*    minimumFrequencyTextControl;
    NumberTextEditCtrl*    maximumFrequencyTextControl;
    wxChoice*              equationChoiceControl;
    NumberTextEditCtrl*    unlockInstructionTextControl;
    NumberTextEditCtrl*    clockDividerTextControl;
    wxStaticText*          versionStaticControl;
    wxButton*              unlockButtonControl;

    int                    clkdivDrLength;
    /// Control identifiers
    enum {
        ID_COLDFIREUNLOCKERPANEL          = 10000,
        ID_INIT_CHAIN_BUTTON              = 10001,
        wxID_NUMBER_OF_DEVICES_STATIC     = 10006,
        wxID_JTAG_IDCODE_STATIC           = 10013,
        ID_JTAG_DEVICE_CHOICE             = 10002,
        ID_IR_LENGTH_SPINCTRL             = 10005,
        wxID_PIN_STATIC                   = 10014,
        ID_TARGET_DEVICE_CHOICE           = 10008,
        ID_SPEED_TEXTCTRL                 = 10009,
        ID_MIN_FREQ_TEXTCTRL              = 10010,
        ID_MAX_FREQ_TEXTCTRL              = 10011,
        ID_EQUATION_CHOICE                = 10012,
        ID_UNLOCK_VALUE_TEXTCTRL          = 10003,
        ID_CLOCK_DIVIDER_VALUE_TEXTCTRL   = 10004,
        wxID_VERSION_STATIC               = 10015,
        ID_UNLOCK_BUTTON                  = 10007
    };
};

#endif /* CFUNLOCKERPANEL_H_ */
