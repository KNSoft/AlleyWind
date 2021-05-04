#include "AlleyWind.h"

UINT uSendMsgTO = 200;
BOOL uEnableRemoteHijack = TRUE;

VOID AWSettings_Init() {
    
}

DWORD AWSettings_GetItemValueEx(INT Index) {
    if (Index == AWSetting_ResponseTimeout)
        return uSendMsgTO;
    else if (Index == AWSetting_EnableRemoteHijack)
        return uEnableRemoteHijack;
    return TRUE;
}