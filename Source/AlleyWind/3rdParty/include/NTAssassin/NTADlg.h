#pragma once

#define DLG_PADDING_X   14
#define DLG_PADDING_Y   20
#define DLG_CONTROL_H   28
#define DLG_BUTTON_W    124

#include "NTAssassin\NTAssassin.h"

typedef struct _DLG_TEMPLATE {
    DLGTEMPLATE Template;
    WORD        wMenu;
    WORD        wClass;
    WORD        wTitle;
} DLG_TEMPLATE, * PDLG_TEMPLATE;

typedef struct _DLG_SCREENSNAPSHOT {
    // Input
    WNDPROC         pfnWndProc;
    HCURSOR         hCursor;
    HINSTANCE       hInstance;
    UINT            dwClassStyle;
    DWORD           dwStyle;
    DWORD           dwExStyle;
    PVOID           lParam;
    // Output
    GDI_SNAPSHOT    Snapshot;
} DLG_SCREENSNAPSHOT, * PDLG_SCREENSNAPSHOT;

#include "NTADlg_ValueEditor.h"
#include "NTADlg_RectEditor.h"

/**
  * @brief Initialize DLGTEMPLATE structure
  */
NTA_API LPDLGTEMPLATEW NTAPI Dlg_InitTemplate(PDLG_TEMPLATE Template, DWORD Style, DWORD ExtendedStyle, INT X, INT Y, INT Width, INT Height);

/**
  * @see "MessageBox"
  */
#define Dlg_MsgBox(Owner, Text, Title, Type) MessageBoxTimeoutW(Owner, Text, Title, Type, 0, -1)

/**
  * @see "GetOpenFileName" and "GetSaveFileName"
  */
NTA_API BOOL NTAPI Dlg_GetOpenFileNameEx(HWND Owner, PCWSTR Filter, PWSTR File, DWORD MaxFile, PCWSTR DefExt);
NTA_API BOOL NTAPI Dlg_GetSaveFileNameEx(HWND Owner, PCWSTR Filter, PWSTR File, DWORD MaxFile, PCWSTR DefExt);
#define Dlg_GetOpenFileName(Owner, Filter, File, DefExt) Dlg_GetOpenFileNameEx(Owner, Filter, File, ARRAYSIZE(File), DefExt)
#define Dlg_GetSaveFileName(Owner, Filter, File, DefExt) Dlg_GetSaveFileNameEx(Owner, Filter, File, ARRAYSIZE(File), DefExt)

/**
  * @see "ChooseColor"
  * @param[in] Owner Handle to owner window
  * @param[in, out] ColorPointer Pointer to a COLORREF specifies initial color and receives the result
  * @return Returns TRUE if a color was chosen, otherwise returns FALSE
  */
NTA_API BOOL NTAPI Dlg_ChooseColor(HWND Owner, LPCOLORREF ColorPointer);

/**
  * @see "ChooseFont"
  * @param[in] Owner Handle to owner window
  * @param[in, out] FontPointer Pointer to a LOGFONT specifies initial font and receives the result
  * @param[in, out] ColorPointer Pointer to a COLORREF specifies initial font color and receives the result, or NULL if ignore effects of font
  * @return Returns TRUE if a font was chosen, otherwise returns FALSE
  */
NTA_API BOOL NTAPI Dlg_ChooseFont(HWND Owner, PLOGFONTW FontPointer, LPCOLORREF ColorPointer);

/**
  * @brief Take snapshot for current screen and provide a new created window
  * @param[in] ScreenSnapshot Pointer to DLG_SCREENSNAPSHOT structure, input window parameters and receive screen size and snapshot DC
  * @note Useful to implement screen capturer or picker, and supports multiple-monitor
  * @return Returns TRUE if the window created and ended successfully, or FALSE if failed
  */
NTA_API BOOL NTAPI Dlg_ScreenSnapshot(PDLG_SCREENSNAPSHOT ScreenSnapshot);

typedef VOID(CALLBACK* DLG_RESIZEDPROC)(HWND Dialog, LONG NewWidth, LONG NewHeight, BOOL FromMgmtFunc);

/**
  * @brief Subclasses a dialog box to help support of resizing
  * @param[in] Dialog Handle to the dialog box
  * @param[in] MinWidth Minimum width of window, set to 0 will no limitation
  * @param[in] MinWidth Minimum height of window, set to 0 will no limitation
  * @param[in] ResizedProc Callback procedure will be invoked when the size of dialog box changed
  * @return Returns TRUE if subclass successfully, or FALSE if failed
  */
NTA_API BOOL NTAPI Dlg_SetResizingSubclass(HWND Dialog, LONG MinWidth, LONG MinHeight, DLG_RESIZEDPROC ResizedProc);