#pragma once

#include "NTADef.h"

/// <seealso cref="ShellExecute"/>
NTA_API BOOL NTAPI Shell_Exec(_In_ PCWSTR File, _In_opt_ PCWSTR Param, PCWSTR Verb, INT ShowCmd, PHANDLE ProcessHandle);

/// <summary>
/// Locates specified file or directory in explorer
/// </summary>
/// <param name="Path">Path of file or directory</param>
/// <returns>TRUE if succeeded, or FALSE if failed, error code storaged in last ERROR</returns>
NTA_API BOOL NTAPI Shell_Locate(_In_ PCWSTR Path);

/// <summary>
/// Resolves a shortcut link
/// </summary>
/// <param name="LinkFile">Path to the shortcut file</param>
/// <param name="Path">Pointer to the buffer to receive path</param>
/// <param name="PathCchSize">The size of the Path buffer in characters</param>
/// <returns>TRUE if succeeded, or FALSE if failed, error code storaged in last ERROR</returns>
_Success_(return != FALSE) NTA_API BOOL NTAPI Shell_GetLinkPath(_In_ PCWSTR LinkFile, _Out_writes_z_(PathCchSize) PWSTR Path, _In_ INT PathCchSize);
