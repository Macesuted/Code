/**
 * @file arc203_c.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-08-03
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1000005
#define mod 998244353

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t inv(int64_t a) { return qpow(a, mod - 2); }

int64_t fac[maxn], ifac[maxn];

int64_t binom(int n, int m) { return 0 <= m && m <= n ? fac[n] * ifac[m] % mod * ifac[n - m] % mod : 0; }

void solve(void) {
    int64_t n, m, k;
    cin >> n >> m >> k;

    if (k < n + m - 2) return cout << 0 << endl, void();
    if (k == n + m - 2) return cout << binom(n + m - 2, n - 1) << endl, void();
    if (k == n + m - 1) return cout << binom(n + m - 2, n - 1) * 2 * (n - 1) % mod * (m - 1) % mod << endl, void();

    int64_t v1 = 0;
    if (n >= 3) v1 = (v1 + binom(n + m - 3, m) * (m - 1) % mod * (n - 2) - binom(n + m - 3, m + 1) * m % mod * (m - 1)) % mod;
    if (m >= 3) v1 = (v1 + binom(n + m - 3, n) * (n - 1) % mod * (m - 2) - binom(n + m - 3, n + 1) * n % mod * (n - 1)) % mod;

    int64_t v2 = (2 * (n - 1) * (m - 1) - 1) % mod * (n - 1) % mod * (m - 1) % mod * binom(n + m - 2, n - 1) % mod;
    int64_t v3 = (n + m - 3) * binom(n + m - 4, n - 2) % mod;

    cout << ((v1 + v2 - v3) % mod + mod) % mod << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = inv(fac[maxn - 1]);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}