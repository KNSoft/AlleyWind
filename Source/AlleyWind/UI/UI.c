#include "../AlleyWind.inl"

static
ULONG
AppendTitleText(
    _Out_writes_(TextCch) PWSTR Text,
    _In_ ULONG TextCch,
    _In_ PCWSTR TextAppend)
{
    ULONG u, Cch = 0;

    if (TextCch <= 2)
    {
        goto _Exit;
    }
    Text[Cch++] = L' ';
    Text[Cch++] = L'(';

    u = Str_CopyExW(Text + Cch, TextCch - Cch, TextAppend);
    if (u == 0 || u >= TextCch - Cch)
    {
        goto _Exit;
    }
    Cch += u;
    if (Cch + 2 > TextCch)
    {
        goto _Exit;
    }
    Text[Cch++] = L')';
    // FIXME: Seems like a false positive, `Cch` won't greater than `TextCch`
#pragma warning(disable: __WARNING_WRITE_OVERRUN)
    Text[Cch] = UNICODE_NULL;
#pragma warning(default: __WARNING_WRITE_OVERRUN)
    return Cch;

_Exit:
    Text[0] = UNICODE_NULL;
    return 0;
}

ULONG
AW_PostfixTitleText(
    _Out_writes_(TextCch) PWSTR Text,
    _In_ ULONG TextCch)
{
    ULONG Cch = 0;

    if (g_IsRunAsAdmin)
    {
        Cch += AppendTitleText(Text, TextCch, AW_GetString(Administrator));
    }
    if (g_HasUIAccess)
    {
        Cch += AppendTitleText(Text + Cch, TextCch - Cch, L"UIAccess");
    }

    Text[Cch] = UNICODE_NULL;
    return Cch;
}

_Success_(return > 0)
ULONG
AW_WriteAddressDisplayString(
    _In_ PAW_WINDOW_PROP Prop,
    _In_ ULONGLONG Address,
    _In_ NTSTATUS Status,
    _In_ PWSTR DisplayString,
    _Out_writes_(BufferCch) _Always_(_Post_z_) PWSTR Buffer,
    _In_ ULONG BufferCch)
{
    ULONG Cch, CchLast, u;

    if (NT_SUCCESS(Status))
    {
        return Str_CopyExW(Buffer, BufferCch, DisplayString);
    }

    /* Write address at first */
    Cch = AW_WritePropAddress(Prop, Address, Buffer, BufferCch);
    if (Cch == 0 || Cch + 2 > BufferCch)
    {
        return Str_CopyExW(Buffer, BufferCch, g_ResNAText);
    }
    CchLast = Cch;
    Buffer[Cch++] = L' ';

    /* Write error information */
    if (Status == STATUS_INVALID_IMAGE_WIN_64)
    {
        u = Str_CopyExW(Buffer + Cch, BufferCch - Cch, AW_GetString(NARequire64Bit));
    } else
    {
        goto _Truncate;
    }
    return Cch + u;

_Truncate:
    Buffer[CchLast] = UNICODE_NULL;
    return CchLast;
}

HRESULT
AW_EditStyleValue(
    _In_ HWND Owner,
    _In_ PAW_WINDOW_PROP Prop,
    _In_ AW_STYLE_VALUE_TYPE StyleType)
{
    HRESULT hr;
    PUI_VALUEEDITOR_CONSTANT Consts;
    ULONG ConstsCount;
    DWORD Value;
    W32ERROR Ret;

    if (StyleType == AW_StyleType_Style)
    {
        Value = Prop->Info.dwStyle;
    } else if (StyleType == AW_StyleType_ExStyle)
    {
        Value = Prop->Info.dwExStyle;
    } else if (StyleType == AW_StyleType_ClassStyle)
    {
        return E_NOTIMPL;
    } else
    {
        return E_INVALIDARG;
    }
    hr = AW_GetStyleValueConstants(Prop->SysClassInfo,
                                   StyleType,
                                   Prop->Info.dwStyle & WS_CHILD,
                                   &Consts,
                                   &ConstsCount);
    if (FAILED(hr))
    {
        return hr;
    }
    hr = UI_ValueEditorDlg(Owner, UIValueEditorCombine, &Value, sizeof(Value), Consts, ConstsCount);
    AW_ReleaseStyleValueConstants(StyleType, Consts);
    if (hr != S_OK)
    {
        return hr;
    }

    if (StyleType == AW_StyleType_Style)
    {
        Ret = UI_SetWindowLong(Prop->Handle, GWL_STYLE, Value);
    } else if (StyleType == AW_StyleType_ExStyle)
    {
        Ret = UI_SetWindowLong(Prop->Handle, GWL_EXSTYLE, Value);
    } else if (StyleType == AW_StyleType_ClassStyle)
    {
        return E_NOTIMPL;
    }
    if (Ret != ERROR_SUCCESS)
    {
        return HRESULT_FROM_WIN32(Ret);
    }
    SetWindowPos(Prop->Handle,
                 NULL,
                 0,
                 0,
                 0,
                 0,
                 SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
    UI_Redraw(Prop->Handle);
    return S_OK;
}
