/*
 * sysinit.c
 *
 * Generic system initialization for Coldfire Vx
 *
 *  Created on: 07/12/2012
 *      Author: podonoghue
 */

#include <stdint.h>
#include "derivative.h"

#define $(targetDeviceSubFamily)

$(cDeviceParameters)


/* This definition is overridden if Clock initialisation is provided */
__attribute__((__weak__))
void clock_initialise(void) {
}

/* This definition is overridden if UART initialisation is provided */
__attribute__((__weak__))
void uart_initialise(int baudRate) {
   (void)baudRate;
}

void sysInit(void) {
   // This is generic initialization code
   // It may not be correct for a specific target

#ifdef SOPT1
   // Disable watch-dog
   SOPT1 = 0x00;
#endif
#ifdef SIM_COPC
   // Disable watch-dog
   SIM_COPC = 0x00;
#endif

   /* Use Clock initialisation - if present */
   clock_initialise();

   /* Use UART initialisation - if present */
   uart_initialise(19200);

}
