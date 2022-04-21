/**
 * @file modint.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 5000005
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

int64_t fac[maxn], ifac[maxn], f[maxn], g[maxn];

int64_t binom(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

void solve(void) {
    int n, m, l, k;
    cin >> n >> m >> l >> k;
    int N = min({n, m, l});
    int64_t d = f[0] = 1;
    for (int i = 1; i <= N; i++)
        f[i] = f[i - 1] * (n - i + 1) % mod * (m - i + 1) % mod * (l - i + 1) % mod,
        d = d * (g[i] = 1LL * n * m % mod * l % mod + mod - 1LL * (n - i) * (m - i) % mod * (l - i) % mod) % mod;
    d = Inv(d);
    for (int i = N; i; i--) f[i] = d * f[i] % mod, d = d * g[i] % mod;
    int64_t ans = 0;
    for (int i = k, op = 1; i <= N; i++, op = mod - op) ans = (ans + op * binom(i, k) % mod * f[i]) % mod;
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifdef MACESUTED
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = Inv(fac[maxn - 1]);
    for (int i = maxn - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef MACESUTED
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}