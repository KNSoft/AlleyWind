// Remote Process accessibility

#pragma once

#include "NTAssassin.h"

typedef struct _RPROC_MAP {
    PVOID   Local;
    SIZE_T  LocalSize;
    PVOID   Remote;
    SIZE_T  RemoteSize;
    ULONG   RemotePageProtect;
} RPROC_MAP, * PRPROC_MAP;

#define RProc_MemReadEx(hProc, BaseAddress, lpBuffer, nBytes) NtReadVirtualMemory(hProc, BaseAddress, lpBuffer, nBytes, NULL)
#define RProc_MemRead(hProc, BaseAddress, lpBuffer) NtReadVirtualMemory(hProc, BaseAddress, lpBuffer, sizeof(*(BaseAddress)), NULL)
#define RProc_MemWriteEx(hProc, BaseAddress, lpBuffer, nBytes) NtWriteVirtualMemory(hProc, BaseAddress, lpBuffer, nBytes, NULL)
#define RProc_MemWrite(hProc, BaseAddress, lpBuffer) NtWriteVirtualMemory(hProc, BaseAddress, lpBuffer, sizeof(*(BaseAddress)), NULL)

NTA_API UINT NTAPI RProc_GetFullImageNameW(HANDLE hProc, LPWSTR pszFileName, UINT cchFileNameMax);
#ifdef UNICODE
#define RProc_GetFullImageName RProc_GetFullImageNameW
#else
#define RProc_GetFullImageName RProc_GetFullImageNameA
#endif

NTA_API HANDLE NTAPI RProc_Open(DWORD dwDesiredAccess, DWORD dwProcessId);
NTA_API HANDLE NTAPI RProc_OpenThread(DWORD dwDesiredAccess, DWORD dwThreadId);
#define RProc_CreateThread(hProc, lpStartAddress, Parameter, bCreateSuspended, lphThread) RtlCreateUserThread(hProc, NULL, bCreateSuspended, 0, 0, 0, lpStartAddress, Parameter, lphThread, NULL)

NTA_API NTSTATUS NTAPI RProc_AdjustPrivilege(HANDLE hProc, PROC_LM_SE_NAMES Privilege, BOOL bEnable);

NTA_API UINT NTAPI RProc_TranslateAddressW(HANDLE hProc, PVOID lpAddr, LPWSTR lpStr, UINT cChStr);
#ifdef UNICODE
#define RProc_TranslateAddress RProc_TranslateAddressW
#else
#define RProc_TranslateAddress RProc_TranslateAddressA
#endif

NTA_API NTSTATUS NTAPI RProc_ReadMemStringW(HANDLE hProc, LPVOID Address, LPWSTR lpszDest, UINT cchDest);
NTA_API NTSTATUS NTAPI RProc_ReadMemStringA(HANDLE hProc, LPVOID Address, LPSTR lpszDest, UINT cchDest);
#ifdef UNICODE
#define RProc_ReadMemString RProc_ReadMemStringW
#else
#define RProc_ReadMemString RProc_ReadMemStringA
#endif

NTA_API VOID NTAPI RProc_InitMap(PRPROC_MAP lpstMap, PVOID Local, SIZE_T  LocalSize, ULONG RemotePageProtect);
NTA_API NTSTATUS NTAPI RProc_MemMap(HANDLE hProc, PRPROC_MAP lpstMap);
#define RProc_MemUnmap(hProc, lpstMap) NtFreeVirtualMemory(hProc, &(lpstMap)->Remote, &(lpstMap)->RemoteSize, MEM_DECOMMIT)