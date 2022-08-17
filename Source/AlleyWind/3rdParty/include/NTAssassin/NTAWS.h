#pragma once

#include "NTADef.h"

NTA_API BOOL NTAPI WS_Startup();

_Must_inspect_result_ NTA_API SOCKET NTAPI WS_CreateIPv4ListenSocket(IPPROTO Protocol, PIN_ADDR Address, USHORT Port);
