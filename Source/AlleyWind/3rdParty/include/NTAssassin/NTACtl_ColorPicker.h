#pragma once

#include "NTAssassin.h"

// No color specified in color picker yet
#define CTL_COLORPICKER_NOCOLOR 0xFF000000

/// <summary>
/// Subclasses a button control to be a RGB color picker
/// </summary>
/// <param name="ButtonCtl">Handle to the button control</param>
/// <param name="Color"> Initial color, or CTL_COLORPICKER_NOCOLOR</param>
/// <returns>TRUE if succeeded, or FALSE if failed, no error code reports due to SetWindowSubclass does</returns>
NTA_API BOOL NTAPI Ctl_SetColorPickerSubclass(HWND ButtonCtl, COLORREF Color);

/// <summary>
/// Gets RGB value of color picker subclassed by "Ctl_SetColorPickerSubclass"
/// </summary>
/// <param name="ButtonCtl">Handle to the button control</param>
/// <returns>RGB value or CTL_COLORPICKER_NOCOLOR</returns>
NTA_API COLORREF NTAPI Ctl_GetColorPickerValue(HWND ButtonCtl);

/// <summary>
/// Sets RGB value of color picker subclassed by "Ctl_SetColorPickerSubclass"
/// </summary>
/// <param name="ButtonCtl">Handle to the button control</param>
/// <param name="Color">RGB value to set or CTL_COLORPICKER_NOCOLOR</param>
/// <returns>TRUE if succeeded, or FALSE if failed, error code storaged in last ERROR</returns>
NTA_API BOOL NTAPI Ctl_SetColorPickerValue(HWND ButtonCtl, COLORREF Color);
