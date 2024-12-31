#include "../../AlleyWind.inl"

#define IDM_PROCESS_OPENFILELOCATION 1
#define IDM_PROCESS_FILEPROPERTIES 2
#define IDM_PROCESS_TERMINATE 3

static
AW_I18N_DLGITEM g_astI18NItems[] = {
    { IDC_PROP_PROCESS_TEXT, Precomp4C_I18N_All_Process },
    { IDC_PROP_THREAD_TEXT, Precomp4C_I18N_All_Thread },
    { IDC_PROP_MONITOR_TEXT, Precomp4C_I18N_All_Monitor },
};

static
UI_MENU_ITEM g_astProcessMenu[] = {
    { FALSE, MF_STRING, IDM_PROCESS_OPENFILELOCATION, NULL, Precomp4C_I18N_All_OpenFileLocation, NULL, 0, NULL },
    { FALSE, MF_STRING | MF_DEFAULT, IDM_PROCESS_FILEPROPERTIES, NULL, Precomp4C_I18N_All_FileProperties, NULL, 0, NULL },
    { FALSE, MF_STRING | MF_DEFAULT, IDM_PROCESS_TERMINATE, NULL, Precomp4C_I18N_All_Terminate, NULL, 0, NULL },
};

static
VOID
UpdatePropInfo(
    _In_ HWND Dialog,
    _In_ PAW_WINDOW_PROP Prop)
{
    WCHAR Buffer[MAX_PATH + 64];
    ULONG Cch, CchLast, u;

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
        u= AW_WriteAddressDisplayString(Prop,
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

    UI_SetDlgItemTextW(Dialog, IDC_PROP_MONITOR_EDIT, Prop->MonitorInfo.szDevice);
}

INT_PTR
CALLBACK
RelationPspProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
