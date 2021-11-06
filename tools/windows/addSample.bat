@echo off
mkdir sample/%1
type nul > sample/%1/%2.in
type nul > sample/%1/%2.ans
start sample/%1/%2.in
start sample/%1/%2.ans