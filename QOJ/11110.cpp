/**
 * @file 11110.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2025-05-13
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

#define maxn 5005
#define mod 998244353

int f[maxn][maxn];

int Mod(int x) { return x >= mod ? x - mod : x; }

void solve(void) {
    int n, m;
    string s, t;
    cin >> n >> m >> s >> t;
    s = ' ' + s, t = ' ' + t;

    auto getT = [&](int i) { return (i <= m || i > n + m) ? '0' : t[i - m]; };

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++) f[i][j] = 0;

    f[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++) {
            if (!f[i - 1][j]) continue;
            if (s[i] != '0' && getT(i + 2 * j) != '0') f[i][j] = Mod(f[i][j] + f[i - 1][j]);
            if (s[i] != '0' && j < m && getT(i + 2 * j) != '1' && getT(i + 2 * j + 1) != '1' && getT(i + 2 * j + 2) != '1')
                f[i][j + 1] = Mod(f[i][j + 1] + f[i - 1][j]);
            if (s[i] != '1' && getT(i + 2 * j) != '1') f[i][j] = Mod(f[i][j] + f[i - 1][j]);
        }

    cout << f[n][m] << endl;

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