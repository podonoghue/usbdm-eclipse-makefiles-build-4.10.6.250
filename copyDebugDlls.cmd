@echo off

set SRC=C:\Users\Peter\Development\USBDM\EclipseUSBDM\Tests
set DEST1=C:\Users\Peter\Development\USBDM\EclipseUSBDM\ARM_Interface\ARM_FlashProgrammer-debug
set DEST2=C:\Users\Peter\Development\USBDM\EclipseUSBDM\ARM_Interface\ARM_GDBServer-debug
set DEST2=C:\Users\Peter\Development\USBDM\EclipseUSBDM\ARM_Interface\usbdm-arm-gdbPipeServer-debug

echo copy %SRC%\*.dll %DEST1%\*.dll
copy %SRC%\*.dll %DEST1%
echo copy %SRC%\*.dll %DEST2%\*.dll
copy %SRC%\*.dll %DEST2%
echo copy %SRC%\*.dll %DEST3%\*.dll
copy %SRC%\*.dll %DEST3%

pause