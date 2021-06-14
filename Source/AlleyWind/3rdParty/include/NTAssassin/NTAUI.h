#pragma once

#include "NTAssassin\NTAssassin.h"

#define UI_NONOTIFYPROP TEXT("NTAssassin.UI.NoNotify")

typedef struct _UI_WINDBPAINT {
    PAINTSTRUCT Paint;  // Native PAINTSTRUCT structure from "BeginPaint"
    HDC         DC;     // Compatible memory DC
    HBITMAP     Bitmap; // Compatible memory bitmap
    RECT        Rect;   // RECT of window client area
} UI_WINDBPAINT, * PUI_WINDBPAINT;

/**
  * @see "BeginPaint"
  * @note Double-buffered painting intergrated
  */
NTA_API HDC NTAPI UI_BeginPaint(HWND Window, PUI_WINDBPAINT Paint);

/**
  * @brief Ends painting began by "UI_BeginPaint"
  * @see "EndPaint"
  */
NTA_API VOID NTAPI UI_EndPaint(HWND Window, PUI_WINDBPAINT Paint);

/**
  * @see "GetWindowRect"
  * @note Fixes frame bounds when DWM composition enabled
  */
NTA_API BOOL NTAPI UI_GetWindowRect(HWND Window, PRECT Rect);

/**
  * @brief Gets position of window relative to specified window
  * @param[in] Window Handle to the window to obtain position
  * @param[in] RefWindow Handle to the window relative to, parent window used if it is NULL
  * @param[out] Rect Pointer to RECT structure to receive position
  * @return Returns TRUE if successed, or FALSE if failed
  */
NTA_API BOOL NTAPI UI_GetRelativeRect(HWND Window, HWND RefWindow, PRECT Rect);

/**
  * @see "EnumChildWindows"
  * @note Implemented by "GetWindow"
  */
NTA_API VOID NTAPI UI_EnumChildWindows(HWND ParentWindow, WNDENUMPROC WindowEnumProc, LPARAM Param);

/**
  * @see "DwmIsCompositionEnabled"
  */
NTA_API BOOL NTAPI UI_IsDWMComposited();

/**
  * @see "DwmGetWindowAttribute" and "DWMWA_CLOAKED"
  */
DWORD NTAPI UI_GetWindowCloackedState(HWND Window);

/**
  * @see "GetWindowDisplayAffinity"
  */
NTA_API BOOL NTAPI UI_GetWindowDisplayAffinity(HWND Window, PDWORD Affinity);

/**
  * @see "SetWindowDisplayAffinity"
  */
NTA_API BOOL NTAPI UI_SetWindowDisplayAffinity(HWND Window, DWORD Affinity);

/**
  * @brief Sets window theme to "Explorer" style
  * @see "SetWindowTheme"
  * @return Returns TRUE if succeed, or FALSE if failed
  */
NTA_API BOOL NTAPI UI_SetTheme(HWND Window);

/**
  * @brief Sets window big and small icons to specified icon
  * @see "WM_SETICON"
  */
NTA_API VOID NTAPI UI_SetWindowIcon(HWND Window, HICON Icon);

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
  * @note Invokes "SHOpenFolderAndSelectItems" to implement UIShellExecExplore instead
  */
NTA_API BOOL NTAPI UI_ShellExec(PCWSTR File, PCWSTR Param, UI_SHELLEXEC_VERB Verb, INT ShowCmd, PHANDLE ProcessHandle);

/**
  * @see "EnableWindow"
  */
#define UI_EnableDlgItem(Dialog, ItemID, EnableState) EnableWindow(GetDlgItem(Dialog, ItemID), EnableState)

/**
  * @see "SendMessageW"
  */
#define UI_SendMsg(Window, Msg, wParam, lParam) SendMessageW(Window, Msg, (WPARAM)(wParam), (LPARAM)(lParam))

/**
  * @see "SendDlgItemMessage"
  */
#define UI_SendDlgItemMsg(Dialog, ItemID, Msg, wParam, lParam) SendMessageW(GetDlgItem(Dialog, ItemID), Msg, (WPARAM)(wParam), (LPARAM)(lParam))

/**
  * @see "IsDlgButtonChecked"
  */
#define UI_GetDlgButtonCheck(Dialog, ButtonID) SendMessageW(GetDlgItem(Dialog, ButtonID), BM_GETCHECK, 0, 0)

/**
  * @see "CheckDlgButton"
  */
#define UI_SetDlgButtonCheck(Dialog, ButtonID, CheckState) SendMessageW(GetDlgItem(Dialog, ButtonID), BM_SETCHECK, (WPARAM)(CheckState), 0)

/**
  * @see "GetProp"
  */
#define UI_GetDlgItemProp(Dialog, ItemID, Prop) GetPropW(GetDlgItem(Dialog, ItemID), Prop)

/**
  * @see "SetWindowPos"
  */
#define UI_SetWindowRect(Window, Rect) SetWindowPos(Window, NULL, (Rect)->left, (Rect)->top, (Rect)->right - (Rect)->left, (Rect)->bottom - (Rect)->top, SWP_NOZORDER | SWP_NOACTIVATE);

/**
  * @see "PtInRect"
  */
#define UI_PtInRect(Rect, Point) (((Point).x >= (Rect)->left) && ((Point).x < (Rect)->right) && ((Point).y >= (Rect)->top) && ((Point).y < (Rect)->bottom))

/**
  * @brief Inverses a RGB color
  * @param[in] rgb The RGB color to be inversed
  * @return Returns a RGB color being inversed
  */
#define UI_InverseRGB(Color) ((COLORREF)(~(Color) & 0xFFFFFF))

/**
  * @brief Invalidates and updates the whole window immediately
  * @see "RedrawWindow"
  */
#define UI_Redraw(Window) RedrawWindow(Window, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW)

/**
  * @brief Enables or disables specified style or extended style for a widnow
  * @param[in] Window Handle to the window to modify the style
  * @param[in] StyleIndex GWL_STYLE or GWL_EXSTYLE
  * @param[in] StyleFlag The style flags to enable or disable
  * @param[in] EnableState Set to TRUE to enable or FALSE to disable
  * @return Returns TRUE if operation succcessfully, or FALSE if failed
  * @see "SetWindowLongPtr"
  */
NTA_API BOOL NTAPI UI_EnableWindowStyle(HWND Window, INT StyleIndex, LONG_PTR StyleFlag, BOOL EnableState);

/**
  * @brief Opens process who owns specified window
  * @param[in] DesiredAccess The access to the process object
  * @param[in] Window Handle to the window
  * @return Returns the process handle or NULL if failed
  * @see "GetWindowThreadProcessId" and "OpenProcess"
  */
NTA_API HANDLE NTAPI UI_OpenProc(DWORD DesiredAccess, HWND Window);

/**
  * @brief Gets full image path of process who owns specified window
  * @see "RProc_GetFullImageNameEx"
  */
NTA_API UINT NTAPI UI_GetWindowModuleFileNameEx(HWND Window, PWSTR FileName, UINT FileNameCch);
#define UI_GetWindowModuleFileName(Window, FileName) UI_GetWindowModuleFileNameEx(Window, FileName, ARRAYSIZE(FileName))

/**
  * @brief Sets a flag and can be obtained by "UI_GetNoNotifyFlag"
  * @param[in] Window Handle to the window
  * @param[in] EnableState TRUE to set the flag, or FALSE to remove
  * @return Returns TRUE if the flag set or remove successfully, or FALSE if failed
  * @note Useful to avoid endless loop caused by notification triggled when handling itself
  */
NTA_API BOOL NTAPI UI_SetNoNotifyFlag(HWND Window, BOOL EnableState);

/**
  * @brief Gets the flag set by "UI_SetNoNotifyFlag"
  * @param[in] Window Handle to the window
  * @return Returns TRUE if the flag was set, or FALSE if not
  */
NTA_API BOOL NTAPI UI_GetNoNotifyFlag(HWND Window);

/**
  * @brief Sets "NoNotify" flag and send message to change text of specified window
  * @param[in] Window Handle to the window
  * @param[in] Text Text to be set
  * @return See "WM_SETTEXT"
  * @see "UI_SetNoNotifyFlag" and "WM_SETTEXT"
  */
NTA_API LRESULT NTAPI UI_SetWndTextNoNotify(HWND Window, PCWSTR Text);

#define UI_SetWindowText(Window, Text) SendMessageW(Window, WM_SETTEXT, 0, (LPARAM)(Text))
#define UI_SetDlgItemText(Dialog, ItemID, Text) UI_SetWindowText(GetDlgItem(Dialog, ItemID), Text)

/**
  * @see "GetWindowTextW"
  * @note Sometimes "WM_GETTEXT" works incorrectly, this function may safer
  */
NTA_API UINT NTAPI UI_GetWindowTextEx(HWND Window, PWSTR Text, UINT TextCch);
#define UI_GetWindowText(Window, Text) UI_GetWindowTextEx(Window, Text, ARRAYSIZE(Text))
#define UI_GetDlgItemTextEx(Dialog, ItemID, Text, TextCch) UI_GetWindowTextEx(GetDlgItem(Dialog, ItemID), Text, TextCch)
#define UI_GetDlgItemText(Dialog, ItemID, Text) UI_GetDlgItemTextEx(Dialog, ItemID, Text, ARRAYSIZE(Text))

/**
  * @see "GetWindowLongPtrW" and "GetClassLongPtrW"
  * @note Sometimes "GetWindowLongPtrW" and "GetClassLongPtrW" work incorrectly, this function may safer
  * @param[in] Window Handle to the window
  * @param[in] ClassLong Set to TRUE to invoke "GetClassLongPtrW", or FALSE to invoke "GetWindowLongPtrW"
  * @param[in] Index The zero-based offset to the value to be retrieved
  * @param[out] Result Pointer to the variable receives the result
  * @return Returns Win32 error code, ERROR_SUCCESS means succeeded
  */
NTA_API DWORD NTAPI UI_GetWindowLong(HWND Window, BOOL ClassLong, INT Index, PLONG_PTR Result);

/**
  * @brief Enters message loop for specified window
  * @param[in] Window Handle to the window
  * @return Returns TRUE if the loop ended when receives WM_QUIT, or FALSE when an error occurred
  */
NTA_API BOOL NTAPI UI_MessageLoop(HWND Window);

/**
  * @brief Gets position and size of virtual screen
  * @param[in] Point Pointer to a POINT structure receives position of virtual screen
  * @param[in] Size Pointer to a SIZE structure receives size of virtual screen
  */
NTA_API VOID NTAPI UI_GetScreenPos(PPOINT Point, PSIZE Size);