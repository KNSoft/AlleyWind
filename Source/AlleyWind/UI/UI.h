#pragma once

#include "../AlleyWind.Core.inl"

EXTERN_C_START

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

HRESULT
AW_OpenMainDialogBox(VOID);

EXTERN_C_END
