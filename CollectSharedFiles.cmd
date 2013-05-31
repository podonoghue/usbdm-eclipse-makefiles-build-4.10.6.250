@echo off

rem This command file copies DLLs that are needed for the build 
rem to a shared library directory %SHARED_LIB%.
rem Some of these DLLs are created by the build process so this file
rem will need to be run multiple times.
rem
rem It also should be run when any of the built & shared DLLs change!

rem Where Eclipse files are
set ECLIPSE_HOME=.

rem Where reference copies of external DLLs are kept
set EXTERNAL_LIB=%ECLIPSE_HOME%\PackageFiles\ExternalDLLs

rem Where DLLs to link against are kept
set SHARED_LIB=%ECLIPSE_HOME%\Shared_V4\Lib

if not exist "%SHARED_LIB%" mkdir "%SHARED_LIB%"

rem External DLLs
copy "%EXTERNAL_LIB%\*.*"                                 %SHARED_LIB%

rem DLLs that are produced as part of USBDM build
rem The make process no copies these
rem copy "wxPlugin_DLL\usbdm-wxPlugin\*.dll"                  %SHARED_LIB%
rem copy "USBDM_DLL\usbdm\*.dll"                              %SHARED_LIB%
rem copy "USBDM_DLL\usbdm-debug\*.dll"                        %SHARED_LIB%
rem copy "USBDM_DSC_DLL\usbdm-dsc\*.dll"                      %SHARED_LIB%
rem copy "USBDM_DSC_DLL\usbdm-dsc-debug\*.dll"                %SHARED_LIB%
rem copy "Usbdm_Tcl\UsbdmTcl\*.dll"                           %SHARED_LIB%
rem copy "Usbdm_Tcl\UsbdmTcl-debug\*.dll"                     %SHARED_LIB%
rem copy "UsbdmJniWrapper_dll\UsbdmJniWrapper\*.dll"          %SHARED_LIB%
rem copy "UsbdmJniWrapper_dll\UsbdmJniWrapper-debug\*.dll"    %SHARED_LIB%

pause
