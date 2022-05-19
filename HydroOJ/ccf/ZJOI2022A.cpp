/**
 * @file ZJOI2022A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-05-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <bits/stdc++.h>
using namespace std;

bool mem1;

#define maxn 505

int64_t f[2][maxn][maxn];

void solve(void) {
    int n, mod;
    cin >> n >> mod;
    for (int i = 1; i < n; i++) f[1][1][i] = 1;
    for (int i = 2; i <= n; i++) {
        bool t = i & 1;
        memset(f[t], 0, sizeof(f[t]));
        for (int j = 1; j < i; j++)
            for (int k = 1; k <= n - i + 1; k++)
                if (f[!t][j][k]) {
                    f[t][j + 1][k] = (f[t][j + 1][k] + f[!t][j][k] * j % mod * k) % mod;
                    f[t][j][k - 1] = (f[t][j][k - 1] + f[!t][j][k] * j % mod * k) % mod;
                    f[t][j][k] = (f[t][j][k] + f[!t][j][k] * (mod - 2) % mod * j % mod * k) % mod;
                }
        int64_t ans = 0;
        for (int j = 1; j < i; j++) ans = (ans + f[t][j][0]) % mod;
        cout << ans << endl;
    }
    return;
}

bool mem2;

int main() {
    ios::sync_with_stdio(false);
#ifndef LOCAL
    freopen("tree.in", "r", stdin), freopen("tree.out", "w", stdout);
#endif
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