/*
 * SecurityValidator.h
 *
 *  Created on: 13/12/2012
 *      Author: podonoghue
 */

#ifndef SECURITYVALIDATOR_H_
#define SECURITYVALIDATOR_H_

#include <string.h>
#include <wx/validate.h>
//#include <wx/richtext/richtextctrl.h>

class SecurityValidator : public wxTextValidator {
   const char *            name;                   //! Name used to report validation errors
   bool                    enabled;                //! Controls if validation is done
   SecurityInfoPtr         securityInfoPtr;        //! Security information to maintain & use

private:
//   char tohex(uint8_t value) {
//      const char table[] = "0123456789ABCDEF";
//      return table[value&0x0F];
//   }
//   int todec(char ch) {
//      if ((ch>='a')&&(ch<='f')) {
//         return ch - 'a' + 10;
//      }
//      if ((ch>='A')&&(ch<='F')) {
//         return ch - 'A' + 10;
//      }
//      if ((ch>='0')&&(ch<='9')) {
//         return ch - '0';
//      }
//      return -1;
//   }

public:
   SecurityValidator(const char *name, SecurityInfoPtr securityInfoPtr) :
      wxTextValidator(wxFILTER_INCLUDE_CHAR_LIST, NULL),
      name(name),
      enabled(false),
      securityInfoPtr(securityInfoPtr){
      Logging::print("SecurityValidator::SecurityValidator(%s, SecurityInfoPtr)\n", name);
      SetCharIncludes(_("0123456789ABCDEFabcdef"));
   }
   SecurityValidator(const SecurityValidator &other) :
      wxTextValidator(wxFILTER_INCLUDE_CHAR_LIST, NULL),
      name(other.name),
      enabled(other.enabled),
      securityInfoPtr(other.securityInfoPtr) {
      Logging::print("SecurityValidator::SecurityValidator(const SecurityValidator &other)\n");
      SetCharIncludes(_("0123456789ABCDEFabcdef"));
   }

public:
   wxTextCtrl *GetWindow() const {
      wxTextCtrl *win = dynamic_cast<wxTextCtrl *>(wxValidator::GetWindow());
      if (win == NULL) {
         throw MyException("SecurityValidator::GetWindow() - window must be associated first");
      }
      return win;
   }
   bool Validate(wxWindow *parent) {
      Logging::print("SecurityValidator::Validate()\n");
      wxTextCtrl *win = GetWindow();
      if (!win->IsEnabled()) {
         return true;
      }
      return true;
   }

   bool TransferToWindow() {
      Logging::print("SecurityValidator::TransferToWindow()\n");
      if (enabled) {
         wxTextCtrl *win = GetWindow();
         if (securityInfoPtr == NULL) {
            throw MyException("TransferToWindow() - securityInfoPtr == NULL!");
         }
         win->SetValue(wxString(securityInfoPtr->getSecurityInfo().c_str(), wxConvUTF8));
      }
      return true;
   }

   //! Get value from associated text control
   //!
   //! @return value from control as zero-padded string
   //!
   const std::string getHexValues() {
      LOGGING;
      wxTextCtrl *win = GetWindow();
      int len = win->GetValue().length(); // in characters
      if (securityInfoPtr == NULL) {
         throw MyException("getHexValues() - securityInfoPtr == NULL!");
      }
      int size = securityInfoPtr->getSize(); // size in bytes
      if (len>(2*size)) {
         len = 2*size;
      }
      char buf[2*size+1];
      memset(buf, '0', sizeof(buf));
      memcpy(buf, (const char*)win->GetValue().mb_str(wxConvUTF8), len );
      buf[2*size] = '\0';
      Logging::print("Size = %d, Value = \'%s\'\n", size, buf);
      return  std::string(buf);
   }

   bool TransferFromWindow() {
      LOGGING;
      Logging::print("SecurityValidator::\n");
      wxTextCtrl *win = GetWindow();
      if (!win->IsEnabled()) {
         return true;
      }
      if (!Validate(NULL)) {
         return false;
      }
      securityInfoPtr->setSecurityInfo(getHexValues());
      return true;
   }

   //! @param name  Assumed to be a statically allocated string and is used by reference
   //! @param value Value to set
   void setObject(const char *name, SecurityInfoPtr securityInfoPtr) {
      this->name            = name;
      this->securityInfoPtr = securityInfoPtr;
      wxTextCtrl *win = GetWindow();
      if (securityInfoPtr != NULL) {
         win->SetMaxLength(2*securityInfoPtr->getSize());
      }
   }

   wxObject *Clone(void) const {
      Logging::print("SecurityValidator::Clone()\n");
      return new SecurityValidator(*this);
   }

   //! Enable or disable validation
   //!
   //! @param enabled  true to enable validation
   //!
   void enable(bool enabled) {
      Logging::print("SecurityValidator::enable(%s)\n", enabled?"true":"false");
      this->enabled = enabled;
   }
};

#endif /* SECURITYVALIDATOR_H_ */
