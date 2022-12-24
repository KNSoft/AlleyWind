#include "AlleyWind.h"

KNS_INFO stKNSInfo = {
    KNS_NAME,
    TRUE,
    { 1, 1, 0, 21224, KNS_VERSION_GA },
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

DWORD Main()
{
    NTSTATUS Status;

    /* Initialize */
    ULONG_PTR ulpGdipToken;
    if (!GDIP_Startup(&ulpGdipToken)) {
        Status = STATUS_INSUFFICIENT_RESOURCES;
        goto Exit_0;
    }

    HRESULT hr;
    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED | COINIT_DISABLE_OLE1DDE);
    if (FAILED(hr)) {
        Status = hr;
        goto Exit_1;
    }

    /* Run */
    Status = (NTSTATUS)KNS_Startup(&stKNSInfo);

    /* Exit */
    CoUninitialize();
Exit_1:
    GDIP_Shutdown(ulpGdipToken);
Exit_0:
    return NtTerminateProcess(CURRENT_PROCESS_HANDLE, Status);
}