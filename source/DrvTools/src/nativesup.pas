{*******************************************************************************
*
*  (C) COPYRIGHT AUTHORS, 2021 - 2022
*
*  TITLE:       nativesup.pas
*
*  VERSION:     1.01
*
*  DATE:        27 Mar 2022
*
*  Windows Native API support routines.
*  ObjFPC variant, based on Win32Pascal WinNative of v1.43
*
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
* TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
*******************************************************************************}
unit nativesup;

{$mode objfpc}{$H+}

interface

uses
  Windows, SysUtils;

{$calling stdcall}

const
  ntdll = 'ntdll.dll';
  win32u = 'win32u.dll';
  ntoskrnl = 'ntoskrnl.exe';
  hal = 'hal.dll';

  OBJECT_TYPE_DIRECTORY = 'Directory';
  OBJECT_TYPE_DEVICE = 'Device';
  OBJECT_TYPE_SYMLINK = 'SymbolicLink';

  NT_REGISTRY_MACHINE = '\Registry\Machine';
  NT_PATH_PREFIX = '\??\';
  NT_SYSTEM_ROOT = '\SystemRoot';
  WIN32_CURRENTCONTROL_SERVICES = 'System\CurrentControlSet\Services\%S';

  NtCurrentProcess = DWORD(-1);
  NtCurrentThread = DWORD(-2);

  SECURITY_NT_AUTHORITY: array[0..5] of byte = (0, 0, 0, 0, 0, 5);

  SE_GROUP_USE_FOR_DENY_ONLY = $00000010;

  {privileges}

  SE_MIN_WELL_KNOWN_PRIVILEGE = 2;
  SE_CREATE_TOKEN_PRIVILEGE = 2;
  SE_ASSIGNPRIMARYTOKEN_PRIVILEGE = 3;
  SE_LOCK_MEMORY_PRIVILEGE = 4;
  SE_INCREASE_QUOTA_PRIVILEGE = 5;
  SE_MACHINE_ACCOUNT_PRIVILEGE = 6;
  SE_TCB_PRIVILEGE = 7;
  SE_SECURITY_PRIVILEGE = 8;
  SE_TAKE_OWNERSHIP_PRIVILEGE = 9;
  SE_LOAD_DRIVER_PRIVILEGE = 10;
  SE_SYSTEM_PROFILE_PRIVILEGE = 11;
  SE_SYSTEMTIME_PRIVILEGE = 12;
  SE_PROF_SINGLE_PROCESS_PRIVILEGE = 13;
  SE_INC_BASE_PRIORITY_PRIVILEGE = 14;
  SE_CREATE_PAGEFILE_PRIVILEGE = 15;
  SE_CREATE_PERMANENT_PRIVILEGE = 16;
  SE_BACKUP_PRIVILEGE = 17;
  SE_RESTORE_PRIVILEGE = 18;
  SE_SHUTDOWN_PRIVILEGE = 19;
  SE_DEBUG_PRIVILEGE = 20;
  SE_AUDIT_PRIVILEGE = 21;
  SE_SYSTEM_ENVIRONMENT_PRIVILEGE = 22;
  SE_CHANGE_NOTIFY_PRIVILEGE = 23;
  SE_REMOTE_SHUTDOWN_PRIVILEGE = 24;
  SE_UNDOCK_PRIVILEGE = 25;
  SE_SYNC_AGENT_PRIVILEGE = 26;
  SE_ENABLE_DELEGATION_PRIVILEGE = 27;
  SE_MANAGE_VOLUME_PRIVILEGE = 28;
  SE_IMPERSONATE_PRIVILEGE = 29;
  SE_CREATE_GLOBAL_PRIVILEGE = 30;
  SE_TRUSTED_CREDMAN_ACCESS_PRIVILEGE = 31;
  SE_RELABEL_PRIVILEGE = 32;
  SE_INC_WORKING_SET_PRIVILEGE = 33;
  SE_TIME_ZONE_PRIVILEGE = 34;
  SE_CREATE_SYMBOLIC_LINK_PRIVILEGE = 35;
  SE_DELEGATE_SESSION_USER_IMPERSONATE_PRIVILEGE = 36;
  SE_MAX_WELL_KNOWN_PRIVILEGE = SE_DELEGATE_SESSION_USER_IMPERSONATE_PRIVILEGE;

  {file consts}
  FILE_SUPERSEDE = $00000000;
  FILE_OPEN = $00000001;
  FILE_CREATE = $00000002;
  FILE_OPEN_IF = $00000003;
  FILE_OVERWRITE = $00000004;
  FILE_APPEND_DATA = $00000004;
  FILE_OVERWRITE_IF = $00000005;
  FILE_MAXIMUM_DISPOSITION = $00000005;

  FILE_DIRECTORY_FILE = $00000001;
  FILE_WRITE_THROUGH = $00000002;
  FILE_SEQUENTIAL_ONLY = $00000004;
  FILE_NO_INTERMEDIATE_BUFFERING = $00000008;
  FILE_SYNCHRONOUS_IO_ALERT = $00000010;
  FILE_SYNCHRONOUS_IO_NONALERT = $00000020;
  FILE_NON_DIRECTORY_FILE = $00000040;
  FILE_CREATE_TREE_CONNECTION = $00000080;
  FILE_COMPLETE_IF_OPLOCKED = $00000100;
  FILE_NO_EA_KNOWLEDGE = $00000200;
  FILE_OPEN_FOR_RECOVERY = $00000400;
  FILE_RANDOM_ACCESS = $00000800;
  FILE_DELETE_ON_CLOSE = $00001000;
  FILE_OPEN_BY_FILE_ID = $00002000;
  FILE_OPEN_FOR_BACKUP_INTENT = $00004000;
  FILE_NO_COMPRESSION = $00008000;
  FILE_RESERVE_OPFILTER = $00100000;
  FILE_OPEN_REPARSE_POINT = $00200000;
  FILE_OPEN_NO_RECALL = $00400000;
  FILE_OPEN_FOR_FREE_SPACE_QUERY = $00800000;
  FILE_ANY_ACCESS = $00000000;
  FILE_SPECIAL_ACCESS = FILE_ANY_ACCESS;
  FILE_READ_ACCESS = $00000001;
  FILE_LIST_DIRECTORY = $0000001;
  FILE_WRITE_ACCESS = $00000002;
  FILE_READ_DATA = $00000001;
  FILE_ADD_FILE = $00000002;
  FILE_WRITE_DATA = $00000002;
  FILE_ADD_SUBDIRECTORY = $00000004;
  FILE_CREATE_PIPE_INSTANCE = $00000004;
  FILE_READ_EA = $00000008;
  FILE_WRITE_EA = $00000010;
  FILE_EXECUTE = $00000020;
  FILE_TRAVERSE = $00000020;
  FILE_DELETE_CHILD = $00000040;
  FILE_READ_ATTRIBUTES = $00000080;
  FILE_WRITE_ATTRIBUTES = $00000100;
  FILE_ALL_ACCESS = (STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or $1FF);

  FILE_GENERIC_READ = (STANDARD_RIGHTS_READ or FILE_READ_DATA or
    FILE_READ_ATTRIBUTES or FILE_READ_EA or SYNCHRONIZE);

  FILE_GENERIC_WRITE = (STANDARD_RIGHTS_WRITE or FILE_WRITE_DATA or
    FILE_WRITE_ATTRIBUTES or FILE_WRITE_EA or FILE_APPEND_DATA or SYNCHRONIZE);

  FILE_ATTRIBUTE_READONLY = $00000001;
  FILE_ATTRIBUTE_HIDDEN = $00000002;
  FILE_ATTRIBUTE_SYSTEM = $00000004;
  FILE_ATTRIBUTE_DIRECTORY = $00000010;
  FILE_ATTRIBUTE_ARCHIVE = $00000020;
  FILE_ATTRIBUTE_DEVICE = $00000040;
  FILE_ATTRIBUTE_NORMAL = $00000080;
  FILE_ATTRIBUTE_TEMPORARY = $00000100;
  FILE_ATTRIBUTE_SPARSE_FILE = $00000200;
  FILE_ATTRIBUTE_REPARSE_POINT = $00000400;
  FILE_ATTRIBUTE_COMPRESSED = $00000800;
  FILE_ATTRIBUTE_OFFLINE = $00001000;
  FILE_ATTRIBUTE_NOT_CONTENT_INDEXED = $00002000;
  FILE_ATTRIBUTE_ENCRYPTED = $00004000;

  {object attributes}
  OBJ_INHERIT = $00000002;
  OBJ_PERMANENT = $00000010;
  OBJ_EXCLUSIVE = $00000020;
  OBJ_CASE_INSENSITIVE = $00000040;
  OBJ_OPENIF = $00000080;
  OBJ_OPENLINK = $00000100;
  OBJ_KERNEL_HANDLE = $00000200;

  {symlink desired access}
  SYMBOLIC_LINK_QUERY = $1;
  SYMBOLIC_LINK_ALL_ACCESS = (STANDARD_RIGHTS_REQUIRED or SYMBOLIC_LINK_QUERY);

  {directory object desired access}
  DIRECTORY_QUERY = $0001;
  DIRECTORY_TRAVERSE = $0002;
  DIRECTORY_CREATE_OBJECT = $0004;
  DIRECTORY_CREATE_SUBDIRECTORY = $0008;
  DIRECTORY_ALL_ACCESS = (STANDARD_RIGHTS_REQUIRED or DIRECTORY_QUERY or
    DIRECTORY_TRAVERSE or DIRECTORY_CREATE_OBJECT or DIRECTORY_CREATE_SUBDIRECTORY);

{begin shitty borland modules definitions workaround}
type
  PFNREADFILEPROC = function(hFile: THandle; lpBuffer: pointer;
    nNumberOfBytesToRead: DWORD; lpNumberOfBytesRead: PDWORD;
    lpOverlapped: POVERLAPPED): BOOL; stdcall;

  PFNWRITEFILEPROC = function(hFile: THandle; lpBuffer: pointer;
    nNumberOfBytesToWrite: DWORD; lpNumberOfBytesWritten: PDWORD;
    lpOverlapped: POVERLAPPED): BOOL; stdcall;

const
  pp1: pointer = @Windows.ReadFile;
  pp2: pointer = @Windows.WriteFile;

var
  _ReadFile: PFNREADFILEPROC absolute pp1;
  _WriteFile: PFNWRITEFILEPROC absolute pp2;
{end of shitty borland modules definitions workaround}

type
  NTSTATUS = LONG;
  UCHAR = byte;
  PUCHAR = ^byte;
  USHORT = word;
  PUSHORT = ^word;
  ULONG = longword;
  PULONG = PLongWord;
  PCUCHAR = ^UCHAR; { const }
  PCUSHORT = ^USHORT; { const }
  PCULONG = ^ULONG; { const }

{$i ntstatus.inc}

function RegDeleteTreeW(hKey: HKEY; lpSubKey: LPCWSTR): LONG;
  external 'advapi32' Name 'RegDeleteTreeW';

type
  _ANSI_STRING = record
    Length: word;
    MaximumLength: word;
    Buffer: PAnsiChar;
  end;
  ANSI_STRING = _ANSI_STRING;
  PANSI_STRING = ^_ANSI_STRING;

  _UNICODE_STRING = record
    Length: word;
    MaximumLength: word;
    Buffer: PWideChar;
  end;
  UNICODE_STRING = _UNICODE_STRING;
  PUNICODE_STRING = ^_UNICODE_STRING;
  PCUNICODE_STRING = ^_UNICODE_STRING;

  _CURDIR = record
    DosPath: UNICODE_STRING;
    Handle: THANDLE;
  end;
  CURDIR = _CURDIR;
  PCURDIR = ^_CURDIR;

  _IO_STATUS_BLOCK = record
    Status: NTSTATUS;
    uInformation: ULONG;
  end;
  IO_STATUS_BLOCK = _IO_STATUS_BLOCK;
  PIO_STATUS_BLOCK = ^_IO_STATUS_BLOCK;

  _OBJECT_ATTRIBUTES = record
    Length: ULONG;
    RootDirectory: THandle;
    ObjectName: PUNICODE_STRING;
    Attributes: ULONG;
    SecurityDescriptor: Pointer; // Points to type SECURITY_DESCRIPTOR
    SecurityQualityOfService: Pointer; // Points to type SECURITY_QUALITY_OF_SERVICE
  end;
  OBJECT_ATTRIBUTES = _OBJECT_ATTRIBUTES;
  POBJECT_ATTRIBUTES = ^_OBJECT_ATTRIBUTES;

  PIO_APC_ROUTINE = procedure(ApcContext: pointer; IoStatusBlock: PIO_STATUS_BLOCK;
    Reserved: cardinal);

type
  _SYSTEM_INFORMATION_CLASS = (
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
    SystemSpare0 = 142,
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
    SystemVsmProtectionInformation = 169, //ex SystemDmaProtectionInformation
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
    SystemDifPoolTrackingInformation = 226,
    SystemPoolZeroingInformation = 227,
    SystemDpcWatchdogInformation = 228,
    SystemDpcWatchdogInformation2 = 229,
    SystemSupportedProcessorArchitectures2 = 230,
    SystemSingleProcessorRelationshipInformation = 231,
    SystemXfgCheckFailureInformation = 232,
    MaxSystemInfoClass);
  SYSTEM_INFORMATION_CLASS = _SYSTEM_INFORMATION_CLASS;
  PSYSTEM_INFORMATION_CLASS = ^_SYSTEM_INFORMATION_CLASS;

type
  _OBJECT_DIRECTORY_INFORMATION = record
    Name: UNICODE_STRING;
    TypeName: UNICODE_STRING;
  end;
  OBJECT_DIRECTORY_INFORMATION = _OBJECT_DIRECTORY_INFORMATION;
  POBJECT_DIRECTORY_INFORMATION = ^_OBJECT_DIRECTORY_INFORMATION;

  _SYSTEM_HANDLE_TABLE_ENTRY_INFO = record
    UniqueProcessId: USHORT;
    CreatorBackTraceIndex: USHORT;
    ObjectTypeIndex: UCHAR;
    HandleAttributes: UCHAR;
    HandleValue: USHORT;
    ObjectPointer: PVOID;
    GrantedAccess: ACCESS_MASK;
  end;
  SYSTEM_HANDLE_TABLE_ENTRY_INFO = _SYSTEM_HANDLE_TABLE_ENTRY_INFO;
  PSYSTEM_HANDLE_TABLE_ENTRY_INFO = ^_SYSTEM_HANDLE_TABLE_ENTRY_INFO;

  _SYSTEM_HANDLE_INFORMATION = record
    NumberOfHandles: ULONG;
    Handles: array[0..0] of SYSTEM_HANDLE_TABLE_ENTRY_INFO;
  end;
  SYSTEM_HANDLE_INFORMATION = _SYSTEM_HANDLE_INFORMATION;
  PSYSTEM_HANDLE_INFORMATION = ^_SYSTEM_HANDLE_INFORMATION;

  _SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX = record
    ObjectPointer: PVOID;
    UniqueProcessId: ULONG_PTR;
    HandleValue: ULONG_PTR;
    GrantedAccess: ULONG;
    CreatorBackTraceIndex: USHORT;
    ObjectTypeIndex: USHORT;
    HandleAttributes: ULONG;
    Reserved: ULONG;
  end;
  SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX = _SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX;
  PSYSTEM_HANDLE_TABLE_ENTRY_INFO_EX = ^_SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX;

  _SYSTEM_HANDLE_INFORMATION_EX = record
    NumberOfHandles: ULONG_PTR;
    Reserved: ULONG_PTR;
    Handles: array[0..0] of SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX;
  end;
  SYSTEM_HANDLE_INFORMATION_EX = _SYSTEM_HANDLE_INFORMATION_EX;
  PSYSTEM_HANDLE_INFORMATION_EX = ^_SYSTEM_HANDLE_INFORMATION_EX;

procedure RtlInitUnicodeString(
  {IN} DestinationString: PUNICODE_STRING;
  {IN} const SourceString: PWideChar); stdcall; external ntdll;

function RtlEqualUnicodeString(
  {IN} String1: PCUNICODE_STRING;
  {IN} String2: PCUNICODE_STRING;
  {IN} CaseInSensitive: boolean): boolean; stdcall; external ntdll;

function NtQuerySystemInformation(
  {IN} InfoClass: SYSTEM_INFORMATION_CLASS;
  {IN} SystemInformation: PVOID;
  {IN} SystemInformationLength: DWORD;
  {OUT} ReturnLength: PULONG): NTSTATUS; stdcall; external ntdll;

function NtLoadDriver(
  {IN} DriverServiceName: PUNICODE_STRING): NTSTATUS; stdcall; external ntdll;

function NtUnloadDriver(
  {IN} DriverServiceName: PUNICODE_STRING): NTSTATUS; stdcall; external ntdll;

function NtCreateFile(
  {OUT} var FileHandle: THANDLE;
  {IN} DesiredAccess: ACCESS_MASK;
  {IN} ObjectAttributes: POBJECT_ATTRIBUTES;
  {OUT} var IoStatusBlock: IO_STATUS_BLOCK;
  {IN} AllocationSize: PLARGE_INTEGER {OPTIONAL};
  {IN} FileAttributes: ULONG;
  {IN} ShareAccess: ULONG;
  {IN} CreateDisposition: ULONG;
  {IN} CreateOptions: ULONG;
  {IN} EaBuffer: PVOID {OPTIONAL};
  {IN} EaLength: ULONG): NTSTATUS; stdcall; external ntdll;

function NtOpenFile(
  {OUT} var FileHandle: THANDLE;
  {IN} DesiredAccess: ACCESS_MASK;
  {IN} ObjectAttributes: POBJECT_ATTRIBUTES;
  {OUT} var IoStatusBlock: IO_STATUS_BLOCK;
  {IN} ShareAccess: ULONG;
  {IN} OpenOptions: ULONG): NTSTATUS; stdcall; external ntdll;

function NtReadFile(
  {IN} FileHandle: THANDLE;
  {IN} Event: THANDLE {OPTIONAL};
  {IN} ApcRoutine: PVOID {PIO_APC_ROUTINE} {OPTIONAL};
  {IN} ApcContext: PVOID {OPTIONAL};
  {OUT} var IoStatusBlock: IO_STATUS_BLOCK;
  {OUT} Buffer: PVOID;
  {IN} Length: ULONG;
  {IN} ByteOffset: PLARGE_INTEGER;
  {IN} Key: PULONG {OPTIONAL}): NTSTATUS; stdcall; external ntdll;

function NtWriteFile(
  {IN} FileHandle: THANDLE;
  {IN} Event: THANDLE; {OPTIONAL}
  {IN} ApcRoutine: PVOID; {PIO_APC_ROUTINE}{OPTIONAL}
  {IN} ApcContext: Pointer;  {OPTIONAL}
  {OUT} var IoStatusBlock: IO_STATUS_BLOCK;
  {OUT} Buffer: Pointer;
  {IN} Length: ULONG;
  {IN} FileOffset: PLARGE_INTEGER;
  {IN}  Key: PDWORD {OPTIONAL}
  ): NTSTATUS; stdcall; external ntdll;

function NtDeviceIoControlFile(
  {IN} DeviceHandle: THANDLE;
  {IN} Event: THANDLE; {OPTIONAL}
  {IN} ApcRoutine: PVOID; {PIO_APC_ROUTINE} {OPTIONAL}
  {IN} ApcContext: PVOID; {OPTIONAL}
  {OUT} IoStatusBlock: PIO_STATUS_BLOCK;
  {IN} IoControlCode: ULONG;
  {IN} InputBuffer: PVOID;
  {IN} InputBufferSize: ULONG;
  {IN} OutputBuffer: PVOID;
  {IN} OutputBufferSize: ULONG): NTSTATUS; stdcall; external ntdll;

function NtCreateSymbolicLinkObject(
  {OUT} var LinkHandle: THANDLE;
  {IN} DesiredAccess: ACCESS_MASK;
  {IN} ObjectAttributes: POBJECT_ATTRIBUTES;
  {IN} LinkTarget: PUNICODE_STRING): NTSTATUS; stdcall; external ntdll;

function NtOpenProcessToken(
  {IN} ProcessHandle: THANDLE;
  {IN} DesiredAccess: ACCESS_MASK;
  {IN} TokenHandle: PHANDLE): NTSTATUS; stdcall; external ntdll;

function NtOpenThreadToken(
  {IN} hThread: THANDLE;
  {IN} DesiredAccess: ACCESS_MASK;
  {IN} bOpenAsSelf: boolean;
  {OUT} var phToken: THANDLE): NTSTATUS; stdcall; external ntdll;

function NtAdjustPrivilegesToken(
  {IN} TokenHandle: THANDLE;
  {IN} DisableAllPrivileges: boolean;
  {IN} NewState: Pointer;
  {IN} BufferLength: ULONG;
  {IN} PreviousState: Pointer;
  {IN} var ReturnLength: ULONG): NTSTATUS; stdcall; external ntdll;

function NtQueryInformationToken(
  {IN} TokenHandle: THANDLE;
  {IN} TokenInformationClass: TOKEN_INFORMATION_CLASS;
  {IN} TokenInformation: PVOID;
  {IN} TokenInformationLength: ULONG;
  {OUT} ReturnLength: PULONG): NTSTATUS; stdcall; external ntdll;

function NtClose(
  {IN} Handle: HANDLE): NTSTATUS; stdcall; external ntdll;

function NtQueryDirectoryObject(
  {IN} DirectoryHandle: THANDLE;
  {IN} Buffer: PVOID;
  {IN} Length: ULONG;
  {IN} ReturnSingleEntry: boolean;
  {IN} RestartScan: boolean;
  {OUT} Context: PULONG;
  {OUT} ReturnLength: PULONG): NTSTATUS; stdcall; external ntdll;

function NtOpenDirectoryObject(
  {OUT} DirectoryHandle: PHANDLE;
  {IN} AccessMask: ACCESS_MASK;
  {IN} ObjectAttributes: POBJECT_ATTRIBUTES): NTSTATUS; stdcall; external ntdll;

function RtlAdjustPrivilege(
  {IN} Privilege: DWORD;
  {IN} NewValue: boolean;
  {IN} ForThread: boolean;
  {IN} var OldValue: boolean): NTSTATUS; stdcall; external ntdll;

function RtlDosPathNameToNtPathName_U(
  {IN} DosName: PCWSTR;
  {IN} NtName: PUNICODE_STRING;
  {IN} ShortName: PWSTR;
  {IN} CurrentDirectory: PCURDIR): boolean; stdcall external ntdll;

procedure RtlFreeAnsiString(
  {IN} DestinationString: PANSI_STRING); stdcall; external ntdll;

procedure RtlFreeUnicodeString(
  {IN} DestinationString: PUNICODE_STRING); stdcall; external ntdll;

function RtlAllocateAndInitializeSid(
  {IN} IdentifierAuthority: PSID_IDENTIFIER_AUTHORITY;
  {IN} SubAuthorityCount: UCHAR;
  {IN} SubAuthority0: ULONG;
  {IN} SubAuthority1: ULONG;
  {IN} SubAuthority2: ULONG;
  {IN} SubAuthority3: ULONG;
  {IN} SubAuthority4: ULONG;
  {IN} SubAuthority5: ULONG;
  {IN} SubAuthority6: ULONG;
  {IN} SubAuthority7: ULONG;
  {IN} Sid: PSID //pointer to PSID
  ): NTSTATUS; stdcall; external ntdll;

function RtlAllocateHeap(
  {IN} HeapHandle: THANDLE;
  {IN} Flags: ULONG;
  {IN} Size: SIZE_T): PVOID; stdcall external ntdll;

function RtlFreeHeap(
  {IN} HeapHandle: THANDLE;
  {IN} Flags: ULONG;
  {IN} HeapBase: PVOID): boolean; stdcall; external ntdll;

function RtlGetVersion(
  {IN} lpVersionInformation: POSVERSIONINFOW): DWORD; stdcall; external ntdll;

procedure InitializeObjectAttributes(
  {IN} var aObjectAttr: OBJECT_ATTRIBUTES;
  {IN} aName: PUNICODE_STRING;
  {IN} aAttributes: ULONG;
  {IN} aRootDir: HANDLE;
  {IN} aSecurity: PSECURITY_DESCRIPTOR = nil {OPTIONAL}); register;

function NT_SUCCESS(Status: NTSTATUS): boolean; register;
function NT_INFORMATION(Status: NTSTATUS): boolean; register;
function NT_WARNING(Status: NTSTATUS): boolean; register;
function NT_ERROR(Status: NTSTATUS): boolean; register;

function supHeapAlloc(Size: SIZE_T): PVOID;
function supHeapFree(Memory: PVOID): boolean;

function ntsupCreateDriverEntry(Name: LPCWSTR; ErrorControl: DWORD;
  StartType: DWORD; ImagePath: LPCWSTR; DisplayName: LPCWSTR;
  ConvertImagePath: boolean = False): NTSTATUS;

function ntsupRemoveDriverEntry(Name: LPCWSTR): NTSTATUS;

function ntsupOpenDevice(DeviceName: LPCWSTR; DesiredAccess: ACCESS_MASK;
  var DeviceHandle: THANDLE): NTSTATUS;

function ntsupOpenDeviceEx(DeviceName: LPCWSTR; DesiredAccess: ACCESS_MASK;
  var DeviceHandle: THANDLE): NTSTATUS;

function ntsupLoadDriverEx(DriverName: LPCWSTR; ImagePath: LPCWSTR;
  DisplayName: LPCWSTR; ErrorControl: DWORD; StartType: DWORD;
  UnloadPreviousInstance: boolean; ConvertImagePath: boolean): NTSTATUS;

function ntsupLoadDriver(DriverName: LPCWSTR; UnloadPreviousInstance: boolean): NTSTATUS;

function ntsupUnloadDriverEx(DriverName: LPCWSTR; RemoveEntry: boolean): NTSTATUS;
function ntsupUnloadDriver(DriverName: LPCWSTR): NTSTATUS;

function ntsupCreateSymbolicLink(var LinkHanlde: THANDLE; LinkName: LPCWSTR;
  LinkTarget: LPCWSTR): NTSTATUS;

function ntsupOpenDirectory(var DirectoryHandle: THANDLE;
  RootDirectoryHandle: THANDLE; DirectoryName: PWidechar;
  DesiredAccess: ACCESS_MASK): NTSTATUS;

function ntsupGetCurrentProcessToken(): THANDLE;

type
  EnumObjectsContext = record
    UserContext: PVOID;
    ObjectPathName: PWideChar;
  end;
  PEnumObjectsContext = ^EnumObjectsContext;

  PEnumObjectsCallback = function(Entry: POBJECT_DIRECTORY_INFORMATION;
    Context: PEnumObjectsContext): BOOL; stdcall;

function ntsupEnumerateObjects(RootDirectory: PWideChar;
  CallbackProc: PEnumObjectsCallback; CallbackContext: PEnumObjectsContext): BOOL;

implementation

procedure InitializeObjectAttributes(var aObjectAttr: OBJECT_ATTRIBUTES;
  aName: PUNICODE_STRING; aAttributes: ULONG; aRootDir: HANDLE;
  aSecurity: PSECURITY_DESCRIPTOR = nil); register;
begin
  with aObjectAttr do
  begin
    Length := SizeOf(OBJECT_ATTRIBUTES);
    RootDirectory := aRootDir;
    Attributes := aAttributes;
    ObjectName := aName;
    SecurityDescriptor := aSecurity;
    SecurityQualityOfService := nil;
  end;
end;

function NT_SUCCESS(Status: NTSTATUS): boolean; register;
begin
  Result := Status >= 0;
end;

function NT_INFORMATION(Status: NTSTATUS): boolean; register;
begin
  Result := ULONG(Status) shr 30 = 1;
end;

function NT_WARNING(Status: NTSTATUS): boolean; register;
begin
  Result := ULONG(Status) shr 30 = 2;
end;

function NT_ERROR(Status: NTSTATUS): boolean; register;
begin
  Result := ULONG(Status) shr 30 = 3;
end;

procedure RtlInitEmptyUnicodeString(InputBuffer: PWSTR; InputSize: DWORD;
  var UString: UNICODE_STRING);
begin
  with UString do
  begin
    Length := 0;
    MaximumLength := InputSize;
    Buffer := InputBuffer;
  end;
end;

function supHeapAlloc(Size: SIZE_T): PVOID;
begin
  Result := RtlAllocateHeap(GetProcessHeap(), HEAP_ZERO_MEMORY, Size);
end;

function supHeapFree(Memory: PVOID): boolean;
begin
  Result := RtlFreeHeap(GetProcessHeap(), 0, Memory);
end;

function ntsupOpenDeviceEx(DeviceName: LPCWSTR; DesiredAccess: ACCESS_MASK;
  var DeviceHandle: THANDLE): NTSTATUS;
var
  usDeviceLink: UNICODE_STRING;
  objAttr: OBJECT_ATTRIBUTES;
  iost: IO_STATUS_BLOCK;
begin
  if (DeviceName <> nil) then
  begin

    with iost do
    begin
      Status := 0;
      uInformation := 0;
    end;

    RtlInitUnicodeString(@usDeviceLink, DeviceName);
    InitializeObjectAttributes(objAttr, @usDeviceLink, OBJ_CASE_INSENSITIVE, 0, nil);

    Result := NtCreateFile(DeviceHandle, DesiredAccess, @objAttr,
      iost, nil, 0, 0, FILE_OPEN, 0, nil, 0);
  end
  else
  begin
    Result := STATUS_INVALID_PARAMETER_1;
  end;
end;

function ntsupOpenDevice(DeviceName: LPCWSTR; DesiredAccess: ACCESS_MASK;
  var DeviceHandle: THANDLE): NTSTATUS;
var
  deviceLink: string;
begin
  if (DeviceName <> nil) then
  begin

    try
      deviceLink := Format('\Device\%S', [DeviceName]);
    except
      Result := STATUS_INVALID_PARAMETER_1;
      exit;
    end;

    Result := ntsupOpenDeviceEx(PWideChar(WideString(deviceLink)),
      DesiredAccess, DeviceHandle);

  end
  else
  begin
    Result := STATUS_INVALID_PARAMETER_1;
  end;
end;

function ntsupCreateDriverEntry(Name: LPCWSTR; ErrorControl: DWORD;
  StartType: DWORD; ImagePath: LPCWSTR; DisplayName: LPCWSTR;
  ConvertImagePath: boolean = False): NTSTATUS;
label
  Cleanup;
var
  driverImagePath: UNICODE_STRING;
  dwResult, dwData: DWORD;
  status: NTSTATUS;
  keyHandle: HKEY;
begin

  //mandatory
  if (Name = nil) then
  begin
    Result := STATUS_INVALID_PARAMETER_1;
    exit;
  end;

  if (ConvertImagePath) then
  begin

    with driverImagePath do
    begin
      Buffer := nil;
      Length := 0;
      MaximumLength := 0;
    end;

    if (ImagePath <> nil) then
    begin
      if (not RtlDosPathNameToNtPathName_U(ImagePath, @driverImagePath, nil, nil)) then
      begin
        Result := STATUS_INVALID_PARAMETER_2;
        exit;
      end;
    end;

  end
  else
  begin
    if (ImagePath <> nil) then
    begin
      RtlInitUnicodeString(@driverImagePath, ImagePath);
    end
    else
    begin
      //mandatory in case of symlink usage
      Result := STATUS_INVALID_PARAMETER_4;
      exit;
    end;
  end;

  keyHandle := 0;

  dwResult := RegCreateKeyExW(HKEY_LOCAL_MACHINE, Name, 0, nil,
    REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, nil, keyHandle, nil);
  if (dwResult <> ERROR_SUCCESS) then
  begin
    status := STATUS_ACCESS_DENIED;
    goto Cleanup;
  end;

  repeat

    dwResult := RegSetValueExW(keyHandle, 'ErrorControl', 0, REG_DWORD,
      @ErrorControl, sizeof(DWORD));

    if (dwResult <> ERROR_SUCCESS) then
      break;

    dwData := SERVICE_KERNEL_DRIVER;

    dwResult := RegSetValueExW(keyHandle, 'Type', 0, REG_DWORD,
      @dwData, sizeof(DWORD));

    if (dwResult <> ERROR_SUCCESS) then
      break;

    dwResult := RegSetValueExW(keyHandle, 'Start', 0, REG_DWORD,
      @StartType, sizeof(DWORD));

    if (dwResult <> ERROR_SUCCESS) then
      break;

    if (DisplayName <> nil) then
    begin
      //optional param, we do not check API result
      RegSetValueExW(keyHandle, 'DisplayName', 0, REG_SZ,
        DisplayName, (StrLen(DisplayName) + 1) * sizeof(WCHAR));
    end;

    if (ImagePath <> nil) then
    begin
      dwResult := RegSetValueExW(keyHandle, 'ImagePath', 0, REG_SZ,
        driverImagePath.Buffer, driverImagePath.Length + sizeof(WCHAR));
    end;

  until (True);

  RegCloseKey(keyHandle);

  if (dwResult <> ERROR_SUCCESS) then
  begin
    status := STATUS_ACCESS_DENIED;
  end
  else
  begin
    status := STATUS_SUCCESS;
  end;

  Cleanup:
    if (ConvertImagePath) then
    begin
      if (ImagePath <> nil) and (driverImagePath.Buffer <> nil) then
      begin
        RtlFreeUnicodeString(@driverImagePath);
      end;
    end;

  Result := status;
end;

function ntsupRemoveDriverEntry(Name: LPCWSTR): NTSTATUS;
var
  S: string;
  lResult: LONG;
  keyHandle: HKEY;
  lpSubKey: LPWSTR;
begin
  try
    S := Format(WIN32_CURRENTCONTROL_SERVICES, [Name]);
  except
    Result := STATUS_INVALID_PARAMETER;
    exit;
  end;

  lpSubKey := PWideChar(WideString(S));

  keyHandle := 0;
  lResult := RegOpenKeyEx(HKEY_LOCAL_MACHINE, nil, REG_OPTION_NON_VOLATILE,
    SERVICE_DELETE or KEY_ENUMERATE_SUB_KEYS or KEY_QUERY_VALUE, keyHandle);

  if (lResult = ERROR_SUCCESS) then
  begin
    lResult := RegDeleteTreeW(keyHandle, lpSubKey);
    RegCloseKey(keyHandle);
  end;

  if (lResult = ERROR_SUCCESS) then
    Result := STATUS_SUCCESS
  else
    Result := STATUS_UNSUCCESSFUL;

end;

function ntsupLoadDriverEx(DriverName: LPCWSTR; ImagePath: LPCWSTR;
  DisplayName: LPCWSTR; ErrorControl: DWORD; StartType: DWORD;
  UnloadPreviousInstance: boolean; ConvertImagePath: boolean): NTSTATUS;
var
  keyOffset: DWORD;
  usDrvKey: UNICODE_STRING;
  drvName: string;
begin

  //mandatory
  if (DriverName = nil) then
  begin
    Result := STATUS_INVALID_PARAMETER_1;
    exit;
  end;

  //mandatory
  if (ImagePath = nil) then
  begin
    Result := STATUS_INVALID_PARAMETER_2;
    exit;
  end;

  keyOffset := StrLen(NT_REGISTRY_MACHINE);

  try

    drvName := Format('%S\' + WIN32_CURRENTCONTROL_SERVICES,
      [NT_REGISTRY_MACHINE, DriverName]);

  except
    Result := STATUS_INTERNAL_ERROR;
    exit;
  end;

  Result := ntsupCreateDriverEntry(@DriverName[keyOffset], ErrorControl,
    StartType, ImagePath, DisplayName, ConvertImagePath);

  if not NT_SUCCESS(Result) then
    exit;

  RtlInitUnicodeString(@usDrvKey, PWideChar(WideString(drvName)));
  Result := NtLoadDriver(@usDrvKey);

  if (UnloadPreviousInstance) then
  begin

    if ((Result = STATUS_IMAGE_ALREADY_LOADED) or
      (Result = STATUS_OBJECT_NAME_COLLISION) or
      (Result = STATUS_OBJECT_NAME_EXISTS)) then
    begin
      Result := NtUnloadDriver(@usDrvKey);

      if (NT_SUCCESS(Result)) then
      begin
        Result := NtLoadDriver(@usDrvKey);
      end;

    end;

  end
  else
  begin
    if (Result = STATUS_OBJECT_NAME_EXISTS) then
      Result := STATUS_SUCCESS;
  end;

end;

function ntsupLoadDriver(DriverName: LPCWSTR; UnloadPreviousInstance: boolean): NTSTATUS;
var
  usDrvKey: UNICODE_STRING;
  drvName: string;
begin

  try
    drvName := Format('%S\' + WIN32_CURRENTCONTROL_SERVICES,
      [NT_REGISTRY_MACHINE, DriverName]);
  except
    Result := STATUS_INTERNAL_ERROR;
    exit;
  end;

  RtlInitUnicodeString(@usDrvKey, PWideChar(WideString(drvName)));
  Result := NtLoadDriver(@usDrvKey);

  if (UnloadPreviousInstance) then
  begin

    if ((Result = STATUS_IMAGE_ALREADY_LOADED) or
      (Result = STATUS_OBJECT_NAME_COLLISION) or
      (Result = STATUS_OBJECT_NAME_EXISTS)) then
    begin
      Result := NtUnloadDriver(@usDrvKey);

      if (NT_SUCCESS(Result)) then
      begin
        Result := NtLoadDriver(@usDrvKey);
      end;

    end;

  end
  else
  begin
    if (Result = STATUS_OBJECT_NAME_EXISTS) then
      Result := STATUS_SUCCESS;
  end;
end;

function ntsupUnloadDriverEx(DriverName: LPCWSTR; RemoveEntry: boolean): NTSTATUS;
var
  keyOffset: DWORD;
  usDrvKey: UNICODE_STRING;
  drvName: string;
begin
  //mandatory
  if (DriverName = nil) then
  begin
    Result := STATUS_INVALID_PARAMETER_1;
    exit;
  end;

  keyOffset := StrLen(NT_REGISTRY_MACHINE);

  try

    drvName := Format('%S\' + WIN32_CURRENTCONTROL_SERVICES,
      [NT_REGISTRY_MACHINE, DriverName]);

  except
    Result := STATUS_INTERNAL_ERROR;
    exit;
  end;

  Result := ntsupCreateDriverEntry(@DriverName[keyOffset], 0, 0, nil, nil, False);
  if not NT_SUCCESS(Result) then
    exit;

  RtlInitUnicodeString(@usDrvKey, PWideChar(WideString(drvName)));
  Result := NtUnloadDriver(@usDrvKey);

  if (NT_SUCCESS(Result) and RemoveEntry) then
  begin
    RegDeleteTreeW(HKEY_LOCAL_MACHINE, PWideChar(WideString(drvName[keyOffset])));
  end;

end;

function ntsupUnloadDriver(DriverName: LPCWSTR): NTSTATUS;
var
  usDrvKey: UNICODE_STRING;
  drvName: string;
begin
  //mandatory
  if (DriverName = nil) then
  begin
    Result := STATUS_INVALID_PARAMETER_1;
    exit;
  end;

  try

    drvName := Format('%S\' + WIN32_CURRENTCONTROL_SERVICES,
      [NT_REGISTRY_MACHINE, DriverName]);

  except
    Result := STATUS_INTERNAL_ERROR;
    exit;
  end;

  RtlInitUnicodeString(@usDrvKey, PWideChar(WideString(drvName)));
  Result := NtUnloadDriver(@usDrvKey);
end;

function ntsupCreateSymbolicLink(var LinkHanlde: THANDLE; LinkName: LPCWSTR;
  LinkTarget: LPCWSTR): NTSTATUS;
var
  objAttr: OBJECT_ATTRIBUTES;
  usTarget, usLink: UNICODE_STRING;
begin
  if (not RtlDosPathNameToNtPathName_U(LinkTarget, @usTarget, nil, nil)) then
  begin
    Result := STATUS_INVALID_PARAMETER_2;
    exit;
  end;

  RtlInitUnicodeString(@usLink, LinkName);
  InitializeObjectAttributes(objAttr, @usLink, OBJ_CASE_INSENSITIVE, 0, nil);

  Result := NtCreateSymbolicLinkObject(LinkHanlde, SYMBOLIC_LINK_ALL_ACCESS,
    @objAttr, @usTarget);
end;

function ntsupGetCurrentProcessToken(): THANDLE;
begin
  Result := 0;
  NtOpenProcessToken(NtCurrentProcess, TOKEN_QUERY, @Result);
end;

function ntsupOpenDirectory(var DirectoryHandle: THANDLE;
  RootDirectoryHandle: THANDLE; DirectoryName: PWidechar;
  DesiredAccess: ACCESS_MASK): NTSTATUS;
var
  status: NTSTATUS;
  dirHandle: THANDLE;
  usDirectory: UNICODE_STRING;
  objectAttrbutes: OBJECT_ATTRIBUTES;
begin

  DirectoryHandle := 0;
  RtlInitUnicodeString(@usDirectory, DirectoryName);
  InitializeObjectAttributes(objectAttrbutes, @usDirectory,
    OBJ_CASE_INSENSITIVE, RootDirectoryHandle, nil);

  status := NtOpenDirectoryObject(@dirHandle, DesiredAccess, @objectAttrbutes);

  if (NT_SUCCESS(status)) then
    DirectoryHandle := dirHandle;

  Result := status;

end;

function ntsupEnumerateObjects(RootDirectory: PWideChar;
  CallbackProc: PEnumObjectsCallback; CallbackContext: PEnumObjectsContext): BOOL;
label
  ExitProc;
var
  bStop: boolean;
  dirHandle: THANDLE;
  status: NTSTATUS;
  ctx, rLength: DWORD;
  infoBuffer: POBJECT_DIRECTORY_INFORMATION;
  usDirectory: UNICODE_STRING;
  sdlen: ULONG;
  newdir, objname: PWideChar;
begin
  bStop := False;
  Result := False;
  dirHandle := 0;
  status := ntsupOpenDirectory(dirHandle, 0, RootDirectory, DIRECTORY_QUERY);

  if (not NT_SUCCESS(status)) then
    exit;

  sdlen := StrLen(RootDirectory);

  RtlInitUnicodeString(@usDirectory, OBJECT_TYPE_DIRECTORY);
  ctx := 0;

  repeat

    rLength := 0;
    status := NtQueryDirectoryObject(dirHandle, nil, 0, True, False,
      @ctx, @rLength);

    if (status <> STATUS_BUFFER_TOO_SMALL) then
      goto ExitProc;

    infoBuffer := supHeapAlloc(rLength);
    if (infoBuffer = nil) then
      break;

    status := NtQueryDirectoryObject(dirHandle, infoBuffer, rLength,
      True, False, @ctx, @rLength);

    if (not NT_SUCCESS(status)) then
    begin
      supHeapFree(infoBuffer);
      break;
    end;

    objname := supHeapAlloc((sdlen + 4) * sizeof(WCHAR) + infoBuffer^.Name.Length);
    if (objname <> nil) then
    begin

      StrCopy(objname, RootDirectory);
      if ((RootDirectory[0] = '\') and (RootDirectory[1] = #0)) then
      begin
        StrLCopy(objname + sdlen, infoBuffer^.Name.Buffer,
          infoBuffer^.Name.Length div sizeof(WCHAR));
      end
      else
      begin
        objname[sdlen] := '\';
        StrLCopy(objname + sdlen + 1, infoBuffer^.Name.Buffer,
          infoBuffer^.Name.Length div sizeof(WCHAR));
      end;

      CallbackContext^.ObjectPathName := objname;

      bStop := CallbackProc(infoBuffer, CallbackContext);

      supHeapFree(objname);
    end;


    if (RtlEqualUnicodeString(@infoBuffer^.TypeName, @usDirectory, True)) then
    begin

      newdir := supHeapAlloc((sdlen + 4) * sizeof(WCHAR) + infoBuffer^.Name.Length);
      if (newdir <> nil) then
      begin
        StrCopy(newdir, RootDirectory);
        if ((RootDirectory[0] = '\') and (RootDirectory[1] = #0)) then
        begin
          StrLCopy(newdir + sdlen, infoBuffer^.Name.Buffer,
            infoBuffer^.Name.Length div sizeof(WCHAR));
        end
        else
        begin
          newdir[sdlen] := '\';
          StrLCopy(newdir + sdlen + 1, infoBuffer^.Name.Buffer,
            infoBuffer^.Name.Length div sizeof(WCHAR));
        end;

        Result := ntsupEnumerateObjects(newdir, CallbackProc, CallbackContext);

        supHeapFree(newdir);

      end;

    end;

    supHeapFree(infoBuffer);

    if (bStop) then
      break;

  until (False);

  ExitProc:
    NtClose(dirHandle);
end;

end.
