/*! \file
   \brief Clock Trimming Code for RS08/HCS08/CFV1

   ClockTrimming.h

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
+===============================================================================
| Revision History
+===============================================================================
| 04 Nov 12 | 4.10.4 Added writeClockRegister()                            - pgo
+-----------+-------------------------------------------------------------------
| 13 Jun 12 | 4.9.5  Created                                               - pgo
+===============================================================================
\endverbatim
*/

#include <math.h>
#include "Common.h"
#include "ProgressTimer.h"
#include "FlashProgramming.h"
#include "USBDM_API.h"
#include "TargetDefines.h"

//! Clock register write with retry
//!
//! @param addr : clock register address
//! @param data : byte to write
//!
//! @return BDM_RC_OK => success
//!
//! @note writes are retried after a re-connect to cope
//!  with a possible clock speed change.
//!
USBDM_ErrorCode writeClockRegister(uint32_t addr, uint8_t data) {
   LOGGING_Q;
   USBDM_ErrorCode rc;

   rc = USBDM_WriteMemory(1,1,addr,&data);
   if (rc != BDM_RC_OK) {
      Logging::print("Failed write 0x%04X <= 0x%02X) - retrying\n", addr, data);
      rc = USBDM_Connect();
      if (rc == BDM_RC_OK) {
         rc = USBDM_WriteMemory(1,1,addr,&data);
         if (rc != BDM_RC_OK) {
         }
      }
   }
   if (rc != BDM_RC_OK) {
      Logging::print("Failed write 0x%04X <= 0x%02X), rc = %s\n", addr, data, USBDM_GetErrorString(rc));
   }
   return rc;
}


//! Configures the MCGCG target clock
//!
//! @param busFrequency    - Resulting BDM frequency after clock adjustment
//! @param clockParameters - Describes clock settings to use
//!
//! @return error code, see \ref USBDM_ErrorCode
//!
//! @note Assumes that connection with the target has been established so
//!       reports any errors as PROGRAMMING_RC_ERROR_FAILED_CLOCK indicating
//!       a problem programming the target clock.
//!
USBDM_ErrorCode FlashProgrammer::configureMCG_Clock(unsigned long         *busFrequency,
                                                 MK_MCG_ClockParameters_t *clockParameters){
   LOGGING_E;

   const uint32_t MCGC1    = parameters.getClockAddress();
   const uint32_t MCGC2    = parameters.getClockAddress()+1;
   const uint32_t MCGTRIM  = parameters.getClockAddress()+2;
   const uint32_t MCGSC    = parameters.getClockAddress()+3;
   const uint32_t MCGC3    = parameters.getClockAddress()+4;
   const uint32_t MCGT     = parameters.getClockAddress()+5;

   unsigned long bdmFrequency;

   Logging::print("MCG Clock: Ad=0x%08X, C1=0x%02X, C2=0x%02X, C3=0x%02X, SC=0x%02X, CT/C4=0x%02X\n",
           parameters.getClockAddress(),
           clockParameters->mcgC1,
           clockParameters->mcgC2,
           clockParameters->mcgC3,
           clockParameters->mcgSC,
           clockParameters->mcgCT
           );

   flashReady = FALSE; // Not configured for Flash access

   // ToDo - Review order of writes & need for re-connect()
   if (writeClockRegister(MCGTRIM, clockParameters->mcgTrim) != BDM_RC_OK) {
      return PROGRAMMING_RC_ERROR_FAILED_CLOCK;
   }
   if (USBDM_Connect() != BDM_RC_OK) { // re-connect after possible bus speed change
      return PROGRAMMING_RC_ERROR_FAILED_CLOCK;
   }
   if (writeClockRegister(MCGC1, clockParameters->mcgC1) != BDM_RC_OK) {
      return PROGRAMMING_RC_ERROR_FAILED_CLOCK;
   }
   if (writeClockRegister(MCGSC, clockParameters->mcgSC) != BDM_RC_OK) {
      return PROGRAMMING_RC_ERROR_FAILED_CLOCK;
   }
   if (writeClockRegister(MCGC2, clockParameters->mcgC2) != BDM_RC_OK) {
      return PROGRAMMING_RC_ERROR_FAILED_CLOCK;
   }
   if (USBDM_Connect() != BDM_RC_OK) { // re-connect after possible bus speed change
      return PROGRAMMING_RC_ERROR_FAILED_CLOCK;
   }
   if (writeClockRegister(MCGC3, clockParameters->mcgC3) != BDM_RC_OK) {
      return PROGRAMMING_RC_ERROR_FAILED_CLOCK;
   }
   if ((parameters.getClockType() != S08MCGV1) &&
       (writeClockRegister(MCGT, clockParameters->mcgCT) != BDM_RC_OK)) {
         return PROGRAMMING_RC_ERROR_FAILED_CLOCK;
   }
   milliSleep(100);
   if (USBDM_Connect() != BDM_RC_OK) {
      return PROGRAMMING_RC_ERROR_FAILED_CLOCK;
   }
   if (USBDM_GetSpeed(&bdmFrequency) != BDM_RC_OK) {
      return PROGRAMMING_RC_ERROR_FAILED_CLOCK;
   }
   bdmFrequency *= 1000; // Convert to Hz
   *busFrequency = bdmFrequency*parameters.getBDMtoBUSFactor();
   Logging::print("BDM Speed = %ld kHz, Bus Speed = %ld kHz\n",
         bdmFrequency/1000, *busFrequency/1000);
   return PROGRAMMING_RC_OK;
}

//! Configures the External target clock
//!
//! @param busFrequency    - Resulting BDM frequency after clock adjustment (Hz)
//!
//! @return error code, see \ref USBDM_ErrorCode
//!
USBDM_ErrorCode FlashProgrammer::configureExternal_Clock(unsigned long  *busFrequency){
   LOGGING_E;
   unsigned long bdmFrequency;

   flashReady = FALSE; // Not configured for Flash access

   // Just connect at whatever speed
   if (USBDM_Connect() != BDM_RC_OK) {
      return PROGRAMMING_RC_ERROR_BDM_CONNECT;
   }
   if (USBDM_GetSpeed(&bdmFrequency) != BDM_RC_OK) {
      return PROGRAMMING_RC_ERROR_BDM_CONNECT;
   }
   bdmFrequency *= 1000; // Convert to Hz
   *busFrequency = bdmFrequency*parameters.getBDMtoBUSFactor();
   Logging::print("BDM Speed = %ld kHz, Bus Speed = %ld kHz\n",
         bdmFrequency/1000, *busFrequency/1000);
   return PROGRAMMING_RC_OK;
}

//! \brief Configures the target clock appropriately for flash programming
//!        The speed would be the maximum safe value for an untrimmed target
//!
//! @param busFrequency    - Resulting BDM frequency after clock adjustment \n
//!                          For a HCS08/CFV1 with CLKSW=1 this will be the bus frequency
//!
//! @return error code, see \ref USBDM_ErrorCode
//!
USBDM_ErrorCode FlashProgrammer::configureTargetClock(unsigned long  *busFrequency) {
   LOGGING_E;

   //! MCG parameters for flash programming 4/8 MHz
   static const MK_MCG_ClockParameters_t MCG_FlashSpeedParameters = {
         // bdm clock = reference clock * 1024/2
         /* .mcgC1   = */ 0x04, // IREFS
         /* .mcgC2   = */ 0x40, // BDIV=/2
         /* .mcgC3   = */ 0x01, // VDIV=x4 (not used)
         /* .mcgTrim = */ 0x80, // TRIM=nominal
         /* .mcgSC   = */ 0x00, // FTRIM=0
         /* .mcgCT   = */ 0x00, // DMX32=0, DRS=0
   };

   MK_MCG_ClockParameters_t   MCG_SpeedParameters   = MCG_FlashSpeedParameters;

//   Logging::print("Configuring Target clock\n");

   switch (parameters.getClockType()) {
      case CLKEXT:
      case CLKINVALID:
      default:
         return configureExternal_Clock(busFrequency);
      case MKMCGV1:
         // Program clock for approx. 8 MHz
         MCG_SpeedParameters.mcgCT = 0x01; // DRS = 1
         return configureMCG_Clock(busFrequency, &MCG_SpeedParameters);
         break;
   }
   return PROGRAMMING_RC_ERROR_ILLEGAL_PARAMS;
}

//!  Determines the trim value for the target internal clock.
//!  The target clock is left trimmed for a bus freq. of targetBusFrequency.
//!
//!     Target clock has been suitably configured.
//!
//!  @param      trimAddress           Address of trim register.
//!  @param      targetBusFrequency    Target Bus Frequency to trim to.
//!  @param      returnTrimValue       Resulting trim value (9-bit number)
//!  @param      measuredBusFrequency  Resulting Bus Frequency
//!  @param      do9BitTrim            True to do 9-bit trim (rather than 8-bit)
//!
//!  @return
//!   == \ref PROGRAMMING_RC_OK  => Success \n
//!   != \ref PROGRAMMING_RC_OK  => Various errors
//!
USBDM_ErrorCode FlashProgrammer::trimTargetClock(uint32_t       trimAddress,
                                                 unsigned long  targetBusFrequency,
                                                 uint16_t      *returnTrimValue,
                                                 unsigned long *measuredBusFrequency,
                                                 int            do9BitTrim){
   LOGGING;
   uint8_t          mask;
   uint8_t          trimMSB, trimLSB, trimCheck;
   int              trimValue;
   int              maxRange;
   int              minRange;
   unsigned         long bdmSpeed;
   int              index;
   USBDM_ErrorCode  rc = PROGRAMMING_RC_OK;

#if (TARGET == RS08) || (TARGET == HCS08) || (TARGET == HCS12) || (TARGET == CFV1)

#if TARGET == RS08
   mask = RS08_BDCSCR_CLKSW;
#elif TARGET == HCS08
   mask = HC08_BDCSCR_CLKSW;
#elif TARGET == HCS12
   mask = HC12_BDMSTS_CLKSW;
#elif TARGET == CFV1
   mask = CFV1_XCSR_CLKSW;
#endif

   unsigned long BDMStatusReg;
   rc = USBDM_ReadStatusReg(&BDMStatusReg);
   if ((BDMStatusReg&mask) == 0) {
      Logging::print("Setting CLKSW\n");
      BDMStatusReg |= mask;
#if TARGET == CFV1
      // Make sure we don't accidently do a mass erase
      mask &= ~CFV1_XCSR_ERASE;
#endif
      rc = USBDM_WriteControlReg(BDMStatusReg);
      rc = USBDM_Connect();
   }
#endif

   static const int maxTrim        = 505;   // Maximum acceptable trim value
   static const int minTrim        =   5;   // Minimum acceptable trim value
   static const int SearchOffset   =   8;   // Linear sweep range is +/- this value
   static const unsigned char zero =   0;
   const unsigned long targetBDMFrequency = targetBusFrequency/parameters.getBDMtoBUSFactor();
   int numAverage;     // Number of times to repeat measurements

   double sumX          = 0.0;
   double sumY          = 0.0;
   double sumXX         = 0.0;
   double sumYY         = 0.0;
   double sumXY         = 0.0;
   double num           = 0.0;
   double alpha, beta;
   double trimValueF;

   Logging::print("targetBusFrequency=%ld, targetBDMFrequency=%ld)\n", targetBusFrequency, targetBDMFrequency);

   flashReady = FALSE; // Not configured for Flash access

   // Set safe defaults
   *returnTrimValue      = 256;
   *measuredBusFrequency = 10000;
   trimMSB               = 0;

   // Set LSB trim value = 0
   if (writeClockRegister(trimAddress+1, zero) != BDM_RC_OK) {
      return PROGRAMMING_RC_ERROR_BDM_WRITE;
   }
   // Initial binary search (MSB only)
   for (mask = 0x80; mask > 0x0; mask>>=1) {
      trimMSB |= mask;
      // Set trim value (MSB only)
      if (writeClockRegister(trimAddress, trimMSB) != BDM_RC_OK) {
         return PROGRAMMING_RC_ERROR_BDM_WRITE;
      }
      // Check target speed
      if (USBDM_Connect() != BDM_RC_OK) {
         return PROGRAMMING_RC_ERROR_BDM_CONNECT;
      }
      if (USBDM_GetSpeed(&bdmSpeed) != BDM_RC_OK) {
         return PROGRAMMING_RC_ERROR_BDM_WRITE;
      }
      bdmSpeed *= 1000; // convert to Hz

    Logging::print("Binary search: trimMSB=0x%02X (%d), bdmSpeed=%ld%c\n",
            trimMSB, trimMSB, bdmSpeed, (bdmSpeed<targetBDMFrequency)?'-':'+');

      // Adjust trim value
      if (bdmSpeed<targetBDMFrequency) {
         trimMSB &= ~mask; // too slow
      }
      if (trimMSB > maxTrim/2) {
         trimMSB = maxTrim/2;
      }
      if (trimMSB < minTrim/2) {
         trimMSB = minTrim/2;
      }
   }

   // Binary search value is middle of range to sweep

   trimValue = trimMSB<<1;  // Convert to 9-bit value

   // Linear sweep +/-SEARCH_OFFSET, starting at higher freq (smaller Trim)
   // Range is constrained to [minTrim..maxTrim]

   maxRange = trimValue + SearchOffset;
   if (maxRange > maxTrim) {
      maxRange = maxTrim;
   }
   minRange = trimValue - SearchOffset;
   if (minRange < minTrim) {
      minRange = minTrim;
   }
//   Logging::print("trimTargetClock(): Linear sweep, f=%6ld    \n"
//                   "trimTargetClock():    Trim       frequency \n"
//                   "========================================== \n",
//                   targetBDMFrequency/1000);

   if (do9BitTrim) {
      numAverage = 2;
   }
   else {
      numAverage = 4;
   }
   for(trimValue=maxRange; trimValue>=minRange; trimValue--) {
      trimLSB = trimValue&0x01;
      trimMSB = (uint8_t)(trimValue>>1);
      if (do9BitTrim) {
         // Write trim LSB
         if (writeClockRegister(trimAddress+1, trimLSB) != BDM_RC_OK)
            return PROGRAMMING_RC_ERROR_BDM_WRITE;
         if (USBDM_ReadMemory(1, 1, trimAddress+1,   &trimCheck) != BDM_RC_OK)
            return PROGRAMMING_RC_ERROR_BDM_WRITE;
         if ((trimCheck&0x01) != trimLSB)
            return PROGRAMMING_RC_ERROR_BDM_WRITE;
      }
      else if (trimValue&0x01) {
         // skip odd trim values if 8-bit trim
         continue;
      }
      // Write trim MSB
      if (writeClockRegister(trimAddress,  trimMSB) != BDM_RC_OK) {
         return PROGRAMMING_RC_ERROR_BDM_WRITE;
      }
      if (USBDM_ReadMemory(1, 1, trimAddress,   &trimCheck) != BDM_RC_OK) {
         return PROGRAMMING_RC_ERROR_BDM_WRITE;
      }
      if (trimCheck != trimMSB) {
         return PROGRAMMING_RC_ERROR_BDM_WRITE;
      }
      //milliSleep(100);
      // Measure sync multiple times
      for(index=numAverage; index>0; index--) {
         // Check target speed
         if (USBDM_Connect() != BDM_RC_OK)
            return PROGRAMMING_RC_ERROR_BDM_CONNECT;
         if (USBDM_GetSpeedHz(&bdmSpeed) != BDM_RC_OK)
            return PROGRAMMING_RC_ERROR_BDM_CONNECT;
         sumX  += trimValue;
         sumY  += bdmSpeed;
         sumXX += trimValue*trimValue;
         sumYY += bdmSpeed*bdmSpeed;
         sumXY += bdmSpeed*trimValue;
         num   += 1.0;
//         Logging::print("trimTargetClock(): %6d    %10ld %10ld\n", trimValue, bdmSpeed, targetBDMFrequency-bdmSpeed);
      }
   }
   for(trimValue=minRange; trimValue<=maxRange; trimValue++) {
      trimLSB = trimValue&0x01;
      trimMSB = (uint8_t)(trimValue>>1);
      if (do9BitTrim) {
         // Write trim LSB
         if (writeClockRegister(trimAddress+1, trimLSB) != BDM_RC_OK) {
            return PROGRAMMING_RC_ERROR_BDM_WRITE;
         }
         if (USBDM_ReadMemory(1, 1, trimAddress+1,   &trimCheck) != BDM_RC_OK) {
            return PROGRAMMING_RC_ERROR_BDM_WRITE;
         }
         if ((trimCheck&0x01) != trimLSB) {
            return PROGRAMMING_RC_ERROR_BDM_WRITE;
         }
      }
      else if (trimValue&0x01) {
         // skip odd trim values if 8-bit trim
         continue;
      }
      // Write trim MSB
      if (writeClockRegister(trimAddress, trimMSB) != BDM_RC_OK) {
         return PROGRAMMING_RC_ERROR_BDM_WRITE;
      }
      if (USBDM_ReadMemory(1, 1, trimAddress,   &trimCheck) != BDM_RC_OK) {
         return PROGRAMMING_RC_ERROR_BDM_WRITE;
      }
      if (trimCheck != trimMSB) {
         return PROGRAMMING_RC_ERROR_BDM_WRITE;
      }
      //milliSleep(100);
      // Measure sync multiple times
      for(index=numAverage; index>0; index--) {
         // Check target speed
         if (USBDM_Connect() != BDM_RC_OK) {
            return PROGRAMMING_RC_ERROR_BDM_CONNECT;
         }
         if (USBDM_GetSpeedHz(&bdmSpeed) != BDM_RC_OK) {
            return PROGRAMMING_RC_ERROR_BDM_CONNECT;
         }
         sumX  += trimValue;
         sumY  += bdmSpeed;
         sumXX += trimValue*trimValue;
         sumYY += bdmSpeed*bdmSpeed;
         sumXY += bdmSpeed*trimValue;
         num   += 1.0;
//         Logging::print("trimTargetClock(): %6d    %10ld %10ld\n", trimValue, bdmSpeed, targetBDMFrequency-bdmSpeed);
      }
   }

//   Logging::print("N=%f, sumX=%f, sumXX=%f, sumY=%f, sumYY=%f, sumXY=%f\n",
//                    num, sumX, sumXX, sumY, sumYY, sumXY);

   // Calculate linear regression co-efficients
   beta  = (num*sumXY-sumX*sumY)/(num*sumXX-sumX*sumX);
   alpha = (sumY-beta*sumX)/num;

   // Estimate required trim value
   trimValueF = ((targetBDMFrequency-alpha)/beta);

   if ((trimValueF <= 5.0) || (trimValue >= 505.0)) { // resulted in extreme value
      trimValueF = 256.0;                             // replace with 'Safe' trim value
      rc = PROGRAMMING_RC_ERROR_TRIM;
   }

   trimValue = (int)round(trimValueF);
   trimMSB   = trimValue>>1;
   trimLSB   = trimValue&0x01;

//   Logging::print("alpha= %f, beta= %f, trimF= %f, trimMSB= %d (0x%02X), trimLSB= %d\n",
//           alpha, beta, trimValueF, trimMSB, trimMSB, trimLSB);

//   Logging::print("trimTargetClock() Result: trim=0x%3.3x (%d), measured bdmSpeed=%ld\n",
//           savedTrimValue, savedTrimValue, bestFrequency);

   *returnTrimValue  = trimValue;

   // Set trim value (LSB first)
   if ((do9BitTrim && (writeClockRegister(trimAddress+1, trimLSB) != BDM_RC_OK)) ||
       (writeClockRegister(trimAddress, trimMSB) != BDM_RC_OK)) {
      return PROGRAMMING_RC_ERROR_BDM_WRITE;
   }
   // Check connection at that speed
   if (USBDM_Connect() != BDM_RC_OK) {
      return PROGRAMMING_RC_ERROR_BDM_CONNECT;
   }
   if (USBDM_GetSpeedHz(&bdmSpeed) != BDM_RC_OK) {
      return PROGRAMMING_RC_ERROR_BDM_CONNECT;
   }
   *measuredBusFrequency = bdmSpeed*parameters.getBDMtoBUSFactor();

   return rc;
}


USBDM_ErrorCode FlashProgrammer::trimMCG_Clock(MK_MCG_ClockParameters_t *clockParameters) {
   LOGGING_E;

   static const MK_MCG_ClockParameters_t MCG_LowSpeedParameters = {
         // bus clock = reference clock * (512,1024)/8/2
         //           = (32,64)*refClk (~32.5kHz)
         //           ~ (1,2) MHz
         /* .mcgC1   = */ 0x04, // IREFS
         /* .mcgC2   = */ 0x80, // LOCRE0
         /* .mcgC3   = */ 0x80, // TRIM=default
         /* .mcgC4   = */ 0x00, // FTRIM=0
         /* .mcgC5   = */ 0x00, //
         /* .mcgC6   = */ 0x00, //
   };

   uint32_t MCGTRIM                = parameters.getClockAddress()+2;
   unsigned int  clockMultiplier;
   unsigned long targetBusFrequency;
   unsigned long originalBusFrequency;
   unsigned long measuredBusFrequency;
   uint16_t trimValue;
   USBDM_ErrorCode rc;

   switch (parameters.getClockType()) {
      case S08MCGV2:
      case S08MCGV3:
         clockMultiplier = 512;
         break;
      case S08MCGV1:
         clockMultiplier = 1024;
         break;
      default:
         return PROGRAMMING_RC_ERROR_ILLEGAL_PARAMS;
   }

   targetBusFrequency = parameters.getClockTrimFreq()*(clockMultiplier/8/2);

   *clockParameters = MCG_LowSpeedParameters;

   Logging::print("TrimF = %.2f kHz, clock Multiplier=%d => Trim bus Freq=%.2f kHz\n",
         parameters.getClockTrimFreq()/1000.0, (1024/8/2), targetBusFrequency/1000.0);

   // Program clock for a low speed to improve accuracy of trimming
   rc = configureMCG_Clock(&originalBusFrequency, clockParameters);
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
//   Logging::print("trimMGCClock(Clock Freq = %.2f kHz, bus Freq = %.2f kHz)\n",
//           parameters.getClockTrimFreq()/1000.0, bdmFrequency/1000.0);

   rc = FlashProgrammer::trimTargetClock(MCGTRIM, targetBusFrequency, &trimValue, &measuredBusFrequency, TRUE);
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
   Logging::print("Desired Freq = %.2f kHz, "
         "Meas. Freq=%.2f kHz, Trim=0x%02X/%1.1X\n",
         parameters.getClockTrimFreq()/1000.0,
         (measuredBusFrequency/(clockMultiplier/16))/1000.0,
         trimValue>>1, trimValue&0x01);

   // Update trim value
   clockParameters->mcgTrim  = trimValue>>1;
   clockParameters->mcgSC   |= trimValue&0x01;

   return rc;
}

//! Determines trim values for the target clock. \n
//! The values determined are written to the Flash image for later programming.
//!
//! @param flashImage - Flash image to be updated.
//!
//! @return error code see \ref USBDM_ErrorCode
//!
//! @note If the trim frequency indicated in parameters is zero then no trimming is done.
//!       This is not an error.
//!
USBDM_ErrorCode FlashProgrammer::setFlashTrimValues(FlashImage *flashImage) {
   LOGGING_Q;
   ClockParameters clockTrimParameters;
   USBDM_ErrorCode rc;
   uint16_t  ftrimMergeValue;

   // Assume no trim or failure
   parameters.setClockTrimValue(0);

   // No trimming required
   if (parameters.getClockTrimFreq() == 0) {
      return PROGRAMMING_RC_OK;
   }
   // Logging::print("setFlashTrimValues() - trimming\n");
   progressTimer->restart("Calculating Clock Trim");

#if TARGET == RS08
   uint32_t NVTRIM_address  = parameters.getClockTrimNVAddress();
   uint32_t NVFTRIM_address = parameters.getClockTrimNVAddress()+1;
#else
   uint32_t NVFTRIM_address = parameters.getClockTrimNVAddress();
   uint32_t NVTRIM_address  = parameters.getClockTrimNVAddress()+1;
#endif

   switch (parameters.getClockType()) {
      case CLKEXT:
      case CLKINVALID:
      default:
         return PROGRAMMING_RC_OK;
      case MKMCGV1:
         // 9-bit value
         rc = trimMCG_Clock(&clockTrimParameters.mcg);
         if (rc != PROGRAMMING_RC_OK) {
            return rc;
         }
         parameters.setClockTrimValue((clockTrimParameters.mcg.mcgTrim<<1)|
                                      (clockTrimParameters.mcg.mcgSC&0x01));
         flashImage->setValue(parameters.getClockTrimNVAddress()+1,
                                         clockTrimParameters.mcg.mcgTrim);
         flashImage->setValue(parameters.getClockTrimNVAddress(),
                                         clockTrimParameters.mcg.mcgSC&0x01);
         return PROGRAMMING_RC_OK;
   }
   return PROGRAMMING_RC_ERROR_ILLEGAL_PARAMS;
}

//=======================================================================
//! Updates the memory image from the target flash Clock trim location(s)
//!
//! @param flashImage   = Flash image
//!
USBDM_ErrorCode FlashProgrammer::dummyTrimLocations(FlashImage *flashImage) {
   LOGGING_Q;
   unsigned size  = 0;
   uint32_t start = 0;

   // Not using trim -> do nothing
   if ((parameters.getClockTrimNVAddress() == 0) ||
       (parameters.getClockTrimFreq() == 0)) {
      Logging::print("Not using trim, no adjustment to image\n");
      return PROGRAMMING_RC_OK;
   }
   start = parameters.getClockTrimNVAddress();
   size  = 2;
   if (size == 0) {
      return PROGRAMMING_RC_OK;
   }
   // Read existing trim information from target
   uint8_t data[10];
   USBDM_ErrorCode rc = USBDM_ReadMemory(1,size,start,data);
   if (rc != BDM_RC_OK) {
      Logging::print("Trim location read failed\n");
      return PROGRAMMING_RC_ERROR_BDM_READ;
   }
   Logging::print("Modifying image[0x%06X..0x%06X]\n",
         start, start+size-1);
   // Update image
   for(uint32_t index=0; index < size; index++ ) {
      flashImage->setValue(start+index, data[index]);
   }
   return PROGRAMMING_RC_OK;
}
