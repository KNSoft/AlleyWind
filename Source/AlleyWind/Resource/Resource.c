#include "../AlleyWind.inl"

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
