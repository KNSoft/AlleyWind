#pragma once

#include "NTADef.h"

#include "NTAGDI.h"

#define DLG_PADDING_X   14
#define DLG_PADDING_Y   20
#define DLG_CONTROL_H   28
#define DLG_BUTTON_W    124

typedef struct _DLG_TEMPLATE {
    DLGTEMPLATE Template;
    WORD        wMenu;
    WORD        wClass;
    WORD        wTitle;
} DLG_TEMPLATE, *PDLG_TEMPLATE;

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
} DLG_SCREENSNAPSHOT, *PDLG_SCREENSNAPSHOT;

typedef struct _DLG_TREEVIEWPROPSHEETPAGE DLG_TREEVIEWPROPSHEETPAGE, *PDLG_TREEVIEWPROPSHEETPAGE;
struct _DLG_TREEVIEWPROPSHEETPAGE {
    PWSTR       DisplayName;
    HINSTANCE   Instance;
    INT         DlgResID;
    DLGPROC     DlgProc;
    LPARAM      Param;
    PDLG_TREEVIEWPROPSHEETPAGE  SubItems;
    UINT                        Count;
    HANDLE                      Handle;     // Reserved
    HTREEITEM                   TreeItem;   // Reserved
};

/// <summary>
/// Initializes DLGTEMPLATE structure
/// </summary>
/// <param name="Template">Pointer to a DLG_TEMPLATE structure to be initialized</param>
/// <param name="Style">Window styles</param>
/// <param name="ExtendedStyle">Window extended styles</param>
/// <param name="X">Window X position</param>
/// <param name="Y">Window Y position</param>
/// <param name="Width">Window width</param>
/// <param name="Height">Window height</param>
/// <returns>Pointer to a DLGTEMPLATEW structure in DLG_TEMPLATE</returns>
NTA_API LPDLGTEMPLATEW NTAPI Dlg_InitTemplate(_Out_ PDLG_TEMPLATE Template, DWORD Style, DWORD ExtendedStyle, INT X, INT Y, INT Width, INT Height);

/// <summary>
/// Displays a modal dialog box
/// </summary>
/// <seealso cref="MessageBox"/>
#define Dlg_MsgBox(Owner, Text, Title, Type) MessageBoxTimeoutW(Owner, Text, Title, Type, 0, -1)

/// <summary>
/// Creates an Open dialog box that lets the user specify the drive, directory, and the name of a file or set of files to be opened
/// </summary>
/// <seealso cref="GetOpenFileName"/>
NTA_API BOOL NTAPI Dlg_GetOpenFileNameEx(HWND Owner, PCWSTR Filter, PWSTR File, DWORD CchFile, PCWSTR DefExt);

/// <summary>
/// Creates a Save dialog box that lets the user specify the drive, directory, and name of a file to save
/// </summary>
/// <seealso cref="GetSaveFileName"/>
NTA_API BOOL NTAPI Dlg_GetSaveFileNameEx(HWND Owner, PCWSTR Filter, PWSTR File, DWORD MaxFile, PCWSTR DefExt);

#define Dlg_GetOpenFileName(Owner, Filter, File, DefExt) Dlg_GetOpenFileNameEx(Owner, Filter, File, ARRAYSIZE(File), DefExt)
#define Dlg_GetSaveFileName(Owner, Filter, File, DefExt) Dlg_GetSaveFileNameEx(Owner, Filter, File, ARRAYSIZE(File), DefExt)

/// <summary>
/// Creates a Color dialog box that enables the user to select a color
/// </summary>
/// <param name="Owner">Handle to the owner window</param>
/// <param name="Color">Pointer to a COLORREF to set initial color and receive the color value user picked</param>
/// <returns>TRUE if a color was picked, or FALSE if user canceled or an error occured</returns>
NTA_API BOOL NTAPI Dlg_ChooseColor(HWND Owner, _Inout_ LPCOLORREF Color);

/// <summary>
/// Creates a Font dialog box that enables the user to choose attributes for a logical font
/// </summary>
/// <param name="Owner">Handle to the owner window</param>
/// <param name="Font">Pointer to a LOGFONT specifies initial font and receives the result</param>
/// <param name="Color">Pointer to a COLORREF specifies initial font color and receives the result, or NULL if ignore effects of font</param>
/// <returns>TRUE if a font was chosen, or FALSE if user canceled or an error occured</returns>
NTA_API BOOL NTAPI Dlg_ChooseFont(HWND Owner, _Inout_ PLOGFONTW Font, _Inout_opt_ LPCOLORREF Color);

/// <summary>
/// Takes snapshot for current screen and provides a new created window
/// </summary>
/// <param name="ScreenSnapshot">Pointer to a DLG_SCREENSNAPSHOT structure, input window parameters and receive screen size and snapshot DC</param>
/// <remarks>Useful to implement screen capturer or picker, and supports multiple-monitor</remarks>
/// <returns>TRUE if the window created and ended successfully, or FALSE if failed</returns>
NTA_API BOOL NTAPI Dlg_ScreenSnapshot(_In_ PDLG_SCREENSNAPSHOT ScreenSnapshot);

/// <summary>
/// Callback registered by <c>Dlg_SetResizingSubclass</c>
/// </summary>
/// <param name="Dialog">Handle to the dialog box</param>
/// <param name="NewWidth">New width of client area</param>
/// <param name="NewHeight">New height of client area</param>
/// <param name="WindowPos">Not NULL when window changed by window-management functions</param>
typedef VOID(CALLBACK* DLG_RESIZEDPROC)(HWND Dialog, LONG NewWidth, LONG NewHeight, PWINDOWPOS WindowPos);

/// <summary>
/// Subclasses a dialog box to help support of resizing
/// </summary>
/// <param name="Dialog">Handle to the dialog box</param>
/// <param name="MinLimit">Use current size as minimum size of window, set to FALSE will no limitation</param>
/// <param name="ResizedProc">Callback procedure will be invoked when the size of dialog box changed</param>
/// <returns>TRUE if succeeded, or FALSE if failed, no error code reports due to SetWindowSubclass does</returns>
NTA_API BOOL NTAPI Dlg_SetResizingSubclass(HWND Dialog, BOOL MinLimit, DLG_RESIZEDPROC ResizedProc);

NTA_API BOOL NTAPI Dlg_SetTreeViewPropertySheetSubclass(HWND Dialog, HWND TreeView, PRECT SheetRect, _In_ PDLG_TREEVIEWPROPSHEETPAGE Sheets, UINT Count);

/// <seealso cref="UI_MessageLoop"/>
/// <remarks>Support dialogue messages and accelerators</remarks>
NTA_API _Success_(return != FALSE) BOOL NTAPI Dlg_MessageLoop(_In_opt_ HWND Window, _In_ HWND Dialog, _In_opt_ HACCEL Accelerator, _Out_opt_ PUINT_PTR ExitCode);

/// <summary>
/// Creates a dialog box that enables the user to edit a RECT structure
/// </summary>
/// <param name="Owner">Handle to the owner window</param>
/// <param name="Strings">String table to display text on the dialog, default strings is ["Title", "Reset", "OK", "Left", "Top", "Right", "Bottom", "Width", "Height"]</param>
/// <param name="Rect">Pointer to the RECT structure to set initial values and receive the result values</param>
/// <returns>TRUE if a RECT was confirmed, or FALSE if user canceled or an error occured</returns>
NTA_API BOOL NTAPI Dlg_RectEditor(HWND Owner, _In_opt_ PCWSTR * Strings, _Inout_ PRECT Rect);

#define DVE_TYPE_COMBINATION    0x1
#define DVE_TYPE_ENUMERATION    0x2

#define DVE_VALUE_HEXDWORD      0x100
#define DVE_VALUE_HEXQWORD      0x200

typedef struct _DLG_VALUEEDITOR_CONST {
    QWORD   Value;
    PCWSTR  Name;
    PCWSTR  Info;
} DLG_VALUEEDITOR_CONST, *PDLG_VALUEEDITOR_CONST;

/// <summary>
/// Creates a dialog box that enables the user to edit a value as combination or enumeration
/// </summary>
/// <param name="Owner">Handle to the owner window</param>
/// <param name="Flags">Can be combined with one of DVE_TYPE_XXX and one of DVE_VALUE_XXX</param>
/// <param name="Strings">String table to display text on the dialog, default strings is ["Title", "Reset", "OK", "Member", "Value", "Info", "Unknow"]</param>
/// <param name="Value">Pointer to the value to set initial value and receive the result value</param>
/// <param name="Consts">Pointer to a DLG_VALUEEDITOR_CONST structures array, contains constant members of value</param>
/// <param name="ConstCount">Number of constants in Consts parameter</param>
/// <returns>TRUE if a value was confirmed, or FALSE if user canceled or an error occured</returns>
NTA_API BOOL NTAPI Dlg_ValueEditorEx(HWND Owner, _In_ DWORD Flags, _In_opt_ PCWSTR * Strings, _Inout_ PQWORD Value, _In_ PDLG_VALUEEDITOR_CONST Consts, _In_ UINT ConstCount);

#define Dlg_ValueEditor(Owner, Flags, Strings, Value, Consts) Dlg_ValueEditorEx(Owner, Flags, Strings, Value, Consts, ARRAYSIZE(Consts))
