#include "../AlleyWind.inl"

typedef struct _UPDATE_WNDTREE_ENUM_CHILDREN
{
    HTREEITEM hParentNode;
    ULONG ulDepth;
} UPDATE_WNDTREE_ENUM_CHILDREN, *PUPDATE_WNDTREE_ENUM_CHILDREN;

static UI_WINDOW_RESIZE_INFO g_stResizeInfo = { 0 };
static HWND g_hTree = NULL;
static LONG _Interlocked_operand_ volatile g_bUpdatingTree = FALSE;
static HIMAGELIST g_himlTreeIcons = NULL;
static HICON g_hIconWndDefault = NULL;

static
BOOL
CALLBACK
InsertWindowToTree(HWND hWnd, LPARAM lParam)
{
    UPDATE_WNDTREE_ENUM_CHILDREN stEnumChildren, *lpstEnumChildren;
    WCHAR szCaption[MAX_WNDCAPTION_CCH], szClassName[MAX_CLASSNAME_CCH];
    WCHAR szBuffer[sizeof(DWORD) * 2 + ARRAYSIZE(szCaption) + ARRAYSIZE(szClassName) + 16];
    HICON hIcon;
    INT iImageIcon, iCch;
    HTREEITEM hTreeItem, hParentNode;
    ULONG ulDepth;
    TVINSERTSTRUCTW stTVIInsert = { 0, TVI_LAST, { TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM } };

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
        iCch = Str_PrintfW(szBuffer, L"%08lX \"%s\" %s", (ULONG)(ULONG_PTR)hWnd, szCaption, szClassName);
    } else
    {
        iCch = Str_PrintfW(szBuffer, L"%08X \"%s\"", (ULONG)(ULONG_PTR)hWnd, szCaption);
    }

    /* Append node info and icon */
    hIcon = NULL;
    if (AW_SendMsgTO(hWnd, WM_GETICON, ICON_SMALL, 0, (PDWORD_PTR)&hIcon) == 0 || hIcon == NULL)
    {
        hIcon = (HICON)GetClassLongPtrW(hWnd, GCLP_HICON);
    }
    iImageIcon = (hIcon != NULL) ? ImageList_ReplaceIcon(g_himlTreeIcons, -1, hIcon) : -1;
    stTVIInsert.item.iImage = stTVIInsert.item.iSelectedImage = iImageIcon;
    stTVIInsert.hParent = hParentNode;
    stTVIInsert.item.pszText = iCch > 0 ? szBuffer : NULL;
    stTVIInsert.item.lParam = (LPARAM)UI_TruncateHandle(hWnd);
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
        SetWindowPos(g_hTree, NULL, 0, 0, Width, Height, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSENDCHANGING);
    }
}

INT_PTR
CALLBACK
MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    UI_DPIScaleDlgProc(hDlg, uMsg, wParam, lParam);
    UI_ResizeWndProc(hDlg, uMsg, wParam, lParam, TRUE, MainDlgResizeProc, &g_stResizeInfo);

    if (uMsg == WM_INITDIALOG)
    {
        /* Initialize tree-view global resources */
        g_hTree = GetDlgItem(hDlg, IDC_WNDTREE);
        g_hIconWndDefault = LoadImageW(NULL, MAKEINTRESOURCEW(OIC_WINLOGO), IMAGE_ICON, 0, 0, LR_SHARED);

        UpdateWindowTreeAsync();

        return FALSE;
    } else if (uMsg == WM_DPICHANGED)
    {
        if (g_himlTreeIcons != NULL)
        {
            UpdateWindowTreeAsync();
        }
    } else if (uMsg == WM_CLOSE)
    {
        EndDialog(hDlg, 0);
        ImageList_Destroy(g_himlTreeIcons);
        SetWindowLongPtrW(hDlg, DWLP_MSGRESULT, 0);
    }
    return 0;
}
