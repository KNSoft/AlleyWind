#pragma once

#include "NTAssassin.h"

/// <seealso cref="GetStdHandle"/>
#define Con_GetStdHandle(i) (\
    i == STD_INPUT_HANDLE ? ((NT_GetPEB()->ProcessParameters->StandardInput) : (\
        i == STD_OUTPUT_HANDLE ? (NT_GetPEB()->ProcessParameters->StandardOutput) : (\
            i == STD_ERROR_HANDLE ? (NT_GetPEB()->ProcessParameters->StandardError) : NULL\
        )\
    )\
)

/// <summary>
/// Writes data to console
/// </summary>
/// <param name="ConHandle">Handle to the console</param>
/// <param name="Buffer">Pointer to the buffer contains data to write</param>
/// <param name="Length">Length of data</param>
/// <returns>Number of bytes actually written, or 0 if failed, error code storaged in last STATUS</returns>
NTA_API DWORD NTAPI Con_Write(HANDLE ConHandle, _In_reads_bytes_opt_(Length) PVOID Buffer, _In_ ULONG Length);

/// <summary>
/// Output string to console
/// </summary>
/// <param name="ConHandle">Handle to the console</param>
/// <param name="String">String to output</param>
/// <returns>Number of bytes actually written, or 0 if failed, error code storaged in last STATUS</returns>
NTA_API DWORD Con_WriteString(HANDLE ConHandle, _In_z_ PCSTR String);

/// <summary>
/// Output string to console and starts a new line
/// </summary>
/// <seealso cref="Con_WriteString"/>
NTA_API DWORD Con_WriteLine(HANDLE ConHandle, _In_z_ PCSTR String);

/// <summary>
/// Prints formatted output to the console
/// <see>Con_Printf</see>
/// </summary>
/// <seealso cref="Con_Printf"/>
NTA_API DWORD Con_VPrintf(HANDLE ConHandle, _In_z_ _Printf_format_string_ PCSTR Format, _In_ va_list ArgList);

/// <summary>
/// Prints formatted output to the console
/// </summary>
/// <param name="ConHandle">Handle to the console</param>
/// <param name="Format">Format control</param>
/// <param name="ArgList">Optional arguments</param>
/// <returns>Number of bytes actually printed</returns>
/// <note>If output bytes exceeds 1024, string will be truncated</note>
NTA_API DWORD WINAPIV Con_Printf(HANDLE ConHandle, _In_z_ _Printf_format_string_ PCSTR Format, ...);

/// <summary>
/// Prints formatted output to the console and starts a new line
/// </summary>
/// <seealso cref="Con_Printf"/>
NTA_API DWORD WINAPIV Con_PrintfLine(HANDLE ConHandle, _In_z_ _Printf_format_string_ PCSTR Format, ...);