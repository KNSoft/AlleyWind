// File management

#pragma once

#include "NTAssassin.h"

typedef struct _FILE_MAP {
    ACCESS_MASK         DesiredAccess;
    HANDLE              hFile;
    HANDLE              hSection;
    MEMORY_RANGE_ENTRY  Mem;
} FILE_MAP, * PFILE_MAP;

/**
  * @brief Creates or opens a file
  * @return Returns NTSTATUS
  * @see "NtCreateFile"
  */
NTA_API NTSTATUS NTAPI File_CreateW(PHANDLE lphFile, LPWSTR lpszFileName, HANDLE hRootDirectory, ACCESS_MASK DesiredAccess, ULONG ShareAccess, ULONG CreateDisposition, ULONG CreateOptions);
#ifdef UNICODE
#define File_Create File_CreateW
#else
#define File_Create File_CreateA
#endif

/**
  * @brief Verifies that a path is a valid directory
  * @param[in] lpszPath Path to be Verified
  * @param[in] lpbResult Pointer to a BOOL to receive the result
  * @return Returns NTSTATUS
  * @see "PathIsDirectory"
  */
NTA_API NTSTATUS NTAPI File_IsDirectory(LPWSTR lpszPath, PBOOL lpbResult);

/**
  * @brief Deletes specified file
  * @param[in] lpszFileName Path to the file to delete
  * @return Returns NTSTATUS
  * @see "DeleteFile"
  */
NTA_API NTSTATUS NTAPI File_DeleteW(LPWSTR lpszFileName);
#ifdef UNICODE
#define File_Delete File_DeleteW
#else
#define File_Delete File_DeleteA
#endif

/**
  * @brief Sets size of specified file
  * @param[in] hFile Handle to the file to set size
  * @param[in] NewSize New size of the file
  * @return Returns NTSTATUS
  */
NTA_API NTSTATUS NTAPI File_SetSize(HANDLE hFile, ULONGLONG NewSize);

/**
  * @brief Maps a file
  * @param[in] lpszFileName Path to the file to map
  * @param[in] lpstFileMap pointer to FILE_MAP structure to receive map information
  * @param[in] bCache Set to FALSE to disable cache when writing the map
  * @return Returns NTSTATUS
  * @see "NtCreateFile"
  */
NTA_API NTSTATUS NTAPI File_MapW(LPWSTR lpszFileName, HANDLE hRootDirectory, PFILE_MAP lpstFileMap, ULONGLONG MaximumSize, ACCESS_MASK DesiredAccess, ULONG ShareAccess, ULONG CreateDisposition, BOOL bCache, SECTION_INHERIT InheritDisposition);
#ifdef UNICODE
#define File_Map File_MapW
#else
#define File_Map File_MapA
#endif

/**
  * @brief Unmaps a file mapped by "File_Map"
  * @param[in] lpstFileMap pointer to FILE_MAP structure contains map information
  * @return Returns NTSTATUS
  */
NTA_API NTSTATUS NTAPI File_Unmap(PFILE_MAP lpstFileMap);