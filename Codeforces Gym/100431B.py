'''
@file 100431B.py
@author Macesuted (i@macesuted.moe)
@date 2025-07-17

@copyright Copyright (c) 2025
'''

from math import log2

fin = open("binary.in", "r")
fout = open("binary.out", "w")

n = int(fin.read())

ans = 0
lim = min(n, int(5 + log2(n)))

for x in range(n):
    cl = 0
    cr = 0

    mark = [0 for i in range(n)]
    mark[x] = -1

    chk = True

    l = 0
    r = n
    while l + 1 < r:
        mid = (l + r) // 2
        if mid <= x:
            l = mid
            if mark[mid] == +1:
                chk = False
                break
            if mark[mid] == 0:
                mark[mid] = -1
                cl += 1
        else:
            r = mid
            if mark[mid] == -1:
                chk = False
                break
            if mark[mid] == 0:
                mark[mid] = +1
                cr += 1

    if chk == False:
        continue

    for v in range(1, n + 1):
        ans += (v ** cl) * ((n - v) ** cr) * (n ** (lim - 1 - cl - cr))

fout.write(str(ans * (n ** (n - lim))))
