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
        CHAR        szANSIBuffer[1024];
        INT         iTemp;
        HANDLE      hProc;
        NTSTATUS    lStatus;
        DWORD_PTR   dwpTemp;
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
        UI_GetWindowLong(hWnd, TRUE, GCW_ATOM, &dwpTemp);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_CLASS_ATOM_EDIT, dwpTemp || NT_LastErrorSucceed(), TEXT("%04X"), LOWORD(dwpTemp));
        // hInst
        UI_GetWindowLong(hWnd, TRUE, GCLP_HMODULE, &dwpTemp);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_CLASS_HINST_EDIT, dwpTemp || NT_LastErrorSucceed(), TEXT("%p"), (HINSTANCE)dwpTemp);
        // WndProc
        UI_GetWindowLong(hWnd, TRUE, GCLP_WNDPROC, &dwpTemp);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_CLASS_WNDPROC_EDIT, dwpTemp || NT_LastErrorSucceed(), TEXT("%p"), (WNDPROC)dwpTemp);
        // Style
        bSucc = UI_GetWindowLong(hWnd, TRUE, GCL_STYLE, &dwpTemp) == ERROR_SUCCESS;
        UI_EnableDlgItem(hDlg, IDC_WNDPROP_CLASS_STYLE_BTN, bSucc);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_CLASS_STYLE_EDIT, bSucc, TEXT("%08X"), (DWORD)dwpTemp);
        // hMenu
        UI_GetWindowLong(hWnd, TRUE, GCLP_MENUNAME, &dwpTemp);
        if (IS_INTRESOURCE(dwpTemp))
            AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_CLASS_MENURES_EDIT, dwpTemp != 0, TEXT("%d"), LOWORD(dwpTemp));
        else {
            hProc = UI_OpenProc(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, hWnd);
            if (hProc) {
                szBuffer[0] = '\0';
                if (IsWindowUnicode(hWnd)) {
                    lStatus = RProc_ReadMemStringW(hProc, (PVOID)dwpTemp, szBuffer);
                } else {
                    lStatus = RProc_ReadMemStringA(hProc, (PVOID)dwpTemp, szANSIBuffer);
                    if (NT_SUCCESS(lStatus))
                        Str_CchA2U(szBuffer, szANSIBuffer);
                }
                AW_SetPropCtlString(hDlg, IDC_WNDPROP_CLASS_MENURES_EDIT, szBuffer, NT_SUCCESS(lStatus));
                NtClose(hProc);
            } else
                UI_EnableDlgItem(hDlg, IDC_WNDPROP_CLASS_MENURES_EDIT, FALSE);
        }
        // Icon
        UI_GetWindowLong(hWnd, TRUE, GCLP_HICON, &dwpTemp);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_CLASS_HICON_EDIT, dwpTemp || NT_LastErrorSucceed(), TEXT("%p"), (HICON)dwpTemp);
        // Small Icon
        UI_GetWindowLong(hWnd, TRUE, GCLP_HICONSM, &dwpTemp);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_CLASS_HICONSM_EDIT, dwpTemp || NT_LastErrorSucceed(), TEXT("%p"), (HICON)dwpTemp);
        // Cursor
        UI_GetWindowLong(hWnd, TRUE, GCLP_HCURSOR, &dwpTemp);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_CLASS_HCURSOR_EDIT, dwpTemp || NT_LastErrorSucceed(), TEXT("%p"), (HCURSOR)dwpTemp);
        // Background Brush
        UI_GetWindowLong(hWnd, TRUE, GCLP_HBRBACKGROUND, &dwpTemp);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_CLASS_HBRBKGD_EDIT, dwpTemp || NT_LastErrorSucceed(), TEXT("%p"), (HBRUSH)dwpTemp);
        // Extra bytes
        hCtl = GetDlgItem(hDlg, IDC_WNDPROP_CLASS_CLSBYTE_LIST);
        Ctl_InitListCtl(hCtl, aExtraBytesListCol, LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);
        AW_EnumExtraBytes(hWnd, TRUE, (LPARAM)hCtl);
    } else if (uMsg == WM_COMMAND) {
        if (wParam == MAKEWPARAM(IDC_WNDPROP_CLASS_STYLE_BTN, BN_CLICKED)) {
            HWND        hWnd = AW_GetWndPropHWnd(hDlg);
            BOOL        bSucc;
            DWORD_PTR   dwpStyle;
            if (UI_GetWindowLong(hWnd, TRUE, GCL_STYLE, &dwpStyle) != ERROR_SUCCESS)
                return FALSE;
            if (AW_DBEditValue(hDlg, hWnd, AWValueClass, (PDWORD)&dwpStyle)) {
                NT_ClearLastError();
                SetClassLongPtr(hWnd, GCL_STYLE, dwpStyle);
                if (NT_LastErrorSucceed()) {
                    SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
                    UI_Redraw(hWnd);
                }
                bSucc = UI_GetWindowLong(hWnd, TRUE, GCL_STYLE, &dwpStyle) == ERROR_SUCCESS;
                UI_EnableDlgItem(hDlg, IDC_WNDPROP_CLASS_STYLE_BTN, bSucc);
                AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_CLASS_STYLE_EDIT, bSucc, TEXT("%08X"), (DWORD)dwpStyle);
            }
        }
    } else
        return FALSE;
    return TRUE;
}