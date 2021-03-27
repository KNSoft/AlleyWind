#pragma once

#include "NTAssassin.h"

#if _DEBUG

#include <stdio.h>

#define Dbg_PrintA printf
#define Dbg_PrintW wprintf
#ifdef UNICODE
#define Dbg_Print Dbg_PrintW
#else
#define Dbg_Print Dbg_PrintA
#endif

#else

#endif