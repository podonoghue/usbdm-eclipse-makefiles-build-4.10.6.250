/*
 ============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : Basic C Main
 ============================================================================
 */
#include "derivative.h"
#include "utilities.h"

/* Example use of interrupt handler
 *
 * The standard ARM libraries provide basic support for the system timer
 * This function is used for the System Timer interrupt handler.
 *
 */
void SysTick_Handler(void) {
   __asm__("nop");
   __asm__("nop");
}


int main(void) {

   // Configure the system timer to generate interrupt every 1000 ticks
   SysTick_Config(1000);

   // Real programs never die!
   for(;;) {
      __asm__("nop");
   }
}
