#pragma once

#include "../AlleyWind.Core.inl"

EXTERN_C_START

VOID
AW_InitClassDatabase(VOID);

_Ret_maybenull_
PCWSTR
AW_GetSysClassDisplayName(
    _In_ PCWSTR ClassName);

EXTERN_C_END
