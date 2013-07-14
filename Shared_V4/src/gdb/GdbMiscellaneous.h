/*
 * gdbMiscellaneous.h
 *
 *  Created on: 02/07/2013
 *      Author: Peter
 */

#ifndef GDBMISCELLANEOUS_H_
#define GDBMISCELLANEOUS_H_

USBDM_ErrorCode usbdmInit(USBDM_ExtendedOptions_t *bdmOptions);
USBDM_ErrorCode usbdmInit(TargetType_t targetType);
USBDM_ErrorCode usbdmClose(void);
USBDM_ErrorCode usbdmResetTarget(bool retry = true);

#endif /* GDBMISCELLANEOUS_H_ */
