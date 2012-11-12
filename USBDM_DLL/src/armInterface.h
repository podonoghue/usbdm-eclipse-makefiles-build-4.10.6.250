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

extern bool armInitialiseDone;

USBDM_ErrorCode resetARM(TargetMode_t targetMode);
USBDM_ErrorCode armSwdConnect();
USBDM_ErrorCode armJtagConnect();

#endif /* ARMINTERFACE_H_ */
