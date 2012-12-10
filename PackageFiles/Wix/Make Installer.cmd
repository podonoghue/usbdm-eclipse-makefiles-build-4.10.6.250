@echo off
cls
set VERSION=4_10_4
set VERSIONn=4.10.4

set WIX_DIR="C:\Program Files (x86)\WiX Toolset v3.7\bin"
if not exist %WIX_DIR% set WIX_DIR="C:\Program Files\WiX Toolset v3.7\bin"

set HEAT=%WIX_DIR%\heat.exe
set CANDLE=%WIX_DIR%\candle.exe
set LIGHT=%WIX_DIR%\light.exe
set TORCH=%WIX_DIR%\torch.exe
set PYRO=%WIX_DIR%\pyro.exe

set WIX_BUILD_DIR=wixBuildDir

rem .wxs regenerated Files 
set REBUILT_WXS=DeviceData.wxs FlashImages.wxs WizardPatchData.wxs Examples.wxs EclipsePlugin_1.wxs EclipsePlugin_2.wxs EclipsePlugin_2.wxs

set LIGHT_OPTIONS=-ext WixUIExtension -ext WixUtilExtension -sw0204
set LIGHT_DIRS=-b bin\DeviceData -b bin\FlashImages -b WizardPatches -b Examples -b plugins

set HEAT_OPTIONS=-srd -ke -gg -sfrag -template fragment -sw5150
set MSI_FILE=USBDM_%VERSION%_Win
set PATCH=patch_1_1

if "%1"=="patch" goto doPatch
if "%1"=="clean" goto doMake
if "%1"==""      goto doMake
echo "Unknown option %1"
goto finish

:doMake
rem del %MSI_FILE%.msi

if "%1"=="clean" goto finish

if not exist %WIX_BUILD_DIR% mkdir %WIX_BUILD_DIR%
%HEAT% dir .\bin\DeviceData                 %HEAT_OPTIONS% -cg Cg.DeviceData      -dr D.DeviceData       -out %WIX_BUILD_DIR%\DeviceData.wxs
%HEAT% dir .\bin\FlashImages                %HEAT_OPTIONS% -cg Cg.FlashImages     -dr D.FlashImages      -out %WIX_BUILD_DIR%\FlashImages.wxs
%HEAT% dir .\WizardPatches                  %HEAT_OPTIONS% -cg Cg.WizardPatchData -dr D.WizardPatchData  -out %WIX_BUILD_DIR%\WizardPatchData.wxs
%HEAT% dir .\Examples                       %HEAT_OPTIONS% -cg Cg.Examples        -dr D.Examples         -out %WIX_BUILD_DIR%\Examples.wxs
%HEAT% dir .\plugins                        %HEAT_OPTIONS% -cg Cg.EclipsePlugin_1 -dr D.EclipsePlugin_1  -out %WIX_BUILD_DIR%\EclipsePlugin_1.wxs
%HEAT% dir .\plugins                        %HEAT_OPTIONS% -cg Cg.EclipsePlugin_2 -dr D.EclipsePlugin_2  -out %WIX_BUILD_DIR%\EclipsePlugin_2.wxs
%HEAT% dir .\plugins                        %HEAT_OPTIONS% -cg Cg.EclipsePlugin_3 -dr D.EclipsePlugin_3  -out %WIX_BUILD_DIR%\EclipsePlugin_3.wxs
%CANDLE% -dProductVersion=%VERSIONn% -o %WIX_BUILD_DIR%\ *.wxs %WIX_BUILD_DIR%\*.wxs
%LIGHT% %LIGHT_OPTIONS% %LIGHT_DIRS% -out %MSI_FILE% %WIX_BUILD_DIR%\*.wixobj

del *.wixpdb
rmdir /S /Q %WIX_BUILD_DIR%

goto finish
:doPatch

%TORCH% -p -xi USBDM_4_9_0_Win.wixpdb %MSI_FILE%.wixpdb -out %PATCH%\diff.wixmst

%CANDLE% %PATCH%.wxs
%LIGHT%  %PATCH%.wixobj -out %PATCH%\%PATCH%.wixmsp
%PYRO%   %PATCH%\%PATCH%.wixmsp -out %PATCH%\%PATCH%.msp -t USBDMPatch %PATCH%\diff.wixmst

:finish
pause