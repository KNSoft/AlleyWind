// Memory management

#pragma once

#include "NTAssassin\NTAssassin.h"

/**
  * @brief Allocates heap memory
  * @see "HeapAlloc"
  */
#define Mem_HeapAllocEx(Flags, Size) RtlAllocateHeap(DEFAULT_HEAP_HANDLE, Flags, Size)
#define Mem_HeapAlloc(Size) RtlAllocateHeap(DEFAULT_HEAP_HANDLE, 0, Size)

/**
  * @brief Frees heap memory
  * @see "HeapFree"
  */
#define Mem_HeapFree(BaseAddress) RtlFreeHeap(DEFAULT_HEAP_HANDLE, 0, BaseAddress)

/**
  * @brief Allocates memory pages
  * @see "VirtualAlloc"
  */
NTA_API PVOID NTAPI Mem_PageAlloc(SIZE_T Size, ULONG Protect);

/**
  * @brief Changes the protection of memory pages
  * @see "VirtualProtect"
  */
NTA_API NTSTATUS NTAPI Mem_PageProt(PVOID BaseAddress, SIZE_T Size, ULONG Protect, PULONG OldProtect);
/**
  * @brief Frees memory pages
  * @see "VirtualFree"
  */
NTA_API NTSTATUS NTAPI Mem_PageFree(PVOID BaseAddress, SIZE_T Size);

// Alias of "Mem_HeapAlloc"
#define Mem_Alloc Mem_HeapAlloc

// Alias of "Mem_HeapFree"
#define Mem_Free Mem_HeapFree