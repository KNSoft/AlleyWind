#pragma once

#include "NTADef.h"

#include <WinSock2.h>

#define WS_Htons(x) (((x & 0x00FF) << 8) | ((x & 0xFF00) >> 8))

NTA_API BOOL NTAPI WS_Startup();

_Check_return_ NTA_API SOCKET NTAPI WS_CreateIPv4ListenSocket(IPPROTO Protocol, PIN_ADDR Address, USHORT Port);
