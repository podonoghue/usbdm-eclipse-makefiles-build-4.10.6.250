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

#include "Common.h"
#include "Log.h"

#include "GdbSerialConnection.h"

#include "USBDM_API.h"
#include "Names.h"
#include "DeviceData.h"
#include "GdbHandler.h"
#include "ProgressTimer.h"
#include "Utils.h"

#include "GdbInput.h"
#include "GdbOutput.h"

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
static ProgressTimer *progressTimer;

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
         "       -noload - Suppress loading of code to flash memory\n"
         "       -d      - list devices in database\n");
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
   bool noLoad = false;
   bool listDevices = false;
   const char *deviceName = NULL;

   while (argc-- > 1) {
      if (stricmp(argv[argc], "-noload")==0) {
         noLoad = true;
      }
      else if (stricmp(argv[argc], "-D")==0) {
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

void ex_program(int sig) {
   (void) signal(SIGINT, ex_program);
}

//
// main
//
int main(int argc, char **argv) {
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
   (void) signal(SIGINT, SIG_IGN);

//   setDefaultWindowParent(FindEclipseWindowHwnd());

   if (progressTimer != NULL) {
      delete progressTimer;
   }
   progressTimer = new ProgressTimer(NULL, 1000);
   progressTimer->restart("Initializing...");

   Logging::print("Starting, Time = %f\n", progressTimer->elapsedTime());
   GdbInput  *gdbInput  = new GdbInput(stdin);
   Logging::print("After gdbInput, Time = %f\n", progressTimer->elapsedTime());
   GdbOutput *gdbOutput = new GdbOutput(stdout);
   Logging::print("After gdbOutput, Time = %f\n", progressTimer->elapsedTime());

   // Redirect stdout to stderr
   dup2(2,1);

   if ((gdbOutput == NULL) || (gdbInput == NULL) || !gdbInput->createThread()) {
      // Quit immediately as we have no way to convey error to gdb
      reportError(BDM_RC_FAIL);
      exit (-1);
   }
   Logging::print("After createThread, Time = %f\n", progressTimer->elapsedTime());
   USBDM_ErrorCode rc = doArgs(argc, argv);
   Logging::print("After doArgs, Time = %f\n", progressTimer->elapsedTime());
   if (rc != BDM_RC_OK) {
      Logging::print("USBDM Initialization failed, waiting for GDB to collect error\n");
      reportErrorAndQuit(rc);
   }
   // Now do the actual processing of GDB messages
   handleGdb(gdbInput, gdbOutput, deviceData, progressTimer);
   exitProgram(BDM_RC_OK);
}
