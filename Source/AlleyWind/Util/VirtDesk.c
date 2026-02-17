#include "../AlleyWind.inl"

static RTL_SRWLOCK g_lockInfo = RTL_SRWLOCK_INIT;
static PAW_VIRTDESK_INFO g_pInfo = NULL;
static ULONG g_cInfo = 0;

static
VOID
FreeVirtDeskInfo(
    _In_reads_(Count) PAW_VIRTDESK_INFO Info,
    _In_ ULONG Count)
{
    for (ULONG i = 0; i < Count; i++)
    {
        if (SUCCEEDED(Info[i].hrName))
        {
            _Inline_WindowsDeleteString(Info[i].Name);
        }
    }
    Mem_Free(Info);
}

static
HRESULT
AW_UpdateVirtDeskInfo(VOID)
{
    HRESULT hr;
    IObjectArray* Desktops;
    UINT Count, i;
    PAW_VIRTDESK_INFO pInfo, pTemp;
    IVirtualDesktop* Desktop;

    if (g_Util_piVDMI_26100 == NULL)
    {
        return E_NOINTERFACE;
    }

    hr = g_Util_piVDMI_26100->lpVtbl->GetDesktops(g_Util_piVDMI_26100, &Desktops);
    if (FAILED(hr))
    {
        return hr;
    }
    hr = Desktops->lpVtbl->GetCount(Desktops, &Count);
    if (FAILED(hr))
    {
        goto _Exit;
    }
    pInfo = Mem_Alloc(Count * sizeof(AW_VIRTDESK_INFO));
    if (pInfo == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto _Exit;
    }

    for (i = 0; i < Count; i++)
    {
        pInfo[i].Index = i;
        hr = Desktops->lpVtbl->GetAt(Desktops, i, &IID_IVirtualDesktop, &Desktop);
        if (FAILED(hr))
        {
            pInfo[i].hrId = pInfo[i].hrName = hr;
            continue;
        }
        pInfo[i].hrId = Desktop->lpVtbl->GetId(Desktop, &pInfo[i].Id);
        if (IS_NT_VERSION_GE(NT_VERSION_WIN11_22H2))
        {
            pInfo[i].hrName = Desktop->lpVtbl->GetName(Desktop, &pInfo[i].Name);
        } else
        {
            pInfo[i].hrName = E_NOINTERFACE;
        }
        Desktop->lpVtbl->Release(Desktop);
    }

    RtlAcquireSRWLockExclusive(&g_lockInfo);
    i = g_cInfo;
    g_cInfo = Count;
    pTemp = g_pInfo;
    g_pInfo = pInfo;
    RtlReleaseSRWLockExclusive(&g_lockInfo);
    FreeVirtDeskInfo(pTemp, i);
    hr = S_OK;

_Exit:
    Desktops->lpVtbl->Release(Desktops);
    return hr;
}

HRESULT
AW_EnumVirtualDesktops(
    _In_ PAW_VIRTDESK_ENUM_PROC Callback,
    _In_opt_ PVOID Context)
{
    HRESULT hr;
    ULONG i;

    hr = AW_UpdateVirtDeskInfo();
    if (FAILED(hr))
    {
        return hr;
    }

    RtlAcquireSRWLockShared(&g_lockInfo);
    for (i = 0; i < g_cInfo; i++)
    {
        if (!Callback(&g_pInfo[i], Context))
        {
            break;
        }
    }
    hr = i == g_cInfo ? S_OK : S_FALSE;
    RtlReleaseSRWLockShared(&g_lockInfo);

    return hr;
}

VOID
AW_FreeVirtDeskInfo(VOID)
{
    RtlAcquireSRWLockExclusive(&g_lockInfo);
    FreeVirtDeskInfo(g_pInfo, g_cInfo);
    RtlReleaseSRWLockExclusive(&g_lockInfo);
}
