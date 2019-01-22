/*******************************************************************************
*
*  (C) COPYRIGHT AUTHORS, 2016 - 2019
*
*  TITLE:       SUP.H
*
*  VERSION:     1.00
*
*  DATE:        23 Jan 2019
*
*  Common header file for the program support routines.
*
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
* TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
*******************************************************************************/
#pragma once

typedef NTSTATUS(NTAPI *PENUMOBJECTSCALLBACK)(POBJECT_DIRECTORY_INFORMATION Entry, PVOID CallbackParam);

typedef struct _OBJSCANPARAM {
    PWSTR Buffer;
    ULONG BufferSize;
} OBJSCANPARAM, *POBJSCANPARAM;

void supCopyMemory(
    _Inout_ void *dest,
    _In_ size_t ccdest,
    _In_ const void *src,
    _In_ size_t ccsrc);

PVOID supGetSystemInfo(
    _In_ SYSTEM_INFORMATION_CLASS InfoClass);

BOOL supBackupVBoxDrv(
    _In_ BOOL bRestore);

DWORD supWriteBufferToFile(
    _In_ LPWSTR lpFileName,
    _In_ PVOID Buffer,
    _In_ DWORD BufferSize);

BOOL supIsObjectExists(
    _In_ LPWSTR RootDirectory,
    _In_ LPWSTR ObjectName);

ULONG_PTR supGetModuleBaseByName(
    _In_ LPSTR ModuleName);

ULONG_PTR supGetNtOsBase(
    VOID);

BOOL supIsVBoxInstalled(
	VOID);

PVOID supLookupImageSectionByName(
	_In_ CHAR* SectionName,
	_In_ ULONG SectionNameLength,
	_In_ PVOID DllBase,
	_Out_ PULONG SectionSize);

ULONG_PTR supFindCiCallbacks(
	_In_ ULONG NtBuildNumber,
	_In_ ULONG NtOsSize,
	_In_ ULONG_PTR NtOsBase,
	_In_ HMODULE hNtOs);

PVOID supFindPattern(
    _In_ CONST PBYTE Buffer,
    _In_ SIZE_T BufferSize,
    _In_ CONST PBYTE Pattern,
    _In_ SIZE_T PatternSize);

ULONG supSizeOfProc(
    _In_ PBYTE FunctionPtr);

ULONG_PTR supGetProcAddress(
    _In_ ULONG_PTR KernelBase,
    _In_ ULONG_PTR KernelImage,
    _In_ LPCSTR FunctionName);

#define PathFileExists(lpszPath) (GetFileAttributes(lpszPath) != (DWORD)-1)
