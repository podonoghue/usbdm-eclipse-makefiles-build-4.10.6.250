/*
 * utilities.h
 *
 *  Created on: May 13, 2013
 *      Author: PODonoghue
 */
#ifndef UTILTIES_H_
#define UTILTIES_H_

#include "derivative.h"

// Used to create port register names in a configurable fashion
//-------------------------------------------------------------
#define CONCAT2_(x,y) x ## y
#define CONCAT3_(x,y,z) x ## y ## z
#define CONCAT4_(w,x,y,z) w ## x ## y ## z

#define PF(port,num)    CONCAT4_(MXC_PT,port,PF,num)
#define PDOR(port)      CONCAT3_(GPIO,port,_PDOR)
#define PSOR(port)      CONCAT3_(GPIO,port,_PSOR)
#define PCOR(port)      CONCAT3_(GPIO,port,_PCOR)
#define PTOR(port)      CONCAT3_(GPIO,port,_PTOR)
#define PDIR(port)      CONCAT3_(GPIO,port,_PDIR)
#define PDDR(port)      CONCAT3_(GPIO,port,_PDDR)

#define MXC(port,muxNum)     CONCAT4_(MXC_PT,port,PF,muxNum)
#define MXC_MASK(pin,value) (((value)&0x0F)<<(4*((pin)&0x01)))

/*!
 *  Stop - used to reduce power
 */
#define __stop(x) __asm__("stop %0" :: "i" (x))

/*!
 *  Debug breakpoint
 */
#define __breakpoint() __asm__("halt")
#define __halt()       __asm__("halt")

/*!
 * Set interrupt level in SR
 */
#define __set_interrupt_level(x) __asm__(" move %0,%%sr" :: "i" ((((x)<<8)&0x0700)|0x2000))

#ifdef INTC_IMRH

#define NVIC_PRIO_BITS (4) /* 4 Bits used for the Priority Levels    */

/*!
 * Enable IRQ channel in INTC
 *
 * @param irqNum - IRQ number (64-128)
 */
static inline void INTC_EnableIrq(int irqNum) {
   if (irqNum>=113) {
      irqNum -= (113-42);
   }
   INTC_CIMR = INTC_CIMR_CIMR(irqNum);
}

/*!
 * Disable IRQ channel in INTC
 *
 * @param irqNum - IRQ number (64-128)
 */
static inline void INTC_DisableIrq(int irqNum) {
   if (irqNum>=113) {
      irqNum -= (113-42);
   }
   INTC_SIMR = INTC_SIMR_SIMR(irqNum);
}

/*!
 * Set an interrupt request atthe given level
 *
 * @param level -  request level, 1...7
 */
static inline void INTC_SetIrqAtLevel(int level) {
   INTC_SFRC = 0x3F-(level&0x7);
}

/*!
 * Clear an interrupt request atthe given level
 *
 * @param level -  request level, 1...7
 */
static inline void INTC_ClearIrqAtLevel(int level) {
   INTC_CFRC = 0x3F-(level&0x7);
}

#endif

#endif /* UTILTIES_H_ */
