"""
@file 696681C.py
@author Macesuted (i@macesuted.moe)
@date 2026-06-06

@copyright Copyright (c) 2026
"""

sa = input()
sb = input()

if sb[-len(sa):] == sa:
    print(0)
    exit(0)

if len(sa) >= len(sb):
    print(-1)
    exit(0)

a = int(sa)
b = int(sb)

if a > b // 10:
    print(-1)
    exit(0)

c = 0
while a < b // 10 and b % 10 != 0:
    a += 1
    b += 1
    c += 1

if a == b // 10:
    print(c)
    exit(0)

delt = (b // 10 - a) // 9 * 10
a += delt
b += delt
c += delt

while a < b // 10:
    a += 1
    b += 1
    c += 1

print(c)