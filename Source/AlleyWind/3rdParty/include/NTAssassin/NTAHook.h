#pragma once

#include "NTAssassin.h"

NTA_API BOOL NTAPI Hook_Begin();
NTA_API BOOL NTAPI Hook_Set(BOOL Enable, PVOID* Address, PVOID HookAddress);
NTA_API BOOL NTAPI Hook_Attach(PVOID* Address, PVOID HookAddress);
NTA_API BOOL NTAPI Hook_Detach(PVOID* Address, PVOID HookAddress);
NTA_API BOOL NTAPI Hook_Commit();