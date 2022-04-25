/**
 * @file 12935.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-04-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 5005
#define mod 998244353

int a[maxn];
int64_t f[maxn][maxn][2], g[maxn][maxn][2];

void solve(void) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    f[0][0][0] = g[0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        int j = i, minA = a[i];
        while (j > 1 && min(minA, a[j - 1]) >= i - j + 2) minA = min(minA, a[--j]);
        auto sum = [&](int l, int r, int j, int k) {
            return ((r >= 0 ? g[r][j][k] : 0) + mod - (l > 0 ? g[l - 1][j][k] : 0)) % mod;
        };
        for (int k = 1; k <= i; k++)
            f[i][k][0] = (f[i - 1][k - 1][0] + f[i - 1][k - 1][1]) * k % mod,
            f[i][k][1] = (2 * (sum(j - 1, i - 2, k - 1, 0) + sum(j - 1, i - 2, k - 1, 1)) * k % mod + mod -
                          2 * sum(j - 1, i - 1, k, 0) % mod + mod - sum(j - 1, i - 1, k, 1)) %
                         mod;
        for (int k = 0; k <= i; k++)
            g[i][k][0] = (g[i - 1][k][0] + f[i][k][0]) % mod, g[i][k][1] = (g[i - 1][k][1] + f[i][k][1]) % mod;
    }
    int64_t ans = 0;
    for (int i = 0; i <= n; i++) ans = (ans + f[n][i][0] + f[n][i][1]) % mod;
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
#ifndef MACESUTED
    freopen("permutation.in", "r", stdin), freopen("permutation.out", "w", stdout);
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
