@echo off
cls
rem ***  Paths to various things
set VERSION_NUMBER=4
set VERSION_MINOR_NUMBER=10
set VERSION_SUFFIX=_V%VERSION_NUMBER%
set VERSION_MINOR_SUFFIX=_V%VERSION_NUMBER%_%VERSION_MINOR_NUMBER%

rem where to find applications (Eclipse folder)
set APP_ROOT=..\EclipseUSBDM

rem where to find applications (Eclipse folder)
set PLUGIN_ROOT=..\EclipsePlugin

rem where to find documentation (Eclipse folder)
set DOC_ROOT=..\EclipseUSBDM

rem where to find JMxx/JS16 firmware
set CW_JB16_ROOT=..\USBDM_JB16%VERSION_MINOR_SUFFIX%
set CW_JMxx_ROOT=..\CodewarriorUSBDM\USBDM_JMxx%VERSION_MINOR_SUFFIX%
set CW_Kinetis_ROOT=..\CodewarriorUSBDM\USBDM_Kinetis

rem where to find PCBs
set PCB_ROOT=..\PCB

set WIN_RAR=c:\Program Files\WinRAR\rar.exe
set HW_VERSION=4_0_0
set INSTALLATION_DIR=1. Installation
set LINUX32_INSTALLATION_DIR=%INSTALLATION_DIR%\Linux32
set DOCUMENTATION_INSTALLATION_DIR=%INSTALLATION_DIR%\Documentation
set WIN32_APPLICATION_DIR=%INSTALLATION_DIR%\WinApplications
set BIN_DIR=%WIN32_APPLICATION_DIR%\bin
set INSTALL_DIR=%WIN32_APPLICATION_DIR%\Install
set FLASH_DIR=%BIN_DIR%\FlashImages
set SOURCE_DIR=2. Source
set PCB_DESTINATION=3. PCB
set DLL_VER=USBDM_DLL_V4

if not exist "%INSTALLATION_DIR%"                 mkdir "%INSTALLATION_DIR%"
if not exist "%WIN32_APPLICATION_DIR%"            mkdir "%WIN32_APPLICATION_DIR%"
if not exist "%LINUX32_INSTALLATION_DIR%"         mkdir "%LINUX32_INSTALLATION_DIR%"
if not exist "%DOCUMENTATION_INSTALLATION_DIR%"   mkdir "%DOCUMENTATION_INSTALLATION_DIR%"

echo ***  ****************************************
echo ***  Do Win32 bin
echo ***  ****************************************
if not exist "%BIN_DIR%"           mkdir "%BIN_DIR%"

echo ***  ****************************************
echo ***  Do Configuration Files
echo ***  ****************************************
echo ***  Stationery
xcopy /E /I /Y /Q "%APP_ROOT%\PackageFiles\Stationery"                  "%BIN_DIR%\Stationery"
echo ***  DeviceData ...
xcopy /E /I /Y /Q "%APP_ROOT%\PackageFiles\DeviceData"                  "%BIN_DIR%\DeviceData"
echo ***  Examples ...
xcopy /E /I /Y /Q "%APP_ROOT%\PackageFiles\Examples"                    "%WIN32_APPLICATION_DIR%\Examples"
echo ***  LaunchConfig ...
xcopy /E /I /Y /Q "%APP_ROOT%\PackageFiles\LaunchConfig"                "%WIN32_APPLICATION_DIR%\LaunchConfig"
echo ***  WizardPatches ...
xcopy /E /I /Y /Q "%APP_ROOT%\PackageFiles\WizardPatches"               "%WIN32_APPLICATION_DIR%\WizardPatches"
echo ***  Wix ...
xcopy /E /I /Y /Q "%APP_ROOT%\PackageFiles\Wix"                         "%WIN32_APPLICATION_DIR%"

echo *** Command line programmer tests
copy "%APP_ROOT%\PackageFiles\MiscellaneousWin\TryProgrammer.cmd"       "%BIN_DIR%"
copy "%APP_ROOT%\PackageFiles\MiscellaneousWin\MakeTestImages.cmd"      "%BIN_DIR%"
copy "%APP_ROOT%\PackageFiles\Miscellaneous\*.s19"                      "%BIN_DIR%"
copy "%APP_ROOT%\PackageFiles\Miscellaneous\*.wav"                      "%BIN_DIR%"

rem List of Targets supported by Programmers
set PROGRAMMER_TARGETS=ARM HCS12 HCS08 RS08 CFV1 CFVx DSC
echo ***  Programmers (%PROGRAMMER_TARGETS%) ...
for %%f in (%PROGRAMMER_TARGETS%) do copy "%APP_ROOT%"\%%f_Interface\%%f_FlashProgrammer\*.exe         "%BIN_DIR%"
for %%f in (%PROGRAMMER_TARGETS%) do copy "%APP_ROOT%"\%%f_Interface\%%f_FlashProgrammer-debug\*.exe   "%BIN_DIR%"

set UTILTITIES_PROGS=FirmwareChanger MergeXML SetBoot JS16_Bootloader
echo ***  Utilities (%UTILTITIES_PROGS%) ...
for %%f in (%UTILTITIES_PROGS%) do copy "%APP_ROOT%\%%f\%%f\*.exe"       "%BIN_DIR%"
for %%f in (%UTILTITIES_PROGS%) do copy "%APP_ROOT%\%%f\%%f-debug\*.exe" "%BIN_DIR%"

set UNLOCKER_PROGS=CFVx_Unlocker CFVx_Unlocker-debug DSC_Unlocker DSC_Unlocker-debug
echo ***  Unlockers (%UNLOCKER_PROGS%) ...
for %%f in (%UNLOCKER_PROGS%) do copy "%APP_ROOT%\Unlocker\%%f\*.exe" "%BIN_DIR%"

echo ***  UsbdmScript ...
copy "%APP_ROOT%\Usbdm_TCL\UsbdmScript\*.exe"                             "%BIN_DIR%"
copy "%APP_ROOT%\Usbdm_TCL\UsbdmScript-debug\*.exe"                       "%BIN_DIR%"
echo ***  TCL DLLs ...
copy "%APP_ROOT%\Usbdm_TCL\UsbdmTCL\*.dll"                                "%BIN_DIR%"
copy "%APP_ROOT%\Usbdm_TCL\UsbdmTCL-debug\*.dll"                          "%BIN_DIR%"
echo ***  CreateFlashTestImage ...
copy "%APP_ROOT%\CreateFlashTestImage\CreateFlashTestImage\*.exe"         "%BIN_DIR%"

echo ***  Shared_V4\lib ...
copy "%APP_ROOT%\Shared_V4\lib\*.dll"                        "%BIN_DIR%"
copy "%APP_ROOT%\Shared_V4\src\*.ico"                        "%BIN_DIR%"

echo ***  USBDM DLL ...
copy "%APP_ROOT%\Usbdm_DLL\usbdm\*.dll"                      "%BIN_DIR%"
copy "%APP_ROOT%\Usbdm_DLL\usbdm-debug\*.dll"                "%BIN_DIR%"
echo ***  ARM DLL ...
copy "%APP_ROOT%\USBDM_ARM_DLL\usbdm-arm\*.dll"              "%BIN_DIR%"
copy "%APP_ROOT%\USBDM_ARM_DLL\usbdm-arm-debug\*.dll"        "%BIN_DIR%"
echo ***  DSC DLL ...
copy "%APP_ROOT%\USBDM_DSC_DLL\usbdm-dsc\*.dll"              "%BIN_DIR%"
copy "%APP_ROOT%\USBDM_DSC_DLL\usbdm-dsc-debug\*.dll"        "%BIN_DIR%"
copy "%APP_ROOT%\wxPlugin_DLL\usbdm-wxPlugin\*.dll"          "%BIN_DIR%"

echo ***  MyCustomAction ...
copy "%APP_ROOT%\MyCustomAction\MyCustomAction\*.dll"        "%BIN_DIR%"

echo ***  ReadMeWizard ...
copy "%APP_ROOT%\PackageFiles\WizardPatches\ReadMeWizard.txt" "%BIN_DIR%"

echo ***  Copy licences ...
if not exist "%INSTALLATION_DIR%\Licenses"             mkdir "%INSTALLATION_DIR%\Licenses"
copy "%APP_ROOT%\PackageFiles\Licenses\*.*"                  "%INSTALLATION_DIR%\Licenses"

echo ***  Copy TCL Scripts ...
copy "%APP_ROOT%\PackageFiles\scripts\*.tcl"                  "%BIN_DIR%"

echo ***  ****************************************
echo ***  Do documentation Files
echo ***  ****************************************
echo copy "%DOC_ROOT%\Documentation\External\*.chm"     "%DOCUMENTATION_INSTALLATION_DIR%"
copy "%DOC_ROOT%\Documentation\External\*.chm"          "%DOCUMENTATION_INSTALLATION_DIR%"

echo ***  ****************************************
echo ***  Do DLLs (GDI + USBDM etc) Files
echo ***  ****************************************
if not exist "%INSTALL_DIR%"                 mkdir "%INSTALL_DIR%"
if not exist "%INSTALL_DIR%\CW_10_x"         mkdir "%INSTALL_DIR%\CW_10_x"
if not exist "%INSTALL_DIR%\Legacy"          mkdir "%INSTALL_DIR%\Legacy"

echo *** Copy DLLS
copy "%APP_ROOT%\Usbdm_DLL\osbdm\*.dll"                    "%INSTALL_DIR%\Legacy"
copy "%APP_ROOT%\Usbdm_DLL\osbdm-debug\*.dll"              "%INSTALL_DIR%\Legacy"
copy "%APP_ROOT%\Legacy_DLLs\tbdml\*.dll"                  "%INSTALL_DIR%\Legacy"
copy "%APP_ROOT%\Legacy_DLLs\opensourcebdm\*.dll"          "%INSTALL_DIR%\Legacy"
copy "%APP_ROOT%\Legacy_DLLs\tbdml-debug\*.dll"            "%INSTALL_DIR%\Legacy"
copy "%APP_ROOT%\Legacy_DLLs\opensourcebdm-debug\*.dll"    "%INSTALL_DIR%\Legacy"

echo *** Doing Eclipse GDIs (Release, Debug)                                                       
rem List of target having Eclipse GDI support                                                      
set GDI_TARGETS=HCS08 RS08 CFV1 CFVx ARM DSC HCS12                                                 
for %%f in (%GDI_TARGETS%) do copy "%APP_ROOT%"\%%f_Interface\"usbdm-%%f-gdi"\*.dll          "%INSTALL_DIR%\CW_10_x"
for %%f in (%GDI_TARGETS%) do copy "%APP_ROOT%"\%%f_Interface\"usbdm-%%f-gdi-debug"\*.dll    "%INSTALL_DIR%\CW_10_x"

echo *** Doing Legacy GDIs
rem List of target having Legacy GDI support
set GDI_TARGETS=CFVx DSC
for %%f in (%GDI_TARGETS%) do copy "%APP_ROOT%"\%%f_Interface\"usbdm-%%f-gdi-legacy"\*.dll        "%INSTALL_DIR%\Legacy"
for %%f in (%GDI_TARGETS%) do copy "%APP_ROOT%"\%%f_Interface\"usbdm-%%f-gdi-legacy-debug"\*.dll  "%INSTALL_DIR%\Legacy"

echo *** Doing GDB (Release, Debug) X (Pipe, Socket, GUI)
rem List of target having GDB support
set GDB_TARGETS=CFVx CFV1 ARM
for %%f in (%GDB_TARGETS%) do copy "%APP_ROOT%"\%%f_Interface\"usbdm-%%f-gdbPipeServer"\*.exe               "%BIN_DIR%"
for %%f in (%GDB_TARGETS%) do copy "%APP_ROOT%"\%%f_Interface\"usbdm-%%f-gdbPipeServer-debug"\*.exe         "%BIN_DIR%"
for %%f in (%GDB_TARGETS%) do copy "%APP_ROOT%"\%%f_Interface\"usbdm-%%f-gdbSocketServer"\*.exe         "%BIN_DIR%"
for %%f in (%GDB_TARGETS%) do copy "%APP_ROOT%"\%%f_Interface\"usbdm-%%f-gdbSocketServer-debug"\*.exe   "%BIN_DIR%"
for %%f in (%GDB_TARGETS%) do copy "%APP_ROOT%"\%%f_Interface\"%%f_GDBServer"\*.exe                     "%BIN_DIR%"
for %%f in (%GDB_TARGETS%) do copy "%APP_ROOT%"\%%f_Interface\"%%f_GDBServer-debug"\*.exe               "%BIN_DIR%"

echo ***  ****************************************
echo ***  Do Win32 drivers
echo ***  ****************************************
if not exist "%INSTALLATION_DIR%\WinDrivers"                              mkdir "%INSTALLATION_DIR%\WinDrivers"
xcopy /E /I /Y /Q "%APP_ROOT%\PackageFiles\WinDrivers"                          "%INSTALLATION_DIR%\WinDrivers" 

echo *** CFFlasher Files
copy "%APP_ROOT%\PackageFiles\MiscellaneousWin\USBDM-CFFlasher-Readme.txt"         "%BIN_DIR%"
copy "%APP_ROOT%\Usbdm_DLL\usbdm-cff\*.dll"                                        "%BIN_DIR%"
copy "%APP_ROOT%\Usbdm_DLL\usbdm-cff-debug\*.dll"                                  "%BIN_DIR%"

echo **********=================**************
echo **********=================**************
echo **********=================**************
rem goto allDone

echo ***  ****************************************
echo ***  Do Firmware files
echo ***  ****************************************
xcopy /E /I /Y /Q "%APP_ROOT%\PackageFiles\FlashImages"                      "%FLASH_DIR%"

goto allDone

:allDone
pause
