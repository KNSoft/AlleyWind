#pragma once

#include "AlleyWind.h"

EXTERN_C LPCWSTR lpszDVE[7];

typedef struct _AW_SYSCLASSINFO {
    LPTSTR  ClassName;
    union {
        UINT_PTR    I18NIndex;
        LPWSTR      DisplayName;
    };
    PDLG_VALUEEDITOR_CONST  StyleConsts;
    UINT                    StyleConstsCount;
} AW_SYSCLASSINFO, * PAW_SYSCLASSINFO;

typedef enum _AW_VALUETYPE {
    AWValueStyle,
    AWValueExStyle,
    AWValueClass
} AW_VALUETYPE, *PAW_VALUETYPE;

PAW_SYSCLASSINFO AW_DBFindSysClassInfoByName(LPTSTR lpszClassName);
PAW_SYSCLASSINFO AW_DBFindSysClassInfo(HWND hWnd);

BOOL AW_DBEditValue(HWND hDlg, HWND hWnd, AW_VALUETYPE eType, PDWORD lpdwValue);