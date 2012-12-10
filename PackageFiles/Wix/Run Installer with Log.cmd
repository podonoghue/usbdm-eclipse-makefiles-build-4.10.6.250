@echo off
cls
set VERSION=4_10_4
set MSI_FILE=USBDM_%VERSION%_Win

msiexec /i %MSI_FILE% /l*v usbdmInstall.log