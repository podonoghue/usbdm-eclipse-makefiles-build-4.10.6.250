/********************************************************************/
/* Coldfire C Header File
 *
 *     Date      : 2009/04/30
 *     Revision  : 0.97
 *
 *     Copyright : 1997 - 2009 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 *     http      : www.freescale.com
 *     mail      : support@freescale.com
 */

#ifndef __MCF52233_H__
#define __MCF52233_H__


/********************************************************************/
/*
 * The basic data types
 */

typedef unsigned char           uint8;   /*  8 bits */
typedef unsigned short int      uint16;  /* 16 bits */
typedef unsigned long int       uint32;  /* 32 bits */

typedef signed char             int8;    /*  8 bits */
typedef signed short int        int16;   /* 16 bits */
typedef signed long int         int32;   /* 32 bits */

typedef volatile uint8          vuint8;  /*  8 bits */
typedef volatile uint16         vuint16; /* 16 bits */
typedef volatile uint32         vuint32; /* 32 bits */

#ifdef __cplusplus
extern "C" {
#endif

#include "MCF52233_SCM.h"
#include "MCF52233_DMA.h"
#include "MCF52233_UART.h"
#include "MCF52233_I2C.h"
#include "MCF52233_QSPI.h"
#include "MCF52233_RTC.h"
#include "MCF52233_DTIM.h"
#include "MCF52233_INTC.h"
#include "MCF52233_FEC.h"
#include "MCF52233_GPIO.h"
#include "MCF52233_PAD.h"
#include "MCF52233_RCM.h"
#include "MCF52233_CCM.h"
#include "MCF52233_PMM.h"
#include "MCF52233_CLOCK.h"
#include "MCF52233_EPORT.h"
#include "MCF52233_PIT.h"
#include "MCF52233_ADC.h"
#include "MCF52233_GPTA.h"
#include "MCF52233_PWM.h"
#include "MCF52233_CFM.h"
#include "MCF52233_EPHY.h"

#ifdef __cplusplus
}
#endif


#endif /* __MCF52233_H__ */
