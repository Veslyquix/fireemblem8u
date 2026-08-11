@echo off
setlocal

set "REPO_DIR=%~dp0"
set "BASH=C:\devkitPro\msys2\usr\bin\bash.exe"

if not exist "%BASH%" (
    echo Could not find devkitPro MSYS bash at:
    echo   %BASH%
    exit /b 1
)

"%BASH%" -lc "export PATH='/c/Program Files/Git/cmd:/mingw64/bin:/usr/bin:/opt/devkitpro/devkitARM/bin':$PATH; cd '/c/devkitPro/decomp'; make fireemblem8.gba -j1 TOOLCHAIN=/opt/devkitpro/devkitARM PYTHON=python3 && sha1sum -c checksum.sha1"
set "BUILD_RESULT=%ERRORLEVEL%"

echo.
if "%BUILD_RESULT%"=="0" (
    echo Build complete.
) else (
    echo Build failed with exit code %BUILD_RESULT%.
)
pause
exit /b %BUILD_RESULT%
