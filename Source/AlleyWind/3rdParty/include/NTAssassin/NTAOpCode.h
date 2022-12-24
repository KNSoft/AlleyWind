#pragma once

#include "NTADef.h"

#define OPCODE_X86_NOP ((BYTE)0x90)
#define OPCODE_X64_NOP ((BYTE)0x90)
#define OPCODE_X86_INT3_CC ((BYTE)0xCC)
#define OPCODE_X64_INT3_CC ((BYTE)0xCC)

#if _M_IX86
#define OPCODE_NOP OPCODE_X86_NOP
#define OPCODE_INT3_CC OPCODE_X86_INT3_CC
#elif _M_X64
#define OPCODE_NOP OPCODE_X64_NOP
#define OPCODE_INT3_CC OPCODE_X64_INT3_CC
#else
#error OPCODE_NOP not supported current platform!
#endif
