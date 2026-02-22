#include "../AlleyWind.inl"

static
INT_PTR
CALLBACK
MsgMonDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    UI_DPIScaleDlgProc(hDlg, uMsg, wParam, lParam);
    if (uMsg == WM_INITDIALOG)
    {
        SetWindowLongPtrW(hDlg, DWLP_USER, lParam);
        return TRUE;
    } else if (uMsg == WM_COMMAND)
    {
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

static
_Function_class_(USER_THREAD_START_ROUTINE)
NTSTATUS
NTAPI
OpenMsgMonDialogBoxThread(
    _In_ PVOID ThreadParameter)
{
    return Err_HrToNtStatus(KNS_OpenModelDialogBox((HINSTANCE)&__ImageBase,
                                                   NULL,
                                                   g_ResMsgMonDlgTemplate,
                                                   MsgMonDlgProc,
                                                   0));
}

NTSTATUS
AW_OpenMsgMonDialogBox(VOID)
{
    return PS_CreateThread(NtCurrentProcess(), FALSE, OpenMsgMonDialogBoxThread, NULL, NULL, NULL);
}
