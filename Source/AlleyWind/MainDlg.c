#include "AlleyWind.h"

// Menu

// File
#define IDM_OPTIONS 3
#define IDM_EXIT 4

CTL_MENU stMenuFile[] = {
    { MF_STRING, IDM_RELOAD, I18NIndex_MenuReload, NULL, 0 },
    { MF_STRING, IDM_SAVETREE, I18NIndex_MenuSaveTree, NULL, 0 },
    //{ MF_STRING, IDM_OPTIONS, I18NIndex_Options, NULL, 0 },
    { MF_STRING, IDM_EXIT, I18NIndex_MenuExit, NULL, 0 }
};

// Tool

CTL_MENU stMenuTool[] = {
    { MF_STRING, IDM_FINDWND, I18NIndex_MenuFindWindow, NULL, 0 }
};

// Help
#define IDM_HOMEPAGE 20
#define IDM_ABOUT 21

CTL_MENU stMenuHelp[] = {
    { MF_STRING, IDM_HOMEPAGE, I18NIndex_Homepage, NULL, 0 },
    { MF_STRING, IDM_ABOUT, I18NIndex_About, NULL, 0 },
};

// Main
CTL_MENU stDlgMenu[] = {
    { MF_STRING, 0, I18NIndex_File, stMenuFile, ARRAYSIZE(stMenuFile) },
    { MF_STRING, 0, I18NIndex_Tool, stMenuTool, ARRAYSIZE(stMenuTool) },
    { MF_STRING, 0, I18NIndex_Help, stMenuHelp, ARRAYSIZE(stMenuHelp) }
};

#define IDM_REFRESHSEARCH 100
#define IDM_EXITSEARCH 101

CTL_MENU stSearchMenu[] = {
    { MF_STRING, IDM_REFRESHSEARCH, I18NIndex_Refresh, NULL, 0 },
    { MF_STRING, IDM_EXITSEARCH, I18NIndex_Cancel, NULL, 0 }
};

HWND        hMainDlg, hBanner, hTree, hDesktop;
HANDLE      hthrLoadWindowTree = NULL;
HMENU       hSearchMenu;
HICON       hIconOEMWinLogo;
HIMAGELIST  himlIcons;
INT         iTreeItemHeight;

TCHAR       szFindCaptionName[MAX_WNDCAPTION_CCH];
TCHAR       szFindClassName[MAX_CLASSNAME_CCH];
BOOL        bFilter, bFindCaption, bFindClassName;
HTREEITEM   hFilterNode;

LPTSTR      lpszExpTreeFileExt = TEXT("txt");

BOOL CALLBACK ExpTreeItemEnumProc(HWND TreeView, HTREEITEM TreeItem, UINT Level, LPARAM Param) {
    HANDLE  hExpFile;
    TVITEMW stTVI;
    WCHAR   szUniBuff[512];
    CHAR    szUTF8Buff[ARRAYSIZE(szUniBuff) * 2];
    UINT    i;
    SIZE_T  uChWritten;
    hExpFile = (HANDLE)Param;
    stTVI.mask = TVIF_TEXT;
    stTVI.hItem = TreeItem;
    stTVI.cchTextMax = ARRAYSIZE(szUniBuff) - Level;
    for (i = 0; i < Level; i++) {
        szUniBuff[i] = '\t';
        stTVI.cchTextMax--;
    }
    stTVI.pszText = szUniBuff + Level;
    if (SendMessage(hTree, TVM_GETITEMW, 0, (LPARAM)&stTVI)) {
        // Patches C6054: szUniBuff is always zero-terminated here
    #pragma warning(disable: 6054)
        uChWritten = Str_UnicodeToUTF8(szUTF8Buff, szUniBuff);
    #pragma warning(default: 6054)
        szUTF8Buff[uChWritten] = '\r';
        szUTF8Buff[uChWritten + 1] = '\n';
        IO_Write(hExpFile, 0, szUTF8Buff, (ULONG)(uChWritten + 2));
    }
    return TRUE;
}

BOOL CALLBACK InsertWindowToTree(HWND hWnd, PAW_ENUMCHILDREN lpstEnumChildren) {
    AW_ENUMCHILDREN     stEnumChildren;
    TCHAR               szCaption[MAX_WNDCAPTION_CCH], szClassName[MAX_CLASSNAME_CCH];
    TCHAR               szBuffer[sizeof(DWORD) * 2 + ARRAYSIZE(szCaption) + ARRAYSIZE(szClassName) + 16];
    PAW_SYSCLASSINFO    pSysClsInfo;
    HICON               hIcon;
    INT                 iImageIcon, iCch;
    HTREEITEM           hTreeItem = NULL, hParent;
    BOOL                bCaptionMatched, bClassMatched;
    UINT                uCount;
    TVINSERTSTRUCT      stTVIInsert = { 0, TVI_LAST, { TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM } };
    uCount = lpstEnumChildren->uCount;
    bCaptionMatched = bClassMatched = FALSE;
    // Filter Node
    if (bFilter) {
        if (uCount == 0) {
            if (bFindCaption && !bFindClassName)
                iCch = Str_Printf(szBuffer, TEXT("%ws - \"%s\""), I18N_GetString(I18NIndex_SearchResult), szFindCaptionName);
            else if (!bFindCaption && bFindClassName)
                iCch = Str_Printf(szBuffer, TEXT("%ws - %s"), I18N_GetString(I18NIndex_SearchResult), szFindClassName);
            else
                iCch = Str_Printf(szBuffer, TEXT("%ws - \"%s\" %s"), I18N_GetString(I18NIndex_SearchResult), szFindCaptionName, szFindClassName);
            stTVIInsert.item.iImage = 0;
            stTVIInsert.hParent = lpstEnumChildren->hParentNode;
            stTVIInsert.item.pszText = iCch > 0 ? szBuffer : NULL;
            stTVIInsert.item.lParam = (LPARAM)INVALID_HANDLE_VALUE;
            hTreeItem = (HTREEITEM)SendMessage(hTree, TVM_INSERTITEM, 0, (LPARAM)&stTVIInsert);
            hFilterNode = hTreeItem;
            uCount++;
        }
        hParent = hFilterNode;
    } else
        hParent = lpstEnumChildren->hParentNode;
    // Get window info
    AW_GetWindowText(hWnd, szCaption);
    if (bFilter && (!bFindCaption || Str_Index_BF(szCaption, szFindCaptionName) != -1))
        bCaptionMatched = TRUE;
    if (!GetClassName(hWnd, szClassName, ARRAYSIZE(szClassName)))
        szClassName[0] = '\0';
    if (bFilter && (!bFindClassName || Str_Index_BF(szClassName, szFindClassName) != -1))
        bClassMatched = TRUE;
    if (!bFilter || (bCaptionMatched && bClassMatched)) {
        // Format display string
        if (szClassName[0] != '\0') {
            pSysClsInfo = AW_DBFindSysClassInfoByName(szClassName);
            iCch = pSysClsInfo ?
                Str_Printf(szBuffer,
                    TEXT("%08X \"%s\" %s (%ws)"),
                    (DWORD)(DWORD_PTR)hWnd,
                    szCaption,
                    szClassName,
                    IS_INTRESOURCE(pSysClsInfo->DisplayName) ? I18N_GetString((UINT_PTR)pSysClsInfo->DisplayName) : pSysClsInfo->DisplayName) :
                Str_Printf(szBuffer, TEXT("%08X \"%s\" %s"), (DWORD)(DWORD_PTR)hWnd, szCaption, szClassName);
        } else
            iCch = Str_Printf(szBuffer, TEXT("%08X \"%s\""), (DWORD)(DWORD_PTR)hWnd, szCaption);
        // Append node info and icon
        hIcon = NULL;
        if (!(AW_SendMsgTO(hWnd, WM_GETICON, ICON_SMALL, 0, (PDWORD_PTR)&hIcon) && hIcon))
            UI_GetWindowLong(hWnd, TRUE, GCLP_HICON, (PLONG_PTR)&hIcon);
        if (hIcon)
            iImageIcon = ImageList_ReplaceIcon(himlIcons, -1, hIcon);
        stTVIInsert.item.iImage = stTVIInsert.item.iSelectedImage = (!hIcon || iImageIcon == -1) ? 0 : iImageIcon;
        stTVIInsert.hParent = hParent;
        stTVIInsert.item.pszText = iCch > 0 ? szBuffer : NULL;
        stTVIInsert.item.lParam = (LPARAM)PURGE_HWND(hWnd);
        // Insert node to tree and enumerate child windows
        hTreeItem = (HTREEITEM)SendMessage(hTree, TVM_INSERTITEM, 0, (LPARAM)&stTVIInsert);
        if (uCount == 1)
            SendMessage(hTree, TVM_EXPAND, TVE_EXPAND, (LPARAM)hParent);
        uCount++;
        hParent = hTreeItem;
    }
    stEnumChildren.hParentNode = hParent;
    stEnumChildren.uCount = uCount;
    UI_EnumChildWindows(hWnd, (WNDENUMPROC)InsertWindowToTree, (LPARAM)&stEnumChildren);
    return TRUE;
}

DWORD WINAPI LoadWindowTreeThread(LPVOID lParam) {
    AW_ENUMCHILDREN stEnumChildren = { TVI_ROOT, 0 };
    // Reset tree and image list
    SendMessage(hTree, TVM_DELETEITEM, 0, (LPARAM)TVI_ROOT);
    ImageList_Remove(himlIcons, -1);
    ImageList_ReplaceIcon(himlIcons, -1, hIconOEMWinLogo);
    // Build window tree
    InsertWindowToTree(hDesktop, &stEnumChildren);
    // Clean up
    NtClose(hthrLoadWindowTree);
    hthrLoadWindowTree = NULL;
    return 0;
}

BOOL AW_LoadWindowTreeAsync(BOOL bUpdateFilter, LPTSTR lpszCaption, LPTSTR lpszClassName) {
    if (bUpdateFilter) {
        bFindCaption = lpszCaption ? Str_Copy(szFindCaptionName, lpszCaption), TRUE : FALSE;
        bFindClassName = lpszClassName ? Str_Copy(szFindClassName, lpszClassName), TRUE : FALSE;
        bFilter = bFindCaption || bFindClassName;
    }
    return hthrLoadWindowTree ? FALSE : Proc_CreateThread(LoadWindowTreeThread, NULL, FALSE, &hthrLoadWindowTree);
}

HWND AW_GetMainDlg() {
    return hMainDlg;
}

BOOL CALLBACK LocateTreeItemEnumProc(HWND TreeView, HTREEITEM TreeItem, UINT Level, LPARAM Param) {
    TVITEM  stTVI;
    stTVI.mask = TVIF_PARAM;
    stTVI.hItem = TreeItem;
    return !(SendMessage(hTree, TVM_GETITEM, 0, (LPARAM)&stTVI) && stTVI.lParam == Param);
}

BOOL AW_LocateWindowInTree(HWND hWnd) {
    HTREEITEM   hItem;
    hItem = Ctl_EnumTreeViewItems(hTree, FALSE, LocateTreeItemEnumProc, (LPARAM)PURGE_HWND(hWnd));
    if (hItem) {
        SendMessage(hTree, TVM_SELECTITEM, TVGN_CARET, (LPARAM)hItem);
        return TRUE;
    } else
        return FALSE;
}

VOID CALLBACK MainDlgResizeProc(HWND Dialog, LONG NewWidth, LONG NewHeight, PWINDOWPOS WindowPos) {
    RECT rcClient;
    if (GetClientRect(hBanner, &rcClient)) {
        SetWindowPos(hBanner, NULL, 0, 0, NewWidth, rcClient.bottom, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
        SetWindowPos(hTree, NULL, 0, 0, NewWidth, NewHeight - rcClient.bottom, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
    }
}

INT_PTR WINAPI MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_INITDIALOG) {

        KNS_SetDialogSubclass(hDlg, MainDlgResizeProc);
        hMainDlg = hDlg;
        SendMessage(hDlg, WM_SETTEXT, 0, (LPARAM)KNS_NAME);

        // Obtain basic info of window and controls
        hBanner = GetDlgItem(hDlg, IDC_MAINBANNER);
        hTree = GetDlgItem(hDlg, IDC_MAINTREE);
        UI_SetTheme(hTree);
        // Prepare controls and resources
        HMENU hMenu = GetMenu(hDlg);
        if (hMenu) {
            DestroyMenu(hMenu);
        }
        Ctl_SetMenu(hDlg, stDlgMenu);
        hSearchMenu = CreatePopupMenu();
        Ctl_CreateMenu(stSearchMenu, hSearchMenu);
        hDesktop = GetDesktopWindow();
        iTreeItemHeight = (INT)SendMessage(hTree, TVM_GETITEMHEIGHT, 0, 0);
        himlIcons = ImageList_Create(iTreeItemHeight, iTreeItemHeight, ILC_MASK | ILC_COLOR32 | ILC_HIGHQUALITYSCALE, 0, 1);
        SendMessage(hTree, TVM_SETIMAGELIST, TVSIL_NORMAL, (LPARAM)himlIcons);
        hIconOEMWinLogo = LoadImage(NULL, MAKEINTRESOURCE(OIC_WINLOGO), IMAGE_ICON, 0, 0, LR_SHARED);
        // Global resources
        AWDatabaseInit();
        FindWndInit();
        WndPropRelationshipInit();
        WndPropResourceInit();
        WndPropOperationInit();
        // Load window tree
        AW_LoadWindowTreeAsync(TRUE, NULL, NULL);
    } else if (uMsg == WM_COMMAND) {
        if (LOWORD(wParam) == IDM_RELOAD) {
            AW_LoadWindowTreeAsync(TRUE, NULL, NULL);
        } else if (LOWORD(wParam) == IDM_EXPWNDTREE) {
            HANDLE      hExpTreeFile;
            TCHAR       szExpTreeFileName[MAX_PATH];
            CHAR        szUTF8BOM[] = "\xEF\xBB\xBF";
            szExpTreeFileName[0] = '\0';
            if (Dlg_GetSaveFileName(hDlg, I18N_GetString(I18NIndex_ExportTreeFilter), szExpTreeFileName, lpszExpTreeFileExt)) {
                if ((hExpTreeFile = File_Create(szExpTreeFileName, NULL, FILE_APPEND_DATA | SYNCHRONIZE, FILE_SHARE_READ, FILE_SUPERSEDE, FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT | FILE_SEQUENTIAL_ONLY)) != NULL) {
                    // Write UTF-8 BOM
                    IO_Write(hExpTreeFile, 0, szUTF8BOM, ARRAYSIZE(szUTF8BOM) - 1);
                    Ctl_EnumTreeViewItems(hTree, FALSE, ExpTreeItemEnumProc, (LPARAM)hExpTreeFile);
                    NtClose(hExpTreeFile);
                } else {
                    KNS_LastStatusMsgBox(hDlg);
                }
            }
        } else if (LOWORD(wParam) == IDM_FINDWND) {
            AW_OpenFindWndDlg(hDlg);
        } else if (wParam == MAKEWPARAM(IDM_EXIT, 0)) {
            EndDialog(hDlg, 0);
        } else if (wParam == MAKEWPARAM(IDM_HOMEPAGE, 0)) {
            KNS_OpenHomePage();
        } else if (wParam == MAKEWPARAM(IDM_ABOUT, 0)) {
            KNS_DlgAbout(hDlg);
        } else if (wParam == MAKEWPARAM(IDM_REFRESHSEARCH, 0)) {
            AW_LoadWindowTreeAsync(FALSE, NULL, NULL);
        } else if (wParam == MAKEWPARAM(IDM_EXITSEARCH, 0)) {
            AW_LoadWindowTreeAsync(TRUE, NULL, NULL);
        }
        SetWindowLongPtr(hDlg, DWLP_MSGRESULT, 0);
    } else if (uMsg == WM_NOTIFY) {
        LPNM_TREEVIEW lpnmtv = (LPNM_TREEVIEW)lParam;
        if (lpnmtv->hdr.idFrom == IDC_MAINTREE && lpnmtv->hdr.code == NM_RCLICK) {
            TVHITTESTINFO   stTVHTI;
            POINT           pt;
            HTREEITEM       hTreeItem;
            TVITEM          stTVIGetLParam;
            GetCursorPos(&stTVHTI.pt);
            pt.x = stTVHTI.pt.x;
            pt.y = stTVHTI.pt.y;
            ScreenToClient(hTree, &stTVHTI.pt);
            hTreeItem = (HTREEITEM)SendMessage(hTree, TVM_HITTEST, 0, (LPARAM)&stTVHTI);
            if (hTreeItem) {
                stTVIGetLParam.mask = TVIF_PARAM;
                stTVIGetLParam.hItem = hTreeItem;
                if (SendMessage(hTree, TVM_GETITEM, 0, (LPARAM)&stTVIGetLParam)) {
                    if (stTVIGetLParam.lParam == (LPARAM)INVALID_HANDLE_VALUE)
                        Ctl_PopupMenu(hSearchMenu, pt.x, pt.y, hDlg);
                    else if (IsWindow((HWND)stTVIGetLParam.lParam)) {
                        AW_OpenWndPropDlg((HWND)stTVIGetLParam.lParam);
                        SendMessage(hTree, TVM_SELECTITEM, TVGN_CARET, (LPARAM)hTreeItem);
                    }
                }
            }
            SetWindowLongPtr(hDlg, DWLP_MSGRESULT, 0);
        }
    } else if (uMsg == WM_CLOSE) {
        FindWndUninit();
        WndPropRelationshipUninit();
        WndPropResourceUninit();
        WndPropOperationUninit();
        DestroyWindow(hDlg);
        SetWindowLongPtr(hDlg, DWLP_MSGRESULT, 0);
    } else if (uMsg == WM_DESTROY) {
        PostQuitMessage(0);
    } else
        return FALSE;
    return TRUE;
}