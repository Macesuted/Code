@echo off
g++ %1.cpp -o %1.exe -lm -Wall -O2 "-Wl,--stack=512000000"
%1.exe < %1-%2.in > %1-%2.out
fc %1-%2.out %1-%2.ans