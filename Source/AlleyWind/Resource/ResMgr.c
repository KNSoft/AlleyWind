#include "../AlleyWind.inl"

#pragma region I18N

static KNS_I18N_TABLE g_I18NTable = { PS_RUNONCE_INIT, &Precomp4C_I18N_Table_All };

PCWSTR
AW_GetStringEx(
    _In_ ULONG_PTR Index)
{
    return KNS_I18NGetString(&g_I18NTable, Index);
}

VOID
AW_InitI18NArrayEx(
    _In_ PVOID Array,
    _In_ ULONG Size,
    _In_ ULONG Count,
    _In_ ULONG FieldOffset)
{
    KNS_I18NInitArray(&g_I18NTable, Array, Size, Count, FieldOffset);
}

#pragma endregion

/* Stock Objects */

PCWSTR g_ResNAText = NULL;
PCWSTR g_ResNAFormatStringText = NULL;
PCWSTR g_ResNAFormatCodeText = NULL;

HICON g_ResWindowIcon = NULL;
HBITMAP g_ResUACShieldIconBitmap = NULL;

/* Main Dialog */

static ACCEL g_MainDlgAccelItems[] = {
    { FVIRTKEY, VK_F5, IDM_MAINDLG_FILE_REFRESH },
    { FVIRTKEY | FCONTROL, 'S', IDM_MAINDLG_FILE_SAVETREE},
};

HACCEL g_ResMainDlgAccel = NULL;

// enum Menu_MainDlg_File_*
UI_MENU_ITEM g_MainDlgFileMenuItems[Menu_MainDlg_File_Max] = {
    { FALSE, MF_STRING, IDM_MAINDLG_FILE_RUNAS_ADMIN, NULL, Precomp4C_I18N_All_RunAsAdmin, NULL, 0 , NULL },
    { FALSE, MF_SEPARATOR, 0, NULL, -1, NULL, 0 , NULL },
    { FALSE, MF_STRING, IDM_MAINDLG_FILE_ALWAYS_ON_TOP, NULL, Precomp4C_I18N_All_AlwaysOnTop, NULL, 0 , NULL },
    { FALSE, MF_SEPARATOR, 0, NULL, -1, NULL, 0 , NULL },
    { FALSE, MF_STRING, IDM_MAINDLG_FILE_REFRESH, NULL, Precomp4C_I18N_All_Refresh_F5, NULL, 0 , NULL },
    { FALSE, MF_STRING, IDM_MAINDLG_FILE_SAVETREE, NULL, Precomp4C_I18N_All_SaveTree_Ctrl_S, NULL, 0 , NULL },
};

static UI_MENU_ITEM g_MainDlgHelpMenuItems[] = {
    { FALSE, MF_STRING, IDM_MAINDLG_HELP_HOMEPAGE, NULL, Precomp4C_I18N_All_Homepage, NULL, 0, NULL },
};

// enum Menu_MainDlg_*
UI_MENU_ITEM g_astMainDlgMenu[] = {
    { FALSE, MF_STRING, 0, NULL, Precomp4C_I18N_All_File, NULL, ARRAYSIZE(g_MainDlgFileMenuItems), g_MainDlgFileMenuItems },
    { FALSE, MF_STRING, 0, NULL, Precomp4C_I18N_All_Help, NULL, ARRAYSIZE(g_MainDlgHelpMenuItems), g_MainDlgHelpMenuItems },
};

/* enum Menu_MainDlg_Item_*/
UI_MENU_ITEM g_astMainDlgItemMenu[] = {
    { FALSE, MF_STRING, IDM_MAINDLG_ITEM_HIGHLIGHT, NULL, Precomp4C_I18N_All_Highlight, NULL, 0, NULL },
    { FALSE, MF_STRING | MF_DEFAULT, IDM_MAINDLG_ITEM_PROPERTIES, NULL, Precomp4C_I18N_All_Properties, NULL, 0, NULL },
};

HMENU g_ResMainDlgMenu = NULL;
HMENU g_ResMainDlgItemMenu = NULL;

LPCDLGTEMPLATEW g_ResMainDlgTemplate = NULL;

/* Properties Dialog */

LPCDLGTEMPLATEW g_ResPropDlgTemplate = NULL;

INT_PTR
CALLBACK
GeneralPspProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT_PTR
CALLBACK
ResourcePspProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT_PTR
CALLBACK
RelationPspProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

static
INT_PTR
CALLBACK
EmptyPspProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

AW_I18N_PROPSHEET_PAGE g_ResPropDlgPages[] = {
    { Precomp4C_I18N_All_General, MAKEINTRESOURCEW(IDD_PROP_GENERAL), GeneralPspProc },
    { Precomp4C_I18N_All_Resource, MAKEINTRESOURCEW(IDD_PROP_RESOURCE), ResourcePspProc },
    { Precomp4C_I18N_All_Relationship, MAKEINTRESOURCEW(IDD_PROP_RELATION), RelationPspProc },
    { Precomp4C_I18N_All_Class, MAKEINTRESOURCEW(IDD_PROP_RESOURCE), EmptyPspProc },
    { (INT_PTR)L"DPI", MAKEINTRESOURCEW(IDD_PROP_RESOURCE), EmptyPspProc },
    { Precomp4C_I18N_All_Operation, MAKEINTRESOURCEW(IDD_PROP_RESOURCE), EmptyPspProc },
};

W32ERROR
AW_InitResource(VOID)
{
    HRESULT hr;
    SHSTOCKICONINFO sii;

    /* Stock Objects */

    g_ResNAText = AW_GetString(NA);
    g_ResNAFormatStringText = AW_GetString(NAFormatString);
    g_ResNAFormatCodeText = AW_GetString(NAFormatCode);

    g_ResWindowIcon = LoadImageW(NULL, MAKEINTRESOURCEW(OIC_WINLOGO), IMAGE_ICON, 0, 0, LR_SHARED);

    sii.cbSize = sizeof(sii);
    hr = SHGetStockIconInfo(SIID_SHIELD, SHGSI_ICON | SHGSI_SMALLICON, &sii);
    if (SUCCEEDED(hr))
    {
        g_ResUACShieldIconBitmap = UI_CreateBitmapFromIcon(sii.hIcon, 0, 0);
        if (g_ResUACShieldIconBitmap == NULL)
        {
            DestroyIcon(sii.hIcon);
        }
    }

    g_ResMainDlgAccel = CreateAcceleratorTableW(g_MainDlgAccelItems, ARRAYSIZE(g_MainDlgAccelItems));

    AW_InitMenuI18N(g_MainDlgFileMenuItems);
    AW_InitMenuI18N(g_MainDlgHelpMenuItems);
    AW_InitMenuI18N(g_astMainDlgMenu);
    AW_InitMenuI18N(g_astMainDlgItemMenu);

    /* Add runas sub-menu if privilege is limited */
    if (!g_IsRunAsAdmin)
    {
        g_MainDlgFileMenuItems[Menu_MainDlg_File_RunAsAdmin].Icon = g_ResUACShieldIconBitmap;
    } else
    {
        g_MainDlgFileMenuItems[Menu_MainDlg_File_RunAsAdmin].Invalid = g_MainDlgFileMenuItems[Menu_MainDlg_File_Separator0].Invalid = TRUE;
    }

    g_ResMainDlgMenu = CreateMenu();
    if (g_ResMainDlgMenu != NULL)
    {
        if (UI_CreateMenuItems(g_ResMainDlgMenu, g_astMainDlgMenu) != ERROR_SUCCESS)
        {
            DestroyMenu(g_ResMainDlgMenu);
            g_ResMainDlgMenu = NULL;
        }
    }

    g_ResMainDlgItemMenu = CreatePopupMenu();
    if (g_ResMainDlgItemMenu != NULL)
    {
        if (UI_CreateMenuItems(g_ResMainDlgItemMenu, g_astMainDlgItemMenu) != ERROR_SUCCESS)
        {
            DestroyMenu(g_ResMainDlgItemMenu);
            g_ResMainDlgItemMenu = NULL;
        }
    }

    g_ResMainDlgTemplate = AW_LoadDialogTemplate(MAKEINTRESOURCEW(IDD_MAIN));
    g_ResPropDlgTemplate = AW_LoadDialogTemplate(MAKEINTRESOURCEW(IDD_PROP));

    AW_InitPropSheetPageI18N(g_ResPropDlgPages);

    return ERROR_SUCCESS;
}

VOID
AW_UninitResource(VOID)
{
    if (g_ResUACShieldIconBitmap != NULL)
    {
        DeleteObject(g_ResUACShieldIconBitmap);
    }
    if (g_ResMainDlgAccel != NULL)
    {
        DestroyAcceleratorTable(g_ResMainDlgAccel);
    }
    if (g_ResMainDlgMenu != NULL)
    {
        DestroyMenu(g_ResMainDlgMenu);
        UI_DestroyMenuItems(g_astMainDlgMenu);
    }
    if (g_ResMainDlgItemMenu != NULL)
    {
        DestroyMenu(g_ResMainDlgItemMenu);
        UI_DestroyMenuItems(g_astMainDlgItemMenu);
    }
}
