#pragma once

#include "NTAssassin.h"

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
#undef OBJECT_INFORMATION_CLASS
#undef ObjectBasicInformation
#undef ObjectTypeInformation

typedef struct _MEMORY_RANGE_ENTRY {
    PVOID VirtualAddress;
    SIZE_T NumberOfBytes;
} MEMORY_RANGE_ENTRY, * PMEMORY_RANGE_ENTRY;

typedef struct _CLIENT_ID {
    INT_PTR UniqueProcess;
    INT_PTR UniqueThread;
} CLIENT_ID, * PCLIENT_ID;

typedef struct _RTL_DRIVE_LETTER_CURDIR {
    USHORT Flags;
    USHORT Length;
    UINT TimeStamp;
    STRING DosPath;
} RTL_DRIVE_LETTER_CURDIR, * PRTL_DRIVE_LETTER_CURDIR;

typedef struct _CURDIR {
    UNICODE_STRING DosPath;
    HANDLE Handle;
} CURDIR, * PCURDIR;

typedef struct _RTL_USER_PROCESS_PARAMETERS {
    DWORD MaximumLength;
    DWORD Length;
    DWORD Flags;
    DWORD DebugFlags;
    HANDLE ConsoleHandle;
    DWORD ConsoleFlags;
    HANDLE StandardInput;
    HANDLE StandardOutput;
    HANDLE StandardError;
    CURDIR CurrentDirectory;
    UNICODE_STRING DllPath;
    UNICODE_STRING ImagePathName;
    UNICODE_STRING CommandLine;
    LPWSTR Environment;
    UINT StartingX;
    UINT StartingY;
    UINT CountX;
    UINT CountY;
    UINT CountCharsX;
    UINT CountCharsY;
    DWORD FillAttribute;
    DWORD WindowFlags;
    DWORD ShowWindowFlags;
    UNICODE_STRING WindowTitle;
    UNICODE_STRING DesktopInfo;
    UNICODE_STRING ShellInfo;
    UNICODE_STRING RuntimeData;
    RTL_DRIVE_LETTER_CURDIR CurrentDirectores[32];
    INT_PTR EnvironmentSize;
    INT_PTR EnvironmentVersion;
    PVOID PackageDependencyData;
    UINT ProcessGroupId;
    DWORD LoaderThreads;
    UNICODE_STRING RedirectionDllName;
    UNICODE_STRING HeapPartitionName;
    PINT_PTR DefaultThreadpoolCpuSetMasks;
    UINT DefaultThreadpoolCpuSetMaskCount;
} RTL_USER_PROCESS_PARAMETERS, * PRTL_USER_PROCESS_PARAMETERS;

typedef struct _LEAP_SECOND_DATA {
    UCHAR Enabled;
    UCHAR Padding[3];
    DWORD Count;
    LARGE_INTEGER Data[1];
} LEAP_SECOND_DATA, * PLEAP_SECOND_DATA;

typedef struct _LDR_SERVICE_TAG_RECORD LDR_SERVICE_TAG_RECORD, * PLDR_SERVICE_TAG_RECORD;

struct _LDR_SERVICE_TAG_RECORD {
    PLDR_SERVICE_TAG_RECORD Next;
    UINT ServiceTag;
};

typedef enum _LDR_DDAG_STATE {
    LdrModulesMerged = -5,
    LdrModulesInitError = -4,
    LdrModulesSnapError = -3,
    LdrModulesUnloaded = -2,
    LdrModulesUnloading = -1,
    LdrModulesPlaceHolder = 0,
    LdrModulesMapping = 1,
    LdrModulesMapped = 2,
    LdrModulesWaitingForDependencies = 3,
    LdrModulesSnapping = 4,
    LdrModulesSnapped = 5,
    LdrModulesCondensed = 6,
    LdrModulesReadyToInit = 7,
    LdrModulesInitializing = 8,
    LdrModulesReadyToRun = 9,
} LDR_DDAG_STATE, * PLDR_DDAG_STATE;

typedef struct _LDRP_CSLIST {
    SINGLE_LIST_ENTRY Tail;
} LDRP_CSLIST, * PLDRP_CSLIST;

typedef struct _LDR_DDAG_NODE {
    LIST_ENTRY Modules;
    PLDR_SERVICE_TAG_RECORD ServiceTagList;
    UINT LoadCount;
    UINT LoadWhileUnloadingCount;
    PVOID LowestLink;
    LDRP_CSLIST Dependencies;
    LDRP_CSLIST IncomingDependencies;
    LDR_DDAG_STATE State;
    SINGLE_LIST_ENTRY CondenseLink;
    UINT PreorderNumber;
} LDR_DDAG_NODE, * PLDR_DDAG_NODE;

typedef struct _RTL_BALANCED_NODE RTL_BALANCED_NODE, * PRTL_BALANCED_NODE;

struct _RTL_BALANCED_NODE {
    union {
        PRTL_BALANCED_NODE Children[2];
        struct {
            PRTL_BALANCED_NODE Left;
            PRTL_BALANCED_NODE Right;
        };
    };
    union {
        DWORD ParentValue;
        DWORD Red : 1;
        DWORD Balance : 2;
    };
};

typedef enum LDR_DLL_LOAD_REASON {
    LoadReasonStaticDependency = 0,
    LoadReasonStaticForwarderDependency = 1,
    LoadReasonDynamicForwarderDependency = 2,
    LoadReasonDelayloadDependency = 3,
    LoadReasonDynamicLoad = 4,
    LoadReasonAsImageLoad = 5,
    LoadReasonAsDataLoad = 6,
    LoadReasonEnclavePrimary = 7,
    LoadReasonEnclaveDependency = 8,
    LoadReasonUnknown = -1
} LDR_DLL_LOAD_REASON;

typedef struct _LDR_DATA_TABLE_ENTRY {
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
    HMODULE DllBase;
    PVOID EntryPoint;
    UINT SizeOfImage;
    UNICODE_STRING FullDllName;
    UNICODE_STRING BaseDllName;
    union {
        DWORD Flags;
        struct {
            DWORD PackagedBinary : 1;
            DWORD MarkedForRemoval : 1;
            DWORD ImageDll : 1;
            DWORD LoadNotificationsSent : 1;
            DWORD TelemetryEntryProcessed : 1;
            DWORD ProcessStaticImport : 1;
            DWORD InLegacyLists : 1;
            DWORD InIndexes : 1;
            DWORD ShimDll : 1;
            DWORD InExceptionTable : 1;
            DWORD ReservedFlags1 : 2;
            DWORD LoadInProgress : 1;
            DWORD LoadConfigProcessed : 1;
            DWORD EntryProcessed : 1;
            DWORD ProtectDelayLoad : 1;
            DWORD ReservedFlags3 : 2;
            DWORD DontCallForThreads : 1;
            DWORD ProcessAttachCalled : 1;
            DWORD ProcessAttachFailed : 1;
            DWORD CorDeferredValidate : 1;
            DWORD CorImage : 1;
            DWORD DontRelocate : 1;
            DWORD CorILOnly : 1;
            DWORD ChpeImage : 1;
            DWORD ReservedFlags5 : 2;
            DWORD Redirected : 1;
            DWORD ReservedFlags6 : 2;
            DWORD CompatDatabaseProcessed : 1;
        };
        USHORT ObsoleteLoadCount;
        USHORT TlsIndex;
        LIST_ENTRY HashLinks;
        DWORD TimeDateStamp;
        struct ACTIVATION_CONTEXT* EntryPointActivationContext;
        PVOID Lock;
        PLDR_DDAG_NODE DdagNode;
        LIST_ENTRY NodeModuleLink;
        struct LDRP_LOAD_CONTEXT* LoadContext;
        HMODULE ParentDllBase;
        PVOID SwitchBackContext;
        RTL_BALANCED_NODE BaseAddressIndexNode;
        RTL_BALANCED_NODE MappingInfoIndexNode;
        UINT_PTR OriginalBase;
        LARGE_INTEGER LoadTime;
        UINT BaseNameHashValue;
        LDR_DLL_LOAD_REASON LoadReason;
        DWORD ImplicitPathOptions;
        UINT ReferenceCount;
        DWORD DependentLoadFlags;
        UCHAR SigningLevel;
    };
} LDR_DATA_TABLE_ENTRY, * PLDR_DATA_TABLE_ENTRY;

typedef struct _PEB_LDR_DATA {
    UINT Length;
    BOOL Initialized;
    PVOID SsHandle;
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
    PVOID EntryInProgress;
    PVOID ShutdownInProgress;
    PVOID ShutdownThreadId;
} PEB_LDR_DATA, * PPEB_LDR_DATA;

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
    HINSTANCE ImageBaseAddress;
    PPEB_LDR_DATA Ldr;
    PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
    PVOID SubSystemData;
    HANDLE ProcessHeap;
    PRTL_CRITICAL_SECTION FastPebLock;
    PSLIST_HEADER AtlThunkSListPtr;
    PVOID IFEOKey;
    union {
        DWORD CrossProcessFlags;
        struct {
            DWORD ProcessInJob : 1;
            DWORD ProcessInitializing : 1;
            DWORD ProcessUsingVEH : 1;
            DWORD ProcessUsingVCH : 1;
            DWORD ProcessUsingFTH : 1;
            DWORD ProcessPreviouslyThrottled : 1;
            DWORD ProcessCurrentlyThrottled : 1;
            DWORD ProcessImagesHotPatched : 1;
            DWORD ReservedBits0 : 24;
        };
    };
#if _WIN64
    UCHAR Padding1[4];
#endif
    union {
        PVOID KernelCallbackTable;
        PVOID UserSharedInfoPtr;
    };
    DWORD SystemReserved;
    DWORD AtlThunkSListPtr32;
    PVOID ApiSetMap;
    DWORD TlsExpansionCounter;
#if _WIN64
    UCHAR Padding2[4];
#endif
    PVOID TlsBitmap;
    DWORD TlsBitmapBits[2];
    PVOID ReadOnlySharedMemoryBase;
    PVOID SharedData;
    PVOID ReadOnlyStaticServerData;
    PVOID AnsiCodePageData;
    PVOID OemCodePageData;
    PVOID UnicodeCaseTableData;
    DWORD NumberOfProcessors;
    DWORD NtGlobalFlag;
    LARGE_INTEGER CriticalSectionTimeout;
    INT_PTR HeapSegmentReserve;
    INT_PTR HeapSegmentCommit;
    INT_PTR HeapDeCommitTotalFreeThreshold;
    INT_PTR HeapDeCommitFreeBlockThreshold;
    DWORD NumberOfHeaps;
    DWORD MaximumNumberOfHeaps;
    PVOID ProcessHeaps;
    PVOID GdiSharedHandleTable;
    PVOID ProcessStarterHelper;
    DWORD GdiDCAttributeList;
#if _WIN64
    UCHAR Padding3[4];
#endif
    PRTL_CRITICAL_SECTION LoaderLock;
    DWORD OSMajorVersion;
    DWORD OSMinorVersion;
    USHORT OSBuildNumber;
    USHORT OSCSDVersion;
    DWORD OSPlatformId;
    DWORD ImageSubsystem;
    DWORD ImageSubsystemMajorVersion;
    DWORD ImageSubsystemMinorVersion;
#if _WIN64
    UCHAR Padding4[4];
#endif
    UINT ActiveProcessAffinityMask;
    DWORD GdiHandleBuffer[60];
    PVOID PostProcessInitRoutine;
    PVOID TlsExpansionBitmap;
    DWORD TlsExpansionBitmapBits[32];
    DWORD SessionId;
#ifdef _WIN64
    UCHAR Padding5[4];
#endif
    ULARGE_INTEGER AppCompatFlags;
    ULARGE_INTEGER AppCompatFlagsUser;
    PVOID pShimData;
    PVOID AppCompatInfo;
    UNICODE_STRING CSDVersion;
    struct ACTIVATION_CONTEXT_DATA* ActivationContextData;
    struct ASSEMBLY_STORAGE_MAP* ProcessAssemblyStorageMap;
    struct ACTIVATION_CONTEXT_DATA* SystemDefaultActivationContextData;
    struct ASSEMBLY_STORAGE_MAP* SystemAssemblyStorageMap;
    INT_PTR MinimumStackCommit;
    PVOID SparePointers[4];
    DWORD SpareUlongs[5];
    PVOID WerRegistrationData;
    PVOID WerShipAssertPtr;
    PVOID pUnused;
    PVOID pImageHeaderHash;
    union {
        DWORD TracingFlags;
        struct {
            DWORD HeapTracingEnabled : 1;
            DWORD CritSecTracingEnabled : 1;
            DWORD LibLoaderTracingEnabled : 1;
            DWORD SpareTracingBits : 29;
        };
    };
#ifdef _WIN64
    UCHAR Padding6[4];
#endif
    INT_PTR CsrServerReadOnlySharedMemoryBase;
    INT_PTR TppWorkerpListLock;
    LIST_ENTRY TppWorkerpList;
    PVOID WaitOnAddressHashTable[128];
    PVOID TelemetryCoverageHeader;
    DWORD CloudFileFlags;
    DWORD CloudFileDiagFlags;
    UCHAR PlaceholderCompatibilityMode;
    UCHAR PlaceholderCompatibilityModeReserved[7];
    PLEAP_SECOND_DATA LeapSecondData;
    union {
        DWORD LeapSecondFlags;
        struct {
            DWORD SixtySecondEnabled : 1;
            DWORD Reserved : 31;
        };
    };
    DWORD NtGlobalFlag2;
} PEB, * PPEB;

typedef struct _GDI_TEB_BATCH {
    struct {
        UINT Offset : 31;
        BOOL HasRenderingCommand : 1;
    };
    UINT HDC;
    DWORD Buffer[310];
} GDI_TEB_BATCH, * PGDI_TEB_BATCH;

typedef struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME RTL_ACTIVATION_CONTEXT_STACK_FRAME, * PRTL_ACTIVATION_CONTEXT_STACK_FRAME;

struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME {
    struct RTL_ACTIVATION_CONTEXT_STACK_FRAME* Previous;
    struct ACTIVATION_CONTEXT* ActivationContext;
    DWORD Flags;
};

typedef struct _ACTIVATION_CONTEXT_STACK {
    PRTL_ACTIVATION_CONTEXT_STACK_FRAME ActiveFrame;
    LIST_ENTRY FrameListCache;
    DWORD Flags;
    DWORD NextCookieSequenceNumber;
    DWORD StackId;
} ACTIVATION_CONTEXT_STACK, * PACTIVATION_CONTEXT_STACK;

typedef struct _TEB_ACTIVE_FRAME_CONTEXT {
    DWORD Flags;
    UCHAR Padding[4];
    PCHAR FrameName;
} TEB_ACTIVE_FRAME_CONTEXT, * PTEB_ACTIVE_FRAME_CONTEXT;

typedef struct _TEB_ACTIVE_FRAME TEB_ACTIVE_FRAME, * PTEB_ACTIVE_FRAME;

struct _TEB_ACTIVE_FRAME {
    DWORD Flags;
    UCHAR Padding[4];
    struct TEB_ACTIVE_FRAME* Previous;
    PTEB_ACTIVE_FRAME_CONTEXT Context;
};

typedef struct _TEB {
    NT_TIB NtTib;
    LPWSTR EnvironmentPointer;
    CLIENT_ID ClientId;
    PVOID ActiveRpcHandle;
    PVOID ThreadLocalStoragePointer;
    PPEB ProcessEnvironmentBlock;
    DWORD LastErrorValue;
    DWORD CountOfOwnedCriticalSections;
    PVOID CsrClientThread;
    PVOID Win32ThreadInfo;
    DWORD User32Reserved[26];
    DWORD UserReserved[5];
    PVOID WOW32Reserved;
    LCID  CurrentLocale;
    DWORD FpSoftwareStatusRegister;
    PVOID ReservedForDebuggerInstrumentation[16];
    PVOID SystemReserved1[30];
    UCHAR PlaceholderCompatibilityMode;
    UCHAR PlaceholderHydrationAlwaysExplicit;
    UCHAR PlaceholderReserved[10];
    DWORD ProxiedProcessId;
    ACTIVATION_CONTEXT_STACK ActivationStack;
    UCHAR WorkingOnBehalfTicket[8];
    DWORD ExceptionCode;
#ifdef _WIN64
    UCHAR Padding0[4];
#endif
    PACTIVATION_CONTEXT_STACK ActivationContextStackPointer;
    PVOID InstrumentationCallbackSp;
    PVOID InstrumentationCallbackPreviousPc;
    PVOID InstrumentationCallbackPreviousSp;
#ifdef _WIN64
    DWORD TxFsContext;
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
    DWORD GdiClientPID;
    DWORD GdiClientTID;
    PVOID GdiThreadLocalInfo;
    INT_PTR Win32ClientInfo[62];
    PVOID glDispatchTable[233];
    INT_PTR glReserved1[29];
    PVOID glReserved2;
    PVOID glSectionInfo;
    PVOID glSection;
    PVOID glTable;
    PVOID glCurrentRC;
    PVOID glContext;
    DWORD LastStatusValue;
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
    DWORD HardErrorMode;
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
    DWORD GdiBatchCount;
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
    DWORD GuaranteedStackBytes;
#ifdef _WIN64
    UCHAR Padding5[4];
#endif
    PVOID ReservedForPerf;
    PVOID ReservedForOle;
    DWORD WaitingOnLoaderLock;
#ifdef _WIN64
    UCHAR Padding6[4];
#endif
    PVOID SavedPriorityState;
    INT_PTR ReservedForCodeCoverage;
    PVOID ThreadPoolData;
    PVOID TlsExpansionSlots;
#ifdef _WIN64
    PVOID DeallocationBStore;
    PVOID BStoreLimit;
#endif
    DWORD MuiGeneration;
    DWORD IsImpersonating;
    PVOID NlsCache;
    PVOID pShimData;
    DWORD HeapData;
#ifdef _WIN64
    UCHAR Padding7[4];
#endif
    PVOID CurrentTransactionHandle;
    PTEB_ACTIVE_FRAME ActiveFrame;
    PVOID FlsData;
    PVOID PreferredLanguages;
    PVOID UserPrefLanguages;
    PVOID MergedPrefLanguages;
    DWORD MuiImpersonation;
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
            USHORT SpareSameTebBits : 1;
        };
    };
    PVOID TxnScopeEnterCallback;
    PVOID TxnScopeExitCallback;
    PVOID TxnScopeContext;
    DWORD LockCount;
    DWORD WowTebOffset;
    PVOID ResourceRetValue;
    PVOID ReservedForWdf;
    ULONGLONG ReservedForCrt;
    GUID EffectiveContainerId;
} TEB, * PTEB;

typedef struct _KSYSTEM_TIME {
    ULONG LowPart;
    LONG High1Time;
    LONG High2Time;
} KSYSTEM_TIME, * PKSYSTEM_TIME;

typedef enum _NT_PRODUCT_TYPE {
    NtProductWinNt = 1,
    NtProductLanManNt,
    NtProductServer
} NT_PRODUCT_TYPE, * PNT_PRODUCT_TYPE;

typedef enum _ALTERNATIVE_ARCHITECTURE_TYPE {
    StandardDesign,                 // None == 0 == standard design
    NEC98x86,                       // NEC PC98xx series on X86
    EndAlternatives                 // past end of known alternatives
} ALTERNATIVE_ARCHITECTURE_TYPE, * PALTERNATIVE_ARCHITECTURE_TYPE;

typedef struct _KUSER_SHARED_DATA {
    ULONG                         TickCountLowDeprecated;
    ULONG                         TickCountMultiplier;
    KSYSTEM_TIME                  InterruptTime;
    KSYSTEM_TIME                  SystemTime;
    KSYSTEM_TIME                  TimeZoneBias;
    USHORT                        ImageNumberLow;
    USHORT                        ImageNumberHigh;
    WCHAR                         NtSystemRoot[260];
    ULONG                         MaxStackTraceDepth;
    ULONG                         CryptoExponent;
    ULONG                         TimeZoneId;
    ULONG                         LargePageMinimum;
    ULONG                         AitSamplingValue;
    ULONG                         AppCompatFlag;
    ULONGLONG                     RNGSeedVersion;
    ULONG                         GlobalValidationRunlevel;
    LONG                          TimeZoneBiasStamp;
    ULONG                         NtBuildNumber;
    NT_PRODUCT_TYPE               NtProductType;
    BOOLEAN                       ProductTypeIsValid;
    BOOLEAN                       Reserved0[1];
    USHORT                        NativeProcessorArchitecture;
    ULONG                         NtMajorVersion;
    ULONG                         NtMinorVersion;
    BOOLEAN                       ProcessorFeatures[PROCESSOR_FEATURE_MAX];
    ULONG                         Reserved1;
    ULONG                         Reserved3;
    ULONG                         TimeSlip;
    ALTERNATIVE_ARCHITECTURE_TYPE AlternativeArchitecture;
    ULONG                         BootId;
    LARGE_INTEGER                 SystemExpirationDate;
    ULONG                         SuiteMask;
    BOOLEAN                       KdDebuggerEnabled;
    union {
        UCHAR MitigationPolicies;
        struct {
            UCHAR NXSupportPolicy : 2;
            UCHAR SEHValidationPolicy : 2;
            UCHAR CurDirDevicesSkippedForDlls : 2;
            UCHAR Reserved : 2;
        };
    };
    USHORT                        CyclesPerYield;
    ULONG                         ActiveConsoleId;
    ULONG                         DismountCount;
    ULONG                         ComPlusPackage;
    ULONG                         LastSystemRITEventTickCount;
    ULONG                         NumberOfPhysicalPages;
    BOOLEAN                       SafeBootMode;
    UCHAR                         VirtualizationFlags;
    UCHAR                         Reserved12[2];
    union {
        ULONG SharedDataFlags;
        struct {
            ULONG DbgErrorPortPresent : 1;
            ULONG DbgElevationEnabled : 1;
            ULONG DbgVirtEnabled : 1;
            ULONG DbgInstallerDetectEnabled : 1;
            ULONG DbgLkgEnabled : 1;
            ULONG DbgDynProcessorEnabled : 1;
            ULONG DbgConsoleBrokerEnabled : 1;
            ULONG DbgSecureBootEnabled : 1;
            ULONG DbgMultiSessionSku : 1;
            ULONG DbgMultiUsersInSessionSku : 1;
            ULONG DbgStateSeparationEnabled : 1;
            ULONG SpareBits : 21;
        };
    };
    ULONG                         DataFlagsPad[1];
    ULONGLONG                     TestRetInstruction;
    LONGLONG                      QpcFrequency;
    ULONG                         SystemCall;
    ULONG                         SystemCallPad0;
    ULONGLONG                     SystemCallPad[2];
    union {
        KSYSTEM_TIME TickCount;
        ULONG64      TickCountQuad;
        struct {
            ULONG ReservedTickCountOverlay[3];
            ULONG TickCountPad[1];
        };
    };
    ULONG                         Cookie;
    ULONG                         CookiePad[1];
    LONGLONG                      ConsoleSessionForegroundProcessId;
    ULONGLONG                     TimeUpdateLock;
    ULONGLONG                     BaselineSystemTimeQpc;
    ULONGLONG                     BaselineInterruptTimeQpc;
    ULONGLONG                     QpcSystemTimeIncrement;
    ULONGLONG                     QpcInterruptTimeIncrement;
    UCHAR                         QpcSystemTimeIncrementShift;
    UCHAR                         QpcInterruptTimeIncrementShift;
    USHORT                        UnparkedProcessorCount;
    ULONG                         EnclaveFeatureMask[4];
    ULONG                         TelemetryCoverageRound;
    USHORT                        UserModeGlobalLogger[16];
    ULONG                         ImageFileExecutionOptions;
    ULONG                         LangGenerationCount;
    ULONGLONG                     Reserved4;
    ULONGLONG                     InterruptTimeBias;
    ULONGLONG                     QpcBias;
    ULONG                         ActiveProcessorCount;
    UCHAR                         ActiveGroupCount;
    UCHAR                         Reserved9;
    union {
        USHORT QpcData;
        struct {
            UCHAR QpcBypassEnabled;
            UCHAR QpcShift;
        };
    };
    LARGE_INTEGER                 TimeZoneBiasEffectiveStart;
    LARGE_INTEGER                 TimeZoneBiasEffectiveEnd;
    XSTATE_CONFIGURATION          XState;
} KUSER_SHARED_DATA, * PKUSER_SHARED_DATA;

typedef struct _RTLP_CURDIR_REF {
    LONG RefCount;
    HANDLE Handle;
} RTLP_CURDIR_REF, * PRTLP_CURDIR_REF;

typedef struct {
    UNICODE_STRING RelativeName;
    HANDLE ContainingDirectory;
    PRTLP_CURDIR_REF CurDirRef;
} RTL_RELATIVE_NAME_U, * PRTL_RELATIVE_NAME_U;

typedef NTSTATUS
(NTAPI* PRTL_HEAP_COMMIT_ROUTINE)(
    IN PVOID Base,
    IN OUT PVOID* CommitAddress,
    IN OUT PSIZE_T CommitSize
    );

typedef struct _RTL_HEAP_PARAMETERS {
    ULONG Length;
    SIZE_T SegmentReserve;
    SIZE_T SegmentCommit;
    SIZE_T DeCommitFreeBlockThreshold;
    SIZE_T DeCommitTotalFreeThreshold;
    SIZE_T MaximumAllocationSize;
    SIZE_T VirtualMemoryThreshold;
    SIZE_T InitialCommit;
    SIZE_T InitialReserve;
    PRTL_HEAP_COMMIT_ROUTINE CommitRoutine;
    SIZE_T Reserved[2];
} RTL_HEAP_PARAMETERS, * PRTL_HEAP_PARAMETERS;

typedef struct _FILE_BASIC_INFORMATION {
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    ULONG         FileAttributes;
} FILE_BASIC_INFORMATION, * PFILE_BASIC_INFORMATION;

typedef struct _FILE_NETWORK_OPEN_INFORMATION {
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER AllocationSize;
    LARGE_INTEGER EndOfFile;
    ULONG         FileAttributes;
} FILE_NETWORK_OPEN_INFORMATION, * PFILE_NETWORK_OPEN_INFORMATION;

typedef struct _FILE_DISPOSITION_INFORMATION {
    BOOLEAN DeleteFile;
} FILE_DISPOSITION_INFORMATION, * PFILE_DISPOSITION_INFORMATION;

typedef struct _FILE_DISPOSITION_INFORMATION_EX {
    ULONG Flags;
} FILE_DISPOSITION_INFORMATION_EX, * PFILE_DISPOSITION_INFORMATION_EX;

typedef enum _SECTION_INHERIT {
    ViewShare = 1,
    ViewUnmap = 2
} SECTION_INHERIT;

typedef enum _FILE_INFORMATION_CLASS {
    FileDirectoryInformation,
    FileFullDirectoryInformation,
    FileBothDirectoryInformation,
    FileBasicInformation,
    FileStandardInformation,
    FileInternalInformation,
    FileEaInformation,
    FileAccessInformation,
    FileNameInformation,
    FileRenameInformation,
    FileLinkInformation,
    FileNamesInformation,
    FileDispositionInformation,
    FilePositionInformation,
    FileFullEaInformation,
    FileModeInformation,
    FileAlignmentInformation,
    FileAllInformation,
    FileAllocationInformation,
    FileEndOfFileInformation,
    FileAlternateNameInformation,
    FileStreamInformation,
    FilePipeInformation,
    FilePipeLocalInformation,
    FilePipeRemoteInformation,
    FileMailslotQueryInformation,
    FileMailslotSetInformation,
    FileCompressionInformation,
    FileObjectIdInformation,
    FileCompletionInformation,
    FileMoveClusterInformation,
    FileQuotaInformation,
    FileReparsePointInformation,
    FileNetworkOpenInformation,
    FileAttributeTagInformation,
    FileTrackingInformation,
    FileIdBothDirectoryInformation,
    FileIdFullDirectoryInformation,
    FileValidDataLengthInformation,
    FileShortNameInformation,
    FileIoCompletionNotificationInformation,
    FileIoStatusBlockRangeInformation,
    FileIoPriorityHintInformation,
    FileSfioReserveInformation,
    FileSfioVolumeInformation,
    FileHardLinkInformation,
    FileProcessIdsUsingFileInformation,
    FileNormalizedNameInformation,
    FileNetworkPhysicalNameInformation,
    FileIdGlobalTxDirectoryInformation,
    FileIsRemoteDeviceInformation,
    FileUnusedInformation,
    FileNumaNodeInformation,
    FileStandardLinkInformation,
    FileRemoteProtocolInformation,
    FileRenameInformationBypassAccessCheck,
    FileLinkInformationBypassAccessCheck,
    FileVolumeNameInformation,
    FileIdInformation,
    FileIdExtdDirectoryInformation,
    FileReplaceCompletionInformation,
    FileHardLinkFullIdInformation,
    FileIdExtdBothDirectoryInformation,
    FileDispositionInformationEx,
    FileRenameInformationEx,
    FileRenameInformationExBypassAccessCheck,
    FileDesiredStorageClassInformation,
    FileStatInformation,
    FileMemoryPartitionInformation,
    FileStatLxInformation,
    FileCaseSensitiveInformation,
    FileLinkInformationEx,
    FileLinkInformationExBypassAccessCheck,
    FileStorageReserveIdInformation,
    FileCaseSensitiveInformationForceAccessCheck,
    FileMaximumInformation
} FILE_INFORMATION_CLASS, * PFILE_INFORMATION_CLASS;

typedef struct _FILE_END_OF_FILE_INFORMATION {
    LARGE_INTEGER EndOfFile;
} FILE_END_OF_FILE_INFORMATION, * PFILE_END_OF_FILE_INFORMATION;

typedef enum _PROCESSINFOCLASS {
    ProcessBasicInformation,
    ProcessQuotaLimits,
    ProcessIoCounters,
    ProcessVmCounters,
    ProcessTimes,
    ProcessBasePriority,
    ProcessRaisePriority,
    ProcessDebugPort,
    ProcessExceptionPort,
    ProcessAccessToken,
    ProcessLdtInformation,
    ProcessLdtSize,
    ProcessDefaultHardErrorMode,
    ProcessIoPortHandlers,
    ProcessPooledUsageAndLimits,
    ProcessWorkingSetWatch,
    ProcessUserModeIOPL,
    ProcessEnableAlignmentFaultFixup,
    ProcessPriorityClass,
    ProcessWx86Information,
    ProcessHandleCount,
    ProcessAffinityMask,
    ProcessPriorityBoost,
    ProcessDeviceMap,
    ProcessSessionInformation,
    ProcessForegroundInformation,
    ProcessWow64Information,
    ProcessImageFileName,
    ProcessLUIDDeviceMapsEnabled,
    ProcessBreakOnTermination,
    ProcessDebugObjectHandle,
    ProcessDebugFlags,
    ProcessHandleTracing,
    ProcessIoPriority,
    ProcessExecuteFlags,
    ProcessResourceManagement,
    ProcessCookie,
    ProcessImageInformation,
    ProcessCycleTime,
    ProcessPagePriority,
    ProcessInstrumentationCallback,
    ProcessThreadStackAllocation,
    ProcessWorkingSetWatchEx,
    ProcessImageFileNameWin32,
    ProcessImageFileMapping,
    ProcessAffinityUpdateMode,
    ProcessMemoryAllocationMode,
    ProcessGroupInformation,
    ProcessTokenVirtualizationEnabled,
    ProcessConsoleHostProcess,
    ProcessWindowInformation,
    ProcessHandleInformation,
    ProcessMitigationPolicy,
    ProcessDynamicFunctionTableInformation,
    ProcessHandleCheckingMode,
    ProcessKeepAliveCount,
    ProcessRevokeFileHandles,
    ProcessWorkingSetControl,
    ProcessHandleTable,
    ProcessCheckStackExtentsMode,
    ProcessCommandLineInformation,
    ProcessProtectionInformation,
    ProcessMemoryExhaustion,
    ProcessFaultInformation,
    ProcessTelemetryIdInformation,
    ProcessCommitReleaseInformation,
    ProcessDefaultCpuSetsInformation,
    ProcessAllowedCpuSetsInformation,
    ProcessReserved1Information,
    ProcessReserved2Information,
    ProcessSubsystemProcess,
    ProcessJobMemoryInformation,
    MaxProcessInfoClass
} PROCESSINFOCLASS, * PPROCESSINFOCLASS;

typedef enum _THREADINFOCLASS {
    ThreadBasicInformation,
    ThreadTimes,
    ThreadPriority,
    ThreadBasePriority,
    ThreadAffinityMask,
    ThreadImpersonationToken,
    ThreadDescriptorTableEntry,
    ThreadEnableAlignmentFaultFixup,
    ThreadEventPair_Reusable,
    ThreadQuerySetWin32StartAddress,
    ThreadZeroTlsCell,
    ThreadPerformanceCount,
    ThreadAmILastThread,
    ThreadIdealProcessor,
    ThreadPriorityBoost,
    ThreadSetTlsArrayAddress,
    ThreadIsIoPending,
    ThreadHideFromDebugger,
    ThreadBreakOnTermination,
    ThreadSwitchLegacyState,
    ThreadIsTerminated,
    ThreadLastSystemCall,
    ThreadIoPriority,
    ThreadCycleTime,
    ThreadPagePriority,
    ThreadActualBasePriority,
    ThreadTebInformation,
    ThreadCSwitchMon,
    ThreadCSwitchPmu,
    ThreadWow64Context,
    ThreadGroupInformation,
    ThreadUmsInformation,
    ThreadCounterProfiling,
    ThreadIdealProcessorEx,
    MaxThreadInfoClass
} THREADINFOCLASS, * PTHREADINFOCLASS;

typedef struct _THREAD_BASIC_INFORMATION {
    NTSTATUS ExitStatus;
    PVOID TebBaseAddress;
    CLIENT_ID ClientId;
    KAFFINITY AffinityMask;
    KPRIORITY Priority;
    KPRIORITY BasePriority;
} THREAD_BASIC_INFORMATION, * PTHREAD_BASIC_INFORMATION;

typedef USHORT RTL_ATOM, * PRTL_ATOM;

typedef enum _ATOM_INFORMATION_CLASS {
    AtomBasicInformation,
    AtomTableInformation,
} ATOM_INFORMATION_CLASS, * PATOM_INFORMATION_CLASS;

typedef struct _ATOM_BASIC_INFORMATION {
    USHORT UsageCount;
    USHORT Flags;
    USHORT NameLength;
    WCHAR Name[1];
} ATOM_BASIC_INFORMATION, * PATOM_BASIC_INFORMATION;

typedef enum _SYSTEM_INFORMATION_CLASS {
    SystemBasicInformation = 0,
    SystemProcessorInformation = 1,
    SystemPerformanceInformation = 2,
    SystemTimeOfDayInformation = 3,
    SystemPathInformation = 4,
    SystemProcessInformation = 5,
    SystemCallCountInformation = 6,
    SystemDeviceInformation = 7,
    SystemProcessorPerformanceInformation = 8,
    SystemFlagsInformation = 9,
    SystemCallTimeInformation = 10,
    SystemModuleInformation = 11,
    SystemLocksInformation = 12,
    SystemStackTraceInformation = 13,
    SystemPagedPoolInformation = 14,
    SystemNonPagedPoolInformation = 15,
    SystemHandleInformation = 16,
    SystemObjectInformation = 17,
    SystemPageFileInformation = 18,
    SystemVdmInstemulInformation = 19,
    SystemVdmBopInformation = 20,
    SystemFileCacheInformation = 21,
    SystemPoolTagInformation = 22,
    SystemInterruptInformation = 23,
    SystemDpcBehaviorInformation = 24,
    SystemFullMemoryInformation = 25,
    SystemLoadGdiDriverInformation = 26,
    SystemUnloadGdiDriverInformation = 27,
    SystemTimeAdjustmentInformation = 28,
    SystemSummaryMemoryInformation = 29,
    SystemMirrorMemoryInformation = 30,
    SystemPerformanceTraceInformation = 31,
    SystemObsolete0 = 32,
    SystemExceptionInformation = 33,
    SystemCrashDumpStateInformation = 34,
    SystemKernelDebuggerInformation = 35,
    SystemContextSwitchInformation = 36,
    SystemRegistryQuotaInformation = 37,
    SystemExtendServiceTableInformation = 38,
    SystemPrioritySeperation = 39,
    SystemVerifierAddDriverInformation = 40,
    SystemVerifierRemoveDriverInformation = 41,
    SystemProcessorIdleInformation = 42,
    SystemLegacyDriverInformation = 43,
    SystemCurrentTimeZoneInformation = 44,
    SystemLookasideInformation = 45,
    SystemTimeSlipNotification = 46,
    SystemSessionCreate = 47,
    SystemSessionDetach = 48,
    SystemSessionInformation = 49,
    SystemRangeStartInformation = 50,
    SystemVerifierInformation = 51,
    SystemVerifierThunkExtend = 52,
    SystemSessionProcessInformation = 53,
    SystemLoadGdiDriverInSystemSpace = 54,
    SystemNumaProcessorMap = 55,
    SystemPrefetcherInformation = 56,
    SystemExtendedProcessInformation = 57,
    SystemRecommendedSharedDataAlignment = 58,
    SystemComPlusPackage = 59,
    SystemNumaAvailableMemory = 60,
    SystemProcessorPowerInformation = 61,
    SystemEmulationBasicInformation = 62,
    SystemEmulationProcessorInformation = 63,
    SystemExtendedHandleInformation = 64,
    SystemLostDelayedWriteInformation = 65,
    SystemBigPoolInformation = 66,
    SystemSessionPoolTagInformation = 67,
    SystemSessionMappedViewInformation = 68,
    SystemHotpatchInformation = 69,
    SystemObjectSecurityMode = 70,
    SystemWatchdogTimerHandler = 71,
    SystemWatchdogTimerInformation = 72,
    SystemLogicalProcessorInformation = 73,
    SystemWow64SharedInformationObsolete = 74,
    SystemRegisterFirmwareTableInformationHandler = 75,
    SystemFirmwareTableInformation = 76,
    SystemModuleInformationEx = 77,
    SystemVerifierTriageInformation = 78,
    SystemSuperfetchInformation = 79,
    SystemMemoryListInformation = 80,
    SystemFileCacheInformationEx = 81,
    SystemThreadPriorityClientIdInformation = 82,
    SystemProcessorIdleCycleTimeInformation = 83,
    SystemVerifierCancellationInformation = 84,
    SystemProcessorPowerInformationEx = 85,
    SystemRefTraceInformation = 86,
    SystemSpecialPoolInformation = 87,
    SystemProcessIdInformation = 88,
    SystemErrorPortInformation = 89,
    SystemBootEnvironmentInformation = 90,
    SystemHypervisorInformation = 91,
    SystemVerifierInformationEx = 92,
    SystemTimeZoneInformation = 93,
    SystemImageFileExecutionOptionsInformation = 94,
    SystemCoverageInformation = 95,
    SystemPrefetchPatchInformation = 96,
    SystemVerifierFaultsInformation = 97,
    SystemSystemPartitionInformation = 98,
    SystemSystemDiskInformation = 99,
    SystemProcessorPerformanceDistribution = 100,
    SystemNumaProximityNodeInformation = 101,
    SystemDynamicTimeZoneInformation = 102,
    SystemCodeIntegrityInformation = 103,
    SystemProcessorMicrocodeUpdateInformation = 104,
    SystemProcessorBrandString = 105,
    SystemVirtualAddressInformation = 106,
    SystemLogicalProcessorAndGroupInformation = 107,
    SystemProcessorCycleTimeInformation = 108,
    SystemStoreInformation = 109,
    SystemRegistryAppendString = 110,
    SystemAitSamplingValue = 111,
    SystemVhdBootInformation = 112,
    SystemCpuQuotaInformation = 113,
    SystemNativeBasicInformation = 114,
    SystemErrorPortTimeouts = 115,
    SystemLowPriorityIoInformation = 116,
    SystemBootEntropyInformation = 117,
    SystemVerifierCountersInformation = 118,
    SystemPagedPoolInformationEx = 119,
    SystemSystemPtesInformationEx = 120,
    SystemNodeDistanceInformation = 121,
    SystemAcpiAuditInformation = 122,
    SystemBasicPerformanceInformation = 123,
    SystemQueryPerformanceCounterInformation = 124,
    SystemSessionBigPoolInformation = 125,
    SystemBootGraphicsInformation = 126,
    SystemScrubPhysicalMemoryInformation = 127,
    SystemBadPageInformation = 128,
    SystemProcessorProfileControlArea = 129,
    SystemCombinePhysicalMemoryInformation = 130,
    SystemEntropyInterruptTimingInformation = 131,
    SystemConsoleInformation = 132,
    SystemPlatformBinaryInformation = 133,
    SystemPolicyInformation = 134,
    SystemHypervisorProcessorCountInformation = 135,
    SystemDeviceDataInformation = 136,
    SystemDeviceDataEnumerationInformation = 137,
    SystemMemoryTopologyInformation = 138,
    SystemMemoryChannelInformation = 139,
    SystemBootLogoInformation = 140,
    SystemProcessorPerformanceInformationEx = 141,
    SystemCriticalProcessErrorLogInformation = 142,
    SystemSecureBootPolicyInformation = 143,
    SystemPageFileInformationEx = 144,
    SystemSecureBootInformation = 145,
    SystemEntropyInterruptTimingRawInformation = 146,
    SystemPortableWorkspaceEfiLauncherInformation = 147,
    SystemFullProcessInformation = 148,
    SystemKernelDebuggerInformationEx = 149,
    SystemBootMetadataInformation = 150,
    SystemSoftRebootInformation = 151,
    SystemElamCertificateInformation = 152,
    SystemOfflineDumpConfigInformation = 153,
    SystemProcessorFeaturesInformation = 154,
    SystemRegistryReconciliationInformation = 155,
    SystemEdidInformation = 156,
    SystemManufacturingInformation = 157,
    SystemEnergyEstimationConfigInformation = 158,
    SystemHypervisorDetailInformation = 159,
    SystemProcessorCycleStatsInformation = 160,
    SystemVmGenerationCountInformation = 161,
    SystemTrustedPlatformModuleInformation = 162,
    SystemKernelDebuggerFlags = 163,
    SystemCodeIntegrityPolicyInformation = 164,
    SystemIsolatedUserModeInformation = 165,
    SystemHardwareSecurityTestInterfaceResultsInformation = 166,
    SystemSingleModuleInformation = 167,
    SystemAllowedCpuSetsInformation = 168,
    SystemVsmProtectionInformation = 169,
    SystemInterruptCpuSetsInformation = 170,
    SystemSecureBootPolicyFullInformation = 171,
    SystemCodeIntegrityPolicyFullInformation = 172,
    SystemAffinitizedInterruptProcessorInformation = 173,
    SystemRootSiloInformation = 174,
    SystemCpuSetInformation = 175,
    SystemCpuSetTagInformation = 176,
    SystemWin32WerStartCallout = 177,
    SystemSecureKernelProfileInformation = 178,
    SystemCodeIntegrityPlatformManifestInformation = 179,
    SystemInterruptSteeringInformation = 180,
    SystemSupportedProcessorArchitectures = 181,
    SystemMemoryUsageInformation = 182,
    SystemCodeIntegrityCertificateInformation = 183,
    SystemPhysicalMemoryInformation = 184,
    SystemControlFlowTransition = 185,
    SystemKernelDebuggingAllowed = 186,
    SystemActivityModerationExeState = 187,
    SystemActivityModerationUserSettings = 188,
    SystemCodeIntegrityPoliciesFullInformation = 189,
    SystemCodeIntegrityUnlockInformation = 190,
    SystemIntegrityQuotaInformation = 191,
    SystemFlushInformation = 192,
    SystemProcessorIdleMaskInformation = 193,
    SystemSecureDumpEncryptionInformation = 194,
    SystemWriteConstraintInformation = 195,
    SystemKernelVaShadowInformation = 196,
    SystemHypervisorSharedPageInformation = 197,
    SystemFirmwareBootPerformanceInformation = 198,
    SystemCodeIntegrityVerificationInformation = 199,
    SystemFirmwarePartitionInformation = 200,
    SystemSpeculationControlInformation = 201,
    SystemDmaGuardPolicyInformation = 202,
    SystemEnclaveLaunchControlInformation = 203,
    SystemWorkloadAllowedCpuSetsInformation = 204,
    SystemCodeIntegrityUnlockModeInformation = 205,
    SystemLeapSecondInformation = 206,
    SystemFlags2Information = 207,
    SystemSecurityModelInformation = 208,
    SystemCodeIntegritySyntheticCacheInformation = 209,
    SystemFeatureConfigurationInformation = 210,
    SystemFeatureConfigurationSectionInformation = 211,
    SystemFeatureUsageSubscriptionInformation = 212,
    SystemSecureSpeculationControlInformation = 213,
    SystemSpacesBootInformation = 214,
    SystemFwRamdiskInformation = 215,
    SystemWheaIpmiHardwareInformation = 216,
    SystemDifSetRuleClassInformation = 217,
    SystemDifClearRuleClassInformation = 218,
    SystemDifApplyPluginVerificationOnDriver = 219,
    SystemDifRemovePluginVerificationOnDriver = 220,
    SystemShadowStackInformation = 221,
    SystemBuildVersionInformation = 222,
    SystemPoolLimitInformation = 223,
    SystemCodeIntegrityAddDynamicStore = 224,
    SystemCodeIntegrityClearDynamicStores = 225,
    SystemPoolZeroingInformation = 227,
    MaxSystemInfoClass = 228
} SYSTEM_INFORMATION_CLASS, * PSYSTEM_INFORMATION_CLASS;

typedef struct _SYSTEM_MODULE_ENTRY {
    ULONG_PTR  Unused;
    ULONG_PTR  Always0;
    PVOID  ModuleBaseAddress;
    ULONG  ModuleSize;
    ULONG  Unknown;
    ULONG  ModuleEntryIndex;
    USHORT ModuleNameLength;
    USHORT ModuleNameOffset;
    CHAR   ModuleName[256];
} SYSTEM_MODULE_ENTRY, * PSYSTEM_MODULE_ENTRY;

typedef struct _SYSTEM_MODULE_INFORMATION {
    ULONG               Count;
    SYSTEM_MODULE_ENTRY Module[1];
} SYSTEM_MODULE_INFORMATION, * PSYSTEM_MODULE_INFORMATION;

typedef enum _OBJECT_INFO_CLASS {
    ObjectBasicInformation,
    ObjectNameInformation,
    ObjectTypeInformation,
    ObjectAllTypesInformation,
    ObjectHandleInformation
} OBJECT_INFO_CLASS, * POBJECT_INFO_CLASS;