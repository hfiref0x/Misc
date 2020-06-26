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
 *   pci_i.h
 *
 *   Abstract:
 *     This file contains the NAL PCI interface generic prototypes.
 *     These prototypes are exposed externally.
 *
 */


#ifndef _PCIINTERFACE_H_
#define _PCIINTERFACE_H_

#include <naltypes.h>
#include <nalcodes.h>
#include <hwbus_t.h>

#if defined(NAL_EFI)
#include <efi\efipci_i.h>

#elif defined(NAL_LINUX)
#include <linux/linuxpci_i.h>

#elif defined(NAL_LINUX_USERMODE)
#include <linux/linuxpci_i.h>

#elif defined(NAL_SOLARIS)
#include <solaris/solarispci_i.h>

#elif defined(NAL_DOS)
#include <dos\dospci_i.h>

#elif defined(NAL_WINNT_WDM)
#include <winnt_wdm\winpci_i.h>

#elif defined(NAL_WINNT4)
#include <winnt4\winpci_i.h>

#else

#error "Undefined NAL Operating System in pci_i.h."
#endif

#define PCI_CONFIG_CAPABILITIES_POINTER 0x34

NAL_STATUS
NalScanPciBus(
    OUT NAL_DEVICE_LOCATION* PciLocations,
    IN OUT UINT32* Count
    );

NAL_STATUS
NalGetPciDeviceInformation(
    IN NAL_DEVICE_LOCATION PciLocation,
    OUT PCI_DEVICE* Device,
    IN UINT32 DwordCount
    );

NAL_STATUS
NalReadPciConfig32(
    IN NAL_DEVICE_LOCATION PciLocation,
    IN UINT32 DwordIndex,
    OUT UINT32* Value
    );

NAL_STATUS
NalReadPciConfigVariable(
    IN NAL_DEVICE_LOCATION PciLocation,
    IN UINT32 DwordIndex,
    IN UINT8 ByteMask,
    OUT UINT32* Value
    );

NAL_STATUS
NalWritePciConfig32(
    IN NAL_DEVICE_LOCATION PciLocation,
    IN UINT32 DwordIndex,
    IN UINT32 Data
    );

NAL_STATUS
NalWritePciConfigVariable(
    IN NAL_DEVICE_LOCATION PciLocation,
    IN UINT32 DwordIndex,
    IN UINT8 ByteMask,
    IN UINT32 Data
    );

NAL_STATUS
_NalWritePciConfig16(
    IN NAL_DEVICE_LOCATION PciLocation,
    IN UINT32 ByteOffset,
    IN UINT16 Value
    );

BOOLEAN
NalIsPcixAdapter(
    IN NAL_DEVICE_LOCATION* PciLocation OPTIONAL,
    IN PCI_DEVICE* Device OPTIONAL
    );

NAL_STATUS
NalIsPciExAdapter(
    IN NAL_DEVICE_LOCATION* PciLocation,
    IN PCI_DEVICE* Device
    );

VOID*
NalFindPciCapability(
    IN PCI_DEVICE* Device,
    IN UINT8 CapabilityId,
    OUT UINT32* ByteIndex
    );

BOOLEAN
NalHasPciCapability(
    IN NAL_DEVICE_LOCATION* DeviceLocation,
    IN NAL_PCI_CAPABILITY Capability,
    OUT UINT32* ByteIndex
    );

NAL_STATUS
NalGetPciMaxFunction(
    IN NAL_DEVICE_LOCATION* DeviceLocation,
    OUT UINT32* MaxFunction
    );

#endif
