@echo off

set PROG_DIR=c:\Program Files (x86)
set ZIP_COMMAND="%PROG_DIR%\7-Zip\7z.exe"

set PROJECTS=
set PROJECTS=%PROJECTS% MK20DX128M5_FRDM MK20DX128M5_FRDM_Serial MK20DX128M5_FRDM_ColourLCD 
set PROJECTS=%PROJECTS% MKL05Z32M4_FRDM  MKL05Z32M4_FRDM_Serial
set PROJECTS=%PROJECTS% MKL25Z128M4_FRDM MKL25Z128M4_FRDM_Serial
set PROJECTS=%PROJECTS% MK40DX256Z_Tower MK40DX256Z_Tower_Serial 
set PROJECTS=%PROJECTS% MK60DN512Z_Tower MK60DN512Z_Tower_Serial 
set PROJECTS=%PROJECTS% MCF51JF128_Tower MCF51JF128_Tower_Serial 
set PROJECTS=%PROJECTS% stm32f-example 
set PROJECTS=%PROJECTS% MCF52233_cpp 
set PROJECTS=%PROJECTS% USBDM_API_Example

echo *** Cleaning %PROJECTS%
for %%f in (%PROJECTS%) do if exist %%f\Debug   rmdir /S /Q %%f\Debug
for %%f in (%PROJECTS%) do if exist %%f\Release rmdir /S /Q %%f\Release

for %%f in (%PROJECTS%) do if exist %%f %ZIP_COMMAND% a -tzip %%f.zip %%f