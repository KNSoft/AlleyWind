// File management

#pragma once

#include "NTAssassin.h"

typedef struct _FILE_MAP {
    ACCESS_MASK         DesiredAccess;
    HANDLE              FileHandle;
    HANDLE              SectionHandle;
    MEMORY_RANGE_ENTRY  Mem;
} FILE_MAP, *PFILE_MAP;

/// <summary>
/// Creates or open a file
/// </summary>
/// <seealso cref="NtCreateFile"/>
/// <returns>Handle to the file, or NULL if failed, error code storaged in last STATUS</returns>
NTA_API HANDLE NTAPI File_Create(_In_z_ PCWSTR FileName, HANDLE RootDirectory, ACCESS_MASK DesiredAccess, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions);

/// <summary>
/// Reads a file
/// </summary>
/// <seealso cref="NtReadFile"/>
/// <returns>Number of bytes read</returns>
NTA_API ULONG NTAPI File_Read(HANDLE FileHandle, _In_ PVOID Buffer, ULONG BytesToRead, PLARGE_INTEGER ByteOffset);

/// <summary>
/// Verifies that a path is a valid directory
/// </summary>
/// <seealso cref="PathIsDirectory"/>
/// <param name="FilePath">Path to be verified</param>
/// <param name="Result">Pointer to a BOOL to receive the result</param>
/// <returns>TRUE if succeeded, or FALSE if failed, error code storaged in last STATUS</returns>
_Success_(return == TRUE) NTA_API BOOL NTAPI File_IsDirectory(_In_z_ PCWSTR FilePath, _Out_ PBOOL Result);

/// <summary>
/// Deletes a file
/// </summary>
/// <param name="FileName">Path to the file to delete</param>
/// <returns>TRUE if succeeded, or FALSE if failed, error code storaged in last STATUS</returns>
NTA_API BOOL NTAPI File_Delete(_In_z_ PCWSTR FilePath);

/// <summary>
/// Marks a file should be deleted when closed
/// </summary>
/// <param name="FileHandle">Handle to the file</param>
/// <returns>TRUE if succeeded, or FALSE if failed, error code storaged in last STATUS</returns>
NTA_API BOOL NTAPI File_Dispose(HANDLE FileHandle);

/// <summary>
/// Sets size of specified file
/// </summary>
/// <param name="FileHandle">Handle to the file</param>
/// <param name="NewSize">New size of the file</param>
/// <returns>TRUE if succeeded, or FALSE if failed, error code storaged in last STATUS</returns>
NTA_API BOOL NTAPI File_SetSize(HANDLE FileHandle, ULONGLONG NewSize);

/// <summary>
/// Maps a file
/// </summary>
/// <seealso cref="NtCreateFile"/>
/// <seealso cref="MapViewOfFile"/>
/// <param name="FileName">Path to the file to map</param>
/// <param name="RootDirectory">Handle to the directory as root of file</param>
/// <param name="FileMap">Pointer to a FILE_MAP structure to receive map information</param>
/// <param name="MaximumSize"></param>
/// <param name="DesiredAccess"></param>
/// <param name="ShareAccess"></param>
/// <param name="CreateDisposition"></param>
/// <param name="NoCache">Set to TRUE to disable cache when writing the map</param>
/// <param name="InheritDisposition"></param>
/// <returns>TRUE if succeeded, or FALSE if failed, error code storaged in last STATUS</returns>
_Success_(return == TRUE) NTA_API BOOL NTAPI File_Map(_In_z_ PCWSTR FileName, HANDLE RootDirectory, _Out_ PFILE_MAP FileMap, ULONGLONG MaximumSize, ACCESS_MASK DesiredAccess, ULONG ShareAccess, ULONG CreateDisposition, BOOL NoCache, SECTION_INHERIT InheritDisposition);

/// <summary>
/// Unmaps a file mapped by "File_Map"
/// </summary>
/// <param name="FileMap">Pointer to a FILE_MAP structure contains map information</param>
/// <returns>TRUE if succeeded, or FALSE if failed, error code storaged in last STATUS</returns>
NTA_API BOOL NTAPI File_Unmap(_In_ PFILE_MAP FileMap);
