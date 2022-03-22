#pragma once

#include "NTAssassin.h"

typedef struct _PE_STRUCT {
    PIMAGE_DOS_HEADER               Image;
    BOOL                            OfflineMap;
    PIMAGE_FILE_HEADER              FileHeader;
    union {
        PIMAGE_OPTIONAL_HEADER      OptionalHeader;
        PIMAGE_OPTIONAL_HEADER64    OptionalHeader64;
        PIMAGE_OPTIONAL_HEADER32    OptionalHeader32;
        PIMAGE_ROM_OPTIONAL_HEADER  OptionalHeaderRom;
    };
    PIMAGE_SECTION_HEADER           SectionHeader;
    PVOID                           OverlayData;
} PE_STRUCT, *PPE_STRUCT;

NTA_API BOOL NTAPI PE_Resolve(PPE_STRUCT PEStruct, PVOID Image, BOOL OfflineMap);

NTA_API PIMAGE_DATA_DIRECTORY NTAPI PE_GetDataDirectory(PPE_STRUCT PEStruct, UINT Index);

NTA_API PIMAGE_SECTION_HEADER NTAPI PE_GetSectionByRVA(PPE_STRUCT PEStruct, DWORD RVA);

NTA_API PIMAGE_SECTION_HEADER NTAPI PE_GetSectionByOffset(PPE_STRUCT PEStruct, DWORD Offset);

NTA_API PVOID NTAPI PE_RVA2Ptr(PPE_STRUCT PEStruct, DWORD RVA);

NTA_API BOOL NTAPI PE_Ptr2RVA(PPE_STRUCT PEStruct, PVOID Ptr, PDWORD RVA);

NTA_API BOOL NTAPI PE_Ptr2Offset(PPE_STRUCT PEStruct, PVOID Ptr, PDWORD Offset);

NTA_API BOOL NTAPI PE_GetExportedName(PPE_STRUCT PEStruct, PVOID Function, PZPCSTR Name);