#pragma once

#include "NTAssassin.h"

/**
  * @brief Fills a rectangle area with single color
  * @see "CDC::FillSolidRect"
  */
NTA_API BOOL NTAPI GDI_FillSolidRect(HDC DC, PRECT Rect, COLORREF Color);

/**
  * @brief Draws a rectangle frame with current brush and specified ROP
  * @param[in] DC Handle to the DC
  * @param[in] Rect Pointer to a RECT specifies rectangle area
  * @param[in] Width Width of frame, positive number indicates outer frame, negative indicates inner frame
  * @param[in] ROP ROP, see also "PatBlt"
  * @return Returns TRUE if succeeded, otherwise returns FALSE
  */
NTA_API BOOL NTAPI GDI_FrameRect(HDC DC, PRECT Rect, INT Width, DWORD ROP);

/**
  * @brief Writes bitmap data to buffer
  * @param[in] DC Handle to the DC
  * @param[in] Bitmap Handle to the bitmap
  * @param[out] Buffer Pointer to buffer to receive bitmap data
  * @param[in] BufferSize Size in bytes of buffer
  * @param[out, opt] BytesWritten Pointer to the variable receives the number of bytes written
  * @return Returns NTSTATUS
  */
NTA_API NTSTATUS NTAPI GDI_WriteBitmap(HDC DC, HBITMAP Bitmap, PVOID Buffer, SIZE_T BufferSize, PSIZE_T BytesWritten);

/**
  * @brief Initializes ENUMLOGFONTEXDVW structure members EXCEPT LOGFONT (elfEnumLogfontEx.elfLogFont)
  * @param[out] InternalFontInfo Pointer to the ENUMLOGFONTEXDVW structure
  */
NTA_API VOID NTAPI GDI_InitInternalFontInfo(PENUMLOGFONTEXDVW InternalFontInfo);

/**
  * @brief Initializes LOGFONTW structure with default and specified attributes
  * @param[out] FontInfo Pointer to the LOGFONTW structure
  * @param[in] FontSize Font size
  * @param[in] FontWeight Font weight
  * @param[in] FontName Font's famliy name, or NULL to use the first font matches attributes
  * @see "CreateFont"
  */
NTA_API VOID NTAPI GDI_SetFontInfo(PLOGFONTW FontInfo, LONG FontSize, LONG FontWeight, PCWSTR FontName);

/**
  * @brief Creates a logical font
  * @return Handle to the logical font, or NULL if failed
  * @see "CreateFont"
  */
HFONT NTAPI GDI_CreateFont(LONG FontSize, LONG FontWeight, PCWSTR FontName);

/**
  * @brief Retrieves information for the font
  * @param[in] Font Handle to the font
  * @param[out] FontInfo Pointer to the LOGFONTW structure receives information
  * @return Number of bytes stored or 0 if failed
  * @see "GetObject"
  */
INT NTAPI GDI_GetFont(HFONT Font, PLOGFONTW FontInfo);