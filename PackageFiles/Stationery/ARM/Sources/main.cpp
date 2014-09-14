/*
 ============================================================================
 * main.c
 *
 *  Created on: 04/12/2012
 *      Author: podonoghue
 ============================================================================
 */
#include "derivative.h"
#include "utilities.h"
#include "leds.h"

// Dummy routines in case LED code not provided
__attribute__((__weak__))
void led_initialise(void) {
}

__attribute__((__weak__))
void greenLedToggle(void) {
}

// Simple delay - not for real programs!
void delay(void) {
   volatile unsigned long i;
   for (i=400000; i>0; i--) {
      __asm__("nop");
   }
}

/* Example use of interrupt handler
 *
 * The standard ARM libraries provide basic support for the system timer
 * This function is used for the System Timer interrupt handler.
 *
 */
void SysTick_Handler(void) {
   __asm__("nop");
}

int main(void) {

   volatile int count = 0;

   SysTick_Config(1000);

   led_initialise();

   // Real programs never die!
   for(;;) {
      count++;
      greenLedToggle();
      delay();
   }
   return 0;
}
