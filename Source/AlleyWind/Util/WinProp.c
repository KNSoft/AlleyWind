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
    Status = PS_GetRemoteAddressName(ProcessHandle, Address, &ModulePath, pSymbolName, &SymbolDisplacement);
    NtClose(ProcessHandle);
    if (!NT_SUCCESS(Status))
    {
        return Status;
    }

    /* Get and write address */
    Cch = AW_WritePropAddress(Prop, Address, Buffer, BufferCount);
    if (Cch == 0 || Cch + 2 > BufferCount)
    {
        PS_FreeUnicodeString(ModulePath);
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
    PS_FreeUnicodeString(ModulePath);
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
        PS_FreeUnicodeString(SymbolName);
    }
    return Status;
}

W32ERROR
AW_GetWindowProp(
    _In_ HWND Window,
    _Out_ PAW_WINDOW_PROP Prop)
{
    PVOID Ptr;
    DWORD_PTR MsgResult;
    NTSTATUS Status;
    HANDLE PSHandle;
    BYTE Buffer[sizeof(UNICODE_STRING) + sizeof(Prop->ProcessImagePath)];
    PUNICODE_STRING String;
    HMONITOR Monitor;

    if (!IsWindow(Window))
    {
        return ERROR_INVALID_PARAMETER;
    }

    /* Basic properties */
    Prop->ReaderBits = sizeof(void*) * CHAR_BIT;
    Prop->Handle = UI_TruncateHandle32(Window);
    Prop->TopLevelWindow = IsTopLevelWindow(Window);
    Prop->ThreadId = GetWindowThreadProcessId(Window, &Prop->ProcessId);
    if (Prop->ThreadId != 0)
    {
        Prop->ThreadProcessIdValid = ERROR_SUCCESS;
    } else
    {
        Prop->ThreadProcessIdValid = NtGetLastError();
        Prop->ProcessId = 0;
    }

    /* Process & Thread */
    Prop->ProcessImagePath[0] = UNICODE_NULL;
    Prop->ThreadStartAddressDisplayName[0] = UNICODE_NULL;
    if (Prop->ThreadProcessIdValid == ERROR_SUCCESS)
    {
        /* Process image path */
        if (Prop->ProcessId != NtCurrentProcessId())
        {
            Status = PS_OpenProcess(&PSHandle, PROCESS_QUERY_LIMITED_INFORMATION, Prop->ProcessId);
            if (!NT_SUCCESS(Status))
            {
                goto _Get_Process_Info_End;
            }
            Prop->ImageMachineValid = PS_GetMachineType(PSHandle, &Prop->ImageMachine);
            Status = NtQueryInformationProcess(PSHandle, ProcessImageFileNameWin32, Buffer, sizeof(Buffer), NULL);
            NtClose(PSHandle);
            if (!NT_SUCCESS(Status))
            {
                goto _Get_Process_Info_End;
            }
            String = (PUNICODE_STRING)Buffer;
        } else
        {
            Prop->ImageMachine = NtGetImageNtHeader()->FileHeader.Machine;
            Prop->ImageMachineValid = STATUS_SUCCESS;
            String = &NtCurrentPeb()->ProcessParameters->ImagePathName;
        }
        Prop->ImageBits = PE_GetMachineBits(Prop->ImageMachine);
        if (String->Length + sizeof(UNICODE_NULL) > sizeof(Prop->ProcessImagePath))
        {
            Status = STATUS_BUFFER_TOO_SMALL;
            goto _Get_Process_Info_End;
        }
        memcpy(Prop->ProcessImagePath, String->Buffer, String->Length);
        Prop->ProcessImagePath[String->Length / 2] = UNICODE_NULL;
        Status = STATUS_SUCCESS;
_Get_Process_Info_End:
        Prop->ProcessImagePathValid = Status;

        /* Thread start address */
        Status = PS_OpenThread(&PSHandle, MAXIMUM_ALLOWED, Prop->ThreadId);
        if (!NT_SUCCESS(Status))
        {
            goto _Get_Thread_Info_End;
        }
        Status = NtQueryInformationThread(PSHandle,
                                          ThreadQuerySetWin32StartAddress,
                                          &Ptr,
                                          sizeof(Ptr),
                                          NULL);
        NtClose(PSHandle);
        if (!NT_SUCCESS(Status))
        {
            Prop->ThreadStartAddress = 0;
            goto _Get_Thread_Info_End;
        }
        Prop->ThreadStartAddress = (ULONGLONG)(ULONG_PTR)Ptr;
        Prop->ThreadStartAddressDisplayNameValid = WriteAddressDisplayName(Prop->ThreadStartAddress,
                                                                           FALSE,
                                                                           Prop,
                                                                           Prop->ThreadStartAddressDisplayName,
                                                                           ARRAYSIZE(Prop->ThreadStartAddressDisplayName));
_Get_Thread_Info_End:
        Prop->ThreadStartAddressValid = Status;
    } else
    {
        Prop->ImageMachineValid = STATUS_UNSUCCESSFUL;
        Prop->ImageMachine = IMAGE_FILE_MACHINE_UNKNOWN;
        Prop->ImageBits = 0;
    }

    /* Caption */
    Prop->CaptionValid = AW_SendMsgTO(Window, WM_GETTEXT, ARRAYSIZE(Prop->Caption), (LPARAM)Prop->Caption, &MsgResult);
    if (Prop->CaptionValid == ERROR_SUCCESS)
    {
        if (MsgResult < ARRAYSIZE(Prop->Caption))
        {
            Prop->Caption[MsgResult] = UNICODE_NULL;
        } else
        {
            Prop->CaptionValid = ERROR_INSUFFICIENT_BUFFER;
            Prop->Caption[0] = UNICODE_NULL;
        }
    } else
    {
        Prop->Caption[0] = UNICODE_NULL;
    }

    /* ClassName */
    if (GetClassNameW(Window, Prop->ClassName, ARRAYSIZE(Prop->ClassName)) != 0)
    {
        Prop->ClassNameValid = ERROR_SUCCESS;
    } else
    {
        Prop->ClassNameValid = NtGetLastError();
        Prop->ClassName[0] = UNICODE_NULL;
    }

    /* GetWindowLongPtr */
    Prop->StyleValid = UI_GetWindowLong(Window, GWL_STYLE, (PLONG_PTR)&Prop->Style);
    Prop->ExStyleValid = UI_GetWindowLong(Window, GWL_EXSTYLE, (PLONG_PTR)&Prop->ExStyle);
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
    if (Prop->TopLevelWindow || !(Prop->Style & WS_CHILD))
    {
        Prop->IdentifierValid = ERROR_INVALID_PARAMETER;
        Prop->Identifier = 0;
    } else
    {
        Prop->IdentifierValid = UI_GetWindowLong(Window, GWLP_ID, (PLONG_PTR)&Prop->Identifier);
    }

    Prop->Unicode = IsWindowUnicode(Window);
    Prop->KernelMode = IsServerSideWindow(Window);

    /* Rect */
    Prop->ScreenRectValid = UI_GetWindowRect(Window, &Prop->ScreenRect);
    if (FAILED(Prop->ScreenRectValid))
    {
        RtlZeroMemory(&Prop->ScreenRect, sizeof(Prop->ScreenRect));
    }
    if (Prop->TopLevelWindow || !(Prop->Style & WS_CHILD))
    {
        if (GetClientRect(Window, &Prop->Rect2))
        {
            Prop->Rect2Valid = ERROR_SUCCESS;
        } else
        {
            Prop->Rect2Valid = NtGetLastError();
            RtlZeroMemory(&Prop->Rect2, sizeof(Prop->Rect2));
        }
    } else
    {
        Prop->Rect2Valid = (ULONG)UI_GetRelativeRect(Window, NULL, &Prop->Rect2);
        if (FAILED((HRESULT)Prop->Rect2Valid))
        {
            RtlZeroMemory(&Prop->Rect2, sizeof(Prop->Rect2));
        }
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
