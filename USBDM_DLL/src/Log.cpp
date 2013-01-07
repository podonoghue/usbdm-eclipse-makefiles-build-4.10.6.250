/*! \file
    \brief Provides Debug logging facilities

    Log.cpp

    \verbatim
    Turbo BDM Light - message log
    Copyright (C) 2005  Daniel Malik

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
   +=========================================================================================
   |  1 Dec 2012 | Changed logging extensively                                - pgo - V4.10.4
   | 16 Nov 2009 | Relocated log file directory for Vista.                    - pgo
   |  5 Nov 2009 | Completed restructure for V1                               - pgo
   | 22 May 2009 | Added Speed options for CFVx & JTAG targets                - pgo
   |  3 Apr 2009 | Re-enabled connection retry on successful connect          - pgo
   | 30 Mar 2009 | Changed timing of reset/bkgd release in extendedConnect()  - pgo
   | 27 Dec 2008 | Added extendedConnect() and associated changes             - pgo
   +=========================================================================================
   \endverbatim
 */
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "Log.h"
#include "Version.h"
#include "USBDM_API.h"

#ifdef UNICODE
#undef UNICODE
#endif

#ifdef LOG

#define ADDRESS_SIZE_MASK    (3<<0)
#define DISPLAY_SIZE_MASK    (3<<2)

#define CONFIG_WITH_SLASHES "/" CONFIGURATION_DIRECTORY_NAME "/"

#ifdef __unix__
static FILE *openApplicationFile(const char *fileName) {

   char tempPathname[64];
   int tempFiledescriptor = -1;
   FILE *fp = NULL;
   strcpy(tempPathname, "/var/tmp/usbdm-XXXXXX"); // Filename template
   tempFiledescriptor=mkstemp(tempPathname);
   if (tempFiledescriptor >=0)
      fp = fdopen(tempFiledescriptor, "w"); // Convert to stream
   return fp;
}
#endif

#ifdef WIN32
#define _WIN32_IE 0x0500      //!< Required for later system calls.
#define _WIN32_WINNT 0x0500   //!< Required for later system calls.
#include <shlobj.h>
//! Obtain the path of the configuration directory or file
//!
//! @param configFilePath - Buffer of size MAX_PATH to return path in.
//! @param filename - Configuration file name to append to configuration directory path.\n
//!                   If NULL then the configuration directory (with trailing \) is returned.
//!
//! @return error code - BDM_RC_OK => success \n
//!                    - BDM_RC_FAIL => failure
//!
//! @note The configuration directory will be created if it doesn't aleady exist.
//!
static int getApplicationDirectoryPath(const char **_configFilePath, const char *filename) {
   static char configFilePath[MAX_PATH];

   memset(configFilePath, '\0', MAX_PATH);
   *_configFilePath = configFilePath;
   if (filename == NULL)
      filename = "\\";

   // Obtain local app folder (create if needed)
   if (SHGetFolderPath(NULL,
         CSIDL_APPDATA|CSIDL_FLAG_CREATE,
         NULL,
         0,
         configFilePath) != S_OK)
      return BDM_RC_FAIL;

   // Append application directory name
   if (strlen(configFilePath)+sizeof(CONFIG_WITH_SLASHES) >= MAX_PATH)
      return BDM_RC_FAIL;

   strcat(configFilePath, CONFIG_WITH_SLASHES);

   // Check if folder exists or can be created
   if ((GetFileAttributes(configFilePath) == INVALID_FILE_ATTRIBUTES) &&
         (SHCreateDirectoryEx( NULL, configFilePath, NULL ) != S_OK))
      return BDM_RC_FAIL;

   // Append filename if non-NULL
   if (strlen(configFilePath)+strlen(filename) >= MAX_PATH)
      return BDM_RC_FAIL;

   strcat(configFilePath, filename);

   Logging::print("getApplicationDirectoryPath()=\'%s\'\n", configFilePath );
   return BDM_RC_OK;
}

//! Opens configuration file
//!
//! @param fileName   - Name of file (without path)
//!
//! @return file handle or NULL on error
//!
//! @note Attempts to open from:
//! - Application data directory (e.g. %APPDATA%\usbdm, $HOME/.usbdm)
//!
FILE *openApplicationFile(const char *fileName) {
   FILE *configFile = NULL;
   const char *configFilePath;
   int rc;

   rc = getApplicationDirectoryPath(&configFilePath, fileName);
   if (rc == BDM_RC_OK)
      configFile = fopen(configFilePath, "wt");

   if (configFile != NULL) {
      Logging::print("openApplicationFile() - Opened \'%s\' from APPDATA directory\n", fileName);
      return configFile;
   }
   return configFile;
}
#endif

const char *Logging::currentName       = NULL;  //!< Name of current function
FILE       *Logging::logFile           = NULL;  //!< File handle for logging file
int         Logging::indent            = 0;     //!< Indent level for listing
int         Logging::currentLogLevel   = 100;   //!< Level below which to log messages
bool        Logging::loggingEnabled    = true;  //!< Logging on/off
bool        Logging::timestampEnabled  = false; //!< Timestamp messages

/*!  \brief Object to allow logging the execution of a function
 *
 *  @param name Name of the function to use in messages
 *  @param when Whether to log entry/exit etc of this function
 */
Logging::Logging(const char *name, When when) : name(name), when(when) {
   indent++;
   lastName      = currentName;
   lastLogLevel  = currentLogLevel;
   currentName   = name;
   if ((when==entry)||(when==both)) {
      print("Entry ================ (i=%d, l=%d)\n", indent, currentLogLevel);
   }
}
/*!  \brief Record exit from a function
 *
 */
Logging::~Logging(){
   if ((when==exit)||(when==both)) {
      print("Exit ================ (i=%d, l=%d)\n", indent, currentLogLevel);
   }
   currentLogLevel = lastLogLevel;
   currentName     = lastName;
   indent--;
}
/*!  \brief Open log file
 *
 *  @param description - Description written to log file
 *
 *  @note logging is enabled and timestamp disabled
 */
void Logging::openLogFile(const char *description){
   time_t time_now;

   indent = 0;
   currentName = NULL;
   if (logFile != NULL) {
      fclose(logFile);
   }
   logFile = openApplicationFile("usbdm.log");
   if (logFile == NULL) {
      return;
   }
   loggingEnabled   = true;
   timestampEnabled = false;
   fprintf(logFile, "%s - %s, Compiled on %s, %s.\n",
         description,
         USBDM_VERSION_STRING, __DATE__,__TIME__);

   time(&time_now);
   fprintf(logFile, "Log file created on: %s"
         "==============================================\n\n", ctime(&time_now));
}
/*! \brief Turns logging on or off
 *
 *  @param value - true/false => on/off logging
 */
void Logging::enableLogging(bool value) {
   loggingEnabled = value;
}
/*!  \brief Set logging level relative to current level
 *
 *  @param level - level to log below \n
 *         A 0 value suppresses logging below the current level.
 */
void Logging::setLoggingLevel(int level) {
   currentLogLevel = indent + level;
}
/*!  \brief Get logging level relative to current level
 *
 */
int Logging::getLoggingLevel() {
   return currentLogLevel - indent;
}
/*! \brief Turns timestamp on or off
 *
 *  @param value - true/false => on/off timestamp
 */
void Logging::enableTimestamp(bool enable) {
   timestampEnabled = enable;
}
/*!  \brief Close the log file
 *
 */
void Logging::closeLogFile() {
   if (logFile == NULL) {
      return;
   }
   time_t time_now;
   time(&time_now);

   loggingEnabled = true;
   fprintf(logFile,
         "\n==========================================\n"
         "End of log file: %s\r", ctime(&time_now));
   loggingEnabled = false;

   fclose(logFile);
   logFile = NULL;
}
/*! \brief Provides a print function which prints data into a log file.
 *
 *  @param format Format and parameters as for printf()
 */
void Logging::printq(const char *format, ...) {
   va_list list;
   if ((logFile == NULL) || (!loggingEnabled) || (indent > currentLogLevel)) {
      return;
   }
   if (format == NULL) {
      format = "printq() - Error - empty format string!\n";
   }
   va_start(list, format);
   vfprintf(logFile, format, list);
   va_end(list);
   fflush(logFile);
}

/*! \brief Get time as milliseconds
 *
 *  @return time value
 */
static double getTimeStamp()
{
   struct timeval tv;
   if (gettimeofday(&tv, NULL) != 0) {
      return 0;
   }
   return (tv.tv_sec*1000)+(tv.tv_usec/1000.0);
}

/*! \brief Provides a print function which prints data into a log file.
 *
 *  @param format Format and parameters as for printf()
 */
void Logging::print(const char *format, ...) {
   va_list list;
   if ((logFile == NULL) || (!loggingEnabled) || (indent > currentLogLevel)) {
      return;
   }
   if (format == NULL) {
      format = "print() - Error - empty format string!\n";
   }
   if (timestampEnabled) {
      fprintf(logFile, "%04.3f: ",getTimeStamp());
   }
   fprintf(logFile, "%*s", 3*indent, "");
   if (currentName!=NULL) {
      fprintf(logFile, "%s(): ", currentName);
   }
   va_start(list, format);
   vfprintf(logFile, format, list);
   va_end(list);
   fflush(logFile);
}
/*! \brief Provides a print function which prints data into a log file.
 *
 *  @param format Format and parameters as for printf()
 */
void Logging::error(const char *format, ...) {
   va_list list;
   if (logFile == NULL) {
      return;
   }
   if (format == NULL) {
      format = "error() - Error - empty format string!\n";
   }
   if (timestampEnabled) {
      fprintf(logFile, "%04.3f: ",getTimeStamp());
   }
   fprintf(logFile, "%*s", 3*indent, "");
   if (currentName!=NULL) {
      fprintf(logFile, "%s(): ", currentName);
   }
   va_start(list, format);
   vfprintf(logFile, format, list);
   va_end(list);
   fflush(logFile);
}
/*! \brief Print a formatted dump of binary data in Hex
 *
 * @param data         Pointer to data to print
 * @param size         Number of bytes to print
 * @param startAddress Address to display against values
 * @param organization Size of data & address increment
 */
void Logging::printDump(unsigned const char *data,
      unsigned int size,
      unsigned int startAddress,
      unsigned int organization) {

   unsigned int addressShift = 0;
   unsigned int elementSize  = 1;
   unsigned int address      = startAddress;
   bool         littleEndian = (organization & DLITTLE_ENDIAN)!= 0;

   if ((logFile == NULL) || (!loggingEnabled) || (indent > currentLogLevel)) {
      return;
   }
   switch (organization&DISPLAY_SIZE_MASK){
      case BYTE_DISPLAY:
         elementSize  = 1;
         break;
      case WORD_DISPLAY:
         elementSize  = 2;
         break;
      case LONG_DISPLAY:
         elementSize  = 4;
         break;
   }
   switch (organization&ADDRESS_SIZE_MASK){
      case BYTE_ADDRESS:
         address = startAddress;
         addressShift = 0;
         break;
      case WORD_ADDRESS:
         address      = startAddress<<1;
         addressShift = 1;
         break;
   }
   //      print("org=%x, sz=%d, es=%d, as=%d\n", organization, size, elementSize, addressShift);
   int eolFlag = true;
   while(size>0) {
      if (eolFlag) {
         eolFlag = false;
         if (timestampEnabled) {
            fprintf(logFile, "%04.3f: ",getTimeStamp());
         }
         fprintf(logFile, "%*s", 3*indent, "");
         fprintf(logFile,"   %8.8X:", address>>addressShift);
      }
      unsigned char dataTemp[4];
      unsigned int sub;
      for(sub=0; (sub<elementSize) && (size>0); sub++) {
         dataTemp[sub] = *data++;
         address++;
         size--;
         if ((address&0xF) == 0)
            eolFlag = true;
      }
      unsigned int indx;
      if (littleEndian) {
         indx=sub-1;
         do {
            fprintf(logFile, "%02X", dataTemp[indx]);
         } while (indx-- > 0) ;
      }
      else {
         for(indx=0; indx<sub; indx++) {
            fprintf(logFile, "%02X", dataTemp[indx]);
         }
      }
      fprintf(logFile," ");
      if (eolFlag)
         fprintf(logFile,"\n");
   }
   if (!eolFlag)
      fprintf(logFile,"\n");
   fflush(logFile);
}

#endif // LOG
