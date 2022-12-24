#pragma once

#include "NTADef.h"

typedef struct _PE_STRUCT {
    PBYTE                           Image;
    ULONG                           ImageSize;
    PIMAGE_FILE_HEADER              FileHeader;
    union {
        PIMAGE_OPTIONAL_HEADER      OptionalHeader;
        PIMAGE_OPTIONAL_HEADER64    OptionalHeader64;
        PIMAGE_OPTIONAL_HEADER32    OptionalHeader32;
        PIMAGE_ROM_OPTIONAL_HEADER  OptionalHeaderRom;
    };
    PIMAGE_SECTION_HEADER           SectionHeader;
    BOOL                            OfflineMap;
    PVOID                           OverlayData;
    ULONG                           OverlayDataSize;
} PE_STRUCT, *PPE_STRUCT;

#define PE_ProbeForRead(pe, ptr, size) ((PBYTE)(ptr) >= (pe)->Image && (PBYTE)(ptr) + (size) <= (pe)->Image + (pe)->ImageSize)
#define PE_GetOptionalHeaderValue(pe, m) (PE_GetBits(pe) == 64 ? PE_GetOptionalHeaderValueEx(pe,  UFIELD_OFFSET(IMAGE_OPTIONAL_HEADER64, m), RTL_FIELD_SIZE(IMAGE_OPTIONAL_HEADER64, m)) : PE_GetOptionalHeaderValueEx(pe,  UFIELD_OFFSET(IMAGE_OPTIONAL_HEADER32, m), RTL_FIELD_SIZE(IMAGE_OPTIONAL_HEADER32, m)))

/// <summary>
/// Resolves a PE image to PE_STRUCT structure
/// </summary>
/// <param name="PEStruct">Pointer to a PE_STRUCT structure</param>
/// <param name="Image">Pointer to the PE image</param>
/// <param name="OfflineMap">TRUE if PE image is offline (like file map), or FALSE if PE image is loaded in memory as a module</param>
/// <returns>TRUE if succeeded, or FALSE if failed</returns>
NTA_API VOID NTAPI PE_ResolveOnline(_Out_ PPE_STRUCT PEStruct, _In_ HMODULE Image);
_Success_(return != FALSE) NTA_API BOOL NTAPI PE_ResolveOffline(_Out_ PPE_STRUCT PEStruct, _In_reads_bytes_(BufferSize) PVOID Buffer, _In_ ULONG BufferSize);

/// <summary>
/// Gets bits of PE image
/// </summary>
/// <param name="PEStruct"></param>
/// <returns>Bits of PE image, 32 or 64</returns>
NTA_API UINT NTAPI PE_GetBits(_In_ PPE_STRUCT PEStruct);

NTA_API ULONGLONG NTAPI PE_GetOptionalHeaderValueEx(_In_ PPE_STRUCT PEStruct, ULONG FieldOffset, ULONG FieldSize);

/// <summary>
/// Gets data directory entry of PE image
/// </summary>
/// <param name="PEStruct">Pointer to the PE_STRUCT structure</param>
/// <param name="Index">IMAGE_DIRECTORY_ENTRY_XXX</param>
/// <returns>Pointer to the IMAGE_DATA_DIRECTORY structure, or NULL if failed</returns>
NTA_API PIMAGE_DATA_DIRECTORY NTAPI PE_GetDataDirectory(_In_ PPE_STRUCT PEStruct, UINT Index);

/// <summary>
/// Gets section by RVA
/// </summary>
/// <param name="PEStruct">Pointer to the PE_STRUCT structure</param>
/// <param name="RVA">RVA</param>
/// <returns>Pointer to the IMAGE_SECTION_HEADER structure, or NULL if failed</returns>
NTA_API PIMAGE_SECTION_HEADER NTAPI PE_GetSectionByRVA(_In_ PPE_STRUCT PEStruct, DWORD RVA);

/// <summary>
/// Gets section by offset
/// </summary>
/// <param name="PEStruct">Pointer to the PE_STRUCT structure</param>
/// <param name="Offset">Offset</param>
/// <returns>Pointer to the IMAGE_SECTION_HEADER structure, or NULL if failed</returns>
NTA_API PIMAGE_SECTION_HEADER NTAPI PE_GetSectionByOffset(_In_ PPE_STRUCT PEStruct, DWORD Offset);

/// <summary>
/// Converts RVA to pointer
/// </summary>
/// <param name="PEStruct">Pointer to the PE_STRUCT structure</param>
/// <param name="RVA">RVA</param>
/// <returns>The pointer converted</returns>
NTA_API PVOID NTAPI PE_RVA2Ptr(_In_ PPE_STRUCT PEStruct, DWORD RVA);

/// <summary>
/// Converts pointer to RVA
/// </summary>
/// <param name="PEStruct">Pointer to the PE_STRUCT structure</param>
/// <param name="Ptr">Pointer</param>
/// <param name="RVA">Pointer to a DWORD variable to receive the RVA converted</param>
/// <returns>TRUE if succeeded, or FALSE if failed</returns>
_Success_(return != FALSE) NTA_API BOOL NTAPI PE_Ptr2RVA(_In_ PPE_STRUCT PEStruct, _In_  PVOID Ptr, _Out_ PDWORD RVA);

/// <summary>
/// Converts pointer to offset
/// </summary>
/// <param name="PEStruct">Pointer to the PE_STRUCT structure</param>
/// <param name="Ptr">Pointer</param>
/// <param name="Offset">Pointer to a DWORD variable to receive the offset converted</param>
/// <returns>TRUE if succeeded, or FALSE if failed</returns>
_Success_(return != FALSE) NTA_API BOOL NTAPI PE_Ptr2Offset(_In_ PPE_STRUCT PEStruct, _In_ PVOID Ptr, _Out_ PDWORD Offset);

/// <summary>
/// Get exported name of specified function
/// </summary>
/// <param name="PEStruct">Pointer to the PE_STRUCT structure</param>
/// <param name="Function">Address of function</param>
/// <param name="Name">Pointer to a PCSTR variable to receive the exported name of the function</param>
/// <returns>TRUE if succeeded, or FALSE if failed</returns>
_Success_(return != FALSE) NTA_API BOOL NTAPI PE_GetExportedName(_In_ PPE_STRUCT PEStruct, _In_ PVOID Function, _Out_ PZPCSTR Name);

NTA_API PCWSTR PE_GetMachineName(_In_ PPE_STRUCT PEStruct);
NTA_API PCWSTR PE_GetSubsystemName(_In_ PPE_STRUCT PEStruct);
