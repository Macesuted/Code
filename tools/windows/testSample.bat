@echo off
echo Compiling...
call compile %1
echo Running...
%1.exe < sample/%1/%2.in