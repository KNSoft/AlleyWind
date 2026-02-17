#pragma once

#include "../AlleyWind.Core.inl"

typedef struct _AW_VIRTDESK_INFO
{
    ULONG Index;
    HRESULT hrId;
    GUID Id;
    HRESULT hrName;
    HSTRING Name;
} AW_VIRTDESK_INFO, *PAW_VIRTDESK_INFO;

/* Return FALSE to stop enumeration */
typedef
_Function_class_(AW_VIRTDESK_ENUM_PROC)
__callback
LOGICAL
CALLBACK
AW_VIRTDESK_ENUM_PROC(
    _In_ PAW_VIRTDESK_INFO DeskInfo,
    _In_opt_ PVOID Context);
typedef AW_VIRTDESK_ENUM_PROC *PAW_VIRTDESK_ENUM_PROC;

HRESULT
AW_EnumVirtualDesktops(
    _In_ PAW_VIRTDESK_ENUM_PROC Callback,
    _In_opt_ PVOID Context);

VOID
AW_FreeVirtDeskInfo(VOID);
