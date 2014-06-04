/****************************************************************************************************//**
 * @file     MKV10Z7.h
 *
 * @brief    CMSIS Cortex-M Peripheral Access Layer Header File for MKV10Z7.
 *           Equivalent: MKV10Z32M7
 *
 * @version  V1.6
 * @date     2014/06
 *
 *******************************************************************************************************/

#ifndef MCU_MKV10Z7
#define MCU_MKV10Z7

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------  Interrupt Number Definition  ------------------------ */

typedef enum {
/* --------------------  Cortex-M Processor Exceptions Numbers  ------------------- */
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
/* ----------------------   MKV10Z7 VectorTable                      ---------------------- */
  DMA0_IRQn                     =   0,   /*!<  16 DMA0 Transfer complete                                                           */
  DMA1_IRQn                     =   1,   /*!<  17 DMA1 Transfer complete                                                           */
  DMA2_IRQn                     =   2,   /*!<  18 DMA2 Transfer complete                                                           */
  DMA3_IRQn                     =   3,   /*!<  19 DMA3 Transfer complete                                                           */
  DMA_Error_IRQn                =   4,   /*!<  20 DMA3 error                                                                       */
  FTFA_IRQn                     =   5,   /*!<  21 FTFA Command complete or error                                                   */
  PMC_IRQn                      =   6,   /*!<  22 PMC Low-voltage detect, low-voltage warning                                      */
  LLWU_IRQn                     =   7,   /*!<  23 Low Leakage Wakeup                                                               */
  I2C0_IRQn                     =   8,   /*!<  24 I2C Interface 0                                                                  */
  SPI0_IRQn                     =  10,   /*!<  26 Serial Peripheral Interface 0                                                    */
  UART0_IRQn                    =  12,   /*!<  28 UART0 Status and error                                                           */
  UART1_IRQn                    =  13,   /*!<  29 UART1 Status and error                                                           */
  ADC0_IRQn                     =  15,   /*!<  31 Analogue to Digital Converter 0                                                  */
  ADC1_IRQn                     =  16,   /*!<  32 Analogue to Digital Converter 1                                                  */
  FTM0_IRQn                     =  17,   /*!<  33 Timer/PWM Module 0                                                               */
  FTM1_IRQn                     =  18,   /*!<  34 Timer/PWM Module 1                                                               */
  FTM2_IRQn                     =  19,   /*!<  35 Timer/PWM Module 2                                                               */
  CMP0_IRQn                     =  20,   /*!<  36                                                                                  */
  CMP1_IRQn                     =  21,   /*!<  37                                                                                  */
  WDOG_EWM_IRQn                 =  23,   /*!<  39                                                                                  */
  DAC0_IRQn                     =  25,   /*!<  41 Digital to Analogue Converter                                                    */
  MCG_IRQn                      =  27,   /*!<  43 Clock interrupt                                                                  */
  LPTMR0_IRQn                   =  28,   /*!<  44 Low Power Timer                                                                  */
  PDB0_IRQn                     =  29,   /*!<  45 Programmable Delay Block 0                                                       */
  PORTA_IRQn                    =  30,   /*!<  46 Port A                                                                           */
  PORTBCDE_IRQn                 =  31,   /*!<  47 Port B,C,D & Port E                                                              */
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
extern void DMA_Error_IRQHandler(void);
extern void FTFA_IRQHandler(void);
extern void PMC_IRQHandler(void);
extern void LLWU_IRQHandler(void);
extern void I2C0_IRQHandler(void);
extern void SPI0_IRQHandler(void);
extern void UART0_IRQHandler(void);
extern void UART1_IRQHandler(void);
extern void ADC0_IRQHandler(void);
extern void ADC1_IRQHandler(void);
extern void FTM0_IRQHandler(void);
extern void FTM1_IRQHandler(void);
extern void FTM2_IRQHandler(void);
extern void CMP0_IRQHandler(void);
extern void CMP1_IRQHandler(void);
extern void WDOG_EWM_IRQHandler(void);
extern void DAC0_IRQHandler(void);
extern void MCG_IRQHandler(void);
extern void LPTMR0_IRQHandler(void);
extern void PDB0_IRQHandler(void);
extern void PORTA_IRQHandler(void);
extern void PORTBCDE_IRQHandler(void);

/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* ----------------Configuration of the cm4 Processor and Core Peripherals---------------- */
#define __CM3_REV                0x0100
#define __MPU_PRESENT            0
#define __NVIC_PRIO_BITS         0
#define __Vendor_SysTickConfig   0
#define __FPU_PRESENT            0

#include <core_cm3.h>   /*!< Cortex-M4 processor and core peripherals                              */

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
   __IO uint32_t  SC1A;                         /*!< 0000: Status and Control Registers 1                               */
   __IO uint32_t  SC1B;                         /*!< 0004: Status and Control Registers 1                               */
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
   __IO uint32_t  CLPD;                         /*!< 0034: Plus-Side General Calibration Value Register                 */
   __IO uint32_t  CLPS;                         /*!< 0038: Plus-Side General Calibration Value Register                 */
   __IO uint32_t  CLP4;                         /*!< 003C: Plus-Side General Calibration Value Register                 */
   __IO uint32_t  CLP3;                         /*!< 0040: Plus-Side General Calibration Value Register                 */
   __IO uint32_t  CLP2;                         /*!< 0044: Plus-Side General Calibration Value Register                 */
   __IO uint32_t  CLP1;                         /*!< 0048: Plus-Side General Calibration Value Register                 */
   __IO uint32_t  CLP0;                         /*!< 004C: Plus-Side General Calibration Value Register                 */
   __I  uint32_t  RESERVED0;                    /*!< 0050:                                                              */
   __IO uint32_t  CLMD;                         /*!< 0054: Minus-Side General Calibration Value Register                */
   __IO uint32_t  CLMS;                         /*!< 0058: Minus-Side General Calibration Value Register                */
   __IO uint32_t  CLM4;                         /*!< 005C: Minus-Side General Calibration Value Register                */
   __IO uint32_t  CLM3;                         /*!< 0060: Minus-Side General Calibration Value Register                */
   __IO uint32_t  CLM2;                         /*!< 0064: Minus-Side General Calibration Value Register                */
   __IO uint32_t  CLM1;                         /*!< 0068: Minus-Side General Calibration Value Register                */
   __IO uint32_t  CLM0;                         /*!< 006C: Minus-Side General Calibration Value Register                */
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
/* ================           ADC1 (derived from ADC0)             ================ */
/* ================================================================================ */

/**
 * @brief Analog-to-Digital Converter
 */
typedef ADC0_Type ADC1_Type;  /*!< ADC1 Structure                                              */


/* -------------------------------------------------------------------------------- */
/* -----------     'ADC1' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define ADC1_SC1A                      (ADC1->SC1A)
#define ADC1_SC1B                      (ADC1->SC1B)
#define ADC1_CFG1                      (ADC1->CFG1)
#define ADC1_CFG2                      (ADC1->CFG2)
#define ADC1_RA                        (ADC1->RA)
#define ADC1_RB                        (ADC1->RB)
#define ADC1_CV1                       (ADC1->CV1)
#define ADC1_CV2                       (ADC1->CV2)
#define ADC1_SC2                       (ADC1->SC2)
#define ADC1_SC3                       (ADC1->SC3)
#define ADC1_OFS                       (ADC1->OFS)
#define ADC1_PG                        (ADC1->PG)
#define ADC1_MG                        (ADC1->MG)
#define ADC1_CLPD                      (ADC1->CLPD)
#define ADC1_CLPS                      (ADC1->CLPS)
#define ADC1_CLP4                      (ADC1->CLP4)
#define ADC1_CLP3                      (ADC1->CLP3)
#define ADC1_CLP2                      (ADC1->CLP2)
#define ADC1_CLP1                      (ADC1->CLP1)
#define ADC1_CLP0                      (ADC1->CLP0)
#define ADC1_CLMD                      (ADC1->CLMD)
#define ADC1_CLMS                      (ADC1->CLMS)
#define ADC1_CLM4                      (ADC1->CLM4)
#define ADC1_CLM3                      (ADC1->CLM3)
#define ADC1_CLM2                      (ADC1->CLM2)
#define ADC1_CLM1                      (ADC1->CLM1)
#define ADC1_CLM0                      (ADC1->CLM0)

/* ================================================================================ */
/* ================           CMP0 (file:CMP0_MKV)                 ================ */
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
/* ================           CMP1 (derived from CMP0)             ================ */
/* ================================================================================ */

/**
 * @brief Comparator, Voltage Ref, D-to-A Converter and Analog Mux
 */
typedef CMP0_Type CMP1_Type;  /*!< CMP1 Structure                                              */


/* -------------------------------------------------------------------------------- */
/* -----------     'CMP1' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define CMP1_CR0                       (CMP1->CR0)
#define CMP1_CR1                       (CMP1->CR1)
#define CMP1_FPR                       (CMP1->FPR)
#define CMP1_SCR                       (CMP1->SCR)
#define CMP1_DACCR                     (CMP1->DACCR)
#define CMP1_MUXCR                     (CMP1->MUXCR)

/* ================================================================================ */
/* ================           CRC (file:CRC_0)                     ================ */
/* ================================================================================ */

/**
 * @brief Cyclic Redundancy Check
 */
typedef struct {                                /*!<       CRC Structure                                                */
   union {                                      /*!< 0000: (size=0004)                                                  */
      __IO uint32_t  DATA;                      /*!< 0000: Data register                                                */
      struct {                                  /*!< 0000: (size=0004)                                                  */
         union {                                /*!< 0000: (size=0002)                                                  */
            __IO uint16_t  DATAL;               /*!< 0000: DATAL register                                               */
            struct {                            /*!< 0000: (size=0002)                                                  */
               __IO uint8_t   DATALL;           /*!< 0000: DATALL register                                              */
               __IO uint8_t   DATALU;           /*!< 0001: DATALU register                                              */
            };
         };
         union {                                /*!< 0000: (size=0002)                                                  */
            __IO uint16_t  DATAH;               /*!< 0002: DATAH register                                               */
            struct {                            /*!< 0000: (size=0002)                                                  */
               __IO uint8_t   DATAHL;           /*!< 0002: DATAHL register                                              */
               __IO uint8_t   DATAHU;           /*!< 0003: DATAHU register                                              */
            };
         };
      };
   };
   union {                                      /*!< 0000: (size=0004)                                                  */
      __IO uint32_t  GPOLY;                     /*!< 0004: Polynomial register                                          */
      struct {                                  /*!< 0000: (size=0004)                                                  */
         union {                                /*!< 0000: (size=0002)                                                  */
            __IO uint16_t  GPOLYL;              /*!< 0004: GPOLYL register                                              */
            struct {                            /*!< 0000: (size=0002)                                                  */
               __IO uint8_t   GPOLYLL;          /*!< 0004: GPOLYLL register                                             */
               __IO uint8_t   GPOLYLU;          /*!< 0005: GPOLYLU register                                             */
            };
         };
         union {                                /*!< 0000: (size=0002)                                                  */
            __IO uint16_t  GPOLYH;              /*!< 0006: GPOLYH register                                              */
            struct {                            /*!< 0000: (size=0002)                                                  */
               __IO uint8_t   GPOLYHL;          /*!< 0006: GPOLYHL register                                             */
               __IO uint8_t   GPOLYHU;          /*!< 0007: GPOLYHU register                                             */
            };
         };
      };
   };
   union {                                      /*!< 0000: (size=0004)                                                  */
      __IO uint32_t  CTRL;                      /*!< 0008: Control register                                             */
      struct {                                  /*!< 0000: (size=0004)                                                  */
         __I  uint8_t   RESERVED0[3];           /*!< 0008:                                                              */
         __IO uint8_t   CTRLHU;                 /*!< 000B: CTRLHU register                                              */
      };
   };
} CRC_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'CRC' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- CRC_DATA                                 ------ */
#define CRC_DATA_LL_MASK                         (0xFFUL << CRC_DATA_LL_SHIFT)                       /*!< CRC_DATA: LL Mask                       */
#define CRC_DATA_LL_SHIFT                        0                                                   /*!< CRC_DATA: LL Position                   */
#define CRC_DATA_LL(x)                           (((x)<<CRC_DATA_LL_SHIFT)&CRC_DATA_LL_MASK)         /*!< CRC_DATA                                */
#define CRC_DATA_LU_MASK                         (0xFFUL << CRC_DATA_LU_SHIFT)                       /*!< CRC_DATA: LU Mask                       */
#define CRC_DATA_LU_SHIFT                        8                                                   /*!< CRC_DATA: LU Position                   */
#define CRC_DATA_LU(x)                           (((x)<<CRC_DATA_LU_SHIFT)&CRC_DATA_LU_MASK)         /*!< CRC_DATA                                */
#define CRC_DATA_HL_MASK                         (0xFFUL << CRC_DATA_HL_SHIFT)                       /*!< CRC_DATA: HL Mask                       */
#define CRC_DATA_HL_SHIFT                        16                                                  /*!< CRC_DATA: HL Position                   */
#define CRC_DATA_HL(x)                           (((x)<<CRC_DATA_HL_SHIFT)&CRC_DATA_HL_MASK)         /*!< CRC_DATA                                */
#define CRC_DATA_HU_MASK                         (0xFFUL << CRC_DATA_HU_SHIFT)                       /*!< CRC_DATA: HU Mask                       */
#define CRC_DATA_HU_SHIFT                        24                                                  /*!< CRC_DATA: HU Position                   */
#define CRC_DATA_HU(x)                           (((x)<<CRC_DATA_HU_SHIFT)&CRC_DATA_HU_MASK)         /*!< CRC_DATA                                */

/* ------- CRC_DATAL                                ------ */
#define CRC_DATAL_DATAL_MASK                     (0xFFFFUL << CRC_DATAL_DATAL_SHIFT)                 /*!< CRC_DATAL: DATAL Mask                   */
#define CRC_DATAL_DATAL_SHIFT                    0                                                   /*!< CRC_DATAL: DATAL Position               */
#define CRC_DATAL_DATAL(x)                       (((x)<<CRC_DATAL_DATAL_SHIFT)&CRC_DATAL_DATAL_MASK) /*!< CRC_DATAL                               */

/* ------- CRC_DATALL                               ------ */
#define CRC_DATALL_DATALL_MASK                   (0xFFUL << CRC_DATALL_DATALL_SHIFT)                 /*!< CRC_DATALL: DATALL Mask                 */
#define CRC_DATALL_DATALL_SHIFT                  0                                                   /*!< CRC_DATALL: DATALL Position             */
#define CRC_DATALL_DATALL(x)                     (((x)<<CRC_DATALL_DATALL_SHIFT)&CRC_DATALL_DATALL_MASK) /*!< CRC_DATALL                              */

/* ------- CRC_DATALU                               ------ */
#define CRC_DATALU_DATALU_MASK                   (0xFFUL << CRC_DATALU_DATALU_SHIFT)                 /*!< CRC_DATALU: DATALU Mask                 */
#define CRC_DATALU_DATALU_SHIFT                  0                                                   /*!< CRC_DATALU: DATALU Position             */
#define CRC_DATALU_DATALU(x)                     (((x)<<CRC_DATALU_DATALU_SHIFT)&CRC_DATALU_DATALU_MASK) /*!< CRC_DATALU                              */

/* ------- CRC_DATAH                                ------ */
#define CRC_DATAH_DATAH_MASK                     (0xFFFFUL << CRC_DATAH_DATAH_SHIFT)                 /*!< CRC_DATAH: DATAH Mask                   */
#define CRC_DATAH_DATAH_SHIFT                    0                                                   /*!< CRC_DATAH: DATAH Position               */
#define CRC_DATAH_DATAH(x)                       (((x)<<CRC_DATAH_DATAH_SHIFT)&CRC_DATAH_DATAH_MASK) /*!< CRC_DATAH                               */

/* ------- CRC_DATAHL                               ------ */
#define CRC_DATAHL_DATAHL_MASK                   (0xFFUL << CRC_DATAHL_DATAHL_SHIFT)                 /*!< CRC_DATAHL: DATAHL Mask                 */
#define CRC_DATAHL_DATAHL_SHIFT                  0                                                   /*!< CRC_DATAHL: DATAHL Position             */
#define CRC_DATAHL_DATAHL(x)                     (((x)<<CRC_DATAHL_DATAHL_SHIFT)&CRC_DATAHL_DATAHL_MASK) /*!< CRC_DATAHL                              */

/* ------- CRC_DATAHU                               ------ */
#define CRC_DATAHU_DATAHU_MASK                   (0xFFUL << CRC_DATAHU_DATAHU_SHIFT)                 /*!< CRC_DATAHU: DATAHU Mask                 */
#define CRC_DATAHU_DATAHU_SHIFT                  0                                                   /*!< CRC_DATAHU: DATAHU Position             */
#define CRC_DATAHU_DATAHU(x)                     (((x)<<CRC_DATAHU_DATAHU_SHIFT)&CRC_DATAHU_DATAHU_MASK) /*!< CRC_DATAHU                              */

/* ------- CRC_GPOLY                                ------ */
#define CRC_GPOLY_LOW_MASK                       (0xFFFFUL << CRC_GPOLY_LOW_SHIFT)                   /*!< CRC_GPOLY: LOW Mask                     */
#define CRC_GPOLY_LOW_SHIFT                      0                                                   /*!< CRC_GPOLY: LOW Position                 */
#define CRC_GPOLY_LOW(x)                         (((x)<<CRC_GPOLY_LOW_SHIFT)&CRC_GPOLY_LOW_MASK)     /*!< CRC_GPOLY                               */
#define CRC_GPOLY_HIGH_MASK                      (0xFFFFUL << CRC_GPOLY_HIGH_SHIFT)                  /*!< CRC_GPOLY: HIGH Mask                    */
#define CRC_GPOLY_HIGH_SHIFT                     16                                                  /*!< CRC_GPOLY: HIGH Position                */
#define CRC_GPOLY_HIGH(x)                        (((x)<<CRC_GPOLY_HIGH_SHIFT)&CRC_GPOLY_HIGH_MASK)   /*!< CRC_GPOLY                               */

/* ------- CRC_GPOLYL                               ------ */
#define CRC_GPOLYL_GPOLYL_MASK                   (0xFFFFUL << CRC_GPOLYL_GPOLYL_SHIFT)               /*!< CRC_GPOLYL: GPOLYL Mask                 */
#define CRC_GPOLYL_GPOLYL_SHIFT                  0                                                   /*!< CRC_GPOLYL: GPOLYL Position             */
#define CRC_GPOLYL_GPOLYL(x)                     (((x)<<CRC_GPOLYL_GPOLYL_SHIFT)&CRC_GPOLYL_GPOLYL_MASK) /*!< CRC_GPOLYL                              */

/* ------- CRC_GPOLYLL                              ------ */
#define CRC_GPOLYLL_GPOLYLL_MASK                 (0xFFUL << CRC_GPOLYLL_GPOLYLL_SHIFT)               /*!< CRC_GPOLYLL: GPOLYLL Mask               */
#define CRC_GPOLYLL_GPOLYLL_SHIFT                0                                                   /*!< CRC_GPOLYLL: GPOLYLL Position           */
#define CRC_GPOLYLL_GPOLYLL(x)                   (((x)<<CRC_GPOLYLL_GPOLYLL_SHIFT)&CRC_GPOLYLL_GPOLYLL_MASK) /*!< CRC_GPOLYLL                             */

/* ------- CRC_GPOLYLU                              ------ */
#define CRC_GPOLYLU_GPOLYLU_MASK                 (0xFFUL << CRC_GPOLYLU_GPOLYLU_SHIFT)               /*!< CRC_GPOLYLU: GPOLYLU Mask               */
#define CRC_GPOLYLU_GPOLYLU_SHIFT                0                                                   /*!< CRC_GPOLYLU: GPOLYLU Position           */
#define CRC_GPOLYLU_GPOLYLU(x)                   (((x)<<CRC_GPOLYLU_GPOLYLU_SHIFT)&CRC_GPOLYLU_GPOLYLU_MASK) /*!< CRC_GPOLYLU                             */

/* ------- CRC_GPOLYH                               ------ */
#define CRC_GPOLYH_GPOLYH_MASK                   (0xFFFFUL << CRC_GPOLYH_GPOLYH_SHIFT)               /*!< CRC_GPOLYH: GPOLYH Mask                 */
#define CRC_GPOLYH_GPOLYH_SHIFT                  0                                                   /*!< CRC_GPOLYH: GPOLYH Position             */
#define CRC_GPOLYH_GPOLYH(x)                     (((x)<<CRC_GPOLYH_GPOLYH_SHIFT)&CRC_GPOLYH_GPOLYH_MASK) /*!< CRC_GPOLYH                              */

/* ------- CRC_GPOLYHL                              ------ */
#define CRC_GPOLYHL_GPOLYHL_MASK                 (0xFFUL << CRC_GPOLYHL_GPOLYHL_SHIFT)               /*!< CRC_GPOLYHL: GPOLYHL Mask               */
#define CRC_GPOLYHL_GPOLYHL_SHIFT                0                                                   /*!< CRC_GPOLYHL: GPOLYHL Position           */
#define CRC_GPOLYHL_GPOLYHL(x)                   (((x)<<CRC_GPOLYHL_GPOLYHL_SHIFT)&CRC_GPOLYHL_GPOLYHL_MASK) /*!< CRC_GPOLYHL                             */

/* ------- CRC_GPOLYHU                              ------ */
#define CRC_GPOLYHU_GPOLYHU_MASK                 (0xFFUL << CRC_GPOLYHU_GPOLYHU_SHIFT)               /*!< CRC_GPOLYHU: GPOLYHU Mask               */
#define CRC_GPOLYHU_GPOLYHU_SHIFT                0                                                   /*!< CRC_GPOLYHU: GPOLYHU Position           */
#define CRC_GPOLYHU_GPOLYHU(x)                   (((x)<<CRC_GPOLYHU_GPOLYHU_SHIFT)&CRC_GPOLYHU_GPOLYHU_MASK) /*!< CRC_GPOLYHU                             */

/* ------- CRC_CTRL                                 ------ */
#define CRC_CTRL_TCRC_MASK                       (0x01UL << CRC_CTRL_TCRC_SHIFT)                     /*!< CRC_CTRL: TCRC Mask                     */
#define CRC_CTRL_TCRC_SHIFT                      24                                                  /*!< CRC_CTRL: TCRC Position                 */
#define CRC_CTRL_WAS_MASK                        (0x01UL << CRC_CTRL_WAS_SHIFT)                      /*!< CRC_CTRL: WAS Mask                      */
#define CRC_CTRL_WAS_SHIFT                       25                                                  /*!< CRC_CTRL: WAS Position                  */
#define CRC_CTRL_FXOR_MASK                       (0x01UL << CRC_CTRL_FXOR_SHIFT)                     /*!< CRC_CTRL: FXOR Mask                     */
#define CRC_CTRL_FXOR_SHIFT                      26                                                  /*!< CRC_CTRL: FXOR Position                 */
#define CRC_CTRL_TOTR_MASK                       (0x03UL << CRC_CTRL_TOTR_SHIFT)                     /*!< CRC_CTRL: TOTR Mask                     */
#define CRC_CTRL_TOTR_SHIFT                      28                                                  /*!< CRC_CTRL: TOTR Position                 */
#define CRC_CTRL_TOTR(x)                         (((x)<<CRC_CTRL_TOTR_SHIFT)&CRC_CTRL_TOTR_MASK)     /*!< CRC_CTRL                                */
#define CRC_CTRL_TOT_MASK                        (0x03UL << CRC_CTRL_TOT_SHIFT)                      /*!< CRC_CTRL: TOT Mask                      */
#define CRC_CTRL_TOT_SHIFT                       30                                                  /*!< CRC_CTRL: TOT Position                  */
#define CRC_CTRL_TOT(x)                          (((x)<<CRC_CTRL_TOT_SHIFT)&CRC_CTRL_TOT_MASK)       /*!< CRC_CTRL                                */

/* ------- CRC_CTRLHU                               ------ */
#define CRC_CTRLHU_TCRC_MASK                     (0x01UL << CRC_CTRLHU_TCRC_SHIFT)                   /*!< CRC_CTRLHU: TCRC Mask                   */
#define CRC_CTRLHU_TCRC_SHIFT                    0                                                   /*!< CRC_CTRLHU: TCRC Position               */
#define CRC_CTRLHU_WAS_MASK                      (0x01UL << CRC_CTRLHU_WAS_SHIFT)                    /*!< CRC_CTRLHU: WAS Mask                    */
#define CRC_CTRLHU_WAS_SHIFT                     1                                                   /*!< CRC_CTRLHU: WAS Position                */
#define CRC_CTRLHU_FXOR_MASK                     (0x01UL << CRC_CTRLHU_FXOR_SHIFT)                   /*!< CRC_CTRLHU: FXOR Mask                   */
#define CRC_CTRLHU_FXOR_SHIFT                    2                                                   /*!< CRC_CTRLHU: FXOR Position               */
#define CRC_CTRLHU_TOTR_MASK                     (0x03UL << CRC_CTRLHU_TOTR_SHIFT)                   /*!< CRC_CTRLHU: TOTR Mask                   */
#define CRC_CTRLHU_TOTR_SHIFT                    4                                                   /*!< CRC_CTRLHU: TOTR Position               */
#define CRC_CTRLHU_TOTR(x)                       (((x)<<CRC_CTRLHU_TOTR_SHIFT)&CRC_CTRLHU_TOTR_MASK) /*!< CRC_CTRLHU                              */
#define CRC_CTRLHU_TOT_MASK                      (0x03UL << CRC_CTRLHU_TOT_SHIFT)                    /*!< CRC_CTRLHU: TOT Mask                    */
#define CRC_CTRLHU_TOT_SHIFT                     6                                                   /*!< CRC_CTRLHU: TOT Position                */
#define CRC_CTRLHU_TOT(x)                        (((x)<<CRC_CTRLHU_TOT_SHIFT)&CRC_CTRLHU_TOT_MASK)   /*!< CRC_CTRLHU                              */

/* -------------------------------------------------------------------------------- */
/* -----------     'CRC' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define CRC_DATA                       (CRC->DATA)
#define CRC_DATAL                      (CRC->DATAL)
#define CRC_DATALL                     (CRC->DATALL)
#define CRC_DATALU                     (CRC->DATALU)
#define CRC_DATAH                      (CRC->DATAH)
#define CRC_DATAHL                     (CRC->DATAHL)
#define CRC_DATAHU                     (CRC->DATAHU)
#define CRC_GPOLY                      (CRC->GPOLY)
#define CRC_GPOLYL                     (CRC->GPOLYL)
#define CRC_GPOLYLL                    (CRC->GPOLYLL)
#define CRC_GPOLYLU                    (CRC->GPOLYLU)
#define CRC_GPOLYH                     (CRC->GPOLYH)
#define CRC_GPOLYHL                    (CRC->GPOLYHL)
#define CRC_GPOLYHU                    (CRC->GPOLYHU)
#define CRC_CTRL                       (CRC->CTRL)
#define CRC_CTRLHU                     (CRC->CTRLHU)

/* ================================================================================ */
/* ================           DAC0 (file:DAC0_MKLZ4)               ================ */
/* ================================================================================ */

/**
 * @brief 12-Bit Digital-to-Analog Converter
 */
typedef struct {                                /*!<       DAC0 Structure                                               */
   struct { /* (cluster) */                     /*!< 0000: (size=0x0004, 4)                                             */
      __IO uint8_t   DATL;                      /*!< 0000: Data Low Register                                            */
      __IO uint8_t   DATH;                      /*!< 0001: Data High Register                                           */
   } DAT[2];
   __I  uint32_t  RESERVED0[7];                 /*!< 0004:                                                              */
   __IO uint8_t   SR;                           /*!< 0020: Status Register                                              */
   __IO uint8_t   C0;                           /*!< 0021: Control Register                                             */
   __IO uint8_t   C1;                           /*!< 0022: Control Register 1                                           */
   __IO uint8_t   C2;                           /*!< 0023: Control Register 2                                           */
} DAC0_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'DAC0' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- DAC0_DATL                                ------ */
#define DAC_DATL_DATA0_MASK                      (0xFFUL << DAC_DATL_DATA0_SHIFT)                    /*!< DAC0_DATL: DATA0 Mask                   */
#define DAC_DATL_DATA0_SHIFT                     0                                                   /*!< DAC0_DATL: DATA0 Position               */
#define DAC_DATL_DATA0(x)                        (((x)<<DAC_DATL_DATA0_SHIFT)&DAC_DATL_DATA0_MASK)   /*!< DAC0_DATL                               */

/* ------- DAC0_DATH                                ------ */
#define DAC_DATH_DATA1_MASK                      (0x0FUL << DAC_DATH_DATA1_SHIFT)                    /*!< DAC0_DATH: DATA1 Mask                   */
#define DAC_DATH_DATA1_SHIFT                     0                                                   /*!< DAC0_DATH: DATA1 Position               */
#define DAC_DATH_DATA1(x)                        (((x)<<DAC_DATH_DATA1_SHIFT)&DAC_DATH_DATA1_MASK)   /*!< DAC0_DATH                               */

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

#define DAC0_DAT0L                     (DAC0->DAT[0].DATL)
#define DAC0_DAT0H                     (DAC0->DAT[0].DATH)
#define DAC0_DAT1L                     (DAC0->DAT[1].DATL)
#define DAC0_DAT1H                     (DAC0->DAT[1].DATH)
#define DAC0_SR                        (DAC0->SR)
#define DAC0_C0                        (DAC0->C0)
#define DAC0_C1                        (DAC0->C1)
#define DAC0_C2                        (DAC0->C2)

/* ================================================================================ */
/* ================           DMA (file:DMA_MKV)                   ================ */
/* ================================================================================ */

/**
 * @brief Enhanced direct memory access controller
 */
typedef struct {                                /*!<       DMA Structure                                                */
   __IO uint32_t  CR;                           /*!< 0000: Control Register                                             */
   __I  uint32_t  ES;                           /*!< 0004: Error Status Register                                        */
   __I  uint32_t  RESERVED0;                    /*!< 0008:                                                              */
   __IO uint32_t  ERQ;                          /*!< 000C: Enable Request Register                                      */
   __I  uint32_t  RESERVED1;                    /*!< 0010:                                                              */
   __IO uint32_t  EEI;                          /*!< 0014: Enable Error Interrupt Register                              */
   __O  uint8_t   CEEI;                         /*!< 0018: Clear Enable Error Interrupt Register                        */
   __O  uint8_t   SEEI;                         /*!< 0019: Set Enable Error Interrupt Register                          */
   __O  uint8_t   CERQ;                         /*!< 001A: Clear Enable Request Register                                */
   __O  uint8_t   SERQ;                         /*!< 001B: Set Enable Request Register                                  */
   __O  uint8_t   CDNE;                         /*!< 001C: Clear DONE Status Bit Register                               */
   __O  uint8_t   SSRT;                         /*!< 001D: Set START Bit Register                                       */
   __O  uint8_t   CERR;                         /*!< 001E: Clear Error Register                                         */
   __O  uint8_t   CINT;                         /*!< 001F: Clear Interrupt Request Register                             */
   __I  uint32_t  RESERVED2;                    /*!< 0020:                                                              */
   __IO uint32_t  INT;                          /*!< 0024: Interrupt Request Register                                   */
   __I  uint32_t  RESERVED3;                    /*!< 0028:                                                              */
   __IO uint32_t  ERR;                          /*!< 002C: Error Register                                               */
   __I  uint32_t  RESERVED4;                    /*!< 0030:                                                              */
   __IO uint32_t  HRS;                          /*!< 0034: Hardware Request Status Register                             */
   __I  uint32_t  RESERVED5[3];                 /*!< 0038:                                                              */
   __IO uint32_t  EARS;                         /*!< 0044: Enable Asynchronous Request in Stop Register                 */
   __I  uint32_t  RESERVED6[46];                /*!< 0048:                                                              */
   __IO uint8_t   DCHPRI3;                      /*!< 0100: Channel n Priority Register                                  */
   __IO uint8_t   DCHPRI2;                      /*!< 0101: Channel n Priority Register                                  */
   __IO uint8_t   DCHPRI1;                      /*!< 0102: Channel n Priority Register                                  */
   __IO uint8_t   DCHPRI0;                      /*!< 0103: Channel n Priority Register                                  */
   __I  uint32_t  RESERVED7[959];               /*!< 0104:                                                              */
   struct { /* (cluster) */                     /*!< 1000: (size=0x0080, 128)                                           */
      __IO uint32_t  SADDR;                     /*!< 1000: TCD Source Address                                           */
      __IO uint16_t  SOFF;                      /*!< 1004: TCD Signed Source Address Offset                             */
      __IO uint16_t  ATTR;                      /*!< 1006: TCD Transfer Attributes                                      */
      union {                                   /*!< 1000: (size=0004)                                                  */
         __IO uint32_t  NBYTES_MLNO;            /*!< 1008: TCD Minor Byte Count (Minor Loop Disabled)                   */
         __IO uint32_t  NBYTES_MLOFFNO;         /*!< 1008: TCD Signed Minor Loop Offset (Minor Loop Enabled and Offset Disabled) */
         __IO uint32_t  NBYTES_MLOFFYES;        /*!< 1008: TCD Signed Minor Loop Offset (Minor Loop and Offset Enabled) */
      };
      __IO uint32_t  SLAST;                     /*!< 100C: TCD Last Source Address Adjustment                           */
      __IO uint32_t  DADDR;                     /*!< 1010: TCD Destination Address                                      */
      __IO uint16_t  DOFF;                      /*!< 1014: TCD Signed Destination Address Offset                        */
      union {                                   /*!< 1000: (size=0002)                                                  */
         __IO uint16_t  CITER_ELINKNO;          /*!< 1016: TCD Current Minor Loop Link, Major Loop Count (Channel Linking Disabled) */
         __IO uint16_t  CITER_ELINKYES;         /*!< 1016: TCD Current Minor Loop Link, Major Loop Count (Channel Linking Enabled) */
      };
      __IO uint32_t  DLASTSGA;                  /*!< 1018: TCD Last Destination Address Adjustment/Scatter Gather Address */
      __IO uint16_t  CSR;                       /*!< 101C: TCD Control and Status                                       */
      union {                                   /*!< 1000: (size=0002)                                                  */
         __IO uint16_t  BITER_ELINKNO;          /*!< 101E: TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Disabled) */
         __IO uint16_t  BITER_ELINKYES;         /*!< 101E: TCD Beginning Minor Loop Link, Major Loop Count (Channel Linking Enabled) */
      };
   } TCD[4];
} DMA_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'DMA' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- DMA_CR                                   ------ */
#define DMA_CR_EDBG_MASK                         (0x01UL << DMA_CR_EDBG_SHIFT)                       /*!< DMA_CR: EDBG Mask                       */
#define DMA_CR_EDBG_SHIFT                        1                                                   /*!< DMA_CR: EDBG Position                   */
#define DMA_CR_ERCA_MASK                         (0x01UL << DMA_CR_ERCA_SHIFT)                       /*!< DMA_CR: ERCA Mask                       */
#define DMA_CR_ERCA_SHIFT                        2                                                   /*!< DMA_CR: ERCA Position                   */
#define DMA_CR_HOE_MASK                          (0x01UL << DMA_CR_HOE_SHIFT)                        /*!< DMA_CR: HOE Mask                        */
#define DMA_CR_HOE_SHIFT                         4                                                   /*!< DMA_CR: HOE Position                    */
#define DMA_CR_HALT_MASK                         (0x01UL << DMA_CR_HALT_SHIFT)                       /*!< DMA_CR: HALT Mask                       */
#define DMA_CR_HALT_SHIFT                        5                                                   /*!< DMA_CR: HALT Position                   */
#define DMA_CR_CLM_MASK                          (0x01UL << DMA_CR_CLM_SHIFT)                        /*!< DMA_CR: CLM Mask                        */
#define DMA_CR_CLM_SHIFT                         6                                                   /*!< DMA_CR: CLM Position                    */
#define DMA_CR_EMLM_MASK                         (0x01UL << DMA_CR_EMLM_SHIFT)                       /*!< DMA_CR: EMLM Mask                       */
#define DMA_CR_EMLM_SHIFT                        7                                                   /*!< DMA_CR: EMLM Position                   */
#define DMA_CR_ECX_MASK                          (0x01UL << DMA_CR_ECX_SHIFT)                        /*!< DMA_CR: ECX Mask                        */
#define DMA_CR_ECX_SHIFT                         16                                                  /*!< DMA_CR: ECX Position                    */
#define DMA_CR_CX_MASK                           (0x01UL << DMA_CR_CX_SHIFT)                         /*!< DMA_CR: CX Mask                         */
#define DMA_CR_CX_SHIFT                          17                                                  /*!< DMA_CR: CX Position                     */

/* ------- DMA_ES                                   ------ */
#define DMA_ES_DBE_MASK                          (0x01UL << DMA_ES_DBE_SHIFT)                        /*!< DMA_ES: DBE Mask                        */
#define DMA_ES_DBE_SHIFT                         0                                                   /*!< DMA_ES: DBE Position                    */
#define DMA_ES_SBE_MASK                          (0x01UL << DMA_ES_SBE_SHIFT)                        /*!< DMA_ES: SBE Mask                        */
#define DMA_ES_SBE_SHIFT                         1                                                   /*!< DMA_ES: SBE Position                    */
#define DMA_ES_SGE_MASK                          (0x01UL << DMA_ES_SGE_SHIFT)                        /*!< DMA_ES: SGE Mask                        */
#define DMA_ES_SGE_SHIFT                         2                                                   /*!< DMA_ES: SGE Position                    */
#define DMA_ES_NCE_MASK                          (0x01UL << DMA_ES_NCE_SHIFT)                        /*!< DMA_ES: NCE Mask                        */
#define DMA_ES_NCE_SHIFT                         3                                                   /*!< DMA_ES: NCE Position                    */
#define DMA_ES_DOE_MASK                          (0x01UL << DMA_ES_DOE_SHIFT)                        /*!< DMA_ES: DOE Mask                        */
#define DMA_ES_DOE_SHIFT                         4                                                   /*!< DMA_ES: DOE Position                    */
#define DMA_ES_DAE_MASK                          (0x01UL << DMA_ES_DAE_SHIFT)                        /*!< DMA_ES: DAE Mask                        */
#define DMA_ES_DAE_SHIFT                         5                                                   /*!< DMA_ES: DAE Position                    */
#define DMA_ES_SOE_MASK                          (0x01UL << DMA_ES_SOE_SHIFT)                        /*!< DMA_ES: SOE Mask                        */
#define DMA_ES_SOE_SHIFT                         6                                                   /*!< DMA_ES: SOE Position                    */
#define DMA_ES_SAE_MASK                          (0x01UL << DMA_ES_SAE_SHIFT)                        /*!< DMA_ES: SAE Mask                        */
#define DMA_ES_SAE_SHIFT                         7                                                   /*!< DMA_ES: SAE Position                    */
#define DMA_ES_ERRCHN_MASK                       (0x03UL << DMA_ES_ERRCHN_SHIFT)                     /*!< DMA_ES: ERRCHN Mask                     */
#define DMA_ES_ERRCHN_SHIFT                      8                                                   /*!< DMA_ES: ERRCHN Position                 */
#define DMA_ES_ERRCHN(x)                         (((x)<<DMA_ES_ERRCHN_SHIFT)&DMA_ES_ERRCHN_MASK)     /*!< DMA_ES                                  */
#define DMA_ES_CPE_MASK                          (0x01UL << DMA_ES_CPE_SHIFT)                        /*!< DMA_ES: CPE Mask                        */
#define DMA_ES_CPE_SHIFT                         14                                                  /*!< DMA_ES: CPE Position                    */
#define DMA_ES_ECX_MASK                          (0x01UL << DMA_ES_ECX_SHIFT)                        /*!< DMA_ES: ECX Mask                        */
#define DMA_ES_ECX_SHIFT                         16                                                  /*!< DMA_ES: ECX Position                    */
#define DMA_ES_VLD_MASK                          (0x01UL << DMA_ES_VLD_SHIFT)                        /*!< DMA_ES: VLD Mask                        */
#define DMA_ES_VLD_SHIFT                         31                                                  /*!< DMA_ES: VLD Position                    */

/* ------- DMA_ERQ                                  ------ */
#define DMA_ERQ_ERQ0_MASK                        (0x01UL << DMA_ERQ_ERQ0_SHIFT)                      /*!< DMA_ERQ: ERQ0 Mask                      */
#define DMA_ERQ_ERQ0_SHIFT                       0                                                   /*!< DMA_ERQ: ERQ0 Position                  */
#define DMA_ERQ_ERQ1_MASK                        (0x01UL << DMA_ERQ_ERQ1_SHIFT)                      /*!< DMA_ERQ: ERQ1 Mask                      */
#define DMA_ERQ_ERQ1_SHIFT                       1                                                   /*!< DMA_ERQ: ERQ1 Position                  */
#define DMA_ERQ_ERQ2_MASK                        (0x01UL << DMA_ERQ_ERQ2_SHIFT)                      /*!< DMA_ERQ: ERQ2 Mask                      */
#define DMA_ERQ_ERQ2_SHIFT                       2                                                   /*!< DMA_ERQ: ERQ2 Position                  */
#define DMA_ERQ_ERQ3_MASK                        (0x01UL << DMA_ERQ_ERQ3_SHIFT)                      /*!< DMA_ERQ: ERQ3 Mask                      */
#define DMA_ERQ_ERQ3_SHIFT                       3                                                   /*!< DMA_ERQ: ERQ3 Position                  */

/* ------- DMA_EEI                                  ------ */
#define DMA_EEI_EEI0_MASK                        (0x01UL << DMA_EEI_EEI0_SHIFT)                      /*!< DMA_EEI: EEI0 Mask                      */
#define DMA_EEI_EEI0_SHIFT                       0                                                   /*!< DMA_EEI: EEI0 Position                  */
#define DMA_EEI_EEI1_MASK                        (0x01UL << DMA_EEI_EEI1_SHIFT)                      /*!< DMA_EEI: EEI1 Mask                      */
#define DMA_EEI_EEI1_SHIFT                       1                                                   /*!< DMA_EEI: EEI1 Position                  */
#define DMA_EEI_EEI2_MASK                        (0x01UL << DMA_EEI_EEI2_SHIFT)                      /*!< DMA_EEI: EEI2 Mask                      */
#define DMA_EEI_EEI2_SHIFT                       2                                                   /*!< DMA_EEI: EEI2 Position                  */
#define DMA_EEI_EEI3_MASK                        (0x01UL << DMA_EEI_EEI3_SHIFT)                      /*!< DMA_EEI: EEI3 Mask                      */
#define DMA_EEI_EEI3_SHIFT                       3                                                   /*!< DMA_EEI: EEI3 Position                  */

/* ------- DMA_CEEI                                 ------ */
#define DMA_CEEI_CEEI_MASK                       (0x03UL << DMA_CEEI_CEEI_SHIFT)                     /*!< DMA_CEEI: CEEI Mask                     */
#define DMA_CEEI_CEEI_SHIFT                      0                                                   /*!< DMA_CEEI: CEEI Position                 */
#define DMA_CEEI_CEEI(x)                         (((x)<<DMA_CEEI_CEEI_SHIFT)&DMA_CEEI_CEEI_MASK)     /*!< DMA_CEEI                                */
#define DMA_CEEI_CAEE_MASK                       (0x01UL << DMA_CEEI_CAEE_SHIFT)                     /*!< DMA_CEEI: CAEE Mask                     */
#define DMA_CEEI_CAEE_SHIFT                      6                                                   /*!< DMA_CEEI: CAEE Position                 */
#define DMA_CEEI_NOP_MASK                        (0x01UL << DMA_CEEI_NOP_SHIFT)                      /*!< DMA_CEEI: NOP Mask                      */
#define DMA_CEEI_NOP_SHIFT                       7                                                   /*!< DMA_CEEI: NOP Position                  */

/* ------- DMA_SEEI                                 ------ */
#define DMA_SEEI_SEEI_MASK                       (0x03UL << DMA_SEEI_SEEI_SHIFT)                     /*!< DMA_SEEI: SEEI Mask                     */
#define DMA_SEEI_SEEI_SHIFT                      0                                                   /*!< DMA_SEEI: SEEI Position                 */
#define DMA_SEEI_SEEI(x)                         (((x)<<DMA_SEEI_SEEI_SHIFT)&DMA_SEEI_SEEI_MASK)     /*!< DMA_SEEI                                */
#define DMA_SEEI_SAEE_MASK                       (0x01UL << DMA_SEEI_SAEE_SHIFT)                     /*!< DMA_SEEI: SAEE Mask                     */
#define DMA_SEEI_SAEE_SHIFT                      6                                                   /*!< DMA_SEEI: SAEE Position                 */
#define DMA_SEEI_NOP_MASK                        (0x01UL << DMA_SEEI_NOP_SHIFT)                      /*!< DMA_SEEI: NOP Mask                      */
#define DMA_SEEI_NOP_SHIFT                       7                                                   /*!< DMA_SEEI: NOP Position                  */

/* ------- DMA_CERQ                                 ------ */
#define DMA_CERQ_CERQ_MASK                       (0x03UL << DMA_CERQ_CERQ_SHIFT)                     /*!< DMA_CERQ: CERQ Mask                     */
#define DMA_CERQ_CERQ_SHIFT                      0                                                   /*!< DMA_CERQ: CERQ Position                 */
#define DMA_CERQ_CERQ(x)                         (((x)<<DMA_CERQ_CERQ_SHIFT)&DMA_CERQ_CERQ_MASK)     /*!< DMA_CERQ                                */
#define DMA_CERQ_CAER_MASK                       (0x01UL << DMA_CERQ_CAER_SHIFT)                     /*!< DMA_CERQ: CAER Mask                     */
#define DMA_CERQ_CAER_SHIFT                      6                                                   /*!< DMA_CERQ: CAER Position                 */
#define DMA_CERQ_NOP_MASK                        (0x01UL << DMA_CERQ_NOP_SHIFT)                      /*!< DMA_CERQ: NOP Mask                      */
#define DMA_CERQ_NOP_SHIFT                       7                                                   /*!< DMA_CERQ: NOP Position                  */

/* ------- DMA_SERQ                                 ------ */
#define DMA_SERQ_SERQ_MASK                       (0x03UL << DMA_SERQ_SERQ_SHIFT)                     /*!< DMA_SERQ: SERQ Mask                     */
#define DMA_SERQ_SERQ_SHIFT                      0                                                   /*!< DMA_SERQ: SERQ Position                 */
#define DMA_SERQ_SERQ(x)                         (((x)<<DMA_SERQ_SERQ_SHIFT)&DMA_SERQ_SERQ_MASK)     /*!< DMA_SERQ                                */
#define DMA_SERQ_SAER_MASK                       (0x01UL << DMA_SERQ_SAER_SHIFT)                     /*!< DMA_SERQ: SAER Mask                     */
#define DMA_SERQ_SAER_SHIFT                      6                                                   /*!< DMA_SERQ: SAER Position                 */
#define DMA_SERQ_NOP_MASK                        (0x01UL << DMA_SERQ_NOP_SHIFT)                      /*!< DMA_SERQ: NOP Mask                      */
#define DMA_SERQ_NOP_SHIFT                       7                                                   /*!< DMA_SERQ: NOP Position                  */

/* ------- DMA_CDNE                                 ------ */
#define DMA_CDNE_CDNE_MASK                       (0x03UL << DMA_CDNE_CDNE_SHIFT)                     /*!< DMA_CDNE: CDNE Mask                     */
#define DMA_CDNE_CDNE_SHIFT                      0                                                   /*!< DMA_CDNE: CDNE Position                 */
#define DMA_CDNE_CDNE(x)                         (((x)<<DMA_CDNE_CDNE_SHIFT)&DMA_CDNE_CDNE_MASK)     /*!< DMA_CDNE                                */
#define DMA_CDNE_CADN_MASK                       (0x01UL << DMA_CDNE_CADN_SHIFT)                     /*!< DMA_CDNE: CADN Mask                     */
#define DMA_CDNE_CADN_SHIFT                      6                                                   /*!< DMA_CDNE: CADN Position                 */
#define DMA_CDNE_NOP_MASK                        (0x01UL << DMA_CDNE_NOP_SHIFT)                      /*!< DMA_CDNE: NOP Mask                      */
#define DMA_CDNE_NOP_SHIFT                       7                                                   /*!< DMA_CDNE: NOP Position                  */

/* ------- DMA_SSRT                                 ------ */
#define DMA_SSRT_SSRT_MASK                       (0x03UL << DMA_SSRT_SSRT_SHIFT)                     /*!< DMA_SSRT: SSRT Mask                     */
#define DMA_SSRT_SSRT_SHIFT                      0                                                   /*!< DMA_SSRT: SSRT Position                 */
#define DMA_SSRT_SSRT(x)                         (((x)<<DMA_SSRT_SSRT_SHIFT)&DMA_SSRT_SSRT_MASK)     /*!< DMA_SSRT                                */
#define DMA_SSRT_SAST_MASK                       (0x01UL << DMA_SSRT_SAST_SHIFT)                     /*!< DMA_SSRT: SAST Mask                     */
#define DMA_SSRT_SAST_SHIFT                      6                                                   /*!< DMA_SSRT: SAST Position                 */
#define DMA_SSRT_NOP_MASK                        (0x01UL << DMA_SSRT_NOP_SHIFT)                      /*!< DMA_SSRT: NOP Mask                      */
#define DMA_SSRT_NOP_SHIFT                       7                                                   /*!< DMA_SSRT: NOP Position                  */

/* ------- DMA_CERR                                 ------ */
#define DMA_CERR_CERR_MASK                       (0x03UL << DMA_CERR_CERR_SHIFT)                     /*!< DMA_CERR: CERR Mask                     */
#define DMA_CERR_CERR_SHIFT                      0                                                   /*!< DMA_CERR: CERR Position                 */
#define DMA_CERR_CERR(x)                         (((x)<<DMA_CERR_CERR_SHIFT)&DMA_CERR_CERR_MASK)     /*!< DMA_CERR                                */
#define DMA_CERR_CAEI_MASK                       (0x01UL << DMA_CERR_CAEI_SHIFT)                     /*!< DMA_CERR: CAEI Mask                     */
#define DMA_CERR_CAEI_SHIFT                      6                                                   /*!< DMA_CERR: CAEI Position                 */
#define DMA_CERR_NOP_MASK                        (0x01UL << DMA_CERR_NOP_SHIFT)                      /*!< DMA_CERR: NOP Mask                      */
#define DMA_CERR_NOP_SHIFT                       7                                                   /*!< DMA_CERR: NOP Position                  */

/* ------- DMA_CINT                                 ------ */
#define DMA_CINT_CINT_MASK                       (0x03UL << DMA_CINT_CINT_SHIFT)                     /*!< DMA_CINT: CINT Mask                     */
#define DMA_CINT_CINT_SHIFT                      0                                                   /*!< DMA_CINT: CINT Position                 */
#define DMA_CINT_CINT(x)                         (((x)<<DMA_CINT_CINT_SHIFT)&DMA_CINT_CINT_MASK)     /*!< DMA_CINT                                */
#define DMA_CINT_CAIR_MASK                       (0x01UL << DMA_CINT_CAIR_SHIFT)                     /*!< DMA_CINT: CAIR Mask                     */
#define DMA_CINT_CAIR_SHIFT                      6                                                   /*!< DMA_CINT: CAIR Position                 */
#define DMA_CINT_NOP_MASK                        (0x01UL << DMA_CINT_NOP_SHIFT)                      /*!< DMA_CINT: NOP Mask                      */
#define DMA_CINT_NOP_SHIFT                       7                                                   /*!< DMA_CINT: NOP Position                  */

/* ------- DMA_INT                                  ------ */
#define DMA_INT_INT0_MASK                        (0x01UL << DMA_INT_INT0_SHIFT)                      /*!< DMA_INT: INT0 Mask                      */
#define DMA_INT_INT0_SHIFT                       0                                                   /*!< DMA_INT: INT0 Position                  */
#define DMA_INT_INT1_MASK                        (0x01UL << DMA_INT_INT1_SHIFT)                      /*!< DMA_INT: INT1 Mask                      */
#define DMA_INT_INT1_SHIFT                       1                                                   /*!< DMA_INT: INT1 Position                  */
#define DMA_INT_INT2_MASK                        (0x01UL << DMA_INT_INT2_SHIFT)                      /*!< DMA_INT: INT2 Mask                      */
#define DMA_INT_INT2_SHIFT                       2                                                   /*!< DMA_INT: INT2 Position                  */
#define DMA_INT_INT3_MASK                        (0x01UL << DMA_INT_INT3_SHIFT)                      /*!< DMA_INT: INT3 Mask                      */
#define DMA_INT_INT3_SHIFT                       3                                                   /*!< DMA_INT: INT3 Position                  */

/* ------- DMA_ERR                                  ------ */
#define DMA_ERR_ERR0_MASK                        (0x01UL << DMA_ERR_ERR0_SHIFT)                      /*!< DMA_ERR: ERR0 Mask                      */
#define DMA_ERR_ERR0_SHIFT                       0                                                   /*!< DMA_ERR: ERR0 Position                  */
#define DMA_ERR_ERR1_MASK                        (0x01UL << DMA_ERR_ERR1_SHIFT)                      /*!< DMA_ERR: ERR1 Mask                      */
#define DMA_ERR_ERR1_SHIFT                       1                                                   /*!< DMA_ERR: ERR1 Position                  */
#define DMA_ERR_ERR2_MASK                        (0x01UL << DMA_ERR_ERR2_SHIFT)                      /*!< DMA_ERR: ERR2 Mask                      */
#define DMA_ERR_ERR2_SHIFT                       2                                                   /*!< DMA_ERR: ERR2 Position                  */
#define DMA_ERR_ERR3_MASK                        (0x01UL << DMA_ERR_ERR3_SHIFT)                      /*!< DMA_ERR: ERR3 Mask                      */
#define DMA_ERR_ERR3_SHIFT                       3                                                   /*!< DMA_ERR: ERR3 Position                  */

/* ------- DMA_HRS                                  ------ */
#define DMA_HRS_HRS0_MASK                        (0x01UL << DMA_HRS_HRS0_SHIFT)                      /*!< DMA_HRS: HRS0 Mask                      */
#define DMA_HRS_HRS0_SHIFT                       0                                                   /*!< DMA_HRS: HRS0 Position                  */
#define DMA_HRS_HRS1_MASK                        (0x01UL << DMA_HRS_HRS1_SHIFT)                      /*!< DMA_HRS: HRS1 Mask                      */
#define DMA_HRS_HRS1_SHIFT                       1                                                   /*!< DMA_HRS: HRS1 Position                  */
#define DMA_HRS_HRS2_MASK                        (0x01UL << DMA_HRS_HRS2_SHIFT)                      /*!< DMA_HRS: HRS2 Mask                      */
#define DMA_HRS_HRS2_SHIFT                       2                                                   /*!< DMA_HRS: HRS2 Position                  */
#define DMA_HRS_HRS3_MASK                        (0x01UL << DMA_HRS_HRS3_SHIFT)                      /*!< DMA_HRS: HRS3 Mask                      */
#define DMA_HRS_HRS3_SHIFT                       3                                                   /*!< DMA_HRS: HRS3 Position                  */

/* ------- DMA_EARS                                 ------ */
#define DMA_EARS_EDREQ_0_MASK                    (0x01UL << DMA_EARS_EDREQ_0_SHIFT)                  /*!< DMA_EARS: EDREQ_0 Mask                  */
#define DMA_EARS_EDREQ_0_SHIFT                   0                                                   /*!< DMA_EARS: EDREQ_0 Position              */
#define DMA_EARS_EDREQ_1_MASK                    (0x01UL << DMA_EARS_EDREQ_1_SHIFT)                  /*!< DMA_EARS: EDREQ_1 Mask                  */
#define DMA_EARS_EDREQ_1_SHIFT                   1                                                   /*!< DMA_EARS: EDREQ_1 Position              */
#define DMA_EARS_EDREQ_2_MASK                    (0x01UL << DMA_EARS_EDREQ_2_SHIFT)                  /*!< DMA_EARS: EDREQ_2 Mask                  */
#define DMA_EARS_EDREQ_2_SHIFT                   2                                                   /*!< DMA_EARS: EDREQ_2 Position              */
#define DMA_EARS_EDREQ_3_MASK                    (0x01UL << DMA_EARS_EDREQ_3_SHIFT)                  /*!< DMA_EARS: EDREQ_3 Mask                  */
#define DMA_EARS_EDREQ_3_SHIFT                   3                                                   /*!< DMA_EARS: EDREQ_3 Position              */

/* ------- DMA_DCHPRI                               ------ */
#define DMA_DCHPRI_CHPRI_MASK                    (0x03UL << DMA_DCHPRI_CHPRI_SHIFT)                  /*!< DMA_DCHPRI: CHPRI Mask                  */
#define DMA_DCHPRI_CHPRI_SHIFT                   0                                                   /*!< DMA_DCHPRI: CHPRI Position              */
#define DMA_DCHPRI_CHPRI(x)                      (((x)<<DMA_DCHPRI_CHPRI_SHIFT)&DMA_DCHPRI_CHPRI_MASK) /*!< DMA_DCHPRI                              */
#define DMA_DCHPRI_DPA_MASK                      (0x01UL << DMA_DCHPRI_DPA_SHIFT)                    /*!< DMA_DCHPRI: DPA Mask                    */
#define DMA_DCHPRI_DPA_SHIFT                     6                                                   /*!< DMA_DCHPRI: DPA Position                */
#define DMA_DCHPRI_ECP_MASK                      (0x01UL << DMA_DCHPRI_ECP_SHIFT)                    /*!< DMA_DCHPRI: ECP Mask                    */
#define DMA_DCHPRI_ECP_SHIFT                     7                                                   /*!< DMA_DCHPRI: ECP Position                */

/* ------- DMA_SADDR                                ------ */
#define DMA_SADDR_SADDR_MASK                     (0xFFFFFFFFUL << DMA_SADDR_SADDR_SHIFT)             /*!< DMA_SADDR: SADDR Mask                   */
#define DMA_SADDR_SADDR_SHIFT                    0                                                   /*!< DMA_SADDR: SADDR Position               */
#define DMA_SADDR_SADDR(x)                       (((x)<<DMA_SADDR_SADDR_SHIFT)&DMA_SADDR_SADDR_MASK) /*!< DMA_SADDR                               */

/* ------- DMA_SOFF                                 ------ */
#define DMA_SOFF_SOFF_MASK                       (0xFFFFUL << DMA_SOFF_SOFF_SHIFT)                   /*!< DMA_SOFF: SOFF Mask                     */
#define DMA_SOFF_SOFF_SHIFT                      0                                                   /*!< DMA_SOFF: SOFF Position                 */
#define DMA_SOFF_SOFF(x)                         (((x)<<DMA_SOFF_SOFF_SHIFT)&DMA_SOFF_SOFF_MASK)     /*!< DMA_SOFF                                */

/* ------- DMA_ATTR                                 ------ */
#define DMA_ATTR_DSIZE_MASK                      (0x07UL << DMA_ATTR_DSIZE_SHIFT)                    /*!< DMA_ATTR: DSIZE Mask                    */
#define DMA_ATTR_DSIZE_SHIFT                     0                                                   /*!< DMA_ATTR: DSIZE Position                */
#define DMA_ATTR_DSIZE(x)                        (((x)<<DMA_ATTR_DSIZE_SHIFT)&DMA_ATTR_DSIZE_MASK)   /*!< DMA_ATTR                                */
#define DMA_ATTR_DMOD_MASK                       (0x1FUL << DMA_ATTR_DMOD_SHIFT)                     /*!< DMA_ATTR: DMOD Mask                     */
#define DMA_ATTR_DMOD_SHIFT                      3                                                   /*!< DMA_ATTR: DMOD Position                 */
#define DMA_ATTR_DMOD(x)                         (((x)<<DMA_ATTR_DMOD_SHIFT)&DMA_ATTR_DMOD_MASK)     /*!< DMA_ATTR                                */
#define DMA_ATTR_SSIZE_MASK                      (0x07UL << DMA_ATTR_SSIZE_SHIFT)                    /*!< DMA_ATTR: SSIZE Mask                    */
#define DMA_ATTR_SSIZE_SHIFT                     8                                                   /*!< DMA_ATTR: SSIZE Position                */
#define DMA_ATTR_SSIZE(x)                        (((x)<<DMA_ATTR_SSIZE_SHIFT)&DMA_ATTR_SSIZE_MASK)   /*!< DMA_ATTR                                */
#define DMA_ATTR_SMOD_MASK                       (0x1FUL << DMA_ATTR_SMOD_SHIFT)                     /*!< DMA_ATTR: SMOD Mask                     */
#define DMA_ATTR_SMOD_SHIFT                      11                                                  /*!< DMA_ATTR: SMOD Position                 */
#define DMA_ATTR_SMOD(x)                         (((x)<<DMA_ATTR_SMOD_SHIFT)&DMA_ATTR_SMOD_MASK)     /*!< DMA_ATTR                                */

/* ------- DMA_NBYTES_MLNO                          ------ */
#define DMA_NBYTES_MLNO_NBYTES_MASK              (0xFFFFFFFFUL << DMA_NBYTES_MLNO_NBYTES_SHIFT)      /*!< DMA_NBYTES_MLNO: NBYTES Mask            */
#define DMA_NBYTES_MLNO_NBYTES_SHIFT             0                                                   /*!< DMA_NBYTES_MLNO: NBYTES Position        */
#define DMA_NBYTES_MLNO_NBYTES(x)                (((x)<<DMA_NBYTES_MLNO_NBYTES_SHIFT)&DMA_NBYTES_MLNO_NBYTES_MASK) /*!< DMA_NBYTES_MLNO                         */

/* ------- DMA_NBYTES_MLOFFNO                       ------ */
#define DMA_NBYTES_MLOFFNO_NBYTES_MASK           (0x3FFFFFFFUL << DMA_NBYTES_MLOFFNO_NBYTES_SHIFT)   /*!< DMA_NBYTES_MLOFFNO: NBYTES Mask         */
#define DMA_NBYTES_MLOFFNO_NBYTES_SHIFT          0                                                   /*!< DMA_NBYTES_MLOFFNO: NBYTES Position     */
#define DMA_NBYTES_MLOFFNO_NBYTES(x)             (((x)<<DMA_NBYTES_MLOFFNO_NBYTES_SHIFT)&DMA_NBYTES_MLOFFNO_NBYTES_MASK) /*!< DMA_NBYTES_MLOFFNO                      */
#define DMA_NBYTES_MLOFFNO_DMLOE_MASK            (0x01UL << DMA_NBYTES_MLOFFNO_DMLOE_SHIFT)          /*!< DMA_NBYTES_MLOFFNO: DMLOE Mask          */
#define DMA_NBYTES_MLOFFNO_DMLOE_SHIFT           30                                                  /*!< DMA_NBYTES_MLOFFNO: DMLOE Position      */
#define DMA_NBYTES_MLOFFNO_SMLOE_MASK            (0x01UL << DMA_NBYTES_MLOFFNO_SMLOE_SHIFT)          /*!< DMA_NBYTES_MLOFFNO: SMLOE Mask          */
#define DMA_NBYTES_MLOFFNO_SMLOE_SHIFT           31                                                  /*!< DMA_NBYTES_MLOFFNO: SMLOE Position      */

/* ------- DMA_NBYTES_MLOFFYES                      ------ */
#define DMA_NBYTES_MLOFFYES_NBYTES_MASK          (0x3FFUL << DMA_NBYTES_MLOFFYES_NBYTES_SHIFT)       /*!< DMA_NBYTES_MLOFFYES: NBYTES Mask        */
#define DMA_NBYTES_MLOFFYES_NBYTES_SHIFT         0                                                   /*!< DMA_NBYTES_MLOFFYES: NBYTES Position    */
#define DMA_NBYTES_MLOFFYES_NBYTES(x)            (((x)<<DMA_NBYTES_MLOFFYES_NBYTES_SHIFT)&DMA_NBYTES_MLOFFYES_NBYTES_MASK) /*!< DMA_NBYTES_MLOFFYES                     */
#define DMA_NBYTES_MLOFFYES_MLOFF_MASK           (0xFFFFFUL << DMA_NBYTES_MLOFFYES_MLOFF_SHIFT)      /*!< DMA_NBYTES_MLOFFYES: MLOFF Mask         */
#define DMA_NBYTES_MLOFFYES_MLOFF_SHIFT          10                                                  /*!< DMA_NBYTES_MLOFFYES: MLOFF Position     */
#define DMA_NBYTES_MLOFFYES_MLOFF(x)             (((x)<<DMA_NBYTES_MLOFFYES_MLOFF_SHIFT)&DMA_NBYTES_MLOFFYES_MLOFF_MASK) /*!< DMA_NBYTES_MLOFFYES                     */
#define DMA_NBYTES_MLOFFYES_DMLOE_MASK           (0x01UL << DMA_NBYTES_MLOFFYES_DMLOE_SHIFT)         /*!< DMA_NBYTES_MLOFFYES: DMLOE Mask         */
#define DMA_NBYTES_MLOFFYES_DMLOE_SHIFT          30                                                  /*!< DMA_NBYTES_MLOFFYES: DMLOE Position     */
#define DMA_NBYTES_MLOFFYES_SMLOE_MASK           (0x01UL << DMA_NBYTES_MLOFFYES_SMLOE_SHIFT)         /*!< DMA_NBYTES_MLOFFYES: SMLOE Mask         */
#define DMA_NBYTES_MLOFFYES_SMLOE_SHIFT          31                                                  /*!< DMA_NBYTES_MLOFFYES: SMLOE Position     */

/* ------- DMA_SLAST                                ------ */
#define DMA_SLAST_SLAST_MASK                     (0xFFFFFFFFUL << DMA_SLAST_SLAST_SHIFT)             /*!< DMA_SLAST: SLAST Mask                   */
#define DMA_SLAST_SLAST_SHIFT                    0                                                   /*!< DMA_SLAST: SLAST Position               */
#define DMA_SLAST_SLAST(x)                       (((x)<<DMA_SLAST_SLAST_SHIFT)&DMA_SLAST_SLAST_MASK) /*!< DMA_SLAST                               */

/* ------- DMA_DADDR                                ------ */
#define DMA_DADDR_DADDR_MASK                     (0xFFFFFFFFUL << DMA_DADDR_DADDR_SHIFT)             /*!< DMA_DADDR: DADDR Mask                   */
#define DMA_DADDR_DADDR_SHIFT                    0                                                   /*!< DMA_DADDR: DADDR Position               */
#define DMA_DADDR_DADDR(x)                       (((x)<<DMA_DADDR_DADDR_SHIFT)&DMA_DADDR_DADDR_MASK) /*!< DMA_DADDR                               */

/* ------- DMA_DOFF                                 ------ */
#define DMA_DOFF_DOFF_MASK                       (0xFFFFUL << DMA_DOFF_DOFF_SHIFT)                   /*!< DMA_DOFF: DOFF Mask                     */
#define DMA_DOFF_DOFF_SHIFT                      0                                                   /*!< DMA_DOFF: DOFF Position                 */
#define DMA_DOFF_DOFF(x)                         (((x)<<DMA_DOFF_DOFF_SHIFT)&DMA_DOFF_DOFF_MASK)     /*!< DMA_DOFF                                */

/* ------- DMA_CITER_ELINKNO                        ------ */
#define DMA_CITER_ELINKNO_CITER_MASK             (0x7FFFUL << DMA_CITER_ELINKNO_CITER_SHIFT)         /*!< DMA_CITER_ELINKNO: CITER Mask           */
#define DMA_CITER_ELINKNO_CITER_SHIFT            0                                                   /*!< DMA_CITER_ELINKNO: CITER Position       */
#define DMA_CITER_ELINKNO_CITER(x)               (((x)<<DMA_CITER_ELINKNO_CITER_SHIFT)&DMA_CITER_ELINKNO_CITER_MASK) /*!< DMA_CITER_ELINKNO                       */
#define DMA_CITER_ELINKNO_ELINK_MASK             (0x01UL << DMA_CITER_ELINKNO_ELINK_SHIFT)           /*!< DMA_CITER_ELINKNO: ELINK Mask           */
#define DMA_CITER_ELINKNO_ELINK_SHIFT            15                                                  /*!< DMA_CITER_ELINKNO: ELINK Position       */

/* ------- DMA_CITER_ELINKYES                       ------ */
#define DMA_CITER_ELINKYES_CITER_MASK            (0x1FFUL << DMA_CITER_ELINKYES_CITER_SHIFT)         /*!< DMA_CITER_ELINKYES: CITER Mask          */
#define DMA_CITER_ELINKYES_CITER_SHIFT           0                                                   /*!< DMA_CITER_ELINKYES: CITER Position      */
#define DMA_CITER_ELINKYES_CITER(x)              (((x)<<DMA_CITER_ELINKYES_CITER_SHIFT)&DMA_CITER_ELINKYES_CITER_MASK) /*!< DMA_CITER_ELINKYES                      */
#define DMA_CITER_ELINKYES_LINKCH_MASK           (0x03UL << DMA_CITER_ELINKYES_LINKCH_SHIFT)         /*!< DMA_CITER_ELINKYES: LINKCH Mask         */
#define DMA_CITER_ELINKYES_LINKCH_SHIFT          9                                                   /*!< DMA_CITER_ELINKYES: LINKCH Position     */
#define DMA_CITER_ELINKYES_LINKCH(x)             (((x)<<DMA_CITER_ELINKYES_LINKCH_SHIFT)&DMA_CITER_ELINKYES_LINKCH_MASK) /*!< DMA_CITER_ELINKYES                      */
#define DMA_CITER_ELINKYES_ELINK_MASK            (0x01UL << DMA_CITER_ELINKYES_ELINK_SHIFT)          /*!< DMA_CITER_ELINKYES: ELINK Mask          */
#define DMA_CITER_ELINKYES_ELINK_SHIFT           15                                                  /*!< DMA_CITER_ELINKYES: ELINK Position      */

/* ------- DMA_DLASTSGA                             ------ */
#define DMA_DLASTSGA_DLASTSGA_MASK               (0xFFFFFFFFUL << DMA_DLASTSGA_DLASTSGA_SHIFT)       /*!< DMA_DLASTSGA: DLASTSGA Mask             */
#define DMA_DLASTSGA_DLASTSGA_SHIFT              0                                                   /*!< DMA_DLASTSGA: DLASTSGA Position         */
#define DMA_DLASTSGA_DLASTSGA(x)                 (((x)<<DMA_DLASTSGA_DLASTSGA_SHIFT)&DMA_DLASTSGA_DLASTSGA_MASK) /*!< DMA_DLASTSGA                            */

/* ------- DMA_CSR                                  ------ */
#define DMA_CSR_START_MASK                       (0x01UL << DMA_CSR_START_SHIFT)                     /*!< DMA_CSR: START Mask                     */
#define DMA_CSR_START_SHIFT                      0                                                   /*!< DMA_CSR: START Position                 */
#define DMA_CSR_INTMAJOR_MASK                    (0x01UL << DMA_CSR_INTMAJOR_SHIFT)                  /*!< DMA_CSR: INTMAJOR Mask                  */
#define DMA_CSR_INTMAJOR_SHIFT                   1                                                   /*!< DMA_CSR: INTMAJOR Position              */
#define DMA_CSR_INTHALF_MASK                     (0x01UL << DMA_CSR_INTHALF_SHIFT)                   /*!< DMA_CSR: INTHALF Mask                   */
#define DMA_CSR_INTHALF_SHIFT                    2                                                   /*!< DMA_CSR: INTHALF Position               */
#define DMA_CSR_DREQ_MASK                        (0x01UL << DMA_CSR_DREQ_SHIFT)                      /*!< DMA_CSR: DREQ Mask                      */
#define DMA_CSR_DREQ_SHIFT                       3                                                   /*!< DMA_CSR: DREQ Position                  */
#define DMA_CSR_ESG_MASK                         (0x01UL << DMA_CSR_ESG_SHIFT)                       /*!< DMA_CSR: ESG Mask                       */
#define DMA_CSR_ESG_SHIFT                        4                                                   /*!< DMA_CSR: ESG Position                   */
#define DMA_CSR_MAJORELINK_MASK                  (0x01UL << DMA_CSR_MAJORELINK_SHIFT)                /*!< DMA_CSR: MAJORELINK Mask                */
#define DMA_CSR_MAJORELINK_SHIFT                 5                                                   /*!< DMA_CSR: MAJORELINK Position            */
#define DMA_CSR_ACTIVE_MASK                      (0x01UL << DMA_CSR_ACTIVE_SHIFT)                    /*!< DMA_CSR: ACTIVE Mask                    */
#define DMA_CSR_ACTIVE_SHIFT                     6                                                   /*!< DMA_CSR: ACTIVE Position                */
#define DMA_CSR_DONE_MASK                        (0x01UL << DMA_CSR_DONE_SHIFT)                      /*!< DMA_CSR: DONE Mask                      */
#define DMA_CSR_DONE_SHIFT                       7                                                   /*!< DMA_CSR: DONE Position                  */
#define DMA_CSR_MAJORLINKCH_MASK                 (0x03UL << DMA_CSR_MAJORLINKCH_SHIFT)               /*!< DMA_CSR: MAJORLINKCH Mask               */
#define DMA_CSR_MAJORLINKCH_SHIFT                8                                                   /*!< DMA_CSR: MAJORLINKCH Position           */
#define DMA_CSR_MAJORLINKCH(x)                   (((x)<<DMA_CSR_MAJORLINKCH_SHIFT)&DMA_CSR_MAJORLINKCH_MASK) /*!< DMA_CSR                                 */
#define DMA_CSR_BWC_MASK                         (0x03UL << DMA_CSR_BWC_SHIFT)                       /*!< DMA_CSR: BWC Mask                       */
#define DMA_CSR_BWC_SHIFT                        14                                                  /*!< DMA_CSR: BWC Position                   */
#define DMA_CSR_BWC(x)                           (((x)<<DMA_CSR_BWC_SHIFT)&DMA_CSR_BWC_MASK)         /*!< DMA_CSR                                 */

/* ------- DMA_BITER_ELINKNO                        ------ */
#define DMA_BITER_ELINKNO_BITER_MASK             (0x7FFFUL << DMA_BITER_ELINKNO_BITER_SHIFT)         /*!< DMA_BITER_ELINKNO: BITER Mask           */
#define DMA_BITER_ELINKNO_BITER_SHIFT            0                                                   /*!< DMA_BITER_ELINKNO: BITER Position       */
#define DMA_BITER_ELINKNO_BITER(x)               (((x)<<DMA_BITER_ELINKNO_BITER_SHIFT)&DMA_BITER_ELINKNO_BITER_MASK) /*!< DMA_BITER_ELINKNO                       */
#define DMA_BITER_ELINKNO_ELINK_MASK             (0x01UL << DMA_BITER_ELINKNO_ELINK_SHIFT)           /*!< DMA_BITER_ELINKNO: ELINK Mask           */
#define DMA_BITER_ELINKNO_ELINK_SHIFT            15                                                  /*!< DMA_BITER_ELINKNO: ELINK Position       */

/* ------- DMA_BITER_ELINKYES                       ------ */
#define DMA_BITER_ELINKYES_BITER_MASK            (0x1FFUL << DMA_BITER_ELINKYES_BITER_SHIFT)         /*!< DMA_BITER_ELINKYES: BITER Mask          */
#define DMA_BITER_ELINKYES_BITER_SHIFT           0                                                   /*!< DMA_BITER_ELINKYES: BITER Position      */
#define DMA_BITER_ELINKYES_BITER(x)              (((x)<<DMA_BITER_ELINKYES_BITER_SHIFT)&DMA_BITER_ELINKYES_BITER_MASK) /*!< DMA_BITER_ELINKYES                      */
#define DMA_BITER_ELINKYES_LINKCH_MASK           (0x03UL << DMA_BITER_ELINKYES_LINKCH_SHIFT)         /*!< DMA_BITER_ELINKYES: LINKCH Mask         */
#define DMA_BITER_ELINKYES_LINKCH_SHIFT          9                                                   /*!< DMA_BITER_ELINKYES: LINKCH Position     */
#define DMA_BITER_ELINKYES_LINKCH(x)             (((x)<<DMA_BITER_ELINKYES_LINKCH_SHIFT)&DMA_BITER_ELINKYES_LINKCH_MASK) /*!< DMA_BITER_ELINKYES                      */
#define DMA_BITER_ELINKYES_ELINK_MASK            (0x01UL << DMA_BITER_ELINKYES_ELINK_SHIFT)          /*!< DMA_BITER_ELINKYES: ELINK Mask          */
#define DMA_BITER_ELINKYES_ELINK_SHIFT           15                                                  /*!< DMA_BITER_ELINKYES: ELINK Position      */

/* -------------------------------------------------------------------------------- */
/* -----------     'DMA' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define DMA_CR                         (DMA->CR)
#define DMA_ES                         (DMA->ES)
#define DMA_ERQ                        (DMA->ERQ)
#define DMA_EEI                        (DMA->EEI)
#define DMA_CEEI                       (DMA->CEEI)
#define DMA_SEEI                       (DMA->SEEI)
#define DMA_CERQ                       (DMA->CERQ)
#define DMA_SERQ                       (DMA->SERQ)
#define DMA_CDNE                       (DMA->CDNE)
#define DMA_SSRT                       (DMA->SSRT)
#define DMA_CERR                       (DMA->CERR)
#define DMA_CINT                       (DMA->CINT)
#define DMA_INT                        (DMA->INT)
#define DMA_ERR                        (DMA->ERR)
#define DMA_HRS                        (DMA->HRS)
#define DMA_EARS                       (DMA->EARS)
#define DMA_DCHPRI3                    (DMA->DCHPRI3)
#define DMA_DCHPRI2                    (DMA->DCHPRI2)
#define DMA_DCHPRI1                    (DMA->DCHPRI1)
#define DMA_DCHPRI0                    (DMA->DCHPRI0)
#define DMA_TCD0_SADDR                 (DMA->TCD[0].SADDR)
#define DMA_TCD0_SOFF                  (DMA->TCD[0].SOFF)
#define DMA_TCD0_ATTR                  (DMA->TCD[0].ATTR)
#define DMA_TCD0_NBYTES_MLNO           (DMA->TCD[0].NBYTES_MLNO)
#define DMA_TCD0_NBYTES_MLOFFNO        (DMA->TCD[0].NBYTES_MLOFFNO)
#define DMA_TCD0_NBYTES_MLOFFYES       (DMA->TCD[0].NBYTES_MLOFFYES)
#define DMA_TCD0_SLAST                 (DMA->TCD[0].SLAST)
#define DMA_TCD0_DADDR                 (DMA->TCD[0].DADDR)
#define DMA_TCD0_DOFF                  (DMA->TCD[0].DOFF)
#define DMA_TCD0_CITER_ELINKNO         (DMA->TCD[0].CITER_ELINKNO)
#define DMA_TCD0_CITER_ELINKYES        (DMA->TCD[0].CITER_ELINKYES)
#define DMA_TCD0_DLASTSGA              (DMA->TCD[0].DLASTSGA)
#define DMA_TCD0_CSR                   (DMA->TCD[0].CSR)
#define DMA_TCD0_BITER_ELINKNO         (DMA->TCD[0].BITER_ELINKNO)
#define DMA_TCD0_BITER_ELINKYES        (DMA->TCD[0].BITER_ELINKYES)
#define DMA_TCD1_SADDR                 (DMA->TCD[1].SADDR)
#define DMA_TCD1_SOFF                  (DMA->TCD[1].SOFF)
#define DMA_TCD1_ATTR                  (DMA->TCD[1].ATTR)
#define DMA_TCD1_NBYTES_MLNO           (DMA->TCD[1].NBYTES_MLNO)
#define DMA_TCD1_NBYTES_MLOFFNO        (DMA->TCD[1].NBYTES_MLOFFNO)
#define DMA_TCD1_NBYTES_MLOFFYES       (DMA->TCD[1].NBYTES_MLOFFYES)
#define DMA_TCD1_SLAST                 (DMA->TCD[1].SLAST)
#define DMA_TCD1_DADDR                 (DMA->TCD[1].DADDR)
#define DMA_TCD1_DOFF                  (DMA->TCD[1].DOFF)
#define DMA_TCD1_CITER_ELINKNO         (DMA->TCD[1].CITER_ELINKNO)
#define DMA_TCD1_CITER_ELINKYES        (DMA->TCD[1].CITER_ELINKYES)
#define DMA_TCD1_DLASTSGA              (DMA->TCD[1].DLASTSGA)
#define DMA_TCD1_CSR                   (DMA->TCD[1].CSR)
#define DMA_TCD1_BITER_ELINKNO         (DMA->TCD[1].BITER_ELINKNO)
#define DMA_TCD1_BITER_ELINKYES        (DMA->TCD[1].BITER_ELINKYES)
#define DMA_TCD2_SADDR                 (DMA->TCD[2].SADDR)
#define DMA_TCD2_SOFF                  (DMA->TCD[2].SOFF)
#define DMA_TCD2_ATTR                  (DMA->TCD[2].ATTR)
#define DMA_TCD2_NBYTES_MLNO           (DMA->TCD[2].NBYTES_MLNO)
#define DMA_TCD2_NBYTES_MLOFFNO        (DMA->TCD[2].NBYTES_MLOFFNO)
#define DMA_TCD2_NBYTES_MLOFFYES       (DMA->TCD[2].NBYTES_MLOFFYES)
#define DMA_TCD2_SLAST                 (DMA->TCD[2].SLAST)
#define DMA_TCD2_DADDR                 (DMA->TCD[2].DADDR)
#define DMA_TCD2_DOFF                  (DMA->TCD[2].DOFF)
#define DMA_TCD2_CITER_ELINKNO         (DMA->TCD[2].CITER_ELINKNO)
#define DMA_TCD2_CITER_ELINKYES        (DMA->TCD[2].CITER_ELINKYES)
#define DMA_TCD2_DLASTSGA              (DMA->TCD[2].DLASTSGA)
#define DMA_TCD2_CSR                   (DMA->TCD[2].CSR)
#define DMA_TCD2_BITER_ELINKNO         (DMA->TCD[2].BITER_ELINKNO)
#define DMA_TCD2_BITER_ELINKYES        (DMA->TCD[2].BITER_ELINKYES)
#define DMA_TCD3_SADDR                 (DMA->TCD[3].SADDR)
#define DMA_TCD3_SOFF                  (DMA->TCD[3].SOFF)
#define DMA_TCD3_ATTR                  (DMA->TCD[3].ATTR)
#define DMA_TCD3_NBYTES_MLNO           (DMA->TCD[3].NBYTES_MLNO)
#define DMA_TCD3_NBYTES_MLOFFNO        (DMA->TCD[3].NBYTES_MLOFFNO)
#define DMA_TCD3_NBYTES_MLOFFYES       (DMA->TCD[3].NBYTES_MLOFFYES)
#define DMA_TCD3_SLAST                 (DMA->TCD[3].SLAST)
#define DMA_TCD3_DADDR                 (DMA->TCD[3].DADDR)
#define DMA_TCD3_DOFF                  (DMA->TCD[3].DOFF)
#define DMA_TCD3_CITER_ELINKNO         (DMA->TCD[3].CITER_ELINKNO)
#define DMA_TCD3_CITER_ELINKYES        (DMA->TCD[3].CITER_ELINKYES)
#define DMA_TCD3_DLASTSGA              (DMA->TCD[3].DLASTSGA)
#define DMA_TCD3_CSR                   (DMA->TCD[3].CSR)
#define DMA_TCD3_BITER_ELINKNO         (DMA->TCD[3].BITER_ELINKNO)
#define DMA_TCD3_BITER_ELINKYES        (DMA->TCD[3].BITER_ELINKYES)

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
/* ================           EWM (file:EWM_MKV)                   ================ */
/* ================================================================================ */

/**
 * @brief External Watchdog Monitor
 */
typedef struct {                                /*!<       EWM Structure                                                */
   __IO uint8_t   CTRL;                         /*!< 0000: Control Register                                             */
   __O  uint8_t   SERV;                         /*!< 0001: Service Register                                             */
   __IO uint8_t   CMPL;                         /*!< 0002: Compare Low Register                                         */
   __IO uint8_t   CMPH;                         /*!< 0003: Compare High Register                                        */
   __IO uint8_t   CLKCTRL;                      /*!< 0004: Clock Control Register                                       */
   __IO uint8_t   CLKPRESCALER;                 /*!< 0005: Clock Prescaler Register                                     */
} EWM_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'EWM' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- EWM_CTRL                                 ------ */
#define EWM_CTRL_EWMEN_MASK                      (0x01UL << EWM_CTRL_EWMEN_SHIFT)                    /*!< EWM_CTRL: EWMEN Mask                    */
#define EWM_CTRL_EWMEN_SHIFT                     0                                                   /*!< EWM_CTRL: EWMEN Position                */
#define EWM_CTRL_ASSIN_MASK                      (0x01UL << EWM_CTRL_ASSIN_SHIFT)                    /*!< EWM_CTRL: ASSIN Mask                    */
#define EWM_CTRL_ASSIN_SHIFT                     1                                                   /*!< EWM_CTRL: ASSIN Position                */
#define EWM_CTRL_INEN_MASK                       (0x01UL << EWM_CTRL_INEN_SHIFT)                     /*!< EWM_CTRL: INEN Mask                     */
#define EWM_CTRL_INEN_SHIFT                      2                                                   /*!< EWM_CTRL: INEN Position                 */
#define EWM_CTRL_INTEN_MASK                      (0x01UL << EWM_CTRL_INTEN_SHIFT)                    /*!< EWM_CTRL: INTEN Mask                    */
#define EWM_CTRL_INTEN_SHIFT                     3                                                   /*!< EWM_CTRL: INTEN Position                */

/* ------- EWM_SERV                                 ------ */
#define EWM_SERV_SERVICE_MASK                    (0xFFUL << EWM_SERV_SERVICE_SHIFT)                  /*!< EWM_SERV: SERVICE Mask                  */
#define EWM_SERV_SERVICE_SHIFT                   0                                                   /*!< EWM_SERV: SERVICE Position              */
#define EWM_SERV_SERVICE(x)                      (((x)<<EWM_SERV_SERVICE_SHIFT)&EWM_SERV_SERVICE_MASK) /*!< EWM_SERV                                */

/* ------- EWM_CMPL                                 ------ */
#define EWM_CMPL_COMPAREL_MASK                   (0xFFUL << EWM_CMPL_COMPAREL_SHIFT)                 /*!< EWM_CMPL: COMPAREL Mask                 */
#define EWM_CMPL_COMPAREL_SHIFT                  0                                                   /*!< EWM_CMPL: COMPAREL Position             */
#define EWM_CMPL_COMPAREL(x)                     (((x)<<EWM_CMPL_COMPAREL_SHIFT)&EWM_CMPL_COMPAREL_MASK) /*!< EWM_CMPL                                */

/* ------- EWM_CMPH                                 ------ */
#define EWM_CMPH_COMPAREH_MASK                   (0xFFUL << EWM_CMPH_COMPAREH_SHIFT)                 /*!< EWM_CMPH: COMPAREH Mask                 */
#define EWM_CMPH_COMPAREH_SHIFT                  0                                                   /*!< EWM_CMPH: COMPAREH Position             */
#define EWM_CMPH_COMPAREH(x)                     (((x)<<EWM_CMPH_COMPAREH_SHIFT)&EWM_CMPH_COMPAREH_MASK) /*!< EWM_CMPH                                */

/* ------- EWM_CLKCTRL                              ------ */
#define EWM_CLKCTRL_CLKSEL_MASK                  (0x03UL << EWM_CLKCTRL_CLKSEL_SHIFT)                /*!< EWM_CLKCTRL: CLKSEL Mask                */
#define EWM_CLKCTRL_CLKSEL_SHIFT                 0                                                   /*!< EWM_CLKCTRL: CLKSEL Position            */
#define EWM_CLKCTRL_CLKSEL(x)                    (((x)<<EWM_CLKCTRL_CLKSEL_SHIFT)&EWM_CLKCTRL_CLKSEL_MASK) /*!< EWM_CLKCTRL                             */

/* ------- EWM_CLKPRESCALER                         ------ */
#define EWM_CLKPRESCALER_CLK_DIV_MASK            (0xFFUL << EWM_CLKPRESCALER_CLK_DIV_SHIFT)          /*!< EWM_CLKPRESCALER: CLK_DIV Mask          */
#define EWM_CLKPRESCALER_CLK_DIV_SHIFT           0                                                   /*!< EWM_CLKPRESCALER: CLK_DIV Position      */
#define EWM_CLKPRESCALER_CLK_DIV(x)              (((x)<<EWM_CLKPRESCALER_CLK_DIV_SHIFT)&EWM_CLKPRESCALER_CLK_DIV_MASK) /*!< EWM_CLKPRESCALER                        */

/* -------------------------------------------------------------------------------- */
/* -----------     'EWM' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define EWM_CTRL                       (EWM->CTRL)
#define EWM_SERV                       (EWM->SERV)
#define EWM_CMPL                       (EWM->CMPL)
#define EWM_CMPH                       (EWM->CMPH)
#define EWM_CLKCTRL                    (EWM->CLKCTRL)
#define EWM_CLKPRESCALER               (EWM->CLKPRESCALER)

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
   __IO uint8_t   FCCOB3;                       /*!< 0004: Flash Common Command Object Register 3 - Usually Flash address [7..0] */
   __IO uint8_t   FCCOB2;                       /*!< 0005: Flash Common Command Object Register 2 - Usually Flash address [15..8] */
   __IO uint8_t   FCCOB1;                       /*!< 0006: Flash Common Command Object Register 1 - Usually Flash address [23..16] */
   __IO uint8_t   FCCOB0;                       /*!< 0007: Flash Common Command Object Register 0 - Usually FCMD (a code that defines the flash command) */
   __IO uint8_t   FCCOB7;                       /*!< 0008: Flash Common Command Object Register 7 - Usually Data Byte 3 */
   __IO uint8_t   FCCOB6;                       /*!< 0009: Flash Common Command Object Register 6 - Usually Data Byte 2 */
   __IO uint8_t   FCCOB5;                       /*!< 000A: Flash Common Command Object Register 5 - Usually Data Byte 1 */
   __IO uint8_t   FCCOB4;                       /*!< 000B: Flash Common Command Object Register 4 - Usually Data Byte 0 */
   __IO uint8_t   FCCOBB;                       /*!< 000C: Flash Common Command Object Register B - Usually Data Byte 7 */
   __IO uint8_t   FCCOBA;                       /*!< 000D: Flash Common Command Object Register A - Usually Data Byte 6 */
   __IO uint8_t   FCCOB9;                       /*!< 000E: Flash Common Command Object Register 9 - Usually Data Byte 5 */
   __IO uint8_t   FCCOB8;                       /*!< 000F: Flash Common Command Object Register 8 - Usually Data Byte 4 */
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
/* ================           FTM0 (file:FTM0_6CH)                 ================ */
/* ================================================================================ */

/**
 * @brief FlexTimer Module (6 channels)
 */
typedef struct {                                /*!<       FTM0 Structure                                               */
   __IO uint32_t  SC;                           /*!< 0000: Status and Control                                           */
   __IO uint32_t  CNT;                          /*!< 0004: Counter                                                      */
   __IO uint32_t  MOD;                          /*!< 0008: Modulo                                                       */
   struct { /* (cluster) */                     /*!< 000C: (size=0x0030, 48)                                            */
      __IO uint32_t  CnSC;                      /*!< 000C: Channel (%s) Status and Control                              */
      __IO uint32_t  CnV;                       /*!< 0010: Channel (%s) Value                                           */
   } CONTROLS[6];
   __I  uint32_t  RESERVED0[4];                 /*!< 003C:                                                              */
   __IO uint32_t  CNTIN;                        /*!< 004C: Counter Initial Value                                        */
   __I  uint32_t  STATUS;                       /*!< 0050: Capture and Compare Status                                   */
   __IO uint32_t  MODE;                         /*!< 0054: Features Mode Selection                                      */
   __IO uint32_t  SYNC;                         /*!< 0058: Synchronization                                              */
   __IO uint32_t  OUTINIT;                      /*!< 005C: Initial State for Channels Output                            */
   __IO uint32_t  OUTMASK;                      /*!< 0060: Output Mask                                                  */
   __IO uint32_t  COMBINE;                      /*!< 0064: Function for Linked Channels                                 */
   __IO uint32_t  DEADTIME;                     /*!< 0068: Deadtime Insertion Control                                   */
   __IO uint32_t  EXTTRIG;                      /*!< 006C: FTM External Trigger                                         */
   __IO uint32_t  POL;                          /*!< 0070: Channels Polarity                                            */
   __IO uint32_t  FMS;                          /*!< 0074: Fault Mode Status                                            */
   __IO uint32_t  FILTER;                       /*!< 0078: Input Capture Filter Control                                 */
   __IO uint32_t  FLTCTRL;                      /*!< 007C: Fault Control                                                */
   __IO uint32_t  QDCTRL;                       /*!< 0080: Quadrature Decoder Control and Status                        */
   __IO uint32_t  CONF;                         /*!< 0084: Configuration                                                */
   __IO uint32_t  FLTPOL;                       /*!< 0088: FTM Fault Input Polarity                                     */
   __IO uint32_t  SYNCONF;                      /*!< 008C: Synchronization Configuration                                */
   __IO uint32_t  INVCTRL;                      /*!< 0090: FTM Inverting Control                                        */
   __IO uint32_t  SWOCTRL;                      /*!< 0094: FTM Software Output Control                                  */
   __IO uint32_t  PWMLOAD;                      /*!< 0098: FTM PWM Load                                                 */
} FTM0_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'FTM0' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- FTM0_SC                                  ------ */
#define FTM_SC_PS_MASK                           (0x07UL << FTM_SC_PS_SHIFT)                         /*!< FTM0_SC: PS Mask                        */
#define FTM_SC_PS_SHIFT                          0                                                   /*!< FTM0_SC: PS Position                    */
#define FTM_SC_PS(x)                             (((x)<<FTM_SC_PS_SHIFT)&FTM_SC_PS_MASK)             /*!< FTM0_SC                                 */
#define FTM_SC_CLKS_MASK                         (0x03UL << FTM_SC_CLKS_SHIFT)                       /*!< FTM0_SC: CLKS Mask                      */
#define FTM_SC_CLKS_SHIFT                        3                                                   /*!< FTM0_SC: CLKS Position                  */
#define FTM_SC_CLKS(x)                           (((x)<<FTM_SC_CLKS_SHIFT)&FTM_SC_CLKS_MASK)         /*!< FTM0_SC                                 */
#define FTM_SC_CPWMS_MASK                        (0x01UL << FTM_SC_CPWMS_SHIFT)                      /*!< FTM0_SC: CPWMS Mask                     */
#define FTM_SC_CPWMS_SHIFT                       5                                                   /*!< FTM0_SC: CPWMS Position                 */
#define FTM_SC_TOIE_MASK                         (0x01UL << FTM_SC_TOIE_SHIFT)                       /*!< FTM0_SC: TOIE Mask                      */
#define FTM_SC_TOIE_SHIFT                        6                                                   /*!< FTM0_SC: TOIE Position                  */
#define FTM_SC_TOF_MASK                          (0x01UL << FTM_SC_TOF_SHIFT)                        /*!< FTM0_SC: TOF Mask                       */
#define FTM_SC_TOF_SHIFT                         7                                                   /*!< FTM0_SC: TOF Position                   */

/* ------- FTM0_CNT                                 ------ */
#define FTM_CNT_COUNT_MASK                       (0xFFFFUL << FTM_CNT_COUNT_SHIFT)                   /*!< FTM0_CNT: COUNT Mask                    */
#define FTM_CNT_COUNT_SHIFT                      0                                                   /*!< FTM0_CNT: COUNT Position                */
#define FTM_CNT_COUNT(x)                         (((x)<<FTM_CNT_COUNT_SHIFT)&FTM_CNT_COUNT_MASK)     /*!< FTM0_CNT                                */

/* ------- FTM0_MOD                                 ------ */
#define FTM_MOD_MOD_MASK                         (0xFFFFUL << FTM_MOD_MOD_SHIFT)                     /*!< FTM0_MOD: MOD Mask                      */
#define FTM_MOD_MOD_SHIFT                        0                                                   /*!< FTM0_MOD: MOD Position                  */
#define FTM_MOD_MOD(x)                           (((x)<<FTM_MOD_MOD_SHIFT)&FTM_MOD_MOD_MASK)         /*!< FTM0_MOD                                */

/* ------- FTM0_CnSC                                ------ */
#define FTM_CnSC_DMA_MASK                        (0x01UL << FTM_CnSC_DMA_SHIFT)                      /*!< FTM0_CnSC: DMA Mask                     */
#define FTM_CnSC_DMA_SHIFT                       0                                                   /*!< FTM0_CnSC: DMA Position                 */
#define FTM_CnSC_ELSA_MASK                       (0x01UL << FTM_CnSC_ELSA_SHIFT)                     /*!< FTM0_CnSC: ELSA Mask                    */
#define FTM_CnSC_ELSA_SHIFT                      2                                                   /*!< FTM0_CnSC: ELSA Position                */
#define FTM_CnSC_ELSB_MASK                       (0x01UL << FTM_CnSC_ELSB_SHIFT)                     /*!< FTM0_CnSC: ELSB Mask                    */
#define FTM_CnSC_ELSB_SHIFT                      3                                                   /*!< FTM0_CnSC: ELSB Position                */
#define FTM_CnSC_MSA_MASK                        (0x01UL << FTM_CnSC_MSA_SHIFT)                      /*!< FTM0_CnSC: MSA Mask                     */
#define FTM_CnSC_MSA_SHIFT                       4                                                   /*!< FTM0_CnSC: MSA Position                 */
#define FTM_CnSC_MSB_MASK                        (0x01UL << FTM_CnSC_MSB_SHIFT)                      /*!< FTM0_CnSC: MSB Mask                     */
#define FTM_CnSC_MSB_SHIFT                       5                                                   /*!< FTM0_CnSC: MSB Position                 */
#define FTM_CnSC_CHIE_MASK                       (0x01UL << FTM_CnSC_CHIE_SHIFT)                     /*!< FTM0_CnSC: CHIE Mask                    */
#define FTM_CnSC_CHIE_SHIFT                      6                                                   /*!< FTM0_CnSC: CHIE Position                */
#define FTM_CnSC_CHF_MASK                        (0x01UL << FTM_CnSC_CHF_SHIFT)                      /*!< FTM0_CnSC: CHF Mask                     */
#define FTM_CnSC_CHF_SHIFT                       7                                                   /*!< FTM0_CnSC: CHF Position                 */

/* ------- FTM0_CnV                                 ------ */
#define FTM_CnV_VAL_MASK                         (0xFFFFUL << FTM_CnV_VAL_SHIFT)                     /*!< FTM0_CnV: VAL Mask                      */
#define FTM_CnV_VAL_SHIFT                        0                                                   /*!< FTM0_CnV: VAL Position                  */
#define FTM_CnV_VAL(x)                           (((x)<<FTM_CnV_VAL_SHIFT)&FTM_CnV_VAL_MASK)         /*!< FTM0_CnV                                */

/* ------- FTM0_CNTIN                               ------ */
#define FTM_CNTIN_INIT_MASK                      (0xFFFFUL << FTM_CNTIN_INIT_SHIFT)                  /*!< FTM0_CNTIN: INIT Mask                   */
#define FTM_CNTIN_INIT_SHIFT                     0                                                   /*!< FTM0_CNTIN: INIT Position               */
#define FTM_CNTIN_INIT(x)                        (((x)<<FTM_CNTIN_INIT_SHIFT)&FTM_CNTIN_INIT_MASK)   /*!< FTM0_CNTIN                              */

/* ------- FTM0_STATUS                              ------ */
#define FTM_STATUS_CH0F_MASK                     (0x01UL << FTM_STATUS_CH0F_SHIFT)                   /*!< FTM0_STATUS: CH0F Mask                  */
#define FTM_STATUS_CH0F_SHIFT                    0                                                   /*!< FTM0_STATUS: CH0F Position              */
#define FTM_STATUS_CH1F_MASK                     (0x01UL << FTM_STATUS_CH1F_SHIFT)                   /*!< FTM0_STATUS: CH1F Mask                  */
#define FTM_STATUS_CH1F_SHIFT                    1                                                   /*!< FTM0_STATUS: CH1F Position              */
#define FTM_STATUS_CH2F_MASK                     (0x01UL << FTM_STATUS_CH2F_SHIFT)                   /*!< FTM0_STATUS: CH2F Mask                  */
#define FTM_STATUS_CH2F_SHIFT                    2                                                   /*!< FTM0_STATUS: CH2F Position              */
#define FTM_STATUS_CH3F_MASK                     (0x01UL << FTM_STATUS_CH3F_SHIFT)                   /*!< FTM0_STATUS: CH3F Mask                  */
#define FTM_STATUS_CH3F_SHIFT                    3                                                   /*!< FTM0_STATUS: CH3F Position              */
#define FTM_STATUS_CH4F_MASK                     (0x01UL << FTM_STATUS_CH4F_SHIFT)                   /*!< FTM0_STATUS: CH4F Mask                  */
#define FTM_STATUS_CH4F_SHIFT                    4                                                   /*!< FTM0_STATUS: CH4F Position              */
#define FTM_STATUS_CH5F_MASK                     (0x01UL << FTM_STATUS_CH5F_SHIFT)                   /*!< FTM0_STATUS: CH5F Mask                  */
#define FTM_STATUS_CH5F_SHIFT                    5                                                   /*!< FTM0_STATUS: CH5F Position              */
#define FTM_STATUS_CH6F_MASK                     (0x01UL << FTM_STATUS_CH6F_SHIFT)                   /*!< FTM0_STATUS: CH6F Mask                  */
#define FTM_STATUS_CH6F_SHIFT                    6                                                   /*!< FTM0_STATUS: CH6F Position              */
#define FTM_STATUS_CH7F_MASK                     (0x01UL << FTM_STATUS_CH7F_SHIFT)                   /*!< FTM0_STATUS: CH7F Mask                  */
#define FTM_STATUS_CH7F_SHIFT                    7                                                   /*!< FTM0_STATUS: CH7F Position              */

/* ------- FTM0_MODE                                ------ */
#define FTM_MODE_FTMEN_MASK                      (0x01UL << FTM_MODE_FTMEN_SHIFT)                    /*!< FTM0_MODE: FTMEN Mask                   */
#define FTM_MODE_FTMEN_SHIFT                     0                                                   /*!< FTM0_MODE: FTMEN Position               */
#define FTM_MODE_INIT_MASK                       (0x01UL << FTM_MODE_INIT_SHIFT)                     /*!< FTM0_MODE: INIT Mask                    */
#define FTM_MODE_INIT_SHIFT                      1                                                   /*!< FTM0_MODE: INIT Position                */
#define FTM_MODE_WPDIS_MASK                      (0x01UL << FTM_MODE_WPDIS_SHIFT)                    /*!< FTM0_MODE: WPDIS Mask                   */
#define FTM_MODE_WPDIS_SHIFT                     2                                                   /*!< FTM0_MODE: WPDIS Position               */
#define FTM_MODE_PWMSYNC_MASK                    (0x01UL << FTM_MODE_PWMSYNC_SHIFT)                  /*!< FTM0_MODE: PWMSYNC Mask                 */
#define FTM_MODE_PWMSYNC_SHIFT                   3                                                   /*!< FTM0_MODE: PWMSYNC Position             */
#define FTM_MODE_CAPTEST_MASK                    (0x01UL << FTM_MODE_CAPTEST_SHIFT)                  /*!< FTM0_MODE: CAPTEST Mask                 */
#define FTM_MODE_CAPTEST_SHIFT                   4                                                   /*!< FTM0_MODE: CAPTEST Position             */
#define FTM_MODE_FAULTM_MASK                     (0x03UL << FTM_MODE_FAULTM_SHIFT)                   /*!< FTM0_MODE: FAULTM Mask                  */
#define FTM_MODE_FAULTM_SHIFT                    5                                                   /*!< FTM0_MODE: FAULTM Position              */
#define FTM_MODE_FAULTM(x)                       (((x)<<FTM_MODE_FAULTM_SHIFT)&FTM_MODE_FAULTM_MASK) /*!< FTM0_MODE                               */
#define FTM_MODE_FAULTIE_MASK                    (0x01UL << FTM_MODE_FAULTIE_SHIFT)                  /*!< FTM0_MODE: FAULTIE Mask                 */
#define FTM_MODE_FAULTIE_SHIFT                   7                                                   /*!< FTM0_MODE: FAULTIE Position             */

/* ------- FTM0_SYNC                                ------ */
#define FTM_SYNC_CNTMIN_MASK                     (0x01UL << FTM_SYNC_CNTMIN_SHIFT)                   /*!< FTM0_SYNC: CNTMIN Mask                  */
#define FTM_SYNC_CNTMIN_SHIFT                    0                                                   /*!< FTM0_SYNC: CNTMIN Position              */
#define FTM_SYNC_CNTMAX_MASK                     (0x01UL << FTM_SYNC_CNTMAX_SHIFT)                   /*!< FTM0_SYNC: CNTMAX Mask                  */
#define FTM_SYNC_CNTMAX_SHIFT                    1                                                   /*!< FTM0_SYNC: CNTMAX Position              */
#define FTM_SYNC_REINIT_MASK                     (0x01UL << FTM_SYNC_REINIT_SHIFT)                   /*!< FTM0_SYNC: REINIT Mask                  */
#define FTM_SYNC_REINIT_SHIFT                    2                                                   /*!< FTM0_SYNC: REINIT Position              */
#define FTM_SYNC_SYNCHOM_MASK                    (0x01UL << FTM_SYNC_SYNCHOM_SHIFT)                  /*!< FTM0_SYNC: SYNCHOM Mask                 */
#define FTM_SYNC_SYNCHOM_SHIFT                   3                                                   /*!< FTM0_SYNC: SYNCHOM Position             */
#define FTM_SYNC_TRIG0_MASK                      (0x01UL << FTM_SYNC_TRIG0_SHIFT)                    /*!< FTM0_SYNC: TRIG0 Mask                   */
#define FTM_SYNC_TRIG0_SHIFT                     4                                                   /*!< FTM0_SYNC: TRIG0 Position               */
#define FTM_SYNC_TRIG1_MASK                      (0x01UL << FTM_SYNC_TRIG1_SHIFT)                    /*!< FTM0_SYNC: TRIG1 Mask                   */
#define FTM_SYNC_TRIG1_SHIFT                     5                                                   /*!< FTM0_SYNC: TRIG1 Position               */
#define FTM_SYNC_TRIG2_MASK                      (0x01UL << FTM_SYNC_TRIG2_SHIFT)                    /*!< FTM0_SYNC: TRIG2 Mask                   */
#define FTM_SYNC_TRIG2_SHIFT                     6                                                   /*!< FTM0_SYNC: TRIG2 Position               */
#define FTM_SYNC_SWSYNC_MASK                     (0x01UL << FTM_SYNC_SWSYNC_SHIFT)                   /*!< FTM0_SYNC: SWSYNC Mask                  */
#define FTM_SYNC_SWSYNC_SHIFT                    7                                                   /*!< FTM0_SYNC: SWSYNC Position              */

/* ------- FTM0_OUTINIT                             ------ */
#define FTM_OUTINIT_CH0OI_MASK                   (0x01UL << FTM_OUTINIT_CH0OI_SHIFT)                 /*!< FTM0_OUTINIT: CH0OI Mask                */
#define FTM_OUTINIT_CH0OI_SHIFT                  0                                                   /*!< FTM0_OUTINIT: CH0OI Position            */
#define FTM_OUTINIT_CH1OI_MASK                   (0x01UL << FTM_OUTINIT_CH1OI_SHIFT)                 /*!< FTM0_OUTINIT: CH1OI Mask                */
#define FTM_OUTINIT_CH1OI_SHIFT                  1                                                   /*!< FTM0_OUTINIT: CH1OI Position            */
#define FTM_OUTINIT_CH2OI_MASK                   (0x01UL << FTM_OUTINIT_CH2OI_SHIFT)                 /*!< FTM0_OUTINIT: CH2OI Mask                */
#define FTM_OUTINIT_CH2OI_SHIFT                  2                                                   /*!< FTM0_OUTINIT: CH2OI Position            */
#define FTM_OUTINIT_CH3OI_MASK                   (0x01UL << FTM_OUTINIT_CH3OI_SHIFT)                 /*!< FTM0_OUTINIT: CH3OI Mask                */
#define FTM_OUTINIT_CH3OI_SHIFT                  3                                                   /*!< FTM0_OUTINIT: CH3OI Position            */
#define FTM_OUTINIT_CH4OI_MASK                   (0x01UL << FTM_OUTINIT_CH4OI_SHIFT)                 /*!< FTM0_OUTINIT: CH4OI Mask                */
#define FTM_OUTINIT_CH4OI_SHIFT                  4                                                   /*!< FTM0_OUTINIT: CH4OI Position            */
#define FTM_OUTINIT_CH5OI_MASK                   (0x01UL << FTM_OUTINIT_CH5OI_SHIFT)                 /*!< FTM0_OUTINIT: CH5OI Mask                */
#define FTM_OUTINIT_CH5OI_SHIFT                  5                                                   /*!< FTM0_OUTINIT: CH5OI Position            */
#define FTM_OUTINIT_CH6OI_MASK                   (0x01UL << FTM_OUTINIT_CH6OI_SHIFT)                 /*!< FTM0_OUTINIT: CH6OI Mask                */
#define FTM_OUTINIT_CH6OI_SHIFT                  6                                                   /*!< FTM0_OUTINIT: CH6OI Position            */
#define FTM_OUTINIT_CH7OI_MASK                   (0x01UL << FTM_OUTINIT_CH7OI_SHIFT)                 /*!< FTM0_OUTINIT: CH7OI Mask                */
#define FTM_OUTINIT_CH7OI_SHIFT                  7                                                   /*!< FTM0_OUTINIT: CH7OI Position            */

/* ------- FTM0_OUTMASK                             ------ */
#define FTM_OUTMASK_CH0OM_MASK                   (0x01UL << FTM_OUTMASK_CH0OM_SHIFT)                 /*!< FTM0_OUTMASK: CH0OM Mask                */
#define FTM_OUTMASK_CH0OM_SHIFT                  0                                                   /*!< FTM0_OUTMASK: CH0OM Position            */
#define FTM_OUTMASK_CH1OM_MASK                   (0x01UL << FTM_OUTMASK_CH1OM_SHIFT)                 /*!< FTM0_OUTMASK: CH1OM Mask                */
#define FTM_OUTMASK_CH1OM_SHIFT                  1                                                   /*!< FTM0_OUTMASK: CH1OM Position            */
#define FTM_OUTMASK_CH2OM_MASK                   (0x01UL << FTM_OUTMASK_CH2OM_SHIFT)                 /*!< FTM0_OUTMASK: CH2OM Mask                */
#define FTM_OUTMASK_CH2OM_SHIFT                  2                                                   /*!< FTM0_OUTMASK: CH2OM Position            */
#define FTM_OUTMASK_CH3OM_MASK                   (0x01UL << FTM_OUTMASK_CH3OM_SHIFT)                 /*!< FTM0_OUTMASK: CH3OM Mask                */
#define FTM_OUTMASK_CH3OM_SHIFT                  3                                                   /*!< FTM0_OUTMASK: CH3OM Position            */
#define FTM_OUTMASK_CH4OM_MASK                   (0x01UL << FTM_OUTMASK_CH4OM_SHIFT)                 /*!< FTM0_OUTMASK: CH4OM Mask                */
#define FTM_OUTMASK_CH4OM_SHIFT                  4                                                   /*!< FTM0_OUTMASK: CH4OM Position            */
#define FTM_OUTMASK_CH5OM_MASK                   (0x01UL << FTM_OUTMASK_CH5OM_SHIFT)                 /*!< FTM0_OUTMASK: CH5OM Mask                */
#define FTM_OUTMASK_CH5OM_SHIFT                  5                                                   /*!< FTM0_OUTMASK: CH5OM Position            */
#define FTM_OUTMASK_CH6OM_MASK                   (0x01UL << FTM_OUTMASK_CH6OM_SHIFT)                 /*!< FTM0_OUTMASK: CH6OM Mask                */
#define FTM_OUTMASK_CH6OM_SHIFT                  6                                                   /*!< FTM0_OUTMASK: CH6OM Position            */
#define FTM_OUTMASK_CH7OM_MASK                   (0x01UL << FTM_OUTMASK_CH7OM_SHIFT)                 /*!< FTM0_OUTMASK: CH7OM Mask                */
#define FTM_OUTMASK_CH7OM_SHIFT                  7                                                   /*!< FTM0_OUTMASK: CH7OM Position            */

/* ------- FTM0_COMBINE                             ------ */
#define FTM_COMBINE_COMBINE0_MASK                (0x01UL << FTM_COMBINE_COMBINE0_SHIFT)              /*!< FTM0_COMBINE: COMBINE0 Mask             */
#define FTM_COMBINE_COMBINE0_SHIFT               0                                                   /*!< FTM0_COMBINE: COMBINE0 Position         */
#define FTM_COMBINE_COMP0_MASK                   (0x01UL << FTM_COMBINE_COMP0_SHIFT)                 /*!< FTM0_COMBINE: COMP0 Mask                */
#define FTM_COMBINE_COMP0_SHIFT                  1                                                   /*!< FTM0_COMBINE: COMP0 Position            */
#define FTM_COMBINE_DECAPEN0_MASK                (0x01UL << FTM_COMBINE_DECAPEN0_SHIFT)              /*!< FTM0_COMBINE: DECAPEN0 Mask             */
#define FTM_COMBINE_DECAPEN0_SHIFT               2                                                   /*!< FTM0_COMBINE: DECAPEN0 Position         */
#define FTM_COMBINE_DECAP0_MASK                  (0x01UL << FTM_COMBINE_DECAP0_SHIFT)                /*!< FTM0_COMBINE: DECAP0 Mask               */
#define FTM_COMBINE_DECAP0_SHIFT                 3                                                   /*!< FTM0_COMBINE: DECAP0 Position           */
#define FTM_COMBINE_DTEN0_MASK                   (0x01UL << FTM_COMBINE_DTEN0_SHIFT)                 /*!< FTM0_COMBINE: DTEN0 Mask                */
#define FTM_COMBINE_DTEN0_SHIFT                  4                                                   /*!< FTM0_COMBINE: DTEN0 Position            */
#define FTM_COMBINE_SYNCEN0_MASK                 (0x01UL << FTM_COMBINE_SYNCEN0_SHIFT)               /*!< FTM0_COMBINE: SYNCEN0 Mask              */
#define FTM_COMBINE_SYNCEN0_SHIFT                5                                                   /*!< FTM0_COMBINE: SYNCEN0 Position          */
#define FTM_COMBINE_FAULTEN0_MASK                (0x01UL << FTM_COMBINE_FAULTEN0_SHIFT)              /*!< FTM0_COMBINE: FAULTEN0 Mask             */
#define FTM_COMBINE_FAULTEN0_SHIFT               6                                                   /*!< FTM0_COMBINE: FAULTEN0 Position         */
#define FTM_COMBINE_COMBINE1_MASK                (0x01UL << FTM_COMBINE_COMBINE1_SHIFT)              /*!< FTM0_COMBINE: COMBINE1 Mask             */
#define FTM_COMBINE_COMBINE1_SHIFT               8                                                   /*!< FTM0_COMBINE: COMBINE1 Position         */
#define FTM_COMBINE_COMP1_MASK                   (0x01UL << FTM_COMBINE_COMP1_SHIFT)                 /*!< FTM0_COMBINE: COMP1 Mask                */
#define FTM_COMBINE_COMP1_SHIFT                  9                                                   /*!< FTM0_COMBINE: COMP1 Position            */
#define FTM_COMBINE_DECAPEN1_MASK                (0x01UL << FTM_COMBINE_DECAPEN1_SHIFT)              /*!< FTM0_COMBINE: DECAPEN1 Mask             */
#define FTM_COMBINE_DECAPEN1_SHIFT               10                                                  /*!< FTM0_COMBINE: DECAPEN1 Position         */
#define FTM_COMBINE_DECAP1_MASK                  (0x01UL << FTM_COMBINE_DECAP1_SHIFT)                /*!< FTM0_COMBINE: DECAP1 Mask               */
#define FTM_COMBINE_DECAP1_SHIFT                 11                                                  /*!< FTM0_COMBINE: DECAP1 Position           */
#define FTM_COMBINE_DTEN1_MASK                   (0x01UL << FTM_COMBINE_DTEN1_SHIFT)                 /*!< FTM0_COMBINE: DTEN1 Mask                */
#define FTM_COMBINE_DTEN1_SHIFT                  12                                                  /*!< FTM0_COMBINE: DTEN1 Position            */
#define FTM_COMBINE_SYNCEN1_MASK                 (0x01UL << FTM_COMBINE_SYNCEN1_SHIFT)               /*!< FTM0_COMBINE: SYNCEN1 Mask              */
#define FTM_COMBINE_SYNCEN1_SHIFT                13                                                  /*!< FTM0_COMBINE: SYNCEN1 Position          */
#define FTM_COMBINE_FAULTEN1_MASK                (0x01UL << FTM_COMBINE_FAULTEN1_SHIFT)              /*!< FTM0_COMBINE: FAULTEN1 Mask             */
#define FTM_COMBINE_FAULTEN1_SHIFT               14                                                  /*!< FTM0_COMBINE: FAULTEN1 Position         */
#define FTM_COMBINE_COMBINE2_MASK                (0x01UL << FTM_COMBINE_COMBINE2_SHIFT)              /*!< FTM0_COMBINE: COMBINE2 Mask             */
#define FTM_COMBINE_COMBINE2_SHIFT               16                                                  /*!< FTM0_COMBINE: COMBINE2 Position         */
#define FTM_COMBINE_COMP2_MASK                   (0x01UL << FTM_COMBINE_COMP2_SHIFT)                 /*!< FTM0_COMBINE: COMP2 Mask                */
#define FTM_COMBINE_COMP2_SHIFT                  17                                                  /*!< FTM0_COMBINE: COMP2 Position            */
#define FTM_COMBINE_DECAPEN2_MASK                (0x01UL << FTM_COMBINE_DECAPEN2_SHIFT)              /*!< FTM0_COMBINE: DECAPEN2 Mask             */
#define FTM_COMBINE_DECAPEN2_SHIFT               18                                                  /*!< FTM0_COMBINE: DECAPEN2 Position         */
#define FTM_COMBINE_DECAP2_MASK                  (0x01UL << FTM_COMBINE_DECAP2_SHIFT)                /*!< FTM0_COMBINE: DECAP2 Mask               */
#define FTM_COMBINE_DECAP2_SHIFT                 19                                                  /*!< FTM0_COMBINE: DECAP2 Position           */
#define FTM_COMBINE_DTEN2_MASK                   (0x01UL << FTM_COMBINE_DTEN2_SHIFT)                 /*!< FTM0_COMBINE: DTEN2 Mask                */
#define FTM_COMBINE_DTEN2_SHIFT                  20                                                  /*!< FTM0_COMBINE: DTEN2 Position            */
#define FTM_COMBINE_SYNCEN2_MASK                 (0x01UL << FTM_COMBINE_SYNCEN2_SHIFT)               /*!< FTM0_COMBINE: SYNCEN2 Mask              */
#define FTM_COMBINE_SYNCEN2_SHIFT                21                                                  /*!< FTM0_COMBINE: SYNCEN2 Position          */
#define FTM_COMBINE_FAULTEN2_MASK                (0x01UL << FTM_COMBINE_FAULTEN2_SHIFT)              /*!< FTM0_COMBINE: FAULTEN2 Mask             */
#define FTM_COMBINE_FAULTEN2_SHIFT               22                                                  /*!< FTM0_COMBINE: FAULTEN2 Position         */
#define FTM_COMBINE_COMBINE3_MASK                (0x01UL << FTM_COMBINE_COMBINE3_SHIFT)              /*!< FTM0_COMBINE: COMBINE3 Mask             */
#define FTM_COMBINE_COMBINE3_SHIFT               24                                                  /*!< FTM0_COMBINE: COMBINE3 Position         */
#define FTM_COMBINE_COMP3_MASK                   (0x01UL << FTM_COMBINE_COMP3_SHIFT)                 /*!< FTM0_COMBINE: COMP3 Mask                */
#define FTM_COMBINE_COMP3_SHIFT                  25                                                  /*!< FTM0_COMBINE: COMP3 Position            */
#define FTM_COMBINE_DECAPEN3_MASK                (0x01UL << FTM_COMBINE_DECAPEN3_SHIFT)              /*!< FTM0_COMBINE: DECAPEN3 Mask             */
#define FTM_COMBINE_DECAPEN3_SHIFT               26                                                  /*!< FTM0_COMBINE: DECAPEN3 Position         */
#define FTM_COMBINE_DECAP3_MASK                  (0x01UL << FTM_COMBINE_DECAP3_SHIFT)                /*!< FTM0_COMBINE: DECAP3 Mask               */
#define FTM_COMBINE_DECAP3_SHIFT                 27                                                  /*!< FTM0_COMBINE: DECAP3 Position           */
#define FTM_COMBINE_DTEN3_MASK                   (0x01UL << FTM_COMBINE_DTEN3_SHIFT)                 /*!< FTM0_COMBINE: DTEN3 Mask                */
#define FTM_COMBINE_DTEN3_SHIFT                  28                                                  /*!< FTM0_COMBINE: DTEN3 Position            */
#define FTM_COMBINE_SYNCEN3_MASK                 (0x01UL << FTM_COMBINE_SYNCEN3_SHIFT)               /*!< FTM0_COMBINE: SYNCEN3 Mask              */
#define FTM_COMBINE_SYNCEN3_SHIFT                29                                                  /*!< FTM0_COMBINE: SYNCEN3 Position          */
#define FTM_COMBINE_FAULTEN3_MASK                (0x01UL << FTM_COMBINE_FAULTEN3_SHIFT)              /*!< FTM0_COMBINE: FAULTEN3 Mask             */
#define FTM_COMBINE_FAULTEN3_SHIFT               30                                                  /*!< FTM0_COMBINE: FAULTEN3 Position         */

/* ------- FTM0_DEADTIME                            ------ */
#define FTM_DEADTIME_DTVAL_MASK                  (0x3FUL << FTM_DEADTIME_DTVAL_SHIFT)                /*!< FTM0_DEADTIME: DTVAL Mask               */
#define FTM_DEADTIME_DTVAL_SHIFT                 0                                                   /*!< FTM0_DEADTIME: DTVAL Position           */
#define FTM_DEADTIME_DTVAL(x)                    (((x)<<FTM_DEADTIME_DTVAL_SHIFT)&FTM_DEADTIME_DTVAL_MASK) /*!< FTM0_DEADTIME                           */
#define FTM_DEADTIME_DTPS_MASK                   (0x03UL << FTM_DEADTIME_DTPS_SHIFT)                 /*!< FTM0_DEADTIME: DTPS Mask                */
#define FTM_DEADTIME_DTPS_SHIFT                  6                                                   /*!< FTM0_DEADTIME: DTPS Position            */
#define FTM_DEADTIME_DTPS(x)                     (((x)<<FTM_DEADTIME_DTPS_SHIFT)&FTM_DEADTIME_DTPS_MASK) /*!< FTM0_DEADTIME                           */

/* ------- FTM0_EXTTRIG                             ------ */
#define FTM_EXTTRIG_CH2TRIG_MASK                 (0x01UL << FTM_EXTTRIG_CH2TRIG_SHIFT)               /*!< FTM0_EXTTRIG: CH2TRIG Mask              */
#define FTM_EXTTRIG_CH2TRIG_SHIFT                0                                                   /*!< FTM0_EXTTRIG: CH2TRIG Position          */
#define FTM_EXTTRIG_CH3TRIG_MASK                 (0x01UL << FTM_EXTTRIG_CH3TRIG_SHIFT)               /*!< FTM0_EXTTRIG: CH3TRIG Mask              */
#define FTM_EXTTRIG_CH3TRIG_SHIFT                1                                                   /*!< FTM0_EXTTRIG: CH3TRIG Position          */
#define FTM_EXTTRIG_CH4TRIG_MASK                 (0x01UL << FTM_EXTTRIG_CH4TRIG_SHIFT)               /*!< FTM0_EXTTRIG: CH4TRIG Mask              */
#define FTM_EXTTRIG_CH4TRIG_SHIFT                2                                                   /*!< FTM0_EXTTRIG: CH4TRIG Position          */
#define FTM_EXTTRIG_CH5TRIG_MASK                 (0x01UL << FTM_EXTTRIG_CH5TRIG_SHIFT)               /*!< FTM0_EXTTRIG: CH5TRIG Mask              */
#define FTM_EXTTRIG_CH5TRIG_SHIFT                3                                                   /*!< FTM0_EXTTRIG: CH5TRIG Position          */
#define FTM_EXTTRIG_CH0TRIG_MASK                 (0x01UL << FTM_EXTTRIG_CH0TRIG_SHIFT)               /*!< FTM0_EXTTRIG: CH0TRIG Mask              */
#define FTM_EXTTRIG_CH0TRIG_SHIFT                4                                                   /*!< FTM0_EXTTRIG: CH0TRIG Position          */
#define FTM_EXTTRIG_CH1TRIG_MASK                 (0x01UL << FTM_EXTTRIG_CH1TRIG_SHIFT)               /*!< FTM0_EXTTRIG: CH1TRIG Mask              */
#define FTM_EXTTRIG_CH1TRIG_SHIFT                5                                                   /*!< FTM0_EXTTRIG: CH1TRIG Position          */
#define FTM_EXTTRIG_INITTRIGEN_MASK              (0x01UL << FTM_EXTTRIG_INITTRIGEN_SHIFT)            /*!< FTM0_EXTTRIG: INITTRIGEN Mask           */
#define FTM_EXTTRIG_INITTRIGEN_SHIFT             6                                                   /*!< FTM0_EXTTRIG: INITTRIGEN Position       */
#define FTM_EXTTRIG_TRIGF_MASK                   (0x01UL << FTM_EXTTRIG_TRIGF_SHIFT)                 /*!< FTM0_EXTTRIG: TRIGF Mask                */
#define FTM_EXTTRIG_TRIGF_SHIFT                  7                                                   /*!< FTM0_EXTTRIG: TRIGF Position            */

/* ------- FTM0_POL                                 ------ */
#define FTM_POL_POL0_MASK                        (0x01UL << FTM_POL_POL0_SHIFT)                      /*!< FTM0_POL: POL0 Mask                     */
#define FTM_POL_POL0_SHIFT                       0                                                   /*!< FTM0_POL: POL0 Position                 */
#define FTM_POL_POL1_MASK                        (0x01UL << FTM_POL_POL1_SHIFT)                      /*!< FTM0_POL: POL1 Mask                     */
#define FTM_POL_POL1_SHIFT                       1                                                   /*!< FTM0_POL: POL1 Position                 */
#define FTM_POL_POL2_MASK                        (0x01UL << FTM_POL_POL2_SHIFT)                      /*!< FTM0_POL: POL2 Mask                     */
#define FTM_POL_POL2_SHIFT                       2                                                   /*!< FTM0_POL: POL2 Position                 */
#define FTM_POL_POL3_MASK                        (0x01UL << FTM_POL_POL3_SHIFT)                      /*!< FTM0_POL: POL3 Mask                     */
#define FTM_POL_POL3_SHIFT                       3                                                   /*!< FTM0_POL: POL3 Position                 */
#define FTM_POL_POL4_MASK                        (0x01UL << FTM_POL_POL4_SHIFT)                      /*!< FTM0_POL: POL4 Mask                     */
#define FTM_POL_POL4_SHIFT                       4                                                   /*!< FTM0_POL: POL4 Position                 */
#define FTM_POL_POL5_MASK                        (0x01UL << FTM_POL_POL5_SHIFT)                      /*!< FTM0_POL: POL5 Mask                     */
#define FTM_POL_POL5_SHIFT                       5                                                   /*!< FTM0_POL: POL5 Position                 */
#define FTM_POL_POL6_MASK                        (0x01UL << FTM_POL_POL6_SHIFT)                      /*!< FTM0_POL: POL6 Mask                     */
#define FTM_POL_POL6_SHIFT                       6                                                   /*!< FTM0_POL: POL6 Position                 */
#define FTM_POL_POL7_MASK                        (0x01UL << FTM_POL_POL7_SHIFT)                      /*!< FTM0_POL: POL7 Mask                     */
#define FTM_POL_POL7_SHIFT                       7                                                   /*!< FTM0_POL: POL7 Position                 */

/* ------- FTM0_FMS                                 ------ */
#define FTM_FMS_FAULTF0_MASK                     (0x01UL << FTM_FMS_FAULTF0_SHIFT)                   /*!< FTM0_FMS: FAULTF0 Mask                  */
#define FTM_FMS_FAULTF0_SHIFT                    0                                                   /*!< FTM0_FMS: FAULTF0 Position              */
#define FTM_FMS_FAULTF1_MASK                     (0x01UL << FTM_FMS_FAULTF1_SHIFT)                   /*!< FTM0_FMS: FAULTF1 Mask                  */
#define FTM_FMS_FAULTF1_SHIFT                    1                                                   /*!< FTM0_FMS: FAULTF1 Position              */
#define FTM_FMS_FAULTF2_MASK                     (0x01UL << FTM_FMS_FAULTF2_SHIFT)                   /*!< FTM0_FMS: FAULTF2 Mask                  */
#define FTM_FMS_FAULTF2_SHIFT                    2                                                   /*!< FTM0_FMS: FAULTF2 Position              */
#define FTM_FMS_FAULTF3_MASK                     (0x01UL << FTM_FMS_FAULTF3_SHIFT)                   /*!< FTM0_FMS: FAULTF3 Mask                  */
#define FTM_FMS_FAULTF3_SHIFT                    3                                                   /*!< FTM0_FMS: FAULTF3 Position              */
#define FTM_FMS_FAULTIN_MASK                     (0x01UL << FTM_FMS_FAULTIN_SHIFT)                   /*!< FTM0_FMS: FAULTIN Mask                  */
#define FTM_FMS_FAULTIN_SHIFT                    5                                                   /*!< FTM0_FMS: FAULTIN Position              */
#define FTM_FMS_WPEN_MASK                        (0x01UL << FTM_FMS_WPEN_SHIFT)                      /*!< FTM0_FMS: WPEN Mask                     */
#define FTM_FMS_WPEN_SHIFT                       6                                                   /*!< FTM0_FMS: WPEN Position                 */
#define FTM_FMS_FAULTF_MASK                      (0x01UL << FTM_FMS_FAULTF_SHIFT)                    /*!< FTM0_FMS: FAULTF Mask                   */
#define FTM_FMS_FAULTF_SHIFT                     7                                                   /*!< FTM0_FMS: FAULTF Position               */

/* ------- FTM0_FILTER                              ------ */
#define FTM_FILTER_CH0FVAL_MASK                  (0x0FUL << FTM_FILTER_CH0FVAL_SHIFT)                /*!< FTM0_FILTER: CH0FVAL Mask               */
#define FTM_FILTER_CH0FVAL_SHIFT                 0                                                   /*!< FTM0_FILTER: CH0FVAL Position           */
#define FTM_FILTER_CH0FVAL(x)                    (((x)<<FTM_FILTER_CH0FVAL_SHIFT)&FTM_FILTER_CH0FVAL_MASK) /*!< FTM0_FILTER                             */
#define FTM_FILTER_CH1FVAL_MASK                  (0x0FUL << FTM_FILTER_CH1FVAL_SHIFT)                /*!< FTM0_FILTER: CH1FVAL Mask               */
#define FTM_FILTER_CH1FVAL_SHIFT                 4                                                   /*!< FTM0_FILTER: CH1FVAL Position           */
#define FTM_FILTER_CH1FVAL(x)                    (((x)<<FTM_FILTER_CH1FVAL_SHIFT)&FTM_FILTER_CH1FVAL_MASK) /*!< FTM0_FILTER                             */
#define FTM_FILTER_CH2FVAL_MASK                  (0x0FUL << FTM_FILTER_CH2FVAL_SHIFT)                /*!< FTM0_FILTER: CH2FVAL Mask               */
#define FTM_FILTER_CH2FVAL_SHIFT                 8                                                   /*!< FTM0_FILTER: CH2FVAL Position           */
#define FTM_FILTER_CH2FVAL(x)                    (((x)<<FTM_FILTER_CH2FVAL_SHIFT)&FTM_FILTER_CH2FVAL_MASK) /*!< FTM0_FILTER                             */
#define FTM_FILTER_CH3FVAL_MASK                  (0x0FUL << FTM_FILTER_CH3FVAL_SHIFT)                /*!< FTM0_FILTER: CH3FVAL Mask               */
#define FTM_FILTER_CH3FVAL_SHIFT                 12                                                  /*!< FTM0_FILTER: CH3FVAL Position           */
#define FTM_FILTER_CH3FVAL(x)                    (((x)<<FTM_FILTER_CH3FVAL_SHIFT)&FTM_FILTER_CH3FVAL_MASK) /*!< FTM0_FILTER                             */

/* ------- FTM0_FLTCTRL                             ------ */
#define FTM_FLTCTRL_FAULT0EN_MASK                (0x01UL << FTM_FLTCTRL_FAULT0EN_SHIFT)              /*!< FTM0_FLTCTRL: FAULT0EN Mask             */
#define FTM_FLTCTRL_FAULT0EN_SHIFT               0                                                   /*!< FTM0_FLTCTRL: FAULT0EN Position         */
#define FTM_FLTCTRL_FAULT1EN_MASK                (0x01UL << FTM_FLTCTRL_FAULT1EN_SHIFT)              /*!< FTM0_FLTCTRL: FAULT1EN Mask             */
#define FTM_FLTCTRL_FAULT1EN_SHIFT               1                                                   /*!< FTM0_FLTCTRL: FAULT1EN Position         */
#define FTM_FLTCTRL_FAULT2EN_MASK                (0x01UL << FTM_FLTCTRL_FAULT2EN_SHIFT)              /*!< FTM0_FLTCTRL: FAULT2EN Mask             */
#define FTM_FLTCTRL_FAULT2EN_SHIFT               2                                                   /*!< FTM0_FLTCTRL: FAULT2EN Position         */
#define FTM_FLTCTRL_FAULT3EN_MASK                (0x01UL << FTM_FLTCTRL_FAULT3EN_SHIFT)              /*!< FTM0_FLTCTRL: FAULT3EN Mask             */
#define FTM_FLTCTRL_FAULT3EN_SHIFT               3                                                   /*!< FTM0_FLTCTRL: FAULT3EN Position         */
#define FTM_FLTCTRL_FFLTR0EN_MASK                (0x01UL << FTM_FLTCTRL_FFLTR0EN_SHIFT)              /*!< FTM0_FLTCTRL: FFLTR0EN Mask             */
#define FTM_FLTCTRL_FFLTR0EN_SHIFT               4                                                   /*!< FTM0_FLTCTRL: FFLTR0EN Position         */
#define FTM_FLTCTRL_FFLTR1EN_MASK                (0x01UL << FTM_FLTCTRL_FFLTR1EN_SHIFT)              /*!< FTM0_FLTCTRL: FFLTR1EN Mask             */
#define FTM_FLTCTRL_FFLTR1EN_SHIFT               5                                                   /*!< FTM0_FLTCTRL: FFLTR1EN Position         */
#define FTM_FLTCTRL_FFLTR2EN_MASK                (0x01UL << FTM_FLTCTRL_FFLTR2EN_SHIFT)              /*!< FTM0_FLTCTRL: FFLTR2EN Mask             */
#define FTM_FLTCTRL_FFLTR2EN_SHIFT               6                                                   /*!< FTM0_FLTCTRL: FFLTR2EN Position         */
#define FTM_FLTCTRL_FFLTR3EN_MASK                (0x01UL << FTM_FLTCTRL_FFLTR3EN_SHIFT)              /*!< FTM0_FLTCTRL: FFLTR3EN Mask             */
#define FTM_FLTCTRL_FFLTR3EN_SHIFT               7                                                   /*!< FTM0_FLTCTRL: FFLTR3EN Position         */
#define FTM_FLTCTRL_FFVAL_MASK                   (0x0FUL << FTM_FLTCTRL_FFVAL_SHIFT)                 /*!< FTM0_FLTCTRL: FFVAL Mask                */
#define FTM_FLTCTRL_FFVAL_SHIFT                  8                                                   /*!< FTM0_FLTCTRL: FFVAL Position            */
#define FTM_FLTCTRL_FFVAL(x)                     (((x)<<FTM_FLTCTRL_FFVAL_SHIFT)&FTM_FLTCTRL_FFVAL_MASK) /*!< FTM0_FLTCTRL                            */

/* ------- FTM0_QDCTRL                              ------ */
#define FTM_QDCTRL_QUADEN_MASK                   (0x01UL << FTM_QDCTRL_QUADEN_SHIFT)                 /*!< FTM0_QDCTRL: QUADEN Mask                */
#define FTM_QDCTRL_QUADEN_SHIFT                  0                                                   /*!< FTM0_QDCTRL: QUADEN Position            */
#define FTM_QDCTRL_TOFDIR_MASK                   (0x01UL << FTM_QDCTRL_TOFDIR_SHIFT)                 /*!< FTM0_QDCTRL: TOFDIR Mask                */
#define FTM_QDCTRL_TOFDIR_SHIFT                  1                                                   /*!< FTM0_QDCTRL: TOFDIR Position            */
#define FTM_QDCTRL_QUADIR_MASK                   (0x01UL << FTM_QDCTRL_QUADIR_SHIFT)                 /*!< FTM0_QDCTRL: QUADIR Mask                */
#define FTM_QDCTRL_QUADIR_SHIFT                  2                                                   /*!< FTM0_QDCTRL: QUADIR Position            */
#define FTM_QDCTRL_QUADMODE_MASK                 (0x01UL << FTM_QDCTRL_QUADMODE_SHIFT)               /*!< FTM0_QDCTRL: QUADMODE Mask              */
#define FTM_QDCTRL_QUADMODE_SHIFT                3                                                   /*!< FTM0_QDCTRL: QUADMODE Position          */
#define FTM_QDCTRL_PHBPOL_MASK                   (0x01UL << FTM_QDCTRL_PHBPOL_SHIFT)                 /*!< FTM0_QDCTRL: PHBPOL Mask                */
#define FTM_QDCTRL_PHBPOL_SHIFT                  4                                                   /*!< FTM0_QDCTRL: PHBPOL Position            */
#define FTM_QDCTRL_PHAPOL_MASK                   (0x01UL << FTM_QDCTRL_PHAPOL_SHIFT)                 /*!< FTM0_QDCTRL: PHAPOL Mask                */
#define FTM_QDCTRL_PHAPOL_SHIFT                  5                                                   /*!< FTM0_QDCTRL: PHAPOL Position            */
#define FTM_QDCTRL_PHBFLTREN_MASK                (0x01UL << FTM_QDCTRL_PHBFLTREN_SHIFT)              /*!< FTM0_QDCTRL: PHBFLTREN Mask             */
#define FTM_QDCTRL_PHBFLTREN_SHIFT               6                                                   /*!< FTM0_QDCTRL: PHBFLTREN Position         */
#define FTM_QDCTRL_PHAFLTREN_MASK                (0x01UL << FTM_QDCTRL_PHAFLTREN_SHIFT)              /*!< FTM0_QDCTRL: PHAFLTREN Mask             */
#define FTM_QDCTRL_PHAFLTREN_SHIFT               7                                                   /*!< FTM0_QDCTRL: PHAFLTREN Position         */

/* ------- FTM0_CONF                                ------ */
#define FTM_CONF_NUMTOF_MASK                     (0x1FUL << FTM_CONF_NUMTOF_SHIFT)                   /*!< FTM0_CONF: NUMTOF Mask                  */
#define FTM_CONF_NUMTOF_SHIFT                    0                                                   /*!< FTM0_CONF: NUMTOF Position              */
#define FTM_CONF_NUMTOF(x)                       (((x)<<FTM_CONF_NUMTOF_SHIFT)&FTM_CONF_NUMTOF_MASK) /*!< FTM0_CONF                               */
#define FTM_CONF_BDMMODE_MASK                    (0x03UL << FTM_CONF_BDMMODE_SHIFT)                  /*!< FTM0_CONF: BDMMODE Mask                 */
#define FTM_CONF_BDMMODE_SHIFT                   6                                                   /*!< FTM0_CONF: BDMMODE Position             */
#define FTM_CONF_BDMMODE(x)                      (((x)<<FTM_CONF_BDMMODE_SHIFT)&FTM_CONF_BDMMODE_MASK) /*!< FTM0_CONF                               */
#define FTM_CONF_GTBEEN_MASK                     (0x01UL << FTM_CONF_GTBEEN_SHIFT)                   /*!< FTM0_CONF: GTBEEN Mask                  */
#define FTM_CONF_GTBEEN_SHIFT                    9                                                   /*!< FTM0_CONF: GTBEEN Position              */
#define FTM_CONF_GTBEOUT_MASK                    (0x01UL << FTM_CONF_GTBEOUT_SHIFT)                  /*!< FTM0_CONF: GTBEOUT Mask                 */
#define FTM_CONF_GTBEOUT_SHIFT                   10                                                  /*!< FTM0_CONF: GTBEOUT Position             */

/* ------- FTM0_FLTPOL                              ------ */
#define FTM_FLTPOL_FLT0POL_MASK                  (0x01UL << FTM_FLTPOL_FLT0POL_SHIFT)                /*!< FTM0_FLTPOL: FLT0POL Mask               */
#define FTM_FLTPOL_FLT0POL_SHIFT                 0                                                   /*!< FTM0_FLTPOL: FLT0POL Position           */
#define FTM_FLTPOL_FLT1POL_MASK                  (0x01UL << FTM_FLTPOL_FLT1POL_SHIFT)                /*!< FTM0_FLTPOL: FLT1POL Mask               */
#define FTM_FLTPOL_FLT1POL_SHIFT                 1                                                   /*!< FTM0_FLTPOL: FLT1POL Position           */
#define FTM_FLTPOL_FLT2POL_MASK                  (0x01UL << FTM_FLTPOL_FLT2POL_SHIFT)                /*!< FTM0_FLTPOL: FLT2POL Mask               */
#define FTM_FLTPOL_FLT2POL_SHIFT                 2                                                   /*!< FTM0_FLTPOL: FLT2POL Position           */
#define FTM_FLTPOL_FLT3POL_MASK                  (0x01UL << FTM_FLTPOL_FLT3POL_SHIFT)                /*!< FTM0_FLTPOL: FLT3POL Mask               */
#define FTM_FLTPOL_FLT3POL_SHIFT                 3                                                   /*!< FTM0_FLTPOL: FLT3POL Position           */

/* ------- FTM0_SYNCONF                             ------ */
#define FTM_SYNCONF_HWTRIGMODE_MASK              (0x01UL << FTM_SYNCONF_HWTRIGMODE_SHIFT)            /*!< FTM0_SYNCONF: HWTRIGMODE Mask           */
#define FTM_SYNCONF_HWTRIGMODE_SHIFT             0                                                   /*!< FTM0_SYNCONF: HWTRIGMODE Position       */
#define FTM_SYNCONF_CNTINC_MASK                  (0x01UL << FTM_SYNCONF_CNTINC_SHIFT)                /*!< FTM0_SYNCONF: CNTINC Mask               */
#define FTM_SYNCONF_CNTINC_SHIFT                 2                                                   /*!< FTM0_SYNCONF: CNTINC Position           */
#define FTM_SYNCONF_INVC_MASK                    (0x01UL << FTM_SYNCONF_INVC_SHIFT)                  /*!< FTM0_SYNCONF: INVC Mask                 */
#define FTM_SYNCONF_INVC_SHIFT                   4                                                   /*!< FTM0_SYNCONF: INVC Position             */
#define FTM_SYNCONF_SWOC_MASK                    (0x01UL << FTM_SYNCONF_SWOC_SHIFT)                  /*!< FTM0_SYNCONF: SWOC Mask                 */
#define FTM_SYNCONF_SWOC_SHIFT                   5                                                   /*!< FTM0_SYNCONF: SWOC Position             */
#define FTM_SYNCONF_SYNCMODE_MASK                (0x01UL << FTM_SYNCONF_SYNCMODE_SHIFT)              /*!< FTM0_SYNCONF: SYNCMODE Mask             */
#define FTM_SYNCONF_SYNCMODE_SHIFT               7                                                   /*!< FTM0_SYNCONF: SYNCMODE Position         */
#define FTM_SYNCONF_SWRSTCNT_MASK                (0x01UL << FTM_SYNCONF_SWRSTCNT_SHIFT)              /*!< FTM0_SYNCONF: SWRSTCNT Mask             */
#define FTM_SYNCONF_SWRSTCNT_SHIFT               8                                                   /*!< FTM0_SYNCONF: SWRSTCNT Position         */
#define FTM_SYNCONF_SWWRBUF_MASK                 (0x01UL << FTM_SYNCONF_SWWRBUF_SHIFT)               /*!< FTM0_SYNCONF: SWWRBUF Mask              */
#define FTM_SYNCONF_SWWRBUF_SHIFT                9                                                   /*!< FTM0_SYNCONF: SWWRBUF Position          */
#define FTM_SYNCONF_SWOM_MASK                    (0x01UL << FTM_SYNCONF_SWOM_SHIFT)                  /*!< FTM0_SYNCONF: SWOM Mask                 */
#define FTM_SYNCONF_SWOM_SHIFT                   10                                                  /*!< FTM0_SYNCONF: SWOM Position             */
#define FTM_SYNCONF_SWINVC_MASK                  (0x01UL << FTM_SYNCONF_SWINVC_SHIFT)                /*!< FTM0_SYNCONF: SWINVC Mask               */
#define FTM_SYNCONF_SWINVC_SHIFT                 11                                                  /*!< FTM0_SYNCONF: SWINVC Position           */
#define FTM_SYNCONF_SWSOC_MASK                   (0x01UL << FTM_SYNCONF_SWSOC_SHIFT)                 /*!< FTM0_SYNCONF: SWSOC Mask                */
#define FTM_SYNCONF_SWSOC_SHIFT                  12                                                  /*!< FTM0_SYNCONF: SWSOC Position            */
#define FTM_SYNCONF_HWRSTCNT_MASK                (0x01UL << FTM_SYNCONF_HWRSTCNT_SHIFT)              /*!< FTM0_SYNCONF: HWRSTCNT Mask             */
#define FTM_SYNCONF_HWRSTCNT_SHIFT               16                                                  /*!< FTM0_SYNCONF: HWRSTCNT Position         */
#define FTM_SYNCONF_HWWRBUF_MASK                 (0x01UL << FTM_SYNCONF_HWWRBUF_SHIFT)               /*!< FTM0_SYNCONF: HWWRBUF Mask              */
#define FTM_SYNCONF_HWWRBUF_SHIFT                17                                                  /*!< FTM0_SYNCONF: HWWRBUF Position          */
#define FTM_SYNCONF_HWOM_MASK                    (0x01UL << FTM_SYNCONF_HWOM_SHIFT)                  /*!< FTM0_SYNCONF: HWOM Mask                 */
#define FTM_SYNCONF_HWOM_SHIFT                   18                                                  /*!< FTM0_SYNCONF: HWOM Position             */
#define FTM_SYNCONF_HWINVC_MASK                  (0x01UL << FTM_SYNCONF_HWINVC_SHIFT)                /*!< FTM0_SYNCONF: HWINVC Mask               */
#define FTM_SYNCONF_HWINVC_SHIFT                 19                                                  /*!< FTM0_SYNCONF: HWINVC Position           */
#define FTM_SYNCONF_HWSOC_MASK                   (0x01UL << FTM_SYNCONF_HWSOC_SHIFT)                 /*!< FTM0_SYNCONF: HWSOC Mask                */
#define FTM_SYNCONF_HWSOC_SHIFT                  20                                                  /*!< FTM0_SYNCONF: HWSOC Position            */

/* ------- FTM0_INVCTRL                             ------ */
#define FTM_INVCTRL_INV0EN_MASK                  (0x01UL << FTM_INVCTRL_INV0EN_SHIFT)                /*!< FTM0_INVCTRL: INV0EN Mask               */
#define FTM_INVCTRL_INV0EN_SHIFT                 0                                                   /*!< FTM0_INVCTRL: INV0EN Position           */
#define FTM_INVCTRL_INV1EN_MASK                  (0x01UL << FTM_INVCTRL_INV1EN_SHIFT)                /*!< FTM0_INVCTRL: INV1EN Mask               */
#define FTM_INVCTRL_INV1EN_SHIFT                 1                                                   /*!< FTM0_INVCTRL: INV1EN Position           */
#define FTM_INVCTRL_INV2EN_MASK                  (0x01UL << FTM_INVCTRL_INV2EN_SHIFT)                /*!< FTM0_INVCTRL: INV2EN Mask               */
#define FTM_INVCTRL_INV2EN_SHIFT                 2                                                   /*!< FTM0_INVCTRL: INV2EN Position           */
#define FTM_INVCTRL_INV3EN_MASK                  (0x01UL << FTM_INVCTRL_INV3EN_SHIFT)                /*!< FTM0_INVCTRL: INV3EN Mask               */
#define FTM_INVCTRL_INV3EN_SHIFT                 3                                                   /*!< FTM0_INVCTRL: INV3EN Position           */

/* ------- FTM0_SWOCTRL                             ------ */
#define FTM_SWOCTRL_CH0OC_MASK                   (0x01UL << FTM_SWOCTRL_CH0OC_SHIFT)                 /*!< FTM0_SWOCTRL: CH0OC Mask                */
#define FTM_SWOCTRL_CH0OC_SHIFT                  0                                                   /*!< FTM0_SWOCTRL: CH0OC Position            */
#define FTM_SWOCTRL_CH1OC_MASK                   (0x01UL << FTM_SWOCTRL_CH1OC_SHIFT)                 /*!< FTM0_SWOCTRL: CH1OC Mask                */
#define FTM_SWOCTRL_CH1OC_SHIFT                  1                                                   /*!< FTM0_SWOCTRL: CH1OC Position            */
#define FTM_SWOCTRL_CH2OC_MASK                   (0x01UL << FTM_SWOCTRL_CH2OC_SHIFT)                 /*!< FTM0_SWOCTRL: CH2OC Mask                */
#define FTM_SWOCTRL_CH2OC_SHIFT                  2                                                   /*!< FTM0_SWOCTRL: CH2OC Position            */
#define FTM_SWOCTRL_CH3OC_MASK                   (0x01UL << FTM_SWOCTRL_CH3OC_SHIFT)                 /*!< FTM0_SWOCTRL: CH3OC Mask                */
#define FTM_SWOCTRL_CH3OC_SHIFT                  3                                                   /*!< FTM0_SWOCTRL: CH3OC Position            */
#define FTM_SWOCTRL_CH4OC_MASK                   (0x01UL << FTM_SWOCTRL_CH4OC_SHIFT)                 /*!< FTM0_SWOCTRL: CH4OC Mask                */
#define FTM_SWOCTRL_CH4OC_SHIFT                  4                                                   /*!< FTM0_SWOCTRL: CH4OC Position            */
#define FTM_SWOCTRL_CH5OC_MASK                   (0x01UL << FTM_SWOCTRL_CH5OC_SHIFT)                 /*!< FTM0_SWOCTRL: CH5OC Mask                */
#define FTM_SWOCTRL_CH5OC_SHIFT                  5                                                   /*!< FTM0_SWOCTRL: CH5OC Position            */
#define FTM_SWOCTRL_CH6OC_MASK                   (0x01UL << FTM_SWOCTRL_CH6OC_SHIFT)                 /*!< FTM0_SWOCTRL: CH6OC Mask                */
#define FTM_SWOCTRL_CH6OC_SHIFT                  6                                                   /*!< FTM0_SWOCTRL: CH6OC Position            */
#define FTM_SWOCTRL_CH7OC_MASK                   (0x01UL << FTM_SWOCTRL_CH7OC_SHIFT)                 /*!< FTM0_SWOCTRL: CH7OC Mask                */
#define FTM_SWOCTRL_CH7OC_SHIFT                  7                                                   /*!< FTM0_SWOCTRL: CH7OC Position            */
#define FTM_SWOCTRL_CH0OCV_MASK                  (0x01UL << FTM_SWOCTRL_CH0OCV_SHIFT)                /*!< FTM0_SWOCTRL: CH0OCV Mask               */
#define FTM_SWOCTRL_CH0OCV_SHIFT                 8                                                   /*!< FTM0_SWOCTRL: CH0OCV Position           */
#define FTM_SWOCTRL_CH1OCV_MASK                  (0x01UL << FTM_SWOCTRL_CH1OCV_SHIFT)                /*!< FTM0_SWOCTRL: CH1OCV Mask               */
#define FTM_SWOCTRL_CH1OCV_SHIFT                 9                                                   /*!< FTM0_SWOCTRL: CH1OCV Position           */
#define FTM_SWOCTRL_CH2OCV_MASK                  (0x01UL << FTM_SWOCTRL_CH2OCV_SHIFT)                /*!< FTM0_SWOCTRL: CH2OCV Mask               */
#define FTM_SWOCTRL_CH2OCV_SHIFT                 10                                                  /*!< FTM0_SWOCTRL: CH2OCV Position           */
#define FTM_SWOCTRL_CH3OCV_MASK                  (0x01UL << FTM_SWOCTRL_CH3OCV_SHIFT)                /*!< FTM0_SWOCTRL: CH3OCV Mask               */
#define FTM_SWOCTRL_CH3OCV_SHIFT                 11                                                  /*!< FTM0_SWOCTRL: CH3OCV Position           */
#define FTM_SWOCTRL_CH4OCV_MASK                  (0x01UL << FTM_SWOCTRL_CH4OCV_SHIFT)                /*!< FTM0_SWOCTRL: CH4OCV Mask               */
#define FTM_SWOCTRL_CH4OCV_SHIFT                 12                                                  /*!< FTM0_SWOCTRL: CH4OCV Position           */
#define FTM_SWOCTRL_CH5OCV_MASK                  (0x01UL << FTM_SWOCTRL_CH5OCV_SHIFT)                /*!< FTM0_SWOCTRL: CH5OCV Mask               */
#define FTM_SWOCTRL_CH5OCV_SHIFT                 13                                                  /*!< FTM0_SWOCTRL: CH5OCV Position           */
#define FTM_SWOCTRL_CH6OCV_MASK                  (0x01UL << FTM_SWOCTRL_CH6OCV_SHIFT)                /*!< FTM0_SWOCTRL: CH6OCV Mask               */
#define FTM_SWOCTRL_CH6OCV_SHIFT                 14                                                  /*!< FTM0_SWOCTRL: CH6OCV Position           */
#define FTM_SWOCTRL_CH7OCV_MASK                  (0x01UL << FTM_SWOCTRL_CH7OCV_SHIFT)                /*!< FTM0_SWOCTRL: CH7OCV Mask               */
#define FTM_SWOCTRL_CH7OCV_SHIFT                 15                                                  /*!< FTM0_SWOCTRL: CH7OCV Position           */

/* ------- FTM0_PWMLOAD                             ------ */
#define FTM_PWMLOAD_CH0SEL_MASK                  (0x01UL << FTM_PWMLOAD_CH0SEL_SHIFT)                /*!< FTM0_PWMLOAD: CH0SEL Mask               */
#define FTM_PWMLOAD_CH0SEL_SHIFT                 0                                                   /*!< FTM0_PWMLOAD: CH0SEL Position           */
#define FTM_PWMLOAD_CH1SEL_MASK                  (0x01UL << FTM_PWMLOAD_CH1SEL_SHIFT)                /*!< FTM0_PWMLOAD: CH1SEL Mask               */
#define FTM_PWMLOAD_CH1SEL_SHIFT                 1                                                   /*!< FTM0_PWMLOAD: CH1SEL Position           */
#define FTM_PWMLOAD_CH2SEL_MASK                  (0x01UL << FTM_PWMLOAD_CH2SEL_SHIFT)                /*!< FTM0_PWMLOAD: CH2SEL Mask               */
#define FTM_PWMLOAD_CH2SEL_SHIFT                 2                                                   /*!< FTM0_PWMLOAD: CH2SEL Position           */
#define FTM_PWMLOAD_CH3SEL_MASK                  (0x01UL << FTM_PWMLOAD_CH3SEL_SHIFT)                /*!< FTM0_PWMLOAD: CH3SEL Mask               */
#define FTM_PWMLOAD_CH3SEL_SHIFT                 3                                                   /*!< FTM0_PWMLOAD: CH3SEL Position           */
#define FTM_PWMLOAD_CH4SEL_MASK                  (0x01UL << FTM_PWMLOAD_CH4SEL_SHIFT)                /*!< FTM0_PWMLOAD: CH4SEL Mask               */
#define FTM_PWMLOAD_CH4SEL_SHIFT                 4                                                   /*!< FTM0_PWMLOAD: CH4SEL Position           */
#define FTM_PWMLOAD_CH5SEL_MASK                  (0x01UL << FTM_PWMLOAD_CH5SEL_SHIFT)                /*!< FTM0_PWMLOAD: CH5SEL Mask               */
#define FTM_PWMLOAD_CH5SEL_SHIFT                 5                                                   /*!< FTM0_PWMLOAD: CH5SEL Position           */
#define FTM_PWMLOAD_CH6SEL_MASK                  (0x01UL << FTM_PWMLOAD_CH6SEL_SHIFT)                /*!< FTM0_PWMLOAD: CH6SEL Mask               */
#define FTM_PWMLOAD_CH6SEL_SHIFT                 6                                                   /*!< FTM0_PWMLOAD: CH6SEL Position           */
#define FTM_PWMLOAD_CH7SEL_MASK                  (0x01UL << FTM_PWMLOAD_CH7SEL_SHIFT)                /*!< FTM0_PWMLOAD: CH7SEL Mask               */
#define FTM_PWMLOAD_CH7SEL_SHIFT                 7                                                   /*!< FTM0_PWMLOAD: CH7SEL Position           */
#define FTM_PWMLOAD_LDOK_MASK                    (0x01UL << FTM_PWMLOAD_LDOK_SHIFT)                  /*!< FTM0_PWMLOAD: LDOK Mask                 */
#define FTM_PWMLOAD_LDOK_SHIFT                   9                                                   /*!< FTM0_PWMLOAD: LDOK Position             */

/* -------------------------------------------------------------------------------- */
/* -----------     'FTM0' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define FTM0_SC                        (FTM0->SC)
#define FTM0_CNT                       (FTM0->CNT)
#define FTM0_MOD                       (FTM0->MOD)
#define FTM0_C0SC                      (FTM0->CONTROLS[0].CnSC)
#define FTM0_C0V                       (FTM0->CONTROLS[0].CnV)
#define FTM0_C1SC                      (FTM0->CONTROLS[1].CnSC)
#define FTM0_C1V                       (FTM0->CONTROLS[1].CnV)
#define FTM0_C2SC                      (FTM0->CONTROLS[2].CnSC)
#define FTM0_C2V                       (FTM0->CONTROLS[2].CnV)
#define FTM0_C3SC                      (FTM0->CONTROLS[3].CnSC)
#define FTM0_C3V                       (FTM0->CONTROLS[3].CnV)
#define FTM0_C4SC                      (FTM0->CONTROLS[4].CnSC)
#define FTM0_C4V                       (FTM0->CONTROLS[4].CnV)
#define FTM0_C5SC                      (FTM0->CONTROLS[5].CnSC)
#define FTM0_C5V                       (FTM0->CONTROLS[5].CnV)
#define FTM0_CNTIN                     (FTM0->CNTIN)
#define FTM0_STATUS                    (FTM0->STATUS)
#define FTM0_MODE                      (FTM0->MODE)
#define FTM0_SYNC                      (FTM0->SYNC)
#define FTM0_OUTINIT                   (FTM0->OUTINIT)
#define FTM0_OUTMASK                   (FTM0->OUTMASK)
#define FTM0_COMBINE                   (FTM0->COMBINE)
#define FTM0_DEADTIME                  (FTM0->DEADTIME)
#define FTM0_EXTTRIG                   (FTM0->EXTTRIG)
#define FTM0_POL                       (FTM0->POL)
#define FTM0_FMS                       (FTM0->FMS)
#define FTM0_FILTER                    (FTM0->FILTER)
#define FTM0_FLTCTRL                   (FTM0->FLTCTRL)
#define FTM0_QDCTRL                    (FTM0->QDCTRL)
#define FTM0_CONF                      (FTM0->CONF)
#define FTM0_FLTPOL                    (FTM0->FLTPOL)
#define FTM0_SYNCONF                   (FTM0->SYNCONF)
#define FTM0_INVCTRL                   (FTM0->INVCTRL)
#define FTM0_SWOCTRL                   (FTM0->SWOCTRL)
#define FTM0_PWMLOAD                   (FTM0->PWMLOAD)

/* ================================================================================ */
/* ================           FTM1 (file:FTM1_MKV)                 ================ */
/* ================================================================================ */

/**
 * @brief FlexTimer Module
 */
typedef struct {                                /*!<       FTM1 Structure                                               */
   __IO uint32_t  SC;                           /*!< 0000: Status and Control                                           */
   __IO uint32_t  CNT;                          /*!< 0004: Counter                                                      */
   __IO uint32_t  MOD;                          /*!< 0008: Modulo                                                       */
   struct { /* (cluster) */                     /*!< 000C: (size=0x0010, 16)                                            */
      __IO uint32_t  CnSC;                      /*!< 000C: Channel (%s) Status and Control                              */
      __IO uint32_t  CV;                        /*!< 0010: Channel (%s) Value                                           */
   } CONTROLS[2];
   __I  uint32_t  RESERVED0[12];                /*!< 001C:                                                              */
   __IO uint32_t  CNTIN;                        /*!< 004C: Counter Initial Value                                        */
   __I  uint32_t  STATUS;                       /*!< 0050: Capture and Compare Status                                   */
   __IO uint32_t  MODE;                         /*!< 0054: Features Mode Selection                                      */
   __IO uint32_t  SYNC;                         /*!< 0058: Synchronization                                              */
   __IO uint32_t  OUTINIT;                      /*!< 005C: Initial State for Channels Output                            */
   __IO uint32_t  OUTMASK;                      /*!< 0060: Output Mask                                                  */
   __IO uint32_t  COMBINE;                      /*!< 0064: Function for Linked Channels                                 */
   __IO uint32_t  DEADTIME;                     /*!< 0068: Deadtime Insertion Control                                   */
   __IO uint32_t  EXTTRIG;                      /*!< 006C: FTM External Trigger                                         */
   __IO uint32_t  POL;                          /*!< 0070: Channels Polarity                                            */
   __IO uint32_t  FMS;                          /*!< 0074: Fault Mode Status                                            */
   __IO uint32_t  FILTER;                       /*!< 0078: Input Capture Filter Control                                 */
   __IO uint32_t  FLTCTRL;                      /*!< 007C: Fault Control                                                */
   __IO uint32_t  QDCTRL;                       /*!< 0080: Quadrature Decoder Control and Status                        */
   __IO uint32_t  CONF;                         /*!< 0084: Configuration                                                */
   __IO uint32_t  FLTPOL;                       /*!< 0088: FTM Fault Input Polarity                                     */
   __IO uint32_t  SYNCONF;                      /*!< 008C: Synchronization Configuration                                */
   __IO uint32_t  INVCTRL;                      /*!< 0090: FTM Inverting Control                                        */
   __IO uint32_t  SWOCTRL;                      /*!< 0094: FTM Software Output Control                                  */
   __IO uint32_t  PWMLOAD;                      /*!< 0098: FTM PWM Load                                                 */
} FTM1_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'FTM1' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- FTM1_SC                                  ------ */

/* ------- FTM1_CNT                                 ------ */

/* ------- FTM1_MOD                                 ------ */

/* ------- FTM1_CnSC                                ------ */

/* ------- FTM1_CV                                  ------ */

/* ------- FTM1_CNTIN                               ------ */

/* ------- FTM1_STATUS                              ------ */

/* ------- FTM1_MODE                                ------ */

/* ------- FTM1_SYNC                                ------ */

/* ------- FTM1_OUTINIT                             ------ */

/* ------- FTM1_OUTMASK                             ------ */

/* ------- FTM1_COMBINE                             ------ */

/* ------- FTM1_DEADTIME                            ------ */

/* ------- FTM1_EXTTRIG                             ------ */

/* ------- FTM1_POL                                 ------ */

/* ------- FTM1_FMS                                 ------ */

/* ------- FTM1_FILTER                              ------ */

/* ------- FTM1_FLTCTRL                             ------ */

/* ------- FTM1_QDCTRL                              ------ */

/* ------- FTM1_CONF                                ------ */

/* ------- FTM1_FLTPOL                              ------ */

/* ------- FTM1_SYNCONF                             ------ */

/* ------- FTM1_INVCTRL                             ------ */

/* ------- FTM1_SWOCTRL                             ------ */

/* ------- FTM1_PWMLOAD                             ------ */

/* -------------------------------------------------------------------------------- */
/* -----------     'FTM1' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define FTM1_SC                        (FTM1->SC)
#define FTM1_CNT                       (FTM1->CNT)
#define FTM1_MOD                       (FTM1->MOD)
#define FTM1_C0SC                      (FTM1->CONTROLS[0].CnSC)
#define FTM1_C0C%sV                    (FTM1->CONTROLS[0].C%sV)
#define FTM1_C1SC                      (FTM1->CONTROLS[1].CnSC)
#define FTM1_C1C%sV                    (FTM1->CONTROLS[1].C%sV)
#define FTM1_CNTIN                     (FTM1->CNTIN)
#define FTM1_STATUS                    (FTM1->STATUS)
#define FTM1_MODE                      (FTM1->MODE)
#define FTM1_SYNC                      (FTM1->SYNC)
#define FTM1_OUTINIT                   (FTM1->OUTINIT)
#define FTM1_OUTMASK                   (FTM1->OUTMASK)
#define FTM1_COMBINE                   (FTM1->COMBINE)
#define FTM1_DEADTIME                  (FTM1->DEADTIME)
#define FTM1_EXTTRIG                   (FTM1->EXTTRIG)
#define FTM1_POL                       (FTM1->POL)
#define FTM1_FMS                       (FTM1->FMS)
#define FTM1_FILTER                    (FTM1->FILTER)
#define FTM1_FLTCTRL                   (FTM1->FLTCTRL)
#define FTM1_QDCTRL                    (FTM1->QDCTRL)
#define FTM1_CONF                      (FTM1->CONF)
#define FTM1_FLTPOL                    (FTM1->FLTPOL)
#define FTM1_SYNCONF                   (FTM1->SYNCONF)
#define FTM1_INVCTRL                   (FTM1->INVCTRL)
#define FTM1_SWOCTRL                   (FTM1->SWOCTRL)
#define FTM1_PWMLOAD                   (FTM1->PWMLOAD)

/* ================================================================================ */
/* ================           FTM2 (derived from FTM1)             ================ */
/* ================================================================================ */

/**
 * @brief FlexTimer Module
 */
typedef FTM1_Type FTM2_Type;  /*!< FTM2 Structure                                              */


/* -------------------------------------------------------------------------------- */
/* -----------     'FTM2' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define FTM2_SC                        (FTM2->SC)
#define FTM2_CNT                       (FTM2->CNT)
#define FTM2_MOD                       (FTM2->MOD)
#define FTM2_C0SC                      (FTM2->CONTROLS[0].CnSC)
#define FTM2_C0C%sV                    (FTM2->CONTROLS[0].C%sV)
#define FTM2_C1SC                      (FTM2->CONTROLS[1].CnSC)
#define FTM2_C1C%sV                    (FTM2->CONTROLS[1].C%sV)
#define FTM2_CNTIN                     (FTM2->CNTIN)
#define FTM2_STATUS                    (FTM2->STATUS)
#define FTM2_MODE                      (FTM2->MODE)
#define FTM2_SYNC                      (FTM2->SYNC)
#define FTM2_OUTINIT                   (FTM2->OUTINIT)
#define FTM2_OUTMASK                   (FTM2->OUTMASK)
#define FTM2_COMBINE                   (FTM2->COMBINE)
#define FTM2_DEADTIME                  (FTM2->DEADTIME)
#define FTM2_EXTTRIG                   (FTM2->EXTTRIG)
#define FTM2_POL                       (FTM2->POL)
#define FTM2_FMS                       (FTM2->FMS)
#define FTM2_FILTER                    (FTM2->FILTER)
#define FTM2_FLTCTRL                   (FTM2->FLTCTRL)
#define FTM2_QDCTRL                    (FTM2->QDCTRL)
#define FTM2_CONF                      (FTM2->CONF)
#define FTM2_FLTPOL                    (FTM2->FLTPOL)
#define FTM2_SYNCONF                   (FTM2->SYNCONF)
#define FTM2_INVCTRL                   (FTM2->INVCTRL)
#define FTM2_SWOCTRL                   (FTM2->SWOCTRL)
#define FTM2_PWMLOAD                   (FTM2->PWMLOAD)

/* ================================================================================ */
/* ================           GPIOA (file:GPIOA_0)                 ================ */
/* ================================================================================ */

/**
 * @brief General Purpose Input/Output
 */
typedef struct {                                /*!<       GPIOA Structure                                              */
   __IO uint32_t  PDOR;                         /*!< 0000: Port Data Output Register                                    */
   __O  uint32_t  PSOR;                         /*!< 0004: Port Set Output Register                                     */
   __O  uint32_t  PCOR;                         /*!< 0008: Port Clear Output Register                                   */
   __O  uint32_t  PTOR;                         /*!< 000C: Port Toggle Output Register                                  */
   __I  uint32_t  PDIR;                         /*!< 0010: Port Data Input Register                                     */
   __IO uint32_t  PDDR;                         /*!< 0014: Port Data Direction Register                                 */
} GPIOA_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'GPIOA' Position & Mask macros                       ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- GPIOA_PDOR                               ------ */
#define GPIOA_PDOR_PDO_MASK                      (0xFFFFFFFFUL << GPIOA_PDOR_PDO_SHIFT)              /*!< GPIOA_PDOR: PDO Mask                    */
#define GPIOA_PDOR_PDO_SHIFT                     0                                                   /*!< GPIOA_PDOR: PDO Position                */
#define GPIOA_PDOR_PDO(x)                        (((x)<<GPIOA_PDOR_PDO_SHIFT)&GPIOA_PDOR_PDO_MASK)   /*!< GPIOA_PDOR                              */

/* ------- GPIOA_PSOR                               ------ */
#define GPIOA_PSOR_PTSO_MASK                     (0xFFFFFFFFUL << GPIOA_PSOR_PTSO_SHIFT)             /*!< GPIOA_PSOR: PTSO Mask                   */
#define GPIOA_PSOR_PTSO_SHIFT                    0                                                   /*!< GPIOA_PSOR: PTSO Position               */
#define GPIOA_PSOR_PTSO(x)                       (((x)<<GPIOA_PSOR_PTSO_SHIFT)&GPIOA_PSOR_PTSO_MASK) /*!< GPIOA_PSOR                              */

/* ------- GPIOA_PCOR                               ------ */
#define GPIOA_PCOR_PTCO_MASK                     (0xFFFFFFFFUL << GPIOA_PCOR_PTCO_SHIFT)             /*!< GPIOA_PCOR: PTCO Mask                   */
#define GPIOA_PCOR_PTCO_SHIFT                    0                                                   /*!< GPIOA_PCOR: PTCO Position               */
#define GPIOA_PCOR_PTCO(x)                       (((x)<<GPIOA_PCOR_PTCO_SHIFT)&GPIOA_PCOR_PTCO_MASK) /*!< GPIOA_PCOR                              */

/* ------- GPIOA_PTOR                               ------ */
#define GPIOA_PTOR_PTTO_MASK                     (0xFFFFFFFFUL << GPIOA_PTOR_PTTO_SHIFT)             /*!< GPIOA_PTOR: PTTO Mask                   */
#define GPIOA_PTOR_PTTO_SHIFT                    0                                                   /*!< GPIOA_PTOR: PTTO Position               */
#define GPIOA_PTOR_PTTO(x)                       (((x)<<GPIOA_PTOR_PTTO_SHIFT)&GPIOA_PTOR_PTTO_MASK) /*!< GPIOA_PTOR                              */

/* ------- GPIOA_PDIR                               ------ */
#define GPIOA_PDIR_PDI_MASK                      (0xFFFFFFFFUL << GPIOA_PDIR_PDI_SHIFT)              /*!< GPIOA_PDIR: PDI Mask                    */
#define GPIOA_PDIR_PDI_SHIFT                     0                                                   /*!< GPIOA_PDIR: PDI Position                */
#define GPIOA_PDIR_PDI(x)                        (((x)<<GPIOA_PDIR_PDI_SHIFT)&GPIOA_PDIR_PDI_MASK)   /*!< GPIOA_PDIR                              */

/* ------- GPIOA_PDDR                               ------ */
#define GPIOA_PDDR_PDD_MASK                      (0xFFFFFFFFUL << GPIOA_PDDR_PDD_SHIFT)              /*!< GPIOA_PDDR: PDD Mask                    */
#define GPIOA_PDDR_PDD_SHIFT                     0                                                   /*!< GPIOA_PDDR: PDD Position                */
#define GPIOA_PDDR_PDD(x)                        (((x)<<GPIOA_PDDR_PDD_SHIFT)&GPIOA_PDDR_PDD_MASK)   /*!< GPIOA_PDDR                              */

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
/* ================           I2C0 (file:I2C0_MKV)                 ================ */
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
   __I  uint8_t   F3;                           /*!< 0007: Flag 3 Register                                              */
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
#define LLWU_ME_WUME0_MASK                       (0x01UL << LLWU_ME_WUME0_SHIFT)                     /*!< LLWU_ME: WUME0 Mask                     */
#define LLWU_ME_WUME0_SHIFT                      0                                                   /*!< LLWU_ME: WUME0 Position                 */
#define LLWU_ME_WUME1_MASK                       (0x01UL << LLWU_ME_WUME1_SHIFT)                     /*!< LLWU_ME: WUME1 Mask                     */
#define LLWU_ME_WUME1_SHIFT                      1                                                   /*!< LLWU_ME: WUME1 Position                 */
#define LLWU_ME_WUME2_MASK                       (0x01UL << LLWU_ME_WUME2_SHIFT)                     /*!< LLWU_ME: WUME2 Mask                     */
#define LLWU_ME_WUME2_SHIFT                      2                                                   /*!< LLWU_ME: WUME2 Position                 */
#define LLWU_ME_WUME3_MASK                       (0x01UL << LLWU_ME_WUME3_SHIFT)                     /*!< LLWU_ME: WUME3 Mask                     */
#define LLWU_ME_WUME3_SHIFT                      3                                                   /*!< LLWU_ME: WUME3 Position                 */
#define LLWU_ME_WUME4_MASK                       (0x01UL << LLWU_ME_WUME4_SHIFT)                     /*!< LLWU_ME: WUME4 Mask                     */
#define LLWU_ME_WUME4_SHIFT                      4                                                   /*!< LLWU_ME: WUME4 Position                 */
#define LLWU_ME_WUME5_MASK                       (0x01UL << LLWU_ME_WUME5_SHIFT)                     /*!< LLWU_ME: WUME5 Mask                     */
#define LLWU_ME_WUME5_SHIFT                      5                                                   /*!< LLWU_ME: WUME5 Position                 */
#define LLWU_ME_WUME6_MASK                       (0x01UL << LLWU_ME_WUME6_SHIFT)                     /*!< LLWU_ME: WUME6 Mask                     */
#define LLWU_ME_WUME6_SHIFT                      6                                                   /*!< LLWU_ME: WUME6 Position                 */
#define LLWU_ME_WUME7_MASK                       (0x01UL << LLWU_ME_WUME7_SHIFT)                     /*!< LLWU_ME: WUME7 Mask                     */
#define LLWU_ME_WUME7_SHIFT                      7                                                   /*!< LLWU_ME: WUME7 Position                 */

/* ------- LLWU_F1                                  ------ */
#define LLWU_F1_WUF0_MASK                        (0x01UL << LLWU_F1_WUF0_SHIFT)                      /*!< LLWU_F1: WUF0 Mask                      */
#define LLWU_F1_WUF0_SHIFT                       0                                                   /*!< LLWU_F1: WUF0 Position                  */
#define LLWU_F1_WUF1_MASK                        (0x01UL << LLWU_F1_WUF1_SHIFT)                      /*!< LLWU_F1: WUF1 Mask                      */
#define LLWU_F1_WUF1_SHIFT                       1                                                   /*!< LLWU_F1: WUF1 Position                  */
#define LLWU_F1_WUF2_MASK                        (0x01UL << LLWU_F1_WUF2_SHIFT)                      /*!< LLWU_F1: WUF2 Mask                      */
#define LLWU_F1_WUF2_SHIFT                       2                                                   /*!< LLWU_F1: WUF2 Position                  */
#define LLWU_F1_WUF3_MASK                        (0x01UL << LLWU_F1_WUF3_SHIFT)                      /*!< LLWU_F1: WUF3 Mask                      */
#define LLWU_F1_WUF3_SHIFT                       3                                                   /*!< LLWU_F1: WUF3 Position                  */
#define LLWU_F1_WUF4_MASK                        (0x01UL << LLWU_F1_WUF4_SHIFT)                      /*!< LLWU_F1: WUF4 Mask                      */
#define LLWU_F1_WUF4_SHIFT                       4                                                   /*!< LLWU_F1: WUF4 Position                  */
#define LLWU_F1_WUF5_MASK                        (0x01UL << LLWU_F1_WUF5_SHIFT)                      /*!< LLWU_F1: WUF5 Mask                      */
#define LLWU_F1_WUF5_SHIFT                       5                                                   /*!< LLWU_F1: WUF5 Position                  */
#define LLWU_F1_WUF6_MASK                        (0x01UL << LLWU_F1_WUF6_SHIFT)                      /*!< LLWU_F1: WUF6 Mask                      */
#define LLWU_F1_WUF6_SHIFT                       6                                                   /*!< LLWU_F1: WUF6 Position                  */
#define LLWU_F1_WUF7_MASK                        (0x01UL << LLWU_F1_WUF7_SHIFT)                      /*!< LLWU_F1: WUF7 Mask                      */
#define LLWU_F1_WUF7_SHIFT                       7                                                   /*!< LLWU_F1: WUF7 Position                  */

/* ------- LLWU_F2                                  ------ */
#define LLWU_F2_WUF8_MASK                        (0x01UL << LLWU_F2_WUF8_SHIFT)                      /*!< LLWU_F2: WUF8 Mask                      */
#define LLWU_F2_WUF8_SHIFT                       0                                                   /*!< LLWU_F2: WUF8 Position                  */
#define LLWU_F2_WUF9_MASK                        (0x01UL << LLWU_F2_WUF9_SHIFT)                      /*!< LLWU_F2: WUF9 Mask                      */
#define LLWU_F2_WUF9_SHIFT                       1                                                   /*!< LLWU_F2: WUF9 Position                  */
#define LLWU_F2_WUF10_MASK                       (0x01UL << LLWU_F2_WUF10_SHIFT)                     /*!< LLWU_F2: WUF10 Mask                     */
#define LLWU_F2_WUF10_SHIFT                      2                                                   /*!< LLWU_F2: WUF10 Position                 */
#define LLWU_F2_WUF11_MASK                       (0x01UL << LLWU_F2_WUF11_SHIFT)                     /*!< LLWU_F2: WUF11 Mask                     */
#define LLWU_F2_WUF11_SHIFT                      3                                                   /*!< LLWU_F2: WUF11 Position                 */
#define LLWU_F2_WUF12_MASK                       (0x01UL << LLWU_F2_WUF12_SHIFT)                     /*!< LLWU_F2: WUF12 Mask                     */
#define LLWU_F2_WUF12_SHIFT                      4                                                   /*!< LLWU_F2: WUF12 Position                 */
#define LLWU_F2_WUF13_MASK                       (0x01UL << LLWU_F2_WUF13_SHIFT)                     /*!< LLWU_F2: WUF13 Mask                     */
#define LLWU_F2_WUF13_SHIFT                      5                                                   /*!< LLWU_F2: WUF13 Position                 */
#define LLWU_F2_WUF14_MASK                       (0x01UL << LLWU_F2_WUF14_SHIFT)                     /*!< LLWU_F2: WUF14 Mask                     */
#define LLWU_F2_WUF14_SHIFT                      6                                                   /*!< LLWU_F2: WUF14 Position                 */
#define LLWU_F2_WUF15_MASK                       (0x01UL << LLWU_F2_WUF15_SHIFT)                     /*!< LLWU_F2: WUF15 Mask                     */
#define LLWU_F2_WUF15_SHIFT                      7                                                   /*!< LLWU_F2: WUF15 Position                 */

/* ------- LLWU_F3                                  ------ */
#define LLWU_F3_MWUF0_MASK                       (0x01UL << LLWU_F3_MWUF0_SHIFT)                     /*!< LLWU_F3: MWUF0 Mask                     */
#define LLWU_F3_MWUF0_SHIFT                      0                                                   /*!< LLWU_F3: MWUF0 Position                 */
#define LLWU_F3_MWUF1_MASK                       (0x01UL << LLWU_F3_MWUF1_SHIFT)                     /*!< LLWU_F3: MWUF1 Mask                     */
#define LLWU_F3_MWUF1_SHIFT                      1                                                   /*!< LLWU_F3: MWUF1 Position                 */
#define LLWU_F3_MWUF2_MASK                       (0x01UL << LLWU_F3_MWUF2_SHIFT)                     /*!< LLWU_F3: MWUF2 Mask                     */
#define LLWU_F3_MWUF2_SHIFT                      2                                                   /*!< LLWU_F3: MWUF2 Position                 */
#define LLWU_F3_MWUF3_MASK                       (0x01UL << LLWU_F3_MWUF3_SHIFT)                     /*!< LLWU_F3: MWUF3 Mask                     */
#define LLWU_F3_MWUF3_SHIFT                      3                                                   /*!< LLWU_F3: MWUF3 Position                 */
#define LLWU_F3_MWUF4_MASK                       (0x01UL << LLWU_F3_MWUF4_SHIFT)                     /*!< LLWU_F3: MWUF4 Mask                     */
#define LLWU_F3_MWUF4_SHIFT                      4                                                   /*!< LLWU_F3: MWUF4 Position                 */
#define LLWU_F3_MWUF5_MASK                       (0x01UL << LLWU_F3_MWUF5_SHIFT)                     /*!< LLWU_F3: MWUF5 Mask                     */
#define LLWU_F3_MWUF5_SHIFT                      5                                                   /*!< LLWU_F3: MWUF5 Position                 */
#define LLWU_F3_MWUF6_MASK                       (0x01UL << LLWU_F3_MWUF6_SHIFT)                     /*!< LLWU_F3: MWUF6 Mask                     */
#define LLWU_F3_MWUF6_SHIFT                      6                                                   /*!< LLWU_F3: MWUF6 Position                 */
#define LLWU_F3_MWUF7_MASK                       (0x01UL << LLWU_F3_MWUF7_SHIFT)                     /*!< LLWU_F3: MWUF7 Mask                     */
#define LLWU_F3_MWUF7_SHIFT                      7                                                   /*!< LLWU_F3: MWUF7 Position                 */

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
#define LPTMR0_CSR_TEN_MASK                      (0x01UL << LPTMR0_CSR_TEN_SHIFT)                    /*!< LPTMR0_CSR: TEN Mask                    */
#define LPTMR0_CSR_TEN_SHIFT                     0                                                   /*!< LPTMR0_CSR: TEN Position                */
#define LPTMR0_CSR_TMS_MASK                      (0x01UL << LPTMR0_CSR_TMS_SHIFT)                    /*!< LPTMR0_CSR: TMS Mask                    */
#define LPTMR0_CSR_TMS_SHIFT                     1                                                   /*!< LPTMR0_CSR: TMS Position                */
#define LPTMR0_CSR_TFC_MASK                      (0x01UL << LPTMR0_CSR_TFC_SHIFT)                    /*!< LPTMR0_CSR: TFC Mask                    */
#define LPTMR0_CSR_TFC_SHIFT                     2                                                   /*!< LPTMR0_CSR: TFC Position                */
#define LPTMR0_CSR_TPP_MASK                      (0x01UL << LPTMR0_CSR_TPP_SHIFT)                    /*!< LPTMR0_CSR: TPP Mask                    */
#define LPTMR0_CSR_TPP_SHIFT                     3                                                   /*!< LPTMR0_CSR: TPP Position                */
#define LPTMR0_CSR_TPS_MASK                      (0x03UL << LPTMR0_CSR_TPS_SHIFT)                    /*!< LPTMR0_CSR: TPS Mask                    */
#define LPTMR0_CSR_TPS_SHIFT                     4                                                   /*!< LPTMR0_CSR: TPS Position                */
#define LPTMR0_CSR_TPS(x)                        (((x)<<LPTMR0_CSR_TPS_SHIFT)&LPTMR0_CSR_TPS_MASK)   /*!< LPTMR0_CSR                              */
#define LPTMR0_CSR_TIE_MASK                      (0x01UL << LPTMR0_CSR_TIE_SHIFT)                    /*!< LPTMR0_CSR: TIE Mask                    */
#define LPTMR0_CSR_TIE_SHIFT                     6                                                   /*!< LPTMR0_CSR: TIE Position                */
#define LPTMR0_CSR_TCF_MASK                      (0x01UL << LPTMR0_CSR_TCF_SHIFT)                    /*!< LPTMR0_CSR: TCF Mask                    */
#define LPTMR0_CSR_TCF_SHIFT                     7                                                   /*!< LPTMR0_CSR: TCF Position                */

/* ------- LPTMR0_PSR                               ------ */
#define LPTMR0_PSR_PCS_MASK                      (0x03UL << LPTMR0_PSR_PCS_SHIFT)                    /*!< LPTMR0_PSR: PCS Mask                    */
#define LPTMR0_PSR_PCS_SHIFT                     0                                                   /*!< LPTMR0_PSR: PCS Position                */
#define LPTMR0_PSR_PCS(x)                        (((x)<<LPTMR0_PSR_PCS_SHIFT)&LPTMR0_PSR_PCS_MASK)   /*!< LPTMR0_PSR                              */
#define LPTMR0_PSR_PBYP_MASK                     (0x01UL << LPTMR0_PSR_PBYP_SHIFT)                   /*!< LPTMR0_PSR: PBYP Mask                   */
#define LPTMR0_PSR_PBYP_SHIFT                    2                                                   /*!< LPTMR0_PSR: PBYP Position               */
#define LPTMR0_PSR_PRESCALE_MASK                 (0x0FUL << LPTMR0_PSR_PRESCALE_SHIFT)               /*!< LPTMR0_PSR: PRESCALE Mask               */
#define LPTMR0_PSR_PRESCALE_SHIFT                3                                                   /*!< LPTMR0_PSR: PRESCALE Position           */
#define LPTMR0_PSR_PRESCALE(x)                   (((x)<<LPTMR0_PSR_PRESCALE_SHIFT)&LPTMR0_PSR_PRESCALE_MASK) /*!< LPTMR0_PSR                              */

/* ------- LPTMR0_CMR                               ------ */
#define LPTMR0_CMR_COMPARE_MASK                  (0xFFFFUL << LPTMR0_CMR_COMPARE_SHIFT)              /*!< LPTMR0_CMR: COMPARE Mask                */
#define LPTMR0_CMR_COMPARE_SHIFT                 0                                                   /*!< LPTMR0_CMR: COMPARE Position            */
#define LPTMR0_CMR_COMPARE(x)                    (((x)<<LPTMR0_CMR_COMPARE_SHIFT)&LPTMR0_CMR_COMPARE_MASK) /*!< LPTMR0_CMR                              */

/* ------- LPTMR0_CNR                               ------ */
#define LPTMR0_CNR_COUNTER_MASK                  (0xFFFFUL << LPTMR0_CNR_COUNTER_SHIFT)              /*!< LPTMR0_CNR: COUNTER Mask                */
#define LPTMR0_CNR_COUNTER_SHIFT                 0                                                   /*!< LPTMR0_CNR: COUNTER Position            */
#define LPTMR0_CNR_COUNTER(x)                    (((x)<<LPTMR0_CNR_COUNTER_SHIFT)&LPTMR0_CNR_COUNTER_MASK) /*!< LPTMR0_CNR                              */

/* -------------------------------------------------------------------------------- */
/* -----------     'LPTMR0' Register Access macros                      ----------- */
/* -------------------------------------------------------------------------------- */

#define LPTMR0_CSR                     (LPTMR0->CSR)
#define LPTMR0_PSR                     (LPTMR0->PSR)
#define LPTMR0_CMR                     (LPTMR0->CMR)
#define LPTMR0_CNR                     (LPTMR0->CNR)

/* ================================================================================ */
/* ================           MCG (file:MCG_MKV)                   ================ */
/* ================================================================================ */

/**
 * @brief Multipurpose Clock Generator module
 */
typedef struct {                                /*!<       MCG Structure                                                */
   __IO uint8_t   C1;                           /*!< 0000: Control 1 Register                                           */
   __IO uint8_t   C2;                           /*!< 0001: Control 2 Register                                           */
   __IO uint8_t   C3;                           /*!< 0002: Control 3 Register                                           */
   __IO uint8_t   C4;                           /*!< 0003: Control 4 Register                                           */
   __I  uint8_t   RESERVED0;                    /*!< 0004:                                                              */
   __IO uint8_t   C6;                           /*!< 0005: Control 6 Register                                           */
   __I  uint8_t   S;                            /*!< 0006: Status Register                                              */
   __I  uint8_t   RESERVED1;                    /*!< 0007:                                                              */
   __IO uint8_t   SC;                           /*!< 0008: Status and Control Register                                  */
   __I  uint8_t   RESERVED2;                    /*!< 0009:                                                              */
   __IO uint8_t   ATCVH;                        /*!< 000A: Auto Trim Compare Value High Register                        */
   __IO uint8_t   ATCVL;                        /*!< 000B: Auto Trim Compare Value Low Register                         */
} MCG_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'MCG' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- MCG_C1                                   ------ */
#define MCG__C1_IREFSTEN_MASK                    (0x01UL << MCG__C1_IREFSTEN_SHIFT)                  /*!< MCG__C1: IREFSTEN Mask                  */
#define MCG__C1_IREFSTEN_SHIFT                   0                                                   /*!< MCG__C1: IREFSTEN Position              */
#define MCG__C1_IRCLKEN_MASK                     (0x01UL << MCG__C1_IRCLKEN_SHIFT)                   /*!< MCG__C1: IRCLKEN Mask                   */
#define MCG__C1_IRCLKEN_SHIFT                    1                                                   /*!< MCG__C1: IRCLKEN Position               */
#define MCG__C1_IREFS_MASK                       (0x01UL << MCG__C1_IREFS_SHIFT)                     /*!< MCG__C1: IREFS Mask                     */
#define MCG__C1_IREFS_SHIFT                      2                                                   /*!< MCG__C1: IREFS Position                 */
#define MCG__C1_FRDIV_MASK                       (0x07UL << MCG__C1_FRDIV_SHIFT)                     /*!< MCG__C1: FRDIV Mask                     */
#define MCG__C1_FRDIV_SHIFT                      3                                                   /*!< MCG__C1: FRDIV Position                 */
#define MCG__C1_FRDIV(x)                         (((x)<<MCG__C1_FRDIV_SHIFT)&MCG__C1_FRDIV_MASK)     /*!< MCG__C1                                 */
#define MCG__C1_CLKS_MASK                        (0x03UL << MCG__C1_CLKS_SHIFT)                      /*!< MCG__C1: CLKS Mask                      */
#define MCG__C1_CLKS_SHIFT                       6                                                   /*!< MCG__C1: CLKS Position                  */
#define MCG__C1_CLKS(x)                          (((x)<<MCG__C1_CLKS_SHIFT)&MCG__C1_CLKS_MASK)       /*!< MCG__C1                                 */

/* ------- MCG_C2                                   ------ */
#define MCG__C2_IRCS_MASK                        (0x01UL << MCG__C2_IRCS_SHIFT)                      /*!< MCG__C2: IRCS Mask                      */
#define MCG__C2_IRCS_SHIFT                       0                                                   /*!< MCG__C2: IRCS Position                  */
#define MCG__C2_LP_MASK                          (0x01UL << MCG__C2_LP_SHIFT)                        /*!< MCG__C2: LP Mask                        */
#define MCG__C2_LP_SHIFT                         1                                                   /*!< MCG__C2: LP Position                    */
#define MCG__C2_EREFS0_MASK                      (0x01UL << MCG__C2_EREFS0_SHIFT)                    /*!< MCG__C2: EREFS0 Mask                    */
#define MCG__C2_EREFS0_SHIFT                     2                                                   /*!< MCG__C2: EREFS0 Position                */
#define MCG__C2_HGO0_MASK                        (0x01UL << MCG__C2_HGO0_SHIFT)                      /*!< MCG__C2: HGO0 Mask                      */
#define MCG__C2_HGO0_SHIFT                       3                                                   /*!< MCG__C2: HGO0 Position                  */
#define MCG__C2_RANGE0_MASK                      (0x03UL << MCG__C2_RANGE0_SHIFT)                    /*!< MCG__C2: RANGE0 Mask                    */
#define MCG__C2_RANGE0_SHIFT                     4                                                   /*!< MCG__C2: RANGE0 Position                */
#define MCG__C2_RANGE0(x)                        (((x)<<MCG__C2_RANGE0_SHIFT)&MCG__C2_RANGE0_MASK)   /*!< MCG__C2                                 */
#define MCG__C2_FCFTRIM_MASK                     (0x01UL << MCG__C2_FCFTRIM_SHIFT)                   /*!< MCG__C2: FCFTRIM Mask                   */
#define MCG__C2_FCFTRIM_SHIFT                    6                                                   /*!< MCG__C2: FCFTRIM Position               */
#define MCG__C2_LOCRE0_MASK                      (0x01UL << MCG__C2_LOCRE0_SHIFT)                    /*!< MCG__C2: LOCRE0 Mask                    */
#define MCG__C2_LOCRE0_SHIFT                     7                                                   /*!< MCG__C2: LOCRE0 Position                */

/* ------- MCG_C3                                   ------ */
#define MCG__C3_SCTRIM_MASK                      (0xFFUL << MCG__C3_SCTRIM_SHIFT)                    /*!< MCG__C3: SCTRIM Mask                    */
#define MCG__C3_SCTRIM_SHIFT                     0                                                   /*!< MCG__C3: SCTRIM Position                */
#define MCG__C3_SCTRIM(x)                        (((x)<<MCG__C3_SCTRIM_SHIFT)&MCG__C3_SCTRIM_MASK)   /*!< MCG__C3                                 */

/* ------- MCG_C4                                   ------ */
#define MCG__C4_SCFTRIM_MASK                     (0x01UL << MCG__C4_SCFTRIM_SHIFT)                   /*!< MCG__C4: SCFTRIM Mask                   */
#define MCG__C4_SCFTRIM_SHIFT                    0                                                   /*!< MCG__C4: SCFTRIM Position               */
#define MCG__C4_FCTRIM_MASK                      (0x0FUL << MCG__C4_FCTRIM_SHIFT)                    /*!< MCG__C4: FCTRIM Mask                    */
#define MCG__C4_FCTRIM_SHIFT                     1                                                   /*!< MCG__C4: FCTRIM Position                */
#define MCG__C4_FCTRIM(x)                        (((x)<<MCG__C4_FCTRIM_SHIFT)&MCG__C4_FCTRIM_MASK)   /*!< MCG__C4                                 */
#define MCG__C4_DRST_DRS_MASK                    (0x03UL << MCG__C4_DRST_DRS_SHIFT)                  /*!< MCG__C4: DRST_DRS Mask                  */
#define MCG__C4_DRST_DRS_SHIFT                   5                                                   /*!< MCG__C4: DRST_DRS Position              */
#define MCG__C4_DRST_DRS(x)                      (((x)<<MCG__C4_DRST_DRS_SHIFT)&MCG__C4_DRST_DRS_MASK) /*!< MCG__C4                                 */
#define MCG__C4_DMX32_MASK                       (0x01UL << MCG__C4_DMX32_SHIFT)                     /*!< MCG__C4: DMX32 Mask                     */
#define MCG__C4_DMX32_SHIFT                      7                                                   /*!< MCG__C4: DMX32 Position                 */

/* ------- MCG_C6                                   ------ */
#define MCG__C6_CME_MASK                         (0x01UL << MCG__C6_CME_SHIFT)                       /*!< MCG__C6: CME Mask                       */
#define MCG__C6_CME_SHIFT                        5                                                   /*!< MCG__C6: CME Position                   */

/* ------- MCG_S                                    ------ */
#define MCG__S_IRCST_MASK                        (0x01UL << MCG__S_IRCST_SHIFT)                      /*!< MCG__S: IRCST Mask                      */
#define MCG__S_IRCST_SHIFT                       0                                                   /*!< MCG__S: IRCST Position                  */
#define MCG__S_OSCINIT0_MASK                     (0x01UL << MCG__S_OSCINIT0_SHIFT)                   /*!< MCG__S: OSCINIT0 Mask                   */
#define MCG__S_OSCINIT0_SHIFT                    1                                                   /*!< MCG__S: OSCINIT0 Position               */
#define MCG__S_CLKST_MASK                        (0x03UL << MCG__S_CLKST_SHIFT)                      /*!< MCG__S: CLKST Mask                      */
#define MCG__S_CLKST_SHIFT                       2                                                   /*!< MCG__S: CLKST Position                  */
#define MCG__S_CLKST(x)                          (((x)<<MCG__S_CLKST_SHIFT)&MCG__S_CLKST_MASK)       /*!< MCG__S                                  */
#define MCG__S_IREFST_MASK                       (0x01UL << MCG__S_IREFST_SHIFT)                     /*!< MCG__S: IREFST Mask                     */
#define MCG__S_IREFST_SHIFT                      4                                                   /*!< MCG__S: IREFST Position                 */

/* ------- MCG_SC                                   ------ */
#define MCG__SC_LOCS0_MASK                       (0x01UL << MCG__SC_LOCS0_SHIFT)                     /*!< MCG__SC: LOCS0 Mask                     */
#define MCG__SC_LOCS0_SHIFT                      0                                                   /*!< MCG__SC: LOCS0 Position                 */
#define MCG__SC_FCRDIV_MASK                      (0x07UL << MCG__SC_FCRDIV_SHIFT)                    /*!< MCG__SC: FCRDIV Mask                    */
#define MCG__SC_FCRDIV_SHIFT                     1                                                   /*!< MCG__SC: FCRDIV Position                */
#define MCG__SC_FCRDIV(x)                        (((x)<<MCG__SC_FCRDIV_SHIFT)&MCG__SC_FCRDIV_MASK)   /*!< MCG__SC                                 */
#define MCG__SC_FLTPRSRV_MASK                    (0x01UL << MCG__SC_FLTPRSRV_SHIFT)                  /*!< MCG__SC: FLTPRSRV Mask                  */
#define MCG__SC_FLTPRSRV_SHIFT                   4                                                   /*!< MCG__SC: FLTPRSRV Position              */
#define MCG__SC_ATMF_MASK                        (0x01UL << MCG__SC_ATMF_SHIFT)                      /*!< MCG__SC: ATMF Mask                      */
#define MCG__SC_ATMF_SHIFT                       5                                                   /*!< MCG__SC: ATMF Position                  */
#define MCG__SC_ATMS_MASK                        (0x01UL << MCG__SC_ATMS_SHIFT)                      /*!< MCG__SC: ATMS Mask                      */
#define MCG__SC_ATMS_SHIFT                       6                                                   /*!< MCG__SC: ATMS Position                  */
#define MCG__SC_ATME_MASK                        (0x01UL << MCG__SC_ATME_SHIFT)                      /*!< MCG__SC: ATME Mask                      */
#define MCG__SC_ATME_SHIFT                       7                                                   /*!< MCG__SC: ATME Position                  */

/* ------- MCG_ATCVH                                ------ */
#define MCG__ATCVH_ATCVH_MASK                    (0xFFUL << MCG__ATCVH_ATCVH_SHIFT)                  /*!< MCG__ATCVH: ATCVH Mask                  */
#define MCG__ATCVH_ATCVH_SHIFT                   0                                                   /*!< MCG__ATCVH: ATCVH Position              */
#define MCG__ATCVH_ATCVH(x)                      (((x)<<MCG__ATCVH_ATCVH_SHIFT)&MCG__ATCVH_ATCVH_MASK) /*!< MCG__ATCVH                              */

/* ------- MCG_ATCVL                                ------ */
#define MCG__ATCVL_ATCVL_MASK                    (0xFFUL << MCG__ATCVL_ATCVL_SHIFT)                  /*!< MCG__ATCVL: ATCVL Mask                  */
#define MCG__ATCVL_ATCVL_SHIFT                   0                                                   /*!< MCG__ATCVL: ATCVL Position              */
#define MCG__ATCVL_ATCVL(x)                      (((x)<<MCG__ATCVL_ATCVL_SHIFT)&MCG__ATCVL_ATCVL_MASK) /*!< MCG__ATCVL                              */

/* -------------------------------------------------------------------------------- */
/* -----------     'MCG' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define MCG_C1                         (MCG->C1)
#define MCG_C2                         (MCG->C2)
#define MCG_C3                         (MCG->C3)
#define MCG_C4                         (MCG->C4)
#define MCG_C6                         (MCG->C6)
#define MCG_S                          (MCG->S)
#define MCG_SC                         (MCG->SC)
#define MCG_ATCVH                      (MCG->ATCVH)
#define MCG_ATCVL                      (MCG->ATCVL)

/* ================================================================================ */
/* ================           MCM (file:MCM_8)                     ================ */
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
/* ================           MMDVSQ (file:MMDVSQ_0)               ================ */
/* ================================================================================ */

/**
 * @brief Memory-Mapped Divide and Square Root
 */
typedef struct {                                /*!<       MMDVSQ Structure                                             */
   __IO uint32_t  DEND;                         /*!< 0000: Dividend Register                                            */
   __IO uint32_t  DSOR;                         /*!< 0004: Divisor Register                                             */
   __IO uint32_t  CSR;                          /*!< 0008: Control/Status Register                                      */
   __IO uint32_t  RES;                          /*!< 000C: Result Register                                              */
   __IO uint32_t  RCND;                         /*!< 0010: Radicand Register                                            */
} MMDVSQ_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'MMDVSQ' Position & Mask macros                      ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- MMDVSQ_DEND                              ------ */
#define MMDVSQ__DEND_DIVIDEND_MASK               (0xFFFFFFFFUL << MMDVSQ__DEND_DIVIDEND_SHIFT)       /*!< MMDVSQ__DEND: DIVIDEND Mask             */
#define MMDVSQ__DEND_DIVIDEND_SHIFT              0                                                   /*!< MMDVSQ__DEND: DIVIDEND Position         */
#define MMDVSQ__DEND_DIVIDEND(x)                 (((x)<<MMDVSQ__DEND_DIVIDEND_SHIFT)&MMDVSQ__DEND_DIVIDEND_MASK) /*!< MMDVSQ__DEND                            */

/* ------- MMDVSQ_DSOR                              ------ */
#define MMDVSQ__DSOR_DIVISOR_MASK                (0xFFFFFFFFUL << MMDVSQ__DSOR_DIVISOR_SHIFT)        /*!< MMDVSQ__DSOR: DIVISOR Mask              */
#define MMDVSQ__DSOR_DIVISOR_SHIFT               0                                                   /*!< MMDVSQ__DSOR: DIVISOR Position          */
#define MMDVSQ__DSOR_DIVISOR(x)                  (((x)<<MMDVSQ__DSOR_DIVISOR_SHIFT)&MMDVSQ__DSOR_DIVISOR_MASK) /*!< MMDVSQ__DSOR                            */

/* ------- MMDVSQ_CSR                               ------ */
#define MMDVSQ__CSR_SRT_MASK                     (0x01UL << MMDVSQ__CSR_SRT_SHIFT)                   /*!< MMDVSQ__CSR: SRT Mask                   */
#define MMDVSQ__CSR_SRT_SHIFT                    0                                                   /*!< MMDVSQ__CSR: SRT Position               */
#define MMDVSQ__CSR_USGN_MASK                    (0x01UL << MMDVSQ__CSR_USGN_SHIFT)                  /*!< MMDVSQ__CSR: USGN Mask                  */
#define MMDVSQ__CSR_USGN_SHIFT                   1                                                   /*!< MMDVSQ__CSR: USGN Position              */
#define MMDVSQ__CSR_REM_MASK                     (0x01UL << MMDVSQ__CSR_REM_SHIFT)                   /*!< MMDVSQ__CSR: REM Mask                   */
#define MMDVSQ__CSR_REM_SHIFT                    2                                                   /*!< MMDVSQ__CSR: REM Position               */
#define MMDVSQ__CSR_DZE_MASK                     (0x01UL << MMDVSQ__CSR_DZE_SHIFT)                   /*!< MMDVSQ__CSR: DZE Mask                   */
#define MMDVSQ__CSR_DZE_SHIFT                    3                                                   /*!< MMDVSQ__CSR: DZE Position               */
#define MMDVSQ__CSR_DZ_MASK                      (0x01UL << MMDVSQ__CSR_DZ_SHIFT)                    /*!< MMDVSQ__CSR: DZ Mask                    */
#define MMDVSQ__CSR_DZ_SHIFT                     4                                                   /*!< MMDVSQ__CSR: DZ Position                */
#define MMDVSQ__CSR_DFS_MASK                     (0x01UL << MMDVSQ__CSR_DFS_SHIFT)                   /*!< MMDVSQ__CSR: DFS Mask                   */
#define MMDVSQ__CSR_DFS_SHIFT                    5                                                   /*!< MMDVSQ__CSR: DFS Position               */
#define MMDVSQ__CSR_SQRT_MASK                    (0x01UL << MMDVSQ__CSR_SQRT_SHIFT)                  /*!< MMDVSQ__CSR: SQRT Mask                  */
#define MMDVSQ__CSR_SQRT_SHIFT                   29                                                  /*!< MMDVSQ__CSR: SQRT Position              */
#define MMDVSQ__CSR_DIV_MASK                     (0x01UL << MMDVSQ__CSR_DIV_SHIFT)                   /*!< MMDVSQ__CSR: DIV Mask                   */
#define MMDVSQ__CSR_DIV_SHIFT                    30                                                  /*!< MMDVSQ__CSR: DIV Position               */
#define MMDVSQ__CSR_BUSY_MASK                    (0x01UL << MMDVSQ__CSR_BUSY_SHIFT)                  /*!< MMDVSQ__CSR: BUSY Mask                  */
#define MMDVSQ__CSR_BUSY_SHIFT                   31                                                  /*!< MMDVSQ__CSR: BUSY Position              */

/* ------- MMDVSQ_RES                               ------ */
#define MMDVSQ__RES_RESULT_MASK                  (0xFFFFFFFFUL << MMDVSQ__RES_RESULT_SHIFT)          /*!< MMDVSQ__RES: RESULT Mask                */
#define MMDVSQ__RES_RESULT_SHIFT                 0                                                   /*!< MMDVSQ__RES: RESULT Position            */
#define MMDVSQ__RES_RESULT(x)                    (((x)<<MMDVSQ__RES_RESULT_SHIFT)&MMDVSQ__RES_RESULT_MASK) /*!< MMDVSQ__RES                             */

/* ------- MMDVSQ_RCND                              ------ */
#define MMDVSQ__RCND_RADICAND_MASK               (0xFFFFFFFFUL << MMDVSQ__RCND_RADICAND_SHIFT)       /*!< MMDVSQ__RCND: RADICAND Mask             */
#define MMDVSQ__RCND_RADICAND_SHIFT              0                                                   /*!< MMDVSQ__RCND: RADICAND Position         */
#define MMDVSQ__RCND_RADICAND(x)                 (((x)<<MMDVSQ__RCND_RADICAND_SHIFT)&MMDVSQ__RCND_RADICAND_MASK) /*!< MMDVSQ__RCND                            */

/* -------------------------------------------------------------------------------- */
/* -----------     'MMDVSQ' Register Access macros                      ----------- */
/* -------------------------------------------------------------------------------- */

#define MMDVSQ_DEND                    (MMDVSQ->DEND)
#define MMDVSQ_DSOR                    (MMDVSQ->DSOR)
#define MMDVSQ_CSR                     (MMDVSQ->CSR)
#define MMDVSQ_RES                     (MMDVSQ->RES)
#define MMDVSQ_RCND                    (MMDVSQ->RCND)

/* ================================================================================ */
/* ================           MTB (file:MTB_MKV)                   ================ */
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
#define MTB_AUTHSTAT_BIT2_MASK                   (0x01UL << MTB_AUTHSTAT_BIT2_SHIFT)                 /*!< MTB_AUTHSTAT: BIT2 Mask                 */
#define MTB_AUTHSTAT_BIT2_SHIFT                  2                                                   /*!< MTB_AUTHSTAT: BIT2 Position             */

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
/* ================           NV (file:NV_FTFA)                    ================ */
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
#define NV_FOPT_NMI_DIS_MASK                     (0x01UL << NV_FOPT_NMI_DIS_SHIFT)                   /*!< NV_FOPT: NMI_DIS Mask                   */
#define NV_FOPT_NMI_DIS_SHIFT                    2                                                   /*!< NV_FOPT: NMI_DIS Position               */
#define NV_FOPT_RESET_PIN_CFG_MASK               (0x01UL << NV_FOPT_RESET_PIN_CFG_SHIFT)             /*!< NV_FOPT: RESET_PIN_CFG Mask             */
#define NV_FOPT_RESET_PIN_CFG_SHIFT              3                                                   /*!< NV_FOPT: RESET_PIN_CFG Position         */
#define NV_FOPT_LPBOOT1_MASK                     (0x01UL << NV_FOPT_LPBOOT1_SHIFT)                   /*!< NV_FOPT: LPBOOT1 Mask                   */
#define NV_FOPT_LPBOOT1_SHIFT                    4                                                   /*!< NV_FOPT: LPBOOT1 Position               */
#define NV_FOPT_FAST_INIT_MASK                   (0x01UL << NV_FOPT_FAST_INIT_SHIFT)                 /*!< NV_FOPT: FAST_INIT Mask                 */
#define NV_FOPT_FAST_INIT_SHIFT                  5                                                   /*!< NV_FOPT: FAST_INIT Position             */

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
   __IO uint8_t   CR;                           /*!< 0000: OSC Control Register                                         */
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
/* ================           PDB0 (file:PDB0_2CH_2TRIG_1PO)       ================ */
/* ================================================================================ */

/**
 * @brief Programmable Delay Block (2 channels, 2 triggers, 1 pulse output)
 */
typedef struct {                                /*!<       PDB0 Structure                                               */
   __IO uint32_t  SC;                           /*!< 0000: Status and Control Register                                  */
   __IO uint32_t  MOD;                          /*!< 0004: Modulus Register                                             */
   __I  uint32_t  CNT;                          /*!< 0008: Counter Register                                             */
   __IO uint32_t  IDLY;                         /*!< 000C: Interrupt Delay Register                                     */
   struct { /* (cluster) */                     /*!< 0010: (size=0x0050, 80)                                            */
      __IO uint32_t  C1;                        /*!< 0010: Channel n Control Register 1                                 */
      __IO uint32_t  S;                         /*!< 0014: Channel n Status Register                                    */
      __IO uint32_t  DLY[2];                    /*!< 0018: Channel n Delay  Register                                    */
      __I  uint32_t  RESERVED0[6];              /*!< 0020:                                                              */
   } CH[2];
   __I  uint32_t  RESERVED0[60];                /*!< 0060:                                                              */
   struct { /* (cluster) */                     /*!< 0150: (size=0x0010, 16)                                            */
      __IO uint32_t  INTC;                      /*!< 0150: DAC Interval Trigger n Control Register                      */
      __IO uint32_t  INT;                       /*!< 0154: DAC Interval n Register                                      */
   } DAC[2];
   __I  uint32_t  RESERVED1[12];                /*!< 0160:                                                              */
   __IO uint32_t  POEN;                         /*!< 0190: Pulse-Out Enable Register                                    */
   __IO uint32_t  PODLY[1];                     /*!< 0194: Pulse-Out  Delay Register                                    */
} PDB0_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'PDB0' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- PDB0_SC                                  ------ */
#define PDB0_SC_LDOK_MASK                        (0x01UL << PDB0_SC_LDOK_SHIFT)                      /*!< PDB0_SC: LDOK Mask                      */
#define PDB0_SC_LDOK_SHIFT                       0                                                   /*!< PDB0_SC: LDOK Position                  */
#define PDB0_SC_CONT_MASK                        (0x01UL << PDB0_SC_CONT_SHIFT)                      /*!< PDB0_SC: CONT Mask                      */
#define PDB0_SC_CONT_SHIFT                       1                                                   /*!< PDB0_SC: CONT Position                  */
#define PDB0_SC_MULT_MASK                        (0x03UL << PDB0_SC_MULT_SHIFT)                      /*!< PDB0_SC: MULT Mask                      */
#define PDB0_SC_MULT_SHIFT                       2                                                   /*!< PDB0_SC: MULT Position                  */
#define PDB0_SC_MULT(x)                          (((x)<<PDB0_SC_MULT_SHIFT)&PDB0_SC_MULT_MASK)       /*!< PDB0_SC                                 */
#define PDB0_SC_PDBIE_MASK                       (0x01UL << PDB0_SC_PDBIE_SHIFT)                     /*!< PDB0_SC: PDBIE Mask                     */
#define PDB0_SC_PDBIE_SHIFT                      5                                                   /*!< PDB0_SC: PDBIE Position                 */
#define PDB0_SC_PDBIF_MASK                       (0x01UL << PDB0_SC_PDBIF_SHIFT)                     /*!< PDB0_SC: PDBIF Mask                     */
#define PDB0_SC_PDBIF_SHIFT                      6                                                   /*!< PDB0_SC: PDBIF Position                 */
#define PDB0_SC_PDBEN_MASK                       (0x01UL << PDB0_SC_PDBEN_SHIFT)                     /*!< PDB0_SC: PDBEN Mask                     */
#define PDB0_SC_PDBEN_SHIFT                      7                                                   /*!< PDB0_SC: PDBEN Position                 */
#define PDB0_SC_TRGSEL_MASK                      (0x0FUL << PDB0_SC_TRGSEL_SHIFT)                    /*!< PDB0_SC: TRGSEL Mask                    */
#define PDB0_SC_TRGSEL_SHIFT                     8                                                   /*!< PDB0_SC: TRGSEL Position                */
#define PDB0_SC_TRGSEL(x)                        (((x)<<PDB0_SC_TRGSEL_SHIFT)&PDB0_SC_TRGSEL_MASK)   /*!< PDB0_SC                                 */
#define PDB0_SC_PRESCALER_MASK                   (0x07UL << PDB0_SC_PRESCALER_SHIFT)                 /*!< PDB0_SC: PRESCALER Mask                 */
#define PDB0_SC_PRESCALER_SHIFT                  12                                                  /*!< PDB0_SC: PRESCALER Position             */
#define PDB0_SC_PRESCALER(x)                     (((x)<<PDB0_SC_PRESCALER_SHIFT)&PDB0_SC_PRESCALER_MASK) /*!< PDB0_SC                                 */
#define PDB0_SC_DMAEN_MASK                       (0x01UL << PDB0_SC_DMAEN_SHIFT)                     /*!< PDB0_SC: DMAEN Mask                     */
#define PDB0_SC_DMAEN_SHIFT                      15                                                  /*!< PDB0_SC: DMAEN Position                 */
#define PDB0_SC_SWTRIG_MASK                      (0x01UL << PDB0_SC_SWTRIG_SHIFT)                    /*!< PDB0_SC: SWTRIG Mask                    */
#define PDB0_SC_SWTRIG_SHIFT                     16                                                  /*!< PDB0_SC: SWTRIG Position                */
#define PDB0_SC_PDBEIE_MASK                      (0x01UL << PDB0_SC_PDBEIE_SHIFT)                    /*!< PDB0_SC: PDBEIE Mask                    */
#define PDB0_SC_PDBEIE_SHIFT                     17                                                  /*!< PDB0_SC: PDBEIE Position                */
#define PDB0_SC_LDMOD_MASK                       (0x03UL << PDB0_SC_LDMOD_SHIFT)                     /*!< PDB0_SC: LDMOD Mask                     */
#define PDB0_SC_LDMOD_SHIFT                      18                                                  /*!< PDB0_SC: LDMOD Position                 */
#define PDB0_SC_LDMOD(x)                         (((x)<<PDB0_SC_LDMOD_SHIFT)&PDB0_SC_LDMOD_MASK)     /*!< PDB0_SC                                 */

/* ------- PDB0_MOD                                 ------ */
#define PDB0_MOD_MOD_MASK                        (0xFFFFUL << PDB0_MOD_MOD_SHIFT)                    /*!< PDB0_MOD: MOD Mask                      */
#define PDB0_MOD_MOD_SHIFT                       0                                                   /*!< PDB0_MOD: MOD Position                  */
#define PDB0_MOD_MOD(x)                          (((x)<<PDB0_MOD_MOD_SHIFT)&PDB0_MOD_MOD_MASK)       /*!< PDB0_MOD                                */

/* ------- PDB0_CNT                                 ------ */
#define PDB0_CNT_CNT_MASK                        (0xFFFFUL << PDB0_CNT_CNT_SHIFT)                    /*!< PDB0_CNT: CNT Mask                      */
#define PDB0_CNT_CNT_SHIFT                       0                                                   /*!< PDB0_CNT: CNT Position                  */
#define PDB0_CNT_CNT(x)                          (((x)<<PDB0_CNT_CNT_SHIFT)&PDB0_CNT_CNT_MASK)       /*!< PDB0_CNT                                */

/* ------- PDB0_IDLY                                ------ */
#define PDB0_IDLY_IDLY_MASK                      (0xFFFFUL << PDB0_IDLY_IDLY_SHIFT)                  /*!< PDB0_IDLY: IDLY Mask                    */
#define PDB0_IDLY_IDLY_SHIFT                     0                                                   /*!< PDB0_IDLY: IDLY Position                */
#define PDB0_IDLY_IDLY(x)                        (((x)<<PDB0_IDLY_IDLY_SHIFT)&PDB0_IDLY_IDLY_MASK)   /*!< PDB0_IDLY                               */

/* ------- PDB0_C1                                  ------ */
#define PDB0_C1_EN_MASK                          (0xFFUL << PDB0_C1_EN_SHIFT)                        /*!< PDB0_C1: EN Mask                        */
#define PDB0_C1_EN_SHIFT                         0                                                   /*!< PDB0_C1: EN Position                    */
#define PDB0_C1_EN(x)                            (((x)<<PDB0_C1_EN_SHIFT)&PDB0_C1_EN_MASK)           /*!< PDB0_C1                                 */
#define PDB0_C1_TOS_MASK                         (0xFFUL << PDB0_C1_TOS_SHIFT)                       /*!< PDB0_C1: TOS Mask                       */
#define PDB0_C1_TOS_SHIFT                        8                                                   /*!< PDB0_C1: TOS Position                   */
#define PDB0_C1_TOS(x)                           (((x)<<PDB0_C1_TOS_SHIFT)&PDB0_C1_TOS_MASK)         /*!< PDB0_C1                                 */
#define PDB0_C1_BB_MASK                          (0xFFUL << PDB0_C1_BB_SHIFT)                        /*!< PDB0_C1: BB Mask                        */
#define PDB0_C1_BB_SHIFT                         16                                                  /*!< PDB0_C1: BB Position                    */
#define PDB0_C1_BB(x)                            (((x)<<PDB0_C1_BB_SHIFT)&PDB0_C1_BB_MASK)           /*!< PDB0_C1                                 */

/* ------- PDB0_S                                   ------ */
#define PDB0_S_ERR_MASK                          (0xFFUL << PDB0_S_ERR_SHIFT)                        /*!< PDB0_S: ERR Mask                        */
#define PDB0_S_ERR_SHIFT                         0                                                   /*!< PDB0_S: ERR Position                    */
#define PDB0_S_ERR(x)                            (((x)<<PDB0_S_ERR_SHIFT)&PDB0_S_ERR_MASK)           /*!< PDB0_S                                  */
#define PDB0_S_CF_MASK                           (0xFFUL << PDB0_S_CF_SHIFT)                         /*!< PDB0_S: CF Mask                         */
#define PDB0_S_CF_SHIFT                          16                                                  /*!< PDB0_S: CF Position                     */
#define PDB0_S_CF(x)                             (((x)<<PDB0_S_CF_SHIFT)&PDB0_S_CF_MASK)             /*!< PDB0_S                                  */

/* ------- PDB0_DLY                                 ------ */
#define PDB0_DLY_DLY_MASK                        (0xFFFFUL << PDB0_DLY_DLY_SHIFT)                    /*!< PDB0_DLY: DLY Mask                      */
#define PDB0_DLY_DLY_SHIFT                       0                                                   /*!< PDB0_DLY: DLY Position                  */
#define PDB0_DLY_DLY(x)                          (((x)<<PDB0_DLY_DLY_SHIFT)&PDB0_DLY_DLY_MASK)       /*!< PDB0_DLY                                */

/* ------- PDB0_INTC                                ------ */
#define PDB0_INTC_TOE_MASK                       (0x01UL << PDB0_INTC_TOE_SHIFT)                     /*!< PDB0_INTC: TOE Mask                     */
#define PDB0_INTC_TOE_SHIFT                      0                                                   /*!< PDB0_INTC: TOE Position                 */
#define PDB0_INTC_EXT_MASK                       (0x01UL << PDB0_INTC_EXT_SHIFT)                     /*!< PDB0_INTC: EXT Mask                     */
#define PDB0_INTC_EXT_SHIFT                      1                                                   /*!< PDB0_INTC: EXT Position                 */

/* ------- PDB0_INT                                 ------ */
#define PDB0_INT_INT_MASK                        (0xFFFFUL << PDB0_INT_INT_SHIFT)                    /*!< PDB0_INT: INT Mask                      */
#define PDB0_INT_INT_SHIFT                       0                                                   /*!< PDB0_INT: INT Position                  */
#define PDB0_INT_INT(x)                          (((x)<<PDB0_INT_INT_SHIFT)&PDB0_INT_INT_MASK)       /*!< PDB0_INT                                */

/* ------- PDB0_POEN                                ------ */
#define PDB0_POEN_POEN_MASK                      (0xFFUL << PDB0_POEN_POEN_SHIFT)                    /*!< PDB0_POEN: POEN Mask                    */
#define PDB0_POEN_POEN_SHIFT                     0                                                   /*!< PDB0_POEN: POEN Position                */
#define PDB0_POEN_POEN(x)                        (((x)<<PDB0_POEN_POEN_SHIFT)&PDB0_POEN_POEN_MASK)   /*!< PDB0_POEN                               */

/* ------- PDB0_PODLY                               ------ */
#define PDB0_PODLY_DLY2_MASK                     (0xFFFFUL << PDB0_PODLY_DLY2_SHIFT)                 /*!< PDB0_PODLY: DLY2 Mask                   */
#define PDB0_PODLY_DLY2_SHIFT                    0                                                   /*!< PDB0_PODLY: DLY2 Position               */
#define PDB0_PODLY_DLY2(x)                       (((x)<<PDB0_PODLY_DLY2_SHIFT)&PDB0_PODLY_DLY2_MASK) /*!< PDB0_PODLY                              */
#define PDB0_PODLY_DLY1_MASK                     (0xFFFFUL << PDB0_PODLY_DLY1_SHIFT)                 /*!< PDB0_PODLY: DLY1 Mask                   */
#define PDB0_PODLY_DLY1_SHIFT                    16                                                  /*!< PDB0_PODLY: DLY1 Position               */
#define PDB0_PODLY_DLY1(x)                       (((x)<<PDB0_PODLY_DLY1_SHIFT)&PDB0_PODLY_DLY1_MASK) /*!< PDB0_PODLY                              */

/* -------------------------------------------------------------------------------- */
/* -----------     'PDB0' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define PDB0_SC                        (PDB0->SC)
#define PDB0_MOD                       (PDB0->MOD)
#define PDB0_CNT                       (PDB0->CNT)
#define PDB0_IDLY                      (PDB0->IDLY)
#define PDB0_CH0C1                     (PDB0->CH[0].C1)
#define PDB0_CH0S                      (PDB0->CH[0].S)
#define PDB0_CH0DLY0                   (PDB0->CH[0].DLY0)
#define PDB0_CH0DLY1                   (PDB0->CH[0].DLY1)
#define PDB0_CH1C1                     (PDB0->CH[1].C1)
#define PDB0_CH1S                      (PDB0->CH[1].S)
#define PDB0_CH1DLY0                   (PDB0->CH[1].DLY0)
#define PDB0_CH1DLY1                   (PDB0->CH[1].DLY1)
#define PDB0_DAC0INTC                  (PDB0->DAC[0].INTC)
#define PDB0_DAC0INT                   (PDB0->DAC[0].INT)
#define PDB0_DAC1INTC                  (PDB0->DAC[1].INTC)
#define PDB0_DAC1INT                   (PDB0->DAC[1].INT)
#define PDB0_POEN                      (PDB0->POEN)
#define PDB0_PO0DLY                    (PDB0->PODLY[0])

/* ================================================================================ */
/* ================           PMC (file:PMC_0)                     ================ */
/* ================================================================================ */

/**
 * @brief Power Management Controller
 */
typedef struct {                                /*!<       PMC Structure                                                */
   __IO uint8_t   LVDSC1;                       /*!< 0000: Low Voltage Detect Status and Control 1 Register             */
   __IO uint8_t   LVDSC2;                       /*!< 0001: Low Voltage Detect Status and Control 2 Register             */
   __IO uint8_t   REGSC;                        /*!< 0002: Regulator Status and Control Register                        */
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
/* ================           PORTA (file:PORTA_MKV)               ================ */
/* ================================================================================ */

/**
 * @brief Pin Control and Interrupts
 */
typedef struct {                                /*!<       PORTA Structure                                              */
   __IO uint32_t  PCR[32];                      /*!< 0000: Pin Control Register n                                       */
   __O  uint32_t  GPCLR;                        /*!< 0080: Global Pin Control Low Register                              */
   __O  uint32_t  GPCHR;                        /*!< 0084: Global Pin Control High Register                             */
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
#define PORT_ISFR_ISF_MASK                       (0xFFFFFFFFUL << PORT_ISFR_ISF_SHIFT)               /*!< PORTA_ISFR: ISF Mask                    */
#define PORT_ISFR_ISF_SHIFT                      0                                                   /*!< PORTA_ISFR: ISF Position                */
#define PORT_ISFR_ISF(x)                         (((x)<<PORT_ISFR_ISF_SHIFT)&PORT_ISFR_ISF_MASK)     /*!< PORTA_ISFR                              */

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
/* ================           PORTC (derived from PORTB)           ================ */
/* ================================================================================ */

/**
 * @brief Pin Control and Interrupts
 */
typedef PORTB_Type PORTC_Type;  /*!< PORTC Structure                                             */


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
/* ================           PORTD (derived from PORTB)           ================ */
/* ================================================================================ */

/**
 * @brief Pin Control and Interrupts
 */
typedef PORTB_Type PORTD_Type;  /*!< PORTD Structure                                             */


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
/* ================           PORTE (derived from PORTB)           ================ */
/* ================================================================================ */

/**
 * @brief Pin Control and Interrupts
 */
typedef PORTB_Type PORTE_Type;  /*!< PORTE Structure                                             */


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
/* ================           RCM (file:RCM_MKL)                   ================ */
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
} RCM_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'RCM' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- RCM_SRS0                                 ------ */
#define RCM_SRS0_WAKEUP_MASK                     (0x01UL << RCM_SRS0_WAKEUP_SHIFT)                   /*!< RCM_SRS0: WAKEUP Mask                   */
#define RCM_SRS0_WAKEUP_SHIFT                    0                                                   /*!< RCM_SRS0: WAKEUP Position               */
#define RCM_SRS0_LVD_MASK                        (0x01UL << RCM_SRS0_LVD_SHIFT)                      /*!< RCM_SRS0: LVD Mask                      */
#define RCM_SRS0_LVD_SHIFT                       1                                                   /*!< RCM_SRS0: LVD Position                  */
#define RCM_SRS0_LOC_MASK                        (0x01UL << RCM_SRS0_LOC_SHIFT)                      /*!< RCM_SRS0: LOC Mask                      */
#define RCM_SRS0_LOC_SHIFT                       2                                                   /*!< RCM_SRS0: LOC Position                  */
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

/* -------------------------------------------------------------------------------- */
/* -----------     'RCM' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define RCM_SRS0                       (RCM->SRS0)
#define RCM_SRS1                       (RCM->SRS1)
#define RCM_RPFC                       (RCM->RPFC)
#define RCM_RPFW                       (RCM->RPFW)

/* ================================================================================ */
/* ================           ROM (file:ROM_0)                     ================ */
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
/* ================           SIM (file:SIM_MKV10Z7)               ================ */
/* ================================================================================ */

/**
 * @brief System Integration Module
 */
typedef struct {                                /*!<       SIM Structure                                                */
   __IO uint32_t  SOPT1;                        /*!< 0000: System Options Register 1                                    */
   __I  uint32_t  RESERVED0[1024];              /*!< 0004:                                                              */
   __IO uint32_t  SOPT2;                        /*!< 1004: System Options Register 2                                    */
   __I  uint32_t  RESERVED1;                    /*!< 1008:                                                              */
   __IO uint32_t  SOPT4;                        /*!< 100C: System Options Register 4                                    */
   __IO uint32_t  SOPT5;                        /*!< 1010: System Options Register 5                                    */
   __I  uint32_t  RESERVED2;                    /*!< 1014:                                                              */
   __IO uint32_t  SOPT7;                        /*!< 1018: System Options Register 7                                    */
   __IO uint32_t  SOPT8;                        /*!< 101C: System Options Register 8                                    */
   __I  uint32_t  RESERVED3;                    /*!< 1020:                                                              */
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
   __IO uint32_t  WDOGCTRL;                     /*!< 1100: WDOG Control Register                                        */
} SIM_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'SIM' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- SIM_SOPT1                                ------ */
#define SIM__SOPT1_OSC32KSEL_MASK                (0x03UL << SIM__SOPT1_OSC32KSEL_SHIFT)              /*!< SIM__SOPT1: OSC32KSEL Mask              */
#define SIM__SOPT1_OSC32KSEL_SHIFT               18                                                  /*!< SIM__SOPT1: OSC32KSEL Position          */
#define SIM__SOPT1_OSC32KSEL(x)                  (((x)<<SIM__SOPT1_OSC32KSEL_SHIFT)&SIM__SOPT1_OSC32KSEL_MASK) /*!< SIM__SOPT1                              */

/* ------- SIM_SOPT2                                ------ */
#define SIM__SOPT2_CLKOUTSEL_MASK                (0x07UL << SIM__SOPT2_CLKOUTSEL_SHIFT)              /*!< SIM__SOPT2: CLKOUTSEL Mask              */
#define SIM__SOPT2_CLKOUTSEL_SHIFT               5                                                   /*!< SIM__SOPT2: CLKOUTSEL Position          */
#define SIM__SOPT2_CLKOUTSEL(x)                  (((x)<<SIM__SOPT2_CLKOUTSEL_SHIFT)&SIM__SOPT2_CLKOUTSEL_MASK) /*!< SIM__SOPT2                              */
#define SIM__SOPT2_FTMFFCLKSEL_MASK              (0x03UL << SIM__SOPT2_FTMFFCLKSEL_SHIFT)            /*!< SIM__SOPT2: FTMFFCLKSEL Mask            */
#define SIM__SOPT2_FTMFFCLKSEL_SHIFT             24                                                  /*!< SIM__SOPT2: FTMFFCLKSEL Position        */
#define SIM__SOPT2_FTMFFCLKSEL(x)                (((x)<<SIM__SOPT2_FTMFFCLKSEL_SHIFT)&SIM__SOPT2_FTMFFCLKSEL_MASK) /*!< SIM__SOPT2                              */

/* ------- SIM_SOPT4                                ------ */
#define SIM__SOPT4_FTM0FLT0_MASK                 (0x01UL << SIM__SOPT4_FTM0FLT0_SHIFT)               /*!< SIM__SOPT4: FTM0FLT0 Mask               */
#define SIM__SOPT4_FTM0FLT0_SHIFT                0                                                   /*!< SIM__SOPT4: FTM0FLT0 Position           */
#define SIM__SOPT4_FTM0FLT1_MASK                 (0x01UL << SIM__SOPT4_FTM0FLT1_SHIFT)               /*!< SIM__SOPT4: FTM0FLT1 Mask               */
#define SIM__SOPT4_FTM0FLT1_SHIFT                1                                                   /*!< SIM__SOPT4: FTM0FLT1 Position           */
#define SIM__SOPT4_FTM1FLT0_MASK                 (0x01UL << SIM__SOPT4_FTM1FLT0_SHIFT)               /*!< SIM__SOPT4: FTM1FLT0 Mask               */
#define SIM__SOPT4_FTM1FLT0_SHIFT                2                                                   /*!< SIM__SOPT4: FTM1FLT0 Position           */
#define SIM__SOPT4_FTM2FLT0_MASK                 (0x01UL << SIM__SOPT4_FTM2FLT0_SHIFT)               /*!< SIM__SOPT4: FTM2FLT0 Mask               */
#define SIM__SOPT4_FTM2FLT0_SHIFT                3                                                   /*!< SIM__SOPT4: FTM2FLT0 Position           */
#define SIM__SOPT4_FTM0TRG0SRC_MASK              (0x01UL << SIM__SOPT4_FTM0TRG0SRC_SHIFT)            /*!< SIM__SOPT4: FTM0TRG0SRC Mask            */
#define SIM__SOPT4_FTM0TRG0SRC_SHIFT             7                                                   /*!< SIM__SOPT4: FTM0TRG0SRC Position        */
#define SIM__SOPT4_FTM0TRG1SRC_MASK              (0x01UL << SIM__SOPT4_FTM0TRG1SRC_SHIFT)            /*!< SIM__SOPT4: FTM0TRG1SRC Mask            */
#define SIM__SOPT4_FTM0TRG1SRC_SHIFT             8                                                   /*!< SIM__SOPT4: FTM0TRG1SRC Position        */
#define SIM__SOPT4_FTM0TRG2SRC_MASK              (0x01UL << SIM__SOPT4_FTM0TRG2SRC_SHIFT)            /*!< SIM__SOPT4: FTM0TRG2SRC Mask            */
#define SIM__SOPT4_FTM0TRG2SRC_SHIFT             9                                                   /*!< SIM__SOPT4: FTM0TRG2SRC Position        */
#define SIM__SOPT4_FTM1TRG0SRC_MASK              (0x01UL << SIM__SOPT4_FTM1TRG0SRC_SHIFT)            /*!< SIM__SOPT4: FTM1TRG0SRC Mask            */
#define SIM__SOPT4_FTM1TRG0SRC_SHIFT             10                                                  /*!< SIM__SOPT4: FTM1TRG0SRC Position        */
#define SIM__SOPT4_FTM1TRG1SRC_MASK              (0x01UL << SIM__SOPT4_FTM1TRG1SRC_SHIFT)            /*!< SIM__SOPT4: FTM1TRG1SRC Mask            */
#define SIM__SOPT4_FTM1TRG1SRC_SHIFT             11                                                  /*!< SIM__SOPT4: FTM1TRG1SRC Position        */
#define SIM__SOPT4_FTM1TRG2SRC_MASK              (0x01UL << SIM__SOPT4_FTM1TRG2SRC_SHIFT)            /*!< SIM__SOPT4: FTM1TRG2SRC Mask            */
#define SIM__SOPT4_FTM1TRG2SRC_SHIFT             12                                                  /*!< SIM__SOPT4: FTM1TRG2SRC Position        */
#define SIM__SOPT4_FTM2TRG0SRC_MASK              (0x01UL << SIM__SOPT4_FTM2TRG0SRC_SHIFT)            /*!< SIM__SOPT4: FTM2TRG0SRC Mask            */
#define SIM__SOPT4_FTM2TRG0SRC_SHIFT             13                                                  /*!< SIM__SOPT4: FTM2TRG0SRC Position        */
#define SIM__SOPT4_FTM2TRG1SRC_MASK              (0x01UL << SIM__SOPT4_FTM2TRG1SRC_SHIFT)            /*!< SIM__SOPT4: FTM2TRG1SRC Mask            */
#define SIM__SOPT4_FTM2TRG1SRC_SHIFT             14                                                  /*!< SIM__SOPT4: FTM2TRG1SRC Position        */
#define SIM__SOPT4_FTM2TRG2SRC_MASK              (0x01UL << SIM__SOPT4_FTM2TRG2SRC_SHIFT)            /*!< SIM__SOPT4: FTM2TRG2SRC Mask            */
#define SIM__SOPT4_FTM2TRG2SRC_SHIFT             15                                                  /*!< SIM__SOPT4: FTM2TRG2SRC Position        */
#define SIM__SOPT4_FTM1ICH0SRC_MASK              (0x03UL << SIM__SOPT4_FTM1ICH0SRC_SHIFT)            /*!< SIM__SOPT4: FTM1ICH0SRC Mask            */
#define SIM__SOPT4_FTM1ICH0SRC_SHIFT             18                                                  /*!< SIM__SOPT4: FTM1ICH0SRC Position        */
#define SIM__SOPT4_FTM1ICH0SRC(x)                (((x)<<SIM__SOPT4_FTM1ICH0SRC_SHIFT)&SIM__SOPT4_FTM1ICH0SRC_MASK) /*!< SIM__SOPT4                              */
#define SIM__SOPT4_FTM2ICH0SRC_MASK              (0x03UL << SIM__SOPT4_FTM2ICH0SRC_SHIFT)            /*!< SIM__SOPT4: FTM2ICH0SRC Mask            */
#define SIM__SOPT4_FTM2ICH0SRC_SHIFT             20                                                  /*!< SIM__SOPT4: FTM2ICH0SRC Position        */
#define SIM__SOPT4_FTM2ICH0SRC(x)                (((x)<<SIM__SOPT4_FTM2ICH0SRC_SHIFT)&SIM__SOPT4_FTM2ICH0SRC_MASK) /*!< SIM__SOPT4                              */
#define SIM__SOPT4_FTM2ICH1SRC_MASK              (0x01UL << SIM__SOPT4_FTM2ICH1SRC_SHIFT)            /*!< SIM__SOPT4: FTM2ICH1SRC Mask            */
#define SIM__SOPT4_FTM2ICH1SRC_SHIFT             22                                                  /*!< SIM__SOPT4: FTM2ICH1SRC Position        */
#define SIM__SOPT4_FTM0CLKSEL_MASK               (0x03UL << SIM__SOPT4_FTM0CLKSEL_SHIFT)             /*!< SIM__SOPT4: FTM0CLKSEL Mask             */
#define SIM__SOPT4_FTM0CLKSEL_SHIFT              24                                                  /*!< SIM__SOPT4: FTM0CLKSEL Position         */
#define SIM__SOPT4_FTM0CLKSEL(x)                 (((x)<<SIM__SOPT4_FTM0CLKSEL_SHIFT)&SIM__SOPT4_FTM0CLKSEL_MASK) /*!< SIM__SOPT4                              */
#define SIM__SOPT4_FTM1CLKSEL_MASK               (0x03UL << SIM__SOPT4_FTM1CLKSEL_SHIFT)             /*!< SIM__SOPT4: FTM1CLKSEL Mask             */
#define SIM__SOPT4_FTM1CLKSEL_SHIFT              26                                                  /*!< SIM__SOPT4: FTM1CLKSEL Position         */
#define SIM__SOPT4_FTM1CLKSEL(x)                 (((x)<<SIM__SOPT4_FTM1CLKSEL_SHIFT)&SIM__SOPT4_FTM1CLKSEL_MASK) /*!< SIM__SOPT4                              */
#define SIM__SOPT4_FTM2CLKSEL_MASK               (0x03UL << SIM__SOPT4_FTM2CLKSEL_SHIFT)             /*!< SIM__SOPT4: FTM2CLKSEL Mask             */
#define SIM__SOPT4_FTM2CLKSEL_SHIFT              28                                                  /*!< SIM__SOPT4: FTM2CLKSEL Position         */
#define SIM__SOPT4_FTM2CLKSEL(x)                 (((x)<<SIM__SOPT4_FTM2CLKSEL_SHIFT)&SIM__SOPT4_FTM2CLKSEL_MASK) /*!< SIM__SOPT4                              */

/* ------- SIM_SOPT5                                ------ */
#define SIM__SOPT5_UART0TXSRC_MASK               (0x03UL << SIM__SOPT5_UART0TXSRC_SHIFT)             /*!< SIM__SOPT5: UART0TXSRC Mask             */
#define SIM__SOPT5_UART0TXSRC_SHIFT              0                                                   /*!< SIM__SOPT5: UART0TXSRC Position         */
#define SIM__SOPT5_UART0TXSRC(x)                 (((x)<<SIM__SOPT5_UART0TXSRC_SHIFT)&SIM__SOPT5_UART0TXSRC_MASK) /*!< SIM__SOPT5                              */
#define SIM__SOPT5_UART0RXSRC_MASK               (0x03UL << SIM__SOPT5_UART0RXSRC_SHIFT)             /*!< SIM__SOPT5: UART0RXSRC Mask             */
#define SIM__SOPT5_UART0RXSRC_SHIFT              2                                                   /*!< SIM__SOPT5: UART0RXSRC Position         */
#define SIM__SOPT5_UART0RXSRC(x)                 (((x)<<SIM__SOPT5_UART0RXSRC_SHIFT)&SIM__SOPT5_UART0RXSRC_MASK) /*!< SIM__SOPT5                              */
#define SIM__SOPT5_UART1TXSRC_MASK               (0x03UL << SIM__SOPT5_UART1TXSRC_SHIFT)             /*!< SIM__SOPT5: UART1TXSRC Mask             */
#define SIM__SOPT5_UART1TXSRC_SHIFT              4                                                   /*!< SIM__SOPT5: UART1TXSRC Position         */
#define SIM__SOPT5_UART1TXSRC(x)                 (((x)<<SIM__SOPT5_UART1TXSRC_SHIFT)&SIM__SOPT5_UART1TXSRC_MASK) /*!< SIM__SOPT5                              */
#define SIM__SOPT5_UART1RXSRC_MASK               (0x03UL << SIM__SOPT5_UART1RXSRC_SHIFT)             /*!< SIM__SOPT5: UART1RXSRC Mask             */
#define SIM__SOPT5_UART1RXSRC_SHIFT              6                                                   /*!< SIM__SOPT5: UART1RXSRC Position         */
#define SIM__SOPT5_UART1RXSRC(x)                 (((x)<<SIM__SOPT5_UART1RXSRC_SHIFT)&SIM__SOPT5_UART1RXSRC_MASK) /*!< SIM__SOPT5                              */
#define SIM__SOPT5_UART0ODE_MASK                 (0x01UL << SIM__SOPT5_UART0ODE_SHIFT)               /*!< SIM__SOPT5: UART0ODE Mask               */
#define SIM__SOPT5_UART0ODE_SHIFT                16                                                  /*!< SIM__SOPT5: UART0ODE Position           */
#define SIM__SOPT5_UART1ODE_MASK                 (0x01UL << SIM__SOPT5_UART1ODE_SHIFT)               /*!< SIM__SOPT5: UART1ODE Mask               */
#define SIM__SOPT5_UART1ODE_SHIFT                17                                                  /*!< SIM__SOPT5: UART1ODE Position           */

/* ------- SIM_SOPT7                                ------ */
#define SIM__SOPT7_ADC0TRGSEL_MASK               (0x0FUL << SIM__SOPT7_ADC0TRGSEL_SHIFT)             /*!< SIM__SOPT7: ADC0TRGSEL Mask             */
#define SIM__SOPT7_ADC0TRGSEL_SHIFT              0                                                   /*!< SIM__SOPT7: ADC0TRGSEL Position         */
#define SIM__SOPT7_ADC0TRGSEL(x)                 (((x)<<SIM__SOPT7_ADC0TRGSEL_SHIFT)&SIM__SOPT7_ADC0TRGSEL_MASK) /*!< SIM__SOPT7                              */
#define SIM__SOPT7_ADC0PRETRGSEL_MASK            (0x01UL << SIM__SOPT7_ADC0PRETRGSEL_SHIFT)          /*!< SIM__SOPT7: ADC0PRETRGSEL Mask          */
#define SIM__SOPT7_ADC0PRETRGSEL_SHIFT           4                                                   /*!< SIM__SOPT7: ADC0PRETRGSEL Position      */
#define SIM__SOPT7_ADC0ALTTRGEN_MASK             (0x01UL << SIM__SOPT7_ADC0ALTTRGEN_SHIFT)           /*!< SIM__SOPT7: ADC0ALTTRGEN Mask           */
#define SIM__SOPT7_ADC0ALTTRGEN_SHIFT            7                                                   /*!< SIM__SOPT7: ADC0ALTTRGEN Position       */
#define SIM__SOPT7_ADC1TRGSEL_MASK               (0x0FUL << SIM__SOPT7_ADC1TRGSEL_SHIFT)             /*!< SIM__SOPT7: ADC1TRGSEL Mask             */
#define SIM__SOPT7_ADC1TRGSEL_SHIFT              8                                                   /*!< SIM__SOPT7: ADC1TRGSEL Position         */
#define SIM__SOPT7_ADC1TRGSEL(x)                 (((x)<<SIM__SOPT7_ADC1TRGSEL_SHIFT)&SIM__SOPT7_ADC1TRGSEL_MASK) /*!< SIM__SOPT7                              */
#define SIM__SOPT7_ADC1PRETRGSEL_MASK            (0x01UL << SIM__SOPT7_ADC1PRETRGSEL_SHIFT)          /*!< SIM__SOPT7: ADC1PRETRGSEL Mask          */
#define SIM__SOPT7_ADC1PRETRGSEL_SHIFT           12                                                  /*!< SIM__SOPT7: ADC1PRETRGSEL Position      */
#define SIM__SOPT7_ADC1ALTTRGEN_MASK             (0x01UL << SIM__SOPT7_ADC1ALTTRGEN_SHIFT)           /*!< SIM__SOPT7: ADC1ALTTRGEN Mask           */
#define SIM__SOPT7_ADC1ALTTRGEN_SHIFT            15                                                  /*!< SIM__SOPT7: ADC1ALTTRGEN Position       */
#define SIM__SOPT7_ADC0ALTCLKSRC_MASK            (0x03UL << SIM__SOPT7_ADC0ALTCLKSRC_SHIFT)          /*!< SIM__SOPT7: ADC0ALTCLKSRC Mask          */
#define SIM__SOPT7_ADC0ALTCLKSRC_SHIFT           24                                                  /*!< SIM__SOPT7: ADC0ALTCLKSRC Position      */
#define SIM__SOPT7_ADC0ALTCLKSRC(x)              (((x)<<SIM__SOPT7_ADC0ALTCLKSRC_SHIFT)&SIM__SOPT7_ADC0ALTCLKSRC_MASK) /*!< SIM__SOPT7                              */
#define SIM__SOPT7_ADC1ALTCLKSRC_MASK            (0x03UL << SIM__SOPT7_ADC1ALTCLKSRC_SHIFT)          /*!< SIM__SOPT7: ADC1ALTCLKSRC Mask          */
#define SIM__SOPT7_ADC1ALTCLKSRC_SHIFT           26                                                  /*!< SIM__SOPT7: ADC1ALTCLKSRC Position      */
#define SIM__SOPT7_ADC1ALTCLKSRC(x)              (((x)<<SIM__SOPT7_ADC1ALTCLKSRC_SHIFT)&SIM__SOPT7_ADC1ALTCLKSRC_MASK) /*!< SIM__SOPT7                              */

/* ------- SIM_SOPT8                                ------ */
#define SIM__SOPT8_FTM0SYNCBIT_MASK              (0x01UL << SIM__SOPT8_FTM0SYNCBIT_SHIFT)            /*!< SIM__SOPT8: FTM0SYNCBIT Mask            */
#define SIM__SOPT8_FTM0SYNCBIT_SHIFT             0                                                   /*!< SIM__SOPT8: FTM0SYNCBIT Position        */
#define SIM__SOPT8_FTM1SYNCBIT_MASK              (0x01UL << SIM__SOPT8_FTM1SYNCBIT_SHIFT)            /*!< SIM__SOPT8: FTM1SYNCBIT Mask            */
#define SIM__SOPT8_FTM1SYNCBIT_SHIFT             1                                                   /*!< SIM__SOPT8: FTM1SYNCBIT Position        */
#define SIM__SOPT8_FTM2SYNCBIT_MASK              (0x01UL << SIM__SOPT8_FTM2SYNCBIT_SHIFT)            /*!< SIM__SOPT8: FTM2SYNCBIT Mask            */
#define SIM__SOPT8_FTM2SYNCBIT_SHIFT             2                                                   /*!< SIM__SOPT8: FTM2SYNCBIT Position        */
#define SIM__SOPT8_CARRIER_SELECT_MASK           (0x01UL << SIM__SOPT8_CARRIER_SELECT_SHIFT)         /*!< SIM__SOPT8: CARRIER_SELECT Mask         */
#define SIM__SOPT8_CARRIER_SELECT_SHIFT          8                                                   /*!< SIM__SOPT8: CARRIER_SELECT Position     */
#define SIM__SOPT8_FTM0OCH0SRC_MASK              (0x01UL << SIM__SOPT8_FTM0OCH0SRC_SHIFT)            /*!< SIM__SOPT8: FTM0OCH0SRC Mask            */
#define SIM__SOPT8_FTM0OCH0SRC_SHIFT             16                                                  /*!< SIM__SOPT8: FTM0OCH0SRC Position        */
#define SIM__SOPT8_FTM0OCH1SRC_MASK              (0x01UL << SIM__SOPT8_FTM0OCH1SRC_SHIFT)            /*!< SIM__SOPT8: FTM0OCH1SRC Mask            */
#define SIM__SOPT8_FTM0OCH1SRC_SHIFT             17                                                  /*!< SIM__SOPT8: FTM0OCH1SRC Position        */
#define SIM__SOPT8_FTM0OCH2SRC_MASK              (0x01UL << SIM__SOPT8_FTM0OCH2SRC_SHIFT)            /*!< SIM__SOPT8: FTM0OCH2SRC Mask            */
#define SIM__SOPT8_FTM0OCH2SRC_SHIFT             18                                                  /*!< SIM__SOPT8: FTM0OCH2SRC Position        */
#define SIM__SOPT8_FTM0OCH3SRC_MASK              (0x01UL << SIM__SOPT8_FTM0OCH3SRC_SHIFT)            /*!< SIM__SOPT8: FTM0OCH3SRC Mask            */
#define SIM__SOPT8_FTM0OCH3SRC_SHIFT             19                                                  /*!< SIM__SOPT8: FTM0OCH3SRC Position        */
#define SIM__SOPT8_FTM0OCH4SRC_MASK              (0x01UL << SIM__SOPT8_FTM0OCH4SRC_SHIFT)            /*!< SIM__SOPT8: FTM0OCH4SRC Mask            */
#define SIM__SOPT8_FTM0OCH4SRC_SHIFT             20                                                  /*!< SIM__SOPT8: FTM0OCH4SRC Position        */
#define SIM__SOPT8_FTM0OCH5SRC_MASK              (0x01UL << SIM__SOPT8_FTM0OCH5SRC_SHIFT)            /*!< SIM__SOPT8: FTM0OCH5SRC Mask            */
#define SIM__SOPT8_FTM0OCH5SRC_SHIFT             21                                                  /*!< SIM__SOPT8: FTM0OCH5SRC Position        */
#define SIM__SOPT8_FTM2OCH0SRC_MASK              (0x01UL << SIM__SOPT8_FTM2OCH0SRC_SHIFT)            /*!< SIM__SOPT8: FTM2OCH0SRC Mask            */
#define SIM__SOPT8_FTM2OCH0SRC_SHIFT             22                                                  /*!< SIM__SOPT8: FTM2OCH0SRC Position        */
#define SIM__SOPT8_FTM2OCH1SRC_MASK              (0x01UL << SIM__SOPT8_FTM2OCH1SRC_SHIFT)            /*!< SIM__SOPT8: FTM2OCH1SRC Mask            */
#define SIM__SOPT8_FTM2OCH1SRC_SHIFT             23                                                  /*!< SIM__SOPT8: FTM2OCH1SRC Position        */

/* ------- SIM_SDID                                 ------ */
#define SIM__SDID_PINID_MASK                     (0x0FUL << SIM__SDID_PINID_SHIFT)                   /*!< SIM__SDID: PINID Mask                   */
#define SIM__SDID_PINID_SHIFT                    0                                                   /*!< SIM__SDID: PINID Position               */
#define SIM__SDID_PINID(x)                       (((x)<<SIM__SDID_PINID_SHIFT)&SIM__SDID_PINID_MASK) /*!< SIM__SDID                               */
#define SIM__SDID_DIEID_MASK                     (0x1FUL << SIM__SDID_DIEID_SHIFT)                   /*!< SIM__SDID: DIEID Mask                   */
#define SIM__SDID_DIEID_SHIFT                    7                                                   /*!< SIM__SDID: DIEID Position               */
#define SIM__SDID_DIEID(x)                       (((x)<<SIM__SDID_DIEID_SHIFT)&SIM__SDID_DIEID_MASK) /*!< SIM__SDID                               */
#define SIM__SDID_REVID_MASK                     (0x0FUL << SIM__SDID_REVID_SHIFT)                   /*!< SIM__SDID: REVID Mask                   */
#define SIM__SDID_REVID_SHIFT                    12                                                  /*!< SIM__SDID: REVID Position               */
#define SIM__SDID_REVID(x)                       (((x)<<SIM__SDID_REVID_SHIFT)&SIM__SDID_REVID_MASK) /*!< SIM__SDID                               */
#define SIM__SDID_SRAMSIZE_MASK                  (0x0FUL << SIM__SDID_SRAMSIZE_SHIFT)                /*!< SIM__SDID: SRAMSIZE Mask                */
#define SIM__SDID_SRAMSIZE_SHIFT                 16                                                  /*!< SIM__SDID: SRAMSIZE Position            */
#define SIM__SDID_SRAMSIZE(x)                    (((x)<<SIM__SDID_SRAMSIZE_SHIFT)&SIM__SDID_SRAMSIZE_MASK) /*!< SIM__SDID                               */
#define SIM__SDID_SERIERID_MASK                  (0x0FUL << SIM__SDID_SERIERID_SHIFT)                /*!< SIM__SDID: SERIERID Mask                */
#define SIM__SDID_SERIERID_SHIFT                 20                                                  /*!< SIM__SDID: SERIERID Position            */
#define SIM__SDID_SERIERID(x)                    (((x)<<SIM__SDID_SERIERID_SHIFT)&SIM__SDID_SERIERID_MASK) /*!< SIM__SDID                               */
#define SIM__SDID_SUBFAMID_MASK                  (0x0FUL << SIM__SDID_SUBFAMID_SHIFT)                /*!< SIM__SDID: SUBFAMID Mask                */
#define SIM__SDID_SUBFAMID_SHIFT                 24                                                  /*!< SIM__SDID: SUBFAMID Position            */
#define SIM__SDID_SUBFAMID(x)                    (((x)<<SIM__SDID_SUBFAMID_SHIFT)&SIM__SDID_SUBFAMID_MASK) /*!< SIM__SDID                               */
#define SIM__SDID_FAMID_MASK                     (0x0FUL << SIM__SDID_FAMID_SHIFT)                   /*!< SIM__SDID: FAMID Mask                   */
#define SIM__SDID_FAMID_SHIFT                    28                                                  /*!< SIM__SDID: FAMID Position               */
#define SIM__SDID_FAMID(x)                       (((x)<<SIM__SDID_FAMID_SHIFT)&SIM__SDID_FAMID_MASK) /*!< SIM__SDID                               */

/* ------- SIM_SCGC4                                ------ */
#define SIM__SCGC4_EWM_MASK                      (0x01UL << SIM__SCGC4_EWM_SHIFT)                    /*!< SIM__SCGC4: EWM Mask                    */
#define SIM__SCGC4_EWM_SHIFT                     1                                                   /*!< SIM__SCGC4: EWM Position                */
#define SIM__SCGC4_I2C0_MASK                     (0x01UL << SIM__SCGC4_I2C0_SHIFT)                   /*!< SIM__SCGC4: I2C0 Mask                   */
#define SIM__SCGC4_I2C0_SHIFT                    6                                                   /*!< SIM__SCGC4: I2C0 Position               */
#define SIM__SCGC4_UART0_MASK                    (0x01UL << SIM__SCGC4_UART0_SHIFT)                  /*!< SIM__SCGC4: UART0 Mask                  */
#define SIM__SCGC4_UART0_SHIFT                   10                                                  /*!< SIM__SCGC4: UART0 Position              */
#define SIM__SCGC4_UART1_MASK                    (0x01UL << SIM__SCGC4_UART1_SHIFT)                  /*!< SIM__SCGC4: UART1 Mask                  */
#define SIM__SCGC4_UART1_SHIFT                   11                                                  /*!< SIM__SCGC4: UART1 Position              */
#define SIM__SCGC4_CMP_MASK                      (0x01UL << SIM__SCGC4_CMP_SHIFT)                    /*!< SIM__SCGC4: CMP Mask                    */
#define SIM__SCGC4_CMP_SHIFT                     19                                                  /*!< SIM__SCGC4: CMP Position                */

/* ------- SIM_SCGC5                                ------ */
#define SIM__SCGC5_LPTMR_MASK                    (0x01UL << SIM__SCGC5_LPTMR_SHIFT)                  /*!< SIM__SCGC5: LPTMR Mask                  */
#define SIM__SCGC5_LPTMR_SHIFT                   0                                                   /*!< SIM__SCGC5: LPTMR Position              */
#define SIM__SCGC5_PORTA_MASK                    (0x01UL << SIM__SCGC5_PORTA_SHIFT)                  /*!< SIM__SCGC5: PORTA Mask                  */
#define SIM__SCGC5_PORTA_SHIFT                   9                                                   /*!< SIM__SCGC5: PORTA Position              */
#define SIM__SCGC5_PORTB_MASK                    (0x01UL << SIM__SCGC5_PORTB_SHIFT)                  /*!< SIM__SCGC5: PORTB Mask                  */
#define SIM__SCGC5_PORTB_SHIFT                   10                                                  /*!< SIM__SCGC5: PORTB Position              */
#define SIM__SCGC5_PORTC_MASK                    (0x01UL << SIM__SCGC5_PORTC_SHIFT)                  /*!< SIM__SCGC5: PORTC Mask                  */
#define SIM__SCGC5_PORTC_SHIFT                   11                                                  /*!< SIM__SCGC5: PORTC Position              */
#define SIM__SCGC5_PORTD_MASK                    (0x01UL << SIM__SCGC5_PORTD_SHIFT)                  /*!< SIM__SCGC5: PORTD Mask                  */
#define SIM__SCGC5_PORTD_SHIFT                   12                                                  /*!< SIM__SCGC5: PORTD Position              */
#define SIM__SCGC5_PORTE_MASK                    (0x01UL << SIM__SCGC5_PORTE_SHIFT)                  /*!< SIM__SCGC5: PORTE Mask                  */
#define SIM__SCGC5_PORTE_SHIFT                   13                                                  /*!< SIM__SCGC5: PORTE Position              */

/* ------- SIM_SCGC6                                ------ */
#define SIM__SCGC6_FTF_MASK                      (0x01UL << SIM__SCGC6_FTF_SHIFT)                    /*!< SIM__SCGC6: FTF Mask                    */
#define SIM__SCGC6_FTF_SHIFT                     0                                                   /*!< SIM__SCGC6: FTF Position                */
#define SIM__SCGC6_DMAMUX_MASK                   (0x01UL << SIM__SCGC6_DMAMUX_SHIFT)                 /*!< SIM__SCGC6: DMAMUX Mask                 */
#define SIM__SCGC6_DMAMUX_SHIFT                  1                                                   /*!< SIM__SCGC6: DMAMUX Position             */
#define SIM__SCGC6_SPI0_MASK                     (0x01UL << SIM__SCGC6_SPI0_SHIFT)                   /*!< SIM__SCGC6: SPI0 Mask                   */
#define SIM__SCGC6_SPI0_SHIFT                    12                                                  /*!< SIM__SCGC6: SPI0 Position               */
#define SIM__SCGC6_CRC_MASK                      (0x01UL << SIM__SCGC6_CRC_SHIFT)                    /*!< SIM__SCGC6: CRC Mask                    */
#define SIM__SCGC6_CRC_SHIFT                     18                                                  /*!< SIM__SCGC6: CRC Position                */
#define SIM__SCGC6_PDB_MASK                      (0x01UL << SIM__SCGC6_PDB_SHIFT)                    /*!< SIM__SCGC6: PDB Mask                    */
#define SIM__SCGC6_PDB_SHIFT                     22                                                  /*!< SIM__SCGC6: PDB Position                */
#define SIM__SCGC6_FTM0_MASK                     (0x01UL << SIM__SCGC6_FTM0_SHIFT)                   /*!< SIM__SCGC6: FTM0 Mask                   */
#define SIM__SCGC6_FTM0_SHIFT                    24                                                  /*!< SIM__SCGC6: FTM0 Position               */
#define SIM__SCGC6_FTM1_MASK                     (0x01UL << SIM__SCGC6_FTM1_SHIFT)                   /*!< SIM__SCGC6: FTM1 Mask                   */
#define SIM__SCGC6_FTM1_SHIFT                    25                                                  /*!< SIM__SCGC6: FTM1 Position               */
#define SIM__SCGC6_FTM2_MASK                     (0x01UL << SIM__SCGC6_FTM2_SHIFT)                   /*!< SIM__SCGC6: FTM2 Mask                   */
#define SIM__SCGC6_FTM2_SHIFT                    26                                                  /*!< SIM__SCGC6: FTM2 Position               */
#define SIM__SCGC6_ADC0_MASK                     (0x01UL << SIM__SCGC6_ADC0_SHIFT)                   /*!< SIM__SCGC6: ADC0 Mask                   */
#define SIM__SCGC6_ADC0_SHIFT                    27                                                  /*!< SIM__SCGC6: ADC0 Position               */
#define SIM__SCGC6_ADC1_MASK                     (0x01UL << SIM__SCGC6_ADC1_SHIFT)                   /*!< SIM__SCGC6: ADC1 Mask                   */
#define SIM__SCGC6_ADC1_SHIFT                    28                                                  /*!< SIM__SCGC6: ADC1 Position               */
#define SIM__SCGC6_DAC0_MASK                     (0x01UL << SIM__SCGC6_DAC0_SHIFT)                   /*!< SIM__SCGC6: DAC0 Mask                   */
#define SIM__SCGC6_DAC0_SHIFT                    31                                                  /*!< SIM__SCGC6: DAC0 Position               */

/* ------- SIM_SCGC7                                ------ */
#define SIM__SCGC7_DMA_MASK                      (0x01UL << SIM__SCGC7_DMA_SHIFT)                    /*!< SIM__SCGC7: DMA Mask                    */
#define SIM__SCGC7_DMA_SHIFT                     8                                                   /*!< SIM__SCGC7: DMA Position                */

/* ------- SIM_CLKDIV1                              ------ */
#define SIM__CLKDIV1_OUTDIV5_MASK                (0x07UL << SIM__CLKDIV1_OUTDIV5_SHIFT)              /*!< SIM__CLKDIV1: OUTDIV5 Mask              */
#define SIM__CLKDIV1_OUTDIV5_SHIFT               12                                                  /*!< SIM__CLKDIV1: OUTDIV5 Position          */
#define SIM__CLKDIV1_OUTDIV5(x)                  (((x)<<SIM__CLKDIV1_OUTDIV5_SHIFT)&SIM__CLKDIV1_OUTDIV5_MASK) /*!< SIM__CLKDIV1                            */
#define SIM__CLKDIV1_OUTDIV5EN_MASK              (0x01UL << SIM__CLKDIV1_OUTDIV5EN_SHIFT)            /*!< SIM__CLKDIV1: OUTDIV5EN Mask            */
#define SIM__CLKDIV1_OUTDIV5EN_SHIFT             15                                                  /*!< SIM__CLKDIV1: OUTDIV5EN Position        */
#define SIM__CLKDIV1_OUTDIV4_MASK                (0x07UL << SIM__CLKDIV1_OUTDIV4_SHIFT)              /*!< SIM__CLKDIV1: OUTDIV4 Mask              */
#define SIM__CLKDIV1_OUTDIV4_SHIFT               16                                                  /*!< SIM__CLKDIV1: OUTDIV4 Position          */
#define SIM__CLKDIV1_OUTDIV4(x)                  (((x)<<SIM__CLKDIV1_OUTDIV4_SHIFT)&SIM__CLKDIV1_OUTDIV4_MASK) /*!< SIM__CLKDIV1                            */
#define SIM__CLKDIV1_OUTDIV1_MASK                (0x0FUL << SIM__CLKDIV1_OUTDIV1_SHIFT)              /*!< SIM__CLKDIV1: OUTDIV1 Mask              */
#define SIM__CLKDIV1_OUTDIV1_SHIFT               28                                                  /*!< SIM__CLKDIV1: OUTDIV1 Position          */
#define SIM__CLKDIV1_OUTDIV1(x)                  (((x)<<SIM__CLKDIV1_OUTDIV1_SHIFT)&SIM__CLKDIV1_OUTDIV1_MASK) /*!< SIM__CLKDIV1                            */

/* ------- SIM_FCFG1                                ------ */
#define SIM__FCFG1_FLASHDIS_MASK                 (0x01UL << SIM__FCFG1_FLASHDIS_SHIFT)               /*!< SIM__FCFG1: FLASHDIS Mask               */
#define SIM__FCFG1_FLASHDIS_SHIFT                0                                                   /*!< SIM__FCFG1: FLASHDIS Position           */
#define SIM__FCFG1_FLASHDOZE_MASK                (0x01UL << SIM__FCFG1_FLASHDOZE_SHIFT)              /*!< SIM__FCFG1: FLASHDOZE Mask              */
#define SIM__FCFG1_FLASHDOZE_SHIFT               1                                                   /*!< SIM__FCFG1: FLASHDOZE Position          */
#define SIM__FCFG1_PFSIZE_MASK                   (0x0FUL << SIM__FCFG1_PFSIZE_SHIFT)                 /*!< SIM__FCFG1: PFSIZE Mask                 */
#define SIM__FCFG1_PFSIZE_SHIFT                  24                                                  /*!< SIM__FCFG1: PFSIZE Position             */
#define SIM__FCFG1_PFSIZE(x)                     (((x)<<SIM__FCFG1_PFSIZE_SHIFT)&SIM__FCFG1_PFSIZE_MASK) /*!< SIM__FCFG1                              */

/* ------- SIM_FCFG2                                ------ */
#define SIM__FCFG2_MAXADDR_MASK                  (0x7FUL << SIM__FCFG2_MAXADDR_SHIFT)                /*!< SIM__FCFG2: MAXADDR Mask                */
#define SIM__FCFG2_MAXADDR_SHIFT                 24                                                  /*!< SIM__FCFG2: MAXADDR Position            */
#define SIM__FCFG2_MAXADDR(x)                    (((x)<<SIM__FCFG2_MAXADDR_SHIFT)&SIM__FCFG2_MAXADDR_MASK) /*!< SIM__FCFG2                              */

/* ------- SIM_UIDMH                                ------ */
#define SIM__UIDMH_UID_MASK                      (0xFFFFFFFFUL << SIM__UIDMH_UID_SHIFT)              /*!< SIM__UIDMH: UID Mask                    */
#define SIM__UIDMH_UID_SHIFT                     0                                                   /*!< SIM__UIDMH: UID Position                */
#define SIM__UIDMH_UID(x)                        (((x)<<SIM__UIDMH_UID_SHIFT)&SIM__UIDMH_UID_MASK)   /*!< SIM__UIDMH                              */

/* ------- SIM_UIDML                                ------ */
#define SIM__UIDML_UID_MASK                      (0xFFFFFFFFUL << SIM__UIDML_UID_SHIFT)              /*!< SIM__UIDML: UID Mask                    */
#define SIM__UIDML_UID_SHIFT                     0                                                   /*!< SIM__UIDML: UID Position                */
#define SIM__UIDML_UID(x)                        (((x)<<SIM__UIDML_UID_SHIFT)&SIM__UIDML_UID_MASK)   /*!< SIM__UIDML                              */

/* ------- SIM_UIDL                                 ------ */
#define SIM__UIDL_UID_MASK                       (0xFFFFFFFFUL << SIM__UIDL_UID_SHIFT)               /*!< SIM__UIDL: UID Mask                     */
#define SIM__UIDL_UID_SHIFT                      0                                                   /*!< SIM__UIDL: UID Position                 */
#define SIM__UIDL_UID(x)                         (((x)<<SIM__UIDL_UID_SHIFT)&SIM__UIDL_UID_MASK)     /*!< SIM__UIDL                               */

/* ------- SIM_WDOGCTRL                             ------ */
#define SIM__WDOGCTRL_WDOGCLKS_MASK              (0x01UL << SIM__WDOGCTRL_WDOGCLKS_SHIFT)            /*!< SIM__WDOGCTRL: WDOGCLKS Mask            */
#define SIM__WDOGCTRL_WDOGCLKS_SHIFT             1                                                   /*!< SIM__WDOGCTRL: WDOGCLKS Position        */

/* -------------------------------------------------------------------------------- */
/* -----------     'SIM' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define SIM_SOPT1                      (SIM->SOPT1)
#define SIM_SOPT2                      (SIM->SOPT2)
#define SIM_SOPT4                      (SIM->SOPT4)
#define SIM_SOPT5                      (SIM->SOPT5)
#define SIM_SOPT7                      (SIM->SOPT7)
#define SIM_SOPT8                      (SIM->SOPT8)
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
#define SIM_WDOGCTRL                   (SIM->WDOGCTRL)

/* ================================================================================ */
/* ================           SMC (file:SMC_MKV)                   ================ */
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
#define SMC_STOPCTRL_LPOPO_MASK                  (0x01UL << SMC_STOPCTRL_LPOPO_SHIFT)                /*!< SMC_STOPCTRL: LPOPO Mask                */
#define SMC_STOPCTRL_LPOPO_SHIFT                 3                                                   /*!< SMC_STOPCTRL: LPOPO Position            */
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
/* ================           SPI0 (file:SPI0_MKV)                 ================ */
/* ================================================================================ */

/**
 * @brief Serial Peripheral Interface
 */
typedef struct {                                /*!<       SPI0 Structure                                               */
   __IO uint32_t  MCR;                          /*!< 0000: Module Configuration Register                                */
   __I  uint32_t  RESERVED0;                    /*!< 0004:                                                              */
   __IO uint32_t  TCR;                          /*!< 0008: Transfer Count Register                                      */
   union {                                      /*!< 0000: (size=0008)                                                  */
      __IO uint32_t  CTAR[2];                   /*!< 000C: Clock and Transfer Attributes Register (In Master Mode)      */
      __IO uint32_t  CTAR_SLAVE;                /*!< 000C: Clock and Transfer Attributes Register (In Slave Mode)       */
   };
   __I  uint32_t  RESERVED1[6];                 /*!< 0014:                                                              */
   __IO uint32_t  SR;                           /*!< 002C: Status Register                                              */
   __IO uint32_t  RSER;                         /*!< 0030: DMA/Interrupt Request Select and Enable Register             */
   union {                                      /*!< 0000: (size=0004)                                                  */
      __IO uint32_t  PUSHR;                     /*!< 0034: PUSH TX FIFO Register In Master Mode                         */
      __IO uint32_t  PUSHR_SLAVE;               /*!< 0034: PUSH TX FIFO Register In Slave Mode                          */
   };
   __I  uint32_t  POPR;                         /*!< 0038: POP RX FIFO Register                                         */
   __I  uint32_t  TXFR[4];                      /*!< 003C: Transmit FIFO                                                */
   __I  uint32_t  RESERVED2[12];                /*!< 004C:                                                              */
   __I  uint32_t  RXFR[4];                      /*!< 007C: Receive FIFO                                                 */
   __I  uint32_t  RESERVED3[44];                /*!< 008C:                                                              */
   __IO uint32_t  SREX;                         /*!< 013C: Status Register Extended                                     */
} SPI0_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'SPI0' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- SPI0_MCR                                 ------ */
#define SPI_MCR_HALT_MASK                        (0x01UL << SPI_MCR_HALT_SHIFT)                      /*!< SPI0_MCR: HALT Mask                     */
#define SPI_MCR_HALT_SHIFT                       0                                                   /*!< SPI0_MCR: HALT Position                 */
#define SPI_MCR_SMPL_PT_MASK                     (0x03UL << SPI_MCR_SMPL_PT_SHIFT)                   /*!< SPI0_MCR: SMPL_PT Mask                  */
#define SPI_MCR_SMPL_PT_SHIFT                    8                                                   /*!< SPI0_MCR: SMPL_PT Position              */
#define SPI_MCR_SMPL_PT(x)                       (((x)<<SPI_MCR_SMPL_PT_SHIFT)&SPI_MCR_SMPL_PT_MASK) /*!< SPI0_MCR                                */
#define SPI_MCR_CLR_RXF_MASK                     (0x01UL << SPI_MCR_CLR_RXF_SHIFT)                   /*!< SPI0_MCR: CLR_RXF Mask                  */
#define SPI_MCR_CLR_RXF_SHIFT                    10                                                  /*!< SPI0_MCR: CLR_RXF Position              */
#define SPI_MCR_CLR_TXF_MASK                     (0x01UL << SPI_MCR_CLR_TXF_SHIFT)                   /*!< SPI0_MCR: CLR_TXF Mask                  */
#define SPI_MCR_CLR_TXF_SHIFT                    11                                                  /*!< SPI0_MCR: CLR_TXF Position              */
#define SPI_MCR_DIS_RXF_MASK                     (0x01UL << SPI_MCR_DIS_RXF_SHIFT)                   /*!< SPI0_MCR: DIS_RXF Mask                  */
#define SPI_MCR_DIS_RXF_SHIFT                    12                                                  /*!< SPI0_MCR: DIS_RXF Position              */
#define SPI_MCR_DIS_TXF_MASK                     (0x01UL << SPI_MCR_DIS_TXF_SHIFT)                   /*!< SPI0_MCR: DIS_TXF Mask                  */
#define SPI_MCR_DIS_TXF_SHIFT                    13                                                  /*!< SPI0_MCR: DIS_TXF Position              */
#define SPI_MCR_MDIS_MASK                        (0x01UL << SPI_MCR_MDIS_SHIFT)                      /*!< SPI0_MCR: MDIS Mask                     */
#define SPI_MCR_MDIS_SHIFT                       14                                                  /*!< SPI0_MCR: MDIS Position                 */
#define SPI_MCR_DOZE_MASK                        (0x01UL << SPI_MCR_DOZE_SHIFT)                      /*!< SPI0_MCR: DOZE Mask                     */
#define SPI_MCR_DOZE_SHIFT                       15                                                  /*!< SPI0_MCR: DOZE Position                 */
#define SPI_MCR_PCSIS_MASK                       (0x1FUL << SPI_MCR_PCSIS_SHIFT)                     /*!< SPI0_MCR: PCSIS Mask                    */
#define SPI_MCR_PCSIS_SHIFT                      16                                                  /*!< SPI0_MCR: PCSIS Position                */
#define SPI_MCR_PCSIS(x)                         (((x)<<SPI_MCR_PCSIS_SHIFT)&SPI_MCR_PCSIS_MASK)     /*!< SPI0_MCR                                */
#define SPI_MCR_ROOE_MASK                        (0x01UL << SPI_MCR_ROOE_SHIFT)                      /*!< SPI0_MCR: ROOE Mask                     */
#define SPI_MCR_ROOE_SHIFT                       24                                                  /*!< SPI0_MCR: ROOE Position                 */
#define SPI_MCR_MTFE_MASK                        (0x01UL << SPI_MCR_MTFE_SHIFT)                      /*!< SPI0_MCR: MTFE Mask                     */
#define SPI_MCR_MTFE_SHIFT                       26                                                  /*!< SPI0_MCR: MTFE Position                 */
#define SPI_MCR_FRZ_MASK                         (0x01UL << SPI_MCR_FRZ_SHIFT)                       /*!< SPI0_MCR: FRZ Mask                      */
#define SPI_MCR_FRZ_SHIFT                        27                                                  /*!< SPI0_MCR: FRZ Position                  */
#define SPI_MCR_DCONF_MASK                       (0x03UL << SPI_MCR_DCONF_SHIFT)                     /*!< SPI0_MCR: DCONF Mask                    */
#define SPI_MCR_DCONF_SHIFT                      28                                                  /*!< SPI0_MCR: DCONF Position                */
#define SPI_MCR_DCONF(x)                         (((x)<<SPI_MCR_DCONF_SHIFT)&SPI_MCR_DCONF_MASK)     /*!< SPI0_MCR                                */
#define SPI_MCR_CONT_SCKE_MASK                   (0x01UL << SPI_MCR_CONT_SCKE_SHIFT)                 /*!< SPI0_MCR: CONT_SCKE Mask                */
#define SPI_MCR_CONT_SCKE_SHIFT                  30                                                  /*!< SPI0_MCR: CONT_SCKE Position            */
#define SPI_MCR_MSTR_MASK                        (0x01UL << SPI_MCR_MSTR_SHIFT)                      /*!< SPI0_MCR: MSTR Mask                     */
#define SPI_MCR_MSTR_SHIFT                       31                                                  /*!< SPI0_MCR: MSTR Position                 */

/* ------- SPI0_TCR                                 ------ */
#define SPI_TCR_SPI_TCNT_MASK                    (0xFFFFUL << SPI_TCR_SPI_TCNT_SHIFT)                /*!< SPI0_TCR: SPI_TCNT Mask                 */
#define SPI_TCR_SPI_TCNT_SHIFT                   16                                                  /*!< SPI0_TCR: SPI_TCNT Position             */
#define SPI_TCR_SPI_TCNT(x)                      (((x)<<SPI_TCR_SPI_TCNT_SHIFT)&SPI_TCR_SPI_TCNT_MASK) /*!< SPI0_TCR                                */

/* ------- SPI0_CTAR                                ------ */
#define SPI_CTAR_BR_MASK                         (0x0FUL << SPI_CTAR_BR_SHIFT)                       /*!< SPI0_CTAR: BR Mask                      */
#define SPI_CTAR_BR_SHIFT                        0                                                   /*!< SPI0_CTAR: BR Position                  */
#define SPI_CTAR_BR(x)                           (((x)<<SPI_CTAR_BR_SHIFT)&SPI_CTAR_BR_MASK)         /*!< SPI0_CTAR                               */
#define SPI_CTAR_DT_MASK                         (0x0FUL << SPI_CTAR_DT_SHIFT)                       /*!< SPI0_CTAR: DT Mask                      */
#define SPI_CTAR_DT_SHIFT                        4                                                   /*!< SPI0_CTAR: DT Position                  */
#define SPI_CTAR_DT(x)                           (((x)<<SPI_CTAR_DT_SHIFT)&SPI_CTAR_DT_MASK)         /*!< SPI0_CTAR                               */
#define SPI_CTAR_ASC_MASK                        (0x0FUL << SPI_CTAR_ASC_SHIFT)                      /*!< SPI0_CTAR: ASC Mask                     */
#define SPI_CTAR_ASC_SHIFT                       8                                                   /*!< SPI0_CTAR: ASC Position                 */
#define SPI_CTAR_ASC(x)                          (((x)<<SPI_CTAR_ASC_SHIFT)&SPI_CTAR_ASC_MASK)       /*!< SPI0_CTAR                               */
#define SPI_CTAR_CSSCK_MASK                      (0x0FUL << SPI_CTAR_CSSCK_SHIFT)                    /*!< SPI0_CTAR: CSSCK Mask                   */
#define SPI_CTAR_CSSCK_SHIFT                     12                                                  /*!< SPI0_CTAR: CSSCK Position               */
#define SPI_CTAR_CSSCK(x)                        (((x)<<SPI_CTAR_CSSCK_SHIFT)&SPI_CTAR_CSSCK_MASK)   /*!< SPI0_CTAR                               */
#define SPI_CTAR_PBR_MASK                        (0x03UL << SPI_CTAR_PBR_SHIFT)                      /*!< SPI0_CTAR: PBR Mask                     */
#define SPI_CTAR_PBR_SHIFT                       16                                                  /*!< SPI0_CTAR: PBR Position                 */
#define SPI_CTAR_PBR(x)                          (((x)<<SPI_CTAR_PBR_SHIFT)&SPI_CTAR_PBR_MASK)       /*!< SPI0_CTAR                               */
#define SPI_CTAR_PDT_MASK                        (0x03UL << SPI_CTAR_PDT_SHIFT)                      /*!< SPI0_CTAR: PDT Mask                     */
#define SPI_CTAR_PDT_SHIFT                       18                                                  /*!< SPI0_CTAR: PDT Position                 */
#define SPI_CTAR_PDT(x)                          (((x)<<SPI_CTAR_PDT_SHIFT)&SPI_CTAR_PDT_MASK)       /*!< SPI0_CTAR                               */
#define SPI_CTAR_PASC_MASK                       (0x03UL << SPI_CTAR_PASC_SHIFT)                     /*!< SPI0_CTAR: PASC Mask                    */
#define SPI_CTAR_PASC_SHIFT                      20                                                  /*!< SPI0_CTAR: PASC Position                */
#define SPI_CTAR_PASC(x)                         (((x)<<SPI_CTAR_PASC_SHIFT)&SPI_CTAR_PASC_MASK)     /*!< SPI0_CTAR                               */
#define SPI_CTAR_PCSSCK_MASK                     (0x03UL << SPI_CTAR_PCSSCK_SHIFT)                   /*!< SPI0_CTAR: PCSSCK Mask                  */
#define SPI_CTAR_PCSSCK_SHIFT                    22                                                  /*!< SPI0_CTAR: PCSSCK Position              */
#define SPI_CTAR_PCSSCK(x)                       (((x)<<SPI_CTAR_PCSSCK_SHIFT)&SPI_CTAR_PCSSCK_MASK) /*!< SPI0_CTAR                               */
#define SPI_CTAR_LSBFE_MASK                      (0x01UL << SPI_CTAR_LSBFE_SHIFT)                    /*!< SPI0_CTAR: LSBFE Mask                   */
#define SPI_CTAR_LSBFE_SHIFT                     24                                                  /*!< SPI0_CTAR: LSBFE Position               */
#define SPI_CTAR_CPHA_MASK                       (0x01UL << SPI_CTAR_CPHA_SHIFT)                     /*!< SPI0_CTAR: CPHA Mask                    */
#define SPI_CTAR_CPHA_SHIFT                      25                                                  /*!< SPI0_CTAR: CPHA Position                */
#define SPI_CTAR_CPOL_MASK                       (0x01UL << SPI_CTAR_CPOL_SHIFT)                     /*!< SPI0_CTAR: CPOL Mask                    */
#define SPI_CTAR_CPOL_SHIFT                      26                                                  /*!< SPI0_CTAR: CPOL Position                */
#define SPI_CTAR_FMSZ_MASK                       (0x0FUL << SPI_CTAR_FMSZ_SHIFT)                     /*!< SPI0_CTAR: FMSZ Mask                    */
#define SPI_CTAR_FMSZ_SHIFT                      27                                                  /*!< SPI0_CTAR: FMSZ Position                */
#define SPI_CTAR_FMSZ(x)                         (((x)<<SPI_CTAR_FMSZ_SHIFT)&SPI_CTAR_FMSZ_MASK)     /*!< SPI0_CTAR                               */
#define SPI_CTAR_DBR_MASK                        (0x01UL << SPI_CTAR_DBR_SHIFT)                      /*!< SPI0_CTAR: DBR Mask                     */
#define SPI_CTAR_DBR_SHIFT                       31                                                  /*!< SPI0_CTAR: DBR Position                 */

/* ------- SPI0_CTAR_SLAVE                          ------ */
#define SPI_CTAR_SLAVE_CPHA_MASK                 (0x01UL << SPI_CTAR_SLAVE_CPHA_SHIFT)               /*!< SPI0_CTAR_SLAVE: CPHA Mask              */
#define SPI_CTAR_SLAVE_CPHA_SHIFT                25                                                  /*!< SPI0_CTAR_SLAVE: CPHA Position          */
#define SPI_CTAR_SLAVE_CPOL_MASK                 (0x01UL << SPI_CTAR_SLAVE_CPOL_SHIFT)               /*!< SPI0_CTAR_SLAVE: CPOL Mask              */
#define SPI_CTAR_SLAVE_CPOL_SHIFT                26                                                  /*!< SPI0_CTAR_SLAVE: CPOL Position          */
#define SPI_CTAR_SLAVE_FMSZ_MASK                 (0x1FUL << SPI_CTAR_SLAVE_FMSZ_SHIFT)               /*!< SPI0_CTAR_SLAVE: FMSZ Mask              */
#define SPI_CTAR_SLAVE_FMSZ_SHIFT                27                                                  /*!< SPI0_CTAR_SLAVE: FMSZ Position          */
#define SPI_CTAR_SLAVE_FMSZ(x)                   (((x)<<SPI_CTAR_SLAVE_FMSZ_SHIFT)&SPI_CTAR_SLAVE_FMSZ_MASK) /*!< SPI0_CTAR_SLAVE                         */

/* ------- SPI0_SR                                  ------ */
#define SPI_SR_POPNXTPTR_MASK                    (0x0FUL << SPI_SR_POPNXTPTR_SHIFT)                  /*!< SPI0_SR: POPNXTPTR Mask                 */
#define SPI_SR_POPNXTPTR_SHIFT                   0                                                   /*!< SPI0_SR: POPNXTPTR Position             */
#define SPI_SR_POPNXTPTR(x)                      (((x)<<SPI_SR_POPNXTPTR_SHIFT)&SPI_SR_POPNXTPTR_MASK) /*!< SPI0_SR                                 */
#define SPI_SR_RXCTR_MASK                        (0x0FUL << SPI_SR_RXCTR_SHIFT)                      /*!< SPI0_SR: RXCTR Mask                     */
#define SPI_SR_RXCTR_SHIFT                       4                                                   /*!< SPI0_SR: RXCTR Position                 */
#define SPI_SR_RXCTR(x)                          (((x)<<SPI_SR_RXCTR_SHIFT)&SPI_SR_RXCTR_MASK)       /*!< SPI0_SR                                 */
#define SPI_SR_TXNXTPTR_MASK                     (0x0FUL << SPI_SR_TXNXTPTR_SHIFT)                   /*!< SPI0_SR: TXNXTPTR Mask                  */
#define SPI_SR_TXNXTPTR_SHIFT                    8                                                   /*!< SPI0_SR: TXNXTPTR Position              */
#define SPI_SR_TXNXTPTR(x)                       (((x)<<SPI_SR_TXNXTPTR_SHIFT)&SPI_SR_TXNXTPTR_MASK) /*!< SPI0_SR                                 */
#define SPI_SR_TXCTR_MASK                        (0x0FUL << SPI_SR_TXCTR_SHIFT)                      /*!< SPI0_SR: TXCTR Mask                     */
#define SPI_SR_TXCTR_SHIFT                       12                                                  /*!< SPI0_SR: TXCTR Position                 */
#define SPI_SR_TXCTR(x)                          (((x)<<SPI_SR_TXCTR_SHIFT)&SPI_SR_TXCTR_MASK)       /*!< SPI0_SR                                 */
#define SPI_SR_RFDF_MASK                         (0x01UL << SPI_SR_RFDF_SHIFT)                       /*!< SPI0_SR: RFDF Mask                      */
#define SPI_SR_RFDF_SHIFT                        17                                                  /*!< SPI0_SR: RFDF Position                  */
#define SPI_SR_RFOF_MASK                         (0x01UL << SPI_SR_RFOF_SHIFT)                       /*!< SPI0_SR: RFOF Mask                      */
#define SPI_SR_RFOF_SHIFT                        19                                                  /*!< SPI0_SR: RFOF Position                  */
#define SPI_SR_TFFF_MASK                         (0x01UL << SPI_SR_TFFF_SHIFT)                       /*!< SPI0_SR: TFFF Mask                      */
#define SPI_SR_TFFF_SHIFT                        25                                                  /*!< SPI0_SR: TFFF Position                  */
#define SPI_SR_TFUF_MASK                         (0x01UL << SPI_SR_TFUF_SHIFT)                       /*!< SPI0_SR: TFUF Mask                      */
#define SPI_SR_TFUF_SHIFT                        27                                                  /*!< SPI0_SR: TFUF Position                  */
#define SPI_SR_EOQF_MASK                         (0x01UL << SPI_SR_EOQF_SHIFT)                       /*!< SPI0_SR: EOQF Mask                      */
#define SPI_SR_EOQF_SHIFT                        28                                                  /*!< SPI0_SR: EOQF Position                  */
#define SPI_SR_TXRXS_MASK                        (0x01UL << SPI_SR_TXRXS_SHIFT)                      /*!< SPI0_SR: TXRXS Mask                     */
#define SPI_SR_TXRXS_SHIFT                       30                                                  /*!< SPI0_SR: TXRXS Position                 */
#define SPI_SR_TCF_MASK                          (0x01UL << SPI_SR_TCF_SHIFT)                        /*!< SPI0_SR: TCF Mask                       */
#define SPI_SR_TCF_SHIFT                         31                                                  /*!< SPI0_SR: TCF Position                   */

/* ------- SPI0_RSER                                ------ */
#define SPI_RSER_RFDF_DIRS_MASK                  (0x01UL << SPI_RSER_RFDF_DIRS_SHIFT)                /*!< SPI0_RSER: RFDF_DIRS Mask               */
#define SPI_RSER_RFDF_DIRS_SHIFT                 16                                                  /*!< SPI0_RSER: RFDF_DIRS Position           */
#define SPI_RSER_RFDF_RE_MASK                    (0x01UL << SPI_RSER_RFDF_RE_SHIFT)                  /*!< SPI0_RSER: RFDF_RE Mask                 */
#define SPI_RSER_RFDF_RE_SHIFT                   17                                                  /*!< SPI0_RSER: RFDF_RE Position             */
#define SPI_RSER_RFOF_RE_MASK                    (0x01UL << SPI_RSER_RFOF_RE_SHIFT)                  /*!< SPI0_RSER: RFOF_RE Mask                 */
#define SPI_RSER_RFOF_RE_SHIFT                   19                                                  /*!< SPI0_RSER: RFOF_RE Position             */
#define SPI_RSER_TFFF_DIRS_MASK                  (0x01UL << SPI_RSER_TFFF_DIRS_SHIFT)                /*!< SPI0_RSER: TFFF_DIRS Mask               */
#define SPI_RSER_TFFF_DIRS_SHIFT                 24                                                  /*!< SPI0_RSER: TFFF_DIRS Position           */
#define SPI_RSER_TFFF_RE_MASK                    (0x01UL << SPI_RSER_TFFF_RE_SHIFT)                  /*!< SPI0_RSER: TFFF_RE Mask                 */
#define SPI_RSER_TFFF_RE_SHIFT                   25                                                  /*!< SPI0_RSER: TFFF_RE Position             */
#define SPI_RSER_TFUF_RE_MASK                    (0x01UL << SPI_RSER_TFUF_RE_SHIFT)                  /*!< SPI0_RSER: TFUF_RE Mask                 */
#define SPI_RSER_TFUF_RE_SHIFT                   27                                                  /*!< SPI0_RSER: TFUF_RE Position             */
#define SPI_RSER_EOQF_RE_MASK                    (0x01UL << SPI_RSER_EOQF_RE_SHIFT)                  /*!< SPI0_RSER: EOQF_RE Mask                 */
#define SPI_RSER_EOQF_RE_SHIFT                   28                                                  /*!< SPI0_RSER: EOQF_RE Position             */
#define SPI_RSER_TCF_RE_MASK                     (0x01UL << SPI_RSER_TCF_RE_SHIFT)                   /*!< SPI0_RSER: TCF_RE Mask                  */
#define SPI_RSER_TCF_RE_SHIFT                    31                                                  /*!< SPI0_RSER: TCF_RE Position              */

/* ------- SPI0_PUSHR                               ------ */
#define SPI_PUSHR_TXDATA_MASK                    (0xFFFFUL << SPI_PUSHR_TXDATA_SHIFT)                /*!< SPI0_PUSHR: TXDATA Mask                 */
#define SPI_PUSHR_TXDATA_SHIFT                   0                                                   /*!< SPI0_PUSHR: TXDATA Position             */
#define SPI_PUSHR_TXDATA(x)                      (((x)<<SPI_PUSHR_TXDATA_SHIFT)&SPI_PUSHR_TXDATA_MASK) /*!< SPI0_PUSHR                              */
#define SPI_PUSHR_PCS_MASK                       (0x1FUL << SPI_PUSHR_PCS_SHIFT)                     /*!< SPI0_PUSHR: PCS Mask                    */
#define SPI_PUSHR_PCS_SHIFT                      16                                                  /*!< SPI0_PUSHR: PCS Position                */
#define SPI_PUSHR_PCS(x)                         (((x)<<SPI_PUSHR_PCS_SHIFT)&SPI_PUSHR_PCS_MASK)     /*!< SPI0_PUSHR                              */
#define SPI_PUSHR_CTCNT_MASK                     (0x01UL << SPI_PUSHR_CTCNT_SHIFT)                   /*!< SPI0_PUSHR: CTCNT Mask                  */
#define SPI_PUSHR_CTCNT_SHIFT                    26                                                  /*!< SPI0_PUSHR: CTCNT Position              */
#define SPI_PUSHR_EOQ_MASK                       (0x01UL << SPI_PUSHR_EOQ_SHIFT)                     /*!< SPI0_PUSHR: EOQ Mask                    */
#define SPI_PUSHR_EOQ_SHIFT                      27                                                  /*!< SPI0_PUSHR: EOQ Position                */
#define SPI_PUSHR_CTAS_MASK                      (0x07UL << SPI_PUSHR_CTAS_SHIFT)                    /*!< SPI0_PUSHR: CTAS Mask                   */
#define SPI_PUSHR_CTAS_SHIFT                     28                                                  /*!< SPI0_PUSHR: CTAS Position               */
#define SPI_PUSHR_CTAS(x)                        (((x)<<SPI_PUSHR_CTAS_SHIFT)&SPI_PUSHR_CTAS_MASK)   /*!< SPI0_PUSHR                              */
#define SPI_PUSHR_CONT_MASK                      (0x01UL << SPI_PUSHR_CONT_SHIFT)                    /*!< SPI0_PUSHR: CONT Mask                   */
#define SPI_PUSHR_CONT_SHIFT                     31                                                  /*!< SPI0_PUSHR: CONT Position               */

/* ------- SPI0_PUSHR_SLAVE                         ------ */
#define SPI_PUSHR_SLAVE_TXDATA_MASK              (0xFFFFUL << SPI_PUSHR_SLAVE_TXDATA_SHIFT)          /*!< SPI0_PUSHR_SLAVE: TXDATA Mask           */
#define SPI_PUSHR_SLAVE_TXDATA_SHIFT             0                                                   /*!< SPI0_PUSHR_SLAVE: TXDATA Position       */
#define SPI_PUSHR_SLAVE_TXDATA(x)                (((x)<<SPI_PUSHR_SLAVE_TXDATA_SHIFT)&SPI_PUSHR_SLAVE_TXDATA_MASK) /*!< SPI0_PUSHR_SLAVE                        */

/* ------- SPI0_POPR                                ------ */
#define SPI_POPR_RXDATA_MASK                     (0xFFFFFFFFUL << SPI_POPR_RXDATA_SHIFT)             /*!< SPI0_POPR: RXDATA Mask                  */
#define SPI_POPR_RXDATA_SHIFT                    0                                                   /*!< SPI0_POPR: RXDATA Position              */
#define SPI_POPR_RXDATA(x)                       (((x)<<SPI_POPR_RXDATA_SHIFT)&SPI_POPR_RXDATA_MASK) /*!< SPI0_POPR                               */

/* ------- SPI0_TXFR                                ------ */
#define SPI_TXFR_TXDATA_MASK                     (0xFFFFUL << SPI_TXFR_TXDATA_SHIFT)                 /*!< SPI0_TXFR: TXDATA Mask                  */
#define SPI_TXFR_TXDATA_SHIFT                    0                                                   /*!< SPI0_TXFR: TXDATA Position              */
#define SPI_TXFR_TXDATA(x)                       (((x)<<SPI_TXFR_TXDATA_SHIFT)&SPI_TXFR_TXDATA_MASK) /*!< SPI0_TXFR                               */
#define SPI_TXFR_TXCMD_TXDATA_MASK               (0xFFFFUL << SPI_TXFR_TXCMD_TXDATA_SHIFT)           /*!< SPI0_TXFR: TXCMD_TXDATA Mask            */
#define SPI_TXFR_TXCMD_TXDATA_SHIFT              16                                                  /*!< SPI0_TXFR: TXCMD_TXDATA Position        */
#define SPI_TXFR_TXCMD_TXDATA(x)                 (((x)<<SPI_TXFR_TXCMD_TXDATA_SHIFT)&SPI_TXFR_TXCMD_TXDATA_MASK) /*!< SPI0_TXFR                               */

/* ------- SPI0_RXFR                                ------ */
#define SPI_RXFR_RXDATA_MASK                     (0xFFFFFFFFUL << SPI_RXFR_RXDATA_SHIFT)             /*!< SPI0_RXFR: RXDATA Mask                  */
#define SPI_RXFR_RXDATA_SHIFT                    0                                                   /*!< SPI0_RXFR: RXDATA Position              */
#define SPI_RXFR_RXDATA(x)                       (((x)<<SPI_RXFR_RXDATA_SHIFT)&SPI_RXFR_RXDATA_MASK) /*!< SPI0_RXFR                               */

/* ------- SPI0_SREX                                ------ */
#define SPI_SREX_CMDNXTPTR_MASK                  (0x0FUL << SPI_SREX_CMDNXTPTR_SHIFT)                /*!< SPI0_SREX: CMDNXTPTR Mask               */
#define SPI_SREX_CMDNXTPTR_SHIFT                 0                                                   /*!< SPI0_SREX: CMDNXTPTR Position           */
#define SPI_SREX_CMDNXTPTR(x)                    (((x)<<SPI_SREX_CMDNXTPTR_SHIFT)&SPI_SREX_CMDNXTPTR_MASK) /*!< SPI0_SREX                               */
#define SPI_SREX_CMDCTR_MASK                     (0x1FUL << SPI_SREX_CMDCTR_SHIFT)                   /*!< SPI0_SREX: CMDCTR Mask                  */
#define SPI_SREX_CMDCTR_SHIFT                    4                                                   /*!< SPI0_SREX: CMDCTR Position              */
#define SPI_SREX_CMDCTR(x)                       (((x)<<SPI_SREX_CMDCTR_SHIFT)&SPI_SREX_CMDCTR_MASK) /*!< SPI0_SREX                               */
#define SPI_SREX_TXCTR4_MASK                     (0x01UL << SPI_SREX_TXCTR4_SHIFT)                   /*!< SPI0_SREX: TXCTR4 Mask                  */
#define SPI_SREX_TXCTR4_SHIFT                    11                                                  /*!< SPI0_SREX: TXCTR4 Position              */
#define SPI_SREX_RXCTR4_MASK                     (0x01UL << SPI_SREX_RXCTR4_SHIFT)                   /*!< SPI0_SREX: RXCTR4 Mask                  */
#define SPI_SREX_RXCTR4_SHIFT                    14                                                  /*!< SPI0_SREX: RXCTR4 Position              */

/* -------------------------------------------------------------------------------- */
/* -----------     'SPI0' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define SPI0_MCR                       (SPI0->MCR)
#define SPI0_TCR                       (SPI0->TCR)
#define SPI0_CTAR0                     (SPI0->CTAR[0])
#define SPI0_CTAR1                     (SPI0->CTAR[1])
#define SPI0_CTAR_SLAVE                (SPI0->CTAR_SLAVE)
#define SPI0_SR                        (SPI0->SR)
#define SPI0_RSER                      (SPI0->RSER)
#define SPI0_PUSHR                     (SPI0->PUSHR)
#define SPI0_PUSHR_SLAVE               (SPI0->PUSHR_SLAVE)
#define SPI0_POPR                      (SPI0->POPR)
#define SPI0_TXFR0                     (SPI0->TXFR[0])
#define SPI0_TXFR1                     (SPI0->TXFR[1])
#define SPI0_TXFR2                     (SPI0->TXFR[2])
#define SPI0_TXFR3                     (SPI0->TXFR[3])
#define SPI0_RXFR0                     (SPI0->RXFR[0])
#define SPI0_RXFR1                     (SPI0->RXFR[1])
#define SPI0_RXFR2                     (SPI0->RXFR[2])
#define SPI0_RXFR3                     (SPI0->RXFR[3])
#define SPI0_SREX                      (SPI0->SREX)

/* ================================================================================ */
/* ================           UART0 (file:UART0_5)                 ================ */
/* ================================================================================ */

/**
 * @brief Universal Asynchronous Receiver/Transmitter
 */
typedef struct {                                /*!<       UART0 Structure                                              */
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
   __I  uint8_t   ED;                           /*!< 000C: Extended Data Register                                       */
   __IO uint8_t   MODEM;                        /*!< 000D: Modem Register                                               */
   __I  uint16_t  RESERVED0;                    /*!< 000E:                                                              */
   __IO uint8_t   PFIFO;                        /*!< 0010: FIFO Parameters                                              */
   __IO uint8_t   CFIFO;                        /*!< 0011: FIFO Control Register                                        */
   __IO uint8_t   SFIFO;                        /*!< 0012: FIFO Status Register                                         */
   __IO uint8_t   TWFIFO;                       /*!< 0013: FIFO Transmit Watermark                                      */
   __I  uint8_t   TCFIFO;                       /*!< 0014: FIFO Transmit Count                                          */
   __IO uint8_t   RWFIFO;                       /*!< 0015: FIFO Receive Watermark                                       */
   __I  uint8_t   RCFIFO;                       /*!< 0016: FIFO Receive Count                                           */
} UART0_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'UART0' Position & Mask macros                       ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- UART0_BDH                                ------ */
#define UART_BDH_SBR_MASK                        (0x1FUL << UART_BDH_SBR_SHIFT)                      /*!< UART0_BDH: SBR Mask                     */
#define UART_BDH_SBR_SHIFT                       0                                                   /*!< UART0_BDH: SBR Position                 */
#define UART_BDH_SBR(x)                          (((x)<<UART_BDH_SBR_SHIFT)&UART_BDH_SBR_MASK)       /*!< UART0_BDH                               */
#define UART_BDH_SBNS_MASK                       (0x01UL << UART_BDH_SBNS_SHIFT)                     /*!< UART0_BDH: SBNS Mask                    */
#define UART_BDH_SBNS_SHIFT                      5                                                   /*!< UART0_BDH: SBNS Position                */
#define UART_BDH_RXEDGIE_MASK                    (0x01UL << UART_BDH_RXEDGIE_SHIFT)                  /*!< UART0_BDH: RXEDGIE Mask                 */
#define UART_BDH_RXEDGIE_SHIFT                   6                                                   /*!< UART0_BDH: RXEDGIE Position             */
#define UART_BDH_LBKDIE_MASK                     (0x01UL << UART_BDH_LBKDIE_SHIFT)                   /*!< UART0_BDH: LBKDIE Mask                  */
#define UART_BDH_LBKDIE_SHIFT                    7                                                   /*!< UART0_BDH: LBKDIE Position              */

/* ------- UART0_BDL                                ------ */
#define UART_BDL_SBR_MASK                        (0xFFUL << UART_BDL_SBR_SHIFT)                      /*!< UART0_BDL: SBR Mask                     */
#define UART_BDL_SBR_SHIFT                       0                                                   /*!< UART0_BDL: SBR Position                 */
#define UART_BDL_SBR(x)                          (((x)<<UART_BDL_SBR_SHIFT)&UART_BDL_SBR_MASK)       /*!< UART0_BDL                               */

/* ------- UART0_C1                                 ------ */
#define UART_C1_PT_MASK                          (0x01UL << UART_C1_PT_SHIFT)                        /*!< UART0_C1: PT Mask                       */
#define UART_C1_PT_SHIFT                         0                                                   /*!< UART0_C1: PT Position                   */
#define UART_C1_PE_MASK                          (0x01UL << UART_C1_PE_SHIFT)                        /*!< UART0_C1: PE Mask                       */
#define UART_C1_PE_SHIFT                         1                                                   /*!< UART0_C1: PE Position                   */
#define UART_C1_ILT_MASK                         (0x01UL << UART_C1_ILT_SHIFT)                       /*!< UART0_C1: ILT Mask                      */
#define UART_C1_ILT_SHIFT                        2                                                   /*!< UART0_C1: ILT Position                  */
#define UART_C1_WAKE_MASK                        (0x01UL << UART_C1_WAKE_SHIFT)                      /*!< UART0_C1: WAKE Mask                     */
#define UART_C1_WAKE_SHIFT                       3                                                   /*!< UART0_C1: WAKE Position                 */
#define UART_C1_M_MASK                           (0x01UL << UART_C1_M_SHIFT)                         /*!< UART0_C1: M Mask                        */
#define UART_C1_M_SHIFT                          4                                                   /*!< UART0_C1: M Position                    */
#define UART_C1_RSRC_MASK                        (0x01UL << UART_C1_RSRC_SHIFT)                      /*!< UART0_C1: RSRC Mask                     */
#define UART_C1_RSRC_SHIFT                       5                                                   /*!< UART0_C1: RSRC Position                 */
#define UART_C1_UARTSWAI_MASK                    (0x01UL << UART_C1_UARTSWAI_SHIFT)                  /*!< UART0_C1: UARTSWAI Mask                 */
#define UART_C1_UARTSWAI_SHIFT                   6                                                   /*!< UART0_C1: UARTSWAI Position             */
#define UART_C1_LOOPS_MASK                       (0x01UL << UART_C1_LOOPS_SHIFT)                     /*!< UART0_C1: LOOPS Mask                    */
#define UART_C1_LOOPS_SHIFT                      7                                                   /*!< UART0_C1: LOOPS Position                */

/* ------- UART0_C2                                 ------ */
#define UART_C2_SBK_MASK                         (0x01UL << UART_C2_SBK_SHIFT)                       /*!< UART0_C2: SBK Mask                      */
#define UART_C2_SBK_SHIFT                        0                                                   /*!< UART0_C2: SBK Position                  */
#define UART_C2_RWU_MASK                         (0x01UL << UART_C2_RWU_SHIFT)                       /*!< UART0_C2: RWU Mask                      */
#define UART_C2_RWU_SHIFT                        1                                                   /*!< UART0_C2: RWU Position                  */
#define UART_C2_RE_MASK                          (0x01UL << UART_C2_RE_SHIFT)                        /*!< UART0_C2: RE Mask                       */
#define UART_C2_RE_SHIFT                         2                                                   /*!< UART0_C2: RE Position                   */
#define UART_C2_TE_MASK                          (0x01UL << UART_C2_TE_SHIFT)                        /*!< UART0_C2: TE Mask                       */
#define UART_C2_TE_SHIFT                         3                                                   /*!< UART0_C2: TE Position                   */
#define UART_C2_ILIE_MASK                        (0x01UL << UART_C2_ILIE_SHIFT)                      /*!< UART0_C2: ILIE Mask                     */
#define UART_C2_ILIE_SHIFT                       4                                                   /*!< UART0_C2: ILIE Position                 */
#define UART_C2_RIE_MASK                         (0x01UL << UART_C2_RIE_SHIFT)                       /*!< UART0_C2: RIE Mask                      */
#define UART_C2_RIE_SHIFT                        5                                                   /*!< UART0_C2: RIE Position                  */
#define UART_C2_TCIE_MASK                        (0x01UL << UART_C2_TCIE_SHIFT)                      /*!< UART0_C2: TCIE Mask                     */
#define UART_C2_TCIE_SHIFT                       6                                                   /*!< UART0_C2: TCIE Position                 */
#define UART_C2_TIE_MASK                         (0x01UL << UART_C2_TIE_SHIFT)                       /*!< UART0_C2: TIE Mask                      */
#define UART_C2_TIE_SHIFT                        7                                                   /*!< UART0_C2: TIE Position                  */

/* ------- UART0_S1                                 ------ */
#define UART_S1_PF_MASK                          (0x01UL << UART_S1_PF_SHIFT)                        /*!< UART0_S1: PF Mask                       */
#define UART_S1_PF_SHIFT                         0                                                   /*!< UART0_S1: PF Position                   */
#define UART_S1_FE_MASK                          (0x01UL << UART_S1_FE_SHIFT)                        /*!< UART0_S1: FE Mask                       */
#define UART_S1_FE_SHIFT                         1                                                   /*!< UART0_S1: FE Position                   */
#define UART_S1_NF_MASK                          (0x01UL << UART_S1_NF_SHIFT)                        /*!< UART0_S1: NF Mask                       */
#define UART_S1_NF_SHIFT                         2                                                   /*!< UART0_S1: NF Position                   */
#define UART_S1_OR_MASK                          (0x01UL << UART_S1_OR_SHIFT)                        /*!< UART0_S1: OR Mask                       */
#define UART_S1_OR_SHIFT                         3                                                   /*!< UART0_S1: OR Position                   */
#define UART_S1_IDLE_MASK                        (0x01UL << UART_S1_IDLE_SHIFT)                      /*!< UART0_S1: IDLE Mask                     */
#define UART_S1_IDLE_SHIFT                       4                                                   /*!< UART0_S1: IDLE Position                 */
#define UART_S1_RDRF_MASK                        (0x01UL << UART_S1_RDRF_SHIFT)                      /*!< UART0_S1: RDRF Mask                     */
#define UART_S1_RDRF_SHIFT                       5                                                   /*!< UART0_S1: RDRF Position                 */
#define UART_S1_TC_MASK                          (0x01UL << UART_S1_TC_SHIFT)                        /*!< UART0_S1: TC Mask                       */
#define UART_S1_TC_SHIFT                         6                                                   /*!< UART0_S1: TC Position                   */
#define UART_S1_TDRE_MASK                        (0x01UL << UART_S1_TDRE_SHIFT)                      /*!< UART0_S1: TDRE Mask                     */
#define UART_S1_TDRE_SHIFT                       7                                                   /*!< UART0_S1: TDRE Position                 */

/* ------- UART0_S2                                 ------ */
#define UART_S2_RAF_MASK                         (0x01UL << UART_S2_RAF_SHIFT)                       /*!< UART0_S2: RAF Mask                      */
#define UART_S2_RAF_SHIFT                        0                                                   /*!< UART0_S2: RAF Position                  */
#define UART_S2_LBKDE_MASK                       (0x01UL << UART_S2_LBKDE_SHIFT)                     /*!< UART0_S2: LBKDE Mask                    */
#define UART_S2_LBKDE_SHIFT                      1                                                   /*!< UART0_S2: LBKDE Position                */
#define UART_S2_BRK13_MASK                       (0x01UL << UART_S2_BRK13_SHIFT)                     /*!< UART0_S2: BRK13 Mask                    */
#define UART_S2_BRK13_SHIFT                      2                                                   /*!< UART0_S2: BRK13 Position                */
#define UART_S2_RWUID_MASK                       (0x01UL << UART_S2_RWUID_SHIFT)                     /*!< UART0_S2: RWUID Mask                    */
#define UART_S2_RWUID_SHIFT                      3                                                   /*!< UART0_S2: RWUID Position                */
#define UART_S2_RXINV_MASK                       (0x01UL << UART_S2_RXINV_SHIFT)                     /*!< UART0_S2: RXINV Mask                    */
#define UART_S2_RXINV_SHIFT                      4                                                   /*!< UART0_S2: RXINV Position                */
#define UART_S2_MSBF_MASK                        (0x01UL << UART_S2_MSBF_SHIFT)                      /*!< UART0_S2: MSBF Mask                     */
#define UART_S2_MSBF_SHIFT                       5                                                   /*!< UART0_S2: MSBF Position                 */
#define UART_S2_RXEDGIF_MASK                     (0x01UL << UART_S2_RXEDGIF_SHIFT)                   /*!< UART0_S2: RXEDGIF Mask                  */
#define UART_S2_RXEDGIF_SHIFT                    6                                                   /*!< UART0_S2: RXEDGIF Position              */
#define UART_S2_LBKDIF_MASK                      (0x01UL << UART_S2_LBKDIF_SHIFT)                    /*!< UART0_S2: LBKDIF Mask                   */
#define UART_S2_LBKDIF_SHIFT                     7                                                   /*!< UART0_S2: LBKDIF Position               */

/* ------- UART0_C3                                 ------ */
#define UART_C3_PEIE_MASK                        (0x01UL << UART_C3_PEIE_SHIFT)                      /*!< UART0_C3: PEIE Mask                     */
#define UART_C3_PEIE_SHIFT                       0                                                   /*!< UART0_C3: PEIE Position                 */
#define UART_C3_FEIE_MASK                        (0x01UL << UART_C3_FEIE_SHIFT)                      /*!< UART0_C3: FEIE Mask                     */
#define UART_C3_FEIE_SHIFT                       1                                                   /*!< UART0_C3: FEIE Position                 */
#define UART_C3_NEIE_MASK                        (0x01UL << UART_C3_NEIE_SHIFT)                      /*!< UART0_C3: NEIE Mask                     */
#define UART_C3_NEIE_SHIFT                       2                                                   /*!< UART0_C3: NEIE Position                 */
#define UART_C3_ORIE_MASK                        (0x01UL << UART_C3_ORIE_SHIFT)                      /*!< UART0_C3: ORIE Mask                     */
#define UART_C3_ORIE_SHIFT                       3                                                   /*!< UART0_C3: ORIE Position                 */
#define UART_C3_TXINV_MASK                       (0x01UL << UART_C3_TXINV_SHIFT)                     /*!< UART0_C3: TXINV Mask                    */
#define UART_C3_TXINV_SHIFT                      4                                                   /*!< UART0_C3: TXINV Position                */
#define UART_C3_TXDIR_MASK                       (0x01UL << UART_C3_TXDIR_SHIFT)                     /*!< UART0_C3: TXDIR Mask                    */
#define UART_C3_TXDIR_SHIFT                      5                                                   /*!< UART0_C3: TXDIR Position                */
#define UART_C3_T8_MASK                          (0x01UL << UART_C3_T8_SHIFT)                        /*!< UART0_C3: T8 Mask                       */
#define UART_C3_T8_SHIFT                         6                                                   /*!< UART0_C3: T8 Position                   */
#define UART_C3_R8_MASK                          (0x01UL << UART_C3_R8_SHIFT)                        /*!< UART0_C3: R8 Mask                       */
#define UART_C3_R8_SHIFT                         7                                                   /*!< UART0_C3: R8 Position                   */

/* ------- UART0_D                                  ------ */
#define UART_D_RT_MASK                           (0xFFUL << UART_D_RT_SHIFT)                         /*!< UART0_D: RT Mask                        */
#define UART_D_RT_SHIFT                          0                                                   /*!< UART0_D: RT Position                    */
#define UART_D_RT(x)                             (((x)<<UART_D_RT_SHIFT)&UART_D_RT_MASK)             /*!< UART0_D                                 */

/* ------- UART0_MA                                 ------ */
#define UART_MA_MA_MASK                          (0xFFUL << UART_MA_MA_SHIFT)                        /*!< UART0_MA: MA Mask                       */
#define UART_MA_MA_SHIFT                         0                                                   /*!< UART0_MA: MA Position                   */
#define UART_MA_MA(x)                            (((x)<<UART_MA_MA_SHIFT)&UART_MA_MA_MASK)           /*!< UART0_MA                                */

/* ------- UART0_C4                                 ------ */
#define UART_C4_BRFA_MASK                        (0x1FUL << UART_C4_BRFA_SHIFT)                      /*!< UART0_C4: BRFA Mask                     */
#define UART_C4_BRFA_SHIFT                       0                                                   /*!< UART0_C4: BRFA Position                 */
#define UART_C4_BRFA(x)                          (((x)<<UART_C4_BRFA_SHIFT)&UART_C4_BRFA_MASK)       /*!< UART0_C4                                */
#define UART_C4_M10_MASK                         (0x01UL << UART_C4_M10_SHIFT)                       /*!< UART0_C4: M10 Mask                      */
#define UART_C4_M10_SHIFT                        5                                                   /*!< UART0_C4: M10 Position                  */
#define UART_C4_MAEN2_MASK                       (0x01UL << UART_C4_MAEN2_SHIFT)                     /*!< UART0_C4: MAEN2 Mask                    */
#define UART_C4_MAEN2_SHIFT                      6                                                   /*!< UART0_C4: MAEN2 Position                */
#define UART_C4_MAEN1_MASK                       (0x01UL << UART_C4_MAEN1_SHIFT)                     /*!< UART0_C4: MAEN1 Mask                    */
#define UART_C4_MAEN1_SHIFT                      7                                                   /*!< UART0_C4: MAEN1 Position                */

/* ------- UART0_C5                                 ------ */
#define UART_C5_LBKDDMAS_MASK                    (0x01UL << UART_C5_LBKDDMAS_SHIFT)                  /*!< UART0_C5: LBKDDMAS Mask                 */
#define UART_C5_LBKDDMAS_SHIFT                   3                                                   /*!< UART0_C5: LBKDDMAS Position             */
#define UART_C5_RDMAS_MASK                       (0x01UL << UART_C5_RDMAS_SHIFT)                     /*!< UART0_C5: RDMAS Mask                    */
#define UART_C5_RDMAS_SHIFT                      5                                                   /*!< UART0_C5: RDMAS Position                */
#define UART_C5_TDMAS_MASK                       (0x01UL << UART_C5_TDMAS_SHIFT)                     /*!< UART0_C5: TDMAS Mask                    */
#define UART_C5_TDMAS_SHIFT                      7                                                   /*!< UART0_C5: TDMAS Position                */

/* ------- UART0_ED                                 ------ */
#define UART_ED_PARITYE_MASK                     (0x01UL << UART_ED_PARITYE_SHIFT)                   /*!< UART0_ED: PARITYE Mask                  */
#define UART_ED_PARITYE_SHIFT                    6                                                   /*!< UART0_ED: PARITYE Position              */
#define UART_ED_NOISY_MASK                       (0x01UL << UART_ED_NOISY_SHIFT)                     /*!< UART0_ED: NOISY Mask                    */
#define UART_ED_NOISY_SHIFT                      7                                                   /*!< UART0_ED: NOISY Position                */

/* ------- UART0_MODEM                              ------ */
#define UART_MODEM_TXCTSE_MASK                   (0x01UL << UART_MODEM_TXCTSE_SHIFT)                 /*!< UART0_MODEM: TXCTSE Mask                */
#define UART_MODEM_TXCTSE_SHIFT                  0                                                   /*!< UART0_MODEM: TXCTSE Position            */
#define UART_MODEM_TXRTSE_MASK                   (0x01UL << UART_MODEM_TXRTSE_SHIFT)                 /*!< UART0_MODEM: TXRTSE Mask                */
#define UART_MODEM_TXRTSE_SHIFT                  1                                                   /*!< UART0_MODEM: TXRTSE Position            */
#define UART_MODEM_TXRTSPOL_MASK                 (0x01UL << UART_MODEM_TXRTSPOL_SHIFT)               /*!< UART0_MODEM: TXRTSPOL Mask              */
#define UART_MODEM_TXRTSPOL_SHIFT                2                                                   /*!< UART0_MODEM: TXRTSPOL Position          */
#define UART_MODEM_RXRTSE_MASK                   (0x01UL << UART_MODEM_RXRTSE_SHIFT)                 /*!< UART0_MODEM: RXRTSE Mask                */
#define UART_MODEM_RXRTSE_SHIFT                  3                                                   /*!< UART0_MODEM: RXRTSE Position            */

/* ------- UART0_PFIFO                              ------ */
#define UART_PFIFO_RXFIFOSIZE_MASK               (0x07UL << UART_PFIFO_RXFIFOSIZE_SHIFT)             /*!< UART0_PFIFO: RXFIFOSIZE Mask            */
#define UART_PFIFO_RXFIFOSIZE_SHIFT              0                                                   /*!< UART0_PFIFO: RXFIFOSIZE Position        */
#define UART_PFIFO_RXFIFOSIZE(x)                 (((x)<<UART_PFIFO_RXFIFOSIZE_SHIFT)&UART_PFIFO_RXFIFOSIZE_MASK) /*!< UART0_PFIFO                             */
#define UART_PFIFO_RXFE_MASK                     (0x01UL << UART_PFIFO_RXFE_SHIFT)                   /*!< UART0_PFIFO: RXFE Mask                  */
#define UART_PFIFO_RXFE_SHIFT                    3                                                   /*!< UART0_PFIFO: RXFE Position              */
#define UART_PFIFO_TXFIFOSIZE_MASK               (0x07UL << UART_PFIFO_TXFIFOSIZE_SHIFT)             /*!< UART0_PFIFO: TXFIFOSIZE Mask            */
#define UART_PFIFO_TXFIFOSIZE_SHIFT              4                                                   /*!< UART0_PFIFO: TXFIFOSIZE Position        */
#define UART_PFIFO_TXFIFOSIZE(x)                 (((x)<<UART_PFIFO_TXFIFOSIZE_SHIFT)&UART_PFIFO_TXFIFOSIZE_MASK) /*!< UART0_PFIFO                             */
#define UART_PFIFO_TXFE_MASK                     (0x01UL << UART_PFIFO_TXFE_SHIFT)                   /*!< UART0_PFIFO: TXFE Mask                  */
#define UART_PFIFO_TXFE_SHIFT                    7                                                   /*!< UART0_PFIFO: TXFE Position              */

/* ------- UART0_CFIFO                              ------ */
#define UART_CFIFO_RXUFE_MASK                    (0x01UL << UART_CFIFO_RXUFE_SHIFT)                  /*!< UART0_CFIFO: RXUFE Mask                 */
#define UART_CFIFO_RXUFE_SHIFT                   0                                                   /*!< UART0_CFIFO: RXUFE Position             */
#define UART_CFIFO_TXOFE_MASK                    (0x01UL << UART_CFIFO_TXOFE_SHIFT)                  /*!< UART0_CFIFO: TXOFE Mask                 */
#define UART_CFIFO_TXOFE_SHIFT                   1                                                   /*!< UART0_CFIFO: TXOFE Position             */
#define UART_CFIFO_RXOFE_MASK                    (0x01UL << UART_CFIFO_RXOFE_SHIFT)                  /*!< UART0_CFIFO: RXOFE Mask                 */
#define UART_CFIFO_RXOFE_SHIFT                   2                                                   /*!< UART0_CFIFO: RXOFE Position             */
#define UART_CFIFO_RXFLUSH_MASK                  (0x01UL << UART_CFIFO_RXFLUSH_SHIFT)                /*!< UART0_CFIFO: RXFLUSH Mask               */
#define UART_CFIFO_RXFLUSH_SHIFT                 6                                                   /*!< UART0_CFIFO: RXFLUSH Position           */
#define UART_CFIFO_TXFLUSH_MASK                  (0x01UL << UART_CFIFO_TXFLUSH_SHIFT)                /*!< UART0_CFIFO: TXFLUSH Mask               */
#define UART_CFIFO_TXFLUSH_SHIFT                 7                                                   /*!< UART0_CFIFO: TXFLUSH Position           */

/* ------- UART0_SFIFO                              ------ */
#define UART_SFIFO_RXUF_MASK                     (0x01UL << UART_SFIFO_RXUF_SHIFT)                   /*!< UART0_SFIFO: RXUF Mask                  */
#define UART_SFIFO_RXUF_SHIFT                    0                                                   /*!< UART0_SFIFO: RXUF Position              */
#define UART_SFIFO_TXOF_MASK                     (0x01UL << UART_SFIFO_TXOF_SHIFT)                   /*!< UART0_SFIFO: TXOF Mask                  */
#define UART_SFIFO_TXOF_SHIFT                    1                                                   /*!< UART0_SFIFO: TXOF Position              */
#define UART_SFIFO_RXOF_MASK                     (0x01UL << UART_SFIFO_RXOF_SHIFT)                   /*!< UART0_SFIFO: RXOF Mask                  */
#define UART_SFIFO_RXOF_SHIFT                    2                                                   /*!< UART0_SFIFO: RXOF Position              */
#define UART_SFIFO_RXEMPT_MASK                   (0x01UL << UART_SFIFO_RXEMPT_SHIFT)                 /*!< UART0_SFIFO: RXEMPT Mask                */
#define UART_SFIFO_RXEMPT_SHIFT                  6                                                   /*!< UART0_SFIFO: RXEMPT Position            */
#define UART_SFIFO_TXEMPT_MASK                   (0x01UL << UART_SFIFO_TXEMPT_SHIFT)                 /*!< UART0_SFIFO: TXEMPT Mask                */
#define UART_SFIFO_TXEMPT_SHIFT                  7                                                   /*!< UART0_SFIFO: TXEMPT Position            */

/* ------- UART0_TWFIFO                             ------ */
#define UART_TWFIFO_TXWATER_MASK                 (0xFFUL << UART_TWFIFO_TXWATER_SHIFT)               /*!< UART0_TWFIFO: TXWATER Mask              */
#define UART_TWFIFO_TXWATER_SHIFT                0                                                   /*!< UART0_TWFIFO: TXWATER Position          */
#define UART_TWFIFO_TXWATER(x)                   (((x)<<UART_TWFIFO_TXWATER_SHIFT)&UART_TWFIFO_TXWATER_MASK) /*!< UART0_TWFIFO                            */

/* ------- UART0_TCFIFO                             ------ */
#define UART_TCFIFO_TXCOUNT_MASK                 (0xFFUL << UART_TCFIFO_TXCOUNT_SHIFT)               /*!< UART0_TCFIFO: TXCOUNT Mask              */
#define UART_TCFIFO_TXCOUNT_SHIFT                0                                                   /*!< UART0_TCFIFO: TXCOUNT Position          */
#define UART_TCFIFO_TXCOUNT(x)                   (((x)<<UART_TCFIFO_TXCOUNT_SHIFT)&UART_TCFIFO_TXCOUNT_MASK) /*!< UART0_TCFIFO                            */

/* ------- UART0_RWFIFO                             ------ */
#define UART_RWFIFO_RXWATER_MASK                 (0xFFUL << UART_RWFIFO_RXWATER_SHIFT)               /*!< UART0_RWFIFO: RXWATER Mask              */
#define UART_RWFIFO_RXWATER_SHIFT                0                                                   /*!< UART0_RWFIFO: RXWATER Position          */
#define UART_RWFIFO_RXWATER(x)                   (((x)<<UART_RWFIFO_RXWATER_SHIFT)&UART_RWFIFO_RXWATER_MASK) /*!< UART0_RWFIFO                            */

/* ------- UART0_RCFIFO                             ------ */
#define UART_RCFIFO_RXCOUNT_MASK                 (0xFFUL << UART_RCFIFO_RXCOUNT_SHIFT)               /*!< UART0_RCFIFO: RXCOUNT Mask              */
#define UART_RCFIFO_RXCOUNT_SHIFT                0                                                   /*!< UART0_RCFIFO: RXCOUNT Position          */
#define UART_RCFIFO_RXCOUNT(x)                   (((x)<<UART_RCFIFO_RXCOUNT_SHIFT)&UART_RCFIFO_RXCOUNT_MASK) /*!< UART0_RCFIFO                            */

/* -------------------------------------------------------------------------------- */
/* -----------     'UART0' Register Access macros                       ----------- */
/* -------------------------------------------------------------------------------- */

#define UART0_BDH                      (UART0->BDH)
#define UART0_BDL                      (UART0->BDL)
#define UART0_C1                       (UART0->C1)
#define UART0_C2                       (UART0->C2)
#define UART0_S1                       (UART0->S1)
#define UART0_S2                       (UART0->S2)
#define UART0_C3                       (UART0->C3)
#define UART0_D                        (UART0->D)
#define UART0_MA1                      (UART0->MA1)
#define UART0_MA2                      (UART0->MA2)
#define UART0_C4                       (UART0->C4)
#define UART0_C5                       (UART0->C5)
#define UART0_ED                       (UART0->ED)
#define UART0_MODEM                    (UART0->MODEM)
#define UART0_PFIFO                    (UART0->PFIFO)
#define UART0_CFIFO                    (UART0->CFIFO)
#define UART0_SFIFO                    (UART0->SFIFO)
#define UART0_TWFIFO                   (UART0->TWFIFO)
#define UART0_TCFIFO                   (UART0->TCFIFO)
#define UART0_RWFIFO                   (UART0->RWFIFO)
#define UART0_RCFIFO                   (UART0->RCFIFO)

/* ================================================================================ */
/* ================           UART1 (derived from UART0)           ================ */
/* ================================================================================ */

/**
 * @brief Universal Asynchronous Receiver/Transmitter
 */
typedef UART0_Type UART1_Type;  /*!< UART1 Structure                                             */


/* -------------------------------------------------------------------------------- */
/* -----------     'UART1' Register Access macros                       ----------- */
/* -------------------------------------------------------------------------------- */

#define UART1_BDH                      (UART1->BDH)
#define UART1_BDL                      (UART1->BDL)
#define UART1_C1                       (UART1->C1)
#define UART1_C2                       (UART1->C2)
#define UART1_S1                       (UART1->S1)
#define UART1_S2                       (UART1->S2)
#define UART1_C3                       (UART1->C3)
#define UART1_D                        (UART1->D)
#define UART1_MA1                      (UART1->MA1)
#define UART1_MA2                      (UART1->MA2)
#define UART1_C4                       (UART1->C4)
#define UART1_C5                       (UART1->C5)
#define UART1_ED                       (UART1->ED)
#define UART1_MODEM                    (UART1->MODEM)
#define UART1_PFIFO                    (UART1->PFIFO)
#define UART1_CFIFO                    (UART1->CFIFO)
#define UART1_SFIFO                    (UART1->SFIFO)
#define UART1_TWFIFO                   (UART1->TWFIFO)
#define UART1_TCFIFO                   (UART1->TCFIFO)
#define UART1_RWFIFO                   (UART1->RWFIFO)
#define UART1_RCFIFO                   (UART1->RCFIFO)

/* ================================================================================ */
/* ================           WDOG (file:WDOG_MK)                  ================ */
/* ================================================================================ */

/**
 * @brief Generation 2008 Watchdog Timer
 */
typedef struct {                                /*!<       WDOG Structure                                               */
   __IO uint16_t  STCTRLH;                      /*!< 0000: Status and Control Register High                             */
   __IO uint16_t  STCTRLL;                      /*!< 0002: Status and Control Register Low                              */
   union {                                      /*!< 0000: (size=0004)                                                  */
      __IO uint32_t  TOVAL;                     /*!< 0004: Time-out Value Register High TOVALL:TOVALH                   */
      struct {                                  /*!< 0000: (size=0004)                                                  */
         __IO uint16_t  TOVALH;                 /*!< 0004: Time-out Value Register High                                 */
         __IO uint16_t  TOVALL;                 /*!< 0006: Time-out Value Register Low                                  */
      };
   };
   union {                                      /*!< 0000: (size=0004)                                                  */
      __IO uint32_t  WIN;                       /*!< 0008: Window Register (WINL:WINH)                                  */
      struct {                                  /*!< 0000: (size=0004)                                                  */
         __IO uint16_t  WINH;                   /*!< 0008: Window Register High                                         */
         __IO uint16_t  WINL;                   /*!< 000A: Window Register Low                                          */
      };
   };
   __IO uint16_t  REFRESH;                      /*!< 000C: Refresh Register                                             */
   __IO uint16_t  UNLOCK;                       /*!< 000E: Unlock Register                                              */
   union {                                      /*!< 0000: (size=0004)                                                  */
      __IO uint32_t  TMROUT;                    /*!< 0010: Timer Output Register (TMROUTL:TMROUTH)                      */
      struct {                                  /*!< 0000: (size=0004)                                                  */
         __IO uint16_t  TMROUTH;                /*!< 0010: Timer Output Register High                                   */
         __IO uint16_t  TMROUTL;                /*!< 0012: Timer Output Register Low                                    */
      };
   };
   __IO uint16_t  RSTCNT;                       /*!< 0014: Reset Count Register                                         */
   __IO uint16_t  PRESC;                        /*!< 0016: Prescaler Register                                           */
} WDOG_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'WDOG' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- WDOG_STCTRLH                             ------ */
#define WDOG_STCTRLH_WDOGEN_MASK                 (0x01UL << WDOG_STCTRLH_WDOGEN_SHIFT)               /*!< WDOG_STCTRLH: WDOGEN Mask               */
#define WDOG_STCTRLH_WDOGEN_SHIFT                0                                                   /*!< WDOG_STCTRLH: WDOGEN Position           */
#define WDOG_STCTRLH_CLKSRC_MASK                 (0x01UL << WDOG_STCTRLH_CLKSRC_SHIFT)               /*!< WDOG_STCTRLH: CLKSRC Mask               */
#define WDOG_STCTRLH_CLKSRC_SHIFT                1                                                   /*!< WDOG_STCTRLH: CLKSRC Position           */
#define WDOG_STCTRLH_IRQRSTEN_MASK               (0x01UL << WDOG_STCTRLH_IRQRSTEN_SHIFT)             /*!< WDOG_STCTRLH: IRQRSTEN Mask             */
#define WDOG_STCTRLH_IRQRSTEN_SHIFT              2                                                   /*!< WDOG_STCTRLH: IRQRSTEN Position         */
#define WDOG_STCTRLH_WINEN_MASK                  (0x01UL << WDOG_STCTRLH_WINEN_SHIFT)                /*!< WDOG_STCTRLH: WINEN Mask                */
#define WDOG_STCTRLH_WINEN_SHIFT                 3                                                   /*!< WDOG_STCTRLH: WINEN Position            */
#define WDOG_STCTRLH_ALLOWUPDATE_MASK            (0x01UL << WDOG_STCTRLH_ALLOWUPDATE_SHIFT)          /*!< WDOG_STCTRLH: ALLOWUPDATE Mask          */
#define WDOG_STCTRLH_ALLOWUPDATE_SHIFT           4                                                   /*!< WDOG_STCTRLH: ALLOWUPDATE Position      */
#define WDOG_STCTRLH_DBGEN_MASK                  (0x01UL << WDOG_STCTRLH_DBGEN_SHIFT)                /*!< WDOG_STCTRLH: DBGEN Mask                */
#define WDOG_STCTRLH_DBGEN_SHIFT                 5                                                   /*!< WDOG_STCTRLH: DBGEN Position            */
#define WDOG_STCTRLH_STOPEN_MASK                 (0x01UL << WDOG_STCTRLH_STOPEN_SHIFT)               /*!< WDOG_STCTRLH: STOPEN Mask               */
#define WDOG_STCTRLH_STOPEN_SHIFT                6                                                   /*!< WDOG_STCTRLH: STOPEN Position           */
#define WDOG_STCTRLH_WAITEN_MASK                 (0x01UL << WDOG_STCTRLH_WAITEN_SHIFT)               /*!< WDOG_STCTRLH: WAITEN Mask               */
#define WDOG_STCTRLH_WAITEN_SHIFT                7                                                   /*!< WDOG_STCTRLH: WAITEN Position           */
#define WDOG_STCTRLH_TESTWDOG_MASK               (0x01UL << WDOG_STCTRLH_TESTWDOG_SHIFT)             /*!< WDOG_STCTRLH: TESTWDOG Mask             */
#define WDOG_STCTRLH_TESTWDOG_SHIFT              10                                                  /*!< WDOG_STCTRLH: TESTWDOG Position         */
#define WDOG_STCTRLH_TESTSEL_MASK                (0x01UL << WDOG_STCTRLH_TESTSEL_SHIFT)              /*!< WDOG_STCTRLH: TESTSEL Mask              */
#define WDOG_STCTRLH_TESTSEL_SHIFT               11                                                  /*!< WDOG_STCTRLH: TESTSEL Position          */
#define WDOG_STCTRLH_BYTESEL_MASK                (0x03UL << WDOG_STCTRLH_BYTESEL_SHIFT)              /*!< WDOG_STCTRLH: BYTESEL Mask              */
#define WDOG_STCTRLH_BYTESEL_SHIFT               12                                                  /*!< WDOG_STCTRLH: BYTESEL Position          */
#define WDOG_STCTRLH_BYTESEL(x)                  (((x)<<WDOG_STCTRLH_BYTESEL_SHIFT)&WDOG_STCTRLH_BYTESEL_MASK) /*!< WDOG_STCTRLH                            */
#define WDOG_STCTRLH_DISTESTWDOG_MASK            (0x01UL << WDOG_STCTRLH_DISTESTWDOG_SHIFT)          /*!< WDOG_STCTRLH: DISTESTWDOG Mask          */
#define WDOG_STCTRLH_DISTESTWDOG_SHIFT           14                                                  /*!< WDOG_STCTRLH: DISTESTWDOG Position      */

/* ------- WDOG_STCTRLL                             ------ */
#define WDOG_STCTRLL_INTFLG_MASK                 (0x01UL << WDOG_STCTRLL_INTFLG_SHIFT)               /*!< WDOG_STCTRLL: INTFLG Mask               */
#define WDOG_STCTRLL_INTFLG_SHIFT                15                                                  /*!< WDOG_STCTRLL: INTFLG Position           */

/* ------- WDOG_TOVAL                               ------ */
#define WDOG_TOVAL_TOVAL_MASK                    (0xFFFFFFFFUL << WDOG_TOVAL_TOVAL_SHIFT)            /*!< WDOG_TOVAL: TOVAL Mask                  */
#define WDOG_TOVAL_TOVAL_SHIFT                   0                                                   /*!< WDOG_TOVAL: TOVAL Position              */
#define WDOG_TOVAL_TOVAL(x)                      (((x)<<WDOG_TOVAL_TOVAL_SHIFT)&WDOG_TOVAL_TOVAL_MASK) /*!< WDOG_TOVAL                              */

/* ------- WDOG_TOVALH                              ------ */
#define WDOG_TOVALH_TOVALHIGH_MASK               (0xFFFFUL << WDOG_TOVALH_TOVALHIGH_SHIFT)           /*!< WDOG_TOVALH: TOVALHIGH Mask             */
#define WDOG_TOVALH_TOVALHIGH_SHIFT              0                                                   /*!< WDOG_TOVALH: TOVALHIGH Position         */
#define WDOG_TOVALH_TOVALHIGH(x)                 (((x)<<WDOG_TOVALH_TOVALHIGH_SHIFT)&WDOG_TOVALH_TOVALHIGH_MASK) /*!< WDOG_TOVALH                             */

/* ------- WDOG_TOVALL                              ------ */
#define WDOG_TOVALL_TOVALLOW_MASK                (0xFFFFUL << WDOG_TOVALL_TOVALLOW_SHIFT)            /*!< WDOG_TOVALL: TOVALLOW Mask              */
#define WDOG_TOVALL_TOVALLOW_SHIFT               0                                                   /*!< WDOG_TOVALL: TOVALLOW Position          */
#define WDOG_TOVALL_TOVALLOW(x)                  (((x)<<WDOG_TOVALL_TOVALLOW_SHIFT)&WDOG_TOVALL_TOVALLOW_MASK) /*!< WDOG_TOVALL                             */

/* ------- WDOG_WIN                                 ------ */
#define WDOG_WIN_WIN_MASK                        (0xFFFFFFFFUL << WDOG_WIN_WIN_SHIFT)                /*!< WDOG_WIN: WIN Mask                      */
#define WDOG_WIN_WIN_SHIFT                       0                                                   /*!< WDOG_WIN: WIN Position                  */
#define WDOG_WIN_WIN(x)                          (((x)<<WDOG_WIN_WIN_SHIFT)&WDOG_WIN_WIN_MASK)       /*!< WDOG_WIN                                */

/* ------- WDOG_WINH                                ------ */
#define WDOG_WINH_WINHIGH_MASK                   (0xFFFFUL << WDOG_WINH_WINHIGH_SHIFT)               /*!< WDOG_WINH: WINHIGH Mask                 */
#define WDOG_WINH_WINHIGH_SHIFT                  0                                                   /*!< WDOG_WINH: WINHIGH Position             */
#define WDOG_WINH_WINHIGH(x)                     (((x)<<WDOG_WINH_WINHIGH_SHIFT)&WDOG_WINH_WINHIGH_MASK) /*!< WDOG_WINH                               */

/* ------- WDOG_WINL                                ------ */
#define WDOG_WINL_WINLOW_MASK                    (0xFFFFUL << WDOG_WINL_WINLOW_SHIFT)                /*!< WDOG_WINL: WINLOW Mask                  */
#define WDOG_WINL_WINLOW_SHIFT                   0                                                   /*!< WDOG_WINL: WINLOW Position              */
#define WDOG_WINL_WINLOW(x)                      (((x)<<WDOG_WINL_WINLOW_SHIFT)&WDOG_WINL_WINLOW_MASK) /*!< WDOG_WINL                               */

/* ------- WDOG_REFRESH                             ------ */
#define WDOG_REFRESH_WDOGREFRESH_MASK            (0xFFFFUL << WDOG_REFRESH_WDOGREFRESH_SHIFT)        /*!< WDOG_REFRESH: WDOGREFRESH Mask          */
#define WDOG_REFRESH_WDOGREFRESH_SHIFT           0                                                   /*!< WDOG_REFRESH: WDOGREFRESH Position      */
#define WDOG_REFRESH_WDOGREFRESH(x)              (((x)<<WDOG_REFRESH_WDOGREFRESH_SHIFT)&WDOG_REFRESH_WDOGREFRESH_MASK) /*!< WDOG_REFRESH                            */

/* ------- WDOG_UNLOCK                              ------ */
#define WDOG_UNLOCK_WDOGUNLOCK_MASK              (0xFFFFUL << WDOG_UNLOCK_WDOGUNLOCK_SHIFT)          /*!< WDOG_UNLOCK: WDOGUNLOCK Mask            */
#define WDOG_UNLOCK_WDOGUNLOCK_SHIFT             0                                                   /*!< WDOG_UNLOCK: WDOGUNLOCK Position        */
#define WDOG_UNLOCK_WDOGUNLOCK(x)                (((x)<<WDOG_UNLOCK_WDOGUNLOCK_SHIFT)&WDOG_UNLOCK_WDOGUNLOCK_MASK) /*!< WDOG_UNLOCK                             */

/* ------- WDOG_TMROUT                              ------ */
#define WDOG_TMROUT_TIMEROUTHIGH_MASK            (0xFFFFFFFFUL << WDOG_TMROUT_TIMEROUTHIGH_SHIFT)    /*!< WDOG_TMROUT: TIMEROUTHIGH Mask          */
#define WDOG_TMROUT_TIMEROUTHIGH_SHIFT           0                                                   /*!< WDOG_TMROUT: TIMEROUTHIGH Position      */
#define WDOG_TMROUT_TIMEROUTHIGH(x)              (((x)<<WDOG_TMROUT_TIMEROUTHIGH_SHIFT)&WDOG_TMROUT_TIMEROUTHIGH_MASK) /*!< WDOG_TMROUT                             */

/* ------- WDOG_TMROUTH                             ------ */
#define WDOG_TMROUTH_TIMEROUTHIGH_MASK           (0xFFFFUL << WDOG_TMROUTH_TIMEROUTHIGH_SHIFT)       /*!< WDOG_TMROUTH: TIMEROUTHIGH Mask         */
#define WDOG_TMROUTH_TIMEROUTHIGH_SHIFT          0                                                   /*!< WDOG_TMROUTH: TIMEROUTHIGH Position     */
#define WDOG_TMROUTH_TIMEROUTHIGH(x)             (((x)<<WDOG_TMROUTH_TIMEROUTHIGH_SHIFT)&WDOG_TMROUTH_TIMEROUTHIGH_MASK) /*!< WDOG_TMROUTH                            */

/* ------- WDOG_TMROUTL                             ------ */
#define WDOG_TMROUTL_TIMEROUTLOW_MASK            (0xFFFFUL << WDOG_TMROUTL_TIMEROUTLOW_SHIFT)        /*!< WDOG_TMROUTL: TIMEROUTLOW Mask          */
#define WDOG_TMROUTL_TIMEROUTLOW_SHIFT           0                                                   /*!< WDOG_TMROUTL: TIMEROUTLOW Position      */
#define WDOG_TMROUTL_TIMEROUTLOW(x)              (((x)<<WDOG_TMROUTL_TIMEROUTLOW_SHIFT)&WDOG_TMROUTL_TIMEROUTLOW_MASK) /*!< WDOG_TMROUTL                            */

/* ------- WDOG_RSTCNT                              ------ */
#define WDOG_RSTCNT_RSTCNT_MASK                  (0xFFFFUL << WDOG_RSTCNT_RSTCNT_SHIFT)              /*!< WDOG_RSTCNT: RSTCNT Mask                */
#define WDOG_RSTCNT_RSTCNT_SHIFT                 0                                                   /*!< WDOG_RSTCNT: RSTCNT Position            */
#define WDOG_RSTCNT_RSTCNT(x)                    (((x)<<WDOG_RSTCNT_RSTCNT_SHIFT)&WDOG_RSTCNT_RSTCNT_MASK) /*!< WDOG_RSTCNT                             */

/* ------- WDOG_PRESC                               ------ */
#define WDOG_PRESC_PRESCVAL_MASK                 (0x07UL << WDOG_PRESC_PRESCVAL_SHIFT)               /*!< WDOG_PRESC: PRESCVAL Mask               */
#define WDOG_PRESC_PRESCVAL_SHIFT                8                                                   /*!< WDOG_PRESC: PRESCVAL Position           */
#define WDOG_PRESC_PRESCVAL(x)                   (((x)<<WDOG_PRESC_PRESCVAL_SHIFT)&WDOG_PRESC_PRESCVAL_MASK) /*!< WDOG_PRESC                              */

/* -------------------------------------------------------------------------------- */
/* -----------     'WDOG' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define WDOG_STCTRLH                   (WDOG->STCTRLH)
#define WDOG_STCTRLL                   (WDOG->STCTRLL)
#define WDOG_TOVAL                     (WDOG->TOVAL)
#define WDOG_TOVALH                    (WDOG->TOVALH)
#define WDOG_TOVALL                    (WDOG->TOVALL)
#define WDOG_WIN                       (WDOG->WIN)
#define WDOG_WINH                      (WDOG->WINH)
#define WDOG_WINL                      (WDOG->WINL)
#define WDOG_REFRESH                   (WDOG->REFRESH)
#define WDOG_UNLOCK                    (WDOG->UNLOCK)
#define WDOG_TMROUT                    (WDOG->TMROUT)
#define WDOG_TMROUTH                   (WDOG->TMROUTH)
#define WDOG_TMROUTL                   (WDOG->TMROUTL)
#define WDOG_RSTCNT                    (WDOG->RSTCNT)
#define WDOG_PRESC                     (WDOG->PRESC)
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
#define ADC1_BASE_PTR                  0x4003C000UL
#define CMP0_BASE_PTR                  0x40073000UL
#define CMP1_BASE_PTR                  0x40073008UL
#define CRC_BASE_PTR                   0x40032000UL
#define DAC0_BASE_PTR                  0x4003F000UL
#define DMA_BASE_PTR                   0x40008000UL
#define DMAMUX_BASE_PTR                0x40021000UL
#define EWM_BASE_PTR                   0x40061000UL
#define FTFA_BASE_PTR                  0x40020000UL
#define FTM0_BASE_PTR                  0x40038000UL
#define FTM1_BASE_PTR                  0x40039000UL
#define FTM2_BASE_PTR                  0x4003A000UL
#define GPIOA_BASE_PTR                 0x400FF000UL
#define GPIOB_BASE_PTR                 0x400FF040UL
#define GPIOC_BASE_PTR                 0x400FF080UL
#define GPIOD_BASE_PTR                 0x400FF0C0UL
#define GPIOE_BASE_PTR                 0x400FF100UL
#define I2C0_BASE_PTR                  0x40066000UL
#define LLWU_BASE_PTR                  0x4007C000UL
#define LPTMR0_BASE_PTR                0x40040000UL
#define MCG_BASE_PTR                   0x40064000UL
#define MCM_BASE_PTR                   0xF0003000UL
#define MMDVSQ_BASE_PTR                0xF0004000UL
#define MTB_BASE_PTR                   0xF0000000UL
#define MTBDWT_BASE_PTR                0xF0001000UL
#define NV_BASE_PTR                    0x00000400UL
#define OSC0_BASE_PTR                  0x40065000UL
#define PDB0_BASE_PTR                  0x40036000UL
#define PMC_BASE_PTR                   0x4007D000UL
#define PORTA_BASE_PTR                 0x40049000UL
#define PORTB_BASE_PTR                 0x4004A000UL
#define PORTC_BASE_PTR                 0x4004B000UL
#define PORTD_BASE_PTR                 0x4004C000UL
#define PORTE_BASE_PTR                 0x4004D000UL
#define RCM_BASE_PTR                   0x4007F000UL
#define ROM_BASE_PTR                   0xF0002000UL
#define SIM_BASE_PTR                   0x40047000UL
#define SMC_BASE_PTR                   0x4007E000UL
#define SPI0_BASE_PTR                  0x4002C000UL
#define UART0_BASE_PTR                 0x4006A000UL
#define UART1_BASE_PTR                 0x4006B000UL
#define WDOG_BASE_PTR                  0x40052000UL

/* ================================================================================ */
/* ================             Peripheral declarations            ================ */
/* ================================================================================ */

#define ADC0                           ((volatile ADC0_Type   *) ADC0_BASE_PTR)
#define ADC1                           ((volatile ADC1_Type   *) ADC1_BASE_PTR)
#define CMP0                           ((volatile CMP0_Type   *) CMP0_BASE_PTR)
#define CMP1                           ((volatile CMP1_Type   *) CMP1_BASE_PTR)
#define CRC                            ((volatile CRC_Type    *) CRC_BASE_PTR)
#define DAC0                           ((volatile DAC0_Type   *) DAC0_BASE_PTR)
#define DMA                            ((volatile DMA_Type    *) DMA_BASE_PTR)
#define DMAMUX                         ((volatile DMAMUX_Type *) DMAMUX_BASE_PTR)
#define EWM                            ((volatile EWM_Type    *) EWM_BASE_PTR)
#define FTFA                           ((volatile FTFA_Type   *) FTFA_BASE_PTR)
#define FTM0                           ((volatile FTM0_Type   *) FTM0_BASE_PTR)
#define FTM1                           ((volatile FTM1_Type   *) FTM1_BASE_PTR)
#define FTM2                           ((volatile FTM2_Type   *) FTM2_BASE_PTR)
#define GPIOA                          ((volatile GPIOA_Type  *) GPIOA_BASE_PTR)
#define GPIOB                          ((volatile GPIOB_Type  *) GPIOB_BASE_PTR)
#define GPIOC                          ((volatile GPIOC_Type  *) GPIOC_BASE_PTR)
#define GPIOD                          ((volatile GPIOD_Type  *) GPIOD_BASE_PTR)
#define GPIOE                          ((volatile GPIOE_Type  *) GPIOE_BASE_PTR)
#define I2C0                           ((volatile I2C0_Type   *) I2C0_BASE_PTR)
#define LLWU                           ((volatile LLWU_Type   *) LLWU_BASE_PTR)
#define LPTMR0                         ((volatile LPTMR0_Type *) LPTMR0_BASE_PTR)
#define MCG                            ((volatile MCG_Type    *) MCG_BASE_PTR)
#define MCM                            ((volatile MCM_Type    *) MCM_BASE_PTR)
#define MMDVSQ                         ((volatile MMDVSQ_Type *) MMDVSQ_BASE_PTR)
#define MTB                            ((volatile MTB_Type    *) MTB_BASE_PTR)
#define MTBDWT                         ((volatile MTBDWT_Type *) MTBDWT_BASE_PTR)
#define NV                             ((volatile NV_Type     *) NV_BASE_PTR)
#define OSC0                           ((volatile OSC0_Type   *) OSC0_BASE_PTR)
#define PDB0                           ((volatile PDB0_Type   *) PDB0_BASE_PTR)
#define PMC                            ((volatile PMC_Type    *) PMC_BASE_PTR)
#define PORTA                          ((volatile PORTA_Type  *) PORTA_BASE_PTR)
#define PORTB                          ((volatile PORTB_Type  *) PORTB_BASE_PTR)
#define PORTC                          ((volatile PORTC_Type  *) PORTC_BASE_PTR)
#define PORTD                          ((volatile PORTD_Type  *) PORTD_BASE_PTR)
#define PORTE                          ((volatile PORTE_Type  *) PORTE_BASE_PTR)
#define RCM                            ((volatile RCM_Type    *) RCM_BASE_PTR)
#define ROM                            ((volatile ROM_Type    *) ROM_BASE_PTR)
#define SIM                            ((volatile SIM_Type    *) SIM_BASE_PTR)
#define SMC                            ((volatile SMC_Type    *) SMC_BASE_PTR)
#define SPI0                           ((volatile SPI0_Type   *) SPI0_BASE_PTR)
#define UART0                          ((volatile UART0_Type  *) UART0_BASE_PTR)
#define UART1                          ((volatile UART1_Type  *) UART1_BASE_PTR)
#define WDOG                           ((volatile WDOG_Type   *) WDOG_BASE_PTR)

#ifdef __cplusplus
}
#endif


#endif  /* MCU_MKV10Z7 */

