// Memory management

#pragma once

#include "NTAssassin.h"

/**
  * @brief Allocates heap memory
  * @see "HeapAlloc"
  */
#define Mem_HeapAllocEx(dwFlags, dwBytes) RtlAllocateHeap(DEFAULT_HEAP_HANDLE, dwFlags, dwBytes)
#define Mem_HeapAlloc(dwBytes) RtlAllocateHeap(DEFAULT_HEAP_HANDLE, 0, dwBytes)

/**
  * @brief Frees heap memory
  * @see "HeapFree"
  */
#define Mem_HeapFree(lpMem) RtlFreeHeap(DEFAULT_HEAP_HANDLE, 0, lpMem)

/**
  * @brief Allocate memory pages
  * @see "VirtualAlloc"
  */
NTA_API LPVOID NTAPI Mem_PageAlloc(SIZE_T dwBytes, ULONG flProtect);

/**
  * @brief Changes the protection of memory pages
  * @see "VirtualProtect"
  */
NTA_API NTSTATUS NTAPI Mem_PageProt(LPVOID lpMem, SIZE_T dwBytes, ULONG flProtect, PULONG lpflOldProtect);

/**
  * @brief Frees memory pages
  * @see "VirtualFree"
  */
NTA_API NTSTATUS NTAPI Mem_PageFree(LPVOID lpMem, SIZE_T dwBytes);

// Alias of "Mem_HeapAlloc"
#define Mem_Alloc Mem_HeapAlloc

// Alias of "Mem_HeapFree"
#define Mem_Free Mem_HeapFree