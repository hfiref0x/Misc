/*******************************************************************************
*
*  (C) COPYRIGHT AUTHORS, 2016 - 2018
*
*  TITLE:       MAIN.C
*
*  VERSION:     1.00
*
*  DATE:        01 Dec 2018
*
*  SRVANY2 for ReactOS tests, based on srvany-ng by Anthony Birkett.
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
#if (_MSC_VER >= 1900)
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
#include "minirtl/minirtl.h"
#include "minirtl/cmdline.h"

#define SVC_NAME TEXT("srvany2")
#define MAX_DATA_LENGTH 16384

SERVICE_STATUS_HANDLE g_StatusHandle = NULL;
HANDLE                g_ServiceStopEvent = NULL;
PROCESS_INFORMATION   g_ProcessInformation;

/*
* ServiceWorkerThread
*
* Purpose:
*
* Worker thread for waiting payload process.
*
*/
DWORD WINAPI ServiceWorkerThread(
    _In_ LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);

    OutputDebugString(TEXT("ServiceWorkerThread"));

    while (WaitForSingleObject(g_ServiceStopEvent, 0) != WAIT_OBJECT_0)
    {
        if (WaitForSingleObject(g_ProcessInformation.hProcess, 0) == WAIT_OBJECT_0) {
            OutputDebugString(TEXT("Wait complete, setting stop event"));
            SetEvent(g_ServiceStopEvent);
        }
        Sleep(1000);
    }

    return ERROR_SUCCESS;
}

/*
* ServiceSetState
*
* Purpose:
*
* Updates the service control manager's status information for the calling service.
*
*/
VOID ServiceSetState(
    _In_ DWORD dwControlsAccepted,
    _In_ DWORD dwCurrentState,
    _In_ DWORD dwWin32ExitCode
)
{
    SERVICE_STATUS serviceStatus;

    OutputDebugString(TEXT("ServiceSetState"));

    RtlSecureZeroMemory(&serviceStatus, sizeof(SERVICE_STATUS));
    serviceStatus.dwCheckPoint = 0;
    serviceStatus.dwControlsAccepted = dwControlsAccepted;
    serviceStatus.dwCurrentState = dwCurrentState;
    serviceStatus.dwServiceSpecificExitCode = 0;
    serviceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS;
    serviceStatus.dwWaitHint = 0;
    serviceStatus.dwWin32ExitCode = dwWin32ExitCode;

    SetServiceStatus(g_StatusHandle, &serviceStatus);
}

/*
* ServiceCtrlHandler
*
* Purpose:
*
* Handler for service control codes.
*
*/
VOID WINAPI ServiceCtrlHandler(
    _In_ DWORD ControlCode
)
{
    OutputDebugString(TEXT("ServiceCtrlHandler"));

    switch (ControlCode)
    {
    case SERVICE_CONTROL_STOP:
        SetEvent(g_ServiceStopEvent);
        TerminateProcess(g_ProcessInformation.hProcess, 0);
        ServiceSetState(0, SERVICE_STOPPED, 0);
        break;

    case SERVICE_CONTROL_PAUSE:
        ServiceSetState(0, SERVICE_PAUSED, 0);
        break;

    case SERVICE_CONTROL_CONTINUE:
        ServiceSetState(0, SERVICE_RUNNING, 0);
        break;

    default:
        break;
    }
}

/*
* ServiceMain
*
* Purpose:
*
* Service initialization routine and payload.
*
*/
VOID WINAPI ServiceMain(
    _In_ DWORD  dwArgc,
    _In_ LPTSTR *lpszArgv
)
{
    HANDLE hHeap = GetProcessHeap();
    HANDLE hThread;

    TCHAR *pszApplication;
    TCHAR *pszCommandLine;
    TCHAR *pszEnvironment;
    TCHAR *pszCurrentDirectory;

    DWORD cch;

    HKEY hKey;

    DWORD dwType, cbData;

    DWORD dwFlags = CREATE_UNICODE_ENVIRONMENT;

    STARTUPINFO startupInfo;
    TCHAR szKey[MAX_PATH];

    UNREFERENCED_PARAMETER(dwArgc);
    UNREFERENCED_PARAMETER(lpszArgv);

    OutputDebugString(TEXT("ServiceMain"));

    RtlSecureZeroMemory(&startupInfo, sizeof(startupInfo));
    RtlSecureZeroMemory(&g_ProcessInformation, sizeof(g_ProcessInformation));

    //
    // Allocate CreateProcess buffers.
    //
    pszApplication = (TCHAR*)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, MAX_DATA_LENGTH + 2);
    if (pszApplication == NULL) {
        OutputDebugString(TEXT("pszApplication not allocated - critical"));
        ServiceSetState(0, SERVICE_STOPPED, GetLastError());
        return;
    }
    pszCommandLine = (TCHAR*)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, MAX_DATA_LENGTH + 2);
    if (pszCommandLine == NULL) {
        OutputDebugString(TEXT("pszCommandLine not allocated - critical"));
        ServiceSetState(0, SERVICE_STOPPED, GetLastError());
        return;
    }
    pszEnvironment = (TCHAR*)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, MAX_DATA_LENGTH + 2);
    if (pszEnvironment == NULL) {
        OutputDebugString(TEXT("pszCurrentDirectory not allocated - critical"));
        ServiceSetState(0, SERVICE_STOPPED, GetLastError());
        return;
    }
    pszCurrentDirectory = (TCHAR*)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, MAX_DATA_LENGTH + 2);
    if (pszCurrentDirectory == NULL) {
        OutputDebugString(TEXT("pszCurrentDirectory not allocated - critical"));
        ServiceSetState(0, SERVICE_STOPPED, GetLastError());
        return;
    }

    //
    // Control handler.
    //
    g_StatusHandle = RegisterServiceCtrlHandler(SVC_NAME, ServiceCtrlHandler);
    if (g_StatusHandle == NULL) {
        OutputDebugString(TEXT("RegisterServiceCtrlHandler failed - critical"));
        ServiceSetState(0, SERVICE_STOPPED, GetLastError());
        return;
    }

    //
    // Service stop notification event.
    //
    g_ServiceStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (g_ServiceStopEvent == NULL) {
        OutputDebugString(TEXT("CreateEvent failed - critical"));
        ServiceSetState(0, SERVICE_STOPPED, GetLastError());
        return;
    }

    //
    // Open service parameters keys.
    //
    _strcpy(szKey, TEXT("SYSTEM\\CurrentControlSet\\Services\\srvany2\\Parameters\\"));

    if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_LOCAL_MACHINE, szKey, 0, KEY_READ, &hKey)) {
        OutputDebugString(TEXT("Parameters key open failed - critical"));
        ServiceSetState(0, SERVICE_STOPPED, GetLastError());
        return;
    }

    //
    // Read ApplicationName.
    //
    cbData = MAX_DATA_LENGTH;
    if (ERROR_SUCCESS != RegQueryValueEx(hKey, TEXT("ApplicationName"),
        NULL, &dwType, (LPBYTE)pszApplication, &cbData))
    {
        OutputDebugString(TEXT("ApplicationName read failed - critical"));

        ServiceSetState(0, SERVICE_STOPPED, GetLastError());
        return;
    }

    //
    // Read CommandLine.
    //
    cbData = MAX_DATA_LENGTH;
    if (ERROR_SUCCESS != RegQueryValueEx(hKey, TEXT("CommandLine"),
        NULL, &dwType, (LPBYTE)pszCommandLine, &cbData))
    {
        OutputDebugString(TEXT("CommandLine not set or query error"));

        HeapFree(hHeap, 0, pszCommandLine);
        pszCommandLine = NULL;
    }


    //
    // Read Environment.
    //
    cbData = MAX_DATA_LENGTH;
    if (ERROR_SUCCESS != RegQueryValueEx(hKey, TEXT("Environment"),
        NULL, &dwType, (LPBYTE)pszEnvironment, &cbData))
    {
        OutputDebugString(TEXT("Environment not set or query error"));

        HeapFree(hHeap, 0, pszEnvironment);
        pszEnvironment = GetEnvironmentStrings();
    }

    //
    // Read CurrentDirectory.
    //
    cbData = MAX_DATA_LENGTH;
    if (ERROR_SUCCESS != RegQueryValueEx(hKey, TEXT("CurrentDirectory"),
        NULL, &dwType, (LPBYTE)pszCurrentDirectory, &cbData))
    {
        OutputDebugString(TEXT("CurrentDirectory not set or query error"));

        RtlSecureZeroMemory(pszCurrentDirectory, MAX_DATA_LENGTH);

        cch = GetCurrentDirectory(MAX_DATA_LENGTH, pszCurrentDirectory);
        if ((cch == 0) || (cch > MAX_DATA_LENGTH)) {
            HeapFree(hHeap, 0, pszCurrentDirectory);
            pszCurrentDirectory = NULL;
        }
    }

    startupInfo.cb = sizeof(startupInfo);
    startupInfo.dwFlags = STARTF_USESHOWWINDOW;
    startupInfo.wShowWindow = SW_SHOW;

    if (CreateProcess(pszApplication,
        pszCommandLine,
        NULL,
        NULL,
        FALSE,
        dwFlags,
        pszEnvironment,
        pszCurrentDirectory,
        &startupInfo,
        &g_ProcessInformation))
    {
        OutputDebugString(TEXT("CreateProcess success"));

        ServiceSetState(SERVICE_ACCEPT_STOP, SERVICE_RUNNING, 0);

        hThread = CreateThread(NULL, 0, ServiceWorkerThread, NULL, 0, NULL);
        if (hThread == NULL) {
            ServiceSetState(0, SERVICE_STOPPED, GetLastError());
            return;
        }
        WaitForSingleObject(hThread, INFINITE);
    }
    else {
        OutputDebugString(TEXT("CreateProcess failed"));
    }

    OutputDebugString(TEXT("Service shutdown"));

    CloseHandle(g_ServiceStopEvent);
    ServiceSetState(0, SERVICE_STOPPED, 0);
}

//#define APP

#ifdef APP

/*
* InstallService
*
* Purpose:
*
* Installs service, force removes previous if found.
*
*/
BOOL InstallService(
    _In_ LPCTSTR lpServiceName,
    _In_ LPCTSTR lpBinary
)
{
    BOOL bResult = FALSE;

    DWORD retryCount;

    SC_HANDLE hManager, hService = NULL, hExService;

    hManager = OpenSCManager(NULL, SERVICES_ACTIVE_DATABASE, SC_MANAGER_CREATE_SERVICE);
    if (hManager) {

        retryCount = 0;

        while (1) {

            hService = CreateService(hManager,
                lpServiceName,
                lpServiceName,
                SERVICE_ALL_ACCESS,
                SERVICE_INTERACTIVE_PROCESS | SERVICE_WIN32_OWN_PROCESS,
                SERVICE_DEMAND_START,
                SERVICE_ERROR_NORMAL,
                lpBinary,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL);

            if (hService) {
                break;
            }
            else {
                OutputDebugString(TEXT("CreateService fail"));
            }

            if (GetLastError() == ERROR_SERVICE_EXISTS) {
                OutputDebugString(TEXT("GetLastError() == ERROR_SERVICE_EXISTS"));

                hExService = OpenService(hManager, lpServiceName, DELETE);
                if (hExService) {
                    OutputDebugString(TEXT("hExService"));

                    DeleteService(hExService);
                    CloseServiceHandle(hExService);
                    Sleep(1000);
                }

                if (++retryCount < 2)
                    continue;

            }
            break;
        }

        if (hService) {
            bResult = TRUE;
            OutputDebugString(TEXT("Service installed"));
            CloseServiceHandle(hService);
        }
        CloseServiceHandle(hManager);
    }
    return bResult;
}

/*
* SetParameter
*
* Purpose:
*
* Set parameter to the service parameters registry key.
*
*/
VOID SetParameter(
    _In_ HKEY hKey,
    _In_ LPCTSTR lpCommandLine,
    _In_ LPCTSTR lpParamName,
    _In_ DWORD ParamIndex
)
{
    ULONG paramLength, cbData;
    TCHAR szCommandLine[MAX_PATH * 4];

    if (GetCommandLineParam(lpCommandLine, ParamIndex,
        szCommandLine, MAX_PATH, &paramLength))
    {
        if (paramLength) {

            cbData = (_strlen(szCommandLine) + 1) * sizeof(TCHAR);

            RegSetValueEx(hKey,
                lpParamName,
                0,
                REG_SZ,
                (BYTE*)szCommandLine,
                cbData);

        }
    }
}

/*
* main
*
* Purpose:
*
* Installer application entry point.
*
*/
void main()
{
    TCHAR szKey[MAX_PATH];
    TCHAR szServiceExe[MAX_PATH * 2];
    DWORD cch;
    HKEY hKey;

    LPTSTR lpCommandLine = GetCommandLine();

    cch = GetCurrentDirectory(MAX_PATH, szServiceExe);
    if ((cch != 0) && (cch < MAX_PATH)) {

        _strcat(szServiceExe, TEXT("\\srvany2.exe"));

        if (InstallService(TEXT("srvany2"), szServiceExe)) {

            _strcpy(szKey, TEXT("SYSTEM\\CurrentControlSet\\Services\\srvany2\\Parameters\\"));

            if (ERROR_SUCCESS == RegCreateKeyEx(HKEY_LOCAL_MACHINE, szKey, 0, NULL,
                REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL))
            {
                SetParameter(hKey, lpCommandLine, TEXT("ApplicationName"), 1);
                SetParameter(hKey, lpCommandLine, TEXT("CommandLine"), 2);
                SetParameter(hKey, lpCommandLine, TEXT("CurrentDirectory"), 3);
                RegCloseKey(hKey);
            }
            else {
                MessageBox(0, TEXT("Could not create parameters key"), NULL, 0);
            }
        }
        else {
            MessageBox(0, TEXT("Could not install srvany2 service"), NULL, 0);
        }
    }
    ExitProcess(0);
}

#else 

/*
* main
*
* Purpose:
*
* Service entry point.
*
*/
void main()
{
    DWORD returnCode = 0;

    SERVICE_TABLE_ENTRY ServiceTable[] =
    {
        { SVC_NAME, (LPSERVICE_MAIN_FUNCTION)ServiceMain },
        { NULL, NULL }
    };

    OutputDebugString(TEXT("srvany2"));

    if (StartServiceCtrlDispatcher(ServiceTable) == FALSE) {
        OutputDebugString(TEXT("StartServiceCtrlDispatcher failed"));
        returnCode = GetLastError();
    }
    ExitProcess(returnCode);
}
#endif
