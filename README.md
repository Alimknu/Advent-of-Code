# Advent-of-Code (local build)

Build and run instructions (PowerShell / Windows). This project creates one executable per `.cpp` file and places binaries under `build/bin/<relative-source-dir>/`.

# create build directory and configure
cmake -S . -B build

# build (uses Release by default)
cmake --build build --config Release

Run the `day1` executable for 2025 (example):

# executable path: build\bin\2025\day1.exe
.\build\bin\2025\day1.exe 2025\day1input.txt 

# MinGW/g++
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

# To clean the build directory:
Remove-Item -Recurse -Force build
