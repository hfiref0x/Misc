/*

  This file is provided under a dual BSD/GPLv2 license.  When using or
  redistributing this file, you may do so under either license.

  GPL LICENSE SUMMARY

  Copyright(c) 1999 - 2013 Intel Corporation. All rights reserved.

  This program is free software; you can redistribute it and/or modify
  it under the terms of version 2 of the GNU General Public License as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
  The full GNU General Public License is included in this distribution
  in the file called LICENSE.GPL.

  Contact Information:
  e1000-devel Mailing List <e1000-devel@lists.sourceforge.net>
  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497

  BSD LICENSE

  Copyright(c) 1999 - 2013 Intel Corporation. All rights reserved.
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the
      distribution.
    * Neither the name of Intel Corporation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

/*
 *
 * Module Name:
 *   osdevice_i.h
 *
 * Abstract:
 *   This file contains includes the OS specific osdevice file for the
 *   particular operating system being defined.
 *
 */


#ifndef _OSDEVICE_I_H_
#define _OSDEVICE_I_H_

#ifndef NAL_DRIVER
#include <device_t.h>

NAL_STATUS
_NalInitializeAdapterOs(
    IN NAL_DEVICE_LOCATION DeviceLocation,
    IN VOID* DeviceInfo,
    IN NAL_ADAPTER_STRUCTURE* NalAdapter,
    IN UINT32 InitFlags
    );

NAL_STATUS
_NalPostInitializeAdapterOs(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter
    );

NAL_STATUS
_NalReleaseAdapterOs(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter
    );

NAL_STATUS
_NalInitializeInterruptsOs(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter
    );

NAL_STATUS
_NalUninitializeInterruptsOs(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter
    );

BOOLEAN
_NalHasInterruptOccurredOs(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter
    );

NAL_STATUS
_NalClearInterruptsOs(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter
    );

BOOLEAN
_NalIsDeviceDriverLoadedOs(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter
    );

NAL_STATUS
_NalUnloadDeviceDriverOs(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter
    );

BOOLEAN
_NalReloadDeviceDriverOs(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter
    );

UINT8
_NalReadPortOs8(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter,
    IN PORT_ADDR Port
    );

UINT16
_NalReadPortOs16(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter,
    IN PORT_ADDR Port
    );

UINT32
_NalReadPortOs32(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter,
    IN PORT_ADDR Port
    );

BOOLEAN
_NalWritePortOs8(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter,
    IN PORT_ADDR Port,
    IN UINT8 Value
    );

BOOLEAN
_NalWritePortOs16(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter,
    IN PORT_ADDR Port,
    IN UINT16 Value
    );

BOOLEAN
_NalWritePortOs32(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter,
    IN PORT_ADDR Port,
    IN UINT32 Value
    );

UINT8
_NalReadRegisterOs8(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter,
    IN KVOID* Address
    );

UINT16
_NalReadRegisterOs16(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter,
    IN KVOID* Address
    );

UINT32
_NalReadRegisterOs32(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter,
    IN KVOID* Address
    );

BOOLEAN
_NalWriteRegisterOs8(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter,
    IN KVOID* Address,
    IN UINT8 Value
    );

BOOLEAN
_NalWriteRegisterOs16(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter,
    IN KVOID* Address,
    IN UINT16 Value
    );

BOOLEAN
_NalWriteRegisterOs32(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter,
    IN KVOID* Address,
    IN UINT32 Value
    );

KVOID*
_NalAllocateMemoryNonPagedOs(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter,
    IN UINT32 AllocationAmount,
    IN UINT32 Alignment,
    OUT NAL_PHYSICAL_ADDRESS* PhysicalAddress
    );

VOID
_NalFreeMemoryNonPagedOs(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter,
    IN KVOID* Address
    );

BOOLEAN
_NalMarkAdapterInUse(
    IN NAL_ADAPTER_STRUCTURE* NalAdapter,
    IN NAL_DEVICE_LOCATION NalDevice,
    IN BOOLEAN Lock
    );

BOOLEAN
_NalIsDriverlessModeOs(
    VOID
    );

#endif

#if defined(NAL_EFI)
#include <efi\efidevice_i.h>

#elif defined(NAL_LINUX)
#if defined(NAL_DRIVER)
#include <linux/linuxdriverdevice_i.h>
#else
#include <linux/linuxdevice_i.h>
#endif

#elif defined(NAL_SOLARIS)
#if defined(NAL_DRIVER)
#include <solaris/solarisdriverdevice_i.h>
#else
#include <solaris/solarisdevice_i.h>
#endif

#elif defined(NAL_DOS)
#include <dos\dosdevice_i.h>

#elif defined(NAL_WINNT_WDM)
#if defined(NAL_DRIVER)
#include <winnt_wdm\windriverdevice_i.h>
#else
#include <winnt_wdm\windevice_i.h>
#endif

#elif defined(NAL_WINNT4)
#if defined(NAL_DRIVER)
#include <winnt4\windriverdevice_i.h>
#else
#include <winnt4\windevice_i.h>
#endif

#else

#error "Undefined NAL Operating System in osdevice_i.h."
#endif

typedef struct _NAL_OS_DEVICE
{
    NAL_MAC_TYPE MacType;
    NAL_DEVICE_LOCATION DeviceLocation;
    NAL_PHYSICAL_ADDRESS PhysicalAddress;
    KVOID* VirtualAddress;
    PORT_ADDR PortAddress;
    BOOLEAN IsDriverLoaded;
    BOOLEAN HasInterruptOccurred;

    NAL_OS_SPECIFIC_DEVICE OsSpecificDevice;

} NAL_OS_DEVICE;

#endif
