#pragma once

#include "AlleyWind.Core.inl"

#include "WindowUtil/WindowUtil.h"
#include "Database/Database.h"
#include "Resource/ResMgr.h"
#include "UI/UI.h"

#pragma comment (lib, "Comctl32.lib")

#define KNSOFT_APP_NAME L"AlleyWind"

#define CMDLINE_SWITCH_TRYELEVATEUIACCESS L"-TryElevateUIAccess"

#define MAX_WNDCAPTION_CCH 128

EXTERN_C_START

extern LOGICAL g_IsRunAsAdmin;
extern LOGICAL g_HasUIAccess;

EXTERN_C_END
