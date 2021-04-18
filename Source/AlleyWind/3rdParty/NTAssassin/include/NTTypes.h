#pragma once

#include "NTAssassin.h"

typedef DWORD64 QWORD, *PQWORD, *LPQWORD;

typedef BOOL(WINAPI* PFNIsProcessDPIAware)();

typedef HRESULT(STDAPICALLTYPE* PFNDwmIsCompositionEnabled)(
    BOOL *pfEnabled);

typedef BOOL(WINAPI* PFNGetWindowDisplayAffinity)(
    HWND hWnd,
    DWORD* pdwAffinity);

typedef BOOL(WINAPI* PFNSetWindowDisplayAffinity)(
    HWND hWnd,
    DWORD dwAffinity);

typedef HRESULT(STDAPICALLTYPE* PFNSetWindowTheme)(
    _In_ HWND hwnd,
    _In_opt_ LPCWSTR pszSubAppName,
    _In_opt_ LPCWSTR pszSubIdList
    );