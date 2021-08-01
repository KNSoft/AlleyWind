#include "AlleyWind.h"

KNS_INFO stKNSInfo = {
    KNS_NAME,
    TRUE,
    { AW_VER_MAJOR, AW_VER_MINOR, AW_VER_REVISION, AW_VER_BUILD, AW_VER_TYPE },
    {
        RGB(255, 140, 0),
        IDI_APP,
        IDD_MAIN,
        MainDlgProc,
        IDC_MAINBANNER,
        0,
        0,
        FALSE
    },
    { NAC_I18N_Lang_Table, ARRAYSIZE(NAC_I18N_Lang_Table), NAC_I18N_ITEM_COUNT },
    {
        TEXT("https://knsoft.org/Products/AlleyWind/"),
        TEXT("https://knsoft.org/Products/AlleyWind/"),
        TEXT("https://knsoft.org/Products/AlleyWind/Download/Update.xml"),
        NULL
    }
};

DWORD Main() {
    NTSTATUS    lStatus;
    HRESULT     hr;
    AWSettings_Init();
    Proc_EnablePrivilege(LSE_DEBUG_NAME);
    hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (hr == S_OK || hr == S_FALSE || hr == RPC_E_CHANGED_MODE) {
        lStatus = (NTSTATUS)KNS_Startup(&stKNSInfo);
        CoUninitialize();
    } else
        lStatus = hr;
    return NtTerminateProcess(CURRENT_PROCESS_HANDLE, lStatus);
}