#pragma once

#include "NTADef.h"
#include "NTANT.h"

/// <summary>
/// Allocates heap memory
/// </summary>
/// <seealso cref="RtlAllocateHeap"/>
#define Mem_HeapAllocEx(Flags, Size) RtlAllocateHeap(NT_GetHeap(), Flags, Size)
#define Mem_HeapAlloc(Size) RtlAllocateHeap(NT_GetHeap(), 0, Size)

/// <summary>
/// Frees heap memory
/// </summary>
/// <seealso cref="RtlFreeHeap"/>
#define Mem_HeapFree(BaseAddress) RtlFreeHeap(NT_GetHeap(), 0, BaseAddress)

/// <summary>
/// Allocates memory pages
/// </summary>
/// <seealso cref="VirtualAlloc"/>
/// <return>Error code storaged in last STATUS</return>
NTA_API _Ret_maybenull_ _Post_writable_byte_size_(Size) _Check_return_ PVOID NTAPI Mem_PageAlloc(_In_ SIZE_T Size, _In_ ULONG Protect);

/// <summary>
/// Changes the protection of memory pages
/// </summary>
/// <seealso cref="VirtualProtect"/>
/// <return>Error code storaged in last STATUS</return>
NTA_API BOOL NTAPI Mem_PageProt(_In_ PVOID BaseAddress, _In_ SIZE_T Size, ULONG Protect, _Out_ PULONG OldProtect);

/// <summary>
/// Frees memory pages
/// </summary>
/// <seealso cref="VirtualFree"/>
/// <return>Error code storaged in last STATUS</return>
NTA_API BOOL NTAPI Mem_PageFree(__drv_freesMem(Mem) PVOID BaseAddress);

// Alias of "Mem_HeapAlloc"
#define Mem_Alloc Mem_HeapAlloc

// Alias of "Mem_HeapFree"
#define Mem_Free Mem_HeapFree
