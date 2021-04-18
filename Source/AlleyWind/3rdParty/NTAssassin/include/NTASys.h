#pragma once

#include "NTAssassin.h"

/**
  * @brief Gets Unicode message text in specified module by message ID
  * @param[in] ModuleHandle Handle to the module
  * @param[in] MessageId ID of message
  * @return Returns Pointer to the message, or NULL if failed
  * @see "RtlFindMessage" 
  */
NTA_API PCWSTR NTAPI Sys_GetMessage(HMODULE ModuleHandle, DWORD MessageId);

/**
  * @brief Gets Unicode message text of given Win32 error or HRESULT
  * @param[in] Error Error code
  * @return Returns Pointer to the message, or NULL if failed
  */
NTA_API PCWSTR NTAPI Sys_GetErrorInfo(DWORD Error);

/**
  * @brief Gets Unicode message text of given NT Status
  * @param[in] Status NT Status
  * @return Returns Pointer to the message, or NULL if failed
  */
NTA_API PCWSTR NTAPI Sys_GetStatusInfo(NTSTATUS Status);

/**
  * @brief Gets Unicode message text of Win32 error corresponding to given NT Status
  * @param[in] Status NT Status
  * @return Returns Pointer to the message. If no Win32 error matched, returns message text of NT Status itself instead
  */
NTA_API PCWSTR NTAPI Sys_GetStatusErrorInfo(NTSTATUS Status);

/**
  * @brief Displays message box shows message text of given Win32 error or HRESULT
  * @param[in] Owner Handle to the owner window
  * @param[in] Title Title string of message box
  * @param[in] Error Error code
  */
NTA_API VOID NTAPI Sys_ErrorMsgBox(HWND Owner, PCWSTR Title, DWORD Error);

/**
  * @brief Displays message box shows message text of given NT Status
  * @param[in] Owner Handle to the owner window
  * @param[in] Title Title string of message box
  * @param[in] Status NT Status
  */
NTA_API VOID NTAPI Sys_StatusMsgBox(HWND Owner, PCWSTR Title, NTSTATUS Status);