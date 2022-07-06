/**
  * @brief Native library of NTAssassin provides basic string functions.
  * @details Functions are named in pattern: Str_[I][Len|Cat|Copy|...][Ex]
  * 
  *  ***The terminating null character was included in buffer size, not included in string length and returnd length***
  *
  * Comparision:
  *  I: Insensitive of case;
  * 
  * Operation:
  *  Len: Gets length of string;
  *  Cat: Catches strings;
  *  Copy: Copies strings;
  *  Equal: Compares strings are equal or not;
  *  Cmp: Compares strings;
  *
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
    StrHashAlgorithmX65599 = StrHashAlgorithmSDBM,
    StrHashAlgorithmFNV1a
} STR_HASH_ALGORITHM, * PSTR_HASH_ALGORITHM;

// String Length and Size

NTA_API SIZE_T NTAPI Str_LenW(_In_ PCWSTR String);
NTA_API SIZE_T NTAPI Str_LenA(_In_ PCSTR String);
#ifdef UNICODE
#define Str_Len Str_LenW
#else
#define Str_Len Str_LenA
#endif

#define Str_SizeW(String) (Str_LenW(String) * sizeof(WCHAR))
#define Str_SizeA Str_LenA
#ifdef UNICODE
#define Str_Size Str_SizeW
#else
#define Str_Size Str_SizeA
#endif

// String Copy

NTA_API SIZE_T NTAPI Str_CopyExW(_Out_writes_z_(DestCchSize) PWSTR Dest, SIZE_T DestCchSize, _In_ PCWSTR Src);
NTA_API SIZE_T NTAPI Str_CopyExA(_Out_writes_z_(DestCchSize) PSTR Dest, SIZE_T DestCchSize, _In_ PCSTR Src);
#define Str_CopyW(Dest, Src) Str_CopyExW(Dest, ARRAYSIZE(Dest), Src)
#define Str_CopyA(Dest, Src) Str_CopyExA(Dest, ARRAYSIZE(Dest), Src)
#ifdef UNICODE
#define Str_CopyEx Str_CopyExW
#define Str_Copy Str_CopyW
#else
#define Str_CopyEx Str_CopyExA
#define Str_Copy Str_CopyA
#endif

// String Compare

NTA_API INT NTAPI Str_CmpW(_In_ PCWSTR String1, _In_ PCWSTR String2);
NTA_API INT NTAPI Str_CmpA(_In_ PCSTR String1, _In_ PCSTR String2);
NTA_API INT NTAPI Str_ICmpW(_In_ PCWSTR String1, _In_ PCWSTR String2);
NTA_API INT NTAPI Str_ICmpA(_In_ PCSTR String1, _In_ PCSTR String2);
#define Str_EqualW(String1, String2) (BOOL)(Str_CmpW(String1, String2) == 0)
#define Str_EqualA(String1, String2) (BOOL)(Str_CmpA(String1, String2) == 0)
#define Str_IEqualW(String1, String2) (BOOL)(Str_ICmpW(String1, String2) == 0)
#define Str_IEqualA(String1, String2) (BOOL)(Str_ICmpA(String1, String2) == 0)
#ifdef UNICODE
#define Str_Cmp Str_CmpW
#define Str_ICmp Str_ICmpW
#define Str_Equal Str_EqualW
#define Str_IEqual Str_IEqualW
#else
#define Str_Cmp Str_CmpA
#define Str_ICmp Str_ICmpA
#define Str_Equal Str_EqualA
#define Str_IEqual Str_IEqualA
#endif

// String Printf

NTA_API INT NTAPI Str_VPrintfExW(_Out_writes_z_(DestCchSize) PWSTR Dest, _In_ INT DestCchSize, _In_ _Printf_format_string_ PCWSTR Format, _In_ va_list ArgList);
NTA_API INT NTAPI Str_VPrintfExA(_Out_writes_z_(DestCchSize) PSTR Dest, _In_ INT DestCchSize, _In_ _Printf_format_string_ PCSTR Format, _In_ va_list ArgList);
NTA_API INT WINAPIV Str_PrintfExW(_Out_writes_z_(DestCchSize) PWSTR Dest, _In_ INT DestCchSize, _In_ _Printf_format_string_ PCWSTR Format, ...);
NTA_API INT WINAPIV Str_PrintfExA(_Out_writes_z_(DestCchSize) PSTR Dest, _In_ INT DestCchSize, _In_ _Printf_format_string_ PCSTR Format, ...);
#ifdef UNICODE
#define Str_VPrintfEx Str_VPrintfExW
#define Str_PrintfEx Str_PrintfExW
#else
#define Str_VPrintfEx Str_VPrintfExA
#define Str_PrintfEx Str_PrintfExA
#endif
#define Str_PrintfW(Dest, Format, ...) Str_PrintfExW(Dest, ARRAYSIZE(Dest), Format, __VA_ARGS__)
#define Str_PrintfA(Dest, Format, ...) Str_PrintfExA(Dest, ARRAYSIZE(Dest), Format, __VA_ARGS__)
#define Str_Printf(Dest, Format, ...) Str_PrintfEx(Dest, ARRAYSIZE(Dest), Format, __VA_ARGS__)
#define Str_VPrintfW(Dest, Format, ArgList) Str_VPrintfExW(Dest, ARRAYSIZE(Dest), Format, ArgList)
#define Str_VPrintfA(Dest, Format, ArgList) Str_VPrintfExA(Dest, ARRAYSIZE(Dest), Format, ArgList)
#define Str_VPrintf(Dest, Format, ArgList) Str_VPrintfEx(Dest, ARRAYSIZE(Dest), Format, ArgList)

// String Index

NTA_API INT NTAPI Str_Index_BFW(_In_ PCWSTR String, _In_ PCWSTR Pattern);
NTA_API INT NTAPI Str_Index_BFA(_In_ PCSTR String, _In_ PCSTR Pattern);
#ifdef UNICODE
#define Str_Index_BF Str_Index_BFW
#else
#define Str_Index_BF Str_Index_BFA
#endif

// String Encode

NTA_API ULONG NTAPI Str_U2AEx(_Out_writes_z_(DestCchSize) PSTR Dest, _In_ ULONG DestCchSize, _In_ PCWSTR Src);
NTA_API ULONG NTAPI Str_A2UEx(_Out_writes_z_(DestCchSize) PWSTR Dest, _In_ ULONG DestCchSize, _In_ PCSTR Src);
#define Str_U2A(Dest, Src) Str_U2AEx(Dest, ARRAYSIZE(Dest), Src)
#define Str_A2U(Dest, Src) Str_A2UEx(Dest, ARRAYSIZE(Dest), Src)

NTA_API SIZE_T NTAPI Str_UnicodeToUTF8Ex(_Out_writes_z_(DestCchSize) PSTR Dest, _In_ SIZE_T DestCchSize, _In_ PCWSTR Src);
#define Str_UnicodeToUTF8(Dest, Src) Str_UnicodeToUTF8Ex(Dest, ARRAYSIZE(Dest), Src)

NTA_API VOID NTAPI Str_UpperW(_Inout_ PWSTR String);
NTA_API VOID NTAPI Str_UpperA(_Inout_ PSTR String);
NTA_API VOID NTAPI Str_LowerW(_Inout_ PWSTR String);
NTA_API VOID NTAPI Str_LowerA(_Inout_ PSTR String);
#ifdef UNICODE
#define Str_Upper Str_UpperW
#define Str_Lower Str_LowerW
#else
#define Str_Upper Str_UpperA
#define Str_Lower Str_LowerA
#endif
#define Str_UpperChar(Ch) ((Ch) >= 'a' && (Ch) <= 'z' ? (Ch) - 'a' + 'A' : (Ch))
#define Str_LowerChar(Ch) ((Ch) >= 'A' && (Ch) <= 'Z' ? (Ch) - 'A' + 'a' : (Ch))

// String Initialize

NTA_API VOID NTAPI Str_InitW(_Out_ PUNICODE_STRING NTString, _In_ PWSTR String);
NTA_API VOID NTAPI Str_InitA(_Out_ PSTRING NTString, _In_ PSTR String);
#ifdef UNICODE
#define Str_Init Str_InitW
#else
#define Str_Init Str_InitA
#endif

// String Convert

_Success_(return != FALSE) NTA_API BOOL NTAPI Str_ToIntExW(_In_ PCWSTR StrValue, BOOL Unsigned, UINT Base, _Out_writes_bytes_(ValueSize) PVOID Value, _In_ SIZE_T ValueSize);
_Success_(return != FALSE) NTA_API BOOL NTAPI Str_ToIntExA(_In_ PCSTR StrValue, BOOL Unsigned, UINT Base, _Out_writes_bytes_(ValueSize) PVOID Value, _In_ SIZE_T ValueSize);

#define Str_ToIntW(StrValue, Value) Str_ToIntExW(StrValue, FALSE, 0, Value, sizeof(*(Value)))
#define Str_ToIntA(StrValue, Value) Str_ToIntExA(StrValue, FALSE, 0, Value, sizeof(*(Value)))
#define Str_ToUIntW(StrValue, Value) Str_ToIntExW(StrValue, TRUE, 0, Value, sizeof(*(Value)))
#define Str_ToUIntA(StrValue, Value) Str_ToIntExA(StrValue, TRUE, 0, Value, sizeof(*(Value)))
#define Str_HexToIntW(StrValue, Value) Str_ToIntExW(StrValue, FALSE, 16, Value, sizeof(*(Value)))
#define Str_HexToIntA(StrValue, Value) Str_ToIntExA(StrValue, FALSE, 16, Value, sizeof(*(Value)))
#define Str_HexToUIntW(StrValue, Value) Str_ToIntExW(StrValue, TRUE, 16, Value, sizeof(*(Value)))
#define Str_HexToUIntA(StrValue, Value) Str_ToIntExA(StrValue, TRUE, 16, Value, sizeof(*(Value)))
#define Str_DecToIntW(StrValue, Value) Str_ToIntExW(StrValue, FALSE, 10, Value, sizeof(*(Value)))
#define Str_DecToIntA(StrValue, Value) Str_ToIntExA(StrValue, FALSE, 10, Value, sizeof(*(Value)))
#define Str_DecToUIntW(StrValue, Value) Str_ToIntExW(StrValue, TRUE, 10, Value, sizeof(*(Value)))
#define Str_DecToUIntA(StrValue, Value) Str_ToIntExA(StrValue, TRUE, 10, Value, sizeof(*(Value)))
#define Str_OctToIntW(StrValue, Value) Str_ToIntExW(StrValue, FALSE, 8, Value, sizeof(*(Value)))
#define Str_OctToIntA(StrValue, Value) Str_ToIntExA(StrValue, FALSE, 8, Value, sizeof(*(Value)))
#define Str_OctToUIntW(StrValue, Value) Str_ToIntExW(StrValue, TRUE, 8, Value, sizeof(*(Value)))
#define Str_OctToUIntA(StrValue, Value) Str_ToIntExA(StrValue, TRUE, 8, Value, sizeof(*(Value)))
#define Str_BinToIntW(StrValue, Value) Str_ToIntExW(StrValue, FALSE, 2, Value, sizeof(*(Value)))
#define Str_BinToIntA(StrValue, Value) Str_ToIntExA(StrValue, FALSE, 2, Value, sizeof(*(Value)))
#define Str_BinToUIntW(StrValue, Value) Str_ToIntExW(StrValue, TRUE, 2, Value, sizeof(*(Value)))
#define Str_BinToUIntA(StrValue, Value) Str_ToIntExA(StrValue, TRUE, 2, Value, sizeof(*(Value)))

#ifdef UNICODE
#define Str_ToIntEx Str_ToIntExW
#define Str_ToInt Str_ToIntW
#define Str_ToUInt Str_ToUIntW
#define Str_HexToInt Str_HexToIntW
#define Str_HexToUInt Str_HexToUIntW
#define Str_DecToInt Str_DecToIntW
#define Str_DecToUInt Str_DecToUIntW
#define Str_OctToInt Str_OctToIntW
#define Str_OctToUInt Str_OctToUIntW
#define Str_BinToInt Str_BinToIntW
#define Str_BinToUInt Str_BinToUIntW
#else
#define Str_ToIntEx Str_ToIntExA
#define Str_ToInt Str_ToIntA
#define Str_ToUInt Str_ToUIntA
#define Str_HexToInt Str_HexToIntA
#define Str_HexToUInt Str_HexToUIntA
#define Str_DecToInt Str_DecToIntA
#define Str_DecToUInt Str_DecToUIntA
#define Str_OctToInt Str_OctToIntA
#define Str_OctToUInt Str_OctToUIntA
#define Str_BinToInt Str_BinToIntA
#define Str_BinToUInt Str_BinToUIntA
#endif

_Success_(return != FALSE) BOOL NTAPI Str_FromIntExW(INT64 Value, BOOL Unsigned, UINT Base, _Out_writes_z_(DestCchSize) PWSTR StrValue, _In_ ULONG DestCchSize);
_Success_(return != FALSE) BOOL NTAPI Str_FromIntExA(INT64 Value, BOOL Unsigned, UINT Base, _Out_writes_z_(DestCchSize) PSTR StrValue, _In_ ULONG DestCchSize);

#define Str_FromIntW(Value, StrValue) Str_FromIntExW(Value, FALSE, 0, StrValue, ARRAYSIZE(StrValue))
#define Str_FromIntA(Value, StrValue) Str_FromIntExA(Value, FALSE, 0, StrValue, ARRAYSIZE(StrValue))
#define Str_FromUIntW(Value, StrValue) Str_FromIntExW(Value, TRUE, 0, StrValue, ARRAYSIZE(StrValue))
#define Str_FromUIntA(Value, StrValue) Str_FromIntExA(Value, TRUE, 0, StrValue, ARRAYSIZE(StrValue))
#define Str_HexFromIntW(Value, StrValue) Str_FromIntExW(Value, FALSE, 16, StrValue, ARRAYSIZE(StrValue))
#define Str_HexFromIntA(Value, StrValue) Str_FromIntExA(Value, FALSE, 16, StrValue, ARRAYSIZE(StrValue))
#define Str_HexFromUIntW(Value, StrValue) Str_FromIntExW(Value, TRUE, 16, StrValue, ARRAYSIZE(StrValue))
#define Str_HexFromUIntA(Value, StrValue) Str_FromIntExA(Value, TRUE, 16, StrValue, ARRAYSIZE(StrValue))
#define Str_DecFromIntW(Value, StrValue) Str_FromIntExW(Value, FALSE, 10, StrValue, ARRAYSIZE(StrValue))
#define Str_DecFromIntA(Value, StrValue) Str_FromIntExA(Value, FALSE, 10, StrValue, ARRAYSIZE(StrValue))
#define Str_DecFromUIntW(Value, StrValue) Str_FromIntExW(Value, TRUE, 10, StrValue, ARRAYSIZE(StrValue))
#define Str_DecFromUIntA(Value, StrValue) Str_FromIntExA(Value, TRUE, 10, StrValue, ARRAYSIZE(StrValue))
#define Str_OctFromIntW(Value, StrValue) Str_FromIntExW(Value, FALSE, 8, StrValue, ARRAYSIZE(StrValue))
#define Str_OctFromIntA(Value, StrValue) Str_FromIntExA(Value, FALSE, 8, StrValue, ARRAYSIZE(StrValue))
#define Str_OctFromUIntW(Value, StrValue) Str_FromIntExW(Value, TRUE, 8, StrValue, ARRAYSIZE(StrValue))
#define Str_OctFromUIntA(Value, StrValue) Str_FromIntExA(Value, TRUE, 8, StrValue, ARRAYSIZE(StrValue))
#define Str_BinFromIntW(Value, StrValue) Str_FromIntExW(Value, FALSE, 2, StrValue, ARRAYSIZE(StrValue))
#define Str_BinFromIntA(Value, StrValue) Str_FromIntExA(Value, FALSE, 2, StrValue, ARRAYSIZE(StrValue))
#define Str_BinFromUIntW(Value, StrValue) Str_FromIntExW(Value, TRUE, 2, StrValue, ARRAYSIZE(StrValue))
#define Str_BinFromUIntA(Value, StrValue) Str_FromIntExA(Value, TRUE, 2, StrValue, ARRAYSIZE(StrValue))

#ifdef UNICODE
#define Str_FromIntEx Str_FromIntExW
#define Str_FromInt Str_FromIntW
#define Str_FromUInt Str_FromUIntW
#define Str_HexFromInt Str_HexFromIntW
#define Str_HexFromUInt Str_HexFromUIntW
#define Str_DecFromInt Str_DecFromIntW
#define Str_DecFromUInt Str_DecFromUIntW
#define Str_OctFromInt Str_OctFromIntW
#define Str_OctFromUInt Str_OctFromUIntW
#define Str_BinFromInt Str_BinFromIntW
#define Str_BinFromUInt Str_BinFromUIntW
#else
#define Str_FromIntEx Str_FromIntExA
#define Str_FromInt Str_FromIntA
#define Str_FromUInt Str_FromUIntA
#define Str_HexFromInt Str_HexFromIntA
#define Str_HexFromUInt Str_HexFromUIntA
#define Str_DecFromInt Str_DecFromIntA
#define Str_DecFromUInt Str_DecFromUIntA
#define Str_OctFromInt Str_OctFromIntA
#define Str_OctFromUInt Str_OctFromUIntA
#define Str_BinFromInt Str_BinFromIntA
#define Str_BinFromUInt Str_BinFromUIntA
#endif

_Success_(return == TRUE) NTA_API BOOL NTAPI Str_RGBToHexExW(COLORREF Color, _Out_writes_z_(DestCchSize) PWSTR Dest, _In_ SIZE_T DestCchSize);
_Success_(return == TRUE) NTA_API BOOL NTAPI Str_RGBToHexExA(COLORREF Color, _Out_writes_z_(DestCchSize) PSTR Dest, _In_ SIZE_T DestCchSize);
#define Str_RGBToHexW(Color, Dest) Str_RGBToHexExW(Color, Dest, ARRAYSIZE(Dest))
#define Str_RGBToHexA(Color, Dest) Str_RGBToHexExA(Color, Dest, ARRAYSIZE(Dest))
#ifdef UNICODE
#define Str_RGBToHexEx Str_RGBToHexExW
#define Str_RGBToHex Str_RGBToHexW
#else
#define Str_RGBToHexEx Str_RGBToHexExA
#define Str_RGBToHex Str_RGBToHexA
#endif

// String Hash

NTA_API DWORD NTAPI Str_HashW(_In_ PCWSTR String, STR_HASH_ALGORITHM HashAlgorithm);
NTA_API DWORD NTAPI Str_HashA(_In_ PCSTR String, STR_HASH_ALGORITHM HashAlgorithm);
#ifdef UNICODE
#define Str_Hash Str_HashW
#else
#define Str_Hash Str_HashA
#endif

PWSTR NTAPI Str_NameOfPath(_In_ PWSTR Path, _In_opt_ ULONG LengthOfPath);