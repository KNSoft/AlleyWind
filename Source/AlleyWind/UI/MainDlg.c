#include "../AlleyWind.inl"

#pragma region Menu

/* File */

#define IDM_RUNAS_ADMIN 1
#define IDM_REFRESH 2
#define IDM_SAVETREE 3

static UI_MENU_ITEM g_astMenuFile[] = {
    { FALSE, MF_STRING, IDM_RUNAS_ADMIN, NULL, Precomp4C_I18N_All_RunAsAdmin, NULL, 0 , NULL },
    { FALSE, MF_STRING, IDM_REFRESH, NULL, Precomp4C_I18N_All_Refresh_F5, NULL, 0 , NULL },
    { FALSE, MF_STRING, IDM_SAVETREE, NULL, Precomp4C_I18N_All_SaveTree_Ctrl_S, NULL, 0 , NULL },
};

/* Help */

#define IDM_HOMEPAGE 20

static UI_MENU_ITEM g_astMenuHelp[] = {
    { FALSE, MF_STRING, IDM_HOMEPAGE, NULL, Precomp4C_I18N_All_Homepage, NULL, 0, NULL },
};

/* Main */

static UI_MENU_ITEM g_astDlgMenu[] = {
    { FALSE, MF_STRING, 0, NULL, Precomp4C_I18N_All_File, NULL, ARRAYSIZE(g_astMenuFile), g_astMenuFile },
    { FALSE, MF_STRING, 0, NULL, Precomp4C_I18N_All_Help, NULL, ARRAYSIZE(g_astMenuHelp), g_astMenuHelp },
};

static ACCEL g_astDlgAccel[] = {
    { FVIRTKEY, VK_F5, IDM_REFRESH },
    { FVIRTKEY | FCONTROL, 'S', IDM_SAVETREE},
};

static
HMENU
SetMainDlgMenu(
    _In_ HWND Dialog)
{
    HMENU hMenu;
    NTSTATUS Status;
    HANDLE Token;

    /* Add runas sub-menu if privilege is limited */
    Status = PS_OpenCurrentThreadToken(&Token);
    if (!NT_SUCCESS(Status))
    {
        goto _CreateMenu;
    }
    if (!NT_SUCCESS(PS_IsAdminToken(Token)))
    {
        g_astMenuFile[0].Icon = g_ResUACIconBitmap;
    } else
    {
        g_astMenuFile[0].Invalid = TRUE;
    }
    NtClose(Token);

_CreateMenu:
    AW_InitMenuI18N(g_astMenuFile);
    AW_InitMenuI18N(g_astMenuHelp);
    AW_InitMenuI18N(g_astDlgMenu);
    hMenu = UI_CreateWindowMenu(g_astDlgMenu);
    if (hMenu == NULL)
    {
        return NULL;
    }

    if (!SetMenu(Dialog, hMenu))
    {
        UI_DestroyWindowMenu(hMenu, g_astDlgMenu);
        hMenu = NULL;
    }
    return hMenu;
}

static
VOID
DestroyMainDlgMenu(
    _In_ HMENU Menu)
{
    UI_DestroyWindowMenuEx(Menu, g_astDlgMenu, ARRAYSIZE(g_astDlgMenu));
}

#pragma endregion

typedef struct _UPDATE_WNDTREE_ENUM_CHILDREN
{
    HTREEITEM hParentNode;
    ULONG ulDepth;
} UPDATE_WNDTREE_ENUM_CHILDREN, *PUPDATE_WNDTREE_ENUM_CHILDREN;

static UI_WINDOW_RESIZE_INFO g_stResizeInfo = { 0 };
static HWND g_hTree = NULL;
static HMENU g_hMenu = NULL;
static HACCEL g_hAccel = NULL;
static LONG _Interlocked_operand_ volatile g_bUpdatingTree = FALSE;
static HIMAGELIST g_himlTreeIcons = NULL;
static HICON g_hIconWndDefault = NULL;

static
_Function_class_(UI_ENUMTREEVIEWITEM_FN)
LOGICAL
CALLBACK
ExportWindowTreeToFileEnumProc(
    _In_ HWND TreeView,
    _In_ HTREEITEM TreeItem,
    _In_ UINT Level,
    _In_opt_ PVOID Context)
{
    HANDLE  hFile;
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

    hr = UI_EnumTreeViewItems(g_hTree, FALSE, ExportWindowTreeToFileEnumProc, (PVOID)hFile);

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
            iCch = Str_PrintfW(szBuffer, L"%08lX \"%ls\" %ls (%ls)", (ULONG)(ULONG_PTR)hWnd, szCaption, szClassName, pszSysClassName);
        } else
        {
            iCch = Str_PrintfW(szBuffer, L"%08lX \"%ls\" %ls", (ULONG)(ULONG_PTR)hWnd, szCaption, szClassName);
        }
    } else
    {
        iCch = Str_PrintfW(szBuffer, L"%08lX \"%ls\"", (ULONG)(ULONG_PTR)hWnd, szCaption);
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
        ImageList_Destroy(g_himlTreeIcons);
    }
    g_himlTreeIcons = ImageList_Create(iTreeItemHeight,
                                       iTreeItemHeight,
                                       ILC_MASK | ILC_COLOR32 | ILC_HIGHQUALITYSCALE,
                                       0,
                                       1);
    SendMessageW(g_hTree, TVM_SETIMAGELIST, TVSIL_NORMAL, (LPARAM)g_himlTreeIcons);
    if (g_himlTreeIcons != NULL)
    {
        ImageList_ReplaceIcon(g_himlTreeIcons, -1, g_hIconWndDefault);
    }
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

        /* Initialize tree-view global resources */
        AW_InitClassDatabase();
        g_hTree = GetDlgItem(hDlg, IDC_WNDTREE);
        UI_SetWindowExplorerVisualStyle(g_hTree);
        g_hIconWndDefault = LoadImageW(NULL, MAKEINTRESOURCEW(OIC_WINLOGO), IMAGE_ICON, 0, 0, LR_SHARED);

        /* Initialize menu before subclass procedures */
        g_hMenu = SetMainDlgMenu(hDlg);
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
        if (wParam == MAKEWPARAM(IDM_RUNAS_ADMIN, 0))
        {
            W32ERROR Ret;

            Ret = Shell_Exec(NtCurrentPeb()->ProcessParameters->ImagePathName.Buffer,
                             NULL,
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
        } else if (wParam == MAKEWPARAM(IDM_HOMEPAGE, 0))
        {
            KNS_OpenHomepage();
        } else if (HIWORD(wParam) == 0 || HIWORD(wParam) == 1)
        {
            if (LOWORD(wParam) == IDM_REFRESH)
            {
                UpdateWindowTreeAsync();
            } else if (LOWORD(wParam) == IDM_SAVETREE)
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
    } else if (uMsg == WM_CLOSE)
    {
        if (g_himlTreeIcons != NULL)
        {
            ImageList_Destroy(g_himlTreeIcons);
        }
        if (g_hMenu != NULL)
        {
            DestroyMainDlgMenu(g_hMenu);
        }
        SetWindowLongPtrW(hDlg, DWLP_MSGRESULT, 0);
        DestroyWindow(hDlg);
    } else if (uMsg == WM_DESTROY)
    {
        PostQuitMessage(S_OK);
    }
    return 0;
}

HRESULT
AW_OpenMainDialogBox(VOID)
{
    HRESULT hr;

    g_hAccel = CreateAcceleratorTableW(g_astDlgAccel, ARRAYSIZE(g_astDlgAccel));
    hr = AW_OpenDialog(NULL, MAKEINTRESOURCEW(IDD_MAIN), g_hAccel, MainDlgProc, 0);
    if (g_hAccel != NULL)
    {
        DestroyAcceleratorTable(g_hAccel);
    }

    return hr;
}
