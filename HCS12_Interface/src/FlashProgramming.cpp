/*! \file
   \brief Utility Routines for programming HCS12 Flash

   FlashProgramming.cpp

   \verbatim
   Copyright (C) 2008  Peter O'Donoghue

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
\endverbatim

\verbatim
 Change History
+==============================================================================
| Revision History
+==============================================================================
| 28 Dec 12 | 4.10.4 Changed handling of security area (& erasing)        - pgo
| 28 Dec 12 | 4.10.4 Changed TCL interface error handling                 - pgo
| 16 Dec 12 | 4.10.4 Moved Check of SDID to before Mass erase (HCS08)     - pgo
| 14 Dec 12 | 4.10.4 Added custom security                                - pgo
| 30 Nov 12 | 4.10.4 Changed logging                                      - pgo
| 30 Oct 12 | 4.10.4 Added MS_FAST option for HCS12/HCS12                 - pgo
| 30 Sep 12 | 4.10.2 RAM write added                                      - pgo
| 26 Aug 12 | 4.10.0 JTAG/SWD combined code                               - pgo
|  1 Jun 12 | 4.9.5 Now handles arbitrary number of memory regions        - pgo
| 30 May 12 | 4.9.5 Re-write of DSC programming                           - pgo
| 12 Apr 12 | 4.9.4 Changed handling of empty images                      - pgo
| 30 Mar 12 | 4.9.4 Added Intelligent security option                     - pgo
| 25 Feb 12 | 4.9.1 Fixed alignment rounding problem on partial phrases   - pgo
| 10 Feb 12 | 4.9.0 Major changes for HCS12 (Generalised code)            - pgo
| 20 Nov 11 | 4.8.0 Major changes for Coldfire+ (Generalised code)        - pgo
|  4 Oct 11 | 4.7.0 Added progress dialogues                              - pgo
| 23 Apr 11 | 4.6.0 Major changes for CFVx programming                    - pgo
|  6 Apr 11 | 4.6.0 Major changes for ARM programming                     - pgo
|  3 Jan 11 | 4.4.0 Major changes for XML device files etc                - pgo
| 17 Sep 10 | 4.0.0 Fixed minor bug in isTrimLocation()                   - pgo
| 30 Jan 10 | 2.0.0 Changed to C++                                        - pgo
|           |       Added paged memory support                            - pgo
| 15 Dec 09 | 1.1.1 setFlashSecurity() was modifying image unnecessarily  - pgo
| 14 Dec 09 | 1.1.0 Changed Trim to use linear curve fitting              - pgo
|           |       FTRIM now combined with image value                   - pgo
|  7 Dec 09 | 1.0.3 Changed SOPT value to disable RESET pin               - pgo
| 29 Nov 09 | 1.0.2 Bug fixes after trim testing                          - pgo
| 17 Nov 09 | 1.0.0 Created                                               - pgo
+==============================================================================
\endverbatim
*/
#define _WIN32_IE 0x0500 //!< Required for common controls?

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>
#include <ctype.h>
#include <memory>
#include "Common.h"
#include "Log.h"
#include "FlashImage.h"
#include "FlashProgramming.h"
#include "USBDM_API.h"
#include "TargetDefines.h"
#include "Utils.h"
#include "Names.h"
#include "ProgressTimer.h"
#include "SimpleSRecords.h"
#if (TARGET == ARM)
#include "STM32F100xx.h"
#include "ARM_Definitions.h"
#elif TARGET == MC56F80xx
#include "USBDM_DSC_API.h"
#endif
#include "usbdmTcl.h"
#include "wxPlugin.h"
#ifdef GDI
#include "GDI.h"
#include "MetrowerksInterface.h"
#endif
#include "Names.h"

static const char *getFlashOperationName(FlashOperation flashOperation);
static const char *getProgramActionNames(unsigned int actions);
static const char *getProgramCapabilityNames(unsigned int actions);

/* ======================================================================
 * Notes on BDM clock source (for default CLKSW):
 *
 *  CPU    BDM clock
 *  ----------------------
 *  RS08   bus clock
 *  HCS08  bus clock
 *  HC12   bus clock
 *  CFV1   bus clock
 *
 */
//=============================================================================

#if (TARGET == ARM)
#define WriteMemory(elementSize, byteCount, address, data) USBDM_WriteMemory((elementSize), (byteCount), (address), (data))
#define ReadMemory(elementSize, byteCount, address, data)  USBDM_ReadMemory((elementSize), (byteCount), (address), (data))
#define WritePC(regValue) USBDM_WriteReg(ARM_RegPC, (regValue))
#define ReadPC(regValue)  USBDM_ReadReg(ARM_RegPC,  (regValue))
#define TargetGo()        USBDM_TargetGo()
#define TargetHalt()      USBDM_TargetHalt()
#define TARGET_TYPE T_ARM
#elif TARGET == MC56F80xx
#define WriteMemory(elementSize, byteCount, address, data) DSC_WriteMemory((elementSize), (byteCount), (address), (data))
#define ReadMemory(elementSize, byteCount, address, data)  DSC_ReadMemory((elementSize), (byteCount), (address), (data))
#define WritePC(regValue) DSC_WriteRegister(DSC_RegPC, (regValue))
#define ReadPC(regValue)  DSC_ReadRegister(DSC_RegPC,  (regValue))
#define TargetGo()        DSC_TargetGo()
#define TargetHalt()      DSC_TargetHalt()
#define TARGET_TYPE T_MC56F80xx
#elif TARGET == CFVx
#define WriteMemory(elementSize, byteCount, address, data) USBDM_WriteMemory((elementSize), (byteCount), (address), (data))
#define ReadMemory(elementSize, byteCount, address, data)  USBDM_ReadMemory((elementSize), (byteCount), (address), (data))
#define WritePC(regValue) USBDM_WriteCReg(CFVx_CRegPC, (regValue))
#define ReadPC(regValue)  USBDM_ReadCReg(CFVx_CRegPC,  (regValue))
#define TargetGo()        USBDM_TargetGo()
#define TargetHalt()      USBDM_TargetHalt()
#define TARGET_TYPE T_CFVx
#elif TARGET == CFV1
#define WriteMemory(elementSize, byteCount, address, data) USBDM_WriteMemory((elementSize), (byteCount), (address), (data))
#define ReadMemory(elementSize, byteCount, address, data)  USBDM_ReadMemory((elementSize), (byteCount), (address), (data))
#define WritePC(regValue) USBDM_WriteCReg(CFV1_CRegPC, (regValue))
#define ReadPC(regValue)  USBDM_ReadCReg(CFV1_CRegPC,  (regValue))
#define TargetGo()        USBDM_TargetGo()
#define TargetHalt()      USBDM_TargetHalt()
#define TARGET_TYPE T_CFV1
#elif TARGET == HCS12
#define WriteMemory(elementSize, byteCount, address, data) USBDM_WriteMemory((elementSize), (byteCount), (address), (data))
#define ReadMemory(elementSize, byteCount, address, data)  USBDM_ReadMemory((elementSize), (byteCount), (address), (data))
#define WritePC(regValue) USBDM_WriteReg(HCS12_RegPC, (regValue))
#define ReadPC(regValue)  USBDM_ReadReg(HCS12_RegPC,  (regValue))
#define TargetGo()        USBDM_TargetGo()
#define TargetHalt()      USBDM_TargetHalt()
#define TARGET_TYPE T_HCS12
#elif TARGET == HCS08
#define WriteMemory(elementSize, byteCount, address, data) USBDM_WriteMemory((elementSize), (byteCount), (address), (data))
#define ReadMemory(elementSize, byteCount, address, data)  USBDM_ReadMemory((elementSize), (byteCount), (address), (data))
#define WritePC(regValue) USBDM_WriteReg(HCS08_RegPC, (regValue))
#define ReadPC(regValue)  USBDM_ReadReg(HCS08_RegPC,  (regValue))
#define TargetGo()        USBDM_TargetGo()
#define TargetHalt()      USBDM_TargetHalt()
#define TARGET_TYPE T_HCS08
#elif TARGET == RS08
#define WriteMemory(elementSize, byteCount, address, data) USBDM_WriteMemory((elementSize), (byteCount), (address), (data))
#define ReadMemory(elementSize, byteCount, address, data)  USBDM_ReadMemory((elementSize), (byteCount), (address), (data))
#define WritePC(regValue) USBDM_WriteReg(RS08_RegPC, (regValue))
#define ReadPC(regValue)  USBDM_ReadReg(RS08_RegPC,  (regValue))
#define TargetGo()        USBDM_TargetGo()
#define TargetHalt()      USBDM_TargetHalt()
#define TARGET_TYPE T_RS08
#else
#error "Need to define macros for this target"
#endif

//=======================================================================================

inline uint16_t swap16(uint16_t data) {
   return ((data<<8)&0xFF00) + ((data>>8)&0xFF);
}
inline uint32_t swap32(uint32_t data) {
   return ((data<<24)&0xFF000000) + ((data<<8)&0xFF0000) + ((data>>8)&0xFF00) + ((data>>24)&0xFF);
}

inline uint32_t getData32Be(uint8_t *data) {
   return (data[0]<<24)+(data[1]<<16)+(data[2]<<8)+data[3];
}
inline uint32_t getData32Le(uint8_t *data) {
   return (data[3]<<24)+(data[2]<<16)+(data[1]<<8)+data[0];
}
inline uint32_t getData16Be(uint8_t *data) {
   return (data[0]<<8)+data[1];
}
inline uint32_t getData16Le(uint8_t *data) {
   return data[0]+(data[1]<<8);
}
inline uint32_t getData32Be(uint16_t *data) {
   return (data[0]<<16)+data[1];
}
inline uint32_t getData32Le(uint16_t *data) {
   return (data[1]<<16)+data[0];
}
inline const uint8_t *getData4x8Le(uint32_t data) {
   static uint8_t data8[4];
   data8[0]= data;
   data8[1]= data>>8;
   data8[2]= data>>16;
   data8[3]= data>>24;
   return data8;
}
inline const uint8_t *getData4x8Be(uint32_t data) {
   static uint8_t data8[4];
   data8[0]= data>>24;
   data8[1]= data>>16;
   data8[2]= data>>8;
   data8[3]= data;
   return data8;
}
inline const uint8_t *getData2x8Le(uint32_t data) {
   static uint8_t data8[2];
   data8[0]= data;
   data8[1]= data>>8;
   return data8;
}
inline const uint8_t *getData2x8Be(uint32_t data) {
   static uint8_t data8[2];
   data8[0]= data>>8;
   data8[1]= data;
   return data8;
}

#if (TARGET == ARM) || (TARGET == MC56F80xx)
#define targetToNative16(x) (x)
#define targetToNative32(x) (x)
#define nativeToTarget16(x) (x)
#define nativeToTarget32(x) (x)

inline uint32_t getData32Target(uint8_t *data) {
   return getData32Le(data);
}
inline uint32_t getData16Target(uint8_t *data) {
   return *data;
}
inline uint32_t getData32Target(uint16_t *data) {
   return getData32Le(data);
}
inline uint32_t getData16Target(uint16_t *data) {
   return *data;
}
#else
#define targetToNative16(x) swap16(x)
#define targetToNative32(x) swap32(x)
#define nativeToTarget16(x) swap16(x)
#define nativeToTarget32(x) swap32(x)

inline uint32_t getData32Target(uint8_t *data) {
   return getData32Be(data);
}
inline uint32_t getData16Target(uint8_t *data) {
   return getData16Be(data);
}
#endif

#if (TARGET == HCS08) || (TARGET == HCS12)
//=======================================================================
//! Gets the page number portion of a physical address (Flash)
//!
//! @param memoryRegionPtr - memory region to check
//! @param physicalAddress - address to examine
//! @param pageNo          - corresponding page number
//!
USBDM_ErrorCode FlashProgrammer::getPageAddress(MemoryRegionConstPtr memoryRegionPtr, uint32_t physicalAddress, uint8_t *pageNo) {

   *pageNo = 0x00;
   if ((memoryRegionPtr == NULL) || !memoryRegionPtr->contains(physicalAddress)) {
      Logging::error("A=0x%06X - Invalid Flash address\n", physicalAddress);
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   if (memoryRegionPtr->getAddressType() != AddrPaged) {
      Logging::print("A=0x%06X - Not paged\n", physicalAddress);
      return PROGRAMMING_RC_OK;
   }
   uint32_t ppageAddress = memoryRegionPtr->getPageAddress();
   if (ppageAddress == 0) {
      Logging::print("A=0x%06X - Not mapped\n", physicalAddress);
      return PROGRAMMING_RC_OK;
   }
   uint32_t virtualAddress = (physicalAddress&0xFFFF);
   uint16_t pageNum16 = memoryRegionPtr->getPageNo(physicalAddress);
   if (pageNum16 == MemoryRegion::NoPageNo) {
      Logging::print("A=0x%06X - No page #!\n", physicalAddress);
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   *pageNo = (uint8_t)pageNum16;
   Logging::print("FlashProgrammer::getPageAddress(0x%06X) - PPAGE=%2.2X (Mapped Address=%06X)\n", physicalAddress, *pageNo, ((*pageNo)<<16)|virtualAddress);

   return PROGRAMMING_RC_OK;
}

//=======================================================================
//! Set PAGE registers (PPAGE/EPAGE)
//!
//! @param physicalAddress - memory address being accessed
//!
//! @return error code see \ref USBDM_ErrorCode.
//!
USBDM_ErrorCode FlashProgrammer::setPageRegisters(uint32_t physicalAddress) {
   // Process each flash region
   USBDM_ErrorCode rc = BDM_RC_OK;
   for (int index=0; ; index++) {
      MemoryRegionConstPtr memoryRegionPtr = parameters.getMemoryRegion(index);
      if (memoryRegionPtr == NULL) {
         break;
      }
      if (memoryRegionPtr && memoryRegionPtr->contains(physicalAddress)) {
         if (memoryRegionPtr->getAddressType() != AddrPaged) {
            return PROGRAMMING_RC_OK;
         }
         uint32_t ppageAddress   = memoryRegionPtr->getPageAddress();
         uint32_t virtualAddress = (physicalAddress&0xFFFF);
         if (ppageAddress == 0) {
            // Not paged memory
            Logging::print("Not mapped (VirtAddr=PhyAddr=%06X)\n", physicalAddress);
            return PROGRAMMING_RC_OK;
         }
         uint16_t pageNum16 = memoryRegionPtr->getPageNo(physicalAddress);
         if (pageNum16 == MemoryRegion::NoPageNo) {
            return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
         }
         uint8_t pageNum = (uint8_t)pageNum16;
         Logging::print("Setting E/PPAGE(0x%04X)=%2.2X (PhyAddr=%06X, VirAddr=%04X)\n", ppageAddress, pageNum, physicalAddress, virtualAddress);
         if (USBDM_WriteMemory(1, 1, ppageAddress, &pageNum) != BDM_RC_OK) {
            return PROGRAMMING_RC_ERROR_PPAGE_FAIL;
         }
         uint8_t pageNumRead;
         if (USBDM_ReadMemory(1, 1, ppageAddress, &pageNumRead) != BDM_RC_OK) {
            return PROGRAMMING_RC_ERROR_PPAGE_FAIL;
         }
         if (pageNum != pageNumRead) {
            return PROGRAMMING_RC_ERROR_PPAGE_FAIL;
         }
         return BDM_RC_OK;
      }
   }
   return rc;
}
#endif

//=============================================================================
//! Connects to the target. \n
//! - Resets target to special mode
//! - Connects
//! - Runs initialisation script
//!
//! @return error code, see \ref USBDM_ErrorCode \n
//!   BDM_OK                       => Success \n
//!   PROGRAMMING_RC_ERROR_SECURED => Device is connected but secured (target connection speed may have been approximated)\n
//!                           USBDM_getStatus() may be used to determine connection method.
//!
USBDM_ErrorCode FlashProgrammer::resetAndConnectTarget(void) {
   Logging log("FlashProgrammer::resetAndConnectTarget");
   USBDM_ErrorCode rc;

   if (parameters.getTargetName().empty()) {
      return PROGRAMMING_RC_ERROR_ILLEGAL_PARAMS;
   }
   flashReady     = false;
   initTargetDone = false;

   // Reset to special mode to allow unlocking of Flash
#if (TARGET == ARM)
   rc = USBDM_TargetReset((TargetMode_t)(RESET_SPECIAL|RESET_DEFAULT));
   if ((rc != BDM_RC_OK) && (rc != BDM_RC_SECURED)) {
      rc = USBDM_TargetReset((TargetMode_t)(RESET_SPECIAL|RESET_HARDWARE));
   }
#elif TARGET == MC56F80xx
   rc = DSC_TargetReset((TargetMode_t)(RESET_SPECIAL|RESET_DEFAULT));
   if ((rc != BDM_RC_OK) && (rc != BDM_RC_SECURED)) {
      rc = DSC_TargetReset((TargetMode_t)(RESET_SPECIAL|RESET_HARDWARE));
   }
#elif (TARGET == CFVx) || (TARGET == HC12)
   rc = USBDM_TargetReset((TargetMode_t)(RESET_SPECIAL|RESET_DEFAULT));
   if (rc != BDM_RC_OK) {
      rc = USBDM_TargetReset((TargetMode_t)(RESET_SPECIAL|RESET_HARDWARE));
   }
#else
   USBDM_Connect();
   rc = USBDM_TargetReset((TargetMode_t)(RESET_SPECIAL|RESET_DEFAULT));
   if (rc != BDM_RC_OK) {
      USBDM_Connect();
      rc = USBDM_TargetReset((TargetMode_t)(RESET_SPECIAL|RESET_HARDWARE));
   }
#endif
   if (rc == BDM_RC_SECURED) {
      Logging::error("... Device is secured\n");
      return PROGRAMMING_RC_ERROR_SECURED;
   }
   if (rc != BDM_RC_OK) {
      Logging::error( "... Failed Reset, %s!\n", USBDM_GetErrorString(rc));
      return rc; //PROGRAMMING_RC_ERROR_BDM_CONNECT;
   }
   // Try auto Connect to target
#if TARGET == MC56F80xx
   rc = DSC_Connect();
#else
   // BDM_RC_BDM_EN_FAILED usually means a secured device
   rc = USBDM_Connect();
#endif
   switch (rc) {
   case BDM_RC_SECURED:
   case BDM_RC_BDM_EN_FAILED:
      // Treat as secured & continue
      Logging::error( "... Partial Connect, rc = %s!\n", USBDM_GetErrorString(rc));
      rc = PROGRAMMING_RC_ERROR_SECURED;
      break;
   case BDM_RC_OK:
      rc = PROGRAMMING_RC_OK;
      break;
   default:
      Logging::error( "... Failed Connect, rc = %s!\n", USBDM_GetErrorString(rc));
      return rc; //PROGRAMMING_RC_ERROR_BDM_CONNECT;
   }
#if (TARGET == ARM)
   TargetHalt();
#endif
   // Use TCL script to set up target
   USBDM_ErrorCode rc2 = initialiseTarget();
   if (rc2 != PROGRAMMING_RC_OK) {
      rc = rc2;
   }
   return rc;
}

//=============================================================================
//! Reads the System Device Identification Register
//!
//! @param targetSDID - location to return SDID
//! @param doInit - reset & re-connect to target first
//!
//! @return error code, see \ref USBDM_ErrorCode
//!
//! @note Assumes the target device has already been opened & USBDM options set.
//! @note Assumes the target has been reset in SPECIAL mode
//!
USBDM_ErrorCode FlashProgrammer::readTargetChipId(uint32_t *targetSDID, bool doInit) {
   LOGGING_E;
   const int SDIDLength = 2;
   uint8_t SDIDValue[SDIDLength];

   if (parameters.getTargetName().empty()) {
      Logging::error("Target name not set\n");
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   *targetSDID = 0x0000;

   if (doInit) {
      USBDM_ErrorCode rc = resetAndConnectTarget();
      if (rc != PROGRAMMING_RC_OK) {
         Logging::error("Failed resetAndConnectTarget()\n");
         return rc;
      }
   }
   if (ReadMemory(SDIDLength, SDIDLength, parameters.getSDIDAddress(), SDIDValue) !=  BDM_RC_OK) {
      Logging::error("A=0x%06X - Failed ReadMemory()\n", parameters.getSDIDAddress());
      return PROGRAMMING_RC_ERROR_BDM_READ;
   }
   *targetSDID = getData16Target(SDIDValue);

   // Do a sanity check on SDID (may get these values if secured w/o any error being signaled)
   if ((*targetSDID == 0xFFFF) || (*targetSDID == 0x0000)) {
      Logging::error("A=0x%06X - Value invalid (0x%04X)\n", parameters.getSDIDAddress(), *targetSDID);
      return PROGRAMMING_RC_ERROR_BDM_READ;
   }
   Logging::print("A=0x%06X => 0x%04X\n", parameters.getSDIDAddress(), *targetSDID);
   return PROGRAMMING_RC_OK;
}

//=============================================================================
//! Check the target SDID agrees with device parameters
//!
//! @return error code, see \ref USBDM_ErrorCode
//!
//! @note Assumes the target has been connected to
//!
USBDM_ErrorCode FlashProgrammer::confirmSDID() {
   LOGGING_E;
   uint32_t targetSDID;
   USBDM_ErrorCode rc;

//   mtwksDisplayLine("confirmSDID() - #1\n");
   if (parameters.getTargetName().empty()) {
      Logging::error("Error: device parameters not set\n");
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
//   mtwksDisplayLine("confirmSDID() - #2\n");
   // Don't check Target SDID if zero
   if (parameters.getSDID() == 0x0000) {
      Logging::print("V=0x0000 => Skipping check\n");
      return PROGRAMMING_RC_OK;
   }
   // Get SDID from target
   rc = readTargetChipId(&targetSDID);
   if (rc != PROGRAMMING_RC_OK) {
      Logging::error("V=%4.4X => Failed, error reading SDID, reason = %s\n",
            parameters.getSDID(),
            USBDM_GetErrorString(rc));
      // Return this error even though the cause may be different
      return PROGRAMMING_RC_ERROR_WRONG_SDID;
   }
   if (!parameters.isThisDevice(targetSDID)) {
      Logging::error("V=0x%4.4X, Mask=0x%4.4X => Failed (Target SDID=0x%4.4X)\n",
            parameters.getSDID(),
            parameters.getSDIDMask(),
            targetSDID);
      return PROGRAMMING_RC_ERROR_WRONG_SDID;
   }
   Logging::print("V=%4.4X => OK\n", targetSDID);
   return PROGRAMMING_RC_OK;
}

//=============================================================================
//! Prepares the target \n
//!
//! @return error code, see \ref USBDM_ErrorCode
//!
//! @note Assumes target has been reset & connected
//!
USBDM_ErrorCode FlashProgrammer::initialiseTarget() {
   USBDM_ErrorCode rc;
   Logging log("FlashProgrammer::initialiseTarget");
   if (initTargetDone) {
      Logging::print("Already done, skipped\n");
      return PROGRAMMING_RC_OK;
   }
   initTargetDone = true;

#if (TARGET == HCS08)
   char args[200] = "initTarget \"";
   char *argPtr = args+strlen(args);

   // Add address of each flash region
   for (int index=0; ; index++) {
      MemoryRegionConstPtr memoryRegionPtr = parameters.getMemoryRegion(index);
      if (memoryRegionPtr == NULL) {
         break;
      }
      if (!memoryRegionPtr->isProgrammableMemory()) {
         continue;
      }
      sprintf(argPtr, " 0x%04X",
            memoryRegionPtr->getDummyAddress()&0xFFFF);
      argPtr += strlen(argPtr);
   }
   *argPtr++ = '\"';
   *argPtr++ = '\0';
#elif (TARGET == HCS12)
   char args[200] = "initTarget \"";
   char *argPtr = args+strlen(args);

   // Add address of each flash region
   for (int index=0; ; index++) {
      MemoryRegionConstPtr memoryRegionPtr = parameters.getMemoryRegion(index);
      if (memoryRegionPtr == NULL) {
         break;
      }
      if (!memoryRegionPtr->isProgrammableMemory()) {
         continue;
      }
      sprintf(argPtr, "{%s 0x%04X} ",
            memoryRegionPtr->getMemoryTypeName(),
            memoryRegionPtr->getDummyAddress()&0xFFFF);
      argPtr += strlen(argPtr);
   }
   *argPtr++ = '\"';
   *argPtr++ = '\0';
#elif (TARGET == RS08)
   char args[200] = "initTarget ";
   char *argPtr = args+strlen(args);
   sprintf(argPtr, "0x%04X 0x%04X 0x%04X",
         parameters.getSOPTAddress(),
         flashMemoryRegionPtr->getFOPTAddress(),
         flashMemoryRegionPtr->getFLCRAddress()
         );
   argPtr += strlen(argPtr);
   *argPtr++ = '\0';
#else
   char args[] = "initTarget \"\"";
#endif

   rc = runTCLCommand(args);
   if (rc != PROGRAMMING_RC_OK) {
      Logging::error("Failed - initTarget TCL failed\n");
      return rc;
   }
   return rc;
}

//=============================================================================
//! Prepares the target for Flash and eeprom operations. \n
//!
//! @return error code, see \ref USBDM_ErrorCode
//!
//! @note Assumes target has been reset & connected
//!
USBDM_ErrorCode FlashProgrammer::initialiseTargetFlash() {
   LOGGING;
   USBDM_ErrorCode rc;

   // Check if already configured
   if (flashReady) {
      return PROGRAMMING_RC_OK;
   }
#if (TARGET==RS08) || (TARGET==HCS08) || (TARGET==HCS12) || (TARGET==CFV1)
   unsigned long busFrequency;
#if (TARGET==RS08) || (TARGET==HCS08) || (TARGET==CFV1)
   // Configure the target clock for Flash programming
   rc = configureTargetClock(&busFrequency);
#elif (TARGET==HCS12)   
   // Configure the target clock for Flash programming
   rc = getTargetBusSpeed(&busFrequency);

   if (rc == PROGRAMMING_RC_ERROR_SPEED_APPROX) {
      // Estimated speed is not sufficiently accurate for programming

      // Check if user has supplied a speed to use
      if (parameters.getConnectionFreq() == 0)
         return PROGRAMMING_RC_ERROR_SPEED_APPROX;

      // Set user supplied speed & confirm SDID as basic communication check
      USBDM_SetSpeed(parameters.getConnectionFreq()/1000);
      if (FlashProgrammer::confirmSDID() != PROGRAMMING_RC_OK)
         return PROGRAMMING_RC_ERROR_SPEED_APPROX;

      busFrequency = parameters.getConnectionFreq()*parameters.getBDMtoBUSFactor();
      Logging::print("Using user-supplied bus speed = %d kHz\n",
            busFrequency/1000);
   }
   else
#endif
   if (rc != PROGRAMMING_RC_OK) {
      Logging::error("Failed to get speed\n");
      return rc;
   }
   // Convert to kHz
   uint32_t targetBusFrequency = (uint32_t)round(busFrequency/1000.0);
   flashOperationInfo.targetBusFrequency = targetBusFrequency;

   Logging::print("Target Bus Frequency = %ld kHz\n", targetBusFrequency);
#endif

   char buffer[100];
   sprintf(buffer, "initFlash %d", flashOperationInfo.targetBusFrequency);
   rc = runTCLCommand(buffer);
   if (rc != PROGRAMMING_RC_OK) {
      Logging::error("Failed, initFlash TCL failed\n");
      return rc;
   }
   // Flash is now ready for programming
   flashReady = TRUE;
   return PROGRAMMING_RC_OK;
}

//=======================================================================
//! \brief Does Mass Erase of Target memory using TCL script.
//!
//! @return error code, see \ref USBDM_ErrorCode
//!
USBDM_ErrorCode FlashProgrammer::massEraseTarget(void) {
   Logging log("FlashProgrammer::massEraseTarget");
   if (progressTimer != NULL) {
      progressTimer->restart("Mass Erasing Target");
   }
   USBDM_ErrorCode rc = initialiseTarget();
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
   // Do Mass erase using TCL script
   rc = runTCLCommand("massEraseTarget");
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
// Don't reset device as it may only be temporarily unsecured!
   return PROGRAMMING_RC_OK;
}

//==============================================================================
// Flag masks
#define DO_INIT_FLASH         (1<<0) // Do initialisation of flash
#define DO_ERASE_BLOCK        (1<<1) // Erase entire flash block e.g. Flash, FlexNVM etc
#define DO_ERASE_RANGE        (1<<2) // Erase range (including option region)
#define DO_BLANK_CHECK_RANGE  (1<<3) // Blank check region
#define DO_PROGRAM_RANGE      (1<<4) // Program range (including option region)
#define DO_VERIFY_RANGE       (1<<5) // Verify range
#define DO_PARTITION_FLEXNVM  (1<<7) // Program FlexNVM DFLASH/EEPROM partitioning
#define DO_TIMING_LOOP        (1<<8) // Counting loop to determine clock speed

// 9 - 14 reserved
#define IS_COMPLETE           (1<<15)

// Capability masks
#define CAP_ERASE_BLOCK        (1<<1)
#define CAP_ERASE_RANGE        (1<<2)
#define CAP_BLANK_CHECK_RANGE  (1<<3)
#define CAP_PROGRAM_RANGE      (1<<4)
#define CAP_VERIFY_RANGE       (1<<5)
#define CAP_PARTITION_FLEXNVM  (1<<7)
#define CAP_TIMING             (1<<7) // Todo change to 8

#define CAP_DSC_OVERLAY        (1<<11) // Indicates DSC code in pMEM overlays xRAM
#define CAP_DATA_FIXED         (1<<12) // Indicates TargetFlashDataHeader is at fixed address
//
#define CAP_RELOCATABLE        (1<<15) // Code may be relocated

#define OPT_SMALL_CODE         (0x80)

//=======================================================================
//! Loads the default Flash programming code to target memory
//!
//! @return error code, see \ref USBDM_ErrorCode
//!
//! @note - see loadTargetProgram(...) for details
//! @note - Tries device program code & then flashRegion specific if necessary
//!
USBDM_ErrorCode FlashProgrammer::loadTargetProgram(FlashOperation flashOperation) {
   LOGGING;
   // Try to get device general routines
   FlashProgramConstPtr flashProgram = parameters.getFlashProgram();
   if (!flashProgram) {
      Logging::print("No default flash program found - searching memory regions\n");
      // Try code from any flash region
      for (int index=0; ; index++) {
         MemoryRegionConstPtr memoryRegionPtr = parameters.getMemoryRegion(index);
         if (memoryRegionPtr == NULL) {
            break;
         }
         flashProgram = memoryRegionPtr->getFlashprogram();
         if (flashProgram != NULL) {
            break;
         }
      }
   }
   else {
      Logging::print("Using shared flash program\n");
   }
   if (!flashProgram) {
      Logging::error("No flash program found for target\n");
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   return loadTargetProgram(flashProgram, flashOperation);
}

//==============================================================================
//! Loads the Flash programming code to target memory
//!
//! @param  flashProgram      program to load
//! @param  flashOperation    intended operation in case of partial loading
//!
//! @return error code, see \ref USBDM_ErrorCode
//!
//! @note - Assumes the target has been connected to
//!         Confirms download (if necessary) and checks RAM boundaries.
//!
USBDM_ErrorCode FlashProgrammer::loadTargetProgram(FlashProgramConstPtr flashProgram, FlashOperation flashOperation) {
   LOGGING;
   memoryElementType     buffer[4000];

   Logging::print("Op=%s\n", getFlashOperationName(flashOperation));
   switch(flashOperation) {
      case OpSelectiveErase:
      case OpBlockErase:
      case OpBlankCheck:
      case OpProgram:
      case OpVerify:
      case OpPartitionFlexNVM:
      case OpTiming:
         break;
      default:
         currentFlashOperation = OpNone;
         Logging::print("No target program load needed\n");
         return BDM_RC_OK;
   }
   if (!flashProgram) {
      // Try to get device general routines
      flashProgram = parameters.getFlashProgram();
   }
   if (!flashProgram) {
      Logging::error("Failed, no flash program found for target\n");
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   // Reload flash code if
   //  - code changed
   //  - operation changed
   //  - alignment changed
   if (currentFlashProgram != flashProgram)  {
      Logging::print("Reloading due to change in flash code\n");
   }
   else if ((currentFlashOperation == OpNone) || (currentFlashOperation != flashOperation)) {
      Logging::print("Reloading due to change in flash operation\n");
   }
   else if (currentFlashAlignment != flashOperationInfo.alignment) {
      Logging::print("Reloading due to change in flash alignment\n");
   }
   else {
      Logging::print("Re-using existing code\n");
      return PROGRAMMING_RC_OK;
   }
   currentFlashOperation = OpNone;

   unsigned size; // In memoryElementType
   uint32_t loadAddress;
   USBDM_ErrorCode rc = loadSRec(flashProgram->flashProgram.c_str(),
                                 buffer,
                                 sizeof(buffer)/sizeof(buffer[0]),
                                 &size,
                                 &loadAddress);
   if (rc !=  BDM_RC_OK) {
      Logging::error("Failed, loadSRec() failed\n");
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
#if TARGET == MC56F80xx
   MemorySpace_t memorySpace = MS_XWord;
#else      
   MemorySpace_t memorySpace = MS_Byte;
#endif   
   // Probe RAM buffer
   rc = probeMemory(memorySpace, parameters.getRamStart());
   if (rc == BDM_RC_OK) {
      rc = probeMemory(memorySpace, parameters.getRamEnd());
   }
   if (rc != BDM_RC_OK) {
      return rc;
   }
#if (TARGET==HCS08)   
   LoadInfoStruct *infoPtr = (LoadInfoStruct *)buffer;
   targetProgramInfo.smallProgram = (infoPtr->flags&OPT_SMALL_CODE) != 0;
   infoPtr->flags &= ~OPT_SMALL_CODE;
   if (targetProgramInfo.smallProgram) {
      return loadSmallTargetProgram(buffer, loadAddress, size, flashProgram, flashOperation);
   }
   else {
      return loadLargeTargetProgram(buffer, loadAddress, size, flashProgram, flashOperation);
   }
#else
   targetProgramInfo.smallProgram = false;
   return loadLargeTargetProgram(buffer, loadAddress, size, flashProgram, flashOperation);
#endif
}

//=======================================================================
//! Loads the Flash programming code to target memory
//!
//! @param  buffer            buffer containing program image
//! @param  loadAddress       address to load image at
//! @param  size              size of image (in memoryElementType)
//! @param  flashProgram      flash program corresponding to image
//! @param  flashOperation    intended operation in case of partial loading
//!
//! @return error code, see \ref USBDM_ErrorCode
//!
//! @note - Assumes the target has been connected to
//!         Confirms download (if necessary) and checks RAM upper boundary.
//!         targetProgramInfo is updated with load information
//!
//! Target Memory map
//! +---------------------------------------------------+ -+
//! |   LargeTargetImageHeader  flashProgramHeader;     |  |
//! +---------------------------------------------------+   > Unchanging written once
//! |   Flash program code....                          |  |
//! +---------------------------------------------------+ -+
//!
USBDM_ErrorCode FlashProgrammer::loadLargeTargetProgram(memoryElementType    *buffer,
                                                        uint32_t              loadAddress,
                                                        uint32_t              size,
                                                        FlashProgramConstPtr  flashProgram,
                                                        FlashOperation        flashOperation) {
   LOGGING;
   Logging::print("Op=%s\n", getFlashOperationName(flashOperation));

   // Find 'header' in download image
   uint32_t headerAddress = getData16Target(buffer);
   LargeTargetImageHeader *headerPtr = (LargeTargetImageHeader*) (buffer+(headerAddress-loadAddress));
   if (headerPtr > (LargeTargetImageHeader*)(buffer+size)) {
      Logging::error("Header ptr out of range\n");
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   // Save the programming data structure
   uint32_t codeLoadAddress   = targetToNative16(headerPtr->loadAddress);
   uint32_t codeEntry         = targetToNative16(headerPtr->entry);
   uint32_t capabilities      = targetToNative16(headerPtr->capabilities);
   uint32_t dataHeaderAddress = targetToNative16(headerPtr->flashData);
   uint32_t calibFactor       = targetToNative32(headerPtr->calibFactor);

   Logging::print("Loaded Image (unmodified) :\n");
   Logging::print("   flashProgramHeader headerAddress   = 0x%08X\n",     headerAddress);
   Logging::print("   flashProgramHeader.loadAddress     = 0x%08X\n",     codeLoadAddress);
   Logging::print("   flashProgramHeader.entry           = 0x%08X\n",     codeEntry);
   Logging::print("   flashProgramHeader.capabilities    = 0x%08X(%s)\n", capabilities, getProgramCapabilityNames(capabilities));
   Logging::print("   flashProgramHeader.flashData       = 0x%08X\n",     dataHeaderAddress);

   if (codeLoadAddress != loadAddress) {
      Logging::error("Inconsistent actual (0x%06X) and image load addresses (0x%06X).\n",
            loadAddress, codeLoadAddress);
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   uint32_t codeLoadSize = size*sizeof(memoryElementType);

   if ((capabilities&CAP_RELOCATABLE)!=0) {
      // Relocate Code
      codeLoadAddress = (parameters.getRamStart()+3)&~3; // Relocate to start of RAM
      if (loadAddress != codeLoadAddress) {
         Logging::print("Loading at non-default address, load@0x%04X (relocated from=%04X)\n",
               codeLoadAddress, loadAddress);
         // Relocate entry point
         codeEntry += codeLoadAddress - loadAddress;
      }
   }
#if TARGET != MC56F80xx
   if ((codeLoadAddress < parameters.getRamStart()) || (codeLoadAddress > parameters.getRamEnd())) {
      Logging::error("Image load address is invalid.\n");
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   if ((codeEntry < parameters.getRamStart()) || (codeEntry > parameters.getRamEnd())) {
      Logging::error("Image Entry point is invalid.\n");
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
#endif
#if TARGET == MC56F80xx
   // Update location of where programming info will be located
   if ((capabilities&CAP_DSC_OVERLAY)!=0) {
      // Loading code into shared RAM - load data offset by code size
      Logging::print("FlashProgrammer::loadLargeTargetProgram() - loading data into overlayed RAM @ 0x%06X\n", dataHeaderAddress);
   }
   else {
      // Loading code into separate program RAM - load data RAM separately
      Logging::print("FlashProgrammer::loadLargeTargetProgram() - loading data into separate RAM @ 0x%06X\n", dataHeaderAddress);
   }
#else
   if ((capabilities&CAP_DATA_FIXED)==0) {
      // Relocate Data Entry to immediately after code
      dataHeaderAddress = codeLoadAddress + size;
      Logging::print("Relocating flashData @ 0x%06X\n", dataHeaderAddress);
   }
#endif

   // Required flash flashAlignmentMask
   uint32_t flashAlignmentMask = flashOperationInfo.alignment-1;
   uint32_t procAlignmentMask  = 1-1;

   // Save location of entry point
   targetProgramInfo.entry        = codeEntry;
   // Were to load flash buffer (including header)
   targetProgramInfo.headerAddress  = dataHeaderAddress;
   // Save offset of RAM data buffer
   uint32_t dataLoadAddress = dataHeaderAddress+sizeof(LargeTargetFlashDataHeader);
   // Align buffer address to worse case alignment for processor read
   dataLoadAddress = (dataLoadAddress+procAlignmentMask)&~procAlignmentMask;
   targetProgramInfo.dataOffset   = dataLoadAddress-dataHeaderAddress;
   // Save maximum size of the buffer (in memoryElementType)
   targetProgramInfo.maxDataSize  = parameters.getRamEnd()-dataLoadAddress+1;
   // Align buffer size to worse case alignment for processor read
   targetProgramInfo.maxDataSize  = targetProgramInfo.maxDataSize&~procAlignmentMask;
   // Align buffer size to flash alignment requirement
   targetProgramInfo.maxDataSize  = targetProgramInfo.maxDataSize&~flashAlignmentMask;
   // Save target program capabilities
   targetProgramInfo.capabilities = capabilities;
   // Save clock calibration factor
   targetProgramInfo.calibFactor    = calibFactor;

   Logging::print("AlignmentMask=0x%08X\n",
         flashAlignmentMask);
   Logging::print("Program code[0x%06X...0x%06X]\n",
         codeLoadAddress, codeLoadAddress+size-1);
   Logging::print("Parameters[0x%06X...0x%06X]\n",
         targetProgramInfo.headerAddress,
         targetProgramInfo.headerAddress+targetProgramInfo.dataOffset-1);
   Logging::print("RAM buffer[0x%06X...0x%06X]\n",
         targetProgramInfo.headerAddress+targetProgramInfo.dataOffset,
         targetProgramInfo.headerAddress+targetProgramInfo.dataOffset+targetProgramInfo.maxDataSize-1);
   Logging::print("Entry=0x%06X\n", targetProgramInfo.entry);

   // RS08, HCS08, HCS12 are byte aligned
   // MC56F80xx deals with word addresses which are always aligned
   if ((codeLoadAddress & procAlignmentMask) != 0){
      Logging::error("CodeLoadAddress is not aligned\n");
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   if (((targetProgramInfo.headerAddress+targetProgramInfo.dataOffset) & procAlignmentMask) != 0){
      Logging::error("FlashProgramHeader.dataOffset is not aligned\n");
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
#if (TARGET != ARM)
   if ((targetProgramInfo.entry & procAlignmentMask) != 0){
      Logging::error("FlashProgramHeader.entry is not aligned\n");
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
#else
   if ((targetProgramInfo.entry & procAlignmentMask) != 1){
      Logging::error("FlashProgramHeader.entry is not aligned\n");
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
#endif
   // Sanity check buffer
   if (((uint32_t)(targetProgramInfo.headerAddress+targetProgramInfo.dataOffset)<parameters.getRamStart()) ||
       ((uint32_t)(targetProgramInfo.headerAddress+targetProgramInfo.dataOffset+targetProgramInfo.maxDataSize-1)>parameters.getRamEnd())) {
      Logging::error("Data buffer location [0x%06X..0x%06X] is outside target RAM [0x%06X-0x%06X]\n",
            targetProgramInfo.headerAddress+targetProgramInfo.dataOffset,
            targetProgramInfo.headerAddress+targetProgramInfo.dataOffset+targetProgramInfo.maxDataSize-1,
            parameters.getRamStart(), parameters.getRamEnd());
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   if ((dataLoadAddress+40) > parameters.getRamEnd()) {
      Logging::error("Data buffer is too small [0x%X..0x%X] \n",
            dataLoadAddress, parameters.getRamEnd());
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
#if TARGET == MC56F80xx
   MemorySpace_t memorySpace = MS_PWord;
#elif TARGET == ARM
   MemorySpace_t memorySpace = MS_Long;
#elif (TARGET == HCS08) || (TARGET == HCS12)
   MemorySpace_t memorySpace = (MemorySpace_t)(MS_Fast|MS_Byte);
#else      
   MemorySpace_t memorySpace = MS_Byte;
#endif   
   headerPtr->flashData   = nativeToTarget16(targetProgramInfo.headerAddress);
   headerPtr->copctlAddress = nativeToTarget16(parameters.getCOPCTLAddress());

   Logging::print("Loaded Image (modified) :\n");
   Logging::print("   flashProgramHeader.loadAddress     = 0x%08X\n",      targetToNative16(headerPtr->loadAddress));
   Logging::print("   flashProgramHeader.entry           = 0x%08X\n",      targetToNative16(headerPtr->entry));
   Logging::print("   flashProgramHeader.capabilities    = 0x%08X(%s)\n",  capabilities,getProgramCapabilityNames(capabilities));
   Logging::print("   flashProgramHeader.flashData       = 0x%08X\n",      targetToNative16(headerPtr->flashData));
   Logging::print("   flashProgramHeader.copctlAddress   = 0x%08X\n",      targetToNative16(headerPtr->copctlAddress));

   if (currentFlashProgram != flashProgram)  {
      Logging::print("Reloading due to change in flash code\n");
      // Write the flash programming code to target memory
      if (WriteMemory(memorySpace, codeLoadSize, codeLoadAddress, (uint8_t *)buffer) != BDM_RC_OK) {
         return PROGRAMMING_RC_ERROR_BDM_WRITE;
      }
   }
   else {
      Logging::print("Suppressing code load as unchanged\n");
   }
   currentFlashProgram   = flashProgram;
   currentFlashOperation = flashOperation;
   currentFlashAlignment = flashOperationInfo.alignment;

   // Loaded routines support extended operations
   targetProgramInfo.programOperation = DO_BLANK_CHECK_RANGE|DO_PROGRAM_RANGE|DO_VERIFY_RANGE;
   return BDM_RC_OK;
}

//=======================================================================
//! Loads the Flash programming code to target memory
//!
//! @param  buffer            buffer containing data to load
//! @param  loadAddress       address to load at
//! @param  size              size of data in buffer
//! @param  flashProgram      program to load
//! @param  flashOperation    operation to do
//!
//! @return error code, see \ref USBDM_ErrorCode
//!
//! @note - Assumes the target has been connected to
//!         Confirms down-load (if necessary) and checks RAM upper boundary.
//!
//! Target Memory map (RAM buffer)
//! +-----------------------------------------+ -+
//! |   SmallTagetFlashDataHeader flashData;  |   > Write/Read
//! +-----------------------------------------+ -+
//! |   Data to program....                   |   > Write
//! +-----------------------------------------+ -+
//! |   Flash program code....                |   > Unchanging written once
//! +-----------------------------------------+ -+
//!
USBDM_ErrorCode FlashProgrammer::loadSmallTargetProgram(memoryElementType    *buffer,
                                                        uint32_t              loadAddress,
                                                        uint32_t              size,
                                                        FlashProgramConstPtr  flashProgram,
                                                        FlashOperation        flashOperation) {
   LOGGING_E;

   Logging::error("Not supported\n");
   return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
}

//! Probe RAM location
//!
//! @param memorySpace - Memory space and size of probe
//! @param address     - Address to probe
//!
//! @return BDM_RC_OK if successful
//!
USBDM_ErrorCode FlashProgrammer::probeMemory(MemorySpace_t memorySpace, uint32_t address) {
   Logging log("FlashProgrammer::probeMemory");
   static const uint8_t probe1[] = {0xA5, 0xF0,0xA5, 0xF0,};
   static const uint8_t probe2[] = {0x0F, 0x5A,0x0F, 0x5A,};
   uint8_t probeResult1[sizeof(probe1)];
   uint8_t probeResult2[sizeof(probe2)];
   uint8_t savedData[sizeof(probe1)];

   if (ReadMemory(memorySpace,memorySpace&MS_SIZE,address,savedData) != BDM_RC_OK)
      return PROGRAMMING_RC_ERROR_BDM_READ;
   if (WriteMemory(memorySpace,memorySpace&MS_SIZE,address,probe1) != BDM_RC_OK)
      return PROGRAMMING_RC_ERROR_BDM_WRITE;
   if (ReadMemory(memorySpace,memorySpace&MS_SIZE,address,probeResult1) != BDM_RC_OK)
      return PROGRAMMING_RC_ERROR_BDM_READ;
   if (WriteMemory(memorySpace,memorySpace&MS_SIZE,address,probe2) != BDM_RC_OK)
      return PROGRAMMING_RC_ERROR_BDM_WRITE;
   if (ReadMemory(memorySpace,memorySpace&MS_SIZE,address,probeResult2) != BDM_RC_OK)
      return PROGRAMMING_RC_ERROR_BDM_READ;
   if (WriteMemory(memorySpace,memorySpace&MS_SIZE,address,savedData) != BDM_RC_OK)
      return PROGRAMMING_RC_ERROR_BDM_WRITE;
   if ((memcmp(probe1, probeResult1, memorySpace&MS_SIZE) != 0) ||
       (memcmp(probe2, probeResult2, memorySpace&MS_SIZE) != 0)) {
      Logging::error("RAM memory probe failed @0x%08X\n", address);
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   return PROGRAMMING_RC_OK;
}

//! \brief Maps a Flash action vector to Text
//!
//! @param actions => action to describe
//!
//! @return pointer to static string buffer describing the actions
//!
static const char *getProgramActionNames(unsigned int actions) {
unsigned index;
static char buff[250] = "";
static const char *actionTable[] = {
"DO_INIT_FLASH|",         // Do initialisation of flash
"DO_ERASE_BLOCK|",        // Mass erase device
"DO_ERASE_RANGE|",        // Erase range (including option region)
"DO_BLANK_CHECK_RANGE|",  // Blank check region
"DO_PROGRAM_RANGE|",      // Program range (including option region)
"DO_VERIFY_RANGE|",       // Verify range
"??|",
"DO_PARTITION_FLEXNVM|",  // Partition FlexNVM boundary
"DO_TIMING_LOOP|",        // Execute timing loop on target
};
   buff[0] = '\0';
   for (index=0;
        index<sizeof(actionTable)/sizeof(actionTable[0]);
         index++) {
      uint32_t mask = 1<<index;
      if ((actions&mask) != 0) {
         strcat(buff,actionTable[index]);
         actions &= ~mask;
      }
   }
   if (actions&IS_COMPLETE) {
      actions &= ~IS_COMPLETE;
      strcat(buff,"IS_COMPLETE|");
   }
   if (actions != 0) {
      strcat(buff,"???");
   }
   return buff;
}

//! \brief Maps a Flash action vector to Text
//!
//! @param flashOperation => operation to describe
//!
//! @return pointer to static string buffer describing the flashOperation
//!
static const char *getFlashOperationName(FlashOperation flashOperation) {
   switch (flashOperation) {
   case OpNone                             : return "OpNone";
   case OpSelectiveErase                   : return "OpSelectiveErase";
   case OpBlockErase                       : return "OpBlockErase";
   case OpBlankCheck                       : return "OpBlankCheck";
   case OpProgram                          : return "OpProgram";
   case OpVerify                           : return "OpVerify";
   case OpWriteRam                         : return "OpWriteRam";
   case OpPartitionFlexNVM                 : return "OpPartitionFlexNVM";
   case OpTiming                           : return "OpTiming";
   default: break;
   }
   return "Op???";
}

//! \brief Maps a Flash capability vector to Text
//!
//! @param actions => actions to describe
//!
//! @return pointer to static string buffer describing actions
//!
static const char *getProgramCapabilityNames(unsigned int actions) {
unsigned index;
static char buff[250] = "";
static const char *actionTable[] = {
"??|",                     // Do initialisation of flash
"CAP_ERASE_BLOCK|",        // Mass erase device
"CAP_ERASE_RANGE|",        // Erase range (including option region)
"CAP_BLANK_CHECK_RANGE|",  // Blank check region
"CAP_PROGRAM_RANGE|",      // Program range (including option region)
"CAP_VERIFY_RANGE|",       // Verify range
"??|",
"DO_PARTITION_FLEXNVM|",   // Un/lock flash with default security options  (+mass erase if needed)
"CAP_TIMING|",             // Lock flash with default security options
};

   buff[0] = '\0';
   for (index=0;
        index<sizeof(actionTable)/sizeof(actionTable[0]);
         index++) {
      if ((actions&(1<<index)) != 0) {
         strcat(buff,actionTable[index]);
      }
   }
   if (actions&CAP_DSC_OVERLAY) {
      strcat(buff,"CAP_DSC_OVERLAY|");
   }
   if (actions&CAP_DATA_FIXED) {
      strcat(buff,"CAP_DATA_FIXED|");
   }
   if (actions&CAP_RELOCATABLE) {
      strcat(buff,"CAP_RELOCATABLE");
   }
   return buff;
}

USBDM_ErrorCode FlashProgrammer::convertTargetErrorCode(FlashDriverError_t rc) {

   switch (rc) {
   case FLASH_ERR_OK                : return PROGRAMMING_RC_OK;
   case FLASH_ERR_LOCKED            : return PROGRAMMING_RC_ERROR_SECURED;               // Flash is still locked
   case FLASH_ERR_ILLEGAL_PARAMS    : return PROGRAMMING_RC_ERROR_ILLEGAL_PARAMS;        // Parameters illegal
   case FLASH_ERR_PROG_FAILED       : return PROGRAMMING_RC_ERROR_FAILED_FLASH_COMMAND;  // STM - Programming operation failed - general
   case FLASH_ERR_PROG_WPROT        : return PROGRAMMING_RC_ERROR_SECURED;               // STM - Programming operation failed - write protected
   case FLASH_ERR_VERIFY_FAILED     : return PROGRAMMING_RC_ERROR_FAILED_VERIFY;         // Verify failed
   case FLASH_ERR_ERASE_FAILED      : return PROGRAMMING_RC_ERROR_NOT_BLANK;             // Not blank after erase
   case FLASH_ERR_TRAP              : return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED; // Program trapped (illegal instruction/location etc.)
   case FLASH_ERR_PROG_ACCERR       : return PROGRAMMING_RC_ERROR_FAILED_FLASH_COMMAND;  // Kinetis/CFVx - Programming operation failed - ACCERR
   case FLASH_ERR_PROG_FPVIOL       : return PROGRAMMING_RC_ERROR_FAILED_FLASH_COMMAND;  // Kinetis/CFVx - Programming operation failed - FPVIOL
   case FLASH_ERR_PROG_MGSTAT0      : return PROGRAMMING_RC_ERROR_FAILED_FLASH_COMMAND;  // Kinetis - Programming operation failed - MGSTAT0
   case FLASH_ERR_CLKDIV            : return PROGRAMMING_RC_ERROR_NO_VALID_FCDIV_VALUE;  // CFVx - Clock divider not set
   case FLASH_ERR_ILLEGAL_SECURITY  : return PROGRAMMING_RC_ERROR_ILLEGAL_SECURITY;      // CFV1+,Kinetis - Illegal value for security location
   case FLASH_ERR_UNKNOWN           : return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED; // Unspecified error
   case FLASH_ERR_TIMEOUT           : return PROGRAMMING_RC_ERROR_FAILED_FLASH_COMMAND;  // Unspecified error
   default                          : return PROGRAMMING_RC_ERROR_FAILED_FLASH_COMMAND;
   }
}

//=======================================================================
#if (TARGET == CFVx)
static bool usePSTSignals = false;
//! Check DSC run status
//!
//! @return BDM_RC_OK   - halted\n
//!         BDM_RC_BUSY - running\n
//!         other       - error
//!
USBDM_ErrorCode getRunStatus(void) {
   LOGGING;
   USBDMStatus_t USBDMStatus;
   USBDM_ErrorCode rc = USBDM_GetBDMStatus(&USBDMStatus);
   if (rc != BDM_RC_OK) {
      Logging::error("Failed, rc=%s\n", USBDM_GetErrorString(rc));
      return rc;
   }
   if (usePSTSignals) {
      // Check processor state using PST signals
      if (USBDMStatus.halt_state == TARGET_RUNNING) {
		   return BDM_RC_BUSY;
      }
      else {
         return BDM_RC_OK;
      }
   }
   else {
      // Probe D0 register - if fail assume processor running!
      unsigned long int dummy;
      rc = USBDM_ReadReg(CFVx_RegD0, &dummy);
      if (rc == BDM_RC_OK) {
         // Processor halted
         return BDM_RC_OK;
      }
      else /* if (rc == BDM_RC_CF_BUS_ERROR) */{
         // Processor executing
         return BDM_RC_BUSY;
      }
   }
}
#endif

//=======================================================================
#if (TARGET == MC56F80xx)
//! Check DSC run status
//!
//! @return BDM_RC_OK   - halted\n
//!         BDM_RC_BUSY - running\n
//!         other       - error
//!
USBDM_ErrorCode getRunStatus(void) {
   LOGGING;
   OnceStatus_t onceStatus;
   USBDM_ErrorCode rc = DSC_GetStatus(&onceStatus);
   if (rc != BDM_RC_OK) {
      Logging::error("Failed, rc=%s\n", USBDM_GetErrorString(rc));
      return rc;
   }
   switch (onceStatus) {
   case stopMode:
   case debugMode:
   case unknownMode:
   default:
      return BDM_RC_OK;
   case executeMode :
   case externalAccessMode:
      return BDM_RC_BUSY;
   }
}
#endif

#if 0 && defined(LOG) && (TARGET==ARM)
//! Report ARM status
//!
//! @param msg - message to print
//!
static void report(const char *msg) {
   LOGGING;
   uint8_t buff[10];
   if (USBDM_ReadMemory(2,2,0x40052000,buff) == BDM_RC_OK) {
      Logging::print("%s::report() - WDOG_STCTRLH=0x%02X\n", msg, getData16Target(buff));
   }
   else {
      Logging::error("%s::report() - Unable to read WDOG_STCTRLHL\n", msg);
   }
   uint8_t mc_srsh;
   uint8_t mc_srsl;
   // Assume if we can read SRS locations then they are valid (Kinetis chip)
   if ((USBDM_ReadMemory(1,1, MC_SRSH, &mc_srsh) == BDM_RC_OK) &&
       (USBDM_ReadMemory(1,1, MC_SRSL, &mc_srsl) == BDM_RC_OK)) {
      Logging::print("%s::report() - MC_SRSH=0x%02X, MC_SRSL=0x%02X \n", msg, mc_srsh, mc_srsl);
   }
   else {
      Logging::print("%s::report() - Unable to read MC_SRSH,MC_SRSL\n", msg);
   }
}
#endif

USBDM_ErrorCode FlashProgrammer::initLargeTargetBuffer(memoryElementType *buffer) {
   LOGGING;
   LargeTargetFlashDataHeader *pFlashHeader = (LargeTargetFlashDataHeader*)buffer;

   pFlashHeader->errorCode       = nativeToTarget16(-1);
   pFlashHeader->controller      = nativeToTarget16(flashOperationInfo.controller);
//   pFlashHeader->watchdogAddress = nativeToTarget16(parameters.getSOPTAddress());
   pFlashHeader->frequency       = nativeToTarget16(flashOperationInfo.targetBusFrequency);
   pFlashHeader->sectorSize      = nativeToTarget16(flashOperationInfo.sectorSize);
   pFlashHeader->address         = nativeToTarget32(flashOperationInfo.flashAddress);
   pFlashHeader->dataSize        = nativeToTarget16(flashOperationInfo.dataSize);
   pFlashHeader->dataAddress     = nativeToTarget16(targetProgramInfo.headerAddress+targetProgramInfo.dataOffset);

   uint32_t operation = 0;
   switch(currentFlashOperation) {
   case OpNone:
   case OpWriteRam:
   default:
      Logging::error("Unexpected operation %s\n", getFlashOperationName(currentFlashOperation));
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   case OpSelectiveErase:
      operation = DO_INIT_FLASH|DO_ERASE_RANGE;
      break;
   case OpProgram:
      operation = DO_INIT_FLASH|targetProgramInfo.programOperation;
      break;
   case OpVerify:
      operation = DO_INIT_FLASH|DO_VERIFY_RANGE;
      break;
   case OpBlankCheck:
      operation = DO_INIT_FLASH|DO_BLANK_CHECK_RANGE;
      break;
   case OpBlockErase:
      operation = DO_INIT_FLASH|DO_ERASE_BLOCK;
      break;
#if (TARGET == MC56F80xx) || (TARGET == HCS12) || (TARGET == CFVx)
   case OpTiming:
      operation = DO_TIMING_LOOP;
      break;
#endif
#if (TARGET==ARM) || (TARGET==CFV1)
   case OpPartitionFlexNVM:
      operation = DO_INIT_FLASH|DO_PARTITION_FLEXNVM;
      // Frequency field used for partition information
      pFlashHeader->frequency = nativeToTarget32(flashOperationInfo.flexNVMPartition);
      break;
#endif
   }
   pFlashHeader->flags           = nativeToTarget16(operation);

   Logging::print("flashOperationInfo.flashAddress = 0x%08X\n", flashOperationInfo.flashAddress);
   Logging::print("pFlashHeader->address = 0x%08X\n", pFlashHeader->address);

   Logging::print("Loaded parameters:\n");
   Logging::print("   currentFlashOperation  = %s\n",        getFlashOperationName(currentFlashOperation));
   Logging::print("   flags                  = %s\n",        getProgramActionNames(targetToNative16(pFlashHeader->flags)));
   Logging::print("   controller             = 0x%08X\n",    targetToNative16(pFlashHeader->controller));
// Logging::print("   watchdogAddress        = 0x%08X\n",    targetToNative16(pFlashHeader->watchdogAddress));
   Logging::print("   frequency              = %d (0x%X)\n", targetToNative16(pFlashHeader->frequency),targetToNative16(pFlashHeader->frequency));
   Logging::print("   sectorSize             = 0x%04X\n",    targetToNative16(pFlashHeader->sectorSize));
   Logging::print("   address                = 0x%08X\n",    targetToNative32(pFlashHeader->address));
   Logging::print("   dataSize               = 0x%08X\n",    targetToNative16(pFlashHeader->dataSize));
   Logging::print("   dataAddress            = 0x%08X\n",    targetToNative16(pFlashHeader->dataAddress));
   pFlashHeader->errorCode = (uint16_t)-1;
   return BDM_RC_OK;
}

USBDM_ErrorCode FlashProgrammer::initSmallTargetBuffer(memoryElementType *buffer) {
   LOGGING_Q;
   Logging::error("Small buffer not supported\n");
   return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
}

//=======================================================================
//! \brief Executes program on target.
//!
//! @return error code, see \ref USBDM_ErrorCode
//!
//! @param pBuffer  - buffer including space for header describing operation (may be NULL)
//! @param dataSize - size of data following header in memoryElementType units
//!
USBDM_ErrorCode FlashProgrammer::executeTargetProgram(memoryElementType *pBuffer, uint32_t dataSize) {
   LOGGING;
   Logging::print("dataSize=0x%X\n", dataSize);

   USBDM_ErrorCode rc = BDM_RC_OK;
   memoryElementType buffer[1000];
   if (pBuffer == NULL) {
      if (dataSize != 0) {
         Logging::error("Error: No buffer but size non-zero\n");
         return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
      }
      pBuffer = buffer;
   }
   if (targetProgramInfo.smallProgram) {
      rc = initSmallTargetBuffer(pBuffer);
   }
   else {
      rc = initLargeTargetBuffer(pBuffer);
   }
   if (rc != BDM_RC_OK) {
      return rc;
   }
#if 0 && defined(LOG) && (TARGET==ARM)
   report("FlashProgrammer::executeTargetProgram()");
#endif
   Logging::print("Writing Header+Data\n");

#if (TARGET==RS08)
   MemorySpace_t memorySpace = MS_Byte;
#elif (TARGET == MC56F80xx)
   MemorySpace_t memorySpace = MS_XWord;
#elif (TARGET == ARM)
   MemorySpace_t memorySpace = MS_Long; 
#elif (TARGET == HCS08) || (TARGET == HCS12)
   MemorySpace_t memorySpace = (MemorySpace_t)(MS_Fast|MS_Byte);
#else
   MemorySpace_t memorySpace = MS_Word;
#endif

   // Write the flash parameters & data to target memory
   if (WriteMemory(memorySpace,
                   (targetProgramInfo.dataOffset+dataSize)*sizeof(memoryElementType),
                   targetProgramInfo.headerAddress,
                   (uint8_t *)pBuffer) != BDM_RC_OK) {
      return PROGRAMMING_RC_ERROR_BDM_WRITE;
   }
   // Set target PC to start of code & verify
   long unsigned targetRegPC;
   if (WritePC(targetProgramInfo.entry) != BDM_RC_OK) {
      Logging::error("PC write failed\n");
      return PROGRAMMING_RC_ERROR_BDM_WRITE;
   }
   if (ReadPC(&targetRegPC) != BDM_RC_OK) {
      Logging::error("PC read failed\n");
      return PROGRAMMING_RC_ERROR_BDM_READ;
   }
   if ((targetProgramInfo.entry) != targetRegPC) {
      Logging::error("PC verify failed\n");
      return PROGRAMMING_RC_ERROR_BDM_WRITE;
   }
#if defined(LOG) && 0
   USBDMStatus_t status;
   USBDM_GetBDMStatus(&status);

   for (int num=0; num<1000; num++) {
      USBDM_ErrorCode rc = USBDM_TargetStep();
      if (rc != BDM_RC_OK) {
         Logging::error("TargetStep() Failed, rc=%s\n",
               USBDM_GetErrorString(rc));
         return rc;
      }
      unsigned long currentPC;
      rc = ReadPC(&currentPC);
      if (rc != BDM_RC_OK) {
         Logging::error("ReadPC() Failed, rc=%s\n",
               USBDM_GetErrorString(rc));
         report("FlashProgrammer::executeTargetProgram()");
         return rc;
      }
      if ((currentPC<(targetRegPC-0x1000))||(currentPC>(targetRegPC+0x1000))) {
         Logging::error("Read PC out of range, PC=0x%08X\n",
               currentPC);
         report("FlashProgrammer::executeTargetProgram()");
         return PROGRAMMING_RC_ERROR_BDM;
      }
      uint8_t  iBuffer[8];
      rc = ReadMemory(1, sizeof(iBuffer), currentPC, (uint8_t *)iBuffer);
      if (rc != BDM_RC_OK) {
         Logging::error("ReadMemory() Failed, rc=%s\n",
               USBDM_GetErrorString(rc));
         report("FlashProgrammer::executeTargetProgram()");
         return rc;
      }
      Logging::print("Step: PC=0x%06X => %02X %02X %02X %02X\n",
             currentPC, iBuffer[0], iBuffer[1], iBuffer[2], iBuffer[3]);
   }
#endif
   // Execute the Flash program on target
   if (TargetGo() != BDM_RC_OK) {
      Logging::error("TargetGo() failed\n");
      return PROGRAMMING_RC_ERROR_BDM;
   }
   progressTimer->progress(0, NULL);
#ifdef LOG
   Logging::print("Polling");
   int dotCount = 50;
#endif
   // Wait for target stop at execution completion
   int timeout = 1000; // x 50 ms
   unsigned long runStatus;
   do {
      milliSleep(50);
#ifdef LOG
      Logging::printq(".");
      if (++dotCount == 100) {
         Logging::printq("\n");
         dotCount = 0;
      }
#endif
      if (USBDM_ReadStatusReg(&runStatus) != BDM_RC_OK) {
         Logging::printq("\n");
         Logging::error("Status read failed\n");
         break;
      }
      progressTimer->progress(0, NULL);
   } while (((runStatus&HC12_BDMSTS_BDMACT) == 0) && (--timeout>0));
   Logging::printq("\n");
   TargetHalt();
   unsigned long value;
   USBDM_Connect();
   ReadPC(&value);
   Logging::print("Start PC = 0x%08X, end PC = 0x%08X\n", targetRegPC, value);

   // Read the flash parameters back from target memory
   ResultStruct executionResult;
   if (ReadMemory(memorySpace, sizeof(ResultStruct),
                  targetProgramInfo.headerAddress,
                  (uint8_t*)&executionResult) != BDM_RC_OK) {
      return PROGRAMMING_RC_ERROR_BDM_READ;
   }
   uint16_t errorCode = targetToNative16(executionResult.errorCode);
   if ((timeout <= 0) && (errorCode == FLASH_ERR_OK)) {
      errorCode = FLASH_ERR_TIMEOUT;
      Logging::error("Error, Timeout waiting for completion.\n");
   }
   if (targetProgramInfo.smallProgram) {
      Logging::print("Complete, errCode=%d\n", errorCode);
   }
   else {
      uint32_t flags = targetToNative16(executionResult.flags);
      if ((flags != IS_COMPLETE) && (errorCode == FLASH_ERR_OK)) {
         errorCode = FLASH_ERR_UNKNOWN;
         Logging::error("Error, Unexpected flag result.\n");
      }
      Logging::print("Complete, flags = 0x%08X(%s), errCode=%d\n",
            flags, getProgramActionNames(flags),
            errorCode);
   }
   rc = convertTargetErrorCode((FlashDriverError_t)errorCode);
   if (rc != BDM_RC_OK) {
      Logging::error("Error - %s\n", USBDM_GetErrorString(rc));
#if (TARGET == MC56F80xx) && 0
      executionResult.data = targetToNative16(executionResult.data);
      executionResult.dataSize = targetToNative16(executionResult.dataSize);
      Logging::print("   Address = 0x%06X, Data = 0x%04X\n", executionResult.data, executionResult.dataSize);
#endif
#if TARGET == CFV1
      uint8_t SRSreg;
      USBDM_ReadMemory(1, 1, 0xFF9800, &SRSreg);
      Logging::error("SRS = 0x%02X\n", SRSreg);
#endif
#if TARGET == HCS08
      uint8_t SRSreg;
      USBDM_ReadMemory(1, 1, 0x1800, &SRSreg);
      Logging::error("SRS = 0x%02X\n", SRSreg);
#endif
   }
#if defined(LOG) && 0
   uint8_t stackBuffer[50];
   ReadMemory(memorySpace, sizeof(stackBuffer), 0x3F0, stackBuffer);
#endif
   return rc;
}

#if (TARGET == CFVx) || (TARGET == HCS12) || (TARGET == MC56F80xx)
//=======================================================================
//! \brief Determines the target execution speed
//!
//! @return error code, see \ref USBDM_ErrorCode
//!
//! @note - Assumes flash programming code has already been loaded to target.
//!
USBDM_ErrorCode FlashProgrammer::determineTargetSpeed(void) {
   LOGGING;
   uint32_t targetBusFrequency = 0;

   flashOperationInfo.alignment = 1;
   flashOperationInfo.dataSize  = 0;

   // Load flash programming code to target
   USBDM_ErrorCode rc = loadTargetProgram(OpTiming);
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
   LargeTargetTimingDataHeader timingData = {0};
   timingData.flags      = nativeToTarget16(DO_TIMING_LOOP|IS_COMPLETE); // IS_COMPLETE as check - should be cleared
   timingData.controller = nativeToTarget16(-1);                         // Dummy value - not used

   Logging::print("flags      = 0x%08X(%s)\n",
         targetToNative16(timingData.flags), getProgramActionNames(targetToNative16(timingData.flags))
         );
   MemorySpace_t memorySpace = MS_Word;
   // Write the flash parameters & data to target memory
   if (WriteMemory(memorySpace, sizeof(LargeTargetTimingDataHeader),
                   targetProgramInfo.headerAddress, (uint8_t*)&timingData) != BDM_RC_OK) {
      return PROGRAMMING_RC_ERROR_BDM_WRITE;
   }
   // Set target PC to start of code & verify
   if (WritePC(targetProgramInfo.entry) != BDM_RC_OK) {
      return PROGRAMMING_RC_ERROR_BDM_WRITE;
   }
   // Execute the Flash program on target for 1 second
   if (TargetGo() != BDM_RC_OK) {
      Logging::error("USBDM_TargetGo failed\n");
      return PROGRAMMING_RC_ERROR_BDM;
   }
   milliSleep(1000);
   if (TargetHalt() != BDM_RC_OK) {
      Logging::error("USBDM_TargetHalt failed\n");
      return PROGRAMMING_RC_ERROR_BDM;
   }
   // Read the flash parameters back from target memory
   LargeTargetTimingDataHeader timingDataResult;
   if (ReadMemory(memorySpace, sizeof(timingDataResult),
                  targetProgramInfo.headerAddress, (uint8_t*)&timingDataResult) != BDM_RC_OK) {
      return PROGRAMMING_RC_ERROR_BDM_READ;
   }
   timingDataResult.flags        = targetToNative16(timingDataResult.flags);
   timingDataResult.errorCode    = targetToNative16(timingDataResult.errorCode);
   timingDataResult.timingCount  = targetToNative32(timingDataResult.timingCount);

   Logging::print("Complete, flags = 0x%08X(%s), errCode=%d\n",
         timingDataResult.flags,
         getProgramActionNames(timingDataResult.flags),
         timingDataResult.errorCode);
   unsigned long value;
   ReadPC(&value);
   Logging::print("Start PC = 0x%08X, end PC = 0x%08X\n", targetProgramInfo.entry, value);
   if ((timingDataResult.flags != DO_TIMING_LOOP) && (timingDataResult.errorCode == FLASH_ERR_OK)) {
      timingDataResult.errorCode    = FLASH_ERR_UNKNOWN;
      Logging::error("Error, Unexpected flag result\n");
   }
   if (timingDataResult.errorCode != FLASH_ERR_OK) {
      Logging::error("Error\n");
      return convertTargetErrorCode((FlashDriverError_t)timingDataResult.errorCode);
   }
   targetBusFrequency = 20*int(0.5+((200.0 * timingDataResult.timingCount)/targetProgramInfo.calibFactor));
   flashOperationInfo.targetBusFrequency = targetBusFrequency;
   Logging::print("Count = %d(0x%X) => Bus Frequency = %d kHz\n",
         timingDataResult.timingCount, timingDataResult.timingCount, targetBusFrequency);
   return PROGRAMMING_RC_OK;
}
#endif

//=======================================================================
//! Erase Target Flash memory
//!
//! @return error code see \ref USBDM_ErrorCode.
//!
USBDM_ErrorCode FlashProgrammer::eraseFlash(void) {
   LOGGING;
   USBDM_ErrorCode rc = BDM_RC_OK;
   progressTimer->restart("Erasing all flash blocks...");

   // Process each flash region
   for (int index=0; ; index++) {
      MemoryRegionConstPtr memoryRegionPtr = parameters.getMemoryRegion(index);
      if (memoryRegionPtr == NULL) {
         break;
      }
      if (!memoryRegionPtr->isProgrammableMemory()) {
         continue;
      }
      MemType_t memoryType = memoryRegionPtr->getMemoryType();
      Logging::print("Erasing %s\n", MemoryRegion::getMemoryTypeName(memoryType));

      uint32_t addressFlag  = 0;
      uint32_t flashAddress = memoryRegionPtr->getDummyAddress();

#if (TARGET == HCS08) || (TARGET == HCS12)
      if (memoryRegionPtr->getAddressType() == AddrLinear) {
         addressFlag |= ADDRESS_LINEAR;
      }
      if (memoryRegionPtr->getMemoryType() == MemEEPROM) {
         addressFlag |= ADDRESS_EEPROM;
      }
#endif
#if (TARGET == MC56F80xx)
      if (memoryType == MemXROM) {
         // |0x80 => XROM, |0x03 => Bank1 (Data)
         addressFlag |= 0x83000000;
      }
#endif      
#if (TARGET == CFV1) || (TARGET == ARM)
      if ((memoryType == MemFlexNVM) || (memoryType == MemDFlash)) {
         // Flag needed for DFLASH/flexNVM access
         addressFlag  |= (1<<23);
         flashAddress  = 0;
      }
#endif
      flashOperationInfo.flashAddress      = flashAddress|addressFlag;
      flashOperationInfo.controller        = memoryRegionPtr->getRegisterAddress();
      flashOperationInfo.sectorSize        = memoryRegionPtr->getSectorSize();
      flashOperationInfo.alignment         = memoryRegionPtr->getAlignment();
      flashOperationInfo.pageAddress       = memoryRegionPtr->getPageAddress();
      flashOperationInfo.dataSize          = 0;
      flashOperationInfo.flexNVMPartition  = (uint32_t)-1;

      FlashProgramConstPtr flashProgram = memoryRegionPtr->getFlashprogram();
      rc = loadTargetProgram(flashProgram, OpBlockErase);
      if (rc != PROGRAMMING_RC_OK) {
         Logging::error("loadTargetProgram() failed \n");
         return rc;
      }
      rc = executeTargetProgram();
      if (rc != PROGRAMMING_RC_OK) {
         return rc;
      }
   }
   return rc;
}

#if (TARGET == CFV1) || (TARGET == ARM) || (TARGET == HCS08)
//=======================================================================
//! Selective erases the target memory security areas.
//! This is only of use when the target is unsecured but the security
//! needs to be modified.
//!
//! @return error code see \ref USBDM_ErrorCode.
//!
USBDM_ErrorCode FlashProgrammer::selectiveEraseFlashSecurity(void) {
   LOGGING;
   USBDM_ErrorCode rc = BDM_RC_OK;
   if (!securityNeedsSelectiveErase) {
      Logging::print("Security areas are valid - no erasure required\n");
      return BDM_RC_OK;
   }
   progressTimer->restart("Erasing all flash security areas...");
   // Process each flash region
   for (int index=0; ; index++) {
      MemoryRegionConstPtr memoryRegionPtr = parameters.getMemoryRegion(index);
      if (memoryRegionPtr == NULL) {
         break;
      }
      if (!memoryRegionPtr->isProgrammableMemory()) {
         continue;
      }
      uint32_t securityAddress = memoryRegionPtr->getSecurityAddress();
      if (securityAddress == 0) {
         continue;
      }
      SecurityInfoConstPtr securityInfo = memoryRegionPtr->getSecureInfo();
      uint32_t securitySize = securityInfo->getSize();
      if (securityInfo == NULL) {
         continue;
      }
      Logging::print("Erasing security area %s[0x%06X..0x%06X]\n",
            memoryRegionPtr->getMemoryTypeName(), securityAddress, securityAddress+securitySize-1);

      flashOperationInfo.controller        = memoryRegionPtr->getRegisterAddress();
      flashOperationInfo.sectorSize        = memoryRegionPtr->getSectorSize();
      flashOperationInfo.alignment         = memoryRegionPtr->getAlignment();
      flashOperationInfo.pageAddress       = memoryRegionPtr->getPageAddress();
      flashOperationInfo.dataSize          = securitySize;
      flashOperationInfo.flexNVMPartition  = (uint32_t)-1;

      const FlashProgramConstPtr flashProgram = memoryRegionPtr->getFlashprogram();
      rc = loadTargetProgram(flashProgram, OpSelectiveErase);
      if (rc != PROGRAMMING_RC_OK) {
         return rc;
      }
      uint32_t addressFlag = 0;

#if (TARGET == HCS08) || (TARGET == HCS12)
      if (memoryRegionPtr->getAddressType() == AddrLinear) {
         addressFlag |= ADDRESS_LINEAR;
      }
      if (memoryRegionPtr->getMemoryType() == MemEEPROM) {
         addressFlag |= ADDRESS_EEPROM;
      }
#endif
#if (TARGET == MC56F80xx)
      MemType_t memoryType = memoryRegionPtr->getMemoryType();
      if (memoryType == MemXROM) {
         // |0x80 => XROM, |0x03 => Bank1 (Data)
         addressFlag |= 0x83000000;
      }
#endif
#if (TARGET == CFV1) || (TARGET == ARM)
      MemType_t memoryType = memoryRegionPtr->getMemoryType();
      if ((memoryType == MemFlexNVM) || (memoryType == MemDFlash)) {
         // Flag need for DFLASH/flexNVM access
         addressFlag |= (1<<23);
      }
#endif
      flashOperationInfo.flashAddress = securityAddress|addressFlag;
      if (flashOperationInfo.sectorSize == 0) {
         return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
      }
      rc = executeTargetProgram();
      if (rc != PROGRAMMING_RC_OK) {
         return rc;
      }
   }
   return rc;
}
#endif

#if (TARGET == CFV1) || (TARGET == ARM)
//=======================================================================
//! Program FlashNVM partion (DFlash/EEPROM backing store)
//!
//! @return error code see \ref USBDM_ErrorCode.
//!
//! @note - Assumes flash programming code has already been loaded to target.
//!
USBDM_ErrorCode FlashProgrammer::partitionFlexNVM() {
   LOGGING;
   uint8_t eeepromSize  = parameters.getFlexNVMParameters().eeepromSize;
   uint8_t partionValue = parameters.getFlexNVMParameters().partionValue;
   USBDM_ErrorCode rc = BDM_RC_OK;
   if ((eeepromSize==0xFF)&&(partionValue==0xFF)) {
      Logging::print("Skipping FlexNVM parameter programming as unprogrammed values\n");
      return BDM_RC_OK;
   }
   Logging::print("eeepromSize=0x%02X, partionValue=0x%02X\n", eeepromSize, partionValue);
   progressTimer->restart("Partitioning DFlash...");

   // Find flexNVM region
   MemoryRegionConstPtr memoryRegionPtr;
   for (int index=0; ; index++) {
      memoryRegionPtr = parameters.getMemoryRegion(index);
      if ((memoryRegionPtr == NULL) ||
          (memoryRegionPtr->getMemoryType() == MemFlexNVM)) {
         break;
      }
   }
   if (memoryRegionPtr == NULL) {
      Logging::print("No FlexNVM Region found\n");
      return PROGRAMMING_RC_ERROR_ILLEGAL_PARAMS;
   }
   MemType_t memoryType = memoryRegionPtr->getMemoryType();
   Logging::print("Partitioning %s\n", MemoryRegion::getMemoryTypeName(memoryType));
   const FlashProgramConstPtr flashProgram = memoryRegionPtr->getFlashprogram();
   rc = loadTargetProgram(flashProgram, OpPartitionFlexNVM);
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
   flashOperationInfo.flexNVMPartition  = (eeepromSize<<24UL)|(partionValue<<16UL);
   rc = executeTargetProgram();
   if (rc == PROGRAMMING_RC_ERROR_FAILED_FLASH_COMMAND) {
      // This usually means this error - more useful message
      rc = PROGRAMMING_RC_FLEXNVM_CONFIGURATION_FAILED;
   }
   return rc;
}
#endif

#if (TARGET == HCS12)
//=======================================================================
//! Checks for unsupported device
//!
USBDM_ErrorCode FlashProgrammer::checkUnsupportedTarget() {
   LOGGING;
   USBDM_ErrorCode rc;
   uint32_t targetSDID;
#define brokenUF32_SDID (0x6311)
//#define brokenUF32_SDID (0x3102) // for testing using C128

   // Get SDID from target
   rc = readTargetChipId(&targetSDID);
   if (rc != PROGRAMMING_RC_OK)
      return rc;

   // It's fatal to try unsecuring this chip using the BDM or
   // unsafe to program it to the secure state.
   // See errata MUCts01498
   if ((targetSDID == brokenUF32_SDID) &&
       ((parameters.getSecurity() != SEC_UNSECURED) ||
        (checkTargetUnSecured() != PROGRAMMING_RC_OK))) {
      Logging::error("Can't unsecure/secure UF32 due to hardware bug - See errata MUCts01498\n");
      return PROGRAMMING_RC_ERROR_CHIP_UNSUPPORTED;
   }
   return PROGRAMMING_RC_OK;
}
#endif

#if (TARGET == MC56F80xx) || (TARGET == HCS12)
//==================================================================================
//! Determines the target frequency by either of these methods: \n
//!   -  BDM SYNC Timing \n
//!   -  Execution of a timing program on target (only if unsecured & no SYNC)
//!
//! @param busFrequency  : Target bus frequency (in Hz)
//!
//! @return error code, see \ref USBDM_ErrorCode \n
//!      - PROGRAMMING_RC_OK                 - speed accurately determined \n
//!      - PROGRAMMING_RC_ERROR_SPEED_APPROX - speed estimated (not suitable for programming) \n
//!      - PROGRAMMING_RC_ERROR_FAILED_CLOCK - speed timing program failed
//!
//! @note - Assumes the target has been initialised. \n
//!       - Re-connects to target.
//!
USBDM_ErrorCode FlashProgrammer::getTargetBusSpeed(unsigned long *busFrequency) {
   LOGGING;
   unsigned long connectionFrequency;
   USBDMStatus_t bdmStatus;
   USBDM_ErrorCode rc;

//   Logging::print("FlashProgrammer::getTargetBusSpeed()\n");

   // Check target connection
   // BDM_RC_BDM_EN_FAILED may mean the target is secured
   rc = USBDM_Connect();
   if (((rc != BDM_RC_OK) && (rc != BDM_RC_BDM_EN_FAILED)) ||
       (USBDM_GetBDMStatus(&bdmStatus) != BDM_RC_OK)) {
      Logging::error("Failed connection\n");
      return PROGRAMMING_RC_ERROR_BDM_CONNECT;
   }

   // If BDM SYNC worked then use that speed
   if ((bdmStatus.connection_state == SPEED_SYNC) &&
       (USBDM_GetSpeedHz(&connectionFrequency) == BDM_RC_OK)) {
      // Use speed determined by BDM SYNC pulse
      *busFrequency = parameters.getBDMtoBUSFactor()*connectionFrequency;
      Logging::print("Using SYNC method, Bus Frequency = %ld kHz\n",
            (unsigned long)round(*busFrequency/1000.0));
      return PROGRAMMING_RC_OK;
   }

   // We can only approximate the target speed if secured & guessed
   if ((checkTargetUnSecured() == PROGRAMMING_RC_ERROR_SECURED) &&
       (bdmStatus.connection_state == SPEED_GUESSED) &&
       (USBDM_GetSpeedHz(&connectionFrequency) == BDM_RC_OK)) {
      // Use speed determined by BDM guessing
      *busFrequency = parameters.getBDMtoBUSFactor()*connectionFrequency;
      Logging::print("FlashProgrammer::getTargetBusSpeed() - Using Approximate method, Bus Frequency = %ld kHz\n",
            (unsigned long)round(*busFrequency/1000.0));
      return PROGRAMMING_RC_ERROR_SPEED_APPROX;
   }
   // We must have a connection for the next method
   if (rc != BDM_RC_OK) {
      Logging::error("Failed connection\n");
      return PROGRAMMING_RC_ERROR_BDM_CONNECT;
   }
   //
   // Try to determine target speed by down-loading a timing program to the target
   //
   USBDM_ErrorCode flashRc = determineTargetSpeed();
   if (flashRc != PROGRAMMING_RC_OK) {
      Logging::error("Failed connection\n");
      return flashRc;
   }
   *busFrequency = 1000*flashOperationInfo.targetBusFrequency;

   Logging::print("FlashProgrammer::getTargetBusSpeed() - Using Timing Program method, Bus Frequency = %ld kHz\n",
        (unsigned long)round(*busFrequency/1000.0));

   return PROGRAMMING_RC_OK;
}
#endif

//=======================================================================
//! Check security state of target
//!
//! @return PROGRAMMING_RC_OK => device is unsecured           \n
//!         PROGRAMMING_RC_ERROR_SECURED => device is secured  \n
//!         else error code see \ref USBDM_ErrorCode
//!
//! @note Assumes the target device has already been opened & USBDM options set.
//!
USBDM_ErrorCode FlashProgrammer::checkTargetUnSecured() {
   Logging log("FlashProgrammer::checkTargetUnSecured");
   USBDM_ErrorCode rc = initialiseTarget();
   if (rc != PROGRAMMING_RC_OK)
      return rc;
   if (runTCLCommand("isUnsecure") != PROGRAMMING_RC_OK) {
      Logging::print("Secured\n");
      return PROGRAMMING_RC_ERROR_SECURED;
   }
   Logging::print("Unsecured\n");
   return PROGRAMMING_RC_OK;
}

const int MaxSecurityAreaSize = 100;
struct SecurityDataCache {
   uint32_t address;                   //!< start address of security area
   uint32_t size;                      //!< size of area
   uint8_t  data[MaxSecurityAreaSize]; //!< security area data
};
unsigned securityAreaCount = 0;
SecurityDataCache securityData[2];

//===========================================================================================================
//! Clears the record of modified security areas
//!
void FlashProgrammer::deleteSecurityAreas(void) {
   securityAreaCount = 0;
}

//===========================================================================================================
//! Record the original contents of a security area for later restoration
//!
//! @param address    Start address of security area
//! @param size       Size of area
//! @param data       Security area data
//!
//! @return error code see \ref USBDM_ErrorCode.
//!
USBDM_ErrorCode FlashProgrammer::recordSecurityArea(const uint32_t address, const int size, const uint8_t *data) {
   if (securityAreaCount >= sizeof(securityData)/sizeof(securityData[0])) {
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   if (size > MaxSecurityAreaSize) {
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
  securityData[securityAreaCount].address = address;
  securityData[securityAreaCount].size    = size;
  memcpy(securityData[securityAreaCount].data, data, size);
  securityAreaCount++;
  return PROGRAMMING_RC_OK;
}

//===========================================================================================================
//! Restores the contents of the security areas to their original values
//!
//! @param flashImage    Flash contents to be programmed.
//!
void FlashProgrammer::restoreSecurityAreas(FlashImage &flashImage) {
   LOGGING_Q;
   for (unsigned index=0; index<securityAreaCount; index++) {
      Logging::print("Restoring security area in image [0x%06X...0x%06X]\n",
            securityData[index].address, securityData[index].address+securityData[index].size-1);
      flashImage.loadDataBytes(securityData[index].size, securityData[index].address, securityData[index].data);
   }
}

//===========================================================================================================
//! Modifies the Security locations in the flash image according to required security options of flashRegion
//!
//! @param flashImage    Flash contents to be programmed.
//! @param flashRegion   The memory region involved (to determine security area if any)
//!
USBDM_ErrorCode FlashProgrammer::setFlashSecurity(FlashImage &flashImage, MemoryRegionConstPtr flashRegion) {
   LOGGING;
   uint32_t securityAddress = flashRegion->getSecurityAddress();

   if (securityAddress == 0) {
      Logging::print("No security area, not modifying flash image\n");
      return PROGRAMMING_RC_OK;
   }
   SecurityInfoConstPtr securityInfo;
   bool dontOverwrite =  false;
   switch (parameters.getSecurity()) {
      case SEC_SECURED:
         Logging::print("Setting image as secured\n");
         securityInfo = flashRegion->getSecureInfo();
         break;
      case SEC_UNSECURED:
         Logging::print("Setting image as unsecured\n");
         securityInfo = flashRegion->getUnsecureInfo();
         break;
      case SEC_CUSTOM:
         Logging::print("Setting image security to custom value\n");
         securityInfo = flashRegion->getCustomSecureInfo();
         break;
      case SEC_INTELLIGENT:
         Logging::print("Setting image as intelligently unsecured\n");
         securityInfo = flashRegion->getUnsecureInfo();
         dontOverwrite = true;
         break;
      case SEC_DEFAULT:   //ToDo Unchanged
         Logging::print("Leaving flash image unchanged\n");
         securityInfo = flashRegion->getUnsecureInfo();
         break;
      default:
         return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   if (securityInfo == NULL) {
      Logging::error("Error - No settings for security area!\n");
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   int size = securityInfo->getSize();
   if (parameters.getSecurity() == SEC_DEFAULT) {
      // Check if security area exists in image
      // If so - selective erase if needed
      for(int index=0; index<size; index++) {
         if (flashImage.isValid(securityAddress+index)) {
            Logging::print("Security area may need erasing\n");
            securityNeedsSelectiveErase = true;
            break;
         }
      }
      return BDM_RC_OK;
   }
   uint8_t data[size];
   memcpy(data, securityInfo->getData(), size);
   if (dontOverwrite) {
      // Copy any existing data from memory array
      for(int index=0; index<size; index++) {
         if (flashImage.isValid(securityAddress+index)) {
            data[index] = flashImage.getValue(securityAddress+index);
         }
      }
   }
   uint8_t memory[size];
   USBDM_ReadMemory(MS_Byte, size, securityAddress, memory);
   // Save contents of current security area in Flash
   recordSecurityArea(securityAddress, size, memory);
   if (memcmp(data, memory, size) == 0) {
      if ((parameters.getEraseOption() == DeviceData::eraseMass) ||
          (parameters.getEraseOption() == DeviceData::eraseNone)) {
         // Clear security area in image to prevent re-programming
         Logging::print("Clearing security area as already valid and not being erased\n");
         for(int index=0; index<size; index++) {
            flashImage.remove(securityAddress+index);
         }
      }
      else {
         // eraseAll & eraseSelective will erase areas anyway so we have to re-program
         Logging::print("Security area is already valid but will be erased anyway (eraseAll or eraseSelective)\n");
         flashImage.loadDataBytes(size, securityAddress, data, dontOverwrite);
      }
   }
   else {
      Logging::print("Security area may need erasing\n");
      // Force erase of security area when mass erased (if necessary)
      securityNeedsSelectiveErase = true;
      flashImage.loadDataBytes(size, securityAddress, data, dontOverwrite);
#ifdef LOG
      Logging::print("Setting security region, \n"
            "              mem[0x%06X-0x%06X] = ", securityAddress, securityAddress+size/sizeof(memoryElementType)-1);
      Logging::printDump(data, size, securityAddress);
#endif
   }
   return PROGRAMMING_RC_OK;
}

//===============================================================================================
//! Modifies the Security locations in the flash image according to required security options
//!
//! @param flashImage  -  Flash image to be modified
//!
//! @return error code see \ref USBDM_ErrorCode.
//!
USBDM_ErrorCode FlashProgrammer::setFlashSecurity(FlashImage &flashImage) {
   LOGGING;
   // Process each flash region
   USBDM_ErrorCode rc = BDM_RC_OK;
   securityNeedsSelectiveErase = false; // Assume security areas are valid
   deleteSecurityAreas();
   for (int index=0; ; index++) {
      MemoryRegionConstPtr memoryRegionPtr = parameters.getMemoryRegion(index);
      if (memoryRegionPtr == NULL) {
         break;
      }
      rc = setFlashSecurity(flashImage, memoryRegionPtr);
      if (rc != BDM_RC_OK) {
         break;
      }
   }
   return rc;
}

//=======================================================================
// Executes a TCL script in the current TCL interpreter
//
USBDM_ErrorCode FlashProgrammer::runTCLScript(TclScriptConstPtr script) {
   Logging log("FlashProgrammer::runTCLScript");
   if (tclInterpreter == NULL) {
      Logging::error("No TCL Interpreter\n");
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   int rc = evalTclScript(tclInterpreter, script->getScript().c_str());
   const char *result = getTclResult(tclInterpreter);
   if (rc != 0) {
      // Unexpected failure!
      Logging::error("Failed\n");
      Logging::error(script->toString().c_str());
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   if ((result != NULL) && (*result != '\0')) {
      // Error return
      Logging::error("Result = \'%s\'\n", result);
      return PROGRAMMING_RC_ERROR_TCL_SCRIPT;
   }
   return PROGRAMMING_RC_OK;
}

//=======================================================================
// Executes a TCL command previously loaded in the TCL interpreter
//
USBDM_ErrorCode FlashProgrammer::runTCLCommand(const char *command) {
   Logging log("FlashProgrammer::runTCLCommand");
   Logging::print("Command = '%s'\n", command);
   if (tclInterpreter == NULL) {
      Logging::error("No TCL Interpreter\n");
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   int rc = evalTclScript(tclInterpreter, command);
   const char *result = getTclResult(tclInterpreter);
   if (rc != 0) {
      // Unexpected failure!
      Logging::error("TCL Command '%s' failed\n", command);
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   if ((result != NULL) && (*result != '\0')) {
      // Error return
      Logging::error("Result = \'%s\'\n", result);
      return PROGRAMMING_RC_ERROR_TCL_SCRIPT;
   }
   return PROGRAMMING_RC_OK;
}

//=======================================================================
// Initialises TCL support for current target
//
USBDM_ErrorCode FlashProgrammer::initTCL(void) {
   Logging log("FlashProgrammer::initTCL");

   // Set up TCL interpreter only once
   if (tclInterpreter != NULL) {
      return PROGRAMMING_RC_OK;
   }
//   FILE *fp = fopen("c:/delme.log", "wt");
//   tclInterpreter = createTclInterpreter(TARGET_TYPE, fp);
   tclInterpreter = createTclInterpreter(TARGET_TYPE, Logging::getLogFileHandle());
   if (tclInterpreter == NULL) {
      Logging::error("No TCL interpreter\n");
      return PROGRAMMING_RC_ERROR_TCL_SCRIPT;
   }
   // Run initial TCL script (loads routines)
   TclScriptConstPtr script = parameters.getFlashScripts();
   if (!script) {
      Logging::error("No TCL script found\n");
      return PROGRAMMING_RC_ERROR_TCL_SCRIPT;
   }
#if defined(LOG) && 0
   Logging::print("FlashProgrammer::initTCL()\n");
   Logging::print(script->toString().c_str());
#endif
   USBDM_ErrorCode rc = runTCLScript(script);
   if (rc != PROGRAMMING_RC_OK) {
      Logging::error("runTCLScript() failed\n");
      return rc;
   }
   return PROGRAMMING_RC_OK;
}

//=======================================================================
//  Release the current TCL interpreter
//
USBDM_ErrorCode FlashProgrammer::releaseTCL(void) {
   Logging log("FlashProgrammer::releaseTCL");
   if (tclInterpreter != NULL) {
      freeTclInterpreter(tclInterpreter);
      tclInterpreter = NULL;
   }
   return PROGRAMMING_RC_OK;
}

//==================================================================================
//! Applies a flash operation to a block of Target Flash memory
//!
//! @param flashImage       Description of flash contents to be processed.
//! @param blockSize        Size of block to process (bytes)
//! @param flashAddress     Start address of block in memory to process
//! @param flashOperation   Operation to do on flash
//!
//! @return error code see \ref USBDM_ErrorCode.
//!
//! @note - Assumes flash programming code has already been loaded to target.
//! @note - The memory range must be within one page for paged devices.
//!
USBDM_ErrorCode FlashProgrammer::doFlashBlock(FlashImage     *flashImage,
                                              unsigned int    blockSize,
                                              uint32_t       &flashAddress,
                                              FlashOperation flashOperation) {
   Logging log("FlashProgrammer::doFlashBlock");
   Logging::print("op=%s, [0x%06X..0x%06X]\n",
         getFlashOperationName(flashOperation), flashAddress, flashAddress+blockSize-1);

   if (!flashReady) {
      Logging::error("FlashProgrammer::doFlashBlock() - Error, Flash not ready\n");
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   // OK for empty block
   if (blockSize==0) {
      return PROGRAMMING_RC_OK;
   }
   //
   // Find flash region to program - this will recurse to handle sub regions
   //
   MemorySpace_t memorySpace = MS_None;
   uint32_t      offset      = 0;
#if (TARGET == MC56F80xx)
   if (flashAddress >= FlashImage::DataOffset) {
      memorySpace = MS_Data;
      offset      = FlashImage::DataOffset;
   }
   else {
      memorySpace = MS_Program;
      offset      = 0;
   }
#endif
   // Locate containing Memory region (Programmable or RAM)
   MemoryRegionConstPtr memoryRegionPtr;
   bool foundRegion = false;
   for (int index=0; !foundRegion ; index++) {
      memoryRegionPtr = parameters.getMemoryRegion(index);
      if (memoryRegionPtr == NULL) {
         // No suitable region found
         break;
      }
      Logging::print("Checking %s[0x%06X..0x%06X]...\n",
            memoryRegionPtr->getMemoryTypeName(),
            memoryRegionPtr->getMemoryRange(0)->start,
            memoryRegionPtr->getMemoryRange(0)->end);
      uint32_t lastContiguous;
      if (!memoryRegionPtr->findLastContiguous((flashAddress-offset), &lastContiguous, memorySpace)) {
         // Not in this memory region
         Logging::print("  ...Not in this region\n");
         continue;
      }
      lastContiguous = lastContiguous + offset; // Convert to last byte

      // Check if block crosses boundary and will need to be split
      if ((flashAddress+blockSize-1) > lastContiguous) {
         // The block is split into an contiguous block + rest. Each is handled by recursion
         Logging::print("  ...Block crosses FLASH boundary - recursing\n");
         uint32_t firstBlockSize = lastContiguous - flashAddress + 1;
         USBDM_ErrorCode rc;
         rc = doFlashBlock(flashImage, firstBlockSize, flashAddress, flashOperation);
         if (rc != PROGRAMMING_RC_OK) {
            return rc;
         }
         rc = doFlashBlock(flashImage, blockSize-firstBlockSize, flashAddress, flashOperation);
         return rc;
      }
      if (memoryRegionPtr->isProgrammableMemory()) {
         switch (flashOperation) {
            case OpBlankCheck:
            case OpProgram:
            case OpSelectiveErase:
            case OpVerify:
               // OK Flash operations
               foundRegion = true;
               break;
            case OpWriteRam:
               // Assume to be done in later RAM phase
               Logging::print("  ...Skipping block %s[0x%06X..0x%06X]\n",
                     memoryRegionPtr->getMemoryTypeName(),
                     flashAddress-offset, flashAddress-offset+blockSize-1);
               // No further processing of this block
               flashAddress += blockSize;
               return BDM_RC_OK;
            default:
         // case OpNone, OpBlockErase, OpPartitionFlexNVM, OpTiming
               // Keep looking
               break;
         }
      }
      else if (doRamWrites) {
         switch (flashOperation) {
            case OpBlankCheck:
            case OpProgram:
            case OpSelectiveErase:
               // Assume done in earlier Flash pass or not applicable
               Logging::print("  ...Skipping block %s[0x%06X..0x%06X]\n",
                     memoryRegionPtr->getMemoryTypeName(),
                     flashAddress-offset, flashAddress-offset+blockSize-1);
               // No further processing of this block
               flashAddress += blockSize;
               return BDM_RC_OK;
            case OpWriteRam:
            case OpVerify:
               // OK to write to & verify RAM
               if ((memoryRegionPtr->getMemoryType() == MemRAM) ||
                   (memoryRegionPtr->getMemoryType() == MemPRAM) ||
                   (memoryRegionPtr->getMemoryType() == MemXRAM)) {
                  foundRegion = true;
               }
               break;
            default:
         // case OpNone, OpBlockErase, OpPartitionFlexNVM, OpTiming
               // Keep looking
               break;
         }
      }
   }
   if (!foundRegion) {
      Logging::error("Block %s[0x%06X...] is not within target memory.\n",
            getMemSpaceName(memorySpace), flashAddress);
      return PROGRAMMING_RC_ERROR_OUTSIDE_TARGET_FLASH;
   }
   MemType_t memoryType = memoryRegionPtr->getMemoryType();
   Logging::print("Processing %s[0x%06X..0x%06X]\n",
         MemoryRegion::getMemoryTypeName(memoryType),
         flashAddress, flashAddress+blockSize-1);

   flashOperationInfo.controller = memoryRegionPtr->getRegisterAddress();
   flashOperationInfo.alignment  = memoryRegionPtr->getAlignment();
   flashOperationInfo.sectorSize = memoryRegionPtr->getSectorSize();

   if ((flashOperation == OpSelectiveErase) && (flashOperationInfo.sectorSize == 0)) {
      Logging::error("Error: sector size is 0\n");
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   USBDM_ErrorCode rc = loadTargetProgram(memoryRegionPtr->getFlashprogram(), flashOperation);
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
   // Maximum split block size must be made less than buffer RAM available
   unsigned int maxSplitBlockSize = targetProgramInfo.maxDataSize;

   const unsigned int MaxSplitBlockSize = 0x4000;
   memoryElementType  buffer[MaxSplitBlockSize+50];
   memoryElementType *bufferData = buffer+targetProgramInfo.dataOffset;

   // Maximum split block size must be made less than buffer size
   if (maxSplitBlockSize > MaxSplitBlockSize) {
      maxSplitBlockSize = MaxSplitBlockSize;
   }
   uint32_t alignMask = memoryRegionPtr->getAlignment()-1;
   Logging::print("Align mask = 0x%08X\n", alignMask);

   // splitBlockSize must be aligned
   maxSplitBlockSize &= ~alignMask;

   // Calculate any odd padding bytes at start of block
   unsigned int oddBytes = flashAddress & alignMask;

   uint32_t addressFlag = 0;

#if (TARGET == HCS08) || (TARGET == HCS12)
   if (memoryRegionPtr->getMemoryType() == MemEEPROM) {
      Logging::print("Setting EEPROM address flag\n");
      addressFlag |= ADDRESS_EEPROM;
   }
   // Set up linear address
   if (memoryRegionPtr->getAddressType() == AddrLinear) {
      // Set Linear address
      Logging::print("Setting Linear address\n");
      addressFlag |= ADDRESS_LINEAR;
   }
#endif
#if (TARGET == MC56F80xx)
      if (memoryType == MemXROM) {
         // |0x80 => XROM, |0x03 => Bank1 (Data)
         Logging::print("Setting MemXROM address\n");
         addressFlag = 0x83000000;
      }
#endif
#if (TARGET == CFV1) || (TARGET==ARM)
      if ((memoryType == MemFlexNVM) || (memoryType == MemDFlash)) {
         // Flag needed for DFLASH/flexNVM access
         addressFlag |= (1<<23);
      }
#endif
   // Round start address off to alignment requirements
   flashAddress  &= ~alignMask;

   // Pad block size with odd leading bytes
   blockSize += oddBytes;

   // Pad block size to alignment requirements
   blockSize = (blockSize+alignMask)&~alignMask;

   progressTimer->progress(0, NULL);

   while (blockSize>0) {
      unsigned flashIndex  = 0;
      unsigned size        = 0;
      // Determine size of block to process
      unsigned int splitBlockSize = blockSize;
      if ((flashOperation == OpProgram)||(flashOperation == OpVerify)||(flashOperation == OpWriteRam)) {
//         Logging::print("FlashProgrammer::doFlashBlock() #2  maxSplitBlockSize=0x%06X, splitBlockSize=0x%06X, blockSize=0x%X\n", maxSplitBlockSize, splitBlockSize, blockSize);
         // Requires data transfer using buffer
         if (splitBlockSize>maxSplitBlockSize) {
            splitBlockSize = maxSplitBlockSize;
         }
         // Pad any odd leading elements as 0xFF..
         for (flashIndex=0; flashIndex<oddBytes; flashIndex++) {
            bufferData[flashIndex] = (memoryElementType)-1;
         }
         // Copy flash data to buffer
         for(flashIndex=0; flashIndex<splitBlockSize; flashIndex++) {
            bufferData[flashIndex] = flashImage->getValue(flashAddress+flashIndex);
         }
         // Pad trailing elements to aligned address
         for (; (flashIndex&alignMask) != 0; flashIndex++) {
            bufferData[flashIndex] = flashImage->getValue(flashAddress+flashIndex);
         }
         // Actual data bytes to write
         size = flashIndex;
      }
      else {
         // No data transfer so no size limits
         flashIndex  = (blockSize+alignMask)&~alignMask;
         size = 0;
      }
      uint32_t targetAddress = flashAddress;

#if (TARGET == HCS08) || (TARGET == HCS12)
      // Map paged address
      if (memoryRegionPtr->getAddressType() != AddrLinear) {
         uint8_t pageNo;
         rc = getPageAddress(memoryRegionPtr, flashAddress, &pageNo);
         if (rc != PROGRAMMING_RC_OK) {
            return rc;
         }
         targetAddress = (pageNo<<16)|(flashAddress&0xFFFF);
      }
#endif
      flashOperationInfo.flashAddress = addressFlag|targetAddress;
      flashOperationInfo.dataSize     = flashIndex;
      if (splitBlockSize==0) {
         Logging::error("FlashProgrammer::doFlashBlock() - Error: splitBlockSize size is 0\n");
         return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
      }
      flashOperationInfo.pageAddress  = memoryRegionPtr->getPageAddress();
      USBDM_ErrorCode rc;
      if (flashOperation == OpWriteRam) {
         Logging::print("ramBlock[0x%06X..0x%06X]\n", flashAddress, flashAddress+splitBlockSize-1);
#if (TARGET == ARM)
         rc = WriteMemory(MS_Long, splitBlockSize, flashAddress, (uint8_t *)buffer+targetProgramInfo.dataOffset);
#elif (TARGET == MC56F80xx)
         rc = WriteMemory(MS_XWord, splitBlockSize, flashAddress, (uint8_t *)buffer+targetProgramInfo.dataOffset);
#else
         rc = WriteMemory(MS_Word, splitBlockSize, flashAddress, (uint8_t *)buffer+targetProgramInfo.dataOffset);
#endif
      }
      else {
         Logging::print("splitBlock[0x%06X..0x%06X]\n", flashAddress, flashAddress+splitBlockSize-1);
         Logging::print("flashOperationInfo.flashAddress = 0x%08X\n", flashOperationInfo.flashAddress);
         rc = executeTargetProgram(buffer, size);
      }
      if (rc != PROGRAMMING_RC_OK) {
         Logging::error("Error\n");
         return rc;
      }
      // Advance to next block of data
      flashAddress  += splitBlockSize;
      blockSize     -= splitBlockSize;
      oddBytes       = 0; // No odd bytes on subsequent blocks
      progressTimer->progress(splitBlockSize*sizeof(memoryElementType), NULL);
   }
   return PROGRAMMING_RC_OK;
}

//==============================================================================
//! Apply a flash operation to target based upon occupied flash addresses
//!
//! @param flashImage       Flash image to use
//! @param flashOperation   Operation to do on flash
//!
//! @return error code see \ref USBDM_ErrorCode
//!
USBDM_ErrorCode FlashProgrammer::applyFlashOperation(FlashImage     *flashImage,
                                                     FlashOperation  flashOperation) {
   Logging log("FlashProgrammer::applyFlashOperation");
   USBDM_ErrorCode rc = PROGRAMMING_RC_OK;
   FlashImage::Enumerator *enumerator = flashImage->getEnumerator();

   Logging::print("Op=%s, Total Bytes = %d\n",
         getFlashOperationName(flashOperation), flashImage->getByteCount());
   // Go through each allocated block of memory applying operation
   while (enumerator->isValid()) {
      // Start address of block to program to flash
      uint32_t startBlock = enumerator->getAddress();
      // Find end of block to process
      enumerator->lastValid();
      uint32_t blockSize = enumerator->getAddress() - startBlock + 1;
      if (blockSize>0) {
         // Process block [startBlock..endBlock]
         rc = doFlashBlock(flashImage, blockSize, startBlock, flashOperation);
         if (rc != PROGRAMMING_RC_OK) {
            Logging::error("FlashProgrammer::applyFlashOperation() - Error \n");
            break;
         }
      }
      else {
         Logging::print("FlashProgrammer::applyFlashOperation() - empty block\n");
      }
      enumerator->setAddress(startBlock);
   }
   delete enumerator;
   return rc;
}

//==============================================================================
//! Blank check, program and verify target from flash image
//!
//! @param flashImage Flash image to program
//!
//! @return error code see \ref USBDM_ErrorCode
//!
USBDM_ErrorCode FlashProgrammer::doProgram(FlashImage *flashImage) {
   Logging log("FlashProgrammer::doProgram");
   // Load target flash code to check programming options
   flashOperationInfo.alignment = 2;
   loadTargetProgram(OpBlankCheck);
   USBDM_ErrorCode rc;
   if ((targetProgramInfo.programOperation&DO_BLANK_CHECK_RANGE) == 0) {
      // Do separate blank check if not done by program operation
      rc = doBlankCheck(flashImage);
   }
   if ((targetProgramInfo.programOperation&DO_VERIFY_RANGE) == 0) {
      progressTimer->restart("Programming");
   }
   else {
      progressTimer->restart("Programming && Verifying...");
   }
   rc = applyFlashOperation(flashImage, OpProgram);
   if (rc != PROGRAMMING_RC_OK) {
      Logging::error("Programming failed, Reason= %s\n", USBDM_GetErrorString(rc));
   }
   if ((targetProgramInfo.programOperation&DO_VERIFY_RANGE) == 0) {
      // Do separate verify operation
      progressTimer->restart("Verifying...");
      rc = doVerify(flashImage);
   }
   return rc;
}

//==============================================================================
//! Selective erase target.  Area erased is determined from flash image
//!
//! @param flashImage - Flash image used to determine regions to erase
//!
//! @return error code see \ref USBDM_ErrorCode
//!
//! Todo This is sub-optimal as it may erase the same sector multiple times.
//!
USBDM_ErrorCode FlashProgrammer::doSelectiveErase(FlashImage *flashImage) {
   Logging log("FlashProgrammer::doSelectiveErase");
   progressTimer->restart("Selective Erasing...");

   USBDM_ErrorCode rc;
   rc = applyFlashOperation(flashImage, OpSelectiveErase);
   if (rc != PROGRAMMING_RC_OK) {
      Logging::error("Selective erase failed, Reason= %s\n", USBDM_GetErrorString(rc));
   }
   return rc;
}

//==================================================================================
//! doReadbackVerify - Verifies the Target memory against memory image
//!
//! @param flashImage Description of flash contents to be verified.
//!
//! @return error code see \ref USBDM_ErrorCode
//!
//! @note Assumes the target device has already been opened & USBDM options set.
//! @note Assumes target connection has been established
//! @note Assumes call-back has been set up if used.
//! @note If target clock trimming is enabled then the Non-volatile clock trim
//!       locations are ignored.
//!
USBDM_ErrorCode FlashProgrammer::doReadbackVerify(FlashImage *flashImage) {
   Logging log("FlashProgrammer::doReadbackVerify");
   const unsigned MAX_BUFFER=0x800;
   memoryElementType buffer[MAX_BUFFER];
   int checkResult = TRUE;
   int blockResult;

   FlashImage::Enumerator *enumerator = flashImage->getEnumerator();
   //ToDo - handle linear addressing on HCS12
   while (enumerator->isValid()) {
      uint32_t startBlock = enumerator->getAddress();
#if (TARGET==HCS08)||(TARGET==HC12)
      USBDM_ErrorCode rc = setPageRegisters(startBlock);
      if (rc != PROGRAMMING_RC_OK) {
         return rc;
      }
#endif
      // Find end of block to verify
      enumerator->lastValid();
      unsigned regionSize = enumerator->getAddress() - startBlock + 1;
      Logging::print("Verifying Block[0x%8.8X..0x%8.8X]\n", startBlock, startBlock+regionSize-1);
      while (regionSize>0) {
#if (TARGET==RS08)
         MemorySpace_t memorySpace = MS_Byte;
#elif (TARGET == MC56F80xx)
         MemorySpace_t memorySpace = MS_PWord;
#elif (TARGET == ARM)
         MemorySpace_t memorySpace = MS_Long;
#elif (TARGET == HCS08) || (TARGET == HCS12)
         MemorySpace_t memorySpace = (MemorySpace_t)(MS_Fast|MS_Byte);
#else
         MemorySpace_t memorySpace = MS_Word;
#endif
         unsigned blockSize    = regionSize;
         if (blockSize > MAX_BUFFER) {
            blockSize = MAX_BUFFER;
         }
         // Fix item size to match alignment
         if ((startBlock & ((memorySpace&MS_SIZE)-1)) != 0) {
            memorySpace = (MemorySpace_t)((memorySpace&MS_SIZE)|MS_Byte);
         }
         if (((startBlock+blockSize) & ((memorySpace&MS_SIZE)-1)) != 0) {
            memorySpace = (MemorySpace_t)((memorySpace&MS_SIZE)|MS_Byte);
         }
         if (ReadMemory(memorySpace, blockSize*sizeof(memoryElementType), startBlock, (uint8_t *)buffer) != BDM_RC_OK) {
            return PROGRAMMING_RC_ERROR_BDM_READ;
         }
         blockResult = TRUE;
         uint32_t testIndex;
         for (testIndex=0; testIndex<blockSize; testIndex++) {
            if (flashImage->getValue(startBlock+testIndex) != buffer[testIndex]) {
               blockResult = FALSE;
#ifndef LOG
               break;
#endif
//               Logging::print("Verifying location[0x%8.8X]=>failed, image=%2.2X != target=%2.2X\n",
//                     startBlock+testIndex,
//                     (uint8_t)(flashImage->getValue(startBlock+testIndex]),
//                     buffer[testIndex]);
            }
         }
         Logging::print("Verifying Sub-block[0x%8.8X..0x%8.8X]=>%s\n",
               startBlock, startBlock+blockSize-1,blockResult?"OK":"FAIL");
         checkResult = checkResult && blockResult;
         regionSize -= blockSize;
         startBlock += blockSize;
         progressTimer->progress(blockSize, NULL);
#ifndef LOG
         if (!checkResult) {
            break;
         }
#endif
      }
#ifndef LOG
      if (!checkResult) {
         break;
      }
#endif
      // Advance to start of next occupied region
      enumerator->nextValid();
   }
   if (enumerator != NULL) {
      delete enumerator;
   }
   return checkResult?PROGRAMMING_RC_OK:PROGRAMMING_RC_ERROR_FAILED_VERIFY;
}

//==============================================================================
//! Verify target against flash image
//!
//! @param flashImage Flash image to verify
//!
//! @return error code see \ref USBDM_ErrorCode
//!
USBDM_ErrorCode FlashProgrammer::doTargetVerify(FlashImage *flashImage) {
   Logging log("FlashProgrammer::doTargetVerify");
   USBDM_ErrorCode rc = applyFlashOperation(flashImage, OpVerify );
   if (rc != PROGRAMMING_RC_OK) {
      Logging::error("Target Verifying failed, Reason= %s\n", USBDM_GetErrorString(rc));
   }
   return rc;
}

//==============================================================================
//! Verify target against flash image
//!
//! @param flashImage Flash image to verify
//!
//! @return error code see \ref USBDM_ErrorCode
//!
USBDM_ErrorCode FlashProgrammer::doVerify(FlashImage *flashImage) {
   Logging log("FlashProgrammer::doVerify");
   USBDM_ErrorCode rc = PROGRAMMING_RC_ERROR_ILLEGAL_PARAMS;
   progressTimer->restart("Verifying...");

   // Try target verify then read-back verify
//   rc = doTargetVerify(flashImage);
   if (rc == PROGRAMMING_RC_ERROR_ILLEGAL_PARAMS) {
     rc = doReadbackVerify(flashImage);
   }
   if (rc != PROGRAMMING_RC_OK) {
      Logging::error("Verifying failed, Reason= %s\n", USBDM_GetErrorString(rc));
   }
   return rc;
}

//==============================================================================
//! Blank check target against flash image
//!
//! @param flashImage - Flash image to verify
//!
//! @return error code see \ref USBDM_ErrorCode
//!
USBDM_ErrorCode FlashProgrammer::doBlankCheck(FlashImage *flashImage) {
   LOGGING;
   progressTimer->restart("Blank Checking...");

   USBDM_ErrorCode rc = applyFlashOperation(flashImage, OpBlankCheck);
   if (rc != PROGRAMMING_RC_OK) {
      Logging::error("Blank check failed, Reason= %s\n", USBDM_GetErrorString(rc));
   }
   return rc;
}

//==============================================================================
//! Write RAM portion of image
//!
//! @param flashImage - Flash image to verify
//!
//! @return error code see \ref USBDM_ErrorCode
//!
USBDM_ErrorCode FlashProgrammer::doWriteRam(FlashImage *flashImage) {
   LOGGING;
   progressTimer->restart("Writing RAM...");

   USBDM_ErrorCode rc = applyFlashOperation(flashImage, OpWriteRam);
   if (rc != PROGRAMMING_RC_OK) {
      Logging::error("Failed, Reason= %s\n", USBDM_GetErrorString(rc));
   }
   return rc;
}

//=======================================================================
//! Verify Target Flash memory
//!
//! @param flashImage        - Description of flash contents to be verified.
//! @param progressCallBack  - Callback function to indicate progress
//!
//! @return error code see \ref USBDM_ErrorCode
//!
//! @note Assumes the target device has already been opened & USBDM options set.
//! @note If target clock trimming is enabled then the Non-volatile clock trim
//!       locations are ignored.
//!
USBDM_ErrorCode FlashProgrammer::verifyFlash(FlashImage  *flashImage, 
                                             CallBackT    progressCallBack) {

   Logging log("FlashProgrammer::verifyFlash");
   USBDM_ErrorCode rc;
   if ((this == NULL) || (parameters.getTargetName().empty())) {
      Logging::print("Error: device parameters not set\n");
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   Logging::print("===========================================================\n");
   Logging::print("\tprogressCallBack = %p\n",                 progressCallBack);
   Logging::print("\tDevice = \'%s\'\n",                       parameters.getTargetName().c_str());
   Logging::print("\tTrim, F=%ld, NVA@%4.4X, clock@%4.4X\n",   parameters.getClockTrimFreq(),
                                                               parameters.getClockTrimNVAddress(),
                                                               parameters.getClockAddress());
   Logging::print("\tRam[%4.4X...%4.4X]\n",                    parameters.getRamStart(), parameters.getRamEnd());
   Logging::print("\tErase=%s\n",                              DeviceData::getEraseOptionName(parameters.getEraseOption()));
   Logging::print("\tSecurity=%s\n",                           getSecurityName(parameters.getSecurity()));
   Logging::print("\tTotal bytes=%d\n",                        flashImage->getByteCount());
   Logging::print("===========================================================\n");

   this->doRamWrites = false;
   if (progressTimer != NULL) {
      delete progressTimer;
   }
   progressTimer = new ProgressTimer(progressCallBack, flashImage->getByteCount());
   progressTimer->restart("Initialising...");

   flashReady = FALSE;
   currentFlashProgram.reset();

   rc = initTCL();
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
   if (parameters.getTargetName().empty()) {
      Logging::error("Error: device parameters not set\n");
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   // Set up the target for Flash operations
   rc = resetAndConnectTarget();
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
   rc = checkTargetUnSecured();
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
   // Modify flash image according to security options - to be consistent with what is programmed
   rc = setFlashSecurity(*flashImage);
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
#if (TARGET == CFV1) || (TARGET == HCS08)
   // Modify flash image according to trim options - to be consistent with what is programmed
   rc = dummyTrimLocations(flashImage);
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
#endif
#if (TARGET == CFVx) || (TARGET == MC56F80xx)
   rc = determineTargetSpeed();
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
#endif
   // Set up for Flash operations (clock etc)
   rc = initialiseTargetFlash();
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
   rc = doVerify(flashImage);

   restoreSecurityAreas(*flashImage);

   Logging::print("Verifying Time = %3.2f s, rc = %d\n", progressTimer->elapsedTime(), rc);

   return rc;
}

//=======================================================================
//! Program Target Flash memory
//!
//! @param flashImage        - Description of flash contents to be programmed.
//! @param progressCallBack  - Callback function to indicate progress
//! @param doRamWrites       - Whether to do writes to RAM
//!
//! @return error code see \ref USBDM_ErrorCode
//!
//! @note Assumes the target device has already been opened & USBDM options set.
//! @note The FTRIM etc. locations in the flash image may be modified with trim values.
//! @note Security locations within the flash image may be modified to effect the protection options.
//!
USBDM_ErrorCode FlashProgrammer::programFlash(FlashImage  *flashImage, 
                                              CallBackT    progressCallBack, 
                                              bool         doRamWrites) {
   Logging log("FlashProgrammer::programFlash");
   Logging::setLoggingLevel(100);

   USBDM_ErrorCode rc;
   if ((this == NULL) || (parameters.getTargetName().empty())) {
      Logging::error("Error: device parameters not set\n");
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
//   if (parameters.getEraseOption() == DeviceData::eraseNone) {
//      parameters.setSecurity(SEC_DEFAULT);
//   }
#ifdef GDI
   mtwksDisplayLine("===========================================================\n"
         "Programming target\n"
         "\tDevice = \'%s\'\n"
         "\tTrim, F=%ld, NVA@%4.4X, clock@%4.4X\n"
         "\tRam[%4.4X...%4.4X]\n"
         "\tErase=%s\n"
         "\tSecurity=%s\n"
         "\tTotal bytes=%d\n"
         "\tdoRamWrites=%s\n",
         parameters.getTargetName().c_str(),
         parameters.getClockTrimFreq(),
         parameters.getClockTrimNVAddress(),
         parameters.getClockAddress(),
         parameters.getRamStart(),
         parameters.getRamEnd(),
         DeviceData::getEraseOptionName(parameters.getEraseOption()),
         getSecurityName(parameters.getSecurity()),
         flashImage->getByteCount(),
         doRamWrites?"T":"F");
#else
   Logging::print("===========================================================\n");
   Logging::print("\tprogressCallBack = %p\n",                 progressCallBack);
   Logging::print("\tDevice = \'%s\'\n",                       parameters.getTargetName().c_str());
   Logging::print("\tTrim, F=%ld, NVA@%4.4X, clock@%4.4X\n",   parameters.getClockTrimFreq(),
                                                               parameters.getClockTrimNVAddress(),
                                                               parameters.getClockAddress());
   Logging::print("\tRam[%4.4X...%4.4X]\n",                    parameters.getRamStart(), parameters.getRamEnd());
   Logging::print("\tErase=%s\n",                              DeviceData::getEraseOptionName(parameters.getEraseOption()));
   Logging::print("\tSecurity=%s\n",                           getSecurityName(parameters.getSecurity()));
   Logging::print("\tTotal bytes=%d\n",                        flashImage->getByteCount());
   Logging::print("\tdoRamWrites=%s\n",                        doRamWrites?"T":"F");
   Logging::print("===========================================================\n");
#endif

   this->doRamWrites = doRamWrites;
   if (progressTimer != NULL) {
      delete progressTimer;
   }
   progressTimer = new ProgressTimer(progressCallBack, flashImage->getByteCount());
   progressTimer->restart("Initialising...");

   flashReady = FALSE;
   currentFlashProgram.reset();

   rc = initTCL();
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
   if (parameters.getTargetName().empty()) {
      Logging::error("Error: device parameters not set\n");
      return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
   }
   // Connect to target
   rc = resetAndConnectTarget();

   // Ignore some errors if mass erasing target as it is possible to mass
   // erase some targets without a complete debug connection
   if ((rc != BDM_RC_OK) &&
       ((parameters.getEraseOption() != DeviceData::eraseMass) ||
        ((rc != PROGRAMMING_RC_ERROR_SECURED) &&
         (rc != BDM_RC_SECURED) &&
         (rc != BDM_RC_BDM_EN_FAILED) ))) {
      return rc;
   }
   bool secured = checkTargetUnSecured() != PROGRAMMING_RC_OK;

   // Check target security
   if (secured && (parameters.getEraseOption() != DeviceData::eraseMass)) {
      // Can't program if secured
      return PROGRAMMING_RC_ERROR_SECURED;
   }
#if (TARGET == HCS12)
   // Check for nasty chip of death
   rc = checkUnsupportedTarget();
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
#endif
#if (TARGET == RS08) || (TARGET == HCS08) || (TARGET == HCS12) 
   // Check target SDID (RS08/HCS08/HCS12 allows SDID to be read on secured device)
   rc = confirmSDID();
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
#endif
   // Mass erase if selected
   if (parameters.getEraseOption() == DeviceData::eraseMass) {
      rc = massEraseTarget();
      if (rc != PROGRAMMING_RC_OK) {
         return rc;
      }
   }
#if (TARGET == CFV1) || (TARGET == ARM) || (TARGET == CFVx) || (TARGET == MC56F80xx)
   // Check target SDID
   rc = confirmSDID();
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
#endif
   // Modify flash image according to security options
   rc = setFlashSecurity(*flashImage);
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
#if (TARGET == CFVx) || (TARGET == MC56F80xx)
   rc = determineTargetSpeed();
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
#endif
#if (TARGET == RS08) || (TARGET == CFV1) || (TARGET == HCS08)
   // Calculate clock trim values & update memory image
   rc = setFlashTrimValues(flashImage);
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
#endif   
   // Set up for Flash operations (clock etc)
   rc = initialiseTargetFlash();
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
   //
   // The above leaves the Flash ready for programming
   //
#if (TARGET==ARM) || (TARGET == CFV1)
   if (parameters.getEraseOption() == DeviceData::eraseMass) {
      // Erase the security area as Mass erase programs it
      rc = selectiveEraseFlashSecurity();
      if (rc != PROGRAMMING_RC_OK) {
         return rc;
      }
   }
   // Program EEPROM/DFLASH Split
   rc = partitionFlexNVM();
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
#endif
   if (parameters.getEraseOption() == DeviceData::eraseAll) {
      // Erase all flash arrays
      rc = eraseFlash();
   }
   else if (parameters.getEraseOption() == DeviceData::eraseSelective) {
      // Selective erase area to be programmed - this may have collateral damage!
      rc = doSelectiveErase(flashImage);
   }
   if (rc != PROGRAMMING_RC_OK) {
      Logging::error("Erasing failed, Reason= %s\n", USBDM_GetErrorString(rc));
      return rc;
   }
   double eraseTime = progressTimer->totalTime();
   if (eraseTime <= 0.0) {
      eraseTime = 0.05;
   }
#ifdef GDI
   mtwksDisplayLine("Erase Time = %3.2f s, Speed = %2.2f kBytes/s, rc = %d\n",
         eraseTime, flashImage->getByteCount()/(1024*eraseTime),  rc);
#endif
#ifdef LOG
   Logging::print("Erase Time = %3.2f s, Speed = %2.2f kBytes/s, rc = %d\n",
         eraseTime, flashImage->getByteCount()/(1+1024*eraseTime),  rc);
#endif
   // Program flash
   rc = doProgram(flashImage);
   if (rc != PROGRAMMING_RC_OK) {
      Logging::error("Programming failed, Reason= %s\n", USBDM_GetErrorString(rc));
      return rc;
   }
   if (doRamWrites){
      rc = doWriteRam(flashImage);
      if (rc != PROGRAMMING_RC_OK) {
         Logging::error("RAM write failed, Reason= %s\n", USBDM_GetErrorString(rc));
         return rc;
      }
   }
   restoreSecurityAreas(*flashImage);

   double programTime = progressTimer->totalTime() - eraseTime;
   if (programTime <= 0.0) {
      programTime = 0.05;
   }
#if (TARGET == RS08) || (TARGET == HCS08) || (TARGET == CFV1)
   if (parameters.getClockTrimFreq() != 0) {
      uint16_t trimValue = parameters.getClockTrimValue();
#ifdef GDI
      mtwksDisplayLine("FlashProgrammer::programFlash() - Device Trim Value = %2.2X.%1X\n", trimValue>>1, trimValue&0x01);
#endif
      Logging::print("Device Trim Value = %2.2X.%1X\n", trimValue>>1, trimValue&0x01);
   }
#endif

#ifdef GDI
   mtwksDisplayLine("Programming & verifying Time = %3.2f s, Speed = %2.2f kBytes/s, rc = %d\n",
         programTime, flashImage->getByteCount()/(1024*programTime),  rc);
#endif

   Logging::print("Programming & verifying Time = %3.2f s, Speed = %2.2f kBytes/s, rc = %d\n",
         programTime, flashImage->getByteCount()/(1+1024*programTime),  rc);

   return rc;
}

//=======================================================================
//! Set device data for flash operations
//!
//! @param theParameters   -   data describing the device
//!
//! @return error code see \ref USBDM_ErrorCode
//!
USBDM_ErrorCode FlashProgrammer::setDeviceData(const DeviceData &theParameters) {
   Logging log("FlashProgrammer::setDeviceData");
   currentFlashProgram.reset();
   parameters = theParameters;
   Logging::print("Target=%s\n", parameters.getTargetName().c_str());
   releaseTCL();
   initTCL();
   return PROGRAMMING_RC_OK;
}

//=======================================================================
FlashProgrammer::~FlashProgrammer() {
//      Logging::print("~FlashProgrammer()\n");
   if (progressTimer != NULL) {
      delete progressTimer;
   }
   releaseTCL();
}

