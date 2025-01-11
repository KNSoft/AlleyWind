#pragma once

#include "../AlleyWind.Core.inl"

#include "Util.h"

EXTERN_C_START

/* Stock Objects */

extern PCWSTR g_ResNAText;
extern PCWSTR g_ResNAFormatStringText;
extern PCWSTR g_ResNAFormatCodeText;

extern HICON g_ResWindowIcon;
extern HBITMAP g_ResUACShieldIconBitmap;

/* Main Dialog */

#define IDM_MAINDLG_FILE_RUNAS_ADMIN 1
#define IDM_MAINDLG_FILE_ALWAYS_ON_TOP 2
#define IDM_MAINDLG_FILE_REFRESH 3
#define IDM_MAINDLG_FILE_SAVETREE 4

#define IDM_MAINDLG_HELP_HOMEPAGE 20

#define IDM_MAINDLG_ITEM_HIGHLIGHT 101
#define IDM_MAINDLG_ITEM_PROPERTIES 102

enum
{
    Menu_MainDlg_Item_Highlight = 0,
    Menu_MainDlg_Item_Properties,
    Menu_MainDlg_Item_Max,
};

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
extern UI_MENU_ITEM g_MainDlgFileMenuItems[Menu_MainDlg_File_Max];

enum
{
    Menu_MainDlg_File = 0,
    Menu_MainDlg_Help,
    Menu_MainDlg_Max
};
extern UI_MENU_ITEM g_ResMainDlgMenuItems[Menu_MainDlg_Max];

extern HACCEL g_ResMainDlgAccel;
extern HMENU g_ResMainDlgMenu;
extern HMENU g_ResMainDlgItemMenu;
extern LPCDLGTEMPLATEW g_ResMainDlgTemplate;

/* Properties Dialog */

extern AW_I18N_PROPSHEET_PAGE g_ResPropDlgPages[6];
extern LPCDLGTEMPLATEW g_ResPropDlgTemplate;

enum
{
    Menu_PropRelDlg_Process_Locate = 0,
    Menu_PropRelDlg_Process_Properties,
    Menu_PropRelDlg_Process_Terminate,
};
extern HMENU g_ResPropRelDlgProcessMenu;

W32ERROR
AW_InitResource(VOID);

VOID
AW_UninitResource(VOID);

EXTERN_C_END
