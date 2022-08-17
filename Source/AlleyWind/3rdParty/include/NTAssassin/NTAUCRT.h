// UCRT functions exported in ntdll.dll

#pragma once

#include "NTADef.h"

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

NTA_API _Success_(return >= 0) _Check_return_opt_ int __CRTDECL UCRT__vsnprintf(
    _Out_writes_opt_(_BufferCount) _Post_maybez_ char*       const _Buffer,
    _In_                                        size_t      const _BufferCount,
    _In_z_ _Printf_format_string_               char const* const _Format,
    va_list           _ArgList
);

NTA_API _Post_equal_to_(_Dst)
_At_buffer_(
    (unsigned char*)_Dst,
    _Iter_,
    _Size,
    _Post_satisfies_(((unsigned char*)_Dst)[_Iter_] == _Val)
) void* __cdecl UCRT_memset(
    _Out_writes_bytes_all_(_Size) void*  _Dst,
    _In_                          int    _Val,
    _In_                          size_t _Size
);

NTA_API _Success_(return == 0)
_Check_return_opt_
errno_t __CRTDECL UCRT_memcpy_s(
    _Out_writes_bytes_to_opt_(_DestinationSize, _SourceSize) void*       const _Destination,
    _In_                                                     rsize_t     const _DestinationSize,
    _In_reads_bytes_opt_(_SourceSize)                        void const* const _Source,
    _In_                                                     rsize_t     const _SourceSize
);
