#include "AlleyWind.inl"

int
WINAPI
WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{
    HRESULT hr, hrCom;

    /* COM initialization is optional currently */
    hrCom = CoInitializeEx(NULL, COINIT_MULTITHREADED);

    hr = AW_OpenMainDialogBox();
    if (FAILED(hr))
    {
        Err_HrMessageBox(NULL, _A2W(KNS_APP_NAME), hr);
    }

    if (SUCCEEDED(hrCom))
    {
        CoUninitialize();
    }
    
    return (int)hr;
}
