@echo off
SET THEFILE=C:\Work\DrvTools\DrvTools32.exe
echo Linking %THEFILE%
C:\lazarus\fpc\3.2.0\bin\x86_64-win64\ld.exe -b pei-i386 -m i386pe  --gc-sections  -s --subsystem windows --entry=_WinMainCRTStartup    -o C:\Work\DrvTools\DrvTools32.exe C:\Work\DrvTools\link.res
if errorlevel 1 goto linkend
C:\lazarus\fpc\3.2.0\bin\x86_64-win64\postw32.exe --subsystem gui --input C:\Work\DrvTools\DrvTools32.exe --stack 16777216
if errorlevel 1 goto linkend
goto end
:asmend
echo An error occurred while assembling %THEFILE%
goto end
:linkend
echo An error occurred while linking %THEFILE%
:end
