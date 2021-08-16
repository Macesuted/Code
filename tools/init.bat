@echo off
type nul > %1-%2.in
type nul > %1-%2.ans
start %1-%2.in
start %1-%2.ans