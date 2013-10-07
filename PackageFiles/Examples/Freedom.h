/*
 * Freedom.h
 *
 *  Created on: 28/05/2013
 *      Author: Peter
 */

#ifndef FREEDOM_H_
#define FREEDOM_H_

#include "portmacros.h"

#ifdef MCU_MK40DZ10
//=================================================================================
// LED Port bit masks
//
#define LED_RED_PORT          C
#define LED_RED_NUM          7

#define LED_ORANGE_PORT       C
#define LED_ORANGE_NUM       8

#define LED_GREEN_PORT        C
#define LED_GREEN_NUM        9

#define LED_BLUE_PORT         B
#define LED_BLUE_NUM        11

//=================================================================================
// UART Port bit masks
//
#define UART0_RX_PIN_PORT       D
#define UART0_RX_PIN_NUM       6
#define UART0_RX_PIN_FN        3

#define UART0_TX_PIN_PORT       D
#define UART0_TX_PIN_NUM       7
#define UART0_TX_PIN_FN        3
#endif

#ifdef MCU_MKL05Z4
//=================================================================================
// LED Port bit masks
//
#define LED_GREEN_PORT          B
#define LED_GREEN_NUM          9

#define LED_RED_PORT            B
#define LED_RED_NUM            8

#define LED_BLUE_PORT           B
#define LED_BLUE_NUM          10

//=================================================================================
// UART Port bit masks
//
#define UART0_RX_PIN_PORT       B
#define UART0_RX_PIN_NUM       2
#define UART0_RX_PIN_FN        2

#define UART0_TX_PIN_PORT       B
#define UART0_TX_PIN_NUM       1
#define UART0_TX_PIN_FN        2
#endif

#ifdef MCU_MKL25Z4
//=================================================================================
// LED Port bit masks
//
#define LED_GREEN_PORT          B
#define LED_GREEN_NUM         19

#define LED_RED_PORT            B
#define LED_RED_NUM           18

#define LED_BLUE_PORT           D
#define LED_BLUE_NUM           1
                                    // Elec freaks LCD Shield buttons
#define SWITCH_0_PORT           B    // North
#define SWITCH_0_NUM           0
#define SWITCH_1_PORT           B    // East
#define SWITCH_1_NUM           1
#define SWITCH_2_PORT           B    // South
#define SWITCH_2_NUM           2
#define SWITCH_3_PORT           B    // Centre
#define SWITCH_3_NUM           3
#define SWITCH_4_PORT           C    // West
#define SWITCH_4_NUM           2

//=================================================================================
// UART Port bit masks
//
#define UART0_RX_PIN_PORT       A
#define UART0_RX_PIN_NUM       1
#define UART0_RX_PIN_FN        2

#define UART0_TX_PIN_PORT       A
#define UART0_TX_PIN_NUM       2
#define UART0_TX_PIN_FN        2
#endif

#ifdef MCU_MK20D5

//=================================================================================
// LED Port bit masks
//
#define LED_GREEN_PORT         D
#define LED_GREEN_NUM          4

#define LED_RED_PORT           C
#define LED_RED_NUM            3

#define LED_BLUE_PORT          A
#define LED_BLUE_NUM           2

#define UART0_RX_PIN_PORT      B
#define UART0_RX_PIN_NUM      16
#define UART0_RX_PIN_FN        3

#define UART0_TX_PIN_PORT      B
#define UART0_TX_PIN_NUM      17
#define UART0_TX_PIN_FN        3

                           // Elec freaks LCD Shield buttons
#define NORTH_SWITCH_PORT          C    // (A0) North
#define NORTH_SWITCH_NUM           0
#define EAST_SWITCH_PORT           C    // (A1) East
#define EAST_SWITCH_NUM            1
#define SOUTH_SWITCH_PORT          D    // (A2) South
#define SOUTH_SWITCH_NUM           6
#define CENTRE_SWITCH_PORT         D    // (A3) Centre
#define CENTRE_SWITCH_NUM          5
#define WEST_SWITCH_PORT           B    // (A4) West
#define WEST_SWITCH_NUM            1

#endif

#endif /* FREEDOM_H_ */
