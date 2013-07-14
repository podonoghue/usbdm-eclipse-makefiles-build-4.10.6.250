/*
 * Shared.cpp
 *
 *  Created on: 18/12/2012
 *      Author: PODonoghue
 */

#ifndef SHARED_CPP_
#define SHARED_CPP_

#include <tr1/memory>

#include "USBDM_API.h"
#include "Log.h"
#include "USBDM_AUX.h"
#include "DeviceData.h"
//#include "FlashPanel.h"
#include "AppSettings.h"

class Shared {

public:
   USBDM_ExtendedOptions_t    bdmOptions;           //!< Current BDM options
   int                        gdbServerPort;        //!< Port for GDB server
   std::string                bdmSerialNumber;      //!< Serial number of BDM to use
   bool                       bdmMatchRequired;     //!< If true then BDM must match serial number

   USBDM_ExtendedOptions_t&   getBdmOptions()            { return bdmOptions; }

#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
   DeviceDataBase*            deviceDatabase;       //!< Database of available devices
   DeviceDataPtr              currentDevice;        //!< Currently selected device
   int                        currentDeviceIndex;   //!< Index of current device
   DeviceDataBase*            getDeviceDataBase()        { return deviceDatabase; }
   DeviceDataPtr&             getCurrentDevice()         { return currentDevice; }
   int                        getCurrentDeviceIndex()    { return currentDeviceIndex; }

   bool                       exitOnClose;          //!< Indicates GDB server should exit when connection closed
   bool                       isExitOnClose() const      { return exitOnClose; }
   void                       setExitOnClose(bool exitOnClose) { this->exitOnClose = exitOnClose; }
#endif

   int                        getGdbServerPort()         { return gdbServerPort; }
   void                       setGdbServerPort(int port) { gdbServerPort = port; }

   /*! Sets BDM to use based on serial number
    *
    *   @param serialNumber  BDM serial number to look for
    *   @param matchRequired If true then are particular BDM is required
    *
    *   @note If matchRequired=false then serialNumberis only a preferred BDM.
    */
   void setBdmSerialNumber(std::string serialNumber, bool matchRequired = false) {
      bdmSerialNumber  = serialNumber;
      bdmMatchRequired = matchRequired && (serialNumber.length() != 0);
   }

   /*! Get serial number of selected BDM
    *
    *   @return serial number
    */
   std::string &getBdmSerialNumber()  { return bdmSerialNumber; }
   bool         getBdmMatchRequired() { return bdmMatchRequired; }

   Shared(TargetType_t targetType);

   USBDM_ErrorCode loadDeviceDatabase(void);

   virtual ~Shared();

   USBDM_ErrorCode initBdm(void);
   USBDM_ErrorCode closeBdm(void);

#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
   USBDM_ErrorCode setCurrentDeviceByIndex(int deviceIndex);
   USBDM_ErrorCode setCurrentDeviceByName(string name);
#endif

   void loadSettings(const AppSettings &settings);
   void saveSettings(AppSettings &settings);

   virtual bool updateState() {
      return true;
   }
};

typedef std::tr1::shared_ptr<Shared> SharedPtr;

#endif /* SHARED_CPP_ */
