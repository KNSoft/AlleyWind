#pragma once

#include "NTAssassin.h"

#define DVE_TYPE_COMBINATION    0x1
#define DVE_TYPE_ENUMERATION    0x2

#define DVE_VALUE_HEXDWORD      0x100
#define DVE_VALUE_HEXQWORD      0x200

typedef struct _DLG_VALUEEDITOR_CONST {
    QWORD   Value;
    PCWSTR  Name;
    PCWSTR  Info;
} DLG_VALUEEDITOR_CONST, *PDLG_VALUEEDITOR_CONST;

/// <summary>
/// Creates a dialog box that enables the user to edit a value as combination or enumeration
/// </summary>
/// <param name="Owner">Handle to the owner window</param>
/// <param name="Flags">Can be combined with one of DVE_TYPE_XXX and one of DVE_VALUE_XXX</param>
/// <param name="Strings">String table to display text on the dialog, default strings is ["Title", "Reset", "OK", "Member", "Value", "Info", "Unknow"]</param>
/// <param name="Value">Pointer to the value to set initial value and receive the result value</param>
/// <param name="Consts">Pointer to a DLG_VALUEEDITOR_CONST structures array, contains constant members of value</param>
/// <param name="ConstCount">Number of constants in Consts parameter</param>
/// <returns>TRUE if a value was confirmed, or FALSE if user canceled or an error occured</returns>
NTA_API BOOL NTAPI Dlg_ValueEditorEx(HWND Owner, _In_ DWORD Flags, _In_opt_ PCWSTR* Strings, _Inout_ PQWORD Value, _In_ PDLG_VALUEEDITOR_CONST Consts, _In_ UINT ConstCount);

#define Dlg_ValueEditor(Owner, Flags, Strings, Value, Consts) Dlg_ValueEditorEx(Owner, Flags, Strings, Value, Consts, ARRAYSIZE(Consts))