#pragma once

#include "NTAssassin.h"

typedef enum _SYS_DLL_NAME {
    SysDllNameNTDll = 0,
    SysDllNameKernel32,
    SysDllNameUser32,
    SysDllNameUxTheme,
    SysDllNameDwmapi,
    SysDllNameShcore,
    SysDllNameMax
} SYS_DLL_NAME, * PSYS_DLL_NAME;

/**
  * @brief Loads specified system DLL with cache
  * @param[in] SysDll System DLL
  * @return Returns Handle to the DLL loaded, or NULL if failed
  * @see "LoadLibrary"
  */
NTA_API HMODULE NTAPI Sys_LoadDll(SYS_DLL_NAME SysDll);

/**
  * @brief Loads API from specified system DLL
  * @param[in] SysDll System DLL
  * @param[in] APIName API name
  * @return Returns address of API, or NULL if failed
  * @see "GetProcAddress"
  */
NTA_API PVOID NTAPI Sys_LoadAPI(SYS_DLL_NAME SysDll, PSTR APIName);

/**
  * @brief Gets Unicode message text in specified module by message ID
  * @param[in] ModuleHandle Handle to the module
  * @param[in] MessageId ID of message
  * @return Returns Pointer to the message, or NULL if failed
  * @see "RtlFindMessage"
  */
NTA_API PCWSTR NTAPI Sys_GetMessage(HMODULE ModuleHandle, DWORD MessageId);

/**
  * @brief Gets Unicode message text of given Win32 error or HRESULT
  * @param[in] Error Error code
  * @return Returns Pointer to the message, or NULL if failed
  */
NTA_API PCWSTR NTAPI Sys_GetErrorInfo(DWORD Error);

/**
  * @brief Gets Unicode message text of given NT Status
  * @param[in] Status NT Status
  * @return Returns Pointer to the message, or NULL if failed
  */
NTA_API PCWSTR NTAPI Sys_GetStatusInfo(NTSTATUS Status);

/**
  * @brief Gets Unicode message text of Win32 error corresponding to given NT Status
  * @param[in] Status NT Status
  * @return Returns Pointer to the message. If no Win32 error matched, returns message text of NT Status itself instead
  */
NTA_API PCWSTR NTAPI Sys_GetStatusErrorInfo(NTSTATUS Status);

/**
  * @brief Displays message box shows message text of given Win32 error or HRESULT
  * @param[in] Owner Handle to the owner window
  * @param[in] Title Title string of message box
  * @param[in] Error Error code
  */
NTA_API VOID NTAPI Sys_ErrorMsgBox(HWND Owner, PCWSTR Title, DWORD Error);

/**
  * @brief Displays message box shows message text of given NT Status
  * @param[in] Owner Handle to the owner window
  * @param[in] Title Title string of message box
  * @param[in] Status NT Status
  */
NTA_API VOID NTAPI Sys_StatusMsgBox(HWND Owner, PCWSTR Title, NTSTATUS Status);

/**
  * @see "Sys_GetErrorInfo"
  */
#define Sys_GetLastErrorInfo() Sys_GetErrorInfo(NT_GetLastError())

/**
  * @see "Sys_GetStatusInfo"
  */
#define Sys_GetLastStatusInfo() Sys_GetStatusInfo(NT_GetLastStatus())

/**
  * @see "Sys_ErrorMsgBox"
  */
#define Sys_LastErrorMsgBox(Owner, Title) Sys_ErrorMsgBox(Owner, Title, NT_GetLastError())

/**
  * @see "Sys_StatusMsgBox"
  */
#define Sys_LastStatusMsgBox(Owner, Title) Sys_StatusMsgBox(Owner, Title, NT_GetLastStatus())

/**
  * @see "IsProcessorFeaturePresent"
  */
#define Sys_TestCPUFeature(Feature) ((Feature) < PROCESSOR_FEATURE_MAX ? (BOOL)NT_GetKUSD()->ProcessorFeatures[(Feature)] : FALSE)

/**
  * @see "IsEqualGUID"
  */
NTA_API BOOL Sys_EqualGUID(REFGUID GUID1, REFGUID GUID2);

/**
  * @brief Copies GUID
  */
NTA_API VOID Sys_CopyGUID(LPGUID Dest, REFGUID Src);

NTA_API BOOL NTAPI Sys_RegVolatileDriver(PCWSTR Name, PCWSTR ImagePath);