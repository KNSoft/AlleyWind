#pragma once

#include "../../AlleyWind.inl"

#define IDM_FILE_RUNAS_ADMIN 1
#define IDM_FILE_ALWAYS_ON_TOP 2
#define IDM_FILE_REFRESH 3
#define IDM_FILE_SAVETREE 4

#define IDM_HELP_HOMEPAGE 20

#define IDM_ITEM_HIGHLIGHT 101
#define IDM_ITEM_PROPERTIES 102

EXTERN_C_START

enum
{
    Menu_MainDlg_File_RunAsAdmin = 0,
    Menu_MainDlg_File_Separator0,
    Menu_MainDlg_File_AlwaysOnTop,
    Menu_MainDlg_File_Separator1,
    Menu_MainDlg_File_Refresh,
    Menu_MainDlg_File_SaveTree,
    Menu_MainDlg_File_Max
};

enum
{
    Menu_MainDlg_File = 0,
    Menu_MainDlg_Help,
    Menu_MainDlg_Max
};
extern UI_MENU_ITEM g_astMainMenu[Menu_MainDlg_Max];

enum
{
    Menu_MainDlg_Item_Highlight = 0,
    Menu_MainDlg_Item_Properties,
    Menu_MainDlg_Item_Max,
};

VOID
MainDlgCreateMenu(
    _Outptr_result_maybenull_ HMENU* MainMenu,
    _Outptr_result_maybenull_ HMENU* ItemMenu);

VOID
MainDlgDestroyMenu(
    _In_opt_ HMENU MainMenu,
    _In_opt_ HMENU ItemMenu);

HACCEL
MainDlgCreateAccelerator(VOID);

EXTERN_C_END
