#include "global.h"
#include "classfactory.h"

//
// Globals
//
HMODULE g_currentModule;
LONG g_cRefDll = 0; //reference count

HRESULT SetKeyStringValue(
    _In_ HKEY key,
    _In_opt_ PCWSTR subkey,
    _In_opt_ PCWSTR valueName,
    _In_ PCWSTR stringValue)
{
    LONG status = RegSetKeyValue(key, subkey, valueName, REG_SZ, stringValue, 
        (DWORD)(_strlen(stringValue) + 1) * sizeof(wchar_t));
    
    return HRESULT_FROM_WIN32(status);
}

_Use_decl_annotations_
STDAPI DllRegisterServer()
{
    WCHAR modulePath[MAX_PATH];
    WCHAR clsidString[40];
    WCHAR keyPath[200];

    HRESULT hr;

    if (GetModuleFileName(g_currentModule, modulePath, ARRAYSIZE(modulePath)) >= ARRAYSIZE(modulePath))
    {
        return E_UNEXPECTED;
    }

    if (StringFromGUID2(&CLSID_AmsiProvider, clsidString, ARRAYSIZE(clsidString)) == 0)
    {
        return E_UNEXPECTED;
    }

    _strcpy(keyPath, L"Software\\Classes\\CLSID\\");
    _strcat(keyPath, clsidString);

    hr = SetKeyStringValue(HKEY_LOCAL_MACHINE, keyPath, NULL, L"FAmsiProvider");
    if (FAILED(hr)) return hr;

    _strcpy(keyPath, L"Software\\Classes\\CLSID\\");
    _strcat(keyPath, clsidString);
    _strcat(keyPath, L"\\InProcServer32");

    hr = SetKeyStringValue(HKEY_LOCAL_MACHINE, keyPath, NULL, modulePath);
    if (FAILED(hr)) return hr;

    hr = SetKeyStringValue(HKEY_LOCAL_MACHINE, keyPath, L"ThreadingModel", L"Both");
    if (FAILED(hr)) return hr;

    _strcpy(keyPath, L"Software\\Microsoft\\AMSI\\Providers\\");
    _strcat(keyPath, clsidString);

    hr = SetKeyStringValue(HKEY_LOCAL_MACHINE, keyPath, NULL, L"FAmsiProvider");
    if (FAILED(hr)) return hr;

    return S_OK;
}

_Use_decl_annotations_
STDAPI DllUnregisterServer()
{
    WCHAR clsidString[40];
    WCHAR keyPath[200];

    LONG status;

    if (StringFromGUID2(&CLSID_AmsiProvider, clsidString, ARRAYSIZE(clsidString)) == 0)
    {
        return E_UNEXPECTED;
    }

    _strcpy(keyPath, L"Software\\Microsoft\\AMSI\\Providers\\");
    _strcat(keyPath, clsidString);

    status = RegDeleteTree(HKEY_LOCAL_MACHINE, keyPath);
    if (status != NO_ERROR && status != ERROR_PATH_NOT_FOUND) return HRESULT_FROM_WIN32(status);

    _strcpy(keyPath, L"Software\\Classes\\CLSID\\");
    _strcat(keyPath, clsidString);

    status = RegDeleteTree(HKEY_LOCAL_MACHINE, keyPath);
    if (status != NO_ERROR && status != ERROR_PATH_NOT_FOUND) return HRESULT_FROM_WIN32(status);

    return S_OK;
}

_Use_decl_annotations_
STDAPI DllCanUnloadNow(void)
{
    return g_cRefDll == 0 ? S_OK : S_FALSE;
}

_Use_decl_annotations_
STDAPI DllGetClassObject(
    _In_ REFCLSID rclsid, 
    _In_ REFIID riid, 
    _Outptr_ LPVOID* ppv
)
{
    const CClassFactory *pcls;

    //
    // Does our class factory can handle this interface?
    //
    if (IsEqualIID(riid, &IID_IClassFactory) || IsEqualIID(riid, &IID_IUnknown))
    {
        for (pcls = g_clsmap; pcls->pclsid; pcls++)
        {
            if (IsEqualIID(rclsid, pcls->pclsid))
            {
                *ppv = (void *)&(pcls->cf);
                DllAddRef();                    
                return NOERROR;
            }
        }
    }
    *ppv = NULL;
    return CLASS_E_CLASSNOTAVAILABLE;
}

#ifndef _DEBUG

BOOL WINAPI DllMain(
    _In_ HINSTANCE hinstDLL,
    _In_ DWORD fdwReason,
    _In_ LPVOID lpvReserved
)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        g_currentModule = hinstDLL;
        DisableThreadLibraryCalls(hinstDLL);
        break;

    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}

#else

void main()
{
    ExitProcess(0);
}

#endif