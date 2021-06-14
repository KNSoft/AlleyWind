// Remote Process accessibility

#pragma once

#include "NTAssassin\NTAssassin.h"

typedef struct _RPROC_MAP {
    PVOID   Local;
    SIZE_T  LocalSize;
    PVOID   Remote;
    SIZE_T  RemoteSize;
    ULONG   RemotePageProtect;
} RPROC_MAP, * PRPROC_MAP;

/**
  * @brief Callback procedure to enumerate DLL modules loaded on remote process
  * @param[in] ProcessHandle Handle to the remote process
  * @param[in] DllLdrEntry Pointer to LDR_DATA_TABLE_ENTRY of each DLL modules
  * @param[in] Param User defined value passed to the callback
  * @return Returns FALSE to stop the enumeration, or TRUE to continue
  */
typedef BOOL(CALLBACK* RPROC_DLLENUMPROC)(HANDLE ProcessHandle, PLDR_DATA_TABLE_ENTRY DllLdrEntry, LPARAM Param);

/**
  * @brief Enumerates DLL modules of remote process
  * @param[in] ProcessHandle Handle to the remote process
  * @param[in] DllEnumProc Callback procedure to receive information of each DLL
  * @param[in] Param User defined value passed to the callback
  * @return Returns NTSTATUS
  */
NTA_API NTSTATUS NTAPI RProc_EnumDlls(HANDLE ProcessHandle, RPROC_DLLENUMPROC DllEnumProc, LPARAM Param);

/**
  * @see "ReadProcessMemory"
  */
#define RProc_MemReadEx(ProcessHandle, BaseAddress, Buffer, Size) NtReadVirtualMemory(ProcessHandle, BaseAddress, Buffer, Size, NULL)
#define RProc_MemRead(ProcessHandle, BaseAddress, Buffer) NtReadVirtualMemory(ProcessHandle, BaseAddress, Buffer, sizeof(*(BaseAddress)), NULL)

/**
  * @see "WriteProcessMemory"
  */
#define RProc_MemWriteEx(ProcessHandle, BaseAddress, Buffer, Size) NtWriteVirtualMemory(ProcessHandle, BaseAddress, Buffer, Size, NULL)
#define RProc_MemWrite(ProcessHandle, BaseAddress, Buffer) NtWriteVirtualMemory(ProcessHandle, BaseAddress, Buffer, sizeof(*(BaseAddress)), NULL)

/**
  * @see "OpenProcess"
  */
NTA_API HANDLE NTAPI RProc_Open(DWORD DesiredAccess, DWORD ProcessId);

/**
  * @see "OpenThread"
  */
NTA_API HANDLE NTAPI RProc_OpenThread(DWORD DesiredAccess, DWORD ThreadId);

/**
  * @see "CreateRemoteThread"
  */
#define RProc_CreateThread(ProcessHandle, StartAddress, Parameter, CreateSuspended, ThreadHandle) RtlCreateUserThread(ProcessHandle, NULL, CreateSuspended, 0, 0, 0, StartAddress, Parameter, ThreadHandle, NULL)

/**
  * @brief Adjusts specified process privilege
  * @param[in] ProcessHandle Handle to the process
  * @param[in] Privilege Privilege to adjust, specify any of PROC_LM_SE_NAMES value
  * @param[in] EnableState Set to TRUE to enable specified privilege, or FALSE to disable
  * @return Returns NTSTATUS
  * @see "AdjustTokenPrivileges"
  */
NTA_API NTSTATUS NTAPI RProc_AdjustPrivilege(HANDLE ProcessHandle, PROC_LM_SE_NAMES Privilege, BOOL EnableState);

/**
  * @brief Gets Win32 format full path of specified process
  * @return Returns Number of characters written to the buffer, not including null-terminates, or 0 if failed
  * @see "GetProcessImageFileName" and "QueryFullProcessImageName"
  * @note PROCESS_QUERY_LIMITED_INFORMATION access privilege is required, in the systems earlier than NT6.0, this function reads path from remote memory, PROCESS_QUERY_INFORMATION and PROCESS_VM_READ access privileges are required
  */
NTA_API UINT NTAPI RProc_GetFullImageNameEx(HANDLE ProcessHandle, PWSTR FilePath, UINT FilePathCch);
#define RProc_GetFullImageName(ProcessHandle, FilePath) RProc_GetFullImageNameEx(ProcessHandle, FilePath, ARRAYSIZE(FilePath))

/**
  * @brief Translates address to format like "ModuleName!Address"
  * @param[in] ProcessHandle Handle to the process
  * @param[in] Address Address to be translated
  * @param[out] OutputString Pointer to the buffer to receive translated string
  * @param[in] OutputStringCch Size in characters of OutputString buffer
  * @return Returns Number of characters written to the buffer, not including null-terminates, or 0 if failed
  */
NTA_API UINT NTAPI RProc_TranslateAddressEx(HANDLE ProcessHandle, PVOID Address, PWSTR OutputString, UINT OutputStringCch);
#define RProc_TranslateAddress(ProcessHandle, Address, OutputString) RProc_TranslateAddressEx(ProcessHandle, Address, OutputString, ARRAYSIZE(OutputString))

/**
  * @brief Reads ANSI or Unicode string from remote memory
  * @param[in] ProcessHandle Handle to the process
  * @param[in] Address Address to the string
  * @param[out] OutputString Pointer to the buffer to receive string
  * @param[in] OutputStringCch Size in characters of OutputString buffer
  * @return Returns Number of characters written to the buffer, not including null-terminates, or 0 if failed
  */
NTA_API NTSTATUS NTAPI RProc_ReadMemStringExW(HANDLE ProcessHandle, PVOID Address, PWSTR OutputString, UINT OutputStringCch);
NTA_API NTSTATUS NTAPI RProc_ReadMemStringExA(HANDLE ProcessHandle, PVOID Address, PSTR OutputString, UINT OutputStringCch);
#define RProc_ReadMemStringW(ProcessHandle, Address, OutputString) RProc_ReadMemStringExW(ProcessHandle, Address, OutputString, ARRAYSIZE(OutputString))
#define RProc_ReadMemStringA(ProcessHandle, Address, OutputString) RProc_ReadMemStringExA(ProcessHandle, Address, OutputString, ARRAYSIZE(OutputString))

/**
  * @brief Initializes RPROC_MAP structure
  * @param[out] RemoteMemMap Pointer to the RPROC_MAP structure
  * @param[in] LocalAddress Address to the local memory address
  * @param[in] LocalSize Size of local memory
  * @param[in] RemotePageProtect Protection flags of mapped remote memory pages
  */
NTA_API VOID NTAPI RProc_InitMap(PRPROC_MAP RemoteMemMap, PVOID LocalAddress, SIZE_T LocalSize, ULONG RemotePageProtect);

/**
  * @brief Maps local memory to remote process
  * @param[in] ProcessHandle Handle to the process
  * @param[in] RemoteMemMap Pointer to the RPROC_MAP structure, which contains necessary information to setup map
  */
NTA_API NTSTATUS NTAPI RProc_MemMap(HANDLE ProcessHandle, PRPROC_MAP RemoteMemMap);

/**
  * @brief Frees memory on remote process mapped by "RProc_MemMap"
  * @param[in] ProcessHandle Handle to the process
  * @param[in] RemoteMemMap Pointer to the RPROC_MAP structure
  * @note This function frees memory only, will not write remote memory back to local
  */
#define RProc_MemUnmap(ProcessHandle, RemoteMemMap) NtFreeVirtualMemory(ProcessHandle, &(RemoteMemMap)->Remote, &(RemoteMemMap)->RemoteSize, MEM_DECOMMIT)