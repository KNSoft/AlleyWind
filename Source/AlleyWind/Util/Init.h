#pragma once

#include "../AlleyWind.Core.inl"

EXTERN_C_START

EXTERN_C IApplicationViewCollection* g_Util_piAVC;
EXTERN_C IVirtualDesktopManager* g_Util_piVDM;
EXTERN_C IVirtualDesktopManagerInternal* g_Util_piVDMI_26100;

EXTERN_C LPIID g_Util_piidAVC;
EXTERN_C LPIID g_Util_piidVDMI;

VOID
AW_InitUtil(VOID);

VOID
AW_UninitUtil(VOID);

EXTERN_C_END
