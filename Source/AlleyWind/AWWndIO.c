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
    c = AW_SendMsgTO(hWnd, WM_GETTEXT,  cCh, (LPARAM)psz, &dwCch) && (UINT)dwCch < cCh ?
        (UINT)dwCch :
    0;
    psz[c] = '\0';
    return c;
}