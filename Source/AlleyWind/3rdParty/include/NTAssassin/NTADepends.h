#pragma once

#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "Kernel32.lib")
#pragma comment(lib, "User32.Lib")
#pragma comment(lib, "gdi32.Lib")
#pragma comment(lib, "Comdlg32.lib")
#pragma comment(lib, "ComCtl32.Lib")
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "Ole32.lib")
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Dwmapi.lib")
#pragma comment(lib, "UxTheme.lib")
#pragma comment(lib, "winsta.lib")
#pragma comment(lib, "ws2_32.lib")

// Always use ComCtl32.dll V6.0
#pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
