/*
 * DeviceData.hpp
 *
 *  Created on: 27/02/2010
 *      Author: podonoghue
 */

#ifndef DEVICEDATA_HPP_
#define DEVICEDATA_HPP_
#include <vector>
#include <map>
#include <string>
#include <streambuf>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <tr1/memory>
#include "Common.h"
#include "MyException.h"
#include "Log.h"
#include "USBDM_API.h"

//! RS08/HCS08/CFV1 clock types
//!
typedef enum {
   CLKINVALID = -1,
   CLKEXT = 0,
   S08ICGV1,S08ICGV2,S08ICGV3,S08ICGV4,
   S08ICSV1,S08ICSV2,S08ICSV2x512,S08ICSV3,S08ICSV4,
   RS08ICSOSCV1,
   RS08ICSV1,
   S08MCGV1,S08MCGV2,S08MCGV3,
} ClockTypes_t;

//! memory types
//!
typedef enum {
   MemInvalid  = 0,
   MemRAM      = 1,
   MemEEPROM   = 2,
   MemFLASH    = 3,
   MemFlexNVM  = 4,
   MemFlexRAM  = 5,
   MemROM      = 6,
   MemIO       = 7,
   MemPFlash   = 8,
   MemDFlash   = 9,
   MemXRAM     = 10, // DSC
   MemPRAM     = 11, // DSC
   MemXROM     = 12, // DSC
   MemPROM     = 13, // DSC
} MemType_t;

typedef enum {
  AddrLinear,
  AddrPaged,
} AddressType;

class EnumValuePair {
private:
   int                 value;
   const std::string   name;
public:
   int               getValue() const { return value; };
   const std::string getName()  const { return name; };
   EnumValuePair(int value, const std::string &name)
       : value(value), name(name) {
   }
};

//! Information on clock types
//!
class ClockTypes {
private:
   //! Mappings for Clock types
   static const EnumValuePair clockNames[];

public:
   static ClockTypes_t        getClockType(const std::string &typeName);
   static ClockTypes_t        getClockType(const char *typeName);
   static const std::string   getClockName(ClockTypes_t clockType);
   static int                 getClockIndex(const std::string &typeName);
   static int                 getClockIndex(ClockTypes_t clockType);
   ClockTypes() {
   };
};

//! SecurityInfo options when programming
//! These options affect the handling of the NVOPT/NVSEC location
//!
typedef enum {
   SEC_DEFAULT      = 0,   //!< Leave Flash image unchanged
   SEC_SECURED      = 1,   //!< Make Flash image secured
   SEC_UNSECURED    = 2,   //!< Make Flash image unsecured
   SEC_SMART        = 3,   //!< Modify flash image unless already modified
   SEC_INTELLIGENT  = 3,   //!< Modify flash image unless already modified
   SEC_CUSTOM       = 4,   //!< Use custom value
} SecurityOptions_t;

class SharedInformationItem {
public:
   virtual ~SharedInformationItem() {};
   int operator==(const SharedInformationItem &other) {
      return this == &other;
   }
};

typedef std::tr1::shared_ptr<SharedInformationItem> SharedInformationItemPtr;

class TclScript: public SharedInformationItem {
private:
   std::string script;
public:
   TclScript(std::string script) :
      script(script) {
//      print("TclScript()\n");
   }
   const std::string toString() const {
      return std::string(
            "TCL Script\n"
            "============================================================================" +
            script +
            "============================================================================\n");
   }
   const std::string getScript() const {
      return script;
   }
   ~TclScript() {
//      print("~TclScript()\n");
   }
};
typedef std::tr1::shared_ptr<TclScript>   TclScriptPtr;
typedef std::tr1::shared_ptr<const TclScript>   TclScriptConstPtr;

class RegisterDescription: public SharedInformationItem {
private:
   std::string description;
   unsigned    lastRegisterIndex;
public:
   RegisterDescription(std::string description, unsigned lastRegisterIndex) :
      description(description),
      lastRegisterIndex(lastRegisterIndex) {
   }
   const std::string toString() const {
      return std::string(
            "Register Description\n"
            "============================================================================" +
            description +
            "============================================================================\n");
   }
   const std::string getDescription() const {
      return description;
   }

   unsigned getLastRegisterIndex() const {
      return lastRegisterIndex;
   }
   ~RegisterDescription() {
//      print("~RegisterDescription()\n");
   }
};
typedef std::tr1::shared_ptr<RegisterDescription>   RegisterDescriptionPtr;
typedef std::tr1::shared_ptr<const RegisterDescription>   RegisterDescriptionConstPtr;

class FlashProgram: public SharedInformationItem {
public:
   std::string flashProgram;
   FlashProgram(std::string script) :
      flashProgram(script) {
//      print("FlashProgram()\n");
   }
   const std::string toString() const {
      return std::string(
            "flashProgram\n"
            "=========================================================================" +
            flashProgram +
            "=========================================================================\n");
   }
   ~FlashProgram() {
//      print("~FlashProgram()\n");
   }
};
typedef std::tr1::shared_ptr<FlashProgram> FlashProgramPtr;
typedef std::tr1::shared_ptr<const FlashProgram> FlashProgramConstPtr;

class SecurityDescription: public SharedInformationItem {
private:
   std::string securityDescription;

public:
   SecurityDescription(std::string desc)
    : securityDescription(desc) {
//        print("SecurityInfo()\n");
    }
    ~SecurityDescription() {
//        print("~SecurityInfo()\n");
    }
    const std::string toString() const {
       return std::string("SecurityDescription ==") + securityDescription + "==";
    }
    std::string    getSecurityDescription() const;
    void           setSecurityDescription(std::string s);
};

typedef std::tr1::shared_ptr<SecurityDescription> SecurityDescriptionPtr;
typedef std::tr1::shared_ptr<const SecurityDescription> SecurityDescriptionConstPtr;

class GnuInfoList: public SharedInformationItem {

public:
   GnuInfoList() {
//        print("SecurityInfo()\n");
    }
    ~GnuInfoList() {
//        print("~SecurityInfo()\n");
    }
    const std::string toString() const {
       return std::string("GnuInfoList");
    }
};

typedef std::tr1::shared_ptr<GnuInfoList> GnuInfoListPtr;
typedef std::tr1::shared_ptr<const GnuInfoList> GnuInfoListConstPtr;

class GnuInfo {

public:
   GnuInfo() {
//        print("SecurityInfo()\n");
    }
    ~GnuInfo() {
//        print("~SecurityInfo()\n");
    }
    const std::string toString() const {
       return std::string("GnuInfo");
    }
};

typedef std::tr1::shared_ptr<GnuInfo> GnuInfoPtr;
typedef std::tr1::shared_ptr<const GnuInfo> GnuInfoConstPtr;

class SecurityInfo: public SharedInformationItem {
public:
   enum SecType {unsecure, secure, custom};

private:
   unsigned    size;
   SecType     mode;
   std::string securityInfo;

public:
   SecurityInfo()
   : size(0), mode(custom), securityInfo("")
   {
//        print("SecurityInfo()\n");
   }
    SecurityInfo(int size, SecType mode, std::string securityInfo)
    : size(size), mode(mode), securityInfo(securityInfo)
    {
       Logging::print("SecurityInfo(%d, %d, %s)\n", size, mode, (const char *)securityInfo.c_str());
       if (size == 0) {
          // Auto size security
          this->size = securityInfo.size()/2;
       }
       else if (this->securityInfo.size()/2 != this->size) {
          throw MyException("Security value does not have correct length");
       }
    }
    SecurityInfo(const SecurityInfo& other)
    : size(other.size), mode(other.mode), securityInfo(other.securityInfo)
    {
    }
    ~SecurityInfo() {
//        print("~SecurityInfo()\n");
    }
    const std::string toString() const {
       static const char *modeNames[] = {"unsecure", "secure", "custom"};
       return std::string("SecurityInfo - ") + modeNames[mode] + " ==" + securityInfo + "==";
    }
    std::string    getSecurityInfo() const;
    void           setSecurityInfo(const std::string &securityInfo) {
       this->securityInfo = securityInfo;
    }
    unsigned       getSize() const;
    SecType        getMode() const;
    const uint8_t *getData() const;
    void           setData(unsigned size, uint8_t *data);
    void           setMode(SecType mode) { this->mode = mode; }
};
typedef std::tr1::shared_ptr<SecurityInfo> SecurityInfoPtr;
typedef std::tr1::shared_ptr<const SecurityInfo> SecurityInfoConstPtr;

class SecurityEntry: public SharedInformationItem {
private:
   SecurityDescriptionPtr  securityDescription;
   SecurityInfoPtr         unsecureInformation;
   SecurityInfoPtr         secureInformation;
   SecurityInfoPtr         customSecureInformation;

public:
   SecurityEntry(SecurityDescriptionPtr securityDesc,
                 SecurityInfoPtr        unsecureInfo,
                 SecurityInfoPtr        secureInfo)
    : securityDescription(securityDesc),
      unsecureInformation(unsecureInfo),
      secureInformation(secureInfo) {
//        print("SecurityInfo()\n");
    }
   SecurityEntry() {
        Logging::print("SecurityInfo()\n");
    }
    ~SecurityEntry() {
       Logging::print("~SecurityInfo()\n");
    }
    const std::string toString() const {
       return std::string("SecurityEntry - \n") +
              "=========================================================================\n" +
              "description =" + ((securityDescription==NULL)?std::string("null"):securityDescription->toString()) + "\n" +
              "unsecured   =" + ((unsecureInformation==NULL)?std::string("null"):unsecureInformation->toString()) + "\n" +
              "secured     =" + ((secureInformation==NULL)?std::string("null"):secureInformation->toString()) + "\n" +
              "custom      =" + ((customSecureInformation==NULL)?std::string("null"):customSecureInformation->toString()) + "\n" +
              "=========================================================================\n";
    }
    SecurityDescriptionConstPtr getSecurityDescription()     const { return securityDescription; };
    SecurityInfoConstPtr        getUnsecureInformation()     const { return unsecureInformation; };
    SecurityInfoConstPtr        getSecureInformation()       const { return secureInformation; };
    SecurityInfoConstPtr        getCustomSecureInformation() const { return customSecureInformation; };
    SecurityDescriptionPtr      getSecurityDescription()           { return securityDescription; };
    SecurityInfoPtr             getUnsecureInformation()           { return unsecureInformation; };
    SecurityInfoPtr             getSecureInformation()             { return secureInformation; };
    SecurityInfoPtr             getCustomSecureInformation()       { return customSecureInformation; };
    void                        setCustomSecureInformation(SecurityInfoPtr ptr)  { customSecureInformation = ptr; };
};

typedef std::tr1::shared_ptr<SecurityEntry> SecurityEntryPtr;
typedef std::tr1::shared_ptr<const SecurityEntry> SecurityEntryConstPtr;

class FlexNVMInfo: public SharedInformationItem {

public:
   class EeepromSizeValue {
   public:
      std::string    description;   // Description of this value
      uint8_t        value;         // EEPROM Data Set Size (as used in Program Partition command)
      unsigned       size;          // EEEPROM size in bytes (FlexRAM used for EEPROM emulation)
      EeepromSizeValue(std::string description, uint8_t value, unsigned size)
      : description(description), value(value), size(size)
      {}
   } ;
   class FlexNvmPartitionValue {
   public:
      std::string    description;  // Description of this value
      uint8_t        value;        // FlexNVM Partition Code (as used in Program Partition command)
      unsigned       backingStore; // EEPROM backing store size in bytes
      FlexNvmPartitionValue(std::string description, uint8_t value, unsigned backingStore)
      : description(description), value(value), backingStore(backingStore)
      {}
   };

private:
    unsigned backingRatio;
    std::vector<EeepromSizeValue>      eeepromSizeValues;
    std::vector<FlexNvmPartitionValue> flexNvmPartitionValues;

public:
    FlexNVMInfo(int backingRatio = 16)
    :backingRatio(backingRatio)
    {
//        print("FlexNVMInfo()\n");
    }

    ~FlexNVMInfo()
    {
//        print("~FlexNVMInfo()\n");
    }

    const std::string toString() const
    {
        return std::string("FlexNVMInfo - \n");
    }
    //! Returns list of permitted EEEPROM values for use in partition command
    //!
    //! @return vector of permitted values
    //!
    const std::vector<FlexNVMInfo::EeepromSizeValue> &getEeepromSizeValues() const {
        return eeepromSizeValues;
    }
    //! Returns list of permitted Partition values for use in partition command
    //!
    //! @return vector of permitted values
    //!
    const std::vector<FlexNVMInfo::FlexNvmPartitionValue> &getFlexNvmPartitionValues() const {
        return flexNvmPartitionValues;
    }
    void addEeepromSizeValues(const EeepromSizeValue &eeepromSizeValue);
    void addFlexNvmPartitionValues(const FlexNvmPartitionValue &flexNvmPartitionValue);

    unsigned getBackingRatio() const;
    void setBackingRatio(unsigned  backingRatio);
};
typedef std::tr1::shared_ptr<FlexNVMInfo> FlexNVMInfoPtr;
typedef std::tr1::shared_ptr<const FlexNVMInfo> FlexNVMInfoConstPtr;

// Represents a collection of related memory ranges
//
// This may be used to represent a non-contiguous range of memory locations that are related
// e.g. two ranges of Flash that are controlled by the same Flash controller as occurs in some HCS08s
//
class MemoryRegion: public SharedInformationItem {

private:
   MemoryRegion(MemoryRegion &);
//   MemoryRegion &operator=(MemoryRegion &);

public:
   static const uint16_t DefaultPageNo = 0xFFFF;
   static const uint16_t NoPageNo      = 0xFFFE;
   class MemoryRange {
      public:
         uint32_t start;
         uint32_t end;
         uint16_t pageNo;
   };
   std::vector<MemoryRange> memoryRanges;           //!< Memory ranges making up this region
   MemType_t                type;                   //!< Type of memory regions
   AddressType              addressType;            //!< Linear/Paged addressing
   uint32_t                 registerAddress;        //!< Control register addresses
   uint32_t                 pageAddress;            //!< Paging register address
   uint32_t                 securityAddress;        //!< Non-volatile option address
   uint32_t                 sectorSize;             //!< Size of sectors i.e. minimum erasable unit
   uint8_t                  alignment;              //!< Memory programming alignment requirement (1,2,4 etc)
   mutable uint32_t         lastIndexUsed;          //!< Last used memoryRanges index
   FlashProgramConstPtr     flashProgram;           //!< Region-specific flash algorithm
   SecurityEntryPtr         securityInformation;    //!< Region-specific security data
   FlexNVMInfoConstPtr      flexNVMInfo;

private:
   //! Find the index of the memory range containing the given address
   //!
   //! @param address - address to look for
   //!
   //! @return range index or -1 if not found
   //!
   //! @note - Uses cache
   //!
   int findMemoryRangeIndex(uint32_t address) const {
      if (type == MemInvalid)
         return -1;
      // Check cached address
      if ((lastIndexUsed < memoryRanges.size()) &&
          (memoryRanges[lastIndexUsed].start <= address) && (address <= memoryRanges[lastIndexUsed].end)) {
         return lastIndexUsed;
      }
      // Look through all memory ranges
      for (lastIndexUsed=0; lastIndexUsed<memoryRanges.size(); lastIndexUsed++) {
         if ((memoryRanges[lastIndexUsed].start <= address) && (address <= memoryRanges[lastIndexUsed].end)) {
            return lastIndexUsed;
         }
      }
//      // clear cache
//      lastIndexUsed = 1000;
      return -1;
   }

public:
   MemoryRegion (MemType_t type = MemInvalid,
                 uint32_t  registerAddress = 0,
                 uint32_t  pageAddress = 0,
                 uint32_t  securityAddress = 0,
                 uint32_t  sectorSize = 0,
                 uint8_t   alignment = 1) :
      type(type),
      addressType(AddrPaged),
      registerAddress(registerAddress),
      pageAddress(pageAddress),
      securityAddress(securityAddress),
      sectorSize(sectorSize),
      alignment(alignment),
      lastIndexUsed((uint32_t)-1)
   {
   }
   //! Add a memory range to this memory region
   //!
   //! @param startAddress - start address (inclusive)
   //! @param endAddress   - end address (inclusive)
   //! @param pageNo       - page number (if used)
   //!
   void addRange (uint32_t startAddress, uint32_t endAddress, uint16_t pageNo=DefaultPageNo) {
//      if (memRangeCount >= (sizeof(memoryRanges)/sizeof(memoryRanges[0])))
//         throw MyException("Too many memory ranges");
//      print("addRange(0x%6X, 0x%6X, 0x%2X)\n", startAddress, endAddress, pageNo);
      if (memoryRanges.size() == memoryRanges.capacity()) {
         unsigned newCapacity = 2*memoryRanges.capacity();
         if (newCapacity < 8) {
            newCapacity = 8;
         }
//         print("addRange() - resizing %d=>%d\n", memoryRanges.capacity(), newCapacity);
         memoryRanges.reserve(newCapacity);
      }
      if (pageAddress == 0) {
         // Non-paged memory
         pageNo = NoPageNo;
      }
      else if (pageNo == DefaultPageNo) {
         // Page no is usually just the 8-bit address
         pageNo = (startAddress>>16)&0xFF;
      }
      MemoryRange memoryRangeE = {startAddress, endAddress, pageNo};
      memoryRanges.push_back(memoryRangeE);
   }

   //! Check if an address is within this memory region
   //! @param address - address to check
   //!
   //! @return true/false result
   //!
   bool contains(uint32_t address) const {
      return findMemoryRangeIndex(address) >= 0;
   }

   //! Find the last contiguous address relative to the address
   //!
   //! @param address        Start address to check
   //! @param lastContinuous The end address of the largest contiguous memory range including address
   //! @param memorySpace    Memory space to check
   //!
   //! @return true  = start address is within memory
   //!         false = start address is not within memory
   //!
   bool findLastContiguous(uint32_t address, uint32_t *lastContinuous, MemorySpace_t memorySpace = MS_None) const {
      *lastContinuous = address;
      if (!isCompatibleType(memorySpace)) {
         return false;
      }
      int index = findMemoryRangeIndex(address);
      if (index<0) {
         // Start address not within region
         return false;
      }
      *lastContinuous = memoryRanges[index].end;
      return true;
   }

   //! Get page number for address
   //! @param address - address to check
   //!
   //! @return MemoryRegion::NoPageNo if not paged/within memory
   //!
   uint16_t getPageNo(uint32_t address) const {
      if (!contains(address))
         return MemoryRegion::NoPageNo;
      return memoryRanges[lastIndexUsed].pageNo;
   }

   //! Obtain string describing the memory type
   //!
   //! @param memoryType - Memory type
   //!
   //! @return - ptr to static string describing type
   //!
   static const char *getMemoryTypeName(MemType_t memoryType);

   //! Indicates if a programmable type e.g Flash, eeprom etc.
   //!
   //! @param memoryType - Memory type
   //!
   //! @return - true/false result
   //!
   static bool isProgrammableMemory(MemType_t memoryType);

   //! Indicates if the memory region is of a programmable type e.g Flash, eeprom etc.
   //!
   //! @return - true/false result
   //!
   bool isProgrammableMemory() const {
      return isProgrammableMemory(type);
   }
   //! Get name of memory type
   //!
   const char *getMemoryTypeName(void) const { return getMemoryTypeName(type); }

   //! Get security address (Flash location)
   //!
   uint32_t getSecurityAddress() const { return securityAddress; }

   // Only available on Flash & EEPROM
   uint32_t    getFCLKDIVAddress() const { return getRegisterAddress() + 0x0; }
   uint32_t    getFSECAddress()    const { return getRegisterAddress() + 0x1; }
   uint32_t    getFTSTMODAddress() const { return getRegisterAddress() + 0x1; }
   uint32_t    getFCNFGAddress()   const { return getRegisterAddress() + 0x3;}
   uint32_t    getFPROTAddress()   const { return getRegisterAddress() + 0x4; }
   uint32_t    getFSTATAddress()   const { return getRegisterAddress() + 0x5;}
   uint32_t    getFCMDAddress()    const { return getRegisterAddress() + 0x6;}
   uint32_t    getFADDRAddress()   const { return getRegisterAddress() + 0x8;}
   uint32_t    getFDATAAddress()   const { return getRegisterAddress() + 0xA;}
   uint32_t    getDummyAddress()   const { return memoryRanges[0].end & 0xFFFFFFF0; }
   uint32_t    getSectorSize()     const { return sectorSize; }
   AddressType getAddressType()    const { return addressType; }
   // Get memory region data alignment (1,2,4 etc)
   uint8_t     getAlignment()      const { return alignment; }

#if TARGET == RS08
   uint32_t    getFOPTAddress()    const { return getRegisterAddress();}
   uint32_t    getFLCRAddress()    const { return getRegisterAddress() + 1;}
#endif

   friend std::ostream & operator <<(std::ostream & s, const MemoryRegion mr);
   bool valid() const { return type != MemInvalid; }
   void setSecurityAddress(uint32_t address) { securityAddress = address; }

   MemType_t getMemoryType() const { return type; }
   static bool isCompatibleType(MemType_t memType, MemorySpace_t memorySpace);
   bool isCompatibleType(MemorySpace_t memorySpace) const {
      return isCompatibleType(type, memorySpace);
   }
   uint32_t  getPageAddress() const { return pageAddress; }
   uint32_t  getRegisterAddress() const {
//      if (registerAddress == 0) {
//         throw MyException("Register address not defined for memory region");
//      }
      return registerAddress;
   }
   const MemoryRange *getMemoryRange(unsigned index) const {
      if (index >= memoryRanges.size())
         return NULL;
      return &memoryRanges[index];
   }
   const MemoryRange *getMemoryRangeFor(uint32_t address) const {
      int index = findMemoryRangeIndex(address);
      if (index<0)
         return NULL;
      return &memoryRanges[index];
   }
   const FlashProgramConstPtr          getFlashprogram()        const { return flashProgram; }
   const SecurityDescriptionConstPtr   getSecurityDescription() const { return securityInformation->getSecurityDescription(); }
   const SecurityInfoConstPtr          getSecureInfo()          const { return securityInformation->getSecureInformation(); }
   const SecurityInfoConstPtr          getUnsecureInfo()        const { return securityInformation->getUnsecureInformation(); }
   const SecurityInfoConstPtr          getCustomSecureInfo()    const { return securityInformation->getCustomSecureInformation(); }

   void setFlashProgram(FlashProgramConstPtr program) { flashProgram = program; }
   void setAddressType(AddressType type)              { addressType = type; }

   void setSecurityEntry(SecurityEntryPtr info)      { securityInformation = info; }
   void setflexNVMInfo(FlexNVMInfoConstPtr info)     { flexNVMInfo = info; }
   SecurityEntryConstPtr   getSecurityEntry() const  { return securityInformation;  }
   SecurityEntryPtr        getSecurityEntry()        { return securityInformation;  }
   FlexNVMInfoConstPtr     getflexNVMInfo()   const  { return flexNVMInfo; }
};

typedef std::tr1::shared_ptr<MemoryRegion> MemoryRegionPtr;
typedef std::tr1::shared_ptr<const MemoryRegion> MemoryRegionConstPtr;

class DeviceData;
typedef std::tr1::shared_ptr<DeviceData> DeviceDataPtr;
typedef std::tr1::shared_ptr<const DeviceData> DeviceDataConstPtr;

class TargetSDID {
public:
   uint32_t mask; // 0 => wildcard
   uint32_t value;
   TargetSDID(uint32_t mask, uint32_t value) : mask(mask), value(value) {}
};

//! Information about a target device
//!
class DeviceData {
public:
   //! How to handle erasing of flash before programming
   typedef enum  {
      eraseNone,        //! Don't erase
      eraseMass,        //! Mass erase / unsecure
      eraseAll,         //! Erase all flash arrays
      eraseSelective,   //! Erase flash block selectively
   } EraseOptions;

   //! Get readable names for erase options
   static const char *getEraseOptionName(EraseOptions option) {
      switch (option) {
      case eraseNone      : return "EraseNone";
      case eraseMass      : return "EraseMass";
      case eraseAll       : return "EraseAll";
      case eraseSelective : return "EraseSelective";
      default :             return "Illegal erase option";
      }
   }
   //! Structure to hold FlexNVM information
   class FlexNVMParameters {
   public:
      FlexNVMParameters() :
         eeepromSize(0xFF),
         partionValue(0xFF) {
      }
      uint8_t eeepromSize;
      uint8_t partionValue;
   };

private:
   std::string                   targetName;             //!< Name of target
   std::string                   aliasName;              //!< Name of real target if alias
   bool                          hidden;                 //!< Device is hidden in programmer
   uint32_t                      ramStart;               //!< Start of internal RAM
   uint32_t                      ramEnd;                 //!< End of internal RAM
   ClockTypes_t                  clockType;              //!< Type of clock
   uint32_t                      clockAddress;           //!< Address of Clock register block
   uint32_t                      clockTrimNVAddress;     //!< Address of Non-volatile storage of trim value
   unsigned long int             clockTrimFreq;          //!< Trim frequency in Hz of the _internal_ clock e.g. 32.7 kHz (0 => no trim required)
   bool                          connectionFreqGiven;    //!< Use connectionFreq if needed
   unsigned long int             connectionFreq;         //!< BDM connection frequency in Hz
   uint32_t                      watchdogAddress;        //!< Address of watchdog (COPCTL, WDOG etc) register
   uint32_t                      SDIDAddress;            //!< Address of SDID register
   SecurityOptions_t             security;               //!< Determines security options of programmed target (modifies NVFOPT value)
   EraseOptions                  eraseOption;            //!< How to handle erasing of flash before programming
   uint16_t                      clockTrimValue;         //!< Clock trim value calculated for a particular device
   std::vector<MemoryRegionPtr>  memoryRegions;          //!< Different memory regions e.g. EEPROM, RAM etc.
   mutable MemoryRegionConstPtr  lastMemoryRegionUsed;   //!< To improve memory searches
   TclScriptConstPtr             flashScripts;           //!< Flash script
   FlashProgramConstPtr          commonFlashProgram;     //!< Common flash code
   FlexNVMParameters             flexNVMParameters;      //!< FlexNVM partitioning values
   FlexNVMInfoConstPtr           flexNVMInfo;            //!< Table describing FlexNVM partitioning
   std::vector<TargetSDID>       targetSDIDs;            //!< System Device Identification Register values (0=> don't know/care)
   RegisterDescriptionConstPtr   registerDescription;    //!< Register description

public:
   static const DeviceData    defaultDevice;
   static const unsigned int  BDMtoBUSFactor = 1;   //!< Factor relating measured BDM frequency to Target BUS frequency\n
                                                    //!< busFrequency = connectionFreq * BDMtoBUSFactor
public:
   const std::string              getTargetName()              const { return targetName; }
   const std::string              getAliasName()               const { return aliasName; }
   const TargetType_t             getTargetType()              const { return T_ARM; }
   bool                           isHidden()                   const { return hidden; }
   uint32_t                       getRamStart()                const { return ramStart; }
   uint32_t                       getRamEnd()                  const { return ramEnd; }
   ClockTypes_t                   getClockType()               const { return clockType; }
   uint32_t                       getClockAddress()            const { return clockAddress; }
   uint32_t                       getClockTrimNVAddress()      const { return clockTrimNVAddress; }
   uint16_t                       getClockTrimValue()          const { return clockTrimValue; }
   unsigned long                  getClockTrimFreq() /*Hz*/    const { return clockTrimFreq; }
   unsigned long                  getConnectionFreq() /*Hz*/   const { return connectionFreq; }
   SecurityOptions_t              getSecurity()                const { return security; }
   EraseOptions                   getEraseOption()             const { return eraseOption; }
   uint32_t                       getWatchdogAddress()         const { return watchdogAddress; }
   uint32_t                       getSDIDAddress()             const { return SDIDAddress; }
   unsigned int                   getBDMtoBUSFactor()          const { return BDMtoBUSFactor; }
   FlashProgramConstPtr           getCommonFlashProgram()      const { return commonFlashProgram; }
   FlashProgramConstPtr           getFlashProgram();
   TclScriptConstPtr              getFlashScripts()            const { return flashScripts; }
   FlexNVMInfoConstPtr            getflexNVMInfo()             const { return flexNVMInfo; }
   FlexNVMParameters              getFlexNVMParameters()       const { return flexNVMParameters; }
   const std::vector<TargetSDID>& getTargetSDIDs()             const { return targetSDIDs; }
   bool                           isAlias(void)                const { return !aliasName.empty();}
   RegisterDescriptionConstPtr    getRegisterDescription()     const { return registerDescription; }

   MemoryRegionConstPtr getMemoryRegion(unsigned index) const {
      if (index >= memoryRegions.size()) {
         return MemoryRegionPtr();
      }
      return memoryRegions[index];
   }

   MemoryRegionPtr getMemoryRegion(unsigned index) {
      if (index >= memoryRegions.size()) {
         return MemoryRegionPtr();
      }
      return memoryRegions[index];
   }

   MemoryRegionConstPtr getMemoryRegionFor(uint32_t address, MemorySpace_t memorySpace=MS_None) const;
   const std::vector<TargetSDID> getSDIDs() const { return targetSDIDs; }
   TargetSDID getSDID(unsigned index=0) const {
      if (index >= targetSDIDs.size()) {
         return TargetSDID(-1,-1);
      }
      return targetSDIDs[index];
   }
   static uint32_t   getDefaultClockTrimFreq(ClockTypes_t clockType);
   static uint32_t   getDefaultClockTrimNVAddress(ClockTypes_t clockType);
   static uint32_t   getDefaultClockAddress(ClockTypes_t clockType);
   uint32_t          getDefaultClockTrimFreq() const;
   uint32_t          getDefaultClockTrimNVAddress() const;
   uint32_t          getDefaultClockAddress() const;

   bool              isThisDevice(std::map<uint32_t,uint32_t> targetSDIDs, bool acceptZero=true) const ;
   bool              isThisDevice(uint32_t targetSDID, bool acceptZero=true) const ;

   MemType_t         getMemoryType(uint32_t address, MemorySpace_t memorySpace=MS_None);
   uint16_t          getPageNo(uint32_t address);

   void  addSDID(uint32_t mask, uint32_t value) {
      targetSDIDs.push_back(TargetSDID(mask, value));
   }

   void addMemoryRegion(MemoryRegionPtr pMemoryRegion) {
      memoryRegions.push_back(pMemoryRegion);
      if (((pMemoryRegion->getMemoryType() == MemRAM)||
           (pMemoryRegion->getMemoryType() == MemXRAM)) && (ramStart == 0)) {
         // Set default RAM range to first added RAM memory region
         const MemoryRegion::MemoryRange *mr = pMemoryRegion->getMemoryRange(0);
         ramStart = mr->start;
         ramEnd   = mr->end;
      }
      if (pMemoryRegion->getMemoryType() == MemFlexNVM) {
         // Copy FlexInfo from memory region to device - Only one FlexNVM in device allowed
         if (getflexNVMInfo() != NULL) {
            throw MyException("Multiple MemFlexNVM regions in device");
         }
         setflexNVMInfo(pMemoryRegion->getflexNVMInfo());
      }
   }
   void setTargetName(const std::string &name)                    { targetName = name; }
   void setAliasName(const std::string &name)                     { aliasName = name; }
   void setHidden(bool value = true)                              { hidden = value; }
   void setRamStart(uint32_t addr)                                { ramStart = addr; }
   void setRamEnd(uint32_t addr)                                  { ramEnd = addr; }
   void setClockType(ClockTypes_t type)                           { clockType = type; }
   void setClockAddress(uint32_t addr)                            { clockAddress = addr; }
   void setClockTrimNVAddress(uint32_t addr)                      { clockTrimNVAddress = addr; }
   void setClockTrimValue(uint16_t value)                         { clockTrimValue = value; }
   void setClockTrimFreq(unsigned long hertz) /*Hz*/              { clockTrimFreq = hertz; }
   void setConnectionFreq(unsigned long hertz /*Hz*/)             { connectionFreq = hertz; }
   void setSecurity(SecurityOptions_t option)                     { security = option; }
   void setCustomSecurity(const std::string &securityValue);
   void setEraseOption(EraseOptions option)                       { eraseOption = option; }
   void setWatchdogAddress(uint32_t addr)                         { watchdogAddress = addr; }
   void setSDIDAddress(uint32_t addr)                             { SDIDAddress = addr; }
   void setFlashScripts(TclScriptConstPtr script)                 { flashScripts = script; }
   void setCommonFlashProgram(FlashProgramConstPtr program)       { commonFlashProgram = program; }
   void setflexNVMInfo(FlexNVMInfoConstPtr info)                  { flexNVMInfo = info; }
   void setFlexNVMParameters(const FlexNVMParameters &param)      { flexNVMParameters = param;}
   void setTargetSDIDs(const std::vector<TargetSDID> &list)       { targetSDIDs = list; }

   void setRegisterDescription(RegisterDescriptionConstPtr desc)  { registerDescription = desc; }

   DeviceData( const std::string    &targetName,
               uint32_t             ramStart,
               uint32_t             ramEnd,
               ClockTypes_t         clockType,
               uint32_t             clockAddress,
               uint32_t             clockTrimNVAddress,
               unsigned long int    clockTrimFreq,
               uint32_t             flashStart              = 0,
               uint32_t             flashEnd                = 0,
               uint32_t             watchdogAddress         = 0x003C,
               uint32_t             SOPTAddress             = 0,
               uint32_t             SDIDAddress             = 0,
               SecurityOptions_t    security                = SEC_DEFAULT,
               bool                 noMassErase             = false,
               bool                 connectFrequencyGiven   = false,
               unsigned int         connectFrequency        = 8000,
               uint16_t             clockTrimValue          = 0
                  ) : targetName(targetName),
                      aliasName(""),
                      hidden(false),
                      ramStart(ramStart),
                      ramEnd(ramEnd),
                      clockType(clockType),
                      clockAddress(clockAddress),
                      clockTrimNVAddress(clockTrimNVAddress),
                      clockTrimFreq(clockTrimFreq),
                      connectionFreqGiven(false),
                      connectionFreq(0),
                      watchdogAddress(watchdogAddress),
                      SDIDAddress(SDIDAddress),
                      security(security),
                      eraseOption(eraseAll),
                      clockTrimValue(clockTrimValue)
                      {
//      print("DeviceData::DeviceData()\n");
      flexNVMParameters.eeepromSize  = 0xFF;
      flexNVMParameters.partionValue = 0xFF;
   };
   DeviceData() : targetName(""),
                  aliasName(""),
                  hidden(false),
                  ramStart(0),
                  ramEnd(0),
                  clockType(CLKINVALID),
                  clockAddress(0),
                  clockTrimNVAddress(0),
                  clockTrimFreq(0),
                  connectionFreqGiven(false),
                  connectionFreq(0),
                  watchdogAddress(0),
                  SDIDAddress(0),
                  security(SEC_DEFAULT),
                  eraseOption(eraseAll),
                  clockTrimValue(0)
                  {
//      print("DeviceData::DeviceData() - default\n");
      flexNVMParameters.eeepromSize  = 0xFF;
      flexNVMParameters.partionValue = 0xFF;
   }
   ~DeviceData();
   DeviceData *shallowCopy(const DeviceData&);

//private:
//   DeviceData &operator=(const DeviceData &);
};

//! Database of device information
//!
class DeviceDataBase {

private:
   std::vector<DeviceDataPtr>  deviceData;                                   //! List of devices
   std::map<const std::string, SharedInformationItemPtr> sharedInformation;  //! Shared information referenced by devices
   static DeviceDataPtr defaultDevice;                                       //! Generic 'default' device
   DeviceDataBase (DeviceDataBase &);                                        //! No copying
   DeviceDataBase &operator=(DeviceDataBase &);                              //! No assignment

public:
   void   loadDeviceData();
   DeviceDataConstPtr findDeviceFromName(const std::string &targetName) const;
   int findDeviceIndexFromName(const std::string &targetName) const;
   const DeviceData &operator[](unsigned index) const {
      if (index > deviceData.size()) {
         throw MyException("DeviceDataBase::operator[] - illegal index");
      }
      return *deviceData[index];
   };
   std::vector<DeviceDataPtr>::const_iterator begin() const {
      return static_cast<std::vector<DeviceDataPtr>::const_iterator>(deviceData.begin());
   }
   std::vector<DeviceDataPtr>::const_iterator end() const {
      return static_cast<std::vector<DeviceDataPtr>::const_iterator>(deviceData.end());
   }
   void   listDevices() const;
   static DeviceDataConstPtr getDefaultDevice() { return defaultDevice; }
   static DeviceDataConstPtr setDefaultDevice(const DeviceDataPtr defaultDevice) {
      DeviceDataBase::defaultDevice = defaultDevice;
      return defaultDevice;
   }
   unsigned getNumDevice() const { return this->deviceData.size(); }

   DeviceDataPtr addDevice(DeviceDataPtr device) {
      std::vector<DeviceDataPtr>::iterator itDev = deviceData.insert(deviceData.end(), device);
      return *itDev;
   }
   SharedInformationItemPtr addSharedData(std::string key, SharedInformationItemPtr pSharedData) {
      sharedInformation.insert(std::pair<const std::string, SharedInformationItemPtr>(key, pSharedData));
      return pSharedData;
   }
   SharedInformationItemPtr addSharedData(std::string key, SharedInformationItem *sharedData) {
      SharedInformationItemPtr pSharedData(sharedData);
      sharedInformation.insert(std::pair<const std::string, SharedInformationItemPtr>(key, pSharedData));
      return pSharedData;
   }
private:
   SharedInformationItemPtr getSharedData(std::string key) const {
      std::map<const std::string, SharedInformationItemPtr>::const_iterator it = sharedInformation.find(key);
      if (it == sharedInformation.end()) {
         throw MyException(std::string("DeviceDataBase::getSharedData() - Unable to find reference - ")+key);
      }
      return it->second;
   }
public:
   SecurityEntryPtr getSecurityEntry(std::string key) {
      SecurityEntryPtr ptr(std::tr1::dynamic_pointer_cast<SecurityEntry>(getSharedData(key)));
      if (ptr == NULL) {
         throw MyException(std::string("DeviceDataBase::getSecurityEntry() - Reference has wrong type - ")+key);
      }
      return ptr;
   }
   SecurityDescriptionPtr getSecurityDescription(std::string key) {
      SecurityDescriptionPtr ptr(std::tr1::dynamic_pointer_cast<SecurityDescription>(getSharedData(key)));
      if (ptr == NULL) {
         throw MyException(std::string("DeviceDataBase::getSecurityEntry() - Reference has wrong type - ")+key);
      }
      return ptr;
   }
   SecurityInfoConstPtr getSecurityInfo(std::string key) const {
      SecurityInfoPtr ptr(std::tr1::dynamic_pointer_cast<SecurityInfo>(getSharedData(key)));
      if (ptr == NULL) {
         throw MyException(std::string("DeviceDataBase::getSecurityEntry() - Reference has wrong type - ")+key);
      }
      return ptr;
   }
   MemoryRegionPtr getMemoryRegion(std::string key) {
      MemoryRegionPtr ptr(std::tr1::dynamic_pointer_cast<MemoryRegion>(getSharedData(key)));
      if (ptr == NULL) {
         throw MyException(std::string("DeviceDataBase::getSecurityEntry() - Reference has wrong type - ")+key);
      }
      return ptr;
   }
   TclScriptConstPtr getTclScript(std::string key) const {
      TclScriptPtr ptr(std::tr1::dynamic_pointer_cast<TclScript>(getSharedData(key)));
      if (ptr == NULL) {
         throw MyException(std::string("DeviceDataBase::getSecurityEntry() - Reference has wrong type - ")+key);
      }
      return ptr;
   }
   RegisterDescriptionConstPtr getRegisterDescription(std::string key) const {
      RegisterDescriptionConstPtr ptr(std::tr1::dynamic_pointer_cast<RegisterDescription>(getSharedData(key)));
      if (ptr == NULL) {
         throw MyException(std::string("DeviceDataBase::getRegisterDescription() - Reference has wrong type - ")+key);
      }
      return ptr;
   }
   FlashProgramConstPtr getFlashProgram(std::string key) const {
      FlashProgramPtr ptr(std::tr1::dynamic_pointer_cast<FlashProgram>(getSharedData(key)));
      if (ptr == NULL) {
         throw MyException(std::string("DeviceDataBase::getSecurityEntry() - Reference has wrong type - ")+key);
      }
      return ptr;
   }
   FlexNVMInfoConstPtr getFlexNVMInfo(std::string key) const {
      FlexNVMInfoPtr ptr(std::tr1::dynamic_pointer_cast<FlexNVMInfo>(getSharedData(key)));
      if (ptr == NULL) {
         throw MyException(std::string("DeviceDataBase::getSecurityEntry() - Reference has wrong type - ")+key);
      }
      return ptr;
   }
   DeviceDataBase() {
      Logging log("DeviceDataBase::DeviceDataBase()");
   };
   ~DeviceDataBase();
};

#endif /* DEVICEDATA_HPP_ */
