#pragma once

#include "AlleyWind.Core.inl"

#include "Resource/ResMgr.h"
#include "Util/StringFormat.h"
#include "Util/WinProp.h"
#include "Database/Database.h"
#include "UI/UI.h"

#pragma comment (lib, "Comctl32.lib")

#define KNSOFT_APP_NAME L"AlleyWind"

#define CMDLINE_SWITCH_TRYELEVATEUIACCESS L"-TryElevateUIAccess"

EXTERN_C_START

extern HWND g_hMainDlg;
extern LOGICAL g_IsRunAsAdmin;
extern LOGICAL g_HasUIAccess;

EXTERN_C_END
