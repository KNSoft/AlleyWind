#pragma once

// NTAssassin
#include "NTAMacro.h"
#include "NTAConst.h"
#include "NTATypes.h"

// Windows

// Conflicts with NTAssassin
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
#define _PROCESS_BASIC_INFORMATION _MS_PROCESS_BASIC_INFORMATION
#define PROCESS_BASIC_INFORMATION MS_PROCESS_BASIC_INFORMATION
#define PPROCESS_BASIC_INFORMATION PMS_PROCESS_BASIC_INFORMATION
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
#define PSID MS_PSID
#define _WINSTATIONINFOCLASS _MS_WINSTATIONINFOCLASS
#define WINSTATIONINFOCLASS MS_WINSTATIONINFOCLASS
#define WinStationInformation MS_WinStationInformation

#define OEMRESOURCE
#define STRICT_TYPED_ITEMIDS
#define WIN32_NO_STATUS
#define _WINSOCKAPI_
#include <Windows.h>
#include <Winternl.h>

// Conflicts in ntdef.h

#undef PROBE_ALIGNMENT
#undef PROBE_ALIGNMENT32
#undef UNICODE_STRING_MAX_BYTES
#undef MAKELANGID
#undef PRIMARYLANGID
#undef SUBLANGID
#undef MAKELCID
#undef MAKESORTLCID
#undef LANGIDFROMLCID
#undef SORTIDFROMLCID
#undef SORTVERSIONFROMLCID
#undef MAX_NATURAL_ALIGNMENT
#undef DEFINE_ENUM_FLAG_OPERATORS

#define _PROCESSOR_NUMBER _MS_PROCESSOR_NUMBER
#define PROCESSOR_NUMBER MS_PROCESSOR_NUMBER
#define PPROCESSOR_NUMBER PMS_PROCESSOR_NUMBER
#define _GROUP_AFFINITY _MS_GROUP_AFFINITY
#define GROUP_AFFINITY MS_GROUP_AFFINITY
#define PGROUP_AFFINITY PMS_GROUP_AFFINITY
#define _FLOAT128 _MS_FLOAT128
#define FLOAT128 MS_FLOAT128
#define PFLOAT128 PMS_FLOAT128
#define _ULARGE_INTEGER _MS_ULARGE_INTEGER
#define ULARGE_INTEGER MS_ULARGE_INTEGER
#define PULARGE_INTEGER PMS_ULARGE_INTEGER
#define _LUID _MS_LUID
#define LUID MS_LUID
#define PLUID PMS_LUID
#define _STRING _MS_STRING
#define STRING MS_STRING
#define PSTRING PMS_STRING
#define ANSI_STRING MS_ANSI_STRING
#define PANSI_STRING PMS_ANSI_STRING
#define PCANSI_STRING PCMS_ANSI_STRING
#define OEM_STRING MS_OEM_STRING
#define POEM_STRING PMS_OEM_STRING
#define PCOEM_STRING PCMS_OEM_STRING
#define _LIST_ENTRY _MS_LIST_ENTRY
#define LIST_ENTRY MS_LIST_ENTRY
#define PLIST_ENTRY PMS_LIST_ENTRY
#define PRLIST_ENTRY PRMS_LIST_ENTRY
#define _SINGLE_LIST_ENTRY _MS_SINGLE_LIST_ENTRY
#define SINGLE_LIST_ENTRY MS_SINGLE_LIST_ENTRY
#define PSINGLE_LIST_ENTRY PMS_SINGLE_LIST_ENTRY
#define _LIST_ENTRY32 _MS_LIST_ENTRY32
#define LIST_ENTRY32 MS_LIST_ENTRY32
#define PLIST_ENTRY32 PMS_LIST_ENTRY32
#define _LIST_ENTRY64 _MS_LIST_ENTRY64
#define LIST_ENTRY64 MS_LIST_ENTRY64
#define PLIST_ENTRY64 PMS_LIST_ENTRY64
#if defined(_M_IX86)
#define Int64ShllMod32 MS_Int64ShllMod32
#define Int64ShraMod32 MS_Int64ShraMod32
#define Int64ShrlMod32 MS_Int64ShrlMod32
#endif
#define _ENUM_FLAG_INTEGER_FOR_SIZE _MS_ENUM_FLAG_INTEGER_FOR_SIZE
#define _ENUM_FLAG_SIZED_INTEGER _MS_ENUM_FLAG_SIZED_INTEGER
#define _LARGE_INTEGER _MS_LARGE_INTEGER
#define LARGE_INTEGER MS_LARGE_INTEGER
#define PLARGE_INTEGER PMS_LARGE_INTEGER
#define _UNICODE_STRING _MS_UNICODE_STRING
#define UNICODE_STRING MS_UNICODE_STRING
#define PUNICODE_STRING PMS_UNICODE_STRING
#define PCUNICODE_STRING PCMS_UNICODE_STRING
#define _OBJECT_ATTRIBUTES _MS_OBJECT_ATTRIBUTES
#define OBJECT_ATTRIBUTES MS_OBJECT_ATTRIBUTES
#define POBJECT_ATTRIBUTES PMS_OBJECT_ATTRIBUTES

#include <ntdef.h>

#undef _PROCESSOR_NUMBER
#undef PROCESSOR_NUMBER
#undef PPROCESSOR_NUMBER
#undef _GROUP_AFFINITY
#undef GROUP_AFFINITY
#undef PGROUP_AFFINITY
#undef _FLOAT128
#undef FLOAT128
#undef PFLOAT128
#undef _ULARGE_INTEGER
#undef ULARGE_INTEGER
#undef PULARGE_INTEGER
#undef _LUID
#undef LUID
#undef PLUID
#undef _STRING
#undef STRING
#undef PSTRING
#undef ANSI_STRING
#undef PANSI_STRING
#undef PCANSI_STRING
#undef OEM_STRING
#undef POEM_STRING
#undef PCOEM_STRING
#undef _LIST_ENTRY
#undef LIST_ENTRY
#undef PLIST_ENTRY
#undef PRLIST_ENTRY
#undef _SINGLE_LIST_ENTRY
#undef SINGLE_LIST_ENTRY
#undef PSINGLE_LIST_ENTRY
#undef _LIST_ENTRY32
#undef LIST_ENTRY32
#undef PLIST_ENTRY32
#undef _LIST_ENTRY64
#undef LIST_ENTRY64
#undef PLIST_ENTRY64
#undef _ENUM_FLAG_INTEGER_FOR_SIZE
#undef _ENUM_FLAG_SIZED_INTEGER
#undef _LARGE_INTEGER
#undef LARGE_INTEGER
#undef PLARGE_INTEGER
#undef _UNICODE_STRING
#undef UNICODE_STRING
#undef PUNICODE_STRING
#undef PCUNICODE_STRING
#undef _OBJECT_ATTRIBUTES
#undef OBJECT_ATTRIBUTES
#undef POBJECT_ATTRIBUTES
#undef Int64ShllMod32
#undef Int64ShraMod32
#undef Int64ShrlMod32

#include <WindowsX.h>
#include <CommCtrl.h>
#include <Shlobj.h>
#include <Shlwapi.h>
#include <shellscalingapi.h>
#include <dwmapi.h>
#include <Tpcshrd.h>
#include <wtsapi32.h>
#include <WinSock2.h>
#include <UserEnv.h>
#include <ntsecapi.h>

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
#undef _PROCESS_BASIC_INFORMATION
#undef PROCESS_BASIC_INFORMATION
#undef PPROCESS_BASIC_INFORMATION
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
#undef PSID
#undef _WINSTATIONINFOCLASS
#undef WINSTATIONINFOCLASS
#undef WinStationInformation

// Windows NT definations
#include "NTConst.h"
#include "NTTypes.h"
#include "NTStruct.h"
#include "NT_R3Shared.h"
#include "NT_MSTSTS.h"
#include "NT_NTDDK.h"
#include "NTAPI.h"
#include "NTObject.h"

#define PRTL_CONSTANT_UNICODE_STRING(s) ((&(UNICODE_STRING)RTL_CONSTANT_STRING(L##s)))
#define PRTL_CONSTANT_ANSI_STRING(s) ((&(ANSI_STRING)RTL_CONSTANT_STRING(s)))
#ifdef UNICODE
#define PRTL_CONSTANT_STRING PRTL_CONSTANT_UNICODE_STRING
#else
#define PRTL_CONSTANT_STRING PRTL_CONSTANT_ANSI_STRING
#endif

#define ANYSIZE_STRUCT_SIZE(structure, field, size) UFIELD_OFFSET(structure, field[size])
