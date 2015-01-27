/*! \file
    \brief Handles GDB output, and GDB input

    GdbInOutSocket.cpp

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
#include <Winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <errno.h>
#include <memory.h>
#include <netdb.h>
#define closesocket close
#define SOCKET int
#endif
#include <stdio.h>

#include "GdbInOutSocket.h"
#include "Log.h"


#define gdbClientPort          2331 // Client port (GDB connection)

#define LOCAL_HOST_NAME       "localhost"
#define D_QUEUE               1
#define D_SOCKETS             1
#define D_INFO                256

#ifndef EWOULDBLOCK
#define EWOULDBLOCK           WSAEWOULDBLOCK
#endif

#ifdef _WIN32
#define NET_ERROR_NUM WSAGetLastError()
#else
#define NET_ERROR_NUM errno
#endif

#define CONNECTION_DELAY      1 // seconds


bool GdbInOutSocket::stopListening = false;

/*
 *
 */
GdbInOutSocket::GdbInOutSocket() :
   GdbInOut(),
   activeSocket(-1) {

   // Create socket to listen on
   listenSocket = createSocket(gdbClientPort, true);
}

/*
 *
 */
GdbInOutSocket::~GdbInOutSocket() {
   finish();
   if (listenSocket > 0) {
      closesocket(listenSocket);
      listenSocket = -1;
   }
}

//=====================================================================
// Input functions
//=====================================================================


void GdbInOutSocket::restart(void) {

   state        = hunt;
   connectionActive  = false;
   activeSocket = -1;
   rxBufferIndex  = 0;
   rxBufferLength = 0;
   gdbTxChecksum  = 0;
   gdbTxCharCount = 0;
   gdbTxPtr       = gdbTxBuffer;

}

/*!  Finish up
 *
 *  - Set end of file
 *  - Close client socket
 */
void GdbInOutSocket::finish(void) {
   GdbInOut::finish();
   if (activeSocket >= 0) {
      closesocket(activeSocket);
      activeSocket = -1;
   }
}

/*!  Get GDB Packet
 *
 *   @return next GDB packet received or NULL if none available
 *
 *   @note Non-blocking
 */
const GdbPacket *GdbInOutSocket::getGdbPacket(void) {
   LOGGING_Q;
   if (!connectionActive) {
      Logging::print("EOF\n");
      return NULL;
   }
   const GdbPacket  *packet;
   int byte;
   do {
      byte = getChar();
      packet = processRxByte(byte);
   } while (byte > 0);
   if (packet != NULL) {
      Logging::print("Rx<=#:%d:%03d$%*.*s#%2.2X\n", packet->sequence, packet->size, packet->size, packet->size, packet->buffer, packet->checkSum );
      if (ackMode) {
         sendAck();
      }
   }
   else {
      Logging::print("No packet\n");
   }
   return packet;
}

/*! Create Socket
 *
 *  @param portNumber
 *  @param nonBlocking
 *
 *  @return socket number on success, -GDB_FATAL_ERROR on fail
 *
 */
int GdbInOutSocket::createSocket(int portNumber, bool nonBlocking) {

   fprintf(stderr, "Creating socket (port #%d)...\n", portNumber);

   //  Create the new socket
   //
   int newSocket = socket(AF_INET, SOCK_STREAM, 0);
   if (newSocket < 0) {
      fprintf(stderr, " Create socket (socket()) failed. Error = %d\n", NET_ERROR_NUM);
      return -GDB_FATAL_ERROR;
   }

   // Allow socket descriptor to be reusable
   //
   int optionValue = 1;
   if (setsockopt(newSocket, SOL_SOCKET,  SO_REUSEADDR, (char *)&optionValue, sizeof(optionValue)) < 0) {
      fprintf(stderr, "Setting socket options (setsockopt()) failed. Error = %d\n", NET_ERROR_NUM);
      closesocket(newSocket);
      return -GDB_FATAL_ERROR;
   }

   if (nonBlocking) {
      // Set socket to be non-blocking.  All of the sockets for the incoming connections
      // will also be non-blocking since they will inherit that state from this
      //
   #ifdef WIN32
      unsigned long option2 = 1;
      int result = ioctlsocket(newSocket, FIONBIO, &option2);
   #else
      char option2 = 1;
      int result = ioctl(newSocket, FIONBIO, (char *)&option2);
   #endif
      if (result < 0 ) {
         fprintf(stderr, "ioctl() failed. Error = %d\n", NET_ERROR_NUM);
         closesocket(newSocket);
         return -GDB_FATAL_ERROR;
      }
   }
#if 0
   int flag = 1;
     int result = setsockopt(sock,            /* socket affected */
                             IPPROTO_TCP,     /* set option at TCP level */
                             TCP_NODELAY,     /* name of option */
                             (char *) &flag,  /* the cast is historical
                                                     cruft */
                             sizeof(int));    /* length of option value */
     if (result < 0)
        ... handle the error ...
#endif

#ifdef _WIN32
   unsigned long option3 = 1;
   int rc = setsockopt(newSocket, IPPROTO_TCP, TCP_NODELAY, (char *) &option3, sizeof(option3));
   if (rc == SOCKET_ERROR) {
      fprintf(stderr, "setsockopt for IPPROTO_TCP.TCP_NODELAY failed with error: %u\n", NET_ERROR_NUM);
   }

   int option4 = 0;
   int option4Length = sizeof(option4);

   // Clear existing socket errors
   rc = getsockopt(newSocket, SOL_SOCKET, SO_ERROR, (char *) &option4, &option4Length);
   if (rc == SOCKET_ERROR) {
      fprintf(stderr, "getsockopt for SOL_SOCKET.SO_ERROR failed with error: %u\n", NET_ERROR_NUM);
   }
#endif

   //  Get information about the host
   struct sockaddr_in addr;
   memset(&addr, 0, sizeof(addr));

   struct hostent *host;
   host = gethostbyname(LOCAL_HOST_NAME);
   if (host == NULL) {
      fprintf(stderr, "Get host information (gethostbyname()) failed. Error = %u\n", NET_ERROR_NUM);
      closesocket(newSocket);
      return -GDB_FATAL_ERROR;
   }

   if (portNumber > 0) {
      //  Bind the socket to an address and port
      memcpy(&addr.sin_addr, host->h_addr_list[0], sizeof(addr.sin_addr));
      addr.sin_family      = AF_INET;
      addr.sin_addr.s_addr = htonl(INADDR_ANY);
      addr.sin_port        = htons(portNumber);
      if (bind(newSocket, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
         fprintf(stderr, "Binding socket to address & port (bind()) failed. Error = %d\n", NET_ERROR_NUM);
         fprintf(stderr, "port = %d", portNumber);
         closesocket(newSocket);
         return -GDB_FATAL_ERROR;
      }
   }
   return newSocket;
}

/*! Non-blocking wait for client connection
 *
 *  @param listenSocket
 *
 *  @return new socket number if success, -GDB_NON_FATAL_ERROR on timeout, -GDB_FATAL_ERROR on error
*/
int GdbInOutSocket::waitForConnection(int listenSocket) {
   int clientSocket;

   /*  Listen for single connections  */
   if (listen(listenSocket, 1) != 0) {
      fprintf(stderr, "Listening for connection failed. Fatal error = %d\n", NET_ERROR_NUM);
      Logging::print("Listening for connection (listen()) failed. Fatal error = %d\n", NET_ERROR_NUM);
      return -GDB_FATAL_ERROR;
   }

   // Clear existing errors on socket
   int socketErrorValue = 0;
#ifdef _WIN32
   int socketErrorValueLength = sizeof(socketErrorValue);
#else
   unsigned socketErrorValueLength = sizeof(socketErrorValue);
#endif

   int rc = getsockopt(listenSocket, SOL_SOCKET, SO_ERROR, (char *) &socketErrorValue, &socketErrorValueLength);
   if (rc != 0) {
      fprintf(stderr, "getsockopt for SOL_SOCKET.SO_ERROR failed with error: %u\n", NET_ERROR_NUM);
   }

//   fprintf(stderr, "Existing errors on port #%d = %d\n", GDB_PORT_NUM, socketErrorValue);
//
//   fprintf(stderr, "Current Windsock Error = %d\n", NET_ERROR_NUM);
//
   fprintf(stderr, "Waiting for connection on port #%d... ", gdbClientPort);
   int result = 0;
   fd_set input;
   do {
      FD_ZERO(&input);
      FD_SET((SOCKET)listenSocket, &input);

      struct timeval tv;
      tv.tv_sec  = CONNECTION_DELAY;
      tv.tv_usec = 0;
      result = select(1, &input, NULL, NULL, &tv);
   } while ((!stopListening) && (result == 0));

   stopListening = false;

   if (result < 0) {
      // select() failed
      fprintf(stderr, "Failed with fatal error. rc = %d, Error = %d\n", result, NET_ERROR_NUM);
      return -GDB_FATAL_ERROR;
   }
   if (result == 0) {
      fprintf(stderr, "Failed no connection (timeout). Error = %d\n", NET_ERROR_NUM);
      return -GDB_NON_FATAL_ERROR;
   }
   if (!FD_ISSET(listenSocket , &input)) {
      fprintf(stderr, "Check state (using FD_ISSET()) had inconsistent state. Error\n");
      return -GDB_NON_FATAL_ERROR;
   }
   clientSocket = accept(listenSocket, NULL, NULL );
   if (clientSocket == -1) {
      fprintf(stderr, "Accepting connection (using accept()) failed with fatal error. Error = %d\n", NET_ERROR_NUM);
      return -GDB_FATAL_ERROR;
   }
   fprintf(stderr, "Client connection established\n");
   return clientSocket;
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
int GdbInOutSocket::getData(unsigned char *buffer, int size) {

   memset(buffer, 0, size);

   if (activeSocket < 0) {
      connectionActive = false;
      return -GDB_FATAL_ERROR;
   }
   int rc = waitForActivity(activeSocket, 0);
   if (rc == -GDB_NON_FATAL_ERROR) {
      // No data available
      return 0;
   }
   if (rc != GDB_OK) {
      return rc;
   }
   rc = recv(activeSocket, (char*)buffer, D_INFO, 0);
   if ((rc < 0) && (NET_ERROR_NUM != EWOULDBLOCK)) {
      fprintf(stderr, " recv() failed. Error = %d\n", NET_ERROR_NUM);
      return -GDB_FATAL_ERROR;
   }
   if (rc > 0) {
      return rc;
   }
   return -GDB_NON_FATAL_ERROR;
}

/*
 *  @param clientSocket - socket to check
 *  @param delay        - how long to wait
 *
 *  @return  GDB_OK(0)           - socket has data (reading will not block) \n
 *          -GDB_NON_FATAL_ERROR - socket has no data (reading will block) \n
 *          -GDB_FATAL_ERROR     - unexpected error
 */
int GdbInOutSocket::waitForActivity(int clientSocket, int delay = CONNECTION_DELAY) {
   fd_set input;
   FD_ZERO(&input);
   FD_SET((SOCKET)clientSocket, &input);
   struct timeval tv;
   tv.tv_sec  = delay;
   tv.tv_usec = 0;

//   fprintf(stderr, "Waiting for activity... ");
   int result = select(1, &input, NULL, NULL, &tv);

   if (result == 0) {
//      fprintf(stderr, "No activity\n");
      return -GDB_NON_FATAL_ERROR;
   }
   if (result<0) {
//      fprintf(stderr, "failed. Error = %d\n", NET_ERROR_NUM);
      return -GDB_FATAL_ERROR;
   }
   if (FD_ISSET((SOCKET)clientSocket , &input)) {
//      fprintf(stderr, "Client active\n");
      return GDB_OK;
   }
//   fprintf(stderr, "Unknown activity\n");
   return -GDB_FATAL_ERROR;
}


//=====================================================================
// Output functions
//=====================================================================

/*!  Write buffer to GDB
 *
 *   @param buffer buffer to write
 *   @param size number of bytes to write
 *
 *   @note Blocking but should usually succeed 1st try
 */
void GdbInOutSocket::writeBuffer(unsigned char *buffer, int size) {
   int rc;
   int bytesWritten = 0;
   do {
      rc = ::send(activeSocket,  (const char *)buffer, size, 0);
      bytesWritten += rc;
   } while ((bytesWritten < size) && (rc > 0));
   if (rc <0) {
      fprintf(stderr, "  send() failed. Error = %d\n", NET_ERROR_NUM);
      connectionActive = false;
   }
}
