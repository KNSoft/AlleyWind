#include "AlleyWind.inl"

/* App Info */

KNS_APPINFO g_KNSAppInfo = {
    L"AlleyWind",
    L"https://github.com/KNSoft/AlleyWind"
};

static
int
RunMainProgram(VOID)
{
    HRESULT hr, hrCom;

    /* COM initialization is optional currently */
    hrCom = CoInitializeEx(NULL, COINIT_MULTITHREADED);

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
W32ERROR
SelfRunAs(
    _In_opt_ HANDLE Token)
{
    W32ERROR Ret;
    PROCESS_INFORMATION pi;

    Ret = PS_CreateProcess(Token,
                           NtCurrentPeb()->ProcessParameters->ImagePathName.Buffer,
                           NULL,
                           FALSE,
                           NULL,
                           NULL,
                           &pi);
    NtClose(pi.hThread);
    NtClose(pi.hProcess);

    return Ret;
}

static
int
RunWithUIAccessElevation(VOID)
{
    HRESULT Ret;
    ULONG LsaProcessId, UIAccess = FALSE;
    HANDLE LsaToken, ProcessToken;
    W32ERROR W32Ret;

    /* Impersonate LSA */
    if (!NT_SUCCESS(Sys_LsaGetProcessId(&LsaProcessId)))
    {
        goto _Exit_0;
    }
    if (!NT_SUCCESS(PS_DuplicateSystemToken(LsaProcessId, TokenImpersonation, &LsaToken)))
    {
        goto _Exit_0;
    }
    if (!NT_SUCCESS(PS_Impersonate(LsaToken)))
    {
        goto _Exit_1;
    }

    /* Duplicate current process token with UIAccess and run */
    if (!NT_SUCCESS(NtOpenProcessToken(NtCurrentProcess(), MAXIMUM_ALLOWED, &ProcessToken)))
    {
        goto _Exit_2;
    }
    UIAccess = TRUE;
    if (!NT_SUCCESS(NtSetInformationToken(ProcessToken, TokenUIAccess, &UIAccess, sizeof(UIAccess))))
    {
        UIAccess = FALSE;
        goto _Exit_3;
    }
    if (SelfRunAs(ProcessToken) != ERROR_SUCCESS)
    {
        UIAccess = FALSE;
    }

_Exit_3:
    NtClose(ProcessToken);
_Exit_2:
    PS_Impersonate(NULL);
_Exit_1:
    NtClose(LsaToken);
_Exit_0:

    /* Fallback to run without UIAccess */
    if (!UIAccess)
    {
        W32Ret = SelfRunAs(NULL);
        Ret = W32Ret == ERROR_SUCCESS ? S_FALSE : HRESULT_FROM_WIN32(W32Ret);
    } else
    {
        Ret = S_OK;
    }

    return (int)Ret;
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
    HRESULT Ret;

    Status = PS_CommandLineToArgvW(lpCmdLine, &ArgC, &ArgV);
    if (!NT_SUCCESS(Status))
    {
        return HRESULT_FROM_NT(Status);
    }

    for (i = 0; i < ArgC; i++)
    {
        if (Str_EqualW(ArgV[i], CMDLINE_SWITCH_ELEVATEUIACCESS))
        {
            Ret = RunWithUIAccessElevation();
            goto _Exit;
        }
    }

    Ret = RunMainProgram();

_Exit:
    PS_FreeCommandLineArgv(ArgV);
    return Ret;
}
