#include "../../AlleyWind.inl"

#include "Menu.h"

typedef struct _UPDATE_WNDTREE_ENUM_CHILDREN
{
    HTREEITEM hParentNode;
    ULONG ulDepth;
} UPDATE_WNDTREE_ENUM_CHILDREN, *PUPDATE_WNDTREE_ENUM_CHILDREN;

HWND g_hMainDlg = NULL;
static UI_WINDOW_RESIZE_INFO g_stResizeInfo = { 0 };
static HWND g_hTree = NULL;
static HMENU g_hMainMenu, g_hItemMenu;
static HACCEL g_hAccel = NULL;
static LONG _Interlocked_operand_ volatile g_bUpdatingTree = FALSE;
static HIMAGELIST g_himlTreeIcons = NULL;
static HICON g_hIconWndDefault = NULL;

static
_Function_class_(UI_TREEVIEW_ENUMITEM_FN)
LOGICAL
CALLBACK
ExportWindowTreeToFileEnumProc(
    _In_ HWND TreeView,
    _In_ HTREEITEM TreeItem,
    _In_ UINT Level,
    _In_opt_ PVOID Context)
{
    HANDLE hFile;
    TVITEMW stTVI;
    WCHAR szUnicodeBuff[512];
    CHAR szUTF8Buff[ARRAYSIZE(szUnicodeBuff) * 2];
    UINT i;
    ULONG uChWritten;

    _Analysis_assume_(Context != NULL);
    hFile = (HANDLE)Context;

    stTVI.mask = TVIF_TEXT;
    stTVI.hItem = TreeItem;
    stTVI.cchTextMax = ARRAYSIZE(szUnicodeBuff) - Level;
    for (i = 0; i < Level; i++)
    {
        szUnicodeBuff[i] = '\t';
        stTVI.cchTextMax--;
    }
    stTVI.pszText = szUnicodeBuff + Level;
    if (SendMessageW(g_hTree, TVM_GETITEMW, 0, (LPARAM)&stTVI))
    {
        _Analysis_assume_nullterminated_(szUnicodeBuff);
        uChWritten = Str_W2U(szUTF8Buff, szUnicodeBuff);
        szUTF8Buff[uChWritten] = '\r';
        szUTF8Buff[uChWritten + 1] = '\n';
        IO_WriteFile(hFile, NULL, szUTF8Buff, uChWritten + 2);
    }

    return TRUE;
}

static
HRESULT
ExportWindowTreeToFile(
    _In_ PCWSTR FileName)
{
    HRESULT hr;
    NTSTATUS Status;
    HANDLE hFile;

    Status = IO_CreateWin32File(&hFile,
                                FileName,
                                NULL,
                                FILE_APPEND_DATA | SYNCHRONIZE,
                                FILE_SHARE_READ,
                                FILE_SUPERSEDE,
                                FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT | FILE_SEQUENTIAL_ONLY);
    if (!NT_SUCCESS(Status))
    {
        return HRESULT_FROM_NT(Status);
    }

    Status = IO_WriteFile(hFile, NULL, Str_Utf8_BOM, sizeof(Str_Utf8_BOM));
    if (!NT_SUCCESS(Status))
    {
        hr = HRESULT_FROM_NT(Status);
        goto _Exit;
    }

    hr = UI_TreeViewEnumItems(g_hTree, FALSE, ExportWindowTreeToFileEnumProc, (PVOID)hFile);

_Exit:
    NtClose(hFile);
    return hr;
}

static
BOOL
CALLBACK
InsertWindowToTree(HWND hWnd, LPARAM lParam)
{
    UPDATE_WNDTREE_ENUM_CHILDREN stEnumChildren, *lpstEnumChildren;
    WCHAR szCaption[MAX_WNDCAPTION_CCH], szClassName[MAX_CLASSNAME_CCH];
    PCWSTR pszSysClassName;
    WCHAR szBuffer[sizeof(DWORD) * 2 + ARRAYSIZE(szCaption) + ARRAYSIZE(szClassName) + 16];
    HICON hIcon;
    INT iImageIcon, iCch;
    HTREEITEM hTreeItem, hParentNode;
    ULONG ulDepth;
    TVINSERTSTRUCTW stTVIInsert = { 0, TVI_LAST, { TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM } };

    hWnd = UI_TruncateHandle(hWnd);
    lpstEnumChildren = (PUPDATE_WNDTREE_ENUM_CHILDREN)lParam;
    ulDepth = lpstEnumChildren->ulDepth;
    hParentNode = lpstEnumChildren->hParentNode;

    /* Get window info */
    UI_GetWindowTextW(hWnd, szCaption);
    if (!GetClassNameW(hWnd, szClassName, ARRAYSIZE(szClassName)))
    {
        szClassName[0] = UNICODE_NULL;
    }
    if (szClassName[0] != UNICODE_NULL)
    {
        pszSysClassName = AW_GetSysClassDisplayName(szClassName);
        if (pszSysClassName != NULL)
        {
            iCch = Str_PrintfW(szBuffer, L"%08lX \"%ls\" %ls (%ls)", UI_TruncateHandle32(hWnd), szCaption, szClassName, pszSysClassName);
        } else
        {
            iCch = Str_PrintfW(szBuffer, L"%08lX \"%ls\" %ls", UI_TruncateHandle32(hWnd), szCaption, szClassName);
        }
    } else
    {
        iCch = Str_PrintfW(szBuffer, L"%08lX \"%ls\"", UI_TruncateHandle32(hWnd), szCaption);
    }

    /* Append node info and icon */
    hIcon = AW_GetWindowIcon(hWnd);
    iImageIcon = (hIcon != NULL) ? ImageList_ReplaceIcon(g_himlTreeIcons, -1, hIcon) : -1;
    stTVIInsert.item.iImage = stTVIInsert.item.iSelectedImage = iImageIcon;
    stTVIInsert.hParent = hParentNode;
    stTVIInsert.item.pszText = iCch > 0 ? szBuffer : NULL;
    stTVIInsert.item.lParam = (LPARAM)hWnd;
    hTreeItem = (HTREEITEM)SendMessageW(g_hTree, TVM_INSERTITEMW, 0, (LPARAM)&stTVIInsert);
    if (ulDepth == 1)
    {
        SendMessageW(g_hTree, TVM_EXPAND, TVE_EXPAND, (LPARAM)hParentNode);
    }
    ulDepth++;
    hParentNode = hTreeItem;

    /* Next one */
    stEnumChildren.hParentNode = hParentNode;
    stEnumChildren.ulDepth = ulDepth;
    UI_EnumChildWindows(hWnd, InsertWindowToTree, (LPARAM)&stEnumChildren);
    return TRUE;
}

static
_Function_class_(USER_THREAD_START_ROUTINE)
NTSTATUS
NTAPI
UpdateWindowTreeThread(
    _In_ PVOID ThreadParameter)
{
    INT iTreeItemHeight;
    UPDATE_WNDTREE_ENUM_CHILDREN stEnumChildren = { TVI_ROOT, 0 };

    SendMessageW(g_hTree, TVM_DELETEITEM, 0, (LPARAM)TVI_ROOT);
    iTreeItemHeight = (INT)SendMessageW(g_hTree, TVM_GETITEMHEIGHT, 0, 0);
    if (g_himlTreeIcons != NULL)
    {
        SendMessageW(g_hTree, TVM_SETIMAGELIST, TVSIL_NORMAL, (LPARAM)NULL);
        ImageList_Destroy(g_himlTreeIcons);
    }
    g_himlTreeIcons = ImageList_Create(iTreeItemHeight,
                                       iTreeItemHeight,
                                       ILC_MASK | ILC_COLOR32 | ILC_HIGHQUALITYSCALE,
                                       0,
                                       1);
    if (g_himlTreeIcons != NULL)
    {
        ImageList_ReplaceIcon(g_himlTreeIcons, -1, g_hIconWndDefault);
    }
    SendMessageW(g_hTree, TVM_SETIMAGELIST, TVSIL_NORMAL, (LPARAM)g_himlTreeIcons);
    InsertWindowToTree(GetDesktopWindow(), (LPARAM)&stEnumChildren);

    g_bUpdatingTree = FALSE;
    return STATUS_SUCCESS;
}

static
W32ERROR
UpdateWindowTreeAsync(VOID)
{
    NTSTATUS Status;

    if (_InterlockedCompareExchange(&g_bUpdatingTree, TRUE, FALSE) != FALSE)
    {
        return ERROR_TRANSACTIONAL_CONFLICT;
    }

    Status = PS_CreateThread(NtCurrentProcess(), FALSE, UpdateWindowTreeThread, NULL, NULL, NULL);
    if (!NT_SUCCESS(Status))
    {
        return RtlNtStatusToDosErrorNoTeb(Status);
    }

    return ERROR_SUCCESS;
}

static
_Success_(return != NULL)
_Ret_maybenull_
HWND
GetSelectedItemRefWindow(VOID)
{
    TVITEMW tvi;

    tvi.hItem = (HTREEITEM)SendMessageW(g_hTree, TVM_GETNEXTITEM, TVGN_CARET, (LPARAM)NULL);
    if (tvi.hItem == NULL)
    {
        return NULL;
    }

    tvi.mask = TVIF_PARAM;
    if (!SendMessageW(g_hTree, TVM_GETITEMW, 0, (LPARAM)&tvi))
    {
        return NULL;
    }

    return IsWindow((HWND)tvi.lParam) ? (HWND)tvi.lParam : NULL;
}

static
VOID
OpenPropDlgForSelectedItemRefWindow(
    _In_ HWND Dialog)
{
    NTSTATUS Status;
    HWND Window;

    Window = GetSelectedItemRefWindow();
    if (Window != NULL)
    {
        Status = AW_OpenPropDialogBoxAsync(Window);
        if (!NT_SUCCESS(Status))
        {
            KNS_NtStatusMessageBox(Dialog, Status);
        }
    }
}

static
_Function_class_(UI_WINDOW_RESIZE_FN)
VOID
CALLBACK
MainDlgResizeProc(
    _In_ HWND Dialog,
    _In_ LONG Width,
    _In_ LONG Height,
    _In_opt_ PWINDOWPOS MgmtWinPos)
{
    if (g_hTree != NULL)
    {
        SetWindowPos(g_hTree,
                     NULL,
                     0,
                     0,
                     Width,
                     Height,
                     SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSENDCHANGING);
    }
}

static
INT_PTR
CALLBACK
MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_INITDIALOG)
    {
        RECT rc;
        WCHAR szTitle[MAX_WNDCAPTION_CCH];

        g_hMainDlg = hDlg;

        /* Set title */
        C_ASSERT(ARRAYSIZE(szTitle) > _STR_CCH_LEN(KNSOFT_APP_NAME));
        wcscpy_s(szTitle, ARRAYSIZE(szTitle), KNSOFT_APP_NAME);
        AW_PostFixTitleText(szTitle + _STR_CCH_LEN(KNSOFT_APP_NAME),
                            ARRAYSIZE(szTitle) - _STR_CCH_LEN(KNSOFT_APP_NAME));
        UI_SetWindowTextW(hDlg, szTitle);

        UI_EnableWindowPeek(hDlg, FALSE);

        /* Initialize tree-view global resources */
        g_hTree = GetDlgItem(hDlg, IDC_WNDTREE);
        UI_SetWindowExplorerVisualStyle(g_hTree);
        g_hIconWndDefault = LoadImageW(NULL, MAKEINTRESOURCEW(OIC_WINLOGO), IMAGE_ICON, 0, 0, LR_SHARED);

        /* Sets menu before subclass procedures */
        SetMenu(hDlg, g_hMainMenu);
        if (GetClientRect(hDlg, &rc))
        {
            MainDlgResizeProc(hDlg, rc.right, rc.bottom, NULL);
        }
    }

    UI_DPIScaleDlgProc(hDlg, uMsg, wParam, lParam);
    UI_ResizeWndProc(hDlg, uMsg, wParam, lParam, TRUE, MainDlgResizeProc, &g_stResizeInfo);

    if (uMsg == WM_INITDIALOG)
    {
        UpdateWindowTreeAsync();
        return FALSE;
    } else if (uMsg == WM_DPICHANGED)
    {
        /* TODO: Update image list only, rather than update the whole tree */
        if (g_himlTreeIcons != NULL)
        {
            UpdateWindowTreeAsync();
        }
    } else if (uMsg == WM_COMMAND)
    {
        if (wParam == MAKEWPARAM(IDM_FILE_RUNAS_ADMIN, 0))
        {
            W32ERROR Ret;

            Ret = Shell_Exec(NtCurrentPeb()->ProcessParameters->ImagePathName.Buffer,
                             CMDLINE_SWITCH_TRYELEVATEUIACCESS,
                             L"runas",
                             SW_SHOWNORMAL,
                             NULL);
            if (Ret == ERROR_SUCCESS)
            {
                SendMessageW(hDlg, WM_CLOSE, 0, 0);
            } else
            {
                KNS_Win32ErrorMessageBox(hDlg, Ret);
            }
        } else if (wParam == MAKEWPARAM(IDM_FILE_ALWAYS_ON_TOP, 0))
        {
            HRESULT hr;

            hr = UI_ToggleMenuCheckItem(g_astMainMenu[Menu_MainDlg_File].Handle, Menu_MainDlg_File_AlwaysOnTop, TRUE);
            if (SUCCEEDED(hr))
            {
                SetWindowPos(hDlg,
                             hr == S_OK ? HWND_TOPMOST : HWND_NOTOPMOST,
                             0,
                             0,
                             0,
                             0,
                             SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOSENDCHANGING);
            }
        } else if (wParam == MAKEWPARAM(IDM_HELP_HOMEPAGE, 0))
        {
            KNS_OpenHomepage();
        } else if (wParam == MAKEWPARAM(IDM_ITEM_HIGHLIGHT, 0))
        {
            HWND Window, RootWindow;

            Window = GetSelectedItemRefWindow();
            if (Window != NULL)
            {
                RootWindow = GetAncestor(Window, GA_ROOT);
                BringWindowToTop(RootWindow);
                if (!IsIconic(RootWindow))
                {
                    UI_FlashWindow(Window);
                } else
                {
                    FlashWindow(Window, TRUE);
                }
                SetActiveWindow(hDlg);
            }
        } else if (wParam == MAKEWPARAM(IDM_ITEM_PROPERTIES, 0))
        {
            OpenPropDlgForSelectedItemRefWindow(hDlg);
        } else if (HIWORD(wParam) == 0 || HIWORD(wParam) == 1)
        {
            if (LOWORD(wParam) == IDM_FILE_REFRESH)
            {
                UpdateWindowTreeAsync();
            } else if (LOWORD(wParam) == IDM_FILE_SAVETREE)
            {
                HRESULT hr;
                WCHAR szFile[MAX_PATH];

                szFile[0] = UNICODE_NULL;
                if (UI_GetSaveFileName(hDlg, AW_GetString(TextFileOfnFilter), szFile, L"txt"))
                {
                    hr = ExportWindowTreeToFile(szFile);
                    if (SUCCEEDED(hr))
                    {
                        Shell_LocateItem(szFile);
                    } else
                    {
                        KNS_HrMessageBox(hDlg, hr);
                    }
                }
            }
        }
    } else if (uMsg == WM_CONTEXTMENU && wParam == (WPARAM)g_hTree)
    {
        TVHITTESTINFO tvhti;
        TVITEMW tvi;
        INT X, Y;
        HWND Window;
        MENUITEMINFOW mii;

        tvhti.pt.x = X = GET_X_LPARAM(lParam);
        tvhti.pt.y = Y = GET_Y_LPARAM(lParam);
        if (ScreenToClient(g_hTree, &tvhti.pt))
        {
            tvi.hItem = (HTREEITEM)SendMessageW(g_hTree, TVM_HITTEST, 0, (LPARAM)&tvhti);
            if (tvi.hItem != NULL)
            {
                tvi.mask = TVIF_PARAM;
                if (SendMessageW(g_hTree, TVM_GETITEMW, 0, (LPARAM)&tvi))
                {
                    Window = (HWND)tvi.lParam;
                    SendMessageW(g_hTree, TVM_SELECTITEM, TVGN_CARET, (LPARAM)tvi.hItem);
                    if (Window == INVALID_HANDLE_VALUE)
                    {
                        // TODO: UI_PopupMenu(g_hSearchItemMenu, X, Y, hDlg);
                    } else if (IsWindow(Window))
                    {
                        mii.cbSize = sizeof(mii);
                        mii.fMask = MIIM_STATE;
                        mii.fState = IsWindowVisible(Window) ? MFS_ENABLED : MFS_DISABLED;
                        if (SetMenuItemInfoW(g_hItemMenu, Menu_MainDlg_Item_Highlight, TRUE, &mii))
                        {
                            UI_PopupMenu(g_hItemMenu, X, Y, hDlg);
                        }
                    }
                }
            }
        }
        SetWindowLongPtrW(hDlg, DWLP_MSGRESULT, 0);
    } else if (uMsg == WM_NOTIFY)
    {
        LPNMHDR pnmh = (LPNMHDR)lParam;
        if (pnmh->hwndFrom == g_hTree)
        {
            LPNMTREEVIEWW pnmtv = (LPNMTREEVIEWW)lParam;
            if (pnmtv->hdr.code == NM_DBLCLK)
            {
                OpenPropDlgForSelectedItemRefWindow(hDlg);
            }
        }
    } else if (uMsg == WM_CLOSE)
    {
        SetWindowLongPtrW(hDlg, DWLP_MSGRESULT, 0);
        DestroyWindow(hDlg);
    } else if (uMsg == WM_DESTROY)
    {
        g_hMainDlg = NULL;
        if (g_himlTreeIcons != NULL)
        {
            SendMessageW(g_hTree, TVM_SETIMAGELIST, TVSIL_NORMAL, (LPARAM)NULL);
            ImageList_Destroy(g_himlTreeIcons);
        }
        PostQuitMessage(S_OK);
    }
    return 0;
}

HRESULT
AW_OpenMainDialogBox(VOID)
{
    HRESULT hr;

    MainDlgCreateMenu(&g_hMainMenu, &g_hItemMenu);
    g_hAccel = MainDlgCreateAccelerator();
    hr = AW_CreateDialog(NULL, NULL, MAKEINTRESOURCEW(IDD_MAIN), MainDlgProc, 0);
    if (SUCCEEDED(hr))
    {
        hr = KNS_DlgMessageLoop(g_hAccel);
    }
    if (g_hAccel != NULL)
    {
        DestroyAcceleratorTable(g_hAccel);
    }
    MainDlgDestroyMenu(g_hMainMenu, g_hItemMenu);

    return hr;
}
