@echo off
cls
set VERSION=1_2_0
set VERSIONn=1.2.0

set WIX_DIR="C:\Program Files (x86)\WiX Toolset v3.7\bin"
if not exist %WIX_DIR% set WIX_DIR="C:\Program Files\WiX Toolset v3.7\bin"

set HEAT=%WIX_DIR%\heat.exe
set CANDLE=%WIX_DIR%\candle.exe
set LIGHT=%WIX_DIR%\light.exe
set TORCH=%WIX_DIR%\torch.exe
set PYRO=%WIX_DIR%\pyro.exe

set WIX_BUILD_DIR=wixBuildDir

set CANDLE_OPTIONS=-ext WixUIExtension -ext WixDifxAppExtension.dll

set LIGHT_OPTIONS=-ext WixUIExtension -ext WixUtilExtension -ext WixDifxAppExtension.dll -sw0204 
set LIGHT_DIRS=-b bin\DeviceData -b bin\FlashImages -b WizardPatches -b plugins -b USBDM_Drivers 

set HEAT_OPTIONS=-srd -ke -gg -sfrag -template fragment -sw5150
set MSI_FILE=USBDM_Drivers_%VERSION%_Win
set MSI_FILE_X32=%MSI_FILE%_x32
set MSI_FILE_X64=%MSI_FILE%_x64
set MSI_FILE_XP_X32=%MSI_FILE%XP_x32
set MSI_FILE_XP_X64=%MSI_FILE%XP_x64

if "%1"=="clean" goto doMake
if "%1"==""      goto doMake
echo "Unknown option %1"
goto finish

:doMake
if exist %MSI_FILE_X64%.msi    del %MSI_FILE_X64%.msi
if exist %MSI_FILE_X32%.msi    del %MSI_FILE_X32%.msi
if exist %MSI_FILE_XP_X32%.msi del %MSI_FILE_XP_X32%.msi
if exist %MSI_FILE_XP_X64%.msi del %MSI_FILE_XP_X64%.msi

if "%1"=="clean" goto finish

if not exist %WIX_BUILD_DIR% mkdir %WIX_BUILD_DIR%
rem %HEAT% dir .\bin\Driver                 %HEAT_OPTIONS% -cg Cg.DeviceData      -dr D.DeviceData       -out %WIX_BUILD_DIR%\DeviceData.wxs
rem echo %CANDLE% %CANDLE_OPTIONS% -dProductVersion=%VERSIONn% -dTargetArchCondition="NOT Msix64" -o %WIX_BUILD_DIR%\%MSI_FILE_X32%.wixobj *.wxs
%CANDLE% %CANDLE_OPTIONS% -dProductVersion=%VERSIONn% -dTargetArchCondition="NOT Msix64" -o %WIX_BUILD_DIR%\%MSI_FILE_X32%.wixobj Driver.wxs
rem echo %CANDLE% %CANDLE_OPTIONS% -dProductVersion=%VERSIONn% -dTargetArchCondition="Msix64"     -o %WIX_BUILD_DIR%\%MSI_FILE_X64%.wixobj *.wxs
%CANDLE% %CANDLE_OPTIONS% -dProductVersion=%VERSIONn% -dTargetArchCondition="Msix64"     -o %WIX_BUILD_DIR%\%MSI_FILE_X64%.wixobj Driver.wxs
rem echo %CANDLE% %CANDLE_OPTIONS% -dProductVersion=%VERSIONn% -dTargetArchCondition="NOT Msix64" -o %WIX_BUILD_DIR%\%MSI_FILE_XP_X32%.wixobj *.wxs
%CANDLE% %CANDLE_OPTIONS% -dProductVersion=%VERSIONn% -dTargetArchCondition="NOT Msix64" -o %WIX_BUILD_DIR%\%MSI_FILE_XP_X32%.wixobj XPDriver.wxs
rem echo %CANDLE% %CANDLE_OPTIONS% -dProductVersion=%VERSIONn% -dTargetArchCondition="Msix64"     -o %WIX_BUILD_DIR%\%MSI_FILE_XP_X64%.wixobj *.wxs
%CANDLE% %CANDLE_OPTIONS% -dProductVersion=%VERSIONn% -dTargetArchCondition="Msix64"     -o %WIX_BUILD_DIR%\%MSI_FILE_XP_X64%.wixobj XPDriver.wxs
%LIGHT% %LIGHT_OPTIONS% %LIGHT_DIRS% -out %MSI_FILE_X32%    %WIX_BUILD_DIR%\%MSI_FILE_X32%.wixobj    %WIX_DIR%\difxapp_x86.wixlib
%LIGHT% %LIGHT_OPTIONS% %LIGHT_DIRS% -out %MSI_FILE_X64%    %WIX_BUILD_DIR%\%MSI_FILE_X64%.wixobj    %WIX_DIR%\difxapp_x64.wixlib
%LIGHT% %LIGHT_OPTIONS% %LIGHT_DIRS% -out %MSI_FILE_XP_X32% %WIX_BUILD_DIR%\%MSI_FILE_XP_X32%.wixobj %WIX_DIR%\difxapp_x86.wixlib
%LIGHT% %LIGHT_OPTIONS% %LIGHT_DIRS% -out %MSI_FILE_XP_X64% %WIX_BUILD_DIR%\%MSI_FILE_XP_X64%.wixobj %WIX_DIR%\difxapp_x64.wixlib

del *.wixpdb
rmdir /S /Q %WIX_BUILD_DIR%

goto finish

:finish
pause