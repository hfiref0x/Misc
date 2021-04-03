/*++

Copyright (c) 1993  Microsoft Corporation

Module Name:

    mapmem.h

Abstract:


Environment:

    kernel & User mode

Notes:


Revision History:

--*/


//
// Define the various device type values.  Note that values used by Microsoft
// Corporation are in the range 0-32767, and 32768-65535 are reserved for use
// by customers.
//

#define FILE_DEVICE_MAPMEM  0x00008000



//
// Macro definition for defining IOCTL and FSCTL function control codes.  Note
// that function codes 0-2047 are reserved for Microsoft Corporation, and
// 2048-4095 are reserved for customers.
//

#define MAPMEM_IOCTL_INDEX  0x800


//
// Define our own private IOCTL
//

#define IOCTL_MAPMEM_MAP_USER_PHYSICAL_MEMORY   CTL_CODE(FILE_DEVICE_MAPMEM , \
                                                         MAPMEM_IOCTL_INDEX,  \
                                                         METHOD_BUFFERED,     \
                                                         FILE_ANY_ACCESS)

#define IOCTL_MAPMEM_UNMAP_USER_PHYSICAL_MEMORY CTL_CODE(FILE_DEVICE_MAPMEM,  \
                                                         MAPMEM_IOCTL_INDEX+1,\
                                                         METHOD_BUFFERED,     \
                                                         FILE_ANY_ACCESS)




//
// Our user mode app will pass an initialized structure like this
//     down to the kernel mode driver
//

typedef struct
{
    INTERFACE_TYPE   InterfaceType; // Isa, Eisa, etc....
    ULONG            BusNumber;     // Bus number
    PHYSICAL_ADDRESS BusAddress;    // Bus-relative address
    ULONG            AddressSpace;  // 0 is memory, 1 is I/O
    ULONG            Length;        // Length of section to map

} PHYSICAL_MEMORY_INFO, *PPHYSICAL_MEMORY_INFO;
