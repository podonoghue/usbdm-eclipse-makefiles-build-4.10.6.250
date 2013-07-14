/*! \file
    \brief Handles GDB output, and GDB input (on a separate thread)

    GdbInOutPipe.cpp

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
   | 23 Jun 2013 | Sockets version created and merged                            - pgo
   +==================================================================================
   | 23 Apr 2012 | Created                                                       - pgo
   +==================================================================================
   \endverbatim
*/

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#endif
#include <stdio.h>

#include <pthread.h>
#include <io.h>
#include <fcntl.h>
#include <unistd.h>

#include "GdbInOutPipe.h"
#include "Log.h"

/*
 *
 */
GdbInOutPipe::GdbInOutPipe() :
   GdbInOut(),
   readyPacket(NULL) {

   fdIn   = dup(fileno(stdin));
   setmode( fdIn, _O_BINARY );

   fdOut = dup(fileno(stdout));
   setmode( fdOut, _O_BINARY );

   connectionActive = true;
}

/*
 *
 */
GdbInOutPipe::~GdbInOutPipe() {
   finish();
}

//=====================================================================
// Input functions
//=====================================================================

 /*!   Create background thread to monitor input pipe
  *
  *   @return true  - Success \n
  *           false - Failed to create thread
  */
bool GdbInOutPipe::createThread(void) {

   int rc = pthread_create(&tid, NULL, threadFunc, (void*)this);
   Logging::print("Creating background thread\n");
   if (rc) {
      Logging::print("ERROR return code from pthread_create() is %d\n", rc);
      return false;
   }
   return true;
}

/*!  Finish up
 *
 *  - Tell background thread to complete
 *  - Kill background thread
 *  - Close file handles
 */
void GdbInOutPipe::finish(void) {
   GdbInOut::finish();
   pthread_cancel(tid);
   if (fdOut > 0) {
      close(fdOut);
      fdOut = -1;
   }
   if (fdIn > 0) {
      close(fdIn);
      fdIn = -1;
   }
}

 /*!   Background thread to monitor GDB input
  *
  *   @param arg - 'this' pointer
  */
void *GdbInOutPipe::threadFunc(void *arg) {
   LOGGING_Q;
   GdbInOutPipe *me = (GdbInOutPipe *)arg;
   me->readyPacket  = NULL;
   do {
      // Get a packet
      const GdbPacket *pkt = NULL;
      int byte;
      do {
         byte = me->getChar();
         pkt  = me->processRxByte(byte);
      } while ((pkt == NULL) && (byte > 0));

      while ((me->readyPacket != NULL) && (me->connectionActive)) {
         // Wait for previous buffer to be consumed
         // This should never occur
         Logging::print("Buffer is unexpectedly busy!!!!!!\n");
      }

//      Logging::print("threadFunc() - new pkt\n");

      // Pass packet to foreground
      me->readyPacket = pkt;
   } while (me->connectionActive);
   return NULL;
}

/*!  Get GDB Packet
 *
 *   @return next GDB packet received or NULL if none available
 *
 *   @note Non-blocking
 */
const GdbPacket *GdbInOutPipe::getGdbPacket(void) {
   LOGGING_Q;
   if (!connectionActive) {
      Logging::print("EOF\n");
      return NULL;
   }
   const GdbPacket  *packet = readyPacket;
   if (packet != NULL) {
      readyPacket = NULL;
      Logging::print("Rx<=#:%d:%03d$%*.*s#%2.2X\n", packet->sequence, packet->size, packet->size, packet->size, packet->buffer, packet->checkSum );
      if (ackMode) {
         sendAck();
      }
   }
   return packet;
}

/*!  Get data from GDB
 *
 *   @param buff   - buffer for data
 *   @param size   - maximum number of bytes to read
 *
 *   @return  >0                  - Number of bytes read \n
 *            GDB_OK(0)           - No data \n
 *           -GDB_FATAL_ERROR     - Unexpected error
 */
int GdbInOutPipe::getData(unsigned char buff[], int size) {

   memset(buff, 0, size);

   if (fdIn < 0) {
      connectionActive = false;
      return -GDB_FATAL_ERROR;
   }
   int rc = read(fdIn, buff, size);
   if (rc < 0) {
      fprintf(stderr, " read() failed. Error = %d\n", errno);
      return -GDB_FATAL_ERROR;
   }
   if (rc > 0) {
      return rc;
   }
   return -GDB_NON_FATAL_ERROR;
}

//=====================================================================
// Output functions
//=====================================================================

/*!  Write buffer to GDB
 *
 *   @param buffer buffer to write
 *   @param size number of bytes to write
 *
 *   @note Blocking
 */
void GdbInOutPipe::writeBuffer(unsigned char *buffer, int size) {
   int rc;
   int bytesWritten = 0;
   do {
      rc = ::write(fdOut, buffer, size);
      bytesWritten += rc;
   } while ((bytesWritten < size) && (rc > 0));
   if (rc <0) {
      fprintf(stderr, "  write() failed. Error = %d\n", errno);
      connectionActive = false;
   }
}
