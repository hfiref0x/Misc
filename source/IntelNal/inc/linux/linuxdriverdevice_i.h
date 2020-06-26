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
 *   linuxdriverdevice_i.h
 *
 * Abstract:
 *   This file contains Linux Specific OS functions that are required
 * to correctly communicate with a device in Linux.
 */


#ifndef _LINUXDRIVERDEVICE_I_H_
#define _LINUXDRIVERDEVICE_I_H_

#include <naltypes.h>
#include <nalcodes.h>

BOOLEAN
_NalMarkAdapterInUse(
    IN NAL_DEVICE_LOCATION NalDevice,
    IN BOOLEAN Lock
    );

typedef struct _NAL_OS_SPECIFIC_DEVICE
{
    UINT32 ReferenceCount;
} NAL_OS_SPECIFIC_DEVICE;

#define _NalReadPortOs8(a,p) NalReadPort8(p)
#define _NalReadPortOs16(a,p) NalReadPort16(p)
#define _NalReadPortOs32(a,p) NalReadPort32(p)
#define _NalWritePortOs8(a,p,v) NalWritePort8(p,v)
#define _NalWritePortOs16(a,p,v) NalWritePort16(p,v)
#define _NalWritePortOs32(a,p,v) NalWritePort32(p,v)
#define _NalReadRegisterOs8(a,d) NalReadRegister8(d)
#define _NalReadRegisterOs16(a,d) NalReadRegister16(d)
#define _NalReadRegisterOs32(a,d) NalReadRegister32(d)
#define _NalWriteRegisterOs8(a,d,v) NalWriteRegister8(d,v)
#define _NalWriteRegisterOs16(a,d,v) NalWriteRegister16(d,v)
#define _NalWriteRegisterOs32(a,d,v) NalWriteRegister32(d,v)

KVOID*
_NalAllocateMemoryNonPagedPci(
    IN KVOID* PDev,
    IN UINT32 ByteCount,
    IN UINT32 Alignment,
    OUT NAL_PHYSICAL_ADDRESS* PhysicalAddress,
    IN CHAR* NamedLocator,
    IN UINT32 LineNumber
    );

VOID
NalFreeMemoryNonPagedPci(
    IN KVOID* PDev,
    IN KVOID* Address,
    IN NAL_PHYSICAL_ADDRESS PhysicalAddress,
    IN UINT32 Size
    );

#endif
