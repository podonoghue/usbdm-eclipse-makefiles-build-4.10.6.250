/*
 * clock-MKE04.c
 *
 *  Used for MKE04
 * 
 *  Created on: 04/03/2012
 *      Author: podonoghue
 */
#include "derivative.h" /* include peripheral declarations */
#include "system.h"
#include "clock_configure.h"
#include "utilities.h"

// Some MCUs call OSC_CR0 just OSC_CR
#ifndef OSC0_CR
#define OSC0_CR OSC_CR
#endif

uint32_t SystemCoreClock = SYSTEM_CORE_CLOCK;   // Hz
uint32_t SystemBusClock  = SYSTEM_BUS_CLOCK; // Hz

/*! @brief Sets up the clock out of RESET
 *
 */
void clock_initialise(void) {

#if (CLOCK_MODE == CLOCK_MODE_NONE)
   // No clock setup
#else
   // XTAL/EXTAL Pins
   // Must not enable I2C0, PTB6, PTB7 as conflicting

   // Configure the Crystal Oscillator
   OSC_CR = OSC_CR_OSCEN_M|OSC_CR_OSCSTEN_M|OSC_CR_OSCOS_M|OSC_CR_RANGE_M|OSC_CR_HGO_M;


   // Out of reset ICS is in FEI mode
   // =============================================================

   // Switch from FEI -> FEI/FBI/FEE/FBE
   // =============================================================
#if (OSC_CR_OSCEN_M != 0)
   // Wait for oscillator stable (if used)
   do {
      __asm__("nop");
   } while ((OSC_CR & OSC_CR_OSCINIT_MASK) == 0);
#endif

   // Reset default
   ICS_C2 = ICS_C2_BDIV(1);

   ICS_C1 = ICS_C1_CLKS_M|ICS_C1_RDIV_M|ICS_C1_IREFS_M|ICS_C1_IRCLKEN_M|ICS_C1_IREFSTEN_M;

#if (ICS_C1_IREFS_M == 0)
#define ICS_S_IREFST_M 0
#else
#define ICS_S_IREFST_M ICS_S_IREFST_MASK
#endif

   // Wait for mode change
   do {
      __asm__("nop");
   } while ((ICS_S & ICS_S_IREFST_MASK) != ICS_S_IREFST_M);

   // Wait for S_CLKST to indicating that OUTCLK has switched
   do {
      __asm__("nop");
   } while ((ICS_S & ICS_S_CLKST_MASK) != ICS_S_CLKST(ICS_C1_CLKS_V));

   // Set clock divider
   SIM_CLKDIV = SIM_CLKDIV_OUTDIV1_M|SIM_CLKDIV_OUTDIV2_M|SIM_CLKDIV_OUTDIV3_M;

   //SIM_BUSDIV = SIM_BUSDIV_BUSDIV_M;
   ICS_C2 = (ICS_C2 & ~ICS_C2_BDIV_MASK)|ICS_C2_BDIV_M;

   ICS_C4 = (ICS_C4&~(ICS_C4_LOLIE0_MASK|ICS_C4_CME_MASK))|ICS_C4_LOLIE_M|ICS_C4_CME_M;

#endif
   SystemCoreClockUpdate();
}

/*!
 * @brief Update SystemCoreClock variable
 *
 * Updates the SystemCoreClock variable with current core Clock retrieved from CPU registers.
 */
void SystemCoreClockUpdate(void) {
   switch (ICS_C1&ICS_C1_CLKS_MASK) {
      case ICS_C1_CLKS(0) : // FLL
         if ((ICS_C1&ICS_C1_IREFS_MASK) == 0) {
            int factor = 1<<(10-((ICS_C1&ICS_C1_RDIV_MASK)>>ICS_C1_RDIV_SHIFT));
            SystemCoreClock = SYSTEM_OSCER_CLOCK*factor;
            if ((OSC_CR&OSC_CR_RANGE_MASK) != 0) {
               SystemCoreClock /= (1<<5);
            }
         }
         else {
            SystemCoreClock = SYSTEM_ICSIR_CLOCK*1024;
         }
      break;
      case ICS_C1_CLKS(1) : // Internal Reference Clock
         SystemCoreClock = SYSTEM_ICSIR_CLOCK;
         break;
      case ICS_C1_CLKS(2) : // External Reference Clock
         SystemCoreClock = SYSTEM_OSCER_CLOCK;
         break;
   }
   SystemCoreClock = SystemCoreClock/(1<<((ICS_C2&ICS_C2_BDIV_MASK)>>ICS_C2_BDIV_SHIFT));
   SystemCoreClock = SystemCoreClock/(((SIM_CLKDIV&SIM_CLKDIV_OUTDIV1_MASK)>>SIM_CLKDIV_OUTDIV1_SHIFT)+1);
   SystemBusClock  = SystemCoreClock/(((SIM_CLKDIV&SIM_CLKDIV_OUTDIV2_MASK)>>SIM_CLKDIV_OUTDIV2_SHIFT)+1);
}

