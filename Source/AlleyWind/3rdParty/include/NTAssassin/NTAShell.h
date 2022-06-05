#pragma once

#include "NTAssassin.h"

typedef enum _SHELL_EXEC_VERB {
    ShellExecEdit,
    ShellExecExplore,
    ShellExecFind,
    ShellExecOpen,
    ShellExecPrint,
    ShellExecProperties,
    ShellExecRunAs
} SHELL_EXEC_VERB, *PSHELL_EXEC_VERB;

/// <seealso cref="ShellExecute"/>
/// <remarks>ShellExecExplore implemented by calling <c>SHOpenFolderAndSelectItems</c> which depends COM, in this case, ProcessHandle is ignored</remarks>
/// <returns>TRUE if succeeded, or FALSE if failed, error code storaged in last ERROR</returns>
NTA_API BOOL NTAPI Shell_Exec(PCWSTR File, PCWSTR Param, SHELL_EXEC_VERB Verb, INT ShowCmd, PHANDLE ProcessHandle);
