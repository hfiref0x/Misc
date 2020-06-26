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
 *    linuxdriverpci_i.c
 *
 *  Abstract:
 *    This file contains function implementations for NAL PCI
 *    functions for the Linux Driver portion.  These routines
 *    are called as IOCTL's from the NalResolveIoctl routines.
 *
 */


#include <nalcodes.h>
#include <naltypes.h>
#include <os_i.h>
#include <hwbus_t.h>
#include <pci_i.h>
#include "linuxnaldriver.h"
#include <linux/module.h>
#include <linux/pci.h>
#include <asm/byteorder.h>

#ifndef CONFIG_PCI
#error "This driver requires PCI support to be available"
#endif

NAL_PHYSICAL_ADDRESS Global_SpiBaseRegPhysicalAddress = 0;

/* For SPI:
*/

BOOLEAN _NalIsBytMfgModeDoneSet()
{
    struct pci_dev*         LinuxPciDevice = NULL;
    struct pci_bus*         LinuxPciBus    = NULL;
    unsigned int            DeviceFunction = 0;
    int                     Result         = 0;
    unsigned int value = 0;
    BOOLEAN status = FALSE;

    /* Use segments for creating a Linux PCi Device, for segemented architecture */
    LinuxPciBus = pci_find_bus(0, HECI_PCI_BUSNUMBER);

    if(LinuxPciBus != NULL)
    {
        /* Set up the DeviceFunction variable */
        DeviceFunction = PCI_DEVFN(HECI_PCI_DEVICEID, HECI_PCI_FUNCTION);

        /* Get the pci device from the bus/dev/function */
        LinuxPciDevice = pci_get_slot(LinuxPciBus, HECI_PCI_FUNCTION);

        /* Read the DWORD */
        if(LinuxPciDevice != NULL)
        {
            Result = pci_read_config_dword(LinuxPciDevice, ME_PCI_FWSTATUS_REG , &value);

            if(Result == 0)
            {
                status = (value & ME_PCI_FWSTATUS_MFG_DONE) ? true:false;
            }
        }
        pci_dev_put(LinuxPciDevice);
    }
    return status;
}

BOOLEAN _NalIsBytPciDevices(IN NAL_PHYSICAL_ADDRESS PhysicalAddress)
{
    struct pci_dev*         LinuxPciDevice = NULL;
    struct pci_bus*         LinuxPciBus    = NULL;
    unsigned int            DeviceFunction = 0;
    int                     Result         = 0;
    unsigned int value = 0;
    BOOLEAN status = FALSE;

    /* Use segments for creating a Linux PCi Device, for segemented architecture */
    LinuxPciBus = pci_find_bus(0, LPC_PCI_BUSNUMBER);

    if(LinuxPciBus != NULL)
    {
        /* Set up the DeviceFunction variable */
        DeviceFunction = PCI_DEVFN(LPC_PCI_DEVICEID, LPC_PCI_FUNCTION);

        /* Get the pci device from the bus/dev/function */
        LinuxPciDevice = pci_get_slot(LinuxPciBus, DeviceFunction);

        /* Read the DWORD */
        if(LinuxPciDevice != NULL)
        {
            Result = pci_read_config_dword(LinuxPciDevice, LPC_SBASE_REG_OFFSET, &value);
            if(Result == 0)
            {
                Global_SpiBaseRegPhysicalAddress = value;
                status = ((PhysicalAddress & 0xFFFFF000) == (value & 0xFFFFF000))  ? TRUE:FALSE;

            }
            if(status == FALSE)
            {
                value = 0;
                Result = pci_read_config_dword(LinuxPciDevice, LPC_PBASE_REG_OFFSET, &value);
                if(Result == 0)
                {
                    status = ((PhysicalAddress & 0xFFFFF000) == (value & 0xFFFFF000))  ? TRUE:FALSE;
                }
            }
        }
        pci_dev_put(LinuxPciDevice);
    }
    return status;
}

UINT16
_NalReadPciDeviceCount(
    VOID
    )
{

    return 0;
}

NAL_STATUS
_NalReadPciDevice(
    OUT NAL_DEVICE_LOCATION* PciLocations,
    IN UINT16* Count
    )
{

    return NAL_NOT_IMPLEMENTED;
}

NAL_STATUS
_NalFillPciConfigSpec(
    IN NAL_DEVICE_LOCATION PciLocation,
    OUT PCI_DEVICE* Device,
    IN UINT32 DwordCount
    )
{

    return NAL_NOT_IMPLEMENTED;
}

NAL_STATUS
_NalOSReadPciConfig32(
    IN NAL_DEVICE_LOCATION PciLocation,
    IN UINT32 DwordNumber,
    OUT UINT32* Value
    )
{
    struct pci_dev* LinuxPciDevice = NULL;
    struct pci_bus* LinuxPciBus = NULL;
    NAL_STATUS NalStatus = NAL_INVALID_PCI_SLOT_ID;
    unsigned int DeviceFunction = 0;
    int Result = 0;

    LinuxPciBus = pci_find_bus(PciLocation.Pci.Segment, PciLocation.Pci.Bus);

    if(LinuxPciBus != NULL)
    {

        DeviceFunction = PCI_DEVFN(PciLocation.Pci.Device, PciLocation.Pci.Function);

        LinuxPciDevice = pci_get_slot(LinuxPciBus, DeviceFunction);

        if(LinuxPciDevice != NULL)
        {
            Result = pci_read_config_dword(LinuxPciDevice, DwordNumber*4, (u32*)Value);

            if(Result == 0)
            {

                NalStatus = NAL_SUCCESS;
            }
            else
            {
                NalStatus = NAL_PCI_CAPABILITY_NOT_FOUND;
                *Value = 0;
            }
        }
        pci_dev_put(LinuxPciDevice);
    }
    return NalStatus;
}

NAL_STATUS
_NalOSWritePciConfig32(
    IN NAL_DEVICE_LOCATION PciLocation,
    IN UINT32 DwordNumber,
    IN UINT32 Data
    )
{
    struct pci_dev* LinuxPciDevice = NULL;
    struct pci_bus* LinuxPciBus = NULL;
    NAL_STATUS NalStatus = NAL_INVALID_PCI_SLOT_ID;
    unsigned int DeviceFunction = 0;
    int Result = 0;

    DeviceFunction = PCI_DEVFN(PciLocation.Pci.Device, PciLocation.Pci.Function);

    LinuxPciBus = pci_find_bus(PciLocation.Pci.Segment, PciLocation.Pci.Bus);

    if(LinuxPciBus != NULL)
    {

        LinuxPciDevice = pci_get_slot(LinuxPciBus, DeviceFunction);

        if(LinuxPciDevice != NULL)
        {
            Result = pci_write_config_dword(LinuxPciDevice, DwordNumber*4, Data);
            if(Result == 0)
            {
                NalStatus = NAL_SUCCESS;
            }
            else
            {
                NalStatus = NAL_PCICONFIG_NOT_AVAILABLE;
            }
        }
        pci_dev_put(LinuxPciDevice);
    }
    return NalStatus;
}

NAL_STATUS
_NalOSWritePciConfigVariable(
    IN NAL_DEVICE_LOCATION PciLocation,
    IN UINT32 DwordNumber,
    IN UINT8 ByteMask,
    IN UINT32 Data
    )
{
    struct pci_dev* LinuxPciDevice = NULL;
    struct pci_bus* LinuxPcibus = NULL;
    NAL_STATUS NalStatus = NAL_INVALID_PCI_SLOT_ID;
    unsigned int DeviceFunction = 0;
    int Result = 0;
    UINT16 Data16 = 0;
    UINT8 Data8 = 0;

    DeviceFunction = PCI_DEVFN(PciLocation.Pci.Device, PciLocation.Pci.Function);

    do
    {

        LinuxPcibus = pci_find_bus(PciLocation.Pci.Segment, PciLocation.Pci.Bus);
        if(LinuxPcibus == NULL)
        {
            break;
        }

        LinuxPciDevice = pci_get_slot(LinuxPcibus, DeviceFunction);

        if(LinuxPciDevice == NULL)
        {
            break;
        }

        if(ByteMask == PCI_CONFIG_BM_ENTIRE_DWORD)
        {
            Result = pci_write_config_dword(LinuxPciDevice, DwordNumber*4, Data);
            break;
        }

        if(ByteMask == PCI_CONFIG_BM_LOWORD)
        {
            Data16 = LOWORD(Data);
            Result = pci_write_config_word(LinuxPciDevice, DwordNumber*4, Data);
            break;
        }

        if(ByteMask == PCI_CONFIG_BM_HIWORD)
        {
            Data16 = HIWORD(Data);
            Result = pci_write_config_word(LinuxPciDevice, (DwordNumber*4 + 2), Data);
            break;
        }

        if(ByteMask & PCI_CONFIG_BM_BYTE1)
        {
            Data8 = (UINT8)Data;
            Result = pci_write_config_byte(LinuxPciDevice, (DwordNumber*4), Data8);
        }

        if(ByteMask & PCI_CONFIG_BM_BYTE2)
        {
            Data8 = (UINT8)(Data >> 8);
            Result = pci_write_config_byte(LinuxPciDevice, (DwordNumber*4 + 1), Data8);
        }

        if(ByteMask & PCI_CONFIG_BM_BYTE3)
        {
            Data8 = (UINT8)(Data >> 16);
            Result = pci_write_config_byte(LinuxPciDevice, (DwordNumber*4 + 2), Data8);
       }

        if(ByteMask & PCI_CONFIG_BM_BYTE4)
        {
            Data8 = (UINT8)(Data >> 24);
            Result = pci_write_config_byte(LinuxPciDevice, (DwordNumber*4 + 3), Data8);
        }
    }
    while(FALSE);
    if(Result == 0)
    {
        NalStatus = NAL_SUCCESS;
    }
    else
    {
        NalStatus = NAL_PCICONFIG_NOT_AVAILABLE;
    }
    return NalStatus;
}

NAL_STATUS
_NalEnablePciDevice(
    IN NAL_DEVICE_LOCATION DeviceLocation
    )
{
    struct pci_dev* LinuxPciDevice = NULL;
    struct pci_bus* LinuxPciBus = NULL;
    unsigned int DeviceFunction = 0;
    int Result = -1;
    NAL_STATUS Status = NAL_SUCCESS;

    DeviceFunction = PCI_DEVFN(DeviceLocation.Pci.Device, DeviceLocation.Pci.Function);

    LinuxPciBus = pci_find_bus(DeviceLocation.Pci.Segment, DeviceLocation.Pci.Bus);

    if(LinuxPciBus != NULL)
    {

        LinuxPciDevice = pci_get_slot(LinuxPciBus, DeviceFunction);

	if (LinuxPciDevice)
		Result = pci_enable_device(LinuxPciDevice);

        if(Result != 0)
        {
            Status = NAL_PCICONFIG_NOT_AVAILABLE;
        }
    }
    return Status;
}

NAL_STATUS
_NalOSWritePciExConfig32(
    IN NAL_DEVICE_LOCATION PciLocation,
    IN UINT32 DwordNumber,
    IN UINT32 Data
    )
{
    return _NalOSWritePciConfig32(PciLocation, DwordNumber, Data);
}

NAL_STATUS
_NalOSReadPciExConfig32(
    IN NAL_DEVICE_LOCATION PciLocation,
    IN UINT32 DwordNumber,
    IN UINT32* Value
    )
{
   return _NalOSReadPciConfig32(PciLocation, DwordNumber, Value);
}

NAL_STATUS
_NalOsReadPciExByte(
    IN NAL_DEVICE_LOCATION DeviceLocation,
    IN UINT32 ByteIndex,
    OUT UINT8* Value
    )
{
    struct pci_dev* LinuxPciDevice = NULL;
    struct pci_bus* LinuxPciBus = NULL;
    NAL_STATUS Status = NAL_INVALID_PCI_SLOT_ID;
    unsigned int DeviceFunction = 0;

    printk(KERN_DEBUG "in the driver Pci Ex config function byte index %d\n", ByteIndex);

    LinuxPciBus = pci_find_bus(DeviceLocation.Pci.Segment, DeviceLocation.Pci.Bus);

    if((LinuxPciBus != NULL) && (ByteIndex < 4096))
    {

        DeviceFunction = PCI_DEVFN(DeviceLocation.Pci.Device, DeviceLocation.Pci.Function);

        LinuxPciDevice = pci_get_slot(LinuxPciBus, DeviceFunction);

        if(LinuxPciDevice != NULL)
        {
            pci_read_config_byte(LinuxPciDevice, ByteIndex, Value);
            Status = NAL_SUCCESS;
        }
    }

    return Status;
}

NAL_STATUS
_NalOsWritePciExByte(
    IN NAL_DEVICE_LOCATION DeviceLocation,
    IN UINT32 ByteOffset,
    IN UINT8 Data
    )
{
    struct pci_dev* LinuxPciDevice = NULL;
    struct pci_bus* LinuxPciBus = NULL;
    NAL_STATUS Status = NAL_INVALID_PCI_SLOT_ID;
    unsigned int DeviceFunction = 0;

    LinuxPciBus = pci_find_bus(DeviceLocation.Pci.Segment, DeviceLocation.Pci.Bus);

    if((LinuxPciBus != NULL) && (ByteOffset < 4096))
    {

        DeviceFunction = PCI_DEVFN(DeviceLocation.Pci.Device, DeviceLocation.Pci.Function);

        LinuxPciDevice = pci_get_slot(LinuxPciBus, DeviceFunction);

        if(LinuxPciDevice != NULL)
        {
            pci_write_config_byte(LinuxPciDevice, ByteOffset, Data);
            Status = NAL_SUCCESS;
        }
    }

    return Status;
}
