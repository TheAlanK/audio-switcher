#include <Windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <iostream>
#include <atlbase.h>
#include <functiondiscoverykeys_devpkey.h>
#include <vector>
#include <string>
#include "PolicyConfig.h"

int main() {
    HRESULT hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        std::cerr << "Failed to initialize COM" << std::endl;
        return -1;
    }

    CComPtr<IMMDeviceEnumerator> pDeviceEnumerator;
    hr = pDeviceEnumerator.CoCreateInstance(__uuidof(MMDeviceEnumerator));
    if (FAILED(hr)) {
        std::cerr << "Failed to create device enumerator" << std::endl;
        CoUninitialize();
        return -1;
    }

    CComPtr<IMMDeviceCollection> pDeviceCollection;
    hr = pDeviceEnumerator->EnumAudioEndpoints(eRender, DEVICE_STATE_ACTIVE, &pDeviceCollection);
    if (FAILED(hr)) {
        std::cerr << "Failed to enumerate audio endpoints" << std::endl;
        CoUninitialize();
        return -1;
    }

    const std::wstring allowedDeviceId1 = L"{0.0.0.00000000}.{25dbd0c9-c3b7-4d72-b671-18f635e61e81}";
    const std::wstring allowedDeviceId2 = L"{0.0.0.00000000}.{4d3b173f-0f8d-4fa5-8e4a-56ab517ae172}";

    CComPtr<IMMDevice> pDefaultDevice;
    hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDefaultDevice);
    if (FAILED(hr)) {
        std::cerr << "Failed to get the default audio endpoint" << std::endl;
        CoUninitialize();
        return -1;
    }

    LPWSTR wstrDefaultID = NULL;
    pDefaultDevice->GetId(&wstrDefaultID);
    CComHeapPtr<WCHAR> sptrDefaultID(wstrDefaultID);

    std::wstring currentDefaultDeviceId(sptrDefaultID);

    std::wstring targetDeviceId;
    if (currentDefaultDeviceId == allowedDeviceId1) {
        targetDeviceId = allowedDeviceId2;
    }
    else if (currentDefaultDeviceId == allowedDeviceId2) {
        targetDeviceId = allowedDeviceId1;
    }
    else {
        std::wcerr << L"None of the specified devices is currently the default." << std::endl;
        CoUninitialize();
        return -1;
    }

    CComPtr<IPolicyConfig> pPolicyConfig;
    hr = pPolicyConfig.CoCreateInstance(__uuidof(CPolicyConfigClient));
    if (SUCCEEDED(hr)) {
        hr = pPolicyConfig->SetDefaultEndpoint(targetDeviceId.c_str(), eConsole);
        if (SUCCEEDED(hr)) {
            std::wcout << L"Default audio endpoint set successfully to: " << targetDeviceId << std::endl;
        }
        else {
            std::wcerr << L"Failed to set default audio endpoint. HRESULT: " << hr << std::endl;
        }
    }
    else {
        std::wcerr << L"Failed to create IPolicyConfig instance. HRESULT: " << hr << std::endl;
    }

    CoUninitialize();
    return 0;
}
