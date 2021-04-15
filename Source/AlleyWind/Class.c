#include "AlleyWind.h"

I18N_CTLTEXT astWndPropClassTextCtl[] = {
    { IDC_WNDPROP_CLASS_NAME_TEXT, I18NIndex_Name },
    { IDC_WNDPROP_CLASS_HINST_TEXT, I18NIndex_InstanceHandle },
    { IDC_WNDPROP_CLASS_WNDPROC_TEXT, I18NIndex_WindowProcedure },
    { IDC_WNDPROP_CLASS_STYLE_TEXT, I18NIndex_Style },
    { IDC_WNDPROP_CLASS_MENURES_TEXT, I18NIndex_MenuResource },
    { IDC_WNDPROP_CLASS_HICON_TEXT, I18NIndex_Icon },
    { IDC_WNDPROP_CLASS_HICONSM_TEXT, I18NIndex_SmallIcon },
    { IDC_WNDPROP_CLASS_HCURSOR_TEXT, I18NIndex_Cursor },
    { IDC_WNDPROP_CLASS_HBRBKGD_TEXT, I18NIndex_BackgroundBrush },
    { IDC_WNDPROP_CLASS_CLSBYTE_TEXT, I18NIndex_ExtraBytes }
};

INT_PTR WINAPI WndPropClassDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_INITDIALOG) {
        HWND        hWnd, hCtl;
        TCHAR       szBuffer[1024];
        INT         iTemp;
        HANDLE      hProc;
        NTSTATUS    lStatus;
        DWORD_PTR   dwTemp;
        BOOL        bSucc;
        hWnd = (HWND)lParam;
        AW_SetWndPropHWnd(hDlg, hWnd);
        // Initialize
        KNS_SetDialogSubclass(hDlg, NULL);
        I18N_InitCtlTexts(hDlg, astWndPropClassTextCtl);
        // Name
        iTemp = GetClassName(hWnd, szBuffer, ARRAYSIZE(szBuffer));
        AW_SetPropCtlString(hDlg, IDC_WNDPROP_CLASS_NAME_EDIT, szBuffer, iTemp != 0);
        // Atom
        NT_LastErrorClear();
        dwTemp = GetClassLongPtr(hWnd, GCW_ATOM);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_CLASS_ATOM_EDIT, dwTemp || NT_LastErrorSucceed(), TEXT("%04X"), LOWORD(dwTemp));
        // hInst
        NT_LastErrorClear();
        dwTemp = GetClassLongPtr(hWnd, GCLP_HMODULE);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_CLASS_HINST_EDIT, dwTemp || NT_LastErrorSucceed(), TEXT("%p"), (HINSTANCE)dwTemp);
        // WndProc
        NT_LastErrorClear();
        dwTemp = GetClassLongPtr(hWnd, GCLP_WNDPROC);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_CLASS_WNDPROC_EDIT, dwTemp || NT_LastErrorSucceed(), TEXT("%p"), (WNDPROC)dwTemp);
        // Style
        NT_LastErrorClear();
        dwTemp = GetClassLongPtr(hWnd, GCL_STYLE);
        bSucc = dwTemp || NT_LastErrorSucceed();
        UI_EnableDlgItem(hDlg, IDC_WNDPROP_CLASS_STYLE_BTN, bSucc);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_CLASS_STYLE_EDIT, bSucc, TEXT("%08X"), (DWORD)dwTemp);
        // hMenu
        dwTemp = GetClassLongPtr(hWnd, GCLP_MENUNAME);
        if (IS_INTRESOURCE(dwTemp))
            AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_CLASS_MENURES_EDIT, dwTemp != 0, TEXT("%d"), LOWORD(dwTemp));
        else {
            hProc = UI_OpenProc(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, hWnd);
            if (hProc) {
                if (IsWindowUnicode(hWnd)) {
                    lStatus = RProc_ReadMemStringW(hProc, (LPVOID)dwTemp, szBuffer, ARRAYSIZE(szBuffer));
                    AW_SetPropCtlStringW(hDlg, IDC_WNDPROP_CLASS_MENURES_EDIT, szBuffer, NT_SUCCESS(lStatus));
                } else {
                    lStatus = RProc_ReadMemStringA(hProc, (LPVOID)dwTemp, (LPSTR)szBuffer, sizeof(szBuffer));
                    AW_SetPropCtlStringA(hDlg, IDC_WNDPROP_CLASS_MENURES_EDIT, (LPSTR)szBuffer, NT_SUCCESS(lStatus));
                }
                NtClose(hProc);
            } else
                UI_EnableDlgItem(hDlg, IDC_WNDPROP_CLASS_MENURES_EDIT, FALSE);
        }
        // Icon
        NT_LastErrorClear();
        dwTemp = GetClassLongPtr(hWnd, GCLP_HICON);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_CLASS_HICON_EDIT, dwTemp || NT_LastErrorSucceed(), TEXT("%p"), (HICON)dwTemp);
        // Small Icon
        NT_LastErrorClear();
        dwTemp = GetClassLongPtr(hWnd, GCLP_HICONSM);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_CLASS_HICONSM_EDIT, dwTemp || NT_LastErrorSucceed(), TEXT("%p"), (HICON)dwTemp);
        // Cursor
        NT_LastErrorClear();
        dwTemp = GetClassLongPtr(hWnd, GCLP_HCURSOR);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_CLASS_HCURSOR_EDIT, dwTemp || NT_LastErrorSucceed(), TEXT("%p"), (HCURSOR)dwTemp);
        // Background Brush
        NT_LastErrorClear();
        dwTemp = GetClassLongPtr(hWnd, GCLP_HBRBACKGROUND);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_CLASS_HBRBKGD_EDIT, dwTemp || NT_LastErrorSucceed(), TEXT("%p"), (HBRUSH)dwTemp);
        // Extra bytes
        hCtl = GetDlgItem(hDlg, IDC_WNDPROP_CLASS_CLSBYTE_LIST);
        Ctl_InitListCtl(hCtl, aExtraBytesListCol, LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);
        AW_EnumExtraBytes(hWnd, TRUE, (LPARAM)hCtl);
    } else if (uMsg == WM_COMMAND) {
        if (wParam == MAKEWPARAM(IDC_WNDPROP_CLASS_STYLE_BTN, BN_CLICKED)) {
            HWND    hWnd = AW_GetWndPropHWnd(hDlg);
            BOOL    bSucc;
            DWORD   dwStyle;
            NT_LastErrorClear();
            dwStyle = (DWORD)GetClassLongPtr(hWnd, GCL_STYLE);
            if (!NT_LastErrorSucceed())
                return FALSE;
            if (AW_DBEditValue(hDlg, hWnd, AWValueClass, &dwStyle)) {
                NT_LastErrorClear();
                SetClassLongPtr(hWnd, GCL_STYLE, (LONG_PTR)dwStyle);
                if (NT_LastErrorSucceed()) {
                    SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
                    UI_Redraw(hWnd);
                }
                NT_LastErrorClear();
                dwStyle = (DWORD)GetClassLongPtr(hWnd, GCL_STYLE);
                bSucc = NT_LastErrorGet() == ERROR_SUCCESS;
                UI_EnableDlgItem(hDlg, IDC_WNDPROP_CLASS_STYLE_BTN, bSucc);
                AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_CLASS_STYLE_EDIT, bSucc, TEXT("%08X"), dwStyle);
            }
        }
    } else
        return FALSE;
    return TRUE;
}