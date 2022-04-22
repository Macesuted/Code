/**
 * @file 12720.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 20000005
#define mod 998244353

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Inv(int64_t a) { return Pow(a, mod - 2); }

int64_t fac[maxn], ifac[maxn];

int64_t binom(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

void solve(void) {
    int n, m, k;
    cin >> n >> m >> k;
    if (k == 0) return cout << Inv(n) << endl, void();
    fac[0] = ifac[0] = 1;
    for (int i = 1; i <= n + m; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[n + m] = Inv(fac[n + m]);
    for (int i = n + m - 1; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
    int64_t ans = binom(m + n - 1, n - 1);
    for (int t = 0, op = mod - 1, x = m; x >= 0 && t <= n; t++, x -= k, op = mod - op)
        ans = (ans + op * binom(n, t) % mod * binom(x + n - 1, n - 1)) % mod;
    cout << ans * Inv(n) % mod * Inv(binom(m - k + n - 1, n - 1)) % mod << endl;
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("probability.in", "r", stdin), freopen("probability.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}