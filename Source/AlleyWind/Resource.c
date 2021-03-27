#include "AlleyWind.h"

I18N_TEXTCTL astWndPropResourceTextCtl[] = {
    { IDC_WNDPROP_RESOURCE_IMAGE_TEXT, I18NIndex_ClientAreaImage },
    { IDC_WNDPROP_RESOURCE_HINSTANCE_TEXT, I18NIndex_InstanceHandle },
    { IDC_WNDPROP_RESOURCE_HFONT_TEXT, I18NIndex_FontHandle },
    { IDC_WNDPROP_RESOURCE_HMENU_TEXT, I18NIndex_MenuHandle },
    { IDC_WNDPROP_RESOURCE_ICON_TEXT, I18NIndex_Icons },
    { IDC_WNDPROP_RESOURCE_HOTKEY_TEXT, I18NIndex_HotKey },
    { IDC_WNDPROP_RESOURCE_PROP_TEXT, I18NIndex_PropertyList }
};

#define IDM_IMAGE_COPY 1
#define IDM_IMAGE_SAVE 2

HMENU hWndPropResourceImage;

CTL_MENU stMenuImage[] = {
    { MF_STRING, IDM_IMAGE_COPY, I18NIndex_Copy, NULL, 0 },
    { MF_STRING, IDM_IMAGE_SAVE, I18NIndex_Save, NULL, 0 }
};

CTL_LISTCTL_COLUME aPropListCol[] = {
    {I18NIndex_Entry, 180},
    {I18NIndex_Data, 180}
};

LPTSTR lpszExpImageFileExt = TEXT("bmp");

VOID WndPropResourceInit() {
    hWndPropResourceImage = CreatePopupMenu();
    Ctl_CreateMenu(stMenuImage, hWndPropResourceImage);
}

VOID WndPropResourceUninit() {
    Ctl_DestroyMenu(stMenuImage, hWndPropResourceImage);
}

BOOL CALLBACK WndPropResourcePropEnumProc(HWND hWnd, LPTSTR lpszProp, HANDLE hData, ULONG_PTR lParam) {
    TCHAR   szBuffer[1024];
    LVITEM  stLVItem;
    INT     iCch;
    stLVItem.mask = LVIF_TEXT;
    if (IS_ATOM(lpszProp)) {
        iCch = Str_CchPrintf(szBuffer, TEXT("#%u"), LOWORD(lpszProp));
        stLVItem.pszText = iCch > 0 ? szBuffer : I18N_GetString(I18NIndex_NotApplicable);
    } else
        stLVItem.pszText = lpszProp;
    stLVItem.iItem = MAXINT;
    stLVItem.iSubItem = 0;
    stLVItem.iItem = (INT)SendMessage((HWND)lParam, LVM_INSERTITEM, 0, (LPARAM)&stLVItem);
    if (stLVItem.iItem != -1) {
        stLVItem.iSubItem++;
        iCch = Str_CchPrintf(szBuffer, TEXT("%p"), hData);
        stLVItem.pszText = iCch > 0 ? szBuffer : I18N_GetString(I18NIndex_NotApplicable);
        SendMessage((HWND)lParam, LVM_SETITEM, 0, (LPARAM)&stLVItem);
    }
    return TRUE;
}

INT_PTR WINAPI WndPropResourceDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_INITDIALOG) {
        HWND        hWnd, hCtl;
        LRESULT     lResult;
        DWORD       dwStyle, dwStyleError;
        DWORD_PTR   dwTemp;
        RECT        rcClient;
        BOOL        bImageAvailable;
        hWnd = (HWND)lParam;
        AW_SetWndPropHWnd(hDlg, hWnd);
        // Initialize
        KNS_DialogSetSubclass(hDlg);
        I18N_InitTextCtls(hDlg, astWndPropResourceTextCtl);
        NT_LastErrorClear();
        dwStyle = (DWORD)GetWindowLongPtr(hWnd, GWL_STYLE);
        dwStyleError = NT_LastErrorGet();
        // Client Area Image
        if (hWnd == GetDesktopWindow()) {
            rcClient.right = GetSystemMetrics(SM_CXVIRTUALSCREEN);
            rcClient.bottom = GetSystemMetrics(SM_CYVIRTUALSCREEN);
            bImageAvailable = TRUE;
        } else
            bImageAvailable = GetClientRect(hWnd, &rcClient) && rcClient.right > 0 && rcClient.bottom > 0 && IsWindowVisible(hWnd) && !IsIconic(hWnd);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_RESOURCE_IMAGE_EDIT, bImageAvailable, TEXT("%ldx%ld"), rcClient.right, rcClient.bottom);
        UI_EnableDlgItem(hDlg, IDC_WNDPROP_RESOURCE_IMAGE_BTN, bImageAvailable);
        // hInstance
        NT_LastErrorClear();
        dwTemp = GetWindowLongPtr(hWnd, GWLP_HINSTANCE);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_RESOURCE_HINSTANCE_EDIT, dwTemp || NT_LastErrorSucceed(), TEXT("%p"), (HINSTANCE)dwTemp);
        // hFont
        lResult = AW_SendMsgTO(hWnd, WM_GETFONT, 0, 0, &dwTemp);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_RESOURCE_HFONT_EDIT, lResult != 0, TEXT("%p"), (HFONT)dwTemp);
        UI_EnableDlgItem(hDlg, IDC_WNDPROP_RESOURCE_HFONT_BTN, dwTemp != 0);
        // hMenu
        if (dwStyleError != ERROR_SUCCESS || dwStyle & WS_CHILD)
            UI_EnableDlgItem(hDlg, IDC_WNDPROP_RESOURCE_HMENU_EDIT, FALSE);
        else
            AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_RESOURCE_HMENU_EDIT, TRUE, TEXT("%p"), GetMenu(hWnd));
        // hIcon
        lResult = AW_SendMsgTO(hWnd, WM_GETICON, 0, 0, &dwTemp);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_RESOURCE_ICON_EDIT, lResult != 0, TEXT("%p"), (HICON)dwTemp);
        // Hot Key
        hCtl = GetDlgItem(hDlg, IDC_WNDPROP_RESOURCE_HOTKEY_EDIT);
        lResult = AW_SendMsgTO(hWnd, WM_GETHOTKEY, 0, 0, &dwTemp);
        if (lResult)
            SendMessage(hCtl, HKM_SETHOTKEY, LOWORD(dwTemp), 0);
        else
            EnableWindow(hCtl, FALSE);
        // Property List
        hCtl = GetDlgItem(hDlg, IDC_WNDPROP_RESOURCE_PROP_LIST);
        Ctl_InitListCtlEx(hCtl, ARRAYSIZE(aPropListCol), aPropListCol, LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);
        EnumPropsEx(hWnd, WndPropResourcePropEnumProc, (LPARAM)hCtl);
    } else if (uMsg == WM_COMMAND) {
        if (wParam == MAKEWPARAM(IDC_WNDPROP_RESOURCE_HFONT_BTN, BN_CLICKED)) {
            HWND    hWnd;
            LRESULT lResult;
            HFONT   hFont;
            LOGFONT stLogFont;
            DWORD   dwProcessId;
            hWnd = AW_GetWndPropHWnd(hDlg);
            lResult = AW_SendMsgTO(hWnd, WM_GETFONT, 0, 0, (PDWORD_PTR)&hFont);
            if (!lResult || GetObject((HFONT)hFont, sizeof(stLogFont), &stLogFont) == 0)
                RtlZeroMemory(&stLogFont, sizeof(stLogFont));
            Dlg_ChooseFont(hDlg, &stLogFont, NULL);
            if (hFont) {
                GetWindowThreadProcessId(hWnd, &dwProcessId);
                if (dwProcessId != NT_GetTEBMember(ClientId.UniqueProcess))
                    DeleteObject(hFont);
            }
            /*if (UI_GetFont(hDlg, &stLogFont, NULL)) {
                hFont = CreateFontIndirect(&stLogFont);
                if (hFont) {
                    lResult = AW_SendMsgTO(hWnd, WM_SETFONT, (WPARAM)hFont, TRUE, (PDWORD_PTR)&hFont);
                    if (lResult) {
                        lResult = AW_SendMsgTO(hWnd, WM_GETFONT, 0, 0, (PDWORD_PTR)&hFont);
                        AW_SetPropCtlValue(hDlg, IDC_WNDPROP_RESOURCE_HFONT_EDIT, TEXT("%08X"), (LONG_PTR)hFont, lResult != 0);
                    }
                }
            }*/
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_RESOURCE_IMAGE_BTN, BN_CLICKED)) {
            RECT rcBtn;
            if (GetWindowRect((HWND)lParam, &rcBtn)) {
                Ctl_PopupMenu(hWndPropResourceImage, rcBtn.right, rcBtn.top, hDlg);
            }
        } else if (wParam == MAKEWPARAM(IDM_IMAGE_SAVE, 0) || wParam == MAKEWPARAM(IDM_IMAGE_COPY, 0)) {
            TCHAR       szExpImageFileName[MAX_PATH];
            HWND        hWnd;
            HDC         hDC, hMemDC;
            HBITMAP     hBmp, hMemBmp;
            SIZE_T      uSize;
            FILE_MAP    stFileMap;
            RECT        rcWnd; // right and bottom are corresponding to CX and CY
            hWnd = AW_GetWndPropHWnd(hDlg);
            if (hWnd == GetDesktopWindow()) {
                hWnd = NULL;
                rcWnd.left = GetSystemMetrics(SM_XVIRTUALSCREEN);
                rcWnd.top = GetSystemMetrics(SM_YVIRTUALSCREEN);
                rcWnd.right = GetSystemMetrics(SM_CXVIRTUALSCREEN);
                rcWnd.bottom = GetSystemMetrics(SM_CYVIRTUALSCREEN);
            } else
                GetClientRect(hWnd, &rcWnd);
            hDC = GetDC(hWnd);
            hMemDC = CreateCompatibleDC(hDC);
            hMemBmp = CreateCompatibleBitmap(hDC, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top);
            SelectObject(hMemDC, hMemBmp);
            BitBlt(hMemDC, 0, 0, rcWnd.right, rcWnd.bottom, hDC, rcWnd.left, rcWnd.top, SRCCOPY);
            hBmp = (HBITMAP)GetCurrentObject(hMemDC, OBJ_BITMAP);
            if (wParam == MAKEWPARAM(IDM_IMAGE_SAVE, 0)) {
                if (hBmp && NT_SUCCESS(GDI_WriteBitmap(hDC, hBmp, NULL, 0, &uSize)) && uSize) {
                    szExpImageFileName[0] = '\0';
                    if (Dlg_GetSaveFileName(hDlg, I18N_GetString(I18NIndex_SaveBitmapFilter), szExpImageFileName, lpszExpImageFileExt)) {
                        if (NT_SUCCESS(File_Map(szExpImageFileName, NULL, &stFileMap, uSize, FILE_READ_DATA | FILE_WRITE_DATA | SYNCHRONIZE, FILE_SHARE_READ, FILE_SUPERSEDE, TRUE, ViewUnmap))) {
                            GDI_WriteBitmap(hDC, hBmp, stFileMap.Mem.VirtualAddress, uSize, &uSize);
                            stFileMap.Mem.NumberOfBytes = uSize;
                            File_Unmap(&stFileMap);
                        }
                    }
                }
            } else {
                OpenClipboard(hDlg);
                EmptyClipboard();
                SetClipboardData(CF_BITMAP, hBmp);
                CloseClipboard();
            }
            DeleteDC(hMemDC);
            DeleteObject(hMemBmp);
            ReleaseDC(hWnd, hDC);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_RESOURCE_HOTKEY_EDIT, EN_CHANGE) && !UI_IsSetNoChangeNotify((HWND)lParam)) {
            HWND        hWnd;
            WORD        wHotkey;
            DWORD_PTR   dwpTemp;
            hWnd = AW_GetWndPropHWnd(hDlg);
            wHotkey = LOWORD(SendMessage((HWND)lParam, HKM_GETHOTKEY, 0, 0));
            if (!AW_SendMsgTO(hWnd, WM_SETHOTKEY, wHotkey, 0, &dwpTemp) || dwpTemp <= 0) {
                if (AW_SendMsgTO(hWnd, WM_GETHOTKEY, 0, 0, &dwpTemp)) {
                    UI_SetNoChangeNotify(hWnd, TRUE);
                    SendMessage((HWND)lParam, HKM_SETHOTKEY, LOWORD(dwpTemp), 0);
                    UI_SetNoChangeNotify(hWnd, FALSE);
                } else
                    EnableWindow((HWND)lParam, FALSE);
            }
        }
    } else
        return FALSE;
    return TRUE;
}