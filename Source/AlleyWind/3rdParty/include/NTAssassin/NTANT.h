// Native library of NTAssassin provides interfaces to access down-level x86/x64 CPU and Windows NT in R3.

#pragma once

#include "NTADef.h"

/// <summary>
/// Gets member value of current TEB
/// </summary>
/// <param name="m">Member of TEB to acquire</param>
/// <returns>The value of member in QWORD(x64 only)/DWORD/WORD/BYTE</returns>
#if defined(_M_X64)
#define NT_GetTEBMember(m) ((RTL_FIELD_SIZE(TEB, m) == sizeof(DWORD64) ? __readgsqword(FIELD_OFFSET(TEB, m)) : (RTL_FIELD_SIZE(TEB, m) == sizeof(DWORD) ? __readgsdword(FIELD_OFFSET(TEB, m)) : (RTL_FIELD_SIZE(TEB, m) == sizeof(WORD) ? __readgsword(FIELD_OFFSET(TEB, m)) : __readgsbyte(FIELD_OFFSET(TEB, m))))))
#define NT_GetTEBMemberQWORD(m) __readgsqword(FIELD_OFFSET(TEB, m))
#define NT_GetTEBMemberDWORD(m) __readgsdword(FIELD_OFFSET(TEB, m))
#define NT_GetTEBMemberWORD(m) __readgsword(FIELD_OFFSET(TEB, m))
#define NT_GetTEBMemberBYTE(m) __readgsbyte(FIELD_OFFSET(TEB, m))
#elif defined(_M_IX86)
#define NT_GetTEBMember(m) ((RTL_FIELD_SIZE(TEB, m) == sizeof(DWORD) ? __readfsdword(FIELD_OFFSET(TEB, m)) : (RTL_FIELD_SIZE(TEB, m) == sizeof(WORD) ? __readfsword(FIELD_OFFSET(TEB, m)) : __readfsbyte(FIELD_OFFSET(TEB, m)))))
#define NT_GetTEBMemberDWORD(m) __readfsdword(FIELD_OFFSET(TEB, m))
#define NT_GetTEBMemberWORD(m) __readfsword(FIELD_OFFSET(TEB, m))
#define NT_GetTEBMemberBYTE(m) __readfsbyte(FIELD_OFFSET(TEB, m))
#endif

/// <summary>
/// Sets member value of current TEB
/// </summary>
/// <param name="m">Member of TEB to set</param>
/// <param name="val">New value to set</param>
#if defined(_M_X64)
// NT_SetTEBMember may cause code analysis warning, use following NT_SetTEBMember[QWORD/DWORD/WORD/BYTE] instead
#define NT_SetTEBMember(m, val) ((RTL_FIELD_SIZE(TEB, m) == sizeof(DWORD64) ? __writegsqword(FIELD_OFFSET(TEB, m), val) : (RTL_FIELD_SIZE(TEB, m) == sizeof(DWORD) ? __writegsdword(FIELD_OFFSET(TEB, m), val) : (RTL_FIELD_SIZE(TEB, m) == sizeof(WORD) ? __writegsword(FIELD_OFFSET(TEB, m), val) : __writegsbyte(FIELD_OFFSET(TEB, m), val)))))
#define NT_SetTEBMemberQWORD(m, val) __writegsqword(FIELD_OFFSET(TEB, m), val)
#define NT_SetTEBMemberDWORD(m, val) __writegsdword(FIELD_OFFSET(TEB, m), val)
#define NT_SetTEBMemberWORD(m, val) __writegsword(FIELD_OFFSET(TEB, m), val)
#define NT_SetTEBMemberBYTE(m, val) __writegsbyte(FIELD_OFFSET(TEB, m), val)
#elif defined(_M_IX86)
#define NT_SetTEBMember(m, val) ((RTL_FIELD_SIZE(TEB, m) == sizeof(DWORD) ? __writefsdword(FIELD_OFFSET(TEB, m), val) : (RTL_FIELD_SIZE(TEB, m) == sizeof(WORD) ? __writefsword(FIELD_OFFSET(TEB, m), val) : __writefsbyte(FIELD_OFFSET(TEB, m), val))))
#define NT_SetTEBMemberDWORD(m, val) __writefsdword(FIELD_OFFSET(TEB, m), val)
#define NT_SetTEBMemberWORD(m, val) __writefsword(FIELD_OFFSET(TEB, m), val)
#define NT_SetTEBMemberBYTE(m, val) __writefsbyte(FIELD_OFFSET(TEB, m), val)
#endif

/// <summary>
/// Gets the pointer to TEB
/// </summary>
/// <returns>The the pointer to TEB</returns>
/// <remarks> To obtain or modify member value of TEB, use "NT_GetTEBMember" or "NT_SetTEBMember" instead</remarks>
#define NT_GetTEB() ((PTEB)NT_GetTEBMember(NtTib.Self))

/// <summary>
/// Gets the pointer to PEB
/// </summary>
/// <returns>The the pointer to PEB</returns>
#define NT_GetPEB() ((PPEB)NT_GetTEBMember(ProcessEnvironmentBlock))

/// <summary>
/// Gets the pointer to KUSER_SHARED_DATA
/// </summary>
#define NT_GetKUSD() ((CONST PKUSER_SHARED_DATA)MM_SHARED_USER_DATA_VA)

/// <summary>
/// Gets the Handle to the default heap
/// </summary>
#define NT_GetHeap() ((HANDLE)NT_GetPEB()->ProcessHeap)

/// <summary>
/// Gets instance handle of current executable module
/// </summary>
#define NT_GetImageBase() (NT_GetPEB()->ImageBaseAddress)

/// <summary>
/// Gets the handle to current directory
/// </summary>
#define NT_GetCurDirHandle() (NT_GetPEB()->ProcessParameters->CurrentDirectory.Handle)

/// <summary>
/// Gets or sets the last error
/// </summary>
#define NT_ClearLastError() NT_SetTEBMemberDWORD(LastErrorValue, ERROR_SUCCESS)
#define NT_GetLastError() NT_GetTEBMemberDWORD(LastErrorValue)
#define NT_SetLastError(dwError) NT_SetTEBMemberDWORD(LastErrorValue, dwError)
#define NT_LastErrorSucceed() (NT_GetTEBMemberDWORD(LastErrorValue) == ERROR_SUCCESS)

/// <summary>
/// Gets or sets the last status
/// </summary>
#define NT_ClearLastStatus() NT_SetTEBMemberDWORD(LastStatusValue, STATUS_SUCCESS)
#define NT_GetLastStatus() NT_GetTEBMemberDWORD(LastStatusValue)
#define NT_SetLastStatus(lStatus) NT_SetTEBMemberDWORD(LastStatusValue, lStatus)
#define NT_LastStatusSucceed() (NT_SUCCESS(NT_GetTEBMemberDWORD(LastStatusValue)))

/// <summary>
/// Gets handle to ntdll.dll, which the first initialized module
/// </summary>
#define NT_GetNtdllHandle() (CONTAINING_RECORD(NT_GetPEB()->Ldr->InInitializationOrderModuleList.Flink, LDR_DATA_TABLE_ENTRY, InInitializationOrderModuleList)->DllBase)

/// <summary>
/// Sets last win32 error according to given NT Status
/// </summary>
/// <param name="Status">NT Status</param>
/// <returns>Win32 Error code corresponding to the given NT Status</returns>
NTA_API DWORD NTAPI NT_SetLastNTError(NTSTATUS Status);

/// <summary>
/// Initializes OBJECT_ATTRIBUTES structure
/// </summary>
NTA_API VOID NTAPI NT_InitObject(_Out_ POBJECT_ATTRIBUTES Object, HANDLE RootDirectory, PUNICODE_STRING ObjectName, ULONG Attributes);

/// <summary>
/// Initializes OBJECT_ATTRIBUTES structure for a path
/// </summary>
/// <returns>TRUE if succeeded, or FALSE if failed, no error code reports</returns>
/// <remarks>ObjectName.Buffer should be freed by <c>Mem_HeapFree</c> when no longer needs</remarks>
NTA_API BOOL NTAPI NT_InitPathObject(POBJECT_ATTRIBUTES Object, _In_z_ PCWSTR Path, HANDLE RootDirectory, PUNICODE_STRING ObjectName);
