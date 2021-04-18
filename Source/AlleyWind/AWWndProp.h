#pragma once

#include "AlleyWind.h"

#define AW_WNDPROP_HWND TEXT("AlleyWind.WndProp.hWnd")

CTL_LISTCTL_COLUME aExtraBytesListCol[2];

HWND AW_GetWndPropHWnd(HWND hDlg);
BOOL AW_SetWndPropHWnd(HWND hDlg, HWND hWnd);
HWND AW_RemoveWndPropHWnd(HWND hDlg);

VOID AW_SetPropCtlFormat(HWND hDlg, UINT uCtlID, BOOL bSuccess, _Printf_format_string_ LPTSTR lpszFormat, ...);

VOID AW_SetPropCtlString(HWND hDlg, UINT uCtlID, LPCWSTR lpszString, BOOL bSuccess);

VOID AW_SetPropCtlCheck(HWND hDlg, UINT uCtlID, UINT_PTR uCheck, BOOL bSuccess);

VOID AW_SetPropCtlRect(HWND hDlg, UINT uCtlID, PRECT lpRect, BOOL bSuccess);

BOOL CALLBACK AW_WndPropExtraBytesEnumProc(DWORD dwOffset, LONG_PTR lBytes, UINT uSize, DWORD dwError, LPARAM lParam);
BOOL AW_EnumExtraBytes(HWND hWnd, BOOL bClassExtraBytes, LPARAM lParam);