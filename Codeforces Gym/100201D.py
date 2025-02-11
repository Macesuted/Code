n = int(open("digit.in", "r").read())

f0, f1 = 1, 0

v = 1

while v <= n:
    if n % (2 * v) >= v:
        f0, f1 = f0 + f1, f1
    else:
        f0, f1 = f0, f0 + f1
    v *= 2

open("digit.out", "w").write(str(f0))