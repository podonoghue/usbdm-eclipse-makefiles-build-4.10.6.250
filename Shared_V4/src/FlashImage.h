/*! \file
   \brief Utility Routines for loading Freescale S-Record Files

   FlashImage.cpp

   \verbatim
   Copyright (C) 2008  Peter O'Donoghue

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
+========================================================================================
| 20 Oct 12 | Added DSC ELF file support                                    V4.10.3 - pgo
+----------------------------------------------------------------------------------------
|  7 Sep 12 | Added HCS12 support & device type check                       V4.10.0 - pgo
+----------------------------------------------------------------------------------------
|  1 Jun 12 | Changed to template format                                    V4.9.5  - pgo
+----------------------------------------------------------------------------------------
| 31 May 12 | Changed back to flat format                                   V4.9.5  - pgo
+----------------------------------------------------------------------------------------
| 17 Apr 12 | Added ELF format loading                                      V4.9.5  - pgo
+----------------------------------------------------------------------------------------
| 14 Feb 11 | Changed to dynamic memory allocation for buffer               V4.5    - pgo
+----------------------------------------------------------------------------------------
| 30 Jan 10 | 2.0.0 Changed to C++                                                  - pgo
|           |       Added paged memory support                                      - pgo
+----------------------------------------------------------------------------------------
|  8 Dec 09 | Started changes for paged files - incomplete                          - pgo
+----------------------------------------------------------------------------------------
|  ??    09 | Created                                                               - pgo
+========================================================================================
\endverbatim
 */
#ifndef _S_FILELOADER_H_
#define _S_FILELOADER_H_

#include <string>
#include <string.h>
#include <map>
#include <stdexcept>
#include "Common.h"
#include "USBDM_ErrorMessages.h"
#include "Log.h"
#include "Elf.h"
#include "Utils.h"

using namespace std;

//! Represents a memory image containing loaded file(s)
//!
template <class dataType> class FlashImageT {

public:
   class Enumerator;
   friend class Enumerator;
   static const uint32_t DataOffset =  (0x02000000);  // Offset used for DSC Data region

private:
   static const int      PageBitOffset =  (15-sizeof(dataType));  // 2**14 = 16K pages
   static const unsigned PageSize      =  (1U<<PageBitOffset);
   static const int      PageMask      =  (PageSize-1U);

   //! Represents a memory 'page'.
   //! Note: A page does not correspond to a flash page or sector!
   //!
   template <class elementType> class MemoryPage {

   public:
      elementType data[PageSize];           //!< Page of memory
      uint8_t     validBits[PageSize/8];    //!< Indicates valid bytes in data

   public:
      //=====================================================================
      //! Constructor
      //!
      MemoryPage() {
         memset(data, 0xFF, sizeof(data));
         memset(validBits, 0, sizeof(validBits));
      }

      //=====================================================================
      //! Indicates if a page[index] has been written to
      //!
      bool isValid(unsigned index) const {
         if (index >= PageSize) {
            throw runtime_error("Page index out of range");
         }
         return (validBits[index/8] & (1<<(index&0x7)))?true:false;
      }

      //=====================================================================
      //! Sets page[index] to value & marks as valid
      //!
      void setValue(unsigned index, elementType value) {
         if (index >= PageSize) {
            throw runtime_error("Page index out of range");
         }
         data[index]         = value;
         validBits[index/8] |= (1<<(index&0x7));
      }

      //=====================================================================
      //! Returns contents of page[index] if valid or 0xFF otherwise
      //!
      elementType getValue(unsigned index) {
         if (index >= PageSize) {
            throw runtime_error("Page index out of range");
         }
         if (!isValid(index)) {
            return 0xFF;
         }
         return data[index];
      }
   };

   //! Class to enumerate the occupied locations within the memory image
   //! @note may be invalidated by changes to the referenced image
public:
   class Enumerator {
   private:
      FlashImageT    &memoryImage;    //! Associated flash image
      uint32_t        address;        //! Current location in image

   public:
      //! Construct an enumerator positioned at the start of the flash image
      //!
      Enumerator(FlashImageT &memoryImage) :
         memoryImage(memoryImage),
         address(memoryImage.firstAllocatedAddress) {
      }

      //! Construct an enumerator positioned at a given starting address
      //!
      Enumerator(FlashImageT &memoryImage, uint32_t address) :
         memoryImage(memoryImage),
         address(address) {
         if (address < memoryImage.firstAllocatedAddress) {
            address = memoryImage.firstAllocatedAddress;
         }
      }

      //! Get the current location as a flat address
      //!
      uint32_t getAddress() const { return address; }

      //! Indicates if the current memory location is valid (occupied)
      //! @return \n
      //!        true  => current location is occupied
      //!        false => current location is unoccupied/unallocated
      bool isValid() const {
//         Logging::print("enumerator::isValid(0x%06X)\n", address);
         return memoryImage.isValid(address);
      }

      //! Sets the iterator to the given address
      //! @return \n
      //!        true  => current location is occupied
      //!        false => current location is unoccupied/unallocated
      bool setAddress(uint32_t addr) {
//         Logging::print("enumerator::isValid(0x%06X)\n", address);
         address = addr;
         if (!memoryImage.isValid(address))
            return nextValid();
         return true;
      }
      bool nextValid();
      void lastValid();
   };

private:
   std::map<uint32_t,MemoryPage<dataType>*>  memoryPages;            //!< Pointers to occupied memory pages
   bool                                      empty;                  //!< Memory is blank
   unsigned                                  firstAllocatedAddress;  //!< First used memory locations
   unsigned                                  lastAllocatedAddress;   //!< Last used memory locations
   uint16_t                                  lastPageNumAccessed;    //!< Page # of last page accessed
   MemoryPage<dataType>                     *lastMemoryPageAccessed; //!< Last page accessed
   unsigned                                  elementCount;           //!< Count of occupied bytes
   bool                                      littleEndian;           //!< Target is little-endian
   string                                    sourceFilename;         //!< Name of last file loaded
   string                                    sourcePath;             //!< Path of last file loaded

public:
   //=====================================================================
   //! Constructor - creates an empty Flash image
   //!
   FlashImageT() :
      empty(true),
      firstAllocatedAddress((unsigned )(-1)),
      lastAllocatedAddress(0),
      lastPageNumAccessed((uint16_t )(-1)),
      lastMemoryPageAccessed(NULL),
      elementCount(0),
      littleEndian(false) {

      initData();
   }

   //=====================================================================
   //! ~Constructor
   //!
   ~FlashImageT() {
      initData();
   }
   const char* get_pFlagsName(unsigned int flags);
   const char* get_ptTypeName(unsigned int type);

   //=====================================================================
   //! Initialises the memory to empty
   //!
   void initData(void) {
      // Initialise flash image to unused value
      typename std::map<uint32_t,MemoryPage<dataType>*>::iterator it = memoryPages.begin();
      while(it != memoryPages.end()){
         delete it->second;
         it++;
      }
      memoryPages.clear();
      empty                  = true;
      firstAllocatedAddress  = (unsigned )(-1);
      lastAllocatedAddress   = 0;
      lastPageNumAccessed    = (uint16_t )(-1);
      lastMemoryPageAccessed = NULL;
      elementCount           = 0;
      littleEndian           = false;
   }

   //=====================================================================
   //! Checks if the memory location is valid (has been written to)
   //!
   //! @param address - 32-bit memory address
   //!
   //! @return\n
   //!         true   => location has been previously written to \n
   //!         false  => location is invalid
   //!
   bool isValid(uint32_t address) {
      uint16_t pageNum;
      uint16_t offset;
      addressToPageOffset(address, pageNum, offset);
      MemoryPage<dataType> *memoryPage = getmemoryPage(pageNum);
      return (memoryPage != NULL) && (memoryPage->isValid(offset));
   }

   //=====================================================================
   //! Gets an enumerator for the memory
   //!
   Enumerator *getEnumerator() {
      return new Enumerator(*this);
   }

   //=====================================================================
   //! Check if image is entirely empty (never written to)
   //!
   //! @return true=>image is entirely empty,\n
   //!               image is not empty
   //!
   bool isEmpty() const {
      return empty;
   }

   //=====================================================================
   //! Prints representation of used memory to log file
   //!
   void printMemoryMap();

   //=====================================================================
   //! Returns an approximate count of occupied bytes
   //!
   unsigned getByteCount() const {
      return elementCount*sizeof(dataType);
   }

   //=====================================================================
   //! Get pathname of last file loaded
   //!
   const string & getSourcePathname() const {
      return sourcePath;
   }

   //=====================================================================
   //! Locate Page from page number
   //!
   //! @param   pageNum
   //!
   //! @return  memory page or NULL id not found
   //!
   MemoryPage<dataType> *getmemoryPage(uint32_t pageNum) {
      MemoryPage<dataType> *memoryPage;
      if ((pageNum == lastPageNumAccessed) && (lastMemoryPageAccessed != NULL)) {
         // Used cached copy
         memoryPage = lastMemoryPageAccessed;
      }
      else {
         typename std::map<uint32_t, MemoryPage<dataType> *>::iterator iter = memoryPages.find(pageNum);
         if (iter == memoryPages.end()) {
            memoryPage = NULL;
         }
         else {
            memoryPage = iter->second;
         }
         // Cache access
         lastMemoryPageAccessed  = memoryPage;
      }
      return memoryPage;
   }

   //=====================================================================
   //! Allocate page
   //!
   //! @param pageNum
   //!
   MemoryPage<dataType> *allocatePage(uint32_t pageNum) {
      MemoryPage<dataType> *memoryPage;

      memoryPage = getmemoryPage(pageNum);
      if (memoryPage == NULL) {
         Logging::print( "Allocating page #%2.2X [0x%06X-0x%06X]\n", pageNum, pageOffsetToAddress(pageNum, 0), pageOffsetToAddress(pageNum, PageSize-1));
         memoryPage = new MemoryPage<dataType>;
         memoryPages.insert(pair<const uint32_t, MemoryPage<dataType>*>(pageNum, memoryPage));
         // Update cache
         lastMemoryPageAccessed = memoryPage;
      }
      return memoryPage;
   }

   //=====================================================================
   //! Load S1-9 file
   //!
   //! @param filePath    - Path to file
   //! @param clearBuffer - Clear the buffer before loading
   //!
   //! @return - Error code
   //!
   USBDM_ErrorCode loadFile(const string &filePath, bool clearBuffer=true);

   //=====================================================================
   //! Obtain the value of a Flash memory location
   //!
   //! @param address - 32-bit memory address
   //!
   //! @return -dataType value (dummy value of 0xFF.. if unallocated address)
   //!
   dataType getValue(uint32_t address);

   //=====================================================================
   //! Set a Flash memory location
   //!
   //! @param address - 32-bit memory byte address
   //! @param value   - dataType value to write to image
   //!
   //! @note Allocates a memory location if necessary
   //!
   void setValue(uint32_t address, dataType value);

   //=====================================================================
   //! Dumps a memory range
   //!
   //! @param startAddress - 32-bit memory byte start address (inclusive)
   //! @param endAddress   - 32-bit memory byte end address (inclusive)
   //!
   void dumpRange(uint32_t startAddress, uint32_t endAddress);

   //=====================================================================
   //! Load data into image
   //!
   //! @param bufferSize    - size of data to load (in bytes)
   //! @param address       - address to load at
   //! @param data          - data to load
   //! @param dontOverwrite - true to prevent overwriting data
   //!
   //! @note This is only of use if dataType is not a byte
   //!
   USBDM_ErrorCode loadData(uint32_t        bufferSize,
                            uint32_t        address,
                            const dataType  data[],
                            bool            dontOverwrite = false);

   //=====================================================================
   //! Load data into Flash image from byte array
   //!
   //! @param bufferSize    - size of data to load (in bytes)
   //! @param address       - address to load at (word address)
   //! @param data          - data to load
   //! @param dontOverwrite - true to prevent overwriting data
   //!
   //! @note This is only of use if dataType is not a byte
   //!
   USBDM_ErrorCode loadDataBytes(uint32_t        bufferSize,
                                 uint32_t        address,
                                 const uint8_t   data[],
                                 bool            dontOverwrite = false);

private:
   uint32_t          targetToNative(uint32_t &);
   uint16_t          targetToNative(uint16_t &);
   int32_t           targetToNative(int32_t &);
   int16_t           targetToNative(int16_t &);

   void              fixElfHeaderSex(Elf32_Ehdr *elfHeader);
   void              printElfHeader(Elf32_Ehdr *elfHeader);
   void              printElfProgramHeader(Elf32_Phdr *programHeader);
   void              fixElfProgramHeaderSex(Elf32_Phdr *programHeader);
   USBDM_ErrorCode   loadElfBlock(FILE *fp, long fOffset, Elf32_Word size, Elf32_Addr addr);
   USBDM_ErrorCode   loadElfFile(const string &fileName);

   USBDM_ErrorCode   loadS1S9File(const string &fileName);

   //! Maps Address to PageNum:offset
   //!
   //! @param address - 32-bit address
   //! @param pageNum - page number portion of address
   //! @param offset  - offset within page
   //!
   //! @note - These values do NOT refer to the paging structure used by the target!
   //!
   static void addressToPageOffset(uint32_t address, uint16_t &pageNum, uint16_t &offset) {
      offset  = address & PageMask;
      pageNum = address >> PageBitOffset;
//      printf("%8.8X=>%2.2X:%4.4X\n", address, pageNum, offset);
   }

   //! Maps PageNum:offset to Address
   //!
   //! @param pageNum - page number portion of address
   //! @param offset  - offset within page
   //!
   //! @return 32-bit address
   //!
   //! @note - These values do NOT refer to the paging structure used by the target!
   //!
   static uint32_t pageOffsetToAddress(uint16_t pageNum, uint16_t offset) {
      if (offset>=PageSize)
         throw runtime_error("Page offset too large\n");
      return (pageNum << PageBitOffset) + offset;
   }
};

template <class dataType>
const char* FlashImageT<dataType>::get_ptTypeName(unsigned int type) {
   const char *names[] = {
         "PT_NULL"    ,
         "PT_LOAD"    ,
         "PT_DYNAMIC" ,
         "PT_INTERP"  ,
         "PT_NOTE"    ,
         "PT_SHLIB"   ,
         "PT_PHDR"    ,
   };
   if (type > sizeof(names)/sizeof(names[0])) {
      return "Unknown";
   }
   return names[type];
}

template <class dataType>
const char* FlashImageT<dataType>::get_pFlagsName(unsigned int flags) {
   static char buff[20];
   buff[0] = '\0';
   if (flags&PF_X) {
      strcat(buff,"PF_X|");
   }
   if (flags&PF_W) {
      strcat(buff,"PF_W|");
   }
   if (flags&PF_R) {
      strcat(buff,"PF_R|");
   }
   return buff;
}


//=====================================================================
//! Set a Flash memory location
//!
//! @param address - 32-bit memory address
//! @param value   - dataType value to write to image
//!
//! @note Allocates a memory location if necessary
//!
template <class dataType>
void FlashImageT<dataType>::setValue(uint32_t address, dataType value) {
   uint16_t offset;
   uint16_t pageNum;

   empty = false;
   addressToPageOffset(address, pageNum, offset);
   MemoryPage<dataType> *memoryPage = allocatePage(pageNum);
   if (!memoryPage->isValid(offset)) {
      // new location
      elementCount++;
   }
   memoryPage->setValue(offset, value);
   if (firstAllocatedAddress > address) {
      firstAllocatedAddress = address;
   }
   if (lastAllocatedAddress < address) {
      lastAllocatedAddress = address;
   }
}

/*! Convert a 32-bit unsigned number between Target and Native format
 *
 * @param value - value to convert
 *
 * @return - converted value
 */
template <class dataType>
uint32_t FlashImageT<dataType>::targetToNative(uint32_t &value) {
   if (littleEndian) {
      return value;
   }
   return ((value<<24)&0xFF000000) + ((value<<8)&0x00FF0000) +
          ((value>>8) &0x0000FF00) + ((value>>24)&0x000000FF);
}

/*! Convert a 16-bit unsigned number between Target and Native format
 *
 * @param value - value to convert
 *
 * @return - converted value
 */
template <class dataType>
uint16_t FlashImageT<dataType>::targetToNative(uint16_t &value) {
   if (littleEndian) {
      return value;
   }
   return ((value<<8)&0xFF00) + ((value>>8)&0x00FF);
}

/*! Convert a 32-bit signed number between Target and Native format
 *
 * @param value - value to convert
 *
 * @return - converted value
 */
template <class dataType>
int32_t FlashImageT<dataType>::targetToNative(int32_t &value) {
   if (littleEndian) {
      return value;
   }
   return ((value<<24)&0xFF000000) + ((value<<8)&0x00FF0000) +
          ((value>>8) &0x0000FF00) + ((value>>24)&0x000000FF);
}

/*! Convert a 16-bit signed number between Target and Native format
 *
 * @param value - value to convert
 *
 * @return - converted value
 */
template <class dataType>
int16_t FlashImageT<dataType>::targetToNative(int16_t &value) {
   if (littleEndian) {
      return value;
   }
   return ((value<<8)&0xFF00) + ((value>>8)&0x00FF);
}

//=====================================================================
//!  Dump the contents of a range of memory
//!
//! @param startAddress - start of range
//! @param endAddress   - end of range
//!
//!
template <class dataType>
void FlashImageT<dataType>::dumpRange(uint32_t startAddress, uint32_t endAddress) {
   uint32_t addr;
   uint32_t rangeEnd;

   Logging::print("Dump of [0x%06X-0x%06X]\n", startAddress, endAddress);
   Enumerator iter(*this, startAddress);
   if (!iter.isValid()) {
      iter.nextValid();
   }
   do {
      if (sizeof(dataType) == 1) {
         addr = iter.getAddress() & ~0xF;
         iter.lastValid();
         rangeEnd = iter.getAddress();
         Logging::print("        : 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n"
               "==========================================================\n");
         while (addr <= rangeEnd) {
            if (((addr & 0x000F) == 0) || (addr == startAddress))
               Logging::print("%8.8X:", addr);
            if (isValid(addr))
               Logging::print("%02X ", getValue(addr));
            else
               Logging::print("   ");
            if (((addr & 0x000F) == 0xF) || (addr == rangeEnd))
               Logging::print("\n");
            addr++;
         }
      }
      else {
         addr = iter.getAddress() & ~0xF;
         iter.lastValid();
         rangeEnd = iter.getAddress();
         Logging::print("        : 0    1    2    3    4    5    6    7\n"
               "==================================================\n");
         while (addr <= rangeEnd) {
            if (((addr & 0x0007) == 0) || (addr == startAddress))
               Logging::print("%8.8X:", addr);
            if (isValid(addr))
               Logging::print("%04X ", getValue(addr));
            else
               Logging::print("     ");
            if (((addr & 0x0007) == 0x7) || (addr == rangeEnd))
               Logging::print("\n");
            addr++;
         }
      }
   } while (iter.nextValid());
   Logging::print("\n\n");
}

//=====================================================================
//!   Load a Freescale S-record file into the buffer. \n
//!
//!   The buffer is cleared to 0xFFFF before loading.  Modified locations will
//!   have a non-0xFF upper byte so used locations can be differentiated. \n
//!
//! @param fileName         : Path of file to load
//!
//! @return error code see \ref USBDM_ErrorCode
//!
template <class dataType>
USBDM_ErrorCode FlashImageT<dataType>::loadS1S9File(const string &fileName) {
   char        *ptr;
   char         buffer[1024];
   uint32_t     addr;
   uint32_t     srecSize;
   uint8_t      checkSum;
   bool         fileRecognized = false;

   FILE *fp = fopen(fileName.c_str(), "rt");

   if (fp == NULL) {
      Logging::print("FlashImageT::MemorySpace::loadS1S9File(\"%s\") - Failed to open input file\n", fileName.c_str());
      return SFILE_RC_FILE_OPEN_FAILED;
   }
   Logging::print("FlashImageT::MemorySpace::loadS1S9File(\"%s\")\n", fileName.c_str());

   unsigned int lineNum  = 0;
   while (fgets(buffer, sizeof(buffer)-1, fp) != NULL) {
      lineNum++;
      //Logging::print("Input: %s",buffer);
      ptr = buffer;
      // Find first non-blank
      while ((*ptr == ' ') || (*ptr == '\t') || (*ptr == '\n') || (*ptr == '\r'))
         ptr++;
      // Check if S-record
      if ((*ptr != 'S') && (*ptr != 's')) {
         Logging::print("FlashImageT::MemorySpace::loadS1S9File() - illegal line #%5d-%s", lineNum, buffer);
         fclose(fp);
         if (fileRecognized) {
            return SFILE_RC_ILLEGAL_LINE;
         }
         else {
            return SFILE_RC_UNKNOWN_FILE_FORMAT;
         }
      }
      switch (*(ptr+1)) {
         case '0': // Information header
         case '7': // 32-bit start address
         case '8': // 24-bit start address
         case '9': // 16-bit start address
            // Discard S0, S7, S8 & S9 records
            continue;
         case '1':
            // S1 = 16-bit address, data record
            ptr +=2; // Skip 'S1'
            srecSize = hex2ToDecimal( &ptr );
            addr = hex4ToDecimal( &ptr );
            checkSum = (uint8_t)srecSize + (uint8_t)(addr>>8) + (uint8_t)addr;
            srecSize -= 3; // subtract 3 from byte count (srecSize + 2 addr bytes)
            //Logging::print("(%2.2X)%4.4lX:\n",srecSize,addr);
            break;
         case '2':
            // S2 = 24-bit address, data record
            ptr +=2; // Skip 'S2'
            srecSize = hex2ToDecimal( &ptr );
            addr = hex6ToDecimal( &ptr );
            checkSum = (uint8_t)srecSize + (uint8_t)(addr>>16) + (uint8_t)(addr>>8) + (uint8_t)addr;
            srecSize -= 4; // subtract 4 from byte count (srecSize + 3 addr bytes)
            //Logging::print("srecSize=0x%02X, addr=0x%06X\n",srecSize,addr);
            break;
         case '3':
            // S3 32-bit address, data record
            ptr +=2; // Skip 'S3'
            srecSize = hex2ToDecimal( &ptr );
            addr = hex8ToDecimal( &ptr );
            checkSum = (uint8_t)srecSize + (uint8_t)(addr>>24) + (uint8_t)(addr>>16) + (uint8_t)(addr>>8) + (uint8_t)addr;
            srecSize -= 5; // subtract 5 from byte count (srecSize + 4 addr bytes)
//            Logging::print("S3: srecSize=0x%02X, addr=0x%08X, initial chk=0x%02X\n", srecSize, addr, checkSum);
            break;
         default:
            Logging::print("FlashImageT::MemorySpace::loadS1S9File() - illegal line #%5d-%s", lineNum, buffer);
            fclose(fp);
            if (fileRecognized) {
               return SFILE_RC_ILLEGAL_LINE;
            }
            else {
               return SFILE_RC_UNKNOWN_FILE_FORMAT;
            }
      }
      if (sizeof(dataType) == 1) {
         while (srecSize>0) {
            uint8_t data;
            data = hex2ToDecimal( &ptr );
            checkSum += (uint8_t)data;
            this->setValue(addr++, (uint8_t)data);
            srecSize--;
            //         Logging::print("%02X",data);
         }
      }
      else {
         while (srecSize>0) {
            uint16_t data1, data2;
            data1 = hex2ToDecimal( &ptr );
            checkSum += (uint8_t)data1;
            data2 = hex2ToDecimal( &ptr );
            checkSum += (uint8_t)data2;
            this->setValue(addr++, (uint16_t)((data2<<8)+data1)); // Assumes little-endian format
            srecSize -= 2;
   //         Logging::print("%02X",data);
         }
      }
      // Get checksum from record
      uint8_t data = hex2ToDecimal( &ptr );
      if ((uint8_t)~checkSum != data) {
         Logging::print("FlashImageT::MemorySpace::loadS1S9File() - illegal line #%5d:\n%s", lineNum, buffer);
         Logging::print("FlashImageT::MemorySpace::loadS1S9File() checksum error, Checksum=0x%02X, "
               "Calculated Checksum=0x%02X\n",
               data, (uint8_t)~checkSum);
         fclose(fp);
         return SFILE_RC_CHECKSUM;
      }
      fileRecognized = true; // Read at least 1 record - assume it's a SREC file
      //Logging::print("\n");
   }
   fclose(fp);
//   Logging::print("FlashImageT::MemorySpace::loadS1S9File()\n");
//   printMemoryMap();
   return SFILE_RC_OK;
}

//=====================================================================
//!   Load a ELF block into the buffer. \n
//!
//!   The buffer is cleared to 0xFFFF before loading.  Modified locations will
//!   have a non-0xFF upper byte so used locations can be differentiated. \n
//!
//! @param fp            : Open file pointer
//! @param fOffset       : Offset to block in file
//! @param size          : Size of block in bytes
//! @param addr          : Bytes address to load block
//!
template <class dataType>
USBDM_ErrorCode FlashImageT<dataType>::loadElfBlock(FILE       *fp,
                                                    long        fOffset,
                                                    Elf32_Word  size,
                                                    Elf32_Addr  addr) {
#if TARGET == MC56F80xx
   // DSC image uses word addresses
   addr /= 2;
#endif
   if (size == 0) {
      Logging::print("FlashImageT::loadElfBlock(): [empty]\n");
   }
   else {
#if TARGET == MC56F80xx
      Logging::print("FlashImageT::loadElfBlock(): [0x%08X..0x%08X]\n", addr, addr+size/2-1);
#else
      Logging::print("FlashImageT::loadElfBlock(): [0x%08X..0x%08X]\n", addr, addr+size-1);
#endif
   }
   fseek(fp, fOffset, SEEK_SET);
   while (size>0) {
      uint8_t buff[1000];
      Elf32_Word blockSize = size;
      if (blockSize > sizeof(buff)) {
         blockSize = sizeof(buff);
      }
      size_t sz;
      if ((sz=fread(buff, 1, blockSize, fp)) != blockSize) {
         Logging::print("FlashImageT::MemorySpace::loadElfFile() - Failed - Undersize read of Block (Expected %d, read %d)\n", blockSize, sz);
         return SFILE_RC_ELF_FORMAT_ERROR;
      }
//#if TARGET == MC56F80xx
//      printDump(buff, blockSize, addr, WORD_ADDRESS|WORD_DISPLAY);
//#else
//      printDump(buff, blockSize, addr, BYTE_ADDRESS);
//#endif
      for (unsigned index=0; index<blockSize; ) {
         uint16_t value;
#if TARGET == MC56F80xx
         value  = buff[index++];
         value += buff[index++]<<8;
#else
         value = buff[index++];
#endif
         this->setValue(addr++, value);
      }
      size -= blockSize;
   }
   return SFILE_RC_OK;
}

//=====================================================================
//! Print ELF Header
//!
//! @param elfHeader -  ELF header to print
//!
template <class dataType>
void FlashImageT<dataType>::printElfHeader(Elf32_Ehdr *elfHeader) {
   Logging::print("e_type      = 0x%04X\n"
         "e_machine   = 0x%04X\n"
         "e_version   = 0x%08X\n"
         "e_entry     = 0x%08X\n"
         "e_phoff     = 0x%08X\n"
         "e_shoff     = 0x%08X\n"
         "e_flags     = 0x%08X\n"
         "e_ehsize    = 0x%04X\n"
         "e_phentsize = 0x%04X\n"
         "e_phnum     = 0x%04X\n"
         "e_shentsize = 0x%04X\n"
         "e_shnum     = 0x%04X\n"
         "e_shstrndx  = 0x%04X\n",
         elfHeader->e_type,
         elfHeader->e_machine,
         elfHeader->e_version,
         elfHeader->e_entry,
         elfHeader->e_phoff,
         elfHeader->e_shoff,
         elfHeader->e_flags,
         elfHeader->e_ehsize,
         elfHeader->e_phentsize,
         elfHeader->e_phnum,
         elfHeader->e_shentsize,
         elfHeader->e_shnum,
         elfHeader->e_shstrndx );
}

//=====================================================================
//! Convert fields in ELF header to native format
//!
//! @param elfHeader -  ELF header to convert
//!
template <class dataType>
void FlashImageT<dataType>::fixElfHeaderSex(Elf32_Ehdr *elfHeader) {
   // Convert to native format
   elfHeader->e_type      = targetToNative(elfHeader->e_type     );
   elfHeader->e_machine   = targetToNative(elfHeader->e_machine  );
   elfHeader->e_version   = targetToNative(elfHeader->e_version  );
   elfHeader->e_entry     = targetToNative(elfHeader->e_entry    );
   elfHeader->e_phoff     = targetToNative(elfHeader->e_phoff    );
   elfHeader->e_shoff     = targetToNative(elfHeader->e_shoff    );
   elfHeader->e_flags     = targetToNative(elfHeader->e_flags    );
   elfHeader->e_ehsize    = targetToNative(elfHeader->e_ehsize   );
   elfHeader->e_phentsize = targetToNative(elfHeader->e_phentsize);
   elfHeader->e_phnum     = targetToNative(elfHeader->e_phnum    );
   elfHeader->e_shentsize = targetToNative(elfHeader->e_shentsize);
   elfHeader->e_shnum     = targetToNative(elfHeader->e_shnum    );
   elfHeader->e_shstrndx  = targetToNative(elfHeader->e_shstrndx );
}

//=====================================================================
//! Print ELF Program Header
//!
//! @param programHeader -  ELF Program header to print
//!
template <class dataType>
void FlashImageT<dataType>::printElfProgramHeader(Elf32_Phdr *programHeader) {
   Logging::print("===================\n"
         "p_type   = 0x%08X(%s)\n"
         "p_offset = 0x%08X\n"
         "p_vaddr  = 0x%08X\n"
         "p_paddr  = 0x%08X\n"
         "p_filesz = 0x%08X\n"
         "p_memsz  = 0x%08X\n"
         "p_flags  = 0x%08X (%s)\n"
         "p_align  = 0x%08X\n",
         programHeader->p_type, get_ptTypeName(programHeader->p_type),
         programHeader->p_offset,
         programHeader->p_vaddr ,
         programHeader->p_paddr ,
         programHeader->p_filesz,
         programHeader->p_memsz ,
         programHeader->p_flags , get_pFlagsName(programHeader->p_flags),
         programHeader->p_align
   );
}

//=====================================================================
//! Convert fields to native format
//!
//! @param elfHeader -  ELF Program header to convert
//!
template <class dataType>
void FlashImageT<dataType>::fixElfProgramHeaderSex(Elf32_Phdr *elfHeader) {
   elfHeader->p_type    = targetToNative(elfHeader->p_type  );
   elfHeader->p_offset  = targetToNative(elfHeader->p_offset);
   elfHeader->p_vaddr   = targetToNative(elfHeader->p_vaddr );
   elfHeader->p_paddr   = targetToNative(elfHeader->p_paddr );
   elfHeader->p_filesz  = targetToNative(elfHeader->p_filesz);
   elfHeader->p_memsz   = targetToNative(elfHeader->p_memsz );
   elfHeader->p_flags   = targetToNative(elfHeader->p_flags );
   elfHeader->p_align   = targetToNative(elfHeader->p_align );
}

//=====================================================================
//!   Load a ELF file into the buffer. \n
//!
//! @param filePath         : Path of file to load
//!
//! @return error code see \ref USBDM_ErrorCode
//!
template <class dataType>
USBDM_ErrorCode FlashImageT<dataType>::loadElfFile(const string &filePath) {
   FILE *fp = fopen(filePath.c_str(), "rb");
   if (fp == NULL) {
      Logging::print("FlashImageT::MemorySpace::loadElfFile(\"%s\") - Failed to open input file\n", filePath.c_str());
      return SFILE_RC_FILE_OPEN_FAILED;
   }
   Logging::print("FlashImageT::MemorySpace::loadElfFile(\"%s\")\n", filePath.c_str());

   Elf32_Ehdr elfHeader;
   if (fread(&elfHeader, 1, sizeof(elfHeader), fp) != sizeof(elfHeader)) {
      return SFILE_RC_ELF_FORMAT_ERROR;
   }
//   Logging::print("FlashImageT::MemorySpace::loadElfFile() - \n");
//   printElfHeader(&elfHeader);

   if ((elfHeader.e_ident[EI_MAG0] != ELFMAG0V) ||(elfHeader.e_ident[EI_MAG1] != ELFMAG1V) ||
       (elfHeader.e_ident[EI_MAG2] != ELFMAG2V) ||(elfHeader.e_ident[EI_MAG3] != ELFMAG3V) ||
       (elfHeader.e_ident[EI_CLASS] != ELFCLASS32)) {
      Logging::print("FlashImageT::MemorySpace::loadElfFile() - Failed - Invalid  format\n", filePath.c_str());
      fclose(fp);
      return SFILE_RC_UNKNOWN_FILE_FORMAT;
   }
   littleEndian = elfHeader.e_ident[EI_DATA] == ELFDATA2LSB;
   fixElfHeaderSex(&elfHeader);

//   Logging::print("FlashImageT::MemorySpace::loadElfFile() - elfHeader.e_machine = 0x%X(%d) \n", elfHeader.e_machine, elfHeader.e_machine);
//   printElfHeader(&elfHeader);

#if TARGET == HCS08
   if (elfHeader.e_machine != EM_68HC08) {
      return SFILE_RC_ELF_FORMAT_ERROR;
   }
#elif TARGET == HCS12
   if (elfHeader.e_machine != EM_68HC12) {
      return SFILE_RC_ELF_FORMAT_ERROR;
   }
#elif TARGET == ARM
   if (elfHeader.e_machine != EM_ARM) {
      return SFILE_RC_ELF_WRONG_TARGET;
   }
#elif (TARGET == CFV1) || (TARGET == CFVx)
   if (elfHeader.e_machine != EM_68K) {
      return SFILE_RC_ELF_FORMAT_ERROR;
   }
#elif TARGET == MC56F80xx
   if (elfHeader.e_machine != EM_56K) {
      return SFILE_RC_ELF_WRONG_TARGET;
   }
#else
   return SFILE_RC_UNKNOWN_FILE_FORMAT;
#endif
   if ((elfHeader.e_type != ET_EXEC) || (elfHeader.e_phoff == 0) || (elfHeader.e_phentsize == 0) || (elfHeader.e_phnum == 0)) {
      Logging::print("FlashImageT::MemorySpace::loadElfFile() - Failed - Invalid  format\n", filePath.c_str());
      fclose(fp);
      return SFILE_RC_ELF_FORMAT_ERROR;
   }
   fseek(fp, elfHeader.e_phoff, SEEK_SET);
   for(Elf32_Half entry=0; entry<elfHeader.e_phnum; entry++) {
      Elf32_Phdr programHeader;
      fseek(fp, elfHeader.e_phoff+entry*elfHeader.e_phentsize, SEEK_SET);
      size_t sz;
      if ((sz=fread(&programHeader, 1, sizeof(programHeader), fp)) != sizeof(programHeader)) {
         Logging::print("FlashImageT::MemorySpace::loadElfFile() - Failed - Undersize read of Header (Expected %d, read %d)\n", sizeof(programHeader), sz);
         return SFILE_RC_ELF_FORMAT_ERROR;
      }
      fixElfProgramHeaderSex(&programHeader);
      if ((programHeader.p_type == PT_LOAD) && (programHeader.p_filesz > 0)) {
//         printElfProgramHeader(&programHeader);
#if (TARGET == RS08) || (TARGET == HCS08) || (TARGET == HCS12) || (TARGET == MC56F80xx)
         // These targets use the virtual address as the paged address
         if (loadElfBlock(fp, programHeader.p_offset, programHeader.p_filesz, programHeader.p_vaddr) != SFILE_RC_OK) {
            return SFILE_RC_ELF_FORMAT_ERROR;
         }
#else
         // These targets load at the physical address (VADDR is RAM copy destination)
         if (loadElfBlock(fp, programHeader.p_offset, programHeader.p_filesz, programHeader.p_paddr) != SFILE_RC_OK) {
            return SFILE_RC_ELF_FORMAT_ERROR;
         }
#endif
      }
   }
   fclose(fp);
//   Logging::print("FlashImageT::MemorySpace::loadElfFile()\n");
//   printMemoryMap();
   return SFILE_RC_OK;
}

//=====================================================================
//!   Load a S19 or ELF file into the buffer. \n
//!
//! @param filePath      : Path of file to load
//! @param clearBuffer   : Clear buffer before loading
//!
//! @return error code see \ref USBDM_ErrorCode
//!
template <class dataType>
USBDM_ErrorCode  FlashImageT<dataType>::loadFile(const string &filePath,
                                                 bool          clearBuffer) {
   sourceFilename = "";
   sourcePath     = "";

   if (clearBuffer) {
      initData();
   }
   Logging::print("FlashImageT::MemorySpace::loadFile(\"%s\")\n", filePath.c_str());

   // Try ELF Format
   USBDM_ErrorCode rc = loadElfFile(filePath);
   if (rc == SFILE_RC_UNKNOWN_FILE_FORMAT) {
      // Try SREC Format if not recognized as ELF
      rc = loadS1S9File(filePath);
   }
   //   Logging::print("FlashImageT::loadFile()\n"
   //         "Lowest used Address \t = 0x%4.4X\n"
   //         "Highest used Address\t = 0x%4.4X\n",
   //         flashImageDescription->firstAddr,  // first non-0xFF address
   //         flashImageDescription->lastAddr    // last non-0xFF address
   //         );
   //
   if (rc == SFILE_RC_OK) {
      sourcePath      = filePath;
      sourceFilename  = filePath; //!Todo Fix
   }
   return rc;
}

//=====================================================================
//! Prints a summary of the Flash memory allocated/used.
//!
template <class dataType>
void FlashImageT<dataType>::printMemoryMap() {
   Enumerator *enumerator = getEnumerator();
   Logging::print("FlashImageT::MemorySpace::printMemoryMap()\n");
   while (enumerator->isValid()) {
      // Start address of block
      uint32_t startBlock = enumerator->getAddress();
      // Find end of block
      enumerator->lastValid();
      uint32_t endBlock = enumerator->getAddress();
      Logging::print("Memory Block[0x%06X...0x%06X]\n", startBlock, endBlock);
      // Move to start of next occupied range
      enumerator->nextValid();
   }
   delete enumerator;
}

//=====================================================================
//! Obtain the value of a Flash memory location
//!
//! @param address - 32-bit memory address
//!
//! @return - dataType value (dummy value of 0xFF.. is unallocated address)
//!
template <class dataType>
dataType FlashImageT<dataType>::getValue(uint32_t address) {
   uint16_t         offset;
   uint16_t         pageNum;
   MemoryPage<dataType> *memoryPage;
   addressToPageOffset(address, pageNum, offset);
   memoryPage = getmemoryPage(pageNum);
   if (memoryPage == NULL)
      return 0xFF;
   else
      return memoryPage->getValue(offset);
}

//=====================================================================
//! Load data into Flash image
//!
//! @param bufferSize    - size of data to load (in dataType)
//! @param address       - address to load at
//! @param data          - data to load
//! @param dontOverwrite - produce error if overwriting existing data
//!
template <class dataType>
USBDM_ErrorCode FlashImageT<dataType>::loadData(uint32_t       bufferSize,
                                                uint32_t       address,
                                                const dataType data[],
                                                bool           dontOverwrite) {
   uint32_t bufferAddress;

   //   Logging::print("FlashImageT::loadData(0x%04X...0x%04X)\n", address, address+bufferSize-1);
   bufferAddress = 0;
   while (bufferAddress < bufferSize){
//      if (!allocatePage(address)) {
//         Logging::print("loadData() - Address is too large = 0x%08X > 0x%08lX\n",
//               address, MAX_SFILE_ADDRESS);
//
//         return SFILE_RC_ADDRESS_TOO_LARGE;
//      }
      if (!this->isValid(address) || !dontOverwrite) {
         this->setValue(address, data[bufferAddress]);
      }
      address++;
      bufferAddress++;
   }
//   printMemoryMap();
   return SFILE_RC_OK;
}

//=====================================================================
//! Load data into Flash image from byte array
//!
//! @param bufferSize    - size of data to load (in bytes)
//! @param address       - address to load at (byte/word address)
//! @param data          - data to load
//! @param dontOverwrite - true to prevent overwriting data
//!
//! @note This is only of use if dataType is not a byte
//!
template <class dataType>
USBDM_ErrorCode FlashImageT<dataType>::loadDataBytes(uint32_t        bufferSize,
                                                     uint32_t        address,
                                                     const uint8_t   data[],
                                                     bool            dontOverwrite) {

//    Logging::print("FlashImageT::loadData(0x%04X...0x%04X)\n", address, address+bufferSize-1);
   if (sizeof(dataType) == 1) {
      // Copy directly to buffer
      uint32_t bufferAddress = 0;
      while (bufferAddress < bufferSize) {
         unsigned value;
         value = data[bufferAddress++];
         if (!this->isValid(address) || !dontOverwrite) {
            this->setValue(address, value);
         }
//         Logging::print("FlashImageT::loadDataBytes() - image[0x%06X] <= 0x%04X\n", address, value);
         address++;
      }
   }
   else {
      if ((bufferSize&0x01) != 0) {
         Logging::print("FlashImageT::loadDataBytes() - Error: Odd buffer size\n");
         return PROGRAMMING_RC_ERROR_INTERNAL_CHECK_FAILED;
      }
      // Convert to little-endian native & copy to buffer
      uint32_t bufferAddress = 0;
      while (bufferAddress < bufferSize) {
         unsigned value;
         value = data[bufferAddress++];
         value = (data[bufferAddress++]<<8)+value;
//         Logging::print("FlashImageT::loadDataBytes() - image[0x%06X] <= 0x%04X\n", address, value);
         if (!this->isValid(address) || !dontOverwrite) {
            this->setValue(address, value);
         }
//         Logging::print("FlashImageT::loadDataBytes() - image[0x%06X] <= 0x%04X\n", address, value);
         address++;
      }
   }
   return BDM_RC_OK;
}

//==============================================================================================
//==============================================================================================
//==============================================================================================

//=====================================================================
//! Advance to next occupied flash location
//!
//! @return \n
//!        true  => advanced to next occupied location
//!        false => no occupied locations remain, enumerator is left at last \e unoccupied location
//!
template <class dataType>
bool FlashImageT<dataType>::Enumerator::nextValid() {
   const MemoryPage<dataType> *memoryPage = NULL;
   uint16_t pageNum, offset;
//   Logging::print("enumerator::nextValid(start=0x%06X)\n", address);
   address++;
   do {
      addressToPageOffset(address, pageNum, offset);
//      Logging::print("enumerator::nextValid() checking 0x%06X)\n", address);

      // At start of page or haven't checked this page yet
      if ((offset == 0) || (memoryPage == NULL)) {
         typename map<uint32_t, MemoryPage<dataType> *>::iterator iter = memoryImage.memoryPages.find(pageNum);
         if (iter == memoryImage.memoryPages.end()) {
            memoryPage = NULL;
         }
         else {
            memoryPage = iter->second;
         }
      }
      if (memoryPage == NULL) {
         // Unallocated page - move to start of next page
//         Logging::print("enumerator::nextValid(a=0x%06X) - skipping unallocated page #0x%X\n", address, pageNum);
         address += PageSize;
         address &= ~PageMask;
         if (address > memoryImage.lastAllocatedAddress) {
//            address = memoryImage.lastAllocatedAddress;
//            Logging::print("enumerator::nextValid(end  =0x%06X), no remaining valid addresses\n", address);
            return false;
         }
         continue;
      }
      // Check if valid byte in page
      if (memoryPage->isValid(offset)) {
//         Logging::print("enumerator::nextValid(end  =0x%06X)\n", address);
         return true;
      }
      address++;
   } while (1);
   return false;
}

//=====================================================================
//! Advance location to just before the next unoccupied flash location or page boundary
//! Assumes current location is occupied.
//!
//! @return \n
//!        true  => advanced to last occupied location or just before a page boundary
//!        false => no unoccupied locations remain, enumerator is advanced to last occupied location
//!
template <class dataType>
void FlashImageT<dataType>::Enumerator::lastValid() {
   uint16_t pageNum, offset;
//   Logging::print("enumerator::lastValid(start=0x%06X)\n", address);
   addressToPageOffset(address, pageNum, offset);
   typename map<uint32_t, MemoryPage<dataType> *>::iterator iter = memoryImage.memoryPages.find(pageNum);
   if (iter == memoryImage.memoryPages.end()) {
//      Logging::print("enumerator::lastValid(end=0x%06X), start address not allocated\n", address);
      return;
   }
   MemoryPage<dataType> *memoryPage = iter->second;
   do {
//      Logging::print("enumerator::lastValid() checking 0x%06X)\n", address);
      if (address == memoryImage.lastAllocatedAddress) {
//         Logging::print("enumerator::lastValid(end=0x%06X), end of memory\n", address);
         return;
      }

      addressToPageOffset(address, pageNum, offset);

      // Check if at page boundary or probing one ahead fails
      if ((offset == PageSize-1) || !memoryPage->isValid(++offset)) {
//         Logging::print("enumerator::lastValid(end=0x%06X)\n", address);
         return;
      }
     address++;
   } while (1);
}

#if (TARGET == MC56F80xx)
typedef FlashImageT<uint16_t> FlashImage;
#else
typedef FlashImageT<uint8_t> FlashImage;
#endif

#endif // _S_FILELOADER_H_
