#pragma once

#include "NTAssassin.h"

typedef struct _GDI_SNAPSHOT {
    HDC     DC;
    HBITMAP Bitmap;
    HBITMAP OriginalBitmap;
    POINT   Position;
    SIZE    Size;
} GDI_SNAPSHOT, *PGDI_SNAPSHOT;

/// <summary>
/// Fills a rectangle area with single color
/// </summary>
/// <seealso cref="CDC::FillSolidRect"/>
/// <returns>TRUE if succeeded, or FALSE if failed</returns>
NTA_API BOOL NTAPI GDI_FillSolidRect(HDC DC, _In_ PRECT Rect, COLORREF Color);

/// <summary>
/// Draws a rectangle frame with current brush and specified ROP
/// </summary>
/// <param name="DC">Handle to the DC</param>
/// <param name="Rect">Pointer to a RECT specifies rectangle area</param>
/// <param name="Width">Width of frame, positive number indicates outer frame, negative indicates inner frame</param>
/// <param name="ROP">ROP, see also <c>PatBlt</c></param>
/// <returns>TRUE if succeeded, or FALSE if failed</returns>
NTA_API BOOL NTAPI GDI_FrameRect(HDC DC, PRECT Rect, INT Width, DWORD ROP);

/// <summary>
/// Writes bitmap (DDB) data to buffer
/// <see href="https://docs.microsoft.com/en-US/windows/win32/gdi/storing-an-image">Storing an Image - MSDN</see>
/// <see href="https://docs.microsoft.com/en-us/windows/win32/gdi/bitmap-storage">Bitmap Storage - MSDN</see>
/// </summary>
/// <param name="DC">Handle to the DC</param>
/// <param name="Bitmap">Handle to the bitmap</param>
/// <param name="Buffer">Pointer to the buffer receives bitmap data, NULL if gets required size only</param>
/// <param name="BufferSize">Size of buffer, ignored if Buffer is NULL when acquire required size</param>
/// <returns>Size of data write in bytes, or size required if Buffer is NULL</returns>
/// <remarks>To writes a DIB, use "GDIP_LoadImageFromBitmap" and "GDIP_SaveImageToBMPFile" instead</remarks>
NTA_API UINT NTAPI GDI_WriteBitmap(HDC DC, HBITMAP Bitmap, _Out_writes_bytes_opt_(BufferSize) PVOID Buffer, UINT BufferSize);

/// <summary>
/// Initializes ENUMLOGFONTEXDVW structure members EXCEPT LOGFONT (elfEnumLogfontEx.elfLogFont)
/// </summary>
/// <param name="InternalFontInfo">Pointer to the ENUMLOGFONTEXDVW structure</param>
NTA_API VOID NTAPI GDI_InitInternalFontInfo(_Out_ PENUMLOGFONTEXDVW InternalFontInfo);

/// <summary>
/// Initializes LOGFONTW structure with default and specified attributes
/// </summary>
/// <param name="FontInfo">Pointer to the LOGFONTW structure</param>
/// <param name="FontSize">Font size</param>
/// <param name="FontWeight">Font weight</param>
/// <param name="FontName">Font's famliy name, or NULL to use the first font matches attributes</param>
NTA_API VOID NTAPI GDI_SetFontInfo(_Out_ PLOGFONTW FontInfo, LONG FontSize, LONG FontWeight, _In_opt_z_ PCWSTR FontName);

/// <summary>
/// Creates a logical font
/// </summary>
/// <seealso cref="CreateFont"/>
/// <returns>Handle to the logical font, or NULL if failed</returns>
NTA_API HFONT NTAPI GDI_CreateFont(LONG FontSize, LONG FontWeight, _In_opt_z_ PCWSTR FontName);

/// <summary>
/// Retrieves information for the font
/// </summary>
/// <seealso cref="GetObject"/>
/// <param name="Font">Handle to the font</param>
/// <param name="FontInfo">Pointer to the LOGFONTW structure receives information</param>
/// <returns>Number of bytes stored or 0 if failed</returns>
NTA_API INT NTAPI GDI_GetFont(HFONT Font, PLOGFONTW FontInfo);

/// <summary>
/// Draws an icon
/// </summary>
/// <seealso cref="DrawIcon"/>
NTA_API BOOL NTAPI GDI_DrawIcon(HDC DC, _In_ HICON Icon, INT X, INT Y, INT CX, INT CY);

/// <summary>
/// Creates snapshot for specified window
/// </summary>
/// <param name="Window">Handle to the window, or NULL to creates snapshot for screen</param>
/// <param name="Snapshot">Pointer to a GDI_SNAPSHOT structure receives the snapshot resources and information</param>
/// <returns>TRUE if succeeded, or FALSE if failed</returns>
/// <remarks>Snapshot should be deleted by <c>GDI_DeleteSnapshot</c> when no longer to be used</remarks>
NTA_API BOOL NTAPI GDI_CreateSnapshot(HWND Window, _Out_ PGDI_SNAPSHOT Snapshot);

/// <summary>
/// Deletes snapshot created by <c>GDI_CreateSnapshot</c>
/// </summary>
/// <param name="Snapshot">Pointer to a GDI_SNAPSHOT structure to delete</param>
/// <returns>TRUE if succeeded, or FALSE if failed</returns>
NTA_API BOOL NTAPI GDI_DeleteSnapshot(_In_ PGDI_SNAPSHOT Snapshot);
