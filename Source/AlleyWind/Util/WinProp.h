#pragma once

#include "../AlleyWind.Core.inl"

#define MAX_WNDCAPTION_CCH MAX_CLASSNAME_CCH
#define MAX_ADDRESSNAME_CCH MAX_PATH

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

FORCEINLINE
W32ERROR
AW_GetWindowText(
    _In_ HWND Window,
    _Out_writes_(BufferCch) PWSTR Buffer,
    _In_ ULONG BufferCch)
{
    DWORD_PTR MsgResult;
    W32ERROR Ret;

    Ret = AW_SendMsgTO(Window, WM_GETTEXT, BufferCch, (LPARAM)Buffer, &MsgResult);
    if (Ret == ERROR_SUCCESS)
    {
        if (MsgResult < BufferCch)
        {
            Buffer[MsgResult] = UNICODE_NULL;
        } else
        {
            return ERROR_INSUFFICIENT_BUFFER;
        }
    }
    return Ret;
}

typedef enum _AW_WINDOW_RELATIONSHIP
{
    AWWindowRelationshipParent = 0,
    AWWindowRelationshipOwner,
    AWWindowRelationshipPrevious,
    AWWindowRelationshipNext,
    AWWindowRelationshipFirstChild,
    AWWindowRelationshipFirst,
    AWWindowRelationshipLast,
    /* TODO
    AWWindowRelationshipPreviousTabControl,
    AWWindowRelationshipNextTabControl,
    AWWindowRelationshipPreviousGroupControl,
    AWWindowRelationshipNextGroupControl,
    */
    AWWindowRelationshipMax,
} AW_WINDOW_RELATIONSHIP, *PAW_WINDOW_RELATIONSHIP;

typedef struct _AW_WINDOW_PROP
{
    _Notnull_ HWND Handle;
    WINDOWINFO Info; // GetWindowInfo must success

    USHORT ReaderBits; // sizeof(void*) * CHAR_BIT, 32 or 64;
    struct
    {
        USHORT TopLevel : 1;
        USHORT Unicode : 1;
        USHORT KernelMode : 1;
        USHORT MonitorInfoValid : 1;
        USHORT RelativeRectValid : 1; // FALSE if failed or not a child window
    }; // Bit flags

    RECT RelativeRect; // { 0 } if invalid

    ULONG CaptionValid;
    _Null_terminated_ WCHAR Caption[MAX_WNDCAPTION_CCH]; // UNICODE_NULL if invalid

    ULONG ClassNameValid;
    _Null_terminated_ WCHAR ClassName[MAX_CLASSNAME_CCH]; // UNICODE_NULL if invalid
    PAW_SYSCLASS_INFO SysClassInfo; // NULL if no system class matched

    ULONG WndProcValid;
    ULONGLONG WndProc; // 0 if invalid
    NTSTATUS WndProcDisplayNameValid;
    _Null_terminated_ WCHAR WndProcDisplayName[MAX_ADDRESSNAME_CCH]; // UNICODE_NULL if invalid

    ULONG InstanceHandleValid;
    ULONGLONG InstanceHandle; // 0 if invalid
    NTSTATUS InstanceHandleDisplayNameValid;
    _Null_terminated_ WCHAR InstanceHandleDisplayName[MAX_ADDRESSNAME_CCH]; // UNICODE_NULL if invalid

    /* ERROR_NOT_CHILD_WINDOW if (Prop->TopLevelWindow || !(Prop->Style & WS_CHILD)) */
    ULONG IdentifierValid;
    LONGLONG Identifier; // 0 if invalid

    ULONG ThreadProcessIdValid;
    ULONG ProcessId; // 0 if invalid
    ULONG ThreadId; // 0 if invalid

    NTSTATUS ImageMachineValid;
    USHORT ImageMachine; // IMAGE_FILE_MACHINE_UNKNOWN if invalid
    USHORT ImageBits; // 0 if invalid
    NTSTATUS ProcessImagePathValid;
    struct
    {
        UNICODE_STRING Path;
        _Null_terminated_ WCHAR Buffer[MAX_PATH];
    } ProcessImagePath;

    NTSTATUS ThreadStartAddressValid;
    ULONGLONG ThreadStartAddress; // 0 if invalid
    NTSTATUS ThreadStartAddressDisplayNameValid;
    _Null_terminated_ WCHAR ThreadStartAddressDisplayName[MAX_ADDRESSNAME_CCH]; // UNICODE_NULL if invalid

    MONITORINFOEXW MonitorInfo;
    ULONG RelWindows[AWWindowRelationshipMax];

} AW_WINDOW_PROP, *PAW_WINDOW_PROP;

/* Update window dynamic information */
W32ERROR
AW_UpdatePropInfo(
    _Inout_ PAW_WINDOW_PROP Prop);

W32ERROR
AW_GetWindowProp(
    _In_ HWND Window,
    _Out_ PAW_WINDOW_PROP* NewProp);

VOID
AW_ReleaseWindowProp(
    __drv_freesMem(Mem) _Frees_ptr_opt_ _Post_invalid_ PAW_WINDOW_PROP Prop);

FORCEINLINE
NTSTATUS
AW_IsWindowPropBitsValid(
    _In_ PAW_WINDOW_PROP Prop)
{
    if (!NT_SUCCESS(Prop->ImageMachineValid))
    {
        return Prop->ImageMachineValid;
    }
    return Prop->ReaderBits >= Prop->ImageBits ? STATUS_SUCCESS : STATUS_INVALID_IMAGE_WIN_64;
}

FORCEINLINE
_Success_(return > 0)
ULONG
AW_WritePropAddress(
    _In_ PAW_WINDOW_PROP Prop,
    _In_ ULONGLONG Address,
    _Out_writes_(BufferCch) _Always_(_Post_z_) PWSTR Buffer,
    _In_ ULONG BufferCch)
{
    ULONG u;

    if (Prop->ReaderBits != 32)
    {
        u = Str_PrintfExW(Buffer, BufferCch, L"0x%016llX", Address);
    } else
    {
        u = Str_PrintfExW(Buffer, BufferCch, L"0x%08lX", (ULONG)Address);
    }
    return u;
}

EXTERN_C_END
