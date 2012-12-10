/*! \file
    \brief Handles GDB output

    GdbOutput.cpp

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
   -==================================================================================
   | 23 Apr 2012 | Created                                                       - pgo
   +==================================================================================
   \endverbatim
*/

#include <stdarg.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#endif

#include "GdbOutput.h"
#include "Log.h"

GdbOutput::GdbOutput(FILE *out) :
   errorMessage(NULL),
   gdbChecksum(0),
   gdbCharCount(0),
   gdbPtr(gdbBuffer)
{
   int outHandle = dup(fileno(out));
   pipeOut = fdopen(outHandle, "wb");

#ifdef _WIN32
   setmode( _fileno( pipeOut ), _O_BINARY );
   setvbuf ( pipeOut,  NULL, _IONBF , 0 );
#else
   setvbuf ( pipein,  NULL, _IONBF , 0 );
#endif
}

//!
//! Convert a binary value to a HEX char
//!
//! @param num - number o convert (0x0 - 0xF)
//!
//! @return converted char ('0'-'9' or 'A' to 'F') - no error checks!
//!
static char hexChar(int num) {
const char chars[] = "0123456789ABCDEF";
   return chars[num&0x0F];
}

//! Add character to gdb Tx buffer
//!
//! @param ch - char to add
//!
void GdbOutput::putGdbChar(char ch) {
   gdbChecksum   += ch;
   gdbCharCount  += 1;
   if (gdbCharCount > sizeof(gdbBuffer)) {
      Logging::print( "putGdbChar(): buffer overflow\n");
      exit(-1);
   }
   *gdbPtr++      = ch;
}

//! Add bytes to gdb Tx buffer as Hex character pairs
//!
//! @param count Size of buffer
//! @param buff  Buffer to add
//!
void GdbOutput::putGdbHex(const unsigned char *buffer, unsigned size) {
   unsigned index;
   for (index=0; index<size; index++) {
      putGdbChar(hexChar(buffer[index]>>4));
      putGdbChar(hexChar(buffer[index]));
   }
}

//! Add a string to gdb Tx buffer
//!
//! @param s    - '\0' terminated string to add
//! @param size - maximum size to send (-1 ignored)
//!
void GdbOutput::putGdbString(const char *s, int size) {
   while ((*s != '\0') && (size != 0)) {
      putGdbChar(*s++);
      if (size > 0)
         size--;
   }
}

//! Add a string to gdb Tx buffer as a series of hex digit pairs
//!
//! @param s    - '\0' terminated string to add
//! @param size - maximum size to send (-1 ignored)
//!
void GdbOutput::putGdbHexString(const char *s, int size) {
   while ((*s != '\0') && (size != 0)) {
      putGdbChar(hexChar((*s)>>4));
      putGdbChar(hexChar(*s++));
      if (size > 0)
         size--;
   }
}

//! Print to gdb Tx buffer in 'printf' manner
//!
//! @param format - print control string
//! @param ...    - argument list
//!
//! @return number of characters written to buffer
//!         -ve on error
//!
int GdbOutput::putGdbPrintf(const char *format, ...) {
   char buff[200];
   va_list list;
   va_start(list, format);
   int numChars = vsprintf(buff, format, list);
   for (int index=0; index<numChars; index++ ) {
      putGdbChar(buff[index]);
   }
   return numChars;
}

//! Set up gdb Tx buffer
//!
//! @param marker - pkt marker to use
//!
void GdbOutput::putGdbPreamble(char marker) {
   gdbPtr = gdbBuffer;
   putGdbChar(marker);
   gdbChecksum  = 0;
   gdbCharCount = 0;
}

//! Adds checksum to buffer
//!
void GdbOutput::putGdbChecksum(void) {
   int checksum = gdbChecksum & 0xFF;
   putGdbChar('#');
   putGdbChar(hexChar(checksum >> 4));
   putGdbChar(hexChar(checksum % 16));
   putGdbChar('\0');
}

//!
//! txGdbPkt - transmit the gdbBuffer to GDB
//!
void GdbOutput::txGdbPkt(void) {
   (void)fwrite(gdbBuffer, 1, gdbCharCount, pipeOut);
   (void)fflush(pipeOut);
   Logging::print( "txGdbPkt()=>:%03d%*s\n", gdbCharCount, gdbCharCount, gdbBuffer);
}

//!
//! flushGdbBuffer - flush gdbBuffer (in background thread)
//!
void GdbOutput::flushGdbBuffer(void) {
   txGdbPkt();
}

//!
//! sendGdbString - send pkt to GDB  (pre-amble and postscript are added)
//!
//! @param buffer - data to send ('\0' terminated)
//! @param size   - size of pkt (-1 ignored)
//!
void GdbOutput::sendGdbString(const char *buffer, int size) {
   putGdbPreamble();
   putGdbString(buffer, size);
   putGdbChecksum();
   flushGdbBuffer();
}

//! Send a string to GDB as a series of hex digit pairs with leading id string
//!
//! @param id   - '\0' terminated string to send unencoded
//! @param s    - '\0' terminated string to send encoded
//! @param size - maximum size of encoded string to send (-1 ignored)
//!
void GdbOutput::sendGdbHexString(const char *id, const char *s, int size) {
   if (id == NULL) {
      id = "";
   }
   putGdbPreamble();
   putGdbString(id);
   putGdbHexString(s, size);
   putGdbChecksum();
   flushGdbBuffer();
}

//!
//! Send bytes to GDB as Hex character pairs
//!
//! @param buffer   - data to put ('\0' terminated)
//! @param size     - size of data (-1 ignored)
//!
void GdbOutput::sendGdbHex(const unsigned char *buffer, unsigned size) {
   putGdbPreamble();
   putGdbHex(buffer, size);
   putGdbChecksum();
   flushGdbBuffer();
}

//!
//! sendGdbString - send notification pkt to GDB  (pre-amble and postscript are added)
//!
//! @param buffer - data to send ('\0' terminated)
//! @param size   - size of data (-1 ignored)
//!
void GdbOutput::sendGdbNotification(const char *buffer, int size) {
   putGdbPreamble('%');
   putGdbString("Stop:");
   putGdbString(buffer, size);
   putGdbChecksum();
   flushGdbBuffer();
}

//!
//! sendGdbBuffer - append checksum & flush gdbBuffer (in background thread)
//!
void GdbOutput::sendGdbBuffer(void) {
   putGdbChecksum();
   flushGdbBuffer();
}

void GdbOutput::sendErrorMessage(ErrorType errorType, const char *msg) {
   static const char *errStrings[] = {"fatal", "memType"};
   if (errorType>E_Memory) {
      errorType = E_Fatal;
   }
   putGdbPreamble();
   putGdbPrintf("E.%s.%s", errStrings[errorType], msg);
   putGdbChecksum();
   flushGdbBuffer();
}

void GdbOutput::sendErrorMessage(unsigned value) {
   putGdbPreamble();
   putGdbPrintf("E%2.2X", value);
   putGdbChecksum();
   flushGdbBuffer();
}

//! Send immediate ACK/NAK response
//!
//! @param ackValue - Either '-' or '+' response to send
//!
void GdbOutput::sendAck(char ackValue) {
   Logging::print("sendAck()=>ack=%c\n", ackValue);
   fputc(ackValue, pipeOut);
   fflush(pipeOut);
}



