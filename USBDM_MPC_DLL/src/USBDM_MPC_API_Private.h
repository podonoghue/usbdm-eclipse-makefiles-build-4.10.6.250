/*
 * USBDM_DSC_API_AUX.h
 *
 *  Created on: 26/02/2011
 *      Author: podonoghue
 */

#ifndef USBDM_DSC_API_AUX_H_
#define USBDM_DSC_API_AUX_H_

// Master TAP
#define JTAG_MASTER_COMMAND_LENGTH    (5)
#define JTAG_IDCODE_COMMAND           (0x01)
#define JTAG_BYPASS_COMMAND           (~0x00)
#define ACCESS_AUX_TAP_NPC_COMMAND    (0x10)
#define ACCESS_AUX_TAP_ONCE_COMMAND   (0x11)
#define ACCESS_AUX_TAP_ETPU_COMMAND   (0x12)
#define ACCESS_AUX_TAP_NXDM_COMMAND   (0x13)
#define ACCESS_AUX_TAP_NXFR_COMMAND   (0x14)

//---------------------------------------------
#define JTAG_IDCODE_LENGTH            (32)

// EONCE Command register details
//-------------------------------------------------------------------
#define ONCE_CMD_LENGTH  (10)

// The following bit masks may be combined
#define ONCE_CMD_READ            (1<<9)   // Read from register
#define ONCE_CMD_WRITE           (0<<9)   // Write to register
#define ONCE_CMD_GO              (1<<8)   // Execute target instruction
#define ONCE_CMD_EXIT            (1<<7)   // Exit debug mode

// Register field - some commonly used reg addresses define here
#define JTAG_DID_ADDRESS         (0x02)
#define CPUSCR_ADDRESS           (0x10)
#define NOREG_ADDRESS            (0x11)
#define OCR_ADDRESS              (0x12)
#define IAC1_ADDRESS             (0x20)
#define IAC2_ADDRESS             (0x21)
#define IAC3_ADDRESS             (0x21)
#define IAC4_ADDRESS             (0x23)
#define DAC1_ADDRESS             (0x24)
#define DAC2_ADDRESS             (0x25)
#define DVC1_ADDRESS             (0x26)
#define DVC2_ADDRESS             (0x27)
#define IAC5_ADDRESS             (0x28)
#define IAC6_ADDRESS             (0x29)
#define IAC7_ADDRESS             (0x2A)
#define IAC8_ADDRESS             (0x2B)
#define DBCNT_ADDRESS            (0x2C)
#define PCFIFO_ADDRESS           (0x2D)
#define EDBCR0_ADDRESS           (0x2E)
#define EDBSR0_ADDRESS           (0x2F)
#define DBSR_ADDRESS             (0x30)
#define DBCR0_ADDRESS            (0x31)
#define DBCR1_ADDRESS            (0x32)
#define DBCR2_ADDRESS            (0x33)
#define DBCR3_ADDRESS            (0x34)
#define DBCR4_ADDRESS            (0x35)
#define DBCR5_ADDRESS            (0x36)
#define DBCR6_ADDRESS            (0x37)
#define DDAM_ADDRESS             (0x3D)
#define DEVENT_ADDRESS           (0x3E)
#define DBERC0_ADDRESS           (0x3F)
#define CDACNTL_ADDRESS          (0x7A)
#define CDADATA_ADDRESS          (0x7B)
#define NX3ACC_ADDRESS           (0x7C)
#define LSRL_ADDRESS             (0x7D)
#define EnONCE_ADDRESS           (0x7E)
#define BYPASS_ADDRESS           (0x7F)

// EONCE_OCR ONCE Control Register Bit masks
//--------------------------------------------------------------------
#define OCR_ERLO                 (1<<7)
#define OCR_PWU                  (1<<5)
#define OCR_DEVEN                (1<<4)   // Debug Event Enable
#define OCR_LTE                  (1<<3)   // Limit Trigger Enable
#define OCR_ISC_MASK             (0x07)
#define OCR_ISC_0                (0x00)
#define OCR_ISC_1                (0x01)
#define OCR_ISC_2                (0x02)
#define OCR_ISC_3                (0x03)
#define OCR_ISC_4                (0x04)
#define OCR_ISC_SINGLE_STEP      (0x05)
#define OCR_ISC_6                (0x06)
#define OCR_ISC_7                (0x07)

// EONCE_OCR ONCE Status Register Bit masks
//--------------------------------------------------------------------
#define OSR_CZ                   (1<<2)   // Counter Zero?
#define OSR_CS                   (1<<3)   // Counter Stopped?
#define OSR_TBFL                 (1<<12)  // Trace Buffer Full?

#define OTBCR_TBH                (1<<2)   // Trace Buffer Halt

//==============================================
// Some Target register details

// Flash
#define HFM_BASE            (0xF400)
#define FM_CLKDIV           (HFM_BASE+0x00)
#define FM_CNFG             (HFM_BASE+0x01)
#define FM_SECLO            (HFM_BASE+0x04)
#define FM_SECHI            (HFM_BASE+0x03)
#define FM_PROT             (HFM_BASE+0x10)
#define FM_RES1             (HFM_BASE+0x11)
#define FM_USTAT            (HFM_BASE+0x13)
#define FM_CMD              (HFM_BASE+0x14)

#define FM_CMD_RDARY1       (0x05) // Erase Verify (All Ones)
#define FM_CMD_RDARYM       (0x06) // Data Compress Flash Unit Data
#define FM_CMD_PGM          (0x20) // Word Program
#define FM_CMD_PGERS        (0x40) // Page Erase
#define FM_CMD_MASERS       (0x41) // Mass Erase
#define FM_CMD_RDARYMI      (0x66) // Data Compress Factory Stored Configuration Data

// COP
#define  COP_CTRL           (0x00F140)   // COP
#define  COP_TOUT           (0x00F141)   // COP
#define  COP_CNTR           (0x00F142)   // COP

// GPIOA
#define  GPIOA_PUR          (0x00F180)   // GPIOA
#define  GPIOA_DR           (0x00F181)   // GPIOA
#define  GPIOA_DDR          (0x00F182)   // GPIOA
#define  GPIOA_PER          (0x00F183)   // GPIOA
#define  GPIOA_IENR         (0x00F185)   // GPIOA
#define  GPIOA_IPOLR        (0x00F186)   // GPIOA
#define  GPIOA_IPR          (0x00F187)   // GPIOA
#define  GPIOA_IESR         (0x00F188)   // GPIOA
#define  GPIOA_RAWDATA      (0x00F18A)   // GPIOA
#define  GPIOA_DRIVE        (0x00F18B)   // GPIOA
#define  GPIOA_IFE          (0x00F18C)   // GPIOA
#define  GPIOA_SLEW         (0x00F18D)   // GPIOA


//! Converts the status returned from the Core JTAG
//! into OnceStatus_t values
//!
OnceStatus_t convertStatus(uint8_t coreStatus);

//! Send DebugRequest to target
//!
//! @note Assumes Core TAP is active & in RUN-TEST/IDLE
//! @note Leaves Core TAP in RUN-TEST/IDLE
//!
USBDM_ErrorCode forceDebugRequest();

//! Enable the Core TAP using the TLM
//!
//! @note - Resets the TAPs before enabling Core TAP
//! @note - It appears that the sequence must end with a EXIT_SHIFT_DR?
//! @note Leaves Core TAP in RUN-TEST/IDLE to TLM action??
//!
USBDM_ErrorCode enableEonceTAP();

//! Read IDCODE from JTAG TAP
//!
//! @param idCode           - 32-bit IDCODE returned from TAP
//! @param resetTAP         - Optionally resets the TAP to RUN-TEST/IDLE before reading IDCODE
//!
//! @note - resetTAP=true will enable the Master TAP & disable the Code TAP
//! @note - Leaves Core TAP in RUN-TEST/IDLE
//!
USBDM_ErrorCode readIDCODE(uint32_t *idCode, int resetTAP);

//!  Execute a series of target instructions
//!
//! @param instructionSequence - Instruction sequence in the following form:\n
//!      - [0] L        - # of instructions
//!      - [1] M        - # of words in 1st instruction
//!      - [2..2*M+1]   - code for 1st instruction
//!      - The above two lines may be repeated  a further (L-1) times
//!
//! @note - These instructions are executed one at a time using the ONCE interface!
//! @note - Assumes Core TAP is active & in RUN-TEST/IDLE
//! @note - Leaves Core TAP in RUN-TEST/IDLE
//!
USBDM_ErrorCode DSC_ExecuteTargetInstruction(uint8_t *instructionSequence);

//! Read Core register via ONCE & target execution
//!
//! @param regNo     - Register number
//! @param regValue  - Value for register
//!
//! @note Assumes Core TAP is active & in RUN-TEST/IDLE
//! @note Leaves Core TAP in RUN-TEST/IDLE
//!
USBDM_ErrorCode readCoreReg(DSC_Registers_t regNo, uint32_t *regValue);

//! Write Core register via ONCE & target execution
//!
//! @param regNo     - Register number
//! @param regValue  - Value for register
//!
//! @note Assumes Core TAP is active & in RUN-TEST/IDLE
//! @note Leaves Core TAP in RUN-TEST/IDLE
//!
USBDM_ErrorCode writeCoreReg(DSC_Registers_t regNo, uint32_t regValue);

//! Read ONCE register
//!
//! @param regNo    - Register number
//! @param regValue - Value from register
//!
//! @note Assumes Core TAP is active & in RUN-TEST/IDLE
//! @note Leaves Core TAP in RUN-TEST/IDLE
//!
USBDM_ErrorCode readONCEReg(int regNo, unsigned long *regValue);

//! Write ONCE register
//!
//! @param regNo     - Register number
//! @param modifiers - Modifier for command byte to ONCE_OCR register
//! @param regValue  - Value for register
//!
//! @note Assumes Core TAP is active & in RUN-TEST/IDLE
//! @note Leaves Core TAP in RUN-TEST/IDLE
//!
USBDM_ErrorCode writeONCEReg(int regNo, uint32_t regValue, uint8_t modifiers=0);

//! Enable ONCE in JTAG chain & Obtain status
//!
//! @param status - Target status from JTAG command
//!
//! @note Assumes Core TAP is active & in RUN-TEST/IDLE
//! @note Leaves Core TAP in RUN-TEST/IDLE
//!
USBDM_ErrorCode enableONCE(OnceStatus_t *status);

USBDM_ErrorCode readONCEStatus(unsigned long *regValue);

USBDM_ErrorCode targetMassErase(void);

typedef struct {
   uint32_t  WBBRL;
   uint32_t  WBBRH;
   uint32_t  MSR;
   uint32_t  PC;
   uint32_t  IR;
   uint32_t  CTL;
} CpuscrT;

//! Write CPUSCR register
//!
//! @param regValues - Value for registers
//!
//! @note Assumes Core TAP is active & in RUN-TEST/IDLE
//! @note Leaves Core TAP in RUN-TEST/IDLE
//!
USBDM_ErrorCode writeCPUSCRRegs(CpuscrT *regValues);

//! Read CPUSCR registers
//!
//! @param regValues - Value from registers
//!
//! @note Assumes Core TAP is active & in RUN-TEST/IDLE
//! @note Leaves Core TAP in RUN-TEST/IDLE
//!
USBDM_ErrorCode readCPUSCRRegs(CpuscrT *regValues);

#endif /* USBDM_DSC_API_AUX_H_ */
