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
 *   linuxos_i.h
 *
 * Abstract:
 *   This file contains Linux specific prototypes & variable types
 *
 */


#ifndef _LINUX_OSINTERFACE_H_
#define _LINUX_OSINTERFACE_H_

#ifndef NAL_DRIVER
#include <sys/time.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#endif

#define NAL_LINUX_MAX_PATH 260
#define NAL_LINUX_INTERRUPT_SIGNATURE 0xA5BABA5A

#define NAL_LINUX_CHILD_STACK_SIZE 0x100000

typedef struct _NAL_LINUX_ISR_DEVICE
{
    UINT32 Signature;
    BOOLEAN DeviceInterrupted;
    KVOID* HardwareVirtualAddress;
    UINT32 Irq;
    UINT32 MacType;
} NAL_LINUX_ISR_DEVICE;

#if !defined(NAL_DRIVER)
typedef pthread_t NAL_THREAD_ID;

typedef struct _NAL_LINUX_TIMER_OBJECT
{
    NAL_TIMER_CALLBACK Callback;
    UINT32 ThreadId;
    struct itimerval TimerVal;
    VOID* Context;
} NAL_LINUX_TIMER_OBJECT;

#endif

#ifndef HIBYTE
    #define HIBYTE(_x) (UINT8)(((_x)>>8)&0xFF)
#endif

#ifndef LOBYTE
    #define LOBYTE(_x) (UINT8)((_x)&0xFF)
#endif

#ifndef HIWORD
    #define HIWORD(_x) ((UINT16)(((_x)>>16)&0xFFFF))
#endif

#ifndef LOWORD
    #define LOWORD(_x) ((UINT16)((_x)&0xFFFF))
#endif

#define HIDWORD(_x) ((UINT32)(((_x)>>32)&0xFFFFFFFF))
#define LODWORD(_x) ((UINT32)((_x)&0xFFFFFFFF))

#define LOW_BYTE(word) LOBYTE(word)
#define HIGH_BYTE(word) HIBYTE(word)

#define LOW_WORD(dword) LOWORD(dword)
#define HIGH_WORD(dword) HIWORD(dword)

#define MAKE_DATA_WORD_TCP_CHECKSUM(hi,low) \
    ((UINT16) ((((UINT16)(hi)) << 8) | (low)))

#define MAKE_DATA_WORD_UDP_CHECKSUM(hi,low) \
    ((UINT16) ((((UINT16)(hi)) << 8) | (low)))

#define MAKE_QWORD(hi,low) \
    ((UINT64) ((((UINT64)(hi)) << 32) | (low)))

#if defined NAL_BIG_ENDIAN

#define MAKE_WORD(hi,low) \
    ((UINT16) ((((UINT16)(low)) << 8) | (hi)))

#define MAKE_DWORD(hi,low) \
    ((UINT32) ((((UINT32)(low)) << 16) | (hi)))

#define BYTE_SWAP_WORD(value) (UINT16)( (((UINT16)(value) & 0x00ff)) | \
                                            (((UINT16)(value) & 0xff00)) )

#define BYTE_SWAP_DWORD(dword) (UINT32)( (((UINT32)(dword) & 0x000000ff) << 24) | \
                                            (((UINT32)(dword) & 0x0000ff00) << 8) | \
                                            (((UINT32)(dword) & 0x00ff0000) >> 8) | \
                                            (((UINT32)(dword) & 0xff000000) >> 24) )

#define BYTE_SWAP_QWORD(_dest,_src) \
{ \
    ((UINT8*)_dest)[0] = ((UINT8*)_src)[7]; \
    ((UINT8*)_dest)[1] = ((UINT8*)_src)[6]; \
    ((UINT8*)_dest)[2] = ((UINT8*)_src)[5]; \
    ((UINT8*)_dest)[3] = ((UINT8*)_src)[4]; \
    ((UINT8*)_dest)[4] = ((UINT8*)_src)[3]; \
    ((UINT8*)_dest)[5] = ((UINT8*)_src)[2]; \
    ((UINT8*)_dest)[6] = ((UINT8*)_src)[1]; \
    ((UINT8*)_dest)[7] = ((UINT8*)_src)[0]; \
}

#define WORD_SWAP(dword) WORD_SWAP_DWORD(dword)

#define BYTE_SWAP(word) BYTE_SWAP_WORD(word)

#else

#define MAKE_WORD(hi,low) \
    ((UINT16) ((((UINT16)(hi)) << 8) | (low)))

#define MAKE_DWORD(hi,low) \
    ((UINT32) ((((UINT32)(hi)) << 16) | (low)))

#define BYTE_SWAP_WORD(value) (UINT16)( (((UINT16)(value) & 0x00ff) << 8) | \
                                            (((UINT16)(value) & 0xff00) >> 8) )

#define BYTE_SWAP_DWORD(dword) (UINT32)( (((UINT32)(dword) & 0x000000ff) << 24) | \
                                            (((UINT32)(dword) & 0x0000ff00) << 8) | \
                                            (((UINT32)(dword) & 0x00ff0000) >> 8) | \
                                            (((UINT32)(dword) & 0xff000000) >> 24) )

#define WORD_SWAP_DWORD(value) (UINT32)( (((UINT32)(value) & 0x0000FFFF) << 16) | \
                                            (((UINT32)(value) & 0xFFFF0000) >> 16) )

#define BYTE_SWAP_QWORD(_dest,_src) \
{ \
    ((UINT8*)_dest)[0] = ((UINT8*)_src)[7]; \
    ((UINT8*)_dest)[1] = ((UINT8*)_src)[6]; \
    ((UINT8*)_dest)[2] = ((UINT8*)_src)[5]; \
    ((UINT8*)_dest)[3] = ((UINT8*)_src)[4]; \
    ((UINT8*)_dest)[4] = ((UINT8*)_src)[3]; \
    ((UINT8*)_dest)[5] = ((UINT8*)_src)[2]; \
    ((UINT8*)_dest)[6] = ((UINT8*)_src)[1]; \
    ((UINT8*)_dest)[7] = ((UINT8*)_src)[0]; \
}

#define WORD_SWAP(dword) WORD_SWAP_DWORD(dword)

#define BYTE_SWAP(word) BYTE_SWAP_WORD(word)
#endif

#include "naltypes.h"
#include "nalcodes.h"
#include <linuxnalioctl.h>
#include <hwbus_t.h>

#ifndef NAL_DRIVER
#include <linuxnallibrary.h>
#endif

NAL_STATUS
NalInitializeOs(VOID);

NAL_STATUS
NalExitOs(VOID);

KVOID*
NalKMemset(
    IN KVOID* Dest,
    IN int Value,
    IN UINTN Size
    );

VOID*
NalKtoUMemcpy(
    IN VOID* Dest,
    IN KVOID* Source,
    IN UINTN Size
    );

KVOID*
NalKtoKMemcpy(
    IN KVOID* Dest,
    IN KVOID* Source,
    IN UINTN Size
    );

KVOID*
NalUtoKMemcpy(
    IN KVOID* Dest,
    IN VOID* Source,
    IN UINTN Size
    );

BOOLEAN
_NalIsAdapterInUse(
    IN NAL_DEVICE_LOCATION NalDevice
    );

#endif
