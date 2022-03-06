#include "AlleyWind.h"

I18N_CTLTEXT astWndPropResourceTextCtl[] = {
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
        iCch = Str_Printf(szBuffer, TEXT("#%u"), LOWORD(lpszProp));
        stLVItem.pszText = iCch > 0 ? szBuffer : I18N_GetString(I18NIndex_NotApplicable);
    } else
        stLVItem.pszText = lpszProp;
    stLVItem.iItem = MAXINT;
    stLVItem.iSubItem = 0;
    stLVItem.iItem = (INT)SendMessage((HWND)lParam, LVM_INSERTITEM, 0, (LPARAM)&stLVItem);
    if (stLVItem.iItem != -1) {
        stLVItem.iSubItem++;
        iCch = Str_Printf(szBuffer, TEXT("%p"), hData);
        stLVItem.pszText = iCch > 0 ? szBuffer : I18N_GetString(I18NIndex_NotApplicable);
        SendMessage((HWND)lParam, LVM_SETITEM, 0, (LPARAM)&stLVItem);
    }
    return TRUE;
}

VOID WndPropResourceGetFont(HWND hDlg, HWND hWnd) {
    DWORD_PTR   dwpTemp;
    LRESULT     lResult = AW_SendMsgTO(hWnd, WM_GETFONT, 0, 0, &dwpTemp);
    AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_RESOURCE_HFONT_EDIT, lResult != 0, TEXT("%p"), (HFONT)dwpTemp);
    UI_EnableDlgItem(hDlg, IDC_WNDPROP_RESOURCE_HFONT_BTN, dwpTemp != 0);
}

INT_PTR WINAPI WndPropResourceDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_INITDIALOG) {
        HWND        hWnd, hCtl;
        LRESULT     lResult;
        BOOL        bSucc, bStyleSucc;
        DWORD_PTR   dwpStyle, dwpTemp;
        RECT        rcClient;
        BOOL        bImageAvailable;
        hWnd = (HWND)lParam;
        AW_SetWndPropHWnd(hDlg, hWnd);
        // Initialize
        KNS_SetDialogSubclass(hDlg, NULL);
        I18N_InitCtlTexts(hDlg, astWndPropResourceTextCtl);
        bSucc = UI_GetWindowLong(hWnd, FALSE, GWL_STYLE, &dwpStyle);
        bStyleSucc = bSucc;
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
        bSucc = UI_GetWindowLong(hWnd, FALSE, GWLP_HINSTANCE, &dwpTemp);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_RESOURCE_HINSTANCE_EDIT, bSucc, TEXT("%p"), (HINSTANCE)dwpTemp);
        // hFont
        WndPropResourceGetFont(hDlg, hWnd);
        // hMenu
        if (!bStyleSucc || dwpStyle & WS_CHILD)
            UI_EnableDlgItem(hDlg, IDC_WNDPROP_RESOURCE_HMENU_EDIT, FALSE);
        else
            AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_RESOURCE_HMENU_EDIT, TRUE, TEXT("%p"), GetMenu(hWnd));
        // hIcon
        lResult = AW_SendMsgTO(hWnd, WM_GETICON, 0, 0, &dwpTemp);
        AW_SetPropCtlFormat(hDlg, IDC_WNDPROP_RESOURCE_ICON_EDIT, lResult != 0, TEXT("%p"), (HICON)dwpTemp);
        // Hot Key
        hCtl = GetDlgItem(hDlg, IDC_WNDPROP_RESOURCE_HOTKEY_EDIT);
        lResult = AW_SendMsgTO(hWnd, WM_GETHOTKEY, 0, 0, &dwpTemp);
        if (lResult)
            SendMessage(hCtl, HKM_SETHOTKEY, LOWORD(dwpTemp), 0);
        else
            EnableWindow(hCtl, FALSE);
        // Property List
        hCtl = GetDlgItem(hDlg, IDC_WNDPROP_RESOURCE_PROP_LIST);
        Ctl_InitListCtl(hCtl, aPropListCol, LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);
        EnumPropsEx(hWnd, WndPropResourcePropEnumProc, (LPARAM)hCtl);
    } else if (uMsg == WM_COMMAND) {
        if (wParam == MAKEWPARAM(IDC_WNDPROP_RESOURCE_HFONT_BTN, BN_CLICKED)) {
            HWND        hWnd;
            LRESULT     lResult;
            HFONT       hFont;
            LOGFONTW    stLogFont;
            DWORD       dwProcessId;
            BOOL        bChosen;
            hWnd = AW_GetWndPropHWnd(hDlg);
            lResult = AW_SendMsgTO(hWnd, WM_GETFONT, 0, 0, (PDWORD_PTR)&hFont);
            if (!lResult || GetObject((HFONT)hFont, sizeof(stLogFont), &stLogFont) == 0)
                RtlZeroMemory(&stLogFont, sizeof(stLogFont));
            bChosen = Dlg_ChooseFont(hDlg, &stLogFont, NULL);
            if (hFont) {
                GetWindowThreadProcessId(hWnd, &dwProcessId);
                if (dwProcessId != NT_GetTEBMember(ClientId.UniqueProcess))
                    DeleteObject(hFont);
            }
            if (bChosen) {
                HANDLE  hProc;
                hProc = UI_OpenProc(PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE | SYNCHRONIZE, hWnd);
                if (hProc) {
                    // Create new font
                    HIJACK_CALLPROCHEADER   stCFICallProc;
                    if (!NT_SUCCESS(
                        Hijack_LoadProcAddr(
                            hProc,
                            L"gdi32.dll",
                            "CreateFontIndirectW",
                            (PVOID*)&stCFICallProc.Procedure,
                            AWSettings_GetItemValueEx(AWSetting_ResponseTimeout)))
                        )
                        goto Label_0;
                    HIJACK_CALLPROCPARAM    stCFIParams[] = {
                        { (DWORD_PTR)&stLogFont, sizeof(stLogFont), FALSE }
                    };
                    stCFICallProc.CallConvention = 0;
                    stCFICallProc.ParamCount = ARRAYSIZE(stCFIParams);
                    if (!NT_SUCCESS(
                        Hijack_CallProc(
                            hProc,
                            &stCFICallProc,
                            stCFIParams,
                            AWSettings_GetItemValueEx(AWSetting_ResponseTimeout)
                        )) || !stCFICallProc.RetValue)
                        goto Label_0;
                    // Apply new font created
                    HIJACK_CALLPROCHEADER   stSMWCallProc;
                    if (!NT_SUCCESS(
                        Hijack_LoadProcAddr(
                            hProc,
                            L"user32.dll",
                            "SendMessageW",
                            (PVOID*)&stSMWCallProc.Procedure,
                            AWSettings_GetItemValueEx(AWSetting_ResponseTimeout)))
                        )
                        goto Label_0;
                    HIJACK_CALLPROCPARAM    stSMWParams[] = {
                        { (DWORD)(DWORD_PTR)hWnd, 0, FALSE },
                        { WM_SETFONT, 0, FALSE },
                        { stCFICallProc.RetValue, 0, FALSE },
                        { TRUE, 0, FALSE }
                    };
                    stSMWCallProc.CallConvention = 0;
                    stSMWCallProc.ParamCount = ARRAYSIZE(stSMWParams);
                    Hijack_CallProc(
                        hProc,
                        &stSMWCallProc,
                        stSMWParams,
                        AWSettings_GetItemValueEx(AWSetting_ResponseTimeout)
                    );
                }
            Label_0:
                NtClose(hProc);
                WndPropResourceGetFont(hDlg, hWnd);
            }
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_RESOURCE_IMAGE_BTN, BN_CLICKED)) {
            RECT rcBtn;
            if (UI_GetWindowRect((HWND)lParam, &rcBtn)) {
                Ctl_PopupMenu(hWndPropResourceImage, rcBtn.right, rcBtn.top, hDlg);
            }
        } else if (wParam == MAKEWPARAM(IDM_IMAGE_SAVE, 0) || wParam == MAKEWPARAM(IDM_IMAGE_COPY, 0)) {
            TCHAR           szExpImageFileName[MAX_PATH];
            HWND            hWnd;
            SIZE_T          uSize;
            FILE_MAP        stFileMap;
            GDI_SNAPSHOT    stSnapshot;
            hWnd = AW_GetWndPropHWnd(hDlg);
            if (GDI_CreateSnapshot(hWnd == GetDesktopWindow() ? NULL : hWnd, &stSnapshot)) {
                SelectObject(stSnapshot.DC, stSnapshot.OriginalBitmap);
                if (wParam == MAKEWPARAM(IDM_IMAGE_SAVE, 0)) {
                    uSize = GDI_WriteBitmap(stSnapshot.DC, stSnapshot.Bitmap, NULL);
                    if (uSize) {
                        szExpImageFileName[0] = '\0';
                        if (Dlg_GetSaveFileName(hDlg, I18N_GetString(I18NIndex_SaveBitmapFilter), szExpImageFileName, lpszExpImageFileExt)) {
                            if (NT_SUCCESS(File_Map(szExpImageFileName, NULL, &stFileMap, uSize, FILE_READ_DATA | FILE_WRITE_DATA | SYNCHRONIZE, FILE_SHARE_READ, FILE_SUPERSEDE, FALSE, ViewUnmap))) {
                                if (!GDI_WriteBitmap(stSnapshot.DC, stSnapshot.Bitmap, stFileMap.Mem.VirtualAddress))
                                    File_Dispose(stFileMap.FileHandle, TRUE);
                                File_Unmap(&stFileMap);
                            }
                        }
                    }
                } else {
                    OpenClipboard(hDlg);
                    EmptyClipboard();
                    SetClipboardData(CF_BITMAP, stSnapshot.Bitmap);
                    CloseClipboard();
                }
                GDI_DeleteSnapshot(&stSnapshot);
            }
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_RESOURCE_HOTKEY_EDIT, EN_CHANGE) && !UI_GetNoNotifyFlag((HWND)lParam)) {
            HWND        hWnd;
            WORD        wHotkey;
            DWORD_PTR   dwpTemp;
            hWnd = AW_GetWndPropHWnd(hDlg);
            wHotkey = LOWORD(SendMessage((HWND)lParam, HKM_GETHOTKEY, 0, 0));
            if (!AW_SendMsgTO(hWnd, WM_SETHOTKEY, wHotkey, 0, &dwpTemp) || dwpTemp <= 0) {
                if (AW_SendMsgTO(hWnd, WM_GETHOTKEY, 0, 0, &dwpTemp)) {
                    UI_SetNoNotifyFlag(hWnd, TRUE);
                    SendMessage((HWND)lParam, HKM_SETHOTKEY, LOWORD(dwpTemp), 0);
                    UI_SetNoNotifyFlag(hWnd, FALSE);
                } else
                    EnableWindow((HWND)lParam, FALSE);
            }
        }
    } else
        return FALSE;
    return TRUE;
}