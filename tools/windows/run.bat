@echo off
echo Compiling...
call compile "%1"
echo Running...
.\"%1.exe"
del "%1.exe"
echo Finish.