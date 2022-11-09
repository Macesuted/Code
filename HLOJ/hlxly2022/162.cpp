/**
 * @file 162.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-07-18
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

#define maxn 2005
#define mod 1000000007

int f[maxn][maxn];

void solve(void) {
    int n, S, T;
    cin >> n >> S >> T;
    f[0][0] = 1;
    for (int i = 1; i < n; i++)
        for (int j = 0; j <= i; j++) {
            int64_t v = f[i - 1][j];
            if (!v) continue;
            if (i == S) {
                f[i][j] = (f[i][j] + v) % mod;
                if (j) f[i][j - 1] = (f[i][j - 1] + v * j) % mod;
            } else if (i == T) {
                f[i][j] = (f[i][j] + v) % mod;
                if (j) f[i][j - 1] = (f[i][j - 1] + v * j) % mod;
            } else {
                f[i][j + 1] = (f[i][j + 1] + v) % mod;
                if (i >= S && j) f[i][j - 1] = (f[i][j - 1] + v * j) % mod;
                if (i >= T && j) f[i][j - 1] = (f[i][j - 1] + v * j) % mod;
                if (j > 1) f[i][j - 1] = (f[i][j - 1] + v * j % mod * (j - 1)) % mod;
            }
        }
    cout << f[n - 1][0] << endl;
    return;
}

bool mem2;

int main() {
#ifndef LOCAL
    freopen("frog.in", "r", stdin), freopen("frog.out", "w", stdout);
#endif
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