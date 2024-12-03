#pragma once

#include "../AlleyWind.Core.inl"

EXTERN_C_START

ULONG
AW_PostFixTitleText(
    _Out_writes_(TextCch) PWSTR Text,
    _In_ ULONG TextCch);

FORCEINLINE
PCWSTR
AW_FormatNA(
    PWSTR Text,
    _In_ ULONG TextCch,
    _In_ PCWSTR Info)
{
    return Str_TestCchRet(Str_PrintfExW(Text, TextCch, g_NAFormatText, Info), TextCch) ? Text : g_NAText;
}

FORCEINLINE
PCWSTR
AW_FormatNAFromWin32Error(
    PWCHAR Text,
    _In_ ULONG TextCch,
    _In_ ULONG Win32Error)
{
    PCWSTR psz;

    psz = Err_GetWin32ErrorInfo(Win32Error);
    if (psz == NULL)
    {
        return g_NAText;
    }
    return AW_FormatNA(Text, TextCch, psz);
}

FORCEINLINE
PCWSTR
AW_FormatNAFromHr(
    PWCHAR Text,
    _In_ ULONG TextCch,
    _In_ HRESULT Hr)
{
    PCWSTR psz;

    psz = Err_GetHrInfo(Hr);
    if (psz == NULL)
    {
        return g_NAText;
    }
    return AW_FormatNA(Text, TextCch, psz);
}

FORCEINLINE
PCWSTR
AW_FormatNAFromNtStatus(
    PWCHAR Text,
    _In_ ULONG TextCch,
    _In_ NTSTATUS Status)
{
    PCWSTR psz;

    psz = Err_GetNtStatusInfo(Status);
    if (psz == NULL)
    {
        return g_NAText;
    }
    return AW_FormatNA(Text, TextCch, psz);
}

HRESULT
AW_OpenMainDialogBox(VOID);

HRESULT
AW_OpenPropDialogBoxSync(
    _In_ HWND RefWindow);

NTSTATUS
AW_OpenPropDialogBoxAsync(
    _In_ HWND RefWindow);

EXTERN_C_END
