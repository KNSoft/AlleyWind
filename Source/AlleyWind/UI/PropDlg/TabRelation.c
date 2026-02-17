#include "../../AlleyWind.inl"

static AW_I18N_DLGITEM aI18NItems[] = {
    { IDC_PROP_PROCESS_TEXT, Precomp4C_I18N_KNSAW_Process },
    { IDC_PROP_THREAD_TEXT, Precomp4C_I18N_KNSAW_Thread },
    { IDC_PROP_MONITOR_TEXT, Precomp4C_I18N_KNSAW_Monitor },
    { IDC_PROP_VIRTDESK_TEXT, Precomp4C_I18N_KNSAW_VirtualDesktop },
};

static UINT aRelWindowColCx[] = { 180, 140, 200, 200 };
static ULONG_PTR aRelWindowColPsz[] = {
    Precomp4C_I18N_KNSAW_Relationship,
    Precomp4C_I18N_KNSAW_Handle,
    Precomp4C_I18N_KNSAW_Caption,
    Precomp4C_I18N_KNSAW_Class,
};
_STATIC_ASSERT(ARRAYSIZE(aRelWindowColCx) == ARRAYSIZE(aRelWindowColPsz));

static ULONG_PTR aRelWindowI18NItems[AWWindowRelationshipMax] = {
    Precomp4C_I18N_KNSAW_ParentWindow,
    Precomp4C_I18N_KNSAW_OwnerWindow,
    Precomp4C_I18N_KNSAW_PreviousWindow,
    Precomp4C_I18N_KNSAW_NextWindow,
    Precomp4C_I18N_KNSAW_FirstChildWindow,
    Precomp4C_I18N_KNSAW_FirstEqualWindow,
    Precomp4C_I18N_KNSAW_LastEqualWindow,
};
_STATIC_ASSERT(ARRAYSIZE(aRelWindowI18NItems) == AWWindowRelationshipMax);

typedef struct
{
    GUID CurrentId;
    HWND ComboBox;
} VIRTDESK_ENUM_CONTEXT, *PVIRTDESK_ENUM_CONTEXT;

static
_Function_class_(AW_VIRTDESK_ENUM_PROC)
__callback
LOGICAL
CALLBACK
EnumVirtualDesktopProc(
    _In_ PAW_VIRTDESK_INFO DeskInfo,
    _In_opt_ PVOID Context)
{
    _Analysis_assume_(Context != NULL);
    PVIRTDESK_ENUM_CONTEXT ctx = (PVIRTDESK_ENUM_CONTEXT)Context;

    ULONG Cch;
    WCHAR Buffer[MAX_PATH];
    INT_PTR iItem;

    /* Index */
    Buffer[0] = L'#';
    Cch = 1;
    Cch += Str_FromIntExW((INT64)DeskInfo->Index + 1, TRUE, 10, Buffer + Cch, ARRAYSIZE(Buffer) - Cch);

    /* Name */
    if (SUCCEEDED(DeskInfo->hrName))
    {
        Cch += Str_PrintfExW(Buffer + Cch,
                             ARRAYSIZE(Buffer) - Cch,
                             L" \"%ls\"",
                             _Inline_WindowsGetStringRawBuffer(DeskInfo->Name, NULL));
    }

    /* Id */
    if (SUCCEEDED(DeskInfo->hrId))
    {
        Buffer[Cch++] = L' ';
        Cch += Str_FromGUIDUpperW(Buffer + Cch,
                                  ARRAYSIZE(Buffer) - Cch,
                                  &DeskInfo->Id);
    }

    iItem = SendMessageW(ctx->ComboBox, CB_ADDSTRING, 0, (LPARAM)Buffer);
    if (iItem >= 0 && IsEqualGUID(&DeskInfo->Id, &ctx->CurrentId))
    {
        SendMessageW(ctx->ComboBox, CB_SETCURSEL, iItem, 0);
    }

    return TRUE;
}

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
    HRESULT hr;

    /* Process and thread information */
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
            u = Str_CopyExW(Buffer + Cch, ARRAYSIZE(Buffer) - Cch, Prop->ProcessImagePath.Buffer);
        } else
        {
            u = AW_WriteNAStringWithNtStatus(Buffer + Cch, ARRAYSIZE(Buffer) - Cch, Prop->ProcessImagePathValid);
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
        if (NT_SUCCESS(Prop->ThreadStartAddressValid))
        {
            u = AW_WriteAddressDisplayString(Prop,
                                             Prop->ThreadStartAddress,
                                             Prop->ThreadStartAddressDisplayNameValid,
                                             Prop->ThreadStartAddressDisplayName,
                                             Buffer + Cch,
                                             ARRAYSIZE(Buffer) - Cch);
        } else
        {
            u = AW_WriteNAStringWithNtStatus(Buffer + Cch, ARRAYSIZE(Buffer) - Cch, Prop->ThreadStartAddressValid);
        }
        if (u == 0)
        {
            Buffer[CchLast] = UNICODE_NULL;
        }
_End_Write_Thread_Address:
        UI_SetDlgItemTextW(Dialog, IDC_PROP_THREAD_EDIT, Buffer);
    } else
    {
        AW_WriteNAStringWithWin32Error(Buffer, ARRAYSIZE(Buffer), Prop->ThreadProcessIdValid);
        UI_SetDlgItemTextW(Dialog, IDC_PROP_PROCESS_EDIT, Buffer);
        UI_SetDlgItemTextW(Dialog, IDC_PROP_THREAD_EDIT, Buffer);
        UI_EnableDlgItem(Dialog, IDC_PROP_PROCESS_BUTTON, FALSE);
    }

    /* Monitor information */
    psz = NULL;
    if (Prop->MonitorInfoValid)
    {
        Cch = Str_CopyW(Buffer, Prop->MonitorInfo.szDevice);
        if (Cch == 0 || Cch == ARRAYSIZE(Buffer) - 1)
        {
            goto _Set_Monitor_Info;
        }
        Buffer[Cch++] = L' ';
        AW_WriteRectString(Buffer + Cch, ARRAYSIZE(Buffer) - Cch, &Prop->MonitorInfo.rcMonitor);
        psz = Buffer;
    }
_Set_Monitor_Info:
    UI_SetDlgItemTextW(Dialog, IDC_PROP_MONITOR_EDIT, psz);

    /* Virtual Desktop information */

    BOOL VDAvailable = FALSE;
    VIRTDESK_ENUM_CONTEXT VDCtx;

    VDCtx.ComboBox = GetDlgItem(Dialog, IDC_PROP_VIRTDESK_COMBO);
    SendMessageW(VDCtx.ComboBox, CB_RESETCONTENT, 0, 0);
    if (!Prop->TopLevel || g_Util_piVDM == NULL)
    {
        psz = (PWSTR)g_ResNAText;
        goto _Set_VirtDesk_Info;
    }
    hr = g_Util_piVDM->lpVtbl->GetWindowDesktopId(g_Util_piVDM, Prop->Handle, &VDCtx.CurrentId);
    if (SUCCEEDED(hr))
    {
        hr = AW_EnumVirtualDesktops(EnumVirtualDesktopProc, &VDCtx);
        if (SUCCEEDED(hr))
        {
            VDAvailable = TRUE;
        }
        Cch = Str_FromGUIDUpperW(Buffer, ARRAYSIZE(Buffer), &VDCtx.CurrentId);
    } else
    {
        Cch = AW_WriteNAStringWithHr(Buffer, ARRAYSIZE(Buffer), hr);
    }
    psz = Cch > 0 ? Buffer : (PWSTR)g_ResNAText;
_Set_VirtDesk_Info:
    UI_SetWindowTextW(VDCtx.ComboBox, psz);
    EnableWindow(VDCtx.ComboBox, VDAvailable);

    /* Related windows */
    hRelList = GetDlgItem(Dialog, IDC_PROP_RELATION_LIST);
    for (ULONG i = 0; i < ARRAYSIZE(aRelWindowI18NItems); i++)
    {
        lvi.mask = LVIF_TEXT | LVIF_PARAM;
        lvi.pszText = (LPWSTR)AW_GetStringEx(aRelWindowI18NItems[i]);
        lvi.iItem = MAXINT;
        lvi.iSubItem = 0;
        lvi.lParam = (LPARAM)Prop->RelWindows[i];
        lvi.iItem = (INT)SendMessageW(hRelList, LVM_INSERTITEMW, 0, (LPARAM)&lvi);
        if (lvi.iItem != -1)
        {
            lvi.mask = LVIF_TEXT;
            lvi.iSubItem++;
            lvi.pszText = Prop->RelWindows[i] != 0 && Str_PrintfW(Buffer, L"%08X", Prop->RelWindows[i]) > 0 ? Buffer : (PWSTR)AW_GetString(NA);
            SendMessageW(hRelList, LVM_SETITEM, 0, (LPARAM)&lvi);
            lvi.iSubItem++;
            if (Prop->RelWindows[i] != 0)
            {
                Ret = AW_GetWindowText(UI_32ToHandle(Prop->RelWindows[i]), Buffer, ARRAYSIZE(Buffer));
                lvi.pszText = Ret == ERROR_SUCCESS ? Buffer :
                    (AW_WriteNAStringWithWin32Error(Buffer, ARRAYSIZE(Buffer), Ret) > 0 ? Buffer : (PWSTR)AW_GetString(NA));
            } else
            {
                lvi.pszText = (PWSTR)AW_GetString(NA);
            }
            SendMessageW(hRelList, LVM_SETITEM, 0, (LPARAM)&lvi);
            lvi.iSubItem++;
            if (Prop->RelWindows[i] != 0)
            {
                lvi.pszText = GetClassNameW(UI_32ToHandle(Prop->RelWindows[i]), Buffer, ARRAYSIZE(Buffer)) > 0 ? Buffer :
                    (AW_WriteNAStringWithWin32Error(Buffer, ARRAYSIZE(Buffer), Err_GetLastError()) > 0 ? Buffer : (PWSTR)AW_GetString(NA));
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
        if (wParam == MAKEWPARAM(IDC_PROP_PROCESS_BUTTON, BN_CLICKED))
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
            HRESULT hr = Shell_LocateItem(Prop->ProcessImagePath.Buffer);
            if (FAILED(hr))
            {
                KNS_HrMessageBox(hDlg, hr);
            }
        } else if (wParam == MAKEWPARAM(IDM_RESPROPDLG_PROCESS_PROPERTIES, 0))
        {

            W32ERROR Ret;
            PAW_WINDOW_PROP Prop = (PAW_WINDOW_PROP)GetWindowLongPtrW(hDlg, DWLP_USER);

            Ret = Shell_Exec(Prop->ProcessImagePath.Path.Buffer, NULL, L"properties", SW_SHOWNORMAL, NULL);
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
                            &Prop->ProcessImagePath.Path,
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
