/*
 *  Vectors.c
 *
 *  Vectors and security for MK40DX256Z
 *
 *  Created on: 07/12/2012
 *      Author: podonoghue
 */
#include <stdint.h>
#include <string.h>
#include "derivative.h"

#define $(targetDeviceSubFamily)

/*
 * Security information
 */
typedef struct {
    uint8_t  backdoorKey[8];
    uint32_t fprot;
    uint8_t  fsec;
    uint8_t  fopt;
    uint8_t  feprot;
    uint8_t  fdprot;
} SecurityInfo;

__attribute__ ((section(".security_information")))
const SecurityInfo securityInfo = {
    /* backdoor */ {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},
    /* fprot    */ 0xFFFFFFFF,
    /* fsec     */ 0xFE,
    /* fopt     */ 0xFF,
    /* feprot   */ 0xFF,
    /* fdprot   */ 0xFF,
};

/*
 * Vector table related
 */
typedef void( *const intfunc )( void );

#define WEAK_DEFAULT_HANDLER __attribute__ ((__weak__, alias("Default_Handler")))

#ifndef SCB_ICSR
#define SCB_ICSR (*(volatile uint32_t*)(0xE000ED04))
#endif

__attribute__((__interrupt__))
void Default_Handler(void) {

   uint32_t vectorNum = SCB_ICSR;

   (void)vectorNum;

   while (1) {
      asm("bkpt #0");
   }
}

typedef struct {
   unsigned int r0;
   unsigned int r1;
   unsigned int r2;
   unsigned int r3;
   unsigned int r12;
   unsigned int lr;
   unsigned int pc;
   unsigned int psr;
} ExceptionFrame;

typedef struct {
   unsigned int scb_hfsr;
   unsigned int scb_cfsr;
   unsigned int scb_bfar;
} ExceptionInfo;

/*  Low-level exception handler
 *
 *  Interface from asm to C.
 *  Passes address of exception handler to C-level handler
 *
 *  See http://www.freertos.org/Debugging-Hard-Faults-On-Cortex-M-Microcontrollers.html
 */
__attribute__((__naked__, __weak__, __interrupt__))
void HardFault_Handler(void) {
        __asm volatile ( "  tst   lr, #4              \n");  // Check mode
        __asm volatile ( "  ite   eq                  \n");  // Get active SP
        __asm volatile ( "  mrseq r0, msp             \n");
        __asm volatile ( "  mrsne r0, psp             \n");
//        __asm volatile ( "  ldr   r1,[r0,#24]         \n");  // PC
//        __asm volatile ( "  push  {r1}                \n");  // Dummy ?
        __asm volatile ( "  bl    _HardFault_Handler  \n");  // Go to C handler
}

/******************************************************************************/
/* Exception frame without floating-point storage
 * hard fault handler in C,
 * with stack frame location as input parameter
 *
 * @param exceptionFrame address of exception frame
 *
 */
void _HardFault_Handler(volatile ExceptionFrame *exceptionFrame) {
   (void)exceptionFrame;
#ifdef SCB_HFSR
   char reason[200] = "";
   volatile ExceptionInfo exceptionInfo = {0};
   exceptionInfo.scb_hfsr = SCB_HFSR;
   (void)exceptionInfo.scb_hfsr;
   if ((exceptionInfo.scb_hfsr&SCB_HFSR_FORCED_MASK) != 0) {
      // Forced
      exceptionInfo.scb_cfsr = SCB_CFSR;

      if (SCB_CFSR&SCB_CFSR_BFARVALID_MASK) {
         exceptionInfo.scb_bfar = SCB_BFAR;
      }
      /* CFSR Bit Fields */
      if (SCB_CFSR&SCB_CFSR_DIVBYZERO_MASK  ) { strcat(reason, "Divide by zero,"); }
      if (SCB_CFSR&SCB_CFSR_UNALIGNED_MASK  ) { strcat(reason, "Unaligned access,"); }
      if (SCB_CFSR&SCB_CFSR_NOCP_MASK       ) { strcat(reason, "No co-processor"); }
      if (SCB_CFSR&SCB_CFSR_INVPC_MASK      ) { strcat(reason, "Invalid PC (on return),"); }
      if (SCB_CFSR&SCB_CFSR_INVSTATE_MASK   ) { strcat(reason, "Invalid state (EPSR.T/IT,"); }
      if (SCB_CFSR&SCB_CFSR_UNDEFINSTR_MASK ) { strcat(reason, "Undefined Instruction,"); }
      if (SCB_CFSR&SCB_CFSR_BFARVALID_MASK  ) { strcat(reason, "BFAR contents valid,"); }
      if (SCB_CFSR&SCB_CFSR_LSPERR_MASK     ) { strcat(reason, "Bus fault on FP state save,"); }
      if (SCB_CFSR&SCB_CFSR_STKERR_MASK     ) { strcat(reason, "Bus fault on exception entry,"); }
      if (SCB_CFSR&SCB_CFSR_UNSTKERR_MASK   ) { strcat(reason, "Bus fault on exception return,"); }
      if (SCB_CFSR&SCB_CFSR_IMPRECISERR_MASK) { strcat(reason, "Imprecise data access error,"); }
      if (SCB_CFSR&SCB_CFSR_PRECISERR_MASK  ) { strcat(reason, "Precise data access error,"); }
      if (SCB_CFSR&SCB_CFSR_IBUSERR_MASK    ) { strcat(reason, "Bus fault on instruction pre-fetch,"); }
      if (SCB_CFSR&SCB_CFSR_MMARVALID_MASK  ) { strcat(reason, "MMAR contents valid,"); }
      if (SCB_CFSR&SCB_CFSR_MLSPERR_MASK    ) { strcat(reason, "MemManage fault on FP state save,"); }
      if (SCB_CFSR&SCB_CFSR_MSTKERR_MASK    ) { strcat(reason, "MemManage fault on exception entry,"); }
      if (SCB_CFSR&SCB_CFSR_MUNSTKERR_MASK  ) { strcat(reason, "MemManage fault on exception return,"); }
      if (SCB_CFSR&SCB_CFSR_DACCVIOL_MASK   ) { strcat(reason, "MemManage access violation on data access,"); }
      if (SCB_CFSR&SCB_CFSR_IACCVIOL_MASK   ) { strcat(reason, "MemManage access violation on instruction fetch,"); }
   }
#endif
   while (1) {
      asm("bkpt #0");
   }
}

void __HardReset(void) __attribute__((__interrupt__));
extern uint32_t __StackTop;

/*
 * Each vector is assigned an unique name.  This is then 'weakly' assigned to the
 * default handler.
 * To install a handler, create a function with the name shown and it will override
 * the weak default.
 */
void NMI_Handler(void)                 WEAK_DEFAULT_HANDLER;
void MemManage_Handler(void)           WEAK_DEFAULT_HANDLER;
void BusFault_Handler(void)            WEAK_DEFAULT_HANDLER;
void UsageFault_Handler(void)          WEAK_DEFAULT_HANDLER;
void SVC_Handler(void)                 WEAK_DEFAULT_HANDLER;
void DebugMon_Handler(void)            WEAK_DEFAULT_HANDLER;
void PendSV_Handler(void)              WEAK_DEFAULT_HANDLER;
void SysTick_Handler(void)             WEAK_DEFAULT_HANDLER;

void DMA0_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void DMA1_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void DMA2_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void DMA3_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void DMA4_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void DMA5_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void DMA6_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void DMA7_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void DMA8_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void DMA9_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void DMA10_IRQHandler(void)            WEAK_DEFAULT_HANDLER;
void DMA11_IRQHandler(void)            WEAK_DEFAULT_HANDLER;
void DMA12_IRQHandler(void)            WEAK_DEFAULT_HANDLER;
void DMA13_IRQHandler(void)            WEAK_DEFAULT_HANDLER;
void DMA14_IRQHandler(void)            WEAK_DEFAULT_HANDLER;
void DMA15_IRQHandler(void)            WEAK_DEFAULT_HANDLER;
void DMA_Error_Handler(void)           WEAK_DEFAULT_HANDLER;
void MCM_IRQHandler(void)              WEAK_DEFAULT_HANDLER;
void FTFL_Command_IRQHandler(void)     WEAK_DEFAULT_HANDLER;
void FTFL_Collision_IRQHandler(void)   WEAK_DEFAULT_HANDLER;
void PMC_IRQHandler(void)              WEAK_DEFAULT_HANDLER;
void LLWU_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void WDOG_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void I2C0_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void I2C1_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void SPI0_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void SPI1_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void SPI2_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void CAN0_Message_IRQHandler(void)     WEAK_DEFAULT_HANDLER;
void CAN0_BussOff_IRQHandler(void)     WEAK_DEFAULT_HANDLER;
void CAN0_Error_IRQHandler(void)       WEAK_DEFAULT_HANDLER;
void CAN0_TxWarning_IRQHandler(void)   WEAK_DEFAULT_HANDLER;
void CAN0_RxWarning_IRQHandler(void)   WEAK_DEFAULT_HANDLER;
void CAN0_Wakeup_IRQHandler(void)      WEAK_DEFAULT_HANDLER;
void CAN1_Message_IRQHandler(void)     WEAK_DEFAULT_HANDLER;
void CAN1_BussOff_IRQHandler(void)     WEAK_DEFAULT_HANDLER;
void CAN1_Error_IRQHandler(void)       WEAK_DEFAULT_HANDLER;
void CAN1_TxWarning_IRQHandler(void)   WEAK_DEFAULT_HANDLER;
void CAN1_RxWarning_IRQHandler(void)   WEAK_DEFAULT_HANDLER;
void CAN1_Wakeup_IRQHandler(void)      WEAK_DEFAULT_HANDLER;
void UART0_Status_IRQHandler(void)     WEAK_DEFAULT_HANDLER;
void UART0_Error_IRQHandler(void)      WEAK_DEFAULT_HANDLER;
void UART1_Status_IRQHandler(void)     WEAK_DEFAULT_HANDLER;
void UART1_Error_IRQHandler(void)      WEAK_DEFAULT_HANDLER;
void UART2_Status_IRQHandler(void)     WEAK_DEFAULT_HANDLER;
void UART2_Error_IRQHandler(void)      WEAK_DEFAULT_HANDLER;
void UART3_Status_IRQHandler(void)     WEAK_DEFAULT_HANDLER;
void UART3_Error_IRQHandler(void)      WEAK_DEFAULT_HANDLER;
void UART4_Status_IRQHandler(void)     WEAK_DEFAULT_HANDLER;
void UART4_Error_IRQHandler(void)      WEAK_DEFAULT_HANDLER;
void UART5_Status_IRQHandler(void)     WEAK_DEFAULT_HANDLER;
void UART5_Error_IRQHandler(void)      WEAK_DEFAULT_HANDLER;
void ADC0_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void ADC1_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void CMP0_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void CMP1_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void CMP2_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void FTM0_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void FTM1_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void FTM2_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void CMT_IRQHandler(void)              WEAK_DEFAULT_HANDLER;
void RTC_IRQHandler(void)              WEAK_DEFAULT_HANDLER;
void PIT_Ch0_IRQHandler(void)          WEAK_DEFAULT_HANDLER;
void PIT_Ch1_IRQHandler(void)          WEAK_DEFAULT_HANDLER;
void PIT_Ch2_IRQHandler(void)          WEAK_DEFAULT_HANDLER;
void PIT_Ch3_IRQHandler(void)          WEAK_DEFAULT_HANDLER;
void PDB_IRQHandler(void)              WEAK_DEFAULT_HANDLER;
void USBOTG_IRQHandler(void)           WEAK_DEFAULT_HANDLER;
void USB0_Charge_IRQHandler(void)      WEAK_DEFAULT_HANDLER;
void I2S0_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void SDHC_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void DAC0_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void DAC1_IRQHandler(void)             WEAK_DEFAULT_HANDLER;
void TSI_IRQHandler(void)              WEAK_DEFAULT_HANDLER;
void MCG_IRQHandler(void)              WEAK_DEFAULT_HANDLER;
void LPTMR0_IRQHandler(void)           WEAK_DEFAULT_HANDLER;
void LCD_IRQHandler(void)              WEAK_DEFAULT_HANDLER;
void PORTA_IRQHandler(void)            WEAK_DEFAULT_HANDLER;
void PORTB_IRQHandler(void)            WEAK_DEFAULT_HANDLER;
void PORTC_IRQHandler(void)            WEAK_DEFAULT_HANDLER;
void PORTD_IRQHandler(void)            WEAK_DEFAULT_HANDLER;
void PORTE_IRQHandler(void)            WEAK_DEFAULT_HANDLER;
void SWI_IRQHandler(void)              WEAK_DEFAULT_HANDLER;

typedef struct {
   uint32_t *initialSP;
   intfunc  handlers[];
} VectorTable;

__attribute__ ((section(".interrupt_vectors")))
VectorTable const __vector_table = {
    &__StackTop,                       /* Vec #0   Initial stack pointer                        */
    {
          __HardReset,                 /* Vec #1   Reset Handler                                */
          NMI_Handler,                 /* Vec #2   NMI Handler                                  */
(intfunc) HardFault_Handler,           /* Vec #3   Hard Fault Handler                           */
          MemManage_Handler,           /* Vec #4   MPU Fault Handler                            */
          BusFault_Handler,            /* Vec #5   Bus Fault Handler                            */
          UsageFault_Handler,          /* Vec #6   Usage Fault Handler                          */
          Default_Handler,             /* Vec #7   Reserved                                     */
          Default_Handler,             /* Vec #8   Reserved                                     */
          Default_Handler,             /* Vec #9   Reserved                                     */
          Default_Handler,             /* Vec #10  Reserved                                     */
          SVC_Handler,                 /* Vec #11  SVCall Handler                               */
          DebugMon_Handler,            /* Vec #12  Debug Monitor Handler                        */
          Default_Handler,             /* Vec #13  Reserved                                     */
          PendSV_Handler,              /* Vec #14  PendSV Handler                               */
          SysTick_Handler,             /* Vec #15  SysTick Handler                              */

                                       /* External Interrupts */
          DMA0_IRQHandler,             /* Int #0   DMA Channel 0 Transfer Complete and Error    */
          DMA1_IRQHandler,             /* Int #1   DMA Channel 1 Transfer Complete and Error    */
          DMA2_IRQHandler,             /* Int #2   DMA Channel 2 Transfer Complete and Error    */
          DMA3_IRQHandler,             /* Int #3   DMA Channel 3 Transfer Complete and Error    */
          DMA4_IRQHandler,             /* Int #4   DMA Channel 4 Transfer Complete and Error    */
          DMA5_IRQHandler,             /* Int #5   DMA Channel 5 Transfer Complete and Error    */
          DMA6_IRQHandler,             /* Int #6   DMA Channel 6 Transfer Complete and Error    */
          DMA7_IRQHandler,             /* Int #7   DMA Channel 7 Transfer Complete and Error    */
          DMA8_IRQHandler,             /* Int #8   DMA Channel 8 Transfer Complete and Error    */
          DMA9_IRQHandler,             /* Int #9   DMA Channel 9 Transfer Complete and Error    */
          DMA10_IRQHandler,            /* Int #10  DMA Channel 10 Transfer Complete and Error   */
          DMA11_IRQHandler,            /* Int #11  DMA Channel 11 Transfer Complete and Error   */
          DMA12_IRQHandler,            /* Int #12  DMA Channel 12 Transfer Complete and Error   */
          DMA13_IRQHandler,            /* Int #13  DMA Channel 13 Transfer Complete and Error   */
          DMA14_IRQHandler,            /* Int #14  DMA Channel 14 Transfer Complete and Error   */
          DMA15_IRQHandler,            /* Int #15  DMA Channel 15 Transfer Complete and Error   */
          DMA_Error_Handler,           /* Int #16  DMA error interrupt channel                  */
          MCM_IRQHandler,              /* Int #17  MCM interrupt                                */
          FTFL_Command_IRQHandler,     /* Int #18  FTFL Flash command complete                  */
          FTFL_Collision_IRQHandler,   /* Int #19  FTFL Flash read collision                    */
          PMC_IRQHandler,              /* Int #20  PMC interrupt */
          LLWU_IRQHandler,             /* Int #21  LLWU Low Leakage Wake-up                     */
          WDOG_IRQHandler,             /* Int #22  WDOG interrupt                               */
          Default_Handler,             /* Int #23 */
          I2C0_IRQHandler,             /* Int #24  I2C0 interrupt                               */
          I2C1_IRQHandler,             /* Int #25  I2C1 interrupt                               */
          SPI0_IRQHandler,             /* Int #26  SPI0 interrupt                               */
          SPI1_IRQHandler,             /* Int #27  SPI1 interrupt                               */
          SPI2_IRQHandler,             /* Int #28  SPI2 interrupt                               */
          CAN0_Message_IRQHandler,     /* Int #29  CAN0 message interrupt                       */
          CAN0_BussOff_IRQHandler,     /* Int #30  CAN0 buss off interrupt                      */
          CAN0_Error_IRQHandler,       /* Int #31  CAN0 Error interrupt                         */
          CAN0_TxWarning_IRQHandler,   /* Int #32  CAN0 Transmit warning interrupt              */
          CAN0_RxWarning_IRQHandler,   /* Int #33  CAN0 Receive Warning interrupt               */
          CAN0_Wakeup_IRQHandler,      /* Int #34  CAN0 Wakeup                                  */
          Default_Handler,             /* Int #35 */
          Default_Handler,             /* Int #36 */
          CAN1_Message_IRQHandler,     /* Int #37  CAN1 message                                 */
          CAN1_BussOff_IRQHandler,     /* Int #38  CAN1 buss off interrupt                      */
          CAN1_Error_IRQHandler,       /* Int #39  CAN1 Error interrupt                         */
          CAN1_TxWarning_IRQHandler,   /* Int #40  CAN0 Transmit warning interrupt              */
          CAN1_RxWarning_IRQHandler,   /* Int #41  CAN0 Receive Warning interrupt               */
          CAN1_Wakeup_IRQHandler,      /* Int #42  CAN0 Wakeup                                  */
          Default_Handler,             /* Int #43 */
          Default_Handler,             /* Int #44 */
          UART0_Status_IRQHandler,     /* Int #45  UART0 Status Interrupt                       */
          UART0_Error_IRQHandler,      /* Int #46  UART0 Error interrupt                        */
          UART1_Status_IRQHandler,     /* Int #47  UART1 Status Interrupt                       */
          UART1_Error_IRQHandler,      /* Int #48  UART1 Error interrupt                        */
          UART2_Status_IRQHandler,     /* Int #49  UART2 Status Interrupt                       */
          UART2_Error_IRQHandler,      /* Int #50  UART2 Error interrupt                        */
          UART3_Status_IRQHandler,     /* Int #51  UART3 Status Interrupt                       */
          UART3_Error_IRQHandler,      /* Int #52  UART3 Error interrupt                        */
          UART4_Status_IRQHandler,     /* Int #53  UART4 Status Interrupt                       */
          UART4_Error_IRQHandler,      /* Int #54  UART4 Error interrupt                        */
          UART5_Status_IRQHandler,     /* Int #55  UART5 Status Interrupt                       */
          UART5_Error_IRQHandler,      /* Int #56  UART5 Error interrupt                        */
          ADC0_IRQHandler,             /* Int #57  ADC0 interrupt                               */
          ADC1_IRQHandler,             /* Int #58  ADC1 interrupt                               */
          CMP0_IRQHandler,             /* Int #59  CMP0 interrupt                               */
          CMP1_IRQHandler,             /* Int #60  CMP1 interrupt                               */
          CMP2_IRQHandler,             /* Int #61  CMP2 interrupt                               */
          FTM0_IRQHandler,             /* Int #62  FTM0 interrupt                               */
          FTM1_IRQHandler,             /* Int #63  FTM1 interrupt                               */
          FTM2_IRQHandler,             /* Int #64  FTM2 interrupt                               */
          CMT_IRQHandler,              /* Int #65  CMT interrupt                                */
          RTC_IRQHandler,              /* Int #66  RTC interrupt                                */
          Default_Handler,             /* Int #67 */
          PIT_Ch0_IRQHandler,          /* Int #68  PIT Channel 0 interrupt                      */
          PIT_Ch1_IRQHandler,          /* Int #69  PIT Channel 1 interrupt                      */
          PIT_Ch2_IRQHandler,          /* Int #70  PIT Channel 2 interrupt                      */
          PIT_Ch3_IRQHandler,          /* Int #71  PIT Channel 3 interrupt                      */
          PDB_IRQHandler,              /* Int #72  PDB interrupt                                */
          USBOTG_IRQHandler,           /* Int #73  USB OTG interrupt                            */
          USB0_Charge_IRQHandler,      /* Int #74  USB Charge detect interrupt                  */
          Default_Handler,             /* Int #75 */
          Default_Handler,             /* Int #76 */
          Default_Handler,             /* Int #77 */
          Default_Handler,             /* Int #78 */
          I2S0_IRQHandler,             /* Int #79  I2SO interrupt                               */
          SDHC_IRQHandler,             /* Int #80  SDHC interrupt                               */
          DAC0_IRQHandler,             /* Int #81  DAC0 interrupt                               */
          DAC1_IRQHandler,             /* Int #82  DAC1 interrupt                               */
          TSI_IRQHandler,              /* Int #83  TSI interrupt                                */
          MCG_IRQHandler,              /* Int #84  MCG interrupt                                */
          LPTMR0_IRQHandler,           /* Int #85  LPTMR0 interrupt                             */
          LCD_IRQHandler,              /* Int #86  LCD interrupt                                */
          PORTA_IRQHandler,            /* Int #87  PORT A interrupt                             */
          PORTB_IRQHandler,            /* Int #88  PORT B interrupt                             */
          PORTC_IRQHandler,            /* Int #89  PORT C interrupt                             */
          PORTD_IRQHandler,            /* Int #90  PORT D interrupt                             */
          PORTE_IRQHandler,            /* Int #91  PORT E interrupt                             */
          Default_Handler,             /* Int #92 */
          Default_Handler,             /* Int #93 */
          SWI_IRQHandler,              /* Int #94  SWI interrupt                                */
   }
};
