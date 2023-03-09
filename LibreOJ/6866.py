"""
File:   6866.py
Author: Macesuted (i@macesuted.moe)
Date:   2023-03-05

Copyright (c) 2023
"""

n, k = input().split(' ');
n, k = int(n), int(k)

if k == 1:
    if n == 1:
        print(1)
    else:
        print('Poor E.S.!')
    exit()

if k == 2:
    print(2 ** (n - 2))
    exit()

k -= 1

f = v = 1
for i in range(2, n + 1):
    v = (f + k - 1) // k
    f += v

print(v)