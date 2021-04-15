#pragma once

#include "NTAssassin.h"

#define HIJACK_LOADPROCADDR_MAXPARAMBUFFERSIZE (STRING_ALIGNMENT + sizeof(UINT) + MAX_PATH * sizeof(WCHAR) + sizeof(WORD) + STRING_ALIGNMENT + MAX_CIDENTIFIERNAME_CCH + sizeof(LPVOID))

typedef struct _HIJACK_CREATETHREAD {
    LPTHREAD_START_ROUTINE  Proc32;
    SIZE_T                  ProcSize32;
    LPTHREAD_START_ROUTINE  Proc64;
    SIZE_T                  ProcSize64;
    PVOID                   Param;
    SIZE_T                  ParamSize;
    DWORD                   ExitCode;
} HIJACK_CREATETHREAD, * PHIJACK_CREATETHREAD;

typedef struct _HIJACK_INJECTTHREAD {
    // Input
    HIJACK_CREATETHREAD     Thread;
    // Outputs
    DWORD                   LastError;
    NTSTATUS                LastStatus;
    DWORD                   ExceptionCode;
} HIJACK_INJECTTHREAD, * PHIJACK_INJECTTHREAD;

#define HCPC_X86_STDCALL 0
#define HCPC_X86_FASTCALL 0x1
#define HCPC_X86_CDECL 0x2
#define HCPC_X86_VECTORCALL 0x4
#define HCPC_X64_MS 0
#define HCPC_X64_GCC 0x100

#pragma pack(push)
#pragma pack(4)
typedef struct _HIJACK_CALLPROCHEADER {
    QWORD       Procedure;
    DWORD       CallConvention;
    QWORD       RetValue;
    DWORD       LastError;
    NTSTATUS    LastStatus;
    DWORD       ExceptionCode;
    UINT        ParamCount; // PHIJACK_CALLPROCPARAM
} HIJACK_CALLPROCHEADER, * PHIJACK_CALLPROCHEADER;

typedef struct _HIJACK_CALLPROCPARAM {
    union {
        QWORD   Address;
        QWORD   Value;
        FLOAT   FloatNum;
    };
    QWORD   Size;       // 0 = Imm, -1 = Float for x64
    BOOL    Out;
} HIJACK_CALLPROCPARAM, * PHIJACK_CALLPROCPARAM;
#pragma pack(pop)

//  [STRING_ALIGNMENT]
//  UINT    uSize;          // IN/OUT, Size of buffer, and output final size of stucture
//  WCHAR   szLibName[];    // IN, Terminated by '\0'
//  WORD    wProcOrdinal;   // IN OPTIONAL, Ordinal of procedure
//  [STRING_ALIGNMENT]
//  CHAR    szProcName[];   // IN OPTIONAL, Terminated by '\0', exists only if wProcOrdinal is 0
                            // Could be empty string if load DLL only
//  LPVOID  lpProc;         // OUT OPTIONAL, Receive address of the procedure

// Initialize parameter structure of Hijack_LoadProcAddr
NTA_API PVOID NTAPI Hijack_LoadProcAddr_InitParamEx(PVOID Buffer, UINT BufferSize, PWSTR LibName, LPSTR ProcName, PVOID** ProcAddrPointer);
#define Hijack_LoadProcAddr_InitParam(Buffer, LibName, ProcName, ProcAddrPointer) Hijack_LoadProcAddr_InitParamEx(Buffer, sizeof(Buffer), LibName, ProcName, (LPVOID**)(ProcAddrPointer))

NTA_API NTSTATUS NTAPI Hijack_CreateThread(HANDLE ProcessHandle, PHIJACK_CREATETHREAD HijackThread, DWORD Timeout);
NTA_API NTSTATUS NTAPI Hijack_LoadProcAddr(HANDLE ProcessHandle, PWSTR LibName, PSTR ProcName, PVOID *ProcAddr);

NTA_API NTSTATUS NTAPI Hijack_CallProc(HANDLE ProcessHandle, PHIJACK_CALLPROCHEADER HijackCallProc, PHIJACK_CALLPROCPARAM HijackParams, DWORD Timeout);