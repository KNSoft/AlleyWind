#pragma once

// NTA_DLL
// 0-lib 1-dll
#if !defined(NTA_DLL)
#define NTA_DLL 0
#endif

// NTA_CUSTOMENTRY / NTA_NOENTRY
#ifdef NTA_CUSTOMENTRY
#pragma comment(linker, "/ENTRY:" NTA_CUSTOMENTRY)
#endif

#if defined(NTA_CUSTOMENTRY) || defined(NTA_NOENTRY) || (NTA_DLL && defined(NTA_EXPORTS))
#if _DEBUG
#if _DLL
#pragma comment(lib, "msvcrtd.lib")
#pragma comment(lib, "vcruntimed.lib")
#pragma comment(lib, "ucrtd.lib")
#else
#pragma comment(lib, "libcmtd.lib")
#pragma comment(lib, "libvcruntimed.lib")
#pragma comment(lib, "libucrtd.lib")
#endif
#else
#if _DLL
#pragma comment(lib, "msvcrt.lib")
#pragma comment(lib, "vcruntime.lib")
#pragma comment(lib, "ucrt.lib")
#else
#pragma comment(lib, "libcmt.lib")
#pragma comment(lib, "libvcruntime.lib")
#pragma comment(lib, "libucrt.lib")
#endif
#endif
#endif
