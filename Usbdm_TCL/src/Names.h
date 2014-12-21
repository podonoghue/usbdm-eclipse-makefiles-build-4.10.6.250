/*!
 * \brief Header file for CmdTable.c
*/
#ifndef _NAMES_H_
#define _NAMES_H_


char const *getCommandName(unsigned char command);
char const *getDebugCommandName(unsigned char cmd);
char const *getDFUCommandName(unsigned char command);
char const *getCFV1RegName( unsigned int regAddr );
char const *getCFVxRegName( unsigned int regAddr );
char const *getARMRegName( unsigned int regAddr );
char const *getDSCRegName( unsigned int regNum);
char const *getHCS12RegName( unsigned int regAddr );
char const *getS12ZRegName( unsigned int regAddr );
char const *getHCS08RegName( unsigned int regAddr );
char const *getRS08RegName( unsigned int regAddr );
char const *getRegName( unsigned int targetType, unsigned int regAddr );
char const *getHCS12DebugRegName( unsigned int regAddr );
char const *getCFV1DebugRegName( unsigned int regAddr );
char const *getCFVxDebugRegName( unsigned int regAddr );
char const *getSWDDebugRegName( unsigned int regAddr );
char const *getCFV1ControlRegName( unsigned int regAddr );
char const *getCFVxControlRegName( unsigned int regAddr );
char const *getARMControlRegName( unsigned int regAddr );
char const *getRS08_BDCSCR_Name( unsigned int BDCSCR);
char const *getHCS08_BDCSCR_Name( unsigned int BDCSCR);
char const *getHCS12ZVM_BDMSTS_Name( unsigned int BDMSTS);
char const *getHCS12_BDMSTS_Name( unsigned int BDMSTS);
char const *getCFV1_XCSR_Name( unsigned int XCSR);
char const *getCFVx_CSR_Name( unsigned int CSR);
char const *getStatusRegName(unsigned int targetType, unsigned int value);
char const *getCapabilityName(unsigned int cmd);
char const *getTargetModeName(TargetMode_t type);
char const *getControlLevelName(InterfaceLevelMasks_t level);
char const *getClockSelectName(ClkSwValues_t level);
char const *getVoltageStatusName(TargetVddState_t level);
char const *getVoltageSelectName(TargetVddSelect_t level);
char const *getVppSelectName(TargetVppSelect_t level);
char const *getPinLevelName(PinLevelMasks_t level);
char const *getExitAction(int action);
char const *getDHCSRName(uint32_t dhcsrValue);
char const *getDEMCRName(uint32_t demcrValue);
char const *getMDM_APControlName(uint32_t mdmApValue);
char const *getMDM_APStatusName(uint32_t mdmApValue);
char const *getAutoConnectName(AutoConnect_t mode);
//char const *getConnectionRetryName(RetryMode mode);
char const *getMemSpaceName(MemorySpace_t memSpace);
char const *getMemSpaceAbbreviatedName(MemorySpace_t memSpace);
char const *getStatusRegName(unsigned int targetType, unsigned int value);
void printBdmOptions(const USBDM_ExtendedOptions_t *options);
#endif // LOG

char const *getHardwareDescription(unsigned int hardwareVersion);
char const *getBriefHardwareDescription(unsigned int hardwareVersion);
char const *getTargetTypeName( unsigned int type );
char const *getBDMStatusName(USBDMStatus_t *USBDMStatus);
char const *getICPErrorName(unsigned char error);
char const *getErrorName(unsigned int error);
char const *getSRSLName(uint32_t srslValue);
char const *getSRSHName(uint32_t srshValue);
char const *getDpRegName(int reg);
char const *ARM_GetRegisterName( unsigned int regAddr );
