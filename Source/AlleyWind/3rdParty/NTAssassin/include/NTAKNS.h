// KNSoft application framework, do not use

#pragma once

#include "NTAssassin.h"

#define KNS_VERSION_ALPHA 1
#define KNS_VERSION_BETA 2
#define KNS_VERSION_RC 3
#define KNS_VERSION_GA 4
#define KNS_VERSION_RELEASE 5

#define KNS_DIALOG_DEFAULT_FONTSIZE 18

#define KNS_BANNER_MARGIN 8
#define KNS_BANNER_FONTBIG_SCALE 1 / 2
#define KNS_BANNER_FONTSMALL_SCALE 2 / 5
#define KNS_BANNER_ICON_SCALE 3 / 5

#define ICON_SIDE   48

typedef struct _KNS_VERSION_INFO {
    USHORT  Major;
    USHORT  Minor;
    USHORT  Revision;
    USHORT  Build;
    USHORT  Type;   // KNS_VERSION_*
} KNS_VERSION_INFO, * PKNS_VERSION_INFO;

typedef struct _KNS_I18NMENU KNS_I18NMENU, * PKNS_I18NMENU;

struct _KNS_I18NMENUW {
    UINT        uFlags;
    UINT_PTR    uID;
    UINT        uI18NText;
    KNS_I18NMENU(*SubMenu)[ANYSIZE_ARRAY];
    UINT        cSubMenu;
};

typedef struct _KNS_INFO {
    PWSTR               Name;           // Name of software
    BOOL                KNSOfficial;    // Is official software of KNSoft
    KNS_VERSION_INFO    Version;
    struct {
        COLORREF    MainColor;      // Main color to draw splash, banner, etc.
        UINT        IconResID;      // Main icon resource to draw splash, banner, etc.
        UINT        DlgResID;       // Main dialog resource template
        DLGPROC     DlgProc;        // Main dialog callback function
        UINT        BannerCtlID;    // ID of static control for banner on main dialog
        UINT        SplashResID;    // ID of splash image resource
        UINT        SplashDuration; // Splash timeout, or no splash if it's null
        BOOL        SplashAsync;    // Display splash asynchronously or not
    } UI;
    struct {
        PI18N_LANGUAGE  *Langs;
        UINT            LangCount;
        USHORT          ItemCount;
    } I18N;
    struct {
        PWSTR   HomePage;        // URL to Homepage
        PWSTR   HelpDoc;         // URL or path to help content
        PWSTR   KNSUpdateSrv;    // URL to KNSoft Update Service
        PWSTR   KNSBugRptSrv;    // URL to KNSoft Bug Report Service
    } OnlineService;
} KNS_INFO, * PKNS_INFO;

typedef struct _KNS_SUBCLASS_BANNER_REFW {
    HWND        hStatic;
    LONG        lWidth;
    LONG        lHeight;
    HICON       hIcon;
    LONG        lIconHotspot;
    HFONT       hFontBig;
    HFONT       hFontSmall;
    LPCWSTR     lpszName;
    LPCWSTR     lpszComment;
} KNS_SUBCLASS_BANNER_REFW, * PKNS_SUBCLASS_BANNER_REFW;

NTA_API INT_PTR NTAPI KNS_Startup(PKNS_INFO KNSInfo);

NTA_API INT NTAPI KNS_MsgBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType);
#ifdef UNICODE
#define KNS_MsgBox KNS_MsgBoxW
#else
#define KNS_MsgBox KNS_MsgBoxA
#endif

NTA_API BOOL NTAPI KNS_GetVersionStringEx(PWSTR StrVersion, UINT ChCount);
#define KNS_GetVersionString(StrVersion) KNS_GetVersionStringEx(StrVersion, ARRAYSIZE(StrVersion))

NTA_API HICON NTAPI KNS_GetIcon();

NTA_API VOID NTAPI KNS_SetDialogSubclass(HWND Dialog, DLG_RESIZEDPROC ResizedProc);

NTA_API VOID NTAPI KNS_DlgAbout(HWND hwndOwner);