/**
 * @author Macesuted (i@macesuted.moe)
 * @copyright Copyright (c) 2021
 */

#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline T read() {
    T x = 0, f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-') f = -1;
    for (; c <= '9' && c >= '0'; c = getchar())
        x = x * 10 + (c & 15);
    return x * f;
}

#define maxn 40005
#define MOD 999911659

int P[4] = {2, 3, 4679, 35617};
long long fac[maxn], ifac[maxn], answer[4];

long long Pow(long long a, long long x, long long mod) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod;
        x >>= 1;
    }
    return ans;
}
long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) return x = 1, y = 0, a;
    long long g = exgcd(b, a % b, x, y);
    return tie(x, y) = make_tuple(y, x - a / b * y), g;
}
long long C(int n, int m, int p) {
    if (n < m) return 0;
    if (n >= p || m >= p) return C(n / p, m / p, p) * C(n % p, m % p, p) % p;
    return fac[n] * ifac[m] % p * ifac[n - m] % p;
}

int main() {
    ios::sync_with_stdio(false);
    int n = read<int>(), g = read<int>();
    if (g % MOD == 0) return cout << 0 << endl, 0;
    for (int t = 0; t < 4; t++) {
        int &mod = P[t];
        fac[0] = ifac[0] = 1;
        for (int i = 1; i < mod; i++) fac[i] = fac[i - 1] * i % mod;
        ifac[mod - 1] = mod - 1;
        for (int i = mod - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
        answer[t] = 0;
        for (int k = 1; k * k <= n; k++)
            if (n % k == 0) {
                answer[t] = (answer[t] + C(n, k, mod)) % mod;
                if (k * k != n) answer[t] = (answer[t] + C(n, n / k, mod)) % mod;
            }
    }
    long long ans = 0;
    for (int i = 0; i < 4; i++) {
        long long m = (MOD - 1) / P[i], _m, y;
        exgcd(m, P[i], _m, y);
        ans = (ans + (answer[i] * m % (MOD - 1) * _m % (MOD - 1) + MOD - 1)) % (MOD - 1);
    }
    cout << Pow(g, ans, MOD) << endl;
    return 0;
}