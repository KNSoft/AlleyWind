#pragma once

// NTAssassin Exports, both of static and dynamic library targets are supported
// Static library target is recommended
#define NTA_DLL 0
#if NTA_DLL
#ifdef NTA_EXPORTS
#define NTA_API DECLSPEC_EXPORT
#else
#define NTA_API DECLSPEC_IMPORT
#endif
#else
#define NTA_API
#endif

// NTAssassin Options

// NTA_CUSTOMENTRY
#ifdef NTA_CUSTOMENTRY
#pragma comment(linker, "/ENTRY:" NTA_CUSTOMENTRY)

#if _DEBUG
#if _DLL
#pragma comment(lib, "msvcrtd.lib")
#pragma comment(lib, "vcruntimed.lib")
#pragma comment(lib, "ucrtd.lib")
#else
#pragma comment(lib, "libcmtd.lib")
#pragma comment(lib, "libvcruntimed.lib")
#pragma comment(lib, "libucrtd.lib")
#endif
#else
#if _DLL
#pragma comment(lib, "msvcrt.lib")
#pragma comment(lib, "vcruntime.lib")
#pragma comment(lib, "ucrt.lib")
#else
#pragma comment(lib, "libcmt.lib")
#pragma comment(lib, "libvcruntime.lib")
#pragma comment(lib, "libucrt.lib")
#endif
#endif

#endif

#define OEMRESOURCE
#define STRICT_TYPED_ITEMIDS

// Replaces definations to redefine them

#define _LDR_DATA_TABLE_ENTRY _MS_LDR_DATA_TABLE_ENTRY
#define LDR_DATA_TABLE_ENTRY MS_LDR_DATA_TABLE_ENTRY
#define PLDR_DATA_TABLE_ENTRY PMS_LDR_DATA_TABLE_ENTRY
#define _PEB_LDR_DATA _MS_PEB_LDR_DATA
#define PEB_LDR_DATA MS_PEB_LDR_DATA
#define PPEB_LDR_DATA PMS_PEB_LDR_DATA
#define _PEB _MS_PEB
#define PEB MS_PEB
#define PPEB PMS_PEB
#define _TEB _MS_TEB
#define TEB MS_TEB
#define PTEB PMS_TEB
#define _RTL_USER_PROCESS_PARAMETERS _MS_RTL_USER_PROCESS_PARAMETERS
#define RTL_USER_PROCESS_PARAMETERS MS_RTL_USER_PROCESS_PARAMETERS
#define PRTL_USER_PROCESS_PARAMETERS PMS_RTL_USER_PROCESS_PARAMETERS
#define _CLIENT_ID _MS_CLIENT_ID
#define CLIENT_ID MS_CLIENT_ID
#define _FILE_INFORMATION_CLASS _MS_FILE_INFORMATION_CLASS
#define FILE_INFORMATION_CLASS MS_FILE_INFORMATION_CLASS
#define PFILE_INFORMATION_CLASS PMS_FILE_INFORMATION_CLASS
#define FileDirectoryInformation MS_FileDirectoryInformation
#define _PROCESSINFOCLASS _MS_PROCESSINFOCLASS
#define PROCESSINFOCLASS MS_PROCESSINFOCLASS
#define ProcessBasicInformation MS_ProcessBasicInformation
#define ProcessDebugPort MS_ProcessDebugPort
#define ProcessWow64Information MS_ProcessWow64Information
#define ProcessImageFileName MS_ProcessImageFileName
#define ProcessBreakOnTermination MS_ProcessBreakOnTermination
#define _THREADINFOCLASS _MS_THREADINFOCLASS
#define THREADINFOCLASS MS_THREADINFOCLASS
#define ThreadIsIoPending MS_ThreadIsIoPending
#define _SYSTEM_INFORMATION_CLASS _MS_SYSTEM_INFORMATION_CLASS
#define SYSTEM_INFORMATION_CLASS MS_SYSTEM_INFORMATION_CLASS
#define SystemBasicInformation MS_SystemBasicInformation
#define SystemPerformanceInformation MS_SystemPerformanceInformation
#define SystemTimeOfDayInformation MS_SystemTimeOfDayInformation
#define SystemProcessInformation MS_SystemProcessInformation
#define SystemProcessorPerformanceInformation MS_SystemProcessorPerformanceInformation
#define SystemInterruptInformation MS_SystemInterruptInformation
#define SystemExceptionInformation MS_SystemExceptionInformation
#define SystemRegistryQuotaInformation MS_SystemRegistryQuotaInformation
#define SystemLookasideInformation MS_SystemLookasideInformation
#define SystemCodeIntegrityInformation MS_SystemCodeIntegrityInformation
#define SystemPolicyInformation MS_SystemPolicyInformation
#define OBJECT_INFORMATION_CLASS MS_OBJECT_INFORMATION_CLASS
#define ObjectBasicInformation MS_ObjectBasicInformation
#define ObjectTypeInformation MS_ObjectTypeInformation

#include <Windows.h>
#include <Winternl.h>
#include <WindowsX.h>
#include <CommCtrl.h>
#include <Shlobj.h>
#include <shellscalingapi.h>
#include <dwmapi.h>
#include <Tpcshrd.h>

#ifdef __cplusplus
extern "C" {
#endif

// NTAssassin dependencies
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(lib, "gdiplus.lib")

// Always use ComCtl32.dll V6.0
#pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

// Additional definitions

#define DECLSPEC_EXPORT __declspec(dllexport)

// Avoid "unused parameter" warnings
#define UNUSED UNREFERENCED_PARAMETER

#if _WIN64
#define IS_WIN64 TRUE
#else
#define IS_WIN64 FALSE
#endif

// Uses an alter value instead if the value is NULL
#define IF_NULL(val, alt_val) (val ? val : alt_val)
// Uses an alter value instead if the value is not NULL
#define IF_NOTNULL(val, alt_val) (val ? alt_val : val)

// Applies different expression depends on 32-bit or 64-bit architecture
#define IF_ARCH32OR64(expr64, expr32) (_WIN64 ? (expr64) : (expr32))

// Makes a DWORD value by LOWORD and HIWORD
#define MAKEDWORD(l, h) ((DWORD)MAKELONG(l, h))
#define MAKEQWORD(l, h) ((QWORD)(((DWORD)(((DWORD_PTR)(l)) & 0xffffffff)) | ((QWORD)((DWORD)(((DWORD_PTR)(h)) & 0xffffffff))) << 32))

// Handle to the default heap
#define DEFAULT_HEAP_HANDLE ((HANDLE)NT_GetPEB()->ProcessHeap)

// Instance handle of current executable module
#define IMAGE_BASE (NT_GetPEB()->ImageBaseAddress)

// Handle to current directory
#define CURRENT_DIR_HANDLE (NT_GetPEB()->ProcessParameters->CurrentDirectory.Handle)

// Clear high 32-bit of HWND
#if _WIN64
#define PURGE_HWND(hWnd) ((HWND)((DWORD_PTR)(hWnd) & 0xFFFFFFFF))
#else
#define PURGE_HWND(hWnd) (hWnd)
#endif

// Gets equality of two value after masked
#define IS_EQUAL_MASKED(val1, val2, mask) (!(((val1) ^ (val2)) & (mask)))
// Sets or removes a flag from a combination value
#define COMBINE_FLAGS(val, uflag, bEnable) ((bEnable) ? ((val) | (uflag)) : ((val) & ~(uflag)))

#define BYTE_ALIGN(val, ali) ((val + ali - 1) & (~(ali - 1)))
#define IS_BYTE_ALIGNED(val, ali) (!(val & (ali - 1)))

// Gets is the value is within the valid range of an atom
#define IS_ATOM(val) (((ULONG_PTR)(val) & 0xFFFF) > 0 && ((ULONG_PTR)(val) & 0xFFFF) < MAXINTATOM)

// Moves pointer
#define MOVE_PTR(address, offset, type) ((type *)((PBYTE)(address) + (LONG_PTR)(offset)))

// Memory alignment
#define PAGE_SIZE 0x1000
#define CODE_ALIGNMENT 0x10
#define STRING_ALIGNMENT 0x4

#define MAX_WORD_IN_DEC_CCH                     6                                   // Max WORD in decimal is 65535
#define MAX_QWORD_IN_HEX_CCH                    17                                  
#define MAX_CLASSNAME_CCH                       256
#define MAX_CIDENTIFIERNAME_CCH                 247
#define MAX_ATOM_CCH                            255
#define MAX_REG_KEYNAME_CCH                     255
#define MAX_REG_VALUENAME_CCH                   16383
#define MAX_LOCALENAME_CCH                      85
#define HEXRGB_CCH                              8   // #RRGGBB
#define MAX_POINTER_CCH                         (sizeof(PVOID) * 2 + 1)
#define CURRENT_PROCESS_HANDLE                  ((HANDLE)-1)
#define CURRENT_THREAD_HANDLE                   ((HANDLE)-2)
#define CURRENT_PROCESS_TOKEN_HANDLE            ((HANDLE)-4)
#define CURRENT_THREAD_TOKEN_HANDLE             ((HANDLE)-5)
#define CURRENT_THREAD_EFFECTIVETOKEN_HANDLE    ((HANDLE)-6)
#define FIXED_IMAGE_BASE32                      ((HINSTANCE)0x00400000)
#define FIXED_IMAGE_BASE64                      ((HINSTANCE)0x0000000140000000)

#define EOLW                                    ((DWORD)0x000A000D)
#define EOLA                                    ((WORD)0x0A0D)
#ifdef UNICODE
#define EOL EOLW
#else
#define EOL EOLA
#endif

// WinNT additions
#include "NTConst.h"
#include "NTTypes.h"
#include "NTStruct.h"
#include "NTAPI.h"

#ifdef NTA_EXPORTS
#include "..\NTA_NAC_Output.h"
#endif

#include "NTAUCRT.h"
#include "NTANT.h"
#include "NTAData.h"
#include "NTADbg.h"
#include "NTAMath.h"
#include "NTAStr.h"
#include "NTAList.h"
#include "NTAMem.h"
#include "NTAPE.h"
#include "NTAProc.h"
#include "NTARProc.h"
#include "NTACon.h"
#include "NTAUI.h"
#include "NTACtl.h"
#include "NTAGDI.h"
#include "NTADlg.h"
#include "NTAI18N.h"
#include "NTAKNS.h"
#include "NTAFile.h"
#include "NTAIO.h"
#include "NTAImage.h"
#include "NTATime.h"
#include "NTASys.h"
#include "NTAHijack.h"
#include "NTADPI.h"
#include "NTAGDIP.h"

#ifdef __cplusplus
}
#endif