/*
 * Shared.cpp
 *
 *  Created on: 05/07/2013
 *      Author: Peter
 */

#include "wxPlugin.h"
#include "Shared.h"

/*! Load device database
 *
 */
USBDM_ErrorCode Shared::loadDeviceDatabase(void) {
   USBDM_ErrorCode rc = BDM_RC_OK;

#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
   if (deviceDatabase == NULL) {
      deviceDatabase = new DeviceDataBase;
      try {
         deviceDatabase->loadDeviceData();
      } catch (MyException &exception) {
         rc = BDM_RC_DEVICE_DATABASE_ERROR;
      }
   }
   DeviceDataConstPtr defaultDevice = deviceDatabase->getDefaultDevice();
   currentDevice = DeviceDataPtr(new DeviceData);
   currentDevice->shallowCopy(*defaultDevice);
   currentDeviceIndex = 0;
#endif
   return rc;
}

#if 0
/*! Opens the currently selected BDM (based on serial number)
 *
 */
USBDM_ErrorCode Shared::openBdm(void) {
   LOGGING_Q;
   Logging::print("Description  = \'%s\'\n", bdmInformation.getDescription().c_str());
   Logging::print("SerialNumber = \'%s\'\n", bdmInformation.getSerialNumber().c_str());

   USBDM_ErrorCode rc = BDM_RC_OK;

   do {
      // Initialise the BDM interface before use
      USBDM_Init();
      if (rc != BDM_RC_OK) {
         continue;
      }
      // Open selected BDM
      rc = USBDM_OpenBySerialNumber(bdmOptions.targetType, bdmInformation.getSerialNumber(), true);
   } while (false);
   if (rc != BDM_RC_OK) {
      closeBdm();
   }
   return rc;
}
#endif

/*! Opens & initialises the currently selected BDM (based on serial number)
 *
 *  Entry - Assumes .bdmInformation contains required information
 *
 *  @return Error code indicating outcome.
 */
USBDM_ErrorCode Shared::initBdm(void) {
   LOGGING;

   Logging::print("SerialNumber = \'%s\'\n", getBdmSerialNumber().c_str());

   USBDM_ErrorCode rc = BDM_RC_OK;

   do {
      // Initialise the BDM interface before use
      USBDM_Init();
      if (rc != BDM_RC_OK) {
         continue;
      }
      // Open selected BDM
      rc = USBDM_OpenBySerialNumber(bdmOptions.targetType, getBdmSerialNumber(), getBdmMatchRequired());
      if (rc != BDM_RC_OK) {
         continue;
      }
      rc = USBDM_SetExtendedOptions(&bdmOptions);
      if (rc != BDM_RC_OK) {
         continue;
      }
      rc = USBDM_SetTargetTypeWithRetry(bdmOptions.targetType);
      if (rc != BDM_RC_OK) {
         continue;
      }
   } while (false);
   if (rc != BDM_RC_OK) {
      closeBdm();
   }
   return rc;
}

/*! Close BDM
 *
 */
USBDM_ErrorCode Shared::closeBdm(void) {
//   (void)USBDM_SetTargetType(T_OFF);
   return USBDM_Close();
}

#define settingsKey "Shared"

const string bdmSerialNumberKey(         settingsKey ".bdmSerailNumber");

const string deviceNameKey(              settingsKey ".deviceName");
const string powerOffDurationKey(        settingsKey ".powerOffDuration");
const string powerOnRecoveryIntervalKey( settingsKey ".powerOnRecoveryInterval");
const string resetDurationKey(           settingsKey ".resetDuration");
const string resetReleaseIntervalKey(    settingsKey ".resetReleaseInterval");
const string resetRecoveryIntervalKey(   settingsKey ".resetRecoveryInterval");
const string setClockTrimFreqKey(        settingsKey ".clockTrimFrequency");
const string clockTrimNVAddressKey(      settingsKey ".clockTrimNVAddress");
const string securityKey(                settingsKey ".security");
const string eraseOptionKey(             settingsKey ".eraseOption");
const string targetBusFrequencyKey(      settingsKey ".targetBusFrequency");
const string gdbServerPortNumberKey(     settingsKey ".gdbServerPortNumber");

const string setTargetVddKey(            settingsKey ".setTargetVdd");
const string cycleTargetVddOnResetKey(   settingsKey ".cycleTargetVddOnReset");
const string cycleTargetVddonConnectKey( settingsKey ".cycleTargetVddonConnect");
const string leaveTargetPoweredKey(      settingsKey ".leaveTargetPowered");
const string automaticReconnectKey(      settingsKey ".automaticReconnect");
const string guessSpeedIfNoSYNCKey(      settingsKey ".guessSpeedIfNoSYNC");
const string bdmClockSourceKey(          settingsKey ".bdmClockSource");
const string useResetSignalKey(          settingsKey ".useResetSignal");
const string maskInterruptsKey(          settingsKey ".maskInterrupts");
const string interfaceFrequencyKey(      settingsKey ".interfaceFrequency");
const string usePSTSignalsKey(           settingsKey ".usePSTSignals");

#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)

/*!  Select current device by device index
 *
 *   @param deviceIndex - Index into device database of desired device
 *
 *   @return true  => device is made the current device \n
 *           false => index out of range, device is set to the 1st device (index 0)
 */
USBDM_ErrorCode Shared::setCurrentDeviceByIndex(int newDeviceIndex) {
   Logging log("Shared::setCurrentDeviceByIndex()");

   log.print("newDeviceIndex = %d\n", newDeviceIndex);
   USBDM_ErrorCode rc = BDM_RC_OK;
   if ((newDeviceIndex < 0) || ((unsigned)newDeviceIndex >= deviceDatabase->getNumDevice())) {
      Logging::print("Index out of range (%d)\n", newDeviceIndex);
      newDeviceIndex = 0;
      rc = BDM_RC_UNKNOWN_DEVICE;
   }
   currentDevice->shallowCopy((*deviceDatabase)[newDeviceIndex]);
   if (currentDevice->isAlias()) {
      // Keep device name & SDIDs but update device details from real device
      string aliasedName = currentDevice->getTargetName();
      const std::vector<uint32_t> targetSDIDs = currentDevice->getTargetSDIDs();
      currentDevice->shallowCopy(*deviceDatabase->findDeviceFromName(aliasedName));
      Logging::print("devIndex=%d, aliased(%s) => %s\n",
                     newDeviceIndex, (const char *)aliasedName.c_str(), (const char *)currentDevice->getTargetName().c_str());
      currentDevice->setTargetName(aliasedName);
      currentDevice->setTargetSDIDs(targetSDIDs);
   }
   currentDeviceIndex = newDeviceIndex;
   return rc;
}

/*!  Select current device by device name
 *
 *   @param deviceName - Name of desired device
 *
 *   @return true  => device is made the current device \n
 *           false => device not found, device is set to the default device
 */
USBDM_ErrorCode Shared::setCurrentDeviceByName(string deviceName) {
   Logging log("Shared::setCurrentDeviceByName()");

   Logging::print("Device = \'%s\'\n", deviceName.c_str());
   int newDeviceIndex = deviceDatabase->findDeviceIndexFromName(deviceName);
   if (newDeviceIndex < 0) {
      Logging::print("Device not found (%s)\n", deviceName.c_str());
   }
   return setCurrentDeviceByIndex(newDeviceIndex);
}
#endif

/*!
 *
 */
Shared::Shared(TargetType_t targetType) {
   Logging log("Shared::Shared");

#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
   deviceDatabase = NULL;
   currentDeviceIndex = 0;
   loadDeviceDatabase();
   exitOnClose = false;
#endif

   // Set options to default
   bdmOptions.size       = sizeof(USBDM_ExtendedOptions_t);
   bdmOptions.targetType = targetType;
   USBDM_GetDefaultExtendedOptions(&bdmOptions);

   gdbServerPort    = 1234;
   bdmSerialNumber  = "";
   bdmMatchRequired = false;
}

Shared::~Shared() {
   Logging log("Shared::~Shared");

#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
   if (deviceDatabase != NULL) {
      delete deviceDatabase;
      deviceDatabase = NULL;
   }
#endif
}

/*!  Load settings from object
 *
 *  @param  settings Settings object
 */
void Shared::loadSettings(const AppSettings &settings) {
   Logging log("Shared::loadSettings");

   // Load previously used BDM
   setBdmSerialNumber(settings.getValue(bdmSerialNumberKey,            bdmSerialNumber));

#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
   // Load previous device description (fixed device data)
   setCurrentDeviceByName(settings.getValue(deviceNameKey, ""));

   // Load the trim information (mutable device data)
   currentDevice->setClockTrimFreq(                          settings.getValue(setClockTrimFreqKey,    0));
   currentDevice->setClockTrimNVAddress(                     settings.getValue(clockTrimNVAddressKey,  currentDevice->getClockTrimNVAddress()));
   SecurityOptions_t securityOption =  (SecurityOptions_t)   settings.getValue(securityKey,            currentDevice->getSecurity());
   if (securityOption == SEC_CUSTOM) {
      securityOption = SEC_UNSECURED;
   }
   currentDevice->setSecurity(securityOption);
   currentDevice->setEraseOption( (DeviceData::EraseOptions) settings.getValue(eraseOptionKey,    (int)currentDevice->getEraseOption()));
   currentDevice->setConnectionFreq(                         settings.getValue(targetBusFrequencyKey,  0));
#endif

   setGdbServerPort(settings.getValue(gdbServerPortNumberKey, getGdbServerPort()));

   bdmOptions.targetVdd                = (TargetVddSelect_t) settings.getValue(setTargetVddKey,             bdmOptions.targetVdd);
   bdmOptions.cycleVddOnReset          =                     settings.getValue(cycleTargetVddOnResetKey,    bdmOptions.cycleVddOnReset);
   bdmOptions.cycleVddOnConnect        =                     settings.getValue(cycleTargetVddonConnectKey,  bdmOptions.cycleVddOnConnect);
   bdmOptions.leaveTargetPowered       =                     settings.getValue(leaveTargetPoweredKey,       bdmOptions.leaveTargetPowered);
   bdmOptions.autoReconnect            =     (AutoConnect_t) settings.getValue(automaticReconnectKey,       bdmOptions.autoReconnect);
   bdmOptions.guessSpeed               =                     settings.getValue(guessSpeedIfNoSYNCKey,       bdmOptions.guessSpeed);
   bdmOptions.bdmClockSource           =     (ClkSwValues_t) settings.getValue(bdmClockSourceKey,           bdmOptions.bdmClockSource);
   bdmOptions.useResetSignal           =                     settings.getValue(useResetSignalKey,           bdmOptions.useResetSignal);
   bdmOptions.maskInterrupts           =                     settings.getValue(maskInterruptsKey,           bdmOptions.maskInterrupts);
   bdmOptions.interfaceFrequency       =                     settings.getValue(interfaceFrequencyKey,       bdmOptions.interfaceFrequency);
   bdmOptions.usePSTSignals            =                     settings.getValue(usePSTSignalsKey,            bdmOptions.usePSTSignals);

   bdmOptions.powerOffDuration         =                     settings.getValue(powerOffDurationKey,         bdmOptions.powerOffDuration);
   bdmOptions.powerOnRecoveryInterval  =                     settings.getValue(powerOnRecoveryIntervalKey,  bdmOptions.powerOnRecoveryInterval);
   bdmOptions.resetDuration            =                     settings.getValue(resetDurationKey,            bdmOptions.resetDuration);
   bdmOptions.resetReleaseInterval     =                     settings.getValue(resetReleaseIntervalKey,     bdmOptions.resetReleaseInterval);
   bdmOptions.resetRecoveryInterval    =                     settings.getValue(resetRecoveryIntervalKey,    bdmOptions.resetRecoveryInterval);
}

/*!  Save settings to object
 *
 *  @param  settings Settings object
 */
void Shared::saveSettings(AppSettings &settings) {
   Logging log("Shared::saveSettings");

   settings.addValue(bdmSerialNumberKey,           getBdmSerialNumber());

#if defined(FLASH_PROGRAMMER) || defined(GDB_SERVER)
   // Save device name
   settings.addValue(deviceNameKey,                currentDevice->getTargetName());

   // Save non-device fixed settings
   if (currentDevice->getClockTrimFreq() != 0) {
      settings.addValue(setClockTrimFreqKey,       currentDevice->getClockTrimFreq());
      settings.addValue(clockTrimNVAddressKey,     currentDevice->getClockTrimNVAddress());
   }
   SecurityOptions_t securityOption = currentDevice->getSecurity();
   if (securityOption == SEC_CUSTOM) {
      securityOption = SEC_UNSECURED;
   }
   settings.addValue(securityKey,                  securityOption);
   settings.addValue(eraseOptionKey,          (int)currentDevice->getEraseOption());
   settings.addValue(targetBusFrequencyKey,        currentDevice->getConnectionFreq());
#endif

   settings.addValue(gdbServerPortNumberKey,       getGdbServerPort());

   settings.addValue(setTargetVddKey,              bdmOptions.targetVdd);
   settings.addValue(cycleTargetVddOnResetKey,     bdmOptions.cycleVddOnReset);
   settings.addValue(cycleTargetVddonConnectKey,   bdmOptions.cycleVddOnConnect);
   settings.addValue(leaveTargetPoweredKey,        bdmOptions.leaveTargetPowered);
   settings.addValue(automaticReconnectKey,        bdmOptions.autoReconnect);
   settings.addValue(guessSpeedIfNoSYNCKey,        bdmOptions.guessSpeed);
   settings.addValue(bdmClockSourceKey,            bdmOptions.bdmClockSource);
   settings.addValue(useResetSignalKey,            bdmOptions.useResetSignal);
   settings.addValue(maskInterruptsKey,            bdmOptions.maskInterrupts);
   settings.addValue(interfaceFrequencyKey,        bdmOptions.interfaceFrequency);
   settings.addValue(usePSTSignalsKey,             bdmOptions.usePSTSignals);

   settings.addValue(powerOffDurationKey,          bdmOptions.powerOffDuration);
   settings.addValue(powerOnRecoveryIntervalKey,   bdmOptions.powerOnRecoveryInterval);
   settings.addValue(resetDurationKey,             bdmOptions.resetDuration);
   settings.addValue(resetReleaseIntervalKey,      bdmOptions.resetReleaseInterval);
   settings.addValue(resetRecoveryIntervalKey,     bdmOptions.resetRecoveryInterval);
}
