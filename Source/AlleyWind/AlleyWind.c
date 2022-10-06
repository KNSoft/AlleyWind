#include "AlleyWind.h"

KNS_INFO stKNSInfo = {
    KNS_NAME,
    TRUE,
    { 1, 1, 0, 21006, KNS_VERSION_RC },
    {
        RGB(255, 140, 0),
        IDI_APP,
        IDD_MAIN,
        IDR_MAIN,
        MainDlgProc,
        IDC_MAINBANNER,
        0,
        0,
        FALSE
    },
    { Precomp4C_I18N_Lang_Table, ARRAYSIZE(Precomp4C_I18N_Lang_Table), Precomp4C_I18N_ITEM_COUNT },
    {
        TEXT("https://github.com/KNSoft/AlleyWind/"),
        TEXT("https://knsoft.org/Products/AlleyWind/"),
        TEXT("https://knsoft.org/Products/AlleyWind/Download/Update.xml"),
        NULL
    }
};

DWORD Main() {
    NTSTATUS    Status;
    HRESULT     hr;
    AWSettings_Init();
    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr)) {
        Status = (NTSTATUS)KNS_Startup(&stKNSInfo);
        CoUninitialize();
    } else {
        Status = hr;
    }
    return NtTerminateProcess(CURRENT_PROCESS_HANDLE, Status);
}