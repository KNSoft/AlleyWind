﻿#pragma once

#include "../AlleyWind.Core.inl"

EXTERN_C_START

ULONG
AW_PostFixTitleText(
    _Out_writes_(TextCch) PWSTR Text,
    _In_ ULONG TextCch);

HRESULT
AW_OpenMainDialogBox(VOID);

HRESULT
AW_OpenPropDialogBoxSync(
    _In_ HWND RefWindow);

NTSTATUS
AW_OpenPropDialogBoxAsync(
    _In_ HWND RefWindow);

EXTERN_C_END
