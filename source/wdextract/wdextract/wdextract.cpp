#include "pch.h"
#include <Windows.h>
#include <strsafe.h>
#include "zlib.h"

#pragma comment(lib, "zlibwapi.lib")

typedef struct _RMDX_HEADER {
    ULONG Signature;        //0
    ULONG Unknown1;         //4
    ULONG Unknown2;         //8
    ULONG Options;          //12 (0C)
    ULONG Unknown3;         //16
    ULONG Unknown4;         //20
    ULONG DataOffset;       //24 (18)
    ULONG Checksum;         //28 (1C)
    //incomplete, irrelevant

} RMDX_HEADER, *PRMDX_HEADER;

typedef struct _CDATA_HEADER {
    ULONG Length;             //0
    ULONG Checksum;           //4
    BYTE Data[1];             //8
} CDATA_HEADER, *PCDATA_HEADER;

#define CHUNK 32768// 16384

unsigned char input_buffer[CHUNK];
unsigned char output_buffer[CHUNK];

#define ShowError(Error) MessageBox(GetDesktopWindow(), Error, NULL, MB_ICONERROR)
#define RtlOffsetToPointer(Base, Offset) ((PCHAR)( ((PCHAR)(Base)) + ((ULONG_PTR)(Offset)) ))

ULONG fwrite(PBYTE InputBuffer, ULONG Size, ULONG Count, HANDLE hFile)
{
    DWORD write = 0;
    WriteFile(hFile, InputBuffer, Count * Size, &write, NULL);
    return write;
}

void ExtractData(LPWSTR FileName)
{
    BOOLEAN IsCompressed = FALSE;
    HANDLE  FileOutputHandle = INVALID_HANDLE_VALUE;
    LPWSTR  NewFileName;
    SIZE_T  FileNameLength = 0;

    int ret;
    unsigned have, got;
    z_stream strm;

    __try {

        HMODULE Dll = LoadLibraryEx(FileName, NULL, DONT_RESOLVE_DLL_REFERENCES);
        if (Dll == NULL) {
            ShowError(TEXT("Cannot load input file."));
            __leave;
        }

        HRSRC hRes = FindResource(Dll, MAKEINTRESOURCE(1000), TEXT("RT_RCDATA"));
        HGLOBAL hResData = LoadResource(Dll, hRes);
        PVOID Data = LockResource(hResData);

        PRMDX_HEADER Header = (PRMDX_HEADER)Data;
        if (Header == NULL) {
            ShowError(TEXT("Resource not found."));
            __leave;
        }

        if (Header->Signature != 'XDMR') {
            ShowError(TEXT("Signature not found."));
            __leave;
        }

        IsCompressed = ((Header->Options >> 1) & 0xff);
        if (IsCompressed != TRUE) {
            ShowError(TEXT("Unexpected header value."));
            __leave;
        }

        PCDATA_HEADER DataHeader = (PCDATA_HEADER)RtlOffsetToPointer(Header, Header->DataOffset);
        if (DataHeader->Length == 0) {
            ShowError(TEXT("Unexpected data header size."));
            __leave;
        }

        StringCchLength(FileName, MAX_PATH, &FileNameLength);
        FileNameLength += (1 + MAX_PATH);
        NewFileName = (LPWSTR)LocalAlloc(LPTR, FileNameLength * sizeof(WCHAR));
        if (NewFileName == NULL) {
            ShowError(TEXT("Memory allocation error."));
            __leave;
        }

        StringCchPrintf(NewFileName, FileNameLength, TEXT("%s.extracted"), FileName);

        FileOutputHandle = CreateFile(NewFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
        LocalFree(NewFileName);

        if (FileOutputHandle == INVALID_HANDLE_VALUE) {
            ShowError(TEXT("Can not create output file."));
            __leave;
        }

        __stosb(input_buffer, 0, sizeof(input_buffer));
        __stosb(output_buffer, 0, sizeof(output_buffer));

        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        strm.avail_in = 0;
        strm.next_in = Z_NULL;
        ret = inflateInit2(&strm, -15);
        if (ret != Z_OK) {
            ShowError(TEXT("inflateInit2 error."));
            __leave;
        }

        DWORD CurrentPosition = 0;
        DWORD CopyLength;
        DWORD TotalBytesWritten = 0;
        DWORD ResourceSize = DataHeader->Length;
        Data = DataHeader->Data;

        do {

            CopyLength = CHUNK;
            if (CurrentPosition + CopyLength > ResourceSize)
                CopyLength = ResourceSize - CurrentPosition;

            RtlCopyMemory(input_buffer, RtlOffsetToPointer(Data, CurrentPosition), CopyLength);
            CurrentPosition += CopyLength;

            strm.avail_in = CopyLength;
            if (strm.avail_in == 0)
                break;
            strm.next_in = input_buffer;

            do {
                strm.avail_out = CHUNK;
                strm.next_out = output_buffer;
                ret = inflate(&strm, Z_NO_FLUSH);

                switch (ret) {
                case Z_NEED_DICT:
                    ret = Z_DATA_ERROR;
                case Z_DATA_ERROR:
                case Z_MEM_ERROR:
                    inflateEnd(&strm);
                    __leave;
                }
                have = CHUNK - strm.avail_out;
                got = fwrite(output_buffer, 1, have, FileOutputHandle);
                TotalBytesWritten += got;
                if (got != have) {
                    inflateEnd(&strm);
                    ShowError(TEXT("Error while unpacking."));
                    __leave;
                }
            } while (strm.avail_out == 0);

        } while (ret != Z_STREAM_END);

        inflateEnd(&strm);

        WCHAR szTotalMsg[200];

        StringCbPrintf(szTotalMsg, 
            _countof(szTotalMsg), 
            TEXT("Unpack code\r\nTotal bytes written = %lu\r\nTotal bytes read = %lu"), 
            TotalBytesWritten, 
            CurrentPosition);

        MessageBox(GetDesktopWindow(), szTotalMsg, TEXT(""), MB_ICONINFORMATION);

    }
    __finally {
        if (FileOutputHandle != INVALID_HANDLE_VALUE)
            CloseHandle(FileOutputHandle);
    }
}

int main()
{
    INT nArgs = 0;
    BOOLEAN fCommand = FALSE;

    LPWSTR *szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
    if (szArglist) {

        if (nArgs > 0) {
            LPWSTR Param = szArglist[1];
            if (Param) {
                ExtractData(Param);
                fCommand = TRUE;
            }
        }
        LocalFree(szArglist);
    }

    if (fCommand != TRUE)
        MessageBox(GetDesktopWindow(), TEXT("Usage: wdextract file"), TEXT("WD data extractor"), MB_OK);

    return 0;
}
