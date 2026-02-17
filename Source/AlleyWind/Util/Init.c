#include "../AlleyWind.inl"

IApplicationViewCollection* g_Util_piAVC = NULL;
IVirtualDesktopManager* g_Util_piVDM = NULL;
IVirtualDesktopManagerInternal* g_Util_piVDMI_26100 = NULL;

LPIID g_Util_piidAVC = NULL;
LPIID g_Util_piidVDMI = NULL;

VOID
AW_InitUtil(VOID)
{
    HRESULT hr;
    IServiceProvider* pISP;

    hr = Shell_CreateImmersiveISP(&pISP);
    if (SUCCEEDED(hr))
    {
        Shell_CreateIApplicationViewCollection(pISP, &g_Util_piAVC, &g_Util_piidAVC);
        pISP->lpVtbl->QueryService(pISP,
                                   &CLSID_VirtualDesktopManagerInternal,
                                   &IID_IVirtualDesktopManagerInternal_26100,
                                   &g_Util_piVDMI_26100);
        pISP->lpVtbl->Release(pISP);
    }

    hr = CoCreateInstance(&CLSID_VirtualDesktopManager,
                          NULL,
                          CLSCTX_INPROC_SERVER,
                          &IID_IVirtualDesktopManager,
                          &g_Util_piVDM);
    if (FAILED(hr))
    {
        g_Util_piVDM = NULL;
    }
}

VOID
AW_UninitUtil(VOID)
{
    AW_FreeVirtDeskInfo();
    if (g_Util_piAVC != NULL)
    {
        g_Util_piAVC->lpVtbl->Release(g_Util_piAVC);
    }
    if (g_Util_piVDMI_26100 != NULL)
    {
        g_Util_piVDMI_26100->lpVtbl->Release(g_Util_piVDMI_26100);
    }
    if (g_Util_piVDM != NULL)
    {
        g_Util_piVDM->lpVtbl->Release(g_Util_piVDM);
    }
}
