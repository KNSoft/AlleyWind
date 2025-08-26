#pragma once

#include "../AlleyWind.Core.inl"

EXTERN_C_START

typedef struct _AW_I18N_DLGITEM
{
    INT ItemId;
    ULONG_PTR I18NIndex;
} AW_I18N_DLGITEM, *PAW_I18N_DLGITEM;

typedef struct _AW_I18N_PROPSHEET_PAGE
{
    union
    {
        ULONG_PTR I18NIndex;
        PCWSTR Title;
    };
    union
    {
        PCWSTR DlgResName;
        LPCDLGTEMPLATEW DlgTemplate;
    };
    DLGPROC DlgProc;
} AW_I18N_PROPSHEET_PAGE, *PAW_I18N_PROPSHEET_PAGE;

PCWSTR
AW_GetStringEx(
    _In_ ULONG_PTR Index);

#define AW_GetString(x) AW_GetStringEx(Precomp4C_I18N_All_##x)

VOID
AW_InitI18NArray(
    _In_ PVOID Array,
    _In_ ULONG Size,
    _In_ ULONG Count,
    _In_ ULONG FieldOffset);

FORCEINLINE
VOID
AW_InitMenuI18N(
    _In_reads_(Count) PUI_MENU_ITEM Items,
    _In_ UINT Count)
{
    AW_InitI18NArray(Items, sizeof(*Items), Count, UFIELD_OFFSET(typeof(*Items), Text));
}

FORCEINLINE
VOID
AW_InitStringI18N(
    _In_reads_(Count) PULONG_PTR Indexes,
    _In_ UINT Count)
{
    AW_InitI18NArray(Indexes, sizeof(*Indexes), Count, 0);
}

FORCEINLINE
LPCDLGTEMPLATEW
AW_LoadDialogTemplate(
    _In_ PCWSTR DlgResName)
{
    LPCDLGTEMPLATEW p;

    return NT_SUCCESS(PE_AccessResource((HINSTANCE)&__ImageBase,
                                        MAKEINTRESOURCEW(RT_DIALOG),
                                        DlgResName,
                                        LANG_USER_DEFAULT,
                                        &p,
                                        NULL)) ? p : NULL;
}

FORCEINLINE
W32ERROR
AW_CreateDialog(
    _Out_opt_ HWND* Dialog,
    _In_opt_ HWND Owner,
    _In_ LPCDLGTEMPLATEW DlgTemplate,
    _In_opt_ DLGPROC DlgProc,
    _In_opt_ LPARAM InitParam)
{
    HWND Window;

    Window = CreateDialogIndirectParamW((HINSTANCE)&__ImageBase, DlgTemplate, Owner, DlgProc, InitParam);
    if (Window == NULL)
    {
        return Err_GetLastError();
    }
    if (Dialog != NULL)
    {
        *Dialog = Window;
    }
    return S_OK;
}

FORCEINLINE
VOID
AW_InitDlgItemI18N(
    _In_ HWND Dialog,
    _In_reads_(Count) AW_I18N_DLGITEM Items[],
    _In_ UINT Count)
{
    UINT i;

    for (i = 0; i < Count; i++)
    {
        UI_SetDlgItemTextW(Dialog, Items[i].ItemId, AW_GetStringEx(Items[i].I18NIndex));
    }
}

FORCEINLINE
VOID
AW_InitPropSheetPageI18N(
    _In_reads_(Count) AW_I18N_PROPSHEET_PAGE Pages[],
    _In_ UINT Count)
{
    UINT i;

    for (i = 0; i < Count; i++)
    {
        Pages[i].Title = AW_GetStringEx(Pages[i].I18NIndex);
        Pages[i].DlgTemplate = AW_LoadDialogTemplate(MAKEINTRESOURCEW(Pages[i].DlgResName));
    }
}

FORCEINLINE
VOID
AW_CreatePropSheetPages(
    _In_ HWND Dialog,
    _In_reads_(Count) AW_I18N_PROPSHEET_PAGE InPages[],
    _Out_writes_(Count) UI_PROPSHEET_PAGE OutPages[],
    _In_ UINT Count,
    _In_opt_ LPARAM InitParam)
{
    UINT i;

    for (i = 0; i < Count; i++)
    {
        if (FAILED(AW_CreateDialog(&OutPages[i].PageWindow,
                                   Dialog,
                                   InPages[i].DlgTemplate,
                                   InPages[i].DlgProc,
                                   InitParam)))
        {
            OutPages[i].PageWindow = NULL;
        }
        OutPages[i].TabTitle = InPages[i].Title;
    }
}

EXTERN_C_END
