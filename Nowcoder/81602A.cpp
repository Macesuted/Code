/**
 * @file 81602A.cpp
 * @author Macesuted (i@macesuted.moe)
 * @date 2024-08-07
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

#define maxn 10005
#define maxm 25

int64_t f[maxn][maxm][maxm << 1][2], g[maxn][maxm], a[maxn], pre[maxn];

void solve(void) {
    int n, k, m;
    cin >> n >> k >> m;
    for (int i = 1; i <= n; i++) cin >> a[i], pre[i] = pre[i - 1] + a[i];

    multiset<int> S;
    for (int i = 1; i < k; i++) S.insert(a[i]);
    for (int l = 1, r = k; r <= n; l++, r++) {
        S.insert(a[r]);
        g[l][0] = pre[r] - pre[l - 1];
        auto p = S.begin();
        for (int i = 1; i <= min(m, k); i++) g[l][i] = g[l][i - 1] - *(p++);
        S.erase(S.find(a[l]));
    }

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            for (int k = -m; k <= m + m; k++) f[i][j][k][0] = f[i][j][k][1] = -1e9;
    f[0][0][0 + m][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int tot = 0; tot <= m; tot++)
            for (int rest = -m + m; rest <= m + m; rest++) {
                if (i % k) {
                    f[i][tot][rest][0] = max({f[i][tot][rest][0], f[i - 1][tot][rest][0], f[i - 1][tot][rest][1]});
                    f[i][tot][rest][1] = max(f[i][tot][rest][1], f[i - 1][tot][rest][1] + a[i]);
                    if (tot < m) f[i][tot + 1][rest + 1][1] = max(f[i][tot + 1][rest + 1][1], f[i - 1][tot][rest][1]);
                    if (rest > -m + m)
                        f[i][tot][rest - 1][0] =
                            max(f[i][tot][rest - 1][0], max(f[i - 1][tot][rest][0], f[i - 1][tot][rest][1]) + a[i]);
                }
                int j = i + k - 1;
                if (j > n) continue;
                for (int x = 0; x <= k && tot + x <= m; x++)
                    f[j][tot + x][rest + x][1] =
                        max(f[j][tot + x][rest + x][1], max(f[i - 1][tot][rest][0], f[i - 1][tot][rest][1]) + g[i][x]);
            }
    int64_t ans = -1e9;
    for (int tot = 0; tot <= m; tot++) ans = max({ans, f[n][tot][0 + m][0], f[n][tot][0 + m][1]});
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