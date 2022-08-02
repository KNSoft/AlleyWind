#include "AlleyWind.h"

#define AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXUNIT 16
#define AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXSCALE 15
#define AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXBORDER 2

#define AW_WNDPROP_OPERATION_THEMT_MAX_CCH 128

I18N_CTLTEXT astWndPropOperationTextCtl[] = {
    { IDC_WNDPROP_OPERATION_QUICKSTYLE_GROUP, I18NIndex_QuickStyle },
    { IDC_WNDPROP_OPERATION_VISIBLE_CHECK, I18NIndex_Visible },
    { IDC_WNDPROP_OPERATION_ENABLED_CHECK, I18NIndex_Enable },
    { IDC_WNDPROP_OPERATION_TOPMOST_CHECK, I18NIndex_Topmost },
    { IDC_WNDPROP_OPERATION_LAYERED_GROUP, I18NIndex_Layered },
    { IDC_WNDPROP_OPERATION_LAYERED_CHECK, I18NIndex_Layered },
    { IDC_WNDPROP_OPERATION_OPACITY_CHECK, I18NIndex_Opacity },
    { IDC_WNDPROP_OPERATION_COLORKEY_CHECK, I18NIndex_ColorKey },
    { IDC_WNDPROP_OPERATION_DISPLAY_GROUP, I18NIndex_Display },
    { IDC_WNDPROP_OPERATION_VISUALSTYLE_TEXT, I18NIndex_VisualStyle },
    { IDC_WNDPROP_OPERATION_VISUALSTYLE_BTN, I18NIndex_Apply },
    { IDC_WNDPROP_OPERATION_ANTICAPTURE_CHECK, I18NIndex_AntiCapture },
    { IDC_WNDPROP_OPERATION_SWITCHTO_BTN, I18NIndex_SwitchTo },
    { IDC_WNDPROP_OPERATION_HIGHLIGHT_BTN, I18NIndex_Highlight },
    { IDC_WNDPROP_OPERATION_REDRAW_BTN, I18NIndex_Redraw },
    { IDC_WNDPROP_OPERATION_CLOSE_BTN, I18NIndex_Close },
    { IDC_WNDPROP_OPERATION_ENDTASK_BTN, I18NIndex_EndTask }
};

CTL_COMBOBOXCTL_ITEM astVisualStyleComboBoxItem[] = {
    { (UINT_PTR)TEXT("Explorer"),  0 },
    { (UINT_PTR)TEXT("Communications"),  0 },
    { (UINT_PTR)TEXT("TaskBand"),  0 },
    { (UINT_PTR)TEXT("TaskBar"),  0 }
};

ICONINFO            stPickColorCursorInfo;
BITMAP              bmPickColorCursor;

CRITICAL_SECTION    csPickColor;
DLG_SCREENSNAPSHOT  stWndPropOperationPickColorScreenSnapshot = { PickColorWndProc, NULL, NULL, 0, WS_POPUP | WS_VISIBLE, WS_EX_TOPMOST | WS_EX_TOOLWINDOW };
BOOL                bPickedColor;
COLORREF            crPicked;

VOID WndPropOperationInit() {
    RtlInitializeCriticalSection(&csPickColor);
    stWndPropOperationPickColorScreenSnapshot.hCursor = LoadImage(IMAGE_BASE, MAKEINTRESOURCE(IDC_PICK), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE);
    stWndPropOperationPickColorScreenSnapshot.hInstance = IMAGE_BASE;
    GetIconInfo(stWndPropOperationPickColorScreenSnapshot.hCursor, &stPickColorCursorInfo);
    if (stPickColorCursorInfo.hbmColor)
        DeleteObject(stPickColorCursorInfo.hbmColor);
    GetObject(stPickColorCursorInfo.hbmMask, sizeof(bmPickColorCursor), &bmPickColorCursor);
}

VOID WndPropOperationUninit() {
    DestroyCursor(stWndPropOperationPickColorScreenSnapshot.hCursor);
    DeleteObject(stPickColorCursorInfo.hbmMask);
}

LRESULT CALLBACK PickColorWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_PAINT) {
        UI_WINDBPAINT   stPaint;
        POINT           pt;
        RECT            rcInfoBox, rcPixel;
        UINT            uRow, uCol;
        HBRUSH          hbrBlack;
        UI_BeginPaint(hWnd, &stPaint);
        // Copy screen mirror
        BitBlt(stPaint.DC,
            0,
            0,
            stWndPropOperationPickColorScreenSnapshot.Snapshot.Size.cx,
            stWndPropOperationPickColorScreenSnapshot.Snapshot.Size.cy,
            stWndPropOperationPickColorScreenSnapshot.Snapshot.DC,
            0,
            0,
            SRCCOPY);
        // Draw info box
        GetCursorPos(&pt);
        ScreenToClient(hWnd, &pt);
        rcInfoBox.left = pt.x - stPickColorCursorInfo.xHotspot + bmPickColorCursor.bmWidth;
        rcInfoBox.top = pt.y - stPickColorCursorInfo.yHotspot + (stPickColorCursorInfo.hbmColor ? bmPickColorCursor.bmHeight : bmPickColorCursor.bmHeight / 2);
        rcInfoBox.right = rcInfoBox.left + AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXUNIT * AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXSCALE;
        rcInfoBox.bottom = rcInfoBox.top + AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXUNIT * AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXSCALE;
        // Draw zoomed image
        hbrBlack = GetStockBrush(BLACK_BRUSH);
        SelectBrush(stPaint.DC, hbrBlack);
        rcPixel.top = rcInfoBox.top;
        rcPixel.bottom = rcInfoBox.top + AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXSCALE;
        for (uRow = 0; uRow < AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXUNIT; uRow++) {
            rcPixel.left = rcInfoBox.left;
            rcPixel.right = rcPixel.left + AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXSCALE;
            for (uCol = 0; uCol < AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXUNIT; uCol++) {
                GDI_FillSolidRect(
                    stPaint.DC,
                    &rcPixel,
                    GetPixel(
                        stWndPropOperationPickColorScreenSnapshot.Snapshot.DC,
                        pt.x - AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXUNIT / 2 + uCol,
                        pt.y - AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXUNIT / 2 + uRow
                    )
                );
                // Draw center cross
                if (uRow == AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXUNIT / 2 && uCol == uRow)
                    GDI_FrameRect(stPaint.DC, &rcPixel, -AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXBORDER, DSTINVERT);
                else if (uRow == AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXUNIT / 2 && (uCol == uRow - 1 || uCol == uRow + 1))
                    PatBlt(stPaint.DC, rcPixel.left, (rcPixel.bottom + rcPixel.top) / 2, rcPixel.right - rcPixel.left, AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXBORDER, DSTINVERT);
                else if (uCol == AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXUNIT / 2 && (uRow == uCol - 1 || uRow == uCol + 1))
                    PatBlt(stPaint.DC, (rcPixel.right + rcPixel.left) / 2, rcPixel.top, AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXBORDER, rcPixel.bottom - rcPixel.top, DSTINVERT);
                rcPixel.left += AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXSCALE;
                rcPixel.right += AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXSCALE;
            }
            rcPixel.top += AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXSCALE;
            rcPixel.bottom += AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXSCALE;
        }
        // Draw border
        GDI_FrameRect(stPaint.DC, &rcInfoBox, AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXBORDER, DSTINVERT);
        UI_EndPaint(hWnd, &stPaint);
        return 0;
    } else if (uMsg == WM_MOUSEMOVE) {
        crPicked = GetPixel(stWndPropOperationPickColorScreenSnapshot.Snapshot.DC, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        UI_Redraw(hWnd);
        return 0;
    } else if (uMsg == WM_LBUTTONUP) {
        bPickedColor = TRUE;
        DestroyWindow(hWnd);
        return 0;
    } else if (uMsg == WM_KEYUP) {
        if (wParam == VK_CANCEL || wParam == VK_ESCAPE || wParam == VK_RETURN) {
            bPickedColor = wParam == VK_RETURN;
            DestroyWindow(hWnd);
        } else if (wParam == VK_UP || wParam == VK_DOWN || wParam == VK_LEFT || wParam == VK_RIGHT) {
            POINT pt;
            GetCursorPos(&pt);
            if (wParam == VK_UP)
                pt.y--;
            else if (wParam == VK_DOWN)
                pt.y++;
            else if (wParam == VK_LEFT)
                pt.x--;
            else
                pt.x++;
            SetCursorPos(pt.x, pt.y);
        }
        return 0;
    } else if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    } else
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

BOOL WndPropOperationOpenPickColorWindow(LPCOLORREF lpcrPicked) {
    RtlEnterCriticalSection(&csPickColor);
    bPickedColor = FALSE;
    Dlg_ScreenSnapshot(&stWndPropOperationPickColorScreenSnapshot);
    if (bPickedColor)
        *lpcrPicked = crPicked;
    RtlLeaveCriticalSection(&csPickColor);
    return bPickedColor;
}

VOID WndPropOperationSetCheckByStyle(HWND hDlg, UINT uCheckID, BOOL bExStyle, LONG_PTR lStyle) {
    LONG_PTR    lTemp;
    UINT_PTR    uCheck;
    BOOL        bSucc;
    bSucc = UI_GetWindowLong(AW_GetWndPropHWnd(hDlg), FALSE, bExStyle ? GWL_EXSTYLE : GWL_STYLE, &lTemp);
    lTemp &= lStyle;
    if (bSucc)
        if (lTemp == lStyle)
            uCheck = BST_CHECKED;
        else if (lTemp == 0)
            uCheck = BST_UNCHECKED;
        else
            uCheck = BST_INDETERMINATE;
    else
        uCheck = BST_UNCHECKED;
    AW_SetPropCtlCheck(hDlg, uCheckID, uCheck, bSucc);
}

BOOL WndPropOperationSetStyleByCheck(HWND hDlg, UINT uCheckID, BOOL bExStyle, LONG_PTR lStyle) {
    HWND        hWnd, hCheck;
    LONG_PTR    lTemp;
    INT         iIndex;
    UINT_PTR    uCheck;
    hWnd = AW_GetWndPropHWnd(hDlg);
    iIndex = bExStyle ? GWL_EXSTYLE : GWL_STYLE;
    if (!UI_GetWindowLong(AW_GetWndPropHWnd(hDlg), FALSE, iIndex, &lTemp))
        return FALSE;
    hCheck = GetDlgItem(hDlg, uCheckID);
    uCheck = SendMessage(hCheck, BM_GETCHECK, 0, 0);
    if (uCheck == BST_INDETERMINATE) {
        SendMessage(hCheck, BM_SETCHECK, BST_UNCHECKED, 0);
        uCheck = BST_UNCHECKED;
    }
    NT_ClearLastError();
    lStyle = SetWindowLongPtr(hWnd, iIndex, COMBINE_FLAGS(lTemp, lStyle, uCheck == BST_CHECKED));
    return lStyle || NT_LastErrorSucceed();
}

VOID WndPropOperationLayeredGet(HWND hDlg) {
    HWND        hWnd, hCtlLayeredCheck, hCtlOpacityCheck, hCtlOpacitySlider, hCtlColorKeyCheck, hCtlColorKeyButton;
    BYTE        byteLayeredAlpha;
    BOOL        bIsLayeredWnd, bTemp;
    COLORREF    crLayeredColorKey;
    DWORD_PTR   dwpExStyle;
    BOOL        bExStyleSucc;
    DWORD       dwLayeredFlags;
    hWnd = AW_GetWndPropHWnd(hDlg);
    bExStyleSucc = UI_GetWindowLong(hWnd, FALSE, GWL_EXSTYLE, &dwpExStyle);
    hCtlLayeredCheck = GetDlgItem(hDlg, IDC_WNDPROP_OPERATION_LAYERED_CHECK);
    hCtlOpacityCheck = GetDlgItem(hDlg, IDC_WNDPROP_OPERATION_OPACITY_CHECK);
    hCtlOpacitySlider = GetDlgItem(hDlg, IDC_WNDPROP_OPERATION_OPACITY_SLIDER);
    hCtlColorKeyCheck = GetDlgItem(hDlg, IDC_WNDPROP_OPERATION_COLORKEY_CHECK);
    hCtlColorKeyButton = GetDlgItem(hDlg, IDC_WNDPROP_OPERATION_COLORKEY_BTN);
    bIsLayeredWnd = FALSE;
    if (bExStyleSucc) {
        bIsLayeredWnd = dwpExStyle & WS_EX_LAYERED;
        SendMessage(hCtlLayeredCheck, BM_SETCHECK, bIsLayeredWnd ? BST_CHECKED : BST_UNCHECKED, 0);
        if (bIsLayeredWnd && GetLayeredWindowAttributes(hWnd, &crLayeredColorKey, &byteLayeredAlpha, &dwLayeredFlags)) {
            EnableWindow(hCtlOpacityCheck, TRUE);
            EnableWindow(hCtlColorKeyCheck, TRUE);
            bTemp = dwLayeredFlags & LWA_ALPHA;
            UI_SetDlgButtonCheck(hDlg, IDC_WNDPROP_OPERATION_OPACITY_CHECK, bTemp ? BST_CHECKED : BST_UNCHECKED);
            if (bTemp)
                SendMessage(hCtlOpacitySlider, TBM_SETPOS, TRUE, byteLayeredAlpha);
            EnableWindow(hCtlOpacitySlider, bTemp != FALSE);
            bTemp = dwLayeredFlags & LWA_COLORKEY;
            UI_SetDlgButtonCheck(hDlg, IDC_WNDPROP_OPERATION_COLORKEY_CHECK, bTemp ? BST_CHECKED : BST_UNCHECKED);
            if (bTemp)
                Ctl_SetColorPickerValue(hCtlColorKeyButton, crLayeredColorKey);
            EnableWindow(hCtlColorKeyButton, bTemp != FALSE);
            UI_EnableDlgItem(hDlg, IDC_WNDPROP_OPERATION_PICK_PIC, bTemp != FALSE);
        } else {
            EnableWindow(hCtlOpacitySlider, FALSE);
            EnableWindow(hCtlColorKeyButton, FALSE);
            UI_EnableDlgItem(hDlg, IDC_WNDPROP_OPERATION_PICK_PIC, FALSE);
        }
    } else {
        SendMessage(hCtlLayeredCheck, BM_SETCHECK, BST_UNCHECKED, 0);
        EnableWindow(hCtlLayeredCheck, FALSE);
    }
    if (!bIsLayeredWnd) {
        SendMessage(hCtlOpacityCheck, BM_SETCHECK, BST_UNCHECKED, 0);
        EnableWindow(hCtlOpacityCheck, FALSE);
        SendMessage(hCtlOpacitySlider, TBM_SETPOS, TRUE, MAXBYTE);
        SendMessage(hCtlColorKeyCheck, BM_SETCHECK, BST_UNCHECKED, 0);
        EnableWindow(hCtlColorKeyCheck, FALSE);
        Ctl_SetColorPickerValue(hCtlColorKeyButton, 0);
    }
}

BOOL WndPropOperationLayeredSet(HWND hDlg) {
    HWND        hWnd;
    LRESULT     lChecked;
    BYTE        byteLayeredAlpha;
    COLORREF    crLayeredColorKey;
    DWORD       dwLayeredFlags;
    hWnd = AW_GetWndPropHWnd(hDlg);
    lChecked = UI_SendDlgItemMsg(hDlg, IDC_WNDPROP_OPERATION_LAYERED_CHECK, BM_GETCHECK, 0, 0);
    if (!UI_EnableWindowStyle(hWnd, GWL_EXSTYLE, WS_EX_LAYERED, lChecked == BST_CHECKED))
        return FALSE;
    if (lChecked == BST_CHECKED) {
        dwLayeredFlags = crLayeredColorKey = byteLayeredAlpha = 0;
        lChecked = UI_SendDlgItemMsg(hDlg, IDC_WNDPROP_OPERATION_OPACITY_CHECK, BM_GETCHECK, 0, 0);
        if (lChecked == BST_CHECKED) {
            dwLayeredFlags |= LWA_ALPHA;
            byteLayeredAlpha = (BYTE)UI_SendDlgItemMsg(hDlg, IDC_WNDPROP_OPERATION_OPACITY_SLIDER, TBM_GETPOS, 0, 0);
        }
        lChecked = UI_SendDlgItemMsg(hDlg, IDC_WNDPROP_OPERATION_COLORKEY_CHECK, BM_GETCHECK, 0, 0);
        if (lChecked == BST_CHECKED) {
            dwLayeredFlags |= LWA_COLORKEY;
            crLayeredColorKey = Ctl_GetColorPickerValue(GetDlgItem(hDlg, IDC_WNDPROP_OPERATION_COLORKEY_BTN));
        }
        return SetLayeredWindowAttributes(hWnd, crLayeredColorKey, byteLayeredAlpha, dwLayeredFlags);
    } else
        return TRUE;
}

VOID WndPropOperationGetDisplayAffinity(HWND hDlg, HWND hWnd) {
    DWORD   dwTemp;
    HWND hCtl = GetDlgItem(hDlg, IDC_WNDPROP_OPERATION_ANTICAPTURE_CHECK);
    BOOL bEnable = GetWindowDisplayAffinity(hWnd, &dwTemp);
    SendMessage(hCtl, BM_SETCHECK, bEnable && dwTemp != WDA_NONE ? BST_CHECKED : BST_UNCHECKED, 0);
    EnableWindow(hCtl, bEnable);
}

INT_PTR WINAPI WndPropOperationDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_INITDIALOG) {
        HWND    hWnd, hCtl;
        hWnd = (HWND)lParam;
        AW_SetWndPropHWnd(hDlg, hWnd);
        // Initialize
        KNS_SetDialogSubclass(hDlg, NULL);
        I18N_InitCtlTexts(hDlg, astWndPropOperationTextCtl);
        UI_SendDlgItemMsg(hDlg, IDC_WNDPROP_OPERATION_OPACITY_SLIDER, TBM_SETRANGE, FALSE, MAKELPARAM(0, MAXBYTE));
        // Visible and Enable
        UI_SetDlgButtonCheck(hDlg, IDC_WNDPROP_OPERATION_VISIBLE_CHECK, IsWindowVisible(hWnd) ? BST_CHECKED : BST_UNCHECKED);
        UI_SetDlgButtonCheck(hDlg, IDC_WNDPROP_OPERATION_ENABLED_CHECK, IsWindowEnabled(hWnd) ? BST_CHECKED : BST_UNCHECKED);
        // Topmost
        WndPropOperationSetCheckByStyle(hDlg, IDC_WNDPROP_OPERATION_TOPMOST_CHECK, TRUE, WS_EX_TOPMOST);
        // Layered
        Ctl_SetColorPickerSubclass(GetDlgItem(hDlg, IDC_WNDPROP_OPERATION_COLORKEY_BTN), CTL_COLORPICKER_NOCOLOR);
        WndPropOperationLayeredGet(hDlg);
        // Visual Style
        hCtl = GetDlgItem(hDlg, IDC_WNDPROP_OPERATION_VISUALSTYLE_COMBOX);
        Ctl_InitComboBox(hCtl, astVisualStyleComboBoxItem, FALSE);
        SendMessage(hCtl, CB_LIMITTEXT, AW_WNDPROP_OPERATION_THEMT_MAX_CCH, 0);
        // Anti capture
        WndPropOperationGetDisplayAffinity(hDlg, hWnd);
        // End task
        if (hWnd == GetDesktopWindow())
            UI_EnableDlgItem(hDlg, IDC_WNDPROP_OPERATION_ENDTASK_BTN, FALSE);
    } else if (uMsg == WM_COMMAND) {
        if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_VISIBLE_CHECK, BN_CLICKED)) {
            HWND hWnd = AW_GetWndPropHWnd(hDlg);
            ShowWindowAsync(hWnd, SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED ? SW_SHOW : SW_HIDE);
            SendMessage((HWND)lParam, BM_SETCHECK, IsWindowVisible(hWnd) ? BST_CHECKED : BST_UNCHECKED, 0);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_ENABLED_CHECK, BN_CLICKED)) {
            HWND hWnd = AW_GetWndPropHWnd(hDlg);
            EnableWindow(hWnd, SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED ? TRUE : FALSE);
            SendMessage((HWND)lParam, BM_SETCHECK, IsWindowEnabled(hWnd) ? BST_CHECKED : BST_UNCHECKED, 0);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_TOPMOST_CHECK, BN_CLICKED)) {
            if (!SetWindowPos(AW_GetWndPropHWnd(hDlg), SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE))
                WndPropOperationSetCheckByStyle(hDlg, IDC_WNDPROP_OPERATION_TOPMOST_CHECK, TRUE, WS_EX_TOPMOST);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_LAYERED_CHECK, BN_CLICKED)) {
            UI_EnableWindowStyle(AW_GetWndPropHWnd(hDlg), GWL_EXSTYLE, WS_EX_LAYERED, SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED);
            WndPropOperationLayeredGet(hDlg);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_OPACITY_CHECK, BN_CLICKED)) {
            UI_EnableDlgItem(hDlg, IDC_WNDPROP_OPERATION_OPACITY_SLIDER, SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED);
            if (!WndPropOperationLayeredSet(hDlg))
                WndPropOperationLayeredGet(hDlg);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_COLORKEY_CHECK, BN_CLICKED)) {
            BOOL    bEnable = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED;
            UI_EnableDlgItem(hDlg, IDC_WNDPROP_OPERATION_COLORKEY_BTN, bEnable);
            UI_EnableDlgItem(hDlg, IDC_WNDPROP_OPERATION_PICK_PIC, bEnable);
            if (!WndPropOperationLayeredSet(hDlg))
                WndPropOperationLayeredGet(hDlg);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_COLORKEY_BTN, BN_CLICKED)) {
            if (!WndPropOperationLayeredSet(hDlg))
                WndPropOperationLayeredGet(hDlg);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_PICK_PIC, STN_CLICKED)) {
            COLORREF crLayeredKey;
            SetWindowPos(hDlg, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
            if (WndPropOperationOpenPickColorWindow(&crLayeredKey)) {
                Ctl_SetColorPickerValue(GetDlgItem(hDlg, IDC_WNDPROP_OPERATION_COLORKEY_BTN), crLayeredKey);
                if (!WndPropOperationLayeredSet(hDlg))
                    WndPropOperationLayeredGet(hDlg);
            }
            BringWindowToTop(hDlg);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_VISUALSTYLE_BTN, BN_CLICKED)) {
            HWND    hWnd = AW_GetWndPropHWnd(hDlg);
            TCHAR   szTheme[AW_WNDPROP_OPERATION_THEMT_MAX_CCH + 1];
            DWORD   dwError;
            szTheme[UI_GetDlgItemText(hDlg, IDC_WNDPROP_OPERATION_VISUALSTYLE_COMBOX, szTheme)] = '\0';
            if (SUCCEEDED(SetWindowTheme(hWnd, szTheme, szTheme[0] ? NULL : szTheme))) {
                SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
                UI_Redraw(hWnd);
                dwError = ERROR_SUCCESS;
            } else
                dwError = ERROR_FUNCTION_FAILED;
            KNS_ErrorMsgBox(hDlg, dwError);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_ANTICAPTURE_CHECK, BN_CLICKED)) {
            HWND    hWnd = AW_GetWndPropHWnd(hDlg);
            DWORD   dwAffinity;
            BOOL    bSucc;
            dwAffinity = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED ? WDA_EXCLUDEFROMCAPTURE : WDA_NONE;

            HANDLE                  hProc;
            HIJACK_CALLPROCHEADER   stCallProc;
            HIJACK_CALLPROCPARAM    stSWDAParams[] = {
                { (DWORD_PTR)hWnd, 0, FALSE },
                { dwAffinity, 0, FALSE }
            };
            bSucc = FALSE;
            hProc = UI_OpenProc(HIJACK_PROCESS_ACCESS, hWnd);
            if (hProc && Hijack_LoadProcAddr(
                    hProc,
                    L"user32.dll",
                    "SetWindowDisplayAffinity",
                    (PVOID*)&stCallProc.Procedure,
                    AWSettings_GetItemValueEx(AWSetting_ResponseTimeout))) {
                stCallProc.CallConvention = CC_STDCALL;
                stCallProc.ParamCount = ARRAYSIZE(stSWDAParams);
                if (Hijack_CallProc(
                        hProc,
                        &stCallProc,
                        stSWDAParams,
                        AWSettings_GetItemValueEx(AWSetting_ResponseTimeout)
                    ) && stCallProc.RetValue)
                    bSucc = TRUE;
            }
            if (!bSucc)
                KNS_ErrorMsgBox(hDlg, ERROR_FUNCTION_FAILED);
            WndPropOperationGetDisplayAffinity(hDlg, hWnd);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_SWITCHTO_BTN, BN_CLICKED)) {
            HWND hWnd = AW_GetWndPropHWnd(hDlg);
            if (IsIconic(hWnd))
                OpenIcon(hWnd);
            BringWindowToTop(hWnd);
            SetFocus(hWnd);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_HIGHLIGHT_BTN, BN_CLICKED)) {
            AW_HighlightWindow(AW_GetWndPropHWnd(hDlg));
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_REDRAW_BTN, BN_CLICKED)) {
            RedrawWindow(AW_GetWndPropHWnd(hDlg), NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ERASENOW | RDW_UPDATENOW | RDW_ALLCHILDREN);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_CLOSE_BTN, BN_CLICKED)) {
            DWORD_PTR dwResult;
            AW_SendMsgTO(AW_GetWndPropHWnd(hDlg), WM_CLOSE, 0, 0, &dwResult);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_ENDTASK_BTN, BN_CLICKED)) {
            EndTask(AW_GetWndPropHWnd(hDlg), FALSE, TRUE);
        }
    } else if (uMsg == WM_DRAWITEM) {
        if (wParam == IDC_WNDPROP_OPERATION_PICK_PIC) {
            PDRAWITEMSTRUCT pdi = (PDRAWITEMSTRUCT)lParam;
            INT             iCX, iCY;
            UINT            uDPIX, uDPIY;
            iCX = GetSystemMetrics(SM_CXCURSOR);
            iCY = GetSystemMetrics(SM_CYCURSOR);
            DPI_FromWindow(hDlg, &uDPIX, &uDPIY);
            if (uDPIX != USER_DEFAULT_SCREEN_DPI)
                DPI_ScaleInt(&iCX, USER_DEFAULT_SCREEN_DPI, uDPIX);
            if (uDPIY != USER_DEFAULT_SCREEN_DPI)
                DPI_ScaleInt(&iCY, USER_DEFAULT_SCREEN_DPI, uDPIY);
            GDI_DrawIcon(
                pdi->hDC,
                stWndPropOperationPickColorScreenSnapshot.hCursor,
                (pdi->rcItem.right - pdi->rcItem.left - iCX) / 2,
                (pdi->rcItem.bottom - pdi->rcItem.top - iCY) / 2,
                iCX,
                iCY);
            SetWindowLongPtr(hDlg, DWLP_MSGRESULT, TRUE);
        }
    } else if (uMsg == WM_HSCROLL) {
        if (lParam == (LPARAM)GetDlgItem(hDlg, IDC_WNDPROP_OPERATION_OPACITY_SLIDER))
            if (!WndPropOperationLayeredSet(hDlg))
                WndPropOperationLayeredGet(hDlg);
    } else
        return FALSE;
    return TRUE;
}