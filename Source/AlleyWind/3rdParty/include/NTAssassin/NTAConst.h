#pragma once

// Memory alignment
#define PAGE_SIZE 0x1000
#define CODE_ALIGNMENT 0x10
#define STRING_ALIGNMENT 0x4

#define ASCII_CASE_MASK                         0b100000
#define MAX_WORD_IN_DEC_CCH                     6                                   // Max WORD in decimal is 65535
#define MAX_QWORD_IN_HEX_CCH                    17                                  
#define MAX_CLASSNAME_CCH                       256
#define MAX_CIDENTIFIERNAME_CCH                 247
#define MAX_ATOM_CCH                            255
#define MAX_REG_KEYNAME_CCH                     255
#define MAX_REG_VALUENAME_CCH                   16383
#define HEXRGB_CCH                              8   // #RRGGBB
#define MAX_POINTER_CCH                         (sizeof(PVOID) * 2 + 1)
#define CURRENT_PROCESS_HANDLE                  ((HANDLE)-1)
#define CURRENT_THREAD_HANDLE                   ((HANDLE)-2)
#define CURRENT_PROCESS_TOKEN_HANDLE            ((HANDLE)-4)
#define CURRENT_THREAD_TOKEN_HANDLE             ((HANDLE)-5)
#define CURRENT_THREAD_EFFECTIVETOKEN_HANDLE    ((HANDLE)-6)
#define FIXED_IMAGE_BASE32                      ((HINSTANCE)0x00400000)
#define FIXED_IMAGE_BASE64                      ((HINSTANCE)0x0000000140000000)

#define EOLW                                    ((DWORD)0x000A000D)
#define EOLA                                    ((WORD)0x0A0D)
#ifdef UNICODE
#define EOL EOLW
#else
#define EOL EOLA
#endif
