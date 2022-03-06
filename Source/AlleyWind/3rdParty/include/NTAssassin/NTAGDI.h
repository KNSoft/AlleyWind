#pragma once

#include "NTAssassin.h"

typedef struct _GDI_SNAPSHOT {
    HDC     DC;
    HBITMAP Bitmap;
    HBITMAP OriginalBitmap;
    POINT   Position;
    SIZE    Size;
} GDI_SNAPSHOT, * PGDI_SNAPSHOT;

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
  * @param[out, opt] Buffer Pointer to buffer to receive bitmap data
  * @return Returns size of data in bytes
  */
NTA_API UINT NTAPI GDI_WriteBitmap(HDC DC, HBITMAP Bitmap, PVOID Buffer);

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
NTA_API HFONT NTAPI GDI_CreateFont(LONG FontSize, LONG FontWeight, PCWSTR FontName);

/**
  * @brief Retrieves information for the font
  * @param[in] Font Handle to the font
  * @param[out] FontInfo Pointer to the LOGFONTW structure receives information
  * @return Number of bytes stored or 0 if failed
  * @see "GetObject"
  */
NTA_API INT NTAPI GDI_GetFont(HFONT Font, PLOGFONTW FontInfo);

/**
  * @see "DrawIcon"
  */
NTA_API BOOL NTAPI GDI_DrawIcon(HDC DC, HICON Icon, INT X, INT Y, INT CX, INT CY);

/**
  * @brief Creates snapshot for specified window
  * @param[in] Window Handle to the window, or NULL to create snapshot for screen
  * @param[in] Snapshot Pointer to a GDI_SNAPSHOT structure receives the snapshot resources and information
  * @return Returns TRUE if succeeded, or FALSE if failed
  * @note Snapshot should be deleted by "GDI_DeleteSnapshot" when no longer to be used
  */
NTA_API BOOL NTAPI GDI_CreateSnapshot(HWND Window, PGDI_SNAPSHOT Snapshot);

/**
  * @brief Deletes snapshot created by "GDI_CreateSnapshot"
  * @param[in] ScreenSnapshot Pointer to a GDI_SNAPSHOT structure to delete
  * @return Returns TRUE if succeeded, or FALSE if failed
  */
NTA_API BOOL NTAPI GDI_DeleteSnapshot(PGDI_SNAPSHOT Snapshot);