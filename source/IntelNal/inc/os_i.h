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
 *   os_i.h
 *
 * Abstract:
 *   This file contains prototypes & datatypes for the OS Interface.
 *   The OS-specific header is included for each OS.
 *
 */


#ifndef _OSINTERFACE_H_
#define _OSINTERFACE_H_

#include <naltypes.h>
#include <nalcodes.h>

#define NAL_CVS_DATE_STRING "$Date: 2013/07/29 11:16:24 $"
#define NAL_DEBUG_DISABLED 0x00000000
#define NAL_DEBUG_APP 0x00000001
#define NAL_DEBUG_MACREG_READ 0x00000002
#define NAL_DEBUG_MACREG_WRITE 0x00000004
#define NAL_DEBUG_MACREG_RW (NAL_DEBUG_MACREG_READ | NAL_DEBUG_MACREG_WRITE)
#define NAL_DEBUG_TRANSMIT 0x00000008
#define NAL_DEBUG_RECEIVE 0x00000010
#define NAL_DEBUG_TXRX (NAL_DEBUG_TRANSMIT | NAL_DEBUG_RECEIVE)
#define NAL_DEBUG_TXRX_LOOP_CODE 0x00000020
#define NAL_DEBUG_SHARED_CODE 0x00000040
#define NAL_DEBUG_PHYREG_READ 0x00000080
#define NAL_DEBUG_PHYREG_WRITE 0x00000100
#define NAL_DEBUG_PHYREG_RW (NAL_DEBUG_PHYREG_READ | NAL_DEBUG_PHYREG_WRITE)
#define NAL_DEBUG_INIT 0x00000200
#define NAL_DEBUG_RELEASE 0x00000400
#define NAL_DEBUG_RESET_ADAPTER 0x00000800
#define NAL_DEBUG_RESET_LINK 0x00001000
#define NAL_DEBUG_GET_LINK 0x00002000
#define NAL_DEBUG_OS_LEVEL 0x00004000
#define NAL_DEBUG_APP_TRACE 0x00008000
#define NAL_DEBUG_SDK_TRACE 0x00010000
#define NAL_DEBUG_KERNEL 0x00020000
#define NAL_DEBUG_EEPROM 0x00040000
#define NAL_DEBUG_FLASH 0x00080000
#define NAL_DEBUG_DIAGS 0x00100000
#define NAL_DEBUG_MEMORY 0x00200000
#define NAL_DEBUG_BUS_SCAN 0x00400000
#define NAL_DEBUG_FAILURES 0x00800000
#define NAL_DEBUG_TIMESYNC 0x01000000
#define NAL_DEBUG_PROTOCOL_ENGINE 0x02000000
#define NAL_DEBUG_HMC 0x04000000
#define NAL_DEBUG_USER 0x80000000
#define NAL_DEBUG_ALL 0xFFFFFFFF

#define NAL_DEBUG_MASK_STACK_SIZE 256
#define NAL_DEBUG_SYSTEM_VARIABLE "QV_DEBUG_LOG"
#define NAL_DEFAULT_SDK_LOG_FILE_NAME "QVSDK.LOG"
extern char Global_Year[5];

#if defined(NAL_EFI)
#include <efi\efios_i.h>

#elif defined(NAL_LINUX)
#include <linux/linuxos_i.h>

#elif defined(NAL_LINUX_USERMODE)
#include <linux/linuxuseros_i.h>

#elif defined(NAL_SOLARIS)
#include <solaris/solarisos_i.h>

#elif defined(NAL_DOS)
#include <dos\dosos_i.h>

#elif defined(NAL_WINNT_WDM)
#include <winnt_wdm\winos_i.h>

#elif defined(NAL_WINNT4)
#include <winnt4\winos_i.h>

#else

#error "Undefined NAL Operating System in os_i.h"
#endif

#define NAL_MIN(_x,_y) ((_x > _y)? (_y) : (_x))
#define NAL_MAX(_x,_y) ((_x > _y)? (_x) : (_y))

#define NAL_ABS(_x) (((_x) > 0)? (_x) : ((_x) * -1))

#if defined (NAL_DRIVER)
extern BOOLEAN Global_DebugPrintEnabled;
#endif

extern UINT32 Global_DebugPrintMask;
extern BOOLEAN Global_FileDebugPrintEnabled;

#if !defined(NAL_DRIVER)
extern FILE* Global_DebugFilePointer;
#endif

#if defined(EFI64) || defined(_WIN64) || defined(LINUX64) || defined(LINUX64E)
#define PTR_TO_PHYSICAL(Pointer) (NAL_PHYSICAL_ADDRESS)(Pointer)
#define PHYSICAL_TO_PTR(Address) (VOID*)(Address)
#else
#define PTR_TO_PHYSICAL(Pointer) (NAL_PHYSICAL_ADDRESS)(UINT32)(Pointer)
#define PHYSICAL_TO_PTR(Address) (VOID*)(UINT32)(Address)

#endif

#if defined(EFI64) || defined(_WIN64) || defined(LINUX64) || defined(LINUX64E)
#define NAL_FIELD_OFFSET32(type,field) ((UINT32)(UINT64)(UINT32*)&(((type *)0)->field))
#else
#define NAL_FIELD_OFFSET32(type,field) ((UINT32)(UINT32*)&(((type *)0)->field))
#endif

#if defined(NAL_BIG_ENDIAN)
#define NAL_LITTLE_ENDIAN_16(_x) (UINT16)( (((UINT16)(_x) & 0x00ff) << 8) | \
                                            (((UINT16)(_x) & 0xff00) >> 8) )
#define NAL_LITTLE_ENDIAN_32(dword) (UINT32)( (((UINT32)(dword) & 0x000000ff) << 24) | \
                                            (((UINT32)(dword) & 0x0000ff00) << 8) | \
                                            (((UINT32)(dword) & 0x00ff0000) >> 8) | \
                                            (((UINT32)(dword) & 0xff000000) >> 24) )
#define NAL_LITTLE_ENDIAN_64(_x) \
    (((UINT64)((_x) & 0xff00000000000000ull) >> 56) | \
    ((UINT64)((_x ) & 0xff000000000000ull) >> 40) | \
    ((UINT64)((_x ) & 0xff0000000000ull) >> 24) | \
    ((UINT64)((_x ) & 0xff00000000ull) >> 8) | \
    ((UINT64)((_x ) & 0xff000000ull) << 8) | \
    ((UINT64)((_x ) & 0xff0000ull) << 24) | \
    ((UINT64)((_x ) & 0xff00ull) << 40) | \
    ((UINT64)((_x ) & 0xffull) << 56))

#else
#define NAL_LITTLE_ENDIAN_16(_x) (_x)
#define NAL_LITTLE_ENDIAN_32(_x) (_x)
#define NAL_LITTLE_ENDIAN_64(_x) (_x)
#endif

UINT8
NalReadPort8(
    IN PORT_ADDR Port
    );

UINT16
NalReadPort16(
    IN PORT_ADDR Port
    );

UINT32
NalReadPort32(
    IN PORT_ADDR Port
    );

BOOLEAN
NalWritePort8(
    IN PORT_ADDR Port,
    IN UINT8 Value
    );

BOOLEAN
NalWritePort16(
    IN PORT_ADDR Port,
    IN UINT16 Value
    );

BOOLEAN
NalWritePort32(
    IN PORT_ADDR Port,
    IN UINT32 Value
    );

UINT8
NalReadRegister8(
    IN KVOID* Address
    );

UINT16
NalReadRegister16(
    IN KVOID* Address
    );

UINT32
NalReadRegister32(
    IN KVOID* Address
    );

BOOLEAN
NalWriteRegister8(
    IN KVOID* Address,
    IN UINT8 Value
    );

BOOLEAN
NalWriteRegister16(
    IN KVOID* Address,
    IN UINT16 Value
    );

BOOLEAN
NalWriteRegister32(
    IN KVOID* Address,
    IN UINT32 Value
    );

NAL_STATUS
NalMmapAddress(
    OUT KVOID** VirtualAddress,
    IN NAL_PHYSICAL_ADDRESS PhysicalAddress,
    IN OUT UINT32* Length
    );

NAL_STATUS
NalUnmapAddress(
    IN KVOID* VirtualAddress,
    IN NAL_PHYSICAL_ADDRESS PhysicalAddress,
    IN UINT32 Length
    );

UINT64
NalGetTimeStamp(VOID);

UINT64
NalGetTimeStampsPerMicrosecond(VOID);

UINT64
NalGetTimeStampsPerMillisecond(VOID);

NAL_STATUS
NalRegisterTimerCallback(
    IN NAL_TIMER_CALLBACK TimerCallback,
    IN OUT UINT32* TimerInterval,
    IN VOID* Context,
    OUT UINT32* CallbackId
    );

NAL_STATUS
NalUnregisterTimerCallback(
    IN UINT32 CallbackId
    );

VOID
NalDelayMilliseconds(
    IN UINT32 Milliseconds
    );

VOID
NalDelayMicroseconds(
    IN UINT32 Microseconds
    );

NAL_PHYSICAL_ADDRESS
NalGetPhysicalMemoryAddress(
    IN KVOID* VirtualAddress
    );

VOID*
_NalAllocateMemory(
    IN UINT32 ByteCount,
    IN CHAR* NamedLocator,
    IN UINT32 LineNumber
    );

VOID
_NalFreeMemory(
    IN VOID* Address,
    IN CHAR* NamedLocator,
    IN UINT32 LineNumber
    );

KVOID*
_NalAllocateMemoryNonPaged(
    IN UINT32 ByteCount,
    IN UINT32 Alignment,
    OUT NAL_PHYSICAL_ADDRESS* PhysicalAddress,
    IN CHAR* NamedLocator,
    IN UINT32 LineNumber
    );

VOID
_NalFreeMemoryNonPaged(
    IN KVOID* Address,
    IN CHAR* NamedLocator,
    IN UINT32 LineNumber
    );

#define NalAllocateMemory(ByteCount) \
    _NalAllocateMemory((ByteCount), __FILE__, __LINE__)

#define NalFreeMemory(VirtualAddress) \
    _NalFreeMemory((VirtualAddress), __FILE__, __LINE__)

#define NalAllocateMemoryNonPaged(ByteCount,Alignment,PhysicalAddress) \
    _NalAllocateMemoryNonPaged((ByteCount), (Alignment), (PhysicalAddress), \
                               __FILE__, __LINE__)

#define NalFreeMemoryNonPaged(VirtualAddress) \
    _NalFreeMemoryNonPaged((VirtualAddress), __FILE__, __LINE__)

UINT32
NalAtomicIncrement32(
    IN UINT32* Address
    );

UINT32
NalAtomicDecrement32(
    IN UINT32* Address
    );

UINT32
NalAtomicTestSet32(
    IN UINT32* Address,
    IN UINT32 Test,
    IN UINT32 Set
    );

VOID
NalAcquireSpinLock(
    IN NAL_SPIN_LOCK* SpinLock
    );

VOID
NalReleaseSpinLock(
    IN NAL_SPIN_LOCK* SpinLock
    );

VOID
NalInitializeSpinLock(
    IN NAL_SPIN_LOCK* SpinLock
    );

VOID
NalFreeSpinLock(
    IN NAL_SPIN_LOCK* SpinLock
    );

NAL_STATUS
NalCheckSecurity(VOID);

NAL_STATUS
NalDebugPrint(
    IN CHAR* Format,
    ...
    );

NAL_STATUS
_NalDebugPrintToDebugger(
    IN CHAR* StringToPrint
    );

NAL_STATUS
NalDebugPrintSupport(
    OUT UINT32* DebugCapabilities
    );

NAL_STATUS
NalDebugPrintOpenFile(
    IN CHAR* DebugFileName
    );

NAL_STATUS
NalDebugPrintCloseFile(VOID);

#if defined(NAL_DRIVER)
VOID
NalEnableDebugPrint(
    IN BOOLEAN Enable
    );
#else
VOID
NalEnableDebugPrint(
    IN UINT32 Mask
    );
#endif

BOOLEAN
_NalCheckSystemVariableForDebugMask(
    OUT UINT32* Mask
    );

NAL_STATUS
_NalSdkDebugPrintOpenFile(VOID);

VOID
_NalEnableSdkDebugPrint(
    IN UINT32 Mask
    );

NAL_STATUS
_NalSdkDebugPrintCloseFile(VOID);

VOID
_NalClearScreen(VOID);

VOID
NalRebootSystem(VOID);

BOOLEAN
NalIsTargetOperatingSystem(
    OUT NAL_OS_TYPE* OsType
    );

NAL_STATUS
NalMaskedDebugPrint(
    IN UINT32 Mask,
    IN CHAR* Format,
    ...
    );

NAL_STATUS
NalDebugPrintPushMask(
    IN UINT32 Mask
    );

NAL_STATUS
NalDebugPrintCheckAndPushMask(
    IN UINT32 MaskToCheck,
    IN UINT32 MaskToPush,
    OUT UINT32* IndexToCheck,
    IN BOOLEAN AddToExisting
    );

UINT32
NalDebugPrintPopMask(VOID);

UINT32
NalDebugPrintCheckAndPopMask(
    IN UINT32 MaskToCheck,
    IN UINT32 IndexToCheck
    );

UINT32
NalGetCurrentDebugPrintMask(VOID);

VOID
_NalEnableDebugPrint(
    IN BOOLEAN Enable
    );

BOOLEAN
NalIsDebugFileOpen(VOID);

UINT32
NalGetMaximumContiguousAllocationSize(VOID);

BOOLEAN
NalCanMapMemoryToUserSpace(VOID);

#if defined(NAL_DRIVER)

NAL_STATUS
NalMmapAddressEx(
    IN OUT KVOID** VirtualAddress,
    IN NAL_PHYSICAL_ADDRESS PhysicalAddress,
    IN OUT UINT32* Length,
    IN UINTN ProcessId
    );

NAL_STATUS
NalUnmapAddressEx(
    IN KVOID* VirtualAddress,
    IN NAL_PHYSICAL_ADDRESS PhysicalAddress,
    IN UINT32 Length,
    IN UINTN ProcessId
    );

KVOID*
_NalAllocateMemoryNonPagedEx(
    IN UINT32 ByteCount,
    IN UINT32 Alignment,
    IN UINTN ProcessId,
    OUT NAL_PHYSICAL_ADDRESS* PhysicalAddress,
    IN CHAR* NamedLocator,
    IN UINT32 LineNumber
    );

VOID
_NalFreeMemoryNonPagedEx(
    IN KVOID* Address,
    IN UINTN ProcessId,
    IN CHAR* NamedLocator,
    IN UINT32 LineNumber
    );

NAL_PHYSICAL_ADDRESS
NalGetPhysicalMemoryAddressEx(
    IN KVOID* VirtualAddress,
    IN UINTN ProcessId
    );

#endif

VOID
NalDisableMapMemoryToUserSpace(VOID);

BOOLEAN
NalOsSupportsIoMode(VOID);

UINT32
_NalBitSwap(
    IN UINT32 Data,
    IN UINT32 Bits
    );

char*
NalGetCopyrightYear(VOID);

#if !defined(NAL_DRIVER)
UINT32
NalGetLogicalCpuCount(VOID);

NAL_STATUS
NalCreateThread(
    IN NAL_THREAD_FUNC ThreadFunction,
    IN VOID* Context,
    OUT NAL_THREAD_ID* ThreadId
    );

NAL_STATUS
NalTerminateThread(
    IN NAL_THREAD_ID* ThreadId
    );

BOOLEAN
NalIsThreadRunning(
    IN NAL_THREAD_ID* ThreadId
    );
#endif

#endif
