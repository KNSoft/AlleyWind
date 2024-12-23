#include "../../AlleyWind.inl"

/*
static
AW_I18N_DLGITEM g_astI18NItems[] = {
    { IDC_PROP_CAPTION_TEXT, Precomp4C_I18N_All_Caption },
};*/

static
VOID
UpdatePropInfo(
    _In_ HWND Dialog,
    _In_ PAW_WINDOW_PROP Prop)
{
    
}

INT_PTR
CALLBACK
ResourcePspProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    UI_DPIScaleDlgProc(hDlg, uMsg, wParam, lParam);
    if (uMsg == WM_INITDIALOG)
    {
        //AW_InitDlgItemI18N(hDlg, g_astI18NItems);

        UpdatePropInfo(hDlg, (PAW_WINDOW_PROP)lParam);

        return TRUE;
    }
    return FALSE;
}
