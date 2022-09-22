#pragma once

// PEB[64/32] and TEB[64/32]

#include "NTADef.h"

// PEB

typedef struct _CLIENT_ID {
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

typedef struct _CLIENT_ID64 {
    VOID* PTR64 UniqueProcess;
    VOID* PTR64 UniqueThread;
} CLIENT_ID64, *PCLIENT_ID64;

typedef struct _CLIENT_ID32 {
    VOID* PTR32 UniqueProcess;
    VOID* PTR32 UniqueThread;
} CLIENT_ID32, *PCLIENT_ID32;

typedef struct _RTL_CRITICAL_SECTION64 RTL_CRITICAL_SECTION64, *PRTL_CRITICAL_SECTION64;
typedef struct _RTL_CRITICAL_SECTION32 RTL_CRITICAL_SECTION32, *PRTL_CRITICAL_SECTION32;

typedef struct _RTL_CRITICAL_SECTION_DEBUG64 {
    WORD Type;
    WORD CreatorBackTraceIndex;
    RTL_CRITICAL_SECTION64* PTR64 CriticalSection;
    LIST_ENTRY64 ProcessLocksList;
    DWORD EntryCount;
    DWORD ContentionCount;
    DWORD Flags;
    WORD CreatorBackTraceIndexHigh;
    WORD Identifier;
} RTL_CRITICAL_SECTION_DEBUG64, *PRTL_CRITICAL_SECTION_DEBUG64, RTL_RESOURCE_DEBUG64, *PRTL_RESOURCE_DEBUG64;

typedef struct _RTL_CRITICAL_SECTION_DEBUG32 {
    WORD Type;
    WORD CreatorBackTraceIndex;
    RTL_CRITICAL_SECTION32* PTR32 CriticalSection;
    LIST_ENTRY32 ProcessLocksList;
    DWORD EntryCount;
    DWORD ContentionCount;
    DWORD Flags;
    WORD CreatorBackTraceIndexHigh;
    WORD Identifier;
} RTL_CRITICAL_SECTION_DEBUG32, *PRTL_CRITICAL_SECTION_DEBUG32, RTL_RESOURCE_DEBUG32, *PRTL_RESOURCE_DEBUG32;

struct _RTL_CRITICAL_SECTION64 {
    RTL_CRITICAL_SECTION_DEBUG64* PTR64 DebugInfo;
    LONG LockCount;
    LONG RecursionCount;
    VOID* PTR64 OwningThread;
    VOID* PTR64 LockSemaphore;
    ULONGLONG SpinCount;
};

struct _RTL_CRITICAL_SECTION32 {
    RTL_CRITICAL_SECTION_DEBUG32* PTR32 DebugInfo;
    LONG LockCount;
    LONG RecursionCount;
    VOID* PTR32 OwningThread;
    VOID* PTR32 LockSemaphore;
    ULONG SpinCount;
};

typedef struct _RTL_DRIVE_LETTER_CURDIR {
    USHORT Flags;
    USHORT Length;
    UINT TimeStamp;
    STRING DosPath;
} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

typedef struct _RTL_DRIVE_LETTER_CURDIR64 {
    USHORT Flags;
    USHORT Length;
    UINT TimeStamp;
    STRING64 DosPath;
} RTL_DRIVE_LETTER_CURDIR64, *PRTL_DRIVE_LETTER_CURDIR64;

typedef struct _RTL_DRIVE_LETTER_CURDIR32 {
    USHORT Flags;
    USHORT Length;
    UINT TimeStamp;
    STRING32 DosPath;
} RTL_DRIVE_LETTER_CURDIR32, *PRTL_DRIVE_LETTER_CURDIR32;

typedef struct _CURDIR {
    UNICODE_STRING DosPath;
    HANDLE Handle;
} CURDIR, *PCURDIR;

typedef struct _CURDIR64 {
    UNICODE_STRING64 DosPath;
    VOID* PTR64 Handle;
} CURDIR64, *PCURDIR64;

typedef struct _CURDIR32 {
    UNICODE_STRING32 DosPath;
    VOID* PTR32 Handle;
} CURDIR32, *PCURDIR32;

typedef struct _RTL_USER_PROCESS_PARAMETERS {
    ULONG MaximumLength;
    ULONG Length;
    ULONG Flags;
    ULONG DebugFlags;
    HANDLE ConsoleHandle;
    ULONG ConsoleFlags;
    HANDLE StandardInput;
    HANDLE StandardOutput;
    HANDLE StandardError;
    CURDIR CurrentDirectory;
    UNICODE_STRING DllPath;
    UNICODE_STRING ImagePathName;
    UNICODE_STRING CommandLine;
    LPWSTR Environment;
    ULONG StartingX;
    ULONG StartingY;
    ULONG CountX;
    ULONG CountY;
    ULONG CountCharsX;
    ULONG CountCharsY;
    ULONG FillAttribute;
    ULONG WindowFlags;
    ULONG ShowWindowFlags;
    UNICODE_STRING WindowTitle;
    UNICODE_STRING DesktopInfo;
    UNICODE_STRING ShellInfo;
    UNICODE_STRING RuntimeData;
    RTL_DRIVE_LETTER_CURDIR CurrentDirectores[32];
    ULONG_PTR EnvironmentSize;
    ULONG_PTR EnvironmentVersion;
    PVOID PackageDependencyData;
    ULONG ProcessGroupId;
    ULONG LoaderThreads;
    UNICODE_STRING RedirectionDllName;
    UNICODE_STRING HeapPartitionName;
    PULONGLONG DefaultThreadpoolCpuSetMasks;
    ULONG DefaultThreadpoolCpuSetMaskCount;
    ULONG DefaultThreadpoolThreadMaximum;
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

typedef struct _RTL_USER_PROCESS_PARAMETERS64 {
    ULONG MaximumLength;
    ULONG Length;
    ULONG Flags;
    ULONG DebugFlags;
    VOID* PTR64 ConsoleHandle;
    ULONG ConsoleFlags;
    VOID* PTR64 StandardInput;
    VOID* PTR64 StandardOutput;
    VOID* PTR64 StandardError;
    CURDIR64 CurrentDirectory;
    UNICODE_STRING64 DllPath;
    UNICODE_STRING64 ImagePathName;
    UNICODE_STRING64 CommandLine;
    WCHAR* PTR64 Environment;
    ULONG StartingX;
    ULONG StartingY;
    ULONG CountX;
    ULONG CountY;
    ULONG CountCharsX;
    ULONG CountCharsY;
    ULONG FillAttribute;
    ULONG WindowFlags;
    ULONG ShowWindowFlags;
    UNICODE_STRING64 WindowTitle;
    UNICODE_STRING64 DesktopInfo;
    UNICODE_STRING64 ShellInfo;
    UNICODE_STRING64 RuntimeData;
    RTL_DRIVE_LETTER_CURDIR64 CurrentDirectores[32];
    ULONGLONG EnvironmentSize;
    ULONGLONG EnvironmentVersion;
    VOID* PTR64 PackageDependencyData;
    ULONG ProcessGroupId;
    ULONG LoaderThreads;
    UNICODE_STRING64 RedirectionDllName;
    UNICODE_STRING64 HeapPartitionName;
    ULONGLONG* PTR64 DefaultThreadpoolCpuSetMasks;
    ULONG DefaultThreadpoolCpuSetMaskCount;
    ULONG DefaultThreadpoolThreadMaximum;
} RTL_USER_PROCESS_PARAMETERS64, *PRTL_USER_PROCESS_PARAMETERS64;

typedef struct _RTL_USER_PROCESS_PARAMETERS32 {
    ULONG MaximumLength;
    ULONG Length;
    ULONG Flags;
    ULONG DebugFlags;
    VOID* PTR32 ConsoleHandle;
    ULONG ConsoleFlags;
    VOID* PTR32 StandardInput;
    VOID* PTR32 StandardOutput;
    VOID* PTR32 StandardError;
    CURDIR32 CurrentDirectory;
    UNICODE_STRING32 DllPath;
    UNICODE_STRING32 ImagePathName;
    UNICODE_STRING32 CommandLine;
    WCHAR* PTR32 Environment;
    ULONG StartingX;
    ULONG StartingY;
    ULONG CountX;
    ULONG CountY;
    ULONG CountCharsX;
    ULONG CountCharsY;
    ULONG FillAttribute;
    ULONG WindowFlags;
    ULONG ShowWindowFlags;
    UNICODE_STRING32 WindowTitle;
    UNICODE_STRING32 DesktopInfo;
    UNICODE_STRING32 ShellInfo;
    UNICODE_STRING32 RuntimeData;
    RTL_DRIVE_LETTER_CURDIR32 CurrentDirectores[32];
    ULONG EnvironmentSize;
    ULONG EnvironmentVersion;
    VOID* PTR32 PackageDependencyData;
    ULONG ProcessGroupId;
    ULONG LoaderThreads;
    UNICODE_STRING32 RedirectionDllName;
    UNICODE_STRING32 HeapPartitionName;
    ULONGLONG* PTR32 DefaultThreadpoolCpuSetMasks;
    ULONG DefaultThreadpoolCpuSetMaskCount;
    ULONG DefaultThreadpoolThreadMaximum;
} RTL_USER_PROCESS_PARAMETERS32, *PRTL_USER_PROCESS_PARAMETERS32;

typedef struct _RTL_BALANCED_NODE64 {
    union {
        struct _RTL_BALANCED_NODE64* PTR64 Children[2];
        struct {
            struct _RTL_BALANCED_NODE64* PTR64 Left;
            struct _RTL_BALANCED_NODE64* PTR64 Right;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

#define RTL_BALANCED_NODE_RESERVED_PARENT_MASK 3

    union {
        UCHAR Red : 1;
        UCHAR Balance : 2;
        ULONGLONG ParentValue;
    } DUMMYUNIONNAME2;
} RTL_BALANCED_NODE64, *PRTL_BALANCED_NODE64;

typedef struct _RTL_BALANCED_NODE32 {
    union {
        struct _RTL_BALANCED_NODE32* PTR32 Children[2];
        struct {
            struct _RTL_BALANCED_NODE32* PTR32 Left;
            struct _RTL_BALANCED_NODE32* PTR32 Right;
        } DUMMYSTRUCTNAME;
    } DUMMYUNIONNAME;

#define RTL_BALANCED_NODE_RESERVED_PARENT_MASK 3

    union {
        UCHAR Red : 1;
        UCHAR Balance : 2;
        ULONG ParentValue;
    } DUMMYUNIONNAME2;
} RTL_BALANCED_NODE32, *PRTL_BALANCED_NODE32;

typedef struct _LDR_DATA_TABLE_ENTRY {
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
    HMODULE DllBase;
    PVOID EntryPoint;
    ULONG SizeOfImage;
    UNICODE_STRING FullDllName;
    UNICODE_STRING BaseDllName;
    union {
        UCHAR FlagGroup[4];
        ULONG Flags;
        struct {
            ULONG PackagedBinary : 1;
            ULONG MarkedForRemoval : 1;
            ULONG ImageDll : 1;
            ULONG LoadNotificationsSent : 1;
            ULONG TelemetryEntryProcessed : 1;
            ULONG ProcessStaticImport : 1;
            ULONG InLegacyLists : 1;
            ULONG InIndexes : 1;
            ULONG ShimDll : 1;
            ULONG InExceptionTable : 1;
            ULONG ReservedFlags1 : 2;
            ULONG LoadInProgress : 1;
            ULONG LoadConfigProcessed : 1;
            ULONG EntryProcessed : 1;
            ULONG ProtectDelayLoad : 1;
            ULONG ReservedFlags3 : 2;
            ULONG DontCallForThreads : 1;
            ULONG ProcessAttachCalled : 1;
            ULONG ProcessAttachFailed : 1;
            ULONG CorDeferredValidate : 1;
            ULONG CorImage : 1;
            ULONG DontRelocate : 1;
            ULONG CorILOnly : 1;
            ULONG ChpeImage : 1;
            ULONG ChpeEmulatorImage : 1;
            ULONG ReservedFlags5 : 1;
            ULONG Redirected : 1;
            ULONG ReservedFlags6 : 2;
            ULONG CompatDatabaseProcessed : 1;
        };
    };
    USHORT ObsoleteLoadCount;
    USHORT TlsIndex;
    LIST_ENTRY HashLinks;
    ULONG TimeDateStamp;
    struct ACTIVATION_CONTEXT* EntryPointActivationContext;
    PVOID Lock;
    PLDR_DDAG_NODE DdagNode;
    LIST_ENTRY NodeModuleLink;
    struct LDRP_LOAD_CONTEXT* LoadContext;
    HMODULE ParentDllBase;
    PVOID SwitchBackContext;
    RTL_BALANCED_NODE BaseAddressIndexNode;
    RTL_BALANCED_NODE MappingInfoIndexNode;
    ULONG_PTR OriginalBase;
    LARGE_INTEGER LoadTime;
    ULONG BaseNameHashValue;
    LDR_DLL_LOAD_REASON LoadReason;
    ULONG ImplicitPathOptions;
    ULONG ReferenceCount;
    ULONG DependentLoadFlags;
    UCHAR SigningLevel;
    ULONG CheckSum;
    PVOID ActivePatchImageBase;
    LDR_HOT_PATCH_STATE HotPatchState;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

typedef struct _LDR_DATA_TABLE_ENTRY64 {
    LIST_ENTRY64 InLoadOrderModuleList;
    LIST_ENTRY64 InMemoryOrderModuleList;
    LIST_ENTRY64 InInitializationOrderModuleList;
    VOID* PTR64 DllBase;
    VOID* PTR64 EntryPoint;
    ULONG SizeOfImage;
    UNICODE_STRING64 FullDllName;
    UNICODE_STRING64 BaseDllName;
    union {
        UCHAR FlagGroup[4];
        ULONG Flags;
        struct {
            ULONG PackagedBinary : 1;
            ULONG MarkedForRemoval : 1;
            ULONG ImageDll : 1;
            ULONG LoadNotificationsSent : 1;
            ULONG TelemetryEntryProcessed : 1;
            ULONG ProcessStaticImport : 1;
            ULONG InLegacyLists : 1;
            ULONG InIndexes : 1;
            ULONG ShimDll : 1;
            ULONG InExceptionTable : 1;
            ULONG ReservedFlags1 : 2;
            ULONG LoadInProgress : 1;
            ULONG LoadConfigProcessed : 1;
            ULONG EntryProcessed : 1;
            ULONG ProtectDelayLoad : 1;
            ULONG ReservedFlags3 : 2;
            ULONG DontCallForThreads : 1;
            ULONG ProcessAttachCalled : 1;
            ULONG ProcessAttachFailed : 1;
            ULONG CorDeferredValidate : 1;
            ULONG CorImage : 1;
            ULONG DontRelocate : 1;
            ULONG CorILOnly : 1;
            ULONG ChpeImage : 1;
            ULONG ChpeEmulatorImage : 1;
            ULONG ReservedFlags5 : 1;
            ULONG Redirected : 1;
            ULONG ReservedFlags6 : 2;
            ULONG CompatDatabaseProcessed : 1;
        };
    };
    USHORT ObsoleteLoadCount;
    USHORT TlsIndex;
    LIST_ENTRY64 HashLinks;
    ULONG TimeDateStamp;
    struct ACTIVATION_CONTEXT* PTR64 EntryPointActivationContext;
    VOID* PTR64 Lock;
    LDR_DDAG_NODE* PTR64 DdagNode; // FIXME: Too complex
    LIST_ENTRY64 NodeModuleLink;
    struct LDRP_LOAD_CONTEXT* PTR64 LoadContext;
    VOID* PTR64 ParentDllBase;
    VOID* PTR64 SwitchBackContext;
    RTL_BALANCED_NODE64 BaseAddressIndexNode;
    RTL_BALANCED_NODE64 MappingInfoIndexNode;
    ULONGLONG OriginalBase;
    LARGE_INTEGER LoadTime;
    ULONG BaseNameHashValue;
    LDR_DLL_LOAD_REASON LoadReason;
    ULONG ImplicitPathOptions;
    ULONG ReferenceCount;
    ULONG DependentLoadFlags;
    UCHAR SigningLevel;
    ULONG CheckSum;
    VOID* PTR64 ActivePatchImageBase;
    LDR_HOT_PATCH_STATE HotPatchState;
} LDR_DATA_TABLE_ENTRY64, *PLDR_DATA_TABLE_ENTRY64;

typedef struct _LDR_DATA_TABLE_ENTRY32 {
    LIST_ENTRY32 InLoadOrderModuleList;
    LIST_ENTRY32 InMemoryOrderModuleList;
    LIST_ENTRY32 InInitializationOrderModuleList;
    VOID* PTR32 DllBase;
    VOID* PTR32 EntryPoint;
    ULONG SizeOfImage;
    UNICODE_STRING32 FullDllName;
    UNICODE_STRING32 BaseDllName;
    union {
        UCHAR FlagGroup[4];
        ULONG Flags;
        struct {
            ULONG PackagedBinary : 1;
            ULONG MarkedForRemoval : 1;
            ULONG ImageDll : 1;
            ULONG LoadNotificationsSent : 1;
            ULONG TelemetryEntryProcessed : 1;
            ULONG ProcessStaticImport : 1;
            ULONG InLegacyLists : 1;
            ULONG InIndexes : 1;
            ULONG ShimDll : 1;
            ULONG InExceptionTable : 1;
            ULONG ReservedFlags1 : 2;
            ULONG LoadInProgress : 1;
            ULONG LoadConfigProcessed : 1;
            ULONG EntryProcessed : 1;
            ULONG ProtectDelayLoad : 1;
            ULONG ReservedFlags3 : 2;
            ULONG DontCallForThreads : 1;
            ULONG ProcessAttachCalled : 1;
            ULONG ProcessAttachFailed : 1;
            ULONG CorDeferredValidate : 1;
            ULONG CorImage : 1;
            ULONG DontRelocate : 1;
            ULONG CorILOnly : 1;
            ULONG ChpeImage : 1;
            ULONG ChpeEmulatorImage : 1;
            ULONG ReservedFlags5 : 1;
            ULONG Redirected : 1;
            ULONG ReservedFlags6 : 2;
            ULONG CompatDatabaseProcessed : 1;
        };
    };
    USHORT ObsoleteLoadCount;
    USHORT TlsIndex;
    LIST_ENTRY32 HashLinks;
    ULONG TimeDateStamp;
    struct ACTIVATION_CONTEXT* PTR32 EntryPointActivationContext;
    VOID* PTR32 Lock;
    LDR_DDAG_NODE* PTR32 DdagNode; // FIXME: Too complex
    LIST_ENTRY32 NodeModuleLink;
    struct LDRP_LOAD_CONTEXT* PTR32 LoadContext;
    VOID* PTR32 ParentDllBase;
    VOID* PTR32 SwitchBackContext;
    RTL_BALANCED_NODE32 BaseAddressIndexNode;
    RTL_BALANCED_NODE32 MappingInfoIndexNode;
    ULONG OriginalBase;
    LARGE_INTEGER LoadTime;
    ULONG BaseNameHashValue;
    LDR_DLL_LOAD_REASON LoadReason;
    ULONG ImplicitPathOptions;
    ULONG ReferenceCount;
    ULONG DependentLoadFlags;
    UCHAR SigningLevel;
    ULONG CheckSum;
    VOID* PTR32 ActivePatchImageBase;
    LDR_HOT_PATCH_STATE HotPatchState;
} LDR_DATA_TABLE_ENTRY32, *PLDR_DATA_TABLE_ENTRY32;

typedef struct _PEB_LDR_DATA {
    ULONG Length;
    BOOL Initialized;
    PVOID SsHandle;
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
    PVOID EntryInProgress;
    PVOID ShutdownInProgress;
    PVOID ShutdownThreadId;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _PEB_LDR_DATA64 {
    ULONG Length;
    BOOL Initialized;
    VOID* PTR64 SsHandle;
    LIST_ENTRY64 InLoadOrderModuleList;
    LIST_ENTRY64 InMemoryOrderModuleList;
    LIST_ENTRY64 InInitializationOrderModuleList;
    VOID* PTR64 EntryInProgress;
    VOID* PTR64 ShutdownInProgress;
    VOID* PTR64 ShutdownThreadId;
} PEB_LDR_DATA64, *PPEB_LDR_DATA64;

typedef struct _PEB_LDR_DATA32 {
    ULONG Length;
    BOOL Initialized;
    VOID* PTR32 SsHandle;
    LIST_ENTRY32 InLoadOrderModuleList;
    LIST_ENTRY32 InMemoryOrderModuleList;
    LIST_ENTRY32 InInitializationOrderModuleList;
    VOID* PTR32 EntryInProgress;
    VOID* PTR32 ShutdownInProgress;
    VOID* PTR32 ShutdownThreadId;
} PEB_LDR_DATA32, *PPEB_LDR_DATA32;

typedef struct _PEB {
    UCHAR InheritedAddressSpace;
    UCHAR ReadImageFileExecOptions;
    UCHAR BeingDebugged;
    union {
        UCHAR BitField;
        struct {
            UCHAR ImageUsesLargePages : 1;
            UCHAR IsProtectedProcess : 1;
            UCHAR IsImageDynamicallyRelocated : 1;
            UCHAR SkipPatchingUser32Forwarders : 1;
            UCHAR IsPackagedProcess : 1;
            UCHAR IsAppContainer : 1;
            UCHAR IsProtectedProcessLight : 1;
            UCHAR IsLongPathAwareProcess : 1;
        };
    };
#if _WIN64
    UCHAR Padding0[4];
#endif
    HANDLE Mutant;
    HMODULE ImageBaseAddress;
    PPEB_LDR_DATA Ldr;
    PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
    PVOID SubSystemData;
    HANDLE ProcessHeap;
    PRTL_CRITICAL_SECTION FastPebLock;
    PSLIST_HEADER AtlThunkSListPtr;
    PVOID IFEOKey;
    union {
        ULONG CrossProcessFlags;
        struct {
            ULONG ProcessInJob : 1;
            ULONG ProcessInitializing : 1;
            ULONG ProcessUsingVEH : 1;
            ULONG ProcessUsingVCH : 1;
            ULONG ProcessUsingFTH : 1;
            ULONG ProcessPreviouslyThrottled : 1;
            ULONG ProcessCurrentlyThrottled : 1;
            ULONG ProcessImagesHotPatched : 1;
            ULONG ReservedBits0 : 24;
        };
    };
#if _WIN64
    UCHAR Padding1[4];
#endif
    union {
        PVOID KernelCallbackTable;
        PVOID UserSharedInfoPtr;
    };
    ULONG SystemReserved;
    ULONG AtlThunkSListPtr32;
    PVOID ApiSetMap;
    ULONG TlsExpansionCounter;
#if _WIN64
    UCHAR Padding2[4];
#endif
    PRTL_BITMAP TlsBitmap;
    ULONG TlsBitmapBits[2];
    PVOID ReadOnlySharedMemoryBase;
    PVOID SharedData;
    PVOID* ReadOnlyStaticServerData;
    PVOID AnsiCodePageData;
    PVOID OemCodePageData;
    PVOID UnicodeCaseTableData;
    ULONG NumberOfProcessors;
    ULONG NtGlobalFlag;
    LARGE_INTEGER CriticalSectionTimeout;
    ULONG_PTR HeapSegmentReserve;
    ULONG_PTR HeapSegmentCommit;
    ULONG_PTR HeapDeCommitTotalFreeThreshold;
    ULONG_PTR HeapDeCommitFreeBlockThreshold;
    ULONG NumberOfHeaps;
    ULONG MaximumNumberOfHeaps;
    PVOID ProcessHeaps;
    PVOID GdiSharedHandleTable;
    PVOID ProcessStarterHelper;
    ULONG GdiDCAttributeList;
#if _WIN64
    UCHAR Padding3[4];
#endif
    PRTL_CRITICAL_SECTION LoaderLock;
    ULONG OSMajorVersion;
    ULONG OSMinorVersion;
    USHORT OSBuildNumber;
    USHORT OSCSDVersion;
    ULONG OSPlatformId;
    ULONG ImageSubsystem;
    ULONG ImageSubsystemMajorVersion;
    ULONG ImageSubsystemMinorVersion;
#if _WIN64
    UCHAR Padding4[4];
#endif
    ULONG_PTR ActiveProcessAffinityMask;
#if _WIN64
    ULONG GdiHandleBuffer[60];
#else
    ULONG GdiHandleBuffer[34];
#endif
    PVOID PostProcessInitRoutine;
    PRTL_BITMAP TlsExpansionBitmap;
    ULONG TlsExpansionBitmapBits[32];
    ULONG SessionId;
#ifdef _WIN64
    UCHAR Padding5[4];
#endif
    ULARGE_INTEGER AppCompatFlags;
    ULARGE_INTEGER AppCompatFlagsUser;
    PVOID pShimData;
    PVOID AppCompatInfo;
    UNICODE_STRING CSDVersion;
    PACTIVATION_CONTEXT_DATA ActivationContextData;
    PASSEMBLY_STORAGE_MAP ProcessAssemblyStorageMap;
    PACTIVATION_CONTEXT_DATA SystemDefaultActivationContextData;
    PASSEMBLY_STORAGE_MAP SystemAssemblyStorageMap;
    ULONG_PTR MinimumStackCommit;
    PVOID SparePointers[2];
    PVOID PatchLoaderData;
    struct CHPEV2_PROCESS_INFO* ChpeV2ProcessInfo;
    ULONG AppModelFeatureState;
    ULONG SpareUlongs[2];
    USHORT ActiveCodePage;
    USHORT OemCodePage;
    USHORT UseCaseMapping;
    USHORT UnusedNlsField;
    PVOID WerRegistrationData;
    PVOID WerShipAssertPtr;
#ifdef _WIN64
    PVOID EcCodeBitMap;
#else
    PVOID Spare;
#endif
    PVOID pImageHeaderHash;
    union {
        ULONG TracingFlags;
        struct {
            ULONG HeapTracingEnabled : 1;
            ULONG CritSecTracingEnabled : 1;
            ULONG LibLoaderTracingEnabled : 1;
            ULONG SpareTracingBits : 29;
        };
    };
#ifdef _WIN64
    UCHAR Padding6[4];
#endif
    ULONGLONG CsrServerReadOnlySharedMemoryBase;
    ULONG_PTR TppWorkerpListLock;
    LIST_ENTRY TppWorkerpList;
    PVOID WaitOnAddressHashTable[128];
    PVOID TelemetryCoverageHeader;
    ULONG CloudFileFlags;
    ULONG CloudFileDiagFlags;
    CHAR PlaceholderCompatibilityMode;
    CHAR PlaceholderCompatibilityModeReserved[7];
    PLEAP_SECOND_DATA LeapSecondData;
    union {
        ULONG LeapSecondFlags;
        struct {
            ULONG SixtySecondEnabled : 1;
            ULONG Reserved : 31;
        };
    };
    ULONG NtGlobalFlag2;
    ULONGLONG ExtendedFeatureDisableMask;
} PEB, *PPEB;

typedef struct _PEB64 {
    UCHAR InheritedAddressSpace;
    UCHAR ReadImageFileExecOptions;
    UCHAR BeingDebugged;
    union {
        UCHAR BitField;
        struct {
            UCHAR ImageUsesLargePages : 1;
            UCHAR IsProtectedProcess : 1;
            UCHAR IsImageDynamicallyRelocated : 1;
            UCHAR SkipPatchingUser32Forwarders : 1;
            UCHAR IsPackagedProcess : 1;
            UCHAR IsAppContainer : 1;
            UCHAR IsProtectedProcessLight : 1;
            UCHAR IsLongPathAwareProcess : 1;
        };
    };
#if _WIN64
    UCHAR Padding0[4];
#endif
    VOID* PTR64 Mutant;
    VOID* PTR64 ImageBaseAddress;
    PEB_LDR_DATA64* PTR64 Ldr;
    PRTL_USER_PROCESS_PARAMETERS64 ProcessParameters;
    VOID* PTR64 SubSystemData;
    VOID* PTR64 ProcessHeap;
    RTL_CRITICAL_SECTION64* PTR64 FastPebLock;
    struct SLIST_HEADER* PTR64 AtlThunkSListPtr; // FIXME: SLIST_HEADER is depends on platform
    VOID* PTR64 IFEOKey;
    union {
        ULONG CrossProcessFlags;
        struct {
            ULONG ProcessInJob : 1;
            ULONG ProcessInitializing : 1;
            ULONG ProcessUsingVEH : 1;
            ULONG ProcessUsingVCH : 1;
            ULONG ProcessUsingFTH : 1;
            ULONG ProcessPreviouslyThrottled : 1;
            ULONG ProcessCurrentlyThrottled : 1;
            ULONG ProcessImagesHotPatched : 1;
            ULONG ReservedBits0 : 24;
        };
    };
    UCHAR Padding1[4];
    union {
        VOID* PTR64 KernelCallbackTable;
        VOID* PTR64 UserSharedInfoPtr;
    };
    ULONG SystemReserved;
    ULONG AtlThunkSListPtr32;
    VOID* PTR64 ApiSetMap;
    ULONG TlsExpansionCounter;
    UCHAR Padding2[4];
    RTL_BITMAP64* PTR64 TlsBitmap;
    ULONG TlsBitmapBits[2];
    VOID* PTR64 ReadOnlySharedMemoryBase;
    VOID* PTR64 SharedData;
    VOID* PTR64* PTR64 ReadOnlyStaticServerData;
    VOID* PTR64 AnsiCodePageData;
    VOID* PTR64 OemCodePageData;
    VOID* PTR64 UnicodeCaseTableData;
    ULONG NumberOfProcessors;
    ULONG NtGlobalFlag;
    LARGE_INTEGER CriticalSectionTimeout;
    ULONGLONG HeapSegmentReserve;
    ULONGLONG HeapSegmentCommit;
    ULONGLONG HeapDeCommitTotalFreeThreshold;
    ULONGLONG HeapDeCommitFreeBlockThreshold;
    ULONG NumberOfHeaps;
    ULONG MaximumNumberOfHeaps;
    VOID* PTR64 ProcessHeaps;
    VOID* PTR64 GdiSharedHandleTable;
    VOID* PTR64 ProcessStarterHelper;
    ULONG GdiDCAttributeList;
    UCHAR Padding3[4];
    RTL_CRITICAL_SECTION64* PTR64 LoaderLock;
    ULONG OSMajorVersion;
    ULONG OSMinorVersion;
    USHORT OSBuildNumber;
    USHORT OSCSDVersion;
    ULONG OSPlatformId;
    ULONG ImageSubsystem;
    ULONG ImageSubsystemMajorVersion;
    ULONG ImageSubsystemMinorVersion;
    UCHAR Padding4[4];
    ULONGLONG ActiveProcessAffinityMask;
    ULONG GdiHandleBuffer[60];
    VOID* PTR64 PostProcessInitRoutine;
    RTL_BITMAP64* PTR64 TlsExpansionBitmap;
    ULONG TlsExpansionBitmapBits[32];
    ULONG SessionId;
    UCHAR Padding5[4];
    ULARGE_INTEGER AppCompatFlags;
    ULARGE_INTEGER AppCompatFlagsUser;
    VOID* PTR64 pShimData;
    VOID* PTR64 AppCompatInfo;
    UNICODE_STRING64 CSDVersion;
    ACTIVATION_CONTEXT_DATA* PTR64 ActivationContextData;
    ASSEMBLY_STORAGE_MAP* PTR64 ProcessAssemblyStorageMap;
    ACTIVATION_CONTEXT_DATA* PTR64 SystemDefaultActivationContextData;
    ASSEMBLY_STORAGE_MAP* PTR64 SystemAssemblyStorageMap;
    ULONGLONG MinimumStackCommit;
    VOID* PTR64 SparePointers[2];
    VOID* PTR64 PatchLoaderData;
    struct CHPEV2_PROCESS_INFO* PTR64 ChpeV2ProcessInfo;
    ULONG AppModelFeatureState;
    ULONG SpareUlongs[2];
    USHORT ActiveCodePage;
    USHORT OemCodePage;
    USHORT UseCaseMapping;
    USHORT UnusedNlsField;
    VOID* PTR64 WerRegistrationData;
    VOID* PTR64 WerShipAssertPtr;
    VOID* PTR64 EcCodeBitMap;
    VOID* PTR64 pImageHeaderHash;
    union {
        ULONG TracingFlags;
        struct {
            ULONG HeapTracingEnabled : 1;
            ULONG CritSecTracingEnabled : 1;
            ULONG LibLoaderTracingEnabled : 1;
            ULONG SpareTracingBits : 29;
        };
    };
    UCHAR Padding6[4];
    ULONGLONG CsrServerReadOnlySharedMemoryBase;
    ULONGLONG TppWorkerpListLock;
    LIST_ENTRY64 TppWorkerpList;
    VOID* PTR64 WaitOnAddressHashTable[128];
    VOID* PTR64 TelemetryCoverageHeader;
    ULONG CloudFileFlags;
    ULONG CloudFileDiagFlags;
    CHAR PlaceholderCompatibilityMode;
    CHAR PlaceholderCompatibilityModeReserved[7];
    LEAP_SECOND_DATA* PTR64 LeapSecondData;
    union {
        ULONG LeapSecondFlags;
        struct {
            ULONG SixtySecondEnabled : 1;
            ULONG Reserved : 31;
        };
    };
    ULONG NtGlobalFlag2;
    ULONGLONG ExtendedFeatureDisableMask;
} PEB64, *PPEB64;

typedef struct _PEB32 {
    UCHAR InheritedAddressSpace;
    UCHAR ReadImageFileExecOptions;
    UCHAR BeingDebugged;
    union {
        UCHAR BitField;
        struct {
            UCHAR ImageUsesLargePages : 1;
            UCHAR IsProtectedProcess : 1;
            UCHAR IsImageDynamicallyRelocated : 1;
            UCHAR SkipPatchingUser32Forwarders : 1;
            UCHAR IsPackagedProcess : 1;
            UCHAR IsAppContainer : 1;
            UCHAR IsProtectedProcessLight : 1;
            UCHAR IsLongPathAwareProcess : 1;
        };
    };
    VOID* PTR32 Mutant;
    VOID* PTR32 ImageBaseAddress;
    PEB_LDR_DATA32* PTR32 Ldr;
    RTL_USER_PROCESS_PARAMETERS32* PTR32 ProcessParameters;
    VOID* PTR32 SubSystemData;
    VOID* PTR32 ProcessHeap;
    RTL_CRITICAL_SECTION32* PTR32 FastPebLock;
    struct SLIST_HEADER* PTR32 AtlThunkSListPtr; // FIXME: SLIST_HEADER is depends on platform
    VOID* PTR32 IFEOKey;
    union {
        ULONG CrossProcessFlags;
        struct {
            ULONG ProcessInJob : 1;
            ULONG ProcessInitializing : 1;
            ULONG ProcessUsingVEH : 1;
            ULONG ProcessUsingVCH : 1;
            ULONG ProcessUsingFTH : 1;
            ULONG ProcessPreviouslyThrottled : 1;
            ULONG ProcessCurrentlyThrottled : 1;
            ULONG ProcessImagesHotPatched : 1;
            ULONG ReservedBits0 : 24;
        };
    };
    union {
        VOID* PTR32 KernelCallbackTable;
        VOID* PTR32 UserSharedInfoPtr;
    };
    ULONG SystemReserved;
    ULONG AtlThunkSListPtr32;
    VOID* PTR32 ApiSetMap;
    ULONG TlsExpansionCounter;
    RTL_BITMAP32* PTR32 TlsBitmap;
    ULONG TlsBitmapBits[2];
    VOID* PTR32 ReadOnlySharedMemoryBase;
    VOID* PTR32 SharedData;
    VOID* PTR32* PTR32 ReadOnlyStaticServerData;
    VOID* PTR32 AnsiCodePageData;
    VOID* PTR32 OemCodePageData;
    VOID* PTR32 UnicodeCaseTableData;
    ULONG NumberOfProcessors;
    ULONG NtGlobalFlag;
    LARGE_INTEGER CriticalSectionTimeout;
    ULONG HeapSegmentReserve;
    ULONG HeapSegmentCommit;
    ULONG HeapDeCommitTotalFreeThreshold;
    ULONG HeapDeCommitFreeBlockThreshold;
    ULONG NumberOfHeaps;
    ULONG MaximumNumberOfHeaps;
    VOID* PTR32 ProcessHeaps;
    VOID* PTR32 GdiSharedHandleTable;
    VOID* PTR32 ProcessStarterHelper;
    ULONG GdiDCAttributeList;
    RTL_CRITICAL_SECTION32* PTR32 LoaderLock;
    ULONG OSMajorVersion;
    ULONG OSMinorVersion;
    USHORT OSBuildNumber;
    USHORT OSCSDVersion;
    ULONG OSPlatformId;
    ULONG ImageSubsystem;
    ULONG ImageSubsystemMajorVersion;
    ULONG ImageSubsystemMinorVersion;
    ULONG ActiveProcessAffinityMask;
    ULONG GdiHandleBuffer[34];
    VOID* PTR32 PostProcessInitRoutine;
    RTL_BITMAP32* PTR32 TlsExpansionBitmap;
    ULONG TlsExpansionBitmapBits[32];
    ULONG SessionId;
    ULARGE_INTEGER AppCompatFlags;
    ULARGE_INTEGER AppCompatFlagsUser;
    VOID* PTR32 pShimData;
    VOID* PTR32 AppCompatInfo;
    UNICODE_STRING32 CSDVersion;
    ACTIVATION_CONTEXT_DATA* PTR32 ActivationContextData;
    ASSEMBLY_STORAGE_MAP32* PTR32 ProcessAssemblyStorageMap;
    ACTIVATION_CONTEXT_DATA* PTR32 SystemDefaultActivationContextData;
    ASSEMBLY_STORAGE_MAP32* PTR32 SystemAssemblyStorageMap;
    ULONG MinimumStackCommit;
    VOID* PTR32 SparePointers[2];
    VOID* PTR32 PatchLoaderData;
    struct CHPEV2_PROCESS_INFO* PTR32 ChpeV2ProcessInfo;
    ULONG AppModelFeatureState;
    ULONG SpareUlongs[2];
    USHORT ActiveCodePage;
    USHORT OemCodePage;
    USHORT UseCaseMapping;
    USHORT UnusedNlsField;
    VOID* PTR32 WerRegistrationData;
    VOID* PTR32 WerShipAssertPtr;
    VOID* PTR32 Spare;
    VOID* PTR32 pImageHeaderHash;
    union {
        ULONG TracingFlags;
        struct {
            ULONG HeapTracingEnabled : 1;
            ULONG CritSecTracingEnabled : 1;
            ULONG LibLoaderTracingEnabled : 1;
            ULONG SpareTracingBits : 29;
        };
    };
    ULONGLONG CsrServerReadOnlySharedMemoryBase;
    ULONG TppWorkerpListLock;
    LIST_ENTRY32 TppWorkerpList;
    VOID* PTR32 WaitOnAddressHashTable[128];
    VOID* PTR32 TelemetryCoverageHeader;
    ULONG CloudFileFlags;
    ULONG CloudFileDiagFlags;
    CHAR PlaceholderCompatibilityMode;
    CHAR PlaceholderCompatibilityModeReserved[7];
    LEAP_SECOND_DATA* PTR32 LeapSecondData;
    union {
        ULONG LeapSecondFlags;
        struct {
            ULONG SixtySecondEnabled : 1;
            ULONG Reserved : 31;
        };
    };
    ULONG NtGlobalFlag2;
    ULONGLONG ExtendedFeatureDisableMask;
} PEB32, *PPEB32;

// TEB

typedef struct _GDI_TEB_BATCH {
    struct {
        ULONG Offset : 31;
        BOOL HasRenderingCommand : 1;
    };
    ULONG_PTR HDC;
    ULONG Buffer[310];
} GDI_TEB_BATCH, *PGDI_TEB_BATCH;

typedef struct _GDI_TEB_BATCH64 {
    struct {
        ULONG Offset : 31;
        BOOL HasRenderingCommand : 1;
    };
    ULONGLONG HDC;
    ULONG Buffer[310];
} GDI_TEB_BATCH64, *PGDI_TEB_BATCH64;

typedef struct _GDI_TEB_BATCH32 {
    struct {
        ULONG Offset : 31;
        BOOL HasRenderingCommand : 1;
    };
    ULONG HDC;
    ULONG Buffer[310];
} GDI_TEB_BATCH32, *PGDI_TEB_BATCH32;

typedef struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME RTL_ACTIVATION_CONTEXT_STACK_FRAME, *PRTL_ACTIVATION_CONTEXT_STACK_FRAME;
typedef struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME64 RTL_ACTIVATION_CONTEXT_STACK_FRAME64, *PRTL_ACTIVATION_CONTEXT_STACK_FRAME64;
typedef struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME32 RTL_ACTIVATION_CONTEXT_STACK_FRAME32, *PRTL_ACTIVATION_CONTEXT_STACK_FRAME32;

struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME {
    struct RTL_ACTIVATION_CONTEXT_STACK_FRAME* Previous;
    struct ACTIVATION_CONTEXT* ActivationContext;
    DWORD Flags;
};

struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME64 {
    struct RTL_ACTIVATION_CONTEXT_STACK_FRAME* PTR64 Previous;
    struct ACTIVATION_CONTEXT* PTR64 ActivationContext;
    ULONG Flags;
};

struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME32 {
    struct RTL_ACTIVATION_CONTEXT_STACK_FRAME* PTR32 Previous;
    struct ACTIVATION_CONTEXT* PTR32 ActivationContext;
    ULONG Flags;
};

typedef struct _ACTIVATION_CONTEXT_STACK {
    PRTL_ACTIVATION_CONTEXT_STACK_FRAME ActiveFrame;
    LIST_ENTRY FrameListCache;
    ULONG Flags;
    ULONG NextCookieSequenceNumber;
    ULONG StackId;
} ACTIVATION_CONTEXT_STACK, *PACTIVATION_CONTEXT_STACK;

typedef struct _ACTIVATION_CONTEXT_STACK64 {
    RTL_ACTIVATION_CONTEXT_STACK_FRAME64* PTR64 ActiveFrame;
    LIST_ENTRY64 FrameListCache;
    ULONG Flags;
    ULONG NextCookieSequenceNumber;
    ULONG StackId;
} ACTIVATION_CONTEXT_STACK64, *PACTIVATION_CONTEXT_STACK64;

typedef struct _ACTIVATION_CONTEXT_STACK32 {
    RTL_ACTIVATION_CONTEXT_STACK_FRAME32* PTR32 ActiveFrame;
    LIST_ENTRY32 FrameListCache;
    ULONG Flags;
    ULONG NextCookieSequenceNumber;
    ULONG StackId;
} ACTIVATION_CONTEXT_STACK32, *PACTIVATION_CONTEXT_STACK32;

typedef struct _TEB_ACTIVE_FRAME_CONTEXT {
    ULONG Flags;
    UCHAR Padding[4];
    PCHAR FrameName;
} TEB_ACTIVE_FRAME_CONTEXT, *PTEB_ACTIVE_FRAME_CONTEXT;

typedef struct _TEB_ACTIVE_FRAME_CONTEXT64 {
    ULONG Flags;
    UCHAR Padding[4];
    CHAR* PTR64 FrameName;
} TEB_ACTIVE_FRAME_CONTEXT64, *PTEB_ACTIVE_FRAME_CONTEXT64;

typedef struct _TEB_ACTIVE_FRAME_CONTEXT32 {
    ULONG Flags;
    UCHAR Padding[4];
    CHAR* PTR32 FrameName;
} TEB_ACTIVE_FRAME_CONTEXT32, *PTEB_ACTIVE_FRAME_CONTEXT32;

typedef struct _TEB_ACTIVE_FRAME TEB_ACTIVE_FRAME, *PTEB_ACTIVE_FRAME;
typedef struct _TEB_ACTIVE_FRAME64 TEB_ACTIVE_FRAME64, *PTEB_ACTIVE_FRAME64;
typedef struct _TEB_ACTIVE_FRAME32 TEB_ACTIVE_FRAME32, *PTEB_ACTIVE_FRAME32;

struct _TEB_ACTIVE_FRAME {
    DWORD Flags;
#if _WIN64
    UCHAR Padding[4];
#endif
    struct TEB_ACTIVE_FRAME* Previous;
    PTEB_ACTIVE_FRAME_CONTEXT Context;
};

struct _TEB_ACTIVE_FRAME64 {
    DWORD Flags;
    UCHAR Padding[4];
    struct TEB_ACTIVE_FRAME64* Previous;
    TEB_ACTIVE_FRAME_CONTEXT64* PTR64 Context;
};

struct _TEB_ACTIVE_FRAME32 {
    DWORD Flags;
    struct TEB_ACTIVE_FRAME32* Previous;
    TEB_ACTIVE_FRAME_CONTEXT32* PTR32 Context;
};

typedef struct _TEB {
    NT_TIB NtTib;
    LPWSTR EnvironmentPointer;
    CLIENT_ID ClientId;
    PVOID ActiveRpcHandle;
    PVOID ThreadLocalStoragePointer;
    PPEB ProcessEnvironmentBlock;
    ULONG LastErrorValue;
    ULONG CountOfOwnedCriticalSections;
    PVOID CsrClientThread;
    PVOID Win32ThreadInfo;
    ULONG User32Reserved[26];
    ULONG UserReserved[5];
    PVOID WOW32Reserved;
    ULONG CurrentLocale;
    ULONG FpSoftwareStatusRegister;
    PVOID ReservedForDebuggerInstrumentation[16];
#ifdef _WIN64
    PVOID SystemReserved1[30];
#else
    PVOID SystemReserved1[26];
#endif
    CHAR PlaceholderCompatibilityMode;
    UCHAR PlaceholderHydrationAlwaysExplicit;
    CHAR PlaceholderReserved[10];
    ULONG ProxiedProcessId;
    ACTIVATION_CONTEXT_STACK _ActivationStack;
    UCHAR WorkingOnBehalfTicket[8];
    LONG ExceptionCode;
#ifdef _WIN64
    UCHAR Padding0[4];
#endif
    PACTIVATION_CONTEXT_STACK ActivationContextStackPointer;
    PVOID InstrumentationCallbackSp;
    PVOID InstrumentationCallbackPreviousPc;
    PVOID InstrumentationCallbackPreviousSp;
#ifdef _WIN64
    ULONG TxFsContext;
    BOOLEAN InstrumentationCallbackDisabled;
    UCHAR UnalignedLoadStoreExceptions;
    UCHAR Padding1[2];
#else
    UCHAR InstrumentationCallbackDisabled;
    UCHAR SpareBytes[23];
    DWORD TxFsContext;
#endif
    GDI_TEB_BATCH GdiTebBatch;
    CLIENT_ID RealClientId;
    PVOID GdiCachedProcessHandle;
    ULONG GdiClientPID;
    ULONG GdiClientTID;
    PVOID GdiThreadLocalInfo;
    ULONG_PTR Win32ClientInfo[62];
    PVOID glDispatchTable[233];
    ULONG_PTR glReserved1[29];
    PVOID glReserved2;
    PVOID glSectionInfo;
    PVOID glSection;
    PVOID glTable;
    PVOID glCurrentRC;
    PVOID glContext;
    ULONG LastStatusValue;
#ifdef _WIN64
    UCHAR Padding2[4];
#endif
    UNICODE_STRING StaticUnicodeString;
    WCHAR StaticUnicodeBuffer[261];
#ifdef _WIN64
    UCHAR Padding3[6];
#endif
    PVOID DeallocationStack;
    PVOID TlsSlots[64];
    LIST_ENTRY TlsLinks;
    PVOID Vdm;
    PVOID ReservedForNtRpc;
    PVOID DbgSsReserved[2];
    ULONG HardErrorMode;
#ifdef _WIN64
    UCHAR Padding4[4];
    PVOID Instrumentation[11];
#else
    PVOID Instrumentation[9];
#endif
    GUID ActivityId;
    PVOID SubProcessTag;
    PVOID PerflibData;
    PVOID EtwTraceData;
    PVOID WinSockData;
    ULONG GdiBatchCount;
    union {
        PROCESSOR_NUMBER CurrentIdealProcessor;
        union {
            DWORD IdealProcessorValue;
            struct {
                UCHAR ReservedPad0;
                UCHAR ReservedPad1;
                UCHAR ReservedPad2;
                UCHAR IdealProcessor;
            };
        };
    };
    ULONG GuaranteedStackBytes;
#ifdef _WIN64
    UCHAR Padding5[4];
#endif
    PVOID ReservedForPerf;
    PVOID ReservedForOle;
    ULONG WaitingOnLoaderLock;
#ifdef _WIN64
    UCHAR Padding6[4];
#endif
    PVOID SavedPriorityState;
    ULONG_PTR ReservedForCodeCoverage;
    PVOID ThreadPoolData;
    PVOID TlsExpansionSlots;
#ifdef _WIN64
    struct CHPEV2_CPUAREA_INFO* PTR64 ChpeV2CpuAreaInfo;
    PVOID Unused;
#endif
    ULONG MuiGeneration;
    ULONG IsImpersonating;
    PVOID NlsCache;
    PVOID pShimData;
    ULONG HeapData;
#ifdef _WIN64
    UCHAR Padding7[4];
#endif
    PVOID CurrentTransactionHandle;
    PTEB_ACTIVE_FRAME ActiveFrame;
    PVOID FlsData;
    PVOID PreferredLanguages;
    PVOID UserPrefLanguages;
    PVOID MergedPrefLanguages;
    ULONG MuiImpersonation;
    union {
        USHORT CrossTebFlags;
        struct {
            USHORT SpareCrossTebBits : 16;
        };
    };
    union {
        USHORT SameTebFlags;
        struct {
            USHORT SafeThunkCall : 1;
            USHORT InDebugPrint : 1;
            USHORT HasFiberData : 1;
            USHORT SkipThreadAttach : 1;
            USHORT WerInShipAssertCode : 1;
            USHORT RanProcessInit : 1;
            USHORT ClonedThread : 1;
            USHORT SuppressDebugMsg : 1;
            USHORT DisableUserStackWalk : 1;
            USHORT RtlExceptionAttached : 1;
            USHORT InitialThread : 1;
            USHORT SessionAware : 1;
            USHORT LoadOwner : 1;
            USHORT LoaderWorker : 1;
            USHORT SkipLoaderInit : 1;
            USHORT SkipFileAPIBrokering : 1;
        };
    };
    PVOID TxnScopeEnterCallback;
    PVOID TxnScopeExitCallback;
    PVOID TxnScopeContext;
    ULONG LockCount;
    LONG WowTebOffset;
    PVOID ResourceRetValue;
    PVOID ReservedForWdf;
    ULONGLONG ReservedForCrt;
    GUID EffectiveContainerId;
    ULONGLONG LastSleepCounter;
    ULONG SpinCallCount;
#ifdef _WIN64
    UCHAR Padding8[4];
#endif
    ULONGLONG ExtendedFeatureDisableMask;
} TEB, *PTEB;

typedef struct _TEB64 {
    NT_TIB64 NtTib;
    WCHAR* PTR64 EnvironmentPointer;
    CLIENT_ID64 ClientId;
    VOID* PTR64 ActiveRpcHandle;
    VOID* PTR64 ThreadLocalStoragePointer;
    PEB64* PTR64 ProcessEnvironmentBlock;
    ULONG LastErrorValue;
    ULONG CountOfOwnedCriticalSections;
    VOID* PTR64 CsrClientThread;
    VOID* PTR64 Win32ThreadInfo;
    ULONG User32Reserved[26];
    ULONG UserReserved[5];
    VOID* PTR64 WOW32Reserved;
    ULONG CurrentLocale;
    ULONG FpSoftwareStatusRegister;
    VOID* PTR64 ReservedForDebuggerInstrumentation[16];
    VOID* PTR64 SystemReserved1[30];
    CHAR PlaceholderCompatibilityMode;
    UCHAR PlaceholderHydrationAlwaysExplicit;
    CHAR PlaceholderReserved[10];
    ULONG ProxiedProcessId;
    ACTIVATION_CONTEXT_STACK64 _ActivationStack;
    UCHAR WorkingOnBehalfTicket[8];
    LONG ExceptionCode;
    UCHAR Padding0[4];
    ACTIVATION_CONTEXT_STACK64* PTR64 ActivationContextStackPointer;
    VOID* PTR64 InstrumentationCallbackSp;
    VOID* PTR64 InstrumentationCallbackPreviousPc;
    VOID* PTR64 InstrumentationCallbackPreviousSp;
    ULONG TxFsContext;
    BOOLEAN InstrumentationCallbackDisabled;
    UCHAR UnalignedLoadStoreExceptions;
    UCHAR Padding1[2];
    GDI_TEB_BATCH64 GdiTebBatch;
    CLIENT_ID64 RealClientId;
    VOID* PTR64 GdiCachedProcessHandle;
    ULONG GdiClientPID;
    ULONG GdiClientTID;
    VOID* PTR64 GdiThreadLocalInfo;
    ULONGLONG Win32ClientInfo[62];
    VOID* PTR64 glDispatchTable[233];
    ULONGLONG glReserved1[29];
    VOID* PTR64 glReserved2;
    VOID* PTR64 glSectionInfo;
    VOID* PTR64 glSection;
    VOID* PTR64 glTable;
    VOID* PTR64 glCurrentRC;
    VOID* PTR64 glContext;
    ULONG LastStatusValue;
    UCHAR Padding2[4];
    UNICODE_STRING64 StaticUnicodeString;
    WCHAR StaticUnicodeBuffer[261];
    UCHAR Padding3[6];
    VOID* PTR64 DeallocationStack;
    VOID* PTR64 TlsSlots[64];
    LIST_ENTRY64 TlsLinks;
    VOID* PTR64 Vdm;
    VOID* PTR64 ReservedForNtRpc;
    VOID* PTR64 DbgSsReserved[2];
    ULONG HardErrorMode;
    UCHAR Padding4[4];
    VOID* PTR64 Instrumentation[11];
    GUID ActivityId;
    VOID* PTR64 SubProcessTag;
    VOID* PTR64 PerflibData;
    VOID* PTR64 EtwTraceData;
    VOID* PTR64 WinSockData;
    ULONG GdiBatchCount;
    union {
        PROCESSOR_NUMBER CurrentIdealProcessor;
        union {
            DWORD IdealProcessorValue;
            struct {
                UCHAR ReservedPad0;
                UCHAR ReservedPad1;
                UCHAR ReservedPad2;
                UCHAR IdealProcessor;
            };
        };
    };
    ULONG GuaranteedStackBytes;
    UCHAR Padding5[4];
    VOID* PTR64 ReservedForPerf;
    VOID* PTR64 ReservedForOle;
    ULONG WaitingOnLoaderLock;
    UCHAR Padding6[4];
    VOID* PTR64 SavedPriorityState;
    ULONGLONG ReservedForCodeCoverage;
    VOID* PTR64 ThreadPoolData;
    VOID* PTR64 TlsExpansionSlots;
    struct CHPEV2_CPUAREA_INFO* PTR64 ChpeV2CpuAreaInfo;
    VOID* PTR64 Unused;
    ULONG MuiGeneration;
    ULONG IsImpersonating;
    VOID* PTR64 NlsCache;
    VOID* PTR64 pShimData;
    ULONG HeapData;
    UCHAR Padding7[4];
    VOID* PTR64 CurrentTransactionHandle;
    TEB_ACTIVE_FRAME64* PTR64 ActiveFrame;
    VOID* PTR64 FlsData;
    VOID* PTR64 PreferredLanguages;
    VOID* PTR64 UserPrefLanguages;
    VOID* PTR64 MergedPrefLanguages;
    ULONG MuiImpersonation;
    union {
        USHORT CrossTebFlags;
        struct {
            USHORT SpareCrossTebBits : 16;
        };
    };
    union {
        USHORT SameTebFlags;
        struct {
            USHORT SafeThunkCall : 1;
            USHORT InDebugPrint : 1;
            USHORT HasFiberData : 1;
            USHORT SkipThreadAttach : 1;
            USHORT WerInShipAssertCode : 1;
            USHORT RanProcessInit : 1;
            USHORT ClonedThread : 1;
            USHORT SuppressDebugMsg : 1;
            USHORT DisableUserStackWalk : 1;
            USHORT RtlExceptionAttached : 1;
            USHORT InitialThread : 1;
            USHORT SessionAware : 1;
            USHORT LoadOwner : 1;
            USHORT LoaderWorker : 1;
            USHORT SkipLoaderInit : 1;
            USHORT SkipFileAPIBrokering : 1;
        };
    };
    VOID* PTR64 TxnScopeEnterCallback;
    VOID* PTR64 TxnScopeExitCallback;
    VOID* PTR64 TxnScopeContext;
    ULONG LockCount;
    LONG WowTebOffset;
    VOID* PTR64 ResourceRetValue;
    VOID* PTR64 ReservedForWdf;
    ULONGLONG ReservedForCrt;
    GUID EffectiveContainerId;
    ULONGLONG LastSleepCounter;
    ULONG SpinCallCount;
    UCHAR Padding8[4];
    ULONGLONG ExtendedFeatureDisableMask;
} TEB64, *PTEB64;

typedef struct _TEB32 {
    NT_TIB32 NtTib;
    WCHAR* PTR32 EnvironmentPointer;
    CLIENT_ID32 ClientId;
    VOID* PTR32 ActiveRpcHandle;
    VOID* PTR32 ThreadLocalStoragePointer;
    PEB32* PTR32 ProcessEnvironmentBlock;
    ULONG LastErrorValue;
    ULONG CountOfOwnedCriticalSections;
    VOID* PTR32 CsrClientThread;
    VOID* PTR32 Win32ThreadInfo;
    ULONG User32Reserved[26];
    ULONG UserReserved[5];
    VOID* PTR32 WOW32Reserved;
    ULONG CurrentLocale;
    ULONG FpSoftwareStatusRegister;
    VOID* PTR32 ReservedForDebuggerInstrumentation[16];
    VOID* PTR32 SystemReserved1[26];
    CHAR PlaceholderCompatibilityMode;
    UCHAR PlaceholderHydrationAlwaysExplicit;
    CHAR PlaceholderReserved[10];
    ULONG ProxiedProcessId;
    ACTIVATION_CONTEXT_STACK32 _ActivationStack;
    UCHAR WorkingOnBehalfTicket[8];
    LONG ExceptionCode;
    ACTIVATION_CONTEXT_STACK32* PTR32 ActivationContextStackPointer;
    VOID* PTR32 InstrumentationCallbackSp;
    VOID* PTR32 InstrumentationCallbackPreviousPc;
    VOID* PTR32 InstrumentationCallbackPreviousSp;
    UCHAR InstrumentationCallbackDisabled;
    UCHAR SpareBytes[23];
    ULONG TxFsContext;
    GDI_TEB_BATCH32 GdiTebBatch;
    CLIENT_ID32 RealClientId;
    VOID* PTR32 GdiCachedProcessHandle;
    ULONG GdiClientPID;
    ULONG GdiClientTID;
    VOID* PTR32 GdiThreadLocalInfo;
    ULONG Win32ClientInfo[62];
    VOID* PTR32 glDispatchTable[233];
    ULONG glReserved1[29];
    VOID* PTR32 glReserved2;
    VOID* PTR32 glSectionInfo;
    VOID* PTR32 glSection;
    VOID* PTR32 glTable;
    VOID* PTR32 glCurrentRC;
    VOID* PTR32 glContext;
    ULONG LastStatusValue;
    UNICODE_STRING32 StaticUnicodeString;
    WCHAR StaticUnicodeBuffer[261];
    VOID* PTR32 DeallocationStack;
    VOID* PTR32 TlsSlots[64];
    LIST_ENTRY32 TlsLinks;
    VOID* PTR32 Vdm;
    VOID* PTR32 ReservedForNtRpc;
    VOID* PTR32 DbgSsReserved[2];
    ULONG HardErrorMode;
    VOID* PTR32 Instrumentation[9];
    GUID ActivityId;
    VOID* PTR32 SubProcessTag;
    VOID* PTR32 PerflibData;
    VOID* PTR32 EtwTraceData;
    VOID* PTR32 WinSockData;
    ULONG GdiBatchCount;
    union {
        PROCESSOR_NUMBER CurrentIdealProcessor;
        union {
            DWORD IdealProcessorValue;
            struct {
                UCHAR ReservedPad0;
                UCHAR ReservedPad1;
                UCHAR ReservedPad2;
                UCHAR IdealProcessor;
            };
        };
    };
    ULONG GuaranteedStackBytes;
    VOID* PTR32 ReservedForPerf;
    VOID* PTR32 ReservedForOle;
    ULONG WaitingOnLoaderLock;
    VOID* PTR32 SavedPriorityState;
    ULONG ReservedForCodeCoverage;
    VOID* PTR32 ThreadPoolData;
    VOID* PTR32 TlsExpansionSlots;
    ULONG MuiGeneration;
    ULONG IsImpersonating;
    VOID* PTR32 NlsCache;
    VOID* PTR32 pShimData;
    ULONG HeapData;
    VOID* PTR32 CurrentTransactionHandle;
    TEB_ACTIVE_FRAME32* PTR32 ActiveFrame;
    VOID* PTR32 FlsData;
    VOID* PTR32 PreferredLanguages;
    VOID* PTR32 UserPrefLanguages;
    VOID* PTR32 MergedPrefLanguages;
    ULONG MuiImpersonation;
    union {
        USHORT CrossTebFlags;
        struct {
            USHORT SpareCrossTebBits : 16;
        };
    };
    union {
        USHORT SameTebFlags;
        struct {
            USHORT SafeThunkCall : 1;
            USHORT InDebugPrint : 1;
            USHORT HasFiberData : 1;
            USHORT SkipThreadAttach : 1;
            USHORT WerInShipAssertCode : 1;
            USHORT RanProcessInit : 1;
            USHORT ClonedThread : 1;
            USHORT SuppressDebugMsg : 1;
            USHORT DisableUserStackWalk : 1;
            USHORT RtlExceptionAttached : 1;
            USHORT InitialThread : 1;
            USHORT SessionAware : 1;
            USHORT LoadOwner : 1;
            USHORT LoaderWorker : 1;
            USHORT SkipLoaderInit : 1;
            USHORT SkipFileAPIBrokering : 1;
        };
    };
    VOID* PTR32 TxnScopeEnterCallback;
    VOID* PTR32 TxnScopeExitCallback;
    VOID* PTR32 TxnScopeContext;
    ULONG LockCount;
    LONG WowTebOffset;
    VOID* PTR32 ResourceRetValue;
    VOID* PTR32 ReservedForWdf;
    ULONGLONG ReservedForCrt;
    GUID EffectiveContainerId;
    ULONGLONG LastSleepCounter;
    ULONG SpinCallCount;
    ULONGLONG ExtendedFeatureDisableMask;
} TEB32, *PTEB32;
