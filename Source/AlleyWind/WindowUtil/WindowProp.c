#include "../AlleyWind.inl"

W32ERROR
AW_GetWindowProp(
    _In_ HWND Window,
    _Out_ PAW_WINDOW_PROP Prop)
{
    DWORD_PTR dwpResult;

    if (!IsWindow(Window))
    {
        return ERROR_INVALID_PARAMETER;
    }

    /* Basic properties */
    Prop->Handle = UI_TruncateHandle(Window);
    Prop->TopLevelWindow = IsTopLevelWindow(Window);

    /* Caption */
    Prop->CaptionValid = AW_SendMsgTO(Window, WM_GETTEXT, ARRAYSIZE(Prop->Caption), (LPARAM)Prop->Caption, &dwpResult);
    if (Prop->CaptionValid == ERROR_SUCCESS)
    {
        if (dwpResult < ARRAYSIZE(Prop->Caption))
        {
            Prop->Caption[dwpResult] = UNICODE_NULL;
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
    Prop->ClassNameValid = GetClassNameW(Window,
                                         Prop->ClassName,
                                         ARRAYSIZE(Prop->ClassName)) != 0 ? ERROR_SUCCESS : NtGetLastError();

    /* GetWindowLongPtr */
    Prop->StyleValid = UI_GetWindowLong(Window, GWL_STYLE, (PLONG_PTR)&Prop->Style);
    Prop->ExStyleValid = UI_GetWindowLong(Window, GWL_EXSTYLE, (PLONG_PTR)&Prop->ExStyle);
    Prop->WndProcValid = UI_GetWindowLong(Window, GWLP_WNDPROC, (PLONG_PTR)&Prop->WndProc);
    Prop->InstanceHandleValid = UI_GetWindowLong(Window, GWLP_HINSTANCE, (PLONG_PTR)&Prop->InstanceHandle);
    if (!Prop->TopLevelWindow && Prop->Style & WS_CHILD)
    {
        Prop->IdentifierValid = UI_GetWindowLong(Window, GWLP_ID, (PLONG_PTR)&Prop->Identifier);
    } else
    {
        Prop->IdentifierValid = ERROR_INVALID_PARAMETER;
        Prop->Identifier = 0;
    }

    return ERROR_SUCCESS;
}
