// I18N support

#pragma once

#include "NTAssassin.h"

typedef struct _I18N_ITEMW {
    DWORD   KeyHash;
    LPCWSTR Value;
} I18N_ITEMW, * PI18N_ITEMW;

#ifdef UNICODE
typedef I18N_ITEMW I18N_ITEM;
typedef PI18N_ITEMW PI18N_ITEM;
#else
typedef I18N_ITEMA I18N_ITEM;
typedef PI18N_ITEMA PI18N_ITEM;
#endif

typedef struct _I18N_LANGUAGEW I18N_LANGUAGEW, * PI18N_LANGUAGEW;

struct _I18N_LANGUAGEW {
    QWORD           Name[3];        // Each parts of name
    PI18N_LANGUAGEW Parent;         // Pointer to parent
    LPWSTR          NativeName;     // Native name
    LPWSTR          FontName;       // Font name prefered
    BOOL            RTLReading;     // Set to TRUE if the language has RTL reading order
    PI18N_ITEMW     StringTable;    // Pointer to the string table
};

typedef struct _I18N_TEXTCTL {
    INT         nCtlID;
    UINT_PTR    uString;
} I18N_TEXTCTL, * PI18N_TEXTCTL;

#ifdef UNICODE
typedef I18N_LANGUAGEW I18N_LANGUAGE;
typedef PI18N_LANGUAGEW PI18N_LANGUAGE;
#else
typedef I18N_LANGUAGEA I18N_LANGUAGE;
typedef PI18N_LANGUAGEA PI18N_LANGUAGE;
#endif

NTA_API PI18N_LANGUAGEW NTAPI I18N_InitExW(PI18N_LANGUAGEW *lpLanguages, UINT nLanguages, USHORT nItems, LPCWSTR lpszLangName);
#ifdef UNICODE
#define I18N_InitEx I18N_InitExW
#else
#define I18N_InitEx I18N_InitExA
#endif

/**
  * @brief Gets string by specified index in string table
  * @param[in] iString Index of the string in string table
  * @return Returns pointer to the string
  */
NTA_API LPCWSTR NTAPI I18N_GetStringW(UINT_PTR uIndex);
#ifdef UNICODE
#define I18N_GetString I18N_GetStringW
#else
#define I18N_GetString I18N_GetStringA
#endif

/**
  * @brief Creates a logical font with I18N prefered name and specified size and weight, see also "CreateFont"
  * @see "CreateFont"
  * @return Returns handle to a logical font, or NULL if failed
  */
NTA_API HFONT NTAPI I18N_CreateFontW(INT iFontSize, INT iFontWeight);
#ifdef UNICODE
#define I18N_CreateFont I18N_CreateFontW
#else
#define I18N_CreateFont I18N_CreateFontA
#endif

/**
  * @brief Sets window text by specified I18N string index
  */
#define I18N_SetWndTextW(hCtl, uString) SendMessageW(hCtl, WM_SETTEXT, 0, (LPARAM)I18N_GetStringW(uString))
#ifdef UNICODE
#define I18N_SetWndText I18N_SetWndTextW
#else
#define I18N_SetWndText I18N_SetWndTextA
#endif

/**
  * @brief Sets a dialogue item text by specified I18N string index
  */
#define I18N_SetDlgItemTextW(hDlg, nIDItem, uString) SendMessageW(GetDlgItem(hDlg, nIDItem), WM_SETTEXT, 0, (LPARAM)I18N_GetStringW(uString))
#ifdef UNICODE
#define I18N_SetDlgItemText I18N_SetDlgItemTextW
#else
#define I18N_SetDlgItemText I18N_SetDlgItemTextA
#endif

/**
  * @brief Initializes window text by specified I18N string index
  */
NTA_API HWND NTAPI I18N_InitTextCtlW(HWND hDlg, INT nCtlID, UINT_PTR uString);
#ifdef UNICODE
#define I18N_InitTextCtl I18N_InitTextCtlW
#else
#define I18N_InitTextCtl I18N_InitTextCtlA
#endif

/**
  * @brief Sets windows text by specified I18N string indexes
  */
NTA_API VOID NTAPI I18N_InitTextCtlsExW(HWND hDlg, PI18N_TEXTCTL lpstTextCtls, UINT uCount);
#define I18N_InitTextCtlsW(hDlg, lpstTextCtls) I18N_InitTextCtlsExW(hDlg, lpstTextCtls, ARRAYSIZE(lpstTextCtls))
#ifdef UNICODE
#define I18N_InitTextCtlsEx I18N_InitTextCtlsExW
#define I18N_InitTextCtls I18N_InitTextCtlsW
#else
#define I18N_InitTextCtlsEx I18N_InitTextCtlsExA
#define I18N_InitTextCtls I18N_InitTextCtlsA
#endif

PI18N_LANGUAGEW I18N_FindLangExW(PI18N_LANGUAGEW *lpLangs, UINT uCount, LPCWSTR lpszName);
#define I18N_FindLangW(lpszName) I18N_FindLangExW(NAC_I18N_Lang_Table, ARRAYSIZE(NAC_I18N_Lang_Table), lpszName)
#define I18N_FindLangA(lpszName) I18N_FindLangExA(NAC_I18N_Lang_Table, ARRAYSIZE(NAC_I18N_Lang_Table), lpszName)
#ifdef UNICODE
#define I18N_FindLang I18N_FindLangW
#else
#define I18N_FindLang I18N_FindLangA
#endif

VOID NTAPI I18N_SetLocaleW(PI18N_LANGUAGE lpstLang);
#ifdef UNICODE
#define I18N_SetLocale I18N_SetLocaleW
#else
#define I18N_SetLocale I18N_SetLocaleA
#endif