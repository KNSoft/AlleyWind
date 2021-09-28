// Native library of NTAssassin provides interfaces to access down-level x86/x64 CPU and Windows NT in R3.

#pragma once

#include "NTAssassin.h"

/**
  * @brief Gets any member of current TEB
  * @param[in] m Member of TEB to acquire
  * @return Returns the value of member in QWORD(x64 only)/DWORD/WORD/BYTE
  */
#if defined(_M_AMD64)
#define NT_GetTEBMember(m) ((RTL_FIELD_SIZE(TEB, m) == sizeof(DWORD64) ? __readgsqword(FIELD_OFFSET(TEB, m)) : (RTL_FIELD_SIZE(TEB, m) == sizeof(DWORD) ? __readgsdword(FIELD_OFFSET(TEB, m)) : (RTL_FIELD_SIZE(TEB, m) == sizeof(WORD) ? __readgsword(FIELD_OFFSET(TEB, m)) : __readgsbyte(FIELD_OFFSET(TEB, m))))))
#elif defined(_M_IX86)
#define NT_GetTEBMember(m) ((RTL_FIELD_SIZE(TEB, m) == sizeof(DWORD) ? __readfsdword(FIELD_OFFSET(TEB, m)) : (RTL_FIELD_SIZE(TEB, m) == sizeof(WORD) ? __readfsword(FIELD_OFFSET(TEB, m)) : __readfsbyte(FIELD_OFFSET(TEB, m)))))
#endif

/**
  * @brief Sets any member of current TEB
  * @param[in] m Member of TEB to acquire
  * @param[in] val New value to set
  * @return Returns the value of member in QWORD(x64 only)/DWORD/WORD/BYTE
  */
#if defined(_M_AMD64)
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

/**
  * @brief Gets the pointer to current TEB
  * @return Returns pointer to TEB
  * @note To obtain or modify member value of TEB, use "NT_GetTEBMember" or "NT_SetTEBMember" instead
  */
#define NT_GetTEB() ((PTEB)NT_GetTEBMember(NtTib.Self))

/**
  * @brief Gets the pointer to current PEB
  * @return Returns pointer to PEB
  */
#define NT_GetPEB() ((PPEB)NT_GetTEBMember(ProcessEnvironmentBlock))

/**
  * @brief Gets the pointer to current KUSER_SHARED_DATA
  * @return Returns pointer to KUSER_SHARED_DATA
  */
#define NT_GetKUSD() ((CONST PKUSER_SHARED_DATA)MM_SHARED_USER_DATA_VA)

// Last Win32 Error value
#define NT_ClearLastError() NT_SetTEBMember(LastErrorValue, ERROR_SUCCESS)
#define NT_GetLastError() NT_GetTEBMember(LastErrorValue)
#define NT_SetLastError(dwError) NT_SetTEBMemberDWORD(LastErrorValue, dwError)
#define NT_LastErrorSucceed() (NT_GetTEBMember(LastErrorValue) == ERROR_SUCCESS)

// Last NT Status value
#define NT_ClearLastStatus() NT_SetTEBMember(LastStatusValue, STATUS_SUCCESS)
#define NT_GetLastStatus() NT_GetTEBMember(LastStatusValue)
#define NT_SetLastStatus(lStatus) NT_SetTEBMemberDWORD(LastStatusValue, lStatus)
#define NT_LastStatusSucceed() (NT_GetTEBMember(LastStatusValue) == ERROR_SUCCESS)

/**
  * @brief Initializes OBJECT_ATTRIBUTES structure
  * @param[out] Object Pointer to OBJECT_ATTRIBUTES to be filled
  * @param[in] RootDirectory RootDirectory member of OBJECT_ATTRIBUTES
  * @param[in] ObjectName ObjectName member of OBJECT_ATTRIBUTES
  * @param[in] Attributes Attributes member of OBJECT_ATTRIBUTES
  */
NTA_API VOID NTAPI NT_InitObject(POBJECT_ATTRIBUTES Object, HANDLE RootDirectory, PUNICODE_STRING ObjectName, ULONG Attributes);

/**
  * @brief Initializes OBJECT_ATTRIBUTES structure of path
  * @param[in] Path Pointer to path string
  * @param[in] RootDirectory RootDirectory member of OBJECT_ATTRIBUTES
  * @param[out] Object Pointer to OBJECT_ATTRIBUTES to be filled
  * @param[out] ObjectName ObjectName member of OBJECT_ATTRIBUTES
  */
NTA_API NTSTATUS NTAPI NT_InitPathObject(PCWSTR Path, HANDLE RootDirectory, POBJECT_ATTRIBUTES Object, PUNICODE_STRING ObjectName);