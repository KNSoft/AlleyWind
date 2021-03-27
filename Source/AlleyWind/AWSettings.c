#include "AlleyWind.h"

UINT uSendMsgTO = 100;
BOOL uEnableRemoteHijack = FALSE;

VOID AWSettings_Init() {
    TCHAR   szSettingsFile[MAX_PATH];
    UINT    uCch = Str_CchCopy(szSettingsFile, NT_GetPEB()->ProcessParameters->ImagePathName.Buffer);
    while (szSettingsFile[--uCch] != '\\');
    uCch++;
    Str_CchCopyEx(szSettingsFile + uCch, ARRAYSIZE(szSettingsFile) - uCch, TEXT("Settings.ini"));
    uSendMsgTO = GetPrivateProfileInt(TEXT("General"), TEXT("ResponseTimeout"), uSendMsgTO, szSettingsFile);
    uEnableRemoteHijack = GetPrivateProfileInt(TEXT("General"), TEXT("EnableRemoteHijack"), uEnableRemoteHijack, szSettingsFile);
}

DWORD AWSettings_GetItemValueEx(INT Index) {
    if (Index == AWSetting_ResponseTimeout)
        return uSendMsgTO;
    else if (Index == AWSetting_EnableRemoteHijack)
        return uEnableRemoteHijack;
    return TRUE;
}