/*
 * mk20-clock.c
 *
 *  Created on: 04/03/2012
 *      Author: podonoghue
 */
#include "derivative.h" /* include peripheral declarations */
#include "clock.h"
#include "clock_private.h"
#include "utilities.h"

// Some MCU call OSC_CR0 just OSC_CR
#ifndef OSC0_CR
#define OSC0_CR OSC_CR
#endif

uint32_t SystemCoreClock; // Hz
uint32_t SystemBusClock;  // Hz

/*! Sets up the clock out of RESET
 *!
 *! MCGOUTCLK = 48MHz
 *! core/platform/system clock = PLL (48MHz),
 *! bus clock = PLL/2 (24MHz),
 *! flash clock = PLL/2 (24MHz)
 *!
 *! Assumes 8 MHz external crystal
 *!
 *! Modes: FEI [FLL engaged internal] ->
 *!        FBE [FLL bypassed external] ->
 *!        PBE [PLL bypassed external] ->
 *!        PEE [PLL engaged external]
 *!
 *! Refer 24.5.3.1 of KL25 Family reference
 */
void clock_initialise(void) {

#if CLOCK_MODE == CLOCK_MODE_RESET
   // No clock setup
   return;
#else

   // XTAL/EXTAL Pins
   SIM_SCGC5  |= SIM_SCGC5_PORTA_MASK;
   PORTA_PCR18 = PORT_PCR_MUX(0);
   PORTA_PCR19 = PORT_PCR_MUX(0);

   // Configure the Crystal Oscillator
   OSC0_CR = OSC_CR_ERCLKEN_M|OSC_CR_EREFSTEN_M|OSC_CR_SCP_M;

   // Fast Internal Clock divider is fixed at 2 on Z version
//   MCG_SC = MCG_SC_FCRDIV(MCG_SC_FCRDIV_V);

   // 1. Switch from FEI (FLL engaged internal) to FBE (FLL bypassed external)

   // Out of reset MCG is in FEI mode
   // =============================================================
   // 1 a) Set up crystal or external clock source
   MCG_C2 =
//            MCG_C2_LOCRE0_M      |
            MCG_C2_RANGE_M       | // low/high/medium clock range
            MCG_C2_HGO_M         |
            MCG_C2_EREFS_M       | // select crystal/external clock
            MCG_C2_LP_M          |
            MCG_C2_IRCS_M;         // IRCS=0/1 -> MCGIRCLK = Slow/fast internal clock

   // 1 b) Select clock mode
   MCG_C1 =  MCG_C1_CLKS(2)      | // CLKS         -> External reference source while adjusting
             MCG_C1_FRDIV_M      | // FRDIV = N    -> XTAL/2^n ~ 31.25 kHz
             MCG_C1_IREFS_M      | // IREFS 0,1    -> External,Slow IRC
             MCG_C1_IRCLKEN_M    | // IRCLKEN = 1  -> MCGIRCLK active
             MCG_C1_IREFSTEN_M;    // IREFSTEN = 1 -> Internal reference enabled in STOP mode

   // FLL Factors
   MCG_C4 = (MCG_C4&~(MCG_C4_DMX32_MASK|MCG_C4_DRST_DRS_MASK))|MCG_C4_DMX32_M|MCG_C4_DRST_DRS_M;

   // 1 c) Wait for crystal to start up
   do {
      __asm__("nop");
   } while ((MCG_S & MCG_S_OSCINIT_MASK) == 0);

   // 1 d) Wait for mode change
   do {
      __asm__("nop");
   } while ((MCG_S & MCG_S_IREFST_MASK) != (MCG_C1_IREFS_V<<MCG_S_IREFST_SHIFT));

   // 1 e) Wait for MCGOUT indicating that the external reference to be fed to MCGOUT
   do {
      __asm__("nop");
   } while ((MCG_S & MCG_S_CLKST_MASK) != MCG_S_CLKST(2));

   // 2. Configure PLL Reference Frequency
   // =============================================================
   // 2 a) Set PRDIV for correct range
   MCG_C5 =  MCG_C5_PLLCLKEN_MASK |
             MCG_C5_PRDIV(MCG_C5_PRDIV0_V);    // PRDIV=?, PLL Ref Freq. = 2-4 MHz

   MCG_C6 = 0;

   // 3. FBE => PBE
   // =============================================================
   // 3 a) (BLPE - not done)
   // 3 b) PBE (/BLPE - not done)
   MCG_C6 = MCG_C6_PLLS_MASK|MCG_C6_VDIV_M; // 4MHz x 24 = 96MHz
   // 3 c) PBE (BLPE only -  not done)
   // 3 d) Wait until PLLS clock source changes to the PLL
   do {
      __asm__("nop");
   } while((MCG_S & MCG_S_PLLST_MASK) == 0);

   // 3 e)  Wait for PLL to acquired lock
   do {
      __asm__("nop");
   } while((MCG_S & MCG_S_LOCK_MASK) == 0);

   // Set up the SIM clock dividers BEFORE switching to the PLL to ensure the
   // system clock speeds are in spec.
   SIM_CLKDIV1 = SIM_CLKDIV1_OUTDIV1_M | SIM_CLKDIV1_OUTDIV2_M | SIM_CLKDIV1_OUTDIV3_M | SIM_CLKDIV1_OUTDIV4_M;

   __asm__("nop");
   __asm__("nop");
   __asm__("nop");

   // 4. PBE -> PEE mode:
   // =============================================================
   // 4 a) Select final clock mode
   MCG_C1 = MCG_C1_CLKS_M             | // CLKS         -> FLL or PLL is selected
            MCG_C1_FRDIV_M            | // FRDIV = 3    -> XTAL/2^n ~ 31.25 kHz
            MCG_C1_IREFS_M            | // IREFS 0,1    -> External,Slow IRC
            MCG_C1_IREFSTEN_M         | // IREFSTEN = 1 -> Internal reference enabled in STOP mode
            MCG_C1_IRCLKEN_M;           // IRCLKEN = 1  -> MCGIRCLK active

#if (MCG_C1_CLKS_V == 0) // FLL or PLL
#if (MCG_C6_PLLS_V == 0)
   #define MCG_S_CLKST_M MCG_S_CLKST(0) // FLL
#else
   #define MCG_S_CLKST_M MCG_S_CLKST(3) // PLL
#endif
#elif (MCG_C1_CLKS_V == 1) // IRC
#define MCG_S_CLKST_M MCG_S_CLKST(1)
#elif (MCG_C1_CLKS_V == 2) // ERC
#define MCG_S_CLKST_M MCG_S_CLKST(2)
#endif

   // 4 b)  Wait for clock stable
   do {
      __asm__("nop");
   } while ((MCG_S & MCG_S_CLKST_MASK) != MCG_S_CLKST_M);

   // Now MCGOUTCLK=MCGPLLCLK

   // Basic clock selection
#if defined(MCU_MK20D5) || defined(MCU_MK20D7) || defined(MCU_MK40D10) || defined(MCU_MK40DZ10)
   // Peripheral clock choice (incl. USB), USBCLK = MCGCLK
   SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_M    | // PLL rather than FLL for peripheral clock
                SIM_SOPT2_USBSRC_MASK;     // MCGPLLCLK/2 Source as USB clock (48MHz req.)
   SIM_SOPT1 = (SIM_SOPT1&~SIM_SOPT1_OSC32KSEL_MASK)|SIM_SOPT1_OSC32KSEL_M; // ERCLK32K source
#elif defined(MCU_MK60D10)
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
   SIM_SOPT2 = SIM_SOPT2_UART0SRC_M   | // MCGPLLCLK/2 as UART0 clock
               SIM_SOPT2_TPMSRC_M ;     // MCGPLLCLK/2 Source as USB clock (48MHz req.)
#else
   #error "CPU not set"
#endif
#endif
}

/**
 * Update SystemCoreClock variable
 *
 * @brief  Updates the SystemCoreClock with current core Clock
 *         retrieved from cpu registers.
 */
void SystemCoreClockUpdate(void) {
   // TODO - do this properly
   SystemCoreClock = SYSTEM_CORE_CLOCK;
   SystemBusClock  = SYSTEM_BUSCLK_CLOCK;
}

