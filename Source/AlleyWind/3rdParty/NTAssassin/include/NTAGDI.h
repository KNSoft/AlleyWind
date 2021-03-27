#pragma once

#include "NTAssassin.h"

/**
  * @brief Fills a rectangle area with single color
  * @see "CDC::FillSolidRect"
  */
NTA_API BOOL NTAPI GDI_FillSolidRect(HDC hDC, LPCRECT lprc, COLORREF cr);

/**
  * @brief Draws a rectangle frame with current brush and specified ROP
  * @param[in] hDC Handle to the DC
  * @param[in] lprc Pointer to a RECT specifies rectangle area
  * @param[in] iWidth Width of frame, positive number indicates outer frame, negative indicates inner frame
  * @return Returns TRUE if succeeded, otherwise returns FALSE
  */
NTA_API BOOL NTAPI GDI_FrameRect(HDC hDC, LPRECT lprc, INT iWidth, DWORD dwROP);

NTA_API NTSTATUS NTAPI GDI_WriteBitmap(HDC hDC, HBITMAP hBmp, LPVOID lpBuff, SIZE_T uBuffSize, PSIZE_T lpBytesWritten);