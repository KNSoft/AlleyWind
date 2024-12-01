#include "../../AlleyWind.inl"

static
AW_I18N_DLGITEM g_astI18NItems[] = {
    { IDC_PROP_CAPTION_TEXT, Precomp4C_I18N_All_Caption },
    { IDC_PROP_HANDLE_TEXT, Precomp4C_I18N_All_Handle },
    { IDC_PROP_INSTANCE_HANDLE_TEXT, Precomp4C_I18N_All_InstanceHandle },
    { IDC_PROP_SYSCLASS_TEXT, Precomp4C_I18N_All_SystemClass },
    { IDC_PROP_CTLID_TEXT, Precomp4C_I18N_All_ControlId },
    { IDC_PROP_WNDPROC_TEXT, Precomp4C_I18N_All_WindowProcedure },
};

static
VOID
UpdatePropInfo(
    _In_ HWND Dialog,
    _In_ HWND RefWindow)
{
    WCHAR szBuffer[max(MAX_WNDCAPTION_CCH, MAX_CLASSNAME_CCH)], szBuffer2[32];
    HWND hCtl;
    DWORD_PTR dwpResult;
    PCWSTR pszTemp;
    INT iTemp;
    PVOID pTemp;
    ULONG uTemp;
    BOOL bTemp;

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
    Str_PrintfW(szBuffer, L"%08lX", UI_TruncateHandle32(RefWindow));
    UI_SetDlgItemTextW(Dialog, IDC_PROP_HANDLE_EDIT, szBuffer[0] != UNICODE_NULL ? szBuffer : g_NAText);

    /* Instance Handle */
    pTemp = (PVOID)GetWindowLongPtrW(RefWindow, GWLP_HINSTANCE);
    if (pTemp != NULL)
    {
        Str_PrintfW(szBuffer, L"%p", pTemp);
        pszTemp = szBuffer;
    } else
    {
        pszTemp = AW_FormatNAFromLastError(szBuffer, ARRAYSIZE(szBuffer));
    }
    UI_SetDlgItemTextW(Dialog, IDC_PROP_INSTANCE_HANDLE_EDIT, pszTemp);

    /* System Class */
    if (GetClassNameW(RefWindow, szBuffer, ARRAYSIZE(szBuffer)) != 0)
    {
        pszTemp = AW_GetSysClassDisplayName(szBuffer);
        if (pszTemp == NULL)
        {
            pszTemp = g_NAText;
        }
    } else
    {
        pszTemp = AW_FormatNAFromLastError(szBuffer, ARRAYSIZE(szBuffer));
    }
    UI_SetDlgItemTextW(Dialog, IDC_PROP_SYSCLASS_EDIT, pszTemp);

    /* Control ID */
    bTemp = TRUE;
    hCtl = GetDlgItem(Dialog, IDC_PROP_CTLID_EDIT);
    if (IsTopLevelWindow(RefWindow))
    {
        pszTemp = AW_FormatNA(szBuffer, ARRAYSIZE(szBuffer), AW_GetString(TopLevelWindow));
    } else
    {
        iTemp = GetDlgCtrlID(RefWindow);
        if (iTemp == 0)
        {
            pszTemp = AW_FormatNAFromLastError(szBuffer, ARRAYSIZE(szBuffer));
        } else
        {
            pszTemp = Str_FromIntW(iTemp, szBuffer) ? szBuffer : g_NAText;
            bTemp = FALSE;
        }
    }
    UI_SetWindowTextW(hCtl, pszTemp);
    SendMessageW(hCtl, EM_SETREADONLY, bTemp, 0);

    /* Window Procedure */
    pTemp = (PVOID)GetWindowLongPtrW(RefWindow, GWLP_WNDPROC);
    if (pTemp != NULL)
    {
        Str_PrintfW(szBuffer2, L"%p", pTemp);
        pszTemp = szBuffer2;
    } else
    {
        pszTemp = AW_FormatNAFromLastError(szBuffer2, ARRAYSIZE(szBuffer2));
    }
    uTemp = Str_PrintfW(szBuffer, L"%ls (%ls)", pszTemp, IsWindowUnicode(RefWindow) ? L"Unicode" : L"ANSI");
    if (uTemp > 0 && uTemp < ARRAYSIZE(szBuffer))
    {
        pszTemp = szBuffer;
    } else
    {
        pszTemp = g_NAText;
    }
    UI_SetDlgItemTextW(Dialog, IDC_PROP_WNDPROC_EDIT, pszTemp);
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
