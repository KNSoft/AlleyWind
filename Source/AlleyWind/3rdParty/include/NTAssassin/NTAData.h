#pragma once

#include "NTADef.h"

/// <summary>
/// Combines groups of structures into a new allocated buffer
/// </summary>
/// <param name="GroupCount">Number of groups</param>
/// <param name="Size">Size of single structure in bytes</param>
/// <param name="...">pst1, u1, pst2, u2, ...</param>
/// <returns>New allocated buffer that combined groups of structures input, should be freed by calling "Mem_Free"</returns>
NTA_API _Check_return_ PVOID WINAPIV Data_StructCombineEx(_In_ UINT GroupCount, _In_ UINT Size, ...);

#define Data_StructCombine(GroupCount, Type, ...) (Type*)Data_StructCombineEx(GroupCount, sizeof(Type), __VA_ARGS__)
