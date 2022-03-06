#pragma once

#include "NTAssassin.h"

typedef PVOID PGDIP_IMAGE;

typedef enum _GDIP_TIFFENCODER_PARAMVALUE {
    TIFF_ParamValue_CompressionUnused,
    TIFF_ParamValue_CompressionLZW = 2,
    TIFF_ParamValue_CompressionCCITT3 = 3,
    TIFF_ParamValue_CompressionCCITT4 = 4,
    TIFF_ParamValue_CompressionRle = 5,
    TIFF_ParamValue_CompressionNone = 6,
    TIFF_ParamValue_CompressionMax
} GDIP_TIFFENCODER_PARAMVALUE, *PGDIP_TIFFENCODER_PARAMVALUE;

NTA_API BOOL NTAPI GDIP_Startup(PULONG_PTR Token);
NTA_API PGDIP_IMAGE NTAPI GDIP_LoadImageFromFile(PCWSTR FileName);
NTA_API PGDIP_IMAGE NTAPI GDIP_LoadImageFromBitmap(HBITMAP Bitmap);
NTA_API BOOL NTAPI GDIP_DisposeImage(PGDIP_IMAGE Image);
NTA_API BOOL NTAPI GDIP_SaveImageToBMPFile(PGDIP_IMAGE Image, PCWSTR FileName);
NTA_API BOOL NTAPI GDIP_SaveImageToGIFFile(PGDIP_IMAGE Image, PCWSTR FileName);
NTA_API BOOL NTAPI GDIP_SaveImageToPNGFile(PGDIP_IMAGE Image, PCWSTR FileName);
NTA_API BOOL NTAPI GDIP_SaveImageToJPEGFile(PGDIP_IMAGE Image, PCWSTR FileName, INT Quality);
NTA_API BOOL NTAPI GDIP_SaveImageToTIFFFile(PGDIP_IMAGE Image, PCWSTR FileName, GDIP_TIFFENCODER_PARAMVALUE Compression, INT ColorDepth);