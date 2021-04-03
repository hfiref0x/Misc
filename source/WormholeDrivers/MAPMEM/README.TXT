Build & Run Instructions:
-------------------------

The MAPMEM sample demonstrates how a kernel-mode device driver
can utilize the Zw*MapViewOfSection APIs to (un)map a physical
address into a user-mode process's address space.


NOTE: Microsoft does not recommend architecting Win32 applications
      such that they read/write directly on physical memory.
      User-mode applications are not considered "trusted" parts
      of the system, and giving hardware access to untrusted
      modules seriously impairs system security.

      We encourage developers who need hardware access to locate
      their hardware I/O code in a device driver, and have their
      Win32 app communicate it's requests to the driver via the
      DeviceIoControl() API.


This sample is composed of two parts, a Windows NT kernel-mode
device driver (MAPMEM) and a Win32 test application (MAPTEST).


The Win32 portion contains a file, MAPTEST.C, which attempts to
obtain a handle to MAPMEM & send it IOCTLs.  The executable is built
using the Windows NT SDK.  First update the environment and path by
running <mstools>\setenv.bat.  Then change to the directory where
you have the C source code and the makefile.  Type "nmake /f maptest.mak"
to compile the Win32 program, MAPTEST.EXE.


The kernel driver portion contains the driver source code, MAPMEM.C
and a text file used to configure your registry so that the driver
can be loaded.  The driver is built using the Windows NT DDK.

To build the driver:


    1. Assuming you have run <sdk_root>\setenv.bat and
       <ddk_root>\setenv.bat, build the driver by typing:

               build -cef

       (If there are any errors have a look at the build.log, build.err,
        and build.wrn files to get an idea of what went wrong.)


    2. Copy the newly built driver, <ddk_root>\lib\*\MAPMEM.SYS to the
       <nt_root>\system32\drivers\ directory, i.e.:

               copy \ntddk\lib\i386\free\mapmem.sys c:\winnt\system32\drivers\


    3. Update the registry by running regini.exe on the mapmem.ini
       file, i.e.:

               regini mapmem.ini

       This adds a MAPMEM driver key under the HKEY_LOCAL_MACHINE\
       SYSTEM\CurrentControlSet\Services tree in the registry. You
       can verify this by starting REGEDIT.EXE and looking in the
       appropriate place.


    4. Reboot.


    5. Type:

               net start mapmem

       ...and then execute MAPTEST.EXE.
