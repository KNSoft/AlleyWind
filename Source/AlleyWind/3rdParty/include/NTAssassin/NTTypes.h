#pragma once

#include "NTADef.h"

typedef DWORD64 QWORD, *PQWORD, *LPQWORD;
typedef SID* PSID;

typedef BOOL(WINAPI* PFNCreateProcessInternalW)(
    _In_opt_ HANDLE hToken,
    _In_opt_ LPCWSTR lpApplicationName,
    _Inout_opt_ LPWSTR lpCommandLine,
    _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
    _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
    _In_ BOOL bInheritHandles,
    _In_ DWORD dwCreationFlags,
    _In_opt_ LPVOID lpEnvironment,
    _In_opt_ LPCWSTR lpCurrentDirectory,
    _In_ LPSTARTUPINFOW lpStartupInfo,
    _Out_ LPPROCESS_INFORMATION lpProcessInformation,
    _Out_opt_ PHANDLE hNewToken
);

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
