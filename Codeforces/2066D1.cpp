/**
 * @file 2066D1.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-02-11
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

#define maxn 105
#define maxm 10005
#define mod 1'000'000'007

int a[maxm], f[maxn][maxm];
int64_t fac[maxm], ifac[maxm];

int64_t qpow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t inv(int64_t a) { return qpow(a, mod - 2); }

int Mod(int x) { return x >= mod ? x - mod : x; }

int64_t C(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

void solve(void) {
    int n, c, m;
    cin >> n >> c >> m;
    for (int i = 1; i <= m; i++) cin >> a[i];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) f[i][j] = 0;

    f[n][c] = 1;
    for (int i = n - 1; i >= 1; i--)
        for (int j = c; j <= m; j++)
            if (f[i + 1][j])
                for (int k = 0; k <= min(m - j, c); k++) f[i][j + k] = (f[i][j + k] + f[i + 1][j] * C(c, k)) % mod;

    cout << f[1][m] << endl;

    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    fac[0] = ifac[0] = 1;
    for (int i = 1; i < maxm; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxm - 1] = inv(fac[maxm - 1]);
    for (int i = maxm - 2; i; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}