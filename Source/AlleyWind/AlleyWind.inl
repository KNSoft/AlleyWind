#pragma once

#define OEMRESOURCE
#define STRICT_TYPED_ITEMIDS
#define MLE_API
#define _USE_COMMCTL60

#include <KNSoft/NDK/NDK.h>
#include <MakeLifeEasier.h>

#include "Resource.h"

#pragma comment (lib, "Comctl32.lib")

#define MAX_WNDCAPTION_CCH 128

// TODO: Read configuration
FORCEINLINE
LRESULT
AW_SendMsgTO(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, PDWORD_PTR lpdwResult)
{
    return SendMessageTimeoutW(hWnd, uMsg, wParam, lParam, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 200, lpdwResult);
}

EXTERN_C
W32ERROR
UpdateWindowTreeAsync(VOID);

EXTERN_C
INT_PTR
CALLBACK
MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
