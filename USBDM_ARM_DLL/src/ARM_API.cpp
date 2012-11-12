/*! \file
    \brief ARM debugging interface

    \verbatim
    Copyright (C) 2009  Peter O'Donoghue

    Some of the following is based on material from OSBDM-JM60
       Target Interface Software Package
    Copyright (C) 2009  Freescale

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Change History
+==================================================================================
| 16 Aug 2012 | All active code is now in USBDM.dll.  This is a shim.        V4.10.0
+==================================================================================
\endverbatim
*/
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "Common.h"
#include "Utils.h"
#include "Log.h"
#include "Conversion.h"
#ifdef DLL
#undef DLL
#endif
#include "USBDM_API.h"
#define DLL
#include "USBDM_ARM_API.h"

#define DHCSR (0xE000EDF0) // RW Debug Halting Control and Status Register
#define DCSR  (0xE000EDF4) // WO Debug Core Selector Register
#define DCDR  (0xE000EDF8) // RW Debug Core Data Register
#define DEMCR (0xE000EDFC) // RW Debug Exception and Monitor Control Register
#define DFSR  (0xE000ED30) // Debug Fault Status Register
#define AIRCR (0xE000ED0C) // Application Interrupt and Reset Control Register

static volatile int dummy = 0;

void ARM_SetLogFile(FILE *fp) {
   dummy = 0;
}

//! Initialise ARM interface
//!
USBDM_ErrorCode ARM_Initialise() {
   return BDM_RC_OK;
}

//! Reset Target
//!
//! @param targetMode - reset mode
//!
USBDM_ErrorCode ARM_TargetReset(TargetMode_t targetMode) {
   return USBDM_TargetReset(targetMode);
}

//! Connect to ARM Target
//!
USBDM_ErrorCode ARM_Connect() {
   return USBDM_Connect();
}

//! Reads a word from ARM target memory
//!
//! @note Breaks transfers on 2**10 boundary as TAR may not increment across this boundary
//!
//! @param address  - 32-bit starting address (aligned)
//! @param data     - pointer to buffer for word
//!
//! @return error code
//!
static USBDM_ErrorCode readMemoryWord(uint32_t address, unsigned long *data) {
   uint8_t buff[4];
   USBDM_ErrorCode rc = USBDM_ReadMemory(4, 4, address, buff);
   *data = (buff[0])+(buff[1]<<8)+(buff[2]<<16)+(buff[3]<<24);
   return rc;
}

//! Get ARM target status
//!
//! @param status - true => halted, false => running
//!
USBDM_ErrorCode ARM_GetStatus(ArmStatus *status) {
   USBDM_ErrorCode rc;
   unsigned long dataIn;
   ArmStatus defaultStatus = {0,0xFFFFFFFF,0,0};

//   print("   ARM_GetStatus()\n");

   *status = defaultStatus;

   // Freesale MDM-AP present ?
   rc = USBDM_ReadCReg(ARM_CRegMDM_AP_Status, &dataIn);
   if (rc == BDM_RC_OK) {
      status->mdmApStatus = dataIn;
   }
   // Generic Debug
   rc = readMemoryWord(DHCSR, &dataIn);
   if (rc != BDM_RC_OK) {
//      print("   ARM_GetStatus() Can't read DHCSR!\n");
      return BDM_RC_BDM_EN_FAILED;
   }
   status->dhcsr = dataIn;

   return BDM_RC_OK;
}

//! Write data to target memory
//!
//! @param elementSize = Size of data elements (1/2/4 bytes)
//! @param byteCount   = Number of _bytes_ to transfer
//! @param address     = Memory address
//! @param data        = Ptr to block of data to write
//!
//! @return error code \n
//!     BDM_RC_OK    => OK \n
//!     other        => Error code - see \ref USBDM_ErrorCode
//!
USBDM_ErrorCode  ARM_WriteMemory( unsigned int  elementSize,
                                  unsigned int  byteCount,
                                  unsigned int  address,
                                  unsigned const char *data) {

   return USBDM_WriteMemory(elementSize, byteCount, address, data);
}

//! Read data from target memory
//!
//! @param elementSize = Size of data (1/2/4 bytes)
//! @param byteCount   = Number of bytes to transfer
//! @param address     = Memory address
//! @param data        = Where to place data
//!
//! @return error code \n
//!     BDM_RC_OK    => OK \n
//!     other        => Error code - see \ref USBDM_ErrorCode
//!
USBDM_ARM_API
USBDM_ErrorCode  ARM_ReadMemory( unsigned int  elementSize,
                                 unsigned int  byteCount,
                                 unsigned int  address,
                                 unsigned char *data) {
   return USBDM_ReadMemory(elementSize, byteCount, address, data);
}

//! Read Register
//!
//! @param regNo     - Register number
//! @param regValue  - Value from register
//!
//! @note Assumes Core TAP is active & in RUN-TEST/IDLE
//! @note Leaves Core TAP in RUN-TEST/IDLE
//!
USBDM_ErrorCode ARM_ReadRegister(ARM_Registers_t regNo, unsigned long *regValue) {

   return USBDM_ReadReg(regNo, regValue);
}

//! Write Register
//!
//! @param regNo     - Register number
//! @param regValue  - Value for register
//!
USBDM_ErrorCode ARM_WriteRegister(ARM_Registers_t regNo, unsigned long regValue) {

   return USBDM_WriteReg(regNo, regValue);
}

//! Read Control Register (
//!
//! @param regNo     - Register number in AP address space
//!                     e.g. MDM-AP.Status  = 0x0100000
//!                          MDM-AP.Control = 0x0100004
//!                          MDM-AP.Ident   = 0x010003F
//! @param regValue  - Value from register
//!
USBDM_ErrorCode ARM_ReadCReg(unsigned int regNo, unsigned long *regValue) {
   return USBDM_ReadCReg(regNo, regValue);
}

//! Write Control Register (
//!
//! @param regNo     - Register number in AP address space
//!                     e.g. MDM-AP.Status  = 0x0100000
//!                          MDM-AP.Control = 0x0100004
//!                          MDM-AP.Ident   = 0x010003F
//! @param regValue  - Value from register
//!
USBDM_ErrorCode ARM_WriteCReg(unsigned int regNo, unsigned long regValue) {
   return USBDM_WriteCReg(regNo, regValue);
}

//! Start Target execution at current PC
//!
//!
USBDM_ErrorCode ARM_TargetGo() {
   return USBDM_TargetGo();
}

//! Execute N instructions from current PC
//!
USBDM_ErrorCode ARM_TargetStepN(unsigned numSteps) {
   while (numSteps-->0) {
      USBDM_ErrorCode rc = USBDM_TargetStep();
      if (rc != BDM_RC_OK) {
         return rc;
      }
   }
   return BDM_RC_OK;
}

//! Execute 1 instruction from current PC
//!
USBDM_ErrorCode ARM_TargetStep(void) {
   return ARM_TargetStepN(1);
}

//! Halts target execution
//!
USBDM_ErrorCode ARM_TargetHalt(void) {
   return USBDM_TargetHalt();
}
