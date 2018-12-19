#include "global.h"
#include "classfactory.h"

VOID ShowCode(HRESULT Code)
{
    WCHAR szBuffer[200];

    _strcpy(szBuffer, L"Code = 0x");
    ultohex((ULONG)Code, _strend(szBuffer));
    _strcat(szBuffer, L"\r\n");
    OutputDebugString(szBuffer);
}

STDAPI_(LONG) DllAddRef()
{
    return InterlockedIncrement(&g_cRefDll);
}

STDAPI_(LONG) DllRelease()
{
    return InterlockedDecrement(&g_cRefDll);
}

//
// Class factory implementation.
//

STDMETHODIMP_(ULONG) CClassFactory_AddRef(
    _In_ IClassFactory *pcf
)
{
    return DllAddRef();
}

STDMETHODIMP_(ULONG) CClassFactory_Release(
    _In_ IClassFactory *pcf
)
{
    return DllRelease();
}

STDMETHODIMP CClassFactory_CreateInstance(
    _In_ IClassFactory *pcf,
    _In_ IUnknown *punkOuter,
    _In_ REFIID riid,
    _COM_Outptr_ void **ppvObject
)
{
    CClassFactory *This = IToClass(CClassFactory, cf, pcf);

    //
    // Run delegated CreateInstance routine.
    //
    return This->lpfnCreateInstance(punkOuter, riid, ppvObject);
}

STDMETHODIMP CClassFactory_LockServer(
    _In_ IClassFactory *pcf,
    _In_ BOOL fLock
)
{
    if (fLock)
        DllAddRef();
    else
        DllRelease();
    return S_OK;
}

STDMETHODIMP CClassFactory_QueryInterface(
    _In_ IClassFactory *pcf,
    _In_ REFIID riid,
    _COM_Outptr_ void **ppvObj
)
{
    if (IsEqualIID(riid, &IID_IClassFactory) || IsEqualIID(riid, &IID_IUnknown))
    {
        *ppvObj = (void *)pcf;
    }
    else
    {
        *ppvObj = NULL;
        return E_NOINTERFACE;
    }
    DllAddRef();
    return NOERROR;
}

const IClassFactoryVtbl g_ClassFactorylpVtbl = {
    CClassFactory_QueryInterface,
    CClassFactory_AddRef,
    CClassFactory_Release,
    CClassFactory_CreateInstance,
    CClassFactory_LockServer
};

//
// AMSI provider implementation.
//

typedef struct _CClassAmsiProvider {
    IAntimalwareProvider ap;
    UINT cRef;
} CClassAmsiProvider, *PCClassAmsiProvider;


HRESULT STDMETHODCALLTYPE CAmsiProvider_QueryInterface(
    _In_ IAntimalwareProvider *AmProvider,
    _In_ REFIID riid,
    _COM_Outptr_ void **ppv)
{
    CClassAmsiProvider *This = IToClass(CClassAmsiProvider, ap, AmProvider);

    OutputDebugString(L"AmsiProvider_QueryInterface\r\n");

    if (IsEqualIID(riid, &IID_IUnknown) ||
        IsEqualIID(riid, &IID_AntimalwareProvider))
    {
        *ppv = &This->ap;
    }
    else {
        *ppv = NULL;
        return E_NOINTERFACE;
    }

    This->cRef++;
    return S_OK;
}

ULONG STDMETHODCALLTYPE CAmsiProvider_AddRef(
    _In_ IAntimalwareProvider *AmProvider
)
{
    CClassAmsiProvider *This = IToClass(CClassAmsiProvider, ap, AmProvider);

    OutputDebugString(L"AmsiProvider_AddRef\r\n");

    This->cRef++;
    return This->cRef;
}

ULONG STDMETHODCALLTYPE CAmsiProvider_Release(
    _In_ IAntimalwareProvider *AmProvider
)
{
    CClassAmsiProvider *This = IToClass(CClassAmsiProvider, ap, AmProvider);

    OutputDebugString(L"AmsiProvider_Release\r\n");

    This->cRef--;
    if (This->cRef > 0)
        return This->cRef;

    LocalFree((HLOCAL)This);
    return 0;
}

ULONG64 AmsiGetAttributeAsUlong64(
    _In_ IAmsiStream *stream,
    _In_ AMSI_ATTRIBUTE attribute
)
{
    ULONG actualSize = 0;
    ULONG64 result = 0;

    HRESULT hr;

    hr = stream->lpVtbl->GetAttribute(stream, attribute,
        sizeof(ULONG64), (UCHAR*)&result, &actualSize);

    if (!SUCCEEDED(hr) || (actualSize != sizeof(ULONG64)))
        return 0;

    return result;
}

PVOID AmsiGetAttributeAsPointer(
    _In_ IAmsiStream *stream,
    _In_ AMSI_ATTRIBUTE attribute
)
{
    ULONG actualSize = 0;
    PVOID result = 0;

    HRESULT hr;

    hr = stream->lpVtbl->GetAttribute(stream, attribute,
        sizeof(PVOID), (UCHAR*)&result, &actualSize);

    if (!SUCCEEDED(hr) || (actualSize != sizeof(PVOID)))
        return 0;

    return result;
}

LPWSTR AmsiGetAttributeAsString(
    _In_ IAmsiStream *stream,
    _In_ AMSI_ATTRIBUTE attribute
)
{
    LPWSTR result = NULL;
    ULONG allocSize;
    ULONG actualSize;

    HRESULT hr;

    hr = stream->lpVtbl->GetAttribute(stream, attribute, 0, NULL, &allocSize);

    if (hr == E_NOT_SUFFICIENT_BUFFER) {

        result = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, allocSize);
        if (result) {

            hr = stream->lpVtbl->GetAttribute(stream, attribute, allocSize,
                (UCHAR*)result, &actualSize);

            if (SUCCEEDED(hr) && (actualSize <= allocSize)) {
                return result;
            }
            else {
                OutputDebugString(L"AmsiGetStringAttribute unexpected result 3\r\n");
            }
        }
        else {
            OutputDebugString(L"AmsiGetStringAttribute unexpected result 2\r\n");
        }
    }
    else {
        OutputDebugString(L"AmsiGetStringAttribute unexpected result 1\r\n");
    }
    return result;
}

BYTE CalculateBufferXor(
    _In_ LPCBYTE buffer,
    _In_ ULONGLONG size
)
{
    ULONGLONG i;
    BYTE value = 0;

    for (i = 0; i < size; i++)
        value ^= buffer[i];

    return value;
}

HRESULT STDMETHODCALLTYPE CAmsiProviderScan(
    _In_ IAntimalwareProvider *This,
    _In_ IAmsiStream *stream,
    _Out_ AMSI_RESULT *result
)
{
    LPWSTR AppName;
    LPWSTR ContentName;
    ULONG64 ContentSize = 0;
    PVOID ContentAddress = NULL;

    BYTE cumulativeXor = 0;
    BYTE chunk[1024];
    ULONG readSize;

    HRESULT hr;

    ULONG64 position;

    WCHAR szOutput[200];

    OutputDebugString(L"AmsiProviderScan\r\n");

    //
    // AMSI_ATTRIBUTE_APP_NAME
    //
    AppName = AmsiGetAttributeAsString(stream, AMSI_ATTRIBUTE_APP_NAME);
    if (AppName) {
        OutputDebugString(L"AMSI_ATTRIBUTE_APP_NAME\r\n");
        OutputDebugString(AppName);
        OutputDebugString(L"\r\n");
        HeapFree(GetProcessHeap(), 0, AppName);
    }

    //
    // AMSI_ATTRIBUTE_CONTENT_NAME
    //
    ContentName = AmsiGetAttributeAsString(stream, AMSI_ATTRIBUTE_CONTENT_NAME);
    if (ContentName) {
        OutputDebugString(L"AMSI_ATTRIBUTE_CONTENT_NAME\r\n");
        OutputDebugString(ContentName);
        OutputDebugString(L"\r\n");
        HeapFree(GetProcessHeap(), 0, ContentName);
    }

    //
    // AMSI_ATTRIBUTE_CONTENT_SIZE
    //
    ContentSize = AmsiGetAttributeAsUlong64(stream, AMSI_ATTRIBUTE_CONTENT_SIZE);

    _strcpy(szOutput, L"AMSI_ATTRIBUTE_CONTENT_SIZE\r\n0x");
    u64tohex(ContentSize, _strend(szOutput));
    _strcat(szOutput, L"\r\n");
    OutputDebugString(szOutput);

    //
    // AMSI_ATTRIBUTE_CONTENT_ADDRESS
    //
    ContentAddress = AmsiGetAttributeAsPointer(stream, AMSI_ATTRIBUTE_CONTENT_ADDRESS);

    _strcpy(szOutput, L"AMSI_ATTRIBUTE_CONTENT_ADDRESS\r\n0x");
    u64tohex((ULONG64)ContentAddress, _strend(szOutput));
    _strcat(szOutput, L"\r\n");
    OutputDebugString(szOutput);

    //
    // Provided a stream. Test read.
    //
    if (ContentAddress == 0) {

        for (position = 0; position < ContentSize; position += readSize)
        {
            hr = stream->lpVtbl->Read(stream, position, sizeof(chunk), chunk, &readSize);
            if (SUCCEEDED(hr))
            {
                cumulativeXor ^= CalculateBufferXor(chunk, readSize);

                RtlSecureZeroMemory(&szOutput, sizeof(szOutput));
                szOutput[0] = L'0';
                szOutput[1] = L'x';
                szOutput[2] = 0;
                ultohex((ULONG)cumulativeXor, &szOutput[2]);
                _strcat(szOutput, L"\r\n");
                OutputDebugString(szOutput);

            }
            else {
                OutputDebugString(L"Stream read error\r\n");
                ShowCode(hr);
                break;
            }
        }
    }

    *result = AMSI_RESULT_NOT_DETECTED;
    return S_OK;
}

void STDMETHODCALLTYPE CAmsiProviderCloseSession(
    _In_ IAntimalwareProvider *This,
    _In_ ULONGLONG session
)
{
    OutputDebugString(L"AmsiProviderCloseSession\r\n");
}

HRESULT STDMETHODCALLTYPE CAmsiProviderDisplayName(
    _In_ IAntimalwareProvider *This,
    _Out_ LPWSTR *displayName
)
{
    OutputDebugString(L"AmsiProviderDisplayName\r\n");
    *displayName = L"Custom AMSI Provider";
    return S_OK;
}

STDAPI CAmsiProvider_CreateInstance(
    _In_ IUnknown *punkOuter,
    _In_ REFIID riid,
    _COM_Outptr_ void **ppv);

IAntimalwareProviderVtbl c_AntimalwareProviderVtbl =
{
    CAmsiProvider_QueryInterface,
    CAmsiProvider_AddRef,
    CAmsiProvider_Release,
    CAmsiProviderScan,
    CAmsiProviderCloseSession,
    CAmsiProviderDisplayName
};

STDAPI CAmsiProvider_CreateInstance(
    _In_ IUnknown *punkOuter,
    _In_ REFIID riid,
    _COM_Outptr_ void **ppv
)
{
    CClassAmsiProvider *This;
    HRESULT hr;

    OutputDebugString(L"AmsiProvider_CreateInstance\r\n");

    *ppv = NULL;

    if (punkOuter) {
        return CLASS_E_NOAGGREGATION;
    }

    This = (CClassAmsiProvider*)LocalAlloc(LPTR, sizeof(CClassAmsiProvider));
    if (This) {
        This->cRef = 1;
        This->ap.lpVtbl = &c_AntimalwareProviderVtbl;

        DllAddRef();

        hr = CAmsiProvider_QueryInterface(&This->ap, riid, ppv);
        CAmsiProvider_Release(&This->ap);
    }
    else
        hr = E_OUTOFMEMORY;

    return hr;
}

//
// Our class factory support only 1 type.
//
const CClassFactory g_clsmap[] = {
    &g_ClassFactorylpVtbl, &CLSID_AmsiProvider, CAmsiProvider_CreateInstance,
    NULL, NULL, NULL
};
