/*
 * CFUnlockerDialogue.h
 *
 *  Created on: 23/10/2010
 *      Author: pgo
 */

#ifndef _CFUNLOCKERDIALOGUE_H_
#define _CFUNLOCKERDIALOGUE_H_


#include "wx/notebook.h"
#include "Shared.h"
#include "CFUnlockerPanel.h"
#include "USBDMPanel.h"

#define SYMBOL_CFUNLOCKERDIALOGUE_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#if TARGET == MC56F80xx
#define SYMBOL_CFUNLOCKERDIALOGUE_TITLE _("MC56F80xx Unlocker")
#elif TARGET == CFVx
#define SYMBOL_CFUNLOCKERDIALOGUE_TITLE _("CFVx Unlocker")
#endif

#define SYMBOL_CFUNLOCKERDIALOGUE_IDNAME ID_CFUNLOCKERDIALOGUE
#define SYMBOL_CFUNLOCKERDIALOGUE_SIZE wxSize(400, 300)
#define SYMBOL_CFUNLOCKERDIALOGUE_POSITION wxDefaultPosition

/*!
 * CFUnlockerDialogue class declaration
 */
class CFUnlockerDialogue: public wxDialog, Shared {

    DECLARE_CLASS( CFUnlockerDialogue )
    DECLARE_EVENT_TABLE()

private:
   TargetType_t            targetType;
   wxString                caption;
   USBDMPanel*             usbdmPanel;
   ColdfireUnlockerPanel*  cfUnlockerPanel;
   wxNotebook*     noteBook;

   void OnSelChanging( wxNotebookEvent& event );
   void OnSelChanged( wxNotebookEvent& event );

public:
   //! Constructors
   CFUnlockerDialogue(TargetType_t targetType, const wxString &caption);

   //! Destructor
   ~CFUnlockerDialogue();

   //! Creation
   bool Create( wxWindow* parent, long style = wxDEFAULT_DIALOG_STYLE|wxMINIMIZE_BOX );
   bool TransferDataToWindow();
   bool TransferDataFromWindow();
   virtual bool updateState();
   // Initializes member variables
   bool Init();
   bool setDialogueValuesToDefault();

   // Creates the controls and sizers
   void CreateControls();

   wxBitmap GetBitmapResource( const wxString& name );
   wxIcon GetIconResource( const wxString& name );
   static bool ShowToolTips();

    /// Control identifiers
    enum {
        ID_CFUNLOCKERDIALOGUE = 10000,
        ID_NOTEBOOK = 10001,
        ID_PANEL = 10002,
        ID_PANEL1 = 10003
    };
};

#endif
    // _CFUNLOCKERDIALOGUE_H_
