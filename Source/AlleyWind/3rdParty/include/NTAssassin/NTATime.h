#pragma once

#include "NTADef.h"

/// <summary>
/// Gets time interval like stop watch
/// </summary>
/// <param name="PrevTime">Reference time to calcuate interval, or pass 0 to have a new one</param>
/// <returns>Time interval from PrevTime to now, or current time if PrevTime is 0</returns>
/// <remarks>Time_StopWatch[Unit], Unit is time unit used in the function. "Time_StopWatch" equals to "Time_StopWatch1ms", which unit is 1ms</remarks>
NTA_API ULONGLONG NTAPI Time_StopWatch100nm(ULONGLONG PrevTime);
NTA_API ULONGLONG NTAPI Time_StopWatch16ms(ULONGLONG PrevTime);
NTA_API ULONGLONG NTAPI Time_StopWatch1ms(ULONGLONG PrevTime);
NTA_API ULONGLONG NTAPI Time_StopWatch1us(ULONGLONG PrevTime);
#define Time_StopWatch Time_StopWatch1ms
