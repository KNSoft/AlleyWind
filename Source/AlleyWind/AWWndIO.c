#include "AlleyWind.h"

LRESULT AW_SendMsgTO(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, PDWORD_PTR lpdwResult) {
    return SendMessageTimeout(
        hWnd,
        uMsg,
        wParam,
        lParam,
        SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT,
        AWSettings_GetItemValueEx(AWSetting_ResponseTimeout),
        lpdwResult);
}

UINT AW_GetWindowTextEx(HWND hWnd, PWSTR psz, UINT cCh) {
    DWORD_PTR   dwCch;
    UINT        c;
    c = AW_SendMsgTO(hWnd, WM_GETTEXT, cCh, (LPARAM)psz, &dwCch) && (UINT)dwCch < cCh ? (UINT)dwCch : 0;
    psz[c] = '\0';
    return c;
}

DWORD WINAPI HighlightWindowThread(LPVOID lParam) {
    HWND        hWnd = lParam;
    DWORD_PTR   dwpStyle;
    HDC         hDC;
    RECT        rcClient;
    UINT        uTimes = 4 * 2;
    BOOL        bFlash;
    bFlash = UI_GetWindowLong(hWnd, FALSE, GWL_STYLE, &dwpStyle) && (dwpStyle & WS_DLGFRAME || dwpStyle & WS_THICKFRAME);
    if (bFlash) {
        FLASHWINFO fwi = { sizeof(FLASHWINFO), hWnd, FLASHW_ALL, 4, 200 };
        FlashWindowEx(&fwi);
        return ERROR_SUCCESS;
    }
    hDC = GetDC(hWnd);
    if (!hDC)
        return ERROR_INVALID_HANDLE;
    if (!GetClientRect(hWnd, &rcClient))
        return NT_GetLastError();
    do {
        GDI_FrameRect(hDC, &rcClient, -3, PATINVERT);
        Proc_DelayExec(100);
    } while (--uTimes);
    return ERROR_SUCCESS;
}

VOID AW_HighlightWindow(HWND hWnd) {
    Proc_CreateThread(HighlightWindowThread, hWnd, FALSE, NULL);
}