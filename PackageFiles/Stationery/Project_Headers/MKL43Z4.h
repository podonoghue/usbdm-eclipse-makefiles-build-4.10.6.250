/****************************************************************************************************//**
 * @file     MKL43Z4.h
 *
 * @brief    CMSIS Cortex-M Peripheral Access Layer Header File for MKL43Z4.
 *           Equivalent: MKL43Z128M4, MKL43Z256M4, FRDM-KL43Z
 *
 * @version  V0.0
 * @date     2014/12
 *
 *******************************************************************************************************/

#ifndef MCU_MKL43Z4
#define MCU_MKL43Z4

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum {
/* ------------------------  Processor Exceptions Numbers  ------------------------- */
  Reset_IRQn                    = -15,   /*!<   1 Reset Vector, invoked on Power up and warm reset                                 */
  NonMaskableInt_IRQn           = -14,   /*!<   2 Non maskable Interrupt, cannot be stopped or preempted                           */
  HardFault_IRQn                = -13,   /*!<   3 Hard Fault, all classes of Fault                                                 */
  MemoryManagement_IRQn         = -12,   /*!<   4 Memory Management, MPU mismatch, including Access Violation and No Match         */
  BusFault_IRQn                 = -11,   /*!<   5 Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory related Fault   */
  UsageFault_IRQn               = -10,   /*!<   6 Usage Fault, i.e. Undef Instruction, Illegal State Transition                    */
  SVCall_IRQn                   =  -5,   /*!<  11 System Service Call via SVC instruction                                          */
  DebugMonitor_IRQn             =  -4,   /*!<  12 Debug Monitor                                                                    */
  PendSV_IRQn                   =  -2,   /*!<  14 Pendable request for system service                                              */
  SysTick_IRQn                  =  -1,   /*!<  15 System Tick Timer                                                                */
/* ----------------------   MKL43Z4 VectorTable                      ---------------------- */
  DMA0_IRQn                     =   0,   /*!<  16 DMA0 Transfer complete or error                                                  */
  DMA1_IRQn                     =   1,   /*!<  17 DMA1 Transfer complete or error                                                  */
  DMA2_IRQn                     =   2,   /*!<  18 DMA2 Transfer complete or error                                                  */
  DMA3_IRQn                     =   3,   /*!<  19 DMA3 Transfer complete or error                                                  */
  FTFA_IRQn                     =   5,   /*!<  21 FTFA Command complete or error                                                   */
  PMC_IRQn                      =   6,   /*!<  22 PMC Low-voltage detect, low-voltage warning                                      */
  LLWU_IRQn                     =   7,   /*!<  23 Low Leakage Wakeup                                                               */
  I2C0_IRQn                     =   8,   /*!<  24 I2C Interface 0                                                                  */
  I2C1_IRQn                     =   9,   /*!<  25 I2C Interface 1                                                                  */
  SPI0_IRQn                     =  10,   /*!<  26 Serial Peripheral Interface 0                                                    */
  SPI1_IRQn                     =  11,   /*!<  27 Serial Peripheral Interface 1                                                    */
  LPUART0_IRQn                  =  12,   /*!<  28 UART0 Status and error                                                           */
  LPUART1_IRQn                  =  13,   /*!<  29 UART1 Status and error                                                           */
  UART2_FLEXIO_IRQn             =  14,   /*!<  30 UART2 or FLEXIO Status and error                                                 */
  ADC0_IRQn                     =  15,   /*!<  31 Analogue to Digital Converter 0                                                  */
  ACMP0_IRQn                    =  16,   /*!<  32 Analogue comparator 0                                                            */
  TPM0_IRQn                     =  17,   /*!<  33 Timer/PWM Module 0                                                               */
  TPM1_IRQn                     =  18,   /*!<  34 Timer/PWM Module 1                                                               */
  TPM2_IRQn                     =  19,   /*!<  35 Timer/PWM Module 2                                                               */
  RTC_Alarm_IRQn                =  20,   /*!<  36 Real Time Clock Alarm                                                            */
  RTC_Seconds_IRQn              =  21,   /*!<  37 Real Time Clock Seconds                                                          */
  PIT_IRQn                      =  22,   /*!<  38 Programmable Interrupt Timer (All channels)                                      */
  I2S0_IRQn                     =  23,   /*!<  39 I2S0                                                                             */
  USBOTG_IRQn                   =  24,   /*!<  40 USBB On The Go                                                                   */
  DAC0_IRQn                     =  25,   /*!<  41 Digital to Analogue Converter                                                    */
  LPTMR0_IRQn                   =  28,   /*!<  44 Low Power Timer                                                                  */
  SLCD_IRQn                     =  29,   /*!<  45 LCD Controller                                                                   */
  PORTA_IRQn                    =  30,   /*!<  46 Port A                                                                           */
  PORTC_D_IRQn                  =  31,   /*!<  47 Port C & Port D                                                                  */
} IRQn_Type;

/* -------------------------  Exception Handlers  ------------------------ */
extern void NMI_Handler(void);
extern void HardFault_Handler(void);
extern void MemManage_Handler(void);
extern void BusFault_Handler(void);
extern void UsageFault_Handler(void);
extern void SVC_Handler(void);
extern void DebugMon_Handler(void);
extern void PendSV_Handler(void);
extern void SysTick_Handler(void);
extern void DMA0_IRQHandler(void);
extern void DMA1_IRQHandler(void);
extern void DMA2_IRQHandler(void);
extern void DMA3_IRQHandler(void);
extern void FTFA_IRQHandler(void);
extern void PMC_IRQHandler(void);
extern void LLWU_IRQHandler(void);
extern void I2C0_IRQHandler(void);
extern void I2C1_IRQHandler(void);
extern void SPI0_IRQHandler(void);
extern void SPI1_IRQHandler(void);
extern void LPUART0_IRQHandler(void);
extern void LPUART1_IRQHandler(void);
extern void UART2_FLEXIO_IRQHandler(void);
extern void ADC0_IRQHandler(void);
extern void ACMP0_IRQHandler(void);
extern void TPM0_IRQHandler(void);
extern void TPM1_IRQHandler(void);
extern void TPM2_IRQHandler(void);
extern void RTC_Alarm_IRQHandler(void);
extern void RTC_Seconds_IRQHandler(void);
extern void PIT_IRQHandler(void);
extern void I2S0_IRQHandler(void);
extern void USBOTG_IRQHandler(void);
extern void DAC0_IRQHandler(void);
extern void LPTMR0_IRQHandler(void);
extern void SLCD_IRQHandler(void);
extern void PORTA_IRQHandler(void);
extern void PORTC_D_IRQHandler(void);

/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* ----------------Configuration of the cm4 Processor and Core Peripherals---------------- */
#define __CM0PLUS_REV                0x0100
#define __MPU_PRESENT            0
#define __NVIC_PRIO_BITS         2
#define __Vendor_SysTickConfig   0
#define __FPU_PRESENT            0

#include <core_cm0plus.h>   /*!< Processor and core peripherals */

#ifndef __IO
#define __IO volatile 
#endif

#ifndef __I
#define __I volatile const
#endif

#ifndef __O
#define __O volatile
#endif


/* ================================================================================ */
/* ================       Device Specific Peripheral Section       ================ */
/* ================================================================================ */



/* -------------------  Start of section using anonymous unions  ------------------ */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
/* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler type
#endif

/* ================================================================================ */
/* ================           ADC0 (file:ADC0_MKD5_MKLZ4)          ================ */
/* ================================================================================ */

/**
 * @brief Analog-to-Digital Converter
 */
typedef struct {                                /*!<       ADC0 Structure                                               */
   __IO uint32_t  SC1A;                         /*!< 0000: Status and Control Register 1                                */
   __IO uint32_t  SC1B;                         /*!< 0004: Status and Control Register 1                                */
   __IO uint32_t  CFG1;                         /*!< 0008: Configuration Register 1                                     */
   __IO uint32_t  CFG2;                         /*!< 000C: Configuration Register 2                                     */
   __I  uint32_t  RA;                           /*!< 0010: Data Result Register                                         */
   __I  uint32_t  RB;                           /*!< 0014: Data Result Register                                         */
   __IO uint32_t  CV1;                          /*!< 0018: Compare Value                                                */
   __IO uint32_t  CV2;                          /*!< 001C: Compare Value                                                */
   __IO uint32_t  SC2;                          /*!< 0020: Status and Control Register 2                                */
   __IO uint32_t  SC3;                          /*!< 0024: Status and Control Register 3                                */
   __IO uint32_t  OFS;                          /*!< 0028: Offset Correction Register                                   */
   __IO uint32_t  PG;                           /*!< 002C: Plus-Side Gain Register                                      */
   __IO uint32_t  MG;                           /*!< 0030: Minus-Side Gain Register                                     */
   __IO uint32_t  CLPD;                         /*!< 0034: Plus-Side General Calibration Value                          */
   __IO uint32_t  CLPS;                         /*!< 0038: Plus-Side General Calibration Value                          */
   __IO uint32_t  CLP4;                         /*!< 003C: Plus-Side General Calibration Value                          */
   __IO uint32_t  CLP3;                         /*!< 0040: Plus-Side General Calibration Value                          */
   __IO uint32_t  CLP2;                         /*!< 0044: Plus-Side General Calibration Value                          */
   __IO uint32_t  CLP1;                         /*!< 0048: Plus-Side General Calibration Value                          */
   __IO uint32_t  CLP0;                         /*!< 004C: Plus-Side General Calibration Value                          */
   __I  uint32_t  RESERVED0;                    /*!< 0050:                                                              */
   __IO uint32_t  CLMD;                         /*!< 0054: Minus-Side General Calibration Value                         */
   __IO uint32_t  CLMS;                         /*!< 0058: Minus-Side General Calibration Value                         */
   __IO uint32_t  CLM4;                         /*!< 005C: Minus-Side General Calibration Value                         */
   __IO uint32_t  CLM3;                         /*!< 0060: Minus-Side General Calibration Value                         */
   __IO uint32_t  CLM2;                         /*!< 0064: Minus-Side General Calibration Value                         */
   __IO uint32_t  CLM1;                         /*!< 0068: Minus-Side General Calibration Value                         */
   __IO uint32_t  CLM0;                         /*!< 006C: Minus-Side General Calibration Value                         */
} ADC0_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'ADC0' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- ADC0_SC1                                 ------ */
#define ADC_SC1_ADCH_MASK                        (0x1FUL << ADC_SC1_ADCH_SHIFT)                      /*!< ADC0_SC1: ADCH Mask                     */
#define ADC_SC1_ADCH_SHIFT                       0                                                   /*!< ADC0_SC1: ADCH Position                 */
#define ADC_SC1_ADCH(x)                          (((x)<<ADC_SC1_ADCH_SHIFT)&ADC_SC1_ADCH_MASK)       /*!< ADC0_SC1                                */
#define ADC_SC1_DIFF_MASK                        (0x01UL << ADC_SC1_DIFF_SHIFT)                      /*!< ADC0_SC1: DIFF Mask                     */
#define ADC_SC1_DIFF_SHIFT                       5                                                   /*!< ADC0_SC1: DIFF Position                 */
#define ADC_SC1_AIEN_MASK                        (0x01UL << ADC_SC1_AIEN_SHIFT)                      /*!< ADC0_SC1: AIEN Mask                     */
#define ADC_SC1_AIEN_SHIFT                       6                                                   /*!< ADC0_SC1: AIEN Position                 */
#define ADC_SC1_COCO_MASK                        (0x01UL << ADC_SC1_COCO_SHIFT)                      /*!< ADC0_SC1: COCO Mask                     */
#define ADC_SC1_COCO_SHIFT                       7                                                   /*!< ADC0_SC1: COCO Position                 */

/* ------- ADC0_CFG1                                ------ */
#define ADC_CFG1_ADICLK_MASK                     (0x03UL << ADC_CFG1_ADICLK_SHIFT)                   /*!< ADC0_CFG1: ADICLK Mask                  */
#define ADC_CFG1_ADICLK_SHIFT                    0                                                   /*!< ADC0_CFG1: ADICLK Position              */
#define ADC_CFG1_ADICLK(x)                       (((x)<<ADC_CFG1_ADICLK_SHIFT)&ADC_CFG1_ADICLK_MASK) /*!< ADC0_CFG1                               */
#define ADC_CFG1_MODE_MASK                       (0x03UL << ADC_CFG1_MODE_SHIFT)                     /*!< ADC0_CFG1: MODE Mask                    */
#define ADC_CFG1_MODE_SHIFT                      2                                                   /*!< ADC0_CFG1: MODE Position                */
#define ADC_CFG1_MODE(x)                         (((x)<<ADC_CFG1_MODE_SHIFT)&ADC_CFG1_MODE_MASK)     /*!< ADC0_CFG1                               */
#define ADC_CFG1_ADLSMP_MASK                     (0x01UL << ADC_CFG1_ADLSMP_SHIFT)                   /*!< ADC0_CFG1: ADLSMP Mask                  */
#define ADC_CFG1_ADLSMP_SHIFT                    4                                                   /*!< ADC0_CFG1: ADLSMP Position              */
#define ADC_CFG1_ADIV_MASK                       (0x03UL << ADC_CFG1_ADIV_SHIFT)                     /*!< ADC0_CFG1: ADIV Mask                    */
#define ADC_CFG1_ADIV_SHIFT                      5                                                   /*!< ADC0_CFG1: ADIV Position                */
#define ADC_CFG1_ADIV(x)                         (((x)<<ADC_CFG1_ADIV_SHIFT)&ADC_CFG1_ADIV_MASK)     /*!< ADC0_CFG1                               */
#define ADC_CFG1_ADLPC_MASK                      (0x01UL << ADC_CFG1_ADLPC_SHIFT)                    /*!< ADC0_CFG1: ADLPC Mask                   */
#define ADC_CFG1_ADLPC_SHIFT                     7                                                   /*!< ADC0_CFG1: ADLPC Position               */

/* ------- ADC0_CFG2                                ------ */
#define ADC_CFG2_ADLSTS_MASK                     (0x03UL << ADC_CFG2_ADLSTS_SHIFT)                   /*!< ADC0_CFG2: ADLSTS Mask                  */
#define ADC_CFG2_ADLSTS_SHIFT                    0                                                   /*!< ADC0_CFG2: ADLSTS Position              */
#define ADC_CFG2_ADLSTS(x)                       (((x)<<ADC_CFG2_ADLSTS_SHIFT)&ADC_CFG2_ADLSTS_MASK) /*!< ADC0_CFG2                               */
#define ADC_CFG2_ADHSC_MASK                      (0x01UL << ADC_CFG2_ADHSC_SHIFT)                    /*!< ADC0_CFG2: ADHSC Mask                   */
#define ADC_CFG2_ADHSC_SHIFT                     2                                                   /*!< ADC0_CFG2: ADHSC Position               */
#define ADC_CFG2_ADACKEN_MASK                    (0x01UL << ADC_CFG2_ADACKEN_SHIFT)                  /*!< ADC0_CFG2: ADACKEN Mask                 */
#define ADC_CFG2_ADACKEN_SHIFT                   3                                                   /*!< ADC0_CFG2: ADACKEN Position             */
#define ADC_CFG2_MUXSEL_MASK                     (0x01UL << ADC_CFG2_MUXSEL_SHIFT)                   /*!< ADC0_CFG2: MUXSEL Mask                  */
#define ADC_CFG2_MUXSEL_SHIFT                    4                                                   /*!< ADC0_CFG2: MUXSEL Position              */

/* ------- ADC0_R                                   ------ */
#define ADC_R_D_MASK                             (0xFFFFUL << ADC_R_D_SHIFT)                         /*!< ADC0_R: D Mask                          */
#define ADC_R_D_SHIFT                            0                                                   /*!< ADC0_R: D Position                      */
#define ADC_R_D(x)                               (((x)<<ADC_R_D_SHIFT)&ADC_R_D_MASK)                 /*!< ADC0_R                                  */

/* ------- ADC0_CV                                  ------ */
#define ADC_CV_CV_MASK                           (0xFFFFUL << ADC_CV_CV_SHIFT)                       /*!< ADC0_CV: CV Mask                        */
#define ADC_CV_CV_SHIFT                          0                                                   /*!< ADC0_CV: CV Position                    */
#define ADC_CV_CV(x)                             (((x)<<ADC_CV_CV_SHIFT)&ADC_CV_CV_MASK)             /*!< ADC0_CV                                 */

/* ------- ADC0_SC2                                 ------ */
#define ADC_SC2_REFSEL_MASK                      (0x03UL << ADC_SC2_REFSEL_SHIFT)                    /*!< ADC0_SC2: REFSEL Mask                   */
#define ADC_SC2_REFSEL_SHIFT                     0                                                   /*!< ADC0_SC2: REFSEL Position               */
#define ADC_SC2_REFSEL(x)                        (((x)<<ADC_SC2_REFSEL_SHIFT)&ADC_SC2_REFSEL_MASK)   /*!< ADC0_SC2                                */
#define ADC_SC2_DMAEN_MASK                       (0x01UL << ADC_SC2_DMAEN_SHIFT)                     /*!< ADC0_SC2: DMAEN Mask                    */
#define ADC_SC2_DMAEN_SHIFT                      2                                                   /*!< ADC0_SC2: DMAEN Position                */
#define ADC_SC2_ACREN_MASK                       (0x01UL << ADC_SC2_ACREN_SHIFT)                     /*!< ADC0_SC2: ACREN Mask                    */
#define ADC_SC2_ACREN_SHIFT                      3                                                   /*!< ADC0_SC2: ACREN Position                */
#define ADC_SC2_ACFGT_MASK                       (0x01UL << ADC_SC2_ACFGT_SHIFT)                     /*!< ADC0_SC2: ACFGT Mask                    */
#define ADC_SC2_ACFGT_SHIFT                      4                                                   /*!< ADC0_SC2: ACFGT Position                */
#define ADC_SC2_ACFE_MASK                        (0x01UL << ADC_SC2_ACFE_SHIFT)                      /*!< ADC0_SC2: ACFE Mask                     */
#define ADC_SC2_ACFE_SHIFT                       5                                                   /*!< ADC0_SC2: ACFE Position                 */
#define ADC_SC2_ADTRG_MASK                       (0x01UL << ADC_SC2_ADTRG_SHIFT)                     /*!< ADC0_SC2: ADTRG Mask                    */
#define ADC_SC2_ADTRG_SHIFT                      6                                                   /*!< ADC0_SC2: ADTRG Position                */
#define ADC_SC2_ADACT_MASK                       (0x01UL << ADC_SC2_ADACT_SHIFT)                     /*!< ADC0_SC2: ADACT Mask                    */
#define ADC_SC2_ADACT_SHIFT                      7                                                   /*!< ADC0_SC2: ADACT Position                */

/* ------- ADC0_SC3                                 ------ */
#define ADC_SC3_AVGS_MASK                        (0x03UL << ADC_SC3_AVGS_SHIFT)                      /*!< ADC0_SC3: AVGS Mask                     */
#define ADC_SC3_AVGS_SHIFT                       0                                                   /*!< ADC0_SC3: AVGS Position                 */
#define ADC_SC3_AVGS(x)                          (((x)<<ADC_SC3_AVGS_SHIFT)&ADC_SC3_AVGS_MASK)       /*!< ADC0_SC3                                */
#define ADC_SC3_AVGE_MASK                        (0x01UL << ADC_SC3_AVGE_SHIFT)                      /*!< ADC0_SC3: AVGE Mask                     */
#define ADC_SC3_AVGE_SHIFT                       2                                                   /*!< ADC0_SC3: AVGE Position                 */
#define ADC_SC3_ADCO_MASK                        (0x01UL << ADC_SC3_ADCO_SHIFT)                      /*!< ADC0_SC3: ADCO Mask                     */
#define ADC_SC3_ADCO_SHIFT                       3                                                   /*!< ADC0_SC3: ADCO Position                 */
#define ADC_SC3_CALF_MASK                        (0x01UL << ADC_SC3_CALF_SHIFT)                      /*!< ADC0_SC3: CALF Mask                     */
#define ADC_SC3_CALF_SHIFT                       6                                                   /*!< ADC0_SC3: CALF Position                 */
#define ADC_SC3_CAL_MASK                         (0x01UL << ADC_SC3_CAL_SHIFT)                       /*!< ADC0_SC3: CAL Mask                      */
#define ADC_SC3_CAL_SHIFT                        7                                                   /*!< ADC0_SC3: CAL Position                  */

/* ------- ADC0_OFS                                 ------ */
#define ADC_OFS_OFS_MASK                         (0xFFFFUL << ADC_OFS_OFS_SHIFT)                     /*!< ADC0_OFS: OFS Mask                      */
#define ADC_OFS_OFS_SHIFT                        0                                                   /*!< ADC0_OFS: OFS Position                  */
#define ADC_OFS_OFS(x)                           (((x)<<ADC_OFS_OFS_SHIFT)&ADC_OFS_OFS_MASK)         /*!< ADC0_OFS                                */

/* ------- ADC0_PG                                  ------ */
#define ADC_PG_PG_MASK                           (0xFFFFUL << ADC_PG_PG_SHIFT)                       /*!< ADC0_PG: PG Mask                        */
#define ADC_PG_PG_SHIFT                          0                                                   /*!< ADC0_PG: PG Position                    */
#define ADC_PG_PG(x)                             (((x)<<ADC_PG_PG_SHIFT)&ADC_PG_PG_MASK)             /*!< ADC0_PG                                 */

/* ------- ADC0_MG                                  ------ */
#define ADC_MG_MG_MASK                           (0xFFFFUL << ADC_MG_MG_SHIFT)                       /*!< ADC0_MG: MG Mask                        */
#define ADC_MG_MG_SHIFT                          0                                                   /*!< ADC0_MG: MG Position                    */
#define ADC_MG_MG(x)                             (((x)<<ADC_MG_MG_SHIFT)&ADC_MG_MG_MASK)             /*!< ADC0_MG                                 */

/* ------- ADC0_CLPD                                ------ */
#define ADC_CLPD_CLPD_MASK                       (0x3FUL << ADC_CLPD_CLPD_SHIFT)                     /*!< ADC0_CLPD: CLPD Mask                    */
#define ADC_CLPD_CLPD_SHIFT                      0                                                   /*!< ADC0_CLPD: CLPD Position                */
#define ADC_CLPD_CLPD(x)                         (((x)<<ADC_CLPD_CLPD_SHIFT)&ADC_CLPD_CLPD_MASK)     /*!< ADC0_CLPD                               */

/* ------- ADC0_CLPS                                ------ */
#define ADC_CLPS_CLPS_MASK                       (0x3FUL << ADC_CLPS_CLPS_SHIFT)                     /*!< ADC0_CLPS: CLPS Mask                    */
#define ADC_CLPS_CLPS_SHIFT                      0                                                   /*!< ADC0_CLPS: CLPS Position                */
#define ADC_CLPS_CLPS(x)                         (((x)<<ADC_CLPS_CLPS_SHIFT)&ADC_CLPS_CLPS_MASK)     /*!< ADC0_CLPS                               */

/* ------- ADC0_CLP4                                ------ */
#define ADC_CLP4_CLP4_MASK                       (0x3FFUL << ADC_CLP4_CLP4_SHIFT)                    /*!< ADC0_CLP4: CLP4 Mask                    */
#define ADC_CLP4_CLP4_SHIFT                      0                                                   /*!< ADC0_CLP4: CLP4 Position                */
#define ADC_CLP4_CLP4(x)                         (((x)<<ADC_CLP4_CLP4_SHIFT)&ADC_CLP4_CLP4_MASK)     /*!< ADC0_CLP4                               */

/* ------- ADC0_CLP3                                ------ */
#define ADC_CLP3_CLP3_MASK                       (0x1FFUL << ADC_CLP3_CLP3_SHIFT)                    /*!< ADC0_CLP3: CLP3 Mask                    */
#define ADC_CLP3_CLP3_SHIFT                      0                                                   /*!< ADC0_CLP3: CLP3 Position                */
#define ADC_CLP3_CLP3(x)                         (((x)<<ADC_CLP3_CLP3_SHIFT)&ADC_CLP3_CLP3_MASK)     /*!< ADC0_CLP3                               */

/* ------- ADC0_CLP2                                ------ */
#define ADC_CLP2_CLP2_MASK                       (0xFFUL << ADC_CLP2_CLP2_SHIFT)                     /*!< ADC0_CLP2: CLP2 Mask                    */
#define ADC_CLP2_CLP2_SHIFT                      0                                                   /*!< ADC0_CLP2: CLP2 Position                */
#define ADC_CLP2_CLP2(x)                         (((x)<<ADC_CLP2_CLP2_SHIFT)&ADC_CLP2_CLP2_MASK)     /*!< ADC0_CLP2                               */

/* ------- ADC0_CLP1                                ------ */
#define ADC_CLP1_CLP1_MASK                       (0x7FUL << ADC_CLP1_CLP1_SHIFT)                     /*!< ADC0_CLP1: CLP1 Mask                    */
#define ADC_CLP1_CLP1_SHIFT                      0                                                   /*!< ADC0_CLP1: CLP1 Position                */
#define ADC_CLP1_CLP1(x)                         (((x)<<ADC_CLP1_CLP1_SHIFT)&ADC_CLP1_CLP1_MASK)     /*!< ADC0_CLP1                               */

/* ------- ADC0_CLP0                                ------ */
#define ADC_CLP0_CLP0_MASK                       (0x3FUL << ADC_CLP0_CLP0_SHIFT)                     /*!< ADC0_CLP0: CLP0 Mask                    */
#define ADC_CLP0_CLP0_SHIFT                      0                                                   /*!< ADC0_CLP0: CLP0 Position                */
#define ADC_CLP0_CLP0(x)                         (((x)<<ADC_CLP0_CLP0_SHIFT)&ADC_CLP0_CLP0_MASK)     /*!< ADC0_CLP0                               */

/* ------- ADC0_CLMD                                ------ */
#define ADC_CLMD_CLMD_MASK                       (0x3FUL << ADC_CLMD_CLMD_SHIFT)                     /*!< ADC0_CLMD: CLMD Mask                    */
#define ADC_CLMD_CLMD_SHIFT                      0                                                   /*!< ADC0_CLMD: CLMD Position                */
#define ADC_CLMD_CLMD(x)                         (((x)<<ADC_CLMD_CLMD_SHIFT)&ADC_CLMD_CLMD_MASK)     /*!< ADC0_CLMD                               */

/* ------- ADC0_CLMS                                ------ */
#define ADC_CLMS_CLMS_MASK                       (0x3FUL << ADC_CLMS_CLMS_SHIFT)                     /*!< ADC0_CLMS: CLMS Mask                    */
#define ADC_CLMS_CLMS_SHIFT                      0                                                   /*!< ADC0_CLMS: CLMS Position                */
#define ADC_CLMS_CLMS(x)                         (((x)<<ADC_CLMS_CLMS_SHIFT)&ADC_CLMS_CLMS_MASK)     /*!< ADC0_CLMS                               */

/* ------- ADC0_CLM4                                ------ */
#define ADC_CLM4_CLM4_MASK                       (0x3FFUL << ADC_CLM4_CLM4_SHIFT)                    /*!< ADC0_CLM4: CLM4 Mask                    */
#define ADC_CLM4_CLM4_SHIFT                      0                                                   /*!< ADC0_CLM4: CLM4 Position                */
#define ADC_CLM4_CLM4(x)                         (((x)<<ADC_CLM4_CLM4_SHIFT)&ADC_CLM4_CLM4_MASK)     /*!< ADC0_CLM4                               */

/* ------- ADC0_CLM3                                ------ */
#define ADC_CLM3_CLM3_MASK                       (0x1FFUL << ADC_CLM3_CLM3_SHIFT)                    /*!< ADC0_CLM3: CLM3 Mask                    */
#define ADC_CLM3_CLM3_SHIFT                      0                                                   /*!< ADC0_CLM3: CLM3 Position                */
#define ADC_CLM3_CLM3(x)                         (((x)<<ADC_CLM3_CLM3_SHIFT)&ADC_CLM3_CLM3_MASK)     /*!< ADC0_CLM3                               */

/* ------- ADC0_CLM2                                ------ */
#define ADC_CLM2_CLM2_MASK                       (0xFFUL << ADC_CLM2_CLM2_SHIFT)                     /*!< ADC0_CLM2: CLM2 Mask                    */
#define ADC_CLM2_CLM2_SHIFT                      0                                                   /*!< ADC0_CLM2: CLM2 Position                */
#define ADC_CLM2_CLM2(x)                         (((x)<<ADC_CLM2_CLM2_SHIFT)&ADC_CLM2_CLM2_MASK)     /*!< ADC0_CLM2                               */

/* ------- ADC0_CLM1                                ------ */
#define ADC_CLM1_CLM1_MASK                       (0x7FUL << ADC_CLM1_CLM1_SHIFT)                     /*!< ADC0_CLM1: CLM1 Mask                    */
#define ADC_CLM1_CLM1_SHIFT                      0                                                   /*!< ADC0_CLM1: CLM1 Position                */
#define ADC_CLM1_CLM1(x)                         (((x)<<ADC_CLM1_CLM1_SHIFT)&ADC_CLM1_CLM1_MASK)     /*!< ADC0_CLM1                               */

/* ------- ADC0_CLM0                                ------ */
#define ADC_CLM0_CLM0_MASK                       (0x3FUL << ADC_CLM0_CLM0_SHIFT)                     /*!< ADC0_CLM0: CLM0 Mask                    */
#define ADC_CLM0_CLM0_SHIFT                      0                                                   /*!< ADC0_CLM0: CLM0 Position                */
#define ADC_CLM0_CLM0(x)                         (((x)<<ADC_CLM0_CLM0_SHIFT)&ADC_CLM0_CLM0_MASK)     /*!< ADC0_CLM0                               */

/* -------------------------------------------------------------------------------- */
/* -----------     'ADC0' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define ADC0_SC1A                      (ADC0->SC1A)
#define ADC0_SC1B                      (ADC0->SC1B)
#define ADC0_CFG1                      (ADC0->CFG1)
#define ADC0_CFG2                      (ADC0->CFG2)
#define ADC0_RA                        (ADC0->RA)
#define ADC0_RB                        (ADC0->RB)
#define ADC0_CV1                       (ADC0->CV1)
#define ADC0_CV2                       (ADC0->CV2)
#define ADC0_SC2                       (ADC0->SC2)
#define ADC0_SC3                       (ADC0->SC3)
#define ADC0_OFS                       (ADC0->OFS)
#define ADC0_PG                        (ADC0->PG)
#define ADC0_MG                        (ADC0->MG)
#define ADC0_CLPD                      (ADC0->CLPD)
#define ADC0_CLPS                      (ADC0->CLPS)
#define ADC0_CLP4                      (ADC0->CLP4)
#define ADC0_CLP3                      (ADC0->CLP3)
#define ADC0_CLP2                      (ADC0->CLP2)
#define ADC0_CLP1                      (ADC0->CLP1)
#define ADC0_CLP0                      (ADC0->CLP0)
#define ADC0_CLMD                      (ADC0->CLMD)
#define ADC0_CLMS                      (ADC0->CLMS)
#define ADC0_CLM4                      (ADC0->CLM4)
#define ADC0_CLM3                      (ADC0->CLM3)
#define ADC0_CLM2                      (ADC0->CLM2)
#define ADC0_CLM1                      (ADC0->CLM1)
#define ADC0_CLM0                      (ADC0->CLM0)

/* ================================================================================ */
/* ================           BP (file:BP_0)                       ================ */
/* ================================================================================ */

/**
 * @brief Breakpoint Unit
 */
typedef struct {                                /*!<       BP Structure                                                 */
   __IO uint32_t  CTRL;                         /*!< 0000: FlashPatch Control Register                                  */
   __I  uint32_t  RESERVED0;                    /*!< 0004:                                                              */
   __IO uint32_t  COMP0;                        /*!< 0008: FlashPatch Comparator Register 0                             */
   __IO uint32_t  COMP1;                        /*!< 000C: FlashPatch Comparator Register 1                             */
   __I  uint32_t  RESERVED1[1008];              /*!< 0010:                                                              */
   __I  uint32_t  PID4;                         /*!< 0FD0: Peripheral Identification Register 4                         */
   __I  uint32_t  PID5;                         /*!< 0FD4: Peripheral Identification Register 5                         */
   __I  uint32_t  PID6;                         /*!< 0FD8: Peripheral Identification Register 6                         */
   __I  uint32_t  PID7;                         /*!< 0FDC: Peripheral Identification Register 7                         */
   __I  uint32_t  PID0;                         /*!< 0FE0: Peripheral Identification Register 0                         */
   __I  uint32_t  PID1;                         /*!< 0FE4: Peripheral Identification Register 1                         */
   __I  uint32_t  PID2;                         /*!< 0FE8: Peripheral Identification Register 2                         */
   __I  uint32_t  PID3;                         /*!< 0FEC: Peripheral Identification Register 3                         */
   __I  uint32_t  CID0;                         /*!< 0FF0: Component Identification Register 0                          */
   __I  uint32_t  CID1;                         /*!< 0FF4: Component Identification Register 1                          */
   __I  uint32_t  CID2;                         /*!< 0FF8: Component Identification Register 2                          */
   __I  uint32_t  CID3;                         /*!< 0FFC: Component Identification Register 3                          */
} BP_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'BP' Position & Mask macros                          ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- BP_CTRL                                  ------ */
#define BP_CTRL_ENABLE_MASK                      (0x01UL << BP_CTRL_ENABLE_SHIFT)                    /*!< BP_CTRL: ENABLE Mask                    */
#define BP_CTRL_ENABLE_SHIFT                     0                                                   /*!< BP_CTRL: ENABLE Position                */
#define BP_CTRL_KEY_MASK                         (0x01UL << BP_CTRL_KEY_SHIFT)                       /*!< BP_CTRL: KEY Mask                       */
#define BP_CTRL_KEY_SHIFT                        1                                                   /*!< BP_CTRL: KEY Position                   */
#define BP_CTRL_NUM_CODE_MASK                    (0x0FUL << BP_CTRL_NUM_CODE_SHIFT)                  /*!< BP_CTRL: NUM_CODE Mask                  */
#define BP_CTRL_NUM_CODE_SHIFT                   4                                                   /*!< BP_CTRL: NUM_CODE Position              */
#define BP_CTRL_NUM_CODE(x)                      (((x)<<BP_CTRL_NUM_CODE_SHIFT)&BP_CTRL_NUM_CODE_MASK) /*!< BP_CTRL                                 */

/* ------- BP_COMP0                                 ------ */
#define BP_COMP0_ENABLE_MASK                     (0x01UL << BP_COMP0_ENABLE_SHIFT)                   /*!< BP_COMP0: ENABLE Mask                   */
#define BP_COMP0_ENABLE_SHIFT                    0                                                   /*!< BP_COMP0: ENABLE Position               */
#define BP_COMP0_COMP_MASK                       (0x7FFFFFFUL << BP_COMP0_COMP_SHIFT)                /*!< BP_COMP0: COMP Mask                     */
#define BP_COMP0_COMP_SHIFT                      2                                                   /*!< BP_COMP0: COMP Position                 */
#define BP_COMP0_COMP(x)                         (((x)<<BP_COMP0_COMP_SHIFT)&BP_COMP0_COMP_MASK)     /*!< BP_COMP0                                */
#define BP_COMP0_BP_MATCH_MASK                   (0x03UL << BP_COMP0_BP_MATCH_SHIFT)                 /*!< BP_COMP0: BP_MATCH Mask                 */
#define BP_COMP0_BP_MATCH_SHIFT                  30                                                  /*!< BP_COMP0: BP_MATCH Position             */
#define BP_COMP0_BP_MATCH(x)                     (((x)<<BP_COMP0_BP_MATCH_SHIFT)&BP_COMP0_BP_MATCH_MASK) /*!< BP_COMP0                                */

/* ------- BP_COMP1                                 ------ */
#define BP_COMP1_ENABLE_MASK                     (0x01UL << BP_COMP1_ENABLE_SHIFT)                   /*!< BP_COMP1: ENABLE Mask                   */
#define BP_COMP1_ENABLE_SHIFT                    0                                                   /*!< BP_COMP1: ENABLE Position               */
#define BP_COMP1_COMP_MASK                       (0x7FFFFFFUL << BP_COMP1_COMP_SHIFT)                /*!< BP_COMP1: COMP Mask                     */
#define BP_COMP1_COMP_SHIFT                      2                                                   /*!< BP_COMP1: COMP Position                 */
#define BP_COMP1_COMP(x)                         (((x)<<BP_COMP1_COMP_SHIFT)&BP_COMP1_COMP_MASK)     /*!< BP_COMP1                                */
#define BP_COMP1_REPLACE_MASK                    (0x03UL << BP_COMP1_REPLACE_SHIFT)                  /*!< BP_COMP1: REPLACE Mask                  */
#define BP_COMP1_REPLACE_SHIFT                   30                                                  /*!< BP_COMP1: REPLACE Position              */
#define BP_COMP1_REPLACE(x)                      (((x)<<BP_COMP1_REPLACE_SHIFT)&BP_COMP1_REPLACE_MASK) /*!< BP_COMP1                                */

/* ------- BP_PID4                                  ------ */
#define BP_PID4_JEP106_MASK                      (0x0FUL << BP_PID4_JEP106_SHIFT)                    /*!< BP_PID4: JEP106 Mask                    */
#define BP_PID4_JEP106_SHIFT                     0                                                   /*!< BP_PID4: JEP106 Position                */
#define BP_PID4_JEP106(x)                        (((x)<<BP_PID4_JEP106_SHIFT)&BP_PID4_JEP106_MASK)   /*!< BP_PID4                                 */
#define BP_PID4_c4KB_MASK                        (0x0FUL << BP_PID4_c4KB_SHIFT)                      /*!< BP_PID4: c4KB Mask                      */
#define BP_PID4_c4KB_SHIFT                       4                                                   /*!< BP_PID4: c4KB Position                  */
#define BP_PID4_c4KB(x)                          (((x)<<BP_PID4_c4KB_SHIFT)&BP_PID4_c4KB_MASK)       /*!< BP_PID4                                 */

/* ------- BP_PID                                   ------ */

/* ------- BP_PID0                                  ------ */
#define BP_PID0_PartNumber_MASK                  (0xFFUL << BP_PID0_PartNumber_SHIFT)                /*!< BP_PID0: PartNumber Mask                */
#define BP_PID0_PartNumber_SHIFT                 0                                                   /*!< BP_PID0: PartNumber Position            */
#define BP_PID0_PartNumber(x)                    (((x)<<BP_PID0_PartNumber_SHIFT)&BP_PID0_PartNumber_MASK) /*!< BP_PID0                                 */

/* ------- BP_PID1                                  ------ */
#define BP_PID1_PartNumber_MASK                  (0x0FUL << BP_PID1_PartNumber_SHIFT)                /*!< BP_PID1: PartNumber Mask                */
#define BP_PID1_PartNumber_SHIFT                 0                                                   /*!< BP_PID1: PartNumber Position            */
#define BP_PID1_PartNumber(x)                    (((x)<<BP_PID1_PartNumber_SHIFT)&BP_PID1_PartNumber_MASK) /*!< BP_PID1                                 */
#define BP_PID1_JEP106_identity_code_MASK        (0x0FUL << BP_PID1_JEP106_identity_code_SHIFT)      /*!< BP_PID1: JEP106_identity_code Mask      */
#define BP_PID1_JEP106_identity_code_SHIFT       4                                                   /*!< BP_PID1: JEP106_identity_code Position  */
#define BP_PID1_JEP106_identity_code(x)          (((x)<<BP_PID1_JEP106_identity_code_SHIFT)&BP_PID1_JEP106_identity_code_MASK) /*!< BP_PID1                                 */

/* ------- BP_PID2                                  ------ */
#define BP_PID2_JEP106_identity_code_MASK        (0x07UL << BP_PID2_JEP106_identity_code_SHIFT)      /*!< BP_PID2: JEP106_identity_code Mask      */
#define BP_PID2_JEP106_identity_code_SHIFT       0                                                   /*!< BP_PID2: JEP106_identity_code Position  */
#define BP_PID2_JEP106_identity_code(x)          (((x)<<BP_PID2_JEP106_identity_code_SHIFT)&BP_PID2_JEP106_identity_code_MASK) /*!< BP_PID2                                 */
#define BP_PID2_JEP106_identity_code_used_MASK   (0x01UL << BP_PID2_JEP106_identity_code_used_SHIFT) /*!< BP_PID2: JEP106_identity_code_used Mask */
#define BP_PID2_JEP106_identity_code_used_SHIFT  3                                                   /*!< BP_PID2: JEP106_identity_code_used Position*/
#define BP_PID2_Revision_MASK                    (0x0FUL << BP_PID2_Revision_SHIFT)                  /*!< BP_PID2: Revision Mask                  */
#define BP_PID2_Revision_SHIFT                   4                                                   /*!< BP_PID2: Revision Position              */
#define BP_PID2_Revision(x)                      (((x)<<BP_PID2_Revision_SHIFT)&BP_PID2_Revision_MASK) /*!< BP_PID2                                 */

/* ------- BP_PID3                                  ------ */
#define BP_PID3_CustomerModified_MASK            (0x0FUL << BP_PID3_CustomerModified_SHIFT)          /*!< BP_PID3: CustomerModified Mask          */
#define BP_PID3_CustomerModified_SHIFT           0                                                   /*!< BP_PID3: CustomerModified Position      */
#define BP_PID3_CustomerModified(x)              (((x)<<BP_PID3_CustomerModified_SHIFT)&BP_PID3_CustomerModified_MASK) /*!< BP_PID3                                 */
#define BP_PID3_RevAnd_MASK                      (0x0FUL << BP_PID3_RevAnd_SHIFT)                    /*!< BP_PID3: RevAnd Mask                    */
#define BP_PID3_RevAnd_SHIFT                     4                                                   /*!< BP_PID3: RevAnd Position                */
#define BP_PID3_RevAnd(x)                        (((x)<<BP_PID3_RevAnd_SHIFT)&BP_PID3_RevAnd_MASK)   /*!< BP_PID3                                 */

/* ------- BP_CID0                                  ------ */
#define BP_CID0_Preamble_MASK                    (0xFFUL << BP_CID0_Preamble_SHIFT)                  /*!< BP_CID0: Preamble Mask                  */
#define BP_CID0_Preamble_SHIFT                   0                                                   /*!< BP_CID0: Preamble Position              */
#define BP_CID0_Preamble(x)                      (((x)<<BP_CID0_Preamble_SHIFT)&BP_CID0_Preamble_MASK) /*!< BP_CID0                                 */

/* ------- BP_CID1                                  ------ */
#define BP_CID1_Preamble_MASK                    (0x0FUL << BP_CID1_Preamble_SHIFT)                  /*!< BP_CID1: Preamble Mask                  */
#define BP_CID1_Preamble_SHIFT                   0                                                   /*!< BP_CID1: Preamble Position              */
#define BP_CID1_Preamble(x)                      (((x)<<BP_CID1_Preamble_SHIFT)&BP_CID1_Preamble_MASK) /*!< BP_CID1                                 */
#define BP_CID1_ComponentClass_MASK              (0x0FUL << BP_CID1_ComponentClass_SHIFT)            /*!< BP_CID1: ComponentClass Mask            */
#define BP_CID1_ComponentClass_SHIFT             4                                                   /*!< BP_CID1: ComponentClass Position        */
#define BP_CID1_ComponentClass(x)                (((x)<<BP_CID1_ComponentClass_SHIFT)&BP_CID1_ComponentClass_MASK) /*!< BP_CID1                                 */

/* ------- BP_CID2                                  ------ */
#define BP_CID2_Preamble_MASK                    (0xFFUL << BP_CID2_Preamble_SHIFT)                  /*!< BP_CID2: Preamble Mask                  */
#define BP_CID2_Preamble_SHIFT                   0                                                   /*!< BP_CID2: Preamble Position              */
#define BP_CID2_Preamble(x)                      (((x)<<BP_CID2_Preamble_SHIFT)&BP_CID2_Preamble_MASK) /*!< BP_CID2                                 */

/* ------- BP_CID3                                  ------ */
#define BP_CID3_Preamble_MASK                    (0xFFUL << BP_CID3_Preamble_SHIFT)                  /*!< BP_CID3: Preamble Mask                  */
#define BP_CID3_Preamble_SHIFT                   0                                                   /*!< BP_CID3: Preamble Position              */
#define BP_CID3_Preamble(x)                      (((x)<<BP_CID3_Preamble_SHIFT)&BP_CID3_Preamble_MASK) /*!< BP_CID3                                 */

/* -------------------------------------------------------------------------------- */
/* -----------     'BP' Register Access macros                          ----------- */
/* -------------------------------------------------------------------------------- */

#define BP_CTRL                        (BP->CTRL)
#define BP_COMP0                       (BP->COMP0)
#define BP_COMP1                       (BP->COMP1)
#define BP_PID4                        (BP->PID4)
#define BP_PID5                        (BP->PID5)
#define BP_PID6                        (BP->PID6)
#define BP_PID7                        (BP->PID7)
#define BP_PID0                        (BP->PID0)
#define BP_PID1                        (BP->PID1)
#define BP_PID2                        (BP->PID2)
#define BP_PID3                        (BP->PID3)
#define BP_CID0                        (BP->CID0)
#define BP_CID1                        (BP->CID1)
#define BP_CID2                        (BP->CID2)
#define BP_CID3                        (BP->CID3)

/* ================================================================================ */
/* ================           CMP0 (file:CMP0_MKL_DMA)             ================ */
/* ================================================================================ */

/**
 * @brief Comparator, Voltage Ref, D-to-A Converter and Analog Mux
 */
typedef struct {                                /*!<       CMP0 Structure                                               */
   __IO uint8_t   CR0;                          /*!< 0000: CMP Control Register 0                                       */
   __IO uint8_t   CR1;                          /*!< 0001: CMP Control Register 1                                       */
   __IO uint8_t   FPR;                          /*!< 0002: CMP Filter Period Register                                   */
   __IO uint8_t   SCR;                          /*!< 0003: CMP Status and Control Register                              */
   __IO uint8_t   DACCR;                        /*!< 0004: DAC Control Register                                         */
   __IO uint8_t   MUXCR;                        /*!< 0005: MUX Control Register                                         */
} CMP0_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'CMP0' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- CMP0_CR0                                 ------ */
#define CMP_CR0_HYSTCTR_MASK                     (0x03UL << CMP_CR0_HYSTCTR_SHIFT)                   /*!< CMP0_CR0: HYSTCTR Mask                  */
#define CMP_CR0_HYSTCTR_SHIFT                    0                                                   /*!< CMP0_CR0: HYSTCTR Position              */
#define CMP_CR0_HYSTCTR(x)                       (((x)<<CMP_CR0_HYSTCTR_SHIFT)&CMP_CR0_HYSTCTR_MASK) /*!< CMP0_CR0                                */
#define CMP_CR0_FILTER_CNT_MASK                  (0x07UL << CMP_CR0_FILTER_CNT_SHIFT)                /*!< CMP0_CR0: FILTER_CNT Mask               */
#define CMP_CR0_FILTER_CNT_SHIFT                 4                                                   /*!< CMP0_CR0: FILTER_CNT Position           */
#define CMP_CR0_FILTER_CNT(x)                    (((x)<<CMP_CR0_FILTER_CNT_SHIFT)&CMP_CR0_FILTER_CNT_MASK) /*!< CMP0_CR0                                */

/* ------- CMP0_CR1                                 ------ */
#define CMP_CR1_EN_MASK                          (0x01UL << CMP_CR1_EN_SHIFT)                        /*!< CMP0_CR1: EN Mask                       */
#define CMP_CR1_EN_SHIFT                         0                                                   /*!< CMP0_CR1: EN Position                   */
#define CMP_CR1_OPE_MASK                         (0x01UL << CMP_CR1_OPE_SHIFT)                       /*!< CMP0_CR1: OPE Mask                      */
#define CMP_CR1_OPE_SHIFT                        1                                                   /*!< CMP0_CR1: OPE Position                  */
#define CMP_CR1_COS_MASK                         (0x01UL << CMP_CR1_COS_SHIFT)                       /*!< CMP0_CR1: COS Mask                      */
#define CMP_CR1_COS_SHIFT                        2                                                   /*!< CMP0_CR1: COS Position                  */
#define CMP_CR1_INV_MASK                         (0x01UL << CMP_CR1_INV_SHIFT)                       /*!< CMP0_CR1: INV Mask                      */
#define CMP_CR1_INV_SHIFT                        3                                                   /*!< CMP0_CR1: INV Position                  */
#define CMP_CR1_PMODE_MASK                       (0x01UL << CMP_CR1_PMODE_SHIFT)                     /*!< CMP0_CR1: PMODE Mask                    */
#define CMP_CR1_PMODE_SHIFT                      4                                                   /*!< CMP0_CR1: PMODE Position                */
#define CMP_CR1_TRIGM_MASK                       (0x01UL << CMP_CR1_TRIGM_SHIFT)                     /*!< CMP0_CR1: TRIGM Mask                    */
#define CMP_CR1_TRIGM_SHIFT                      5                                                   /*!< CMP0_CR1: TRIGM Position                */
#define CMP_CR1_WE_MASK                          (0x01UL << CMP_CR1_WE_SHIFT)                        /*!< CMP0_CR1: WE Mask                       */
#define CMP_CR1_WE_SHIFT                         6                                                   /*!< CMP0_CR1: WE Position                   */
#define CMP_CR1_SE_MASK                          (0x01UL << CMP_CR1_SE_SHIFT)                        /*!< CMP0_CR1: SE Mask                       */
#define CMP_CR1_SE_SHIFT                         7                                                   /*!< CMP0_CR1: SE Position                   */

/* ------- CMP0_FPR                                 ------ */
#define CMP_FPR_FILT_PER_MASK                    (0xFFUL << CMP_FPR_FILT_PER_SHIFT)                  /*!< CMP0_FPR: FILT_PER Mask                 */
#define CMP_FPR_FILT_PER_SHIFT                   0                                                   /*!< CMP0_FPR: FILT_PER Position             */
#define CMP_FPR_FILT_PER(x)                      (((x)<<CMP_FPR_FILT_PER_SHIFT)&CMP_FPR_FILT_PER_MASK) /*!< CMP0_FPR                                */

/* ------- CMP0_SCR                                 ------ */
#define CMP_SCR_COUT_MASK                        (0x01UL << CMP_SCR_COUT_SHIFT)                      /*!< CMP0_SCR: COUT Mask                     */
#define CMP_SCR_COUT_SHIFT                       0                                                   /*!< CMP0_SCR: COUT Position                 */
#define CMP_SCR_CFF_MASK                         (0x01UL << CMP_SCR_CFF_SHIFT)                       /*!< CMP0_SCR: CFF Mask                      */
#define CMP_SCR_CFF_SHIFT                        1                                                   /*!< CMP0_SCR: CFF Position                  */
#define CMP_SCR_CFR_MASK                         (0x01UL << CMP_SCR_CFR_SHIFT)                       /*!< CMP0_SCR: CFR Mask                      */
#define CMP_SCR_CFR_SHIFT                        2                                                   /*!< CMP0_SCR: CFR Position                  */
#define CMP_SCR_IEF_MASK                         (0x01UL << CMP_SCR_IEF_SHIFT)                       /*!< CMP0_SCR: IEF Mask                      */
#define CMP_SCR_IEF_SHIFT                        3                                                   /*!< CMP0_SCR: IEF Position                  */
#define CMP_SCR_IER_MASK                         (0x01UL << CMP_SCR_IER_SHIFT)                       /*!< CMP0_SCR: IER Mask                      */
#define CMP_SCR_IER_SHIFT                        4                                                   /*!< CMP0_SCR: IER Position                  */
#define CMP_SCR_DMAEN_MASK                       (0x01UL << CMP_SCR_DMAEN_SHIFT)                     /*!< CMP0_SCR: DMAEN Mask                    */
#define CMP_SCR_DMAEN_SHIFT                      6                                                   /*!< CMP0_SCR: DMAEN Position                */

/* ------- CMP0_DACCR                               ------ */
#define CMP_DACCR_VOSEL_MASK                     (0x3FUL << CMP_DACCR_VOSEL_SHIFT)                   /*!< CMP0_DACCR: VOSEL Mask                  */
#define CMP_DACCR_VOSEL_SHIFT                    0                                                   /*!< CMP0_DACCR: VOSEL Position              */
#define CMP_DACCR_VOSEL(x)                       (((x)<<CMP_DACCR_VOSEL_SHIFT)&CMP_DACCR_VOSEL_MASK) /*!< CMP0_DACCR                              */
#define CMP_DACCR_VRSEL_MASK                     (0x01UL << CMP_DACCR_VRSEL_SHIFT)                   /*!< CMP0_DACCR: VRSEL Mask                  */
#define CMP_DACCR_VRSEL_SHIFT                    6                                                   /*!< CMP0_DACCR: VRSEL Position              */
#define CMP_DACCR_DACEN_MASK                     (0x01UL << CMP_DACCR_DACEN_SHIFT)                   /*!< CMP0_DACCR: DACEN Mask                  */
#define CMP_DACCR_DACEN_SHIFT                    7                                                   /*!< CMP0_DACCR: DACEN Position              */

/* ------- CMP0_MUXCR                               ------ */
#define CMP_MUXCR_MSEL_MASK                      (0x07UL << CMP_MUXCR_MSEL_SHIFT)                    /*!< CMP0_MUXCR: MSEL Mask                   */
#define CMP_MUXCR_MSEL_SHIFT                     0                                                   /*!< CMP0_MUXCR: MSEL Position               */
#define CMP_MUXCR_MSEL(x)                        (((x)<<CMP_MUXCR_MSEL_SHIFT)&CMP_MUXCR_MSEL_MASK)   /*!< CMP0_MUXCR                              */
#define CMP_MUXCR_PSEL_MASK                      (0x07UL << CMP_MUXCR_PSEL_SHIFT)                    /*!< CMP0_MUXCR: PSEL Mask                   */
#define CMP_MUXCR_PSEL_SHIFT                     3                                                   /*!< CMP0_MUXCR: PSEL Position               */
#define CMP_MUXCR_PSEL(x)                        (((x)<<CMP_MUXCR_PSEL_SHIFT)&CMP_MUXCR_PSEL_MASK)   /*!< CMP0_MUXCR                              */
#define CMP_MUXCR_PSTM_MASK                      (0x01UL << CMP_MUXCR_PSTM_SHIFT)                    /*!< CMP0_MUXCR: PSTM Mask                   */
#define CMP_MUXCR_PSTM_SHIFT                     7                                                   /*!< CMP0_MUXCR: PSTM Position               */

/* -------------------------------------------------------------------------------- */
/* -----------     'CMP0' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define CMP0_CR0                       (CMP0->CR0)
#define CMP0_CR1                       (CMP0->CR1)
#define CMP0_FPR                       (CMP0->FPR)
#define CMP0_SCR                       (CMP0->SCR)
#define CMP0_DACCR                     (CMP0->DACCR)
#define CMP0_MUXCR                     (CMP0->MUXCR)

/* ================================================================================ */
/* ================           DAC0 (file:DAC0_MKLZ4)               ================ */
/* ================================================================================ */

/**
 * @brief 12-Bit Digital-to-Analog Converter
 */
typedef struct {                                /*!<       DAC0 Structure                                               */
   struct { /* (cluster) */                     /*!< 0000: (size=0x0004, 4)                                             */
      union {                                   /*!< 0000: (size=0002)                                                  */
         __IO uint16_t  DATA;                   /*!< 0000: Data Register                                                */
         struct {                               /*!< 0000: (size=0002)                                                  */
            __IO uint8_t   DATL;                /*!< 0000: Data Low Register                                            */
            __IO uint8_t   DATH;                /*!< 0001: Data High Register                                           */
         };
      };
   } DAT[2];
   __I  uint32_t  RESERVED0[7];                 /*!< 0004:                                                              */
   __IO uint8_t   SR;                           /*!< 0020: Status Register                                              */
   __IO uint8_t   C0;                           /*!< 0021: Control Register 0                                           */
   __IO uint8_t   C1;                           /*!< 0022: Control Register 1                                           */
   __IO uint8_t   C2;                           /*!< 0023: Control Register 2                                           */
} DAC0_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'DAC0' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- DAC0_DATA                                ------ */
#define DAC_DATA_DATA_MASK                       (0x7FFUL << DAC_DATA_DATA_SHIFT)                    /*!< DAC0_DATA: DATA Mask                    */
#define DAC_DATA_DATA_SHIFT                      0                                                   /*!< DAC0_DATA: DATA Position                */
#define DAC_DATA_DATA(x)                         (((x)<<DAC_DATA_DATA_SHIFT)&DAC_DATA_DATA_MASK)     /*!< DAC0_DATA                               */

/* ------- DAC0_DATL                                ------ */
#define DAC_DATL_DATA_MASK                       (0xFFUL << DAC_DATL_DATA_SHIFT)                     /*!< DAC0_DATL: DATA Mask                    */
#define DAC_DATL_DATA_SHIFT                      0                                                   /*!< DAC0_DATL: DATA Position                */
#define DAC_DATL_DATA(x)                         (((x)<<DAC_DATL_DATA_SHIFT)&DAC_DATL_DATA_MASK)     /*!< DAC0_DATL                               */

/* ------- DAC0_DATH                                ------ */
#define DAC_DATH_DATA_MASK                       (0x0FUL << DAC_DATH_DATA_SHIFT)                     /*!< DAC0_DATH: DATA Mask                    */
#define DAC_DATH_DATA_SHIFT                      0                                                   /*!< DAC0_DATH: DATA Position                */
#define DAC_DATH_DATA(x)                         (((x)<<DAC_DATH_DATA_SHIFT)&DAC_DATH_DATA_MASK)     /*!< DAC0_DATH                               */

/* ------- DAC0_SR                                  ------ */
#define DAC_SR_DACBFRPBF_MASK                    (0x01UL << DAC_SR_DACBFRPBF_SHIFT)                  /*!< DAC0_SR: DACBFRPBF Mask                 */
#define DAC_SR_DACBFRPBF_SHIFT                   0                                                   /*!< DAC0_SR: DACBFRPBF Position             */
#define DAC_SR_DACBFRPTF_MASK                    (0x01UL << DAC_SR_DACBFRPTF_SHIFT)                  /*!< DAC0_SR: DACBFRPTF Mask                 */
#define DAC_SR_DACBFRPTF_SHIFT                   1                                                   /*!< DAC0_SR: DACBFRPTF Position             */

/* ------- DAC0_C0                                  ------ */
#define DAC_C0_DACBBIEN_MASK                     (0x01UL << DAC_C0_DACBBIEN_SHIFT)                   /*!< DAC0_C0: DACBBIEN Mask                  */
#define DAC_C0_DACBBIEN_SHIFT                    0                                                   /*!< DAC0_C0: DACBBIEN Position              */
#define DAC_C0_DACBTIEN_MASK                     (0x01UL << DAC_C0_DACBTIEN_SHIFT)                   /*!< DAC0_C0: DACBTIEN Mask                  */
#define DAC_C0_DACBTIEN_SHIFT                    1                                                   /*!< DAC0_C0: DACBTIEN Position              */
#define DAC_C0_DACBWIEN_MASK                     (0x01UL << DAC_C0_DACBWIEN_SHIFT)                   /*!< DAC0_C0: DACBWIEN Mask                  */
#define DAC_C0_DACBWIEN_SHIFT                    2                                                   /*!< DAC0_C0: DACBWIEN Position              */
#define DAC_C0_LPEN_MASK                         (0x01UL << DAC_C0_LPEN_SHIFT)                       /*!< DAC0_C0: LPEN Mask                      */
#define DAC_C0_LPEN_SHIFT                        3                                                   /*!< DAC0_C0: LPEN Position                  */
#define DAC_C0_DACSWTRG_MASK                     (0x01UL << DAC_C0_DACSWTRG_SHIFT)                   /*!< DAC0_C0: DACSWTRG Mask                  */
#define DAC_C0_DACSWTRG_SHIFT                    4                                                   /*!< DAC0_C0: DACSWTRG Position              */
#define DAC_C0_DACTRGSEL_MASK                    (0x01UL << DAC_C0_DACTRGSEL_SHIFT)                  /*!< DAC0_C0: DACTRGSEL Mask                 */
#define DAC_C0_DACTRGSEL_SHIFT                   5                                                   /*!< DAC0_C0: DACTRGSEL Position             */
#define DAC_C0_DACRFS_MASK                       (0x01UL << DAC_C0_DACRFS_SHIFT)                     /*!< DAC0_C0: DACRFS Mask                    */
#define DAC_C0_DACRFS_SHIFT                      6                                                   /*!< DAC0_C0: DACRFS Position                */
#define DAC_C0_DACEN_MASK                        (0x01UL << DAC_C0_DACEN_SHIFT)                      /*!< DAC0_C0: DACEN Mask                     */
#define DAC_C0_DACEN_SHIFT                       7                                                   /*!< DAC0_C0: DACEN Position                 */

/* ------- DAC0_C1                                  ------ */
#define DAC_C1_DACBFEN_MASK                      (0x01UL << DAC_C1_DACBFEN_SHIFT)                    /*!< DAC0_C1: DACBFEN Mask                   */
#define DAC_C1_DACBFEN_SHIFT                     0                                                   /*!< DAC0_C1: DACBFEN Position               */
#define DAC_C1_DACBFMD_MASK                      (0x01UL << DAC_C1_DACBFMD_SHIFT)                    /*!< DAC0_C1: DACBFMD Mask                   */
#define DAC_C1_DACBFMD_SHIFT                     2                                                   /*!< DAC0_C1: DACBFMD Position               */
#define DAC_C1_DMAEN_MASK                        (0x01UL << DAC_C1_DMAEN_SHIFT)                      /*!< DAC0_C1: DMAEN Mask                     */
#define DAC_C1_DMAEN_SHIFT                       7                                                   /*!< DAC0_C1: DMAEN Position                 */

/* ------- DAC0_C2                                  ------ */
#define DAC_C2_DACBFUP_MASK                      (0x01UL << DAC_C2_DACBFUP_SHIFT)                    /*!< DAC0_C2: DACBFUP Mask                   */
#define DAC_C2_DACBFUP_SHIFT                     0                                                   /*!< DAC0_C2: DACBFUP Position               */
#define DAC_C2_DACBFRP_MASK                      (0x01UL << DAC_C2_DACBFRP_SHIFT)                    /*!< DAC0_C2: DACBFRP Mask                   */
#define DAC_C2_DACBFRP_SHIFT                     4                                                   /*!< DAC0_C2: DACBFRP Position               */

/* -------------------------------------------------------------------------------- */
/* -----------     'DAC0' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define DAC0_DATA0                     (DAC0->DAT[0].DATA)
#define DAC0_DAT0L                     (DAC0->DAT[0].DATL)
#define DAC0_DAT0H                     (DAC0->DAT[0].DATH)
#define DAC0_DATA1                     (DAC0->DAT[1].DATA)
#define DAC0_DAT1L                     (DAC0->DAT[1].DATL)
#define DAC0_DAT1H                     (DAC0->DAT[1].DATH)
#define DAC0_SR                        (DAC0->SR)
#define DAC0_C0                        (DAC0->C0)
#define DAC0_C1                        (DAC0->C1)
#define DAC0_C2                        (DAC0->C2)

/* ================================================================================ */
/* ================           DMA (file:DMA_MKLZ4)                 ================ */
/* ================================================================================ */

/**
 * @brief DMA Controller
 */
typedef struct {                                /*!<       DMA Structure                                                */
   __I  uint32_t  RESERVED0[64];                /*!< 0000:                                                              */
   struct { /* (cluster) */                     /*!< 0100: (size=0x0040, 64)                                            */
      __IO uint32_t  SAR;                       /*!< 0100: Source Address Register                                      */
      __IO uint32_t  DAR;                       /*!< 0104: Destination Address Register                                 */
      union {                                   /*!< 0100: (size=0004)                                                  */
         __IO uint32_t  DSR_BCR;                /*!< 0108: DMA Status Register / Byte Count Register                    */
         struct {                               /*!< 0100: (size=0004)                                                  */
            __I  uint8_t   RESERVED0[3];        /*!< 0108:                                                              */
            __IO uint8_t   DSR;                 /*!< 010B: DMA Status Register                                          */
         };
      };
      __IO uint32_t  DCR;                       /*!< 010C: DMA Control Register                                         */
   } CHANNEL[4];
} DMA_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'DMA' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- DMA_SAR                                  ------ */
#define DMA_SAR_SAR_MASK                         (0xFFFFFFFFUL << DMA_SAR_SAR_SHIFT)                 /*!< DMA_SAR: SAR Mask                       */
#define DMA_SAR_SAR_SHIFT                        0                                                   /*!< DMA_SAR: SAR Position                   */
#define DMA_SAR_SAR(x)                           (((x)<<DMA_SAR_SAR_SHIFT)&DMA_SAR_SAR_MASK)         /*!< DMA_SAR                                 */

/* ------- DMA_DAR                                  ------ */
#define DMA_DAR_DAR_MASK                         (0xFFFFFFFFUL << DMA_DAR_DAR_SHIFT)                 /*!< DMA_DAR: DAR Mask                       */
#define DMA_DAR_DAR_SHIFT                        0                                                   /*!< DMA_DAR: DAR Position                   */
#define DMA_DAR_DAR(x)                           (((x)<<DMA_DAR_DAR_SHIFT)&DMA_DAR_DAR_MASK)         /*!< DMA_DAR                                 */

/* ------- DMA_DSR_BCR                              ------ */
#define DMA_DSR_BCR_BCR_MASK                     (0xFFFFFFUL << DMA_DSR_BCR_BCR_SHIFT)               /*!< DMA_DSR_BCR: BCR Mask                   */
#define DMA_DSR_BCR_BCR_SHIFT                    0                                                   /*!< DMA_DSR_BCR: BCR Position               */
#define DMA_DSR_BCR_BCR(x)                       (((x)<<DMA_DSR_BCR_BCR_SHIFT)&DMA_DSR_BCR_BCR_MASK) /*!< DMA_DSR_BCR                             */
#define DMA_DSR_BCR_DONE_MASK                    (0x01UL << DMA_DSR_BCR_DONE_SHIFT)                  /*!< DMA_DSR_BCR: DONE Mask                  */
#define DMA_DSR_BCR_DONE_SHIFT                   24                                                  /*!< DMA_DSR_BCR: DONE Position              */
#define DMA_DSR_BCR_BSY_MASK                     (0x01UL << DMA_DSR_BCR_BSY_SHIFT)                   /*!< DMA_DSR_BCR: BSY Mask                   */
#define DMA_DSR_BCR_BSY_SHIFT                    25                                                  /*!< DMA_DSR_BCR: BSY Position               */
#define DMA_DSR_BCR_REQ_MASK                     (0x01UL << DMA_DSR_BCR_REQ_SHIFT)                   /*!< DMA_DSR_BCR: REQ Mask                   */
#define DMA_DSR_BCR_REQ_SHIFT                    26                                                  /*!< DMA_DSR_BCR: REQ Position               */
#define DMA_DSR_BCR_BED_MASK                     (0x01UL << DMA_DSR_BCR_BED_SHIFT)                   /*!< DMA_DSR_BCR: BED Mask                   */
#define DMA_DSR_BCR_BED_SHIFT                    28                                                  /*!< DMA_DSR_BCR: BED Position               */
#define DMA_DSR_BCR_BES_MASK                     (0x01UL << DMA_DSR_BCR_BES_SHIFT)                   /*!< DMA_DSR_BCR: BES Mask                   */
#define DMA_DSR_BCR_BES_SHIFT                    29                                                  /*!< DMA_DSR_BCR: BES Position               */
#define DMA_DSR_BCR_CE_MASK                      (0x01UL << DMA_DSR_BCR_CE_SHIFT)                    /*!< DMA_DSR_BCR: CE Mask                    */
#define DMA_DSR_BCR_CE_SHIFT                     30                                                  /*!< DMA_DSR_BCR: CE Position                */

/* ------- DMA_DSR                                  ------ */
#define DMA_DSR_DONE_MASK                        (0x01UL << DMA_DSR_DONE_SHIFT)                      /*!< DMA_DSR: DONE Mask                      */
#define DMA_DSR_DONE_SHIFT                       0                                                   /*!< DMA_DSR: DONE Position                  */
#define DMA_DSR_BSY_MASK                         (0x01UL << DMA_DSR_BSY_SHIFT)                       /*!< DMA_DSR: BSY Mask                       */
#define DMA_DSR_BSY_SHIFT                        1                                                   /*!< DMA_DSR: BSY Position                   */
#define DMA_DSR_REQ_MASK                         (0x01UL << DMA_DSR_REQ_SHIFT)                       /*!< DMA_DSR: REQ Mask                       */
#define DMA_DSR_REQ_SHIFT                        2                                                   /*!< DMA_DSR: REQ Position                   */
#define DMA_DSR_BED_MASK                         (0x01UL << DMA_DSR_BED_SHIFT)                       /*!< DMA_DSR: BED Mask                       */
#define DMA_DSR_BED_SHIFT                        4                                                   /*!< DMA_DSR: BED Position                   */
#define DMA_DSR_BES_MASK                         (0x01UL << DMA_DSR_BES_SHIFT)                       /*!< DMA_DSR: BES Mask                       */
#define DMA_DSR_BES_SHIFT                        5                                                   /*!< DMA_DSR: BES Position                   */
#define DMA_DSR_CE_MASK                          (0x01UL << DMA_DSR_CE_SHIFT)                        /*!< DMA_DSR: CE Mask                        */
#define DMA_DSR_CE_SHIFT                         6                                                   /*!< DMA_DSR: CE Position                    */

/* ------- DMA_DCR                                  ------ */
#define DMA_DCR_LCH2_MASK                        (0x03UL << DMA_DCR_LCH2_SHIFT)                      /*!< DMA_DCR: LCH2 Mask                      */
#define DMA_DCR_LCH2_SHIFT                       0                                                   /*!< DMA_DCR: LCH2 Position                  */
#define DMA_DCR_LCH2(x)                          (((x)<<DMA_DCR_LCH2_SHIFT)&DMA_DCR_LCH2_MASK)       /*!< DMA_DCR                                 */
#define DMA_DCR_LCH1_MASK                        (0x03UL << DMA_DCR_LCH1_SHIFT)                      /*!< DMA_DCR: LCH1 Mask                      */
#define DMA_DCR_LCH1_SHIFT                       2                                                   /*!< DMA_DCR: LCH1 Position                  */
#define DMA_DCR_LCH1(x)                          (((x)<<DMA_DCR_LCH1_SHIFT)&DMA_DCR_LCH1_MASK)       /*!< DMA_DCR                                 */
#define DMA_DCR_LINKCC_MASK                      (0x03UL << DMA_DCR_LINKCC_SHIFT)                    /*!< DMA_DCR: LINKCC Mask                    */
#define DMA_DCR_LINKCC_SHIFT                     4                                                   /*!< DMA_DCR: LINKCC Position                */
#define DMA_DCR_LINKCC(x)                        (((x)<<DMA_DCR_LINKCC_SHIFT)&DMA_DCR_LINKCC_MASK)   /*!< DMA_DCR                                 */
#define DMA_DCR_D_REQ_MASK                       (0x01UL << DMA_DCR_D_REQ_SHIFT)                     /*!< DMA_DCR: D_REQ Mask                     */
#define DMA_DCR_D_REQ_SHIFT                      7                                                   /*!< DMA_DCR: D_REQ Position                 */
#define DMA_DCR_DMOD_MASK                        (0x0FUL << DMA_DCR_DMOD_SHIFT)                      /*!< DMA_DCR: DMOD Mask                      */
#define DMA_DCR_DMOD_SHIFT                       8                                                   /*!< DMA_DCR: DMOD Position                  */
#define DMA_DCR_DMOD(x)                          (((x)<<DMA_DCR_DMOD_SHIFT)&DMA_DCR_DMOD_MASK)       /*!< DMA_DCR                                 */
#define DMA_DCR_SMOD_MASK                        (0x0FUL << DMA_DCR_SMOD_SHIFT)                      /*!< DMA_DCR: SMOD Mask                      */
#define DMA_DCR_SMOD_SHIFT                       12                                                  /*!< DMA_DCR: SMOD Position                  */
#define DMA_DCR_SMOD(x)                          (((x)<<DMA_DCR_SMOD_SHIFT)&DMA_DCR_SMOD_MASK)       /*!< DMA_DCR                                 */
#define DMA_DCR_START_MASK                       (0x01UL << DMA_DCR_START_SHIFT)                     /*!< DMA_DCR: START Mask                     */
#define DMA_DCR_START_SHIFT                      16                                                  /*!< DMA_DCR: START Position                 */
#define DMA_DCR_DSIZE_MASK                       (0x03UL << DMA_DCR_DSIZE_SHIFT)                     /*!< DMA_DCR: DSIZE Mask                     */
#define DMA_DCR_DSIZE_SHIFT                      17                                                  /*!< DMA_DCR: DSIZE Position                 */
#define DMA_DCR_DSIZE(x)                         (((x)<<DMA_DCR_DSIZE_SHIFT)&DMA_DCR_DSIZE_MASK)     /*!< DMA_DCR                                 */
#define DMA_DCR_DINC_MASK                        (0x01UL << DMA_DCR_DINC_SHIFT)                      /*!< DMA_DCR: DINC Mask                      */
#define DMA_DCR_DINC_SHIFT                       19                                                  /*!< DMA_DCR: DINC Position                  */
#define DMA_DCR_SSIZE_MASK                       (0x03UL << DMA_DCR_SSIZE_SHIFT)                     /*!< DMA_DCR: SSIZE Mask                     */
#define DMA_DCR_SSIZE_SHIFT                      20                                                  /*!< DMA_DCR: SSIZE Position                 */
#define DMA_DCR_SSIZE(x)                         (((x)<<DMA_DCR_SSIZE_SHIFT)&DMA_DCR_SSIZE_MASK)     /*!< DMA_DCR                                 */
#define DMA_DCR_SINC_MASK                        (0x01UL << DMA_DCR_SINC_SHIFT)                      /*!< DMA_DCR: SINC Mask                      */
#define DMA_DCR_SINC_SHIFT                       22                                                  /*!< DMA_DCR: SINC Position                  */
#define DMA_DCR_EADREQ_MASK                      (0x01UL << DMA_DCR_EADREQ_SHIFT)                    /*!< DMA_DCR: EADREQ Mask                    */
#define DMA_DCR_EADREQ_SHIFT                     23                                                  /*!< DMA_DCR: EADREQ Position                */
#define DMA_DCR_AA_MASK                          (0x01UL << DMA_DCR_AA_SHIFT)                        /*!< DMA_DCR: AA Mask                        */
#define DMA_DCR_AA_SHIFT                         28                                                  /*!< DMA_DCR: AA Position                    */
#define DMA_DCR_CS_MASK                          (0x01UL << DMA_DCR_CS_SHIFT)                        /*!< DMA_DCR: CS Mask                        */
#define DMA_DCR_CS_SHIFT                         29                                                  /*!< DMA_DCR: CS Position                    */
#define DMA_DCR_ERQ_MASK                         (0x01UL << DMA_DCR_ERQ_SHIFT)                       /*!< DMA_DCR: ERQ Mask                       */
#define DMA_DCR_ERQ_SHIFT                        30                                                  /*!< DMA_DCR: ERQ Position                   */
#define DMA_DCR_EINT_MASK                        (0x01UL << DMA_DCR_EINT_SHIFT)                      /*!< DMA_DCR: EINT Mask                      */
#define DMA_DCR_EINT_SHIFT                       31                                                  /*!< DMA_DCR: EINT Position                  */

/* -------------------------------------------------------------------------------- */
/* -----------     'DMA' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define DMA_SAR0                       (DMA->CHANNEL[0].SAR)
#define DMA_DAR0                       (DMA->CHANNEL[0].DAR)
#define DMA_DSR_BCR0                   (DMA->CHANNEL[0].DSR_BCR)
#define DMA_DSR0                       (DMA->CHANNEL[0].DSR)
#define DMA_DCR0                       (DMA->CHANNEL[0].DCR)
#define DMA_SAR1                       (DMA->CHANNEL[1].SAR)
#define DMA_DAR1                       (DMA->CHANNEL[1].DAR)
#define DMA_DSR_BCR1                   (DMA->CHANNEL[1].DSR_BCR)
#define DMA_DSR1                       (DMA->CHANNEL[1].DSR)
#define DMA_DCR1                       (DMA->CHANNEL[1].DCR)
#define DMA_SAR2                       (DMA->CHANNEL[2].SAR)
#define DMA_DAR2                       (DMA->CHANNEL[2].DAR)
#define DMA_DSR_BCR2                   (DMA->CHANNEL[2].DSR_BCR)
#define DMA_DSR2                       (DMA->CHANNEL[2].DSR)
#define DMA_DCR2                       (DMA->CHANNEL[2].DCR)
#define DMA_SAR3                       (DMA->CHANNEL[3].SAR)
#define DMA_DAR3                       (DMA->CHANNEL[3].DAR)
#define DMA_DSR_BCR3                   (DMA->CHANNEL[3].DSR_BCR)
#define DMA_DSR3                       (DMA->CHANNEL[3].DSR)
#define DMA_DCR3                       (DMA->CHANNEL[3].DCR)

/* ================================================================================ */
/* ================           DMAMUX (file:DMAMUX_4CH)             ================ */
/* ================================================================================ */

/**
 * @brief DMA channel multiplexor
 */
typedef struct {                                /*!<       DMAMUX Structure                                             */
   __IO uint8_t   CHCFG[4];                     /*!< 0000: Channel Configuration Register                               */
} DMAMUX_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'DMAMUX' Position & Mask macros                      ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- DMAMUX_CHCFG                             ------ */
#define DMAMUX_CHCFG_SOURCE_MASK                 (0x3FUL << DMAMUX_CHCFG_SOURCE_SHIFT)               /*!< DMAMUX_CHCFG: SOURCE Mask               */
#define DMAMUX_CHCFG_SOURCE_SHIFT                0                                                   /*!< DMAMUX_CHCFG: SOURCE Position           */
#define DMAMUX_CHCFG_SOURCE(x)                   (((x)<<DMAMUX_CHCFG_SOURCE_SHIFT)&DMAMUX_CHCFG_SOURCE_MASK) /*!< DMAMUX_CHCFG                            */
#define DMAMUX_CHCFG_TRIG_MASK                   (0x01UL << DMAMUX_CHCFG_TRIG_SHIFT)                 /*!< DMAMUX_CHCFG: TRIG Mask                 */
#define DMAMUX_CHCFG_TRIG_SHIFT                  6                                                   /*!< DMAMUX_CHCFG: TRIG Position             */
#define DMAMUX_CHCFG_ENBL_MASK                   (0x01UL << DMAMUX_CHCFG_ENBL_SHIFT)                 /*!< DMAMUX_CHCFG: ENBL Mask                 */
#define DMAMUX_CHCFG_ENBL_SHIFT                  7                                                   /*!< DMAMUX_CHCFG: ENBL Position             */

/* -------------------------------------------------------------------------------- */
/* -----------     'DMAMUX' Register Access macros                      ----------- */
/* -------------------------------------------------------------------------------- */

#define DMAMUX_CHCFG0                  (DMAMUX->CHCFG[0])
#define DMAMUX_CHCFG1                  (DMAMUX->CHCFG[1])
#define DMAMUX_CHCFG2                  (DMAMUX->CHCFG[2])
#define DMAMUX_CHCFG3                  (DMAMUX->CHCFG[3])

/* ================================================================================ */
/* ================           FGPIOA (file:FGPIOA_0)               ================ */
/* ================================================================================ */

/**
 * @brief General Purpose Input/Output
 */
typedef struct {                                /*!<       FGPIOA Structure                                             */
   __IO uint32_t  PDOR;                         /*!< 0000: Port Data Output Register                                    */
   __O  uint32_t  PSOR;                         /*!< 0004: Port Set Output Register                                     */
   __O  uint32_t  PCOR;                         /*!< 0008: Port Clear Output Register                                   */
   __O  uint32_t  PTOR;                         /*!< 000C: Port Toggle Output Register                                  */
   __I  uint32_t  PDIR;                         /*!< 0010: Port Data Input Register                                     */
   __IO uint32_t  PDDR;                         /*!< 0014: Port Data Direction Register                                 */
} FGPIOA_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'FGPIOA' Position & Mask macros                      ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- FGPIOA_PDOR                              ------ */
#define GPIO_PDOR_PDO0_MASK                      (0x01UL << GPIO_PDOR_PDO0_SHIFT)                    /*!< FGPIOA_PDOR: PDO0 Mask                  */
#define GPIO_PDOR_PDO0_SHIFT                     0                                                   /*!< FGPIOA_PDOR: PDO0 Position              */
#define GPIO_PDOR_PDO1_MASK                      (0x01UL << GPIO_PDOR_PDO1_SHIFT)                    /*!< FGPIOA_PDOR: PDO1 Mask                  */
#define GPIO_PDOR_PDO1_SHIFT                     1                                                   /*!< FGPIOA_PDOR: PDO1 Position              */
#define GPIO_PDOR_PDO2_MASK                      (0x01UL << GPIO_PDOR_PDO2_SHIFT)                    /*!< FGPIOA_PDOR: PDO2 Mask                  */
#define GPIO_PDOR_PDO2_SHIFT                     2                                                   /*!< FGPIOA_PDOR: PDO2 Position              */
#define GPIO_PDOR_PDO3_MASK                      (0x01UL << GPIO_PDOR_PDO3_SHIFT)                    /*!< FGPIOA_PDOR: PDO3 Mask                  */
#define GPIO_PDOR_PDO3_SHIFT                     3                                                   /*!< FGPIOA_PDOR: PDO3 Position              */
#define GPIO_PDOR_PDO4_MASK                      (0x01UL << GPIO_PDOR_PDO4_SHIFT)                    /*!< FGPIOA_PDOR: PDO4 Mask                  */
#define GPIO_PDOR_PDO4_SHIFT                     4                                                   /*!< FGPIOA_PDOR: PDO4 Position              */
#define GPIO_PDOR_PDO5_MASK                      (0x01UL << GPIO_PDOR_PDO5_SHIFT)                    /*!< FGPIOA_PDOR: PDO5 Mask                  */
#define GPIO_PDOR_PDO5_SHIFT                     5                                                   /*!< FGPIOA_PDOR: PDO5 Position              */
#define GPIO_PDOR_PDO6_MASK                      (0x01UL << GPIO_PDOR_PDO6_SHIFT)                    /*!< FGPIOA_PDOR: PDO6 Mask                  */
#define GPIO_PDOR_PDO6_SHIFT                     6                                                   /*!< FGPIOA_PDOR: PDO6 Position              */
#define GPIO_PDOR_PDO7_MASK                      (0x01UL << GPIO_PDOR_PDO7_SHIFT)                    /*!< FGPIOA_PDOR: PDO7 Mask                  */
#define GPIO_PDOR_PDO7_SHIFT                     7                                                   /*!< FGPIOA_PDOR: PDO7 Position              */
#define GPIO_PDOR_PDO8_MASK                      (0x01UL << GPIO_PDOR_PDO8_SHIFT)                    /*!< FGPIOA_PDOR: PDO8 Mask                  */
#define GPIO_PDOR_PDO8_SHIFT                     8                                                   /*!< FGPIOA_PDOR: PDO8 Position              */
#define GPIO_PDOR_PDO9_MASK                      (0x01UL << GPIO_PDOR_PDO9_SHIFT)                    /*!< FGPIOA_PDOR: PDO9 Mask                  */
#define GPIO_PDOR_PDO9_SHIFT                     9                                                   /*!< FGPIOA_PDOR: PDO9 Position              */
#define GPIO_PDOR_PDO10_MASK                     (0x01UL << GPIO_PDOR_PDO10_SHIFT)                   /*!< FGPIOA_PDOR: PDO10 Mask                 */
#define GPIO_PDOR_PDO10_SHIFT                    10                                                  /*!< FGPIOA_PDOR: PDO10 Position             */
#define GPIO_PDOR_PDO11_MASK                     (0x01UL << GPIO_PDOR_PDO11_SHIFT)                   /*!< FGPIOA_PDOR: PDO11 Mask                 */
#define GPIO_PDOR_PDO11_SHIFT                    11                                                  /*!< FGPIOA_PDOR: PDO11 Position             */
#define GPIO_PDOR_PDO12_MASK                     (0x01UL << GPIO_PDOR_PDO12_SHIFT)                   /*!< FGPIOA_PDOR: PDO12 Mask                 */
#define GPIO_PDOR_PDO12_SHIFT                    12                                                  /*!< FGPIOA_PDOR: PDO12 Position             */
#define GPIO_PDOR_PDO13_MASK                     (0x01UL << GPIO_PDOR_PDO13_SHIFT)                   /*!< FGPIOA_PDOR: PDO13 Mask                 */
#define GPIO_PDOR_PDO13_SHIFT                    13                                                  /*!< FGPIOA_PDOR: PDO13 Position             */
#define GPIO_PDOR_PDO14_MASK                     (0x01UL << GPIO_PDOR_PDO14_SHIFT)                   /*!< FGPIOA_PDOR: PDO14 Mask                 */
#define GPIO_PDOR_PDO14_SHIFT                    14                                                  /*!< FGPIOA_PDOR: PDO14 Position             */
#define GPIO_PDOR_PDO15_MASK                     (0x01UL << GPIO_PDOR_PDO15_SHIFT)                   /*!< FGPIOA_PDOR: PDO15 Mask                 */
#define GPIO_PDOR_PDO15_SHIFT                    15                                                  /*!< FGPIOA_PDOR: PDO15 Position             */
#define GPIO_PDOR_PDO16_MASK                     (0x01UL << GPIO_PDOR_PDO16_SHIFT)                   /*!< FGPIOA_PDOR: PDO16 Mask                 */
#define GPIO_PDOR_PDO16_SHIFT                    16                                                  /*!< FGPIOA_PDOR: PDO16 Position             */
#define GPIO_PDOR_PDO17_MASK                     (0x01UL << GPIO_PDOR_PDO17_SHIFT)                   /*!< FGPIOA_PDOR: PDO17 Mask                 */
#define GPIO_PDOR_PDO17_SHIFT                    17                                                  /*!< FGPIOA_PDOR: PDO17 Position             */
#define GPIO_PDOR_PDO18_MASK                     (0x01UL << GPIO_PDOR_PDO18_SHIFT)                   /*!< FGPIOA_PDOR: PDO18 Mask                 */
#define GPIO_PDOR_PDO18_SHIFT                    18                                                  /*!< FGPIOA_PDOR: PDO18 Position             */
#define GPIO_PDOR_PDO19_MASK                     (0x01UL << GPIO_PDOR_PDO19_SHIFT)                   /*!< FGPIOA_PDOR: PDO19 Mask                 */
#define GPIO_PDOR_PDO19_SHIFT                    19                                                  /*!< FGPIOA_PDOR: PDO19 Position             */
#define GPIO_PDOR_PDO20_MASK                     (0x01UL << GPIO_PDOR_PDO20_SHIFT)                   /*!< FGPIOA_PDOR: PDO20 Mask                 */
#define GPIO_PDOR_PDO20_SHIFT                    20                                                  /*!< FGPIOA_PDOR: PDO20 Position             */
#define GPIO_PDOR_PDO21_MASK                     (0x01UL << GPIO_PDOR_PDO21_SHIFT)                   /*!< FGPIOA_PDOR: PDO21 Mask                 */
#define GPIO_PDOR_PDO21_SHIFT                    21                                                  /*!< FGPIOA_PDOR: PDO21 Position             */
#define GPIO_PDOR_PDO22_MASK                     (0x01UL << GPIO_PDOR_PDO22_SHIFT)                   /*!< FGPIOA_PDOR: PDO22 Mask                 */
#define GPIO_PDOR_PDO22_SHIFT                    22                                                  /*!< FGPIOA_PDOR: PDO22 Position             */
#define GPIO_PDOR_PDO23_MASK                     (0x01UL << GPIO_PDOR_PDO23_SHIFT)                   /*!< FGPIOA_PDOR: PDO23 Mask                 */
#define GPIO_PDOR_PDO23_SHIFT                    23                                                  /*!< FGPIOA_PDOR: PDO23 Position             */
#define GPIO_PDOR_PDO24_MASK                     (0x01UL << GPIO_PDOR_PDO24_SHIFT)                   /*!< FGPIOA_PDOR: PDO24 Mask                 */
#define GPIO_PDOR_PDO24_SHIFT                    24                                                  /*!< FGPIOA_PDOR: PDO24 Position             */
#define GPIO_PDOR_PDO25_MASK                     (0x01UL << GPIO_PDOR_PDO25_SHIFT)                   /*!< FGPIOA_PDOR: PDO25 Mask                 */
#define GPIO_PDOR_PDO25_SHIFT                    25                                                  /*!< FGPIOA_PDOR: PDO25 Position             */
#define GPIO_PDOR_PDO26_MASK                     (0x01UL << GPIO_PDOR_PDO26_SHIFT)                   /*!< FGPIOA_PDOR: PDO26 Mask                 */
#define GPIO_PDOR_PDO26_SHIFT                    26                                                  /*!< FGPIOA_PDOR: PDO26 Position             */
#define GPIO_PDOR_PDO27_MASK                     (0x01UL << GPIO_PDOR_PDO27_SHIFT)                   /*!< FGPIOA_PDOR: PDO27 Mask                 */
#define GPIO_PDOR_PDO27_SHIFT                    27                                                  /*!< FGPIOA_PDOR: PDO27 Position             */
#define GPIO_PDOR_PDO28_MASK                     (0x01UL << GPIO_PDOR_PDO28_SHIFT)                   /*!< FGPIOA_PDOR: PDO28 Mask                 */
#define GPIO_PDOR_PDO28_SHIFT                    28                                                  /*!< FGPIOA_PDOR: PDO28 Position             */
#define GPIO_PDOR_PDO29_MASK                     (0x01UL << GPIO_PDOR_PDO29_SHIFT)                   /*!< FGPIOA_PDOR: PDO29 Mask                 */
#define GPIO_PDOR_PDO29_SHIFT                    29                                                  /*!< FGPIOA_PDOR: PDO29 Position             */
#define GPIO_PDOR_PDO30_MASK                     (0x01UL << GPIO_PDOR_PDO30_SHIFT)                   /*!< FGPIOA_PDOR: PDO30 Mask                 */
#define GPIO_PDOR_PDO30_SHIFT                    30                                                  /*!< FGPIOA_PDOR: PDO30 Position             */
#define GPIO_PDOR_PDO31_MASK                     (0x01UL << GPIO_PDOR_PDO31_SHIFT)                   /*!< FGPIOA_PDOR: PDO31 Mask                 */
#define GPIO_PDOR_PDO31_SHIFT                    31                                                  /*!< FGPIOA_PDOR: PDO31 Position             */

/* ------- FGPIOA_PSOR                              ------ */
#define GPIO_PSOR_PTSO0_MASK                     (0x01UL << GPIO_PSOR_PTSO0_SHIFT)                   /*!< FGPIOA_PSOR: PTSO0 Mask                 */
#define GPIO_PSOR_PTSO0_SHIFT                    0                                                   /*!< FGPIOA_PSOR: PTSO0 Position             */
#define GPIO_PSOR_PTSO1_MASK                     (0x01UL << GPIO_PSOR_PTSO1_SHIFT)                   /*!< FGPIOA_PSOR: PTSO1 Mask                 */
#define GPIO_PSOR_PTSO1_SHIFT                    1                                                   /*!< FGPIOA_PSOR: PTSO1 Position             */
#define GPIO_PSOR_PTSO2_MASK                     (0x01UL << GPIO_PSOR_PTSO2_SHIFT)                   /*!< FGPIOA_PSOR: PTSO2 Mask                 */
#define GPIO_PSOR_PTSO2_SHIFT                    2                                                   /*!< FGPIOA_PSOR: PTSO2 Position             */
#define GPIO_PSOR_PTSO3_MASK                     (0x01UL << GPIO_PSOR_PTSO3_SHIFT)                   /*!< FGPIOA_PSOR: PTSO3 Mask                 */
#define GPIO_PSOR_PTSO3_SHIFT                    3                                                   /*!< FGPIOA_PSOR: PTSO3 Position             */
#define GPIO_PSOR_PTSO4_MASK                     (0x01UL << GPIO_PSOR_PTSO4_SHIFT)                   /*!< FGPIOA_PSOR: PTSO4 Mask                 */
#define GPIO_PSOR_PTSO4_SHIFT                    4                                                   /*!< FGPIOA_PSOR: PTSO4 Position             */
#define GPIO_PSOR_PTSO5_MASK                     (0x01UL << GPIO_PSOR_PTSO5_SHIFT)                   /*!< FGPIOA_PSOR: PTSO5 Mask                 */
#define GPIO_PSOR_PTSO5_SHIFT                    5                                                   /*!< FGPIOA_PSOR: PTSO5 Position             */
#define GPIO_PSOR_PTSO6_MASK                     (0x01UL << GPIO_PSOR_PTSO6_SHIFT)                   /*!< FGPIOA_PSOR: PTSO6 Mask                 */
#define GPIO_PSOR_PTSO6_SHIFT                    6                                                   /*!< FGPIOA_PSOR: PTSO6 Position             */
#define GPIO_PSOR_PTSO7_MASK                     (0x01UL << GPIO_PSOR_PTSO7_SHIFT)                   /*!< FGPIOA_PSOR: PTSO7 Mask                 */
#define GPIO_PSOR_PTSO7_SHIFT                    7                                                   /*!< FGPIOA_PSOR: PTSO7 Position             */
#define GPIO_PSOR_PTSO8_MASK                     (0x01UL << GPIO_PSOR_PTSO8_SHIFT)                   /*!< FGPIOA_PSOR: PTSO8 Mask                 */
#define GPIO_PSOR_PTSO8_SHIFT                    8                                                   /*!< FGPIOA_PSOR: PTSO8 Position             */
#define GPIO_PSOR_PTSO9_MASK                     (0x01UL << GPIO_PSOR_PTSO9_SHIFT)                   /*!< FGPIOA_PSOR: PTSO9 Mask                 */
#define GPIO_PSOR_PTSO9_SHIFT                    9                                                   /*!< FGPIOA_PSOR: PTSO9 Position             */
#define GPIO_PSOR_PTSO10_MASK                    (0x01UL << GPIO_PSOR_PTSO10_SHIFT)                  /*!< FGPIOA_PSOR: PTSO10 Mask                */
#define GPIO_PSOR_PTSO10_SHIFT                   10                                                  /*!< FGPIOA_PSOR: PTSO10 Position            */
#define GPIO_PSOR_PTSO11_MASK                    (0x01UL << GPIO_PSOR_PTSO11_SHIFT)                  /*!< FGPIOA_PSOR: PTSO11 Mask                */
#define GPIO_PSOR_PTSO11_SHIFT                   11                                                  /*!< FGPIOA_PSOR: PTSO11 Position            */
#define GPIO_PSOR_PTSO12_MASK                    (0x01UL << GPIO_PSOR_PTSO12_SHIFT)                  /*!< FGPIOA_PSOR: PTSO12 Mask                */
#define GPIO_PSOR_PTSO12_SHIFT                   12                                                  /*!< FGPIOA_PSOR: PTSO12 Position            */
#define GPIO_PSOR_PTSO13_MASK                    (0x01UL << GPIO_PSOR_PTSO13_SHIFT)                  /*!< FGPIOA_PSOR: PTSO13 Mask                */
#define GPIO_PSOR_PTSO13_SHIFT                   13                                                  /*!< FGPIOA_PSOR: PTSO13 Position            */
#define GPIO_PSOR_PTSO14_MASK                    (0x01UL << GPIO_PSOR_PTSO14_SHIFT)                  /*!< FGPIOA_PSOR: PTSO14 Mask                */
#define GPIO_PSOR_PTSO14_SHIFT                   14                                                  /*!< FGPIOA_PSOR: PTSO14 Position            */
#define GPIO_PSOR_PTSO15_MASK                    (0x01UL << GPIO_PSOR_PTSO15_SHIFT)                  /*!< FGPIOA_PSOR: PTSO15 Mask                */
#define GPIO_PSOR_PTSO15_SHIFT                   15                                                  /*!< FGPIOA_PSOR: PTSO15 Position            */
#define GPIO_PSOR_PTSO16_MASK                    (0x01UL << GPIO_PSOR_PTSO16_SHIFT)                  /*!< FGPIOA_PSOR: PTSO16 Mask                */
#define GPIO_PSOR_PTSO16_SHIFT                   16                                                  /*!< FGPIOA_PSOR: PTSO16 Position            */
#define GPIO_PSOR_PTSO17_MASK                    (0x01UL << GPIO_PSOR_PTSO17_SHIFT)                  /*!< FGPIOA_PSOR: PTSO17 Mask                */
#define GPIO_PSOR_PTSO17_SHIFT                   17                                                  /*!< FGPIOA_PSOR: PTSO17 Position            */
#define GPIO_PSOR_PTSO18_MASK                    (0x01UL << GPIO_PSOR_PTSO18_SHIFT)                  /*!< FGPIOA_PSOR: PTSO18 Mask                */
#define GPIO_PSOR_PTSO18_SHIFT                   18                                                  /*!< FGPIOA_PSOR: PTSO18 Position            */
#define GPIO_PSOR_PTSO19_MASK                    (0x01UL << GPIO_PSOR_PTSO19_SHIFT)                  /*!< FGPIOA_PSOR: PTSO19 Mask                */
#define GPIO_PSOR_PTSO19_SHIFT                   19                                                  /*!< FGPIOA_PSOR: PTSO19 Position            */
#define GPIO_PSOR_PTSO20_MASK                    (0x01UL << GPIO_PSOR_PTSO20_SHIFT)                  /*!< FGPIOA_PSOR: PTSO20 Mask                */
#define GPIO_PSOR_PTSO20_SHIFT                   20                                                  /*!< FGPIOA_PSOR: PTSO20 Position            */
#define GPIO_PSOR_PTSO21_MASK                    (0x01UL << GPIO_PSOR_PTSO21_SHIFT)                  /*!< FGPIOA_PSOR: PTSO21 Mask                */
#define GPIO_PSOR_PTSO21_SHIFT                   21                                                  /*!< FGPIOA_PSOR: PTSO21 Position            */
#define GPIO_PSOR_PTSO22_MASK                    (0x01UL << GPIO_PSOR_PTSO22_SHIFT)                  /*!< FGPIOA_PSOR: PTSO22 Mask                */
#define GPIO_PSOR_PTSO22_SHIFT                   22                                                  /*!< FGPIOA_PSOR: PTSO22 Position            */
#define GPIO_PSOR_PTSO23_MASK                    (0x01UL << GPIO_PSOR_PTSO23_SHIFT)                  /*!< FGPIOA_PSOR: PTSO23 Mask                */
#define GPIO_PSOR_PTSO23_SHIFT                   23                                                  /*!< FGPIOA_PSOR: PTSO23 Position            */
#define GPIO_PSOR_PTSO24_MASK                    (0x01UL << GPIO_PSOR_PTSO24_SHIFT)                  /*!< FGPIOA_PSOR: PTSO24 Mask                */
#define GPIO_PSOR_PTSO24_SHIFT                   24                                                  /*!< FGPIOA_PSOR: PTSO24 Position            */
#define GPIO_PSOR_PTSO25_MASK                    (0x01UL << GPIO_PSOR_PTSO25_SHIFT)                  /*!< FGPIOA_PSOR: PTSO25 Mask                */
#define GPIO_PSOR_PTSO25_SHIFT                   25                                                  /*!< FGPIOA_PSOR: PTSO25 Position            */
#define GPIO_PSOR_PTSO26_MASK                    (0x01UL << GPIO_PSOR_PTSO26_SHIFT)                  /*!< FGPIOA_PSOR: PTSO26 Mask                */
#define GPIO_PSOR_PTSO26_SHIFT                   26                                                  /*!< FGPIOA_PSOR: PTSO26 Position            */
#define GPIO_PSOR_PTSO27_MASK                    (0x01UL << GPIO_PSOR_PTSO27_SHIFT)                  /*!< FGPIOA_PSOR: PTSO27 Mask                */
#define GPIO_PSOR_PTSO27_SHIFT                   27                                                  /*!< FGPIOA_PSOR: PTSO27 Position            */
#define GPIO_PSOR_PTSO28_MASK                    (0x01UL << GPIO_PSOR_PTSO28_SHIFT)                  /*!< FGPIOA_PSOR: PTSO28 Mask                */
#define GPIO_PSOR_PTSO28_SHIFT                   28                                                  /*!< FGPIOA_PSOR: PTSO28 Position            */
#define GPIO_PSOR_PTSO29_MASK                    (0x01UL << GPIO_PSOR_PTSO29_SHIFT)                  /*!< FGPIOA_PSOR: PTSO29 Mask                */
#define GPIO_PSOR_PTSO29_SHIFT                   29                                                  /*!< FGPIOA_PSOR: PTSO29 Position            */
#define GPIO_PSOR_PTSO30_MASK                    (0x01UL << GPIO_PSOR_PTSO30_SHIFT)                  /*!< FGPIOA_PSOR: PTSO30 Mask                */
#define GPIO_PSOR_PTSO30_SHIFT                   30                                                  /*!< FGPIOA_PSOR: PTSO30 Position            */
#define GPIO_PSOR_PTSO31_MASK                    (0x01UL << GPIO_PSOR_PTSO31_SHIFT)                  /*!< FGPIOA_PSOR: PTSO31 Mask                */
#define GPIO_PSOR_PTSO31_SHIFT                   31                                                  /*!< FGPIOA_PSOR: PTSO31 Position            */

/* ------- FGPIOA_PCOR                              ------ */
#define GPIO_PCOR_PTCO0_MASK                     (0x01UL << GPIO_PCOR_PTCO0_SHIFT)                   /*!< FGPIOA_PCOR: PTCO0 Mask                 */
#define GPIO_PCOR_PTCO0_SHIFT                    0                                                   /*!< FGPIOA_PCOR: PTCO0 Position             */
#define GPIO_PCOR_PTCO1_MASK                     (0x01UL << GPIO_PCOR_PTCO1_SHIFT)                   /*!< FGPIOA_PCOR: PTCO1 Mask                 */
#define GPIO_PCOR_PTCO1_SHIFT                    1                                                   /*!< FGPIOA_PCOR: PTCO1 Position             */
#define GPIO_PCOR_PTCO2_MASK                     (0x01UL << GPIO_PCOR_PTCO2_SHIFT)                   /*!< FGPIOA_PCOR: PTCO2 Mask                 */
#define GPIO_PCOR_PTCO2_SHIFT                    2                                                   /*!< FGPIOA_PCOR: PTCO2 Position             */
#define GPIO_PCOR_PTCO3_MASK                     (0x01UL << GPIO_PCOR_PTCO3_SHIFT)                   /*!< FGPIOA_PCOR: PTCO3 Mask                 */
#define GPIO_PCOR_PTCO3_SHIFT                    3                                                   /*!< FGPIOA_PCOR: PTCO3 Position             */
#define GPIO_PCOR_PTCO4_MASK                     (0x01UL << GPIO_PCOR_PTCO4_SHIFT)                   /*!< FGPIOA_PCOR: PTCO4 Mask                 */
#define GPIO_PCOR_PTCO4_SHIFT                    4                                                   /*!< FGPIOA_PCOR: PTCO4 Position             */
#define GPIO_PCOR_PTCO5_MASK                     (0x01UL << GPIO_PCOR_PTCO5_SHIFT)                   /*!< FGPIOA_PCOR: PTCO5 Mask                 */
#define GPIO_PCOR_PTCO5_SHIFT                    5                                                   /*!< FGPIOA_PCOR: PTCO5 Position             */
#define GPIO_PCOR_PTCO6_MASK                     (0x01UL << GPIO_PCOR_PTCO6_SHIFT)                   /*!< FGPIOA_PCOR: PTCO6 Mask                 */
#define GPIO_PCOR_PTCO6_SHIFT                    6                                                   /*!< FGPIOA_PCOR: PTCO6 Position             */
#define GPIO_PCOR_PTCO7_MASK                     (0x01UL << GPIO_PCOR_PTCO7_SHIFT)                   /*!< FGPIOA_PCOR: PTCO7 Mask                 */
#define GPIO_PCOR_PTCO7_SHIFT                    7                                                   /*!< FGPIOA_PCOR: PTCO7 Position             */
#define GPIO_PCOR_PTCO8_MASK                     (0x01UL << GPIO_PCOR_PTCO8_SHIFT)                   /*!< FGPIOA_PCOR: PTCO8 Mask                 */
#define GPIO_PCOR_PTCO8_SHIFT                    8                                                   /*!< FGPIOA_PCOR: PTCO8 Position             */
#define GPIO_PCOR_PTCO9_MASK                     (0x01UL << GPIO_PCOR_PTCO9_SHIFT)                   /*!< FGPIOA_PCOR: PTCO9 Mask                 */
#define GPIO_PCOR_PTCO9_SHIFT                    9                                                   /*!< FGPIOA_PCOR: PTCO9 Position             */
#define GPIO_PCOR_PTCO10_MASK                    (0x01UL << GPIO_PCOR_PTCO10_SHIFT)                  /*!< FGPIOA_PCOR: PTCO10 Mask                */
#define GPIO_PCOR_PTCO10_SHIFT                   10                                                  /*!< FGPIOA_PCOR: PTCO10 Position            */
#define GPIO_PCOR_PTCO11_MASK                    (0x01UL << GPIO_PCOR_PTCO11_SHIFT)                  /*!< FGPIOA_PCOR: PTCO11 Mask                */
#define GPIO_PCOR_PTCO11_SHIFT                   11                                                  /*!< FGPIOA_PCOR: PTCO11 Position            */
#define GPIO_PCOR_PTCO12_MASK                    (0x01UL << GPIO_PCOR_PTCO12_SHIFT)                  /*!< FGPIOA_PCOR: PTCO12 Mask                */
#define GPIO_PCOR_PTCO12_SHIFT                   12                                                  /*!< FGPIOA_PCOR: PTCO12 Position            */
#define GPIO_PCOR_PTCO13_MASK                    (0x01UL << GPIO_PCOR_PTCO13_SHIFT)                  /*!< FGPIOA_PCOR: PTCO13 Mask                */
#define GPIO_PCOR_PTCO13_SHIFT                   13                                                  /*!< FGPIOA_PCOR: PTCO13 Position            */
#define GPIO_PCOR_PTCO14_MASK                    (0x01UL << GPIO_PCOR_PTCO14_SHIFT)                  /*!< FGPIOA_PCOR: PTCO14 Mask                */
#define GPIO_PCOR_PTCO14_SHIFT                   14                                                  /*!< FGPIOA_PCOR: PTCO14 Position            */
#define GPIO_PCOR_PTCO15_MASK                    (0x01UL << GPIO_PCOR_PTCO15_SHIFT)                  /*!< FGPIOA_PCOR: PTCO15 Mask                */
#define GPIO_PCOR_PTCO15_SHIFT                   15                                                  /*!< FGPIOA_PCOR: PTCO15 Position            */
#define GPIO_PCOR_PTCO16_MASK                    (0x01UL << GPIO_PCOR_PTCO16_SHIFT)                  /*!< FGPIOA_PCOR: PTCO16 Mask                */
#define GPIO_PCOR_PTCO16_SHIFT                   16                                                  /*!< FGPIOA_PCOR: PTCO16 Position            */
#define GPIO_PCOR_PTCO17_MASK                    (0x01UL << GPIO_PCOR_PTCO17_SHIFT)                  /*!< FGPIOA_PCOR: PTCO17 Mask                */
#define GPIO_PCOR_PTCO17_SHIFT                   17                                                  /*!< FGPIOA_PCOR: PTCO17 Position            */
#define GPIO_PCOR_PTCO18_MASK                    (0x01UL << GPIO_PCOR_PTCO18_SHIFT)                  /*!< FGPIOA_PCOR: PTCO18 Mask                */
#define GPIO_PCOR_PTCO18_SHIFT                   18                                                  /*!< FGPIOA_PCOR: PTCO18 Position            */
#define GPIO_PCOR_PTCO19_MASK                    (0x01UL << GPIO_PCOR_PTCO19_SHIFT)                  /*!< FGPIOA_PCOR: PTCO19 Mask                */
#define GPIO_PCOR_PTCO19_SHIFT                   19                                                  /*!< FGPIOA_PCOR: PTCO19 Position            */
#define GPIO_PCOR_PTCO20_MASK                    (0x01UL << GPIO_PCOR_PTCO20_SHIFT)                  /*!< FGPIOA_PCOR: PTCO20 Mask                */
#define GPIO_PCOR_PTCO20_SHIFT                   20                                                  /*!< FGPIOA_PCOR: PTCO20 Position            */
#define GPIO_PCOR_PTCO21_MASK                    (0x01UL << GPIO_PCOR_PTCO21_SHIFT)                  /*!< FGPIOA_PCOR: PTCO21 Mask                */
#define GPIO_PCOR_PTCO21_SHIFT                   21                                                  /*!< FGPIOA_PCOR: PTCO21 Position            */
#define GPIO_PCOR_PTCO22_MASK                    (0x01UL << GPIO_PCOR_PTCO22_SHIFT)                  /*!< FGPIOA_PCOR: PTCO22 Mask                */
#define GPIO_PCOR_PTCO22_SHIFT                   22                                                  /*!< FGPIOA_PCOR: PTCO22 Position            */
#define GPIO_PCOR_PTCO23_MASK                    (0x01UL << GPIO_PCOR_PTCO23_SHIFT)                  /*!< FGPIOA_PCOR: PTCO23 Mask                */
#define GPIO_PCOR_PTCO23_SHIFT                   23                                                  /*!< FGPIOA_PCOR: PTCO23 Position            */
#define GPIO_PCOR_PTCO24_MASK                    (0x01UL << GPIO_PCOR_PTCO24_SHIFT)                  /*!< FGPIOA_PCOR: PTCO24 Mask                */
#define GPIO_PCOR_PTCO24_SHIFT                   24                                                  /*!< FGPIOA_PCOR: PTCO24 Position            */
#define GPIO_PCOR_PTCO25_MASK                    (0x01UL << GPIO_PCOR_PTCO25_SHIFT)                  /*!< FGPIOA_PCOR: PTCO25 Mask                */
#define GPIO_PCOR_PTCO25_SHIFT                   25                                                  /*!< FGPIOA_PCOR: PTCO25 Position            */
#define GPIO_PCOR_PTCO26_MASK                    (0x01UL << GPIO_PCOR_PTCO26_SHIFT)                  /*!< FGPIOA_PCOR: PTCO26 Mask                */
#define GPIO_PCOR_PTCO26_SHIFT                   26                                                  /*!< FGPIOA_PCOR: PTCO26 Position            */
#define GPIO_PCOR_PTCO27_MASK                    (0x01UL << GPIO_PCOR_PTCO27_SHIFT)                  /*!< FGPIOA_PCOR: PTCO27 Mask                */
#define GPIO_PCOR_PTCO27_SHIFT                   27                                                  /*!< FGPIOA_PCOR: PTCO27 Position            */
#define GPIO_PCOR_PTCO28_MASK                    (0x01UL << GPIO_PCOR_PTCO28_SHIFT)                  /*!< FGPIOA_PCOR: PTCO28 Mask                */
#define GPIO_PCOR_PTCO28_SHIFT                   28                                                  /*!< FGPIOA_PCOR: PTCO28 Position            */
#define GPIO_PCOR_PTCO29_MASK                    (0x01UL << GPIO_PCOR_PTCO29_SHIFT)                  /*!< FGPIOA_PCOR: PTCO29 Mask                */
#define GPIO_PCOR_PTCO29_SHIFT                   29                                                  /*!< FGPIOA_PCOR: PTCO29 Position            */
#define GPIO_PCOR_PTCO30_MASK                    (0x01UL << GPIO_PCOR_PTCO30_SHIFT)                  /*!< FGPIOA_PCOR: PTCO30 Mask                */
#define GPIO_PCOR_PTCO30_SHIFT                   30                                                  /*!< FGPIOA_PCOR: PTCO30 Position            */
#define GPIO_PCOR_PTCO31_MASK                    (0x01UL << GPIO_PCOR_PTCO31_SHIFT)                  /*!< FGPIOA_PCOR: PTCO31 Mask                */
#define GPIO_PCOR_PTCO31_SHIFT                   31                                                  /*!< FGPIOA_PCOR: PTCO31 Position            */

/* ------- FGPIOA_PTOR                              ------ */
#define GPIO_PTOR_PTTO0_MASK                     (0x01UL << GPIO_PTOR_PTTO0_SHIFT)                   /*!< FGPIOA_PTOR: PTTO0 Mask                 */
#define GPIO_PTOR_PTTO0_SHIFT                    0                                                   /*!< FGPIOA_PTOR: PTTO0 Position             */
#define GPIO_PTOR_PTTO1_MASK                     (0x01UL << GPIO_PTOR_PTTO1_SHIFT)                   /*!< FGPIOA_PTOR: PTTO1 Mask                 */
#define GPIO_PTOR_PTTO1_SHIFT                    1                                                   /*!< FGPIOA_PTOR: PTTO1 Position             */
#define GPIO_PTOR_PTTO2_MASK                     (0x01UL << GPIO_PTOR_PTTO2_SHIFT)                   /*!< FGPIOA_PTOR: PTTO2 Mask                 */
#define GPIO_PTOR_PTTO2_SHIFT                    2                                                   /*!< FGPIOA_PTOR: PTTO2 Position             */
#define GPIO_PTOR_PTTO3_MASK                     (0x01UL << GPIO_PTOR_PTTO3_SHIFT)                   /*!< FGPIOA_PTOR: PTTO3 Mask                 */
#define GPIO_PTOR_PTTO3_SHIFT                    3                                                   /*!< FGPIOA_PTOR: PTTO3 Position             */
#define GPIO_PTOR_PTTO4_MASK                     (0x01UL << GPIO_PTOR_PTTO4_SHIFT)                   /*!< FGPIOA_PTOR: PTTO4 Mask                 */
#define GPIO_PTOR_PTTO4_SHIFT                    4                                                   /*!< FGPIOA_PTOR: PTTO4 Position             */
#define GPIO_PTOR_PTTO5_MASK                     (0x01UL << GPIO_PTOR_PTTO5_SHIFT)                   /*!< FGPIOA_PTOR: PTTO5 Mask                 */
#define GPIO_PTOR_PTTO5_SHIFT                    5                                                   /*!< FGPIOA_PTOR: PTTO5 Position             */
#define GPIO_PTOR_PTTO6_MASK                     (0x01UL << GPIO_PTOR_PTTO6_SHIFT)                   /*!< FGPIOA_PTOR: PTTO6 Mask                 */
#define GPIO_PTOR_PTTO6_SHIFT                    6                                                   /*!< FGPIOA_PTOR: PTTO6 Position             */
#define GPIO_PTOR_PTTO7_MASK                     (0x01UL << GPIO_PTOR_PTTO7_SHIFT)                   /*!< FGPIOA_PTOR: PTTO7 Mask                 */
#define GPIO_PTOR_PTTO7_SHIFT                    7                                                   /*!< FGPIOA_PTOR: PTTO7 Position             */
#define GPIO_PTOR_PTTO8_MASK                     (0x01UL << GPIO_PTOR_PTTO8_SHIFT)                   /*!< FGPIOA_PTOR: PTTO8 Mask                 */
#define GPIO_PTOR_PTTO8_SHIFT                    8                                                   /*!< FGPIOA_PTOR: PTTO8 Position             */
#define GPIO_PTOR_PTTO9_MASK                     (0x01UL << GPIO_PTOR_PTTO9_SHIFT)                   /*!< FGPIOA_PTOR: PTTO9 Mask                 */
#define GPIO_PTOR_PTTO9_SHIFT                    9                                                   /*!< FGPIOA_PTOR: PTTO9 Position             */
#define GPIO_PTOR_PTTO10_MASK                    (0x01UL << GPIO_PTOR_PTTO10_SHIFT)                  /*!< FGPIOA_PTOR: PTTO10 Mask                */
#define GPIO_PTOR_PTTO10_SHIFT                   10                                                  /*!< FGPIOA_PTOR: PTTO10 Position            */
#define GPIO_PTOR_PTTO11_MASK                    (0x01UL << GPIO_PTOR_PTTO11_SHIFT)                  /*!< FGPIOA_PTOR: PTTO11 Mask                */
#define GPIO_PTOR_PTTO11_SHIFT                   11                                                  /*!< FGPIOA_PTOR: PTTO11 Position            */
#define GPIO_PTOR_PTTO12_MASK                    (0x01UL << GPIO_PTOR_PTTO12_SHIFT)                  /*!< FGPIOA_PTOR: PTTO12 Mask                */
#define GPIO_PTOR_PTTO12_SHIFT                   12                                                  /*!< FGPIOA_PTOR: PTTO12 Position            */
#define GPIO_PTOR_PTTO13_MASK                    (0x01UL << GPIO_PTOR_PTTO13_SHIFT)                  /*!< FGPIOA_PTOR: PTTO13 Mask                */
#define GPIO_PTOR_PTTO13_SHIFT                   13                                                  /*!< FGPIOA_PTOR: PTTO13 Position            */
#define GPIO_PTOR_PTTO14_MASK                    (0x01UL << GPIO_PTOR_PTTO14_SHIFT)                  /*!< FGPIOA_PTOR: PTTO14 Mask                */
#define GPIO_PTOR_PTTO14_SHIFT                   14                                                  /*!< FGPIOA_PTOR: PTTO14 Position            */
#define GPIO_PTOR_PTTO15_MASK                    (0x01UL << GPIO_PTOR_PTTO15_SHIFT)                  /*!< FGPIOA_PTOR: PTTO15 Mask                */
#define GPIO_PTOR_PTTO15_SHIFT                   15                                                  /*!< FGPIOA_PTOR: PTTO15 Position            */
#define GPIO_PTOR_PTTO16_MASK                    (0x01UL << GPIO_PTOR_PTTO16_SHIFT)                  /*!< FGPIOA_PTOR: PTTO16 Mask                */
#define GPIO_PTOR_PTTO16_SHIFT                   16                                                  /*!< FGPIOA_PTOR: PTTO16 Position            */
#define GPIO_PTOR_PTTO17_MASK                    (0x01UL << GPIO_PTOR_PTTO17_SHIFT)                  /*!< FGPIOA_PTOR: PTTO17 Mask                */
#define GPIO_PTOR_PTTO17_SHIFT                   17                                                  /*!< FGPIOA_PTOR: PTTO17 Position            */
#define GPIO_PTOR_PTTO18_MASK                    (0x01UL << GPIO_PTOR_PTTO18_SHIFT)                  /*!< FGPIOA_PTOR: PTTO18 Mask                */
#define GPIO_PTOR_PTTO18_SHIFT                   18                                                  /*!< FGPIOA_PTOR: PTTO18 Position            */
#define GPIO_PTOR_PTTO19_MASK                    (0x01UL << GPIO_PTOR_PTTO19_SHIFT)                  /*!< FGPIOA_PTOR: PTTO19 Mask                */
#define GPIO_PTOR_PTTO19_SHIFT                   19                                                  /*!< FGPIOA_PTOR: PTTO19 Position            */
#define GPIO_PTOR_PTTO20_MASK                    (0x01UL << GPIO_PTOR_PTTO20_SHIFT)                  /*!< FGPIOA_PTOR: PTTO20 Mask                */
#define GPIO_PTOR_PTTO20_SHIFT                   20                                                  /*!< FGPIOA_PTOR: PTTO20 Position            */
#define GPIO_PTOR_PTTO21_MASK                    (0x01UL << GPIO_PTOR_PTTO21_SHIFT)                  /*!< FGPIOA_PTOR: PTTO21 Mask                */
#define GPIO_PTOR_PTTO21_SHIFT                   21                                                  /*!< FGPIOA_PTOR: PTTO21 Position            */
#define GPIO_PTOR_PTTO22_MASK                    (0x01UL << GPIO_PTOR_PTTO22_SHIFT)                  /*!< FGPIOA_PTOR: PTTO22 Mask                */
#define GPIO_PTOR_PTTO22_SHIFT                   22                                                  /*!< FGPIOA_PTOR: PTTO22 Position            */
#define GPIO_PTOR_PTTO23_MASK                    (0x01UL << GPIO_PTOR_PTTO23_SHIFT)                  /*!< FGPIOA_PTOR: PTTO23 Mask                */
#define GPIO_PTOR_PTTO23_SHIFT                   23                                                  /*!< FGPIOA_PTOR: PTTO23 Position            */
#define GPIO_PTOR_PTTO24_MASK                    (0x01UL << GPIO_PTOR_PTTO24_SHIFT)                  /*!< FGPIOA_PTOR: PTTO24 Mask                */
#define GPIO_PTOR_PTTO24_SHIFT                   24                                                  /*!< FGPIOA_PTOR: PTTO24 Position            */
#define GPIO_PTOR_PTTO25_MASK                    (0x01UL << GPIO_PTOR_PTTO25_SHIFT)                  /*!< FGPIOA_PTOR: PTTO25 Mask                */
#define GPIO_PTOR_PTTO25_SHIFT                   25                                                  /*!< FGPIOA_PTOR: PTTO25 Position            */
#define GPIO_PTOR_PTTO26_MASK                    (0x01UL << GPIO_PTOR_PTTO26_SHIFT)                  /*!< FGPIOA_PTOR: PTTO26 Mask                */
#define GPIO_PTOR_PTTO26_SHIFT                   26                                                  /*!< FGPIOA_PTOR: PTTO26 Position            */
#define GPIO_PTOR_PTTO27_MASK                    (0x01UL << GPIO_PTOR_PTTO27_SHIFT)                  /*!< FGPIOA_PTOR: PTTO27 Mask                */
#define GPIO_PTOR_PTTO27_SHIFT                   27                                                  /*!< FGPIOA_PTOR: PTTO27 Position            */
#define GPIO_PTOR_PTTO28_MASK                    (0x01UL << GPIO_PTOR_PTTO28_SHIFT)                  /*!< FGPIOA_PTOR: PTTO28 Mask                */
#define GPIO_PTOR_PTTO28_SHIFT                   28                                                  /*!< FGPIOA_PTOR: PTTO28 Position            */
#define GPIO_PTOR_PTTO29_MASK                    (0x01UL << GPIO_PTOR_PTTO29_SHIFT)                  /*!< FGPIOA_PTOR: PTTO29 Mask                */
#define GPIO_PTOR_PTTO29_SHIFT                   29                                                  /*!< FGPIOA_PTOR: PTTO29 Position            */
#define GPIO_PTOR_PTTO30_MASK                    (0x01UL << GPIO_PTOR_PTTO30_SHIFT)                  /*!< FGPIOA_PTOR: PTTO30 Mask                */
#define GPIO_PTOR_PTTO30_SHIFT                   30                                                  /*!< FGPIOA_PTOR: PTTO30 Position            */
#define GPIO_PTOR_PTTO31_MASK                    (0x01UL << GPIO_PTOR_PTTO31_SHIFT)                  /*!< FGPIOA_PTOR: PTTO31 Mask                */
#define GPIO_PTOR_PTTO31_SHIFT                   31                                                  /*!< FGPIOA_PTOR: PTTO31 Position            */

/* ------- FGPIOA_PDIR                              ------ */
#define GPIO_PDIR_PDI0_MASK                      (0x01UL << GPIO_PDIR_PDI0_SHIFT)                    /*!< FGPIOA_PDIR: PDI0 Mask                  */
#define GPIO_PDIR_PDI0_SHIFT                     0                                                   /*!< FGPIOA_PDIR: PDI0 Position              */
#define GPIO_PDIR_PDI1_MASK                      (0x01UL << GPIO_PDIR_PDI1_SHIFT)                    /*!< FGPIOA_PDIR: PDI1 Mask                  */
#define GPIO_PDIR_PDI1_SHIFT                     1                                                   /*!< FGPIOA_PDIR: PDI1 Position              */
#define GPIO_PDIR_PDI2_MASK                      (0x01UL << GPIO_PDIR_PDI2_SHIFT)                    /*!< FGPIOA_PDIR: PDI2 Mask                  */
#define GPIO_PDIR_PDI2_SHIFT                     2                                                   /*!< FGPIOA_PDIR: PDI2 Position              */
#define GPIO_PDIR_PDI3_MASK                      (0x01UL << GPIO_PDIR_PDI3_SHIFT)                    /*!< FGPIOA_PDIR: PDI3 Mask                  */
#define GPIO_PDIR_PDI3_SHIFT                     3                                                   /*!< FGPIOA_PDIR: PDI3 Position              */
#define GPIO_PDIR_PDI4_MASK                      (0x01UL << GPIO_PDIR_PDI4_SHIFT)                    /*!< FGPIOA_PDIR: PDI4 Mask                  */
#define GPIO_PDIR_PDI4_SHIFT                     4                                                   /*!< FGPIOA_PDIR: PDI4 Position              */
#define GPIO_PDIR_PDI5_MASK                      (0x01UL << GPIO_PDIR_PDI5_SHIFT)                    /*!< FGPIOA_PDIR: PDI5 Mask                  */
#define GPIO_PDIR_PDI5_SHIFT                     5                                                   /*!< FGPIOA_PDIR: PDI5 Position              */
#define GPIO_PDIR_PDI6_MASK                      (0x01UL << GPIO_PDIR_PDI6_SHIFT)                    /*!< FGPIOA_PDIR: PDI6 Mask                  */
#define GPIO_PDIR_PDI6_SHIFT                     6                                                   /*!< FGPIOA_PDIR: PDI6 Position              */
#define GPIO_PDIR_PDI7_MASK                      (0x01UL << GPIO_PDIR_PDI7_SHIFT)                    /*!< FGPIOA_PDIR: PDI7 Mask                  */
#define GPIO_PDIR_PDI7_SHIFT                     7                                                   /*!< FGPIOA_PDIR: PDI7 Position              */
#define GPIO_PDIR_PDI8_MASK                      (0x01UL << GPIO_PDIR_PDI8_SHIFT)                    /*!< FGPIOA_PDIR: PDI8 Mask                  */
#define GPIO_PDIR_PDI8_SHIFT                     8                                                   /*!< FGPIOA_PDIR: PDI8 Position              */
#define GPIO_PDIR_PDI9_MASK                      (0x01UL << GPIO_PDIR_PDI9_SHIFT)                    /*!< FGPIOA_PDIR: PDI9 Mask                  */
#define GPIO_PDIR_PDI9_SHIFT                     9                                                   /*!< FGPIOA_PDIR: PDI9 Position              */
#define GPIO_PDIR_PDI10_MASK                     (0x01UL << GPIO_PDIR_PDI10_SHIFT)                   /*!< FGPIOA_PDIR: PDI10 Mask                 */
#define GPIO_PDIR_PDI10_SHIFT                    10                                                  /*!< FGPIOA_PDIR: PDI10 Position             */
#define GPIO_PDIR_PDI11_MASK                     (0x01UL << GPIO_PDIR_PDI11_SHIFT)                   /*!< FGPIOA_PDIR: PDI11 Mask                 */
#define GPIO_PDIR_PDI11_SHIFT                    11                                                  /*!< FGPIOA_PDIR: PDI11 Position             */
#define GPIO_PDIR_PDI12_MASK                     (0x01UL << GPIO_PDIR_PDI12_SHIFT)                   /*!< FGPIOA_PDIR: PDI12 Mask                 */
#define GPIO_PDIR_PDI12_SHIFT                    12                                                  /*!< FGPIOA_PDIR: PDI12 Position             */
#define GPIO_PDIR_PDI13_MASK                     (0x01UL << GPIO_PDIR_PDI13_SHIFT)                   /*!< FGPIOA_PDIR: PDI13 Mask                 */
#define GPIO_PDIR_PDI13_SHIFT                    13                                                  /*!< FGPIOA_PDIR: PDI13 Position             */
#define GPIO_PDIR_PDI14_MASK                     (0x01UL << GPIO_PDIR_PDI14_SHIFT)                   /*!< FGPIOA_PDIR: PDI14 Mask                 */
#define GPIO_PDIR_PDI14_SHIFT                    14                                                  /*!< FGPIOA_PDIR: PDI14 Position             */
#define GPIO_PDIR_PDI15_MASK                     (0x01UL << GPIO_PDIR_PDI15_SHIFT)                   /*!< FGPIOA_PDIR: PDI15 Mask                 */
#define GPIO_PDIR_PDI15_SHIFT                    15                                                  /*!< FGPIOA_PDIR: PDI15 Position             */
#define GPIO_PDIR_PDI16_MASK                     (0x01UL << GPIO_PDIR_PDI16_SHIFT)                   /*!< FGPIOA_PDIR: PDI16 Mask                 */
#define GPIO_PDIR_PDI16_SHIFT                    16                                                  /*!< FGPIOA_PDIR: PDI16 Position             */
#define GPIO_PDIR_PDI17_MASK                     (0x01UL << GPIO_PDIR_PDI17_SHIFT)                   /*!< FGPIOA_PDIR: PDI17 Mask                 */
#define GPIO_PDIR_PDI17_SHIFT                    17                                                  /*!< FGPIOA_PDIR: PDI17 Position             */
#define GPIO_PDIR_PDI18_MASK                     (0x01UL << GPIO_PDIR_PDI18_SHIFT)                   /*!< FGPIOA_PDIR: PDI18 Mask                 */
#define GPIO_PDIR_PDI18_SHIFT                    18                                                  /*!< FGPIOA_PDIR: PDI18 Position             */
#define GPIO_PDIR_PDI19_MASK                     (0x01UL << GPIO_PDIR_PDI19_SHIFT)                   /*!< FGPIOA_PDIR: PDI19 Mask                 */
#define GPIO_PDIR_PDI19_SHIFT                    19                                                  /*!< FGPIOA_PDIR: PDI19 Position             */
#define GPIO_PDIR_PDI20_MASK                     (0x01UL << GPIO_PDIR_PDI20_SHIFT)                   /*!< FGPIOA_PDIR: PDI20 Mask                 */
#define GPIO_PDIR_PDI20_SHIFT                    20                                                  /*!< FGPIOA_PDIR: PDI20 Position             */
#define GPIO_PDIR_PDI21_MASK                     (0x01UL << GPIO_PDIR_PDI21_SHIFT)                   /*!< FGPIOA_PDIR: PDI21 Mask                 */
#define GPIO_PDIR_PDI21_SHIFT                    21                                                  /*!< FGPIOA_PDIR: PDI21 Position             */
#define GPIO_PDIR_PDI22_MASK                     (0x01UL << GPIO_PDIR_PDI22_SHIFT)                   /*!< FGPIOA_PDIR: PDI22 Mask                 */
#define GPIO_PDIR_PDI22_SHIFT                    22                                                  /*!< FGPIOA_PDIR: PDI22 Position             */
#define GPIO_PDIR_PDI23_MASK                     (0x01UL << GPIO_PDIR_PDI23_SHIFT)                   /*!< FGPIOA_PDIR: PDI23 Mask                 */
#define GPIO_PDIR_PDI23_SHIFT                    23                                                  /*!< FGPIOA_PDIR: PDI23 Position             */
#define GPIO_PDIR_PDI24_MASK                     (0x01UL << GPIO_PDIR_PDI24_SHIFT)                   /*!< FGPIOA_PDIR: PDI24 Mask                 */
#define GPIO_PDIR_PDI24_SHIFT                    24                                                  /*!< FGPIOA_PDIR: PDI24 Position             */
#define GPIO_PDIR_PDI25_MASK                     (0x01UL << GPIO_PDIR_PDI25_SHIFT)                   /*!< FGPIOA_PDIR: PDI25 Mask                 */
#define GPIO_PDIR_PDI25_SHIFT                    25                                                  /*!< FGPIOA_PDIR: PDI25 Position             */
#define GPIO_PDIR_PDI26_MASK                     (0x01UL << GPIO_PDIR_PDI26_SHIFT)                   /*!< FGPIOA_PDIR: PDI26 Mask                 */
#define GPIO_PDIR_PDI26_SHIFT                    26                                                  /*!< FGPIOA_PDIR: PDI26 Position             */
#define GPIO_PDIR_PDI27_MASK                     (0x01UL << GPIO_PDIR_PDI27_SHIFT)                   /*!< FGPIOA_PDIR: PDI27 Mask                 */
#define GPIO_PDIR_PDI27_SHIFT                    27                                                  /*!< FGPIOA_PDIR: PDI27 Position             */
#define GPIO_PDIR_PDI28_MASK                     (0x01UL << GPIO_PDIR_PDI28_SHIFT)                   /*!< FGPIOA_PDIR: PDI28 Mask                 */
#define GPIO_PDIR_PDI28_SHIFT                    28                                                  /*!< FGPIOA_PDIR: PDI28 Position             */
#define GPIO_PDIR_PDI29_MASK                     (0x01UL << GPIO_PDIR_PDI29_SHIFT)                   /*!< FGPIOA_PDIR: PDI29 Mask                 */
#define GPIO_PDIR_PDI29_SHIFT                    29                                                  /*!< FGPIOA_PDIR: PDI29 Position             */
#define GPIO_PDIR_PDI30_MASK                     (0x01UL << GPIO_PDIR_PDI30_SHIFT)                   /*!< FGPIOA_PDIR: PDI30 Mask                 */
#define GPIO_PDIR_PDI30_SHIFT                    30                                                  /*!< FGPIOA_PDIR: PDI30 Position             */
#define GPIO_PDIR_PDI31_MASK                     (0x01UL << GPIO_PDIR_PDI31_SHIFT)                   /*!< FGPIOA_PDIR: PDI31 Mask                 */
#define GPIO_PDIR_PDI31_SHIFT                    31                                                  /*!< FGPIOA_PDIR: PDI31 Position             */

/* ------- FGPIOA_PDDR                              ------ */
#define GPIO_PDDR_PDD0_MASK                      (0x01UL << GPIO_PDDR_PDD0_SHIFT)                    /*!< FGPIOA_PDDR: PDD0 Mask                  */
#define GPIO_PDDR_PDD0_SHIFT                     0                                                   /*!< FGPIOA_PDDR: PDD0 Position              */
#define GPIO_PDDR_PDD1_MASK                      (0x01UL << GPIO_PDDR_PDD1_SHIFT)                    /*!< FGPIOA_PDDR: PDD1 Mask                  */
#define GPIO_PDDR_PDD1_SHIFT                     1                                                   /*!< FGPIOA_PDDR: PDD1 Position              */
#define GPIO_PDDR_PDD2_MASK                      (0x01UL << GPIO_PDDR_PDD2_SHIFT)                    /*!< FGPIOA_PDDR: PDD2 Mask                  */
#define GPIO_PDDR_PDD2_SHIFT                     2                                                   /*!< FGPIOA_PDDR: PDD2 Position              */
#define GPIO_PDDR_PDD3_MASK                      (0x01UL << GPIO_PDDR_PDD3_SHIFT)                    /*!< FGPIOA_PDDR: PDD3 Mask                  */
#define GPIO_PDDR_PDD3_SHIFT                     3                                                   /*!< FGPIOA_PDDR: PDD3 Position              */
#define GPIO_PDDR_PDD4_MASK                      (0x01UL << GPIO_PDDR_PDD4_SHIFT)                    /*!< FGPIOA_PDDR: PDD4 Mask                  */
#define GPIO_PDDR_PDD4_SHIFT                     4                                                   /*!< FGPIOA_PDDR: PDD4 Position              */
#define GPIO_PDDR_PDD5_MASK                      (0x01UL << GPIO_PDDR_PDD5_SHIFT)                    /*!< FGPIOA_PDDR: PDD5 Mask                  */
#define GPIO_PDDR_PDD5_SHIFT                     5                                                   /*!< FGPIOA_PDDR: PDD5 Position              */
#define GPIO_PDDR_PDD6_MASK                      (0x01UL << GPIO_PDDR_PDD6_SHIFT)                    /*!< FGPIOA_PDDR: PDD6 Mask                  */
#define GPIO_PDDR_PDD6_SHIFT                     6                                                   /*!< FGPIOA_PDDR: PDD6 Position              */
#define GPIO_PDDR_PDD7_MASK                      (0x01UL << GPIO_PDDR_PDD7_SHIFT)                    /*!< FGPIOA_PDDR: PDD7 Mask                  */
#define GPIO_PDDR_PDD7_SHIFT                     7                                                   /*!< FGPIOA_PDDR: PDD7 Position              */
#define GPIO_PDDR_PDD8_MASK                      (0x01UL << GPIO_PDDR_PDD8_SHIFT)                    /*!< FGPIOA_PDDR: PDD8 Mask                  */
#define GPIO_PDDR_PDD8_SHIFT                     8                                                   /*!< FGPIOA_PDDR: PDD8 Position              */
#define GPIO_PDDR_PDD9_MASK                      (0x01UL << GPIO_PDDR_PDD9_SHIFT)                    /*!< FGPIOA_PDDR: PDD9 Mask                  */
#define GPIO_PDDR_PDD9_SHIFT                     9                                                   /*!< FGPIOA_PDDR: PDD9 Position              */
#define GPIO_PDDR_PDD10_MASK                     (0x01UL << GPIO_PDDR_PDD10_SHIFT)                   /*!< FGPIOA_PDDR: PDD10 Mask                 */
#define GPIO_PDDR_PDD10_SHIFT                    10                                                  /*!< FGPIOA_PDDR: PDD10 Position             */
#define GPIO_PDDR_PDD11_MASK                     (0x01UL << GPIO_PDDR_PDD11_SHIFT)                   /*!< FGPIOA_PDDR: PDD11 Mask                 */
#define GPIO_PDDR_PDD11_SHIFT                    11                                                  /*!< FGPIOA_PDDR: PDD11 Position             */
#define GPIO_PDDR_PDD12_MASK                     (0x01UL << GPIO_PDDR_PDD12_SHIFT)                   /*!< FGPIOA_PDDR: PDD12 Mask                 */
#define GPIO_PDDR_PDD12_SHIFT                    12                                                  /*!< FGPIOA_PDDR: PDD12 Position             */
#define GPIO_PDDR_PDD13_MASK                     (0x01UL << GPIO_PDDR_PDD13_SHIFT)                   /*!< FGPIOA_PDDR: PDD13 Mask                 */
#define GPIO_PDDR_PDD13_SHIFT                    13                                                  /*!< FGPIOA_PDDR: PDD13 Position             */
#define GPIO_PDDR_PDD14_MASK                     (0x01UL << GPIO_PDDR_PDD14_SHIFT)                   /*!< FGPIOA_PDDR: PDD14 Mask                 */
#define GPIO_PDDR_PDD14_SHIFT                    14                                                  /*!< FGPIOA_PDDR: PDD14 Position             */
#define GPIO_PDDR_PDD15_MASK                     (0x01UL << GPIO_PDDR_PDD15_SHIFT)                   /*!< FGPIOA_PDDR: PDD15 Mask                 */
#define GPIO_PDDR_PDD15_SHIFT                    15                                                  /*!< FGPIOA_PDDR: PDD15 Position             */
#define GPIO_PDDR_PDD16_MASK                     (0x01UL << GPIO_PDDR_PDD16_SHIFT)                   /*!< FGPIOA_PDDR: PDD16 Mask                 */
#define GPIO_PDDR_PDD16_SHIFT                    16                                                  /*!< FGPIOA_PDDR: PDD16 Position             */
#define GPIO_PDDR_PDD17_MASK                     (0x01UL << GPIO_PDDR_PDD17_SHIFT)                   /*!< FGPIOA_PDDR: PDD17 Mask                 */
#define GPIO_PDDR_PDD17_SHIFT                    17                                                  /*!< FGPIOA_PDDR: PDD17 Position             */
#define GPIO_PDDR_PDD18_MASK                     (0x01UL << GPIO_PDDR_PDD18_SHIFT)                   /*!< FGPIOA_PDDR: PDD18 Mask                 */
#define GPIO_PDDR_PDD18_SHIFT                    18                                                  /*!< FGPIOA_PDDR: PDD18 Position             */
#define GPIO_PDDR_PDD19_MASK                     (0x01UL << GPIO_PDDR_PDD19_SHIFT)                   /*!< FGPIOA_PDDR: PDD19 Mask                 */
#define GPIO_PDDR_PDD19_SHIFT                    19                                                  /*!< FGPIOA_PDDR: PDD19 Position             */
#define GPIO_PDDR_PDD20_MASK                     (0x01UL << GPIO_PDDR_PDD20_SHIFT)                   /*!< FGPIOA_PDDR: PDD20 Mask                 */
#define GPIO_PDDR_PDD20_SHIFT                    20                                                  /*!< FGPIOA_PDDR: PDD20 Position             */
#define GPIO_PDDR_PDD21_MASK                     (0x01UL << GPIO_PDDR_PDD21_SHIFT)                   /*!< FGPIOA_PDDR: PDD21 Mask                 */
#define GPIO_PDDR_PDD21_SHIFT                    21                                                  /*!< FGPIOA_PDDR: PDD21 Position             */
#define GPIO_PDDR_PDD22_MASK                     (0x01UL << GPIO_PDDR_PDD22_SHIFT)                   /*!< FGPIOA_PDDR: PDD22 Mask                 */
#define GPIO_PDDR_PDD22_SHIFT                    22                                                  /*!< FGPIOA_PDDR: PDD22 Position             */
#define GPIO_PDDR_PDD23_MASK                     (0x01UL << GPIO_PDDR_PDD23_SHIFT)                   /*!< FGPIOA_PDDR: PDD23 Mask                 */
#define GPIO_PDDR_PDD23_SHIFT                    23                                                  /*!< FGPIOA_PDDR: PDD23 Position             */
#define GPIO_PDDR_PDD24_MASK                     (0x01UL << GPIO_PDDR_PDD24_SHIFT)                   /*!< FGPIOA_PDDR: PDD24 Mask                 */
#define GPIO_PDDR_PDD24_SHIFT                    24                                                  /*!< FGPIOA_PDDR: PDD24 Position             */
#define GPIO_PDDR_PDD25_MASK                     (0x01UL << GPIO_PDDR_PDD25_SHIFT)                   /*!< FGPIOA_PDDR: PDD25 Mask                 */
#define GPIO_PDDR_PDD25_SHIFT                    25                                                  /*!< FGPIOA_PDDR: PDD25 Position             */
#define GPIO_PDDR_PDD26_MASK                     (0x01UL << GPIO_PDDR_PDD26_SHIFT)                   /*!< FGPIOA_PDDR: PDD26 Mask                 */
#define GPIO_PDDR_PDD26_SHIFT                    26                                                  /*!< FGPIOA_PDDR: PDD26 Position             */
#define GPIO_PDDR_PDD27_MASK                     (0x01UL << GPIO_PDDR_PDD27_SHIFT)                   /*!< FGPIOA_PDDR: PDD27 Mask                 */
#define GPIO_PDDR_PDD27_SHIFT                    27                                                  /*!< FGPIOA_PDDR: PDD27 Position             */
#define GPIO_PDDR_PDD28_MASK                     (0x01UL << GPIO_PDDR_PDD28_SHIFT)                   /*!< FGPIOA_PDDR: PDD28 Mask                 */
#define GPIO_PDDR_PDD28_SHIFT                    28                                                  /*!< FGPIOA_PDDR: PDD28 Position             */
#define GPIO_PDDR_PDD29_MASK                     (0x01UL << GPIO_PDDR_PDD29_SHIFT)                   /*!< FGPIOA_PDDR: PDD29 Mask                 */
#define GPIO_PDDR_PDD29_SHIFT                    29                                                  /*!< FGPIOA_PDDR: PDD29 Position             */
#define GPIO_PDDR_PDD30_MASK                     (0x01UL << GPIO_PDDR_PDD30_SHIFT)                   /*!< FGPIOA_PDDR: PDD30 Mask                 */
#define GPIO_PDDR_PDD30_SHIFT                    30                                                  /*!< FGPIOA_PDDR: PDD30 Position             */
#define GPIO_PDDR_PDD31_MASK                     (0x01UL << GPIO_PDDR_PDD31_SHIFT)                   /*!< FGPIOA_PDDR: PDD31 Mask                 */
#define GPIO_PDDR_PDD31_SHIFT                    31                                                  /*!< FGPIOA_PDDR: PDD31 Position             */

/* -------------------------------------------------------------------------------- */
/* -----------     'FGPIOA' Register Access macros                      ----------- */
/* -------------------------------------------------------------------------------- */

#define FGPIOA_PDOR                    (FGPIOA->PDOR)
#define FGPIOA_PSOR                    (FGPIOA->PSOR)
#define FGPIOA_PCOR                    (FGPIOA->PCOR)
#define FGPIOA_PTOR                    (FGPIOA->PTOR)
#define FGPIOA_PDIR                    (FGPIOA->PDIR)
#define FGPIOA_PDDR                    (FGPIOA->PDDR)

/* ================================================================================ */
/* ================           FGPIOB (derived from FGPIOA)         ================ */
/* ================================================================================ */

/**
 * @brief General Purpose Input/Output
 */
typedef FGPIOA_Type FGPIOB_Type;  /*!< FGPIOB Structure                                            */


/* -------------------------------------------------------------------------------- */
/* -----------     'FGPIOB' Register Access macros                      ----------- */
/* -------------------------------------------------------------------------------- */

#define FGPIOB_PDOR                    (FGPIOB->PDOR)
#define FGPIOB_PSOR                    (FGPIOB->PSOR)
#define FGPIOB_PCOR                    (FGPIOB->PCOR)
#define FGPIOB_PTOR                    (FGPIOB->PTOR)
#define FGPIOB_PDIR                    (FGPIOB->PDIR)
#define FGPIOB_PDDR                    (FGPIOB->PDDR)

/* ================================================================================ */
/* ================           FGPIOC (derived from FGPIOA)         ================ */
/* ================================================================================ */

/**
 * @brief General Purpose Input/Output
 */
typedef FGPIOA_Type FGPIOC_Type;  /*!< FGPIOC Structure                                            */


/* -------------------------------------------------------------------------------- */
/* -----------     'FGPIOC' Register Access macros                      ----------- */
/* -------------------------------------------------------------------------------- */

#define FGPIOC_PDOR                    (FGPIOC->PDOR)
#define FGPIOC_PSOR                    (FGPIOC->PSOR)
#define FGPIOC_PCOR                    (FGPIOC->PCOR)
#define FGPIOC_PTOR                    (FGPIOC->PTOR)
#define FGPIOC_PDIR                    (FGPIOC->PDIR)
#define FGPIOC_PDDR                    (FGPIOC->PDDR)

/* ================================================================================ */
/* ================           FGPIOD (derived from FGPIOA)         ================ */
/* ================================================================================ */

/**
 * @brief General Purpose Input/Output
 */
typedef FGPIOA_Type FGPIOD_Type;  /*!< FGPIOD Structure                                            */


/* -------------------------------------------------------------------------------- */
/* -----------     'FGPIOD' Register Access macros                      ----------- */
/* -------------------------------------------------------------------------------- */

#define FGPIOD_PDOR                    (FGPIOD->PDOR)
#define FGPIOD_PSOR                    (FGPIOD->PSOR)
#define FGPIOD_PCOR                    (FGPIOD->PCOR)
#define FGPIOD_PTOR                    (FGPIOD->PTOR)
#define FGPIOD_PDIR                    (FGPIOD->PDIR)
#define FGPIOD_PDDR                    (FGPIOD->PDDR)

/* ================================================================================ */
/* ================           FGPIOE (derived from FGPIOA)         ================ */
/* ================================================================================ */

/**
 * @brief General Purpose Input/Output
 */
typedef FGPIOA_Type FGPIOE_Type;  /*!< FGPIOE Structure                                            */


/* -------------------------------------------------------------------------------- */
/* -----------     'FGPIOE' Register Access macros                      ----------- */
/* -------------------------------------------------------------------------------- */

#define FGPIOE_PDOR                    (FGPIOE->PDOR)
#define FGPIOE_PSOR                    (FGPIOE->PSOR)
#define FGPIOE_PCOR                    (FGPIOE->PCOR)
#define FGPIOE_PTOR                    (FGPIOE->PTOR)
#define FGPIOE_PDIR                    (FGPIOE->PDIR)
#define FGPIOE_PDDR                    (FGPIOE->PDDR)

/* ================================================================================ */
/* ================           FTFA (file:FTFA)                     ================ */
/* ================================================================================ */

/**
 * @brief Flash Memory Interface
 */
typedef struct {                                /*!<       FTFA Structure                                               */
   __IO uint8_t   FSTAT;                        /*!< 0000: Flash Status Register                                        */
   __IO uint8_t   FCNFG;                        /*!< 0001: Flash Configuration Register                                 */
   __I  uint8_t   FSEC;                         /*!< 0002: Flash Security Register                                      */
   __I  uint8_t   FOPT;                         /*!< 0003: Flash Option Register                                        */
   __IO uint8_t   FCCOB3;                       /*!< 0004: FCCOB 3 - Usually Flash address [7..0]                       */
   __IO uint8_t   FCCOB2;                       /*!< 0005: FCCOB 2 - Usually Flash address [15..8]                      */
   __IO uint8_t   FCCOB1;                       /*!< 0006: FCCOB 1 - Usually Flash address [23..16]                     */
   __IO uint8_t   FCCOB0;                       /*!< 0007: FCCOB 0 - Usually FCMD (a code that defines the flash command)  */
   __IO uint8_t   FCCOB7;                       /*!< 0008: FCCOB 7 - Usually Data Byte 3                                */
   __IO uint8_t   FCCOB6;                       /*!< 0009: FCCOB 6 - Usually Data Byte 2                                */
   __IO uint8_t   FCCOB5;                       /*!< 000A: FCCOB 5 - Usually Data Byte 1                                */
   __IO uint8_t   FCCOB4;                       /*!< 000B: FCCOB 4 - Usually Data Byte 0                                */
   __IO uint8_t   FCCOBB;                       /*!< 000C: FCCOB B - Usually Data Byte 7                                */
   __IO uint8_t   FCCOBA;                       /*!< 000D: FCCOB A - Usually Data Byte 6                                */
   __IO uint8_t   FCCOB9;                       /*!< 000E: FCCOB 9 - Usually Data Byte 5                                */
   __IO uint8_t   FCCOB8;                       /*!< 000F: FCCOB 8 - Usually Data Byte 4                                */
   __IO uint8_t   FPROT3;                       /*!< 0010: Program Flash Protection                                     */
   __IO uint8_t   FPROT2;                       /*!< 0011: Program Flash Protection                                     */
   __IO uint8_t   FPROT1;                       /*!< 0012: Program Flash Protection                                     */
   __IO uint8_t   FPROT0;                       /*!< 0013: Program Flash Protection                                     */
} FTFA_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'FTFA' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- FTFA_FSTAT                               ------ */
#define FTFA_FSTAT_MGSTAT0_MASK                  (0x01UL << FTFA_FSTAT_MGSTAT0_SHIFT)                /*!< FTFA_FSTAT: MGSTAT0 Mask                */
#define FTFA_FSTAT_MGSTAT0_SHIFT                 0                                                   /*!< FTFA_FSTAT: MGSTAT0 Position            */
#define FTFA_FSTAT_FPVIOL_MASK                   (0x01UL << FTFA_FSTAT_FPVIOL_SHIFT)                 /*!< FTFA_FSTAT: FPVIOL Mask                 */
#define FTFA_FSTAT_FPVIOL_SHIFT                  4                                                   /*!< FTFA_FSTAT: FPVIOL Position             */
#define FTFA_FSTAT_ACCERR_MASK                   (0x01UL << FTFA_FSTAT_ACCERR_SHIFT)                 /*!< FTFA_FSTAT: ACCERR Mask                 */
#define FTFA_FSTAT_ACCERR_SHIFT                  5                                                   /*!< FTFA_FSTAT: ACCERR Position             */
#define FTFA_FSTAT_RDCOLERR_MASK                 (0x01UL << FTFA_FSTAT_RDCOLERR_SHIFT)               /*!< FTFA_FSTAT: RDCOLERR Mask               */
#define FTFA_FSTAT_RDCOLERR_SHIFT                6                                                   /*!< FTFA_FSTAT: RDCOLERR Position           */
#define FTFA_FSTAT_CCIF_MASK                     (0x01UL << FTFA_FSTAT_CCIF_SHIFT)                   /*!< FTFA_FSTAT: CCIF Mask                   */
#define FTFA_FSTAT_CCIF_SHIFT                    7                                                   /*!< FTFA_FSTAT: CCIF Position               */

/* ------- FTFA_FCNFG                               ------ */
#define FTFA_FCNFG_ERSSUSP_MASK                  (0x01UL << FTFA_FCNFG_ERSSUSP_SHIFT)                /*!< FTFA_FCNFG: ERSSUSP Mask                */
#define FTFA_FCNFG_ERSSUSP_SHIFT                 4                                                   /*!< FTFA_FCNFG: ERSSUSP Position            */
#define FTFA_FCNFG_ERSAREQ_MASK                  (0x01UL << FTFA_FCNFG_ERSAREQ_SHIFT)                /*!< FTFA_FCNFG: ERSAREQ Mask                */
#define FTFA_FCNFG_ERSAREQ_SHIFT                 5                                                   /*!< FTFA_FCNFG: ERSAREQ Position            */
#define FTFA_FCNFG_RDCOLLIE_MASK                 (0x01UL << FTFA_FCNFG_RDCOLLIE_SHIFT)               /*!< FTFA_FCNFG: RDCOLLIE Mask               */
#define FTFA_FCNFG_RDCOLLIE_SHIFT                6                                                   /*!< FTFA_FCNFG: RDCOLLIE Position           */
#define FTFA_FCNFG_CCIE_MASK                     (0x01UL << FTFA_FCNFG_CCIE_SHIFT)                   /*!< FTFA_FCNFG: CCIE Mask                   */
#define FTFA_FCNFG_CCIE_SHIFT                    7                                                   /*!< FTFA_FCNFG: CCIE Position               */

/* ------- FTFA_FSEC                                ------ */
#define FTFA_FSEC_SEC_MASK                       (0x03UL << FTFA_FSEC_SEC_SHIFT)                     /*!< FTFA_FSEC: SEC Mask                     */
#define FTFA_FSEC_SEC_SHIFT                      0                                                   /*!< FTFA_FSEC: SEC Position                 */
#define FTFA_FSEC_SEC(x)                         (((x)<<FTFA_FSEC_SEC_SHIFT)&FTFA_FSEC_SEC_MASK)     /*!< FTFA_FSEC                               */
#define FTFA_FSEC_FSLACC_MASK                    (0x03UL << FTFA_FSEC_FSLACC_SHIFT)                  /*!< FTFA_FSEC: FSLACC Mask                  */
#define FTFA_FSEC_FSLACC_SHIFT                   2                                                   /*!< FTFA_FSEC: FSLACC Position              */
#define FTFA_FSEC_FSLACC(x)                      (((x)<<FTFA_FSEC_FSLACC_SHIFT)&FTFA_FSEC_FSLACC_MASK) /*!< FTFA_FSEC                               */
#define FTFA_FSEC_MEEN_MASK                      (0x03UL << FTFA_FSEC_MEEN_SHIFT)                    /*!< FTFA_FSEC: MEEN Mask                    */
#define FTFA_FSEC_MEEN_SHIFT                     4                                                   /*!< FTFA_FSEC: MEEN Position                */
#define FTFA_FSEC_MEEN(x)                        (((x)<<FTFA_FSEC_MEEN_SHIFT)&FTFA_FSEC_MEEN_MASK)   /*!< FTFA_FSEC                               */
#define FTFA_FSEC_KEYEN_MASK                     (0x03UL << FTFA_FSEC_KEYEN_SHIFT)                   /*!< FTFA_FSEC: KEYEN Mask                   */
#define FTFA_FSEC_KEYEN_SHIFT                    6                                                   /*!< FTFA_FSEC: KEYEN Position               */
#define FTFA_FSEC_KEYEN(x)                       (((x)<<FTFA_FSEC_KEYEN_SHIFT)&FTFA_FSEC_KEYEN_MASK) /*!< FTFA_FSEC                               */

/* ------- FTFA_FOPT                                ------ */
#define FTFA_FOPT_OPT_MASK                       (0xFFUL << FTFA_FOPT_OPT_SHIFT)                     /*!< FTFA_FOPT: OPT Mask                     */
#define FTFA_FOPT_OPT_SHIFT                      0                                                   /*!< FTFA_FOPT: OPT Position                 */
#define FTFA_FOPT_OPT(x)                         (((x)<<FTFA_FOPT_OPT_SHIFT)&FTFA_FOPT_OPT_MASK)     /*!< FTFA_FOPT                               */

/* ------- FTFA_FCCOB                               ------ */
#define FTFA_FCCOB_CCOBn_MASK                    (0xFFUL << FTFA_FCCOB_CCOBn_SHIFT)                  /*!< FTFA_FCCOB: CCOBn Mask                  */
#define FTFA_FCCOB_CCOBn_SHIFT                   0                                                   /*!< FTFA_FCCOB: CCOBn Position              */
#define FTFA_FCCOB_CCOBn(x)                      (((x)<<FTFA_FCCOB_CCOBn_SHIFT)&FTFA_FCCOB_CCOBn_MASK) /*!< FTFA_FCCOB                              */

/* ------- FTFA_FPROT                               ------ */
#define FTFA_FPROT_PROT_MASK                     (0xFFUL << FTFA_FPROT_PROT_SHIFT)                   /*!< FTFA_FPROT: PROT Mask                   */
#define FTFA_FPROT_PROT_SHIFT                    0                                                   /*!< FTFA_FPROT: PROT Position               */
#define FTFA_FPROT_PROT(x)                       (((x)<<FTFA_FPROT_PROT_SHIFT)&FTFA_FPROT_PROT_MASK) /*!< FTFA_FPROT                              */

/* -------------------------------------------------------------------------------- */
/* -----------     'FTFA' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define FTFA_FSTAT                     (FTFA->FSTAT)
#define FTFA_FCNFG                     (FTFA->FCNFG)
#define FTFA_FSEC                      (FTFA->FSEC)
#define FTFA_FOPT                      (FTFA->FOPT)
#define FTFA_FCCOB3                    (FTFA->FCCOB3)
#define FTFA_FCCOB2                    (FTFA->FCCOB2)
#define FTFA_FCCOB1                    (FTFA->FCCOB1)
#define FTFA_FCCOB0                    (FTFA->FCCOB0)
#define FTFA_FCCOB7                    (FTFA->FCCOB7)
#define FTFA_FCCOB6                    (FTFA->FCCOB6)
#define FTFA_FCCOB5                    (FTFA->FCCOB5)
#define FTFA_FCCOB4                    (FTFA->FCCOB4)
#define FTFA_FCCOBB                    (FTFA->FCCOBB)
#define FTFA_FCCOBA                    (FTFA->FCCOBA)
#define FTFA_FCCOB9                    (FTFA->FCCOB9)
#define FTFA_FCCOB8                    (FTFA->FCCOB8)
#define FTFA_FPROT3                    (FTFA->FPROT3)
#define FTFA_FPROT2                    (FTFA->FPROT2)
#define FTFA_FPROT1                    (FTFA->FPROT1)
#define FTFA_FPROT0                    (FTFA->FPROT0)

/* ================================================================================ */
/* ================           GPIOA (derived from FGPIOA)          ================ */
/* ================================================================================ */

/**
 * @brief General Purpose Input/Output
 */
typedef FGPIOA_Type GPIOA_Type;  /*!< GPIOA Structure                                             */


/* -------------------------------------------------------------------------------- */
/* -----------     'GPIOA' Register Access macros                       ----------- */
/* -------------------------------------------------------------------------------- */

#define GPIOA_PDOR                     (GPIOA->PDOR)
#define GPIOA_PSOR                     (GPIOA->PSOR)
#define GPIOA_PCOR                     (GPIOA->PCOR)
#define GPIOA_PTOR                     (GPIOA->PTOR)
#define GPIOA_PDIR                     (GPIOA->PDIR)
#define GPIOA_PDDR                     (GPIOA->PDDR)

/* ================================================================================ */
/* ================           GPIOB (derived from GPIOA)           ================ */
/* ================================================================================ */

/**
 * @brief General Purpose Input/Output
 */
typedef GPIOA_Type GPIOB_Type;  /*!< GPIOB Structure                                             */


/* -------------------------------------------------------------------------------- */
/* -----------     'GPIOB' Register Access macros                       ----------- */
/* -------------------------------------------------------------------------------- */

#define GPIOB_PDOR                     (GPIOB->PDOR)
#define GPIOB_PSOR                     (GPIOB->PSOR)
#define GPIOB_PCOR                     (GPIOB->PCOR)
#define GPIOB_PTOR                     (GPIOB->PTOR)
#define GPIOB_PDIR                     (GPIOB->PDIR)
#define GPIOB_PDDR                     (GPIOB->PDDR)

/* ================================================================================ */
/* ================           GPIOC (derived from GPIOA)           ================ */
/* ================================================================================ */

/**
 * @brief General Purpose Input/Output
 */
typedef GPIOA_Type GPIOC_Type;  /*!< GPIOC Structure                                             */


/* -------------------------------------------------------------------------------- */
/* -----------     'GPIOC' Register Access macros                       ----------- */
/* -------------------------------------------------------------------------------- */

#define GPIOC_PDOR                     (GPIOC->PDOR)
#define GPIOC_PSOR                     (GPIOC->PSOR)
#define GPIOC_PCOR                     (GPIOC->PCOR)
#define GPIOC_PTOR                     (GPIOC->PTOR)
#define GPIOC_PDIR                     (GPIOC->PDIR)
#define GPIOC_PDDR                     (GPIOC->PDDR)

/* ================================================================================ */
/* ================           GPIOD (derived from GPIOA)           ================ */
/* ================================================================================ */

/**
 * @brief General Purpose Input/Output
 */
typedef GPIOA_Type GPIOD_Type;  /*!< GPIOD Structure                                             */


/* -------------------------------------------------------------------------------- */
/* -----------     'GPIOD' Register Access macros                       ----------- */
/* -------------------------------------------------------------------------------- */

#define GPIOD_PDOR                     (GPIOD->PDOR)
#define GPIOD_PSOR                     (GPIOD->PSOR)
#define GPIOD_PCOR                     (GPIOD->PCOR)
#define GPIOD_PTOR                     (GPIOD->PTOR)
#define GPIOD_PDIR                     (GPIOD->PDIR)
#define GPIOD_PDDR                     (GPIOD->PDDR)

/* ================================================================================ */
/* ================           GPIOE (derived from GPIOA)           ================ */
/* ================================================================================ */

/**
 * @brief General Purpose Input/Output
 */
typedef GPIOA_Type GPIOE_Type;  /*!< GPIOE Structure                                             */


/* -------------------------------------------------------------------------------- */
/* -----------     'GPIOE' Register Access macros                       ----------- */
/* -------------------------------------------------------------------------------- */

#define GPIOE_PDOR                     (GPIOE->PDOR)
#define GPIOE_PSOR                     (GPIOE->PSOR)
#define GPIOE_PCOR                     (GPIOE->PCOR)
#define GPIOE_PTOR                     (GPIOE->PTOR)
#define GPIOE_PDIR                     (GPIOE->PDIR)
#define GPIOE_PDDR                     (GPIOE->PDDR)

/* ================================================================================ */
/* ================           I2C0 (file:I2C0_MKL_SMB)             ================ */
/* ================================================================================ */

/**
 * @brief Inter-Integrated Circuit
 */
typedef struct {                                /*!<       I2C0 Structure                                               */
   __IO uint8_t   A1;                           /*!< 0000: Address Register 1                                           */
   __IO uint8_t   F;                            /*!< 0001: Frequency Divider register                                   */
   __IO uint8_t   C1;                           /*!< 0002: Control Register 1                                           */
   __IO uint8_t   S;                            /*!< 0003: Status Register                                              */
   __IO uint8_t   D;                            /*!< 0004: Data I/O register                                            */
   __IO uint8_t   C2;                           /*!< 0005: Control Register 2                                           */
   __IO uint8_t   FLT;                          /*!< 0006: Programmable Input Glitch Filter register                    */
   __IO uint8_t   RA;                           /*!< 0007: Range Address register                                       */
   __IO uint8_t   SMB;                          /*!< 0008: SMBus Control and Status register                            */
   __IO uint8_t   A2;                           /*!< 0009: Address Register 2                                           */
   __IO uint8_t   SLTH;                         /*!< 000A: SCL Low Timeout Register High                                */
   __IO uint8_t   SLTL;                         /*!< 000B: SCL Low Timeout Register Low                                 */
} I2C0_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'I2C0' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- I2C0_A1                                  ------ */
#define I2C_A1_AD_MASK                           (0x7FUL << I2C_A1_AD_SHIFT)                         /*!< I2C0_A1: AD Mask                        */
#define I2C_A1_AD_SHIFT                          1                                                   /*!< I2C0_A1: AD Position                    */
#define I2C_A1_AD(x)                             (((x)<<I2C_A1_AD_SHIFT)&I2C_A1_AD_MASK)             /*!< I2C0_A1                                 */

/* ------- I2C0_F                                   ------ */
#define I2C_F_ICR_MASK                           (0x3FUL << I2C_F_ICR_SHIFT)                         /*!< I2C0_F: ICR Mask                        */
#define I2C_F_ICR_SHIFT                          0                                                   /*!< I2C0_F: ICR Position                    */
#define I2C_F_ICR(x)                             (((x)<<I2C_F_ICR_SHIFT)&I2C_F_ICR_MASK)             /*!< I2C0_F                                  */
#define I2C_F_MULT_MASK                          (0x03UL << I2C_F_MULT_SHIFT)                        /*!< I2C0_F: MULT Mask                       */
#define I2C_F_MULT_SHIFT                         6                                                   /*!< I2C0_F: MULT Position                   */
#define I2C_F_MULT(x)                            (((x)<<I2C_F_MULT_SHIFT)&I2C_F_MULT_MASK)           /*!< I2C0_F                                  */

/* ------- I2C0_C1                                  ------ */
#define I2C_C1_DMAEN_MASK                        (0x01UL << I2C_C1_DMAEN_SHIFT)                      /*!< I2C0_C1: DMAEN Mask                     */
#define I2C_C1_DMAEN_SHIFT                       0                                                   /*!< I2C0_C1: DMAEN Position                 */
#define I2C_C1_WUEN_MASK                         (0x01UL << I2C_C1_WUEN_SHIFT)                       /*!< I2C0_C1: WUEN Mask                      */
#define I2C_C1_WUEN_SHIFT                        1                                                   /*!< I2C0_C1: WUEN Position                  */
#define I2C_C1_RSTA_MASK                         (0x01UL << I2C_C1_RSTA_SHIFT)                       /*!< I2C0_C1: RSTA Mask                      */
#define I2C_C1_RSTA_SHIFT                        2                                                   /*!< I2C0_C1: RSTA Position                  */
#define I2C_C1_TXAK_MASK                         (0x01UL << I2C_C1_TXAK_SHIFT)                       /*!< I2C0_C1: TXAK Mask                      */
#define I2C_C1_TXAK_SHIFT                        3                                                   /*!< I2C0_C1: TXAK Position                  */
#define I2C_C1_TX_MASK                           (0x01UL << I2C_C1_TX_SHIFT)                         /*!< I2C0_C1: TX Mask                        */
#define I2C_C1_TX_SHIFT                          4                                                   /*!< I2C0_C1: TX Position                    */
#define I2C_C1_MST_MASK                          (0x01UL << I2C_C1_MST_SHIFT)                        /*!< I2C0_C1: MST Mask                       */
#define I2C_C1_MST_SHIFT                         5                                                   /*!< I2C0_C1: MST Position                   */
#define I2C_C1_IICIE_MASK                        (0x01UL << I2C_C1_IICIE_SHIFT)                      /*!< I2C0_C1: IICIE Mask                     */
#define I2C_C1_IICIE_SHIFT                       6                                                   /*!< I2C0_C1: IICIE Position                 */
#define I2C_C1_IICEN_MASK                        (0x01UL << I2C_C1_IICEN_SHIFT)                      /*!< I2C0_C1: IICEN Mask                     */
#define I2C_C1_IICEN_SHIFT                       7                                                   /*!< I2C0_C1: IICEN Position                 */

/* ------- I2C0_S                                   ------ */
#define I2C_S_RXAK_MASK                          (0x01UL << I2C_S_RXAK_SHIFT)                        /*!< I2C0_S: RXAK Mask                       */
#define I2C_S_RXAK_SHIFT                         0                                                   /*!< I2C0_S: RXAK Position                   */
#define I2C_S_IICIF_MASK                         (0x01UL << I2C_S_IICIF_SHIFT)                       /*!< I2C0_S: IICIF Mask                      */
#define I2C_S_IICIF_SHIFT                        1                                                   /*!< I2C0_S: IICIF Position                  */
#define I2C_S_SRW_MASK                           (0x01UL << I2C_S_SRW_SHIFT)                         /*!< I2C0_S: SRW Mask                        */
#define I2C_S_SRW_SHIFT                          2                                                   /*!< I2C0_S: SRW Position                    */
#define I2C_S_RAM_MASK                           (0x01UL << I2C_S_RAM_SHIFT)                         /*!< I2C0_S: RAM Mask                        */
#define I2C_S_RAM_SHIFT                          3                                                   /*!< I2C0_S: RAM Position                    */
#define I2C_S_ARBL_MASK                          (0x01UL << I2C_S_ARBL_SHIFT)                        /*!< I2C0_S: ARBL Mask                       */
#define I2C_S_ARBL_SHIFT                         4                                                   /*!< I2C0_S: ARBL Position                   */
#define I2C_S_BUSY_MASK                          (0x01UL << I2C_S_BUSY_SHIFT)                        /*!< I2C0_S: BUSY Mask                       */
#define I2C_S_BUSY_SHIFT                         5                                                   /*!< I2C0_S: BUSY Position                   */
#define I2C_S_IAAS_MASK                          (0x01UL << I2C_S_IAAS_SHIFT)                        /*!< I2C0_S: IAAS Mask                       */
#define I2C_S_IAAS_SHIFT                         6                                                   /*!< I2C0_S: IAAS Position                   */
#define I2C_S_TCF_MASK                           (0x01UL << I2C_S_TCF_SHIFT)                         /*!< I2C0_S: TCF Mask                        */
#define I2C_S_TCF_SHIFT                          7                                                   /*!< I2C0_S: TCF Position                    */

/* ------- I2C0_D                                   ------ */
#define I2C_D_DATA_MASK                          (0xFFUL << I2C_D_DATA_SHIFT)                        /*!< I2C0_D: DATA Mask                       */
#define I2C_D_DATA_SHIFT                         0                                                   /*!< I2C0_D: DATA Position                   */
#define I2C_D_DATA(x)                            (((x)<<I2C_D_DATA_SHIFT)&I2C_D_DATA_MASK)           /*!< I2C0_D                                  */

/* ------- I2C0_C2                                  ------ */
#define I2C_C2_AD_MASK                           (0x07UL << I2C_C2_AD_SHIFT)                         /*!< I2C0_C2: AD Mask                        */
#define I2C_C2_AD_SHIFT                          0                                                   /*!< I2C0_C2: AD Position                    */
#define I2C_C2_AD(x)                             (((x)<<I2C_C2_AD_SHIFT)&I2C_C2_AD_MASK)             /*!< I2C0_C2                                 */
#define I2C_C2_RMEN_MASK                         (0x01UL << I2C_C2_RMEN_SHIFT)                       /*!< I2C0_C2: RMEN Mask                      */
#define I2C_C2_RMEN_SHIFT                        3                                                   /*!< I2C0_C2: RMEN Position                  */
#define I2C_C2_SBRC_MASK                         (0x01UL << I2C_C2_SBRC_SHIFT)                       /*!< I2C0_C2: SBRC Mask                      */
#define I2C_C2_SBRC_SHIFT                        4                                                   /*!< I2C0_C2: SBRC Position                  */
#define I2C_C2_HDRS_MASK                         (0x01UL << I2C_C2_HDRS_SHIFT)                       /*!< I2C0_C2: HDRS Mask                      */
#define I2C_C2_HDRS_SHIFT                        5                                                   /*!< I2C0_C2: HDRS Position                  */
#define I2C_C2_ADEXT_MASK                        (0x01UL << I2C_C2_ADEXT_SHIFT)                      /*!< I2C0_C2: ADEXT Mask                     */
#define I2C_C2_ADEXT_SHIFT                       6                                                   /*!< I2C0_C2: ADEXT Position                 */
#define I2C_C2_GCAEN_MASK                        (0x01UL << I2C_C2_GCAEN_SHIFT)                      /*!< I2C0_C2: GCAEN Mask                     */
#define I2C_C2_GCAEN_SHIFT                       7                                                   /*!< I2C0_C2: GCAEN Position                 */

/* ------- I2C0_FLT                                 ------ */
#define I2C_FLT_FLT_MASK                         (0x1FUL << I2C_FLT_FLT_SHIFT)                       /*!< I2C0_FLT: FLT Mask                      */
#define I2C_FLT_FLT_SHIFT                        0                                                   /*!< I2C0_FLT: FLT Position                  */
#define I2C_FLT_FLT(x)                           (((x)<<I2C_FLT_FLT_SHIFT)&I2C_FLT_FLT_MASK)         /*!< I2C0_FLT                                */
#define I2C_FLT_STOPIE_MASK                      (0x01UL << I2C_FLT_STOPIE_SHIFT)                    /*!< I2C0_FLT: STOPIE Mask                   */
#define I2C_FLT_STOPIE_SHIFT                     5                                                   /*!< I2C0_FLT: STOPIE Position               */
#define I2C_FLT_STOPF_MASK                       (0x01UL << I2C_FLT_STOPF_SHIFT)                     /*!< I2C0_FLT: STOPF Mask                    */
#define I2C_FLT_STOPF_SHIFT                      6                                                   /*!< I2C0_FLT: STOPF Position                */
#define I2C_FLT_SHEN_MASK                        (0x01UL << I2C_FLT_SHEN_SHIFT)                      /*!< I2C0_FLT: SHEN Mask                     */
#define I2C_FLT_SHEN_SHIFT                       7                                                   /*!< I2C0_FLT: SHEN Position                 */

/* ------- I2C0_RA                                  ------ */
#define I2C_RA_RAD_MASK                          (0x7FUL << I2C_RA_RAD_SHIFT)                        /*!< I2C0_RA: RAD Mask                       */
#define I2C_RA_RAD_SHIFT                         1                                                   /*!< I2C0_RA: RAD Position                   */
#define I2C_RA_RAD(x)                            (((x)<<I2C_RA_RAD_SHIFT)&I2C_RA_RAD_MASK)           /*!< I2C0_RA                                 */

/* ------- I2C0_SMB                                 ------ */
#define I2C_SMB_SHTF2IE_MASK                     (0x01UL << I2C_SMB_SHTF2IE_SHIFT)                   /*!< I2C0_SMB: SHTF2IE Mask                  */
#define I2C_SMB_SHTF2IE_SHIFT                    0                                                   /*!< I2C0_SMB: SHTF2IE Position              */
#define I2C_SMB_SHTF2_MASK                       (0x01UL << I2C_SMB_SHTF2_SHIFT)                     /*!< I2C0_SMB: SHTF2 Mask                    */
#define I2C_SMB_SHTF2_SHIFT                      1                                                   /*!< I2C0_SMB: SHTF2 Position                */
#define I2C_SMB_SHTF1_MASK                       (0x01UL << I2C_SMB_SHTF1_SHIFT)                     /*!< I2C0_SMB: SHTF1 Mask                    */
#define I2C_SMB_SHTF1_SHIFT                      2                                                   /*!< I2C0_SMB: SHTF1 Position                */
#define I2C_SMB_SLTF_MASK                        (0x01UL << I2C_SMB_SLTF_SHIFT)                      /*!< I2C0_SMB: SLTF Mask                     */
#define I2C_SMB_SLTF_SHIFT                       3                                                   /*!< I2C0_SMB: SLTF Position                 */
#define I2C_SMB_TCKSEL_MASK                      (0x01UL << I2C_SMB_TCKSEL_SHIFT)                    /*!< I2C0_SMB: TCKSEL Mask                   */
#define I2C_SMB_TCKSEL_SHIFT                     4                                                   /*!< I2C0_SMB: TCKSEL Position               */
#define I2C_SMB_SIICAEN_MASK                     (0x01UL << I2C_SMB_SIICAEN_SHIFT)                   /*!< I2C0_SMB: SIICAEN Mask                  */
#define I2C_SMB_SIICAEN_SHIFT                    5                                                   /*!< I2C0_SMB: SIICAEN Position              */
#define I2C_SMB_ALERTEN_MASK                     (0x01UL << I2C_SMB_ALERTEN_SHIFT)                   /*!< I2C0_SMB: ALERTEN Mask                  */
#define I2C_SMB_ALERTEN_SHIFT                    6                                                   /*!< I2C0_SMB: ALERTEN Position              */
#define I2C_SMB_FACK_MASK                        (0x01UL << I2C_SMB_FACK_SHIFT)                      /*!< I2C0_SMB: FACK Mask                     */
#define I2C_SMB_FACK_SHIFT                       7                                                   /*!< I2C0_SMB: FACK Position                 */

/* ------- I2C0_A2                                  ------ */
#define I2C_A2_SAD_MASK                          (0x7FUL << I2C_A2_SAD_SHIFT)                        /*!< I2C0_A2: SAD Mask                       */
#define I2C_A2_SAD_SHIFT                         1                                                   /*!< I2C0_A2: SAD Position                   */
#define I2C_A2_SAD(x)                            (((x)<<I2C_A2_SAD_SHIFT)&I2C_A2_SAD_MASK)           /*!< I2C0_A2                                 */

/* ------- I2C0_SLTH                                ------ */
#define I2C_SLTH_SSLT_MASK                       (0xFFUL << I2C_SLTH_SSLT_SHIFT)                     /*!< I2C0_SLTH: SSLT Mask                    */
#define I2C_SLTH_SSLT_SHIFT                      0                                                   /*!< I2C0_SLTH: SSLT Position                */
#define I2C_SLTH_SSLT(x)                         (((x)<<I2C_SLTH_SSLT_SHIFT)&I2C_SLTH_SSLT_MASK)     /*!< I2C0_SLTH                               */

/* ------- I2C0_SLTL                                ------ */
#define I2C_SLTL_SSLT_MASK                       (0xFFUL << I2C_SLTL_SSLT_SHIFT)                     /*!< I2C0_SLTL: SSLT Mask                    */
#define I2C_SLTL_SSLT_SHIFT                      0                                                   /*!< I2C0_SLTL: SSLT Position                */
#define I2C_SLTL_SSLT(x)                         (((x)<<I2C_SLTL_SSLT_SHIFT)&I2C_SLTL_SSLT_MASK)     /*!< I2C0_SLTL                               */

/* -------------------------------------------------------------------------------- */
/* -----------     'I2C0' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define I2C0_A1                        (I2C0->A1)
#define I2C0_F                         (I2C0->F)
#define I2C0_C1                        (I2C0->C1)
#define I2C0_S                         (I2C0->S)
#define I2C0_D                         (I2C0->D)
#define I2C0_C2                        (I2C0->C2)
#define I2C0_FLT                       (I2C0->FLT)
#define I2C0_RA                        (I2C0->RA)
#define I2C0_SMB                       (I2C0->SMB)
#define I2C0_A2                        (I2C0->A2)
#define I2C0_SLTH                      (I2C0->SLTH)
#define I2C0_SLTL                      (I2C0->SLTL)

/* ================================================================================ */
/* ================           I2C1 (derived from I2C0)             ================ */
/* ================================================================================ */

/**
 * @brief Inter-Integrated Circuit
 */
typedef I2C0_Type I2C1_Type;  /*!< I2C1 Structure                                              */


/* -------------------------------------------------------------------------------- */
/* -----------     'I2C1' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define I2C1_A1                        (I2C1->A1)
#define I2C1_F                         (I2C1->F)
#define I2C1_C1                        (I2C1->C1)
#define I2C1_S                         (I2C1->S)
#define I2C1_D                         (I2C1->D)
#define I2C1_C2                        (I2C1->C2)
#define I2C1_FLT                       (I2C1->FLT)
#define I2C1_RA                        (I2C1->RA)
#define I2C1_SMB                       (I2C1->SMB)
#define I2C1_A2                        (I2C1->A2)
#define I2C1_SLTH                      (I2C1->SLTH)
#define I2C1_SLTL                      (I2C1->SLTL)

/* ================================================================================ */
/* ================           I2S0 (file:I2S0_MKL)                 ================ */
/* ================================================================================ */

/**
 * @brief Inter-IC Sound / Synchronous Audio Interface
 */
typedef struct {                                /*!<       I2S0 Structure                                               */
   __IO uint32_t  TCSR;                         /*!< 0000: SAI Transmit Control Register                                */
   __I  uint32_t  RESERVED0;                    /*!< 0004:                                                              */
   __IO uint32_t  TCR2;                         /*!< 0008: SAI Transmit Configuration 2 Register                        */
   __IO uint32_t  TCR3;                         /*!< 000C: SAI Transmit Configuration 3 Register                        */
   __IO uint32_t  TCR4;                         /*!< 0010: SAI Transmit Configuration 4 Register                        */
   __IO uint32_t  TCR5;                         /*!< 0014: SAI Transmit Configuration 5 Register                        */
   __I  uint32_t  RESERVED1[2];                 /*!< 0018:                                                              */
   __O  uint32_t  TDR0;                         /*!< 0020: SAI Transmit Data Register                                   */
   __I  uint32_t  RESERVED2[15];                /*!< 0024:                                                              */
   __IO uint32_t  TMR;                          /*!< 0060: SAI Transmit Mask Register                                   */
   __I  uint32_t  RESERVED3[7];                 /*!< 0064:                                                              */
   __IO uint32_t  RCSR;                         /*!< 0080: SAI Receive Control Register                                 */
   __I  uint32_t  RESERVED4;                    /*!< 0084:                                                              */
   __IO uint32_t  RCR2;                         /*!< 0088: SAI Receive Configuration 2 Register                         */
   __IO uint32_t  RCR3;                         /*!< 008C: SAI Receive Configuration 3 Register                         */
   __IO uint32_t  RCR4;                         /*!< 0090: SAI Receive Configuration 4 Register                         */
   __IO uint32_t  RCR5;                         /*!< 0094: SAI Receive Configuration 5 Register                         */
   __I  uint32_t  RESERVED5[2];                 /*!< 0098:                                                              */
   __I  uint32_t  RDR[1];                       /*!< 00A0: SAI Receive Data Register                                    */
   __I  uint32_t  RESERVED6[15];                /*!< 00A4:                                                              */
   __IO uint32_t  RMR;                          /*!< 00E0: SAI Receive Mask Register                                    */
   __I  uint32_t  RESERVED7[7];                 /*!< 00E4:                                                              */
   __IO uint32_t  MCR;                          /*!< 0100: SAI MCLK Control Register                                    */
   __IO uint32_t  MDR;                          /*!< 0104: SAI MCLK Divide Register                                     */
} I2S0_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'I2S0' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- I2S0_TCSR                                ------ */
#define I2S_TCSR_FWDE_MASK                       (0x01UL << I2S_TCSR_FWDE_SHIFT)                     /*!< I2S_TCSR: FWDE Mask                     */
#define I2S_TCSR_FWDE_SHIFT                      1                                                   /*!< I2S_TCSR: FWDE Position                 */
#define I2S_TCSR_FWIE_MASK                       (0x01UL << I2S_TCSR_FWIE_SHIFT)                     /*!< I2S_TCSR: FWIE Mask                     */
#define I2S_TCSR_FWIE_SHIFT                      9                                                   /*!< I2S_TCSR: FWIE Position                 */
#define I2S_TCSR_FEIE_MASK                       (0x01UL << I2S_TCSR_FEIE_SHIFT)                     /*!< I2S_TCSR: FEIE Mask                     */
#define I2S_TCSR_FEIE_SHIFT                      10                                                  /*!< I2S_TCSR: FEIE Position                 */
#define I2S_TCSR_SEIE_MASK                       (0x01UL << I2S_TCSR_SEIE_SHIFT)                     /*!< I2S_TCSR: SEIE Mask                     */
#define I2S_TCSR_SEIE_SHIFT                      11                                                  /*!< I2S_TCSR: SEIE Position                 */
#define I2S_TCSR_WSIE_MASK                       (0x01UL << I2S_TCSR_WSIE_SHIFT)                     /*!< I2S_TCSR: WSIE Mask                     */
#define I2S_TCSR_WSIE_SHIFT                      12                                                  /*!< I2S_TCSR: WSIE Position                 */
#define I2S_TCSR_FWF_MASK                        (0x01UL << I2S_TCSR_FWF_SHIFT)                      /*!< I2S_TCSR: FWF Mask                      */
#define I2S_TCSR_FWF_SHIFT                       17                                                  /*!< I2S_TCSR: FWF Position                  */
#define I2S_TCSR_FEF_MASK                        (0x01UL << I2S_TCSR_FEF_SHIFT)                      /*!< I2S_TCSR: FEF Mask                      */
#define I2S_TCSR_FEF_SHIFT                       18                                                  /*!< I2S_TCSR: FEF Position                  */
#define I2S_TCSR_SEF_MASK                        (0x01UL << I2S_TCSR_SEF_SHIFT)                      /*!< I2S_TCSR: SEF Mask                      */
#define I2S_TCSR_SEF_SHIFT                       19                                                  /*!< I2S_TCSR: SEF Position                  */
#define I2S_TCSR_WSF_MASK                        (0x01UL << I2S_TCSR_WSF_SHIFT)                      /*!< I2S_TCSR: WSF Mask                      */
#define I2S_TCSR_WSF_SHIFT                       20                                                  /*!< I2S_TCSR: WSF Position                  */
#define I2S_TCSR_SR_MASK                         (0x01UL << I2S_TCSR_SR_SHIFT)                       /*!< I2S_TCSR: SR Mask                       */
#define I2S_TCSR_SR_SHIFT                        24                                                  /*!< I2S_TCSR: SR Position                   */
#define I2S_TCSR_FR_MASK                         (0x01UL << I2S_TCSR_FR_SHIFT)                       /*!< I2S_TCSR: FR Mask                       */
#define I2S_TCSR_FR_SHIFT                        25                                                  /*!< I2S_TCSR: FR Position                   */
#define I2S_TCSR_BCE_MASK                        (0x01UL << I2S_TCSR_BCE_SHIFT)                      /*!< I2S_TCSR: BCE Mask                      */
#define I2S_TCSR_BCE_SHIFT                       28                                                  /*!< I2S_TCSR: BCE Position                  */
#define I2S_TCSR_DBGE_MASK                       (0x01UL << I2S_TCSR_DBGE_SHIFT)                     /*!< I2S_TCSR: DBGE Mask                     */
#define I2S_TCSR_DBGE_SHIFT                      29                                                  /*!< I2S_TCSR: DBGE Position                 */
#define I2S_TCSR_STOPE_MASK                      (0x01UL << I2S_TCSR_STOPE_SHIFT)                    /*!< I2S_TCSR: STOPE Mask                    */
#define I2S_TCSR_STOPE_SHIFT                     30                                                  /*!< I2S_TCSR: STOPE Position                */
#define I2S_TCSR_TE_MASK                         (0x01UL << I2S_TCSR_TE_SHIFT)                       /*!< I2S_TCSR: TE Mask                       */
#define I2S_TCSR_TE_SHIFT                        31                                                  /*!< I2S_TCSR: TE Position                   */

/* ------- I2S0_TCR2                                ------ */
#define I2S_TCR2_DIV_MASK                        (0xFFUL << I2S_TCR2_DIV_SHIFT)                      /*!< I2S_TCR2: DIV Mask                      */
#define I2S_TCR2_DIV_SHIFT                       0                                                   /*!< I2S_TCR2: DIV Position                  */
#define I2S_TCR2_DIV(x)                          (((x)<<I2S_TCR2_DIV_SHIFT)&I2S_TCR2_DIV_MASK)       /*!< I2S_TCR2                                */
#define I2S_TCR2_BCD_MASK                        (0x01UL << I2S_TCR2_BCD_SHIFT)                      /*!< I2S_TCR2: BCD Mask                      */
#define I2S_TCR2_BCD_SHIFT                       24                                                  /*!< I2S_TCR2: BCD Position                  */
#define I2S_TCR2_BCP_MASK                        (0x01UL << I2S_TCR2_BCP_SHIFT)                      /*!< I2S_TCR2: BCP Mask                      */
#define I2S_TCR2_BCP_SHIFT                       25                                                  /*!< I2S_TCR2: BCP Position                  */
#define I2S_TCR2_CLKMODE_MASK                    (0x03UL << I2S_TCR2_CLKMODE_SHIFT)                  /*!< I2S_TCR2: CLKMODE Mask                  */
#define I2S_TCR2_CLKMODE_SHIFT                   26                                                  /*!< I2S_TCR2: CLKMODE Position              */
#define I2S_TCR2_CLKMODE(x)                      (((x)<<I2S_TCR2_CLKMODE_SHIFT)&I2S_TCR2_CLKMODE_MASK) /*!< I2S_TCR2                                */

/* ------- I2S0_TCR3                                ------ */
#define I2S_TCR3_WDFL_MASK                       (0x01UL << I2S_TCR3_WDFL_SHIFT)                     /*!< I2S_TCR3: WDFL Mask                     */
#define I2S_TCR3_WDFL_SHIFT                      0                                                   /*!< I2S_TCR3: WDFL Position                 */
#define I2S_TCR3_TCE_MASK                        (0x01UL << I2S_TCR3_TCE_SHIFT)                      /*!< I2S_TCR3: TCE Mask                      */
#define I2S_TCR3_TCE_SHIFT                       16                                                  /*!< I2S_TCR3: TCE Position                  */

/* ------- I2S0_TCR4                                ------ */
#define I2S_TCR4_FSD_MASK                        (0x01UL << I2S_TCR4_FSD_SHIFT)                      /*!< I2S_TCR4: FSD Mask                      */
#define I2S_TCR4_FSD_SHIFT                       0                                                   /*!< I2S_TCR4: FSD Position                  */
#define I2S_TCR4_FSP_MASK                        (0x01UL << I2S_TCR4_FSP_SHIFT)                      /*!< I2S_TCR4: FSP Mask                      */
#define I2S_TCR4_FSP_SHIFT                       1                                                   /*!< I2S_TCR4: FSP Position                  */
#define I2S_TCR4_FSE_MASK                        (0x01UL << I2S_TCR4_FSE_SHIFT)                      /*!< I2S_TCR4: FSE Mask                      */
#define I2S_TCR4_FSE_SHIFT                       3                                                   /*!< I2S_TCR4: FSE Position                  */
#define I2S_TCR4_MF_MASK                         (0x01UL << I2S_TCR4_MF_SHIFT)                       /*!< I2S_TCR4: MF Mask                       */
#define I2S_TCR4_MF_SHIFT                        4                                                   /*!< I2S_TCR4: MF Position                   */
#define I2S_TCR4_SYWD_MASK                       (0x1FUL << I2S_TCR4_SYWD_SHIFT)                     /*!< I2S_TCR4: SYWD Mask                     */
#define I2S_TCR4_SYWD_SHIFT                      8                                                   /*!< I2S_TCR4: SYWD Position                 */
#define I2S_TCR4_SYWD(x)                         (((x)<<I2S_TCR4_SYWD_SHIFT)&I2S_TCR4_SYWD_MASK)     /*!< I2S_TCR4                                */
#define I2S_TCR4_FRSZ_MASK                       (0x01UL << I2S_TCR4_FRSZ_SHIFT)                     /*!< I2S_TCR4: FRSZ Mask                     */
#define I2S_TCR4_FRSZ_SHIFT                      16                                                  /*!< I2S_TCR4: FRSZ Position                 */

/* ------- I2S0_TCR5                                ------ */
#define I2S_TCR5_FBT_MASK                        (0x1FUL << I2S_TCR5_FBT_SHIFT)                      /*!< I2S_TCR5: FBT Mask                      */
#define I2S_TCR5_FBT_SHIFT                       8                                                   /*!< I2S_TCR5: FBT Position                  */
#define I2S_TCR5_FBT(x)                          (((x)<<I2S_TCR5_FBT_SHIFT)&I2S_TCR5_FBT_MASK)       /*!< I2S_TCR5                                */
#define I2S_TCR5_W0W_MASK                        (0x1FUL << I2S_TCR5_W0W_SHIFT)                      /*!< I2S_TCR5: W0W Mask                      */
#define I2S_TCR5_W0W_SHIFT                       16                                                  /*!< I2S_TCR5: W0W Position                  */
#define I2S_TCR5_W0W(x)                          (((x)<<I2S_TCR5_W0W_SHIFT)&I2S_TCR5_W0W_MASK)       /*!< I2S_TCR5                                */
#define I2S_TCR5_WNW_MASK                        (0x1FUL << I2S_TCR5_WNW_SHIFT)                      /*!< I2S_TCR5: WNW Mask                      */
#define I2S_TCR5_WNW_SHIFT                       24                                                  /*!< I2S_TCR5: WNW Position                  */
#define I2S_TCR5_WNW(x)                          (((x)<<I2S_TCR5_WNW_SHIFT)&I2S_TCR5_WNW_MASK)       /*!< I2S_TCR5                                */

/* ------- I2S0_TDR0                                ------ */
#define I2S_TDR0_TDR_MASK                        (0xFFFFFFFFUL << I2S_TDR0_TDR_SHIFT)                /*!< I2S_TDR0: TDR Mask                      */
#define I2S_TDR0_TDR_SHIFT                       0                                                   /*!< I2S_TDR0: TDR Position                  */
#define I2S_TDR0_TDR(x)                          (((x)<<I2S_TDR0_TDR_SHIFT)&I2S_TDR0_TDR_MASK)       /*!< I2S_TDR0                                */

/* ------- I2S0_TMR                                 ------ */
#define I2S_TMR_TWM_MASK                         (0x03UL << I2S_TMR_TWM_SHIFT)                       /*!< I2S_TMR: TWM Mask                       */
#define I2S_TMR_TWM_SHIFT                        0                                                   /*!< I2S_TMR: TWM Position                   */
#define I2S_TMR_TWM(x)                           (((x)<<I2S_TMR_TWM_SHIFT)&I2S_TMR_TWM_MASK)         /*!< I2S_TMR                                 */

/* ------- I2S0_RCSR                                ------ */
#define I2S_RCSR_FWDE_MASK                       (0x01UL << I2S_RCSR_FWDE_SHIFT)                     /*!< I2S_RCSR: FWDE Mask                     */
#define I2S_RCSR_FWDE_SHIFT                      1                                                   /*!< I2S_RCSR: FWDE Position                 */
#define I2S_RCSR_FWIE_MASK                       (0x01UL << I2S_RCSR_FWIE_SHIFT)                     /*!< I2S_RCSR: FWIE Mask                     */
#define I2S_RCSR_FWIE_SHIFT                      9                                                   /*!< I2S_RCSR: FWIE Position                 */
#define I2S_RCSR_FEIE_MASK                       (0x01UL << I2S_RCSR_FEIE_SHIFT)                     /*!< I2S_RCSR: FEIE Mask                     */
#define I2S_RCSR_FEIE_SHIFT                      10                                                  /*!< I2S_RCSR: FEIE Position                 */
#define I2S_RCSR_SEIE_MASK                       (0x01UL << I2S_RCSR_SEIE_SHIFT)                     /*!< I2S_RCSR: SEIE Mask                     */
#define I2S_RCSR_SEIE_SHIFT                      11                                                  /*!< I2S_RCSR: SEIE Position                 */
#define I2S_RCSR_WSIE_MASK                       (0x01UL << I2S_RCSR_WSIE_SHIFT)                     /*!< I2S_RCSR: WSIE Mask                     */
#define I2S_RCSR_WSIE_SHIFT                      12                                                  /*!< I2S_RCSR: WSIE Position                 */
#define I2S_RCSR_FWF_MASK                        (0x01UL << I2S_RCSR_FWF_SHIFT)                      /*!< I2S_RCSR: FWF Mask                      */
#define I2S_RCSR_FWF_SHIFT                       17                                                  /*!< I2S_RCSR: FWF Position                  */
#define I2S_RCSR_FEF_MASK                        (0x01UL << I2S_RCSR_FEF_SHIFT)                      /*!< I2S_RCSR: FEF Mask                      */
#define I2S_RCSR_FEF_SHIFT                       18                                                  /*!< I2S_RCSR: FEF Position                  */
#define I2S_RCSR_SEF_MASK                        (0x01UL << I2S_RCSR_SEF_SHIFT)                      /*!< I2S_RCSR: SEF Mask                      */
#define I2S_RCSR_SEF_SHIFT                       19                                                  /*!< I2S_RCSR: SEF Position                  */
#define I2S_RCSR_WSF_MASK                        (0x01UL << I2S_RCSR_WSF_SHIFT)                      /*!< I2S_RCSR: WSF Mask                      */
#define I2S_RCSR_WSF_SHIFT                       20                                                  /*!< I2S_RCSR: WSF Position                  */
#define I2S_RCSR_SR_MASK                         (0x01UL << I2S_RCSR_SR_SHIFT)                       /*!< I2S_RCSR: SR Mask                       */
#define I2S_RCSR_SR_SHIFT                        24                                                  /*!< I2S_RCSR: SR Position                   */
#define I2S_RCSR_FR_MASK                         (0x01UL << I2S_RCSR_FR_SHIFT)                       /*!< I2S_RCSR: FR Mask                       */
#define I2S_RCSR_FR_SHIFT                        25                                                  /*!< I2S_RCSR: FR Position                   */
#define I2S_RCSR_BCE_MASK                        (0x01UL << I2S_RCSR_BCE_SHIFT)                      /*!< I2S_RCSR: BCE Mask                      */
#define I2S_RCSR_BCE_SHIFT                       28                                                  /*!< I2S_RCSR: BCE Position                  */
#define I2S_RCSR_DBGE_MASK                       (0x01UL << I2S_RCSR_DBGE_SHIFT)                     /*!< I2S_RCSR: DBGE Mask                     */
#define I2S_RCSR_DBGE_SHIFT                      29                                                  /*!< I2S_RCSR: DBGE Position                 */
#define I2S_RCSR_STOPE_MASK                      (0x01UL << I2S_RCSR_STOPE_SHIFT)                    /*!< I2S_RCSR: STOPE Mask                    */
#define I2S_RCSR_STOPE_SHIFT                     30                                                  /*!< I2S_RCSR: STOPE Position                */
#define I2S_RCSR_RE_MASK                         (0x01UL << I2S_RCSR_RE_SHIFT)                       /*!< I2S_RCSR: RE Mask                       */
#define I2S_RCSR_RE_SHIFT                        31                                                  /*!< I2S_RCSR: RE Position                   */

/* ------- I2S0_RCR2                                ------ */
#define I2S_RCR2_DIV_MASK                        (0xFFUL << I2S_RCR2_DIV_SHIFT)                      /*!< I2S_RCR2: DIV Mask                      */
#define I2S_RCR2_DIV_SHIFT                       0                                                   /*!< I2S_RCR2: DIV Position                  */
#define I2S_RCR2_DIV(x)                          (((x)<<I2S_RCR2_DIV_SHIFT)&I2S_RCR2_DIV_MASK)       /*!< I2S_RCR2                                */
#define I2S_RCR2_BCD_MASK                        (0x01UL << I2S_RCR2_BCD_SHIFT)                      /*!< I2S_RCR2: BCD Mask                      */
#define I2S_RCR2_BCD_SHIFT                       24                                                  /*!< I2S_RCR2: BCD Position                  */
#define I2S_RCR2_BCP_MASK                        (0x01UL << I2S_RCR2_BCP_SHIFT)                      /*!< I2S_RCR2: BCP Mask                      */
#define I2S_RCR2_BCP_SHIFT                       25                                                  /*!< I2S_RCR2: BCP Position                  */
#define I2S_RCR2_CLKMODE_MASK                    (0x03UL << I2S_RCR2_CLKMODE_SHIFT)                  /*!< I2S_RCR2: CLKMODE Mask                  */
#define I2S_RCR2_CLKMODE_SHIFT                   26                                                  /*!< I2S_RCR2: CLKMODE Position              */
#define I2S_RCR2_CLKMODE(x)                      (((x)<<I2S_RCR2_CLKMODE_SHIFT)&I2S_RCR2_CLKMODE_MASK) /*!< I2S_RCR2                                */

/* ------- I2S0_RCR3                                ------ */
#define I2S_RCR3_WDFL_MASK                       (0x1FUL << I2S_RCR3_WDFL_SHIFT)                     /*!< I2S_RCR3: WDFL Mask                     */
#define I2S_RCR3_WDFL_SHIFT                      0                                                   /*!< I2S_RCR3: WDFL Position                 */
#define I2S_RCR3_WDFL(x)                         (((x)<<I2S_RCR3_WDFL_SHIFT)&I2S_RCR3_WDFL_MASK)     /*!< I2S_RCR3                                */
#define I2S_RCR3_RCE_MASK                        (0x03UL << I2S_RCR3_RCE_SHIFT)                      /*!< I2S_RCR3: RCE Mask                      */
#define I2S_RCR3_RCE_SHIFT                       16                                                  /*!< I2S_RCR3: RCE Position                  */
#define I2S_RCR3_RCE(x)                          (((x)<<I2S_RCR3_RCE_SHIFT)&I2S_RCR3_RCE_MASK)       /*!< I2S_RCR3                                */

/* ------- I2S0_RCR4                                ------ */
#define I2S_RCR4_FSD_MASK                        (0x01UL << I2S_RCR4_FSD_SHIFT)                      /*!< I2S_RCR4: FSD Mask                      */
#define I2S_RCR4_FSD_SHIFT                       0                                                   /*!< I2S_RCR4: FSD Position                  */
#define I2S_RCR4_FSP_MASK                        (0x01UL << I2S_RCR4_FSP_SHIFT)                      /*!< I2S_RCR4: FSP Mask                      */
#define I2S_RCR4_FSP_SHIFT                       1                                                   /*!< I2S_RCR4: FSP Position                  */
#define I2S_RCR4_FSE_MASK                        (0x01UL << I2S_RCR4_FSE_SHIFT)                      /*!< I2S_RCR4: FSE Mask                      */
#define I2S_RCR4_FSE_SHIFT                       3                                                   /*!< I2S_RCR4: FSE Position                  */
#define I2S_RCR4_MF_MASK                         (0x01UL << I2S_RCR4_MF_SHIFT)                       /*!< I2S_RCR4: MF Mask                       */
#define I2S_RCR4_MF_SHIFT                        4                                                   /*!< I2S_RCR4: MF Position                   */
#define I2S_RCR4_SYWD_MASK                       (0x1FUL << I2S_RCR4_SYWD_SHIFT)                     /*!< I2S_RCR4: SYWD Mask                     */
#define I2S_RCR4_SYWD_SHIFT                      8                                                   /*!< I2S_RCR4: SYWD Position                 */
#define I2S_RCR4_SYWD(x)                         (((x)<<I2S_RCR4_SYWD_SHIFT)&I2S_RCR4_SYWD_MASK)     /*!< I2S_RCR4                                */
#define I2S_RCR4_FRSZ_MASK                       (0x01UL << I2S_RCR4_FRSZ_SHIFT)                     /*!< I2S_RCR4: FRSZ Mask                     */
#define I2S_RCR4_FRSZ_SHIFT                      16                                                  /*!< I2S_RCR4: FRSZ Position                 */

/* ------- I2S0_RCR5                                ------ */
#define I2S_RCR5_FBT_MASK                        (0x1FUL << I2S_RCR5_FBT_SHIFT)                      /*!< I2S_RCR5: FBT Mask                      */
#define I2S_RCR5_FBT_SHIFT                       8                                                   /*!< I2S_RCR5: FBT Position                  */
#define I2S_RCR5_FBT(x)                          (((x)<<I2S_RCR5_FBT_SHIFT)&I2S_RCR5_FBT_MASK)       /*!< I2S_RCR5                                */
#define I2S_RCR5_W0W_MASK                        (0x1FUL << I2S_RCR5_W0W_SHIFT)                      /*!< I2S_RCR5: W0W Mask                      */
#define I2S_RCR5_W0W_SHIFT                       16                                                  /*!< I2S_RCR5: W0W Position                  */
#define I2S_RCR5_W0W(x)                          (((x)<<I2S_RCR5_W0W_SHIFT)&I2S_RCR5_W0W_MASK)       /*!< I2S_RCR5                                */
#define I2S_RCR5_WNW_MASK                        (0x1FUL << I2S_RCR5_WNW_SHIFT)                      /*!< I2S_RCR5: WNW Mask                      */
#define I2S_RCR5_WNW_SHIFT                       24                                                  /*!< I2S_RCR5: WNW Position                  */
#define I2S_RCR5_WNW(x)                          (((x)<<I2S_RCR5_WNW_SHIFT)&I2S_RCR5_WNW_MASK)       /*!< I2S_RCR5                                */

/* ------- I2S0_RDR                                 ------ */
#define I2S_RDR_RDR_MASK                         (0xFFFFFFFFUL << I2S_RDR_RDR_SHIFT)                 /*!< I2S_RDR: RDR Mask                       */
#define I2S_RDR_RDR_SHIFT                        0                                                   /*!< I2S_RDR: RDR Position                   */
#define I2S_RDR_RDR(x)                           (((x)<<I2S_RDR_RDR_SHIFT)&I2S_RDR_RDR_MASK)         /*!< I2S_RDR                                 */

/* ------- I2S0_RMR                                 ------ */
#define I2S_RMR_RWM_MASK                         (0xFFFFUL << I2S_RMR_RWM_SHIFT)                     /*!< I2S_RMR: RWM Mask                       */
#define I2S_RMR_RWM_SHIFT                        0                                                   /*!< I2S_RMR: RWM Position                   */
#define I2S_RMR_RWM(x)                           (((x)<<I2S_RMR_RWM_SHIFT)&I2S_RMR_RWM_MASK)         /*!< I2S_RMR                                 */

/* ------- I2S0_MCR                                 ------ */
#define I2S_MCR_MICS_MASK                        (0x03UL << I2S_MCR_MICS_SHIFT)                      /*!< I2S_MCR: MICS Mask                      */
#define I2S_MCR_MICS_SHIFT                       24                                                  /*!< I2S_MCR: MICS Position                  */
#define I2S_MCR_MICS(x)                          (((x)<<I2S_MCR_MICS_SHIFT)&I2S_MCR_MICS_MASK)       /*!< I2S_MCR                                 */
#define I2S_MCR_MOE_MASK                         (0x01UL << I2S_MCR_MOE_SHIFT)                       /*!< I2S_MCR: MOE Mask                       */
#define I2S_MCR_MOE_SHIFT                        30                                                  /*!< I2S_MCR: MOE Position                   */
#define I2S_MCR_DUF_MASK                         (0x01UL << I2S_MCR_DUF_SHIFT)                       /*!< I2S_MCR: DUF Mask                       */
#define I2S_MCR_DUF_SHIFT                        31                                                  /*!< I2S_MCR: DUF Position                   */

/* ------- I2S0_MDR                                 ------ */
#define I2S_MDR_DIVIDE_MASK                      (0xFFFUL << I2S_MDR_DIVIDE_SHIFT)                   /*!< I2S_MDR: DIVIDE Mask                    */
#define I2S_MDR_DIVIDE_SHIFT                     0                                                   /*!< I2S_MDR: DIVIDE Position                */
#define I2S_MDR_DIVIDE(x)                        (((x)<<I2S_MDR_DIVIDE_SHIFT)&I2S_MDR_DIVIDE_MASK)   /*!< I2S_MDR                                 */
#define I2S_MDR_FRACT_MASK                       (0xFFUL << I2S_MDR_FRACT_SHIFT)                     /*!< I2S_MDR: FRACT Mask                     */
#define I2S_MDR_FRACT_SHIFT                      12                                                  /*!< I2S_MDR: FRACT Position                 */
#define I2S_MDR_FRACT(x)                         (((x)<<I2S_MDR_FRACT_SHIFT)&I2S_MDR_FRACT_MASK)     /*!< I2S_MDR                                 */

/* -------------------------------------------------------------------------------- */
/* -----------     'I2S0' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define I2S0_TCSR                      (I2S0->TCSR)
#define I2S0_TCR2                      (I2S0->TCR2)
#define I2S0_TCR3                      (I2S0->TCR3)
#define I2S0_TCR4                      (I2S0->TCR4)
#define I2S0_TCR5                      (I2S0->TCR5)
#define I2S0_TDR0                      (I2S0->TDR0)
#define I2S0_TMR                       (I2S0->TMR)
#define I2S0_RCSR                      (I2S0->RCSR)
#define I2S0_RCR2                      (I2S0->RCR2)
#define I2S0_RCR3                      (I2S0->RCR3)
#define I2S0_RCR4                      (I2S0->RCR4)
#define I2S0_RCR5                      (I2S0->RCR5)
#define I2S0_RDR0                      (I2S0->RDR[0])
#define I2S0_RMR                       (I2S0->RMR)
#define I2S0_MCR                       (I2S0->MCR)
#define I2S0_MDR                       (I2S0->MDR)

/* ================================================================================ */
/* ================           LCD (file:LCD_2)                     ================ */
/* ================================================================================ */

/**
 * @brief Segment Liquid Crystal Display
 */
typedef struct {                                /*!<       LCD Structure                                                */
   __IO uint32_t  GCR;                          /*!< 0000: LCD General Control Register                                 */
   __IO uint32_t  AR;                           /*!< 0004: LCD Auxiliary Register                                       */
   __IO uint32_t  FDCR;                         /*!< 0008: LCD Fault Detect Control Register                            */
   __IO uint32_t  FDSR;                         /*!< 000C: LCD Fault Detect Status Register                             */
   __IO uint32_t  PENL;                         /*!< 0010: LCD Pin Enable register                                      */
   __IO uint32_t  PENH;                         /*!< 0014: LCD Pin Enable register                                      */
   __IO uint32_t  BPENL;                        /*!< 0018: LCD Back Plane Enable register                               */
   __IO uint32_t  BPENH;                        /*!< 001C: LCD Back Plane Enable register                               */
   __IO uint32_t  WF3TO0;                       /*!< 0020: LCD Waveform register                                        */
   __IO uint32_t  WF7TO4;                       /*!< 0024: LCD Waveform register                                        */
   __IO uint32_t  WF11TO8;                      /*!< 0028: LCD Waveform register                                        */
   __IO uint32_t  WF15TO12;                     /*!< 002C: LCD Waveform register                                        */
   __IO uint32_t  WF19TO16;                     /*!< 0030: LCD Waveform register                                        */
   __IO uint32_t  WF23TO20;                     /*!< 0034: LCD Waveform register                                        */
   __IO uint32_t  WF27TO24;                     /*!< 0038: LCD Waveform register                                        */
   __IO uint32_t  WF31TO28;                     /*!< 003C: LCD Waveform register                                        */
   __IO uint32_t  WF35TO32;                     /*!< 0040: LCD Waveform register                                        */
   __IO uint32_t  WF39TO36;                     /*!< 0044: LCD Waveform register                                        */
   __IO uint32_t  WF43TO40;                     /*!< 0048: LCD Waveform register                                        */
   __IO uint32_t  WF47TO44;                     /*!< 004C: LCD Waveform register                                        */
   __IO uint32_t  WF51TO48;                     /*!< 0050: LCD Waveform register                                        */
   __IO uint32_t  WF55TO52;                     /*!< 0054: LCD Waveform register                                        */
   __IO uint32_t  WF59TO56;                     /*!< 0058: LCD Waveform register                                        */
   __IO uint32_t  WF63TO60;                     /*!< 005C: LCD Waveform register                                        */
} LCD_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'LCD' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- LCD_GCR                                  ------ */
#define LCD_GCR_DUTY_MASK                        (0x07UL << LCD_GCR_DUTY_SHIFT)                      /*!< LCD_GCR: DUTY Mask                      */
#define LCD_GCR_DUTY_SHIFT                       0                                                   /*!< LCD_GCR: DUTY Position                  */
#define LCD_GCR_DUTY(x)                          (((x)<<LCD_GCR_DUTY_SHIFT)&LCD_GCR_DUTY_MASK)       /*!< LCD_GCR                                 */
#define LCD_GCR_LCLK_MASK                        (0x07UL << LCD_GCR_LCLK_SHIFT)                      /*!< LCD_GCR: LCLK Mask                      */
#define LCD_GCR_LCLK_SHIFT                       3                                                   /*!< LCD_GCR: LCLK Position                  */
#define LCD_GCR_LCLK(x)                          (((x)<<LCD_GCR_LCLK_SHIFT)&LCD_GCR_LCLK_MASK)       /*!< LCD_GCR                                 */
#define LCD_GCR_SOURCE_MASK                      (0x01UL << LCD_GCR_SOURCE_SHIFT)                    /*!< LCD_GCR: SOURCE Mask                    */
#define LCD_GCR_SOURCE_SHIFT                     6                                                   /*!< LCD_GCR: SOURCE Position                */
#define LCD_GCR_LCDEN_MASK                       (0x01UL << LCD_GCR_LCDEN_SHIFT)                     /*!< LCD_GCR: LCDEN Mask                     */
#define LCD_GCR_LCDEN_SHIFT                      7                                                   /*!< LCD_GCR: LCDEN Position                 */
#define LCD_GCR_LCDSTP_MASK                      (0x01UL << LCD_GCR_LCDSTP_SHIFT)                    /*!< LCD_GCR: LCDSTP Mask                    */
#define LCD_GCR_LCDSTP_SHIFT                     8                                                   /*!< LCD_GCR: LCDSTP Position                */
#define LCD_GCR_LCDDOZE_MASK                     (0x01UL << LCD_GCR_LCDDOZE_SHIFT)                   /*!< LCD_GCR: LCDDOZE Mask                   */
#define LCD_GCR_LCDDOZE_SHIFT                    9                                                   /*!< LCD_GCR: LCDDOZE Position               */
#define LCD_GCR_FFR_MASK                         (0x01UL << LCD_GCR_FFR_SHIFT)                       /*!< LCD_GCR: FFR Mask                       */
#define LCD_GCR_FFR_SHIFT                        10                                                  /*!< LCD_GCR: FFR Position                   */
#define LCD_GCR_ALTSOURCE_MASK                   (0x01UL << LCD_GCR_ALTSOURCE_SHIFT)                 /*!< LCD_GCR: ALTSOURCE Mask                 */
#define LCD_GCR_ALTSOURCE_SHIFT                  11                                                  /*!< LCD_GCR: ALTSOURCE Position             */
#define LCD_GCR_ALTDIV_MASK                      (0x03UL << LCD_GCR_ALTDIV_SHIFT)                    /*!< LCD_GCR: ALTDIV Mask                    */
#define LCD_GCR_ALTDIV_SHIFT                     12                                                  /*!< LCD_GCR: ALTDIV Position                */
#define LCD_GCR_ALTDIV(x)                        (((x)<<LCD_GCR_ALTDIV_SHIFT)&LCD_GCR_ALTDIV_MASK)   /*!< LCD_GCR                                 */
#define LCD_GCR_FDCIEN_MASK                      (0x01UL << LCD_GCR_FDCIEN_SHIFT)                    /*!< LCD_GCR: FDCIEN Mask                    */
#define LCD_GCR_FDCIEN_SHIFT                     14                                                  /*!< LCD_GCR: FDCIEN Position                */
#define LCD_GCR_PADSAFE_MASK                     (0x01UL << LCD_GCR_PADSAFE_SHIFT)                   /*!< LCD_GCR: PADSAFE Mask                   */
#define LCD_GCR_PADSAFE_SHIFT                    15                                                  /*!< LCD_GCR: PADSAFE Position               */
#define LCD_GCR_VSUPPLY_MASK                     (0x01UL << LCD_GCR_VSUPPLY_SHIFT)                   /*!< LCD_GCR: VSUPPLY Mask                   */
#define LCD_GCR_VSUPPLY_SHIFT                    17                                                  /*!< LCD_GCR: VSUPPLY Position               */
#define LCD_GCR_LADJ_MASK                        (0x03UL << LCD_GCR_LADJ_SHIFT)                      /*!< LCD_GCR: LADJ Mask                      */
#define LCD_GCR_LADJ_SHIFT                       20                                                  /*!< LCD_GCR: LADJ Position                  */
#define LCD_GCR_LADJ(x)                          (((x)<<LCD_GCR_LADJ_SHIFT)&LCD_GCR_LADJ_MASK)       /*!< LCD_GCR                                 */
#define LCD_GCR_CPSEL_MASK                       (0x01UL << LCD_GCR_CPSEL_SHIFT)                     /*!< LCD_GCR: CPSEL Mask                     */
#define LCD_GCR_CPSEL_SHIFT                      23                                                  /*!< LCD_GCR: CPSEL Position                 */
#define LCD_GCR_RVTRIM_MASK                      (0x0FUL << LCD_GCR_RVTRIM_SHIFT)                    /*!< LCD_GCR: RVTRIM Mask                    */
#define LCD_GCR_RVTRIM_SHIFT                     24                                                  /*!< LCD_GCR: RVTRIM Position                */
#define LCD_GCR_RVTRIM(x)                        (((x)<<LCD_GCR_RVTRIM_SHIFT)&LCD_GCR_RVTRIM_MASK)   /*!< LCD_GCR                                 */
#define LCD_GCR_RVEN_MASK                        (0x01UL << LCD_GCR_RVEN_SHIFT)                      /*!< LCD_GCR: RVEN Mask                      */
#define LCD_GCR_RVEN_SHIFT                       31                                                  /*!< LCD_GCR: RVEN Position                  */

/* ------- LCD_AR                                   ------ */
#define LCD_AR_BRATE_MASK                        (0x07UL << LCD_AR_BRATE_SHIFT)                      /*!< LCD_AR: BRATE Mask                      */
#define LCD_AR_BRATE_SHIFT                       0                                                   /*!< LCD_AR: BRATE Position                  */
#define LCD_AR_BRATE(x)                          (((x)<<LCD_AR_BRATE_SHIFT)&LCD_AR_BRATE_MASK)       /*!< LCD_AR                                  */
#define LCD_AR_BMODE_MASK                        (0x01UL << LCD_AR_BMODE_SHIFT)                      /*!< LCD_AR: BMODE Mask                      */
#define LCD_AR_BMODE_SHIFT                       3                                                   /*!< LCD_AR: BMODE Position                  */
#define LCD_AR_BLANK_MASK                        (0x01UL << LCD_AR_BLANK_SHIFT)                      /*!< LCD_AR: BLANK Mask                      */
#define LCD_AR_BLANK_SHIFT                       5                                                   /*!< LCD_AR: BLANK Position                  */
#define LCD_AR_ALT_MASK                          (0x01UL << LCD_AR_ALT_SHIFT)                        /*!< LCD_AR: ALT Mask                        */
#define LCD_AR_ALT_SHIFT                         6                                                   /*!< LCD_AR: ALT Position                    */
#define LCD_AR_BLINK_MASK                        (0x01UL << LCD_AR_BLINK_SHIFT)                      /*!< LCD_AR: BLINK Mask                      */
#define LCD_AR_BLINK_SHIFT                       7                                                   /*!< LCD_AR: BLINK Position                  */

/* ------- LCD_FDCR                                 ------ */
#define LCD_FDCR_FDPINID_MASK                    (0x3FUL << LCD_FDCR_FDPINID_SHIFT)                  /*!< LCD_FDCR: FDPINID Mask                  */
#define LCD_FDCR_FDPINID_SHIFT                   0                                                   /*!< LCD_FDCR: FDPINID Position              */
#define LCD_FDCR_FDPINID(x)                      (((x)<<LCD_FDCR_FDPINID_SHIFT)&LCD_FDCR_FDPINID_MASK) /*!< LCD_FDCR                                */
#define LCD_FDCR_FDBPEN_MASK                     (0x01UL << LCD_FDCR_FDBPEN_SHIFT)                   /*!< LCD_FDCR: FDBPEN Mask                   */
#define LCD_FDCR_FDBPEN_SHIFT                    6                                                   /*!< LCD_FDCR: FDBPEN Position               */
#define LCD_FDCR_FDEN_MASK                       (0x01UL << LCD_FDCR_FDEN_SHIFT)                     /*!< LCD_FDCR: FDEN Mask                     */
#define LCD_FDCR_FDEN_SHIFT                      7                                                   /*!< LCD_FDCR: FDEN Position                 */
#define LCD_FDCR_FDSWW_MASK                      (0x07UL << LCD_FDCR_FDSWW_SHIFT)                    /*!< LCD_FDCR: FDSWW Mask                    */
#define LCD_FDCR_FDSWW_SHIFT                     9                                                   /*!< LCD_FDCR: FDSWW Position                */
#define LCD_FDCR_FDSWW(x)                        (((x)<<LCD_FDCR_FDSWW_SHIFT)&LCD_FDCR_FDSWW_MASK)   /*!< LCD_FDCR                                */
#define LCD_FDCR_FDPRS_MASK                      (0x07UL << LCD_FDCR_FDPRS_SHIFT)                    /*!< LCD_FDCR: FDPRS Mask                    */
#define LCD_FDCR_FDPRS_SHIFT                     12                                                  /*!< LCD_FDCR: FDPRS Position                */
#define LCD_FDCR_FDPRS(x)                        (((x)<<LCD_FDCR_FDPRS_SHIFT)&LCD_FDCR_FDPRS_MASK)   /*!< LCD_FDCR                                */

/* ------- LCD_FDSR                                 ------ */
#define LCD_FDSR_FDCNT_MASK                      (0xFFUL << LCD_FDSR_FDCNT_SHIFT)                    /*!< LCD_FDSR: FDCNT Mask                    */
#define LCD_FDSR_FDCNT_SHIFT                     0                                                   /*!< LCD_FDSR: FDCNT Position                */
#define LCD_FDSR_FDCNT(x)                        (((x)<<LCD_FDSR_FDCNT_SHIFT)&LCD_FDSR_FDCNT_MASK)   /*!< LCD_FDSR                                */
#define LCD_FDSR_FDCF_MASK                       (0x01UL << LCD_FDSR_FDCF_SHIFT)                     /*!< LCD_FDSR: FDCF Mask                     */
#define LCD_FDSR_FDCF_SHIFT                      15                                                  /*!< LCD_FDSR: FDCF Position                 */

/* ------- LCD_PENL                                 ------ */
#define LCD_PENL_PEN_MASK                        (0xFFFFFFFFUL << LCD_PENL_PEN_SHIFT)                /*!< LCD_PENL: PEN Mask                      */
#define LCD_PENL_PEN_SHIFT                       0                                                   /*!< LCD_PENL: PEN Position                  */
#define LCD_PENL_PEN(x)                          (((x)<<LCD_PENL_PEN_SHIFT)&LCD_PENL_PEN_MASK)       /*!< LCD_PENL                                */

/* ------- LCD_PENH                                 ------ */
#define LCD_PENH_PEN_MASK                        (0xFFFFFFFFUL << LCD_PENH_PEN_SHIFT)                /*!< LCD_PENH: PEN Mask                      */
#define LCD_PENH_PEN_SHIFT                       0                                                   /*!< LCD_PENH: PEN Position                  */
#define LCD_PENH_PEN(x)                          (((x)<<LCD_PENH_PEN_SHIFT)&LCD_PENH_PEN_MASK)       /*!< LCD_PENH                                */

/* ------- LCD_BPENL                                ------ */
#define LCD_BPENL_BPEN_MASK                      (0xFFFFFFFFUL << LCD_BPENL_BPEN_SHIFT)              /*!< LCD_BPENL: BPEN Mask                    */
#define LCD_BPENL_BPEN_SHIFT                     0                                                   /*!< LCD_BPENL: BPEN Position                */
#define LCD_BPENL_BPEN(x)                        (((x)<<LCD_BPENL_BPEN_SHIFT)&LCD_BPENL_BPEN_MASK)   /*!< LCD_BPENL                               */

/* ------- LCD_BPENH                                ------ */
#define LCD_BPENH_BPEN_MASK                      (0xFFFFFFFFUL << LCD_BPENH_BPEN_SHIFT)              /*!< LCD_BPENH: BPEN Mask                    */
#define LCD_BPENH_BPEN_SHIFT                     0                                                   /*!< LCD_BPENH: BPEN Position                */
#define LCD_BPENH_BPEN(x)                        (((x)<<LCD_BPENH_BPEN_SHIFT)&LCD_BPENH_BPEN_MASK)   /*!< LCD_BPENH                               */

/* ------- LCD_WF3TO0                               ------ */
#define LCD_WF3TO0_WF0_MASK                      (0xFFUL << LCD_WF3TO0_WF0_SHIFT)                    /*!< LCD_WF3TO0: WF0 Mask                    */
#define LCD_WF3TO0_WF0_SHIFT                     0                                                   /*!< LCD_WF3TO0: WF0 Position                */
#define LCD_WF3TO0_WF0(x)                        (((x)<<LCD_WF3TO0_WF0_SHIFT)&LCD_WF3TO0_WF0_MASK)   /*!< LCD_WF3TO0                              */
#define LCD_WF3TO0_WF1_MASK                      (0xFFUL << LCD_WF3TO0_WF1_SHIFT)                    /*!< LCD_WF3TO0: WF1 Mask                    */
#define LCD_WF3TO0_WF1_SHIFT                     8                                                   /*!< LCD_WF3TO0: WF1 Position                */
#define LCD_WF3TO0_WF1(x)                        (((x)<<LCD_WF3TO0_WF1_SHIFT)&LCD_WF3TO0_WF1_MASK)   /*!< LCD_WF3TO0                              */
#define LCD_WF3TO0_WF2_MASK                      (0xFFUL << LCD_WF3TO0_WF2_SHIFT)                    /*!< LCD_WF3TO0: WF2 Mask                    */
#define LCD_WF3TO0_WF2_SHIFT                     16                                                  /*!< LCD_WF3TO0: WF2 Position                */
#define LCD_WF3TO0_WF2(x)                        (((x)<<LCD_WF3TO0_WF2_SHIFT)&LCD_WF3TO0_WF2_MASK)   /*!< LCD_WF3TO0                              */
#define LCD_WF3TO0_WF3_MASK                      (0xFFUL << LCD_WF3TO0_WF3_SHIFT)                    /*!< LCD_WF3TO0: WF3 Mask                    */
#define LCD_WF3TO0_WF3_SHIFT                     24                                                  /*!< LCD_WF3TO0: WF3 Position                */
#define LCD_WF3TO0_WF3(x)                        (((x)<<LCD_WF3TO0_WF3_SHIFT)&LCD_WF3TO0_WF3_MASK)   /*!< LCD_WF3TO0                              */

/* ------- LCD_WF7TO4                               ------ */
#define LCD_WF7TO4_WF4_MASK                      (0xFFUL << LCD_WF7TO4_WF4_SHIFT)                    /*!< LCD_WF7TO4: WF4 Mask                    */
#define LCD_WF7TO4_WF4_SHIFT                     0                                                   /*!< LCD_WF7TO4: WF4 Position                */
#define LCD_WF7TO4_WF4(x)                        (((x)<<LCD_WF7TO4_WF4_SHIFT)&LCD_WF7TO4_WF4_MASK)   /*!< LCD_WF7TO4                              */
#define LCD_WF7TO4_WF5_MASK                      (0xFFUL << LCD_WF7TO4_WF5_SHIFT)                    /*!< LCD_WF7TO4: WF5 Mask                    */
#define LCD_WF7TO4_WF5_SHIFT                     8                                                   /*!< LCD_WF7TO4: WF5 Position                */
#define LCD_WF7TO4_WF5(x)                        (((x)<<LCD_WF7TO4_WF5_SHIFT)&LCD_WF7TO4_WF5_MASK)   /*!< LCD_WF7TO4                              */
#define LCD_WF7TO4_WF6_MASK                      (0xFFUL << LCD_WF7TO4_WF6_SHIFT)                    /*!< LCD_WF7TO4: WF6 Mask                    */
#define LCD_WF7TO4_WF6_SHIFT                     16                                                  /*!< LCD_WF7TO4: WF6 Position                */
#define LCD_WF7TO4_WF6(x)                        (((x)<<LCD_WF7TO4_WF6_SHIFT)&LCD_WF7TO4_WF6_MASK)   /*!< LCD_WF7TO4                              */
#define LCD_WF7TO4_WF7_MASK                      (0xFFUL << LCD_WF7TO4_WF7_SHIFT)                    /*!< LCD_WF7TO4: WF7 Mask                    */
#define LCD_WF7TO4_WF7_SHIFT                     24                                                  /*!< LCD_WF7TO4: WF7 Position                */
#define LCD_WF7TO4_WF7(x)                        (((x)<<LCD_WF7TO4_WF7_SHIFT)&LCD_WF7TO4_WF7_MASK)   /*!< LCD_WF7TO4                              */

/* ------- LCD_WF11TO8                              ------ */
#define LCD_WF11TO8_WF8_MASK                     (0xFFUL << LCD_WF11TO8_WF8_SHIFT)                   /*!< LCD_WF11TO8: WF8 Mask                   */
#define LCD_WF11TO8_WF8_SHIFT                    0                                                   /*!< LCD_WF11TO8: WF8 Position               */
#define LCD_WF11TO8_WF8(x)                       (((x)<<LCD_WF11TO8_WF8_SHIFT)&LCD_WF11TO8_WF8_MASK) /*!< LCD_WF11TO8                             */
#define LCD_WF11TO8_WF9_MASK                     (0xFFUL << LCD_WF11TO8_WF9_SHIFT)                   /*!< LCD_WF11TO8: WF9 Mask                   */
#define LCD_WF11TO8_WF9_SHIFT                    8                                                   /*!< LCD_WF11TO8: WF9 Position               */
#define LCD_WF11TO8_WF9(x)                       (((x)<<LCD_WF11TO8_WF9_SHIFT)&LCD_WF11TO8_WF9_MASK) /*!< LCD_WF11TO8                             */
#define LCD_WF11TO8_WF10_MASK                    (0xFFUL << LCD_WF11TO8_WF10_SHIFT)                  /*!< LCD_WF11TO8: WF10 Mask                  */
#define LCD_WF11TO8_WF10_SHIFT                   16                                                  /*!< LCD_WF11TO8: WF10 Position              */
#define LCD_WF11TO8_WF10(x)                      (((x)<<LCD_WF11TO8_WF10_SHIFT)&LCD_WF11TO8_WF10_MASK) /*!< LCD_WF11TO8                             */
#define LCD_WF11TO8_WF11_MASK                    (0xFFUL << LCD_WF11TO8_WF11_SHIFT)                  /*!< LCD_WF11TO8: WF11 Mask                  */
#define LCD_WF11TO8_WF11_SHIFT                   24                                                  /*!< LCD_WF11TO8: WF11 Position              */
#define LCD_WF11TO8_WF11(x)                      (((x)<<LCD_WF11TO8_WF11_SHIFT)&LCD_WF11TO8_WF11_MASK) /*!< LCD_WF11TO8                             */

/* ------- LCD_WF15TO12                             ------ */
#define LCD_WF15TO12_WF12_MASK                   (0xFFUL << LCD_WF15TO12_WF12_SHIFT)                 /*!< LCD_WF15TO12: WF12 Mask                 */
#define LCD_WF15TO12_WF12_SHIFT                  0                                                   /*!< LCD_WF15TO12: WF12 Position             */
#define LCD_WF15TO12_WF12(x)                     (((x)<<LCD_WF15TO12_WF12_SHIFT)&LCD_WF15TO12_WF12_MASK) /*!< LCD_WF15TO12                            */
#define LCD_WF15TO12_WF13_MASK                   (0xFFUL << LCD_WF15TO12_WF13_SHIFT)                 /*!< LCD_WF15TO12: WF13 Mask                 */
#define LCD_WF15TO12_WF13_SHIFT                  8                                                   /*!< LCD_WF15TO12: WF13 Position             */
#define LCD_WF15TO12_WF13(x)                     (((x)<<LCD_WF15TO12_WF13_SHIFT)&LCD_WF15TO12_WF13_MASK) /*!< LCD_WF15TO12                            */
#define LCD_WF15TO12_WF14_MASK                   (0xFFUL << LCD_WF15TO12_WF14_SHIFT)                 /*!< LCD_WF15TO12: WF14 Mask                 */
#define LCD_WF15TO12_WF14_SHIFT                  16                                                  /*!< LCD_WF15TO12: WF14 Position             */
#define LCD_WF15TO12_WF14(x)                     (((x)<<LCD_WF15TO12_WF14_SHIFT)&LCD_WF15TO12_WF14_MASK) /*!< LCD_WF15TO12                            */
#define LCD_WF15TO12_WF15_MASK                   (0xFFUL << LCD_WF15TO12_WF15_SHIFT)                 /*!< LCD_WF15TO12: WF15 Mask                 */
#define LCD_WF15TO12_WF15_SHIFT                  24                                                  /*!< LCD_WF15TO12: WF15 Position             */
#define LCD_WF15TO12_WF15(x)                     (((x)<<LCD_WF15TO12_WF15_SHIFT)&LCD_WF15TO12_WF15_MASK) /*!< LCD_WF15TO12                            */

/* ------- LCD_WF19TO16                             ------ */
#define LCD_WF19TO16_WF16_MASK                   (0xFFUL << LCD_WF19TO16_WF16_SHIFT)                 /*!< LCD_WF19TO16: WF16 Mask                 */
#define LCD_WF19TO16_WF16_SHIFT                  0                                                   /*!< LCD_WF19TO16: WF16 Position             */
#define LCD_WF19TO16_WF16(x)                     (((x)<<LCD_WF19TO16_WF16_SHIFT)&LCD_WF19TO16_WF16_MASK) /*!< LCD_WF19TO16                            */
#define LCD_WF19TO16_WF17_MASK                   (0xFFUL << LCD_WF19TO16_WF17_SHIFT)                 /*!< LCD_WF19TO16: WF17 Mask                 */
#define LCD_WF19TO16_WF17_SHIFT                  8                                                   /*!< LCD_WF19TO16: WF17 Position             */
#define LCD_WF19TO16_WF17(x)                     (((x)<<LCD_WF19TO16_WF17_SHIFT)&LCD_WF19TO16_WF17_MASK) /*!< LCD_WF19TO16                            */
#define LCD_WF19TO16_WF18_MASK                   (0xFFUL << LCD_WF19TO16_WF18_SHIFT)                 /*!< LCD_WF19TO16: WF18 Mask                 */
#define LCD_WF19TO16_WF18_SHIFT                  16                                                  /*!< LCD_WF19TO16: WF18 Position             */
#define LCD_WF19TO16_WF18(x)                     (((x)<<LCD_WF19TO16_WF18_SHIFT)&LCD_WF19TO16_WF18_MASK) /*!< LCD_WF19TO16                            */
#define LCD_WF19TO16_WF19_MASK                   (0xFFUL << LCD_WF19TO16_WF19_SHIFT)                 /*!< LCD_WF19TO16: WF19 Mask                 */
#define LCD_WF19TO16_WF19_SHIFT                  24                                                  /*!< LCD_WF19TO16: WF19 Position             */
#define LCD_WF19TO16_WF19(x)                     (((x)<<LCD_WF19TO16_WF19_SHIFT)&LCD_WF19TO16_WF19_MASK) /*!< LCD_WF19TO16                            */

/* ------- LCD_WF23TO20                             ------ */
#define LCD_WF23TO20_WF20_MASK                   (0xFFUL << LCD_WF23TO20_WF20_SHIFT)                 /*!< LCD_WF23TO20: WF20 Mask                 */
#define LCD_WF23TO20_WF20_SHIFT                  0                                                   /*!< LCD_WF23TO20: WF20 Position             */
#define LCD_WF23TO20_WF20(x)                     (((x)<<LCD_WF23TO20_WF20_SHIFT)&LCD_WF23TO20_WF20_MASK) /*!< LCD_WF23TO20                            */
#define LCD_WF23TO20_WF21_MASK                   (0xFFUL << LCD_WF23TO20_WF21_SHIFT)                 /*!< LCD_WF23TO20: WF21 Mask                 */
#define LCD_WF23TO20_WF21_SHIFT                  8                                                   /*!< LCD_WF23TO20: WF21 Position             */
#define LCD_WF23TO20_WF21(x)                     (((x)<<LCD_WF23TO20_WF21_SHIFT)&LCD_WF23TO20_WF21_MASK) /*!< LCD_WF23TO20                            */
#define LCD_WF23TO20_WF22_MASK                   (0xFFUL << LCD_WF23TO20_WF22_SHIFT)                 /*!< LCD_WF23TO20: WF22 Mask                 */
#define LCD_WF23TO20_WF22_SHIFT                  16                                                  /*!< LCD_WF23TO20: WF22 Position             */
#define LCD_WF23TO20_WF22(x)                     (((x)<<LCD_WF23TO20_WF22_SHIFT)&LCD_WF23TO20_WF22_MASK) /*!< LCD_WF23TO20                            */
#define LCD_WF23TO20_WF23_MASK                   (0xFFUL << LCD_WF23TO20_WF23_SHIFT)                 /*!< LCD_WF23TO20: WF23 Mask                 */
#define LCD_WF23TO20_WF23_SHIFT                  24                                                  /*!< LCD_WF23TO20: WF23 Position             */
#define LCD_WF23TO20_WF23(x)                     (((x)<<LCD_WF23TO20_WF23_SHIFT)&LCD_WF23TO20_WF23_MASK) /*!< LCD_WF23TO20                            */

/* ------- LCD_WF27TO24                             ------ */
#define LCD_WF27TO24_WF24_MASK                   (0xFFUL << LCD_WF27TO24_WF24_SHIFT)                 /*!< LCD_WF27TO24: WF24 Mask                 */
#define LCD_WF27TO24_WF24_SHIFT                  0                                                   /*!< LCD_WF27TO24: WF24 Position             */
#define LCD_WF27TO24_WF24(x)                     (((x)<<LCD_WF27TO24_WF24_SHIFT)&LCD_WF27TO24_WF24_MASK) /*!< LCD_WF27TO24                            */
#define LCD_WF27TO24_WF25_MASK                   (0xFFUL << LCD_WF27TO24_WF25_SHIFT)                 /*!< LCD_WF27TO24: WF25 Mask                 */
#define LCD_WF27TO24_WF25_SHIFT                  8                                                   /*!< LCD_WF27TO24: WF25 Position             */
#define LCD_WF27TO24_WF25(x)                     (((x)<<LCD_WF27TO24_WF25_SHIFT)&LCD_WF27TO24_WF25_MASK) /*!< LCD_WF27TO24                            */
#define LCD_WF27TO24_WF26_MASK                   (0xFFUL << LCD_WF27TO24_WF26_SHIFT)                 /*!< LCD_WF27TO24: WF26 Mask                 */
#define LCD_WF27TO24_WF26_SHIFT                  16                                                  /*!< LCD_WF27TO24: WF26 Position             */
#define LCD_WF27TO24_WF26(x)                     (((x)<<LCD_WF27TO24_WF26_SHIFT)&LCD_WF27TO24_WF26_MASK) /*!< LCD_WF27TO24                            */
#define LCD_WF27TO24_WF27_MASK                   (0xFFUL << LCD_WF27TO24_WF27_SHIFT)                 /*!< LCD_WF27TO24: WF27 Mask                 */
#define LCD_WF27TO24_WF27_SHIFT                  24                                                  /*!< LCD_WF27TO24: WF27 Position             */
#define LCD_WF27TO24_WF27(x)                     (((x)<<LCD_WF27TO24_WF27_SHIFT)&LCD_WF27TO24_WF27_MASK) /*!< LCD_WF27TO24                            */

/* ------- LCD_WF31TO28                             ------ */
#define LCD_WF31TO28_WF28_MASK                   (0xFFUL << LCD_WF31TO28_WF28_SHIFT)                 /*!< LCD_WF31TO28: WF28 Mask                 */
#define LCD_WF31TO28_WF28_SHIFT                  0                                                   /*!< LCD_WF31TO28: WF28 Position             */
#define LCD_WF31TO28_WF28(x)                     (((x)<<LCD_WF31TO28_WF28_SHIFT)&LCD_WF31TO28_WF28_MASK) /*!< LCD_WF31TO28                            */
#define LCD_WF31TO28_WF29_MASK                   (0xFFUL << LCD_WF31TO28_WF29_SHIFT)                 /*!< LCD_WF31TO28: WF29 Mask                 */
#define LCD_WF31TO28_WF29_SHIFT                  8                                                   /*!< LCD_WF31TO28: WF29 Position             */
#define LCD_WF31TO28_WF29(x)                     (((x)<<LCD_WF31TO28_WF29_SHIFT)&LCD_WF31TO28_WF29_MASK) /*!< LCD_WF31TO28                            */
#define LCD_WF31TO28_WF30_MASK                   (0xFFUL << LCD_WF31TO28_WF30_SHIFT)                 /*!< LCD_WF31TO28: WF30 Mask                 */
#define LCD_WF31TO28_WF30_SHIFT                  16                                                  /*!< LCD_WF31TO28: WF30 Position             */
#define LCD_WF31TO28_WF30(x)                     (((x)<<LCD_WF31TO28_WF30_SHIFT)&LCD_WF31TO28_WF30_MASK) /*!< LCD_WF31TO28                            */
#define LCD_WF31TO28_WF31_MASK                   (0xFFUL << LCD_WF31TO28_WF31_SHIFT)                 /*!< LCD_WF31TO28: WF31 Mask                 */
#define LCD_WF31TO28_WF31_SHIFT                  24                                                  /*!< LCD_WF31TO28: WF31 Position             */
#define LCD_WF31TO28_WF31(x)                     (((x)<<LCD_WF31TO28_WF31_SHIFT)&LCD_WF31TO28_WF31_MASK) /*!< LCD_WF31TO28                            */

/* ------- LCD_WF35TO32                             ------ */
#define LCD_WF35TO32_WF32_MASK                   (0xFFUL << LCD_WF35TO32_WF32_SHIFT)                 /*!< LCD_WF35TO32: WF32 Mask                 */
#define LCD_WF35TO32_WF32_SHIFT                  0                                                   /*!< LCD_WF35TO32: WF32 Position             */
#define LCD_WF35TO32_WF32(x)                     (((x)<<LCD_WF35TO32_WF32_SHIFT)&LCD_WF35TO32_WF32_MASK) /*!< LCD_WF35TO32                            */
#define LCD_WF35TO32_WF33_MASK                   (0xFFUL << LCD_WF35TO32_WF33_SHIFT)                 /*!< LCD_WF35TO32: WF33 Mask                 */
#define LCD_WF35TO32_WF33_SHIFT                  8                                                   /*!< LCD_WF35TO32: WF33 Position             */
#define LCD_WF35TO32_WF33(x)                     (((x)<<LCD_WF35TO32_WF33_SHIFT)&LCD_WF35TO32_WF33_MASK) /*!< LCD_WF35TO32                            */
#define LCD_WF35TO32_WF34_MASK                   (0xFFUL << LCD_WF35TO32_WF34_SHIFT)                 /*!< LCD_WF35TO32: WF34 Mask                 */
#define LCD_WF35TO32_WF34_SHIFT                  16                                                  /*!< LCD_WF35TO32: WF34 Position             */
#define LCD_WF35TO32_WF34(x)                     (((x)<<LCD_WF35TO32_WF34_SHIFT)&LCD_WF35TO32_WF34_MASK) /*!< LCD_WF35TO32                            */
#define LCD_WF35TO32_WF35_MASK                   (0xFFUL << LCD_WF35TO32_WF35_SHIFT)                 /*!< LCD_WF35TO32: WF35 Mask                 */
#define LCD_WF35TO32_WF35_SHIFT                  24                                                  /*!< LCD_WF35TO32: WF35 Position             */
#define LCD_WF35TO32_WF35(x)                     (((x)<<LCD_WF35TO32_WF35_SHIFT)&LCD_WF35TO32_WF35_MASK) /*!< LCD_WF35TO32                            */

/* ------- LCD_WF39TO36                             ------ */
#define LCD_WF39TO36_WF36_MASK                   (0xFFUL << LCD_WF39TO36_WF36_SHIFT)                 /*!< LCD_WF39TO36: WF36 Mask                 */
#define LCD_WF39TO36_WF36_SHIFT                  0                                                   /*!< LCD_WF39TO36: WF36 Position             */
#define LCD_WF39TO36_WF36(x)                     (((x)<<LCD_WF39TO36_WF36_SHIFT)&LCD_WF39TO36_WF36_MASK) /*!< LCD_WF39TO36                            */
#define LCD_WF39TO36_WF37_MASK                   (0xFFUL << LCD_WF39TO36_WF37_SHIFT)                 /*!< LCD_WF39TO36: WF37 Mask                 */
#define LCD_WF39TO36_WF37_SHIFT                  8                                                   /*!< LCD_WF39TO36: WF37 Position             */
#define LCD_WF39TO36_WF37(x)                     (((x)<<LCD_WF39TO36_WF37_SHIFT)&LCD_WF39TO36_WF37_MASK) /*!< LCD_WF39TO36                            */
#define LCD_WF39TO36_WF38_MASK                   (0xFFUL << LCD_WF39TO36_WF38_SHIFT)                 /*!< LCD_WF39TO36: WF38 Mask                 */
#define LCD_WF39TO36_WF38_SHIFT                  16                                                  /*!< LCD_WF39TO36: WF38 Position             */
#define LCD_WF39TO36_WF38(x)                     (((x)<<LCD_WF39TO36_WF38_SHIFT)&LCD_WF39TO36_WF38_MASK) /*!< LCD_WF39TO36                            */
#define LCD_WF39TO36_WF39_MASK                   (0xFFUL << LCD_WF39TO36_WF39_SHIFT)                 /*!< LCD_WF39TO36: WF39 Mask                 */
#define LCD_WF39TO36_WF39_SHIFT                  24                                                  /*!< LCD_WF39TO36: WF39 Position             */
#define LCD_WF39TO36_WF39(x)                     (((x)<<LCD_WF39TO36_WF39_SHIFT)&LCD_WF39TO36_WF39_MASK) /*!< LCD_WF39TO36                            */

/* ------- LCD_WF43TO40                             ------ */
#define LCD_WF43TO40_WF40_MASK                   (0xFFUL << LCD_WF43TO40_WF40_SHIFT)                 /*!< LCD_WF43TO40: WF40 Mask                 */
#define LCD_WF43TO40_WF40_SHIFT                  0                                                   /*!< LCD_WF43TO40: WF40 Position             */
#define LCD_WF43TO40_WF40(x)                     (((x)<<LCD_WF43TO40_WF40_SHIFT)&LCD_WF43TO40_WF40_MASK) /*!< LCD_WF43TO40                            */
#define LCD_WF43TO40_WF41_MASK                   (0xFFUL << LCD_WF43TO40_WF41_SHIFT)                 /*!< LCD_WF43TO40: WF41 Mask                 */
#define LCD_WF43TO40_WF41_SHIFT                  8                                                   /*!< LCD_WF43TO40: WF41 Position             */
#define LCD_WF43TO40_WF41(x)                     (((x)<<LCD_WF43TO40_WF41_SHIFT)&LCD_WF43TO40_WF41_MASK) /*!< LCD_WF43TO40                            */
#define LCD_WF43TO40_WF42_MASK                   (0xFFUL << LCD_WF43TO40_WF42_SHIFT)                 /*!< LCD_WF43TO40: WF42 Mask                 */
#define LCD_WF43TO40_WF42_SHIFT                  16                                                  /*!< LCD_WF43TO40: WF42 Position             */
#define LCD_WF43TO40_WF42(x)                     (((x)<<LCD_WF43TO40_WF42_SHIFT)&LCD_WF43TO40_WF42_MASK) /*!< LCD_WF43TO40                            */
#define LCD_WF43TO40_WF43_MASK                   (0xFFUL << LCD_WF43TO40_WF43_SHIFT)                 /*!< LCD_WF43TO40: WF43 Mask                 */
#define LCD_WF43TO40_WF43_SHIFT                  24                                                  /*!< LCD_WF43TO40: WF43 Position             */
#define LCD_WF43TO40_WF43(x)                     (((x)<<LCD_WF43TO40_WF43_SHIFT)&LCD_WF43TO40_WF43_MASK) /*!< LCD_WF43TO40                            */

/* ------- LCD_WF47TO44                             ------ */
#define LCD_WF47TO44_WF44_MASK                   (0xFFUL << LCD_WF47TO44_WF44_SHIFT)                 /*!< LCD_WF47TO44: WF44 Mask                 */
#define LCD_WF47TO44_WF44_SHIFT                  0                                                   /*!< LCD_WF47TO44: WF44 Position             */
#define LCD_WF47TO44_WF44(x)                     (((x)<<LCD_WF47TO44_WF44_SHIFT)&LCD_WF47TO44_WF44_MASK) /*!< LCD_WF47TO44                            */
#define LCD_WF47TO44_WF45_MASK                   (0xFFUL << LCD_WF47TO44_WF45_SHIFT)                 /*!< LCD_WF47TO44: WF45 Mask                 */
#define LCD_WF47TO44_WF45_SHIFT                  8                                                   /*!< LCD_WF47TO44: WF45 Position             */
#define LCD_WF47TO44_WF45(x)                     (((x)<<LCD_WF47TO44_WF45_SHIFT)&LCD_WF47TO44_WF45_MASK) /*!< LCD_WF47TO44                            */
#define LCD_WF47TO44_WF46_MASK                   (0xFFUL << LCD_WF47TO44_WF46_SHIFT)                 /*!< LCD_WF47TO44: WF46 Mask                 */
#define LCD_WF47TO44_WF46_SHIFT                  16                                                  /*!< LCD_WF47TO44: WF46 Position             */
#define LCD_WF47TO44_WF46(x)                     (((x)<<LCD_WF47TO44_WF46_SHIFT)&LCD_WF47TO44_WF46_MASK) /*!< LCD_WF47TO44                            */
#define LCD_WF47TO44_WF47_MASK                   (0xFFUL << LCD_WF47TO44_WF47_SHIFT)                 /*!< LCD_WF47TO44: WF47 Mask                 */
#define LCD_WF47TO44_WF47_SHIFT                  24                                                  /*!< LCD_WF47TO44: WF47 Position             */
#define LCD_WF47TO44_WF47(x)                     (((x)<<LCD_WF47TO44_WF47_SHIFT)&LCD_WF47TO44_WF47_MASK) /*!< LCD_WF47TO44                            */

/* ------- LCD_WF51TO48                             ------ */
#define LCD_WF51TO48_WF48_MASK                   (0xFFUL << LCD_WF51TO48_WF48_SHIFT)                 /*!< LCD_WF51TO48: WF48 Mask                 */
#define LCD_WF51TO48_WF48_SHIFT                  0                                                   /*!< LCD_WF51TO48: WF48 Position             */
#define LCD_WF51TO48_WF48(x)                     (((x)<<LCD_WF51TO48_WF48_SHIFT)&LCD_WF51TO48_WF48_MASK) /*!< LCD_WF51TO48                            */
#define LCD_WF51TO48_WF49_MASK                   (0xFFUL << LCD_WF51TO48_WF49_SHIFT)                 /*!< LCD_WF51TO48: WF49 Mask                 */
#define LCD_WF51TO48_WF49_SHIFT                  8                                                   /*!< LCD_WF51TO48: WF49 Position             */
#define LCD_WF51TO48_WF49(x)                     (((x)<<LCD_WF51TO48_WF49_SHIFT)&LCD_WF51TO48_WF49_MASK) /*!< LCD_WF51TO48                            */
#define LCD_WF51TO48_WF50_MASK                   (0xFFUL << LCD_WF51TO48_WF50_SHIFT)                 /*!< LCD_WF51TO48: WF50 Mask                 */
#define LCD_WF51TO48_WF50_SHIFT                  16                                                  /*!< LCD_WF51TO48: WF50 Position             */
#define LCD_WF51TO48_WF50(x)                     (((x)<<LCD_WF51TO48_WF50_SHIFT)&LCD_WF51TO48_WF50_MASK) /*!< LCD_WF51TO48                            */
#define LCD_WF51TO48_WF51_MASK                   (0xFFUL << LCD_WF51TO48_WF51_SHIFT)                 /*!< LCD_WF51TO48: WF51 Mask                 */
#define LCD_WF51TO48_WF51_SHIFT                  24                                                  /*!< LCD_WF51TO48: WF51 Position             */
#define LCD_WF51TO48_WF51(x)                     (((x)<<LCD_WF51TO48_WF51_SHIFT)&LCD_WF51TO48_WF51_MASK) /*!< LCD_WF51TO48                            */

/* ------- LCD_WF55TO52                             ------ */
#define LCD_WF55TO52_WF52_MASK                   (0xFFUL << LCD_WF55TO52_WF52_SHIFT)                 /*!< LCD_WF55TO52: WF52 Mask                 */
#define LCD_WF55TO52_WF52_SHIFT                  0                                                   /*!< LCD_WF55TO52: WF52 Position             */
#define LCD_WF55TO52_WF52(x)                     (((x)<<LCD_WF55TO52_WF52_SHIFT)&LCD_WF55TO52_WF52_MASK) /*!< LCD_WF55TO52                            */
#define LCD_WF55TO52_WF53_MASK                   (0xFFUL << LCD_WF55TO52_WF53_SHIFT)                 /*!< LCD_WF55TO52: WF53 Mask                 */
#define LCD_WF55TO52_WF53_SHIFT                  8                                                   /*!< LCD_WF55TO52: WF53 Position             */
#define LCD_WF55TO52_WF53(x)                     (((x)<<LCD_WF55TO52_WF53_SHIFT)&LCD_WF55TO52_WF53_MASK) /*!< LCD_WF55TO52                            */
#define LCD_WF55TO52_WF54_MASK                   (0xFFUL << LCD_WF55TO52_WF54_SHIFT)                 /*!< LCD_WF55TO52: WF54 Mask                 */
#define LCD_WF55TO52_WF54_SHIFT                  16                                                  /*!< LCD_WF55TO52: WF54 Position             */
#define LCD_WF55TO52_WF54(x)                     (((x)<<LCD_WF55TO52_WF54_SHIFT)&LCD_WF55TO52_WF54_MASK) /*!< LCD_WF55TO52                            */
#define LCD_WF55TO52_WF55_MASK                   (0xFFUL << LCD_WF55TO52_WF55_SHIFT)                 /*!< LCD_WF55TO52: WF55 Mask                 */
#define LCD_WF55TO52_WF55_SHIFT                  24                                                  /*!< LCD_WF55TO52: WF55 Position             */
#define LCD_WF55TO52_WF55(x)                     (((x)<<LCD_WF55TO52_WF55_SHIFT)&LCD_WF55TO52_WF55_MASK) /*!< LCD_WF55TO52                            */

/* ------- LCD_WF59TO56                             ------ */
#define LCD_WF59TO56_WF56_MASK                   (0xFFUL << LCD_WF59TO56_WF56_SHIFT)                 /*!< LCD_WF59TO56: WF56 Mask                 */
#define LCD_WF59TO56_WF56_SHIFT                  0                                                   /*!< LCD_WF59TO56: WF56 Position             */
#define LCD_WF59TO56_WF56(x)                     (((x)<<LCD_WF59TO56_WF56_SHIFT)&LCD_WF59TO56_WF56_MASK) /*!< LCD_WF59TO56                            */
#define LCD_WF59TO56_WF57_MASK                   (0xFFUL << LCD_WF59TO56_WF57_SHIFT)                 /*!< LCD_WF59TO56: WF57 Mask                 */
#define LCD_WF59TO56_WF57_SHIFT                  8                                                   /*!< LCD_WF59TO56: WF57 Position             */
#define LCD_WF59TO56_WF57(x)                     (((x)<<LCD_WF59TO56_WF57_SHIFT)&LCD_WF59TO56_WF57_MASK) /*!< LCD_WF59TO56                            */
#define LCD_WF59TO56_WF58_MASK                   (0xFFUL << LCD_WF59TO56_WF58_SHIFT)                 /*!< LCD_WF59TO56: WF58 Mask                 */
#define LCD_WF59TO56_WF58_SHIFT                  16                                                  /*!< LCD_WF59TO56: WF58 Position             */
#define LCD_WF59TO56_WF58(x)                     (((x)<<LCD_WF59TO56_WF58_SHIFT)&LCD_WF59TO56_WF58_MASK) /*!< LCD_WF59TO56                            */
#define LCD_WF59TO56_WF59_MASK                   (0xFFUL << LCD_WF59TO56_WF59_SHIFT)                 /*!< LCD_WF59TO56: WF59 Mask                 */
#define LCD_WF59TO56_WF59_SHIFT                  24                                                  /*!< LCD_WF59TO56: WF59 Position             */
#define LCD_WF59TO56_WF59(x)                     (((x)<<LCD_WF59TO56_WF59_SHIFT)&LCD_WF59TO56_WF59_MASK) /*!< LCD_WF59TO56                            */

/* ------- LCD_WF63TO60                             ------ */
#define LCD_WF63TO60_WF60_MASK                   (0xFFUL << LCD_WF63TO60_WF60_SHIFT)                 /*!< LCD_WF63TO60: WF60 Mask                 */
#define LCD_WF63TO60_WF60_SHIFT                  0                                                   /*!< LCD_WF63TO60: WF60 Position             */
#define LCD_WF63TO60_WF60(x)                     (((x)<<LCD_WF63TO60_WF60_SHIFT)&LCD_WF63TO60_WF60_MASK) /*!< LCD_WF63TO60                            */
#define LCD_WF63TO60_WF61_MASK                   (0xFFUL << LCD_WF63TO60_WF61_SHIFT)                 /*!< LCD_WF63TO60: WF61 Mask                 */
#define LCD_WF63TO60_WF61_SHIFT                  8                                                   /*!< LCD_WF63TO60: WF61 Position             */
#define LCD_WF63TO60_WF61(x)                     (((x)<<LCD_WF63TO60_WF61_SHIFT)&LCD_WF63TO60_WF61_MASK) /*!< LCD_WF63TO60                            */
#define LCD_WF63TO60_WF62_MASK                   (0xFFUL << LCD_WF63TO60_WF62_SHIFT)                 /*!< LCD_WF63TO60: WF62 Mask                 */
#define LCD_WF63TO60_WF62_SHIFT                  16                                                  /*!< LCD_WF63TO60: WF62 Position             */
#define LCD_WF63TO60_WF62(x)                     (((x)<<LCD_WF63TO60_WF62_SHIFT)&LCD_WF63TO60_WF62_MASK) /*!< LCD_WF63TO60                            */
#define LCD_WF63TO60_WF63_MASK                   (0xFFUL << LCD_WF63TO60_WF63_SHIFT)                 /*!< LCD_WF63TO60: WF63 Mask                 */
#define LCD_WF63TO60_WF63_SHIFT                  24                                                  /*!< LCD_WF63TO60: WF63 Position             */
#define LCD_WF63TO60_WF63(x)                     (((x)<<LCD_WF63TO60_WF63_SHIFT)&LCD_WF63TO60_WF63_MASK) /*!< LCD_WF63TO60                            */

/* -------------------------------------------------------------------------------- */
/* -----------     'LCD' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define LCD_GCR                        (LCD->GCR)
#define LCD_AR                         (LCD->AR)
#define LCD_FDCR                       (LCD->FDCR)
#define LCD_FDSR                       (LCD->FDSR)
#define LCD_PENL                       (LCD->PENL)
#define LCD_PENH                       (LCD->PENH)
#define LCD_BPENL                      (LCD->BPENL)
#define LCD_BPENH                      (LCD->BPENH)
#define LCD_WF3TO0                     (LCD->WF3TO0)
#define LCD_WF7TO4                     (LCD->WF7TO4)
#define LCD_WF11TO8                    (LCD->WF11TO8)
#define LCD_WF15TO12                   (LCD->WF15TO12)
#define LCD_WF19TO16                   (LCD->WF19TO16)
#define LCD_WF23TO20                   (LCD->WF23TO20)
#define LCD_WF27TO24                   (LCD->WF27TO24)
#define LCD_WF31TO28                   (LCD->WF31TO28)
#define LCD_WF35TO32                   (LCD->WF35TO32)
#define LCD_WF39TO36                   (LCD->WF39TO36)
#define LCD_WF43TO40                   (LCD->WF43TO40)
#define LCD_WF47TO44                   (LCD->WF47TO44)
#define LCD_WF51TO48                   (LCD->WF51TO48)
#define LCD_WF55TO52                   (LCD->WF55TO52)
#define LCD_WF59TO56                   (LCD->WF59TO56)
#define LCD_WF63TO60                   (LCD->WF63TO60)

/* ================================================================================ */
/* ================           LLWU (file:LLWU_MKL_1)               ================ */
/* ================================================================================ */

/**
 * @brief Low leakage wakeup unit
 */
typedef struct {                                /*!<       LLWU Structure                                               */
   __IO uint8_t   PE1;                          /*!< 0000: Pin Enable 1 Register                                        */
   __IO uint8_t   PE2;                          /*!< 0001: Pin Enable 2 Register                                        */
   __IO uint8_t   PE3;                          /*!< 0002: Pin Enable 3 Register                                        */
   __IO uint8_t   PE4;                          /*!< 0003: Pin Enable 4 Register                                        */
   __IO uint8_t   ME;                           /*!< 0004: Module Enable Register                                       */
   __IO uint8_t   F1;                           /*!< 0005: Flag 1 Register                                              */
   __IO uint8_t   F2;                           /*!< 0006: Flag 2 Register                                              */
   __IO uint8_t   F3;                           /*!< 0007: Flag 3 Register                                              */
   __IO uint8_t   FILT1;                        /*!< 0008: Pin Filter 1 register                                        */
   __IO uint8_t   FILT2;                        /*!< 0009: Pin Filter 2 register                                        */
} LLWU_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'LLWU' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- LLWU_PE1                                 ------ */
#define LLWU_PE1_WUPE0_MASK                      (0x03UL << LLWU_PE1_WUPE0_SHIFT)                    /*!< LLWU_PE1: WUPE0 Mask                    */
#define LLWU_PE1_WUPE0_SHIFT                     0                                                   /*!< LLWU_PE1: WUPE0 Position                */
#define LLWU_PE1_WUPE0(x)                        (((x)<<LLWU_PE1_WUPE0_SHIFT)&LLWU_PE1_WUPE0_MASK)   /*!< LLWU_PE1                                */
#define LLWU_PE1_WUPE1_MASK                      (0x03UL << LLWU_PE1_WUPE1_SHIFT)                    /*!< LLWU_PE1: WUPE1 Mask                    */
#define LLWU_PE1_WUPE1_SHIFT                     2                                                   /*!< LLWU_PE1: WUPE1 Position                */
#define LLWU_PE1_WUPE1(x)                        (((x)<<LLWU_PE1_WUPE1_SHIFT)&LLWU_PE1_WUPE1_MASK)   /*!< LLWU_PE1                                */
#define LLWU_PE1_WUPE2_MASK                      (0x03UL << LLWU_PE1_WUPE2_SHIFT)                    /*!< LLWU_PE1: WUPE2 Mask                    */
#define LLWU_PE1_WUPE2_SHIFT                     4                                                   /*!< LLWU_PE1: WUPE2 Position                */
#define LLWU_PE1_WUPE2(x)                        (((x)<<LLWU_PE1_WUPE2_SHIFT)&LLWU_PE1_WUPE2_MASK)   /*!< LLWU_PE1                                */
#define LLWU_PE1_WUPE3_MASK                      (0x03UL << LLWU_PE1_WUPE3_SHIFT)                    /*!< LLWU_PE1: WUPE3 Mask                    */
#define LLWU_PE1_WUPE3_SHIFT                     6                                                   /*!< LLWU_PE1: WUPE3 Position                */
#define LLWU_PE1_WUPE3(x)                        (((x)<<LLWU_PE1_WUPE3_SHIFT)&LLWU_PE1_WUPE3_MASK)   /*!< LLWU_PE1                                */

/* ------- LLWU_PE2                                 ------ */
#define LLWU_PE2_WUPE4_MASK                      (0x03UL << LLWU_PE2_WUPE4_SHIFT)                    /*!< LLWU_PE2: WUPE4 Mask                    */
#define LLWU_PE2_WUPE4_SHIFT                     0                                                   /*!< LLWU_PE2: WUPE4 Position                */
#define LLWU_PE2_WUPE4(x)                        (((x)<<LLWU_PE2_WUPE4_SHIFT)&LLWU_PE2_WUPE4_MASK)   /*!< LLWU_PE2                                */
#define LLWU_PE2_WUPE5_MASK                      (0x03UL << LLWU_PE2_WUPE5_SHIFT)                    /*!< LLWU_PE2: WUPE5 Mask                    */
#define LLWU_PE2_WUPE5_SHIFT                     2                                                   /*!< LLWU_PE2: WUPE5 Position                */
#define LLWU_PE2_WUPE5(x)                        (((x)<<LLWU_PE2_WUPE5_SHIFT)&LLWU_PE2_WUPE5_MASK)   /*!< LLWU_PE2                                */
#define LLWU_PE2_WUPE6_MASK                      (0x03UL << LLWU_PE2_WUPE6_SHIFT)                    /*!< LLWU_PE2: WUPE6 Mask                    */
#define LLWU_PE2_WUPE6_SHIFT                     4                                                   /*!< LLWU_PE2: WUPE6 Position                */
#define LLWU_PE2_WUPE6(x)                        (((x)<<LLWU_PE2_WUPE6_SHIFT)&LLWU_PE2_WUPE6_MASK)   /*!< LLWU_PE2                                */
#define LLWU_PE2_WUPE7_MASK                      (0x03UL << LLWU_PE2_WUPE7_SHIFT)                    /*!< LLWU_PE2: WUPE7 Mask                    */
#define LLWU_PE2_WUPE7_SHIFT                     6                                                   /*!< LLWU_PE2: WUPE7 Position                */
#define LLWU_PE2_WUPE7(x)                        (((x)<<LLWU_PE2_WUPE7_SHIFT)&LLWU_PE2_WUPE7_MASK)   /*!< LLWU_PE2                                */

/* ------- LLWU_PE3                                 ------ */
#define LLWU_PE3_WUPE8_MASK                      (0x03UL << LLWU_PE3_WUPE8_SHIFT)                    /*!< LLWU_PE3: WUPE8 Mask                    */
#define LLWU_PE3_WUPE8_SHIFT                     0                                                   /*!< LLWU_PE3: WUPE8 Position                */
#define LLWU_PE3_WUPE8(x)                        (((x)<<LLWU_PE3_WUPE8_SHIFT)&LLWU_PE3_WUPE8_MASK)   /*!< LLWU_PE3                                */
#define LLWU_PE3_WUPE9_MASK                      (0x03UL << LLWU_PE3_WUPE9_SHIFT)                    /*!< LLWU_PE3: WUPE9 Mask                    */
#define LLWU_PE3_WUPE9_SHIFT                     2                                                   /*!< LLWU_PE3: WUPE9 Position                */
#define LLWU_PE3_WUPE9(x)                        (((x)<<LLWU_PE3_WUPE9_SHIFT)&LLWU_PE3_WUPE9_MASK)   /*!< LLWU_PE3                                */
#define LLWU_PE3_WUPE10_MASK                     (0x03UL << LLWU_PE3_WUPE10_SHIFT)                   /*!< LLWU_PE3: WUPE10 Mask                   */
#define LLWU_PE3_WUPE10_SHIFT                    4                                                   /*!< LLWU_PE3: WUPE10 Position               */
#define LLWU_PE3_WUPE10(x)                       (((x)<<LLWU_PE3_WUPE10_SHIFT)&LLWU_PE3_WUPE10_MASK) /*!< LLWU_PE3                                */
#define LLWU_PE3_WUPE11_MASK                     (0x03UL << LLWU_PE3_WUPE11_SHIFT)                   /*!< LLWU_PE3: WUPE11 Mask                   */
#define LLWU_PE3_WUPE11_SHIFT                    6                                                   /*!< LLWU_PE3: WUPE11 Position               */
#define LLWU_PE3_WUPE11(x)                       (((x)<<LLWU_PE3_WUPE11_SHIFT)&LLWU_PE3_WUPE11_MASK) /*!< LLWU_PE3                                */

/* ------- LLWU_PE4                                 ------ */
#define LLWU_PE4_WUPE12_MASK                     (0x03UL << LLWU_PE4_WUPE12_SHIFT)                   /*!< LLWU_PE4: WUPE12 Mask                   */
#define LLWU_PE4_WUPE12_SHIFT                    0                                                   /*!< LLWU_PE4: WUPE12 Position               */
#define LLWU_PE4_WUPE12(x)                       (((x)<<LLWU_PE4_WUPE12_SHIFT)&LLWU_PE4_WUPE12_MASK) /*!< LLWU_PE4                                */
#define LLWU_PE4_WUPE13_MASK                     (0x03UL << LLWU_PE4_WUPE13_SHIFT)                   /*!< LLWU_PE4: WUPE13 Mask                   */
#define LLWU_PE4_WUPE13_SHIFT                    2                                                   /*!< LLWU_PE4: WUPE13 Position               */
#define LLWU_PE4_WUPE13(x)                       (((x)<<LLWU_PE4_WUPE13_SHIFT)&LLWU_PE4_WUPE13_MASK) /*!< LLWU_PE4                                */
#define LLWU_PE4_WUPE14_MASK                     (0x03UL << LLWU_PE4_WUPE14_SHIFT)                   /*!< LLWU_PE4: WUPE14 Mask                   */
#define LLWU_PE4_WUPE14_SHIFT                    4                                                   /*!< LLWU_PE4: WUPE14 Position               */
#define LLWU_PE4_WUPE14(x)                       (((x)<<LLWU_PE4_WUPE14_SHIFT)&LLWU_PE4_WUPE14_MASK) /*!< LLWU_PE4                                */
#define LLWU_PE4_WUPE15_MASK                     (0x03UL << LLWU_PE4_WUPE15_SHIFT)                   /*!< LLWU_PE4: WUPE15 Mask                   */
#define LLWU_PE4_WUPE15_SHIFT                    6                                                   /*!< LLWU_PE4: WUPE15 Position               */
#define LLWU_PE4_WUPE15(x)                       (((x)<<LLWU_PE4_WUPE15_SHIFT)&LLWU_PE4_WUPE15_MASK) /*!< LLWU_PE4                                */

/* ------- LLWU_ME                                  ------ */
#define LLWU_ME_WUME_MASK                        (0xFFUL << LLWU_ME_WUME_SHIFT)                      /*!< LLWU_ME: WUME Mask                      */
#define LLWU_ME_WUME_SHIFT                       0                                                   /*!< LLWU_ME: WUME Position                  */
#define LLWU_ME_WUME(x)                          (((x)<<LLWU_ME_WUME_SHIFT)&LLWU_ME_WUME_MASK)       /*!< LLWU_ME                                 */

/* ------- LLWU_F1                                  ------ */
#define LLWU_F1_WUF0_MASK                        (0xFFUL << LLWU_F1_WUF0_SHIFT)                      /*!< LLWU_F1: WUF0 Mask                      */
#define LLWU_F1_WUF0_SHIFT                       0                                                   /*!< LLWU_F1: WUF0 Position                  */
#define LLWU_F1_WUF0(x)                          (((x)<<LLWU_F1_WUF0_SHIFT)&LLWU_F1_WUF0_MASK)       /*!< LLWU_F1                                 */

/* ------- LLWU_F2                                  ------ */
#define LLWU_F2_WUFn_MASK                        (0xFFUL << LLWU_F2_WUFn_SHIFT)                      /*!< LLWU_F2: WUFn Mask                      */
#define LLWU_F2_WUFn_SHIFT                       0                                                   /*!< LLWU_F2: WUFn Position                  */
#define LLWU_F2_WUFn(x)                          (((x)<<LLWU_F2_WUFn_SHIFT)&LLWU_F2_WUFn_MASK)       /*!< LLWU_F2                                 */

/* ------- LLWU_F3                                  ------ */
#define LLWU_F3_MWUFn_MASK                       (0xFFUL << LLWU_F3_MWUFn_SHIFT)                     /*!< LLWU_F3: MWUFn Mask                     */
#define LLWU_F3_MWUFn_SHIFT                      0                                                   /*!< LLWU_F3: MWUFn Position                 */
#define LLWU_F3_MWUFn(x)                         (((x)<<LLWU_F3_MWUFn_SHIFT)&LLWU_F3_MWUFn_MASK)     /*!< LLWU_F3                                 */

/* ------- LLWU_FILT                                ------ */
#define LLWU_FILT_FILTSEL_MASK                   (0x0FUL << LLWU_FILT_FILTSEL_SHIFT)                 /*!< LLWU_FILT: FILTSEL Mask                 */
#define LLWU_FILT_FILTSEL_SHIFT                  0                                                   /*!< LLWU_FILT: FILTSEL Position             */
#define LLWU_FILT_FILTSEL(x)                     (((x)<<LLWU_FILT_FILTSEL_SHIFT)&LLWU_FILT_FILTSEL_MASK) /*!< LLWU_FILT                               */
#define LLWU_FILT_FILTE_MASK                     (0x03UL << LLWU_FILT_FILTE_SHIFT)                   /*!< LLWU_FILT: FILTE Mask                   */
#define LLWU_FILT_FILTE_SHIFT                    5                                                   /*!< LLWU_FILT: FILTE Position               */
#define LLWU_FILT_FILTE(x)                       (((x)<<LLWU_FILT_FILTE_SHIFT)&LLWU_FILT_FILTE_MASK) /*!< LLWU_FILT                               */
#define LLWU_FILT_FILTF_MASK                     (0x01UL << LLWU_FILT_FILTF_SHIFT)                   /*!< LLWU_FILT: FILTF Mask                   */
#define LLWU_FILT_FILTF_SHIFT                    7                                                   /*!< LLWU_FILT: FILTF Position               */

/* -------------------------------------------------------------------------------- */
/* -----------     'LLWU' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define LLWU_PE1                       (LLWU->PE1)
#define LLWU_PE2                       (LLWU->PE2)
#define LLWU_PE3                       (LLWU->PE3)
#define LLWU_PE4                       (LLWU->PE4)
#define LLWU_ME                        (LLWU->ME)
#define LLWU_F1                        (LLWU->F1)
#define LLWU_F2                        (LLWU->F2)
#define LLWU_F3                        (LLWU->F3)
#define LLWU_FILT1                     (LLWU->FILT1)
#define LLWU_FILT2                     (LLWU->FILT2)

/* ================================================================================ */
/* ================           LPTMR0 (file:LPTMR0_0)               ================ */
/* ================================================================================ */

/**
 * @brief Low Power Timer
 */
typedef struct {                                /*!<       LPTMR0 Structure                                             */
   __IO uint32_t  CSR;                          /*!< 0000: Control Status Register                                      */
   __IO uint32_t  PSR;                          /*!< 0004: Prescale Register                                            */
   __IO uint32_t  CMR;                          /*!< 0008: Compare Register                                             */
   __I  uint32_t  CNR;                          /*!< 000C: Counter Register                                             */
} LPTMR0_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'LPTMR0' Position & Mask macros                      ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- LPTMR0_CSR                               ------ */
#define LPTMR_CSR_TEN_MASK                       (0x01UL << LPTMR_CSR_TEN_SHIFT)                     /*!< LPTMR0_CSR: TEN Mask                    */
#define LPTMR_CSR_TEN_SHIFT                      0                                                   /*!< LPTMR0_CSR: TEN Position                */
#define LPTMR_CSR_TMS_MASK                       (0x01UL << LPTMR_CSR_TMS_SHIFT)                     /*!< LPTMR0_CSR: TMS Mask                    */
#define LPTMR_CSR_TMS_SHIFT                      1                                                   /*!< LPTMR0_CSR: TMS Position                */
#define LPTMR_CSR_TFC_MASK                       (0x01UL << LPTMR_CSR_TFC_SHIFT)                     /*!< LPTMR0_CSR: TFC Mask                    */
#define LPTMR_CSR_TFC_SHIFT                      2                                                   /*!< LPTMR0_CSR: TFC Position                */
#define LPTMR_CSR_TPP_MASK                       (0x01UL << LPTMR_CSR_TPP_SHIFT)                     /*!< LPTMR0_CSR: TPP Mask                    */
#define LPTMR_CSR_TPP_SHIFT                      3                                                   /*!< LPTMR0_CSR: TPP Position                */
#define LPTMR_CSR_TPS_MASK                       (0x03UL << LPTMR_CSR_TPS_SHIFT)                     /*!< LPTMR0_CSR: TPS Mask                    */
#define LPTMR_CSR_TPS_SHIFT                      4                                                   /*!< LPTMR0_CSR: TPS Position                */
#define LPTMR_CSR_TPS(x)                         (((x)<<LPTMR_CSR_TPS_SHIFT)&LPTMR_CSR_TPS_MASK)     /*!< LPTMR0_CSR                              */
#define LPTMR_CSR_TIE_MASK                       (0x01UL << LPTMR_CSR_TIE_SHIFT)                     /*!< LPTMR0_CSR: TIE Mask                    */
#define LPTMR_CSR_TIE_SHIFT                      6                                                   /*!< LPTMR0_CSR: TIE Position                */
#define LPTMR_CSR_TCF_MASK                       (0x01UL << LPTMR_CSR_TCF_SHIFT)                     /*!< LPTMR0_CSR: TCF Mask                    */
#define LPTMR_CSR_TCF_SHIFT                      7                                                   /*!< LPTMR0_CSR: TCF Position                */

/* ------- LPTMR0_PSR                               ------ */
#define LPTMR_PSR_PCS_MASK                       (0x03UL << LPTMR_PSR_PCS_SHIFT)                     /*!< LPTMR0_PSR: PCS Mask                    */
#define LPTMR_PSR_PCS_SHIFT                      0                                                   /*!< LPTMR0_PSR: PCS Position                */
#define LPTMR_PSR_PCS(x)                         (((x)<<LPTMR_PSR_PCS_SHIFT)&LPTMR_PSR_PCS_MASK)     /*!< LPTMR0_PSR                              */
#define LPTMR_PSR_PBYP_MASK                      (0x01UL << LPTMR_PSR_PBYP_SHIFT)                    /*!< LPTMR0_PSR: PBYP Mask                   */
#define LPTMR_PSR_PBYP_SHIFT                     2                                                   /*!< LPTMR0_PSR: PBYP Position               */
#define LPTMR_PSR_PRESCALE_MASK                  (0x0FUL << LPTMR_PSR_PRESCALE_SHIFT)                /*!< LPTMR0_PSR: PRESCALE Mask               */
#define LPTMR_PSR_PRESCALE_SHIFT                 3                                                   /*!< LPTMR0_PSR: PRESCALE Position           */
#define LPTMR_PSR_PRESCALE(x)                    (((x)<<LPTMR_PSR_PRESCALE_SHIFT)&LPTMR_PSR_PRESCALE_MASK) /*!< LPTMR0_PSR                              */

/* ------- LPTMR0_CMR                               ------ */
#define LPTMR_CMR_COMPARE_MASK                   (0xFFFFUL << LPTMR_CMR_COMPARE_SHIFT)               /*!< LPTMR0_CMR: COMPARE Mask                */
#define LPTMR_CMR_COMPARE_SHIFT                  0                                                   /*!< LPTMR0_CMR: COMPARE Position            */
#define LPTMR_CMR_COMPARE(x)                     (((x)<<LPTMR_CMR_COMPARE_SHIFT)&LPTMR_CMR_COMPARE_MASK) /*!< LPTMR0_CMR                              */

/* ------- LPTMR0_CNR                               ------ */
#define LPTMR_CNR_COUNTER_MASK                   (0xFFFFUL << LPTMR_CNR_COUNTER_SHIFT)               /*!< LPTMR0_CNR: COUNTER Mask                */
#define LPTMR_CNR_COUNTER_SHIFT                  0                                                   /*!< LPTMR0_CNR: COUNTER Position            */
#define LPTMR_CNR_COUNTER(x)                     (((x)<<LPTMR_CNR_COUNTER_SHIFT)&LPTMR_CNR_COUNTER_MASK) /*!< LPTMR0_CNR                              */

/* -------------------------------------------------------------------------------- */
/* -----------     'LPTMR0' Register Access macros                      ----------- */
/* -------------------------------------------------------------------------------- */

#define LPTMR0_CSR                     (LPTMR0->CSR)
#define LPTMR0_PSR                     (LPTMR0->PSR)
#define LPTMR0_CMR                     (LPTMR0->CMR)
#define LPTMR0_CNR                     (LPTMR0->CNR)

/* ================================================================================ */
/* ================           LPUART0 (file:LPUART0_MKLx3)         ================ */
/* ================================================================================ */

/**
 * @brief Low Power Universal Asynchronous Receiver/Transmitter
 */
typedef struct {                                /*!<       LPUART0 Structure                                            */
   __IO uint32_t  BAUD;                         /*!< 0000: Baud Rate Register                                           */
   __IO uint32_t  STAT;                         /*!< 0004: Status Register                                              */
   __IO uint32_t  CTRL;                         /*!< 0008: Control Register                                             */
   __IO uint32_t  DATA;                         /*!< 000C: Data Register                                                */
   __IO uint32_t  MATCH;                        /*!< 0010: Match Address Register                                       */
} LPUART0_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'LPUART0' Position & Mask macros                     ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- LPUART0_BAUD                             ------ */
#define LPUART_BAUD_SBR_MASK                     (0x1FFFUL << LPUART_BAUD_SBR_SHIFT)                 /*!< LPUART0_BAUD: SBR Mask                  */
#define LPUART_BAUD_SBR_SHIFT                    0                                                   /*!< LPUART0_BAUD: SBR Position              */
#define LPUART_BAUD_SBR(x)                       (((x)<<LPUART_BAUD_SBR_SHIFT)&LPUART_BAUD_SBR_MASK) /*!< LPUART0_BAUD                            */
#define LPUART_BAUD_SBNS_MASK                    (0x01UL << LPUART_BAUD_SBNS_SHIFT)                  /*!< LPUART0_BAUD: SBNS Mask                 */
#define LPUART_BAUD_SBNS_SHIFT                   13                                                  /*!< LPUART0_BAUD: SBNS Position             */
#define LPUART_BAUD_RXEDGIE_MASK                 (0x01UL << LPUART_BAUD_RXEDGIE_SHIFT)               /*!< LPUART0_BAUD: RXEDGIE Mask              */
#define LPUART_BAUD_RXEDGIE_SHIFT                14                                                  /*!< LPUART0_BAUD: RXEDGIE Position          */
#define LPUART_BAUD_LBKDIE_MASK                  (0x01UL << LPUART_BAUD_LBKDIE_SHIFT)                /*!< LPUART0_BAUD: LBKDIE Mask               */
#define LPUART_BAUD_LBKDIE_SHIFT                 15                                                  /*!< LPUART0_BAUD: LBKDIE Position           */
#define LPUART_BAUD_RESYNCDIS_MASK               (0x01UL << LPUART_BAUD_RESYNCDIS_SHIFT)             /*!< LPUART0_BAUD: RESYNCDIS Mask            */
#define LPUART_BAUD_RESYNCDIS_SHIFT              16                                                  /*!< LPUART0_BAUD: RESYNCDIS Position        */
#define LPUART_BAUD_BOTHEDGE_MASK                (0x01UL << LPUART_BAUD_BOTHEDGE_SHIFT)              /*!< LPUART0_BAUD: BOTHEDGE Mask             */
#define LPUART_BAUD_BOTHEDGE_SHIFT               17                                                  /*!< LPUART0_BAUD: BOTHEDGE Position         */
#define LPUART_BAUD_MATCFG_MASK                  (0x03UL << LPUART_BAUD_MATCFG_SHIFT)                /*!< LPUART0_BAUD: MATCFG Mask               */
#define LPUART_BAUD_MATCFG_SHIFT                 18                                                  /*!< LPUART0_BAUD: MATCFG Position           */
#define LPUART_BAUD_MATCFG(x)                    (((x)<<LPUART_BAUD_MATCFG_SHIFT)&LPUART_BAUD_MATCFG_MASK) /*!< LPUART0_BAUD                            */
#define LPUART_BAUD_RDMAE_MASK                   (0x01UL << LPUART_BAUD_RDMAE_SHIFT)                 /*!< LPUART0_BAUD: RDMAE Mask                */
#define LPUART_BAUD_RDMAE_SHIFT                  21                                                  /*!< LPUART0_BAUD: RDMAE Position            */
#define LPUART_BAUD_TDMAE_MASK                   (0x01UL << LPUART_BAUD_TDMAE_SHIFT)                 /*!< LPUART0_BAUD: TDMAE Mask                */
#define LPUART_BAUD_TDMAE_SHIFT                  23                                                  /*!< LPUART0_BAUD: TDMAE Position            */
#define LPUART_BAUD_OSR_MASK                     (0x1FUL << LPUART_BAUD_OSR_SHIFT)                   /*!< LPUART0_BAUD: OSR Mask                  */
#define LPUART_BAUD_OSR_SHIFT                    24                                                  /*!< LPUART0_BAUD: OSR Position              */
#define LPUART_BAUD_OSR(x)                       (((x)<<LPUART_BAUD_OSR_SHIFT)&LPUART_BAUD_OSR_MASK) /*!< LPUART0_BAUD                            */
#define LPUART_BAUD_M10_MASK                     (0x01UL << LPUART_BAUD_M10_SHIFT)                   /*!< LPUART0_BAUD: M10 Mask                  */
#define LPUART_BAUD_M10_SHIFT                    29                                                  /*!< LPUART0_BAUD: M10 Position              */
#define LPUART_BAUD_MAEN2_MASK                   (0x01UL << LPUART_BAUD_MAEN2_SHIFT)                 /*!< LPUART0_BAUD: MAEN2 Mask                */
#define LPUART_BAUD_MAEN2_SHIFT                  30                                                  /*!< LPUART0_BAUD: MAEN2 Position            */
#define LPUART_BAUD_MAEN1_MASK                   (0x01UL << LPUART_BAUD_MAEN1_SHIFT)                 /*!< LPUART0_BAUD: MAEN1 Mask                */
#define LPUART_BAUD_MAEN1_SHIFT                  31                                                  /*!< LPUART0_BAUD: MAEN1 Position            */

/* ------- LPUART0_STAT                             ------ */
#define LPUART_STAT_MA2F_MASK                    (0x01UL << LPUART_STAT_MA2F_SHIFT)                  /*!< LPUART0_STAT: MA2F Mask                 */
#define LPUART_STAT_MA2F_SHIFT                   14                                                  /*!< LPUART0_STAT: MA2F Position             */
#define LPUART_STAT_MA1F_MASK                    (0x01UL << LPUART_STAT_MA1F_SHIFT)                  /*!< LPUART0_STAT: MA1F Mask                 */
#define LPUART_STAT_MA1F_SHIFT                   15                                                  /*!< LPUART0_STAT: MA1F Position             */
#define LPUART_STAT_PF_MASK                      (0x01UL << LPUART_STAT_PF_SHIFT)                    /*!< LPUART0_STAT: PF Mask                   */
#define LPUART_STAT_PF_SHIFT                     16                                                  /*!< LPUART0_STAT: PF Position               */
#define LPUART_STAT_FE_MASK                      (0x01UL << LPUART_STAT_FE_SHIFT)                    /*!< LPUART0_STAT: FE Mask                   */
#define LPUART_STAT_FE_SHIFT                     17                                                  /*!< LPUART0_STAT: FE Position               */
#define LPUART_STAT_NF_MASK                      (0x01UL << LPUART_STAT_NF_SHIFT)                    /*!< LPUART0_STAT: NF Mask                   */
#define LPUART_STAT_NF_SHIFT                     18                                                  /*!< LPUART0_STAT: NF Position               */
#define LPUART_STAT_OR_MASK                      (0x01UL << LPUART_STAT_OR_SHIFT)                    /*!< LPUART0_STAT: OR Mask                   */
#define LPUART_STAT_OR_SHIFT                     19                                                  /*!< LPUART0_STAT: OR Position               */
#define LPUART_STAT_IDLE_MASK                    (0x01UL << LPUART_STAT_IDLE_SHIFT)                  /*!< LPUART0_STAT: IDLE Mask                 */
#define LPUART_STAT_IDLE_SHIFT                   20                                                  /*!< LPUART0_STAT: IDLE Position             */
#define LPUART_STAT_RDRF_MASK                    (0x01UL << LPUART_STAT_RDRF_SHIFT)                  /*!< LPUART0_STAT: RDRF Mask                 */
#define LPUART_STAT_RDRF_SHIFT                   21                                                  /*!< LPUART0_STAT: RDRF Position             */
#define LPUART_STAT_TC_MASK                      (0x01UL << LPUART_STAT_TC_SHIFT)                    /*!< LPUART0_STAT: TC Mask                   */
#define LPUART_STAT_TC_SHIFT                     22                                                  /*!< LPUART0_STAT: TC Position               */
#define LPUART_STAT_TDRE_MASK                    (0x01UL << LPUART_STAT_TDRE_SHIFT)                  /*!< LPUART0_STAT: TDRE Mask                 */
#define LPUART_STAT_TDRE_SHIFT                   23                                                  /*!< LPUART0_STAT: TDRE Position             */
#define LPUART_STAT_RAF_MASK                     (0x01UL << LPUART_STAT_RAF_SHIFT)                   /*!< LPUART0_STAT: RAF Mask                  */
#define LPUART_STAT_RAF_SHIFT                    24                                                  /*!< LPUART0_STAT: RAF Position              */
#define LPUART_STAT_LBKDE_MASK                   (0x01UL << LPUART_STAT_LBKDE_SHIFT)                 /*!< LPUART0_STAT: LBKDE Mask                */
#define LPUART_STAT_LBKDE_SHIFT                  25                                                  /*!< LPUART0_STAT: LBKDE Position            */
#define LPUART_STAT_BRK13_MASK                   (0x01UL << LPUART_STAT_BRK13_SHIFT)                 /*!< LPUART0_STAT: BRK13 Mask                */
#define LPUART_STAT_BRK13_SHIFT                  26                                                  /*!< LPUART0_STAT: BRK13 Position            */
#define LPUART_STAT_RWUID_MASK                   (0x01UL << LPUART_STAT_RWUID_SHIFT)                 /*!< LPUART0_STAT: RWUID Mask                */
#define LPUART_STAT_RWUID_SHIFT                  27                                                  /*!< LPUART0_STAT: RWUID Position            */
#define LPUART_STAT_RXINV_MASK                   (0x01UL << LPUART_STAT_RXINV_SHIFT)                 /*!< LPUART0_STAT: RXINV Mask                */
#define LPUART_STAT_RXINV_SHIFT                  28                                                  /*!< LPUART0_STAT: RXINV Position            */
#define LPUART_STAT_MSBF_MASK                    (0x01UL << LPUART_STAT_MSBF_SHIFT)                  /*!< LPUART0_STAT: MSBF Mask                 */
#define LPUART_STAT_MSBF_SHIFT                   29                                                  /*!< LPUART0_STAT: MSBF Position             */
#define LPUART_STAT_RXEDGIF_MASK                 (0x01UL << LPUART_STAT_RXEDGIF_SHIFT)               /*!< LPUART0_STAT: RXEDGIF Mask              */
#define LPUART_STAT_RXEDGIF_SHIFT                30                                                  /*!< LPUART0_STAT: RXEDGIF Position          */
#define LPUART_STAT_LBKDIF_MASK                  (0x01UL << LPUART_STAT_LBKDIF_SHIFT)                /*!< LPUART0_STAT: LBKDIF Mask               */
#define LPUART_STAT_LBKDIF_SHIFT                 31                                                  /*!< LPUART0_STAT: LBKDIF Position           */

/* ------- LPUART0_CTRL                             ------ */
#define LPUART_CTRL_PT_MASK                      (0x01UL << LPUART_CTRL_PT_SHIFT)                    /*!< LPUART0_CTRL: PT Mask                   */
#define LPUART_CTRL_PT_SHIFT                     0                                                   /*!< LPUART0_CTRL: PT Position               */
#define LPUART_CTRL_PE_MASK                      (0x01UL << LPUART_CTRL_PE_SHIFT)                    /*!< LPUART0_CTRL: PE Mask                   */
#define LPUART_CTRL_PE_SHIFT                     1                                                   /*!< LPUART0_CTRL: PE Position               */
#define LPUART_CTRL_ILT_MASK                     (0x01UL << LPUART_CTRL_ILT_SHIFT)                   /*!< LPUART0_CTRL: ILT Mask                  */
#define LPUART_CTRL_ILT_SHIFT                    2                                                   /*!< LPUART0_CTRL: ILT Position              */
#define LPUART_CTRL_WAKE_MASK                    (0x01UL << LPUART_CTRL_WAKE_SHIFT)                  /*!< LPUART0_CTRL: WAKE Mask                 */
#define LPUART_CTRL_WAKE_SHIFT                   3                                                   /*!< LPUART0_CTRL: WAKE Position             */
#define LPUART_CTRL_M_MASK                       (0x01UL << LPUART_CTRL_M_SHIFT)                     /*!< LPUART0_CTRL: M Mask                    */
#define LPUART_CTRL_M_SHIFT                      4                                                   /*!< LPUART0_CTRL: M Position                */
#define LPUART_CTRL_RSRC_MASK                    (0x01UL << LPUART_CTRL_RSRC_SHIFT)                  /*!< LPUART0_CTRL: RSRC Mask                 */
#define LPUART_CTRL_RSRC_SHIFT                   5                                                   /*!< LPUART0_CTRL: RSRC Position             */
#define LPUART_CTRL_DOZEEN_MASK                  (0x01UL << LPUART_CTRL_DOZEEN_SHIFT)                /*!< LPUART0_CTRL: DOZEEN Mask               */
#define LPUART_CTRL_DOZEEN_SHIFT                 6                                                   /*!< LPUART0_CTRL: DOZEEN Position           */
#define LPUART_CTRL_LOOPS_MASK                   (0x01UL << LPUART_CTRL_LOOPS_SHIFT)                 /*!< LPUART0_CTRL: LOOPS Mask                */
#define LPUART_CTRL_LOOPS_SHIFT                  7                                                   /*!< LPUART0_CTRL: LOOPS Position            */
#define LPUART_CTRL_MA2IE_MASK                   (0x01UL << LPUART_CTRL_MA2IE_SHIFT)                 /*!< LPUART0_CTRL: MA2IE Mask                */
#define LPUART_CTRL_MA2IE_SHIFT                  14                                                  /*!< LPUART0_CTRL: MA2IE Position            */
#define LPUART_CTRL_MA1IE_MASK                   (0x01UL << LPUART_CTRL_MA1IE_SHIFT)                 /*!< LPUART0_CTRL: MA1IE Mask                */
#define LPUART_CTRL_MA1IE_SHIFT                  15                                                  /*!< LPUART0_CTRL: MA1IE Position            */
#define LPUART_CTRL_SBK_MASK                     (0x01UL << LPUART_CTRL_SBK_SHIFT)                   /*!< LPUART0_CTRL: SBK Mask                  */
#define LPUART_CTRL_SBK_SHIFT                    16                                                  /*!< LPUART0_CTRL: SBK Position              */
#define LPUART_CTRL_RWU_MASK                     (0x01UL << LPUART_CTRL_RWU_SHIFT)                   /*!< LPUART0_CTRL: RWU Mask                  */
#define LPUART_CTRL_RWU_SHIFT                    17                                                  /*!< LPUART0_CTRL: RWU Position              */
#define LPUART_CTRL_RE_MASK                      (0x01UL << LPUART_CTRL_RE_SHIFT)                    /*!< LPUART0_CTRL: RE Mask                   */
#define LPUART_CTRL_RE_SHIFT                     18                                                  /*!< LPUART0_CTRL: RE Position               */
#define LPUART_CTRL_TE_MASK                      (0x01UL << LPUART_CTRL_TE_SHIFT)                    /*!< LPUART0_CTRL: TE Mask                   */
#define LPUART_CTRL_TE_SHIFT                     19                                                  /*!< LPUART0_CTRL: TE Position               */
#define LPUART_CTRL_ILIE_MASK                    (0x01UL << LPUART_CTRL_ILIE_SHIFT)                  /*!< LPUART0_CTRL: ILIE Mask                 */
#define LPUART_CTRL_ILIE_SHIFT                   20                                                  /*!< LPUART0_CTRL: ILIE Position             */
#define LPUART_CTRL_RIE_MASK                     (0x01UL << LPUART_CTRL_RIE_SHIFT)                   /*!< LPUART0_CTRL: RIE Mask                  */
#define LPUART_CTRL_RIE_SHIFT                    21                                                  /*!< LPUART0_CTRL: RIE Position              */
#define LPUART_CTRL_TCIE_MASK                    (0x01UL << LPUART_CTRL_TCIE_SHIFT)                  /*!< LPUART0_CTRL: TCIE Mask                 */
#define LPUART_CTRL_TCIE_SHIFT                   22                                                  /*!< LPUART0_CTRL: TCIE Position             */
#define LPUART_CTRL_TIE_MASK                     (0x01UL << LPUART_CTRL_TIE_SHIFT)                   /*!< LPUART0_CTRL: TIE Mask                  */
#define LPUART_CTRL_TIE_SHIFT                    23                                                  /*!< LPUART0_CTRL: TIE Position              */
#define LPUART_CTRL_PEIE_MASK                    (0x01UL << LPUART_CTRL_PEIE_SHIFT)                  /*!< LPUART0_CTRL: PEIE Mask                 */
#define LPUART_CTRL_PEIE_SHIFT                   24                                                  /*!< LPUART0_CTRL: PEIE Position             */
#define LPUART_CTRL_FEIE_MASK                    (0x01UL << LPUART_CTRL_FEIE_SHIFT)                  /*!< LPUART0_CTRL: FEIE Mask                 */
#define LPUART_CTRL_FEIE_SHIFT                   25                                                  /*!< LPUART0_CTRL: FEIE Position             */
#define LPUART_CTRL_NEIE_MASK                    (0x01UL << LPUART_CTRL_NEIE_SHIFT)                  /*!< LPUART0_CTRL: NEIE Mask                 */
#define LPUART_CTRL_NEIE_SHIFT                   26                                                  /*!< LPUART0_CTRL: NEIE Position             */
#define LPUART_CTRL_ORIE_MASK                    (0x01UL << LPUART_CTRL_ORIE_SHIFT)                  /*!< LPUART0_CTRL: ORIE Mask                 */
#define LPUART_CTRL_ORIE_SHIFT                   27                                                  /*!< LPUART0_CTRL: ORIE Position             */
#define LPUART_CTRL_TXINV_MASK                   (0x01UL << LPUART_CTRL_TXINV_SHIFT)                 /*!< LPUART0_CTRL: TXINV Mask                */
#define LPUART_CTRL_TXINV_SHIFT                  28                                                  /*!< LPUART0_CTRL: TXINV Position            */
#define LPUART_CTRL_TXDIR_MASK                   (0x01UL << LPUART_CTRL_TXDIR_SHIFT)                 /*!< LPUART0_CTRL: TXDIR Mask                */
#define LPUART_CTRL_TXDIR_SHIFT                  29                                                  /*!< LPUART0_CTRL: TXDIR Position            */
#define LPUART_CTRL_R9T8_MASK                    (0x01UL << LPUART_CTRL_R9T8_SHIFT)                  /*!< LPUART0_CTRL: R9T8 Mask                 */
#define LPUART_CTRL_R9T8_SHIFT                   30                                                  /*!< LPUART0_CTRL: R9T8 Position             */
#define LPUART_CTRL_R8T9_MASK                    (0x01UL << LPUART_CTRL_R8T9_SHIFT)                  /*!< LPUART0_CTRL: R8T9 Mask                 */
#define LPUART_CTRL_R8T9_SHIFT                   31                                                  /*!< LPUART0_CTRL: R8T9 Position             */

/* ------- LPUART0_DATA                             ------ */
#define LPUART_DATA_RT_MASK                      (0x3FFUL << LPUART_DATA_RT_SHIFT)                   /*!< LPUART0_DATA: RT Mask                   */
#define LPUART_DATA_RT_SHIFT                     0                                                   /*!< LPUART0_DATA: RT Position               */
#define LPUART_DATA_RT(x)                        (((x)<<LPUART_DATA_RT_SHIFT)&LPUART_DATA_RT_MASK)   /*!< LPUART0_DATA                            */
#define LPUART_DATA_IDLINE_MASK                  (0x01UL << LPUART_DATA_IDLINE_SHIFT)                /*!< LPUART0_DATA: IDLINE Mask               */
#define LPUART_DATA_IDLINE_SHIFT                 11                                                  /*!< LPUART0_DATA: IDLINE Position           */
#define LPUART_DATA_RXEMPT_MASK                  (0x01UL << LPUART_DATA_RXEMPT_SHIFT)                /*!< LPUART0_DATA: RXEMPT Mask               */
#define LPUART_DATA_RXEMPT_SHIFT                 12                                                  /*!< LPUART0_DATA: RXEMPT Position           */
#define LPUART_DATA_FRETSC_MASK                  (0x01UL << LPUART_DATA_FRETSC_SHIFT)                /*!< LPUART0_DATA: FRETSC Mask               */
#define LPUART_DATA_FRETSC_SHIFT                 13                                                  /*!< LPUART0_DATA: FRETSC Position           */
#define LPUART_DATA_PARITYE_MASK                 (0x01UL << LPUART_DATA_PARITYE_SHIFT)               /*!< LPUART0_DATA: PARITYE Mask              */
#define LPUART_DATA_PARITYE_SHIFT                14                                                  /*!< LPUART0_DATA: PARITYE Position          */
#define LPUART_DATA_NOISY_MASK                   (0x01UL << LPUART_DATA_NOISY_SHIFT)                 /*!< LPUART0_DATA: NOISY Mask                */
#define LPUART_DATA_NOISY_SHIFT                  15                                                  /*!< LPUART0_DATA: NOISY Position            */

/* ------- LPUART0_MATCH                            ------ */
#define LPUART_MATCH_MA1_MASK                    (0x3FFUL << LPUART_MATCH_MA1_SHIFT)                 /*!< LPUART0_MATCH: MA1 Mask                 */
#define LPUART_MATCH_MA1_SHIFT                   0                                                   /*!< LPUART0_MATCH: MA1 Position             */
#define LPUART_MATCH_MA1(x)                      (((x)<<LPUART_MATCH_MA1_SHIFT)&LPUART_MATCH_MA1_MASK) /*!< LPUART0_MATCH                           */
#define LPUART_MATCH_MA2_MASK                    (0x3FFUL << LPUART_MATCH_MA2_SHIFT)                 /*!< LPUART0_MATCH: MA2 Mask                 */
#define LPUART_MATCH_MA2_SHIFT                   16                                                  /*!< LPUART0_MATCH: MA2 Position             */
#define LPUART_MATCH_MA2(x)                      (((x)<<LPUART_MATCH_MA2_SHIFT)&LPUART_MATCH_MA2_MASK) /*!< LPUART0_MATCH                           */

/* -------------------------------------------------------------------------------- */
/* -----------     'LPUART0' Register Access macros                     ----------- */
/* -------------------------------------------------------------------------------- */

#define LPUART0_BAUD                   (LPUART0->BAUD)
#define LPUART0_STAT                   (LPUART0->STAT)
#define LPUART0_CTRL                   (LPUART0->CTRL)
#define LPUART0_DATA                   (LPUART0->DATA)
#define LPUART0_MATCH                  (LPUART0->MATCH)

/* ================================================================================ */
/* ================           LPUART1 (derived from LPUART0)       ================ */
/* ================================================================================ */

/**
 * @brief Low Power Universal Asynchronous Receiver/Transmitter
 */
typedef LPUART0_Type LPUART1_Type;  /*!< LPUART1 Structure                                           */


/* -------------------------------------------------------------------------------- */
/* -----------     'LPUART1' Register Access macros                     ----------- */
/* -------------------------------------------------------------------------------- */

#define LPUART1_BAUD                   (LPUART1->BAUD)
#define LPUART1_STAT                   (LPUART1->STAT)
#define LPUART1_CTRL                   (LPUART1->CTRL)
#define LPUART1_DATA                   (LPUART1->DATA)
#define LPUART1_MATCH                  (LPUART1->MATCH)

/* ================================================================================ */
/* ================           MCG (file:MCG_LITE)                  ================ */
/* ================================================================================ */

/**
 * @brief Multipurpose Clock Generator Light module
 */
typedef struct {                                /*!<       MCG Structure                                                */
   __IO uint8_t   C1;                           /*!< 0000: Control 1 Register                                           */
   __IO uint8_t   C2;                           /*!< 0001: Control 2 Register                                           */
   __I  uint16_t  RESERVED0[2];                 /*!< 0002:                                                              */
   __I  uint8_t   S;                            /*!< 0006: Status Register                                              */
   __I  uint8_t   RESERVED1;                    /*!< 0007:                                                              */
   __IO uint8_t   SC;                           /*!< 0008: Status and Control Register                                  */
   __I  uint8_t   RESERVED2[15];                /*!< 0009:                                                              */
   __IO uint8_t   MC;                           /*!< 0018: MCG Miscellaneous Control Register                           */
} MCG_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'MCG' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- MCG_C1                                   ------ */
#define MCG_C1_IREFSTEN_MASK                     (0x01UL << MCG_C1_IREFSTEN_SHIFT)                   /*!< MCG_C1: IREFSTEN Mask                   */
#define MCG_C1_IREFSTEN_SHIFT                    0                                                   /*!< MCG_C1: IREFSTEN Position               */
#define MCG_C1_IRCLKEN_MASK                      (0x01UL << MCG_C1_IRCLKEN_SHIFT)                    /*!< MCG_C1: IRCLKEN Mask                    */
#define MCG_C1_IRCLKEN_SHIFT                     1                                                   /*!< MCG_C1: IRCLKEN Position                */
#define MCG_C1_CLKS_MASK                         (0x03UL << MCG_C1_CLKS_SHIFT)                       /*!< MCG_C1: CLKS Mask                       */
#define MCG_C1_CLKS_SHIFT                        6                                                   /*!< MCG_C1: CLKS Position                   */
#define MCG_C1_CLKS(x)                           (((x)<<MCG_C1_CLKS_SHIFT)&MCG_C1_CLKS_MASK)         /*!< MCG_C1                                  */

/* ------- MCG_C2                                   ------ */
#define MCG_C2_IRCS_MASK                         (0x01UL << MCG_C2_IRCS_SHIFT)                       /*!< MCG_C2: IRCS Mask                       */
#define MCG_C2_IRCS_SHIFT                        0                                                   /*!< MCG_C2: IRCS Position                   */
#define MCG_C2_EREFS0_MASK                       (0x01UL << MCG_C2_EREFS0_SHIFT)                     /*!< MCG_C2: EREFS0 Mask                     */
#define MCG_C2_EREFS0_SHIFT                      2                                                   /*!< MCG_C2: EREFS0 Position                 */
#define MCG_C2_HGO0_MASK                         (0x01UL << MCG_C2_HGO0_SHIFT)                       /*!< MCG_C2: HGO0 Mask                       */
#define MCG_C2_HGO0_SHIFT                        3                                                   /*!< MCG_C2: HGO0 Position                   */
#define MCG_C2_RANGE0_MASK                       (0x03UL << MCG_C2_RANGE0_SHIFT)                     /*!< MCG_C2: RANGE0 Mask                     */
#define MCG_C2_RANGE0_SHIFT                      4                                                   /*!< MCG_C2: RANGE0 Position                 */
#define MCG_C2_RANGE0(x)                         (((x)<<MCG_C2_RANGE0_SHIFT)&MCG_C2_RANGE0_MASK)     /*!< MCG_C2                                  */

/* ------- MCG_S                                    ------ */
#define MCG_S_OSCINIT0_MASK                      (0x01UL << MCG_S_OSCINIT0_SHIFT)                    /*!< MCG_S: OSCINIT0 Mask                    */
#define MCG_S_OSCINIT0_SHIFT                     1                                                   /*!< MCG_S: OSCINIT0 Position                */
#define MCG_S_CLKST_MASK                         (0x03UL << MCG_S_CLKST_SHIFT)                       /*!< MCG_S: CLKST Mask                       */
#define MCG_S_CLKST_SHIFT                        2                                                   /*!< MCG_S: CLKST Position                   */
#define MCG_S_CLKST(x)                           (((x)<<MCG_S_CLKST_SHIFT)&MCG_S_CLKST_MASK)         /*!< MCG_S                                   */

/* ------- MCG_SC                                   ------ */
#define MCG_SC_FCRDIV_MASK                       (0x07UL << MCG_SC_FCRDIV_SHIFT)                     /*!< MCG_SC: FCRDIV Mask                     */
#define MCG_SC_FCRDIV_SHIFT                      1                                                   /*!< MCG_SC: FCRDIV Position                 */
#define MCG_SC_FCRDIV(x)                         (((x)<<MCG_SC_FCRDIV_SHIFT)&MCG_SC_FCRDIV_MASK)     /*!< MCG_SC                                  */

/* ------- MCG_MC                                   ------ */
#define MCG_MC_LIRC_DIV2_MASK                    (0x07UL << MCG_MC_LIRC_DIV2_SHIFT)                  /*!< MCG_MC: LIRC_DIV2 Mask                  */
#define MCG_MC_LIRC_DIV2_SHIFT                   0                                                   /*!< MCG_MC: LIRC_DIV2 Position              */
#define MCG_MC_LIRC_DIV2(x)                      (((x)<<MCG_MC_LIRC_DIV2_SHIFT)&MCG_MC_LIRC_DIV2_MASK) /*!< MCG_MC                                  */
#define MCG_MC_HIRCEN_MASK                       (0x01UL << MCG_MC_HIRCEN_SHIFT)                     /*!< MCG_MC: HIRCEN Mask                     */
#define MCG_MC_HIRCEN_SHIFT                      7                                                   /*!< MCG_MC: HIRCEN Position                 */

/* -------------------------------------------------------------------------------- */
/* -----------     'MCG' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define MCG_C1                         (MCG->C1)
#define MCG_C2                         (MCG->C2)
#define MCG_S                          (MCG->S)
#define MCG_SC                         (MCG->SC)
#define MCG_MC                         (MCG->MC)

/* ================================================================================ */
/* ================           MCM (file:MCM_MKL)                   ================ */
/* ================================================================================ */

/**
 * @brief Core Platform Miscellaneous Control Module
 */
typedef struct {                                /*!<       MCM Structure                                                */
   __I  uint32_t  RESERVED0[2];                 /*!< 0000:                                                              */
   __I  uint16_t  PLASC;                        /*!< 0008: Crossbar Switch (AXBS) Slave Configuration                   */
   __I  uint16_t  PLAMC;                        /*!< 000A: Crossbar Switch (AXBS) Master Configuration                  */
   __IO uint32_t  PLACR;                        /*!< 000C: Platform Control Register                                    */
   __I  uint32_t  RESERVED1[12];                /*!< 0010:                                                              */
   __IO uint32_t  CPO;                          /*!< 0040: Compute Operation Control Register                           */
} MCM_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'MCM' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- MCM_PLASC                                ------ */
#define MCM_PLASC_ASC_MASK                       (0xFFUL << MCM_PLASC_ASC_SHIFT)                     /*!< MCM_PLASC: ASC Mask                     */
#define MCM_PLASC_ASC_SHIFT                      0                                                   /*!< MCM_PLASC: ASC Position                 */
#define MCM_PLASC_ASC(x)                         (((x)<<MCM_PLASC_ASC_SHIFT)&MCM_PLASC_ASC_MASK)     /*!< MCM_PLASC                               */

/* ------- MCM_PLAMC                                ------ */
#define MCM_PLAMC_AMC_MASK                       (0xFFUL << MCM_PLAMC_AMC_SHIFT)                     /*!< MCM_PLAMC: AMC Mask                     */
#define MCM_PLAMC_AMC_SHIFT                      0                                                   /*!< MCM_PLAMC: AMC Position                 */
#define MCM_PLAMC_AMC(x)                         (((x)<<MCM_PLAMC_AMC_SHIFT)&MCM_PLAMC_AMC_MASK)     /*!< MCM_PLAMC                               */

/* ------- MCM_PLACR                                ------ */
#define MCM_PLACR_ARB_MASK                       (0x01UL << MCM_PLACR_ARB_SHIFT)                     /*!< MCM_PLACR: ARB Mask                     */
#define MCM_PLACR_ARB_SHIFT                      9                                                   /*!< MCM_PLACR: ARB Position                 */
#define MCM_PLACR_CFCC_MASK                      (0x01UL << MCM_PLACR_CFCC_SHIFT)                    /*!< MCM_PLACR: CFCC Mask                    */
#define MCM_PLACR_CFCC_SHIFT                     10                                                  /*!< MCM_PLACR: CFCC Position                */
#define MCM_PLACR_DFCDA_MASK                     (0x01UL << MCM_PLACR_DFCDA_SHIFT)                   /*!< MCM_PLACR: DFCDA Mask                   */
#define MCM_PLACR_DFCDA_SHIFT                    11                                                  /*!< MCM_PLACR: DFCDA Position               */
#define MCM_PLACR_DFCIC_MASK                     (0x01UL << MCM_PLACR_DFCIC_SHIFT)                   /*!< MCM_PLACR: DFCIC Mask                   */
#define MCM_PLACR_DFCIC_SHIFT                    12                                                  /*!< MCM_PLACR: DFCIC Position               */
#define MCM_PLACR_DFCC_MASK                      (0x01UL << MCM_PLACR_DFCC_SHIFT)                    /*!< MCM_PLACR: DFCC Mask                    */
#define MCM_PLACR_DFCC_SHIFT                     13                                                  /*!< MCM_PLACR: DFCC Position                */
#define MCM_PLACR_EFDS_MASK                      (0x01UL << MCM_PLACR_EFDS_SHIFT)                    /*!< MCM_PLACR: EFDS Mask                    */
#define MCM_PLACR_EFDS_SHIFT                     14                                                  /*!< MCM_PLACR: EFDS Position                */
#define MCM_PLACR_DFCS_MASK                      (0x01UL << MCM_PLACR_DFCS_SHIFT)                    /*!< MCM_PLACR: DFCS Mask                    */
#define MCM_PLACR_DFCS_SHIFT                     15                                                  /*!< MCM_PLACR: DFCS Position                */
#define MCM_PLACR_ESFC_MASK                      (0x01UL << MCM_PLACR_ESFC_SHIFT)                    /*!< MCM_PLACR: ESFC Mask                    */
#define MCM_PLACR_ESFC_SHIFT                     16                                                  /*!< MCM_PLACR: ESFC Position                */

/* ------- MCM_CPO                                  ------ */
#define MCM_CPO_CPOREQ_MASK                      (0x01UL << MCM_CPO_CPOREQ_SHIFT)                    /*!< MCM_CPO: CPOREQ Mask                    */
#define MCM_CPO_CPOREQ_SHIFT                     0                                                   /*!< MCM_CPO: CPOREQ Position                */
#define MCM_CPO_CPOACK_MASK                      (0x01UL << MCM_CPO_CPOACK_SHIFT)                    /*!< MCM_CPO: CPOACK Mask                    */
#define MCM_CPO_CPOACK_SHIFT                     1                                                   /*!< MCM_CPO: CPOACK Position                */
#define MCM_CPO_CPOWOI_MASK                      (0x01UL << MCM_CPO_CPOWOI_SHIFT)                    /*!< MCM_CPO: CPOWOI Mask                    */
#define MCM_CPO_CPOWOI_SHIFT                     2                                                   /*!< MCM_CPO: CPOWOI Position                */

/* -------------------------------------------------------------------------------- */
/* -----------     'MCM' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define MCM_PLASC                      (MCM->PLASC)
#define MCM_PLAMC                      (MCM->PLAMC)
#define MCM_PLACR                      (MCM->PLACR)
#define MCM_CPO                        (MCM->CPO)

/* ================================================================================ */
/* ================           MTB (file:MTB_0)                     ================ */
/* ================================================================================ */

/**
 * @brief Micro Trace Buffer
 */
typedef struct {                                /*!<       MTB Structure                                                */
   __IO uint32_t  POSITION;                     /*!< 0000: MTB Position Register                                        */
   __IO uint32_t  MASTER;                       /*!< 0004: MTB Master Register                                          */
   __IO uint32_t  FLOW;                         /*!< 0008: MTB Flow Register                                            */
   __I  uint32_t  BASE;                         /*!< 000C: MTB Base Register                                            */
   __I  uint32_t  RESERVED0[956];               /*!< 0010:                                                              */
   __I  uint32_t  MODECTRL;                     /*!< 0F00: Integration Mode Control Register                            */
   __I  uint32_t  RESERVED1[39];                /*!< 0F04:                                                              */
   __I  uint32_t  TAGSET;                       /*!< 0FA0: Claim TAG Set Register                                       */
   __I  uint32_t  TAGCLEAR;                     /*!< 0FA4: Claim TAG Clear Register                                     */
   __I  uint32_t  RESERVED2[2];                 /*!< 0FA8:                                                              */
   __I  uint32_t  LOCKACCESS;                   /*!< 0FB0: Lock Access Register                                         */
   __I  uint32_t  LOCKSTAT;                     /*!< 0FB4: Lock Status Register                                         */
   __I  uint32_t  AUTHSTAT;                     /*!< 0FB8: Authentication Status Register                               */
   __I  uint32_t  DEVICEARCH;                   /*!< 0FBC: Device Architecture Register                                 */
   __I  uint32_t  RESERVED3[2];                 /*!< 0FC0:                                                              */
   __I  uint32_t  DEVICECFG;                    /*!< 0FC8: Device Configuration Register                                */
   __I  uint32_t  DEVICETYPID;                  /*!< 0FCC: Device Type Identifier Register                              */
   __I  uint32_t  PERIPHID4;                    /*!< 0FD0: Peripheral ID Register                                       */
   __I  uint32_t  PERIPHID5;                    /*!< 0FD4: Peripheral ID Register                                       */
   __I  uint32_t  PERIPHID6;                    /*!< 0FD8: Peripheral ID Register                                       */
   __I  uint32_t  PERIPHID7;                    /*!< 0FDC: Peripheral ID Register                                       */
   __I  uint32_t  PERIPHID0;                    /*!< 0FE0: Peripheral ID Register                                       */
   __I  uint32_t  PERIPHID1;                    /*!< 0FE4: Peripheral ID Register                                       */
   __I  uint32_t  PERIPHID2;                    /*!< 0FE8: Peripheral ID Register                                       */
   __I  uint32_t  PERIPHID3;                    /*!< 0FEC: Peripheral ID Register                                       */
   __I  uint32_t  COMPID[4];                    /*!< 0FF0: Component ID Register                                        */
} MTB_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'MTB' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- MTB_POSITION                             ------ */
#define MTB_POSITION_WRAP_MASK                   (0x01UL << MTB_POSITION_WRAP_SHIFT)                 /*!< MTB_POSITION: WRAP Mask                 */
#define MTB_POSITION_WRAP_SHIFT                  2                                                   /*!< MTB_POSITION: WRAP Position             */
#define MTB_POSITION_POINTER_MASK                (0x1FFFFFFFUL << MTB_POSITION_POINTER_SHIFT)        /*!< MTB_POSITION: POINTER Mask              */
#define MTB_POSITION_POINTER_SHIFT               3                                                   /*!< MTB_POSITION: POINTER Position          */
#define MTB_POSITION_POINTER(x)                  (((x)<<MTB_POSITION_POINTER_SHIFT)&MTB_POSITION_POINTER_MASK) /*!< MTB_POSITION                            */

/* ------- MTB_MASTER                               ------ */
#define MTB_MASTER_MASK_MASK                     (0x1FUL << MTB_MASTER_MASK_SHIFT)                   /*!< MTB_MASTER: MASK Mask                   */
#define MTB_MASTER_MASK_SHIFT                    0                                                   /*!< MTB_MASTER: MASK Position               */
#define MTB_MASTER_MASK(x)                       (((x)<<MTB_MASTER_MASK_SHIFT)&MTB_MASTER_MASK_MASK) /*!< MTB_MASTER                              */
#define MTB_MASTER_TSTARTEN_MASK                 (0x01UL << MTB_MASTER_TSTARTEN_SHIFT)               /*!< MTB_MASTER: TSTARTEN Mask               */
#define MTB_MASTER_TSTARTEN_SHIFT                5                                                   /*!< MTB_MASTER: TSTARTEN Position           */
#define MTB_MASTER_TSTOPEN_MASK                  (0x01UL << MTB_MASTER_TSTOPEN_SHIFT)                /*!< MTB_MASTER: TSTOPEN Mask                */
#define MTB_MASTER_TSTOPEN_SHIFT                 6                                                   /*!< MTB_MASTER: TSTOPEN Position            */
#define MTB_MASTER_SFRWPRIV_MASK                 (0x01UL << MTB_MASTER_SFRWPRIV_SHIFT)               /*!< MTB_MASTER: SFRWPRIV Mask               */
#define MTB_MASTER_SFRWPRIV_SHIFT                7                                                   /*!< MTB_MASTER: SFRWPRIV Position           */
#define MTB_MASTER_RAMPRIV_MASK                  (0x01UL << MTB_MASTER_RAMPRIV_SHIFT)                /*!< MTB_MASTER: RAMPRIV Mask                */
#define MTB_MASTER_RAMPRIV_SHIFT                 8                                                   /*!< MTB_MASTER: RAMPRIV Position            */
#define MTB_MASTER_HALTREQ_MASK                  (0x01UL << MTB_MASTER_HALTREQ_SHIFT)                /*!< MTB_MASTER: HALTREQ Mask                */
#define MTB_MASTER_HALTREQ_SHIFT                 9                                                   /*!< MTB_MASTER: HALTREQ Position            */
#define MTB_MASTER_EN_MASK                       (0x01UL << MTB_MASTER_EN_SHIFT)                     /*!< MTB_MASTER: EN Mask                     */
#define MTB_MASTER_EN_SHIFT                      31                                                  /*!< MTB_MASTER: EN Position                 */

/* ------- MTB_FLOW                                 ------ */
#define MTB_FLOW_AUTOSTOP_MASK                   (0x01UL << MTB_FLOW_AUTOSTOP_SHIFT)                 /*!< MTB_FLOW: AUTOSTOP Mask                 */
#define MTB_FLOW_AUTOSTOP_SHIFT                  0                                                   /*!< MTB_FLOW: AUTOSTOP Position             */
#define MTB_FLOW_AUTOHALT_MASK                   (0x01UL << MTB_FLOW_AUTOHALT_SHIFT)                 /*!< MTB_FLOW: AUTOHALT Mask                 */
#define MTB_FLOW_AUTOHALT_SHIFT                  1                                                   /*!< MTB_FLOW: AUTOHALT Position             */
#define MTB_FLOW_WATERMARK_MASK                  (0x1FFFFFFFUL << MTB_FLOW_WATERMARK_SHIFT)          /*!< MTB_FLOW: WATERMARK Mask                */
#define MTB_FLOW_WATERMARK_SHIFT                 3                                                   /*!< MTB_FLOW: WATERMARK Position            */
#define MTB_FLOW_WATERMARK(x)                    (((x)<<MTB_FLOW_WATERMARK_SHIFT)&MTB_FLOW_WATERMARK_MASK) /*!< MTB_FLOW                                */

/* ------- MTB_BASE                                 ------ */
#define MTB_BASE_BASEADDR_MASK                   (0xFFFFFFFFUL << MTB_BASE_BASEADDR_SHIFT)           /*!< MTB_BASE: BASEADDR Mask                 */
#define MTB_BASE_BASEADDR_SHIFT                  0                                                   /*!< MTB_BASE: BASEADDR Position             */
#define MTB_BASE_BASEADDR(x)                     (((x)<<MTB_BASE_BASEADDR_SHIFT)&MTB_BASE_BASEADDR_MASK) /*!< MTB_BASE                                */

/* ------- MTB_MODECTRL                             ------ */
#define MTB_MODECTRL_MODECTRL_MASK               (0xFFFFFFFFUL << MTB_MODECTRL_MODECTRL_SHIFT)       /*!< MTB_MODECTRL: MODECTRL Mask             */
#define MTB_MODECTRL_MODECTRL_SHIFT              0                                                   /*!< MTB_MODECTRL: MODECTRL Position         */
#define MTB_MODECTRL_MODECTRL(x)                 (((x)<<MTB_MODECTRL_MODECTRL_SHIFT)&MTB_MODECTRL_MODECTRL_MASK) /*!< MTB_MODECTRL                            */

/* ------- MTB_TAGSET                               ------ */
#define MTB_TAGSET_TAGSET_MASK                   (0xFFFFFFFFUL << MTB_TAGSET_TAGSET_SHIFT)           /*!< MTB_TAGSET: TAGSET Mask                 */
#define MTB_TAGSET_TAGSET_SHIFT                  0                                                   /*!< MTB_TAGSET: TAGSET Position             */
#define MTB_TAGSET_TAGSET(x)                     (((x)<<MTB_TAGSET_TAGSET_SHIFT)&MTB_TAGSET_TAGSET_MASK) /*!< MTB_TAGSET                              */

/* ------- MTB_TAGCLEAR                             ------ */
#define MTB_TAGCLEAR_TAGCLEAR_MASK               (0xFFFFFFFFUL << MTB_TAGCLEAR_TAGCLEAR_SHIFT)       /*!< MTB_TAGCLEAR: TAGCLEAR Mask             */
#define MTB_TAGCLEAR_TAGCLEAR_SHIFT              0                                                   /*!< MTB_TAGCLEAR: TAGCLEAR Position         */
#define MTB_TAGCLEAR_TAGCLEAR(x)                 (((x)<<MTB_TAGCLEAR_TAGCLEAR_SHIFT)&MTB_TAGCLEAR_TAGCLEAR_MASK) /*!< MTB_TAGCLEAR                            */

/* ------- MTB_LOCKACCESS                           ------ */
#define MTB_LOCKACCESS_LOCKACCESS_MASK           (0xFFFFFFFFUL << MTB_LOCKACCESS_LOCKACCESS_SHIFT)   /*!< MTB_LOCKACCESS: LOCKACCESS Mask         */
#define MTB_LOCKACCESS_LOCKACCESS_SHIFT          0                                                   /*!< MTB_LOCKACCESS: LOCKACCESS Position     */
#define MTB_LOCKACCESS_LOCKACCESS(x)             (((x)<<MTB_LOCKACCESS_LOCKACCESS_SHIFT)&MTB_LOCKACCESS_LOCKACCESS_MASK) /*!< MTB_LOCKACCESS                          */

/* ------- MTB_LOCKSTAT                             ------ */
#define MTB_LOCKSTAT_LOCKSTAT_MASK               (0xFFFFFFFFUL << MTB_LOCKSTAT_LOCKSTAT_SHIFT)       /*!< MTB_LOCKSTAT: LOCKSTAT Mask             */
#define MTB_LOCKSTAT_LOCKSTAT_SHIFT              0                                                   /*!< MTB_LOCKSTAT: LOCKSTAT Position         */
#define MTB_LOCKSTAT_LOCKSTAT(x)                 (((x)<<MTB_LOCKSTAT_LOCKSTAT_SHIFT)&MTB_LOCKSTAT_LOCKSTAT_MASK) /*!< MTB_LOCKSTAT                            */

/* ------- MTB_AUTHSTAT                             ------ */
#define MTB_AUTHSTAT_BIT0_MASK                   (0x01UL << MTB_AUTHSTAT_BIT0_SHIFT)                 /*!< MTB_AUTHSTAT: BIT0 Mask                 */
#define MTB_AUTHSTAT_BIT0_SHIFT                  0                                                   /*!< MTB_AUTHSTAT: BIT0 Position             */
#define MTB_AUTHSTAT_BIT1_MASK                   (0x01UL << MTB_AUTHSTAT_BIT1_SHIFT)                 /*!< MTB_AUTHSTAT: BIT1 Mask                 */
#define MTB_AUTHSTAT_BIT1_SHIFT                  1                                                   /*!< MTB_AUTHSTAT: BIT1 Position             */
#define MTB_AUTHSTAT_BIT2_MASK                   (0x01UL << MTB_AUTHSTAT_BIT2_SHIFT)                 /*!< MTB_AUTHSTAT: BIT2 Mask                 */
#define MTB_AUTHSTAT_BIT2_SHIFT                  2                                                   /*!< MTB_AUTHSTAT: BIT2 Position             */
#define MTB_AUTHSTAT_BIT3_MASK                   (0x01UL << MTB_AUTHSTAT_BIT3_SHIFT)                 /*!< MTB_AUTHSTAT: BIT3 Mask                 */
#define MTB_AUTHSTAT_BIT3_SHIFT                  3                                                   /*!< MTB_AUTHSTAT: BIT3 Position             */

/* ------- MTB_DEVICEARCH                           ------ */
#define MTB_DEVICEARCH_DEVICEARCH_MASK           (0xFFFFFFFFUL << MTB_DEVICEARCH_DEVICEARCH_SHIFT)   /*!< MTB_DEVICEARCH: DEVICEARCH Mask         */
#define MTB_DEVICEARCH_DEVICEARCH_SHIFT          0                                                   /*!< MTB_DEVICEARCH: DEVICEARCH Position     */
#define MTB_DEVICEARCH_DEVICEARCH(x)             (((x)<<MTB_DEVICEARCH_DEVICEARCH_SHIFT)&MTB_DEVICEARCH_DEVICEARCH_MASK) /*!< MTB_DEVICEARCH                          */

/* ------- MTB_DEVICECFG                            ------ */
#define MTB_DEVICECFG_DEVICECFG_MASK             (0xFFFFFFFFUL << MTB_DEVICECFG_DEVICECFG_SHIFT)     /*!< MTB_DEVICECFG: DEVICECFG Mask           */
#define MTB_DEVICECFG_DEVICECFG_SHIFT            0                                                   /*!< MTB_DEVICECFG: DEVICECFG Position       */
#define MTB_DEVICECFG_DEVICECFG(x)               (((x)<<MTB_DEVICECFG_DEVICECFG_SHIFT)&MTB_DEVICECFG_DEVICECFG_MASK) /*!< MTB_DEVICECFG                           */

/* ------- MTB_DEVICETYPID                          ------ */
#define MTB_DEVICETYPID_DEVICETYPID_MASK         (0xFFFFFFFFUL << MTB_DEVICETYPID_DEVICETYPID_SHIFT) /*!< MTB_DEVICETYPID: DEVICETYPID Mask       */
#define MTB_DEVICETYPID_DEVICETYPID_SHIFT        0                                                   /*!< MTB_DEVICETYPID: DEVICETYPID Position   */
#define MTB_DEVICETYPID_DEVICETYPID(x)           (((x)<<MTB_DEVICETYPID_DEVICETYPID_SHIFT)&MTB_DEVICETYPID_DEVICETYPID_MASK) /*!< MTB_DEVICETYPID                         */

/* ------- MTB_PERIPHID                             ------ */
#define MTB_PERIPHID_PERIPHID_MASK               (0xFFFFFFFFUL << MTB_PERIPHID_PERIPHID_SHIFT)       /*!< MTB_PERIPHID: PERIPHID Mask             */
#define MTB_PERIPHID_PERIPHID_SHIFT              0                                                   /*!< MTB_PERIPHID: PERIPHID Position         */
#define MTB_PERIPHID_PERIPHID(x)                 (((x)<<MTB_PERIPHID_PERIPHID_SHIFT)&MTB_PERIPHID_PERIPHID_MASK) /*!< MTB_PERIPHID                            */

/* ------- MTB_COMPID                               ------ */
#define MTB_COMPID_COMPID_MASK                   (0xFFFFFFFFUL << MTB_COMPID_COMPID_SHIFT)           /*!< MTB_COMPID: COMPID Mask                 */
#define MTB_COMPID_COMPID_SHIFT                  0                                                   /*!< MTB_COMPID: COMPID Position             */
#define MTB_COMPID_COMPID(x)                     (((x)<<MTB_COMPID_COMPID_SHIFT)&MTB_COMPID_COMPID_MASK) /*!< MTB_COMPID                              */

/* -------------------------------------------------------------------------------- */
/* -----------     'MTB' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define MTB_POSITION                   (MTB->POSITION)
#define MTB_MASTER                     (MTB->MASTER)
#define MTB_FLOW                       (MTB->FLOW)
#define MTB_BASE                       (MTB->BASE)
#define MTB_MODECTRL                   (MTB->MODECTRL)
#define MTB_TAGSET                     (MTB->TAGSET)
#define MTB_TAGCLEAR                   (MTB->TAGCLEAR)
#define MTB_LOCKACCESS                 (MTB->LOCKACCESS)
#define MTB_LOCKSTAT                   (MTB->LOCKSTAT)
#define MTB_AUTHSTAT                   (MTB->AUTHSTAT)
#define MTB_DEVICEARCH                 (MTB->DEVICEARCH)
#define MTB_DEVICECFG                  (MTB->DEVICECFG)
#define MTB_DEVICETYPID                (MTB->DEVICETYPID)
#define MTB_PERIPHID4                  (MTB->PERIPHID4)
#define MTB_PERIPHID5                  (MTB->PERIPHID5)
#define MTB_PERIPHID6                  (MTB->PERIPHID6)
#define MTB_PERIPHID7                  (MTB->PERIPHID7)
#define MTB_PERIPHID0                  (MTB->PERIPHID0)
#define MTB_PERIPHID1                  (MTB->PERIPHID1)
#define MTB_PERIPHID2                  (MTB->PERIPHID2)
#define MTB_PERIPHID3                  (MTB->PERIPHID3)
#define MTB_COMPID0                    (MTB->COMPID[0])
#define MTB_COMPID1                    (MTB->COMPID[1])
#define MTB_COMPID2                    (MTB->COMPID[2])
#define MTB_COMPID3                    (MTB->COMPID[3])

/* ================================================================================ */
/* ================           MTBDWT (file:MTBDWT_MKL)             ================ */
/* ================================================================================ */

/**
 * @brief MTB data watchpoint and trace
 */
typedef struct {                                /*!<       MTBDWT Structure                                             */
   __I  uint32_t  CTRL;                         /*!< 0000: MTB DWT Control Register                                     */
   __I  uint32_t  RESERVED0[7];                 /*!< 0004:                                                              */
   struct { /* (cluster) */                     /*!< 0020: (size=0x0020, 32)                                            */
      __IO uint32_t  COMP;                      /*!< 0020: MTB_DWT Comparator Register                                  */
      __IO uint32_t  MASK;                      /*!< 0024: MTB_DWT Comparator Mask Register                             */
      __IO uint32_t  FCT;                       /*!< 0028: MTB_DWT Comparator Function Register 0                       */
      __I  uint32_t  RESERVED0;                 /*!< 002C:                                                              */
   } COMPARATOR[2];
   __I  uint32_t  RESERVED1[112];               /*!< 0040:                                                              */
   __IO uint32_t  TBCTRL;                       /*!< 0200: MTB_DWT Trace Buffer Control Register                        */
   __I  uint32_t  RESERVED2[881];               /*!< 0204:                                                              */
   __I  uint32_t  DEVICECFG;                    /*!< 0FC8: Device Configuration Register                                */
   __I  uint32_t  DEVICETYPID;                  /*!< 0FCC: Device Type Identifier Register                              */
   __I  uint32_t  PERIPHID4;                    /*!< 0FD0: Peripheral ID Register                                       */
   __I  uint32_t  PERIPHID5;                    /*!< 0FD4: Peripheral ID Register                                       */
   __I  uint32_t  PERIPHID6;                    /*!< 0FD8: Peripheral ID Register                                       */
   __I  uint32_t  PERIPHID7;                    /*!< 0FDC: Peripheral ID Register                                       */
   __I  uint32_t  PERIPHID0;                    /*!< 0FE0: Peripheral ID Register                                       */
   __I  uint32_t  PERIPHID1;                    /*!< 0FE4: Peripheral ID Register                                       */
   __I  uint32_t  PERIPHID2;                    /*!< 0FE8: Peripheral ID Register                                       */
   __I  uint32_t  PERIPHID3;                    /*!< 0FEC: Peripheral ID Register                                       */
   __I  uint32_t  COMPID[4];                    /*!< 0FF0: Component ID Register                                        */
} MTBDWT_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'MTBDWT' Position & Mask macros                      ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- MTBDWT_CTRL                              ------ */
#define MTBDWT_CTRL_DWTCFGCTRL_MASK              (0xFFFFFFFUL << MTBDWT_CTRL_DWTCFGCTRL_SHIFT)       /*!< MTBDWT_CTRL: DWTCFGCTRL Mask            */
#define MTBDWT_CTRL_DWTCFGCTRL_SHIFT             0                                                   /*!< MTBDWT_CTRL: DWTCFGCTRL Position        */
#define MTBDWT_CTRL_DWTCFGCTRL(x)                (((x)<<MTBDWT_CTRL_DWTCFGCTRL_SHIFT)&MTBDWT_CTRL_DWTCFGCTRL_MASK) /*!< MTBDWT_CTRL                             */
#define MTBDWT_CTRL_NUMCMP_MASK                  (0x0FUL << MTBDWT_CTRL_NUMCMP_SHIFT)                /*!< MTBDWT_CTRL: NUMCMP Mask                */
#define MTBDWT_CTRL_NUMCMP_SHIFT                 28                                                  /*!< MTBDWT_CTRL: NUMCMP Position            */
#define MTBDWT_CTRL_NUMCMP(x)                    (((x)<<MTBDWT_CTRL_NUMCMP_SHIFT)&MTBDWT_CTRL_NUMCMP_MASK) /*!< MTBDWT_CTRL                             */

/* ------- MTBDWT_COMP                              ------ */
#define MTBDWT_COMP_COMP_MASK                    (0xFFFFFFFFUL << MTBDWT_COMP_COMP_SHIFT)            /*!< MTBDWT_COMP: COMP Mask                  */
#define MTBDWT_COMP_COMP_SHIFT                   0                                                   /*!< MTBDWT_COMP: COMP Position              */
#define MTBDWT_COMP_COMP(x)                      (((x)<<MTBDWT_COMP_COMP_SHIFT)&MTBDWT_COMP_COMP_MASK) /*!< MTBDWT_COMP                             */

/* ------- MTBDWT_MASK                              ------ */
#define MTBDWT_MASK_MASK_MASK                    (0x1FUL << MTBDWT_MASK_MASK_SHIFT)                  /*!< MTBDWT_MASK: MASK Mask                  */
#define MTBDWT_MASK_MASK_SHIFT                   0                                                   /*!< MTBDWT_MASK: MASK Position              */
#define MTBDWT_MASK_MASK(x)                      (((x)<<MTBDWT_MASK_MASK_SHIFT)&MTBDWT_MASK_MASK_MASK) /*!< MTBDWT_MASK                             */

/* ------- MTBDWT_FCT                               ------ */
#define MTBDWT_FCT_FUNCTION_MASK                 (0x0FUL << MTBDWT_FCT_FUNCTION_SHIFT)               /*!< MTBDWT_FCT: FUNCTION Mask               */
#define MTBDWT_FCT_FUNCTION_SHIFT                0                                                   /*!< MTBDWT_FCT: FUNCTION Position           */
#define MTBDWT_FCT_FUNCTION(x)                   (((x)<<MTBDWT_FCT_FUNCTION_SHIFT)&MTBDWT_FCT_FUNCTION_MASK) /*!< MTBDWT_FCT                              */
#define MTBDWT_FCT_DATAVMATCH_MASK               (0x01UL << MTBDWT_FCT_DATAVMATCH_SHIFT)             /*!< MTBDWT_FCT: DATAVMATCH Mask             */
#define MTBDWT_FCT_DATAVMATCH_SHIFT              8                                                   /*!< MTBDWT_FCT: DATAVMATCH Position         */
#define MTBDWT_FCT_DATAVSIZE_MASK                (0x03UL << MTBDWT_FCT_DATAVSIZE_SHIFT)              /*!< MTBDWT_FCT: DATAVSIZE Mask              */
#define MTBDWT_FCT_DATAVSIZE_SHIFT               10                                                  /*!< MTBDWT_FCT: DATAVSIZE Position          */
#define MTBDWT_FCT_DATAVSIZE(x)                  (((x)<<MTBDWT_FCT_DATAVSIZE_SHIFT)&MTBDWT_FCT_DATAVSIZE_MASK) /*!< MTBDWT_FCT                              */
#define MTBDWT_FCT_DATAVADDR0_MASK               (0x0FUL << MTBDWT_FCT_DATAVADDR0_SHIFT)             /*!< MTBDWT_FCT: DATAVADDR0 Mask             */
#define MTBDWT_FCT_DATAVADDR0_SHIFT              12                                                  /*!< MTBDWT_FCT: DATAVADDR0 Position         */
#define MTBDWT_FCT_DATAVADDR0(x)                 (((x)<<MTBDWT_FCT_DATAVADDR0_SHIFT)&MTBDWT_FCT_DATAVADDR0_MASK) /*!< MTBDWT_FCT                              */
#define MTBDWT_FCT_MATCHED_MASK                  (0x01UL << MTBDWT_FCT_MATCHED_SHIFT)                /*!< MTBDWT_FCT: MATCHED Mask                */
#define MTBDWT_FCT_MATCHED_SHIFT                 24                                                  /*!< MTBDWT_FCT: MATCHED Position            */

/* ------- MTBDWT_TBCTRL                            ------ */
#define MTBDWT_TBCTRL_ACOMP0_MASK                (0x01UL << MTBDWT_TBCTRL_ACOMP0_SHIFT)              /*!< MTBDWT_TBCTRL: ACOMP0 Mask              */
#define MTBDWT_TBCTRL_ACOMP0_SHIFT               0                                                   /*!< MTBDWT_TBCTRL: ACOMP0 Position          */
#define MTBDWT_TBCTRL_ACOMP1_MASK                (0x01UL << MTBDWT_TBCTRL_ACOMP1_SHIFT)              /*!< MTBDWT_TBCTRL: ACOMP1 Mask              */
#define MTBDWT_TBCTRL_ACOMP1_SHIFT               1                                                   /*!< MTBDWT_TBCTRL: ACOMP1 Position          */
#define MTBDWT_TBCTRL_NUMCOMP_MASK               (0x0FUL << MTBDWT_TBCTRL_NUMCOMP_SHIFT)             /*!< MTBDWT_TBCTRL: NUMCOMP Mask             */
#define MTBDWT_TBCTRL_NUMCOMP_SHIFT              28                                                  /*!< MTBDWT_TBCTRL: NUMCOMP Position         */
#define MTBDWT_TBCTRL_NUMCOMP(x)                 (((x)<<MTBDWT_TBCTRL_NUMCOMP_SHIFT)&MTBDWT_TBCTRL_NUMCOMP_MASK) /*!< MTBDWT_TBCTRL                           */

/* ------- MTBDWT_DEVICECFG                         ------ */
#define MTBDWT_DEVICECFG_DEVICECFG_MASK          (0xFFFFFFFFUL << MTBDWT_DEVICECFG_DEVICECFG_SHIFT)  /*!< MTBDWT_DEVICECFG: DEVICECFG Mask        */
#define MTBDWT_DEVICECFG_DEVICECFG_SHIFT         0                                                   /*!< MTBDWT_DEVICECFG: DEVICECFG Position    */
#define MTBDWT_DEVICECFG_DEVICECFG(x)            (((x)<<MTBDWT_DEVICECFG_DEVICECFG_SHIFT)&MTBDWT_DEVICECFG_DEVICECFG_MASK) /*!< MTBDWT_DEVICECFG                        */

/* ------- MTBDWT_DEVICETYPID                       ------ */
#define MTBDWT_DEVICETYPID_DEVICETYPID_MASK      (0xFFFFFFFFUL << MTBDWT_DEVICETYPID_DEVICETYPID_SHIFT) /*!< MTBDWT_DEVICETYPID: DEVICETYPID Mask    */
#define MTBDWT_DEVICETYPID_DEVICETYPID_SHIFT     0                                                   /*!< MTBDWT_DEVICETYPID: DEVICETYPID Position*/
#define MTBDWT_DEVICETYPID_DEVICETYPID(x)        (((x)<<MTBDWT_DEVICETYPID_DEVICETYPID_SHIFT)&MTBDWT_DEVICETYPID_DEVICETYPID_MASK) /*!< MTBDWT_DEVICETYPID                      */

/* ------- MTBDWT_PERIPHID                          ------ */
#define MTBDWT_PERIPHID_PERIPHID_MASK            (0xFFFFFFFFUL << MTBDWT_PERIPHID_PERIPHID_SHIFT)    /*!< MTBDWT_PERIPHID: PERIPHID Mask          */
#define MTBDWT_PERIPHID_PERIPHID_SHIFT           0                                                   /*!< MTBDWT_PERIPHID: PERIPHID Position      */
#define MTBDWT_PERIPHID_PERIPHID(x)              (((x)<<MTBDWT_PERIPHID_PERIPHID_SHIFT)&MTBDWT_PERIPHID_PERIPHID_MASK) /*!< MTBDWT_PERIPHID                         */

/* ------- MTBDWT_COMPID                            ------ */
#define MTBDWT_COMPID_COMPID_MASK                (0xFFFFFFFFUL << MTBDWT_COMPID_COMPID_SHIFT)        /*!< MTBDWT_COMPID: COMPID Mask              */
#define MTBDWT_COMPID_COMPID_SHIFT               0                                                   /*!< MTBDWT_COMPID: COMPID Position          */
#define MTBDWT_COMPID_COMPID(x)                  (((x)<<MTBDWT_COMPID_COMPID_SHIFT)&MTBDWT_COMPID_COMPID_MASK) /*!< MTBDWT_COMPID                           */

/* -------------------------------------------------------------------------------- */
/* -----------     'MTBDWT' Register Access macros                      ----------- */
/* -------------------------------------------------------------------------------- */

#define MTBDWT_CTRL                    (MTBDWT->CTRL)
#define MTBDWT_COMP0                   (MTBDWT->COMPARATOR[0].COMP)
#define MTBDWT_MASK0                   (MTBDWT->COMPARATOR[0].MASK)
#define MTBDWT_FCT0                    (MTBDWT->COMPARATOR[0].FCT)
#define MTBDWT_COMP1                   (MTBDWT->COMPARATOR[1].COMP)
#define MTBDWT_MASK1                   (MTBDWT->COMPARATOR[1].MASK)
#define MTBDWT_FCT1                    (MTBDWT->COMPARATOR[1].FCT)
#define MTBDWT_TBCTRL                  (MTBDWT->TBCTRL)
#define MTBDWT_DEVICECFG               (MTBDWT->DEVICECFG)
#define MTBDWT_DEVICETYPID             (MTBDWT->DEVICETYPID)
#define MTBDWT_PERIPHID4               (MTBDWT->PERIPHID4)
#define MTBDWT_PERIPHID5               (MTBDWT->PERIPHID5)
#define MTBDWT_PERIPHID6               (MTBDWT->PERIPHID6)
#define MTBDWT_PERIPHID7               (MTBDWT->PERIPHID7)
#define MTBDWT_PERIPHID0               (MTBDWT->PERIPHID0)
#define MTBDWT_PERIPHID1               (MTBDWT->PERIPHID1)
#define MTBDWT_PERIPHID2               (MTBDWT->PERIPHID2)
#define MTBDWT_PERIPHID3               (MTBDWT->PERIPHID3)
#define MTBDWT_COMPID0                 (MTBDWT->COMPID[0])
#define MTBDWT_COMPID1                 (MTBDWT->COMPID[1])
#define MTBDWT_COMPID2                 (MTBDWT->COMPID[2])
#define MTBDWT_COMPID3                 (MTBDWT->COMPID[3])

/* ================================================================================ */
/* ================           NV (file:NV_FTFA_boot)               ================ */
/* ================================================================================ */

/**
 * @brief Flash configuration field
 */
typedef struct {                                /*!<       NV Structure                                                 */
   __I  uint8_t   BACKKEY3;                     /*!< 0000: Backdoor Comparison Key 3                                    */
   __I  uint8_t   BACKKEY2;                     /*!< 0001: Backdoor Comparison Key 2                                    */
   __I  uint8_t   BACKKEY1;                     /*!< 0002: Backdoor Comparison Key 1                                    */
   __I  uint8_t   BACKKEY0;                     /*!< 0003: Backdoor Comparison Key 0                                    */
   __I  uint8_t   BACKKEY7;                     /*!< 0004: Backdoor Comparison Key 7                                    */
   __I  uint8_t   BACKKEY6;                     /*!< 0005: Backdoor Comparison Key 6                                    */
   __I  uint8_t   BACKKEY5;                     /*!< 0006: Backdoor Comparison Key 5                                    */
   __I  uint8_t   BACKKEY4;                     /*!< 0007: Backdoor Comparison Key 4                                    */
   __I  uint8_t   FPROT3;                       /*!< 0008: Non-volatile P-Flash Protection Register                     */
   __I  uint8_t   FPROT2;                       /*!< 0009: Non-volatile P-Flash Protection Register                     */
   __I  uint8_t   FPROT1;                       /*!< 000A: Non-volatile P-Flash Protection Register                     */
   __I  uint8_t   FPROT0;                       /*!< 000B: Non-volatile P-Flash Protection Register                     */
   __I  uint8_t   FSEC;                         /*!< 000C: Non-volatile Flash Security Register                         */
   __I  uint8_t   FOPT;                         /*!< 000D: Non-volatile Flash Option Register                           */
} NV_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'NV' Position & Mask macros                          ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- NV_BACKKEY                               ------ */
#define NV_BACKKEY_KEY_MASK                      (0xFFUL << NV_BACKKEY_KEY_SHIFT)                    /*!< NV_BACKKEY: KEY Mask                    */
#define NV_BACKKEY_KEY_SHIFT                     0                                                   /*!< NV_BACKKEY: KEY Position                */
#define NV_BACKKEY_KEY(x)                        (((x)<<NV_BACKKEY_KEY_SHIFT)&NV_BACKKEY_KEY_MASK)   /*!< NV_BACKKEY                              */

/* ------- NV_FPROT                                 ------ */
#define NV_FPROT_PROT_MASK                       (0xFFUL << NV_FPROT_PROT_SHIFT)                     /*!< NV_FPROT: PROT Mask                     */
#define NV_FPROT_PROT_SHIFT                      0                                                   /*!< NV_FPROT: PROT Position                 */
#define NV_FPROT_PROT(x)                         (((x)<<NV_FPROT_PROT_SHIFT)&NV_FPROT_PROT_MASK)     /*!< NV_FPROT                                */

/* ------- NV_FSEC                                  ------ */
#define NV_FSEC_SEC_MASK                         (0x03UL << NV_FSEC_SEC_SHIFT)                       /*!< NV_FSEC: SEC Mask                       */
#define NV_FSEC_SEC_SHIFT                        0                                                   /*!< NV_FSEC: SEC Position                   */
#define NV_FSEC_SEC(x)                           (((x)<<NV_FSEC_SEC_SHIFT)&NV_FSEC_SEC_MASK)         /*!< NV_FSEC                                 */
#define NV_FSEC_FSLACC_MASK                      (0x03UL << NV_FSEC_FSLACC_SHIFT)                    /*!< NV_FSEC: FSLACC Mask                    */
#define NV_FSEC_FSLACC_SHIFT                     2                                                   /*!< NV_FSEC: FSLACC Position                */
#define NV_FSEC_FSLACC(x)                        (((x)<<NV_FSEC_FSLACC_SHIFT)&NV_FSEC_FSLACC_MASK)   /*!< NV_FSEC                                 */
#define NV_FSEC_MEEN_MASK                        (0x03UL << NV_FSEC_MEEN_SHIFT)                      /*!< NV_FSEC: MEEN Mask                      */
#define NV_FSEC_MEEN_SHIFT                       4                                                   /*!< NV_FSEC: MEEN Position                  */
#define NV_FSEC_MEEN(x)                          (((x)<<NV_FSEC_MEEN_SHIFT)&NV_FSEC_MEEN_MASK)       /*!< NV_FSEC                                 */
#define NV_FSEC_KEYEN_MASK                       (0x03UL << NV_FSEC_KEYEN_SHIFT)                     /*!< NV_FSEC: KEYEN Mask                     */
#define NV_FSEC_KEYEN_SHIFT                      6                                                   /*!< NV_FSEC: KEYEN Position                 */
#define NV_FSEC_KEYEN(x)                         (((x)<<NV_FSEC_KEYEN_SHIFT)&NV_FSEC_KEYEN_MASK)     /*!< NV_FSEC                                 */

/* ------- NV_FOPT                                  ------ */
#define NV_FOPT_LPBOOT_MASK                      (0x01UL << NV_FOPT_LPBOOT_SHIFT)                    /*!< NV_FOPT: LPBOOT Mask                    */
#define NV_FOPT_LPBOOT_SHIFT                     0                                                   /*!< NV_FOPT: LPBOOT Position                */
#define NV_FOPT_BOOTPIN_OPT_MASK                 (0x01UL << NV_FOPT_BOOTPIN_OPT_SHIFT)               /*!< NV_FOPT: BOOTPIN_OPT Mask               */
#define NV_FOPT_BOOTPIN_OPT_SHIFT                1                                                   /*!< NV_FOPT: BOOTPIN_OPT Position           */
#define NV_FOPT_NMI_DIS_MASK                     (0x01UL << NV_FOPT_NMI_DIS_SHIFT)                   /*!< NV_FOPT: NMI_DIS Mask                   */
#define NV_FOPT_NMI_DIS_SHIFT                    2                                                   /*!< NV_FOPT: NMI_DIS Position               */
#define NV_FOPT_RESET_PIN_CFG_MASK               (0x01UL << NV_FOPT_RESET_PIN_CFG_SHIFT)             /*!< NV_FOPT: RESET_PIN_CFG Mask             */
#define NV_FOPT_RESET_PIN_CFG_SHIFT              3                                                   /*!< NV_FOPT: RESET_PIN_CFG Position         */
#define NV_FOPT_LPBOOT1_MASK                     (0x01UL << NV_FOPT_LPBOOT1_SHIFT)                   /*!< NV_FOPT: LPBOOT1 Mask                   */
#define NV_FOPT_LPBOOT1_SHIFT                    4                                                   /*!< NV_FOPT: LPBOOT1 Position               */
#define NV_FOPT_FAST_INIT_MASK                   (0x01UL << NV_FOPT_FAST_INIT_SHIFT)                 /*!< NV_FOPT: FAST_INIT Mask                 */
#define NV_FOPT_FAST_INIT_SHIFT                  5                                                   /*!< NV_FOPT: FAST_INIT Position             */
#define NV_FOPT_BOOTSRC_SEL_MASK                 (0x03UL << NV_FOPT_BOOTSRC_SEL_SHIFT)               /*!< NV_FOPT: BOOTSRC_SEL Mask               */
#define NV_FOPT_BOOTSRC_SEL_SHIFT                6                                                   /*!< NV_FOPT: BOOTSRC_SEL Position           */
#define NV_FOPT_BOOTSRC_SEL(x)                   (((x)<<NV_FOPT_BOOTSRC_SEL_SHIFT)&NV_FOPT_BOOTSRC_SEL_MASK) /*!< NV_FOPT                                 */

/* -------------------------------------------------------------------------------- */
/* -----------     'NV' Register Access macros                          ----------- */
/* -------------------------------------------------------------------------------- */

#define NV_BACKKEY3                    (NV->BACKKEY3)
#define NV_BACKKEY2                    (NV->BACKKEY2)
#define NV_BACKKEY1                    (NV->BACKKEY1)
#define NV_BACKKEY0                    (NV->BACKKEY0)
#define NV_BACKKEY7                    (NV->BACKKEY7)
#define NV_BACKKEY6                    (NV->BACKKEY6)
#define NV_BACKKEY5                    (NV->BACKKEY5)
#define NV_BACKKEY4                    (NV->BACKKEY4)
#define NV_FPROT3                      (NV->FPROT3)
#define NV_FPROT2                      (NV->FPROT2)
#define NV_FPROT1                      (NV->FPROT1)
#define NV_FPROT0                      (NV->FPROT0)
#define NV_FSEC                        (NV->FSEC)
#define NV_FOPT                        (NV->FOPT)

/* ================================================================================ */
/* ================           OSC0 (file:OSC_0)                    ================ */
/* ================================================================================ */

/**
 * @brief System Oscillator
 */
typedef struct {                                /*!<       OSC0 Structure                                               */
   __IO uint8_t   CR;                           /*!< 0000: Control Register                                             */
} OSC0_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'OSC0' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- OSC0_CR                                  ------ */
#define OSC_CR_SC16P_MASK                        (0x01UL << OSC_CR_SC16P_SHIFT)                      /*!< OSC0_CR: SC16P Mask                     */
#define OSC_CR_SC16P_SHIFT                       0                                                   /*!< OSC0_CR: SC16P Position                 */
#define OSC_CR_SC8P_MASK                         (0x01UL << OSC_CR_SC8P_SHIFT)                       /*!< OSC0_CR: SC8P Mask                      */
#define OSC_CR_SC8P_SHIFT                        1                                                   /*!< OSC0_CR: SC8P Position                  */
#define OSC_CR_SC4P_MASK                         (0x01UL << OSC_CR_SC4P_SHIFT)                       /*!< OSC0_CR: SC4P Mask                      */
#define OSC_CR_SC4P_SHIFT                        2                                                   /*!< OSC0_CR: SC4P Position                  */
#define OSC_CR_SC2P_MASK                         (0x01UL << OSC_CR_SC2P_SHIFT)                       /*!< OSC0_CR: SC2P Mask                      */
#define OSC_CR_SC2P_SHIFT                        3                                                   /*!< OSC0_CR: SC2P Position                  */
#define OSC_CR_EREFSTEN_MASK                     (0x01UL << OSC_CR_EREFSTEN_SHIFT)                   /*!< OSC0_CR: EREFSTEN Mask                  */
#define OSC_CR_EREFSTEN_SHIFT                    5                                                   /*!< OSC0_CR: EREFSTEN Position              */
#define OSC_CR_ERCLKEN_MASK                      (0x01UL << OSC_CR_ERCLKEN_SHIFT)                    /*!< OSC0_CR: ERCLKEN Mask                   */
#define OSC_CR_ERCLKEN_SHIFT                     7                                                   /*!< OSC0_CR: ERCLKEN Position               */

/* -------------------------------------------------------------------------------- */
/* -----------     'OSC0' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define OSC0_CR                        (OSC0->CR)

/* ================================================================================ */
/* ================           PIT (file:PIT_2CH_LTMR64)            ================ */
/* ================================================================================ */

/**
 * @brief Periodic Interrupt Timer (2 channels)
 */
typedef struct {                                /*!<       PIT Structure                                                */
   __IO uint32_t  MCR;                          /*!< 0000: Module Control Register                                      */
   __I  uint32_t  RESERVED0[55];                /*!< 0004:                                                              */
   __I  uint32_t  LTMR64H;                      /*!< 00E0: Upper Lifetime Timer Register                                */
   __I  uint32_t  LTMR64L;                      /*!< 00E4: Lower Lifetime Timer Register                                */
   __I  uint32_t  RESERVED1[6];                 /*!< 00E8:                                                              */
   struct { /* (cluster) */                     /*!< 0100: (size=0x0020, 32)                                            */
      __IO uint32_t  LDVAL;                     /*!< 0100: Timer Load Value Register                                    */
      __I  uint32_t  CVAL;                      /*!< 0104: Current Timer Value Register                                 */
      __IO uint32_t  TCTRL;                     /*!< 0108: Timer Control Register                                       */
      __IO uint32_t  TFLG;                      /*!< 010C: Timer Flag Register                                          */
   } CS[2];
} PIT_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'PIT' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- PIT_MCR                                  ------ */
#define PIT_MCR_FRZ_MASK                         (0x01UL << PIT_MCR_FRZ_SHIFT)                       /*!< PIT_MCR: FRZ Mask                       */
#define PIT_MCR_FRZ_SHIFT                        0                                                   /*!< PIT_MCR: FRZ Position                   */
#define PIT_MCR_MDIS_MASK                        (0x01UL << PIT_MCR_MDIS_SHIFT)                      /*!< PIT_MCR: MDIS Mask                      */
#define PIT_MCR_MDIS_SHIFT                       1                                                   /*!< PIT_MCR: MDIS Position                  */

/* ------- PIT_LTMR64H                              ------ */
#define PIT_LTMR64H_LTH_MASK                     (0xFFFFFFFFUL << PIT_LTMR64H_LTH_SHIFT)             /*!< PIT_LTMR64H: LTH Mask                   */
#define PIT_LTMR64H_LTH_SHIFT                    0                                                   /*!< PIT_LTMR64H: LTH Position               */
#define PIT_LTMR64H_LTH(x)                       (((x)<<PIT_LTMR64H_LTH_SHIFT)&PIT_LTMR64H_LTH_MASK) /*!< PIT_LTMR64H                             */

/* ------- PIT_LTMR64L                              ------ */
#define PIT_LTMR64L_LTL_MASK                     (0xFFFFFFFFUL << PIT_LTMR64L_LTL_SHIFT)             /*!< PIT_LTMR64L: LTL Mask                   */
#define PIT_LTMR64L_LTL_SHIFT                    0                                                   /*!< PIT_LTMR64L: LTL Position               */
#define PIT_LTMR64L_LTL(x)                       (((x)<<PIT_LTMR64L_LTL_SHIFT)&PIT_LTMR64L_LTL_MASK) /*!< PIT_LTMR64L                             */

/* ------- PIT_LDVAL                                ------ */
#define PIT_LDVAL_TSV_MASK                       (0xFFFFFFFFUL << PIT_LDVAL_TSV_SHIFT)               /*!< PIT_LDVAL: TSV Mask                     */
#define PIT_LDVAL_TSV_SHIFT                      0                                                   /*!< PIT_LDVAL: TSV Position                 */
#define PIT_LDVAL_TSV(x)                         (((x)<<PIT_LDVAL_TSV_SHIFT)&PIT_LDVAL_TSV_MASK)     /*!< PIT_LDVAL                               */

/* ------- PIT_CVAL                                 ------ */
#define PIT_CVAL_TVL_MASK                        (0xFFFFFFFFUL << PIT_CVAL_TVL_SHIFT)                /*!< PIT_CVAL: TVL Mask                      */
#define PIT_CVAL_TVL_SHIFT                       0                                                   /*!< PIT_CVAL: TVL Position                  */
#define PIT_CVAL_TVL(x)                          (((x)<<PIT_CVAL_TVL_SHIFT)&PIT_CVAL_TVL_MASK)       /*!< PIT_CVAL                                */

/* ------- PIT_TCTRL                                ------ */
#define PIT_TCTRL_TEN_MASK                       (0x01UL << PIT_TCTRL_TEN_SHIFT)                     /*!< PIT_TCTRL: TEN Mask                     */
#define PIT_TCTRL_TEN_SHIFT                      0                                                   /*!< PIT_TCTRL: TEN Position                 */
#define PIT_TCTRL_TIE_MASK                       (0x01UL << PIT_TCTRL_TIE_SHIFT)                     /*!< PIT_TCTRL: TIE Mask                     */
#define PIT_TCTRL_TIE_SHIFT                      1                                                   /*!< PIT_TCTRL: TIE Position                 */
#define PIT_TCTRL_CHN_MASK                       (0x01UL << PIT_TCTRL_CHN_SHIFT)                     /*!< PIT_TCTRL: CHN Mask                     */
#define PIT_TCTRL_CHN_SHIFT                      2                                                   /*!< PIT_TCTRL: CHN Position                 */

/* ------- PIT_TFLG                                 ------ */
#define PIT_TFLG_TIF_MASK                        (0x01UL << PIT_TFLG_TIF_SHIFT)                      /*!< PIT_TFLG: TIF Mask                      */
#define PIT_TFLG_TIF_SHIFT                       0                                                   /*!< PIT_TFLG: TIF Position                  */

/* -------------------------------------------------------------------------------- */
/* -----------     'PIT' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define PIT_MCR                        (PIT->MCR)
#define PIT_LTMR64H                    (PIT->LTMR64H)
#define PIT_LTMR64L                    (PIT->LTMR64L)
#define PIT_LDVAL0                     (PIT->CS[0].LDVAL)
#define PIT_CVAL0                      (PIT->CS[0].CVAL)
#define PIT_TCTRL0                     (PIT->CS[0].TCTRL)
#define PIT_TFLG0                      (PIT->CS[0].TFLG)
#define PIT_LDVAL1                     (PIT->CS[1].LDVAL)
#define PIT_CVAL1                      (PIT->CS[1].CVAL)
#define PIT_TCTRL1                     (PIT->CS[1].TCTRL)
#define PIT_TFLG1                      (PIT->CS[1].TFLG)

/* ================================================================================ */
/* ================           PMC (file:PMC_0)                     ================ */
/* ================================================================================ */

/**
 * @brief Power Management Controller
 */
typedef struct {                                /*!<       PMC Structure                                                */
   __IO uint8_t   LVDSC1;                       /*!< 0000: Low Voltage Status and Control 1                             */
   __IO uint8_t   LVDSC2;                       /*!< 0001: Low Voltage Status and Control 2                             */
   __IO uint8_t   REGSC;                        /*!< 0002: Regulator Status and Control                                 */
} PMC_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'PMC' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- PMC_LVDSC1                               ------ */
#define PMC_LVDSC1_LVDV_MASK                     (0x03UL << PMC_LVDSC1_LVDV_SHIFT)                   /*!< PMC_LVDSC1: LVDV Mask                   */
#define PMC_LVDSC1_LVDV_SHIFT                    0                                                   /*!< PMC_LVDSC1: LVDV Position               */
#define PMC_LVDSC1_LVDV(x)                       (((x)<<PMC_LVDSC1_LVDV_SHIFT)&PMC_LVDSC1_LVDV_MASK) /*!< PMC_LVDSC1                              */
#define PMC_LVDSC1_LVDRE_MASK                    (0x01UL << PMC_LVDSC1_LVDRE_SHIFT)                  /*!< PMC_LVDSC1: LVDRE Mask                  */
#define PMC_LVDSC1_LVDRE_SHIFT                   4                                                   /*!< PMC_LVDSC1: LVDRE Position              */
#define PMC_LVDSC1_LVDIE_MASK                    (0x01UL << PMC_LVDSC1_LVDIE_SHIFT)                  /*!< PMC_LVDSC1: LVDIE Mask                  */
#define PMC_LVDSC1_LVDIE_SHIFT                   5                                                   /*!< PMC_LVDSC1: LVDIE Position              */
#define PMC_LVDSC1_LVDACK_MASK                   (0x01UL << PMC_LVDSC1_LVDACK_SHIFT)                 /*!< PMC_LVDSC1: LVDACK Mask                 */
#define PMC_LVDSC1_LVDACK_SHIFT                  6                                                   /*!< PMC_LVDSC1: LVDACK Position             */
#define PMC_LVDSC1_LVDF_MASK                     (0x01UL << PMC_LVDSC1_LVDF_SHIFT)                   /*!< PMC_LVDSC1: LVDF Mask                   */
#define PMC_LVDSC1_LVDF_SHIFT                    7                                                   /*!< PMC_LVDSC1: LVDF Position               */

/* ------- PMC_LVDSC2                               ------ */
#define PMC_LVDSC2_LVWV_MASK                     (0x03UL << PMC_LVDSC2_LVWV_SHIFT)                   /*!< PMC_LVDSC2: LVWV Mask                   */
#define PMC_LVDSC2_LVWV_SHIFT                    0                                                   /*!< PMC_LVDSC2: LVWV Position               */
#define PMC_LVDSC2_LVWV(x)                       (((x)<<PMC_LVDSC2_LVWV_SHIFT)&PMC_LVDSC2_LVWV_MASK) /*!< PMC_LVDSC2                              */
#define PMC_LVDSC2_LVWIE_MASK                    (0x01UL << PMC_LVDSC2_LVWIE_SHIFT)                  /*!< PMC_LVDSC2: LVWIE Mask                  */
#define PMC_LVDSC2_LVWIE_SHIFT                   5                                                   /*!< PMC_LVDSC2: LVWIE Position              */
#define PMC_LVDSC2_LVWACK_MASK                   (0x01UL << PMC_LVDSC2_LVWACK_SHIFT)                 /*!< PMC_LVDSC2: LVWACK Mask                 */
#define PMC_LVDSC2_LVWACK_SHIFT                  6                                                   /*!< PMC_LVDSC2: LVWACK Position             */
#define PMC_LVDSC2_LVWF_MASK                     (0x01UL << PMC_LVDSC2_LVWF_SHIFT)                   /*!< PMC_LVDSC2: LVWF Mask                   */
#define PMC_LVDSC2_LVWF_SHIFT                    7                                                   /*!< PMC_LVDSC2: LVWF Position               */

/* ------- PMC_REGSC                                ------ */
#define PMC_REGSC_BGBE_MASK                      (0x01UL << PMC_REGSC_BGBE_SHIFT)                    /*!< PMC_REGSC: BGBE Mask                    */
#define PMC_REGSC_BGBE_SHIFT                     0                                                   /*!< PMC_REGSC: BGBE Position                */
#define PMC_REGSC_REGONS_MASK                    (0x01UL << PMC_REGSC_REGONS_SHIFT)                  /*!< PMC_REGSC: REGONS Mask                  */
#define PMC_REGSC_REGONS_SHIFT                   2                                                   /*!< PMC_REGSC: REGONS Position              */
#define PMC_REGSC_ACKISO_MASK                    (0x01UL << PMC_REGSC_ACKISO_SHIFT)                  /*!< PMC_REGSC: ACKISO Mask                  */
#define PMC_REGSC_ACKISO_SHIFT                   3                                                   /*!< PMC_REGSC: ACKISO Position              */
#define PMC_REGSC_BGEN_MASK                      (0x01UL << PMC_REGSC_BGEN_SHIFT)                    /*!< PMC_REGSC: BGEN Mask                    */
#define PMC_REGSC_BGEN_SHIFT                     4                                                   /*!< PMC_REGSC: BGEN Position                */

/* -------------------------------------------------------------------------------- */
/* -----------     'PMC' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define PMC_LVDSC1                     (PMC->LVDSC1)
#define PMC_LVDSC2                     (PMC->LVDSC2)
#define PMC_REGSC                      (PMC->REGSC)

/* ================================================================================ */
/* ================           PORTA (file:PORTA_MKL)               ================ */
/* ================================================================================ */

/**
 * @brief Pin Control and Interrupts
 */
typedef struct {                                /*!<       PORTA Structure                                              */
   __IO uint32_t  PCR[32];                      /*!< 0000: Pin Control Register                                         */
   __IO uint32_t  GPCLR;                        /*!< 0080: Global Pin Control Low Register                              */
   __IO uint32_t  GPCHR;                        /*!< 0084: Global Pin Control High Register                             */
   __I  uint32_t  RESERVED0[6];                 /*!< 0088:                                                              */
   __IO uint32_t  ISFR;                         /*!< 00A0: Interrupt Status Flag Register                               */
} PORTA_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'PORTA' Position & Mask macros                       ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- PORTA_PCR                                ------ */
#define PORT_PCR_PS_MASK                         (0x01UL << PORT_PCR_PS_SHIFT)                       /*!< PORTA_PCR: PS Mask                      */
#define PORT_PCR_PS_SHIFT                        0                                                   /*!< PORTA_PCR: PS Position                  */
#define PORT_PCR_PE_MASK                         (0x01UL << PORT_PCR_PE_SHIFT)                       /*!< PORTA_PCR: PE Mask                      */
#define PORT_PCR_PE_SHIFT                        1                                                   /*!< PORTA_PCR: PE Position                  */
#define PORT_PCR_SRE_MASK                        (0x01UL << PORT_PCR_SRE_SHIFT)                      /*!< PORTA_PCR: SRE Mask                     */
#define PORT_PCR_SRE_SHIFT                       2                                                   /*!< PORTA_PCR: SRE Position                 */
#define PORT_PCR_PFE_MASK                        (0x01UL << PORT_PCR_PFE_SHIFT)                      /*!< PORTA_PCR: PFE Mask                     */
#define PORT_PCR_PFE_SHIFT                       4                                                   /*!< PORTA_PCR: PFE Position                 */
#define PORT_PCR_ODE_MASK                        (0x01UL << PORT_PCR_ODE_SHIFT)                      /*!< PORTA_PCR: ODE Mask                     */
#define PORT_PCR_ODE_SHIFT                       5                                                   /*!< PORTA_PCR: ODE Position                 */
#define PORT_PCR_DSE_MASK                        (0x01UL << PORT_PCR_DSE_SHIFT)                      /*!< PORTA_PCR: DSE Mask                     */
#define PORT_PCR_DSE_SHIFT                       6                                                   /*!< PORTA_PCR: DSE Position                 */
#define PORT_PCR_MUX_MASK                        (0x07UL << PORT_PCR_MUX_SHIFT)                      /*!< PORTA_PCR: MUX Mask                     */
#define PORT_PCR_MUX_SHIFT                       8                                                   /*!< PORTA_PCR: MUX Position                 */
#define PORT_PCR_MUX(x)                          (((x)<<PORT_PCR_MUX_SHIFT)&PORT_PCR_MUX_MASK)       /*!< PORTA_PCR                               */
#define PORT_PCR_IRQC_MASK                       (0x0FUL << PORT_PCR_IRQC_SHIFT)                     /*!< PORTA_PCR: IRQC Mask                    */
#define PORT_PCR_IRQC_SHIFT                      16                                                  /*!< PORTA_PCR: IRQC Position                */
#define PORT_PCR_IRQC(x)                         (((x)<<PORT_PCR_IRQC_SHIFT)&PORT_PCR_IRQC_MASK)     /*!< PORTA_PCR                               */
#define PORT_PCR_ISF_MASK                        (0x01UL << PORT_PCR_ISF_SHIFT)                      /*!< PORTA_PCR: ISF Mask                     */
#define PORT_PCR_ISF_SHIFT                       24                                                  /*!< PORTA_PCR: ISF Position                 */

/* ------- PORTA_GPCLR                              ------ */
#define PORT_GPCLR_GPWD_MASK                     (0xFFFFUL << PORT_GPCLR_GPWD_SHIFT)                 /*!< PORTA_GPCLR: GPWD Mask                  */
#define PORT_GPCLR_GPWD_SHIFT                    0                                                   /*!< PORTA_GPCLR: GPWD Position              */
#define PORT_GPCLR_GPWD(x)                       (((x)<<PORT_GPCLR_GPWD_SHIFT)&PORT_GPCLR_GPWD_MASK) /*!< PORTA_GPCLR                             */
#define PORT_GPCLR_GPWE_MASK                     (0xFFFFUL << PORT_GPCLR_GPWE_SHIFT)                 /*!< PORTA_GPCLR: GPWE Mask                  */
#define PORT_GPCLR_GPWE_SHIFT                    16                                                  /*!< PORTA_GPCLR: GPWE Position              */
#define PORT_GPCLR_GPWE(x)                       (((x)<<PORT_GPCLR_GPWE_SHIFT)&PORT_GPCLR_GPWE_MASK) /*!< PORTA_GPCLR                             */

/* ------- PORTA_GPCHR                              ------ */
#define PORT_GPCHR_GPWD_MASK                     (0xFFFFUL << PORT_GPCHR_GPWD_SHIFT)                 /*!< PORTA_GPCHR: GPWD Mask                  */
#define PORT_GPCHR_GPWD_SHIFT                    0                                                   /*!< PORTA_GPCHR: GPWD Position              */
#define PORT_GPCHR_GPWD(x)                       (((x)<<PORT_GPCHR_GPWD_SHIFT)&PORT_GPCHR_GPWD_MASK) /*!< PORTA_GPCHR                             */
#define PORT_GPCHR_GPWE_MASK                     (0xFFFFUL << PORT_GPCHR_GPWE_SHIFT)                 /*!< PORTA_GPCHR: GPWE Mask                  */
#define PORT_GPCHR_GPWE_SHIFT                    16                                                  /*!< PORTA_GPCHR: GPWE Position              */
#define PORT_GPCHR_GPWE(x)                       (((x)<<PORT_GPCHR_GPWE_SHIFT)&PORT_GPCHR_GPWE_MASK) /*!< PORTA_GPCHR                             */

/* ------- PORTA_ISFR                               ------ */
#define PORT_ISFR_ISF0_MASK                      (0x01UL << PORT_ISFR_ISF0_SHIFT)                    /*!< PORTA_ISFR: ISF0 Mask                   */
#define PORT_ISFR_ISF0_SHIFT                     0                                                   /*!< PORTA_ISFR: ISF0 Position               */
#define PORT_ISFR_ISF1_MASK                      (0x01UL << PORT_ISFR_ISF1_SHIFT)                    /*!< PORTA_ISFR: ISF1 Mask                   */
#define PORT_ISFR_ISF1_SHIFT                     1                                                   /*!< PORTA_ISFR: ISF1 Position               */
#define PORT_ISFR_ISF2_MASK                      (0x01UL << PORT_ISFR_ISF2_SHIFT)                    /*!< PORTA_ISFR: ISF2 Mask                   */
#define PORT_ISFR_ISF2_SHIFT                     2                                                   /*!< PORTA_ISFR: ISF2 Position               */
#define PORT_ISFR_ISF3_MASK                      (0x01UL << PORT_ISFR_ISF3_SHIFT)                    /*!< PORTA_ISFR: ISF3 Mask                   */
#define PORT_ISFR_ISF3_SHIFT                     3                                                   /*!< PORTA_ISFR: ISF3 Position               */
#define PORT_ISFR_ISF4_MASK                      (0x01UL << PORT_ISFR_ISF4_SHIFT)                    /*!< PORTA_ISFR: ISF4 Mask                   */
#define PORT_ISFR_ISF4_SHIFT                     4                                                   /*!< PORTA_ISFR: ISF4 Position               */
#define PORT_ISFR_ISF5_MASK                      (0x01UL << PORT_ISFR_ISF5_SHIFT)                    /*!< PORTA_ISFR: ISF5 Mask                   */
#define PORT_ISFR_ISF5_SHIFT                     5                                                   /*!< PORTA_ISFR: ISF5 Position               */
#define PORT_ISFR_ISF6_MASK                      (0x01UL << PORT_ISFR_ISF6_SHIFT)                    /*!< PORTA_ISFR: ISF6 Mask                   */
#define PORT_ISFR_ISF6_SHIFT                     6                                                   /*!< PORTA_ISFR: ISF6 Position               */
#define PORT_ISFR_ISF7_MASK                      (0x01UL << PORT_ISFR_ISF7_SHIFT)                    /*!< PORTA_ISFR: ISF7 Mask                   */
#define PORT_ISFR_ISF7_SHIFT                     7                                                   /*!< PORTA_ISFR: ISF7 Position               */
#define PORT_ISFR_ISF8_MASK                      (0x01UL << PORT_ISFR_ISF8_SHIFT)                    /*!< PORTA_ISFR: ISF8 Mask                   */
#define PORT_ISFR_ISF8_SHIFT                     8                                                   /*!< PORTA_ISFR: ISF8 Position               */
#define PORT_ISFR_ISF9_MASK                      (0x01UL << PORT_ISFR_ISF9_SHIFT)                    /*!< PORTA_ISFR: ISF9 Mask                   */
#define PORT_ISFR_ISF9_SHIFT                     9                                                   /*!< PORTA_ISFR: ISF9 Position               */
#define PORT_ISFR_ISF10_MASK                     (0x01UL << PORT_ISFR_ISF10_SHIFT)                   /*!< PORTA_ISFR: ISF10 Mask                  */
#define PORT_ISFR_ISF10_SHIFT                    10                                                  /*!< PORTA_ISFR: ISF10 Position              */
#define PORT_ISFR_ISF11_MASK                     (0x01UL << PORT_ISFR_ISF11_SHIFT)                   /*!< PORTA_ISFR: ISF11 Mask                  */
#define PORT_ISFR_ISF11_SHIFT                    11                                                  /*!< PORTA_ISFR: ISF11 Position              */
#define PORT_ISFR_ISF12_MASK                     (0x01UL << PORT_ISFR_ISF12_SHIFT)                   /*!< PORTA_ISFR: ISF12 Mask                  */
#define PORT_ISFR_ISF12_SHIFT                    12                                                  /*!< PORTA_ISFR: ISF12 Position              */
#define PORT_ISFR_ISF13_MASK                     (0x01UL << PORT_ISFR_ISF13_SHIFT)                   /*!< PORTA_ISFR: ISF13 Mask                  */
#define PORT_ISFR_ISF13_SHIFT                    13                                                  /*!< PORTA_ISFR: ISF13 Position              */
#define PORT_ISFR_ISF14_MASK                     (0x01UL << PORT_ISFR_ISF14_SHIFT)                   /*!< PORTA_ISFR: ISF14 Mask                  */
#define PORT_ISFR_ISF14_SHIFT                    14                                                  /*!< PORTA_ISFR: ISF14 Position              */
#define PORT_ISFR_ISF15_MASK                     (0x01UL << PORT_ISFR_ISF15_SHIFT)                   /*!< PORTA_ISFR: ISF15 Mask                  */
#define PORT_ISFR_ISF15_SHIFT                    15                                                  /*!< PORTA_ISFR: ISF15 Position              */
#define PORT_ISFR_ISF16_MASK                     (0x01UL << PORT_ISFR_ISF16_SHIFT)                   /*!< PORTA_ISFR: ISF16 Mask                  */
#define PORT_ISFR_ISF16_SHIFT                    16                                                  /*!< PORTA_ISFR: ISF16 Position              */
#define PORT_ISFR_ISF17_MASK                     (0x01UL << PORT_ISFR_ISF17_SHIFT)                   /*!< PORTA_ISFR: ISF17 Mask                  */
#define PORT_ISFR_ISF17_SHIFT                    17                                                  /*!< PORTA_ISFR: ISF17 Position              */
#define PORT_ISFR_ISF18_MASK                     (0x01UL << PORT_ISFR_ISF18_SHIFT)                   /*!< PORTA_ISFR: ISF18 Mask                  */
#define PORT_ISFR_ISF18_SHIFT                    18                                                  /*!< PORTA_ISFR: ISF18 Position              */
#define PORT_ISFR_ISF19_MASK                     (0x01UL << PORT_ISFR_ISF19_SHIFT)                   /*!< PORTA_ISFR: ISF19 Mask                  */
#define PORT_ISFR_ISF19_SHIFT                    19                                                  /*!< PORTA_ISFR: ISF19 Position              */
#define PORT_ISFR_ISF20_MASK                     (0x01UL << PORT_ISFR_ISF20_SHIFT)                   /*!< PORTA_ISFR: ISF20 Mask                  */
#define PORT_ISFR_ISF20_SHIFT                    20                                                  /*!< PORTA_ISFR: ISF20 Position              */
#define PORT_ISFR_ISF21_MASK                     (0x01UL << PORT_ISFR_ISF21_SHIFT)                   /*!< PORTA_ISFR: ISF21 Mask                  */
#define PORT_ISFR_ISF21_SHIFT                    21                                                  /*!< PORTA_ISFR: ISF21 Position              */
#define PORT_ISFR_ISF22_MASK                     (0x01UL << PORT_ISFR_ISF22_SHIFT)                   /*!< PORTA_ISFR: ISF22 Mask                  */
#define PORT_ISFR_ISF22_SHIFT                    22                                                  /*!< PORTA_ISFR: ISF22 Position              */
#define PORT_ISFR_ISF23_MASK                     (0x01UL << PORT_ISFR_ISF23_SHIFT)                   /*!< PORTA_ISFR: ISF23 Mask                  */
#define PORT_ISFR_ISF23_SHIFT                    23                                                  /*!< PORTA_ISFR: ISF23 Position              */
#define PORT_ISFR_ISF24_MASK                     (0x01UL << PORT_ISFR_ISF24_SHIFT)                   /*!< PORTA_ISFR: ISF24 Mask                  */
#define PORT_ISFR_ISF24_SHIFT                    24                                                  /*!< PORTA_ISFR: ISF24 Position              */
#define PORT_ISFR_ISF25_MASK                     (0x01UL << PORT_ISFR_ISF25_SHIFT)                   /*!< PORTA_ISFR: ISF25 Mask                  */
#define PORT_ISFR_ISF25_SHIFT                    25                                                  /*!< PORTA_ISFR: ISF25 Position              */
#define PORT_ISFR_ISF26_MASK                     (0x01UL << PORT_ISFR_ISF26_SHIFT)                   /*!< PORTA_ISFR: ISF26 Mask                  */
#define PORT_ISFR_ISF26_SHIFT                    26                                                  /*!< PORTA_ISFR: ISF26 Position              */
#define PORT_ISFR_ISF27_MASK                     (0x01UL << PORT_ISFR_ISF27_SHIFT)                   /*!< PORTA_ISFR: ISF27 Mask                  */
#define PORT_ISFR_ISF27_SHIFT                    27                                                  /*!< PORTA_ISFR: ISF27 Position              */
#define PORT_ISFR_ISF28_MASK                     (0x01UL << PORT_ISFR_ISF28_SHIFT)                   /*!< PORTA_ISFR: ISF28 Mask                  */
#define PORT_ISFR_ISF28_SHIFT                    28                                                  /*!< PORTA_ISFR: ISF28 Position              */
#define PORT_ISFR_ISF29_MASK                     (0x01UL << PORT_ISFR_ISF29_SHIFT)                   /*!< PORTA_ISFR: ISF29 Mask                  */
#define PORT_ISFR_ISF29_SHIFT                    29                                                  /*!< PORTA_ISFR: ISF29 Position              */
#define PORT_ISFR_ISF30_MASK                     (0x01UL << PORT_ISFR_ISF30_SHIFT)                   /*!< PORTA_ISFR: ISF30 Mask                  */
#define PORT_ISFR_ISF30_SHIFT                    30                                                  /*!< PORTA_ISFR: ISF30 Position              */
#define PORT_ISFR_ISF31_MASK                     (0x01UL << PORT_ISFR_ISF31_SHIFT)                   /*!< PORTA_ISFR: ISF31 Mask                  */
#define PORT_ISFR_ISF31_SHIFT                    31                                                  /*!< PORTA_ISFR: ISF31 Position              */

/* -------------------------------------------------------------------------------- */
/* -----------     'PORTA' Register Access macros                       ----------- */
/* -------------------------------------------------------------------------------- */

#define PORTA_PCR0                     (PORTA->PCR[0])
#define PORTA_PCR1                     (PORTA->PCR[1])
#define PORTA_PCR2                     (PORTA->PCR[2])
#define PORTA_PCR3                     (PORTA->PCR[3])
#define PORTA_PCR4                     (PORTA->PCR[4])
#define PORTA_PCR5                     (PORTA->PCR[5])
#define PORTA_PCR6                     (PORTA->PCR[6])
#define PORTA_PCR7                     (PORTA->PCR[7])
#define PORTA_PCR8                     (PORTA->PCR[8])
#define PORTA_PCR9                     (PORTA->PCR[9])
#define PORTA_PCR10                    (PORTA->PCR[10])
#define PORTA_PCR11                    (PORTA->PCR[11])
#define PORTA_PCR12                    (PORTA->PCR[12])
#define PORTA_PCR13                    (PORTA->PCR[13])
#define PORTA_PCR14                    (PORTA->PCR[14])
#define PORTA_PCR15                    (PORTA->PCR[15])
#define PORTA_PCR16                    (PORTA->PCR[16])
#define PORTA_PCR17                    (PORTA->PCR[17])
#define PORTA_PCR18                    (PORTA->PCR[18])
#define PORTA_PCR19                    (PORTA->PCR[19])
#define PORTA_PCR20                    (PORTA->PCR[20])
#define PORTA_PCR21                    (PORTA->PCR[21])
#define PORTA_PCR22                    (PORTA->PCR[22])
#define PORTA_PCR23                    (PORTA->PCR[23])
#define PORTA_PCR24                    (PORTA->PCR[24])
#define PORTA_PCR25                    (PORTA->PCR[25])
#define PORTA_PCR26                    (PORTA->PCR[26])
#define PORTA_PCR27                    (PORTA->PCR[27])
#define PORTA_PCR28                    (PORTA->PCR[28])
#define PORTA_PCR29                    (PORTA->PCR[29])
#define PORTA_PCR30                    (PORTA->PCR[30])
#define PORTA_PCR31                    (PORTA->PCR[31])
#define PORTA_GPCLR                    (PORTA->GPCLR)
#define PORTA_GPCHR                    (PORTA->GPCHR)
#define PORTA_ISFR                     (PORTA->ISFR)

/* ================================================================================ */
/* ================           PORTB (derived from PORTA)           ================ */
/* ================================================================================ */

/**
 * @brief Pin Control and Interrupts
 */
typedef PORTA_Type PORTB_Type;  /*!< PORTB Structure                                             */


/* -------------------------------------------------------------------------------- */
/* -----------     'PORTB' Register Access macros                       ----------- */
/* -------------------------------------------------------------------------------- */

#define PORTB_PCR0                     (PORTB->PCR[0])
#define PORTB_PCR1                     (PORTB->PCR[1])
#define PORTB_PCR2                     (PORTB->PCR[2])
#define PORTB_PCR3                     (PORTB->PCR[3])
#define PORTB_PCR4                     (PORTB->PCR[4])
#define PORTB_PCR5                     (PORTB->PCR[5])
#define PORTB_PCR6                     (PORTB->PCR[6])
#define PORTB_PCR7                     (PORTB->PCR[7])
#define PORTB_PCR8                     (PORTB->PCR[8])
#define PORTB_PCR9                     (PORTB->PCR[9])
#define PORTB_PCR10                    (PORTB->PCR[10])
#define PORTB_PCR11                    (PORTB->PCR[11])
#define PORTB_PCR12                    (PORTB->PCR[12])
#define PORTB_PCR13                    (PORTB->PCR[13])
#define PORTB_PCR14                    (PORTB->PCR[14])
#define PORTB_PCR15                    (PORTB->PCR[15])
#define PORTB_PCR16                    (PORTB->PCR[16])
#define PORTB_PCR17                    (PORTB->PCR[17])
#define PORTB_PCR18                    (PORTB->PCR[18])
#define PORTB_PCR19                    (PORTB->PCR[19])
#define PORTB_PCR20                    (PORTB->PCR[20])
#define PORTB_PCR21                    (PORTB->PCR[21])
#define PORTB_PCR22                    (PORTB->PCR[22])
#define PORTB_PCR23                    (PORTB->PCR[23])
#define PORTB_PCR24                    (PORTB->PCR[24])
#define PORTB_PCR25                    (PORTB->PCR[25])
#define PORTB_PCR26                    (PORTB->PCR[26])
#define PORTB_PCR27                    (PORTB->PCR[27])
#define PORTB_PCR28                    (PORTB->PCR[28])
#define PORTB_PCR29                    (PORTB->PCR[29])
#define PORTB_PCR30                    (PORTB->PCR[30])
#define PORTB_PCR31                    (PORTB->PCR[31])
#define PORTB_GPCLR                    (PORTB->GPCLR)
#define PORTB_GPCHR                    (PORTB->GPCHR)
#define PORTB_ISFR                     (PORTB->ISFR)

/* ================================================================================ */
/* ================           PORTC (derived from PORTA)           ================ */
/* ================================================================================ */

/**
 * @brief Pin Control and Interrupts
 */
typedef PORTA_Type PORTC_Type;  /*!< PORTC Structure                                             */


/* -------------------------------------------------------------------------------- */
/* -----------     'PORTC' Register Access macros                       ----------- */
/* -------------------------------------------------------------------------------- */

#define PORTC_PCR0                     (PORTC->PCR[0])
#define PORTC_PCR1                     (PORTC->PCR[1])
#define PORTC_PCR2                     (PORTC->PCR[2])
#define PORTC_PCR3                     (PORTC->PCR[3])
#define PORTC_PCR4                     (PORTC->PCR[4])
#define PORTC_PCR5                     (PORTC->PCR[5])
#define PORTC_PCR6                     (PORTC->PCR[6])
#define PORTC_PCR7                     (PORTC->PCR[7])
#define PORTC_PCR8                     (PORTC->PCR[8])
#define PORTC_PCR9                     (PORTC->PCR[9])
#define PORTC_PCR10                    (PORTC->PCR[10])
#define PORTC_PCR11                    (PORTC->PCR[11])
#define PORTC_PCR12                    (PORTC->PCR[12])
#define PORTC_PCR13                    (PORTC->PCR[13])
#define PORTC_PCR14                    (PORTC->PCR[14])
#define PORTC_PCR15                    (PORTC->PCR[15])
#define PORTC_PCR16                    (PORTC->PCR[16])
#define PORTC_PCR17                    (PORTC->PCR[17])
#define PORTC_PCR18                    (PORTC->PCR[18])
#define PORTC_PCR19                    (PORTC->PCR[19])
#define PORTC_PCR20                    (PORTC->PCR[20])
#define PORTC_PCR21                    (PORTC->PCR[21])
#define PORTC_PCR22                    (PORTC->PCR[22])
#define PORTC_PCR23                    (PORTC->PCR[23])
#define PORTC_PCR24                    (PORTC->PCR[24])
#define PORTC_PCR25                    (PORTC->PCR[25])
#define PORTC_PCR26                    (PORTC->PCR[26])
#define PORTC_PCR27                    (PORTC->PCR[27])
#define PORTC_PCR28                    (PORTC->PCR[28])
#define PORTC_PCR29                    (PORTC->PCR[29])
#define PORTC_PCR30                    (PORTC->PCR[30])
#define PORTC_PCR31                    (PORTC->PCR[31])
#define PORTC_GPCLR                    (PORTC->GPCLR)
#define PORTC_GPCHR                    (PORTC->GPCHR)
#define PORTC_ISFR                     (PORTC->ISFR)

/* ================================================================================ */
/* ================           PORTD (derived from PORTA)           ================ */
/* ================================================================================ */

/**
 * @brief Pin Control and Interrupts
 */
typedef PORTA_Type PORTD_Type;  /*!< PORTD Structure                                             */


/* -------------------------------------------------------------------------------- */
/* -----------     'PORTD' Register Access macros                       ----------- */
/* -------------------------------------------------------------------------------- */

#define PORTD_PCR0                     (PORTD->PCR[0])
#define PORTD_PCR1                     (PORTD->PCR[1])
#define PORTD_PCR2                     (PORTD->PCR[2])
#define PORTD_PCR3                     (PORTD->PCR[3])
#define PORTD_PCR4                     (PORTD->PCR[4])
#define PORTD_PCR5                     (PORTD->PCR[5])
#define PORTD_PCR6                     (PORTD->PCR[6])
#define PORTD_PCR7                     (PORTD->PCR[7])
#define PORTD_PCR8                     (PORTD->PCR[8])
#define PORTD_PCR9                     (PORTD->PCR[9])
#define PORTD_PCR10                    (PORTD->PCR[10])
#define PORTD_PCR11                    (PORTD->PCR[11])
#define PORTD_PCR12                    (PORTD->PCR[12])
#define PORTD_PCR13                    (PORTD->PCR[13])
#define PORTD_PCR14                    (PORTD->PCR[14])
#define PORTD_PCR15                    (PORTD->PCR[15])
#define PORTD_PCR16                    (PORTD->PCR[16])
#define PORTD_PCR17                    (PORTD->PCR[17])
#define PORTD_PCR18                    (PORTD->PCR[18])
#define PORTD_PCR19                    (PORTD->PCR[19])
#define PORTD_PCR20                    (PORTD->PCR[20])
#define PORTD_PCR21                    (PORTD->PCR[21])
#define PORTD_PCR22                    (PORTD->PCR[22])
#define PORTD_PCR23                    (PORTD->PCR[23])
#define PORTD_PCR24                    (PORTD->PCR[24])
#define PORTD_PCR25                    (PORTD->PCR[25])
#define PORTD_PCR26                    (PORTD->PCR[26])
#define PORTD_PCR27                    (PORTD->PCR[27])
#define PORTD_PCR28                    (PORTD->PCR[28])
#define PORTD_PCR29                    (PORTD->PCR[29])
#define PORTD_PCR30                    (PORTD->PCR[30])
#define PORTD_PCR31                    (PORTD->PCR[31])
#define PORTD_GPCLR                    (PORTD->GPCLR)
#define PORTD_GPCHR                    (PORTD->GPCHR)
#define PORTD_ISFR                     (PORTD->ISFR)

/* ================================================================================ */
/* ================           PORTE (derived from PORTA)           ================ */
/* ================================================================================ */

/**
 * @brief Pin Control and Interrupts
 */
typedef PORTA_Type PORTE_Type;  /*!< PORTE Structure                                             */


/* -------------------------------------------------------------------------------- */
/* -----------     'PORTE' Register Access macros                       ----------- */
/* -------------------------------------------------------------------------------- */

#define PORTE_PCR0                     (PORTE->PCR[0])
#define PORTE_PCR1                     (PORTE->PCR[1])
#define PORTE_PCR2                     (PORTE->PCR[2])
#define PORTE_PCR3                     (PORTE->PCR[3])
#define PORTE_PCR4                     (PORTE->PCR[4])
#define PORTE_PCR5                     (PORTE->PCR[5])
#define PORTE_PCR6                     (PORTE->PCR[6])
#define PORTE_PCR7                     (PORTE->PCR[7])
#define PORTE_PCR8                     (PORTE->PCR[8])
#define PORTE_PCR9                     (PORTE->PCR[9])
#define PORTE_PCR10                    (PORTE->PCR[10])
#define PORTE_PCR11                    (PORTE->PCR[11])
#define PORTE_PCR12                    (PORTE->PCR[12])
#define PORTE_PCR13                    (PORTE->PCR[13])
#define PORTE_PCR14                    (PORTE->PCR[14])
#define PORTE_PCR15                    (PORTE->PCR[15])
#define PORTE_PCR16                    (PORTE->PCR[16])
#define PORTE_PCR17                    (PORTE->PCR[17])
#define PORTE_PCR18                    (PORTE->PCR[18])
#define PORTE_PCR19                    (PORTE->PCR[19])
#define PORTE_PCR20                    (PORTE->PCR[20])
#define PORTE_PCR21                    (PORTE->PCR[21])
#define PORTE_PCR22                    (PORTE->PCR[22])
#define PORTE_PCR23                    (PORTE->PCR[23])
#define PORTE_PCR24                    (PORTE->PCR[24])
#define PORTE_PCR25                    (PORTE->PCR[25])
#define PORTE_PCR26                    (PORTE->PCR[26])
#define PORTE_PCR27                    (PORTE->PCR[27])
#define PORTE_PCR28                    (PORTE->PCR[28])
#define PORTE_PCR29                    (PORTE->PCR[29])
#define PORTE_PCR30                    (PORTE->PCR[30])
#define PORTE_PCR31                    (PORTE->PCR[31])
#define PORTE_GPCLR                    (PORTE->GPCLR)
#define PORTE_GPCHR                    (PORTE->GPCHR)
#define PORTE_ISFR                     (PORTE->ISFR)

/* ================================================================================ */
/* ================           RCM (file:RCM_MKL_BOOT)              ================ */
/* ================================================================================ */

/**
 * @brief Reset Control Module
 */
typedef struct {                                /*!<       RCM Structure                                                */
   __I  uint8_t   SRS0;                         /*!< 0000: System Reset Status Register 0                               */
   __I  uint8_t   SRS1;                         /*!< 0001: System Reset Status Register 1                               */
   __I  uint16_t  RESERVED0;                    /*!< 0002:                                                              */
   __IO uint8_t   RPFC;                         /*!< 0004: Reset Pin Filter Control Register                            */
   __IO uint8_t   RPFW;                         /*!< 0005: Reset Pin Filter Width Register                              */
   __IO uint8_t   FM;                           /*!< 0006: Force Mode Register                                          */
   __IO uint8_t   MR;                           /*!< 0007: Mode Register                                                */
   __IO uint8_t   SSRS0;                        /*!< 0008: Sticky System Reset Status Register 0                        */
   __IO uint8_t   SSRS1;                        /*!< 0009: Sticky System Reset Status Register 1                        */
} RCM_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'RCM' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- RCM_SRS0                                 ------ */
#define RCM_SRS0_WAKEUP_MASK                     (0x01UL << RCM_SRS0_WAKEUP_SHIFT)                   /*!< RCM_SRS0: WAKEUP Mask                   */
#define RCM_SRS0_WAKEUP_SHIFT                    0                                                   /*!< RCM_SRS0: WAKEUP Position               */
#define RCM_SRS0_LVD_MASK                        (0x01UL << RCM_SRS0_LVD_SHIFT)                      /*!< RCM_SRS0: LVD Mask                      */
#define RCM_SRS0_LVD_SHIFT                       1                                                   /*!< RCM_SRS0: LVD Position                  */
#define RCM_SRS0_WDOG_MASK                       (0x01UL << RCM_SRS0_WDOG_SHIFT)                     /*!< RCM_SRS0: WDOG Mask                     */
#define RCM_SRS0_WDOG_SHIFT                      5                                                   /*!< RCM_SRS0: WDOG Position                 */
#define RCM_SRS0_PIN_MASK                        (0x01UL << RCM_SRS0_PIN_SHIFT)                      /*!< RCM_SRS0: PIN Mask                      */
#define RCM_SRS0_PIN_SHIFT                       6                                                   /*!< RCM_SRS0: PIN Position                  */
#define RCM_SRS0_POR_MASK                        (0x01UL << RCM_SRS0_POR_SHIFT)                      /*!< RCM_SRS0: POR Mask                      */
#define RCM_SRS0_POR_SHIFT                       7                                                   /*!< RCM_SRS0: POR Position                  */

/* ------- RCM_SRS1                                 ------ */
#define RCM_SRS1_LOCKUP_MASK                     (0x01UL << RCM_SRS1_LOCKUP_SHIFT)                   /*!< RCM_SRS1: LOCKUP Mask                   */
#define RCM_SRS1_LOCKUP_SHIFT                    1                                                   /*!< RCM_SRS1: LOCKUP Position               */
#define RCM_SRS1_SW_MASK                         (0x01UL << RCM_SRS1_SW_SHIFT)                       /*!< RCM_SRS1: SW Mask                       */
#define RCM_SRS1_SW_SHIFT                        2                                                   /*!< RCM_SRS1: SW Position                   */
#define RCM_SRS1_MDM_AP_MASK                     (0x01UL << RCM_SRS1_MDM_AP_SHIFT)                   /*!< RCM_SRS1: MDM_AP Mask                   */
#define RCM_SRS1_MDM_AP_SHIFT                    3                                                   /*!< RCM_SRS1: MDM_AP Position               */
#define RCM_SRS1_SACKERR_MASK                    (0x01UL << RCM_SRS1_SACKERR_SHIFT)                  /*!< RCM_SRS1: SACKERR Mask                  */
#define RCM_SRS1_SACKERR_SHIFT                   5                                                   /*!< RCM_SRS1: SACKERR Position              */

/* ------- RCM_RPFC                                 ------ */
#define RCM_RPFC_RSTFLTSRW_MASK                  (0x03UL << RCM_RPFC_RSTFLTSRW_SHIFT)                /*!< RCM_RPFC: RSTFLTSRW Mask                */
#define RCM_RPFC_RSTFLTSRW_SHIFT                 0                                                   /*!< RCM_RPFC: RSTFLTSRW Position            */
#define RCM_RPFC_RSTFLTSRW(x)                    (((x)<<RCM_RPFC_RSTFLTSRW_SHIFT)&RCM_RPFC_RSTFLTSRW_MASK) /*!< RCM_RPFC                                */
#define RCM_RPFC_RSTFLTSS_MASK                   (0x01UL << RCM_RPFC_RSTFLTSS_SHIFT)                 /*!< RCM_RPFC: RSTFLTSS Mask                 */
#define RCM_RPFC_RSTFLTSS_SHIFT                  2                                                   /*!< RCM_RPFC: RSTFLTSS Position             */

/* ------- RCM_RPFW                                 ------ */
#define RCM_RPFW_RSTFLTSEL_MASK                  (0x1FUL << RCM_RPFW_RSTFLTSEL_SHIFT)                /*!< RCM_RPFW: RSTFLTSEL Mask                */
#define RCM_RPFW_RSTFLTSEL_SHIFT                 0                                                   /*!< RCM_RPFW: RSTFLTSEL Position            */
#define RCM_RPFW_RSTFLTSEL(x)                    (((x)<<RCM_RPFW_RSTFLTSEL_SHIFT)&RCM_RPFW_RSTFLTSEL_MASK) /*!< RCM_RPFW                                */

/* ------- RCM_FM                                   ------ */
#define RCM_FM_FORCEROM_MASK                     (0x03UL << RCM_FM_FORCEROM_SHIFT)                   /*!< RCM_FM: FORCEROM Mask                   */
#define RCM_FM_FORCEROM_SHIFT                    1                                                   /*!< RCM_FM: FORCEROM Position               */
#define RCM_FM_FORCEROM(x)                       (((x)<<RCM_FM_FORCEROM_SHIFT)&RCM_FM_FORCEROM_MASK) /*!< RCM_FM                                  */

/* ------- RCM_MR                                   ------ */
#define RCM_MR_BOOTROM_MASK                      (0x03UL << RCM_MR_BOOTROM_SHIFT)                    /*!< RCM_MR: BOOTROM Mask                    */
#define RCM_MR_BOOTROM_SHIFT                     1                                                   /*!< RCM_MR: BOOTROM Position                */
#define RCM_MR_BOOTROM(x)                        (((x)<<RCM_MR_BOOTROM_SHIFT)&RCM_MR_BOOTROM_MASK)   /*!< RCM_MR                                  */

/* ------- RCM_SSRS0                                ------ */
#define RCM_SSRS0_SWAKEUP_MASK                   (0x01UL << RCM_SSRS0_SWAKEUP_SHIFT)                 /*!< RCM_SSRS0: SWAKEUP Mask                 */
#define RCM_SSRS0_SWAKEUP_SHIFT                  0                                                   /*!< RCM_SSRS0: SWAKEUP Position             */
#define RCM_SSRS0_SLVD_MASK                      (0x01UL << RCM_SSRS0_SLVD_SHIFT)                    /*!< RCM_SSRS0: SLVD Mask                    */
#define RCM_SSRS0_SLVD_SHIFT                     1                                                   /*!< RCM_SSRS0: SLVD Position                */
#define RCM_SSRS0_SWDOG_MASK                     (0x01UL << RCM_SSRS0_SWDOG_SHIFT)                   /*!< RCM_SSRS0: SWDOG Mask                   */
#define RCM_SSRS0_SWDOG_SHIFT                    5                                                   /*!< RCM_SSRS0: SWDOG Position               */
#define RCM_SSRS0_SPIN_MASK                      (0x01UL << RCM_SSRS0_SPIN_SHIFT)                    /*!< RCM_SSRS0: SPIN Mask                    */
#define RCM_SSRS0_SPIN_SHIFT                     6                                                   /*!< RCM_SSRS0: SPIN Position                */
#define RCM_SSRS0_SPOR_MASK                      (0x01UL << RCM_SSRS0_SPOR_SHIFT)                    /*!< RCM_SSRS0: SPOR Mask                    */
#define RCM_SSRS0_SPOR_SHIFT                     7                                                   /*!< RCM_SSRS0: SPOR Position                */

/* ------- RCM_SSRS1                                ------ */
#define RCM_SSRS1_SLOCKUP_MASK                   (0x01UL << RCM_SSRS1_SLOCKUP_SHIFT)                 /*!< RCM_SSRS1: SLOCKUP Mask                 */
#define RCM_SSRS1_SLOCKUP_SHIFT                  1                                                   /*!< RCM_SSRS1: SLOCKUP Position             */
#define RCM_SSRS1_SSW_MASK                       (0x01UL << RCM_SSRS1_SSW_SHIFT)                     /*!< RCM_SSRS1: SSW Mask                     */
#define RCM_SSRS1_SSW_SHIFT                      2                                                   /*!< RCM_SSRS1: SSW Position                 */
#define RCM_SSRS1_SMDM_AP_MASK                   (0x01UL << RCM_SSRS1_SMDM_AP_SHIFT)                 /*!< RCM_SSRS1: SMDM_AP Mask                 */
#define RCM_SSRS1_SMDM_AP_SHIFT                  3                                                   /*!< RCM_SSRS1: SMDM_AP Position             */
#define RCM_SSRS1_SSACKERR_MASK                  (0x01UL << RCM_SSRS1_SSACKERR_SHIFT)                /*!< RCM_SSRS1: SSACKERR Mask                */
#define RCM_SSRS1_SSACKERR_SHIFT                 5                                                   /*!< RCM_SSRS1: SSACKERR Position            */

/* -------------------------------------------------------------------------------- */
/* -----------     'RCM' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define RCM_SRS0                       (RCM->SRS0)
#define RCM_SRS1                       (RCM->SRS1)
#define RCM_RPFC                       (RCM->RPFC)
#define RCM_RPFW                       (RCM->RPFW)
#define RCM_FM                         (RCM->FM)
#define RCM_MR                         (RCM->MR)
#define RCM_SSRS0                      (RCM->SSRS0)
#define RCM_SSRS1                      (RCM->SSRS1)

/* ================================================================================ */
/* ================           ROM (file:ROM_MKL)                   ================ */
/* ================================================================================ */

/**
 * @brief System ROM
 */
typedef struct {                                /*!<       ROM Structure                                                */
   __I  uint32_t  ENTRY[3];                     /*!< 0000: Entry                                                        */
   __I  uint32_t  TABLEMARK;                    /*!< 000C: End of Table Marker Register                                 */
   __I  uint32_t  RESERVED0[1007];              /*!< 0010:                                                              */
   __I  uint32_t  SYSACCESS;                    /*!< 0FCC: System Access Register                                       */
   __I  uint32_t  PERIPHID4;                    /*!< 0FD0: Peripheral ID Register                                       */
   __I  uint32_t  PERIPHID5;                    /*!< 0FD4: Peripheral ID Register                                       */
   __I  uint32_t  PERIPHID6;                    /*!< 0FD8: Peripheral ID Register                                       */
   __I  uint32_t  PERIPHID7;                    /*!< 0FDC: Peripheral ID Register                                       */
   __I  uint32_t  PERIPHID0;                    /*!< 0FE0: Peripheral ID Register                                       */
   __I  uint32_t  PERIPHID1;                    /*!< 0FE4: Peripheral ID Register                                       */
   __I  uint32_t  PERIPHID2;                    /*!< 0FE8: Peripheral ID Register                                       */
   __I  uint32_t  PERIPHID3;                    /*!< 0FEC: Peripheral ID Register                                       */
   __I  uint32_t  COMPID[4];                    /*!< 0FF0: Component ID Register                                        */
} ROM_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'ROM' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- ROM_ENTRY                                ------ */
#define ROM_ENTRY_ENTRY_MASK                     (0xFFFFFFFFUL << ROM_ENTRY_ENTRY_SHIFT)             /*!< ROM_ENTRY: ENTRY Mask                   */
#define ROM_ENTRY_ENTRY_SHIFT                    0                                                   /*!< ROM_ENTRY: ENTRY Position               */
#define ROM_ENTRY_ENTRY(x)                       (((x)<<ROM_ENTRY_ENTRY_SHIFT)&ROM_ENTRY_ENTRY_MASK) /*!< ROM_ENTRY                               */

/* ------- ROM_TABLEMARK                            ------ */
#define ROM_TABLEMARK_MARK_MASK                  (0xFFFFFFFFUL << ROM_TABLEMARK_MARK_SHIFT)          /*!< ROM_TABLEMARK: MARK Mask                */
#define ROM_TABLEMARK_MARK_SHIFT                 0                                                   /*!< ROM_TABLEMARK: MARK Position            */
#define ROM_TABLEMARK_MARK(x)                    (((x)<<ROM_TABLEMARK_MARK_SHIFT)&ROM_TABLEMARK_MARK_MASK) /*!< ROM_TABLEMARK                           */

/* ------- ROM_SYSACCESS                            ------ */
#define ROM_SYSACCESS_SYSACCESS_MASK             (0xFFFFFFFFUL << ROM_SYSACCESS_SYSACCESS_SHIFT)     /*!< ROM_SYSACCESS: SYSACCESS Mask           */
#define ROM_SYSACCESS_SYSACCESS_SHIFT            0                                                   /*!< ROM_SYSACCESS: SYSACCESS Position       */
#define ROM_SYSACCESS_SYSACCESS(x)               (((x)<<ROM_SYSACCESS_SYSACCESS_SHIFT)&ROM_SYSACCESS_SYSACCESS_MASK) /*!< ROM_SYSACCESS                           */

/* ------- ROM_PERIPHID                             ------ */
#define ROM_PERIPHID_PERIPHID_MASK               (0xFFFFFFFFUL << ROM_PERIPHID_PERIPHID_SHIFT)       /*!< ROM_PERIPHID: PERIPHID Mask             */
#define ROM_PERIPHID_PERIPHID_SHIFT              0                                                   /*!< ROM_PERIPHID: PERIPHID Position         */
#define ROM_PERIPHID_PERIPHID(x)                 (((x)<<ROM_PERIPHID_PERIPHID_SHIFT)&ROM_PERIPHID_PERIPHID_MASK) /*!< ROM_PERIPHID                            */

/* ------- ROM_COMPID                               ------ */
#define ROM_COMPID_COMPID_MASK                   (0xFFFFFFFFUL << ROM_COMPID_COMPID_SHIFT)           /*!< ROM_COMPID: COMPID Mask                 */
#define ROM_COMPID_COMPID_SHIFT                  0                                                   /*!< ROM_COMPID: COMPID Position             */
#define ROM_COMPID_COMPID(x)                     (((x)<<ROM_COMPID_COMPID_SHIFT)&ROM_COMPID_COMPID_MASK) /*!< ROM_COMPID                              */

/* -------------------------------------------------------------------------------- */
/* -----------     'ROM' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define ROM_ENTRY0                     (ROM->ENTRY[0])
#define ROM_ENTRY1                     (ROM->ENTRY[1])
#define ROM_ENTRY2                     (ROM->ENTRY[2])
#define ROM_TABLEMARK                  (ROM->TABLEMARK)
#define ROM_SYSACCESS                  (ROM->SYSACCESS)
#define ROM_PERIPHID4                  (ROM->PERIPHID4)
#define ROM_PERIPHID5                  (ROM->PERIPHID5)
#define ROM_PERIPHID6                  (ROM->PERIPHID6)
#define ROM_PERIPHID7                  (ROM->PERIPHID7)
#define ROM_PERIPHID0                  (ROM->PERIPHID0)
#define ROM_PERIPHID1                  (ROM->PERIPHID1)
#define ROM_PERIPHID2                  (ROM->PERIPHID2)
#define ROM_PERIPHID3                  (ROM->PERIPHID3)
#define ROM_COMPID0                    (ROM->COMPID[0])
#define ROM_COMPID1                    (ROM->COMPID[1])
#define ROM_COMPID2                    (ROM->COMPID[2])
#define ROM_COMPID3                    (ROM->COMPID[3])

/* ================================================================================ */
/* ================           RTC (file:RTC)                       ================ */
/* ================================================================================ */

/**
 * @brief Secure Real Time Clock
 */
typedef struct {                                /*!<       RTC Structure                                                */
   __IO uint32_t  TSR;                          /*!< 0000: Time Seconds Register                                        */
   __IO uint32_t  TPR;                          /*!< 0004: Time Prescaler Register                                      */
   __IO uint32_t  TAR;                          /*!< 0008: Time Alarm Register                                          */
   __IO uint32_t  TCR;                          /*!< 000C: Time Compensation Register                                   */
   __IO uint32_t  CR;                           /*!< 0010: Control Register                                             */
   __IO uint32_t  SR;                           /*!< 0014: Status Register                                              */
   __IO uint32_t  LR;                           /*!< 0018: Lock Register                                                */
   __IO uint32_t  IER;                          /*!< 001C: Interrupt Enable Register                                    */
} RTC_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'RTC' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- RTC_TSR                                  ------ */
#define RTC_TSR_TSR_MASK                         (0xFFFFFFFFUL << RTC_TSR_TSR_SHIFT)                 /*!< RTC_TSR: TSR Mask                       */
#define RTC_TSR_TSR_SHIFT                        0                                                   /*!< RTC_TSR: TSR Position                   */
#define RTC_TSR_TSR(x)                           (((x)<<RTC_TSR_TSR_SHIFT)&RTC_TSR_TSR_MASK)         /*!< RTC_TSR                                 */

/* ------- RTC_TPR                                  ------ */
#define RTC_TPR_TPR_MASK                         (0xFFFFUL << RTC_TPR_TPR_SHIFT)                     /*!< RTC_TPR: TPR Mask                       */
#define RTC_TPR_TPR_SHIFT                        0                                                   /*!< RTC_TPR: TPR Position                   */
#define RTC_TPR_TPR(x)                           (((x)<<RTC_TPR_TPR_SHIFT)&RTC_TPR_TPR_MASK)         /*!< RTC_TPR                                 */

/* ------- RTC_TAR                                  ------ */
#define RTC_TAR_TAR_MASK                         (0xFFFFFFFFUL << RTC_TAR_TAR_SHIFT)                 /*!< RTC_TAR: TAR Mask                       */
#define RTC_TAR_TAR_SHIFT                        0                                                   /*!< RTC_TAR: TAR Position                   */
#define RTC_TAR_TAR(x)                           (((x)<<RTC_TAR_TAR_SHIFT)&RTC_TAR_TAR_MASK)         /*!< RTC_TAR                                 */

/* ------- RTC_TCR                                  ------ */
#define RTC_TCR_TCR_MASK                         (0xFFUL << RTC_TCR_TCR_SHIFT)                       /*!< RTC_TCR: TCR Mask                       */
#define RTC_TCR_TCR_SHIFT                        0                                                   /*!< RTC_TCR: TCR Position                   */
#define RTC_TCR_TCR(x)                           (((x)<<RTC_TCR_TCR_SHIFT)&RTC_TCR_TCR_MASK)         /*!< RTC_TCR                                 */
#define RTC_TCR_CIR_MASK                         (0xFFUL << RTC_TCR_CIR_SHIFT)                       /*!< RTC_TCR: CIR Mask                       */
#define RTC_TCR_CIR_SHIFT                        8                                                   /*!< RTC_TCR: CIR Position                   */
#define RTC_TCR_CIR(x)                           (((x)<<RTC_TCR_CIR_SHIFT)&RTC_TCR_CIR_MASK)         /*!< RTC_TCR                                 */
#define RTC_TCR_TCV_MASK                         (0xFFUL << RTC_TCR_TCV_SHIFT)                       /*!< RTC_TCR: TCV Mask                       */
#define RTC_TCR_TCV_SHIFT                        16                                                  /*!< RTC_TCR: TCV Position                   */
#define RTC_TCR_TCV(x)                           (((x)<<RTC_TCR_TCV_SHIFT)&RTC_TCR_TCV_MASK)         /*!< RTC_TCR                                 */
#define RTC_TCR_CIC_MASK                         (0xFFUL << RTC_TCR_CIC_SHIFT)                       /*!< RTC_TCR: CIC Mask                       */
#define RTC_TCR_CIC_SHIFT                        24                                                  /*!< RTC_TCR: CIC Position                   */
#define RTC_TCR_CIC(x)                           (((x)<<RTC_TCR_CIC_SHIFT)&RTC_TCR_CIC_MASK)         /*!< RTC_TCR                                 */

/* ------- RTC_CR                                   ------ */
#define RTC_CR_SWR_MASK                          (0x01UL << RTC_CR_SWR_SHIFT)                        /*!< RTC_CR: SWR Mask                        */
#define RTC_CR_SWR_SHIFT                         0                                                   /*!< RTC_CR: SWR Position                    */
#define RTC_CR_WPE_MASK                          (0x01UL << RTC_CR_WPE_SHIFT)                        /*!< RTC_CR: WPE Mask                        */
#define RTC_CR_WPE_SHIFT                         1                                                   /*!< RTC_CR: WPE Position                    */
#define RTC_CR_SUP_MASK                          (0x01UL << RTC_CR_SUP_SHIFT)                        /*!< RTC_CR: SUP Mask                        */
#define RTC_CR_SUP_SHIFT                         2                                                   /*!< RTC_CR: SUP Position                    */
#define RTC_CR_UM_MASK                           (0x01UL << RTC_CR_UM_SHIFT)                         /*!< RTC_CR: UM Mask                         */
#define RTC_CR_UM_SHIFT                          3                                                   /*!< RTC_CR: UM Position                     */
#define RTC_CR_WPS_MASK                          (0x01UL << RTC_CR_WPS_SHIFT)                        /*!< RTC_CR: WPS Mask                        */
#define RTC_CR_WPS_SHIFT                         4                                                   /*!< RTC_CR: WPS Position                    */
#define RTC_CR_OSCE_MASK                         (0x01UL << RTC_CR_OSCE_SHIFT)                       /*!< RTC_CR: OSCE Mask                       */
#define RTC_CR_OSCE_SHIFT                        8                                                   /*!< RTC_CR: OSCE Position                   */
#define RTC_CR_CLKO_MASK                         (0x01UL << RTC_CR_CLKO_SHIFT)                       /*!< RTC_CR: CLKO Mask                       */
#define RTC_CR_CLKO_SHIFT                        9                                                   /*!< RTC_CR: CLKO Position                   */
#define RTC_CR_SC16P_MASK                        (0x01UL << RTC_CR_SC16P_SHIFT)                      /*!< RTC_CR: SC16P Mask                      */
#define RTC_CR_SC16P_SHIFT                       10                                                  /*!< RTC_CR: SC16P Position                  */
#define RTC_CR_SC8P_MASK                         (0x01UL << RTC_CR_SC8P_SHIFT)                       /*!< RTC_CR: SC8P Mask                       */
#define RTC_CR_SC8P_SHIFT                        11                                                  /*!< RTC_CR: SC8P Position                   */
#define RTC_CR_SC4P_MASK                         (0x01UL << RTC_CR_SC4P_SHIFT)                       /*!< RTC_CR: SC4P Mask                       */
#define RTC_CR_SC4P_SHIFT                        12                                                  /*!< RTC_CR: SC4P Position                   */
#define RTC_CR_SC2P_MASK                         (0x01UL << RTC_CR_SC2P_SHIFT)                       /*!< RTC_CR: SC2P Mask                       */
#define RTC_CR_SC2P_SHIFT                        13                                                  /*!< RTC_CR: SC2P Position                   */

/* ------- RTC_SR                                   ------ */
#define RTC_SR_TIF_MASK                          (0x01UL << RTC_SR_TIF_SHIFT)                        /*!< RTC_SR: TIF Mask                        */
#define RTC_SR_TIF_SHIFT                         0                                                   /*!< RTC_SR: TIF Position                    */
#define RTC_SR_TOF_MASK                          (0x01UL << RTC_SR_TOF_SHIFT)                        /*!< RTC_SR: TOF Mask                        */
#define RTC_SR_TOF_SHIFT                         1                                                   /*!< RTC_SR: TOF Position                    */
#define RTC_SR_TAF_MASK                          (0x01UL << RTC_SR_TAF_SHIFT)                        /*!< RTC_SR: TAF Mask                        */
#define RTC_SR_TAF_SHIFT                         2                                                   /*!< RTC_SR: TAF Position                    */
#define RTC_SR_TCE_MASK                          (0x01UL << RTC_SR_TCE_SHIFT)                        /*!< RTC_SR: TCE Mask                        */
#define RTC_SR_TCE_SHIFT                         4                                                   /*!< RTC_SR: TCE Position                    */

/* ------- RTC_LR                                   ------ */
#define RTC_LR_TCL_MASK                          (0x01UL << RTC_LR_TCL_SHIFT)                        /*!< RTC_LR: TCL Mask                        */
#define RTC_LR_TCL_SHIFT                         3                                                   /*!< RTC_LR: TCL Position                    */
#define RTC_LR_CRL_MASK                          (0x01UL << RTC_LR_CRL_SHIFT)                        /*!< RTC_LR: CRL Mask                        */
#define RTC_LR_CRL_SHIFT                         4                                                   /*!< RTC_LR: CRL Position                    */
#define RTC_LR_SRL_MASK                          (0x01UL << RTC_LR_SRL_SHIFT)                        /*!< RTC_LR: SRL Mask                        */
#define RTC_LR_SRL_SHIFT                         5                                                   /*!< RTC_LR: SRL Position                    */
#define RTC_LR_LRL_MASK                          (0x01UL << RTC_LR_LRL_SHIFT)                        /*!< RTC_LR: LRL Mask                        */
#define RTC_LR_LRL_SHIFT                         6                                                   /*!< RTC_LR: LRL Position                    */

/* ------- RTC_IER                                  ------ */
#define RTC_IER_TIIE_MASK                        (0x01UL << RTC_IER_TIIE_SHIFT)                      /*!< RTC_IER: TIIE Mask                      */
#define RTC_IER_TIIE_SHIFT                       0                                                   /*!< RTC_IER: TIIE Position                  */
#define RTC_IER_TOIE_MASK                        (0x01UL << RTC_IER_TOIE_SHIFT)                      /*!< RTC_IER: TOIE Mask                      */
#define RTC_IER_TOIE_SHIFT                       1                                                   /*!< RTC_IER: TOIE Position                  */
#define RTC_IER_TAIE_MASK                        (0x01UL << RTC_IER_TAIE_SHIFT)                      /*!< RTC_IER: TAIE Mask                      */
#define RTC_IER_TAIE_SHIFT                       2                                                   /*!< RTC_IER: TAIE Position                  */
#define RTC_IER_TSIE_MASK                        (0x01UL << RTC_IER_TSIE_SHIFT)                      /*!< RTC_IER: TSIE Mask                      */
#define RTC_IER_TSIE_SHIFT                       4                                                   /*!< RTC_IER: TSIE Position                  */
#define RTC_IER_WPON_MASK                        (0x01UL << RTC_IER_WPON_SHIFT)                      /*!< RTC_IER: WPON Mask                      */
#define RTC_IER_WPON_SHIFT                       7                                                   /*!< RTC_IER: WPON Position                  */

/* -------------------------------------------------------------------------------- */
/* -----------     'RTC' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define RTC_TSR                        (RTC->TSR)
#define RTC_TPR                        (RTC->TPR)
#define RTC_TAR                        (RTC->TAR)
#define RTC_TCR                        (RTC->TCR)
#define RTC_CR                         (RTC->CR)
#define RTC_SR                         (RTC->SR)
#define RTC_LR                         (RTC->LR)
#define RTC_IER                        (RTC->IER)

/* ================================================================================ */
/* ================           SIM (file:SIM_MKL43Z4)               ================ */
/* ================================================================================ */

/**
 * @brief System Integration Module
 */
typedef struct {                                /*!<       SIM Structure                                                */
   __IO uint32_t  SOPT1;                        /*!< 0000: System Options Register 1                                    */
   __IO uint32_t  SOPT1CFG;                     /*!< 0004: SOPT1 Configuration Register                                 */
   __I  uint32_t  RESERVED0[1023];              /*!< 0008:                                                              */
   __IO uint32_t  SOPT2;                        /*!< 1004: System Options Register 2                                    */
   __I  uint32_t  RESERVED1;                    /*!< 1008:                                                              */
   __IO uint32_t  SOPT4;                        /*!< 100C: System Options Register 4                                    */
   __IO uint32_t  SOPT5;                        /*!< 1010: System Options Register 5                                    */
   __I  uint32_t  RESERVED2;                    /*!< 1014:                                                              */
   __IO uint32_t  SOPT7;                        /*!< 1018: System Options Register 7                                    */
   __I  uint32_t  RESERVED3[2];                 /*!< 101C:                                                              */
   __I  uint32_t  SDID;                         /*!< 1024: System Device Identification Register                        */
   __I  uint32_t  RESERVED4[3];                 /*!< 1028:                                                              */
   __IO uint32_t  SCGC4;                        /*!< 1034: System Clock Gating Control Register 4                       */
   __IO uint32_t  SCGC5;                        /*!< 1038: System Clock Gating Control Register 5                       */
   __IO uint32_t  SCGC6;                        /*!< 103C: System Clock Gating Control Register 6                       */
   __IO uint32_t  SCGC7;                        /*!< 1040: System Clock Gating Control Register 7                       */
   __IO uint32_t  CLKDIV1;                      /*!< 1044: System Clock Divider Register 1                              */
   __I  uint32_t  RESERVED5;                    /*!< 1048:                                                              */
   __IO uint32_t  FCFG1;                        /*!< 104C: Flash Configuration Register 1                               */
   __I  uint32_t  FCFG2;                        /*!< 1050: Flash Configuration Register 2                               */
   __I  uint32_t  RESERVED6;                    /*!< 1054:                                                              */
   __I  uint32_t  UIDMH;                        /*!< 1058: Unique Identification Register Mid-High                      */
   __I  uint32_t  UIDML;                        /*!< 105C: Unique Identification Register Mid Low                       */
   __I  uint32_t  UIDL;                         /*!< 1060: Unique Identification Register Low                           */
   __I  uint32_t  RESERVED7[39];                /*!< 1064:                                                              */
   __IO uint32_t  COPC;                         /*!< 1100: COP Control Register                                         */
   __O  uint32_t  SRVCOP;                       /*!< 1104: Service COP Register                                         */
} SIM_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'SIM' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- SIM_SOPT1                                ------ */
#define SIM_SOPT1_OSC32KOUT_MASK                 (0x03UL << SIM_SOPT1_OSC32KOUT_SHIFT)               /*!< SIM_SOPT1: OSC32KOUT Mask               */
#define SIM_SOPT1_OSC32KOUT_SHIFT                16                                                  /*!< SIM_SOPT1: OSC32KOUT Position           */
#define SIM_SOPT1_OSC32KOUT(x)                   (((x)<<SIM_SOPT1_OSC32KOUT_SHIFT)&SIM_SOPT1_OSC32KOUT_MASK) /*!< SIM_SOPT1                               */
#define SIM_SOPT1_OSC32KSEL_MASK                 (0x03UL << SIM_SOPT1_OSC32KSEL_SHIFT)               /*!< SIM_SOPT1: OSC32KSEL Mask               */
#define SIM_SOPT1_OSC32KSEL_SHIFT                18                                                  /*!< SIM_SOPT1: OSC32KSEL Position           */
#define SIM_SOPT1_OSC32KSEL(x)                   (((x)<<SIM_SOPT1_OSC32KSEL_SHIFT)&SIM_SOPT1_OSC32KSEL_MASK) /*!< SIM_SOPT1                               */
#define SIM_SOPT1_USBVSTBY_MASK                  (0x01UL << SIM_SOPT1_USBVSTBY_SHIFT)                /*!< SIM_SOPT1: USBVSTBY Mask                */
#define SIM_SOPT1_USBVSTBY_SHIFT                 29                                                  /*!< SIM_SOPT1: USBVSTBY Position            */
#define SIM_SOPT1_USBSSTBY_MASK                  (0x01UL << SIM_SOPT1_USBSSTBY_SHIFT)                /*!< SIM_SOPT1: USBSSTBY Mask                */
#define SIM_SOPT1_USBSSTBY_SHIFT                 30                                                  /*!< SIM_SOPT1: USBSSTBY Position            */
#define SIM_SOPT1_USBREGEN_MASK                  (0x01UL << SIM_SOPT1_USBREGEN_SHIFT)                /*!< SIM_SOPT1: USBREGEN Mask                */
#define SIM_SOPT1_USBREGEN_SHIFT                 31                                                  /*!< SIM_SOPT1: USBREGEN Position            */

/* ------- SIM_SOPT1CFG                             ------ */
#define SIM_SOPT1CFG_URWE_MASK                   (0x01UL << SIM_SOPT1CFG_URWE_SHIFT)                 /*!< SIM_SOPT1CFG: URWE Mask                 */
#define SIM_SOPT1CFG_URWE_SHIFT                  24                                                  /*!< SIM_SOPT1CFG: URWE Position             */
#define SIM_SOPT1CFG_UVSWE_MASK                  (0x01UL << SIM_SOPT1CFG_UVSWE_SHIFT)                /*!< SIM_SOPT1CFG: UVSWE Mask                */
#define SIM_SOPT1CFG_UVSWE_SHIFT                 25                                                  /*!< SIM_SOPT1CFG: UVSWE Position            */
#define SIM_SOPT1CFG_USSWE_MASK                  (0x01UL << SIM_SOPT1CFG_USSWE_SHIFT)                /*!< SIM_SOPT1CFG: USSWE Mask                */
#define SIM_SOPT1CFG_USSWE_SHIFT                 26                                                  /*!< SIM_SOPT1CFG: USSWE Position            */

/* ------- SIM_SOPT2                                ------ */
#define SIM_SOPT2_RTCCLKOUTSEL_MASK              (0x01UL << SIM_SOPT2_RTCCLKOUTSEL_SHIFT)            /*!< SIM_SOPT2: RTCCLKOUTSEL Mask            */
#define SIM_SOPT2_RTCCLKOUTSEL_SHIFT             4                                                   /*!< SIM_SOPT2: RTCCLKOUTSEL Position        */
#define SIM_SOPT2_CLKOUTSEL_MASK                 (0x07UL << SIM_SOPT2_CLKOUTSEL_SHIFT)               /*!< SIM_SOPT2: CLKOUTSEL Mask               */
#define SIM_SOPT2_CLKOUTSEL_SHIFT                5                                                   /*!< SIM_SOPT2: CLKOUTSEL Position           */
#define SIM_SOPT2_CLKOUTSEL(x)                   (((x)<<SIM_SOPT2_CLKOUTSEL_SHIFT)&SIM_SOPT2_CLKOUTSEL_MASK) /*!< SIM_SOPT2                               */
#define SIM_SOPT2_USBSRC_MASK                    (0x01UL << SIM_SOPT2_USBSRC_SHIFT)                  /*!< SIM_SOPT2: USBSRC Mask                  */
#define SIM_SOPT2_USBSRC_SHIFT                   18                                                  /*!< SIM_SOPT2: USBSRC Position              */
#define SIM_SOPT2_FLEXIOSRC_MASK                 (0x03UL << SIM_SOPT2_FLEXIOSRC_SHIFT)               /*!< SIM_SOPT2: FLEXIOSRC Mask               */
#define SIM_SOPT2_FLEXIOSRC_SHIFT                22                                                  /*!< SIM_SOPT2: FLEXIOSRC Position           */
#define SIM_SOPT2_FLEXIOSRC(x)                   (((x)<<SIM_SOPT2_FLEXIOSRC_SHIFT)&SIM_SOPT2_FLEXIOSRC_MASK) /*!< SIM_SOPT2                               */
#define SIM_SOPT2_TPMSRC_MASK                    (0x03UL << SIM_SOPT2_TPMSRC_SHIFT)                  /*!< SIM_SOPT2: TPMSRC Mask                  */
#define SIM_SOPT2_TPMSRC_SHIFT                   24                                                  /*!< SIM_SOPT2: TPMSRC Position              */
#define SIM_SOPT2_TPMSRC(x)                      (((x)<<SIM_SOPT2_TPMSRC_SHIFT)&SIM_SOPT2_TPMSRC_MASK) /*!< SIM_SOPT2                               */
#define SIM_SOPT2_LPUART0SRC_MASK                (0x03UL << SIM_SOPT2_LPUART0SRC_SHIFT)              /*!< SIM_SOPT2: LPUART0SRC Mask              */
#define SIM_SOPT2_LPUART0SRC_SHIFT               26                                                  /*!< SIM_SOPT2: LPUART0SRC Position          */
#define SIM_SOPT2_LPUART0SRC(x)                  (((x)<<SIM_SOPT2_LPUART0SRC_SHIFT)&SIM_SOPT2_LPUART0SRC_MASK) /*!< SIM_SOPT2                               */
#define SIM_SOPT2_LPUART1SRC_MASK                (0x03UL << SIM_SOPT2_LPUART1SRC_SHIFT)              /*!< SIM_SOPT2: LPUART1SRC Mask              */
#define SIM_SOPT2_LPUART1SRC_SHIFT               28                                                  /*!< SIM_SOPT2: LPUART1SRC Position          */
#define SIM_SOPT2_LPUART1SRC(x)                  (((x)<<SIM_SOPT2_LPUART1SRC_SHIFT)&SIM_SOPT2_LPUART1SRC_MASK) /*!< SIM_SOPT2                               */

/* ------- SIM_SOPT4                                ------ */
#define SIM_SOPT4_TPM1CH0SRC_MASK                (0x03UL << SIM_SOPT4_TPM1CH0SRC_SHIFT)              /*!< SIM_SOPT4: TPM1CH0SRC Mask              */
#define SIM_SOPT4_TPM1CH0SRC_SHIFT               18                                                  /*!< SIM_SOPT4: TPM1CH0SRC Position          */
#define SIM_SOPT4_TPM1CH0SRC(x)                  (((x)<<SIM_SOPT4_TPM1CH0SRC_SHIFT)&SIM_SOPT4_TPM1CH0SRC_MASK) /*!< SIM_SOPT4                               */
#define SIM_SOPT4_TPM2CH0SRC_MASK                (0x01UL << SIM_SOPT4_TPM2CH0SRC_SHIFT)              /*!< SIM_SOPT4: TPM2CH0SRC Mask              */
#define SIM_SOPT4_TPM2CH0SRC_SHIFT               20                                                  /*!< SIM_SOPT4: TPM2CH0SRC Position          */
#define SIM_SOPT4_TPM0CLKSEL_MASK                (0x01UL << SIM_SOPT4_TPM0CLKSEL_SHIFT)              /*!< SIM_SOPT4: TPM0CLKSEL Mask              */
#define SIM_SOPT4_TPM0CLKSEL_SHIFT               24                                                  /*!< SIM_SOPT4: TPM0CLKSEL Position          */
#define SIM_SOPT4_TPM1CLKSEL_MASK                (0x01UL << SIM_SOPT4_TPM1CLKSEL_SHIFT)              /*!< SIM_SOPT4: TPM1CLKSEL Mask              */
#define SIM_SOPT4_TPM1CLKSEL_SHIFT               25                                                  /*!< SIM_SOPT4: TPM1CLKSEL Position          */
#define SIM_SOPT4_TPM2CLKSEL_MASK                (0x01UL << SIM_SOPT4_TPM2CLKSEL_SHIFT)              /*!< SIM_SOPT4: TPM2CLKSEL Mask              */
#define SIM_SOPT4_TPM2CLKSEL_SHIFT               26                                                  /*!< SIM_SOPT4: TPM2CLKSEL Position          */

/* ------- SIM_SOPT5                                ------ */
#define SIM_SOPT5_LPUART0TXSRC_MASK              (0x03UL << SIM_SOPT5_LPUART0TXSRC_SHIFT)            /*!< SIM_SOPT5: LPUART0TXSRC Mask            */
#define SIM_SOPT5_LPUART0TXSRC_SHIFT             0                                                   /*!< SIM_SOPT5: LPUART0TXSRC Position        */
#define SIM_SOPT5_LPUART0TXSRC(x)                (((x)<<SIM_SOPT5_LPUART0TXSRC_SHIFT)&SIM_SOPT5_LPUART0TXSRC_MASK) /*!< SIM_SOPT5                               */
#define SIM_SOPT5_LPUART0RXSRC_MASK              (0x01UL << SIM_SOPT5_LPUART0RXSRC_SHIFT)            /*!< SIM_SOPT5: LPUART0RXSRC Mask            */
#define SIM_SOPT5_LPUART0RXSRC_SHIFT             2                                                   /*!< SIM_SOPT5: LPUART0RXSRC Position        */
#define SIM_SOPT5_LPUART1TXSRC_MASK              (0x03UL << SIM_SOPT5_LPUART1TXSRC_SHIFT)            /*!< SIM_SOPT5: LPUART1TXSRC Mask            */
#define SIM_SOPT5_LPUART1TXSRC_SHIFT             4                                                   /*!< SIM_SOPT5: LPUART1TXSRC Position        */
#define SIM_SOPT5_LPUART1TXSRC(x)                (((x)<<SIM_SOPT5_LPUART1TXSRC_SHIFT)&SIM_SOPT5_LPUART1TXSRC_MASK) /*!< SIM_SOPT5                               */
#define SIM_SOPT5_LPUART1RXSRC_MASK              (0x01UL << SIM_SOPT5_LPUART1RXSRC_SHIFT)            /*!< SIM_SOPT5: LPUART1RXSRC Mask            */
#define SIM_SOPT5_LPUART1RXSRC_SHIFT             6                                                   /*!< SIM_SOPT5: LPUART1RXSRC Position        */
#define SIM_SOPT5_LPUART0ODE_MASK                (0x01UL << SIM_SOPT5_LPUART0ODE_SHIFT)              /*!< SIM_SOPT5: LPUART0ODE Mask              */
#define SIM_SOPT5_LPUART0ODE_SHIFT               16                                                  /*!< SIM_SOPT5: LPUART0ODE Position          */
#define SIM_SOPT5_LPUART1ODE_MASK                (0x01UL << SIM_SOPT5_LPUART1ODE_SHIFT)              /*!< SIM_SOPT5: LPUART1ODE Mask              */
#define SIM_SOPT5_LPUART1ODE_SHIFT               17                                                  /*!< SIM_SOPT5: LPUART1ODE Position          */
#define SIM_SOPT5_UART2ODE_MASK                  (0x01UL << SIM_SOPT5_UART2ODE_SHIFT)                /*!< SIM_SOPT5: UART2ODE Mask                */
#define SIM_SOPT5_UART2ODE_SHIFT                 18                                                  /*!< SIM_SOPT5: UART2ODE Position            */

/* ------- SIM_SOPT7                                ------ */
#define SIM_SOPT7_ADC0TRGSEL_MASK                (0x0FUL << SIM_SOPT7_ADC0TRGSEL_SHIFT)              /*!< SIM_SOPT7: ADC0TRGSEL Mask              */
#define SIM_SOPT7_ADC0TRGSEL_SHIFT               0                                                   /*!< SIM_SOPT7: ADC0TRGSEL Position          */
#define SIM_SOPT7_ADC0TRGSEL(x)                  (((x)<<SIM_SOPT7_ADC0TRGSEL_SHIFT)&SIM_SOPT7_ADC0TRGSEL_MASK) /*!< SIM_SOPT7                               */
#define SIM_SOPT7_ADC0PRETRGSEL_MASK             (0x01UL << SIM_SOPT7_ADC0PRETRGSEL_SHIFT)           /*!< SIM_SOPT7: ADC0PRETRGSEL Mask           */
#define SIM_SOPT7_ADC0PRETRGSEL_SHIFT            4                                                   /*!< SIM_SOPT7: ADC0PRETRGSEL Position       */
#define SIM_SOPT7_ADC0ALTTRGEN_MASK              (0x01UL << SIM_SOPT7_ADC0ALTTRGEN_SHIFT)            /*!< SIM_SOPT7: ADC0ALTTRGEN Mask            */
#define SIM_SOPT7_ADC0ALTTRGEN_SHIFT             7                                                   /*!< SIM_SOPT7: ADC0ALTTRGEN Position        */

/* ------- SIM_SDID                                 ------ */
#define SIM_SDID_PINID_MASK                      (0x0FUL << SIM_SDID_PINID_SHIFT)                    /*!< SIM_SDID: PINID Mask                    */
#define SIM_SDID_PINID_SHIFT                     0                                                   /*!< SIM_SDID: PINID Position                */
#define SIM_SDID_PINID(x)                        (((x)<<SIM_SDID_PINID_SHIFT)&SIM_SDID_PINID_MASK)   /*!< SIM_SDID                                */
#define SIM_SDID_DIEID_MASK                      (0x1FUL << SIM_SDID_DIEID_SHIFT)                    /*!< SIM_SDID: DIEID Mask                    */
#define SIM_SDID_DIEID_SHIFT                     7                                                   /*!< SIM_SDID: DIEID Position                */
#define SIM_SDID_DIEID(x)                        (((x)<<SIM_SDID_DIEID_SHIFT)&SIM_SDID_DIEID_MASK)   /*!< SIM_SDID                                */
#define SIM_SDID_REVID_MASK                      (0x0FUL << SIM_SDID_REVID_SHIFT)                    /*!< SIM_SDID: REVID Mask                    */
#define SIM_SDID_REVID_SHIFT                     12                                                  /*!< SIM_SDID: REVID Position                */
#define SIM_SDID_REVID(x)                        (((x)<<SIM_SDID_REVID_SHIFT)&SIM_SDID_REVID_MASK)   /*!< SIM_SDID                                */
#define SIM_SDID_SRAMSIZE_MASK                   (0x0FUL << SIM_SDID_SRAMSIZE_SHIFT)                 /*!< SIM_SDID: SRAMSIZE Mask                 */
#define SIM_SDID_SRAMSIZE_SHIFT                  16                                                  /*!< SIM_SDID: SRAMSIZE Position             */
#define SIM_SDID_SRAMSIZE(x)                     (((x)<<SIM_SDID_SRAMSIZE_SHIFT)&SIM_SDID_SRAMSIZE_MASK) /*!< SIM_SDID                                */
#define SIM_SDID_SERIESID_MASK                   (0x0FUL << SIM_SDID_SERIESID_SHIFT)                 /*!< SIM_SDID: SERIESID Mask                 */
#define SIM_SDID_SERIESID_SHIFT                  20                                                  /*!< SIM_SDID: SERIESID Position             */
#define SIM_SDID_SERIESID(x)                     (((x)<<SIM_SDID_SERIESID_SHIFT)&SIM_SDID_SERIESID_MASK) /*!< SIM_SDID                                */
#define SIM_SDID_SUBFAMID_MASK                   (0x0FUL << SIM_SDID_SUBFAMID_SHIFT)                 /*!< SIM_SDID: SUBFAMID Mask                 */
#define SIM_SDID_SUBFAMID_SHIFT                  24                                                  /*!< SIM_SDID: SUBFAMID Position             */
#define SIM_SDID_SUBFAMID(x)                     (((x)<<SIM_SDID_SUBFAMID_SHIFT)&SIM_SDID_SUBFAMID_MASK) /*!< SIM_SDID                                */
#define SIM_SDID_FAMID_MASK                      (0x0FUL << SIM_SDID_FAMID_SHIFT)                    /*!< SIM_SDID: FAMID Mask                    */
#define SIM_SDID_FAMID_SHIFT                     28                                                  /*!< SIM_SDID: FAMID Position                */
#define SIM_SDID_FAMID(x)                        (((x)<<SIM_SDID_FAMID_SHIFT)&SIM_SDID_FAMID_MASK)   /*!< SIM_SDID                                */

/* ------- SIM_SCGC4                                ------ */
#define SIM_SCGC4_I2C0_MASK                      (0x01UL << SIM_SCGC4_I2C0_SHIFT)                    /*!< SIM_SCGC4: I2C0 Mask                    */
#define SIM_SCGC4_I2C0_SHIFT                     6                                                   /*!< SIM_SCGC4: I2C0 Position                */
#define SIM_SCGC4_I2C1_MASK                      (0x01UL << SIM_SCGC4_I2C1_SHIFT)                    /*!< SIM_SCGC4: I2C1 Mask                    */
#define SIM_SCGC4_I2C1_SHIFT                     7                                                   /*!< SIM_SCGC4: I2C1 Position                */
#define SIM_SCGC4_UART2_MASK                     (0x01UL << SIM_SCGC4_UART2_SHIFT)                   /*!< SIM_SCGC4: UART2 Mask                   */
#define SIM_SCGC4_UART2_SHIFT                    12                                                  /*!< SIM_SCGC4: UART2 Position               */
#define SIM_SCGC4_USBOTG_MASK                    (0x01UL << SIM_SCGC4_USBOTG_SHIFT)                  /*!< SIM_SCGC4: USBOTG Mask                  */
#define SIM_SCGC4_USBOTG_SHIFT                   18                                                  /*!< SIM_SCGC4: USBOTG Position              */
#define SIM_SCGC4_CMP0_MASK                      (0x01UL << SIM_SCGC4_CMP0_SHIFT)                    /*!< SIM_SCGC4: CMP0 Mask                    */
#define SIM_SCGC4_CMP0_SHIFT                     19                                                  /*!< SIM_SCGC4: CMP0 Position                */
#define SIM_SCGC4_VREF_MASK                      (0x01UL << SIM_SCGC4_VREF_SHIFT)                    /*!< SIM_SCGC4: VREF Mask                    */
#define SIM_SCGC4_VREF_SHIFT                     20                                                  /*!< SIM_SCGC4: VREF Position                */
#define SIM_SCGC4_SPI0_MASK                      (0x01UL << SIM_SCGC4_SPI0_SHIFT)                    /*!< SIM_SCGC4: SPI0 Mask                    */
#define SIM_SCGC4_SPI0_SHIFT                     22                                                  /*!< SIM_SCGC4: SPI0 Position                */
#define SIM_SCGC4_SPI1_MASK                      (0x01UL << SIM_SCGC4_SPI1_SHIFT)                    /*!< SIM_SCGC4: SPI1 Mask                    */
#define SIM_SCGC4_SPI1_SHIFT                     23                                                  /*!< SIM_SCGC4: SPI1 Position                */

/* ------- SIM_SCGC5                                ------ */
#define SIM_SCGC5_LPTMR_MASK                     (0x01UL << SIM_SCGC5_LPTMR_SHIFT)                   /*!< SIM_SCGC5: LPTMR Mask                   */
#define SIM_SCGC5_LPTMR_SHIFT                    0                                                   /*!< SIM_SCGC5: LPTMR Position               */
#define SIM_SCGC5_PORTA_MASK                     (0x01UL << SIM_SCGC5_PORTA_SHIFT)                   /*!< SIM_SCGC5: PORTA Mask                   */
#define SIM_SCGC5_PORTA_SHIFT                    9                                                   /*!< SIM_SCGC5: PORTA Position               */
#define SIM_SCGC5_PORTB_MASK                     (0x01UL << SIM_SCGC5_PORTB_SHIFT)                   /*!< SIM_SCGC5: PORTB Mask                   */
#define SIM_SCGC5_PORTB_SHIFT                    10                                                  /*!< SIM_SCGC5: PORTB Position               */
#define SIM_SCGC5_PORTC_MASK                     (0x01UL << SIM_SCGC5_PORTC_SHIFT)                   /*!< SIM_SCGC5: PORTC Mask                   */
#define SIM_SCGC5_PORTC_SHIFT                    11                                                  /*!< SIM_SCGC5: PORTC Position               */
#define SIM_SCGC5_PORTD_MASK                     (0x01UL << SIM_SCGC5_PORTD_SHIFT)                   /*!< SIM_SCGC5: PORTD Mask                   */
#define SIM_SCGC5_PORTD_SHIFT                    12                                                  /*!< SIM_SCGC5: PORTD Position               */
#define SIM_SCGC5_PORTE_MASK                     (0x01UL << SIM_SCGC5_PORTE_SHIFT)                   /*!< SIM_SCGC5: PORTE Mask                   */
#define SIM_SCGC5_PORTE_SHIFT                    13                                                  /*!< SIM_SCGC5: PORTE Position               */
#define SIM_SCGC5_SLCD_MASK                      (0x01UL << SIM_SCGC5_SLCD_SHIFT)                    /*!< SIM_SCGC5: SLCD Mask                    */
#define SIM_SCGC5_SLCD_SHIFT                     19                                                  /*!< SIM_SCGC5: SLCD Position                */
#define SIM_SCGC5_LPUART0_MASK                   (0x01UL << SIM_SCGC5_LPUART0_SHIFT)                 /*!< SIM_SCGC5: LPUART0 Mask                 */
#define SIM_SCGC5_LPUART0_SHIFT                  20                                                  /*!< SIM_SCGC5: LPUART0 Position             */
#define SIM_SCGC5_LPUART1_MASK                   (0x01UL << SIM_SCGC5_LPUART1_SHIFT)                 /*!< SIM_SCGC5: LPUART1 Mask                 */
#define SIM_SCGC5_LPUART1_SHIFT                  21                                                  /*!< SIM_SCGC5: LPUART1 Position             */
#define SIM_SCGC5_FLEXIO_MASK                    (0x01UL << SIM_SCGC5_FLEXIO_SHIFT)                  /*!< SIM_SCGC5: FLEXIO Mask                  */
#define SIM_SCGC5_FLEXIO_SHIFT                   31                                                  /*!< SIM_SCGC5: FLEXIO Position              */

/* ------- SIM_SCGC6                                ------ */
#define SIM_SCGC6_FTF_MASK                       (0x01UL << SIM_SCGC6_FTF_SHIFT)                     /*!< SIM_SCGC6: FTF Mask                     */
#define SIM_SCGC6_FTF_SHIFT                      0                                                   /*!< SIM_SCGC6: FTF Position                 */
#define SIM_SCGC6_DMAMUX_MASK                    (0x01UL << SIM_SCGC6_DMAMUX_SHIFT)                  /*!< SIM_SCGC6: DMAMUX Mask                  */
#define SIM_SCGC6_DMAMUX_SHIFT                   1                                                   /*!< SIM_SCGC6: DMAMUX Position              */
#define SIM_SCGC6_I2S_MASK                       (0x01UL << SIM_SCGC6_I2S_SHIFT)                     /*!< SIM_SCGC6: I2S Mask                     */
#define SIM_SCGC6_I2S_SHIFT                      15                                                  /*!< SIM_SCGC6: I2S Position                 */
#define SIM_SCGC6_PIT_MASK                       (0x01UL << SIM_SCGC6_PIT_SHIFT)                     /*!< SIM_SCGC6: PIT Mask                     */
#define SIM_SCGC6_PIT_SHIFT                      23                                                  /*!< SIM_SCGC6: PIT Position                 */
#define SIM_SCGC6_TPM0_MASK                      (0x01UL << SIM_SCGC6_TPM0_SHIFT)                    /*!< SIM_SCGC6: TPM0 Mask                    */
#define SIM_SCGC6_TPM0_SHIFT                     24                                                  /*!< SIM_SCGC6: TPM0 Position                */
#define SIM_SCGC6_TPM1_MASK                      (0x01UL << SIM_SCGC6_TPM1_SHIFT)                    /*!< SIM_SCGC6: TPM1 Mask                    */
#define SIM_SCGC6_TPM1_SHIFT                     25                                                  /*!< SIM_SCGC6: TPM1 Position                */
#define SIM_SCGC6_TPM2_MASK                      (0x01UL << SIM_SCGC6_TPM2_SHIFT)                    /*!< SIM_SCGC6: TPM2 Mask                    */
#define SIM_SCGC6_TPM2_SHIFT                     26                                                  /*!< SIM_SCGC6: TPM2 Position                */
#define SIM_SCGC6_ADC0_MASK                      (0x01UL << SIM_SCGC6_ADC0_SHIFT)                    /*!< SIM_SCGC6: ADC0 Mask                    */
#define SIM_SCGC6_ADC0_SHIFT                     27                                                  /*!< SIM_SCGC6: ADC0 Position                */
#define SIM_SCGC6_RTC_MASK                       (0x01UL << SIM_SCGC6_RTC_SHIFT)                     /*!< SIM_SCGC6: RTC Mask                     */
#define SIM_SCGC6_RTC_SHIFT                      29                                                  /*!< SIM_SCGC6: RTC Position                 */
#define SIM_SCGC6_DAC0_MASK                      (0x01UL << SIM_SCGC6_DAC0_SHIFT)                    /*!< SIM_SCGC6: DAC0 Mask                    */
#define SIM_SCGC6_DAC0_SHIFT                     31                                                  /*!< SIM_SCGC6: DAC0 Position                */

/* ------- SIM_SCGC7                                ------ */
#define SIM_SCGC7_DMA_MASK                       (0x01UL << SIM_SCGC7_DMA_SHIFT)                     /*!< SIM_SCGC7: DMA Mask                     */
#define SIM_SCGC7_DMA_SHIFT                      8                                                   /*!< SIM_SCGC7: DMA Position                 */

/* ------- SIM_CLKDIV1                              ------ */
#define SIM_CLKDIV1_OUTDIV4_MASK                 (0x07UL << SIM_CLKDIV1_OUTDIV4_SHIFT)               /*!< SIM_CLKDIV1: OUTDIV4 Mask               */
#define SIM_CLKDIV1_OUTDIV4_SHIFT                16                                                  /*!< SIM_CLKDIV1: OUTDIV4 Position           */
#define SIM_CLKDIV1_OUTDIV4(x)                   (((x)<<SIM_CLKDIV1_OUTDIV4_SHIFT)&SIM_CLKDIV1_OUTDIV4_MASK) /*!< SIM_CLKDIV1                             */
#define SIM_CLKDIV1_OUTDIV1_MASK                 (0x0FUL << SIM_CLKDIV1_OUTDIV1_SHIFT)               /*!< SIM_CLKDIV1: OUTDIV1 Mask               */
#define SIM_CLKDIV1_OUTDIV1_SHIFT                28                                                  /*!< SIM_CLKDIV1: OUTDIV1 Position           */
#define SIM_CLKDIV1_OUTDIV1(x)                   (((x)<<SIM_CLKDIV1_OUTDIV1_SHIFT)&SIM_CLKDIV1_OUTDIV1_MASK) /*!< SIM_CLKDIV1                             */

/* ------- SIM_FCFG1                                ------ */
#define SIM_FCFG1_FLASHDIS_MASK                  (0x01UL << SIM_FCFG1_FLASHDIS_SHIFT)                /*!< SIM_FCFG1: FLASHDIS Mask                */
#define SIM_FCFG1_FLASHDIS_SHIFT                 0                                                   /*!< SIM_FCFG1: FLASHDIS Position            */
#define SIM_FCFG1_FLASHDOZE_MASK                 (0x01UL << SIM_FCFG1_FLASHDOZE_SHIFT)               /*!< SIM_FCFG1: FLASHDOZE Mask               */
#define SIM_FCFG1_FLASHDOZE_SHIFT                1                                                   /*!< SIM_FCFG1: FLASHDOZE Position           */
#define SIM_FCFG1_PFSIZE_MASK                    (0x0FUL << SIM_FCFG1_PFSIZE_SHIFT)                  /*!< SIM_FCFG1: PFSIZE Mask                  */
#define SIM_FCFG1_PFSIZE_SHIFT                   24                                                  /*!< SIM_FCFG1: PFSIZE Position              */
#define SIM_FCFG1_PFSIZE(x)                      (((x)<<SIM_FCFG1_PFSIZE_SHIFT)&SIM_FCFG1_PFSIZE_MASK) /*!< SIM_FCFG1                               */

/* ------- SIM_FCFG2                                ------ */
#define SIM_FCFG2_MAXADDR1_MASK                  (0x7FUL << SIM_FCFG2_MAXADDR1_SHIFT)                /*!< SIM_FCFG2: MAXADDR1 Mask                */
#define SIM_FCFG2_MAXADDR1_SHIFT                 16                                                  /*!< SIM_FCFG2: MAXADDR1 Position            */
#define SIM_FCFG2_MAXADDR1(x)                    (((x)<<SIM_FCFG2_MAXADDR1_SHIFT)&SIM_FCFG2_MAXADDR1_MASK) /*!< SIM_FCFG2                               */
#define SIM_FCFG2_MAXADDR0_MASK                  (0x7FUL << SIM_FCFG2_MAXADDR0_SHIFT)                /*!< SIM_FCFG2: MAXADDR0 Mask                */
#define SIM_FCFG2_MAXADDR0_SHIFT                 24                                                  /*!< SIM_FCFG2: MAXADDR0 Position            */
#define SIM_FCFG2_MAXADDR0(x)                    (((x)<<SIM_FCFG2_MAXADDR0_SHIFT)&SIM_FCFG2_MAXADDR0_MASK) /*!< SIM_FCFG2                               */

/* ------- SIM_UIDMH                                ------ */
#define SIM_UIDMH_UID_MASK                       (0xFFFFUL << SIM_UIDMH_UID_SHIFT)                   /*!< SIM_UIDMH: UID Mask                     */
#define SIM_UIDMH_UID_SHIFT                      0                                                   /*!< SIM_UIDMH: UID Position                 */
#define SIM_UIDMH_UID(x)                         (((x)<<SIM_UIDMH_UID_SHIFT)&SIM_UIDMH_UID_MASK)     /*!< SIM_UIDMH                               */

/* ------- SIM_UIDML                                ------ */
#define SIM_UIDML_UID_MASK                       (0xFFFFFFFFUL << SIM_UIDML_UID_SHIFT)               /*!< SIM_UIDML: UID Mask                     */
#define SIM_UIDML_UID_SHIFT                      0                                                   /*!< SIM_UIDML: UID Position                 */
#define SIM_UIDML_UID(x)                         (((x)<<SIM_UIDML_UID_SHIFT)&SIM_UIDML_UID_MASK)     /*!< SIM_UIDML                               */

/* ------- SIM_UIDL                                 ------ */
#define SIM_UIDL_UID_MASK                        (0xFFFFFFFFUL << SIM_UIDL_UID_SHIFT)                /*!< SIM_UIDL: UID Mask                      */
#define SIM_UIDL_UID_SHIFT                       0                                                   /*!< SIM_UIDL: UID Position                  */
#define SIM_UIDL_UID(x)                          (((x)<<SIM_UIDL_UID_SHIFT)&SIM_UIDL_UID_MASK)       /*!< SIM_UIDL                                */

/* ------- SIM_COPC                                 ------ */
#define SIM_COPC_COPW_MASK                       (0x01UL << SIM_COPC_COPW_SHIFT)                     /*!< SIM_COPC: COPW Mask                     */
#define SIM_COPC_COPW_SHIFT                      0                                                   /*!< SIM_COPC: COPW Position                 */
#define SIM_COPC_COPCLKS_MASK                    (0x01UL << SIM_COPC_COPCLKS_SHIFT)                  /*!< SIM_COPC: COPCLKS Mask                  */
#define SIM_COPC_COPCLKS_SHIFT                   1                                                   /*!< SIM_COPC: COPCLKS Position              */
#define SIM_COPC_COPT_MASK                       (0x03UL << SIM_COPC_COPT_SHIFT)                     /*!< SIM_COPC: COPT Mask                     */
#define SIM_COPC_COPT_SHIFT                      2                                                   /*!< SIM_COPC: COPT Position                 */
#define SIM_COPC_COPT(x)                         (((x)<<SIM_COPC_COPT_SHIFT)&SIM_COPC_COPT_MASK)     /*!< SIM_COPC                                */
#define SIM_COPC_COPSTPEN_MASK                   (0x01UL << SIM_COPC_COPSTPEN_SHIFT)                 /*!< SIM_COPC: COPSTPEN Mask                 */
#define SIM_COPC_COPSTPEN_SHIFT                  4                                                   /*!< SIM_COPC: COPSTPEN Position             */
#define SIM_COPC_COPDBGEN_MASK                   (0x01UL << SIM_COPC_COPDBGEN_SHIFT)                 /*!< SIM_COPC: COPDBGEN Mask                 */
#define SIM_COPC_COPDBGEN_SHIFT                  5                                                   /*!< SIM_COPC: COPDBGEN Position             */
#define SIM_COPC_COPCLKSEL_MASK                  (0x03UL << SIM_COPC_COPCLKSEL_SHIFT)                /*!< SIM_COPC: COPCLKSEL Mask                */
#define SIM_COPC_COPCLKSEL_SHIFT                 6                                                   /*!< SIM_COPC: COPCLKSEL Position            */
#define SIM_COPC_COPCLKSEL(x)                    (((x)<<SIM_COPC_COPCLKSEL_SHIFT)&SIM_COPC_COPCLKSEL_MASK) /*!< SIM_COPC                                */

/* ------- SIM_SRVCOP                               ------ */
#define SIM_SRVCOP_SRVCOP_MASK                   (0xFFUL << SIM_SRVCOP_SRVCOP_SHIFT)                 /*!< SIM_SRVCOP: SRVCOP Mask                 */
#define SIM_SRVCOP_SRVCOP_SHIFT                  0                                                   /*!< SIM_SRVCOP: SRVCOP Position             */
#define SIM_SRVCOP_SRVCOP(x)                     (((x)<<SIM_SRVCOP_SRVCOP_SHIFT)&SIM_SRVCOP_SRVCOP_MASK) /*!< SIM_SRVCOP                              */

/* -------------------------------------------------------------------------------- */
/* -----------     'SIM' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define SIM_SOPT1                      (SIM->SOPT1)
#define SIM_SOPT1CFG                   (SIM->SOPT1CFG)
#define SIM_SOPT2                      (SIM->SOPT2)
#define SIM_SOPT4                      (SIM->SOPT4)
#define SIM_SOPT5                      (SIM->SOPT5)
#define SIM_SOPT7                      (SIM->SOPT7)
#define SIM_SDID                       (SIM->SDID)
#define SIM_SCGC4                      (SIM->SCGC4)
#define SIM_SCGC5                      (SIM->SCGC5)
#define SIM_SCGC6                      (SIM->SCGC6)
#define SIM_SCGC7                      (SIM->SCGC7)
#define SIM_CLKDIV1                    (SIM->CLKDIV1)
#define SIM_FCFG1                      (SIM->FCFG1)
#define SIM_FCFG2                      (SIM->FCFG2)
#define SIM_UIDMH                      (SIM->UIDMH)
#define SIM_UIDML                      (SIM->UIDML)
#define SIM_UIDL                       (SIM->UIDL)
#define SIM_COPC                       (SIM->COPC)
#define SIM_SRVCOP                     (SIM->SRVCOP)

/* ================================================================================ */
/* ================           SMC (file:SMC_MKL)                   ================ */
/* ================================================================================ */

/**
 * @brief System Mode Controller
 */
typedef struct {                                /*!<       SMC Structure                                                */
   __IO uint8_t   PMPROT;                       /*!< 0000: Power Mode Protection Register                               */
   __IO uint8_t   PMCTRL;                       /*!< 0001: Power Mode Control Register                                  */
   __IO uint8_t   STOPCTRL;                     /*!< 0002: Stop Control Register                                        */
   __I  uint8_t   PMSTAT;                       /*!< 0003: Power Mode Status Register                                   */
} SMC_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'SMC' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- SMC_PMPROT                               ------ */
#define SMC_PMPROT_AVLLS_MASK                    (0x01UL << SMC_PMPROT_AVLLS_SHIFT)                  /*!< SMC_PMPROT: AVLLS Mask                  */
#define SMC_PMPROT_AVLLS_SHIFT                   1                                                   /*!< SMC_PMPROT: AVLLS Position              */
#define SMC_PMPROT_ALLS_MASK                     (0x01UL << SMC_PMPROT_ALLS_SHIFT)                   /*!< SMC_PMPROT: ALLS Mask                   */
#define SMC_PMPROT_ALLS_SHIFT                    3                                                   /*!< SMC_PMPROT: ALLS Position               */
#define SMC_PMPROT_AVLP_MASK                     (0x01UL << SMC_PMPROT_AVLP_SHIFT)                   /*!< SMC_PMPROT: AVLP Mask                   */
#define SMC_PMPROT_AVLP_SHIFT                    5                                                   /*!< SMC_PMPROT: AVLP Position               */

/* ------- SMC_PMCTRL                               ------ */
#define SMC_PMCTRL_STOPM_MASK                    (0x07UL << SMC_PMCTRL_STOPM_SHIFT)                  /*!< SMC_PMCTRL: STOPM Mask                  */
#define SMC_PMCTRL_STOPM_SHIFT                   0                                                   /*!< SMC_PMCTRL: STOPM Position              */
#define SMC_PMCTRL_STOPM(x)                      (((x)<<SMC_PMCTRL_STOPM_SHIFT)&SMC_PMCTRL_STOPM_MASK) /*!< SMC_PMCTRL                              */
#define SMC_PMCTRL_STOPA_MASK                    (0x01UL << SMC_PMCTRL_STOPA_SHIFT)                  /*!< SMC_PMCTRL: STOPA Mask                  */
#define SMC_PMCTRL_STOPA_SHIFT                   3                                                   /*!< SMC_PMCTRL: STOPA Position              */
#define SMC_PMCTRL_RUNM_MASK                     (0x03UL << SMC_PMCTRL_RUNM_SHIFT)                   /*!< SMC_PMCTRL: RUNM Mask                   */
#define SMC_PMCTRL_RUNM_SHIFT                    5                                                   /*!< SMC_PMCTRL: RUNM Position               */
#define SMC_PMCTRL_RUNM(x)                       (((x)<<SMC_PMCTRL_RUNM_SHIFT)&SMC_PMCTRL_RUNM_MASK) /*!< SMC_PMCTRL                              */

/* ------- SMC_STOPCTRL                             ------ */
#define SMC_STOPCTRL_VLLSM_MASK                  (0x07UL << SMC_STOPCTRL_VLLSM_SHIFT)                /*!< SMC_STOPCTRL: VLLSM Mask                */
#define SMC_STOPCTRL_VLLSM_SHIFT                 0                                                   /*!< SMC_STOPCTRL: VLLSM Position            */
#define SMC_STOPCTRL_VLLSM(x)                    (((x)<<SMC_STOPCTRL_VLLSM_SHIFT)&SMC_STOPCTRL_VLLSM_MASK) /*!< SMC_STOPCTRL                            */
#define SMC_STOPCTRL_PORPO_MASK                  (0x01UL << SMC_STOPCTRL_PORPO_SHIFT)                /*!< SMC_STOPCTRL: PORPO Mask                */
#define SMC_STOPCTRL_PORPO_SHIFT                 5                                                   /*!< SMC_STOPCTRL: PORPO Position            */
#define SMC_STOPCTRL_PSTOPO_MASK                 (0x03UL << SMC_STOPCTRL_PSTOPO_SHIFT)               /*!< SMC_STOPCTRL: PSTOPO Mask               */
#define SMC_STOPCTRL_PSTOPO_SHIFT                6                                                   /*!< SMC_STOPCTRL: PSTOPO Position           */
#define SMC_STOPCTRL_PSTOPO(x)                   (((x)<<SMC_STOPCTRL_PSTOPO_SHIFT)&SMC_STOPCTRL_PSTOPO_MASK) /*!< SMC_STOPCTRL                            */

/* ------- SMC_PMSTAT                               ------ */
#define SMC_PMSTAT_PMSTAT_MASK                   (0x7FUL << SMC_PMSTAT_PMSTAT_SHIFT)                 /*!< SMC_PMSTAT: PMSTAT Mask                 */
#define SMC_PMSTAT_PMSTAT_SHIFT                  0                                                   /*!< SMC_PMSTAT: PMSTAT Position             */
#define SMC_PMSTAT_PMSTAT(x)                     (((x)<<SMC_PMSTAT_PMSTAT_SHIFT)&SMC_PMSTAT_PMSTAT_MASK) /*!< SMC_PMSTAT                              */

/* -------------------------------------------------------------------------------- */
/* -----------     'SMC' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define SMC_PMPROT                     (SMC->PMPROT)
#define SMC_PMCTRL                     (SMC->PMCTRL)
#define SMC_STOPCTRL                   (SMC->STOPCTRL)
#define SMC_PMSTAT                     (SMC->PMSTAT)

/* ================================================================================ */
/* ================           SPI0 (file:SPI0_MKL_FIFO)            ================ */
/* ================================================================================ */

/**
 * @brief Serial Peripheral Interface
 */
typedef struct {                                /*!<       SPI0 Structure                                               */
   __I  uint8_t   S;                            /*!< 0000: SPI status register                                          */
   __IO uint8_t   BR;                           /*!< 0001: SPI baud rate register                                       */
   __IO uint8_t   C2;                           /*!< 0002: SPI control register 2                                       */
   __IO uint8_t   C1;                           /*!< 0003: SPI control register 1                                       */
   __IO uint8_t   ML;                           /*!< 0004: SPI match register low                                       */
   __IO uint8_t   MH;                           /*!< 0005: SPI match register high                                      */
   __IO uint8_t   DL;                           /*!< 0006: SPI data register low                                        */
   __IO uint8_t   DH;                           /*!< 0007: SPI data register high                                       */
   __I  uint16_t  RESERVED0;                    /*!< 0008:                                                              */
   __IO uint8_t   CI;                           /*!< 000A: SPI clear interrupt register                                 */
   __IO uint8_t   C3;                           /*!< 000B: SPI control register 3                                       */
} SPI0_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'SPI0' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- SPI0_S                                   ------ */
#define SPI_S_RFIFOEF_MASK                       (0x01UL << SPI_S_RFIFOEF_SHIFT)                     /*!< SPI0_S: RFIFOEF Mask                    */
#define SPI_S_RFIFOEF_SHIFT                      0                                                   /*!< SPI0_S: RFIFOEF Position                */
#define SPI_S_TXFULLF_MASK                       (0x01UL << SPI_S_TXFULLF_SHIFT)                     /*!< SPI0_S: TXFULLF Mask                    */
#define SPI_S_TXFULLF_SHIFT                      1                                                   /*!< SPI0_S: TXFULLF Position                */
#define SPI_S_TNEAREF_MASK                       (0x01UL << SPI_S_TNEAREF_SHIFT)                     /*!< SPI0_S: TNEAREF Mask                    */
#define SPI_S_TNEAREF_SHIFT                      2                                                   /*!< SPI0_S: TNEAREF Position                */
#define SPI_S_RNFULLF_MASK                       (0x01UL << SPI_S_RNFULLF_SHIFT)                     /*!< SPI0_S: RNFULLF Mask                    */
#define SPI_S_RNFULLF_SHIFT                      3                                                   /*!< SPI0_S: RNFULLF Position                */
#define SPI_S_MODF_MASK                          (0x01UL << SPI_S_MODF_SHIFT)                        /*!< SPI0_S: MODF Mask                       */
#define SPI_S_MODF_SHIFT                         4                                                   /*!< SPI0_S: MODF Position                   */
#define SPI_S_SPTEF_MASK                         (0x01UL << SPI_S_SPTEF_SHIFT)                       /*!< SPI0_S: SPTEF Mask                      */
#define SPI_S_SPTEF_SHIFT                        5                                                   /*!< SPI0_S: SPTEF Position                  */
#define SPI_S_SPMF_MASK                          (0x01UL << SPI_S_SPMF_SHIFT)                        /*!< SPI0_S: SPMF Mask                       */
#define SPI_S_SPMF_SHIFT                         6                                                   /*!< SPI0_S: SPMF Position                   */
#define SPI_S_SPRF_MASK                          (0x01UL << SPI_S_SPRF_SHIFT)                        /*!< SPI0_S: SPRF Mask                       */
#define SPI_S_SPRF_SHIFT                         7                                                   /*!< SPI0_S: SPRF Position                   */

/* ------- SPI0_BR                                  ------ */
#define SPI_BR_SPR_MASK                          (0x0FUL << SPI_BR_SPR_SHIFT)                        /*!< SPI0_BR: SPR Mask                       */
#define SPI_BR_SPR_SHIFT                         0                                                   /*!< SPI0_BR: SPR Position                   */
#define SPI_BR_SPR(x)                            (((x)<<SPI_BR_SPR_SHIFT)&SPI_BR_SPR_MASK)           /*!< SPI0_BR                                 */
#define SPI_BR_SPPR_MASK                         (0x07UL << SPI_BR_SPPR_SHIFT)                       /*!< SPI0_BR: SPPR Mask                      */
#define SPI_BR_SPPR_SHIFT                        4                                                   /*!< SPI0_BR: SPPR Position                  */
#define SPI_BR_SPPR(x)                           (((x)<<SPI_BR_SPPR_SHIFT)&SPI_BR_SPPR_MASK)         /*!< SPI0_BR                                 */

/* ------- SPI0_C2                                  ------ */
#define SPI_C2_SPC0_MASK                         (0x01UL << SPI_C2_SPC0_SHIFT)                       /*!< SPI0_C2: SPC0 Mask                      */
#define SPI_C2_SPC0_SHIFT                        0                                                   /*!< SPI0_C2: SPC0 Position                  */
#define SPI_C2_SPISWAI_MASK                      (0x01UL << SPI_C2_SPISWAI_SHIFT)                    /*!< SPI0_C2: SPISWAI Mask                   */
#define SPI_C2_SPISWAI_SHIFT                     1                                                   /*!< SPI0_C2: SPISWAI Position               */
#define SPI_C2_RXDMAE_MASK                       (0x01UL << SPI_C2_RXDMAE_SHIFT)                     /*!< SPI0_C2: RXDMAE Mask                    */
#define SPI_C2_RXDMAE_SHIFT                      2                                                   /*!< SPI0_C2: RXDMAE Position                */
#define SPI_C2_BIDIROE_MASK                      (0x01UL << SPI_C2_BIDIROE_SHIFT)                    /*!< SPI0_C2: BIDIROE Mask                   */
#define SPI_C2_BIDIROE_SHIFT                     3                                                   /*!< SPI0_C2: BIDIROE Position               */
#define SPI_C2_MODFEN_MASK                       (0x01UL << SPI_C2_MODFEN_SHIFT)                     /*!< SPI0_C2: MODFEN Mask                    */
#define SPI_C2_MODFEN_SHIFT                      4                                                   /*!< SPI0_C2: MODFEN Position                */
#define SPI_C2_TXDMAE_MASK                       (0x01UL << SPI_C2_TXDMAE_SHIFT)                     /*!< SPI0_C2: TXDMAE Mask                    */
#define SPI_C2_TXDMAE_SHIFT                      5                                                   /*!< SPI0_C2: TXDMAE Position                */
#define SPI_C2_SPIMODE_MASK                      (0x01UL << SPI_C2_SPIMODE_SHIFT)                    /*!< SPI0_C2: SPIMODE Mask                   */
#define SPI_C2_SPIMODE_SHIFT                     6                                                   /*!< SPI0_C2: SPIMODE Position               */
#define SPI_C2_SPMIE_MASK                        (0x01UL << SPI_C2_SPMIE_SHIFT)                      /*!< SPI0_C2: SPMIE Mask                     */
#define SPI_C2_SPMIE_SHIFT                       7                                                   /*!< SPI0_C2: SPMIE Position                 */

/* ------- SPI0_C1                                  ------ */
#define SPI_C1_LSBFE_MASK                        (0x01UL << SPI_C1_LSBFE_SHIFT)                      /*!< SPI0_C1: LSBFE Mask                     */
#define SPI_C1_LSBFE_SHIFT                       0                                                   /*!< SPI0_C1: LSBFE Position                 */
#define SPI_C1_SSOE_MASK                         (0x01UL << SPI_C1_SSOE_SHIFT)                       /*!< SPI0_C1: SSOE Mask                      */
#define SPI_C1_SSOE_SHIFT                        1                                                   /*!< SPI0_C1: SSOE Position                  */
#define SPI_C1_CPHA_MASK                         (0x01UL << SPI_C1_CPHA_SHIFT)                       /*!< SPI0_C1: CPHA Mask                      */
#define SPI_C1_CPHA_SHIFT                        2                                                   /*!< SPI0_C1: CPHA Position                  */
#define SPI_C1_CPOL_MASK                         (0x01UL << SPI_C1_CPOL_SHIFT)                       /*!< SPI0_C1: CPOL Mask                      */
#define SPI_C1_CPOL_SHIFT                        3                                                   /*!< SPI0_C1: CPOL Position                  */
#define SPI_C1_MSTR_MASK                         (0x01UL << SPI_C1_MSTR_SHIFT)                       /*!< SPI0_C1: MSTR Mask                      */
#define SPI_C1_MSTR_SHIFT                        4                                                   /*!< SPI0_C1: MSTR Position                  */
#define SPI_C1_SPTIE_MASK                        (0x01UL << SPI_C1_SPTIE_SHIFT)                      /*!< SPI0_C1: SPTIE Mask                     */
#define SPI_C1_SPTIE_SHIFT                       5                                                   /*!< SPI0_C1: SPTIE Position                 */
#define SPI_C1_SPE_MASK                          (0x01UL << SPI_C1_SPE_SHIFT)                        /*!< SPI0_C1: SPE Mask                       */
#define SPI_C1_SPE_SHIFT                         6                                                   /*!< SPI0_C1: SPE Position                   */
#define SPI_C1_SPIE_MASK                         (0x01UL << SPI_C1_SPIE_SHIFT)                       /*!< SPI0_C1: SPIE Mask                      */
#define SPI_C1_SPIE_SHIFT                        7                                                   /*!< SPI0_C1: SPIE Position                  */

/* ------- SPI0_ML                                  ------ */
#define SPI_ML_Bits_MASK                         (0xFFUL << SPI_ML_Bits_SHIFT)                       /*!< SPI0_ML: Bits Mask                      */
#define SPI_ML_Bits_SHIFT                        0                                                   /*!< SPI0_ML: Bits Position                  */
#define SPI_ML_Bits(x)                           (((x)<<SPI_ML_Bits_SHIFT)&SPI_ML_Bits_MASK)         /*!< SPI0_ML                                 */

/* ------- SPI0_MH                                  ------ */
#define SPI_MH_Bits_MASK                         (0xFFUL << SPI_MH_Bits_SHIFT)                       /*!< SPI0_MH: Bits Mask                      */
#define SPI_MH_Bits_SHIFT                        0                                                   /*!< SPI0_MH: Bits Position                  */
#define SPI_MH_Bits(x)                           (((x)<<SPI_MH_Bits_SHIFT)&SPI_MH_Bits_MASK)         /*!< SPI0_MH                                 */

/* ------- SPI0_DL                                  ------ */
#define SPI_DL_Bits_MASK                         (0xFFUL << SPI_DL_Bits_SHIFT)                       /*!< SPI0_DL: Bits Mask                      */
#define SPI_DL_Bits_SHIFT                        0                                                   /*!< SPI0_DL: Bits Position                  */
#define SPI_DL_Bits(x)                           (((x)<<SPI_DL_Bits_SHIFT)&SPI_DL_Bits_MASK)         /*!< SPI0_DL                                 */

/* ------- SPI0_DH                                  ------ */
#define SPI_DH_Bits_MASK                         (0xFFUL << SPI_DH_Bits_SHIFT)                       /*!< SPI0_DH: Bits Mask                      */
#define SPI_DH_Bits_SHIFT                        0                                                   /*!< SPI0_DH: Bits Position                  */
#define SPI_DH_Bits(x)                           (((x)<<SPI_DH_Bits_SHIFT)&SPI_DH_Bits_MASK)         /*!< SPI0_DH                                 */

/* ------- SPI0_CI                                  ------ */
#define SPI_CI_SPRFCI_MASK                       (0x01UL << SPI_CI_SPRFCI_SHIFT)                     /*!< SPI0_CI: SPRFCI Mask                    */
#define SPI_CI_SPRFCI_SHIFT                      0                                                   /*!< SPI0_CI: SPRFCI Position                */
#define SPI_CI_SPTEFCI_MASK                      (0x01UL << SPI_CI_SPTEFCI_SHIFT)                    /*!< SPI0_CI: SPTEFCI Mask                   */
#define SPI_CI_SPTEFCI_SHIFT                     1                                                   /*!< SPI0_CI: SPTEFCI Position               */
#define SPI_CI_RNFULLFCI_MASK                    (0x01UL << SPI_CI_RNFULLFCI_SHIFT)                  /*!< SPI0_CI: RNFULLFCI Mask                 */
#define SPI_CI_RNFULLFCI_SHIFT                   2                                                   /*!< SPI0_CI: RNFULLFCI Position             */
#define SPI_CI_TNEAREFCI_MASK                    (0x01UL << SPI_CI_TNEAREFCI_SHIFT)                  /*!< SPI0_CI: TNEAREFCI Mask                 */
#define SPI_CI_TNEAREFCI_SHIFT                   3                                                   /*!< SPI0_CI: TNEAREFCI Position             */
#define SPI_CI_RXFOF_MASK                        (0x01UL << SPI_CI_RXFOF_SHIFT)                      /*!< SPI0_CI: RXFOF Mask                     */
#define SPI_CI_RXFOF_SHIFT                       4                                                   /*!< SPI0_CI: RXFOF Position                 */
#define SPI_CI_TXFOF_MASK                        (0x01UL << SPI_CI_TXFOF_SHIFT)                      /*!< SPI0_CI: TXFOF Mask                     */
#define SPI_CI_TXFOF_SHIFT                       5                                                   /*!< SPI0_CI: TXFOF Position                 */
#define SPI_CI_RXFERR_MASK                       (0x01UL << SPI_CI_RXFERR_SHIFT)                     /*!< SPI0_CI: RXFERR Mask                    */
#define SPI_CI_RXFERR_SHIFT                      6                                                   /*!< SPI0_CI: RXFERR Position                */
#define SPI_CI_TXFERR_MASK                       (0x01UL << SPI_CI_TXFERR_SHIFT)                     /*!< SPI0_CI: TXFERR Mask                    */
#define SPI_CI_TXFERR_SHIFT                      7                                                   /*!< SPI0_CI: TXFERR Position                */

/* ------- SPI0_C3                                  ------ */
#define SPI_C3_FIFOMODE_MASK                     (0x01UL << SPI_C3_FIFOMODE_SHIFT)                   /*!< SPI0_C3: FIFOMODE Mask                  */
#define SPI_C3_FIFOMODE_SHIFT                    0                                                   /*!< SPI0_C3: FIFOMODE Position              */
#define SPI_C3_RNFULLIEN_MASK                    (0x01UL << SPI_C3_RNFULLIEN_SHIFT)                  /*!< SPI0_C3: RNFULLIEN Mask                 */
#define SPI_C3_RNFULLIEN_SHIFT                   1                                                   /*!< SPI0_C3: RNFULLIEN Position             */
#define SPI_C3_TNEARIEN_MASK                     (0x01UL << SPI_C3_TNEARIEN_SHIFT)                   /*!< SPI0_C3: TNEARIEN Mask                  */
#define SPI_C3_TNEARIEN_SHIFT                    2                                                   /*!< SPI0_C3: TNEARIEN Position              */
#define SPI_C3_INTCLR_MASK                       (0x01UL << SPI_C3_INTCLR_SHIFT)                     /*!< SPI0_C3: INTCLR Mask                    */
#define SPI_C3_INTCLR_SHIFT                      3                                                   /*!< SPI0_C3: INTCLR Position                */
#define SPI_C3_RNFULLF_MARK_MASK                 (0x01UL << SPI_C3_RNFULLF_MARK_SHIFT)               /*!< SPI0_C3: RNFULLF_MARK Mask              */
#define SPI_C3_RNFULLF_MARK_SHIFT                4                                                   /*!< SPI0_C3: RNFULLF_MARK Position          */
#define SPI_C3_TNEAREF_MARK_MASK                 (0x01UL << SPI_C3_TNEAREF_MARK_SHIFT)               /*!< SPI0_C3: TNEAREF_MARK Mask              */
#define SPI_C3_TNEAREF_MARK_SHIFT                5                                                   /*!< SPI0_C3: TNEAREF_MARK Position          */

/* -------------------------------------------------------------------------------- */
/* -----------     'SPI0' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define SPI0_S                         (SPI0->S)
#define SPI0_BR                        (SPI0->BR)
#define SPI0_C2                        (SPI0->C2)
#define SPI0_C1                        (SPI0->C1)
#define SPI0_ML                        (SPI0->ML)
#define SPI0_MH                        (SPI0->MH)
#define SPI0_DL                        (SPI0->DL)
#define SPI0_DH                        (SPI0->DH)
#define SPI0_CI                        (SPI0->CI)
#define SPI0_C3                        (SPI0->C3)

/* ================================================================================ */
/* ================           SPI1 (derived from SPI0)             ================ */
/* ================================================================================ */

/**
 * @brief Serial Peripheral Interface
 */
typedef SPI0_Type SPI1_Type;  /*!< SPI1 Structure                                              */


/* -------------------------------------------------------------------------------- */
/* -----------     'SPI1' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define SPI1_S                         (SPI1->S)
#define SPI1_BR                        (SPI1->BR)
#define SPI1_C2                        (SPI1->C2)
#define SPI1_C1                        (SPI1->C1)
#define SPI1_ML                        (SPI1->ML)
#define SPI1_MH                        (SPI1->MH)
#define SPI1_DL                        (SPI1->DL)
#define SPI1_DH                        (SPI1->DH)
#define SPI1_CI                        (SPI1->CI)
#define SPI1_C3                        (SPI1->C3)

/* ================================================================================ */
/* ================           SYST (file:SysTick_0)                ================ */
/* ================================================================================ */

/**
 * @brief System timer SysTick
 */
typedef struct {                                /*!<       SYST Structure                                               */
   __IO uint32_t  CSR;                          /*!< 0000: Control and Status Register                                  */
   __IO uint32_t  RVR;                          /*!< 0004: Reload Value Register                                        */
   __IO uint32_t  CVR;                          /*!< 0008: Current Value Register                                       */
   __I  uint32_t  CALIB;                        /*!< 000C: Calibration Value Register                                   */
} SYST_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'SYST' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- SYST_CSR                                 ------ */
#define SYST_CSR_ENABLE_MASK                     (0x01UL << SYST_CSR_ENABLE_SHIFT)                   /*!< SYST_CSR: ENABLE Mask                   */
#define SYST_CSR_ENABLE_SHIFT                    0                                                   /*!< SYST_CSR: ENABLE Position               */
#define SYST_CSR_TICKINT_MASK                    (0x01UL << SYST_CSR_TICKINT_SHIFT)                  /*!< SYST_CSR: TICKINT Mask                  */
#define SYST_CSR_TICKINT_SHIFT                   1                                                   /*!< SYST_CSR: TICKINT Position              */
#define SYST_CSR_CLKSOURCE_MASK                  (0x01UL << SYST_CSR_CLKSOURCE_SHIFT)                /*!< SYST_CSR: CLKSOURCE Mask                */
#define SYST_CSR_CLKSOURCE_SHIFT                 2                                                   /*!< SYST_CSR: CLKSOURCE Position            */
#define SYST_CSR_COUNTFLAG_MASK                  (0x01UL << SYST_CSR_COUNTFLAG_SHIFT)                /*!< SYST_CSR: COUNTFLAG Mask                */
#define SYST_CSR_COUNTFLAG_SHIFT                 16                                                  /*!< SYST_CSR: COUNTFLAG Position            */

/* ------- SYST_RVR                                 ------ */
#define SYST_RVR_RELOAD_MASK                     (0xFFFFFFUL << SYST_RVR_RELOAD_SHIFT)               /*!< SYST_RVR: RELOAD Mask                   */
#define SYST_RVR_RELOAD_SHIFT                    0                                                   /*!< SYST_RVR: RELOAD Position               */
#define SYST_RVR_RELOAD(x)                       (((x)<<SYST_RVR_RELOAD_SHIFT)&SYST_RVR_RELOAD_MASK) /*!< SYST_RVR                                */

/* ------- SYST_CVR                                 ------ */
#define SYST_CVR_CURRENT_MASK                    (0xFFFFFFUL << SYST_CVR_CURRENT_SHIFT)              /*!< SYST_CVR: CURRENT Mask                  */
#define SYST_CVR_CURRENT_SHIFT                   0                                                   /*!< SYST_CVR: CURRENT Position              */
#define SYST_CVR_CURRENT(x)                      (((x)<<SYST_CVR_CURRENT_SHIFT)&SYST_CVR_CURRENT_MASK) /*!< SYST_CVR                                */

/* ------- SYST_CALIB                               ------ */
#define SYST_CALIB_TENMS_MASK                    (0xFFFFFFUL << SYST_CALIB_TENMS_SHIFT)              /*!< SYST_CALIB: TENMS Mask                  */
#define SYST_CALIB_TENMS_SHIFT                   0                                                   /*!< SYST_CALIB: TENMS Position              */
#define SYST_CALIB_TENMS(x)                      (((x)<<SYST_CALIB_TENMS_SHIFT)&SYST_CALIB_TENMS_MASK) /*!< SYST_CALIB                              */
#define SYST_CALIB_SKEW_MASK                     (0x01UL << SYST_CALIB_SKEW_SHIFT)                   /*!< SYST_CALIB: SKEW Mask                   */
#define SYST_CALIB_SKEW_SHIFT                    30                                                  /*!< SYST_CALIB: SKEW Position               */
#define SYST_CALIB_NOREF_MASK                    (0x01UL << SYST_CALIB_NOREF_SHIFT)                  /*!< SYST_CALIB: NOREF Mask                  */
#define SYST_CALIB_NOREF_SHIFT                   31                                                  /*!< SYST_CALIB: NOREF Position              */

/* -------------------------------------------------------------------------------- */
/* -----------     'SYST' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define SYST_CSR                       (SYST->CSR)
#define SYST_RVR                       (SYST->RVR)
#define SYST_CVR                       (SYST->CVR)
#define SYST_CALIB                     (SYST->CALIB)

/* ================================================================================ */
/* ================           TPM0 (file:TPM0_6CH)                 ================ */
/* ================================================================================ */

/**
 * @brief Timer/PWM Module (6 channels)
 */
typedef struct {                                /*!<       TPM0 Structure                                               */
   __IO uint32_t  SC;                           /*!< 0000: Status and Control                                           */
   __IO uint32_t  CNT;                          /*!< 0004: Counter                                                      */
   __IO uint32_t  MOD;                          /*!< 0008: Modulo                                                       */
   struct { /* (cluster) */                     /*!< 000C: (size=0x0030, 48)                                            */
      __IO uint32_t  CnSC;                      /*!< 000C: Channel  Status and Control                                  */
      __IO uint32_t  CnV;                       /*!< 0010: Channel  Value                                               */
   } CONTROLS[6];
   __I  uint32_t  RESERVED0[5];                 /*!< 003C:                                                              */
   __IO uint32_t  STATUS;                       /*!< 0050: Capture and Compare Status                                   */
   __I  uint32_t  RESERVED1[12];                /*!< 0054:                                                              */
   __IO uint32_t  CONF;                         /*!< 0084: Configuration                                                */
} TPM0_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'TPM0' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- TPM0_SC                                  ------ */
#define TPM_SC_PS_MASK                           (0x07UL << TPM_SC_PS_SHIFT)                         /*!< TPM0_SC: PS Mask                        */
#define TPM_SC_PS_SHIFT                          0                                                   /*!< TPM0_SC: PS Position                    */
#define TPM_SC_PS(x)                             (((x)<<TPM_SC_PS_SHIFT)&TPM_SC_PS_MASK)             /*!< TPM0_SC                                 */
#define TPM_SC_CMOD_MASK                         (0x03UL << TPM_SC_CMOD_SHIFT)                       /*!< TPM0_SC: CMOD Mask                      */
#define TPM_SC_CMOD_SHIFT                        3                                                   /*!< TPM0_SC: CMOD Position                  */
#define TPM_SC_CMOD(x)                           (((x)<<TPM_SC_CMOD_SHIFT)&TPM_SC_CMOD_MASK)         /*!< TPM0_SC                                 */
#define TPM_SC_CPWMS_MASK                        (0x01UL << TPM_SC_CPWMS_SHIFT)                      /*!< TPM0_SC: CPWMS Mask                     */
#define TPM_SC_CPWMS_SHIFT                       5                                                   /*!< TPM0_SC: CPWMS Position                 */
#define TPM_SC_TOIE_MASK                         (0x01UL << TPM_SC_TOIE_SHIFT)                       /*!< TPM0_SC: TOIE Mask                      */
#define TPM_SC_TOIE_SHIFT                        6                                                   /*!< TPM0_SC: TOIE Position                  */
#define TPM_SC_TOF_MASK                          (0x01UL << TPM_SC_TOF_SHIFT)                        /*!< TPM0_SC: TOF Mask                       */
#define TPM_SC_TOF_SHIFT                         7                                                   /*!< TPM0_SC: TOF Position                   */
#define TPM_SC_DMA_MASK                          (0x01UL << TPM_SC_DMA_SHIFT)                        /*!< TPM0_SC: DMA Mask                       */
#define TPM_SC_DMA_SHIFT                         8                                                   /*!< TPM0_SC: DMA Position                   */

/* ------- TPM0_CNT                                 ------ */
#define TPM_CNT_COUNT_MASK                       (0xFFFFUL << TPM_CNT_COUNT_SHIFT)                   /*!< TPM0_CNT: COUNT Mask                    */
#define TPM_CNT_COUNT_SHIFT                      0                                                   /*!< TPM0_CNT: COUNT Position                */
#define TPM_CNT_COUNT(x)                         (((x)<<TPM_CNT_COUNT_SHIFT)&TPM_CNT_COUNT_MASK)     /*!< TPM0_CNT                                */

/* ------- TPM0_MOD                                 ------ */
#define TPM_MOD_MOD_MASK                         (0xFFFFUL << TPM_MOD_MOD_SHIFT)                     /*!< TPM0_MOD: MOD Mask                      */
#define TPM_MOD_MOD_SHIFT                        0                                                   /*!< TPM0_MOD: MOD Position                  */
#define TPM_MOD_MOD(x)                           (((x)<<TPM_MOD_MOD_SHIFT)&TPM_MOD_MOD_MASK)         /*!< TPM0_MOD                                */

/* ------- TPM0_CnSC                                ------ */
#define TPM_CnSC_DMA_MASK                        (0x01UL << TPM_CnSC_DMA_SHIFT)                      /*!< TPM0_CnSC: DMA Mask                     */
#define TPM_CnSC_DMA_SHIFT                       0                                                   /*!< TPM0_CnSC: DMA Position                 */
#define TPM_CnSC_ELS_MASK                        (0x03UL << TPM_CnSC_ELS_SHIFT)                      /*!< TPM0_CnSC: ELS Mask                     */
#define TPM_CnSC_ELS_SHIFT                       2                                                   /*!< TPM0_CnSC: ELS Position                 */
#define TPM_CnSC_ELS(x)                          (((x)<<TPM_CnSC_ELS_SHIFT)&TPM_CnSC_ELS_MASK)       /*!< TPM0_CnSC                               */
#define TPM_CnSC_ELSA_MASK                       (0x01UL << TPM_CnSC_ELSA_SHIFT)                     /*!< TPM0_CnSC: ELSA Mask                    */
#define TPM_CnSC_ELSA_SHIFT                      2                                                   /*!< TPM0_CnSC: ELSA Position                */
#define TPM_CnSC_ELSB_MASK                       (0x01UL << TPM_CnSC_ELSB_SHIFT)                     /*!< TPM0_CnSC: ELSB Mask                    */
#define TPM_CnSC_ELSB_SHIFT                      3                                                   /*!< TPM0_CnSC: ELSB Position                */
#define TPM_CnSC_MS_MASK                         (0x03UL << TPM_CnSC_MS_SHIFT)                       /*!< TPM0_CnSC: MS Mask                      */
#define TPM_CnSC_MS_SHIFT                        4                                                   /*!< TPM0_CnSC: MS Position                  */
#define TPM_CnSC_MS(x)                           (((x)<<TPM_CnSC_MS_SHIFT)&TPM_CnSC_MS_MASK)         /*!< TPM0_CnSC                               */
#define TPM_CnSC_MSA_MASK                        (0x01UL << TPM_CnSC_MSA_SHIFT)                      /*!< TPM0_CnSC: MSA Mask                     */
#define TPM_CnSC_MSA_SHIFT                       4                                                   /*!< TPM0_CnSC: MSA Position                 */
#define TPM_CnSC_MSB_MASK                        (0x01UL << TPM_CnSC_MSB_SHIFT)                      /*!< TPM0_CnSC: MSB Mask                     */
#define TPM_CnSC_MSB_SHIFT                       5                                                   /*!< TPM0_CnSC: MSB Position                 */
#define TPM_CnSC_CHIE_MASK                       (0x01UL << TPM_CnSC_CHIE_SHIFT)                     /*!< TPM0_CnSC: CHIE Mask                    */
#define TPM_CnSC_CHIE_SHIFT                      6                                                   /*!< TPM0_CnSC: CHIE Position                */
#define TPM_CnSC_CHF_MASK                        (0x01UL << TPM_CnSC_CHF_SHIFT)                      /*!< TPM0_CnSC: CHF Mask                     */
#define TPM_CnSC_CHF_SHIFT                       7                                                   /*!< TPM0_CnSC: CHF Position                 */

/* ------- TPM0_CnV                                 ------ */
#define TPM_CnV_VAL_MASK                         (0xFFFFUL << TPM_CnV_VAL_SHIFT)                     /*!< TPM0_CnV: VAL Mask                      */
#define TPM_CnV_VAL_SHIFT                        0                                                   /*!< TPM0_CnV: VAL Position                  */
#define TPM_CnV_VAL(x)                           (((x)<<TPM_CnV_VAL_SHIFT)&TPM_CnV_VAL_MASK)         /*!< TPM0_CnV                                */

/* ------- TPM0_STATUS                              ------ */
#define TPM_STATUS_CH0F_MASK                     (0x01UL << TPM_STATUS_CH0F_SHIFT)                   /*!< TPM0_STATUS: CH0F Mask                  */
#define TPM_STATUS_CH0F_SHIFT                    0                                                   /*!< TPM0_STATUS: CH0F Position              */
#define TPM_STATUS_CH1F_MASK                     (0x01UL << TPM_STATUS_CH1F_SHIFT)                   /*!< TPM0_STATUS: CH1F Mask                  */
#define TPM_STATUS_CH1F_SHIFT                    1                                                   /*!< TPM0_STATUS: CH1F Position              */
#define TPM_STATUS_CH2F_MASK                     (0x01UL << TPM_STATUS_CH2F_SHIFT)                   /*!< TPM0_STATUS: CH2F Mask                  */
#define TPM_STATUS_CH2F_SHIFT                    2                                                   /*!< TPM0_STATUS: CH2F Position              */
#define TPM_STATUS_CH3F_MASK                     (0x01UL << TPM_STATUS_CH3F_SHIFT)                   /*!< TPM0_STATUS: CH3F Mask                  */
#define TPM_STATUS_CH3F_SHIFT                    3                                                   /*!< TPM0_STATUS: CH3F Position              */
#define TPM_STATUS_CH4F_MASK                     (0x01UL << TPM_STATUS_CH4F_SHIFT)                   /*!< TPM0_STATUS: CH4F Mask                  */
#define TPM_STATUS_CH4F_SHIFT                    4                                                   /*!< TPM0_STATUS: CH4F Position              */
#define TPM_STATUS_CH5F_MASK                     (0x01UL << TPM_STATUS_CH5F_SHIFT)                   /*!< TPM0_STATUS: CH5F Mask                  */
#define TPM_STATUS_CH5F_SHIFT                    5                                                   /*!< TPM0_STATUS: CH5F Position              */
#define TPM_STATUS_TOF_MASK                      (0x01UL << TPM_STATUS_TOF_SHIFT)                    /*!< TPM0_STATUS: TOF Mask                   */
#define TPM_STATUS_TOF_SHIFT                     8                                                   /*!< TPM0_STATUS: TOF Position               */

/* ------- TPM0_CONF                                ------ */
#define TPM_CONF_DOZEEN_MASK                     (0x01UL << TPM_CONF_DOZEEN_SHIFT)                   /*!< TPM0_CONF: DOZEEN Mask                  */
#define TPM_CONF_DOZEEN_SHIFT                    5                                                   /*!< TPM0_CONF: DOZEEN Position              */
#define TPM_CONF_DBGMODE_MASK                    (0x03UL << TPM_CONF_DBGMODE_SHIFT)                  /*!< TPM0_CONF: DBGMODE Mask                 */
#define TPM_CONF_DBGMODE_SHIFT                   6                                                   /*!< TPM0_CONF: DBGMODE Position             */
#define TPM_CONF_DBGMODE(x)                      (((x)<<TPM_CONF_DBGMODE_SHIFT)&TPM_CONF_DBGMODE_MASK) /*!< TPM0_CONF                               */
#define TPM_CONF_GTBEEN_MASK                     (0x01UL << TPM_CONF_GTBEEN_SHIFT)                   /*!< TPM0_CONF: GTBEEN Mask                  */
#define TPM_CONF_GTBEEN_SHIFT                    9                                                   /*!< TPM0_CONF: GTBEEN Position              */
#define TPM_CONF_CSOT_MASK                       (0x01UL << TPM_CONF_CSOT_SHIFT)                     /*!< TPM0_CONF: CSOT Mask                    */
#define TPM_CONF_CSOT_SHIFT                      16                                                  /*!< TPM0_CONF: CSOT Position                */
#define TPM_CONF_CSOO_MASK                       (0x01UL << TPM_CONF_CSOO_SHIFT)                     /*!< TPM0_CONF: CSOO Mask                    */
#define TPM_CONF_CSOO_SHIFT                      17                                                  /*!< TPM0_CONF: CSOO Position                */
#define TPM_CONF_CROT_MASK                       (0x01UL << TPM_CONF_CROT_SHIFT)                     /*!< TPM0_CONF: CROT Mask                    */
#define TPM_CONF_CROT_SHIFT                      18                                                  /*!< TPM0_CONF: CROT Position                */
#define TPM_CONF_TRGSEL_MASK                     (0x0FUL << TPM_CONF_TRGSEL_SHIFT)                   /*!< TPM0_CONF: TRGSEL Mask                  */
#define TPM_CONF_TRGSEL_SHIFT                    24                                                  /*!< TPM0_CONF: TRGSEL Position              */
#define TPM_CONF_TRGSEL(x)                       (((x)<<TPM_CONF_TRGSEL_SHIFT)&TPM_CONF_TRGSEL_MASK) /*!< TPM0_CONF                               */

/* -------------------------------------------------------------------------------- */
/* -----------     'TPM0' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define TPM0_SC                        (TPM0->SC)
#define TPM0_CNT                       (TPM0->CNT)
#define TPM0_MOD                       (TPM0->MOD)
#define TPM0_C0SC                      (TPM0->CONTROLS[0].CnSC)
#define TPM0_C0V                       (TPM0->CONTROLS[0].CnV)
#define TPM0_C1SC                      (TPM0->CONTROLS[1].CnSC)
#define TPM0_C1V                       (TPM0->CONTROLS[1].CnV)
#define TPM0_C2SC                      (TPM0->CONTROLS[2].CnSC)
#define TPM0_C2V                       (TPM0->CONTROLS[2].CnV)
#define TPM0_C3SC                      (TPM0->CONTROLS[3].CnSC)
#define TPM0_C3V                       (TPM0->CONTROLS[3].CnV)
#define TPM0_C4SC                      (TPM0->CONTROLS[4].CnSC)
#define TPM0_C4V                       (TPM0->CONTROLS[4].CnV)
#define TPM0_C5SC                      (TPM0->CONTROLS[5].CnSC)
#define TPM0_C5V                       (TPM0->CONTROLS[5].CnV)
#define TPM0_STATUS                    (TPM0->STATUS)
#define TPM0_CONF                      (TPM0->CONF)

/* ================================================================================ */
/* ================           TPM1 (file:TPM1_2CH)                 ================ */
/* ================================================================================ */

/**
 * @brief Timer/PWM Module (2 channels)
 */
typedef struct {                                /*!<       TPM1 Structure                                               */
   __IO uint32_t  SC;                           /*!< 0000: Status and Control                                           */
   __IO uint32_t  CNT;                          /*!< 0004: Counter                                                      */
   __IO uint32_t  MOD;                          /*!< 0008: Modulo                                                       */
   struct { /* (cluster) */                     /*!< 000C: (size=0x0010, 16)                                            */
      __IO uint32_t  CnSC;                      /*!< 000C: Channel  Status and Control                                  */
      __IO uint32_t  CnV;                       /*!< 0010: Channel  Value                                               */
   } CONTROLS[2];
   __I  uint32_t  RESERVED0[13];                /*!< 001C:                                                              */
   __IO uint32_t  STATUS;                       /*!< 0050: Capture and Compare Status                                   */
   __I  uint32_t  RESERVED1[12];                /*!< 0054:                                                              */
   __IO uint32_t  CONF;                         /*!< 0084: Configuration                                                */
} TPM1_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'TPM1' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- TPM1_SC                                  ------ */

/* ------- TPM1_CNT                                 ------ */

/* ------- TPM1_MOD                                 ------ */

/* ------- TPM1_CnSC                                ------ */

/* ------- TPM1_CnV                                 ------ */

/* ------- TPM1_STATUS                              ------ */

/* ------- TPM1_CONF                                ------ */

/* -------------------------------------------------------------------------------- */
/* -----------     'TPM1' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define TPM1_SC                        (TPM1->SC)
#define TPM1_CNT                       (TPM1->CNT)
#define TPM1_MOD                       (TPM1->MOD)
#define TPM1_C0SC                      (TPM1->CONTROLS[0].CnSC)
#define TPM1_C0V                       (TPM1->CONTROLS[0].CnV)
#define TPM1_C1SC                      (TPM1->CONTROLS[1].CnSC)
#define TPM1_C1V                       (TPM1->CONTROLS[1].CnV)
#define TPM1_STATUS                    (TPM1->STATUS)
#define TPM1_CONF                      (TPM1->CONF)

/* ================================================================================ */
/* ================           TPM2 (derived from TPM1)             ================ */
/* ================================================================================ */

/**
 * @brief Timer/PWM Module (2 channels)
 */
typedef TPM1_Type TPM2_Type;  /*!< TPM2 Structure                                              */


/* -------------------------------------------------------------------------------- */
/* -----------     'TPM2' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define TPM2_SC                        (TPM2->SC)
#define TPM2_CNT                       (TPM2->CNT)
#define TPM2_MOD                       (TPM2->MOD)
#define TPM2_C0SC                      (TPM2->CONTROLS[0].CnSC)
#define TPM2_C0V                       (TPM2->CONTROLS[0].CnV)
#define TPM2_C1SC                      (TPM2->CONTROLS[1].CnSC)
#define TPM2_C1V                       (TPM2->CONTROLS[1].CnV)
#define TPM2_STATUS                    (TPM2->STATUS)
#define TPM2_CONF                      (TPM2->CONF)

/* ================================================================================ */
/* ================           UART2 (file:UART2_MKL)               ================ */
/* ================================================================================ */

/**
 * @brief Universal Asynchronous Receiver/Transmitter
 */
typedef struct {                                /*!<       UART2 Structure                                              */
   __IO uint8_t   BDH;                          /*!< 0000: Baud Rate Register: High                                     */
   __IO uint8_t   BDL;                          /*!< 0001: Baud Rate Register: Low                                      */
   __IO uint8_t   C1;                           /*!< 0002: Control Register 1                                           */
   __IO uint8_t   C2;                           /*!< 0003: Control Register 2                                           */
   __I  uint8_t   S1;                           /*!< 0004: Status Register 1                                            */
   __IO uint8_t   S2;                           /*!< 0005: Status Register 2                                            */
   __IO uint8_t   C3;                           /*!< 0006: Control Register 3                                           */
   __IO uint8_t   D;                            /*!< 0007: Data Register                                                */
   __IO uint8_t   MA1;                          /*!< 0008: Match Address Registers 1                                    */
   __IO uint8_t   MA2;                          /*!< 0009: Match Address Registers 2                                    */
   __IO uint8_t   C4;                           /*!< 000A: Control Register 4                                           */
   __IO uint8_t   C5;                           /*!< 000B: Control Register 5                                           */
   __I  uint32_t  RESERVED0[3];                 /*!< 000C:                                                              */
   __IO uint8_t   C7816;                        /*!< 0018: 7816 Control Register                                        */
   __IO uint8_t   IE7816;                       /*!< 0019: 7816 Interrupt Enable Register                               */
   __IO uint8_t   IS7816;                       /*!< 001A: 7816 Interrupt Status Register                               */
   __IO uint8_t   WP7816;                       /*!< 001B: 7816 Wait Parameter Register                                 */
   __IO uint8_t   WN7816;                       /*!< 001C: 7816 Wait N Register                                         */
   __IO uint8_t   WF7816;                       /*!< 001D: 7816 Wait FD Register                                        */
   __IO uint8_t   ET7816;                       /*!< 001E: 7816 Error Threshold Register                                */
   __IO uint8_t   TL7816;                       /*!< 001F: 7816 Transmit Length Register                                */
   __I  uint16_t  RESERVED1[13];                /*!< 0020:                                                              */
   __IO uint8_t   UART2_AP7816A_T0;             /*!< 003A: 7816 ATR Duration Timer Register A                           */
   __IO uint8_t   UART2_AP7816B_T0;             /*!< 003B: 7816 ATR Duration Timer Register B                           */
   union {                                      /*!< 0000: (size=0001)                                                  */
      __IO uint8_t   UART2_WP7816A_T0;          /*!< 003C: 7816 Wait Parameter Register A                               */
      __IO uint8_t   UART2_WP7816A_T1;          /*!< 003C: 7816 Wait Parameter Register A                               */
   };
   union {                                      /*!< 0000: (size=0001)                                                  */
      __IO uint8_t   UART2_WP7816B_T0;          /*!< 003D: 7816 Wait Parameter Register B                               */
      __IO uint8_t   UART2_WP7816B_T1;          /*!< 003D: 7816 Wait Parameter Register B                               */
   };
   __IO uint8_t   UART2_WGP7816_T1;             /*!< 003E: 7816 Wait and Guard Parameter Register                       */
   __IO uint8_t   UART2_WP7816C_T1;             /*!< 003F: 7816 Wait Parameter Register C                               */
} UART2_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'UART2' Position & Mask macros                       ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- UART2_BDH                                ------ */
#define UART_BDH_SBR_MASK                        (0x1FUL << UART_BDH_SBR_SHIFT)                      /*!< UART2_BDH: SBR Mask                     */
#define UART_BDH_SBR_SHIFT                       0                                                   /*!< UART2_BDH: SBR Position                 */
#define UART_BDH_SBR(x)                          (((x)<<UART_BDH_SBR_SHIFT)&UART_BDH_SBR_MASK)       /*!< UART2_BDH                               */
#define UART_BDH_RXEDGIE_MASK                    (0x01UL << UART_BDH_RXEDGIE_SHIFT)                  /*!< UART2_BDH: RXEDGIE Mask                 */
#define UART_BDH_RXEDGIE_SHIFT                   6                                                   /*!< UART2_BDH: RXEDGIE Position             */

/* ------- UART2_BDL                                ------ */
#define UART_BDL_SBR_MASK                        (0xFFUL << UART_BDL_SBR_SHIFT)                      /*!< UART2_BDL: SBR Mask                     */
#define UART_BDL_SBR_SHIFT                       0                                                   /*!< UART2_BDL: SBR Position                 */
#define UART_BDL_SBR(x)                          (((x)<<UART_BDL_SBR_SHIFT)&UART_BDL_SBR_MASK)       /*!< UART2_BDL                               */

/* ------- UART2_C1                                 ------ */
#define UART_C1_PT_MASK                          (0x01UL << UART_C1_PT_SHIFT)                        /*!< UART2_C1: PT Mask                       */
#define UART_C1_PT_SHIFT                         0                                                   /*!< UART2_C1: PT Position                   */
#define UART_C1_PE_MASK                          (0x01UL << UART_C1_PE_SHIFT)                        /*!< UART2_C1: PE Mask                       */
#define UART_C1_PE_SHIFT                         1                                                   /*!< UART2_C1: PE Position                   */
#define UART_C1_ILT_MASK                         (0x01UL << UART_C1_ILT_SHIFT)                       /*!< UART2_C1: ILT Mask                      */
#define UART_C1_ILT_SHIFT                        2                                                   /*!< UART2_C1: ILT Position                  */
#define UART_C1_WAKE_MASK                        (0x01UL << UART_C1_WAKE_SHIFT)                      /*!< UART2_C1: WAKE Mask                     */
#define UART_C1_WAKE_SHIFT                       3                                                   /*!< UART2_C1: WAKE Position                 */
#define UART_C1_M_MASK                           (0x01UL << UART_C1_M_SHIFT)                         /*!< UART2_C1: M Mask                        */
#define UART_C1_M_SHIFT                          4                                                   /*!< UART2_C1: M Position                    */
#define UART_C1_RSRC_MASK                        (0x01UL << UART_C1_RSRC_SHIFT)                      /*!< UART2_C1: RSRC Mask                     */
#define UART_C1_RSRC_SHIFT                       5                                                   /*!< UART2_C1: RSRC Position                 */
#define UART_C1_LOOPS_MASK                       (0x01UL << UART_C1_LOOPS_SHIFT)                     /*!< UART2_C1: LOOPS Mask                    */
#define UART_C1_LOOPS_SHIFT                      7                                                   /*!< UART2_C1: LOOPS Position                */

/* ------- UART2_C2                                 ------ */
#define UART_C2_SBK_MASK                         (0x01UL << UART_C2_SBK_SHIFT)                       /*!< UART2_C2: SBK Mask                      */
#define UART_C2_SBK_SHIFT                        0                                                   /*!< UART2_C2: SBK Position                  */
#define UART_C2_RWU_MASK                         (0x01UL << UART_C2_RWU_SHIFT)                       /*!< UART2_C2: RWU Mask                      */
#define UART_C2_RWU_SHIFT                        1                                                   /*!< UART2_C2: RWU Position                  */
#define UART_C2_RE_MASK                          (0x01UL << UART_C2_RE_SHIFT)                        /*!< UART2_C2: RE Mask                       */
#define UART_C2_RE_SHIFT                         2                                                   /*!< UART2_C2: RE Position                   */
#define UART_C2_TE_MASK                          (0x01UL << UART_C2_TE_SHIFT)                        /*!< UART2_C2: TE Mask                       */
#define UART_C2_TE_SHIFT                         3                                                   /*!< UART2_C2: TE Position                   */
#define UART_C2_ILIE_MASK                        (0x01UL << UART_C2_ILIE_SHIFT)                      /*!< UART2_C2: ILIE Mask                     */
#define UART_C2_ILIE_SHIFT                       4                                                   /*!< UART2_C2: ILIE Position                 */
#define UART_C2_RIE_MASK                         (0x01UL << UART_C2_RIE_SHIFT)                       /*!< UART2_C2: RIE Mask                      */
#define UART_C2_RIE_SHIFT                        5                                                   /*!< UART2_C2: RIE Position                  */
#define UART_C2_TCIE_MASK                        (0x01UL << UART_C2_TCIE_SHIFT)                      /*!< UART2_C2: TCIE Mask                     */
#define UART_C2_TCIE_SHIFT                       6                                                   /*!< UART2_C2: TCIE Position                 */
#define UART_C2_TIE_MASK                         (0x01UL << UART_C2_TIE_SHIFT)                       /*!< UART2_C2: TIE Mask                      */
#define UART_C2_TIE_SHIFT                        7                                                   /*!< UART2_C2: TIE Position                  */

/* ------- UART2_S1                                 ------ */
#define UART_S1_PF_MASK                          (0x01UL << UART_S1_PF_SHIFT)                        /*!< UART2_S1: PF Mask                       */
#define UART_S1_PF_SHIFT                         0                                                   /*!< UART2_S1: PF Position                   */
#define UART_S1_FE_MASK                          (0x01UL << UART_S1_FE_SHIFT)                        /*!< UART2_S1: FE Mask                       */
#define UART_S1_FE_SHIFT                         1                                                   /*!< UART2_S1: FE Position                   */
#define UART_S1_NF_MASK                          (0x01UL << UART_S1_NF_SHIFT)                        /*!< UART2_S1: NF Mask                       */
#define UART_S1_NF_SHIFT                         2                                                   /*!< UART2_S1: NF Position                   */
#define UART_S1_OR_MASK                          (0x01UL << UART_S1_OR_SHIFT)                        /*!< UART2_S1: OR Mask                       */
#define UART_S1_OR_SHIFT                         3                                                   /*!< UART2_S1: OR Position                   */
#define UART_S1_IDLE_MASK                        (0x01UL << UART_S1_IDLE_SHIFT)                      /*!< UART2_S1: IDLE Mask                     */
#define UART_S1_IDLE_SHIFT                       4                                                   /*!< UART2_S1: IDLE Position                 */
#define UART_S1_RDRF_MASK                        (0x01UL << UART_S1_RDRF_SHIFT)                      /*!< UART2_S1: RDRF Mask                     */
#define UART_S1_RDRF_SHIFT                       5                                                   /*!< UART2_S1: RDRF Position                 */
#define UART_S1_TC_MASK                          (0x01UL << UART_S1_TC_SHIFT)                        /*!< UART2_S1: TC Mask                       */
#define UART_S1_TC_SHIFT                         6                                                   /*!< UART2_S1: TC Position                   */
#define UART_S1_TDRE_MASK                        (0x01UL << UART_S1_TDRE_SHIFT)                      /*!< UART2_S1: TDRE Mask                     */
#define UART_S1_TDRE_SHIFT                       7                                                   /*!< UART2_S1: TDRE Position                 */

/* ------- UART2_S2                                 ------ */
#define UART_S2_RAF_MASK                         (0x01UL << UART_S2_RAF_SHIFT)                       /*!< UART2_S2: RAF Mask                      */
#define UART_S2_RAF_SHIFT                        0                                                   /*!< UART2_S2: RAF Position                  */
#define UART_S2_BRK13_MASK                       (0x01UL << UART_S2_BRK13_SHIFT)                     /*!< UART2_S2: BRK13 Mask                    */
#define UART_S2_BRK13_SHIFT                      2                                                   /*!< UART2_S2: BRK13 Position                */
#define UART_S2_RWUID_MASK                       (0x01UL << UART_S2_RWUID_SHIFT)                     /*!< UART2_S2: RWUID Mask                    */
#define UART_S2_RWUID_SHIFT                      3                                                   /*!< UART2_S2: RWUID Position                */
#define UART_S2_RXINV_MASK                       (0x01UL << UART_S2_RXINV_SHIFT)                     /*!< UART2_S2: RXINV Mask                    */
#define UART_S2_RXINV_SHIFT                      4                                                   /*!< UART2_S2: RXINV Position                */
#define UART_S2_MSBF_MASK                        (0x01UL << UART_S2_MSBF_SHIFT)                      /*!< UART2_S2: MSBF Mask                     */
#define UART_S2_MSBF_SHIFT                       5                                                   /*!< UART2_S2: MSBF Position                 */
#define UART_S2_RXEDGIF_MASK                     (0x01UL << UART_S2_RXEDGIF_SHIFT)                   /*!< UART2_S2: RXEDGIF Mask                  */
#define UART_S2_RXEDGIF_SHIFT                    6                                                   /*!< UART2_S2: RXEDGIF Position              */

/* ------- UART2_C3                                 ------ */
#define UART_C3_PEIE_MASK                        (0x01UL << UART_C3_PEIE_SHIFT)                      /*!< UART2_C3: PEIE Mask                     */
#define UART_C3_PEIE_SHIFT                       0                                                   /*!< UART2_C3: PEIE Position                 */
#define UART_C3_FEIE_MASK                        (0x01UL << UART_C3_FEIE_SHIFT)                      /*!< UART2_C3: FEIE Mask                     */
#define UART_C3_FEIE_SHIFT                       1                                                   /*!< UART2_C3: FEIE Position                 */
#define UART_C3_NEIE_MASK                        (0x01UL << UART_C3_NEIE_SHIFT)                      /*!< UART2_C3: NEIE Mask                     */
#define UART_C3_NEIE_SHIFT                       2                                                   /*!< UART2_C3: NEIE Position                 */
#define UART_C3_ORIE_MASK                        (0x01UL << UART_C3_ORIE_SHIFT)                      /*!< UART2_C3: ORIE Mask                     */
#define UART_C3_ORIE_SHIFT                       3                                                   /*!< UART2_C3: ORIE Position                 */
#define UART_C3_TXINV_MASK                       (0x01UL << UART_C3_TXINV_SHIFT)                     /*!< UART2_C3: TXINV Mask                    */
#define UART_C3_TXINV_SHIFT                      4                                                   /*!< UART2_C3: TXINV Position                */
#define UART_C3_TXDIR_MASK                       (0x01UL << UART_C3_TXDIR_SHIFT)                     /*!< UART2_C3: TXDIR Mask                    */
#define UART_C3_TXDIR_SHIFT                      5                                                   /*!< UART2_C3: TXDIR Position                */
#define UART_C3_T8_MASK                          (0x01UL << UART_C3_T8_SHIFT)                        /*!< UART2_C3: T8 Mask                       */
#define UART_C3_T8_SHIFT                         6                                                   /*!< UART2_C3: T8 Position                   */
#define UART_C3_R8_MASK                          (0x01UL << UART_C3_R8_SHIFT)                        /*!< UART2_C3: R8 Mask                       */
#define UART_C3_R8_SHIFT                         7                                                   /*!< UART2_C3: R8 Position                   */

/* ------- UART2_D                                  ------ */
#define UART_D_RT_MASK                           (0xFFUL << UART_D_RT_SHIFT)                         /*!< UART2_D: RT Mask                        */
#define UART_D_RT_SHIFT                          0                                                   /*!< UART2_D: RT Position                    */
#define UART_D_RT(x)                             (((x)<<UART_D_RT_SHIFT)&UART_D_RT_MASK)             /*!< UART2_D                                 */

/* ------- UART2_MA                                 ------ */
#define UART_MA_MA_MASK                          (0xFFUL << UART_MA_MA_SHIFT)                        /*!< UART2_MA: MA Mask                       */
#define UART_MA_MA_SHIFT                         0                                                   /*!< UART2_MA: MA Position                   */
#define UART_MA_MA(x)                            (((x)<<UART_MA_MA_SHIFT)&UART_MA_MA_MASK)           /*!< UART2_MA                                */

/* ------- UART2_C4                                 ------ */
#define UART_C4_BRFA_MASK                        (0x1FUL << UART_C4_BRFA_SHIFT)                      /*!< UART2_C4: BRFA Mask                     */
#define UART_C4_BRFA_SHIFT                       0                                                   /*!< UART2_C4: BRFA Position                 */
#define UART_C4_BRFA(x)                          (((x)<<UART_C4_BRFA_SHIFT)&UART_C4_BRFA_MASK)       /*!< UART2_C4                                */
#define UART_C4_M10_MASK                         (0x01UL << UART_C4_M10_SHIFT)                       /*!< UART2_C4: M10 Mask                      */
#define UART_C4_M10_SHIFT                        5                                                   /*!< UART2_C4: M10 Position                  */
#define UART_C4_MAEN2_MASK                       (0x01UL << UART_C4_MAEN2_SHIFT)                     /*!< UART2_C4: MAEN2 Mask                    */
#define UART_C4_MAEN2_SHIFT                      6                                                   /*!< UART2_C4: MAEN2 Position                */
#define UART_C4_MAEN1_MASK                       (0x01UL << UART_C4_MAEN1_SHIFT)                     /*!< UART2_C4: MAEN1 Mask                    */
#define UART_C4_MAEN1_SHIFT                      7                                                   /*!< UART2_C4: MAEN1 Position                */

/* ------- UART2_C5                                 ------ */
#define UART_C5_RDMAS_MASK                       (0x01UL << UART_C5_RDMAS_SHIFT)                     /*!< UART2_C5: RDMAS Mask                    */
#define UART_C5_RDMAS_SHIFT                      5                                                   /*!< UART2_C5: RDMAS Position                */
#define UART_C5_TDMAS_MASK                       (0x01UL << UART_C5_TDMAS_SHIFT)                     /*!< UART2_C5: TDMAS Mask                    */
#define UART_C5_TDMAS_SHIFT                      7                                                   /*!< UART2_C5: TDMAS Position                */

/* ------- UART2_C7816                              ------ */
#define UART_C7816_ISO_7816E_MASK                (0x01UL << UART_C7816_ISO_7816E_SHIFT)              /*!< UART2_C7816: ISO_7816E Mask             */
#define UART_C7816_ISO_7816E_SHIFT               0                                                   /*!< UART2_C7816: ISO_7816E Position         */
#define UART_C7816_TTYPE_MASK                    (0x01UL << UART_C7816_TTYPE_SHIFT)                  /*!< UART2_C7816: TTYPE Mask                 */
#define UART_C7816_TTYPE_SHIFT                   1                                                   /*!< UART2_C7816: TTYPE Position             */
#define UART_C7816_INIT_MASK                     (0x01UL << UART_C7816_INIT_SHIFT)                   /*!< UART2_C7816: INIT Mask                  */
#define UART_C7816_INIT_SHIFT                    2                                                   /*!< UART2_C7816: INIT Position              */
#define UART_C7816_ANACK_MASK                    (0x01UL << UART_C7816_ANACK_SHIFT)                  /*!< UART2_C7816: ANACK Mask                 */
#define UART_C7816_ANACK_SHIFT                   3                                                   /*!< UART2_C7816: ANACK Position             */
#define UART_C7816_ONACK_MASK                    (0x01UL << UART_C7816_ONACK_SHIFT)                  /*!< UART2_C7816: ONACK Mask                 */
#define UART_C7816_ONACK_SHIFT                   4                                                   /*!< UART2_C7816: ONACK Position             */

/* ------- UART2_IE7816                             ------ */
#define UART_IE7816_RXTE_MASK                    (0x01UL << UART_IE7816_RXTE_SHIFT)                  /*!< UART2_IE7816: RXTE Mask                 */
#define UART_IE7816_RXTE_SHIFT                   0                                                   /*!< UART2_IE7816: RXTE Position             */
#define UART_IE7816_TXTE_MASK                    (0x01UL << UART_IE7816_TXTE_SHIFT)                  /*!< UART2_IE7816: TXTE Mask                 */
#define UART_IE7816_TXTE_SHIFT                   1                                                   /*!< UART2_IE7816: TXTE Position             */
#define UART_IE7816_GTVE_MASK                    (0x01UL << UART_IE7816_GTVE_SHIFT)                  /*!< UART2_IE7816: GTVE Mask                 */
#define UART_IE7816_GTVE_SHIFT                   2                                                   /*!< UART2_IE7816: GTVE Position             */
#define UART_IE7816_ADTE_MASK                    (0x01UL << UART_IE7816_ADTE_SHIFT)                  /*!< UART2_IE7816: ADTE Mask                 */
#define UART_IE7816_ADTE_SHIFT                   3                                                   /*!< UART2_IE7816: ADTE Position             */
#define UART_IE7816_INITDE_MASK                  (0x01UL << UART_IE7816_INITDE_SHIFT)                /*!< UART2_IE7816: INITDE Mask               */
#define UART_IE7816_INITDE_SHIFT                 4                                                   /*!< UART2_IE7816: INITDE Position           */
#define UART_IE7816_BWTE_MASK                    (0x01UL << UART_IE7816_BWTE_SHIFT)                  /*!< UART2_IE7816: BWTE Mask                 */
#define UART_IE7816_BWTE_SHIFT                   5                                                   /*!< UART2_IE7816: BWTE Position             */
#define UART_IE7816_CWTE_MASK                    (0x01UL << UART_IE7816_CWTE_SHIFT)                  /*!< UART2_IE7816: CWTE Mask                 */
#define UART_IE7816_CWTE_SHIFT                   6                                                   /*!< UART2_IE7816: CWTE Position             */
#define UART_IE7816_WTE_MASK                     (0x01UL << UART_IE7816_WTE_SHIFT)                   /*!< UART2_IE7816: WTE Mask                  */
#define UART_IE7816_WTE_SHIFT                    7                                                   /*!< UART2_IE7816: WTE Position              */

/* ------- UART2_IS7816                             ------ */
#define UART_IS7816_RXT_MASK                     (0x01UL << UART_IS7816_RXT_SHIFT)                   /*!< UART2_IS7816: RXT Mask                  */
#define UART_IS7816_RXT_SHIFT                    0                                                   /*!< UART2_IS7816: RXT Position              */
#define UART_IS7816_TXT_MASK                     (0x01UL << UART_IS7816_TXT_SHIFT)                   /*!< UART2_IS7816: TXT Mask                  */
#define UART_IS7816_TXT_SHIFT                    1                                                   /*!< UART2_IS7816: TXT Position              */
#define UART_IS7816_GTV_MASK                     (0x01UL << UART_IS7816_GTV_SHIFT)                   /*!< UART2_IS7816: GTV Mask                  */
#define UART_IS7816_GTV_SHIFT                    2                                                   /*!< UART2_IS7816: GTV Position              */
#define UART_IS7816_ADT_MASK                     (0x01UL << UART_IS7816_ADT_SHIFT)                   /*!< UART2_IS7816: ADT Mask                  */
#define UART_IS7816_ADT_SHIFT                    3                                                   /*!< UART2_IS7816: ADT Position              */
#define UART_IS7816_INITD_MASK                   (0x01UL << UART_IS7816_INITD_SHIFT)                 /*!< UART2_IS7816: INITD Mask                */
#define UART_IS7816_INITD_SHIFT                  4                                                   /*!< UART2_IS7816: INITD Position            */
#define UART_IS7816_BWT_MASK                     (0x01UL << UART_IS7816_BWT_SHIFT)                   /*!< UART2_IS7816: BWT Mask                  */
#define UART_IS7816_BWT_SHIFT                    5                                                   /*!< UART2_IS7816: BWT Position              */
#define UART_IS7816_CWT_MASK                     (0x01UL << UART_IS7816_CWT_SHIFT)                   /*!< UART2_IS7816: CWT Mask                  */
#define UART_IS7816_CWT_SHIFT                    6                                                   /*!< UART2_IS7816: CWT Position              */
#define UART_IS7816_WT_MASK                      (0x01UL << UART_IS7816_WT_SHIFT)                    /*!< UART2_IS7816: WT Mask                   */
#define UART_IS7816_WT_SHIFT                     7                                                   /*!< UART2_IS7816: WT Position               */

/* ------- UART2_WP7816                             ------ */
#define UART_WP7816_WTX_MASK                     (0xFFUL << UART_WP7816_WTX_SHIFT)                   /*!< UART2_WP7816: WTX Mask                  */
#define UART_WP7816_WTX_SHIFT                    0                                                   /*!< UART2_WP7816: WTX Position              */
#define UART_WP7816_WTX(x)                       (((x)<<UART_WP7816_WTX_SHIFT)&UART_WP7816_WTX_MASK) /*!< UART2_WP7816                            */

/* ------- UART2_WN7816                             ------ */
#define UART_WN7816_GTN_MASK                     (0xFFUL << UART_WN7816_GTN_SHIFT)                   /*!< UART2_WN7816: GTN Mask                  */
#define UART_WN7816_GTN_SHIFT                    0                                                   /*!< UART2_WN7816: GTN Position              */
#define UART_WN7816_GTN(x)                       (((x)<<UART_WN7816_GTN_SHIFT)&UART_WN7816_GTN_MASK) /*!< UART2_WN7816                            */

/* ------- UART2_WF7816                             ------ */
#define UART_WF7816_GTFD_MASK                    (0xFFUL << UART_WF7816_GTFD_SHIFT)                  /*!< UART2_WF7816: GTFD Mask                 */
#define UART_WF7816_GTFD_SHIFT                   0                                                   /*!< UART2_WF7816: GTFD Position             */
#define UART_WF7816_GTFD(x)                      (((x)<<UART_WF7816_GTFD_SHIFT)&UART_WF7816_GTFD_MASK) /*!< UART2_WF7816                            */

/* ------- UART2_ET7816                             ------ */
#define UART_ET7816_RXTHRESHOLD_MASK             (0x0FUL << UART_ET7816_RXTHRESHOLD_SHIFT)           /*!< UART2_ET7816: RXTHRESHOLD Mask          */
#define UART_ET7816_RXTHRESHOLD_SHIFT            0                                                   /*!< UART2_ET7816: RXTHRESHOLD Position      */
#define UART_ET7816_RXTHRESHOLD(x)               (((x)<<UART_ET7816_RXTHRESHOLD_SHIFT)&UART_ET7816_RXTHRESHOLD_MASK) /*!< UART2_ET7816                            */
#define UART_ET7816_TXTHRESHOLD_MASK             (0x0FUL << UART_ET7816_TXTHRESHOLD_SHIFT)           /*!< UART2_ET7816: TXTHRESHOLD Mask          */
#define UART_ET7816_TXTHRESHOLD_SHIFT            4                                                   /*!< UART2_ET7816: TXTHRESHOLD Position      */
#define UART_ET7816_TXTHRESHOLD(x)               (((x)<<UART_ET7816_TXTHRESHOLD_SHIFT)&UART_ET7816_TXTHRESHOLD_MASK) /*!< UART2_ET7816                            */

/* ------- UART2_TL7816                             ------ */
#define UART_TL7816_TLEN_MASK                    (0xFFUL << UART_TL7816_TLEN_SHIFT)                  /*!< UART2_TL7816: TLEN Mask                 */
#define UART_TL7816_TLEN_SHIFT                   0                                                   /*!< UART2_TL7816: TLEN Position             */
#define UART_TL7816_TLEN(x)                      (((x)<<UART_TL7816_TLEN_SHIFT)&UART_TL7816_TLEN_MASK) /*!< UART2_TL7816                            */

/* ------- UART2_UART2_AP7816A_T0                   ------ */

/* ------- UART2_UART2_AP7816B_T0                   ------ */

/* ------- UART2_UART2_WP7816A_T0                   ------ */

/* ------- UART2_UART2_WP7816A_T1                   ------ */

/* ------- UART2_UART2_WP7816B_T0                   ------ */

/* ------- UART2_UART2_WP7816B_T1                   ------ */

/* ------- UART2_UART2_WGP7816_T1                   ------ */

/* ------- UART2_UART2_WP7816C_T1                   ------ */

/* -------------------------------------------------------------------------------- */
/* -----------     'UART2' Register Access macros                       ----------- */
/* -------------------------------------------------------------------------------- */

#define UART2_BDH                      (UART2->BDH)
#define UART2_BDL                      (UART2->BDL)
#define UART2_C1                       (UART2->C1)
#define UART2_C2                       (UART2->C2)
#define UART2_S1                       (UART2->S1)
#define UART2_S2                       (UART2->S2)
#define UART2_C3                       (UART2->C3)
#define UART2_D                        (UART2->D)
#define UART2_MA1                      (UART2->MA1)
#define UART2_MA2                      (UART2->MA2)
#define UART2_C4                       (UART2->C4)
#define UART2_C5                       (UART2->C5)
#define UART2_C7816                    (UART2->C7816)
#define UART2_IE7816                   (UART2->IE7816)
#define UART2_IS7816                   (UART2->IS7816)
#define UART2_WP7816                   (UART2->WP7816)
#define UART2_WN7816                   (UART2->WN7816)
#define UART2_WF7816                   (UART2->WF7816)
#define UART2_ET7816                   (UART2->ET7816)
#define UART2_TL7816                   (UART2->TL7816)
#define UART2_UART2_AP7816A_T0         (UART2->UART2_AP7816A_T0)
#define UART2_UART2_AP7816B_T0         (UART2->UART2_AP7816B_T0)
#define UART2_UART2_WP7816A_T0         (UART2->UART2_WP7816A_T0)
#define UART2_UART2_WP7816A_T1         (UART2->UART2_WP7816A_T1)
#define UART2_UART2_WP7816B_T0         (UART2->UART2_WP7816B_T0)
#define UART2_UART2_WP7816B_T1         (UART2->UART2_WP7816B_T1)
#define UART2_UART2_WGP7816_T1         (UART2->UART2_WGP7816_T1)
#define UART2_UART2_WP7816C_T1         (UART2->UART2_WP7816C_T1)

/* ================================================================================ */
/* ================           USB0 (file:USB0_MK_MKL)              ================ */
/* ================================================================================ */

/**
 * @brief Universal Serial Bus, OTG Capable Controller
 */
typedef struct {                                /*!<       USB0 Structure                                               */
   __I  uint8_t   PERID;                        /*!< 0000: Peripheral ID Register                                       */
   __I  uint8_t   RESERVED0[3];                 /*!< 0001:                                                              */
   __I  uint8_t   IDCOMP;                       /*!< 0004: Peripheral ID Complement Register                            */
   __I  uint8_t   RESERVED1[3];                 /*!< 0005:                                                              */
   __I  uint8_t   REV;                          /*!< 0008: Peripheral Revision Register                                 */
   __I  uint8_t   RESERVED2[3];                 /*!< 0009:                                                              */
   __I  uint8_t   ADDINFO;                      /*!< 000C: Peripheral Additional Info Register                          */
   __I  uint8_t   RESERVED3[3];                 /*!< 000D:                                                              */
   __IO uint8_t   OTGISTAT;                     /*!< 0010: OTG Interrupt Status Register                                */
   __I  uint8_t   RESERVED4[3];                 /*!< 0011:                                                              */
   __IO uint8_t   OTGICR;                       /*!< 0014: OTG Interrupt Control Register                               */
   __I  uint8_t   RESERVED5[3];                 /*!< 0015:                                                              */
   __IO uint8_t   OTGSTAT;                      /*!< 0018: OTG Status Register                                          */
   __I  uint8_t   RESERVED6[3];                 /*!< 0019:                                                              */
   __IO uint8_t   OTGCTL;                       /*!< 001C: OTG Control Register                                         */
   __I  uint8_t   RESERVED7[99];                /*!< 001D:                                                              */
   __IO uint8_t   ISTAT;                        /*!< 0080: Interrupt Status Register                                    */
   __I  uint8_t   RESERVED8[3];                 /*!< 0081:                                                              */
   __IO uint8_t   INTEN;                        /*!< 0084: Interrupt Enable Register                                    */
   __I  uint8_t   RESERVED9[3];                 /*!< 0085:                                                              */
   __IO uint8_t   ERRSTAT;                      /*!< 0088: Error Interrupt Status Register                              */
   __I  uint8_t   RESERVED10[3];                /*!< 0089:                                                              */
   __IO uint8_t   ERREN;                        /*!< 008C: Error Interrupt Enable Register                              */
   __I  uint8_t   RESERVED11[3];                /*!< 008D:                                                              */
   __I  uint8_t   STAT;                         /*!< 0090: Status Register                                              */
   __I  uint8_t   RESERVED12[3];                /*!< 0091:                                                              */
   __IO uint8_t   CTL;                          /*!< 0094: Control register                                             */
   __I  uint8_t   RESERVED13[3];                /*!< 0095:                                                              */
   __IO uint8_t   ADDR;                         /*!< 0098: Address Register                                             */
   __I  uint8_t   RESERVED14[3];                /*!< 0099:                                                              */
   __IO uint8_t   BDTPAGE1;                     /*!< 009C: BDT Page Register 1                                          */
   __I  uint8_t   RESERVED15[3];                /*!< 009D:                                                              */
   __IO uint8_t   FRMNUML;                      /*!< 00A0: Frame Number Register Low                                    */
   __I  uint8_t   RESERVED16[3];                /*!< 00A1:                                                              */
   __IO uint8_t   FRMNUMH;                      /*!< 00A4: Frame Number Register High                                   */
   __I  uint8_t   RESERVED17[3];                /*!< 00A5:                                                              */
   __IO uint8_t   TOKEN;                        /*!< 00A8: Token Register                                               */
   __I  uint8_t   RESERVED18[3];                /*!< 00A9:                                                              */
   __IO uint8_t   SOFTHLD;                      /*!< 00AC: SOF Threshold Register                                       */
   __I  uint8_t   RESERVED19[3];                /*!< 00AD:                                                              */
   __IO uint8_t   BDTPAGE2;                     /*!< 00B0: BDT Page Register 2                                          */
   __I  uint8_t   RESERVED20[3];                /*!< 00B1:                                                              */
   __IO uint8_t   BDTPAGE3;                     /*!< 00B4: BDT Page Register 3                                          */
   __I  uint8_t   RESERVED21[11];               /*!< 00B5:                                                              */
   struct { /* (cluster) */                     /*!< 00C0: (size=0x0040, 64)                                            */
      __IO uint8_t   ENDPT;                     /*!< 00C0: Endpoint Control Register                                    */
      __I  uint8_t   RESERVED0[3];              /*!< 00C1:                                                              */
   } ENDPOINT[16];
   __IO uint8_t   USBCTRL;                      /*!< 0100: USB Control Register                                         */
   __I  uint8_t   RESERVED22[3];                /*!< 0101:                                                              */
   __I  uint8_t   OBSERVE;                      /*!< 0104: USB OTG Observe Register                                     */
   __I  uint8_t   RESERVED23[3];                /*!< 0105:                                                              */
   __IO uint8_t   CONTROL;                      /*!< 0108: USB OTG Control Register                                     */
   __I  uint8_t   RESERVED24[3];                /*!< 0109:                                                              */
   __IO uint8_t   USBTRC0;                      /*!< 010C: USB Transceiver Control Register 0                           */
   __I  uint8_t   RESERVED25[7];                /*!< 010D:                                                              */
   __IO uint8_t   USBFRMADJUST;                 /*!< 0114: Frame Adjust Register                                        */
} USB0_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'USB0' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- USB0_PERID                               ------ */
#define USB_PERID_ID_MASK                        (0x3FUL << USB_PERID_ID_SHIFT)                      /*!< USB0_PERID: ID Mask                     */
#define USB_PERID_ID_SHIFT                       0                                                   /*!< USB0_PERID: ID Position                 */
#define USB_PERID_ID(x)                          (((x)<<USB_PERID_ID_SHIFT)&USB_PERID_ID_MASK)       /*!< USB0_PERID                              */

/* ------- USB0_IDCOMP                              ------ */
#define USB_IDCOMP_NID_MASK                      (0x3FUL << USB_IDCOMP_NID_SHIFT)                    /*!< USB0_IDCOMP: NID Mask                   */
#define USB_IDCOMP_NID_SHIFT                     0                                                   /*!< USB0_IDCOMP: NID Position               */
#define USB_IDCOMP_NID(x)                        (((x)<<USB_IDCOMP_NID_SHIFT)&USB_IDCOMP_NID_MASK)   /*!< USB0_IDCOMP                             */

/* ------- USB0_REV                                 ------ */
#define USB_REV_REV_MASK                         (0xFFUL << USB_REV_REV_SHIFT)                       /*!< USB0_REV: REV Mask                      */
#define USB_REV_REV_SHIFT                        0                                                   /*!< USB0_REV: REV Position                  */
#define USB_REV_REV(x)                           (((x)<<USB_REV_REV_SHIFT)&USB_REV_REV_MASK)         /*!< USB0_REV                                */

/* ------- USB0_ADDINFO                             ------ */
#define USB_ADDINFO_IEHOST_MASK                  (0x01UL << USB_ADDINFO_IEHOST_SHIFT)                /*!< USB0_ADDINFO: IEHOST Mask               */
#define USB_ADDINFO_IEHOST_SHIFT                 0                                                   /*!< USB0_ADDINFO: IEHOST Position           */
#define USB_ADDINFO_IRQNUM_MASK                  (0x1FUL << USB_ADDINFO_IRQNUM_SHIFT)                /*!< USB0_ADDINFO: IRQNUM Mask               */
#define USB_ADDINFO_IRQNUM_SHIFT                 3                                                   /*!< USB0_ADDINFO: IRQNUM Position           */
#define USB_ADDINFO_IRQNUM(x)                    (((x)<<USB_ADDINFO_IRQNUM_SHIFT)&USB_ADDINFO_IRQNUM_MASK) /*!< USB0_ADDINFO                            */

/* ------- USB0_OTGISTAT                            ------ */
#define USB_OTGISTAT_AVBUSCHG_MASK               (0x01UL << USB_OTGISTAT_AVBUSCHG_SHIFT)             /*!< USB0_OTGISTAT: AVBUSCHG Mask            */
#define USB_OTGISTAT_AVBUSCHG_SHIFT              0                                                   /*!< USB0_OTGISTAT: AVBUSCHG Position        */
#define USB_OTGISTAT_B_SESS_CHG_MASK             (0x01UL << USB_OTGISTAT_B_SESS_CHG_SHIFT)           /*!< USB0_OTGISTAT: B_SESS_CHG Mask          */
#define USB_OTGISTAT_B_SESS_CHG_SHIFT            2                                                   /*!< USB0_OTGISTAT: B_SESS_CHG Position      */
#define USB_OTGISTAT_SESSVLDCHG_MASK             (0x01UL << USB_OTGISTAT_SESSVLDCHG_SHIFT)           /*!< USB0_OTGISTAT: SESSVLDCHG Mask          */
#define USB_OTGISTAT_SESSVLDCHG_SHIFT            3                                                   /*!< USB0_OTGISTAT: SESSVLDCHG Position      */
#define USB_OTGISTAT_LINE_STATE_CHG_MASK         (0x01UL << USB_OTGISTAT_LINE_STATE_CHG_SHIFT)       /*!< USB0_OTGISTAT: LINE_STATE_CHG Mask      */
#define USB_OTGISTAT_LINE_STATE_CHG_SHIFT        5                                                   /*!< USB0_OTGISTAT: LINE_STATE_CHG Position  */
#define USB_OTGISTAT_ONEMSEC_MASK                (0x01UL << USB_OTGISTAT_ONEMSEC_SHIFT)              /*!< USB0_OTGISTAT: ONEMSEC Mask             */
#define USB_OTGISTAT_ONEMSEC_SHIFT               6                                                   /*!< USB0_OTGISTAT: ONEMSEC Position         */
#define USB_OTGISTAT_IDCHG_MASK                  (0x01UL << USB_OTGISTAT_IDCHG_SHIFT)                /*!< USB0_OTGISTAT: IDCHG Mask               */
#define USB_OTGISTAT_IDCHG_SHIFT                 7                                                   /*!< USB0_OTGISTAT: IDCHG Position           */

/* ------- USB0_OTGICR                              ------ */
#define USB_OTGICR_AVBUSEN_MASK                  (0x01UL << USB_OTGICR_AVBUSEN_SHIFT)                /*!< USB0_OTGICR: AVBUSEN Mask               */
#define USB_OTGICR_AVBUSEN_SHIFT                 0                                                   /*!< USB0_OTGICR: AVBUSEN Position           */
#define USB_OTGICR_BSESSEN_MASK                  (0x01UL << USB_OTGICR_BSESSEN_SHIFT)                /*!< USB0_OTGICR: BSESSEN Mask               */
#define USB_OTGICR_BSESSEN_SHIFT                 2                                                   /*!< USB0_OTGICR: BSESSEN Position           */
#define USB_OTGICR_SESSVLDEN_MASK                (0x01UL << USB_OTGICR_SESSVLDEN_SHIFT)              /*!< USB0_OTGICR: SESSVLDEN Mask             */
#define USB_OTGICR_SESSVLDEN_SHIFT               3                                                   /*!< USB0_OTGICR: SESSVLDEN Position         */
#define USB_OTGICR_LINESTATEEN_MASK              (0x01UL << USB_OTGICR_LINESTATEEN_SHIFT)            /*!< USB0_OTGICR: LINESTATEEN Mask           */
#define USB_OTGICR_LINESTATEEN_SHIFT             5                                                   /*!< USB0_OTGICR: LINESTATEEN Position       */
#define USB_OTGICR_ONEMSECEN_MASK                (0x01UL << USB_OTGICR_ONEMSECEN_SHIFT)              /*!< USB0_OTGICR: ONEMSECEN Mask             */
#define USB_OTGICR_ONEMSECEN_SHIFT               6                                                   /*!< USB0_OTGICR: ONEMSECEN Position         */
#define USB_OTGICR_IDEN_MASK                     (0x01UL << USB_OTGICR_IDEN_SHIFT)                   /*!< USB0_OTGICR: IDEN Mask                  */
#define USB_OTGICR_IDEN_SHIFT                    7                                                   /*!< USB0_OTGICR: IDEN Position              */

/* ------- USB0_OTGSTAT                             ------ */
#define USB_OTGSTAT_AVBUSVLD_MASK                (0x01UL << USB_OTGSTAT_AVBUSVLD_SHIFT)              /*!< USB0_OTGSTAT: AVBUSVLD Mask             */
#define USB_OTGSTAT_AVBUSVLD_SHIFT               0                                                   /*!< USB0_OTGSTAT: AVBUSVLD Position         */
#define USB_OTGSTAT_BSESSEND_MASK                (0x01UL << USB_OTGSTAT_BSESSEND_SHIFT)              /*!< USB0_OTGSTAT: BSESSEND Mask             */
#define USB_OTGSTAT_BSESSEND_SHIFT               2                                                   /*!< USB0_OTGSTAT: BSESSEND Position         */
#define USB_OTGSTAT_SESS_VLD_MASK                (0x01UL << USB_OTGSTAT_SESS_VLD_SHIFT)              /*!< USB0_OTGSTAT: SESS_VLD Mask             */
#define USB_OTGSTAT_SESS_VLD_SHIFT               3                                                   /*!< USB0_OTGSTAT: SESS_VLD Position         */
#define USB_OTGSTAT_LINESTATESTABLE_MASK         (0x01UL << USB_OTGSTAT_LINESTATESTABLE_SHIFT)       /*!< USB0_OTGSTAT: LINESTATESTABLE Mask      */
#define USB_OTGSTAT_LINESTATESTABLE_SHIFT        5                                                   /*!< USB0_OTGSTAT: LINESTATESTABLE Position  */
#define USB_OTGSTAT_ONEMSECEN_MASK               (0x01UL << USB_OTGSTAT_ONEMSECEN_SHIFT)             /*!< USB0_OTGSTAT: ONEMSECEN Mask            */
#define USB_OTGSTAT_ONEMSECEN_SHIFT              6                                                   /*!< USB0_OTGSTAT: ONEMSECEN Position        */
#define USB_OTGSTAT_ID_MASK                      (0x01UL << USB_OTGSTAT_ID_SHIFT)                    /*!< USB0_OTGSTAT: ID Mask                   */
#define USB_OTGSTAT_ID_SHIFT                     7                                                   /*!< USB0_OTGSTAT: ID Position               */

/* ------- USB0_OTGCTL                              ------ */
#define USB_OTGCTL_OTGEN_MASK                    (0x01UL << USB_OTGCTL_OTGEN_SHIFT)                  /*!< USB0_OTGCTL: OTGEN Mask                 */
#define USB_OTGCTL_OTGEN_SHIFT                   2                                                   /*!< USB0_OTGCTL: OTGEN Position             */
#define USB_OTGCTL_DMLOW_MASK                    (0x01UL << USB_OTGCTL_DMLOW_SHIFT)                  /*!< USB0_OTGCTL: DMLOW Mask                 */
#define USB_OTGCTL_DMLOW_SHIFT                   4                                                   /*!< USB0_OTGCTL: DMLOW Position             */
#define USB_OTGCTL_DPLOW_MASK                    (0x01UL << USB_OTGCTL_DPLOW_SHIFT)                  /*!< USB0_OTGCTL: DPLOW Mask                 */
#define USB_OTGCTL_DPLOW_SHIFT                   5                                                   /*!< USB0_OTGCTL: DPLOW Position             */
#define USB_OTGCTL_DPHIGH_MASK                   (0x01UL << USB_OTGCTL_DPHIGH_SHIFT)                 /*!< USB0_OTGCTL: DPHIGH Mask                */
#define USB_OTGCTL_DPHIGH_SHIFT                  7                                                   /*!< USB0_OTGCTL: DPHIGH Position            */

/* ------- USB0_ISTAT                               ------ */
#define USB_ISTAT_USBRST_MASK                    (0x01UL << USB_ISTAT_USBRST_SHIFT)                  /*!< USB0_ISTAT: USBRST Mask                 */
#define USB_ISTAT_USBRST_SHIFT                   0                                                   /*!< USB0_ISTAT: USBRST Position             */
#define USB_ISTAT_ERROR_MASK                     (0x01UL << USB_ISTAT_ERROR_SHIFT)                   /*!< USB0_ISTAT: ERROR Mask                  */
#define USB_ISTAT_ERROR_SHIFT                    1                                                   /*!< USB0_ISTAT: ERROR Position              */
#define USB_ISTAT_SOFTOK_MASK                    (0x01UL << USB_ISTAT_SOFTOK_SHIFT)                  /*!< USB0_ISTAT: SOFTOK Mask                 */
#define USB_ISTAT_SOFTOK_SHIFT                   2                                                   /*!< USB0_ISTAT: SOFTOK Position             */
#define USB_ISTAT_TOKDNE_MASK                    (0x01UL << USB_ISTAT_TOKDNE_SHIFT)                  /*!< USB0_ISTAT: TOKDNE Mask                 */
#define USB_ISTAT_TOKDNE_SHIFT                   3                                                   /*!< USB0_ISTAT: TOKDNE Position             */
#define USB_ISTAT_SLEEP_MASK                     (0x01UL << USB_ISTAT_SLEEP_SHIFT)                   /*!< USB0_ISTAT: SLEEP Mask                  */
#define USB_ISTAT_SLEEP_SHIFT                    4                                                   /*!< USB0_ISTAT: SLEEP Position              */
#define USB_ISTAT_RESUME_MASK                    (0x01UL << USB_ISTAT_RESUME_SHIFT)                  /*!< USB0_ISTAT: RESUME Mask                 */
#define USB_ISTAT_RESUME_SHIFT                   5                                                   /*!< USB0_ISTAT: RESUME Position             */
#define USB_ISTAT_ATTACH_MASK                    (0x01UL << USB_ISTAT_ATTACH_SHIFT)                  /*!< USB0_ISTAT: ATTACH Mask                 */
#define USB_ISTAT_ATTACH_SHIFT                   6                                                   /*!< USB0_ISTAT: ATTACH Position             */
#define USB_ISTAT_STALL_MASK                     (0x01UL << USB_ISTAT_STALL_SHIFT)                   /*!< USB0_ISTAT: STALL Mask                  */
#define USB_ISTAT_STALL_SHIFT                    7                                                   /*!< USB0_ISTAT: STALL Position              */

/* ------- USB0_INTEN                               ------ */
#define USB_INTEN_USBRSTEN_MASK                  (0x01UL << USB_INTEN_USBRSTEN_SHIFT)                /*!< USB0_INTEN: USBRSTEN Mask               */
#define USB_INTEN_USBRSTEN_SHIFT                 0                                                   /*!< USB0_INTEN: USBRSTEN Position           */
#define USB_INTEN_ERROREN_MASK                   (0x01UL << USB_INTEN_ERROREN_SHIFT)                 /*!< USB0_INTEN: ERROREN Mask                */
#define USB_INTEN_ERROREN_SHIFT                  1                                                   /*!< USB0_INTEN: ERROREN Position            */
#define USB_INTEN_SOFTOKEN_MASK                  (0x01UL << USB_INTEN_SOFTOKEN_SHIFT)                /*!< USB0_INTEN: SOFTOKEN Mask               */
#define USB_INTEN_SOFTOKEN_SHIFT                 2                                                   /*!< USB0_INTEN: SOFTOKEN Position           */
#define USB_INTEN_TOKDNEEN_MASK                  (0x01UL << USB_INTEN_TOKDNEEN_SHIFT)                /*!< USB0_INTEN: TOKDNEEN Mask               */
#define USB_INTEN_TOKDNEEN_SHIFT                 3                                                   /*!< USB0_INTEN: TOKDNEEN Position           */
#define USB_INTEN_SLEEPEN_MASK                   (0x01UL << USB_INTEN_SLEEPEN_SHIFT)                 /*!< USB0_INTEN: SLEEPEN Mask                */
#define USB_INTEN_SLEEPEN_SHIFT                  4                                                   /*!< USB0_INTEN: SLEEPEN Position            */
#define USB_INTEN_RESUMEEN_MASK                  (0x01UL << USB_INTEN_RESUMEEN_SHIFT)                /*!< USB0_INTEN: RESUMEEN Mask               */
#define USB_INTEN_RESUMEEN_SHIFT                 5                                                   /*!< USB0_INTEN: RESUMEEN Position           */
#define USB_INTEN_ATTACHEN_MASK                  (0x01UL << USB_INTEN_ATTACHEN_SHIFT)                /*!< USB0_INTEN: ATTACHEN Mask               */
#define USB_INTEN_ATTACHEN_SHIFT                 6                                                   /*!< USB0_INTEN: ATTACHEN Position           */
#define USB_INTEN_STALLEN_MASK                   (0x01UL << USB_INTEN_STALLEN_SHIFT)                 /*!< USB0_INTEN: STALLEN Mask                */
#define USB_INTEN_STALLEN_SHIFT                  7                                                   /*!< USB0_INTEN: STALLEN Position            */

/* ------- USB0_ERRSTAT                             ------ */
#define USB_ERRSTAT_PIDERR_MASK                  (0x01UL << USB_ERRSTAT_PIDERR_SHIFT)                /*!< USB0_ERRSTAT: PIDERR Mask               */
#define USB_ERRSTAT_PIDERR_SHIFT                 0                                                   /*!< USB0_ERRSTAT: PIDERR Position           */
#define USB_ERRSTAT_CRC5EOF_MASK                 (0x01UL << USB_ERRSTAT_CRC5EOF_SHIFT)               /*!< USB0_ERRSTAT: CRC5EOF Mask              */
#define USB_ERRSTAT_CRC5EOF_SHIFT                1                                                   /*!< USB0_ERRSTAT: CRC5EOF Position          */
#define USB_ERRSTAT_CRC16_MASK                   (0x01UL << USB_ERRSTAT_CRC16_SHIFT)                 /*!< USB0_ERRSTAT: CRC16 Mask                */
#define USB_ERRSTAT_CRC16_SHIFT                  2                                                   /*!< USB0_ERRSTAT: CRC16 Position            */
#define USB_ERRSTAT_DFN8_MASK                    (0x01UL << USB_ERRSTAT_DFN8_SHIFT)                  /*!< USB0_ERRSTAT: DFN8 Mask                 */
#define USB_ERRSTAT_DFN8_SHIFT                   3                                                   /*!< USB0_ERRSTAT: DFN8 Position             */
#define USB_ERRSTAT_BTOERR_MASK                  (0x01UL << USB_ERRSTAT_BTOERR_SHIFT)                /*!< USB0_ERRSTAT: BTOERR Mask               */
#define USB_ERRSTAT_BTOERR_SHIFT                 4                                                   /*!< USB0_ERRSTAT: BTOERR Position           */
#define USB_ERRSTAT_DMAERR_MASK                  (0x01UL << USB_ERRSTAT_DMAERR_SHIFT)                /*!< USB0_ERRSTAT: DMAERR Mask               */
#define USB_ERRSTAT_DMAERR_SHIFT                 5                                                   /*!< USB0_ERRSTAT: DMAERR Position           */
#define USB_ERRSTAT_BTSERR_MASK                  (0x01UL << USB_ERRSTAT_BTSERR_SHIFT)                /*!< USB0_ERRSTAT: BTSERR Mask               */
#define USB_ERRSTAT_BTSERR_SHIFT                 7                                                   /*!< USB0_ERRSTAT: BTSERR Position           */

/* ------- USB0_ERREN                               ------ */
#define USB_ERREN_PIDERREN_MASK                  (0x01UL << USB_ERREN_PIDERREN_SHIFT)                /*!< USB0_ERREN: PIDERREN Mask               */
#define USB_ERREN_PIDERREN_SHIFT                 0                                                   /*!< USB0_ERREN: PIDERREN Position           */
#define USB_ERREN_CRC5EOFEN_MASK                 (0x01UL << USB_ERREN_CRC5EOFEN_SHIFT)               /*!< USB0_ERREN: CRC5EOFEN Mask              */
#define USB_ERREN_CRC5EOFEN_SHIFT                1                                                   /*!< USB0_ERREN: CRC5EOFEN Position          */
#define USB_ERREN_CRC16EN_MASK                   (0x01UL << USB_ERREN_CRC16EN_SHIFT)                 /*!< USB0_ERREN: CRC16EN Mask                */
#define USB_ERREN_CRC16EN_SHIFT                  2                                                   /*!< USB0_ERREN: CRC16EN Position            */
#define USB_ERREN_DFN8EN_MASK                    (0x01UL << USB_ERREN_DFN8EN_SHIFT)                  /*!< USB0_ERREN: DFN8EN Mask                 */
#define USB_ERREN_DFN8EN_SHIFT                   3                                                   /*!< USB0_ERREN: DFN8EN Position             */
#define USB_ERREN_BTOERREN_MASK                  (0x01UL << USB_ERREN_BTOERREN_SHIFT)                /*!< USB0_ERREN: BTOERREN Mask               */
#define USB_ERREN_BTOERREN_SHIFT                 4                                                   /*!< USB0_ERREN: BTOERREN Position           */
#define USB_ERREN_DMAERREN_MASK                  (0x01UL << USB_ERREN_DMAERREN_SHIFT)                /*!< USB0_ERREN: DMAERREN Mask               */
#define USB_ERREN_DMAERREN_SHIFT                 5                                                   /*!< USB0_ERREN: DMAERREN Position           */
#define USB_ERREN_BTSERREN_MASK                  (0x01UL << USB_ERREN_BTSERREN_SHIFT)                /*!< USB0_ERREN: BTSERREN Mask               */
#define USB_ERREN_BTSERREN_SHIFT                 7                                                   /*!< USB0_ERREN: BTSERREN Position           */

/* ------- USB0_STAT                                ------ */
#define USB_STAT_ODD_MASK                        (0x01UL << USB_STAT_ODD_SHIFT)                      /*!< USB0_STAT: ODD Mask                     */
#define USB_STAT_ODD_SHIFT                       2                                                   /*!< USB0_STAT: ODD Position                 */
#define USB_STAT_TX_MASK                         (0x01UL << USB_STAT_TX_SHIFT)                       /*!< USB0_STAT: TX Mask                      */
#define USB_STAT_TX_SHIFT                        3                                                   /*!< USB0_STAT: TX Position                  */
#define USB_STAT_ENDP_MASK                       (0x0FUL << USB_STAT_ENDP_SHIFT)                     /*!< USB0_STAT: ENDP Mask                    */
#define USB_STAT_ENDP_SHIFT                      4                                                   /*!< USB0_STAT: ENDP Position                */
#define USB_STAT_ENDP(x)                         (((x)<<USB_STAT_ENDP_SHIFT)&USB_STAT_ENDP_MASK)     /*!< USB0_STAT                               */

/* ------- USB0_CTL                                 ------ */
#define USB_CTL_USBENSOFEN_MASK                  (0x01UL << USB_CTL_USBENSOFEN_SHIFT)                /*!< USB0_CTL: USBENSOFEN Mask               */
#define USB_CTL_USBENSOFEN_SHIFT                 0                                                   /*!< USB0_CTL: USBENSOFEN Position           */
#define USB_CTL_ODDRST_MASK                      (0x01UL << USB_CTL_ODDRST_SHIFT)                    /*!< USB0_CTL: ODDRST Mask                   */
#define USB_CTL_ODDRST_SHIFT                     1                                                   /*!< USB0_CTL: ODDRST Position               */
#define USB_CTL_RESUME_MASK                      (0x01UL << USB_CTL_RESUME_SHIFT)                    /*!< USB0_CTL: RESUME Mask                   */
#define USB_CTL_RESUME_SHIFT                     2                                                   /*!< USB0_CTL: RESUME Position               */
#define USB_CTL_HOSTMODEEN_MASK                  (0x01UL << USB_CTL_HOSTMODEEN_SHIFT)                /*!< USB0_CTL: HOSTMODEEN Mask               */
#define USB_CTL_HOSTMODEEN_SHIFT                 3                                                   /*!< USB0_CTL: HOSTMODEEN Position           */
#define USB_CTL_RESET_MASK                       (0x01UL << USB_CTL_RESET_SHIFT)                     /*!< USB0_CTL: RESET Mask                    */
#define USB_CTL_RESET_SHIFT                      4                                                   /*!< USB0_CTL: RESET Position                */
#define USB_CTL_TXSUSPENDTOKENBUSY_MASK          (0x01UL << USB_CTL_TXSUSPENDTOKENBUSY_SHIFT)        /*!< USB0_CTL: TXSUSPENDTOKENBUSY Mask       */
#define USB_CTL_TXSUSPENDTOKENBUSY_SHIFT         5                                                   /*!< USB0_CTL: TXSUSPENDTOKENBUSY Position   */
#define USB_CTL_SE0_MASK                         (0x01UL << USB_CTL_SE0_SHIFT)                       /*!< USB0_CTL: SE0 Mask                      */
#define USB_CTL_SE0_SHIFT                        6                                                   /*!< USB0_CTL: SE0 Position                  */
#define USB_CTL_JSTATE_MASK                      (0x01UL << USB_CTL_JSTATE_SHIFT)                    /*!< USB0_CTL: JSTATE Mask                   */
#define USB_CTL_JSTATE_SHIFT                     7                                                   /*!< USB0_CTL: JSTATE Position               */

/* ------- USB0_ADDR                                ------ */
#define USB_ADDR_ADDR_MASK                       (0x7FUL << USB_ADDR_ADDR_SHIFT)                     /*!< USB0_ADDR: ADDR Mask                    */
#define USB_ADDR_ADDR_SHIFT                      0                                                   /*!< USB0_ADDR: ADDR Position                */
#define USB_ADDR_ADDR(x)                         (((x)<<USB_ADDR_ADDR_SHIFT)&USB_ADDR_ADDR_MASK)     /*!< USB0_ADDR                               */
#define USB_ADDR_LSEN_MASK                       (0x01UL << USB_ADDR_LSEN_SHIFT)                     /*!< USB0_ADDR: LSEN Mask                    */
#define USB_ADDR_LSEN_SHIFT                      7                                                   /*!< USB0_ADDR: LSEN Position                */

/* ------- USB0_BDTPAGE1                            ------ */
#define USB_BDTPAGE1_BDTBA_MASK                  (0x7FUL << USB_BDTPAGE1_BDTBA_SHIFT)                /*!< USB0_BDTPAGE1: BDTBA Mask               */
#define USB_BDTPAGE1_BDTBA_SHIFT                 1                                                   /*!< USB0_BDTPAGE1: BDTBA Position           */
#define USB_BDTPAGE1_BDTBA(x)                    (((x)<<USB_BDTPAGE1_BDTBA_SHIFT)&USB_BDTPAGE1_BDTBA_MASK) /*!< USB0_BDTPAGE1                           */

/* ------- USB0_FRMNUML                             ------ */
#define USB_FRMNUML_FRM_MASK                     (0xFFUL << USB_FRMNUML_FRM_SHIFT)                   /*!< USB0_FRMNUML: FRM Mask                  */
#define USB_FRMNUML_FRM_SHIFT                    0                                                   /*!< USB0_FRMNUML: FRM Position              */
#define USB_FRMNUML_FRM(x)                       (((x)<<USB_FRMNUML_FRM_SHIFT)&USB_FRMNUML_FRM_MASK) /*!< USB0_FRMNUML                            */

/* ------- USB0_FRMNUMH                             ------ */
#define USB_FRMNUMH_FRM_MASK                     (0x07UL << USB_FRMNUMH_FRM_SHIFT)                   /*!< USB0_FRMNUMH: FRM Mask                  */
#define USB_FRMNUMH_FRM_SHIFT                    0                                                   /*!< USB0_FRMNUMH: FRM Position              */
#define USB_FRMNUMH_FRM(x)                       (((x)<<USB_FRMNUMH_FRM_SHIFT)&USB_FRMNUMH_FRM_MASK) /*!< USB0_FRMNUMH                            */

/* ------- USB0_TOKEN                               ------ */
#define USB_TOKEN_TOKENENDPT_MASK                (0x0FUL << USB_TOKEN_TOKENENDPT_SHIFT)              /*!< USB0_TOKEN: TOKENENDPT Mask             */
#define USB_TOKEN_TOKENENDPT_SHIFT               0                                                   /*!< USB0_TOKEN: TOKENENDPT Position         */
#define USB_TOKEN_TOKENENDPT(x)                  (((x)<<USB_TOKEN_TOKENENDPT_SHIFT)&USB_TOKEN_TOKENENDPT_MASK) /*!< USB0_TOKEN                              */
#define USB_TOKEN_TOKENPID_MASK                  (0x0FUL << USB_TOKEN_TOKENPID_SHIFT)                /*!< USB0_TOKEN: TOKENPID Mask               */
#define USB_TOKEN_TOKENPID_SHIFT                 4                                                   /*!< USB0_TOKEN: TOKENPID Position           */
#define USB_TOKEN_TOKENPID(x)                    (((x)<<USB_TOKEN_TOKENPID_SHIFT)&USB_TOKEN_TOKENPID_MASK) /*!< USB0_TOKEN                              */

/* ------- USB0_SOFTHLD                             ------ */
#define USB_SOFTHLD_CNT_MASK                     (0xFFUL << USB_SOFTHLD_CNT_SHIFT)                   /*!< USB0_SOFTHLD: CNT Mask                  */
#define USB_SOFTHLD_CNT_SHIFT                    0                                                   /*!< USB0_SOFTHLD: CNT Position              */
#define USB_SOFTHLD_CNT(x)                       (((x)<<USB_SOFTHLD_CNT_SHIFT)&USB_SOFTHLD_CNT_MASK) /*!< USB0_SOFTHLD                            */

/* ------- USB0_BDTPAGE2                            ------ */
#define USB_BDTPAGE2_BDTBA_MASK                  (0xFFUL << USB_BDTPAGE2_BDTBA_SHIFT)                /*!< USB0_BDTPAGE2: BDTBA Mask               */
#define USB_BDTPAGE2_BDTBA_SHIFT                 0                                                   /*!< USB0_BDTPAGE2: BDTBA Position           */
#define USB_BDTPAGE2_BDTBA(x)                    (((x)<<USB_BDTPAGE2_BDTBA_SHIFT)&USB_BDTPAGE2_BDTBA_MASK) /*!< USB0_BDTPAGE2                           */

/* ------- USB0_BDTPAGE3                            ------ */
#define USB_BDTPAGE3_BDTBA_MASK                  (0xFFUL << USB_BDTPAGE3_BDTBA_SHIFT)                /*!< USB0_BDTPAGE3: BDTBA Mask               */
#define USB_BDTPAGE3_BDTBA_SHIFT                 0                                                   /*!< USB0_BDTPAGE3: BDTBA Position           */
#define USB_BDTPAGE3_BDTBA(x)                    (((x)<<USB_BDTPAGE3_BDTBA_SHIFT)&USB_BDTPAGE3_BDTBA_MASK) /*!< USB0_BDTPAGE3                           */

/* ------- USB0_ENDPT                               ------ */
#define USB_ENDPT_EPHSHK_MASK                    (0x01UL << USB_ENDPT_EPHSHK_SHIFT)                  /*!< USB0_ENDPT: EPHSHK Mask                 */
#define USB_ENDPT_EPHSHK_SHIFT                   0                                                   /*!< USB0_ENDPT: EPHSHK Position             */
#define USB_ENDPT_EPSTALL_MASK                   (0x01UL << USB_ENDPT_EPSTALL_SHIFT)                 /*!< USB0_ENDPT: EPSTALL Mask                */
#define USB_ENDPT_EPSTALL_SHIFT                  1                                                   /*!< USB0_ENDPT: EPSTALL Position            */
#define USB_ENDPT_EPTXEN_MASK                    (0x01UL << USB_ENDPT_EPTXEN_SHIFT)                  /*!< USB0_ENDPT: EPTXEN Mask                 */
#define USB_ENDPT_EPTXEN_SHIFT                   2                                                   /*!< USB0_ENDPT: EPTXEN Position             */
#define USB_ENDPT_EPRXEN_MASK                    (0x01UL << USB_ENDPT_EPRXEN_SHIFT)                  /*!< USB0_ENDPT: EPRXEN Mask                 */
#define USB_ENDPT_EPRXEN_SHIFT                   3                                                   /*!< USB0_ENDPT: EPRXEN Position             */
#define USB_ENDPT_EPCTLDIS_MASK                  (0x01UL << USB_ENDPT_EPCTLDIS_SHIFT)                /*!< USB0_ENDPT: EPCTLDIS Mask               */
#define USB_ENDPT_EPCTLDIS_SHIFT                 4                                                   /*!< USB0_ENDPT: EPCTLDIS Position           */
#define USB_ENDPT_RETRYDIS_MASK                  (0x01UL << USB_ENDPT_RETRYDIS_SHIFT)                /*!< USB0_ENDPT: RETRYDIS Mask               */
#define USB_ENDPT_RETRYDIS_SHIFT                 6                                                   /*!< USB0_ENDPT: RETRYDIS Position           */
#define USB_ENDPT_HOSTWOHUB_MASK                 (0x01UL << USB_ENDPT_HOSTWOHUB_SHIFT)               /*!< USB0_ENDPT: HOSTWOHUB Mask              */
#define USB_ENDPT_HOSTWOHUB_SHIFT                7                                                   /*!< USB0_ENDPT: HOSTWOHUB Position          */

/* ------- USB0_USBCTRL                             ------ */
#define USB_USBCTRL_PDE_MASK                     (0x01UL << USB_USBCTRL_PDE_SHIFT)                   /*!< USB0_USBCTRL: PDE Mask                  */
#define USB_USBCTRL_PDE_SHIFT                    6                                                   /*!< USB0_USBCTRL: PDE Position              */
#define USB_USBCTRL_SUSP_MASK                    (0x01UL << USB_USBCTRL_SUSP_SHIFT)                  /*!< USB0_USBCTRL: SUSP Mask                 */
#define USB_USBCTRL_SUSP_SHIFT                   7                                                   /*!< USB0_USBCTRL: SUSP Position             */

/* ------- USB0_OBSERVE                             ------ */
#define USB_OBSERVE_DMPD_MASK                    (0x01UL << USB_OBSERVE_DMPD_SHIFT)                  /*!< USB0_OBSERVE: DMPD Mask                 */
#define USB_OBSERVE_DMPD_SHIFT                   4                                                   /*!< USB0_OBSERVE: DMPD Position             */
#define USB_OBSERVE_DPPD_MASK                    (0x01UL << USB_OBSERVE_DPPD_SHIFT)                  /*!< USB0_OBSERVE: DPPD Mask                 */
#define USB_OBSERVE_DPPD_SHIFT                   6                                                   /*!< USB0_OBSERVE: DPPD Position             */
#define USB_OBSERVE_DPPU_MASK                    (0x01UL << USB_OBSERVE_DPPU_SHIFT)                  /*!< USB0_OBSERVE: DPPU Mask                 */
#define USB_OBSERVE_DPPU_SHIFT                   7                                                   /*!< USB0_OBSERVE: DPPU Position             */

/* ------- USB0_CONTROL                             ------ */
#define USB_CONTROL_DPPULLUPNONOTG_MASK          (0x01UL << USB_CONTROL_DPPULLUPNONOTG_SHIFT)        /*!< USB0_CONTROL: DPPULLUPNONOTG Mask       */
#define USB_CONTROL_DPPULLUPNONOTG_SHIFT         4                                                   /*!< USB0_CONTROL: DPPULLUPNONOTG Position   */

/* ------- USB0_USBTRC0                             ------ */
#define USB_USBTRC0_USB_RESUME_INT_MASK          (0x01UL << USB_USBTRC0_USB_RESUME_INT_SHIFT)        /*!< USB0_USBTRC0: USB_RESUME_INT Mask       */
#define USB_USBTRC0_USB_RESUME_INT_SHIFT         0                                                   /*!< USB0_USBTRC0: USB_RESUME_INT Position   */
#define USB_USBTRC0_SYNC_DET_MASK                (0x01UL << USB_USBTRC0_SYNC_DET_SHIFT)              /*!< USB0_USBTRC0: SYNC_DET Mask             */
#define USB_USBTRC0_SYNC_DET_SHIFT               1                                                   /*!< USB0_USBTRC0: SYNC_DET Position         */
#define USB_USBTRC0_USBRESMEN_MASK               (0x01UL << USB_USBTRC0_USBRESMEN_SHIFT)             /*!< USB0_USBTRC0: USBRESMEN Mask            */
#define USB_USBTRC0_USBRESMEN_SHIFT              5                                                   /*!< USB0_USBTRC0: USBRESMEN Position        */
#define USB_USBTRC0_USBRESET_MASK                (0x01UL << USB_USBTRC0_USBRESET_SHIFT)              /*!< USB0_USBTRC0: USBRESET Mask             */
#define USB_USBTRC0_USBRESET_SHIFT               7                                                   /*!< USB0_USBTRC0: USBRESET Position         */

/* ------- USB0_USBFRMADJUST                        ------ */
#define USB_USBFRMADJUST_ADJ_MASK                (0xFFUL << USB_USBFRMADJUST_ADJ_SHIFT)              /*!< USB0_USBFRMADJUST: ADJ Mask             */
#define USB_USBFRMADJUST_ADJ_SHIFT               0                                                   /*!< USB0_USBFRMADJUST: ADJ Position         */
#define USB_USBFRMADJUST_ADJ(x)                  (((x)<<USB_USBFRMADJUST_ADJ_SHIFT)&USB_USBFRMADJUST_ADJ_MASK) /*!< USB0_USBFRMADJUST                       */

/* -------------------------------------------------------------------------------- */
/* -----------     'USB0' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define USB0_PERID                     (USB0->PERID)
#define USB0_IDCOMP                    (USB0->IDCOMP)
#define USB0_REV                       (USB0->REV)
#define USB0_ADDINFO                   (USB0->ADDINFO)
#define USB0_OTGISTAT                  (USB0->OTGISTAT)
#define USB0_OTGICR                    (USB0->OTGICR)
#define USB0_OTGSTAT                   (USB0->OTGSTAT)
#define USB0_OTGCTL                    (USB0->OTGCTL)
#define USB0_ISTAT                     (USB0->ISTAT)
#define USB0_INTEN                     (USB0->INTEN)
#define USB0_ERRSTAT                   (USB0->ERRSTAT)
#define USB0_ERREN                     (USB0->ERREN)
#define USB0_STAT                      (USB0->STAT)
#define USB0_CTL                       (USB0->CTL)
#define USB0_ADDR                      (USB0->ADDR)
#define USB0_BDTPAGE1                  (USB0->BDTPAGE1)
#define USB0_FRMNUML                   (USB0->FRMNUML)
#define USB0_FRMNUMH                   (USB0->FRMNUMH)
#define USB0_TOKEN                     (USB0->TOKEN)
#define USB0_SOFTHLD                   (USB0->SOFTHLD)
#define USB0_BDTPAGE2                  (USB0->BDTPAGE2)
#define USB0_BDTPAGE3                  (USB0->BDTPAGE3)
#define USB0_ENDPT0                    (USB0->ENDPOINT[0].ENDPT)
#define USB0_ENDPT1                    (USB0->ENDPOINT[1].ENDPT)
#define USB0_ENDPT2                    (USB0->ENDPOINT[2].ENDPT)
#define USB0_ENDPT3                    (USB0->ENDPOINT[3].ENDPT)
#define USB0_ENDPT4                    (USB0->ENDPOINT[4].ENDPT)
#define USB0_ENDPT5                    (USB0->ENDPOINT[5].ENDPT)
#define USB0_ENDPT6                    (USB0->ENDPOINT[6].ENDPT)
#define USB0_ENDPT7                    (USB0->ENDPOINT[7].ENDPT)
#define USB0_ENDPT8                    (USB0->ENDPOINT[8].ENDPT)
#define USB0_ENDPT9                    (USB0->ENDPOINT[9].ENDPT)
#define USB0_ENDPT10                   (USB0->ENDPOINT[10].ENDPT)
#define USB0_ENDPT11                   (USB0->ENDPOINT[11].ENDPT)
#define USB0_ENDPT12                   (USB0->ENDPOINT[12].ENDPT)
#define USB0_ENDPT13                   (USB0->ENDPOINT[13].ENDPT)
#define USB0_ENDPT14                   (USB0->ENDPOINT[14].ENDPT)
#define USB0_ENDPT15                   (USB0->ENDPOINT[15].ENDPT)
#define USB0_USBCTRL                   (USB0->USBCTRL)
#define USB0_OBSERVE                   (USB0->OBSERVE)
#define USB0_CONTROL                   (USB0->CONTROL)
#define USB0_USBTRC0                   (USB0->USBTRC0)
#define USB0_USBFRMADJUST              (USB0->USBFRMADJUST)
/* --------------------  End of section using anonymous unions  ------------------- */
#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
  /* leave anonymous unions enabled */
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler type
#endif

/* ================================================================================ */
/* ================              Peripheral memory map             ================ */
/* ================================================================================ */

#define ADC0_BASE_PTR                  0x4003B000UL
#define BP_BASE_PTR                    0xE0002000UL
#define CMP0_BASE_PTR                  0x40073000UL
#define DAC0_BASE_PTR                  0x4003F000UL
#define DMA_BASE_PTR                   0x40008000UL
#define DMAMUX_BASE_PTR                0x40021000UL
#define FGPIOA_BASE_PTR                0xF80FF000UL
#define FGPIOB_BASE_PTR                0xF80FF040UL
#define FGPIOC_BASE_PTR                0xF80FF080UL
#define FGPIOD_BASE_PTR                0xF80FF0C0UL
#define FGPIOE_BASE_PTR                0xF80FF100UL
#define FTFA_BASE_PTR                  0x40020000UL
#define GPIOA_BASE_PTR                 0x400FF000UL
#define GPIOB_BASE_PTR                 0x400FF040UL
#define GPIOC_BASE_PTR                 0x400FF080UL
#define GPIOD_BASE_PTR                 0x400FF0C0UL
#define GPIOE_BASE_PTR                 0x400FF100UL
#define I2C0_BASE_PTR                  0x40066000UL
#define I2C1_BASE_PTR                  0x40067000UL
#define I2S0_BASE_PTR                  0x4002F000UL
#define LCD_BASE_PTR                   0x40053000UL
#define LLWU_BASE_PTR                  0x4007C000UL
#define LPTMR0_BASE_PTR                0x40040000UL
#define LPUART0_BASE_PTR               0x40054000UL
#define LPUART1_BASE_PTR               0x40055000UL
#define MCG_BASE_PTR                   0x40064000UL
#define MCM_BASE_PTR                   0xF0003000UL
#define MTB_BASE_PTR                   0xF0000000UL
#define MTBDWT_BASE_PTR                0xF0001000UL
#define NV_BASE_PTR                    0x00000400UL
#define OSC0_BASE_PTR                  0x40065000UL
#define PIT_BASE_PTR                   0x40037000UL
#define PMC_BASE_PTR                   0x4007D000UL
#define PORTA_BASE_PTR                 0x40049000UL
#define PORTB_BASE_PTR                 0x4004A000UL
#define PORTC_BASE_PTR                 0x4004B000UL
#define PORTD_BASE_PTR                 0x4004C000UL
#define PORTE_BASE_PTR                 0x4004D000UL
#define RCM_BASE_PTR                   0x4007F000UL
#define ROM_BASE_PTR                   0xF0002000UL
#define RTC_BASE_PTR                   0x4003D000UL
#define SIM_BASE_PTR                   0x40047000UL
#define SMC_BASE_PTR                   0x4007E000UL
#define SPI0_BASE_PTR                  0x40076000UL
#define SPI1_BASE_PTR                  0x40077000UL
#define SYST_BASE_PTR                  0xE000E010UL
#define TPM0_BASE_PTR                  0x40038000UL
#define TPM1_BASE_PTR                  0x40039000UL
#define TPM2_BASE_PTR                  0x4003A000UL
#define UART2_BASE_PTR                 0x4006C000UL
#define USB0_BASE_PTR                  0x40072000UL

/* ================================================================================ */
/* ================             Peripheral declarations            ================ */
/* ================================================================================ */

#define ADC0                           ((volatile ADC0_Type   *) ADC0_BASE_PTR)
#define BP                             ((volatile BP_Type     *) BP_BASE_PTR)
#define CMP0                           ((volatile CMP0_Type   *) CMP0_BASE_PTR)
#define DAC0                           ((volatile DAC0_Type   *) DAC0_BASE_PTR)
#define DMA                            ((volatile DMA_Type    *) DMA_BASE_PTR)
#define DMAMUX                         ((volatile DMAMUX_Type *) DMAMUX_BASE_PTR)
#define FGPIOA                         ((volatile FGPIOA_Type *) FGPIOA_BASE_PTR)
#define FGPIOB                         ((volatile FGPIOB_Type *) FGPIOB_BASE_PTR)
#define FGPIOC                         ((volatile FGPIOC_Type *) FGPIOC_BASE_PTR)
#define FGPIOD                         ((volatile FGPIOD_Type *) FGPIOD_BASE_PTR)
#define FGPIOE                         ((volatile FGPIOE_Type *) FGPIOE_BASE_PTR)
#define FTFA                           ((volatile FTFA_Type   *) FTFA_BASE_PTR)
#define GPIOA                          ((volatile GPIOA_Type  *) GPIOA_BASE_PTR)
#define GPIOB                          ((volatile GPIOB_Type  *) GPIOB_BASE_PTR)
#define GPIOC                          ((volatile GPIOC_Type  *) GPIOC_BASE_PTR)
#define GPIOD                          ((volatile GPIOD_Type  *) GPIOD_BASE_PTR)
#define GPIOE                          ((volatile GPIOE_Type  *) GPIOE_BASE_PTR)
#define I2C0                           ((volatile I2C0_Type   *) I2C0_BASE_PTR)
#define I2C1                           ((volatile I2C1_Type   *) I2C1_BASE_PTR)
#define I2S0                           ((volatile I2S0_Type   *) I2S0_BASE_PTR)
#define LCD                            ((volatile LCD_Type    *) LCD_BASE_PTR)
#define LLWU                           ((volatile LLWU_Type   *) LLWU_BASE_PTR)
#define LPTMR0                         ((volatile LPTMR0_Type *) LPTMR0_BASE_PTR)
#define LPUART0                        ((volatile LPUART0_Type *) LPUART0_BASE_PTR)
#define LPUART1                        ((volatile LPUART1_Type *) LPUART1_BASE_PTR)
#define MCG                            ((volatile MCG_Type    *) MCG_BASE_PTR)
#define MCM                            ((volatile MCM_Type    *) MCM_BASE_PTR)
#define MTB                            ((volatile MTB_Type    *) MTB_BASE_PTR)
#define MTBDWT                         ((volatile MTBDWT_Type *) MTBDWT_BASE_PTR)
#define NV                             ((volatile NV_Type     *) NV_BASE_PTR)
#define OSC0                           ((volatile OSC0_Type   *) OSC0_BASE_PTR)
#define PIT                            ((volatile PIT_Type    *) PIT_BASE_PTR)
#define PMC                            ((volatile PMC_Type    *) PMC_BASE_PTR)
#define PORTA                          ((volatile PORTA_Type  *) PORTA_BASE_PTR)
#define PORTB                          ((volatile PORTB_Type  *) PORTB_BASE_PTR)
#define PORTC                          ((volatile PORTC_Type  *) PORTC_BASE_PTR)
#define PORTD                          ((volatile PORTD_Type  *) PORTD_BASE_PTR)
#define PORTE                          ((volatile PORTE_Type  *) PORTE_BASE_PTR)
#define RCM                            ((volatile RCM_Type    *) RCM_BASE_PTR)
#define ROM                            ((volatile ROM_Type    *) ROM_BASE_PTR)
#define RTC                            ((volatile RTC_Type    *) RTC_BASE_PTR)
#define SIM                            ((volatile SIM_Type    *) SIM_BASE_PTR)
#define SMC                            ((volatile SMC_Type    *) SMC_BASE_PTR)
#define SPI0                           ((volatile SPI0_Type   *) SPI0_BASE_PTR)
#define SPI1                           ((volatile SPI1_Type   *) SPI1_BASE_PTR)
#define SYST                           ((volatile SYST_Type   *) SYST_BASE_PTR)
#define TPM0                           ((volatile TPM0_Type   *) TPM0_BASE_PTR)
#define TPM1                           ((volatile TPM1_Type   *) TPM1_BASE_PTR)
#define TPM2                           ((volatile TPM2_Type   *) TPM2_BASE_PTR)
#define UART2                          ((volatile UART2_Type  *) UART2_BASE_PTR)
#define USB0                           ((volatile USB0_Type   *) USB0_BASE_PTR)

#ifdef __cplusplus
}
#endif


#endif  /* MCU_MKL43Z4 */

