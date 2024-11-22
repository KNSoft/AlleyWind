#include "Menu.h"

static UI_MENU_ITEM g_astMenuFile[] = {
    { FALSE, MF_STRING, IDM_FILE_RUNAS_ADMIN, NULL, Precomp4C_I18N_All_RunAsAdmin, NULL, 0 , NULL },
    { FALSE, MF_SEPARATOR, 0, NULL, -1, NULL, 0 , NULL },
    { FALSE, MF_STRING, IDM_FILE_REFRESH, NULL, Precomp4C_I18N_All_Refresh_F5, NULL, 0 , NULL },
    { FALSE, MF_STRING, IDM_FILE_SAVETREE, NULL, Precomp4C_I18N_All_SaveTree_Ctrl_S, NULL, 0 , NULL },
};

static UI_MENU_ITEM g_astMenuHelp[] = {
    { FALSE, MF_STRING, IDM_HELP_HOMEPAGE, NULL, Precomp4C_I18N_All_Homepage, NULL, 0, NULL },
};

static UI_MENU_ITEM g_astMainMenu[] = {
    { FALSE, MF_STRING, 0, NULL, Precomp4C_I18N_All_File, NULL, ARRAYSIZE(g_astMenuFile), g_astMenuFile },
    { FALSE, MF_STRING, 0, NULL, Precomp4C_I18N_All_Help, NULL, ARRAYSIZE(g_astMenuHelp), g_astMenuHelp },
};

static UI_MENU_ITEM g_astItemMenu[] = {
    { FALSE, MF_STRING, IDM_ITEM_HIGHLIGHT, NULL, Precomp4C_I18N_All_Highlight, NULL, 0, NULL },
    { FALSE, MF_STRING | MF_DEFAULT, IDM_ITEM_PROPERTIES, NULL, Precomp4C_I18N_All_Properties, NULL, 0, NULL },
};

static ACCEL g_astDlgAccel[] = {
    { FVIRTKEY, VK_F5, IDM_FILE_REFRESH },
    { FVIRTKEY | FCONTROL, 'S', IDM_FILE_SAVETREE},
};

VOID
MainDlgCreateMenu(
    _Outptr_result_maybenull_ HMENU* MainMenu,
    _Outptr_result_maybenull_ HMENU* ItemMenu)
{
    HANDLE Token;
    HMENU Menu;

    /* Add runas sub-menu if privilege is limited */
    if (!NT_SUCCESS(PS_OpenCurrentThreadToken(&Token)))
    {
        goto _CreateMenu;
    }
    if (!NT_SUCCESS(PS_IsAdminToken(Token)))
    {
        g_astMenuFile[0].Icon = g_ResUACShieldIconBitmap;
    } else
    {
        g_astMenuFile[0].Invalid = g_astMenuFile[1].Invalid = TRUE;
    }
    NtClose(Token);

_CreateMenu:
    AW_InitMenuI18N(g_astMenuFile);
    AW_InitMenuI18N(g_astMenuHelp);
    AW_InitMenuI18N(g_astMainMenu);
    AW_InitMenuI18N(g_astItemMenu);

    Menu = CreateMenu();
    if (Menu != NULL)
    {
        if (UI_CreateMenuItems(Menu, g_astMainMenu) != ERROR_SUCCESS)
        {
            DestroyMenu(Menu);
            Menu = NULL;
        }
    }
    *MainMenu = Menu;

    Menu = CreatePopupMenu();
    if (Menu != NULL)
    {
        if (UI_CreateMenuItems(Menu, g_astItemMenu) != ERROR_SUCCESS)
        {
            DestroyMenu(Menu);
            Menu = NULL;
        }
    }
    *ItemMenu = Menu;
}

VOID
MainDlgDestroyMenu(
    _In_opt_ HMENU MainMenu,
    _In_opt_ HMENU ItemMenu)
{
    if (MainMenu != NULL)
    {
        DestroyMenu(MainMenu);
        UI_DestroyMenuItems(g_astMainMenu);
    }
    if (ItemMenu != NULL)
    {
        DestroyMenu(ItemMenu);
        UI_DestroyMenuItems(g_astItemMenu);
    }
}

HACCEL
MainDlgCreateAccelerator(VOID)
{
    return CreateAcceleratorTableW(g_astDlgAccel, ARRAYSIZE(g_astDlgAccel));
}
