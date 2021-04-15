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
    BOOL    bSuccess;
    hWnd = AW_GetWndPropHWnd(hDlg);
    if (hWnd == GetDesktopWindow()) {
        rc.left = GetSystemMetrics(SM_XVIRTUALSCREEN);
        rc.top = GetSystemMetrics(SM_YVIRTUALSCREEN);
        rc.right = rc.left + GetSystemMetrics(SM_CXVIRTUALSCREEN);
        rc.bottom = rc.top + GetSystemMetrics(SM_CYVIRTUALSCREEN);
        bSuccess = TRUE;
    } else
        bSuccess = UI_SendDlgItemMsg(hDlg, IDC_WNDPROP_GENERAL_RECTRELATIVEPOS_CHECK, BM_GETCHECK, 0, 0) == BST_CHECKED ? UI_GetRelativeRect(hWnd, NULL, &rc) : GetWindowRect(hWnd, &rc);
    AW_SetPropCtlRect(hDlg, IDC_WNDPROP_GENERAL_RECT_EDIT, &rc, bSuccess);
}

INT_PTR WINAPI WndPropGeneralDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_INITDIALOG) {
        HWND                hWnd, hCtl;
        TCHAR               szBuffer[1024], szTempPath[MAX_PATH];
        LPCTSTR             lpszTemp;
        DWORD               dwStyle, dwStyleError;
        PAW_SYSCLASSINFO    lpSysClsInfo;
        DWORD_PTR           dwpTemp;
        INT                 iTemp;
        UINT                uTemp;
        hWnd = (HWND)lParam;
        AW_SetWndPropHWnd(hDlg, hWnd);
        // Initialize
        KNS_SetDialogSubclass(hDlg, NULL);
        I18N_InitCtlTexts(hDlg, astWndPropGeneralTextCtl);
        UI_SetDlgButtonCheck(hDlg, IDC_WNDPROP_GENERAL_RECTRELATIVEPOS_CHECK, TRUE);
        NT_LastErrorClear();
        dwStyle = (DWORD)GetWindowLongPtr(hWnd, GWL_STYLE);
        dwStyleError = NT_LastErrorGet();
        // Handle
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_GENERAL_HANDLE_EDIT, TRUE, TEXT("%08X"), (DWORD)(DWORD_PTR)hWnd);
        // Style and extra style
        UI_EnableDlgItem(hDlg, IDC_WNDPROP_GENERAL_STYLE_BTN, dwStyleError == ERROR_SUCCESS);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_GENERAL_STYLE_EDIT, dwStyleError == ERROR_SUCCESS, TEXT("%08X"), dwStyle);
        NT_LastErrorClear();
        dwpTemp = GetWindowLongPtr(hWnd, GWL_EXSTYLE);
        dwStyleError = NT_LastErrorGet();
        UI_EnableDlgItem(hDlg, IDC_WNDPROP_GENERAL_EXSTYLE_BTN, dwStyleError == ERROR_SUCCESS);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_GENERAL_EXSTYLE_EDIT, dwStyleError == ERROR_SUCCESS, TEXT("%08X"), (DWORD)dwpTemp);
        // Caption
        if (!AW_SendMsgTO(hWnd, WM_GETTEXT, ARRAYSIZE(szBuffer), (LPARAM)szBuffer, &dwpTemp))
            dwpTemp = 0;
        szBuffer[dwpTemp] = '\0';
        AW_SetPropCtlString(hDlg, IDC_WNDPROP_GENERAL_CAPTION_EDIT, szBuffer, TRUE);
        // WndProc
        HANDLE      hProc;
        DWORD       dwPID;
        GetWindowThreadProcessId(hWnd, &dwPID);
        hProc = RProc_Open(PROCESS_ALL_ACCESS, dwPID);
        if (AWSettings_GetItemValueEx(AWSetting_EnableRemoteHijack)) {
            NTSTATUS    lStatus;
            BOOL        b32Proc;
            LPSTR       lpszGWLFunc;
            HIJACK_CALLPROCHEADER   stCallProc;
            HIJACK_CALLPROCPARAM    stGWLParams[] = {
                { (DWORD)(DWORD_PTR)hWnd, 0, FALSE },
                { GWLP_WNDPROC, 0, FALSE }
            };
            if (hProc && IsWow64Process(hProc, &b32Proc)) {
                lpszGWLFunc = b32Proc ? "GetWindowLongW" : "GetWindowLongPtrW";
                lStatus = Hijack_LoadProcAddr(hProc, L"user32.dll", lpszGWLFunc, (PVOID*)&stCallProc.Procedure);
                if (NT_SUCCESS(lStatus)) {
                    stCallProc.RetValue = 0;
                    stCallProc.CallConvention = 0;
                    stCallProc.ParamCount = ARRAYSIZE(stGWLParams);
                    lStatus = Hijack_CallProc(hProc, &stCallProc, stGWLParams, INFINITE);
                    dwpTemp = NT_SUCCESS(lStatus) ? (DWORD_PTR)stCallProc.RetValue : 0;
                    if (b32Proc)
                        dwpTemp = (DWORD)dwpTemp;
                }
            } else
                dwpTemp = 0;
        } else
            dwpTemp = GetWindowLongPtr(hWnd, GWLP_WNDPROC);
        uTemp = hProc && dwpTemp ? RProc_TranslateAddress(hProc, (PVOID)dwpTemp, szTempPath, ARRAYSIZE(szTempPath)) : 0;
        iTemp = Str_CchPrintf(szBuffer, TEXT("%s (%s)"), uTemp ? szTempPath : I18N_GetString(I18NIndex_NotApplicable), IsWindowUnicode(hWnd) ? TEXT("Unicode") : TEXT("ANSI"));
        AW_SetPropCtlString(hDlg, IDC_WNDPROP_GENERAL_WNDPROC_EDIT, szBuffer, iTemp > 0);
        if (hProc)
            NtClose(hProc);
        // Control ID
        if (dwStyleError == ERROR_SUCCESS && dwStyle & WS_CHILD) {
            NT_LastErrorClear();
            iTemp = GetDlgCtrlID(hWnd);
            AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_GENERAL_CTRLID_EDIT, iTemp || NT_LastErrorSucceed(), TEXT("%d"), iTemp);
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
        NT_LastErrorClear();
        dwpTemp = GetWindowLongPtr(hWnd, GWLP_USERDATA);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_GENERAL_USERDATA_EDIT, dwpTemp || NT_LastErrorSucceed(), TEXT("%p"), (LPVOID)dwpTemp);
        // Rectangles
        WndPropGeneralUpdateRectCtl(hDlg);
        // Extra Bytes
        hCtl = GetDlgItem(hDlg, IDC_WNDPROP_GENERAL_WNDBYTE_LIST);
        Ctl_InitListCtl(hCtl, aExtraBytesListCol, LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);
        AW_EnumExtraBytes(hWnd, FALSE, (LPARAM)hCtl);
    } else if (uMsg == WM_COMMAND) {
        if (wParam == MAKEWPARAM(IDC_WNDPROP_GENERAL_CAPTION_EDIT, EN_CHANGE) && !UI_IsSetNoChangeNotify((HWND)lParam)) {
            HWND        hWnd;
            TCHAR       szBuffer[1024];
            LRESULT     lResult;
            DWORD_PTR   dwResult;
            hWnd = AW_GetWndPropHWnd(hDlg);
            lResult = SendMessage((HWND)lParam, WM_GETTEXT, ARRAYSIZE(szBuffer), (LPARAM)szBuffer);
            lResult = AW_SendMsgTO(hWnd, WM_SETTEXT, 0, lResult ? (LPARAM)szBuffer : 0, &dwResult);
            if (!lResult || dwResult != TRUE) {
                if (!AW_SendMsgTO(hWnd, WM_GETTEXT, ARRAYSIZE(szBuffer), (LPARAM)szBuffer, &dwResult))
                    dwResult = 0;
                szBuffer[dwResult] = '\0';
                AW_SetPropCtlString(hDlg, LOWORD(wParam), szBuffer, TRUE);
            }
        } else if (
            wParam == MAKEWPARAM(IDC_WNDPROP_GENERAL_STYLE_BTN, BN_CLICKED) ||
            wParam == MAKEWPARAM(IDC_WNDPROP_GENERAL_EXSTYLE_BTN, BN_CLICKED)
            ) {
            HWND    hWnd = AW_GetWndPropHWnd(hDlg);
            BOOL    bSucc, bStyle = wParam == MAKEWPARAM(IDC_WNDPROP_GENERAL_STYLE_BTN, BN_CLICKED);
            DWORD   dwStyle;
            NT_LastErrorClear();
            dwStyle = (DWORD)GetWindowLongPtr(hWnd, bStyle ? GWL_STYLE : GWL_EXSTYLE);
            if (!NT_LastErrorSucceed())
                return FALSE;
            if (AW_DBEditValue(hDlg, hWnd, bStyle ? AWValueStyle : AWValueExStyle, &dwStyle)) {
                NT_LastErrorClear();
                SetWindowLongPtr(hWnd, bStyle ? GWL_STYLE : GWL_EXSTYLE, (LONG_PTR)dwStyle);
                if (NT_LastErrorSucceed()) {
                    SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
                    UI_Redraw(hWnd);
                }
                NT_LastErrorClear();
                dwStyle = (DWORD)GetWindowLongPtr(hWnd, bStyle ? GWL_STYLE : GWL_EXSTYLE);
                bSucc = NT_LastErrorGet() == ERROR_SUCCESS;
                UI_EnableDlgItem(hDlg, bStyle ? IDC_WNDPROP_GENERAL_STYLE_BTN : IDC_WNDPROP_GENERAL_EXSTYLE_BTN, bSucc);
                AW_SetPropCtlFormat(hDlg, bStyle ? IDC_WNDPROP_GENERAL_STYLE_EDIT : IDC_WNDPROP_GENERAL_EXSTYLE_EDIT, bSucc, TEXT("%08X"), dwStyle);
            }
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_GENERAL_RECTRELATIVEPOS_CHECK, BN_CLICKED)) {
            WndPropGeneralUpdateRectCtl(hDlg);
        }
    } else
        return FALSE;
    return TRUE;
}