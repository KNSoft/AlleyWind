#include "../../AlleyWind.inl"

static
AW_I18N_DLGITEM g_astI18NItems[] = {
    { IDC_PROP_REFRESH, Precomp4C_I18N_All_Refresh },
};

/* TODO */
static
INT_PTR
CALLBACK
EmptyPspProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

static
AW_I18N_PROPSHEET_PAGE g_astPspSource[] = {
    { Precomp4C_I18N_All_General, MAKEINTRESOURCEW(IDD_PROP_GENERAL), EmptyPspProc, 0 },
    { Precomp4C_I18N_All_Resource, MAKEINTRESOURCEW(IDD_PROP_GENERAL), EmptyPspProc, 0 },
    { Precomp4C_I18N_All_Relationship, MAKEINTRESOURCEW(IDD_PROP_GENERAL), EmptyPspProc, 0 },
    { Precomp4C_I18N_All_Class, MAKEINTRESOURCEW(IDD_PROP_GENERAL), EmptyPspProc, 0 },
    { Precomp4C_I18N_All_Operation, MAKEINTRESOURCEW(IDD_PROP_GENERAL), EmptyPspProc, 0 },
};

static
INT_PTR
CALLBACK
PropDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    UI_DPIScaleDlgProc(hDlg, uMsg, wParam, lParam);
    UI_PropSheetWndProc(hDlg, uMsg, wParam, lParam, IDC_PROP_TAB);
    if (uMsg == WM_INITDIALOG)
    {
        HWND RefWindow;
        WCHAR szTitle[MAX_WNDCAPTION_CCH];
        ULONG Cch;
        UI_PROPSHEET_PAGE Psp[ARRAYSIZE(g_astPspSource)];

        RefWindow = (HWND)lParam;

        /* Set title */
        Cch = Str_PrintfW(szTitle, AW_GetString(WindowPropertiesFormat), UI_TruncateHandle32(RefWindow));
        AW_PostFixTitleText(szTitle + Cch, ARRAYSIZE(szTitle) - Cch);
        UI_SetWindowTextW(hDlg, szTitle);

        /* Create property sheet */
        AW_InitDlgItemI18N(hDlg, g_astI18NItems);
        AW_InitPropSheetPageI18NEx(hDlg,
                                   g_astPspSource,
                                   Psp,
                                   ARRAYSIZE(g_astPspSource));
        UI_InitPropSheet(hDlg, IDC_PROP_TAB, Psp);
    } else if (uMsg == WM_COMMAND)
    {
        if (wParam == MAKEWPARAM(IDC_PROP_REFRESH, 0))
        {
            // TODO
        }
    } else if (uMsg == WM_CLOSE)
    {
        SetWindowLongPtrW(hDlg, DWLP_MSGRESULT, 0);
        DestroyWindow(hDlg);
    } else if (uMsg == WM_DESTROY)
    {
        PostQuitMessage(S_OK);
    }
    return 0;
}

HRESULT
AW_OpenPropDialogBoxSync(
    _In_ HWND RefWindow)
{
    HRESULT hr;

    hr = AW_CreateDialog(NULL, NULL, MAKEINTRESOURCEW(IDD_PROP), PropDlgProc, (LPARAM)RefWindow);
    if (SUCCEEDED(hr))
    {
        hr = KNS_DlgMessageLoop(NULL);
    }

    return hr;
}

static
_Function_class_(USER_THREAD_START_ROUTINE)
NTSTATUS
NTAPI
OpenPropDialogBoxThread(
    _In_ PVOID ThreadParameter)
{
    return Err_HrToNtStatus(AW_OpenPropDialogBoxSync((HWND)ThreadParameter));
}

NTSTATUS
AW_OpenPropDialogBoxAsync(
    _In_ HWND RefWindow)
{
    return PS_CreateThread(NtCurrentProcess(), FALSE, OpenPropDialogBoxThread, (PVOID)RefWindow, NULL, NULL);
}
