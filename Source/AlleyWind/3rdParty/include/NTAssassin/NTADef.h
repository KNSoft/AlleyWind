#pragma once

// NTAssassin
#include "NTAMacro.h"
#include "NTAConst.h"

// Windows
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
#define _SYSTEM_PROCESS_INFORMATION _MS_SYSTEM_PROCESS_INFORMATION
#define SYSTEM_PROCESS_INFORMATION MS_SYSTEM_PROCESS_INFORMATION
#define PSYSTEM_PROCESS_INFORMATION PMS_SYSTEM_PROCESS_INFORMATION
#define _SYSTEM_THREAD_INFORMATION _MS_SYSTEM_THREAD_INFORMATION
#define SYSTEM_THREAD_INFORMATION MS_SYSTEM_THREAD_INFORMATION
#define PSYSTEM_THREAD_INFORMATION PMS_SYSTEM_THREAD_INFORMATION
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
#define _OBJECT_INFORMATION_CLASS _MS_OBJECT_INFORMATION_CLASS
#define OBJECT_INFORMATION_CLASS MS_OBJECT_INFORMATION_CLASS
#define ObjectBasicInformation MS_ObjectBasicInformation
#define ObjectTypeInformation MS_ObjectTypeInformation

#define OEMRESOURCE
#define STRICT_TYPED_ITEMIDS
#define WIN32_NO_STATUS
#define _WINSOCKAPI_
#include <Windows.h>
#include <Winternl.h>
#include <WindowsX.h>
#include <CommCtrl.h>
#include <Shlobj.h>
#include <Shlwapi.h>
#include <shellscalingapi.h>
#include <dwmapi.h>
#include <Tpcshrd.h>
#include <wtsapi32.h>
#include <WinSock2.h>

#undef _LDR_DATA_TABLE_ENTRY
#undef LDR_DATA_TABLE_ENTRY
#undef PLDR_DATA_TABLE_ENTRY
#undef _PEB_LDR_DATA
#undef PEB_LDR_DATA
#undef PPEB_LDR_DATA
#undef _PEB
#undef PEB
#undef PPEB
#undef _TEB
#undef TEB
#undef PTEB
#undef _RTL_USER_PROCESS_PARAMETERS
#undef RTL_USER_PROCESS_PARAMETERS
#undef PRTL_USER_PROCESS_PARAMETERS
#undef _CLIENT_ID
#undef CLIENT_ID
#undef _FILE_INFORMATION_CLASS
#undef FILE_INFORMATION_CLASS
#undef PFILE_INFORMATION_CLASS
#undef FileDirectoryInformation
#undef _PROCESSINFOCLASS
#undef PROCESSINFOCLASS
#undef ProcessBasicInformation
#undef ProcessDebugPort
#undef ProcessWow64Information
#undef ProcessImageFileName
#undef ProcessBreakOnTermination
#undef _THREADINFOCLASS
#undef THREADINFOCLASS
#undef ThreadIsIoPending
#undef _SYSTEM_INFORMATION_CLASS
#undef SYSTEM_INFORMATION_CLASS
#undef _SYSTEM_PROCESS_INFORMATION
#undef SYSTEM_PROCESS_INFORMATION
#undef PSYSTEM_PROCESS_INFORMATION
#undef _SYSTEM_THREAD_INFORMATION
#undef SYSTEM_THREAD_INFORMATION
#undef PSYSTEM_THREAD_INFORMATION
#undef SystemBasicInformation
#undef SystemPerformanceInformation
#undef SystemTimeOfDayInformation
#undef SystemProcessInformation
#undef SystemProcessorPerformanceInformation
#undef SystemInterruptInformation
#undef SystemExceptionInformation
#undef SystemRegistryQuotaInformation
#undef SystemLookasideInformation
#undef SystemCodeIntegrityInformation
#undef SystemPolicyInformation
#undef _OBJECT_INFORMATION_CLASS
#undef OBJECT_INFORMATION_CLASS
#undef ObjectBasicInformation
#undef ObjectTypeInformation

// Windows NT definations
#include "NTConst.h"
#include "NTTypes.h"
#include "NTStruct.h"
#include "NTAPI.h"
