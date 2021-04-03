# Nmake macros for building Windows 32-Bit apps

!include <ntwin32.mak>

all: maptest.exe

maptest.obj: maptest.c
    $(cc) $(cflags) $(cvars) $(cdebug) -I..\sys maptest.c

maptest.exe: maptest.obj
    $(link) $(linkdebug) $(conflags) -out:maptest.exe maptest.obj $(conlibs)
