#pragma once

#include "NTAssassin.h"

NTA_API ULONGLONG NTAPI Time_StopWatch100nm(ULONGLONG ullPrevTime);

NTA_API ULONGLONG NTAPI Time_StopWatch16ms(ULONGLONG ullPrevTime);

NTA_API ULONGLONG NTAPI Time_StopWatch1ms(ULONGLONG ullPrevTime);

NTA_API ULONGLONG NTAPI Time_StopWatch1us(ULONGLONG ullPrevTime);

#define Time_StopWatch Time_StopWatch1ms