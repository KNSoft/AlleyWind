#pragma once

#include "NTAssassin.h"

typedef DWORD64 QWORD, *PQWORD, *LPQWORD;

typedef BOOL(WINAPI* PFNIsProcessDPIAware)();

typedef HRESULT(STDAPICALLTYPE* PFNGetDpiForMonitor)(
    _In_ HMONITOR hmonitor,
    _In_ MONITOR_DPI_TYPE dpiType,
    _Out_ UINT *dpiX,
    _Out_ UINT *dpiY
    );

typedef HRESULT(STDAPICALLTYPE* PFNDwmIsCompositionEnabled)(
    BOOL *pfEnabled
    );

typedef HRESULT(STDAPICALLTYPE* PFNDwmGetWindowAttribute)(
    HWND hwnd,
    DWORD dwAttribute,
    _Out_writes_bytes_(cbAttribute) PVOID pvAttribute,
    DWORD cbAttribute
    );

typedef HRESULT(STDAPICALLTYPE* PFNDwmSetWindowAttribute)(
    HWND hwnd,
    DWORD dwAttribute,
    _In_reads_bytes_(cbAttribute) LPCVOID pvAttribute,
    DWORD cbAttribute
    );

typedef BOOL(WINAPI* PFNGetWindowDisplayAffinity)(
    HWND hWnd,
    DWORD* pdwAffinity
    );

typedef BOOL(WINAPI* PFNSetWindowDisplayAffinity)(
    HWND hWnd,
    DWORD dwAffinity
    );

typedef HRESULT(STDAPICALLTYPE* PFNSetWindowTheme)(
    _In_ HWND hwnd,
    _In_opt_ LPCWSTR pszSubAppName,
    _In_opt_ LPCWSTR pszSubIdList
    );

typedef NTSTATUS(NTAPI* PFNLdrLoadDll)(
    IN PWSTR SearchPath OPTIONAL,
    IN PULONG DllCharacteristics OPTIONAL,
    IN PUNICODE_STRING DllName,
    OUT PVOID* BaseAddress
    );

typedef NTSTATUS(NTAPI* PFNLdrGetProcedureAddress)(
    IN PVOID BaseAddress,
    IN PANSI_STRING Name,
    IN ULONG Ordinal,
    OUT PVOID* ProcedureAddress
    );