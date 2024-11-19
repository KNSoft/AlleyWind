#include "AlleyWind.inl"

KNS_APPINFO g_KNSAppInfo = {
    L"AlleyWind",
    L"https://github.com/KNSoft/AlleyWind"
};

int
WINAPI
wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd)
{
    HRESULT hr, hrCom;

    /* COM initialization is optional currently */
    hrCom = CoInitializeEx(NULL, COINIT_MULTITHREADED);

    hr = AW_OpenMainDialogBox();
    if (FAILED(hr))
    {
        KNS_HrMessageBox(NULL, hr);
    }

    if (SUCCEEDED(hrCom))
    {
        CoUninitialize();
    }

    return (int)hr;
}
