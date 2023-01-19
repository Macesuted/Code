/**
 * @file 4812.cpp
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

#define maxn 300005
#define maxS 805
#define mod 998244353

int f[2][maxn << 1], g[maxS << 1][maxS << 1];

void solve(void) {
    int n;
    int64_t c, ans = 0;
    cin >> n >> c;
    int S = sqrt(2 * n) + 5;
    f[1][0 + maxn] = 1;
    if (S <= n) ans = 1;
    for (int i = 2; i * S <= 2 * n; i++) {
        bool t = i & 1;
        for (int j = max(-i * (i + 1) / 2, -i * S + 1); j <= i * (i + 1) / 2 && i * S + j <= n; j++) {
            f[t][j + maxn] = (f[!t][j - i + 1 + maxn] + f[!t][j + i - 1 + maxn] * c) % mod;
            if ((n - j) % i == 0) ans = (ans + f[t][j + maxn]) % mod;
        }
    }
    int T = 2 * S + 5;
    for (int i = 1; i <= n; i++) {
        int t = i % T;
        for (int j = 1; j <= min(i, T); j++) {
            g[t][j] = g[(t + T - j) % T][j + 1] * c % mod;
            if (j > 1) g[t][j] = (g[t][j] + g[(t + T - j) % T][j - 1]) % mod;
        }
        if (i < S) g[t][i] = (g[t][i] + 1) % mod;
    }
    for (int j = 1; j <= T; j++) ans = (ans + g[n % T][j]) % mod;
    cout << ans << endl;
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
#ifdef LOCAL
    cerr << "Memory Cost: " << abs(&mem1 - &mem2) / 1024. / 1024. << "MB" << endl;
#endif

    int _ = 1;
    while (_--) solve();

#ifdef LOCAL
    cerr << "Time Cost: " << clock() * 1000. / CLOCKS_PER_SEC << "MS" << endl;
#endif
    return 0;
}