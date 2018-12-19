#include "pch.h"
#include <iostream>
#include <amsi.h>

#pragma comment(lib, "amsi.lib")

int main()
{
    std::cout << "Hello World!\n";

    HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);

    if (!SUCCEEDED(hr)) {
        std::cout << "CoInitializeEx error = " << std::hex << hr << "\n";
        return -1;
    }

    HAMSICONTEXT amsiContext = nullptr;

    hr = AmsiInitialize(L"Amsi Scanner", &amsiContext);
    if (!SUCCEEDED(hr)) {
        std::cout << "AmsiInitialize error = " << std::hex << hr << "\n";
        return -2;
    }

    HAMSISESSION amsiSession = nullptr;
    hr = AmsiOpenSession(amsiContext, &amsiSession);
    if (!SUCCEEDED(hr)) {
        std::cout << "AmsiOpenSession error = " << std::hex << hr << "\n";
        return -2;
    }

    UCHAR ScanBuffer[] = "Scanned buffer";

    AMSI_RESULT ScanResult;
    hr = AmsiScanBuffer(amsiContext, ScanBuffer, sizeof(ScanBuffer), L"ScanContentName", amsiSession, &ScanResult);
    if (!SUCCEEDED(hr)) {
        std::cout << "AmsiScanBuffer error = " << std::hex << hr << "\n";
        return -2;
    }

    if (AmsiResultIsMalware(ScanResult)) {
        std::cout << "Malware detected." << "\n";
    }
    else {
        std::cout << "Not detected." << "\n";
    }

    AmsiCloseSession(amsiContext, amsiSession);
    AmsiUninitialize(amsiContext);
    CoUninitialize();
}

