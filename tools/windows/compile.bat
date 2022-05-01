@echo off
g++ "%1.cpp" -o "%1.exe" -lm -Wall -Wextra -O2 -std=c++20 "-Wl,--stack=512000000" -I E:\Code\libs\ac-library -I E:\Code\libs\testlib -DLOCAL