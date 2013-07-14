/*
 * GdbInOutPipe.h
 *
 *  Created on: 23/04/2012
 *      Author: PODonoghue
 */

#ifndef GDBINOUTPIPE_H_
#define GDBINOUTPIPE_H_

#include "GdbInOut.h"
#include <pthread.h>

class GdbInOutPipe : public GdbInOut {

public:
   GdbInOutPipe();
   virtual ~GdbInOutPipe();
   virtual const GdbPacket *getGdbPacket();

private:
   pthread_t        tid;  //! Thread ID of background Rx function

   int              fdIn;  //! Input handle from GDB
   int              fdOut; //! Output handle to GDB

   const GdbPacket *readyPacket;       //! Packet assembled by background thread

private:
   static void*             threadFunc(void *arg);
   bool                     createThread(void);

   virtual void             writeBuffer(unsigned char *buffer, int size);
   virtual int              getData(unsigned char *buffer, int size);

public:
   virtual void finish(void);
   static GdbInOutPipe *getGdbInOut(void) {
      GdbInOutPipe *gdbInOut = new GdbInOutPipe();
      if (!gdbInOut->createThread()) {
         delete gdbInOut;
         gdbInOut = NULL;
      }
      return gdbInOut;
   }
};

#endif /* GDBINOUTPIPE_H_ */
