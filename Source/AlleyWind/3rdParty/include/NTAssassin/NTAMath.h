#pragma once

#include "NTAssassin.h"

/// <summary>
/// Rounds a value
/// </summary>
#define Math_RoundUInt(val) ((UINT)((val) + 0.5))
#define Math_RoundInt(val) ((INT)((val) + 0.5))
#define Math_RoundUIntPtr(val) ((INT_PTR)((val) + 0.5))
#define Math_RoundIntPtr(val) ((INT_PTR)((val) + 0.5))

/// <summary>
/// Generates a random
/// </summary>
/// <seealso cref="RtlRandomEx"/>
/// <returns>A random number within [0, MAXLONG-1]</returns>
NTA_API ULONG NTAPI Math_Random();

/// <summary>
/// Generates a random within specified range
/// </summary>
/// <seealso cref="RtlRandomEx"/>
/// <param name="Min">Minimum</param>
/// <param name="Max">Maximum</param>
/// <returns>A random number within [Min, Max]</returns>
NTA_API ULONG NTAPI Math_RangedRandom(ULONG Min, ULONG Max);

/// <summary>
/// Checks the number is a power of 2
/// </summary>
#define Math_IsPowerOf2(n) ((n != 0) && ((n & (n - 1)) == 0))

/// <summary>
/// Gets the absolute difference between two numbers
/// </summary>
#define Math_AbsDiff(v1, v2) ((v1) > (v2) ? (v1) - (v2) : (v2) - (v1))

NTA_API DOUBLE NTAPI Math_SimplifySize(UINT64 Size, PCHAR Unit);