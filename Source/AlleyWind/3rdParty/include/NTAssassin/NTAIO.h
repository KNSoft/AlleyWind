// I/O a file or device

#pragma once

#include "NTAssassin.h"

/**
  * @brief Writes data to specified file or device
  * @return Returns NTSTATUS
  * @see "WriteFile"
  */
NTA_API NTSTATUS NTAPI IO_Write(HANDLE FileHandle, ULONGLONG ByteOffset, PVOID Buffer, ULONG Length);

/**
  * @brief Writes string to specified file or device
  * @return Returns NTSTATUS
  */
NTA_API NTSTATUS NTAPI IO_WriteStringW(HANDLE FileHandle, PWSTR String);
NTA_API NTSTATUS NTAPI IO_WriteStringA(HANDLE FileHandle, PSTR String);
#ifdef UNICODE
#define IO_WriteString IO_WriteStringW
#else
#define IO_WriteString IO_WriteStringA
#endif

/**
  * @brief Writes string to specified file or device and starts a new line
  * @return Returns NTSTATUS
  */
NTA_API NTSTATUS NTAPI IO_WriteLineW(HANDLE FileHandle, PWSTR String);
NTA_API NTSTATUS NTAPI IO_WriteLineA(HANDLE FileHandle, PSTR String);
#ifdef UNICODE
#define IO_WriteLine IO_WriteLineW
#else
#define IO_WriteLine IO_WriteLineA
#endif