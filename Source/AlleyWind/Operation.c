#include "AlleyWind.h"

#define AW_WNDPROP_OPERATION_COLORKEY_PROP TEXT("AlleyWind.WndProp.Operation.ColorKey")
#define AW_WNDPROP_OPERATION_COLORKEY_BORDER 2
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
    { IDC_WNDPROP_OPERATION_VISUALSTYLE_GROUP, I18NIndex_VisualStyle },
    { IDC_WNDPROP_OPERATION_VISUALSTYLE_BTN, I18NIndex_Apply },
    { IDC_WNDPROP_OPERATION_OTHERS_GROUP, I18NIndex_Others },
    { IDC_WNDPROP_OPERATION_ANTICAPTURE_CHECK, I18NIndex_AntiCapture },
    { IDC_WNDPROP_OPERATION_SWITCHTO_BTN, I18NIndex_SwitchTo },
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
        BitBlt(stPaint.hDC,
            0,
            0,
            stWndPropOperationPickColorScreenSnapshot.iScreenCX,
            stWndPropOperationPickColorScreenSnapshot.iScreenCY,
            stWndPropOperationPickColorScreenSnapshot.hdcMirror,
            0,
            0,
            SRCCOPY);
        // Draw info box
        GetCursorPos(&pt);
        ScreenToClient(hWnd, &pt);
        rcInfoBox.left = pt.x - stPickColorCursorInfo.xHotspot + bmPickColorCursor.bmWidth;
        rcInfoBox.top = pt.y - stPickColorCursorInfo.yHotspot + bmPickColorCursor.bmHeight / 2;
        rcInfoBox.right = rcInfoBox.left + AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXUNIT * AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXSCALE;
        rcInfoBox.bottom = rcInfoBox.top + AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXUNIT * AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXSCALE;
        // Draw zoomed image
        hbrBlack = GetStockBrush(BLACK_BRUSH);
        SelectBrush(stPaint.hDC, hbrBlack);
        rcPixel.top = rcInfoBox.top;
        rcPixel.bottom = rcInfoBox.top + AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXSCALE;
        for (uRow = 0; uRow < AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXUNIT; uRow++) {
            rcPixel.left = rcInfoBox.left;
            rcPixel.right = rcPixel.left + AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXSCALE;
            for (uCol = 0; uCol < AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXUNIT; uCol++) {
                GDI_FillSolidRect(
                    stPaint.hDC,
                    &rcPixel,
                    GetPixel(
                        stWndPropOperationPickColorScreenSnapshot.hdcMirror,
                        pt.x - AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXUNIT / 2 + uCol,
                        pt.y - AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXUNIT / 2 + uRow
                    )
                );
                // Draw center cross
                if (uRow == AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXUNIT / 2 && uCol == uRow)
                    GDI_FrameRect(stPaint.hDC, &rcPixel, -AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXBORDER, DSTINVERT);
                else if (uRow == AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXUNIT / 2 && (uCol == uRow - 1 || uCol == uRow + 1))
                    PatBlt(stPaint.hDC, rcPixel.left, (rcPixel.bottom + rcPixel.top) / 2, rcPixel.right - rcPixel.left, AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXBORDER, DSTINVERT);
                else if (uCol == AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXUNIT / 2 && (uRow == uCol - 1 || uRow == uCol + 1))
                    PatBlt(stPaint.hDC, (rcPixel.right + rcPixel.left) / 2, rcPixel.top, AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXBORDER, rcPixel.bottom - rcPixel.top, DSTINVERT);
                rcPixel.left += AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXSCALE;
                rcPixel.right += AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXSCALE;
            }
            rcPixel.top += AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXSCALE;
            rcPixel.bottom += AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXSCALE;
        }
        // Draw border
        GDI_FrameRect(stPaint.hDC, &rcInfoBox, AW_WNDPROP_OPERATION_PICKCOLOR_INFOBOXBORDER, DSTINVERT);
        UI_EndPaint(hWnd, &stPaint);
        return 0;
    } else if (uMsg == WM_MOUSEMOVE) {
        crPicked = GetPixel(stWndPropOperationPickColorScreenSnapshot.hdcMirror, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
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
    BOOL        bSuccess;
    NT_LastErrorClear();
    lTemp = GetWindowLongPtr(AW_GetWndPropHWnd(hDlg), bExStyle ? GWL_EXSTYLE : GWL_STYLE);
    bSuccess = lTemp || NT_LastErrorSucceed();
    lTemp &= lStyle;
    if (bSuccess)
        if (lTemp == lStyle)
            uCheck = BST_CHECKED;
        else if (lTemp == 0)
            uCheck = BST_UNCHECKED;
        else
            uCheck = BST_INDETERMINATE;
    else
        uCheck = BST_UNCHECKED;
    AW_SetPropCtlCheck(hDlg, uCheckID, uCheck, bSuccess);
}

BOOL WndPropOperationSetStyleByCheck(HWND hDlg, UINT uCheckID, BOOL bExStyle, LONG_PTR lStyle) {
    HWND        hWnd, hCheck;
    LONG_PTR    lTemp;
    INT         iIndex;
    UINT_PTR    uCheck;
    BOOL        bSuccess;
    hWnd = AW_GetWndPropHWnd(hDlg);
    iIndex = bExStyle ? GWL_EXSTYLE : GWL_STYLE;
    NT_LastErrorClear();
    lTemp = GetWindowLongPtr(hWnd, iIndex);
    bSuccess = lTemp || NT_LastErrorSucceed();
    if (!bSuccess)
        return FALSE;
    hCheck = GetDlgItem(hDlg, uCheckID);
    uCheck = SendMessage(hCheck, BM_GETCHECK, 0, 0);
    if (uCheck == BST_INDETERMINATE) {
        SendMessage(hCheck, BM_SETCHECK, BST_UNCHECKED, 0);
        uCheck = BST_UNCHECKED;
    }
    NT_LastErrorClear();
    lStyle = SetWindowLongPtr(hWnd, iIndex, COMBINE_FLAGS(lTemp, lStyle, uCheck == BST_CHECKED));
    return lStyle || NT_LastErrorSucceed();
}

COLORREF WndPropOperationLayeredGetColorKeyCtl(HWND hDlg) {
    return (COLORREF)(DWORD_PTR)UI_GetDlgItemProp(hDlg, IDC_WNDPROP_OPERATION_COLORKEY_PIC, AW_WNDPROP_OPERATION_COLORKEY_PROP);
}

VOID WndPropOperationLayeredSetColorKeyCtl(HWND hDlg, COLORREF crColorKey) {
    HWND    hCtlColorKey = GetDlgItem(hDlg, IDC_WNDPROP_OPERATION_COLORKEY_PIC);
    SetProp(hCtlColorKey, AW_WNDPROP_OPERATION_COLORKEY_PROP, (HANDLE)(DWORD_PTR)crColorKey);
    UI_Redraw(hCtlColorKey);
}

VOID WndPropOperationLayeredGet(HWND hDlg) {
    HANDLE      hWnd, hCtlLayeredCheck, hCtlOpacityCheck, hCtlOpacitySlider, hCtlColorKeyCheck;
    BYTE        byteLayeredAlpha;
    BOOL        bIsLayeredWnd, bTemp;
    COLORREF    crLayeredColorKey;
    DWORD       dwExStyle, dwExStyleError, dwLayeredFlags;
    hWnd = AW_GetWndPropHWnd(hDlg);
    NT_LastErrorClear();
    dwExStyle = (DWORD)GetWindowLongPtr(hWnd, GWL_EXSTYLE);
    dwExStyleError = NT_LastErrorGet();
    hCtlLayeredCheck = GetDlgItem(hDlg, IDC_WNDPROP_OPERATION_LAYERED_CHECK);
    hCtlOpacityCheck = GetDlgItem(hDlg, IDC_WNDPROP_OPERATION_OPACITY_CHECK);
    hCtlOpacitySlider = GetDlgItem(hDlg, IDC_WNDPROP_OPERATION_OPACITY_SLIDER);
    hCtlColorKeyCheck = GetDlgItem(hDlg, IDC_WNDPROP_OPERATION_COLORKEY_CHECK);
    bIsLayeredWnd = FALSE;
    if (dwExStyleError == ERROR_SUCCESS) {
        bIsLayeredWnd = dwExStyle & WS_EX_LAYERED;
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
                WndPropOperationLayeredSetColorKeyCtl(hDlg, crLayeredColorKey);
            UI_EnableDlgItem(hDlg, IDC_WNDPROP_OPERATION_COLORKEY_PIC, bTemp != FALSE);
            UI_EnableDlgItem(hDlg, IDC_WNDPROP_OPERATION_PICK_PIC, bTemp != FALSE);
        } else {
            EnableWindow(hCtlOpacitySlider, FALSE);
            UI_EnableDlgItem(hDlg, IDC_WNDPROP_OPERATION_COLORKEY_PIC, FALSE);
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
        WndPropOperationLayeredSetColorKeyCtl(hDlg, 0);
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
            crLayeredColorKey = WndPropOperationLayeredGetColorKeyCtl(hDlg);
        }
        return SetLayeredWindowAttributes(hWnd, crLayeredColorKey, byteLayeredAlpha, dwLayeredFlags);
    } else
        return TRUE;
}

INT_PTR WINAPI WndPropOperationDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_INITDIALOG) {
        HWND    hWnd, hCtl;
        DWORD   dwTemp;
        hWnd = (HANDLE)lParam;
        AW_SetWndPropHWnd(hDlg, hWnd);
        // Initialize
        KNS_SetDialogSubclass(hDlg, NULL);
        I18N_InitCtlTexts(hDlg, astWndPropOperationTextCtl);
        UI_SendDlgItemMsg(hDlg, IDC_WNDPROP_OPERATION_OPACITY_SLIDER, TBM_SETRANGE, FALSE, MAKELPARAM(0, MAXBYTE));
        UI_SendDlgItemMsg(hDlg, IDC_WNDPROP_OPERATION_PICK_PIC, STM_SETIMAGE, IMAGE_CURSOR, (LPARAM)stWndPropOperationPickColorScreenSnapshot.hCursor);
        // Visible and Enable
        UI_SetDlgButtonCheck(hDlg, IDC_WNDPROP_OPERATION_VISIBLE_CHECK, IsWindowVisible(hWnd) ? BST_CHECKED : BST_UNCHECKED);
        UI_SetDlgButtonCheck(hDlg, IDC_WNDPROP_OPERATION_ENABLED_CHECK, IsWindowEnabled(hWnd) ? BST_CHECKED : BST_UNCHECKED);
        // Topmost
        WndPropOperationSetCheckByStyle(hDlg, IDC_WNDPROP_OPERATION_TOPMOST_CHECK, TRUE, WS_EX_TOPMOST);
        // Layered
        WndPropOperationLayeredGet(hDlg);
        // Visual Style
        hCtl = GetDlgItem(hDlg, IDC_WNDPROP_OPERATION_VISUALSTYLE_COMBOX);
        Ctl_InitComboBox(hCtl, astVisualStyleComboBoxItem, FALSE);
        SendMessage(hCtl, CB_LIMITTEXT, AW_WNDPROP_OPERATION_THEMT_MAX_CCH, 0);
        // Anti capture
        hCtl = GetDlgItem(hDlg, IDC_WNDPROP_OPERATION_ANTICAPTURE_CHECK);
        if (UI_GetWindowDisplayAffinity(hWnd, &dwTemp))
            SendMessage(hCtl, BM_SETCHECK, dwTemp == WDA_NONE ? BST_UNCHECKED : BST_CHECKED, 0);
        else
            EnableWindow(hCtl, FALSE);
        // End task
        if (hWnd == GetDesktopWindow())
            UI_EnableDlgItem(hDlg, IDC_WNDPROP_OPERATION_ENDTASK_BTN, FALSE);
    } else if (uMsg == WM_COMMAND) {
        if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_VISIBLE_CHECK, BN_CLICKED)) {
            HWND hWnd = AW_GetWndPropHWnd(hDlg);
            ShowWindow(hWnd, SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED ? SW_SHOW : SW_HIDE);
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
            UI_EnableDlgItem(hDlg, IDC_WNDPROP_OPERATION_COLORKEY_PIC, bEnable);
            UI_EnableDlgItem(hDlg, IDC_WNDPROP_OPERATION_PICK_PIC, bEnable);
            if (!WndPropOperationLayeredSet(hDlg))
                WndPropOperationLayeredGet(hDlg);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_COLORKEY_PIC, STN_CLICKED)) {
            COLORREF    crLayeredColorKey;
            crLayeredColorKey = WndPropOperationLayeredGetColorKeyCtl(hDlg);
            if (Dlg_ChooseColor(hDlg, &crLayeredColorKey)) {
                WndPropOperationLayeredSetColorKeyCtl(hDlg, crLayeredColorKey);
                if (!WndPropOperationLayeredSet(hDlg))
                    WndPropOperationLayeredGet(hDlg);
            }
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_PICK_PIC, STN_CLICKED)) {
            COLORREF crLayeredKey;
            SetWindowPos(hDlg, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
            if (WndPropOperationOpenPickColorWindow(&crLayeredKey)) {
                WndPropOperationLayeredSetColorKeyCtl(hDlg, crLayeredKey);
                if (!WndPropOperationLayeredSet(hDlg))
                    WndPropOperationLayeredGet(hDlg);
            }
            BringWindowToTop(hDlg);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_VISUALSTYLE_BTN, BN_CLICKED)) {
            HWND    hWnd = AW_GetWndPropHWnd(hDlg);
            TCHAR   szTheme[AW_WNDPROP_OPERATION_THEMT_MAX_CCH + 1];
            LPCWSTR lpszText;
            UINT    uType;
            szTheme[UI_GetDlgItemText(hDlg, IDC_WNDPROP_OPERATION_VISUALSTYLE_COMBOX, szTheme)] = '\0';
            if (SUCCEEDED(SetWindowTheme(hWnd, szTheme, L""))) {
                SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
                UI_Redraw(hWnd);
                lpszText = (LPCWSTR)I18NIndex_OperationSucceeded;
                uType = MB_OK;
            } else {
                lpszText = (LPCWSTR)I18NIndex_OperationFailed;
                uType = MB_OK | MB_ICONERROR;
            }
            KNS_MsgBox(hDlg, lpszText, NULL, uType);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_ANTICAPTURE_CHECK, BN_CLICKED)) {
            HWND hWnd = AW_GetWndPropHWnd(hDlg);
            LRESULT lChecked;
            lChecked = SendMessage((HWND)lParam, BM_GETCHECK, 0, 0);
            if (!UI_SetWindowDisplayAffinity(hWnd, lChecked == BST_CHECKED ? WDA_EXCLUDEFROMCAPTURE : WDA_NONE))
                SendMessage((HWND)lParam, BM_SETCHECK, lChecked == BST_CHECKED ? BST_UNCHECKED : BST_CHECKED, 0);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_SWITCHTO_BTN, BN_CLICKED)) {
            HWND hWnd = AW_GetWndPropHWnd(hDlg);
            if (IsIconic(hWnd))
                OpenIcon(hWnd);
            BringWindowToTop(hWnd);
            SetFocus(hWnd);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_REDRAW_BTN, BN_CLICKED)) {
            RedrawWindow(AW_GetWndPropHWnd(hDlg), NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ERASENOW | RDW_UPDATENOW | RDW_ALLCHILDREN);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_CLOSE_BTN, BN_CLICKED)) {
            DWORD_PTR dwResult;
            AW_SendMsgTO(AW_GetWndPropHWnd(hDlg), WM_CLOSE, 0, 0, &dwResult);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_OPERATION_ENDTASK_BTN, BN_CLICKED)) {
            EndTask(AW_GetWndPropHWnd(hDlg), FALSE, TRUE);
        }
    } else if (uMsg == WM_HSCROLL) {
        if (lParam == (LPARAM)GetDlgItem(hDlg, IDC_WNDPROP_OPERATION_OPACITY_SLIDER))
            if (!WndPropOperationLayeredSet(hDlg))
                WndPropOperationLayeredGet(hDlg);
    } else if (uMsg == WM_DRAWITEM) {
        if (wParam == IDC_WNDPROP_OPERATION_COLORKEY_PIC) {
            PDRAWITEMSTRUCT lpstDrawItem = (PDRAWITEMSTRUCT)lParam;
            RECT            rcInner;
            GDI_FillSolidRect(lpstDrawItem->hDC, &lpstDrawItem->rcItem, RGB(0, 0, 0));
            rcInner.left = lpstDrawItem->rcItem.left + AW_WNDPROP_OPERATION_COLORKEY_BORDER;
            rcInner.top = lpstDrawItem->rcItem.top + AW_WNDPROP_OPERATION_COLORKEY_BORDER;
            rcInner.right = lpstDrawItem->rcItem.right - AW_WNDPROP_OPERATION_COLORKEY_BORDER;
            rcInner.bottom = lpstDrawItem->rcItem.bottom - AW_WNDPROP_OPERATION_COLORKEY_BORDER;
            GDI_FillSolidRect(lpstDrawItem->hDC, &rcInner, (COLORREF)(DWORD_PTR)GetProp(lpstDrawItem->hwndItem, AW_WNDPROP_OPERATION_COLORKEY_PROP));
        }
    } else
        return FALSE;
    return TRUE;
}