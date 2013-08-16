/*
 * main.cpp
 *
 *  Created on: 06/03/2011
 *      Author: podonoghue
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <unistd.h>
#include <tr1/memory>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#ifdef __unix__
#include <dlfcn.h>
#define WXSTUB_DLL_NAME "libusbdm-wxStub.so"
#endif

#include "Common.h"
#include "Log.h"

#include "USBDM_API.h"
#include "Names.h"
#include "DeviceData.h"
#include "GdbHandler.h"
#include "ProgressTimer.h"
#include "Utils.h"

#include "GdbHandler.h"

#include "GdbInOutPipe.h"

#include "Shared.h"

#include "wxPlugin.h"
#include "FindWindow.h"

#if TARGET==CFV1
#define TARGET_TYPE T_CFV1
#elif TARGET==CFVx
#define TARGET_TYPE T_CFVx
#elif TARGET==ARM
#define TARGET_TYPE T_ARM
#else
#error "Unhandled case"
#endif

static SharedPtr shared;

#ifndef _WIN32_
#define stricmp(x,y) strcasecmp((x),(y))
#endif

//! Print usage message
//!
void usage(void) {
   fprintf(stderr,
         "Usage: \n"
         "usbdm-gdbServer args...\n"
         "Args = device  - device to load (use -d to obtain device names)\n"
         "       -d      - list devices in database\n");
//   "       -noload - Suppress loading of code to flash memory\n"
}

//! Process command line args
//!
//! @param argc - count of args
//! @param argv - the actual arguments
//!
//! @return error code
//!
USBDM_ErrorCode doArgs(int argc, char **argv) {
   LOGGING;
   bool listDevices = false;
   const char *deviceName = NULL;

   while (argc-- > 1) {
    	  if (stricmp(argv[argc], "-D")==0) {
         // List targets
         listDevices = true;
      }
      else {
         // Assume device name
         deviceName = argv[argc];
      }
   }
   if ((deviceName == NULL) && !listDevices) {
      fprintf(stderr, "No device specified\n");
      Logging::print("No device specified\n");
      return BDM_RC_ILLEGAL_PARAMS;
   }
   if (listDevices) {
      int count = 0;
      std::vector<DeviceDataPtr>::const_iterator it;
      DeviceDataBase *deviceDatabase = shared->getDeviceDataBase();
      for (it = deviceDatabase->begin(); it != deviceDatabase->end(); it++) {
         fprintf(stderr, "%s,\t", (*it)->getTargetName().c_str());
         if (++count == 3) {
            count = 0;
            fprintf(stderr, "\n");
         }
      }
      if (count != 0) {
         fprintf(stderr, "\n");
      }
      return BDM_RC_ERROR_HANDLED;
   }
   else {
      // Find device details from database
      USBDM_ErrorCode rc = shared->setCurrentDeviceByName(deviceName);
      if (rc != BDM_RC_OK) {
         return rc;
      }
      Logging::print( "Loaded device description\n");
   }
   return BDM_RC_OK;
}

void signalHandler(int sig) {
static bool error_in_progress = false;

   if (error_in_progress) {
      raise(sig);
   }
   error_in_progress = true;
   fprintf(stderr, "Aborting wait\n");
   signal(SIGINT, signalHandler);
   error_in_progress = false;
}

USBDM_ErrorCode serverError;

static USBDM_ErrorCode callBack(const char *msg, GdbMessageLevel level, USBDM_ErrorCode rc) {
   if (level >= M_ERROR) {
      displayDialogue(USBDM_GetErrorString(rc), msg, wxOK|wxICON_ERROR);
      serverError = rc;
   }
   return rc;
}

static const unsigned  POLL_INTERVAL = 10; // ms

static USBDM_ErrorCode gdbLoop(GdbInOut *gdbInOut) {
   LOGGING;
   Logging::print("gdbLoop()...\n");

   const GdbPacket *packet;
   unsigned pollCount = 0;
   GdbTargetStatus targetStatus = T_UNKNOWN;

   serverError = BDM_RC_OK;

   do {
      do {
         // Process packets from GDB until idle
         packet = gdbInOut->getGdbPacket();
         if (packet != NULL) {
            USBDM_ErrorCode rc = doGdbCommand(packet);
            if (rc != BDM_RC_OK) {
               return rc;
            }
         }
      } while (packet != NULL);

      // Get current target status (w/o polling)
      targetStatus = getGdbTargetStatus();
      switch (targetStatus) {
         case T_RUNNING:
         case T_SLEEPING:
            if (pollCount++ >= POLL_INTERVAL) {
               // Actually poll the target
               pollCount = 0;
               targetStatus = gdbPollTarget();
            }
            break;
         case T_NOCONNECTION:
            break;
         case T_UNKNOWN:
         case T_HALT:
            // Don't poll while not running
            milliSleep(1 /* ms */);
            break;
      }

   // Keep going until loose target or GDB
   } while ((targetStatus != T_NOCONNECTION) && (serverError == BDM_RC_OK) && (!gdbInOut->isEOF()));

   Logging::print("gdbLoop() - Exiting GDB Loop\n");
   return BDM_RC_OK;
}

//
// main
//
int main(int argc, char **argv) {
#ifdef __unix__
   // Load wxWindows Stub (for pop-up dialogues)
   (void)dlopen(WXSTUB_DLL_NAME, RTLD_NOW|RTLD_NODELETE);
#endif

#ifdef LOG
   char buff[1000];
   if (getUserDataDir(buff, sizeof(buff)) != 0) {
      strcpy(buff, "c:");
   }
   strcat(buff, "/gdbServer.log");
   FILE *errorLog = fopen(buff, "wt");
   Logging::setLogFileHandle(errorLog);
#endif
   Logging::setLoggingLevel(100);
   LOGGING;

#ifdef LOG
   Logging::print("Args = ");
   for (int index=0; index<argc; index++) {
      Logging::printq("%s ", argv[index]);
   }
   Logging::printq("\n");
#endif
   if (signal(SIGINT, signalHandler) == SIG_IGN) {
      (void)signal(SIGINT, SIG_IGN);
   }

   shared = SharedPtr(new Shared(TARGET_TYPE));

   USBDM_ErrorCode rc = doArgs(argc, argv);
   if (rc != BDM_RC_OK) {
      Logging::print("Error %s\n", USBDM_GetErrorString(rc));
      exit (-1);
   }
   Logging::print("After doArgs\n");

   rc = shared->initBdm();
   if (rc != BDM_RC_OK) {
      Logging::print("Error %s\n", USBDM_GetErrorString(rc));
      exit (-1);
   }
   Logging::print("After shared->initBdm()\n");
   //   setDefaultWindowParent(FindEclipseWindowHwnd());

   GdbInOutPipe  *gdbInOut  = GdbInOutPipe::getGdbInOut();
   Logging::print("After GdbInOutPipe::getGdbInOut()\n");

   // Redirect stdout to stderr
   dup2(2,1);

   if (gdbInOut == NULL) {
      Logging::print("Error gdbInOut() creation failed\n");
      exit (-1);
   }
   Logging::print("After gdbInOut()\n");

   // Now do the actual processing of GDB messages
   gdbHandlerInit(gdbInOut, *shared->getCurrentDevice(), callBack);
   gdbLoop(gdbInOut);

   gdbInOut->finish();
   delete gdbInOut;

   return 0;
}

