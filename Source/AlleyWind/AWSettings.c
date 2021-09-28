#include "AlleyWind.h"

UINT uSendMsgTO = 200;

VOID AWSettings_Init() {
    
}

DWORD AWSettings_GetItemValueEx(INT Index) {
    if (Index == AWSetting_ResponseTimeout)
        return uSendMsgTO;
    return TRUE;
}