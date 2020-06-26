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
 * Module Name:
 *   linuxnaldriver.h
 *
 * Abstract:
 *   This is the main header file for the memspi Linux driver modules.
 *
 */


#ifndef __LINUXNALDRIVER_H__
#define __LINUXNALDRIVER_H__

#ifdef NAL_LINUX_ANDROID
#define DRIVER_NAME "SPI Device Memmap Linux Driver"
#else
#define DRIVER_NAME "Nal Linux Driver"
#endif

#include <naltypes.h>
#include <nalcodes.h>
#include <hwbus_t.h>
#include <linux/fs.h>
#include <osdevice_i.h>
#include <os_i.h>
#include <linuxnalioctl.h>

#define NAL_DRIVER_MAX_ADAPTERS 256
#ifdef NAL_LINUX_ANDROID
#define NAL_LINUX_DRIVER_NAME "memspi"
#else
#define NAL_LINUX_DRIVER_NAME "nal"
#endif

#ifdef NAL_LINUX_ANDROID
#define DRIVER_MAJOR_VERSION 1
#define DRIVER_MINOR_VERSION 1
#define DRIVER_BUILD_NUMBER 0
#define DRIVER_FIX_NUMBER 1
#else
#define DRIVER_MAJOR_VERSION 1
#define DRIVER_MINOR_VERSION 1
#define DRIVER_BUILD_NUMBER 4
#define DRIVER_FIX_NUMBER 5
#endif

#ifndef MINOR_VERSION
#define MINOR_VERSION DRIVER_MINOR_VERSION
#endif

#if MINOR_VERSION < 10
#define _MAKE_VER_STRING(maj,min,build,fix) #maj ".0" #min "." #build "." #fix
#else
#define _MAKE_VER_STRING(maj,min,build,fix) #maj "." #min "." #build "." #fix
#endif
#define MAKE_VER_STRING(maj,min,submin,bld) _MAKE_VER_STRING(maj, min, submin, bld)

#define DRIVER_FILEVERSION DRIVER_MAJOR_VERSION,DRIVER_MINOR_VERSION,DRIVER_BUILD_NUMBER,DRIVER_FIX_NUMBER

#define DRIVER_FILEVERSION_STR LINUX_DRIVER_VERSION

#ifdef NAL_LINUX_ANDROID
#define DRIVER_FILEDESCRIPTION "Intel(R) SPI Device Memmap Linux Driver "
#else
#define DRIVER_FILEDESCRIPTION "Intel(R) Network Adapter Diagnostic Driver "
#endif
#define DRIVER_COMPANYNAME "Intel Corporation "
#define DRIVER_COPYRIGHT_YEARS "2002-2013 "
#define DRIVER_LEGALCOPYRIGHT "Copyright (C) " DRIVER_COPYRIGHT_YEARS DRIVER_COMPANYNAME "All Rights Reserved."

#define DRIVER_DESCRIPTION DRIVER_FILEDESCRIPTION DRIVER_FILEVERSION_STR

typedef struct _NAL_ADAPTER_IN_USE_TABLE
{
    NAL_DEVICE_LOCATION DeviceLocation;
    BOOLEAN InUse;
} NAL_ADAPTER_IN_USE_TABLE;

#define NAL_LINUX_MEMORY_ROUNDUP(i,size) ((i) = (((i) + (size) - 1) & ~((size) - 1)))

int
NalDeviceControl(
    struct inode* Inode,
    struct file* File,
    unsigned int Cmd,
    unsigned long Arg
    );

long
NalDeviceControlUnlockedIoctl(
    struct file* File,
    unsigned int Cmd,
    unsigned long Arg
    );

int
NalOpen(
    struct inode* Inode,
    struct file* File
    );

int
NalRelease(
    struct inode* Inode,
    struct file* File
    );

NAL_STATUS
_NalInitializeInterrupts(
    IN NAL_LINUX_ISR_DEVICE* NalIsrDevice
    );

NAL_STATUS
_NalUninitializeInterrupts(
    IN NAL_LINUX_ISR_DEVICE* NalIsrDevice
    );

BOOLEAN
_NalHasInterruptOccurred(
    IN NAL_LINUX_ISR_DEVICE* NalIsrDevice
    );

VOID
_NalDriverDecrementReferenceCount(
    VOID
    );

VOID
_NalDriverIncrementReferenceCount(
    VOID
    );

UINT32
_NalDriverGetReferenceCount(
    VOID
    );

VOID
_NalDriverGetVersion(
    OUT CHAR* Version
    );

#endif
