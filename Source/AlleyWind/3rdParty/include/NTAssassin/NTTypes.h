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
