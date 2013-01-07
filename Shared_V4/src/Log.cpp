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
#include "Common.h"
#include "ApplicationFiles.h"
#include "Log.h"
#include "Version.h"
#include "USBDM_API.h"

#ifdef UNICODE
#undef UNICODE
#endif

#ifdef LOG

#define ADDRESS_SIZE_MASK    (3<<0)
#define DISPLAY_SIZE_MASK    (3<<2)


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
      print("Entry ===============\n");
   }
}
/*!  \brief Record exit from a function
 *
 */
Logging::~Logging(){
   if ((when==exit)||(when==both)) {
      print("Exit ================\n");
   }
   currentLogLevel = lastLogLevel;
   currentName     = lastName;
   indent--;
}
#if defined(USBDMDSC_DLL_EXPORTS) || defined(USBDMMPC_DLL_EXPORTS)
// Dummy - not used by DSC
void Logging::openLogFile(const char *logFileName, const char *description){
}
#else
/*!  \brief Open log file
 *
 *  @param logFileName - Name of log file
 *  @param description - Description written to log file
 *
 *  @note logging is enabled and timestamp disabled
 */
void Logging::openLogFile(const char *logFileName, const char *description){
   time_t time_now;

   indent = 0;
   currentName = NULL;
   if (logFile != NULL) {
      fclose(logFile);
   }
   logFile = openApplicationFile(logFileName, "wt");
#ifdef _WIN32
   if (logFile == NULL) {
      logFile = fopen("C:\\Documents and Settings\\PODonoghue\\Application Data\\usbdm\\xx.log", "wt");
//         print("openLogFile() - failed to open %s\n", logFileName);
   }
#endif
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
#endif
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
   return indent - currentLogLevel;
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
