#pragma once

#include "NTAssassin\NTAssassin.h"

#define DVE_TYPE_COMBINATION    0x1
#define DVE_TYPE_ENUMERATION    0x2

#define DVE_VALUE_HEXDWORD      0x100
#define DVE_VALUE_HEXQWORD      0x200

typedef struct _DLG_VALUEEDITOR_CONST {
    QWORD   Value;
    PCWSTR  Name;
    PCWSTR  Info;
} DLG_VALUEEDITOR_CONST, * PDLG_VALUEEDITOR_CONST;

typedef struct _DLG_VALUEEDITOR {
    HWND                    hwndOwner;
    DWORD                   Flags;
    PCWSTR                  *lpstr;     // ["Title", "Reset", "OK", "Member", "Value", "Info", "Unknow"]
    PDLG_VALUEEDITOR_CONST  lpstConsts;
    UINT                    uConsts;
    QWORD                   qwValue;
    QWORD                   Reserved;   // Reserved, do not use
} DLG_VALUEEDITOR, * PDLG_VALUEEDITOR;

/**
  * @brief Edits value as combination or enumeration
  * @param[in] Owner Handle to owner window
  * @param[in] Flags Can be combined with one of DVE_TYPE_XXX and one of DVE_VALUE_XXX
  * @param[in] Strings String table to display text on the dialog, default strings is ["Title", "Reset", "OK", "Member", "Value", "Info", "Unknow"]
  * @param[in, out] Value Pointer to the value
  * @param[in] Consts Constant members of value
  * @param[in] ConstCount Number of constants in Consts parameter
  * @return Returns BOOL
  */
NTA_API BOOL NTAPI Dlg_ValueEditorEx(HWND Owner, DWORD Flags, PCWSTR *Strings, PQWORD Value, PDLG_VALUEEDITOR_CONST Consts, UINT ConstCount);
#define Dlg_ValueEditor(Owner, Flags, Strings, ValuePointer, Consts) Dlg_ValueEditorEx(Owner, Flags, Strings, ValuePointer, Consts, ARRAYSIZE(Consts))