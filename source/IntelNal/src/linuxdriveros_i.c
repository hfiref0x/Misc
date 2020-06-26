/*
 * Intel QV Linux kernel driver
 * Copyright (c) 1999 - 2013, Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

/*
 * Module Name:
 *   linuxdriveros_i.c
 *
 * Abstract:
 *   This is the driver OSI portion of NAL Linux.  These same
 *   function implementations will appear in Linuxlibrary.c. This file
 *   provides the necessary means to call the IOCTL needed and returns
 *   the correct values for the OS Interface of the NAL for Linux.
 */


#include "nalcodes.h"
#include "naltypes.h"
#include "os_i.h"
#include "pci_i.h"
#include "linuxnaldriver.h"

#include <asm/io.h>
#include <asm/mman.h>
#include <linux/slab.h>
#include <asm/atomic.h>
#include <linux/sched.h>
#include <asm/page.h>

#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/pci_ids.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <asm/uaccess.h>
#include <linux/pci.h>
#include <linux/delay.h>

spinlock_t Global_AtomicTestSetSpinLock;

#if 0
BOOLEAN Global_DebugPrintEnabled = TRUE;
#else
BOOLEAN Global_DebugPrintEnabled = FALSE;
#endif

extern NAL_PHYSICAL_ADDRESS Global_SpiBaseRegPhysicalAddress;

UINT8
NalReadPort8(
    IN PORT_ADDR Port
    )
{
    UINT8 Buffer = 0;
    Buffer = inb(Port);
    return Buffer;
}

UINT16
NalReadPort16(
    IN PORT_ADDR Port
    )
{
    UINT16 Buffer = 0;

    Buffer = inw(Port);
    return Buffer;
}

UINT32
NalReadPort32(
    IN PORT_ADDR Port
    )
{
    UINT32 Buffer = 0;
    Buffer = inl(Port);
    return Buffer;
}

BOOLEAN
NalWritePort8(
    IN PORT_ADDR Port,
    IN UINT8 Value
    )
{
    outb(Value, Port);
    return TRUE;
}

BOOLEAN
NalWritePort16(
    IN PORT_ADDR Port,
    IN UINT16 Value
    )
{
    outw(Value, Port);
    return TRUE;
}

BOOLEAN
NalWritePort32(
    IN PORT_ADDR Port,
    IN UINT32 Value
    )
{
    outl(Value, Port);
    return TRUE;
}

UINT8
NalReadRegister8(
    IN KVOID* Address
    )
{
    UINT8 Value = 0;

    if(Address != NULL)
    {
        Value = readb((CHAR*)Address);
    }
    return Value;
}

UINT16
NalReadRegister16(
    IN KVOID* Address
    )
{
    UINT16 Value = 0;

    if(Address != NULL)
    {
        Value = readw((CHAR*)Address);
    }
    return Value;
}

UINT32
NalReadRegister32(
    IN KVOID* Address
    )
{
    UINT32 Value = 0;

    if(Address != NULL)
    {
        Value = readl((CHAR*)Address);
    }
    return Value;
}

BOOLEAN
NalWriteRegister8(
    IN KVOID* Address,
    IN UINT8 Value
    )
{
    BOOLEAN Success = FALSE;

    if(Address != NULL)
    {
        writeb(Value, (CHAR*)Address);
        Success = TRUE;
    }
    return Success;
}

BOOLEAN
NalWriteRegister16(
    IN KVOID* Address,
    IN UINT16 Value
    )
{
    BOOLEAN Success = FALSE;

    if(Address != NULL)
    {
        writew(Value, (CHAR*)Address);
        Success = TRUE;
    }
    return Success;
}

BOOLEAN
NalWriteRegister32(
    IN KVOID* Address,
    IN UINT32 Value
    )
{
    BOOLEAN Success = FALSE;

    if(Address != NULL)
    {
        writel(Value, (CHAR*)Address);
        Success = TRUE;
    }
    return Success;
}

NAL_STATUS
NalMmapAddress(
    IN OUT KVOID** VirtualAddress,
    IN NAL_PHYSICAL_ADDRESS PhysicalAddress,
    IN OUT UINT32* Length
    )
{
    NAL_STATUS NalStatus = NAL_INVALID_PARAMETER;

    if(_NalIsBytPciDevices(PhysicalAddress) != TRUE) {
	NalDebugPrint("PhysicalAddress : %x is not supported by Android driver", PhysicalAddress);
        return NAL_MMAP_FAILED;
    }

    if(VirtualAddress != NULL && Length != NULL)
    {
        *VirtualAddress = ioremap(PhysicalAddress, (UINT64)(*Length));
        if(*VirtualAddress != NULL)
        {
            NalStatus = NAL_SUCCESS;
        }
        else
        {
            NalStatus = NAL_MMAP_FAILED;
        }
    }
    return NalStatus;
}

NAL_STATUS
NalUnmapAddress(
    IN KVOID* VirtualAddress,
    IN NAL_PHYSICAL_ADDRESS PhysicalAddress,
    IN UINT32 Length
    )
{
    NAL_STATUS NalStatus = NAL_INVALID_PARAMETER;
    if(VirtualAddress != NULL)
    {
        iounmap(VirtualAddress);
        NalStatus = NAL_SUCCESS;
    }
    return NalStatus;
}

VOID
NalDelayMilliseconds(
    IN UINT32 Milliseconds
    )
{
    mdelay(Milliseconds);
}

VOID
NalDelayMicroseconds(
    IN UINT32 Microseconds
    )
{

    if(Microseconds>1000)
    {
        NalDelayMilliseconds((UINT32)(Microseconds/1000));
        Microseconds %= 1000;
    }
    udelay(Microseconds);
}

UINT64
NalGetTimeStamp( VOID )
{
    UINT32 Low = 0;
    UINT32 High = 0;

    return (UINT64)((((UINT64)High) << 32) | Low);
}

UINT64
NalGetTimeStampsPerMicrosecond( VOID )
{
    return (UINT64)0;
}

VOID*
_NalAllocateMemory(
    IN UINT32 ByteCount,
    IN CHAR* NamedLocator,
    IN UINT32 LineNumber
    )
{
    VOID* Address = kmalloc(ByteCount, GFP_KERNEL);
    if(Address != NULL)
    {
        memset(Address, 0, ByteCount);
    }
    return Address;
}

KVOID*
_NalAllocateMemoryNonPaged(
    IN UINT32 ByteCount,
    IN UINT32 Alignment,
    OUT NAL_PHYSICAL_ADDRESS* PhysicalAddress,
    IN CHAR* NamedLocator,
    IN UINT32 LineNumber
    )
{
    KVOID* Allocation = NULL;

    NalDebugPrint("PAGE_SIZE = %d\n", PAGE_SIZE);
    if(ByteCount < Alignment)
    {
        NAL_LINUX_MEMORY_ROUNDUP(ByteCount, Alignment);
        NalDebugPrint("Aligned bytecount = %d\n", ByteCount);
    }

    if(ByteCount <= (128 * 1024))
    {
        Allocation = kmalloc(ByteCount, GFP_KERNEL | GFP_DMA);

        if(Allocation != NULL && PhysicalAddress != NULL)
        {
            *PhysicalAddress = (NAL_PHYSICAL_ADDRESS)__pa(Allocation);
        }
    }

    if(Allocation == NULL)
    {
        NalDebugPrint("Allocation failed: File: %s, Line %d\n", NamedLocator, LineNumber);
    }
    else
    {
        memset(Allocation, 0, ByteCount);
        if(PhysicalAddress != NULL)
        {
            NalDebugPrint("Phys Addr: %x", *PhysicalAddress);
        }
        NalDebugPrint("\n");
    }
    return Allocation;
}

KVOID*
_NalAllocateMemoryNonPagedPci(
    IN KVOID* PDev,
    IN UINT32 ByteCount,
    IN UINT32 Alignment,
    OUT NAL_PHYSICAL_ADDRESS* PhysicalAddress,
    IN CHAR* NamedLocator,
    IN UINT32 LineNumber
    )
{
    KVOID* Allocation = NULL;
    struct pci_dev* LinuxPciDevice = (struct pci_dev*)PDev;
    dma_addr_t Dma;

    NalDebugPrint("PAGE_SIZE = %d\n", PAGE_SIZE);
    if(ByteCount < Alignment)
    {
        NAL_LINUX_MEMORY_ROUNDUP(ByteCount, Alignment);
        NalDebugPrint("Aligned bytecount = %d\n", ByteCount);
    }

    if((LinuxPciDevice != NULL) && ByteCount <= NAL_LINUX_MAX_CONTIGUOUS_MEMORY_ALLOCATION)
    {

        Allocation = pci_alloc_consistent(LinuxPciDevice,ByteCount, &Dma);
        *PhysicalAddress = (NAL_PHYSICAL_ADDRESS)Dma;
    }

    if(Allocation == NULL)
    {
        NalDebugPrint("Allocation failed: File: %s, Line %d\n", NamedLocator, LineNumber);
    }
    else
    {
        memset(Allocation, 0, ByteCount);
        if(PhysicalAddress != NULL)
        {
            NalDebugPrint("Phys Addr: %x", *PhysicalAddress);
        }
        NalDebugPrint("\n");
    }
    return Allocation;
}

VOID
_NalFreeMemory(
    IN VOID* Address,
    IN CHAR* NamedLocator,
    IN UINT32 LineNumber
    )
{
    if(Address != NULL)
    {
        kfree(Address);
    }
}

VOID
_NalFreeMemoryNonPaged(
    IN KVOID* Address,
    IN CHAR* NamedLocator,
    IN UINT32 LineNumber
    )
{
    if(Address != NULL)
    {

        kfree(Address);
    }
}

VOID
NalFreeMemoryNonPagedPci(
    IN KVOID* PDev,
    IN KVOID* Address,
    IN NAL_PHYSICAL_ADDRESS PhysicalAddress,
    IN UINT32 Size
    )
{
    struct pci_dev* LinuxPciDevice = (struct pci_dev*)PDev;

    if(PDev != NULL && Address != NULL && PhysicalAddress != 0)
    {
        printk(KERN_DEBUG "freeing memory with size %d and phy address %x'%x\n", Size, HIDWORD((UINT64)PhysicalAddress), LODWORD((UINT64)PhysicalAddress));
        pci_free_consistent(LinuxPciDevice, Size, Address, PhysicalAddress);
    }
}

NAL_PHYSICAL_ADDRESS
NalGetPhysicalMemoryAddress(
    IN KVOID* VirtualAddress
    )
{
    NAL_PHYSICAL_ADDRESS NalPhysical = 0;

    if(VirtualAddress != NULL)
    {
        NalPhysical = __pa(VirtualAddress);
    }

    return NalPhysical;
}

KVOID*
NalKMemset(
    IN KVOID* Dest,
    IN int Value,
    IN UINTN Size
    )
{
    return memset(Dest, Value, Size);
}

VOID*
NalKtoUMemcpy(
    IN VOID* Dest,
    IN KVOID* Source,
    IN UINTN Size
    )
{
    UINTN BytesLeft = 0;
    BytesLeft = copy_to_user(Dest, Source, Size);
    return Dest;
}

KVOID*
NalKtoKMemcpy(
    IN KVOID* Dest,
    IN KVOID* Source,
    IN UINTN Size
    )
{
    return memcpy(Dest, Source, Size);
}

KVOID*
NalUtoKMemcpy(
    IN KVOID* Dest,
    IN VOID* Source,
    IN UINTN Size
    )
{
    UINTN BytesLeft = 0;
    NAL_PHYSICAL_ADDRESS NalPhysical = 0;

    if(Dest != NULL) {
        if(_NalIsBytMfgModeDoneSet() == TRUE) {
            NalPhysical = __pa(Dest);
            if(NalPhysical >= (Global_SpiBaseRegPhysicalAddress + SPI_FDATA0_OFFSET)
               && NalPhysical <= (Global_SpiBaseRegPhysicalAddress + SPI_FDATA15_OFFSET)) {
                printk(KERN_DEBUG "MFG mode is set cannot write to SPI after MFG mode is set\n");
	        return NULL;
            }
        }
        BytesLeft = copy_from_user(Dest, Source, Size);
    }
    return Dest;
}

UINT32
NalAtomicIncrement32(
    IN UINT32* Address
    )
{
    UINT32 ReturnValue = 0;
    UINT32 AddressLocal = 0;
    UINTN BytesLeft = 0;

    if(Address != NULL)
    {

        spin_lock(&Global_AtomicTestSetSpinLock);
        BytesLeft = copy_from_user((void*)(&AddressLocal), (void*)Address, sizeof(UINT32));

        AddressLocal++;

        ReturnValue = AddressLocal;

        BytesLeft = copy_to_user((void*)Address, (void*)(&AddressLocal), sizeof(UINT32));

        spin_unlock(&Global_AtomicTestSetSpinLock);
    }
    return ReturnValue;
}

UINT32
NalAtomicDecrement32(
    IN UINT32* Address
    )
{
    UINT32 ReturnValue = 0;
    UINT32 AddressLocal = 0;
    UINTN BytesLeft = 0;

    if(Address != NULL)
    {

        spin_lock(&Global_AtomicTestSetSpinLock);
        BytesLeft = copy_from_user((void*)(&AddressLocal), (void*)Address, sizeof(UINT32));

        AddressLocal--;

        ReturnValue = AddressLocal;

        BytesLeft = copy_to_user((void*)Address, (void*)(&AddressLocal), sizeof(UINT32));

        spin_unlock(&Global_AtomicTestSetSpinLock);
    }

    return ReturnValue;
}

UINT32
NalAtomicTestSet32(
    IN UINT32* Address,
    IN UINT32 Test,
    IN UINT32 Set
    )
{
    UINT32 ReturnValue = 0;
    UINT32 AddressLocal = 0;
    UINTN BytesLeft = 0;

    if(Address != NULL)
    {

        spin_lock(&Global_AtomicTestSetSpinLock);
        BytesLeft = copy_from_user((void*)(&AddressLocal), (void*)Address, sizeof(UINT32));

        ReturnValue = AddressLocal;

        if(AddressLocal == Test)
        {
            AddressLocal = Set;
        }

        BytesLeft = copy_to_user((void*)Address, (void*)(&AddressLocal), sizeof(UINT32));

        spin_unlock(&Global_AtomicTestSetSpinLock);
    }

    return ReturnValue;
}

NAL_STATUS
NalDebugPrintSupport(
    OUT UINT32* DebugCapabilities
    )
{
    if (DebugCapabilities != NULL)
    {
        *DebugCapabilities = NAL_DEBUG_PRINT_SUPPORTED |
                             NAL_DEBUG_PRINT_FILEIO;
    }

    return NAL_SUCCESS;
}

NAL_STATUS
NalDebugPrint(
    IN CHAR* Format,
    ...
    )
{
    CHAR FormattedStatus[500];
    va_list ArgPtr;
    NAL_STATUS DbgPrintStatus = NAL_DEBUGPRINT_FAILED;

    if(Global_DebugPrintEnabled == TRUE)
    {

        va_start(ArgPtr, Format);
        vsprintf(FormattedStatus, Format, ArgPtr);
        va_end(ArgPtr);

        printk(KERN_DEBUG "%s", FormattedStatus);
        DbgPrintStatus = NAL_SUCCESS;
    }
    return DbgPrintStatus;
}

VOID
NalEnableDebugPrint(
    IN BOOLEAN Enable
    )
{
    Global_DebugPrintEnabled = Enable;
}

NAL_STATUS
NalMmapAddressEx(
    IN OUT KVOID** VirtualAddress,
    IN NAL_PHYSICAL_ADDRESS PhysicalAddress,
    IN OUT UINT32* Length,
    IN UINTN ProcessId
    )
{
    return NalMmapAddress(VirtualAddress, PhysicalAddress, Length);
}

NAL_STATUS
NalUnmapAddressEx(
    IN KVOID* VirtualAddress,
    IN NAL_PHYSICAL_ADDRESS PhysicalAddress,
    IN UINT32 Length,
    IN UINTN ProcessId
    )
{
    return NalUnmapAddress(VirtualAddress, PhysicalAddress, Length);
}

KVOID*
_NalAllocateMemoryNonPagedEx(
    IN UINT32 ByteCount,
    IN UINT32 Alignment,
    IN UINTN ProcessId,
    OUT NAL_PHYSICAL_ADDRESS* PhysicalAddress,
    IN CHAR* NamedLocator,
    IN UINT32 LineNumber
    )
{
    return _NalAllocateMemoryNonPaged(ByteCount, Alignment, PhysicalAddress, NamedLocator, LineNumber);
}

VOID
_NalFreeMemoryNonPagedEx(
    IN KVOID* Address,
    IN UINTN ProcessId,
    IN CHAR* NamedLocator,
    IN UINT32 LineNumber
    )
{
    return _NalFreeMemoryNonPaged(Address, NamedLocator, LineNumber);
}

NAL_PHYSICAL_ADDRESS
NalGetPhysicalMemoryAddressEx(
    IN KVOID* VirtualAddress,
    IN UINTN ProcessId
    )
{
    return NalGetPhysicalMemoryAddress(VirtualAddress);
}
