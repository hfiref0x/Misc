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
 *   hwbus_t.h
 *
 * Abstract:
 *   This file includes all the types required for the NAL hardware
 *   bus interface.
 *
 */


#ifndef _NAL_HWBUS_TYPES_H_
#define _NAL_HWBUS_TYPES_H_

#include "pci_t.h"
#include "cardbus_t.h"

#define NAL_MAX_BARS 6
#define NAL_DEVICE_SIGNATURE 0xA55A5AA5

#if defined(NAL_EFI)
typedef struct _NAL_OS_SLOT_ID
{
    PCI_SLOT_ID Pci;
    UINT32 Signature;
    VOID* Handle;
} NAL_OS_SLOT_ID;

#elif defined(NAL_LINUX)
typedef struct _NAL_OS_SLOT_ID
{
    PCI_SLOT_ID Pci;
    UINT32 Signature;
} NAL_OS_SLOT_ID;

#elif defined(NAL_SOLARIS)
typedef struct _NAL_OS_SLOT_ID
{
    PCI_SLOT_ID Pci;
    UINT32 Signature;
    INT32 DevInfo;
} NAL_OS_SLOT_ID;

#elif defined(NAL_DOS)
typedef struct _NAL_OS_SLOT_ID
{
    PCI_SLOT_ID Pci;
    UINT32 Signature;
} NAL_OS_SLOT_ID;

#elif defined(NAL_WINNT_WDM)
typedef struct _NAL_OS_SLOT_ID
{
    PCI_SLOT_ID Pci;
    CHAR RegistryKey[250];
    UINT32 Signature;
} NAL_OS_SLOT_ID;

#elif defined(NAL_WINNT4)
typedef struct _NAL_OS_SLOT_ID
{
    PCI_SLOT_ID Pci;
    UINT32 Signature;
} NAL_OS_SLOT_ID;

#else

#error "Undefined NAL Operating System in hwbus_t.h."
#endif

typedef union _VF_SLOT_ID
{
    struct
    {
        UINT32 SlotId;
        UINT32 ReservedForSignature;
        UINT32 ParentSlotId;
        UINT16 SupportedModule;
        BOOLEAN IsVirtualDevice;
        UINT8 Pad;
    } slot_id;
    struct
    {
        struct
        {
#if defined (NAL_BIG_ENDIAN)
            UINT32 DwordLo : 2;
            UINT32 _Byte : 2;
            UINT32 Reserved : 4;
            UINT32 DwordHi : 8;
            UINT32 Device : 7;
            UINT32 Function : 1;
            UINT32 Bus : 8;
#else
            UINT32 Bus : 8;
            UINT32 Device : 7;
            UINT32 Function : 1;
            UINT32 Dword : 10;
            UINT32 _Byte : 2;
            UINT32 Reserved : 4;
#endif
        } vf_slot_id;
        UINT32 ReservedForSignature;
        PCI_EXPRESS_SLOT_ID ParentDevice;
    };
} VF_SLOT_ID;

typedef union _NAL_DEVICE_LOCATION
{
    PCI_SLOT_ID Pci;
    PCI_EXPRESS_SLOT_ID PciExpress;
    VF_SLOT_ID Vf;
    CARDBUS_SLOT_ID Cardbus;
    NAL_OS_SLOT_ID OsDeviceLocation;
    UINT64 Reserved;
} NAL_DEVICE_LOCATION;

#pragma pack(1)
typedef struct _NAL_SUBST_DEVICE_TABLE
{
    UINT16 DeviceId;
    NAL_DEVICE_LOCATION DeviceLocation;
} NAL_SUBST_DEVICE_TABLE;

typedef struct _PCIEXP_CONFIG_STORE
{
    NAL_DEVICE_LOCATION DeviceLocation;
    PCI_EXPRESS_CONFIG_SPACE ConfigSpace;
}PCIEXP_CONFIG_STORE;

typedef enum _NAL_IO_RESOURCE_TYPE
{
    NAL_IO_TYPE_UNUSED = 0,
    NAL_IO_TYPE_IO,
    NAL_IO_TYPE_MEM
} NAL_IO_RESOURCE_TYPE;

typedef struct _NAL_IO_RESOURCE
{
    NAL_IO_RESOURCE_TYPE Type;
    NAL_PHYSICAL_ADDRESS MemoryAddress;
} NAL_IO_RESOURCE;

typedef struct _NAL_INTERRUPT_INFO
{
    BOOLEAN Valid;
    UINT32 Irq;
    UINT32 Vector;
    UINT32 Trigger;
    UINT32 Affinity;
    UINT32 Mode;
    UINT64 Reserved;
} NAL_INTERRUPT_INFO;

typedef enum _NAL_DEVICE_CLASS
{
    NAL_CLASS_LEGACY = 0,
    NAL_CLASS_STORAGE,
    NAL_CLASS_NETWORK,
    NAL_CLASS_DISPLAY,
    NAL_CLASS_MULTIMEDIA,
    NAL_CLASS_MEMORY_CONTROLLER,
    NAL_CLASS_BRIDGE_DEVICES,
    NAL_CLASS_SIMPLE_COMMUNICATION,
    NAL_CLASS_SYSTEM,
    NAL_CLASS_USB,
    NAL_CLASS_UNKNOWN = 0xFF
} NAL_DEVICE_CLASS;

typedef UINT8 NAL_DEVICE_SUBCLASS;

typedef struct _NAL_DEVICE
{
    UINT32 Signature;
    UINT16 VendorId;
    UINT16 DeviceId;
    UINT16 SubSystemId;
    UINT16 SubVendorId;
    UINT8 RevisionId;
    NAL_DEVICE_CLASS Class;
    NAL_DEVICE_SUBCLASS SubClass;
    UINT32 ResourceCount;
    NAL_IO_RESOURCE IoResource[NAL_MAX_BARS];
    NAL_INTERRUPT_INFO InterruptInfo;
    NAL_DEVICE_LOCATION DeviceLocation;
    BOOLEAN DeviceIsOsConfigured;
} NAL_DEVICE;
#pragma pack()

typedef struct _NAL_ADAPTER_VENDOR_INFO
{
    UINT16 Vendor;
    UINT16 Device;
    UINT16 SubVendor;
    UINT16 SubDevice;
    UINT8 Revision;
} NAL_ADAPTER_VENDOR_INFO;

#endif
