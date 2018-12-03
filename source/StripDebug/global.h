#pragma once

//disable nonmeaningful warnings.
#pragma warning(disable: 4091) //'typedef ': ignored on left of '' when no variable is declared
#pragma warning(disable: 4005) // macro redefinition
#pragma warning(disable: 4201) // nonstandard extension used : nameless struct/union
#pragma warning(disable: 4054) // %s : from function pointer %s to data pointer %s
#pragma warning(disable: 6102) // Using %s from failed function call at line %u

#include <Windows.h>
#include <DbgHelp.h>
#include "cui.h"
#include "minirtl\minirtl.h"
#include "minirtl\cmdline.h"

#pragma comment(lib, "dbghelp.lib")
#pragma comment(lib, "imagehlp.lib")

#if !defined UNICODE
#error ANSI build is not supported
#endif

#if defined (_MSC_VER)
#if (_MSC_VER >= 1910)
#ifdef _DEBUG
#pragma comment(lib, "vcruntimed.lib")
#pragma comment(lib, "ucrtd.lib")
#else
#pragma comment(lib, "libucrt.lib")
#pragma comment(lib, "libvcruntime.lib")
#endif
#endif
#endif

#define IMAGE_DEBUG_TYPE_POGO 13

PIMAGE_NT_HEADERS WINAPI CheckSumMappedFile(
    _In_ PVOID BaseAddress,
    _In_ DWORD FileLength,
    _Out_ PDWORD HeaderSum,
    _Out_ PDWORD CheckSum
);

