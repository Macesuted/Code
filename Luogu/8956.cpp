/**
 * @file 8956.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2023-01-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 1000
#define mod 998244353

int64_t f[maxn], g[maxn];

int64_t Pow(int64_t a, int64_t x) {
    int64_t ans = 1;
    while (x) {
        if (x & 1) ans = ans * a % mod;
        a = a * a % mod, x >>= 1;
    }
    return ans;
}
int64_t Sqrt(int64_t x) {
    int64_t v = sqrtl(x);
    while (v * v > x) v--;
    while ((v + 1) * (v + 1) <= x) v++;
    return v;
}

void solve(void) {
    int64_t n, p = 2, q = 2, ans = 1;
    cin >> n >> f[0] >> f[1] >> g[0] >> g[1];
    if (n == 1) return cout << (g[0] + mod - f[0] % mod) % mod << endl, void();
    while (f[p - 2] != f[p - 1] && p < n) f[p] = Sqrt(f[p - 2] * f[p - 1]) + 1, p++;
    while (g[q - 2] != g[q - 1] && q < n) g[q] = Sqrt(g[q - 2] * g[q - 1]) + 1, q++;
    while (p < q) f[p] = Sqrt(f[p - 2] * f[p - 1]) + 1, p++;
    while (p > q) g[q] = Sqrt(g[q - 2] * g[q - 1]) + 1, q++;
    for (int i = 0; i < p; i++) ans = ans * (g[i] + mod - f[i] % mod) % mod;
    cout << ans * Pow(g[p - 2] + mod - f[p - 2] % mod, (n - p) / 2 + (n - p) % 2) % mod *
                Pow(g[p - 1] + mod - f[p - 1] % mod, (n - p) / 2) % mod
         << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    cin >> _;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}