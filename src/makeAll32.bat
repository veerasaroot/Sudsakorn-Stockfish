@echo off
REM x32 builds end
SET PATH=C:\tools\msys64\mingw32\bin;C:\tools\msys64\usr\bin;%PATH%
Title "x86-32"
make clean
make -f MakeFile profile-build ARCH=x86-32 COMP=mingw
strip sudsakorn.exe
ren sudsakorn.exe "Sudsakorn0.5-x86-32.exe"

Title "x86-32-old"
make clean
make -f MakeFile profile-build ARCH=x86-32-old COMP=mingw
strip sudsakorn.exe
ren sudsakorn.exe "Sudsakorn0.5-x86-32-old.exe"

Title "general-32"
make clean
make -f MakeFile profile-build ARCH=general-32 COMP=mingw
strip sudsakorn.exe
ren sudsakorn.exe "Sudsakorn0.5-general-32.exe"

make clean
REM x32 builds end

pause
