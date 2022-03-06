#pragma once

#include "NTAssassin.h"

NTA_API PVOID WINAPIV Data_StructCombineEx(UINT GroupCount, UINT Size, ...);

/**
  * @brief Combines groups of structures into a new allocated buffer
  * @param[in] uGroupCount Number of groups
  * @param[in] t Type of structure
  * @param[in] ... lpst1, uCount1, lpst2, uCount2, ...
  * @return Returns new allocated buffer, should be freed by calling "Mem_HeapFree"
  */
#define Data_StructCombine(uGroupCount, t, ...) (t*)Data_StructCombineEx(uGroupCount, sizeof(t), __VA_ARGS__)