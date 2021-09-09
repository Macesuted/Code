@echo off
g++ %1.cpp -o %1.exe -lm -Wall -O2 -std=c++14 "-Wl,--stack=512000000"