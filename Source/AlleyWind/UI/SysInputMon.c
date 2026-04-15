#include "../AlleyWind.inl"

typedef union _AW_LLHOOKINFO
{ 
    PVOID lParam;
    PKBDLLHOOKSTRUCT Kb;
    PMSLLHOOKSTRUCT Ms;
} AW_LLHOOKINFO, *PAW_LLHOOKINFO;

static const INT g_MsgMonMaxItems = 300;
static _Interlocked_operand_ HWND volatile g_hSysInputDialog = NULL;

static UINT aMsgListColCx[] = { 150, 250 };
static ULONG_PTR aMsgListColPsz[] = {
    Precomp4C_I18N_KNSAW_Time,
    Precomp4C_I18N_KNSAW_Message,
};
_STATIC_ASSERT(ARRAYSIZE(aMsgListColCx) == ARRAYSIZE(aMsgListColPsz));

static HHOOK g_hhLLKeyboard = NULL;
static HHOOK g_hhLLMouse = NULL;
static HWND g_hList = NULL;

static
_Ret_maybenull_
PCWSTR
GetInputMessageName(
    _In_ WPARAM Message)
{
    for (ULONG i = 0; i < AW_DB_MSG_WM_Input.ConstantsCount; i++)
    {
        if (AW_DB_MSG_WM_Input.Constants[i].Value == Message)
        {
            return AW_DB_MSG_WM_Input.Constants[i].Name;
        }
    }
    return NULL;
}

static
VOID
AppendMonitorLog(
    _In_ UINT uMsg,
    _In_ PVOID lParam,
    _In_ LOGICAL bKeyboard)
{
    LVITEMW lvi;
    INT ItemIndex;
    
    AW_LLHOOKINFO Info = { lParam };
    LARGE_INTEGER Time;
    TIME_FIELDS TimeFields;
    WCHAR TimeText[13]; // 00:00:00:000

    if (bKeyboard)
    {
        Time.QuadPart = Info.Kb->time;
    } else
    {
        Time.QuadPart = Info.Ms->time;
    }
    RtlTimeToTimeFields(&Time, &TimeFields);
    if (Str_PrintfW(TimeText,
                    L"%02hu:%02hu:%02hu.%03hu",
                    TimeFields.Hour,
                    TimeFields.Minute,
                    TimeFields.Second,
                    TimeFields.Milliseconds) == 0)
    {
        return;
    }

    lvi.mask = LVIF_TEXT;
    lvi.iItem = MAXINT;
    lvi.iSubItem = 0;
    lvi.pszText = TimeText;
    ItemIndex = (INT)SendMessageW(g_hList, LVM_INSERTITEMW, 0, (LPARAM)&lvi);
    if (ItemIndex == -1)
    {
        return;
    }

    lvi.iItem = ItemIndex;
    lvi.iSubItem = 1;
    lvi.pszText = (PWSTR)GetInputMessageName(uMsg);
    SendMessageW(g_hList, LVM_SETITEMW, 0, (LPARAM)&lvi);

    while (ListView_GetItemCount(g_hList) > g_MsgMonMaxItems)
    {
        ListView_DeleteItem(g_hList, 0);
    }
    ListView_EnsureVisible(g_hList, ItemIndex, FALSE);
}

static
LRESULT
CALLBACK
LowLevelKeyboardHookProc(
    _In_ INT nCode,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        AppendMonitorLog((UINT)wParam, (PVOID)lParam, TRUE);
    }
    return CallNextHookEx(g_hhLLKeyboard, nCode, wParam, lParam);
}

static
LRESULT
CALLBACK
LowLevelMouseHookProc(
    _In_ INT nCode,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        AppendMonitorLog((UINT)wParam, (PVOID)lParam, TRUE);
    }
    return CallNextHookEx(g_hhLLMouse, nCode, wParam, lParam);
}

static
VOID
StopInputMonitor(
    _In_opt_ HWND Dialog)
{
    if (g_hhLLKeyboard != NULL)
    {
        UnhookWindowsHookEx(g_hhLLKeyboard);
        g_hhLLKeyboard = NULL;
    }
    if (g_hhLLMouse != NULL)
    {
        UnhookWindowsHookEx(g_hhLLMouse);
        g_hhLLMouse = NULL;
    }
    if (Dialog != NULL)
    {
        SendDlgItemMessageW(Dialog, IDC_SYSINPUTMON_CAPTURE_BTN, BM_SETCHECK, BST_UNCHECKED, 0);
    }
}

static
W32ERROR
StartInputMonitor(VOID)
{
    HHOOK hKeyboardHook;
    HHOOK hMouseHook;
    W32ERROR Ret;

    hKeyboardHook = SetWindowsHookExW(WH_KEYBOARD_LL, LowLevelKeyboardHookProc, NULL, 0);
    if (hKeyboardHook == NULL)
    {
        return Err_GetLastError();
    }

    hMouseHook = SetWindowsHookExW(WH_MOUSE_LL, LowLevelMouseHookProc, NULL, 0);
    if (hMouseHook == NULL)
    {
        Ret = Err_GetLastError();
        UnhookWindowsHookEx(hKeyboardHook);
        return Ret;
    }

    g_hhLLKeyboard = hKeyboardHook;
    g_hhLLMouse = hMouseHook;
    return ERROR_SUCCESS;
}

static
VOID
ToggleInputMonitor(
    _In_ HWND Dialog)
{
    W32ERROR Ret;
    LRESULT Checked;

    Checked = SendDlgItemMessageW(Dialog, IDC_SYSINPUTMON_CAPTURE_BTN, BM_GETCHECK, 0, 0);
    if (Checked == BST_CHECKED)
    {
        if (g_hhLLKeyboard != NULL || g_hhLLMouse != NULL)
        {
            return;
        }

        Ret = StartInputMonitor();
        if (Ret != ERROR_SUCCESS)
        {
            SendDlgItemMessageW(Dialog, IDC_SYSINPUTMON_CAPTURE_BTN, BM_SETCHECK, BST_UNCHECKED, 0);
            KNS_Win32ErrorMessageBox(Dialog, Ret);
        }
    } else
    {
        StopInputMonitor(Dialog);
    }
}

static
INT_PTR
CALLBACK
SysInputMonDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    UI_DPIScaleDlgProc(hDlg, uMsg, wParam, lParam);
    if (uMsg == WM_INITDIALOG)
    {
        LVCOLUMNW lvc;

        _InterlockedCompareExchangePointer(&g_hSysInputDialog, hDlg, NULL);
        g_hList = GetDlgItem(hDlg, IDC_SYSINPUTMON_LIST);
        ListView_SetExtendedListViewStyle(g_hList, LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);
        UI_SetWindowExplorerVisualStyle(g_hList);
        lvc.mask = LVCF_TEXT | LVCF_WIDTH;
        for (ULONG i = 0; i < ARRAYSIZE(aMsgListColCx); i++)
        {
            lvc.cx = aMsgListColCx[i];
            lvc.pszText = (PWSTR)AW_GetStringEx(aMsgListColPsz[i]);
            ListView_InsertColumn(g_hList, i, &lvc);
        }
        SetWindowLongPtrW(hDlg, DWLP_USER, lParam);
        return TRUE;
    } else if (uMsg == WM_COMMAND)
    {
        if (wParam == MAKEWPARAM(IDC_SYSINPUTMON_CAPTURE_BTN, BN_CLICKED))
        {
            ToggleInputMonitor(hDlg);
        }
    } else if (uMsg == WM_CLOSE)
    {
        SetWindowLongPtrW(hDlg, DWLP_MSGRESULT, 0);
        DestroyWindow(hDlg);
    } else if (uMsg == WM_DESTROY)
    {
        _InterlockedCompareExchangePointer(&g_hSysInputDialog, NULL, hDlg);
        StopInputMonitor(NULL);
        PostQuitMessage(S_OK);
    }
    return 0;
}

static
_Function_class_(USER_THREAD_START_ROUTINE)
NTSTATUS
NTAPI
OpenSysInputMonDialogBoxThread(
    _In_ PVOID ThreadParameter)
{
    NTSTATUS Status;
    Status = Err_HrToNtStatus(KNS_OpenModelDialogBox((HINSTANCE)&__ImageBase,
                                                     NULL,
                                                     g_ResSysInputMonDlgTemplate,
                                                     SysInputMonDlgProc,
                                                     0));
    return Status;
}

NTSTATUS
AW_OpenSysInputMonDialogBox(VOID)
{
    if (g_hSysInputDialog != NULL)
    {
        ShowWindow(g_hSysInputDialog, SW_SHOWNORMAL);
        return STATUS_SUCCESS;
    }
    return PS_CreateThread(NtCurrentProcess(), FALSE, OpenSysInputMonDialogBoxThread, NULL, NULL, NULL);
}
