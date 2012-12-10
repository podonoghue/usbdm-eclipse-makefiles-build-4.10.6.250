/*
 * Test.cpp
 *
 *  Created on: 09/09/2012
 *      Author: podonoghue
 */

#include <stdio.h>
#include "USBDM_API.h"
#include "USBDM_MPC_API.h"
#include "USBDM_MPC_API_Private.h"

USBDM_ErrorCode enableEonceTAP();

//! Convenience macro
//!
#define CHECK(x) if((rc = (x)) != BDM_RC_OK) { return rc; }

USBDM_ErrorCode openAndConnect(void) {

   USBDM_ErrorCode rc = BDM_RC_OK;

   CHECK(USBDM_Init());
   unsigned deviceCount;
   CHECK(USBDM_FindDevices(&deviceCount));
   CHECK(USBDM_Open(0));

   // Read default options (may be target dependent)
   USBDM_ExtendedOptions_t options = {sizeof(USBDM_ExtendedOptions_t), T_JTAG};
   CHECK(USBDM_GetDefaultExtendedOptions(&options));

   options.resetDuration         = 100;
   options.resetReleaseInterval  = 200;
   options.resetRecoveryInterval = 200;
   options.targetVdd             = BDM_TARGET_VDD_3V3;
   options.autoReconnect         = AUTOCONNECT_ALWAYS;
   options.interfaceFrequency    = 500;     // kHz only useful for CFVx/ARM/DSC or very old HCS12

   // Set options
   CHECK(USBDM_SetExtendedOptions(&options));

   // Set target - above options are applied (including Power-on-reset if BDM has target-Vdd control)
   CHECK(USBDM_SetTargetType(T_JTAG));

   return BDM_RC_OK;
}

int main(void) {
   FILE *fp = fopen("res.txt", "wt");

   openAndConnect();
   MPC_SetLogFile(fp);
   printf("Starting\n");

   uint32_t idcode;
   readIDCODE(&idcode, true);
   enableEonceTAP();

#define OCR_DR     (1<<0)
#define OCR_WKUP   (1<<2)
#define OCR_FDB    (1<<1)
#define DBCR0_EDM  (1<<31)

   unsigned int dummy;
   USBDM_ControlPins(PIN_RESET_LOW, &dummy);
   writeONCEReg(2, OCR_DR|OCR_WKUP);
   USBDM_ControlPins(PIN_RESET_3STATE, &dummy);
   unsigned long status;
   readONCEStatus(&status);
   writeONCEReg(2, OCR_FDB|OCR_WKUP);

   unsigned long value;
   readONCEReg(0, &value);
   writeONCEReg(20, DBCR0_EDM);
   readONCEReg(20, &value);

   readONCEReg(19, &value);
   writeONCEReg(19, 0xFFFFFFFF);
   readONCEReg(19, &value);

   CpuscrT cpuscr;
   readCPUSCRRegs(&cpuscr);
   readCPUSCRRegs(&cpuscr);

   cpuscr.CTL   = 0x100;
   cpuscr.IR    = 0x101;
   cpuscr.MSR   = 0x102;
   cpuscr.PC    = 0x103;
   cpuscr.WBBRH = 0x104;
   cpuscr.WBBRL = 0x105;
   writeCPUSCRRegs(&cpuscr);

   readCPUSCRRegs(&cpuscr);

   printf("Complete\n");

   USBDM_Close();
   return 0;
}
