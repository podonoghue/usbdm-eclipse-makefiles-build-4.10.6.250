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

static const int pollIntervalFast = 100;      // ms
static const int pollIntervalSlow = 1000;     // ms
static unsigned  pollInterval     = pollIntervalFast;

static USBDM_ErrorCode gdbLoop(GdbInOut *gdbInOut) {
   LOGGING;
   Logging::print("gdbLoop()...\n");

   const GdbPacket *packet;
   unsigned pollCount = 0;
   GdbTargetStatus targetStatus = T_UNKNOWN;

   do {
      do {
         // Process packets from GDB until idle
         packet = gdbInOut->getGdbPacket();
         if (packet != NULL) {
            USBDM_ErrorCode rc = doGdbCommand(packet);
            if (rc != BDM_RC_OK) {
               return rc;
            }
         pollInterval = pollIntervalFast;
         }
      } while (packet != NULL);

      if (pollCount++ == pollInterval) {
         pollCount = 0;
         targetStatus = gdbPollTarget();
         if (targetStatus == T_RUNNING) {
            pollInterval = pollIntervalFast;
         }
         else {
            pollInterval = pollIntervalSlow;
         }
      }

      milliSleep(1 /* ms */);

   // Keep going until loose target or GDB
   } while ((targetStatus != T_NOCONNECTION) && (!gdbInOut->isEOF()));

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

   USBDM_ErrorCode rc = doArgs(argc, argv);
   if (rc != BDM_RC_OK) {
      gdbReportError(rc);
      exit (-1);
   }
   Logging::print("After doArgs\n");

   shared = SharedPtr(new Shared(TARGET_TYPE));

   rc = shared->initBdm();
   if (rc != BDM_RC_OK) {
      gdbReportError(rc);
      exit (-1);
   }
   Logging::print("After shared->initBdm()\n");
   //   setDefaultWindowParent(FindEclipseWindowHwnd());

   GdbInOutPipe  *gdbInOut  = GdbInOutPipe::getGdbInOut();
   Logging::print("After GdbInOutPipe::getGdbInOut()\n");

   // Redirect stdout to stderr
   dup2(2,1);

   if (gdbInOut == NULL) {
      // Quit immediately as we have no way to convey error to gdb
      gdbReportError(BDM_RC_FAIL);
      exit (-1);
   }
   Logging::print("After gdbInOut()\n");

   // Now do the actual processing of GDB messages
   gdbHandlerInit(gdbInOut, *shared->getCurrentDevice());
   gdbLoop(gdbInOut);

   return 0;
}

