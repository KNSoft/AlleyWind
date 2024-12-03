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
            Status = PS_OpenProcess(&ProcessHandle, PROCESS_QUERY_LIMITED_INFORMATION, Prop->ProcessId);
            if (!NT_SUCCESS(Status))
            {
                goto _Get_Process_Path_End;
            }
            Status = NtQueryInformationProcess(ProcessHandle, ProcessImageFileNameWin32, Buffer, sizeof(Buffer), NULL);
            NtClose(ProcessHandle);
            if (!NT_SUCCESS(Status))
            {
                goto _Get_Process_Path_End;
            }
            String = (PUNICODE_STRING)Buffer;
        } else
        {
            String = &NtCurrentPeb()->ProcessParameters->ImagePathName;
        }

        if (String->Length + sizeof(UNICODE_NULL) > sizeof(Prop->ProcessImagePath))
        {
            Status = STATUS_BUFFER_TOO_SMALL;
            goto _Get_Process_Path_End;
        }
        memcpy(Prop->ProcessImagePath, String->Buffer, String->Length);
        Prop->ProcessImagePath[String->Length / 2] = UNICODE_NULL;
        Status = STATUS_SUCCESS;
_Get_Process_Path_End:
        Prop->ProcessImagePathValid = Status;
    } else
    {
        Prop->ThreadProcessIdValid = NtGetLastError();
        Prop->ProcessId = 0;
    }

    return ERROR_SUCCESS;
}
