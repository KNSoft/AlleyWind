// Remote Process accessibility

#pragma once

#include "NTADef.h"

typedef struct _RPROC_MAP {
    PVOID   Local;
    SIZE_T  LocalSize;
    PVOID   Remote;
    SIZE_T  RemoteSize;
    ULONG   RemotePageProtect;
} RPROC_MAP, *PRPROC_MAP;

/// <summary>
/// Callback procedure to enumerate DLL modules in remote process
/// </summary>
/// <param name="ProcessHandle">Handle to the remote process</param>
/// <param name="DllLdrEntry">Pointer to a LDR_DATA_TABLE_ENTRY structure represents each DLL</param>
/// <param name="Param">User defined value passed to this callback</param>
/// <returns>TRUE if continue enumeration, or FALSE to stop</returns>
typedef BOOL(CALLBACK* RPROC_DLLENUMPROC64)(_In_ HANDLE ProcessHandle, _In_ PLDR_DATA_TABLE_ENTRY64 DllLdrEntry, LPARAM Param);
typedef BOOL(CALLBACK* RPROC_DLLENUMPROC32)(_In_ HANDLE ProcessHandle, _In_ PLDR_DATA_TABLE_ENTRY32 DllLdrEntry, LPARAM Param);

/// <summary>
/// Enumerates DLL modules of remote process
/// </summary>
/// <param name="ProcessHandle">Handle to the remote process</param>
/// <param name="DllEnumProc">Callback procedure to receive information of each DLL</param>
/// <param name="Param">User defined value passed to the callback</param>
/// <returns>TRUE if succeeded, or FALSE if failed, error code storaged in last STATUS</returns>
NTA_API BOOL NTAPI RProc_EnumDlls64(_In_ HANDLE ProcessHandle, _In_ RPROC_DLLENUMPROC64 DllEnumProc, LPARAM Param);
NTA_API BOOL NTAPI RProc_EnumDlls32(_In_ HANDLE ProcessHandle, _In_ RPROC_DLLENUMPROC32 DllEnumProc, LPARAM Param);

/// <seealso cref="RtlCreateUserThread"/>
_Success_(return != FALSE) NTA_API BOOL NTAPI RProc_CreateThread(_In_ HANDLE ProcessHandle, _In_ LPTHREAD_START_ROUTINE StartAddress, _In_opt_ __drv_aliasesMem PVOID Param, BOOL CreateSuspended, _Out_opt_ PHANDLE ThreadHandle);


/// <seealso cref="ReadProcessMemory"/>
_Success_(return > 0) NTA_API SIZE_T NTAPI RProc_ReadMemory(_In_ HANDLE ProcessHandle, _In_ PVOID BaseAddress, _Out_writes_bytes_(Size) PVOID Buffer, _In_ SIZE_T Size);

/// <seealso cref="WriteProcessMemory"/>
_Success_(return > 0) NTA_API SIZE_T NTAPI RProc_WriteMemory(_In_ HANDLE ProcessHandle, _In_ PVOID BaseAddress, _In_reads_bytes_(Size) LPCVOID Buffer, _In_ SIZE_T Size);

/// <seealso cref="OpenProcess"/>
NTA_API HANDLE NTAPI RProc_Open(DWORD DesiredAccess, DWORD ProcessId);

/// <seealso cref="OpenThread"/>
NTA_API HANDLE NTAPI RProc_OpenThread(DWORD DesiredAccess, DWORD ThreadId);

/// <summary>
/// Adjusts specified process privilege
/// </summary>
/// <seealso cref="AdjustTokenPrivileges"/>
/// <param name="ProcessHandle">Handle to the process</param>
/// <param name="Privilege">Privilege value to adjust, SE_XXX_PRIVILEGE</param>
/// <param name="Attributes">Attribute of privilege, SE_PRIVILEGE_XXX, or 0 to disable the privilege</param>
/// <returns>TRUE if succeeded, or FALSE if failed, error code storaged in last STATUS</returns>
NTA_API BOOL NTAPI RProc_AdjustPrivilege(_In_ HANDLE ProcessHandle, _In_ SE_PRIVILEGE Privilege, _In_ DWORD Attributes);

/// <summary>
/// Gets Win32 format full path of specified process
/// </summary>
/// <param name="ProcessHandle">Handle to the process</param>
/// <param name="FilePath">Pointer to the buffer to receive path</param>
/// <param name="FilePathCch">The size of the FilePath buffer in WCHARs</param>
/// <returns>Number of characters written, NOT including null-terminates, or 0 if failed, error code storaged in last STATUS</returns>
/// <remarks>PROCESS_QUERY_LIMITED_INFORMATION or PROCESS_QUERY_INFORMATION access is required</remarks>
_Success_(return > 0) NTA_API UINT NTAPI RProc_GetFullImageNameEx(HANDLE ProcessHandle, _Out_writes_z_(FilePathCch) PWSTR FilePath, _In_ UINT FilePathCch);
#define RProc_GetFullImageName(ProcessHandle, FilePath) RProc_GetFullImageNameEx(ProcessHandle, FilePath, ARRAYSIZE(FilePath))

/// <summary>
/// Translates address in remote procecss to "ModuleName!Address" format
/// </summary>
/// <param name="ProcessHandle">Handle to the process</param>
/// <param name="Address">Address to translate</param>
/// <param name="OutputString">Pointer to the buffer to receive translated string</param>
/// <param name="OutputStringCch">The size of the FilePath buffer in WCHARs</param>
/// <returns>Number of characters written, NOT including null-terminates, or 0 if failed, error code storaged in last STATUS</returns>
_Success_(return > 0) NTA_API UINT NTAPI RProc_TranslateAddressEx(HANDLE ProcessHandle, _In_ ULONGLONG Address, _Out_writes_z_(OutputStringCch) PWSTR OutputString, _In_ UINT OutputStringCch);
#define RProc_TranslateAddress(ProcessHandle, Address, OutputString) RProc_TranslateAddressEx(ProcessHandle, Address, OutputString, ARRAYSIZE(OutputString))

/// <summary>
/// Reads ANSI or Unicode string from remote memory
/// </summary>
/// <param name="ProcessHandle">Handle to the process</param>
/// <param name="Address">Address to the string</param>
/// <param name="OutputString">Pointer to the buffer to receive string</param>
/// <param name="OutputStringCch">The size of the FilePath buffer in TCHARs</param>
/// <returns>Number of characters written, NOT including null-terminates, or 0 if failed, error code storaged in last STATUS</returns>
_Success_(return > 0) NTA_API UINT NTAPI RProc_ReadMemStringExW(HANDLE ProcessHandle, _In_ PVOID Address, _Out_writes_z_(OutputStringCch) PWSTR OutputString, _In_ UINT OutputStringCch);
_Success_(return > 0) NTA_API UINT NTAPI RProc_ReadMemStringExA(HANDLE ProcessHandle, _In_ PVOID Address, _Out_writes_z_(OutputStringCch) PSTR OutputString, _In_ UINT OutputStringCch);
#define RProc_ReadMemStringW(ProcessHandle, Address, OutputString) RProc_ReadMemStringExW(ProcessHandle, Address, OutputString, ARRAYSIZE(OutputString))
#define RProc_ReadMemStringA(ProcessHandle, Address, OutputString) RProc_ReadMemStringExA(ProcessHandle, Address, OutputString, ARRAYSIZE(OutputString))

/// <summary>
/// Initializes LocalAddress, LocalSize, RemotePageProtect RPROC_MAP structure
/// </summary>
/// <param name="RemoteMemMap">Pointer to the RPROC_MAP structure</param>
/// <param name="LocalAddress">Address to the local memory</param>
/// <param name="LocalSize">Size of local memory</param>
/// <param name="RemoteAddress">Address to the remote memory, or NULL lets the system determines where to allocate</param>
/// <param name="RemotePageProtect">Page protection flags of mapped remote memory pages</param>
NTA_API VOID NTAPI RProc_InitMap(_Out_ PRPROC_MAP RemoteMemMap, _In_ PVOID LocalAddress, _In_ SIZE_T LocalSize, _In_opt_ PVOID RemoteAddress, _In_ ULONG RemotePageProtect);

/// <summary>
/// Maps local memory to remote process
/// </summary>
/// <param name="ProcessHandle">Handle to the remote process</param>
/// <param name="RemoteMemMap">Pointer to the RPROC_MAP structure contains necessary information to setup map</param>
/// <returns>TRUE if succeeded, or FALSE if failed, error code storaged in last STATUS</returns>
/// <remarks>LocalAddress, LocalSize and RemotePageProtect should be specified in RemoteMemMap, or initialize by <c>RProc_InitMap</c></remarks>
_Success_(return != FALSE) NTA_API BOOL NTAPI RProc_MemMap(HANDLE ProcessHandle, _Inout_ PRPROC_MAP RemoteMemMap);

/// <summary>
/// Frees memory on remote process mapped by <c>RProc_MemMap</c>
/// </summary>
/// <param name="ProcessHandle">Handle to the remote process</param>
/// <param name="RemoteMemMap">Pointer to the RPROC_MAP structure</param>
/// <returns>TRUE if succeeded, or FALSE if failed, error code storaged in last STATUS</returns>
NTA_API BOOL NTAPI RProc_MemUnmap(HANDLE ProcessHandle, _In_ PRPROC_MAP RemoteMemMap);

_Success_(return != FALSE) NTA_API BOOL NTAPI RProc_GetWow64PEB(_In_ HANDLE hProcess, _Out_ PPEB32 * Wow64PEB);

/// <seealso cref="IsWow64Process"/>
_Success_(return != FALSE) NTA_API BOOL NTAPI RProc_IsWow64(_In_ HANDLE hProcess, _Out_ PBOOL Wow64Process);

/// <summary>
/// Creates a new process
/// </summary>
/// <seealso cref="CreateProcessAsUser"/>
HANDLE NTAPI RProc_Create(_In_opt_ HANDLE TokenHandle, _In_opt_ LPCWSTR ApplicationName, _Inout_opt_ LPWSTR CommandLine, _In_ BOOL InheritHandles);
