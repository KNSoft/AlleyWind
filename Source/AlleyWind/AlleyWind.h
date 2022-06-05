#pragma once

#define NTA_CUSTOMENTRY "Main"
#include "NTAssassin\NTAssassin.h"
#include "Precomp4C.Output.h"

#include <Uxtheme.h>

#include "DB_StyleEditor.h"
#include "DB_Message.h"
#include "AWSettings.h"
#include "AWWndIO.h"
#include "AWWndProp.h"
#include "resource.h"

#if _DEBUG
#if _WIN64
#pragma comment(lib, "x64\\Debug\\NTAssassin.lib")
#else
#pragma comment(lib, "x86\\Debug\\NTAssassin.lib")
#endif
#else
#if _WIN64
#pragma comment(lib, "x64\\Release\\NTAssassin.lib")
#else
#pragma comment(lib, "x86\\Release\\NTAssassin.lib")
#endif
#endif

#pragma comment(lib, "UxTheme.lib")

#define KNS_NAME TEXT("AlleyWind")

#define MAX_WNDCAPTION_CCH 128

INT_PTR WINAPI MainDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR WINAPI FindWndDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK CaptureWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK PickColorWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT_PTR WINAPI WndPropGeneralDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR WINAPI WndPropResourceDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR WINAPI WndPropRelationshipDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR WINAPI WndPropClassDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR WINAPI WndPropOperationDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR WINAPI WndPropMessageDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND AW_GetMainDlg();

VOID AWDatabaseInit();

VOID FindWndInit();
VOID FindWndUninit();

VOID WndPropRelationshipInit();
VOID WndPropRelationshipUninit();
VOID WndPropResourceInit();
VOID WndPropResourceUninit();
VOID WndPropOperationInit();
VOID WndPropOperationUninit();

INT_PTR WINAPI WndPropDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
DWORD WINAPI OpenWndPropDlgThread(PVOID lParam);

BOOL AW_LoadWindowTreeAsync(BOOL bUpdateFilter, LPTSTR lpszCaption, LPTSTR lpszClassName);
BOOL AW_LocateWindowInTree(HWND hWnd);
VOID AW_OpenWndPropDlg(HWND hWnd);
VOID AW_OpenFindWndDlg(HWND hDlg);