#include "AlleyWind.h"

VOID AW_OpenWndPropDlg(HWND hWnd) {
    Proc_CreateThread(OpenWndPropDlgThread, (PVOID)hWnd, FALSE, NULL);
}

HWND AW_GetWndPropHWnd(HWND hDlg) {
    return GetProp(hDlg, AW_WNDPROP_HWND);
}

BOOL AW_SetWndPropHWnd(HWND hDlg, HWND hWnd) {
    return SetProp(hDlg, AW_WNDPROP_HWND, hWnd);
}

HWND AW_RemoveWndPropHWnd(HWND hDlg) {
    return RemoveProp(hDlg, AW_WNDPROP_HWND);
}

VOID AW_SetPropCtlFormat(HWND hDlg, UINT uCtlID, BOOL bSuccess, _Printf_format_string_ LPTSTR lpszFormat, ...) {
    HWND    hCtl;
    TCHAR   szBuffer[1024];
    INT     iCch = 0;
    va_list args;
    hCtl = GetDlgItem(hDlg, uCtlID);
    if (bSuccess) {
        va_start(args, lpszFormat);
        iCch = Str_VPrintf(szBuffer, lpszFormat, args);
        va_end(args);
    }
    UI_SetWndTextNoNotify(hCtl, iCch > 0 ? szBuffer : NULL);
    EnableWindow(hCtl, bSuccess);
}

VOID AW_SetPropCtlString(HWND hDlg, UINT uCtlID, LPCWSTR lpszString, BOOL bSuccess) {
    HWND    hCtl = GetDlgItem(hDlg, uCtlID);
    UI_SetWndTextNoNotify(hCtl, bSuccess ? lpszString : NULL);
    EnableWindow(hCtl, bSuccess);
}

VOID AW_SetPropCtlRect(HWND hDlg, UINT uCtlID, PRECT lpRect, BOOL bSuccess) {
    HWND    hCtl;
    TCHAR   szBuffer[1024];
    INT     iCch;
    hCtl = GetDlgItem(hDlg, uCtlID);
    if (bSuccess) {
        iCch = Str_Printf(szBuffer, TEXT("LT(%ld, %ld)-RB(%ld, %ld) [%ldx%ld]"), lpRect->left, lpRect->top, lpRect->right, lpRect->bottom, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top);
        UI_SetWndTextNoNotify(hCtl, iCch > 0 ? szBuffer : NULL);
    } else
        EnableWindow(hCtl, FALSE);
}

VOID AW_SetPropCtlCheck(HWND hDlg, UINT uCtlID, UINT_PTR uCheck, BOOL bSuccess) {
    HWND    hCtl = GetDlgItem(hDlg, uCtlID);
    SendMessage(hCtl, BM_SETCHECK, bSuccess ? uCheck : BST_UNCHECKED, 0);
    EnableWindow(hCtl, bSuccess);
}

CTL_LISTCTL_COLUME aExtraBytesListCol[] = {
    { I18NIndex_Offset, 80 },
    { I18NIndex_Data, 180 }
};

BOOL CALLBACK AW_WndPropExtraBytesEnumProc(DWORD dwOffset, LONG_PTR lBytes, UINT uSize, DWORD dwError, LPARAM lParam) {
    TCHAR   szBuffer[1024];
    LVITEM  stLVItem;
    INT     iCch;
    stLVItem.mask = LVIF_TEXT;
    iCch = Str_Printf(szBuffer, TEXT("+%u"), dwOffset);
    stLVItem.pszText = iCch > 0 ? szBuffer : I18N_GetString(I18NIndex_NotApplicable);
    stLVItem.iItem = MAXINT;
    stLVItem.iSubItem = 0;
    stLVItem.iItem = (INT)SendMessage((HWND)lParam, LVM_INSERTITEM, 0, (LPARAM)&stLVItem);
    if (stLVItem.iItem != -1) {
        stLVItem.iSubItem++;
        iCch = 0;
        if (dwError == ERROR_SUCCESS) {
            iCch = Str_Printf(szBuffer, TEXT("%p"), (LPVOID)lBytes);
            if (iCch > 0)
                szBuffer[uSize * 2] = '\0';
        }
        stLVItem.pszText = iCch > 0 ? szBuffer : I18N_GetString(I18NIndex_NotApplicable);
        SendMessage((HWND)lParam, LVM_SETITEM, 0, (LPARAM)&stLVItem);
    }
    return TRUE;
}

BOOL AW_EnumExtraBytes(HWND hWnd, BOOL bClassExtraBytes, LPARAM lParam) {
    HANDLE                  hProc = NULL;
    DWORD_PTR               dwpExtraSize, dwpNextOffset, dwpOffset;
    LONG_PTR                lBytes;
    UINT_PTR                uWordSize;
    HIJACK_CALLPROCHEADER   stCallProc;
    HIJACK_CALLPROCPARAM    stGLParams[] = {
        { (DWORD_PTR)hWnd, 0, FALSE },
        { 0, 0, FALSE }
    };
    BOOL                    bUseHijack = FALSE, b32Proc;
    PCSTR                   pszGLFunc;
    UI_GetWindowLong(hWnd, TRUE, bClassExtraBytes ? GCL_CBCLSEXTRA : GCL_CBWNDEXTRA, &dwpExtraSize);
    if (dwpExtraSize) {
        DWORD       dwPID;
        GetWindowThreadProcessId(hWnd, &dwPID);
        hProc = RProc_Open(HIJACK_PROCESS_ACCESS, dwPID);
        if (hProc) {
            if (RProc_IsWow64(hProc, &b32Proc)) {
                pszGLFunc = AW_GetWindowLongFunc(bClassExtraBytes, b32Proc, IsWindowUnicode(hWnd));
                if (Hijack_LoadProcAddr(hProc, L"user32.dll", pszGLFunc, (PVOID*)&stCallProc.Procedure, AWSettings_GetItemValueEx(AWSetting_ResponseTimeout))) {
                    stCallProc.RetValue = 0;
                    stCallProc.CallConvention = CC_STDCALL;
                    stCallProc.ParamCount = ARRAYSIZE(stGLParams);
                    bUseHijack = TRUE;
                }
            }
            if (!bUseHijack) {
                NtClose(hProc);
                hProc = NULL;
            }
        }
        uWordSize = bUseHijack ?
            (b32Proc ? sizeof(DWORD) : sizeof(QWORD)) :
            sizeof(LONG_PTR);
        dwpOffset = 0;
        do {
            if (bUseHijack) {
                stGLParams[1].Value = (INT)dwpOffset;
                if (Hijack_CallProc(hProc, &stCallProc, stGLParams, AWSettings_GetItemValueEx(AWSetting_ResponseTimeout)) &&
                    stCallProc.LastError == ERROR_SUCCESS) {
                    lBytes = (LONG_PTR)stCallProc.RetValue;
                    EH_SetLastError(ERROR_SUCCESS);
                } else {
                    lBytes = 0;
                    EH_SetLastError(ERROR_READ_FAULT);
                }
                if (b32Proc)
                    lBytes = (DWORD)lBytes;
            } else
                UI_GetWindowLong(hWnd, bClassExtraBytes, (INT)dwpOffset, &lBytes);
            dwpNextOffset = dwpOffset + uWordSize;
            if (!AW_WndPropExtraBytesEnumProc((DWORD)dwpOffset, lBytes, (UINT)(dwpNextOffset > dwpExtraSize ? dwpExtraSize - dwpOffset : uWordSize), lBytes ? ERROR_SUCCESS : EH_GetLastError(), lParam))
                return FALSE;
            dwpOffset = dwpNextOffset;
        } while (dwpOffset < dwpExtraSize);
        if (bUseHijack) {
            NtClose(hProc);
            hProc = NULL;
        }
        return TRUE;
    } else
        return EH_LastErrorSucceed();
}