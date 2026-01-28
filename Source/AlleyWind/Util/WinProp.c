#include "../AlleyWind.inl"

static
NTSTATUS
WriteAddressDisplayName(
    _In_ ULONGLONG Address,
    _In_ LOGICAL ModuleNameOnly,
    _In_ PAW_WINDOW_PROP Prop,
    _Out_writes_(BufferCount) PWSTR Buffer,
    _In_ ULONG BufferCount)
{
    ULONG Cch, CchLast, uTemp;
    NTSTATUS Status;
    HANDLE ProcessHandle;
    PUNICODE_STRING ModulePath, SymbolName, *pSymbolName;
    ULONGLONG SymbolDisplacement;
    PWSTR ModuleName;
    WCHAR ch;

    /* If reader bits smaller than image bits, address is invalid */
    Status = AW_IsWindowPropBitsValid(Prop);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Get name of address */
    Status = PS_OpenProcess(&ProcessHandle, MAXIMUM_ALLOWED, Prop->ProcessId);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }
    if (ModuleNameOnly)
    {
        pSymbolName = NULL;
        SymbolName = NULL;
    } else
    {
        pSymbolName = &SymbolName;
    }
    Status = PS_RemoteGetAddressName(ProcessHandle, Address, &ModulePath, pSymbolName, &SymbolDisplacement);
    NtClose(ProcessHandle);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Get and write address */
    Cch = AW_WritePropAddress(Prop, Address, Buffer, BufferCount);
    if (Cch == 0 || Cch + 2 > BufferCount)
    {
        NT_FreeStringW(ModulePath);
        Status = STATUS_BUFFER_TOO_SMALL;
        goto _Exit;
    }

    /* Get and write module base name */
    CchLast = Cch;
    Buffer[Cch++] = L' ';
    ModuleName = Add2Ptr(ModulePath->Buffer, ModulePath->Length);
    do
    {
        ch = *--ModuleName;
        if (ch == L'\\' || ch == L'/')
        {
            ModuleName++;
            break;
        }
    } while (ModuleName > ModulePath->Buffer);
    uTemp = Str_CopyExW(Buffer + Cch, BufferCount - Cch, ModuleName);
    NT_FreeStringW(ModulePath);
    if (uTemp == 0)
    {
        goto _Truncate;
    }
    if (ModuleNameOnly || SymbolName == NULL)
    {
        return STATUS_SUCCESS;
    }
    Cch += uTemp;
    if (Cch + 2 > BufferCount)
    {
        goto _Truncate;
    }
    CchLast = Cch;
    Buffer[Cch++] = L'!';
    uTemp = Str_CopyExW(Buffer + Cch, BufferCount - Cch, SymbolName->Buffer);
    if (uTemp == 0)
    {
        goto _Truncate;
    }
    Cch += uTemp;
    if (SymbolDisplacement == 0)
    {
        return STATUS_SUCCESS;
    }
    if (Cch + 2 > BufferCount)
    {
        goto _Truncate;
    }
    CchLast = Cch;
    /* FIXME: Seems false positive, we already checked (Cch + 2 > BufferCount) */
#pragma warning(disable: __WARNING_WRITE_OVERRUN)
    Buffer[Cch++] = L'+';
#pragma warning(default: __WARNING_WRITE_OVERRUN)
    uTemp = Str_FromIntExW(SymbolDisplacement, TRUE, 16, Buffer + Cch, BufferCount - Cch);
    if (uTemp == 0)
    {
        goto _Truncate;
    }
    Status = STATUS_SUCCESS;
    goto _Exit;

_Truncate:
    Cch = CchLast;
    Buffer[Cch] = UNICODE_NULL;
    Status = STATUS_SUCCESS;
_Exit:
    if (SymbolName != NULL)
    {
        NT_FreeStringW(SymbolName);
    }
    return Status;
}

W32ERROR
AW_UpdatePropInfo(
    _Inout_ PAW_WINDOW_PROP Prop)
{
    HWND Window = Prop->Handle, RelWindow;
    HMONITOR Monitor;

    /* Basic information is required */
    Prop->Info.cbSize = sizeof(Prop->Info);
    if (!GetWindowInfo(Window, &Prop->Info))
    {
        return Err_GetLastError();
    }

    /* Window relationships */
    Prop->TopLevel = IsTopLevelWindow(Window);
    for (ULONG i = 0; i < AWWindowRelationshipMax; i++)
    {
        if (i == AWWindowRelationshipParent)
        {
            RelWindow = GetAncestor(Window, GA_PARENT);
        } else if (i == AWWindowRelationshipOwner)
        {
            RelWindow = GetWindow(Window, GW_OWNER);
        } else if (i == AWWindowRelationshipPrevious)
        {
            RelWindow = GetWindow(Window, GW_HWNDPREV);
        } else if (i == AWWindowRelationshipNext)
        {
            RelWindow = GetWindow(Window, GW_HWNDNEXT);
        } else if (i == AWWindowRelationshipFirstChild)
        {
            RelWindow = GetWindow(Window, GW_CHILD);
        } else if (i == AWWindowRelationshipFirst)
        {
            RelWindow = GetWindow(Window, GW_HWNDFIRST);
        } else if (i == AWWindowRelationshipLast)
        {
            RelWindow = GetWindow(Window, GW_HWNDLAST);
        } else
        {
            RelWindow = NULL;
        }
        Prop->RelWindows[i] = UI_TruncateHandle32(RelWindow);
    }
    RelWindow = (HWND)(ULONG_PTR)Prop->RelWindows[AWWindowRelationshipParent];

    if (RelWindow != NULL &&
        RelWindow != GetDesktopWindow() &&
        UI_ScreenRectToClient(RelWindow, &Prop->Info.rcWindow, &Prop->RelativeRect))
    {
        Prop->RelativeRectValid = TRUE;
    } else
    {
        Prop->RelativeRectValid = FALSE;
        RtlZeroMemory(&Prop->RelativeRect, sizeof(Prop->RelativeRect));
    }
    if (Prop->TopLevel || !(Prop->Info.dwStyle & WS_CHILD))
    {
        Prop->IdentifierValid = ERROR_NOT_CHILD_WINDOW;
        Prop->Identifier = 0;
    } else
    {
        Prop->IdentifierValid = UI_GetWindowLong(Window, GWLP_ID, (PLONG_PTR)&Prop->Identifier);
    }

    /* Caption */
    Prop->CaptionValid = AW_GetWindowText(Window, Prop->Caption, ARRAYSIZE(Prop->Caption));
    if (Prop->CaptionValid != ERROR_SUCCESS)
    {
        Prop->Caption[0] = UNICODE_NULL;
    }

    /* Monitor */
    Prop->MonitorInfoValid = FALSE;
    Monitor = MonitorFromWindow(Window, MONITOR_DEFAULTTONULL);
    if (Monitor != NULL)
    {
        Prop->MonitorInfo.cbSize = sizeof(Prop->MonitorInfo);
        if (GetMonitorInfoW(Monitor, (LPMONITORINFO)&Prop->MonitorInfo))
        {
            Prop->MonitorInfoValid = TRUE;
        }
    }

    return ERROR_SUCCESS;
}

W32ERROR
AW_GetWindowProp(
    _In_ HWND Window,
    _Out_ PAW_WINDOW_PROP Prop)
{
    W32ERROR Ret;
    PVOID Ptr;
    NTSTATUS Status;
    HANDLE PSHandle;

    Prop->Handle = UI_TruncateHandle(Window);
    Ret = AW_UpdatePropInfo(Prop);
    if (Ret != ERROR_SUCCESS)
    {
        return Ret;
    }

    /* Process & Thread */

    Prop->ReaderBits = sizeof(void*) * CHAR_BIT;
    Prop->ThreadId = GetWindowThreadProcessId(Window, &Prop->ProcessId);
    if (Prop->ThreadId != 0)
    {
        Prop->ThreadProcessIdValid = ERROR_SUCCESS;
    } else
    {
        Prop->ThreadProcessIdValid = Err_GetLastError();
        Prop->ProcessId = 0;
    }

    Prop->ImageMachine = IMAGE_FILE_MACHINE_UNKNOWN;
    Prop->ImageBits = 0;
    Prop->ProcessImagePath.Buffer[0] = UNICODE_NULL;
    Prop->ThreadStartAddressDisplayName[0] = UNICODE_NULL;
    if (Prop->ThreadProcessIdValid != ERROR_SUCCESS)
    {
        Prop->ImageMachineValid =
            Prop->ProcessImagePathValid =
            Prop->ThreadStartAddressValid =
            Prop->ThreadStartAddressDisplayNameValid = NTSTATUS_FROM_WIN32(Prop->ThreadProcessIdValid);
        goto _Get_Thread_Info_End;
    }

    /*
     * Process image machine and path.
     * We may inject DLL to target process then call this function in the future.
     */
    if ((HANDLE)(ULONG_PTR)Prop->ProcessId != NtCurrentProcessId())
    {
        Status = PS_OpenProcess(&PSHandle, PROCESS_QUERY_LIMITED_INFORMATION, Prop->ProcessId);
        if (!NT_SUCCESS(Status))
        {
            Prop->ImageMachineValid = Prop->ProcessImagePathValid = Status;
            goto _Get_Process_Info_End;
        }
        Prop->ImageMachineValid = PS_RemoteGetMachineType(PSHandle, &Prop->ImageMachine);
        Prop->ProcessImagePathValid = NtQueryInformationProcess(PSHandle,
                                                                ProcessImageFileNameWin32,
                                                                &Prop->ProcessImagePath,
                                                                sizeof(Prop->ProcessImagePath),
                                                                NULL);
        NtClose(PSHandle);
    } else
    {
        PUNICODE_STRING pPath;

        Prop->ImageMachine = NtGetImageNtHeader()->FileHeader.Machine;
        Prop->ImageMachineValid = STATUS_SUCCESS;
        pPath = &NtCurrentPeb()->ProcessParameters->ImagePathName;
        if (pPath->Length >= sizeof(Prop->ProcessImagePath.Buffer))
        {
            Status = STATUS_BUFFER_TOO_SMALL;
        } else
        {
            Prop->ProcessImagePath.Path.Length = pPath->Length;
            Prop->ProcessImagePath.Path.MaximumLength = sizeof(Prop->ProcessImagePath.Buffer);
            Prop->ProcessImagePath.Path.Buffer = Prop->ProcessImagePath.Buffer;
            memcpy(Prop->ProcessImagePath.Buffer, pPath->Buffer, pPath->Length);
            Prop->ProcessImagePath.Buffer[pPath->Length / sizeof(WCHAR)] = UNICODE_NULL;
            Status = STATUS_SUCCESS;
        }
        Prop->ProcessImagePathValid = Status;
    }
    Prop->ImageBits = PE_GetMachineBits(Prop->ImageMachine);
_Get_Process_Info_End:

    /* Thread start address */
    Status = PS_OpenThread(&PSHandle, MAXIMUM_ALLOWED, Prop->ThreadId);
    if (!NT_SUCCESS(Status))
    {
        Prop->ThreadStartAddress = 0;
        Prop->ThreadStartAddressValid = Prop->ThreadStartAddressDisplayNameValid = Status;
        goto _Get_Thread_Info_End;
    }
    Prop->ThreadStartAddressValid = NtQueryInformationThread(PSHandle,
                                                             ThreadQuerySetWin32StartAddress,
                                                             &Ptr,
                                                             sizeof(Ptr),
                                                             NULL);
    NtClose(PSHandle);
    if (!NT_SUCCESS(Prop->ThreadStartAddressValid))
    {
        Prop->ThreadStartAddress = 0;
        Prop->ThreadStartAddressDisplayNameValid = Prop->ThreadStartAddressValid;
        goto _Get_Thread_Info_End;
    }
    Prop->ThreadStartAddress = (ULONGLONG)(ULONG_PTR)Ptr;
    Prop->ThreadStartAddressDisplayNameValid = WriteAddressDisplayName(Prop->ThreadStartAddress,
                                                                       FALSE,
                                                                       Prop,
                                                                       Prop->ThreadStartAddressDisplayName,
                                                                       ARRAYSIZE(Prop->ThreadStartAddressDisplayName));
_Get_Thread_Info_End:

    /* ClassName */
    if (GetClassNameW(Window, Prop->ClassName, ARRAYSIZE(Prop->ClassName)) != 0)
    {
        Prop->ClassNameValid = ERROR_SUCCESS;
        Prop->SysClassInfo = AW_GetSysClass(Prop->ClassName);
    } else
    {
        Prop->ClassNameValid = Err_GetLastError();
        Prop->ClassName[0] = UNICODE_NULL;
    }

    /* GetWindowLongPtr */
    Prop->WndProcValid = UI_GetWindowLong(Window, GWLP_WNDPROC, (PLONG_PTR)&Ptr);
    Prop->WndProc = (ULONGLONG)(ULONG_PTR)Ptr;
    if (Prop->WndProcValid == ERROR_SUCCESS)
    {
        Prop->WndProcDisplayNameValid = WriteAddressDisplayName(Prop->WndProc,
                                                                FALSE,
                                                                Prop,
                                                                Prop->WndProcDisplayName,
                                                                ARRAYSIZE(Prop->WndProcDisplayName));
    }
    Prop->InstanceHandleValid = UI_GetWindowLong(Window, GWLP_HINSTANCE, (PLONG_PTR)&Ptr);
    Prop->InstanceHandle = (ULONGLONG)(ULONG_PTR)Ptr;
    if (Prop->InstanceHandleValid == ERROR_SUCCESS)
    {
        Prop->InstanceHandleDisplayNameValid = WriteAddressDisplayName(Prop->InstanceHandle,
                                                                       TRUE,
                                                                       Prop,
                                                                       Prop->InstanceHandleDisplayName,
                                                                       ARRAYSIZE(Prop->InstanceHandleDisplayName));
    } else
    {
        Prop->InstanceHandleDisplayName[0] = UNICODE_NULL;
    }

    Prop->Unicode = IsWindowUnicode(Window);
    Prop->KernelMode = IsServerSideWindow(Window);

    return ERROR_SUCCESS;
}
