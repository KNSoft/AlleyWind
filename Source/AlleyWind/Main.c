#include "AlleyWind.inl"

int
WINAPI
WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd)
{
    NTSTATUS Status;
    PVOID MainDlgRes;
    INT_PTR DlgRet;
    DPI_AWARENESS_CONTEXT DPIContext;

    Status = PE_AccessResource(hInstance,
                               MAKEINTRESOURCEW(RT_DIALOG),
                               MAKEINTRESOURCEW(IDD_MAIN),
                               LANG_USER_DEFAULT,
                               &MainDlgRes,
                               NULL);
    if (!NT_SUCCESS(Status))
    {
        return RtlNtStatusToDosErrorNoTeb(Status);
    }

    DPIContext = UI_EnableDPIAwareContext();
    DlgRet = DialogBoxIndirectParamW((HINSTANCE)&__ImageBase, MainDlgRes, NULL, MainDlgProc, 0);
    UI_RestoreDPIAwareContext(DPIContext);
    return DlgRet != -1 ? (int)DlgRet : (int)NtGetLastError();
}
