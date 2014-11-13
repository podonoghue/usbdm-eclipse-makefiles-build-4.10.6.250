/*
 * armInterface.h
 *
 *  Created on: 18/08/2012
 *      Author: podonoghue
 */

#ifndef ARMINTERFACE_H_
#define ARMINTERFACE_H_

#include "USBDM_API.h"
#include "USBDM_API_Private.h"

DLL_LOCAL
extern bool armInitialiseDone;
DLL_LOCAL
extern bool pendingResetRelease;

USBDM_ErrorCode resetARM(TargetMode_t targetMode);
USBDM_ErrorCode armConnect(TargetType_t targetType);
USBDM_ErrorCode armDisconnect(TargetType_t targetType);

#endif /* ARMINTERFACE_H_ */
