#include "AlleyWind.h"

EXTERN_C LPTSTR apszI18NLangTable_0409[];
EXTERN_C LPTSTR apszI18NLangTable_0804[];

I18N_LANGUAGE aI18NLanguages[] = {
    {
        // en-US 0x0409
        MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT),
        {TEXT("Segoe UI"), TEXT("Tahoma"), TEXT("Arial")},
        FALSE,
        TEXT("M/d/yyyy"),
        TEXT("h:mm:ss tt"),
        &apszI18NLangTable_0409
    }, {
        // zh-CN 0x0804
        MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED), SORT_DEFAULT),
        {TEXT("Microsoft YaHei UI"), TEXT("Î¢ÈíÑÅºÚ"), TEXT("SimSun")},
        FALSE,
        TEXT("yyyy/M/d"),
        TEXT("H:mm:ss"),
        &apszI18NLangTable_0804
    }
};