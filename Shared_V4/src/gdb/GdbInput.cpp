/*! \file
    \brief Handles GDB input on a separate thread

    GdbInput.cpp

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

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#endif

#include <pthread.h>
#include <unistd.h>

#include "GdbInput.h"
#include "Log.h"

GdbInput::GdbInput(FILE *in) :
   state(hunt),
   full(false),
   idle(false),
   terminate(false),
   isEndOfFile(false),
   buffer(NULL),
   pipeIn(NULL)
{
   pthread_mutex_init(&mutex, NULL);
   pthread_cond_init(&dataNeeded_cv, NULL);
   int inHandle = dup(fileno(in));
   pipeIn= fdopen(inHandle, "rb");

#ifdef _WIN32
   setmode( _fileno( pipeIn ), _O_BINARY );
   setvbuf ( pipeIn,  NULL, _IONBF , 0 );
#else
   setvbuf ( pipeIn,  NULL, _IONBF , 0 );
#endif
}

//! Create background thread to monitor input pipe
//!
//! @return true  - Success \n
//!         false - Failed to create thread
//!
bool GdbInput::createThread(void) {

   int rc = pthread_create(&tid, NULL, threadFunc, (void*)this);
   if (rc) {
      Logging::print("ERROR return code from pthread_create() is %d\n", rc);
      return false;
   }
   return true;
}

//! Tell background thread to complete
//!
void GdbInput::finish(void) {
   terminate = true;
   (void)receiveGdbPacket();
}

//! Kill background thread
//!
//! @return true  - Success \n
//!         false - Failed to create thread
//!
void GdbInput::kill(void) {
   finish();
   pthread_cancel(tid);
   if (pipeIn != NULL) {
      fclose(pipeIn);
   }
}

//! GDB Packet that indicate a break has been received.
//!
const GdbPacket GdbPacket::breakToken  = {
      sizeof("break"),
      "break"
};

//!
//! Convert a HEX char to binary
//!
//! @param ch - char to convert ('0'-'9', 'a'-'f' or 'A' to 'F')
//!
//! @return converted value - no error checks!
//!
static int hex(char ch) {
   if (('0' <= ch) && (ch <= '9'))
      return ch - '0';
   if (('a' <= ch) && (ch <= 'f'))
      return ch - 'a' + 10;
   if (('A' <= ch) && (ch <= 'F'))
      return ch - 'A' + 10;
   return 0;
}

//! Receive packet from debugger (blocking but runs on background thread)
//!
//! @return - !=NULL => pkt ready
//!           ==NULL => pipe closed etc
//!
const GdbPacket *GdbInput::receiveGdbPacket(void) {
   static GdbPacket packet1;
   static GdbPacket *const packet = &packet1;
   static unsigned char  checksum    = 0;
   static unsigned char  xmitcsum    = 0;
   static unsigned int   sequenceNum = 0;

   if (terminate || isEndOfFile) {
      isEndOfFile = true;
	   return NULL;
   }
   while(1) {
      int ch = fgetc(pipeIn);
      if (ch == EOF) {
         int rc = ferror(pipeIn);
         if (rc != 0) {
//            perror("PipeIn error:");
         }
//         Logging::print("GdbPipeConnection::getGdbPacket() - EOF\n");
         isEndOfFile = true;
      }
      if (terminate || isEndOfFile) {
         isEndOfFile = true;
         fclose(pipeIn);
         pipeIn = NULL;
         return NULL;
      }
      switch(state) {
      case hunt: // Looking for start of pkt (or Break)
//         Logging::print("GdbPipeConnection::busyLoop(): h:%c\n", ch);
         if (ch == '$') { // Start token
            state         = data;
            checksum      = 0;
            packet->size  = 0;
         }
         else if (ch == 0x03) { // Break request
//            Logging::print("GdbPipeConnection::busyLoop(): BREAK\n");
            return &GdbPacket::breakToken;
         }
         break;
      case data: // Data bytes within pkt
         //         Logging::print("GdbPipeConnection::busyLoop(): d:%c\n", ch);
         if (ch == '}') { // Escape token
            state     = escape;
            checksum  = checksum + ch;
         }
         else if (ch == '$') { // Unexpected start token
            state        = data;
            checksum         = 0;
            packet->size      = 0;
         }
         else if (ch == '#') { // End of data token
            state    = checksum1;
         }
         else { // Regular data
            if (packet->size < GdbPacket::MAX_MESSAGE) {
               packet->buffer[packet->size++] = ch;
            }
            checksum  = checksum + ch;
         }
         break;
      case escape: // Escaped byte within data
         //         Logging::print("GdbPipeConnection::busyLoop(): e:%c\n", ch);
         state    = data;
         checksum = checksum + ch;
         ch       = ch ^ 0x20;
         if (packet->size < GdbPacket::MAX_MESSAGE) {
            packet->buffer[packet->size++] = ch;
         }
         break;
      case checksum1: // 1st Checksum byte
         //         Logging::print("GdbPipeConnection::busyLoop(): c1:%c\n", ch);
         state    = checksum2;
         xmitcsum = hex(ch) << 4;
         break;
      case checksum2: // 2nd Checksum byte
         xmitcsum += hex(ch);
         //         Logging::print("GdbPipeConnection::busyLoop(): c2:%c\n", ch);
         if (checksum != xmitcsum) {
            // Invalid pkt - discard and start again
//            Logging::print("\nBad checksum: my checksum = %2.2X, ", checksum);
//            Logging::print("sent checksum = %2.2X\n", xmitcsum);
//            Logging::print(" -- Bad buffer: \"%s\"\n", packet->buffer);
//            fputc('-', pipeOut); // failed checksum
//            fflush(pipeOut);
            state = hunt;
         }
         else {
            // Valid pkt
            packet->checkSum = checksum;
            packet->buffer[packet->size] = '\0';
            state = hunt;
            packet->sequence = ++sequenceNum;
//            Logging::print("#%40s<-:%d:%03d$%*.*s#%2.2X\n", "", packet->sequence, packet->size, packet->size, packet->size, packet->buffer, packet->checkSum );
            // Pkt ready
//            Logging::print("<=:%03d:\'%*s\'\n", packet->size, packet->size, packet->buffer);
            return packet;
         }
         break;
      }
   }
   return NULL;
}

//! Background thread to monitor input pipe
//!
//! @param arg - this pointer
//!
void *GdbInput::threadFunc(void *arg) {
   GdbInput *me = (GdbInput *)arg;
   pthread_mutex_lock(&me->mutex);
   me->full   = false;
   me->buffer = NULL;
   do {
      // Wait until pkt needed
      me->idle = true;
      pthread_cond_wait(&me->dataNeeded_cv, &me->mutex);
      // Receive a pkt
      pthread_mutex_unlock(&me->mutex);
      const GdbPacket *pkt = me->receiveGdbPacket();
      pthread_mutex_lock(&me->mutex);
      me->buffer = pkt;
      me->full   = true;
   } while(true);
   return NULL;
}

const GdbPacket *GdbInput::getGdbPacket(void) {
//   static int lastSequence = -1;
   LOGGING_Q;
   if (isEndOfFile) {
      Logging::print("EOF\n");
      return NULL;
   }
   // Lock shared data flags
//   Logging::print("before lock\n");
   pthread_mutex_lock(&mutex);
//   Logging::print("locked\n");
   // Check if new pkt ready & accept it
   bool pktReady = full;
   full = false;
   // Start reception of next pkt
   if (idle && !pktReady) {
//      Logging::print("idle && !pktReady => signaling dataNeeded\n");
      idle = false;
      pthread_cond_signal(&dataNeeded_cv);
   }
   pthread_mutex_unlock(&mutex);
//   Logging::print("unlocked\n");
   if (pktReady) {
//      Logging::print("pkt ready\n");
      if (buffer == NULL) {
         Logging::print("Rx<='%s'\n", "Buffer NULL!");
         if (this->isEndOfFile) {
            Logging::print("Rx<='%s'\n", "EOF");
         }
      }
      else {
         if (buffer->buffer == NULL) {
            Logging::print("Rx<='%s'\n", "NULL");
         }
         else {
            Logging::print("Rx<=#:%d:%03d$%*.*s#%2.2X\n", buffer->sequence, buffer->size, buffer->size, buffer->size, buffer->buffer, buffer->checkSum );
         }
//         if (buffer->sequence == lastSequence) {
//            // Discard repeated message
//            Logging::print("Rx<= **** Discarded repeated pkt\n");
//            return NULL;
//         }
//         lastSequence = buffer->sequence;
      }
      return buffer;
   }
//   Logging::print("No pkt ready\n");
   return NULL;
}

void GdbInput::flush(void) {
   LOGGING_E;
   fflush(pipeIn);
}
