#include "global.h"

void ProcessFile(
    LPSTR lpFileName
)
{
    HANDLE  hFile = INVALID_HANDLE_VALUE;
    HANDLE  hFileMap = NULL;
    DWORD   FileSize;
    LPVOID  ImageBase = NULL;

    INT i, cEntries;

    PIMAGE_OPTIONAL_HEADER32    oh32 = NULL;
    PIMAGE_OPTIONAL_HEADER64    oh64 = NULL;
    PIMAGE_SECTION_HEADER       SectionHeader = NULL;

    ULONG DebugDirRva, DebugDirSize, Offset, CurrentCheckSum, NewCheckSum;

    IMAGE_NT_HEADERS *NtHeaders = NULL;
    IMAGE_DEBUG_DIRECTORY *DebugDirectory;
    LPBYTE pDebugInfo;

    __try {

        hFile = CreateFileA(lpFileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE) {
            cuiPrintTextA("Cannot open input file", TRUE);
            __leave;
        }

        FileSize = GetFileSize(hFile, NULL);
        if (FileSize == 0) {
            cuiPrintTextA("Input file is empty", TRUE);
            __leave;
        }

        hFileMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, NULL);
        if (hFileMap == NULL) {
            cuiPrintTextA("CreateFileMapping failed for input file", TRUE);
            __leave;
        }

        ImageBase = MapViewOfFile(hFileMap, FILE_MAP_WRITE, 0, 0, 0);
        if (ImageBase == NULL) {
            cuiPrintTextA("MapViewOfFile failed for input file", TRUE);
            __leave;
        }

        NtHeaders = ImageNtHeader(ImageBase);
        if (NtHeaders == NULL) {
            cuiPrintTextA("ImageNtHeaders failed for input file", TRUE);
            __leave;
        }

        oh32 = (PIMAGE_OPTIONAL_HEADER32)&NtHeaders->OptionalHeader;
        oh64 = (PIMAGE_OPTIONAL_HEADER64)oh32;

        if ((NtHeaders->FileHeader.Machine != IMAGE_FILE_MACHINE_AMD64) && (NtHeaders->FileHeader.Machine != IMAGE_FILE_MACHINE_I386)) {
            cuiPrintTextA("Unsuported FileHeader.Machine value", TRUE);
            __leave;
        }

        if (NtHeaders->FileHeader.Machine == IMAGE_FILE_MACHINE_AMD64) {
            DebugDirRva = oh64->DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress;
            if (DebugDirRva == 0) {
                cuiPrintTextA("DebugDirectory address not set", TRUE);
                __leave;
            }
            else {
                cuiPrintTextA("Setting DebugDirectory.VirtualAddress to zero", TRUE);
                oh64->DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress = 0;
            }

            DebugDirSize = oh64->DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size;
            if (DebugDirSize == 0) {
                cuiPrintTextA("DebugDirectory is zero size", TRUE);
                __leave;
            }
            else {
                cuiPrintTextA("Setting DebugDirectory.Size to zero", TRUE);
                oh64->DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size = 0;
            }
        }
        else {
            DebugDirRva = oh32->DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress;
            if (DebugDirRva == 0) {
                cuiPrintTextA("DebugDirectory address not set", TRUE);
                __leave;
            }
            else {
                cuiPrintTextA("Setting DebugDirectory.VirtualAddress to zero", TRUE);
                oh32->DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].VirtualAddress = 0;
            }

            DebugDirSize = oh32->DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size;
            if (DebugDirSize == 0) {
                cuiPrintTextA("DebugDirectory is zero size", TRUE);
                __leave;
            }
            else {
                cuiPrintTextA("Setting DebugDirectory.Size to zero", TRUE);
                oh32->DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG].Size = 0;
            }
        }

        SectionHeader = ImageRvaToSection(NtHeaders, ImageBase, DebugDirRva);
        if (SectionHeader) {
            Offset = DebugDirRva - ((ULONG)(SectionHeader->VirtualAddress - SectionHeader->PointerToRawData));
            cEntries = DebugDirSize / sizeof(IMAGE_DEBUG_DIRECTORY);
            DebugDirectory = (IMAGE_DEBUG_DIRECTORY *)((ULONG_PTR)ImageBase + Offset);
            if (DebugDirectory) {
                for (i = 1; i <= cEntries; i++) {
                    if (DebugDirectory->Type == IMAGE_DEBUG_TYPE_POGO) {
                        pDebugInfo = (LPBYTE)((ULONG_PTR)ImageBase + DebugDirectory->PointerToRawData);
                        if (pDebugInfo) {
                            RtlSecureZeroMemory(pDebugInfo, DebugDirectory->SizeOfData);
                            cuiPrintTextA("Zeroing debug data", TRUE);
                        }
                    }
                    DebugDirectory++;
                    if (DebugDirectory->SizeOfData == 0)
                        continue;
                }
            }
            else {
                cuiPrintTextA("DebugDirectory address invalid", TRUE);
            }
        }
        else {
            cuiPrintTextA("SectionHeader address invalid", TRUE);
        }

        NewCheckSum = 0;
        CheckSumMappedFile(ImageBase, FileSize, &CurrentCheckSum, &NewCheckSum);
        if (NtHeaders->FileHeader.Machine == IMAGE_FILE_MACHINE_AMD64) {
            oh64->CheckSum = NewCheckSum;
        }
        else {
            oh32->CheckSum = NewCheckSum;
        }
    }
    __finally {
        if (ImageBase) {
            FlushViewOfFile(ImageBase, 0);
            UnmapViewOfFile(ImageBase);
        }

        if (hFileMap)
            CloseHandle(hFileMap);

        if (hFile != INVALID_HANDLE_VALUE)
            CloseHandle(hFile);
    }
}

void main()
{
    ULONG l;
    CHAR szFileName[MAX_PATH + 1];

    __security_init_cookie();

    cuiInitialize(FALSE, NULL);

    l = 0;
    RtlSecureZeroMemory(szFileName, sizeof(szFileName));
    GetCommandLineParamA(GetCommandLineA(), 1, szFileName, MAX_PATH, &l);
    if (l > 0) {
        cuiPrintTextA("Processing input file", TRUE);
        cuiPrintTextA(szFileName, TRUE);
        ProcessFile(szFileName);
    }

    ExitProcess(0);
}
