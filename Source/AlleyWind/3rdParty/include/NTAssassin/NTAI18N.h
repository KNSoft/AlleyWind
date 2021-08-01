// I18N support, used with NAC is recommanded

#pragma once

#include "NTAssassin\NTAssassin.h"

typedef struct _I18N_ITEM {
    DWORD   KeyHash;
    LPCWSTR Value;
} I18N_ITEM, * PI18N_ITEM;

typedef struct _I18N_LANGUAGE I18N_LANGUAGE, * PI18N_LANGUAGE;

struct _I18N_LANGUAGE {
    QWORD           Name[3];        // Each parts of name
    LCID            dwLangId;       // LCID
    PI18N_LANGUAGE  Parent;         // Pointer to parent
    LPWSTR          NativeName;     // Native name
    LPWSTR          FontName;       // Font name prefered
    BOOL            RTLReading;     // Set to TRUE if the language has RTL reading order
    PI18N_ITEM      StringTable;    // Pointer to the string table
};

typedef struct _I18N_CTLTEXT {
    INT         CtlID;
    UINT_PTR    StrIndex;
} I18N_CTLTEXT, * PI18N_CTLTEXT;

NTA_API PI18N_LANGUAGE NTAPI I18N_InitEx(PI18N_LANGUAGE *Langs, UINT LangCount, USHORT ItemCount, PCWSTR LangName);
#define I18N_Init(LangName) I18N_InitEx(NAC_I18N_Lang_Table, ARRAYSIZE(NAC_I18N_Lang_Table), NAC_I18N_ITEM_COUNT, LangName)

VOID NTAPI I18N_SetLocale(PI18N_LANGUAGE Lang);

PI18N_LANGUAGE I18N_FindLangEx(PI18N_LANGUAGE *lpLangs, UINT uCount, PCWSTR lpszName);
#define I18N_FindLang(lpszName) I18N_FindLangExW(NAC_I18N_Lang_Table, ARRAYSIZE(NAC_I18N_Lang_Table), lpszName)

/**
  * @brief Gets string by specified index or hash in string table
  * @param[in] Index Index or hash value of the string in string table
  * @return Returns pointer to the string
  */
NTA_API PCWSTR NTAPI I18N_GetString(UINT_PTR StrIndex);

/**
  * @brief Creates a logical font with I18N prefered name and specified size and weight, see also "CreateFont"
  * @see "CreateFont"
  * @return Returns handle to a logical font, or NULL if failed
  */
NTA_API HFONT NTAPI I18N_CreateFont(INT FontSize, INT FontWeight);

/**
  * @brief Sets window text by specified I18N string index
  */
#define I18N_SetWndText(Window, StrIndex) SendMessageW(Window, WM_SETTEXT, 0, (LPARAM)I18N_GetString(StrIndex))

/**
  * @brief Sets a dialogue item text by specified I18N string index
  */
#define I18N_SetDlgItemText(Dialog, ItemId, StrIndex) I18N_SetWndText(GetDlgItem(Dialog, ItemId), StrIndex)

/**
  * @brief Initializes window text by specified I18N string index
  */
NTA_API HWND NTAPI I18N_InitCtlText(HWND Dialog, INT CtlID, UINT_PTR StrIndex);

/**
  * @brief Sets windows text by specified I18N string indexes
  */
NTA_API VOID NTAPI I18N_InitCtlTextsEx(HWND Dialog, PI18N_CTLTEXT CtlTexts, UINT CtlTextCount);
#define I18N_InitCtlTexts(Dialog, CtlTexts) I18N_InitCtlTextsEx(Dialog, CtlTexts, ARRAYSIZE(CtlTexts))