#pragma once

#include "AlleyWind.Core.inl"

#include "Resource/ResMgr.h"
#include "Util/StringFormat.h"
#include "Database/Database.h"
#include "Util/Init.h"
#include "Util/VirtDesk.h"
#include "Util/WinProp.h"
#include "UI/UI.h"

#pragma comment (lib, "Comctl32.lib")

#define KNSOFT_APP_NAME L"AlleyWind"

#define CMDLINE_SWITCH_TRYELEVATEUIACCESS L"-TryElevateUIAccess"

EXTERN_C_START

extern LOGICAL g_IsRunAsAdmin;
extern LOGICAL g_HasUIAccess;

EXTERN_C_END
