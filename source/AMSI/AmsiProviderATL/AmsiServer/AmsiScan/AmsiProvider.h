// AmsiProvider.h : Declaration of the CAmsiProvider

#pragma once
#include "resource.h"       // main symbols



#include "AmsiScan_i.h"
#include <amsi.h>


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CAmsiProvider

class ATL_NO_VTABLE CAmsiProvider :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAmsiProvider, &CLSID_AmsiProvider>,
    public IAntimalwareProvider
{
public:
	CAmsiProvider()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_AMSIPROVIDER)


BEGIN_COM_MAP(CAmsiProvider)
    COM_INTERFACE_ENTRY(IAntimalwareProvider)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

    HRESULT STDMETHODCALLTYPE Scan(
        _In_ IAmsiStream *stream,
        _Out_ AMSI_RESULT *result);

    void STDMETHODCALLTYPE CloseSession(
        _In_ ULONGLONG session);

    HRESULT STDMETHODCALLTYPE DisplayName(
        _Outptr_ LPWSTR *displayName);

};

OBJECT_ENTRY_AUTO(__uuidof(AmsiProvider), CAmsiProvider)
