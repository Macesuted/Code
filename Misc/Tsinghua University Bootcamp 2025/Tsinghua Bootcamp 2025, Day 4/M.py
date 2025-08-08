'''
@file M.py
@author Macesuted (i@macesuted.moe)
@date 2025-08-08

@copyright Copyright (c) 2025
'''

from decimal import Decimal, getcontext, FloatOperation

getcontext().prec = 1500
getcontext().traps[FloatOperation] = True

MAXN = 10005

fac = [1] * MAXN

for i in range(1, MAXN):
    fac[i] = fac[i - 1] * i

def C(n, m):
    return fac[n] // fac[m] // fac[n - m]

w, h, n, k = map(int, input().split())

x = [0] * (n + 2)
y = [0] * (n + 2)
for i in range(1, n + 1):
    x[i], y[i] = map(int, input().split())

    if x[i] == 0 and y[i] == 0 or x[i] == w - 1 and y[i] == h - 1:
        print(-1)
        exit()

for i in range(1, n + 1):
    for j in range(i + 1, n + 1):
        if x[i] > x[j] or x[i] == x[j] and y[i] > y[j]:
            t = x[i]
            x[i] = x[j]
            x[j] = t

            t = y[i]
            y[i] = y[j]
            y[j] = t

x[0] = 0
y[0] = 0
x[n + 1] = w - 1
y[n + 1] = h - 1

f = [0] * (n + 2)
f[0] = 1

for i in range(0, n + 1):
    if i > 0:
        f[i] *= -1
    for j in range(i + 1, n + 2):
        if y[i] <= y[j]:
            f[j] += f[i] * C((x[j] - x[i]) + (y[j] - y[i]), x[j] - x[i])

if f[n + 1] < k:
    print(-1)
    exit()

lnk = Decimal(k).ln()
lnf = Decimal(f[n + 1]).ln()

w = Decimal(lnk - lnf) / Decimal(w + h - 1)

v = Decimal(w).exp()

print(f"{v:.21f}")
