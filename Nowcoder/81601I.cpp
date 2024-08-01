/**
 * @file 81601I.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

vector<vector<int64_t>> a, fl, fr, f;

void solve(void) {
    int n, m;
    cin >> n >> m;
    a.clear(), fl.clear(), fr.clear(), f.clear();
    a.resize(n + 1), fl.resize(n + 1), fr.resize(n + 1), f.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i].resize(m + 1), fl[i].resize(m + 1), fr[i].resize(m + 1), f[i].resize(m + 1);
        for (int j = 1; j <= m; j++) cin >> a[i][j];
        int64_t sum = 0;
        for (int j = 1; j <= m; j++) fl[i][j] = fr[i][j] = (sum += a[i][j]);
        for (int j = 1; j <= m; j++) fl[i][j] = min(fl[i][j - 1], fl[i][j]);
        for (int j = m - 1; j; j--) fr[i][j] = max(fr[i][j + 1], fr[i][j]);
    }
    for (int j = 1; j <= m; j++) f[1][j] = fr[1][j] - fl[1][j - 1];
    for (int i = 1; i < n; i++) {
        vector<int64_t> g;
        g.resize(m + 1);

        for (int j = 1; j <= m; j++) g[j] = f[i][j] + fr[i + 1][j];
        for (int j = m - 1; j; j--) g[j] = max(g[j], g[j + 1]);
        for (int j = 1; j <= m; j++) f[i + 1][j] = g[j] - fl[i + 1][j - 1];

        for (int j = 1; j <= m; j++) g[j] = f[i][j] - fl[i + 1][j - 1];
        for (int j = 2; j <= m; j++) g[j] = max(g[j], g[j - 1]);
        for (int j = 1; j <= m; j++) f[i + 1][j] = max(f[i + 1][j], g[j] + fr[i + 1][j]);
    }
    int64_t ans = f[n][1];
    for (int j = 1; j <= m; j++) ans = max(ans, f[n][j]);
    cout << ans << endl;
    return;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(nullptr);

    int _ = 1;
    cin >> _;
    while (_--) solve();

    return 0;
}