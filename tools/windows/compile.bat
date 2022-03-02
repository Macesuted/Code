@echo off
g++ %1.cpp -o %1.exe -lm -Wall -Wextra -O2 -std=c++14 "-Wl,--stack=512000000" -I E:\Code\tools\libs\atcoder -I E:\Code\tools\libs\testlib -DMACESUTED