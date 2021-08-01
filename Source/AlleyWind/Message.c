#include "AlleyWind.h"

#define MAX_MSG_CCH 64
#define MAX_TIMEOUT_CCH 8
#define MAX_PARAM_CCH MAX_PATH

I18N_CTLTEXT astWndPropMessageTextCtl[] = {
    { IDC_WNDPROP_MSG_MSG_TEXT, I18NIndex_Message },
    { IDC_WNDPROP_MSG_METHOD_TEXT, I18NIndex_SendMethod },
    { IDC_WNDPROP_MSG_ATTACH_CHECK, I18NIndex_AttachThreadInput },
    { IDC_WNDPROP_MSG_TIMEOUT_TEXT, I18NIndex_Timeout },
    { IDC_WNDPROP_MSG_SEND_BTN, I18NIndex_Send },
    { IDC_WNDPROP_MSG_RESULT_TEXT, I18NIndex_Result }
};

CTL_COMBOBOXCTL_ITEM astWndPropMessageSendMethodItems[] = {
    { I18NIndex_SendMethod_LMS, I18NIndex_SendMethod_LMS },
    { I18NIndex_SendMethod_RMS, I18NIndex_SendMethod_RMS },
    { I18NIndex_SendMethod_RWPC, I18NIndex_SendMethod_RWPC },
    { I18NIndex_SendMethod_RWPE, I18NIndex_SendMethod_RWPE }
};

CTL_COMBOBOXCTL_ITEM astWndPropMessageParamTypeItems[] = {
    { I18NIndex_ParamTypeNotUsed, MsgParamTypeNotUsed },
    { I18NIndex_ParamTypeNum, MsgParamTypeNum },
    { I18NIndex_ParamTypeBoolean, MsgParamTypeBoolean },
    { I18NIndex_ParamTypeString, MsgParamTypeString },
    { I18NIndex_Handle, MsgParamTypeHandle },
    { I18NIndex_ParamTypeRaw, MsgParamTypeRaw },
};

CTL_COMBOBOXCTL_ITEM astWndPropMessageTimeoutItems[] = {
    { I18NIndex_AsyncTimeout, 0 },
    { (UINT_PTR)TEXT("100"), 100 },
    { (UINT_PTR)TEXT("200"), 200 },
    { (UINT_PTR)TEXT("300"), 300 },
    { (UINT_PTR)TEXT("500"), 500 },
    { (UINT_PTR)TEXT("1000"), 1000 }
};

CTL_COMBOBOXCTL_ITEM astWndPropMessageBooleanItems[] = {
    { (UINT_PTR)TEXT("TRUE(1)"), TRUE },
    { (UINT_PTR)TEXT("FALSE(0)"), FALSE },
    { (UINT_PTR)TEXT("ERROR(-1)"), -1 }
};

VOID WndPropMessageEnableLink(HWND hLink, BOOL bEnable) {
    LITEM   stLI;
    stLI.iLink = 0;
    stLI.mask = LIF_ITEMINDEX | LIF_STATE;
    stLI.stateMask = LIS_ENABLED | LIS_DEFAULTCOLORS;
    stLI.state = bEnable ? LIS_ENABLED : LIS_DEFAULTCOLORS;
    SendMessage(hLink, LM_SETITEM, (WPARAM)NULL, (LPARAM)&stLI);
    EnableWindow(hLink, bEnable);
}

INT_PTR WINAPI WndPropMessageDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_INITDIALOG) {
        HWND    hCombox;
        UINT    i, iItem;
        AW_SetWndPropHWnd(hDlg, (HWND)lParam);
        KNS_SetDialogSubclass(hDlg, NULL);
        I18N_InitCtlTexts(hDlg, astWndPropMessageTextCtl);

        // Windows Message List and MSDN Link
        hCombox = GetDlgItem(hDlg, IDC_WNDPROP_MSG_MSG_COMBOX);
        SendMessage(hCombox, CB_SETCUEBANNER, 0, (LPARAM)I18N_GetString(I18NIndex_MsgComboxCue));
        for (i = 0; i < ARRAYSIZE(DB_stMsgInfo); i++) {
            PTSTR   pszDisplayText;
            TCHAR   szMsgDisplay[MAX_PATH];
            pszDisplayText = Str_CchPrintf(szMsgDisplay, TEXT("(%4d) %s"), DB_stMsgInfo[i].Msg, DB_stMsgInfo[i].Name) > 0 ? szMsgDisplay : DB_stMsgInfo[i].Name;
            iItem = (UINT)SendMessage(hCombox, CB_ADDSTRING, 0, (LPARAM)pszDisplayText);
            if (iItem != CB_ERR)
                SendMessage(hCombox, CB_SETITEMDATA, iItem, (LPARAM)&DB_stMsgInfo[i]);
        }
        SendMessage(hCombox, CB_LIMITTEXT, MAX_MSG_CCH - 1, 0);
        WndPropMessageEnableLink(GetDlgItem(hDlg, IDC_WNDPROP_MSG_MSDN_LINK), FALSE);

        // Send Methods
        hCombox = GetDlgItem(hDlg, IDC_WNDPROP_MSG_METHOD_COMBOX);
        Ctl_InitComboBox(hCombox, astWndPropMessageSendMethodItems, TRUE);
        SendMessage(hCombox, CB_SETCURSEL, 0, 0);

        // Type of WPARAM and LPARAM
        BOOL    bWParam = TRUE;
        do {
            hCombox = GetDlgItem(hDlg, bWParam ? IDC_WNDPROP_MSG_WPARAM_TYPE_COMBOX : IDC_WNDPROP_MSG_LPARAM_TYPE_COMBOX);
            Ctl_InitComboBox(hCombox, astWndPropMessageParamTypeItems, TRUE);
            SendMessage(hCombox, CB_LIMITTEXT, MAX_PARAM_CCH - 1, 0);
            bWParam = !bWParam;
        } while (!bWParam);

        // Timeout
        hCombox = GetDlgItem(hDlg, IDC_WNDPROP_MSG_TIMEOUT_COMBOX);
        Ctl_InitComboBox(hCombox, astWndPropMessageTimeoutItems, TRUE);
        SendMessage(hCombox, CB_SETCURSEL, 0, 0);
        SendMessage(hCombox, CB_LIMITTEXT, MAX_TIMEOUT_CCH - 1, 0);
    } else if (uMsg == WM_CTLCOLORSTATIC) {
        if (lParam == (LPARAM)GetDlgItem(hDlg, IDC_WNDPROP_MSG_MSDN_LINK))
            return (LRESULT)GetSysColorBrush(COLOR_BTNFACE);
    } else if (uMsg == WM_COMMAND) {
        if (wParam == MAKEWPARAM(IDC_WNDPROP_MSG_MSG_COMBOX, CBN_SETFOCUS)) {
            SendMessage((HWND)lParam, CB_SHOWDROPDOWN, TRUE, 0);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_MSG_WPARAM_TYPE_COMBOX, CBN_SELCHANGE) || wParam == MAKEWPARAM(IDC_WNDPROP_MSG_LPARAM_TYPE_COMBOX, CBN_SELCHANGE)) {
            INT_PTR iTypeIndex, iIndex;
            HWND    hValueCombox, hTypeCombobox = (HWND)lParam;
            BOOL    bWParam;
            INT     eParamType;
            bWParam = wParam == MAKEWPARAM(IDC_WNDPROP_MSG_WPARAM_TYPE_COMBOX, CBN_SELCHANGE);
            hValueCombox = GetDlgItem(hDlg, bWParam ? IDC_WNDPROP_MSG_WPARAM_VALUE_COMBOX : IDC_WNDPROP_MSG_LPARAM_VALUE_COMBOX);
            SendMessage(hValueCombox, CB_RESETCONTENT, 0, 0);
            EnableWindow(hValueCombox, TRUE);
            iTypeIndex = SendMessage(hTypeCombobox, CB_GETCURSEL, 0, 0);
            if (iTypeIndex != CB_ERR) {
                eParamType = (INT)SendMessage(hTypeCombobox, CB_GETITEMDATA, iTypeIndex, 0);
                if (eParamType == MsgParamTypeNotUsed) {
                    iIndex = SendMessage(hValueCombox, CB_ADDSTRING, 0, (LPARAM)I18N_GetString(I18NIndex_ParamValueNotUsed));
                    if (iIndex != CB_ERR) {
                        SendMessage(hValueCombox, CB_SETITEMDATA, iIndex, 0);
                        SendMessage(hValueCombox, CB_SETCURSEL, iIndex, 0);
                    }
                    EnableWindow(hValueCombox, FALSE);
                } else if (eParamType == MsgParamTypeBoolean) {
                    Ctl_InitComboBox(hValueCombox, astWndPropMessageBooleanItems, TRUE);
                } else if (eParamType == MsgParamTypeEnumeration) {
                    iIndex = UI_SendDlgItemMsg(hDlg, IDC_WNDPROP_MSG_MSG_COMBOX, CB_GETCURSEL, 0, 0);
                    if (iIndex != CB_ERR) {
                        PAW_MSGPARAM_INFO   pMsgParamInfo;
                        pMsgParamInfo = bWParam ? &DB_stMsgInfo[iIndex].WParamInfo : &DB_stMsgInfo[iIndex].LParamInfo;
                        if (pMsgParamInfo->EnumValue)
                            Ctl_InitComboBoxEx(hValueCombox, pMsgParamInfo->EnumValue->Items, pMsgParamInfo->EnumValue->Count, TRUE);
                    }
                }
            }
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_MSG_MSG_COMBOX, CBN_EDITCHANGE)) {
            WndPropMessageEnableLink(GetDlgItem(hDlg, IDC_WNDPROP_MSG_MSDN_LINK), FALSE);
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_MSG_MSG_COMBOX, CBN_SELCHANGE)) {
            INT_PTR iMsgIndex = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);

            // MSDN Link
            WndPropMessageEnableLink(
                GetDlgItem(hDlg, IDC_WNDPROP_MSG_MSDN_LINK),
                iMsgIndex != CB_ERR && DB_stMsgInfo[iMsgIndex].MSDNDocLink
            );

            // Type of wParam and lParam
            if (iMsgIndex != CB_ERR) {
                HWND                hTypeCombobox;
                UINT                iTypeIndex;
                PAW_MSGPARAM_INFO   pMsgParamInfo;
                UINT_PTR            iCueI18N;
                BOOL                bWParam = TRUE;
                do {
                    hTypeCombobox = GetDlgItem(hDlg, bWParam ? IDC_WNDPROP_MSG_WPARAM_TYPE_COMBOX : IDC_WNDPROP_MSG_LPARAM_TYPE_COMBOX);
                    pMsgParamInfo = bWParam ? &DB_stMsgInfo[iMsgIndex].WParamInfo : &DB_stMsgInfo[iMsgIndex].LParamInfo;
                    for (iTypeIndex = 0; iTypeIndex < ARRAYSIZE(astWndPropMessageParamTypeItems); iTypeIndex++)
                        if (astWndPropMessageParamTypeItems[iTypeIndex].Param == pMsgParamInfo->Type) {
                            Ctl_ComboBoxSetSelect(hTypeCombobox, iTypeIndex);
                            break;
                        }
                    if (iTypeIndex == ARRAYSIZE(astWndPropMessageParamTypeItems))
                        Ctl_ComboBoxSetSelect(hTypeCombobox, -1);
                    iCueI18N = pMsgParamInfo->CueI18NIndex;
                    SendMessage(
                        GetDlgItem(hDlg, bWParam ? IDC_WNDPROP_MSG_WPARAM_VALUE_COMBOX : IDC_WNDPROP_MSG_LPARAM_VALUE_COMBOX),
                        CB_SETCUEBANNER,
                        0,
                        iCueI18N == MAXUINT_PTR ? (LPARAM)L"" : (IS_INTRESOURCE(iCueI18N) ? (LPARAM)I18N_GetString(iCueI18N) : iCueI18N)
                    );
                    bWParam = !bWParam;
                } while (!bWParam);
            }
        } else if (wParam == MAKEWPARAM(IDC_WNDPROP_MSG_SEND_BTN, BN_CLICKED)) {
            HWND    hWnd;
            BOOL    bUnicode;
            UINT    _uMsg;
            WPARAM  _wParam;
            LPARAM  _lParam;
            UINT    uTimeout;
            DWORD   dwError;
            LRESULT lResult;
            hWnd = AW_GetWndPropHWnd(hDlg);

            bUnicode = IsWindowUnicode(hWnd);

            // uMsg
            BOOL    bGetMsg = FALSE;
            HWND    hMsgCombobox = GetDlgItem(hDlg, IDC_WNDPROP_MSG_MSG_COMBOX);
            INT_PTR iMsgIndex = SendMessage(hMsgCombobox, CB_GETCURSEL, 0, 0);
            if (iMsgIndex == CB_ERR) {
                TCHAR   szMsg[MAX_MSG_CCH];
                UINT    i;
                if (UI_GetWindowText(hMsgCombobox, szMsg))
                    if (!Str_ToUIntW(szMsg, &_uMsg)) {
                        Str_UpperW(szMsg);
                        for (i = 0; i < ARRAYSIZE(DB_stMsgInfo); i++) {
                            if (Str_EqualW(DB_stMsgInfo[i].Name, szMsg)) {
                                _uMsg = DB_stMsgInfo[i].Msg;
                                bGetMsg = TRUE;
                                break;
                            }
                        }
                    } else
                        bGetMsg = TRUE;
            } else
                _uMsg = ((PAW_SYSMSGINFO)SendMessage(hMsgCombobox, CB_GETITEMDATA, iMsgIndex, 0))->Msg;
            if (!bGetMsg) {
                KNS_MsgBox(hDlg, (PCWSTR)I18NIndex_Msg_uMsgErr, NULL, MB_ICONERROR);
                SetFocus(hMsgCombobox);
                return TRUE;
            }

            // wParam, lParam
            AW_MSGPARAMTYPE eType;
            BOOL    bWParam = TRUE;
            HWND    hTypeCombobox;
            WCHAR   szWParamText[MAX_PARAM_CCH];
            WCHAR   szLParamText[MAX_PARAM_CCH];
            do {
                // Get type
                eType = MsgParamTypeUnknow;
                hTypeCombobox = GetDlgItem(hDlg, bWParam ? IDC_WNDPROP_MSG_WPARAM_TYPE_COMBOX : IDC_WNDPROP_MSG_LPARAM_TYPE_COMBOX);
                INT_PTR iTypeIndex = SendMessage(hTypeCombobox, CB_GETCURSEL, 0, 0);
                if (iTypeIndex != CB_ERR)
                    eType = SendMessage(hTypeCombobox, CB_GETITEMDATA, iTypeIndex, 0);
                if (eType == MsgParamTypeUnknow) {
                    KNS_MsgBox(hDlg, (PCWSTR)I18NIndex_Msg_ParamTypeErr, NULL, MB_ICONERROR);
                    SetFocus(hTypeCombobox);
                    SendMessage(hTypeCombobox, CB_SHOWDROPDOWN, TRUE, 0);
                    return TRUE;
                }
                INT_PTR iValue, iValueIndex;
                HWND    hValueCombobox = GetDlgItem(hDlg, bWParam ? IDC_WNDPROP_MSG_WPARAM_VALUE_COMBOX : IDC_WNDPROP_MSG_LPARAM_VALUE_COMBOX);
                BOOL    bGetParam = FALSE;
                if (eType == MsgParamTypeNotUsed) {
                    iValue = 0;
                    bGetParam = TRUE;
                } else if (eType == MsgParamTypeBoolean) {
                    iValueIndex = SendMessage(hValueCombobox, CB_GETCURSEL, 0, 0);
                    if (iValueIndex != CB_ERR) {
                        iValue = SendMessage(hValueCombobox, CB_GETITEMDATA, iValueIndex, 0);
                        bGetParam = TRUE;
                    }
                } else if (eType == MsgParamTypeString) {
                    iValue = bWParam ? (INT_PTR)szWParamText : (INT_PTR)szLParamText;
                    bGetParam = TRUE;
                    if (bUnicode)
                        UI_GetWindowTextExW(hValueCombobox, (PWSTR)iValue, MAX_PARAM_CCH);
                    else
                        UI_GetWindowTextExA(hValueCombobox, (PSTR)iValue, MAX_PARAM_CCH);
                } else {
                    TCHAR   szParamText[MAX_PARAM_CCH];
                    INT     iCchParam;
                    iCchParam = UI_GetWindowText(hValueCombobox, szParamText);
                    if (eType == MsgParamTypeNum) {
                        bGetParam = Str_ToIntEx(szParamText, bWParam, 0, &iValue, sizeof(iValue));
                    } else if (eType == MsgParamTypeHandle) {
                        if (Str_HexToInt(szParamText, &iValue) &&
                            (IsWindow((HWND)iValue) || GetObjectType((HGDIOBJ)iValue)))
                            bGetParam = TRUE;
                    } else if (eType == MsgParamTypeRaw) {
                        if (iCchParam && !(iCchParam & 1)) {
                            iValue = (INT_PTR)Mem_Alloc(iCchParam >> 1);
                            if (iValue) {
                                INT     i = 0;
                                PBYTE   pBuff = (PBYTE)iValue;
                                CHAR    ch, c;
                                do {
                                    c = (CHAR)szParamText[i];
                                    if (c >= '0' && c <= '9')
                                        c -= '0';
                                    else if (c >= 'a' && c <= 'f')
                                        c = c - 'a' + 10;
                                    else if (c >= 'A' && c <= 'F')
                                        c = c - 'A' + 10;
                                    else
                                        break;
                                    if (i & 1) {
                                        ch = (ch << 4) | c;
                                        *pBuff++ = ch;
                                    } else
                                        ch = c;
                                } while (++i < iCchParam);
                                if (i == iCchParam)
                                    bGetParam = TRUE;
                            }
                        }
                    }
                }
                if (!bGetParam) {
                    KNS_MsgBox(hDlg, (PCWSTR)I18NIndex_Msg_ParamValueErr, NULL, MB_ICONERROR);
                    SetFocus(hValueCombobox);
                    return TRUE;
                } else {
                    if (bWParam)
                        _wParam = (WPARAM)iValue;
                    else
                        _lParam = (LPARAM)iValue;
                }
                bWParam = !bWParam;
            } while (!bWParam);

            // Method
            HWND    hMethodCombobox = GetDlgItem(hDlg, IDC_WNDPROP_MSG_METHOD_COMBOX);
            INT_PTR iMethod = SendMessage(
                hMethodCombobox,
                CB_GETITEMDATA,
                SendMessage(hMethodCombobox, CB_GETCURSEL, 0, 0),
                0);

            // Timeout
            TCHAR   szTimeout[MAX_TIMEOUT_CCH];
            HWND    hTimeoutCombobox = GetDlgItem(hDlg, IDC_WNDPROP_MSG_TIMEOUT_COMBOX);
            INT_PTR iTimeoutIndex = SendMessage(hTimeoutCombobox, CB_GETCURSEL, 0, 0);
            if (iTimeoutIndex == CB_ERR &&
                (!UI_GetWindowText(hTimeoutCombobox, szTimeout) || !Str_ToUInt(szTimeout, &uTimeout))
                ) {
                KNS_MsgBox(hDlg, (PCWSTR)I18NIndex_Msg_TimeoutErr, NULL, MB_ICONERROR);
                SetFocus(hTimeoutCombobox);
                return TRUE;
            } else
                uTimeout = (UINT)(UINT_PTR)SendMessage(hTimeoutCombobox, CB_GETITEMDATA, iTimeoutIndex, 0);
            UI_GetDlgItemText(hDlg, IDC_WNDPROP_MSG_TIMEOUT_COMBOX, szTimeout);

            // Send
            // TODO
        }
    } else if (uMsg == WM_NOTIFY) {
        LPNMHDR pnmhdr = (LPNMHDR)lParam;
        if (pnmhdr->idFrom == IDC_WNDPROP_MSG_MSDN_LINK && pnmhdr->code == NM_CLICK) {
            INT_PTR iMsgIndex = UI_SendDlgItemMsg(hDlg, IDC_WNDPROP_MSG_MSG_COMBOX, CB_GETCURSEL, 0, 0);
            if (iMsgIndex != CB_ERR && DB_stMsgInfo[iMsgIndex].MSDNDocLink)
                UI_ShellExec(DB_stMsgInfo[iMsgIndex].MSDNDocLink, NULL, UIShellExecOpen, SW_SHOWNORMAL, NULL);
        }
    } else
        return FALSE;

    return TRUE;
}