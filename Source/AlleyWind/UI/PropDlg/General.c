#include "../../AlleyWind.inl"

static
AW_I18N_DLGITEM g_astI18NItems[] = {
    { IDC_PROP_CAPTION_TEXT, Precomp4C_I18N_All_Caption },
    { IDC_PROP_HANDLE_TEXT, Precomp4C_I18N_All_Handle },
    { IDC_PROP_INSTANCE_HANDLE_TEXT, Precomp4C_I18N_All_InstanceHandle },
    { IDC_PROP_SYSCLASS_TEXT, Precomp4C_I18N_All_SystemClass },
    { IDC_PROP_CTLID_TEXT, Precomp4C_I18N_All_ControlId },
    { IDC_PROP_WNDPROC_TEXT, Precomp4C_I18N_All_WindowProcedure },
    { IDC_PROP_STYLE_TEXT, Precomp4C_I18N_All_Style },
    { IDC_PROP_EXSTYLE_TEXT, Precomp4C_I18N_All_ExtendedStyle },
};

static
VOID
UpdateStyleProp(
    _In_ HWND EditControl,
    _In_ ULONG Value,
    _In_ ULONG LastError,
    PWCHAR Buffer,
    _In_ ULONG BufferCch)
{
    PCWSTR psz;

    if (LastError == ERROR_SUCCESS)
    {
        psz = Str_TestCchRet(Str_PrintfExW(Buffer, BufferCch, L"%08lX", Value), BufferCch) ? Buffer : g_NAText;
    } else
    {
        psz = AW_FormatNAFromWin32Error(Buffer, BufferCch, LastError);
    }
    UI_SetWindowTextW(EditControl, psz);
    SendMessageW(EditControl, EM_SETREADONLY, LastError != ERROR_SUCCESS, 0);
}

static
VOID
UpdatePropInfo(
    _In_ HWND Dialog,
    _In_ PAW_WINDOW_PROP Prop)
{
    WCHAR szBuffer[MAX_PATH];
    HWND hCtl;
    PCWSTR pszTemp;
    BOOL bTemp;
    ULONG uTemp, uTemp2;

    /* Caption */
    hCtl = GetDlgItem(Dialog, IDC_PROP_CAPTION_EDIT);
    if (Prop->CaptionValid == ERROR_SUCCESS)
    {
        pszTemp = Prop->Caption;
    } else
    {
        pszTemp = AW_FormatNAFromWin32Error(szBuffer, ARRAYSIZE(szBuffer), Prop->CaptionValid);
    }
    UI_SetWindowTextW(hCtl, pszTemp);
    SendMessageW(hCtl, EM_SETREADONLY, Prop->CaptionValid != ERROR_SUCCESS, 0);

    /* Handle */
    Str_PrintfW(szBuffer, L"%08lX", UI_TruncateHandle32(Prop->Handle));
    UI_SetDlgItemTextW(Dialog, IDC_PROP_HANDLE_EDIT, szBuffer);

    /* Instance Handle */
    if (Prop->InstanceHandleValid == ERROR_SUCCESS)
    {
        Str_PrintfW(szBuffer, L"%p", Prop->InstanceHandle);
        pszTemp = szBuffer;
    } else
    {
        pszTemp = AW_FormatNAFromWin32Error(szBuffer, ARRAYSIZE(szBuffer), Prop->InstanceHandleValid);
    }
    UI_SetDlgItemTextW(Dialog, IDC_PROP_INSTANCE_HANDLE_EDIT, pszTemp);

    /* System Class */
    if (Prop->ClassNameValid == ERROR_SUCCESS)
    {
        pszTemp = AW_GetSysClassDisplayName(Prop->ClassName);
    } else
    {
        pszTemp = AW_FormatNAFromWin32Error(szBuffer, ARRAYSIZE(szBuffer), Prop->ClassNameValid);
    }
    UI_SetDlgItemTextW(Dialog, IDC_PROP_SYSCLASS_EDIT, pszTemp);

    /* Control ID */
    hCtl = GetDlgItem(Dialog, IDC_PROP_CTLID_EDIT);
    bTemp = TRUE;
    if (Prop->IdentifierValid == ERROR_SUCCESS)
    {
        pszTemp = Str_FromIntW(Prop->Identifier, szBuffer) ? szBuffer : NULL;
        bTemp = FALSE;
    } else if (Prop->TopLevelWindow || !(Prop->Style & WS_CHILD))
    {
        pszTemp = AW_FormatNA(szBuffer, ARRAYSIZE(szBuffer), AW_GetString(NonChildWindow));
    } else
    {
        pszTemp = AW_FormatNAFromWin32Error(szBuffer, ARRAYSIZE(szBuffer), Prop->IdentifierValid);
    }
    UI_SetWindowTextW(hCtl, pszTemp);
    SendMessageW(hCtl, EM_SETREADONLY, bTemp, 0);

    /* Window Procedure */
    if (Prop->WndProcValid != ERROR_SUCCESS)
    {
        pszTemp = Err_GetWin32ErrorInfo(Prop->WndProcValid);
        if (pszTemp != NULL)
        {
            uTemp = Str_PrintfW(szBuffer, g_NAFormatText, pszTemp);
            if (Str_TestCchRet(uTemp, ARRAYSIZE(szBuffer)))
            {
                goto _Get_Window_Unicode;
            }
        }
        uTemp2 = (ULONG)Str_CopyW(szBuffer, g_NAText);
        if (Str_TestCchRet(uTemp2, ARRAYSIZE(szBuffer)))
        {
            uTemp += uTemp2;
        }
    } else
    {
        uTemp = Str_PrintfW(szBuffer, L"%p", Prop->WndProc);
        if (!Str_TestCchRet(uTemp, ARRAYSIZE(szBuffer)))
        {
            uTemp = 0;
        }
    }
_Get_Window_Unicode:
    if (ARRAYSIZE(szBuffer) - uTemp <= 2)
    {
        goto _End_WndProc;
    }
    uTemp2 = uTemp;
    szBuffer[uTemp++] = L' ';
    szBuffer[uTemp++] = L'(';
    uTemp += (ULONG)Str_CopyExW(szBuffer + uTemp,
                                ARRAYSIZE(szBuffer) - uTemp,
                                IsWindowUnicode(Prop->Handle) ? L"Unicode" : L"ANSI");
    if (ARRAYSIZE(szBuffer) - uTemp <= 2)
    {
        szBuffer[uTemp2] = UNICODE_NULL;
        goto _End_WndProc;
    }
    szBuffer[uTemp++] = L')';
    szBuffer[uTemp] = UNICODE_NULL;
_End_WndProc:
    UI_SetDlgItemTextW(Dialog, IDC_PROP_WNDPROC_EDIT, szBuffer);

    /* Style & Extended-style */
    UpdateStyleProp(GetDlgItem(Dialog, IDC_PROP_STYLE_EDIT),
                    Prop->Style,
                    Prop->StyleValid,
                    szBuffer,
                    ARRAYSIZE(szBuffer));
    UpdateStyleProp(GetDlgItem(Dialog, IDC_PROP_EXSTYLE_EDIT),
                    Prop->ExStyle,
                    Prop->ExStyleValid,
                    szBuffer,
                    ARRAYSIZE(szBuffer));
}

INT_PTR
CALLBACK
GeneralPspProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    UI_DPIScaleDlgProc(hDlg, uMsg, wParam, lParam);
    if (uMsg == WM_INITDIALOG)
    {
        AW_InitDlgItemI18N(hDlg, g_astI18NItems);

        UpdatePropInfo(hDlg, (PAW_WINDOW_PROP)lParam);

        return TRUE;
    }
    return FALSE;
}
