/*
 * GdbInOutSocket.h
 *
 *  Created on: 19/06/2013
 *      Author: PODonoghue
 */

#ifndef GDBINOUTSOCKET_H_
#define GDBINOUTSOCKET_H_

#include "GdbInOut.h"

class GdbInOutSocket : public GdbInOut {

public:
   GdbInOutSocket();
   virtual ~GdbInOutSocket();

private:

   int              listenSocket;
   int              activeSocket;

   unsigned char    gdbRxBuffer[1000]; //! Buffer for Rx data from GDB
   unsigned         rxBufferIndex;     //! Read index for gdbRxBuffer
   unsigned         rxBufferLength;    //! Occupied size of gdbRxBuffer

   static bool      stopListening;

private:
   int createSocket(int portNumber, bool nonBlocking);
   int waitForConnection(int listenSocket);
   int waitForActivity(int clientSocket, int delay);
   virtual void             writeBuffer(unsigned char *buffer, int size);
   virtual int              getData(unsigned char *buffer, int size);
   virtual const GdbPacket *getGdbPacket();

public:
   void restart(void);
   virtual void finish(void);
   static GdbInOutSocket *getGdbInOut(void) {
      GdbInOutSocket *gdbInOut = new GdbInOutSocket();
      return gdbInOut;
   }


   static void stopWaiting(void) {
      stopListening = true;
   }
   int waitForConnection(void) {
      activeSocket = waitForConnection(listenSocket);
      if (activeSocket >= 0) {
         connectionActive = true;
         return GDB_OK;
      }
      return -activeSocket;
   }
};

#endif /* GDBINOUTSOCKET_H_ */
