#include "../../AlleyWind.inl"

static AW_I18N_DLGITEM aI18NItems[] = {
    { IDC_PROP_CAPTION_TEXT, Precomp4C_I18N_KNSAW_Caption },
    { IDC_PROP_HANDLE_TEXT, Precomp4C_I18N_KNSAW_Handle },
    { IDC_PROP_INSTANCE_HANDLE_TEXT, Precomp4C_I18N_KNSAW_InstanceHandle },
    { IDC_PROP_SYSCLASS_TEXT, Precomp4C_I18N_KNSAW_SystemClass },
    { IDC_PROP_WNDPROC_TEXT, Precomp4C_I18N_KNSAW_WindowProcedure },
    { IDC_PROP_STYLE_TEXT, Precomp4C_I18N_KNSAW_Style },
    { IDC_PROP_EXSTYLE_TEXT, Precomp4C_I18N_KNSAW_ExtendedStyle },
    { IDC_PROP_RECT_TEXT, Precomp4C_I18N_KNSAW_Rectangle },
    { IDC_PROP_RECT_RELTIVE_CHECK, Precomp4C_I18N_KNSAW_Relative },
};

FORCEINLINE
VOID
SetStyleValue(
    _Out_ PWSTR Buffer,
    _In_ ULONG BufferCch,
    _In_ HWND Dialog,
    _In_ INT EditTextId,
    _In_ DWORD Style)
{
    UI_SetDlgItemTextW(Dialog,
                       EditTextId,
                       Str_PrintfExW(Buffer, BufferCch, L"%08lX", Style) != 0 ? Buffer : g_ResNAText);
}

static
VOID
SetRectValue(
    _Out_ PWSTR Buffer,
    _In_ ULONG BufferCch,
    _In_ HWND Dialog,
    _In_ PAW_WINDOW_PROP Prop)
{
    HWND hCheck = GetDlgItem(Dialog, IDC_PROP_RECT_RELTIVE_CHECK);
    LOGICAL bShowRelative;
    
    EnableWindow(hCheck,
                 Prop->RelativeRectValid &&
                 Prop->RelWindows[AWWindowRelationshipParent] != UI_TruncateHandle32(GetDesktopWindow()));
    UI_EnableDlgItem(Dialog, IDC_PROP_RECT_BTN, Prop->RelativeRectValid);

    if (Prop->RelativeRectValid)
    {
        bShowRelative = SendMessageW(hCheck, BM_GETCHECK, 0, 0) != BST_UNCHECKED;
    } else
    {
        SendMessageW(hCheck, BM_SETCHECK, BST_UNCHECKED, 0);
        bShowRelative = FALSE;
    }
    if (bShowRelative)
    {
        AW_WriteRectString(Buffer, BufferCch, &Prop->RelativeRect);
    } else
    {
        AW_WriteRectString(Buffer, BufferCch, &Prop->Info.rcWindow);
    }
    UI_SetDlgItemTextW(Dialog, IDC_PROP_RECT_EDIT, Buffer);
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

    /* Caption */
    hCtl = GetDlgItem(Dialog, IDC_PROP_CAPTION_EDIT);
    if (Prop->CaptionValid == ERROR_SUCCESS)
    {
        pszTemp = Prop->Caption;
    } else
    {
        AW_WriteNAStringWithWin32Error(szBuffer, ARRAYSIZE(szBuffer), Prop->CaptionValid);
        pszTemp = szBuffer;
    }
    UI_SetWindowTextW(hCtl, pszTemp);
    SendMessageW(hCtl, EM_SETREADONLY, Prop->CaptionValid != ERROR_SUCCESS, 0);

    /* Handle */
    Str_PrintfW(szBuffer, L"%08lX", UI_TruncateHandle32(Prop->Handle));
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
        AW_WriteNAStringWithWin32Error(szBuffer, ARRAYSIZE(szBuffer), Prop->InstanceHandleValid);
    }
    UI_SetDlgItemTextW(Dialog, IDC_PROP_INSTANCE_HANDLE_EDIT, szBuffer);

    /* System Class */
    if (Prop->ClassNameValid == ERROR_SUCCESS)
    {
        pszTemp = Prop->SysClassInfo == NULL ? NULL : Prop->SysClassInfo->DisplayName;
    } else
    {
        AW_WriteNAStringWithWin32Error(szBuffer, ARRAYSIZE(szBuffer), Prop->ClassNameValid);
        pszTemp = szBuffer;
    }
    UI_SetDlgItemTextW(Dialog, IDC_PROP_SYSCLASS_EDIT, pszTemp);

    /* Control ID */
    hCtl = GetDlgItem(Dialog, IDC_PROP_CTLID_EDIT);
    bTemp = Prop->IdentifierValid == ERROR_SUCCESS;
    if (bTemp)
    {
        pszTemp = Str_FromIntW(Prop->Identifier, szBuffer) > 0 ? szBuffer : NULL;
    } else
    {
        AW_WriteNAStringWithWin32Error(szBuffer, ARRAYSIZE(szBuffer), Prop->IdentifierValid);
        pszTemp = szBuffer;
    }
    UI_SetWindowTextW(hCtl, pszTemp);
    SendMessageW(hCtl, EM_SETREADONLY, !bTemp, 0);

    /* Window Procedure */
    if (Prop->WndProcValid != ERROR_SUCCESS)
    {
        AW_WriteNAStringWithWin32Error(szBuffer, ARRAYSIZE(szBuffer), Prop->WndProcValid);
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
                AW_GetStringEx(Prop->KernelMode ? Precomp4C_I18N_KNSAW_KernelMode : Precomp4C_I18N_KNSAW_UserMode));
    UI_SetDlgItemTextW(Dialog, IDC_PROP_WNDPROC_ATTR_TEXT, szBuffer);

    /* Style & Extended-style */
    SetStyleValue(szBuffer, ARRAYSIZE(szBuffer), Dialog, IDC_PROP_STYLE_EDIT, Prop->Info.dwStyle);
    SetStyleValue(szBuffer, ARRAYSIZE(szBuffer), Dialog, IDC_PROP_EXSTYLE_EDIT, Prop->Info.dwExStyle);

    /* Rectangle */
    SetRectValue(szBuffer, ARRAYSIZE(szBuffer), Dialog, Prop);
}

INT_PTR
CALLBACK
GeneralPspProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    UI_DPIScaleDlgProc(hDlg, uMsg, wParam, lParam);
    if (uMsg == WM_INITDIALOG)
    {
        AW_InitDlgItemI18N(hDlg, aI18NItems, ARRAYSIZE(aI18NItems));

        UpdatePropInfo(hDlg, (PAW_WINDOW_PROP)lParam);
        SetWindowLongPtrW(hDlg, DWLP_USER, lParam);
        return TRUE;
    } else if (uMsg == WM_COMMAND)
    {
        HRESULT hr;
        PAW_WINDOW_PROP Prop = (PAW_WINDOW_PROP)GetWindowLongPtrW(hDlg, DWLP_USER);

        if (wParam == MAKEWPARAM(IDC_PROP_STYLE_BTN, BN_CLICKED) ||
            wParam == MAKEWPARAM(IDC_PROP_EXSTYLE_BTN, BN_CLICKED))
        {
            LOGICAL bStyle = wParam == MAKEWPARAM(IDC_PROP_STYLE_BTN, BN_CLICKED);
            hr = AW_EditStyleValue(hDlg, Prop, bStyle ? AW_StyleType_Style : AW_StyleType_ExStyle);
            if (SUCCEEDED(hr))
            {
                AW_UpdatePropInfo(Prop);
                UpdatePropInfo(hDlg, Prop);
            }
        } else if (wParam == MAKEWPARAM(IDC_PROP_RECT_BTN, BN_CLICKED))
        {
            RECT rc;
            W32ERROR Ret;
            LOGICAL bRelative;

            bRelative = UI_GetDlgButtonCheck(hDlg, IDC_PROP_RECT_RELTIVE_CHECK) != BST_UNCHECKED;
            if (bRelative && !Prop->RelativeRectValid)
            {
                return FALSE;
            }

            rc = bRelative ? Prop->RelativeRect : Prop->Info.rcWindow;
            hr = UI_RectEditorDlg(hDlg, &rc);
            if (hr == S_OK)
            {
                if (!bRelative)
                {
                    if (!UI_ScreenRectToClient(UI_32ToHandle(Prop->RelWindows[AWWindowRelationshipParent]),
                                               &rc,
                                               &rc))
                    {
                        KNS_HrMessageBox(hDlg, E_UNEXPECTED);
                        return FALSE;
                    }
                }
                Ret = UI_SetWindowRect(Prop->Handle, &rc, TRUE);
                if (Ret == ERROR_SUCCESS)
                {
                    AW_UpdatePropInfo(Prop);
                    UpdatePropInfo(hDlg, Prop); 
                } else
                {
                    KNS_Win32ErrorMessageBox(hDlg, Ret);
                }
            } else if (FAILED(hr))
            {
                KNS_HrMessageBox(hDlg, hr);
            }
        } else if (wParam == MAKEWPARAM(IDC_PROP_RECT_RELTIVE_CHECK, BN_CLICKED))
        {
            WCHAR szBuffer[MAX_PATH];
            SetRectValue(szBuffer, ARRAYSIZE(szBuffer), hDlg, Prop);
        }
    }
    return FALSE;
}
