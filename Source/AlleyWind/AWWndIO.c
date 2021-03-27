#include "AlleyWind.h"



LRESULT AW_SendMsgTO(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, PDWORD_PTR lpdwResult) {
    return SendMessageTimeout(
        hWnd,
        uMsg,
        wParam,
        lParam,
        SMTO_ABORTIFHUNG | SMTO_ERRORONEXIT,
        AWSettings_GetItemValueEx(AWSetting_ResponseTimeout),
        lpdwResult);
}