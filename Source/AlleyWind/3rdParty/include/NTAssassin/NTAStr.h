/**
  * @brief Native library of NTAssassin provides basic string functions.
  * @note ***WILL BE DEPRECATED, assembly language and existing function in ntdll.dll instead***
  * @details Functions are named in pattern: Str_[Cch|Ccb][Len|Cat|Copy|...][IC][Ex]
  *
  * Counter:
  *  Cch: Counted string by number of characters;
  *  Ccb: Counted string by size in bytes;
  *  ***The terminating null character was included in buffer size, not included in string length***
  *
  * Operation:
  *  Len: Gets length of string;
  *  Cat: Catches strings;
  *  Copy: Copies strings;
  *  Equal: Compares strings are equal or not;
  *
  * Comparision:
  *  IC: Insensitive of case;
  */

#pragma once

#include "NTAssassin.h"

typedef enum _STR_HASH_ALGORITHM {
    StrHashAlgorithmSDBM,
    StrHashAlgorithmBKDR,
    StrHashAlgorithmAP,
    StrHashAlgorithmDJB,
    StrHashAlgorithmJS,
    StrHashAlgorithmRS,
    StrHashAlgorithmELF,
    StrHashAlgorithmPJW,
    StrHashAlgorithmX65599 = StrHashAlgorithmSDBM
} STR_HASH_ALGORITHM, * PSTR_HASH_ALGORITHM;

// String Length

NTA_API SIZE_T NTAPI Str_CchLenW(PCWSTR String);
NTA_API SIZE_T NTAPI Str_CchLenA(PCSTR String);
#ifdef UNICODE
#define Str_CchLen Str_CchLenW
#else
#define Str_CchLen Str_CchLenA
#endif

NTA_API SIZE_T NTAPI Str_CcbLenW(PCWSTR String);
#define Str_CcbLenA Str_CchLenA
#ifdef UNICODE
#define Str_CcbLen Str_CcbLenW
#else
#define Str_CcbLen Str_CcbLenA
#endif

// String Copy

NTA_API SIZE_T NTAPI Str_CchCopyExW(PWSTR Dest, SIZE_T DestCchSize, PCWSTR Src);
NTA_API SIZE_T NTAPI Str_CchCopyExA(PSTR Dest, SIZE_T DestCchSize, PCSTR Src);
#define Str_CchCopyW(Dest, Src) Str_CchCopyExW(Dest, ARRAYSIZE(Dest), Src)
#define Str_CchCopyA(Dest, Src) Str_CchCopyExA(Dest, ARRAYSIZE(Dest), Src)
#ifdef UNICODE
#define Str_CchCopyEx Str_CchCopyExW
#define Str_CchCopy Str_CchCopyW
#else
#define Str_CchCopyEx Str_CchCopyExA
#define Str_CchCopy Str_CchCopyA
#endif

NTA_API SIZE_T NTAPI Str_CcbCopyExW(PWSTR Dest, SIZE_T DestCcbSize, PCWSTR Src);
#define Str_CcbCopyExA Str_CchCopyExA
#define Str_CcbCopyW(Dest, Src) Str_CcbCopyExW(Dest, sizeof(Dest), Src)
#define Str_CcbCopyA(Dest, Src) Str_CcbCopyExA(Dest, sizeof(Dest), Src)
#ifdef UNICODE
#define Str_CcbCopy Str_CcbCopyW
#else
#define Str_CcbCopy Str_CcbCopyA
#endif

// String Equal

NTA_API BOOL NTAPI Str_EqualW(PCWSTR String1, PCWSTR String2);
NTA_API BOOL NTAPI Str_EqualA(PCSTR String1, PCSTR String2);
#ifdef UNICODE
#define Str_Equal Str_EqualW
#else
#define Str_Equal Str_EqualA
#endif

NTA_API BOOL NTAPI Str_EqualICW(PCWSTR String1, PCWSTR String2);
NTA_API BOOL NTAPI Str_EqualICA(PCSTR String1, PCSTR String2);
#ifdef UNICODE
#define Str_EqualIC Str_EqualICW
#else
#define Str_EqualIC Str_EqualICA
#endif

// String Index

NTA_API SIZE_T NTAPI Str_Index_BFW(PCWSTR String, PCWSTR Pattern);
NTA_API SIZE_T NTAPI Str_Index_BFA(PCSTR String, PCSTR Pattern);
#ifdef UNICODE
#define Str_Index_BF Str_Index_BFW
#else
#define Str_Index_BF Str_Index_BFA
#endif

// String Printf

#define Str_CchPrintfExW wnsprintfW
#define Str_CchPrintfExA wnsprintfA
#define Str_CchPrintfEx wnsprintf
#define Str_CchPrintfW(Dest, Format, ...) Str_CchPrintfExW(Dest, ARRAYSIZE(Dest), Format, __VA_ARGS__)
#define Str_CchPrintfA(Dest, Format, ...) Str_CchPrintfExA(Dest, ARRAYSIZE(Dest), Format, __VA_ARGS__)
#define Str_CchPrintf(Dest, Format, ...) Str_CchPrintfEx(Dest, ARRAYSIZE(Dest), Format, __VA_ARGS__)

#define Str_CchVPrintfExW wvnsprintfW
#define Str_CchVPrintfExA wvnsprintfA
#define Str_CchVPrintfEx wvnsprintf
#define Str_CchVPrintfW(Dest, Format, ArgList) Str_CchVPrintfExW(Dest, ARRAYSIZE(Dest), Format, ArgList)
#define Str_CchVPrintfA(Dest, Format, ArgList) Str_CchVPrintfExA(Dest, ARRAYSIZE(Dest), Format, ArgList)
#define Str_CchVPrintf(Dest, Format, ArgList) Str_CchVPrintfEx(Dest, ARRAYSIZE(Dest), Format, ArgList)

// String Encode

NTA_API ULONG NTAPI Str_CchU2AEx(PSTR Dest, ULONG DestCchSize, PCWSTR Src);
#define Str_CcbU2AEx Str_CchU2AEx
NTA_API ULONG NTAPI Str_CchA2UEx(_Out_writes_(DestCchSize) PWSTR Dest, _In_ ULONG DestCchSize, PCSTR Src);
NTA_API ULONG NTAPI Str_CcbA2UEx(_Out_writes_bytes_(DestCcbSize) PWSTR Dest, _In_ ULONG DestCcbSize, PCSTR Src);

#define Str_CchA2U(Dest, Src) Str_CchA2UEx(Dest, ARRAYSIZE(Dest), Src)
#define Str_CcbA2U(Dest, Src) Str_CcbA2UEx(Dest, ARRAYSIZE(Dest) * sizeof(WCHAR), Src)
#define Str_CchU2A(Dest, Src) Str_CchU2AEx(Dest, ARRAYSIZE(Dest), Src)
#define Str_CcbU2A(Dest, Src) Str_CcbU2AEx(Dest, ARRAYSIZE(Dest) * sizeof(CHAR), Src)

NTA_API NTSTATUS NTAPI Str_UnicodeToUTF8Ex(PSTR Dest, SIZE_T DestCchSize, PCWSTR Src, PSIZE_T CharsWritten);
#define Str_UnicodeToUTF8(pszDest, pszSrc, pulChWritten) Str_UnicodeToUTF8Ex(pszDest, ARRAYSIZE(pszDest), pszSrc, pulChWritten)

NTA_API VOID NTAPI Str_UpperW(PWSTR String);
NTA_API VOID NTAPI Str_UpperA(PSTR String);
#ifdef UNICODE
#define Str_Upper Str_UpperW
#else
#define Str_Upper Str_UpperA
#endif

// String Initialize

NTA_API VOID NTAPI Str_CchInitW(PUNICODE_STRING NTString, PWSTR String);
NTA_API VOID NTAPI Str_CchInitA(PSTRING NTString, PSTR String);
#ifdef UNICODE
#define Str_CchInit Str_CchInitW
#else
#define Str_CchInit Str_CchInitA
#endif

// String Convert

NTA_API BOOL NTAPI Str_ToIntExW(PCWSTR StrValue, BOOL Unsigned, UINT Base, PVOID Value, SIZE_T ValueSize);
NTA_API BOOL NTAPI Str_ToIntExA(PCSTR StrValue, BOOL Unsigned, UINT Base, PVOID Value, SIZE_T ValueSize);
#ifdef UNICODE
#define Str_ToIntEx Str_ToIntExW
#define Str_ToIntW(StrValue, Value) Str_ToIntExW(StrValue, FALSE, 0, Value, sizeof(*(Value)))
#define Str_ToInt Str_ToIntW
#define Str_ToUIntW(StrValue, Value) Str_ToIntExW(StrValue, TRUE, 0, Value, sizeof(*(Value)))
#define Str_ToUInt Str_ToUIntW
#define Str_HexToIntW(StrValue, Value) Str_ToIntExW(StrValue, FALSE, 16, Value, sizeof(*(Value)))
#define Str_HexToInt Str_HexToIntW
#define Str_HexToUIntW(StrValue, Value) Str_ToIntExW(StrValue, TRUE, 16, Value, sizeof(*(Value)))
#define Str_HexToUInt Str_HexToUIntW
#define Str_DecToIntW(StrValue, Value) Str_ToIntExW(StrValue, FALSE, 10, Value, sizeof(*(Value)))
#define Str_DecToInt Str_DecToIntW
#define Str_DecToUIntW(StrValue, Value) Str_ToIntExW(StrValue, TRUE, 10, Value, sizeof(*(Value)))
#define Str_DecToUInt Str_DecToUIntW
#define Str_OctToIntW(StrValue, Value) Str_ToIntExW(StrValue, FALSE, 8, Value, sizeof(*(Value)))
#define Str_OctToInt Str_OctToIntW
#define Str_OctToUIntW(StrValue, Value) Str_ToIntExW(StrValue, TRUE, 8, Value, sizeof(*(Value)))
#define Str_OctToUInt Str_OctToUIntW
#define Str_BinToIntW(StrValue, Value) Str_ToIntExW(StrValue, FALSE, 2, Value, sizeof(*(Value)))
#define Str_BinToInt Str_BinToIntW
#define Str_BinToUIntW(StrValue, Value) Str_ToIntExW(StrValue, TRUE, 2, Value, sizeof(*(Value)))
#define Str_BinToUInt Str_BinToUIntW
#else
#define Str_ToIntEx Str_ToIntExA
#define Str_ToIntA(StrValue, Value) Str_ToIntExA(StrValue, FALSE, 0, Value, sizeof(*(Value)))
#define Str_ToInt Str_ToIntA
#define Str_ToUIntA(StrValue, Value) Str_ToIntExA(StrValue, TRUE, 0, Value, sizeof(*(Value)))
#define Str_ToUInt Str_ToUIntA
#define Str_HexToIntA(StrValue, Value) Str_ToIntExA(StrValue, FALSE, 16, Value, sizeof(*(Value)))
#define Str_HexToInt Str_HexToIntA
#define Str_HexToUIntA(StrValue, Value) Str_ToIntExA(StrValue, TRUE, 16, Value, sizeof(*(Value)))
#define Str_HexToUInt Str_HexToUIntA
#define Str_DecToIntA(StrValue, Value) Str_ToIntExA(StrValue, FALSE, 10, Value, sizeof(*(Value)))
#define Str_DecToInt Str_DecToIntA
#define Str_DecToUIntA(StrValue, Value) Str_ToIntExA(StrValue, TRUE, 10, Value, sizeof(*(Value)))
#define Str_DecToUInt Str_DecToUIntA
#define Str_OctToIntA(StrValue, Value) Str_ToIntExA(StrValue, FALSE, 8, Value, sizeof(*(Value)))
#define Str_OctToInt Str_OctToIntA
#define Str_OctToUIntA(StrValue, Value) Str_ToIntExA(StrValue, TRUE, 8, Value, sizeof(*(Value)))
#define Str_OctToUInt Str_OctToUIntA
#define Str_BinToIntA(StrValue, Value) Str_ToIntExA(StrValue, FALSE, 2, Value, sizeof(*(Value)))
#define Str_BinToInt Str_BinToIntA
#define Str_BinToUIntA(StrValue, Value) Str_ToIntExA(StrValue, TRUE, 2, Value, sizeof(*(Value)))
#define Str_BinToUInt Str_BinToUIntA
#endif

BOOL NTAPI Str_FromIntExW(INT64 Value, BOOL Unsigned, UINT Base, PWSTR StrValue, ULONG DestCchSize);
BOOL NTAPI Str_FromIntExA(INT64 Value, BOOL Unsigned, UINT Base, PSTR StrValue, ULONG DestCchSize);
#ifdef UNICODE
#define Str_FromIntEx Str_FromIntExW
#define Str_FromIntW(Value, StrValue) Str_FromIntExW(Value, FALSE, 0, StrValue, ARRAYSIZE(StrValue))
#define Str_FromInt Str_FromIntW
#define Str_FromUIntW(Value, StrValue) Str_FromIntExW(Value, TRUE, 0, StrValue, ARRAYSIZE(StrValue))
#define Str_FromUInt Str_FromUIntW
#define Str_HexFromIntW(Value, StrValue) Str_FromIntExW(Value, FALSE, 16, StrValue, ARRAYSIZE(StrValue))
#define Str_HexFromInt Str_HexFromIntW
#define Str_HexFromUIntW(Value, StrValue) Str_FromIntExW(Value, TRUE, 16, StrValue, ARRAYSIZE(StrValue))
#define Str_HexFromUInt Str_HexFromUIntW
#define Str_DecFromIntW(Value, StrValue) Str_FromIntExW(Value, FALSE, 10, StrValue, ARRAYSIZE(StrValue))
#define Str_DecFromInt Str_DecFromIntW
#define Str_DecFromUIntW(Value, StrValue) Str_FromIntExW(Value, TRUE, 10, StrValue, ARRAYSIZE(StrValue))
#define Str_DecFromUInt Str_DecFromUIntW
#define Str_OctFromIntW(Value, StrValue) Str_FromIntExW(Value, FALSE, 8, StrValue, ARRAYSIZE(StrValue))
#define Str_OctFromInt Str_OctFromIntW
#define Str_OctFromUIntW(Value, StrValue) Str_FromIntExW(Value, TRUE, 8, StrValue, ARRAYSIZE(StrValue))
#define Str_OctFromUInt Str_OctFromUIntW
#define Str_BinFromIntW(Value, StrValue) Str_FromIntExW(Value, FALSE, 2, StrValue, ARRAYSIZE(StrValue))
#define Str_BinFromInt Str_BinFromIntW
#define Str_BinFromUIntW(Value, StrValue) Str_FromIntExW(Value, TRUE, 2, StrValue, ARRAYSIZE(StrValue))
#define Str_BinFromUInt Str_BinFromUIntW
#else
#define Str_FromIntEx Str_FromIntExA
#define Str_FromIntA(Value, StrValue) Str_FromIntExA(Value, FALSE, 0, StrValue, ARRAYSIZE(StrValue))
#define Str_FromInt Str_FromIntA
#define Str_FromUIntA(Value, StrValue) Str_FromIntExA(Value, TRUE, 0, StrValue, ARRAYSIZE(StrValue))
#define Str_FromUInt Str_FromUIntA
#define Str_HexFromIntA(Value, StrValue) Str_FromIntExA(Value, FALSE, 16, StrValue, ARRAYSIZE(StrValue))
#define Str_HexFromInt Str_HexFromIntA
#define Str_HexFromUIntA(Value, StrValue) Str_FromIntExA(Value, TRUE, 16, StrValue, ARRAYSIZE(StrValue))
#define Str_HexFromUInt Str_HexFromUIntA
#define Str_DecFromIntA(Value, StrValue) Str_FromIntExA(Value, FALSE, 10, StrValue, ARRAYSIZE(StrValue))
#define Str_DecFromInt Str_DecFromIntA
#define Str_DecFromUIntA(Value, StrValue) Str_FromIntExA(Value, TRUE, 10, StrValue, ARRAYSIZE(StrValue))
#define Str_DecFromUInt Str_DecFromUIntA
#define Str_OctFromIntA(Value, StrValue) Str_FromIntExA(Value, FALSE, 8, StrValue, ARRAYSIZE(StrValue))
#define Str_OctFromInt Str_OctFromIntA
#define Str_OctFromUIntA(Value, StrValue) Str_FromIntExA(Value, TRUE, 8, StrValue, ARRAYSIZE(StrValue))
#define Str_OctFromUInt Str_OctFromUIntA
#define Str_BinFromIntA(Value, StrValue) Str_FromIntExA(Value, FALSE, 2, StrValue, ARRAYSIZE(StrValue))
#define Str_BinFromInt Str_BinFromIntA
#define Str_BinFromUIntA(Value, StrValue) Str_FromIntExA(Value, TRUE, 2, StrValue, ARRAYSIZE(StrValue))
#define Str_BinFromUInt Str_BinFromUIntA
#endif

NTA_API BOOL NTAPI Str_RGBToHexExW(COLORREF Color, PWSTR Dest, SIZE_T DestCchSize);
#define Str_RGBToHexW(Color, Dest) Str_RGBToHexExW(Color, Dest, ARRAYSIZE(Dest))
#ifdef UNICODE
#define Str_RGBToHexEx Str_RGBToHexExW
#define Str_RGBToHex Str_RGBToHexW
#else
#define Str_RGBToHexEx Str_RGBToHexExA
#define Str_RGBToHex Str_RGBToHexA
#endif

// String Hash

NTA_API DWORD NTAPI Str_HashW(PCWSTR String, STR_HASH_ALGORITHM HashAlgorithm);
NTA_API DWORD NTAPI Str_HashA(PCSTR String, STR_HASH_ALGORITHM HashAlgorithm);
#ifdef UNICODE
#define Str_Hash Str_HashW
#else
#define Str_Hash Str_HashA
#endif