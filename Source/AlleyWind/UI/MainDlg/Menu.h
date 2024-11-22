#pragma once

#include "../../AlleyWind.inl"

#define IDM_FILE_RUNAS_ADMIN 1
#define IDM_FILE_REFRESH 2
#define IDM_FILE_SAVETREE 3

#define IDM_HELP_HOMEPAGE 20

#define IDM_ITEM_HIGHLIGHT 101
#define IDM_ITEM_PROPERTIES 102

EXTERN_C_START

VOID
MainDlgCreateMenu(
    _Outptr_result_maybenull_ HMENU* MainMenu,
    _Outptr_result_maybenull_ HMENU* ItemMenu);

VOID
MainDlgDestroyMenu(
    _In_opt_ HMENU MainMenu,
    _In_opt_ HMENU ItemMenu);

HACCEL
MainDlgCreateAccelerator(VOID);

EXTERN_C_END
