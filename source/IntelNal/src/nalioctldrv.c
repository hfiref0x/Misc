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
 *   nalioctldrv.c
 *
 * Abstract:
 *   This contains driver (ring 0) functions that are shared between
 *   protected mode operating systems.
 *
 */



#include <os_i.h>
#include <pci_i.h>
#include <nalioctl.h>

#if defined(NAL_WINNT_WDM) || defined(NAL_WINNT4)
#include <windriverdevice_i.h>
#endif

#if defined(NAL_LINUX)
#include <linuxnaldriver.h>
#endif

#if defined(NAL_SOLARIS)
#include <osdevice_i.h>
#include <solarisnaldriver.h>
#endif

NAL_STATUS
NalResolveNdiIoctl(
    IN NAL_IOCTL_INPUT_DATA* NalIoctl
    )
{
    NAL_STATUS NalStatus = NAL_INVALID_PARAMETER;

    if(NalIoctl != NULL)
    {
        switch(NalIoctl->FunctionId)
        {
            case NAL_INITIALIZEINTERRUPTS_FUNCID:
                {
                    NAL_INTERRUPT_FUNCS* FunctionData =
                        (NAL_INTERRUPT_FUNCS*)(&(NalIoctl->InputBuffer));
                    if(FunctionData != NULL)
                    {
                        FunctionData->ReturnValue =
                            _NalInitializeInterrupts(FunctionData->NalOsDevice);
                    }
                    NalStatus = NAL_SUCCESS;
                }
                break;

            case NAL_UNINITIALIZEINTERRUPTS_FUNCID:
                {
                    NAL_INTERRUPT_FUNCS* FunctionData =
                        (NAL_INTERRUPT_FUNCS*)(&(NalIoctl->InputBuffer));
                    if(FunctionData != NULL)
                    {
                        FunctionData->ReturnValue =
                            _NalUninitializeInterrupts(FunctionData->NalOsDevice);
                    }
                    NalStatus = NAL_SUCCESS;
                }
                break;

            case NAL_HASINTERRUPTOCCURRED_FUNCID:
                {
                    NAL_INTERRUPT_FUNCS* FunctionData =
                        (NAL_INTERRUPT_FUNCS*)(&(NalIoctl->InputBuffer));
                    if(FunctionData != NULL)
                    {
                        FunctionData->Triggered =
                            _NalHasInterruptOccurred(FunctionData->NalOsDevice);
                    }
                    NalStatus = NAL_SUCCESS;
                }
                break;

           default:

                NalStatus = NAL_IOCTL_INVALID_FUNCTION_ID;
                break;
        }
    }
    return NalStatus;
}

NAL_STATUS
NalResolveOsiIoctl(
    IN NAL_IOCTL_INPUT_DATA* NalIoctl
    )
{
    NAL_STATUS NalStatus = NAL_INVALID_PARAMETER;

    if(NalIoctl != NULL)
    {

        switch(NalIoctl->FunctionId)
        {
        case NAL_READPORT8_FUNCID:
            {
                NAL_READPORT_FUNCS* FunctionData =
                    (NAL_READPORT_FUNCS*)(&(NalIoctl->InputBuffer));
                FunctionData->ReturnValue.Uint8 =
                    NalReadPort8(FunctionData->Port);

                NalStatus = NAL_SUCCESS;
            }
            break;

        case NAL_READPORT16_FUNCID:
            {
                NAL_READPORT_FUNCS* FunctionData =
                    (NAL_READPORT_FUNCS*)(&(NalIoctl->InputBuffer));
                FunctionData->ReturnValue.Uint16 =
                    NalReadPort16(FunctionData->Port);

                NalStatus = NAL_SUCCESS;
            }
            break;

        case NAL_READPORT32_FUNCID:
            {
                NAL_READPORT_FUNCS* FunctionData =
                    (NAL_READPORT_FUNCS*)(&(NalIoctl->InputBuffer));
                FunctionData->ReturnValue.Uint32 =
                    NalReadPort32(FunctionData->Port);

                NalStatus = NAL_SUCCESS;
            }
            break;

        case NAL_WRITEPORT8_FUNCID:
            {
                NAL_WRITEPORT_FUNCS* FunctionData =
                    (NAL_WRITEPORT_FUNCS*)(&(NalIoctl->InputBuffer));
                FunctionData->ReturnValue =
                    NalWritePort8(FunctionData->Port,
                                  FunctionData->Value.Uint8);

                NalStatus = NAL_SUCCESS;
            }
            break;

        case NAL_WRITEPORT16_FUNCID:
            {
                NAL_WRITEPORT_FUNCS* FunctionData =
                    (NAL_WRITEPORT_FUNCS*)(&(NalIoctl->InputBuffer));
                FunctionData->ReturnValue =
                    NalWritePort16(FunctionData->Port,
                                   FunctionData->Value.Uint16);

                NalStatus = NAL_SUCCESS;
            }
            break;

        case NAL_WRITEPORT32_FUNCID:
            {
                NAL_WRITEPORT_FUNCS* FunctionData =
                    (NAL_WRITEPORT_FUNCS*)(&(NalIoctl->InputBuffer));
                FunctionData->ReturnValue =
                    NalWritePort32(FunctionData->Port,
                                   FunctionData->Value.Uint32);

                NalStatus = NAL_SUCCESS;
            }
            break;

       case NAL_READREGISTER8_FUNCID:
            {
                NAL_READREGISTER_FUNCS* FunctionData =
                    (NAL_READREGISTER_FUNCS*)(&(NalIoctl->InputBuffer));
                FunctionData->ReturnValue.Uint8 =
                    NalReadRegister8(FunctionData->Address);

                NalStatus = NAL_SUCCESS;
            }
            break;

        case NAL_READREGISTER16_FUNCID:
            {
                NAL_READREGISTER_FUNCS* FunctionData =
                    (NAL_READREGISTER_FUNCS*)(&(NalIoctl->InputBuffer));
                FunctionData->ReturnValue.Uint16 =
                    NalReadRegister16(FunctionData->Address);

                NalStatus = NAL_SUCCESS;
            }
            break;

        case NAL_READREGISTER32_FUNCID:
            {
                NAL_READREGISTER_FUNCS* FunctionData =
                    (NAL_READREGISTER_FUNCS*)(&(NalIoctl->InputBuffer));
                FunctionData->ReturnValue.Uint32 =
                    NalReadRegister32(FunctionData->Address);
                NalStatus = NAL_SUCCESS;
            }
            break;

        case NAL_WRITEREGISTER8_FUNCID:
            {
                NAL_WRITEREGISTER_FUNCS* FunctionData =
                    (NAL_WRITEREGISTER_FUNCS*)(&(NalIoctl->InputBuffer));
                FunctionData->ReturnValue =
                    NalWriteRegister8(FunctionData->Address,
                                      FunctionData->Value.Uint8);

                NalStatus = NAL_SUCCESS;
            }
            break;

        case NAL_WRITEREGISTER16_FUNCID:
            {
                NAL_WRITEREGISTER_FUNCS* FunctionData =
                    (NAL_WRITEREGISTER_FUNCS*)(&(NalIoctl->InputBuffer));
                FunctionData->ReturnValue =
                    NalWriteRegister16(FunctionData->Address,
                                       FunctionData->Value.Uint16);

                NalStatus = NAL_SUCCESS;
            }
            break;

        case NAL_WRITEREGISTER32_FUNCID:
            {
                NAL_WRITEREGISTER_FUNCS* FunctionData =
                    (NAL_WRITEREGISTER_FUNCS*)(&(NalIoctl->InputBuffer));
                FunctionData->ReturnValue =
                    NalWriteRegister32(FunctionData->Address,
                                       FunctionData->Value.Uint32);

                NalStatus = NAL_SUCCESS;
            }
            break;

        case NAL_MMAPADDRESS_FUNCID:
            {
                NAL_MEMMAP_FUNCS* FunctionData =
                    (NAL_MEMMAP_FUNCS*)(&(NalIoctl->InputBuffer));
                FunctionData->ReturnValue =
                    NalMmapAddress((KVOID**)&FunctionData->VirtualAddress,
                                   FunctionData->PhysicalAddress,
                                   &FunctionData->Length);

                NalStatus = NAL_SUCCESS;
            }
            break;

        case NAL_UNMAPADDRESS_FUNCID:
            {
                NAL_MEMMAP_FUNCS* FunctionData =
                    (NAL_MEMMAP_FUNCS*)(&(NalIoctl->InputBuffer));
                FunctionData->ReturnValue =
                    NalUnmapAddress(FunctionData->VirtualAddress,
                                    FunctionData->PhysicalAddress,
                                    FunctionData->Length);

                NalStatus = NAL_SUCCESS;
            }
            break;

        case NAL_GETTIMESTAMP_FUNCID:
            {
                NAL_TIMESTAMP_FUNCS* FunctionData =
                    (NAL_TIMESTAMP_FUNCS*)(&(NalIoctl->InputBuffer));
                FunctionData->ReturnValue =
                    NalGetTimeStamp();

                NalStatus = NAL_SUCCESS;
            }
            break;

        case NAL_GETTIMESTAMPSPERMICROSECOND_FUNCID:
            {
                NAL_TIMESTAMP_FUNCS* FunctionData =
                    (NAL_TIMESTAMP_FUNCS*)(&(NalIoctl->InputBuffer));
                FunctionData->ReturnValue =
                    NalGetTimeStampsPerMicrosecond();

                NalStatus = NAL_SUCCESS;
            }
            break;

        case NAL_DELAYMICROSECONDS_FUNCID:
            {
                NAL_DELAY_FUNCS* FunctionData =
                    (NAL_DELAY_FUNCS*)(&(NalIoctl->InputBuffer));

                    NalDelayMicroseconds(FunctionData->Delay);

                NalStatus = NAL_SUCCESS;
            }
            break;

        case NAL_DELAYMILLISECONDS_FUNCID:
            {
                NAL_DELAY_FUNCS* FunctionData =
                    (NAL_DELAY_FUNCS*)(&(NalIoctl->InputBuffer));

                    NalDelayMilliseconds(FunctionData->Delay);

                NalStatus = NAL_SUCCESS;
            }
            break;

        case NAL_GETPHYSICALMEMORYADDRESS_FUNCID:
            {
                NAL_GETPHYSICALMEMORYADDRESS_FUNC* FunctionData =
                    (NAL_GETPHYSICALMEMORYADDRESS_FUNC*)(&(NalIoctl->InputBuffer));

                    FunctionData->ReturnValue =
                        NalGetPhysicalMemoryAddress(FunctionData->VirtualAddress);

                NalStatus = NAL_SUCCESS;
            }
            break;

         case NAL_ALLOCATEMEMORYNONPAGED_FUNCID:
            {
                NAL_ALLOCATEMEMORYNONPAGED_FUNC* FunctionData =
                    (NAL_ALLOCATEMEMORYNONPAGED_FUNC*)(&(NalIoctl->InputBuffer));

                    FunctionData->ReturnValue =
                        _NalAllocateMemoryNonPaged(FunctionData->ByteCount,
                                                   FunctionData->Alignment,
                                                   &FunctionData->PhysicalAddress,
                                                   NULL,
                                                   0);

                NalStatus = NAL_SUCCESS;
            }
            break;

         case NAL_FREEMEMORYNONPAGED_FUNCID:
            {
                NAL_FREEMEMORYNONPAGED_FUNC* FunctionData =
                    (NAL_FREEMEMORYNONPAGED_FUNC*)(&(NalIoctl->InputBuffer));

                    _NalFreeMemoryNonPaged(FunctionData->Address,
                                           NULL,
                                           0);

                NalStatus = NAL_SUCCESS;
            }
            break;

         case NAL_KMEMSET_FUNCID:
            {
                NAL_KMEMSET_FUNC* FunctionData =
                    (NAL_KMEMSET_FUNC*)(&(NalIoctl->InputBuffer));

                if(FunctionData->Destination != NULL)
                {
                    NalKMemset(FunctionData->Destination,
                               FunctionData->Source,
                               FunctionData->Size);
                    NalStatus = NAL_SUCCESS;
                }
                else
                {
                    NalDebugPrint("NAL_KMEMSET_FUNCID: One of the buffers was NULL\n");
                    NalStatus = NAL_INVALID_PARAMETER;
                }
            }
            break;

         case NAL_KUMEMCPY_FUNCID:
            {
                NAL_KMEM_FUNCS* FunctionData =
                    (NAL_KMEM_FUNCS*)(&(NalIoctl->InputBuffer));

                if(FunctionData->Destination != NULL &&
                   FunctionData->Source != NULL)
                {
                    NalKtoUMemcpy(FunctionData->Destination,
                                  FunctionData->Source,
                                  FunctionData->Size);
                    NalStatus = NAL_SUCCESS;
                }
                else
                {
                    NalDebugPrint("NAL_KUMEMCPY_FUNCID: One of the buffers was NULL\n");
                    NalStatus = NAL_INVALID_PARAMETER;
                }
            }
            break;

         case NAL_KKMEMCPY_FUNCID:
            {
                NAL_KMEM_FUNCS* FunctionData =
                    (NAL_KMEM_FUNCS*)(&(NalIoctl->InputBuffer));

                if(FunctionData->Destination != NULL &&
                   FunctionData->Source != NULL)
                {
                    NalKtoKMemcpy(FunctionData->Destination,
                                  FunctionData->Source,
                                  FunctionData->Size);
                    NalStatus = NAL_SUCCESS;
                }
                else
                {
                    NalDebugPrint("NAL_KKMEMCPY_FUNCID: One of the buffers was NULL\n");
                    NalStatus = NAL_INVALID_PARAMETER;
                }
            }
            break;

         case NAL_UKMEMCPY_FUNCID:
            {
                NAL_KMEM_FUNCS* FunctionData =
                    (NAL_KMEM_FUNCS*)(&(NalIoctl->InputBuffer));

                NalUtoKMemcpy(FunctionData->Destination,
                              FunctionData->Source,
                              FunctionData->Size);

                NalStatus = NAL_SUCCESS;
            }
            break;

         case NAL_ATOMICINCREMENT32_FUNCID:
            {
                NAL_ATOMIC_FUNCS* FunctionData =
                    (NAL_ATOMIC_FUNCS*)(&(NalIoctl->InputBuffer));

                FunctionData->ReturnValue =
                    NalAtomicIncrement32(FunctionData->Address);
                NalStatus = NAL_SUCCESS;
            }
            break;

         case NAL_ATOMICDECREMENT32_FUNCID:
            {
                NAL_ATOMIC_FUNCS* FunctionData =
                    (NAL_ATOMIC_FUNCS*)(&(NalIoctl->InputBuffer));

                FunctionData->ReturnValue =
                    NalAtomicDecrement32(FunctionData->Address);
                NalStatus = NAL_SUCCESS;
            }
            break;

         case NAL_ATOMICTESTSET32_FUNCID:
            {
                NAL_ATOMICTESTSET32_FUNC* FunctionData =
                    (NAL_ATOMICTESTSET32_FUNC*)(&(NalIoctl->InputBuffer));

                FunctionData->ReturnValue =
                    NalAtomicTestSet32(FunctionData->Address,
                                       FunctionData->Test,
                                       FunctionData->Set);
                NalStatus = NAL_SUCCESS;
            }
            break;

        case NAL_ENABLE_DEBUG_PRINT_FUNCID:
            {
                NAL_ENABLE_DEBUG_PRINT_FUNC* FunctionData =
                    (NAL_ENABLE_DEBUG_PRINT_FUNC*)(&(NalIoctl->InputBuffer));

                if(FunctionData != NULL)
                {
                    NalEnableDebugPrint(FunctionData->Enable);
                    NalStatus = NAL_SUCCESS;
                }
                else
                {
                    NalDebugPrint("NAL_ENABLE_DEBUG_PRINT_FUNCID: FunctionData is NULL\n");
                    NalStatus = NAL_INVALID_PARAMETER;
                }
            }
            break;

        case NAL_DEBUGPRINT_FUNCID:
            {
                NAL_DEBUGPRINT_FUNC* FunctionData =
                    (NAL_DEBUGPRINT_FUNC*)(&(NalIoctl->InputBuffer));

                if(FunctionData != NULL)
                {
                    FunctionData->ReturnValue = NalDebugPrint(FunctionData->Message);
                    NalStatus = NAL_SUCCESS;
                }
                else
                {
                    NalDebugPrint("NAL_ENABLE_DEBUG_PRINT_FUNCID: FunctionData is NULL\n");
                    NalStatus = NAL_INVALID_PARAMETER;
                }
            }
            break;

         case NAL_ALLOCATEMEMORYNONPAGEDEX_FUNCID:
            {
                NAL_ALLOCATEMEMORYNONPAGED_FUNC* FunctionData =
                    (NAL_ALLOCATEMEMORYNONPAGED_FUNC*)(&(NalIoctl->InputBuffer));

                    FunctionData->ReturnValue =
                        _NalAllocateMemoryNonPagedEx(FunctionData->ByteCount,
                                                     FunctionData->Alignment,
                                                     FunctionData->ProcessId,
                                                     &FunctionData->PhysicalAddress,
                                                     NULL,
                                                     0);

                NalStatus = NAL_SUCCESS;
            }
            break;

         case NAL_FREEMEMORYNONPAGEDEX_FUNCID:
            {
                NAL_FREEMEMORYNONPAGED_FUNC* FunctionData =
                    (NAL_FREEMEMORYNONPAGED_FUNC*)(&(NalIoctl->InputBuffer));

                    _NalFreeMemoryNonPagedEx(FunctionData->Address,
                                             FunctionData->ProcessId,
                                             NULL,
                                             0);

                NalStatus = NAL_SUCCESS;
            }
            break;

        case NAL_MMAPADDRESSEX_FUNCID:
            {
                NAL_MEMMAP_FUNCS* FunctionData =
                    (NAL_MEMMAP_FUNCS*)(&(NalIoctl->InputBuffer));
                FunctionData->ReturnValue =
                    NalMmapAddressEx((KVOID**)&FunctionData->VirtualAddress,
                                     FunctionData->PhysicalAddress,
                                     &FunctionData->Length,
                                     FunctionData->ProcessId);

                NalStatus = NAL_SUCCESS;
            }
            break;

        case NAL_UNMAPADDRESSEX_FUNCID:
            {
                NAL_MEMMAP_FUNCS* FunctionData =
                    (NAL_MEMMAP_FUNCS*)(&(NalIoctl->InputBuffer));
                FunctionData->ReturnValue =
                    NalUnmapAddressEx(FunctionData->VirtualAddress,
                                      FunctionData->PhysicalAddress,
                                      FunctionData->Length,
                                      FunctionData->ProcessId);

                NalStatus = NAL_SUCCESS;
            }
            break;

        case NAL_GETPHYSICALMEMORYADDRESSEX_FUNCID:
            {
                NAL_GETPHYSICALMEMORYADDRESS_FUNC* FunctionData =
                    (NAL_GETPHYSICALMEMORYADDRESS_FUNC*)(&(NalIoctl->InputBuffer));

                    FunctionData->ReturnValue =
                        NalGetPhysicalMemoryAddressEx(FunctionData->VirtualAddress,
                                                      FunctionData->ProcessId);

                NalStatus = NAL_SUCCESS;
            }
            break;

        default:

            NalStatus = NAL_IOCTL_INVALID_FUNCTION_ID;
            break;
        }
    }
    return NalStatus;
}

NAL_STATUS
NalResolveHwBusIoctl(
    IN NAL_IOCTL_INPUT_DATA* NalIoctl
    )
{
    NAL_STATUS NalStatus = NAL_INVALID_PARAMETER;

    if(NalIoctl != NULL)
    {

        switch(NalIoctl->FunctionId)
        {
            case NAL_READPCIDEVICECOUNT_FUNCID:
                {
                    NAL_READPCIDEVICECOUNT_FUNC* FunctionData =
                        (NAL_READPCIDEVICECOUNT_FUNC*)(&(NalIoctl->InputBuffer));
                    FunctionData->ReturnValue =
                        _NalReadPciDeviceCount();

                    NalStatus = NAL_SUCCESS;
                }
                break;

            case NAL_READPCIDEVICE_FUNCID:
                {
                    NAL_READPCIDEVICE_FUNC* FunctionData =
                        (NAL_READPCIDEVICE_FUNC*)(&(NalIoctl->InputBuffer));
                    FunctionData->ReturnValue =
                        _NalReadPciDevice(FunctionData->PciLocations,
                                          &FunctionData->Count);

                    NalStatus = NAL_SUCCESS;
                }
                break;

            case NAL_FILLPCICONFIGSPEC_FUNCID:
                {
                    NAL_FILLPCICONFIGSPEC_FUNC* FunctionData =
                        (NAL_FILLPCICONFIGSPEC_FUNC*)(&(NalIoctl->InputBuffer));
                    FunctionData->ReturnValue =
                        _NalFillPciConfigSpec(FunctionData->PciLocation,
                                              &FunctionData->PciDevice,
                                              FunctionData->DwordCount);

                    NalStatus = NAL_SUCCESS;
                }
                break;

            case NAL_OSREADPCICONFIG32_FUNCID:
                {
                    NAL_OSREADPCICONFIG32_FUNC* FunctionData =
                        (NAL_OSREADPCICONFIG32_FUNC*)(&(NalIoctl->InputBuffer));
                    FunctionData->ReturnValue =
                        _NalOSReadPciConfig32(FunctionData->PciLocation,
                                              FunctionData->DwordNumber,
                                              &FunctionData->Value);

                    NalStatus = NAL_SUCCESS;
                }
                break;

            case NAL_OSWRITEPCICONFIG32_FUNCID:
                {
                    NAL_OSWRITEPCICONFIG32_FUNC* FunctionData =
                        (NAL_OSWRITEPCICONFIG32_FUNC*)(&(NalIoctl->InputBuffer));
                    FunctionData->ReturnValue =
                        _NalOSWritePciConfig32(FunctionData->PciLocation,
                                               FunctionData->DwordNumber,
                                               FunctionData->Data);

                    NalStatus = NAL_SUCCESS;
                }
                break;

            case NAL_OSWRITEPCICONFIGVARIABLE_FUNCID:
                {
                    NAL_OSWRITEPCICONFIGVARIABLE_FUNC* FunctionData =
                        (NAL_OSWRITEPCICONFIGVARIABLE_FUNC*)(&(NalIoctl->InputBuffer));
                    FunctionData->ReturnValue =
                        _NalOSWritePciConfigVariable(FunctionData->PciLocation,
                                                     FunctionData->DwordNumber,
                                                     FunctionData->ByteMask,
                                                     FunctionData->Data);

                    NalStatus = NAL_SUCCESS;
                }
                break;

            case NAL_ENABLEPCIDEVICE_FUNCID:
                {
                    NAL_ENABLEPCIDEVICE_FUNC* FunctionData =
                        (NAL_ENABLEPCIDEVICE_FUNC*)(&(NalIoctl->InputBuffer));
                    FunctionData->ReturnValue =
                        _NalEnablePciDevice(FunctionData->DeviceLocation);
                    NalStatus = NAL_SUCCESS;
                }
                break;

           default:

                NalStatus = NAL_IOCTL_INVALID_FUNCTION_ID;
                break;
        }
    }
    return NalStatus;
}
