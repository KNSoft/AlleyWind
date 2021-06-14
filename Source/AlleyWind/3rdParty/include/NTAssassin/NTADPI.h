// High-DPI support

#pragma once

#include "NTAssassin\NTAssassin.h"

/**
  * @brief Gets DPI of window
  * @param[in] Window Handle to the window
  * @param[in] DPIX Pointer to an UINT variable to receive DPI-X
  * @param[in] DPIY Pointer to an UINT variable to receive DPI-Y
  * @return Returns TRUE if DPI values returned by dialogue subclassed by DPI_SetAutoAdjustSubclass, or FALSE if returned by system
  */
NTA_API BOOL NTAPI DPI_FromWindow(HWND Window, PUINT DPIX, PUINT DPIY);

/**
  * @brief Scales a value according to given DPI
  * @param[in, out] Value Pointer to the RECT structure to be scaled
  * @param[in] OldDPI Old DPI value
  * @param[in] NewDPI New DPI value
  */
NTA_API VOID NTAPI DPI_Scale(PINT Value, UINT OldDPI, UINT NewDPI);

/**
  * @brief Scales a value according to given DPI
  * @param[in, out] Rect Pointer to the RECT structure to be scaled
  * @param[in] OldDPIX Old DPI-X value
  * @param[in] NewDPIX New DPI-X value
  * @param[in] OldDPIY Old DPI-Y value
  * @param[in] NewDPIY New DPI-Y value
  */
VOID NTAPI DPI_ScaleRect(PRECT Rect, UINT OldDPIX, UINT NewDPIX, UINT OldDPIY, UINT NewDPIY);

/**
  * @see "IsProcessDPIAware"
  * @return Returns TRUE if the process is DPI aware, or FALSE if not or failed.
  */
NTA_API BOOL NTAPI DPI_IsAware();

/**
  * @brief Subclasses a dialog box to support High-DPI
  * @param[in] Dialog Handle to the dialog box
  * @param[in, opt] Font Handle to the font apply to the dialog box
  * @return Returns TRUE if subclass successfully, or FALSE if failed
  * @see "SetDialogDpiChangeBehavior"
  */
NTA_API BOOL NTAPI DPI_SetAutoAdjustSubclass(HWND Dialog, HFONT Font);