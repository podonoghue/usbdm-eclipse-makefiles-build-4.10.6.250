/*
 * sysinit-mkl.c
 *
 * Generic system initialization for Kinetis MKLxx family
 *
 *  Created on: 07/12/2012
 *      Author: podonoghue
 */

#include <stdint.h>
#include "derivative.h"

#define $(targetDeviceSubFamily)

$(cDeviceParameters)

/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
//uint32_t SystemCoreClock = 48000000UL; /*!< System Clock Frequency (Core Clock)*/

/**
 * Update SystemCoreClock variable
 *
 * @param  none
 * @return none
 *
 * @brief  Updates the SystemCoreClock with current core Clock
 *         retrieved from cpu registers.
 */
/* This definition is overridden if Clock initialisation is provided */
__attribute__((__weak__))
void SystemCoreClockUpdate(void) {           /* Get Core Clock Frequency      */
}

/* Actual Vector table */
extern int const __vector_table[];

#ifndef SCB_VTOR
#define SCB_VTOR (*(uint32_t *)0xE000ED08)
#endif

#if !defined(SIM_COPC)
   /* Defaults for MKL devices */

   /* COP timer register */
   #define SIM_COPC (*(uint32_t *)0x40048100)
#endif


/* This definition is overridden if Clock initialisation is provided */
__attribute__((__weak__))
void clock_initialise() {
}

/* This definition is overridden if UART initialisation is provided */
__attribute__((__weak__))
void uart_initialise(int baudRate) {
   (void)baudRate;
}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit(void) {
   /* This is generic initialization code */
   /* It may not be correct for a specific target */

   /* Set the interrupt vector table position */
   SCB_VTOR = (uint32_t)__vector_table;

   // Disable watch-dog
   SIM_COPC = 0x00;

   /* Use Clock initialisation - if present */
   clock_initialise();

   /* Use UART initialisation - if present */
   uart_initialise(19200);
}

void _exit(int i) {
   (void)i;
   while (1) {
      asm("bkpt #0");
   }
}

