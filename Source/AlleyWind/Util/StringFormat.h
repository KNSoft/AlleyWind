#pragma once

#include "../AlleyWind.Core.inl"

EXTERN_C_START

FORCEINLINE
_Success_(return > 0)
ULONG
AW_WriteNAInfoString(
    _Out_writes_(BufferCch) _Always_(_Post_z_) PWSTR Buffer,
    _In_ ULONG BufferCch,
    _In_ PCWSTR Info)
{
    ULONG u;

    u = Str_PrintfExW(Buffer, BufferCch, g_ResNAFormatStringText, Info);
    if (u == 0)
    {
        u = Str_CopyExW(Buffer, BufferCch, g_ResNAText);
    }
    return u;
}

FORCEINLINE
_Success_(return > 0)
ULONG
AW_WriteNACodeString(
    _Out_writes_(BufferCch) _Always_(_Post_z_) PWSTR Buffer,
    _In_ ULONG BufferCch,
    _In_ ULONG Code)
{
    ULONG u;

    u = Str_PrintfExW(Buffer, BufferCch, g_ResNAFormatCodeText, Code);
    if (u == 0)
    {
        u = Str_CopyExW(Buffer, BufferCch, g_ResNAText);
    }
    return u;
}

FORCEINLINE
_Success_(return > 0)
ULONG
AW_WriteNAStringFromWin32Error(
    _Out_writes_(BufferCch) _Always_(_Post_z_) PWSTR Buffer,
    _In_ ULONG BufferCch,
    _In_ ULONG Win32Error)
{
    PCWSTR psz = Err_GetWin32ErrorInfo(Win32Error);
    return psz != NULL ? AW_WriteNAInfoString(Buffer, BufferCch, psz) : AW_WriteNACodeString(Buffer, BufferCch, Win32Error);
}

FORCEINLINE
_Success_(return > 0)
ULONG
AW_WriteNAStringFromHr(
    _Out_writes_(BufferCch) _Always_(_Post_z_) PWSTR Buffer,
    _In_ ULONG BufferCch,
    _In_ HRESULT Hr)
{
    PCWSTR psz = Err_GetHrInfo(Hr);
    return psz != NULL ? AW_WriteNAInfoString(Buffer, BufferCch, psz) : AW_WriteNACodeString(Buffer, BufferCch, Hr);
}

FORCEINLINE
_Success_(return > 0)
ULONG
AW_WriteNAStringFromNtStatus(
    _Out_writes_(BufferCch) _Always_(_Post_z_) PWSTR Buffer,
    _In_ ULONG BufferCch,
    _In_ NTSTATUS Status)
{
    PCWSTR psz = Err_GetNtStatusInfo(Status);
    return psz != NULL ? AW_WriteNAInfoString(Buffer, BufferCch, psz) : AW_WriteNACodeString(Buffer, BufferCch, Status);
}

FORCEINLINE
_Success_(return > 0)
ULONG
AW_WriteRectString(
    _Out_writes_(BufferCch) _Always_(_Post_z_) PWSTR Buffer,
    _In_ ULONG BufferCch,
    _In_ PRECT Rect)
{
    return Str_PrintfExW(Buffer,
                         BufferCch,
                         AW_GetString(RectangleFormat),
                         Rect->left,
                         Rect->top,
                         Rect->right,
                         Rect->bottom,
                         Rect->right - Rect->left,
                         Rect->bottom - Rect->top);
}

EXTERN_C_END
