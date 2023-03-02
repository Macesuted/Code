@echo off
g++ %1.cpp -o %1 -std=c++17 -Wall -Wextra -O2 -Wl,--stack=512000000 -IE:/Code/libs/testlib -DLOCAL