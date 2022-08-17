#pragma once

#include "NTADef.h"

/// <summary>
/// Creates a dialog box that enables the user to edit a RECT structure
/// </summary>
/// <param name="Owner">Handle to the owner window</param>
/// <param name="Strings">String table to display text on the dialog, default strings is ["Title", "Reset", "OK", "Left", "Top", "Right", "Bottom", "Width", "Height"]</param>
/// <param name="Rect">Pointer to the RECT structure to set initial values and receive the result values</param>
/// <returns>TRUE if a RECT was confirmed, or FALSE if user canceled or an error occured</returns>
NTA_API BOOL NTAPI Dlg_RectEditor(HWND Owner, _In_opt_ PCWSTR* Strings, _Inout_ PRECT Rect);
