#pragma once

#include "NTADef.h"
#include "NTANT.h"

typedef enum _SYS_DLL_NAME {
    SysDllNameNTDll = 0,
    SysDllNameKernel32,
    SysDllNameUser32,
    SysDllNameComDlg32,
    SysDllNameOle32,
    SysDllNameUxTheme,
    SysDllNameDwmapi,
    SysDllNameShcore,
    SysDllNameWs2_32,
    SysDllNameWinmm,
    SysDllNameMax
} SYS_DLL_NAME, * PSYS_DLL_NAME;

/// <summary>
/// Loads specified system DLL with cache
/// </summary>
/// <seealso cref="LoadLibrary"/>
/// <param name="SysDll">System DLL</param>
/// <returns>Handle to the DLL loaded, or NULL if failed</returns>
NTA_API HMODULE NTAPI Sys_LoadDll(SYS_DLL_NAME SysDll);

/// <summary>
/// Loads API from specified system DLL
/// </summary>
/// <seealso cref="GetProcAddress"/>
/// <param name="SysDll">System DLL</param>
/// <param name="APIName">API name</param>
/// <returns>Address of API, or NULL if failed</returns>
NTA_API PVOID NTAPI Sys_LoadAPI(SYS_DLL_NAME SysDll, _In_z_ PCSTR APIName);

/// <summary>
/// Gets Unicode message text in specified module by message ID
/// </summary>
/// <seealso cref="RtlFindMessage"/>
/// <param name="ModuleHandle">Handle to the module</param>
/// <param name="MessageId"></param>
/// <returns>Pointer to the message string, or NULL if failed</returns>
NTA_API PCWSTR NTAPI Sys_GetMessage(HMODULE ModuleHandle, DWORD MessageId);

/// <summary>
/// Gets Unicode message text of given Win32 error or HRESULT
/// </summary>
/// <param name="Error">Error code</param>
/// <returns>Pointer to the message string, or NULL if failed</returns>
NTA_API PCWSTR NTAPI Sys_GetErrorInfo(DWORD Error);

/// <summary>
/// Gets Unicode message text of given NT Status
/// </summary>
/// <param name="Status">NT Status</param>
/// <returns>Pointer to the message string, or NULL if failed</returns>
NTA_API PCWSTR NTAPI Sys_GetStatusInfo(NTSTATUS Status);

/// <summary>
/// Gets Unicode message text of Win32 error corresponding to given NT Status
/// </summary>
/// <param name="Status">NT Status</param>
/// <returns>Pointer to the message. If no Win32 error matched, returns message text of NT Status itself instead</returns>
NTA_API PCWSTR NTAPI Sys_GetStatusErrorInfo(NTSTATUS Status);

/// <summary>
/// Displays message box shows message text of given Win32 error or HRESULT
/// </summary>
/// <param name="Owner">Handle to the owner window</param>
/// <param name="Title">Title string of message box</param>
/// <param name="Error">Error code</param>
NTA_API VOID NTAPI Sys_ErrorMsgBox(HWND Owner, PCWSTR Title, DWORD Error);

/// <summary>
/// Displays message box shows message text of given NT Status
/// </summary>
/// <param name="Owner">Handle to the owner window</param>
/// <param name="Title">Title string of message box</param>
/// <param name="Status">NT Status</param>
NTA_API VOID NTAPI Sys_StatusMsgBox(HWND Owner, PCWSTR Title, NTSTATUS Status);

/// <seealso cref="Sys_GetErrorInfo"/>
#define Sys_GetLastErrorInfo() Sys_GetErrorInfo(NT_GetLastError())

/// <seealso cref="Sys_GetStatusInfo"/>
#define Sys_GetLastStatusInfo() Sys_GetStatusInfo(NT_GetLastStatus())

/// <seealso cref="Sys_ErrorMsgBox"/>
#define Sys_LastErrorMsgBox(Owner, Title) Sys_ErrorMsgBox(Owner, Title, NT_GetLastError())

/// <seealso cref="Sys_StatusMsgBox"/>
#define Sys_LastStatusMsgBox(Owner, Title) Sys_StatusMsgBox(Owner, Title, NT_GetLastStatus())

/// <summary>
/// Gets current system processes information
/// </summary>
/// <returns>Pointer to SYSTEM_PROCESS_INFORMATION buffer, should be freed by <c>Sys_FreeProcessInfo</c> when no longer needed</returns>
NTA_API PSYSTEM_PROCESS_INFORMATION NTAPI Sys_GetProcessInfo();

#define Sys_FreeProcessInfo(p) Mem_Free(p);

/// <seealso cref="IsProcessorFeaturePresent"/>
#define Sys_TestCPUFeature(Feature) ((Feature) < PROCESSOR_FEATURE_MAX ? (BOOL)NT_GetKUSD()->ProcessorFeatures[(Feature)] : FALSE)

/// <seealso cref="IsEqualGUID"/>
NTA_API BOOL NTAPI Sys_EqualGUID(REFGUID GUID1, REFGUID GUID2);

// Error code converts
NTA_API DWORD NTAPI Sys_HRESULTToWin32(HRESULT hr);
#define Sys_Win32ToHRESULT HRESULT_FROM_WIN32
#define Sys_StatusToWin32 RtlNtStatusToDosErrorNoTeb
#define Sys_StatusToHRESULT HRESULT_FROM_NT
