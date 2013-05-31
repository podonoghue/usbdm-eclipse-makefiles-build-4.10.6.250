
/*! \file
    \brief Header file for Log.c (Logging features)
*/
#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>
#include <stdarg.h>
#include "Version.h"

#define BYTE_ADDRESS    (0<<0)  // Addresses identify a byte in memory
#define WORD_ADDRESS    (1<<0)  // Addresses identify a word in memory
#define BYTE_DISPLAY    (0<<2)  // Display as bytes (8-bits)
#define WORD_DISPLAY    (1<<2)  // Display as words (16-bits)
#define LONG_DISPLAY    (2<<2)  // Display as longs (32-bits)
#define DBIG_ENDIAN     (0<<4)
#define DLITTLE_ENDIAN  (1<<4)

#ifndef LOG
class Logging {
public:
   enum When {neither, entry, exit, both};
   Logging(const char *name, When when=both) {};
   ~Logging() {};
   static void openLogFile(const char *logFileName, const char *description="") {}
   static void closeLogFile() {}
   static void enableLogging(bool value) {}
   static void setLoggingLevel(int level) {}
   static int  getLoggingLevel() { return 0; }
   static void error(const char *format, ...) {}
   static void print(const char *format, ...) {}
   static void printq(const char *format, ...) {}
   static void printDump(unsigned const char *data,
                         unsigned int size,
                         unsigned int startAddress=0x0000,
                         unsigned int organization=BYTE_ADDRESS|BYTE_DISPLAY) {}
   static FILE* getLogFileHandle() { return (FILE*)0; }
   static void setLogFileHandle(FILE *logFile) {}
   static void enableTimestamping(bool enable=true) {}
};
#define LOGGING_Q (void)0
#define LOGGING_E (void)0
#define LOGGING   (void)0
#else // LOG
class Logging {
public:
   enum When {neither, entry, exit, both};
private:
   static FILE  *logFile;
   static bool   loggingEnabled;
   static bool   timestampEnabled;
   static int    indent;
   static int    currentLogLevel;
   static const char *currentName;
   const  char  *name;
   const  char  *lastName;
   int    lastLogLevel;
   When   when;
public:
   Logging(const char *name, When when=both);
   ~Logging();
   static void openLogFile(const char *logFileName, const char *description="");
   static void closeLogFile();
   static void enableLogging(bool value = true);
   static void enableTimestamp(bool enable = true);
   static void setLoggingLevel(int level);
   static int  getLoggingLevel();
   static void error(const char *format, ...);
   static void print(const char *format, ...);
   static void printq(const char *format, ...);
   static void printDump(unsigned const char *data,
                         unsigned int size,
                         unsigned int startAddress=0x0000,
                         unsigned int organization=BYTE_ADDRESS|BYTE_DISPLAY);
   static FILE* getLogFileHandle() {
      return logFile;
   }
   static void setLogFileHandle(FILE *logFile) {
      Logging::logFile = logFile;
   }
};
#define LOGGING_Q Logging log(__FUNCTION__, Logging::neither)
#define LOGGING_E Logging log(__FUNCTION__, Logging::entry)
#define LOGGING   Logging log(__FUNCTION__, Logging::both)
#endif
#endif // _LOG_H_
