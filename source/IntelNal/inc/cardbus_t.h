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
 *   cardbus_t.h
 *
 * Abstract:
 *   This file contains NAL Cardbus data types.
 *
 */


#include <naltypes.h>

#ifndef _CARDBUS_H_
#define _CARDBUS_H_

#define CARDBUS_0 (1 << 31)

#pragma pack(1)

typedef union _CARDBUS_SLOT_ID
{
    UINT32 SlotId;
#if defined(NAL_BIG_ENDIAN)
    struct _CARDBUS_PARTS
    {
        UINT32 Reserved : 7;
        UINT32 Enable : 1;
        UINT32 Bus : 8;
        UINT32 Function : 3;
        UINT32 Device : 5;
        UINT32 _Byte : 2;
        UINT32 Dword : 6;
    } CARDBUS_PARTS;
#else
    struct _CARDBUS_PARTS
    {
        UINT32 _Byte : 2;
        UINT32 Dword : 6;
        UINT32 Function : 3;
        UINT32 Device : 5;
        UINT32 Bus : 8;
        UINT32 Reserved : 7;
        UINT32 Enable : 1;
    } CARDBUS_PARTS;
#endif
} CARDBUS_SLOT_ID;

typedef union _CARDBUS_CIS_POINTER
{
    UINT32 CISPointer;
    struct _CARDBUS_CIS_POINTER_REGISTER
    {

        UINT32 AddressSpaceIndicator : 3;

        UINT32 AddressSpaceOffset : 25;

        UINT32 ROMImage : 4;

    } CARDBUS_CIS_POINTER_REGISTER;
} CARDBUS_CIS_POINTER;

typedef struct _CARDBUS_DEVICE
{
    UINT32 Reserved;
    UINT16 CommandRegister;
    UINT16 StatusRegister;
    UINT32 Reserved1;
    UINT8 CacheLineSize;
    UINT8 LatencyTimer;
    UINT8 HeaderType;
    UINT8 Bist;
    UINT32 Bar0;
    UINT32 Bar1;
    UINT32 Bar2;
    UINT32 Bar3;
    UINT32 Bar4;
    UINT32 Bar5;
    UINT32 CardBusCisPointer;
    UINT32 Reserved2;
    UINT32 ExpansionRomBaseAddress;
    UINT32 Reserved3;
    UINT32 Reserved4;
    UINT8 Reserved5;
    UINT8 InterruptPin;
    UINT16 Reserved6;
} CARDBUS_DEVICE;

typedef struct _CARDBUS_BRIDGE
{
    UINT16 VendorId;
    UINT16 DeviceId;
    UINT16 CommandRegister;
    UINT16 StatusRegister;
    UINT8 RevisionId;
    UINT8 ProgIf;
    UINT8 SubclassCode;
    UINT8 ClassCode;
    UINT8 CacheLineSize;
    UINT8 LatencyTimer;
    UINT8 HeaderType;
    UINT8 Bist;
    UINT8 PciBusNumber;
    UINT8 CardbusBusNumber;
    UINT8 SubordinateBusNumber;
    UINT8 CardbusLatencyTimer;
    UINT32 Bar0;
    UINT32 Limit0;
    UINT32 Bar1;
    UINT32 Limit1;
    UINT16 IoBaseRegister0Lower;
    UINT16 IoBaseRegister0OptionalUpper;
    UINT16 IoLimitRegister0Lower;
    UINT16 IoLimitRegiseter0OptionalUpper;
    UINT16 IoBaseRegister1Lower;
    UINT16 IoBaseRegister1OptionalUpper;
    UINT16 IoLimitRegister1Lower;
    UINT16 IoLimitRegiseter1OptionalUpper;
    UINT8 InterruptLine;
    UINT8 InterruptPin;
    UINT16 BridgeControl;
    UINT16 SubsystemVendorId;
    UINT16 SubsystemId;
    UINT32 Optional16BitPcCardBaseAddress;
} CARDBUS_BRIDGE;

#pragma pack()
#endif
