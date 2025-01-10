/**
 * @file 11520.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-12-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <bits/stdc++.h>
using namespace std;

#ifndef LOCAL
#define endl '\n'
#endif

bool mem1;

#define maxn 155
#define maxm 10005

typedef pair<int, int> pii;

int a[maxn];
int64_t f[maxn][maxn], g[maxn][maxn], h[maxn][maxn << 1], sum[maxn][maxn];
vector<pii> rec[maxn];

void solve(void) {
    int n, m, c;
    cin >> n >> m >> c;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, w, d, t; i <= m; i++) cin >> w >> d >> t, rec[t].emplace_back(w, d);

    for (int t = 1; t <= 150; t++) {
        for (int i = 1; i <= 2 * n; i++) h[t][i] = 1e18;
        for (auto x : rec[t]) {
            int w = x.first, d = x.second;
            for (int i = d; i <= 2 * n; i++) h[t][i] = min(h[t][i], h[t][i - d] + w);
            for (int i = 2 * n - 1; ~i; i--) h[t][i] = min(h[t][i], h[t][i + 1]);
        }
    }

    for (int l = 1; l <= n; l++)
        for (int r = l; r <= n; r++) f[l][r] = 1e18;

    for (int t = 150; t >= 0; t--) {
        for (int l = 1; l <= n; l++)
            for (int r = l; r <= n; r++) sum[l][r] = sum[l][r - 1] + max(0, (a[r] - t) * c);

        for (int l = 1; l <= n; l++)
            for (int r = l; r <= n; r++) g[l][r] = 1e18;

        for (int len = 1; len <= n; len++)
            for (int l = 1, r = len; r <= n; l++, r++) {
                for (int x = l; x <= r; x++)
                    f[l][r] = min(f[l][r], f[l][x - 1] + f[x][r]),
                    g[l][r] = min({g[l][r], g[l][x - 1] + sum[x][r], g[l][x - 1] + f[x][r]});
                f[l][r] = min(f[l][r], g[l][r] + h[t][len]);
            }
    }

    cout << f[1][n] << endl;

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