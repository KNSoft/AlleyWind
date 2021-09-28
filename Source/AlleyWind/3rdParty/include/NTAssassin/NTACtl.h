#pragma once

#include "NTAssassin.h"
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
    HMENU       Handle;
};

typedef struct _CTL_PROPSHEETPAGE CTL_PROPSHEETPAGE, * PCTL_PROPSHEETPAGE;
struct _CTL_PROPSHEETPAGE {
    union {
        UINT_PTR    I18NIndex;
        PCWSTR      Title;
    };
    HINSTANCE   Instance;
    UINT        DlgResID;
    DLGPROC     DlgProc;
    HWND        Handle;
};

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
} CTL_COMBOBOXCTL_ITEM, * PCTL_COMBOBOXCTL_ITEM;

typedef BOOL(CALLBACK* CTL_TREEVIEWITEMENUMPROC)(HWND TreeView, HTREEITEM TreeItem, UINT Level, LPARAM Param);

/**
  * @brief Creates window menu
  * @param[in, out] Menus Pointer to an UI_MENU structures array, contains information about submenus to be created
  * @param[in] Count Number of UI_MENU structures in Menus parameter
  * @param[in] Parent Handle to parent menu, or NULL if create a top-level menu
  * @return Returns handle to the new menu
  */
NTA_API HMENU NTAPI Ctl_CreateMenuEx(CTL_MENU Menus[], UINT Count, HMENU Parent);
#define Ctl_CreateMenu(Menus, Parent) Ctl_CreateMenuEx(Menus, ARRAYSIZE(Menus), Parent)

/**
  * @brief Creates a menu and append to specified window
  * @see "Ctl_CreateMenuEx" and "SetMenu"
  */
#define Ctl_SetMenuEx(Window, Menus, Count) SetMenu(Window, Ctl_CreateMenuEx(Menus, Count, NULL));
#define Ctl_SetMenu(Window, Menus) SetMenu(Window, Ctl_CreateMenuEx(Menus, ARRAYSIZE(Menus), NULL));

/**
  * @brief Popups the menu
  * @see "TrackPopupMenu"
  */
#define Ctl_PopupMenu(hMenu, x, y, hOwner) TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON, x, y, 0, hOwner, NULL)

/**
  * @brief Destroies the menu created by "Ctl_CreateMenuEx"
  */
NTA_API VOID NTAPI Ctl_DestroyMenuEx(PCTL_MENU Menus, UINT Count, HMENU Menu);
#define Ctl_DestroyMenu(Menus, Menu) Ctl_DestroyMenuEx(Menus, ARRAYSIZE(Menus), Menu)

/**
  * @brief Initializes tab control with property sheet feature powered
  * @param[in] Dialog Handle to the dialog contains the tab control
  * @param[in] TabCtlID Control ID of tab control
  * @param[in, out] Sheets Pointer to an CTL_PROPSHEETPAGE structures array, contains information about property sheet of tabs
  * @param[in] SheetCount Number of CTL_PROPSHEETPAGE structures in Sheets parameter
  * @param[in] Param User defined parameter, will be passed to each DlgProc in UI_PROPSHEETPAGE structure by WM_INITDIALOG message
  */
NTA_API VOID NTAPI Ctl_SetPropertySheetEx(HWND Dialog, INT TabCtlID, CTL_PROPSHEETPAGE Sheets[], UINT SheetCount, LPARAM Param);
#define Ctl_SetPropertySheet(Dialog, TabCtlID, Sheets, Param) Ctl_SetPropertySheetEx(Dialog, TabCtlID, Sheets, ARRAYSIZE(Sheets), Param)

/**
  * @brief Initializes List-View control by specified columes
  * @param[in] List Handle to the List-View control
  * @param[in] Cols Pointer to an CTL_LISTCTL_COLUME structures array, contains information about columes
  * @param[in] ColCount Number of CTL_LISTCTL_COLUME structures specified in Cols parameter
  * @param[in] ExStyle Extended styles set to the List-View control
  */
NTA_API VOID NTAPI Ctl_InitListCtlEx(HWND List, CTL_LISTCTL_COLUME Cols[], UINT ColCount, LONG_PTR ExStyle);
#define Ctl_InitListCtl(List, Cols, ExStyle) Ctl_InitListCtlEx(List, Cols, ARRAYSIZE(Cols), ExStyle)

/**
  * @brief Initializes ComboBox control by specified items
  * @param[in] ComboBox Handle to the ComboBox control
  * @param[in] Items Pointer to a CTL_COMBOBOXCTL_ITEM structures array, contains information about items
  * @param[in] ItemCount Number of CTL_COMBOBOXCTL_ITEM structures specified in Items parameter
  * @param[in] SetParam Set to TRUE to makes Param member in CTL_COMBOBOXCTL_ITEM will be applied to the item
  */
NTA_API VOID NTAPI Ctl_InitComboBoxEx(HWND ComboBox, PCTL_COMBOBOXCTL_ITEM Items, UINT ItemCount, BOOL SetParam);
#define Ctl_InitComboBox(ComboBox, Items, SetParam) Ctl_InitComboBoxEx(ComboBox, Items, ARRAYSIZE(Items), SetParam)

/**
  * @brief Enumerates item in given tree-view control
  * @param[in] TreeView Handle to the tree-view  control
  * @param[in] BFS Use Breadth-First-Search algorithm instead of DFS (Depth-First-Search), BFS is not supported yet, must be FALSE
  * @param[in] TreeItemEnumProc Callback procedure to receive information of each item
  * @param[in] Param User defined value passed to the callback
  * @return Returns handle to the last enumerated item if the callback stops the enumeration, or NULL if enumeration finished successfully
  */
HTREEITEM NTAPI Ctl_EnumTreeViewItems(HWND TreeView, BOOL BFS, CTL_TREEVIEWITEMENUMPROC TreeItemEnumProc, LPARAM Param);

/**
  * @see "CB_SETCURSEL"
  * @note This function will notify parent window by sending "WM_COMMAND"
  */
LRESULT NTAPI Ctl_ComboBoxSetSelect(HWND ComboBox, INT ItemIndex);