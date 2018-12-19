// AmsiProvider.cpp : Implementation of CAmsiProvider

#include "stdafx.h"
#include "AmsiProvider.h"

template<typename TypeName>
class MemoryBuffer
{
private:
    TypeName* Buffer = nullptr;
public:
    MemoryBuffer() {}
    MemoryBuffer(const MemoryBuffer& other) = delete;
    MemoryBuffer(MemoryBuffer&& other) : Buffer(other.Buffer) { other.Buffer = nullptr; }
    MemoryBuffer& operator=(const MemoryBuffer& other) = delete;
    MemoryBuffer& operator=(MemoryBuffer&& other) {
        auto tempBuffer = Buffer; Buffer = other.Buffer; other.Buffer = tempBuffer;
        return *this;
    }

    ~MemoryBuffer() { if (Buffer) HeapFree(GetProcessHeap(), 0, Buffer); }
    HRESULT AllocBuffer(size_t size)
    {
        Buffer = reinterpret_cast<TypeName*>(HeapAlloc(GetProcessHeap(), 0, size));
        return Buffer ? S_OK : E_OUTOFMEMORY;
    }

    TypeName* Get() { return Buffer; }
    operator bool() { return Buffer != nullptr; }
};

MemoryBuffer<wchar_t> AmsiGetStringAttribute(
    _In_ IAmsiStream* stream,
    _In_ AMSI_ATTRIBUTE attribute)
{
    MemoryBuffer<wchar_t> result;
    ULONG allocSize;
    ULONG actualSize;

    if (stream->GetAttribute(attribute, 0, nullptr, &allocSize) == E_NOT_SUFFICIENT_BUFFER &&
        SUCCEEDED(result.AllocBuffer(allocSize)) &&
        SUCCEEDED(stream->GetAttribute(attribute, allocSize, reinterpret_cast<PBYTE>(result.Get()), &actualSize)) &&
        actualSize <= allocSize)
    {
        return result;
    }
    return MemoryBuffer<wchar_t>();
}

template<typename TypeName>
TypeName AmsiGetFixedSizeAttribute(_In_ IAmsiStream* stream, _In_ AMSI_ATTRIBUTE attribute)
{
    TypeName result;

    ULONG actualSize;
    if (SUCCEEDED(stream->GetAttribute(attribute, sizeof(TypeName), reinterpret_cast<PBYTE>(&result), &actualSize)) &&
        actualSize == sizeof(TypeName))
    {
        return result;
    }
    return TypeName();
}


// CAmsiProvider

HRESULT STDMETHODCALLTYPE CAmsiProvider::Scan(
    _In_ IAmsiStream *stream,
    _Out_ AMSI_RESULT *result)
{
    OutputDebugString(L"AmsiProvider->Scan\r\n");

    auto AppName = AmsiGetStringAttribute(stream, AMSI_ATTRIBUTE_APP_NAME);

    if (AppName) {

        OutputDebugString(L"AMSI_ATTRIBUTE_APP_NAME\r\n");
        OutputDebugString(AppName.Get());
        OutputDebugString(L"\r\n");

    }

    auto ContentName = AmsiGetStringAttribute(stream, AMSI_ATTRIBUTE_CONTENT_NAME);

    if (ContentName) {

        OutputDebugString(L"AMSI_ATTRIBUTE_CONTENT_NAME\r\n");
        OutputDebugString(ContentName.Get());
        OutputDebugString(L"\r\n");

    }

    *result = AMSI_RESULT_NOT_DETECTED;
    return S_OK;
}

void STDMETHODCALLTYPE CAmsiProvider::CloseSession(
    _In_ ULONGLONG session)
{
    OutputDebugString(L"AmsiProvider->CloseSession\r\n");
}

HRESULT STDMETHODCALLTYPE CAmsiProvider::DisplayName(
    _Outptr_ LPWSTR *displayName)
{
    OutputDebugString(L"AmsiProvider->DisplayName\r\n");

    *displayName = const_cast<LPWSTR>(L"Custom AMSI Provider");
    return S_OK;
}
