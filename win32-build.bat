@echo off

:: Clean the existing build directory.
:: echo Cleaning the existing build directory...
:: rmdir /s /q build
:: mkdir build

:: Navigate into the build directory.
mkdir build
cd build

:: Run CMake build.
echo Running CMake build.
cmake -G "MinGW Makefiles" ..

:: Run MinGW build.
echo Running MinGW build.
mingw32-make

pause
