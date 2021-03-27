#pragma once

#include "NTAssassin.h"

#define DVE_TYPE_COMBINATION    0x1
#define DVE_TYPE_ENUMERATION    0x2

#define DVE_VALUE_HEXDWORD      0x100
#define DVE_VALUE_HEXQWORD      0x200

typedef struct _DLG_VALUEEDITOR_CONSTW {
    QWORD   Value;
    LPCWSTR Name;
    LPCWSTR Info;
} DLG_VALUEEDITOR_CONSTW, * PDLG_VALUEEDITOR_CONSTW;

typedef struct _DLG_VALUEEDITORW {
    HWND                    hwndOwner;
    DWORD                   Flags;
    LPCWSTR                 *lpstr;     // ["Title", "Reset", "OK", "Member", "Value", "Info", "Unknow"]
    PDLG_VALUEEDITOR_CONSTW lpstConsts;
    UINT                    uConsts;
    QWORD                   qwValue;
    QWORD                   Reserved;   // Reserved, do not use
} DLG_VALUEEDITORW, * PDLG_VALUEEDITORW;

NTA_API BOOL NTAPI Dlg_ValueEditorW(HWND hwndOwner, DWORD dwFlags, LPCWSTR *lpsz, LPQWORD lpqwValue, PDLG_VALUEEDITOR_CONSTW lpstConsts, UINT uConsts);
#ifdef UNICODE
#define Dlg_ValueEditor Dlg_ValueEditorW
#define DLG_VALUEEDITOR DLG_VALUEEDITORW
#define PDLG_VALUEEDITOR PDLG_VALUEEDITORW
#define DLG_VALUEEDITOR_CONST DLG_VALUEEDITOR_CONSTW
#define PDLG_VALUEEDITOR_CONST PDLG_VALUEEDITOR_CONSTW
#else
#define Dlg_ValueEditor Dlg_ValueEditorA
#define DLG_VALUEEDITOR DLG_VALUEEDITORA
#define PDLG_VALUEEDITOR PDLG_VALUEEDITORA
#define DLG_VALUEEDITOR_CONST DLG_VALUEEDITOR_CONSTA
#define PDLG_VALUEEDITOR_CONST PDLG_VALUEEDITOR_CONSTA
#endif