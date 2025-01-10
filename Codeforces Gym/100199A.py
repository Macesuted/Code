import math;

fin = open("china.in", "r")
fout = open("china.out", "w")

n = int(fin.read())

m = n // 2

while math.gcd(n, m) != 1:
    m -= 1

fout.write(str(m))