/*
 * utilities-mke.h
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

#define PCR(port,num)   CONCAT4_(PORT,port,_PCR,num)
#define PDOR(port)      CONCAT3_(GPIO,port,_PDOR)
#define PSOR(port)      CONCAT3_(GPIO,port,_PSOR)
#define PCOR(port)      CONCAT3_(GPIO,port,_PCOR)
#define PTOR(port)      CONCAT3_(GPIO,port,_PTOR)
#define PDIR(port)      CONCAT3_(GPIO,port,_PDIR)
#define PDDR(port)      CONCAT3_(GPIO,port,_PDDR)

/*!
 *  Wait for interrupt event - used to reduce power
 */
#define __wait_for_interrupt() __asm__("wfi")

/*!
 *  Debug breakpoint
 */
#define __breakpoint() __asm__("bkpt")

/*!
 *  Enable interrupts
 */
#define __enable_interrupt() __asm__("cpsie I")

/*!
 *  Disable interrupts
 */
#define __disable_interrupt() __asm__("cpsid I")

/*!
 *  Enable fault interrupts
 */
#define __enable_fault_interrupt() __asm__("cpsie F")

/*!
 *  Disable fault interrupts
 */
#define __disable_fault_interrupt() __asm__("cpsid F")

#endif /* UTILTIES_H_ */
