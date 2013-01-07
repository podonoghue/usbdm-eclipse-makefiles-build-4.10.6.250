/*
 * Shared.cpp
 *
 *  Created on: 18/12/2012
 *      Author: PODonoghue
 */

#ifndef SHARED_CPP_
#define SHARED_CPP_

#include "USBDM_API.h"
#include "Log.h"

#if defined(FLASH_PROGRAMMER)
#include "DeviceData.h"
#include "FlashPanel.h"
#endif

class Shared {

public:
   USBDM_ExtendedOptions_t    bdmOptions;       //!< Current bdm options
   USBDM_ExtendedOptions_t&   getBdmOptions()   { return bdmOptions; }

#ifdef FLASH_PROGRAMMER
   DeviceDataBase*   deviceDatabase;        //!< Database of available devices
   DeviceDataPtr     currentDevice;         //!< Currently selected device
   DeviceDataBase*   getDeviceDataBase()    { return deviceDatabase;}
   DeviceDataPtr&    getCurrentDevice()     { return currentDevice; }
#endif

   Shared(TargetType_t targetType) {
      Logging log("Shared::Shared");
#ifdef FLASH_PROGRAMMER
      deviceDatabase = NULL;
#endif
      // Set options to default
      Logging::print("Resetting extended BDM options\n");
      bdmOptions.size       = sizeof(USBDM_ExtendedOptions_t);
      bdmOptions.targetType = targetType;
      USBDM_GetDefaultExtendedOptions(&bdmOptions);
   }
   virtual bool updateState() { return true; };
   virtual ~Shared() {};
};
#endif /* SHARED_CPP_ */
