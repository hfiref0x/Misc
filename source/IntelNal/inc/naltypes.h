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
 *   naltypes.h
 *
 * Abstract:
 *   NAL types for each OS are declared here.
 *
 */


#ifndef _NALTYPES_H_
#define _NALTYPES_H_ 

#if defined(NAL_EFI)

#include <efi.h>

typedef VOID KVOID;
typedef UINT16 PORT_ADDR;
typedef UINT64 NAL_PHYSICAL_ADDRESS;
typedef char CHAR;
typedef CHAR16 WCHAR;
typedef UINT32 NAL_STATUS;

typedef volatile UINT32 NAL_SPIN_LOCK;

#define NAL_MAX_INTERRUPT_VECTORS 256
#define NAL_MAX_REFERENCES 32

typedef struct _NAL_VECTOR
{
    volatile BOOLEAN NalInterruptVector;
    UINT32 ReferenceCount;
} NAL_VECTOR;

typedef VOID (*NAL_SERVICE_ROUTINE) (VOID);

#if defined(NAL_DEBUG)
#define ASSERTEX(X,f,l) 
#else
#define ASSERTEX(X,f,l) 
#endif

#elif defined(NAL_DOS)

#define _EXACT_WIDTH_INTS 

typedef void VOID;
typedef void KVOID;
typedef signed char INT8;
typedef unsigned char UINT8;
typedef signed short INT16;
typedef unsigned short UINT16;
typedef signed long INT32;
typedef unsigned long UINT32;
typedef signed __int64 INT64;
typedef unsigned __int64 UINT64;
typedef signed int INTN;
typedef unsigned int UINTN;

typedef UINT8 BOOLEAN;
typedef UINT16 PORT_ADDR;
typedef UINT64 NAL_PHYSICAL_ADDRESS;
typedef char CHAR;
typedef UINT16 WCHAR;
typedef UINT32 NAL_STATUS;

typedef volatile UINT32 NAL_SPIN_LOCK;

#define INLINE __inline

#define NAL_MAX_INTERRUPT_VECTORS 256
#define NAL_MAX_REFERENCES 32

typedef struct _NAL_VECTOR
{
    volatile BOOLEAN NalInterruptVector;
    UINT32 ReferenceCount;
} NAL_VECTOR;

typedef VOID (*NAL_SERVICE_ROUTINE) (VOID);

#if defined(NAL_DEBUG)
#include <stdio.h>
#include <stdlib.h>
#define ASSERT(X) if (!(X)) {printf("ASSERT %s (%d): " #X "\n", __FILE__, __LINE__); getchar();}
#define ASSERTEX(X,f,l) if (!(X)) {printf("ASSERT %s (%d): " #X "\n", f, l); getchar();}
#else
#define ASSERT(X) 
#define ASSERTEX(X,f,l) 
#endif

#elif defined(NAL_LINUX)

#ifdef NAL_DRIVER

#include <linux/time.h>

#undef VOID
#endif

#ifndef VOID
#define VOID void
#endif
#define KVOID void
typedef signed char INT8;
typedef unsigned char UINT8;
typedef signed short INT16;
typedef unsigned short UINT16;
typedef signed int INT32;
typedef unsigned int UINT32;
typedef signed long long INT64;
typedef unsigned long long UINT64;
typedef signed long INTN;
typedef unsigned long UINTN;

typedef UINT8 BOOLEAN;
typedef UINT16 PORT_ADDR;
typedef UINT64 NAL_PHYSICAL_ADDRESS;
typedef char CHAR;
typedef UINT16 WCHAR;
typedef UINT32 NAL_STATUS;

#define INLINE static inline

#if defined(LINUXPPC64)
#define NAL_BIG_ENDIAN 1
#endif
#if defined(LINUXPPC)
#define NAL_BIG_ENDIAN 1
#endif

#if defined(NAL_DRIVER)
typedef UINTN NAL_SPIN_LOCK;
#else
#include <sys/types.h>

typedef pthread_mutex_t NAL_SPIN_LOCK;

#include <stdint.h>
#endif

#if defined(NAL_DRIVER)
  #if defined(LINUXPPC)
    #define NAL_BIG_ENDIAN 1
  #endif
  #if defined(LINUXPPC64)
    #define NAL_BIG_ENDIAN 1
  #endif
#endif

#if defined(NAL_DEBUG)
#define ASSERT(X) 
#define ASSERTEX(X,f,l) 
#else
#define ASSERT(X) 
#define ASSERTEX(X,f,l) 
#endif

#elif defined(NAL_SOLARIS)

#ifndef VOID
typedef void VOID;
#endif
typedef void KVOID;
typedef signed char INT8;
typedef unsigned char UINT8;
typedef signed short INT16;
typedef unsigned short UINT16;
typedef signed int INT32;
typedef unsigned int UINT32;
typedef signed long long INT64;
typedef unsigned long long UINT64;
typedef signed long INTN;
typedef unsigned long UINTN;

typedef UINT8 BOOLEAN;
typedef UINT16 PORT_ADDR;
typedef UINT64 NAL_PHYSICAL_ADDRESS;
typedef char CHAR;
typedef UINT16 WCHAR;
typedef UINT32 NAL_STATUS;

#define INLINE static inline

#ifndef NAL_BIG_ENDIAN
#if defined(SPARC32)
#define NAL_BIG_ENDIAN 1
#endif
#if defined(SPARC64)
#define NAL_BIG_ENDIAN 1
#endif
#endif

#include <pthread.h>
typedef pthread_mutex_t NAL_SPIN_LOCK;

#if defined(NAL_DEBUG)
#ifndef ASSERT
#define ASSERT(X) 
#endif
#ifndef ASSERTEX
#define ASSERTEX(X,f,l) 
#endif
#else
#ifndef ASSERT
#define ASSERT(X) 
#endif
#ifndef ASSERTEX
#define ASSERTEX(X,f,l) 
#endif
#endif

#elif defined(NAL_WINNT_WDM) || defined(NAL_WINNT4)

#if defined(_WIN64)
    typedef __int64 INTN;
    typedef unsigned __int64 UINTN;
#else
    typedef long INTN;
    typedef unsigned long UINTN;
#endif

#if defined(NAL_DRIVER)
#include <ntddk.h>

#if defined(NAL_WINNT4)
    typedef unsigned char UINT8;
    typedef signed char INT8;
    typedef char CHAR;
    typedef signed short INT16;
    typedef unsigned short UINT16;
    typedef ULONG UINT32;
    typedef signed int INT32;
    typedef ULONGLONG UINT64;
    typedef LONGLONG INT64;
#endif
#else
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 
#endif

#include <windows.h>
#include <winioctl.h>
#endif

typedef signed char INT8;
typedef unsigned char UINT8;
typedef signed short INT16;
typedef unsigned short UINT16;

typedef void KVOID;
typedef UINTN PORT_ADDR;
typedef UINT64 NAL_PHYSICAL_ADDRESS;
typedef UINT32 NAL_STATUS;

typedef struct _NAL_SPIN_LOCK
{
    volatile UINT32 SpinLock;
    BOOLEAN Initialized;
    BOOLEAN Acquired;
} NAL_SPIN_LOCK;

#if defined(NAL_DEBUG)
#ifndef ASSERT
#define ASSERT(X) 
#endif
#ifndef ASSERTEX
#define ASSERTEX(X,f,l) 
#endif
#else
#ifndef ASSERT
#define ASSERT(X) 
#endif
#ifndef ASSERTEX
#define ASSERTEX(X,f,l) 
#endif
#endif

#else

#error "Undefined NAL Operating System in naltypes.h."
#endif

#ifndef IN
#define IN 
#endif

#ifndef OUT
#define OUT 
#endif

#ifndef NULL
#define NULL (VOID *)0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef OPTIONAL
#define OPTIONAL 
#endif

#ifndef INLINE
#define INLINE __forceinline
#endif

#define PHYSICAL_NULL (NAL_PHYSICAL_ADDRESS)0

typedef enum _NAL_DEBUG_PRINT_CAPABILITIES
{
    NAL_DEBUG_PRINT_SUPPORTED = 0x00000001,
    NAL_DEBUG_PRINT_ASCII = 0x00000002,
    NAL_DEBUG_PRINT_RESERVED = 0x00000004,
    NAL_DEBUG_PRINT_FILEIO = 0x00000008,
    NAL_DEBUG_PRINT_COUNT
} NAL_DEBUG_PRINT_CAPABILITIES;

#define NAL_SIZE_OF_8_BYTES 8

#define NAL_PIC1_FIRST_ACCESS_PORT 0x0020
#define NAL_PIC2_FIRST_ACCESS_PORT 0x00A0
#define NAL_PIC1_SECOND_ACCESS_PORT 0x0021
#define NAL_PIC2_SECOND_ACCESS_PORT 0x00A1
#define NAL_CLEAR_PIC_COMMAND 0x0020

#define NAL_TIMER_INTERVAL_LENGTH 100
#define NAL_MAX_TIMER_CALLBACKS 1

typedef VOID (*NAL_TIMER_CALLBACK) (VOID*);
typedef VOID *(*NAL_THREAD_FUNC) (VOID*);

#ifndef NAL_DRIVER

typedef struct _NAL_TIMER_CALLBACK_ENTRY
{
    struct _NAL_TIMER_CALLBACK_ENTRY* Next;
    struct _NAL_TIMER_CALLBACK_ENTRY* Prev;

    volatile UINT64 NextExecution;

    NAL_TIMER_CALLBACK TimerCallback;
    VOID* Context;

    UINT32 CallbackId;

    UINT32 TimerInterval;

    UINT32 Status;

} NAL_TIMER_CALLBACK_ENTRY;

#define NAL_TIMER_CALLBACK_ID_INVALID 0
#define NAL_TIMER_CALLBACK_ID_NEW_ENTRY -1

#define NAL_TIMER_CALLBACK_STATUS_NONE 0
#define NAL_TIMER_CALLBACK_STATUS_WAITING 1
#define NAL_TIMER_CALLBACK_STATUS_RESCHEDULE 2
#define NAL_TIMER_CALLBACK_STATUS_EXECUTING 3
#define NAL_TIMER_CALLBACK_STATUS_REMOVE 4

#endif

typedef enum _NAL_ASF_SUPPORT
{
    NAL_ASF_NOT_SUPPORTED = 0,
    NAL_ASF1_SUPPORTED,
    NAL_ASF2_SUPPORTED,
    NAL_ASF1_ASF2_SUPPORTED
} NAL_ASF_SUPPORT;

typedef enum _NAL_OS_TYPE
{
    NAL_OS_UNKNOWN = 0,
    NAL_OS_DOS,
    NAL_OS_EFI32,
    NAL_OS_EFI64,
    NAL_OS_LINUX32,
    NAL_OS_WIN3XX,
    NAL_OS_WIN9X,
    NAL_OS_OS2,
    NAL_OS_WINNT4,
    NAL_OS_WIN2K,
    NAL_OS_WINXP32,
    NAL_OS_WINXP64,
    NAL_OS_WINXP64E,
    NAL_OS_LINUX64,
    NAL_OS_FREEBSD32,
    NAL_OS_FREEBSD64,
    NAL_OS_LINUX64E,
    NAL_OS_NWS,
    NAL_OS_EFI64E,
    NAL_OS_LINUXPPC,
    NAL_OS_LINUXPPC64,
    NAL_OS_COUNT,
    NAL_OS_SOLARIS_X86,
    NAL_OS_SOLARIS_64E,
    NAL_OS_SOLARIS_SPARC32,
    NAL_OS_SOLARIS_SPARC64
} NAL_OS_TYPE;

typedef enum _NAL_OS_RUN_DOMAIN
{
    NAL_OS_DOMAIN_BAREMETAL = 0,
    NAL_OS_DOMAIN_0,
    NAL_OS_DOMAIN_U
} NAL_OS_RUN_DOMAIN;

#define NAL_OS_LINUX NAL_OS_LINUX32

#if !defined(NAL_DRIVER)
#define boolean_t BOOLEAN
#define uint8_t UINT8
#define u8 UINT8
#define int8_t INT8
#define s8 INT8
#define uint16_t UINT16
#define u16 UINT16
#define int16_t INT16
#define s16 INT16
#define uint32_t UINT32
#define u32 UINT32
#define int32_t INT32
#define s32 INT32
#define uint64_t UINT64
#define u64 UINT64
#define int64_t INT64
#define s64 INT64
#endif

typedef UINT32 NAL_REGISTER;
typedef UINTN NAL_MAC_TYPE;

#define MAKE_BOOLEAN(x) (!!(x))

typedef enum _NAL_QUEUE_TYPE
{
    NAL_RX_QUEUE = 0,
    NAL_TX_QUEUE
} NAL_QUEUE_TYPE;

#endif
