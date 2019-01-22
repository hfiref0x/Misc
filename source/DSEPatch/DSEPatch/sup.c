/*******************************************************************************
*
*  (C) COPYRIGHT AUTHORS, 2016 - 2019
*
*  TITLE:       SUP.C
*
*  VERSION:     1.05
*
*  DATE:        22 Jan 2019
*
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
* TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
*******************************************************************************/
#include "global.h"
#include "se_patterns.h"

#define PAGE_SECTION "PAGE"
#define PAGE_SECTION_LEGNTH sizeof(PAGE_SECTION)

/*
* supCopyMemory
*
* Purpose:
*
* Copies bytes between buffers.
*
* dest - Destination buffer
* cbdest - Destination buffer size in bytes
* src - Source buffer
* cbsrc - Source buffer size in bytes
*
*/
void supCopyMemory(
    _Inout_ void *dest,
    _In_ size_t cbdest,
    _In_ const void *src,
    _In_ size_t cbsrc
)
{
    char *d = (char*)dest;
    char *s = (char*)src;

    if ((dest == 0) || (src == 0) || (cbdest == 0))
        return;
    if (cbdest < cbsrc)
        cbsrc = cbdest;

    while (cbsrc > 0) {
        *d++ = *s++;
        cbsrc--;
    }
}

/*
* supGetSystemInfo
*
* Purpose:
*
* Returns buffer with system information by given InfoClass.
*
* Returned buffer must be freed with HeapFree after usage.
* Function will return error after 100 attempts.
*
*/
PVOID supGetSystemInfo(
    _In_ SYSTEM_INFORMATION_CLASS InfoClass
)
{
    INT         c = 0;
    PVOID       Buffer = NULL;
    ULONG		Size = 0x1000;
    NTSTATUS    status;
    ULONG       memIO;
    PVOID       hHeap = NtCurrentPeb()->ProcessHeap;

    do {
        Buffer = RtlAllocateHeap(hHeap, HEAP_ZERO_MEMORY, (SIZE_T)Size);
        if (Buffer != NULL) {
            status = NtQuerySystemInformation(InfoClass, Buffer, Size, &memIO);
        }
        else {
            return NULL;
        }
        if (status == STATUS_INFO_LENGTH_MISMATCH) {
            RtlFreeHeap(hHeap, 0, Buffer);
            Buffer = NULL;
            Size *= 2;
            c++;
            if (c > 100) {
                status = STATUS_SECRET_TOO_LONG;
                break;
            }
        }
    } while (status == STATUS_INFO_LENGTH_MISMATCH);

    if (NT_SUCCESS(status)) {
        return Buffer;
    }

    if (Buffer) {
        RtlFreeHeap(hHeap, 0, Buffer);
    }
    return NULL;
}

/*
* supBackupVBoxDrv
*
* Purpose:
*
* Backup virtualbox driver file if it already installed.
*
*/
BOOL supBackupVBoxDrv(
    _In_ BOOL bRestore
)
{
    BOOL  bResult = FALSE;
    WCHAR szOldDriverName[MAX_PATH * 2];
    WCHAR szNewDriverName[MAX_PATH * 2];
    WCHAR szDriverDirName[MAX_PATH * 2];

    if (!GetSystemDirectory(szDriverDirName, MAX_PATH)) {
        return FALSE;
    }

    _strcat(szDriverDirName, TEXT("\\drivers\\"));

    if (bRestore) {
        _strcpy(szOldDriverName, szDriverDirName);
        _strcat(szOldDriverName, TEXT("VBoxDrv.backup"));
        if (PathFileExists(szOldDriverName)) {
            _strcpy(szNewDriverName, szDriverDirName);
            _strcat(szNewDriverName, TEXT("VBoxDrv.sys"));
            bResult = MoveFileEx(szOldDriverName, szNewDriverName,
                MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH);
        }
    }
    else {
        _strcpy(szOldDriverName, szDriverDirName);
        _strcat(szOldDriverName, TEXT("VBoxDrv.sys"));
        _strcpy(szNewDriverName, szDriverDirName);
        _strcat(szNewDriverName, TEXT("VBoxDrv.backup"));
        bResult = MoveFileEx(szOldDriverName, szNewDriverName,
            MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH);
    }
    return bResult;
}

/*
* supWriteBufferToFile
*
* Purpose:
*
* Create new file and write buffer to it.
*
*/
DWORD supWriteBufferToFile(
    _In_ LPWSTR lpFileName,
    _In_ PVOID Buffer,
    _In_ DWORD BufferSize
)
{
    HANDLE hFile;
    DWORD bytesIO;

    if (
        (lpFileName == NULL) ||
        (Buffer == NULL) ||
        (BufferSize == 0)
        )
    {
        return FALSE;
    }

    hFile = CreateFile(lpFileName,
        GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
        return FALSE;

    WriteFile(hFile, Buffer, BufferSize, &bytesIO, NULL);
    CloseHandle(hFile);

    return bytesIO;
}

/*
* supDetectObjectCallback
*
* Purpose:
*
* Comparer callback routine used in objects enumeration.
*
*/
NTSTATUS NTAPI supDetectObjectCallback(
    _In_ POBJECT_DIRECTORY_INFORMATION Entry,
    _In_ PVOID CallbackParam
)
{
    POBJSCANPARAM Param = (POBJSCANPARAM)CallbackParam;

    if (Entry == NULL) {
        return STATUS_INVALID_PARAMETER_1;
    }

    if (CallbackParam == NULL) {
        return STATUS_INVALID_PARAMETER_2;
    }

    if (Param->Buffer == NULL || Param->BufferSize == 0) {
        return STATUS_MEMORY_NOT_ALLOCATED;
    }

    if (Entry->Name.Buffer) {
        if (_strcmpi_w(Entry->Name.Buffer, Param->Buffer) == 0) {
            return STATUS_SUCCESS;
        }
    }
    return STATUS_UNSUCCESSFUL;
}

/*
* supEnumSystemObjects
*
* Purpose:
*
* Lookup object by name in given directory.
*
*/
NTSTATUS NTAPI supEnumSystemObjects(
    _In_opt_ LPWSTR pwszRootDirectory,
    _In_opt_ HANDLE hRootDirectory,
    _In_ PENUMOBJECTSCALLBACK CallbackProc,
    _In_opt_ PVOID CallbackParam
)
{
    BOOL                cond = TRUE;
    ULONG               ctx, rlen;
    HANDLE              hDirectory = NULL;
    NTSTATUS            status;
    NTSTATUS            CallbackStatus;
    OBJECT_ATTRIBUTES   attr;
    UNICODE_STRING      sname;

    POBJECT_DIRECTORY_INFORMATION    objinf;

    if (CallbackProc == NULL) {
        return STATUS_INVALID_PARAMETER_4;
    }

    status = STATUS_UNSUCCESSFUL;

    __try {

        // We can use root directory.
        if (pwszRootDirectory != NULL) {
            RtlSecureZeroMemory(&sname, sizeof(sname));
            RtlInitUnicodeString(&sname, pwszRootDirectory);
            InitializeObjectAttributes(&attr, &sname, OBJ_CASE_INSENSITIVE, NULL, NULL);
            status = NtOpenDirectoryObject(&hDirectory, DIRECTORY_QUERY, &attr);
            if (!NT_SUCCESS(status)) {
                return status;
            }
        }
        else {
            if (hRootDirectory == NULL) {
                return STATUS_INVALID_PARAMETER_2;
            }
            hDirectory = hRootDirectory;
        }

        // Enumerate objects in directory.
        ctx = 0;
        do {

            rlen = 0;
            status = NtQueryDirectoryObject(hDirectory, NULL, 0, TRUE, FALSE, &ctx, &rlen);
            if (status != STATUS_BUFFER_TOO_SMALL)
                break;

            objinf = RtlAllocateHeap(NtCurrentPeb()->ProcessHeap, HEAP_ZERO_MEMORY, rlen);
            if (objinf == NULL)
                break;

            status = NtQueryDirectoryObject(hDirectory, objinf, rlen, TRUE, FALSE, &ctx, &rlen);
            if (!NT_SUCCESS(status)) {
                RtlFreeHeap(NtCurrentPeb()->ProcessHeap, 0, objinf);
                break;
            }

            CallbackStatus = CallbackProc(objinf, CallbackParam);

            RtlFreeHeap(NtCurrentPeb()->ProcessHeap, 0, objinf);

            if (NT_SUCCESS(CallbackStatus)) {
                status = STATUS_SUCCESS;
                break;
            }

        } while (cond);

        if (hDirectory != NULL) {
            NtClose(hDirectory);
        }

    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        status = STATUS_ACCESS_VIOLATION;
    }

    return status;
}

/*
* supIsObjectExists
*
* Purpose:
*
* Return TRUE if the given object exists, FALSE otherwise.
*
*/
BOOL supIsObjectExists(
    _In_ LPWSTR RootDirectory,
    _In_ LPWSTR ObjectName
)
{
    OBJSCANPARAM Param;

    if (ObjectName == NULL) {
        return FALSE;
    }

    Param.Buffer = ObjectName;
    Param.BufferSize = (ULONG)_strlen(ObjectName);

    return NT_SUCCESS(supEnumSystemObjects(RootDirectory, NULL, supDetectObjectCallback, &Param));
}

/*
* supGetModuleBaseByName
*
* Purpose:
*
* Return module base address.
*
*/
ULONG_PTR supGetModuleBaseByName(
    _In_ LPSTR ModuleName
)
{
    ULONG_PTR ReturnAddress = 0;
    ULONG i, k;
    PRTL_PROCESS_MODULES miSpace;

    miSpace = supGetSystemInfo(SystemModuleInformation);
    if (miSpace != NULL) {
        for (i = 0; i < miSpace->NumberOfModules; i++) {
            k = miSpace->Modules[i].OffsetToFileName;
            if (_strcmpi_a(
                (CONST CHAR*)&miSpace->Modules[i].FullPathName[k],
                ModuleName) == 0)
            {
                ReturnAddress = (ULONG_PTR)miSpace->Modules[i].ImageBase;
                break;
            }
        }
        RtlFreeHeap(NtCurrentPeb()->ProcessHeap, 0, miSpace);
    }
    return ReturnAddress;
}

/*
* supGetNtOsBase
*
* Purpose:
*
* Return ntoskrnl base address.
*
*/
ULONG_PTR supGetNtOsBase(
    VOID
)
{
    PRTL_PROCESS_MODULES   miSpace;
    ULONG_PTR              NtOsBase = 0;

    miSpace = supGetSystemInfo(SystemModuleInformation);
    if (miSpace != NULL) {
        NtOsBase = (ULONG_PTR)miSpace->Modules[0].ImageBase;
        RtlFreeHeap(NtCurrentPeb()->ProcessHeap, 0, miSpace);
    }
    return NtOsBase;
}

/*
* supIsVBoxInstalled
*
* Purpose:
*
* Check VirtualBox software installation state.
*
*/
BOOL supIsVBoxInstalled(
    VOID
)
{
    BOOL     bPresent = FALSE;
    LRESULT  lRet;
    HKEY     hKey = NULL;

    lRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("Software\\Oracle\\VirtualBox"),
        0, KEY_READ, &hKey);

    bPresent = (hKey != NULL);

    if (hKey) {
        RegCloseKey(hKey);
    }

    return bPresent;
}

/*
* supLookupImageSectionByName
*
* Purpose:
*
* Lookup section pointer and size for section name.
*
*/
PVOID supLookupImageSectionByName(
    _In_ CHAR* SectionName,
    _In_ ULONG SectionNameLength,
    _In_ PVOID DllBase,
    _Out_ PULONG SectionSize
)
{
    BOOLEAN bFound = FALSE;
    ULONG i;
    PVOID Section;
    IMAGE_NT_HEADERS *NtHeaders = RtlImageNtHeader(DllBase);
    IMAGE_SECTION_HEADER *SectionTableEntry;

    if (SectionSize)
        *SectionSize = 0;

    SectionTableEntry = (PIMAGE_SECTION_HEADER)((PCHAR)NtHeaders +
        sizeof(ULONG) +
        sizeof(IMAGE_FILE_HEADER) +
        NtHeaders->FileHeader.SizeOfOptionalHeader);

    //
    // Locate section.
    //
    i = NtHeaders->FileHeader.NumberOfSections;
    while (i > 0) {

        if (_strncmp_a(
            (CHAR*)SectionTableEntry->Name,
            SectionName,
            SectionNameLength) == 0)
        {
            bFound = TRUE;
            break;
        }

        i -= 1;
        SectionTableEntry += 1;
    }

    //
    // Section not found, abort scan.
    //
    if (!bFound)
        return NULL;

    Section = (PVOID)((ULONG_PTR)DllBase + SectionTableEntry->VirtualAddress);
    if (SectionSize)
        *SectionSize = SectionTableEntry->Misc.VirtualSize;

    return Section;
}

/*
* supFindCiCallbacks
*
* Purpose:
*
* Locate address of ntoskrnl g_CiCallbacks/SeCiCallbacks structure.
*
*/
ULONG_PTR supFindCiCallbacks(
    _In_ ULONG NtBuildNumber,
    _In_ ULONG NtOsSize,
    _In_ ULONG_PTR NtOsBase,
    _In_ HMODULE hNtOs
)
{
    BOOL    bCond = FALSE;

    ULONG_PTR Address = 0, Result = 0;

    PBYTE   Signature = NULL, ptrCode = NULL, MatchingPattern = NULL;
    ULONG   SignatureSize = 0;

    PVOID   SectionBase;
    ULONG   SectionSize = 0, Index;

    LONG    Rel = 0;
    hde64s  hs;

    do {
        //
        // Locate PAGE image section as required variable is always in PAGE.
        //
        SectionBase = supLookupImageSectionByName(
            PAGE_SECTION,
            PAGE_SECTION_LEGNTH,
            (PVOID)hNtOs,
            &SectionSize);

        if ((SectionBase == 0) || (SectionSize == 0))
            break;

        MatchingPattern = SeCiCallbacksMatchingPattern; //default matching pattern

        switch (NtBuildNumber) {

        case 7601:
            Signature = g_CiCallbacksPattern_7601;
            SignatureSize = sizeof(g_CiCallbacksPattern_7601);
            MatchingPattern = g_CiCallbacksMatchingPattern;
            break;

        case 9200:
        case 9600:
            Signature = SeCiCallbacksPattern_9200_9600;
            SignatureSize = sizeof(SeCiCallbacksPattern_9200_9600);
            MatchingPattern = SeCiCallbacksMatchingPattern;
            break;

        case 10240:
        case 10586:
            Signature = SeCiCallbacksPattern_10240_10586;
            SignatureSize = sizeof(SeCiCallbacksPattern_10240_10586);
            MatchingPattern = SeCiCallbacksMatchingPattern;
            break;

        case 14393:
            Signature = SeCiCallbacksPattern_14393;
            SignatureSize = sizeof(SeCiCallbacksPattern_14393);
            MatchingPattern = SeCiCallbacksMatchingPattern;
            break;

        case 15063:
        case 16299:
            Signature = SeCiCallbacksPattern_15063_16299;
            SignatureSize = sizeof(SeCiCallbacksPattern_15063_16299);
            MatchingPattern = SeCiCallbacksMatchingPattern;
            break;

        case 17134:
        case 17763:
            Signature = SeCiCallbacksPattern_17134_17763;
            SignatureSize = sizeof(SeCiCallbacksPattern_17134_17763);
            MatchingPattern = SeCiCallbacksMatchingPattern;
            break;

        default:
            break;
        }

        if ((SignatureSize) && (Signature)) {

            ptrCode = (PBYTE)supFindPattern(
                (PBYTE)SectionBase,
                SectionSize,
                Signature,
                SignatureSize);
        }

        if (ptrCode == NULL)
            break;

        if (NtBuildNumber <= 7601) {

            //
            // Find reference to g_CiCallbacks in code.
            //

            Index = 0; //pattern search include target instruction, do not skip

        }
        else {

            //
            // Find reference to SeCiCallbacks/g_CiCallbacks in code.
            //

            Index = SignatureSize; //skip signature instructions

        }

        do {
            hde64_disasm((void*)(ptrCode + Index), &hs);
            if (hs.flags & F_ERROR)
                break;
            //
            // mov cs:g_CiCallbacks, rax (for Windows 7)
            // lea rcx, SeCiCallbacks (for everything else)
            //
            if (hs.len == 7) {
                if ((ptrCode[Index] == MatchingPattern[0]) &&
                    (ptrCode[Index + 1] == MatchingPattern[1]) &&
                    (ptrCode[Index + 2] == MatchingPattern[2]))
                {
                    Rel = *(PLONG)(ptrCode + Index + 3);
                    break;
                }
            }
            Index += hs.len;

        } while (Index < 64);

        if (Rel == 0)
            break;

        Address = (ULONG_PTR)ptrCode + Index + hs.len + Rel;
        Address = NtOsBase + Address - (ULONG_PTR)hNtOs;

        if (!IN_REGION(Address, NtOsBase, NtOsSize))
            break;

        Result = Address;

    } while (bCond);

    return Result;
}

/*
* supFindPattern
*
* Purpose:
*
* Lookup pattern in buffer.
*
*/
PVOID supFindPattern(
    _In_ CONST PBYTE Buffer,
    _In_ SIZE_T BufferSize,
    _In_ CONST PBYTE Pattern,
    _In_ SIZE_T PatternSize
)
{
    PBYTE	p = Buffer;

    if (PatternSize == 0)
        return NULL;
    if (BufferSize < PatternSize)
        return NULL;
    BufferSize -= PatternSize;

    do {
        p = (PBYTE)memchr(p, Pattern[0], BufferSize - (p - Buffer));
        if (p == NULL)
            break;

        if (memcmp(p, Pattern, PatternSize) == 0)
            return p;

        p++;
    } while (BufferSize - (p - Buffer) > 0); //-V555

    return NULL;
}

/*
* supSizeOfProc
*
* Purpose:
*
* Very simplified. Return size of procedure when first ret meet.
* Limit size to 4k.
*
*/
ULONG supSizeOfProc(
    _In_ PBYTE FunctionPtr)
{
    ULONG   c = 0;
    UCHAR  *p;
    hde64s  hs;

    __try {

        do {
            p = FunctionPtr + c;
            hde64_disasm(p, &hs);
            if (hs.flags & F_ERROR)
                break;

            if (hs.len == 1) {
                if (*p == 0xC3)
                    return c + 1;
            }
            c += hs.len;

        } while (c < 4096);

    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return 0;
    }
    return c;
}

/*
* supGetProcAddress
*
* Purpose:
*
* Get NtOskrnl procedure address.
*
*/
ULONG_PTR supGetProcAddress(
    _In_ ULONG_PTR KernelBase,
    _In_ ULONG_PTR KernelImage,
    _In_ LPCSTR FunctionName
)
{
    ANSI_STRING    cStr;
    ULONG_PTR      pfn = 0;

    RtlInitString(&cStr, FunctionName);
    if (!NT_SUCCESS(LdrGetProcedureAddress((PVOID)KernelImage, &cStr, 0, (PVOID)&pfn)))
        return 0;

    return KernelBase + (pfn - KernelImage);
}
