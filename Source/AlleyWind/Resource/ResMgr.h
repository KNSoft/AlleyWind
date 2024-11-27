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

/* Dialog resource */

FORCEINLINE
HRESULT
AW_CreateDialog(
    _Out_opt_ HWND* Dialog,
    _In_opt_ HWND Owner,
    _In_ PCWSTR DlgResName,
    _In_opt_ DLGPROC DlgProc,
    _In_opt_ LPARAM InitParam)
{
    NTSTATUS Status;
    PVOID DlgRes;
    HWND Window;

    Status = PE_AccessResource((HINSTANCE)&__ImageBase,
                               MAKEINTRESOURCEW(RT_DIALOG),
                               DlgResName,
                               LANG_USER_DEFAULT,
                               &DlgRes,
                               NULL);
    if (!NT_SUCCESS(Status))
    {
        return HRESULT_FROM_NT(Status);
    }

    Window = CreateDialogIndirectParamW((HINSTANCE)&__ImageBase, DlgRes, Owner, DlgProc, InitParam);
    if (Window == NULL)
    {
        return HRESULT_FROM_WIN32(NtGetLastError());
    } else
    {
        if (Dialog != NULL)
        {
            *Dialog = Window;
        }
        return S_OK;
    }
}

typedef struct _AW_I18N_DLGITEM
{
    INT ItemId;
    INT I18NIndex;
} AW_I18N_DLGITEM, *PAW_I18N_DLGITEM;

typedef struct _AW_I18N_PROPSHEET_PAGE
{
    INT I18NIndex;
    PCWSTR DlgResName;
    DLGPROC DlgProc;
    LPARAM InitParam;
} AW_I18N_PROPSHEET_PAGE, *PAW_I18N_PROPSHEET_PAGE;

FORCEINLINE
VOID
AW_InitDlgItemI18NEx(
    _In_ HWND Dialog,
    _In_reads_(Count) AW_I18N_DLGITEM Items[],
    _In_ UINT Count)
{
    UINT i;
    HWND hCtl;

    for (i = 0; i < Count; i++)
    {
        hCtl = GetDlgItem(Dialog, Items[i].ItemId);
        SetWindowTextW(hCtl, AW_GetStringEx(Items[i].I18NIndex));
    }
}

#define AW_InitDlgItemI18N(Dialog, Items) AW_InitDlgItemI18NEx(Dialog, Items, ARRAYSIZE(Items))

FORCEINLINE
VOID
AW_InitPropSheetPageI18NEx(
    _In_ HWND Dialog,
    _In_reads_(Count) AW_I18N_PROPSHEET_PAGE InPages[],
    _Out_writes_(Count) UI_PROPSHEET_PAGE OutPages[],
    _In_ UINT Count)
{
    UINT i;

    for (i = 0; i < Count; i++)
    {
        if (FAILED(AW_CreateDialog(&OutPages[i].PageWindow,
                                   Dialog,
                                   InPages[i].DlgResName,
                                   InPages[i].DlgProc,
                                   InPages[i].InitParam)))
        {
            OutPages[i].PageWindow = NULL;
        }
        OutPages[i].TabTitle = AW_GetStringEx(InPages[i].I18NIndex);
    }
}

/* Stock resource */

extern HICON g_ResUACShieldIcon;
extern HBITMAP g_ResUACShieldIconBitmap;

VOID
AW_InitStockResource(VOID);

VOID
AW_UninitStockResource(VOID);

EXTERN_C_END
