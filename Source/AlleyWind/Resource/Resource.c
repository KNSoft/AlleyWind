#include "../AlleyWind.inl"

#pragma region I18N

static KNS_I18N_TABLE g_I18NTable = { PS_RUNONCE_INIT, &Precomp4C_I18N_Table_All };

PCWSTR
AW_GetStringEx(
    _In_ INT Index)
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

HICON g_ResUACShieldIcon = NULL;
HBITMAP g_ResUACShieldIconBitmap = NULL;
PCWSTR g_NAText = NULL;
PCWSTR g_NAFormatText = NULL;

VOID
AW_InitStockResource(VOID)
{
    HRESULT hr;
    SHSTOCKICONINFO sii;

    g_NAText = AW_GetString(NA);
    g_NAFormatText = AW_GetString(NAFormat);

    /* UAC shield icon */
    sii.cbSize = sizeof(sii);
    hr = SHGetStockIconInfo(SIID_SHIELD, SHGSI_ICON | SHGSI_SMALLICON, &sii);
    if (SUCCEEDED(hr))
    {
        g_ResUACShieldIcon = sii.hIcon;
        g_ResUACShieldIconBitmap = UI_CreateBitmapFromIcon(g_ResUACShieldIcon, 0, 0);
        if (g_ResUACShieldIconBitmap == NULL)
        {
            DestroyIcon(g_ResUACShieldIcon);
            g_ResUACShieldIcon = NULL;
        }
    }
}

VOID
AW_UninitStockResource(VOID)
{
    if (g_ResUACShieldIconBitmap != NULL)
    {
        DeleteObject(g_ResUACShieldIconBitmap);
    }
    if (g_ResUACShieldIcon != NULL)
    {
        DestroyIcon(g_ResUACShieldIcon);
    }
}
