// Implement of two-way linked-list data structure.

#pragma once

#include "NTAssassin.h"

typedef struct _DATA_LIST_NODE DATA_LIST_NODE, * PDATA_LIST_NODE;

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
} DATA_LIST, * PDATA_LIST;

/**
  * @brief Initializes list structure
  * @param[in] DataList Pointer to DATA_LIST structure to be initialized
  */
NTA_API VOID NTAPI Data_ListInit(PDATA_LIST DataList);

/**
  * @brief Inserts node to the end of list
  * @param[in] DataList Pointer to DATA_LIST structure
  * @param[in] NodeValue Node value to the new node to be inserted
  * @return Returns TRUE if succeed, otherwise returns FALSE
  */
NTA_API BOOL NTAPI Data_ListPushBack(PDATA_LIST DataList, PVOID NodeValue);

/**
  * @brief Inserts node to the beginning of list
  * @param[in] DataList Pointer to DATA_LIST structure
  * @param[in] NodeValue Node value to the new node to be inserted
  * @return Returns TRUE if succeed, otherwise returns FALSE
  */
NTA_API BOOL NTAPI Data_ListPushFront(PDATA_LIST DataList, PVOID NodeValue);

/**
  * @brief Removes node in the end of list
  * @param[in] DataList Pointer to DATA_LIST structure
  * @param[out, opt] NodeValuePointer Pointer to a buffer to receive node value to be removed
  * @return Returns TRUE if succeed, otherwise returns FALSE
  */
NTA_API BOOL NTAPI Data_ListPopBack(PDATA_LIST DataList, PVOID* NodeValuePointer);


/**
  * @brief Removes node in the beginning of list
  * @param[in] DataList Pointer to DATA_LIST structure
  * @param[out, opt] NodeValuePointer Pointer to a buffer to receive node value to be removed
  * @return Returns TRUE if succeed, otherwise returns FALSE
  */
NTA_API BOOL NTAPI Data_ListPopFront(PDATA_LIST DataList, PVOID* NodeValuePointer);

/**
  * @brief Inserts node before specified node
  * @param[in] DataList Pointer to DATA_LIST structure
  * @param[in] DestNode Pointer to DATA_LIST_NODE structure of the referenced node
  * @param[in] NodeValue Node value to the new node to be inserted
  * @return Returns TRUE if succeed, otherwise returns FALSE
  */
NTA_API BOOL NTAPI Data_ListInsertBefore(PDATA_LIST DataList, PDATA_LIST_NODE DestNode, PVOID NodeValue);

/**
  * @brief Inserts node after specified node
  * @param[in] DataList Pointer to DATA_LIST structure
  * @param[in] DestNode Pointer to DATA_LIST_NODE structure of the referenced node
  * @param[in] NodeValue Node value to the new node to be inserted
  * @return Returns TRUE if succeed, otherwise returns FALSE
  */
NTA_API BOOL NTAPI Data_ListInsertAfter(PDATA_LIST DataList, PDATA_LIST_NODE DestNode, PVOID NodeValue);

/**
  * @brief Removes specified node
  * @param[in] DataList Pointer to DATA_LIST structure
  * @param[in] Node Pointer to DATA_LIST_NODE structure of the node to be removed
  * @return Returns TRUE if succeed, otherwise returns FALSE
  */
NTA_API BOOL NTAPI Data_ListRemove(PDATA_LIST DataList, PDATA_LIST_NODE Node);

/**
  * @brief Resets list structure
  * @param[in] DataList Pointer to DATA_LIST structure to be initialized
  * @param[in] FreeValuePtr Set to TRUE to free each memory pointed by node value
  */
NTA_API VOID NTAPI Data_ListReset(PDATA_LIST DataList, BOOL FreeValuePtr);