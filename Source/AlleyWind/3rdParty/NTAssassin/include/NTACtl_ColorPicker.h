#pragma once

#include "NTAssassin.h"

// No color specified in color picker yet
#define CTL_COLORPICKER_NOCOLOR 0xFF000000

/**
  * @brief Subclasses a button control to be a RGB color picker
  * @param[in] ButtonCtl Handle to the button control
  * @param[in] Color Initial color, or CTL_COLORPICKER_NOCOLOR
  * @return Returns BOOL
  */
NTA_API BOOL NTAPI Ctl_SetColorPickerSubclass(HWND ButtonCtl, COLORREF Color);

/**
  * @brief Gets RGB value of color picker subclassed by "Ctl_SetColorPickerSubclass"
  * @param[in] ButtonCtl Handle to the button control
  * @return Returns RGB value or CTL_COLORPICKER_NOCOLOR
  */
NTA_API COLORREF NTAPI Ctl_GetColorPickerValue(HWND ButtonCtl);

/**
  * @brief Sets RGB value of color picker subclassed by "Ctl_SetColorPickerSubclass"
  * @param[in] ButtonCtl Handle to the button control
  * @param[in] Color RGB value to set or CTL_COLORPICKER_NOCOLOR
  * @return Returns BOOL
  */
NTA_API BOOL NTAPI Ctl_SetColorPickerValue(HWND ButtonCtl, COLORREF Color);