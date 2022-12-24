// UCRT functions exported in ntdll.dll

#pragma once

#include "NTADef.h"

NTA_API _Check_return_ size_t __cdecl NT_wcslen(_In_z_ wchar_t const* _String);
NTA_API _Check_return_ size_t __cdecl NT_strlen(_In_z_ char const* _Str);

NTA_API _Check_return_ _Ret_maybenull_
_When_(return != NULL, _Ret_range_(_Str, _Str + _String_length_(_Str) - 1))
wchar_t _CONST_RETURN* __cdecl NT_wcsstr(
    _In_z_ wchar_t const* _Str,
    _In_z_ wchar_t const* _SubStr);
NTA_API _Check_return_ _Ret_maybenull_
_When_(return != NULL, _Ret_range_(_Str, _Str + _String_length_(_Str) - 1))
char _CONST_RETURN* __cdecl NT_strstr(
    _In_z_ char const* _Str,
    _In_z_ char const* _SubStr);

NTA_API _Check_return_ int __cdecl NT_wcscmp(_In_z_ wchar_t const* _String1, _In_z_ wchar_t const* _String2);
NTA_API _Check_return_ int __cdecl NT_strcmp(_In_z_ char const* _Str1, _In_z_ char const* _Str2);

NTA_API _Success_(return >= 0) _Check_return_ int __CRTDECL NT_vswprintf_s(
    _Out_writes_(_BufferCount) _Always_(_Post_z_) wchar_t* const _Buffer,
    _In_                                          size_t         const _BufferCount,
    _In_z_ _Printf_format_string_                 wchar_t const* const _Format,
    va_list              _ArgList
);
NTA_API _Success_(return >= 0) _Check_return_ int __CRTDECL NT_vsprintf_s(
    _Out_writes_(_BufferCount) _Always_(_Post_z_) char*       const _Buffer,
    _In_                                          size_t      const _BufferCount,
    _In_z_ _Printf_format_string_                 char const* const _Format,
    va_list           _ArgList
);

NTA_API _Post_equal_to_(_Dst)
_At_buffer_(
    (unsigned char*)_Dst,
    _Iter_,
    _Size,
    _Post_satisfies_(((unsigned char*)_Dst)[_Iter_] == _Val)
) void* __cdecl NT_memset(
    _Out_writes_bytes_all_(_Size) void*  _Dst,
    _In_                          int    _Val,
    _In_                          size_t _Size
);

NTA_API _Success_(return == 0)
_Check_return_opt_
errno_t __CRTDECL NT_memcpy_s(
    _Out_writes_bytes_to_opt_(_DestinationSize, _SourceSize) void*       const _Destination,
    _In_                                                     rsize_t     const _DestinationSize,
    _In_reads_bytes_opt_(_SourceSize)                        void const* const _Source,
    _In_                                                     rsize_t     const _SourceSize
);
