@echo off
REM make -j profile-build
make profile-build ARCH=native COMP=gcc
strip sudsakorn
ren sudsakorn Sudsakorn0.5-native
make clean
pause
