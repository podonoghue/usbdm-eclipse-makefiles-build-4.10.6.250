/*
 * CFUnlockerApp.c
 *
 *  Created on: 23/10/2010
 *      Author: podonoghue
 */

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/stdpaths.h>
#endif

#include "USBDM_API.h"
#include "Log.h"
#include "CFUnlockerApp.h"
#include "CFUnlockerDialogue.h"
#include "CFUnlockerPanel.h"

const TargetType_t targetType = T_JTAG;

#if TARGET==CFVx
const char caption[] = "USBDM Coldfire Unlock Utility";
const char *logFilename("FlashProgrammer_CFVx.log");
#elif TARGET==MC56F80xx
#include "USBDM_DSC_API.h"
const char caption[] = "USBDM MC56F80xx Unlock Utiltiy";
const char *logFilename("FlashProgrammer_DSC.log");
#else
#error "TARGET must be set"
#endif

/*
 * Application instance implementation
 */
IMPLEMENT_APP( CFUnlockerApp )

/*
 * CFUnlockerApp type definition
 */
IMPLEMENT_CLASS( CFUnlockerApp, wxApp )

/*
 * CFUnlockerApp event table definition
 */
BEGIN_EVENT_TABLE( CFUnlockerApp, wxApp )
END_EVENT_TABLE()

/*
 * Constructor for CFUnlockerApp
 */
CFUnlockerApp::CFUnlockerApp()
{
    Init();
    wxGetApp().SetAppName(_("usbdm"));
    Logging::openLogFile("CFUnlocker.log");

#ifndef _WIN32
   ((wxStandardPaths&)wxStandardPaths::Get()).SetInstallPrefix(_("/usr/local"));
#endif
}

/*
 * Member initialization
 */
void CFUnlockerApp::Init()
{
}

/*
 * Initialization for CFUnlockerApp
 */
bool CFUnlockerApp::OnInit()
{
   Logging::setLoggingLevel(100);
   Logging log("CFUnlockerApp::OnInit()");

   USBDM_Init();

   CFUnlockerDialogue *dialogue = new CFUnlockerDialogue(targetType, caption);
   dialogue->Create(NULL);
   dialogue->ShowModal();
   dialogue->Destroy();

   return false; // Terminate app on return
}

/*
 * Cleanup for CFUnlockerApp
 */
int CFUnlockerApp::OnExit()
{
   return wxApp::OnExit();
}
