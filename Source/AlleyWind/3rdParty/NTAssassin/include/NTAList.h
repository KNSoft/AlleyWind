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
    CRITICAL_SECTION    Interlock;  // Internal lock to implement thread-safe, do not use it
    UINT                Length;     // Number of nodes the list has
} DATA_LIST, * PDATA_LIST;

/**
  * @brief Initializes list structure
  * @param[in] lpstList Pointer to DATA_LIST structure to be initialized
  */
NTA_API VOID NTAPI Data_ListInit(PDATA_LIST lpstList);

/**
  * @brief Inserts node to the end of list
  * @param[in] lpstList Pointer to DATA_LIST structure
  * @param[in] lpNodeValue Node value to the new node to be inserted
  * @return Returns TRUE if succeed, otherwise returns FALSE
  */
NTA_API BOOL NTAPI Data_ListPushBack(PDATA_LIST lpstList, PVOID lpNodeValue);

/**
  * @brief Inserts node to the beginning of list
  * @param[in] lpstList Pointer to DATA_LIST structure
  * @param[in] lpNodeValue Node value to the new node to be inserted
  * @return Returns TRUE if succeed, otherwise returns FALSE
  */
NTA_API BOOL NTAPI Data_ListPushFront(PDATA_LIST lpstList, PVOID lpNodeValue);

/**
  * @brief Removes node in the end of list
  * @param[in] lpstList Pointer to DATA_LIST structure
  * @param[in] Optional, lppNodeValue Pointer to a buffer to receive node value to be removed
  * @return Returns TRUE if succeed, otherwise returns FALSE
  */
NTA_API BOOL NTAPI Data_ListPopBack(PDATA_LIST lpstList, PVOID* lppNodeValue);


/**
  * @brief Removes node in the beginning of list
  * @param[in] lpstList Pointer to DATA_LIST structure
  * @param[in] Optional, lppNodeValue Pointer to a buffer to receive node value to be removed
  * @return Returns TRUE if succeed, otherwise returns FALSE
  */
NTA_API BOOL NTAPI Data_ListPopFront(PDATA_LIST lpstList, PVOID* lppNodeValue);

/**
  * @brief Inserts node before specified node
  * @param[in] lpstList Pointer to DATA_LIST structure
  * @param[in] lpstNodeDest Pointer to DATA_LIST_NODE structure of the referenced node
  * @param[in] lpNodeValue Node value to the new node to be inserted
  * @return Returns TRUE if succeed, otherwise returns FALSE
  */
NTA_API BOOL NTAPI Data_ListInsertBefore(PDATA_LIST lpstList, PDATA_LIST_NODE lpstNodeDest, PVOID lpNodeValue);

/**
  * @brief Inserts node after specified node
  * @param[in] lpstList Pointer to DATA_LIST structure
  * @param[in] lpstNodeDest Pointer to DATA_LIST_NODE structure of the referenced node
  * @param[in] lpNodeValue Node value to the new node to be inserted
  * @return Returns TRUE if succeed, otherwise returns FALSE
  */
NTA_API BOOL NTAPI Data_ListInsertAfter(PDATA_LIST lpstList, PDATA_LIST_NODE lpstNodeDest, PVOID lpNodeValue);

/**
  * @brief Removes specified node
  * @param[in] lpstList Pointer to DATA_LIST structure
  * @param[in] lpstNode Pointer to DATA_LIST_NODE structure of the node to be removed
  * @param[in] Optional, lppNodeValue Pointer to a buffer to receive node value to be removed
  * @return Returns TRUE if succeed, otherwise returns FALSE
  */
NTA_API BOOL NTAPI Data_ListRemove(PDATA_LIST lpstList, PDATA_LIST_NODE lpstNode, PVOID lpNodeValue);

/**
  * @brief Resets list structure
  * @param[in] lpstList Pointer to DATA_LIST structure to be initialized
  * @param[in] bFreeValuePtr Set to TRUE to free each memory pointed by node value
  */
NTA_API VOID NTAPI Data_ListReset(PDATA_LIST lpstList, BOOL bFreeValuePtr);