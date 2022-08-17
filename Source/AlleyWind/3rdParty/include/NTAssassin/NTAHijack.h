#pragma once

#include "NTADef.h"

#define HIJACK_PROCESS_ACCESS (PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE | SYNCHRONIZE)

#pragma pack(push)
#pragma pack(4)
typedef struct _HIJACK_CALLPROCHEADER {
    PVOID64     Procedure;
    CALLCONV    CallConvention;
    QWORD       RetValue;
    DWORD       LastError;
    NTSTATUS    LastStatus;
    DWORD       ExceptionCode;
    UINT        ParamCount; // PHIJACK_CALLPROCPARAM
} HIJACK_CALLPROCHEADER, *PHIJACK_CALLPROCHEADER;

typedef struct _HIJACK_CALLPROCPARAM {
    union {
        QWORD   Value;
        PVOID64 Address;
        FLOAT   FloatNum;
    };
    QWORD   Size;       // 0 = Imm, -1 = Float for x64, >0 = Size of buffer
    BOOL    Out;
} HIJACK_CALLPROCPARAM, *PHIJACK_CALLPROCPARAM;
#pragma pack(pop)

/// <summary>
/// Injects shellcode and starts new thread to execute in remote process
/// </summary>
/// <param name="ProcessHandle">Handle to the process</param>
/// <param name="ShellCode">Pointer to the shellcode</param>
/// <param name="ShellCodeSize">Size of shellcode in bytes</param>
/// <param name="Param">User defined parameter passed to the remote thread</param>
/// <param name="ParamSize">Size of Param in bytes</param>
/// <param name="ExitCode">Pointer to variable to receive remote thread exit code</param>
/// <param name="Timeout">Timeout in milliseconds</param>
/// <returns>TRUE if succeeded, or FALSE if failed, error code storaged in last STATUS</returns>
/// <remarks>
/// HIJACK_PROCESS_ACCESS access is required
/// if Timeout is 0, ExitCode always returns STILL_ACTIVE
/// </remarks>
_Success_(return != FALSE) NTA_API BOOL NTAPI Hijack_ExecShellcode(_In_ HANDLE ProcessHandle, _In_reads_bytes_(ShellCodeSize) PVOID ShellCode, SIZE_T ShellCodeSize, _In_reads_bytes_opt_(ParamSize) PVOID Param, SIZE_T ParamSize, _Out_opt_ PDWORD ExitCode, DWORD Timeout);

/// <summary>
/// Gets procedure address in remote process space, if specified library not loaded in remote process, will be load
/// </summary>
/// <param name="ProcessHandle">Handle to the process</param>
/// <param name="LibName">Library name</param>
/// <param name="ProcName">Procedure name, can be NULL if loads library only</param>
/// <param name="ProcAddr">Pointer to a pointer variable to receive remote procedure address, can be NULL only if ProcName also is NULL</param>
/// <param name="Timeout">Timeout in milliseconds</param>
/// <returns>TRUE if succeeded, or FALSE if failed, error code storaged in last STATUS</returns>
/// <remarks>HIJACK_PROCESS_ACCESS access is required</remarks>
NTA_API BOOL NTAPI Hijack_LoadProcAddr(_In_ HANDLE ProcessHandle, _In_z_ PCWSTR LibName, _In_opt_z_ PCSTR ProcName, _When_(ProcName != NULL, _Notnull_) PVOID64* ProcAddr, DWORD Timeout);

/// <summary>
/// Starts a thread and calls a procedure in remote process
/// </summary>
/// <param name="ProcessHandle">Handle to the process</param>
/// <param name="CallProcHeader">Pointer to a HIJACK_CALLPROCHEADER structure contains procedure information and receives return values</param>
/// <param name="Params">Pointer to a HIJACK_CALLPROCPARAM array, corresponding to each parameters of procedure to call</param>
/// <param name="Timeout">Timeout in milliseconds</param>
/// <returns>TRUE if succeeded, or FALSE if failed, error code storaged in last STATUS</returns>
/// <remarks>HIJACK_PROCESS_ACCESS access is required</remarks>
NTA_API BOOL NTAPI Hijack_CallProc(_In_ HANDLE ProcessHandle, _Inout_ PHIJACK_CALLPROCHEADER CallProcHeader, _In_opt_ PHIJACK_CALLPROCPARAM Params, DWORD Timeout);
