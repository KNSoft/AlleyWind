#pragma once

#include "NTAssassin.h"
#include "NTADlg_ValueEditor.h"

/**
  * @see "MessageBox"
  */
#define Dlg_MsgBoxW(hWnd, lpText, lpCaption, uType) MessageBoxTimeoutW(hWnd, lpText, lpCaption, uType, 0, -1)
#define Dlg_MsgBoxA(hWnd, lpText, lpCaption, uType) MessageBoxTimeoutA(hWnd, lpText, lpCaption, uType, 0, -1)
#ifdef UNICODE
#define Dlg_MsgBox Dlg_MsgBoxW
#else
#define Dlg_MsgBox Dlg_MsgBoxA
#endif

/**
  * @see "GetOpenFileName" and "GetSaveFileName"
  */
NTA_API BOOL NTAPI Dlg_GetOpenFileNameExW(HWND hwndOwner, LPCWSTR lpstrFilter, LPWSTR lpstrFile, DWORD nMaxFile, LPCWSTR lpstrDefExt);
NTA_API BOOL NTAPI Dlg_GetOpenFileNameExA(HWND hwndOwner, LPCSTR lpstrFilter, LPSTR lpstrFile, DWORD nMaxFile, LPCSTR lpstrDefExt);
NTA_API BOOL NTAPI Dlg_GetSaveFileNameExW(HWND hwndOwner, LPCWSTR lpstrFilter, LPWSTR lpstrFile, DWORD nMaxFile, LPCWSTR lpstrDefExt);
NTA_API BOOL NTAPI Dlg_GetSaveFileNameExA(HWND hwndOwner, LPCSTR lpstrFilter, LPSTR lpstrFile, DWORD nMaxFile, LPCSTR lpstrDefExt);
#define Dlg_GetOpenFileNameW(hwndOwner, lpstrFilter, lpstrFile, lpstrDefExt) Dlg_GetOpenFileNameExW(hwndOwner, lpstrFilter, lpstrFile, ARRAYSIZE(lpstrFile), lpstrDefExt)
#define Dlg_GetOpenFileNameA(hwndOwner, lpstrFilter, lpstrFile, lpstrDefExt) Dlg_GetOpenFileNameExA(hwndOwner, lpstrFilter, lpstrFile, ARRAYSIZE(lpstrFile), lpstrDefExt)
#define Dlg_GetSaveFileNameW(hwndOwner, lpstrFilter, lpstrFile, lpstrDefExt) Dlg_GetSaveFileNameExW(hwndOwner, lpstrFilter, lpstrFile, ARRAYSIZE(lpstrFile), lpstrDefExt)
#define Dlg_GetSaveFileNameA(hwndOwner, lpstrFilter, lpstrFile, lpstrDefExt) Dlg_GetSaveFileNameExA(hwndOwner, lpstrFilter, lpstrFile, ARRAYSIZE(lpstrFile), lpstrDefExt)
#ifdef UNICODE
#define Dlg_GetOpenFileNameEx Dlg_GetOpenFileNameExW
#define Dlg_GetSaveFileNameEx Dlg_GetSaveFileNameExW
#define Dlg_GetOpenFileName Dlg_GetOpenFileNameW
#define Dlg_GetSaveFileName Dlg_GetSaveFileNameW
#else
#define Dlg_GetOpenFileNameEx Dlg_GetOpenFileNameExA
#define Dlg_GetSaveFileNameEx Dlg_GetSaveFileNameExA
#define Dlg_GetOpenFileName Dlg_GetOpenFileNameA
#define Dlg_GetSaveFileName Dlg_GetSaveFileNameA
#endif

/**
  * @see "ChooseColor"
  * @param[in] hwndOwner Handle to owner window
  * @param[in, out] lpcrColor Pointer to a COLORREF specifies initial color and receives the result
  * @return Returns TRUE if a color was chosen, otherwise returns FALSE
  */
NTA_API BOOL NTAPI Dlg_ChooseColor(HWND hwndOwner, LPCOLORREF lpcrColor);

/**
  * @see "ChooseFont"
  * @param[in] hwndOwner Handle to owner window
  * @param[in, out] lplfFont Pointer to a LOGFONT specifies initial font and receives the result
  * @param[in, out] lpcrColor Pointer to a COLORREF specifies initial font color and receives the result, or NULL if ignore effects of font
  * @return Returns TRUE if a font was chosen, otherwise returns FALSE
  */
NTA_API BOOL NTAPI Dlg_ChooseFontW(HWND hwndOwner, LPLOGFONTW lplfFont, LPCOLORREF lpcrColor);
#ifdef UNICODE
#define Dlg_ChooseFont Dlg_ChooseFontW
#else
#define Dlg_ChooseFont Dlg_ChooseFontA
#endif

typedef struct _DLG_SCREENSNAPSHOTW {
    // Input
    WNDPROC     lpfnWndProc;
    HCURSOR     hCursor;
    HINSTANCE   hInstance;
    UINT        dwClassStyle;
    DWORD       dwStyle;
    DWORD       dwExStyle;
    LPVOID      lParam;
    // Output
    INT         iScreenX;
    INT         iScreenY;
    INT         iScreenCX;
    INT         iScreenCY;
    HDC         hdcMirror;
    HBITMAP     hbmMirror;
} DLG_SCREENSNAPSHOTW, * PDLG_SCREENSNAPSHOTW;
#ifdef UNICODE
#define DLG_SCREENSNAPSHOT DLG_SCREENSNAPSHOTW
#else
#define DLG_SCREENSNAPSHOT DLG_SCREENSNAPSHOTA
#endif

/**
  * @brief Take snapshot for current screen and provide a new created window
  * @param[in] lpstScreenSnapshot Pointer to DLG_SCREENSNAPSHOT structure, input window parameters and receive screen size and snapshot DC
  * @note Useful to implement screen capturer or picker, and supports multiple-monitor
  * @return Returns TRUE if the window created and ended successfully, or FALSE if failed
  */
NTA_API BOOL NTAPI Dlg_ScreenSnapshotW(PDLG_SCREENSNAPSHOTW lpstScreenSnapshot);
#ifdef UNICODE
#define Dlg_ScreenSnapshot Dlg_ScreenSnapshotW
#else
#define Dlg_ScreenSnapshot Dlg_ScreenSnapshotA
#endif

typedef struct _DLG_TEMPLATE {
    DLGTEMPLATE Template;
    WORD        wMenu;
    WORD        wClass;
    WORD        wTitle;
} DLG_TEMPLATE, * PDLG_TEMPLATE;