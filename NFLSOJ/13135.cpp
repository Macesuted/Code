/**
 * @file 13135.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 4005
#define mod 998244353

int a[maxn];
int64_t aft[maxn], f[maxn][maxn], g[maxn << 1];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    aft[n + 1] = 1;
    for (int i = n; i; i--) aft[i] = aft[i + 1] * (a[i] + 1) % mod;
    f[1][0] = 1;
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = (ans + (a[i] + 1) / 2 * f[i][0] % mod * aft[i + 1]) % mod;
        memset(g, 0, sizeof(g));
        g[1] = (g[1] + f[i][0]) % mod, g[a[i] + 2] = (g[a[i] + 2] + mod - f[i][0]) % mod;
        for (int j = 1; j < maxn; j++) g[j] = (g[j] + f[i][j]) % mod, g[a[i] + j + 1] = (g[a[i] + j + 1] + mod - f[i][j]) % mod;
        for (int j = 1; j < (maxn << 1); j++) g[j] = (g[j] + g[j - 1]) % mod;
        for (int j = 0; j < (maxn << 1); j++) f[i + 1][j >> 1] = (f[i + 1][j >> 1] + g[j]) % mod;
    }
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("partition.in", "r", stdin), freopen("partition.out", "w", stdout);
#endif
#ifdef LOCAL
    cerr << "Memory: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}