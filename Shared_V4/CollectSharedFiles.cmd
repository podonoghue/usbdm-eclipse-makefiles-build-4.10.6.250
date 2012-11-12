@echo off

rem Where reference copies of external DLLs are kept
set EXTERNAL_LIB=PackageFiles\ExternalDLLs

rem Where DLLs to link against are kept
set SHARED_LIB=Shared_V4\Lib

rem External DLLs
copy "%EXTERNAL_LIB%\*.*"                                 %SHARED_LIB%

rem DLLs that are produced as part of USBDM
copy "wxPlugin_DLL\wxPlugin\*.dll"                        %SHARED_LIB%
copy "USBDM_DLL\usbdm\*.dll"                              %SHARED_LIB%
copy "USBDM_DLL\usbdm-debug\*.dll"                        %SHARED_LIB%
copy "USBDM_DSC_DLL\usbdm-dsc\*.dll"                      %SHARED_LIB%
copy "USBDM_DSC_DLL\usbdm-dsc-debug\*.dll"                %SHARED_LIB%
copy "Usbdm_Tcl\UsbdmTcl\*.dll"                           %SHARED_LIB%
copy "Usbdm_Tcl\UsbdmTcl-debug\*.dll"                     %SHARED_LIB%
copy "UsbdmJniWrapper_dll\UsbdmJniWrapper\*.dll"          %SHARED_LIB%
copy "UsbdmJniWrapper_dll\UsbdmJniWrapper-debug\*.dll"    %SHARED_LIB%

pause
