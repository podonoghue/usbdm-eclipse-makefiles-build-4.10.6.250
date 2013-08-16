/*! \file
    \brief Provides device data

    DeviceData.cpp

    \verbatim
    USBDM
    Copyright (C) 2009  Peter O'Donoghue

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
   -============================================================================
   | 12 Aug 2011 | Changed device directory so avoid need for installation - pgo
   | 15 June     | Changed to std::tr1::shared_ptr (from boost)            - pgo
   +============================================================================
   \endverbatim
*/
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
#include "Common.h"
#include "DeviceXmlParser.h"
#include "ApplicationFiles.h"
#include "DeviceData.h"
#include "Log.h"

static string emptyString("");

//static void strUpper(char *s) {
//   if (s == NULL) {
//	   return;
//   }
//   while (*s != '\0') {
//      int ch = ::toupper(*s);
//      *s++ = ch;
//   }
//}

//! Allows meaningful printing of memory ranges
//!
std::ostream& operator<<(std::ostream& s, const MemoryRegion mr) {
   s << setiosflags (ios_base::showbase | ios_base::hex);
   s << mr.getMemoryTypeName(mr.type) <<  "[";
   for (unsigned rangeIndex=0; rangeIndex<mr.memoryRanges.size(); rangeIndex++) {
      s << mr.memoryRanges[rangeIndex].start << "..." << mr.memoryRanges[rangeIndex].end;
      if (rangeIndex+1<mr.memoryRanges.size())
         s << ',';
   }
   if (mr.registerAddress != 0)
      s << ", reg=" << mr.registerAddress;
   if (mr.pageAddress != 0)
      s << ", pp=" << mr.pageAddress;
   s << "]";
   s << resetiosflags (ios_base::showbase | ios_base::uppercase | ios_base::hex);
   return s;
}

//! Mappings for Clock types
const EnumValuePair ClockTypes::clockNames[] = {
   EnumValuePair(  CLKEXT,       ("External") ),
   EnumValuePair(  S08ICGV1,     ("S08ICGV1") ),
   EnumValuePair(  S08ICGV2,     ("S08ICGV2") ),
   EnumValuePair(  S08ICGV3,     ("S08ICGV3") ),
   EnumValuePair(  S08ICGV4,     ("S08ICGV4") ),
   EnumValuePair(  S08ICSV1,     ("S08ICSV1") ),
   EnumValuePair(  S08ICSV2,     ("S08ICSV2") ),
   EnumValuePair(  S08ICSV2x512, ("S08ICSV2x512") ),
   EnumValuePair(  S08ICSV3,     ("S08ICSV3") ),
   EnumValuePair(  S08ICSV4,     ("S08ICSV4") ),
   EnumValuePair(  S08MCGV1,     ("S08MCGV1") ),
   EnumValuePair(  S08MCGV2,     ("S08MCGV2") ),
   EnumValuePair(  S08MCGV3,     ("S08MCGV3") ),
   EnumValuePair(  RS08ICSOSCV1, ("RS08ICSOSCV1") ),
   EnumValuePair(  RS08ICSV1,    ("RS08ICSV1") ),
   EnumValuePair(  CLKINVALID,   ("Invalid Clock") ),
   EnumValuePair(  0,              ""),
};

DeviceData *DeviceData::shallowCopy(const DeviceData &other) {
   *this = other;
   return this;
}

//! Returns the default non-volatile flash location for the clock trim value
//!
//! @param  clockType - clock type being queried
//!
//! @return Address of clock trim location(s)
//!
uint32_t DeviceData::getDefaultClockTrimNVAddress(ClockTypes_t clockType) {
#if TARGET == RS08
    return 0x3FFA;
#elif TARGET == CFV1
    return 0x3FE;
#elif TARGET == HCS08
   switch (clockType) {
      case S08ICGV1 :
      case S08ICGV2 :
      case S08ICGV3 :
      case S08ICGV4 :      return 0xFFBE;

      case S08ICSV1 :
      case S08ICSV2 :
      case S08ICSV2x512 :
      case S08ICSV3 :
      case RS08ICSOSCV1 :
      case RS08ICSV1 :     return 0xFFAE;

      case S08ICSV4 :      return 0xFF6E;

      case S08MCGV1 :
      case S08MCGV2 :
      case S08MCGV3 :      return 0xFFAE;

      case CLKINVALID :
      case CLKEXT :
      default :            return 0U;
   }
#else
   return 0;
#endif
}

//! Returns the default non-volatile flash location for the clock trim value
//!
//! @return Address of clock trim location(s) for the current clock type
//!
uint32_t DeviceData::getDefaultClockTrimNVAddress()  const {
   return getDefaultClockTrimNVAddress(clockType);
}

//! Returns the default (nominal) trim frequency for the currently selected clock
//!
//! @return clock trim frequency in Hz.
//!
uint32_t DeviceData::getDefaultClockTrimFreq(ClockTypes_t clockType) {
   switch (clockType) {
      case S08ICGV1 :
      case S08ICGV2 :
      case S08ICGV3 :
      case S08ICGV4 :
         return 243000UL;

      case S08ICSV1 :
      case S08ICSV2 :
      case S08ICSV2x512 :
      case S08ICSV3 :
      case S08ICSV4 :
      case RS08ICSOSCV1 :
      case RS08ICSV1 :
         return 31250UL;

      case S08MCGV1 :
      case S08MCGV2 :
      case S08MCGV3 :
         return 31250UL;

      case CLKINVALID :
      case CLKEXT :
      default :
         return 0U;
   }
}

//! Returns the default (nominal) trim frequency for the currently selected clock
//!
//! @return clock trim frequency in Hz.
//!
uint32_t DeviceData::getDefaultClockTrimFreq()  const {
   return getDefaultClockTrimFreq(clockType);
}

//! Returns the default clock register address
//!
//! @return clock register address
//!
uint32_t DeviceData::getDefaultClockAddress(ClockTypes_t clockType) {
#if TARGET == CFV1
   return 0xFF8048; // There really isn't a sensible default
#elif TARGET == RS08
   return 0x0238;   // There really isn't a sensible default
#elif TARGET == HCS08
   switch (clockType) {
      case S08ICGV1 :
      case S08ICGV2 :
      case S08ICGV3 :
      case S08ICGV4 :
      case S08MCGV1 :
      case S08MCGV2 :
      case S08MCGV3 :
         return 0x0048;

      case S08ICSV1 :
      case S08ICSV2x512 :
         return 0x0038;

      case S08ICSV2 :
         return 0x0048;

      case S08ICSV3 :
         return 0x0038;

      case RS08ICSOSCV1 :
         return 0x023C;

      case RS08ICSV1 :
      case CLKINVALID :
      case CLKEXT :
      default :
         return 0U;
   }
#else
   return 0;
#endif
}

//! Returns the default (nominal) trim frequency for the currently selected clock
//!
//! @return clock trim frequency in Hz.
//!
uint32_t DeviceData::getDefaultClockAddress()  const {
   return getDefaultClockAddress(clockType);
}

//! Determines the clock type from a string description
//!
ClockTypes_t ClockTypes::getClockType(const std::string &typeName) {
int sub;

   for (sub=0; !clockNames[sub].getName().empty(); sub++) {
      if (clockNames[sub].getName().compare(typeName) == 0) {
         return (ClockTypes_t) clockNames[sub].getValue();
      }
   }
   Logging::print("getClockType(): Error: invalid clock type '%s'\n", typeName.c_str());
   return CLKINVALID;
}

//! Determines the clock type from a string description
//!
ClockTypes_t ClockTypes::getClockType(const char *_typeName) {
   string typeName(_typeName);
   return getClockType(typeName);
}

int ClockTypes::getClockIndex(const std::string &typeName) {
   return (int)getClockType(typeName);
}

int ClockTypes::getClockIndex(ClockTypes_t clockType) {
   return (int)clockType;
}

//! Determines the clock name from a clock type
//!
//! @param clockType Clocktype to map to name
//!
//! @return string describing the clock
//!
const string ClockTypes::getClockName(ClockTypes_t clockType) {
int sub;

   for (sub=0; !clockNames[sub].getName().empty(); sub++) {
      if (clockNames[sub].getValue() == clockType)
         return clockNames[sub].getName();
   }
   Logging::print("getClockName(): Error: invalid clock type %d\n", clockType);
   return emptyString;
}

//! Checks if the SDID is used by the device
//!
//! @param desiredSDID  The SDID to check against
//! @param acceptZero   Accept a zero SDID
//!
//! @return true/false result of check
//!
bool DeviceData::isThisDevice(uint32_t  desiredSDID, bool acceptZero) const {
   unsigned int index;

   if (((targetSDIDs.size() == 0)||(targetSDIDs[0]) == 0) && acceptZero) {
      // 0x0000 or empty matches all
      return true;
   }
   for (index=0; index<targetSDIDs.size(); index++) {
//      Logging::print("Comparing Target=0x%04X with Desired=0x%04X, Mask=0x%04X\n", targetSDIDs[index], desiredSDID, targetSDIDMask);
      if (((targetSDIDs[index]^desiredSDID)&targetSDIDMask) == 0x0000)
         return true;
   }
   return false;
}

//! Checks if any of the SDIDs provided are used by the device
//!
//! @param desiredSDIDs Map of {SDIDaddress,SDIDs} to check against
//! @param acceptZero   Accept a zero SDID
//!
//! @return true/false result of check
//!
bool DeviceData::isThisDevice(std::map<uint32_t,uint32_t> desiredSDIDs, bool acceptZero) const {
   map<uint32_t,uint32_t>::iterator sdidEntry;

   if (((targetSDIDs.size() == 0)||(targetSDIDs[0]) == 0) && acceptZero) {
      // 0x0000 or empty matches all
      return true;
   }
   for (sdidEntry = desiredSDIDs.begin();
        sdidEntry != desiredSDIDs.end();
        sdidEntry++) {
      if ((SDIDAddress == sdidEntry->first) && isThisDevice(sdidEntry->second, acceptZero ))
         return true;
      }
   return false;
}

//! Determines the memory region containing an address in given memory space
//!
//! @param address     - The address to check
//! @param memorySpace - Memory space to check (MS_None, MS_Program, MS_Data)
//!
//! @return shared_ptr for Memory region found (or NULL if none found)
//!
MemoryRegionConstPtr DeviceData::getMemoryRegionFor(uint32_t address, MemorySpace_t memorySpace) const {
   // Check cached location to avoid searching in many cases
   if ((lastMemoryRegionUsed != NULL) &&
        lastMemoryRegionUsed->isCompatibleType(memorySpace) &&
        lastMemoryRegionUsed->contains(address)
        ) {
      return lastMemoryRegionUsed;
   }
   for (int index=0; ; index++) {
      lastMemoryRegionUsed = getMemoryRegion(index);
      if (lastMemoryRegionUsed == NULL) {
         break;
      }
      if (lastMemoryRegionUsed->isCompatibleType(memorySpace) &&
          lastMemoryRegionUsed->contains(address)
          ) {
         return lastMemoryRegionUsed;
      }
   }
   return MemoryRegionPtr();
}

//! Determines the memory type for an address
//!
//! @param address     - The address to check
//! @param memorySpace - Memory space to check (MS_None, MS_Program, MS_Data)
//!
//! @return Memory type of region (or MemInvalid if no information available)
//!
MemType_t DeviceData::getMemoryType(uint32_t address, MemorySpace_t memorySpace) {
   MemoryRegionConstPtr memoryRegion = getMemoryRegionFor(address, memorySpace);
   if (memoryRegion != NULL) {
      return memoryRegion->getMemoryType();
   }
   return MemInvalid;
}

//! Sets the security of all memory regions to a custom value
//!
//! @param securityValue - custom value to use
//!
void DeviceData::setCustomSecurity(const std::string &securityValue) {
   Logging log("DeviceData::setCustomSecurity");
   security = SEC_CUSTOM;
   int index = 0;
   MemoryRegionPtr memoryRegionPtr = getMemoryRegion(index);
   while (memoryRegionPtr != NULL) {
      const MemoryRegion::MemoryRange *memoryRange = memoryRegionPtr->getMemoryRange(0);
      if (memoryRange == NULL) {
         throw(MyException("DeviceData::setCustomSecurity() - empty memory range!"));
      }
      SecurityEntryPtr securityEntry = memoryRegionPtr->getSecurityEntry();
      if (securityEntry != NULL) {
         Logging::print("securityEntry = %p, use_count = %d, securityInfo = %s\n", &*securityEntry, securityEntry.use_count(), (const char *)securityEntry->toString().c_str());
         securityEntry->setCustomSecureInformation(SecurityInfoPtr(new SecurityInfo(0, SecurityInfo::custom, securityValue)));
         SecurityInfoPtr getCustomSecureInformation = securityEntry->getCustomSecureInformation();
//         Logging::print("getCustomSecureInformation = %p, use_count = %d, size = %d, securityInfo = %s\n", &*getCustomSecureInformation, getCustomSecureInformation.use_count(), getCustomSecureInformation->getSize(), (const char *)getCustomSecureInformation->toString().c_str());
      }
      memoryRegionPtr = getMemoryRegion(++index);
   }
}

//! Determines the page number for an address
//!
//! @param address - The address to check
//!
//! @return page number (PPAGE value) or  MemoryRegion::NoPageNo if not paged/found
//!
uint16_t DeviceData::getPageNo(uint32_t address) {
   // Check cached location to avoid searching in most cases
   if ((lastMemoryRegionUsed != NULL) && lastMemoryRegionUsed->contains(address))
      return lastMemoryRegionUsed->getPageNo(address);

   for (int index=0; ; index++) {
      lastMemoryRegionUsed = getMemoryRegion(index);
      if (lastMemoryRegionUsed == NULL)
         break;
      if (lastMemoryRegionUsed->contains(address))
         return lastMemoryRegionUsed->getPageNo(address);
   }
   return MemoryRegion::NoPageNo;
}

//! Searches the known devices for a device with given name
//!
//! @param targetName - Name of device
//!
//! @returns entry found or NULL if no suitable device found
//!
//! @note - If the device is an alias then it will return the true device
//!
DeviceDataConstPtr DeviceDataBase::findDeviceFromName(const string &targetName) const {

   static int recursionCheck = 0;
//   Logging::print("findDeviceFromName(%s)\n", (const char *)targetName.c_str());

   if (recursionCheck++>5) {
      throw MyException("Recursion limit in DeviceDataBase::findDeviceFromName");
   }
//   // Note - Assumes ASCII string
//   char buff[50];
//   strncpy(buff, targetName.c_str(), sizeof(buff));
//   buff[sizeof(buff)-1] = '\0';
//   strUpper(buff);

   DeviceDataConstPtr theDevice;
   vector<DeviceDataPtr>::const_iterator it;
   for (it = deviceData.begin(); it != deviceData.end(); it++) {
      if (strcasecmp((*it)->getTargetName().c_str(), targetName.c_str()) == 0) {
         theDevice = static_cast<DeviceDataConstPtr>(*it);
         Logging::print("findDeviceFromName(%s) found %s%s\n",
                        (const char *)targetName.c_str(), (const char *)(theDevice->getTargetName().c_str()), theDevice->isAlias()?"(alias)":"");
         if (theDevice->isAlias()) {
            theDevice = findDeviceFromName(theDevice->getAliasName());
         }
         break;
      }
   }
   recursionCheck--;
   if (theDevice == NULL) {
      Logging::print("findDeviceFromName(%s) => Device not found\n", (const char *)targetName.c_str());
   }
   return theDevice;
}

//! Searches the known devices for a device with given name
//!
//! @param targetName - Name of device
//!
//! @returns index or -1 if not found
//!
int DeviceDataBase::findDeviceIndexFromName(const string &targetName) const {

   vector<DeviceDataPtr>::const_iterator it;
   for (it = deviceData.begin(); it != deviceData.end(); it++) {
      if (strcasecmp((*it)->getTargetName().c_str(), targetName.c_str()) == 0) {
         return it - deviceData.begin();
      }
   }
   Logging::print("findDeviceIndexFromName(%s) => Device not found\n", targetName.c_str());
   return -1;
}

//! A generic device to use as a default
DeviceDataPtr DeviceDataBase::defaultDevice;

//! \brief Loads the known devices list from the configuration file.
//!
void DeviceDataBase::loadDeviceData(void) {
   Logging log("DeviceDataBase::loadDeviceData");

#if TARGET == HCS08
   #define CONFIG_FILEPATH DEVICE_DATABASE_DIRECTORY "/hcs08_devices.xml"
#elif TARGET == RS08
   #define CONFIG_FILEPATH DEVICE_DATABASE_DIRECTORY "/rs08_devices.xml"
#elif TARGET == CFV1
   #define CONFIG_FILEPATH DEVICE_DATABASE_DIRECTORY "/cfv1_devices.xml"
#elif TARGET == HC12
   #define CONFIG_FILEPATH DEVICE_DATABASE_DIRECTORY "/hcs12_devices.xml"
#elif TARGET == CFVx
   #define CONFIG_FILEPATH DEVICE_DATABASE_DIRECTORY "/cfvx_devices.xml"
#elif (TARGET == ARM) || (TARGET == ARM_SWD)
   #define CONFIG_FILEPATH DEVICE_DATABASE_DIRECTORY "/arm_devices.xml"
#elif TARGET == MC56F80xx
   #define CONFIG_FILEPATH DEVICE_DATABASE_DIRECTORY "/dsc_devices.xml"
#endif

   try {
      string appFilePath = getApplicationFilePath(CONFIG_FILEPATH);
      if (appFilePath.empty()) {
         throw MyException("DeviceDataBase::loadDeviceData() - failed to find device database file");
      }
      DeviceXmlParser::loadDeviceData(appFilePath, this);
   }
   catch (MyException &exception) {
      // Create dummy default device
//      defaultDevice = *aDevice.insert(aDevice.end(), new DeviceData()).base();
      Logging::print(" - Exception \'%s\'\n", exception.what());
      deviceData.clear();
      DeviceDataPtr aDevice = DeviceDataPtr(new DeviceData());
      aDevice->setTargetName("Invalid Database");
      setDefaultDevice(aDevice);
      addDevice(aDevice);
      throw exception;
   }
   catch (...) {
      Logging::print(" - Unknown exception\n");
      deviceData.clear();
      DeviceDataPtr aDevice = DeviceDataPtr(new DeviceData());
      aDevice->setTargetName("Invalid Database");
      setDefaultDevice(aDevice);
      addDevice(aDevice);
      throw MyException("DeviceDataBase::loadDeviceData() - Unknown exception");
   }
#if defined(LOG) && 0
   listDevices();
#endif
   Logging::print(" - %d devices loaded\n", deviceData.size());
}

void DeviceDataBase::listDevices() const {
   Logging log("DeviceDataBase::listDevices");

   vector<DeviceDataPtr>::const_iterator it;
   int lineCount = 0;
   try {
      for (it = deviceData.begin(); it != deviceData.end(); it++) {
         DeviceDataConstPtr deviceData = (*it);
         if (deviceData == NULL) {
            Logging::print("Null device pointer\n");
            continue;
         }
         bool aliased = deviceData->isAlias();
         if (aliased) {
            deviceData = findDeviceFromName(deviceData->getTargetName());
            if (deviceData == NULL) {
               Logging::print("Failed to find alias\n");
               continue;
            }
         }
#if (TARGET == ARM) || (TARGET == CFVx) || (TARGET==ARM_SWD)
         if (lineCount == 0) {
            Logging::print("\n");
            Logging::print("#                     SDID                                                \n");
            Logging::print("#    Target           Address    SDID          Script? Flash?             \n");
            Logging::print("#=========================================================================\n");
         }
         Logging::print("%-20s%s 0x%08X 0x%08X %7s %7s\n",
               deviceData->getTargetName().c_str(), aliased?"(A)":"   ",
//                  ClockTypes::getClockName(deviceData->getClockType()).c_str(),
//                  deviceData->getClockAddress(),
//                  deviceData->getClockTrimNVAddress(),
//                  deviceData->getClockTrimFreq()/1000.0,
               deviceData->getSDIDAddress(),
               deviceData->getSDID(),
               deviceData->getFlashScripts()?"Yes":"No",
               deviceData->getFlashProgram()?"Yes":"No"
         );
#else
         if (lineCount == 0) {
            Logging::print("\n");
            Logging::print("#                      RAM          Clock    Clock   NVTRIM    Trim                                     \n");
            Logging::print("# Target         Start     End      Name     Addr     Addr     Freq.  SDIDA    SDID  Scripts? FlashP?   \n");
            Logging::print("#=======================================================================================================\n");
         }
         Logging::print("%-14s%s 0x%06X 0x%06X %10s 0x%06X 0x%06X %6.2f %08X %08X %4s %4s\n",
               deviceData->getTargetName().c_str(), aliased?"(A)":"   ",
               deviceData->getRamStart(), deviceData->getRamEnd(),
               ClockTypes::getClockName(deviceData->getClockType()).c_str(),
               deviceData->getClockAddress(),
               deviceData->getClockTrimNVAddress(),
               deviceData->getClockTrimFreq()/1000.0,
               deviceData->getSDIDAddress(),
               deviceData->getSDID(),
               deviceData->getFlashScripts()?"Y":"N",
               deviceData->getFlashProgram()?"Y":"N"
         );
#endif
#if 1
         for (int regionNum=0; deviceData->getMemoryRegion(regionNum) != NULL; regionNum++) {
            MemoryRegionConstPtr reg=deviceData->getMemoryRegion(regionNum);
            Logging::print("      %10s: ", reg->getMemoryTypeName());
            if (reg->getFlashprogram())
               Logging::printq("FP=Yes, ");
            else
               Logging::printq("        ");
            Logging::printq("SS=%6d ", reg->getSectorSize());
            for(unsigned index=0; ; index++) {
               const MemoryRegion::MemoryRange *memoryRange = reg->getMemoryRange(index);
               if (memoryRange == NULL) {
                  break;
               }
               Logging::printq("(0x%08X,0x%08X", memoryRange->start, memoryRange->end);
               if ((memoryRange->pageNo != MemoryRegion::DefaultPageNo) &&
                   (memoryRange->pageNo != MemoryRegion::NoPageNo) &&
                   (memoryRange->pageNo != ((memoryRange->start>>16)&0xFF))){
                  Logging::printq(",P=0x%02X)", memoryRange->pageNo);
               }
               else {
                  Logging::printq(")", memoryRange->start, memoryRange->end);
               }
            }
            Logging::print("\n");
         }
         Logging::print("\n");
#endif
//         const TclScript *tclScript;
//         tclScript = deviceData->getPreSequence();
//         if (tclScript != NULL) {
//            Logging::print("preSequence \n=========================\n"
//                  "%s\n========================\n", tclScript->toString().c_str());
//         }
//         tclScript = deviceData->getPostSequence();
//         if (tclScript != NULL) {
//            Logging::print("postSequence \n=========================\n"
//                  "%s\n========================\n", tclScript->toString().c_str());
//         }
//         tclScript = deviceData->getUnsecureSequence();
//         if (tclScript != NULL) {
//            Logging::print("unsecureSequence \n=========================\n"
//                  "%s\n========================\n", tclScript->toString().c_str());
//         }
         //         std::stringstream buffer;
         //         buffer.exceptions(std::ios::badb(*it) | std::ios::failbit);
         //         buffer.str("");
         //         buffer << setw(15) << deviceData->getTargetName();
         //         buffer << setw(14) << ClockTypes::getClockName(deviceData->getClockType());
         //         buffer << setiosflags (ios_base::showbase | ios_base::hex);
         //         buffer << setw(8) << deviceData->getClockAddress();
         //         buffer << setw(8) << deviceData->getClockAddress();
         //         buffer << resetiosflags (ios_base::showbase | ios_base::hex);
         //         buffer << setw(6) << deviceData->getClockTrimFreq()/1000.0;
         //         for (int memIndex=0; true; memIndex++) {
         //            const MemoryRegion *pMemRegion = deviceData->getMemoryRegion(memIndex);
         //            if (pMemRegion == NULL)
         //               break;
         //             buffer << " " << *pMemRegion;
         //         }
         //         for (int sdidIndex=0; true; sdidIndex++) {
         //            uint32_t sdid = deviceData->getSDID(sdidIndex);
         //            if (sdid == 0)
         //               break;
         //             buffer << " " << sdid;
         //         }
         //         buffer << endl;
         //         Logging::print(buffer.str().c_str());
         lineCount = (lineCount+1)%40;
      }
   } catch (...) {

   }
#if 0
   Logging::print("================================================\n"
         "Shared data, #elements = %d\n", sharedInformation.size());
   map<const string, SharedInformationItemPtr>::iterator mapIt;
   for (mapIt = sharedInformation.begin(); mapIt != sharedInformation.end(); mapIt++) {
      std::map<const std::string, SharedInformationItem> sharedInformation;
      const string &key   = mapIt->first;
//      const TclScript *item     = dynamic_cast<const TclScript *> (mapIt->second);
      Logging::print("key = %s\n", key.c_str());
//      if (item == NULL) {
//         Logging::print("Failed cast\n");
//      }
//      else {
//         Logging::print("%s", item->toString().c_str());
//      }
   }
   Logging::print("================================================\n");
#endif
}

DeviceDataBase::~DeviceDataBase() {
   Logging::print("DeviceDataBase::~DeviceDataBase()\n");
   sharedInformation.clear();

//   std::vector<DeviceDataPtr>::iterator itDevice = deviceData.begin();
//   while (itDevice != deviceData.end()) {
//      (*itDevice)->valid = false;
//      delete (*itDevice);
//      itDevice++;
//   }
   deviceData.clear();
}

DeviceData::~DeviceData() {
//   Logging::print("DeviceData::~DeviceData()\n");
}

std::string SecurityInfo::getSecurityInfo() const
{
    return securityInfo;
}

std::string SecurityDescription::getSecurityDescription() const
{
   return securityDescription;
}

 void SecurityDescription::setSecurityDescription(std::string s)
{
    securityDescription = s;
}

unsigned SecurityInfo::getSize() const {
    return size;
}

SecurityInfo::SecType SecurityInfo::getMode() const {
    return mode;
}

int aToi(char ch) {
   if ((ch >= '0') && (ch <= '9'))
      return ch -'0';
   else if ((ch >= 'a') && (ch <= 'f'))
      return ch -'a' + 10;
   else if ((ch >= 'A') && (ch <= 'F'))
      return ch -'A' + 10;
   else
      return -1;
}

const uint8_t *SecurityInfo::getData() const {
   unsigned       cSub = 0;
   static uint8_t data[100];
   if (size > sizeof(data)) {
      throw MyException("Security field too large in SecurityInfo::getData()");
   }
   for (unsigned sub=0; sub<size; sub++) {
      // Skip non-numeric leading chars
      while ((aToi(securityInfo[cSub]) < 0) && (cSub < securityInfo.length())) {
         cSub++;
      }
      data[sub]  = aToi(securityInfo[cSub++])<<4;
      data[sub] += aToi(securityInfo[cSub++]);
   }
   return data;
}

static inline char tohex(uint8_t value) {
   static const char table[] = "0123456789ABCDEF";
   return table[value&0x0F];
}

void SecurityInfo::setData(unsigned size, uint8_t *data) {
   securityInfo.clear();
   for (unsigned sub=0; sub<size; sub++) {
      char value[2];
      value[0] = tohex(data[sub]>>4);
      value[1] = tohex(data[sub]);
      securityInfo.append(value);
   }
}

//! Obtain string describing the memory type
//!
//! @param memoryType - Memory type
//!
//! @return - ptr to static string describing type
//!
const char *MemoryRegion::getMemoryTypeName(MemType_t memoryType) {
   static const char *names[] = {
            "Invalid",
            "RAM",
            "EEPROM",
            "FLASH",
            "FlexNVM",
            "FlexRAM",
            "ROM",
            "IO",
            "PFlash",
            "DFlash",
            "XRAM",
            "PRAM",
            "XROM",
            "PROM",
   };
   if((unsigned )((memoryType)) >= (sizeof (names) / sizeof (names[0])))
      memoryType = (MemType_t)((0));
   return names[memoryType];
}

//! Indicates if a programmable type e.g Flash, eeprom etc.
//!
//! @param memoryType - Memory type
//!
//! @return - true/false result
//!
bool MemoryRegion::isProgrammableMemory(MemType_t memoryType) {
   switch (memoryType) {
      case MemEEPROM  :
      case MemFLASH   :
      case MemFlexNVM :
      case MemPFlash  :
      case MemDFlash  :
      case MemXROM    :
      case MemPROM    :
         return true;
         break;
      default :
         return false;
   }
}

//! Indicates if a memory type is compatible with a memory space e.g. MemPROM lies in MS_Program
//!
//! @param memoryType  - Memory type
//! @param memorySpace - Memory space
//!
//! @return - true/false result
//!
bool MemoryRegion::isCompatibleType(MemType_t memoryType, MemorySpace_t memorySpace) {
   switch(memorySpace&MS_SPACE) {
      default         : return true;
      case MS_Program : return ((memoryType == MemPRAM) || (memoryType == MemPROM));
      case MS_Data    : return ((memoryType == MemXRAM) || (memoryType == MemXROM));
   }
}


//=============================================================================================

//! Return minimum required ration between backing store in EEPROM and EEEPROM
//!
//! @return ratio e.g. 16 => EEPROM size >= 16* EEEPROM size
//!
unsigned FlexNVMInfo::getBackingRatio() const {
    return backingRatio;
}

//! Adds a permitted EEEPROM values for use in partition command
//!
//! @param eeepromSizeValue - Description of value
//!
void FlexNVMInfo::addEeepromSizeValues(const EeepromSizeValue &eeepromSizeValue) {
   this->eeepromSizeValues.push_back(eeepromSizeValue);
}

//! Adds a permitted Partition values for use in partition command
//!
//! @param flexNvmPartitionValue  - Description of value
//!
void FlexNVMInfo::addFlexNvmPartitionValues(const FlexNvmPartitionValue &flexNvmPartitionValue) {
   this->flexNvmPartitionValues.push_back(flexNvmPartitionValue);
}

void FlexNVMInfo::setBackingRatio(unsigned  backingRatio) {
    this->backingRatio = backingRatio;
}


