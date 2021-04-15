#pragma once

#include "NTAssassin.h"

#define UI_NOCHANGENOTIFYPROP TEXT("NTAssassin.UI.NoChangeNotify")

typedef struct _UI_WINDBPAINT {
    PAINTSTRUCT ps;
    HDC hDC;
    HBITMAP hBmp;
    RECT rcWnd;
}UI_WINDBPAINT, * PUI_WINDBPAINT;

typedef struct _UI_DPIINFO {
    DWORD   dwNewDPIX;
    DWORD   dwNewDPIY;
    DWORD   dwOldDPIX;
    DWORD   dwOldDPIY;
}UI_DPIINFO, * PUI_DPIINFO;

/**
  * @brief Gets rectangle of window relative to specified window
  * @param[in] hWnd Handle to the window to obtain the rectangle
  * @param[in] hWndRef Handle to the window relative to, parent window used if it is NULL
  * @param[out] lpRect Pointer to RECT structure to receive rectangle
  * @return Returns TRUE if successed, or FALSE if failed
  */
NTA_API BOOL NTAPI UI_GetRelativeRect(HWND hWnd, HWND hWndRef, LPRECT lpRect);

/**
  * @see "BeginPaint"
  * @note Performs Double-buffered painting
  */
NTA_API HDC NTAPI UI_BeginPaint(HWND hWnd, PUI_WINDBPAINT lpPaint);

/**
  * @brief Ends painting began by "UI_BeginPaint"
  * @see "EndPaint"
  */
NTA_API VOID NTAPI UI_EndPaint(HWND hWnd, PUI_WINDBPAINT lpPaint);

/**
  * @see "EnumChildWindows"
  * @note Implemented by "GetWindow"
  */
NTA_API VOID NTAPI UI_EnumChildWindows(HWND hWndParent, WNDENUMPROC lpfnEnum, LPARAM lParam);

/**
  * @see "SetWindowDisplayAffinity"
  */
NTA_API BOOL NTAPI UI_SetWindowDisplayAffinity(HWND hWnd, DWORD dwAffinity);

/**
  * @see "GetWindowDisplayAffinity"
  */
NTA_API BOOL NTAPI UI_GetWindowDisplayAffinity(HWND hWnd, DWORD* pdwAffinity);

/**
  * @brief Sets window theme as "Explorer" style
  * @see "SetWindowTheme"
  * @return Returns TRUE if succeed, or FALSE if failed
  */
NTA_API BOOL NTAPI UI_SetTheme(HWND hWnd);

/**
  * @brief Sets window big and small icons to specified icon
  * @see "WM_SETICON"
  */
NTA_API VOID NTAPI UI_SetWindowIcon(HWND hWnd, HICON hIcon);

typedef enum _UI_SHELLEXEC_VERB {
    UIShellExecEdit,
    UIShellExecExplore,
    UIShellExecFind,
    UIShellExecOpen,
    UIShellExecPrint,
    UIShellExecProperties,
    UIShellExecRunAs
} UI_SHELLEXEC_VERB, * PUI_SHELLEXEC_VERB;

/**
  * @see "ShellExecute" and "ShellExecuteEx"
  */
NTA_API BOOL NTAPI UI_ShellExecW(LPCWSTR lpszFile, LPCWSTR lpParameters, UI_SHELLEXEC_VERB Verb, INT nShowCmd, PHANDLE lphProc);
NTA_API BOOL NTAPI UI_ShellExecA(LPCSTR lpszFile, LPCSTR lpParameters, UI_SHELLEXEC_VERB Verb, INT nShowCmd, PHANDLE lphProc);
#ifdef UNICODE
#define UI_ShellExec UI_ShellExecW
#else
#define UI_ShellExec UI_ShellExecA
#endif

/**
  * @see "EnableWindow"
  */
#define UI_EnableDlgItem(hDlg, nIDItem, bEnable) EnableWindow(GetDlgItem(hDlg, nIDItem), bEnable)

/**
  * @see "SendMessage"
  */
#define UI_SendMsgW(hWnd, uMsg, wParam, lParam) SendMessageW(hWnd, uMsg, (WPARAM)(wParam), (LPARAM)(lParam))
#define UI_SendMsgA(hWnd, uMsg, wParam, lParam) SendMessageA(hWnd, uMsg, (WPARAM)(wParam), (LPARAM)(lParam))
#ifdef UNICODE
#define UI_SendMsg UI_SendMsgW
#else
#define UI_SendMsg UI_SendMsgA
#endif

/**
  * @see "SetDlgItemText"
  */
#define UI_SetDlgItemTextW(hDlg, nIDItem, lpszText) SendMessageW(GetDlgItem(hDlg, nIDItem), WM_SETTEXT, 0, (LPARAM)(lpszText))
#define UI_SetDlgItemTextA(hDlg, nIDItem, lpszText) SendMessageA(GetDlgItem(hDlg, nIDItem), WM_SETTEXT, 0, (LPARAM)(lpszText))
#ifdef UNICODE
#define UI_SetDlgItemText UI_SetDlgItemTextW
#else
#define UI_SetDlgItemText UI_SetDlgItemTextA
#endif

/**
  * @see "GetDlgItemText"
  */
#define UI_GetDlgItemTextW(hDlg, nIDItem, lpszText) SendMessageW(GetDlgItem(hDlg, nIDItem), WM_GETTEXT, ARRAYSIZE(lpszText), (LPARAM)(lpszText))
#define UI_GetDlgItemTextA(hDlg, nIDItem, lpszText) SendMessageA(GetDlgItem(hDlg, nIDItem), WM_GETTEXT, ARRAYSIZE(lpszText), (LPARAM)(lpszText))
#ifdef UNICODE
#define UI_GetDlgItemText UI_GetDlgItemTextW
#else
#define UI_GetDlgItemText UI_GetDlgItemTextA
#endif

/**
  * @see "IsDlgButtonChecked"
  */
#define UI_GetDlgButtonCheckW(hDlg, nIDButton) SendMessageW(GetDlgItem(hDlg, nIDButton), BM_GETCHECK, 0, 0)
#define UI_GetDlgButtonCheckA(hDlg, nIDButton) SendMessageA(GetDlgItem(hDlg, nIDButton), BM_GETCHECK, 0, 0)
#ifdef UNICODE
#define UI_GetDlgButtonCheck UI_GetDlgButtonCheckW
#else
#define UI_GetDlgButtonCheck UI_GetDlgButtonCheckA
#endif

/**
  * @see "CheckDlgButton"
  */
#define UI_SetDlgButtonCheckW(hDlg, nIDButton, uCheck) SendMessageW(GetDlgItem(hDlg, nIDButton), BM_SETCHECK, (WPARAM)(uCheck), 0)
#define UI_SetDlgButtonCheckA(hDlg, nIDButton, uCheck) SendMessageA(GetDlgItem(hDlg, nIDButton), BM_SETCHECK, (WPARAM)(uCheck), 0)
#ifdef UNICODE
#define UI_SetDlgButtonCheck UI_SetDlgButtonCheckW
#else
#define UI_SetDlgButtonCheck UI_SetDlgButtonCheckA
#endif

/**
  * @see "SendDlgItemMessage"
  */
#define UI_SendDlgItemMsgW(hDlg, nIDItem, uMsg, wParam, lParam) SendMessageW(GetDlgItem(hDlg, nIDItem), uMsg, (WPARAM)(wParam), (LPARAM)(lParam))
#define UI_SendDlgItemMsgA(hDlg, nIDItem, uMsg, wParam, lParam) SendMessageA(GetDlgItem(hDlg, nIDItem), uMsg, (WPARAM)(wParam), (LPARAM)(lParam))
#ifdef UNICODE
#define UI_SendDlgItemMsg UI_SendDlgItemMsgW
#else
#define UI_SendDlgItemMsg UI_SendDlgItemMsgA
#endif

/**
  * @see "GetProp"
  */
#define UI_GetDlgItemPropW(hDlg, nIDItem, lpszProp) GetPropW(GetDlgItem(hDlg, nIDItem), lpszProp)
#define UI_GetDlgItemPropA(hDlg, nIDItem, lpszProp) GetPropA(GetDlgItem(hDlg, nIDItem), lpszProp)
#ifdef UNICODE
#define UI_GetDlgItemProp UI_GetDlgItemPropW
#else
#define UI_GetDlgItemProp UI_GetDlgItemPropA
#endif

/**
  * @see "SetWindowPos"
  */
#define UI_SetWindowRect(hWnd, lprc) SetWindowPos(hWnd, NULL, (lprc)->left, (lprc)->top, (lprc)->right - (lprc)->left, (lprc)->bottom - (lprc)->top, SWP_NOZORDER | SWP_NOACTIVATE);

/**
  * @brief Inverses a RGB color
  * @param[in] rgb The RGB color to be inversed
  * @return Returns a RGB color being inversed
  */
#define UI_InverseRGB(rgb) ((COLORREF)(~(rgb) & 0xFFFFFF))

/**
  * @brief Invalidates and updates the window immediately
  * @see "RedrawWindow"
  */
#define UI_Redraw(hWnd) RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW)

/**
  * @brief Enables or disables specified style or extended style for a widnow
  * @param[in] hWnd Handle to the window to modify the style
  * @param[in] nIndex GWL_STYLE or GWL_EXSTYLE
  * @param[in] lStyleFlag The style flags to enable or disable
  * @param[in] bEnable Set to TRUE to enable or FALSE to disable
  * @see "SetWindowLongPtr"
  */
NTA_API BOOL NTAPI UI_EnableWindowStyle(HWND hWnd, INT nIndex, LONG_PTR lStyleFlag, BOOL bEnable);

/**
  * @brief Opens process that created specified window
  * @param[in] dwDesiredAccess The access to the process object
  * @param[in] hWnd Handle to the window
  * @return Returns the process handle or NULL if failed
  * @see "GetWindowThreadProcessId" and "OpenProcess"
  */
NTA_API HANDLE NTAPI UI_OpenProc(DWORD dwDesiredAccess, HWND hWnd);

/**
  * @brief Gets full process image path of specified window
  * @param[in] hWnd Handle to the window
  * @param[in] pszFileName Pointer to the buffer receives image path
  * @param[in] cchFileNameMax Number of characters the pszFileName could contain
  * @return Returns the number of characters copied to the buffer, or 0 if failed
  */
NTA_API UINT NTAPI UI_GetWindowModuleFileNameW(HWND hWnd, LPWSTR pszFileName, UINT cchFileNameMax);
#ifdef UNICODE
#define UI_GetWindowModuleFileName UI_GetWindowModuleFileNameW
#else
#define UI_GetWindowModuleFileName UI_GetWindowModuleFileNameA
#endif

// "UI_SetNoChangeNotify" and "UI_IsSetNoChangeNotify" are useful to avoid endless loop in some notification handling,
// caused by the same notification was triggled again during the handling

/**
  * @brief Sets a flag and verified by "UI_IsSetNoChangeNotify"
  * @param[in] hWnd Handle to the window
  * @param[in] bEnable TRUE to set the flag, or FALSE to remove
  * @return Returns TRUE if the flag set or remove successfully, or FALSE if failed
  */
NTA_API BOOL NTAPI UI_SetNoChangeNotify(HWND hWnd, BOOL bEnable);

/**
  * @brief Verifies the flag set by "UI_SetNoChangeNotify"
  * @param[in] hWnd Handle to the window
  * @return Returns TRUE if the flag was set, or FALSE if not set
  */
NTA_API BOOL NTAPI UI_IsSetNoChangeNotify(HWND hWnd);

/**
  * @brief Sets "NoChangeNotify" flag and send message to change specified window text
  * @param[in] hWnd Handle to the window
  * @param[in] lpszText Text to be set
  * @return See "WM_SETTEXT"
  * @see "UI_SetNoChangeNotify" and "WM_SETTEXT"
  */
NTA_API LRESULT NTAPI UI_SetWndTextNoNotifyW(HWND hWnd, LPCWSTR lpszText);
NTA_API LRESULT NTAPI UI_SetWndTextNoNotifyA(HWND hWnd, LPCSTR lpszText);
#ifdef UNICODE
#define UI_SetWndTextNoNotify UI_SetWndTextNoNotifyW
#else
#define UI_SetWndTextNoNotify UI_SetWndTextNoNotifyA
#endif