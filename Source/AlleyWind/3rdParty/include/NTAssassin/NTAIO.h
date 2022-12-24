// I/O a file or device

#pragma once

#include "NTADef.h"

/// <summary>
/// Writes data to specified file or device
/// </summary>
/// <param name="FileHandle">Handle to the file</param>
/// <param name="ByteOffset">Offset to write</param>
/// <param name="Buffer">Data to write</param>
/// <param name="Length">Size of data in bytes</param>
/// <returns>TRUE if succeeded, or NULL if failed, error code storaged in last STATUS</returns>
NTA_API BOOL NTAPI IO_Write(HANDLE FileHandle, ULONGLONG ByteOffset, _In_reads_bytes_(Length) PVOID Buffer, ULONG Length);

/// <summary>
/// Writes string to specified file or device
/// </summary>
/// <seealso cref="IO_Write"/>
NTA_API BOOL NTAPI IO_WriteStringW(HANDLE FileHandle, _In_z_ PCWSTR String);
NTA_API BOOL NTAPI IO_WriteStringA(HANDLE FileHandle, _In_z_ PCSTR String);
#ifdef UNICODE
#define IO_WriteString IO_WriteStringW
#else
#define IO_WriteString IO_WriteStringA
#endif

/// <summary>
/// Writes string to specified file or device and starts a new line
/// </summary>
/// <seealso cref="IO_Write"/>
NTA_API BOOL NTAPI IO_WriteLineW(HANDLE FileHandle, _In_z_ PCWSTR String);
NTA_API BOOL NTAPI IO_WriteLineA(HANDLE FileHandle, _In_z_ PCSTR String);
#ifdef UNICODE
#define IO_WriteLine IO_WriteLineW
#else
#define IO_WriteLine IO_WriteLineA
#endif
