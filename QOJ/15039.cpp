/**
 * @file 15039.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-11-17
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

#define maxn 3005

int64_t f[maxn][maxn], g[maxn][maxn];

void solve(void) {
    int n, mod;

    cin >> n >> mod;

    for (int i = 0; i <= n; i++) f[1][i] = 1;

    for (int i = 2; i <= n; i++) {
        int lim = n / i, mxx = 0;

        for (int k = 0; k <= lim; k++) g[0][k] = f[i - 1][k];
        for (int x = 1, y = i - 2; x <= y; x++, y--) {
            mxx = x;
            for (int k = 0; k <= lim; k++) g[x][k] = 0;
            for (int kl = 0; kl <= lim; kl++)
                for (int kr = kl; kr <= lim; kr++) {
                    int64_t coef = x == y ? f[x][2 * (kr - kl)] : f[x][kr - kl] * f[y][kr - kl] % mod;
                    g[x][kr] = (g[x][kr] + g[x - 1][kl] * coef) % mod;
                }
        }

        for (int k = 0; k <= lim; k++) f[i][k] = g[mxx][k];
    }

    cout << f[n][1] << endl;

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