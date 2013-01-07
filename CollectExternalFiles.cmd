@echo off

echo =============================
echo not active
echo =============================
pause
exit

rem Where Eclipse files are
set ECLIPSE_HOME=.

set SHARED_LIB=%ECLIPSE_HOME%\Shared_V4\Lib

set XERCES_LIB=C:\Apps\xerces-c-3.1.1\src\.libs
set XERCES_LIB_LIST=libxerces-c-3-1

set MINGW_BIN=C:\Apps\MinGW\bin
set MINGW_LIB_LIST= libgcc_s_dw2-1 libstdc++-6 pthreadGC2

set WXWIDGETS_LIB=C:\Apps\wxWidgets-2.9.4\lib\gcc_dll
set WXWIDGETS_LIB_LIST= wxmsw294u_adv_gcc_custom wxmsw294u_core_gcc_custom wxbase294u_gcc_custom 
rem set WXWIDGETS_LIB_LIST= %WXWIDGETS_LIB_LIST% wxmsw294u_richtext_gcc_custom wxbase294u_xml_gcc_custom wxmsw294u_html_gcc_custom.dll

for %%f in (%MINGW_LIB_LIST%) do copy "%MINGW_BIN%\%%f.*" %SHARED_LIB%

for %%f in (%WXWIDGETS_LIB_LIST%) do copy "%WXWIDGETS_LIB%\%%f.*" %SHARED_LIB%

for %%f in (%XERCES_LIB_LIST%) do copy "%XERCES_LIB%\%%f.*" %SHARED_LIB%

pause
