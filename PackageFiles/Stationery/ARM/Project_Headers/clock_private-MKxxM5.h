/*
 * clock_private-mk20.h
 *
 *  Created on: Nov 6, 2012
 *      Author: podonoghue
 */

#ifndef CLOCK_PRIVATE_H_
#define CLOCK_PRIVATE_H_

#include <stdint.h>
#include "derivative.h"

#ifdef __cplusplus
extern "C" {
#endif

//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------

// Convention
// name_V = field value
// name_M = field mask i.e. value in correct position for register

//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------

// XTAL_FREQ ==============================
//
//   <o> Frequency of External Clock or Crystal (Hz)
//   <i> Frequency of external crystal or clock
#define OSCCLK_CLOCK (8000000)

#if   (OSCCLK_CLOCK > 32000UL)   && (OSCCLK_CLOCK <= 40000UL)
#define MCG_C2_RANGE0_M MCG_C2_RANGE0(0) // 32-40 kHz
#elif (OSCCLK_CLOCK > 3000000UL) && (OSCCLK_CLOCK <= 8000000UL)
#define MCG_C2_RANGE0_M MCG_C2_RANGE0(1) // 3-8 MHz
#elif (OSCCLK_CLOCK > 8000000UL) && (OSCCLK_CLOCK <= 32000000UL)
#define MCG_C2_RANGE0_M MCG_C2_RANGE0(2) // 8-32 MHz
#else
#error "Illegal Crystal Frequency"
#endif

// Slow Internal Clock ~32kHz
#define SYSTEM_SLOW_IRC_CLOCK (32000UL)

// 32kHz crystal oscillator
// May be the same as the main OSC on some chips
#define SYSTEM_OSC32KCLK_CLOCK (32625UL)

// Slow Internal Clock ~4MHz
#define SYSTEM_FAST_IRC_CLOCK (4000000UL)

// Low Power Oscillator Clock ~1kHz
#define SYSTEM_LOW_POWER_CLOCK (1000UL)

// SYSTEM_RTC_CLKIN_CLOCK ==============================
//
//   <o> External RTC clock input
//   <i> Frequency of external clock provided to RTC clock input pin
#define SYSTEM_RTC_CLKIN_CLOCK (0UL)

// CLOCK_MODE ===============================
//
//   <o> Clock Mode to set up (Not currently used)
//   <i> Basic choice on final clock mode
//     <0=> No setup (Reset default FEI)
//     <1=> FLL Engaged Internal (FEI)
//     <2=> FLL Engaged External (FEE)
//     <3=> PLL Engaged External (PEE)
#define CLOCK_MODE 3
#define CLOCK_MODE_RESET (0)
#define CLOCK_MODE_FEI   (1)
#define CLOCK_MODE_FEE   (2)
#define CLOCK_MODE_PEE   (3)

//========================================================================================
//========================================================================================
// <h> OSC Control Register (OSC_CR)

// OSC_CR_ERCLKEN ===============================
//
//   <q> External Reference Enable (ERCLKEN)
//   <i> Enables external reference clock [OSC_CR_ERCLKEN]
//     <0=> Disabled
//     <1=> Enabled
#define OSC_CR_ERCLKEN_V 1
#define OSC_CR_ERCLKEN_M (OSC_CR_ERCLKEN_V<<OSC_CR_ERCLKEN_SHIFT)

// OSC_CR_EREFSTEN ===============================
//
//   <q> External Reference Stop Enable (EREFSTEN)
//   <i> Determines if external reference clock is enabled in Stop mode [OSC_CR_EREFSTEN]
//     <0=> Disabled in Stop mode
//     <1=> Enabled in Stop mode
#define OSC_CR_EREFSTEN_V 1
#define OSC_CR_EREFSTEN_M (OSC_CR_EREFSTEN_V<<OSC_CR_EREFSTEN_SHIFT)

// OSC_CR_SC2P ===============================
//
//   <q0> Oscillator Capacitor Load Configure
//   <i> Configures the oscillator load capacitance [OSC_CR_SC2P]
//     <0=>
//     <1=> +2pF

// OSC_CR_SC4P ===============================
//
//   <q1> Oscillator Capacitor Load Configure
//   <i> Configures the oscillator load capacitance [OSC_CR_SC4P]
//     <0=>
//     <1=> +4pF

// OSC_CR_SC8P ===============================
//
//   <q2> Oscillator Capacitor Load Configure
//   <i> Configures the oscillator load capacitance [OSC_CR_SC8P]
//     <0=>
//     <1=> +8pF

// OSC_CR_SC16P ===============================
//
//   <q3> Oscillator Capacitor Load Configure
//   <i> Configures the oscillator load capacitance [OSC_CR_SC16P]
//     <0=>
//     <1=> +16pF

#define OSC_CR_SCP_M ((0<<OSC_CR_SC2P_SHIFT)|(0<<OSC_CR_SC4P_SHIFT)|(1<<OSC_CR_SC8P_SHIFT)|(0<<OSC_CR_SC16P_SHIFT))
// </h>

//========================================================================================
//========================================================================================

// MCG_C1_CLKS =======================================
//
//  <o> MCGOUTCLK Clock Source Select (CLKS) <0-2>
//  <i> Selects the clock source for MCGOUTCLK [MCG_C1_CLKS]
//      <0=> Output of FLL/PLL is selected
//      <1=> Internal reference clock is selected
//      <2=> External reference clock is selected
#define MCG_C1_CLKS_V 0
#define MCG_C1_CLKS_M MCG_C1_CLKS(MCG_C1_CLKS_V)

// MCG_C1_IREFS ================================
//
//   <q> IREFS Internal Reference Select (IREFS)
//   <i> FLL External Reference Divider [MCG_C1_IREFS]
//      <0=> External Reference Clock
//      <1=> Slow Internal Clock
#define MCG_C1_IREFS_V 0
#define MCG_C1_IREFS_M (MCG_C1_IREFS_V<<MCG_C1_IREFS_SHIFT)

// MCG_C1_IRCLKEN ==============================
//
//   <q> Internal Reference Clock Enable (IRCLKEN)
//   <i> Enables the internal reference clock for use as MCGIRCLK [MCG_C1_IRCLKEN]
//      <0=> inactive
//      <1=> active
#define MCG_C1_IRCLKEN_V   1
#define MCG_C1_IRCLKEN_M   (1<<MCG_C1_IRCLKEN_SHIFT)

// MCG_C1_IREFSTEN =============================
//
//   <q> Internal Reference Stop Enable (IREFSTEN)
//   <i> Determines if IRS is enabled in Stop mode [MCG_C1_IREFSTEN]
//      <0=> IR disabled in STOP
//      <1=> IR enabled in STOP
#define MCG_C1_IREFSTEN_V   1
#define MCG_C1_IREFSTEN_M   (MCG_C1_IREFSTEN_V<<MCG_C1_IREFSTEN_SHIFT)

// MCG_C2_LOCRE0 =============================
//
//   <q> Loss of Clock Reset Enable (LOCRE0)
//   <i> Reset on loss of OSC0 external reference [MCG_C2_LOCRE0]
//      <0=> Interrupt only (if CME0=1)
//      <1=> Reset
#define MCG_C2_LOCRE0_V (0)
#define MCG_C2_LOCRE0_M (MCG_C2_LOCRE0_V<<MCG_C2_LOCRE0_SHIFT)

// MCG_C2_HGO0 =============================
//
//   <q> Oscillator Gain (HGO0)
//   <i> Controls the crystal oscillator mode of operation [MCG_C2_HGO0_V]
//      <0=> Low gain
//      <1=> High gain
#define MCG_C2_HGO0_V   0
#define MCG_C2_HGO0_M   (MCG_C2_HGO0_V<<MCG_C2_HGO0_SHIFT)

// MCG_C2_EREFS0 =============================
//
//   <q> External Reference Select (EREFS0)
//   <i> Selects the source for the external reference clock [C2_EREFS0]
//      <0=> External clock
//      <1=> Oscillator
#define MCG_C2_EREFS0_V  1
#define MCG_C2_EREFS0_M (MCG_C2_EREFS0_V<<MCG_C2_EREFS0_SHIFT)

// MCG_C2_LP =============================
//
//   <q> Low Power Select (LP)
//   <i> Whether FLL/PLL continues operation when bypassed [MCG_C2_LP]
//      <0=> FLL/PLL is enabled in bypass modes
//      <1=> FLL/PLL is disabled in bypass modes
#define MCG_C2_LP_V  0
#define MCG_C2_LP_M (MCG_C2_LP_V<<MCG_C2_LP_SHIFT)

// MCG_C2_IRCS ==============================
//
//   <q> MCG IRC Clock Source (IRCS)
//   <i> MCG Internal Clock Source [MCG_C2_IRCS]
//     <0=> Slow internal reference clock
//     <1=> Fast internal reference clock
#define MCG_C2_IRCS_V 1
#define MCG_C2_IRCS_M (MCG_C2_IRCS_V<<MCG_C2_IRCS_SHIFT)

// MCG_C4_DMX32 ==============================
//
//   <q> DMX32 DCO lock range (DMX32)
//   <i> Optimise for 32.768 kHz Reference [MCG_C4_DMX32]
//     <0=> Wide lock range 31.25-39.06 kHz
//     <1=> Optimised for 32.768 kHz reference
#define MCG_C4_DMX32_V  0
#define MCG_C4_DMX32_M (MCG_C4_DMX32_V<<MCG_C4_DMX32_SHIFT)

// MCG_C4_DRST_DRS =============================
//
//   <o> DCO Range Select (DRST_DRS) <0-3>
//   <i> Frequency range for the FLL output, DCOOUT [MCG_C4_DRST_DRS]
//      <0=> Low range (24/20-25 MHz)
//      <1=> Mid range (48/40-50 MHz)
//      <2=> Mid-high range (72/60-75 MHz)
//      <3=> High range (96/80-100 MHz)
#define MCG_C4_DRST_DRS_V  1
#define MCG_C4_DRST_DRS_M (MCG_C4_DRST_DRS_V<<MCG_C4_DRST_DRS_SHIFT)

// MCG_C6_PLLS_V ==============================
//
//   <q> FLL/PLL selected as Clock source when CLKS=0 (PLLS)
//   <i> Selects PLL or FLL output [MCG_C6_PLLS]
//     <0=> FLL is selected
//     <1=> PLL is selected
#define MCG_C6_PLLS_V    1
#define MCG_C6_PLLS_M   (MCG_C6_PLLS_V<<MCG_C6_PLLS_SHIFT)

// MCG_C6_CME0 ==============================
//
//   <q> Clock Monitor Enable (CME0)
//   <i> Determines if a reset on loss of external clock [MCG_C6_CME0]
//      <0=> External clock monitor is disabled.
//      <1=> Reset request on loss of external clock.
#define MCG_C6_CME0_V (0)
#define MCG_C6_CME0_M (MCG_C6_CME_V<<MCG_C6_CME0_SHIFT)

// MCG_C6_VDIV0 ==============================
//
//   <o> PLL Multiplication Factor (VDIV0) <24-55> <#-24>
//   <i> Determine the multiplication factor of the PLL (x24-x55) [MCG_C6_VDIV0]
#define MCG_C6_VDIV0_V (0)
#define MCG_C6_VDIV0_M (MCG_C6_VDIV0_V<<MCG_C6_VDIV0_SHIFT)

// MCG_SC_FCRDIV ==============================
//
//   <o> Fast Clock Internal Reference Divider (FCRDIV) <0-7>
//   <i> Selects the amount to divide down the fast internal reference clock [MCG_SC_FCRDIV]
#define MCG_SC_FCRDIV_V  0
#define MCG_SC_FCRDIV_M (MCG_SC_FCRDIV_V<<MCG_SC_FCRDIV_SHIFT)

// MCG_C7_OSCSEL ==============================
//
//   <q> MCG OSC Clock Select (OSCSEL)
//   <i> Selects the MCG FLL external reference clock [MCG_C7_OSCSEL]
//     <0=> Selects System Oscillator (OSCCLK)
//     <1=> Selects 32 kHz RTC Oscillator
#define MCG_C7_OSCSEL_V  0
#define MCG_C7_OSCSEL_M (MCG_C7_OSCSEL_V<<MCG_C7_OSCSEL_SHIFT)

#if (MCG_C7_OSCSEL_V == 0)
#define SYSTEM_OSCERCLK_CLOCK    OSCCLK_CLOCK         // External reference clock
#else
#define SYSTEM_OSCERCLK_CLOCK    SYSTEM_RTC_CLOCK      // RTC OScillator (MK20 only)
#endif

// Assume no pre-scaler
#define OSCERCLK_CLOCKx         SYSTEM_OSCERCLK_CLOCK
#define MCG_C2_RANGE0_V    0

#if   (((OSCERCLK_CLOCKx/1)>=31250UL)   && ((OSCERCLK_CLOCKx/1)<=39063UL))
#define MCG_C1_FRDIV_V 0
#elif (((OSCERCLK_CLOCKx/2)>=31250UL)   && ((OSCERCLK_CLOCKx/2)<=39063UL))
#define MCG_C1_FRDIV_V 1
#elif (((OSCERCLK_CLOCKx/4)>=31250UL)   && ((OSCERCLK_CLOCKx/4)<=39063UL))
#define MCG_C1_FRDIV_V 2
#elif (((OSCERCLK_CLOCKx/8)>=31250UL)   && ((OSCERCLK_CLOCKx/8)<=39063UL))
#define MCG_C1_FRDIV_V 3
#elif (((OSCERCLK_CLOCKx/16)>=31250UL)  && ((OSCERCLK_CLOCKx/16)<=39063UL))
#define MCG_C1_FRDIV_V 4
#elif (((OSCERCLK_CLOCKx/32)>=31250UL)  && ((OSCERCLK_CLOCKx/32)<=39063UL))
#define MCG_C1_FRDIV_V 5
#elif (((OSCERCLK_CLOCKx/64)>=31250UL)  && ((OSCERCLK_CLOCKx/64)<=39063UL))
#define MCG_C1_FRDIV_V 6
#elif (((OSCERCLK_CLOCKx/128)>=31250UL) && ((OSCERCLK_CLOCKx/128)<=39063UL))
#define MCG_C1_FRDIV_V 7
#else
// Try with pre-scaler
#undef OSCERCLK_CLOCKx
#undef MCG_C2_RANGE0_V
#define OSCERCLK_CLOCKx         (SYSTEM_OSCERCLK_CLOCK/(1<<5))
#define MCG_C2_RANGE0_V    1
#if   (((OSCERCLK_CLOCKx/1)>=31250UL)   && ((OSCERCLK_CLOCKx/1)<=39063UL))
#define MCG_C1_FRDIV_V 0
#elif (((OSCERCLK_CLOCKx/2)>=31250UL)   && ((OSCERCLK_CLOCKx/2)<=39063UL))
#define MCG_C1_FRDIV_V 1
#elif (((OSCERCLK_CLOCKx/4)>=31250UL)   && ((OSCERCLK_CLOCKx/4)<=39063UL))
#define MCG_C1_FRDIV_V 2
#elif (((OSCERCLK_CLOCKx/8)>=31250UL)   && ((OSCERCLK_CLOCKx/8)<=39063UL))
#define MCG_C1_FRDIV_V 3
#elif (((OSCERCLK_CLOCKx/16)>=31250UL)  && ((OSCERCLK_CLOCKx/16)<=39063UL))
#define MCG_C1_FRDIV_V 4
#elif (((OSCERCLK_CLOCKx/32)>=31250UL)  && ((OSCERCLK_CLOCKx/32)<=39063UL))
#define MCG_C1_FRDIV_V 5
#elif (((OSCERCLK_CLOCKx/64)>=31250UL)  && ((OSCERCLK_CLOCKx/64)<=39063UL))
#define MCG_C1_FRDIV_V 6
#elif (((OSCERCLK_CLOCKx/128)>=31250UL) && ((OSCERCLK_CLOCKx/128)<=39063UL))
#define MCG_C1_FRDIV_V 7
#else
#endif
#endif
#undef OSCERCLK_CLOCKx

#define MCG_C1_FRDIV_M (MCG_C1_FRDIV_V<<MCG_C1_FRDIV_SHIFT)

// ERC_AFTER_FRDIV_CLOCK = External reference clock after dividers
#if (MCG_C2_RANGE0_V == 0) || (MCG_C7_OSCSEL_V != 0)
#define ERC_AFTER_FRDIV_CLOCK (SYSTEM_OSCERCLK_CLOCK/(1<<MCG_C1_FRDIV_V))
#else
#define ERC_AFTER_FRDIV_CLOCK (SYSTEM_OSCERCLK_CLOCK/(1<<(MCG_C1_FRDIV_V+5)))
#endif

#if (ERC_AFTER_FRDIV_CLOCK > 39062UL) || (ERC_AFTER_FRDIV_CLOCK < 31250UL)
#error "External reference clock must be in range 31.25 kHz to 39.0625 kHz"
#endif

// SYSTEM_MCGFFCLK_CLOCK  ==============================
#if (MCG_C1_IREFS_V == 0)
#define SYSTEM_MCGFFCLK_CLOCK ERC_AFTER_FRDIV_CLOCK  // External Reference clock after dividers
#else
#define SYSTEM_MCGFFCLK_CLOCK SYSTEM_SLOW_IRC_CLOCK  // Slow internal clock (nominally 32 kHz)
#endif

// MCGFLLCLK_CLOCK  ==============================

#if (MCG_C4_DMX32_V == 0)
#define SYSTEM_MCGFLLCLK_CLOCK (640*(MCG_C4_DRST_DRS_V+1)*SYSTEM_MCGFFCLK_CLOCK)
#elif (MCG_C4_DMX32_V == 1)
#define SYSTEM_MCGFLLCLK_CLOCK (732*(MCG_C4_DRST_DRS_V+1)*SYSTEM_MCGFFCLK_CLOCK)
#endif

// SYSTEM_MCGPLLCLK_CLOCK  ==============================

// Select PLL External Reference Divider - 0-24 -> 1-25
// Selects the amount to divide down the external reference clock for the PLL.
// The resulting frequency must be in the range of 2 MHz to 4 MHz.

#if   ((SYSTEM_OSCERCLK_CLOCK) >= 2000000) && ((SYSTEM_OSCERCLK_CLOCK/1) <= 4000000)
#define MCG_C5_PRDIV0_V ( 0)
#elif ((SYSTEM_OSCERCLK_CLOCK/2) <= 4000000)
#define MCG_C5_PRDIV0_V ( 1)
#elif ((SYSTEM_OSCERCLK_CLOCK/3) <= 4000000)
#define MCG_C5_PRDIV0_V ( 2)
#elif ((SYSTEM_OSCERCLK_CLOCK/4) <= 4000000)
#define MCG_C5_PRDIV0_V ( 3)
#elif ((SYSTEM_OSCERCLK_CLOCK/5) <= 4000000)
#define MCG_C5_PRDIV0_V ( 4)
#elif ((SYSTEM_OSCERCLK_CLOCK/6) <= 4000000)
#define MCG_C5_PRDIV0_V ( 5)
#elif ((SYSTEM_OSCERCLK_CLOCK/7) <= 4000000)
#define MCG_C5_PRDIV0_V ( 6)
#elif ((SYSTEM_OSCERCLK_CLOCK/8) <= 4000000)
#define MCG_C5_PRDIV0_V ( 7)
#elif ((SYSTEM_OSCERCLK_CLOCK/9) <= 4000000)
#define MCG_C5_PRDIV0_V ( 8)
#elif ((SYSTEM_OSCERCLK_CLOCK/10) <= 4000000)
#define MCG_C5_PRDIV0_V ( 9)
#elif ((SYSTEM_OSCERCLK_CLOCK/11) <= 4000000)
#define MCG_C5_PRDIV0_V (10)
#elif ((SYSTEM_OSCERCLK_CLOCK/12) <= 4000000)
#define MCG_C5_PRDIV0_V (11)
#elif ((SYSTEM_OSCERCLK_CLOCK/13) <= 4000000)
#define MCG_C5_PRDIV0_V (12)
#elif ((SYSTEM_OSCERCLK_CLOCK/14) <= 4000000)
#define MCG_C5_PRDIV0_V (13)
#elif ((SYSTEM_OSCERCLK_CLOCK/15) <= 4000000)
#define MCG_C5_PRDIV0_V (14)
#elif ((SYSTEM_OSCERCLK_CLOCK/16) <= 4000000)
#define MCG_C5_PRDIV0_V (15)
#elif ((SYSTEM_OSCERCLK_CLOCK/17) <= 4000000)
#define MCG_C5_PRDIV0_V (16)
#elif ((SYSTEM_OSCERCLK_CLOCK/18) <= 4000000)
#define MCG_C5_PRDIV0_V (17)
#elif ((SYSTEM_OSCERCLK_CLOCK/19) <= 4000000)
#define MCG_C5_PRDIV0_V (18)
#elif ((SYSTEM_OSCERCLK_CLOCK/20) <= 4000000)
#define MCG_C5_PRDIV0_V (19)
#elif ((SYSTEM_OSCERCLK_CLOCK/21) <= 4000000)
#define MCG_C5_PRDIV0_V (20)
#elif ((SYSTEM_OSCERCLK_CLOCK/22) <= 4000000)
#define MCG_C5_PRDIV0_V (21)
#elif ((SYSTEM_OSCERCLK_CLOCK/23) <= 4000000)
#define MCG_C5_PRDIV0_V (22)
#elif ((SYSTEM_OSCERCLK_CLOCK/24) <= 4000000)
#define MCG_C5_PRDIV0_V (23)
#elif ((SYSTEM_OSCERCLK_CLOCK/25) <= 4000000)
#define MCG_C5_PRDIV0_V (24)
#else
#error "Unable to find suitable MCG_C5_PRDIV0_V for SYSTEM_OSCERCLK_CLOCK value"
#endif

#define PLL_INPUT_DIVIDER (MCG_C5_PRDIV0_V+1)
#if ((SYSTEM_OSCERCLK_CLOCK/PLL_INPUT_DIVIDER) < 2000000) || ((SYSTEM_OSCERCLK_CLOCK/PLL_INPUT_DIVIDER) > 4000000)
#error "Unable to find suitable MCG_C5_PRDIV0_V for SYSTEM_OSCERCLK_CLOCK value"
#endif

// Select the amount to divide the VCO output of the PLL - 0-31 -> 24-55
// This determine the multiplication factor of the PLL
#define PLL_FACTOR (MCG_C6_VDIV0_V+24)

#define SYSTEM_MCGPLLCLK_CLOCK ((SYSTEM_OSCERCLK_CLOCK/PLL_INPUT_DIVIDER)*PLL_FACTOR)

#if (SYSTEM_MCGPLLCLK_CLOCK > 96000000)
#error "SYSTEM_MCGPLLCLK_CLOCK too high"
#endif

// SYSTEM_PERIPHERAL_CLOCK  ==============================

// <h> Peripheral Clock Source Selection

// SIM_SOPT2_PLLFLLSEL =============================
//
//   <q> Peripheral clock source (PLL/FLL)
//   <i> Source for clock used by some peripherals [SIM_SOPT2_PLLFLLSEL]
//      <0=> FLL (MCGFLLCLK)
//      <1=> PLL (MCGPLLCLK/2)
#define SIM_SOPT2_PLLFLLSEL_V  1
#define SIM_SOPT2_PLLFLLSEL_M (SIM_SOPT2_PLLFLLSEL_V<<SIM_SOPT2_PLLFLLSEL_SHIFT)

#if (SIM_SOPT2_PLLFLLSEL_V == 0) 
#define SYSTEM_PERIPHERAL_CLOCK SYSTEM_MCGFLLCLK_CLOCK
#else
#define SYSTEM_PERIPHERAL_CLOCK SYSTEM_MCGPLLCLK_CLOCK
#endif

#if (MCG_C1_CLKS_V == 0)
   #if (MCG_C6_PLLS_V == 0)
   #define SYSTEM_MCGOUTCLK_CLOCK SYSTEM_MCGFLLCLK_CLOCK
   #else
   #define SYSTEM_MCGOUTCLK_CLOCK SYSTEM_MCGPLLCLK_CLOCK
   #endif
#elif (MCG_C1_CLKS_V == 1)
#define SYSTEM_MCGOUTCLK_CLOCK SYSTEM_MCGIRCLK_CLOCK
#elif (MCG_C1_CLKS_V == 2)
#define SYSTEM_MCGOUTCLK_CLOCK SYSTEM_OSCERCLK_CLOCK
#endif

#if (MCG_C2_IRCS_V == 0)
#define SYSTEM_MCGIRCLK_CLOCK SYSTEM_SLOW_IRC_CLOCK
#else
#define SYSTEM_MCGIRCLK_CLOCK (SYSTEM_FAST_IRC_CLOCK/(1<<MCG_SC_FCRDIV_V))
#endif

// SIM_SOPT1_OSC32KSEL ================================
//
//   <o> 32kHz Clock Source (ERCLK32)
//   <i> 32kHz clock source- [SIM_SOPT1_OSC32KSEL]
//     <0=> System Oscillator (OSC32KCLK)
//     <2=> RTC 32.768kHz oscillator
//     <3=> Low power oscillator (LPO - 1kHz)
#define SIM_SOPT1_OSC32KSEL_V 3
#define SIM_SOPT1_OSC32KSEL_M SIM_SOPT1_OSC32KSEL(SIM_SOPT1_OSC32KSEL_V)

#if SIM_SOPT1_OSC32KSEL_V == 0
#define SYSTEM_ERCLK32_CLOCK SYSTEM_RTC_CLKIN_CLOCK   // External RTC clock pin
#elif SIM_SOPT1_OSC32KSEL_V == 2
#define SYSTEM_ERCLK32_CLOCK SYSTEM_OSC32KCLK_CLOCK   // Main/32kHz Oscillator (depends on chip)
#elif SIM_SOPT1_OSC32KSEL_V == 3
#define SYSTEM_ERCLK32_CLOCK SYSTEM_LOW_POWER_CLOCK   // LPO
#else
#error "Invalid ERCLK32 clock selected"
#endif

// LPTMR0_CLKSRC ==============================
//
//   <o> LPTMR0 Clock Source
//   <i> Low Power Timer clock source - [LPTMR0_PSR_PCS]
//     <0=> MCG Internal Reference Clock (MCGIRCLK)
//     <1=> Low power oscillator (LPO - 1kHz)
//     <2=> 32kHz Clock Source (ERCLK32)
//     <3=> Oscillator External Reference Clock (OSCERCLK)
#define LPTMR0_CLKSRC_M LPTMR0_PSR_PCS(0)

#if (LPTMR0_CLKSRC_M == LPTMR0_PSR_PCS(0))
#define SYSTEM_LPTMR0_CLOCK SYSTEM_MCGIRCLK_CLOCK
#elif (LPTMR0_CLKSRC_M == LPTMR0_PSR_PCS(1))
#define SYSTEM_LPTMR0_CLOCK SYSTEM_LOW_POWER_CLOCK
#elif (LPTMR0_CLKSRC_M == LPTMR0_PSR_PCS(2))
#define SYSTEM_LPTMR0_CLOCK SYSTEM_ERCLK32_CLOCK
#elif (LPTMR0_CLKSRC_M == LPTMR0_PSR_PCS(3))
#define SYSTEM_LPTMR0_CLOCK OSCCLK_CLOCK
#endif

#define SYSTEM_UART0_CLOCK SYSTEM_CORE_CLOCK
#define SYSTEM_UART1_CLOCK SYSTEM_CORE_CLOCK
#define SYSTEM_UART2_CLOCK SYSTEM_BUSCLK_CLOCK

// </h>

// <h> System Clock dividers
// SIM_CLKDIV1_OUTDIV1 ================================
//
//   <o> Core Clock Division (OUTDIV1) - Divide by <1-16> <#-1>
//   <i> Clocks the ARM Cortex-M4 core (50 MHz max.) [SIM_CLKDIV1_OUTDIV1]
//   <i> MCGOUTCLK clock is source. Default /2
#define SIM_CLKDIV1_OUTDIV1_V (1)
#define SIM_CLKDIV1_OUTDIV1_M SIM_CLKDIV1_OUTDIV1(SIM_CLKDIV1_OUTDIV1_V)

// SIM_CLKDIV1_OUTDIV2 ================================
//
//   <o> Bus Clock Divider (OUTDIV2) - Divide by <1-16> <#-1>
//   <i> Clocks the bus slaves and peripheral (50 MHz max.) [SIM_CLKDIV1_OUTDIV2]
//   <i> MCGOUTCLK clock is source. Default /2
#define SIM_CLKDIV1_OUTDIV2_V (1)
#define SIM_CLKDIV1_OUTDIV2_M SIM_CLKDIV1_OUTDIV2(SIM_CLKDIV1_OUTDIV2_V)

// SIM_CLKDIV1_OUTDIV3 ================================
// Not used
#define SIM_CLKDIV1_OUTDIV3_M (0)

// SIM_CLKDIV1_OUTDIV4 ================================
//
//   <o> Flash Clock Divider (OUTDIV4) - Divide by <1-16> <#-1>
//   <i> Clocks the flash memory (25 MHz max.) [SIM_CLKDIV1_OUTDIV4]
//   <i> MCGOUTCLK clock is source. Default /4
#define SIM_CLKDIV1_OUTDIV4_V (3)
#define SIM_CLKDIV1_OUTDIV4_M SIM_CLKDIV1_OUTDIV4(SIM_CLKDIV1_OUTDIV4_V)

// </h>

#define SYSTEM_CORE_CLOCK      (SYSTEM_MCGOUTCLK_CLOCK/(SIM_CLKDIV1_OUTDIV1_V+1))
#define SYSTEM_BUSCLK_CLOCK    (SYSTEM_MCGOUTCLK_CLOCK/(SIM_CLKDIV1_OUTDIV2_V+1))
#define SYSTEM_FLASHCLK_CLOCK  (SYSTEM_MCGOUTCLK_CLOCK/(SIM_CLKDIV1_OUTDIV4_V+1))

/*
 * The following are 'public' definitions
 *
 * SYSTEM_MCGIRCLK_CLOCK   MCG Internal Reference clock
 * SYSTEM_MCGFFCLK_CLOCK   MCG Various   (from SlowIRC/ERC_DIV/Peripheral bus clock)
 * SYSTEM_MCGFLLCLK_CLOCK  MCG FLL clock (from FLL)
 * SYSTEM_MCGPLLCLK_CLOCK  MCG PLL clock (from PLL)
 * SYSTEM_MCGOUTCLK_CLOCK  MCG OUT clock (from SlowIRC/FastIRC/ExternalRC/PLL/FLL)
 * SYSTEM_PERIPHERAL_CLOCK
 * SYSTEM_OSCERCLK_CLOCK
 * SYSTEM_BUSCLK_CLOCK
 * SYSTEM_CORE_CLOCK
 *
 */

void clock_initialise(void);

#ifdef __cplusplus
}
#endif

#endif /* CLOCK_PRIVATE_H_ */
