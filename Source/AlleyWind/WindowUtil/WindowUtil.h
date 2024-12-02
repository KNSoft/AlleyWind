#pragma once

#include "../AlleyWind.Core.inl"

EXTERN_C_START

// TODO: Read configuration
FORCEINLINE
W32ERROR
AW_SendMsgTO(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, PDWORD_PTR lpdwResult)
{
    return UI_SendMessageTimeout(hWnd, uMsg, wParam, lParam, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 200, lpdwResult);
}

FORCEINLINE
HICON
AW_GetWindowIcon(
    _In_ HWND Window)
{
    HICON hIcon = NULL;
    if (AW_SendMsgTO(Window, WM_GETICON, ICON_SMALL, 0, (PDWORD_PTR)&hIcon) != ERROR_SUCCESS || hIcon == NULL)
    {
        hIcon = (HICON)GetClassLongPtrW(Window, GCLP_HICON);
    }
    return hIcon;
}

EXTERN_C_END
