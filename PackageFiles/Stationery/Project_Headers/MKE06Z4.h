/****************************************************************************************************//**
 * @file     MKE06Z4.h
 *
 * @brief    CMSIS Cortex-M Peripheral Access Layer Header File for MKE06Z4.
 *           Equivalent: MKE06Z128M4, MKE06Z64M4
 *
 * @version  V0.0
 * @date     2014/06
 *
 *******************************************************************************************************/

#ifndef MCU_MKE06Z4
#define MCU_MKE06Z4

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
/* ----------------------   MKE06Z4 VectorTable                      ---------------------- */
  FTMRE_IRQn                    =   5,   /*!<  21 FTMRE Command complete or error                                                  */
  PMC_IRQn                      =   6,   /*!<  22 PMC Low-voltage detect, low-voltage warning                                      */
  IRQ_IRQn                      =   7,   /*!<  23 External Interrupt                                                               */
  I2C0_IRQn                     =   8,   /*!<  24 I2C Interface 0                                                                  */
  I2C1_IRQn                     =   9,   /*!<  25 I2C Interface 1                                                                  */
  SPI0_IRQn                     =  10,   /*!<  26 Serial Peripheral Interface 0                                                    */
  SPI1_IRQn                     =  11,   /*!<  27 Serial Peripheral Interface 1                                                    */
  UART0_IRQn                    =  12,   /*!<  28 UART0 Status and error                                                           */
  UART1_IRQn                    =  13,   /*!<  29 UART1 Status and error                                                           */
  UART2_IRQn                    =  14,   /*!<  30 UART2 Status and error                                                           */
  ADC0_IRQn                     =  15,   /*!<  31 Analogue to Digital Converter 0                                                  */
  ACMP0_IRQn                    =  16,   /*!<  32 Analogue comparator 0                                                            */
  FTM0_IRQn                     =  17,   /*!<  33 Flexible Timer Module 0                                                          */
  FTM1_IRQn                     =  18,   /*!<  34 Flexible Timer Module 1                                                          */
  FTM2_IRQn                     =  19,   /*!<  35 Flexible Timer Module 2                                                          */
  RTC_IRQn                      =  20,   /*!<  36 Real Time Clock overflow                                                         */
  ACMP1_IRQn                    =  21,   /*!<  37 Analogue comparator 0                                                            */
  PIT_Ch0_IRQn                  =  22,   /*!<  38 Programmable Interrupt Timer Channel 0                                           */
  PIT_Ch1_IRQn                  =  23,   /*!<  39 Programmable Interrupt Timer Channel 1                                           */
  KBI0_IRQn                     =  24,   /*!<  40 Keyboard Interrupt 0                                                             */
  KBI1_IRQn                     =  25,   /*!<  41 Keyboard Interrupt 1                                                             */
  ICS_IRQn                      =  27,   /*!<  43 ICS                                                                              */
  WDOG_IRQn                     =  28,   /*!<  44 Watch dog                                                                        */
  PWT_IRQn                      =  29,   /*!<  45 Pulse Width Timer                                                                */
  MSCAN_RX_IRQn                 =  30,   /*!<  46 MSCAN Rx Interrupt                                                               */
  MSCAN_TX_IRQn                 =  31,   /*!<  47 MSCAN Tx, Err and Wake-up interrupt                                              */
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
extern void FTMRE_IRQHandler(void);
extern void PMC_IRQHandler(void);
extern void IRQ_IRQHandler(void);
extern void I2C0_IRQHandler(void);
extern void I2C1_IRQHandler(void);
extern void SPI0_IRQHandler(void);
extern void SPI1_IRQHandler(void);
extern void UART0_IRQHandler(void);
extern void UART1_IRQHandler(void);
extern void UART2_IRQHandler(void);
extern void ADC0_IRQHandler(void);
extern void ACMP0_IRQHandler(void);
extern void FTM0_IRQHandler(void);
extern void FTM1_IRQHandler(void);
extern void FTM2_IRQHandler(void);
extern void RTC_IRQHandler(void);
extern void ACMP1_IRQHandler(void);
extern void PIT_Ch0_IRQHandler(void);
extern void PIT_Ch1_IRQHandler(void);
extern void KBI0_IRQHandler(void);
extern void KBI1_IRQHandler(void);
extern void ICS_IRQHandler(void);
extern void WDOG_IRQHandler(void);
extern void PWT_IRQHandler(void);
extern void MSCAN_RX_IRQHandler(void);
extern void MSCAN_TX_IRQHandler(void);

/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* ----------------Configuration of the cm4 Processor and Core Peripherals---------------- */
#define __CM0_REV                0x0100
#define __MPU_PRESENT            0
#define __NVIC_PRIO_BITS         2
#define __Vendor_SysTickConfig   0
#define __FPU_PRESENT            0

#include <core_cm0.h>   /*!< Cortex-M4 processor and core peripherals                              */

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
/* ================           ACMP0 (file:ACMP0_MKE)               ================ */
/* ================================================================================ */

/**
 * @brief Analog comparator
 */
typedef struct {                                /*!<       ACMP0 Structure                                              */
   __IO uint8_t   CS;                           /*!< 0000: ACMP Control and Status Register                             */
   __IO uint8_t   C0;                           /*!< 0001: ACMP Control Register 0                                      */
   __IO uint8_t   C1;                           /*!< 0002: ACMP Control Register 1                                      */
   __IO uint8_t   C2;                           /*!< 0003: ACMP Control Register 2                                      */
} ACMP0_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'ACMP0' Position & Mask macros                       ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- ACMP0_CS                                 ------ */
#define ACMP0_CS_ACMOD_MASK                      (0x03UL << ACMP0_CS_ACMOD_SHIFT)                    /*!< ACMP0_CS: ACMOD Mask                    */
#define ACMP0_CS_ACMOD_SHIFT                     0                                                   /*!< ACMP0_CS: ACMOD Position                */
#define ACMP0_CS_ACMOD(x)                        (((x)<<ACMP0_CS_ACMOD_SHIFT)&ACMP0_CS_ACMOD_MASK)   /*!< ACMP0_CS                                */
#define ACMP0_CS_ACOPE_MASK                      (0x01UL << ACMP0_CS_ACOPE_SHIFT)                    /*!< ACMP0_CS: ACOPE Mask                    */
#define ACMP0_CS_ACOPE_SHIFT                     2                                                   /*!< ACMP0_CS: ACOPE Position                */
#define ACMP0_CS_ACO_MASK                        (0x01UL << ACMP0_CS_ACO_SHIFT)                      /*!< ACMP0_CS: ACO Mask                      */
#define ACMP0_CS_ACO_SHIFT                       3                                                   /*!< ACMP0_CS: ACO Position                  */
#define ACMP0_CS_ACIE_MASK                       (0x01UL << ACMP0_CS_ACIE_SHIFT)                     /*!< ACMP0_CS: ACIE Mask                     */
#define ACMP0_CS_ACIE_SHIFT                      4                                                   /*!< ACMP0_CS: ACIE Position                 */
#define ACMP0_CS_ACF_MASK                        (0x01UL << ACMP0_CS_ACF_SHIFT)                      /*!< ACMP0_CS: ACF Mask                      */
#define ACMP0_CS_ACF_SHIFT                       5                                                   /*!< ACMP0_CS: ACF Position                  */
#define ACMP0_CS_HYST_MASK                       (0x01UL << ACMP0_CS_HYST_SHIFT)                     /*!< ACMP0_CS: HYST Mask                     */
#define ACMP0_CS_HYST_SHIFT                      6                                                   /*!< ACMP0_CS: HYST Position                 */
#define ACMP0_CS_ACE_MASK                        (0x01UL << ACMP0_CS_ACE_SHIFT)                      /*!< ACMP0_CS: ACE Mask                      */
#define ACMP0_CS_ACE_SHIFT                       7                                                   /*!< ACMP0_CS: ACE Position                  */

/* ------- ACMP0_C0                                 ------ */
#define ACMP0_C0_ACNSEL_MASK                     (0x03UL << ACMP0_C0_ACNSEL_SHIFT)                   /*!< ACMP0_C0: ACNSEL Mask                   */
#define ACMP0_C0_ACNSEL_SHIFT                    0                                                   /*!< ACMP0_C0: ACNSEL Position               */
#define ACMP0_C0_ACNSEL(x)                       (((x)<<ACMP0_C0_ACNSEL_SHIFT)&ACMP0_C0_ACNSEL_MASK) /*!< ACMP0_C0                                */
#define ACMP0_C0_ACPSEL_MASK                     (0x03UL << ACMP0_C0_ACPSEL_SHIFT)                   /*!< ACMP0_C0: ACPSEL Mask                   */
#define ACMP0_C0_ACPSEL_SHIFT                    4                                                   /*!< ACMP0_C0: ACPSEL Position               */
#define ACMP0_C0_ACPSEL(x)                       (((x)<<ACMP0_C0_ACPSEL_SHIFT)&ACMP0_C0_ACPSEL_MASK) /*!< ACMP0_C0                                */

/* ------- ACMP0_C1                                 ------ */
#define ACMP0_C1_DACVAL_MASK                     (0x3FUL << ACMP0_C1_DACVAL_SHIFT)                   /*!< ACMP0_C1: DACVAL Mask                   */
#define ACMP0_C1_DACVAL_SHIFT                    0                                                   /*!< ACMP0_C1: DACVAL Position               */
#define ACMP0_C1_DACVAL(x)                       (((x)<<ACMP0_C1_DACVAL_SHIFT)&ACMP0_C1_DACVAL_MASK) /*!< ACMP0_C1                                */
#define ACMP0_C1_DACREF_MASK                     (0x01UL << ACMP0_C1_DACREF_SHIFT)                   /*!< ACMP0_C1: DACREF Mask                   */
#define ACMP0_C1_DACREF_SHIFT                    6                                                   /*!< ACMP0_C1: DACREF Position               */
#define ACMP0_C1_DACEN_MASK                      (0x01UL << ACMP0_C1_DACEN_SHIFT)                    /*!< ACMP0_C1: DACEN Mask                    */
#define ACMP0_C1_DACEN_SHIFT                     7                                                   /*!< ACMP0_C1: DACEN Position                */

/* ------- ACMP0_C2                                 ------ */
#define ACMP0_C2_ACIPE_MASK                      (0x07UL << ACMP0_C2_ACIPE_SHIFT)                    /*!< ACMP0_C2: ACIPE Mask                    */
#define ACMP0_C2_ACIPE_SHIFT                     0                                                   /*!< ACMP0_C2: ACIPE Position                */
#define ACMP0_C2_ACIPE(x)                        (((x)<<ACMP0_C2_ACIPE_SHIFT)&ACMP0_C2_ACIPE_MASK)   /*!< ACMP0_C2                                */

/* -------------------------------------------------------------------------------- */
/* -----------     'ACMP0' Register Access macros                       ----------- */
/* -------------------------------------------------------------------------------- */

#define ACMP0_CS                       (ACMP0->CS)
#define ACMP0_C0                       (ACMP0->C0)
#define ACMP0_C1                       (ACMP0->C1)
#define ACMP0_C2                       (ACMP0->C2)

/* ================================================================================ */
/* ================           ACMP1 (derived from ACMP0)           ================ */
/* ================================================================================ */

/**
 * @brief Analog comparator
 */
typedef ACMP0_Type ACMP1_Type;  /*!< ACMP1 Structure                                             */


/* -------------------------------------------------------------------------------- */
/* -----------     'ACMP1' Register Access macros                       ----------- */
/* -------------------------------------------------------------------------------- */

#define ACMP1_CS                       (ACMP1->CS)
#define ACMP1_C0                       (ACMP1->C0)
#define ACMP1_C1                       (ACMP1->C1)
#define ACMP1_C2                       (ACMP1->C2)

/* ================================================================================ */
/* ================           ADC (file:ADC_MKE04)                 ================ */
/* ================================================================================ */

/**
 * @brief Analog-to-digital converter
 */
typedef struct {                                /*!<       ADC Structure                                                */
   __IO uint32_t  SC1;                          /*!< 0000: Status and Control Register 1                                */
   __IO uint32_t  SC2;                          /*!< 0004: Status and Control Register 2                                */
   __IO uint32_t  SC3;                          /*!< 0008: Status and Control Register 3                                */
   __IO uint32_t  SC4;                          /*!< 000C: Status and Control Register 4                                */
   __I  uint32_t  R;                            /*!< 0010: Conversion Result Register                                   */
   __IO uint32_t  CV;                           /*!< 0014: Compare Value Register                                       */
   __IO uint32_t  APCTL1;                       /*!< 0018: Pin Control 1 Register                                       */
   __IO uint32_t  SC5;                          /*!< 001C: Status and Control Register 5                                */
} ADC_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'ADC' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- ADC_SC1                                  ------ */
#define ADC_SC1_ADCH_MASK                        (0x1FUL << ADC_SC1_ADCH_SHIFT)                      /*!< ADC_SC1: ADCH Mask                      */
#define ADC_SC1_ADCH_SHIFT                       0                                                   /*!< ADC_SC1: ADCH Position                  */
#define ADC_SC1_ADCH(x)                          (((x)<<ADC_SC1_ADCH_SHIFT)&ADC_SC1_ADCH_MASK)       /*!< ADC_SC1                                 */
#define ADC_SC1_ADCO_MASK                        (0x01UL << ADC_SC1_ADCO_SHIFT)                      /*!< ADC_SC1: ADCO Mask                      */
#define ADC_SC1_ADCO_SHIFT                       5                                                   /*!< ADC_SC1: ADCO Position                  */
#define ADC_SC1_AIEN_MASK                        (0x01UL << ADC_SC1_AIEN_SHIFT)                      /*!< ADC_SC1: AIEN Mask                      */
#define ADC_SC1_AIEN_SHIFT                       6                                                   /*!< ADC_SC1: AIEN Position                  */
#define ADC_SC1_COCO_MASK                        (0x01UL << ADC_SC1_COCO_SHIFT)                      /*!< ADC_SC1: COCO Mask                      */
#define ADC_SC1_COCO_SHIFT                       7                                                   /*!< ADC_SC1: COCO Position                  */

/* ------- ADC_SC2                                  ------ */
#define ADC_SC2_REFSEL_MASK                      (0x03UL << ADC_SC2_REFSEL_SHIFT)                    /*!< ADC_SC2: REFSEL Mask                    */
#define ADC_SC2_REFSEL_SHIFT                     0                                                   /*!< ADC_SC2: REFSEL Position                */
#define ADC_SC2_REFSEL(x)                        (((x)<<ADC_SC2_REFSEL_SHIFT)&ADC_SC2_REFSEL_MASK)   /*!< ADC_SC2                                 */
#define ADC_SC2_FFULL_MASK                       (0x01UL << ADC_SC2_FFULL_SHIFT)                     /*!< ADC_SC2: FFULL Mask                     */
#define ADC_SC2_FFULL_SHIFT                      2                                                   /*!< ADC_SC2: FFULL Position                 */
#define ADC_SC2_FEMPTY_MASK                      (0x01UL << ADC_SC2_FEMPTY_SHIFT)                    /*!< ADC_SC2: FEMPTY Mask                    */
#define ADC_SC2_FEMPTY_SHIFT                     3                                                   /*!< ADC_SC2: FEMPTY Position                */
#define ADC_SC2_ACFGT_MASK                       (0x01UL << ADC_SC2_ACFGT_SHIFT)                     /*!< ADC_SC2: ACFGT Mask                     */
#define ADC_SC2_ACFGT_SHIFT                      4                                                   /*!< ADC_SC2: ACFGT Position                 */
#define ADC_SC2_ACFE_MASK                        (0x01UL << ADC_SC2_ACFE_SHIFT)                      /*!< ADC_SC2: ACFE Mask                      */
#define ADC_SC2_ACFE_SHIFT                       5                                                   /*!< ADC_SC2: ACFE Position                  */
#define ADC_SC2_ADTRG_MASK                       (0x01UL << ADC_SC2_ADTRG_SHIFT)                     /*!< ADC_SC2: ADTRG Mask                     */
#define ADC_SC2_ADTRG_SHIFT                      6                                                   /*!< ADC_SC2: ADTRG Position                 */
#define ADC_SC2_ADACT_MASK                       (0x01UL << ADC_SC2_ADACT_SHIFT)                     /*!< ADC_SC2: ADACT Mask                     */
#define ADC_SC2_ADACT_SHIFT                      7                                                   /*!< ADC_SC2: ADACT Position                 */

/* ------- ADC_SC3                                  ------ */
#define ADC_SC3_ADICLK_MASK                      (0x03UL << ADC_SC3_ADICLK_SHIFT)                    /*!< ADC_SC3: ADICLK Mask                    */
#define ADC_SC3_ADICLK_SHIFT                     0                                                   /*!< ADC_SC3: ADICLK Position                */
#define ADC_SC3_ADICLK(x)                        (((x)<<ADC_SC3_ADICLK_SHIFT)&ADC_SC3_ADICLK_MASK)   /*!< ADC_SC3                                 */
#define ADC_SC3_MODE_MASK                        (0x03UL << ADC_SC3_MODE_SHIFT)                      /*!< ADC_SC3: MODE Mask                      */
#define ADC_SC3_MODE_SHIFT                       2                                                   /*!< ADC_SC3: MODE Position                  */
#define ADC_SC3_MODE(x)                          (((x)<<ADC_SC3_MODE_SHIFT)&ADC_SC3_MODE_MASK)       /*!< ADC_SC3                                 */
#define ADC_SC3_ADLSMP_MASK                      (0x01UL << ADC_SC3_ADLSMP_SHIFT)                    /*!< ADC_SC3: ADLSMP Mask                    */
#define ADC_SC3_ADLSMP_SHIFT                     4                                                   /*!< ADC_SC3: ADLSMP Position                */
#define ADC_SC3_ADIV_MASK                        (0x03UL << ADC_SC3_ADIV_SHIFT)                      /*!< ADC_SC3: ADIV Mask                      */
#define ADC_SC3_ADIV_SHIFT                       5                                                   /*!< ADC_SC3: ADIV Position                  */
#define ADC_SC3_ADIV(x)                          (((x)<<ADC_SC3_ADIV_SHIFT)&ADC_SC3_ADIV_MASK)       /*!< ADC_SC3                                 */
#define ADC_SC3_ADLPC_MASK                       (0x01UL << ADC_SC3_ADLPC_SHIFT)                     /*!< ADC_SC3: ADLPC Mask                     */
#define ADC_SC3_ADLPC_SHIFT                      7                                                   /*!< ADC_SC3: ADLPC Position                 */

/* ------- ADC_SC4                                  ------ */
#define ADC_SC4_AFDEP_MASK                       (0x07UL << ADC_SC4_AFDEP_SHIFT)                     /*!< ADC_SC4: AFDEP Mask                     */
#define ADC_SC4_AFDEP_SHIFT                      0                                                   /*!< ADC_SC4: AFDEP Position                 */
#define ADC_SC4_AFDEP(x)                         (((x)<<ADC_SC4_AFDEP_SHIFT)&ADC_SC4_AFDEP_MASK)     /*!< ADC_SC4                                 */
#define ADC_SC4_ACFSEL_MASK                      (0x01UL << ADC_SC4_ACFSEL_SHIFT)                    /*!< ADC_SC4: ACFSEL Mask                    */
#define ADC_SC4_ACFSEL_SHIFT                     5                                                   /*!< ADC_SC4: ACFSEL Position                */
#define ADC_SC4_ASCANE_MASK                      (0x01UL << ADC_SC4_ASCANE_SHIFT)                    /*!< ADC_SC4: ASCANE Mask                    */
#define ADC_SC4_ASCANE_SHIFT                     6                                                   /*!< ADC_SC4: ASCANE Position                */
#define ADC_SC4_HTRGME_MASK                      (0x01UL << ADC_SC4_HTRGME_SHIFT)                    /*!< ADC_SC4: HTRGME Mask                    */
#define ADC_SC4_HTRGME_SHIFT                     8                                                   /*!< ADC_SC4: HTRGME Position                */

/* ------- ADC_R                                    ------ */
#define ADC_R_ADR_MASK                           (0xFFFUL << ADC_R_ADR_SHIFT)                        /*!< ADC_R: ADR Mask                         */
#define ADC_R_ADR_SHIFT                          0                                                   /*!< ADC_R: ADR Position                     */
#define ADC_R_ADR(x)                             (((x)<<ADC_R_ADR_SHIFT)&ADC_R_ADR_MASK)             /*!< ADC_R                                   */

/* ------- ADC_CV                                   ------ */
#define ADC_CV_ADR_MASK                          (0xFFFUL << ADC_CV_ADR_SHIFT)                       /*!< ADC_CV: ADR Mask                        */
#define ADC_CV_ADR_SHIFT                         0                                                   /*!< ADC_CV: ADR Position                    */
#define ADC_CV_ADR(x)                            (((x)<<ADC_CV_ADR_SHIFT)&ADC_CV_ADR_MASK)           /*!< ADC_CV                                  */

/* ------- ADC_APCTL1                               ------ */
#define ADC_APCTL1_ADPC_MASK                     (0xFFFFUL << ADC_APCTL1_ADPC_SHIFT)                 /*!< ADC_APCTL1: ADPC Mask                   */
#define ADC_APCTL1_ADPC_SHIFT                    0                                                   /*!< ADC_APCTL1: ADPC Position               */
#define ADC_APCTL1_ADPC(x)                       (((x)<<ADC_APCTL1_ADPC_SHIFT)&ADC_APCTL1_ADPC_MASK) /*!< ADC_APCTL1                              */

/* ------- ADC_SC5                                  ------ */
#define ADC_SC5_HTRGMASKSEL_MASK                 (0x01UL << ADC_SC5_HTRGMASKSEL_SHIFT)               /*!< ADC_SC5: HTRGMASKSEL Mask               */
#define ADC_SC5_HTRGMASKSEL_SHIFT                0                                                   /*!< ADC_SC5: HTRGMASKSEL Position           */
#define ADC_SC5_HTRGMASKE_MASK                   (0x01UL << ADC_SC5_HTRGMASKE_SHIFT)                 /*!< ADC_SC5: HTRGMASKE Mask                 */
#define ADC_SC5_HTRGMASKE_SHIFT                  1                                                   /*!< ADC_SC5: HTRGMASKE Position             */

/* -------------------------------------------------------------------------------- */
/* -----------     'ADC' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define ADC_SC1                        (ADC->SC1)
#define ADC_SC2                        (ADC->SC2)
#define ADC_SC3                        (ADC->SC3)
#define ADC_SC4                        (ADC->SC4)
#define ADC_R                          (ADC->R)
#define ADC_CV                         (ADC->CV)
#define ADC_APCTL1                     (ADC->APCTL1)
#define ADC_SC5                        (ADC->SC5)

/* ================================================================================ */
/* ================           BP (file:BP_1_MKE)                   ================ */
/* ================================================================================ */

/**
 * @brief Breakpoint Unit
 */
typedef struct {                                /*!<       BP Structure                                                 */
   __IO uint32_t  CTRL;                         /*!< 0000:                                                              */
   __I  uint32_t  RESERVED0;                    /*!< 0004:                                                              */
   __IO uint32_t  COMP[2];                      /*!< 0008:                                                              */
   __I  uint32_t  RESERVED1[1008];              /*!< 0010:                                                              */
   __IO uint32_t  PID4;                         /*!< 0FD0:                                                              */
   __IO uint32_t  PID5;                         /*!< 0FD4:                                                              */
   __IO uint32_t  PID6;                         /*!< 0FD8:                                                              */
   __IO uint32_t  PID7;                         /*!< 0FDC:                                                              */
   __IO uint32_t  PID0;                         /*!< 0FE0:                                                              */
   __IO uint32_t  PID1;                         /*!< 0FE4:                                                              */
   __IO uint32_t  PID2;                         /*!< 0FE8:                                                              */
   __IO uint32_t  PID3;                         /*!< 0FEC:                                                              */
   __IO uint32_t  CID[4];                       /*!< 0FF0:                                                              */
} BP_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'BP' Position & Mask macros                          ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- BP_CTRL                                  ------ */

/* ------- BP_COMP                                  ------ */

/* ------- BP_PID                                   ------ */

/* ------- BP_CID                                   ------ */

/* -------------------------------------------------------------------------------- */
/* -----------     'BP' Register Access macros                          ----------- */
/* -------------------------------------------------------------------------------- */

#define BP_CTRL                        (BP->CTRL)
#define BP_COMP0                       (BP->COMP[0])
#define BP_COMP1                       (BP->COMP[1])
#define BP_PID4                        (BP->PID4)
#define BP_PID5                        (BP->PID5)
#define BP_PID6                        (BP->PID6)
#define BP_PID7                        (BP->PID7)
#define BP_PID0                        (BP->PID0)
#define BP_PID1                        (BP->PID1)
#define BP_PID2                        (BP->PID2)
#define BP_PID3                        (BP->PID3)
#define BP_CID0                        (BP->CID[0])
#define BP_CID1                        (BP->CID[1])
#define BP_CID2                        (BP->CID[2])
#define BP_CID3                        (BP->CID[3])

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
/* ================           FGPIOA (file:FGPIOA_MKE)             ================ */
/* ================================================================================ */

/**
 * @brief General Purpose Input/Output
 */
typedef struct {                                /*!<       FGPIOA Structure                                             */
   __IO uint32_t  PDOR;                         /*!< 0000: Port Data Output Register                                    */
   __O  uint32_t  PSOR;                         /*!< 0004: Port Set Output Register                                     */
   __O  uint32_t  PCOR;                         /*!< 0008: Port Clear Output Register                                   */
   __O  uint32_t  PTOR;                         /*!< 000C: Port Toggle Output Register                                  */
   __IO uint32_t  PDIR;                         /*!< 0010: Port Data Input Register                                     */
   __IO uint32_t  PDDR;                         /*!< 0014: Port Data Direction Register                                 */
   __I  uint32_t  PIDR;                         /*!< 0018: Port Input Disable Register                                  */
} FGPIOA_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'FGPIOA' Position & Mask macros                      ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- FGPIOA_PDOR                              ------ */
#define GPIO_PDOR_PTA_MASK                       (0xFFUL << GPIO_PDOR_PTA_SHIFT)                     /*!< FGPIOA_PDOR: PTA Mask                   */
#define GPIO_PDOR_PTA_SHIFT                      0                                                   /*!< FGPIOA_PDOR: PTA Position               */
#define GPIO_PDOR_PTA(x)                         (((x)<<GPIO_PDOR_PTA_SHIFT)&GPIO_PDOR_PTA_MASK)     /*!< FGPIOA_PDOR                             */
#define GPIO_PDOR_PTB_MASK                       (0xFFUL << GPIO_PDOR_PTB_SHIFT)                     /*!< FGPIOA_PDOR: PTB Mask                   */
#define GPIO_PDOR_PTB_SHIFT                      8                                                   /*!< FGPIOA_PDOR: PTB Position               */
#define GPIO_PDOR_PTB(x)                         (((x)<<GPIO_PDOR_PTB_SHIFT)&GPIO_PDOR_PTB_MASK)     /*!< FGPIOA_PDOR                             */
#define GPIO_PDOR_PTC_MASK                       (0xFFUL << GPIO_PDOR_PTC_SHIFT)                     /*!< FGPIOA_PDOR: PTC Mask                   */
#define GPIO_PDOR_PTC_SHIFT                      16                                                  /*!< FGPIOA_PDOR: PTC Position               */
#define GPIO_PDOR_PTC(x)                         (((x)<<GPIO_PDOR_PTC_SHIFT)&GPIO_PDOR_PTC_MASK)     /*!< FGPIOA_PDOR                             */
#define GPIO_PDOR_PTD_MASK                       (0xFFUL << GPIO_PDOR_PTD_SHIFT)                     /*!< FGPIOA_PDOR: PTD Mask                   */
#define GPIO_PDOR_PTD_SHIFT                      24                                                  /*!< FGPIOA_PDOR: PTD Position               */
#define GPIO_PDOR_PTD(x)                         (((x)<<GPIO_PDOR_PTD_SHIFT)&GPIO_PDOR_PTD_MASK)     /*!< FGPIOA_PDOR                             */

/* ------- FGPIOA_PSOR                              ------ */
#define GPIO_PSOR_PTA_MASK                       (0xFFUL << GPIO_PSOR_PTA_SHIFT)                     /*!< FGPIOA_PSOR: PTA Mask                   */
#define GPIO_PSOR_PTA_SHIFT                      0                                                   /*!< FGPIOA_PSOR: PTA Position               */
#define GPIO_PSOR_PTA(x)                         (((x)<<GPIO_PSOR_PTA_SHIFT)&GPIO_PSOR_PTA_MASK)     /*!< FGPIOA_PSOR                             */
#define GPIO_PSOR_PTB_MASK                       (0xFFUL << GPIO_PSOR_PTB_SHIFT)                     /*!< FGPIOA_PSOR: PTB Mask                   */
#define GPIO_PSOR_PTB_SHIFT                      8                                                   /*!< FGPIOA_PSOR: PTB Position               */
#define GPIO_PSOR_PTB(x)                         (((x)<<GPIO_PSOR_PTB_SHIFT)&GPIO_PSOR_PTB_MASK)     /*!< FGPIOA_PSOR                             */
#define GPIO_PSOR_PTC_MASK                       (0xFFUL << GPIO_PSOR_PTC_SHIFT)                     /*!< FGPIOA_PSOR: PTC Mask                   */
#define GPIO_PSOR_PTC_SHIFT                      16                                                  /*!< FGPIOA_PSOR: PTC Position               */
#define GPIO_PSOR_PTC(x)                         (((x)<<GPIO_PSOR_PTC_SHIFT)&GPIO_PSOR_PTC_MASK)     /*!< FGPIOA_PSOR                             */
#define GPIO_PSOR_PTD_MASK                       (0xFFUL << GPIO_PSOR_PTD_SHIFT)                     /*!< FGPIOA_PSOR: PTD Mask                   */
#define GPIO_PSOR_PTD_SHIFT                      24                                                  /*!< FGPIOA_PSOR: PTD Position               */
#define GPIO_PSOR_PTD(x)                         (((x)<<GPIO_PSOR_PTD_SHIFT)&GPIO_PSOR_PTD_MASK)     /*!< FGPIOA_PSOR                             */

/* ------- FGPIOA_PCOR                              ------ */
#define GPIO_PCOR_PTA_MASK                       (0xFFUL << GPIO_PCOR_PTA_SHIFT)                     /*!< FGPIOA_PCOR: PTA Mask                   */
#define GPIO_PCOR_PTA_SHIFT                      0                                                   /*!< FGPIOA_PCOR: PTA Position               */
#define GPIO_PCOR_PTA(x)                         (((x)<<GPIO_PCOR_PTA_SHIFT)&GPIO_PCOR_PTA_MASK)     /*!< FGPIOA_PCOR                             */
#define GPIO_PCOR_PTB_MASK                       (0xFFUL << GPIO_PCOR_PTB_SHIFT)                     /*!< FGPIOA_PCOR: PTB Mask                   */
#define GPIO_PCOR_PTB_SHIFT                      8                                                   /*!< FGPIOA_PCOR: PTB Position               */
#define GPIO_PCOR_PTB(x)                         (((x)<<GPIO_PCOR_PTB_SHIFT)&GPIO_PCOR_PTB_MASK)     /*!< FGPIOA_PCOR                             */
#define GPIO_PCOR_PTC_MASK                       (0xFFUL << GPIO_PCOR_PTC_SHIFT)                     /*!< FGPIOA_PCOR: PTC Mask                   */
#define GPIO_PCOR_PTC_SHIFT                      16                                                  /*!< FGPIOA_PCOR: PTC Position               */
#define GPIO_PCOR_PTC(x)                         (((x)<<GPIO_PCOR_PTC_SHIFT)&GPIO_PCOR_PTC_MASK)     /*!< FGPIOA_PCOR                             */
#define GPIO_PCOR_PTD_MASK                       (0xFFUL << GPIO_PCOR_PTD_SHIFT)                     /*!< FGPIOA_PCOR: PTD Mask                   */
#define GPIO_PCOR_PTD_SHIFT                      24                                                  /*!< FGPIOA_PCOR: PTD Position               */
#define GPIO_PCOR_PTD(x)                         (((x)<<GPIO_PCOR_PTD_SHIFT)&GPIO_PCOR_PTD_MASK)     /*!< FGPIOA_PCOR                             */

/* ------- FGPIOA_PTOR                              ------ */
#define GPIO_PTOR_PTA_MASK                       (0xFFUL << GPIO_PTOR_PTA_SHIFT)                     /*!< FGPIOA_PTOR: PTA Mask                   */
#define GPIO_PTOR_PTA_SHIFT                      0                                                   /*!< FGPIOA_PTOR: PTA Position               */
#define GPIO_PTOR_PTA(x)                         (((x)<<GPIO_PTOR_PTA_SHIFT)&GPIO_PTOR_PTA_MASK)     /*!< FGPIOA_PTOR                             */
#define GPIO_PTOR_PTB_MASK                       (0xFFUL << GPIO_PTOR_PTB_SHIFT)                     /*!< FGPIOA_PTOR: PTB Mask                   */
#define GPIO_PTOR_PTB_SHIFT                      8                                                   /*!< FGPIOA_PTOR: PTB Position               */
#define GPIO_PTOR_PTB(x)                         (((x)<<GPIO_PTOR_PTB_SHIFT)&GPIO_PTOR_PTB_MASK)     /*!< FGPIOA_PTOR                             */
#define GPIO_PTOR_PTC_MASK                       (0xFFUL << GPIO_PTOR_PTC_SHIFT)                     /*!< FGPIOA_PTOR: PTC Mask                   */
#define GPIO_PTOR_PTC_SHIFT                      16                                                  /*!< FGPIOA_PTOR: PTC Position               */
#define GPIO_PTOR_PTC(x)                         (((x)<<GPIO_PTOR_PTC_SHIFT)&GPIO_PTOR_PTC_MASK)     /*!< FGPIOA_PTOR                             */
#define GPIO_PTOR_PTD_MASK                       (0xFFUL << GPIO_PTOR_PTD_SHIFT)                     /*!< FGPIOA_PTOR: PTD Mask                   */
#define GPIO_PTOR_PTD_SHIFT                      24                                                  /*!< FGPIOA_PTOR: PTD Position               */
#define GPIO_PTOR_PTD(x)                         (((x)<<GPIO_PTOR_PTD_SHIFT)&GPIO_PTOR_PTD_MASK)     /*!< FGPIOA_PTOR                             */

/* ------- FGPIOA_PDIR                              ------ */
#define GPIO_PDIR_PTA_MASK                       (0xFFUL << GPIO_PDIR_PTA_SHIFT)                     /*!< FGPIOA_PDIR: PTA Mask                   */
#define GPIO_PDIR_PTA_SHIFT                      0                                                   /*!< FGPIOA_PDIR: PTA Position               */
#define GPIO_PDIR_PTA(x)                         (((x)<<GPIO_PDIR_PTA_SHIFT)&GPIO_PDIR_PTA_MASK)     /*!< FGPIOA_PDIR                             */
#define GPIO_PDIR_PTB_MASK                       (0xFFUL << GPIO_PDIR_PTB_SHIFT)                     /*!< FGPIOA_PDIR: PTB Mask                   */
#define GPIO_PDIR_PTB_SHIFT                      8                                                   /*!< FGPIOA_PDIR: PTB Position               */
#define GPIO_PDIR_PTB(x)                         (((x)<<GPIO_PDIR_PTB_SHIFT)&GPIO_PDIR_PTB_MASK)     /*!< FGPIOA_PDIR                             */
#define GPIO_PDIR_PTC_MASK                       (0xFFUL << GPIO_PDIR_PTC_SHIFT)                     /*!< FGPIOA_PDIR: PTC Mask                   */
#define GPIO_PDIR_PTC_SHIFT                      16                                                  /*!< FGPIOA_PDIR: PTC Position               */
#define GPIO_PDIR_PTC(x)                         (((x)<<GPIO_PDIR_PTC_SHIFT)&GPIO_PDIR_PTC_MASK)     /*!< FGPIOA_PDIR                             */
#define GPIO_PDIR_PTD_MASK                       (0xFFUL << GPIO_PDIR_PTD_SHIFT)                     /*!< FGPIOA_PDIR: PTD Mask                   */
#define GPIO_PDIR_PTD_SHIFT                      24                                                  /*!< FGPIOA_PDIR: PTD Position               */
#define GPIO_PDIR_PTD(x)                         (((x)<<GPIO_PDIR_PTD_SHIFT)&GPIO_PDIR_PTD_MASK)     /*!< FGPIOA_PDIR                             */

/* ------- FGPIOA_PDDR                              ------ */
#define GPIO_PDDR_PTA_MASK                       (0xFFUL << GPIO_PDDR_PTA_SHIFT)                     /*!< FGPIOA_PDDR: PTA Mask                   */
#define GPIO_PDDR_PTA_SHIFT                      0                                                   /*!< FGPIOA_PDDR: PTA Position               */
#define GPIO_PDDR_PTA(x)                         (((x)<<GPIO_PDDR_PTA_SHIFT)&GPIO_PDDR_PTA_MASK)     /*!< FGPIOA_PDDR                             */
#define GPIO_PDDR_PTB_MASK                       (0xFFUL << GPIO_PDDR_PTB_SHIFT)                     /*!< FGPIOA_PDDR: PTB Mask                   */
#define GPIO_PDDR_PTB_SHIFT                      8                                                   /*!< FGPIOA_PDDR: PTB Position               */
#define GPIO_PDDR_PTB(x)                         (((x)<<GPIO_PDDR_PTB_SHIFT)&GPIO_PDDR_PTB_MASK)     /*!< FGPIOA_PDDR                             */
#define GPIO_PDDR_PTC_MASK                       (0xFFUL << GPIO_PDDR_PTC_SHIFT)                     /*!< FGPIOA_PDDR: PTC Mask                   */
#define GPIO_PDDR_PTC_SHIFT                      16                                                  /*!< FGPIOA_PDDR: PTC Position               */
#define GPIO_PDDR_PTC(x)                         (((x)<<GPIO_PDDR_PTC_SHIFT)&GPIO_PDDR_PTC_MASK)     /*!< FGPIOA_PDDR                             */
#define GPIO_PDDR_PTD_MASK                       (0xFFUL << GPIO_PDDR_PTD_SHIFT)                     /*!< FGPIOA_PDDR: PTD Mask                   */
#define GPIO_PDDR_PTD_SHIFT                      24                                                  /*!< FGPIOA_PDDR: PTD Position               */
#define GPIO_PDDR_PTD(x)                         (((x)<<GPIO_PDDR_PTD_SHIFT)&GPIO_PDDR_PTD_MASK)     /*!< FGPIOA_PDDR                             */

/* ------- FGPIOA_PIDR                              ------ */
#define GPIO_PIDR_PTA_MASK                       (0xFFUL << GPIO_PIDR_PTA_SHIFT)                     /*!< FGPIOA_PIDR: PTA Mask                   */
#define GPIO_PIDR_PTA_SHIFT                      0                                                   /*!< FGPIOA_PIDR: PTA Position               */
#define GPIO_PIDR_PTA(x)                         (((x)<<GPIO_PIDR_PTA_SHIFT)&GPIO_PIDR_PTA_MASK)     /*!< FGPIOA_PIDR                             */
#define GPIO_PIDR_PTB_MASK                       (0xFFUL << GPIO_PIDR_PTB_SHIFT)                     /*!< FGPIOA_PIDR: PTB Mask                   */
#define GPIO_PIDR_PTB_SHIFT                      8                                                   /*!< FGPIOA_PIDR: PTB Position               */
#define GPIO_PIDR_PTB(x)                         (((x)<<GPIO_PIDR_PTB_SHIFT)&GPIO_PIDR_PTB_MASK)     /*!< FGPIOA_PIDR                             */
#define GPIO_PIDR_PTC_MASK                       (0xFFUL << GPIO_PIDR_PTC_SHIFT)                     /*!< FGPIOA_PIDR: PTC Mask                   */
#define GPIO_PIDR_PTC_SHIFT                      16                                                  /*!< FGPIOA_PIDR: PTC Position               */
#define GPIO_PIDR_PTC(x)                         (((x)<<GPIO_PIDR_PTC_SHIFT)&GPIO_PIDR_PTC_MASK)     /*!< FGPIOA_PIDR                             */
#define GPIO_PIDR_PTD_MASK                       (0xFFUL << GPIO_PIDR_PTD_SHIFT)                     /*!< FGPIOA_PIDR: PTD Mask                   */
#define GPIO_PIDR_PTD_SHIFT                      24                                                  /*!< FGPIOA_PIDR: PTD Position               */
#define GPIO_PIDR_PTD(x)                         (((x)<<GPIO_PIDR_PTD_SHIFT)&GPIO_PIDR_PTD_MASK)     /*!< FGPIOA_PIDR                             */

/* -------------------------------------------------------------------------------- */
/* -----------     'FGPIOA' Register Access macros                      ----------- */
/* -------------------------------------------------------------------------------- */

#define FGPIOA_PDOR                    (FGPIOA->PDOR)
#define FGPIOA_PSOR                    (FGPIOA->PSOR)
#define FGPIOA_PCOR                    (FGPIOA->PCOR)
#define FGPIOA_PTOR                    (FGPIOA->PTOR)
#define FGPIOA_PDIR                    (FGPIOA->PDIR)
#define FGPIOA_PDDR                    (FGPIOA->PDDR)
#define FGPIOA_PIDR                    (FGPIOA->PIDR)

/* ================================================================================ */
/* ================           FGPIOB (file:FGPIOB_MKE)             ================ */
/* ================================================================================ */

/**
 * @brief General Purpose Input/Output
 */
typedef struct {                                /*!<       FGPIOB Structure                                             */
   __IO uint32_t  PDOR;                         /*!< 0000: Port Data Output Register                                    */
   __O  uint32_t  PSOR;                         /*!< 0004: Port Set Output Register                                     */
   __O  uint32_t  PCOR;                         /*!< 0008: Port Clear Output Register                                   */
   __O  uint32_t  PTOR;                         /*!< 000C: Port Toggle Output Register                                  */
   __IO uint32_t  PDIR;                         /*!< 0010: Port Data Input Register                                     */
   __IO uint32_t  PDDR;                         /*!< 0014: Port Data Direction Register                                 */
   __I  uint32_t  PIDR;                         /*!< 0018: Port Input Disable Register                                  */
} FGPIOB_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'FGPIOB' Position & Mask macros                      ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- FGPIOB_PDOR                              ------ */

/* ------- FGPIOB_PSOR                              ------ */

/* ------- FGPIOB_PCOR                              ------ */

/* ------- FGPIOB_PTOR                              ------ */

/* ------- FGPIOB_PDIR                              ------ */

/* ------- FGPIOB_PDDR                              ------ */

/* ------- FGPIOB_PIDR                              ------ */

/* -------------------------------------------------------------------------------- */
/* -----------     'FGPIOB' Register Access macros                      ----------- */
/* -------------------------------------------------------------------------------- */

#define FGPIOB_PDOR                    (FGPIOB->PDOR)
#define FGPIOB_PSOR                    (FGPIOB->PSOR)
#define FGPIOB_PCOR                    (FGPIOB->PCOR)
#define FGPIOB_PTOR                    (FGPIOB->PTOR)
#define FGPIOB_PDIR                    (FGPIOB->PDIR)
#define FGPIOB_PDDR                    (FGPIOB->PDDR)
#define FGPIOB_PIDR                    (FGPIOB->PIDR)

/* ================================================================================ */
/* ================           FGPIOC (file:FGPIOC_MKE)             ================ */
/* ================================================================================ */

/**
 * @brief General Purpose Input/Output
 */
typedef struct {                                /*!<       FGPIOC Structure                                             */
   __IO uint32_t  PDOR;                         /*!< 0000: Port Data Output Register                                    */
   __O  uint32_t  PSOR;                         /*!< 0004: Port Set Output Register                                     */
   __O  uint32_t  PCOR;                         /*!< 0008: Port Clear Output Register                                   */
   __O  uint32_t  PTOR;                         /*!< 000C: Port Toggle Output Register                                  */
   __IO uint32_t  PDIR;                         /*!< 0010: Port Data Input Register                                     */
   __IO uint32_t  PDDR;                         /*!< 0014: Port Data Direction Register                                 */
   __I  uint32_t  PIDR;                         /*!< 0018: Port Input Disable Register                                  */
} FGPIOC_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'FGPIOC' Position & Mask macros                      ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- FGPIOC_PDOR                              ------ */

/* ------- FGPIOC_PSOR                              ------ */

/* ------- FGPIOC_PCOR                              ------ */

/* ------- FGPIOC_PTOR                              ------ */

/* ------- FGPIOC_PDIR                              ------ */

/* ------- FGPIOC_PDDR                              ------ */

/* ------- FGPIOC_PIDR                              ------ */

/* -------------------------------------------------------------------------------- */
/* -----------     'FGPIOC' Register Access macros                      ----------- */
/* -------------------------------------------------------------------------------- */

#define FGPIOC_PDOR                    (FGPIOC->PDOR)
#define FGPIOC_PSOR                    (FGPIOC->PSOR)
#define FGPIOC_PCOR                    (FGPIOC->PCOR)
#define FGPIOC_PTOR                    (FGPIOC->PTOR)
#define FGPIOC_PDIR                    (FGPIOC->PDIR)
#define FGPIOC_PDDR                    (FGPIOC->PDDR)
#define FGPIOC_PIDR                    (FGPIOC->PIDR)

/* ================================================================================ */
/* ================           FTM0 (file:FTM0_2CH_MKE)             ================ */
/* ================================================================================ */

/**
 * @brief FlexTimer Module (2 channels)
 */
typedef struct {                                /*!<       FTM0 Structure                                               */
   __IO uint32_t  SC;                           /*!< 0000: Status and Control                                           */
   __IO uint32_t  CNT;                          /*!< 0004: Counter                                                      */
   __IO uint32_t  MOD;                          /*!< 0008: Modulo                                                       */
   struct { /* (cluster) */                     /*!< 000C: (size=0x0010, 16)                                            */
      __IO uint32_t  CnSC;                      /*!< 000C: Channel (%s) Status and Control                              */
      __IO uint32_t  CnV;                       /*!< 0010: Channel (%s) Value                                           */
   } CONTROLS[2];
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

/* ================================================================================ */
/* ================           FTM1 (derived from FTM0)             ================ */
/* ================================================================================ */

/**
 * @brief FlexTimer Module (2 channels)
 */
typedef FTM0_Type FTM1_Type;  /*!< FTM1 Structure                                              */


/* -------------------------------------------------------------------------------- */
/* -----------     'FTM1' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define FTM1_SC                        (FTM1->SC)
#define FTM1_CNT                       (FTM1->CNT)
#define FTM1_MOD                       (FTM1->MOD)
#define FTM1_C0SC                      (FTM1->CONTROLS[0].CnSC)
#define FTM1_C0V                       (FTM1->CONTROLS[0].CnV)
#define FTM1_C1SC                      (FTM1->CONTROLS[1].CnSC)
#define FTM1_C1V                       (FTM1->CONTROLS[1].CnV)

/* ================================================================================ */
/* ================           FTM2 (file:FTM2_6CH_MKE)             ================ */
/* ================================================================================ */

/**
 * @brief FlexTimer Module (6 channels)
 */
typedef struct {                                /*!<       FTM2 Structure                                               */
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
   __I  uint32_t  RESERVED1;                    /*!< 0080:                                                              */
   __IO uint32_t  CONF;                         /*!< 0084: Configuration                                                */
   __IO uint32_t  FLTPOL;                       /*!< 0088: FTM Fault Input Polarity                                     */
   __IO uint32_t  SYNCONF;                      /*!< 008C: Synchronization Configuration                                */
   __IO uint32_t  INVCTRL;                      /*!< 0090: FTM Inverting Control                                        */
   __IO uint32_t  SWOCTRL;                      /*!< 0094: FTM Software Output Control                                  */
   __IO uint32_t  PWMLOAD;                      /*!< 0098: FTM PWM Load                                                 */
} FTM2_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'FTM2' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- FTM2_SC                                  ------ */

/* ------- FTM2_CNT                                 ------ */

/* ------- FTM2_MOD                                 ------ */

/* ------- FTM2_CnSC                                ------ */

/* ------- FTM2_CnV                                 ------ */

/* ------- FTM2_CNTIN                               ------ */

/* ------- FTM2_STATUS                              ------ */

/* ------- FTM2_MODE                                ------ */

/* ------- FTM2_SYNC                                ------ */

/* ------- FTM2_OUTINIT                             ------ */

/* ------- FTM2_OUTMASK                             ------ */

/* ------- FTM2_COMBINE                             ------ */

/* ------- FTM2_DEADTIME                            ------ */

/* ------- FTM2_EXTTRIG                             ------ */

/* ------- FTM2_POL                                 ------ */

/* ------- FTM2_FMS                                 ------ */

/* ------- FTM2_FILTER                              ------ */

/* ------- FTM2_FLTCTRL                             ------ */

/* ------- FTM2_CONF                                ------ */

/* ------- FTM2_FLTPOL                              ------ */

/* ------- FTM2_SYNCONF                             ------ */

/* ------- FTM2_INVCTRL                             ------ */

/* ------- FTM2_SWOCTRL                             ------ */

/* ------- FTM2_PWMLOAD                             ------ */

/* -------------------------------------------------------------------------------- */
/* -----------     'FTM2' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define FTM2_SC                        (FTM2->SC)
#define FTM2_CNT                       (FTM2->CNT)
#define FTM2_MOD                       (FTM2->MOD)
#define FTM2_C0SC                      (FTM2->CONTROLS[0].CnSC)
#define FTM2_C0V                       (FTM2->CONTROLS[0].CnV)
#define FTM2_C1SC                      (FTM2->CONTROLS[1].CnSC)
#define FTM2_C1V                       (FTM2->CONTROLS[1].CnV)
#define FTM2_C2SC                      (FTM2->CONTROLS[2].CnSC)
#define FTM2_C2V                       (FTM2->CONTROLS[2].CnV)
#define FTM2_C3SC                      (FTM2->CONTROLS[3].CnSC)
#define FTM2_C3V                       (FTM2->CONTROLS[3].CnV)
#define FTM2_C4SC                      (FTM2->CONTROLS[4].CnSC)
#define FTM2_C4V                       (FTM2->CONTROLS[4].CnV)
#define FTM2_C5SC                      (FTM2->CONTROLS[5].CnSC)
#define FTM2_C5V                       (FTM2->CONTROLS[5].CnV)
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
#define FTM2_CONF                      (FTM2->CONF)
#define FTM2_FLTPOL                    (FTM2->FLTPOL)
#define FTM2_SYNCONF                   (FTM2->SYNCONF)
#define FTM2_INVCTRL                   (FTM2->INVCTRL)
#define FTM2_SWOCTRL                   (FTM2->SWOCTRL)
#define FTM2_PWMLOAD                   (FTM2->PWMLOAD)

/* ================================================================================ */
/* ================           FTMRE (file:FTMRE_MKE)               ================ */
/* ================================================================================ */

/**
 * @brief Flash Memory Interface
 */
typedef struct {                                /*!<       FTMRE Structure                                              */
   __I  uint8_t   RESERVED0;                    /*!< 0000:                                                              */
   __IO uint8_t   FCCOBIX;                      /*!< 0001: Flash CCOB Index Register                                    */
   __IO uint8_t   FSEC;                         /*!< 0002: Flash Security Register                                      */
   __IO uint8_t   FCLKDIV;                      /*!< 0003: Flash Clock Divider Register                                 */
   __I  uint8_t   RESERVED1;                    /*!< 0004:                                                              */
   __IO uint8_t   FSTAT;                        /*!< 0005: Flash Status Register                                        */
   __I  uint8_t   RESERVED2;                    /*!< 0006:                                                              */
   __IO uint8_t   FCNFG;                        /*!< 0007: Flash Configuration Register                                 */
   union {                                      /*!< 0000: (size=0002)                                                  */
      __IO uint16_t  FCCOB;                     /*!< 0008: Flash Common Command Object Register (FCCOBLO:FCCOBHI)       */
      struct {                                  /*!< 0000: (size=0002)                                                  */
         __IO uint8_t   FCCOBLO;                /*!< 0008: Flash Common Command Object Register:Low                     */
         __IO uint8_t   FCCOBHI;                /*!< 0009: Flash Common Command Object Register:High                    */
      };
   };
   __I  uint8_t   RESERVED3;                    /*!< 000A:                                                              */
   __IO uint8_t   FPROT;                        /*!< 000B: Flash Protection Register                                    */
   __I  uint8_t   RESERVED4[3];                 /*!< 000C:                                                              */
   __IO uint8_t   FOPT;                         /*!< 000F: Flash Option Register                                        */
} FTMRE_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'FTMRE' Position & Mask macros                       ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- FTMRE_FCCOBIX                            ------ */
#define FTMRE_FCCOBIX_CCOBIX_MASK                (0x07UL << FTMRE_FCCOBIX_CCOBIX_SHIFT)              /*!< FTMRE_FCCOBIX: CCOBIX Mask              */
#define FTMRE_FCCOBIX_CCOBIX_SHIFT               0                                                   /*!< FTMRE_FCCOBIX: CCOBIX Position          */
#define FTMRE_FCCOBIX_CCOBIX(x)                  (((x)<<FTMRE_FCCOBIX_CCOBIX_SHIFT)&FTMRE_FCCOBIX_CCOBIX_MASK) /*!< FTMRE_FCCOBIX                           */

/* ------- FTMRE_FSEC                               ------ */
#define FTMRE_FSEC_SEC_MASK                      (0x03UL << FTMRE_FSEC_SEC_SHIFT)                    /*!< FTMRE_FSEC: SEC Mask                    */
#define FTMRE_FSEC_SEC_SHIFT                     0                                                   /*!< FTMRE_FSEC: SEC Position                */
#define FTMRE_FSEC_SEC(x)                        (((x)<<FTMRE_FSEC_SEC_SHIFT)&FTMRE_FSEC_SEC_MASK)   /*!< FTMRE_FSEC                              */
#define FTMRE_FSEC_KEYEN_MASK                    (0x03UL << FTMRE_FSEC_KEYEN_SHIFT)                  /*!< FTMRE_FSEC: KEYEN Mask                  */
#define FTMRE_FSEC_KEYEN_SHIFT                   6                                                   /*!< FTMRE_FSEC: KEYEN Position              */
#define FTMRE_FSEC_KEYEN(x)                      (((x)<<FTMRE_FSEC_KEYEN_SHIFT)&FTMRE_FSEC_KEYEN_MASK) /*!< FTMRE_FSEC                              */

/* ------- FTMRE_FCLKDIV                            ------ */
#define FTMRE_FCLKDIV_FDIV_MASK                  (0x3FUL << FTMRE_FCLKDIV_FDIV_SHIFT)                /*!< FTMRE_FCLKDIV: FDIV Mask                */
#define FTMRE_FCLKDIV_FDIV_SHIFT                 0                                                   /*!< FTMRE_FCLKDIV: FDIV Position            */
#define FTMRE_FCLKDIV_FDIV(x)                    (((x)<<FTMRE_FCLKDIV_FDIV_SHIFT)&FTMRE_FCLKDIV_FDIV_MASK) /*!< FTMRE_FCLKDIV                           */
#define FTMRE_FCLKDIV_FDIVLCK_MASK               (0x01UL << FTMRE_FCLKDIV_FDIVLCK_SHIFT)             /*!< FTMRE_FCLKDIV: FDIVLCK Mask             */
#define FTMRE_FCLKDIV_FDIVLCK_SHIFT              6                                                   /*!< FTMRE_FCLKDIV: FDIVLCK Position         */
#define FTMRE_FCLKDIV_FDIVLD_MASK                (0x01UL << FTMRE_FCLKDIV_FDIVLD_SHIFT)              /*!< FTMRE_FCLKDIV: FDIVLD Mask              */
#define FTMRE_FCLKDIV_FDIVLD_SHIFT               7                                                   /*!< FTMRE_FCLKDIV: FDIVLD Position          */

/* ------- FTMRE_FSTAT                              ------ */
#define FTMRE_FSTAT_MGSTAT_MASK                  (0x03UL << FTMRE_FSTAT_MGSTAT_SHIFT)                /*!< FTMRE_FSTAT: MGSTAT Mask                */
#define FTMRE_FSTAT_MGSTAT_SHIFT                 0                                                   /*!< FTMRE_FSTAT: MGSTAT Position            */
#define FTMRE_FSTAT_MGSTAT(x)                    (((x)<<FTMRE_FSTAT_MGSTAT_SHIFT)&FTMRE_FSTAT_MGSTAT_MASK) /*!< FTMRE_FSTAT                             */
#define FTMRE_FSTAT_MGBUSY_MASK                  (0x01UL << FTMRE_FSTAT_MGBUSY_SHIFT)                /*!< FTMRE_FSTAT: MGBUSY Mask                */
#define FTMRE_FSTAT_MGBUSY_SHIFT                 3                                                   /*!< FTMRE_FSTAT: MGBUSY Position            */
#define FTMRE_FSTAT_FPVIOL_MASK                  (0x01UL << FTMRE_FSTAT_FPVIOL_SHIFT)                /*!< FTMRE_FSTAT: FPVIOL Mask                */
#define FTMRE_FSTAT_FPVIOL_SHIFT                 4                                                   /*!< FTMRE_FSTAT: FPVIOL Position            */
#define FTMRE_FSTAT_ACCERR_MASK                  (0x01UL << FTMRE_FSTAT_ACCERR_SHIFT)                /*!< FTMRE_FSTAT: ACCERR Mask                */
#define FTMRE_FSTAT_ACCERR_SHIFT                 5                                                   /*!< FTMRE_FSTAT: ACCERR Position            */
#define FTMRE_FSTAT_CCIF_MASK                    (0x01UL << FTMRE_FSTAT_CCIF_SHIFT)                  /*!< FTMRE_FSTAT: CCIF Mask                  */
#define FTMRE_FSTAT_CCIF_SHIFT                   7                                                   /*!< FTMRE_FSTAT: CCIF Position              */

/* ------- FTMRE_FCNFG                              ------ */
#define FTMRE_FCNFG_FSFD_MASK                    (0x01UL << FTMRE_FCNFG_FSFD_SHIFT)                  /*!< FTMRE_FCNFG: FSFD Mask                  */
#define FTMRE_FCNFG_FSFD_SHIFT                   0                                                   /*!< FTMRE_FCNFG: FSFD Position              */
#define FTMRE_FCNFG_FDFD_MASK                    (0x01UL << FTMRE_FCNFG_FDFD_SHIFT)                  /*!< FTMRE_FCNFG: FDFD Mask                  */
#define FTMRE_FCNFG_FDFD_SHIFT                   1                                                   /*!< FTMRE_FCNFG: FDFD Position              */
#define FTMRE_FCNFG_IGNSF_MASK                   (0x01UL << FTMRE_FCNFG_IGNSF_SHIFT)                 /*!< FTMRE_FCNFG: IGNSF Mask                 */
#define FTMRE_FCNFG_IGNSF_SHIFT                  4                                                   /*!< FTMRE_FCNFG: IGNSF Position             */
#define FTMRE_FCNFG_CCIE_MASK                    (0x01UL << FTMRE_FCNFG_CCIE_SHIFT)                  /*!< FTMRE_FCNFG: CCIE Mask                  */
#define FTMRE_FCNFG_CCIE_SHIFT                   7                                                   /*!< FTMRE_FCNFG: CCIE Position              */

/* ------- FTMRE_FCCOB                              ------ */

/* ------- FTMRE_FCCOBLO                            ------ */

/* ------- FTMRE_FCCOBHI                            ------ */

/* ------- FTMRE_FPROT                              ------ */
#define FTMRE_FPROT_FPLS_MASK                    (0x03UL << FTMRE_FPROT_FPLS_SHIFT)                  /*!< FTMRE_FPROT: FPLS Mask                  */
#define FTMRE_FPROT_FPLS_SHIFT                   0                                                   /*!< FTMRE_FPROT: FPLS Position              */
#define FTMRE_FPROT_FPLS(x)                      (((x)<<FTMRE_FPROT_FPLS_SHIFT)&FTMRE_FPROT_FPLS_MASK) /*!< FTMRE_FPROT                             */
#define FTMRE_FPROT_FPLDIS_MASK                  (0x01UL << FTMRE_FPROT_FPLDIS_SHIFT)                /*!< FTMRE_FPROT: FPLDIS Mask                */
#define FTMRE_FPROT_FPLDIS_SHIFT                 2                                                   /*!< FTMRE_FPROT: FPLDIS Position            */
#define FTMRE_FPROT_FPHS_MASK                    (0x03UL << FTMRE_FPROT_FPHS_SHIFT)                  /*!< FTMRE_FPROT: FPHS Mask                  */
#define FTMRE_FPROT_FPHS_SHIFT                   3                                                   /*!< FTMRE_FPROT: FPHS Position              */
#define FTMRE_FPROT_FPHS(x)                      (((x)<<FTMRE_FPROT_FPHS_SHIFT)&FTMRE_FPROT_FPHS_MASK) /*!< FTMRE_FPROT                             */
#define FTMRE_FPROT_FPHDIS_MASK                  (0x01UL << FTMRE_FPROT_FPHDIS_SHIFT)                /*!< FTMRE_FPROT: FPHDIS Mask                */
#define FTMRE_FPROT_FPHDIS_SHIFT                 5                                                   /*!< FTMRE_FPROT: FPHDIS Position            */
#define FTMRE_FPROT_FPOPEN_MASK                  (0x01UL << FTMRE_FPROT_FPOPEN_SHIFT)                /*!< FTMRE_FPROT: FPOPEN Mask                */
#define FTMRE_FPROT_FPOPEN_SHIFT                 7                                                   /*!< FTMRE_FPROT: FPOPEN Position            */

/* ------- FTMRE_FOPT                               ------ */

/* -------------------------------------------------------------------------------- */
/* -----------     'FTMRE' Register Access macros                       ----------- */
/* -------------------------------------------------------------------------------- */

#define FTMRE_FCCOBIX                  (FTMRE->FCCOBIX)
#define FTMRE_FSEC                     (FTMRE->FSEC)
#define FTMRE_FCLKDIV                  (FTMRE->FCLKDIV)
#define FTMRE_FSTAT                    (FTMRE->FSTAT)
#define FTMRE_FCNFG                    (FTMRE->FCNFG)
#define FTMRE_FCCOB                    (FTMRE->FCCOB)
#define FTMRE_FCCOBLO                  (FTMRE->FCCOBLO)
#define FTMRE_FCCOBHI                  (FTMRE->FCCOBHI)
#define FTMRE_FPROT                    (FTMRE->FPROT)
#define FTMRE_FOPT                     (FTMRE->FOPT)

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
#define GPIOA_PIDR                     (GPIOA->PIDR)

/* ================================================================================ */
/* ================           GPIOB (derived from FGPIOB)          ================ */
/* ================================================================================ */

/**
 * @brief General Purpose Input/Output
 */
typedef FGPIOB_Type GPIOB_Type;  /*!< GPIOB Structure                                             */


/* -------------------------------------------------------------------------------- */
/* -----------     'GPIOB' Register Access macros                       ----------- */
/* -------------------------------------------------------------------------------- */

#define GPIOB_PDOR                     (GPIOB->PDOR)
#define GPIOB_PSOR                     (GPIOB->PSOR)
#define GPIOB_PCOR                     (GPIOB->PCOR)
#define GPIOB_PTOR                     (GPIOB->PTOR)
#define GPIOB_PDIR                     (GPIOB->PDIR)
#define GPIOB_PDDR                     (GPIOB->PDDR)
#define GPIOB_PIDR                     (GPIOB->PIDR)

/* ================================================================================ */
/* ================           GPIOC (derived from FGPIOC)          ================ */
/* ================================================================================ */

/**
 * @brief General Purpose Input/Output
 */
typedef FGPIOC_Type GPIOC_Type;  /*!< GPIOC Structure                                             */


/* -------------------------------------------------------------------------------- */
/* -----------     'GPIOC' Register Access macros                       ----------- */
/* -------------------------------------------------------------------------------- */

#define GPIOC_PDOR                     (GPIOC->PDOR)
#define GPIOC_PSOR                     (GPIOC->PSOR)
#define GPIOC_PCOR                     (GPIOC->PCOR)
#define GPIOC_PTOR                     (GPIOC->PTOR)
#define GPIOC_PDIR                     (GPIOC->PDIR)
#define GPIOC_PDDR                     (GPIOC->PDDR)
#define GPIOC_PIDR                     (GPIOC->PIDR)

/* ================================================================================ */
/* ================           I2C0 (file:I2C0_MKE)                 ================ */
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
#define I2C_C2_ADEXT_MASK                        (0x01UL << I2C_C2_ADEXT_SHIFT)                      /*!< I2C0_C2: ADEXT Mask                     */
#define I2C_C2_ADEXT_SHIFT                       6                                                   /*!< I2C0_C2: ADEXT Position                 */
#define I2C_C2_GCAEN_MASK                        (0x01UL << I2C_C2_GCAEN_SHIFT)                      /*!< I2C0_C2: GCAEN Mask                     */
#define I2C_C2_GCAEN_SHIFT                       7                                                   /*!< I2C0_C2: GCAEN Position                 */

/* ------- I2C0_FLT                                 ------ */
#define I2C_FLT_FLT_MASK                         (0x0FUL << I2C_FLT_FLT_SHIFT)                       /*!< I2C0_FLT: FLT Mask                      */
#define I2C_FLT_FLT_SHIFT                        0                                                   /*!< I2C0_FLT: FLT Position                  */
#define I2C_FLT_FLT(x)                           (((x)<<I2C_FLT_FLT_SHIFT)&I2C_FLT_FLT_MASK)         /*!< I2C0_FLT                                */
#define I2C_FLT_STARTF_MASK                      (0x01UL << I2C_FLT_STARTF_SHIFT)                    /*!< I2C0_FLT: STARTF Mask                   */
#define I2C_FLT_STARTF_SHIFT                     4                                                   /*!< I2C0_FLT: STARTF Position               */
#define I2C_FLT_SSIE_MASK                        (0x01UL << I2C_FLT_SSIE_SHIFT)                      /*!< I2C0_FLT: SSIE Mask                     */
#define I2C_FLT_SSIE_SHIFT                       5                                                   /*!< I2C0_FLT: SSIE Position                 */
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
/* ================           ICS (file:ICS_MKE)                   ================ */
/* ================================================================================ */

/**
 * @brief Clock management
 */
typedef struct {                                /*!<       ICS Structure                                                */
   __IO uint8_t   C1;                           /*!< 0000: ICS Control Register 1                                       */
   __IO uint8_t   C2;                           /*!< 0001: ICS Control Register 2                                       */
   __IO uint8_t   C3;                           /*!< 0002: ICS Control Register 3                                       */
   __IO uint8_t   C4;                           /*!< 0003: ICS Control Register 4                                       */
   __I  uint8_t   S;                            /*!< 0004: ICS Status Register                                          */
} ICS_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'ICS' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- ICS_C1                                   ------ */
#define ICS_C1_IREFSTEN_MASK                     (0x01UL << ICS_C1_IREFSTEN_SHIFT)                   /*!< ICS_C1: IREFSTEN Mask                   */
#define ICS_C1_IREFSTEN_SHIFT                    0                                                   /*!< ICS_C1: IREFSTEN Position               */
#define ICS_C1_IRCLKEN_MASK                      (0x01UL << ICS_C1_IRCLKEN_SHIFT)                    /*!< ICS_C1: IRCLKEN Mask                    */
#define ICS_C1_IRCLKEN_SHIFT                     1                                                   /*!< ICS_C1: IRCLKEN Position                */
#define ICS_C1_IREFS_MASK                        (0x01UL << ICS_C1_IREFS_SHIFT)                      /*!< ICS_C1: IREFS Mask                      */
#define ICS_C1_IREFS_SHIFT                       2                                                   /*!< ICS_C1: IREFS Position                  */
#define ICS_C1_RDIV_MASK                         (0x07UL << ICS_C1_RDIV_SHIFT)                       /*!< ICS_C1: RDIV Mask                       */
#define ICS_C1_RDIV_SHIFT                        3                                                   /*!< ICS_C1: RDIV Position                   */
#define ICS_C1_RDIV(x)                           (((x)<<ICS_C1_RDIV_SHIFT)&ICS_C1_RDIV_MASK)         /*!< ICS_C1                                  */
#define ICS_C1_CLKS_MASK                         (0x03UL << ICS_C1_CLKS_SHIFT)                       /*!< ICS_C1: CLKS Mask                       */
#define ICS_C1_CLKS_SHIFT                        6                                                   /*!< ICS_C1: CLKS Position                   */
#define ICS_C1_CLKS(x)                           (((x)<<ICS_C1_CLKS_SHIFT)&ICS_C1_CLKS_MASK)         /*!< ICS_C1                                  */

/* ------- ICS_C2                                   ------ */
#define ICS_C2_LP_MASK                           (0x01UL << ICS_C2_LP_SHIFT)                         /*!< ICS_C2: LP Mask                         */
#define ICS_C2_LP_SHIFT                          4                                                   /*!< ICS_C2: LP Position                     */
#define ICS_C2_BDIV_MASK                         (0x07UL << ICS_C2_BDIV_SHIFT)                       /*!< ICS_C2: BDIV Mask                       */
#define ICS_C2_BDIV_SHIFT                        5                                                   /*!< ICS_C2: BDIV Position                   */
#define ICS_C2_BDIV(x)                           (((x)<<ICS_C2_BDIV_SHIFT)&ICS_C2_BDIV_MASK)         /*!< ICS_C2                                  */

/* ------- ICS_C3                                   ------ */
#define ICS_C3_SCTRIM_MASK                       (0xFFUL << ICS_C3_SCTRIM_SHIFT)                     /*!< ICS_C3: SCTRIM Mask                     */
#define ICS_C3_SCTRIM_SHIFT                      0                                                   /*!< ICS_C3: SCTRIM Position                 */
#define ICS_C3_SCTRIM(x)                         (((x)<<ICS_C3_SCTRIM_SHIFT)&ICS_C3_SCTRIM_MASK)     /*!< ICS_C3                                  */

/* ------- ICS_C4                                   ------ */
#define ICS_C4_SCFTRIM_MASK                      (0x01UL << ICS_C4_SCFTRIM_SHIFT)                    /*!< ICS_C4: SCFTRIM Mask                    */
#define ICS_C4_SCFTRIM_SHIFT                     0                                                   /*!< ICS_C4: SCFTRIM Position                */
#define ICS_C4_CME_MASK                          (0x01UL << ICS_C4_CME_SHIFT)                        /*!< ICS_C4: CME Mask                        */
#define ICS_C4_CME_SHIFT                         5                                                   /*!< ICS_C4: CME Position                    */
#define ICS_C4_LOLIE0_MASK                       (0x01UL << ICS_C4_LOLIE0_SHIFT)                     /*!< ICS_C4: LOLIE0 Mask                     */
#define ICS_C4_LOLIE0_SHIFT                      7                                                   /*!< ICS_C4: LOLIE0 Position                 */

/* ------- ICS_S                                    ------ */
#define ICS_S_CLKST_MASK                         (0x03UL << ICS_S_CLKST_SHIFT)                       /*!< ICS_S: CLKST Mask                       */
#define ICS_S_CLKST_SHIFT                        2                                                   /*!< ICS_S: CLKST Position                   */
#define ICS_S_CLKST(x)                           (((x)<<ICS_S_CLKST_SHIFT)&ICS_S_CLKST_MASK)         /*!< ICS_S                                   */
#define ICS_S_IREFST_MASK                        (0x01UL << ICS_S_IREFST_SHIFT)                      /*!< ICS_S: IREFST Mask                      */
#define ICS_S_IREFST_SHIFT                       4                                                   /*!< ICS_S: IREFST Position                  */
#define ICS_S_LOCK_MASK                          (0x01UL << ICS_S_LOCK_SHIFT)                        /*!< ICS_S: LOCK Mask                        */
#define ICS_S_LOCK_SHIFT                         6                                                   /*!< ICS_S: LOCK Position                    */
#define ICS_S_LOLS_MASK                          (0x01UL << ICS_S_LOLS_SHIFT)                        /*!< ICS_S: LOLS Mask                        */
#define ICS_S_LOLS_SHIFT                         7                                                   /*!< ICS_S: LOLS Position                    */

/* -------------------------------------------------------------------------------- */
/* -----------     'ICS' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define ICS_C1                         (ICS->C1)
#define ICS_C2                         (ICS->C2)
#define ICS_C3                         (ICS->C3)
#define ICS_C4                         (ICS->C4)
#define ICS_S                          (ICS->S)

/* ================================================================================ */
/* ================           IRQ (file:IRQ_MKE)                   ================ */
/* ================================================================================ */

/**
 * @brief Interrupt
 */
typedef struct {                                /*!<       IRQ Structure                                                */
   __IO uint8_t   SC;                           /*!< 0000: Interrupt Pin Request Status and Control Register            */
} IRQ_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'IRQ' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- IRQ_SC                                   ------ */
#define IRQ_SC_IRQMOD_MASK                       (0x01UL << IRQ_SC_IRQMOD_SHIFT)                     /*!< IRQ_SC: IRQMOD Mask                     */
#define IRQ_SC_IRQMOD_SHIFT                      0                                                   /*!< IRQ_SC: IRQMOD Position                 */
#define IRQ_SC_IRQIE_MASK                        (0x01UL << IRQ_SC_IRQIE_SHIFT)                      /*!< IRQ_SC: IRQIE Mask                      */
#define IRQ_SC_IRQIE_SHIFT                       1                                                   /*!< IRQ_SC: IRQIE Position                  */
#define IRQ_SC_IRQACK_MASK                       (0x01UL << IRQ_SC_IRQACK_SHIFT)                     /*!< IRQ_SC: IRQACK Mask                     */
#define IRQ_SC_IRQACK_SHIFT                      2                                                   /*!< IRQ_SC: IRQACK Position                 */
#define IRQ_SC_IRQF_MASK                         (0x01UL << IRQ_SC_IRQF_SHIFT)                       /*!< IRQ_SC: IRQF Mask                       */
#define IRQ_SC_IRQF_SHIFT                        3                                                   /*!< IRQ_SC: IRQF Position                   */
#define IRQ_SC_IRQPE_MASK                        (0x01UL << IRQ_SC_IRQPE_SHIFT)                      /*!< IRQ_SC: IRQPE Mask                      */
#define IRQ_SC_IRQPE_SHIFT                       4                                                   /*!< IRQ_SC: IRQPE Position                  */
#define IRQ_SC_IRQEDG_MASK                       (0x01UL << IRQ_SC_IRQEDG_SHIFT)                     /*!< IRQ_SC: IRQEDG Mask                     */
#define IRQ_SC_IRQEDG_SHIFT                      5                                                   /*!< IRQ_SC: IRQEDG Position                 */
#define IRQ_SC_IRQPDD_MASK                       (0x01UL << IRQ_SC_IRQPDD_SHIFT)                     /*!< IRQ_SC: IRQPDD Mask                     */
#define IRQ_SC_IRQPDD_SHIFT                      6                                                   /*!< IRQ_SC: IRQPDD Position                 */

/* -------------------------------------------------------------------------------- */
/* -----------     'IRQ' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define IRQ_SC                         (IRQ->SC)

/* ================================================================================ */
/* ================           KBI0 (file:KBI0_MKE_2)               ================ */
/* ================================================================================ */

/**
 * @brief Keyboard interrupts
 */
typedef struct {                                /*!<       KBI0 Structure                                               */
   __IO uint32_t  PE;                           /*!< 0000: KBI Pin Enables                                              */
   __IO uint32_t  ES;                           /*!< 0004: KBI Edge Selects                                             */
   __IO uint32_t  SC;                           /*!< 0008: KBI Status and Control Register                              */
   __IO uint32_t  SP;                           /*!< 000C: KBI Source Pin                                               */
} KBI0_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'KBI0' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- KBI0_PE                                  ------ */
#define KBI0_PE_KBIPE_MASK                       (0xFFFFFFFFUL << KBI0_PE_KBIPE_SHIFT)               /*!< KBI0_PE: KBIPE Mask                     */
#define KBI0_PE_KBIPE_SHIFT                      0                                                   /*!< KBI0_PE: KBIPE Position                 */
#define KBI0_PE_KBIPE(x)                         (((x)<<KBI0_PE_KBIPE_SHIFT)&KBI0_PE_KBIPE_MASK)     /*!< KBI0_PE                                 */

/* ------- KBI0_ES                                  ------ */
#define KBI0_ES_KBEDG_MASK                       (0xFFFFFFFFUL << KBI0_ES_KBEDG_SHIFT)               /*!< KBI0_ES: KBEDG Mask                     */
#define KBI0_ES_KBEDG_SHIFT                      0                                                   /*!< KBI0_ES: KBEDG Position                 */
#define KBI0_ES_KBEDG(x)                         (((x)<<KBI0_ES_KBEDG_SHIFT)&KBI0_ES_KBEDG_MASK)     /*!< KBI0_ES                                 */

/* ------- KBI0_SC                                  ------ */
#define KBI0_SC_KBMOD_MASK                       (0x01UL << KBI0_SC_KBMOD_SHIFT)                     /*!< KBI0_SC: KBMOD Mask                     */
#define KBI0_SC_KBMOD_SHIFT                      0                                                   /*!< KBI0_SC: KBMOD Position                 */
#define KBI0_SC_KBIE_MASK                        (0x01UL << KBI0_SC_KBIE_SHIFT)                      /*!< KBI0_SC: KBIE Mask                      */
#define KBI0_SC_KBIE_SHIFT                       1                                                   /*!< KBI0_SC: KBIE Position                  */
#define KBI0_SC_KBACK_MASK                       (0x01UL << KBI0_SC_KBACK_SHIFT)                     /*!< KBI0_SC: KBACK Mask                     */
#define KBI0_SC_KBACK_SHIFT                      2                                                   /*!< KBI0_SC: KBACK Position                 */
#define KBI0_SC_KBF_MASK                         (0x01UL << KBI0_SC_KBF_SHIFT)                       /*!< KBI0_SC: KBF Mask                       */
#define KBI0_SC_KBF_SHIFT                        3                                                   /*!< KBI0_SC: KBF Position                   */
#define KBI0_SC_KBSPEN_MASK                      (0x01UL << KBI0_SC_KBSPEN_SHIFT)                    /*!< KBI0_SC: KBSPEN Mask                    */
#define KBI0_SC_KBSPEN_SHIFT                     4                                                   /*!< KBI0_SC: KBSPEN Position                */
#define KBI0_SC_RSTKBSP_MASK                     (0x01UL << KBI0_SC_RSTKBSP_SHIFT)                   /*!< KBI0_SC: RSTKBSP Mask                   */
#define KBI0_SC_RSTKBSP_SHIFT                    5                                                   /*!< KBI0_SC: RSTKBSP Position               */

/* ------- KBI0_SP                                  ------ */

/* -------------------------------------------------------------------------------- */
/* -----------     'KBI0' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define KBI0_PE                        (KBI0->PE)
#define KBI0_ES                        (KBI0->ES)
#define KBI0_SC                        (KBI0->SC)
#define KBI0_SP                        (KBI0->SP)

/* ================================================================================ */
/* ================           KBI1 (derived from KBI0)             ================ */
/* ================================================================================ */

/**
 * @brief Keyboard interrupts
 */
typedef KBI0_Type KBI1_Type;  /*!< KBI1 Structure                                              */


/* -------------------------------------------------------------------------------- */
/* -----------     'KBI1' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define KBI1_PE                        (KBI1->PE)
#define KBI1_ES                        (KBI1->ES)
#define KBI1_SC                        (KBI1->SC)
#define KBI1_SP                        (KBI1->SP)

/* ================================================================================ */
/* ================           MCM (file:MCM_MKE)                   ================ */
/* ================================================================================ */

/**
 * @brief Core Platform Miscellaneous Control Module
 */
typedef struct {                                /*!<       MCM Structure                                                */
   __I  uint32_t  RESERVED0[2];                 /*!< 0000:                                                              */
   __I  uint16_t  PLASC;                        /*!< 0008: Crossbar Switch (AXBS) Slave Configuration                   */
   __I  uint16_t  PLAMC;                        /*!< 000A: Crossbar Switch (AXBS) Master Configuration                  */
   __IO uint32_t  PLACR;                        /*!< 000C: Platform Control Register                                    */
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

/* -------------------------------------------------------------------------------- */
/* -----------     'MCM' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define MCM_PLASC                      (MCM->PLASC)
#define MCM_PLAMC                      (MCM->PLAMC)
#define MCM_PLACR                      (MCM->PLACR)

/* ================================================================================ */
/* ================           MSCAN (file:MSCAN)                   ================ */
/* ================================================================================ */

/**
 * @brief Scalable Controller Area Network
 */
typedef struct {                                /*!<       MSCAN Structure                                              */
   __IO uint8_t   CANCTL0;                      /*!< 0000: Control Register 0                                           */
   __IO uint8_t   CANCTL1;                      /*!< 0001: Control Register 1                                           */
   __IO uint8_t   CANBTR0;                      /*!< 0002: Bus Timing Register 0                                        */
   __IO uint8_t   CANBTR1;                      /*!< 0003: Bus Timing Register 1                                        */
   __IO uint8_t   CANRFLG;                      /*!< 0004: Receiver Flag Register                                       */
   __IO uint8_t   CANRIER;                      /*!< 0005: Receiver Interrupt Enable Register                           */
   __IO uint8_t   CANTFLG;                      /*!< 0006: Transmitter Flag Register                                    */
   __IO uint8_t   CANTIER;                      /*!< 0007: Transmitter Interrupt Enable Register                        */
   __IO uint8_t   CANTARQ;                      /*!< 0008: Transmitter Message Abort Request Register                   */
   __IO uint8_t   CANTAAK;                      /*!< 0009: Transmitter Message Abort Acknowledge Register               */
   __IO uint8_t   CANTBSEL;                     /*!< 000A: Transmit Buffer Selection Register                           */
   __IO uint8_t   CANIDAC;                      /*!< 000B: Identifier Acceptance Control Register                       */
   __I  uint8_t   RESERVED0;                    /*!< 000C:                                                              */
   __IO uint8_t   CANMISC;                      /*!< 000D: Miscellaneous Register                                       */
   __IO uint8_t   CANRXERR;                     /*!< 000E: Receive Error Counter                                        */
   __IO uint8_t   CANTXERR;                     /*!< 000F: Transmit Error Counter                                       */
   __IO uint8_t   CANIDAR[4];                   /*!< 0010: Identifier Acceptance Register n of First Bank               */
   __IO uint8_t   CANIDMR[4];                   /*!< 0014: Identifier Mask Register n of First Bank                     */
   __IO uint8_t   CANIDAR4;                     /*!< 0018: Identifier Acceptance Register n of Second Bank              */
   __IO uint8_t   CANIDAR5;                     /*!< 0019: Identifier Acceptance Register n of Second Bank              */
   __IO uint8_t   CANIDAR6;                     /*!< 001A: Identifier Acceptance Register n of Second Bank              */
   __IO uint8_t   CANIDAR7;                     /*!< 001B: Identifier Acceptance Register n of Second Bank              */
   __IO uint8_t   CANIDMR4;                     /*!< 001C: Identifier Mask Register n of Second Bank                    */
   __IO uint8_t   CANIDMR5;                     /*!< 001D: Identifier Mask Register n of Second Bank                    */
   __IO uint8_t   CANIDMR6;                     /*!< 001E: Identifier Mask Register n of Second Bank                    */
   __IO uint8_t   CANIDMR7;                     /*!< 001F: Identifier Mask Register n of Second Bank                    */
   union {                                      /*!< 0000: (size=0004)                                                  */
      __IO uint8_t   REIDR[4];                  /*!< 0020: Receive Extended Identifier Register %n                      */
      __IO uint8_t   RSIDR[2];                  /*!< 0020: Receive Standard Identifier Register %n                      */
   };
   __IO uint8_t   REDSR[8];                     /*!< 0024: Receive Extended Data Segment Register %n                    */
   __IO uint8_t   RDLR;                         /*!< 002C: Receive Data Length Register                                 */
   __I  uint8_t   RESERVED1;                    /*!< 002D:                                                              */
   __IO uint8_t   RTSRH;                        /*!< 002E: Receive Time Stamp Register High                             */
   __IO uint8_t   RTSRL;                        /*!< 002F: Receive Time Stamp Register Low                              */
   union {                                      /*!< 0000: (size=0004)                                                  */
      __IO uint8_t   TEIDR[4];                  /*!< 0030: Transmit Extended Identifier Register %n                     */
      __IO uint8_t   TSIDR[2];                  /*!< 0030: Transmit Standard Identifier Register %n                     */
   };
   __IO uint8_t   TEDSR[8];                     /*!< 0034: Transmit Extended Data Segment Register %n                   */
   __IO uint8_t   TDLR;                         /*!< 003C: Transmit Data Length Register                                */
   __IO uint8_t   TBPR;                         /*!< 003D: Transmit Buffer Priority Register                            */
   __IO uint8_t   TTSRH;                        /*!< 003E: Transmit Time Stamp Register High                            */
   __IO uint8_t   TTSRL;                        /*!< 003F: Transmit Time Stamp Register Low                             */
} MSCAN_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'MSCAN' Position & Mask macros                       ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- MSCAN_CANCTL0                            ------ */
#define MSCAN_CANCTL0_INITRQ_MASK                (0x01UL << MSCAN_CANCTL0_INITRQ_SHIFT)              /*!< MSCAN_CANCTL0: INITRQ Mask              */
#define MSCAN_CANCTL0_INITRQ_SHIFT               0                                                   /*!< MSCAN_CANCTL0: INITRQ Position          */
#define MSCAN_CANCTL0_SLPRQ_MASK                 (0x01UL << MSCAN_CANCTL0_SLPRQ_SHIFT)               /*!< MSCAN_CANCTL0: SLPRQ Mask               */
#define MSCAN_CANCTL0_SLPRQ_SHIFT                1                                                   /*!< MSCAN_CANCTL0: SLPRQ Position           */
#define MSCAN_CANCTL0_WUPE_MASK                  (0x01UL << MSCAN_CANCTL0_WUPE_SHIFT)                /*!< MSCAN_CANCTL0: WUPE Mask                */
#define MSCAN_CANCTL0_WUPE_SHIFT                 2                                                   /*!< MSCAN_CANCTL0: WUPE Position            */
#define MSCAN_CANCTL0_TIME_MASK                  (0x01UL << MSCAN_CANCTL0_TIME_SHIFT)                /*!< MSCAN_CANCTL0: TIME Mask                */
#define MSCAN_CANCTL0_TIME_SHIFT                 3                                                   /*!< MSCAN_CANCTL0: TIME Position            */
#define MSCAN_CANCTL0_SYNCH_MASK                 (0x01UL << MSCAN_CANCTL0_SYNCH_SHIFT)               /*!< MSCAN_CANCTL0: SYNCH Mask               */
#define MSCAN_CANCTL0_SYNCH_SHIFT                4                                                   /*!< MSCAN_CANCTL0: SYNCH Position           */
#define MSCAN_CANCTL0_CSWAI_MASK                 (0x01UL << MSCAN_CANCTL0_CSWAI_SHIFT)               /*!< MSCAN_CANCTL0: CSWAI Mask               */
#define MSCAN_CANCTL0_CSWAI_SHIFT                5                                                   /*!< MSCAN_CANCTL0: CSWAI Position           */
#define MSCAN_CANCTL0_RXACT_MASK                 (0x01UL << MSCAN_CANCTL0_RXACT_SHIFT)               /*!< MSCAN_CANCTL0: RXACT Mask               */
#define MSCAN_CANCTL0_RXACT_SHIFT                6                                                   /*!< MSCAN_CANCTL0: RXACT Position           */
#define MSCAN_CANCTL0_RXFRM_MASK                 (0x01UL << MSCAN_CANCTL0_RXFRM_SHIFT)               /*!< MSCAN_CANCTL0: RXFRM Mask               */
#define MSCAN_CANCTL0_RXFRM_SHIFT                7                                                   /*!< MSCAN_CANCTL0: RXFRM Position           */

/* ------- MSCAN_CANCTL1                            ------ */
#define MSCAN_CANCTL1_INITAK_MASK                (0x01UL << MSCAN_CANCTL1_INITAK_SHIFT)              /*!< MSCAN_CANCTL1: INITAK Mask              */
#define MSCAN_CANCTL1_INITAK_SHIFT               0                                                   /*!< MSCAN_CANCTL1: INITAK Position          */
#define MSCAN_CANCTL1_SLPAK_MASK                 (0x01UL << MSCAN_CANCTL1_SLPAK_SHIFT)               /*!< MSCAN_CANCTL1: SLPAK Mask               */
#define MSCAN_CANCTL1_SLPAK_SHIFT                1                                                   /*!< MSCAN_CANCTL1: SLPAK Position           */
#define MSCAN_CANCTL1_WUPM_MASK                  (0x01UL << MSCAN_CANCTL1_WUPM_SHIFT)                /*!< MSCAN_CANCTL1: WUPM Mask                */
#define MSCAN_CANCTL1_WUPM_SHIFT                 2                                                   /*!< MSCAN_CANCTL1: WUPM Position            */
#define MSCAN_CANCTL1_BORM_MASK                  (0x01UL << MSCAN_CANCTL1_BORM_SHIFT)                /*!< MSCAN_CANCTL1: BORM Mask                */
#define MSCAN_CANCTL1_BORM_SHIFT                 3                                                   /*!< MSCAN_CANCTL1: BORM Position            */
#define MSCAN_CANCTL1_LISTEN_MASK                (0x01UL << MSCAN_CANCTL1_LISTEN_SHIFT)              /*!< MSCAN_CANCTL1: LISTEN Mask              */
#define MSCAN_CANCTL1_LISTEN_SHIFT               4                                                   /*!< MSCAN_CANCTL1: LISTEN Position          */
#define MSCAN_CANCTL1_LOOPB_MASK                 (0x01UL << MSCAN_CANCTL1_LOOPB_SHIFT)               /*!< MSCAN_CANCTL1: LOOPB Mask               */
#define MSCAN_CANCTL1_LOOPB_SHIFT                5                                                   /*!< MSCAN_CANCTL1: LOOPB Position           */
#define MSCAN_CANCTL1_CLKSRC_MASK                (0x01UL << MSCAN_CANCTL1_CLKSRC_SHIFT)              /*!< MSCAN_CANCTL1: CLKSRC Mask              */
#define MSCAN_CANCTL1_CLKSRC_SHIFT               6                                                   /*!< MSCAN_CANCTL1: CLKSRC Position          */
#define MSCAN_CANCTL1_CANE_MASK                  (0x01UL << MSCAN_CANCTL1_CANE_SHIFT)                /*!< MSCAN_CANCTL1: CANE Mask                */
#define MSCAN_CANCTL1_CANE_SHIFT                 7                                                   /*!< MSCAN_CANCTL1: CANE Position            */

/* ------- MSCAN_CANBTR0                            ------ */
#define MSCAN_CANBTR0_BRP_MASK                   (0x1FUL << MSCAN_CANBTR0_BRP_SHIFT)                 /*!< MSCAN_CANBTR0: BRP Mask                 */
#define MSCAN_CANBTR0_BRP_SHIFT                  0                                                   /*!< MSCAN_CANBTR0: BRP Position             */
#define MSCAN_CANBTR0_BRP(x)                     (((x)<<MSCAN_CANBTR0_BRP_SHIFT)&MSCAN_CANBTR0_BRP_MASK) /*!< MSCAN_CANBTR0                           */
#define MSCAN_CANBTR0_SJW_MASK                   (0x03UL << MSCAN_CANBTR0_SJW_SHIFT)                 /*!< MSCAN_CANBTR0: SJW Mask                 */
#define MSCAN_CANBTR0_SJW_SHIFT                  6                                                   /*!< MSCAN_CANBTR0: SJW Position             */
#define MSCAN_CANBTR0_SJW(x)                     (((x)<<MSCAN_CANBTR0_SJW_SHIFT)&MSCAN_CANBTR0_SJW_MASK) /*!< MSCAN_CANBTR0                           */

/* ------- MSCAN_CANBTR1                            ------ */
#define MSCAN_CANBTR1_TSEG1_MASK                 (0x0FUL << MSCAN_CANBTR1_TSEG1_SHIFT)               /*!< MSCAN_CANBTR1: TSEG1 Mask               */
#define MSCAN_CANBTR1_TSEG1_SHIFT                0                                                   /*!< MSCAN_CANBTR1: TSEG1 Position           */
#define MSCAN_CANBTR1_TSEG1(x)                   (((x)<<MSCAN_CANBTR1_TSEG1_SHIFT)&MSCAN_CANBTR1_TSEG1_MASK) /*!< MSCAN_CANBTR1                           */
#define MSCAN_CANBTR1_TSEG2_MASK                 (0x07UL << MSCAN_CANBTR1_TSEG2_SHIFT)               /*!< MSCAN_CANBTR1: TSEG2 Mask               */
#define MSCAN_CANBTR1_TSEG2_SHIFT                4                                                   /*!< MSCAN_CANBTR1: TSEG2 Position           */
#define MSCAN_CANBTR1_TSEG2(x)                   (((x)<<MSCAN_CANBTR1_TSEG2_SHIFT)&MSCAN_CANBTR1_TSEG2_MASK) /*!< MSCAN_CANBTR1                           */
#define MSCAN_CANBTR1_SAMP_MASK                  (0x01UL << MSCAN_CANBTR1_SAMP_SHIFT)                /*!< MSCAN_CANBTR1: SAMP Mask                */
#define MSCAN_CANBTR1_SAMP_SHIFT                 7                                                   /*!< MSCAN_CANBTR1: SAMP Position            */

/* ------- MSCAN_CANRFLG                            ------ */
#define MSCAN_CANRFLG_RXF_MASK                   (0x01UL << MSCAN_CANRFLG_RXF_SHIFT)                 /*!< MSCAN_CANRFLG: RXF Mask                 */
#define MSCAN_CANRFLG_RXF_SHIFT                  0                                                   /*!< MSCAN_CANRFLG: RXF Position             */
#define MSCAN_CANRFLG_OVRIF_MASK                 (0x01UL << MSCAN_CANRFLG_OVRIF_SHIFT)               /*!< MSCAN_CANRFLG: OVRIF Mask               */
#define MSCAN_CANRFLG_OVRIF_SHIFT                1                                                   /*!< MSCAN_CANRFLG: OVRIF Position           */
#define MSCAN_CANRFLG_TSTAT_MASK                 (0x03UL << MSCAN_CANRFLG_TSTAT_SHIFT)               /*!< MSCAN_CANRFLG: TSTAT Mask               */
#define MSCAN_CANRFLG_TSTAT_SHIFT                2                                                   /*!< MSCAN_CANRFLG: TSTAT Position           */
#define MSCAN_CANRFLG_TSTAT(x)                   (((x)<<MSCAN_CANRFLG_TSTAT_SHIFT)&MSCAN_CANRFLG_TSTAT_MASK) /*!< MSCAN_CANRFLG                           */
#define MSCAN_CANRFLG_RSTAT_MASK                 (0x03UL << MSCAN_CANRFLG_RSTAT_SHIFT)               /*!< MSCAN_CANRFLG: RSTAT Mask               */
#define MSCAN_CANRFLG_RSTAT_SHIFT                4                                                   /*!< MSCAN_CANRFLG: RSTAT Position           */
#define MSCAN_CANRFLG_RSTAT(x)                   (((x)<<MSCAN_CANRFLG_RSTAT_SHIFT)&MSCAN_CANRFLG_RSTAT_MASK) /*!< MSCAN_CANRFLG                           */
#define MSCAN_CANRFLG_CSCIF_MASK                 (0x01UL << MSCAN_CANRFLG_CSCIF_SHIFT)               /*!< MSCAN_CANRFLG: CSCIF Mask               */
#define MSCAN_CANRFLG_CSCIF_SHIFT                6                                                   /*!< MSCAN_CANRFLG: CSCIF Position           */
#define MSCAN_CANRFLG_WUPIF_MASK                 (0x01UL << MSCAN_CANRFLG_WUPIF_SHIFT)               /*!< MSCAN_CANRFLG: WUPIF Mask               */
#define MSCAN_CANRFLG_WUPIF_SHIFT                7                                                   /*!< MSCAN_CANRFLG: WUPIF Position           */

/* ------- MSCAN_CANRIER                            ------ */
#define MSCAN_CANRIER_RXFIE_MASK                 (0x01UL << MSCAN_CANRIER_RXFIE_SHIFT)               /*!< MSCAN_CANRIER: RXFIE Mask               */
#define MSCAN_CANRIER_RXFIE_SHIFT                0                                                   /*!< MSCAN_CANRIER: RXFIE Position           */
#define MSCAN_CANRIER_OVRIE_MASK                 (0x01UL << MSCAN_CANRIER_OVRIE_SHIFT)               /*!< MSCAN_CANRIER: OVRIE Mask               */
#define MSCAN_CANRIER_OVRIE_SHIFT                1                                                   /*!< MSCAN_CANRIER: OVRIE Position           */
#define MSCAN_CANRIER_TSTATE_MASK                (0x03UL << MSCAN_CANRIER_TSTATE_SHIFT)              /*!< MSCAN_CANRIER: TSTATE Mask              */
#define MSCAN_CANRIER_TSTATE_SHIFT               2                                                   /*!< MSCAN_CANRIER: TSTATE Position          */
#define MSCAN_CANRIER_TSTATE(x)                  (((x)<<MSCAN_CANRIER_TSTATE_SHIFT)&MSCAN_CANRIER_TSTATE_MASK) /*!< MSCAN_CANRIER                           */
#define MSCAN_CANRIER_RSTATE_MASK                (0x03UL << MSCAN_CANRIER_RSTATE_SHIFT)              /*!< MSCAN_CANRIER: RSTATE Mask              */
#define MSCAN_CANRIER_RSTATE_SHIFT               4                                                   /*!< MSCAN_CANRIER: RSTATE Position          */
#define MSCAN_CANRIER_RSTATE(x)                  (((x)<<MSCAN_CANRIER_RSTATE_SHIFT)&MSCAN_CANRIER_RSTATE_MASK) /*!< MSCAN_CANRIER                           */
#define MSCAN_CANRIER_CSCIE_MASK                 (0x01UL << MSCAN_CANRIER_CSCIE_SHIFT)               /*!< MSCAN_CANRIER: CSCIE Mask               */
#define MSCAN_CANRIER_CSCIE_SHIFT                6                                                   /*!< MSCAN_CANRIER: CSCIE Position           */
#define MSCAN_CANRIER_WUPIE_MASK                 (0x01UL << MSCAN_CANRIER_WUPIE_SHIFT)               /*!< MSCAN_CANRIER: WUPIE Mask               */
#define MSCAN_CANRIER_WUPIE_SHIFT                7                                                   /*!< MSCAN_CANRIER: WUPIE Position           */

/* ------- MSCAN_CANTFLG                            ------ */
#define MSCAN_CANTFLG_TXE_MASK                   (0x07UL << MSCAN_CANTFLG_TXE_SHIFT)                 /*!< MSCAN_CANTFLG: TXE Mask                 */
#define MSCAN_CANTFLG_TXE_SHIFT                  0                                                   /*!< MSCAN_CANTFLG: TXE Position             */
#define MSCAN_CANTFLG_TXE(x)                     (((x)<<MSCAN_CANTFLG_TXE_SHIFT)&MSCAN_CANTFLG_TXE_MASK) /*!< MSCAN_CANTFLG                           */

/* ------- MSCAN_CANTIER                            ------ */
#define MSCAN_CANTIER_TXEIE_MASK                 (0x07UL << MSCAN_CANTIER_TXEIE_SHIFT)               /*!< MSCAN_CANTIER: TXEIE Mask               */
#define MSCAN_CANTIER_TXEIE_SHIFT                0                                                   /*!< MSCAN_CANTIER: TXEIE Position           */
#define MSCAN_CANTIER_TXEIE(x)                   (((x)<<MSCAN_CANTIER_TXEIE_SHIFT)&MSCAN_CANTIER_TXEIE_MASK) /*!< MSCAN_CANTIER                           */

/* ------- MSCAN_CANTARQ                            ------ */
#define MSCAN_CANTARQ_ABTRQ_MASK                 (0x07UL << MSCAN_CANTARQ_ABTRQ_SHIFT)               /*!< MSCAN_CANTARQ: ABTRQ Mask               */
#define MSCAN_CANTARQ_ABTRQ_SHIFT                0                                                   /*!< MSCAN_CANTARQ: ABTRQ Position           */
#define MSCAN_CANTARQ_ABTRQ(x)                   (((x)<<MSCAN_CANTARQ_ABTRQ_SHIFT)&MSCAN_CANTARQ_ABTRQ_MASK) /*!< MSCAN_CANTARQ                           */

/* ------- MSCAN_CANTAAK                            ------ */
#define MSCAN_CANTAAK_ABTAK_MASK                 (0x07UL << MSCAN_CANTAAK_ABTAK_SHIFT)               /*!< MSCAN_CANTAAK: ABTAK Mask               */
#define MSCAN_CANTAAK_ABTAK_SHIFT                0                                                   /*!< MSCAN_CANTAAK: ABTAK Position           */
#define MSCAN_CANTAAK_ABTAK(x)                   (((x)<<MSCAN_CANTAAK_ABTAK_SHIFT)&MSCAN_CANTAAK_ABTAK_MASK) /*!< MSCAN_CANTAAK                           */

/* ------- MSCAN_CANTBSEL                           ------ */
#define MSCAN_CANTBSEL_TX_MASK                   (0x07UL << MSCAN_CANTBSEL_TX_SHIFT)                 /*!< MSCAN_CANTBSEL: TX Mask                 */
#define MSCAN_CANTBSEL_TX_SHIFT                  0                                                   /*!< MSCAN_CANTBSEL: TX Position             */
#define MSCAN_CANTBSEL_TX(x)                     (((x)<<MSCAN_CANTBSEL_TX_SHIFT)&MSCAN_CANTBSEL_TX_MASK) /*!< MSCAN_CANTBSEL                          */

/* ------- MSCAN_CANIDAC                            ------ */
#define MSCAN_CANIDAC_IDHIT_MASK                 (0x07UL << MSCAN_CANIDAC_IDHIT_SHIFT)               /*!< MSCAN_CANIDAC: IDHIT Mask               */
#define MSCAN_CANIDAC_IDHIT_SHIFT                0                                                   /*!< MSCAN_CANIDAC: IDHIT Position           */
#define MSCAN_CANIDAC_IDHIT(x)                   (((x)<<MSCAN_CANIDAC_IDHIT_SHIFT)&MSCAN_CANIDAC_IDHIT_MASK) /*!< MSCAN_CANIDAC                           */
#define MSCAN_CANIDAC_IDAM_MASK                  (0x03UL << MSCAN_CANIDAC_IDAM_SHIFT)                /*!< MSCAN_CANIDAC: IDAM Mask                */
#define MSCAN_CANIDAC_IDAM_SHIFT                 4                                                   /*!< MSCAN_CANIDAC: IDAM Position            */
#define MSCAN_CANIDAC_IDAM(x)                    (((x)<<MSCAN_CANIDAC_IDAM_SHIFT)&MSCAN_CANIDAC_IDAM_MASK) /*!< MSCAN_CANIDAC                           */

/* ------- MSCAN_CANMISC                            ------ */
#define MSCAN_CANMISC_BOHOLD_MASK                (0x01UL << MSCAN_CANMISC_BOHOLD_SHIFT)              /*!< MSCAN_CANMISC: BOHOLD Mask              */
#define MSCAN_CANMISC_BOHOLD_SHIFT               0                                                   /*!< MSCAN_CANMISC: BOHOLD Position          */

/* ------- MSCAN_CANRXERR                           ------ */

/* ------- MSCAN_CANTXERR                           ------ */

/* ------- MSCAN_CANIDAR                            ------ */

/* ------- MSCAN_CANIDMR                            ------ */

/* ------- MSCAN_CANIDAR                            ------ */

/* ------- MSCAN_CANIDMR                            ------ */

/* ------- MSCAN_REIDR                              ------ */

/* ------- MSCAN_RSIDR                              ------ */

/* ------- MSCAN_REDSR                              ------ */

/* ------- MSCAN_RDLR                               ------ */
#define MSCAN_RDLR_RDLC_MASK                     (0x0FUL << MSCAN_RDLR_RDLC_SHIFT)                   /*!< MSCAN_RDLR: RDLC Mask                   */
#define MSCAN_RDLR_RDLC_SHIFT                    0                                                   /*!< MSCAN_RDLR: RDLC Position               */
#define MSCAN_RDLR_RDLC(x)                       (((x)<<MSCAN_RDLR_RDLC_SHIFT)&MSCAN_RDLR_RDLC_MASK) /*!< MSCAN_RDLR                              */

/* ------- MSCAN_RTSRH                              ------ */

/* ------- MSCAN_RTSRL                              ------ */

/* ------- MSCAN_TEIDR                              ------ */

/* ------- MSCAN_TSIDR                              ------ */

/* ------- MSCAN_TEDSR                              ------ */

/* ------- MSCAN_TDLR                               ------ */

/* ------- MSCAN_TBPR                               ------ */

/* ------- MSCAN_TTSRH                              ------ */

/* ------- MSCAN_TTSRL                              ------ */

/* -------------------------------------------------------------------------------- */
/* -----------     'MSCAN' Register Access macros                       ----------- */
/* -------------------------------------------------------------------------------- */

#define MSCAN_CANCTL0                  (MSCAN->CANCTL0)
#define MSCAN_CANCTL1                  (MSCAN->CANCTL1)
#define MSCAN_CANBTR0                  (MSCAN->CANBTR0)
#define MSCAN_CANBTR1                  (MSCAN->CANBTR1)
#define MSCAN_CANRFLG                  (MSCAN->CANRFLG)
#define MSCAN_CANRIER                  (MSCAN->CANRIER)
#define MSCAN_CANTFLG                  (MSCAN->CANTFLG)
#define MSCAN_CANTIER                  (MSCAN->CANTIER)
#define MSCAN_CANTARQ                  (MSCAN->CANTARQ)
#define MSCAN_CANTAAK                  (MSCAN->CANTAAK)
#define MSCAN_CANTBSEL                 (MSCAN->CANTBSEL)
#define MSCAN_CANIDAC                  (MSCAN->CANIDAC)
#define MSCAN_CANMISC                  (MSCAN->CANMISC)
#define MSCAN_CANRXERR                 (MSCAN->CANRXERR)
#define MSCAN_CANTXERR                 (MSCAN->CANTXERR)
#define MSCAN_CANIDAR0                 (MSCAN->CANIDAR[0])
#define MSCAN_CANIDAR1                 (MSCAN->CANIDAR[1])
#define MSCAN_CANIDAR2                 (MSCAN->CANIDAR[2])
#define MSCAN_CANIDAR3                 (MSCAN->CANIDAR[3])
#define MSCAN_CANIDMR0                 (MSCAN->CANIDMR[0])
#define MSCAN_CANIDMR1                 (MSCAN->CANIDMR[1])
#define MSCAN_CANIDMR2                 (MSCAN->CANIDMR[2])
#define MSCAN_CANIDMR3                 (MSCAN->CANIDMR[3])
#define MSCAN_CANIDAR4                 (MSCAN->CANIDAR4)
#define MSCAN_CANIDAR5                 (MSCAN->CANIDAR5)
#define MSCAN_CANIDAR6                 (MSCAN->CANIDAR6)
#define MSCAN_CANIDAR7                 (MSCAN->CANIDAR7)
#define MSCAN_CANIDMR4                 (MSCAN->CANIDMR4)
#define MSCAN_CANIDMR5                 (MSCAN->CANIDMR5)
#define MSCAN_CANIDMR6                 (MSCAN->CANIDMR6)
#define MSCAN_CANIDMR7                 (MSCAN->CANIDMR7)
#define MSCAN_REIDR0                   (MSCAN->REIDR[0])
#define MSCAN_REIDR1                   (MSCAN->REIDR[1])
#define MSCAN_REIDR2                   (MSCAN->REIDR[2])
#define MSCAN_REIDR3                   (MSCAN->REIDR[3])
#define MSCAN_RSIDR0                   (MSCAN->RSIDR[0])
#define MSCAN_RSIDR1                   (MSCAN->RSIDR[1])
#define MSCAN_REDSR0                   (MSCAN->REDSR[0])
#define MSCAN_REDSR1                   (MSCAN->REDSR[1])
#define MSCAN_REDSR2                   (MSCAN->REDSR[2])
#define MSCAN_REDSR3                   (MSCAN->REDSR[3])
#define MSCAN_REDSR4                   (MSCAN->REDSR[4])
#define MSCAN_REDSR5                   (MSCAN->REDSR[5])
#define MSCAN_REDSR6                   (MSCAN->REDSR[6])
#define MSCAN_REDSR7                   (MSCAN->REDSR[7])
#define MSCAN_RDLR                     (MSCAN->RDLR)
#define MSCAN_RTSRH                    (MSCAN->RTSRH)
#define MSCAN_RTSRL                    (MSCAN->RTSRL)
#define MSCAN_TEIDR0                   (MSCAN->TEIDR[0])
#define MSCAN_TEIDR1                   (MSCAN->TEIDR[1])
#define MSCAN_TEIDR2                   (MSCAN->TEIDR[2])
#define MSCAN_TEIDR3                   (MSCAN->TEIDR[3])
#define MSCAN_TSIDR0                   (MSCAN->TSIDR[0])
#define MSCAN_TSIDR1                   (MSCAN->TSIDR[1])
#define MSCAN_TEDSR0                   (MSCAN->TEDSR[0])
#define MSCAN_TEDSR1                   (MSCAN->TEDSR[1])
#define MSCAN_TEDSR2                   (MSCAN->TEDSR[2])
#define MSCAN_TEDSR3                   (MSCAN->TEDSR[3])
#define MSCAN_TEDSR4                   (MSCAN->TEDSR[4])
#define MSCAN_TEDSR5                   (MSCAN->TEDSR[5])
#define MSCAN_TEDSR6                   (MSCAN->TEDSR[6])
#define MSCAN_TEDSR7                   (MSCAN->TEDSR[7])
#define MSCAN_TDLR                     (MSCAN->TDLR)
#define MSCAN_TBPR                     (MSCAN->TBPR)
#define MSCAN_TTSRH                    (MSCAN->TTSRH)
#define MSCAN_TTSRL                    (MSCAN->TTSRL)

/* ================================================================================ */
/* ================           NV (file:NV_FTMRH)                   ================ */
/* ================================================================================ */

/**
 * @brief Flash configuration field
 */
typedef struct {                                /*!<       NV Structure                                                 */
   __I  uint8_t   BACKKEY[8];                   /*!< 0000: Backdoor Comparison Key                                      */
   __I  uint32_t  RESERVED0;                    /*!< 0008:                                                              */
   __I  uint8_t   EEPROT;                       /*!< 000C: Non-volatile EE-Flash Protection Register (If implemented)   */
   __I  uint8_t   FPROT;                        /*!< 000D: Non-volatile P-Flash Protection Register                     */
   __I  uint8_t   FSEC;                         /*!< 000E: Non-volatile Flash Security Register                         */
   __I  uint8_t   FOPT;                         /*!< 000F: Non-volatile Flash Option Register                           */
} NV_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'NV' Position & Mask macros                          ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- NV_BACKKEY                               ------ */
#define NV_BACKKEY_KEY_MASK                      (0xFFUL << NV_BACKKEY_KEY_SHIFT)                    /*!< NV_BACKKEY: KEY Mask                    */
#define NV_BACKKEY_KEY_SHIFT                     0                                                   /*!< NV_BACKKEY: KEY Position                */
#define NV_BACKKEY_KEY(x)                        (((x)<<NV_BACKKEY_KEY_SHIFT)&NV_BACKKEY_KEY_MASK)   /*!< NV_BACKKEY                              */

/* ------- NV_EEPROT                                ------ */
#define NV_EEPROT_PROT_MASK                      (0xFFUL << NV_EEPROT_PROT_SHIFT)                    /*!< NV_EEPROT: PROT Mask                    */
#define NV_EEPROT_PROT_SHIFT                     0                                                   /*!< NV_EEPROT: PROT Position                */
#define NV_EEPROT_PROT(x)                        (((x)<<NV_EEPROT_PROT_SHIFT)&NV_EEPROT_PROT_MASK)   /*!< NV_EEPROT                               */

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
#define NV_FOPT_LPBOOT0_MASK                     (0x01UL << NV_FOPT_LPBOOT0_SHIFT)                   /*!< NV_FOPT: LPBOOT0 Mask                   */
#define NV_FOPT_LPBOOT0_SHIFT                    0                                                   /*!< NV_FOPT: LPBOOT0 Position               */
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

#define NV_BACKKEY0                    (NV->BACKKEY[0])
#define NV_BACKKEY1                    (NV->BACKKEY[1])
#define NV_BACKKEY2                    (NV->BACKKEY[2])
#define NV_BACKKEY3                    (NV->BACKKEY[3])
#define NV_BACKKEY4                    (NV->BACKKEY[4])
#define NV_BACKKEY5                    (NV->BACKKEY[5])
#define NV_BACKKEY6                    (NV->BACKKEY[6])
#define NV_BACKKEY7                    (NV->BACKKEY[7])
#define NV_EEPROT                      (NV->EEPROT)
#define NV_FPROT                       (NV->FPROT)
#define NV_FSEC                        (NV->FSEC)
#define NV_FOPT                        (NV->FOPT)

/* ================================================================================ */
/* ================           OSC (file:OSC_MKE)                   ================ */
/* ================================================================================ */

/**
 * @brief Oscillator
 */
typedef struct {                                /*!<       OSC Structure                                                */
   __IO uint8_t   CR;                           /*!< 0000: OSC Control Register                                         */
} OSC_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'OSC' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- OSC_CR                                   ------ */
#define OSC_CR_OSCINIT_MASK                      (0x01UL << OSC_CR_OSCINIT_SHIFT)                    /*!< OSC_CR: OSCINIT Mask                    */
#define OSC_CR_OSCINIT_SHIFT                     0                                                   /*!< OSC_CR: OSCINIT Position                */
#define OSC_CR_HGO_MASK                          (0x01UL << OSC_CR_HGO_SHIFT)                        /*!< OSC_CR: HGO Mask                        */
#define OSC_CR_HGO_SHIFT                         1                                                   /*!< OSC_CR: HGO Position                    */
#define OSC_CR_RANGE_MASK                        (0x01UL << OSC_CR_RANGE_SHIFT)                      /*!< OSC_CR: RANGE Mask                      */
#define OSC_CR_RANGE_SHIFT                       2                                                   /*!< OSC_CR: RANGE Position                  */
#define OSC_CR_OSCOS_MASK                        (0x01UL << OSC_CR_OSCOS_SHIFT)                      /*!< OSC_CR: OSCOS Mask                      */
#define OSC_CR_OSCOS_SHIFT                       4                                                   /*!< OSC_CR: OSCOS Position                  */
#define OSC_CR_OSCSTEN_MASK                      (0x01UL << OSC_CR_OSCSTEN_SHIFT)                    /*!< OSC_CR: OSCSTEN Mask                    */
#define OSC_CR_OSCSTEN_SHIFT                     5                                                   /*!< OSC_CR: OSCSTEN Position                */
#define OSC_CR_OSCEN_MASK                        (0x00UL << OSC_CR_OSCEN_SHIFT)                      /*!< OSC_CR: OSCEN Mask                      */
#define OSC_CR_OSCEN_SHIFT                       7                                                   /*!< OSC_CR: OSCEN Position                  */

/* -------------------------------------------------------------------------------- */
/* -----------     'OSC' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define OSC_CR                         (OSC->CR)

/* ================================================================================ */
/* ================           PIT (file:PIT_2CH_CHAIN)             ================ */
/* ================================================================================ */

/**
 * @brief Periodic Interrupt Timer (2 channels)
 */
typedef struct {                                /*!<       PIT Structure                                                */
   __IO uint32_t  MCR;                          /*!< 0000: Module Control Register                                      */
   __I  uint32_t  RESERVED0[63];                /*!< 0004:                                                              */
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
#define PIT_LDVAL0                     (PIT->CS[0].LDVAL)
#define PIT_CVAL0                      (PIT->CS[0].CVAL)
#define PIT_TCTRL0                     (PIT->CS[0].TCTRL)
#define PIT_TFLG0                      (PIT->CS[0].TFLG)
#define PIT_LDVAL1                     (PIT->CS[1].LDVAL)
#define PIT_CVAL1                      (PIT->CS[1].CVAL)
#define PIT_TCTRL1                     (PIT->CS[1].TCTRL)
#define PIT_TFLG1                      (PIT->CS[1].TFLG)

/* ================================================================================ */
/* ================           PMC (file:PMC_MKE)                   ================ */
/* ================================================================================ */

/**
 * @brief Power Management Controller
 */
typedef struct {                                /*!<       PMC Structure                                                */
   __IO uint8_t   SPMSC1;                       /*!< 0000: Low Voltage Detect Status and Control 1 Register             */
   __IO uint8_t   SPMSC2;                       /*!< 0001: System Power Management Status and Control 2 Register        */
} PMC_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'PMC' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- PMC_SPMSC1                               ------ */
#define PMC_SPMSC1_BGBE_MASK                     (0x01UL << PMC_SPMSC1_BGBE_SHIFT)                   /*!< PMC_SPMSC1: BGBE Mask                   */
#define PMC_SPMSC1_BGBE_SHIFT                    0                                                   /*!< PMC_SPMSC1: BGBE Position               */
#define PMC_SPMSC1_LVDE_MASK                     (0x01UL << PMC_SPMSC1_LVDE_SHIFT)                   /*!< PMC_SPMSC1: LVDE Mask                   */
#define PMC_SPMSC1_LVDE_SHIFT                    2                                                   /*!< PMC_SPMSC1: LVDE Position               */
#define PMC_SPMSC1_LVDSE_MASK                    (0x01UL << PMC_SPMSC1_LVDSE_SHIFT)                  /*!< PMC_SPMSC1: LVDSE Mask                  */
#define PMC_SPMSC1_LVDSE_SHIFT                   3                                                   /*!< PMC_SPMSC1: LVDSE Position              */
#define PMC_SPMSC1_LVDRE_MASK                    (0x01UL << PMC_SPMSC1_LVDRE_SHIFT)                  /*!< PMC_SPMSC1: LVDRE Mask                  */
#define PMC_SPMSC1_LVDRE_SHIFT                   4                                                   /*!< PMC_SPMSC1: LVDRE Position              */
#define PMC_SPMSC1_LVWIE_MASK                    (0x01UL << PMC_SPMSC1_LVWIE_SHIFT)                  /*!< PMC_SPMSC1: LVWIE Mask                  */
#define PMC_SPMSC1_LVWIE_SHIFT                   5                                                   /*!< PMC_SPMSC1: LVWIE Position              */
#define PMC_SPMSC1_LVWACK_MASK                   (0x01UL << PMC_SPMSC1_LVWACK_SHIFT)                 /*!< PMC_SPMSC1: LVWACK Mask                 */
#define PMC_SPMSC1_LVWACK_SHIFT                  6                                                   /*!< PMC_SPMSC1: LVWACK Position             */
#define PMC_SPMSC1_LVWF_MASK                     (0x01UL << PMC_SPMSC1_LVWF_SHIFT)                   /*!< PMC_SPMSC1: LVWF Mask                   */
#define PMC_SPMSC1_LVWF_SHIFT                    7                                                   /*!< PMC_SPMSC1: LVWF Position               */

/* ------- PMC_SPMSC2                               ------ */
#define PMC_SPMSC2_LVWV_MASK                     (0x03UL << PMC_SPMSC2_LVWV_SHIFT)                   /*!< PMC_SPMSC2: LVWV Mask                   */
#define PMC_SPMSC2_LVWV_SHIFT                    4                                                   /*!< PMC_SPMSC2: LVWV Position               */
#define PMC_SPMSC2_LVWV(x)                       (((x)<<PMC_SPMSC2_LVWV_SHIFT)&PMC_SPMSC2_LVWV_MASK) /*!< PMC_SPMSC2                              */
#define PMC_SPMSC2_LVDV_MASK                     (0x01UL << PMC_SPMSC2_LVDV_SHIFT)                   /*!< PMC_SPMSC2: LVDV Mask                   */
#define PMC_SPMSC2_LVDV_SHIFT                    6                                                   /*!< PMC_SPMSC2: LVDV Position               */

/* -------------------------------------------------------------------------------- */
/* -----------     'PMC' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define PMC_SPMSC1                     (PMC->SPMSC1)
#define PMC_SPMSC2                     (PMC->SPMSC2)

/* ================================================================================ */
/* ================           PORT (file:PORT_MKE_2)               ================ */
/* ================================================================================ */

/**
 * @brief Port control
 */
typedef struct {                                /*!<       PORT Structure                                               */
   __IO uint32_t  IOFLT0;                       /*!< 0000: Port Filter Register 0                                       */
   __IO uint32_t  IOFLT1;                       /*!< 0004: Port Filter Register 1                                       */
   __IO uint32_t  PUE0;                         /*!< 0008: Port Pull-up Enable Register 0                               */
   __IO uint32_t  PUE1;                         /*!< 000C: Port Pull-up Enable Register 1                               */
   __IO uint32_t  PUE2;                         /*!< 0010: Port Pull-up Enable High Register                            */
   __IO uint32_t  HDRVE;                        /*!< 0014: Port High Drive Enable Register                              */
} PORT_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'PORT' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- PORT_IOFLT0                              ------ */
#define PORT_IOFLT0_FLTA_MASK                    (0x03UL << PORT_IOFLT0_FLTA_SHIFT)                  /*!< PORT_IOFLT0: FLTA Mask                  */
#define PORT_IOFLT0_FLTA_SHIFT                   0                                                   /*!< PORT_IOFLT0: FLTA Position              */
#define PORT_IOFLT0_FLTA(x)                      (((x)<<PORT_IOFLT0_FLTA_SHIFT)&PORT_IOFLT0_FLTA_MASK) /*!< PORT_IOFLT0                             */
#define PORT_IOFLT0_FLTB_MASK                    (0x03UL << PORT_IOFLT0_FLTB_SHIFT)                  /*!< PORT_IOFLT0: FLTB Mask                  */
#define PORT_IOFLT0_FLTB_SHIFT                   2                                                   /*!< PORT_IOFLT0: FLTB Position              */
#define PORT_IOFLT0_FLTB(x)                      (((x)<<PORT_IOFLT0_FLTB_SHIFT)&PORT_IOFLT0_FLTB_MASK) /*!< PORT_IOFLT0                             */
#define PORT_IOFLT0_FLTC_MASK                    (0x03UL << PORT_IOFLT0_FLTC_SHIFT)                  /*!< PORT_IOFLT0: FLTC Mask                  */
#define PORT_IOFLT0_FLTC_SHIFT                   4                                                   /*!< PORT_IOFLT0: FLTC Position              */
#define PORT_IOFLT0_FLTC(x)                      (((x)<<PORT_IOFLT0_FLTC_SHIFT)&PORT_IOFLT0_FLTC_MASK) /*!< PORT_IOFLT0                             */
#define PORT_IOFLT0_FLTD_MASK                    (0x03UL << PORT_IOFLT0_FLTD_SHIFT)                  /*!< PORT_IOFLT0: FLTD Mask                  */
#define PORT_IOFLT0_FLTD_SHIFT                   6                                                   /*!< PORT_IOFLT0: FLTD Position              */
#define PORT_IOFLT0_FLTD(x)                      (((x)<<PORT_IOFLT0_FLTD_SHIFT)&PORT_IOFLT0_FLTD_MASK) /*!< PORT_IOFLT0                             */
#define PORT_IOFLT0_FLTE_MASK                    (0x03UL << PORT_IOFLT0_FLTE_SHIFT)                  /*!< PORT_IOFLT0: FLTE Mask                  */
#define PORT_IOFLT0_FLTE_SHIFT                   8                                                   /*!< PORT_IOFLT0: FLTE Position              */
#define PORT_IOFLT0_FLTE(x)                      (((x)<<PORT_IOFLT0_FLTE_SHIFT)&PORT_IOFLT0_FLTE_MASK) /*!< PORT_IOFLT0                             */
#define PORT_IOFLT0_FLTF_MASK                    (0x03UL << PORT_IOFLT0_FLTF_SHIFT)                  /*!< PORT_IOFLT0: FLTF Mask                  */
#define PORT_IOFLT0_FLTF_SHIFT                   10                                                  /*!< PORT_IOFLT0: FLTF Position              */
#define PORT_IOFLT0_FLTF(x)                      (((x)<<PORT_IOFLT0_FLTF_SHIFT)&PORT_IOFLT0_FLTF_MASK) /*!< PORT_IOFLT0                             */
#define PORT_IOFLT0_FLTG_MASK                    (0x03UL << PORT_IOFLT0_FLTG_SHIFT)                  /*!< PORT_IOFLT0: FLTG Mask                  */
#define PORT_IOFLT0_FLTG_SHIFT                   12                                                  /*!< PORT_IOFLT0: FLTG Position              */
#define PORT_IOFLT0_FLTG(x)                      (((x)<<PORT_IOFLT0_FLTG_SHIFT)&PORT_IOFLT0_FLTG_MASK) /*!< PORT_IOFLT0                             */
#define PORT_IOFLT0_FLTH_MASK                    (0x03UL << PORT_IOFLT0_FLTH_SHIFT)                  /*!< PORT_IOFLT0: FLTH Mask                  */
#define PORT_IOFLT0_FLTH_SHIFT                   14                                                  /*!< PORT_IOFLT0: FLTH Position              */
#define PORT_IOFLT0_FLTH(x)                      (((x)<<PORT_IOFLT0_FLTH_SHIFT)&PORT_IOFLT0_FLTH_MASK) /*!< PORT_IOFLT0                             */
#define PORT_IOFLT0_FLTRST_MASK                  (0x03UL << PORT_IOFLT0_FLTRST_SHIFT)                /*!< PORT_IOFLT0: FLTRST Mask                */
#define PORT_IOFLT0_FLTRST_SHIFT                 16                                                  /*!< PORT_IOFLT0: FLTRST Position            */
#define PORT_IOFLT0_FLTRST(x)                    (((x)<<PORT_IOFLT0_FLTRST_SHIFT)&PORT_IOFLT0_FLTRST_MASK) /*!< PORT_IOFLT0                             */
#define PORT_IOFLT0_FLTKBI0_MASK                 (0x03UL << PORT_IOFLT0_FLTKBI0_SHIFT)               /*!< PORT_IOFLT0: FLTKBI0 Mask               */
#define PORT_IOFLT0_FLTKBI0_SHIFT                18                                                  /*!< PORT_IOFLT0: FLTKBI0 Position           */
#define PORT_IOFLT0_FLTKBI0(x)                   (((x)<<PORT_IOFLT0_FLTKBI0_SHIFT)&PORT_IOFLT0_FLTKBI0_MASK) /*!< PORT_IOFLT0                             */
#define PORT_IOFLT0_FLTKBI1_MASK                 (0x03UL << PORT_IOFLT0_FLTKBI1_SHIFT)               /*!< PORT_IOFLT0: FLTKBI1 Mask               */
#define PORT_IOFLT0_FLTKBI1_SHIFT                20                                                  /*!< PORT_IOFLT0: FLTKBI1 Position           */
#define PORT_IOFLT0_FLTKBI1(x)                   (((x)<<PORT_IOFLT0_FLTKBI1_SHIFT)&PORT_IOFLT0_FLTKBI1_MASK) /*!< PORT_IOFLT0                             */
#define PORT_IOFLT0_FLTNMI_MASK                  (0x03UL << PORT_IOFLT0_FLTNMI_SHIFT)                /*!< PORT_IOFLT0: FLTNMI Mask                */
#define PORT_IOFLT0_FLTNMI_SHIFT                 22                                                  /*!< PORT_IOFLT0: FLTNMI Position            */
#define PORT_IOFLT0_FLTNMI(x)                    (((x)<<PORT_IOFLT0_FLTNMI_SHIFT)&PORT_IOFLT0_FLTNMI_MASK) /*!< PORT_IOFLT0                             */
#define PORT_IOFLT0_FLTDIV1_MASK                 (0x03UL << PORT_IOFLT0_FLTDIV1_SHIFT)               /*!< PORT_IOFLT0: FLTDIV1 Mask               */
#define PORT_IOFLT0_FLTDIV1_SHIFT                24                                                  /*!< PORT_IOFLT0: FLTDIV1 Position           */
#define PORT_IOFLT0_FLTDIV1(x)                   (((x)<<PORT_IOFLT0_FLTDIV1_SHIFT)&PORT_IOFLT0_FLTDIV1_MASK) /*!< PORT_IOFLT0                             */
#define PORT_IOFLT0_FLTDIV2_MASK                 (0x07UL << PORT_IOFLT0_FLTDIV2_SHIFT)               /*!< PORT_IOFLT0: FLTDIV2 Mask               */
#define PORT_IOFLT0_FLTDIV2_SHIFT                26                                                  /*!< PORT_IOFLT0: FLTDIV2 Position           */
#define PORT_IOFLT0_FLTDIV2(x)                   (((x)<<PORT_IOFLT0_FLTDIV2_SHIFT)&PORT_IOFLT0_FLTDIV2_MASK) /*!< PORT_IOFLT0                             */
#define PORT_IOFLT0_FLTDIV3_MASK                 (0x07UL << PORT_IOFLT0_FLTDIV3_SHIFT)               /*!< PORT_IOFLT0: FLTDIV3 Mask               */
#define PORT_IOFLT0_FLTDIV3_SHIFT                29                                                  /*!< PORT_IOFLT0: FLTDIV3 Position           */
#define PORT_IOFLT0_FLTDIV3(x)                   (((x)<<PORT_IOFLT0_FLTDIV3_SHIFT)&PORT_IOFLT0_FLTDIV3_MASK) /*!< PORT_IOFLT0                             */

/* ------- PORT_IOFLT1                              ------ */
#define PORT_IOFLT1_FLTI_MASK                    (0x03UL << PORT_IOFLT1_FLTI_SHIFT)                  /*!< PORT_IOFLT1: FLTI Mask                  */
#define PORT_IOFLT1_FLTI_SHIFT                   0                                                   /*!< PORT_IOFLT1: FLTI Position              */
#define PORT_IOFLT1_FLTI(x)                      (((x)<<PORT_IOFLT1_FLTI_SHIFT)&PORT_IOFLT1_FLTI_MASK) /*!< PORT_IOFLT1                             */
#define PORT_IOFLT1_FLTIRQ_MASK                  (0x03UL << PORT_IOFLT1_FLTIRQ_SHIFT)                /*!< PORT_IOFLT1: FLTIRQ Mask                */
#define PORT_IOFLT1_FLTIRQ_SHIFT                 4                                                   /*!< PORT_IOFLT1: FLTIRQ Position            */
#define PORT_IOFLT1_FLTIRQ(x)                    (((x)<<PORT_IOFLT1_FLTIRQ_SHIFT)&PORT_IOFLT1_FLTIRQ_MASK) /*!< PORT_IOFLT1                             */
#define PORT_IOFLT1_FLTFTM0_MASK                 (0x03UL << PORT_IOFLT1_FLTFTM0_SHIFT)               /*!< PORT_IOFLT1: FLTFTM0 Mask               */
#define PORT_IOFLT1_FLTFTM0_SHIFT                6                                                   /*!< PORT_IOFLT1: FLTFTM0 Position           */
#define PORT_IOFLT1_FLTFTM0(x)                   (((x)<<PORT_IOFLT1_FLTFTM0_SHIFT)&PORT_IOFLT1_FLTFTM0_MASK) /*!< PORT_IOFLT1                             */
#define PORT_IOFLT1_FLTFTM1_MASK                 (0x03UL << PORT_IOFLT1_FLTFTM1_SHIFT)               /*!< PORT_IOFLT1: FLTFTM1 Mask               */
#define PORT_IOFLT1_FLTFTM1_SHIFT                8                                                   /*!< PORT_IOFLT1: FLTFTM1 Position           */
#define PORT_IOFLT1_FLTFTM1(x)                   (((x)<<PORT_IOFLT1_FLTFTM1_SHIFT)&PORT_IOFLT1_FLTFTM1_MASK) /*!< PORT_IOFLT1                             */
#define PORT_IOFLT1_FLTPWT_MASK                  (0x03UL << PORT_IOFLT1_FLTPWT_SHIFT)                /*!< PORT_IOFLT1: FLTPWT Mask                */
#define PORT_IOFLT1_FLTPWT_SHIFT                 10                                                  /*!< PORT_IOFLT1: FLTPWT Position            */
#define PORT_IOFLT1_FLTPWT(x)                    (((x)<<PORT_IOFLT1_FLTPWT_SHIFT)&PORT_IOFLT1_FLTPWT_MASK) /*!< PORT_IOFLT1                             */
#define PORT_IOFLT1_FLTI2C0_MASK                 (0x03UL << PORT_IOFLT1_FLTI2C0_SHIFT)               /*!< PORT_IOFLT1: FLTI2C0 Mask               */
#define PORT_IOFLT1_FLTI2C0_SHIFT                12                                                  /*!< PORT_IOFLT1: FLTI2C0 Position           */
#define PORT_IOFLT1_FLTI2C0(x)                   (((x)<<PORT_IOFLT1_FLTI2C0_SHIFT)&PORT_IOFLT1_FLTI2C0_MASK) /*!< PORT_IOFLT1                             */
#define PORT_IOFLT1_FLTI2C1_MASK                 (0x03UL << PORT_IOFLT1_FLTI2C1_SHIFT)               /*!< PORT_IOFLT1: FLTI2C1 Mask               */
#define PORT_IOFLT1_FLTI2C1_SHIFT                14                                                  /*!< PORT_IOFLT1: FLTI2C1 Position           */
#define PORT_IOFLT1_FLTI2C1(x)                   (((x)<<PORT_IOFLT1_FLTI2C1_SHIFT)&PORT_IOFLT1_FLTI2C1_MASK) /*!< PORT_IOFLT1                             */

/* ------- PORT_PUE0                                ------ */
#define PORT_PUE0_PTAPE_MASK                     (0xFFUL << PORT_PUE0_PTAPE_SHIFT)                   /*!< PORT_PUE0: PTAPE Mask                   */
#define PORT_PUE0_PTAPE_SHIFT                    0                                                   /*!< PORT_PUE0: PTAPE Position               */
#define PORT_PUE0_PTAPE(x)                       (((x)<<PORT_PUE0_PTAPE_SHIFT)&PORT_PUE0_PTAPE_MASK) /*!< PORT_PUE0                               */
#define PORT_PUE0_PTBPE_MASK                     (0xFFUL << PORT_PUE0_PTBPE_SHIFT)                   /*!< PORT_PUE0: PTBPE Mask                   */
#define PORT_PUE0_PTBPE_SHIFT                    8                                                   /*!< PORT_PUE0: PTBPE Position               */
#define PORT_PUE0_PTBPE(x)                       (((x)<<PORT_PUE0_PTBPE_SHIFT)&PORT_PUE0_PTBPE_MASK) /*!< PORT_PUE0                               */
#define PORT_PUE0_PTCPE_MASK                     (0xFFUL << PORT_PUE0_PTCPE_SHIFT)                   /*!< PORT_PUE0: PTCPE Mask                   */
#define PORT_PUE0_PTCPE_SHIFT                    16                                                  /*!< PORT_PUE0: PTCPE Position               */
#define PORT_PUE0_PTCPE(x)                       (((x)<<PORT_PUE0_PTCPE_SHIFT)&PORT_PUE0_PTCPE_MASK) /*!< PORT_PUE0                               */
#define PORT_PUE0_PTDPE_MASK                     (0xFFUL << PORT_PUE0_PTDPE_SHIFT)                   /*!< PORT_PUE0: PTDPE Mask                   */
#define PORT_PUE0_PTDPE_SHIFT                    24                                                  /*!< PORT_PUE0: PTDPE Position               */
#define PORT_PUE0_PTDPE(x)                       (((x)<<PORT_PUE0_PTDPE_SHIFT)&PORT_PUE0_PTDPE_MASK) /*!< PORT_PUE0                               */

/* ------- PORT_PUE1                                ------ */
#define PORT_PUE1_PTEPE_MASK                     (0xFFUL << PORT_PUE1_PTEPE_SHIFT)                   /*!< PORT_PUE1: PTEPE Mask                   */
#define PORT_PUE1_PTEPE_SHIFT                    0                                                   /*!< PORT_PUE1: PTEPE Position               */
#define PORT_PUE1_PTEPE(x)                       (((x)<<PORT_PUE1_PTEPE_SHIFT)&PORT_PUE1_PTEPE_MASK) /*!< PORT_PUE1                               */
#define PORT_PUE1_PTFPE_MASK                     (0xFFUL << PORT_PUE1_PTFPE_SHIFT)                   /*!< PORT_PUE1: PTFPE Mask                   */
#define PORT_PUE1_PTFPE_SHIFT                    8                                                   /*!< PORT_PUE1: PTFPE Position               */
#define PORT_PUE1_PTFPE(x)                       (((x)<<PORT_PUE1_PTFPE_SHIFT)&PORT_PUE1_PTFPE_MASK) /*!< PORT_PUE1                               */
#define PORT_PUE1_PTGPE_MASK                     (0xFFUL << PORT_PUE1_PTGPE_SHIFT)                   /*!< PORT_PUE1: PTGPE Mask                   */
#define PORT_PUE1_PTGPE_SHIFT                    16                                                  /*!< PORT_PUE1: PTGPE Position               */
#define PORT_PUE1_PTGPE(x)                       (((x)<<PORT_PUE1_PTGPE_SHIFT)&PORT_PUE1_PTGPE_MASK) /*!< PORT_PUE1                               */
#define PORT_PUE1_PTHPE_MASK                     (0xFFUL << PORT_PUE1_PTHPE_SHIFT)                   /*!< PORT_PUE1: PTHPE Mask                   */
#define PORT_PUE1_PTHPE_SHIFT                    24                                                  /*!< PORT_PUE1: PTHPE Position               */
#define PORT_PUE1_PTHPE(x)                       (((x)<<PORT_PUE1_PTHPE_SHIFT)&PORT_PUE1_PTHPE_MASK) /*!< PORT_PUE1                               */

/* ------- PORT_PUE2                                ------ */
#define PORT_PUE2_PTIPE_MASK                     (0x7FUL << PORT_PUE2_PTIPE_SHIFT)                   /*!< PORT_PUE2: PTIPE Mask                   */
#define PORT_PUE2_PTIPE_SHIFT                    0                                                   /*!< PORT_PUE2: PTIPE Position               */
#define PORT_PUE2_PTIPE(x)                       (((x)<<PORT_PUE2_PTIPE_SHIFT)&PORT_PUE2_PTIPE_MASK) /*!< PORT_PUE2                               */

/* ------- PORT_HDRVE                               ------ */
#define PORT_HDRVE_PTB4_MASK                     (0x01UL << PORT_HDRVE_PTB4_SHIFT)                   /*!< PORT_HDRVE: PTB4 Mask                   */
#define PORT_HDRVE_PTB4_SHIFT                    0                                                   /*!< PORT_HDRVE: PTB4 Position               */
#define PORT_HDRVE_PTB5_MASK                     (0x01UL << PORT_HDRVE_PTB5_SHIFT)                   /*!< PORT_HDRVE: PTB5 Mask                   */
#define PORT_HDRVE_PTB5_SHIFT                    1                                                   /*!< PORT_HDRVE: PTB5 Position               */
#define PORT_HDRVE_PTD0_MASK                     (0x01UL << PORT_HDRVE_PTD0_SHIFT)                   /*!< PORT_HDRVE: PTD0 Mask                   */
#define PORT_HDRVE_PTD0_SHIFT                    2                                                   /*!< PORT_HDRVE: PTD0 Position               */
#define PORT_HDRVE_PTD1_MASK                     (0x01UL << PORT_HDRVE_PTD1_SHIFT)                   /*!< PORT_HDRVE: PTD1 Mask                   */
#define PORT_HDRVE_PTD1_SHIFT                    3                                                   /*!< PORT_HDRVE: PTD1 Position               */
#define PORT_HDRVE_PTE0_MASK                     (0x01UL << PORT_HDRVE_PTE0_SHIFT)                   /*!< PORT_HDRVE: PTE0 Mask                   */
#define PORT_HDRVE_PTE0_SHIFT                    4                                                   /*!< PORT_HDRVE: PTE0 Position               */
#define PORT_HDRVE_PTE1_MASK                     (0x01UL << PORT_HDRVE_PTE1_SHIFT)                   /*!< PORT_HDRVE: PTE1 Mask                   */
#define PORT_HDRVE_PTE1_SHIFT                    5                                                   /*!< PORT_HDRVE: PTE1 Position               */
#define PORT_HDRVE_PTH0_MASK                     (0x01UL << PORT_HDRVE_PTH0_SHIFT)                   /*!< PORT_HDRVE: PTH0 Mask                   */
#define PORT_HDRVE_PTH0_SHIFT                    6                                                   /*!< PORT_HDRVE: PTH0 Position               */
#define PORT_HDRVE_PTH1_MASK                     (0x01UL << PORT_HDRVE_PTH1_SHIFT)                   /*!< PORT_HDRVE: PTH1 Mask                   */
#define PORT_HDRVE_PTH1_SHIFT                    7                                                   /*!< PORT_HDRVE: PTH1 Position               */

/* -------------------------------------------------------------------------------- */
/* -----------     'PORT' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define PORT_IOFLT0                    (PORT->IOFLT0)
#define PORT_IOFLT1                    (PORT->IOFLT1)
#define PORT_PUE0                      (PORT->PUE0)
#define PORT_PUE1                      (PORT->PUE1)
#define PORT_PUE2                      (PORT->PUE2)
#define PORT_HDRVE                     (PORT->HDRVE)

/* ================================================================================ */
/* ================           PWT (file:PWT_MKE)                   ================ */
/* ================================================================================ */

/**
 * @brief Pulse Width Timer
 */
typedef struct {                                /*!<       PWT Structure                                                */
   __IO uint32_t  R1;                           /*!< 0000: Pulse Width Timer Register 1                                 */
   __IO uint32_t  R2;                           /*!< 0004: Pulse Width Timer Register 2                                 */
} PWT_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'PWT' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- PWT_R1                                   ------ */
#define PWT_R1_PWTOV_MASK                        (0x01UL << PWT_R1_PWTOV_SHIFT)                      /*!< PWT_R1: PWTOV Mask                      */
#define PWT_R1_PWTOV_SHIFT                       0                                                   /*!< PWT_R1: PWTOV Position                  */
#define PWT_R1_PWTRDY_MASK                       (0x01UL << PWT_R1_PWTRDY_SHIFT)                     /*!< PWT_R1: PWTRDY Mask                     */
#define PWT_R1_PWTRDY_SHIFT                      1                                                   /*!< PWT_R1: PWTRDY Position                 */
#define PWT_R1_PWTSR_MASK                        (0x01UL << PWT_R1_PWTSR_SHIFT)                      /*!< PWT_R1: PWTSR Mask                      */
#define PWT_R1_PWTSR_SHIFT                       3                                                   /*!< PWT_R1: PWTSR Position                  */
#define PWT_R1_POVIE_MASK                        (0x01UL << PWT_R1_POVIE_SHIFT)                      /*!< PWT_R1: POVIE Mask                      */
#define PWT_R1_POVIE_SHIFT                       4                                                   /*!< PWT_R1: POVIE Position                  */
#define PWT_R1_PRDYIE_MASK                       (0x01UL << PWT_R1_PRDYIE_SHIFT)                     /*!< PWT_R1: PRDYIE Mask                     */
#define PWT_R1_PRDYIE_SHIFT                      5                                                   /*!< PWT_R1: PRDYIE Position                 */
#define PWT_R1_PWTIE_MASK                        (0x01UL << PWT_R1_PWTIE_SHIFT)                      /*!< PWT_R1: PWTIE Mask                      */
#define PWT_R1_PWTIE_SHIFT                       6                                                   /*!< PWT_R1: PWTIE Position                  */
#define PWT_R1_PWTEN_MASK                        (0x01UL << PWT_R1_PWTEN_SHIFT)                      /*!< PWT_R1: PWTEN Mask                      */
#define PWT_R1_PWTEN_SHIFT                       7                                                   /*!< PWT_R1: PWTEN Position                  */
#define PWT_R1_PRE_MASK                          (0x07UL << PWT_R1_PRE_SHIFT)                        /*!< PWT_R1: PRE Mask                        */
#define PWT_R1_PRE_SHIFT                         8                                                   /*!< PWT_R1: PRE Position                    */
#define PWT_R1_PRE(x)                            (((x)<<PWT_R1_PRE_SHIFT)&PWT_R1_PRE_MASK)           /*!< PWT_R1                                  */
#define PWT_R1_EDGE_MASK                         (0x03UL << PWT_R1_EDGE_SHIFT)                       /*!< PWT_R1: EDGE Mask                       */
#define PWT_R1_EDGE_SHIFT                        11                                                  /*!< PWT_R1: EDGE Position                   */
#define PWT_R1_EDGE(x)                           (((x)<<PWT_R1_EDGE_SHIFT)&PWT_R1_EDGE_MASK)         /*!< PWT_R1                                  */
#define PWT_R1_PINSEL_MASK                       (0x03UL << PWT_R1_PINSEL_SHIFT)                     /*!< PWT_R1: PINSEL Mask                     */
#define PWT_R1_PINSEL_SHIFT                      13                                                  /*!< PWT_R1: PINSEL Position                 */
#define PWT_R1_PINSEL(x)                         (((x)<<PWT_R1_PINSEL_SHIFT)&PWT_R1_PINSEL_MASK)     /*!< PWT_R1                                  */
#define PWT_R1_PCLKS_MASK                        (0x01UL << PWT_R1_PCLKS_SHIFT)                      /*!< PWT_R1: PCLKS Mask                      */
#define PWT_R1_PCLKS_SHIFT                       15                                                  /*!< PWT_R1: PCLKS Position                  */
#define PWT_R1_PPW_MASK                          (0xFFFFUL << PWT_R1_PPW_SHIFT)                      /*!< PWT_R1: PPW Mask                        */
#define PWT_R1_PPW_SHIFT                         16                                                  /*!< PWT_R1: PPW Position                    */
#define PWT_R1_PPW(x)                            (((x)<<PWT_R1_PPW_SHIFT)&PWT_R1_PPW_MASK)           /*!< PWT_R1                                  */

/* ------- PWT_R2                                   ------ */

/* -------------------------------------------------------------------------------- */
/* -----------     'PWT' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define PWT_R1                         (PWT->R1)
#define PWT_R2                         (PWT->R2)

/* ================================================================================ */
/* ================           RTC (file:RTC_MKE)                   ================ */
/* ================================================================================ */

/**
 * @brief Real-time counter
 */
typedef struct {                                /*!<       RTC Structure                                                */
   __IO uint32_t  SC;                           /*!< 0000: Status and Control Register                                  */
   __IO uint32_t  MOD;                          /*!< 0004: Modulo Register: Contains the modulo value used to reset the count to 0x0000 upon a compare match and set SC[RTIF] status field */
   __I  uint32_t  CNT;                          /*!< 0008: Counter Register: Reset or writing different values to SC[RTCLKS] and SC[RTCPS] clear the count to 0x0000 */
} RTC_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'RTC' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- RTC_SC                                   ------ */
#define RTC_SC_RTCO_MASK                         (0x01UL << RTC_SC_RTCO_SHIFT)                       /*!< RTC_SC: RTCO Mask                       */
#define RTC_SC_RTCO_SHIFT                        4                                                   /*!< RTC_SC: RTCO Position                   */
#define RTC_SC_RTIE_MASK                         (0x01UL << RTC_SC_RTIE_SHIFT)                       /*!< RTC_SC: RTIE Mask                       */
#define RTC_SC_RTIE_SHIFT                        6                                                   /*!< RTC_SC: RTIE Position                   */
#define RTC_SC_RTIF_MASK                         (0x01UL << RTC_SC_RTIF_SHIFT)                       /*!< RTC_SC: RTIF Mask                       */
#define RTC_SC_RTIF_SHIFT                        7                                                   /*!< RTC_SC: RTIF Position                   */
#define RTC_SC_RTCPS_MASK                        (0x07UL << RTC_SC_RTCPS_SHIFT)                      /*!< RTC_SC: RTCPS Mask                      */
#define RTC_SC_RTCPS_SHIFT                       8                                                   /*!< RTC_SC: RTCPS Position                  */
#define RTC_SC_RTCPS(x)                          (((x)<<RTC_SC_RTCPS_SHIFT)&RTC_SC_RTCPS_MASK)       /*!< RTC_SC                                  */
#define RTC_SC_RTCLKS_MASK                       (0x03UL << RTC_SC_RTCLKS_SHIFT)                     /*!< RTC_SC: RTCLKS Mask                     */
#define RTC_SC_RTCLKS_SHIFT                      14                                                  /*!< RTC_SC: RTCLKS Position                 */
#define RTC_SC_RTCLKS(x)                         (((x)<<RTC_SC_RTCLKS_SHIFT)&RTC_SC_RTCLKS_MASK)     /*!< RTC_SC                                  */

/* ------- RTC_MOD                                  ------ */
#define RTC_MOD_MOD_MASK                         (0xFFFFUL << RTC_MOD_MOD_SHIFT)                     /*!< RTC_MOD: MOD Mask                       */
#define RTC_MOD_MOD_SHIFT                        0                                                   /*!< RTC_MOD: MOD Position                   */
#define RTC_MOD_MOD(x)                           (((x)<<RTC_MOD_MOD_SHIFT)&RTC_MOD_MOD_MASK)         /*!< RTC_MOD                                 */

/* ------- RTC_CNT                                  ------ */
#define RTC_CNT_CNT_MASK                         (0xFFFFUL << RTC_CNT_CNT_SHIFT)                     /*!< RTC_CNT: CNT Mask                       */
#define RTC_CNT_CNT_SHIFT                        0                                                   /*!< RTC_CNT: CNT Position                   */
#define RTC_CNT_CNT(x)                           (((x)<<RTC_CNT_CNT_SHIFT)&RTC_CNT_CNT_MASK)         /*!< RTC_CNT                                 */

/* -------------------------------------------------------------------------------- */
/* -----------     'RTC' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define RTC_SC                         (RTC->SC)
#define RTC_MOD                        (RTC->MOD)
#define RTC_CNT                        (RTC->CNT)

/* ================================================================================ */
/* ================           SIM (file:SIM_MKE04Z4)               ================ */
/* ================================================================================ */

/**
 * @brief System Integration Module
 */
typedef struct {                                /*!<       SIM Structure                                                */
   __IO uint32_t  SRSID;                        /*!< 0000: System Reset Status and ID Register                          */
   __IO uint32_t  SOPT0;                        /*!< 0004: System Options Register 1                                    */
   __IO uint32_t  SOPT1;                        /*!< 0008: System Options Register 1                                    */
   __IO uint32_t  PINSEL0;                      /*!< 000C: Pin Selection Register 0                                     */
   __IO uint32_t  PINSEL1;                      /*!< 0010: Pin Selection Register 1                                     */
   __IO uint32_t  SCGC;                         /*!< 0014: System Clock Gating Control Register                         */
   __IO uint32_t  UUIDL;                        /*!< 0018: Universally Unique Identifier Low Register                   */
   __IO uint32_t  UUIDML;                       /*!< 001C: Universally Unique Identifier Middle Low Register            */
   __IO uint32_t  UUIDMH;                       /*!< 0020: Universally Unique Identifier Middle High Register           */
   __IO uint32_t  CLKDIV;                       /*!< 0024: BUS Clock Divider Register                                   */
} SIM_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'SIM' Position & Mask macros                         ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- SIM_SRSID                                ------ */
#define SIM_SRSID_LVD_MASK                       (0x01UL << SIM_SRSID_LVD_SHIFT)                     /*!< SIM_SRSID: LVD Mask                     */
#define SIM_SRSID_LVD_SHIFT                      1                                                   /*!< SIM_SRSID: LVD Position                 */
#define SIM_SRSID_LOC_MASK                       (0x01UL << SIM_SRSID_LOC_SHIFT)                     /*!< SIM_SRSID: LOC Mask                     */
#define SIM_SRSID_LOC_SHIFT                      2                                                   /*!< SIM_SRSID: LOC Position                 */
#define SIM_SRSID_WDOG_MASK                      (0x01UL << SIM_SRSID_WDOG_SHIFT)                    /*!< SIM_SRSID: WDOG Mask                    */
#define SIM_SRSID_WDOG_SHIFT                     5                                                   /*!< SIM_SRSID: WDOG Position                */
#define SIM_SRSID_PIN_MASK                       (0x01UL << SIM_SRSID_PIN_SHIFT)                     /*!< SIM_SRSID: PIN Mask                     */
#define SIM_SRSID_PIN_SHIFT                      6                                                   /*!< SIM_SRSID: PIN Position                 */
#define SIM_SRSID_POR_MASK                       (0x01UL << SIM_SRSID_POR_SHIFT)                     /*!< SIM_SRSID: POR Mask                     */
#define SIM_SRSID_POR_SHIFT                      7                                                   /*!< SIM_SRSID: POR Position                 */
#define SIM_SRSID_LOCKUP_MASK                    (0x01UL << SIM_SRSID_LOCKUP_SHIFT)                  /*!< SIM_SRSID: LOCKUP Mask                  */
#define SIM_SRSID_LOCKUP_SHIFT                   9                                                   /*!< SIM_SRSID: LOCKUP Position              */
#define SIM_SRSID_SW_MASK                        (0x01UL << SIM_SRSID_SW_SHIFT)                      /*!< SIM_SRSID: SW Mask                      */
#define SIM_SRSID_SW_SHIFT                       10                                                  /*!< SIM_SRSID: SW Position                  */
#define SIM_SRSID_MDMAP_MASK                     (0x01UL << SIM_SRSID_MDMAP_SHIFT)                   /*!< SIM_SRSID: MDMAP Mask                   */
#define SIM_SRSID_MDMAP_SHIFT                    11                                                  /*!< SIM_SRSID: MDMAP Position               */
#define SIM_SRSID_SACKERR_MASK                   (0x01UL << SIM_SRSID_SACKERR_SHIFT)                 /*!< SIM_SRSID: SACKERR Mask                 */
#define SIM_SRSID_SACKERR_SHIFT                  13                                                  /*!< SIM_SRSID: SACKERR Position             */
#define SIM_SRSID_PINID_MASK                     (0x0FUL << SIM_SRSID_PINID_SHIFT)                   /*!< SIM_SRSID: PINID Mask                   */
#define SIM_SRSID_PINID_SHIFT                    16                                                  /*!< SIM_SRSID: PINID Position               */
#define SIM_SRSID_PINID(x)                       (((x)<<SIM_SRSID_PINID_SHIFT)&SIM_SRSID_PINID_MASK) /*!< SIM_SRSID                               */
#define SIM_SRSID_REVID_MASK                     (0x0FUL << SIM_SRSID_REVID_SHIFT)                   /*!< SIM_SRSID: REVID Mask                   */
#define SIM_SRSID_REVID_SHIFT                    20                                                  /*!< SIM_SRSID: REVID Position               */
#define SIM_SRSID_REVID(x)                       (((x)<<SIM_SRSID_REVID_SHIFT)&SIM_SRSID_REVID_MASK) /*!< SIM_SRSID                               */
#define SIM_SRSID_SUBFAMID_MASK                  (0x0FUL << SIM_SRSID_SUBFAMID_SHIFT)                /*!< SIM_SRSID: SUBFAMID Mask                */
#define SIM_SRSID_SUBFAMID_SHIFT                 24                                                  /*!< SIM_SRSID: SUBFAMID Position            */
#define SIM_SRSID_SUBFAMID(x)                    (((x)<<SIM_SRSID_SUBFAMID_SHIFT)&SIM_SRSID_SUBFAMID_MASK) /*!< SIM_SRSID                               */
#define SIM_SRSID_FAMID_MASK                     (0x0FUL << SIM_SRSID_FAMID_SHIFT)                   /*!< SIM_SRSID: FAMID Mask                   */
#define SIM_SRSID_FAMID_SHIFT                    28                                                  /*!< SIM_SRSID: FAMID Position               */
#define SIM_SRSID_FAMID(x)                       (((x)<<SIM_SRSID_FAMID_SHIFT)&SIM_SRSID_FAMID_MASK) /*!< SIM_SRSID                               */

/* ------- SIM_SOPT0                                ------ */
#define SIM_SOPT0_NMIE_MASK                      (0x01UL << SIM_SOPT0_NMIE_SHIFT)                    /*!< SIM_SOPT0: NMIE Mask                    */
#define SIM_SOPT0_NMIE_SHIFT                     1                                                   /*!< SIM_SOPT0: NMIE Position                */
#define SIM_SOPT0_RSTPE_MASK                     (0x01UL << SIM_SOPT0_RSTPE_SHIFT)                   /*!< SIM_SOPT0: RSTPE Mask                   */
#define SIM_SOPT0_RSTPE_SHIFT                    2                                                   /*!< SIM_SOPT0: RSTPE Position               */
#define SIM_SOPT0_SWDE_MASK                      (0x01UL << SIM_SOPT0_SWDE_SHIFT)                    /*!< SIM_SOPT0: SWDE Mask                    */
#define SIM_SOPT0_SWDE_SHIFT                     3                                                   /*!< SIM_SOPT0: SWDE Position                */
#define SIM_SOPT0_ACTRG_MASK                     (0x01UL << SIM_SOPT0_ACTRG_SHIFT)                   /*!< SIM_SOPT0: ACTRG Mask                   */
#define SIM_SOPT0_ACTRG_SHIFT                    5                                                   /*!< SIM_SOPT0: ACTRG Position               */
#define SIM_SOPT0_RXDFE_MASK                     (0x03UL << SIM_SOPT0_RXDFE_SHIFT)                   /*!< SIM_SOPT0: RXDFE Mask                   */
#define SIM_SOPT0_RXDFE_SHIFT                    8                                                   /*!< SIM_SOPT0: RXDFE Position               */
#define SIM_SOPT0_RXDFE(x)                       (((x)<<SIM_SOPT0_RXDFE_SHIFT)&SIM_SOPT0_RXDFE_MASK) /*!< SIM_SOPT0                               */
#define SIM_SOPT0_RTCC_MASK                      (0x01UL << SIM_SOPT0_RTCC_SHIFT)                    /*!< SIM_SOPT0: RTCC Mask                    */
#define SIM_SOPT0_RTCC_SHIFT                     10                                                  /*!< SIM_SOPT0: RTCC Position                */
#define SIM_SOPT0_ACIC_MASK                      (0x01UL << SIM_SOPT0_ACIC_SHIFT)                    /*!< SIM_SOPT0: ACIC Mask                    */
#define SIM_SOPT0_ACIC_SHIFT                     11                                                  /*!< SIM_SOPT0: ACIC Position                */
#define SIM_SOPT0_RXDCE_MASK                     (0x01UL << SIM_SOPT0_RXDCE_SHIFT)                   /*!< SIM_SOPT0: RXDCE Mask                   */
#define SIM_SOPT0_RXDCE_SHIFT                    12                                                  /*!< SIM_SOPT0: RXDCE Position               */
#define SIM_SOPT0_FTMSYNC_MASK                   (0x01UL << SIM_SOPT0_FTMSYNC_SHIFT)                 /*!< SIM_SOPT0: FTMSYNC Mask                 */
#define SIM_SOPT0_FTMSYNC_SHIFT                  14                                                  /*!< SIM_SOPT0: FTMSYNC Position             */
#define SIM_SOPT0_TXDME_MASK                     (0x01UL << SIM_SOPT0_TXDME_SHIFT)                   /*!< SIM_SOPT0: TXDME Mask                   */
#define SIM_SOPT0_TXDME_SHIFT                    15                                                  /*!< SIM_SOPT0: TXDME Position               */
#define SIM_SOPT0_BUSREF_MASK                    (0x07UL << SIM_SOPT0_BUSREF_SHIFT)                  /*!< SIM_SOPT0: BUSREF Mask                  */
#define SIM_SOPT0_BUSREF_SHIFT                   16                                                  /*!< SIM_SOPT0: BUSREF Position              */
#define SIM_SOPT0_BUSREF(x)                      (((x)<<SIM_SOPT0_BUSREF_SHIFT)&SIM_SOPT0_BUSREF_MASK) /*!< SIM_SOPT0                               */
#define SIM_SOPT0_CLKOE_MASK                     (0x01UL << SIM_SOPT0_CLKOE_SHIFT)                   /*!< SIM_SOPT0: CLKOE Mask                   */
#define SIM_SOPT0_CLKOE_SHIFT                    19                                                  /*!< SIM_SOPT0: CLKOE Position               */
#define SIM_SOPT0_ADHWT_MASK                     (0x07UL << SIM_SOPT0_ADHWT_SHIFT)                   /*!< SIM_SOPT0: ADHWT Mask                   */
#define SIM_SOPT0_ADHWT_SHIFT                    20                                                  /*!< SIM_SOPT0: ADHWT Position               */
#define SIM_SOPT0_ADHWT(x)                       (((x)<<SIM_SOPT0_ADHWT_SHIFT)&SIM_SOPT0_ADHWT_MASK) /*!< SIM_SOPT0                               */
#define SIM_SOPT0_DLYACT_MASK                    (0x01UL << SIM_SOPT0_DLYACT_SHIFT)                  /*!< SIM_SOPT0: DLYACT Mask                  */
#define SIM_SOPT0_DLYACT_SHIFT                   23                                                  /*!< SIM_SOPT0: DLYACT Position              */
#define SIM_SOPT0_DELAY_MASK                     (0xFFUL << SIM_SOPT0_DELAY_SHIFT)                   /*!< SIM_SOPT0: DELAY Mask                   */
#define SIM_SOPT0_DELAY_SHIFT                    24                                                  /*!< SIM_SOPT0: DELAY Position               */
#define SIM_SOPT0_DELAY(x)                       (((x)<<SIM_SOPT0_DELAY_SHIFT)&SIM_SOPT0_DELAY_MASK) /*!< SIM_SOPT0                               */

/* ------- SIM_SOPT1                                ------ */
#define SIM_SOPT1_I2C04WEN_MASK                  (0x01UL << SIM_SOPT1_I2C04WEN_SHIFT)                /*!< SIM_SOPT1: I2C04WEN Mask                */
#define SIM_SOPT1_I2C04WEN_SHIFT                 0                                                   /*!< SIM_SOPT1: I2C04WEN Position            */
#define SIM_SOPT1_I2C0OINV_MASK                  (0x01UL << SIM_SOPT1_I2C0OINV_SHIFT)                /*!< SIM_SOPT1: I2C0OINV Mask                */
#define SIM_SOPT1_I2C0OINV_SHIFT                 1                                                   /*!< SIM_SOPT1: I2C0OINV Position            */
#define SIM_SOPT1_ACPWTS_MASK                    (0x01UL << SIM_SOPT1_ACPWTS_SHIFT)                  /*!< SIM_SOPT1: ACPWTS Mask                  */
#define SIM_SOPT1_ACPWTS_SHIFT                   3                                                   /*!< SIM_SOPT1: ACPWTS Position              */
#define SIM_SOPT1_UARTPWTS_MASK                  (0x03UL << SIM_SOPT1_UARTPWTS_SHIFT)                /*!< SIM_SOPT1: UARTPWTS Mask                */
#define SIM_SOPT1_UARTPWTS_SHIFT                 4                                                   /*!< SIM_SOPT1: UARTPWTS Position            */
#define SIM_SOPT1_UARTPWTS(x)                    (((x)<<SIM_SOPT1_UARTPWTS_SHIFT)&SIM_SOPT1_UARTPWTS_MASK) /*!< SIM_SOPT1                               */

/* ------- SIM_PINSEL0                              ------ */
#define SIM_PINSEL0_IRQPS_MASK                   (0x07UL << SIM_PINSEL0_IRQPS_SHIFT)                 /*!< SIM_PINSEL0: IRQPS Mask                 */
#define SIM_PINSEL0_IRQPS_SHIFT                  0                                                   /*!< SIM_PINSEL0: IRQPS Position             */
#define SIM_PINSEL0_IRQPS(x)                     (((x)<<SIM_PINSEL0_IRQPS_SHIFT)&SIM_PINSEL0_IRQPS_MASK) /*!< SIM_PINSEL0                             */
#define SIM_PINSEL0_RTCPS_MASK                   (0x01UL << SIM_PINSEL0_RTCPS_SHIFT)                 /*!< SIM_PINSEL0: RTCPS Mask                 */
#define SIM_PINSEL0_RTCPS_SHIFT                  4                                                   /*!< SIM_PINSEL0: RTCPS Position             */
#define SIM_PINSEL0_I2C0PS_MASK                  (0x01UL << SIM_PINSEL0_I2C0PS_SHIFT)                /*!< SIM_PINSEL0: I2C0PS Mask                */
#define SIM_PINSEL0_I2C0PS_SHIFT                 5                                                   /*!< SIM_PINSEL0: I2C0PS Position            */
#define SIM_PINSEL0_SPI0PS_MASK                  (0x01UL << SIM_PINSEL0_SPI0PS_SHIFT)                /*!< SIM_PINSEL0: SPI0PS Mask                */
#define SIM_PINSEL0_SPI0PS_SHIFT                 6                                                   /*!< SIM_PINSEL0: SPI0PS Position            */
#define SIM_PINSEL0_UART0PS_MASK                 (0x01UL << SIM_PINSEL0_UART0PS_SHIFT)               /*!< SIM_PINSEL0: UART0PS Mask               */
#define SIM_PINSEL0_UART0PS_SHIFT                7                                                   /*!< SIM_PINSEL0: UART0PS Position           */
#define SIM_PINSEL0_FTM0PS0_MASK                 (0x01UL << SIM_PINSEL0_FTM0PS0_SHIFT)               /*!< SIM_PINSEL0: FTM0PS0 Mask               */
#define SIM_PINSEL0_FTM0PS0_SHIFT                8                                                   /*!< SIM_PINSEL0: FTM0PS0 Position           */
#define SIM_PINSEL0_FTM0PS1_MASK                 (0x01UL << SIM_PINSEL0_FTM0PS1_SHIFT)               /*!< SIM_PINSEL0: FTM0PS1 Mask               */
#define SIM_PINSEL0_FTM0PS1_SHIFT                9                                                   /*!< SIM_PINSEL0: FTM0PS1 Position           */
#define SIM_PINSEL0_FTM1PS0_MASK                 (0x01UL << SIM_PINSEL0_FTM1PS0_SHIFT)               /*!< SIM_PINSEL0: FTM1PS0 Mask               */
#define SIM_PINSEL0_FTM1PS0_SHIFT                10                                                  /*!< SIM_PINSEL0: FTM1PS0 Position           */
#define SIM_PINSEL0_FTM1PS1_MASK                 (0x01UL << SIM_PINSEL0_FTM1PS1_SHIFT)               /*!< SIM_PINSEL0: FTM1PS1 Mask               */
#define SIM_PINSEL0_FTM1PS1_SHIFT                11                                                  /*!< SIM_PINSEL0: FTM1PS1 Position           */
#define SIM_PINSEL0_FTM0CLKPS_MASK               (0x03UL << SIM_PINSEL0_FTM0CLKPS_SHIFT)             /*!< SIM_PINSEL0: FTM0CLKPS Mask             */
#define SIM_PINSEL0_FTM0CLKPS_SHIFT              24                                                  /*!< SIM_PINSEL0: FTM0CLKPS Position         */
#define SIM_PINSEL0_FTM0CLKPS(x)                 (((x)<<SIM_PINSEL0_FTM0CLKPS_SHIFT)&SIM_PINSEL0_FTM0CLKPS_MASK) /*!< SIM_PINSEL0                             */
#define SIM_PINSEL0_FTM1CLKPS_MASK               (0x03UL << SIM_PINSEL0_FTM1CLKPS_SHIFT)             /*!< SIM_PINSEL0: FTM1CLKPS Mask             */
#define SIM_PINSEL0_FTM1CLKPS_SHIFT              26                                                  /*!< SIM_PINSEL0: FTM1CLKPS Position         */
#define SIM_PINSEL0_FTM1CLKPS(x)                 (((x)<<SIM_PINSEL0_FTM1CLKPS_SHIFT)&SIM_PINSEL0_FTM1CLKPS_MASK) /*!< SIM_PINSEL0                             */
#define SIM_PINSEL0_FTM2CLKPS_MASK               (0x03UL << SIM_PINSEL0_FTM2CLKPS_SHIFT)             /*!< SIM_PINSEL0: FTM2CLKPS Mask             */
#define SIM_PINSEL0_FTM2CLKPS_SHIFT              28                                                  /*!< SIM_PINSEL0: FTM2CLKPS Position         */
#define SIM_PINSEL0_FTM2CLKPS(x)                 (((x)<<SIM_PINSEL0_FTM2CLKPS_SHIFT)&SIM_PINSEL0_FTM2CLKPS_MASK) /*!< SIM_PINSEL0                             */
#define SIM_PINSEL0_PWTCLKPS_MASK                (0x03UL << SIM_PINSEL0_PWTCLKPS_SHIFT)              /*!< SIM_PINSEL0: PWTCLKPS Mask              */
#define SIM_PINSEL0_PWTCLKPS_SHIFT               30                                                  /*!< SIM_PINSEL0: PWTCLKPS Position          */
#define SIM_PINSEL0_PWTCLKPS(x)                  (((x)<<SIM_PINSEL0_PWTCLKPS_SHIFT)&SIM_PINSEL0_PWTCLKPS_MASK) /*!< SIM_PINSEL0                             */

/* ------- SIM_PINSEL1                              ------ */
#define SIM_PINSEL1_FTM2PS0_MASK                 (0x03UL << SIM_PINSEL1_FTM2PS0_SHIFT)               /*!< SIM_PINSEL1: FTM2PS0 Mask               */
#define SIM_PINSEL1_FTM2PS0_SHIFT                0                                                   /*!< SIM_PINSEL1: FTM2PS0 Position           */
#define SIM_PINSEL1_FTM2PS0(x)                   (((x)<<SIM_PINSEL1_FTM2PS0_SHIFT)&SIM_PINSEL1_FTM2PS0_MASK) /*!< SIM_PINSEL1                             */
#define SIM_PINSEL1_FTM2PS1_MASK                 (0x03UL << SIM_PINSEL1_FTM2PS1_SHIFT)               /*!< SIM_PINSEL1: FTM2PS1 Mask               */
#define SIM_PINSEL1_FTM2PS1_SHIFT                2                                                   /*!< SIM_PINSEL1: FTM2PS1 Position           */
#define SIM_PINSEL1_FTM2PS1(x)                   (((x)<<SIM_PINSEL1_FTM2PS1_SHIFT)&SIM_PINSEL1_FTM2PS1_MASK) /*!< SIM_PINSEL1                             */
#define SIM_PINSEL1_FTM2PS2_MASK                 (0x03UL << SIM_PINSEL1_FTM2PS2_SHIFT)               /*!< SIM_PINSEL1: FTM2PS2 Mask               */
#define SIM_PINSEL1_FTM2PS2_SHIFT                4                                                   /*!< SIM_PINSEL1: FTM2PS2 Position           */
#define SIM_PINSEL1_FTM2PS2(x)                   (((x)<<SIM_PINSEL1_FTM2PS2_SHIFT)&SIM_PINSEL1_FTM2PS2_MASK) /*!< SIM_PINSEL1                             */
#define SIM_PINSEL1_FTM2PS3_MASK                 (0x03UL << SIM_PINSEL1_FTM2PS3_SHIFT)               /*!< SIM_PINSEL1: FTM2PS3 Mask               */
#define SIM_PINSEL1_FTM2PS3_SHIFT                6                                                   /*!< SIM_PINSEL1: FTM2PS3 Position           */
#define SIM_PINSEL1_FTM2PS3(x)                   (((x)<<SIM_PINSEL1_FTM2PS3_SHIFT)&SIM_PINSEL1_FTM2PS3_MASK) /*!< SIM_PINSEL1                             */
#define SIM_PINSEL1_FTM2PS4_MASK                 (0x01UL << SIM_PINSEL1_FTM2PS4_SHIFT)               /*!< SIM_PINSEL1: FTM2PS4 Mask               */
#define SIM_PINSEL1_FTM2PS4_SHIFT                8                                                   /*!< SIM_PINSEL1: FTM2PS4 Position           */
#define SIM_PINSEL1_FTM2PS5_MASK                 (0x01UL << SIM_PINSEL1_FTM2PS5_SHIFT)               /*!< SIM_PINSEL1: FTM2PS5 Mask               */
#define SIM_PINSEL1_FTM2PS5_SHIFT                9                                                   /*!< SIM_PINSEL1: FTM2PS5 Position           */
#define SIM_PINSEL1_I2C1PS_MASK                  (0x01UL << SIM_PINSEL1_I2C1PS_SHIFT)                /*!< SIM_PINSEL1: I2C1PS Mask                */
#define SIM_PINSEL1_I2C1PS_SHIFT                 10                                                  /*!< SIM_PINSEL1: I2C1PS Position            */
#define SIM_PINSEL1_SPI1PS_MASK                  (0x01UL << SIM_PINSEL1_SPI1PS_SHIFT)                /*!< SIM_PINSEL1: SPI1PS Mask                */
#define SIM_PINSEL1_SPI1PS_SHIFT                 11                                                  /*!< SIM_PINSEL1: SPI1PS Position            */
#define SIM_PINSEL1_UART1PS_MASK                 (0x01UL << SIM_PINSEL1_UART1PS_SHIFT)               /*!< SIM_PINSEL1: UART1PS Mask               */
#define SIM_PINSEL1_UART1PS_SHIFT                12                                                  /*!< SIM_PINSEL1: UART1PS Position           */
#define SIM_PINSEL1_UART2PS_MASK                 (0x01UL << SIM_PINSEL1_UART2PS_SHIFT)               /*!< SIM_PINSEL1: UART2PS Mask               */
#define SIM_PINSEL1_UART2PS_SHIFT                13                                                  /*!< SIM_PINSEL1: UART2PS Position           */
#define SIM_PINSEL1_PWTIN0PS_MASK                (0x01UL << SIM_PINSEL1_PWTIN0PS_SHIFT)              /*!< SIM_PINSEL1: PWTIN0PS Mask              */
#define SIM_PINSEL1_PWTIN0PS_SHIFT               14                                                  /*!< SIM_PINSEL1: PWTIN0PS Position          */
#define SIM_PINSEL1_PWTIN1PS_MASK                (0x01UL << SIM_PINSEL1_PWTIN1PS_SHIFT)              /*!< SIM_PINSEL1: PWTIN1PS Mask              */
#define SIM_PINSEL1_PWTIN1PS_SHIFT               15                                                  /*!< SIM_PINSEL1: PWTIN1PS Position          */

/* ------- SIM_SCGC                                 ------ */
#define SIM_SCGC_RTC_MASK                        (0x01UL << SIM_SCGC_RTC_SHIFT)                      /*!< SIM_SCGC: RTC Mask                      */
#define SIM_SCGC_RTC_SHIFT                       0                                                   /*!< SIM_SCGC: RTC Position                  */
#define SIM_SCGC_PIT_MASK                        (0x01UL << SIM_SCGC_PIT_SHIFT)                      /*!< SIM_SCGC: PIT Mask                      */
#define SIM_SCGC_PIT_SHIFT                       1                                                   /*!< SIM_SCGC: PIT Position                  */
#define SIM_SCGC_PWT_MASK                        (0x01UL << SIM_SCGC_PWT_SHIFT)                      /*!< SIM_SCGC: PWT Mask                      */
#define SIM_SCGC_PWT_SHIFT                       4                                                   /*!< SIM_SCGC: PWT Position                  */
#define SIM_SCGC_FTM0_MASK                       (0x01UL << SIM_SCGC_FTM0_SHIFT)                     /*!< SIM_SCGC: FTM0 Mask                     */
#define SIM_SCGC_FTM0_SHIFT                      5                                                   /*!< SIM_SCGC: FTM0 Position                 */
#define SIM_SCGC_FTM1_MASK                       (0x01UL << SIM_SCGC_FTM1_SHIFT)                     /*!< SIM_SCGC: FTM1 Mask                     */
#define SIM_SCGC_FTM1_SHIFT                      6                                                   /*!< SIM_SCGC: FTM1 Position                 */
#define SIM_SCGC_FTM2_MASK                       (0x01UL << SIM_SCGC_FTM2_SHIFT)                     /*!< SIM_SCGC: FTM2 Mask                     */
#define SIM_SCGC_FTM2_SHIFT                      7                                                   /*!< SIM_SCGC: FTM2 Position                 */
#define SIM_SCGC_CRC_MASK                        (0x01UL << SIM_SCGC_CRC_SHIFT)                      /*!< SIM_SCGC: CRC Mask                      */
#define SIM_SCGC_CRC_SHIFT                       10                                                  /*!< SIM_SCGC: CRC Position                  */
#define SIM_SCGC_FLASH_MASK                      (0x01UL << SIM_SCGC_FLASH_SHIFT)                    /*!< SIM_SCGC: FLASH Mask                    */
#define SIM_SCGC_FLASH_SHIFT                     12                                                  /*!< SIM_SCGC: FLASH Position                */
#define SIM_SCGC_SWD_MASK                        (0x01UL << SIM_SCGC_SWD_SHIFT)                      /*!< SIM_SCGC: SWD Mask                      */
#define SIM_SCGC_SWD_SHIFT                       13                                                  /*!< SIM_SCGC: SWD Position                  */
#define SIM_SCGC_I2C0_MASK                       (0x01UL << SIM_SCGC_I2C0_SHIFT)                     /*!< SIM_SCGC: I2C0 Mask                     */
#define SIM_SCGC_I2C0_SHIFT                      16                                                  /*!< SIM_SCGC: I2C0 Position                 */
#define SIM_SCGC_I2C1_MASK                       (0x01UL << SIM_SCGC_I2C1_SHIFT)                     /*!< SIM_SCGC: I2C1 Mask                     */
#define SIM_SCGC_I2C1_SHIFT                      17                                                  /*!< SIM_SCGC: I2C1 Position                 */
#define SIM_SCGC_SPI0_MASK                       (0x01UL << SIM_SCGC_SPI0_SHIFT)                     /*!< SIM_SCGC: SPI0 Mask                     */
#define SIM_SCGC_SPI0_SHIFT                      18                                                  /*!< SIM_SCGC: SPI0 Position                 */
#define SIM_SCGC_SPI1_MASK                       (0x01UL << SIM_SCGC_SPI1_SHIFT)                     /*!< SIM_SCGC: SPI1 Mask                     */
#define SIM_SCGC_SPI1_SHIFT                      19                                                  /*!< SIM_SCGC: SPI1 Position                 */
#define SIM_SCGC_UART0_MASK                      (0x01UL << SIM_SCGC_UART0_SHIFT)                    /*!< SIM_SCGC: UART0 Mask                    */
#define SIM_SCGC_UART0_SHIFT                     20                                                  /*!< SIM_SCGC: UART0 Position                */
#define SIM_SCGC_UART1_MASK                      (0x01UL << SIM_SCGC_UART1_SHIFT)                    /*!< SIM_SCGC: UART1 Mask                    */
#define SIM_SCGC_UART1_SHIFT                     21                                                  /*!< SIM_SCGC: UART1 Position                */
#define SIM_SCGC_UART2_MASK                      (0x01UL << SIM_SCGC_UART2_SHIFT)                    /*!< SIM_SCGC: UART2 Mask                    */
#define SIM_SCGC_UART2_SHIFT                     22                                                  /*!< SIM_SCGC: UART2 Position                */
#define SIM_SCGC_KBI0_MASK                       (0x01UL << SIM_SCGC_KBI0_SHIFT)                     /*!< SIM_SCGC: KBI0 Mask                     */
#define SIM_SCGC_KBI0_SHIFT                      24                                                  /*!< SIM_SCGC: KBI0 Position                 */
#define SIM_SCGC_KBI1_MASK                       (0x01UL << SIM_SCGC_KBI1_SHIFT)                     /*!< SIM_SCGC: KBI1 Mask                     */
#define SIM_SCGC_KBI1_SHIFT                      25                                                  /*!< SIM_SCGC: KBI1 Position                 */
#define SIM_SCGC_IRQ_MASK                        (0x01UL << SIM_SCGC_IRQ_SHIFT)                      /*!< SIM_SCGC: IRQ Mask                      */
#define SIM_SCGC_IRQ_SHIFT                       27                                                  /*!< SIM_SCGC: IRQ Position                  */
#define SIM_SCGC_ADC_MASK                        (0x01UL << SIM_SCGC_ADC_SHIFT)                      /*!< SIM_SCGC: ADC Mask                      */
#define SIM_SCGC_ADC_SHIFT                       29                                                  /*!< SIM_SCGC: ADC Position                  */
#define SIM_SCGC_ACMP0_MASK                      (0x01UL << SIM_SCGC_ACMP0_SHIFT)                    /*!< SIM_SCGC: ACMP0 Mask                    */
#define SIM_SCGC_ACMP0_SHIFT                     30                                                  /*!< SIM_SCGC: ACMP0 Position                */
#define SIM_SCGC_ACMP1_MASK                      (0x01UL << SIM_SCGC_ACMP1_SHIFT)                    /*!< SIM_SCGC: ACMP1 Mask                    */
#define SIM_SCGC_ACMP1_SHIFT                     31                                                  /*!< SIM_SCGC: ACMP1 Position                */

/* ------- SIM_UUIDL                                ------ */

/* ------- SIM_UUIDML                               ------ */

/* ------- SIM_UUIDMH                               ------ */

/* ------- SIM_CLKDIV                               ------ */
#define SIM_CLKDIV_OUTDIV3_MASK                  (0x01UL << SIM_CLKDIV_OUTDIV3_SHIFT)                /*!< SIM_CLKDIV: OUTDIV3 Mask                */
#define SIM_CLKDIV_OUTDIV3_SHIFT                 20                                                  /*!< SIM_CLKDIV: OUTDIV3 Position            */
#define SIM_CLKDIV_OUTDIV2_MASK                  (0x01UL << SIM_CLKDIV_OUTDIV2_SHIFT)                /*!< SIM_CLKDIV: OUTDIV2 Mask                */
#define SIM_CLKDIV_OUTDIV2_SHIFT                 24                                                  /*!< SIM_CLKDIV: OUTDIV2 Position            */
#define SIM_CLKDIV_OUTDIV1_MASK                  (0x03UL << SIM_CLKDIV_OUTDIV1_SHIFT)                /*!< SIM_CLKDIV: OUTDIV1 Mask                */
#define SIM_CLKDIV_OUTDIV1_SHIFT                 28                                                  /*!< SIM_CLKDIV: OUTDIV1 Position            */
#define SIM_CLKDIV_OUTDIV1(x)                    (((x)<<SIM_CLKDIV_OUTDIV1_SHIFT)&SIM_CLKDIV_OUTDIV1_MASK) /*!< SIM_CLKDIV                              */

/* -------------------------------------------------------------------------------- */
/* -----------     'SIM' Register Access macros                         ----------- */
/* -------------------------------------------------------------------------------- */

#define SIM_SRSID                      (SIM->SRSID)
#define SIM_SOPT0                      (SIM->SOPT0)
#define SIM_SOPT1                      (SIM->SOPT1)
#define SIM_PINSEL0                    (SIM->PINSEL0)
#define SIM_PINSEL1                    (SIM->PINSEL1)
#define SIM_SCGC                       (SIM->SCGC)
#define SIM_UUIDL                      (SIM->UUIDL)
#define SIM_UUIDML                     (SIM->UUIDML)
#define SIM_UUIDMH                     (SIM->UUIDMH)
#define SIM_CLKDIV                     (SIM->CLKDIV)

/* ================================================================================ */
/* ================           SPI0 (file:SPI0_MKE)                 ================ */
/* ================================================================================ */

/**
 * @brief Serial Peripheral Interface
 */
typedef struct {                                /*!<       SPI0 Structure                                               */
   __IO uint8_t   C1;                           /*!< 0000: SPI control register 1                                       */
   __IO uint8_t   C2;                           /*!< 0001: SPI control register 2                                       */
   __IO uint8_t   BR;                           /*!< 0002: SPI baud rate register BAUD = (Bus Clock)/Prescaler/Baud Rate Divisor */
   __I  uint8_t   S;                            /*!< 0003: SPI status register                                          */
   __I  uint8_t   RESERVED0;                    /*!< 0004:                                                              */
   __IO uint8_t   D;                            /*!< 0005: SPI data register                                            */
   __I  uint8_t   RESERVED1;                    /*!< 0006:                                                              */
   __IO uint8_t   M;                            /*!< 0007: SPI match register:                                          */
} SPI0_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'SPI0' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


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

/* ------- SPI0_C2                                  ------ */
#define SPI_C2_SPC0_MASK                         (0x01UL << SPI_C2_SPC0_SHIFT)                       /*!< SPI0_C2: SPC0 Mask                      */
#define SPI_C2_SPC0_SHIFT                        0                                                   /*!< SPI0_C2: SPC0 Position                  */
#define SPI_C2_SPISWAI_MASK                      (0x01UL << SPI_C2_SPISWAI_SHIFT)                    /*!< SPI0_C2: SPISWAI Mask                   */
#define SPI_C2_SPISWAI_SHIFT                     1                                                   /*!< SPI0_C2: SPISWAI Position               */
#define SPI_C2_BIDIROE_MASK                      (0x01UL << SPI_C2_BIDIROE_SHIFT)                    /*!< SPI0_C2: BIDIROE Mask                   */
#define SPI_C2_BIDIROE_SHIFT                     3                                                   /*!< SPI0_C2: BIDIROE Position               */
#define SPI_C2_MODFEN_MASK                       (0x01UL << SPI_C2_MODFEN_SHIFT)                     /*!< SPI0_C2: MODFEN Mask                    */
#define SPI_C2_MODFEN_SHIFT                      4                                                   /*!< SPI0_C2: MODFEN Position                */
#define SPI_C2_SPMIE_MASK                        (0x01UL << SPI_C2_SPMIE_SHIFT)                      /*!< SPI0_C2: SPMIE Mask                     */
#define SPI_C2_SPMIE_SHIFT                       7                                                   /*!< SPI0_C2: SPMIE Position                 */

/* ------- SPI0_BR                                  ------ */
#define SPI_BR_SPR_MASK                          (0x0FUL << SPI_BR_SPR_SHIFT)                        /*!< SPI0_BR: SPR Mask                       */
#define SPI_BR_SPR_SHIFT                         0                                                   /*!< SPI0_BR: SPR Position                   */
#define SPI_BR_SPR(x)                            (((x)<<SPI_BR_SPR_SHIFT)&SPI_BR_SPR_MASK)           /*!< SPI0_BR                                 */
#define SPI_BR_SPPR_MASK                         (0x07UL << SPI_BR_SPPR_SHIFT)                       /*!< SPI0_BR: SPPR Mask                      */
#define SPI_BR_SPPR_SHIFT                        4                                                   /*!< SPI0_BR: SPPR Position                  */
#define SPI_BR_SPPR(x)                           (((x)<<SPI_BR_SPPR_SHIFT)&SPI_BR_SPPR_MASK)         /*!< SPI0_BR                                 */

/* ------- SPI0_S                                   ------ */
#define SPI_S_MODF_MASK                          (0x01UL << SPI_S_MODF_SHIFT)                        /*!< SPI0_S: MODF Mask                       */
#define SPI_S_MODF_SHIFT                         4                                                   /*!< SPI0_S: MODF Position                   */
#define SPI_S_SPTEF_MASK                         (0x01UL << SPI_S_SPTEF_SHIFT)                       /*!< SPI0_S: SPTEF Mask                      */
#define SPI_S_SPTEF_SHIFT                        5                                                   /*!< SPI0_S: SPTEF Position                  */
#define SPI_S_SPMF_MASK                          (0x01UL << SPI_S_SPMF_SHIFT)                        /*!< SPI0_S: SPMF Mask                       */
#define SPI_S_SPMF_SHIFT                         6                                                   /*!< SPI0_S: SPMF Position                   */
#define SPI_S_SPRF_MASK                          (0x01UL << SPI_S_SPRF_SHIFT)                        /*!< SPI0_S: SPRF Mask                       */
#define SPI_S_SPRF_SHIFT                         7                                                   /*!< SPI0_S: SPRF Position                   */

/* ------- SPI0_D                                   ------ */
#define SPI_D_Bits_MASK                          (0xFFUL << SPI_D_Bits_SHIFT)                        /*!< SPI0_D: Bits Mask                       */
#define SPI_D_Bits_SHIFT                         0                                                   /*!< SPI0_D: Bits Position                   */
#define SPI_D_Bits(x)                            (((x)<<SPI_D_Bits_SHIFT)&SPI_D_Bits_MASK)           /*!< SPI0_D                                  */

/* ------- SPI0_M                                   ------ */
#define SPI_M_Bits_MASK                          (0xFFUL << SPI_M_Bits_SHIFT)                        /*!< SPI0_M: Bits Mask                       */
#define SPI_M_Bits_SHIFT                         0                                                   /*!< SPI0_M: Bits Position                   */
#define SPI_M_Bits(x)                            (((x)<<SPI_M_Bits_SHIFT)&SPI_M_Bits_MASK)           /*!< SPI0_M                                  */

/* -------------------------------------------------------------------------------- */
/* -----------     'SPI0' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define SPI0_C1                        (SPI0->C1)
#define SPI0_C2                        (SPI0->C2)
#define SPI0_BR                        (SPI0->BR)
#define SPI0_S                         (SPI0->S)
#define SPI0_D                         (SPI0->D)
#define SPI0_M                         (SPI0->M)

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

#define SPI1_C1                        (SPI1->C1)
#define SPI1_C2                        (SPI1->C2)
#define SPI1_BR                        (SPI1->BR)
#define SPI1_S                         (SPI1->S)
#define SPI1_D                         (SPI1->D)
#define SPI1_M                         (SPI1->M)

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
/* ================           UART0 (file:UART0_MKE)               ================ */
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
#define UART_D_DATA_MASK                         (0xFFUL << UART_D_DATA_SHIFT)                       /*!< UART0_D: DATA Mask                      */
#define UART_D_DATA_SHIFT                        0                                                   /*!< UART0_D: DATA Position                  */
#define UART_D_DATA(x)                           (((x)<<UART_D_DATA_SHIFT)&UART_D_DATA_MASK)         /*!< UART0_D                                 */

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

/* ================================================================================ */
/* ================           UART2 (derived from UART0)           ================ */
/* ================================================================================ */

/**
 * @brief Universal Asynchronous Receiver/Transmitter
 */
typedef UART0_Type UART2_Type;  /*!< UART2 Structure                                             */


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

/* ================================================================================ */
/* ================           WDOG (file:WDOG_MKE)                 ================ */
/* ================================================================================ */

/**
 * @brief Watchdog timer
 */
typedef struct {                                /*!<       WDOG Structure                                               */
   __IO uint8_t   CS1;                          /*!< 0000: Control and Status Register 1                                */
   __IO uint8_t   CS2;                          /*!< 0001: Control and Status Register 2                                */
   union {                                      /*!< 0000: (size=0002)                                                  */
      __IO uint16_t  CNT;                       /*!< 0002: Counter Register: (Note: CNTL:CNTH)                          */
      struct {                                  /*!< 0000: (size=0002)                                                  */
         __I  uint8_t   CNTH;                   /*!< 0002: Counter Register: High (see CNT for description)             */
         __I  uint8_t   CNTL;                   /*!< 0003: Counter Register: Low (see CNT for description)              */
      };
   };
   union {                                      /*!< 0000: (size=0002)                                                  */
      __IO uint16_t  TOVAL;                     /*!< 0004: Timeout Value Register: (Note TOVALL:TOVALH)                 */
      struct {                                  /*!< 0000: (size=0002)                                                  */
         __IO uint8_t   TOVALH;                 /*!< 0004: Timeout Value Register: High (see TOVAL for description)     */
         __IO uint8_t   TOVALL;                 /*!< 0005: Timeout Value Register: Low (see TOVAL for description)      */
      };
   };
   union {                                      /*!< 0000: (size=0002)                                                  */
      __IO uint16_t  WIN;                       /*!< 0006: Window Register:(Note WINL:WINH)                             */
      struct {                                  /*!< 0000: (size=0002)                                                  */
         __IO uint8_t   WINH;                   /*!< 0006: Window Register: High (see WIN for description)              */
         __IO uint8_t   WINL;                   /*!< 0007: Window Register: Low (see WIN for description)               */
      };
   };
} WDOG_Type;


/* -------------------------------------------------------------------------------- */
/* -----------     'WDOG' Position & Mask macros                        ----------- */
/* -------------------------------------------------------------------------------- */


/* ------- WDOG_CS1                                 ------ */
#define WDOG_CS1_STOP_MASK                       (0x01UL << WDOG_CS1_STOP_SHIFT)                     /*!< WDOG_CS1: STOP Mask                     */
#define WDOG_CS1_STOP_SHIFT                      0                                                   /*!< WDOG_CS1: STOP Position                 */
#define WDOG_CS1_WAIT_MASK                       (0x01UL << WDOG_CS1_WAIT_SHIFT)                     /*!< WDOG_CS1: WAIT Mask                     */
#define WDOG_CS1_WAIT_SHIFT                      1                                                   /*!< WDOG_CS1: WAIT Position                 */
#define WDOG_CS1_DBG_MASK                        (0x01UL << WDOG_CS1_DBG_SHIFT)                      /*!< WDOG_CS1: DBG Mask                      */
#define WDOG_CS1_DBG_SHIFT                       2                                                   /*!< WDOG_CS1: DBG Position                  */
#define WDOG_CS1_TST_MASK                        (0x03UL << WDOG_CS1_TST_SHIFT)                      /*!< WDOG_CS1: TST Mask                      */
#define WDOG_CS1_TST_SHIFT                       3                                                   /*!< WDOG_CS1: TST Position                  */
#define WDOG_CS1_TST(x)                          (((x)<<WDOG_CS1_TST_SHIFT)&WDOG_CS1_TST_MASK)       /*!< WDOG_CS1                                */
#define WDOG_CS1_UPDATE_MASK                     (0x01UL << WDOG_CS1_UPDATE_SHIFT)                   /*!< WDOG_CS1: UPDATE Mask                   */
#define WDOG_CS1_UPDATE_SHIFT                    5                                                   /*!< WDOG_CS1: UPDATE Position               */
#define WDOG_CS1_INT_MASK                        (0x01UL << WDOG_CS1_INT_SHIFT)                      /*!< WDOG_CS1: INT Mask                      */
#define WDOG_CS1_INT_SHIFT                       6                                                   /*!< WDOG_CS1: INT Position                  */
#define WDOG_CS1_EN_MASK                         (0x01UL << WDOG_CS1_EN_SHIFT)                       /*!< WDOG_CS1: EN Mask                       */
#define WDOG_CS1_EN_SHIFT                        7                                                   /*!< WDOG_CS1: EN Position                   */

/* ------- WDOG_CS2                                 ------ */
#define WDOG_CS2_CLK_MASK                        (0x03UL << WDOG_CS2_CLK_SHIFT)                      /*!< WDOG_CS2: CLK Mask                      */
#define WDOG_CS2_CLK_SHIFT                       0                                                   /*!< WDOG_CS2: CLK Position                  */
#define WDOG_CS2_CLK(x)                          (((x)<<WDOG_CS2_CLK_SHIFT)&WDOG_CS2_CLK_MASK)       /*!< WDOG_CS2                                */
#define WDOG_CS2_PRES_MASK                       (0x01UL << WDOG_CS2_PRES_SHIFT)                     /*!< WDOG_CS2: PRES Mask                     */
#define WDOG_CS2_PRES_SHIFT                      4                                                   /*!< WDOG_CS2: PRES Position                 */
#define WDOG_CS2_FLG_MASK                        (0x01UL << WDOG_CS2_FLG_SHIFT)                      /*!< WDOG_CS2: FLG Mask                      */
#define WDOG_CS2_FLG_SHIFT                       6                                                   /*!< WDOG_CS2: FLG Position                  */
#define WDOG_CS2_WIN_MASK                        (0x01UL << WDOG_CS2_WIN_SHIFT)                      /*!< WDOG_CS2: WIN Mask                      */
#define WDOG_CS2_WIN_SHIFT                       7                                                   /*!< WDOG_CS2: WIN Position                  */

/* ------- WDOG_CNT                                 ------ */

/* ------- WDOG_CNTH                                ------ */

/* ------- WDOG_CNTL                                ------ */

/* ------- WDOG_TOVAL                               ------ */

/* ------- WDOG_TOVALH                              ------ */

/* ------- WDOG_TOVALL                              ------ */

/* ------- WDOG_WIN                                 ------ */

/* ------- WDOG_WINH                                ------ */

/* ------- WDOG_WINL                                ------ */

/* -------------------------------------------------------------------------------- */
/* -----------     'WDOG' Register Access macros                        ----------- */
/* -------------------------------------------------------------------------------- */

#define WDOG_CS1                       (WDOG->CS1)
#define WDOG_CS2                       (WDOG->CS2)
#define WDOG_CNT                       (WDOG->CNT)
#define WDOG_CNTH                      (WDOG->CNTH)
#define WDOG_CNTL                      (WDOG->CNTL)
#define WDOG_TOVAL                     (WDOG->TOVAL)
#define WDOG_TOVALH                    (WDOG->TOVALH)
#define WDOG_TOVALL                    (WDOG->TOVALL)
#define WDOG_WIN                       (WDOG->WIN)
#define WDOG_WINH                      (WDOG->WINH)
#define WDOG_WINL                      (WDOG->WINL)
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

#define ACMP0_BASE_PTR                 0x40073000UL
#define ACMP1_BASE_PTR                 0x40074000UL
#define ADC_BASE_PTR                   0x4003B000UL
#define BP_BASE_PTR                    0xE0002000UL
#define CRC_BASE_PTR                   0x40032000UL
#define FGPIOA_BASE_PTR                0xF8000000UL
#define FGPIOB_BASE_PTR                0xF8000000UL
#define FGPIOC_BASE_PTR                0xF8000000UL
#define FTM0_BASE_PTR                  0x40038000UL
#define FTM1_BASE_PTR                  0x40039000UL
#define FTM2_BASE_PTR                  0x4003A000UL
#define FTMRE_BASE_PTR                 0x40020000UL
#define GPIOA_BASE_PTR                 0x400FF000UL
#define GPIOB_BASE_PTR                 0x400FF040UL
#define GPIOC_BASE_PTR                 0x400FF080UL
#define I2C0_BASE_PTR                  0x40066000UL
#define I2C1_BASE_PTR                  0x40067000UL
#define ICS_BASE_PTR                   0x40064000UL
#define IRQ_BASE_PTR                   0x40031000UL
#define KBI0_BASE_PTR                  0x40079000UL
#define KBI1_BASE_PTR                  0x4007A000UL
#define MCM_BASE_PTR                   0xF0003000UL
#define MSCAN_BASE_PTR                 0x40024000UL
#define NV_BASE_PTR                    0x00000400UL
#define OSC_BASE_PTR                   0x40065000UL
#define PIT_BASE_PTR                   0x40037000UL
#define PMC_BASE_PTR                   0x4007D000UL
#define PORT_BASE_PTR                  0x40049000UL
#define PWT_BASE_PTR                   0x40033000UL
#define RTC_BASE_PTR                   0x4003D000UL
#define SIM_BASE_PTR                   0x40048000UL
#define SPI0_BASE_PTR                  0x40076000UL
#define SPI1_BASE_PTR                  0x40077000UL
#define SYST_BASE_PTR                  0xE000E010UL
#define UART0_BASE_PTR                 0x4006A000UL
#define UART1_BASE_PTR                 0x4006B000UL
#define UART2_BASE_PTR                 0x4006C000UL
#define WDOG_BASE_PTR                  0x40052000UL

/* ================================================================================ */
/* ================             Peripheral declarations            ================ */
/* ================================================================================ */

#define ACMP0                          ((volatile ACMP0_Type  *) ACMP0_BASE_PTR)
#define ACMP1                          ((volatile ACMP1_Type  *) ACMP1_BASE_PTR)
#define ADC                            ((volatile ADC_Type    *) ADC_BASE_PTR)
#define BP                             ((volatile BP_Type     *) BP_BASE_PTR)
#define CRC                            ((volatile CRC_Type    *) CRC_BASE_PTR)
#define FGPIOA                         ((volatile FGPIOA_Type *) FGPIOA_BASE_PTR)
#define FGPIOB                         ((volatile FGPIOB_Type *) FGPIOB_BASE_PTR)
#define FGPIOC                         ((volatile FGPIOC_Type *) FGPIOC_BASE_PTR)
#define FTM0                           ((volatile FTM0_Type   *) FTM0_BASE_PTR)
#define FTM1                           ((volatile FTM1_Type   *) FTM1_BASE_PTR)
#define FTM2                           ((volatile FTM2_Type   *) FTM2_BASE_PTR)
#define FTMRE                          ((volatile FTMRE_Type  *) FTMRE_BASE_PTR)
#define GPIOA                          ((volatile GPIOA_Type  *) GPIOA_BASE_PTR)
#define GPIOB                          ((volatile GPIOB_Type  *) GPIOB_BASE_PTR)
#define GPIOC                          ((volatile GPIOC_Type  *) GPIOC_BASE_PTR)
#define I2C0                           ((volatile I2C0_Type   *) I2C0_BASE_PTR)
#define I2C1                           ((volatile I2C1_Type   *) I2C1_BASE_PTR)
#define ICS                            ((volatile ICS_Type    *) ICS_BASE_PTR)
#define IRQ                            ((volatile IRQ_Type    *) IRQ_BASE_PTR)
#define KBI0                           ((volatile KBI0_Type   *) KBI0_BASE_PTR)
#define KBI1                           ((volatile KBI1_Type   *) KBI1_BASE_PTR)
#define MCM                            ((volatile MCM_Type    *) MCM_BASE_PTR)
#define MSCAN                          ((volatile MSCAN_Type  *) MSCAN_BASE_PTR)
#define NV                             ((volatile NV_Type     *) NV_BASE_PTR)
#define OSC                            ((volatile OSC_Type    *) OSC_BASE_PTR)
#define PIT                            ((volatile PIT_Type    *) PIT_BASE_PTR)
#define PMC                            ((volatile PMC_Type    *) PMC_BASE_PTR)
#define PORT                           ((volatile PORT_Type   *) PORT_BASE_PTR)
#define PWT                            ((volatile PWT_Type    *) PWT_BASE_PTR)
#define RTC                            ((volatile RTC_Type    *) RTC_BASE_PTR)
#define SIM                            ((volatile SIM_Type    *) SIM_BASE_PTR)
#define SPI0                           ((volatile SPI0_Type   *) SPI0_BASE_PTR)
#define SPI1                           ((volatile SPI1_Type   *) SPI1_BASE_PTR)
#define SYST                           ((volatile SYST_Type   *) SYST_BASE_PTR)
#define UART0                          ((volatile UART0_Type  *) UART0_BASE_PTR)
#define UART1                          ((volatile UART1_Type  *) UART1_BASE_PTR)
#define UART2                          ((volatile UART2_Type  *) UART2_BASE_PTR)
#define WDOG                           ((volatile WDOG_Type   *) WDOG_BASE_PTR)

#ifdef __cplusplus
}
#endif


#endif  /* MCU_MKE06Z4 */
