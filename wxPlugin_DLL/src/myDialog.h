/*
 * myDialog.h
 *
 *  Created on: 11/12/2012
 *      Author: podonoghue
 */

#ifndef MYDIALOG_H_
#define MYDIALOG_H_

class MyDialog: public wxDialog
{
   DECLARE_CLASS( MyDialog )
   DECLARE_EVENT_TABLE()

public:
   // Constructors
   MyDialog(void);
   MyDialog(
         wxWindow*       parent,
         wxWindowID      id      = wxID_ANY,
         const wxString& caption = wxT("Empty"),
         const wxPoint&  pos     = wxDefaultPosition,
         const wxSize&   size    = wxDefaultSize,
         long            style   = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU
         );

   // Initialize our variables
   void Init(void);

   // Creation
   bool Create(
         wxWindow*         parent,
         wxWindowID        id       = wxID_ANY,
         const wxString&   caption  = wxT("Empty"),
         const wxPoint&    pos      = wxDefaultPosition,
         const wxSize&     size     = wxDefaultSize,
         long              style    = wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU
         );

   // Creates the controls and sizers
   void CreateControls(void);

   void OnQuit(wxCloseEvent& event);

   enum  {
      ID_Quit = 1,
   };
};

#endif /* MYDIALOG_H_ */
