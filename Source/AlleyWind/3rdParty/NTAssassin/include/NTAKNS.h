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

typedef struct _KNS_I18NMENUW KNS_I18NMENUW, * PKNS_I18NMENUW;

struct _KNS_I18NMENUW {
    UINT        uFlags;
    UINT_PTR    uID;
    UINT        uI18NText;
    KNS_I18NMENUW(*SubMenu)[ANYSIZE_ARRAY];
    UINT        cSubMenu;
};

#ifdef UNICODE
#define KNS_I18NMENU KNS_I18NMENUW
#define PKNS_I18NMENU PKNS_I18NMENUW
#else
#define KNS_I18NMENU KNS_I18NMENUA
#define PKNS_I18NMENU PKNS_I18NMENUA
#endif

typedef struct _KNS_INFOW {
    LPWSTR              Name;           // Name of software
    BOOL                KNSOfficial;    // Is official software of KNSoft
    KNS_VERSION_INFO    Version;
    struct {
        COLORREF    MainColor;      // Main color to draw splash, banner, etc.
        UINT        IconResID;      // Main icon resource to draw splash, banner, etc.
        struct {
            UINT            ResID;  // Main dialog resource template
            DLGPROC         Proc;   // Main dialog callback function
        } Dialog;
        struct {
            UINT    CtlID;         // ID of static control for banner on main dialog
            struct {
                DWORD HasIcon : 1;
                DWORD HasVersion : 1;
                DWORD ReservedBits : 30;
            };
        } Banner;
        struct {
            LPWSTR  ResName;        // Splash image resource, or use default splash if it's null
            UINT    Duration;       // Splash timeout, or no splash if it's null
            BOOL    Async;          // Splash is async or not
        } Splash;
        struct {
            UINT            LangCount;
            PI18N_LANGUAGE  *LangTable;
            USHORT          StringCount;
        } I18N;
    } UI;
    struct {
        LPWSTR  HomePage;        // URL to Homepage
        LPWSTR  KNSUpdateSrv;    // URL to KNSoft Update Service
        LPWSTR  KNSBugRptSrv;    // URL to KNSoft Bug Report Service
    } OnlineService;
} KNS_INFOW, * PKNS_INFOW;

typedef struct _KNS_SUBCLASS_DIALOG_REF {
    HWND        hDlg;
    LONG        lInitWidth;
    LONG        lInitHeight;
    LONG        lStyle;
    UI_DPIINFO  stDPIInfo;
    UINT        uFontSize;
    HFONT       hFont;
} KNS_SUBCLASS_DIALOG_REF, * PKNS_SUBCLASS_DIALOG_REF;

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

#ifdef UNICODE
typedef KNS_INFOW KNS_INFO;
typedef PKNS_INFOW PKNS_INFO;
#else
typedef KNS_INFOA KNS_INFO;
typedef PKNS_INFOA PKNS_INFO;
#endif

NTA_API INT_PTR NTAPI KNS_StartupW(PKNS_INFOW lpstKNSInfo);
#ifdef UNICODE
#define KNS_Startup KNS_StartupW
#else
#define KNS_Startup KNS_StartupA
#endif

NTA_API INT NTAPI KNS_MsgBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType);
#ifdef UNICODE
#define KNS_MsgBox KNS_MsgBoxW
#else
#define KNS_MsgBox KNS_MsgBoxA
#endif

NTA_API BOOL NTAPI KNS_GetVersionStringExW(LPWSTR lpszVersion, UINT cchMax);
#ifdef UNICODE
#define KNS_GetVersionStringW(lpszVersion) KNS_GetVersionStringExW(lpszVersion, ARRAYSIZE(lpszVersion))
#define KNS_GetVersionStringEx KNS_GetVersionStringExW
#define KNS_GetVersionString KNS_GetVersionStringW
#else
#define KNS_GetVersionStringA(lpszVersion) KNS_GetVersionStringExA(lpszVersion, ARRAYSIZE(lpszVersion))
#define KNS_GetVersionStringEx KNS_GetVersionStringExA
#define KNS_GetVersionString KNS_GetVersionStringA
#endif

NTA_API HICON NTAPI KNS_GetIcon();

NTA_API VOID NTAPI KNS_DialogSetSubclass(HWND hDlg);

NTA_API VOID NTAPI KNS_DlgAbout(HWND hwndOwner);