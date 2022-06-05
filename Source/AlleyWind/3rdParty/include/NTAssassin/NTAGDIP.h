#pragma once

#include "NTAssassin.h"

typedef PVOID PGDIP_IMAGE, PGDIP_GRAPHICS, PGDIP_BRUSH, PGDIP_PATH;

typedef DWORD ARGB;

// Makes ARGB value (AARRGGBB)
#define MAKE_ARGB(a, r, g, b) ((ARGB) (b) <<  0) | ((ARGB)(g) << 8) | ((ARGB)(r) << 16) | ((ARGB)(a) << 24)

#pragma region C-style wrappers of Gdiplus.h

typedef enum _GDIP_TIFFENCODER_PARAMVALUE {
    TIFF_ParamValue_CompressionUnused,
    TIFF_ParamValue_CompressionLZW = 2,
    TIFF_ParamValue_CompressionCCITT3 = 3,
    TIFF_ParamValue_CompressionCCITT4 = 4,
    TIFF_ParamValue_CompressionRle = 5,
    TIFF_ParamValue_CompressionNone = 6,
    TIFF_ParamValue_CompressionMax
} GDIP_TIFFENCODER_PARAMVALUE, *PGDIP_TIFFENCODER_PARAMVALUE;

typedef enum _GDIP_SMOOTHINGMODE {
    GDIP_SmoothingModeDefault = 0x00,
    GDIP_SmoothingModeHighSpeed = 0x01,
    GDIP_SmoothingModeHighQuality = 0x02,
    GDIP_SmoothingModeNone = 0x03,
    GDIP_SmoothingModeAntiAlias8x4 = 0x04,
    GDIP_SmoothingModeAntiAlias8x8 = 0x05
} GDIP_SMOOTHINGMODE, *PGDIP_SMOOTHINGMODE;

NTA_API BOOL NTAPI GDIP_Startup(PULONG_PTR Token);
NTA_API VOID NTAPI GDIP_Shutdown(ULONG_PTR Token);

NTA_API PGDIP_GRAPHICS NTAPI GDIP_CreateFromHDC(HDC DC);
NTA_API BOOL NTAPI GDIP_DeleteGraphics(PGDIP_GRAPHICS Graphics);
NTA_API BOOL NTAPI GDIP_SetGraphicsSmoothingMode(PGDIP_GRAPHICS Graphics, GDIP_SMOOTHINGMODE Mode);
NTA_API BOOL NTAPI GDIP_DrawImage(PGDIP_GRAPHICS Graphics, PGDIP_IMAGE Image, INT X, INT Y);
NTA_API BOOL NTAPI GDIP_DrawImageRect(PGDIP_GRAPHICS Graphics, PGDIP_IMAGE Image, INT X, INT Y, INT Width, INT Height);
NTA_API BOOL NTAPI GDIP_GetImageDimension(PGDIP_IMAGE Image, PUINT Width, PUINT Height);

NTA_API PGDIP_BRUSH NTAPI GDIP_CreateSolidBrush(ARGB Color);
NTA_API BOOL NTAPI GDIP_FillRect(PGDIP_GRAPHICS Graphics, PGDIP_BRUSH Brush, INT X, INT Y, INT Width, INT Height);
NTA_API BOOL NTAPI GDIP_DeleteBrush(PGDIP_BRUSH Brush);
NTA_API PGDIP_PATH NTAPI GDIP_CreatePath();

NTA_API PGDIP_IMAGE NTAPI GDIP_LoadImageFromFile(PCWSTR FileName);
NTA_API PGDIP_IMAGE NTAPI GDIP_LoadImageFromBitmap(HBITMAP Bitmap);
NTA_API BOOL NTAPI GDIP_DisposeImage(PGDIP_IMAGE Image);

#pragma endregion

/// <summary>
/// Loads an image file from buffer
/// </summary>
/// <param name="Buffer">Buffer to the image file data</param>
/// <param name="Size">Size of buffer</param>
/// <returns>Pointer to the image created, or NULL if failed</returns>
NTA_API PGDIP_IMAGE NTAPI GDIP_LoadImageFromBuffer(_In_reads_bytes_(Size) PVOID Buffer, _In_ UINT Size);

/// <summary>
/// Saves image to file in different format
/// </summary>
/// <param name="Image">Pointer to the image</param>
/// <param name="FilePath">Path save to</param>
/// <returns>TRUE if succeeded, or FALSE if failed</returns>
NTA_API BOOL NTAPI GDIP_SaveImageToBMPFile(PGDIP_IMAGE Image, _In_z_ PCWSTR FilePath);
NTA_API BOOL NTAPI GDIP_SaveImageToGIFFile(PGDIP_IMAGE Image, _In_z_ PCWSTR FilePath);
NTA_API BOOL NTAPI GDIP_SaveImageToPNGFile(PGDIP_IMAGE Image, _In_z_ PCWSTR FilePath);
NTA_API BOOL NTAPI GDIP_SaveImageToJPEGFile(PGDIP_IMAGE Image, _In_z_ PCWSTR FilePath, INT Quality);
NTA_API BOOL NTAPI GDIP_SaveImageToTIFFFile(PGDIP_IMAGE Image, _In_z_ PCWSTR FilePath, GDIP_TIFFENCODER_PARAMVALUE Compression, INT ColorDepth);