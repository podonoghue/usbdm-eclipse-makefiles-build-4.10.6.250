/*! \file
    \brief Implements USBDM dialogue

    CFUnlockerDialogue.cpp

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
   | 24 Oct 2010 | wxWidgets version created                               - pgo
   +============================================================================
   \endverbatim
 */

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
#include "wx/imaglist.h"
////@end includes

#include "CFUnlockerDialogue.h"

#include "USBDM_API.h"
#include "USBDMPanel.h"

//===================================================================
//===================================================================
//===================================================================

//! CFUnlockerDialogue constructor
//!
//!
//! @note: It is necessary to call Create()
//!
CFUnlockerDialogue::CFUnlockerDialogue(TargetType_t targetType, const wxString &caption) :
                  Shared(targetType),
                  targetType(targetType),
                  caption(caption) {
   Logging::setLoggingLevel(100);
   Logging log("CFUnlockerDialogue::CFUnlockerDialogue");
   Init();
}



//! Set the dialogue internal state to the default (not including pages)
//!
bool CFUnlockerDialogue::Init()
{
   Logging log("CFUnlockerDialogue::Init");

   usbdmPanel = NULL;
   cfUnlockerPanel = NULL;

   // Set options to default
   bdmOptions.size       = sizeof(USBDM_ExtendedOptions_t);
   bdmOptions.targetType = targetType;
   USBDM_GetDefaultExtendedOptions(&bdmOptions);
   return true;
}

//! CFUnlockerDialgue creator
//!
//! @param parent     : Parent window
//!
bool CFUnlockerDialogue::Create(wxWindow* parent, long style) {
   Logging log("CFUnlockerDialogue::Create");

   wxDialog::Create( parent, SYMBOL_CFUNLOCKERDIALOGUE_IDNAME, caption, wxDefaultPosition, wxSize(-1,-1), style);

   CreateControls();

   if (GetSizer()) {
      GetSizer()->SetSizeHints(this);
   }
   Centre();

   return true;
}

//! CFUnlockerDialogue destructor
//!

CFUnlockerDialogue::~CFUnlockerDialogue() {
}

//! Control creation
//!
void CFUnlockerDialogue::CreateControls() {
   Logging log("CFUnlockerDialogue::CreateControls");

   CFUnlockerDialogue* frame = this;

   wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
   frame->SetSizer(itemBoxSizer2);

   noteBook = new wxNotebook( frame, ID_NOTEBOOK, wxDefaultPosition, wxDefaultSize, wxBK_DEFAULT );
   itemBoxSizer2->Add(noteBook, 0, wxGROW|wxALL, 5);

   usbdmPanel = new USBDMPanel(noteBook, this, targetType);
   noteBook->AddPage(usbdmPanel, _("Connection"));

   cfUnlockerPanel = new ColdfireUnlockerPanel(noteBook, this);

   noteBook->AddPage(cfUnlockerPanel, _("Unlocker"));

}

//===================================================================
//! Copy internal state to Dialogue controls
//!
bool CFUnlockerDialogue::TransferDataToWindow() {
   Logging log("CFUnlockerDialogue::TransferDataToWindow");

   bool ok = wxDialog::TransferDataToWindow();
   ok = ok && usbdmPanel->TransferDataToWindow();
   ok = ok && cfUnlockerPanel->TransferDataToWindow();
   return ok;
}

//===================================================================
//! Update internal state on all pages
//!
//! @return true  => success
//!         false => dialogue page has inconsistent data
//!
bool CFUnlockerDialogue::updateState() {
   bool ok = true;
   ok = ok && usbdmPanel->updateState();
   ok = ok && cfUnlockerPanel->updateState();
   return ok;
}

//===================================================================
//! Set dialogue state to default values
//!
bool CFUnlockerDialogue::setDialogueValuesToDefault() {
   Logging log("CFUnlockerDialogue::setDialogueValuesToDefault");

   Init();
   TransferDataToWindow();

   return true;
}

//===================================================================
//! Copy internal state from Dialogue controls
//!
bool CFUnlockerDialogue::TransferDataFromWindow() {
   Logging log("CFUnlockerDialogue::TransferDataFromWindow");

   bool ok = wxDialog::TransferDataFromWindow();
   ok = ok && usbdmPanel->TransferDataFromWindow();
   ok = ok && cfUnlockerPanel->TransferDataFromWindow();
   return ok;
}

//! Should we show tooltips?
//!
bool CFUnlockerDialogue::ShowToolTips() {
    return true;
}

//! Get bitmap resources
//!
//! @param name
//!
wxBitmap CFUnlockerDialogue::GetBitmapResource( const wxString& name ) {
    // Bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
}

//! Get icon resources
//!
//! @param name
//!
wxIcon CFUnlockerDialogue::GetIconResource( const wxString& name ) {
    // Icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
}

/*
 * USBDMDialogue type definition
 */
IMPLEMENT_CLASS( CFUnlockerDialogue, wxDialog )

//
//  CFUnlockerDialogue event table definition
//

BEGIN_EVENT_TABLE( CFUnlockerDialogue, wxDialog )

   EVT_NOTEBOOK_PAGE_CHANGING( ID_NOTEBOOK, CFUnlockerDialogue::OnSelChanging )
   EVT_NOTEBOOK_PAGE_CHANGED( ID_NOTEBOOK,  CFUnlockerDialogue::OnSelChanged )
END_EVENT_TABLE()

//! wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGING event handler for ID_NOTEBOOK
//!
//! @param event The event to handle.
//!
void CFUnlockerDialogue::OnSelChanging( wxNotebookEvent& event ) {
   Logging log("CFUnlockerDialogue::OnSelChanging");

   int leavingPage = event.GetOldSelection();
   if (leavingPage < 0) {
      return;
   }
   // Validate page before leaving
   wxPanel *panel = static_cast<wxPanel *>(noteBook->GetPage(leavingPage));
   if (!panel->TransferDataFromWindow()) {
      Logging::print("Vetoing page change\n");
      event.Veto();
      return;
   }
   if (panel == usbdmPanel) {
      // Leaving Communication page - Try to open BDM
      Logging::print("Opening BDM\n");
      USBDM_ErrorCode rc = usbdmPanel->openBdm();
      if (rc != BDM_RC_OK) {
         Logging::print("CFUnlockerDialogue::OnNotebookPageChanging() - openBdm() failed\n");
         wxMessageBox(_("Failed to open BDM.\n\n"
                        "Reason: ") +
                      wxString(USBDM_GetErrorString(rc), wxConvUTF8),
                      _("USBDM Connection Error"),
                      wxOK|wxICON_ERROR,
                      this
                      );
         event.Veto();
      }
   }
}

//! wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED event handler for ID_NOTEBOOK
//!
//! @param event The event to handle.
//!
void CFUnlockerDialogue::OnSelChanged( wxNotebookEvent& event ) {
   Logging log("CFUnlockerDialogue::OnSelChanged");
//   Logging::print("(%d => %d)\n", event.GetOldSelection(), event.GetSelection());
   int enteringPage = event.GetSelection();
   if (enteringPage < 0) {
      return;
   }
   wxPanel *panel = static_cast<wxPanel *>(noteBook->GetPage(enteringPage));
   if (panel == usbdmPanel) {
      // Entering Communication page - Close the BDM
//      Logging::print("Closing BDM\n");
      USBDM_Close();
   }
   panel->TransferDataToWindow();
}

