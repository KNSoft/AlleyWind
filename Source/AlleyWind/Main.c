#include "AlleyWind.inl"

/* App Info */

KNS_APPINFO g_KNSAppInfo = {
    KNSOFT_APP_NAME,
    L"https://github.com/KNSoft/AlleyWind"
};

LOGICAL g_IsRunAsAdmin = FALSE;
LOGICAL g_HasUIAccess = FALSE;

static
int
RunMainProgram(VOID)
{
    HRESULT hr, hrCom;

    /* COM initialization is optional currently */
    hrCom = CoInitializeEx(NULL, COINIT_MULTITHREADED);

    AW_InitClassDatabase();
    AW_InitStockResource();
    hr = AW_OpenMainDialogBox();
    if (FAILED(hr))
    {
        KNS_HrMessageBox(NULL, hr);
    }
    AW_UninitStockResource();

    if (SUCCEEDED(hrCom))
    {
        CoUninitialize();
    }

    return (int)hr;
}

static
HRESULT
TryElevateUIAccess(VOID)
{
    HRESULT Ret;
    NTSTATUS Status;
    ULONG LsaProcessId, UIAccess = FALSE;
    HANDLE LsaToken, ProcessToken;
    W32ERROR W32Ret;
    PROCESS_INFORMATION pi;

    /* Impersonate LSA */
    Status = Sys_LsaGetProcessId(&LsaProcessId);
    if (!NT_SUCCESS(Status))
    {
        return HRESULT_FROM_NT(Status);
    }
    Status = PS_DuplicateSystemToken(LsaProcessId, TokenImpersonation, &LsaToken);
    if (!NT_SUCCESS(Status))
    {
        return HRESULT_FROM_NT(Status);
    }
    Status = PS_Impersonate(LsaToken);
    if (!NT_SUCCESS(Status))
    {
        Ret = HRESULT_FROM_NT(Status);
        goto _Exit_0;
    }

    /* Duplicate current process token with UIAccess and run */
    Status = NtOpenProcessToken(NtCurrentProcess(), MAXIMUM_ALLOWED, &ProcessToken);
    if (!NT_SUCCESS(Status))
    {
        Ret = HRESULT_FROM_NT(Status);
        goto _Exit_1;
    }
    UIAccess = TRUE;
    Status = NtSetInformationToken(ProcessToken, TokenUIAccess, &UIAccess, sizeof(UIAccess));
    if (!NT_SUCCESS(Status))
    {
        Ret = HRESULT_FROM_NT(Status);
        goto _Exit_2;
    }
    W32Ret = PS_CreateProcess(ProcessToken,
                              NtCurrentPeb()->ProcessParameters->ImagePathName.Buffer,
                              NULL,
                              FALSE,
                              NULL,
                              NULL,
                              &pi);
    NtClose(pi.hThread);
    NtClose(pi.hProcess);
    Ret = W32Ret == ERROR_SUCCESS ? S_OK : HRESULT_FROM_WIN32(W32Ret);

_Exit_2:
    NtClose(ProcessToken);
_Exit_1:
    PS_Impersonate(NULL);
_Exit_0:
    NtClose(LsaToken);
    return Ret;
}

int
WINAPI
wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd)
{
    NTSTATUS Status;
    ULONG ArgC, i;
    PWSTR* ArgV;
    HANDLE Token;
    ULONG UIAccess, Length;
    HRESULT Ret;

    Status = PS_CommandLineToArgvW(lpCmdLine, &ArgC, &ArgV);
    if (!NT_SUCCESS(Status))
    {
        return HRESULT_FROM_NT(Status);
    }
    for (i = 0; i < ArgC; i++)
    {
        if (Str_EqualW(ArgV[i], CMDLINE_SWITCH_TRYELEVATEUIACCESS))
        {
            Ret = TryElevateUIAccess();
            if (SUCCEEDED(Ret))
            {
                goto _Exit;
            }
            goto _RunMain;
        }
    }

_RunMain:

    /* Get current privileges */
    Status = PS_OpenCurrentThreadToken(&Token);
    if (NT_SUCCESS(Status))
    {
        g_IsRunAsAdmin = NT_SUCCESS(PS_IsAdminToken(Token));
        g_HasUIAccess = NT_SUCCESS(NtQueryInformationToken(Token,
                                                           TokenUIAccess,
                                                           &UIAccess,
                                                           sizeof(UIAccess),
                                                           &Length)) && UIAccess != 0;
        NtClose(Token);
    }

    /* Try to acquire UIAccess if we are already have Administrator privilege */
    if (g_IsRunAsAdmin && !g_HasUIAccess)
    {
        Ret = TryElevateUIAccess();
        if (SUCCEEDED(Ret))
        {
            goto _Exit;
        }
    }

    Ret = RunMainProgram();

_Exit:
    PS_FreeCommandLineArgv(ArgV);
    return Ret;
}
