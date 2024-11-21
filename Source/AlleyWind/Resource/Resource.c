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

HICON g_ResUACIcon = NULL;
HBITMAP g_ResUACIconBitmap = NULL;

VOID
AW_InitStockResource(VOID)
{
    HRESULT hr;
    SHSTOCKICONINFO sii;

    /* UAC shield icon */
    sii.cbSize = sizeof(sii);
    hr = SHGetStockIconInfo(SIID_SHIELD, SHGSI_ICON | SHGSI_SMALLICON, &sii);
    if (SUCCEEDED(hr))
    {
        g_ResUACIcon = sii.hIcon;
        g_ResUACIconBitmap = UI_CreateBitmapFromIcon(g_ResUACIcon, 0, 0);
        if (g_ResUACIconBitmap == NULL)
        {
            DestroyIcon(g_ResUACIcon);
            g_ResUACIcon = NULL;
        }
    }
}

VOID
AW_UninitStockResource(VOID)
{
    if (g_ResUACIconBitmap != NULL)
    {
        DeleteObject(g_ResUACIconBitmap);
    }
    if (g_ResUACIcon != NULL)
    {
        DestroyIcon(g_ResUACIcon);
    }
}
