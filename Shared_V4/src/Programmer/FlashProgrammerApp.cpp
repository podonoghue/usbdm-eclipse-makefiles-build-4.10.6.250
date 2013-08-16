/*! \file
    \brief Flash Programming App

    FlashProgrammingApp.cpp

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
-=================================================================================
|   9 Jul 2013 | Re-factor for GDB Server                              4.9.6 - pgo
|   7 Apr 2012 | Added -reset, -power  options                         4.9.4 - pgo
|    Feb  2012 | Added -execute option                                 4.9.3 - pgo
|   5 May 2011 | Fixed Vdd options                                     4.4.3 - pgo
|  31 Jan 2011 | Added command line options (finally)                  4.4.1 - pgo
+=================================================================================
\endverbatim
*/

#include <wx/wx.h>
#include <wx/cmdline.h>
#include <wx/stdpaths.h>

#include "Common.h"
#include "USBDM_API.h"
#include "DeviceData.h"
#include "Log.h"
#include "USBDMDialogue.h"
#include "AppSettings.h"
#include "Common.h"
#include "Version.h"
#include "FlashProgramming.h"
#include "FlashImage.h"

#if TARGET==HCS08
const TargetType_t targetType = T_HCS08;
const char *logFilename("FlashProgrammer_HCS08.log");
#elif TARGET==HCS12
const TargetType_t targetType = T_HC12;
const char *logFilename("FlashProgrammer_HCS12.log");
#elif TARGET==RS08
const TargetType_t targetType = T_RS08;
const char *logFilename("FlashProgrammer_RS08.log");
#elif TARGET==CFV1
const TargetType_t targetType = T_CFV1;
const char *logFilename("FlashProgrammer_CFV1.log");
#elif TARGET==CFVx
const TargetType_t targetType = T_CFVx;
const char *logFilename("FlashProgrammer_CFVx.log");
#elif (TARGET==ARM)
const TargetType_t targetType = T_ARM;
const char *logFilename("FlashProgrammer_ARM.log");
#elif TARGET==MC56F80xx
#include "USBDM_DSC_API.h"
const TargetType_t targetType = T_MC56F80xx;
const char *logFilename("FlashProgrammer_DSC.log");
#else
#error "TARGET must be set"
#endif

// Declare the application class
class FlashProgrammerApp : public wxApp {
   DECLARE_CLASS( FlashProgrammerApp )
   DECLARE_EVENT_TABLE()

private:
   std::string                      customSecurityValue;
   bool                             commandLine;
   bool                             verify;
   bool                             program;
   bool                             verbose;
   wxString                         hexFileName;
   double                           trimFrequency;
   long                             trimNVAddress;

   void doCommandLineProgram();

   int                              returnValue;
   SharedPtr                        shared;

public:
   // Called on application startup
   virtual bool OnInit();
   virtual int  OnExit();
   virtual int  OnRun();
   virtual void OnInitCmdLine(wxCmdLineParser& parser);
   virtual bool OnCmdLineParsed(wxCmdLineParser& parser);
   virtual ~FlashProgrammerApp();

private:
   AppSettings                   *appSettings;

};

// Implements FlashProgrammerApp & GetApp()
DECLARE_APP(FlashProgrammerApp)
IMPLEMENT_APP(FlashProgrammerApp)
IMPLEMENT_CLASS(FlashProgrammerApp, wxApp)

/*
 * FlashProgrammerApp event table definition
 */
BEGIN_EVENT_TABLE( FlashProgrammerApp, wxApp )
END_EVENT_TABLE()

USBDM_ErrorCode callBack(USBDM_ErrorCode status, int percent, const char *message) {
   fprintf(stdout, "%d%%: %s", percent, message);
   return PROGRAMMING_RC_OK;
}

#if 1
void FlashProgrammerApp::doCommandLineProgram() {
   Logging log("FlashProgrammerApp::doCommandLineProgram");
   FlashImage flashImage;
   FlashProgrammer flashProgrammer;

   do {
      // Initialise the BDM
      if (shared->initBdm() != BDM_RC_OK) {
         returnValue = 1;
         break;
      }
      if (!hexFileName.IsEmpty() &&
         (flashImage.loadFile((const char *)hexFileName.ToAscii()) != BDM_RC_OK)) {
         Logging::print("Failed to load Hex file\n");
         returnValue = 1;
         break;
      }
      if (shared->loadDeviceDatabase() != BDM_RC_OK) {
         returnValue = 1;
         break;
      }
      // Copy device description and change mutable settings
      DeviceDataPtr &deviceData = shared->getCurrentDevice();
      if (deviceData->getSecurity() == SEC_CUSTOM) {
         deviceData->setCustomSecurity(customSecurityValue);
      }
      USBDM_ErrorCode rc;
      if (program) {
         if (verbose) {
            rc = flashProgrammer.programFlash(&flashImage, callBack);
         }
         else{
            rc = flashProgrammer.programFlash(&flashImage, NULL);
         }
      }
      else {
         if (verbose) {
            rc = flashProgrammer.verifyFlash(&flashImage, callBack);
         }
         else{
            rc = flashProgrammer.verifyFlash(&flashImage);
         }
      }
      if (rc != PROGRAMMING_RC_OK) {
         Logging::print("FlashProgrammerApp::doCommandLineProgram() - failed, rc = %s\n", USBDM_GetErrorString(rc));
#ifdef _UNIX_
         fprintf(stderr, "FlashProgrammerApp::doCommandLineProgram() - failed, rc = %s\n", USBDM_GetErrorString(rc));
#endif
         returnValue = 1;
         break;
      }
   } while (false);

   Logging::print(" Closing BDM\n");
   if (shared->getBdmOptions().leaveTargetPowered) {
#if (TARGET==HCS08) || (TARGET==RS08) || (TARGET==CFV1)
      USBDM_TargetReset((TargetMode_t)(RESET_SOFTWARE|RESET_NORMAL));
#elif (TARGET==HCS12) || (TARGET==CFVx) || (TARGET == ARM) ||(TARGET==MC56F80xx)
      USBDM_TargetReset((TargetMode_t)(RESET_HARDWARE|RESET_NORMAL));
#else
#error "TARGET must be set"
#endif
   }
   USBDM_Close();

#ifdef _UNIX_
   if (returnValue == 0) {
      fprintf(stdout, "Operation completed successfully\n");
   }
#endif
}
#endif

// Initialize the application
bool FlashProgrammerApp::OnInit(void) {
   returnValue = 0;

   SetAppName(_("usbdm")); // So application files are kept in the correct directory

   Logging::openLogFile(logFilename);
   Logging::setLoggingLevel(100);
   LOGGING;

   shared = SharedPtr(new Shared(targetType));

   // Create empty app settings
   appSettings = new AppSettings("GDBServer_", targetType);

   // call for default command parsing behaviour
   if (!wxApp::OnInit()) {
      return false;
   }

   if (!commandLine) {
      // Not using command line options so load saved settings
      appSettings->loadFromAppDirFile();
   }
   const wxString settingsFilename(_("FlashProgrammer_"));
   const wxString title(_("Flash Programmer"));

#ifndef _WIN32
   ((wxStandardPaths&)wxStandardPaths::Get()).SetInstallPrefix(_("/usr/local"));
#endif

#if TARGET == MC56F80xx
   DSC_SetLogFile(Logging::getLogFileHandle());
#endif

   if (commandLine) {
      doCommandLineProgram();
//      fprintf(stderr, "Programming Complete - rc = %d\n", returnValue);
   }
   else {
      SharedPtr shared(SharedPtr(new Shared(targetType)));

      // Create the main application window
      UsbdmDialogue *dialogue = new UsbdmDialogue(shared, *appSettings);
      dialogue->SetTitle(title);
      SetTopWindow(dialogue);
      dialogue->execute(hexFileName);
      dialogue->Destroy();
   }
   return true;
}

int FlashProgrammerApp::OnRun(void) {
   LOGGING;
   if (!commandLine) {
      int exitcode = wxApp::OnRun();
      if (exitcode != 0) {
         return exitcode;
      }
   }
   // Everything is done in OnInit()!
   Logging::print("FlashProgrammerApp::OnRun() - return value = %d\n", returnValue);
   return returnValue;
}

int FlashProgrammerApp::OnExit(void) {

//   Logging::print("FlashProgrammerApp::OnExit()\n");
   USBDM_Exit();

   if (!commandLine) {
      // Not using command line so save changed settings
      appSettings->writeToAppDirFile();
   }
   if (appSettings != NULL) {
      delete appSettings;
      appSettings = NULL;
   }
   return wxApp::OnExit();
}

FlashProgrammerApp::~FlashProgrammerApp() {
   Logging::closeLogFile();
}

static const wxCmdLineEntryDesc g_cmdLineDesc[] = {
      { wxCMD_LINE_PARAM,    NULL,         NULL, _("Name of the S19 Hex file to load"),                     wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },
      { wxCMD_LINE_OPTION, _("device"),    NULL, _("Target device e.g. MC9S08AW16A"),                       wxCMD_LINE_VAL_STRING },
      { wxCMD_LINE_OPTION, _("erase"),     NULL, _("Erase method (Mass, All, Selective, None)"),            wxCMD_LINE_VAL_STRING },
      { wxCMD_LINE_SWITCH, _("execute"),   NULL, _("Leave target power on & reset to normal mode at completion"), },
      { wxCMD_LINE_OPTION, _("flexNVM"),   NULL, _("FlexNVM parameters (eeprom,partition hex values)"),     wxCMD_LINE_VAL_STRING },
      { wxCMD_LINE_SWITCH, _("masserase"), NULL, _("Equivalent to erase=Mass") },
      { wxCMD_LINE_SWITCH, _("noerase"),   NULL, _("Equivalent to erase=None") },
      { wxCMD_LINE_OPTION, _("nvloc"),     NULL, _("Trim non-volatile memory location (hex)"),              wxCMD_LINE_VAL_STRING },
      { wxCMD_LINE_OPTION, _("power"),     NULL, _("Power timing (off,recovery) 100-10000 ms"),             wxCMD_LINE_VAL_STRING },
      { wxCMD_LINE_SWITCH, _("program"),   NULL, _("Program and verify flash contents"), },
      { wxCMD_LINE_OPTION, _("reset"),     NULL, _("Reset timing (active,release,recovery) 100-10000 ms"),  wxCMD_LINE_VAL_STRING },
      { wxCMD_LINE_OPTION, _("speed"),     NULL, _("Interface speed (CFVx/Kinetis/DSC) kHz"),               wxCMD_LINE_VAL_STRING },
      { wxCMD_LINE_OPTION, _("security"),  NULL, _("Explicit security value to use (as hex string)"),       wxCMD_LINE_VAL_STRING },
      { wxCMD_LINE_SWITCH, _("secure"),    NULL, _("Leave device secure after programming") },
      { wxCMD_LINE_OPTION, _("trim"),      NULL, _("Trim internal clock to frequency (in kHz) e.g. 32.7"),  wxCMD_LINE_VAL_STRING },
#ifdef _UNIX_
      { wxCMD_LINE_SWITCH, _("verbose"),   NULL, _("Print progress messages to stdout") },
#endif
      { wxCMD_LINE_SWITCH, _("unsecure"),  NULL, _("Leave device unsecure after programming") },
      { wxCMD_LINE_SWITCH, _("verify"),    NULL, _("Verify flash contents") },
      { wxCMD_LINE_OPTION, _("vdd"),       NULL, _("Supply Vdd to target (3V3 or 5V)"),                     wxCMD_LINE_VAL_STRING },
      { wxCMD_LINE_NONE }
};

void FlashProgrammerApp::OnInitCmdLine(wxCmdLineParser& parser)
{
    parser.SetDesc (g_cmdLineDesc);
    // must refuse '/' as parameter starter or cannot use "/path" style paths
    parser.SetSwitchChars (_("-"));
    parser.SetLogo(_("USBDM Flash Programmer \n"));

#if (wxCHECK_VERSION(2, 9, 0))
    parser.AddUsageText(_(
          "\nExamples:\n"
          "Programming an image with clock trimming:\n"
          "  FlashProgrammer Image.s19 -device=MC9S08AW16A -trim=243 -program -secure\n"
          "This will program a MC9S08AW16A with the contents of the file Image.s19 and\n"
          "trim the internal clock to 243kHz. The Flash image will be modified so that\n"
          "the device will be secure after programming.\n\n"
          "Programming the clock trim in an already programmed chip:\n"
          "  FlashProgrammer -device=MC9S08QG8 -trim=35.25 -erase=None -program \n"
          "This will trim the internal clock of MC9S08QG8 to 35.25kHz without erasing\n"
          "the present flash contents. It is necessary that the clock trim locations \n"
          "in flash are still unprogrammed (0xFF) when using the -trim option. The \n"
          "target must not be secured and cannot be made secured when using -erase=None.\n\n"
          "Programming image with custom security value:\n"
          "FlashProgrammer -device=MKL25Z128M4 -vdd=3v3 -erase=mass -program -security=123456789ABCDEF0FFFFFFFFFEFFFFFF Image.elf"
          ));
#endif
}

//! Process command line arguments
//!
bool FlashProgrammerApp::OnCmdLineParsed(wxCmdLineParser& parser) {
   Logging log("FlashProgrammerApp::OnCmdLineParsed");
   wxString  sValue;
   bool      success = true;

   commandLine  = false;
   verbose      = false;

   if (parser.GetParamCount() > 0) {
      hexFileName = parser.GetParam(0);
   }
   if (parser.Found(_("verify")) || parser.Found(_("program"))) {
      commandLine           = true;
      USBDM_ExtendedOptions_t &bdmOptions = shared->getBdmOptions();

#ifdef _UNIX_
      if (parser.Found(_("verbose"))) {
         verbose = true;
      }
#endif

   // Command line requires at least a device name
      if (parser.Found(_("device"), &sValue)) {
         USBDM_ErrorCode rc = shared->setCurrentDeviceByName((const char *)sValue.ToAscii());
         if (rc != BDM_RC_OK) {
            log.print("Failed to set device to \'%s\'\n", (const char *)sValue.ToAscii());
#if (wxCHECK_VERSION(2, 9, 0))
            parser.AddUsageText(_("***** Error: Failed to find device.\n"));
#endif
            success = false;
         }
         else {
            success = false;
         }
      }

   DeviceDataPtr deviceData = shared->getCurrentDevice();

#if (TARGET==HCS08) || (TARGET==RS08) || (TARGET==ARM)
      deviceData->setEraseOption(DeviceData::eraseMass);
#elif (TARGET==HCS12) || (TARGET==CFV1) || (TARGET==CFVx) || (TARGET==MC56F80xx)
      deviceData->setEraseOption(DeviceData::eraseAll);
#else
#error "TARGET must be set"
#endif
      if (parser.Found(_("masserase"))) {
         deviceData->setEraseOption(DeviceData::eraseMass);
      }
      if (parser.Found(_("noerase"))) {
         deviceData->setEraseOption(DeviceData::eraseNone);
      }
      if (parser.Found(_("secure"))) {
         deviceData->setSecurity(SEC_SECURED);
      }
      else if (parser.Found(_("unsecure"))) {
         deviceData->setSecurity(SEC_UNSECURED);
      }
      else {
         deviceData->setSecurity(SEC_DEFAULT);
      }
      if (parser.Found(_("security"), &sValue)) {
         if (deviceData->getSecurity() != SEC_DEFAULT) {
            // Can't use this option with secure/unsecure
            success = false;
         }
         else {
            deviceData->setSecurity(SEC_CUSTOM);
            customSecurityValue = std::string(sValue.ToAscii());
         }
      }
      verify   = parser.Found(_("verify"));
      program  = parser.Found(_("program"));

      if (parser.Found(_("nvloc"), &sValue)) {
         unsigned long uValue;
         if (!sValue.ToULong(&uValue, 16)) {
#if (wxCHECK_VERSION(2, 9, 0))
            parser.AddUsageText(_("***** Error: Illegal nvloc value.\n"));
#endif
            success = false;
         }
         deviceData->setClockTrimNVAddress(uValue);
      }
      if (parser.Found(_("erase"), &sValue)) {
         if (sValue.CmpNoCase(_("Mass")) == 0) {
            deviceData->setEraseOption(DeviceData::eraseMass);
         }
         else if (sValue.CmpNoCase(_("All")) == 0) {
            deviceData->setEraseOption(DeviceData::eraseAll);
         }
         else if (sValue.CmpNoCase(_("Selective")) == 0) {
            deviceData->setEraseOption(DeviceData::eraseSelective);
         }
         else if (sValue.CmpNoCase(_("None")) == 0) {
            deviceData->setEraseOption(DeviceData::eraseNone);
         }
         else {
#if (wxCHECK_VERSION(2, 9, 0))
            parser.AddUsageText(_("***** Error: Illegal erase value.\n"));
#endif
            success = false;
         }
      }
      if (parser.Found(_("vdd"), &sValue)) {
         if (sValue.CmpNoCase(_("3V3")) == 0) {
            bdmOptions.targetVdd = BDM_TARGET_VDD_3V3;
         }
         else if (sValue.CmpNoCase(_("5V")) == 0) {
            bdmOptions.targetVdd = BDM_TARGET_VDD_5V;
         }
         else {
#if (wxCHECK_VERSION(2, 9, 0))
            parser.AddUsageText(_("***** Error: Illegal vdd value.\n"));
#endif
            success = false;
         }
      }
      if (parser.Found(_("trim"), &sValue)) {
         double    dValue;
         if (!sValue.ToDouble(&dValue)) {
#if (wxCHECK_VERSION(2, 9, 0))
            parser.AddUsageText(_("***** Error: Illegal trim value.\n"));
#endif
            success = false;
         }
         deviceData->setClockTrimFreq(dValue * 1000);
      }
      else {
         trimFrequency = 0;
      }
      // flexNVM options
      if (parser.Found(_("flexNVM"), &sValue)) {
         DeviceData::FlexNVMParameters    flexParameters;
         unsigned long uValue;
 
         int index1 = 0;
         int index2 = sValue.find(',');
         wxString t = sValue.substr(index1, index2-index1);
         if (!t.ToULong(&uValue, 16)) {
#if (wxCHECK_VERSION(2, 9, 0))
            parser.AddUsageText(_("***** Error: Illegal flexNVM value.\n"));
#endif
            success = false;
         }
         else {
            flexParameters.eeepromSize = (uint8_t)uValue;
            // Check for truncation
            success = success && (flexParameters.eeepromSize == uValue);
         }
         index1 = index2+1;
         index2 = sValue.find(',', index1);
         t = sValue.substr(index1, index2-index1);
         if (!t.ToULong(&uValue, 16)) {
#if (wxCHECK_VERSION(2, 9, 0))
            parser.AddUsageText(_("***** Error: Illegal flexNVM value.\n"));
#endif
            success = false;
         }
         else {
            flexParameters.partionValue = (uint8_t)uValue;
            // Check for truncation
            success = success && (flexParameters.partionValue == uValue);
         }
         flexParameters.partionValue = (uint8_t)uValue;
         deviceData->setFlexNVMParameters(flexParameters);
      }
      // Reset options
      if (parser.Found(_("reset"), &sValue)) {
         unsigned long uValue=100000; // invalid so faults later
  
         int index1 = 0;
         int index2 = sValue.find(',');
         wxString t = sValue.substr(index1, index2-index1);
         if (!t.ToULong(&uValue, 10)) {
#if (wxCHECK_VERSION(2, 9, 0))
            parser.AddUsageText(_("***** Error: Illegal reset value.\n"));
#endif
            success = false;
         }
         bdmOptions.resetDuration = uValue;
 
         index1 = index2+1;
         index2 = sValue.find(',', index1);
         t = sValue.substr(index1, index2-index1);
         if (!t.ToULong(&uValue, 10)) {
#if (wxCHECK_VERSION(2, 9, 0))
            parser.AddUsageText(_("***** Error: Illegal reset value.\n"));
#endif
            success = false;
         }
         bdmOptions.resetReleaseInterval = uValue;
 
         index1 = index2+1;
         index2 = sValue.length();
         t = sValue.substr(index1, index2-index1);
         if (!t.ToULong(&uValue, 10)) {
#if (wxCHECK_VERSION(2, 9, 0))
            parser.AddUsageText(_("***** Error: Illegal reset value.\n"));
#endif
            success = false;
         }
         bdmOptions.resetRecoveryInterval = uValue;
      }
      // Power options
      if (parser.Found(_("power"), &sValue)) {
         unsigned long uValue=100000; // invalid so faults later
 
         int index1 = 0;
         int index2 = sValue.find(',');
         wxString t = sValue.substr(index1, index2-index1);
         if (!t.ToULong(&uValue, 10)) {
#if (wxCHECK_VERSION(2, 9, 0))
            parser.AddUsageText(_("***** Error: Illegal power value.\n"));
#endif
            success = false;
         }
         bdmOptions.powerOffDuration = uValue;
 
         index1 = index2+1;
         index2 = sValue.length();
         t = sValue.substr(index1, index2-index1);
         if (!t.ToULong(&uValue, 10)) {
#if (wxCHECK_VERSION(2, 9, 0))
            parser.AddUsageText(_("***** Error: Illegal power value.\n"));
#endif
            success = false;
         }
         bdmOptions.powerOnRecoveryInterval = uValue;
      }
      if (parser.Found(_("speed"), &sValue)) {
         unsigned long uValue;
         if (sValue.ToULong(&uValue, 10)) {
#if (wxCHECK_VERSION(2, 9, 0))
            parser.AddUsageText(_("***** Error: Illegal speed value.\n"));
#endif
            success = false;
         }
         bdmOptions.interfaceFrequency = uValue;
      }
      bdmOptions.leaveTargetPowered = parser.Found(_("execute"));
      // Programming includes verification
      if (program) {
         verify = false;
      }
   }
   if (!success) {
      parser.Usage();
   }
   return success;
}

