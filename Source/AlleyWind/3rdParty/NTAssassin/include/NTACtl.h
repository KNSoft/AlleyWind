#pragma once

#include "NTAssassin.h"

typedef struct _CTL_MENUW CTL_MENUW, * PCTL_MENUW;

struct _CTL_MENUW {
    UINT        uFlags;
    UINT_PTR    uID;
    union {
        UINT_PTR    I18NIndex;
        LPARAM      lParam;     // MF_OWNERDRAW
        HBITMAP     hBmp;       // MF_BITMAP
        LPCWSTR     lpszText;   // MF_STRING
    };
    PCTL_MENUW  lpSubMenu;
    UINT        SubMenuCount;
    HMENU       Handle;
};

#ifdef UNICODE
#define CTL_MENU CTL_MENUW
#define PCTL_MENU PCTL_MENUW
#else
#define CTL_MENU CTL_MENUA
#define PCTL_MENU PCTL_MENUA
#endif

typedef struct _CTL_PROPSHEETPAGEW CTL_PROPSHEETPAGEW, * PCTL_PROPSHEETPAGEW;
struct _CTL_PROPSHEETPAGEW {
    union {
        UINT_PTR    I18NIndex;
        LPCWSTR     Title;
    };
    HINSTANCE   Instance;
    UINT        DlgResID;
    DLGPROC     DlgProc;
};

#ifdef UNICODE
#define CTL_PROPSHEETPAGE CTL_PROPSHEETPAGEW
#define PCTL_PROPSHEETPAGE PCTL_PROPSHEETPAGEW
#else
#define CTL_PROPSHEETPAGE CTL_PROPSHEETPAGEA
#define PCTL_PROPSHEETPAGE PCTL_PROPSHEETPAGEA
#endif

typedef struct _CTL_LISTCTL_COLUMEW {
    union {
        UINT_PTR    I18NIndex;
        LPCWSTR     Title;
    };
    INT     Width;
} CTL_LISTCTL_COLUMEW, * PCTL_LISTCTL_COLUMEW;

#ifdef UNICODE
#define CTL_LISTCTL_COLUME CTL_LISTCTL_COLUMEW
#define PCTL_LISTCTL_COLUME PCTL_LISTCTL_COLUMEW
#else
#define CTL_LISTCTL_COLUME CTL_LISTCTL_COLUMEA
#define PCTL_LISTCTL_COLUME PCTL_LISTCTL_COLUMEA
#endif

typedef struct _CTL_COMBOBOXCTL_ITEMW {
    union {
        UINT_PTR    I18NIndex;
        LPCWSTR     String;
    };
    LPARAM          Param;
} CTL_COMBOBOXCTL_ITEMW, * PCTL_COMBOBOXCTL_ITEMW;

#ifdef UNICODE
#define CTL_COMBOBOXCTL_ITEM CTL_COMBOBOXCTL_ITEMW
#define PCTL_COMBOBOXCTL_ITEM PCTL_COMBOBOXCTL_ITEMW
#else
#define CTL_COMBOBOXCTL_ITEM CTL_COMBOBOXCTL_ITEMA
#define PCTL_COMBOBOXCTL_ITEM PCTL_COMBOBOXCTL_ITEMA
#endif

/**
  * @brief Creates window menu
  * @param[in] stMenus Pointer to an UI_MENU structures array, contains information about submenus to be created
  * @param[in] uCount Number of UI_MENU structures in stMenus parameter point to
  * @param[in] hParent Handle to parent menu, or NULL if create a top-level menu
  * @return Returns handle to the new menu
  */
NTA_API HMENU NTAPI Ctl_CreateMenuExW(CTL_MENUW stMenus[], UINT uCount, HMENU hParent);
#define Ctl_CreateMenuW(stMenus, hParent) Ctl_CreateMenuExW(stMenus, ARRAYSIZE(stMenus), hParent)
#ifdef UNICODE
#define Ctl_CreateMenuEx Ctl_CreateMenuExW
#define Ctl_CreateMenu Ctl_CreateMenuW
#else
#define Ctl_CreateMenuEx Ctl_CreateMenuExA
#define Ctl_CreateMenu Ctl_CreateMenuA
#endif

/**
  * @brief Creates a menu and append to specified window
  * @see "Ctl_CreateMenuEx" and "SetMenu"
  */
#define Ctl_SetMenuExW(hWnd, stMenus, uCount) SetMenu(hWnd, Ctl_CreateMenuExW(stDlgMenu, uCount, NULL));
#define Ctl_SetMenuW(hWnd, stMenus) SetMenu(hWnd, Ctl_CreateMenuExW(stDlgMenu, ARRAYSIZE(stMenus), NULL));
#ifdef UNICODE
#define Ctl_SetMenuEx Ctl_SetMenuExW
#define Ctl_SetMenu Ctl_SetMenuW
#else
#define Ctl_SetMenuEx Ctl_SetMenuExA
#define Ctl_SetMenu Ctl_SetMenuA
#endif

/**
  * @brief Popups the menu
  * @see "TrackPopupMenu"
  */
#define Ctl_PopupMenu(hMenu, x, y, hOwner) TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON, x, y, 0, hOwner, NULL)

/**
  * @brief Destroies the menu created by "Ctl_CreateMenuEx"
  */
NTA_API VOID NTAPI Ctl_DestroyMenuEx(PCTL_MENUW lpstMenus, UINT uCount, HMENU hMenu);
#define Ctl_DestroyMenu(lpstMenus, hMenu) Ctl_DestroyMenuEx(lpstMenus, ARRAYSIZE(lpstMenus), hMenu)

/**
  * @brief Initializes tab control with property sheet feature powered
  * @param[in] hDlg Handle to the dialog contains the tab control
  * @param[in] uTabCtlID Control ID of tab control
  * @param[in] uSheetCount Number of UI_PROPSHEETPAGE structures in Sheets parameter point to
  * @param[in] Sheets Pointer to an UI_PROPSHEETPAGE structures array, contains information about property sheet of tabs
  * @param[in] lParam User defined parameter, will be passed to each DlgProc in UI_PROPSHEETPAGE structure by WM_INITDIALOG message
  */
NTA_API VOID NTAPI Ctl_SetPropertySheetW(HWND hDlg, UINT uTabCtlID, UINT uSheetCount, CTL_PROPSHEETPAGEW Sheets[], LPARAM lParam);
#ifdef UNICODE
#define Ctl_SetPropertySheet Ctl_SetPropertySheetW
#else
#define Ctl_SetPropertySheet Ctl_SetPropertySheetA
#endif

/**
  * @brief Initializes List-View control by specified columes
  * @param[in] hList Handle to the List-View control
  * @param[in] uCols Number of UI_LISTCTL_COLUME structures specified in Cols parameter
  * @param[in] Cols Pointer to an UI_LISTCTL_COLUME structures array, contains information about columes
  * @param[in] lExStyle Extended styles set to the List-View control
  */
NTA_API VOID NTAPI Ctl_InitListCtlExW(HWND hList, UINT uCols, CTL_LISTCTL_COLUMEW Cols[], LONG_PTR lExStyle);
#ifdef UNICODE
#define Ctl_InitListCtlEx Ctl_InitListCtlExW
#else
#define Ctl_InitListCtlEx Ctl_InitListCtlExA
#endif

#define Ctl_InitListCtlW(hList, Cols, lExStyle) Ctl_InitListCtlExW(hList, ARRAYSIZE(Cols), Cols, lExStyle)
#define Ctl_InitListCtlA(hList, Cols, lExStyle) Ctl_InitListCtlExA(hList, ARRAYSIZE(Cols), Cols, lExStyle)
#ifdef UNICODE
#define Ctl_InitListCtl Ctl_InitListCtlW
#else
#define Ctl_InitListCtl Ctl_InitListCtlA
#endif

NTA_API VOID NTAPI Ctl_InitComboBoxExW(HWND hComboBox, PCTL_COMBOBOXCTL_ITEMW lpstItems, UINT uItems, BOOL bSetParam);
#ifdef UNICODE
#define Ctl_InitComboBoxEx Ctl_InitComboBoxExW
#else
#define Ctl_InitComboBoxEx Ctl_InitComboBoxExA
#endif

#define Ctl_InitComboBoxW(hComboBox, lpstItems, bSetParam) Ctl_InitComboBoxExW(hComboBox, lpstItems, ARRAYSIZE(lpstItems), bSetParam)
#define Ctl_InitComboBoxA(hComboBox, lpstItems, bSetParam) Ctl_InitComboBoxExA(hComboBox, lpstItems, ARRAYSIZE(lpstItems), bSetParam)
#ifdef UNICODE
#define Ctl_InitComboBox Ctl_InitComboBoxW
#else
#define Ctl_InitComboBox Ctl_InitComboBoxA
#endif