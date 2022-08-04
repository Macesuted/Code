#include <bits/stdc++.h>
using namespace std;

const int N = 1e7 + 5, mod = 998244353;

inline int inc(int a, int b) { return (a += b - mod) + (a >> 31 & mod); }
inline int dec(int a, int b) { return (a -= b) + (a >> 31 & mod); }
inline int mul(int a, int b) { return 1ll * a * b % mod; }
inline void Inc(int &a, int b) { return void(a = inc(a, b)); }
inline void Dec(int &a, int b) { return void(a = dec(a, b)); }
inline void Mul(int &a, int b) { return void(a = mul(a, b)); }
inline int Pow(int a, int b) {
    int c = 1;
    for (; b; Mul(a, a), b >>= 1)
        if (1 & b) Mul(c, a);
    return c;
}
inline int Inv(int x) { return Pow(x, mod - 2); }

int fac[N], inv[N], n, k1, k2, a, b, tot, Sum;

inline int Polycoef(int n, int m, int k) { return mul(fac[n + m + k], mul(mul(inv[n], inv[m]), inv[k])); }

int main(void) {
    scanf("%d%d%d%d%d", &k1, &k2, &n, &a, &b);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = mul(fac[i - 1], i);
    inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = mul(mod - mod / i, inv[mod % i]);
    inv[0] = 1;
    for (int i = 1; i <= n; i++) Mul(inv[i], inv[i - 1]);
    for (int i = 0; i <= n; i++)
        if (i * k1 <= n - 1) {
            int res = n - 1 - i * k1;
            if (res % k2) continue;
            int j = res / k2;
            if (j > n) continue;
            Inc(tot, Polycoef(i, j, n - i - j));
        }
    for (int i = 0; i <= n - 1; i++)
        if (i * k1 <= n - 1 - k1) {
            int res = n - 1 - k1 - i * k1;
            if (res % k2) continue;
            int j = res / k2;
            if (j > n - 1) continue;
            Inc(Sum, mul(Polycoef(i, j, n - 1 - i - j), a));
        }
    for (int i = 0; i <= n - 1; i++)
        if (i * k1 <= n - 1 - k2) {
            int res = n - 1 - k2 - i * k1;
            if (res % k2) continue;
            int j = res / k2;
            if (j > n - 1) continue;
            Inc(Sum, mul(Polycoef(i, j, n - 1 - i - j), b));
        }
    Mul(tot, Inv(n));
    return printf("%d\n", mul(Sum, Inv(tot))) * 0;
}