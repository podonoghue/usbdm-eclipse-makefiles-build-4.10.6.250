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
|   9 Jul 2013 | Created                                               4.9.6 - pgo
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
#include "Names.h"

#include "GdbServerWindow.h"
#define CONFIG_FILE_NAME "GDBServer_"

#if TARGET==HCS08
const TargetType_t targetType = T_HCS08;
const char *logFilename("GDBServer_HCS08.log");
#elif TARGET==HCS12
const TargetType_t targetType = T_HC12;
const char *logFilename("GDBServer_HCS12.log");
#elif TARGET==RS08
const TargetType_t targetType = T_RS08;
const char *logFilename("GDBServer_RS08.log");
#elif TARGET==CFV1
const TargetType_t targetType = T_CFV1;
const char *logFilename("GDBServer_CFV1.log");
#elif TARGET==CFVx
const TargetType_t targetType = T_CFVx;
const char *logFilename("GDBServer_CFVx.log");
#elif (TARGET==ARM)
const TargetType_t targetType = T_ARM;
const char *logFilename("GDBServer_ARM.log");
#elif TARGET==MC56F80xx
#include "USBDM_DSC_API.h"
const TargetType_t targetType = T_MC56F80xx;
const char *logFilename("GDBServer_DSC.log");
#else
#error "TARGET must be set"
#endif

// Declare the application class
class GDBServerApp : public wxApp {
   DECLARE_CLASS( GDBServerApp )
   DECLARE_EVENT_TABLE()

private:
   std::string                      customSecurityValue;
   bool                             skipOpeningDialogue;
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
   virtual ~GDBServerApp();

private:
   AppSettings                   *appSettings;

};

// Implements GDBServerApp & GetApp()
DECLARE_APP(GDBServerApp)
IMPLEMENT_APP(GDBServerApp)
IMPLEMENT_CLASS(GDBServerApp, wxApp)

/*
 * GDBServerApp event table definition
 */
BEGIN_EVENT_TABLE( GDBServerApp, wxApp )
END_EVENT_TABLE()

USBDM_ErrorCode callBack(USBDM_ErrorCode status, int percent, const char *message) {
   fprintf(stdout, "%d%%: %s", percent, message);
   return PROGRAMMING_RC_OK;
}

// Initialize the application
bool GDBServerApp::OnInit(void) {
   returnValue = 0;

#ifndef _WIN32
   // Otherwise wxWidgets doesn't look in the correct location
   ((wxStandardPaths&)wxStandardPaths::Get()).SetInstallPrefix(_(USBDM_INSTALL_DIRECTORY));
#endif

   SetAppName(_("usbdm")); // So application files are kept in the correct directory
   Logging::openLogFile(logFilename);

   Logging::setLoggingLevel(100);
   Logging log("GDBServerApp::OnInit");

   shared = SharedPtr(new Shared(targetType));

   // Create empty app settings
   appSettings = new AppSettings(CONFIG_FILE_NAME, targetType);

   // call for default command parsing behaviour
   if (!wxApp::OnInit()) {
      return false;
   }

   if (!skipOpeningDialogue) {
      // Not using command line options so load saved settings
      appSettings->loadFromAppDirFile();
   }
   const wxString title(_("GDB Server"));

#if TARGET == MC56F80xx
   DSC_SetLogFile(Logging::getLogFileHandle());
#endif

   // Create the main application window
   GdbServerWindow *serverWindow = new GdbServerWindow(shared, *appSettings);
   serverWindow->SetTitle(title);
   SetTopWindow(serverWindow);
   serverWindow->execute(skipOpeningDialogue);

   return true;
}

int GDBServerApp::OnRun(void) {
   LOGGING;
   int exitcode = wxApp::OnRun();
   if (exitcode != 0) {
      return exitcode;
   }
   // Everything is done in OnInit()!
   Logging::print("GDBServerApp::OnRun() - return value = %d\n", returnValue);
   return returnValue;
}

int GDBServerApp::OnExit(void) {

//   Logging::print("GDBServerApp::OnExit()\n");
   USBDM_Exit();

   if (!skipOpeningDialogue) {
      // Not using command line so save changed settings
      appSettings->writeToAppDirFile();
   }

   return wxApp::OnExit();
}

GDBServerApp::~GDBServerApp() {
   Logging::closeLogFile();
}

static const wxCmdLineEntryDesc g_cmdLineDesc[] = {
      { wxCMD_LINE_OPTION, _("bdm"),         NULL, _("Serial number of preferred BDM to use"),                wxCMD_LINE_VAL_STRING },
      { wxCMD_LINE_OPTION, _("requiredBdm"), NULL, _("Serial number of required BDM to use"),                 wxCMD_LINE_VAL_STRING },
      { wxCMD_LINE_OPTION, _("device"),      NULL, _("Target device e.g. MCF51CN128"),                        wxCMD_LINE_VAL_STRING },
      { wxCMD_LINE_OPTION, _("erase"),       NULL, _("Erase method (Mass, All, Selective, None)"),            wxCMD_LINE_VAL_STRING },
      { wxCMD_LINE_SWITCH, _("exitOnClose"), NULL, _("Exit Server when connection closed"),                   wxCMD_LINE_VAL_NONE   },
//      { wxCMD_LINE_OPTION, _("flexNVM"),   NULL, _("FlexNVM parameters (eeprom,partition hex values)"),     wxCMD_LINE_VAL_STRING },
      { wxCMD_LINE_OPTION, _("nvloc"),       NULL, _("Trim non-volatile memory location (hex)"),              wxCMD_LINE_VAL_STRING },
      { wxCMD_LINE_OPTION, _("power"),       NULL, _("Power timing (off,recovery) 100-10000 ms"),             wxCMD_LINE_VAL_STRING },
      { wxCMD_LINE_OPTION, _("port"),        NULL, _("Server port # to use e.g. 1234"),                       wxCMD_LINE_VAL_STRING },
      { wxCMD_LINE_OPTION, _("reset"),       NULL, _("Reset timing (active,release,recovery) 10-10000 ms"),   wxCMD_LINE_VAL_STRING },
      { wxCMD_LINE_OPTION, _("security"),    NULL, _("Device security (unsecured, image, smart)"),            wxCMD_LINE_VAL_STRING },
      { wxCMD_LINE_OPTION, _("speed"),       NULL, _("Interface speed (CFVx/Kinetis/DSC) kHz"),               wxCMD_LINE_VAL_STRING },
      { wxCMD_LINE_OPTION, _("trim"),        NULL, _("Trim internal clock to frequency (in kHz) e.g. 32.7"),  wxCMD_LINE_VAL_STRING },
      { wxCMD_LINE_OPTION, _("vdd"),         NULL, _("Supply Vdd to target (3V3 or 5V)"),                     wxCMD_LINE_VAL_STRING },
      { wxCMD_LINE_NONE }
};

void GDBServerApp::OnInitCmdLine(wxCmdLineParser& parser) {
    parser.SetDesc (g_cmdLineDesc);
    // must refuse '/' as parameter starter or cannot use "/path" style paths
    parser.SetSwitchChars (_("-"));
    parser.SetLogo(_("USBDM GDB Server \n"));

#if (wxCHECK_VERSION(2, 9, 0))
    parser.AddUsageText(_("\n"
          "Notes: \n"
          "  - If any options are given then the opening dialogue is skipped and the server is started immediately.\n"
          "    Also in this case changes to settings are discarded on exit."
          "\nExample:\n"
          "Start server:\n"
          "  GDBServer -port=1234 -device=MCF51CN128 -trim=243\n"
          "This will start the server on localhost:1234 for a MCF51CN128 device and\n"
          "trim the internal clock to 243kHz when programming. \n\n"
          ));
#endif
}

//! Process command line arguments
//!
bool GDBServerApp::OnCmdLineParsed(wxCmdLineParser& parser) {
   Logging log("GDBServerApp::OnCmdLineParsed");
   wxString  sValue;
   bool      success = true;

   skipOpeningDialogue  = false;
   verbose              = false;

   if (parser.Found(_("device"), &sValue)) {
      log.print("Setting device to \'%s\'\n", (const char *)sValue.ToAscii());
      skipOpeningDialogue = true;
      USBDM_ErrorCode rc = shared->setCurrentDeviceByName((const char *)sValue.ToAscii());
      if (rc != BDM_RC_OK) {
         log.print("Failed to set device to \'%s\'\n", (const char *)sValue.ToAscii());
#if (wxCHECK_VERSION(2, 9, 0))
         parser.AddUsageText("***** Error: Failed to find device.\n");
#endif
         success = false;
      }
   }
   USBDM_ExtendedOptions_t &bdmOptions = shared->getBdmOptions();
   DeviceDataPtr            deviceData = shared->getCurrentDevice();

   if (parser.Found(_("nvloc"), &sValue)) {
      skipOpeningDialogue = true;
      unsigned long uValue;
      if (!sValue.ToULong(&uValue, 16)) {
#if (wxCHECK_VERSION(2, 9, 0))
         parser.AddUsageText("***** Error: Illegal nvloc value.\n");
#endif
         success = false;
      }
      deviceData->setClockTrimNVAddress(uValue);
   }
   shared->setExitOnClose(parser.Found(_("exitOnClose")));

   if (parser.Found(_("erase"), &sValue)) {
      skipOpeningDialogue = true;
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
         parser.AddUsageText("***** Error: Illegal erase value.\n");
#endif
         success = false;
      }
   }
   if (parser.Found(_("security"), &sValue)) {
      skipOpeningDialogue = true;
      if (sValue.CmpNoCase(_("Smart")) == 0) {
         deviceData->setSecurity(SEC_SMART);
      }
      else if (sValue.CmpNoCase(_("Image")) == 0) {
         deviceData->setSecurity(SEC_DEFAULT);
      }
      else if (sValue.CmpNoCase(_("Unsecured")) == 0) {
         deviceData->setSecurity(SEC_UNSECURED);
      }
      else {
#if (wxCHECK_VERSION(2, 9, 0))
         parser.AddUsageText("***** Error: Illegal security value.\n");
#endif
         success = false;
      }
   }

   if (parser.Found(_("vdd"), &sValue)) {
      skipOpeningDialogue = true;
      if (sValue.CmpNoCase(_("3V3")) == 0) {
         bdmOptions.targetVdd = BDM_TARGET_VDD_3V3;
      }
      else if (sValue.CmpNoCase(_("5V")) == 0) {
         bdmOptions.targetVdd = BDM_TARGET_VDD_5V;
      }
      else {
#if (wxCHECK_VERSION(2, 9, 0))
         parser.AddUsageText("***** Error: Illegal vdd value.\n");
#endif
         success = false;
      }
   }
   if (parser.Found(_("trim"), &sValue)) {
      skipOpeningDialogue = true;
      double    dValue;
      if (!sValue.ToDouble(&dValue)) {
#if (wxCHECK_VERSION(2, 9, 0))
         parser.AddUsageText("***** Error: Illegal trim value.\n");
#endif
         success = false;
      }
      deviceData->setClockTrimFreq(dValue * 1000);
   }
   else {
      trimFrequency = 0;
   }
   // Reset options
   if (parser.Found(_("reset"), &sValue)) {
      skipOpeningDialogue = true;
      unsigned long uValue=100000; // invalid so faults later

      int index1 = 0;
      int index2 = sValue.find(',');
      wxString t = sValue.substr(index1, index2-index1);
      if (!t.ToULong(&uValue, 10)) {
#if (wxCHECK_VERSION(2, 9, 0))
         parser.AddUsageText("***** Error: Illegal reset value.\n");
#endif
         success = false;
      }
      bdmOptions.resetDuration = uValue;

      index1 = index2+1;
      index2 = sValue.find(',', index1);
      t = sValue.substr(index1, index2-index1);
      if (!t.ToULong(&uValue, 10)) {
#if (wxCHECK_VERSION(2, 9, 0))
         parser.AddUsageText("***** Error: Illegal reset value.\n");
#endif
         success = false;
      }
      bdmOptions.resetReleaseInterval = uValue;

      index1 = index2+1;
      index2 = sValue.length();
      t = sValue.substr(index1, index2-index1);
      if (!t.ToULong(&uValue, 10)) {
#if (wxCHECK_VERSION(2, 9, 0))
         parser.AddUsageText("***** Error: Illegal reset value.\n");
#endif
         success = false;
      }
      bdmOptions.resetRecoveryInterval = uValue;
   }
   // Power options
   if (parser.Found(_("power"), &sValue)) {
      skipOpeningDialogue = true;
      unsigned long uValue=100000; // invalid so faults later

      int index1 = 0;
      int index2 = sValue.find(',');
      wxString t = sValue.substr(index1, index2-index1);
      if (!t.ToULong(&uValue, 10)) {
#if (wxCHECK_VERSION(2, 9, 0))
         parser.AddUsageText("***** Error: Illegal power value.\n");
#endif
         success = false;
      }
      bdmOptions.powerOffDuration = uValue;

      index1 = index2+1;
      index2 = sValue.length();
      t = sValue.substr(index1, index2-index1);
      if (!t.ToULong(&uValue, 10)) {
#if (wxCHECK_VERSION(2, 9, 0))
         parser.AddUsageText("***** Error: Illegal power value.\n");
#endif
         success = false;
      }
      bdmOptions.powerOnRecoveryInterval = uValue;
   }
   if (parser.Found(_("speed"), &sValue)) {
      skipOpeningDialogue = true;
      unsigned long uValue;
      if (!sValue.ToULong(&uValue, 10)) {
#if (wxCHECK_VERSION(2, 9, 0))
         parser.AddUsageText("***** Error: Illegal speed value.\n");
#endif
         success = false;
      }
      bdmOptions.interfaceFrequency = uValue;
   }
   if (parser.Found(_("port"), &sValue)) {
      skipOpeningDialogue = true;
      unsigned long uValue;
      if (!sValue.ToULong(&uValue, 10)) {
#if (wxCHECK_VERSION(2, 9, 0))
         parser.AddUsageText("***** Error: Illegal port value.\n");
#endif
         success = false;
      }
      shared->setGdbServerPort(uValue);
   }
   if (parser.Found(_("bdm"), &sValue)) {
      skipOpeningDialogue = true;
      shared->setBdmSerialNumber((const char *)sValue.ToAscii(), false);
   }
   if (parser.Found(_("requiredBdm"), &sValue)) {
      skipOpeningDialogue = true;
      shared->setBdmSerialNumber((const char *)sValue.ToAscii(), true);
   }
   if (!success) {
      parser.Usage();
   }
   else {
      shared->saveSettings(*appSettings);
      log.print("Success\n");
   }
   return success;
}

