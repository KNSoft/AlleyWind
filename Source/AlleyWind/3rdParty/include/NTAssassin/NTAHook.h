#pragma once

#include "NTAssassin.h"

#pragma region C-style wrappers of Microsoft Detours

NTA_API BOOL NTAPI Hook_Begin();
NTA_API BOOL NTAPI Hook_Set(BOOL Enable, PVOID* Address, PVOID HookAddress);
NTA_API BOOL NTAPI Hook_Attach(PVOID* Address, PVOID HookAddress);
NTA_API BOOL NTAPI Hook_Detach(PVOID* Address, PVOID HookAddress);
NTA_API BOOL NTAPI Hook_Commit();

#pragma endregion