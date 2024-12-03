#include "../../AlleyWind.inl"

static
AW_I18N_DLGITEM g_astI18NItems[] = {
    { IDC_PROP_PROCESS_TEXT, Precomp4C_I18N_All_Process },
    { IDC_PROP_THREAD_TEXT, Precomp4C_I18N_All_Thread },
};

static
VOID
UpdatePropInfo(
    _In_ HWND Dialog,
    _In_ PAW_WINDOW_PROP Prop)
{
    WCHAR szBuffer[MAX_PATH + 64];
    ULONG uTemp, uTemp2;
    PCWSTR pszTemp;

    if (Prop->ThreadProcessIdValid == ERROR_SUCCESS)
    {
        uTemp = Str_PrintfW(szBuffer, L"(%lu)", Prop->ProcessId);
        if (ARRAYSIZE(szBuffer) - uTemp <= 2)
        {
            goto _End_Write_Process_Path;
        }
        uTemp2 = uTemp;
        szBuffer[uTemp++] = L' ';
        if (NT_SUCCESS(Prop->ProcessImagePathValid))
        {
            if (Str_CopyExW(szBuffer + uTemp,
                            ARRAYSIZE(szBuffer) - uTemp,
                            Prop->ProcessImagePath) >= ARRAYSIZE(szBuffer) - uTemp)
            {
                szBuffer[uTemp2] = UNICODE_NULL;
                goto _End_Write_Process_Path;
            }
        } else
        {
            pszTemp = Err_GetNtStatusInfo(Prop->ProcessImagePathValid);
            if (pszTemp != NULL)
            {
                Str_PrintfExW(szBuffer + uTemp, ARRAYSIZE(szBuffer) - uTemp, g_NAFormatText, pszTemp);
            } else
            {
                Str_CopyExW(szBuffer + uTemp, ARRAYSIZE(szBuffer) - uTemp, g_NAText);
            }
        }
_End_Write_Process_Path:
        UI_SetDlgItemTextW(Dialog, IDC_PROP_PROCESS_EDIT, szBuffer);
    } else
    {
        pszTemp = AW_FormatNAFromWin32Error(szBuffer, ARRAYSIZE(szBuffer), Prop->ThreadProcessIdValid);
        UI_SetDlgItemTextW(Dialog, IDC_PROP_PROCESS_EDIT, pszTemp);
        UI_SetDlgItemTextW(Dialog, IDC_PROP_THREAD_EDIT, pszTemp);
    }
}

INT_PTR
CALLBACK
RelationPspProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    UI_DPIScaleDlgProc(hDlg, uMsg, wParam, lParam);
    if (uMsg == WM_INITDIALOG)
    {
        AW_InitDlgItemI18N(hDlg, g_astI18NItems);

        UpdatePropInfo(hDlg, (PAW_WINDOW_PROP)lParam);

        return TRUE;
    }
    return FALSE;
}
