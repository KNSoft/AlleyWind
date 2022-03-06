#pragma once

#include "NTAssassin.h"

typedef struct _DLG_RECTEDITOR {
    HWND    hwndOwner;
    PCWSTR* lpstr;     // ["Title", "Reset", "OK", "Left", "Top", "Right", "Bottom", "Width", "Height"]
    LPRECT  lprc;
} DLG_RECTEDITOR, * PDLG_RECTEDITOR;

/**
  * @brief Edits RECT structure
  * @param[in] Strings String table to display text on the dialog, default strings is ["Title", "Reset", "OK", "Left", "Top", "Right", "Bottom", "Width", "Height"]
  * @param[in, out] Rect Pointer to the RECT structure
  * @return Returns BOOL
  */
NTA_API BOOL NTAPI Dlg_RectEditor(HWND Owner, PCWSTR* Strings, PRECT Rect);