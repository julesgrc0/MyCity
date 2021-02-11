@echo off
@REM gcc version 8.1.0 (x86_64-win32-seh-rev0, Built by MinGW-W64 project) 
g++ -std=gnu++11 -std=c++11 -static-libgcc -static-libstdc++   "*.cpp" "src/*.cpp"  -o "bin/main" -pedantic -Wall -Wextra  -I "include" -L "lib" -lmingw32 -lSDL2main -lSDL2_ttf -lSDL2 && cd bin && main && cd ..