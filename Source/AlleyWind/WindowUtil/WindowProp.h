#pragma once

#include "../AlleyWind.Core.inl"

#define MAX_WNDCAPTION_CCH MAX_CLASSNAME_CCH

EXTERN_C_START

typedef struct _AW_WINDOW_PROP
{
    HWND Handle;

    LOGICAL TopLevelWindow;

    W32ERROR CaptionValid;
    _Null_terminated_ WCHAR Caption[MAX_WNDCAPTION_CCH]; // UNICODE_NULL if invalid
    
    W32ERROR ClassNameValid;
    _Null_terminated_ WCHAR ClassName[MAX_CLASSNAME_CCH]; // UNICODE_NULL if invalid
    
    W32ERROR StyleValid;
    ULONG Style; // 0 if invalid

    W32ERROR ExStyleValid;
    ULONG ExStyle; // 0 if invalid

    W32ERROR WndProcValid;
    PVOID WndProc; // NULL if invalid

    W32ERROR InstanceHandleValid;
    HINSTANCE InstanceHandle; // NULL if invalid

    /* !TopLevelWindow only */
    W32ERROR IdentifierValid; // ERROR_INVALID_PARAMETER if TopLevelWindow / Non-child window
    INT_PTR Identifier; // 0 if invalid

} AW_WINDOW_PROP, *PAW_WINDOW_PROP;

W32ERROR
AW_GetWindowProp(
    _In_ HWND Window,
    _Out_ PAW_WINDOW_PROP Prop);

EXTERN_C_END
