#include "../../AlleyWind.inl"

static
AW_I18N_DLGITEM g_astI18NItems[] = {
    { IDC_PROP_CAPTION_TEXT, Precomp4C_I18N_All_Caption },
    { IDC_PROP_HANDLE_TEXT, Precomp4C_I18N_All_Handle },
    { IDC_PROP_INSTANCE_HANDLE_TEXT, Precomp4C_I18N_All_InstanceHandle },
    { IDC_PROP_SYSCLASS_TEXT, Precomp4C_I18N_All_SystemClass },
    { IDC_PROP_WNDPROC_TEXT, Precomp4C_I18N_All_WindowProcedure },
    { IDC_PROP_STYLE_TEXT, Precomp4C_I18N_All_Style },
    { IDC_PROP_EXSTYLE_TEXT, Precomp4C_I18N_All_ExtendedStyle },
    { IDC_PROP_SCREEN_RECT_TEXT, Precomp4C_I18N_All_ScreenRectangle },
};

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
    INT iTemp;

    /* Caption */
    hCtl = GetDlgItem(Dialog, IDC_PROP_CAPTION_EDIT);
    if (Prop->CaptionValid == ERROR_SUCCESS)
    {
        pszTemp = Prop->Caption;
    } else
    {
        AW_WriteNAStringFromWin32Error(szBuffer, ARRAYSIZE(szBuffer), Prop->CaptionValid);
        pszTemp = szBuffer;
    }
    UI_SetWindowTextW(hCtl, pszTemp);
    SendMessageW(hCtl, EM_SETREADONLY, Prop->CaptionValid != ERROR_SUCCESS, 0);

    /* Handle */
    Str_PrintfW(szBuffer, L"%08lX", Prop->Handle);
    UI_SetDlgItemTextW(Dialog, IDC_PROP_HANDLE_EDIT, szBuffer);

    /* Instance Handle */
    if (Prop->InstanceHandleValid == ERROR_SUCCESS)
    {
        AW_WriteAddressDisplayString(Prop,
                                     Prop->InstanceHandle,
                                     Prop->InstanceHandleDisplayNameValid,
                                     Prop->InstanceHandleDisplayName,
                                     szBuffer,
                                     ARRAYSIZE(szBuffer));
    } else
    {
        AW_WriteNAStringFromWin32Error(szBuffer, ARRAYSIZE(szBuffer), Prop->InstanceHandleValid);
    }
    UI_SetDlgItemTextW(Dialog, IDC_PROP_INSTANCE_HANDLE_EDIT, szBuffer);

    /* System Class */
    if (Prop->ClassNameValid == ERROR_SUCCESS)
    {
        pszTemp = AW_GetSysClassDisplayName(Prop->ClassName);
    } else
    {
        AW_WriteNAStringFromWin32Error(szBuffer, ARRAYSIZE(szBuffer), Prop->ClassNameValid);
        pszTemp = szBuffer;
    }
    UI_SetDlgItemTextW(Dialog, IDC_PROP_SYSCLASS_EDIT, pszTemp);

    /* Control ID */
    hCtl = GetDlgItem(Dialog, IDC_PROP_CTLID_EDIT);
    bTemp = TRUE;
    if (Prop->IdentifierValid == ERROR_SUCCESS)
    {
        pszTemp = Str_FromIntW(Prop->Identifier, szBuffer) > 0 ? szBuffer : NULL;
        bTemp = FALSE;
    } else if (Prop->TopLevelWindow || !(Prop->Style & WS_CHILD))
    {
        pszTemp = AW_GetString(NANonChildWindow);
    } else
    {
        AW_WriteNAStringFromWin32Error(szBuffer, ARRAYSIZE(szBuffer), Prop->IdentifierValid);
        pszTemp = szBuffer;
    }
    UI_SetWindowTextW(hCtl, pszTemp);
    SendMessageW(hCtl, EM_SETREADONLY, bTemp, 0);

    /* Window Procedure */
    if (Prop->WndProcValid != ERROR_SUCCESS)
    {
        AW_WriteNAStringFromWin32Error(szBuffer, ARRAYSIZE(szBuffer), Prop->WndProcValid);
    } else
    {
        AW_WriteAddressDisplayString(Prop,
                                     Prop->WndProc,
                                     Prop->WndProcDisplayNameValid,
                                     Prop->WndProcDisplayName,
                                     szBuffer,
                                     ARRAYSIZE(szBuffer));
    }
    UI_SetDlgItemTextW(Dialog, IDC_PROP_WNDPROC_EDIT, szBuffer);
    Str_PrintfW(szBuffer,
                L"%ls | %ls",
                Prop->Unicode ? L"Unicode" : L"ANSI",
                AW_GetStringEx(Prop->KernelMode ? Precomp4C_I18N_All_KernelMode : Precomp4C_I18N_All_UserMode));
    UI_SetDlgItemTextW(Dialog, IDC_PROP_WNDPROC_ATTR_TEXT, szBuffer);

    /* Style & Extended-style */
    if (Prop->StyleValid == ERROR_SUCCESS)
    {
        Str_PrintfW(szBuffer, L"%08lX", Prop->Style) > 0 ? szBuffer : g_ResNAText;
    } else
    {
        AW_WriteNAStringFromWin32Error(szBuffer, ARRAYSIZE(szBuffer), Prop->StyleValid);
    }
    UI_SetDlgItemTextW(Dialog, IDC_PROP_STYLE_EDIT, szBuffer);
    if (Prop->ExStyleValid == ERROR_SUCCESS)
    {
        Str_PrintfW(szBuffer, L"%08lX", Prop->ExStyle) > 0 ? szBuffer : g_ResNAText;
    } else
    {
        AW_WriteNAStringFromWin32Error(szBuffer, ARRAYSIZE(szBuffer), Prop->ExStyleValid);
    }
    UI_SetDlgItemTextW(Dialog, IDC_PROP_EXSTYLE_EDIT, szBuffer);

    /* Rectangles */
    if (SUCCEEDED(Prop->ScreenRectValid))
    {
        Str_PrintfW(szBuffer,
                    AW_GetString(RectangleFormat),
                    Prop->ScreenRect.left,
                    Prop->ScreenRect.top,
                    Prop->ScreenRect.right,
                    Prop->ScreenRect.bottom,
                    Prop->ScreenRect.right - Prop->ScreenRect.left,
                    Prop->ScreenRect.bottom - Prop->ScreenRect.top);
    } else
    {
        AW_WriteNAStringFromHr(szBuffer, ARRAYSIZE(szBuffer), Prop->ScreenRectValid);
    }
    UI_SetDlgItemTextW(Dialog, IDC_PROP_SCREEN_RECT_EDIT, szBuffer);

    if (Prop->TopLevelWindow || !(Prop->Style & WS_CHILD))
    {
        iTemp = Precomp4C_I18N_All_ClientRectangle;
        if (Prop->Rect2Valid == ERROR_SUCCESS)
        {
            Str_PrintfW(szBuffer,
                        AW_GetString(RectangleFormat),
                        Prop->Rect2.left,
                        Prop->Rect2.top,
                        Prop->Rect2.right,
                        Prop->Rect2.bottom,
                        Prop->Rect2.right - Prop->Rect2.left,
                        Prop->Rect2.bottom - Prop->Rect2.top);
        } else
        {
            AW_WriteNAStringFromWin32Error(szBuffer, ARRAYSIZE(szBuffer), Prop->Rect2Valid);
        }
    } else
    {
        iTemp = Precomp4C_I18N_All_RelativeRectangle;
        if (SUCCEEDED(Prop->Rect2Valid))
        {
            Str_PrintfW(szBuffer,
                        AW_GetString(RectangleFormat),
                        Prop->Rect2.left,
                        Prop->Rect2.top,
                        Prop->Rect2.right,
                        Prop->Rect2.bottom,
                        Prop->Rect2.right - Prop->Rect2.left,
                        Prop->Rect2.bottom - Prop->Rect2.top);
        } else
        {
            AW_WriteNAStringFromHr(szBuffer, ARRAYSIZE(szBuffer), Prop->Rect2Valid);
        }
    }
    UI_SetDlgItemTextW(Dialog, IDC_PROP_RECT2_TEXT, AW_GetStringEx(iTemp));
    UI_SetDlgItemTextW(Dialog, IDC_PROP_RECT2_EDIT, szBuffer);
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
