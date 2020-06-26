/*
 * Intel QV Linux kernel driver for Android SPI device
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
 *
 * Module Name:
 *   linuxnaldriver.c
 *
 * Abstract:
 *   This contains the functions necessary for the Linux Driver
 *   component of NAL to function as a driver. This includes the
 *   driver entry point and all Linux specific ring 0 functions.
 *
 *
 */


#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/pci_ids.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/version.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include "naltypes.h"
#include "nalioctl.h"
#include "linuxnaldriver.h"

int
init_module(void);
void
cleanup_module(void);

extern spinlock_t Global_AtomicTestSetSpinLock;
static char Global_NalDeviceName[] = NAL_LINUX_DRIVER_NAME;
static int Global_NalMajor = 0;
static struct class *nal_class = NULL;
static struct device *nal_device = NULL;
static dev_t nal_dev;
static struct cdev nal_cdev;

NAL_ADAPTER_IN_USE_TABLE Global_AdapterInUse[NAL_DRIVER_MAX_ADAPTERS];
UINT32 Global_DriverReferenceCount = 0;

char NalLinuxDriverVersion[] = LINUX_DRIVER_VERSION;

static struct file_operations Global_NalFops =
{
    owner: THIS_MODULE,

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36)
    ioctl: NalDeviceControl,
#endif
#if LINUX_VERSION_CODE > KERNEL_VERSION(2,6,10)

    unlocked_ioctl: NalDeviceControlUnlockedIoctl,
#endif
    open: NalOpen,
    release: NalRelease
};

MODULE_AUTHOR(DRIVER_COMPANYNAME);
MODULE_DESCRIPTION(DRIVER_DESCRIPTION);
MODULE_LICENSE("GPL");
MODULE_VERSION(LINUX_DRIVER_VERSION);

int
init_module(void)
{
#ifdef NAL_LINUX_ANDROID
    int Result = 0;
    UINT32 i = 0;

    printk(KERN_DEBUG "Intel Memmap SPI Device Driver loading (v. %s)\n", LINUX_DRIVER_VERSION);

    /* Get a range of minor numbers (starting with 0) to work with */
    Result = alloc_chrdev_region(&nal_dev, 0, 1, Global_NalDeviceName);
    if (Result < 0) {
	printk(KERN_WARNING "[target] alloc_chrdev_region() failed\n");
	return Result;
    }
    Global_NalMajor = MAJOR(nal_dev);

    nal_class = class_create(THIS_MODULE, Global_NalDeviceName);
    if (nal_class == NULL) {
        printk(KERN_DEBUG "Intel Memmap SPI Device Driver cannot create class\n");
        return -ENODEV;
    }

    cdev_init(&nal_cdev, &Global_NalFops);
    nal_cdev.owner = THIS_MODULE;
    nal_cdev.ops = &Global_NalFops;
    Result = cdev_add (&nal_cdev, MKDEV(Global_NalMajor, 0), 1);
    /* Fail gracefully if need be */
    if (Result)
        printk(KERN_NOTICE "Error %d adding scull%d", Result, 0);

    nal_device = device_create(nal_class, NULL, nal_dev, NULL, Global_NalDeviceName);
    printk(KERN_DEBUG "Intel Memmap SPI Device Driver device major: %d\n", Global_NalMajor);

    if (nal_device == NULL) {
        printk(KERN_DEBUG "Intel Memmap SPI Device Driver cannot create device\n");
        return -ENODEV;
    }

    for(i=0; i<NAL_DRIVER_MAX_ADAPTERS; i++)
    {
        memset(&Global_AdapterInUse[i], 0, sizeof(NAL_ADAPTER_IN_USE_TABLE));
    }

    spin_lock_init(&Global_AtomicTestSetSpinLock);

    return Result;
#else
    int Result = 0;
    UINT32 i = 0;
    static struct class *nal_class = NULL;
    static struct device *nal_device = NULL;

    printk(KERN_DEBUG "Intel Pro Diagnostic Driver loading (v. %s)\n", LINUX_DRIVER_VERSION);
    Result = register_chrdev(0, Global_NalDeviceName, &Global_NalFops);
    if(Result < 0)
    {
        Result = -ENODEV;
    }
    else
    {
        Global_NalMajor = Result;
        Result = 0;
    }

    nal_class = class_create(THIS_MODULE, Global_NalDeviceName);
    if (nal_class == NULL) {
        printk(KERN_DEBUG "Intel Pro Diagnostic Driver cannot create class\n");
        return -ENODEV;
    }

    nal_device = device_create(nal_class, NULL, Global_NalMajor, NULL, Global_NalDeviceName);
    if (nal_device == NULL) {
        printk(KERN_DEBUG "Intel Pro Diagnostic Driver cannot create device\n");
        return -ENODEV;
    }

    for(i=0; i<NAL_DRIVER_MAX_ADAPTERS; i++)
    {
        memset(&Global_AdapterInUse[i], 0, sizeof(NAL_ADAPTER_IN_USE_TABLE));
    }

    spin_lock_init(&Global_AtomicTestSetSpinLock);

    return Result;
#endif
}

void
cleanup_module(void)
{
#ifdef NAL_LINUX_ANDROID
    printk(KERN_DEBUG "Intel Memmap SPI Device Driver exiting\n");

    cdev_del(&nal_cdev);

    if (nal_device)
        device_destroy(nal_class, MKDEV(Global_NalMajor, 0));

    if (nal_class)
        class_destroy(nal_class);

    unregister_chrdev_region(nal_dev, 1);
#else
    printk(KERN_DEBUG "Intel Pro Diagnostic Driver exiting\n");

    if (nal_device)
        device_destroy(nal_class, MKDEV(Global_NalMajor, 0));

    if (nal_class)
        class_destroy(nal_class);

    unregister_chrdev(Global_NalMajor, Global_NalDeviceName);
#endif
}

long
NalDeviceControlUnlockedIoctl(
    struct file* File,
    unsigned int Cmd,
    unsigned long Arg
    )

{
    return NalDeviceControl(NULL, File, Cmd, Arg);
}

int
NalDeviceControl(
    struct inode* Inode,
    struct file* File,
    unsigned int Cmd,
    unsigned long Arg
    )
{
    NAL_IOCTL_INPUT_DATA InputData;
    NAL_IOCTL_INPUT_DATA* NalIoctlInputData = &InputData;
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
    mm_segment_t old_fs;
#endif
    NAL_STATUS Status = NAL_SUCCESS;
    UINT32 IoctlNumber = 0;
    int Result = 0;

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)

    old_fs = get_fs();
    set_fs(get_ds());
    Result = copy_from_user(&InputData, (void*)Arg, sizeof(NAL_IOCTL_INPUT_DATA));
    set_fs(old_fs);
#else
    Result = copy_from_user(&InputData, (void*)Arg, sizeof(NAL_IOCTL_INPUT_DATA));
#endif
    if(Result == 0)
    {

        IoctlNumber = Cmd;

        switch (IoctlNumber)
        {
        case IOCTL_NAL_OSI:
            Status = NalResolveOsiIoctl(NalIoctlInputData);
            break;

        case IOCTL_NAL_HW_BUS:
            Status = NalResolveHwBusIoctl(NalIoctlInputData);
            break;

        case IOCTL_NAL_NDI:
            Status = NalResolveNdiIoctl(NalIoctlInputData);
            break;

        case IOCTL_NAL_OS_SPECIFIC:
            Status = NalResolveOsSpecificIoctl(NalIoctlInputData);
            break;

        default:

            Status = NAL_INVALID_PARAMETER;
            Result = EINVAL;
            break;
        }
    }
    if(Result == 0)
    {

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,0)
        old_fs = get_fs();
        set_fs(get_ds());
        Result = copy_to_user((void*)Arg, NalIoctlInputData, sizeof(NAL_IOCTL_INPUT_DATA));
        set_fs(old_fs);
#else

        Result = copy_to_user((void*)Arg, NalIoctlInputData, sizeof(NAL_IOCTL_INPUT_DATA));
#endif
    }
    return Result;
}

int
NalOpen(
    struct inode* Inode,
    struct file* File
    )
{
    return 0;
}

int
NalRelease(
    struct inode* Inode,
    struct file* File
    )
{
    return 0;
}

BOOLEAN
_NalMarkAdapterInUse(
    IN NAL_DEVICE_LOCATION NalDevice,
    IN BOOLEAN Lock
    )
{
    UINTN i = 0;
    BOOLEAN CanBeUsed = FALSE;

    for(i=0; i<NAL_DRIVER_MAX_ADAPTERS; i++)
    {

        if(Global_AdapterInUse[i].DeviceLocation.Reserved == NalDevice.Reserved)
        {

            if(Global_AdapterInUse[i].InUse == TRUE)
            {

                if(Lock == FALSE)
                {
                    Global_AdapterInUse[i].InUse = FALSE;
                    Global_AdapterInUse[i].DeviceLocation.Reserved = 0;
                    CanBeUsed = TRUE;
                    break;
                }
                else
                {
                    CanBeUsed = FALSE;
                    break;
                }
            }

            else if(Lock == TRUE)
            {
                Global_AdapterInUse[i].InUse = TRUE;
                CanBeUsed = TRUE;
                break;
            }
        }
    }

    if(i == NAL_DRIVER_MAX_ADAPTERS && Lock == TRUE)
    {

        for(i=0; i<NAL_DRIVER_MAX_ADAPTERS; i++)
        {
            if(Global_AdapterInUse[i].DeviceLocation.Reserved == 0)
            {
                break;
            }
        }

        if(i<NAL_DRIVER_MAX_ADAPTERS)
        {
            Global_AdapterInUse[i].DeviceLocation.Reserved = NalDevice.Reserved;
            Global_AdapterInUse[i].InUse = Lock;
            CanBeUsed = TRUE;
        }
    }

    else if(i == NAL_DRIVER_MAX_ADAPTERS && Lock == FALSE)
    {
        CanBeUsed = TRUE;
    }

    return CanBeUsed;
}

BOOLEAN
_NalIsAdapterInUse(
    IN NAL_DEVICE_LOCATION NalDevice
    )
{
    UINTN i = 0;
    BOOLEAN IsInUse = FALSE;

    for(i=0; i<NAL_DRIVER_MAX_ADAPTERS; i++)
    {

        if(Global_AdapterInUse[i].DeviceLocation.Reserved == NalDevice.Reserved)
        {

            if(Global_AdapterInUse[i].InUse == TRUE)
            {
                IsInUse = TRUE;
                break;
            }
        }
    }

    return IsInUse;
}

UINT32
_NalDriverGetReferenceCount(
 VOID
 )
{
    return Global_DriverReferenceCount;
}

VOID
_NalDriverIncrementReferenceCount(
    VOID
    )
{

    spin_lock(&Global_AtomicTestSetSpinLock);
    Global_DriverReferenceCount++;
    spin_unlock(&Global_AtomicTestSetSpinLock);
}

VOID
_NalDriverDecrementReferenceCount(
    VOID
    )
{

    spin_lock(&Global_AtomicTestSetSpinLock);
    if(Global_DriverReferenceCount > 0)
    {
        Global_DriverReferenceCount--;
    }
    spin_unlock(&Global_AtomicTestSetSpinLock);
}

VOID
_NalDriverGetVersion(
 OUT CHAR* Version
 )
{
    strcpy(Version, NalLinuxDriverVersion);
}
