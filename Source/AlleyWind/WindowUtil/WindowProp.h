#pragma once

#include "../AlleyWind.Core.inl"

#define MAX_WNDCAPTION_CCH MAX_CLASSNAME_CCH

EXTERN_C_START

typedef struct _AW_WINDOW_PROP
{
    HWND Handle;

    LOGICAL TopLevelWindow;

    ULONG CaptionValid;
    _Null_terminated_ WCHAR Caption[MAX_WNDCAPTION_CCH]; // UNICODE_NULL if invalid

    ULONG ClassNameValid;
    _Null_terminated_ WCHAR ClassName[MAX_CLASSNAME_CCH]; // UNICODE_NULL if invalid

    ULONG StyleValid;
    ULONG Style; // 0 if invalid

    ULONG ExStyleValid;
    ULONG ExStyle; // 0 if invalid

    ULONG WndProcValid;
    PVOID WndProc; // NULL if invalid

    ULONG InstanceHandleValid;
    HINSTANCE InstanceHandle; // NULL if invalid

    /* ERROR_INVALID_PARAMETER if (Prop->TopLevelWindow || !(Prop->Style & WS_CHILD)) */
    ULONG IdentifierValid;
    INT_PTR Identifier; // 0 if invalid

    HRESULT ScreenRectValid;
    RECT ScreenRect; // { 0 } if invalid

    /*
     * ULONG(Win32 ERROR) with Client Rect if (Prop->TopLevelWindow || !(Prop->Style & WS_CHILD)),
     * HRESULT with Relative Rect otherwise
     */
    ULONG Rect2Valid;
    RECT Rect2;

    ULONG ThreadProcessIdValid;
    ULONG ProcessId; // 0 if invalid
    ULONG ThreadId; // 0 if invalid

    /* Require ProcessId valid */
    NTSTATUS ProcessImagePathValid;
    WCHAR ProcessImagePath[MAX_PATH]; // UNICODE_NULL if invalid

} AW_WINDOW_PROP, *PAW_WINDOW_PROP;

W32ERROR
AW_GetWindowProp(
    _In_ HWND Window,
    _Out_ PAW_WINDOW_PROP Prop);

EXTERN_C_END
