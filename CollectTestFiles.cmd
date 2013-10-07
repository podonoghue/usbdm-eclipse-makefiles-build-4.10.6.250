@echo off

rem Where Eclipse files are
set ECLIPSE_HOME=.

rem Where to place test files
set TEST_DIR=%ECLIPSE_HOME%\Tests

rem Where DLLs to link against are kept
set DEVICE_DATA=%ECLIPSE_HOME%\PackageFiles\DeviceData

if not exist "%TEST_DIR%" mkdir "%TEST_DIR%"

rem External DLLs
copy "%SHARED_LIB%\*.*"                                                                                       "%TEST_DIR%"

rem Executables that are produced as part of USBDM
xcopy /E /I /Y /Q "%ECLIPSE_HOME%\PackageFiles\bin"                  "%TEST_DIR%"

rem Misc commands
xcopy /E /I /Y /Q "%ECLIPSE_HOME%\PackageFiles\Miscellaneous\"*.tcl  "%TEST_DIR%"

:doit
xcopy /S /Y /I "%DEVICE_DATA%"                                       "%TEST_DIR%\DeviceData"
pause
 