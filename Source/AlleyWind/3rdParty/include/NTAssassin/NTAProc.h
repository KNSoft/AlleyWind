// provides process functions for current process

#pragma once

#include "NTAssassin.h"

typedef enum _PROC_LM_SE_NAMES {
    LSE_CREATE_TOKEN_NAME = 2,
    LSE_ASSIGNPRIMARYTOKEN_NAME = 3,
    LSE_LOCK_MEMORY_NAME = 4,
    LSE_INCREASE_QUOTA_NAME = 5,
    LSE_UNSOLICITED_INPUT_NAME = 0,
    LSE_MACHINE_ACCOUNT_NAME = 6,
    LSE_TCB_NAME = 7,
    LSE_SECURITY_NAME = 8,
    LSE_TAKE_OWNERSHIP_NAME = 9,
    LSE_LOAD_DRIVER_NAME = 10,
    LSE_SYSTEM_PROFILE_NAME = 11,
    LSE_SYSTEMTIME_NAME = 12,
    LSE_PROF_SINGLE_PROCESS_NAME = 13,
    LSE_INC_BASE_PRIORITY_NAME = 14,
    LSE_CREATE_PAGEFILE_NAME = 15,
    LSE_CREATE_PERMANENT_NAME = 16,
    LSE_BACKUP_NAME = 17,
    LSE_RESTORE_NAME = 18,
    LSE_SHUTDOWN_NAME = 19,
    LSE_DEBUG_NAME = 20,
    LSE_AUDIT_NAME = 21,
    LSE_SYSTEM_ENVIRONMENT_NAME = 22,
    LSE_CHANGE_NOTIFY_NAME = 23,
    LSE_REMOTE_SHUTDOWN_NAME = 24,
    LSE_UNDOCK_NAME = 25,
    LSE_SYNC_AGENT_NAME = 26,
    LSE_ENABLE_DELEGATION_NAME = 27,
    LSE_MANAGE_VOLUME_NAME = 28,
    LSE_IMPERSONATE_NAME = 29,
    LSE_CREATE_GLOBAL_NAME = 30,
    LSE_TRUSTED_CREDMAN_ACCESS_NAME = 31,
    LSE_RELABEL_NAME = 32,
    LSE_INC_WORKING_SET_NAME = 34,
    LSE_TIME_ZONE_NAME = 35,
    LSE_CREATE_SYMBOLIC_LINK_NAME = 36,
    LSE_DELEGATE_SESSION_USER_IMPERSONATE_NAME = 37
} PROC_LM_SE_NAMES, * PPROC_LM_SE_NAMES;

/**
  * @brief Callback procedure to enumerate DLL modules
  * @param[in] DllLdrEntry Pointer to LDR_DATA_TABLE_ENTRY of each DLL modules
  * @param[in] Param User defined value passed to the callback
  * @return Returns FALSE to stop the enumeration, or TRUE to continue
  */
typedef BOOL(CALLBACK* PROC_DLLENUMPROC)(PLDR_DATA_TABLE_ENTRY DllLdrEntry, LPARAM Param);

/**
 * @brief Gets current process command line
 * @return Returns pointer to native command line string
 */
#define Proc_GetCommandLine() (NT_GetPEB()->ProcessParameters->CommandLine.Buffer)

/**
 * @brief Creates a new thread
 * @return Returns NTSTATUS
 */
#define Proc_CreateThread(StartAddress, Parameter, CreateSuspended, ThreadHandle) RtlCreateUserThread(CURRENT_PROCESS_HANDLE, NULL, CreateSuspended, 0, 0, 0, StartAddress, Parameter, ThreadHandle, NULL)

 /**
  * @brief Gets handle to ntdll.dll, which the first loaded module of executable image
  * @return Returns handle of ntdll.dll
  */
#define Proc_GetNtdllHandle() (CONTAINING_RECORD(NT_GetPEB()->Ldr->InInitializationOrderModuleList.Flink, LDR_DATA_TABLE_ENTRY, InInitializationOrderModuleList)->DllBase)

/**
  * @brief Enumerates DLL modules of current process
  * @param[in] DllEnumProc Callback procedure to receive information of each DLL
  * @param[in] Param User defined value passed to the callback
  * @return Returns pointer to LDR_DATA_TABLE_ENTRY structure of last enumerated DLL if the callback stops the enumeration, or NULL if enumeration finished successfully
  */
NTA_API PLDR_DATA_TABLE_ENTRY NTAPI Proc_EnumDlls(PROC_DLLENUMPROC DllEnumProc, LPARAM Param);

/**
  * @brief Gets DLL information with specified module name
  * @param[in] DllName Module name of DLL
  * @return Returns pointer to LDR_DATA_TABLE_ENTRY structure of specified DLL, or NULL if no DLL matched
  */
NTA_API PLDR_DATA_TABLE_ENTRY NTAPI Proc_GetDllByName(PWSTR DllName);

/**
  * @brief Gets handle to a DLL by module name
  * @param[in] DllName Module name of DLL
  * @return Returns handle to the DLL or NULL if failed
  */
NTA_API HMODULE NTAPI Proc_GetDllHandleByName(PWSTR DllName);

/**
  * @brief Gets handle to a DLL by address
  * @param[in] Address within the DLL
  * @return Returns pointer to LDR_DATA_TABLE_ENTRY structure of matched DLL, or NULL if no DLL matched
  */
NTA_API PLDR_DATA_TABLE_ENTRY NTAPI Proc_GetDllByAddr(PVOID Address);

/**
  * @brief Loads specified DLL
  * @param[in] LibName Name of DLL
  * @param[in] DontResolveRef Set to TRUE to don't resolve references
  * @return Returns handle to the DLL or NULL if failed
  */
NTA_API HMODULE NTAPI Proc_LoadDll(PWSTR LibName, BOOL DontResolveRef);

/**
  * @see "GetProcAddress"
  */
NTA_API PVOID NTAPI Proc_GetProcAddr(HMODULE Module, PSTR ProcName);

/**
  * @brief Loads procedure address of specified module, module will be loaded if not yet
  * @see "LoadLibrary" and "GetProcAddress"
  */
NTA_API PVOID NTAPI Proc_LoadProcAddr(PWSTR LibName, PSTR ProcName);

/**
  * @brief Adjusts current process privilege
  * @param[in] Privilege Privilege to adjust, specify any of PROC_LM_SE_NAMES value
  * @param[in] EnableState Set to TRUE to enable specified privilege, or FALSE to disable
  * @return Returns NTSTATUS
  * @see "AdjustTokenPrivileges"
  */
#define Proc_AdjustPrivilege(Privilege, EnableState) RProc_AdjustPrivilege(CURRENT_PROCESS_HANDLE, Privilege, EnableState)
#define Proc_EnablePrivilege(Privilege) Proc_AdjustPrivilege(Privilege, TRUE)
#define Proc_DisablePrivilege(Privilege) Proc_AdjustPrivilege(Privilege, FALSE)

/**
  * @brief Waits until the specified object is in the signaled state
  * @param[in] hObj Handle to the object to wait for
  * @param[in] dwMilliseconds The time-out interval, in milliseconds, or INFINITE for infinite waiting
  * @return Returns NTSTATUS
  * @see "WaitForSingleObject"
  */
NTA_API NTSTATUS NTAPI Proc_WaitForObject(HANDLE Object, DWORD Milliseconds);

/**
  * @see "Sleep"
  */
NTA_API NTSTATUS NTAPI Proc_DelayExec(DWORD Milliseconds);

/**
  * @see "GetExitCodeThread"
  */
NTA_API NTSTATUS NTAPI Proc_GetThreadExitCode(HANDLE ThreadHandle, PDWORD ExitCode);