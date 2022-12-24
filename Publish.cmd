RD /S /Q "%~dp0Release"
MD "%~dp0Release"
COPY /Y "%~dp0Source\x86\Release\AlleyWind.exe" "%~dp0Release\AlleyWind_x86.exe"
COPY /Y "%~dp0Source\x64\Release\AlleyWind.exe" "%~dp0Release\AlleyWind_x64.exe"
PAUSE