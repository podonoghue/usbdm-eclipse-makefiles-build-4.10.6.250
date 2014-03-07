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

#if defined(MCU_MKE02Z2)
//=================================================================================
// UART to use
//
#define UART  UART1
#define UART_CLOCK SYSTEM_UART1_CLOCK

//=================================================================================
// UART Port pin setup
//
__attribute__((always_inline))
inline static void initDefaultUart()  {
   // Enable clock to UART
   SIM_SCGC |= SIM_SCGC_UART1_MASK;
}
#elif defined(MCU_MKL02Z4) || defined(MCU_MKL04Z4) || defined(MCU_MKL05Z4)
//=================================================================================
// UART to use
//
#define UART  UART0
#define UART_CLOCK SYSTEM_UART0_CLOCK

//=================================================================================
// UART Port pin setup
//
__attribute__((always_inline))
inline static void initDefaultUart()  {
   // Enable clock to UART
   SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;

   // Enable clock to port pins used by UART
   SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;

   // Select Tx & Rx pins to use
   SIM_SOPT5 &= ~(SIM_SOPT5_UART0RXSRC_MASK|SIM_SOPT5_UART0TXSRC_MASK);

   // Set Tx & Rx Pin function
   PORTB_PCR1 = PORT_PCR_MUX(2);
   PORTB_PCR2 = PORT_PCR_MUX(2);
}
#elif defined(MCU_MKL14Z4) || defined(MCU_MKL15Z4) || defined(MCU_MKL16Z4) || defined(MCU_MKL24Z4) || \
      defined(MCU_MKL25Z4) || defined(MCU_MKL26Z4) || defined(MCU_MKL34Z4) || defined(MCU_MKL36Z4) || \
      defined(MCU_MKL46Z4)
//=================================================================================
// UART to use
//
#define UART  UART0
#define UART_CLOCK SYSTEM_UART0_CLOCK

//=================================================================================
// UART Port pin setup
//
__attribute__((always_inline))
inline static void initDefaultUart()  {
   // Enable clock to UART
   SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;

   // Enable clock to port pins used by UART
   SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;

   // Select Tx & Rx pins to use
   SIM_SOPT5 &= ~(SIM_SOPT5_UART0RXSRC_MASK|SIM_SOPT5_UART0TXSRC_MASK);

   // Set Tx & Rx Pin function
   PORTA_PCR1 = PORT_PCR_MUX(2);
   PORTA_PCR2 = PORT_PCR_MUX(2);
}
#elif defined(MCU_MK20D5)
//=================================================================================
// UART to use
//
#define UART  UART0
#define UART_CLOCK SYSTEM_UART0_CLOCK

//=================================================================================
// UART Port pin setup
//
__attribute__((always_inline))
inline static void initDefaultUart()  {
   // Enable clock to UART
   SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;

   // Enable clock to port pins used by UART
   SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;

   // Select Tx & Rx pins to use
   SIM_SOPT5 &= ~(SIM_SOPT5_UART0RXSRC_MASK|SIM_SOPT5_UART0TXSRC_MASK);

   // Set Tx & Rx Pin function
   PORTB_PCR16 = PORT_PCR_MUX(3);
   PORTB_PCR17 = PORT_PCR_MUX(3);
}
#elif defined(MCU_MK20D10) || defined(MCU_MK20DZ10) || defined(MCU_MK40D10) || defined(MCU_MK40DZ10) || defined(MCU_MK20D7)
//=================================================================================
// UART to use
//
#define UART  UART0
#define UART_CLOCK SYSTEM_UART0_CLOCK

//=================================================================================
// UART Port pin setup
//
__attribute__((always_inline))
inline static void initDefaultUart()  {
   // Enable clock to UART
   SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;

   // Enable clock to port pins used by UART
   SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;

   // Select Tx & Rx pins to use
   SIM_SOPT5 &= ~(SIM_SOPT5_UART0RXSRC_MASK|SIM_SOPT5_UART0TXSRC_MASK);

   // Set Tx & Rx Pin function
   PORTD_PCR6 = PORT_PCR_MUX(3);
   PORTD_PCR7 = PORT_PCR_MUX(3);
}
#elif defined(MCU_MK60DZ10) || defined(MCU_MK60D10) || defined(MCU_MK60F12) || defined(MCU_MK10DZ10) || defined(MCU_MK10D10) || defined(MCU_MK10F12)
//=================================================================================
// UART to use
//
#define UART  UART5
#define UART_CLOCK SYSTEM_UART5_CLOCK

//=================================================================================
// UART Port pin setup
//
__attribute__((always_inline))
inline static void initDefaultUart()  {
   // Enable clock to UART
   SIM_SCGC1 |= SIM_SCGC1_UART5_MASK;

   // Enable clock to port pins used by UART
   SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;

   // Set Tx & Rx pins in use
   SIM_SOPT5 &= ~(SIM_SOPT5_UART0RXSRC_MASK|SIM_SOPT5_UART0TXSRC_MASK);

   // Set Tx & Rx Pin function
   PORTE_PCR8 = PORT_PCR_MUX(3);
   PORTE_PCR9 = PORT_PCR_MUX(3);
}
#else
#error "Please modify before use"
//=================================================================================
// UART to use
//
#define UART  UART0
#define UART_CLOCK SYSTEM_UART0_CLOCK

//=================================================================================
// UART Port pin setup
//
__attribute__((always_inline))
inline static void initDefaultUart()  {
   // Enable clock to UART
   SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;

   // Enable clock to port pins used by UART
   SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;

   // Select Tx & Rx pins to use
   SIM_SOPT5 &= ~(SIM_SOPT5_UART0RXSRC_MASK|SIM_SOPT5_UART0TXSRC_MASK);

   // Set Tx & Rx Pin function
   PORTD_PCR6 = PORT_PCR_MUX(3);
   PORTD_PCR7 = PORT_PCR_MUX(3);
}
#endif

#if !defined(UART_CLOCK)
#error "UART_CLOCK not defined"
#endif

/*
 * Initialises the UART
 *
 * @param baudrate - the baud rate to use e.g. 19200
 */
void uart_initialise(int baudrate) {
   initDefaultUart();

   // Disable UART before changing registers
   UART->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);

   // Calculate UART clock setting (5-bit fraction at right)
   int scaledBaudValue = (2*UART_CLOCK)/(baudrate);
   
#ifdef UART_C4_BRFA_MASK
   // Set Baud rate register
   UART->BDH = (UART->BDH&~UART_BDH_SBR_MASK) | UART_BDH_SBR((scaledBaudValue>>(8+5)));
   UART->BDL = UART_BDL_SBR(scaledBaudValue>>5);
   // Fractional divider to get closer to the baud rate
   UART->C4 = (UART->C4&~UART_C4_BRFA_MASK) | UART_C4_BRFA(scaledBaudValue);
#else
	scaledBaudValue += 1<<4; // Round value
   // Set Baud rate register
   UART->BDH = (UART->BDH&~UART_BDH_SBR_MASK) | UART_BDH_SBR((scaledBaudValue>>(8+5)));
   UART->BDL = UART_BDL_SBR(scaledBaudValue>>5);
#endif

   UART->C1 = 0;

   // Enable UART Tx & Rx
   UART->C2 = UART_C2_TE_MASK|UART_C2_RE_MASK;
}

/*
 * Transmits a single character over the UART (blocking)
 *
 * @param ch - character to send
 */
void uart_txChar(int ch) {
   while ((UART->S1 & UART_S1_TDRE_MASK) == 0) {
      // Wait for Tx buffer empty
      __asm__("nop");
   }
   UART->D = ch;
}

/*
 * Receives a single character over the UART (blocking)
 *
 * @return - character received
 */
int uart_rxChar(void) {
   while ((UART->S1 & UART_S1_RDRF_MASK) == 0) {
      // Wait for Rx buffer full
      __asm__("nop");
   }
   return UART->D;
};
