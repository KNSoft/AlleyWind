// Error handling

#pragma once

#include "NTADef.h"
#include "NTANT.h"

/// <summary>
/// Gets or sets the last error
/// </summary>
#define EH_ClearLastError() NT_SetTEBMemberDWORD(LastErrorValue, ERROR_SUCCESS)
#define EH_GetLastError() NT_GetTEBMemberDWORD(LastErrorValue)
#define EH_SetLastError(Error) NT_SetTEBMemberDWORD(LastErrorValue, Error)
#define EH_LastErrorSucceed() (NT_GetTEBMemberDWORD(LastErrorValue) == ERROR_SUCCESS)

/// <summary>
/// Gets or sets the last status
/// </summary>
#define EH_ClearLastStatus() NT_SetTEBMemberDWORD(LastStatusValue, STATUS_SUCCESS)
#define EH_GetLastStatus() ((NTSTATUS)(NT_GetTEBMemberDWORD(LastStatusValue)))
#define EH_SetLastStatus(Status) NT_SetTEBMemberDWORD(LastStatusValue, Status)
#define EH_LastStatusSucceed() (NT_SUCCESS(NT_GetTEBMemberDWORD(LastStatusValue)))

/// <summary>
/// Sets last win32 error according to given NT Status
/// </summary>
/// <param name="Status">NT Status</param>
/// <returns>Win32 Error code corresponding to the given NT Status</returns>
NTA_API DWORD NTAPI EH_SetLastNTError(NTSTATUS Status);

/// <summary>
/// Gets Unicode message text of given Win32 error or HRESULT
/// </summary>
/// <param name="Error">Error code</param>
/// <returns>Pointer to the message string, or NULL if failed</returns>
NTA_API PCWSTR NTAPI EH_GetErrorInfo(DWORD Error);

/// <summary>
/// Gets Unicode message text of given NT Status
/// </summary>
/// <param name="Status">NT Status</param>
/// <returns>Pointer to the message string, or NULL if failed</returns>
NTA_API PCWSTR NTAPI EH_GetStatusInfo(NTSTATUS Status);

/// <summary>
/// Gets Unicode message text of Win32 error corresponding to given NT Status
/// </summary>
/// <param name="Status">NT Status</param>
/// <returns>Pointer to the message. If no Win32 error matched, returns message text of NT Status itself instead</returns>
NTA_API PCWSTR NTAPI EH_GetStatusErrorInfo(NTSTATUS Status);

/// <summary>
/// Displays message box shows message text of given Win32 error or HRESULT
/// </summary>
/// <param name="Owner">Handle to the owner window</param>
/// <param name="Title">Title string of message box</param>
/// <param name="Error">Error code</param>
NTA_API VOID NTAPI EH_ErrorMsgBox(HWND Owner, PCWSTR Title, DWORD Error);

/// <summary>
/// Displays message box shows message text of given NT Status
/// </summary>
/// <param name="Owner">Handle to the owner window</param>
/// <param name="Title">Title string of message box</param>
/// <param name="Status">NT Status</param>
NTA_API VOID NTAPI EH_StatusMsgBox(HWND Owner, PCWSTR Title, NTSTATUS Status);

/// <seealso cref="EH_GetErrorInfo"/>
#define EH_GetLastErrorInfo() EH_GetErrorInfo(EH_GetLastError())

/// <seealso cref="EH_GetStatusInfo"/>
#define EH_GetLastStatusInfo() EH_GetStatusInfo(EH_GetLastStatus())

/// <seealso cref="EH_ErrorMsgBox"/>
#define EH_LastErrorMsgBox(Owner, Title) EH_ErrorMsgBox(Owner, Title, EH_GetLastError())

/// <seealso cref="EH_StatusMsgBox"/>
#define EH_LastStatusMsgBox(Owner, Title) EH_StatusMsgBox(Owner, Title, EH_GetLastStatus())

// Error code converts
NTA_API DWORD NTAPI EH_HrToWin32(HRESULT hr);
#define EH_Win32ToHr HRESULT_FROM_WIN32
#define EH_StatusToWin32 RtlNtStatusToDosErrorNoTeb
#define EH_StatusToHr HRESULT_FROM_NT
