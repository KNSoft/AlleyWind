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

/// <seealso cref="IsEqualGUID"/>
NTA_API BOOL NTAPI Sys_EqualGUID(REFGUID GUID1, REFGUID GUID2);
