/*
 * gdbHandler.cpp
 *
 *  Created on: 06/03/2011
 *      Author: podonoghue
\verbatim
Change History
-==================================================================================
| 16 Nov 2013 | Changed maskisr function                                      - pgo
| 16 Nov 2013 | Changed monitor command handling                              - pgo
|  9 Nov 2013 | Changed default memory access size to 32-bit (+intelligent)   - pgo
| 31 Mar 2013 | Updated gdbLoop so that break updates status promptly         - pgo
| 23 Apr 2012 | Created                                                       - pgo
+==================================================================================
\endverbatim
 */
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <string>
#include "Common.h"
#include "Log.h"
#include "Utils.h"
#include "signals.h"
#include "Names.h"
//#include "wxPlugin.h"
#include "FindWindow.h"

using namespace std;

#ifndef TARGET
#error "Define target"
#endif

#include "USBDM_API.h"
#if (TARGET == ARM)
#include "ARM_Definitions.h"
#endif

#include "TargetDefines.h"

#include "DeviceData.h"
#include "FlashImage.h"
#include "FlashProgramming.h"

#include "tclInterface.h"

#include "GdbHandler.h"
#include "GdbBreakpoints.h"
#include "GdbMiscellaneous.h"

#if TARGET == CFV1
#define USBDM_ReadPC(x)                      USBDM_ReadCReg(CFV1_CRegPC, x);
#define USBDM_WritePC(x)                     USBDM_WriteCReg(CFV1_CRegPC, x);
#define USBDM_ReadSP(x)                      USBDM_ReadCReg(CFV1_CRegSP, x);
#define USBDM_WriteSP(x)                     USBDM_WriteCReg(CFV1_CRegSP, x);
#define USBDM_ReadSR(x)                      USBDM_ReadCReg(CFV1_CRegSR, x);
#define USBDM_WriteSR(x)                     USBDM_WriteCReg(CFV1_CRegSR, x);
#elif TARGET == CFVx
#define USBDM_ReadPC(x)                      USBDM_ReadCReg(CFVx_CRegPC, x);
#define USBDM_WritePC(x)                     USBDM_WriteCReg(CFVx_CRegPC, x);
#define USBDM_ReadSP(x)                      USBDM_ReadCReg(CFVx_CRegSP, x);
#define USBDM_WriteSP(x)                     USBDM_WriteCReg(CFVx_CRegSP, x);
#define USBDM_ReadSR(x)                      USBDM_ReadCReg(CFVx_CRegSR, x);
#define USBDM_WriteSR(x)                     USBDM_WriteCReg(CFVx_CRegSR, x);
#elif TARGET == ARM
#define USBDM_ReadPC(x)                      USBDM_ReadReg(ARM_RegPC, x);
#define USBDM_WritePC(x)                     USBDM_WriteReg(ARM_RegPC, x);
#define USBDM_ReadSP(x)                      USBDM_ReadReg(ARM_RegSP, x);
#define USBDM_WriteSP(x)                     USBDM_WriteReg(ARM_RegSP, x);
#define USBDM_ReadSR(x)                      USBDM_ReadReg(ARM_RegSR, x);
#define USBDM_WriteSR(x)                     USBDM_WriteReg(ARM_RegSR, x);
#else
#error "Unhandled TARGET"
#endif

#if TARGET==CFV1
#define TARGET_TYPE T_CFV1
#elif TARGET==CFVx
#define TARGET_TYPE T_CFVx
#elif TARGET==ARM
#define TARGET_TYPE T_ARM
#else
#error "Unhandled case"
#endif

enum RunState {halted, stepping, running, breaking};

static GdbInOut        *gdbInOut                     = NULL;
static RunState         runState                     = halted;
static DeviceData       deviceData;
static bool             maskInterruptsWhenStepping   = true;

static GdbTargetStatus gdbTargetStatus = T_UNKNOWN;

static void reportLocation(char mode, int reason);
USBDM_ErrorCode (*gdbCallBackPtr)(const char *msg, GdbMessageLevel level, USBDM_ErrorCode rc);

/*!  Writes status message in 'printf' manner
 *
 *   @param level  - Debug level
 *   @param rc     - Error code associated with message
 *   @param format - Print control string
 *   @param ...    - Argument list
 *
 *   @return Modified error code
 *
 *   @note assumes BDM_RC_OK error code (i.e. no error)
 */
USBDM_ErrorCode reportGdbPrintf(GdbMessageLevel level, USBDM_ErrorCode rc, const char *format, ...) {
  char buff[200];
  va_list list;
  va_start(list, format);
  vsnprintf(buff, sizeof(buff), format, list);

  if (gdbCallBackPtr != NULL) {
     return (*gdbCallBackPtr)(buff, level, rc);
  }
  return BDM_RC_OK;
}

/*!  Writes status message in 'printf' manner
 *
 *   @param level  - Debug level
 *   @param format - Print control string
 *   @param ...    - Argument list
 *
 *   @return Modified error code
 *
 *   @note assumes BDM_RC_OK error code (i.e. no error)
 */
USBDM_ErrorCode reportGdbPrintf(GdbMessageLevel level, const char *format, ...) {
  char buff[200];
  va_list list;
  va_start(list, format);
  vsnprintf(buff, sizeof(buff), format, list);
  if (gdbCallBackPtr != NULL) {
     return (*gdbCallBackPtr)(buff, level, BDM_RC_OK);
  }
  return BDM_RC_OK;
}

/*!  Writes status message in 'printf' manner
 *
 *   @param format - Print control string
 *   @param ...    - Argument list
 *
 *   @return Modified error code
 *
 *   @note assumes BDM_RC_OK error code (i.e. no error)
 *   @note assumed M_BORINGINFO interest level
 */
USBDM_ErrorCode reportGdbPrintf(const char *format, ...) {
   char buff[200];
   va_list list;
   va_start(list, format);
   vsnprintf(buff, sizeof(buff), format, list);

   if (gdbCallBackPtr != NULL) {
      return (*gdbCallBackPtr)(buff, M_BORINGINFO, BDM_RC_OK);
   }
   return BDM_RC_OK;
}

inline uint16_t swap16(uint16_t data) {
   return ((data<<8)&0xFF00) + ((data>>8)&0xFF);
}
inline uint32_t swap32(uint32_t data) {
   return ((data<<24)&0xFF000000) + ((data<<8)&0xFF0000) + ((data>>8)&0xFF00) + ((data>>24)&0xFF);
}
inline uint16_t unchanged16(uint16_t data) {
   return data;
}
inline uint32_t unchanged32(uint32_t data) {
   return data;
}

#if (TARGET == ARM)
#define targetToNative16(x)    unchanged16(x) // Target to PC
#define targetToNative32(x)    unchanged32(x) // Target to PC
#define nativeToTarget16(x)    unchanged16(x) // PC to target
#define nativeToTarget32(x)    unchanged32(x) // PC to target
#define bigendianToTarget16(x) swap16(x)      // Big-endian to Target
#define bigendianToTarget32(x) swap32(x)      // Big-endian to Target

#else
#define targetToNative16(x)    swap16(x)      // Target to PC
#define targetToNative32(x)    swap32(x)      // Target to PC
#define nativeToTarget16(x)    swap16(x)      // PC to target
#define nativeToTarget32(x)    swap32(x)      // PC to target
#define bigendianToTarget16(x) unchanged16(x) // Big-endian to Target
#define bigendianToTarget32(x) unchanged32(x) // Big-endian to Target

#endif

// Note - the following assume bigendian
inline bool hexToInt(char ch, int *value) {
   if ((ch >= '0') && (ch <= '9')) {
      *value = (ch - '0');
      return true;
   }
   if ((ch >= 'a') && (ch <= 'f')) {
      *value = (ch - 'a' + 10);
      return true;
   }
   if ((ch >= 'A') && (ch <= 'F')) {
      *value = (ch - 'A' + 10);
      return true;
   }
   return false;
}

inline bool hexToInt32(const char *ch, unsigned long *value) {
   *value = 0;
   for (int i=0; i<8; i++) {
      int temp;
      if (!hexToInt(*ch++, &temp))
         return false;
      *value *= 16;
      *value += temp;
   }
   return true;
}

inline long hexToInt16(const char *ch, unsigned long *value) {
   *value = 0;
   for (int i=0; i<4; i++) {
      int temp;
      if (!hexToInt(*ch++, &temp))
         return false;
      *value *= 16;
      *value += temp;
   }
   return true;
}

inline long hexToInt8(const char *ch, unsigned long *value) {
   *value = 0;
   for (int i=0; i<2; i++) {
      int temp;
      if (!hexToInt(*ch++, &temp))
         return false;
      *value *= 16;
      *value += temp;
   }
   return true;
}

//! Description of currently selected device
//!
static DeviceData deviceOptions;

//! Flash image for programming
//!
static FlashImage *flashImage = NULL;

//! Report status to GDB ("O...")
//!
//! @param s          - string describing status
//!
void reportStatusToGdb(const char *s, int size=-1) {
   LOGGING_Q;
   gdbInOut->sendGdbHexString("O", s, size);
}

//!
//! Create XML description of current device memory map in GDB expected format
//!
//! @param buffer     - location to return address of static buffer initialised.
//! @param bufferSize - size of buffer data
//!
static void createMemoryMapXML(const char **buffer, unsigned *bufferSize) {
   LOGGING_Q;
   // Prefix for memory map XML
   static const char xmlPrefix[] =
      "<?xml version=\"1.0\"?>\n"
      "<!DOCTYPE memory-map\n"
      "   PUBLIC \"+//IDN gnu.org//DTD GDB Memory Map V1.0//EN\"\n"
      "   \"http://sourceware.org/gdb/gdb-memory-map.dtd\">\n"
      "<memory-map version=\"1.0.0\" >\n";
   // Suffix for memory map XML
   static const char xmlSuffix[] =
      "</memory-map>\n";

   static char xmlBuff[2000] = {0};
   char *xmlPtr;

   xmlPtr = xmlBuff;
   *bufferSize = 0;
   strcpy(xmlPtr, xmlPrefix);
   xmlPtr += sizeof(xmlPrefix)-1; // Discard trailing '\0'

   for (int memIndex=0; true; memIndex++) {
      MemoryRegionPtr pMemoryregion(deviceData.getMemoryRegion(memIndex));
      if (!pMemoryregion) {
         break;
      }
      Logging::print("memory area #%d", memIndex);
      for (unsigned memRange=0; memRange<pMemoryregion->memoryRanges.size(); memRange++) {
         uint32_t start, size;
         const MemoryRegion::MemoryRange *memoryRange = pMemoryregion->getMemoryRange(memRange);
         if (memoryRange == NULL)
            break;
         switch (pMemoryregion->getMemoryType()) {
         case MemXRAM:
         case MemXROM:
         case MemPROM:
         case MemPRAM:
            Logging::printq(" - XRAM/XROM - Ignored\n");
            break;
         case MemFlexNVM:
         case MemFlexRAM:
            Logging::printq(" - FlexNVM/FlexNVM - Ignored\n");
            break;
         case MemEEPROM:
            Logging::printq(" - EEPROM - Ignored\n");
            break;
         case MemDFlash:
         case MemPFlash:
         case MemFLASH:
            start = memoryRange->start;
            size  = memoryRange->end - start + 1;
            Logging::printq(" - FLASH[0x%08X..0x%08X]\n", memoryRange->start, memoryRange->end);
            xmlPtr += sprintf(xmlPtr,
                           "   <memory type=\"flash\" start=\"0x%X\" length=\"0x%X\" > \n"
                           "      <property name=\"blocksize\">0x400</property> \n"
                           "   </memory>\n",
                           start, size);
            break;
         case MemIO:  // Treat I/O as RAM
         case MemRAM:
            start = memoryRange->start;
            size  = memoryRange->end - start + 1;
            Logging::printq(" - RAM[0x%08X..0x%08X]\n", memoryRange->start, memoryRange->end);
            xmlPtr += sprintf(xmlPtr,
                           "<memory type=\"ram\" start=\"0x%X\" length=\"0x%X\" /> \n",
                           start, size);
            break;
         case MemROM:
            start = memoryRange->start;
            size  = memoryRange->end - start + 1;
            Logging::printq(" - ROM[0x%08X..0x%08X]\n", memoryRange->start, memoryRange->end);
            xmlPtr += sprintf(xmlPtr,
                           "<memory type=\"rom\" start=\"0x%X\" length=\"0x%X\" /> \n",
                           start, size);
            break;
         case MemInvalid:
            Logging::printq(" - Invalid\n");
            break;
         }
      }
   }
   strcpy(xmlPtr, xmlSuffix);
   xmlPtr += sizeof(xmlSuffix)-1; // Discard trailing '0'

//   Logging::print("XML = \n\"%s\"\n", xmlBuff);
   *buffer = xmlBuff;
   *bufferSize = xmlPtr-xmlBuff;
}

static const char targetXML[] =
      "<?xml version=\"1.0\"?>\n"
      "<!DOCTYPE target SYSTEM \"gdb-target.dtd\">\n"
      "<target version=\"1.0\">\n"
#if (TARGET == ARM) || (TARGET == CFV1) || (TARGET == CFVx)
      "   <xi:include href=\"targetRegs.xml\"/>\n"
#endif
      "</target>\n"
      ;

#if (TARGET == CFV1) || (TARGET == CFVx)
static const char defaultTargetRegsXML[] =
      "<?xml version=\"1.0\"?>\n"
      "<!DOCTYPE feature SYSTEM \"gdb-target.dtd\">\n"
      "<feature name=\"org.gnu.gdb.coldfire.core\">\n"
      "   <flags id=\"ps.type\" size=\"4\">\n"
      "      <field name=\"C\"  start=\"0\"  end=\"0\"/>\n"
      "      <field name=\"V\"  start=\"1\"  end=\"1\"/>\n"
      "      <field name=\"Z\"  start=\"2\"  end=\"2\"/>\n"
      "      <field name=\"N\"  start=\"3\"  end=\"3\"/>\n"
      "      <field name=\"X\"  start=\"4\"  end=\"4\"/>\n"
      "      <field name=\"I0\" start=\"8\"  end=\"8\"/>\n"
      "      <field name=\"I1\" start=\"9\"  end=\"9\"/>\n"
      "      <field name=\"I2\" start=\"10\" end=\"10\"/>\n"
      "      <field name=\"M\"  start=\"12\" end=\"12\"/>\n"
      "      <field name=\"S\"  start=\"13\" end=\"13\"/>\n"
      "      <field name=\"T0\" start=\"14\" end=\"14\"/>\n"
      "      <field name=\"T1\" start=\"15\" end=\"15\"/>\n"
      "   </flags>\n"
      "   <reg name=\"d0\" bitsize=\"32\" type=\"uint32\"     group=\"general\" />\n"
      "   <reg name=\"d1\" bitsize=\"32\" type=\"uint32\"     group=\"general\" />\n"
      "   <reg name=\"d2\" bitsize=\"32\" type=\"uint32\"     group=\"general\" />\n"
      "   <reg name=\"d3\" bitsize=\"32\" type=\"uint32\"     group=\"general\" />\n"
      "   <reg name=\"d4\" bitsize=\"32\" type=\"uint32\"     group=\"general\" />\n"
      "   <reg name=\"d5\" bitsize=\"32\" type=\"uint32\"     group=\"general\" />\n"
      "   <reg name=\"d6\" bitsize=\"32\" type=\"uint32\"     group=\"general\" />\n"
      "   <reg name=\"d7\" bitsize=\"32\" type=\"uint32\"     group=\"general\" />\n"
      "   <reg name=\"a0\" bitsize=\"32\" type=\"data_ptr\"   group=\"general\" />\n"
      "   <reg name=\"a1\" bitsize=\"32\" type=\"data_ptr\"   group=\"general\" />\n"
      "   <reg name=\"a2\" bitsize=\"32\" type=\"data_ptr\"   group=\"general\" />\n"
      "   <reg name=\"a3\" bitsize=\"32\" type=\"data_ptr\"   group=\"general\" />\n"
      "   <reg name=\"a4\" bitsize=\"32\" type=\"data_ptr\"   group=\"general\" />\n"
      "   <reg name=\"a5\" bitsize=\"32\" type=\"data_ptr\"   group=\"general\" />\n"
      "   <reg name=\"fp\" bitsize=\"32\" type=\"data_ptr\"   group=\"general\" />\n"
      "   <reg name=\"sp\" bitsize=\"32\" type=\"data_ptr\"   group=\"general\" />\n"
      "   \n"
      "   <reg name=\"ps\" bitsize=\"32\" type=\"ps.type\"  group=\"general\" />\n"
      "   <reg name=\"pc\" bitsize=\"32\" type=\"code_ptr\" group=\"general\" />\n"
      "   \n"
      "</feature>\n";
#else
static const char defaultTargetRegsXML[] =
   "<?xml version=\"1.0\"?>\n"
   "<!DOCTYPE feature SYSTEM \"gdb-target.dtd\">\n"
   "<feature name=\"org.gnu.gdb.arm.m-profile\" >\n"
   "   <struct id=\"misc.type\">\n"
   "      <field name=\"primask\"   type = \"uint8\"    />\n"
   "      <field name=\"basepri\"   type = \"uint8\"    />\n"
   "      <field name=\"faultmask\" type = \"uint8\"    />\n"
   "      <field name=\"control\"   type = \"uint8\"    />\n"
   "   </struct>\n"
   "   <reg name=\"r0\"   bitsize=\"32\" type=\"uint32\"   group=\"general\" />\n"
   "   <reg name=\"r1\"   bitsize=\"32\" type=\"uint32\"   group=\"general\" />\n"
   "   <reg name=\"r2\"   bitsize=\"32\" type=\"uint32\"   group=\"general\" />\n"
   "   <reg name=\"r3\"   bitsize=\"32\" type=\"uint32\"   group=\"general\" />\n"
   "   <reg name=\"r4\"   bitsize=\"32\" type=\"uint32\"   group=\"general\" />\n"
   "   <reg name=\"r5\"   bitsize=\"32\" type=\"uint32\"   group=\"general\" />\n"
   "   <reg name=\"r6\"   bitsize=\"32\" type=\"uint32\"   group=\"general\" />\n"
   "   <reg name=\"r7\"   bitsize=\"32\" type=\"uint32\"   group=\"general\" />\n"
   "   <reg name=\"r8\"   bitsize=\"32\" type=\"uint32\"   group=\"general\" />\n"
   "   <reg name=\"r9\"   bitsize=\"32\" type=\"uint32\"   group=\"general\" />\n"
   "   <reg name=\"r10\"  bitsize=\"32\" type=\"uint32\"   group=\"general\" />\n"
   "   <reg name=\"r11\"  bitsize=\"32\" type=\"uint32\"   group=\"general\" />\n"
   "   <reg name=\"r12\"  bitsize=\"32\" type=\"uint32\"   group=\"general\" />\n"
   "   <reg name=\"sp\"   bitsize=\"32\" type=\"data_ptr\" group=\"general\" />\n"
   "   <reg name=\"lr\"   bitsize=\"32\" type=\"uint32\"   group=\"general\" />\n"
   "   <reg name=\"pc\"   bitsize=\"32\" type=\"code_ptr\" group=\"general\" />\n"
   "   <reg name=\"xpsr\" bitsize=\"32\" type=\"uint32\"   group=\"general\" />\n"
   "   <reg name=\"msp\"  bitsize=\"32\" type=\"data_ptr\" group=\"general\" />\n"
   "   <reg name=\"psp\"  bitsize=\"32\" type=\"data_ptr\" group=\"general\" />\n"
   "   <reg name=\"misc\" bitsize=\"32\" type=\"misc.type\" group=\"general\" />\n"
   "</feature>\n"
   ;
#endif

typedef struct {
   unsigned long value;
   int           size;
} Register_t;

#if (TARGET == ARM)
// Maps GDB register numbers to USBDM register numbers (or -1 if invalid)
int registerMap[] = {
      ARM_RegR0,   ARM_RegR1,   ARM_RegR2,  ARM_RegR3,
      ARM_RegR4,   ARM_RegR5,   ARM_RegR6,  ARM_RegR7,
      ARM_RegR8,   ARM_RegR9,   ARM_RegR10, ARM_RegR11,
      ARM_RegR12,  ARM_RegSP,   ARM_RegLR,  ARM_RegPC, // r0-r12,sp,lr,pc
      ARM_RegxPSR, ARM_RegMSP,  ARM_RegPSP,            // psr, main sp, process sp
      ARM_RegMISC,   // [31:24]=CONTROL,[23:16]=FAULTMASK,[15:8]=BASEPRI,[7:0]=PRIMASK.
      ARM_RegFPSCR,
      ARM_RegFPS0+0x00, ARM_RegFPS0+0x01, ARM_RegFPS0+0x02, ARM_RegFPS0+0x03,
      ARM_RegFPS0+0x04, ARM_RegFPS0+0x05, ARM_RegFPS0+0x06, ARM_RegFPS0+0x07,
      ARM_RegFPS0+0x08, ARM_RegFPS0+0x09, ARM_RegFPS0+0x0A, ARM_RegFPS0+0x0B,
      ARM_RegFPS0+0x0C, ARM_RegFPS0+0x0D, ARM_RegFPS0+0x0E, ARM_RegFPS0+0x0F,
      ARM_RegFPS0+0x10, ARM_RegFPS0+0x11, ARM_RegFPS0+0x12, ARM_RegFPS0+0x13,
      ARM_RegFPS0+0x14, ARM_RegFPS0+0x15, ARM_RegFPS0+0x16, ARM_RegFPS0+0x17,
      ARM_RegFPS0+0x18, ARM_RegFPS0+0x19, ARM_RegFPS0+0x1A, ARM_RegFPS0+0x1B,
      ARM_RegFPS0+0x1C, ARM_RegFPS0+0x1D, ARM_RegFPS0+0x1E, ARM_RegFPS0+0x1F,
};
#define CACHED_PC_VALUE  (*(uint32_t*)(registerBuffer+(4*ARM_RegPC)))
#elif TARGET == CFV1
int registerMap[] = {
      CFV1_RegD0,CFV1_RegD1,CFV1_RegD2,CFV1_RegD3,
      CFV1_RegD4,CFV1_RegD5,CFV1_RegD6,CFV1_RegD7,
      CFV1_RegA0,CFV1_RegA1,CFV1_RegA2,CFV1_RegA3,
      CFV1_RegA4,CFV1_RegA5,CFV1_RegA6,CFV1_RegA7,
      0x100+CFV1_CRegSR, 0x100+CFV1_CRegPC,         // +0x100 indicates USBDM_ReadCReg
};
#define CACHED_PC_VALUE  (*(uint32_t*)(registerBuffer+(4*17)))
#elif TARGET == CFVx
int registerMap[] = {
      CFVx_RegD0,CFVx_RegD1,CFVx_RegD2,CFVx_RegD3,
      CFVx_RegD4,CFVx_RegD5,CFVx_RegD6,CFVx_RegD7,
      CFVx_RegA0,CFVx_RegA1,CFVx_RegA2,CFVx_RegA3,
      CFVx_RegA4,CFVx_RegA5,CFVx_RegA6,CFVx_RegA7,
      0x100+CFVx_CRegSR, 0x100+CFVx_CRegPC,        // +0x100 indicates USBDM_ReadCReg
};
#define CACHED_PC_VALUE  (*(uint32_t*)(registerBuffer+(4*17)))
#endif

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

static char     targetRegsXML[6000];
static unsigned targetRegsXMLSize   = 0;
static unsigned targetLastRegIndex  = 0;

/*!  Sets up the register description
 *
 */
void initRegisterDescription(void) {
   RegisterDescriptionConstPtr registerDescriptionPtr = deviceData.getRegisterDescription();
   if (registerDescriptionPtr != NULL) {
      reportGdbPrintf("Loading register description from device database\n");
      targetRegsXMLSize  = registerDescriptionPtr->getDescription().length();
      if (targetRegsXMLSize > sizeof(targetRegsXML)) {
         reportGdbPrintf(M_FATAL, BDM_RC_ILLEGAL_PARAMS, "Internal error, targetRegsXML description is too large: ");
         targetRegsXMLSize = sizeof(targetRegsXML);
      }
      string s = registerDescriptionPtr->getDescription();
      strncpy(targetRegsXML, ltrim(s).c_str(), targetRegsXMLSize);
      targetLastRegIndex = registerDescriptionPtr->getLastRegisterIndex();
   }
   else {
      reportGdbPrintf("Using default register description\n");
      strcpy(targetRegsXML, defaultTargetRegsXML);
      targetRegsXMLSize  = sizeof(defaultTargetRegsXML);
      targetLastRegIndex = (sizeof(registerMap)/sizeof(registerMap[0]))-1;
   }
}

bool isValidRegister(unsigned regNo) {
   if (regNo >= sizeof(registerMap)/sizeof(registerMap[0]))
      return false;
   else
      return registerMap[regNo]>=0;
}

//! Read register into string buffer as hex chars
//!
//! @param regNo    - number of register to read (GDB numbering)
//! @param buffPtr  - pointer to buffer
//!
//! @return number of bytes written
//!
//! @note bytes are written in target byte order
//!
static int readReg(unsigned regNo, unsigned char *buffPtr) {
   LOGGING_Q;
   unsigned long regValue;

   if (!isValidRegister(regNo)) {
      Logging::print("reg[%d] => Invalid GDB register number\n", regNo);
      reportGdbPrintf(M_FATAL, BDM_RC_ILLEGAL_PARAMS, "Invalid GDB register number. ");
      memset(buffPtr, 0xAA, 4);
      return 4;
   }
   int usbdmRegNo = registerMap[regNo];

   USBDM_ErrorCode rc;

#if (TARGET == ARM)
   rc = USBDM_ReadReg((ARM_Registers_t)usbdmRegNo, &regValue);
   Logging::print("%s(0x%02X) => %08lX\n", getARMRegName(usbdmRegNo), usbdmRegNo, regValue);
   regValue = nativeToTarget32(regValue);
#elif (TARGET == CFV1)
   if (usbdmRegNo < 0x100) {
      rc = USBDM_ReadReg((CFV1_Registers_t)usbdmRegNo, &regValue);
      Logging::print("%s => %08lX\n", getCFV1RegName(regNo), regValue);
   }
   else {
      rc = USBDM_ReadCReg((CFV1_Registers_t)(usbdmRegNo-0x100), &regValue);
      Logging::print("%s => %08lX\n", getCFV1ControlRegName(usbdmRegNo-0x100), regValue);
   }
#elif(TARGET == CFVx)
   if (usbdmRegNo < 0x100) {
      rc = USBDM_ReadReg((CFV1_Registers_t)usbdmRegNo, &regValue);
      Logging::print("%s => %08lX\n", getCFVxRegName(usbdmRegNo), regValue);
   }
   else {
      usbdmRegNo -= 0x100;
      rc = USBDM_ReadCReg((CFV1_Registers_t)(usbdmRegNo), &regValue);
      Logging::print("%s => %08lX\n", getCFVxControlRegName(usbdmRegNo), regValue);
   }
#endif
   if (rc != BDM_RC_OK) {
      Logging::print("Register read(%d) failed, reason = %s\n", regNo, USBDM_GetErrorString(rc));
      reportGdbPrintf(M_ERROR, rc, "Register read failed. ");
      memset(buffPtr, 0xAA, 4);
      return 4;
   }
   regValue = nativeToTarget32(regValue);
   memcpy(buffPtr, &regValue, 4);
   return 4;
}

static unsigned char registerBuffer[1000];
static unsigned registerBufferSize = 0;  // Number of bytes valid in buffer, 0 => not cached

static bool useFastRegisterRead = true;

/*
 *  Get cached value of PC as a string
 *
 *  @return ptr to static buffer
 */
const char *getCachedPC() {
   static char buff[20];

   sprintf(buff, "0x%08X", targetToNative32(CACHED_PC_VALUE));
   return buff;
}

//! Read all registers from target into registerBuffer
//! Sets registerBufferSize to number of bytes valid in buffer
//!
//! @note values are returned in target byte order
//!
//! ToDo Handle errors
//!
static USBDM_ErrorCode readRegs(void) {
   LOGGING;

   if (useFastRegisterRead) {
      // Read registers
      USBDM_ErrorCode rc = USBDM_ReadMultipleRegs(registerBuffer, 0, targetLastRegIndex);
      if (rc == BDM_RC_OK) {
         // OK
         registerBufferSize = 4*(targetLastRegIndex+1);
         return BDM_RC_OK;
      }
      if (rc != BDM_RC_ILLEGAL_COMMAND) {
         // Unknown failure
         registerBufferSize = 0;
         return rc;
      }
      // rc == BDM_RC_ILLEGAL_COMMAND
      // Try the old method
      useFastRegisterRead = false;
   }
   if (!useFastRegisterRead) {
      unsigned regNo;
      registerBufferSize = 0;
      unsigned char *buffPtr = registerBuffer;
      for (regNo = 0; regNo<=targetLastRegIndex; regNo++) {
         buffPtr += readReg(regNo, buffPtr);
      }
      registerBufferSize = buffPtr-registerBuffer;
   }
   return BDM_RC_OK;
}

//! Report register values to GDB
//! Reads registers from target if necessary
//!
//! @note values are returned in target byte order
//!
static void sendRegs(void) {
   reportGdbPrintf("Reading Registers\n");
   if (registerBufferSize == 0) {
      readRegs();
   }
   gdbInOut->sendGdbHex(registerBuffer, registerBufferSize);
   registerBufferSize = 0;
}

//! Write to target register
//!
//! @param regNo     - number of register to read (GDB numbering)
//! @param regValue  - value to write
//!
static void writeReg(unsigned regNo, unsigned long regValue) {
   LOGGING;
   if (!isValidRegister(regNo))
      return;
   int usbdmRegNo = registerMap[regNo];

#if (TARGET == ARM)
   USBDM_WriteReg((ARM_Registers_t)usbdmRegNo, regValue);
   Logging::print("%s(0x%02X) <= %08lX\n", getARMRegName(usbdmRegNo), usbdmRegNo, regValue);
   regValue = bigendianToTarget32(regValue);
#elif (TARGET == CFV1) || (TARGET == CFVx)
   if (usbdmRegNo < 0x100) {
      USBDM_WriteReg((CFV1_Registers_t)usbdmRegNo, regValue);
      Logging::print("reg[%d] <= %08lX\n", regNo, regValue);
   }
   else {
      USBDM_WriteCReg((CFV1_Registers_t)(usbdmRegNo-0x100), regValue);
      Logging::print("reg[%d] <= %08lX\n", regNo, regValue);
   }
#endif
}

//! Write target registers from string buffer containing hex chars
//!
//! @param ccPtr  - ptr to buffer
//!
//! @note characters are written in target byte order
//!
static void writeRegs(const char *ccPtr) {
   LOGGING;
   unsigned long regValue = 0;
   unsigned regNo;

   reportGdbPrintf("Writing Registers\n");
   for (regNo = 0; regNo<=targetLastRegIndex; regNo++) {
      if (!hexToInt32(ccPtr, &regValue))
         break;
      ccPtr += 8;
      regValue = bigendianToTarget32(regValue);
      writeReg(regNo, regValue);
   }
   gdbInOut->sendGdbString("OK");
   registerBufferSize = 0;
}

static MemorySpace_t getAlignment(uint32_t address, uint32_t numBytes) {

   MemorySpace_t align = MS_Long; // Assume 4-byte alignment
   if (((address & 0x3) != 0) || ((numBytes & 0x3) != 0)) {
      align = MS_Word;
   }
   if (((address & 0x1) != 0) || ((numBytes & 0x1) != 0)) {
      align = MS_Byte;
   }
   return align;
}
static void readMemory(uint32_t address, uint32_t numBytes) {
   LOGGING;
   unsigned char buff[1000] = {0};

   MemorySpace_t align = getAlignment(address, numBytes);
   reportGdbPrintf(M_BORINGINFO, "Reading Memory[%X..%X], align = %s\n", address, address+numBytes-1, getMemSpaceName(align));
//   Logging::print("readMemory(addr=%X, size=%X)\n", address, numBytes);
   if (USBDM_ReadMemory(align, numBytes, address, buff) != BDM_RC_OK) {
      // Ignore errors
      memset(buff, 0xAA, numBytes);
//      gdbInOut->sendErrorMessage(0x11);
//      return;
   }
   gdbInOut->sendGdbHex(buff, numBytes);
}

//! Convert a hex string to a series of byte values
//!
//! @param numBytes - number of bytes to convert
//! @param dataIn   - ptr to string of Hex chars (2 * numBytes)
//! @param dataOut  - ptr to output buffer (numBytes)
//!
//! @return true => ok conversion\n
//!         false => failed
//!
static bool convertFromHex(unsigned numBytes, const char *dataIn, unsigned char *dataOut) {
//   Logging::print("convertFromHex()\n");
   for (unsigned index=0; index<numBytes; index++) {
      unsigned long value;
      if (!hexToInt8(dataIn, &value)) {
         return false;
      }
//      Logging::print("convertFromHex() %2.2s => %2.2X\n", dataIn, value);
      dataIn += 2;
      *dataOut++ = value;
   }
   return true;
}

static void writeMemory(const char *ccPtr, uint32_t address, uint32_t numBytes) {
   unsigned char buff[1000];

   MemorySpace_t align = getAlignment(address, numBytes);
   reportGdbPrintf(M_BORINGINFO, "Writing Memory[%X..%X], align = %s\n", address, address+numBytes-1, getMemSpaceName(align));
//   Logging::print("writeMemory(addr=%X, size=%X)\n", address, numBytes);
   convertFromHex(numBytes, ccPtr, buff);
   USBDM_WriteMemory(align, numBytes, address, buff);
   gdbInOut->sendGdbString("OK");
}

#if (TARGET == ARM)
//! Reads a word from ARM target memory
//!
//! @param address  - 32-bit address (aligned)
//! @param data     - pointer to buffer for word
//!
//! @return error code
//!
static USBDM_ErrorCode armReadMemoryWord(unsigned long address, unsigned long *data) {
   LOGGING_Q;
   uint8_t buff[4];
   USBDM_ErrorCode rc = USBDM_ReadMemory(4, 4, address, buff);
   *data = (buff[0])+(buff[1]<<8)+(buff[2]<<16)+(buff[3]<<24);
//   switch(address) {
//   case DEMCR:
//      Logging::print("DEMCR => %s)\n", getDEMCRName(*data));
//      break;
//   case DHCSR:
//      Logging::print("DHCSR => %s)\n", getDHCSRName(*data));
//      break;
//   default: break;
//   }
   return rc;
}


//! Get ARM run state by polling target
//!
//! @return status - status of target T_UNKNOWN/T_SLEEP/T_HALT/T_RUNNING
//!
GdbTargetStatus getTargetStatus(void) {
   LOGGING_Q;
   static GdbTargetStatus lastStatus;
   GdbTargetStatus status;

   unsigned long dhcsr;

   USBDM_ErrorCode BDMrc = armReadMemoryWord(DHCSR, &dhcsr);

   if (BDMrc != BDM_RC_OK) {
      Logging::print("Doing autoReconnect\n");
      if (USBDM_Connect() != BDM_RC_OK) {
         Logging::print("Re-connect failed\n");
      }
      else {
         Logging::print("Re-connect OK\n");
         // retry after connect
         BDMrc = armReadMemoryWord(DHCSR, &dhcsr);
      }
   }
   while (BDMrc != BDM_RC_OK) {
//      Logging::print("Reporting Error: %s\n", USBDM_GetErrorString(BDMrc));
//      if (reportErrorWithRetryPrompt(BDMrc)) {
//         if (USBDM_Connect()) {
//            BDMrc = armReadMemoryWord(DHCSR, &dhcsr);
//         }
//      }
//      else {
      //         return T_NOCONNECTION;
//      }
      return T_NOCONNECTION;
   }
   // Reset on OK status
   if ((dhcsr & DHCSR_S_SLEEP) != 0) {
      // Stopped - low power sleep, treated as special
      status = T_SLEEPING;
      if (lastStatus != status) {
         Logging::print("Status change => T_SLEEP)\n");
      }
   }
   else if ((dhcsr & (DHCSR_S_HALT|DHCSR_S_LOCKUP)) != 0) {
      // Processor in debug halt
      status = T_HALT;
      if (lastStatus != status) {
         Logging::print("Status change => T_HALT)\n");
      }
   }
   else {
      // Processor executing
      status = T_RUNNING;
      if (lastStatus != status) {
         Logging::print("Status change => T_RUNNING)\n");
      }
   }
   lastStatus = status;
   return status;
}

#elif TARGET == CFV1
//! Get CFV1 run state by polling target
//!
//! @return status - status of target T_UNKNOWN/T_SLEEP/T_HALT/T_RUNNING
//!
GdbTargetStatus getTargetStatus (void) {
   LOGGING_Q;
   static GdbTargetStatus lastStatus;
   GdbTargetStatus status;

   unsigned long value;
   USBDM_ErrorCode rc = USBDM_ReadStatusReg(&value);
   if (rc != BDM_RC_OK) {
      Logging::print("Failed, rc = %s\n", USBDM_GetErrorString(rc));
      status = T_UNKNOWN;
   }
   else if ((value & CFV1_XCSR_ENBDM) == 0) {
      Logging::print("ENBDM=0\n");
      status = T_UNKNOWN;
   }
   else if (value&CFV1_XCSR_RUNSTATE) {
      status = T_HALT;
      if (lastStatus != status) {
         Logging::print("Status change => T_HALT)\n");
      }
   }
   else {
      status = T_RUNNING;
      if (lastStatus != status) {
         Logging::print("Status change => T_RUNNING)\n");
      }
   }
   lastStatus = status;
   return status;
}
#elif TARGET == CFVx
//! Get CFVx run state by polling target
//!
//! @return status - status of target T_UNKNOWN/T_SLEEP/T_HALT/T_RUNNING
//!
GdbTargetStatus getTargetStatus(void) {
   LOGGING_Q;
   static GdbTargetStatus lastStatus;
   GdbTargetStatus status;

   USBDM_ErrorCode rc = USBDM_Connect();
   if (rc == BDM_RC_CF_NOT_READY) {
      // Returns this response after an attempted operation while running
      status = T_RUNNING;
      if (lastStatus != status) {
         Logging::print("Status change => T_RUNNING)\n");
      }
   }
   else if (rc != BDM_RC_OK) {
      Logging::print("Connect failed, rc = %s\n", USBDM_GetErrorString(rc));
      status = T_UNKNOWN;
   }
   else {
      // Crude - Assume if register read succeeds then target is halted
      unsigned long value;
      rc = USBDM_ReadReg(CFVx_RegD0, &value);
      if (rc == BDM_RC_OK) {
         status = T_HALT;
         if (lastStatus != status) {
            Logging::print("Status change => T_HALT)\n");
         }
      }
      else {
         status = T_RUNNING;
         if (lastStatus != status) {
            Logging::print("Status change => T_RUNNING)\n");
         }
      }
   }
   lastStatus = status;
   return status;
}
#endif

//! Send portion of XML to debugger
//!
//!
static void sendXML(unsigned size, unsigned offset, const char *buffer, unsigned bufferSize) {
   LOGGING;
   gdbInOut->putGdbPreamble();
   if (offset >= bufferSize) {
      gdbInOut->putGdbString("l");
   }
   else {
      if (size > (bufferSize-offset)) {
         // Remainder fits in this pkt
         size = bufferSize-offset;
         gdbInOut->putGdbChar('l');
      }
      else {
         // More pkts to follow
         gdbInOut->putGdbChar('m');
      }
      gdbInOut->putGdbString(buffer+offset, size);
   }
   gdbInOut->sendGdbBuffer();
}

#if TARGET==ARM
/*! Mask/unmask interrupts (in DHCSR)
 *
 * @param disableInterrupts - true/false -> disable/enable interrupts
 */
void maskInterrupts(bool disableInterrupts) {
   const uint8_t disableInts[4] = {DHCSR_C_MASKINTS|DHCSR_C_HALT|DHCSR_C_DEBUGEN,0x00,0x5F,0xA0};
   const uint8_t enableInts[4]  = {DHCSR_C_HALT|DHCSR_C_DEBUGEN,0x00,0x5F,0xA0};

   if (disableInterrupts) {
      USBDM_WriteMemory(MS_Long, 4, DHCSR, disableInts);
   }
   else {
      USBDM_WriteMemory(MS_Long, 4, DHCSR, enableInts);
   }
   // For debug checking
//   uint8_t temp[4];
//   USBDM_ReadMemory(MS_Long, 4, DHCSR, temp);
}
#elif TARGET==CFV1
void maskInterrupts(bool disableInterrupts) {
   unsigned long csrValue;

   USBDM_ReadDReg(CFV1_DRegCSR, &csrValue);

   if (disableInterrupts) {
      USBDM_WriteDReg(CFV1_DRegCSR, csrValue|CFV1_CSR_IPI);
   }
   else {
      USBDM_WriteDReg(CFV1_DRegCSR, csrValue&~CFV1_CSR_IPI);
   }
   // For debug
   USBDM_ReadDReg(CFV1_DRegCSR, &csrValue);
}
#else
void maskInterrupts(bool disableInterrupts) {
      (void)disableInterrupts;
      // Not implemented
}
#endif

/*!
 *    Single step target
 *
 * @param disableInterrupts - true/false -> disable/enable interrupts on step
 */
void stepTarget(bool disableInterrupts) {
   maskInterrupts(disableInterrupts);
   USBDM_TargetStep();
}

/*!
 *    Continue target
 *
 *    If at a breakpoint then a single step is done (with interrupts masked) before
 *    continuing at full execution.
 *    Breakpoints are activated.
 */
void continueTarget(void) {
   if (atMemoryBreakpoint()) {
      // Do 1 step before activating memory breakpoints
      Logging::print("Continue - stepping one instruction...\n");
      stepTarget(true);
   }
   maskInterrupts(false);
   activateBreakpoints();
   Logging::print("Continue - executing...\n");
   USBDM_TargetGo();
   Logging::print("Continue - Now running\n");

}

/*! Checks if two string are equal
 *  @param s1 first string
 *  @paran s2 second string
 *
 *  @return true if equal, false otherwise
 */
bool streq(const char *s1, const char *s2) {
   return strcmp(s1,s2) == 0;
}

/*! Checks if two string are equal
 *
 *  @param s1 first string
 *  @paran s2 second string
 *  @param length number of characters to check
 *
 *  @return true if equal in the first length characters, false otherwise
 */
bool strneq(const char *s1, const char *s2, int length) {
   return strncmp(s1,s2,length) == 0;
}

void setMaskISR(bool disableInterrupts) {

   maskInterruptsWhenStepping = disableInterrupts;
}

bool getMaskISR(void) {
   return maskInterruptsWhenStepping;
}

/* Do monitor commands
 *
 */
static USBDM_ErrorCode doMonitorCommand(const char *cmd) {
   LOGGING_Q;
   char command[200], *bPtr = command;
   for (const char *cp=cmd+sizeof("qRcmd,")-1; *cp != '\0'; cp += 2) {
      unsigned long value;
      if (!hexToInt8(cp, &value)) {
         break;
      }
      *bPtr++ = (char)value;
   }
   *bPtr = '\0';
   Logging::print("%s\n", command);
   if (strneq(command, "reset", sizeof("reset")-1)) {
      // ignore any parameters
      reportGdbPrintf(M_INFO, "User reset of target\n");
      USBDM_TargetReset((TargetMode_t)(RESET_DEFAULT|RESET_SPECIAL));
      gdbInOut->sendGdbHexString("O", "User reset of target\n", -1);
      gdbInOut->sendGdbString("OK");
      registerBufferSize = 0;
   }
   else if (strneq(command, "halt", sizeof("halt")-1)) {
      // ignore any parameters
      reportGdbPrintf(M_INFO, "User halt of target\n");
      USBDM_TargetHalt();
      gdbInOut->sendGdbHexString("O", "User halt of target\n", -1);
      gdbInOut->sendGdbString("OK");
      registerBufferSize = 0;
   }
   else if (strneq(command, "speed", sizeof("speed")-1)) {
      // ignore any parameters
      reportGdbPrintf(M_INFO, "Setting speed\n");
      USBDM_SetSpeed(12000 /* kHz */);
      gdbInOut->sendGdbHexString("O", "Done", -1);
      gdbInOut->sendGdbString("OK");
   }
   else if (strneq(command, "maskisr", sizeof("maskisr")-1)) {
      char *ptr = command+sizeof("maskisr")-1;
      while (isspace(*ptr)) {
         ptr++;
      }
      if (strneq(ptr, "1",  sizeof("1")-1) ||
            strneq(ptr, "on", sizeof("on")-1) ||
            strneq(ptr, "t",  sizeof("t")-1)) {
         setMaskISR(true);
      }
      else if (strneq(ptr, "0",   sizeof("1")-1) ||
            strneq(ptr, "off", sizeof("off")-1) ||
            strneq(ptr, "f",   sizeof("f")-1)) {
         reportGdbPrintf(M_INFO, "maskisr On\n");
         setMaskISR(false);
      }
      if (maskInterruptsWhenStepping) {
         reportGdbPrintf(M_INFO, "maskisr on\n");
         gdbInOut->sendGdbHexString("O", "maskisr on\n", -1);
      }
      else {
         reportGdbPrintf(M_INFO, "maskisr off\n");
         gdbInOut->sendGdbHexString("O", "maskisr off\n", -1);
      }
      gdbInOut->sendGdbString("OK");
      registerBufferSize = 0;
   }
   else if (strneq(command, "help", sizeof("help")-1)) {
      gdbInOut->sendGdbHexString("O",
                                 "MON commands\n"
                                 "=====================\n"
                                 "maskisr (on|off)\n"
                                 "halt\n"
                                 "reset\n"
                                 "=====================\n",
                                 -1);
      gdbInOut->sendGdbString("OK");
   }
   else {
      Logging::print("Unrecognised mon commandcommand: \'%s\'\n", cmd);
      reportGdbPrintf(M_INFO, "Unrecognised command: \'%s\'\n", cmd);
      gdbInOut->sendGdbHexString("O", "Unrecognized command\n", -1);
      gdbInOut->sendGdbString("OK");
   }
   return BDM_RC_OK;
}

static USBDM_ErrorCode doQCommands(const GdbPacket *pkt) {
   LOGGING_Q;
   int offset, size;
   const char *cmd = pkt->buffer;

   if (strncmp(cmd, "qSupported", sizeof("qSupported")-1) == 0) {
      Logging::print("qSupported\n");
      char buff[200];
      sprintf(buff,"QStartNoAckMode+;qXfer:memory-map:read+;PacketSize=%X;qXfer:features:read+",GdbPacket::MAX_MESSAGE-10);
//      sprintf(buff,"QStartNoAckMode+;qXfer:memory-map:read+;PacketSize=%X",GdbPacket::MAX_MESSAGE-10);
      gdbInOut->sendGdbString(buff);
   }
//   else if (strncmp(cmd, "qC", sizeof("qC")-1) == 0) {
//      gdbInOut->sendGdbString(""); //("QC-1");
//   }
//   else if (strncmp(cmd, "qfThreadInfo", sizeof("qfThreadInfo")-1) == 0) {
//      gdbInOut->sendGdbString("m1"); //("m0");
//      pendingCommand = true;
//   }
//   else if (strncmp(cmd, "qsThreadInfo", sizeof("qsThreadInfo")-1) == 0) {
//      gdbInOut->sendGdbString("l");
//   }
//   else if (strncmp(cmd, "qThreadExtraInfo", sizeof("qThreadExtraInfo")-1) == 0) {
//      gdbInOut->sendGdbHexString(NULL, "Runnable");
//   }
   else if (strncmp(cmd, "qAttached", sizeof("qAttached")-1) == 0) {
      Logging::print("qAttached\n");
      gdbInOut->sendGdbString("0");
   }
   else if (strncmp(cmd, "QStartNoAckMode", sizeof("QStartNoAckMode")-1) == 0) {
      Logging::print("QStartNoAckMode\n");
      gdbInOut->sendGdbString("OK");
      gdbInOut->setAckMode(false);
   }
//   else if (strncmp(cmd, "qTStatus", sizeof("qTStatus")-1) == 0) {
//      gdbInOut->sendGdbString("T0");
//   }
   else if (strncmp(cmd, "qOffsets", sizeof("qOffsets")-1) == 0) {
      Logging::print("qOffsets\n");
      // No relocation done
      gdbInOut->sendGdbString("Text=0;Data=0;Bss=0");
   }
   else if (strncmp(cmd, "qXfer:memory-map:read::", sizeof("qXfer:memory-map:read::")-1) == 0) {
      if (sscanf(cmd,"qXfer:memory-map:read::%X,%X",&offset, &size) != 2) {
         Logging::print("Ill formed:\'%s\'", cmd);
         gdbInOut->sendGdbString("");
      }
      else {
         Logging::print("memory-map:read::%X:%X\n", offset, size);
         unsigned xmlBufferSize;
         const char *xmlBuffer;
         createMemoryMapXML(&xmlBuffer, &xmlBufferSize);
         sendXML(size, offset, xmlBuffer, xmlBufferSize);
      }
   }
   else if (strncmp(cmd, "qXfer:features:read:target.xml:", sizeof("qXfer:features:read:target.xml:")-1) == 0) {
      if (targetRegsXMLSize > 0) {
         reportGdbPrintf(M_INFO, "Sending target description\n");
         if (sscanf(cmd,"qXfer:features:read:target.xml:%X,%X",&offset, &size) != 2) {
            Logging::print("Ill formed:\'%s\'", cmd);
            gdbInOut->sendGdbString("");
         }
         else {
            Logging::print("qXfer:features:read:target.xml:%X:%X\n", offset, size);
            sendXML(size, offset, targetXML, sizeof(targetXML));
         }
      }
      else {
         // Target register description not available
         gdbInOut->sendGdbString("");
      }
   }
   else if (strncmp(cmd, "qXfer:features:read:targetRegs.xml:", sizeof("qXfer:features:read:targetRegs.xml:")-1) == 0) {
      reportGdbPrintf(M_INFO, "Sending register description\n");
      if (targetRegsXMLSize > 0) {
         if (sscanf(cmd,"qXfer:features:read:targetRegs.xml:%X,%X",&offset, &size) != 2) {
            Logging::print("Ill formed:\'%s\'", cmd);
            gdbInOut->sendGdbString("");
         }
         else {
            Logging::print("qXfer:features:read:targetRegs.xml:%X:%X\n", offset, size);
            sendXML(size, offset, targetRegsXML, targetRegsXMLSize);
         }
      }
      else {
         // Target register description not available
         gdbInOut->sendGdbString("");
      }
   }
//   else if (strncmp(cmd, "qTStatus,", sizeof("qTStatus,")-1) == 0) {
//      // Ignore
//      gdbInOut->sendGdbString("");
//      // No trace experiment running right now
//      gdbInOut->sendGdbString("T0;tnotrun:0");
//   }
   else if (strncmp(cmd, "qRcmd,", sizeof("qRcmd,")-1) == 0) {
      // Monitor command
      doMonitorCommand(cmd);
   }
   else {
      Logging::print("Unrecognized command:\'%s\'\n", cmd);
      gdbInOut->sendGdbString("");
   }
   return BDM_RC_OK;
}

static USBDM_ErrorCode programImage(FlashImage *flashImage) {
   LOGGING;
   USBDM_ErrorCode rc;
   FlashProgrammer flashProgrammer;

   Logging::print("Security = %s\n", getSecurityName(deviceData.getSecurity()));

   if (deviceData.getEraseOption() == DeviceData::eraseNone) {
#if (TARGET==CFV1) || (TARGET==ARM)
      deviceData.setEraseOption(DeviceData::eraseMass);
#elif TARGET==CFVx
      deviceData.setEraseOption(DeviceData::eraseAll);
#else
   #error "Unhandled case"
#endif
   }

   if (deviceData.getSecurity() == SEC_SECURED) {
      deviceData.setSecurity(SEC_SMART);
   }
   deviceData.setClockTrimFreq(0);
   deviceData.setClockTrimNVAddress(0);
   rc = flashProgrammer.setDeviceData(deviceData);
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
   rc = flashProgrammer.programFlash(flashImage);

   // Initialise the target after programming
   flashProgrammer.resetAndConnectTarget();

   if (rc != PROGRAMMING_RC_OK) {
      Logging::print("programImage() - failed, rc = %s\n", USBDM_GetErrorString(rc));
      return rc;
   }
   Logging::print("programImage() - Complete\n");
   return BDM_RC_OK;
}

//#define VCONT_SUPPORTED

#ifdef VCONT_SUPPORTED

//! Handle 'vCont' commands
//!
static USBDM_ErrorCode doVContCommands(const GdbPacket *pkt) {
   LOGGING;
//   int address, length;
   const char *cmd = pkt->buffer;
   if (strncmp(cmd, "vCont?", sizeof("vCont?")) == 0) {
      gdbInOut->sendGdbString("vCont;c;s;t");
   }
   else if (strncmp(cmd, "vCont;c", sizeof("vCont;c")) == 0) {
      Logging::print("vCont;c - continue", cmd);
      gdbInOut->sendGdbString("OK");
   }
   else if (strncmp(cmd, "vCont;s", sizeof("vCont;s")) == 0) {
      Logging::print("vCont;s - step", cmd);
      gdbInOut->sendGdbString("OK");
   }
   else if (strncmp(cmd, "vCont;s", sizeof("vCont;t")) == 0) {
      Logging::print("vCont;t - halt", cmd);
      gdbInOut->sendGdbString("OK");
   }
   else {
      Logging::print("Unrecognized command:\'%s\'\n", cmd);
      gdbInOut->sendGdbString("OK");
   }
   return BDM_RC_OK;
}
#endif

//! Handle 'v...' commands
//!
static USBDM_ErrorCode doVCommands(const GdbPacket *pkt) {
   LOGGING;
   int address, length;
   const char *cmd = pkt->buffer;

   if (strncmp(cmd, "vFlashErase", 11) == 0) {
      // vFlashErase:addr,length
      if (sscanf(cmd, "vFlashErase:%x,%x", &address, &length) != 2) {
         gdbInOut->sendErrorMessage(0x11);
      }
      else {
         Logging::print("vFlashErase:0x%X:0x%X\n", address, length);
         reportGdbPrintf(M_INFO, "Erasing flash[%X..%X] - ignored\n", address, address+length-1);
         gdbInOut->sendGdbString("OK");
      }
   }
   else if (strncmp(cmd, "vFlashWrite", 11) == 0) {
      // vFlashWrite:addr:XX...
      if (sscanf(cmd, "vFlashWrite:%x:", &address) != 1) {
         Logging::print(" vFlashWrite:error:\n");
         gdbInOut->sendErrorMessage(0x11);
      }
      else {
         Logging::print("vFlashWrite:0x%X:\n", address);
         if (flashImage == NULL) {
            reportGdbPrintf(M_INFO, "Creating flash image\n");
            flashImage = new FlashImage();
         }
         reportGdbPrintf(M_INFO, "Writing to flash image[%X..", address);
         const char *vPtr = strchr(pkt->buffer,':');
         vPtr = strchr(++vPtr, ':');
         vPtr++;
         int size=pkt->size-(vPtr-pkt->buffer);
         bool newLine = true;
         while(size-->0) {
            flashImage->setValue(address, *vPtr);
            if (newLine)
               Logging::printq("\n%8.8X:", address);
            Logging::printq("%2.2X", (unsigned char)*vPtr);
            address++;
            vPtr++;
            newLine = (address & 0x0F) == 0;
         }
         reportGdbPrintf(M_INFO, "%X]\n", address-1);
         Logging::printq("\n");
         gdbInOut->sendGdbString("OK");
      }
   }
   else if (strncmp(cmd, "vFlashDone", 10) == 0) {
      // vFlashDone
      Logging::print("vFlashDone\n");
      if (flashImage != NULL) {
         USBDM_ErrorCode rc = programImage(flashImage);
         delete flashImage;
         flashImage = NULL;
         if (rc != PROGRAMMING_RC_OK) {
            Logging::print("vFlashDone: Programming failed, rc=%s\n", USBDM_GetErrorString(rc));
            reportGdbPrintf(M_FATAL, rc,"Programming Flash Image failed: ");
            gdbInOut->sendErrorMessage(1, "Flash programming failed");
            return rc;
         }
         else {
            reportGdbPrintf(M_INFO, "Programmed flash Image to target\n");
            Logging::print("vFlashDone: Programming complete\n");
         }
      }
      else {
         reportGdbPrintf(M_INFO, "Programming Flash Image skipped (empty image)\n");
         Logging::print("vFlashDone: Memory image empty, programming skipped\n");
      }
      gdbInOut->sendGdbString("OK");
   }
   else if (strncmp(cmd, "vCont", 5) == 0) {
#ifdef VCONT_SUPPORTED
      doVContCommands(pkt);
#else
      // Not yet supported
      gdbInOut->sendGdbString("");
#endif
   }
   else {
      Logging::print("Unrecognized command:\'%s\'\n", cmd);
      gdbInOut->sendGdbString("");
   }
   return BDM_RC_OK;
}

#define THREAD_STAT "'thread':-1.-1;"

#if (TARGET == CFV1) || (TARGET == CFVx)
#define PC_STAT "11:%08lX"
#elif TARGET == ARM
#define PC_STAT "0F:%08lX"
#endif
#undef PC_STAT
#define PC_STAT ""

//#define REPORT_LONG_LOCATION

static void reportLocation(char mode, int reason) {
   LOGGING_Q;
   char buff[100];
   char *cPtr = buff;

   cPtr += sprintf(buff, "%c%2.2X", mode, reason);
#ifdef REPORT_LONG_LOCATION
#if (TARGET == CFV1)||(TARGET == CFVx)
   static const int regsToReport[] = {17, 15, 14, 16}; // PC, SP, FP, SR
#elif (TARGET == ARM)
   static const int regsToReport[] = {15, 14, 13, 16}; // PC, LR, SP, PSR
#endif
   for (unsigned index=0; index<(sizeof(regsToReport)/sizeof(regsToReport[0])); index++) {
      cPtr += sprintf(cPtr, "%X:", regsToReport[index]);
      cPtr += readReg(regsToReport[index], cPtr);
      *cPtr++ = ';';
   }
#endif
   *cPtr++ = '\0';
   gdbInOut->sendGdbString(buff);
}

USBDM_ErrorCode doGdbCommand(const GdbPacket *pkt) {
   LOGGING_Q;
   unsigned address;
   unsigned numBytes;
   const char *ccptr;
   int type;
   unsigned kind;
   int regNo;
   int value;

//   Logging::print("doGdbCommand()\n");
   if (pkt->isBreak()) {
      if ((runState != running)) {
         Logging::print("Ignoring Break\n");
         reportGdbPrintf(M_INFO, "Ignoring Break as not running\n");
         return BDM_RC_OK;
      }
      Logging::print("Breaking...\n");
      reportGdbPrintf(M_INFO, "Breaking...\n");
      USBDM_Connect();
      USBDM_TargetHalt();
      gdbPollTarget();
      return BDM_RC_OK;
   }
   switch (pkt->buffer[0]) {
   case '!' : // Enable extended mode
      Logging::print("Enable extended mode\n");
      gdbInOut->sendGdbString("OK");
      break;
   case 'R' : // Target reset
      Logging::print("Target Reset\n");
      USBDM_TargetReset((TargetMode_t)(RESET_SPECIAL|RESET_DEFAULT));
      break;
   case 'g' : // 'g' - Read general registers.
//   Reply:
//   -  'XX...' Each byte of register data is described by two hex digits. The bytes
//      with the register are transmitted in target byte order. The size of
//      each register and their position within the 'g' packet are determined
//      by the gdb internal gdbarch functions and gdbarch_register_name.
//   -  'E NN' for an error.
      Logging::print("Read Regs =>\n");
      sendRegs();
      break;
   case 'G' : // 'G XX...' - Write general registers.
//      See [read registers packet] for a description of the XX... data.
//   Reply:
//     - 'OK' for success
//     - 'E NN' for an error
      Logging::print("Write Regs =>\n");
      writeRegs(pkt->buffer+1);
      break;
   case 'm' : // 'm addr,length' - Read memory
      if (sscanf(pkt->buffer, "m%X,%x:", &address, &numBytes) != 2) {
         Logging::print("Illegal cmd format\n");
         gdbInOut->sendErrorMessage(0x01);
      }
      else {
         Logging::print("readMemory [0x%08X..0x%08X]\n", address, address+numBytes-1);
         readMemory(address, numBytes);
      }
//      Read length bytes of memory starting at address addr. Note that addr may
//      not be aligned to any particular boundary.
//      The stub need not use any particular size or alignment when gathering data
//      from memory for the response; even if addr is word-aligned and length is a
//      multiple of the word size, the stub is free to use byte accesses, or not. For
//      this reason, this packet may not be suitable for accessing memory-mapped I/O
//      devices.
//      Reply:
//      'XX...' Memory contents; each byte is transmitted as a two-digit hexadecimal
//      number. The reply may contain fewer bytes than requested if
//      the server was able to read only part of the region of memory.
//      'E NN' NN is errno
      break;
   case 'M' : // 'M addr,length:XX...' - Write memory
      if ((sscanf(pkt->buffer, "M%X,%x:", &address, &numBytes) != 2) ||
          ((ccptr = strchr(pkt->buffer, ':')) == NULL)) {
         Logging::print("Illegal cmd format\n");
         gdbInOut->sendErrorMessage(0x01);
      }
      else {
         Logging::print("writeMemory [0x%08X...0x%08X] %2s...\n", address, address+numBytes-1, ccptr+1);
         writeMemory(ccptr+1, address, numBytes);
      }
//      Write length bytes of memory starting at address addr. XX. . . is the data;
//      each byte is transmitted as a two-digit hexadecimal number.
//      Reply:
//      'OK' for success
//      'E NN' for an error (this includes the case where only part of the data was
//      written).
      break;
   case 'c' : // 'c [addr]' - Continue
      //      Continue. addr is address to resume. If addr is omitted, resume at current
      //      address.
      //      Reply: See [Stop Reply Packets] for the reply specifications.
      if (sscanf(pkt->buffer, "c%X", &address) == 1) {
         // Set PC to address
         address = bigendianToTarget32(address);
         Logging::print("Continue @addr=%X\n", address);
         USBDM_WritePC(address);
      }
      else {
         Logging::print("Continue @PC\n");
      }
      continueTarget();
      runState = running;
      registerBufferSize = 0;
      gdbPollTarget();
      break;
   case 's' :
      // 's' [addr] - Single step.
      //      addr is the address at which to resume. If addr is omitted, resume at same address.
      //      Reply: See [Stop Reply Packets], page for the reply specifications.
      if (sscanf(pkt->buffer, "s%X", &address) > 1) {
         // Set PC to address
         reportGdbPrintf(M_BORINGINFO, "Single step @addr=%X\n", address);
         Logging::print("Single step @addr=%X\n", address);
         USBDM_WritePC(address);
      }
      else {
         reportGdbPrintf(M_BORINGINFO, "Single step @PC\n");
         Logging::print("Single step @PC\n");
      }
      runState = stepping;
      stepTarget(maskInterruptsWhenStepping);
      registerBufferSize = 0;
      gdbPollTarget();
      break;
   case 'Z' :
      // 'z type,addr,kind' - insert/remove breakpoint
      Logging::print("Z - Set breakpoint\n");
      if (sscanf(pkt->buffer, "Z%d,%x,%d", &type, &address, &kind) != 3) {
         Logging::print("Illegal cmd format\n");
         gdbInOut->sendErrorMessage(0x11);
         break;
      }
      if (insertBreakpoint((breakType)type, address, kind)) {
         gdbInOut->sendGdbString("OK");
         reportGdbPrintf(M_BORINGINFO, "Set breakpoint @0x%X\n", address);
      }
      else {
         Logging::print("Failed to set Breakpoint\n");
         reportGdbPrintf(M_ERROR, "Failed to set breakpoint @0x%X\n", address);
         gdbInOut->sendErrorMessage(0x11);
      }
      break;
   case 'z' : // 'z type,addr,kind' - insert/remove breakpoint
      Logging::print("z - Remove breakpoint\n");
      if (sscanf(pkt->buffer, "z%d,%x,%d", &type, &address, &kind) != 3) {
         gdbInOut->sendErrorMessage(0x11);
         break;
      }
      if (removeBreakpoint((breakType)type, address, kind)) {
         reportGdbPrintf(M_BORINGINFO, "Removed breakpoint @0x%X\n", address);
         gdbInOut->sendGdbString("OK");
      }
      else {
         Logging::print("Failed to remove Breakpoint\n");
         reportGdbPrintf(M_ERROR, "Failed to remove breakpoint @0x%X\n", address);
         gdbInOut->sendErrorMessage(0x11);
      }
      break;
   case 'P' :
      // 'P n...=r...' Write register n... with value r.... The register number n
      // is in hexadecimal,
      if (sscanf(pkt->buffer, "P%x=%x", &regNo, &value) != 2) {
         Logging::print("Illegal cmd format\n");
         gdbInOut->sendErrorMessage(0x11);
         break;
      }
//      Logging::print("GDB-P regNo=%x, val=%X\n", regNo, value);
      if (isValidRegister(regNo)) {
         value = bigendianToTarget32(value);
         writeReg(regNo, value);
         gdbInOut->sendGdbString("OK");
      }
      else {
         Logging::print("Illegal register\n");
         gdbInOut->sendErrorMessage(0x11);
      }
      registerBufferSize = 0;
      break;
   case 'p' : // 'p n...' Read register n...
      if (sscanf(pkt->buffer, "p%x", &regNo) != 1) {
         Logging::print("Failed to read register\n");
         gdbInOut->sendErrorMessage(0x11);
         break;
      }
      {
         unsigned char buff[10];
         unsigned size = readReg(regNo, buff);
         gdbInOut->sendGdbHex(buff, size);
      }
//      if (isValidRegister(regNo)) {
//         readReg(regNo, buff);
//         gdbInOut->sendGdbString(buff);
//      }
//      else {
//         gdbInOut->sendErrorMessage(0x11);
//      }
      break;
//   case 'H' : // 'Hc num' Set thread
//      gdbInOut->sendGdbString("OK");
//      break;
   case '?' : // '?' Indicate the reason the target stopped.
      reportLocation('T', TARGET_SIGNAL_TRAP);
      break;
//   case 'T' : // Thread status
//      Logging::print("Thread Status\n");
//      gdbInOut->sendGdbString("OK");
//      break;
   case 'k' : // Kill
      reportGdbPrintf(M_INFO, "Kill command received\n");
      Logging::print("Kill...\n");
      gdbInOut->finish();
      return BDM_RC_OK;
   case 'D' : // Detach
      Logging::print("Detach...\n");
      gdbInOut->sendGdbString("OK");
      break;
   case 'q' : // q commands
   case 'Q' : // Q commands
      doQCommands(pkt);
      break;
   case 'v' : // v commands
      doVCommands(pkt);
      break;
   default : // Unrecognized command
      Logging::print("Unrecognized command:\'%s\'\n", pkt->buffer);
      gdbInOut->sendGdbString("");
      break;
   }
   return BDM_RC_OK;
}

/*
 *   Return target status without polling target
 *
 *   @return Target status
 */
GdbTargetStatus getGdbTargetStatus(void) {

   return gdbTargetStatus;
}

/*!  Check for change in target run state
 *   - Polls target
 *   - Report changes to GDB
 *   - Updates gdbTargetStatus (Global)
 *
 *   @return Target status
 */
GdbTargetStatus gdbPollTarget(void) {
   LOGGING;
//   Logging::print("Polling\n");

   gdbTargetStatus = getTargetStatus();

   if (gdbTargetStatus == T_HALT) {
//      Logging::print("Polling - runState\n");
      switch(runState) {
         case halted :  // halted -> halted
            break;
         case breaking : // user break -> halted
            reportLocation('T', TARGET_SIGNAL_INT);
            readRegs();
            Logging::print("Target has halted (from breaking) @%s\n", getCachedPC());
            reportGdbPrintf(M_INFO, "Target has halted (due to user break)  @%s\n", getCachedPC());
            deactivateBreakpoints();
            checkAndAdjustBreakpointHalt();
            break;
         case stepping : // stepping -> halted
            reportLocation('T', TARGET_SIGNAL_TRAP);
            readRegs();
            Logging::print("Target has halted (from stepping) @%s\n", getCachedPC());
            reportGdbPrintf(M_BORINGINFO, "Target has halted (from stepping)  @%s\n", getCachedPC());
            deactivateBreakpoints();
            checkAndAdjustBreakpointHalt();
            break;
         default:       // ???     -> halted
         case running : // running -> halted
            reportLocation('T', TARGET_SIGNAL_TRAP);
            readRegs();
            Logging::print("Target has halted (from running) @%s\n", getCachedPC());
            reportGdbPrintf(M_INFO, "Target has halted (from running)  @%s\n", getCachedPC());
            deactivateBreakpoints();
            checkAndAdjustBreakpointHalt();
            break;
      }
      runState     = halted;
   }
   else if (gdbTargetStatus == T_SLEEPING) {
      if (runState == halted) {
         reportGdbPrintf(M_INFO, "Target is sleeping\n");
         runState = running;
      }
//      if (lastTargetStatus != targetStatus) {
//         reportGdbPrintf("Sleeping\n");
//      }
   }
   else if (gdbTargetStatus == T_UNKNOWN) {
      // Ignore - results in retry
      reportLocation('T', TARGET_SIGNAL_INT); // breaks!
   }
   else {
      if (runState == halted) {
         runState = running;
      }
//      if (lastTargetStatus != targetStatus) {
//         reportGdbPrintf("Running\n");
//      }
   }
//   lastTargetStatus = targetStatus;

   return gdbTargetStatus;
}

USBDM_ErrorCode dummyCallback(const char *msg, GdbMessageLevel level, USBDM_ErrorCode rc) {

   return BDM_RC_FAIL;
}

//! Handle GDB communication
//!
//! @param gdbInOut       - In/Out from/to GDB
//! @param deviceData     - Selected device
//!
USBDM_ErrorCode gdbHandlerInit(GdbInOut *gdbInOut, DeviceData &deviceData, GdbCallback callBack) {
   LOGGING_E;
   ::gdbInOut      = (GdbInOut *)gdbInOut;
   ::deviceData    = deviceData;
   if (callBack == NULL) {
      callBack = dummyCallback;
   }
   ::gdbCallBackPtr      = callBack;

   initRegisterDescription();

   useFastRegisterRead = true;

   runState = halted;

   // ToDo - fix this hack
   USBDM_ErrorCode rc = usbdmResetTarget();
   if (rc != BDM_RC_OK) {
      return rc;
   }
   rc = initBreakpoints();

   return rc;
}
