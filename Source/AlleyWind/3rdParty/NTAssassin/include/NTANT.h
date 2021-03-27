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
#define NT_SetTEBMember(m, val) ((RTL_FIELD_SIZE(TEB, m) == sizeof(DWORD64) ? __writegsqword(FIELD_OFFSET(TEB, m), val) : (RTL_FIELD_SIZE(TEB, m) == sizeof(DWORD) ? __writegsdword(FIELD_OFFSET(TEB, m), val) : (RTL_FIELD_SIZE(TEB, m) == sizeof(WORD) ? __writegsword(FIELD_OFFSET(TEB, m), val) : __writegsbyte(FIELD_OFFSET(TEB, m), val)))))
#elif defined(_M_IX86)
#define NT_SetTEBMember(m, val) ((RTL_FIELD_SIZE(TEB, m) == sizeof(DWORD) ? __writefsdword(FIELD_OFFSET(TEB, m), val) : (RTL_FIELD_SIZE(TEB, m) == sizeof(WORD) ? __writefsword(FIELD_OFFSET(TEB, m), val) : __writefsbyte(FIELD_OFFSET(TEB, m), val))))
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
#define NT_GetKUSD() ((PKUSER_SHARED_DATA)MM_SHARED_USER_DATA_VA)

// Last error value
#define NT_LastErrorClear() NT_SetTEBMember(LastErrorValue, ERROR_SUCCESS)
#define NT_LastErrorGet() NT_GetTEBMember(LastErrorValue)
#define NT_LastErrorSet(dwError) NT_SetTEBMember(LastErrorValue, dwError)
#define NT_LastErrorSucceed() (NT_GetTEBMember(LastErrorValue) == ERROR_SUCCESS)

/**
  * @brief Initializes OBJECT_ATTRIBUTES structure
  * @param[in] lpstObject Pointer to OBJECT_ATTRIBUTES to be filled
  * @param[in] lpstObjectName ObjectName member to OBJECT_ATTRIBUTES
  * @param[in] hRootDirectory RootDirectory member to OBJECT_ATTRIBUTES
  * @param[in] ulAttributes Attributes member to OBJECT_ATTRIBUTES
  */
NTA_API VOID NTAPI NT_InitObjectW(POBJECT_ATTRIBUTES lpstObject, PUNICODE_STRING lpstObjectName, HANDLE hRootDirectory, ULONG ulAttributes);
#ifdef UNICODE
#define NT_InitObject NT_InitObjectW
#else
#define NT_InitObject NT_InitObjectA
#endif

/**
  * @brief Initializes OBJECT_ATTRIBUTES structure of path
  * @param[in] lpszPath Pointer to path string
  * @param[in] lpstObject Pointer to OBJECT_ATTRIBUTES to be filled
  * @param[in] lpstObjectName ObjectName member to OBJECT_ATTRIBUTES
  * @param[in] hRootDirectory RootDirectory member to OBJECT_ATTRIBUTES
  */
NTA_API NTSTATUS NTAPI NT_InitPathObject(LPWSTR lpszPath, POBJECT_ATTRIBUTES lpstObject, PUNICODE_STRING lpstObjectName, HANDLE hRootDirectory);

NTA_API int NT_SEH_NopHandler(LPEXCEPTION_POINTERS lpstExceptionInfo);