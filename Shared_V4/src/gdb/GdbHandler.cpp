/*
 * gdbHandler.cpp
 *
 *  Created on: 06/03/2011
 *      Author: podonoghue
 */
#include <stdio.h>

#include <sys/types.h>
#include <string>
#include "Common.h"
#include "Log.h"
#include "Utils.h"
#include "signals.h"
#include "Names.h"
#include "wxPlugin.h"

using namespace std;

#include "USBDM_API.h"
#if (TARGET == ARM)
#include "ARM_Definitions.h"
#endif

#include "TargetDefines.h"

#include "DeviceData.h"
#include "FlashImage.h"
#include "FlashProgramming.h"

#include "tclInterface.h"
#include "ProgressTimer.h"

#include "GdbInput.h"
#include "GdbOutput.h"
#include "GdbBreakpoints.h"

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

static GdbOutput       *gdbOutput      = NULL;
static GdbInput        *gdbInput       = NULL;
static const GdbPacket *packet         = NULL;
static RunState         runState       = halted;
static unsigned         pollInterval   = 100;
static DeviceData       deviceData;
static bool             ackMode        = true;  // Send ACK to GDB messages
static bool             pendingCommand = false; // Pending mult-part GDB command e.g. qfThreadInfo/qsThreadInfo

static ProgressTimer *progressTimer;

USBDM_ErrorCode usbdmInit(TargetType_t targetType = T_CFV1) {
   LOGGING_Q;
   unsigned int deviceCount;
   unsigned int deviceNum;
   USBDM_ErrorCode rc = USBDM_Init();
   if (rc != BDM_RC_OK) {
      return rc;
   }
   rc = USBDM_FindDevices(&deviceCount);
   Logging::print( "Usb initialized, found %d device(s)\n", deviceCount);
   if (rc != BDM_RC_OK) {
      return rc;
   }
   deviceNum  = 0;
   rc = USBDM_Open(deviceNum);
   if (rc != BDM_RC_OK) {
      Logging::print( "usbdmInit(): Failed to open %s, device #%d\n", getTargetTypeName(targetType), deviceNum);
      return rc;
   }
   Logging::print("Opened %s, device #%d\n", getTargetTypeName(targetType), deviceNum);

   // Set up sensible default since we can't change this (at the moment)
   USBDM_ExtendedOptions_t bdmOptions = {sizeof(USBDM_ExtendedOptions_t), TARGET_TYPE};
   USBDM_GetDefaultExtendedOptions(&bdmOptions);
   bdmOptions.targetVdd                  = BDM_TARGET_VDD_3V3; // BDM_TARGET_VDD_NONE;
   bdmOptions.autoReconnect              = AUTOCONNECT_ALWAYS; // Aggressively auto-connect
   bdmOptions.guessSpeed                 = FALSE;
   bdmOptions.cycleVddOnConnect          = FALSE;
   bdmOptions.cycleVddOnReset            = FALSE;
   bdmOptions.leaveTargetPowered         = FALSE;
   bdmOptions.bdmClockSource             = CS_DEFAULT;
   bdmOptions.useResetSignal             = FALSE;
   bdmOptions.usePSTSignals              = FALSE;
   bdmOptions.interfaceFrequency         = 1000; // 1MHz
   bdmOptions.powerOnRecoveryInterval    = 100;
   bdmOptions.resetDuration              = 100;
   bdmOptions.resetReleaseInterval       = 100;
   bdmOptions.resetRecoveryInterval      = 100;
   rc = USBDM_SetExtendedOptions(&bdmOptions);
   if (rc != BDM_RC_OK) {
      Logging::print("USBDM_SetExtendedOptions() failed\n");
      return rc;
   }
   rc = USBDM_SetTargetType(targetType);
   if (rc != BDM_RC_OK) {
      Logging::print("USBDM_SetTargetType() failed\n");
      return rc;
   }
   USBDM_TargetReset((TargetMode_t)(RESET_DEFAULT|RESET_SPECIAL));
   if (USBDM_Connect() != BDM_RC_OK) {
      Logging::print("Connecting failed - retry\n");
      USBDM_TargetReset((TargetMode_t)(RESET_DEFAULT|RESET_SPECIAL));
      rc = USBDM_Connect();
      if (rc != BDM_RC_OK) {
         Logging::print("USBDM_SetTargetType() failed\n");
         return rc;
      }
   }
   Logging::print( "Success\n", deviceCount);
   return BDM_RC_OK;
}

/* closes currently open device */
int usbdmClose(void) {
   LOGGING;
   Logging::print("Closing the device\n");
   USBDM_Close();
   USBDM_Exit();
   return 0;
}

USBDM_ErrorCode lastError = BDM_RC_OK;
static bool targetConnected = false;

void reportError(USBDM_ErrorCode rc) {
   if ((rc & BDM_RC_ERROR_HANDLED) == 0) {
      displayDialogue(USBDM_GetErrorString(rc), "USBDM GDB Server error", wxOK|wxICON_ERROR);
   }
}

//! Exit GDB Server
//!
void exitProgram(USBDM_ErrorCode rc) {
   LOGGING_Q;
   usbdmClose();
//   fprintf(stderr, "gdbServer - Exiting, rc = %s\n", USBDM_GetErrorString(rc));
   fflush(stdout);
   fflush(stderr);
   if (gdbInput != NULL) {
      gdbInput->kill();
   }
   if (gdbOutput != NULL) {
      gdbOutput->close();
   }
#ifdef LOG
   Logging::print("Exiting, rc = %s\n", USBDM_GetErrorString(rc));
   Logging::closeLogFile();
#endif
   exit((rc==BDM_RC_OK)?0:-1);
}

void reportErrorAndQuit(USBDM_ErrorCode rc) {
   LOGGING;
   int replyCount = 0;
   // Report error to user
   reportError(rc);
   if ((gdbInput != NULL) && (gdbOutput != NULL)) {
      // Wait for GDB to go away
      for (int i = 0; i<50; i++) {
         milliSleep(100);
         Logging::print("Getting GDB pkt\n");
         const GdbPacket *pkt = gdbInput->getGdbPacket();
         if ((pkt==NULL) && gdbInput->isEOF()) {
            Logging::print("EOF\n");
            break;
         }
         if (pkt != NULL) {
            if (ackMode) {
               Logging::print("Sending GDB ACK\n");
               gdbOutput->sendAck();
            }
            Logging::print("Sending GDB Error\n");
            gdbOutput->sendErrorMessage(GdbOutput::E_Fatal, USBDM_GetErrorString(rc));
            replyCount++;

            gdbInput->finish();
         }
         if (replyCount>=3) {
            break;
         }
      }
   }
   exitProgram(rc);
}

void setErrorCode(USBDM_ErrorCode rc) {
   if ((lastError == BDM_RC_OK) && (rc != BDM_RC_OK)) {
      lastError = rc;
   }
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
#define targetToNative16(x)    unchanged16(x)
#define targetToNative32(x)    unchanged32(x)
#define nativeToTarget16(x)    unchanged16(x)
#define nativeToTarget32(x)    unchanged32(x)
#define bigendianToTarget16(x) swap16(x)
#define bigendianToTarget32(x) swap32(x)

#else
#define targetToNative16(x)    swap16(x)
#define targetToNative32(x)    swap32(x)
#define nativeToTarget16(x)    swap16(x)
#define nativeToTarget32(x)    swap32(x)
#define bigendianToTarget16(x) unchanged16(x)
#define bigendianToTarget32(x) unchanged32(x)

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

//! reportStatus - report status to GDB ("O...")
//!
//! @param s          - string describing status
//!
void reportStatus(const char *s, int size=-1) {
   LOGGING_Q;
   gdbOutput->sendGdbHexString("O", s, size);
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
//       Logging::print("FlashProgrammer::setDeviceData() finished\n");
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
static const char targetRegsXML[] =
      "<?xml version=\"1.0\"?>\n"
      "<!DOCTYPE feature SYSTEM \"gdb-target.dtd\">\n"
      "<feature name=\"org.gnu.gdb.coldfire.core\">\n"
      "   <reg name=\"d0\" bitsize=\"32\"/>\n"
      "   <reg name=\"d1\" bitsize=\"32\"/>\n"
      "   <reg name=\"d2\" bitsize=\"32\"/>\n"
      "   <reg name=\"d3\" bitsize=\"32\"/>\n"
      "   <reg name=\"d4\" bitsize=\"32\"/>\n"
      "   <reg name=\"d5\" bitsize=\"32\"/>\n"
      "   <reg name=\"d6\" bitsize=\"32\"/>\n"
      "   <reg name=\"d7\" bitsize=\"32\"/>\n"
      "   <reg name=\"a0\" bitsize=\"32\" type=\"data_ptr\"/>\n"
      "   <reg name=\"a1\" bitsize=\"32\" type=\"data_ptr\"/>\n"
      "   <reg name=\"a2\" bitsize=\"32\" type=\"data_ptr\"/>\n"
      "   <reg name=\"a3\" bitsize=\"32\" type=\"data_ptr\"/>\n"
      "   <reg name=\"a4\" bitsize=\"32\" type=\"data_ptr\"/>\n"
      "   <reg name=\"a5\" bitsize=\"32\" type=\"data_ptr\"/>\n"
      "   <reg name=\"fp\" bitsize=\"32\" type=\"data_ptr\"/>\n"
      "   <reg name=\"sp\" bitsize=\"32\" type=\"data_ptr\"/>\n"
      "   \n"
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
      "   \n"
      "   <reg name=\"ps\" bitsize=\"32\" type=\"ps.type\"/>\n"
      "   <reg name=\"pc\" bitsize=\"32\" type=\"code_ptr\"/>\n"
      "   \n"
      "</feature>\n";
#else
static const char targetRegsXML[] =
   "<?xml version=\"1.0\"?>\n"
   "<!DOCTYPE feature SYSTEM \"gdb-target.dtd\">\n"
   "<feature name=\"org.gnu.gdb.arm.core\" >\n"
   "   <reg name=\"r0\"   bitsize=\"32\" />\n"
   "   <reg name=\"r1\"   bitsize=\"32\" />\n"
   "   <reg name=\"r2\"   bitsize=\"32\" />\n"
   "   <reg name=\"r3\"   bitsize=\"32\" />\n"
   "   <reg name=\"r4\"   bitsize=\"32\" />\n"
   "   <reg name=\"r5\"   bitsize=\"32\" />\n"
   "   <reg name=\"r6\"   bitsize=\"32\" />\n"
   "   <reg name=\"r7\"   bitsize=\"32\" />\n"
   "   <reg name=\"r8\"   bitsize=\"32\" />\n"
   "   <reg name=\"r9\"   bitsize=\"32\" />\n"
   "   <reg name=\"r10\"  bitsize=\"32\" />\n"
   "   <reg name=\"r11\"  bitsize=\"32\" />\n"
   "   <reg name=\"r12\"  bitsize=\"32\" />\n"
   "   <reg name=\"sp\"   bitsize=\"32\" type=\"data_ptr\"/>\n"
   "   <reg name=\"lr\"   bitsize=\"32\" type=\"code_ptr\"/>\n"
   "   <reg name=\"pc\"   bitsize=\"32\" type=\"code_ptr\"/>\n"
#if 1
   "   <reg name=\"cpsr\" bitsize=\"32\" type=\"uint32\"/>\n"
#elif 1
   "   <flags id=\"cpsr.type\" size=\"4\">\n"
   "      <field name=\"N\"      start=\"31\"  end=\"31\" />\n"
   "      <field name=\"Z\"      start=\"30\"  end=\"30\" />\n"
   "      <field name=\"C\"      start=\"29\"  end=\"29\" />\n"
   "      <field name=\"V\"      start=\"28\"  end=\"28\" />\n"
   "      <field name=\"Q\"      start=\"27\"  end=\"27\" />\n"
   "      <field name=\"IT1\"    start=\"26\"  end=\"26\" />\n"
   "      <field name=\"IT0\"    start=\"25\"  end=\"25\" />\n"
   "      <field name=\"T\"      start=\"24\"  end=\"24\" />\n"
   "      <field name=\"IT7\"    start=\"15\"  end=\"15\" />\n"
   "      <field name=\"IT6\"    start=\"14\"  end=\"14\" />\n"
   "      <field name=\"IT5\"    start=\"13\"  end=\"13\" />\n"
   "      <field name=\"IT4\"    start=\"12\"  end=\"12\" />\n"
   "      <field name=\"IT2\"    start=\"11\"  end=\"11\" />\n"
   "      <field name=\"IT3\"    start=\"10\"  end=\"10\" />\n"
   "      <field name=\"E8\"     start=\"8\"   end=\"8\"  />\n"
   "      <field name=\"E7\"     start=\"7\"   end=\"7\"  />\n"
   "      <field name=\"E6\"     start=\"6\"   end=\"6\"  />\n"
   "      <field name=\"E5\"     start=\"5\"   end=\"5\"  />\n"
   "      <field name=\"E4\"     start=\"4\"   end=\"4\"  />\n"
   "      <field name=\"E3\"     start=\"3\"   end=\"3\"  />\n"
   "      <field name=\"E2\"     start=\"2\"   end=\"2\"  />\n"
   "      <field name=\"E1\"     start=\"1\"   end=\"1\"  />\n"
   "      <field name=\"E0\"     start=\"0\"   end=\"0\"  />\n"
   "   </flags>\n"
   "   <reg name=\"cpsr\"      bitsize=\"32\" type=\"cpsr.type\"/>\n"
#else
   "   <flags id=\"flags.type\" size=\"1\">\n"
   "      <field name=\"N\"      start=\"7\"  end=\"7\" />\n"
   "      <field name=\"Z\"      start=\"6\"  end=\"6\" />\n"
   "      <field name=\"C\"      start=\"5\"  end=\"5\" />\n"
   "      <field name=\"V\"      start=\"4\"  end=\"4\" />\n"
   "      <field name=\"Q\"      start=\"3\"  end=\"3\" />\n"
   "      <field name=\"IT1\"    start=\"2\"  end=\"2\" />\n"
   "      <field name=\"IT0\"    start=\"1\"  end=\"1\" />\n"
   "      <field name=\"T\"      start=\"0\"  end=\"0\" />\n"
   "   </flags>\n"
   "   <struct id=\"cpsr.type\">\n"
   "      <field name=\"Except\"   type = \"uint16\"  bitSize=\"10\"   />\n"
   "      <field name=\"\"         type = \"uint8\"   bitSize=\"1\"    />\n"
   "      <field name=\"ICI/IT\"   type = \"uint8\"   bitSize=\"6\"    />\n"
   "      <field name=\"\"         type = \"uint8\"   bitSize=\"8\"    />\n"
   "      <field name=\"Flags\"    type = \"flags.type\" />\n"
   "   </struct>\n"
   "   <reg name=\"cpsr\" bitsize=\"32\" type=\"cpsr.type\"/>\n"
#endif
      "   <reg name=\"msp\"       bitsize=\"32\" type=\"data_ptr\"/>\n"
      "   <reg name=\"psp\"       bitsize=\"32\" type=\"data_ptr\"/>\n"
      "   <struct id=\"misc.type\">\n"
      "      <field name=\"primask\"   type = \"uint8\"    />\n"
      "      <field name=\"basepri\"   type = \"uint8\"    />\n"
      "      <field name=\"faultmask\" type = \"uint8\"    />\n"
      "      <field name=\"control\"   type = \"uint8\"    />\n"
      "   </struct>\n"
      "   <reg name=\"misc\" bitsize=\"32\" type=\"misc.type\"/>\n"
   "</feature>\n"
   ;
#endif

//!
//!
//! Convert a binary value to a HEX char
//!
//! @param num - number o convert (0x0 - 0xF)
//! @return converted char ('0'-'9' or 'A' to 'F') - no error checks!
//!
//static char hexChar(int num) {
//const char chars[] = "0123456789ABCDEF";
//   return chars[num&0x0F];
//}

typedef struct {
   unsigned long value;
   int           size;
} Register_t;

#if (TARGET == ARM)
// Maps GDB register numbers to USBDM register numbers (or -1 is invalid)
int registerMap[] = {
      ARM_RegR0,   ARM_RegR1,   ARM_RegR2,  ARM_RegR3,
      ARM_RegR4,   ARM_RegR5,   ARM_RegR6,  ARM_RegR7,
      ARM_RegR8,   ARM_RegR9,   ARM_RegR10, ARM_RegR11,
      ARM_RegR12,  ARM_RegSP,   ARM_RegLR,  ARM_RegPC, // r0-r12,sp,lr,pc
      ARM_RegxPSR, ARM_RegMSP,  ARM_RegPSP,            // psr, main sp, process sp
      ARM_RegMISC,   // [31:24]=CONTROL,[23:16]=FAULTMASK,[15:8]=BASEPRI,[7:0]=PRIMASK.
};
#elif TARGET == CFV1
unsigned registerMap[] = {
      CFV1_RegD0,CFV1_RegD1,CFV1_RegD2,CFV1_RegD3,
      CFV1_RegD4,CFV1_RegD5,CFV1_RegD6,CFV1_RegD7,
      CFV1_RegA0,CFV1_RegA1,CFV1_RegA2,CFV1_RegA3,
      CFV1_RegA4,CFV1_RegA5,CFV1_RegA6,CFV1_RegA7,
      0x100+CFV1_CRegSR, 0x100+CFV1_CRegPC,         // +0x100 indicates USBDM_ReadCReg
};
#elif TARGET == CFVx
unsigned registerMap[] = {
      CFVx_RegD0,CFVx_RegD1,CFVx_RegD2,CFVx_RegD3,
      CFVx_RegD4,CFVx_RegD5,CFVx_RegD6,CFVx_RegD7,
      CFVx_RegA0,CFVx_RegA1,CFVx_RegA2,CFVx_RegA3,
      CFVx_RegA4,CFVx_RegA5,CFVx_RegA6,CFVx_RegA7,
      0x100+CFVx_CRegSR, 0x100+CFVx_CRegPC,        // +0x100 indicates USBDM_ReadCReg
};
#endif
#define NUMREGISTERS (sizeof(registerMap)/sizeof(registerMap[0]))

bool isValidRegister(unsigned regNo) {
   if (regNo >= sizeof(registerMap)/sizeof(registerMap[0]))
      return false;
   else
      return registerMap[regNo]>=0;
}

//! Read register into string buffer as hex chars
//!
//! @param regNo - number of register to read (GDB numbering)
//! @param cPtr  - ptr to buffer
//!
//! @return number of chars written
//!
//! @note characters are written in target byte order
//!
static int readReg(unsigned regNo, char *cPtr) {
   LOGGING_Q;
   unsigned long regValue;

   if (!isValidRegister(regNo)) {
      Logging::print("reg[%d] => Invalid\n", regNo);
      return sprintf(cPtr, "%08lX", 0xFF000000UL+regNo);
//      return sprintf(cPtr, "12345678");
   }
   int usbdmRegNo = registerMap[regNo];

#if (TARGET == ARM)
   USBDM_ErrorCode rc = USBDM_ReadReg((ARM_Registers_t)usbdmRegNo, &regValue);
   if (rc != BDM_RC_OK) {
      Logging::print("%s(0x%02X) => Failed\n", getARMRegName(usbdmRegNo), usbdmRegNo, regValue);
   }
//   else {
//      Logging::print("%s(0x%02X) => %08lX\n", getARMRegName(usbdmRegNo), usbdmRegNo, regValue);
//   }
   regValue = bigendianToTarget32(regValue);
#elif (TARGET == CFV1)
   if (usbdmRegNo < 0x100) {
      USBDM_ReadReg((CFV1_Registers_t)usbdmRegNo, &regValue);
      Logging::print("%s => %08lX\n", getCFV1RegName(regNo), regValue);
   }
   else {
      USBDM_ReadCReg((CFV1_Registers_t)(usbdmRegNo-0x100), &regValue);
      Logging::print("%s => %08lX\n", getCFV1ControlRegName(regNo), regValue);
   }
#elif(TARGET == CFVx)
   if (usbdmRegNo < 0x100) {
      USBDM_ReadReg((CFV1_Registers_t)usbdmRegNo, &regValue);
      Logging::print("%s => %08lX\n", getCFVxRegName(regNo), regValue);
   }
   else {
      USBDM_ReadCReg((CFV1_Registers_t)(usbdmRegNo-0x100), &regValue);
      Logging::print("%s => %08lX\n", getCFVxControlRegName(regNo), regValue);
   }
#endif
   return sprintf(cPtr, "%0*lX", 8, regValue);
}

//! Read all registers from target
//!
//! @note values are returned in target byte order
//!
static void readRegs(void) {
   LOGGING_Q;
   unsigned regNo;
   char buff[1000];
   char *cPtr = buff;
   for (regNo = 0; regNo<NUMREGISTERS; regNo++) {
      cPtr += readReg(regNo, cPtr);
   }
//   for (regNo = NUMREGISTERS; regNo<(NUMREGISTERS+10); regNo++) {
//      cPtr += readReg(regNo, cPtr);
//   }
   *cPtr = '\0';
   gdbOutput->sendGdbString(buff);
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

   for (regNo = 0; regNo<NUMREGISTERS; regNo++) {
      if (!hexToInt32(ccPtr, &regValue))
         break;
      ccPtr += 8;
      regValue = bigendianToTarget32(regValue);
      writeReg(regNo, regValue);
   }
   gdbOutput->sendGdbString("OK");
}

static void readMemory(uint32_t address, uint32_t numBytes) {
   LOGGING_Q;
   unsigned char buff[1000] = {0};

//   Logging::print("readMemory(addr=%X, size=%X)\n", address, numBytes);
   if (USBDM_ReadMemory(1, numBytes, address, buff) != BDM_RC_OK) {
      // Ignore errors
      memset(buff, 0xAA, numBytes);
//      gdbOutput->sendErrorMessage(0x11);
//      return;
   }
   gdbOutput->sendGdbHex(buff, numBytes);
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

   Logging::print("writeMemory(addr=%X, size=%X)\n", address, numBytes);
   convertFromHex(numBytes, ccPtr, buff);
   USBDM_WriteMemory(1, numBytes, address, buff);
   gdbOutput->sendGdbString("OK");
}

#define T_UNKNOWN (1<<0) // Unknown - error
#define T_RUNNING (1<<1) // Executing
#define T_HALT    (1<<2) // Debug halt
#define T_SLEEP   (1<<3) // Low power sleep

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

//! Get target status
//!
//! @return status - status of target T_UNKNOWN/T_SLEEP/T_HALT/T_RUNNING
//!
static int getTargetStatus(void) {
   LOGGING_Q;
   USBDM_ErrorCode BDMrc;
   static int lastStatus;
   static int failureCount = 0;
   int status;

   unsigned long dhcsr;
   BDMrc = armReadMemoryWord(DHCSR, &dhcsr);
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
   if (BDMrc != BDM_RC_OK) {
      failureCount++;
      Logging::print("Error %s\n", USBDM_GetErrorString(BDMrc));
      status = T_UNKNOWN;
   }
   else {
      // Reset on OK status
      failureCount = 0;
      if ((dhcsr & DHCSR_S_SLEEP) != 0) {
         // Stopped - low power sleep, treated as special
         status = T_SLEEP;
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
   }
   lastStatus = status;
   return status;
}
#elif TARGET == CFV1
//! Get target status
//!
//! @param status - status from target T_UNKNOWN/T_SLEEP/T_HALT/T_RUNNING
//!
static int getTargetStatus (void) {
   LOGGING_Q;
   static int lastStatus;
   int status;

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
//! Get target status
//!
//! @param status - status from target T_UNKNOWN/T_SLEEP/T_HALT/T_RUNNING
//!
static int getTargetStatus(void) {
   LOGGING_Q;
   static int lastStatus;
   int status;

   USBDM_ErrorCode rc = USBDM_Connect();
   if (rc != BDM_RC_OK) {
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
   gdbOutput->putGdbPreamble();
   if (offset >= bufferSize) {
      gdbOutput->putGdbString("l");
   }
   else {
      if (size > (bufferSize-offset)) {
         // Remainder fits in this pkt
         size = bufferSize-offset;
         gdbOutput->putGdbChar('l');
      }
      else {
         // More pkts to follow
         gdbOutput->putGdbChar('m');
      }
      gdbOutput->putGdbString(buffer+offset, size);
   }
   gdbOutput->sendGdbBuffer();
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
      gdbOutput->sendGdbString(buff);
   }
//   else if (strncmp(cmd, "qC", sizeof("qC")-1) == 0) {
//      gdbOutput->sendGdbString(""); //("QC-1");
//   }
//   else if (strncmp(cmd, "qfThreadInfo", sizeof("qfThreadInfo")-1) == 0) {
//      gdbOutput->sendGdbString("m1"); //("m0");
//      pendingCommand = true;
//   }
//   else if (strncmp(cmd, "qsThreadInfo", sizeof("qsThreadInfo")-1) == 0) {
//      gdbOutput->sendGdbString("l");
//   }
//   else if (strncmp(cmd, "qThreadExtraInfo", sizeof("qThreadExtraInfo")-1) == 0) {
//      gdbOutput->sendGdbHexString(NULL, "Runnable");
//   }
   else if (strncmp(cmd, "qAttached", sizeof("qAttached")-1) == 0) {
      Logging::print("qAttached\n");
      gdbOutput->sendGdbString("0");
   }
   else if (strncmp(cmd, "QStartNoAckMode", sizeof("QStartNoAckMode")-1) == 0) {
      Logging::print("QStartNoAckMode\n");
      gdbOutput->sendGdbString("OK");
      ackMode = false;
   }
//   else if (strncmp(cmd, "qTStatus", sizeof("qTStatus")-1) == 0) {
//      gdbOutput->sendGdbString("T0");
//   }
   else if (strncmp(cmd, "qOffsets", sizeof("qOffsets")-1) == 0) {
      Logging::print("qOffsets\n");
//      gdbOutput->sendGdbString("TextSeg=08000000;DataSeg=20000000");
#if (TARGET == CFV1) || (TARGET == CFVx)
      gdbOutput->sendGdbString("Text=0;Data=0;Bss=0");
#elif (TARGET == ARM)
      gdbOutput->sendGdbString("TextSeg=0000000;DataSeg=00000000");
#endif
   }
   else if (strncmp(cmd, "qXfer:memory-map:read::", sizeof("qXfer:memory-map:read::")-1) == 0) {
      if (sscanf(cmd,"qXfer:memory-map:read::%X,%X",&offset, &size) != 2) {
         Logging::print("Ill formed:\'%s\'", cmd);
         gdbOutput->sendGdbString("");
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
      if (sscanf(cmd,"qXfer:features:read:target.xml:%X,%X",&offset, &size) != 2) {
         Logging::print("Ill formed:\'%s\'", cmd);
         gdbOutput->sendGdbString("");
      }
      else {
         Logging::print("qXfer:features:read:target.xml:%X:%X\n", offset, size);
         sendXML(size, offset, targetXML, sizeof(targetXML));
      }
   }
   else if (strncmp(cmd, "qXfer:features:read:targetRegs.xml:", sizeof("qXfer:features:read:targetRegs.xml:")-1) == 0) {
      if (sscanf(cmd,"qXfer:features:read:targetRegs.xml:%X,%X",&offset, &size) != 2) {
         Logging::print("Ill formed:\'%s\'", cmd);
         gdbOutput->sendGdbString("");
      }
      else {
         Logging::print("qXfer:features:read:targetRegs.xml:%X:%X\n", offset, size);
         sendXML(size, offset, targetRegsXML, sizeof(targetRegsXML));
      }
   }
   else {
      Logging::print("Unrecognized command:\'%s\'\n", cmd);
      gdbOutput->sendGdbString("");
   }
   return BDM_RC_OK;
}

static USBDM_ErrorCode programImage(FlashImage *flashImage) {
   LOGGING;
   USBDM_ErrorCode rc;
   FlashProgrammer flashProgrammer;

   deviceData.setEraseOption(DeviceData::eraseMass);
   deviceData.setSecurity(SEC_SMART);
   deviceData.setClockTrimFreq(0);
   deviceData.setClockTrimNVAddress(0);
   rc = flashProgrammer.setDeviceData(deviceData);
   if (rc != PROGRAMMING_RC_OK) {
      return rc;
   }
   rc = flashProgrammer.programFlash(flashImage);

   // Initialize the target after programming
   flashProgrammer.resetAndConnectTarget();

   if (rc != PROGRAMMING_RC_OK) {
      Logging::print("programImage() - failed, rc = %s\n", USBDM_GetErrorString(rc));
      return rc;
   }
   Logging::print("programImage() - Complete\n");
   return BDM_RC_OK;
}

//! Handle 'v...' commands
//!
static USBDM_ErrorCode doVCommands(const GdbPacket *pkt) {
   LOGGING;
   int address, length;
   const char *cmd = pkt->buffer;

   if (strncmp(cmd, "vFlashErase", 11) == 0) {
      // vFlashErase:addr,length
      if (sscanf(cmd, "vFlashErase:%x,%x", &address, &length) != 2) {
         gdbOutput->sendErrorMessage(0x11);
      }
      else {
         Logging::print("vFlashErase:0x%X:0x%X\n", address, length);
         gdbOutput->sendGdbString("OK");
      }
   }
   else if (strncmp(cmd, "vFlashWrite", 11) == 0) {
      // vFlashWrite:addr:XX...
      if (sscanf(cmd, "vFlashWrite:%x:", &address) != 1) {
         Logging::print(" vFlashWrite:error:\n");
         gdbOutput->sendErrorMessage(0x11);
      }
      else {
         Logging::print("vFlashWrite:0x%X:\n", address);
         if (flashImage == NULL) {
            flashImage = new FlashImage();
         }
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
         Logging::printq("\n");
         gdbOutput->sendGdbString("OK");
      }
   }
   else if (strncmp(cmd, "vFlashDone", 10) == 0) {
      // vFlashDone
      Logging::print("vFlashDone\n");
      if (flashImage != NULL) {
         USBDM_ErrorCode rc = programImage(flashImage);
         delete flashImage;
         if (rc != PROGRAMMING_RC_OK) {
            Logging::print("vFlashDone: Programming failed, rc=%s\n", USBDM_GetErrorString(rc));
//            gdbOutput->sendErrorMessage(0x11);
            gdbOutput->sendErrorMessage(gdbOutput->E_Fatal, "Flash programming failed");
            reportErrorAndQuit(rc);
            return rc;
         }
         else {
            Logging::print("vFlashDone: Programming complete\n");
         }
      }
      else {
         Logging::print("vFlashDone: Memory image empty, programming skipped\n");
      }
      gdbOutput->sendGdbString("OK");
   }
   else if (strncmp(cmd, "vCont", sizeof("vCont")) == 0) {
      // Not yet supported
      gdbOutput->sendGdbString("");
   }
   else {
      Logging::print("Unrecognized command:\'%s\'\n", cmd);
      gdbOutput->sendGdbString("");
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

static void reportLocation(char mode, int reason) {
   LOGGING_Q;
   char buff[100];
   char *cPtr = buff;

   cPtr += sprintf(buff, "%c%2.2X", mode, reason);
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
   *cPtr++ = '\0';
   gdbOutput->sendGdbString(buff);
}

static USBDM_ErrorCode doGdbCommand(const GdbPacket *pkt) {
   LOGGING_Q;
   unsigned address;
   unsigned numBytes;
   const char *ccptr;
   int type;
   unsigned kind;
   int regNo;
   int value;
   char buff[100] = {0};

//   Logging::print("doGdbCommand()\n");
   if (pkt->isBreak()) {
      Logging::print("Break......\n");
      USBDM_Connect();
      USBDM_TargetHalt();
      runState = breaking;
      return BDM_RC_OK;
   }
   switch (pkt->buffer[0]) {
   case '!' : // Enable extended mode
      Logging::print("Enable extended mode\n");
      gdbOutput->sendGdbString("OK");
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
      readRegs();
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
         gdbOutput->sendErrorMessage(0x01);
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
         gdbOutput->sendErrorMessage(0x01);
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
      if (atMemoryBreakpoint()) {
         // Do 1 step before installing memory breakpoints
         Logging::print("Continue - stepping one instruction...\n");
         USBDM_TargetStep();
      }
      activateBreakpoints();
      Logging::print("Continue - executing...\n");
      USBDM_TargetGo();
      runState = running;
      pollInterval = 1; // Poll fast
      break;
   case 's' : // 's' [addr] - Single step.
      if (sscanf(pkt->buffer, "s%X", &address) > 1) {
         // Set PC to address
//         bigendianToTarget32(address);
         Logging::print("Single step @addr=%X\n", address);
         USBDM_WritePC(address);
      }
      else {
         Logging::print("Single step @PC\n");
      }
      runState = stepping;
      pollInterval = 1; // Poll fast
      USBDM_TargetStep();
//      addr is the address at which to resume. If addr is omitted, resume at same address.
//      Reply: See [Stop Reply Packets], page for the reply specifications.
      break;
   case 'Z' : // 'z type,addr,kind' - insert/remove breakpoint
      Logging::print("Z - Set breakpoint\n");
      if (sscanf(pkt->buffer, "Z%d,%x,%d", &type, &address, &kind) != 3) {
         Logging::print("Illegal cmd format\n");
         gdbOutput->sendErrorMessage(0x11);
         break;
      }
      if (insertBreakpoint((breakType)type, address, kind)) {
         gdbOutput->sendGdbString("OK");
      }
      else {
         Logging::print("Failed to set Breakpoint\n");
         gdbOutput->sendErrorMessage(0x11);
      }
      break;
   case 'z' : // 'z type,addr,kind' - insert/remove breakpoint
      Logging::print("z - Remove breakpoint\n");
      if (sscanf(pkt->buffer, "z%d,%x,%d", &type, &address, &kind) != 3) {
         gdbOutput->sendErrorMessage(0x11);
         break;
      }
      if (removeBreakpoint((breakType)type, address, kind)) {
         gdbOutput->sendGdbString("OK");
      }
      else {
         Logging::print("Failed to remove Breakpoint\n");
         gdbOutput->sendErrorMessage(0x11);
      }
      break;
   case 'P' :
      // 'P n...=r...' Write register n... with value r.... The register number n
      // is in hexadecimal,
      if (sscanf(pkt->buffer, "P%x=%x", &regNo, &value) != 2) {
         Logging::print("Illegal cmd format\n");
         gdbOutput->sendErrorMessage(0x11);
         break;
      }
//      Logging::print("GDB-P regNo=%x, val=%X\n", regNo, value);
      if (isValidRegister(regNo)) {
         value = bigendianToTarget32(value);
         writeReg(regNo, value);
         gdbOutput->sendGdbString("OK");
      }
      else {
         Logging::print("Illegal register\n");
         gdbOutput->sendErrorMessage(0x11);
      }
      break;
   case 'p' : // 'p n...' Read register n...
      if (sscanf(pkt->buffer, "p%x", &regNo) != 1) {
         Logging::print("Failed to read register\n");
         gdbOutput->sendErrorMessage(0x11);
         break;
      }
      readReg(regNo, buff);
      gdbOutput->sendGdbString(buff);
//      if (isValidRegister(regNo)) {
//         readReg(regNo, buff);
//         gdbOutput->sendGdbString(buff);
//      }
//      else {
//         gdbOutput->sendErrorMessage(0x11);
//      }
      break;
//   case 'H' : // 'Hc num' Set thread
//      gdbOutput->sendGdbString("OK");
//      break;
   case '?' : // '?' Indicate the reason the target runState.
//      The reply is the same as for step and continue. This packet has a special interpretation
//      when the target is in non-stop mode;
      if (!targetConnected) {
         USBDM_ErrorCode rc = usbdmInit(TARGET_TYPE);
         Logging::print("Initial connect to target = %f\n", progressTimer->elapsedTime());
         if (rc != BDM_RC_OK) {
            gdbOutput->sendErrorMessage(gdbOutput->E_Fatal, "Target connection failed");
            reportErrorAndQuit(rc);
            return rc;
         }
         targetConnected = true;
      }
      reportLocation('T', TARGET_SIGNAL_TRAP);
      break;
//   case 'T' : // Thread status
//      Logging::print("Thread Status\n");
//      gdbOutput->sendGdbString("OK");
//      break;
   case 'k' : // Kill
      Logging::print("Kill...\n");
      return BDM_RC_OK;
   case 'D' : // Detach
      Logging::print("Detach...\n");
      gdbOutput->sendGdbString("OK");
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
      gdbOutput->sendGdbString("");
      break;
   }
   return BDM_RC_OK;
}

static USBDM_ErrorCode gdbLoop(void) {
   LOGGING;
   unsigned pollCount = 0;
   USBDM_ErrorCode rc;
   Logging::print("gdbLoop()...\n");
   do {
      do {
         packet = gdbInput->getGdbPacket();
         if (packet != NULL) {
   //         Logging::print("After getGdbPacket, Time = %f\n", progressTimer->elapsedTime());
            pendingCommand = false;
            if (ackMode) {
               gdbOutput->sendAck();
            }
            rc = doGdbCommand(packet);
            if (rc != BDM_RC_OK) {
               return rc;
            }
         }
         else {
            if (gdbInput->isEOF()) {
               return BDM_RC_OK;
            }
         }
      } while (packet != NULL);
//      Logging::print("gdbLoop() - polling\n");
      milliSleep(1);
      if (targetConnected && !pendingCommand && (pollCount++ >= pollInterval)) {
         pollCount = 0;
         static int lastTargetStatus = -1;
         int targetStatus = getTargetStatus();
         if (targetStatus == T_HALT) {
//            Logging::print("Polling - runState\n");
            switch(runState) {
            case halted :  // ??? -> halted
               break;
            case breaking : // user break -> halted
               Logging::print("Target has halted (breaking)\n");
               deactivateBreakpoints();
               checkAndAdjustBreakpointHalt();
               reportLocation('T', TARGET_SIGNAL_INT);
               break;
            case stepping : // stepping -> halted
               Logging::print("Target has halted (stepping)\n");
               deactivateBreakpoints();
               checkAndAdjustBreakpointHalt();
               reportLocation('T', TARGET_SIGNAL_TRAP);
               break;
            default:       // ???     -> halted
            case running : // running -> halted
               Logging::print("Target has halted (running)\n");
               deactivateBreakpoints();
               checkAndAdjustBreakpointHalt();
               reportLocation('T', TARGET_SIGNAL_TRAP);
               break;
            }
            runState     = halted;
            pollInterval = 1000; // Slow poll when running
         }
         else if (targetStatus == T_SLEEP) {
            if (runState == halted) {
               runState = running;
            }
//            if (lastTargetStatus != targetStatus) {
//               reportStatus("Sleeping\n");
//            }
            pollInterval = 10; // Poll fast
         }
         else {
//            Logging::print("Polling - running\n");
            if (runState == halted) {
               runState = running;
            }
//            if (lastTargetStatus != targetStatus) {
//               reportStatus("Running\n");
//            }
            pollInterval = 10; // Poll fast
         }
         lastTargetStatus = targetStatus;
      }
   } while (true);
   Logging::print("gdbLoop() - Exiting GDB Loop\n");
}

//! Handle GDB communication
//!
//! @param gdbInput       - Input from GDB
//! @param gdbOutput      - Output to GDB
//! @param deviceData     - Selected device
//! @param progressTimer  - Progress timer commenced at start of program
//!
void handleGdb(GdbInput *gdbInput, GdbOutput *gdbOutput, DeviceData &deviceData, ProgressTimer *progressTimer) {
   LOGGING_E;
//   TclInterface *tclInterface = new TclInterface(TARGET_TYPE, &deviceData);
//   if (tclInterface == NULL) {
//      Logging::print("Failed to create TCL interpreter)\n");
//      return;
//   }
   ::gdbInput      = gdbInput;
   ::gdbOutput     = gdbOutput;
   ::deviceData    = deviceData;
   ::progressTimer = progressTimer;
   clearAllBreakpoints();
   gdbLoop();
//   delete tclInterface;
}
