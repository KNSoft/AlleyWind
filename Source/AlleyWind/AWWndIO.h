#pragma once

#include "AlleyWind.h"

typedef struct _AW_ENUMCHILDREN {
    HTREEITEM   hParentNode;
    UINT        uCount;
} AW_ENUMCHILDREN, * PAW_ENUMCHILDREN;

LRESULT AW_SendMsgTO(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, PDWORD_PTR lpdwResult);

UINT AW_GetWindowTextEx(HWND hWnd, PWSTR psz, UINT cCh);
#define AW_GetWindowText(hWnd, psz) AW_GetWindowTextEx(hWnd, psz, ARRAYSIZE(psz))