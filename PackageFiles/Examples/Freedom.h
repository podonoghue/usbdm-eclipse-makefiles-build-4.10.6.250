/*
 * Freedom.h
 *
 *  Created on: 28/05/2013
 *      Author: Peter
 */

#ifndef FREEDOM_H_
#define FREEDOM_H_

#include "portmacros.h"
#ifdef MCU_MKL05Z4
//=================================================================================
// LED Port bit masks
//
#define LED_GREEN_REG          B
#define LED_GREEN_NUM          9

#define LED_RED_REG            B
#define LED_RED_NUM            8

#define LED_BLUE_REG           B
#define LED_BLUE_NUM          10

//=================================================================================
// UART Port bit masks
//
#define UART0_RX_PIN_REG       B
#define UART0_RX_PIN_NUM       2
#define UART0_RX_PIN_FN        2

#define UART0_TX_PIN_REG       B
#define UART0_TX_PIN_NUM       1
#define UART0_TX_PIN_FN        2
#endif

#ifdef MCU_MKL25Z4
//=================================================================================
// LED Port bit masks
//
#define LED_GREEN_REG          B
#define LED_GREEN_NUM         19

#define LED_RED_REG            B
#define LED_RED_NUM           18

#define LED_BLUE_REG           D
#define LED_BLUE_NUM           1
                                    // Elec freaks LCD Shield buttons
#define SWITCH_0_REG           B	// North
#define SWITCH_0_NUM           0
#define SWITCH_1_REG           B    // East
#define SWITCH_1_NUM           1
#define SWITCH_2_REG           B    // South
#define SWITCH_2_NUM           2
#define SWITCH_3_REG           B    // Centre
#define SWITCH_3_NUM           3
#define SWITCH_4_REG           C    // West
#define SWITCH_4_NUM           2

//=================================================================================
// UART Port bit masks
//
#define UART0_RX_PIN_REG       A
#define UART0_RX_PIN_NUM       1
#define UART0_RX_PIN_FN        2

#define UART0_TX_PIN_REG       A
#define UART0_TX_PIN_NUM       2
#define UART0_TX_PIN_FN        2
#endif

#ifdef MCU_MK20D5

//=================================================================================
// LED Port bit masks
//
#define LED_GREEN_REG          D
#define LED_GREEN_NUM          4

#define LED_RED_REG            C
#define LED_RED_NUM            3

#define LED_BLUE_REG           A
#define LED_BLUE_NUM           2

#define UART0_RX_PIN_REG       B
#define UART0_RX_PIN_NUM      16
#define UART0_RX_PIN_FN        3

#define UART0_TX_PIN_REG       B
#define UART0_TX_PIN_NUM      17
#define UART0_TX_PIN_FN        3

                                    // Elec freaks LCD Shield buttons
#define SWITCH_0_REG           C	// (A0) North
#define SWITCH_0_NUM           0
#define SWITCH_1_REG           C    // (A1) East
#define SWITCH_1_NUM           1
#define SWITCH_2_REG           D    // (A2) South
#define SWITCH_2_NUM           6
#define SWITCH_3_REG           D    // (A3) Centre
#define SWITCH_3_NUM           5
#define SWITCH_4_REG           B    // (A4) West
#define SWITCH_4_NUM           1
#endif

#endif /* FREEDOM_H_ */
