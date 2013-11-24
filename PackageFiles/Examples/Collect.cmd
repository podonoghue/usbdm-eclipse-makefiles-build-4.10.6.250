@echo off

set PROG_DIR=c:\Program Files
set ZIP_COMMAND="%PROG_DIR%\7-Zip\7z.exe"

set PROJECTS=
set PROJECTS=%PROJECTS% MCF51JF128_Tower MCF51JF128_Tower_Demo
set PROJECTS=%PROJECTS% MCF52233_cpp 
set PROJECTS=%PROJECTS% MK20DX128M5_FRDM MK20DX128M5_FRDM_Demo MK20DX128M5_FRDM_ColourLCD MK20DX128M5_cmsis_rtos
set PROJECTS=%PROJECTS% MK40DX256Z_Tower MK40DX256Z_Tower_Serial 
set PROJECTS=%PROJECTS% MK60DN512Z_Tower MK60DN512Z_Tower_Serial 
set PROJECTS=%PROJECTS% MKE02Z64M2_FRDM_Serial
set PROJECTS=%PROJECTS% MKL02Z32M4_FRDM  MKL02Z32M4_FRDM_Serial
set PROJECTS=%PROJECTS% MKL05Z32M4_FRDM  MKL05Z32M4_FRDM_Serial
set PROJECTS=%PROJECTS% MKL25Z128M4_FRDM MKL25Z128M4_FRDM_Demo MKL25Z128M4_FRDM_DemoCPP
set PROJECTS=%PROJECTS% MKL26Z128M4_FRDM MKL26Z128M4_FRDM_Serial
set PROJECTS=%PROJECTS% MKL46Z256M4_FRDM MKL46Z256M4_FRDM_Serial
set PROJECTS=%PROJECTS% STM32_cmsis_rtos
set PROJECTS=%PROJECTS% USBDM_API_Example

echo *** Cleaning %PROJECTS%
for %%f in (%PROJECTS%) do if exist %%f\Debug   rmdir /S /Q %%f\Debug
for %%f in (%PROJECTS%) do if exist %%f\Release rmdir /S /Q %%f\Release
for %%f in (%PROJECTS%) do if exist "%%f\Thread Example" rmdir /S /Q "%%f\Thread Example"
for %%f in (%PROJECTS%) do if exist "%%f\Timer Example" rmdir /S /Q "%%f\Timer Example"

for %%f in (%PROJECTS%) do if exist %%f %ZIP_COMMAND% a -tzip %%f.zip %%f