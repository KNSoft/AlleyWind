#include "../AlleyWind.inl"

#pragma region I18N

KNS_I18N_TABLE g_I18NTable = { PS_RUNONCE_INIT, &Precomp4C_I18N_Table_KNSAW };

VOID
AW_InitI18NArray(
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
    { FVIRTKEY | FCONTROL, 'S', IDM_MAINDLG_FILE_SAVETREE },
    { FVIRTKEY | FCONTROL, 'F', IDM_MAINDLG_TOOL_FINDWINDOW },
};

HACCEL g_ResMainDlgAccel = NULL;

// enum Menu_MainDlg_File_*
UI_MENU_ITEM g_MainDlgFileMenuItems[Menu_MainDlg_File_Max] = {
    { FALSE, MF_STRING, IDM_MAINDLG_FILE_RUNAS_ADMIN, NULL, Precomp4C_I18N_KNSAW_RunAsAdmin, NULL, 0 , NULL },
    { FALSE, MF_SEPARATOR, 0, NULL, -1, NULL, 0 , NULL },
    { FALSE, MF_STRING, IDM_MAINDLG_FILE_ALWAYS_ON_TOP, NULL, Precomp4C_I18N_KNSAW_AlwaysOnTop, NULL, 0 , NULL },
    { FALSE, MF_SEPARATOR, 0, NULL, -1, NULL, 0 , NULL },
    { FALSE, MF_STRING, IDM_MAINDLG_FILE_REFRESH, NULL, Precomp4C_I18N_KNSAW_Refresh_F5, NULL, 0 , NULL },
    { FALSE, MF_STRING, IDM_MAINDLG_FILE_SAVETREE, NULL, Precomp4C_I18N_KNSAW_SaveTree_Ctrl_S, NULL, 0 , NULL },
};

static UI_MENU_ITEM g_MainDlgToolMenuItems[] = {
    { FALSE, MF_STRING, IDM_MAINDLG_TOOL_FINDWINDOW, NULL, Precomp4C_I18N_KNSAW_FindWindow, NULL, 0, NULL },
    { FALSE, MF_STRING, IDM_MAINDLG_TOOL_SYSINPUTMON, NULL, Precomp4C_I18N_KNSAW_SysInputMon, NULL, 0, NULL },
};

static UI_MENU_ITEM g_MainDlgHelpMenuItems[] = {
    { FALSE, MF_STRING, IDM_MAINDLG_HELP_HOMEPAGE, NULL, Precomp4C_I18N_KNSAW_Homepage, NULL, 0, NULL },
};

// enum Menu_MainDlg_*
UI_MENU_ITEM g_MainDlgMenuItems[] = {
    { FALSE, MF_STRING, 0, NULL, Precomp4C_I18N_KNSAW_File, NULL, ARRAYSIZE(g_MainDlgFileMenuItems), g_MainDlgFileMenuItems },
    { FALSE, MF_STRING, 0, NULL, Precomp4C_I18N_KNSAW_Tool, NULL, ARRAYSIZE(g_MainDlgToolMenuItems), g_MainDlgToolMenuItems },
    { FALSE, MF_STRING, 0, NULL, Precomp4C_I18N_KNSAW_Help, NULL, ARRAYSIZE(g_MainDlgHelpMenuItems), g_MainDlgHelpMenuItems },
};

/* enum Menu_MainDlg_Item_*/
UI_MENU_ITEM aMainDlgItemMenuItems[] = {
    { FALSE, MF_STRING, IDM_MAINDLG_ITEM_HIGHLIGHT, NULL, Precomp4C_I18N_KNSAW_Highlight, NULL, 0, NULL },
    { FALSE, MF_STRING | MF_DEFAULT, IDM_MAINDLG_ITEM_PROPERTIES, NULL, Precomp4C_I18N_KNSAW_Properties, NULL, 0, NULL },
};

HMENU g_ResMainDlgMenu = NULL;
HMENU g_ResMainDlgItemMenu = NULL;

LPCDLGTEMPLATEW g_ResMainDlgTemplate = NULL;

/* Message monitor Dialog */

LPCDLGTEMPLATEW g_ResMsgMonDlgTemplate = NULL;

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

/* Properties - Relation Dialog */

AW_I18N_PROPSHEET_PAGE g_ResPropDlgPages[] = {
    { Precomp4C_I18N_KNSAW_General, MAKEINTRESOURCEW(IDD_PROP_GENERAL), GeneralPspProc },
    { Precomp4C_I18N_KNSAW_Resource, MAKEINTRESOURCEW(IDD_PROP_RESOURCE), ResourcePspProc },
    { Precomp4C_I18N_KNSAW_Relationship, MAKEINTRESOURCEW(IDD_PROP_RELATION), RelationPspProc },
    { Precomp4C_I18N_KNSAW_Class, MAKEINTRESOURCEW(IDD_PROP_RESOURCE), EmptyPspProc },
    { (INT_PTR)L"DPI", MAKEINTRESOURCEW(IDD_PROP_RESOURCE), EmptyPspProc },
    { Precomp4C_I18N_KNSAW_Operation, MAKEINTRESOURCEW(IDD_PROP_RESOURCE), EmptyPspProc },
};

static UI_MENU_ITEM aPropProcessMenuItems[] = {
    { FALSE, MF_STRING, IDM_RESPROPDLG_PROCESS_LOCATE, NULL, Precomp4C_I18N_KNSAW_OpenFileLocation, NULL, 0, NULL },
    { FALSE, MF_STRING, IDM_RESPROPDLG_PROCESS_PROPERTIES, NULL, Precomp4C_I18N_KNSAW_FileProperties, NULL, 0, NULL },
    { FALSE, MF_STRING, IDM_RESPROPDLG_PROCESS_TERMINATE, NULL, Precomp4C_I18N_KNSAW_Terminate, NULL, 0, NULL },
};

HMENU g_ResPropRelDlgProcessMenu = NULL;

static UI_MENU_ITEM aPropRelWindowMenuItems[] = {
    { FALSE, MF_STRING, IDM_RESPROPDLG_RELWINDOW_PROPERTIES, NULL, Precomp4C_I18N_KNSAW_Properties, NULL, 0, NULL },
    { FALSE, MF_STRING, IDM_RESPROPDLG_RELWINDOW_LOCATEINLIST, NULL, Precomp4C_I18N_KNSAW_LocateInList, NULL, 0, NULL },
    { FALSE, MF_STRING, IDM_RESPROPDLG_RELWINDOW_HIGHLIGHT, NULL, Precomp4C_I18N_KNSAW_Highlight, NULL, 0, NULL }
};

HMENU g_ResPropRelDlgRelWindowMenu = NULL;

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
        DestroyIcon(sii.hIcon);
    }

    g_ResMainDlgAccel = CreateAcceleratorTableW(g_MainDlgAccelItems, ARRAYSIZE(g_MainDlgAccelItems));

    AW_InitMenuI18N(g_MainDlgFileMenuItems, ARRAYSIZE(g_MainDlgFileMenuItems));
    AW_InitMenuI18N(g_MainDlgToolMenuItems, ARRAYSIZE(g_MainDlgToolMenuItems));
    AW_InitMenuI18N(g_MainDlgHelpMenuItems, ARRAYSIZE(g_MainDlgHelpMenuItems));
    AW_InitMenuI18N(g_MainDlgMenuItems, ARRAYSIZE(g_MainDlgMenuItems));
    AW_InitMenuI18N(aMainDlgItemMenuItems, ARRAYSIZE(aMainDlgItemMenuItems));
    AW_InitMenuI18N(aPropProcessMenuItems, ARRAYSIZE(aPropProcessMenuItems));
    AW_InitMenuI18N(aPropRelWindowMenuItems, ARRAYSIZE(aPropRelWindowMenuItems));

    /* Add runas sub-menu if privilege is limited */
    if (!g_IsRunAsAdmin)
    {
        g_MainDlgFileMenuItems[Menu_MainDlg_File_RunAsAdmin].Icon = g_ResUACShieldIconBitmap;
    } else
    {
        g_MainDlgFileMenuItems[Menu_MainDlg_File_RunAsAdmin].Invalid = g_MainDlgFileMenuItems[Menu_MainDlg_File_Separator0].Invalid = TRUE;
    }


    UI_CreateMenu(&g_ResMainDlgMenu, FALSE, g_MainDlgMenuItems);
    UI_CreateMenu(&g_ResMainDlgItemMenu, TRUE, aMainDlgItemMenuItems);
    UI_CreateMenu(&g_ResPropRelDlgProcessMenu, TRUE, aPropProcessMenuItems);
    UI_CreateMenu(&g_ResPropRelDlgRelWindowMenu, TRUE, aPropRelWindowMenuItems);

    g_ResMainDlgTemplate = AW_LoadDialogTemplate(MAKEINTRESOURCEW(IDD_MAIN));
    g_ResPropDlgTemplate = AW_LoadDialogTemplate(MAKEINTRESOURCEW(IDD_PROP));
    g_ResMsgMonDlgTemplate = AW_LoadDialogTemplate(MAKEINTRESOURCEW(IDD_MSGMON));

    AW_InitPropSheetPageI18N(g_ResPropDlgPages, ARRAYSIZE(g_ResPropDlgPages));

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
        UI_DestroyMenuItems(g_MainDlgMenuItems);
    }
    if (g_ResMainDlgItemMenu != NULL)
    {
        DestroyMenu(g_ResMainDlgItemMenu);
        UI_DestroyMenuItems(aMainDlgItemMenuItems);
    }
    if (g_ResPropRelDlgProcessMenu != NULL)
    {
        DestroyMenu(g_ResPropRelDlgProcessMenu);
        UI_DestroyMenuItems(aPropProcessMenuItems);
    }
    if (g_ResPropRelDlgRelWindowMenu != NULL)
    {
        DestroyMenu(g_ResPropRelDlgRelWindowMenu);
        UI_DestroyMenuItems(aPropRelWindowMenuItems);
    }
}
