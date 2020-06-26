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
 *  Module Name:
 *    linuxdriverdevice_i.c
 *
 *  Abstract:
 *    This file contains implementation for any functions that are
 *    called from nalioctldrv.c and need to be run in kernel mode.
 *
 */


#include <nalcodes.h>
#include <naltypes.h>
#include "nalioctl.h"
#include <osdevice_i.h>
#include <os_i.h>
#include "linuxnaldriver.h"
#include "linuxpci_i.h"
#include <linux/sched.h>
#include <asm/io.h>
#include <linux/pci.h>

#ifndef DMA_BIT_MASK
#define DMA_BIT_MASK(n) (((n) == 64) ? ~0ULL : ((1ULL<<(n))-1))
#endif

BOOLEAN
_NalCheckAndClearAdapterInterrupt(
    IN NAL_MAC_TYPE MacType,
    IN KVOID* BaseAddress
    );

void
_NalServiceRoutine(
    IN int Irq,
    IN void* Context,
    IN struct pt_regs* Regs
    );

NAL_STATUS
_NalEnableDevice(
    IN NAL_DEVICE_LOCATION DeviceLocation,
    OUT NAL_IO_RESOURCE* IoResource,
    OUT KVOID** Pdev
    );

NAL_STATUS
_NalFillDeviceResource(
    IN NAL_DEVICE_LOCATION DeviceLocation,
    OUT NAL_IO_RESOURCE* IoResource,
    OUT KVOID** Pdev
    );

NAL_STATUS
_NalReleaseRegions(
    IN KVOID* PDev
    );

NAL_OS_RUN_DOMAIN
_NalGetOsRunDomain( void );

void
_NalServiceRoutine(
    IN int Irq,
    IN void* Context,
    IN struct pt_regs* Regs
    )
{
    NAL_LINUX_ISR_DEVICE* NalIsrDevice = (NAL_LINUX_ISR_DEVICE*)Context;

    if(NalIsrDevice != NULL)
    {

        NalIsrDevice->DeviceInterrupted =
            _NalCheckAndClearAdapterInterrupt((NAL_MAC_TYPE)NalIsrDevice->MacType,
                                              NalIsrDevice->HardwareVirtualAddress);
    }
}

NAL_STATUS
_NalInitializeInterrupts(
    IN NAL_LINUX_ISR_DEVICE* NalIsrDevice
    )
{
    return NAL_NOT_IMPLEMENTED;
}

NAL_STATUS
_NalUninitializeInterrupts(
    IN NAL_LINUX_ISR_DEVICE* NalIsrDevice
    )
{
    return NAL_NOT_IMPLEMENTED;
}

BOOLEAN
_NalHasInterruptOccurred(
    IN NAL_LINUX_ISR_DEVICE* NalIsrDevice
    )
{
    BOOLEAN InterruptOccurred = FALSE;

    if(NalIsrDevice != NULL && NalIsrDevice->Signature == NAL_LINUX_INTERRUPT_SIGNATURE)
    {
        InterruptOccurred = NalIsrDevice->DeviceInterrupted;
    }

    return InterruptOccurred;
}

BOOLEAN
_NalCheckAndClearAdapterInterrupt(
    IN NAL_MAC_TYPE MacType,
    IN KVOID* BaseAddress
    )
{
    return FALSE;
}

NAL_STATUS
NalResolveOsSpecificIoctl(
    IN NAL_IOCTL_INPUT_DATA* NalIoctl
    )
{
    NAL_STATUS NalStatus = NAL_INVALID_PARAMETER;

    if(NalIoctl != NULL)
    {
        switch(NalIoctl->FunctionId)
        {
           case NAL_LINUX_ADAPTER_IN_USE_FUNCID:
                {
                    NAL_LINUX_ADAPTER_IN_USE_FUNC* FunctionData =
                        (NAL_LINUX_ADAPTER_IN_USE_FUNC*)(&(NalIoctl->InputBuffer));

                    printk(KERN_DEBUG "calling ioctl In mark adapter lock \n");
                    if(FunctionData != NULL)
                    {
                        FunctionData->CanBeUsed = _NalMarkAdapterInUse(FunctionData->NalDevice,
                                                                       FunctionData->Locked);
                        NalStatus = NAL_SUCCESS;
                    }
                    else
                    {
                        NalStatus = NAL_INVALID_PARAMETER;
                        NalDebugPrint("NalResolveOsSpecificIoctl: NAL_LINUX_ADAPTER_IN_USE_FUNCID FunctionData is NULL\n");
                    }
                }
                break;

           case NAL_LINUX_IS_ADAPTER_IN_USE_FUNCID:
                {
                    NAL_LINUX_IS_ADAPTER_IN_USE_FUNC* FunctionData =
                        (NAL_LINUX_IS_ADAPTER_IN_USE_FUNC*)(&(NalIoctl->InputBuffer));

                    if(FunctionData != NULL)
                    {
                        FunctionData->IsInUse = _NalIsAdapterInUse(FunctionData->NalDevice);
                        NalStatus = NAL_SUCCESS;
                    }
                    else
                    {
                        NalStatus = NAL_INVALID_PARAMETER;
                        NalDebugPrint("NalResolveOsSpecificIoctl: NAL_LINUX_IS_ADAPTER_IN_USE_FUNCID FunctionData is NULL\n");
                    }
                }
                break;

            case NAL_LINUX_REQUEST_REGIONS_FUNCID:
                {
                    NAL_LINUX_DEVICERESOURCE_FUNC* FunctionData =
                        (NAL_LINUX_DEVICERESOURCE_FUNC*)(&(NalIoctl->InputBuffer));

                    if(FunctionData != NULL)
                    {
                        FunctionData->ReturnValue = _NalEnableDevice(FunctionData->DeviceLocation,
                                                                     &(FunctionData->NalIoResource[0]),
                                                                     &FunctionData->Pdev);
                        NalStatus = NAL_SUCCESS;
                    }
                    else
                    {
                        NalStatus = NAL_INVALID_PARAMETER;
                        NalDebugPrint("NalResolveOsSpecificIoctl: NAL_LINUX_REQUEST_REGIONS_FUNCID FunctionData is NULL\n");
                    }
                }
                break;

            case NAL_LINUX_RELEASE_REGIONS_FUNCID:
                {
                    NAL_LINUX_DEVICERESOURCE_FUNC* FunctionData =
                        (NAL_LINUX_DEVICERESOURCE_FUNC*)(&(NalIoctl->InputBuffer));
                    NalDebugPrint("NalResolveOsSpecificIoctl: NAL_LINUX_RELEASE_REGIONS_FUNCID FunctionData is NULL\n");

                    if(FunctionData != NULL)
                    {
                        FunctionData->ReturnValue = _NalReleaseRegions(FunctionData->Pdev);
                        NalStatus = NAL_SUCCESS;
                    }
                    else
                    {
                        NalStatus = NAL_INVALID_PARAMETER;
                        NalDebugPrint("NalResolveOsSpecificIoctl: NAL_LINUX_RELEASE_REGIONS_FUNCID FunctionData is NULL\n");
                    }
                }
                break;

            case NAL_LINUX_INC_DRIVER_REFCOUNT_FUNCID:
                {
                    _NalDriverIncrementReferenceCount();
                    NalStatus = NAL_SUCCESS;
                }
                break;

            case NAL_LINUX_DEC_DRIVER_REFCOUNT_FUNCID:
                {
                    _NalDriverDecrementReferenceCount();
                    NalStatus = NAL_SUCCESS;
                }
                break;

            case NAL_LINUX_GET_DRIVER_REFCOUNT_FUNCID:
                {
                    NAL_LINUX_REFCOUNT_FUNCS* FunctionData =
                        (NAL_LINUX_REFCOUNT_FUNCS*)(&(NalIoctl->InputBuffer));

                    if(FunctionData != NULL)
                    {
                        FunctionData->ReturnValue = _NalDriverGetReferenceCount();
                        NalStatus = NAL_SUCCESS;
                    }
                    else
                    {
                        NalStatus = NAL_INVALID_PARAMETER;
                    }
                }
                break;

            case NAL_LINUX_DRIVER_GET_VERSION:
                {
                    NAL_LINUX_DRIVER_GET_VERSION_FUNCS* FunctionData =
                        (NAL_LINUX_DRIVER_GET_VERSION_FUNCS*)(&(NalIoctl->InputBuffer));

                   NalDebugPrint("NalResolveOsSpecificIoctl: Nal get version Ioctl\n");

                    if(FunctionData != NULL)
                    {
                        _NalDriverGetVersion(FunctionData->Version);
                        NalStatus = NAL_SUCCESS;
                    }
                    else
                    {
                        NalStatus = NAL_INVALID_PARAMETER;
                    }
                }
                break;

            case NAL_LINUX_FILL_DEVICE_RESOURCE_FUNCID:
                {
                    NAL_LINUX_DEVICERESOURCE_FUNC* FunctionData =
                        (NAL_LINUX_DEVICERESOURCE_FUNC*)(&(NalIoctl->InputBuffer));

                    NalDebugPrint("NalResolveOsSpecificIoctl: Nal Fill device resource Ioctl\n");

                    if(FunctionData != NULL)
                    {
                        FunctionData->ReturnValue = _NalFillDeviceResource(FunctionData->DeviceLocation,
                                                                           &(FunctionData->NalIoResource[0]),
                                                                           &FunctionData->Pdev);
                        NalStatus = NAL_SUCCESS;
                    }
                    else
                    {
                        NalStatus = NAL_INVALID_PARAMETER;
                        NalDebugPrint("NalResolveOsSpecificIoctl: NAL_LINUX_FILL_DEVICE_RESOURCE_FUNCID FunctionData is NULL\n");
                    }
                }
                break;

            case NAL_LINUX_FREEMEMORYNONPAGEDPCI_FUNCID:
                {
                    NAL_LINUX_FREEMEMORYNONPAGEDPCI_FUNC* FunctionData =
                        (NAL_LINUX_FREEMEMORYNONPAGEDPCI_FUNC*)(&(NalIoctl->InputBuffer));

                        NalFreeMemoryNonPagedPci(FunctionData->PDev,
                                               FunctionData->Address,
                                               FunctionData->PhysicalAddress,
                                               FunctionData->Size);

                    NalStatus = NAL_SUCCESS;
                }
                break;

            case NAL_LINUX_ALLOCATEMEMORYNONPAGEDPCI_FUNCID:
                {
                    NAL_LINUX_ALLOCATEMEMORYNONPAGEDPCI_FUNC* FunctionData =
                        (NAL_LINUX_ALLOCATEMEMORYNONPAGEDPCI_FUNC*)(&(NalIoctl->InputBuffer));

                        FunctionData->ReturnValue =
                            _NalAllocateMemoryNonPagedPci(FunctionData->PDev,
                                                       FunctionData->ByteCount,
                                                       FunctionData->Alignment,
                                                       &FunctionData->PhysicalAddress,
                                                       NULL,
                                                       0);

                    NalStatus = NAL_SUCCESS;
                }
                break;

            case NAL_LINUX_READPCIEXBYTE_FUNCID:
                {
                    NAL_LINUX_READPCIEXBYTE_FUNC* FunctionData =
                        (NAL_LINUX_READPCIEXBYTE_FUNC*)(&(NalIoctl->InputBuffer));

                    FunctionData->ReturnValue =
                        _NalOsReadPciExByte(FunctionData->PciLocation,
                                                   FunctionData->ByteIndex,
                                                   &FunctionData->Value);

                    NalStatus = NAL_SUCCESS;
                }
                break;

            case NAL_LINUX_WRITEPCIEXBYTE_FUNCID:
                {
                    NAL_LINUX_WRITEPCIEXBYTE_FUNC* FunctionData =
                        (NAL_LINUX_WRITEPCIEXBYTE_FUNC*)(&(NalIoctl->InputBuffer));
                    FunctionData->ReturnValue =
                        _NalOsWritePciExByte(FunctionData->PciLocation,
                                                    FunctionData->ByteIndex,
                                                    FunctionData->Value);

                    NalStatus = NAL_SUCCESS;
                }
                break;

            case NAL_LINUX_GET_RUN_DOMAIN_FUNCID:
                {
                    NAL_LINUX_RUN_DOMAIN_FUNC* FunctionData =
                        (NAL_LINUX_RUN_DOMAIN_FUNC*)(&(NalIoctl->InputBuffer));

                    printk(KERN_DEBUG "calling ioctl get run domain\n");
                    if(FunctionData != NULL)
                    {
                        FunctionData->RunDomain = _NalGetOsRunDomain();
                        FunctionData->ReturnValue = NAL_SUCCESS;
                        NalStatus = NAL_SUCCESS;
                    }
                    else
                    {
                        NalStatus = NAL_INVALID_PARAMETER;
                        NalDebugPrint("NalResolveOsSpecificIoctl: NAL_LINUX_GET_RUN_DOMAIN_FUNCID FunctionData is NULL\n");
                    }
                }
                break;

           default:
                NalStatus = NAL_IOCTL_INVALID_FUNCTION_ID;
                break;
        }
    }

    return NalStatus;
}

NAL_STATUS
_NalEnableDevice(
    IN NAL_DEVICE_LOCATION DeviceLocation,
    OUT NAL_IO_RESOURCE* IoResource,
    OUT KVOID** PDev
    )
{
    struct pci_dev* PciDevice = NULL;
    struct pci_bus* LinuxPciBus = NULL;
    NAL_STATUS NalStatus = NAL_SUCCESS;
    UINT32 i = 0;
    unsigned int DeviceFunction = 0;
    int Result = 0;

    DeviceFunction = PCI_DEVFN(DeviceLocation.Pci.Device, DeviceLocation.Pci.Function);

    do
    {

        LinuxPciBus = pci_find_bus(DeviceLocation.Pci.Segment, DeviceLocation.Pci.Bus);
        if(LinuxPciBus == NULL)
        {
            NalStatus = NAL_PCICONFIG_NOT_AVAILABLE;
            break;
        }

        PciDevice = pci_get_slot(LinuxPciBus, DeviceFunction);
        if(PciDevice == NULL)
        {
            NalStatus = NAL_PCICONFIG_NOT_AVAILABLE;
            break;
        }

        Result = pci_enable_device(PciDevice);
        if(Result != 0)
        {
            NalStatus = NAL_PCICONFIG_NOT_AVAILABLE;
            break;
        }

        if (pci_set_dma_mask(PciDevice, DMA_BIT_MASK(64)) ||
            pci_set_consistent_dma_mask(PciDevice, DMA_BIT_MASK(64)))
        {
            if (pci_set_dma_mask(PciDevice, DMA_BIT_MASK(32)) ||
                pci_set_consistent_dma_mask(PciDevice, DMA_BIT_MASK(32)))
            {
                    printk(KERN_DEBUG "No usable DMA configuration, aborting\n");
                    NalStatus = NAL_DMA_NOT_SUPPORTED;
                    break;
            }
        }

        for(i=0; i<6; i++)
        {

            if(pci_resource_len(PciDevice, i) == 0)
            {
                continue;
            }

            if(pci_resource_flags(PciDevice, i) & IORESOURCE_IO)
            {
                request_region(pci_resource_start(PciDevice, i),
                               pci_resource_len(PciDevice, i),
                               NAL_LINUX_DRIVER_NAME);
                IoResource[i].MemoryAddress = pci_resource_start(PciDevice, i);
                IoResource[i].Type = NAL_IO_TYPE_IO;
            }
            else if(pci_resource_flags(PciDevice, i) & IORESOURCE_MEM)
            {
                if(!check_mem_region(pci_resource_start(PciDevice, i), pci_resource_len(PciDevice, i)))
                {
                    request_mem_region(pci_resource_start(PciDevice, i),
                                       pci_resource_len(PciDevice, i),
                                       NAL_LINUX_DRIVER_NAME);
                    IoResource[i].MemoryAddress = pci_resource_start(PciDevice, i);
                }
                else
                {
                    IoResource[i].MemoryAddress = 0;
                }
                IoResource[i].Type = NAL_IO_TYPE_MEM;
            }
        }

        pci_set_master(PciDevice);

        *PDev = PciDevice;
    } while(0);

    return NalStatus;
}

NAL_STATUS
_NalFillDeviceResource(
    IN NAL_DEVICE_LOCATION DeviceLocation,
    OUT NAL_IO_RESOURCE* IoResource,
    OUT KVOID** PDev
    )
{
    struct pci_dev* PciDevice = NULL;
    struct pci_bus* LinuxPciBus = NULL;
    NAL_STATUS NalStatus = NAL_SUCCESS;
    UINT32 i = 0;
    unsigned int DeviceFunction = 0;

    printk(KERN_DEBUG "In Nal Fill Device resource\n");

    DeviceFunction = PCI_DEVFN(DeviceLocation.Pci.Device, DeviceLocation.Pci.Function);

    do
    {

        LinuxPciBus = pci_find_bus(DeviceLocation.Pci.Segment, DeviceLocation.Pci.Bus);
        if(LinuxPciBus == NULL)
        {
            NalStatus = NAL_PCICONFIG_NOT_AVAILABLE;
            break;
        }

        PciDevice = pci_get_slot(LinuxPciBus, DeviceFunction);
        if(PciDevice == NULL)
        {
            NalStatus = NAL_PCICONFIG_NOT_AVAILABLE;
            break;
        }

        if (!pci_dma_supported(PciDevice, DMA_BIT_MASK(64)))
        {
            if (!pci_dma_supported(PciDevice, DMA_BIT_MASK(32)))
            {
                printk(KERN_DEBUG "No usable DMA configuration, aborting\n");
                NalStatus = NAL_DMA_NOT_SUPPORTED;
                break;
            }
        }

        for(i=0; i<6; i++)
        {

            if(pci_resource_len(PciDevice, i) == 0)
            {
                continue;
            }

            if(pci_resource_flags(PciDevice, i) & IORESOURCE_IO)
            {
                IoResource[i].MemoryAddress = pci_resource_start(PciDevice, i);
                IoResource[i].Type = NAL_IO_TYPE_IO;
            }
            else if(pci_resource_flags(PciDevice, i) & IORESOURCE_MEM)
            {
                if(!check_mem_region(pci_resource_start(PciDevice, i), pci_resource_len(PciDevice, i)))
                {
                    IoResource[i].MemoryAddress = 0;
                }
                else
                {
                    IoResource[i].MemoryAddress = pci_resource_start(PciDevice, i);
                }
                IoResource[i].Type = NAL_IO_TYPE_MEM;
            }
        }

        *PDev = PciDevice;
    }while(0);

    return NalStatus;
}

NAL_STATUS
_NalReleaseRegions(
    IN KVOID* PDev
    )
{
    struct pci_dev* PciDevice = (struct pci_dev*)PDev;
    NAL_STATUS NalStatus = NAL_SUCCESS;
    UINT32 i = 0;

    for(i=0; i<6; i++)
    {

        if(pci_resource_len(PciDevice, i) == 0)
        {
            continue;
        }

        if(pci_resource_flags(PciDevice, i) & IORESOURCE_IO)
        {
            release_region(pci_resource_start(PciDevice, i),
                           pci_resource_len(PciDevice, i));
        }
        else if(pci_resource_flags(PciDevice, i) & IORESOURCE_MEM)
        {
            release_mem_region(pci_resource_start(PciDevice, i),
                               pci_resource_len(PciDevice, i));
        }
    }
    pci_dev_put(PciDevice);
    pci_disable_device(PciDevice);

    return NalStatus;
}

NAL_OS_RUN_DOMAIN
_NalGetOsRunDomain()
{
    NAL_OS_RUN_DOMAIN Domain = NAL_OS_DOMAIN_BAREMETAL;

#ifdef is_running_on_xen
    if(is_running_on_xen())
    {
        if(is_initial_xendomain())
        {
            Domain = NAL_OS_DOMAIN_0;
        }
        else
        {
            Domain = NAL_OS_DOMAIN_U;
        }
    }
#endif

    return Domain;
}
