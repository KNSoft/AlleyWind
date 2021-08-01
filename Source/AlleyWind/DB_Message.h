#pragma once

#include "AlleyWind.h"

typedef enum _AW_MSGPARAMTYPE {
    MsgParamTypeUnknow,
    // wParam and lParam types
    MsgParamTypeNotUsed,
    MsgParamTypeNum,
    MsgParamTypeBoolean,
    MsgParamTypeString,
    MsgParamTypeHandle,
    MsgParamTypeRaw,
    // Custom types
    MsgParamTypeEnumeration,
    MsgParamTypeCombination,
    MsgParamTypeUseCallback,
    MsgParamTypeOthers
} AW_MSGPARAMTYPE, * PAW_MSGPARAMTYPE;

typedef struct _AW_MSGPARAMENUMITEM {
    union {
        UINT_PTR    I18NIndex;
        PCTSTR      Text;
    };
    LONG_PTR        Value;
} AW_MSGPARAMENUMITEM, * PAW_MSGPARAMENUMITEM;

typedef struct _AW_MSGPARAMENUM {
    PCTL_COMBOBOXCTL_ITEM   Items;
    UINT                    Count;
} AW_MSGPARAMENUM, * PAW_MSGPARAMENUM;

typedef struct _AW_MSGPARAM_INFO {
    AW_MSGPARAMTYPE Type;
    union {
        UINT_PTR    CueI18NIndex;
        PWSTR       CueText;
    };
    union {
        PAW_MSGPARAMENUM    EnumValue;
        PVOID               Callback;
    }; // Reserved
} AW_MSGPARAM_INFO, * PAW_MSGPARAM_INFO;

typedef struct _AW_SYSMSGINFO {
    UINT                Msg;
    PTSTR               Name;
    AW_MSGPARAM_INFO    WParamInfo;
    AW_MSGPARAM_INFO    LParamInfo;
    AW_MSGPARAM_INFO    RetValInfo;
    PCTSTR              MSDNDocLink;
} AW_SYSMSGINFO, * PAW_SYSMSGINFO;

EXTERN_C AW_SYSMSGINFO DB_stMsgInfo[246];