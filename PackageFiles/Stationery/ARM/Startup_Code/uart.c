/*
 * uart.c
 *
 *  Created on: 14/04/2013
 *      Author: pgo
 */

#include <derivative.h>
#include "clock.h"
#include "clock_private.h"
#include "uart.h"
#include "Freedom.h"

#if !defined(UART0_RX_PIN_PORT)
//=================================================================================
// UART Port bit masks
//
#error "Please modify before use"
#define UART0_RX_PIN_PORT      D
#define UART0_RX_PIN_NUM       6
#define UART0_RX_PIN_FN        3

#define UART0_TX_PIN_PORT      D
#define UART0_TX_PIN_NUM       7
#define UART0_TX_PIN_FN        3
#endif

#define UART0_TX_PIN_MASK      (1<<UART0_TX_PIN_NUM)
#define UART0_TX_PIN_PCR       PCR(UART0_TX_PIN_PORT,UART0_TX_PIN_NUM)
#define UART0_TX_PIN_PDOR      PDOR(UART0_TX_PIN_PORT)
#define UART0_TX_PIN_PSOR      PSOR(UART0_TX_PIN_PORT)  // Data set
#define UART0_TX_PIN_PCOR      PCOR(UART0_TX_PIN_PORT)  // Data clear
#define UART0_TX_PIN_PTOR      PTOR(UART0_TX_PIN_PORT)  // Data toggle
#define UART0_TX_PIN_PDIR      PDIR(UART0_TX_PIN_PORT)  // Data input
#define UART0_TX_PIN_PDDR      PDDR(UART0_TX_PIN_PORT)  // Data direction

#define UART0_RX_PIN_MASK      (1<<UART0_RX_PIN_NUM)
#define UART0_RX_PIN_PCR       PCR(UART0_RX_PIN_PORT,UART0_RX_PIN_NUM)
#define UART0_RX_PIN_PDOR      PDOR(UART0_RX_PIN_PORT)
#define UART0_RX_PIN_PSOR      PSOR(UART0_RX_PIN_PORT)  // Data set
#define UART0_RX_PIN_PCOR      PCOR(UART0_RX_PIN_PORT)  // Data clear
#define UART0_RX_PIN_PTOR      PTOR(UART0_RX_PIN_PORT)  // Data toggle
#define UART0_RX_PIN_PDIR      PDIR(UART0_RX_PIN_PORT)  // Data input
#define UART0_RX_PIN_PDDR      PDDR(UART0_RX_PIN_PORT)  // Data direction

#define SIM_SCGC5_PORT_MASK(reg) CONCAT3_(SIM_SCGC5_PORT,reg,_MASK)

// Clock enables for the two port pins used by the UART
#define SIM_SCGC5_PORT_MASK_FOR_UART_PINS (SIM_SCGC5_PORT_MASK(UART0_TX_PIN_PORT)|\
                                           SIM_SCGC5_PORT_MASK(UART0_RX_PIN_PORT))

#if defined(SYSTEM_UART0_CLOCK)
#define UART_CLOCK SYSTEM_UART0_CLOCK
#elif defined (SYSTEM_PERIPHERAL_CLOCK)
#define UART_CLOCK SYSTEM_PERIPHERAL_CLOCK
#else
#error "UART_CLOCK not defined"
#endif

/*
 * Initialises the UART
 *
 * @param baudrate - the baud rate to use e.g. 19200
 */
void uart_initialise(int baudrate) {
   uint16_t ubd;

   // Enable clock to UART
   SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;

   // Enable clock to port pins used by UART
   SIM_SCGC5 |= SIM_SCGC5_PORT_MASK_FOR_UART_PINS;

   // Set Tx & Rx pins in use
   SIM_SOPT5 &= ~(SIM_SOPT5_UART0RXSRC_MASK|SIM_SOPT5_UART0TXSRC_MASK);

   // Set Tx & Rx Pin function
   UART0_TX_PIN_PCR = PORT_PCR_MUX(UART0_TX_PIN_FN) | PORT_PCR_DSE_MASK;
   UART0_RX_PIN_PCR = PORT_PCR_MUX(UART0_RX_PIN_FN);

   // Set Tx & Rx pins in use
   SIM_SOPT5 &= ~(SIM_SOPT5_UART0RXSRC_MASK|SIM_SOPT5_UART0TXSRC_MASK);

   // Disable UART before changing registers
   UART0_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);

   // Calculate baud settings
   ubd = (uint16_t)(UART_CLOCK/(baudrate * 16));

   // Set Baud rate register
   UART0_BDH = (UART0_BDH&~UART_BDH_SBR_MASK) | UART_BDH_SBR((ubd>>8));
   UART0_BDL = UART_BDL_SBR(ubd);

#ifdef UART_C4_BRFA_MASK
   // Determine fractional divider to get closer to the baud rate
   uint16_t brfa;
   brfa     = (uint8_t)(((SystemCoreClock*32000)/(baudrate * 16)) - (ubd * 32));
   UART0_C4 = (UART0_C4&~UART_C4_BRFA_MASK) | UART_C4_BRFA(brfa);

#endif
   UART0_C1 = 0;

   // Enable UART Tx & Rx
   UART0_C2 = UART_C2_TE_MASK|UART_C2_RE_MASK;
}


/*
 * Transmits a single character over the UART (blocking)
 *
 * @param ch - character to send
 */
void uart_txChar(int ch) {
   while ((UART0_S1 & UART_S1_TDRE_MASK) == 0) {
      // Wait for Tx buffer empty
      __asm__("nop");
   }
   UART0_D = ch;
}

/*
 * Receives a single character over the UART (blocking)
 *
 * @return - character received
 */
int uart_rxChar(void) {
   while ((UART0_S1 & UART_S1_RDRF_MASK) == 0) {
      // Wait for Rx buffer full
      __asm__("nop");
   }
   return UART0_D;
};
