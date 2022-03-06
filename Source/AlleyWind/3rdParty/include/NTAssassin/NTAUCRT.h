#pragma once

#include "NTAssassin.h"

NTA_API _Check_return_ size_t __cdecl UCRT_wcslen(_In_z_ wchar_t const* _String);
NTA_API _Check_return_ size_t __cdecl UCRT_strlen(_In_z_ char const* _Str);

NTA_API _Check_return_ int __cdecl UCRT_wcscmp(_In_z_ wchar_t const* _String1, _In_z_ wchar_t const* _String2);
NTA_API _Check_return_ int __cdecl UCRT_strcmp(_In_z_ char const* _Str1, _In_z_ char const* _Str2);

NTA_API _Success_(return >= 0) int __CRTDECL UCRT_vswprintf_s(
    _Out_writes_(_BufferCount) _Always_(_Post_z_) wchar_t* const _Buffer,
    _In_                                          size_t         const _BufferCount,
    _In_z_ _Printf_format_string_                 wchar_t const* const _Format,
    va_list              _ArgList
);
NTA_API _Success_(return >= 0) int __CRTDECL UCRT_vsprintf_s(
    _Out_writes_(_BufferCount) _Always_(_Post_z_) char* const _Buffer,
    _In_                                          size_t      const _BufferCount,
    _In_z_ _Printf_format_string_                 char const* const _Format,
    va_list           _ArgList
);