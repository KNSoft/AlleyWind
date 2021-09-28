typedef enum _AW_SETTING_INDEX {
    AWSetting_ResponseTimeout
} AW_SETTING_INDEX, * PAW_SETTING_INDEX;

VOID AWSettings_Init();
DWORD AWSettings_GetItemValueEx(INT Index);