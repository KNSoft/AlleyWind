#pragma once

#include "../AlleyWind.Core.inl"

EXTERN_C_START

ULONG
AW_PostfixTitleText(
    _Out_writes_(TextCch) PWSTR Text,
    _In_ ULONG TextCch);

_Success_(return > 0)
ULONG
AW_WriteAddressDisplayString(
    _In_ PAW_WINDOW_PROP Prop,
    _In_ ULONGLONG Address,
    _In_ NTSTATUS Status,
    _In_ PWSTR DisplayString,
    _Out_writes_(BufferCch) _Always_(_Post_z_) PWSTR Buffer,
    _In_ ULONG BufferCch);

HRESULT
AW_OpenMainDialogBox(VOID);

HRESULT
AW_OpenPropDialogBoxSync(
    _In_ HWND Window);

NTSTATUS
AW_OpenPropDialogBoxAsync(
    _In_ HWND Window);

HRESULT
AW_EditStyleValue(
    _In_ HWND Owner,
    _In_ PAW_WINDOW_PROP Prop,
    _In_ AW_STYLE_VALUE_TYPE StyleType);

EXTERN_C_END
