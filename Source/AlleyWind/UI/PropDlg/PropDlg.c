#include "../../AlleyWind.inl"

static
AW_I18N_DLGITEM g_astI18NItems[] = {
    { IDC_PROP_REFRESH, Precomp4C_I18N_All_Refresh },
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
        AW_PostFixTitleText(szTitle + Cch, ARRAYSIZE(szTitle) - Cch);
        UI_SetWindowTextW(hDlg, szTitle);

        /* Create property sheet */
        AW_CreatePropSheetPages(hDlg,
                                g_ResPropDlgPages,
                                Psp,
                                ARRAYSIZE(g_ResPropDlgPages),
                                lParam);
        UI_InitPropSheet(hDlg, IDC_PROP_TAB, Psp);

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
    _In_ HWND RefWindow)
{
    HRESULT hr;
    PAW_WINDOW_PROP Prop;
    W32ERROR Error;

    if (!Mem_AllocPtr(Prop))
    {
        return E_OUTOFMEMORY;
    }
    Error = AW_GetWindowProp(RefWindow, Prop);
    if (Error != ERROR_SUCCESS)
    {
        hr = HRESULT_FROM_WIN32(Error);
        goto _Exit;
    }

    hr = KNS_OpenModelDialogBox((HINSTANCE)&__ImageBase, NULL, g_ResPropDlgTemplate, PropDlgProc, (LPARAM)Prop);

_Exit:
    Mem_Free(Prop);
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
