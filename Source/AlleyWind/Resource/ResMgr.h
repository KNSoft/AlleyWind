#pragma once

#include "../AlleyWind.Core.inl"

EXTERN_C_START

/* I18N */

PCWSTR
AW_GetStringEx(
    _In_ INT Index);

#define AW_GetString(x) AW_GetStringEx(Precomp4C_I18N_All_##x)

VOID
AW_InitI18NArrayEx(
    _In_ PVOID Array,
    _In_ ULONG Size,
    _In_ ULONG Count,
    _In_ ULONG FieldOffset);

FORCEINLINE
VOID
AW_InitMenuI18NEx(
    _In_reads_(Count) PUI_MENU_ITEM Items,
    _In_ UINT Count)
{
    AW_InitI18NArrayEx(Items, sizeof(*Items), Count, UFIELD_OFFSET(TYPE_OF(*Items), Text));
}

#define AW_InitMenuI18N(Items) AW_InitMenuI18NEx(Items, ARRAYSIZE(Items))

/* Stock resources */

extern HICON g_ResUACShieldIcon;
extern HBITMAP g_ResUACShieldIconBitmap;

VOID
AW_InitStockResource(VOID);

VOID
AW_UninitStockResource(VOID);

EXTERN_C_END
