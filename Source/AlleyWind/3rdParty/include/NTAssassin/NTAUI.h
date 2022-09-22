#pragma once

#include "NTADef.h"

#define UI_NONOTIFYPROP TEXT("NTAssassin.UI.NoNotify")

typedef struct _UI_WINDBPAINT {
    PAINTSTRUCT Paint;  // Native PAINTSTRUCT structure from "BeginPaint"
    HDC         DC;     // Compatible memory DC
    HBITMAP     Bitmap; // Compatible memory bitmap
    RECT        Rect;   // RECT of window client area
} UI_WINDBPAINT, * PUI_WINDBPAINT;

/// <seealso cref="BeginPaint"/>
/// <remarks>Double-buffered painting intergrated</remarks>
NTA_API HDC NTAPI UI_BeginPaint(HWND Window, _Out_ PUI_WINDBPAINT Paint);

/// <summary>
/// Ends painting began by <c>UI_BeginPaint</c>
/// </summary>
/// <seealso cref="EndPaint"/>
NTA_API VOID NTAPI UI_EndPaint(HWND Window, _In_ PUI_WINDBPAINT Paint);

/// <seealso cref="GetWindowRect"/>
/// <remarks>With DWM frame bounds correction</remarks>
NTA_API BOOL NTAPI UI_GetWindowRect(HWND Window, _Out_ PRECT Rect);

/// <seealso cref="SetWindowPos"/>
/// <remarks>With DWM frame bounds correction</remarks>
NTA_API BOOL NTAPI UI_SetWindowRect(HWND Window, _In_ PRECT Rect);

/// <summary>
/// Gets position of window relative to specified window
/// </summary>
/// <param name="Window">Handle to the window to obtain position</param>
/// <param name="RefWindow">Handle to the window relative to, parent window used if inputs NULL</param>
/// <param name="Rect">Pointer to a RECT structure to receive position</param>
/// <returns>TRUE if successed, or FALSE if failed</returns>
_Success_(return != FALSE) NTA_API BOOL NTAPI UI_GetRelativeRect(HWND Window, HWND RefWindow, _Out_ PRECT Rect);

/// <seealso cref="EnumChildWindows"/>
/// <remarks>Implemented by <c>GetWindow</c></remarks>
NTA_API VOID NTAPI UI_EnumChildWindows(HWND ParentWindow, _In_ WNDENUMPROC WindowEnumProc, LPARAM Param);

/// <seealso cref="DwmIsCompositionEnabled"/>
NTA_API BOOL NTAPI UI_IsDWMComposited();

/// <seealso cref = "DwmGetWindowAttribute"/>
/// <seealso cref = "DWMWA_CLOAKED"/>
NTA_API DWORD NTAPI UI_GetWindowCloackedState(HWND Window);

/// <summary>
/// Sets window theme to "Explorer" style
/// </summary>
/// <seealso cref="SetWindowTheme"/>
/// <returns>TRUE if succeed, or FALSE if failed</returns>
NTA_API BOOL NTAPI UI_SetTheme(HWND Window);

/// <seealso cref="EnableWindow"/>
#define UI_EnableDlgItem(Dialog, ItemID, EnableState) EnableWindow(GetDlgItem(Dialog, ItemID), EnableState)

/// <seealso cref="SendMessage"/>
#define UI_SendMsg(Window, Msg, wParam, lParam) SendMessage(Window, Msg, (WPARAM)(wParam), (LPARAM)(lParam))

/// <seealso cref="SendDlgItemMessage"/>
#define UI_SendDlgItemMsg(Dialog, ItemID, Msg, wParam, lParam) SendMessage(GetDlgItem(Dialog, ItemID), Msg, (WPARAM)(wParam), (LPARAM)(lParam))

/// <seealso cref="IsDlgButtonChecked"/>
#define UI_GetDlgButtonCheck(Dialog, ButtonID) SendMessage(GetDlgItem(Dialog, ButtonID), BM_GETCHECK, 0, 0)

/// <seealso cref="CheckDlgButton"/>
#define UI_SetDlgButtonCheck(Dialog, ButtonID, CheckState) SendMessageW(GetDlgItem(Dialog, ButtonID), BM_SETCHECK, (WPARAM)(CheckState), 0)

/// <seealso cref="SetWindowText"/>
#define UI_SetWindowTextW(Window, Text) SendMessageW(Window, WM_SETTEXT, 0, (LPARAM)(Text))
#define UI_SetWindowTextA(Window, Text) SendMessageA(Window, WM_SETTEXT, 0, (LPARAM)(Text))
#ifdef UNICODE
#define UI_SetWindowText UI_SetWindowTextW
#else
#define UI_SetWindowText UI_SetWindowTextA
#endif

/// <seealso cref="SetDlgItemText"/>
#define UI_SetDlgItemTextW(Dialog, ItemID, Text) UI_SetWindowTextW(GetDlgItem(Dialog, ItemID), Text)
#define UI_SetDlgItemTextA(Dialog, ItemID, Text) UI_SetWindowTextA(GetDlgItem(Dialog, ItemID), Text)
#ifdef UNICODE
#define UI_SetDlgItemText UI_SetDlgItemTextW
#else
#define UI_SetDlgItemText UI_SetDlgItemTextA
#endif

/// <seealso cref="GetProp"/>
#define UI_GetDlgItemProp(Dialog, ItemID, Prop) GetPropW(GetDlgItem(Dialog, ItemID), Prop)

/// <seealso cref="PtInRect"/>
#define UI_PtInRect(Rect, Point) (((Point).x >= (Rect)->left) && ((Point).x < (Rect)->right) && ((Point).y >= (Rect)->top) && ((Point).y < (Rect)->bottom))

/// <summary>
/// Inverses a RGB color
/// </summary>
/// <param name="Color">RGB color to be inversed</param>
/// <returns>RGB color being inversed</returns>
#define UI_InverseRGB(Color) ((COLORREF)(~(Color) & 0xFFFFFF))

/// <summary>
/// Invalidates and updates the whole window immediately
/// </summary>
/// <seealso cref="RedrawWindow"/>
#define UI_Redraw(Window) RedrawWindow(Window, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_UPDATENOW)

/// <summary>
/// Enables or disables specified style or extended style for a widnow
/// </summary>
/// <seealso cref="SetWindowLongPtr"/>
/// <param name="Window">Handle to the window</param>
/// <param name="StyleIndex">GWL_STYLE or GWL_EXSTYLE</param>
/// <param name="StyleFlag">The style flags to enable or disable</param>
/// <param name="EnableState">Set to TRUE to enable or FALSE to disable</param>
/// <returns>TRUE if succeeded, or FALSE if failed</returns>
NTA_API BOOL NTAPI UI_EnableWindowStyle(HWND Window, INT StyleIndex, LONG_PTR StyleFlag, BOOL EnableState);

/// <summary>
/// Opens process who owns specified window
/// </summary>
/// <param name="DesiredAccess">The access to the process object</param>
/// <param name="Window">Handle to the window</param>
/// <returns>The process handle or NULL if failed</returns>
NTA_API HANDLE NTAPI UI_OpenProc(DWORD DesiredAccess, HWND Window);

// Set window text without notify, useful to avoid endless loop caused by notification triggled when handling itself
NTA_API BOOL NTAPI UI_SetNoNotifyFlag(HWND Window, BOOL EnableState);
NTA_API BOOL NTAPI UI_GetNoNotifyFlag(HWND Window);
NTA_API LRESULT NTAPI UI_SetWndTextNoNotify(HWND Window, _In_opt_ PCWSTR Text);

/**
  * @see "GetWindowTextW"
  * @note Sometimes "WM_GETTEXT" works incorrectly, this function may safer
  */

  /// <seealso cref="WM_GETTEXT"/>
  /// <remarks><c>WM_GETTEXT</c> may not writting null-terminates in some cases, this wrapper fixes it</remarks>
NTA_API _Success_(return > 0) UINT NTAPI UI_GetWindowTextExW(HWND Window, _Out_writes_z_(TextCch) PWSTR Text, UINT TextCch);
NTA_API _Success_(return > 0) UINT NTAPI UI_GetWindowTextExA(HWND Window, _Out_writes_z_(TextCch) PSTR Text, UINT TextCch);
#define UI_GetWindowTextW(Window, Text) UI_GetWindowTextExW(Window, Text, ARRAYSIZE(Text))
#define UI_GetDlgItemTextExW(Dialog, ItemID, Text, TextCch) UI_GetWindowTextExW(GetDlgItem(Dialog, ItemID), Text, TextCch)
#define UI_GetDlgItemTextW(Dialog, ItemID, Text) UI_GetDlgItemTextExW(Dialog, ItemID, Text, ARRAYSIZE(Text))
#define UI_GetWindowTextA(Window, Text) UI_GetWindowTextExA(Window, Text, ARRAYSIZE(Text))
#define UI_GetDlgItemTextExA(Dialog, ItemID, Text, TextCch) UI_GetWindowTextExA(GetDlgItem(Dialog, ItemID), Text, TextCch)
#define UI_GetDlgItemTextA(Dialog, ItemID, Text) UI_GetDlgItemTextExA(Dialog, ItemID, Text, ARRAYSIZE(Text))
#ifdef UNICODE
#define UI_GetWindowText UI_GetWindowTextW
#define UI_GetDlgItemTextEx UI_GetDlgItemTextExW
#define UI_GetDlgItemText UI_GetDlgItemTextW
#else
#define UI_GetWindowText UI_GetWindowTextA
#define UI_GetDlgItemTextEx UI_GetDlgItemTextExA
#define UI_GetDlgItemText UI_GetDlgItemTextA
#endif

/// <seealso cref="GetWindowLongPtr"/>
/// <seealso cref="GetClassLongPtr"/>
/// <remarks><c>GetWindowLongPtr</c> may crash in some cases, this wrapper fixes it</remarks>
NTA_API _Success_(return != FALSE) BOOL NTAPI UI_GetWindowLong(HWND Window, BOOL ClassLong, INT Index, _Out_ PLONG_PTR Result);

/// <summary>
/// Enters message loop for specified window
/// <see href="https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmessage">GetMessage - MSDN</see>
/// </summary>
/// <param name="Window">Handle to the window, NULL to loop all windows belong to current thread</param>
/// <param name="ExitCode">Pointer to a variable receives exit code</param>
/// <returns>TRUE if the loop ended when receives WM_QUIT, or FALSE when an error occurred</returns>
NTA_API _Success_(return != FALSE) BOOL NTAPI UI_MessageLoop(HWND Window, _Out_opt_ PUINT_PTR ExitCode);

/// <summary>
/// Gets position and size of virtual screen (multiple monitors support)
/// </summary>
/// <param name="Point">Pointer to a POINT structure receives position of virtual screen</param>
/// <param name="Size">Pointer to a SIZE structure receives size of virtual screen</param>
NTA_API VOID NTAPI UI_GetScreenPos(_Out_opt_ PPOINT Point, _Out_opt_ PSIZE Size);

/// <summary>
/// Allows WM_DROPFILES message, especially in an elevated application
/// </summary>
/// <param name="Window">Handle to the window</param>
/// <returns>TRUE if successed, or FALSE if failed</returns>
NTA_API BOOL NTAPI UI_AllowDrop(HWND Window);
