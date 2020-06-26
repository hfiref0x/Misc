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
 *   nalcodes.h
 *
 * Abstract:
 *   This file contains the status codes.
 *
 */


#ifndef _NALCODES_H_
#define _NALCODES_H_

#include <naltypes.h>

#define NAL_CODE_SUCCESS 0x0
#define NAL_CODE_INFORMATIONAL 0x1
#define NAL_CODE_WARNING 0x2
#define NAL_CODE_ERROR 0x3

#define OEM_NONE 0x00
#define OEM_INTEL 0x86

#define CODE_GENERAL 0x0
#define CODE_NAL 0xA

#define MAKE_STATUS_CODE(type,custom,status) \
    ((UINT32)(((UINT32)(type)<<30) | \
    ((UINT32)(OEM_INTEL)<<20) | \
    ((UINT32)(custom)<<16) | \
    ((UINT32)(status))))

#ifdef NAL_DRIVER
#define NalMakeCode(_Type,_Library,_Number,_Description) MAKE_STATUS_CODE(_Type, _Library, _Number)
#else

typedef UINT32 NAL_LINK_MODE;

#define NAL_MAX_CODES 1000

typedef struct _NAL_CODE_STRUCT
{
    BOOLEAN InUse;
    UINT32 Status;
    CHAR* Description;
} NAL_CODE_STRUCT;

extern NAL_CODE_STRUCT Global_CodeStruct[NAL_MAX_CODES];

NAL_STATUS
NalMakeCode(
    IN UINT32 Type,
    IN UINT32 Library,
    IN UINT32 Number,
    IN CHAR* Description
    );

CHAR*
NalGetStatusCodeDescription(
    IN NAL_STATUS Status
    );

#endif

#define NAL_SUCCESS 0
#define NAL_INVALID_PARAMETER 1
#define NAL_NOT_ENOUGH_SPACE NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x0002, "Not enough space")
#define NAL_NOT_IMPLEMENTED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x0003, "Not Implemented")
#define NAL_TIMEOUT_ERROR NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x0004, "Timeout Error")
#define NAL_NOT_ENABLED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x0005, "Feature not enabled in HW")
#define NAL_CONFIGURATION_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x0006, "Configuration failed")
#define NAL_AQ_COMMAND_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x0007, "Admin Queue command failed")
#define NAL_AQ_COMMAND_TIMEOUT NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x0008, "Admin Queue command timeout")

#define NAL_INITIALIZATION_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x8001, "Initialization Failed")
#define NAL_IO_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x8002, "IO Failure")
#define NAL_MMAP_ADDRESS_IN_USE NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x8003, "Memory Map Address In Use")
#define NAL_MMAP_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x8004, "Memory Mapping Failed")
#define NAL_MMAP_ADDRESS_NOT_MAPPED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x8005, "Memory Map Address Not Mapped")
#define NAL_INVALID_VECTOR NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x8006, "Invalid IRQ Vector")
#define NAL_VECTOR_INITIALIZATION_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x8007, "IRQ Vector Init Failed")
#define NAL_SPINLOCK_FAILURE NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x8008, "Spinlock Failure")
#define NAL_SECURITY_ACCESS_DENIED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x8009, "Access Denied")
#define NAL_DEBUGPRINT_NO_SUPPORT NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x800A, "No Debug Print Support")
#define NAL_DEBUGPRINT_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x800B, "Debug Print Failed")
#define NAL_TIMER_CALLBACK_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x800C, "Timer Callback Failed")
#define NAL_MEMORY_BAR_INVALID NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x800E, "No PCI memory resources assigned by BIOS or OS!")
#define NAL_INCORRECT_OS NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x800F, "Incorrect OS")
#define NAL_NO_DEBUG_STACK_SPACE NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x8010, "Debug Stack Space Is Full")
#define NAL_THREAD_CREATE_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x8011, "Failed to Create Thread")
#define NAL_INITIALIZATION_BASE_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x8012, "Initialization Failed. Please unload device driver")
#define NAL_INITIALIZATION_DLM_BASE_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x8013, "Initialization in DLM Failed. Not capable device driver")

#define NAL_PCISCANBUS_NOT_ENOUGH_SPACE NAL_NOT_ENOUGH_SPACE
#define NAL_INVALID_PCI_SLOT_ID NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x4002, "Invalid PCI Slot")
#define NAL_PCICONFIG_NOT_AVAILABLE NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x4003, "PCI Config is not available")
#define NAL_NOT_A_VALID_SLOT NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x4006, "Not a valid PCI slot")
#define NAL_NOT_A_VALID_BUS NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x4007, "Invalid bus")
#define NAL_PCI_CAPABILITY_NOT_FOUND NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x4008, "PCI Capability not found")
#define NAL_IO_CALL_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x4009, "IO Driver Call failed")
#define NAL_DMA_NOT_SUPPORTED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x4010, "No usable DMA configuration")
#define NAL_PCI_D3_STATE NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x4011, "PCI Device in D3 state")

#define NAL_INVALID_ADAPTER_HANDLE NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2001, "Adapter handle is invalid")
#define NAL_ADAPTER_INITIALIZATION_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2002, "Adapter initialization failed")
#define NAL_ADAPTER_START_REQUIRED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2003, "Adapter start required for this operation")
#define NAL_ADAPTER_STOP_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2004, "Adapter stop failed")
#define NAL_ADAPTER_RESET_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2005, "Adapter reset failed")
#define NAL_INVALID_MAC_REGISTER NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2006, "Invalid MAC register")
#define NAL_INVALID_PHY_REGISTER NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2007, "Invalid PHY register")
#define NAL_NO_LINK NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2008, "Adapter has no link")
#define NAL_EEPROM_DOES_NOT_EXIST NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2009, "Adapter has no EEPROM")
#define NAL_EEPROM_BAD_INDEX NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x200A, "EEPROM index is bad or out of range")
#define NAL_EEPROM_BAD_IMAGE NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x200B, "EEPROM image is bad")
#define NAL_EEPROM_WRITE_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x200C, "EEPROM write failure")
#define NAL_FLASH_DOES_NOT_EXIST NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x200D, "Flash does not exist")
#define NAL_FLASH_ID_UNKNOWN NalMakeCode(NAL_CODE_SUCCESS, CODE_NAL, 0x200E,"Flash ID is unknown")
#define NAL_FLASH_BAD_INDEX NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x200F, "Flash index is bad or our of range")
#define NAL_FLASH_BAD_IMAGE NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2010, "Flash image is bad")
#define NAL_FLASH_WRITE_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2011, "Flash write failed")
#define NAL_FLASH_READ_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2011, "Flash read failed")
#define NAL_ADAPTER_HANDLE_IN_USE NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2012, "Adapter handle is in use")
#define NAL_RESOURCE_ALLOCATION_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2013, "Resource allocation failed")
#define NAL_RESOURCE_NOT_AVAILABLE NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2014, "Resource is unavailable")
#define NAL_CONNECTION_TO_DRIVER_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2015, "Connection to driver failed")
#define NAL_DRIVER_HANDLE_INVALID NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2016, "Invalid Driver Handle")
#define NAL_DRIVER_IOCTL_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2017, "IOCTL to driver failed")
#define NAL_IOCTL_INVALID_FUNCTION_ID NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2018, "IOCTL to invalid function ID")
#define NAL_HARDWARE_FAILURE NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2019, "Hardware Failure")
#define NAL_ADAPTER_IN_USE NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x201A, "Adapter is already in use")
#define NAL_EEPROM_SIZE_INCORRECT NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x201B, "EEPROM size is incorrect")
#define NAL_HOST_IF_COMMAND_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x201C, "Host interface command failure")
#define NAL_WRITE_EEPROM_SIZE_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x201D, "Writing of EEPROM size failed")
#define NAL_NO_MODULE_VALIDITY_SIGNATURE NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x201E, "Module does not contain validity signature")
#define NAL_WRONG_MODULE_FOR_DEVICE NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x201F, "This module does not support this device")
#define NAL_DEVICE_DRIVER_UNLOAD_REQUIRED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2020, "OS Device driver must be unloaded for this operation")
#define NAL_DEVICE_DRIVER_RELOAD_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2021, "The OS device driver could not be reloaded")
#define NAL_PACKET_SIZE_TOO_LARGE NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2022, "The packet size is too large for this adapter")
#define NAL_NO_RECEIVE_PENDING NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2023, "No receive is pending")
#define NAL_TRANSMIT_TIMEOUT NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2024, "Transmit packet timed out")
#define NAL_ERASE_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2025, "Flash could not be erased")
#define NAL_ADAPTER_DOES_NOT_SUPPORT NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2026, "The adapter does not support this feature")
#define NAL_HEAD_WRITEBACK_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2027, "Head Writeback failed")
#define NAL_ADAPTER_IN_USE_ISCSI NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2028, "Adapter is in use for iSCSI and cannot be initialized")
#define NAL_EEPROM_READ_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2029, "Failed to read EEPROM or EEPROM image.")
#define NAL_EEPROM_CALCULATION_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x202A, "Failed to calculate Manageability CRC/Checksum.")
#define NAL_EEPROM_ASF1_CRC_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x202B, "ASF1 CRC validation failed.")
#define NAL_EEPROM_ASF2_CSUM_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x202C, "ASF2 Checksum validation failed.")
#define NAL_EEPROM_ASF2_CRC_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x202D, "Failed to calculate Manageability CRC/Checksum.")
#define NAL_RESOURCE_LESS_THAN_REQUESTED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x202E, "Resource allocation succeeded but allocated less than requested.")
#define NAL_REGISTER_CHECK_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x202F, "The register test for some value failed." )
#define NAL_TIMESYNC_NO_TIMESTAMP NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2030, "No timestamp found")
#define NAL_FLASH_IS_NOT_MAPPED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2031, "Flash is not mapped in the memory BAR")
#define NAL_HMC_NOT_INITIALIZED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2032, "HMC is not initialized")
#define NAL_HMC_PAGE_NOT_ALLOCATED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2033, "Requested HMC page is not allocated")
#define NAL_HMC_PAGE_NOT_VALID NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2034, "Requested HMC page is not marked valid")
#define NAL_FLASH_REGION_PROTECTED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2035, "Flash region protected")
#define NAL_FLASH_REGION_EMPTY NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2036, "Flash region empty")
#define NAL_EEPROM_MERGE_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2037, "Cannot merge EEPROM images")
#define NAL_EEPROM_POINTERS_CORRUPTED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2038, "Pointers in Shadow RAM are corrupted")
#define NAL_FLASH_AUTHENTICATION_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2039, "FLASH image authentication failed")
#define NAL_FLASH_FW_AUTHENTICATION_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x203A, "Current firmware authentication failed - try performing full power cycle")
#define NAL_FLASH_FW_AUTHENTICATION_TIMEOUT NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x203B, "Firmware authentication timeout")
#define NAL_MPHY_READ_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x203C, "mPHY reading failed")
#define NAL_MPHY_WRITE_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x203D, "mPHY writing failed")
#define NAL_EEPROM_RO_WORD_WRITE_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x203E, "Attempt to write RO word failed")
#define NAL_FLASH_DEVICE_TOO_SMALL NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x203F, "Flash device is too small for this image")
#define NAL_ALTRAM_READ_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2040, "AltRAM read failed")
#define NAL_ALTRAM_WRITE_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x2041, "AltRAM write failed")
#define NAL_EEPROM_FW_CRC_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x202D, "Failed to calculate Firmware CRC/Checksum.")
#define NAL_EEPROM_FW_CSUM_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x202C, "Firmware Checksum validation failed.")

#define NAL_RSDP_TABLE_NOT_FOUND NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x1001, "RSDP BIOS Table was not found")
#define NAL_ACPI_TABLE_NOT_FOUND NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x1002, "ACPI BIOS Table was not found")
#define NAL_PCIE_TABLE_NOT_FOUND NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x1003, "PCIE BIOS Table was not found")

#define NAL_QUEUE_NOT_DISABLED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x1004, "Failed to disable the queue")
#define NAL_QUEUE_NOT_ENABLED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x1005, "Failed to enable the queue")
#define NAL_AQUEUE_INITIALIZATION_FAILED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x1006, "Failed to initialize admin queue")

#define NAL_PROTECTION_DOMAIN_MISMATCH NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x1007, "Protection Domain Mismatch")

#define NAL_OTP_CANT_BE_UPDATED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x1008, "OTP can't be updated")
#define NAL_OTP_ACCESS_ERROR NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x1009, "OTP access failed.")

#define NAL_SFP_EEPROM_ACCESS_ERROR NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x100A, "SFP EEPROM access failed.")

#define NAL_ICSP_NOT_ENABLED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x100B, "ICSP Protocol is not enabled.")
#define NAL_ICSP_ID_UNKNOWN NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x100C, "Unknown Microcontroller Device ID.")

#define NAL_PHY_MODE_UNSUPPORTED NalMakeCode(NAL_CODE_ERROR, CODE_NAL, 0x100D, "Current PHY mode is not supported.")

#endif
