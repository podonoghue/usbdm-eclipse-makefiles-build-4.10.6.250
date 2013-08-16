/*
 * main.cpp
 *
 *  Created on: 06/03/2011
 *      Author: podonoghue

\verbatim
Change History
-==================================================================================
| 16 Jul 2013 | Updated & refactored to use new I/O class                     - pgo
|        ???? | Created                                                       - pgo
+==================================================================================
\endverbatim

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

#include "GdbInOutSocket.h"

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

static DeviceData deviceData;

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
//   bool noLoad = false;
   bool listDevices = false;
   const char *deviceName = NULL;

   while (argc-- > 1) {
//      if (stricmp(argv[argc], "-noload")==0) {
//         noLoad = true;
//      }
//      else
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
   // Find device details from database
   DeviceDataBase *deviceDatabase = new DeviceDataBase;
   Logging::print( "Loading device database\n");
   try {
      deviceDatabase->loadDeviceData();
   } catch (MyException &exception) {
      Logging::print("doArgs() - Failed to load device database\n");
      return BDM_RC_DEVICE_DATABASE_ERROR;
   }
   Logging::print( "Loaded device database\n");
   if (listDevices) {
      int count = 0;
      std::vector<DeviceDataPtr>::const_iterator it;
      try {
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
      } catch (...) {
      }
      delete deviceDatabase;
      return BDM_RC_ERROR_HANDLED;
   }
   else {
      DeviceDataConstPtr devicePtr = deviceDatabase->findDeviceFromName(deviceName);
      if (devicePtr == NULL) {
         Logging::print("Failed to find device '%s' in database\n", deviceName);
         return BDM_RC_UNKNOWN_DEVICE;
      }
      deviceData = *devicePtr;
      delete deviceDatabase;
   }
   return BDM_RC_OK;
}

#ifdef _WIN32
#define NET_ERROR_NUM WSAGetLastError()
#else
#define NET_ERROR_NUM errno
#endif

void signalHandler(int sig) {
static bool error_in_progress = false;

   if (error_in_progress) {
      raise(sig);
   }
   error_in_progress = true;
   GdbInOutSocket::stopWaiting();
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

static USBDM_ErrorCode callBack(const char *msg, GdbMessageLevel level, USBDM_ErrorCode rc) {
   if (level >= M_ERROR) {
      displayDialogue(USBDM_GetErrorString(rc), msg, wxOK|wxICON_ERROR);
   }
   return rc;
}

//
// main
//
int main(int argc, char **argv) {
#ifdef __unix__
   // Load wxWindows Stub (for pop-up dialogues)
   (void)dlopen(WXSTUB_DLL_NAME, RTLD_NOW|RTLD_NODELETE);
#endif
#ifdef WIN32
   // Initiate use of the Winsock DLL by this process.
   WSADATA wsaData;
   if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
      fprintf(stderr, "Winsock initialization (WSAStartup()) failed. Error = %d\n", NET_ERROR_NUM);
      return (1);
   }
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

   if (signal(SIGINT, signalHandler) == SIG_IGN) {
      (void)signal(SIGINT, SIG_IGN);
   }

//   setDefaultWindowParent(FindEclipseWindowHwnd());

   USBDM_ErrorCode rc = doArgs(argc, argv);
   Logging::print("After doArgs()\n");
   if (rc != BDM_RC_OK) {
      Logging::print("USBDM Initialization failed, waiting for GDB to collect error\n");
   }

   GdbInOutSocket  *gdbInOut  = GdbInOutSocket::getGdbInOut();
   if (gdbInOut == NULL) {
      exit (-1);
   }
   Logging::print("After gdbInOut()\n");

   do {
      LOGGING;

      gdbInOut->restart();

      // Wait for GDB Connection
      int rc = gdbInOut->waitForConnection();
      Logging::print("waitForConnection() => %d\n", rc);
      if (rc == GDB_FATAL_ERROR) {
         break;
      }
      if (rc != GDB_OK) {
         break;
      }
      // Now do the actual processing of GDB messages
      gdbHandlerInit(gdbInOut, deviceData, callBack);
      gdbLoop(gdbInOut);
      gdbInOut->finish();
   } while (1);

   if (gdbInOut != NULL) {
      gdbInOut->finish();
      delete gdbInOut;
      gdbInOut = NULL;
   }

#ifdef WIN32
   WSACleanup();
#endif

   return 0;
}
