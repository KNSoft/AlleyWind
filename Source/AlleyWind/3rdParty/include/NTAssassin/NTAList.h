// Implement of two-way linked-list data structure.

#pragma once

#include "NTADef.h"

typedef struct _DATA_LIST_NODE DATA_LIST_NODE, *PDATA_LIST_NODE;

struct _DATA_LIST_NODE {
    PDATA_LIST_NODE Flink;  // Forward link, point to the next node
    PDATA_LIST_NODE Blink;  // Backward link, point to the previous node
    PVOID           Value;  // Node value
};

typedef struct _DATA_LIST {
    PDATA_LIST_NODE     First;      // Pointer to the first node
    PDATA_LIST_NODE     Last;       // Pointer to the last node
    BOOL                Lock;       // Set to TRUE to implement thread-safe
    UINT                Length;     // Number of nodes the list has
    CRITICAL_SECTION    Reserved;   // Internal lock to implement thread-safe, do not use it
} DATA_LIST, *PDATA_LIST;

/// <summary>
/// Initializes DATA_LIST structure
/// </summary>
NTA_API VOID NTAPI Data_ListInit(_Out_ PDATA_LIST DataList);

/// <summary>
/// Inserts node to the end of list
/// </summary>
/// <param name="DataList">Pointer to the DATA_LIST structure</param>
/// <param name="NodeValue">Node value to the new node to be inserted</param>
/// <returns>TRUE if succeeded, or FALSE if failed</returns>
NTA_API BOOL NTAPI Data_ListPushBack(_In_ PDATA_LIST DataList, PVOID NodeValue);

/// <summary>
/// Inserts node to the beginning of list
/// </summary>
/// <param name="DataList">Pointer to the DATA_LIST structure</param>
/// <param name="NodeValue">Node value to the new node to be inserted</param>
/// <returns>TRUE if succeeded, or FALSE if failed</returns>
NTA_API BOOL NTAPI Data_ListPushFront(_In_ PDATA_LIST DataList, PVOID NodeValue);

/// <summary>
/// Removes node in the end of list
/// </summary>
/// <param name="DataList">Pointer to the DATA_LIST structure</param>
/// <param name="NodeValue">Pointer to a buffer to receive node value to be removed</param>
/// <returns>TRUE if succeeded, or FALSE if failed</returns>
_Success_(return != FALSE) NTA_API BOOL NTAPI Data_ListPopBack(_In_ PDATA_LIST DataList, _Out_opt_ PVOID* NodeValue);

/// <summary>
/// Removes node in the beginning of list
/// </summary>
/// <param name="DataList">Pointer to the DATA_LIST structure</param>
/// <param name="NodeValue">Pointer to a buffer to receive node value to be removed</param>
/// <returns>TRUE if succeeded, or FALSE if failed</returns>
_Success_(return != FALSE) NTA_API BOOL NTAPI Data_ListPopFront(_In_ PDATA_LIST DataList, _Out_opt_ PVOID* NodeValue);

/// <summary>
/// Inserts node before specified node
/// </summary>
/// <param name="DataList">Pointer to the DATA_LIST structure</param>
/// <param name="RelNode">Pointer to DATA_LIST_NODE structure of the node relative to</param>
/// <param name="NodeValue">Node value to the new node to be inserted</param>
/// <returns>TRUE if succeeded, or FALSE if failed</returns>
NTA_API BOOL NTAPI Data_ListInsertBefore(_In_ PDATA_LIST DataList, _In_ PDATA_LIST_NODE RelNode, PVOID NodeValue);

/// <summary>
/// Inserts node after specified node
/// </summary>
/// <param name="DataList">Pointer to the DATA_LIST structure</param>
/// <param name="RelNode">Pointer to DATA_LIST_NODE structure of the node relative to</param>
/// <param name="NodeValue">Node value to the new node to be inserted</param>
/// <returns>TRUE if succeeded, or FALSE if failed</returns>
NTA_API BOOL NTAPI Data_ListInsertAfter(_In_ PDATA_LIST DataList, _In_ PDATA_LIST_NODE RelNode, PVOID NodeValue);

/// <summary>
/// Removes specified node
/// </summary>
/// <param name="DataList">Pointer to the DATA_LIST structure</param>
/// <param name="Node">Pointer to DATA_LIST_NODE structure of the node to be removed</param>
/// <returns>TRUE if succeeded, or FALSE if failed</returns>
NTA_API BOOL NTAPI Data_ListRemove(_In_ PDATA_LIST DataList, _In_ PDATA_LIST_NODE Node);

/// <summary>
/// Resets list structure
/// </summary>
/// <param name="DataList">Pointer to the DATA_LIST structure</param>
/// <param name="FreeValuePtr">Set to TRUE to frees each memory address in node value by calling <c>Mem_Free</c></param>
NTA_API VOID NTAPI Data_ListReset(_In_ PDATA_LIST DataList, BOOL FreeValuePtr);
