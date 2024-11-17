#pragma once

#define OEMRESOURCE
#define STRICT_TYPED_ITEMIDS
#define _USE_COMMCTL60
#include <KNSoft/NDK/NDK.h>

#include "KNSoft.AppInfo.h"
#include "Resource/Resource.h"
#include "Resource/I18N.xml.g.h"

#define MLE_API
#include <MakeLifeEasier.h>

#pragma comment (lib, "Comctl32.lib")

#define MAX_WNDCAPTION_CCH 128

EXTERN_C_START

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
AW_InitMenuEx(
    _In_reads_(Count) PUI_MENU_ITEM Items,
    _In_ UINT Count)
{
    AW_InitI18NArrayEx(Items, sizeof(*Items), Count, UFIELD_OFFSET(TYPE_OF(*Items), Text));
}

#define AW_InitMenu(Items) AW_InitMenuEx(Items, ARRAYSIZE(Items))

VOID
AW_InitClassDatabase(VOID);

FORCEINLINE
HRESULT
AW_OpenDialog(
    _In_opt_ HWND Owner,
    _In_ LPCWSTR DlgResName,
    _In_opt_ HACCEL Accelerator,
    _In_opt_ DLGPROC DlgProc,
    _In_opt_ LPARAM InitParam)
{
    NTSTATUS Status;
    PVOID DlgRes;

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

    return KNS_DlgBox((HINSTANCE)&__ImageBase, Owner, DlgRes, Accelerator, DlgProc, InitParam);
}

// TODO: Read configuration
FORCEINLINE
LRESULT
AW_SendMsgTO(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, PDWORD_PTR lpdwResult)
{
    return SendMessageTimeoutW(hWnd, uMsg, wParam, lParam, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 200, lpdwResult);
}

FORCEINLINE
HICON
AW_GetWindowIcon(
    _In_ HWND Window)
{
    HICON hIcon = NULL;
    if (AW_SendMsgTO(Window, WM_GETICON, ICON_SMALL, 0, (PDWORD_PTR)&hIcon) == 0 || hIcon == NULL)
    {
        hIcon = (HICON)GetClassLongPtrW(Window, GCLP_HICON);
    }
    return hIcon;
}

_Ret_maybenull_
PCWSTR
AW_GetSysClassDisplayName(
    _In_ PCWSTR ClassName);

HRESULT
AW_OpenMainDialogBox(VOID);

EXTERN_C_END
