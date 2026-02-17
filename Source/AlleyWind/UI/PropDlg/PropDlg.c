#include "../../AlleyWind.inl"

static
AW_I18N_DLGITEM g_astI18NItems[] = {
    { IDC_PROP_REFRESH, Precomp4C_I18N_KNSAW_Refresh },
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
        WCHAR szTitle[MAX_WNDCAPTION_CCH];
        ULONG Cch;
        UI_PROPSHEET_PAGE Psp[ARRAYSIZE(g_ResPropDlgPages)];

        AW_InitDlgItemI18N(hDlg, g_astI18NItems, ARRAYSIZE(g_astI18NItems));

        /* Set title */
        Cch = Str_PrintfW(szTitle,
                          AW_GetString(WindowPropertiesFormat),
                          UI_TruncateHandle32(((PAW_WINDOW_PROP)lParam)->Handle));
        AW_PostfixTitleText(szTitle + Cch, ARRAYSIZE(szTitle) - Cch);
        UI_SetWindowTextW(hDlg, szTitle);

        /* Create property sheet */
        AW_CreatePropSheetPages(hDlg,
                                g_ResPropDlgPages,
                                Psp,
                                ARRAYSIZE(g_ResPropDlgPages),
                                lParam);
        UI_InitPropSheet(hDlg, IDC_PROP_TAB, Psp);

        SetWindowLongPtrW(hDlg, DWLP_USER, lParam);
        return TRUE;
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
    _In_ HWND Window)
{
    PAW_WINDOW_PROP Prop;
    W32ERROR Ret;
    HRESULT hr, hrCom;

    hrCom = CoInitializeEx(NULL, COINIT_MULTITHREADED);

    Ret = AW_GetWindowProp(Window, &Prop);
    if (Ret == ERROR_SUCCESS)
    {
        hr = KNS_OpenModelDialogBox((HINSTANCE)&__ImageBase,
                                    NULL,
                                    g_ResPropDlgTemplate,
                                    PropDlgProc,
                                    (LPARAM)Prop);
        AW_ReleaseWindowProp(Prop);
    } else
    {
        hr = HRESULT_FROM_WIN32(Ret);
    }

    if (SUCCEEDED(hrCom))
    {
        CoUninitialize();
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
    _In_ HWND Window)
{
    return PS_CreateThread(NtCurrentProcess(), FALSE, OpenPropDialogBoxThread, (PVOID)Window, NULL, NULL);
}
