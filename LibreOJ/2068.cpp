/**
 * @file 2068.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2022-12-07
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

#define maxn 805

int64_t a[maxn][maxn], sum[maxn][maxn], fl[maxn][maxn], fr[maxn][maxn], gl[maxn][maxn], gr[maxn][maxn], h[maxn][2];

int64_t _(int xl, int xr, int yl, int yr) { return sum[xr][yr] - sum[xl - 1][yr] - sum[xr][yl - 1] + sum[xl - 1][yl - 1]; }
int64_t dp(int n, int m) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) sum[i][j] = sum[i][j - 1] + a[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) sum[i][j] += sum[i - 1][j];
    for (int i = 0; i <= n + 1; i++)
        for (int j = 0; j <= m + 1; j++) fl[i][j] = fr[i][j] = gl[i][j] = gr[i][j] = -1e18;
    fl[1][1] = fr[1][1] = a[1][1], gl[n][m] = gr[n][m] = a[n][m];
    for (int i = 1; i <= n; i++)
        for (int j = 1 + (i == 1); j <= m; j++)
            fl[i][j] = max({fl[i][j - 1], fl[i - 1][j] + a[i][1], fr[i - 1][j - 1] + _(i, i, 1, j) + _(1, i - 1, j, j)}),
            fr[i][j] = max({fr[i - 1][j], fr[i][j - 1] + a[1][j], fl[i - 1][j - 1] + _(i, i, 1, j) + _(1, i - 1, j, j)});
    for (int i = n; i; i--)
        for (int j = m - (i == n); j; j--)
            gl[i][j] = max({gl[i + 1][j], gl[i][j + 1] + a[n][j], gr[i + 1][j + 1] + _(i, i, j, m) + _(i + 1, n, j, j)}),
            gr[i][j] = max({gr[i][j + 1], gr[i + 1][j] + a[i][n], gl[i + 1][j + 1] + _(i, i, j, m) + _(i + 1, n, j, j)});
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) h[i][0] = fl[i][m], h[i][1] = -1e18;
    for (int j = 1; j <= m; j++) {
        int64_t val = -1e18;
        for (int i = 1; i <= n; i++) {
            val = max(val + a[i][m], _(1, i, j, j) + _(i, i, j + 1, m));
            h[i][1] = max(h[i][1], (j == 1 ? 0 : fr[i][j - 1]) + val);
        }
    }
    for (int i = 2; i <= n; i++)
        h[i][0] = max({h[i][0], h[i - 1][0] + a[i][1], h[i - 1][1] + _(i, i, 1, m)}),
        h[i][1] = max({h[i][1], h[i - 1][1] + a[i][m], h[i - 1][0] + _(i, i, 1, m)});
    ans = max(ans, h[n][1]);
    for (int i = 1; i <= n; i++) ans = max(ans, h[i - 1][1] + gr[i][m]);
    for (int j = 1; j <= m; j++) {
        int64_t val = -1e18;
        for (int i = n; i; i--) {
            val = max(val + a[i][1], _(i, n, j, j) + _(i, i, 1, j - 1));
            ans = max(ans, h[i - 1][0] + (j == m ? 0 : gl[i][j + 1]) + val);
        }
    }
    return ans;
}

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> a[i][j];
    int64_t ans = dp(n, m);
    for (int i = 1; i <= max(n, m); i++)
        for (int j = 1; j < i; j++) swap(a[i][j], a[j][i]);
    cout << max(ans, dp(m, n)) << endl;
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