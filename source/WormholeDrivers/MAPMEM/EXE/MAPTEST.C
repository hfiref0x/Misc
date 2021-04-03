/*++

Copyright (c) 1993  Microsoft Corporation

Module Name:

    maptest.h

Abstract:

    Win32 test app for the MAPMEM driver

Environment:

    User mode

Notes:


Revision History:

--*/


#include "windows.h"
#include "winioctl.h"
#include "stdio.h"
#include "stdlib.h"
#include "ioaccess.h"


//
// A couple of typedefs mapmem.h depends on from  MINIPORT.H & NTDDK.H.
//

typedef enum _INTERFACE_TYPE
{
    Internal,
    Isa,
    Eisa,
    MicroChannel,
    TurboChannel,
    MaximumInterfaceType
} INTERFACE_TYPE, *PINTERFACE_TYPE;

typedef LARGE_INTEGER PHYSICAL_ADDRESS;

#include "mapmem.h"



int
__cdecl
main(
    IN int  argc,
    IN char *argv[])
/*++

Routine Description:

    Tries to open the MAPMEM driver & send it a couple of IOCTLs.

Arguments:

    argc - count of command line arguments

    argv - command line arguments

Return Value:


--*/
{
    HANDLE               hDriver;
    PHYSICAL_MEMORY_INFO pmi;
    PVOID                pPartyMem;
    DWORD                cbReturned;
    ULONG                length;
    char                 *aInterfaceType[] =  {"Internal",
                                               "Isa",
                                               "Eisa",
                                               "MicroChannel",
                                               "TurboChannel" };
    if (argc < 4)
    {
        //
        // Display usage message
        //

        printf ("\nUsage: maptest <InterfaceType> <BusNumber> <BusAddress> <AddressSpace> <length>\n\n");
        printf ("\t<InterfaceType>: 1 = Isa, 2 = Eisa, 3 = Microchannel, 4 = TurboChannel\n");
        printf ("\t<BusNumber>    : bus number, i.e. 0 for standard x86 ISA systems\n");
        printf ("\t<BusAddress>   : physical address to map (hex)\n");
        printf ("\t<AddressSpace> : 0 = memory, 1 = I/O\n");
        printf ("\t<length>       : length of section to map (hex)\n\n");

        printf ("\tExample: 'maptest 1 0 0xa0000 0 0x2000'\n");
        return 0;
    }



    //
    // Parse the args
    //

    pmi.InterfaceType       = (INTERFACE_TYPE) atoi (argv[1]);
    pmi.BusNumber           = (ULONG)          atoi (argv[2]);
    pmi.BusAddress.HighPart = (LONG)           0x00000000;
    pmi.AddressSpace        = (LONG)           atoi (argv[4]);

    sscanf (argv[3], "%x", &pmi.BusAddress.LowPart);
    sscanf (argv[5], "%x", &pmi.Length);

    printf ("\tInterfaceType = %s\n",   aInterfaceType[pmi.InterfaceType]);
    printf ("\tBusNumber     = %d\n",   pmi.BusNumber);
    printf ("\tBusAddress    = 0x%x\n", pmi.BusAddress.LowPart, pmi.BusAddress.LowPart);
    printf ("\tAddressSpace  = %d\n",   pmi.AddressSpace);
    printf ("\tLength        = 0x%x\n", pmi.Length, pmi.Length);

    length = pmi.Length;



    //
    // Try to open the device
    //

    if ((hDriver = CreateFile("\\\\.\\MAPMEM",
                              GENERIC_READ | GENERIC_WRITE,
                              0,
                              NULL,
                              OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL
                              )) != ((HANDLE)-1))

        printf ("\nRetrieved valid handle for MAPMEM driver\n");


    else
    {
        printf ("Can't get a handle to MAPMEM driver\n");

        return 0;
    }



    //
    // Try to map the memory
    //

    if (DeviceIoControl (hDriver,
                         (DWORD) IOCTL_MAPMEM_MAP_USER_PHYSICAL_MEMORY,
                         &pmi,
                         sizeof(PHYSICAL_MEMORY_INFO),
                         &pPartyMem,
                         sizeof(PVOID),
                         &cbReturned,
                         0
                         ) )
    {
        ULONG j;

        //
        // party on memory...
        //

        if (pPartyMem)
        {
            UCHAR uc;

            for (j = 0; j < length; j++)
            {
                uc = READ_REGISTER_UCHAR( (PUCHAR)pPartyMem + j );
                WRITE_REGISTER_UCHAR( (PUCHAR)pPartyMem + j , 0x47 );
            }


            //
            // Unmap the memory
            //

            DeviceIoControl (hDriver,
                             (DWORD) IOCTL_MAPMEM_UNMAP_USER_PHYSICAL_MEMORY,
                             &pPartyMem,
                             sizeof(PVOID),
                             NULL,
                             0,
                             &cbReturned,
                             0
                             );
        }

        else

            printf ("pPartyMem = NULL\n");
    }

    else

        //
        // We failed to map, possibly due to resource conflicts (i.e
        // some other driver/device already grabbed the section we
        // wanted).
        //

        printf ("DeviceIoControl failed\n");


    CloseHandle(hDriver);

    return 1;
}
