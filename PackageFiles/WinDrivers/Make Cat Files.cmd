@echo off

set INF_2_CAT=F:\Apps\WinDDK\7600.16385.1\bin\selfsign\Inf2Cat.exe

echo Creating CAT files
%INF_2_CAT% /driver:Drivers /os:XP_X86,XP_X64,7_X86,7_X64,Vista_X86,Vista_X64

pause