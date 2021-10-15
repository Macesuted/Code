@echo off
call compile %1
%1.exe
del %1.exe