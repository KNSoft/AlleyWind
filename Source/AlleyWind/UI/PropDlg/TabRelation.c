#include "../../AlleyWind.inl"

static AW_I18N_DLGITEM aI18NItems[] = {
    { IDC_PROP_PROCESS_TEXT, Precomp4C_I18N_All_Process },
    { IDC_PROP_THREAD_TEXT, Precomp4C_I18N_All_Thread },
    { IDC_PROP_MONITOR_TEXT, Precomp4C_I18N_All_Monitor },
};

static UINT aRelWindowColCx[] = { 180, 140, 200, 200 };
static ULONG_PTR aRelWindowColPsz[] = {
    Precomp4C_I18N_All_Relationship,
    Precomp4C_I18N_All_Handle,
    Precomp4C_I18N_All_Caption,
    Precomp4C_I18N_All_Class,
};
C_ASSERT(ARRAYSIZE(aRelWindowColCx) == ARRAYSIZE(aRelWindowColPsz));

static ULONG_PTR aRelWindowI18NItems[AWWindowRelationshipMax] = {
    Precomp4C_I18N_All_ParentWindow,
    Precomp4C_I18N_All_OwnerWindow,
    Precomp4C_I18N_All_PreviousWindow,
    Precomp4C_I18N_All_NextWindow,
    Precomp4C_I18N_All_FirstChildWindow,
    Precomp4C_I18N_All_FirstEqualWindow,
    Precomp4C_I18N_All_LastEqualWindow,
};
C_ASSERT(ARRAYSIZE(aRelWindowI18NItems) == AWWindowRelationshipMax);

static
VOID
UpdatePropInfo(
    _In_ HWND Dialog,
    _In_ PAW_WINDOW_PROP Prop)
{
    WCHAR Buffer[MAX_PATH + 64], *psz;
    ULONG Cch, CchLast, u;
    LVITEMW lvi;
    HWND hRelList;
    W32ERROR Ret;

    if (Prop->ThreadProcessIdValid == ERROR_SUCCESS)
    {
        /* Process Id and Path */
        Cch = Str_PrintfW(Buffer, L"(%lu)", Prop->ProcessId);
        if (Cch == 0 || ARRAYSIZE(Buffer) - Cch <= 2)
        {
            goto _End_Write_Process_Path;
        }
        CchLast = Cch;
        Buffer[Cch++] = L' ';
        if (NT_SUCCESS(Prop->ProcessImagePathValid))
        {
            u = Str_CopyExW(Buffer + Cch, ARRAYSIZE(Buffer) - Cch, Prop->ProcessImagePath);
        } else
        {
            u = AW_WriteNAStringFromNtStatus(Buffer + Cch, ARRAYSIZE(Buffer) - Cch, Prop->ProcessImagePathValid);
        }
        if (u == 0)
        {
            Buffer[CchLast] = UNICODE_NULL;
        }
_End_Write_Process_Path:
        UI_SetDlgItemTextW(Dialog, IDC_PROP_PROCESS_EDIT, Buffer);

        /* Thread Id and Address */
        Cch = Str_PrintfW(Buffer, L"(%lu)", Prop->ThreadId);
        if (Cch == 0 || ARRAYSIZE(Buffer) - Cch <= 2)
        {
            goto _End_Write_Thread_Address;
        }
        CchLast = Cch;
        Buffer[Cch++] = L' ';
        u = AW_WriteAddressDisplayString(Prop,
                                         Prop->ThreadStartAddress,
                                         Prop->ThreadStartAddressDisplayNameValid,
                                         Prop->ThreadStartAddressDisplayName,
                                         Buffer + Cch,
                                         ARRAYSIZE(Buffer) - Cch);
        if (u == 0)
        {
            Buffer[CchLast] = UNICODE_NULL;
        }
_End_Write_Thread_Address:
        UI_SetDlgItemTextW(Dialog, IDC_PROP_THREAD_EDIT, Buffer);
    } else
    {
        AW_WriteNAStringFromWin32Error(Buffer, ARRAYSIZE(Buffer), Prop->ThreadProcessIdValid);
        UI_SetDlgItemTextW(Dialog, IDC_PROP_PROCESS_EDIT, Buffer);
        UI_SetDlgItemTextW(Dialog, IDC_PROP_THREAD_EDIT, Buffer);
    }

    if (Prop->MonitorInfoValid)
    {
        psz = Prop->MonitorInfo.szDevice;
        // TODO: Rect
    } else
    {
        psz = NULL;
    }
    UI_SetDlgItemTextW(Dialog, IDC_PROP_MONITOR_EDIT, psz);

    hRelList = GetDlgItem(Dialog, IDC_PROP_RELATION_LIST);
    for (ULONG i = 0; i < ARRAYSIZE(aRelWindowI18NItems); i++)
    {
        lvi.mask = LVIF_TEXT | LVIF_PARAM;
        lvi.pszText = (LPWSTR)AW_GetStringEx(aRelWindowI18NItems[i]);
        lvi.iItem = MAXINT;
        lvi.iSubItem = 0;
        lvi.lParam = (LPARAM)Prop->RelWindows[i];
        lvi.iItem = (INT)SendMessageW(hRelList, LVM_INSERTITEM, 0, (LPARAM)&lvi);
        if (lvi.iItem != -1)
        {
            lvi.mask = LVIF_TEXT;
            lvi.iSubItem++;
            lvi.pszText = Prop->RelWindows[i] != 0 && Str_PrintfW(Buffer, L"%08X", Prop->RelWindows[i]) > 0 ? Buffer : (PWSTR)AW_GetString(NA);
            SendMessageW(hRelList, LVM_SETITEM, 0, (LPARAM)&lvi);
            lvi.iSubItem++;
            if (Prop->RelWindows[i] != 0)
            {
                Ret = AW_GetWindowText((HWND)(ULONG_PTR)Prop->RelWindows[i], Buffer, ARRAYSIZE(Buffer));
                lvi.pszText = Ret == ERROR_SUCCESS ? Buffer :
                    (AW_WriteNAStringFromWin32Error(Buffer, ARRAYSIZE(Buffer), Ret) > 0 ? Buffer : (PWSTR)AW_GetString(NA));
            } else
            {
                lvi.pszText = (PWSTR)AW_GetString(NA);
            }
            SendMessageW(hRelList, LVM_SETITEM, 0, (LPARAM)&lvi);
            lvi.iSubItem++;
            if (Prop->RelWindows[i] != 0)
            {
                lvi.pszText = GetClassNameW((HWND)(ULONG_PTR)Prop->RelWindows[i], Buffer, ARRAYSIZE(Buffer)) > 0 ? Buffer :
                    (AW_WriteNAStringFromWin32Error(Buffer, ARRAYSIZE(Buffer), Err_GetLastError()) > 0 ? Buffer : (PWSTR)AW_GetString(NA));
            } else
            {
                lvi.pszText = (PWSTR)AW_GetString(NA);
            }
            SendMessageW(hRelList, LVM_SETITEM, 0, (LPARAM)&lvi);
        }
    }
}

INT_PTR
CALLBACK
RelationPspProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    UI_DPIScaleDlgProc(hDlg, uMsg, wParam, lParam);
    if (uMsg == WM_INITDIALOG)
    {
        HWND hRelList;
        LVCOLUMNW lvc;

        hRelList = GetDlgItem(hDlg, IDC_PROP_RELATION_LIST);
        AW_InitDlgItemI18N(hDlg, aI18NItems, ARRAYSIZE(aI18NItems));

        ListView_SetExtendedListViewStyle(hRelList, LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);
        UI_SetWindowExplorerVisualStyle(hRelList);
        lvc.mask = LVCF_TEXT | LVCF_WIDTH;
        for (INT i = 0; i < ARRAYSIZE(aRelWindowColCx); i++)
        {
            lvc.cx = aRelWindowColCx[i];
            lvc.pszText = (PWSTR)AW_GetStringEx(aRelWindowColPsz[i]);
            ListView_InsertColumn(hRelList, i, &lvc);
        }

        UpdatePropInfo(hDlg, (PAW_WINDOW_PROP)lParam);
        SetWindowLongPtrW(hDlg, DWLP_USER, lParam);
        return TRUE;
    } else if (uMsg == WM_COMMAND)
    {
        if (wParam == MAKEWPARAM(IDC_IDC_PROP_PROCESS_BUTTON, BN_CLICKED))
        {
            POINT pt;
            if (GetCursorPos(&pt))
            {
                PAW_WINDOW_PROP Prop = (PAW_WINDOW_PROP)GetWindowLongPtrW(hDlg, DWLP_USER);
                BOOL b = NT_SUCCESS(Prop->ProcessImagePathValid);

                if (UI_EnableMenuItem(g_ResPropRelDlgProcessMenu, Menu_PropRelDlg_Process_Locate, TRUE, b) &&
                    UI_EnableMenuItem(g_ResPropRelDlgProcessMenu, Menu_PropRelDlg_Process_Properties, TRUE, b))
                {
                    UI_PopupMenu(g_ResPropRelDlgProcessMenu, pt.x, pt.y, hDlg);
                }
            }
        } else if (wParam == MAKEWPARAM(IDM_RESPROPDLG_PROCESS_LOCATE, 0))
        {
            PAW_WINDOW_PROP Prop = (PAW_WINDOW_PROP)GetWindowLongPtrW(hDlg, DWLP_USER);
            HRESULT hr = Shell_LocateItem(Prop->ProcessImagePath);

            if (FAILED(hr))
            {
                KNS_HrMessageBox(hDlg, hr);
            }
        } else if (wParam == MAKEWPARAM(IDM_RESPROPDLG_PROCESS_PROPERTIES, 0))
        {

            W32ERROR Ret;
            PAW_WINDOW_PROP Prop = (PAW_WINDOW_PROP)GetWindowLongPtrW(hDlg, DWLP_USER);

            Ret = Shell_Exec(Prop->ProcessImagePath, NULL, L"properties", SW_SHOWNORMAL, NULL);
            if (Ret != ERROR_SUCCESS)
            {
                KNS_Win32ErrorMessageBox(hDlg, Ret);
            }
        } else if (wParam == MAKEWPARAM(IDM_RESPROPDLG_PROCESS_TERMINATE, 0))
        {
            PAW_WINDOW_PROP Prop = (PAW_WINDOW_PROP)GetWindowLongPtrW(hDlg, DWLP_USER);
            WCHAR ConfirmText[MAX_PATH * 2];
            NTSTATUS Status;

            if (Str_PrintfW(ConfirmText,
                            AW_GetString(TerminateConfirm),
                            Prop->ProcessImagePath,
                            Prop->ProcessId) > 0 &&
                UI_MsgBox(hDlg, ConfirmText, g_KNSAppInfo.AppName, MB_ICONQUESTION | MB_YESNO) == IDYES)
            {
                if (!EndTask(Prop->Handle, FALSE, TRUE))
                {
                    Status = PS_TerminateProcessById(Prop->ProcessId, 1);
                    if (!NT_SUCCESS(Status))
                    {
                        KNS_NtStatusMessageBox(hDlg, Status);
                    }
                }
            }
        }
    }
    return FALSE;
}
