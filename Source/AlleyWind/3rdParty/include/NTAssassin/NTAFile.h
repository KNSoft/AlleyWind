// File management

#pragma once

#include "NTAssassin.h"

typedef struct _FILE_MAP {
    ACCESS_MASK         DesiredAccess;
    HANDLE              FileHandle;
    HANDLE              SectionHandle;
    MEMORY_RANGE_ENTRY  Mem;
} FILE_MAP, * PFILE_MAP;

/**
  * @brief Creates or opens a file
  * @return Returns NTSTATUS
  * @see "NtCreateFile"
  */
NTA_API NTSTATUS NTAPI File_Create(PHANDLE FileHandle, PWSTR FileName, HANDLE RootDirectory, ACCESS_MASK DesiredAccess, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions);

/**
  * @brief Read a file
  * @return Returns NTSTATUS
  * @see "ReadFile"
  */
NTA_API NTSTATUS NTAPI File_Read(HANDLE FileHandle, PVOID Buffer, ULONG Length, PLARGE_INTEGER ByteOffset, PULONG BytesRead);

/**
  * @brief Verifies that a path is a valid directory
  * @param[in] FilePath Path to be Verified
  * @param[out] Result Pointer to a BOOL to receive the result
  * @return Returns NTSTATUS
  * @see "PathIsDirectory"
  */
NTA_API NTSTATUS NTAPI File_IsDirectory(PWSTR FilePath, PBOOL Result);

/**
  * @brief Deletes specified file
  * @param[in] FileName Path to the file to delete
  * @return Returns NTSTATUS
  * @see "DeleteFile"
  */
NTA_API NTSTATUS NTAPI File_Delete(PWSTR FileName);

/**
  * @see "NtSetInformationFile" and "FileDispositionInformation"
  */
NTA_API NTSTATUS NTAPI File_Dispose(HANDLE FileHandle, BOOL Disposition);

/**
  * @brief Sets size of specified file
  * @param[in] FileHandle Handle to the file to set size
  * @param[in] NewSize New size of the file
  * @return Returns NTSTATUS
  */
NTA_API NTSTATUS NTAPI File_SetSize(HANDLE FileHandle, ULONGLONG NewSize);

/**
  * @brief Maps a file
  * @param[in] FileName Path to the file to map
  * @param[in] RootDirectory Path to the directory as root of file
  * @param[out] FileMap pointer to FILE_MAP structure to receive map information
  * @param[in] NoCache Set to TRUE to disable cache when writing the map
  * @return Returns NTSTATUS
  * @see "NtCreateFile"
  */
NTA_API NTSTATUS NTAPI File_Map(PWSTR FileName, HANDLE RootDirectory, PFILE_MAP FileMap, ULONGLONG MaximumSize, ACCESS_MASK DesiredAccess, ULONG ShareAccess, ULONG CreateDisposition, BOOL NoCache, SECTION_INHERIT InheritDisposition);

/**
  * @brief Unmaps a file mapped by "File_Map"
  * @param[in] FileMap pointer to FILE_MAP structure contains map information
  * @return Returns NTSTATUS
  */
NTA_API NTSTATUS NTAPI File_Unmap(PFILE_MAP FileMap);