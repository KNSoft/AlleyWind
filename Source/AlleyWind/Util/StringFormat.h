#pragma once

#include "../AlleyWind.Core.inl"

EXTERN_C_START

FORCEINLINE
PWSTR
AW_GetNAInfoString(
    PWSTR Buffer,
    _In_ ULONG BufferCch,
    _In_ PCWSTR Info)
{
    return Str_TestCchRet(Str_PrintfExW(Buffer, BufferCch, g_NAFormatStringText, Info), BufferCch) ? Buffer : (PWSTR)g_NAText;
}

FORCEINLINE
PWSTR
AW_GetNACodeString(
    PWSTR Buffer,
    _In_ ULONG BufferCch,
    _In_ ULONG Code)
{
    return Str_TestCchRet(Str_PrintfExW(Buffer, BufferCch, g_NAFormatCodeText, Code), BufferCch) ? Buffer : (PWSTR)g_NAText;
}

FORCEINLINE
PWSTR
AW_GetNAStringFromWin32Error(
    PWCHAR Text,
    _In_ ULONG TextCch,
    _In_ ULONG Win32Error)
{
    PCWSTR psz = Err_GetWin32ErrorInfo(Win32Error);
    return psz != NULL ? AW_GetNAInfoString(Text, TextCch, psz) : AW_GetNACodeString(Text, TextCch, Win32Error);
}

FORCEINLINE
PWSTR
AW_GetNAStringFromHr(
    PWCHAR Text,
    _In_ ULONG TextCch,
    _In_ HRESULT Hr)
{
    PCWSTR psz = Err_GetHrInfo(Hr);
    return psz != NULL ? AW_GetNAInfoString(Text, TextCch, psz) : AW_GetNACodeString(Text, TextCch, Hr);
}

FORCEINLINE
PWSTR
AW_GetNAStringFromNtStatus(
    PWCHAR Text,
    _In_ ULONG TextCch,
    _In_ NTSTATUS Status)
{
    PCWSTR psz = Err_GetNtStatusInfo(Status);
    return psz != NULL ? AW_GetNAInfoString(Text, TextCch, psz) : AW_GetNACodeString(Text, TextCch, Status);
}

EXTERN_C_END
