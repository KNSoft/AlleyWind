#include "AlleyWind.h"

#define IDM_PROC_EXPLORE 1
#define IDM_PROC_TERMINATE 2
#define IDM_PROC_PROP 3

#define IDM_WNDOP_PROPERTIES 10
#define IDM_WNDOP_LOCATEINLIST 11
#define IDM_WNDOP_HIGHLIGHT 12

HMENU hPropRelationshipProcMenu, hPropRelationshipWndOpMenu;

CTL_MENU stPropRelationshipProcMenu[] = {
    { MF_STRING, IDM_PROC_EXPLORE, I18NIndex_Explore, NULL, 0 },
    { MF_STRING, IDM_PROC_TERMINATE, I18NIndex_Terminate, NULL, 0 },
    { MF_STRING, IDM_PROC_PROP, I18NIndex_Properties, NULL, 0 }
};

CTL_MENU stPropRelationshipWndOpMenu[] = {
    { MF_STRING, IDM_WNDOP_PROPERTIES, I18NIndex_Properties, NULL, 0 },
    { MF_STRING, IDM_WNDOP_LOCATEINLIST, I18NIndex_LocateInList, NULL, 0 },
    { MF_STRING, IDM_WNDOP_HIGHLIGHT, I18NIndex_Highlight, NULL, 0 }
};

I18N_CTLTEXT astWndPropRelationshipTextCtl[] = {
    { IDC_WNDPROP_RELATIONSHIP_PROCESS_TEXT, I18NIndex_Process },
    { IDC_WNDPROP_RELATIONSHIP_THREAD_TEXT, I18NIndex_Thread },
    { IDC_WNDPROP_RELATIONSHIP_WINDOW_TEXT, I18NIndex_RelatedWindow }
};

CTL_LISTCTL_COLUME aRelateWindowListCol[] = {
    { I18NIndex_Relationship, 180 },
    { I18NIndex_Handle, 140 },
    { I18NIndex_Caption, 200 },
    { I18NIndex_Class, 200 }
};

typedef enum _AW_WINDOW_RELATIONSHIP {
    AWWindowRelationshipParent,
    AWWindowRelationshipOwner,
    AWWindowRelationshipPrevious,
    AWWindowRelationshipNext,
    AWWindowRelationshipFirstChild,
    AWWindowRelationshipFirst,
    AWWindowRelationshipLast,
    AWWindowRelationshipPreviousTabControl,
    AWWindowRelationshipNextTabControl,
    AWWindowRelationshipPreviousGroupControl,
    AWWindowRelationshipNextGroupControl
} AW_WINDOW_RELATIONSHIP, * PAW_WINDOW_RELATIONSHIP;

typedef struct _AW_WINDOW_RELATIONSHIPITEM {
    AW_WINDOW_RELATIONSHIP  Relationship;
    UINT_PTR                I18NIndex;
} AW_WINDOW_RELATIONSHIPITEM, * PAW_WINDOW_RELATIONSHIPITEM;

AW_WINDOW_RELATIONSHIPITEM aRelationshipItems[] = {
    { AWWindowRelationshipParent, I18NIndex_ParentWindow },
    { AWWindowRelationshipOwner, I18NIndex_OwnerWindow },
    { AWWindowRelationshipPrevious, I18NIndex_PreviousWindow },
    { AWWindowRelationshipNext, I18NIndex_NextWindow },
    { AWWindowRelationshipFirstChild, I18NIndex_FirstChildWindow },
    { AWWindowRelationshipFirst, I18NIndex_FirstEqualWindow },
    { AWWindowRelationshipLast, I18NIndex_LastEqualWindow }
};

VOID WndPropRelationshipInit() {
    hPropRelationshipProcMenu = CreatePopupMenu();
    Ctl_CreateMenu(stPropRelationshipProcMenu, hPropRelationshipProcMenu);
    hPropRelationshipWndOpMenu = CreatePopupMenu();
    Ctl_CreateMenu(stPropRelationshipWndOpMenu, hPropRelationshipWndOpMenu);
}

VOID WndPropRelationshipUninit() {
    Ctl_DestroyMenu(stPropRelationshipProcMenu, hPropRelationshipProcMenu);
    Ctl_DestroyMenu(stPropRelationshipWndOpMenu, hPropRelationshipWndOpMenu);
}

HWND WndPropRelationshipGetWindow(HWND hWnd, AW_WINDOW_RELATIONSHIP eRelationship) {
    if (eRelationship == AWWindowRelationshipParent)
        return GetParent(hWnd);
    else if (eRelationship == AWWindowRelationshipOwner)
        return GetWindow(hWnd, GW_OWNER);
    else if (eRelationship == AWWindowRelationshipPrevious)
        return GetWindow(hWnd, GW_HWNDPREV);
    else if (eRelationship == AWWindowRelationshipNext)
        return GetWindow(hWnd, GW_HWNDNEXT);
    else if (eRelationship == AWWindowRelationshipFirstChild)
        return GetWindow(hWnd, GW_CHILD);
    else if (eRelationship == AWWindowRelationshipFirst)
        return GetWindow(hWnd, GW_HWNDFIRST);
    else if (eRelationship == AWWindowRelationshipLast)
        return GetWindow(hWnd, GW_HWNDLAST);
    else
        return NULL;
}

HWND GetSelectedRelationship(HWND hDlg) {
    HWND    hList = GetDlgItem(hDlg, IDC_WNDPROP_RELATIONSHIP_WINDOW_LIST);
    INT     iSelected = (INT)SendMessage(hList, LVM_GETNEXTITEM, -1, LVNI_SELECTED);
    LVITEM  stLVI;
    if (iSelected != -1) {
        stLVI.mask = LVIF_PARAM;
        stLVI.iItem = iSelected;
        stLVI.iSubItem = 0;
        stLVI.lParam = 0;
        if (SendMessage(hList, LVM_GETITEM, 0, (LPARAM)&stLVI) && stLVI.lParam)
            return (HWND)stLVI.lParam;
    }
    return NULL;
}

INT_PTR WINAPI WndPropRelationshipDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_INITDIALOG) {
        HWND        hWnd, hCtl;
        TCHAR       szTempPath[MAX_PATH], szBuffer[1024];
        DWORD       dwPID, dwTID;
        HANDLE      hProc = NULL, hThread = NULL;
        PVOID       pThreadStartAddr;
        INT         i, iTemp;
        UINT        uTemp;
        hWnd = (HWND)lParam;
        AW_SetWndPropHWnd(hDlg, hWnd);
        // Initialize
        KNS_SetDialogSubclass(hDlg, NULL);
        I18N_InitCtlTexts(hDlg, astWndPropRelationshipTextCtl);
        // Process and Thread
        dwTID = GetWindowThreadProcessId(hWnd, &dwPID);
        hProc = RProc_Open(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, dwPID);
        uTemp = hProc ? RProc_GetFullImageName(hProc, szTempPath) : 0;
        iTemp = Str_Printf(szBuffer, TEXT("(%ld) %ws"), dwPID, uTemp ? szTempPath : I18N_GetString(I18NIndex_NotApplicable));
        AW_SetPropCtlString(hDlg, IDC_WNDPROP_RELATIONSHIP_PROCESS_EDIT, szBuffer, iTemp > 0);
        UI_EnableDlgItem(hDlg, IDC_WNDPROP_RELATIONSHIP_PROCESS_BTN, hProc != NULL);
        hThread = RProc_OpenThread(THREAD_QUERY_INFORMATION, dwTID);
        uTemp = hProc && hThread && NT_SUCCESS(NtQueryInformationThread(hThread, ThreadQuerySetWin32StartAddress, &pThreadStartAddr, sizeof(pThreadStartAddr), NULL)) ?
            RProc_TranslateAddress(hProc, pThreadStartAddr, szTempPath) :
            0;
        iTemp = Str_Printf(szBuffer, TEXT("(%ld) %ws"), dwTID, uTemp ? szTempPath : I18N_GetString(I18NIndex_NotApplicable));
        AW_SetPropCtlString(hDlg, IDC_WNDPROP_RELATIONSHIP_THREAD_EDIT, szBuffer, iTemp > 0);
        if (hProc)
            NtClose(hProc);
        if (hThread)
            NtClose(hThread);
        // Related Window
        hCtl = GetDlgItem(hDlg, IDC_WNDPROP_RELATIONSHIP_WINDOW_LIST);
        Ctl_InitListCtl(hCtl, aRelateWindowListCol, LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);
        for (i = 0; i < ARRAYSIZE(aRelationshipItems); i++) {
            LVITEM  stLVItem;
            HWND    hWndRelated;
            hWndRelated = WndPropRelationshipGetWindow(hWnd, aRelationshipItems[i].Relationship);
            stLVItem.mask = LVIF_TEXT | LVIF_PARAM;
            stLVItem.pszText = (LPWSTR)I18N_GetString(aRelationshipItems[i].I18NIndex);
            stLVItem.iItem = MAXINT;
            stLVItem.iSubItem = 0;
            stLVItem.lParam = (LPARAM)PURGE_HWND(hWndRelated);
            stLVItem.iItem = (INT)SendMessage(hCtl, LVM_INSERTITEM, 0, (LPARAM)&stLVItem);
            if (stLVItem.iItem != -1) {
                stLVItem.mask = LVIF_TEXT;
                stLVItem.iSubItem++;
                stLVItem.pszText = hWndRelated && Str_Printf(szBuffer, TEXT("%08X"), (DWORD)(DWORD_PTR)hWndRelated) > 0 ? szBuffer : I18N_GetString(I18NIndex_NotApplicable);
                SendMessage(hCtl, LVM_SETITEM, 0, (LPARAM)&stLVItem);
                stLVItem.iSubItem++;
                AW_GetWindowText(hWndRelated, szBuffer);
                stLVItem.pszText = szBuffer;
                SendMessage(hCtl, LVM_SETITEM, 0, (LPARAM)&stLVItem);
                stLVItem.iSubItem++;
                stLVItem.pszText = hWndRelated && GetClassName(hWndRelated, szBuffer, ARRAYSIZE(szBuffer)) > 0 ? szBuffer : I18N_GetString(I18NIndex_NotApplicable);
                SendMessage(hCtl, LVM_SETITEM, 0, (LPARAM)&stLVItem);
            }
        }
    } else if (uMsg == WM_COMMAND) {
        if (wParam == MAKEWPARAM(IDC_WNDPROP_RELATIONSHIP_PROCESS_BTN, BN_CLICKED)) {
            RECT rcBtn;
            if (UI_GetWindowRect((HWND)lParam, &rcBtn))
                Ctl_PopupMenu(hPropRelationshipProcMenu, rcBtn.right, rcBtn.top, hDlg);
        } else if (wParam == MAKEWPARAM(IDM_PROC_EXPLORE, 0) || wParam == MAKEWPARAM(IDM_PROC_PROP, 0)) {
            BOOL bSucc = FALSE;
            TCHAR szPath[MAX_PATH];
            HANDLE hProc = UI_OpenProc(PROCESS_QUERY_LIMITED_INFORMATION, AW_GetWndPropHWnd(hDlg));
            if (hProc) {
                if (RProc_GetFullImageName(hProc, szPath)) {
                    bSucc = Shell_Exec(szPath, NULL, wParam == MAKEWPARAM(IDM_PROC_EXPLORE, 0) ? ShellExecExplore : ShellExecProperties, SW_SHOWDEFAULT, NULL);
                }
                NtClose(hProc);
            }
            if (!bSucc) {
                KNS_LastErrorMsgBox(hDlg);
            }
        } else if (wParam == MAKEWPARAM(IDM_PROC_TERMINATE, 0)) {
            HANDLE hProc = UI_OpenProc(PROCESS_TERMINATE, AW_GetWndPropHWnd(hDlg));
            if (hProc) {
                NtTerminateProcess(hProc, 1);
                NtClose(hProc);
            }
        } else if (wParam == MAKEWPARAM(IDM_WNDOP_PROPERTIES, 0)) {
            HWND hRelatedWnd = GetSelectedRelationship(hDlg);
            if (hRelatedWnd)
                AW_OpenWndPropDlg(hRelatedWnd);
        } else if (wParam == MAKEWPARAM(IDM_WNDOP_LOCATEINLIST, 0)) {
            HWND hRelatedWnd = GetSelectedRelationship(hDlg);
            if (hRelatedWnd && AW_LocateWindowInTree(hRelatedWnd))
                BringWindowToTop(AW_GetMainDlg());
        } else if (wParam == MAKEWPARAM(IDM_WNDOP_HIGHLIGHT, 0)) {
            HWND hRelatedWnd = GetSelectedRelationship(hDlg);
            if (hRelatedWnd)
                AW_HighlightWindow(hRelatedWnd);
        }
    } else if (uMsg == WM_NOTIFY) {
        LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE)lParam;
        if (lpnmitem->hdr.idFrom == IDC_WNDPROP_RELATIONSHIP_WINDOW_LIST && lpnmitem->hdr.code == NM_RCLICK && lpnmitem->iItem != -1) {
            HWND hRelatedWnd = GetSelectedRelationship(hDlg);
            if (IsWindow(hRelatedWnd)) {
                POINT pt;
                if (!GetCursorPos(&pt))
                    pt.x = pt.y = 0;
                Ctl_PopupMenu(hPropRelationshipWndOpMenu, pt.x, pt.y, hDlg);
            }
        }
    }

    return FALSE;
}