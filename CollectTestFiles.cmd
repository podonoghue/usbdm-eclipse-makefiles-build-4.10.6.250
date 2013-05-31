@echo off

rem Where Eclipse files are
set ECLIPSE_HOME=.

rem Where to place test files
set TEST_DIR=%ECLIPSE_HOME%\Tests

rem Where DLLs to link against are kept
set SHARED_LIB=%ECLIPSE_HOME%\Shared_V4\lib
set DEVICE_DATA=%ECLIPSE_HOME%\PackageFiles\DeviceData

if not exist "%TEST_DIR%" mkdir "%TEST_DIR%"

rem External DLLs
copy "%SHARED_LIB%\*.*"                                                                                       "%TEST_DIR%"

rem EXEs that are produced as part of USBDM
set PROGRAMMER_TARGETS=ARM HCS12 HCS08 RS08 CFV1 CFVx DSC
for %%f in (%PROGRAMMER_TARGETS%) do copy "%ECLIPSE_HOME%\%%f_Interface\%%f_FlashProgrammer\*.exe"            "%TEST_DIR%"
for %%f in (%PROGRAMMER_TARGETS%) do copy "%ECLIPSE_HOME%\%%f_Interface\%%f_FlashProgrammer-debug\*.exe"      "%TEST_DIR%"
set UTILTITIES_PROGS=FirmwareChanger MergeXML SetBoot JS16_Bootloader USBDM_API_Example CopyFlash
for %%f in (%UTILTITIES_PROGS%) do copy "%ECLIPSE_HOME%\%%f\%%f\*.exe"                                        "%TEST_DIR%"
for %%f in (%UTILTITIES_PROGS%) do copy "%ECLIPSE_HOME%\%%f\%%f-debug\*.exe"                                  "%TEST_DIR%"
set TCL=UsbdmScript UsbdmScript-debug
for %%f in (%TCL%) do copy "%ECLIPSE_HOME%\Usbdm_TCL\%%f\*.exe"                                               "%TEST_DIR%"

:doit
xcopy /S /Y /I "%DEVICE_DATA%"                                                                     "%TEST_DIR%\DeviceData"
pause
 