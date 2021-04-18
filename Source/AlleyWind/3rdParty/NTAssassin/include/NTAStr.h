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

NTA_API UINT NTAPI Str_CchLenExW(LPCWSTR psz, UINT cchMax);
NTA_API UINT NTAPI Str_CchLenExA(LPCSTR psz, UINT cchMax);
#ifdef UNICODE
#define Str_CchLenEx Str_CchLenExW
#else
#define Str_CchLenEx Str_CchLenExA
#endif

#define Str_CchLenW(psz) Str_CchLenExW(psz, ARRAYSIZE(psz))
#define Str_CchLenA(psz) Str_CchLenExA(psz, ARRAYSIZE(psz))
#ifdef UNICODE
#define Str_CchLen Str_CchLenW
#else
#define Str_CchLen Str_CchLenA
#endif

NTA_API UINT NTAPI Str_CcbLenExW(LPCWSTR psz, UINT ccbMax);
#define Str_CcbLenExA Str_CchLenExA
#ifdef UNICODE
#define Str_CcbLenEx Str_CcbLenExW
#else
#define Str_CcbLenEx Str_CcbLenExA
#endif

NTA_API UINT NTAPI Str_CchCopyExW(LPWSTR pszDest, UINT cchDest, LPCWSTR pszSrc);
NTA_API UINT NTAPI Str_CchCopyExA(LPSTR pszDest, UINT cchDest, LPCSTR pszSrc);
#ifdef UNICODE
#define Str_CchCopyEx Str_CchCopyExW
#else
#define Str_CchCopyEx Str_CchCopyExA
#endif

#define Str_CchCopyW(pszDest, pszSrc) Str_CchCopyExW(pszDest, ARRAYSIZE(pszDest), pszSrc)
#define Str_CchCopyA(pszDest, pszSrc) Str_CchCopyExA(pszDest, ARRAYSIZE(pszDest), pszSrc)
#ifdef UNICODE
#define Str_CchCopy Str_CchCopyW
#else
#define Str_CchCopy Str_CchCopyA
#endif

NTA_API UINT NTAPI Str_CcbCopyExW(LPWSTR pszDest, UINT ccbDest, LPCWSTR pszSrc);
#define Str_CcbCopyExA Str_CchCopyExA
#define Str_CcbCopyW(pszDest, pszSrc) Str_CcbCopyExW(pszDest, sizeof(pszDest), pszSrc)
#define Str_CcbCopyA(pszDest, pszSrc) Str_CcbCopyExA(pszDest, sizeof(pszDest), pszSrc)
#ifdef UNICODE
#define Str_CcbCopy Str_CcbCopyW
#else
#define Str_CcbCopy Str_CcbCopyA
#endif

NTA_API BOOL NTAPI Str_CchEqualExW(LPCWSTR psz1, UINT cch1, LPCWSTR psz2, UINT cch2);
NTA_API BOOL NTAPI Str_CchEqualExA(LPCSTR psz1, UINT cch1, LPCSTR psz2, UINT cch2);

#ifdef UNICODE
#define Str_CchEqualEx Str_CchEqualExW
#else
#define Str_CchEqualEx Str_CchEqualExA
#endif

#define Str_EqualW(psz1, psz2) Str_CchEqualExW(psz1, ARRAYSIZE(psz1), psz2, ARRAYSIZE(psz2))
#define Str_EqualA(psz1, psz2) Str_CchEqualExA(psz1, ARRAYSIZE(psz1), psz2, ARRAYSIZE(psz2))
#ifdef UNICODE
#define Str_Equal Str_EqualW
#else
#define Str_Equal Str_EqualA
#endif

NTA_API BOOL NTAPI Str_CcbEqualICExW(LPCWSTR psz1, UINT ccb1, LPCWSTR psz2, UINT ccb2);
#ifdef UNICODE
#define Str_CcbEqualICEx Str_CcbEqualICExW
#else
#define Str_CcbEqualICEx Str_CcbEqualICExA
#endif

#define Str_CcbEqualICW(psz1, ccb1, psz2, ccb2) Str_CcbEqualICExW(psz1, sizeof(psz1), psz2, sizeof(psz2))
#define Str_CcbEqualICA(psz1, ccb1, psz2, ccb2) Str_CcbEqualICExA(psz1, sizeof(psz1), psz2, sizeof(psz2))
#ifdef UNICODE
#define Str_CcbEqualIC Str_CcbEqualICW
#else
#define Str_CcbEqualIC Str_CcbEqualICA
#endif

NTA_API UINT NTAPI Str_CchIndex_BFExW(LPCWSTR lpszSrc, UINT cchMaxSrc, LPCWSTR lpszPattern, UINT cchMaxPattern);
#define Str_CchIndex_BFW(lpszSrc, lpszPattern) Str_CchIndex_BFExW(lpszSrc, ARRAYSIZE(lpszSrc), lpszPattern, ARRAYSIZE(lpszPattern))
#define Str_CchIndex_BFA(lpszSrc, lpszPattern) Str_CchIndex_BFExA(lpszSrc, ARRAYSIZE(lpszSrc), lpszPattern, ARRAYSIZE(lpszPattern))
#ifdef UNICODE
#define Str_CchIndex_BFEx Str_CchIndex_BFExW
#define Str_CchIndex_BF Str_CchIndex_BFW
#else
#define Str_CchIndex_BFEx Str_CchIndex_BFExA
#define Str_CchIndex_BF Str_CchIndex_BFA
#endif

#define Str_CchPrintfExW wnsprintfW
#define Str_CchPrintfExA wnsprintfA
#define Str_CchPrintfEx wnsprintf
#define Str_CchPrintfW(pszDest, pszFmt, ...) Str_CchPrintfExW(pszDest, ARRAYSIZE(pszDest), pszFmt, __VA_ARGS__)
#define Str_CchPrintfA(pszDest, pszFmt, ...) Str_CchPrintfExA(pszDest, ARRAYSIZE(pszDest), pszFmt, __VA_ARGS__)
#define Str_CchPrintf(pszDest, pszFmt, ...) Str_CchPrintfEx(pszDest, ARRAYSIZE(pszDest), pszFmt, __VA_ARGS__)

#define Str_CchVPrintfExW wvnsprintfW
#define Str_CchVPrintfExA wvnsprintfA
#define Str_CchVPrintfEx wvnsprintf
#define Str_CchVPrintfW(pszDest, pszFmt, arglist) Str_CchVPrintfExW(pszDest, ARRAYSIZE(pszDest), pszFmt, arglist)
#define Str_CchVPrintfA(pszDest, pszFmt, arglist) Str_CchVPrintfExA(pszDest, ARRAYSIZE(pszDest), pszFmt, arglist)
#define Str_CchVPrintf(pszDest, pszFmt, arglist) Str_CchVPrintfEx(pszDest, ARRAYSIZE(pszDest), pszFmt, arglist)

NTA_API VOID NTAPI Str_CchInitExW(PUNICODE_STRING lpstStr, LPWSTR lpStr, UINT cchMax);
NTA_API VOID NTAPI Str_CchInitExA(PSTRING lpstStr, LPSTR lpStr, UINT cchMax);
#define Str_CchInitW(lpstStr, lpStr) Str_CchInitExW(lpstStr, lpStr, ARRAYSIZE(lpStr))
#define Str_CchInitA(lpstStr, lpStr) Str_CchInitExA(lpstStr, lpStr, ARRAYSIZE(lpStr))
#ifdef UNICODE
#define Str_CchInitEx Str_CchInitExW
#define Str_CchInit Str_CchInitW
#else
#define Str_CchInitEx Str_CchInitExA
#define Str_CchInit Str_CchInitA
#endif

NTA_API UINT NTAPI Str_CchU2AEx(LPSTR lpszANSI, UINT cchANSIMax, LPCWSTR lpszUnicode);
NTA_API UINT NTAPI Str_CchA2UEx(_Out_writes_(cchUnicodeMax) LPWSTR lpszUnicode, _In_ UINT cchUnicodeMax, LPCSTR lpszANSI);
NTA_API UINT NTAPI Str_CcbA2UEx(_Out_writes_bytes_(ccbUnicodeMax) LPWSTR lpszUnicode, _In_ UINT ccbUnicodeMax, LPCSTR lpszANSI);
#define Str_CcbU2AEx Str_CchU2AEx

#define Str_CchA2U(lpszUnicode, lpszANSI) Str_CchA2UEx(lpszUnicode, ARRAYSIZE(lpszUnicode), lpszANSI)
#define Str_CcbA2U(lpszUnicode, lpszANSI) Str_CcbA2UEx(lpszUnicode, ARRAYSIZE(lpszUnicode) * sizeof(WCHAR), lpszANSI)
#define Str_CchU2A(lpszANSI, lpszUnicode) Str_CchU2AEx(lpszANSI, ARRAYSIZE(lpszANSI), lpszUnicode)
#define Str_CcbU2A(lpszANSI, lpszUnicode) Str_CcbU2AEx(lpszANSI, ARRAYSIZE(lpszANSI) * sizeof(CHAR), lpszUnicode)

NTA_API BOOL NTAPI Str_HexTo32ExW(LPCWSTR lpsz, UINT cchMax, PDWORD lpdwOut);
NTA_API BOOL NTAPI Str_HexTo32ExA(LPCSTR lpsz, UINT cchMax, PDWORD lpdwOut);
#define Str_HexTo32W(lpsz, lpdwOut) Str_HexTo32ExW(lpsz, ARRAYSIZE(lpsz), lpdwOut)
#define Str_HexTo32A(lpsz, lpdwOut) Str_HexTo32ExA(lpsz, ARRAYSIZE(lpsz), lpdwOut)
#define Str_HexToHWndW(lpsz, lphWnd) Str_HexTo32W(lpsz, (PDWORD)(lphWnd))
#define Str_HexToHWndA(lpsz, lphWnd) Str_HexTo32A(lpsz, (PDWORD)(lphWnd))
#ifdef UNICODE
#define Str_HexTo32Ex Str_HexTo32ExW
#define Str_HexTo32 Str_HexTo32W
#define Str_HexToHWnd Str_HexToHWndW
#else
#define Str_HexTo32Ex Str_HexTo32ExA
#define Str_HexTo32 Str_HexTo32A
#define Str_HexToHWnd Str_HexToHWndA
#endif

NTA_API BOOL NTAPI Str_16ToUDecExW(USHORT uNum, LPWSTR lpszOutput, UINT cchMax);
#define Str_16ToUDecW(uNum, lpszOutput) Str_16ToUDecExW(uNum, lpszOutput, ARRAYSIZE(lpszOutput))
#ifdef UNICODE
#define Str_16ToUDecEx Str_16ToUDecExW
#define Str_16ToUDec Str_16ToUDecW
#else
#define Str_16ToUDecEx Str_16ToUDecExA
#define Str_16ToUDec Str_16ToUDecA
#endif

NTA_API NTSTATUS NTAPI Str_UnicodeToUTF8Ex(LPSTR pszDest, UINT cchDest, LPCWSTR pszSrc, PULONG pulChWritten);
#define Str_UnicodeToUTF8(pszDest, pszSrc, pulChWritten) Str_UnicodeToUTF8Ex(pszDest, ARRAYSIZE(pszDest), pszSrc, pulChWritten)

NTA_API DWORD NTAPI Str_HashExW(LPCWSTR psz, UINT cchMax, STR_HASH_ALGORITHM HashAlgorithm);
NTA_API DWORD NTAPI Str_HashExA(LPCSTR psz, UINT cchMax, STR_HASH_ALGORITHM HashAlgorithm);
#define Str_HashW(psz, HashAlgorithm) Str_HashExW(psz, ARRAYSIZE(psz), HashAlgorithm)
#define Str_HashA(psz, HashAlgorithm) Str_HashExA(psz, ARRAYSIZE(psz), HashAlgorithm)
#ifdef UNICODE
#define Str_HashEx Str_HashExW
#define Str_Hash Str_HashW
#else
#define Str_HashEx Str_HashExA
#define Str_Hash Str_HashA
#endif