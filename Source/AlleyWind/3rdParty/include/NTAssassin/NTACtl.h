#pragma once

#include "NTADef.h"
#include "NTACtl_ColorPicker.h"

typedef struct _CTL_MENU CTL_MENU, * PCTL_MENU;
struct _CTL_MENU {
    UINT        Flags;
    UINT_PTR    ID;
    union {
        UINT_PTR    I18NIndex;
        LPARAM      Param;  // MF_OWNERDRAW
        HBITMAP     Bitmap; // MF_BITMAP
        PCWSTR      Text;   // MF_STRING
    };
    PCTL_MENU   SubMenu;
    UINT        SubMenuCount;
    HMENU       Handle;     // Initializes with NULL
};

typedef struct _CTL_PROPSHEETPAGE {
    union {
        UINT_PTR    I18NIndex;
        PCWSTR      Title;
    };
    HINSTANCE   Instance;
    UINT        DlgResID;
    DLGPROC     DlgProc;
    HWND        Handle;
} CTL_PROPSHEETPAGE, *PCTL_PROPSHEETPAGE;

typedef struct _CTL_LISTCTL_COLUME {
    union {
        UINT_PTR    I18NIndex;
        PCWSTR      Title;
    };
    INT     Width;
} CTL_LISTCTL_COLUME, * PCTL_LISTCTL_COLUME;

typedef struct _CTL_COMBOBOXCTL_ITEM {
    union {
        UINT_PTR    I18NIndex;
        PCWSTR      String;
    };
    LPARAM          Param;
} CTL_COMBOBOXCTL_ITEM, *PCTL_COMBOBOXCTL_ITEM;

typedef BOOL(CALLBACK* CTL_TREEVIEWITEMENUMPROC)(HWND TreeView, HTREEITEM TreeItem, UINT Level, LPARAM Param);

/// <summary>
/// Creates menu
/// </summary>
/// <param name="Menus">Pointer to an UI_MENU structures array, contains information and receive handle about submenus to be created</param>
/// <param name="Count">Number of UI_MENU structures in Menus parameter</param>
/// <param name="Parent">Handle to parent menu, or NULL if create a top-level menu</param>
/// <returns>Handle to the new menu, or NULL if failed, error code storaged in last ERROR</returns>
NTA_API HMENU NTAPI Ctl_CreateMenuEx(_Inout_ PCTL_MENU Menus, _In_ UINT Count, _In_opt_ HMENU Parent);
#define Ctl_CreateMenu(Menus, Parent) Ctl_CreateMenuEx(Menus, ARRAYSIZE(Menus), Parent)

/// <summary>
/// Creates a menu and append to specified window
/// </summary>
/// <seealso cref="Ctl_CreateMenuEx"/>
/// <seealso cref="SetMenu"/>
#define Ctl_SetMenuEx(Window, Menus, Count) SetMenu(Window, Ctl_CreateMenuEx(Menus, Count, NULL))
#define Ctl_SetMenu(Window, Menus) SetMenu(Window, Ctl_CreateMenuEx(Menus, ARRAYSIZE(Menus), NULL))

/// <summary>
/// Popups the menu
/// </summary>
/// <seealso cref="TrackPopupMenu"/>
#define Ctl_PopupMenu(hMenu, x, y, hOwner) TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON, x, y, 0, hOwner, NULL)

/// <summary>
/// Destroies the menu created by "Ctl_CreateMenuEx"
/// </summary>
/// <seealso cref="Ctl_CreateMenuEx"/>
NTA_API VOID NTAPI Ctl_DestroyMenuEx(_In_ PCTL_MENU Menus, _In_ UINT Count, HMENU Menu);
#define Ctl_DestroyMenu(Menus, Menu) Ctl_DestroyMenuEx(Menus, ARRAYSIZE(Menus), Menu)

/// <summary>
/// Initializes tab control with property sheet feature powered
/// </summary>
/// <param name="Dialog">Handle to the dialog contains the tab control</param>
/// <param name="TabCtlID">Control ID of tab control</param>
/// <param name="Sheets">Pointer to a CTL_PROPSHEETPAGE structures array, contains information and receive handle about property sheet of tabs</param>
/// <param name="SheetCount">Number of CTL_PROPSHEETPAGE structures in Sheets parameter</param>
/// <param name="Param">User defined parameter, will be passed to each DlgProc in UI_PROPSHEETPAGE structure via WM_INITDIALOG message</param>
/// <returns>TRUE if succeeded, or FALSE if failed, no error code reports due to SetWindowSubclass does</returns>
NTA_API BOOL NTAPI Ctl_SetPropertySheetEx(HWND Dialog, INT TabCtlID, _In_ PCTL_PROPSHEETPAGE Sheets, _In_ UINT SheetCount, LPARAM Param);
#define Ctl_SetPropertySheet(Dialog, TabCtlID, Sheets, Param) Ctl_SetPropertySheetEx(Dialog, TabCtlID, Sheets, ARRAYSIZE(Sheets), Param)


/// <summary>
/// Initializes List-View control with specified columes
/// </summary>
/// <param name="List">Handle to the List-View control</param>
/// <param name="Cols">Cols Pointer to a CTL_LISTCTL_COLUME structures array, contains information about columes</param>
/// <param name="ColCount">Number of CTL_LISTCTL_COLUME structures specified in Cols parameter</param>
/// <param name="ExStyle">Extended styles set to the List-View control</param>
/// <returns>TRUE if succeeded, or FALSE if failed, no error code reports</returns>
NTA_API BOOL NTAPI Ctl_InitListCtlEx(HWND List, _In_ PCTL_LISTCTL_COLUME Cols, _In_ UINT ColCount, LONG_PTR ExStyle);
#define Ctl_InitListCtl(List, Cols, ExStyle) Ctl_InitListCtlEx(List, Cols, ARRAYSIZE(Cols), ExStyle)

/// <summary>
/// Initializes ComboBox control with specified items
/// </summary>
/// <param name="ComboBox">Handle to the ComboBox control</param>
/// <param name="Items">Pointer to a CTL_COMBOBOXCTL_ITEM structures array, contains information about items</param>
/// <param name="ItemCount">Number of CTL_COMBOBOXCTL_ITEM structures specified in Items parameter</param>
/// <param name="SetParam">Set to TRUE to makes Param member in CTL_COMBOBOXCTL_ITEM will be applied to the item</param>
/// <returns>TRUE if succeeded, or FALSE if failed, no error code reports</returns>
NTA_API BOOL NTAPI Ctl_InitComboBoxEx(HWND ComboBox, _In_ PCTL_COMBOBOXCTL_ITEM Items, _In_ UINT ItemCount, BOOL SetParam);
#define Ctl_InitComboBox(ComboBox, Items, SetParam) Ctl_InitComboBoxEx(ComboBox, Items, ARRAYSIZE(Items), SetParam)

/// <summary>
/// Enumerates item in given Tree-View control
/// </summary>
/// <param name="TreeView">Handle to the tree-view  control</param>
/// <param name="BFS">Use BFS (Breadth-First-Search) algorithm instead of DFS (Depth-First-Search), BFS is not supported yet, so this parameter must be FALSE</param>
/// <param name="TreeItemEnumProc">Callback procedure to receive information of each item</param>
/// <param name="Param">User defined value passed to the callback</param>
/// <returns>Returns handle to the last enumerated item if the callback stops the enumeration, or NULL if enumeration finished successfully</returns>
NTA_API HTREEITEM NTAPI Ctl_EnumTreeViewItems(HWND TreeView, BOOL BFS, _In_ CTL_TREEVIEWITEMENUMPROC TreeItemEnumProc, LPARAM Param);

/// <summary>
/// Sends CB_SETCURSEL message but will notify parent window by sending "WM_COMMAND" with CBN_SELCHANGE
/// </summary>
/// <seealso cref="CB_SETCURSEL"/>
NTA_API LRESULT NTAPI Ctl_ComboBoxSetSelect(HWND ComboBox, INT ItemIndex);
