#include "AlleyWind.h"

#define AW_FINDWND_CAPTUREBORDER 2

I18N_CTLTEXT astFindWndTextCtl[] = {
    { IDC_FINDWND_CAPTION_CHECK, I18NIndex_Caption },
    { IDC_FINDWND_CLASS_CHECK, I18NIndex_Class },
    { IDC_FINDWND_RECT_TEXT, I18NIndex_Rectangle },
    { IDC_FINDWND_HANDLE_CHECK, I18NIndex_Handle },
    { IDC_FINDWND_CAPTURE_TEXT, I18NIndex_Capture },
    { IDC_FINDWND_THOROUGHSEARCH_CHECK, I18NIndex_SearchChild },
    { IDC_FINDWND_OK_BTN, I18NIndex_OK }
};

CRITICAL_SECTION    csFindWndCapture;
DLG_SCREENSNAPSHOT  stFindWndCaptureScreenSnapshot = { CaptureWndProc, NULL, NULL, 0, WS_POPUP | WS_VISIBLE, WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT };
HWND                hFindWndTarget;
BOOL                bFindWndThoroughSearch;

BLENDFUNCTION       stFindWndCaptureBlendFunc = { AC_SRC_OVER, 0, 128, 0 };

VOID AW_OpenFindWndDlg(HWND hDlg) {
    DialogBoxParam(IMAGE_BASE, MAKEINTRESOURCE(IDD_FINDWND), hDlg, FindWndDlgProc, (LPARAM)hDlg);
}

VOID FindWndInit() {
    RtlInitializeCriticalSection(&csFindWndCapture);
    stFindWndCaptureScreenSnapshot.hCursor = LoadImage(IMAGE_BASE, MAKEINTRESOURCE(IDC_CAPTURE), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE);
    stFindWndCaptureScreenSnapshot.hInstance = IMAGE_BASE;
}

VOID FindWndUninit() {
    DestroyCursor(stFindWndCaptureScreenSnapshot.hCursor);
}

LRESULT CALLBACK CaptureWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_PAINT) {
        UI_WINDBPAINT   stPaint;
        UI_BeginPaint(hWnd, &stPaint);
        GdiAlphaBlend(
            stPaint.DC,
            0,
            0,
            stFindWndCaptureScreenSnapshot.iScreenCX,
            stFindWndCaptureScreenSnapshot.iScreenCY,
            stFindWndCaptureScreenSnapshot.hdcMirror,
            0,
            0,
            stFindWndCaptureScreenSnapshot.iScreenCX,
            stFindWndCaptureScreenSnapshot.iScreenCY,
            stFindWndCaptureBlendFunc);
        if (hFindWndTarget) {
            RECT    rc;
            if (UI_GetRelativeRect(hFindWndTarget, hWnd, &rc)) {
                BitBlt(
                    stPaint.DC,
                    rc.left,
                    rc.top,
                    rc.right - rc.left,
                    rc.bottom - rc.top,
                    stFindWndCaptureScreenSnapshot.hdcMirror,
                    rc.left,
                    rc.top,
                    SRCCOPY);
                GDI_FrameRect(stPaint.DC, &rc, -AW_FINDWND_CAPTUREBORDER, DSTINVERT);
            }
        }
        UI_EndPaint(hWnd, &stPaint);
        return 0;
    } else if (uMsg == WM_MOUSEMOVE) {
        POINT   ptScreen, pt;
        HWND    hWndHover, hWndParent;
        // Obtain screen point
        hWndParent = GetDesktopWindow();
        ptScreen.x = GET_X_LPARAM(lParam);
        ptScreen.y = GET_Y_LPARAM(lParam);
        ClientToScreen(hWnd, &ptScreen);
        // Search child window
        hWndHover = NULL;
        if (bFindWndThoroughSearch) {
            while (TRUE) {
                pt.x = ptScreen.x;
                pt.y = ptScreen.y;
                ScreenToClient(hWndParent, &pt);
                hWndHover = ChildWindowFromPointEx(hWndParent, pt, CWP_SKIPINVISIBLE | CWP_SKIPTRANSPARENT);
                if (!hWndHover) {
                    hWndHover = hWndParent;
                    break;
                } else if (hWndHover == hWndParent) {
                    break;
                } else
                    hWndParent = hWndHover;
            }
        } else {
            ScreenToClient(hWndParent, &ptScreen);
            hWndHover = ChildWindowFromPointEx(hWndParent, ptScreen, CWP_SKIPINVISIBLE | CWP_SKIPTRANSPARENT);
        }
        // Update window
        if (hWndHover != hFindWndTarget) {
            hFindWndTarget = hWndHover;
            UI_Redraw(hWnd);
        }
        return 0;
    } else if (uMsg == WM_LBUTTONUP) {
        DestroyWindow(hWnd);
        return 0;
    } else if (uMsg == WM_KEYUP) {
        if (wParam == VK_CANCEL || wParam == VK_ESCAPE || wParam == VK_RETURN) {
            if (wParam != VK_RETURN)
                hFindWndTarget = NULL;
            DestroyWindow(hWnd);
        }
        return 0;
    } else
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

HWND FindWndOpenCaptureWindow(BOOL bThorough) {
    RtlEnterCriticalSection(&csFindWndCapture);
    bFindWndThoroughSearch = bThorough;
    hFindWndTarget = NULL;
    Dlg_ScreenSnapshot(&stFindWndCaptureScreenSnapshot);
    RtlLeaveCriticalSection(&csFindWndCapture);
    return hFindWndTarget;
}

VOID FindWndUpdateHandle(HWND hDlg) {
    TCHAR       szHandle[sizeof(DWORD) * 2 + 2];
    LONG_PTR    lResult;
    HWND        hWnd, hBtnOK;
    lResult = UI_GetDlgItemText(hDlg, IDC_FINDWND_HANDLE_EDIT, szHandle);
    szHandle[lResult] = '\0';
    hBtnOK = GetDlgItem(hDlg, IDC_FINDWND_OK_BTN);
    I18N_SetWndText(hBtnOK, I18NIndex_OK);
    if (Str_HexToHWnd(szHandle, &hWnd) && IsWindow(hWnd)) {
        EnableWindow(hBtnOK, TRUE);
        AW_SetWndPropHWnd(hDlg, hWnd);
    } else {
        EnableWindow(hBtnOK, FALSE);
        AW_RemoveWndPropHWnd(hDlg);
    }
}

VOID FindWndCheckItem(HWND hDlg, UINT uCtlID, BOOL bSetCheck, BOOL bCheck) {
    HWND hBtnOK = GetDlgItem(hDlg, IDC_FINDWND_OK_BTN);
    if (bSetCheck)
        UI_SetDlgButtonCheck(hDlg, uCtlID, bCheck);
    if (uCtlID == IDC_FINDWND_CAPTION_CHECK || uCtlID == IDC_FINDWND_CLASS_CHECK) {
        if (bCheck) {
            FindWndCheckItem(hDlg, IDC_FINDWND_HANDLE_CHECK, TRUE, FALSE);
            I18N_SetWndText(hBtnOK, I18NIndex_Find);
            EnableWindow(hBtnOK, TRUE);
        } else if (UI_GetDlgButtonCheck(hDlg, uCtlID == IDC_FINDWND_CAPTION_CHECK ? IDC_FINDWND_CLASS_CHECK : IDC_FINDWND_CAPTION_CHECK) == BST_UNCHECKED)
            EnableWindow(hBtnOK, FALSE);
        UI_SendDlgItemMsg(hDlg, uCtlID == IDC_FINDWND_CAPTION_CHECK ? IDC_FINDWND_CAPTION_EDIT : IDC_FINDWND_CLASS_EDIT, EM_SETREADONLY, !bCheck, 0);
    } else if (uCtlID == IDC_FINDWND_HANDLE_CHECK) {
        if (bCheck) {
            FindWndCheckItem(hDlg, IDC_FINDWND_CAPTION_CHECK, TRUE, FALSE);
            FindWndCheckItem(hDlg, IDC_FINDWND_CLASS_CHECK, TRUE, FALSE);
            FindWndUpdateHandle(hDlg);
        } else
            EnableWindow(hBtnOK, FALSE);
        UI_SendDlgItemMsg(hDlg, IDC_FINDWND_HANDLE_EDIT, EM_SETREADONLY, !bCheck, 0);
    }
}

INT_PTR WINAPI FindWndDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_INITDIALOG) {
        KNS_SetDialogSubclass(hDlg, NULL);
        I18N_InitCtlTexts(hDlg, astFindWndTextCtl);
        SendMessage(hDlg, WM_SETTEXT, 0, (LPARAM)I18N_GetString(I18NIndex_FindWindow));
        UI_SetWindowIcon(hDlg, KNS_GetIcon());
        UI_SendDlgItemMsg(hDlg, IDC_FINDWND_CAPTURE_PIC, STM_SETIMAGE, IMAGE_CURSOR, (LPARAM)stFindWndCaptureScreenSnapshot.hCursor);
    } else if (uMsg == WM_COMMAND) {
        if (wParam == MAKEWPARAM(IDC_FINDWND_CAPTURE_PIC, STN_CLICKED)) {
            HWND        hWnd;
            TCHAR       szBuffer[1024];
            INT         iTemp;
            RECT        rcTemp;
            BOOL        bTemp;
            SetWindowPos(hDlg, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
            hWnd = FindWndOpenCaptureWindow(UI_GetDlgButtonCheck(hDlg, IDC_FINDWND_THOROUGHSEARCH_CHECK) == BST_CHECKED);
            if (hWnd) {
                FindWndCheckItem(hDlg, IDC_FINDWND_HANDLE_CHECK, TRUE, TRUE);
                AW_SetPropCtlFormat(hDlg, IDC_FINDWND_HANDLE_EDIT, TRUE, TEXT("%08X"), (DWORD)(DWORD_PTR)hWnd);
                AW_GetWindowText(hWnd, szBuffer);
                AW_SetPropCtlString(hDlg, IDC_FINDWND_CAPTION_EDIT, szBuffer, TRUE);
                iTemp = GetClassName(hWnd, szBuffer, ARRAYSIZE(szBuffer));
                AW_SetPropCtlString(hDlg, IDC_FINDWND_CLASS_EDIT, szBuffer, iTemp != 0);
                bTemp = UI_GetRelativeRect(hWnd, NULL, &rcTemp);
                AW_SetPropCtlRect(hDlg, IDC_FINDWND_RECT_EDIT, &rcTemp, bTemp);
            }
            BringWindowToTop(hDlg);
        } else if (wParam == MAKEWPARAM(IDC_FINDWND_CAPTION_CHECK, BN_CLICKED) ||
            wParam == MAKEWPARAM(IDC_FINDWND_CLASS_CHECK, BN_CLICKED) ||
            wParam == MAKEWPARAM(IDC_FINDWND_HANDLE_CHECK, BN_CLICKED)) {
            FindWndCheckItem(hDlg, LOWORD(wParam), FALSE, SendMessage((HWND)lParam, BM_GETCHECK, 0, 0) == BST_CHECKED);
        } else if (wParam == MAKEWPARAM(IDC_FINDWND_OK_BTN, BN_CLICKED)) {
            HWND    hWnd = AW_GetWndPropHWnd(hDlg);
            if (UI_GetDlgButtonCheck(hDlg, IDC_FINDWND_HANDLE_CHECK) == BST_CHECKED) {
                AW_LocateWindowInTree(hWnd);
                AW_OpenWndPropDlg(hWnd);
            } else {
                TCHAR   szFindCaptionName[MAX_WNDCAPTION_CCH], szFindClassName[MAX_CLASSNAME_CCH];
                LPTSTR  lpszFindCaptionName, lpszFindClassName;
                if (UI_GetDlgButtonCheck(hDlg, IDC_FINDWND_CAPTION_CHECK) == BST_CHECKED) {
                    UI_GetDlgItemText(hDlg, IDC_FINDWND_CAPTION_EDIT, szFindCaptionName);
                    lpszFindCaptionName = szFindCaptionName;
                } else
                    lpszFindCaptionName = NULL;
                if (UI_GetDlgButtonCheck(hDlg, IDC_FINDWND_CLASS_CHECK) == BST_CHECKED) {
                    UI_GetDlgItemText(hDlg, IDC_FINDWND_CLASS_EDIT, szFindClassName);
                    lpszFindClassName = szFindClassName;
                } else
                    lpszFindClassName = NULL;
                AW_LoadWindowTreeAsync(TRUE, lpszFindCaptionName, lpszFindClassName);
            }
            EndDialog(hDlg, 0);
        } else if (wParam == MAKEWPARAM(IDC_FINDWND_HANDLE_EDIT, EN_CHANGE)) {
            FindWndUpdateHandle(hDlg);
        }
        SetWindowLongPtr(hDlg, DWLP_MSGRESULT, 0);
    } else if (uMsg == WM_CLOSE) {
        EndDialog(hDlg, 0);
        SetWindowLongPtr(hDlg, DWLP_MSGRESULT, 0);
    } else
        return FALSE;
    return TRUE;
}