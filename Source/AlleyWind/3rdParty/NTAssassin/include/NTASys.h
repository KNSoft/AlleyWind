#pragma once

#include "NTAssassin.h"

NTA_API LPCWSTR NTAPI Sys_GetMessageW(HMODULE hDll, DWORD dwMessageId, LCID dwLangId);
NTA_API LPCWSTR NTAPI Sys_GetErrorInfo(DWORD dwWin32Error, LCID dwLangId);
NTA_API LPCWSTR NTAPI Sys_GetStatusInfo(NTSTATUS lStatus, LCID dwLangId);