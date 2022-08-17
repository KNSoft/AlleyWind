#include "AlleyWind.h"

CTL_PROPSHEETPAGE astWndPropSheetPage[] = {
    { I18NIndex_General, NULL, IDD_WNDPROP_GENERAL, WndPropGeneralDlgProc },
    { I18NIndex_Resource, NULL, IDD_WNDPROP_RESOURCE, WndPropResourceDlgProc },
    { I18NIndex_Relationship, NULL, IDD_WNDPROP_RELATIONSHIP, WndPropRelationshipDlgProc },
    { I18NIndex_Class, NULL, IDD_WNDPROP_CLASS, WndPropClassDlgProc },
    { I18NIndex_Operation, NULL, IDD_WNDPROP_OPERATION, WndPropOperationDlgProc },
    //{ I18NIndex_Message, NULL, IDD_WNDPROP_MESSAGE, WndPropMessageDlgProc }
};

INT_PTR WINAPI WndPropDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_INITDIALOG) {
        TCHAR   szCaption[MAX_PATH];
        INT     iCch;
        iCch = Str_Printf(szCaption, TEXT("%ws %08X"), I18N_GetString(I18NIndex_Window), (DWORD)(DWORD_PTR)lParam);
        SendMessage(hDlg, WM_SETTEXT, 0, iCch > 0 ? (LPARAM)szCaption : 0);
        SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)KNS_GetIcon());
        Ctl_SetPropertySheet(hDlg, IDC_WNDPROPTAB, astWndPropSheetPage, lParam);
        KNS_SetDialogSubclass(hDlg, NULL);
    } else if (uMsg == WM_DPICHANGED) {
        HWND    hTab;
        UINT    i;
        RECT    rc;
        hTab = GetDlgItem(hDlg, IDC_WNDPROPTAB);
        UI_GetRelativeRect(hTab, hDlg, &rc);
        SendMessage(hTab, TCM_ADJUSTRECT, FALSE, (LPARAM)&rc);
        for (i = 0; i < ARRAYSIZE(astWndPropSheetPage); i++) {
            SendMessage(astWndPropSheetPage[i].Handle, WM_DPICHANGED, wParam, (LPARAM)&rc);
        }
    } else if (uMsg == WM_CLOSE) {
        EndDialog(hDlg, 0);
        SetWindowLongPtr(hDlg, DWLP_MSGRESULT, 0);
    } else
        return FALSE;
    return TRUE;
}

DWORD WINAPI OpenWndPropDlgThread(PVOID lParam) {
    return (DWORD)DialogBoxParam(NT_GetImageBase(), MAKEINTRESOURCE(IDD_WNDPROP), NULL, WndPropDlgProc, (LPARAM)lParam);
}