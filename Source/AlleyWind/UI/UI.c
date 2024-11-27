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

    u = (ULONG)Str_CopyExW(Text + Cch, TextCch - Cch, TextAppend);
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
AW_PostFixTitleText(
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
