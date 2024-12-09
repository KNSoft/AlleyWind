#pragma once

#include "../AlleyWind.Core.inl"

#define MAX_WNDCAPTION_CCH MAX_CLASSNAME_CCH

EXTERN_C_START

// TODO: Read configuration
FORCEINLINE
W32ERROR
AW_SendMsgTO(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, PDWORD_PTR lpdwResult)
{
    return UI_SendMessageTimeout(hWnd, uMsg, wParam, lParam, SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT, 200, lpdwResult);
}

FORCEINLINE
HICON
AW_GetWindowIcon(
    _In_ HWND Window)
{
    HICON hIcon = NULL;
    if (AW_SendMsgTO(Window, WM_GETICON, ICON_SMALL, 0, (PDWORD_PTR)&hIcon) != ERROR_SUCCESS || hIcon == NULL)
    {
        hIcon = (HICON)GetClassLongPtrW(Window, GCLP_HICON);
    }
    return hIcon;
}

typedef struct _AW_WINDOW_PROP
{
    USHORT ReaderBits; // sizeof(void*) * CHAR_BIT, 32 or 64;
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
    ULONGLONG WndProc; // 0 if invalid

    ULONG InstanceHandleValid;
    ULONGLONG InstanceHandle; // 0 if invalid

    /* ERROR_INVALID_PARAMETER if (Prop->TopLevelWindow || !(Prop->Style & WS_CHILD)) */
    ULONG IdentifierValid;
    LONGLONG Identifier; // 0 if invalid

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
    USHORT ImageMachine; // IMAGE_FILE_MACHINE_UNKNOWN if invalid
    USHORT ImageBits; // 0 if invalid

    /* Require ProcessId valid */
    NTSTATUS ProcessImagePathValid;
    WCHAR ProcessImagePath[MAX_PATH]; // UNICODE_NULL if invalid

} AW_WINDOW_PROP, *PAW_WINDOW_PROP;

W32ERROR
AW_GetWindowProp(
    _In_ HWND Window,
    _Out_ PAW_WINDOW_PROP Prop);

ULONG
AW_FormatAddress(
    _Out_writes_opt_(BufferCount) _Always_(_Post_z_) wchar_t* const Buffer,
    _In_ size_t const BufferCount,
    _In_ PAW_WINDOW_PROP Prop,
    _In_ ULONGLONG Address);

EXTERN_C_END
