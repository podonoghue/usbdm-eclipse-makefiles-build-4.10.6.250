@echo off

rem echo =============================
rem echo not active
rem echo =============================
rem pause
rem exit

rem This command file copies external DLLs that are needed for the build 
rem to a shared library directory %EXTERNAL_LIB%.
rem CollectSharedFiles copies these to %SHARED_LIB% along with other provided files

rem Where Eclipse files are
set ECLIPSE_HOME=.

rem set SHARED_LIB=%ECLIPSE_HOME%\Shared_V4\Lib

rem Where reference copies of external DLLs are kept
set EXTERNAL_LIB=%ECLIPSE_HOME%\PackageFiles\ExternalDLLs

set XERCES_LIB=C:\Apps\xerces-c-3.1.1\src\.libs
set XERCES_LIB_LIST=libxerces-c-3-1

set MINGW_BIN=C:\Apps\MinGW\bin
set MINGW_LIB_LIST= libgcc_s_dw2-1 libstdc++-6 pthreadGC2

set WXWIDGETS_LIB=C:\Apps\wxWidgets-2.9.4\lib\gcc_dll
set WXWIDGETS_LIB_LIST= wxmsw294u_adv_gcc_custom wxmsw294u_core_gcc_custom wxbase294u_gcc_custom 
rem set WXWIDGETS_LIB_LIST= %WXWIDGETS_LIB_LIST% wxmsw294u_richtext_gcc_custom wxbase294u_xml_gcc_custom wxmsw294u_html_gcc_custom.dll

set TCL_LIB=C:\Apps\tcl\bin
set TCL_LIB_LIST= tcl86

if not exist "%EXTERNAL_LIB%" mkdir "%EXTERNAL_LIB%"

for %%f in (%MINGW_LIB_LIST%) do copy "%MINGW_BIN%\%%f.*" %EXTERNAL_LIB%

for %%f in (%WXWIDGETS_LIB_LIST%) do copy "%WXWIDGETS_LIB%\%%f.*" %EXTERNAL_LIB%

for %%f in (%XERCES_LIB_LIST%) do copy "%XERCES_LIB%\%%f.*" %EXTERNAL_LIB%

for %%f in (%TCL_LIB_LIST%) do copy "%TCL_LIB%\%%f.*" %EXTERNAL_LIB%

pause
