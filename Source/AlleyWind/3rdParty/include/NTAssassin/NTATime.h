#pragma once

#include "NTADef.h"

/// <summary>
/// Gets time interval like stop watch
/// </summary>
/// <param name="PrevTime">Reference time to calcuate interval, or pass 0 to have a new one</param>
/// <returns>Time interval from PrevTime to now, or current time if PrevTime is 0</returns>
/// <remarks>Time_StopWatch[Unit], Unit is time unit used in the function. "Time_StopWatch" equals to "Time_StopWatch1ms", which unit is 1ms</remarks>
NTA_API ULONGLONG NTAPI Time_StopWatch100nm(ULONGLONG PrevTime);
NTA_API ULONGLONG NTAPI Time_StopWatch1ms(ULONGLONG PrevTime);
NTA_API ULONGLONG NTAPI Time_StopWatch1us(ULONGLONG PrevTime);
#define Time_StopWatch Time_StopWatch1ms

/// <summary>
/// Converts Unix timestamp to FILETIME
/// </summary>
/// <see href="https://learn.microsoft.com/en-us/windows/win32/sysinfo/converting-a-time-t-value-to-a-file-time">Converting a time_t value to a FILETIME - Microsoft Learn</see>
NTA_API VOID NTAPI Time_UnixTimeToFileTime(time_t UnixTime, PFILETIME FileTime);
