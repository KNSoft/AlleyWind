#include "../AlleyWind.inl"

W32ERROR
AW_GetWindowProp(
    _In_ HWND Window,
    _Out_ PAW_WINDOW_PROP Prop)
{
    DWORD_PTR MsgResult;
    NTSTATUS Status;
    HANDLE ProcessHandle;
    BYTE Buffer[sizeof(UNICODE_STRING) + sizeof(Prop->ProcessImagePath)];
    PUNICODE_STRING String;

    if (!IsWindow(Window))
    {
        return ERROR_INVALID_PARAMETER;
    }

    /* Basic properties */
    Prop->ReaderBits = sizeof(void*) * CHAR_BIT;
    Prop->Handle = UI_TruncateHandle(Window);
    Prop->TopLevelWindow = IsTopLevelWindow(Window);

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
    Prop->WndProcValid = UI_GetWindowLong(Window, GWLP_WNDPROC, (PLONG_PTR)&Prop->WndProc);
    Prop->InstanceHandleValid = UI_GetWindowLong(Window, GWLP_HINSTANCE, (PLONG_PTR)&Prop->InstanceHandle);
    if (Prop->TopLevelWindow || !(Prop->Style & WS_CHILD))
    {
        Prop->IdentifierValid = ERROR_INVALID_PARAMETER;
        Prop->Identifier = 0;
    } else
    {
        Prop->IdentifierValid = UI_GetWindowLong(Window, GWLP_ID, (PLONG_PTR)&Prop->Identifier);
    }

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

    /* Process & Thread */
    Prop->ProcessImagePath[0] = UNICODE_NULL;
    Prop->ThreadId = GetWindowThreadProcessId(Window, &Prop->ProcessId);
    if (Prop->ThreadId != 0)
    {
        Prop->ThreadProcessIdValid = ERROR_SUCCESS;

        if (Prop->ProcessId != NtCurrentProcessId())
        {
            Prop->ImageMachine = IMAGE_FILE_MACHINE_UNKNOWN;
            Status = PS_OpenProcess(&ProcessHandle, PROCESS_QUERY_LIMITED_INFORMATION, Prop->ProcessId);
            if (!NT_SUCCESS(Status))
            {
                goto _Get_Process_Info_End;
            }
            PS_GetMachineType(ProcessHandle, &Prop->ImageMachine);
            Status = NtQueryInformationProcess(ProcessHandle, ProcessImageFileNameWin32, Buffer, sizeof(Buffer), NULL);
            NtClose(ProcessHandle);
            if (!NT_SUCCESS(Status))
            {
                goto _Get_Process_Info_End;
            }
            String = (PUNICODE_STRING)Buffer;
        } else
        {
            Prop->ImageMachine = ((PIMAGE_NT_HEADERS)Add2Ptr(&__ImageBase,
                                                             ((PIMAGE_DOS_HEADER)&__ImageBase)->e_lfanew))->FileHeader.Machine;
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
    } else
    {
        Prop->ThreadProcessIdValid = NtGetLastError();
        Prop->ProcessId = 0;
        Prop->ImageMachine = IMAGE_FILE_MACHINE_UNKNOWN;
        Prop->ImageBits = 0;
    }

    return ERROR_SUCCESS;
}

ULONG
AW_FormatAddress(
    _Out_writes_opt_(BufferCount) _Always_(_Post_z_) wchar_t* const Buffer,
    _In_ size_t const BufferCount,
    _In_ PAW_WINDOW_PROP Prop,
    _In_ ULONGLONG Address)
{
    ULONG Cch, CchLast, uTemp;
    NTSTATUS Status;
    HRESULT hr;
    HANDLE ProcessHandle;
    PUNICODE_STRING ModulePath, SymbolName;
    ULONGLONG SymbolDisplacement;
    PWSTR ModuleName;
    WCHAR ch;
    PWSTR psz;

    /* Get and write address */
    if (Prop->ReaderBits != 32)
    {
        Cch = Str_PrintfExW(Buffer, BufferCount, L"0x%016llX", Address);
    } else
    {
        Cch = Str_PrintfExW(Buffer, BufferCount, L"0x%08lX", (ULONG)Address);
    }
    if (!Str_TestCchRet(Cch, BufferCount))
    {
        return 0;
    }

    /* If reader bits smaller than image bits, address is invalid */
    if (Prop->ImageBits == 0)
    {
        psz = (PWSTR)g_NAText;
    } else if (Prop->ReaderBits < Prop->ImageBits)
    {
        psz = (PWSTR)AW_GetString(NARequire64Bit);
    } else
    {
        goto _Get_Address_Name;
    }
    if (Cch + 2 > BufferCount)
    {
        return Cch;
    }
    CchLast = Cch;
    Buffer[Cch++] = L' ';
    uTemp = (ULONG)Str_CopyExW(Buffer + Cch, BufferCount - Cch, psz);
    if (!Str_TestCchRet(uTemp, BufferCount - Cch))
    {
        goto _Truncate_0;
    }
    return Cch;

_Get_Address_Name:
    /* Get name of address */
    Status = PS_OpenProcess(&ProcessHandle, MAXIMUM_ALLOWED, Prop->ProcessId);
    if (!NT_SUCCESS(Status))
    {
        return Cch;
    }
    hr = PS_GetRemoteAddressName(ProcessHandle, Address, &ModulePath, &SymbolName, &SymbolDisplacement);
    NtClose(ProcessHandle);
    if (FAILED(hr))
    {
        return Cch;
    }

    /* Get and write module base name */
    if (Cch + 2 > BufferCount)
    {
        return Cch;
    }
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
    uTemp = (ULONG)Str_CopyExW(Buffer + Cch, BufferCount - Cch, ModuleName);
    PS_FreeUnicodeString(ModulePath);
    if (!Str_TestCchRet(uTemp, BufferCount - Cch))
    {
        goto _Truncate_1;
    }
    Cch += uTemp;
    if (SymbolName == NULL)
    {
        return Cch;
    }

    if (Cch + 2 > BufferCount)
    {
        return Cch;
    }
    CchLast = Cch;
    Buffer[Cch++] = L'!';
    uTemp = (ULONG)Str_CopyExW(Buffer + Cch, BufferCount - Cch, SymbolName->Buffer);
    if (!Str_TestCchRet(uTemp, BufferCount - Cch))
    {
        goto _Truncate_1;
    }
    Cch += uTemp;
    if (SymbolDisplacement == 0)
    {
        return Cch;
    }
    if (Cch + 2 > BufferCount)
    {
        return Cch;
    }
    CchLast = Cch;
    Buffer[Cch++] = L'+';
    if (!Str_FromIntExW(SymbolDisplacement, TRUE, 16, Buffer + Cch, (ULONG)(BufferCount - Cch)))
    {
        goto _Truncate_1;
    }
    return Cch;

_Truncate_1:
    PS_FreeUnicodeString(SymbolName);
_Truncate_0:
    Cch = CchLast;
    Buffer[Cch] = UNICODE_NULL;
    return Cch;
}
