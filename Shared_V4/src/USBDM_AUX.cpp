/*! \file
   \brief USBDM utility functions

   USBDM_AUX.cpp

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
+============================================================================================
| 22 Dec 2012 | Added TargetConnectWithDelayedConfirmation() for 'watchdog' devices - pgo V4.9
| 22 Dec 2012 | Improvements to USBDM_TargetConnectWithRetry() for secured devices  - pgo V4.9
| 30 Jan 2012 | Added firmware version compatibility checks to findBDMs()           - pgo V4.9
| 16 Jul 2011 | Extended TargetConnect() strategies & Messages HCSxx                - pgo V4.7
|  1 Aug 2010 | Created for Linux version                                           - pgo
+============================================================================================
\endverbatim
*/
#ifdef useWxWidgets
// For compilers that support pre-compilation, includes <wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/string.h>
#include <wx/progdlg.h>
#include <wx/app.h>
#include <wx/evtloop.h>
#endif
#endif

#include <vector>
#include <string>
using namespace std;

#include "Common.h"
#include "Log.h"
#include "USBDM_API.h"
#include "USBDM_AUX.h"
#include "Names.h"
#include "Utils.h"
#include "wxPlugin.h"
#include "TargetDefines.h"

// Used to suppress retry dialogue if previous attempt failed
static bool extendedRetry = true;
static USBDM_ExtendedOptions_t bdmOptions;

//! Gets BDM Status with checks for fatal errors with no recovery option
//!
//! At this time the only fatal errors are:
//!   - USBDM_GetBDMStatus() failed i.e. the BDMs gone away - quietly fails
//!   - Target supply overload - flags error to user & fails
//!
//! @param USBDMStatus status value from BDM
//!
//! @return \n
//!     DI_OK              => OK \n
//!     DI_ERR_FATAL       => Error see \ref currentErrorString
//!
USBDM_ErrorCode getBDMStatus(USBDMStatus_t *USBDMStatus) {
   USBDM_ErrorCode rc;

//   Logging::print("getBDMStatus()\n");

   // USBDM_GetBDMStatus() should always succeed
   rc = USBDM_GetBDMStatus(USBDMStatus);
   if (rc != BDM_RC_OK) {
      Logging::print("getBDMStatus() - failed, reason = %s\n", USBDM_GetErrorString(rc));
      return rc;
   }

   // Check for Fatal power supply problems
   if (USBDMStatus->power_state == BDM_TARGET_VDD_ERR) {
      displayDialogue("Overload of the BDM Target Vdd supply has been detected.  \n"
                      "The target supply has been disabled.\n\n"
                      "Please restart the debugging session to restore power.",
                      "USBDM Interface - Target Power Failure",
                      wxICON_ERROR|wxOK);
      Logging::print("getBDMStatus() - failed, reason = Vdd overload\n");
      return BDM_RC_VDD_NOT_PRESENT;
   }
   return BDM_RC_OK;
}

//! Connect to target with a delayed check
//!
//! @note - The delayed check is to help detect watch-dog timeouts that can cause the
//!         BDM to get a connection but then loose it before anything useful can be done.
//!
//! @return \n
//!     DI_OK                  => OK \n
//!     BDM_RC_BDM_EN_FAILED   => Usually indicates an initial connection that is lost before re-check
//!     other                  => Some other more varied error
//!
USBDM_ErrorCode TargetConnectWithDelayedConfirmation(RetryMode retryMode) {
   LOGGING;
   USBDM_ErrorCode rc;

   //=========================================================
   //  Basic connect
   rc = USBDM_Connect();
   if (rc != BDM_RC_OK) {
      return rc;
   }
   uint8_t          mask;
#if TARGET == RS08
   mask = RS08_BDCSCR_ENBDM;
#elif TARGET == HCS08
   mask = HC08_BDCSCR_ENBDM;
#elif TARGET == HCS12
   mask = HC12_BDMSTS_ENBDM;
#elif TARGET == CFV1
   mask = CFV1_XCSR_ENBDM;
#else
   return rc;
#endif
   if (retryMode&retryDelayedCheck) {
      // Check if still connected after a while (WDOG check)
      milliSleep(20);
   }
   unsigned long BDMStatusReg;
   rc = USBDM_ReadStatusReg(&BDMStatusReg);
   if ((rc == BDM_RC_OK) && ((BDMStatusReg&mask) == 0)) {
      rc = BDM_RC_BDM_EN_FAILED;
   }
   if (rc != BDM_RC_OK) {
      Logging::error("Failed - rc = %s\n", USBDM_GetErrorString(rc));
   }
   return rc;
}

//! Releases reset etc using correct Special Mode sequence and then  retries connection
//!
//! @return \n
//!     DI_OK                  => OK \n
//!     BDM_RC_BDM_EN_FAILED   => Usually indicates an initial connection that is lost before re-check
//!     other                  => Some other more varied error
//!
static USBDM_ErrorCode retryConnection(USBDMStatus_t *usbdmStatus) {
   USBDMStatus_t status;

#if TARGET == ARM
   USBDM_ControlPins(PIN_RESET_LOW);                   // Leave RESET low during connect
#elif TARGET == CFVx
   USBDM_ControlPins(PIN_BKPT_LOW|PIN_RESET_3STATE);   // Release RESET (BKPT stays low)
   milliSleep(bdmOptions.resetReleaseInterval);        // Make sure BKPT/BKGD are seen after reset
   USBDM_ControlPins(PIN_RELEASE);                     // Release all pins
   milliSleep(bdmOptions.resetRecoveryInterval);       // Give target time to recover from reset
#else
   USBDM_ControlPins(PIN_BKGD_LOW|PIN_RESET_3STATE);   // Release RESET (BKGD stays low)
   milliSleep(bdmOptions.resetReleaseInterval);        // Make sure BKPT/BKGD are seen after reset
   USBDM_ControlPins(PIN_RELEASE);                     // Release all pins
   milliSleep(bdmOptions.resetRecoveryInterval);       // Give target time to recover from reset
#endif

   // Get status twice to clear spurious reset flag
   getBDMStatus(&status);
   USBDM_ErrorCode rc = getBDMStatus(&status);
   if (usbdmStatus != NULL) {
      *usbdmStatus = status;
   }
   if (rc != BDM_RC_OK) {
      // Fatal error
      Logging::print("USBDM_GetBDMStatus() failed!\n");
      return rc;
   }
   // Retry connection
   rc = TargetConnectWithDelayedConfirmation(retryDelayedCheck);  // Try connect again

   USBDM_ControlPins(PIN_RELEASE);                     // Release all pins
   milliSleep(bdmOptions.resetRecoveryInterval);       // Give target time to recover from reset
   return rc;
}

//! Connects to Target (RS08/HCS08/HCS12/CFV1/CFVx only)
//!
//! @note If there are connection problems, the user may be prompted to cycle
//!       the target power on some targets.
//!
//! @param usbdmStatus Current status of the BDM, may be NULL if not needed.
//! @param retryMode   How hard to retry \n
//!     The following are silent retries: \n
//!       retryNever      - give up after basic attempt, target state not affected \n
//!      +retryByReset    - quietly retry after hardware reset (if supported by target and allows debug entry). May be combined with others. \n
//!       retryNotPartial - give up quietly if device may be secured (BDM_RC_SECURED or BDM_RC_BDM_EN_FAILED) \n
//!     The following is interactive:\n
//!       retryAlways     - retry with dialogue prompt to user \n
//!
//! @return \n
//!     BDM_RC_OK => OK \n
//!     other     => Error code - see \ref USBDM_ErrorCode
//!
USBDM_ErrorCode USBDM_TargetConnectWithRetry(USBDMStatus_t *usbdmStatus, RetryMode retryMode) {
   LOGGING;
   Logging::print("%s\n", getConnectionRetryName(retryMode));

   USBDM_ErrorCode rc;
   
   USBDMStatus_t status;
   rc = getBDMStatus(&status);
   if (usbdmStatus != NULL) {
      *usbdmStatus = status;
   }
   if (rc != BDM_RC_OK) {
      Logging::print("getBDMStatus() failed\n");
      return rc; // Fatal error
   }
   //=========================================================
   //  Basic connect
   rc = TargetConnectWithDelayedConfirmation(retryMode);
   if (rc == BDM_RC_OK) {
      if (!extendedRetry)
         Logging::print("Enabling Extended Retry\n");
      extendedRetry = true;
      return rc;
   }
   // Quietly retry once
   rc = TargetConnectWithDelayedConfirmation(retryMode);
   if (rc == BDM_RC_OK) {
      if (!extendedRetry)
         Logging::print("Enabling Extended Retry\n");
      extendedRetry = true;
      return rc;
   }
   //===============================================
   // Connection has at least partially failed

   // Don't retry at all - silently fail
   if ((retryMode&retryMask) == retryNever) {
      Logging::error("Failed - No retries, rc = %s\n", USBDM_GetErrorString(rc));
      return rc;
   }

#if (TARGET == CFVx)
   // Target may be in low power mode
   // This will only work if an interrupt or similar
   // wakes the target while BKGD is low.
   // BKPT should wake the target but appears not to work if actually in
   // low power mode as opposed to just stopped
   USBDM_ControlPins(PIN_BKPT_LOW); // Assert BKPT
   milliSleep(100);
   USBDM_ControlPins(PIN_RELEASE); // Release BKPT
   rc = USBDM_Connect();
   if (rc == BDM_RC_OK) {
      return rc;
   }
#endif

#if (TARGET == RS08) || (TARGET == HCS08) || (TARGET == CFV1)
   if (retryMode & retryByReset) {
      // These targets may suffer from Watchdog problems - try multiple resets
      Logging::error("Failed - Trying multiple resets, (rc = %s)\n", USBDM_GetErrorString(rc));
      USBDM_TargetReset((TargetMode_t)(RESET_DEFAULT|RESET_SPECIAL));
      USBDM_TargetReset((TargetMode_t)(RESET_DEFAULT|RESET_SPECIAL));
      rc = TargetConnectWithDelayedConfirmation(retryMode);
      if (rc == BDM_RC_OK) {
         Logging::error("Success - After multiple resets\n");
         return rc;
      }
      USBDM_TargetReset((TargetMode_t)(RESET_DEFAULT|RESET_SPECIAL));
      USBDM_TargetReset((TargetMode_t)(RESET_DEFAULT|RESET_SPECIAL));
      rc = TargetConnectWithDelayedConfirmation(retryMode);
      if (rc == BDM_RC_OK) {
         Logging::error("Success - After multiple resets\n");
         return rc;
      }
   }
#endif

   // Don't retry for 'special cases' - silently fail
   if ((retryMode&retryMask) == retryNotPartial) {
      switch (rc) {
      case BDM_RC_BDM_EN_FAILED:
      case BDM_RC_SECURED:
         Logging::error("Failed - No retry for special cases, rc = %s\n", USBDM_GetErrorString(rc));
         return rc;
      default:
         break;
      }
   }
   // retryAlways or not a special case

   // Inform user of error and prompt for retry
   if (extendedRetry) {
      // Update target status
      getBDMStatus(&status);
      // Connection failure - retry
      int getYesNo;
      do {
         string message;
         long style = wxYES_NO|wxYES_DEFAULT|wxICON_QUESTION;
         Logging::error("Retry, reason = %s\n", USBDM_GetErrorString(rc));

#if TARGET == CFVx
         USBDM_ControlPins(PIN_BKPT_LOW|PIN_RESET_LOW); // Set BKPT & RESET low
#elif TARGET == ARM
         USBDM_ControlPins(PIN_RESET_LOW); // Set RESET low
#else
         USBDM_ControlPins(PIN_BKGD_LOW|PIN_RESET_LOW); // Set BKGD & RESET low
#endif
         if (retryMode&retryByPower) {
            // Try power cycle first
            USBDM_SetTargetVdd(BDM_TARGET_VDD_DISABLE);
            milliSleep(bdmOptions.powerOffDuration);
            USBDM_SetTargetVdd(BDM_TARGET_VDD_ENABLE);
            milliSleep(bdmOptions.powerOnRecoveryInterval);
            rc = retryConnection(usbdmStatus);
            if (rc == BDM_RC_OK) {
               break;
            }
         }
         // Check for 'interesting cases'
         if (status.power_state == BDM_TARGET_VDD_NONE) {
            message = "Target Vdd supply interrupted.\n\n"
                  "Please restore power to the target.\n\n"
                  "Retry connection?";
         }
         else if (status.reset_recent == RESET_DETECTED) {
            message = "Target RESET detected (watchdog?).\n\n"
                  "Please cycle power to the target.\n\n"
                  "Retry connection?";
         }
         else if (rc == BDM_RC_BDM_EN_FAILED) {
            message = "Enabling BDM interface on target failed.\n"
                  "The target may be secured.\n\n"
                  "Please cycle power to the target.\n\n"
                  "Retry connection?";
         }
#if (TARGET == CFVx)||(TARGET == HCS12)
         // Target supports guaranteed connection after Hardware reset
         else {
            message = "Connection with the target has failed.\n\n"
                  "Target reset done.\n\n"
                  "Retry connection?";
         }
#else
         // Target may require power cycle for guaranteed connection
         else if (bdmOptions.cycleVddOnConnect) {
               message = "Connection with the target has failed.\n\n"
                     "Target power has been cycled.\n\n"
                     "Retry connection?";
            }
         else {
         message = "Connection with the target has failed.\n\n"
               "Please cycle power to the target.\n\n"
               "Retry connection?";
         }
#endif
         getYesNo = displayDialogue(message.c_str(),
                                    "USBDM - Target Connection Failure",
                                    style
                                    );
         rc = retryConnection(usbdmStatus);
      } while ((rc != BDM_RC_OK) && (getYesNo == wxYES));
   }
   if (rc != BDM_RC_OK) {
      Logging::error("Failed, (disabling Extended Retry)\n");
   }
   // Only enable re-try if successful to prevent nagging
   extendedRetry = (rc == BDM_RC_OK);
   return rc;
}

//===================================================================
//! Displays a dialogue with suitable error message and prompts
//! to retry
//!
//! @param rc - error code for message look up
//!
//! @return Response from dialogue (wxNO, wxYES)
//!
int handleError(USBDM_ErrorCode rc) {
   int getYesNo;

   Logging::print("handleError(%d (%s))\n", rc, USBDM_GetErrorString(rc));

   switch (rc) {
   case BDM_RC_UNKNOWN_TARGET:
      getYesNo = displayDialogue("USBDM interface does not support target device.\n\n"
                                 "Change BDM and Retry?",
                                 "USBDM - BDM Not Suitable",
                                 wxYES_NO|wxYES_DEFAULT|wxICON_QUESTION
                                 );
      break;
   case BDM_RC_NO_USBDM_DEVICE:
      getYesNo = displayDialogue("No suitable USBDM interface was found.\n\n"
                                 "Retry?",
                                 "USBDM - BDM Not Found",
                                 wxYES_NO|wxYES_DEFAULT|wxICON_QUESTION
                                 );
      break;
   case BDM_RC_VDD_NOT_PRESENT:
      getYesNo = displayDialogue("The target appears to have no power.\n\n"
                                 "Please supply power to the target.\n\n"
                                 "Retry?",
                                 "USBDM - No Target Power",
                                 wxYES_NO|wxYES_DEFAULT|wxICON_QUESTION
                                 );
      break;
   case BDM_RC_BDM_EN_FAILED:
      getYesNo = displayDialogue("Enabling BDM interface on target failed.\n"
                                 "The target may be secured.\n\n"
                                 "Retry?",
                                 "USBDM - Target Connection Failure",
                                 wxYES_NO|wxYES_DEFAULT|wxICON_QUESTION
                                 );
      break;
   default: {
      std::string s;
      s += "An error occurred while accessing the BDM.\n\n"
           "Reason: ";
      s += USBDM_GetErrorString(rc);
      s += "\n\n"
           "Please cycle power to the target\n\n"
           "Retry?";
      getYesNo = displayDialogue(s.c_str(),
                                 "USBDM - Error",
                                 wxYES_NO|wxYES_DEFAULT|wxICON_QUESTION
                                 );
      break;
      }
   }
   return getYesNo;
}

//===================================================================
//! Sets target MCU type with retry
//!
//! @param targetType type of target
//!
//! @return \n
//!     BDM_RC_OK  => OK \n
//!     other      => Error code - see \ref USBDM_ErrorCode
//!
//! @note  The user may be prompted to supply target power.
//! @note  The user is alerted to any problems.
//!
USBDM_ErrorCode USBDM_SetTargetTypeWithRetry(TargetType_t targetType) {
   LOGGING;
   USBDM_ErrorCode rc;
   int getYesNo = wxNO;
   int firstTryFlag = true;

   Logging::print("USBDM_SetTargetTypeWithRetry(%s)\n", getTargetTypeName(targetType));
   do {
      rc  = USBDM_SetTargetType(targetType);
      if (firstTryFlag && (rc == BDM_RC_VDD_NOT_PRESENT)) {
         // Target power can sometimes take a long while to rise
         // Give it another second to reduce 'noise'
         milliSleep(1000);
         rc = USBDM_SetTargetType(targetType);
         firstTryFlag = false;
      }
      if (rc == BDM_RC_OK) {
         // Check for target power
         USBDMStatus_t status;
         rc = USBDM_GetBDMStatus(&status);
         if ((rc = BDM_RC_OK) && (status.power_state == BDM_TARGET_VDD_NONE)) {
            rc = BDM_RC_VDD_NOT_PRESENT;
         }
      }
      if (rc != BDM_RC_OK) {
         getYesNo = handleError(rc);
      }
   } while ((rc != BDM_RC_OK) && (getYesNo == wxYES));

#if (TARGET != ARM)
   // Get status to clear reset flag on possible power-up
   USBDMStatus_t status;
   USBDM_GetBDMStatus(&status);
#endif

   // Only enable re-try if successful to stop nagging
   extendedRetry = (rc == BDM_RC_OK);

   return rc;
}

/*!
 * Converts a UTF-16-LE to a UTF-8 C string
 *
 * @param source - the UTF16LE string to convert
 *
 * @return source converted to a C string
 *
 * @note - Uses a static buffer so value should be used immediately
 */
static const char *utf16leToUtf8(const char *source) {
   const  uint8_t  *inPtr  = (const uint8_t*) source;
   static uint8_t  buffer[100];
          uint8_t  *outPtr = buffer;
          uint16_t utf16leValue;

    while ((*inPtr != 0) && (outPtr < (buffer+100))) {
       utf16leValue  = *inPtr++;
       utf16leValue += *inPtr++<<8;
       if (utf16leValue < 0x80) {  // 1-byte
          *outPtr++ = (uint8_t)utf16leValue;
       }
       else if (utf16leValue <0x0800) {   // 2-byte
          *outPtr++ = (uint8_t)(0xC0 + (utf16leValue>>6));
          *outPtr++ = (uint8_t)(0x80 + (utf16leValue&0x3F));
       }
       else {   // 3-byte
          *outPtr++ = (uint8_t)(0xE0 + (utf16leValue>>12));
          *outPtr++ = (uint8_t)(0x80 + ((utf16leValue>>6)&0x3F));
          *outPtr++ = (uint8_t)(0x80 + (utf16leValue&0x3F));
       }
    }
    // Make sure '\0' terminated
    if (outPtr < (buffer+sizeof(buffer)/sizeof(buffer[0])))
       *outPtr = 0;
    buffer[sizeof(buffer)-1] = 0;
    return (const char *)buffer;
}

USBDM_ErrorCode USBDM_GetBDMSerialNumber(string &serialNumber) {
   const char *serialNumberPtr;
   USBDM_ErrorCode rc;

   rc = USBDM_GetBDMSerialNumber(&serialNumberPtr);
   if (rc != BDM_RC_OK)
      return rc;
   serialNumber = string(utf16leToUtf8(serialNumberPtr));
   return BDM_RC_OK;
}

USBDM_ErrorCode USBDM_GetBDMDescription(string &description) {
   const char *descriptionPtr;
   USBDM_ErrorCode rc;

   rc = USBDM_GetBDMDescription(&descriptionPtr);
   if (rc != BDM_RC_OK)
      return rc;
   description = string(utf16leToUtf8(descriptionPtr));
   return BDM_RC_OK;
}

//! Update the list of connected BDMs
//!
USBDM_ErrorCode USBDM_FindBDMs(TargetType_t targetType, vector<BdmInformation> &bdmInformation) {
   LOGGING;

	USBDM_Close();          // Close any open devices

	unsigned deviceCount;
	USBDM_FindDevices(&deviceCount);

	bdmInformation.clear();

	if (deviceCount==0) {
		Logging::print("No devices\n");
		return BDM_RC_NO_USBDM_DEVICE;
	}
   int targetCapabilityMask = 0x0000;
   switch(targetType) {
      case T_HC12      : targetCapabilityMask =  BDM_CAP_HCS12;     break;
      case T_HCS08     : targetCapabilityMask =  BDM_CAP_HCS08;     break;
      case T_RS08      : targetCapabilityMask =  BDM_CAP_RS08;      break;
      case T_MC56F80xx : targetCapabilityMask =  BDM_CAP_DSC ;      break;
      case T_CFV1      : targetCapabilityMask =  BDM_CAP_CFV1;      break;
      case T_CFVx      : targetCapabilityMask =  BDM_CAP_CFVx;      break;
      case T_JTAG      : targetCapabilityMask =  BDM_CAP_JTAG;      break;
      case T_ARM_JTAG  : targetCapabilityMask =  BDM_CAP_ARM_JTAG;  break;
      case T_ARM_SWD   : targetCapabilityMask =  BDM_CAP_ARM_SWD;   break;
      case T_ARM       : targetCapabilityMask =  BDM_CAP_ARM_JTAG|
                                                 BDM_CAP_ARM_SWD;   break;
      default :
         break;
   }
   USBDM_ErrorCode rc = BDM_RC_NO_USBDM_DEVICE; // Assume no devices

   for (unsigned index=0; index<deviceCount; index++) {
      BdmInformation bdmInfo(index, "Device not responding or busy", "Unknown");
      do {
         USBDM_ErrorCode bdmRc = USBDM_Open(index);
         if (bdmRc != BDM_RC_OK) {
            Logging::print("USBDM_Open(BDM #%d) failed\n", index);
            bdmInfo.suitable = bdmRc;
            break;
         }
         USBDM_bdmInformation_t theBdmInfo = {sizeof(theBdmInfo)};
         bdmRc = USBDM_GetBdmInformation(&theBdmInfo);
         if (bdmRc != BDM_RC_OK) {
            Logging::print("USBDM_GetBdmInformation(BDM #%d) failed \n", index);
            bdmInfo.suitable = bdmRc;
            break;
         }
         bdmInfo.info = theBdmInfo;
         bdmRc = USBDM_GetBDMDescription(bdmInfo.description);
         if (bdmRc != BDM_RC_OK) {
            Logging::print("USBDM_GetBDMDescription(BDM #%d) failed \n", index);
            bdmInfo.suitable = bdmRc;
            break;
         }
         // Check capabilities against target needs
         if ((theBdmInfo.capabilities & targetCapabilityMask) == 0) {
            Logging::print("BDM #%d is not suitable for target\n", index);
            bdmInfo.serialNumber = "BDM Doesn't support target";
            bdmInfo.suitable = BDM_RC_UNKNOWN_TARGET;
            break;
         }
         Logging::print("USBDM_GetCapabilities(BDM #%d) =>  0x%4.4X \n", index, theBdmInfo.capabilities);
         Logging::print("USBDM_GetCapabilities() => seeking 0x%4.4X \n", targetCapabilityMask);
         Logging::print("USBDM_GetCapabilities() => targetType = %d \n", targetType);

         // Already have capabilities but this is used to check BDM firmware compatibility
         HardwareCapabilities_t bdmCapabilities;
         bdmRc = USBDM_GetCapabilities(&bdmCapabilities);
         if (bdmRc != BDM_RC_OK) {
            Logging::print("USBDM_GetCapabilities(BDM #%d) failed \n", index);
            if (bdmRc == BDM_RC_WRONG_BDM_REVISION) {
               bdmInfo.serialNumber = "Wrong Firmware Version";
            }
            bdmInfo.suitable = bdmRc;
            break;
         }
         bdmInfo.suitable = BDM_RC_OK;
         // At least one suitable device
         rc = BDM_RC_OK;
         if (USBDM_GetBDMSerialNumber(bdmInfo.serialNumber) != BDM_RC_OK) {
            Logging::print("USBDM_GetBDMSerialNumber(BDM #%d) failed \n", index);
            break;
         }
      } while (false);
      USBDM_Close();
      bdmInformation.push_back(bdmInfo);
   }
	Logging::print("%d devices located\n", deviceCount);

	return rc;
}

/*
 * Open a BDM with preference given to a particular device (indicated by serial number)
 *
 * @param targetType    BDM are filtered by support for this target
 * @param serialnumber  Serial number of BDM to open preferentially
 *
 * @note - Will open the first suitable BDM if the specified one is not located.
 *
 */
USBDM_ErrorCode USBDM_OpenBySerialNumber(TargetType_t targetType, const string &serialnumber) {
   LOGGING;
	Logging::print("(%s, %s)\n", getTargetTypeName(targetType), serialnumber.c_str());

	// Enumerate all attached BDMs
	vector<BdmInformation> bdmInformation;
	USBDM_FindBDMs(targetType, bdmInformation);

	// Search for preferred BDM
	vector<BdmInformation>::iterator it 				     = bdmInformation.begin();
	vector<BdmInformation>::iterator firstSuitableDevice = bdmInformation.end();

   USBDM_ErrorCode rc = BDM_RC_NO_USBDM_DEVICE;
	while (it != bdmInformation.end()) {
		if (it->suitable == BDM_RC_OK) {
			if (it->serialNumber.compare(serialnumber) == 0) {
				Logging::print("Opening preferred device #%d\n", it->deviceNumber);
				return USBDM_Open(it->deviceNumber);
			}
			if (firstSuitableDevice == bdmInformation.end())
				firstSuitableDevice = it;
			}
  	   it++;
   }
	if (firstSuitableDevice != bdmInformation.end()) {
		Logging::print("Opening first suitable BDM #%s\n",
		      firstSuitableDevice->serialNumber.c_str());
		rc = USBDM_Open(firstSuitableDevice->deviceNumber);
	}
	else if (bdmInformation.begin() != bdmInformation.end()) {
	   // Return error code from first/only device found
      Logging::print("No suitable BDM found, first/only found = %s\n",
            bdmInformation.begin()->serialNumber.c_str());
	   rc = bdmInformation.begin()->suitable;
	}
	else {
	   Logging::print("No BDMs found\n");
	   rc = BDM_RC_NO_USBDM_DEVICE;
	}
   Logging::print("rc = %s\n", USBDM_GetErrorString(rc));
	return rc;
}

USBDM_ErrorCode USBDM_OpenBySerialNumberWithRetry(TargetType_t targetType, const string &serialnumber) {
   LOGGING;
   USBDM_ErrorCode rc;
   int getYesNo = wxNO;
   do {
      rc = USBDM_OpenBySerialNumber(targetType, serialnumber);
      if (rc != BDM_RC_OK) {
         getYesNo = handleError(rc);
      }
   } while ((rc != BDM_RC_OK) && (getYesNo == wxYES));
   return rc;
}

USBDM_ErrorCode  USBDM_SetOptionsWithRetry(USBDM_ExtendedOptions_t *bdmOptions) {
   LOGGING;
   USBDM_ErrorCode rc;

   ::bdmOptions = *bdmOptions;
   // Power cycle is done by GDI not BDM
   bdmOptions->cycleVddOnConnect = FALSE;
   int getYesNo = wxNO;
   do {
      rc = USBDM_SetExtendedOptions(bdmOptions);
      if (rc != BDM_RC_OK) {
         getYesNo = handleError(rc);
      }
   } while ((rc != BDM_RC_OK) && (getYesNo == wxYES));
   return rc;
}
