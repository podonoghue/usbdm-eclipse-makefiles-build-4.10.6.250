/*
 * myDialog.cpp
 *
 *  Created on: 11/12/2012
 *      Author: podonoghue
 */

#include <stdio.h>
#include <wx/wx.h>
#include <wx/window.h>
#include <wx/dialog.h>
#include "myDialog.h"

extern FILE *logFile;

IMPLEMENT_CLASS(MyDialog, wxDialog);

BEGIN_EVENT_TABLE(MyDialog, wxDialog)
   EVT_CLOSE( MyDialog::OnQuit) // Close window when X pressed
END_EVENT_TABLE()

MyDialog::MyDialog(void) {
   Init();
}

MyDialog::MyDialog(  wxWindow*       parent,
                     wxWindowID      id,
                     const wxString& caption,
                     const wxPoint&  pos,
                     const wxSize&   size,
                     long            style) {

   Init();
   Create(parent, id, caption, pos, size, style);
}

void MyDialog::Init(void) {
   fprintf(logFile, "Init()\n");
}

bool MyDialog::Create(
      wxWindow*         parent,
      wxWindowID        id,
      const wxString&   caption,
      const wxPoint&    pos,
      const wxSize&     size,
      long              style) {

   const long extraStyles = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxSTAY_ON_TOP;
   // We have to set extra styles before creating the dialog
   SetExtraStyle(wxWS_EX_BLOCK_EVENTS|wxDIALOG_EX_CONTEXTHELP);
   if (!wxDialog::Create( parent, id, caption, pos, size, style|extraStyles )) {
      return false;
   }
   CreateControls();
//    This fits the dialog to the minimum size dictated by
//    the sizers
//   GetSizer()->Fit(this);
//   // This ensures that the dialog cannot be sized smaller
//   // than the minimum size
//   GetSizer()->SetSizeHints(this);
//   // Centre the dialog on the parent or (if none) screen
   Centre();
   return true;
}

void MyDialog::CreateControls() {
   fprintf(logFile, "CreateControls()\n");
}

void MyDialog::OnQuit(wxCloseEvent& event) {
      if ( IsModal() ) {
         EndModal(wxID_OK); // If modal
      }
      else {
         SetReturnCode(wxID_OK);
         this->Show(false); // If modeless
      }
}
