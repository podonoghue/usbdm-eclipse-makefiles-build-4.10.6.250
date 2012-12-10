/*
 * GdbOutput.h
 *
 *  Created on: 23/04/2012
 *      Author: PODonoghue
 */

#ifndef GDBOUTPUT_H_
#define GDBOUTPUT_H_

#include <stdio.h>

class GdbOutput {
public:
   enum ErrorType {E_Fatal, E_Memory};

private:
   FILE             *pipeOut;
   const char       *errorMessage;
   int               gdbChecksum;
   unsigned          gdbCharCount;
   char             *gdbPtr;
   char              gdbBuffer[1000];

public:
   GdbOutput(FILE *out);
   // Add values to gdbBuffer
   void putGdbPreamble(char marker='$');
   void putGdbChar(char ch);
   void putGdbHex(const unsigned char *buffer, unsigned size);
   void putGdbString(const char *s, int size=-1);
   void putGdbHexString(const char *s, int size=-1);
   int  putGdbPrintf(const char *format, ...);
   void putGdbChecksum(void);
   void putGdbPostscript(void);

   // Send data to GDB
   void flushGdbBuffer(void);
   void sendGdbBuffer(void);
   void sendGdbHex(const unsigned char *buffer, unsigned size);
   void sendGdbString(const char *buffer, int size=-1);
   void sendGdbHexString(const char *id, const char *buffer, int size=-1);
   void sendGdbNotification(const char *buffer, int size=-1);
   void sendErrorMessage(ErrorType errorType, const char *msg);
   void sendErrorMessage(unsigned value);
   void sendAck(char ackValue='+');
   void close(void) {
      if (pipeOut != NULL) {
         fclose(pipeOut);
         pipeOut = NULL;
      }
   }
private:
   void txGdbPkt(void);
};

#endif /* GDBOUTPUT_H_ */
