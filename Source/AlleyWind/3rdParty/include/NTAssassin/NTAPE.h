#pragma once

#include "NTAssassin\NTAssassin.h"

typedef struct _PE_IMAGE {
    PIMAGE_DOS_HEADER   lpImage;
    WORD                wMachine;
    union {
        PIMAGE_NT_HEADERS64 lpNtHeader64;
        PIMAGE_NT_HEADERS32 lpNtHeader32;
        PIMAGE_NT_HEADERS   lpNtHeader;
    };
    BOOL                bFileMap;
} PE_IMAGE, * PPE_IMAGE;

NTA_API BOOL NTAPI PE_Init(PPE_IMAGE lpImage, LPVOID lpMem, BOOL bFileMap);

#define PE_GetFirstSection(lpImage) (IMAGE_FIRST_SECTION((lpImage)->lpNtHeader))