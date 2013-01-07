/*
 * USBDM_GDI.h
 *
 *  Created on: 22/12/2012
 *      Author: podonoghue
 */

#ifndef USBDM_GDI_H_
#define USBDM_GDI_H_

#include "GDI.h"
#include "Log.h"
extern const TargetType_t        targetType;
extern const DiFeaturesT         diFeatures;
extern bool                      pcWritten;
extern uint32_t                  pcResetValue;
extern bool                      programmingSupported;
extern bool                      forceMassErase;
extern USBDM_ExtendedOptions_t   bdmOptions;
extern USBDM_ExtendedOptions_t   bdmProgrammingOptions;
extern RetryMode                 initialConnectOptions;
extern RetryMode                 softConnectOptions;
extern USBDMStatus_t             USBDMStatus;

extern DiReturnT setErrorState(DiReturnT   errorCode, const char *errorString = NULL);
extern DiReturnT setErrorState(DiReturnT   errorCode, USBDM_ErrorCode rc);

//=====================================================================================
// Error handling
extern DiReturnT   currentError;
extern const char *currentErrorString;

//! Check if pending error condition and return immediately if so
//!
#define CHECK_ERROR_STATE() \
   if (currentError == DI_ERR_FATAL) {\
      Logging::print("CHECK_ERROR_STATE() - failed, rc=%d\n", currentError); \
      return currentError; \
   }

extern USBDM_ErrorCode targetConnect(RetryMode retryMode);

#endif /* USBDM_GDI_H_ */
