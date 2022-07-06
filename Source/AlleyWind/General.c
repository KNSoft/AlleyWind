#include "AlleyWind.h"

I18N_CTLTEXT astWndPropGeneralTextCtl[] = {
    { IDC_WNDPROP_GENERAL_CAPTION_TEXT, I18NIndex_Caption },
    { IDC_WNDPROP_GENERAL_HANDLE_TEXT, I18NIndex_Handle },
    { IDC_WNDPROP_GENERAL_WNDPROC_TEXT, I18NIndex_WindowProcedure },
    { IDC_WNDPROP_GENERAL_CTRLID_TEXT, I18NIndex_ControlID },
    { IDC_WNDPROP_GENERAL_SYSCLS_TEXT, I18NIndex_SystemClass },
    { IDC_WNDPROP_GENERAL_STYLE_TEXT, I18NIndex_Style },
    { IDC_WNDPROP_GENERAL_EXSTYLE_TEXT, I18NIndex_ExtendedStyle },
    { IDC_WNDPROP_GENERAL_USERDATA_TEXT, I18NIndex_UserData },
    { IDC_WNDPROP_GENERAL_RECT_TEXT, I18NIndex_Rectangle },
    { IDC_WNDPROP_GENERAL_RECTRELATIVEPOS_CHECK, I18NIndex_RelativePosition },
    { IDC_WNDPROP_GENERAL_WNDBYTE_TEXT, I18NIndex_ExtraBytes }
};

VOID WndPropGeneralUpdateRectCtl(HWND hDlg) {
    HWND    hWnd;
    RECT    rc;
    BOOL    bSucc, bRelative;
    hWnd = AW_GetWndPropHWnd(hDlg);
    if (hWnd == GetDesktopWindow()) {
        rc.left = GetSystemMetrics(SM_XVIRTUALSCREEN);
        rc.top = GetSystemMetrics(SM_YVIRTUALSCREEN);
        rc.right = rc.left + GetSystemMetrics(SM_CXVIRTUALSCREEN);
        rc.bottom = rc.top + GetSystemMetrics(SM_CYVIRTUALSCREEN);
        bRelative = FALSE;
        bSucc = TRUE;
        UI_SetDlgButtonCheck(hDlg, IDC_WNDPROP_GENERAL_RECTRELATIVEPOS_CHECK, BST_UNCHECKED);
        UI_EnableDlgItem(hDlg, IDC_WNDPROP_GENERAL_RECTRELATIVEPOS_CHECK, FALSE);
    } else {
        bRelative = UI_GetDlgButtonCheck(hDlg, IDC_WNDPROP_GENERAL_RECTRELATIVEPOS_CHECK) == BST_CHECKED;
        bSucc = bRelative ? UI_GetRelativeRect(hWnd, NULL, &rc) : UI_GetWindowRect(hWnd, &rc);
    }
    AW_SetPropCtlRect(hDlg, IDC_WNDPROP_GENERAL_RECT_EDIT, &rc, bSucc);
    UI_EnableDlgItem(hDlg, IDC_WNDPROP_GENERAL_RECT_BTN, bSucc && bRelative);
}

INT_PTR WINAPI WndPropGeneralDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_INITDIALOG) {
        HWND                hWnd, hCtl;
        TCHAR               szBuffer[1024], szTempPath[MAX_PATH];
        LPCTSTR             lpszTemp;
        DWORD_PTR           dwpStyle, dwpTemp;
        BOOL                bSucc, bStyleSucc;
        PAW_SYSCLASSINFO    lpSysClsInfo;
        INT                 iTemp;
        UINT                uTemp;
        hWnd = (HWND)lParam;
        AW_SetWndPropHWnd(hDlg, hWnd);
        // Initialize
        KNS_SetDialogSubclass(hDlg, NULL);
        I18N_InitCtlTexts(hDlg, astWndPropGeneralTextCtl);
        UI_SetDlgButtonCheck(hDlg, IDC_WNDPROP_GENERAL_RECTRELATIVEPOS_CHECK, TRUE);
        bSucc = UI_GetWindowLong(hWnd, FALSE, GWL_STYLE, &dwpStyle);
        bStyleSucc = bSucc;
        // Handle
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_GENERAL_HANDLE_EDIT, TRUE, TEXT("%08X"), (DWORD)(DWORD_PTR)hWnd);
        // Style and extra style
        UI_EnableDlgItem(hDlg, IDC_WNDPROP_GENERAL_STYLE_BTN, bSucc);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_GENERAL_STYLE_EDIT, bSucc, TEXT("%08X"), (DWORD)dwpStyle);;
        bSucc = UI_GetWindowLong(hWnd, FALSE, GWL_EXSTYLE, &dwpTemp);
        UI_EnableDlgItem(hDlg, IDC_WNDPROP_GENERAL_EXSTYLE_BTN, bSucc);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_GENERAL_EXSTYLE_EDIT, bSucc, TEXT("%08X"), (DWORD)dwpTemp);
        // Caption
        AW_GetWindowText(hWnd, szBuffer);
        AW_SetPropCtlString(hDlg, IDC_WNDPROP_GENERAL_CAPTION_EDIT, szBuffer, TRUE);
        // WndProc
        HANDLE      hProc;
        DWORD       dwPID;
        GetWindowThreadProcessId(hWnd, &dwPID);
        hProc = RProc_Open(HIJACK_PROCESS_ACCESS, dwPID);
        dwpTemp = 0;
        BOOL        b32Proc;
        PCSTR       pszGWLFunc;
        BOOL        bUnicode = IsWindowUnicode(hWnd);
        HIJACK_CALLPROCHEADER   stCallProc;
        HIJACK_CALLPROCPARAM    stGWLParams[] = {
            { (DWORD_PTR)hWnd, 0, FALSE },
            { GWLP_WNDPROC, 0, FALSE }
        };
        if (hProc && RProc_IsWow64(hProc, &b32Proc)) {
            pszGWLFunc = AW_GetWindowLongFunc(FALSE, b32Proc, bUnicode);
            if (Hijack_LoadProcAddr(hProc, L"user32.dll", pszGWLFunc, (PVOID*)&stCallProc.Procedure, AWSettings_GetItemValueEx(AWSetting_ResponseTimeout))) {
                stCallProc.RetValue = 0;
                stCallProc.CallConvention = CC_STDCALL;
                stCallProc.ParamCount = ARRAYSIZE(stGWLParams);
                dwpTemp = Hijack_CallProc(hProc, &stCallProc, stGWLParams, AWSettings_GetItemValueEx(AWSetting_ResponseTimeout)) ? (DWORD_PTR)stCallProc.RetValue : 0;
                if (b32Proc)
                    dwpTemp = (DWORD)dwpTemp;
            }
        }
        if (!dwpTemp)
            UI_GetWindowLong(hWnd, FALSE, GWLP_WNDPROC, &dwpTemp);
        uTemp = hProc && dwpTemp ? RProc_TranslateAddress(hProc, (PVOID)dwpTemp, szTempPath) : 0;
        iTemp = Str_Printf(szBuffer, TEXT("%s (%ws)"), uTemp ? szTempPath : I18N_GetString(I18NIndex_NotApplicable), bUnicode ? TEXT("Unicode") : TEXT("ANSI"));
        AW_SetPropCtlString(hDlg, IDC_WNDPROP_GENERAL_WNDPROC_EDIT, szBuffer, iTemp > 0);
        if (hProc)
            NtClose(hProc);
        // Control ID
        if (bStyleSucc && dwpStyle & WS_CHILD) {
            bSucc = UI_GetWindowLong(hWnd, FALSE, GWLP_ID, &dwpTemp);
            AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_GENERAL_CTRLID_EDIT, bSucc, TEXT("%d"), (INT)dwpTemp);
        } else {
            UI_EnableDlgItem(hDlg, IDC_WNDPROP_GENERAL_CTRLID_EDIT, FALSE);
        }
        // System class type
        lpszTemp = NULL;
        lpSysClsInfo = AW_DBFindSysClassInfo(hWnd);
        if (lpSysClsInfo)
            lpszTemp = IS_INTRESOURCE(lpSysClsInfo->DisplayName) ? I18N_GetString((UINT_PTR)lpSysClsInfo->DisplayName) : lpSysClsInfo->DisplayName;
        AW_SetPropCtlString(hDlg, IDC_WNDPROP_GENERAL_SYSCLS_EDIT, lpszTemp, lpszTemp != NULL);
        // User Data
        bSucc = UI_GetWindowLong(hWnd, FALSE, GWLP_USERDATA, &dwpTemp);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_GENERAL_USERDATA_EDIT, bSucc, TEXT("%p"), (LPVOID)dwpTemp);
        // Rectangles
        WndPropGeneralUpdateRectCtl(hDlg);
        // Extra Bytes
        hCtl = GetDlgItem(hDlg, IDC_WNDPROP_GENERAL_WNDBYTE_LIST);
        Ctl_InitListCtl(hCtl, aExtraBytesListCol, LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);
        AW_EnumExtraBytes(hWnd, FALSE, (LPARAM)hCtl);
    } else if (uMsg == WM_COMMAND) {
        if (wParam == MAKEWPARAM(IDC_WNDPROP_GENERAL_CAPTION_EDIT, EN_CHANGE) && !UI_GetNoNotifyFlag((HWND)lParam)) {
            HWND        hWnd;
            TCHAR       szBuffer[1024];
            LRESULT     lResult;
            DWORD_PTR   dwResult;
            hWnd = AW_GetWndPropHWnd(hDlg);
            lResult = UI_GetWindowText((HWND)lParam, szBuffer);
            lResult = AW_SendMsgTO(hWnd, WM_SETTEXT, 0, lResult ? (LPARAM)szBuffer : 0, &dwResult);
            if (!lResult || dwResult != TRUE) {
                AW_GetWindowText(hWnd, szBuffer);
                AW_SetPropCtlString(hDlg, LOWORD(wParam), szBuffer, TRUE);
            }
        } else if (
            wParam == MAKEWPARAM(IDC_WNDPROP_GENERAL_STYLE_BTN, BN_CLICKED) ||
            wParam == MAKEWPARAM(IDC_WNDPROP_GENERAL_EXSTYLE_BTN, BN_CLICKED)
            ) {
            HWND        hWnd = AW_GetWndPropHWnd(hDlg);
            BOOL        bSucc, bStyle = wParam == MAKEWPARAM(IDC_WNDPROP_GENERAL_STYLE_BTN, BN_CLICKED);
            DWORD_PTR   dwpStyle;
            if (!UI_GetWindowLong(hWnd, FALSE, bStyle ? GWL_STYLE : GWL_EXSTYLE, &dwpStyle))
                return FALSE;
            if (AW_DBEditValue(hDlg, hWnd, bStyle ? AWValueStyle : AWValueExStyle, (PDWORD)&dwpStyle)) {
                NT_ClearLastError();
                SetWindowLongPtr(hWnd, bStyle ? GWL_STYLE : GWL_EXSTYLE, dwpStyle);
                if (NT_LastErrorSucceed()) {
                    SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
                    UI_Redraw(hWnd);
                }
                bSucc = UI_GetWindowLong(hWnd, FALSE, bStyle ? GWL_STYLE : GWL_EXSTYLE, &dwpStyle);
                UI_EnableDlgItem(hDlg, bStyle ? IDC_WNDPROP_GENERAL_STYLE_BTN : IDC_WNDPROP_GENERAL_EXSTYLE_BTN, bSucc);
                AW_SetPropCtlFormat(hDlg, bStyle ? IDC_WNDPROP_GENERAL_STYLE_EDIT : IDC_WNDPROP_GENERAL_EXSTYLE_EDIT, bSucc, TEXT("%08X"), (DWORD)dwpStyle);
            }
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_GENERAL_RECTRELATIVEPOS_CHECK, BN_CLICKED)) {
            WndPropGeneralUpdateRectCtl(hDlg);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_GENERAL_RECT_BTN, BN_CLICKED)) {
            HWND    hWnd = AW_GetWndPropHWnd(hDlg);
            RECT    rc;
            if (UI_GetRelativeRect(hWnd, NULL, &rc) && Dlg_RectEditor(hDlg, DB_lpszDRE, &rc)) {
                UI_SetWindowRect(hWnd, &rc);
                WndPropGeneralUpdateRectCtl(hDlg);
            }
        }
    } else
        return FALSE;
    return TRUE;
}