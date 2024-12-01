#include "../../AlleyWind.inl"

static
AW_I18N_DLGITEM g_astI18NItems[] = {
    { IDC_PROP_CAPTION_TEXT, Precomp4C_I18N_All_Caption },
    { IDC_PROP_HANDLE_TEXT, Precomp4C_I18N_All_Handle },
    { IDC_PROP_CTLID_TEXT, Precomp4C_I18N_All_ControlId },
    { IDC_PROP_WNDPROC_TEXT, Precomp4C_I18N_All_WindowProcedure },
};

static
VOID
UpdatePropInfo(
    _In_ HWND Dialog,
    _In_ HWND RefWindow)
{
    WCHAR szBuffer[MAX_WNDCAPTION_CCH];
    HWND hCtl;
    DWORD_PTR dwpResult;
    INT iCtrlId;
    PVOID pWndProc;

    /* Caption */
    if (AW_SendMsgTO(RefWindow, WM_GETTEXT, ARRAYSIZE(szBuffer), (LPARAM)szBuffer, &dwpResult) != 0 &&
        dwpResult < ARRAYSIZE(szBuffer))
    {
        szBuffer[dwpResult] = UNICODE_NULL;
    } else
    {
        szBuffer[0] = UNICODE_NULL;
    }
    UI_SetDlgItemTextW(Dialog, IDC_PROP_CAPTION_EDIT, szBuffer);

    /* Handle */
    hCtl = GetDlgItem(Dialog, IDC_PROP_HANDLE_EDIT);
    Str_PrintfW(szBuffer, L"%08lX", UI_TruncateHandle32(RefWindow));
    UI_SetWindowTextW(hCtl, szBuffer[0] != UNICODE_NULL ? szBuffer : g_NAText);

    /* Control ID */
    hCtl = GetDlgItem(Dialog, IDC_PROP_CTLID_EDIT);
    if (!IsTopLevelWindow(RefWindow))
    {
        iCtrlId = GetDlgCtrlID(RefWindow);
        if (!Str_FromIntW(iCtrlId, szBuffer))
        {
            szBuffer[0] = UNICODE_NULL;
        }
        UI_SetWindowTextW(hCtl, szBuffer);
        if (iCtrlId != 0)
        {
            goto _End_ControlId;
        }
    } else
    {
        UI_SetWindowTextW(hCtl, g_NAText);
    }
    EnableWindow(hCtl, FALSE);
_End_ControlId:

    /* Window Procedure */
    hCtl = GetDlgItem(Dialog, IDC_PROP_WNDPROC_EDIT);
    pWndProc = (PVOID)GetWindowLongPtrW(RefWindow, GWLP_WNDPROC);
    if (pWndProc != NULL)
    {
        Str_PrintfW(szBuffer, L"%p (%ls)", pWndProc, IsWindowUnicode(RefWindow) ? L"Unicode" : L"ANSI");
        UI_SetWindowTextW(hCtl, szBuffer);
    } else
    {
        UI_SetWindowTextW(hCtl, g_NAText);
    }
}

INT_PTR
CALLBACK
GeneralPspProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    UI_DPIScaleDlgProc(hDlg, uMsg, wParam, lParam);
    if (uMsg == WM_INITDIALOG)
    {
        AW_InitDlgItemI18N(hDlg, g_astI18NItems);

        UpdatePropInfo(hDlg, (HWND)lParam);

        return TRUE;
    }
    return FALSE;
}
