/*
 * clockMK64M12.c
 *
 *  Used for MK64M12
 * 
 *  Created on: 04/03/2012
 *      Author: podonoghue
 */
#include "string.h"
#include "derivative.h" /* include peripheral declarations */
#include "clock.h"
#include "clock_private.h"
#include "utilities.h"
#include "stdbool.h"

// Some MCUs call OSC_CR0 just OSC_CR
#ifndef OSC0_CR
#define OSC0_CR OSC_CR
#endif

uint32_t SystemCoreClock = SYSTEM_CORE_CLOCK;   // Hz
uint32_t SystemBusClock  = SYSTEM_BUS_CLOCK; // Hz

/*! Sets up the clock out of RESET
 *!
 */
void clock_initialise(void) {

#if (CLOCK_MODE == CLOCK_MODE_NONE)
   // No clock setup
#else
   // XTAL/EXTAL Pins
   SIM_SCGC5  |= SIM_SCGC5_PORTA_MASK;
   PORTA_PCR18 = PORT_PCR_MUX(0);
   PORTA_PCR19 = PORT_PCR_MUX(0);

   // Configure the Crystal Oscillator
   OSC0_CR = OSC_CR_ERCLKEN_M|OSC_CR_EREFSTEN_M|OSC_CR_SCP_M;

#if (MCG_C7_OSCSEL_V == 1)
   SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;

   // Configure the RTC Crystal Oscillator
   RTC_CR = RTC_CR_SCP_M|RTC_CR_CLKO_M|RTC_CR_OSCE_M|RTC_CR_UM_M|RTC_CR_SUP_M|RTC_CR_WPE_M;
#endif

#if (MCG_C7_OSCSEL_V == 2)
   // Note IRC48M Internal Oscillator automatically enable if MCG_C7_OSCSEL = 2
   SIM_SCGC4 |= SIM_SCGC4_USBOTG_MASK;
   USB0_CLK_RECOVER_IRC_EN = USB0_CLK_RECOVER_IRC_EN_IRC_EN_MASK|USB0_CLK_RECOVER_IRC_EN_REG_EN_MASK;
#endif

   // Select OSCCLK Source
   MCG_C7 = MCG_C7_OSCSEL_M; // OSCSEL = 0,1,2 -> XTAL/XTAL32/IRC48M

   // Fast Internal Clock divider
   MCG_SC = MCG_SC_FCRDIV_M;

   // Out of reset MCG is in FEI mode
   // =============================================================

   // Set conservative SIM clock dividers BEFORE switching to ensure the clock speed remain within specification
   SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1(3) | SIM_CLKDIV1_OUTDIV2(7) | SIM_CLKDIV1_OUTDIV3(3) | SIM_CLKDIV1_OUTDIV4(7);

   // Switch from FEI -> FEI/FBI/FEE/FBE
   // =============================================================

   // Set up crystal or external clock source
   MCG_C2 = 
            MCG_C2_LOCRE0_M     | // LOCRE0 = 0,1   -> Loss of clock reset enable
            MCG_C2_RANGE0_M     | // RANGE0 = 0,1,2 -> Oscillator low/high/very high clock range
            MCG_C2_HGO0_M       | // HGO0   = 0,1   -> Oscillator low power/high gain
            MCG_C2_EREFS0_M     | // EREFS0 = 0,1   -> Select external clock/crystal oscillator
            MCG_C2_IRCS_M;        // IRCS   = 0,1   -> Select slow/fast internal clock for internal reference

   // Set up RTC clock monitor
   MCG_C8 = MCG_C8_LOCRE1_M |    // LOCRE1 = 0,1 -> Loss of Lock Reset enable
            MCG_C8_CME1_M;       // CME1   = 0,1 -> Clock monitor enable

#if ((CLOCK_MODE == CLOCK_MODE_FEI) || (CLOCK_MODE == CLOCK_MODE_FBI) || (CLOCK_MODE == CLOCK_MODE_BLPI) )
   // Transition via FBI
   //=====================================
#define BYPASS (1) // CLKS value used while FLL locks
   MCG_C1 =  MCG_C1_CLKS(BYPASS)     | // CLKS     = X     -> External reference source while PLL locks
             MCG_C1_FRDIV_M          | // FRDIV    = N     -> XTAL/2^n ~ 31.25 kHz
             MCG_C1_IREFS_M          | // IREFS    = 0,1   -> External/Slow IRC for FLL source
             MCG_C1_IRCLKEN_M        | // IRCLKEN  = 0,1   -> IRCLK disable/enable
             MCG_C1_IREFSTEN_M;        // IREFSTEN = 0,1   -> Internal reference enabled in STOP mode

   // Wait for S_IREFST to indicate FLL Reference has switched
   do {
      __asm__("nop");
   } while ((MCG_S & MCG_S_IREFST_MASK) != (MCG_C1_IREFS_V<<MCG_S_IREFST_SHIFT));

   // Wait for S_CLKST to indicating that OUTCLK has switched to bypass PLL/FLL
   do {
      __asm__("nop");
   } while ((MCG_S & MCG_S_CLKST_MASK) != MCG_S_CLKST(BYPASS));

   // Set FLL Parameters
   MCG_C4 = (MCG_C4&~(MCG_C4_DMX32_MASK|MCG_C4_DRST_DRS_MASK))|MCG_C4_DMX32_M|MCG_C4_DRST_DRS_M;
#endif

#if ((CLOCK_MODE == CLOCK_MODE_FBE) || (CLOCK_MODE == CLOCK_MODE_FEE) || (CLOCK_MODE == CLOCK_MODE_PLBE) || (CLOCK_MODE == CLOCK_MODE_PBE) || (CLOCK_MODE == CLOCK_MODE_PEE))

   // Transition via FBE
   //=====================================
#define BYPASS (2) // CLKS value used while PLL locks
   MCG_C1 =  MCG_C1_CLKS(BYPASS)     | // CLKS     = 2     -> External reference source while PLL locks
             MCG_C1_FRDIV_M          | // FRDIV    = N     -> XTAL/2^n ~ 31.25 kHz
             MCG_C1_IREFS_M          | // IREFS    = 0,1   -> External/Slow IRC for FLL source
             MCG_C1_IRCLKEN_M        | // IRCLKEN  = 0,1   -> IRCLK disable/enable
             MCG_C1_IREFSTEN_M;        // IREFSTEN = 0,1   -> Internal reference enabled in STOP mode

#if (MCG_C2_EREFS_V != 0)
   // Wait for oscillator stable (if used)
   do {
      __asm__("nop");
   } while ((MCG_S & MCG_S_OSCINIT0_MASK) == 0);
#endif

   // Wait for S_IREFST to indicate FLL Reference has switched
   do {
      __asm__("nop");
   } while ((MCG_S & MCG_S_IREFST_MASK) != (MCG_C1_IREFS_V<<MCG_S_IREFST_SHIFT));

   // Wait for S_CLKST to indicating that OUTCLK has switched to bypass PLL/FLL
   do {
      __asm__("nop");
   } while ((MCG_S & MCG_S_CLKST_MASK) != MCG_S_CLKST(BYPASS));

   // Set FLL Parameters
   MCG_C4 = (MCG_C4&~(MCG_C4_DMX32_MASK|MCG_C4_DRST_DRS_MASK))|MCG_C4_DMX32_M|MCG_C4_DRST_DRS_M;
#endif

#if ((CLOCK_MODE == CLOCK_MODE_PBE) || (CLOCK_MODE == CLOCK_MODE_PEE))

   // Configure PLL Reference Frequency
   // =============================================================
   MCG_C5 =  MCG_C5_PLLCLKEN0_M    |  // PLLCLKEN = 0,1 -> PLL -/enabled (irrespective of PLLS)
             MCG_C5_PLLSTEN0_M     |  // PLLSTEN0 = 0,1 -> disabled/enabled in normal stop mode
             MCG_C5_PRDIV0_M;         // PRDIV0   = N   -> PLL divider so PLL Ref. Freq. = 2-4 MHz

   // Transition via PBE
   // =============================================================
   MCG_C6 = MCG_C6_LOLIE0_M    |
            MCG_C6_PLLS_M      |  // PLLS  = 0,1 -> Enable PLL
            MCG_C6_CME0_M      |  // CME0  = 0,1 -> Disable/enable clock monitor
            MCG_C6_VDIV0_M;       // VDIV0 = N   -> PLL Multiplication factor

   // Wait for PLL to lock
   do {
      __asm__("nop");
   } while((MCG_S & MCG_S_LOCK0_MASK) == 0);

   // Wait until PLLS clock source changes to the PLL clock out
   do {
      __asm__("nop");
   } while((MCG_S & MCG_S_PLLST_MASK) == 0);
#endif

#if ((CLOCK_MODE == CLOCK_MODE_FEI) || (CLOCK_MODE == CLOCK_MODE_FEE))
   // Wait for FLL to lock
   do {
      __asm__("nop");
   } while ((MCG_C4&MCG_C4_DRST_DRS_MASK) != MCG_C4_DRST_DRS_M);
#endif

   // Select FEI/FBI/FEE/FBE/PBE/PEE clock mode
   MCG_C1 =  MCG_C1_CLKS_M       | // CLKS     = 0,1,2 -> Select FLL/IRCSCLK/ERCLK
             MCG_C1_FRDIV_M      | // FRDIV    = N     -> XTAL/2^n ~ 31.25 kHz
             MCG_C1_IREFS_M      | // IREFS    = 0,1   -> External/Slow IRC for FLL source
             MCG_C1_IRCLKEN_M    | // IRCLKEN  = 0,1   -> IRCLK disable/enable
             MCG_C1_IREFSTEN_M;    // IREFSTEN = 0,1   -> Internal reference enabled in STOP mode

   // Wait for mode change
   do {
      __asm__("nop");
   } while ((MCG_S & MCG_S_IREFST_MASK) != (MCG_C1_IREFS_V<<MCG_S_IREFST_SHIFT));

#if defined (MCG_C6_PLLS_V) && (MCG_C1_CLKS_V == 0) // FLL or PLL
#define MCG_S_CLKST_M MCG_S_CLKST(MCG_C6_PLLS_V?3:0)
#else
   #define MCG_S_CLKST_M MCG_S_CLKST(MCG_C1_CLKS_V)
#endif

   // Wait for S_CLKST to indicating that OUTCLK has switched
   do {
      __asm__("nop");
   } while ((MCG_S & MCG_S_CLKST_MASK) != MCG_S_CLKST_M);

   // Set the SIM _CLKDIV dividers
   SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1_M | SIM_CLKDIV1_OUTDIV2_M | SIM_CLKDIV1_OUTDIV3_M | SIM_CLKDIV1_OUTDIV4_M;

#if (CLOCK_MODE == CLOCK_MODE_BLPE) || (CLOCK_MODE == CLOCK_MODE_BLPI)
   // Select BLPE/BLPI clock mode
   MCG_C2 =
            MCG_C2_LOCRE0_M      | // LOCRE0 = 0,1   -> Loss of clock reset
            MCG_C2_RANGE0_M      | // RANGE0 = 0,1,2 -> Oscillator low/high/very high clock range
            MCG_C2_HGO0_M        | // HGO0   = 0,1   -> Oscillator low power/high gain
            MCG_C2_EREFS0_M      | // EREFS0 = 0,1   -> Select external clock/crystal oscillator
            MCG_C2_LP_M          | // LP     = 0,1   -> Select FLL enabled/disabled in bypass mode
            MCG_C2_IRCS_M;         // IRCS   = 0,1   -> Select slow/fast internal clock for internal reference

#endif // (CLOCK_MODE == CLOCK_MODE_BLPE) || (CLOCK_MODE == CLOCK_MODE_BLPI)
#endif // (CLOCK_MODE == CLOCK_MODE_NONE)

   // Basic clock multiplexing
#if defined(MCU_MK20D5) || defined(MCU_MK20D7) || defined(MCU_MK40D10) || defined(MCU_MK40DZ10)
   // Peripheral clock choice (incl. USB), USBCLK = MCGCLK
   SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_M    | // PLL rather than FLL for peripheral clock
                SIM_SOPT2_USBSRC_MASK;     // MCGPLLCLK/2 Source as USB clock (48MHz req.)
   SIM_SOPT1 = (SIM_SOPT1&~SIM_SOPT1_OSC32KSEL_MASK)|SIM_SOPT1_OSC32KSEL_M; // ERCLK32K source
#elif defined(MCU_MK60D10) || defined(MCU_MK60DZ10)
   // Peripheral clock choice (incl. USB), USBCLK = MCGCLK
   SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK | // PLL rather than FLL for peripheral clock
                SIM_SOPT2_USBSRC_MASK;     // MCGPLLCLK/2 Source as USB clock (48MHz req.)
#elif defined(MCU_MKL24Z4) || defined(MCU_MKL25Z4) || defined(MCU_MKL26Z4) || defined(MCU_MKL46Z4)
   SIM_SOPT2 = SIM_SOPT2_UART0SRC_M      | // UART0 clock - 0,1,2,3 -> Disabled, (MCGFLLCLK, MCGPLLCLK/2),  OSCERCLK, MCGIRCLK
               SIM_SOPT2_TPMSRC_M        | // TPM clock - 0,1,2,3 -> Disabled, (MCGFLLCLK, MCGPLLCLK/2),  OSCERCLK, MCGIRCLK
               SIM_SOPT2_PLLFLLSEL_M     | // Peripheral clock - 0,1 -> MCGFLLCLK,MCGPLLCLK/2
               SIM_SOPT2_USBSRC_MASK;      // MCGPLLCLK/2 Source as USB clock (48MHz req.)
   SIM_SOPT1 = (SIM_SOPT1&~SIM_SOPT1_OSC32KSEL_MASK)|SIM_SOPT1_OSC32KSEL_M; // ERCLK32K clock - 0,1,2,3 -> OSC32KCLK, - , RTC_CLKIN, LPO (1kHz)
#elif defined(MCU_MKL14Z4) || defined(MCU_MKL15Z4) || defined(MCU_MKL16Z4) || defined(MCU_MKL34Z4) || defined(MCU_MKL36Z4)
   SIM_SOPT2 = SIM_SOPT2_UART0SRC_M      | // UART0 clock - 0,1,2,3 -> Disabled, (MCGFLLCLK, MCGPLLCLK/2),  OSCERCLK, MCGIRCLK
               SIM_SOPT2_TPMSRC_M        | // TPM clock - 0,1,2,3 -> Disabled, (MCGFLLCLK, MCGPLLCLK/2),  OSCERCLK, MCGIRCLK
               SIM_SOPT2_PLLFLLSEL_M;      // Peripheral clock - 0,1 -> MCGFLLCLK,MCGPLLCLK/2
   SIM_SOPT1 = (SIM_SOPT1&~SIM_SOPT1_OSC32KSEL_MASK)|SIM_SOPT1_OSC32KSEL_M; // ERCLK32K clock - 0,1,2,3 -> OSC32KCLK, - , RTC_CLKIN, LPO (1kHz)
#elif defined(MCU_MKL02Z4) || defined(MCU_MKL04Z4) || defined(MCU_MKL05Z4)
   SIM_SOPT2 = SIM_SOPT2_UART0SRC_M      | // UART0 clock - 0,1,2,3 -> Disabled, (MCGFLLCLK, MCGPLLCLK/2),  OSCERCLK, MCGIRCLK
               SIM_SOPT2_TPMSRC_M ;        // TPM2 source
#elif defined(MCU_MK60D12) || defined(MCU_MK60F12)
   // Peripheral clock choice (incl. USB), USBCLK = MCGCLK
   SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK | // PLL rather than FLL for peripheral clock
                SIM_SOPT2_USBFSRC_MASK;     // MCGPLLCLK/2 Source as USB clock (48MHz req.)
#elif defined(MCU_MK10D12) || defined(MCU_MK10F12)
   // Peripheral clock choice (incl. USB), USBCLK = MCGCLK
   SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK; // PLL rather than FLL for peripheral clock
#elif defined MCU_MK64F12
   SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_M |
                SIM_SOPT2_USBSRC_MASK;
#elif defined(MCU_MK64F12)
   // Peripheral clock choice (incl. USB), USBCLK = MCGCLK
   SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_M    | // PLL rather than FLL for peripheral clock
                SIM_SOPT2_USBSRC_MASK;     // MCGPLLCLK/2 Source as USB clock (48MHz req.)
   SIM_SOPT1 = (SIM_SOPT1&~SIM_SOPT1_OSC32KSEL_MASK)|SIM_SOPT1_OSC32KSEL_M; // ERCLK32K source
#else
   #error "Please add code as required"
#endif
   SystemCoreClockUpdate();
}

/**
 * Update SystemCoreClock variable
 *
 * @brief  Updates the SystemCoreClock with current core Clock
 *         retrieved from CPU registers.
 */
void SystemCoreClockUpdate(void) {
   uint32_t oscerclk = 0;
   switch((MCG_C7&MCG_C7_OSCSEL_MASK)) {
      case (0<<MCG_C7_OSCSEL_SHIFT) : oscerclk = OSCCLK_CLOCK; break;
      case (1<<MCG_C7_OSCSEL_SHIFT) : oscerclk = RTCCLK_CLOCK; break;
      case (2<<MCG_C7_OSCSEL_SHIFT) : oscerclk = IRC48M_CLOCK; break;
   }
   switch (MCG_S&MCG_S_CLKST_MASK) {
      case MCG_S_CLKST(0) : // FLL
         SystemCoreClock = (MCG_C4&MCG_C4_DMX32_MASK)?732:640;
         if ((MCG_C1&MCG_C1_IREFS_MASK) == 0) {
            SystemCoreClock *= oscerclk/(1<<((MCG_C1&MCG_C1_FRDIV_MASK)>>MCG_C1_FRDIV_SHIFT));
            if (((MCG_C2&MCG_C2_RANGE0_MASK) != 0) && ((MCG_C7&MCG_C7_OSCSEL_MASK) !=  1)) {
               if ((MCG_C1&MCG_C1_FRDIV_M) == MCG_C1_FRDIV(6)) {
                  SystemCoreClock /= 20;
               }
               else if ((MCG_C1&MCG_C1_FRDIV_M) == MCG_C1_FRDIV(7)) {
                  SystemCoreClock /= 12;
               }
               else {
                  SystemCoreClock /= 32;
               }
            }
         }
         else {
            SystemCoreClock *= SYSTEM_SLOW_IRC_CLOCK;
         }
         SystemCoreClock *= ((MCG_C4&MCG_C4_DRST_DRS_MASK)>>MCG_C4_DRST_DRS_SHIFT)+1;
      break;
      case MCG_S_CLKST(1) : // Internal Reference Clock
         if ((MCG_C2&MCG_C2_IRCS_MASK) != 0) {
            SystemCoreClock = SYSTEM_FAST_IRC_CLOCK/(1<<((MCG_SC&MCG_SC_FCRDIV_MASK)>>MCG_SC_FCRDIV_SHIFT));
         }
         else {
            SystemCoreClock = SYSTEM_SLOW_IRC_CLOCK;
         }
         break;
      case MCG_S_CLKST(2) : // External Reference Clock
         SystemCoreClock = oscerclk;
         break;
      case MCG_S_CLKST(3) : // PLL
         SystemCoreClock  = (oscerclk/10)*(((MCG_C6&MCG_C6_VDIV0_MASK)>>MCG_C6_VDIV0_SHIFT)+24);
         SystemCoreClock /= ((MCG_C5&MCG_C5_PRDIV0_MASK)>>MCG_C5_PRDIV0_SHIFT)+1;
         SystemCoreClock *= 10;
         break;
   }
   SystemBusClock    = SystemCoreClock/(((SIM_CLKDIV1&SIM_CLKDIV1_OUTDIV2_MASK)>>SIM_CLKDIV1_OUTDIV2_SHIFT)+1);
   SystemCoreClock   = SystemCoreClock/(((SIM_CLKDIV1&SIM_CLKDIV1_OUTDIV1_MASK)>>SIM_CLKDIV1_OUTDIV1_SHIFT)+1);
}

