// provides process functions for current process

#pragma once

#include "NTADef.h"
#include "NTARProc.h"

/// <summary>
/// Callback procedure to enumerate DLL modules
/// </summary>
/// <param name="DllLdrEntry">Pointer to a LDR_DATA_TABLE_ENTRY structure represents each DLL</param>
/// <param name="Param">User defined value passed to this callback</param>
/// <returns>TRUE if continue enumeration, or FALSE to stop</returns>
typedef BOOL(CALLBACK* PROC_DLLENUMPROC)(_In_ PLDR_DATA_TABLE_ENTRY DllLdrEntry, LPARAM Param);

/// <summary>
/// Enumerates DLL modules of current process
/// </summary>
/// <param name="DllEnumProc">Callback procedure to receive information of each DLL</param>
/// <param name="Param">User defined value passed to the callback</param>
/// <returns>NULL if enumeration finished successfully, or a pointer to LDR_DATA_TABLE_ENTRY structure represents the last enumerated DLL and the callback stops enumeration</returns>
NTA_API PLDR_DATA_TABLE_ENTRY NTAPI Proc_EnumDlls(_In_ PROC_DLLENUMPROC DllEnumProc, LPARAM Param);

/// <summary>
/// Gets DLL information according to name
/// </summary>
/// <param name="DllName">Module name of DLL</param>
/// <returns>Pointer to a LDR_DATA_TABLE_ENTRY structure represents DLL matched, or NULL if no DLL matched</returns>
NTA_API PLDR_DATA_TABLE_ENTRY NTAPI Proc_GetDllByName(_In_z_ PCWSTR DllName);

/// <summary>
/// Gets DLL information according to handle
/// </summary>
/// <param name="DllHandle">Handle to the DLL</param>
/// <returns>Pointer to a LDR_DATA_TABLE_ENTRY structure represents DLL matched, or NULL if no DLL matched</returns>
NTA_API PLDR_DATA_TABLE_ENTRY NTAPI Proc_GetDllByHandle(_In_ HMODULE DllHandle);

/// <summary>
/// Gets handle to the DLL according to address
/// </summary>
/// <param name="Address">Any address within the DLL</param>
/// <returns>Pointer to a LDR_DATA_TABLE_ENTRY structure represents DLL matched, or NULL if no DLL matched</returns>
NTA_API PLDR_DATA_TABLE_ENTRY NTAPI Proc_GetDllByAddr(_In_ PVOID Address);

/// <summary>
/// Gets handle to the DLL according to name
/// </summary>
/// <param name="DllName">Module name of DLL</param>
/// <returns>Handle to the DLL that matched, or NULL if no DLL matched</returns>
NTA_API HMODULE NTAPI Proc_GetDllHandleByName(_In_z_ PCWSTR DllName);

/// <summary>
/// Gets current process command line
/// </summary>
/// <seealso cref="GetCommandLineW"/>
#define Proc_GetCommandLine() (NT_GetPEB()->ProcessParameters->CommandLine.Buffer)

/// <summary>
/// Creates a new thread
/// </summary>
/// <seealso cref="RtlCreateUserThread"/>
#define Proc_CreateThread(StartAddress, Parameter, CreateSuspended, ThreadHandle) RProc_CreateThread(CURRENT_PROCESS_HANDLE, StartAddress, Parameter, CreateSuspended, ThreadHandle)

/// <summary>
/// Loads specified DLL
/// </summary>
/// <seealso cref="LoadLibrary"/>
/// <param name="LibName">Name of DLL</param>
/// <param name="DontResolveRef">Set to TRUE to don't resolve references</param>
/// <returns>Handle to the DLL or NULL if failed</returns>
NTA_API HMODULE NTAPI Proc_LoadDll(_In_z_ PCWSTR LibName, BOOL DontResolveRef);

/// <seealso cref="GetProcAddress"/>
NTA_API PVOID NTAPI Proc_GetProcAddr(_In_ HMODULE Module, _In_z_ PCSTR ProcName);

/// <summary>
/// Loads procedure address of specified module, module will be loaded if not loaded yet
/// </summary>
/// <seealso cref="LoadLibrary"/>
/// <seealso cref="GetProcAddress"/>
/// <param name="LibName">Name of DLL</param>
/// <param name="ProcName">Name of procedure</param>
NTA_API PVOID NTAPI Proc_LoadProcAddr(_In_z_ PCWSTR LibName, _In_z_ PCSTR ProcName);

/// <summary>
/// Adjusts current process privilege
/// </summary>
/// <seealso cref="AdjustTokenPrivileges"/>
/// <seealso cref="RProc_AdjustPrivilege"/>
#define Proc_AdjustPrivilege(Privilege, EnableState) RProc_AdjustPrivilege(CURRENT_PROCESS_HANDLE, Privilege, EnableState)
#define Proc_EnablePrivilege(Privilege) Proc_AdjustPrivilege(Privilege, TRUE)
#define Proc_DisablePrivilege(Privilege) Proc_AdjustPrivilege(Privilege, FALSE)

/// <seealso cref="NtWaitForSingleObject"/>
NTA_API NTSTATUS NTAPI Proc_WaitForObject(HANDLE Object, DWORD Milliseconds);

/// <seealso cref="Sleep"/>
NTA_API VOID NTAPI Proc_DelayExec(DWORD Milliseconds);

/// <seealso cref="GetExitCodeThread"/>
_Success_(return != FALSE) NTA_API BOOL NTAPI Proc_GetThreadExitCode(HANDLE ThreadHandle, _Out_ PDWORD ExitCode);

/// <seealso cref="IsWow64Process"/>
#define Proc_IsWow64(Wow64Process) RProc_IsWow64(CURRENT_PROCESS_HANDLE, Wow64Process)
