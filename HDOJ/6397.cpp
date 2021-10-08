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

#define maxn 200005
#define mod 998244353

long long fac[maxn], ifac[maxn];

long long Pow(long long a, long long x) {
    long long ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod;
        x >>= 1;
    }
    return ans;
}

inline long long C(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }
inline long long choose(int n, int m) { return C(n + m - 1, m - 1); }

void solve(void) {
    int n = read<int>(), m = read<int>(), k = read<int>();
    long long answer = 0;
    for (int i = 0, id = +1; i <= m && n * i <= k; i++, id = -id) {
        answer = (answer + id * C(m, i) % mod * choose(k - n * i, m)) % mod;
    }
    cout << (answer + mod) % mod << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false);
    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = Pow(fac[maxn - 1], mod - 2);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
    int _ = read<int>();
    while (_--) solve();
    return 0;
}