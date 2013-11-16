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
USBDM_ErrorCode armSwdConnect();
USBDM_ErrorCode armJtagConnect();

#endif /* ARMINTERFACE_H_ */
