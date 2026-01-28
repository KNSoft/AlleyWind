#pragma once

#include "../AlleyWind.Core.inl"

EXTERN_C_START

typedef struct _AW_SYSCLASS_INFO
{
    CONST PCWSTR ClassName;
    PCWSTR DisplayName;
    PUI_VALUEEDITOR_CONSTANT StyleConsts;
    CONST ULONG StyleConstsCount;
} AW_SYSCLASS_INFO, * PAW_SYSCLASS_INFO;

VOID
AW_InitClassDatabase(VOID);

_Ret_maybenull_
PAW_SYSCLASS_INFO
AW_GetSysClass(
    _In_ PCWSTR ClassName);

typedef enum _AW_STYLE_VALUE_TYPE {
    AW_StyleType_Style,
    AW_StyleType_ExStyle,
    AW_StyleType_ClassStyle
} AW_STYLE_VALUE_TYPE, *PAW_STYLE_VALUE_TYPE;

HRESULT
AW_GetStyleValueConstants(
    _In_opt_ PAW_SYSCLASS_INFO SysClassInfo,
    _In_ AW_STYLE_VALUE_TYPE StyleType,
    _In_ LOGICAL IsChild,
    _Out_ PUI_VALUEEDITOR_CONSTANT* Consts,
    _Out_ PULONG ConstsCount);

FORCEINLINE
AW_ReleaseStyleValueConstants(
    _In_ AW_STYLE_VALUE_TYPE StyleType,
    _In_ PUI_VALUEEDITOR_CONSTANT Consts)
{
    if (StyleType == AW_StyleType_Style)
    {
        Mem_Free(Consts);
    }
}

EXTERN_C_END
