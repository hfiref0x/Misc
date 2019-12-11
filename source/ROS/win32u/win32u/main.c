/*******************************************************************************
*
*  (C) COPYRIGHT hfiref0x, 2018 - 2019
*
*  TITLE:       MAIN.C
*
*  VERSION:     1.01
*
*  DATE:        06 Dec 2019
*
*  Syscall stubs for NtUser/NtGdi
*
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
* TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
*******************************************************************************/

#if !defined UNICODE
#error ANSI build is not supported
#endif

#if defined (_MSC_VER)
#if (_MSC_VER >= 1900) //VS15, 17 etc
#ifdef _DEBUG
#pragma comment(lib, "vcruntimed.lib")
#pragma comment(lib, "ucrtd.lib")
#else
#pragma comment(lib, "libucrt.lib")
#pragma comment(lib, "libvcruntime.lib")
#endif
#endif
#endif

#include <Windows.h>

//
// These files are machine generated, do not edit.
//
#ifdef _RELEASE_FOR_CHECKED
#include "w32kcall_checked.h"
#include "w32parguments_checked.h"
#else
#include "w32kcall.h"
#include "w32parguments.h"
#endif

ULONG W32pServiceLimit = sizeof(W32pServiceArgumentTable);
